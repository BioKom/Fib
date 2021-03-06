/**
 * @file cImageAreaSameColor
 * file name: cImageAreaSameColor.h
 * @author Betti Oesterholz
 * @date 23.10.2012
 * @mail Oesterholz@Fib-development.org
 *
 * System: C++
 *
 * This header specifies a class to store the data of a same colored area
 * in an image.
 *
 * Copyright (C) @c GPL3 2012 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This header specifies a class to store the data of a same colored area
 * in an image.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * If you have a area with one color, you can use this class to represent it.
 */
/*
History:
23.10.2012  Oesterholz  created
*/


#ifndef ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__C_IMAGE_AREA_SAME_COLOR_H__
#define ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__C_IMAGE_AREA_SAME_COLOR_H__

#include "version.h"

#include "cImageStructure.h"

#include "cVectorProperty.h"


namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{

namespace nStructureData{


class cImageAreaSameColor: public cImageStructure{
protected:
	

	/**
	 * The color of the area.
	 * @see getColorOfArea()
	 * @see setColorOfArea()
	 */
	cVectorProperty vecColor;
	
public:
	
	/**
	 * standard constructor
	 *
	 * @param vecInColor the color the area has
	 */
	cImageAreaSameColor( const cVectorProperty & vecInColor );
	
	/**
	 * copy constructor
	 *
	 * @param structureToCopy the image structure to copy
	 */
	cImageAreaSameColor( const cImageAreaSameColor & structureToCopy );
	
	/**
	 * The constructor for restoring a image structure from an TinyXml element.
	 *
	 * @param pXmlNode a pointer to the TinyXml node the image structure is stored in
	 * @param outStatus a reference to an integer value where the error value
	 * 	can be stored to.
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 */
	cImageAreaSameColor( const TiXmlElement * pXmlElement, intFib & outStatus );
	
	/**
	 * destructor
	 */
	virtual ~cImageAreaSameColor();
	
	
	/**
	 * @return the name of the image structure (class name without the leading 'c')
	 */
	virtual string getName() const;
	
	/**
	 * @see vecColor
	 * @see setColorOfArea()
	 * @return the color the area has
	 */
	cVectorProperty getColorOfArea() const;
	
	/**
	 * @see vecColor
	 * @see setColorOfArea()
	 * @return the color the area has
	 */
	const cVectorProperty & getColorOfAreaConst() const;
	
	/**
	 * This method sets the color the area has to the given color.
	 *
	 * @see vecColor
	 * @see getColorOfArea()
	 * @param vecInColor the color the area should have
	 */
	void setColorOfArea( const cVectorProperty & vecInColor );
	
	
	/**
	 * This method clones this object.
	 *
	 * @return a clone of this object
	 */
	virtual cImageAreaSameColor *clone() const;
	
	
	/**
	 * This method returns the number of properties for the image structure
	 * point.
	 *
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( getStructurePoints() ) will be ignored (return value 0), else
	 * 	it works as if the given point was included in this image structure
	 * @param vecPoint the point for which to return the number of
	 * 	properties
	 * @return the number of property vectors for the given position
	 */
	virtual unsigned int getNumberOfProperties( const bool bEvenIfOutside = false,
		const cVectorPosition vecPoint = cVectorPosition( 2 ) ) const;
	
	/**
	 * This method returns the number of properties for the image structure
	 * point.
	 *
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( getStructurePoints() ) will be ignored (return value 0), else
	 * 	it works as if the given point was included in this image structure
	 * @param point the point for which to return the number of
	 * 	properties
	 * @return the number of property vectors for the given position
	 */
	virtual unsigned int getNumberOfProperties( const bool bEvenIfOutside = false,
		const pair< unsigned int, unsigned int> point =
			pair< unsigned int, unsigned int>(0, 0) ) const;
	
	/**
	 * This method returns the number of the uiPropertyNumber'th property
	 * type for the image structure point.
	 * @see cTypeProperty
	 * @see getPropertyNumberForType()
	 *
	 * @param uiPropertyNumber the number of the property to return the type of;
	 * 	counting starts with 1; @see getNumberOfProperties()
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( getStructurePoints() ) will be ignored (return value 0), else
	 * 	it works as if the given point was included in this image structure
	 * @param vecPoint the point for which to return the number of
	 * 	the type of the property
	 * @return the number of the type of the uiPropertyNumber'th property
	 * 	on the given position, or 0 (cTypeProperty::NONE) if non exists
	 * 	@see cTypeProperty
	 */
	virtual unsigned int getPropertyType( const unsigned int uiPropertyNumber,
		const bool bEvenIfOutside = false,
		const cVectorPosition vecPoint = cVectorPosition( 2 ) ) const;
	
	/**
	 * This method returns the number of the uiPropertyNumber'th property
	 * type for the image structure point.
	 * @see cTypeProperty
	 * @see getPropertyNumberForType()
	 *
	 * @param uiPropertyNumber the number of the property to return the type of;
	 * 	counting starts with 1; @see getNumberOfProperties()
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( getStructurePoints() ) will be ignored (return value 0), else
	 * 	it works as if the given point was included in this image structure
	 * @param point the point for which to return the number of
	 * 	the type of the property
	 * @return the number of the type of the uiPropertyNumber'th property
	 * 	on the given position, or 0 (cTypeProperty::NONE) if non exists
	 * 	@see cTypeProperty
	 */
	virtual unsigned int getPropertyType( const unsigned int uiPropertyNumber,
		const bool bEvenIfOutside = false,
		const pair< unsigned int, unsigned int> point =
			pair< unsigned int, unsigned int>(0, 0) ) const;
	
	/**
	 * This method returns the property number for the given property type
	 * for the image position.
	 * @see cTypeProperty
	 * @see getPropertyType()
	 * @see getNumberOfProperties()
	 *
	 * @param uiPropertyType the type number of the property to return the
	 * 	number of (e. g. cTypeProperty::COLOR_RGB )
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( getStructurePoints() ) will be ignored (return value 0), else
	 * 	it works as if the given point was included in this image structure
	 * @param vecPoint the point for which to return the number of
	 * 	the property of the given type
	 * @return the number for the given property type for the image position,
	 * 	or 0 if no such property extists
	 * 	@see cTypeProperty
	 */
	virtual unsigned int getPropertyNumberForType( const unsigned int uiPropertyType,
		const bool bEvenIfOutside = false,
		const cVectorPosition vecPoint = cVectorPosition( 2 ) ) const;
	
	/**
	 * This method returns the property number for the given property type
	 * for the image position.
	 * @see cTypeProperty
	 * @see getPropertyType()
	 * @see getNumberOfProperties()
	 *
	 * @param uiPropertyType the type number of the property to return the
	 * 	number of (e. g. cTypeProperty::COLOR_RGB )
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( getStructurePoints() ) will be ignored (return value 0), else
	 * 	it works as if the given point was included in this image structure
	 * @param point the point for which to return the number of
	 * 	the property of the given type
	 * @return the number for the given property type for the image position,
	 * 	or 0 if no such property extists
	 * 	@see cTypeProperty
	 */
	virtual unsigned int getPropertyNumberForType( const unsigned int uiPropertyType,
		const bool bEvenIfOutside = false,
		const pair< unsigned int, unsigned int> point =
			pair< unsigned int, unsigned int>(0, 0) ) const;
	
	/**
	 * With this method the properties for given point are returned.
	 * Antialising will be ignored. @see bIsAntialised
	 *
	 * @param vecPoint the point, for which the properties should be returned
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( getStructurePoints() ) will be ignored (return empty list), else
	 * 	it works as if the given point was included in this image structure
	 * @return a list of the properties of the point
	 */
	virtual list<cVectorProperty> getPointProperties(
		const cVectorPosition & vecPoint,
		const bool bEvenIfOutside = false ) const;
	
	/**
	 * With this method the properties for given point are returned.
	 * Antialising will be ignored. @see bIsAntialised
	 *
	 * @param point the point, for which the properties should be
	 * 	returned
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( getStructurePoints() ) will be ignored (return empty list), else
	 * 	it works as if the given point was included in this image structure
	 * @return a list of the properties of the point
	 */
	virtual list<cVectorProperty> getPointProperties(
		const pair< unsigned int, unsigned int> & point,
		const bool bEvenIfOutside = false ) const;
	
	/**
	 * This method returns the property of the given type for the given image
	 * structure point.
	 * Antialising will be ignored. @see bIsAntialised
	 *
	 * @param vecPoint the point of which to return the property vector
	 * @param uiPropertyType the type number of the property to return
	 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( getStructurePoints() ) will be ignored (return cTypeProperty::NONE),
	 * 	 else it works as if the given point was included in this image structure
	 * @return the property for the given type uiPropertyType for the given
	 * 	point or the property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getProperty( const cVectorPosition & vecPoint,
		const unsigned int uiPropertyType = 0, const bool bEvenIfOutside = false ) const;
	
	/**
	 * This method returns the property of the given type for the given image
	 * structure point.
	 * Antialising will be ignored. @see bIsAntialised
	 *
	 * @param point the point of which to return the property vector
	 * @param uiPropertyType the type number of the property to return
	 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( getStructurePoints() ) will be ignored (return cTypeProperty::NONE),
	 * 	 else it works as if the given point was included in this image structure
	 * @return the property for the given type uiPropertyType for the given
	 * 	point or the property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getProperty(
		const pair< unsigned int, unsigned int> & point,
		const unsigned int uiPropertyType = 0, const bool bEvenIfOutside = false ) const;

	/**
	 * This method returns the uiPropertyNumber'th property for the given image
	 * structure point.
	 * Antialising will be ignored. @see bIsAntialised
	 *
	 * @param vecPoint the point of which to return the property vector
	 * @param uiPropertyNumber the number of the property to return;
	 * 	counting starts with 1; @see getNumberOfProperties()
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( getStructurePoints() ) will be ignored (return cTypeProperty::NONE),
	 * 	 else it works as if the given point was included in this image structure
	 * @return the uiPropertyNumber'th property from the given position or the
	 * 	property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getPropertyForNumber( const cVectorPosition & vecPoint,
		const unsigned int uiPropertyNumber = 0, const bool bEvenIfOutside = false ) const;
	
	/**
	 * This method returns the uiPropertyNumber'th property for the given image
	 * structure point.
	 * Antialising will be ignored. @see bIsAntialised
	 *
	 * @param point the point of which to return the property vector
	 * @param uiPropertyNumber the number of the property to return;
	 * 	counting starts with 1; @see getNumberOfProperties()
	 * @param bEvenIfOutside if false points outside this image structure
	 * 	( getStructurePoints() ) will be ignored (return cTypeProperty::NONE),
	 * 	 else it works as if the given point was included in this image structure
	 * @return the uiPropertyNumber'th property from the given position or the
	 * 	property of type cTypeProperty::NONE if non exists
	 */
	virtual cVectorProperty getPropertyForNumber(
		const pair< unsigned int, unsigned int> & point,
		const unsigned int uiPropertyNumber = 0, const bool bEvenIfOutside = false ) const;
	
	/**
	 * This method checks if the given image structure is equal to this
	 * image structure.
	 *
	 * @param imageStructure the image structure, which should be equal to
	 * 	this image structure
	 * @return true if the given image structure is equal to this image
	 * 	structure, else false
	 */
	virtual bool equal( const cImageStructure &imageStructure ) const;

	/**
	 * This method stores this image structure in the XML format into the
	 * given stream.
	 *
	 * @param ostream the stream where image structure should be stored to
	 * @return true if this image structure was stored, else false
	 */
	virtual bool storeXml( ostream & ostream ) const;
	
	/**
	 * This method restores a image structure in the XML format from a
	 * TinyXml element.
	 *
	 * @param pXmlElement a pointer to the TinyXml node wher the image
	 * 	structure is stored in
	 * @return an integer value with the error value
	 * 	possible error values are:
	 * 		- 0  loading successful
	 * 		- -1 loading error, invalid pXmlElement
	 * 		- -2 loading error, invalid data in pXmlElement
	 * 		- 1 loading warning, invalid data in pXmlElement, error could be corrected
	 * 		- 2 loading warning, invalid data in pXmlElement, maybe the loaded
	 * 			object is wrong
	 */
	virtual intFib restoreXml( const TiXmlElement * pXmlElement );
	
	
	//methods of iConvertImageStructureToFib
	
	/**
	 * This method is for converting the data of this object to a Fib object.
	 * The area is converted with the iConvertAreaToExtObjects class,
	 * which is set by the cUseConvertAreaToExtObjectsStrategy class methods.
	 * For antialising it uses the cConvertFibDatabaseObject::convertToAntialised()
	 * method.
	 * @see iConvertAreaToExtObjects
	 * @see cConvertFibDatabaseObject::convertToAntialised()
	 * @see iConvertAreaToExtObjects
	 * @see cUseConvertAreaToExtObjectsStrategy
	 *
	 * @param pImageSearchData a pointer to the image search data of found
	 * 	image parts, which will overwrite area parts
	 * 	(the area can be bigger, because some parts of it won't be seen)
	 * @param maxValue the maximum possible value in all evalued parameters
	 * 	of the evalued Fib elements will allways have lower absolute values
	 * 	or the values (parameters) of the Fib elements are coordinate values
	 * 	of points;
	 * 	if 0 (standard value) is given, the maximum possible value will
	 * 	be evalued from the given data (absolute maximum in given data * 256)
	 * @param maxErrorPerValue the maximal error for the border points to
	 * 	find on one border point; every point in the area of the generated
	 * 	Fib object will have a distance lower or equal maxErrorPerValue
	 * 	to a point in this structure or an overlappted point of pImageSearchData
	 * @return a Fib object which represents the data of this object
	 * 	Beware: You have to delete the returned Fib object after usage.
	 * 		Also the given root element will contain no domains, you have to
	 * 		create them if needed (eg. with cRoot::generateNeededDomains() ).
	 */
	virtual cRoot * convertToFib( const cImageSearchData * pImageSearchData,
		const double maxValue = 65536.0, const unsigned long ulMaxErrorPerPoint = 0.0 ) const;

	
};//class cImageAreaSameColor


};//end namespace nStructureData
};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__C_IMAGE_AREA_SAME_COLOR_H__


