/**
 * @class cEvalueSimpleRGBA255
 * file name: cEvalueSimpleRGBA255.h
 * @author Betti Oesterholz
 * @date 18.03.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the class for evaluing Fib objects as a matrix of
 * a RGBA image.
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
 * This file contains the class for evaluing Fib objects as a matrix of
 * a RGBA image. @see pImageData
 * Just colors and transparency is evalued. The data is stored into an
 * array. The array is two dimensional and goes in the first dimension
 * from 0 to uiBorderIndexX and in the second from 0 to uiBorderIndexY. Every entry of the
 * array consists of tree values with 8 bit each (values from 0 to 255).
 * This class should keep the evaluing of a normal image (e.g. Bitmap image)
 * as simple as possible.
 */
/*
History:
18.03.2012  Oesterholz  created
10.04.2012  Oesterholz  methods of interface iImageData added
19.02.2013  Oesterholz  clone method and copy constructor added
23.02.2013  Oesterholz  destructore is now virtual (change for cEvalueSimpleRGBA255Scaled)
28.02.2013  Oesterholz  new methods from iMatrix3D added
*/

#ifndef ___FIB__C_EVALUE_SIMPLE_RGBA_255__
#define ___FIB__C_EVALUE_SIMPLE_RGBA_255__

#include "version.h"

#include "iEvaluePosition.h"
#include "iImageData.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"
#include "cMatrix3DInteger.h"


#include <list>



using std::list;

namespace fib{

class cEvalueSimpleRGBA255: public virtual iEvaluePosition, public iImageData{
public:
	
	/**
	 * The maximum value for the first (x) dimension.
	 * (The number of point rows.)
	 */
	const unsigned int uiBorderIndexX;
	
	/**
	 * The maximum value for the second (y) dimension.
	 * (The number of point lines.)
	 */
	const unsigned int uiBorderIndexY;
	
	/**
	 * The matrix with the ARGB image data.
	 * The dimension entries are:
	 * 	- first dimension (x)
	 * 	- second dimension (y)
	 * 	- value: alpha (transparency), red, green, blue
	 * 	where 0 is the minimum (e.g. no green) and 255 the maximum (e.g.
	 * 	full red), the color values are non-premultiplied;
	 * 	for the alpha value @see http://en.wikipedia.org/wiki/Alpha_compositing
	 * 	(0 = total transparent, 255 = total opaque)
	 *
	 * The pointer will point to an one dimensional array. You have to evalue
	 * the single entries by hand (with: *(pImageData + (x * uiBorderIndexY + y) * 4) )
	 */
	unsigned char * pImageData;
	
	/**
	 * The ARGB value for the background color.
	 * value: alpha (transparency), red, green, blue
	 * 	where 0 is the minimum (e.g. no green) and 255 the maximum (e.g.
	 * 	full red), the color values are non-premultiplied;
	 * 	for the alpha value @see http://en.wikipedia.org/wiki/Alpha_compositing
	 * 	(0 = total transparent, 255 = total opaque)
	 */
	unsigned char pBackgroundColor[ 4 ];
	
	/**
	 * If true a background color was set.
	 */
	bool bBackgroundColorExists;
	
	/**
	 * standard constructor
	 *
	 * @param uiInMaxX the maximum value for the first (x) dimension @see uiBorderIndexX
	 * @param uiInMaxY the maximum value for the second (y) dimension @see uiBorderIndexY
	 */
	cEvalueSimpleRGBA255( const unsigned int uiInMaxX, const unsigned int uiInMaxY );

	/**
	 * copy constructor
	 *
	 * @param evalueSimpleRGBA255 the evalueSimpleRGBA255 to copy
	 */
	cEvalueSimpleRGBA255( const cEvalueSimpleRGBA255 & evalueSimpleRGBA255 );

	/**
	 * desstructor
	 */
	virtual ~cEvalueSimpleRGBA255();

	/**
	 * @return the name of this class
	 */
	virtual string getName() const;
	
	/**
	 * This method clones this object.
	 *
	 * @return a pointer to the clone of this object
	 */
	virtual cEvalueSimpleRGBA255 * clone() const;
	
	/**
	 * The method with wich the evalued points with ther properties are
	 * inserted. Everytime a point (to evalue) is reached in the
	 * evaluation, this method is called with the position and the
	 * properties of the point and stores the data into @see pImageData
	 * This method will just evalue two dimensional points and properties
	 * for RGB and transparency.
	 * Points first dimension can have values from 0 ( including ) to the
	 * maximum value for the first (x) dimension.
	 * 	( 0 =< vPosition.getValue( 1 ) < uiBorderIndexX ) @see uiBorderIndexX
	 * Points second dimension ( vPosition.getValue( 2 ) ) can have values
	 * from 0 ( including ) to the maximum value for the second (y) dimension.
	 * 	( 0 =< vPosition.getValue( 2 ) < uiBorderIndexY ) @see uiBorderIndexY
	 * Background points (with 0 elements) are also possible.
	 * All other points will be discarded.
	 * Property (color RGB or transparency) element values should have a
	 * values from 0 to 255 (both including), else they will be rounded
	 * into the area.
	 *
	 * @see pImageData
	 * @param vPosition the position of the point, which is evalued
	 * @param vProperties a list of the properties of the point
	 */
	virtual bool evaluePosition( const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties );

	/**
	 * This method clears the data from the list with the evalued position data
	 * liEvaluedPositionData.
	 * After the function call the liEvaluedPositionData list will be empty.
	 *
	 * @see liEvaluedPositionData
	 */
	virtual void clear();
	
	/**
	 * Adds the background color pBackgroundColor to the image data matrix
	 * pImageData, if existing.
	 *
	 * @see pBackgroundColor
	 * @see pImageData
	 * @return true if the background color was added the image data matrix,
	 * 	else false
	 */
	bool colorWithBackgroundColor();
	
	
//methods of interface iImageData:
	
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
	 * With this method the properties for a point are set.
	 *
	 * @param vPosition the position of the point to set
	 * @param vProperties a list of the properties of the point
	 * @return true if the properties for the point cold be set, else false
	 */
	virtual bool setPoint(  const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties );
	
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
	 * @param lValue the integer value to set
	 * @param uiPositionX the index on the first (x) dimension where to set
	 * 	the value lValue
	 * @param uiPositionY the index on the second (y) dimension where to set
	 * 	the value lValue
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
	 * With this method the integer value for a matrix element is returned.
	 *
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the value
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the value
	 * @param uiChanel the index for the property chanel;
	 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
	 * @return the integer value of the given position in the matrix
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
	 * @param uiChanel the index for the property chanel;
	 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
	 * @return the minimum value of the given position in the matrix
	 */
	virtual doubleFib getMinValue( const unsigned int uiPositionX = 0,
		const unsigned int uiPositionY = 0, const unsigned int uiChanel = 0 ) const;
	
	/**
	 * With this method the minimum integer value for a matrix element is returned.
	 *
	 * @return the minimum integer value for entries in the matrix
	 */
	virtual longFib getMinValueUInt() const;
	
	/**
	 * With this method the maximum value for a matrix element is returned.
	 *
	 * @param uiPositionX the index on the first (x) dimension of which to
	 * 	return the maximum value
	 * @param uiPositionY the index on the second (y) dimension of which to
	 * 	return the maximum value
	 * @param uiChanel the index for the property chanel;
	 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
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
	 * @return the maximum integer value for entries in the matrix
	 */
	virtual longFib getMaxValueUInt() const;
	
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
	 * @return true if the property types don't depend on the position of the
	 * 	point, else false;
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
	 * 	third dimension values of the property of the first and second point
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
	 * 	third dimension of the property of the first and second point
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
	 * 	 (e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
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
	 * @return the uiPropertyNumber'th property from the given position or the
	 * 	property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getPropertyForNumber(
		const pair< unsigned int, unsigned int> & position,
		const unsigned int uiPropertyNumber = 0 ) const;
	
protected:
	
	/**
	 * This method returns a empty matrix for storing the derivate of this
	 * matrix to.
	 * With this method child classes of this class can use the same
	 * evalueDerivate() method and overwrite this method for the respectivly
	 * cMatrix3DInteger child they need for their derivation.
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
	 * @return a pointer to the cMatrix3DInteger (or child of it) matrix with
	 * 	the given size, to store the derivate of this matrix to
	 * 	Beware: You have to care that the returnd object is deleted.
	 */
	virtual cMatrix3DInteger * getEmptyMatrixForDerivate(
		const unsigned int uiMaxIndexX, const unsigned int uiMaxIndexY,
		const unsigned int uiMaxIndexZ ) const;
	
	
};//class cEvalueSimpleRGBA255

};

#endif


