/**
 * @file cConvertImageToFibForOnePropertySimple
 * file name: cConvertImageToFibForOnePropertySimple.h
 * @author Betti Oesterholz
 * @date 17.02.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for converting an image to a Fib object.
 *
 * Copyright (C) @c GPL3 2013 Betti Oesterholz
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
 *
 * This header specifies a class for converting an image to a Fib object.
 * For this a method convertToFib() is implemented (in a simple way).
 * The convered Fib object is just for one property.
 * If antialising is allowed the transparency property will be used.
 *
 * @pattern Strategy
 * @see iFindImageStructure
 * @see cImageStructure
 */
/*
History:
17.02.2013  Oesterholz  created
*/


#ifndef ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__C_CONVERT_IMAGE_TO_FIB_FOR_ONE_PROPERTY_SIMPLE_H__
#define ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__C_CONVERT_IMAGE_TO_FIB_FOR_ONE_PROPERTY_SIMPLE_H__


/**
 * With this feature the search border will be evalued with
 * @see cImageSearchDataForOverlappedBorder
 *
 * created: 29.04.2013  Betti Oesterholz
 * status:  running and tested (04.2013)
 * (deprecated: not FEATURE_SEARCH_BORDER_HANDLING)
 *//*
History:
*/
#define FEATURE_SEARCH_BORDER_HANDLING



#include "version.h"

#include "iImageData.h"
#include "cConvertImageToFib.h"

#include "cImageStructure.h"
#include "iImageStructureSearchOperator.h"
#include "cImageSearchDataForOverlappedBorder.h"



namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{


class cConvertImageToFibForOnePropertySimple: public cConvertImageToFib{
protected:
	
	/**
	 * The type number of the property to use. (e. g. cTypeProperty::COLOR_RGB )
	 * @see iImageData::getNumberOfProperties()
	 * @see iImageData::getProperty()
	 */
	unsigned int propertyTypeNumber;

	/**
	 * The maximal error for a point of the area.
	 */
	const double maxErrorPerPoint;
	
	/**
	 * The maximal error for the border points to find on one border point.
	 * Every point in the part areas of the generated Fib objects will have
	 * a distance lower or equal dMaxErrorPerBorderPoint to a point in the
	 * correct area border.
	 */
	const double maxErrorPerBorderPoint;
	
	/**
	 * If true the found image structure can be antialised, else the image
	 * structure should not be antialised.
	 */
	const bool bCanBeAntialised;
	
	/**
	 * A list with the operators for the created image structures.
	 * On every created image structure, which will be converted to a
	 * Fib object, every operator (from begin to end of the list) will be
	 * called.
	 */
	list< nStructureData::nOperators::iImageStructureSearchOperator * >
		liOperatoresForImageStructure;

#ifdef FEATURE_SEARCH_BORDER_HANDLING
	/**
	 * The actual search data of the to convert image.
	 */
	cImageSearchDataForOverlappedBorder * pImageSearchDataForOverlappedBorder;
#endif //FEATURE_SEARCH_BORDER_HANDLING
	
public:
	
	/**
	 * constructor
	 *
	 * @param imageData the image data to convert;
	 * 	The given image data object will be copied. @see pImageData
	 * @param uiPropertyType the type number of the property to use;
	 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
	 * @param dMaxErrorPerPoint the maximal error for a point of the area
	 * @param dMaxErrorPerBorderPoint the maximal error for the border points to
	 * 	find on one border point; every point in the part areas of the generated
	 * 	Fib objects will have a distance lower or equal dMaxErrorPerBorderPoint
	 * 	to a point in the correct area border
	 * @param bInCanBeAntialised if true the found Fib object can use
	 * 	antialising (transparency for border points of areas), else it can't
	 * @param liInOperatoresForImageStructure A list with the operators for
	 * 	the created image structures.
	 * 	On every created image structure, which will be converted to a
	 * 	Fib object, every operator (from begin to end of the list) will be
	 * 	called. @see liOperatoresForImageStructure
	 */
	cConvertImageToFibForOnePropertySimple( const iImageData & imageData,
		const unsigned int uiPropertyType, const double dMaxErrorPerPoint = 0.0,
		const double dMaxErrorPerBorderPoint = 0.0,
		const bool bInCanBeAntialised = true,
		const list< nStructureData::nOperators::iImageStructureSearchOperator * >
			liInOperatoresForImageStructure =
				list< nStructureData::nOperators::iImageStructureSearchOperator * >() );
	
	/**
	 * constructor
	 *
	 * @param pInImageData a pointer to the image data to convert;
	 * 	Beware this object won't be copied, so keep it alive as long as
	 * 	this object exists. @see pImageData
	 * @param uiPropertyType the type number of the property to use;
	 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
	 * @param dMaxErrorPerPoint the maximal error for a point of the area
	 * @param dMaxErrorPerBorderPoint the maximal error for the border points to
	 * 	find on one border point; every point in the part areas of the generated
	 * 	Fib objects will have a distance lower or equal dMaxErrorPerBorderPoint
	 * 	to a point in the correct area border
	 * @param bInCanBeAntialised if true the found Fib object can use
	 * 	antialising (transparency for border points of areas), else it can't
	 * @param liInOperatoresForImageStructure A list with the operators for
	 * 	the created image structures.
	 * 	On every created image structure, which will be converted to a
	 * 	Fib object, every operator (from begin to end of the list) will be
	 * 	called. @see liOperatoresForImageStructure
	 */
	cConvertImageToFibForOnePropertySimple( const iImageData * pInImageData,
		const unsigned int uiPropertyType, const double dMaxErrorPerPoint = 0.0,
		const double dMaxErrorPerBorderPoint = 0.0,
		const bool bInCanBeAntialised = true,
		const list< nStructureData::nOperators::iImageStructureSearchOperator * >
			liOperatoresForImageStructure =
				list< nStructureData::nOperators::iImageStructureSearchOperator * >()  );
	
	/**
	 * destructor
	 */
	virtual ~cConvertImageToFibForOnePropertySimple();
	
	
	/**
	 * This method is for converting the image data to a Fib object.
	 *
	 * @pattern Factory Method
	 * @return a Fib object which represents the the image data of this object
	 * 	or NULL if non could be generated
	 * 	Beware: You have to delete the returned Fib object after usage.
	 */
	virtual cRoot * convertToFib();
	
	
	/**
	 * @return the name of this class
	 */
	virtual string getName() const;
	
	/**
	 * @return the type number of the property to use (e. g. cTypeProperty::COLOR_RGB )
	 * @see propertyTypeNumber
	 * @see iImageData::getNumberOfProperties()
	 * @see iImageData::getProperty()
	 */
	unsigned int getPropertyTypeNumber() const;
	
	/**
	 * @return the maximal error for a point of the area
	 * @see maxErrorPerPoint
	 */
	double getMaxErrorPerPoint() const;
	
	/**
	 * @return the maximal error for the border points to find on one
	 * 	border point; every point in the part areas of the generated
	 * 	Fib objects will have a distance lower or equal maxErrorPerBorderPoint
	 * 	to a point in the correct area border
	 * @see maxErrorPerBorderPoint
	 */
	double getMaxErrorPerBorderPoint() const;
	
	/**
	 * @return true if the found image structure can be antialised, else the
	 * 	image structure should not be antialised
	 * @see bCanBeAntialised
	 */
	const bool isCanBeAntialised() const;
	
	/**
	 * @return A list with the operators for the created image structures.
	 * 	On every created image structure, which will be converted to a
	 * 	Fib object, every operator (from begin to end of the list) will be
	 * 	called. @see liOperatoresForImageStructure
	 */
	const list< nStructureData::nOperators::iImageStructureSearchOperator * > &
		getOperatoresForImageStructure() const;
	
	
protected:
	/**
	 * This method generates for the given point a Fib object.
	 *
	 * @param paPoint the point for which to generate the Fib object
	 * @return the Fib object for the given point or NULL if non could be
	 * 	generated; The returned Fib object will consist of a point with the
	 * 	given position and a property element for the property in the image
	 * 	data for the point
	 */
	cFibElement * generateObjectForPoint(
		const pair< unsigned int, unsigned int > & paPoint ) const;
	
	/**
	 * This function checks if the width of the given image structure is lower
	 * the given value uiWidth in both directions.
	 * (The width is the distance of the position elements in the two dimensions.)
	 *
	 * @param pImageStructureToUse the image structure of which to check the width
	 * @param uiWidth the maximal width the image structure should have
	 * @return true if given the image structure has a width lower uiWidth, else false
	 */
	bool checkWidthLower( const nStructureData::cImageStructure * pImageStructureToUse,
		const unsigned int uiWidth ) const;
	
};//interface cConvertImageToFibForOnePropertySimple


};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__C_CONVERT_IMAGE_TO_FIB_FOR_ONE_PROPERTY_SIMPLE_H__
