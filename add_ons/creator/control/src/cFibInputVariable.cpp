
//TODO check

/**
 * @file cFibInputVariable
 * file name: cFibInputVariable.cpp
 * @author Betti Oesterholz
 * @date 16.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements a class for a input variable of a Fib object.
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
 * This file implements a class for a input variable of a Fib object.
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



//TODO switches for test proposes
#define DEBUG


#include "cFibInputVariable.h"

#include "cDomainIntegerBasis.h"
#include "cDomainRationalBasis.h"



using namespace fib::nCreator;
using namespace fib;


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
cFibInputVariable::cFibInputVariable( cFibVariable * pInInputVariable,
		const doubleFib dInValue, const QString strInVariableName,
		cDomainSingle * pInVariableDomain ):
		pFibVariable( pInInputVariable ), dValue( dInValue ),
		strVariableName( strInVariableName ), pVariableDomain( NULL ){
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::cFibInputVariable( pInInputVariable="<<pInInputVariable<<", dInValue="<<dInValue<<", strInVariableName="<<strInVariableName.toStdString()<<", pInVariableDomain="<<pInVariableDomain<<") called"<<endl<<flush);
	setDomain( pInVariableDomain );//also sets dDeltaValue
}


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
cFibInputVariable::cFibInputVariable( const cFibInputVariable & fibInputVariable,
		cFibVariable * pInInputVariable ):
		pFibVariable( pInInputVariable ), dValue( fibInputVariable.dValue ),
		pVariableDomain( fibInputVariable.pVariableDomain ),
		dDeltaValue( fibInputVariable.dDeltaValue ){
	//nothing to do
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::cFibInputVariable( fibInputVariable, pInInputVariable="<<pInInputVariable<<") called"<<endl<<flush);
}


/**
 * copy constructor for a input variable
 *
 * @param fibInputVariable a reference to the input variable, which to copy
 */
cFibInputVariable::cFibInputVariable( const cFibInputVariable & fibInputVariable ):
		QObject( fibInputVariable.parent() ),
		pFibVariable( fibInputVariable.pFibVariable ),
		dValue( fibInputVariable.dValue ),
		pVariableDomain( fibInputVariable.pVariableDomain ),
		dDeltaValue( fibInputVariable.dDeltaValue ){
	//nothing to do
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::cFibInputVariable( fibInputVariable ) called"<<endl<<flush);
}


/**
 * destructor
 */
cFibInputVariable::~cFibInputVariable(){
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::~cFibInputVariable() called"<<endl<<flush);
	//send input variable change event
	eFibInputVariableChangedEvent fibInputVariableChangedEvent(
		this );
	fibInputVariableChangedEvent.bInputVariableDeleted = true;
	
	sendInputVariableChange( &fibInputVariableChangedEvent );
	//delete variable domain
	if ( pVariableDomain ){
		delete pVariableDomain;
	}
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::~cFibInputVariable() done"<<endl<<flush);
}


/**
 * @return the name of this class "cFibInputVariable"
 */
std::string cFibInputVariable::getName() const{
	
	return string( "cFibInputVariable" );
}


/**
 * @see pFibVariable
 * @see setFibVariable()
 * @return a pointer to the Fib variable for the input variable
 */
const fib::cFibVariable * cFibInputVariable::getFibVariable() const{
	
	return pFibVariable;
}


/**
 * @see pFibVariable
 * @see setFibVariable()
 * @return a pointer to the Fib variable for the input variable
 */
cFibVariable * cFibInputVariable::getFibVariable(){
	
	return pFibVariable;
}


/**
 * This methods sets the pointer to the Fib variable of this input
 * variable to the given Fib variable pointer.
 *
 * @see pFibVariable
 * @see getFibVariable()
 * @param pInInputVariable a pointer to the Fib variable to set for this
 * 	input variable
 */
void cFibInputVariable::setFibVariable( cFibVariable * pInInputVariable ){
	
	if ( pFibVariable == pInInputVariable ){
		//nothing changed
		return;
	}
	pFibVariable = pInInputVariable;
	
	//send input variable change event
	const eFibInputVariableChangedEvent fibInputVariableChangedEvent(
		this );
	sendInputVariableChange( &fibInputVariableChangedEvent );
}


/**
 * @see setValue()
 * @see dValue
 * @see assignValue()
 * @return the value for the input variable
 */
doubleFib cFibInputVariable::getValue() const{
	
	return dValue;
}


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
void cFibInputVariable::setValue( const doubleFib & dInValue ){
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::setValue( dInValue="<<dInValue<<") called"<<endl<<flush);
	if ( dValue == dInValue ){
		//value not changed
		return;
	}
	dValue = dInValue;
	
	if ( pVariableDomain ){
		if ( dValue < pVariableDomain->getMaximum() ){
			//value lower maximum -> value can be increased
			if ( ! bCanIncreaseValue ){
				bCanIncreaseValue = true;
				emit increaseValuePossible( true );
			}
		}else{//value can not be increased
			if ( bCanIncreaseValue ){
				bCanIncreaseValue = false;
				emit increaseValuePossible( false );
			}
		}
		
		if ( pVariableDomain->getMinimum() < dValue ){
			//value bigger minimum -> value can be decreased
			if ( ! bCanDecreaseValue ){
				bCanDecreaseValue = true;
				emit decreaseValuePossible( true );
			}
		}else{//value can not be decreased
			if ( bCanDecreaseValue ){
				bCanDecreaseValue = false;
				emit decreaseValuePossible( false );
			}
		}
	}//end if variable domain exists
	
	emit variableValueChanged( dValue );
	//send input variable change event
	const eFibInputVariableChangedEvent fibInputVariableChangedEvent(
		this );
	sendInputVariableChange( &fibInputVariableChangedEvent );
	sendInputVariableValueChange();
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::setValue( dInValue="<<dInValue<<") done"<<endl<<flush);
}


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
bool cFibInputVariable::assignValue(){
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::assignValue() "<<dValue<<" called"<<endl<<flush);
	if ( pFibVariable == NULL ){
		return false;
	}
	pFibVariable->setValue( dValue );
	return true;
}


/**
 * @return the name of the input variable
 * 	@see strVariableName
 */
QString cFibInputVariable::getVariableName() const{
	
	return strVariableName;
}


/**
 * This method sets the name of the input to the given name.
 *
 * @see strVariableName
 * @param strName the name of the input variable should have
 */
void cFibInputVariable::setVariableName( const QString & strName ){
	
	strVariableName = strName;
	
	//send input variable change event
	const eFibInputVariableChangedEvent fibInputVariableChangedEvent(
		this );
	sendInputVariableChange( &fibInputVariableChangedEvent );
}


/**
 * This method returns a pointer to the domain for the input variable.
 *
 * @see pVariableDomain
 * @see setDomain()
 * @return a pointer to the domain for the input variable, or the null
 * 	pointer NULL if non exists
 */
const cDomainSingle * cFibInputVariable::getDomain() const{
	
	return pVariableDomain;
}


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
void cFibInputVariable::setDomain( cDomainSingle * pInVariableDomain ){
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::setDomain( pInVariableDomain="<<pInVariableDomain<<") called"<<endl<<flush);
	if ( pVariableDomain ){
		delete pVariableDomain;
		if ( ( pInVariableDomain != NULL ) &&
				pVariableDomain->equal( * pInVariableDomain ) ){
			//domains allready equal -> don nothing
			DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::setDomain( pInVariableDomain="<<pInVariableDomain<<") done domains allready equal -> don nothing"<<endl<<flush);
			pInVariableDomain = pInVariableDomain;
			return;
		}
	}
	
	pVariableDomain = pInVariableDomain;
	//evalue a good delta value
	if ( pVariableDomain == NULL ){
		//no domain -> delta is standard value 1
		dDeltaValue = 1.0;
		
		//all values now possible
		if ( ! bCanIncreaseValue ){
			bCanIncreaseValue = true;
			emit increaseValuePossible( true );
		}
		if ( ! bCanDecreaseValue ){
			bCanDecreaseValue = true;
			emit decreaseValuePossible( true );
		}
		return;
	}//else pVariableDomain exists
	const doubleFib dMaximum = pVariableDomain->getMaximum();
	const doubleFib dMinimum = pVariableDomain->getMinimum();
	
	doubleFib dScalingFactor = 1.0;
	
	const string szDomainType = pVariableDomain->getType();
	if ( ( szDomainType.compare( 0, 19, "DomainNaturalNumber") == 0 ) ||
			( szDomainType.compare( 0, 13, "DomainInteger") == 0 ) ){
		//if the first domain is an integer number domain
		dScalingFactor = ((cDomainIntegerBasis*)pVariableDomain)->getScalingFactor();
	
	}else if ( szDomainType.compare( 0, 19, "cDomainRational") == 0 ){
		//if the first domain is an rational number domain
		/*set the exponent to the maximum and evalue the difference betwean
		 a minimal mantissa increas*/
		const cDomainRationalBasis * pVariableIntegerDomain =
			((cDomainRationalBasis*)pVariableDomain);
		
		const cDomainIntegerBasis * pMantissaDomain =
			pVariableIntegerDomain->getMantissaDomain();
		const cDomainIntegerBasis * pExponentDomain =
			pVariableIntegerDomain->getExponentDomain();
		
		const doubleFib dMantissaScalingFactor =
			pMantissaDomain->getScalingFactor();
		const longFib lExponentMaximum = roundToLongFib(
			pExponentDomain->getMaximum() );
		
		dScalingFactor = dMantissaScalingFactor *
			composeDoubleFib( 2, lExponentMaximum );
	}//else unknown domain type -> scaling factor is 1
	const doubleFib dWidth = dMaximum - dMinimum;
	const unsigned long ulNumbersInDomain = dWidth / dScalingFactor + 1;
	//min( ulNumbersInDomain, 1024 )
	const unsigned long ulStepsInDomain = ( ulNumbersInDomain < 1024 ) ?
		ulNumbersInDomain : 1024;
	
	dDeltaValue = dWidth / ((doubleFib)(ulStepsInDomain));
	
	if ( ( 0.9 < dDeltaValue ) && ( dDeltaValue < 1.1 ) ){
		//check if 1 is a multiple of the scaling factor
		if ( ( ( 0.9999 < dScalingFactor ) && ( dScalingFactor < 1.0001 ) ) ||
				( ( -1.0001 < dScalingFactor ) && ( dScalingFactor < -0.9999 ) ) ){
			//set delta value to 1
			dDeltaValue = 1.0;
		}
	}
	
	
	if ( dValue < pVariableDomain->getMaximum() ){
		//value lower maximum -> value can be increased
		if ( ! bCanIncreaseValue ){
			bCanIncreaseValue = true;
			emit increaseValuePossible( true );
		}
	}else{//value can not be increased
		if ( bCanIncreaseValue ){
			bCanIncreaseValue = false;
			emit increaseValuePossible( false );
		}
	}
	
	if ( pVariableDomain->getMaximum() < dValue ){
		//value bigger minimum -> value can be decreased
		if ( ! bCanDecreaseValue ){
			bCanDecreaseValue = true;
			emit decreaseValuePossible( true );
		}
	}else{//value can not be decreased
		if ( bCanDecreaseValue ){
			bCanDecreaseValue = false;
			emit decreaseValuePossible( false );
		}
	}
	
	//send input variable change event
	const eFibInputVariableChangedEvent fibInputVariableChangedEvent(
		this );
	sendInputVariableChange( &fibInputVariableChangedEvent );
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::setDomain( pInVariableDomain="<<pInVariableDomain<<") done"<<endl<<flush);
}


/**
 * @return the delta value by which the variable value is increased or
 * 	decreased
 * @see dDeltaValue
 * @see increaseValue()
 * @see decreaseValue()
 */
doubleFib cFibInputVariable::getDelta() const{
	
	return dDeltaValue;
}


/**
 * This method sets the delta value by which the variable value is
 * increased or decreased.
 *
 * @see dDeltaValue
 * @see increaseValue()
 * @see decreaseValue()
 * @param dInDeltaValue the new delta value to use
 */
void cFibInputVariable::setDelta( const doubleFib & dInDeltaValue ){
	
	if ( dDeltaValue == dInDeltaValue ){
		//nothing changed
		return;
	}
	dDeltaValue = dInDeltaValue;
	
	//send input variable change event
	const eFibInputVariableChangedEvent fibInputVariableChangedEvent(
		this );
	sendInputVariableChange( &fibInputVariableChangedEvent );
}


/**
 * @see increaseValue()
 * @see dValue
 * @see dDeltaValue
 * @see canDecreaseValue()
 * @return true if the value of the input variable can be increased else false
 */
bool cFibInputVariable::canIncreaseValue(){
	
	if ( pVariableDomain == NULL ){
		//no domain -> value can be increased
		if ( ! bCanIncreaseValue ){
			bCanIncreaseValue = true;
			emit increaseValuePossible( true );
		}
		return true;
	}//else
	if ( dValue < pVariableDomain->getMaximum() ){
		//value lower maximum -> value can be increased
		if ( ! bCanIncreaseValue ){
			bCanIncreaseValue = true;
			emit increaseValuePossible( true );
		}
		return true;
	}//else value can not be increased
	if ( bCanIncreaseValue ){
		bCanIncreaseValue = false;
		emit increaseValuePossible( false );
	}
	return false;
}


/**
 * @see increaseValue()
 * @see dValue
 * @see dDeltaValue
 * @see canDecreaseValue()
 * @return true if the value of the input variable can be decreased else false
 */
bool cFibInputVariable::canDecreaseValue(){
	
	if ( pVariableDomain == NULL ){
		//no domain -> value can be decreased
		if ( ! bCanDecreaseValue ){
			bCanDecreaseValue = true;
			emit increaseValuePossible( true );
		}
		return true;
	}//else
	if ( pVariableDomain->getMinimum() < dValue ){
		//value bigger minimum -> value can be decreased
		if ( ! bCanDecreaseValue ){
			bCanDecreaseValue = true;
			emit increaseValuePossible( true );
		}
		return true;
	}//else value can not be decreased
	if ( bCanDecreaseValue ){
		bCanDecreaseValue = false;
		emit increaseValuePossible( false );
	}
	return false;
}


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
QList< doubleFib > cFibInputVariable::getPossibleValues(
		const unsigned long ulMaxCount ) const{
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::getPossibleValues( ulMaxCount="<<ulMaxCount<<") called"<<endl<<flush);
	
	QList< doubleFib > liPossibleValues;
	if ( ulMaxCount == 0 ){
		//no values to return
		return liPossibleValues;
	}
	if ( pVariableDomain == NULL ){
		//return all values from 0 till ulMaxCount - 1
		for ( unsigned long ulActualValue = 0; ulActualValue < ulMaxCount;
				ulActualValue++ ){
			
			liPossibleValues.push_back( ulActualValue );
		}
		return liPossibleValues;
	}//else variable domain exists
	//TODO? what if value domain?
	
	//evalue values equaly spaced in the domain
	if ( ulMaxCount == 1 ){
		//just return the null value of the variabledomain
		liPossibleValues.push_back( pVariableDomain->getNull() );
		return liPossibleValues;
	}
	const doubleFib dMinimum = pVariableDomain->getMinimum();
	const doubleFib dMaximum = pVariableDomain->getMaximum();
	const doubleFib dWidth = dMaximum - dMinimum;
	const doubleFib dStepWidth = dWidth / ( (doubleFib)(ulMaxCount - 1) );
	
	const doubleFib dMaximumToCheck = dMaximum + dStepWidth;
	
	doubleFib dActualRounded = dMinimum;
	doubleFib dLastRounded = dMinimum - 1.0;
	for ( doubleFib dActualValue = dMinimum; dActualValue <= dMaximumToCheck;
			dActualValue += dStepWidth ){
		
		dActualRounded = pVariableDomain->round( dActualValue );
		if ( dActualRounded != dLastRounded ){
			//add the new value to the possible values
			liPossibleValues.push_back( dActualRounded );
			dLastRounded = dActualRounded;
		}
	}
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::getPossibleValues( ulMaxCount="<<ulMaxCount<<") done values to return "<<liPossibleValues.size()<<endl<<flush);
	return liPossibleValues;
}



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
bool cFibInputVariable::registerInputVariableChangeListener(
		lInputVariableChanged * pInputVariableListener ){
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::registerInputVariableChangeListener( pInputVariableListener="<<pInputVariableListener<<") called"<<endl<<flush);
	if ( pInputVariableListener == NULL ){
		//nothing to register
		return false;
	}
	const pair< set< lInputVariableChanged * >::iterator, bool > paListenerInserted =
		setInputVariableChangeListener.insert( pInputVariableListener );
	return paListenerInserted.second;
}


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
bool cFibInputVariable::unregisterInputVariableChangeListener(
		lInputVariableChanged * pInputVariableListener){
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::unregisterInputVariableChangeListener( pInputVariableListener="<<pInputVariableListener<<") called"<<endl<<flush);
	return ( 0 < setInputVariableChangeListener.erase( pInputVariableListener ) );
}


/**
 * This method sents a input variable changed event to all input variable
 * change listeners of this object.
 *
 * @see setInputVariableChangeListener
 * @see registerInputVariableChangeListener()
 * @see unregisterInputVariableChangeListener()
 * @param pFibInputVariableChangedEvent the change event to send
 */
void cFibInputVariable::sendInputVariableChange(
		const eFibInputVariableChangedEvent * pFibInputVariableChangedEvent ){
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this<<")::sendInputVariableChange( pFibInputVariableChangedEvent="<<pFibInputVariableChangedEvent<<") called"<<endl<<flush);
	for ( set< lInputVariableChanged * >::iterator
			itrChangeListener = setInputVariableChangeListener.begin();
			itrChangeListener != setInputVariableChangeListener.end();
			itrChangeListener++ ){
		
		(*itrChangeListener)->fibInputVariableChangedEvent(
			pFibInputVariableChangedEvent );
	}
}


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
bool cFibInputVariable::registerInputVariableValueChangeListener(
		lInputVariableValueChanged * pInputVariableValueListener ){
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this <<")::registerInputVariableValueChangeListener( pInputVariableValueListener="<<pInputVariableValueListener<<") called"<<endl<<flush);
	if ( pInputVariableValueListener == NULL ){
		//nothing to register
		return false;
	}
	const pair< set< lInputVariableValueChanged * >::iterator, bool > paListenerInserted =
		setInputVariableValueChangeListener.insert( pInputVariableValueListener );
	return paListenerInserted.second;
}


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
bool cFibInputVariable::unregisterInputVariableValueChangeListener(
		lInputVariableValueChanged * pInputVariableValueListener ){
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this <<")::unregisterInputVariableValueChangeListener( pInputVariableValueListener="<<pInputVariableValueListener<<") called"<<endl<<flush);
	return ( 0 < setInputVariableValueChangeListener.erase( pInputVariableValueListener ) );
}


/**
 * This method sents a input variable value changed event to all input
 * variable value change listeners of this object.
 *
 * @see setInputVariableValueChangeListener
 * @see registerInputVariableValueChangeListener()
 * @see unregisterInputVariableValueChangeListener()
 */
void cFibInputVariable::sendInputVariableValueChange(){
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this <<")::sendInputVariableValueChange() called"<<endl<<flush);
	for ( set< lInputVariableValueChanged * >::iterator
			itrChangeListener = setInputVariableValueChangeListener.begin();
			itrChangeListener != setInputVariableValueChangeListener.end();
			itrChangeListener++ ){
		
		(*itrChangeListener)->fibInputVariableValueChangedEvent( this );
	}
}


/**
 * This method will increase the value of the input variable (if possible).
 * ( dValue = max( dValue + dDeltaValue, maximum value )
 * @see pVariableDomain
 * @see dDeltaValue
 * @see decreaseValue()
 */
bool cFibInputVariable::increaseValue(){
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this <<")::increaseValue() called"<<endl<<flush);
	if ( ! bCanIncreaseValue ){
		return false;
	}
	//increase so that the variable changes
	doubleFib dNewValue = dValue + dDeltaValue;
	if ( pVariableDomain ){
		//TODO? what if the domain is a value domain
		//check that the variable is in the domain
		if ( dNewValue < pVariableDomain->getMaximum() ){
			//choose a bigger value in the domain
			while ( pVariableDomain->round( dNewValue ) <= dValue ){
				//while value not changed
				dNewValue += dDeltaValue;
			}
		}
		//choose a value in the domain
		dNewValue = pVariableDomain->round( dNewValue );
	}
	
	setValue( dNewValue );
	return true;
}


/**
 * This method will decrease the value of the input variable (if possible).
 * ( dValue = min( dValue - dDeltaValue, minimum value )
 * @see pVariableDomain
 * @see dDeltaValue
 * @see increaseValue()
 */
bool cFibInputVariable::decreaseValue(){
	
	DEBUG_OUT_L2(<<"cFibInputVariable("<<this <<")::decreaseValue() called"<<endl<<flush);
	if ( ! bCanDecreaseValue ){
		return false;
	}
	//decrease so that the variable changes
	doubleFib dNewValue = dValue - dDeltaValue;
	if ( pVariableDomain ){
		//TODO? what if the domain is a value domain
		//check that the variable is in the domain
		if ( pVariableDomain->getMinimum() < dNewValue ){
			//choose a lower value in the domain
			while ( dValue <= pVariableDomain->round( dNewValue ) ){
				//while value not changed
				dNewValue -= dDeltaValue;
			}
		}
		//choose a value in the domain
		dNewValue = pVariableDomain->round( dNewValue );
	}
	
	setValue( dNewValue );
	return true;
}






