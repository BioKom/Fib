/**
 * @class cConditionFalse
 * file name: cConditionFalse.h
 * @author Betti Oesterholz
 * @date 30.04.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a false condition.
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
 * This class represents a false condition.
 * This condition is allways false.
 *
 */
/*
History:
30.04.2011  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/

#ifndef ___C_CONDITION_FALSE_H__
#define ___C_CONDITION_FALSE_H__


#include "version.h"
#include "fibDatatyps.h"
#include "cReadBits.h"

#include "cCondition.h"


using std::set;

namespace fib{


class cConditionFalse: public cCondition{
public:


	/**
	 * The constructor of the false condition.
	 *
	 * @param pInSuperiorCondition the condition which contains the
	 * 	new condition
	 * @param pInDefiningFibElement the Fib-element which defines/ uses
	 * 	the new condition
	 */
	cConditionFalse( cCondition * pInSuperiorCondition = NULL,
		cFibElement * pInDefiningFibElement = NULL );

	/**
	 * The copy constructor of the condition.
	 *
	 * @param condition the condition which to copy
	 * @param pInSuperiorCondition the condition which contains the
	 * 	new condition
	 * @param pInDefiningFibElement the Fib-element which defines/ uses
	 * 	the new condition
	 */
	cConditionFalse( const cConditionFalse & condition,
		cCondition * pInSuperiorCondition = NULL,
		cFibElement *pInDefiningFibElement = NULL );

	/**
	 * The destructor of the condition.
	 */
	virtual ~cConditionFalse();

	/**
	 * This method returns if this condition is valid, else false.
	 * All subcondition and underfunctions must be valid.
	 * No condition should contain itself or should be contained in one
	 * of its condition (no cycles allowed).
	 *
	 * @return true if this condition is valid, else false
	 */
	virtual bool isValid() const;

	/**
	 * This method checks if the given variable is used in this condition.
	 *
	 * @see cFibVariable
	 * @param variable the variable to check if it is used
	 * @return true if the variable is used, else false
	 */
	virtual bool isUsedVariable( const cFibVariable * variable ) const;
	
	/**
	 * This method returns all variables used in this condition.
	 *
	 * @see cFibVariable
	 * @return all variables used in this condition
	 */
	virtual set<cFibVariable*> getUsedVariables();

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
	virtual bool replaceVariable( cFibVariable * variableOld,
		cFibVariable * variableNew );

	/**
	 * Returns the value false of the condition.
	 *
	 * @return false
	 */
	virtual bool getValue() const;

	/**
	 * @return the number of conditions, a condition of this type has
	 */
	virtual unsignedIntFib getNumberOfConditions() const;
	
	/**
	 * @return the number of underfunctions, a condition of this type has
	 */
	virtual unsignedIntFib getNumberOfUnderFunctions() const;

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
	virtual unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
	
	/**
	 * This method evaluades the size of the Fib-object in bits in the
	 * compressed file form.
	 * The optionalpart field of point -elements will be ignored.
	 *
	 * @see store()
	 * @return the size of the Fib-object in bits in the compressed form
	 */
	virtual unsignedLongFib getCompressedSize() const;

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
		unsigned char & uiRestBitPosition ) const;

	/**
	 * This method stores this condition in the XML-format into the
	 * given stream.
	 * Variables should have ther number as ther value.
	 *
	 * @param stream the stream where this conditionshould be
	 * 	stored to
	 * @return true if this condition is stored, else false
	 */
	virtual bool storeXml( ostream & stream ) const;

	/**
	 * @return the type for the condition
	 */
	virtual unsignedIntFib getType() const;
	
	/**
	 * @return the name for the condition
	 */
	virtual string getConditionName() const;

#ifndef FEATURE_EQUAL_FIB_OBJECT
	/**
	 * This Method checks if the given condition is equal to this condition.
	 *
	 * @param condition the condition to compare with this condition
	 * @return true if the given condition is equal to this condition, else false
	 */
	virtual bool equal( const cCondition & condition ) const;
#endif //FEATURE_EQUAL_FIB_OBJECT

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
	virtual cConditionFalse * clone(
		cCondition * pInSuperiorCondition = NULL,
		cFibElement *pInDefiningFibElement = NULL) const;

protected:

#ifdef FEATURE_EQUAL_FIB_OBJECT
	
	/**
	 * This Method checks if the given variable is equal to this variable.
	 *
	 * @param condition the condition to which this condition should be
	 * 	equal
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
	virtual bool equalInternal( const cCondition & condition,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

};//end class cConditionFalse


}//end namespace Fib

#endif
