/**
 * @class cFibObjectCounts
 * file name: cFibObjectCounts.cpp
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

#ifndef ___C_FIB_OBJECT_COUNTS_CPP__
#define ___C_FIB_OBJECT_COUNTS_CPP__


#include "cFibObjectCounts.h"

using namespace fib;




/**
 * Standardconstructor
 */
cFibObjectCounts::cFibObjectCounts():
		vecNumberOfFibElements( MAX_ELEMENT_TYPS ),
		uiNumberOfObjectpoints( 0 ){


}

/**
 * The adding operator.
 * It adds the counts of the given cFibObjectCounts to this
 * cFibObjectCounts.
 *
 * @param fibObjectCounts the counts to add
 * @return a reference to this object
 */
cFibObjectCounts & cFibObjectCounts::operator+=(
		const cFibObjectCounts & fibObjectCounts ){
	
	vecNumberOfFibElements += fibObjectCounts.vecNumberOfFibElements;
	uiNumberOfObjectpoints += fibObjectCounts.uiNumberOfObjectpoints;
	
	return *this;
}

/**
 * The subtracting operator.
 * It adds the counts of the given cFibObjectCounts to this
 * cFibObjectCounts.
 *
 * @param fibObjectCounts the counts to subtract
 * @return a reference to this object
 */
cFibObjectCounts & cFibObjectCounts::operator-=(
		const cFibObjectCounts & fibObjectCounts ){
	
	vecNumberOfFibElements -= fibObjectCounts.vecNumberOfFibElements;
	uiNumberOfObjectpoints -= fibObjectCounts.uiNumberOfObjectpoints;
	
	return *this;
}



/**
 * This method reevalues the counter for all fib elements with the help
 * of the counters of the Fib-elements of the different typs.
 *
 * @return the number of all Fib-elements
 */
intFib cFibObjectCounts::evalueAllFibElements(){
	
	vecNumberOfFibElements[ 0 ] = 0;
	vecNumberOfFibElements[ 0 ] = vecNumberOfFibElements.sum();
	return vecNumberOfFibElements[ 0 ];
}


/**
 * @return the number of move points evalued with the help of counters
 * 	of the Fib-elements of the different typs
 */
intFib cFibObjectCounts::getNumberOfMovePoints() const{
	
	return vecNumberOfFibElements[ PROPERTY ] +
		vecNumberOfFibElements[ FUNCTION ] +
		vecNumberOfFibElements[ AREA ] +
		vecNumberOfFibElements[ COMMENT ] +
		vecNumberOfFibElements[ FIB_SET ] +
		vecNumberOfFibElements[ FIB_MATRIX ];
}


/**
 * @param cType the char for the Fib-elementtype for which to return
 * 	the index in the @see fibObjectCounts array
 * @return the indexnumber for the @see fibObjectCounts array
 * 	which contains the count of the elements of the given type
 */
int cFibObjectCounts::elementTypeToIndex( char cType ){
	
	switch ( cType ){
		case 'u': return ALL;
		case 'p': return POINT;
		case 'l': return LIST;
		case 'r': return ROOT;
		case 'i': return IF;
		case 'y': return PROPERTY;
		case 'f': return FUNCTION;
		case 'a': return AREA;
		case 'c': return COMMENT;
		case 'o': return EXT_OBJECT;
		case 's': return EXT_SUBOBJECT;
		case 'v': return FIB_SET;
		case 'm': return FIB_MATRIX;
	
	}
	return 0;
}


/**
 * @param index the index for which to return the Fib-elementtype char
 * @return the char for the elementtype, which has the given index in
 * 	the @see fibObjectCounts array
 */
char cFibObjectCounts::indexToElementType( const char index ){
	
	switch ( index ){
		case ALL:
			return 'u';
		case POINT:
			return 'p';
		case LIST:
			return 'l';
		case ROOT:
			return 'r';
		case IF:
			return 'i';
		case PROPERTY:
			return 'y';
		case FUNCTION:
			return 'f';
		case AREA:
			return 'a';
		case COMMENT:
			return 'c';
		case EXT_OBJECT:
			return 'o';
		case EXT_SUBOBJECT:
			return 's';
		case FIB_SET:
			return 'v';
		case FIB_MATRIX:
			return 'm';
	}
	return 'u';
}


/**
 * This function checks if the given type char stands for an valid /
 * existing type.
 *
 * @see cFibElement::getType()
 * @param cType the type char to check
 * @return true if the type for the given type char is valid /exists,
 * 	else false
 */
bool cFibObjectCounts::isValidType( const char cType ){

	if ( (cType == 'u') || (cType == 'p') || (cType == 'l') ||
			(cType == 'r') || (cType == 'i') || (cType == 'y') ||
			(cType == 'f') || (cType == 'a') || (cType == 'c') ||
			(cType == 'o') || (cType == 's') || (cType == 'v') ||
			(cType == 'm') ){
		//valid existing type
		return true;
	}
	return false;
}



#endif //___C_FIB_OBJECT_COUNTS_CPP__
