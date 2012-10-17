/**
 * @class cFibObjectCounts
 * file name: cFibObjectCounts.h
 * @author Betti Oesterholz
 * @date 16.08.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class is for storing the data of counters for a Fib-object.
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
 * This class is for storing the data of counters for a Fib-object.
 * It is basicly a helpclass for cFibBranch to store ist counters.
 * Stored counts are:
 * 	- the number of all Fib-elements
 * 	- the number of Fib-elements of the different typs
 * 	- the number of objectpoints
 *
 */
/*
History:
16.08.2010  Oesterholz  created
28.04.2011  Oesterholz  if-element added
03.08.2011  Oesterholz  cExtObject added
07.11.2011  Oesterholz  cExtSubobject added
15.12.2011  Oesterholz  cFibSet and cFibmatrix added
*/

#ifndef ___C_FIB_OBJECT_COUNTS_H__
#define ___C_FIB_OBJECT_COUNTS_H__


#include "fibDatatyps.h"

#include <valarray>

using namespace std;

namespace fib{


class cFibObjectCounts{

public:

	/**
	 * The maximal number of possible Fib-elementtyps.
	 * @see uiNumberOfFibElements .
	 */
	static const char MAX_ELEMENT_TYPS = 13;
	
	/**
	 * The type for the vector with the counters of the Fib-elements.
	 * @see vecNumberOfFibElements
	 */
	typedef valarray<intFib> typeVecCounters;
	
	/**
	 * Defines for the Fib-element type position in
	 * @see uiNumberOfFibElements .
	 * Thy can be use as an index in uiNumberOfFibElements .
	 */
	static const char ALL    = 0;
	static const char POINT  = 1;
	static const char LIST   = 2;
	static const char ROOT   = 3;
	static const char IF     = 4;
	static const char PROPERTY = 5;
	static const char FUNCTION = 6;
	static const char AREA     = 7;
	static const char COMMENT  = 8;
	static const char EXT_OBJECT    = 9;
	static const char EXT_SUBOBJECT = 10;
	static const char FIB_SET  = 11;
	static const char FIB_MATRIX    = 12;

	/**
	 * The number of Fib-elements of the given type.
	 */
	typeVecCounters vecNumberOfFibElements;
	
	/**
	 * The number of objectpoints.
	 */
	intFib uiNumberOfObjectpoints;
	
	
	/**
	 * Standardconstructor
	 */
	cFibObjectCounts();
	
	/**
	 * The adding operator.
	 * It adds the counts of the given cFibObjectCounts to this
	 * cFibObjectCounts.
	 *
	 * @param fibObjectCounts the counts to add
	 * @return a reference to this object
	 */
	cFibObjectCounts & operator+=( const cFibObjectCounts & fibObjectCounts );

	/**
	 * The subtracting operator.
	 * It adds the counts of the given cFibObjectCounts to this
	 * cFibObjectCounts.
	 *
	 * @param fibObjectCounts the counts to subtract
	 * @return a reference to this object
	 */
	cFibObjectCounts & operator-=( const cFibObjectCounts & fibObjectCounts );

	/**
	 * This method reevalues the counter for all fib elements with the help
	 * of the counters of the Fib-elements of the different typs.
	 *
	 * @return the number of all Fib-elements
	 */
	intFib evalueAllFibElements();

	/**
	 * @return the number of move points evalued with the help of counters
	 * 	of the Fib-elements of the different typs
	 */
	intFib getNumberOfMovePoints() const;


	/**
	 * @param cType the char for the Fib-elementtype for which to return
	 * 	the index in the @see uiNumberOfFibElements array
	 * @return the indexnumber for the @see uiNumberOfFibElements array
	 * 	which contains the count of the elements of the given type
	 */
	static int elementTypeToIndex( char cType );
	
	/**
	 * @param index the index for which to return the Fib-elementtype char
	 * @return the char for the elementtype, which has the given index in
	 * 	the @see uiNumberOfFibElements array
	 */
	static char indexToElementType( const char index );
	
	/**
	 * This function checks if the given type char stands for an valid /
	 * existing type.
	 *
	 * @see cFibElement::getType()
	 * @param cType the type char to check
	 * @return true if the type for the given type char is valid /exists,
	 * 	else false
	 */
	static bool isValidType( const char cType );

};//end class cFibObjectCounts


}//end namespace fib

#endif //___C_FIB_OBJECT_COUNTS_H__
