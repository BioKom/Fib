
//TODO check

/**
 * @file cFibInputVariables
 * file name: cFibInputVariables.h
 * @author Betti Oesterholz
 * @date 28.07.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a list of input variables.
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
 * This file specifies a class for a list of input variables.
 * If you have a Fib object, the input variables of it are root object
 * input variables or variables used in the Fib object but not defined in it.
 * With this class you can store these.
 *
 * @see cFibInputVariable
 * @see cFibVariable
 */
/*
History:
28.07.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_INPUT_VARIABLES_H__
#define ___FIB__NCREATOR__C_FIB_INPUT_VARIABLES_H__


#include "version.h"

#include "cFibElement.h"

#include "cFibInputVariable.h"
#include "lInputVariableChanged.h"
#include "eFibInputVariableChangedEvent.h"

#include <string>

#include <QObject>
#include <QList>
#include <QMutex>


namespace fib{

namespace nCreator{

class cFibInputVariables: public lInputVariableChanged,
		public lInputVariableValueChanged{
protected:
	/**
	 * A list with input variables.
	 */
	QList< cFibInputVariable * > inputVariables;
	
	/**
	 * Mutex to lock access to the list of input variables.
	 * Lock the mutex if you use one of the following containers:
	 * @see inputVariables
	 */
	mutable QMutex mutexFibNodeHandler;
	
	
	/**
	 * The Fib object for which the input variables are or NULL.
	 */
	cFibElement * pFibObject;
	
	
	/**
	 * The set with the listeners for input variables changes.
	 */
	set< lInputVariableChanged * > setInputVariableChangeListener;
	
	/**
	 * The set with the listeners for input variables value changes.
	 */
	set< lInputVariableValueChanged * > setInputVariableValueChangeListener;
	
public:

	/**
	 * standard constructor for a list of input variables
	 * It constructs a list of input variables with no input variables. (So
	 * you can add them later.)
	 */
	cFibInputVariables();

	/**
	 * parameter constructor for a list of input variables
	 *
	 * @param liInInputVariables list with input variables for this object
	 * 	@see inputVariables
	 * @param pInFibObject the Fib object for which the input variables are or NULL
	 * 	@see pFibObject
	 */
	cFibInputVariables( QList< cFibInputVariable * > & liInInputVariables,
		cFibElement * pInFibObject = NULL );
	
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
	 * 	Also the list will be updated for input variables changes.
	 * 	@see nFibObjectTools::evalueInputVariables()
	 * 	If bFindInputVariables is false, this constructor constructs a
	 * 	list of input variables with no input variables. (So you can add
	 * 	them later.)
	 * @param bTillRoot if true searches for input variables in the Fib
	 * 	object for pFibObject till the root Fib element (Fib element
	 * 	with no superior), else the input variables for pFibObject will
	 * 	be returned
	 */
	cFibInputVariables( cFibElement * pInFibObject,
		const bool bFindInputVariables = true, const bool bTillRoot=false );
	
	/**
	 * copy constructor for a list of input variables
	 *
	 * @param fibInputVariables the input variables to copy
	 */
	cFibInputVariables( cFibInputVariables & fibInputVariables );
	
	/**
	 * destructor
	 */
	virtual ~cFibInputVariables();
	
	
	/**
	 * @return the name of this class "cFibInputVariables"
	 */
	virtual std::string getName() const;
	
	
	/**
	 * @return the number of input variables in the input variables list
	 * 	@see inputVariables
	 */
	virtual unsigned int getNumberOfInputVariables() const;
	
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
	virtual cFibInputVariable * getInputVariable(
		const unsigned int uiNumberOfVariable );
	
	/**
	 * This method returns the uiNumberOfVariable'th input variable of
	 * this input variable list.
	 *
	 * @see inputVariables
	 * @see getNumberOfInputVariables()
	 * @param uiNumberOfVariable the number of the input variable to return
	 * 	(counting starts with 1)
	 * @return a const pointer to the uiNumberOfVariable'th input variable,
	 * 	or NULL if non exists
	 */
	virtual const cFibInputVariable * getInputVariable(
		const unsigned int uiNumberOfVariable ) const;
	
	/**
	 * @see inputVariables
	 * @see getNumberOfInputVariables()
	 * @see getInputVariable()
	 * @return a list with the pointers to the input variables of this input
	 * 	variable list
	 */
	virtual QList< cFibInputVariable * > getInputVariables();
	
	/**
	 * @see inputVariables
	 * @see getNumberOfInputVariables()
	 * @see getInputVariable()
	 * @return a const list with the pointers to the input variables of this
	 * 	input variable list
	 */
	virtual const QList< cFibInputVariable * > getInputVariables() const;
	
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
	virtual bool addInputVariable( cFibInputVariable * pInputVariable,
		const unsigned int uiPosition = 0 );
	
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
	virtual bool removeInputVariable( const unsigned int uiPosition );
	
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
	virtual bool removeInputVariable( cFibInputVariable * pInputVariable );
	
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
	virtual bool replaceInputVariable( cFibInputVariable * pInputVariable,
		const unsigned int uiPosition );
	
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
	virtual bool setInputVariables( QList< cFibInputVariable * > & liInInputVariables );
	
	/**
	 * @see setFibObject()
	 * @return a pointer to the Fib object, for which the input variables
	 * 	of this object are or NULL if non was given
	 * 	@see pFibObject
	 */
	virtual cFibElement * getFibObject();
	
	/**
	 * @see setFibObject()
	 * @return a const pointer to the Fib object, for which the input
	 * 	variables of this object are or NULL if non was given
	 * 	@see pFibObject
	 */
	virtual const cFibElement * getFibObject() const;
	
	/**
	 * This method sets the Fib object, for which the input
	 * variables of this object are.
	 *
	 * @see pFibObject
	 * @see getFibObject()
	 * @param pInFibObject a pointer to the Fib object, for which the input
	 * 	variables of this object are or NULL if non should be stored
	 */
	virtual void setFibObject( cFibElement * pInFibObject );
	
	
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
	virtual void assignValues();
	
	
	/**
	 * Event method
	 * It will be called every time a input variable (cFibInputVariable),
	 * at which this object is registered,was changed.
	 *
	 * @param pFibInputVariableEvent a pointer to the event with the
	 * 	information of the change of the Fib input variable
	 */
	virtual void fibInputVariableChangedEvent(
		const eFibInputVariableChangedEvent * pFibInputVariableEvent );
	
	/**
	 * Event method
	 * It will be called every time a input variable value (cFibInputVariable),
	 * at which this object is registered, was changed.
	 *
	 * @see cFibInputVariable::dValue
	 * @param pFibInputVariable a pointer to the changed Fib input variable
	 */
	virtual void fibInputVariableValueChangedEvent(
		const cFibInputVariable * pFibInputVariable );
	
	
	
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
	bool registerInputVariableChangeListener(
		lInputVariableChanged * pInputVariableListener );
	
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
	bool unregisterInputVariableChangeListener(
		lInputVariableChanged * pInputVariableListener );

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
	bool registerInputVariableValueChangeListener(
		lInputVariableValueChanged * pInputVariableValueListener );
	
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
	bool unregisterInputVariableValueChangeListener(
		lInputVariableValueChanged * pInputVariableValueListener );
	
};//end class cFibInputVariables

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_INPUT_VARIABLES_H__





