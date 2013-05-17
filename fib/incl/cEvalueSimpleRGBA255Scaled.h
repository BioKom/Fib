/**
 * @class cEvalueSimpleRGBA255Scaled
 * file name: cEvalueSimpleRGBA255Scaled.h
 * @author Betti Oesterholz
 * @date 23.02.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the class for evaluing Fib objects as a matrix of
 * a RGBA image.
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
 * This file contains the class for evaluing Fib objects as a matrix of
 * a RGBA image. @see pImageData
 * Just colors and transparency is evalued. The data is stored into an
 * array. The array is two dimensional and goes in the first dimension
 * from 0 to uiBorderIndexX and in the second from 0 to uiBorderIndexY. Every entry of the
 * array consists of tree values with 8 bit each (values from 0 to 255).
 * This class should keep the evaluing of a normal image (e.g. Bitmap image)
 * as simple as possible.
 * The input property vector values will be scaled with given scaling factors.
 */
/*
History:
23.02.2013  Oesterholz  created
24.02.2013  Oesterholz  clone method and copy constructor added
*/

#ifndef ___FIB__C_EVALUE_SIMPLE_RGBA_255_SCALED__
#define ___FIB__C_EVALUE_SIMPLE_RGBA_255_SCALED__

#include "version.h"

#include "cEvalueSimpleRGBA255.h"
#include "cMatrix3DIntegerScaledDim3.h"
#include "iImageData.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"


#include <list>



using std::list;

namespace fib{

class cEvalueSimpleRGBA255Scaled: public virtual cEvalueSimpleRGBA255{
public:
	
	
	/**
	 * The scaling factor for the transparency values.
	 * The scaling factor should be a value, so that all evalued transparency
	 * values multiplied by the scaling factor are betwean (including) 0 and 255.
	 */
	const doubleFib dScalingFactorAlpha;
	
	/**
	 * The scaling factor for the color red.
	 * The scaling factor should be a value, so that all evalued color red
	 * values multiplied by the scaling factor are betwean (including) 0 and 255.
	 */
	const doubleFib dScalingFactorRed;
	
	/**
	 * The scaling factor for the color green.
	 * The scaling factor should be a value, so that all evalued color green
	 * values multiplied by the scaling factor are betwean (including) 0 and 255.
	 */
	const doubleFib dScalingFactorGreen;
	
	/**
	 * The scaling factor for the color blue.
	 * The scaling factor should be a value, so that all evalued color blue
	 * values multiplied by the scaling factor are betwean (including) 0 and 255.
	 */
	const doubleFib dScalingFactorBlue;
	
	
	/**
	 * standard constructor
	 * The given scaling factors should be a values, so that all evalued
	 * property values multiplied by the scaling factor are betwean
	 * (including) 0 and 255.
	 *
	 * @param uiInMaxX the maximum value for the first (x) dimension @see uiBorderIndexX
	 * @param uiInMaxY the maximum value for the second (y) dimension @see uiBorderIndexY
	 * @param dInScalingFactorAlpha the scaling factor for the color alpha
	 * 	@see dScalingFactorAlpha
	 * @param dInScalingFactorRed the scaling factor for the color red
	 * 	@see dScalingFactorRed
	 * @param dInScalingFactorGreen the scaling factor for the color green
	 * 	@see dScalingFactorGreen
	 * @param dInScalingFactorBlue the scaling factor for the color blue
	 * 	@see dScalingFactorBlue
	 */
	cEvalueSimpleRGBA255Scaled( const unsigned int uiInMaxX,
			const unsigned int uiInMaxY,
			const doubleFib dInScalingFactorAlpha = 1.0,
			const doubleFib dInScalingFactorRed = 1.0,
			const doubleFib dInScalingFactorGreen = 1.0,
			const doubleFib dInScalingFactorBlue = 1.0 );

	/**
	 * copy constructor
	 *
	 * @param cEvalueSimpleRGBA255Scaled the cEvalueSimpleRGBA255Scaled to copy
	 */
	cEvalueSimpleRGBA255Scaled( const cEvalueSimpleRGBA255Scaled & evalueSimpleRGBA255 );

	/**
	 * desstructor
	 */
	virtual ~cEvalueSimpleRGBA255Scaled();

	/**
	 * @return the name of this class
	 */
	virtual string getName() const;
	
	/**
	 * This method clones this object.
	 *
	 * @return a pointer to the clone of this object
	 */
	virtual cEvalueSimpleRGBA255Scaled * clone() const;
	
//methods of interface iImageData:
	
	/**
	 * This method returns the domains for the color and transparency properties.
	 *
	 * @return the domains for the color and transparency properties
	 */
	virtual cDomains getPropertyDomains() const;

	/**
	 * With this method the properties for a point are set.
	 *
	 * @param vPosition the position of the point to set
	 * @param vProperties a list of the properties of the point
	 * @return true if the properties for the point cold be set, else false
	 */
	virtual bool setPoint(  const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties );
	
	/**
	 * This method checks if the given matrix is equal to this matrix.
	 *
	 * @param matrix the matrix, which should be equal to this matrix
	 * @return true if the given matrix is equal to this matrix, else false
	 */
	virtual bool equal( const iMatrix3D &matrix ) const;
	
	/**
	 * With this method the properties for given point are returned.
	 *
	 * @param vPosition the position of the point, for which the properties
	 * 	should be returned
	 * @return a list of the properties of the point
	 */
	virtual list<cVectorProperty> getPointProperties(
		const cVectorPosition & vPosition ) const;

	
	/**
	 * With this method the value for a matrix element is set.
	 *
	 * @param dValue the value to set
	 * @param uiPositionX the index on the first (x) dimension where to set
	 * 	the value dValue
	 * @param uiPositionY the index on the second (y) dimension where to set
	 * 	the value dValue
	 * @param uiChanel the index for the property chanel;
	 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
	 * @return OK (or 0) if the value could be set, else the error value
	 * 	@see tErrorValue
	 */
	virtual tErrorValue setValue( const doubleFib dValue,
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiChanel = 0 );
	
	/**
	 * With this method a integer value for a matrix element is set.
	 *
	 * @param lValue the value to set
	 * @param uiPositionX the index on the first (x) dimension where to set
	 * 	the value dValue
	 * @param uiPositionY the index on the second (y) dimension where to set
	 * 	the value dValue
	 * @param uiChanel the index for the property chanel;
	 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
	 * @return OK (or 0) if the value could be set, else the error value
	 * 	@see tErrorValue
	 */
	virtual tErrorValue setValue( const longFib lValue,
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiChanel = 0 );

	/**
	 * With this method a unscaled integer value for a matrix element is set.
	 *
	 * @param uiValue the value to set
	 * @param uiPositionX the index on the first (x) dimension where to set
	 * 	the value dValue
	 * @param uiPositionY the index on the second (y) dimension where to set
	 * 	the value dValue
	 * @param uiChanel the index for the property chanel;
	 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
	 * @return OK (or 0) if the value could be set, else the error value
	 * 	@see tErrorValue
	 */
	virtual tErrorValue setValueUInt( const unsigned int uiValue,
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiChanel = 0 );

	/**
	 * With this method the value for a matrix element is returned.
	 *
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the value
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the value
	 * @param uiChanel the index for the property chanel;
	 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
	 * @return the value of the given position in the matrix
	 */
	virtual doubleFib getValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel = 0 ) const;
	
	/**
	 * With this method the unscaled value for a matrix element is returned.
	 *
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the value
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the value
	 * @param uiChanel the index for the property chanel;
	 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
	 * @return the value of the given position in the matrix
	 *
	virtual unsigned int getValueUInt( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel = 0 ) const;
	 */
	
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
		const unsigned int uiPositionY = 0, const unsigned int uiChanel = 0 ) const;
	
	/**
	 * With this method the unscaled minimum integer value for a matrix
	 * element is returned.
	 *
	 * @return the minimum integer value for entries in the matrix
	 *
	virtual longFib getMinValueUInt() const;
	 */
	
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
		const unsigned int uiPositionY = 0, const unsigned int uiChanel = 0 ) const;
	
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
	 * With this method the unscaled maximum integer value for a matrix
	 * element is returned.
	 *
	 * @return the maximum integer value for entries in the matrix
	 *
	virtual longFib getMaxValueUInt() const;
	 */
	
	/**
	 * This method evalues the difference of two points properties.
	 * This difference is the sum of the difference of the property
	 * vector elements or the sum of the distance betwean the third dimension
	 * elements on the given positions.
	 *
	 * @param uiPositionX the index on the first (x) dimension of the first
	 * 	point for the first property vector
	 * @param uiPositionY the index on the second (y) dimension of the first
	 * 	point for the first property vector
	 * @param uiPositionX the index on the first (x) dimension of the second
	 * 	point for the second property vector
	 * @param uiPositionY the index on the second (y) dimension of the second
	 * 	point for the second property vector
	 * @return the sum of distances betwean the vector elements of the
	 * 	third dimension (properties) of the first and second point
	 */
	virtual doubleFib getDifference(
		const unsigned int uiPosition1X, const unsigned int uiPosition1Y,
		const unsigned int uiPosition2X = 0, const unsigned int uiPosition2Y = 0 )
			const;
	
	/**
	 * This method evalues the difference of two points properties.
	 * This difference is the sum of the difference of the property
	 * vector elements or the sum of the distance betwean the third dimension
	 * elements for the property on the given positions.
	 *
	 * @param uiPositionX the index on the first (x) dimension of the first
	 * 	point for the first property vector
	 * @param uiPositionY the index on the second (y) dimension of the first
	 * 	point for the first property vector
	 * @param uiPositionX the index on the first (x) dimension of the second
	 * 	point for the second property vector
	 * @param uiPositionY the index on the second (y) dimension of the second
	 * 	point for the second property vector
	 * @param uiPropertyType the type number of the property to return the
	 * 	distances of (e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
	 * @return the sum of distances betwean the vector elements of the
	 * 	third dimension of the property of the first and second point
	 */
	virtual doubleFib getDifference(
		const unsigned int uiPosition1X, const unsigned int uiPosition1Y,
		const unsigned int uiPosition2X, const unsigned int uiPosition2Y,
		const unsigned int uiPropertyType ) const;
	
	using cEvalueSimpleRGBA255::getDifference;
	
	/**
	 * This method returns the property of the given type for the image
	 * position.
	 * (The properties are given by the third dimension vector on the position.)
	 *
	 * @param vPosition the position of which to return the property vector
	 * @param uiPropertyType the type number of the property to return
	 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
	 * @return the property for the given type uiPropertyType from the given
	 * 	position or the property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getProperty( const cVectorPosition & vPosition,
		const unsigned int uiPropertyType = 0 ) const;

	/**
	 * This method returns the property of the given type for the image
	 * position.
	 * (The properties are given by the third dimension vector on the position.)
	 *
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the property vector
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the property vector
	 * @param uiPropertyType the type number of the property to return
	 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
	 * @return the property for the given type uiPropertyType from the given
	 * 	position or the property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getProperty( const unsigned int uiPositionX = 0,
		const unsigned int uiPositionY = 0,
		const unsigned int uiPropertyType = 0 ) const;

	using cEvalueSimpleRGBA255::getProperty;
	
	/**
	 * This method returns the uiPropertyNumber'th property for the image
	 * position.
	 * (The properties are given by the third dimension vector on the position.)
	 *
	 * @param vPosition the position of which to return the property vector
	 * @param uiPropertyNumber the number of the property to return;
	 * 	counting starts with 1; @see getNumberOfProperties()
	 * @return the uiPropertyNumber'th property from the given position or the
	 * 	property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getPropertyForNumber( const cVectorPosition & vPosition,
		const unsigned int uiPropertyNumber = 0 ) const;
	
	
	/**
	 * This method returns the uiPropertyNumber'th property for the image
	 * position.
	 * (The properties are given by the third dimension vector on the position.)
	 *
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the property vector
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the property vector
	 * @param uiPropertyNumber the number of the property to return;
	 * 	counting starts with 1; @see getNumberOfProperties()
	 * @return the uiPropertyNumber'th property from the given position or the
	 * 	property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getPropertyForNumber( const unsigned int uiPositionX = 0,
		const unsigned int uiPositionY = 0,
		const unsigned int uiPropertyNumber = 0 ) const;
		
	using cEvalueSimpleRGBA255::getPropertyForNumber;
	
protected:
	
	/**
	 * This method returns an empty matrix for storing the derivate of this
	 * matrix to.
	 * With this method child classes of the cEvalueSimpleRGBA255 class can
	 * use the same evalueDerivate() method and overwrite this method for the
	 * respectivly cMatrix3DInteger child they need for their derivation.
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
	 * @return a pointer to the cMatrix3DIntegerScaledDim3 (or child of it) matrix with
	 * 	the given size, to store the derivate of this matrix to
	 * 	Beware: You have to care that the returnd object is deleted.
	 */
	virtual cMatrix3DIntegerScaledDim3 * getEmptyMatrixForDerivate(
		const unsigned int uiMaxIndexX, const unsigned int uiMaxIndexY,
		const unsigned int uiMaxIndexZ, const unsigned int uiBitsPerValue ) const;
	

};//class cEvalueSimpleRGBA255Scaled

};

#endif


