/**
 * @class cUnderFunction
 * file name: cUnderFunction.h
 * @author Betti Oesterholz
 * @date 22.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a basic Fib-underfunction.
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
 * This file contains the basisclass of all Fib-underfunctions. It's not
 * possible to create instances from this class.
 * Underfunctions are used in Fib-elements, especialy functions, to
 * represent mathematical functions such like addition or the maximum
 * function.
 *
 */
/*
History:
22.04.2010  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/

#ifndef ___C_UNDER_FUNCTION_H__
#define ___C_UNDER_FUNCTION_H__


#include "version.h"
#include "fibDatatyps.h"
#include "cReadBits.h"

#include "cTypeUnderFunction.h"
#include "cDomainSingle.h"
#include "cFibVariable.h"

#include "tinyxml.h"

#include <sstream>
#include <ostream>
#include <istream>
#include <set>
#include <list>

using std::set;
using std::list;

namespace fib{


class cFibElement;//cyclic dependencie


class cUnderFunction{

	friend class cFunction;
	friend class cFunctionIf;
	friend class cFunctionOneValue;
	friend class cFunctionTwoValue;
	friend class cConditionComparison;
	
public:

	/**
	 * the definitions for the underfunctions
	 */
	static const unsignedIntFib FUNCTION_VALUE  = 0; // cUnderFunction
	static const unsignedIntFib FUNCTION_VARIABLE = 1; // cFunctionVariable
	static const unsignedIntFib FUNCTION_LOG    = 10; // cFunctionLog
	static const unsignedIntFib FUNCTION_SIN    = 11; // cFunctionSin
	static const unsignedIntFib FUNCTION_ABS    = 12; // cFunctionAbs
	static const unsignedIntFib FUNCTION_ARCSIN = 13; // cFunctionArcsin
	static const unsignedIntFib FUNCTION_ROUND  = 14; // cFunctionRound
	static const unsignedIntFib FUNCTION_ADD    = 20; // cFunctionAdd
	static const unsignedIntFib FUNCTION_SUB    = 21; // cFunctionSub
	static const unsignedIntFib FUNCTION_MULT   = 22; // cFunctionMult
	static const unsignedIntFib FUNCTION_DIV    = 23; // cFunctionDiv
	static const unsignedIntFib FUNCTION_EXP    = 24; // cFunctionExp
	static const unsignedIntFib FUNCTION_MIN    = 25; // cFunctionMin
	static const unsignedIntFib FUNCTION_MAX    = 26; // cFunctionMax
	static const unsignedIntFib FUNCTION_IF     = 30; // cFunctionIf
	static const unsignedIntFib FUNCTION_MOD    = 31; // cFunctionMod

protected:

	/**
	 * the Fib-element which defines/ uses the underfunction
	 */
	cUnderFunction * pSuperiorUnderFunction;
	
	/**
	 * the Fib-element which defines/ uses the underfunction
	 */
	cFibElement * pDefiningFibElement;


	/**
	 * The constructor of the underfunction.
	 *
	 * @param pInSuperiorUnderFunction the underfunction which contains
	 * @param pInDefiningFibElement the Fib-element which defines/ uses
	 * 	the new underfunction
	 */
	cUnderFunction( cUnderFunction * pInSuperiorUnderFunction = NULL,
		cFibElement * pInDefiningFibElement = NULL );

	/**
	 * The copy constructor of the underfunction.
	 *
	 * @param underfunction the underfunction which to copy
	 * @param pSuperiorUnderFunction the underfunction which contains
	 * @param pInDefiningFibElement the Fib-element which defines/ uses
	 */
	cUnderFunction( const cUnderFunction & underfunction,
		cUnderFunction * pInSuperiorUnderFunction = NULL,
		cFibElement *pInDefiningFibElement = NULL );

public:

	/**
	 * The destructor of the underfunction.
	 */
	virtual ~cUnderFunction();

	/**
	 * This method returns if this underfunction is valid, else false.
	 * All values in the underfunction and it's underfunctions must be
	 * inside the underfunction domain. All variables must be defined over
	 * this underfunction.
	 * No underfunction should contain itself or should be contained in one
	 * of its underfunctions (no cycles allowed).
	 *
	 * @return true if this underfunction is valid, else false
	 */
	virtual bool isValid() const = 0;


	/**
	 * This method checks if the given variable is used in this underfunction.
	 *
	 * @see cFibVariable
	 * @param variable the variable to check if it is used
	 * @return true if the variable is used, else false
	 */
	virtual bool isUsedVariable( const cFibVariable * variable ) const = 0;
	
	/**
	 * This method returns all variables used in this underfunction.
	 *
	 * @see cFibVariable
	 * @return all variables used in this underfunction
	 */
	virtual set<cFibVariable*> getUsedVariables() = 0;

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
		cFibVariable *variableNew ) = 0;

	/**
	 * Returns the value of the underfunction or 0 if non such exists.
	 *
	 * @return the value of the underfunction or 0 if non
	 * 	such exists
	 */
	virtual doubleFib getValue() const = 0;

	/**
	 * @return the number of underfunctions, a underfunction of this type has
	 */
	virtual unsignedIntFib getNumberOfUnderFunctions() const = 0;

	/**
	 * Returns the type of the underfunction.
	 * You have to delete the returned object after usage.
	 *
	 * @return the type of the underfunction
	 */
	virtual cTypeElement * getElementType() const;


	/**
	 * Returns a reference to the domain of the underfunction or
	 * the nullpointer NULL if no domain is defined for the underfunction.
	 * If the nullpointer NULL is returned the standarddomain is valid for the
	 * underfunction.
	 *
	 * @return a reference to the underfunctiondomain of the underfunction
	 */
	virtual cDomainSingle * getDomain() const;

	/**
	 * Returns a reference to the value domain of the underfunction or
	 * the nullpointer NULL if no value domain is defined for the underfunction.
	 * If the nullpointer NULL is returned the standarddomain is valid for the
	 * underfunction.
	 *
	 * @return a reference to the definitionarea of the underfunction
	 */
	virtual cDomainSingle * getValueDomain() const;

	/**
	 * Returns a reference to the standard domain of the underfunction.
	 * You have to delete the returned object after usage.
	 *
	 * @return a reference to the standard domain of the underfunction
	 */
	virtual cDomainSingle * getStandardDomain() const;

	/**
	 * Returns a reference to the domain for variables of the underfunction.
	 * You have to delete the returned object after usage.
	 *
	 * @return a reference to the domain for variables of the underfunction
	 */
	virtual cDomainSingle * getVariableDomain() const;

	/**
	 * @return the Fib-element which defines/ uses this underfunction or
	 * 	a Nullpointer NULL if non such Fib-element exists
	 */
	cFibElement * getDefiningFibElement() const;

	/**
	 * @return the superior underfunction to this or NULL, if non such
	 * 	exists (the superior underfunction is the underfunction, which
	 * 	contains this underfunction)
	 */
	cUnderFunction * getSuperiorUnderFunction() const;

	/**
	 * Sets the Fib-element which defines/ uses this underfunction.
	 * If the given pointer is the nullpointer (standardvalue), no
	 * Fib-element defines this underfunction.
	 *
	 * @param definingFibElement a pointer to the Fib-element which
	 * 	defines/ uses this underfunction
	 * @param bCheckDomains get the domains of the defining element and
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
	virtual unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const = 0;
	
	/**
	 * This method evaluades the size of the Fib-object in bits in the
	 * compressed file form.
	 * The optionalpart field of point -elements will be ignored.
	 *
	 * @see store()
	 * @return the size of the Fib-object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const = 0;

	/**
	 * This method restores a underfunction in the XML -format from an
	 * TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node wher the underfunction is stored in
	 * @param outStatus an integervalue with the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore Fib-element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	to restore underfunction
	 * @param pInDefiningFibElement the Fib-element which defines/ uses
	 * 	the to restore underfunction
	 * @return the pointers to the restored underfunction, if non could be restored
	 * 	the returned pointer is NULL
	 */
	static cUnderFunction * restoreXml( const TiXmlElement * pXmlElement,
		intFib & outStatus, list<cFibVariable*> & liDefinedVariables,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement *pInDefiningFibElement = NULL );

	/**
	 * This method stores this underfunction in the XML -format into the
	 * given stream.
	 * Variables should have ther number as ther value.
	 *
	 * @param stream the stream where this underfunctionshould be
	 * 	stored to
	 * @return true if this underfunction is stored, else false
	 */
	virtual bool storeXml( ostream &stream ) const = 0;

	/**
	 * This method restores a underfunction from a bitstream, wher it is
	 * stored in the compressed Fib-format.
	 *
	 * @see store
	 * @param iBitStream the stream where the underfunction is stored in,
	 * 	because the stream is an cReadBits, any number of bits can be
	 * 	readed from it
	 * @param outStatus an integervalue with the errorvalue
	 * 	possible errorvalues are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 * @param liDefinedVariables a list with the defined variables for the
	 * 	to restore Fib-element, every variable should have it's number
	 * 	(the number under which it is stored) as it's value
	 * @param pInValueDomain the domain for value underfunction
	 * @param pInDomainVariable the domain for variables
	 * @param pInSuperiorFunction the underfunction which contains the
	 * 	to restore underfunction
	 * @param pInDefiningFibElement the Fib-element which defines/ uses
	 * 	the to restore underfunction
	 * @return a pointer to the restored underfunction or NULL
	 */
	static cUnderFunction * restore( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomainSingle * pInValueDomain, const cDomainSingle * pInDomainVariable,
		cUnderFunction * pInSuperiorFunction = NULL,
		cFibElement *pInDefiningFibElement = NULL );

	/**
	 * This method stores this Fib-object in the compressed Fib-format
	 * into the given stream.
	 * It is needed becouse the stream can yust store byts but the size of
	 * Fib-elements can be any number of bits. Because of that ther have to
	 * be a possibility to exchange the missing bits betwean the Fib-elements.
	 *
	 * @see store
	 * @param stream the stream where this Fib-object should be stored to
	 * @param cRestBits the not yet writen bits which should be stored
	 * @param uiRestBitPosition the number of bits in the cRestBits which
	 * 	should be writen respectively containing valid information
	 * @return true if this Fib-object is stored, else false
	 */
	virtual bool store( ostream & stream, char & cRestBits,
		unsigned char & uiRestBitPosition ) const = 0;

	/**
	 * @return the type for the underfunction
	 */
	virtual unsignedIntFib getType() const = 0;
	
	/**
	 * @return the name for the underfunction
	 */
	virtual string getUnderFunctionName() const = 0;

#ifdef FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method checks if the given underfunction is equal to this underfunction.
	 *
	 * @param underfunction the underfunction to compare with this underfunction
	 * @param bCheckExternalObjects if true the external objects of
	 * 	cExtObject will be compared
	 * @return true if the given underfunction is equal to this underfunction, else false
	 */
	virtual bool equal( const cUnderFunction &underfunction,
		const bool bCheckExternalObjects=true ) const;
	
#else //FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method checks if the given underfunction is equal to this underfunction.
	 *
	 * @param underfunction the underfunction to compare with this underfunction
	 * @return true if the given underfunction is equal to this underfunction, else false
	 */
	virtual bool equal( const cUnderFunction &underfunction ) const = 0;
	
#endif //FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method checks if the given underfunction is equal to this underfunction.
	 *
	 * @param underfunction the underfunction to compare with this underfunction
	 * @return true if the given underfunction is equal to this underfunction, else false
	 */
	virtual bool operator==( const cUnderFunction &underfunction ) const;

	/**
	 * This method checks if the given underfunction is not equal to this underfunction.
	 *
	 * @param underfunction the underfunction to compare with this underfunction
	 * @return true if the given underfunction is not equal to this underfunction, else false
	 */
	bool operator!=( const cUnderFunction &underfunction ) const;

	/**
	 * This method duplicates this whole underfunction.
	 * Underfunctions of this underfunction are also cloned.
	 *
	 * @param pSuperiorUnderFunction the underfunction which contains the
	 * 	cloned underfunction
	 * @param pInDefiningFibElement the Fib-element which defines/ uses the
	 * 	cloned underfunction
	 * @return the cloned/ duplicated underfunction
	 */
	virtual cUnderFunction * clone(
		cUnderFunction * pInSuperiorUnderFunction = NULL,
		cFibElement *pInDefiningFibElement = NULL) const = 0;

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
		const bool bCheckExternalObjects ) const = 0;
		
#endif //FEATURE_EQUAL_FIB_OBJECT


};//end class cUnderFunction


}//end namespace fib

#endif
