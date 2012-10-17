/**
 * @class cFunctionOneValue
 * file name: cFunctionOneValue.h
 * @author Betti Oesterholz
 * @date 08.05.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents the basisclass for all one value underfunctions.
 * Copyright (C) @c LGPL3 2010 Betti Oesterholz
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
 * This class represents the basisclass for all one value underfunction.
 * From this class all classes are derived, which represent function,
 * which work on one input values.
 *
 */
/*
History:
08.05.2010  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/

#ifndef ___C_FUNCTION_ONE_VALUE_H__
#define ___C_FUNCTION_ONE_VALUE_H__


#include "version.h"
#include "fibDatatyps.h"
#include "cReadBits.h"

#include "cUnderFunction.h"


using std::set;

namespace fib{


class cFunctionOneValue: public cUnderFunction{

protected:
	
	/**
	 * The first underfunction for the function.
	 */
	cUnderFunction * pUnderfunction;

public:


	/**
	 * The constructor of the underfunction.
	 *
	 * @param pUnderfunction a pointer to the underfunction for the function
	 * 	(a clone of the underfunction will be taken as the underfunction of
	 * 	this function; this is a pointer, so that this constructor didn't
	 * 	gets confused with the copy constructor) @see pUnderfunction
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	new underfunction
	 * @param pInDefiningFibElement the fib -element which defines/ uses
	 * 	the new underfunction
	 */
	cFunctionOneValue( const cUnderFunction * const pUnderfunction,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement * pInDefiningFibElement = NULL );

	/**
	 * The copy constructor of the underfunction.
	 * This constructor will also copy the underfunctions of the given
	 * function.
	 *
	 * @param underfunction the underfunction which to copy
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	new underfunction
	 * @param pInDefiningFibElement the fib -element which defines/ uses
	 * 	the new underfunction
	 */
	cFunctionOneValue( const cFunctionOneValue & underfunction,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement *pInDefiningFibElement = NULL );

	/**
	 * The constructor for restoring a value underfunction from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node the underfunction is stored in
	 * @param outStatus An reference to an integervalue where the errorvalue
	 * 	can be stored to.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore fib -element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	new underfunction
	 * @param pInDefiningFibElement the fib -element which defines/ uses
	 * 	the new underfunction
	 */
	cFunctionOneValue( const TiXmlElement * pXmlElement, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement * pInDefiningFibElement = NULL );

	/**
	 * This constructor restores a value underfunction from the stream
	 * where it is stored in the compressed fib -format.
	 * Beware: The bits for the functiontype should be allready readed, this
	 * 	constructor reads yust the one underfunctions.
	 *
	 * @param iBitStream the stream where this underfunction is stored to in,
	 * 	because this stream is an cReadBits, any number of bits can be
	 * 	readed from it
	 * @param outStatus An reference to an integervalue where the errorvalue
	 * 	can be stored to. If the pointer is NULL no errorvalue will be
	 * 	given back.
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid stream
	 * 		- -2 loading error, invalid data in stream
	 * 		- 1 loading warning, invalid data in stream, error could be corrected
	 * 		- 2 loading warning, invalid data in stream, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore fib -element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @param pInDomainValue the domain for value underfunction
	 * @param pInDomainVariable the domain for variables
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	new underfunction
	 * @param pInDefiningFibElement the fib -element which defines/ uses
	 * 	the new underfunction
	 */
	cFunctionOneValue( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement * pInDefiningFibElement = NULL );


	/**
	 * The destructor of the underfunction.
	 */
	virtual ~cFunctionOneValue();

	/**
	 * @return This method returns a pointer to the underfunction of
	 * 	this function. @see pUnderfunction
	 */
	cUnderFunction * getUnderFunction();
	
	/**
	 * This methods sets the underfunction of this function.
	 *
	 * @see pUnderfunction
	 * @param underFunction the underfunction, which should be set as the
	 * 	underfunction of this function; the underfunction will be
	 * 	copied and the copy will be inserted
	 * @param bDeleteOld if true the old underfunction will be deleted from
	 * 	memory, else the old underfunction should be deleted elswher
	 */
	void setUnderFunction( const cUnderFunction & underFunction,
		bool bDeleteOld=true );
	
	/**
	 * This method returns if this underfunction is valid, else false.
	 * All values in the underfunction and it's underfunctions must be
	 * inside the underfunction domain. All variables must be defined over
	 * this underfunction.
	 * No underfunction should contain itselfor should be contained in one
	 * of its underfunctions (no cycles allowed).
	 *
	 * @return true if this underfunction is valid, else false
	 */
	virtual bool isValid() const;

	/**
	 * This method checks if the given variable is used in this underfunction.
	 *
	 * @see cFibVariable
	 * @param variable the variable to check if it is used
	 * @return true if the variable is used, else false
	 */
	virtual bool isUsedVariable( const cFibVariable * variable ) const;
	
	/**
	 * This method returns all variables used in this underfunction.
	 *
	 * @see cFibVariable
	 * @return all variables used in this underfunction
	 */
	virtual set<cFibVariable*> getUsedVariables();

	/**
	 * This method replace the variable variableOld with the variable
	 * variableNew in the underfunction.
	 *
	 * @see cFibVariable
	 * @see isVariable()
	 * @see isUsedVariable()
	 * @param variableOld the variable to replace
	 * @param variableNew the variable with which the variable variableOld
	 * 	is to replace
	 * @return true if the variable variableOld is replaced with variableNew,
	 * 	else false
	 */
	virtual bool replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew );

	/**
	 * @return the number of underfunctions, a underfunction of this type has
	 */
	virtual unsignedIntFib getNumberOfUnderFunctions() const;
	
	/**
	 * Sets the Fib -element which defines/ uses this underfunction.
	 * If the given pointer is the nullpointer (standardvalue), no
	 * Fib -element defines this underfunction.
	 *
	 * @param definingFibElement a pointer to the Fib -element which
	 * 	defines/ uses this underfunction
	 * @param bCheckDomains getthe domains of the defining element and
	 * 	check the underfunctionelements with it
	 */
	virtual void setDefiningFibElement( cFibElement *fibElement=NULL,
		bool bCheckDomains=true );

	/**
	 * This method evaluades a value for the time needed to evalue the
	 * underfunction.
	 * This value should not exceed lMaxTime, if the value for the time
	 * is greater than lMaxTime the evaluation will be stopt and lMaxTime
	 * returned. If lMaxTime is 0 (for infinity) the evaluation won't be
	 * stoped, this is the standard case.
	 *
	 * @see cFibElement::evalueObject()
	 * @param lMaxTime the maximum time for the evaluation, the returned
	 * 	exceed this value; the value 0 stands for infinity, so the
	 * 	evaluation won't be stoped
	 * @return a value for the time needed to evalue this underfunction
	 */
	virtual unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
	
	/**
	 * This method evaluades the size of the Fib -object in bits in the
	 * compressed file form.
	 * The optionalpart field of point -elements will be ignored.
	 *
	 * @see store()
	 * @return the size of the Fib -object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;

	/**
	 * This method stores this underfunction in the XML -format into the
	 * given stream.
	 * Variables should have ther number as ther value.
	 *
	 * @param stream the stream where this underfunctionshould be
	 * 	stored to
	 * @return true if this underfunction is stored, else false
	 */
	virtual bool storeXml( ostream &stream ) const;

#ifndef FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This Method checks if the given underfunction is equal to this underfunction.
	 *
	 * @param underfunction the underfunction to compare with this underfunction
	 * @return true if the given underfunction is equal to this underfunction, else false
	 */
	virtual bool equal( const cUnderFunction & underfunction ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

protected:

#ifdef FEATURE_EQUAL_FIB_OBJECT
	/**
	 * This method checks if the given underfunction is equal to this underfunction.
	 * Variables can be others, but must be defined and used in equivalent
	 * Fib-elements.
	 *
	 * @param underfunction the underfunction to compare with this underfunction
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
	 * @return true if this Fib-object is equal to the given Fib-object,
	 * 	else false
	 */
	virtual bool equalInternal( const cUnderFunction & underfunction,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT


};//end class cFunctionOneValue


}//end namespace fib

#endif
