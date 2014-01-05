
//TODO check

/**
 * @file cFibNodeHandler
 * file name: cFibNodeHandler.cpp
 * @author Betti Oesterholz
 * @date 17.06.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for handling Fib object nodes for the
 * Fib creator application.
 *
 *
 * Copyright (C) @c GPL3 2013 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file implements a class for handling Fib object nodes for the
 * Fib creator application.
 * It should store all the Fib nodes of the application and make sure,
 * that for every Fib object there is exactly one Fib node.
 * It will link Fib nodes to there superior and lower nodes.
 * @see cFibNode::setNextSuperiorNodes
 * @see cFibNode::setNextLowerNodes
 * It will also delete Fib nodes without a listener and delete Fib object
 * roots without a Fib nodes for it or a contained Fib object.
 * So if you remove the last listener from a Fib node, which is handeled by
 * this object, you should treat the Fib node as deleted.
 *
 * @pattern singelton
 */
/*
History:
17.06.2013  Oesterholz  created
*/

//TODO switches for test proposes
#define DEBUG


//TODO
//#define SWITCH_SUPERIOR_EVALUED_OBJECT


#include <list>
#include <map>
#include <utility>

#include <QtGlobal>
#include <QThread>

#include "cFibNodeHandler.h"

#include "cThreadDeleteNodesWithoutListener.h"

#include "fibDatatyps.h"

#include "cList.h"
#include "cRoot.h"
#include "cExtObject.h"
#include "cIf.h"


using namespace std;
using namespace fib::nCreator;
using namespace fib;


/**
 * The delay time in secounds betwean when it should be tried to delete not
 * needed nodes.
 * @see tmNextDeleteNodesAction
 * @see deleteNodesWithoutListeners()
 */
#define TM_DELAY_BETWEAN_DELETE_NODES_ACTION 10


//static variable

/**
 * A pointer to the node handler object.
 */
cFibNodeHandler * cFibNodeHandler::pFibNodeHandler = NULL;



namespace fib{
namespace nCreator{
namespace nFibNodeHandler{

	/**
	 * This class is for deleting the Fib node handler when the programm ends.
	 * @see cFibNodeHandler
	 */
	class cFibNodeHandlerDeleter{
	public:
		
		/**
		 * destructor which deletes the Fib node handler if not allready deleted
		 */
		~cFibNodeHandlerDeleter() {
			
			if ( cFibNodeHandler::pFibNodeHandler != NULL ) {
				//delete node handler
				delete cFibNodeHandler::pFibNodeHandler;
				cFibNodeHandler::pFibNodeHandler = NULL;
			}
		}
		
	};//end class cFibNodeHandlerDeleter
	
	/**
	 * Object to delete the Fib node handler when the programm ends.
	 */
	cFibNodeHandlerDeleter fibNodeHandlerDeleter;
	
};//end namespace nFibNodeHandler
};//end namespace nCreator
};//end namespace fib





/**
 * constructor for the Fib object node handler
 */
cFibNodeHandler::cFibNodeHandler():
		tmNextDeleteNodesAction( time( NULL ) + TM_DELAY_BETWEAN_DELETE_NODES_ACTION ) {
	
	pFibNodeHandler = this;
}


/**
 * destructor
 */
cFibNodeHandler::~cFibNodeHandler() {
	
	DEBUG_OUT_L2(<<"cFibNodeHandler::~cFibNodeHandler() called"<<endl<<flush);
	//delete all Fib object nodes
	for ( set< cFibNode * >::iterator itrFibNode = setFibNodes.begin();
			itrFibNode != setFibNodes.end(); itrFibNode++ ) {
		
		delete (*itrFibNode);
	}
	setFibNodes.clear();
	
	//delete all Fib objects
#ifdef DEBUG
	DEBUG_OUT_L2(<<"cFibNodeHandler::~cFibNodeHandler() existing "<<setFibObjectsRoot.size()<<" root Fib objects"<<endl<<flush);
	for ( set< cFibElement * >::iterator itrFibObject = setFibObjectsRoot.begin();
			itrFibObject != setFibObjectsRoot.end(); itrFibObject++ ) {
		
		DEBUG_OUT_L3(<<"cFibNodeHandler::~cFibNodeHandler() existing Fib object root "<<(*itrFibObject)<<endl<<flush);
	}
#endif //DEBUG
	DEBUG_OUT_L2(<<"cFibNodeHandler::~cFibNodeHandler() delete all "<<setFibObjectsRoot.size()<<" Fib objects"<<endl<<flush);
	for ( set< cFibElement * >::iterator itrFibObject = setFibObjectsRoot.begin();
			itrFibObject != setFibObjectsRoot.end(); itrFibObject++ ) {
		
		DEBUG_OUT_L3(<<"cFibNodeHandler::~cFibNodeHandler() delete Fib object root "<<(*itrFibObject)<<" (superior "<<flush<<(*itrFibObject)->getSuperiorFibElement()<<")"<<endl<<flush);
		(*itrFibObject)->deleteObject();
	}
	setFibObjectsRoot.clear();
	
	//delete the mappings
	DEBUG_OUT_L2(<<"cFibNodeHandler::~cFibNodeHandler() delete the mappings"<<endl<<flush);
	mapFibNodes.clear();
	mapFibObjectRoots.clear();
	mapNodesForRoots.clear();
	
	//delete the mutex for the Fib node
	for ( map< cFibElement * , QMutex * >::iterator
			itrFibObjectMutex = mapFibObjectRootsMutex.begin();
			itrFibObjectMutex != mapFibObjectRootsMutex.end(); itrFibObjectMutex++ ) {
		
		delete (itrFibObjectMutex->second);
	}
	
	DEBUG_OUT_L2(<<"cFibNodeHandler::~cFibNodeHandler() done"<<endl<<flush);
}


/**
 * @return a instance of the Fib object node handler
 */
cFibNodeHandler * cFibNodeHandler::getInstance() {
	
	if ( pFibNodeHandler == NULL ) {
		//create a new instance
		pFibNodeHandler = new cFibNodeHandler();
	}//else return existing instance
	return pFibNodeHandler;
}


/**
 * This method returns the Fib node for the given Fib object.
 * If no Fib node exists till now one is created.
 * Beware: Nodes without a listener will be deleted.
 * 	Also root Fib objects wich don't contain a Fib object to which
 * 	a node points, will be deleted.
 *
 * @see mapFibNodes
 * @param pFibObject the Fib object for the Fib node to return
 * @param pFibNodeChangeListener the listener for node changes of the to
 * 	return Fib node
 * @param bIsChangebel true (standard value) if (the Fib element
 * 	 pFibObject of) the to create node is changebel, else false
 * @return the Fib node for the given Fib object
 */
cFibNode * cFibNodeHandler::getNodeForFibObject( cFibElement * pFibObject,
		lFibNodeChanged * pFibNodeChangeListener, const bool bIsChangebel ) {
	
	DEBUG_OUT_L2(<<"cFibNodeHandler("<<this<<")::getNodeForFibObject( pFibObject="<<pFibObject<<", bIsChangebel="<<(bIsChangebel?"true":"false")<<") called"<<endl<<flush);
	if ( pFibObject == NULL ) {
		//no Fib object -> no node
		return NULL;
	}
	
	mutexFibNodeHandler.lock();
	map< cFibElement * , cFibNode * >::iterator itrFoundFibNode =
		mapFibNodes.find( pFibObject );
		
	if ( itrFoundFibNode != mapFibNodes.end() ) {
		//existing Fib node found
		DEBUG_OUT_L2(<<"cFibNodeHandler("<<this<<")::getNodeForFibObject( "<<pFibObject<<") existing Fib node found"<<endl<<flush);
		cFibNode * pFoundFibNode = itrFoundFibNode->second;
		if ( pFibNodeChangeListener != NULL ) {
			//register the Fib node change listener
			pFoundFibNode->registerNodeChangeListener( pFibNodeChangeListener );
		}
		mutexFibNodeHandler.unlock();
		DEBUG_OUT_L2(<<"cFibNodeHandler("<<this<<")::getNodeForFibObject( "<<pFibObject<<") done found node to return: "<<pFoundFibNode<<endl<<flush);
		return pFoundFibNode;
	}//else no existing Fib node found -> create a new Fib node
	DEBUG_OUT_L2(<<"cFibNodeHandler("<<this<<")::getNodeForFibObject( "<<pFibObject<<") no existing Fib node found -> create a new Fib node"<<endl<<flush);
	
	cFibNode * pFibNode = new cFibNode( pFibObject, bIsChangebel );
	if ( pFibNodeChangeListener != NULL ) {
		//register the Fib node change listener
		pFibNode->registerNodeChangeListener( pFibNodeChangeListener );
	}
	
	//update the Fib node andler members
	cFibElement * pFibObjectRoot = pFibObject->getMasterRoot();
	DEBUG_OUT_L2(<<"cFibNodeHandler::getNodeForFibObject() add root Fib object "<<pFibObjectRoot<<endl<<flush);
	pair< set< cFibElement * >::iterator, bool > paRootInserted =
		setFibObjectsRoot.insert( pFibObjectRoot );
	if ( ! paRootInserted.second ) {
#ifdef SWITCH_SUPERIOR_EVALUED_OBJECT

		//find superior Fib objects
		set< cFibNode * > setSuperiorNodes;
		//search for all superior nodes
		list< cFibElement * > liSuperiorFibElements =
			getSuperiorFibElement( pFibObject );
		
		while ( ! liSuperiorFibElements.empty ) {
			//check next superior Fib element
			pActualSuperiorObject = liSuperiorFibElements.front();
			liSuperiorFibElements.pop_front();
			
			//search the possible nodes
			for ( set< cFibNode * >::iterator
						itrActualNode = setFibNodes.begin();
					itrActualNode != setFibNodes.end(); itrActualNode++ ) {
				
				if ( pActualSuperiorObject == ((*itrActualNode)->pFibObject) ) {
					//superior node found
					setSuperiorNodes.insert( *itrActualNode );
					break;
				}
			}
		}//while superior Fib elements to check exists
		
		//find the next lower Fib objects
		if ( ! setSuperiorNodes.empty() ) {
			
			/*check which of the lower Fib objects of the superior Fib object is
			 a lower Fib object of pFibObject and move them to the new node*/
			set< cFibNode * > setNextSuperiorLowerNodes;
			map< cFibElement *, cFibNode * > mapSuperiorNodeFibElements;
			for ( set< cFibNode * >::iterator itrSuperiorNode = setSuperiorNodes.begin();
					itrSuperiorNode != setSuperiorNodes.end(); itrSuperiorNode++ ) {
				setNextSuperiorLowerNodes.insert(
					(*itrSuperiorNode)->setNextLowerNodes.begin(),
					(*itrSuperiorNode->setNextLowerNodes.end() );
				mapSuperiorNodeFibElements.inser(
					pSuperiorNode->pFibObject, pSuperiorNode );
				
			}
			//the Fib element of the superior node
			for ( set< cFibNode * >::iterator
						itrNextSupLower = setNextSuperiorLowerNodes.begin();
					itrNextSupLower != setNextSuperiorLowerNodes.end();
					itrNextSupLower++ ) {
				/* check the superior nodes of the actual lower Fib node (lower
				 * to next superior)*/
				//remove the link betwean lower node and next superior nodes
				for (set< cFibNode * >::iterator
							itrSuperiorNode = setSuperiorNodes.begin();
						itrSuperiorNode != setSuperiorNodes.end(); itrSuperiorNode++ ) {
					//remove connection from actual lower node to superior node
					(*itrSuperiorNode)->setNextLowerNodes.erase( *itrNextSupLower );
					(*itrNextSupLower)->setNextSuperiorNodes.erase( *itrSuperiorNode );
					
				}//end for all superior nodes
				
				list< cFibElement * > liSuperiorObjects =
					getSuperiorFibElements( (itrNextSupLower*)->pFibObject );
				
				while ( ! liSuperiorObjects.empty() ) {
					//check next superrior Fib element
					cFibElement * pActualSuperiorObject =
						liSuperiorObjects.front();
					liSuperiorObjects.pop_front();
					
					//check if the given superior is still a superior actual lower Fib node
					const map< cFibElement *, cFibNode * >::iterator
						itrFoundSuperiorNodeElement =
							mapSuperiorNodeFibElements.find( pActualSuperiorObject );
					
					if ( itrFoundSuperiorNodeElement != mapSuperiorNodeFibElements.end() ) {
						// actual superior is also a next superior
						//make the link betwean lower node and next superior node
						itrFoundSuperiorNodeElement->second->setNextLowerNodes.insert(
							*itrNextSupLower );
						(*itrNextSupLower)->setNextSuperiorNodes.insert(
							itrFoundSuperiorNodeElement->second );
						// don't evalue more superior of actual node + check next superior element
						continue;
					}
					//check if the given superior is a superior of the new Fib node
					if ( pActualSuperiorObject == pFibObject ) {
						/* actual superior is Fib object for new node
						 *-> move lower Fib node to new Fib node*/
						pFibNode->setNextLowerNodes.insert( *itrNextSupLower );
						(*itrNextSupLower)->setNextSuperiorNodes.insert( pFibNode );
						//check next superior element
						continue;
					}
					const list< cFibElement * > liActualSuperiorObjects =
						getSuperiorFibElements( pActualSuperiorObject );
					
					liSuperiorObjects.insert( liSuperiorObjects.end(),
						liActualSuperiorObjects.begin(), liActualSuperiorObjects.end() );
				}//end while superior nodes exists
			}//end for all lower Fib nodes of the superior Fib nodes
			
			//link the new node as lower to its next superior node
			//make connection from new Fib node to all its superior nodes
			for (set< cFibNode * >::iterator
						itrSuperiorNode = setSuperiorNodes.begin();
					itrSuperiorNode != setSuperiorNodes.end(); itrSuperiorNode++ ) {
				//make connection from superior node to new node
				(*itrSuperiorNode)->setNextLowerNodes.insert( pFibNode );
				pFibNode->setNextSuperiorNodes.insert( *itrSuperiorNode );
				
			}//end for all superior nodes
			
		}else{//no superior node found
			//search for lower Fib element nodes
			//check for all Fib nodes in the root Fib object without superior nodes
			list< cFibNode * > liPossibleLowerNodes;
			for ( set< cFibNode * >::iterator itrActualNode = setFibNodes.begin();
					itrActualNode != setFibNodes.end(); itrActualNode++ ) {
				
				if ( (*itrActualNode)->setNextSuperiorNodes.empty() ) {
					/*node has no superior nodes
					-> it is possible a lower to the new node*/
					liPossibleLowerNodes.push_back( (*itrActualNode) );
				}//node allready has superior nodes
			}
			if ( list< cFibNode * >::iterator
						itrPossibleLowerNode = liPossibleLowerNodes.begin();
					itrPossibleLowerNode != liPossibleLowerNodes.end();
					itrPossibleLowerNode++ ) {
				//check superior Fib elements of possible lower node
				list< cFibElement * > liSuperiorObjects =
					getSuperiorFibElements( (itrNextSupLower*)->pFibObject );
				
				while ( ! liSuperiorObjects.empty() ) {
					cFibElement * pActualSuperiorObject =
						liSuperiorObjects.front();
					liSuperiorObjects.pop_front();
					
					if ( pActualSuperiorObject == pFibObject ) {
						/* actual superior is Fib object for new node
						 *-> (mark lower Fib node to) move lower Fib node to new
						 *  Fib node*/
						pFibNode->setNextLowerNodes.insert( *itrPossibleLowerNode );
						(*itrPossibleLowerNode)->setNextSuperiorNodes.insert( pFibNode );
						//check next superior element
						continue;
					}
					const list< cFibElement * > liActualSuperiorObjects =
						getSuperiorFibElements( pActualSuperiorObject );
					
					liSuperiorObjects.insert( liSuperiorObjects.end(),
						liActualSuperiorObjects.begin(), liActualSuperiorObjects.end() );
				}//end while superior nodes exists
			}//end for all lower nodes
		}//if superior node found

#else //SWITCH_SUPERIOR_EVALUED_OBJECT
//TODO weg:

		/*root Fib object allready existing
		 * -> link to existing superior and lower nodes*/
		set< cFibNode * > & setNodesForRoot = mapNodesForRoots[ pFibObjectRoot ];
		
		//find superior Fib object
		/*list with the possible nodes for superior node elements
		 * - first: a pointer to the the node
		 * - second: the number of the Fib element in the order of
		 * 	Fib elements for the node (see cFibElement::getNumberOfElement() )
		 */
		list< pair< cFibNode *, unsignedIntFib > > liPossibleNodes;
		//fill liPossibleNodes with nodes from
		for ( set< cFibNode * >::iterator itrActualNode = setNodesForRoot.begin();
				itrActualNode != setNodesForRoot.end(); itrActualNode++ ) {
			liPossibleNodes.push_back( pair< cFibNode *, unsignedIntFib >(
				(*itrActualNode),
				((*itrActualNode)->pFibObject)->getNumberOfElement() ) );
		}
		
		cFibNode * pSuperiorNode = NULL;
		
		bool bCheckNodesIfPossible = true;
		
		for ( cFibElement * pActualSuperiorObject =
			pFibObject->getSuperiorFibElement(); pActualSuperiorObject != NULL;
			pActualSuperiorObject = pActualSuperiorObject->getSuperiorFibElement() ) {
			
			const unsignedIntFib uiActualFibElementNumber =
				pActualSuperiorObject->getNumberOfElement();
			//search the possible nodes
			if ( bCheckNodesIfPossible ) {
				//check if nodes are still possible
				for ( list< pair< cFibNode *, unsignedIntFib > >::iterator
							itrActualNode = liPossibleNodes.begin();
						itrActualNode != liPossibleNodes.end(); ) {
					
					if ( pActualSuperiorObject == (itrActualNode->first->pFibObject) ) {
						//superior node found
						pSuperiorNode = itrActualNode->first;
						break;
					}
					//check if the node is still possible
					if ( itrActualNode->second < uiActualFibElementNumber ) {
						//node is still possible
						itrActualNode++;
					}else{/*actual node Fib element number is greater/after actual
						 superior Fib element number -> node is not possible anymore*/
						itrActualNode = liPossibleNodes.erase( itrActualNode );
					}
				}
			}else{//don't check if nodes are still possible
				for ( list< pair< cFibNode *, unsignedIntFib > >::iterator
							itrActualNode = liPossibleNodes.begin();
						itrActualNode != liPossibleNodes.end(); itrActualNode++ ) {
					
					if ( pActualSuperiorObject == (itrActualNode->first->pFibObject) ) {
						//superior node found
						pSuperiorNode = itrActualNode->first;
						break;
					}
				}
			}
			if ( pSuperiorNode ) {
				//superior node found -> stop search
				break;
			}
			bCheckNodesIfPossible = pActualSuperiorObject->isBranch();
		}
		if ( pSuperiorNode ) {
			//superior node found
			
			/*check which of the lower Fib objects of the superior Fib object is
			 a lower Fib object of pFibObject and move them to the new node*/
			set< cFibNode * > & setNextSuperiorLowerNodes =
				pSuperiorNode->setNextLowerNodes;
			//list of the Fib nodes which are lower than the new node
			list< cFibNode * > liLowerNodesOfNewNode;
			//the Fib element of the superior node elements)
			const cFibElement * pSuperiorNodeFibElement =
				pSuperiorNode->pFibObject;
			for ( set< cFibNode * >::iterator
						itrNextSupLower = setNextSuperiorLowerNodes.begin();
					itrNextSupLower != setNextSuperiorLowerNodes.end();
					itrNextSupLower++ ) {
				/* check the superior nodes of the actual lower Fib node (lower
				 * to next superior)*/
				
				list< cFibElement * > liSuperiorObjects =
					getSuperiorFibElements( (*itrNextSupLower)->pFibObject );
				
				while ( ! liSuperiorObjects.empty() ) {
					cFibElement * pActualSuperiorObject =
						liSuperiorObjects.front();
					liSuperiorObjects.pop_front();
					if ( pActualSuperiorObject == pSuperiorNodeFibElement ) {
						// actual superior is next superior -> check next superior element
						continue;
					}
					if ( pActualSuperiorObject == pFibObject ) {
						/* actual superior is Fib object for new node
						 *-> (mark lower Fib node to) move lower Fib node to new
						 *  Fib node*/
						liLowerNodesOfNewNode.push_back( *itrNextSupLower );
						//check next superior element
						continue;
					}
					const list< cFibElement * > liActualSuperiorObjects =
						getSuperiorFibElements( pActualSuperiorObject );
					
					liSuperiorObjects.insert( liSuperiorObjects.end(),
						liActualSuperiorObjects.begin(), liActualSuperiorObjects.end() );
				}//end while superior nodes exists
			}//end for all lower Fib nodes of the superior Fib nodes
			//move the found nodes
			for ( list< cFibNode * >::iterator itrLowerNode = liLowerNodesOfNewNode.begin();
					itrLowerNode != liLowerNodesOfNewNode.end(); itrLowerNode++ ) {
				//move actual lower node from superior node to new node
				setNextSuperiorLowerNodes.erase( *itrLowerNode );
				(*itrLowerNode)->setNextSuperiorNodes.erase( pSuperiorNode );
				
				pFibNode->setNextLowerNodes.insert( *itrLowerNode );
				(*itrLowerNode)->setNextSuperiorNodes.insert( pFibNode );
			}
			//link the new node as lower to its next superior node
			setNextSuperiorLowerNodes.insert( pFibNode );
			pFibNode->setNextSuperiorNodes.insert( pSuperiorNode );
		}else{//no superior node found
			//search for lower Fib element nodes
			//check for all Fib nodes in the root Fib object without superior nodes
			list< cFibNode * > liPossibleLowerNodes;
			for ( set< cFibNode * >::iterator itrActualNode = setNodesForRoot.begin();
					itrActualNode != setNodesForRoot.end(); itrActualNode++ ) {
				
				if ( (*itrActualNode)->setNextSuperiorNodes.empty() ) {
					/*node has no superior nodes
					-> it is possible a lower to the new node*/
					liPossibleLowerNodes.push_back( (*itrActualNode) );
				}//node allready has superior nodes
			}
			for ( list< cFibNode * >::iterator
						itrPossibleLowerNode = liPossibleLowerNodes.begin();
					itrPossibleLowerNode != liPossibleLowerNodes.end();
					itrPossibleLowerNode++ ) {
				//check superior Fib elements of possible lower node
				list< cFibElement * > liSuperiorObjects =
					getSuperiorFibElements( (*itrPossibleLowerNode)->pFibObject );
				
				while ( ! liSuperiorObjects.empty() ) {
					cFibElement * pActualSuperiorObject =
						liSuperiorObjects.front();
					liSuperiorObjects.pop_front();
					
					if ( pActualSuperiorObject == pFibObject ) {
						/* actual superior is Fib object for new node
						 *-> (mark lower Fib node to) move lower Fib node to new
						 *  Fib node*/
						pFibNode->setNextLowerNodes.insert( *itrPossibleLowerNode );
						(*itrPossibleLowerNode)->setNextSuperiorNodes.insert( pFibNode );
						//check next superior element
						continue;
					}
					const list< cFibElement * > liActualSuperiorObjects =
						getSuperiorFibElements( pActualSuperiorObject );
					
					liSuperiorObjects.insert( liSuperiorObjects.end(),
						liActualSuperiorObjects.begin(), liActualSuperiorObjects.end() );
				}//end while superior nodes exists
			}//end for all lower nodes
		}//if superior node found
#endif //SWITCH_SUPERIOR_EVALUED_OBJECT
		
		//add the new Fib node to the Fib object root
		setNodesForRoot.insert( pFibNode );
	}else{//new master root element -> no lower or superior nodes
		mapNodesForRoots[ pFibObjectRoot ].insert( pFibNode );
	}
	setFibNodes.insert( pFibNode );
	mapFibNodes.insert( pair< cFibElement * , cFibNode * >(
			pFibObject, pFibNode ) );
	mapFibObjectRoots.insert( pair< cFibElement * , cFibElement * >(
			pFibObject, pFibObjectRoot ) );
	
	mutexFibNodeHandler.unlock();
	
	/* start tread to call deleteNodesWithoutListeners() if the last start
	 * was more than 10 seconds in the past*/
	if ( tmNextDeleteNodesAction < time( NULL )  ) {
		//set the time when it should be tried to delete not needed nodes the next time
		tmNextDeleteNodesAction = time( NULL ) + TM_DELAY_BETWEAN_DELETE_NODES_ACTION;
		
		nFibNodeHandler::cThreadDeleteNodesWithoutListener *
			pThreadDeleteNodesWithoutListener =
				new nFibNodeHandler::cThreadDeleteNodesWithoutListener();
		/*TODO weg: no result needed: connect( pThreadDeleteNodesWithoutListener,
			&cThreadDeleteNodesWithoutListener::resultReady, this,
			&MyObject::handleResults);*/
		
		QObject::connect( pThreadDeleteNodesWithoutListener, SIGNAL( finished() ),
			pThreadDeleteNodesWithoutListener, SLOT( deleteLater() ) );
		//start the thread with low piority
		pThreadDeleteNodesWithoutListener->start( QThread::LowestPriority );
	}
	DEBUG_OUT_L2(<<"cFibNodeHandler("<<this<<")::getNodeForFibObject( "<<pFibObject<<") done new node to return: "<<pFibNode<<endl<<flush);
	return pFibNode;
}


/*TODO listen for external object changes (new external object,
 * delete external object or change identifier of external object)*/



/**
 * This method checks if the given pointer points to a in this handler
 * existing Fib node.
 *
 * @param pFibNode a pointer to the Fib node to check
 * @return true if the given Fib node points to an existing Fib node
 * 	in this handler, else false
 */
bool cFibNodeHandler::isValidNode( cFibNode * pFibNode ) {
	
	//check if the Fib node exists
	const set< cFibNode * >::const_iterator itrFoundFibNode =
		setFibNodes.find( pFibNode );
	return ( itrFoundFibNode != setFibNodes.end() );
}


/**
 * This method returns the next Fib node, which contains the given Fib
 * object.
 * Beware: Nodes without a listener will be deleted.
 * 	Also root Fib objects, wich don't contain a Fib object, to which
 * 	a node points, will be deleted.
 *
 * @see mapFibNodes
 * @see getNodeForFibObject()
 * @param pFibObject the Fib object for the Fib node to return
 * @return the next Fib node which contains the given Fib object, or
 * 	NULL if non exists
 */
cFibNode * cFibNodeHandler::getContainingNodeForFibObject( cFibElement * pFibObject ) {
	
	for ( cFibElement * pActualFibElement = pFibObject; pActualFibElement != NULL;
			pActualFibElement = pActualFibElement->getSuperiorFibElement() ) {
		//try to find a Fib node for the actual Fib element
		map< cFibElement * , cFibNode * >::iterator itrActualFibElementNode =
			mapFibNodes.find( pActualFibElement );
		
		if ( itrActualFibElementNode != mapFibNodes.end() ) {
			//node for Fib element found -> return it
			return itrActualFibElementNode->second;
		}
	}//no node for superior Fib element found -> return NULL
	return NULL;
}


/**
 * This method integrates the given Fib object into the given other Fib object.
 * All not needed parts of the Fib objects will be deleted.
 *
 * @param pContainingNode a pointer to the node which contains the
 * 	Fib object to replace
 * @param pOriginalFibObjectToReplace the Fib object which to replace with
 * 	the given other Fib object pNewFibObject
 * @param pNewFibObject the Fib object which schould be integrated
 * @param pChangedBy a pointer to the object which had created the new
 * 	Fib object pNewFibObject (which called this method)
 * @return true if the Fib object could be integrated
 */
bool cFibNodeHandler::integrateFibObjectIntoNode( cFibNode * pContainingNode,
		cFibElement * pOriginalFibObjectToReplace, cFibElement * pNewFibObject,
		const QObject * pChangedBy ) {
	
	DEBUG_OUT_L2(<<"bool cFibNodeHandler::integrateFibObjectIntoNode( pContainingNode="<<pContainingNode<<", pOriginalFibObjectToReplace="<<pOriginalFibObjectToReplace<<", pNewFibObject="<<pNewFibObject<<", pChangedBy="<<pChangedBy<<" ) called"<<endl<<flush);
	
	if ( ( pContainingNode == NULL ) || ( pOriginalFibObjectToReplace == NULL ) ||
			( pNewFibObject == NULL ) ) {
		//can't integrate Fib object
		if ( pNewFibObject != NULL ) {
			DEBUG_OUT_L2(<<"bool cFibNodeHandler::integrateFibObjectIntoNode() delete new Fib object ("<<pNewFibObject<<" delete Fib object)"<<endl<<flush);
			pNewFibObject->deleteObject();
		}
		DEBUG_OUT_L2(<<"bool cFibNodeHandler::integrateFibObjectIntoNode() done NULL given"<<endl<<flush);
		return false;
	}
	
	if ( ! pContainingNode->bIsChangebel ) {
		//original not changebel -> can't integrate new Fib object pNewFibObject
		DEBUG_OUT_L2(<<"bool cFibNodeHandler::integrateFibObjectIntoNode() done original not changebel -> can't integrate new Fib object pNewFibObject -> delete Fib object pNewFibObject ("<<pNewFibObject<<")"<<endl<<flush);
		pNewFibObject->deleteObject();
		return false;
	}
	
	
	if ( pContainingNode->getFibObject() == NULL ) {
		//set new Fib object pNewFibObject
		DEBUG_OUT_L2(<<"bool cFibNodeHandler::integrateFibObjectIntoNode() old Fib object NULL -> set new Fib object pNewFibObject"<<endl<<flush);
		//lock Fib node
		lock( pContainingNode );
		
		pContainingNode->pFibObject = pNewFibObject;
		pContainingNode->ulVersion = 0;
		pContainingNode->pMasterRoot = pNewFibObject->getMasterRoot();
		//notify Fib node listeners for change
		pContainingNode->fibObjectChanged( pChangedBy );
		
		unlock( pContainingNode );
		
	}else if ( ! pOriginalFibObjectToReplace->equal( *pNewFibObject, false ) ) {
		
		//transfer the node and all its subnodes
		DEBUG_OUT_L2(<<"bool cFibNodeHandler::integrateFibObjectIntoNode() transfer the node and all its subnodes"<<endl<<flush);
		/*find all Fib nodes below the containing node pContainingNode and in
		 *the original Fib object pOriginalFibObjectToReplace*/
		const unsignedIntFib uiOrgFibElementNumber =
			pOriginalFibObjectToReplace->getNumberOfElement();
		const unsignedIntFib uiOrgNumberOfFibElements =
			pOriginalFibObjectToReplace->getNumberOfElements();
		const unsignedIntFib uiOrgLastFibElementNumber =
			uiOrgFibElementNumber + uiOrgNumberOfFibElements - 1;
		
		//lock Fib node
		lock( pContainingNode );
		
		const cFibElement * pOriginalFibObjectMasterRoot =
			pContainingNode->getMasterRoot();
		/* the list of nodes for which to check if they should be transvered
		 * (note that the master root elements of all Fib nodes on this list
		 * are identical (in same Fib object) to pContainingNode master root)*/
		list< cFibNode * > liNodesToCheckIfTransfer;
		liNodesToCheckIfTransfer.push_back( pContainingNode );
		/*set of Fib nodes below the containing node pContainingNode and in
		 *the original Fib object pOriginalFibObjectToReplace*/
		set< cFibNode * > setNodesToTransfer;
		cFibNode * pNodeToTransfer = NULL;
		DEBUG_OUT_L3(<<"bool cFibNodeHandler::integrateFibObjectIntoNode() find all nodes to transfer"<<endl<<flush);
		while ( ! liNodesToCheckIfTransfer.empty() ) {
			//take next node
			pNodeToTransfer = liNodesToCheckIfTransfer.front();
			liNodesToCheckIfTransfer.pop_front();
			
			if ( pNodeToTransfer->pFibObject == NULL ) {
				//no Fib object -> skip node
				continue;
			}
			//check if it should be transfered
			const unsignedIntFib uiNodeFibElementNumber =
				pNodeToTransfer->pFibObject->getNumberOfElement();
			
			if ( ( uiOrgFibElementNumber <= uiNodeFibElementNumber ) &&
					( uiNodeFibElementNumber <= uiOrgLastFibElementNumber ) ) {
				/*next node in original Fib object (pOriginalFibObjectToReplace)
				 -> next node is node to transfer*/
				setNodesToTransfer.insert( pNodeToTransfer );
			}else{/*next lower node is not a node to transfer
				-> if it should not be transfered check it next lower nodes*/
				set< cFibNode * > & setNextLowerNodes =
					pNodeToTransfer->setNextLowerNodes;
				
				for ( set< cFibNode * >::iterator
						itrNextLowerNode = setNextLowerNodes.begin();
						itrNextLowerNode != setNextLowerNodes.end(); itrNextLowerNode++ ) {
					
					if ( ( (*itrNextLowerNode) != NULL ) &&
							( (*itrNextLowerNode)->pMasterRoot ==
								pOriginalFibObjectMasterRoot ) ) {
						//master root elements identical (in same Fib object)
						liNodesToCheckIfTransfer.push_back( *itrNextLowerNode );
					}//else next lower node is not a node to transfer
				}//end for all next lower nodes
			}//end if next node was not a node to transfer
		}//end find all nodes to transfer
		
		if ( pOriginalFibObjectToReplace->getSuperiorFibElement() != NULL ) {
			//replace the original Fib object with new Fib object
			DEBUG_OUT_L3(<<"bool cFibNodeHandler::integrateFibObjectIntoNode() replace the original Fib object with new Fib object"<<endl<<flush);
			const bool bFibObjectReplaced = pOriginalFibObjectToReplace->
				overwriteObjectWithObject( pNewFibObject );
			if ( ! bFibObjectReplaced ) {
				//Error: Fib object could not be replaced
				DEBUG_OUT_EL2(<<"bool cFibNodeHandler::integrateFibObjectIntoNode() Error: Fib object could not be replaced (delete Fib object "<<pNewFibObject<<" (new))"<<endl<<flush);
				
				pNewFibObject->deleteObject();
				//unlock the containers of this object
				mutexFibNodeHandler.unlock();
				unlock( pContainingNode );
				
				return false;
			}
		}
		
		//transfer nodes
		DEBUG_OUT_L3(<<"bool cFibNodeHandler::integrateFibObjectIntoNode() transfer nodes"<<endl<<flush);
		set< cFibNode * > setLowestNodesToNotify;
		if ( ! setNodesToTransfer.empty() ) {
			//nodes to transfer
			for ( set< cFibNode * >::iterator
					itrActualNode = setNodesToTransfer.begin();
					itrActualNode != setNodesToTransfer.end(); itrActualNode++ ) {
				
				//transfer actual node
				set< cFibNode * > setActualLowestNodesToNotify =
					transferNode( *itrActualNode,
						pOriginalFibObjectToReplace, pNewFibObject );
				//remember lowest changed nodes
				setLowestNodesToNotify.insert( setActualLowestNodesToNotify.begin(),
					setActualLowestNodesToNotify.end() );
			}
		}
		
		if ( pOriginalFibObjectToReplace->getSuperiorFibElement() != NULL ) {
			//check if given containing node needs to be rewired
			DEBUG_OUT_L3(<<"bool cFibNodeHandler::integrateFibObjectIntoNode() check if given containing node needs to be rewired"<<endl<<flush);
			if ( pNodeToTransfer->pFibObject == pOriginalFibObjectToReplace ) {
				/*the original Fib object is the Fib object for the containing node needs
				 -> replace Fib object with new one*/
				pNodeToTransfer->pFibObject  = pNewFibObject;
				pNodeToTransfer->pMasterRoot = pNewFibObject->getMasterRoot();
			}
		}else{/*if no superior Fib element exists
			-> don't need to replace original Fib object with new Fib object
				+ just set new Fib object for the node*/
			DEBUG_OUT_L3(<<"bool cFibNodeHandler::integrateFibObjectIntoNode() no superior Fib element exists -> just set new Fib object for the node"<<endl<<flush);
			cFibElement * pOldMasterRoot = pNodeToTransfer->pMasterRoot;
			map< cFibElement * , set< cFibNode * > >::iterator
				itrNodesForRoot = mapNodesForRoots.find( pOldMasterRoot );
			
			pNodeToTransfer->pFibObject  = pNewFibObject;
			pNodeToTransfer->pMasterRoot = pNewFibObject->getMasterRoot();
			
			//for all changed roots update there master root object
			if ( ( itrNodesForRoot != mapNodesForRoots.end() ) &&
					( itrNodesForRoot->second.empty() ) ) {
				//no nodes for root remaining -> remove it from this class members
				DEBUG_OUT_L3(<<"cFibNodeHandler::integrateFibObjectIntoNode() erase old root Fib object "<<pOldMasterRoot<<endl<<flush);
				setFibObjectsRoot.erase( pOldMasterRoot );
				mapNodesForRoots.erase( itrNodesForRoot );
				mapFibObjectRootsMutex.erase( pOldMasterRoot );
				DEBUG_OUT_L3(<<"cFibNodeHandler::integrateFibObjectIntoNode() delete old root Fib object (delete Fib object)"<<pOldMasterRoot<<endl<<flush);
				pOldMasterRoot->deleteObject();
			}
			//update class members
			mapFibNodes[ pNewFibObject ] = pNodeToTransfer;
			DEBUG_OUT_L3(<<"cFibNodeHandler::integrateFibObjectIntoNode() add new root Fib object "<<pNodeToTransfer->pMasterRoot<<endl<<flush);
			setFibObjectsRoot.insert( pNodeToTransfer->pMasterRoot );
			mapFibObjectRoots[ pNewFibObject ] = pNodeToTransfer->pMasterRoot;
			mapNodesForRoots[ pNodeToTransfer->pMasterRoot ].insert( pNodeToTransfer );
		}
		unlock( pContainingNode );
		
		//for all lowest Fib nodes which contain changes -> notify them
		DEBUG_OUT_L3(<<"bool cFibNodeHandler::integrateFibObjectIntoNode() for all lowest Fib nodes which contain changes -> notify them"<<endl<<flush);
		if ( setLowestNodesToNotify.empty() ) {
			//notify given containing node of change
			pContainingNode->fibObjectChanged( pChangedBy );
			
		}else{//notify lowest nodes
			//increase version number of all changed (lower nodes)
			for ( set< cFibNode * >::iterator
					itrActualNode = setLowestNodesToNotify.begin();
					itrActualNode != setLowestNodesToNotify.end(); itrActualNode++ ) {
				//increase version number
				(*itrActualNode)->increaseFibObjectVersion();
				
			}//end increase the version number of all nodes
			
			for ( set< cFibNode * >::iterator
					itrActualNode = setLowestNodesToNotify.begin();
					itrActualNode != setLowestNodesToNotify.end(); itrActualNode++ ) {
				
				const eFibNodeChangedEvent fibNodeChangedEvent( (*itrActualNode),
					(*itrActualNode)->getFibObjectVersion(), pChangedBy );
				
				(*itrActualNode)->sendNodeChange( &fibNodeChangedEvent );
			}//end notify all nodes
		}
		
		//delete the original Fib object
		DEBUG_OUT_L3(<<"cFibNodeHandler::integrateFibObjectIntoNode() delete original root Fib object "<<pOriginalFibObjectToReplace<<" (delete Fib object)"<<endl<<flush);
		
		set< cFibElement * >::iterator itrRootFibObject =
			setFibObjectsRoot.find( pOriginalFibObjectToReplace );
		if ( itrRootFibObject != setFibObjectsRoot.end() ) {
			//original Fib object is a root Fib object
			setFibObjectsRoot.erase( itrRootFibObject );
			//erase entries from mapFibObjectRoots
			map< cFibElement * , cFibElement * >::iterator
				itrNextElement;
			for ( map< cFibElement * , cFibElement * >::iterator
					itrActualFibElement = mapFibObjectRoots.begin();
					itrActualFibElement != mapFibObjectRoots.end(); ) {
				itrNextElement = itrActualFibElement;
				itrNextElement++;
				if ( (itrActualFibElement->second) == pOriginalFibObjectToReplace ) {
					//delete entry
					mapFibObjectRoots.erase( itrActualFibElement );
				}//else use next element
				itrActualFibElement = itrNextElement;
			}
			//mapNodesForRoots value entry for root should allready be empty
			mapNodesForRoots.erase( pOriginalFibObjectToReplace );
			//delete the mutex for the root
			map< cFibElement * , QMutex * > ::iterator itrMutexForRoot =
				mapFibObjectRootsMutex.find( pOriginalFibObjectToReplace );
			if ( itrMutexForRoot->second ) {
				//delete mutex for Fib object
				delete (itrMutexForRoot->second);
			}
			mapFibObjectRootsMutex.erase( itrMutexForRoot );
		}//end if original Fib object is a root Fib object
		pOriginalFibObjectToReplace->deleteObject();
		
		//unlock the containers of this object
		mutexFibNodeHandler.unlock();
		
	}else{//original Fib object allready equal to new Fib object -> delete new
		DEBUG_OUT_L2(<<"bool cFibNodeHandler::integrateFibObjectIntoNode() original Fib object allready equal to new Fib object -> delete new (delete Fib object)"<<endl<<flush);
		pNewFibObject->deleteObject();
	}
	
	DEBUG_OUT_L2(<<"bool cFibNodeHandler::integrateFibObjectIntoNode( pContainingNode="<<pContainingNode<<", pOriginalFibObjectToReplace="<<pOriginalFibObjectToReplace<<", pNewFibObject="<<pNewFibObject<<", pChangedBy="<<pChangedBy<<" ) done"<<endl<<flush);
	return true;
}


namespace fib{
namespace nCreator{
namespace nFibNodeHandler{
namespace nTransferNode{


/**
 * @class cOpenPathForTransferNode
 * This class stores the data for a open path to a Fib node.
 *
 * help structure of the method @see cFibNodeHandler::transferNode()
 */
class cOpenPathForTransferNode{
public:
	
	/**
	 * The cost of the path.
	 */
	unsigned long ulPathCost;
	
	/**
	 * The cost of the path from the last found Fib element of the original
	 * path (not including it) to the last Fib element in the path
	 * (including it); see end condition 2.
	 *
	 * End condition 2: maximal possible gain = number of missing
	 * 	Fib objects x cost missing Fib objects
	 * 	-> if cost from last found Fib objects till path end is greater
	 * 	maximal possible gain
	 * 	-> stop enlarging of the path
	 */
	unsigned long ulPathCostFromLastFound;
	
	/**
	 * End Fib element of the path (=last Fib element integrated into the
	 * path, it is includes in the cost);
	 */
	cFibElement * pEndFibObject;
	
	/**
	 * A list of Fib element (in ther order) which are still missing in the
	 * path.
	 */
	list< pair< cFibElement *, unsignedIntFib > > liOpenElementsToFind;
	
	/**
	 * If true the subobject of pEndFibObject is equal to the subobject of
	 * the old first open Fib element to find, which was removed for the
	 * last integrated Fib element.
	 * @see pEndFibObject
	 * @see liOpenElementsToFind
	 */
	bool bEndSubobjectsEqual;
	
	
	/**
	 * init constructor
	 * It constructs an init path with one Fib element.
	 *
	 * @param pFirstFibElement the (first and only) Fib element for the path
	 * 	to create
	 * @param liPathToFind a list with pointers to the Fib elements of the
	 * 	remaining path to find
	 */
	cOpenPathForTransferNode( cFibElement * pFirstFibElement,
			list< pair< cFibElement *, unsignedIntFib > > & liPathToFind ):
			ulPathCost( 32 * liPathToFind.size() + 4 ),
			ulPathCostFromLastFound( 0 ),
			pEndFibObject( NULL ),
			liOpenElementsToFind( liPathToFind ),
			bEndSubobjectsEqual( false ) {
		
		integrateFibElementIntoPath( pFirstFibElement, 0 );
	}
	
	
	/**
	 * copy constructor
	 *
	 * @param pPathToCopy the path to copy
	 */
	cOpenPathForTransferNode( cOpenPathForTransferNode * pPathToCopy ):
			ulPathCost( pPathToCopy->ulPathCost ),
			ulPathCostFromLastFound( pPathToCopy->ulPathCostFromLastFound ),
			pEndFibObject( pPathToCopy->pEndFibObject ),
			liOpenElementsToFind( pPathToCopy->liOpenElementsToFind ),
			bEndSubobjectsEqual( pPathToCopy->bEndSubobjectsEqual ) {
		//nothing to do
	}
	
	
	/**
	 * This method will integrate the given Fib element into a clone of this path.
	 * The cost and path members of the clone element will be adapted.
	 *
	 * @see integrateFibElementIntoPath()
	 * @param pNextFibElement the Fib element, which should be integrated
	 * 	into a clone of this path;
	 * 	This Fib element as to be a subobject of the end / last
	 * 	Fib element of this path.
	 * @param uiNumberOfSubobject the number of subobject the given Fib
	 * 	element (pNextFibElement) was in its original superior Fib element
	 * @return a pointer to a path, which is equal to this path with the
	 * 	given Fib element integrated, or NULL if the Fib element could not
	 * 	be integrated into this path
	 * 	Beware: you have to care that the returned pointer is deleted
	 */
	cOpenPathForTransferNode * integrateFibElementIntoPathClone(
			cFibElement * pNextFibElement, unsigned int uiNumberOfSubobject = 1 ) {
		//clone this path
		cOpenPathForTransferNode * pPathClone =
			new cOpenPathForTransferNode( this );
		//integrate Fib element into path clone
		const bool bFibElementIntegrated =
			pPathClone->integrateFibElementIntoPath(
				pNextFibElement, uiNumberOfSubobject );
		
		if ( bFibElementIntegrated ) {
			//Fib element was integrated
			return pPathClone;
		}//else Fib element could not be integrated -> delete path clone and return NULL
		delete pPathClone;
		return NULL;
	}
	
	
	/**
	 * This method will integrate the given Fib element into this path.
	 * The cost and path members of this element will be adapted.
	 *
	 * costs for the path elements:
	 * 	- 32 missing Fib element
	 * 	- 4 Fib element to much
	 * 	- 2 Fib element wrong order
	 * 	- 1 Fib element wrong subobject (of branch)
	 * 	- 4 not equal subobject for new end object (? or try similarity value
	 * 		for subobjects )
	 *
	 * @see integrateFibElementIntoPathClone()
	 * @param pNextFibElement the Fib element, which should be integrated
	 * 	into this path;
	 * 	This Fib element as to be a subobject of the end / last
	 * 	Fib element of this path.
	 * @param uiNumberOfSubobject the number of subobject the given Fib
	 * 	element (pNextFibElement) was in its original superior Fib element
	 * @return true if the given Fib element could be integrated, else false
	 */
	bool integrateFibElementIntoPath(
			cFibElement * pNextFibElement, unsigned int uiNumberOfSubobject = 1 ) {
		
		if ( pNextFibElement == NULL ) {
			//can't create new path with no Fib element
			return false;
		}
		/*check if the given Fib element is equal to a Fib element in the
		 list of open Fib elements liOpenElementsToFind*/
		list< pair< cFibElement *, unsignedIntFib > >::iterator
			itrFoundEqualFibElement;
		for ( itrFoundEqualFibElement = liOpenElementsToFind.begin();
				itrFoundEqualFibElement != liOpenElementsToFind.end();
				itrFoundEqualFibElement++ ) {
			
			if ( pNextFibElement->equalElement( *(itrFoundEqualFibElement->first) ) ) {
				//equal Fib element found
				break;
			}
		}//end search for equal Fib element
		if ( itrFoundEqualFibElement != liOpenElementsToFind.end() ) {
			//equal Fib element found
			cFibElement * pEqualFibElement = itrFoundEqualFibElement->first;
			ulPathCostFromLastFound = 0;
			 /* applicable path costs for the next Fib elements:
			  * 	- 32 missing Fib element
			  * 	- 2 Fib element wrong order
			  * 	- 1 Fib element wrong subobject (of branch)
			  * 	- 4 not equal subobject for new end object (? or try similarity value
			  * 		for subobjects )*/
			ulPathCost -= 32;//one Fib element less missing
			//check Fib element in wrong order
			if ( itrFoundEqualFibElement != liOpenElementsToFind.begin() ) {
				//next Fib element not first of path to find
				ulPathCost += 2;//Fib elements in wrong order
			}
			//check Fib element in wrong subobject (of branch)
			if ( itrFoundEqualFibElement->second != uiNumberOfSubobject ) {
				ulPathCost += 1;//Fib element wrong subobject (of branch)
			}
			
			//check not equal subobjects for new end object
			if ( pNextFibElement->equal( *pEqualFibElement ) ) {
				//Fib objects are equal -> subobjects are equal
				if ( ! bEndSubobjectsEqual ) {
					//end Fib objects not equal before, but now equal -> reduce cost
					ulPathCost -= 4;
					bEndSubobjectsEqual = true;
				}
			}else{//Fib objects are not equal
				if ( bEndSubobjectsEqual ) {
					//end Fib objects equal before, but now not equal -> increase cost
					ulPathCost += 4;
					bEndSubobjectsEqual = false;
				}
			}
		}else{//no equal Fib element found -> 1 Fib element in path to much
			 // costs for the path element: 4 Fib element to much
			ulPathCost += 4;
			ulPathCostFromLastFound += 4;
		}
		//set the next Fib element to integrate as end / last Fib element of this path
		pEndFibObject = pNextFibElement;
		return true;
	}
	
	
	/**
	 * This method checks if the end condition for this path holds.
	 * If the end condition holds for this path, it should not be enlarged
	 * anymore (or no new Fib elements should be integrated).
	 *
	 * end condition check:
	 * 	1. leaf Fib element reached (last / end Fib element has no subobjects)
	 * 	2. maximal possible gain = number of missing Fib objects x cost
	 * 		missing Fib objects
	 * 		-> if cost from last found Fib objects till path end is greater
	 * 			maximal possible gain
	 * 		-> stop enlarging of the path
	 *
	 * @return true if the end condition holds, else false
	 */
	bool checkEndCondition() const{
		/* check end condition 1: leaf Fib element reached (last / end Fib
		 * 	element has no subobjects)*/
		if ( ( pEndFibObject == NULL ) ||
				( pEndFibObject->getNumberOfSubobjects() == 0 ) ) {
			//last / end Fib element of the path has no subobjects -> path ends
			return true;
		}
		/* check end condition 2: maximal possible gain = number of missing
		 * 	Fib objects x cost missing Fib objects
		 * 	-> if cost from last found Fib objects till path end is greater
		 * 	maximal possible gain -> stop enlarging of the path
		 */
		const unsigned long ulMaxPossibleGain =
			liOpenElementsToFind.size() * 32;
		if ( ulMaxPossibleGain < ulPathCostFromLastFound ) {
			return true;
		}//else
		//end condition not true
		return false;
	}
	
	
	/**
	 * Operation lower for the path.
	 * Lower path are better path.
	 *
	 * @see ulPathCost
	 * @param otherPath the path to which this path should be compared.
	 * @return true if this path has lower cost then the other path,
	 * 	else true if the cost is equal but the number of open Fib elements
	 * 	is lower else if both are equal true if the path cost from last
	 * 	found is lower, else false
	 */
	bool operator<( const cOpenPathForTransferNode & otherPath ) const{
		
		if ( ulPathCost < otherPath.ulPathCost ) {
			//this path is lower / better
			return true;
		}//else
		if ( ulPathCost == otherPath.ulPathCost ) {
			if ( liOpenElementsToFind.size() < otherPath.liOpenElementsToFind.size() ) {
				//this path is lower / better
				return true;
			}//else
			if ( liOpenElementsToFind.size() == otherPath.liOpenElementsToFind.size() ) {
				
				if ( ulPathCostFromLastFound < otherPath.ulPathCostFromLastFound ) {
					//this path is lower / better
					return true;
				}//else
			}
		}
		//this path is not lower
		return false;
	}
	
};//end class cOpenPathForTransferNode

};//end namespace nTransferNode
};//end namespace nFibNodeHandler
};//end namespace nCreator
};//end namespace fib


using namespace nFibNodeHandler::nTransferNode;

//TODO look at:

/**
 * This method will transfer the given Fib node and all Fib nodes for
 * Fib objects, which the Fib object for the given Fib node contains,
 * from one Fib object to a other Fib object.
 * For that the path from the given node pNodeToTransfer Fib object to
 * the (root) Fib element of the from Fib object pFromFibObject will be
 * evalued and the Fib node will be set to a Fib object, which path to the
 * Fib element pToFibObject is as similar as posible to the original path.
 * If more than one path is equal, the node will be set to the first
 * Fib object, which is (most) equal to its original Fib object.
 * This procedure will be repeated for all Fib nodes for Fib objects
 * containd in the given Fib nodes pNodeToTransfer Fib object.
 *
 * @param pNodeToTransfer a pointer to the Fib node, which and which lower
 * 	Fib nodes to transfer, its Fib object should be contained in pFromFibObject
 * @param pFromFibObject a pointer to the Fib object, from which to transfer
 * 	the Fib node (pNodeToTransfer)
 * @param pToFibObject a pointer to the Fib object, to which to transfer the
 * 	Fib nodes (pNodeToTransfer)
 * @return set of the pointers to the lowest nodes, which subobjects where changed
 * 		(they have no nodes below, which contain changed subobjects)
 */
set< cFibNode * > cFibNodeHandler::transferNode(
		cFibNode * pNodeToTransfer,
		cFibElement * pFromFibObject, cFibElement * pToFibObject ) {
	
	DEBUG_OUT_L3(<<"cFibNodeHandler::transferNode( pNodeToTransfer="<<pNodeToTransfer<<", pFromFibObject="<<pFromFibObject<<", pToFibObject="<<pToFibObject<<" ) started "<<endl<<flush);
	if ( ( pNodeToTransfer == NULL ) || ( pFromFibObject == NULL ) ||
			( pToFibObject == NULL ) ) {
		//can't integrate Fib node, something is missing
		return set< cFibNode * >();
	}
	
	/*evalue the path from the Fib node pNodeToTransfer to the Fib element
	of pFromFibObject*/
	list< pair< cFibElement *, unsignedIntFib > > liPathToFind;
	
	cFibElement * pNodeFibElement = pNodeToTransfer->getFibObject();
	cFibElement * pNextSuperiorFibElement;
	for ( cFibElement * pActualFibElement = pNodeFibElement;
			( pActualFibElement != pFromFibObject ) &&
			( pActualFibElement != NULL ); ) {
		//find number of subobject
		pNextSuperiorFibElement = pActualFibElement->getSuperiorFibElement();
		unsignedIntFib uiNumberOfSubobject = 0;
		if ( pNextSuperiorFibElement ) {
			//evalue the number of the subobject for the actual Fib object
			list< cFibElement * > liNextFibElementsSubobjects =
				pActualFibElement->getSubobjects();
			if ( ! liNextFibElementsSubobjects.empty() ) {
				//search for pActualFibElement in the subobjects
				uiNumberOfSubobject = 1;
				for ( list< cFibElement * >::const_iterator
						itrSubobject = liNextFibElementsSubobjects.begin();
						itrSubobject != liNextFibElementsSubobjects.end();
						itrSubobject++, uiNumberOfSubobject++ ) {
					
					if ( (*itrSubobject) == pActualFibElement ) {
						//pActualFibElement found
						break;
					}
				}//end search for pActualFibElement
				if ( liNextFibElementsSubobjects.size() < uiNumberOfSubobject ) {
					//pActualFibElement not found
					uiNumberOfSubobject = 0;
				}
			}
		}
		//push the actual Fib element to the front of the path
		liPathToFind.push_front( pair< cFibElement *, unsignedIntFib >(
			pActualFibElement, uiNumberOfSubobject ) );
		pActualFibElement = pNextSuperiorFibElement;
	}//end for find path to node
	
	
	// try to reverse the path of the Fib node to pFromFibObject
	
	/* set with the open paths (=path which can be still enlarged)
	 * @see nFibNodeHandler::nTransferNode::cOpenPathForTransferNode
	 */
	set< cOpenPathForTransferNode * > setOpenPaths;
	
	//best Fib object for the given Fib node (= best found path)
	cOpenPathForTransferNode * pBestFibObjectForNode =
		new cOpenPathForTransferNode( pToFibObject, liPathToFind );
	//add best path to open paths
	setOpenPaths.insert( new cOpenPathForTransferNode( pBestFibObjectForNode ) );
	
	//find the best path
	while ( ! setOpenPaths.empty() ) {
		//chose best path till now to enlarge it
		set< cOpenPathForTransferNode * >::iterator
			itrActualPath = setOpenPaths.begin();
		cOpenPathForTransferNode * pActualPath = (*itrActualPath);
		cFibElement * pActualPathEndFibElement = pActualPath->pEndFibObject;
		//remove choosen actual from open paths
		setOpenPaths.erase( itrActualPath );
		//add next possible Fib elements to best open path
		list< cFibElement * > liNextFibElementsForPath =
			pActualPathEndFibElement->getSubobjects();
		
		unsigned int uiNumberOfSubobject = 1;
		for ( list< cFibElement * >::iterator
				itrNextFibElement = liNextFibElementsForPath.begin();
				itrNextFibElement != liNextFibElementsForPath.end();
				itrNextFibElement++, uiNumberOfSubobject++ ) {
			
			//evalue costs for path which ends with the actual next Fib element
			cOpenPathForTransferNode * pNewPathForFibElement =
				pActualPath->integrateFibElementIntoPathClone( *itrNextFibElement,
					uiNumberOfSubobject );
			if ( pNewPathForFibElement == NULL ) {
				//no new path for Fib element -> check next
				continue;
			}
			
			//for new path + old best: choose the best path of the evalued paths
			if ( (*pBestFibObjectForNode) < (*pNewPathForFibElement) ) {
				//new path is better than old best path -> take it as new best path
				
				//old best path not needed anymore
				delete pBestFibObjectForNode;
				//set best path to (copy of) new path
				pBestFibObjectForNode = new cOpenPathForTransferNode( pNewPathForFibElement );
			}
			//check end condition for new paths
			if ( pNewPathForFibElement->checkEndCondition() ) {
				//new path is path that ends -> don't add to open path
				if ( pNewPathForFibElement != pBestFibObjectForNode ) {
					//new path not needed anymore -> delete it
					delete pNewPathForFibElement;
				}
			}else{//new path should be start point for more paths
				setOpenPaths.insert( pNewPathForFibElement );
			}
			
		}//end for all possible next Fib elements
		
		//actual path not needed anymore
		delete pActualPath;
		
	}//end while still open paths to check / enlarge
	/*set Fib object of Fib node to transfer to best Fib object for the
	 *given Fib node (= best found path)*/
	cFibElement * pOldFibNodeObject = pNodeToTransfer->pFibObject;
	cFibElement * pNewFibNodeObject = pBestFibObjectForNode->pEndFibObject;
	const cFibElement * pOriginalFibObjectMasterRoot =
		pNodeToTransfer->pMasterRoot;
	pNodeToTransfer->pFibObject  = pNewFibNodeObject;
	pNodeToTransfer->pMasterRoot = pNewFibNodeObject->getMasterRoot();
	
	//update class members
	mapFibNodes[ pNewFibNodeObject ] = pNodeToTransfer;
	DEBUG_OUT_L3(<<"cFibNodeHandler::transferNode() add new root Fib object "<<pNodeToTransfer->pMasterRoot<<endl<<flush);
	setFibObjectsRoot.insert( pNodeToTransfer->pMasterRoot );
	mapFibObjectRoots[ pNewFibNodeObject ] = pNodeToTransfer->pMasterRoot;
	mapNodesForRoots[ pNodeToTransfer->pMasterRoot ].insert( pNodeToTransfer );
	
	/*Find all Fib nodes below the found Fib node pNodeToTransfer
		- the Fib nodes have the same root and there Fib object
		Fib element number is betwean that of the found Fib node
		pNodeToTransfer and the last in the Fib (sub) object of the found
		Fib node
	 */
	
	const unsignedIntFib uiOrgFibElementNumber =
		pOldFibNodeObject->getNumberOfElement();
	const unsignedIntFib uiOrgNumberOfFibElements =
		pOldFibNodeObject->getNumberOfElements();
	const unsignedIntFib uiOrgLastFibElementNumber =
		uiOrgFibElementNumber + uiOrgNumberOfFibElements - 1;
	
	set< cFibNode * > & setNextLowerNodes = pNodeToTransfer->setNextLowerNodes;
	list< cFibNode * > liNodesToTransfer;
	for ( set< cFibNode * >::iterator
			itrNextLowerNode = setNextLowerNodes.begin();
			itrNextLowerNode != setNextLowerNodes.end(); itrNextLowerNode++ ) {
		
		cFibElement * pNextLowerNodeFibElement =
			(*itrNextLowerNode)->getFibObject();
		
		if ( (*itrNextLowerNode)->pMasterRoot ==
				pOriginalFibObjectMasterRoot ) {
			//master root elements identical (in same Fib object)
			const unsignedIntFib uiNextLowerNodeFibElementNumber =
				pNextLowerNodeFibElement->getNumberOfElement();
			
			if ( ( uiOrgFibElementNumber < uiNextLowerNodeFibElementNumber ) &&
					( uiNextLowerNodeFibElementNumber <= uiOrgLastFibElementNumber ) ) {
				/*next lower node in Fib object of actual Fib node
				 -> next lower node is node to transfer*/
				liNodesToTransfer.push_back( *itrNextLowerNode );
				//continue
			}
		}//else next lower node is not a node to transfer
	}//end for all next lower nodes
	/*for all Fib nodes below the found Fib node pNodeToTransfer
	-> transfer them (call transferNode)*/
	const bool bNodeFibObjectEqual = pOldFibNodeObject->equal( *pNewFibNodeObject );
	
	set< cFibNode * > setChangedLowestNodes;
	if ( bNodeFibObjectEqual || liNodesToTransfer.empty() ) {
		//old and new Fib node Fib objects equal or no more lower nodes to transfer
		
		if ( ! liNodesToTransfer.empty() ) {
			/*old and new Fib node Fib objects equal + lower nodes exists
			-> transfer lower nodes*/
			for ( list< cFibNode * >::iterator itrLowerNode = liNodesToTransfer.begin();
					itrLowerNode != liNodesToTransfer.end(); itrLowerNode++ ) {
				
				transferNodeForEqualFibObject(
					*itrLowerNode, pOldFibNodeObject, pNewFibNodeObject );
			}
		}//else no lower nodes exists
		/*if the Fib object for the found Fib nodes is equal to its old
		 Fib object or now lower nodes exists
		 -> mark Fib node as lowest changed*/
		setChangedLowestNodes.insert( pNodeToTransfer );
		
	}else{//old and new Fib node Fib objects not equal -> transfer with path search
		for ( list< cFibNode * >::iterator itrLowerNode = liNodesToTransfer.begin();
				itrLowerNode != liNodesToTransfer.end(); itrLowerNode++ ) {
			
			set< cFibNode * > setActualChangedNodes =
				transferNode( *itrLowerNode, pOldFibNodeObject, pNewFibNodeObject );
			
			if ( ! setActualChangedNodes.empty() ) {
				//if Fib objects for nodes changed
				setChangedLowestNodes.insert(
					setActualChangedNodes.begin(), setActualChangedNodes.end() );
			}
		}
		
	}//end if new and old Fib object are equal
	return setChangedLowestNodes;
}


/**
 * This method will transfer the given Fib node and all Fib nodes for
 * Fib objects, which the Fib object for the given Fib node contains,
 * from one Fib object to a other Fib object.
 * Both given Fib object have to be equal (pFromFibObject->equal( *pToFibObject )).
 * The Fib nodes will be transfered to the Fib element in the to Fib object
 * (pToFibObject) with the same Fib element number as the original Fib object
 * for the Fib node. (The Fib element numbers are relativ to the pFromFibObject
 * and pToFibObject Fib element numbers.)
 *
 * @param pNodeToTransfer a pointer to the Fib node, which and which lower
 * 	Fib nodes to transfer, its Fib object should be contained in pFromFibObject
 * @param pFromFibObject a pointer to the Fib object, from which to transfer
 * 	the Fib node (pNodeToTransfer);
 * 	it should be equal to pToFibObject
 * @param pToFibObject a pointer to the Fib object, to which to transfer the
 * 	Fib nodes (pNodeToTransfer)
 * 	it should be equal to pFromFibObject
 * @return true if the Fib nodes where transfered, else false
 */
bool cFibNodeHandler::transferNodeForEqualFibObject(
		cFibNode * pNodeToTransfer,
		cFibElement * pFromFibObject, cFibElement * pToFibObject ) {
	
	DEBUG_OUT_L2(<<"cFibNodeHandler::transferNodeForEqualFibObject( pNodeToTransfer="<<pNodeToTransfer<<", pFromFibObject="<<pFromFibObject<<", pToFibObject="<<pToFibObject<<" ) started"<<endl<<flush);
	if ( ( pNodeToTransfer == NULL ) || ( pFromFibObject == NULL ) ||
			( pToFibObject == NULL ) ) {
		//can't integrate Fib node, something is missing
		return false;
	}
	/*if both Fib objects pFromFibObject and pToFibObject are equal
	 -> set the Fib object for the Fib node to the Fib element with the
	 same (relativ) Fib element number as the old Fib object for the Fib node had
	 + repeat step for all lower / contained Fib nodes*/
	const unsigned int uiRootFromFibElementNumber =
		pFromFibObject->getNumberOfElement();
	const unsigned int uiRootToFibElementNumber =
		pToFibObject->getNumberOfElement();
		
	list< cFibNode * > liNodesToTransfer;
	liNodesToTransfer.push_back( pNodeToTransfer );
	while ( ! liNodesToTransfer.empty() ) {
		//take next node
		pNodeToTransfer = liNodesToTransfer.front();
		liNodesToTransfer.pop_front();
		//transfer actual Fib node
		cFibElement * pOriginalFibObject = pNodeToTransfer->getFibObject();
		const cFibElement * pOriginalFibObjectMasterRoot =
			pNodeToTransfer->pMasterRoot;
		
		const unsignedIntFib uiOrgFibElementNumber =
			pOriginalFibObject->getNumberOfElement();
		const unsignedIntFib uiOrgNumberOfFibElements =
			pOriginalFibObject->getNumberOfElements();
		const unsignedIntFib uiOrgLastFibElementNumber =
			uiOrgFibElementNumber + uiOrgNumberOfFibElements - 1;
		
		cFibElement * pNewFibElementForNode =
			pToFibObject->getFibElement( uiOrgFibElementNumber -
				uiRootFromFibElementNumber + uiRootToFibElementNumber );
			
		pNodeToTransfer->pFibObject  = pNewFibElementForNode;
		pNodeToTransfer->pMasterRoot = pNewFibElementForNode->getMasterRoot();
		
		//update class members
		mapFibNodes[ pNewFibElementForNode ] = pNodeToTransfer;
		DEBUG_OUT_L3(<<"cFibNodeHandler::transferNodeForEqualFibObject() add new root Fib object "<<pNodeToTransfer->pMasterRoot<<endl<<flush);
		setFibObjectsRoot.insert( pNodeToTransfer->pMasterRoot );
		mapFibObjectRoots[ pNewFibElementForNode ] = pNodeToTransfer->pMasterRoot;
		mapNodesForRoots[ pNodeToTransfer->pMasterRoot ].insert( pNodeToTransfer );
		
		/*Find all Fib nodes below the found Fib node pNodeToTransfer and
		 * add them to the nodes to transfer
			- the Fib nodes have the same root and there Fib object
			Fib element number is betwean that of the found Fib node
			pNodeToTransfer and the last in the Fib (sub) object of the found
			Fib node
		 */
		set< cFibNode * > & setNextLowerNodes = pNodeToTransfer->setNextLowerNodes;
		for ( set< cFibNode * >::iterator
				itrNextLowerNode = setNextLowerNodes.begin();
				itrNextLowerNode != setNextLowerNodes.end(); itrNextLowerNode++ ) {
			
			cFibElement * pNextLowerNodeFibElement =
				(*itrNextLowerNode)->getFibObject();
			
			if ( (*itrNextLowerNode)->pMasterRoot ==
						pOriginalFibObjectMasterRoot ) {
				//master root elements identical (in same Fib object)
				const unsignedIntFib uiNextLowerNodeFibElementNumber =
					pNextLowerNodeFibElement->getNumberOfElement();
				
				if ( ( uiOrgFibElementNumber < uiNextLowerNodeFibElementNumber ) &&
						( uiNextLowerNodeFibElementNumber <= uiOrgLastFibElementNumber ) ) {
					/*next lower node in Fib object of actual Fib node
					 -> next lower node is node to transfer*/
					liNodesToTransfer.push_back( *itrNextLowerNode );
				}
			}//else next lower node is not a node to transfer
		}//end for all next lower nodes
		
	}//end while there are nodes to transfer
	//no Fib objects for nodes changed
	return true;
}


/**
 * This method returns the mutex for the given Fib node.
 * @see lock( cFibNode * pFibNode )
 * @see unlock( cFibNode * pFibNode )
 * @see tryLock( cFibNode * pFibNode )
 * @see mapFibObjectRootsMutex
 *
 * @param pFibNode a pointer to the node for which to return the mutex
 * @return a pointer to the mutex for the given Fib node, or NULL if non exists
 */
QMutex * cFibNodeHandler::getMutex( cFibNode * pFibNode ) {
	
	if ( pFibNode == NULL ) {
		//no Fib node given -> no mutex
		return NULL;
	}
	cFibElement * pMasterRootForNode = pFibNode->pMasterRoot;
	
	if ( pMasterRootForNode == NULL ) {
		//no master root object for given Fib node -> no mutex
		return NULL;
	}
	
	map< cFibElement * , QMutex * >::iterator itrMutex =
		mapFibObjectRootsMutex.find( pMasterRootForNode );
	
	if ( itrMutex == mapFibObjectRootsMutex.end() ) {
		//master root element don't exists -> create new mutex
		pair< map< cFibElement * , QMutex * >::iterator , bool > paInsertElement =
			mapFibObjectRootsMutex.insert( pair< cFibElement * , QMutex * >(
					pMasterRootForNode, new QMutex() ) );
		
		if ( paInsertElement.second ) {
			return (paInsertElement.first->second);
		}//else no new mutex created -> no mutex
		return NULL;
	}//else mutex found
	return (itrMutex->second);
}


/**
 * This method locks the whole Fib object (the Fib master root object)
 * for the given Fib node. If another thread has locked one of the
 * Fib nodes for Fib objects for the whole Fib object of the given
 * Fib node then this call will block until that thread has unlocked it.
 * @see unlock( cFibNode * pFibNode )
 * @see tryLock( cFibNode * pFibNode )
 * @see mapFibObjectRootsMutex
 * @see QMutex::lock()
 *
 * @param pFibNode the node for which to lock the whole Fib object
 * @return true if the Fib object could be locked (whole Fib object exists)
 */
bool cFibNodeHandler::lock( cFibNode * pFibNode ) {
	
	DEBUG_OUT_L3(<<"cFibNodeHandler("<<this<<")::lock( pFibNode="<<pFibNode<<") called"<<endl<<flush);
	
	QMutex * pMutexForNode = getMutex( pFibNode );
	
	if ( pMutexForNode == NULL ) {
		//no mutex for the node -> can't lock
		DEBUG_OUT_L3(<<"cFibNodeHandler("<<this<<")::lock( pFibNode="<<pFibNode<<") done; no mutex for the node -> can't lock"<<endl<<flush);
		return false;
	}
	pMutexForNode->lock();
	
	DEBUG_OUT_L3(<<"cFibNodeHandler("<<this<<")::lock( pFibNode="<<pFibNode<<") done"<<endl<<flush);
	return true;
}


/**
 * This method attempts to lock the whole Fib object (the Fib master
 * root object) for the given Fib node.
 * This method returns true if the lock was obtained, otherwise it
 * returns false.
 * If another thread has locked one of the Fib object, this method will
 * wait for at most timeout milliseconds for a Fib node to become
 * available.
 * Note: Passing a negative number as the timeout is equivalent to
 * calling lock(), i.e. this method will wait forever until Fib object
 * can be locked if timeout is negative.
 *
 * If the lock was obtained, the Fib object must be unlocked with unlock()
 * before another thread can successfully lock it.
 *
 * @see lock()
 * @see unlock()
 * @see mapFibObjectRootsMutex
 * @see QMutex::tryLock()
 *
 * @param pFibNode the node for which to lock the whole Fib object
 * @param iTimeout the time an milliseconds to wait for a Fib node to
 * 	become available
 * @return true if the lock was obtained, otherwise it returns false
 */
bool cFibNodeHandler::tryLock( cFibNode * pFibNode, int iTimeout ) {
	
	DEBUG_OUT_L3(<<"cFibNodeHandler("<<this<<")::tryLock( pFibNode="<<pFibNode<<") called"<<endl<<flush);
	QMutex * pMutexForNode = getMutex( pFibNode );
	
	if ( pMutexForNode == NULL ) {
		//no mutex for the node -> can't lock
		DEBUG_OUT_L3(<<"cFibNodeHandler("<<this<<")::tryLock( pFibNode="<<pFibNode<<") done; no mutex for the node -> can't lock"<<endl<<flush);
		return false;
	}
	
	return pMutexForNode->tryLock( iTimeout );
}


/**
 * This method unlocks the whole Fib object (the Fib master root object)
 * for the given Fib node.
 * Attempting to unlock a Fib object in a different thread to the one that
 * locked it results in an error. Unlocking a Fib object that is not
 * locked results in undefined behavior.
 *
 * @see lock()
 * @see tryLock( cFibNode * pFibNode )
 * @see mapFibObjectRootsMutex
 * @see QMutex::unlock()
 *
 * @param pFibNode the node for which to unlock the whole Fib object
 * @return true if the Fib object could be unlocked (whole Fib object exists)
 */
bool cFibNodeHandler::unlock( cFibNode * pFibNode ) {
	
	DEBUG_OUT_L3(<<"cFibNodeHandler("<<this<<")::unlock( pFibNode="<<pFibNode<<") called"<<endl<<flush);
	
	QMutex * pMutexForNode = getMutex( pFibNode );
	
	if ( pMutexForNode == NULL ) {
		//no mutex for the node -> can't lock
		DEBUG_OUT_L3(<<"cFibNodeHandler("<<this<<")::unlock( pFibNode="<<pFibNode<<") done; no mutex for the node -> can't lock"<<endl<<flush);
		return false;
	}
	pMutexForNode->unlock();
	
	DEBUG_OUT_L3(<<"cFibNodeHandler("<<this<<")::unlock( pFibNode="<<pFibNode<<") done"<<endl<<flush);
	return true;
}



/**
 * This method returns all superior Fib objects to the given Fib object,
 * in the evaluation order.
 * Normaly a superior Element to a given Fib object is the superior
 * Fib element in all of the root Fib object. But if external objects
 * are used, a superior Fib object to a subroot object are the externel
 * object elements where the subroot object is used.
 *
 * @param pFibObject the Fib object for which to return the superior
 * 	Fib objects
 * @return a list with all superior Fib objects of the given Fib object
 * 	pFibObject
 */
list<cFibElement *> cFibNodeHandler::getSuperiorFibElements(
		cFibElement * pFibObject ) {
	/*TODO? linkt sub roots to there external objects
	 * (what if a external object changes its identifier?)
	 * - implement list<cFibElement *> getSuperiorFibElements( cFibElement)
	 * (to replace pFibObject->getSuperiorFibElement())
	 * which also search for sub roots and mayby loaded database objects
	 * (map< longFib Id, cFibElement * > mapDatabaseObjects )
	 * + if new database object gets loaded
	 * 	-> check existing Fib objects for external objects which use it
	 * + for external subobject go into external object
	 * - how to prevent infinit cycles?
	 * 
	 * - What if database Fib object are used? (link betwean different Root objects)
	 */

	list<cFibElement *> liSuperiorElements;
//TODO
#ifdef SWITCH_SUPERIOR_EVALUED_OBJECT
	const unsigned char ucType = pFibObject->getType();
	
	//TODO
	
	
	switch ( ucType ) {
		case 'r':{//given Fib element is sub root element
			//evalue if object is a sub-root object
			cFibElement * pSuperiorFibElement =
				pFibObject->getSuperiorFibElement();
			if ( pSuperiorFibElement != NULL ) {
				//evalue all external object elements which use the subroot object
				//find the id for the given Fib (subroot) object pFibObject
				//TODO
				
				/*for all root objects below and before (but after sub root
				 * object for same identifer) the Fib (subroot) object pFibObject
				 * -> evalue all external object elements for the identifier
				 */
				
				
			}/*else object is not a sub-root object, but top most root
			-> no superior Fib object exists*/
		}break;
		default:
			cFibElement * pSuperiorFibElement =
				pFibObject->getSuperiorFibElement();
			
			liSuperiorElements.push_back( pFibObject->getSuperiorFibElement() );
			
			if ( pSuperiorFibElement.getType() == 'o' ) {
				//the Fib object pFibObject is a external subobject
				//evalue which (=number) of external subobject in superior external object
				//TODO
				
				//evalue root object for external object
				
			}
			
			
	};//end switch ucType
	
#else //SWITCH_SUPERIOR_EVALUED_OBJECT
	
	liSuperiorElements.push_back( pFibObject->getSuperiorFibElement() );
#endif //SWITCH_SUPERIOR_EVALUED_OBJECT
	return liSuperiorElements;
}


/**
 * This method will delete all Fib nodes without listeners.
 * It will also delete all Fib object roots without nodes for the
 * Fib object root or a contained Fib object.
 * @see mapFibNodes
 * @see setFibObjectsRoot
 */
void cFibNodeHandler::deleteNodesWithoutListeners() {
	DEBUG_OUT_L2(<<"cFibNodeHandler::deleteNodesWithoutListeners() called"<<endl<<flush);
	//set the time when it should be tried to delete not needed nodes the next time
	tmNextDeleteNodesAction = time( NULL ) + TM_DELAY_BETWEAN_DELETE_NODES_ACTION;
	
	mutexFibNodeHandler.lock();
	
	//delete all nodes without a listener
	for ( set< cFibNode * >::iterator itrActualNode = setFibNodes.begin();
			itrActualNode != setFibNodes.end(); itrActualNode++ ) {
		
		//check if node can be deleted
		DEBUG_OUT_L4(<<"cFibNodeHandler::deleteNodesWithoutListeners() checking if node "<<(*itrActualNode)<<" can be deleted"<<endl<<flush);
		if ( (*itrActualNode)->liNodeChangedListeners.empty() ) {
			//node can be deleted
			DEBUG_OUT_L2(<<"cFibNodeHandler::deleteNodesWithoutListeners() node "<<(*itrActualNode)<<" can be deleted"<<endl<<flush);
			cFibNode * pFibNodeToDelete = (*itrActualNode);
			cFibElement * pFibElementForNode = pFibNodeToDelete->pFibObject;
			cFibElement * pFibElementRoot =
				mapFibObjectRoots[ pFibElementForNode ];
			
			//update class members
			DEBUG_OUT_L3(<<"cFibNodeHandler::deleteNodesWithoutListeners() update class members after deleting node "<<(*itrActualNode)<<""<<endl<<flush);
			set< cFibNode * >::iterator itrNextNode = itrActualNode;
			itrNextNode++;
			setFibNodes.erase( itrActualNode );
			itrActualNode = itrNextNode;
			mapFibNodes.erase( pFibElementForNode );
			mapFibObjectRoots.erase( pFibElementForNode );
			
			set< cFibNode * > & setNodesForRoot = mapNodesForRoots[ pFibElementRoot ];
			setNodesForRoot.erase( pFibNodeToDelete );
			//delete the node
			DEBUG_OUT_L3(<<"cFibNodeHandler::deleteNodesWithoutListeners() delete the node "<<pFibNodeToDelete<<endl<<flush);
			delete pFibNodeToDelete;
			
			if ( setNodesForRoot.empty() ) {
				//no Fib node for root object -> delete root object
				DEBUG_OUT_L3(<<"cFibNodeHandler::deleteNodesWithoutListeners() no Fib node ("<<(*itrActualNode)<<") for root object -> erase root object "<<pFibElementRoot<<""<<endl<<flush);
				setFibObjectsRoot.erase( pFibElementRoot );
				mapNodesForRoots.erase( pFibElementRoot );
				
				map< cFibElement * , QMutex * >::iterator itrMutex =
					mapFibObjectRootsMutex.find( pFibElementRoot );
				
				if ( itrMutex != mapFibObjectRootsMutex.end() ) {
					//mutex found -> delete it
					delete (itrMutex->second);
					mapFibObjectRootsMutex.erase( itrMutex );
				}
				
				DEBUG_OUT_L3(<<"cFibNodeHandler::deleteNodesWithoutListeners() delete root object "<<pFibElementRoot<<" (delete Fib object)"<<endl<<flush);
				pFibElementRoot->deleteObject();
			}
		}//end if node can be deleted
	}//end for all existing Fib nodes
	mutexFibNodeHandler.unlock();
}






