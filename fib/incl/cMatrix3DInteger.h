/**
 * @class cMatrix3DInteger
 * file name: cMatrix3DInteger.h
 * @author Betti Oesterholz
 * @date 04.03.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the specification for 3 dimensional integer matrix class.
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
 * This file contains the specification for 3 dimensional integer matrix class.
 * It stores a 3 dimensional matrix. The element of the matrix are integer
 * values. The index of the matrix are natural numbers beginning at 0 .
 */
/*
History:
04.03.2013  Oesterholz  created
*/

#ifndef ___C_MATRIX_3_D_INTEGER__
#define ___C_MATRIX_3_D_INTEGER__

#include "version.h"

#include "fibDatatyps.h"
#include "iMatrix3D.h"

#include <string>
#include <vector>


using namespace std;

namespace fib{

class cMatrix3DInteger: public iMatrix3D{
protected:
	
	/**
	 * The data matrix which this object represents.
	 * The first vector is for the third (3. or z) dimension index.
	 * The second vector is for the second (2. or y) dimension index.
	 * The first demension is stored in a char array.
	 *
	 * If you want the matrix entry ( x, y, z) you go to the point:
	 * 	(matrix[ z ].[ y ]) + x * uiBytsPerEntry
	 * @see uiBytsPerEntry
	 * @see uiBorderIndexX
	 * @see uiBorderIndexY
	 * @see uiBorderIndexZ
	 */
	vector< vector< char* > > matrix;
	
	/**
	 * All index values in the first (1. or x) dimension are positiv
	 * (including 0) natural numbers lower uiBorderIndexX .
	 * @see matrix
	 */
	const unsigned int uiBorderIndexX;
	
	/**
	 * All index values in the second (2. or y) dimension are positiv
	 * (including 0) natural numbers lower uiBorderIndexY .
	 * @see matrix
	 */
	const unsigned int uiBorderIndexY;
	
	/**
	 * All index values in the third (3. or z) dimension are positiv
	 * (including 0) natural numbers lower uiBorderIndexZ .
	 * @see matrix
	 */
	const unsigned int uiBorderIndexZ;
	
	/**
	 * The bits per integer entry value in the matrix.
	 * The entry values in the matrix are in the range from
	 * -1 * 2^(uiBitsPerEntry - 1) to 2^(uiBitsPerEntry - 1) - 1 .
	 */
	const unsigned int uiBitsPerEntry;
	
	/**
	 * The byts per integer entry value in the memory.
	 * uiBytsPerEntry = ( uiBitsPerEntry - 1 ) / 8 + 1.
	 * @see matrix
	 */
	const unsigned int uiBytsPerEntry;
	
	/**
	 * The minimum integer value for a entry.
	 */
	const longFib lMinEntryValue;
	
	/**
	 * The maximum integer value for a entry.
	 */
	const longFib lMaxEntryValue;
	
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
	 */
	cMatrix3DInteger( const unsigned int uiMaxIndexX,
		const unsigned int uiMaxIndexY, const unsigned int uiMaxIndexZ,
		const unsigned int uiBitsPerValue = 1 );
	
	/**
	 * copy constructor
	 *
	 * @param matrix3DInteger the matrix to copy
	 */
	cMatrix3DInteger( const cMatrix3DInteger & matrix3DInteger );
	
	/**
	 * destructor
	 */
	virtual ~cMatrix3DInteger();
	
	
	/**
	 * This method clones this object.
	 *
	 * @return a pointer to the clone of this object
	 */
	virtual cMatrix3DInteger * clone() const;
	
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
	 * @return the minimum integer value for entries in the matrix
	 */
	virtual longFib getMinValueLong() const;
	
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
	 * @return the maximum integer value for entries in the matrix
	 */
	virtual longFib getMaxValueLong() const;
	
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
	 * @return the bits per integer entry value in this matrix
	 */
	unsigned int getBitsPerValue() const;
	
	
	/**
	 * This method clears the data form the matrix.
	 * All entries of the matrix are set to 0 .
	 */
	virtual void clear();
	
	/**
	 * This method checks if the given matrix is equal to this matrix.
	 *
	 * @param inMatrix the matrix, which should be equal to this matrix
	 * @return true if the given matrix is equal to this matrix, else false
	 */
	virtual bool equal( const iMatrix3D &inMatrix ) const;

	
	/**
	 * This function evalues the derivate of the matrix in the given
	 * direction / dimension.
	 *
	 * @param uiDirection the direction in which the derivation should
	 * 	be evalued (possible values are 0 to 2)
	 * @return a pointer to the derivate matrix in the given direction of
	 * 	this matrix, or NULL if non exists
	 * 	Beware: You have to care that the returnd object is deleted.
	 */
	virtual cMatrix3DInteger * evalueDerivate( const unsigned int uiDirection = 0 ) const;
	
protected:
	
	/**
	 * This method returns a empty matrix for storing the derivate of this
	 * matrix to.
	 * With this method child classes of this class can use the same
	 * evalueDerivate() method and overwrite this method for the respectivly
	 * cMatrix3DInteger child they need for ther derivation.
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
	 * @param uiBitsPerValue The bits per integer entry value in the created matrix.
	 * 	The entry values in the matrix are in the range from
	 * 	-1 * 2^(uiBitsPerEntry - 1) to 2^(uiBitsPerEntry - 1) - 1 .
	 * 	@see uiBitsPerEntry
	 * @return a pointer to the cMatrix3DInteger (or child of it) matrix with
	 * 	the given size, to store the derivate of this matrix to
	 * 	Beware: You have to care that the returnd object is deleted.
	 */
	virtual cMatrix3DInteger * getEmptyMatrixForDerivate(
		const unsigned int uiMaxIndexX, const unsigned int uiMaxIndexY,
		const unsigned int uiMaxIndexZ, const unsigned int uiBitsPerValue ) const;
	
	/**
	 * @return the minimum possible entry value for the given bit per entry:
	 * 	-1 * 2^(uiBitsPerEntry - 1)
	 * 	@see uiBitsPerEntry
	 * 	@see lMinEntryValue
	 */
	static longFib evalueMinValue( const unsigned int uiBitsPerEntry );
	
	/**
	 * @return the maximum possible entry value for the given bit per entry:
	 * 	 2^(uiBitsPerEntry - 1) - 1
	 * 	@see uiBitsPerEntry
	 * 	@see lMaxEntryValue
	 */
	static longFib evalueMaxValue( const unsigned int uiBitsPerEntry );
	
};//class cMatrix3DInteger

};

#endif


