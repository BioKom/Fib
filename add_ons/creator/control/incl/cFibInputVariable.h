
//TODO check

/**
 * @file cFibInputVariable
 * file name: cFibInputVariable.h
 * @author Betti Oesterholz
 * @date 16.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file specifies a class for a input variable of a Fib object.
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
 * This file specifies a class for a input variable of a Fib object.
 * In some Fib objects not all used variables are defined in it.
 * Every Fib variable, which is used in a Fib object, but not defined in it
 * is a input variable for the Fib object. The input variables need to be
 * given  and set for a Fib object.
 *
 *
 * @see cFibInputVariables
 * @see cFibVariable
 * @see cFibElement
 */
/*
History:
16.08.2013  Oesterholz  created
*/


#ifndef ___FIB__NCREATOR__C_FIB_INPUT_VARIABLE_H__
#define ___FIB__NCREATOR__C_FIB_INPUT_VARIABLE_H__


#include "version.h"

#include "lInputVariableChanged.h"
#include "eFibInputVariableChangedEvent.h"
#include "lInputVariableValueChanged.h"

#include "cFibVariable.h"

#include "cDomainSingle.h"


#include <string>

#include <QObject>
#include <QList>
#include <QString>


namespace fib{

namespace nCreator{

//cyclic dependencies
class cFibInputVariableHandler;

class cFibInputVariable: public QObject{
		Q_OBJECT
	
friend class cFibInputVariableHandler;
	
	/**
	 * A pointer to the Fib Variable which is the input variable for the
	 * Fib object.
	 */
	fib::cFibVariable * pFibVariable;
	
	/**
	 * The value for the input variable.
	 */
	doubleFib dValue;
	
	/**
	 * The name of the input variable.
	 */
	QString strVariableName;
	
	/**
	 * The domain with the possible values vor a input variable.
	 * The value dValue to be set should be in this domain. Only values in
	 * this domain can be set.
	 * If it is the null pointer NULL all values can be set.
	 *
	 * @see dValue
	 * @see setValue()
	 * @see increaseValue()
	 * @see decreaseValue()
	 */
	cDomainSingle * pVariableDomain;
	
	/**
	 * The delta value to increase or decrease the value of the variable.
	 *
	 * @see dValue
	 * @see increaseValue()
	 * @see decreaseValue()
	 */
	doubleFib dDeltaValue;
	
	/**
	 * If true the value of the input variable can be increased.
	 */
	bool bCanIncreaseValue;
	
	/**
	 * If true the value of the input variable can be decreased.
	 */
	bool bCanDecreaseValue;
	
	/**
	 * The set with the listeners for input variables changes.
	 */
	set< lInputVariableChanged * > setInputVariableChangeListener;
	
	/**
	 * The set with the listeners for input variables value changes.
	 */
	set< lInputVariableValueChanged * > setInputVariableValueChangeListener;
	
	
	/**
	 * parameter constructor for a input variable
	 *
	 * @param pInInputVariable a pointer to the Fib variable for the input variable
	 * 	@see cFibVariable
	 * @param dInValue the value for the input variable
	 * 	@see assignValue()
	 * @param strInVariableName the name of the input variable
	 * 	@see strVariableName
	 * @param pInVariableDomain a pointer to the domain for the input variable
	 * 	Beware: This object will delete the given object on destruction.
	 */
	cFibInputVariable( fib::cFibVariable * pInInputVariable,
		const doubleFib dInValue = 0, const QString strInVariableName="",
		cDomainSingle * pInVariableDomain = NULL );
	
	/**
	 * copy parameter constructor for a input variable
	 * It will copy the values of a given input variable except the pointer
	 * to the Fib input variable itself, which will be given seperatly.
	 * If you copy or clone a Fib object, you can use this constructor to
	 * copy its input variables.
	 *
	 * @param fibInputVariable a reference to the input variable, which
	 * 	values to copy (the pointer to the input variable won't be copied)
	 * @param pInInputVariable a pointer to the Fib variable for the input variable
	 * 	@see cFibVariable
	 */
	cFibInputVariable( const cFibInputVariable & fibInputVariable,
		fib::cFibVariable * pInInputVariable );
	
	/**
	 * copy constructor for a input variable
	 *
	 * @param fibInputVariable a reference to the input variable, which to copy
	 */
	cFibInputVariable( const cFibInputVariable & fibInputVariable);
	
	/**
	 * destructor
	 */
	~cFibInputVariable();
	
public:
	
	/**
	 * @return the name of this class "cFibInputVariable"
	 */
	std::string getName() const;
	
	/**
	 * @see pFibVariable
	 * @see setFibVariable()
	 * @return a pointer to the Fib variable for the input variable
	 */
	const fib::cFibVariable * getFibVariable() const;
	
	/**
	 * @see pFibVariable
	 * @see setFibVariable()
	 * @return a pointer to the Fib variable for the input variable
	 */
	fib::cFibVariable * getFibVariable();
	
	/**
	 * This methods sets the pointer to the Fib variable of this input
	 * variable to the given Fib variable pointer.
	 *
	 * @see pFibVariable
	 * @see getFibVariable()
	 * @param pInInputVariable a pointer to the Fib variable to set for this
	 * 	input variable
	 */
	void setFibVariable( fib::cFibVariable * pInInputVariable );
	
	/**
	 * @see setValue()
	 * @see dValue
	 * @see assignValue()
	 * @return the value for the input variable
	 */
	doubleFib getValue() const;
	
	/**
	 * This method sets the value for the input variable.
	 * If a value is outside the domain pVariableDomain are given, it will
	 * be rounded to the next value inside the domain.
	 *
	 * @see assignValue()
	 * @see dValue
	 * @see getValue()
	 * @see cDomainSingle::round()
	 * @param dInValue the value to set for the input variable
	 */
	void setValue( const doubleFib & dInValue );
	
	/**
	 * This method assigns the value of the input variable to the Fib
	 * variable. ( pFibVariable->setValue( dValue ) )
	 * Call this function before evaluing the Fib object for the input variable.
	 *
	 * @see cFibVariable::setValue()
	 * @see getValue()
	 * @see setValue()
	 * @return true if the value could be assigned, else false
	 */
	bool assignValue();
	
	/**
	 * @return the name of the input variable
	 * 	@see strVariableName
	 */
	QString getVariableName() const;
	
	/**
	 * This method sets the name of the input to the given name.
	 *
	 * @see strVariableName
	 * @param strName the name of the input variable should have
	 */
	void setVariableName( const QString & strName );
	
	/**
	 * This method returns a pointer to the domain for the input variable.
	 *
	 * @see pVariableDomain
	 * @see setDomain()
	 * @return a pointer to the domain for the input variable, or the null
	 * 	pointer NULL if non exists
	 */
	const cDomainSingle * getDomain() const;
	
	/**
	 * This method sets domain for the input variable.
	 * Note: Thismethod will reset the delta value dDeltaValue and
	 * 	delete the old domain if existing.
	 *
	 * @see pVariableDomain
	 * @see setDomain()
	 * @see dDeltaValue
	 * @param pInVariableDomain a pointer to the domain for the input
	 * 	variable, or the null pointer NULL if non should exists
	 * 	Beware: This object will delete the given object on destruction.
	 */
	void setDomain( cDomainSingle * pInVariableDomain = NULL );
	
	/**
	 * @return the delta value by which the variable value is increased or
	 * 	decreased
	 * @see dDeltaValue
	 * @see increaseValue()
	 * @see decreaseValue()
	 */
	doubleFib getDelta() const;
	
	/**
	 * This method sets the delta value by which the variable value is
	 * increased or decreased.
	 *
	 * @see dDeltaValue
	 * @see increaseValue()
	 * @see decreaseValue()
	 * @param dInDeltaValue the new delta value to use
	 */
	void setDelta( const doubleFib & dInDeltaValue );
	
	/**
	 * @see increaseValue()
	 * @see dValue
	 * @see dDeltaValue
	 * @see canDecreaseValue()
	 * @return true if the value of the input variable can be increased else false
	 */
	bool canIncreaseValue();
	
	/**
	 * @see increaseValue()
	 * @see dValue
	 * @see dDeltaValue
	 * @see canDecreaseValue()
	 * @return true if the value of the input variable can be decreased else false
	 */
	bool canDecreaseValue();
	
	/**
	 * This method returns possible values for the input variable.
	 * It will return maximal ulMaxCount values, but can return less.
	 * Also it will try to space the values evenly across the domain for
	 * the input variable.
	 *
	 * @see pVariableDomain
	 * @see dDeltaValue
	 * @see decreaseValue()
	 * @see increaseValue()
	 * @return a list with maximal ulMaxCount values to which the input
	 * 	variable can be set
	 */
	QList< doubleFib > getPossibleValues( const unsigned long ulMaxCount = 1024 ) const;
	
	
	/**
	 * With this function you can register a listeners for changes in this
	 * input variable.
	 *
	 * @see unregisterInputVariableChangeListener()
	 * @see setInputVariableChangeListener
	 * @see sendInputVariableChange()
	 * @param pInputVariableListener a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool registerInputVariableChangeListener(
		lInputVariableChanged * pInputVariableListener );
	
	/**
	 * With this function you can unregister a listeners for changes in this
	 * input variable.
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
	 * With this function you can register a listeners for changes of this
	 * input variable value.
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
	 * With this function you can unregister a listeners for changes of this
	 * input variable value.
	 *
	 * @see registerInputVariableValueChangeListener()
	 * @see setInputVariableValueChangeListener
	 * @see sendInputVariableValueChange()
	 * @param pInputVariableValueListener a pointer to the listener for changes
	 * @return true if the listener was registered, else false
	 */
	bool unregisterInputVariableValueChangeListener(
		lInputVariableValueChanged * pInputVariableValueListener );

signals:
	
	/**
	 * This signal is triggert if the variable value chages.
	 *
	 * @see dValue
	 * @param dNewValue the new variable value
	 */
	void variableValueChanged( doubleFib dNewValue );
	
	/**
	 * This signal is triggert if the canIncreaseValue() status changes.
	 *
	 * @see bCanIncreaseValue
	 * @see canIncreaseValue()
	 * @param bIncreaseValuePossible true if incresing the value of the
	 * 	variable is possible, else false
	 */
	void increaseValuePossible( bool bIncreaseValuePossible );
	
	/**
	 * This signal is triggert if the canDecreaseValue() status changes.
	 *
	 * @see bCanDecreaseValue
	 * @see canDecreaseValue()
	 * @param bDecreaseValuePossible true if decresing the value of the
	 * 	variable is possible, else false
	 */
	void decreaseValuePossible( bool bDecreaseValuePossible );
	
	
public slots:
	
	
	/**
	 * This method will increase the value of the input variable (if possible).
	 * ( dValue = pVariableDomain->round( dValue + dDeltaValue )
	 * @see pVariableDomain
	 * @see dDeltaValue
	 * @see decreaseValue()
	 */
	bool increaseValue();
	
	/**
	 * This method will decrease the value of the input variable (if possible).
	 * ( dValue = pVariableDomain->round( dValue - dDeltaValue )
	 * @see pVariableDomain
	 * @see dDeltaValue
	 * @see increaseValue()
	 */
	bool decreaseValue();
	
	
protected:
	
	/**
	 * This method sents a input variable changed event to all input variable
	 * change listeners of this object.
	 *
	 * @see setInputVariableChangeListener
	 * @see registerInputVariableChangeListener()
	 * @see unregisterInputVariableChangeListener()
	 * @param pFibInputVariableChangedEvent the change event to send
	 */
	void sendInputVariableChange(
		const eFibInputVariableChangedEvent * pFibInputVariableChangedEvent );

	/**
	 * This method sents a input variable value changed event to all input
	 * variable value change listeners of this object.
	 *
	 * @see setInputVariableValueChangeListener
	 * @see registerInputVariableValueChangeListener()
	 * @see unregisterInputVariableValueChangeListener()
	 */
	void sendInputVariableValueChange();

	
};//end class cFibInputVariable

};//end namespace nCreator
};//end namespace fib

#endif //___FIB__NCREATOR__C_FIB_INPUT_VARIABLE_H__





