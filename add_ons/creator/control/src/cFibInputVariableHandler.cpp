
//TODO check

/**
 * @file cFibInputVariableHandler
 * file name: cFibInputVariableHandler.cpp
 * @author Betti Oesterholz
 * @date 25.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for handling Fib input variables for the
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
 * This file implements a class for handling Fib input variables for the
 * Fib creator application.
 * If you have a Fib object, the input variables of it are root object
 * input variables or variables used in the Fib object but not defined in it.
 * With this class you can handle these.
 *
 * @pattern singelton
 * @see cFibInputVariable
 * @see cFibInputVariables
 */
/*
History:
25.08.2013  Oesterholz  created
*/


//TODO switches for test proposes
#define DEBUG


#include "cFibInputVariableHandler.h"

#include "cFibNodeHandler.h"

#include "cFibElement.h"
#include "cRoot.h"
#include "cTypeInVar.h"

#include <QObject>


using namespace std;


using namespace fib::nCreator;
using namespace fib;


/**
 * A pointer to the input variable handler object.
 */
cFibInputVariableHandler *
	cFibInputVariableHandler::pFibInputVariableHandler = NULL;

/**
 * constructor for the Fib input variable handler
 */
cFibInputVariableHandler::cFibInputVariableHandler(){
	
	DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::cFibInputVariableHandler() called"<<endl<<flush);
	pFibInputVariableHandler = this;
	
	mapVariableCounters[ 'u' ] = 1;
	mapVariableCounters[ 'r' ] = 1;
	mapVariableCounters[ 'f' ] = 1;
	mapVariableCounters[ 'a' ] = 1;
	mapVariableCounters[ 's' ] = 1;
	mapVariableCounters[ 'm' ] = 1;
	mapVariableCounters[ 'o' ] = 1;
}


/**
 * destructor
 */
cFibInputVariableHandler::~cFibInputVariableHandler(){
	
	DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::~cFibInputVariableHandler() called"<<endl<<flush);
	//delete all input variables
	while ( ! setFibInputVariables.empty() ){
		/*delete sends delete event
		-> which calls fibInputVariableChangedEvent()
		-> which removes the pointer from the input variable containers*/
		mutexFibInputVariableHandler.lock();
		cFibInputVariable * pInputVariableToDelete =
			(*setFibInputVariables.begin());
		mutexFibInputVariableHandler.unlock();
		delete pInputVariableToDelete;
	}
}


/**
 * @return a instance of the Fib input variable handler
 */
cFibInputVariableHandler * cFibInputVariableHandler::getInstance(){
	
	DEBUG_OUT_L2(<<"cFibInputVariableHandler::getInstance() static called"<<endl<<flush);
	if ( pFibInputVariableHandler == NULL ){
		//create a new instance
		pFibInputVariableHandler = new cFibInputVariableHandler();
	}//else return existing instance
	DEBUG_OUT_L2(<<"cFibInputVariableHandler::getInstance() static done instance="<<pFibInputVariableHandler<<endl<<flush);
	return pFibInputVariableHandler;
}


/**
 * @return the name of this class "cFibInputVariableHandler"
 */
std::string cFibInputVariableHandler::getName() const{
	
	return std::string("cFibInputVariableHandler");
}


/**
 * This method returns the Fib input variable for the given Fib variable.
 * If no Fib input variable exists till now one is created.
 * Beware: Input variables which defining Fib element is deleted will
 * 	be also deleted.
 *
 * @see mapFibInputVariables
 * @param pFibVariable the Fib variable for the Fib input variable to return
 * @param pListenerInputVariableChanged a listener for the changes in
 * 	the input variable or NULL
 * @return the Fib input variable for the given Fib variable, or NULL if
 * 	non could be evalued
 */
cFibInputVariable * cFibInputVariableHandler::getFibInputVariableForFibVariable(
		cFibVariable * pFibVariable,
		lInputVariableChanged * pListenerInputVariableChanged ){
	DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::getFibInputVariableForFibVariable( pFibVariable="<<pFibVariable<<", pListenerInputVariableChanged="<<pListenerInputVariableChanged<<" ) called"<<endl<<flush);
	if ( pFibVariable == NULL ){
		//no Fib variable given -> no input variable possible
		return NULL;
	}
	
	//check if the input variable for Fib variable exists allready
	mutexFibInputVariableHandler.lock();
	map< cFibVariable * , cFibInputVariable * >::iterator
		itrFoundInputVariable = mapFibInputVariables.find( pFibVariable );
	if ( itrFoundInputVariable != mapFibInputVariables.end() ){
		//input variable for Fib variable found -> return it
		cFibInputVariable * pFoundInVar = itrFoundInputVariable->second;
		if ( pListenerInputVariableChanged ){
			//add given change listener for input variable
			pFoundInVar->registerInputVariableChangeListener(
				pListenerInputVariableChanged );
		}
		mutexFibInputVariableHandler.unlock();
		DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::getFibInputVariableForFibVariable( pFibVariable="<<pFibVariable<<", pListenerInputVariableChanged="<<pListenerInputVariableChanged<<" ) done return existing input variable "<<pFoundInVar<<endl<<flush);
		return pFoundInVar;
	}//input variable for Fib variable don't exists -> create one
	cFibInputVariable * pNewInVar = new cFibInputVariable( pFibVariable );
	
	//get the master root object Fib node for the input variable
	cFibNode * pMasterNode = NULL;
	cFibElement * pDefiningFibElement = pFibVariable->getDefiningElement();
	if ( pDefiningFibElement ){
		//defining Fib object exists
		cFibElement * pMasterRootFibObject = pDefiningFibElement->getMasterRoot();
		pMasterNode = cFibNodeHandler::getInstance()->getNodeForFibObject(
			pMasterRootFibObject, this );
		
		//choose name depending on defining Fib element type (e.g. funVar4 )
		const char cTypeDefFibElement = pDefiningFibElement->getType();
		unsigned int & uiNextFreeNumber = mapVariableCounters[ 'u' ];
		//the string for the variable number
		QString strNumber;
		//TODO for subelements (with help of creator Fib elements):
			//TODO try to evalue a good domain (don't use domain for the Fib element)
			//TODO if domain exists -> set null value of domain as input variable value
		
		switch ( cTypeDefFibElement ){
			case 'r':{
				uiNextFreeNumber = mapVariableCounters[ cTypeDefFibElement ];
				strNumber.setNum( uiNextFreeNumber );
				pNewInVar->setVariableName(
					QString( QObject::tr("inVar", "input variable prefix for root input variable") ) +
						strNumber );
				
				//use input variable domain
				cRoot * pDefiningRootElement = ((cRoot *)pDefiningFibElement);
				//evalue the number of the input variable in the root element
				const list<cFibVariable*> liRootInputVariables =
					pDefiningRootElement->getInputVariables();
				//position of input in root element input variables
				unsignedIntFib uiActualInputVariable = 1;
				list<cFibVariable*>::const_iterator
					itrActualRootInVar = liRootInputVariables.begin();
				//find position of input in root element input variables
				for ( ; ( itrActualRootInVar != liRootInputVariables.end() ) &&
						( (*itrActualRootInVar) != pFibVariable );
						itrActualRootInVar++, uiActualInputVariable++ ){
				}
				if ( itrActualRootInVar != liRootInputVariables.end() ){
					//input variable found in root element
					const cTypeInVar typeInVar( uiActualInputVariable );
					
					cDomain * pInVarDomain = pDefiningRootElement->getDomains()->
						getDomainForElement( typeInVar );
					if ( ( pInVarDomain == NULL ) || ( ! pInVarDomain->isScalar() ) ){
						//no good domain in normal domains -> try to use value domains
						pInVarDomain = pDefiningRootElement->getValueDomains()->
							getDomainForElement( typeInVar );
					}
					if ( ( pInVarDomain != NULL ) && ( pInVarDomain->isScalar() ) ){
						//good domain found -> set it (/clone) for the input variable
						pNewInVar->setDomain( ((cDomainSingle *)(
							pInVarDomain->clone() )) );
					}
					/*set the value for the input variable to the standard value
					 of the root input variable*/
					pNewInVar->setValue( pDefiningRootElement->
						getStandardValueOfInputVariable( uiActualInputVariable ) );
				}
			};break;
			case 'f':{
				uiNextFreeNumber = mapVariableCounters[ cTypeDefFibElement ];
				strNumber.setNum( uiNextFreeNumber );
				pNewInVar->setVariableName(
					QString( QObject::tr("funVar", "input variable prefix for function variable") ) +
						strNumber );
			};break;
			case 'a':{
				uiNextFreeNumber = mapVariableCounters[ cTypeDefFibElement ];
				strNumber.setNum( uiNextFreeNumber );
				pNewInVar->setVariableName(
					QString( QObject::tr("areaVar", "input variable prefix for area variable") ) +
						strNumber );
			};break;
			case 's':{
				uiNextFreeNumber = mapVariableCounters[ cTypeDefFibElement ];
				strNumber.setNum( uiNextFreeNumber );
				pNewInVar->setVariableName(
					QString( QObject::tr("setVar", "input variable prefix for set element variable") ) +
						strNumber );
			};break;
			case 'm':{
				uiNextFreeNumber = mapVariableCounters[ cTypeDefFibElement ];
				strNumber.setNum( uiNextFreeNumber );
				pNewInVar->setVariableName(
					QString( QObject::tr("matrixVar", "input variable prefix for matrix element variable") ) +
						strNumber );
			};break;
			case 'o':{
				uiNextFreeNumber = mapVariableCounters[ cTypeDefFibElement ];
				strNumber.setNum( uiNextFreeNumber );
				pNewInVar->setVariableName(
					QString( QObject::tr("subObjVar", "input variable prefix for external subobject variable") ) +
						strNumber );
			};break;
			default:{
				strNumber.setNum( uiNextFreeNumber );
				pNewInVar->setVariableName(
					QString( QObject::tr("var", "input variable prefix") ) +
						strNumber );
			};break;
		};
		uiNextFreeNumber++;
		
	}else{
		//create dummy name
		//choose name for the variable
		unsigned int & uiNextFreeNumber = mapVariableCounters[ 'u' ];
		//the string for the variable number
		QString strNumber;
		strNumber.setNum( uiNextFreeNumber );
		pNewInVar->setVariableName(
			QString( QObject::tr("var", "input variable prefix") ) +
				strNumber );
		uiNextFreeNumber++;
	}
	
	
	if ( pListenerInputVariableChanged ){
		//add given change listener for input variable
		pNewInVar->registerInputVariableChangeListener(
			pListenerInputVariableChanged );
	}
	//update class members
	setFibInputVariables.insert( pNewInVar );
	mapFibInputVariables.insert( pair< cFibVariable * , cFibInputVariable * >(
		pFibVariable, pNewInVar ) );
	mapInputVariablesForNodes[ pMasterNode ].insert( pNewInVar );
	
	mutexFibInputVariableHandler.unlock();
	
	DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::getFibInputVariableForFibVariable( pFibVariable="<<pFibVariable<<", pListenerInputVariableChanged="<<pListenerInputVariableChanged<<" ) done return new input variable "<<pNewInVar<<endl<<flush);
	return pNewInVar;
}


/**
 * This method checks if the given pointer points to a in this handler
 * existing Fib input variable.
 *
 * @param pFibInputVariable a pointer to the Fib input variable to check
 * @return true if the given Fib input variable points to an existing
 * 	Fib input variable in this handler, else false
 */
bool cFibInputVariableHandler::isValidInputVariable(
		cFibInputVariable * pFibInputVariable ){
	
	if ( setFibInputVariables.find( pFibInputVariable ) ==
			setFibInputVariables.end() ){
		//input variable not found -> not valid input variable
		return false;
	}//input variable found -> valid input variable
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
void cFibInputVariableHandler::fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged ){
	
	DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) called"<<endl<<flush);
	
	if ( ( pFibNodeChanged == NULL ) ||
			( pFibNodeChanged->pFibNodeChanged == NULL ) ){
		//no node changed
		DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) done no node changed"<<endl<<flush);
		return;
	}
	//evalue the input variables for the node
	mutexFibInputVariableHandler.lock();
	cFibNode * pChangedFibNode =
		const_cast< cFibNode* >( pFibNodeChanged->pFibNodeChanged );
	map< cFibNode * , set< cFibInputVariable * > >::const_iterator
		itrInVarsForNode = mapInputVariablesForNodes.find( pChangedFibNode );
	if ( itrInVarsForNode == mapInputVariablesForNodes.end() ){
		//Fib node not found
		mutexFibInputVariableHandler.unlock();
		DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) done Fib node not found"<<endl<<flush);
		return;
	}
	set< cFibInputVariable * > setInputVariableForNode =
		itrInVarsForNode->second;
		
	if ( pFibNodeChanged->bNodeDeleted ){
		//if node got deleted -> delete all its input variables
		mutexFibInputVariableHandler.unlock();
		
		DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) if node got deleted -> delete all "<<setInputVariableForNode.size()<<" variables for it"<<endl<<flush);
		for ( set< cFibInputVariable * >::iterator
				itrInVar = setInputVariableForNode.begin();
				itrInVar != setInputVariableForNode.end(); itrInVar++ ){
			//TODO: can't do this variable could get deleted before
			delete (*itrInVar);
		}
		DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) done if node got deleted"<<endl<<flush);
		return;
	}
	
	//check if all input variables for the node still exists
	cFibNodeHandler * pFibNodeHandler = cFibNodeHandler::getInstance();
	if ( ( pChangedFibNode->getFibObjectConst() == NULL ) ||
			( ! pFibNodeHandler->lock( pChangedFibNode ) ) ){
		//node don't exists anymore -> delete all variables for it
		pFibNodeHandler->unlock( pChangedFibNode );
		
		DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) node don't exists anymore -> delete all "<<setInputVariableForNode.size()<<" variables for it"<<endl<<flush);
		for ( set< cFibInputVariable * >::iterator
				itrInVar = setInputVariableForNode.begin();
				itrInVar != setInputVariableForNode.end(); itrInVar++ ){
			//TODO: can't do this variable could get deleted before
			delete (*itrInVar);
		}
		DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) done node don't exists anymore"<<endl<<flush);
		return;
	}
	//get all defined variable in the Fib object
	list<cFibVariable*> liDefinedVariables =
		pChangedFibNode->getFibObject()->
			getDefinedVariables( ED_ALL );
	//get all Fib input variables not defined anymore in the Fib object
	for ( list<cFibVariable*>::const_iterator
			itrDefVariable = liDefinedVariables.begin();
			itrDefVariable != liDefinedVariables.end(); itrDefVariable++ ){
		//find Fib input variable for defined Fib variable
		map< cFibVariable * , cFibInputVariable * >::iterator
			itrFibInVarForDefVar = mapFibInputVariables.find( *itrDefVariable );
		if ( itrFibInVarForDefVar != mapFibInputVariables.end() ){
			//input variable for defined variable found -> delete it
			setInputVariableForNode.erase( itrFibInVarForDefVar->second );
		}
	}
	pFibNodeHandler->unlock( pChangedFibNode );
	//delete all not defined input variables
	DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) delete all "<<setInputVariableForNode.size()<<" not defined input variables"<<endl<<flush);
	for ( set< cFibInputVariable * >::iterator
			itrInVar = setInputVariableForNode.begin();
			itrInVar != setInputVariableForNode.end(); itrInVar++ ){
		//TODO: can't do this variable could get deleted before
		delete (*itrInVar);
	}
	
	mutexFibInputVariableHandler.unlock();
	DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) done"<<endl<<flush);
}


/**
 * Event method
 * It will be called every time a input variable value (cFibInputVariable),
 * at which this object is registered,was changed.
 *
 * @see cFibInputVariable::dValue
 * @param pFibInputVariable a pointer to the changed Fib input variable
 */
void cFibInputVariableHandler::fibInputVariableChangedEvent(
		const eFibInputVariableChangedEvent * pFibInputVariableEvent ){
	
	DEBUG_OUT_L2(<<"cFibInputVariableHandler("<<this<<")::fibInputVariableChangedEvent( pFibInputVariableEvent="<<pFibInputVariableEvent<<" ) called"<<endl<<flush);
	
	if ( ( pFibInputVariableEvent == NULL ) ||
			( pFibInputVariableEvent->pInputVariableChanged == NULL ) ){
		//no event or input variable -> nothing to do
		return;
	}
	if ( pFibInputVariableEvent->bInputVariableDeleted ){
		//if input variable gets deleted -> update this object members
		mutexFibInputVariableHandler.lock();
		cFibInputVariable * pInVarDeleted = const_cast< cFibInputVariable *>(
			pFibInputVariableEvent->pInputVariableChanged );
		//update class members
		setFibInputVariables.erase( pInVarDeleted );
		for ( map< cFibVariable * , cFibInputVariable * >::iterator
				itrActualInVar = mapFibInputVariables.begin();
				itrActualInVar != mapFibInputVariables.end(); itrActualInVar++ ){
			
			if ( itrActualInVar->second == pInVarDeleted ){
				//input variable found -> delete it from container
				mapFibInputVariables.erase( itrActualInVar );
				break;
			}
		}
		for ( map< cFibNode * , set< cFibInputVariable * > >::iterator
				itrActualNode = mapInputVariablesForNodes.begin();
				itrActualNode != mapInputVariablesForNodes.end(); itrActualNode++ ){
			
			set< cFibInputVariable * >::iterator itrFoundInVar =
				itrActualNode->second.find( pInVarDeleted );
			
			if ( itrFoundInVar != itrActualNode->second.end() ){
				//input variable found -> delete it from container
				itrActualNode->second.erase( itrFoundInVar );
				if ( itrActualNode->second.empty() ){
					//no input variables for the node -> delete node from container
					mapInputVariablesForNodes.erase( itrActualNode );
				}
				break;
			}
		}
		mutexFibInputVariableHandler.unlock();
		return;
	}//else nothing to do
	
}

















