
//TODO check

/**
 * @file cFibInputVariables
 * file name: cFibInputVariables.cpp
 * @author Betti Oesterholz
 * @date 23.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a list of input variables.
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
 * This file implements a class for a list of input variables.
 * If you have a Fib object, the input variables of it are root object
 * input variables or variables used in the Fib object but not defined in it.
 * With this class you can store these.
 *
 * @see cFibInputVariable
 * @see cFibVariable
 */
/*
History:
23.08.2013  Oesterholz  created
*/


//TODO switches for test proposes
#define DEBUG


#include "cFibInputVariables.h"

#include "nFibObjectTools.h"
#include "cFibInputVariableHandler.h"


using namespace fib::nCreator;
using namespace fib;




/**
 * standard constructor for a list of input variables
 * It constructs a list of input variables with no input variables. (So
 * you can add them later.)
 */
cFibInputVariables::cFibInputVariables():pFibObject( NULL ){
	//nothing to do
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::cFibInputVariables() called"<<endl<<flush);
}


/**
 * parameter constructor for a list of input variables
 *
 * @param liInInputVariables list with input variables for this object
 * 	@see inputVariables
 * @param pInFibObject the Fib object for which the input variables are or NULL
 * 	@see pFibObject
 */
cFibInputVariables::cFibInputVariables(
		QList< cFibInputVariable * > & liInInputVariables,
		cFibElement * pInFibObject ):inputVariables( liInInputVariables ),
		pFibObject( pInFibObject ){
	
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::cFibInputVariables( liInInputVariables, pInFibObject="<<pInFibObject<<") called"<<endl<<flush);
	//register this as input variable change listener at input variables
	for ( QList< cFibInputVariable * >::iterator
			itrActualInVar = inputVariables.begin();
			itrActualInVar != inputVariables.end(); itrActualInVar++ ){
		
		(*itrActualInVar)->registerInputVariableChangeListener( this );
		(*itrActualInVar)->registerInputVariableValueChangeListener( this );
	}
}


/**
 * parameter constructor for a list of input variables
 *
 * @param pInFibObject the Fib object for which the input variables are or NULL
 * 	@see pFibObject
 * @param bFindInputVariables if true it will evalue the input variables
 * 	for the given Fib object.
 * 	It will evalue all variables used in the Fib object, but not
 * 	defined in it. Also input variables are input variables of the
 * 	root element pFibObject, if pFibObject is a root element.
 * 	@see nFibObjectTools::evalueInputVariables()
 * 	Also the list will be updated for input variables changes.
 * 	If bFindInputVariables is false, this constructor constructs a
 * 	list of input variables with no input variables. (So you can add
 * 	them later.)
 * @param bTillRoot if true searches for input variables in the Fib
 * 	object for pFibObject till the root Fib element (Fib element
 * 	with no superior), else the input variables for pFibObject will
 * 	be returned
 */
cFibInputVariables::cFibInputVariables( cFibElement * pInFibObject,
		const bool bFindInputVariables, const bool bTillRoot ):
		pFibObject( pInFibObject ){
	
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::cFibInputVariables( pInFibObject="<<pInFibObject<<", bFindInputVariables="<<(bFindInputVariables?"true":"false")<<") called"<<endl<<flush);
	if ( bFindInputVariables && pFibObject != NULL ){
		mutexFibNodeHandler.lock();
		//evalue the input variables with nFibObjectTools::evalueInputVariables()
		list< cFibVariable * > liFibInputVariables =
			nFibObjectTools::evalueInputVariables( pFibObject, bTillRoot );
		/*use handler to get cFibInputVariable for cFibVariable and add them
		 *to inputVariables*/
		cFibInputVariableHandler * pFibInputVariableHandler =
			cFibInputVariableHandler::getInstance();
		for ( list< cFibVariable * > ::iterator
				itrActualInVar = liFibInputVariables.begin();
				itrActualInVar != liFibInputVariables.end();
				itrActualInVar++ ){
			/*get Fib input variable for Fib variable and register this as
			 *input variable change listener at Fib input variables*/
			cFibInputVariable * pActualInputVariable =
				pFibInputVariableHandler->getFibInputVariableForFibVariable(
					*itrActualInVar, this );
			
			if ( pActualInputVariable ){
				pActualInputVariable->registerInputVariableValueChangeListener( this );
				
				inputVariables.push_back( pActualInputVariable );
			}
		}
		mutexFibNodeHandler.unlock();
	}
}


/**
 * copy constructor for a list of input variables
 *
 * @param fibInputVariables the input variables to copy
 */
cFibInputVariables::cFibInputVariables( cFibInputVariables & fibInputVariables ):
		inputVariables( fibInputVariables.inputVariables ),
		pFibObject( fibInputVariables.pFibObject ){
			
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::cFibInputVariables( &fibInputVariables="<<(&fibInputVariables)<<" ) called"<<endl<<flush);
	//register this as input variable change listener at input variables
	mutexFibNodeHandler.lock();
	for ( QList< cFibInputVariable * >::iterator
			itrActualInVar = inputVariables.begin();
			itrActualInVar != inputVariables.end(); itrActualInVar++ ){
		
		(*itrActualInVar)->registerInputVariableChangeListener( this );
		(*itrActualInVar)->registerInputVariableValueChangeListener( this );
	}
	mutexFibNodeHandler.unlock();
}


/**
 * destructor
 */
cFibInputVariables::~cFibInputVariables(){
	
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::~cFibInputVariables() called"<<endl<<flush);
	//unregister this as input variable change listener at input variables
	mutexFibNodeHandler.lock();
	for ( QList< cFibInputVariable * >::iterator
			itrActualInVar = inputVariables.begin();
			itrActualInVar != inputVariables.end(); itrActualInVar++ ){
		
		(*itrActualInVar)->unregisterInputVariableChangeListener( this );
		(*itrActualInVar)->unregisterInputVariableValueChangeListener( this );
	}
	mutexFibNodeHandler.unlock();
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::~cFibInputVariables() done"<<endl<<flush);
}


/**
 * @return the name of this class "cFibInputVariables"
 */
std::string cFibInputVariables::getName() const{
	
	return std::string( "cFibInputVariables" );
}


/**
 * @return the number of input variables in the input variables list
 * 	@see inputVariables
 */
unsigned int cFibInputVariables::getNumberOfInputVariables() const{
	
	return inputVariables.size();
}


/**
 * This method returns the uiNumberOfVariable'th input variable of
 * this input variable list.
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @param uiNumberOfVariable the number of the input variable to remove
 * 	(counting starts with 1)
 * @return a pointer to the uiNumberOfVariable'th input variable, or
 * 	NULL if non exists
 */
cFibInputVariable * cFibInputVariables::getInputVariable(
		const unsigned int uiNumberOfVariable ){
	
	mutexFibNodeHandler.lock();
	cFibInputVariable * pInputVariable =
		inputVariables.value( uiNumberOfVariable - 1, NULL );
	mutexFibNodeHandler.unlock();
	return pInputVariable;
}


/**
 * This method returns the uiNumberOfVariable'th input variable of
 * this input variable list.
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @param uiNumberOfVariable the number of the input variable to remove
 * 	(counting starts with 1)
 * @return a const pointer to the uiNumberOfVariable'th input variable,
 * 	or NULL if non exists
 */
const cFibInputVariable * cFibInputVariables::getInputVariable(
		const unsigned int uiNumberOfVariable ) const{
	
	mutexFibNodeHandler.lock();
	const cFibInputVariable * pInputVariable =
		inputVariables.value( uiNumberOfVariable - 1, NULL );
	mutexFibNodeHandler.unlock();
	return pInputVariable;
}


/**
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see getInputVariable()
 * @return a list with the pointers to the input variables of this input
 * 	variable list
 */
QList< cFibInputVariable * > cFibInputVariables::getInputVariables(){
	
	mutexFibNodeHandler.lock();
	QList< cFibInputVariable * > retInputVariables( inputVariables );
	mutexFibNodeHandler.unlock();
	return retInputVariables;
}


/**
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see getInputVariable()
 * @return a const list with the pointers to the input variables of this
 * 	input variable list
 */
const QList< cFibInputVariable * > cFibInputVariables::getInputVariables() const{
	
	mutexFibNodeHandler.lock();
	const QList< cFibInputVariable * > retInputVariables( inputVariables );
	mutexFibNodeHandler.unlock();
	return retInputVariables;
}


/**
 * This method adds the given input variable to this input variable list.
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see removeInputVariable()
 * @see replaceInputVariable()
 * @param pInputVariable a pointer to the input variable to add
 * @param uiPosition the position where to add the input variable,
 * 	if 0 or greater the number of input variables in this input
 * 	variable list it will be added to the end of the input variable list
 * 	(counting starts with 1)
 * @return true if the input variable was added, else false
 */
bool cFibInputVariables::addInputVariable( cFibInputVariable * pInputVariable,
		const unsigned int uiPosition ){
	
	mutexFibNodeHandler.lock();
	if ( pInputVariable == NULL ){
		//no input variable to add
		mutexFibNodeHandler.unlock();
		return true;
	}
	if ( ( uiPosition == 0 ) ||
			( ((unsigned int)(inputVariables.size())) < uiPosition ) ){
		//add input variable to the end of the input variable list
		inputVariables.push_back( pInputVariable );
	}else{//insert the input variable at the given position
		inputVariables.insert( uiPosition - 1 , pInputVariable );
	}
	//register this as input variable change listener at input variables
	pInputVariable->registerInputVariableChangeListener( this );
	pInputVariable->registerInputVariableValueChangeListener( this );
	
	mutexFibNodeHandler.unlock();
	return true;
}


/**
 * This method removes the uiPosition'th input variable from this input
 * variable list.
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see addInputVariable()
 * @see replaceInputVariable()
 * @param uiPosition the position where to remove the input variable from
 * 	(counting starts with 1)
 * @return true if the input variable was removed, else false
 */
bool cFibInputVariables::removeInputVariable( const unsigned int uiPosition ){
	
	mutexFibNodeHandler.lock();
	if ( ( uiPosition < 1 ) ||
			( uiPosition <= ((unsigned int)(inputVariables.size())) ) ){
		//no such input variable to remove
		mutexFibNodeHandler.unlock();
		return false;
	}
	//evaluate the to remove input variable
	cFibInputVariable * pRemovedInputVariable =
		inputVariables.value( uiPosition - 1, NULL );
	//remove the input variable
	inputVariables.removeAt( uiPosition - 1 );
	if ( ! inputVariables.contains( pRemovedInputVariable ) ){
		//unregister this as input variable change listener at input variables
		pRemovedInputVariable->unregisterInputVariableChangeListener( this );
		pRemovedInputVariable->unregisterInputVariableValueChangeListener( this );
	}
	
	mutexFibNodeHandler.unlock();
	return true;
}


/**
 * This method removes the given input variable from this input
 * variable list.
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see addInputVariable()
 * @see replaceInputVariable()
 * @param pInputVariable the input variable to remove
 * @return true if the input variable was removed, else false
 */
bool cFibInputVariables::removeInputVariable(
		cFibInputVariable * pInputVariable ){
	
	mutexFibNodeHandler.lock();
	if ( ( pInputVariable == NULL ) ||
			( ! inputVariables.contains( pInputVariable ) ) ){
		//no such input variable to remove
		mutexFibNodeHandler.unlock();
		return false;
	}
	
	//remove input variable
	inputVariables.removeAll( pInputVariable );
	//unregister this as input variable change listener at input variables
	pInputVariable->unregisterInputVariableChangeListener( this );
	pInputVariable->unregisterInputVariableValueChangeListener( this );
	mutexFibNodeHandler.unlock();
	return true;
}


/**
 * This method replaces a input variable in this input variable list.
 * It will replace the uiPosition'th input variable in the input
 * variable list with the given input variable pInputVariable (if possible).
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see removeInputVariable()
 * @see addInputVariable()
 * @param pInputVariable a pointer to the input variable to add,
 * 	which will replace the old input variable on the uiPosition'th position
 * @param uiPosition the position where to replace the input variable,
 * 	(counting starts with 1)
 * @return true if the input variable was replace, else false
 */
bool cFibInputVariables::replaceInputVariable( cFibInputVariable * pInputVariable,
		const unsigned int uiPosition ){
	
	mutexFibNodeHandler.lock();
	if ( ( pInputVariable == NULL ) || ( uiPosition < 1 ) ||
			( uiPosition <= ((unsigned int)(inputVariables.size())) ) ){
		//no such input variable to replace
		mutexFibNodeHandler.unlock();
		return false;
	}
	//evaluate the to remove input variable
	cFibInputVariable * pRemovedInputVariable =
		inputVariables.value( uiPosition - 1, NULL );
	//remove the input variable
	inputVariables.removeAt( uiPosition - 1 );
	if ( ! inputVariables.contains( pRemovedInputVariable ) ){
		//unregister this as input variable change listener at input variables
		pRemovedInputVariable->unregisterInputVariableChangeListener( this );
		pRemovedInputVariable->unregisterInputVariableValueChangeListener( this );
	}
	
	//add the given input variable on the position
	if ( ((unsigned int)(inputVariables.size())) < uiPosition ){
		//add input variable to the end of the input variable list
		inputVariables.push_back( pInputVariable );
	}else{//insert the input variable at the given position
		inputVariables.insert( uiPosition - 1 , pInputVariable );
	}
	//register this as input variable change listener at new input variables
	pInputVariable->registerInputVariableChangeListener( this );
	pInputVariable->registerInputVariableValueChangeListener( this );
	
	mutexFibNodeHandler.unlock();
	return true;
}


/**
 * This method sets the list of input variables to the given list.
 * All old input variables of this list are removed and the given input
 * added.
 *
 * @see inputVariables
 * @see getNumberOfInputVariables()
 * @see replaceInputVariable()
 * @see removeInputVariable()
 * @see addInputVariable()
 * @param liInInputVariables a list of the input variables this object
 * 	should contain
 * @return true if the input variables could be set, else false
 */
bool cFibInputVariables::setInputVariables(
		QList< cFibInputVariable * > & liInInputVariables ){
	
	mutexFibNodeHandler.lock();
	//unregister this as input variable change listener at old input variables
	for ( QList< cFibInputVariable * >::iterator
			itrActualInVar = inputVariables.begin();
			itrActualInVar != inputVariables.end(); itrActualInVar++ ){
		
		(*itrActualInVar)->unregisterInputVariableChangeListener( this );
		(*itrActualInVar)->unregisterInputVariableValueChangeListener( this );
	}
	//set the new input variables
	inputVariables = liInInputVariables;
	
	//register this as input variable change listener at new input variables
	for ( QList< cFibInputVariable * >::iterator
			itrActualInVar = inputVariables.begin();
			itrActualInVar != inputVariables.end(); itrActualInVar++ ){
		
		(*itrActualInVar)->registerInputVariableChangeListener( this );
		(*itrActualInVar)->registerInputVariableValueChangeListener( this );
	}
	mutexFibNodeHandler.unlock();
	
	return true;
}


/**
 * @see setFibObject()
 * @return a pointer to the Fib object, for which the input variables
 * 	of this object are or NULL if non was given
 * 	@see pFibObject
 */
cFibElement * cFibInputVariables::getFibObject(){
	
	return pFibObject;
}


/**
 * @see setFibObject()
 * @return a const pointer to the Fib object, for which the input
 * 	variables of this object are or NULL if non was given
 * 	@see pFibObject
 */
const cFibElement * cFibInputVariables::getFibObject() const{
	
	return pFibObject;
}


/**
 * This method sets the Fib object, for which the input
 * variables of this object are.
 *
 * @see pFibObject
 * @see getFibObject()
 * @param pInFibObject a pointer to the Fib object, for which the input
 * 	variables of this object are or NULL if non should be stored
 */
void cFibInputVariables::setFibObject( cFibElement * pInFibObject ){
	
	pFibObject = pInFibObject;
}


/**
 * This method assigns the value of the input variable to the Fib
 * variable. ( pInputVariable->setValue( dValue ) )
 * Call this function before evaluing the Fib object for the input variable.
 *
 * @see cFibInputVariable::assignValues()
 * @see cFibVariable::setValue()
 * @see cFibInputVariable::getValue()
 * @see cFibInputVariable::setValue()
 */
void cFibInputVariables::assignValues(){
	
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::assignValues() called"<<endl<<flush);
	mutexFibNodeHandler.lock();
	for ( QList< cFibInputVariable * >::iterator
			itrActualInVar = inputVariables.begin();
			itrActualInVar != inputVariables.end(); itrActualInVar++ ){
		
		(*itrActualInVar)->assignValue();
	}
	mutexFibNodeHandler.unlock();
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::assignValues() done"<<endl<<flush);
}



/**
 * Event method
 * It will be called every time a input variable (cFibInputVariable),
 * at which this object is registered,was changed.
 *
 * @param pFibInputVariableEvent a pointer to the event with the
 * 	information of the change of the Fib input variable
 */
void cFibInputVariables::fibInputVariableChangedEvent(
		const eFibInputVariableChangedEvent * pFibInputVariableEvent ){
	
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::fibInputVariableChangedEvent( pFibInputVariableEvent="<<pFibInputVariableEvent<<") called"<<endl<<flush);
	if ( pFibInputVariableEvent == NULL ){
		//no event given
		return;
	}
	if ( pFibInputVariableEvent->bInputVariableDeleted ){
		//remove deleted input variable
		mutexFibNodeHandler.lock();
		inputVariables.removeAll( const_cast<cFibInputVariable*>(
			pFibInputVariableEvent->pInputVariableChanged ) );
		mutexFibNodeHandler.unlock();
	}
	//redirect event to all variables change listeners
	for ( set< lInputVariableChanged * >::iterator
			itrChangeListener = setInputVariableChangeListener.begin();
			itrChangeListener != setInputVariableChangeListener.end();
			itrChangeListener++ ){
		
		(*itrChangeListener)->fibInputVariableChangedEvent(
			pFibInputVariableEvent );
	}
}


/**
 * Event method
 * It will be called every time a input variable value (cFibInputVariable),
 * at which this object is registered, was changed.
 *
 * @see cFibInputVariable::dValue
 * @param pFibInputVariable a pointer to the changed Fib input variable
 */
void cFibInputVariables::fibInputVariableValueChangedEvent(
		const cFibInputVariable * pFibInputVariable ){
	
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::fibInputVariableValueChangedEvent( pFibInputVariable="<<pFibInputVariable<<") called"<<endl<<flush);
	if ( pFibInputVariable == NULL ){
		//no variable given
		return;
	}
	//redirect event to all variables change listeners
	for ( set< lInputVariableValueChanged * >::iterator
			itrChangeListener = setInputVariableValueChangeListener.begin();
			itrChangeListener != setInputVariableValueChangeListener.end();
			itrChangeListener++ ){
		
		(*itrChangeListener)->fibInputVariableValueChangedEvent(
			pFibInputVariable );
	}
}



/**
 * With this function you can register a listeners for changes for any
 * of the contained input variables.
 *
 * @see cFibInputVariable::registerInputVariableChangeListener()
 * @see unregisterInputVariableChangeListener()
 * @see setInputVariableChangeListener
 * @see sendInputVariableChange()
 * @param pInputVariableListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibInputVariables::registerInputVariableChangeListener(
		lInputVariableChanged * pInputVariableListener ){
	
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::registerInputVariableChangeListener( pInputVariableListener="<<pInputVariableListener<<") called"<<endl<<flush);
	if ( pInputVariableListener == NULL ){
		//nothing to register
		return false;
	}
	const pair< set< lInputVariableChanged * >::iterator, bool > paListenerInserted =
		setInputVariableChangeListener.insert( pInputVariableListener );
	return paListenerInserted.second;
}


/**
 * With this function you can unregister a listeners for changes for any
 * of the contained input variables.
 *
 * @see registerInputVariableChangeListener()
 * @see setInputVariableChangeListener
 * @see sendInputVariableChange()
 * @param pInputVariableListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibInputVariables::unregisterInputVariableChangeListener(
		lInputVariableChanged * pInputVariableListener ){
	
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::unregisterInputVariableChangeListener( pInputVariableListener="<<pInputVariableListener<<") called"<<endl<<flush);
	return ( 0 < setInputVariableChangeListener.erase( pInputVariableListener ) );
}


/**
 * With this function you can register a listeners for changes for any
 * of the contained input variables.
 *
 * @see unregisterInputVariableValueChangeListener()
 * @see setInputVariableValueChangeListener
 * @see sendInputVariableValueChange()
 * @param pInputVariableValueListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibInputVariables::registerInputVariableValueChangeListener(
		lInputVariableValueChanged * pInputVariableValueListener ){
	
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::registerInputVariableValueChangeListener( pInputVariableValueListener="<<pInputVariableValueListener<<") called"<<endl<<flush);
	if ( pInputVariableValueListener == NULL ){
		//nothing to register
		return false;
	}
	const pair< set< lInputVariableValueChanged * >::iterator, bool > paListenerInserted =
		setInputVariableValueChangeListener.insert( pInputVariableValueListener );
	return paListenerInserted.second;
}


/**
 * With this function you can unregister a listeners for changes for any
 * of the contained input variables.
 *
 * @see registerInputVariableValueChangeListener()
 * @see setInputVariableValueChangeListener
 * @see sendInputVariableValueChange()
 * @param pInputVariableValueListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibInputVariables::unregisterInputVariableValueChangeListener(
		lInputVariableValueChanged * pInputVariableValueListener ){
	
	DEBUG_OUT_L2(<<"cFibInputVariables("<<this<<")::unregisterInputVariableValueChangeListener( pInputVariableValueListener="<<pInputVariableValueListener<<") called"<<endl<<flush);
	return ( 0 < setInputVariableValueChangeListener.erase( pInputVariableValueListener ) );
}











