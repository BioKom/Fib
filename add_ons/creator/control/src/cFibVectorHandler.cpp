
//TODO check

/**
 * @file cFibVectorHandler
 * file name: cFibVectorHandler.cpp
 * @author Betti Oesterholz
 * @date 28.11.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for handling Fib vectors for the
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
 * This file implements a class for handling Fib vectors for the
 * Fib creator application.
 *
 * @pattern singelton
 * @see cFibVectorCreator
 * @see fib::cFibVector
 */
/*
History:
28.11.2013  Oesterholz  created
*/


#include "cFibVectorHandler.h"

#include <list>

#include "cFibVector.h"

#include "cFibVectorCreator.h"
#include "cFibNode.h"
#include "cFibNodeHandler.h"


using namespace std;
using namespace fib::nCreator;



/**
 * A pointer to the Fib vector handler object.
 */
cFibVectorHandler * cFibVectorHandler::pFibVectorHandler = NULL;


/**
 * The constructor for the Fib vector handler.
 */
cFibVectorHandler::cFibVectorHandler(){
	
	DEBUG_OUT_L2(<<"cFibVectorHandler("<<this<<")::cFibVectorHandler() called"<<endl<<flush);
	pFibVectorHandler = this;
	
	mapVectorCounters[ 'u' ] = 1;
	mapVectorCounters[ 'r' ] = 1;
	mapVectorCounters[ 'f' ] = 1;
	mapVectorCounters[ 'a' ] = 1;
	mapVectorCounters[ 's' ] = 1;
	mapVectorCounters[ 'm' ] = 1;
	mapVectorCounters[ 'o' ] = 1;
}


/**
 * The destructor of this class.
 */
cFibVectorHandler::~cFibVectorHandler(){
	
	DEBUG_OUT_L2(<<"cFibVectorHandler("<<this<<")::~cFibVectorHandler() called"<<endl<<flush);
	//delete all vector
	while ( true ){
		/*delete sends delete event
		-> which calls fibVectorChangedEvent()
		-> which removes the pointer from the vector containers (including
		   this)*/
		mutexFibVectorHandler.lock();
		if ( setFibVectors.empty() ){
			//no more input variables to delete
			mutexFibVectorHandler.unlock();
			break;
		}
		cFibVectorCreator * pVectorToDelete = (*setFibVectors.begin());
		mutexFibVectorHandler.unlock();
		delete pVectorToDelete;
	}
}


/**
 * @return a instance of the Fib vector handler
 */
cFibVectorHandler * cFibVectorHandler::getInstance(){
	
	DEBUG_OUT_L2(<<"cFibVectorHandler::getInstance() static called"<<endl<<flush);
	if ( pFibVectorHandler == NULL ){
		//create a new instance
		pFibVectorHandler = new cFibVectorHandler();
	}//else return existing instance
	DEBUG_OUT_L2(<<"cFibVectorHandler::getInstance() static done instance="<<pFibVectorHandler<<endl<<flush);
	return pFibVectorHandler;
}


/**
 * @return the name of this class "cFibVectorHandler"
 */
std::string cFibVectorHandler::getName() const{
	
	return std::string("cFibVectorHandler");
}


/**
 * This method returns the Fib creator vector for the given Fib vector.
 * If no Fib creator vector exists till now one is created.
 * Beware: Input scalars which defining Fib element is deleted will
 * 	be also deleted.
 *
 * @see mapFibVectors
 * @param pFibVector the Fib vector for the Fib creator vector to return
 * @param pListenerVectorChanged a listener for the changes in
 * 	the vector or NULL
 * @return the Fib creator vector for the given Fib vector, or NULL if
 * 	non could be evalued
 */
cFibVectorCreator * cFibVectorHandler::getFibVectorForFibVector(
		fib::cFibVector * pFibVector,
		lFibVectorChanged * pListenerVectorChanged ){

	DEBUG_OUT_L2(<<"cFibVectorHandler("<<this<<")::getFibVectorForFibVector( pFibVector="<<pFibVector<<", pListenerVectorChanged="<<pListenerVectorChanged<<" ) called"<<endl<<flush);
	if ( pFibVector == NULL ){
		//no Fib variable given -> no input variable possible
		return NULL;
	}
	//check if the input variable for Fib variable exists allready
	mutexFibVectorHandler.lock();
	map< fib::cFibVector * , cFibVectorCreator * >::iterator
		itrFoundVector = mapFibVectors.find( pFibVector );
	if ( itrFoundVector != mapFibVectors.end() ){
		//vector for Fib vector found -> return it
		cFibVectorCreator * pFoundVector = itrFoundVector->second;
		if ( pListenerVectorChanged ){
			//add given change listener for vector
			pFoundVector->registerFibVectorChangeListener(
				pListenerVectorChanged );
		}
		mutexFibVectorHandler.unlock();
		DEBUG_OUT_L2(<<"cFibVectorHandler("<<this<<")::getFibVectorForFibVector( pFibVector="<<pFibVector<<", pListenerVectorChanged="<<pListenerVectorChanged<<" ) done return existing input variable "<<pFoundVector<<endl<<flush);
		return pFoundVector;
	}//input variable for Fib variable don't exists -> create one
	
	cFibVectorCreator * pNewVector = new cFibVectorCreator( pFibVector );
	
	if ( pListenerVectorChanged ){
		//add given change listener for vector
		pNewVector->registerFibVectorChangeListener(
			pListenerVectorChanged );
	}
	//update class members
	setFibVectors.insert( pNewVector );
	mapFibVectors.insert( pair< fib::cFibVector * , cFibVectorCreator * >(
		pFibVector, pNewVector ) );
	
	cFibElement * pDefiningFibElement = pFibVector->getDefiningFibElement();
	if ( pDefiningFibElement ){
		//defining Fib object exists
		cFibElement * pMasterRootFibObject = pDefiningFibElement->getMasterRoot();
		cFibNode * pMasterNode = cFibNodeHandler::getInstance()->getNodeForFibObject(
			pMasterRootFibObject, this );
		mapVectorsForNodes[ pMasterNode ].insert( pNewVector );
	}
	
	mutexFibVectorHandler.unlock();
	
	DEBUG_OUT_L2(<<"cFibVectorHandler("<<this<<")::getFibVectorForFibVector( pFibVector="<<pFibVector<<", pListenerVectorChanged="<<pListenerVectorChanged<<" ) done return new vector "<<pNewVector<<endl<<flush);
	
	return pNewVector;
}


/**
 * This method checks if the given pointer points to an in this handler
 * existing Fib creator vector.
 *
 * @param pFibVector a pointer to the Fib creator vector to check
 * @return true if the given Fib creator vector points to an existing
 * 	Fib creator vector in this handler, else false
 */
bool cFibVectorHandler::isValidVector( cFibVectorCreator * pFibVector ){
	
	if ( setFibVectors.find( pFibVector ) == setFibVectors.end() ){
		//vector not found -> not valid vector
		return false;
	}//vector found -> valid vector
	return true;
}


/**
 * Event method
 * It will be called every time a Fib node (cFibNode), at which
 * this object is registered, was changed.
 *
 * @param pFibNodeChanged a pointer to the event, with the information
 * 	about the changed Fib node
 */
void cFibVectorHandler::fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged ){
	
	DEBUG_OUT_L2(<<"cFibVectorHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) called"<<endl<<flush);
	
	if ( ( pFibNodeChanged == NULL ) ||
			( pFibNodeChanged->pFibNodeChanged == NULL ) ){
		//no node changed
		DEBUG_OUT_L2(<<"cFibVectorHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) done no node changed"<<endl<<flush);
		return;
	}
	//evalue the vectors for the node
	mutexFibVectorHandler.lock();
	cFibNode * pChangedFibNode =
		const_cast< cFibNode* >( pFibNodeChanged->pFibNodeChanged );
	map< cFibNode * , set< cFibVectorCreator * > >::const_iterator
		itrVectorsForNode = mapVectorsForNodes.find( pChangedFibNode );
	if ( itrVectorsForNode == mapVectorsForNodes.end() ){
		//Fib node not found
		mutexFibVectorHandler.unlock();
		DEBUG_OUT_L2(<<"cFibVectorHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) done Fib node not found"<<endl<<flush);
		return;
	}
	set< cFibVectorCreator * > setVectorForNode = itrVectorsForNode->second;
	
	if ( pFibNodeChanged->bNodeDeleted ){
		//if node got deleted -> delete all its vectors
		mutexFibVectorHandler.unlock();
		
		DEBUG_OUT_L2(<<"cFibVectorHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) if node got deleted -> delete all "<<setVectorForNode.size()<<" variables for it"<<endl<<flush);
		//delete vectors for the node
		for ( set< cFibVectorCreator * >::iterator
				itrVector = setVectorForNode.begin();
				itrVector != setVectorForNode.end(); itrVector++ ){
			
			delete (*itrVector);
		}
		DEBUG_OUT_L2(<<"cFibVectorHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) done if node got deleted"<<endl<<flush);
		return;
	}
	
	//check if all vectors for the node still exists
	cFibNodeHandler * pFibNodeHandler = cFibNodeHandler::getInstance();
	if ( ( pChangedFibNode->getFibObjectConst() == NULL ) ||
			( ! pFibNodeHandler->lock( pChangedFibNode ) ) ){
		//node don't exists anymore -> delete all variables for it
		pFibNodeHandler->unlock( pChangedFibNode );
		
		DEBUG_OUT_L2(<<"cFibVectorHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) node don't exists anymore -> delete all "<<setVectorForNode.size()<<" variables for it"<<endl<<flush);
		for ( set< cFibVectorCreator * >::iterator
				itrVector = setVectorForNode.begin();
				itrVector != setVectorForNode.end(); itrVector++ ){
			
			delete (*itrVector);
		}
		DEBUG_OUT_L2(<<"cFibVectorHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) done node don't exists anymore"<<endl<<flush);
		return;
	}
	//get all defining Fib element for the Fib vectors
	map< cFibElement*, cFibVectorCreator * > mapDefiningFibElements;
	list< cFibVectorCreator * > liVectorsToDelete;
	
	for ( set< cFibVectorCreator * >::iterator
			itrVector = setVectorForNode.begin();
			itrVector != setVectorForNode.end(); itrVector++ ){
		
		cFibElement * pDefiningFibElement = (*itrVector)->getFibElement();
		if ( pDefiningFibElement ){
			mapDefiningFibElements.insert(
				pair< cFibElement*, cFibVectorCreator * >(
					pDefiningFibElement, (*itrVector) ) );
		}else{//no defining Fib element exists -> delete vector
			liVectorsToDelete.push_back( *itrVector );
		}
	}
	//evaluate all Fib elements no more in the Fib object to the Fib node
	cFibElement * pActualFibElement = pChangedFibNode->getFibObject();
	unsignedIntFib uiElementsToCheck = pActualFibElement->getNumberOfElements();
	for ( ; ( pActualFibElement != NULL ) && ( 0 < uiElementsToCheck );
			pActualFibElement = pActualFibElement->getNextFibElement(),
			uiElementsToCheck-- ){
		
		mapDefiningFibElements.erase( pActualFibElement );
	}
	
	/*mapDefiningFibElements contains all Fib elements not in the Fib node
	 -> delete them*/
	for ( map< cFibElement*, cFibVectorCreator * >::iterator
			itrActualVector = mapDefiningFibElements.begin();
			itrActualVector != mapDefiningFibElements.end(); itrActualVector++ ){
		
		liVectorsToDelete.push_back( itrActualVector->second );
	}
	
	pFibNodeHandler->unlock( pChangedFibNode );
	mutexFibVectorHandler.unlock();
	
	//delete all not used vectors
	DEBUG_OUT_L2(<<"cFibVectorHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) delete all "<<liVectorsToDelete.size()<<" not used vectors"<<endl<<flush);
	for ( list< cFibVectorCreator * >::iterator
			itrVector = liVectorsToDelete.begin();
			itrVector != liVectorsToDelete.end(); itrVector++ ){
		
		delete (*itrVector);
	}
	
	DEBUG_OUT_L2(<<"cFibVectorHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) done"<<endl<<flush);
}



/**
 * This method removes the given vector from this handler.
 * cFibVector should call it on destruction.
 *
 * @see cFibVectorCreator::cFibVectorCreator()
 * @param pFibVector a pointer to the vector to remove
 * @return true if the vector was removed, else false (the vector didn't
 * 	exists in this handler)
 */
bool cFibVectorHandler::removeVector( cFibVectorCreator * pFibVector ){
	
	if ( pFibVector == NULL ){
		//nothing to remove
		return false;
	}
	//update class members
	mutexFibVectorHandler.lock();
	
	const bool bVectorRemoved = ( 0 < setFibVectors.erase( pFibVector ) );
	
	for ( std::map< fib::cFibVector * , cFibVectorCreator * >::iterator
			itrActualVector = mapFibVectors.begin();
			itrActualVector != mapFibVectors.end(); ){
		
		if ( itrActualVector->second == pFibVector ){
			//vector found -> remove it
			std::map< fib::cFibVector * , cFibVectorCreator * >::iterator
				itrNextVector = itrActualVector;
			itrNextVector++;
			mapFibVectors.erase( itrActualVector );
			
			itrActualVector = itrNextVector;
		}else{//check next vector
			itrActualVector++;
		}
		
	}
	for ( std::map< cFibNode * , std::set< cFibVectorCreator * > >::iterator
			itrActualVector = mapVectorsForNodes.begin();
			itrActualVector != mapVectorsForNodes.end(); ){
		
		itrActualVector->second.erase( pFibVector );
		if ( itrActualVector->second.empty() ){
			//no more vectors for the Fib node -> remove it
			std::map< cFibNode * , std::set< cFibVectorCreator * > >::iterator
				itrNextVector = itrActualVector;
			itrNextVector++;
			mapVectorsForNodes.erase( itrActualVector );
			
			itrActualVector = itrNextVector;
		}else{//check next vector
			itrActualVector++;
		}
	}
	
	mutexFibVectorHandler.unlock();
	return bVectorRemoved;
}







