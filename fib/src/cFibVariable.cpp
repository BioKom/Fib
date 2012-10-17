/**
 * @class cFibVariable
 * file name: cFibVariable.cpp
 * @author Betti Oesterholz
 * @date 02.05.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a Fib -variable.
 * Copyright (C) @c LGPL3 2009 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file contains the class for Fib -variables. Just Fib -elements
 * can create Fib -variables. A variable contains a value or is undefined.
 */
/*
History:
05.05.2009  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/


#include "cFibVariable.h"

#include "cFibElement.h"

using namespace fib;


/**
 * The constructor of the variable.
 *
 * @param definingFibElement the Fib -element that defines the variable
 */
cFibVariable::cFibVariable( cFibElement *definingFibElement ):
		variableType( UNDEFINED ), pDefiningFibElement( definingFibElement ){
}

/**
 * The copyconstructor of the variable.
 *
 * @param variable the Fib -element that should be copied
 */
cFibVariable::cFibVariable( const cFibVariable & variable,
		cFibElement *definingFibElement ):
		variableType( variable.variableType ),
		doubleValue( variable.doubleValue ),
		integerValue( variable.integerValue ),
		pDefiningFibElement( definingFibElement ){
	//nothing to do
	if ( pDefiningFibElement == NULL ){
		pDefiningFibElement = variable.pDefiningFibElement;
	}
}

/**
 * The destructor of the variable.
 */
cFibVariable::~cFibVariable(){
	
	DEBUG_OUT_L3(<<this<<"->~cFibVariable()"<<endl);
	
	//delete this variable from all using elements
	while ( ! setUsingElements.empty() ){
		
		set<iVariableUser*>::iterator itrUsingElement = setUsingElements.begin();
		if ( *itrUsingElement != NULL ){
			DEBUG_OUT_L3(<<"call "<<(*itrUsingElement)<<"->deleteVariable( "<< this <<" )"<<endl<<flush);
			
			(*itrUsingElement)->deleteVariable( this );
		}
		setUsingElements.erase( itrUsingElement );
	}
}



/**
 * This method registers an Fib -element that uses the variable.
 *
 * @param usingElement the Fib -element that uses the variable
 */
void cFibVariable::registerUsingElement( iVariableUser * usingElement ){

	DEBUG_OUT_L3(<<this<<"->cFibVariable::registerUsingElement( "<< usingElement <<" )"<<endl);
	
	setUsingElements.insert( usingElement );
}


/**
 * This method unregisters an Fib -element that don't uses the variable
 * anymore.
 *
 * @param usingElement the Fib -element that don't uses the variable
 * 	anymore
 */
void cFibVariable::unregisterUsingElement( iVariableUser * usingElement ){

	DEBUG_OUT_L3(<<this<<"->cFibVariable::unregisterUsingElement( "<< usingElement <<" )"<<endl);
	
	setUsingElements.erase( usingElement );
}


/**
 * This method returns the value of the variable as an real value.
 * It returns 0 if the variable is undefined.
 *
 * @return the value of the variable or 0 if the variable is undefined
 */
doubleFib cFibVariable::getValue() const{

	if ( variableType == REAL_VALUE ){
		//return real value
		return doubleValue;
		
	}else if ( variableType == INTEGER_VALUE ){
		//return integer value
		return (doubleFib)( integerValue );
		
	}// else UNDEFINED
	return (doubleFib)( 0.0 );
}


/**
 * This method returns the value of the variable as an integer value.
 * It returns 0 if the variable is undefined. If the value of the
 * variable is an real value, the value is rounded to an integervalue.
 *
 * @return the value of the variable or 0 if the variable is undefined
 */
longFib cFibVariable::getIntegerValue() const{

	if ( variableType == REAL_VALUE ){
		//return real value
		return roundToLongFib( doubleValue );
		
	}else if ( variableType == INTEGER_VALUE ){
		//return integer value
		return integerValue;
		
	}// else UNDEFINED
	return (longFib)(0);
}


/**
 * This method sets the value of the variable as an real value.
 *
 * @param dValue the value of the variable to set
 */
void cFibVariable::setValue( const doubleFib dValue ){
	doubleValue  = dValue;
	variableType = REAL_VALUE;
}


/**
 * This method sets the value of the variable as an integer value.
 *
 * @param lValue the value of the variable to set
 */
void cFibVariable::setIntegerValue( const longFib lValue ){
	integerValue = lValue;
	variableType = INTEGER_VALUE;
}


/**
 * This method returns a pointer to the Fib -element that defines the
 * variable.
 *
 * @return a pointer to  the Fib -element that defines the variable
 */
cFibElement *cFibVariable::getDefiningElement( ) const{
	return pDefiningFibElement;
}


/**
 * This method returns the number of Fib -elements that uses the
 * variable. These have to be registered befor.
 *
 * @return the number of Fib -elements that uses the variable
 */
unsignedIntFib cFibVariable::getNumberOfUsingElements( ) const{
	return (unsignedIntFib) setUsingElements.size();
}


/**
 * This method returns a set of Fib -elements that uses the variable.
 * These have to be registered befor.
 *
 * @return a set Fib -elements that uses the variable
 */
set<cFibElement*> cFibVariable::getUsingElements() const{

	set<cFibElement*> setUsingFibElements;
	for ( set<iVariableUser*>::const_iterator itrUsingElement =
			setUsingElements.begin(); 
			itrUsingElement != setUsingElements.end(); itrUsingElement++ ){
		
		setUsingFibElements.insert(
			(*itrUsingElement)->getVariableUsingFibElement() );
	}

	return setUsingFibElements;
}

/**
 * @return if the value of the variable was set true is returned, else false
 */
bool cFibVariable::isSet() const{
	
	if ( variableType == UNDEFINED ){
		return false;
	}//else
	return true;
}

/**
 * @return if the value is an integer value true, else false
 */
bool cFibVariable::isIntegerValue() const{
	
	if ( variableType == INTEGER_VALUE ){
		return true;
	}//else
	return false;
}


#ifdef FEATURE_EQUAL_FIB_OBJECT

/**
 * This Method checks if the given variable is equal to this variable.
 *
 * @param variable the variable to compare with this variable
 * @param bCheckExternalObjects if true the external objects of
 * 	cExtObject will be compared
 * @return true if the given variable is equal to this variable, else false
 */
bool cFibVariable::equal( const cFibVariable &variable,
		const bool bCheckExternalObjects ) const{
	
	map< const cRoot *, const cRoot * > mapEqualRootObjects;
	map< const cFibElement *, const cFibElement * > mapEqualDefinedVariables;
	
	return equalInternal( variable,
		mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
}


/**
 * This Method checks if the given variable is equal to this variable.
 *
 * @param variable the variable to compare with this variable
 * @return true if the given variable is equal to this variable, else false
 */
bool cFibVariable::operator==( const cFibVariable &variable ) const{
	
	map< const cRoot *, const cRoot * > mapEqualRootObjects;
	map< const cFibElement *, const cFibElement * > mapEqualDefinedVariables;
	
	return equalInternal( variable,
		mapEqualRootObjects, mapEqualDefinedVariables, true );
}


/**
 * This Method checks if the given variable is equal to this variable.
 *
 * @param variable the variable to compare with this variable
 * @param mapEqualRootObjects the root objects of this object that wher
 * 	already checked as equal
 * 	map entries:
 * 		key: the root-element of this Fib object that was checked
 * 		value: the to the key correspondending root-element of the
 * 			fibObject that was checked and which is equal to the key
 * 		root-element
 * 	(it is empty if bCheckExternalObjects == false)
 * @param mapEqualDefinedVariables the Fib elements that defines
 * 	variables and are equal;
 * 	map entries:
 * 		key: the Fib element of this Fib object that was checked
 * 		value: the to the key correspondending Fib element of the
 * 			fibObject that was checked and which sets its defined
 * 			variables to the same values as the key Fib element
 * @param bCheckExternalObjects if true the external objects of
 * 	cExtObject will be compared
 * @return true if the given variable is equal to this variable, else false
 */
bool cFibVariable::equalInternal( const cFibVariable &variable,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	/*don't compare the value of the variable, because for a variable the
	value can change without changing the variable;
	The variable yust dependends on the defining element and the values it
	can give the variable*/
	if ( (pDefiningFibElement == NULL) || (variable.pDefiningFibElement == NULL) ){
		if ( pDefiningFibElement == variable.pDefiningFibElement ){
			//both pDefiningFibElement are NULL
			return true;
		}//else
		return false;
	}
	
	return pDefiningFibElement->equalValuesSetInternal( this,
		*(variable.pDefiningFibElement), &variable,
		mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This Method checks if the given variable is equal to this variable.
 *
 * @param variable the variable to compare with this variable
 * @return true if the given variable is equal to this variable, else false
 */
bool cFibVariable::equal( const cFibVariable &variable ) const{
	return ((*this) == variable);
}

/**
 * This Method checks if the given variable is equal to this variable.
 *
 * @param variable the variable to compare with this variable
 * @return true if the given variable is equal to this variable, else false
 */
bool cFibVariable::operator==( const cFibVariable &variable ) const{
	
	/*don't compare the value of the variable, because for a variable the
	value can change without changing the variable;
	The variable yust dependends on the defining element and the values it
	can give the variable*/
	if ( (pDefiningFibElement == NULL) || (variable.pDefiningFibElement == NULL) ){
		if ( pDefiningFibElement == variable.pDefiningFibElement ){
			//both pDefiningFibElement are NULL
			return true;
		}//else
		return false;
	}
	return pDefiningFibElement->equalValuesSet( this,
		*(variable.pDefiningFibElement), &variable );
}

#endif //FEATURE_EQUAL_FIB_OBJECT


/**
 * This Method maks this variable equal to the given variable.
 *
 * @param variable the variable to copy
 */
cFibVariable & cFibVariable::operator=( const cFibVariable &variable ){

	variableType = variable.variableType;
	doubleValue = variable.doubleValue;
	integerValue = variable.integerValue;
	pDefiningFibElement = variable.pDefiningFibElement;
	return (*this);
}








