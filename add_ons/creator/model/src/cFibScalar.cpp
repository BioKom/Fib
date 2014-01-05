
//TODO check

/**
 * @file cFibScalar
 * file name: cFibScalar.cpp
 * @author Betti Oesterholz
 * @date 16.08.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++, Qt4
 *
 * This file implements the basis class for a scalar in a Fib object.
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
 * This file implements the basis class for a scalar in a Fib object.
 * For every scalar value or scalar in a Fib element a child of this
 * class can be used.
 * It helps the Fib creator applictaion to handle scalars in Fib objects.
 * (e. g. notify for value changes)
 *
 *
 * @see cFibElement
 * @see cDomainSingle
 */
/*
History:
21.11.2013  Oesterholz  created
*/



//TODO switches for test proposes
#define DEBUG


#include "cFibScalar.h"

#include "cDomainIntegerBasis.h"
#include "cDomainRationalBasis.h"

#include "cWidgetFibScalar.h"


using namespace fib::nCreator;
using namespace fib;


/**
 * The parameter constructor for a scalar.
 *
 * @param dInValue the value for the scalar
 * 	@see assignValue()
 * @param strInScalarName the name of the scalar
 * 	@see strScalarName
 * @param pInScalarDomain a pointer to the domain for the scalar
 * 	Beware: This object will delete the given object on destruction.
 */
cFibScalar::cFibScalar( const doubleFib dInValue, const QString strInScalarName,
		cDomainSingle * pInScalarDomain ): dValue( dInValue ),
		strScalarName( strInScalarName ), pScalarDomain( NULL ) {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::cFibScalar( dInValue="<<dInValue<<", strInScalarName="<<strInScalarName.toStdString()<<", pInScalarDomain="<<pInScalarDomain<<") called"<<endl<<flush);
	setDomain( pInScalarDomain );//also sets dDeltaValue
}


/**
 * The copy constructor for a scalar.
 *
 * @param fibScalar a reference to the scalar, which to copy
 */
cFibScalar::cFibScalar( const cFibScalar & fibScalar ):
		QObject( fibScalar.parent() ),
		dValue( fibScalar.dValue ),
		pScalarDomain( fibScalar.pScalarDomain ),
		dDeltaValue( fibScalar.dDeltaValue ) {
	//nothing to do
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::cFibScalar( fibScalar ) called"<<endl<<flush);
}


/**
 * destructor
 */
cFibScalar::~cFibScalar() {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::~cFibScalar() called"<<endl<<flush);
	//send scalar change event
	eFibScalarChangedEvent fibScalarChangedEvent(
		this );
	fibScalarChangedEvent.bScalarDeleted = true;
	
	sendScalarChange( &fibScalarChangedEvent );
	//delete scalar domain
	if ( pScalarDomain ) {
		delete pScalarDomain;
	}
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::~cFibScalar() done"<<endl<<flush);
}


/**
 * This method clones this object.
 *
 * @return a pointer to the clone of this object
 */
cFibScalar * cFibScalar::clone() const{
	
	return new cFibScalar( *this );
}


/**
 * @return the name of this class "cFibScalar"
 */
std::string cFibScalar::getName() const{
	
	return string( "cFibScalar" );
}


/**
 * @see setValue()
 * @see dValue
 * @see assignValue()
 * @return the value for the scalar
 */
doubleFib cFibScalar::getValue() const{
	
	return dValue;
}


/**
 * This method sets the value for the scalar.
 * If a value is outside the domain pScalarDomain are given, it will
 * be rounded to the next value inside the domain.
 *
 * @see assignValue()
 * @see dValue
 * @see getValue()
 * @see cDomainSingle::round()
 * @param dInValue the value to set for the scalar
 */
void cFibScalar::setValue( const doubleFib & dInValue ) {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::setValue( dInValue="<<dInValue<<") called"<<endl<<flush);
	if ( dValue == dInValue ) {
		//value not changed
		DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::setValue( dInValue="<<dInValue<<") done: value not changed"<<endl<<flush);
		return;
	}
	dValue = dInValue;
	
	if ( pScalarDomain ) {
		DEBUG_OUT_L3(<<"cFibScalar("<<this<<")::setValue( dInValue="<<dInValue<<") scalar domain exists"<<endl<<flush);
		if ( dValue < pScalarDomain->getMaximum() ) {
			//value lower maximum -> value can be increased
			if ( ! bCanIncreaseValue ) {
				bCanIncreaseValue = true;
				emit increaseValuePossible( true );
			}
		}else{//value can not be increased
			if ( bCanIncreaseValue ) {
				bCanIncreaseValue = false;
				emit increaseValuePossible( false );
			}
		}
		
		if ( pScalarDomain->getMinimum() < dValue ) {
			//value bigger minimum -> value can be decreased
			if ( ! bCanDecreaseValue ) {
				bCanDecreaseValue = true;
				emit decreaseValuePossible( true );
			}
		}else{//value can not be decreased
			if ( bCanDecreaseValue ) {
				bCanDecreaseValue = false;
				emit decreaseValuePossible( false );
			}
		}
	}//end if scalar domain exists
	
	DEBUG_OUT_L3(<<"cFibScalar("<<this<<")::setValue( dInValue="<<dInValue<<") send scalar change event"<<endl<<flush);
	
	//send scalar change event
	emit scalarValueChanged( dValue );
	const eFibScalarChangedEvent fibScalarChangedEvent(
		this );
	sendScalarChange( &fibScalarChangedEvent );
	sendScalarValueChange();
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::setValue( dInValue="<<dInValue<<") done"<<endl<<flush);
}


/**
 * @return the name of the scalar
 * 	@see strScalarName
 */
QString cFibScalar::getScalarName() const{
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::getScalarName() =\""<<strScalarName.toStdString()<<"\" called"<<endl<<flush);
	return strScalarName;
}


/**
 * This method sets the name of the scalar to the given name.
 *
 * @see strScalarName
 * @param strName the name of the scalar should have
 */
void cFibScalar::setScalarName( const QString & strName ) {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::setScalarName( strName=\""<<strName.toStdString()<<"\" )  called"<<endl<<flush);
	strScalarName = strName;
	
	//send scalar change event
	const eFibScalarChangedEvent fibScalarChangedEvent(
		this );
	sendScalarChange( &fibScalarChangedEvent );
}


/**
 * This method returns a pointer to the domain for the scalar.
 *
 * @see pScalarDomain
 * @see setDomain()
 * @return a pointer to the domain for the scalar, or the null
 * 	pointer NULL if non exists
 */
const cDomainSingle * cFibScalar::getDomain() const{
	
	return pScalarDomain;
}


/**
 * This method sets domain for the scalar.
 * Note: This method will reset the delta value dDeltaValue and
 * 	delete the old domain if existing.
 *
 * @see pScalarDomain
 * @see setDomain()
 * @see dDeltaValue
 * @param pInScalarDomain a pointer to the domain for the scalar,
 * 	or the null pointer NULL if non should exists
 * 	Beware: This object will delete the given object on destruction.
 */
void cFibScalar::setDomain( cDomainSingle * pInScalarDomain ) {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::setDomain( pInScalarDomain="<<pInScalarDomain<<") called"<<endl<<flush);
	if ( pScalarDomain ) {
		if ( ( pInScalarDomain != NULL ) &&
				pScalarDomain->equal( * pInScalarDomain ) ) {
			//domains allready equal -> do nothing
			DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::setDomain( pInScalarDomain="<<pInScalarDomain<<") done domains allready equal -> don nothing"<<endl<<flush);
			delete pInScalarDomain;
			return;
		}//else delete old domain
		delete pScalarDomain;
	}
	
	pScalarDomain = pInScalarDomain;
	//evalue a good delta value
	if ( pScalarDomain == NULL ) {
		//no domain -> delta is standard value 1
		dDeltaValue = 1.0;
		
		//all values now possible
		if ( ! bCanIncreaseValue ) {
			bCanIncreaseValue = true;
			emit increaseValuePossible( true );
		}
		if ( ! bCanDecreaseValue ) {
			bCanDecreaseValue = true;
			emit decreaseValuePossible( true );
		}
		return;
	}//else pScalarDomain exists
	const doubleFib dMaximum = pScalarDomain->getMaximum();
	const doubleFib dMinimum = pScalarDomain->getMinimum();
	
	doubleFib dScalingFactor = 1.0;
	
	const string szDomainType = pScalarDomain->getType();
	if ( ( szDomainType.compare( 0, 19, "DomainNaturalNumber") == 0 ) ||
			( szDomainType.compare( 0, 13, "DomainInteger") == 0 ) ) {
		//if the first domain is an integer number domain
		dScalingFactor = ((cDomainIntegerBasis*)pScalarDomain)->getScalingFactor();
	
	}else if ( szDomainType.compare( 0, 19, "cDomainRational") == 0 ) {
		//if the first domain is an rational number domain
		/*set the exponent to the maximum and evalue the difference betwean
		 a minimal mantissa increas*/
		const cDomainRationalBasis * pScalarIntegerDomain =
			((cDomainRationalBasis*)pScalarDomain);
		
		const cDomainIntegerBasis * pMantissaDomain =
			pScalarIntegerDomain->getMantissaDomain();
		const cDomainIntegerBasis * pExponentDomain =
			pScalarIntegerDomain->getExponentDomain();
		
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
	
	if ( ( 0.9 < dDeltaValue ) && ( dDeltaValue < 1.1 ) ) {
		//check if 1 is a multiple of the scaling factor
		if ( ( ( 0.9999 < dScalingFactor ) && ( dScalingFactor < 1.0001 ) ) ||
				( ( -1.0001 < dScalingFactor ) && ( dScalingFactor < -0.9999 ) ) ) {
			//set delta value to 1
			dDeltaValue = 1.0;
		}
	}
	
	
	if ( dValue < pScalarDomain->getMaximum() ) {
		//value lower maximum -> value can be increased
		if ( ! bCanIncreaseValue ) {
			bCanIncreaseValue = true;
			emit increaseValuePossible( true );
		}
	}else{//value can not be increased
		if ( bCanIncreaseValue ) {
			bCanIncreaseValue = false;
			emit increaseValuePossible( false );
		}
	}
	
	if ( pScalarDomain->getMaximum() < dValue ) {
		//value bigger minimum -> value can be decreased
		if ( ! bCanDecreaseValue ) {
			bCanDecreaseValue = true;
			emit decreaseValuePossible( true );
		}
	}else{//value can not be decreased
		if ( bCanDecreaseValue ) {
			bCanDecreaseValue = false;
			emit decreaseValuePossible( false );
		}
	}
	
	//send scalar change event
	const eFibScalarChangedEvent fibScalarChangedEvent(
		this );
	sendScalarChange( &fibScalarChangedEvent );
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::setDomain( pInScalarDomain="<<pInScalarDomain<<") done"<<endl<<flush);
}


/**
 * @return the delta value by which the scalar value is increased or
 * 	decreased
 * @see dDeltaValue
 * @see increaseValue()
 * @see decreaseValue()
 */
doubleFib cFibScalar::getDelta() const{
	
	return dDeltaValue;
}


/**
 * This method sets the delta value by which the scalar value is
 * increased or decreased.
 *
 * @see dDeltaValue
 * @see increaseValue()
 * @see decreaseValue()
 * @param dInDeltaValue the new delta value to use
 */
void cFibScalar::setDelta( const doubleFib & dInDeltaValue ) {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::setDelta( dInDeltaValue="<<dInDeltaValue<<" )  called"<<endl<<flush);
	if ( dDeltaValue == dInDeltaValue ) {
		//nothing changed
		return;
	}
	dDeltaValue = dInDeltaValue;
	
	//send scalar change event
	const eFibScalarChangedEvent fibScalarChangedEvent(
		this );
	sendScalarChange( &fibScalarChangedEvent );
}


/**
 * @see increaseValue()
 * @see dValue
 * @see dDeltaValue
 * @see canDecreaseValue()
 * @return true if the value of the scalar can be increased else false
 */
bool cFibScalar::canIncreaseValue() {
	
	if ( pScalarDomain == NULL ) {
		//no domain -> value can be increased
		if ( ! bCanIncreaseValue ) {
			bCanIncreaseValue = true;
			emit increaseValuePossible( true );
		}
		return true;
	}//else
	if ( dValue < pScalarDomain->getMaximum() ) {
		//value lower maximum -> value can be increased
		if ( ! bCanIncreaseValue ) {
			bCanIncreaseValue = true;
			emit increaseValuePossible( true );
		}
		return true;
	}//else value can not be increased
	if ( bCanIncreaseValue ) {
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
 * @return true if the value of the scalar can be decreased else false
 */
bool cFibScalar::canDecreaseValue() {
	
	if ( pScalarDomain == NULL ) {
		//no domain -> value can be decreased
		if ( ! bCanDecreaseValue ) {
			bCanDecreaseValue = true;
			emit increaseValuePossible( true );
		}
		return true;
	}//else
	if ( pScalarDomain->getMinimum() < dValue ) {
		//value bigger minimum -> value can be decreased
		if ( ! bCanDecreaseValue ) {
			bCanDecreaseValue = true;
			emit increaseValuePossible( true );
		}
		return true;
	}//else value can not be decreased
	if ( bCanDecreaseValue ) {
		bCanDecreaseValue = false;
		emit increaseValuePossible( false );
	}
	return false;
}


/**
 * This method returns possible values for the scalar.
 * It will return maximal ulMaxCount values, but can return less.
 * Also it will try to space the values evenly across the domain for
 * the scalar.
 *
 * @see pScalarDomain
 * @see dDeltaValue
 * @see decreaseValue()
 * @see increaseValue()
 * @return a list with maximal ulMaxCount values to which the scalar can be set
 */
QList< doubleFib > cFibScalar::getPossibleValues(
		const unsigned long ulMaxCount ) const{
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::getPossibleValues( ulMaxCount="<<ulMaxCount<<") called"<<endl<<flush);
	
	QList< doubleFib > liPossibleValues;
	if ( ulMaxCount == 0 ) {
		//no values to return
		return liPossibleValues;
	}
	if ( pScalarDomain == NULL ) {
		//return all values from 0 till ulMaxCount - 1
		for ( unsigned long ulActualValue = 0; ulActualValue < ulMaxCount;
				ulActualValue++ ) {
			
			liPossibleValues.push_back( ulActualValue );
		}
		return liPossibleValues;
	}//else scalar domain exists
	//TODO? what if value domain?
	
	//evalue values equaly spaced in the domain
	if ( ulMaxCount == 1 ) {
		//just return the null value of the scalar domain
		liPossibleValues.push_back( pScalarDomain->getNull() );
		return liPossibleValues;
	}
	const doubleFib dMinimum = pScalarDomain->getMinimum();
	const doubleFib dMaximum = pScalarDomain->getMaximum();
	const doubleFib dWidth = dMaximum - dMinimum;
	const doubleFib dStepWidth = dWidth / ( (doubleFib)(ulMaxCount - 1) );
	
	const doubleFib dMaximumToCheck = dMaximum + dStepWidth;
	
	doubleFib dActualRounded = dMinimum;
	doubleFib dLastRounded = dMinimum - 1.0;
	for ( doubleFib dActualValue = dMinimum; dActualValue <= dMaximumToCheck;
			dActualValue += dStepWidth ) {
		
		dActualRounded = pScalarDomain->round( dActualValue );
		if ( dActualRounded != dLastRounded ) {
			//add the new value to the possible values
			liPossibleValues.push_back( dActualRounded );
			dLastRounded = dActualRounded;
		}
	}
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::getPossibleValues( ulMaxCount="<<ulMaxCount<<") done values to return "<<liPossibleValues.size()<<endl<<flush);
	return liPossibleValues;
}



/**
 * With this function you can register a listeners for changes in this
 * scalar.
 *
 * @see unregisterScalarChangeListener()
 * @see setScalarChangeListener
 * @see sendScalarChange()
 * @param pScalarListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibScalar::registerScalarChangeListener(
		lScalarChanged * pScalarListener ) {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::registerScalarChangeListener( pScalarListener="<<pScalarListener<<") called"<<endl<<flush);
	if ( pScalarListener == NULL ) {
		//nothing to register
		return false;
	}
	const pair< set< lScalarChanged * >::iterator, bool > paListenerInserted =
		setScalarChangeListener.insert( pScalarListener );
	return paListenerInserted.second;
}


/**
 * With this function you can unregister a listeners for changes in this
 * scalar.
 *
 * @see registerScalarChangeListener()
 * @see setScalarChangeListener
 * @see sendScalarChange()
 * @param pScalarListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibScalar::unregisterScalarChangeListener(
		lScalarChanged * pScalarListener ) {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::unregisterScalarChangeListener( pScalarListener="<<pScalarListener<<") called"<<endl<<flush);
	return ( 0 < setScalarChangeListener.erase( pScalarListener ) );
}


/**
 * This method sents a scalar changed event to all scalar
 * change listeners of this object.
 *
 * @see setScalarChangeListener
 * @see registerScalarChangeListener()
 * @see unregisterScalarChangeListener()
 * @param pFibScalarChangedEvent the change event to send
 */
void cFibScalar::sendScalarChange(
		const eFibScalarChangedEvent * pFibScalarChangedEvent ) {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::sendScalarChange( pFibScalarChangedEvent="<<pFibScalarChangedEvent<<") called"<<endl<<flush);
	for ( set< lScalarChanged * >::iterator
			itrChangeListener = setScalarChangeListener.begin();
			itrChangeListener != setScalarChangeListener.end();
			itrChangeListener++ ) {
		
		(*itrChangeListener)->fibScalarChangedEvent(
			pFibScalarChangedEvent );
	}
}


/**
 * With this function you can register a listeners for changes of this
 * scalar value.
 *
 * @see unregisterScalarValueChangeListener()
 * @see setScalarValueChangeListener
 * @see sendScalarValueChange()
 * @param pScalarValueListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibScalar::registerScalarValueChangeListener(
		lScalarValueChanged * pScalarValueListener ) {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this <<")::registerScalarValueChangeListener( pScalarValueListener="<<pScalarValueListener<<") called"<<endl<<flush);
	if ( pScalarValueListener == NULL ) {
		//nothing to register
		return false;
	}
	const pair< set< lScalarValueChanged * >::iterator, bool > paListenerInserted =
		setScalarValueChangeListener.insert( pScalarValueListener );
	return paListenerInserted.second;
}


/**
 * With this function you can unregister a listeners for changes of this
 * scalar value.
 *
 * @see registerScalarValueChangeListener()
 * @see setScalarValueChangeListener
 * @see sendScalarValueChange()
 * @param pScalarValueListener a pointer to the listener for changes
 * @return true if the listener was registered, else false
 */
bool cFibScalar::unregisterScalarValueChangeListener(
		lScalarValueChanged * pScalarValueListener ) {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this <<")::unregisterScalarValueChangeListener( pScalarValueListener="<<pScalarValueListener<<") called"<<endl<<flush);
	return ( 0 < setScalarValueChangeListener.erase( pScalarValueListener ) );
}


/**
 * This method sents a scalar value changed event to all scalar value
 * change listeners of this object.
 *
 * @see setScalarValueChangeListener
 * @see registerScalarValueChangeListener()
 * @see unregisterScalarValueChangeListener()
 */
void cFibScalar::sendScalarValueChange() {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this <<")::sendScalarValueChange() called"<<endl<<flush);
	for ( set< lScalarValueChanged * >::iterator
			itrChangeListener = setScalarValueChangeListener.begin();
			itrChangeListener != setScalarValueChangeListener.end();
			itrChangeListener++ ) {
		
		(*itrChangeListener)->fibScalarValueChangedEvent( this );
	}
}


/**
 * This method will create a widget, which displays this object.
 * ATTENTION: You have to care that the returned widget is deleted.
 *
 * @param pParent a pointer the parent of this new Fib scalar widget
 * @return a pointer to the created widget, or NULL if non could be created
 */
QWidget * cFibScalar::getWidget( QWidget * pParent ) {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this<<")::getWidget( pParent="<<pParent<<" )  called"<<endl<<flush);
	return new cWidgetFibScalar( this, pParent );
}



/**
 * This method will increase the value of the scalar (if possible).
 * ( dValue = max( dValue + dDeltaValue, maximum value )
 * @see pScalarDomain
 * @see dDeltaValue
 * @see decreaseValue()
 */
bool cFibScalar::increaseValue() {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this <<")::increaseValue() called"<<endl<<flush);
	if ( ! bCanIncreaseValue ) {
		return false;
	}
	//increase so that the scalar changes
	doubleFib dNewValue = dValue + dDeltaValue;
	if ( pScalarDomain ) {
		//TODO? what if the domain is a value domain
		//check that the scalar is in the domain
		if ( dNewValue < pScalarDomain->getMaximum() ) {
			//choose a bigger value in the domain
			while ( pScalarDomain->round( dNewValue ) <= dValue ) {
				//while value not changed
				dNewValue += dDeltaValue;
			}
		}
		//choose a value in the domain
		dNewValue = pScalarDomain->round( dNewValue );
	}
	
	setValue( dNewValue );
	return true;
}


/**
 * This method will decrease the value of the scalar (if possible).
 * ( dValue = min( dValue - dDeltaValue, minimum value )
 * @see pScalarDomain
 * @see dDeltaValue
 * @see increaseValue()
 */
bool cFibScalar::decreaseValue() {
	
	DEBUG_OUT_L2(<<"cFibScalar("<<this <<")::decreaseValue() called"<<endl<<flush);
	if ( ! bCanDecreaseValue ) {
		return false;
	}
	//decrease so that the scalar changes
	doubleFib dNewValue = dValue - dDeltaValue;
	if ( pScalarDomain ) {
		//TODO? what if the domain is a value domain
		//check that the scalar is in the domain
		if ( pScalarDomain->getMinimum() < dNewValue ) {
			//choose a lower value in the domain
			while ( dValue <= pScalarDomain->round( dNewValue ) ) {
				//while value not changed
				dNewValue -= dDeltaValue;
			}
		}
		//choose a value in the domain
		dNewValue = pScalarDomain->round( dNewValue );
	}
	
	setValue( dNewValue );
	return true;
}






