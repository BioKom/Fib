/**
 * @class cMatrix3DIntegerScaledDim3
 * file name: cMatrix3DIntegerScaledDim3.cpp
 * @author Betti Oesterholz
 * @date 04.03.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the implementation for 3 dimensional integer matrix
 * class, where the values are scaled according to ther third dimension index.
 *
 *
 * Copyright (C) @c LGPL3 2013 Betti Oesterholz
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
 * This file contains the implementation for 3 dimensional integer matrix
 * class, where the values are scaled according to ther third dimension index.
 * It stores a 3 dimensional matrix. The element of the matrix are integer
 * values. The index of the matrix are natural numbers beginning at 0 .
 */
/*
History:
04.03.2013  Oesterholz  created
*/


#include "cMatrix3DIntegerScaledDim3.h"

#include <string.h>


using namespace fib;


/**
 * constructor
 *
 * @param uiMaxIndexX the maximal index for the first (1. or x)
 * 	dimension; All index values in the first (1. or x) dimension are
 * 	positiv (including 0) natural numbers lower equal uiMaxIndexX .
 * 	@see uiBorderIndexX
 * @param uiMaxIndexY the maximal index for the second (2. or y)
 * 	dimension; All index values in the second (2. or y) dimension are
 * 	positiv (including 0) natural numbers lower equal uiMaxIndexY .
 * 	@see uiBorderIndexY
 * @param uiMaxIndexZ the maximal index for the third (3. or z)
 * 	dimension; All index values in the third (3. or z) dimension are
 * 	positiv (including 0) natural numbers lower equal uiMaxIndexZ .
 * 	@see uiBorderIndexZ
 * @param uiBitsPerValue The bits per integer entry value in the matrix.
 * 	The entry values in the matrix are in the range from
 * 	-1 * 2^(uiBitsPerEntry - 1) to 2^(uiBitsPerEntry - 1) - 1 .
 * 	@see uiBitsPerEntry
 * @param vecInScalingFactorsDim3 the scaling factors;
 * 	For indexes for which no scaling factor is given it will be set to 1 .
 * 	The values are scaled according to there third dimension index.
 * 	@see vecScalingFactorsDim3
 */
cMatrix3DIntegerScaledDim3::cMatrix3DIntegerScaledDim3(
		const unsigned int uiMaxIndexX, const unsigned int uiMaxIndexY,
		const unsigned int uiMaxIndexZ, const unsigned int uiBitsPerValue,
		const vector< doubleFib > vecInScalingFactorsDim3 ):
		cMatrix3DInteger( uiMaxIndexX, uiMaxIndexY, uiMaxIndexZ,
			uiBitsPerValue ){
	
	vecScalingFactorsDim3 = vector< doubleFib >( uiMaxIndexZ + 1, 1.0 );
	
	vector< doubleFib >::iterator
		itrToSetFactor = vecScalingFactorsDim3.begin();
	for ( vector< doubleFib >::const_iterator
			itrActualFactor = vecInScalingFactorsDim3.begin();
			( itrActualFactor != vecInScalingFactorsDim3.end() ) &&
			( itrToSetFactor != vecScalingFactorsDim3.end() );
			itrActualFactor++, itrToSetFactor++ ){
		
		(*itrToSetFactor) = (*itrActualFactor);
	}
}


/**
 * copy constructor
 *
 * @param matrix3DInteger the matrix to copy
 */
cMatrix3DIntegerScaledDim3::cMatrix3DIntegerScaledDim3(
		const cMatrix3DIntegerScaledDim3 & matrix3DInteger ):
		cMatrix3DInteger( matrix3DInteger ),
		vecScalingFactorsDim3( matrix3DInteger.vecScalingFactorsDim3 ){
	//nothing to do
}


/**
 * destructor
 */
cMatrix3DIntegerScaledDim3::~cMatrix3DIntegerScaledDim3(){
	//nothing to do
}


/**
 * This method clones this object.
 *
 * @return a pointer to the clone of this object
 */
cMatrix3DIntegerScaledDim3 * cMatrix3DIntegerScaledDim3::clone() const{
	
	return new cMatrix3DIntegerScaledDim3( *this );
}


/**
 * @return the name of this class
 */
string cMatrix3DIntegerScaledDim3::getName() const{
	
	return "cMatrix3DIntegerScaledDim3";
}


/**
 * With this method the value for a matrix element is set.
 *
 * @param dValue the value to set
 * @param uiPositionX the index on the first (x) dimension where to set
 * 	the value dValue
 * @param uiPositionY the index on the second (y) dimension where to set
 * 	the value dValue
 * @param uiPositionZ the index on the third (z) dimension where to set
 * 	the value dValue
 * @return OK (or 0) if the value could be set, else the error value
 * 	@see tErrorValue
 */
iMatrix3D::tErrorValue cMatrix3DIntegerScaledDim3::setValue( const doubleFib dValue,
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiPositionZ ){
	
	if ( uiBorderIndexX <= uiPositionX ){
		//no such entry
		return ERROR_OUTSIDE_INDEX_DIMENSION_1;
	}//else
	if ( uiBorderIndexY <= uiPositionY ){
		//no such entry
		return ERROR_OUTSIDE_INDEX_DIMENSION_2;
	}//else
	if ( uiBorderIndexZ <= uiPositionZ ){
		//no such entry
		return ERROR_OUTSIDE_INDEX_DIMENSION_3;
	}//else
	//scale value
	const longFib lValueToSet = roundToLongFib(
		dValue / vecScalingFactorsDim3[ uiPositionZ ] );
	
	if ( lValueToSet < lMinEntryValue ){
		//value lower minimum entry value -> don't set
		return ERROR_LOWER_MIN_VALUE;
	}//else
	if ( lMaxEntryValue < lValueToSet ){
		//value higher maximum entry value -> don't set
		return ERROR_GREATER_MAX_VALUE;
	}//else
	
	char * pEntry = matrix[ uiPositionZ ][ uiPositionY ] +
		uiPositionX * uiBytsPerEntry;
	memcpy( pEntry, &lValueToSet, uiBytsPerEntry );
	
	return OK;
}


/**
 * With this method the value for a matrix element is set.
 *
 * @param lValue the value to set
 * @param uiPositionX the index on the first (x) dimension where to set
 * 	the value dValue
 * @param uiPositionY the index on the second (y) dimension where to set
 * 	the value dValue
 * @param uiPositionZ the index on the third (z) dimension where to set
 * 	the value dValue
 * @return OK (or 0) if the value could be set, else the error value
 * 	@see tErrorValue
 */
iMatrix3D::tErrorValue cMatrix3DIntegerScaledDim3::setValue( const longFib lValue,
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiPositionZ ){
	
	if ( uiBorderIndexX <= uiPositionX ){
		//no such entry
		return ERROR_OUTSIDE_INDEX_DIMENSION_1;
	}//else
	if ( uiBorderIndexY <= uiPositionY ){
		//no such entry
		return ERROR_OUTSIDE_INDEX_DIMENSION_2;
	}//else
	if ( uiBorderIndexZ <= uiPositionZ ){
		//no such entry
		return ERROR_OUTSIDE_INDEX_DIMENSION_3;
	}//else
	//scale value
	const longFib lValueToSet = roundToLongFib( ((doubleFib)lValue) /
		vecScalingFactorsDim3[ uiPositionZ ] );
	
	if ( lValueToSet < lMinEntryValue ){
		//value lower minimum entry value -> don't set
		return ERROR_LOWER_MIN_VALUE;
	}//else
	if ( lMaxEntryValue < lValueToSet ){
		//value higher maximum entry value -> don't set
		return ERROR_GREATER_MAX_VALUE;
	}//else
	
	char * pEntry = matrix[ uiPositionZ ][ uiPositionY ] +
		uiPositionX * uiBytsPerEntry;
	memcpy( pEntry, &lValueToSet, uiBytsPerEntry );
	
	return OK;
}


/**
 * With this method the value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the value
 * @param uiPositionZ the index on the third (z) dimension of which to
 * 	return the value
 * @return the value of the given position in the matrix
 */
doubleFib cMatrix3DIntegerScaledDim3::getValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiPositionZ ) const{
	
	if ( ( uiBorderIndexX <= uiPositionX ) ||
			( uiBorderIndexY <= uiPositionY ) ||
			( uiBorderIndexZ <= uiPositionZ ) ){
		//no such entry
		return 0;
	}//else
	if ( uiBytsPerEntry == 0 ){
		//no byts per entry -> all entries 0
		return 0;
	}
	const char * pEntry = matrix[ uiPositionZ ][ uiPositionY ] +
		uiPositionX * uiBytsPerEntry;
	
	const char * pEntrySign = pEntry + (uiBytsPerEntry - 1);
	
	longFib lValue = ( ((*pEntrySign) & 0x80) == 0x80 )? -1 : 0;
	memcpy( &lValue, pEntry, uiBytsPerEntry );
	
	return ((doubleFib)(lValue)) * vecScalingFactorsDim3[ uiPositionZ ];
}


/**
 * With this method the integer value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the value
 * @param uiPositionZ the index for the third (z) dimension of which to
 * 	return the value
 * @return the integer value of the given position in the matrix
 */
longFib cMatrix3DIntegerScaledDim3::getValueLong( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiPositionZ ) const{
	
	if ( ( uiBorderIndexX <= uiPositionX ) ||
			( uiBorderIndexY <= uiPositionY ) ||
			( uiBorderIndexZ <= uiPositionZ ) ){
		//no such entry
		return 0;
	}//else
	if ( uiBytsPerEntry == 0 ){
		//no byts per entry -> all entries 0
		return 0;
	}
	const char * pEntry = matrix[ uiPositionZ ][ uiPositionY ] +
		uiPositionX * uiBytsPerEntry;
	
	const char * pEntrySign = pEntry + (uiBytsPerEntry - 1);
	
	longFib lValue = ( ((*pEntrySign) & 0x80) == 0x80 )? -1 : 0;
	memcpy( &lValue, pEntry, uiBytsPerEntry );
	
	return roundToLongFib( ((doubleFib)(lValue)) *
		vecScalingFactorsDim3[ uiPositionZ ] );
}


/**
 * With this method the minimum value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the minimum value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the minimum value
 * @param uiPositionZ the index on the third (z) dimension of which to
 * 	return the minimum value
 * @return the minimum value of the given position in the matrix
 */
doubleFib cMatrix3DIntegerScaledDim3::getMinValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiPositionZ ) const{
	
	if ( uiPositionZ < uiBorderIndexZ ){
		return ((doubleFib)(lMinEntryValue)) * vecScalingFactorsDim3[ uiPositionZ ];
	}
	return 0.0;
}


/**
 * With this method the minimum integer value for a matrix element is returned.
 *
 * @param uiPositionZ the index on the third (z) dimension of which to
 * 	return the minimum value
 * @return the minimum integer value for entries in the matrix with the
 * 	index uiPositionZ in the third dimension
 */
longFib cMatrix3DIntegerScaledDim3::getMinValueLong(
		const unsigned int uiPositionZ ) const{
	
	if ( uiPositionZ < uiBorderIndexZ ){
		return roundToLongFib( ((doubleFib)(lMinEntryValue)) *
			vecScalingFactorsDim3[ uiPositionZ ] );
	}
	return 0;
}


/**
 * With this method the maximum value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the maximum value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the maximum value
 * @param uiPositionZ the index on the third (z) dimension of which to
 * 	return the maximum value
 * @return the maximum value of the given position in the matrix
 */
doubleFib cMatrix3DIntegerScaledDim3::getMaxValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiPositionZ ) const{
	
	if ( uiPositionZ < uiBorderIndexZ ){
		return ((doubleFib)(lMaxEntryValue)) * vecScalingFactorsDim3[ uiPositionZ ];
	}
	return 0.0;
}


/**
 * With this method the maximum integer value for a matrix element is returned.
 *
 * @param uiPositionZ the index on the third (z) dimension of which to
 * 	return the maximum value
 * @return the maximum integer value for entries in the matrix with the
 * 	index uiPositionZ in the third dimension
 */
longFib cMatrix3DIntegerScaledDim3::getMaxValueLong(
		const unsigned int uiPositionZ ) const{
	
	if ( uiPositionZ < uiBorderIndexZ ){
		return roundToLongFib( ((doubleFib)(lMaxEntryValue)) *
			vecScalingFactorsDim3[ uiPositionZ ] );
	}
	return 0;
}


/**
 * With this method the minimal difference betwean two values for the
 * matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the minimal difference value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the minimal difference value
 * @param uiPositionZ the index on the third (z) dimension of which to
 * 	return the minimal difference value
 * @return the minimal difference betwean two values for the
 * 	matrix element
 */
doubleFib cMatrix3DIntegerScaledDim3::getMinDifference( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiPositionZ ) const{
	
	if ( uiPositionZ < uiBorderIndexZ ){
		return 1.0 * vecScalingFactorsDim3[ uiPositionZ ];
	}
	return 0.0;
}


/**
 * This method returns the maximum index value of the given direction/
 * dimension.
 * All index values for the direction uiDirection should be natural
 * numbers betwean (including) 0 and the returned value.
 *
 * @param uiDirection the direction for which the maximum value should
 * 	be returned (possible values are 0 to 2)
 * @return the maximum index value for the direction uiDirection
 */
unsigned int cMatrix3DIntegerScaledDim3::getMaxIndex(
		const unsigned int uiDirection ) const{
	
	if ( 2 < uiDirection ){
		//no such direction
		return 0;
	}//else
	if ( uiDirection == 0 ){
		return uiBorderIndexX - 1;
	}//else
	if ( uiDirection == 1 ){
		return uiBorderIndexY - 1;
	}//else
	if ( uiDirection == 2 ){
		return uiBorderIndexZ - 1;
	}//else
	//no such dimension -> maximal index 0
	return 0;
}


/**
 * @return the scaling factors for the values;
 * 	The values are scaled according to there third dimension index.
 * @see vecScalingFactorsDim3
 */
vector< doubleFib > cMatrix3DIntegerScaledDim3::getScalingFactors() const{
	
	return vecScalingFactorsDim3;
}


/**
 * This method checks if the given matrix is equal to this matrix.
 *
 * @param inMatrix the matrix, which should be equal to this matrix
 * @return true if the given matrix is equal to this matrix, else false
 */
bool cMatrix3DIntegerScaledDim3::equal( const iMatrix3D & inMatrix ) const{
	
	if ( getName() != inMatrix.getName() ){
		//not the correct matrix type
		return false;
	}
	cMatrix3DIntegerScaledDim3 * pOtherMatrix =
		((cMatrix3DIntegerScaledDim3*)(&inMatrix));
	if ( vecScalingFactorsDim3 != pOtherMatrix->vecScalingFactorsDim3 ){
		//scaling factors arn't the same
		return false;
	}
	//compare field of parrent class
	return cMatrix3DInteger::equal( inMatrix );
}


/**
 * This method returns a empty matrix for storing the derivate of this
 * matrix to.
 * With this method, child classes of the cMatrix3DInteger class can use
 * the same evalueDerivate() method and overwrite this method for the
 * respectivly cMatrix3DIntegerScaledDim3 child they need for ther derivation.
 *
 * @see evalueDerivate()
 * @param uiMaxIndexX the maximal index for the first (1. or x)
 * 	dimension for the to create martrix; All index values in the
 * 	first (1. or x) dimension are positiv (including 0) natural numbers
 * 	lower equal uiMaxIndexX .
 * 	@see uiBorderIndexX
 * @param uiMaxIndexY the maximal index for the second (2. or y)
 * 	dimension for the to create martrix; All index values in the
 * 	second (2. or y) dimension are positiv (including 0) natural numbers
 * 	lower equal uiMaxIndexY .
 * 	@see uiBorderIndexY
 * @param uiMaxIndexZ the maximal index for the third (3. or z)
 * 	dimension for the to create martrix; All index values in the
 * 	third (3. or z) dimension are positiv (including 0) natural numbers
 * 	lower equal uiMaxIndexZ .
 * 	@see uiBorderIndexZ
 * @param uiBitsPerValue The bits per integer entry value in the  to create matrix.
 * 	The unscaled entry values in the matrix are in the range from
 * 	-1 * 2^(uiBitsPerEntry - 1) to 2^(uiBitsPerEntry - 1) - 1 .
 * 	@see uiBitsPerEntry
 * @return a pointer to the cMatrix3DIntegerScaledDim3 (or child of it)
 * 	matrix with the given size, to store the derivate of this matrix to
 * 	Beware: You have to care that the returnd object is deleted.
 */
cMatrix3DIntegerScaledDim3 * cMatrix3DIntegerScaledDim3::getEmptyMatrixForDerivate(
		const unsigned int uiMaxIndexX, const unsigned int uiMaxIndexY,
		const unsigned int uiMaxIndexZ, const unsigned int uiBitsPerValue ) const{
	
	return new cMatrix3DIntegerScaledDim3( uiMaxIndexX, uiMaxIndexY, uiMaxIndexZ,
		uiBitsPerValue, vecScalingFactorsDim3 );
}






