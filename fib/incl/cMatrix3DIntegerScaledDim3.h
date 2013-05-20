/**
 * @class cMatrix3DIntegerScaledDim3
 * file name: cMatrix3DIntegerScaledDim3.h
 * @author Betti Oesterholz
 * @date 04.03.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the specification for 3 dimensional integer matrix
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
 * This file contains the specification for 3 dimensional integer matrix
 * class, where the values are scaled according to ther third dimension index.
 * It stores a 3 dimensional matrix. The element of the matrix are integer
 * values. The index of the matrix are natural numbers beginning at 0 .
 */
/*
History:
11.03.2013  Oesterholz  created
*/

#ifndef ___C_MATRIX_3_D_INTEGER_SCALED_DIM_3__
#define ___C_MATRIX_3_D_INTEGER_SCALED_DIM_3__

#include "version.h"

#include "fibDatatyps.h"
#include "cMatrix3DInteger.h"

#include <string>
#include <vector>


using namespace std;

namespace fib{

class cMatrix3DIntegerScaledDim3: public cMatrix3DInteger{
protected:
	
	/**
	 * The scaling factors.
	 * The values are scaled according to there third dimension index.
	 * So if the matrix contains the integer value lValue[x][y][z] the
	 * value lValue[x][y][z] * vecScalingFactorsDim3[z] will be returned.
	 */
	vector< doubleFib > vecScalingFactorsDim3;
	
public:
	
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
	cMatrix3DIntegerScaledDim3( const unsigned int uiMaxIndexX,
		const unsigned int uiMaxIndexY, const unsigned int uiMaxIndexZ,
		const unsigned int uiBitsPerValue = 1,
		const vector< doubleFib > vecInScalingFactorsDim3 = vector< doubleFib >() );
	
	/**
	 * copy constructor
	 *
	 * @param matrix3DInteger the matrix to copy
	 */
	cMatrix3DIntegerScaledDim3( const cMatrix3DIntegerScaledDim3 & matrix3DInteger );
	
	/**
	 * destructor
	 */
	virtual ~cMatrix3DIntegerScaledDim3();
	
	
	/**
	 * This method clones this object.
	 *
	 * @return a pointer to the clone of this object
	 */
	virtual cMatrix3DIntegerScaledDim3 * clone() const;
	
	/**
	 * @return the name of this class
	 */
	virtual string getName() const;
	
	/**
	 * With this method a value for a matrix element is set.
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
	virtual tErrorValue setValue( const doubleFib dValue,
		const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0,
		const unsigned int uiPositionZ = 0 );
	
	/**
	 * With this method a integer value for a matrix element is set.
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
	virtual tErrorValue setValue( const longFib lValue,
		const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0,
		const unsigned int uiPositionZ = 0 );

	/**
	 * With this method the value of a matrix element is returned.
	 *
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the value
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the value
	 * @param uiPositionZ the index on the third (z) dimension of which to
	 * 	return the value
	 * @return the value of the given position in the matrix
	 */
	virtual doubleFib getValue( const unsigned int uiPositionX = 0,
		const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const;
	
	/**
	 * With this method the integer value of a matrix element is returned.
	 *
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the value
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the value
	 * @param uiPositionZ the index for the third (z) dimension of which to
	 * 	return the value
	 * @return the integer value of the given position in the matrix
	 */
	virtual longFib getValueLong( const unsigned int uiPositionX = 0,
		const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const;
	
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
	virtual doubleFib getMinValue( const unsigned int uiPositionX = 0,
		const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const;
	
	/**
	 * With this method the minimum integer value for a matrix element is returned.
	 *
	 * @param uiPositionZ the index on the third (z) dimension of which to
	 * 	return the minimum value
	 * @return the minimum integer value for entries in the matrix with the
	 * 	index uiPositionZ in the third dimension
	 */
	virtual longFib getMinValueLong( const unsigned int uiPositionZ = 0 ) const;
	
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
	virtual doubleFib getMaxValue( const unsigned int uiPositionX = 0,
		const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const;
	
	/**
	 * With this method the maximum integer value for a matrix element is returned.
	 *
	 * @param uiPositionZ the index on the third (z) dimension of which to
	 * 	return the maximum value
	 * @return the maximum integer value for entries in the matrix with the
	 * 	index uiPositionZ in the third dimension
	 */
	virtual longFib getMaxValueLong( const unsigned int uiPositionZ = 0 ) const;
	
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
	virtual doubleFib getMinDifference( const unsigned int uiPositionX = 0,
		const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const;
	
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
	virtual unsigned int getMaxIndex( const unsigned int uiDirection = 0 ) const;
	
	
	/**
	 * @return the scaling factors for the values;
	 * 	The values are scaled according to there third dimension index.
	 * @see vecScalingFactorsDim3
	 */
	vector< doubleFib > getScalingFactors() const;
	
	
	/**
	 * This method checks if the given matrix is equal to this matrix.
	 *
	 * @param inMatrix the matrix, which should be equal to this matrix
	 * @return true if the given matrix is equal to this matrix, else false
	 */
	virtual bool equal( const iMatrix3D &inMatrix ) const;

protected:
	
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
	 * @param uiBitsPerValue The bits per integer entry value in the to create matrix.
	 * 	The unscaled entry values in the matrix are in the range from
	 * 	-1 * 2^(uiBitsPerEntry - 1) to 2^(uiBitsPerEntry - 1) - 1 .
	 * 	@see uiBitsPerEntry
	 * @return a pointer to the cMatrix3DIntegerScaledDim3 (or child of it)
	 * 	matrix with the given size, to store the derivate of this matrix to
	 * 	Beware: You have to care that the returnd object is deleted.
	 */
	virtual cMatrix3DIntegerScaledDim3 * getEmptyMatrixForDerivate(
		const unsigned int uiMaxIndexX, const unsigned int uiMaxIndexY,
		const unsigned int uiMaxIndexZ, const unsigned int uiBitsPerValue ) const;
	
};//class cMatrix3DIntegerScaledDim3

};

#endif


