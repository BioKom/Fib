
//TODO check

/**
 * @file cFibNode
 * file name: cFibNode.cpp
 * @author Betti Oesterholz
 * @date 11.06.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for Fib object nodes for the Fib creator
 * application.
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
 * This file implements a class for Fib object nodes for the Fib creator
 * application.
 * When you work with the Fib creator on a Fib object it could be a part of
 * a bigger Fib object, this class is for handling this situation.
 * So you can open a Fib object and its parts in more than one window.
 * It stores the Fib element for the Fib node, its top most root element,
 * the next and previous existing Fib nodes (to be notified on changes).
 * You can register for listening if the node (or a Fib element contained
 * in the Fib object of the node) was changed.
 * TODO: (or extra object for: variable list + node = window)
 * It also stores the area / window (cPlainArea) of the Fib object this
 * node represents and the variables the Fib object use, but which aren't
 * defined in it. (These variables are the input parameters for the Fib object.)
 *
 * Normally for every Fib object (@see pFibObject) there should be just one node.
 *
 * TODO:
 * @see cPlainArea (should store the area for the node)
 */
/*
History:
11.06.2013  Oesterholz  created
*/


//TODO switches for test proposes
#define DEBUG


#include "cFibNode.h"

#include "cFibNodeHandler.h"
#include "cFibObjectInfo.h"
#include "cFibObjectSourceFibDb.h"
#include "nFibObjectTools.h"

#include "cExtObject.h"
#include "cList.h"
#include "cFunction.h"
#include "cFunctionValue.h"


using namespace std;
using namespace fib::nCreator;



/**
 * parameter constructor for a Fib object node
 *
 * @param pInFibObject a pointer to the Fib object of the node to constructor
 * 	@see pFibObject
 * @param bInIsChangebel true (standard value) if (the Fib element of)
 * 	the to create node is changebel, else false
 */
cFibNode::cFibNode( cFibElement * pInFibObject, const bool bInIsChangebel ):
		pFibObject( pInFibObject ), bIsChangebel( bInIsChangebel ),
		ulVersion( 1 ), pMasterRoot( NULL ){
	
	if ( pFibObject ){
		//get the master Root object
		pMasterRoot = pFibObject->getMasterRoot();
	}//end if Fib object exists
	//TODO init setNextSuperiorNodes and setNextLowerNodes in the node handler
}



/**
 * copy constructor
 *
 * @param fibNode the Fib node of which to create a copy
 */
cFibNode::cFibNode( cFibNode & fibNode ):pFibObject( fibNode.pFibObject ),
		bIsChangebel( bIsChangebel ), ulVersion( 1 ),
		pMasterRoot( fibNode.pMasterRoot ){
	//nothing to do
}


/**
 * destructor
 */
cFibNode::~cFibNode(){
	
	DEBUG_OUT_L2(<<"cFibNode("<<this<<")::~cFibNode()"<<endl<<flush);
	//send a Fib node deleted event
	increaseFibObjectVersion();
	eFibNodeChangedEvent fibNodeChangedEvent( this, ulVersion, NULL );
	fibNodeChangedEvent.bNodeDeleted = true;
	sendNodeChange( &fibNodeChangedEvent );
	
	/*register all listeners for changes of this object in all next superior
	 Fib object nodes, so they get notyfied if the Fib object for this node changes*/
	DEBUG_OUT_L3(<<"cFibNode("<<this<<")::~cFibNode(): register all listeners for changes of this object in all next superior Fib object nodes"<<endl<<flush);
	for ( set< cFibNode * >::iterator itrSuperiorNode = setNextSuperiorNodes.begin();
			itrSuperiorNode != setNextSuperiorNodes.end(); itrSuperiorNode++ ){
		
		for ( set< lFibNodeChanged * >::iterator
				itrChangeListener = liNodeChangedListeners.begin();
				itrChangeListener != liNodeChangedListeners.end(); itrChangeListener++ ){
			
			(*itrSuperiorNode)->registerNodeChangeListener( (*itrChangeListener) );
		}//end for all change listeners
	}//end for all superior nodes
	
	//add the next superior nodes of this to the next lower nodes of this node
	DEBUG_OUT_L3(<<"cFibNode("<<this<<")::~cFibNode(): add the next superior nodes of this to the next lower nodes of this node"<<endl<<flush);
	for ( set< cFibNode * >::iterator itrLowerNode = setNextLowerNodes.begin();
			itrLowerNode != setNextLowerNodes.end(); itrLowerNode++ ){
		
		(*itrLowerNode)->setNextSuperiorNodes.insert(
			setNextSuperiorNodes.begin(), setNextSuperiorNodes.end() );
		
	}//end for all lower nodes
	
	//add the next lower nodes of this to the next superior nodes of this node
	DEBUG_OUT_L3(<<"cFibNode("<<this<<")::~cFibNode(): add the next lower nodes of this to the next superior nodes of this node"<<endl<<flush);
	for ( set< cFibNode * >::iterator itrSuperiorNode = setNextSuperiorNodes.begin();
			itrSuperiorNode != setNextSuperiorNodes.end(); itrSuperiorNode++ ){
		
		(*itrSuperiorNode)->setNextLowerNodes.insert(
			setNextLowerNodes.begin(), setNextLowerNodes.end() );
		
	}//end for all superior nodes
	
	//remove this node from the superior nodes of the next lower nodes of this node
	DEBUG_OUT_L3(<<"cFibNode("<<this<<")::~cFibNode(): remove this node from the superior nodes of the next lower nodes of this node"<<endl<<flush);
	for ( set< cFibNode * >::iterator itrNextLowerNode = setNextLowerNodes.begin();
			itrNextLowerNode != setNextLowerNodes.end(); itrNextLowerNode++ ){
		
		(*itrNextLowerNode)->setNextSuperiorNodes.erase( this );
		
	}//end for all lower nodes
	
	//remove this node from the lower nodes of the next superior nodes of this node
	DEBUG_OUT_L3(<<"cFibNode("<<this<<")::~cFibNode(): remove this node from the lower nodes of the next superior nodes of this node"<<endl<<flush);
	for ( set< cFibNode * >::iterator itrSuperiorNode = setNextSuperiorNodes.begin();
			itrSuperiorNode != setNextSuperiorNodes.end(); itrSuperiorNode++ ){
		
		(*itrSuperiorNode)->setNextLowerNodes.erase( this );
		
	}//end for all superior nodes
	
	DEBUG_OUT_L2(<<"cFibNode("<<this<<")::~cFibNode() done"<<endl<<flush);
}



/**
 * @return a pointer to the Fib object this node represents or
 * 	NULL if no changebel Fib object can be returned (e.g.
 * 	if the Fib object is not changebel)
 * 	@see pFibObject
 * 	@see bIsChangebel
 */
cFibElement * cFibNode::getFibObject(){
	
	return pFibObject;
}


/**
 * @return a const pointer to the Fib object this node represents
 * 	@see pFibObject
 */
const cFibElement * cFibNode::getFibObjectConst() const{
	
	return pFibObject;
}


/**
 * Call this method if the Fib object for this node changed.
 * @see pFibObject
 * @see liNodeChangedListeners
 * @see ulVersion
 *
 * @param pChangedBy a pointer to the object which had changed the Fib node
 */
bool cFibNode::fibObjectChanged( const QObject * pChangedBy ){
	
	increaseFibObjectVersion();
	const eFibNodeChangedEvent fibNodeChangedEvent( this, ulVersion, pChangedBy );
	
	//TODO in own tread (so it dosn't block)
	sendNodeChange( &fibNodeChangedEvent );
	
	return true;
}


/**
 * Call this method if the Fib object for this node changed.
 * @see pFibObject
 * @see liNodeChangedListeners
 * @see ulVersion
 * @see eFibNodeChangedEvent
 *
 * @param fibNodeChangedEvent the event with the change information
 */
bool cFibNode::fibObjectChanged( const eFibNodeChangedEvent & fibNodeChangedEvent ){
	
	increaseFibObjectVersion();
	
	//TODO in own tread (so it dosn't block)
	sendNodeChange( &fibNodeChangedEvent );
	
	return true;
}


/**
 * @return the version of the Fib object for the node
 * 	Every time the Fib object is changed the version number is counted up.
 * 	@see ulVersion
 */
unsigned long cFibNode::getFibObjectVersion() const{
	
	return ulVersion;
}


/**
 * @return a pointer to the master root object of the Fib object this
 * 	node represents or NULL if no changebel Fib object can be returned
 * 	(e.g. if the Fib object is not changebel)
 * 	@see pMasterRoot
 * 	@see bIsChangebel
 */
cFibElement * cFibNode::getMasterRoot(){
	
	return pMasterRoot;
}


/**
 * @return a const pointer to the master root object of the Fib object
 * 	this node represents
 * 	@see pMasterRoot
 */
const cFibElement * cFibNode::getMasterRootConst() const{
	
	return pMasterRoot;
}


/**
 * @return true if (the Fib element of) this node is changebel, else false
 * 	@see bIsChangebel
 */
bool cFibNode::isChangebel() const{
	
	return bIsChangebel;
}


/**
 * This method inserts the Fib object for the given Fib object info
 * into the Fib object of this Fib object node.
 * It will be tried to insert the given Fib object as a external
 * subobject and a subroot object (if not a same subroot object allready
 * exists).
 *
 * @see cFibElement::insertObjectInElement()
 * @see cExtObject
 * @see cRoot::integrateSubRootObject()
 * @param pFibObjectInfo a pointer to the Fib object info object of
 * 	the Fib object to insert
 * @return true if the Fib object could be inserted, else false
 */
bool cFibNode::insertFibObjectInfo( cFibObjectInfo * pFibObjectInfo ){
	
	DEBUG_OUT_L2(<<"cFibNode("<<this<<")::insertFibObjectInfo( pFibObjectInfo="<<pFibObjectInfo<<" ) started"<<endl<<flush);
	if ( ( ! isChangebel() ) || ( pFibObject == NULL ) ){
		//Fib object for this node not changebel -> can't insert a Fib object in it
		return false;
	}
	if ( pFibObjectInfo == NULL ){
		//no Fib object for the new main window -> return false
		return false;
	}
	cFibNodeHandler * pFibNodeHandler = cFibNodeHandler::getInstance();
	
	if ( pFibNodeHandler ){
		pFibNodeHandler->lock( this );
	}
	
	//try to integrate the Fib object for the Fib object info object
	cExtObject * pExternalSubobjectToInsert = NULL;
	if ( ( pFibObjectInfo->getFibObjectSource() != NULL ) &&
			( pFibObjectInfo->getFibObjectSource()->getName() ==
				"cFibObjectSourceFibDb" ) ){
		DEBUG_OUT_L3(<<"cFibNode("<<this<<")::insertFibObjectInfo( pFibObjectInfo="<<pFibObjectInfo<<" ) using Fib database object"<<endl<<flush);
		
		cFibObjectSourceFibDb * pFibObjectSourceFibDb =
			((cFibObjectSourceFibDb*)(pFibObjectInfo->getFibObjectSource()));
		//if the to integrate Fib object is a database object
		const unsignedIntFib ulNumberOfInputVariables =
			pFibObjectInfo->getNumberOfInputVariables();
		cVectorExtObject vecInInputValues( ulNumberOfInputVariables );
		if ( 0 < ulNumberOfInputVariables ){
			//evalue and set default values for the input variables
			int iOutStatus = 0;
			cFibElement * pLoadedFibObject =
				pFibObjectInfo->loadFibObjectFromSource( &iOutStatus );
			
			if ( ( pLoadedFibObject != NULL ) && ( 0 <= iOutStatus ) &&
					( pLoadedFibObject->getType() == 'r' ) ){
				
				cRoot * pLoadedRootObject = (static_cast<cRoot*>(pLoadedFibObject));
				
				for ( unsignedIntFib uiActualInVar = 1;
						uiActualInVar <= ulNumberOfInputVariables; uiActualInVar++ ){
					vecInInputValues.setValue( uiActualInVar,
						pLoadedRootObject->getStandardValueOfInputVariable( uiActualInVar ) );
				}
			}/*else no Fib object for Fib object info or error while loading
				 * Fib object for Fib object info or not a root element
				 * -> no main window can be created*/
			
		}
		//create external subobject to insert
		pExternalSubobjectToInsert = new cExtObject(
			pFibObjectSourceFibDb->getFibDbIdentifier(), vecInInputValues );
		
	}else if ( 2 < pFibObjectInfo->getNumberOfFibElements() ){
		/*else the to integrate Fib object is not a database object
		 and if the Fib object for the info object contains more than a root
		 element and a other Fib element*/
		DEBUG_OUT_L3(<<"cFibNode("<<this<<")::insertFibObjectInfo( pFibObjectInfo="<<pFibObjectInfo<<" ) using not a Fib database object"<<endl<<flush);
		int iOutStatus = 0;
		cFibElement * pLoadedFibObject =
			pFibObjectInfo->loadFibObjectFromSource( &iOutStatus );
		
		if ( ( pLoadedFibObject == NULL ) || ( iOutStatus < 0 ) ){
			/* no Fib object for Fib object info or error while loading
			 * Fib object for Fib object info
			 * -> no main window can be created*/
			if ( pFibNodeHandler ){
				pFibNodeHandler->unlock( this );
			}
			return false;
		}
		//the root element where to integrate the loaded Fib object
		cRoot * pNextSuperiorRoot = ( pFibObject->getType() == 'r' ) ?
			(static_cast<cRoot*>(pFibObject)) :
			pFibObject->getSuperiorRootElement();
		
		if ( pNextSuperiorRoot != NULL ){
			//more than root and one Fib element in the to integrate Fib object
			//try to integrate Fib (root) object in next superior root element
			const longFib lIdentifier = pNextSuperiorRoot->integrateSubRootObject(
				pLoadedFibObject );
			
			if ( lIdentifier != 0 ){
				/*the Fib object could be inserted as a subroot object
				 -> create external subobject for it*/
				//if the to integrate Fib object is a database object
				cRoot * pSubRoot =
					pNextSuperiorRoot->getAccessibleRootObject( lIdentifier );
				const unsignedIntFib ulNumberOfInputVariables =
					pSubRoot->getNumberOfInputVariables();
				cVectorExtObject vecInInputValues( ulNumberOfInputVariables );
				if ( 0 < ulNumberOfInputVariables ){
					//evalue and set default values for the input variables
					for ( unsignedIntFib uiActualInVar = 1;
							uiActualInVar <= ulNumberOfInputVariables; uiActualInVar++ ){
						vecInInputValues.setValue( uiActualInVar,
							pSubRoot->getStandardValueOfInputVariable( uiActualInVar ) );
					}
				}//end if input variables exists
				//create external subobject to insert
				pExternalSubobjectToInsert = new cExtObject(
					lIdentifier, vecInInputValues );
			}
		}
	}//end if Fib database object
	DEBUG_OUT_L3(<<"cFibNode("<<this<<")::insertFibObjectInfo( pFibObjectInfo="<<pFibObjectInfo<<" ) integrating Fib object of info (pExternalSubobjectToInsert="<<pExternalSubobjectToInsert<<")"<<endl<<flush);
	cFibElement * pFibObjectToInsert = pExternalSubobjectToInsert;
	if ( pFibObjectToInsert == NULL ){
		//insert Fib object directly
		int iOutStatus = 0;
		cFibElement * pLoadedFibObject =
			pFibObjectInfo->loadFibObjectFromSource( &iOutStatus );
		
		if ( ( pLoadedFibObject == NULL ) || ( iOutStatus < 0 ) ){
			/* no Fib object for Fib object info or error while loading
			 * Fib object for Fib object info
			 * -> no main window can be created*/
			if ( pFibNodeHandler ){
				pFibNodeHandler->unlock( this );
			}
			return false;
		}
		const list< cFibVariable * > liInputvariables =
			nFibObjectTools::evalueInputVariables( pLoadedFibObject );
		
		pFibObjectToInsert = pLoadedFibObject->clone();
		//define every input variable (create a function element with value 0 for it)
		cFunctionValue subFunValueNull( 0.0 );
		for ( list< cFibVariable * >::const_reverse_iterator
				itrActualVariable = liInputvariables.rbegin();
				itrActualVariable != liInputvariables.rend(); itrActualVariable++ ){
			
			cFunction * pNewFunction = new cFunction( subFunValueNull,
				pFibObjectToInsert );
			
			pFibObjectToInsert->replaceVariable( *itrActualVariable,
				pNewFunction->getDefinedVariable() );
			
			pFibObjectToInsert = pNewFunction;
		}
	}//else insert the created external object into the Fib object of this node
	
	const bool bExtObjectInserted = pFibObject->insertObjectInElement(
		pFibObjectToInsert, 'u', 0, false );
	if ( ! bExtObjectInserted ){
		//external object could not be inserted -> delete it
		if ( pFibNodeHandler ){
			pFibNodeHandler->unlock( this );
		}
		pExternalSubobjectToInsert->deleteObject();
		return false;
	}
	if ( pFibNodeHandler ){
		pFibNodeHandler->unlock( this );
	}
	fibObjectChanged();
	DEBUG_OUT_L2(<<"cFibNode("<<this<<")::insertFibObjectInfo( pFibObjectInfo="<<pFibObjectInfo<<" ) done insert OK"<<endl<<flush);
	return true;
}


/**
 * With this function you can register a listeners for changes in the
 * Fib object for this node.
 *
 * @see fibObjectChanged()
 * @see unregisterNodeChangeListener()
 * @see liNodeChangedListeners
 * @see sendNodeChange()
 * @param pNodeListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibNode::registerNodeChangeListener( lFibNodeChanged * pNodeListener ){
	
	if ( pNodeListener == NULL ){
		//nothing to register
		return false;
	}
	const pair< set< lFibNodeChanged * >::iterator, bool > paListenerInserted =
		liNodeChangedListeners.insert( pNodeListener );
	return paListenerInserted.second;
}


/**
 * With this function you can unregister a listeners for changes in the
 * Fib object for this node.
 *
 * @see fibObjectChanged()
 * @see registerNodeChangeListener()
 * @see liNodeChangedListeners
 * @see sendNodeChange()
 * @param pNodeListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibNode::unregisterNodeChangeListener( lFibNodeChanged * pNodeListener ){
	
	return ( 0 < liNodeChangedListeners.erase( pNodeListener ) );
}


/**
 * This method will increase the Fib object version number for all
 * Fib nodes for superior Fib objects. (The supperior Fib node
 * Fib object has to contain this Fib node Fib object.)
 * @see ulVersion
 * @see fibObjectChanged()
 */
void cFibNode::increaseFibObjectVersion(){
	//increase this Fib node version number
	ulVersion++;
	
	//send node change to all superior nodes
	for ( set< cFibNode * >::iterator itrSuperiorNode = setNextSuperiorNodes.begin();
			itrSuperiorNode != setNextSuperiorNodes.end(); itrSuperiorNode++ ){
		
		if ( (*itrSuperiorNode)->pMasterRoot == pMasterRoot ){
			//node is for the same whole Fib object -> increase Version number
			(*itrSuperiorNode)->increaseFibObjectVersion();
		}
	}//end for all superior nodes
}


/**
 * This method sents a node changed event to all change node listeners
 * of this object.
 *
 * @see liNodeChangedListeners
 * @see setNextSuperiorNodes
 * @see fibObjectChanged()
 * @param pFibNodeChangedEvent the change event to send
 */
void cFibNode::sendNodeChange( const eFibNodeChangedEvent * pFibNodeChangedEvent ){
	
	for ( set< lFibNodeChanged * >::iterator
			itrChangeListener = liNodeChangedListeners.begin();
			itrChangeListener != liNodeChangedListeners.end(); itrChangeListener++ ){
		
		(*itrChangeListener)->fibNodeChangedEvent( pFibNodeChangedEvent );
	}
	//send node change to all superior nodes
	for ( set< cFibNode * >::iterator itrSuperiorNode = setNextSuperiorNodes.begin();
			itrSuperiorNode != setNextSuperiorNodes.end(); itrSuperiorNode++ ){
		
		(*itrSuperiorNode)->sendNodeChange( pFibNodeChangedEvent );
	}//end for all superior nodes
}




