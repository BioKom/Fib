
//TODO check

/**
 * @file cFibVariableHandler
 * file name: cFibVariableHandler.cpp
 * @author Betti Oesterholz
 * @date 25.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for handling Fib variables for the
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
 * This file implements a class for handling Fib variables for the
 * Fib creator application.
 *
 * @pattern singelton
 * @see cFibVariableCreator
 */
/*
History:
25.08.2013  Oesterholz  created
*/


//TODO switches for test proposes
#define DEBUG


#include "cFibVariableHandler.h"


#include <QObject>

#include "cFibElement.h"
#include "cRoot.h"
#include "cTypeInVar.h"

#include "cFibNode.h"
#include "cFibNodeHandler.h"
#include "cFibInputVariable.h"
#include "eFibNodeChangedEvent.h"


using namespace std;


using namespace fib::nCreator;
using namespace fib;


/**
 * A pointer to the variable handler object.
 */
cFibVariableHandler *
	cFibVariableHandler::pFibVariableHandler = NULL;

/**
 * constructor for the Fib variable handler
 */
cFibVariableHandler::cFibVariableHandler(){
	
	DEBUG_OUT_L2(<<"cFibVariableHandler("<<this<<")::cFibVariableHandler() called"<<endl<<flush);
	pFibVariableHandler = this;
	
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
cFibVariableHandler::~cFibVariableHandler(){
	
	DEBUG_OUT_L2(<<"cFibVariableHandler("<<this<<")::~cFibVariableHandler() called"<<endl<<flush);
	//delete all variables
	mutexFibVariableHandler.lock();
	cFibVariableCreator * pInputVariableToDelete;
	while ( ! setFibVariables.empty() ){
		//delete input variable
		pInputVariableToDelete = (*setFibVariables.begin());
		pInputVariableToDelete->unregisterChangeListener( this );
		delete pInputVariableToDelete;
		removeVariableFromHandler( pInputVariableToDelete );
	}
	mutexFibVariableHandler.unlock();
}


/**
 * @return a instance of the Fib variable handler
 */
cFibVariableHandler * cFibVariableHandler::getInstance(){
	
	DEBUG_OUT_L2(<<"cFibVariableHandler::getInstance() static called"<<endl<<flush);
	if ( pFibVariableHandler == NULL ){
		//create a new instance
		pFibVariableHandler = new cFibVariableHandler();
	}//else return existing instance
	DEBUG_OUT_L2(<<"cFibVariableHandler::getInstance() static done instance="<<pFibVariableHandler<<endl<<flush);
	return pFibVariableHandler;
}


/**
 * @return the name of this class "cFibVariableHandler"
 */
std::string cFibVariableHandler::getName() const{
	
	return std::string("cFibVariableHandler");
}


/**
 * This method returns the Fib variable for the given Fib variable.
 * If no Fib variable exists till now one is created.
 * Beware: Input variables which defining Fib element is deleted will
 * 	be also deleted.
 *
 * @see mapFibVariables
 * @param pFibVariable the Fib variable for the Fib variable to return
 * @param pListenerVariableChanged a listener for the changes in
 * 	the variable or NULL
 * @return the Fib variable for the given Fib variable, or NULL if
 * 	non could be evalued
 */
cFibVariableCreator * cFibVariableHandler::getFibVariableCreatorForFibVariable(
		fib::cFibVariable * pFibVariable,
		lFibVariableCreatorChanged * pListenerVariableChanged ){
	DEBUG_OUT_L2(<<"cFibVariableHandler("<<this<<")::getFibVariableCreatorForFibVariable( pFibVariable="<<pFibVariable<<", pListenerVariableChanged="<<pListenerVariableChanged<<" ) called"<<endl<<flush);
	if ( pFibVariable == NULL ){
		//no Fib variable given -> no variable possible
		return NULL;
	}
	
	//check if the variable for Fib variable exists allready
	mutexFibVariableHandler.lock();
	map< fib::cFibVariable * , cFibVariableCreator * >::iterator
		itrFoundInputVariable = mapFibVariables.find( pFibVariable );
	if ( itrFoundInputVariable != mapFibVariables.end() ){
		//variable for Fib variable found -> return it
		cFibVariableCreator * pFoundInVar = itrFoundInputVariable->second;
		if ( pListenerVariableChanged ){
			//add given change listener for variable
			pFoundInVar->registerChangeListener( pListenerVariableChanged );
		}
		mutexFibVariableHandler.unlock();
		DEBUG_OUT_L2(<<"cFibVariableHandler("<<this<<")::getFibVariableCreatorForFibVariable( pFibVariable="<<pFibVariable<<", pListenerVariableChanged="<<pListenerVariableChanged<<" ) done return existing variable "<<pFoundInVar<<endl<<flush);
		return pFoundInVar;
	}//variable for Fib variable don't exists -> create one
	cFibVariableCreator * pNewVariable = NULL;
	
	//get the master root object Fib node for the variable
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
			//TODO if domain exists -> set null value of domain as variable value
		
		switch ( cTypeDefFibElement ){
			case 'r':{
				cFibInputVariable * pNewInputVariable =
					new cFibInputVariable( pFibVariable );
				pNewVariable = pNewInputVariable;
				
				
				uiNextFreeNumber = mapVariableCounters[ cTypeDefFibElement ];
				strNumber.setNum( uiNextFreeNumber );
				pNewInputVariable->setVariableName(
					QString( QObject::tr("inVar", "variable prefix for root variable") ) +
						strNumber );
				
				//use variable domain
				cRoot * pDefiningRootElement = ((cRoot *)pDefiningFibElement);
				//evalue the number of the variable in the root element
				const list<fib::cFibVariable*> liRootInputVariables =
					pDefiningRootElement->getInputVariables();
				//position of input in root element variables
				unsignedIntFib uiActualInputVariable = 1;
				list<fib::cFibVariable*>::const_iterator
					itrActualRootInVar = liRootInputVariables.begin();
				//find position of input in root element variables
				for ( ; ( itrActualRootInVar != liRootInputVariables.end() ) &&
						( (*itrActualRootInVar) != pFibVariable );
						itrActualRootInVar++, uiActualInputVariable++ ){
				}
				if ( itrActualRootInVar != liRootInputVariables.end() ){
					//variable found in root element
					const cTypeInVar typeInVar( uiActualInputVariable );
					
					cDomain * pInVarDomain = pDefiningRootElement->getDomains()->
						getDomainForElement( typeInVar );
					if ( ( pInVarDomain == NULL ) || ( ! pInVarDomain->isScalar() ) ){
						//no good domain in normal domains -> try to use value domains
						pInVarDomain = pDefiningRootElement->getValueDomains()->
							getDomainForElement( typeInVar );
					}
					if ( ( pInVarDomain != NULL ) && ( pInVarDomain->isScalar() ) ){
						//good domain found -> set it (/clone) for the variable
						pNewInputVariable->setDomain( ((cDomainSingle *)(
							pInVarDomain->clone() )) );
					}
					/*set the value for the variable to the standard value
					 of the root variable*/
					pNewInputVariable->setValue( pDefiningRootElement->
						getStandardValueOfInputVariable( uiActualInputVariable ) );
					
					/*set the variable name to the optional part entry
					 *with key "inVarX::name" or "inVarX::description"*/
					const cOptionalPart * pOptionalPart =
						pDefiningRootElement->getOptionalPart();
					if ( pOptionalPart != NULL ){
						char szKeyBuffer[ 64 ];
						sprintf( szKeyBuffer, "inVar%u::name", uiActualInputVariable );
						//try to find a "inVarX::name" entry
						const list< pair<string,string> > liFoundNameEntries =
							pOptionalPart->getEntries( string( szKeyBuffer ) );
						
						if ( ! liFoundNameEntries.empty() ){
							//a "inVarX::name" was found -> set the variable name to it
							pNewInputVariable->setVariableName( QString(
								liFoundNameEntries.front().second.c_str() ) );
						}else{//if liFoundNameEntries.empty()
							sprintf( szKeyBuffer, "inVar%u::description",
								uiActualInputVariable );
							//try to find a "inVarX::description" entry
							const list< pair<string,string> > liFoundDescriptionEntries =
								pOptionalPart->getEntries( string( szKeyBuffer ) );
							
							if ( ! liFoundDescriptionEntries.empty() ){
								//a "inVarX::name" was found -> set the variable name to it
								pNewInputVariable->setVariableName( QString(
									liFoundDescriptionEntries.front().second.c_str() ) );
							}//else don't change the variable name
						}
					}//end if set the variables name from optional part
					
				}
			};break;
			case 'f':{
				pNewVariable = new cFibVariableCreator( pFibVariable );
				uiNextFreeNumber = mapVariableCounters[ cTypeDefFibElement ];
				strNumber.setNum( uiNextFreeNumber );
				pNewVariable->setVariableName(
					QString( QObject::tr("funVar", "variable prefix for function variable") ) +
						strNumber );
			};break;
			case 'a':{
				pNewVariable = new cFibVariableCreator( pFibVariable );
				uiNextFreeNumber = mapVariableCounters[ cTypeDefFibElement ];
				strNumber.setNum( uiNextFreeNumber );
				pNewVariable->setVariableName(
					QString( QObject::tr("areaVar", "variable prefix for area variable") ) +
						strNumber );
			};break;
			case 's':{
				pNewVariable = new cFibVariableCreator( pFibVariable );
				uiNextFreeNumber = mapVariableCounters[ cTypeDefFibElement ];
				strNumber.setNum( uiNextFreeNumber );
				pNewVariable->setVariableName(
					QString( QObject::tr("setVar", "variable prefix for set element variable") ) +
						strNumber );
			};break;
			case 'm':{
				pNewVariable = new cFibVariableCreator( pFibVariable );
				uiNextFreeNumber = mapVariableCounters[ cTypeDefFibElement ];
				strNumber.setNum( uiNextFreeNumber );
				pNewVariable->setVariableName(
					QString( QObject::tr("matrixVar", "variable prefix for matrix element variable") ) +
						strNumber );
			};break;
			case 'o':{
				pNewVariable = new cFibVariableCreator( pFibVariable );
				uiNextFreeNumber = mapVariableCounters[ cTypeDefFibElement ];
				strNumber.setNum( uiNextFreeNumber );
				pNewVariable->setVariableName(
					QString( QObject::tr("subObjVar", "variable prefix for external subobject variable") ) +
						strNumber );
			};break;
			default:{
				pNewVariable = new cFibVariableCreator( pFibVariable );
				strNumber.setNum( uiNextFreeNumber );
				pNewVariable->setVariableName(
					QString( QObject::tr("var", "variable prefix") ) +
						strNumber );
			};break;
		};
		uiNextFreeNumber++;
		
	}else{//create dummy name
		pNewVariable = new cFibVariableCreator( pFibVariable );
		//choose name for the variable
		unsigned int & uiNextFreeNumber = mapVariableCounters[ 'u' ];
		//the string for the variable number
		QString strNumber;
		strNumber.setNum( uiNextFreeNumber );
		pNewVariable->setVariableName(
			QString( QObject::tr("var", "variable prefix") ) +
				strNumber );
		uiNextFreeNumber++;
	}
	
	if ( pListenerVariableChanged ){
		//add given change listener for variable
		pNewVariable->registerChangeListener(
			pListenerVariableChanged );
	}
	//update class members
	setFibVariables.insert( pNewVariable );
	mapFibVariables.insert( pair< fib::cFibVariable * , cFibVariableCreator * >(
		pFibVariable, pNewVariable ) );
	mapVariablesForNodes[ pMasterNode ].insert( pNewVariable );
	mapDefiningFibElements.insert( pair< cFibVariableCreator * , cFibElement * >(
		pNewVariable, pDefiningFibElement ) );
	
	mutexFibVariableHandler.unlock();
	
	DEBUG_OUT_L2(<<"cFibVariableHandler("<<this<<")::getFibVariableCreatorForFibVariable( pFibVariable="<<pFibVariable<<", pListenerVariableChanged="<<pListenerVariableChanged<<" ) done return new variable "<<pNewVariable<<endl<<flush);
	return pNewVariable;
}


/**
 * This method checks if the given pointer points to a in this handler
 * existing Fib variable.
 *
 * @param pFibInputVariable a pointer to the Fib variable to check
 * @return true if the given Fib variable points to an existing
 * 	Fib variable in this handler, else false
 */
bool cFibVariableHandler::isValidInputVariable(
		cFibVariableCreator * pFibInputVariable ){
	
	if ( setFibVariables.find( pFibInputVariable ) ==
			setFibVariables.end() ){
		//variable not found -> not valid variable
		return false;
	}//variable found -> valid variable
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
void cFibVariableHandler::fibNodeChangedEvent(
		const eFibNodeChangedEvent * pFibNodeChanged ){
	
	DEBUG_OUT_L2(<<"cFibVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) called"<<endl<<flush);
	
	if ( pFibNodeChanged == NULL ) {
		//no Fib node change event
		return;
	}
	cFibNode * pChangedFibNode =
		const_cast< cFibNode* >( pFibNodeChanged->getChangedNode() );
	if ( pChangedFibNode == NULL ){
		//no node changed
		DEBUG_OUT_L2(<<"cFibVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) done no node changed"<<endl<<flush);
		return;
	}
	//evalue the variables for the node
	mutexFibVariableHandler.lock();
	map< cFibNode * , set< cFibVariableCreator * > >::const_iterator
		itrVarsForNode = mapVariablesForNodes.find( pChangedFibNode );
	if ( itrVarsForNode == mapVariablesForNodes.end() ){
		//Fib node not found
		mutexFibVariableHandler.unlock();
		DEBUG_OUT_L2(<<"cFibVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) done Fib node not found"<<endl<<flush);
		return;
	}
	set< cFibVariableCreator * > setVariableForNode = itrVarsForNode->second;
	
	//delete variables which defining Fib elements where deleted
	set< cFibVariableCreator * >::iterator itrVariableNext;
	for ( set< cFibVariableCreator * >::iterator
			itrVariable = setVariableForNode.begin();
			itrVariable != setVariableForNode.end(); ) {
		
		std::map< cFibVariableCreator * , cFibElement * >::iterator
			itrDefFibElement = mapDefiningFibElements.find( *itrVariable );
		
		if ( ( itrDefFibElement != mapDefiningFibElements.end() ) &&
				( pFibNodeChanged->isElementChanged(
					itrDefFibElement->second, eFibNodeChangedEvent::DELETED ) ) ) {
			//the defining Fib element was deleted -> delete the variable
			(*itrVariable)->unregisterChangeListener( this );
			delete (*itrVariable);
			removeVariableFromHandler( *itrVariable );
			
			//delete variable from set of variables to check setVariableForNode
			itrVariableNext = itrVariable;
			++itrVariableNext;
			setVariableForNode.erase( itrVariable );
			itrVariable = itrVariableNext;
		}else{//check next variable
			itrVariable++;
		}
	}//end for all variables of the event Fib node

	
	//check if all variables for the node still exists
	cFibNodeHandler * pFibNodeHandler = cFibNodeHandler::getInstance();
	if ( ( pChangedFibNode->getFibObjectConst() == NULL ) ||
			( ! pFibNodeHandler->lock( pChangedFibNode ) ) ){
		//node don't exists anymore -> delete all variables for it
		pFibNodeHandler->unlock( pChangedFibNode );
		
		DEBUG_OUT_L2(<<"cFibVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) node don't exists anymore -> delete all "<<setVariableForNode.size()<<" variables for it"<<endl<<flush);
		for ( set< cFibVariableCreator * >::iterator
				itrVariable = setVariableForNode.begin();
				itrVariable != setVariableForNode.end(); itrVariable++ ){
			(*itrVariable)->unregisterChangeListener( this );
			delete (*itrVariable);
			removeVariableFromHandler( *itrVariable );
		}
		mutexFibVariableHandler.unlock();
		DEBUG_OUT_L2(<<"cFibVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) done node don't exists anymore"<<endl<<flush);
		return;
	}
	//get all defined variable in the Fib object
	list<fib::cFibVariable*> liDefinedVariables =
		pChangedFibNode->getFibObject()->
			getDefinedVariables( ED_ALL );
	//get all Fib variables not defined anymore in the Fib object
	for ( list<fib::cFibVariable*>::const_iterator
			itrDefVariable = liDefinedVariables.begin();
			itrDefVariable != liDefinedVariables.end(); itrDefVariable++ ){
		//find Fib variable for defined Fib variable
		map< fib::cFibVariable * , cFibVariableCreator * >::iterator
			itrFibInVarForDefVar = mapFibVariables.find( *itrDefVariable );
		if ( itrFibInVarForDefVar != mapFibVariables.end() ){
			//variable for defined variable found -> delete it
			setVariableForNode.erase( itrFibInVarForDefVar->second );
		}
	}
	pFibNodeHandler->unlock( pChangedFibNode );
	//delete all not defined variables
	DEBUG_OUT_L2(<<"cFibVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) delete all "<<setVariableForNode.size()<<" not defined variables"<<endl<<flush);
	for ( set< cFibVariableCreator * >::iterator
			itrVariable = setVariableForNode.begin();
			itrVariable != setVariableForNode.end(); itrVariable++ ){
		(*itrVariable)->unregisterChangeListener( this );
		delete (*itrVariable);
		removeVariableFromHandler( *itrVariable );
	}
	mutexFibVariableHandler.unlock();
	
	DEBUG_OUT_L2(<<"cFibVariableHandler("<<this<<")::fibNodeChangedEvent( pFibNodeChanged="<<pFibNodeChanged<<" ) done"<<endl<<flush);
}


/**
 * Event method
 * It will be called every time a scalar (cFibScalar), at which this object
 * is registered, was changed.
 *
 * @see cFibScalar::dValue
 * @param pFibVariableChangedEvent a pointer to the Fib scalar change event
 */
void cFibVariableHandler::changedEvent(
		const eFibVariableCreatorChangedEvent * pFibVariableChangedEvent ){
	DEBUG_OUT_L2(<<"cFibScalarHandler("<<this<<")::changedEvent( pFibVariableChangedEvent="<<pFibVariableChangedEvent<<" ) called"<<endl<<flush);
	
	if ( ( pFibVariableChangedEvent == NULL ) ||
			( pFibVariableChangedEvent->getObject() == NULL ) ){
		//no event or variable -> nothing to do
		return;
	}
	if ( pFibVariableChangedEvent->isDeleted() ){
		//if variable gets deleted -> update this object members
		mutexFibVariableHandler.lock();
		//just needs the pointer, not the object
		cFibVariableCreator * pInVarDeleted = const_cast< cFibVariableCreator *>(
			static_cast< const cFibVariableCreator *>( pFibVariableChangedEvent->getObject() ) );
		
		removeVariableFromHandler( pInVarDeleted );
		mutexFibVariableHandler.unlock();
		return;
	}//else nothing to do
	
}

/**
 * This method will remove the given variable from this handler.
 * Note: Tis method won't use any mutex.
 *
 * @see setFibVariables
 * @see mapFibVariables
 * @see mapVariablesForNodes
 * @see mapDefiningFibElements
 * @see mutexFibVariableHandler
 * @param pVariable a pointer to the variable to delete from this handler
 */
void cFibVariableHandler::removeVariableFromHandler(
		cFibVariableCreator * pVariable ) {
	//update class members
	setFibVariables.erase( pVariable );
	mapDefiningFibElements.erase( pVariable );
	for ( map< fib::cFibVariable * , cFibVariableCreator * >::iterator
			itrActualVariable = mapFibVariables.begin();
			itrActualVariable != mapFibVariables.end(); itrActualVariable++ ){
		
		if ( itrActualVariable->second == pVariable ){
			//variable found -> delete it from container
			mapFibVariables.erase( itrActualVariable );
			break;
		}
	}
	for ( map< cFibNode * , set< cFibVariableCreator * > >::iterator
			itrActualNode = mapVariablesForNodes.begin();
			itrActualNode != mapVariablesForNodes.end(); itrActualNode++ ){
		
		set< cFibVariableCreator * >::iterator itrFoundVariable =
			itrActualNode->second.find( pVariable );
		
		if ( itrFoundVariable != itrActualNode->second.end() ){
			//variable found -> delete it from container
			itrActualNode->second.erase( itrFoundVariable );
			if ( itrActualNode->second.empty() ){
				//no variables for the node -> delete node from container
				mapVariablesForNodes.erase( itrActualNode );
			}
			break;
		}
	}
}













