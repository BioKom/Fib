/**
 * @class iMatrix3D
 * file name: iMatrix3D.h
 * @author Betti Oesterholz
 * @date 28.02.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the interface for 3 dimensional matrix data classes.
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
 * This file contains the interface for 3 dimensional matrix data classes.
 * It stores a 3 dimensional matrix. The elements of the matrix are values.
 * The index of the matrix are natural numbers beginning at 0 .
 * The numbering of the directions for the dimensions also begin with 0,
 * so dimension 1 is direction 0 .
 */
/*
History:
28.02.2013  Oesterholz  created
*/

#ifndef ___FIB__I_MATRIX_3_D__
#define ___FIB__I_MATRIX_3_D__

#include "version.h"

#include "fibDatatyps.h"

#include <string>


using std::string;


namespace fib{

class iMatrix3D{
public:
	
	enum tErrorValue{
		OK = 0,
		ERROR_OUTSIDE_INDEX_DIMENSION_1,
		ERROR_OUTSIDE_INDEX_DIMENSION_2,
		ERROR_OUTSIDE_INDEX_DIMENSION_3,
		ERROR_LOWER_MIN_VALUE,
		ERROR_GREATER_MAX_VALUE,
		ERROR
	};
	
	
	/**
	 * destructor
	 */
	virtual ~iMatrix3D(){};

	/**
	 * This method clones this object.
	 *
	 * @return a pointer to the clone of this object
	 */
	virtual iMatrix3D * clone() const = 0;
	
	/**
	 * @return the name of this class
	 */
	virtual string getName() const = 0;
	
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
	virtual tErrorValue setValue( const doubleFib dValue,
		const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0,
		const unsigned int uiPositionZ = 0 ) = 0;
	
	/**
	 * With this method the integer value for a matrix element is set.
	 *
	 * @param lValue the integer value to set
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
		const unsigned int uiPositionZ = 0 ) = 0;

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
	virtual doubleFib getValue( const unsigned int uiPositionX = 0,
		const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const = 0;
	
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
		const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const = 0;
	
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
		const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const = 0;
	
	/**
	 * With this method the minimal difference betwean two values for the
	 * matrix element is returned.
	 *
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the maximum value
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the maximum value
	 * @param uiPositionZ the index on the third (z) dimension of which to
	 * 	return the maximum value
	 * @return the minimal difference betwean two values for the
	 * 	matrix element
	 */
	virtual doubleFib getMinDifference( const unsigned int uiPositionX = 0,
		const unsigned int uiPositionY = 0, const unsigned int uiPositionZ = 0 ) const = 0;
	
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
	virtual unsigned int getMaxIndex( const unsigned int uiDirection = 0 ) const = 0;
	
	/**
	 * This method clears the data form the matrix.
	 * All entries of the matrix are set to 0 .
	 */
	virtual void clear() = 0;
	
	/**
	 * This method checks if the given matrix is equal to this matrix.
	 *
	 * @param matrix the matrix, which should be equal to this matrix
	 * @return true if the given matrix is equal to this matrix, else false
	 */
	virtual bool equal( const iMatrix3D &matrix ) const = 0;

	/**
	 * This method checks if the given matrix is equal to this matrix.
	 *
	 * @param matrix the matrix, which should be equal to this matrix
	 * @return true if the given matrix is equal to this matrix, else false
	 */
	virtual bool operator==( const iMatrix3D &matrix ) const{
		
		return this->equal( matrix );
	}
	
	
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
	virtual iMatrix3D * evalueDerivate( const unsigned int uiDirection = 0 ) const = 0;
	
};//class iMatrix3D

};

#endif


