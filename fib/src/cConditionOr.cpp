/**
 * @class cConditionOr
 * file name: cConditionOr.cpp
 * @author Betti Oesterholz
 * @date 13.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a or condition.
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
 * This class represents a or condition, wich is true if one or more of
 * its subconditions is true.
 *
 */
/*
History:
13.05.2011  Oesterholz  created
*/


#include "cConditionOr.h"



using namespace fib;


/**
 * The constructor of the or condition.
 *
 * @param pInFirstSubCondition a pointer to the first condition, this condition
 * 	contains; Beware: It (pSubCondition) won't be copied.
 * 	@see pFirstSubCondition
 * @param pInSecondSubCondition a pointer to the second condition, this
 * 	condition contains; Beware: It (pSubCondition) won't be copied.
 * 	@see pSecondSubCondition
 * @param pInSuperiorCondition the condition which contains the
 * 	new condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the new condition
 */
cConditionOr::cConditionOr( cCondition * pInFirstSubCondition,
		cCondition * pInSecondSubCondition,
		cCondition * pInSuperiorCondition,
		cFibElement * pInDefiningFibElement ):
		cConditionTwoValue( pInFirstSubCondition, pInSecondSubCondition,
			pInSuperiorCondition, pInDefiningFibElement ){
	//nothing to do
}


/**
 * The constructor of the or condition.
 *
 * @param inFirstSubCondition the first condition, this condition contains
 * 	@see pFirstSubCondition
 * @param inSecondSubCondition the second condition, this condition contains
 * 	@see pSecondSubCondition
 * @param pInSuperiorCondition the condition which contains the
 * 	new condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the new condition
 */
cConditionOr::cConditionOr( const cCondition & inFirstSubCondition,
		const cCondition & inSecondSubCondition,
		cCondition * pInSuperiorCondition,
		cFibElement * pInDefiningFibElement ):
		cConditionTwoValue( inFirstSubCondition, inSecondSubCondition,
			pInSuperiorCondition, pInDefiningFibElement ){
	//nothing to do
}


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
cConditionOr::cConditionOr( const cConditionOr & condition,
		cCondition * pInSuperiorCondition,
		cFibElement *pInDefiningFibElement ):
		cConditionTwoValue( condition, pInSuperiorCondition, pInDefiningFibElement ){
	//nothing to do
}


/**
 * The destructor of the condition.
 */
cConditionOr::~cConditionOr(){
	//nothing to do
}


/**
 * Returns the value of the condition (if it is true or false).
 *
 * @return true if one or more of its subconditions is true, else false
 */
bool cConditionOr::getValue() const{

	if ( pFirstSubCondition != NULL ){
		//check first subcondition
		if ( pFirstSubCondition->getValue() ){
			return true;
		}
	}
	if ( pSecondSubCondition != NULL ){
		//check second subcondition
		if ( pSecondSubCondition->getValue() ){
			return true;
		}
	}
	return false;
}



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
cConditionOr * cConditionOr::clone(
		cCondition * pInSuperiorCondition ,
		cFibElement *pInDefiningFibElement) const{
	
	return new cConditionOr( *this, pInSuperiorCondition,
		pInDefiningFibElement );
}


/**
 * @return the type for the condition
 */
unsignedIntFib cConditionOr::getType() const{

	return CONDITION_OR;
}

/**
 * @return the name for the condition
 */
string cConditionOr::getConditionName() const{

	return "or";
}


/**
 * @return the compressed type bits for this type of condition
 */
char cConditionOr::getTypeBit() const{

	return 0x02;
}



















