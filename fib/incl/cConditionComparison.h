/**
 * @class cConditionComparison
 * file name: cConditionComparison.h
 * @author Betti Oesterholz
 * @date 15.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a abstract condition for comparing numbers.
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
 * This class represents a abstract condition with two subfunctions, which
 * values will be compared with this condition.
 *
 */
/*
History:
15.05.2011  Oesterholz  created
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/

#ifndef ___C_CONDITION_COMPARISON_H__
#define ___C_CONDITION_COMPARISON_H__


#include "version.h"
#include "fibDatatyps.h"
#include "cReadBits.h"

#include "cCondition.h"

#include "cUnderFunction.h"


using std::set;

namespace fib{


class cConditionComparison: public cCondition{
protected:
	/**
	 * The first function this condition contains.
	 */
	cUnderFunction * pFirstSubFunction;
	
	/**
	 * The second function this condition contains.
	 */
	cUnderFunction * pSecondSubFunction;

public:


	/**
	 * The constructor of the two value condition.
	 *
	 * @param pInFirstSubFunction a pointer to the first function, this condition
	 * 	contains; Beware: It (pSubFunction) won't be copied.
	 * 	@see pFirstSubFunction
	 * @param pInSecondSubFunction a pointer to the second function, this
	 * 	condition contains; Beware: It (pSubFunction) won't be copied.
	 * 	@see pSecondSubFunction
	 * @param pInSuperiorCondition the condition which contains the
	 * 	new condition
	 * @param pInDefiningFibElement the Fib-element which defines/ uses
	 * 	the new condition
	 */
	cConditionComparison( cUnderFunction * pInFirstSubFunction,
		cUnderFunction * pInSecondSubFunction,
		cCondition * pInSuperiorCondition = NULL,
		cFibElement * pInDefiningFibElement = NULL );

	/**
	 * The constructor of the two value condition.
	 *
	 * @param inFirstSubFunction the first function, this condition contains
	 * 	@see pFirstSubFunction
	 * @param inSecondSubFunction the second function, this condition contains
	 * 	@see pSecondSubFunction
	 * @param pInSuperiorCondition the condition which contains the
	 * 	new condition
	 * @param pInDefiningFibElement the Fib-element which defines/ uses
	 * 	the new condition
	 */
	cConditionComparison( const cUnderFunction & inFirstSubFunction,
		const cUnderFunction & inSecondSubFunction,
		cCondition * pInSuperiorCondition = NULL,
		cFibElement * pInDefiningFibElement = NULL );
	
	/**
	 * The copy constructor of the condition.
	 * This constructor will also copy the subconditions of the given
	 * condition.
	 *
	 * @param condition the condition which to copy
	 * @param pInSuperiorCondition the condition which contains the
	 * 	new condition
	 * @param pInDefiningFibElement the Fib-element which defines/ uses
	 * 	the new condition
	 */
	cConditionComparison( const cConditionComparison & condition,
		cCondition * pInSuperiorCondition = NULL,
		cFibElement *pInDefiningFibElement = NULL );
	

	/**
	 * The destructor of the condition.
	 */
	virtual ~cConditionComparison();

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
	 * @return the number of conditions, a condition of this type has
	 */
	virtual unsignedIntFib getNumberOfConditions() const;
	
	/**
	 * @return the number of underfunctions, a condition of this type has
	 */
	virtual unsignedIntFib getNumberOfUnderFunctions() const;

	/**
	 * Sets the Fib-element which defines/ uses this condition.
	 * If the given pointer is the nullpointer (standardvalue), no
	 * Fib-element defines this condition.
	 *
	 * @param pDefiningFibElement a pointer to the Fib-element which
	 * 	defines/ uses this condition
	 * @param bCheckDomains get the domains of the defining element and
	 * 	check the underfunctionelements with it
	 */
	virtual void setDefiningFibElement( cFibElement * pDefiningFibElement=NULL,
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
	 * @see pFirstSubFunction
	 * @see setFirstSubFunction()
	 * @return a pointer to the first function this condition contains (@see pSubFunction)
	 */
	cUnderFunction * getFirstSubFunction();
	
	/**
	 * @see pFirstSubFunction
	 * @see setFirstSubFunction()
	 * @return a pointer to the first function this condition contains (@see pSubFunction)
	 */
	const cUnderFunction * getFirstSubFunction() const;
	
	/**
	 * This method sets the contained first function (@see pSubFunction) to the
	 * given condition pInSubFunction.
	 * Beware: It (pInSubFunction) won't be copied.
	 *
	 * @see pFirstSubFunction
	 * @see getFirstSubFunction()
	 * @param pInSubFunction a pointer to the subcondition to set
	 * @param bDeleteOld if true, delete the old subcondition from the memory
	 * @return true if pInSubFunction condition was set, else false
	 */
	bool setFirstSubFunction( cUnderFunction * pInSubFunction, bool bDeleteOld=true );
	
	/**
	 * This method sets the contained first function (@see pSubFunction) to the
	 * given condition pInSubFunction.
	 *
	 * @see pFirstSubFunction
	 * @see getFirstSubFunction()
	 * @param pInSubFunction the subcondition to set
	 * @param bDeleteOld if true, delete the old subcondition from the memory
	 * @return true if pInSubFunction condition was set, else false
	 */
	bool setFirstSubFunction( const cUnderFunction & pInSubFunction, bool bDeleteOld=true );

	/**
	 * @see pSecondSubFunction
	 * @see setSecondSubFunction()
	 * @return a pointer to the second function this condition contains (@see pSubFunction)
	 */
	cUnderFunction * getSecondSubFunction();
	
	/**
	 * @see pSecondSubFunction
	 * @see setSecondSubFunction()
	 * @return a pointer to the second function this condition contains (@see pSubFunction)
	 */
	const cUnderFunction * getSecondSubFunction() const;
	
	/**
	 * This method sets the contained second function (@see pSubFunction) to the
	 * given condition pInSubFunction.
	 * Beware: It (pInSubFunction) won't be copied.
	 *
	 * @see pSecondSubFunction
	 * @see getSecondSubFunction()
	 * @param pInSubFunction a pointer to the subcondition to set
	 * @param bDeleteOld if true, delete the old subcondition from the memory
	 * @return true if pInSubFunction condition was set, else false
	 */
	bool setSecondSubFunction( cUnderFunction * pInSubFunction, bool bDeleteOld=true );
	
	/**
	 * This method sets the contained second function (@see pSubFunction) to the
	 * given condition pInSubFunction.
	 *
	 * @see pSecondSubFunction
	 * @see getSecondSubFunction()
	 * @param pInSubFunction the subcondition to set
	 * @param bDeleteOld if true, delete the old subcondition from the memory
	 * @return true if pInSubFunction condition was set, else false
	 */
	bool setSecondSubFunction( const cUnderFunction & pInSubFunction, bool bDeleteOld=true );


protected:
	
	/**
	 * @return the compressed type bits for this type of condition
	 */
	virtual char getTypeBit() const = 0;

#ifdef FEATURE_EQUAL_FIB_OBJECT

	/**
	 * This method checks if the given Fib-object is equal to this fib
	 * -object.
	 * Variables can be others, but must be defined and used in equivalent
	 * Fib-elements.
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
		const bool bCheckExternalObjects ) const;

#endif //FEATURE_EQUAL_FIB_OBJECT

};//end class cConditionComparison


}//end namespace Fib

#endif //___C_CONDITION_COMPARISON_H__
