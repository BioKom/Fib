/**
 * @class cCondition
 * file name: cCondition.h
 * @author Betti Oesterholz
 * @date 29.04.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a basic Fib-condition.
 * Copyright (C) @c LGPL3 2011 Betti Oesterholz
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
 * This file contains the basisclass of all Fib-condition. It's not
 * possible to create instances from this class.
 * Conditions are used in Fib-elements, especialy if-elements, to
 * represent logical conditions such like "not" or the "and" condition.
 *
 */
/*
History:
29.04.2011  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/

#ifndef ___C_CONDITION_H__
#define ___C_CONDITION_H__


#include "version.h"
#include "fibDatatyps.h"
#include "cReadBits.h"

#include "cFibVariable.h"
#include "cDomainSingle.h"

#include "tinyxml.h"

#include <sstream>
#include <ostream>
#include <istream>
#include <set>
#include <map>
#include <list>

using std::set;
using std::map;
using std::list;

namespace fib{


class cFibElement;//cyclic dependencie


class cCondition{

	friend class cIf;
	friend class cFunctionIf;
	friend class cConditionNot;
	friend class cConditionTwoValue;

public:

	/**
	 * the definitions for the condition
	 */
	static const unsignedIntFib CONDITION_FALSE = 0; // cConditionFalse
	static const unsignedIntFib CONDITION_TRUE  = 1; // cConditionTrue
	static const unsignedIntFib CONDITION_NOT   = 10; // cConditionNot
	static const unsignedIntFib CONDITION_OR    = 20; // cConditionTrue
	static const unsignedIntFib CONDITION_AND   = 21; // cConditionTrue
	static const unsignedIntFib CONDITION_XOR   = 23; // cConditionTrue
	static const unsignedIntFib CONDITION_EQUAL_INTEGER = 25; // cConditionEqualInteger
	static const unsignedIntFib CONDITION_LOWER = 26; // cConditionLower
	static const unsignedIntFib CONDITION_GREATER  = 27; // cConditionGreater

protected:

	/**
	 * the Fib-element which defines/ uses the condition
	 */
	cCondition * pSuperiorCondition;
	
	/**
	 * the Fib-element which defines/ uses the condition
	 */
	cFibElement * pDefiningFibElement;


	/**
	 * The constructor of the condition.
	 *
	 * @param pInSuperiorCondition the condition which contains
	 * @param pInDefiningFibElement the Fib-element which defines/ uses
	 * 	the new condition
	 */
	cCondition( cCondition * pInSuperiorCondition = NULL,
		cFibElement * pInDefiningFibElement = NULL );

	/**
	 * The copy constructor of the condition.
	 *
	 * @param condition the condition which to copy
	 * @param pSuperiorCondition the condition which contains
	 * @param pInDefiningFibElement the Fib-element which defines/ uses
	 */
	cCondition( const cCondition & condition,
		cCondition * pInSuperiorCondition = NULL,
		cFibElement *pInDefiningFibElement = NULL );

public:

	/**
	 * The destructor of the condition.
	 */
	virtual ~cCondition();

	/**
	 * This method returns if this condition is valid, else false.
	 * All subcondition and underfunctions must be valid.
	 * No condition should contain itself or should be contained in one
	 * of its condition (no cycles allowed).
	 *
	 * @return true if this condition is valid, else false
	 */
	virtual bool isValid() const = 0;


	/**
	 * This method checks if the given variable is used in this condition.
	 *
	 * @see cFibVariable
	 * @param variable the variable to check if it is used
	 * @return true if the variable is used, else false
	 */
	virtual bool isUsedVariable( const cFibVariable * variable ) const = 0;
	
	/**
	 * This method returns all variables used in this condition.
	 *
	 * @see cFibVariable
	 * @return all variables used in this condition
	 */
	virtual set<cFibVariable*> getUsedVariables() = 0;

	/**
	 * This method replace the variable variableOld with the variable
	 * variableNew in the condition.
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
	 * Returns the value of the condition (if it is true or false).
	 *
	 * @return the value of the condition
	 */
	virtual bool getValue() const = 0;

	/**
	 * @return the number of sub-condition, a condition of this type has
	 */
	virtual unsignedIntFib getNumberOfConditions() const = 0;

	/**
	 * @return the number of underfunctions, a condition of this type has
	 */
	virtual unsignedIntFib getNumberOfUnderFunctions() const = 0;

	/**
	 * @return the Fib-element which defines/ uses this condition or
	 * 	a Nullpointer NULL if non such Fib-element exists
	 */
	cFibElement * getDefiningFibElement() const;

	/**
	 * @return the superior condition to this or NULL, if non such
	 * 	exists (the superior condition is the condition, which
	 * 	contains this condition)
	 */
	cCondition * getSuperiorCondition() const;

	/**
	 * Sets the Fib-element which defines/ uses this condition.
	 * If the given pointer is the nullpointer (standardvalue), no
	 * Fib-element defines this condition.
	 *
	 * @param definingFibElement a pointer to the Fib-element which
	 * 	defines/ uses this condition
	 * @param bCheckDomains get the domains of the defining element and
	 * 	check the conditionelements with it
	 */
	virtual void setDefiningFibElement( cFibElement *fibElement=NULL,
		bool bCheckDomains=true );

	/**
	 * This method evaluades a value for the time needed to evalue the
	 * condition.
	 * This value should not exceed lMaxTime, if the value for the time
	 * is greater than lMaxTime the evaluation will be stopt and lMaxTime
	 * returned. If lMaxTime is 0 (for infinity) the evaluation won't be
	 * stoped, this is the standard case.
	 *
	 * @see cFibElement::evalueObject()
	 * @param lMaxTime the maximum time for the evaluation, the returned
	 * 	exceed this value; the value 0 stands for infinity, so the
	 * 	evaluation won't be stoped
	 * @return a value for the time needed to evalue this condition
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
	 * This method restores a condition in the XML-format from an
	 * TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node wher the condition is stored in
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
	 * @param pInSuperiorCondition the condition which contains the
	 * 	to restore condition
	 * @param pInDefiningFibElement the Fib-element which defines/ uses
	 * 	the to restore condition
	 * @return the pointers to the restored condition, if non could be restored
	 * 	the returned pointer is NULL
	 */
	static cCondition * restoreXml( const TiXmlElement * pXmlElement,
		intFib & outStatus, list<cFibVariable*> & liDefinedVariables,
		cCondition * pInSuperiorCondition = NULL,
		cFibElement *pInDefiningFibElement = NULL );

	/**
	 * This method stores this condition in the XML -format into the
	 * given stream.
	 * Variables should have ther number as ther value.
	 *
	 * @param stream the stream where this conditionhould be
	 * 	stored to
	 * @return true if this condition is stored, else false
	 */
	virtual bool storeXml( ostream &stream ) const = 0;

	/**
	 * This method restores a condition from a bitstream, wher it is
	 * stored in the compressed Fib-format.
	 *
	 * @see store
	 * @param iBitStream the stream where the condition is stored in,
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
	 * @param pInValueDomain the domain for value condition
	 * @param pInDomainVariable the domain for variables
	 * @param pInSuperiorCondition the condition which contains the
	 * 	to restore condition
	 * @param pInDefiningFibElement the Fib-element which defines/ uses
	 * 	the to restore condition
	 * @return a pointer to the restored condition or NULL
	 */
	static cCondition * restore( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables,
		const cDomainSingle * pInValueDomain, const cDomainSingle * pInDomainVariable,
		cCondition * pInSuperiorCondition = NULL,
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
	 * @return the type for the condition
	 */
	virtual unsignedIntFib getType() const = 0;
	
	/**
	 * @return the name for the condition
	 */
	virtual string getConditionName() const = 0;

#ifdef FEATURE_EQUAL_FIB_OBJECT
	/**
	 * This method checks if the given condition is equal to this condition.
	 *
	 * @param condition the condition to compare with this condition
	 * @param bCheckExternalObjects if true the external objects of
	 * 	cExtObject will be compared
	 * @return true if the given condition is equal to this condition, else false
	 */
	virtual bool equal( const cCondition &condition,
		const bool bCheckExternalObjects=true ) const;
	
#else //FEATURE_EQUAL_FIB_OBJECT
	/**
	 * This method checks if the given condition is equal to this condition.
	 *
	 * @param condition the condition to compare with this condition
	 * @return true if the given condition is equal to this condition, else false
	 */
	virtual bool equal( const cCondition &condition ) const = 0;
#endif //FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method checks if the given condition is equal to this condition.
	 *
	 * @param condition the condition to compare with this condition
	 * @return true if the given condition is equal to this condition, else false
	 */
	virtual bool operator==( const cCondition &condition ) const;

	/**
	 * This method checks if the given condition is not equal to this condition.
	 *
	 * @param condition the condition to compare with this condition
	 * @return true if the given condition is not equal to this condition, else false
	 */
	bool operator!=( const cCondition &condition ) const;

	/**
	 * This method duplicates this whole condition.
	 * subcondition of this condition are also cloned.
	 *
	 * @param pSuperiorCondition the condition which contains the cloned
	 * 	condition
	 * @param pInDefiningFibElement the Fib-element which defines/ uses
	 * 	the cloned condition
	 * @return the cloned/ duplicated condition
	 */
	virtual cCondition * clone(
		cCondition * pInSuperiorCondition = NULL,
		cFibElement *pInDefiningFibElement = NULL) const = 0;

protected:

#ifdef FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method checks if the given Fib-object is equal to this fib
	 * -object.
	 * Variables can be others, but must be defined and used in equivalent
	 * Fib-elements.
	 *
	 * @param condition the condition to which this condition should be equal
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
	virtual bool equalInternal( const cCondition & condition,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const = 0;

#endif //FEATURE_EQUAL_FIB_OBJECT


};//end class cCondition


}//end namespace fib

#endif //___C_CONDITION_H__
