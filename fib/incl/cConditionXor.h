/**
 * @class cConditionXor
 * file name: cConditionXor.h
 * @author Betti Oesterholz
 * @date 13.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a xor condition.
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
 * This class represents a xor condition, wich is true if exactly one of
 * its subconditions is true.
 *
 */
/*
History:
13.05.2011  Oesterholz  created
*/

#ifndef ___C_CONDITION_XOR_H__
#define ___C_CONDITION_XOR_H__


#include "version.h"
#include "fibDatatyps.h"
#include "cReadBits.h"

#include "cConditionTwoValue.h"


using std::set;

namespace fib{


class cConditionXor: public cConditionTwoValue{

public:

	/**
	 * The constructor of the xor condition.
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
	cConditionXor( cCondition * pInFirstSubCondition,
		cCondition * pInSecondSubCondition,
		cCondition * pInSuperiorCondition = NULL,
		cFibElement * pInDefiningFibElement = NULL );

	/**
	 * The constructor of the xor condition.
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
	cConditionXor( const cCondition & inFirstSubCondition,
		const cCondition & inSecondSubCondition,
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
	cConditionXor( const cConditionXor & condition,
		cCondition * pInSuperiorCondition = NULL,
		cFibElement *pInDefiningFibElement = NULL );
	

	/**
	 * The destructor of the condition.
	 */
	virtual ~cConditionXor();

	/**
	 * Returns the value of the condition (if it is true or false).
	 *
	 * @return exactly one of its subconditions is true, else false
	 */
	virtual bool getValue() const;

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
	virtual cConditionXor * clone(
		cCondition * pInSuperiorCondition = NULL,
		cFibElement *pInDefiningFibElement = NULL) const;

	/**
	 * @return the type for the condition
	 */
	virtual unsignedIntFib getType() const;
	
	/**
	 * @return the name for the condition
	 */
	virtual string getConditionName() const;



protected:
	
	/**
	 * @return the compressed type bits for this type of condition
	 */
	virtual char getTypeBit() const;

};//end class cConditionXor


}//end namespace Fib

#endif //___C_CONDITION_XOR_H__
