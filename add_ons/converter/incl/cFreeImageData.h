/**
 * @class cFreeImageData
 * file name: cFreeImageData.h
 * @author Betti Oesterholz
 * @date 14.04.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains a warper class for FreeImage image data with the
 * iImageData interface.
 * Copyright (C) @c LGPL3 2012 Betti Oesterholz
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
 * This file contains a warper class for FreeImage image data with the
 * iImageData interface.
 * (TODO: Just implemented for RGB images. No palettized image implemented.)
 * @pattern Fassade
 */
/*
History:
14.04.2012  Oesterholz  created
19.02.2013  Oesterholz  clone method and copy constructor added
*/

#ifndef ___FIB__C_FREE_IMAGE_DATA__
#define ___FIB__C_FREE_IMAGE_DATA__

#include "version.h"

#include "iImageData.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"

#include "fipImage.h"


#include <list>



using std::list;

namespace fib{

class cFreeImageData: public iImageData{
public:

	
	/**
	 * The object, for which this class is the wraper.
	 */
	fipImage * pFipImageDataObject;
	
	
	/**
	 * standard constructor
	 *
	 * @param pInFipImageDataObject a pointer to the object, for which this
	 * 	class is the wraper
	 */
	cFreeImageData( fipImage * pInFipImageDataObject );

	/**
	 * copy constructor
	 *
	 * @param freeImageData the cFreeImageData object to copy
	 */
	cFreeImageData( cFreeImageData & freeImageData );

	/**
	 * destructor
	 */
	virtual ~cFreeImageData();

	/**
	 * @return the name of this class
	 */
	virtual string getName() const;
	
	/**
	 * This method clones this object.
	 *
	 * @return a pointer to the clone of this object
	 */
	virtual cFreeImageData * clone() const;
	
	
	/**
	 * This method returns the domains for the color and transparency properties.
	 *
	 * @return the domains for the color and transparency properties
	 */
	virtual cDomains getPropertyDomains() const;

	/**
	 * This method returns the domains for the positions (dimension domain).
	 *
	 * @return the domains for the positions (dimension domain)
	 */
	virtual cDomains getPositionDomain() const;
	
	/**
	 * With this method the properties for a points are set.
	 * Beware: No scaling is done. The position coordinate values are taken
	 * as index values (counting starts at 0) for the image matrix. Color and
	 * transparency values should be numbers from 0 to 255 (inclusive).
	 *
	 * @param vPosition the position of the point to set
	 * @param vProperties a list of the properties of the point
	 * @return true if the properties for the point cold be set, else false
	 */
	virtual bool setPoint( const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties );
	
	/**
	 * With this method the properties for given points are returned.
	 *
	 * @param vPosition the position of the point, for which the properties
	 * 	should be returned
	 * @return a list of the properties of the point
	 */
	virtual list<cVectorProperty> getPointProperties(
		const cVectorPosition & vPosition ) const;

	/**
	 * This method clears the data from the list with the evalued position data
	 * liEvaluedPositionData.
	 * After the function call the liEvaluedPositionData list will be empty.
	 *
	 * @see liEvaluedPositionData
	 */
	virtual void clear();
	
	
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
	 * With this method the value for a matrix element is set.
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
	virtual unsigned int getValueUInt( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel = 0 ) const;
	
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
	 * With this method the minimum integer value for a matrix element is returned.
	 *
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the minimum value
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the minimum value
	 * @param uiPositionZ the index on the third (z) dimension of which to
	 * 	return the minimum value
	 * @return the minimum integer value of the given position in the matrix
	 */
	virtual unsigned int getMinValueUInt( const unsigned int uiPositionX = 0,
		const unsigned int uiPositionY = 0, const unsigned int uiChanel = 0 ) const;
	
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
	 * With this method the maximum integer value for a matrix element is returned.
	 *
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the maximum value
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the maximum value
	 * @param uiPositionZ the index on the third (z) dimension of which to
	 * 	return the maximum value
	 * @return the maximum integer value of the given position in the matrix
	 */
	virtual unsigned int getMaxValueUInt( const unsigned int uiPositionX = 0,
		const unsigned int uiPositionY = 0, const unsigned int uiChanel = 0 ) const;

	/**
	 * This method returns the maximum index values of the given direction/
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
	 * This method checks if the given matrix is equal to this matrix.
	 *
	 * @param matrix the matrix, which should be equal to this matrix
	 * @return true if the given matrix is equal to this matrix, else false
	 */
	virtual bool equal( const iMatrix3D &matrix ) const;

	/**
	 * This method evalues the derivate of the matrix in the given
	 * direction / dimension.
	 *
	 * @param uiDirection the direction in which the derivation should
	 * 	be evalued (possible values are 0 to 2)
	 * @return a pointer to the derivate matrix in the given direction of
	 * 	this matrix, or NULL if non exists
	 * 	Beware: You have to care that the returnd object is deleted.
	 */
	virtual iMatrix3D * evalueDerivate( const unsigned int uiDirection ) const;

	
	/**
	 * This method evalues the difference of two points properties.
	 * This difference is the sum of the difference of the property
	 * vectors elements or the sum of the distance betwean the third dimension
	 * elements on the given positions.
	 *
	 * @param vPosition1 the first point for the first property vector
	 * @param vPosition2 the second point for the second property vector
	 * @return the sum of distances betwean the vector elements of the
	 * 	properties of the first and second point
	 */
	virtual doubleFib getDifference( const cVectorPosition & vPosition1,
		const cVectorPosition & vPosition2 ) const;
	
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
	 * This method returns the number of properties for the image position.
	 * (The properties are given by the third dimension vector on the position.)
	 *
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the number of property vectors
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the number of property vectors
	 * @return the number of property vectors for the given position
	 */
	virtual unsigned int getNumberOfProperties( const unsigned int uiPositionX = 0,
		const unsigned int uiPositionY = 0 ) const;
	
	/**
	 * @return true if the property types don't depend on the position of
	 * 	the point, else false;
	 * 	If true you can for example ignore the position parameters of:
	 * 		@see getPropertyType()
	 * 		@see getPropertyNumberForType()
	 * 		@see getDimension3IndexesForPropertyType()
	 */
	virtual bool isPropertyTypeIndependentOfPosition() const;
	
	/**
	 * This method returns the indexes in the third dimension of the
	 * property vector elements of the given type.
	 * The returned vector elements are ordered like the property vector
	 * elements. So the first property vector element has the index in
	 * dimension 3 of the returned vector element with index 0 .
	 * Example:
	 * vector< unsigned int > vecPropertyTypeIndexes =
	 * 	getDimension3IndexesForPropertyType( t ,x, y );
	 * getValue( x, y, vecPropertyTypeIndexes[ 1 ] ) ==
	 * 	getProperty( x, y, t ).getValue( 2 )
	 * @see isPropertyTypeIndependentOfPosition
	 *
	 * @param uiPropertyType the type number of the property to return the
	 * 	indexes of (e. g. cTypeProperty::COLOR_RGB )
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the property indexes
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the property indexes
	 * @return the dimension 3 indexes of the property of the given type
	 */
	virtual vector< unsigned int > getDimension3IndexesForPropertyType(
		const unsigned int uiPropertyType,
		const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0 ) const;
	
	/**
	 * This method returns the number of the uiPropertyNumber'th property
	 * type for the image position.
	 * (The properties are given by the third dimension vector on the position.)
	 * @see cTypeProperty
	 *
	 * @param uiPropertyNumber the number of the property to return the type of;
	 * 	counting starts with 1; @see getNumberOfProperties()
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the property type
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the property type
	 * @return the number of the type of the uiPropertyNumber'th property
	 * 	on the given position, or cTypeProperty::NONE if non exists
	 * 	@see cTypeProperty
	 */
	virtual unsigned int getPropertyType( const unsigned int uiPropertyNumber,
		const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0 ) const;
	
	/**
	 * This method returns the property number for the given property type
	 * for the image position.
	 * @see cTypeProperty
	 * @see getPropertyType()
	 * @see getNumberOfProperties()
	 *
	 * @param uiPropertyType the type number of the property to return the
	 * 	number of (e. g. cTypeProperty::COLOR_RGB )
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the property number
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the property number
	 * @return the number for the given property type for the image position,
	 * 	or 0 if no such property extists
	 * 	@see cTypeProperty
	 */
	virtual unsigned int getPropertyNumberForType( const unsigned int uiPropertyType,
		const unsigned int uiPositionX = 0, const unsigned int uiPositionY = 0 ) const;
	
	/**
	 * This method evalues the difference of two points properties.
	 * This difference is the sum of the difference of the property
	 * vectors elements or the sum of the distance betwean the third dimension
	 * elements for the property on the given positions.
	 *
	 * @param vPosition1 the first point for the first property vector
	 * @param vPosition2 the second point for the second property vector
	 * @param uiPropertyType the type number of the property to return the
	 * 	distances of (e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
	 * @return the sum of distances betwean the vector elements of the
	 * 	properties of the first and second point
	 */
	virtual doubleFib getDifference( const cVectorPosition & vPosition1,
		const cVectorPosition & vPosition2,
		const unsigned int uiPropertyType ) const;
	
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
	 * 	third dimension values of the property of the first and second point
	 */
	virtual doubleFib getDifference(
		const unsigned int uiPosition1X, const unsigned int uiPosition1Y,
		const unsigned int uiPosition2X, const unsigned int uiPosition2Y,
		const unsigned int uiPropertyType ) const;
	
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


//methods for points given as unsigned int pairs:
	
	/**
	 * This method evalues the difference of two points properties.
	 * This difference is the sum of the difference of the property
	 * vectors elements or the sum of the distance betwean the third dimension
	 * elements on the given positions.
	 *
	 * @param position1 the first point for the first property vector
	 * @param position2 the second point for the second property vector
	 * @return the sum of distances betwean the vector elements of the
	 * 	properties of the first and second point
	 */
	virtual doubleFib getDifference(
			const pair< unsigned int, unsigned int> & position1,
			const pair< unsigned int, unsigned int> & position2 ) const;
	
	/**
	 * This method evalues the difference of two points properties.
	 * This difference is the sum of the difference of the property
	 * vectors elements or the sum of the distance betwean the third dimension
	 * elements for the property on the given positions.
	 *
	 * @param position1 the first point for the first property vector
	 * @param position2 the second point for the second property vector
	 * @param uiPropertyType the type number of the property to return the
	 * 	distances of (e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
	 * @return the sum of distances betwean the vector elements of the
	 * 	properties of the first and second point
	 */
	virtual doubleFib getDifference(
		const pair< unsigned int, unsigned int> & position1,
		const pair< unsigned int, unsigned int> & position2,
		const unsigned int uiPropertyType ) const;
	
	/**
	 * This method returns the property of the given type for the image
	 * position.
	 * (The properties are given by the third dimension vector on the position.)
	 *
	 * @param position the position of which to return the property vector
	 * @param uiPropertyType the type number of the property to return
	 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
	 * @return the property for the given type uiPropertyType from the given
	 * 	position or the property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getProperty(
		const pair< unsigned int, unsigned int> & position,
		const unsigned int uiPropertyType = 0 ) const;
	
	/**
	 * This method returns the uiPropertyNumber'th property for the image
	 * position.
	 * (The properties are given by the third dimension vector on the position.)
	 *
	 * @param position the position of which to return the property vector
	 * @param uiPropertyNumber the number of the property to return;
	 * 	counting starts with 1; @see getNumberOfProperties()
	 * @return the uiPropertyNumber'th property from the given position or
	 * 	the property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getPropertyForNumber(
		const pair< unsigned int, unsigned int> & position,
		const unsigned int uiPropertyNumber = 0 ) const;
	
};//class cFreeImageData

};

#endif //___FIB__C_FREE_IMAGE_DATA__


