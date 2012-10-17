/**
 * @class cConditionGreater
 * file name: cConditionGreater.cpp
 * @author Betti Oesterholz
 * @date 15.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a condition to compare values on lower.
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
 * This class represents a condition to compare values on lower.
 * It is is true if the value of the first subfunction is greater than that
 * of the second.
 */
/*
History:
15.05.2011  Oesterholz  created
*/

#include "cConditionGreater.h"



using namespace fib;


/**
 * The constructor of the xor condition.
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
cConditionGreater::cConditionGreater( cUnderFunction * pInFirstSubFunction,
		cUnderFunction * pInSecondSubFunction,
		cCondition * pInSuperiorCondition,
		cFibElement * pInDefiningFibElement ):
		cConditionComparison( pInFirstSubFunction, pInSecondSubFunction,
			pInSuperiorCondition, pInDefiningFibElement ){
	//nothing to do
}


/**
 * The constructor of the xor condition.
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
cConditionGreater::cConditionGreater( const cUnderFunction & inFirstSubFunction,
		const cUnderFunction & inSecondSubFunction,
		cCondition * pInSuperiorCondition,
		cFibElement * pInDefiningFibElement ):
		cConditionComparison( inFirstSubFunction, inSecondSubFunction,
			pInSuperiorCondition, pInDefiningFibElement ){
	//nothing to do
}


/**
 * The copy constructor of the condition.
 * This constructor will also copy the subfunctions of the given
 * condition.
 *
 * @param condition the condition which to copy
 * @param pInSuperiorCondition the condition which contains the
 * 	new condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the new condition
 */
cConditionGreater::cConditionGreater( const cConditionGreater & condition,
		cCondition * pInSuperiorCondition,
		cFibElement *pInDefiningFibElement ):
		cConditionComparison( condition, pInSuperiorCondition, pInDefiningFibElement ){
	//nothing to do
}


/**
 * The destructor of the condition.
 */
cConditionGreater::~cConditionGreater(){
	//nothing to do
}


/**
 * Returns the value of the condition (if it is true or false).
 *
 * @return true if the value of the first subfunction is greater than that
 * 	of the second
 */
bool cConditionGreater::getValue() const{
	

	if ( ( pFirstSubFunction != NULL ) && ( pSecondSubFunction != NULL ) ){
		//check first subfunction
		return ( pFirstSubFunction->getValue() > pSecondSubFunction->getValue() );
	}
	return false;
}



/**
 * This method duplicates this whole condition.
 * subfunction of this condition are also cloned.
 *
 * @param pSuperiorCondition the condition which contains the cloned
 * 	condition
 * @param pInDefiningFibElement the Fib-element which defines/ uses
 * 	the cloned condition
 * @return the cloned/ duplicated condition
 */
cConditionGreater * cConditionGreater::clone(
		cCondition * pInSuperiorCondition ,
		cFibElement *pInDefiningFibElement) const{
	
	return new cConditionGreater( *this, pInSuperiorCondition,
		pInDefiningFibElement );
}


/**
 * @return the type for the condition
 */
unsignedIntFib cConditionGreater::getType() const{

	return CONDITION_GREATER;
}

/**
 * @return the name for the condition
 */
string cConditionGreater::getConditionName() const{

	return "gr";
}


/**
 * @return the compressed type bits for this type of condition
 */
char cConditionGreater::getTypeBit() const{

	return 0x0A;
}



















