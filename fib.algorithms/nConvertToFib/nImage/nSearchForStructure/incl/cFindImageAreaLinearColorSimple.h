
//TODO check

/**
 * @file cFindImageAreaLinearColorSimple
 * file name: cFindImageAreaLinearColorSimple.h
 * @author Betti Oesterholz
 * @date 28.03.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for searching for a structure with
 * linear color gradient in an image.
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
 * This header specifies a class for searching for a structure with
 * linear color gradient color in an image.
 * For this a method findImageStructure() is defined.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * For this you can use this class.
 * @see findImageStructure()
 *
 * @pattern Strategy
 * @see cImageAreaLinearColor
 * @see cConvertImageToFib
 * @see iFindImageStructure
 * @see iConvertImageStructureToFib
 */
/*
History:
28.03.2013  Oesterholz  created
*/


#ifndef ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_SEARCH_FOR_STRUCTURE__C_FIND_IMAGE_AREA_LINEAR_COLOR_SIMPLE_H__
#define ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_SEARCH_FOR_STRUCTURE__C_FIND_IMAGE_AREA_LINEAR_COLOR_SIMPLE_H__

#include "version.h"

#include "iFindImageStructure.h"

#include "cImageAreaLinearColor.h"



namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{

namespace nSearchForStructure{


class cFindImageAreaLinearColorSimple: public iFindImageStructure{
protected:
	
	/**
	 * The type number of the property to use. (e. g. cTypeProperty::COLOR_RGB )
	 * @see fib::cTypeProperty
	 * @see iImageData::getNumberOfProperties()
	 * @see iImageData::getProperty()
	 * @see maxErrorPerPropertyElement
	 */
	unsigned int propertyTypeNumber;
	
	/**
	 * The maximal error for a point of the area.
	 * The difference of the properties (of type propertyTypeNumber) for the
	 * point. @see iImageData::getDifference()
	 * @see propertyTypeNumber
	 */
	const double maxErrorPerPoint;
	
	/**
	 * If true the found image structure can be antialised, else the image
	 * structure should not be antialised.
	 * @see cImageStructure::isAntialised()
	 */
	const bool bCanBeAntialised;
	
	/**
	 * The maximal error for a element of a property of a point of the area.
	 * The difference of the properties (of type propertyTypeNumber) for the
	 * point. @see iImageData::getDifference()
	 * @see propertyTypeNumber
	 */
	const double maxErrorPerPropertyElement;
	
	/**
	 * A realy smaal value, error values lower will be taken as zero.
	 * Just for internal use.
	 */
	mutable double zeroErrorValue;
	
	/**
	 * The maximal number of points to use to evalue the parameters.
	 */
	const static unsigned int uiPointsToUseToEvalueParameters = 256;
	
public:
	
	/**
	 * Constructor
	 *
	 * @param uiPropertyType the type number of the property to use;
	 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
	 * @param dMaxErrorPerPoint the maximal error for a point of the area
	 * 	@see maxErrorPerPoint
	 * @param bInCanBeAntialised if true the found image structure can be
	 * 	antialised, else the image structure should not antialised
	 * 	@see bCanBeAntialised
	 * @param dMaxErrorPerPropertyElement the maximal error for a property
	 * 	element value for a point of the area;
	 * 	This value is just for evaluing the base and slope parameters for the
	 * 	image structure (for linear properties) to create.
	 * 	@see maxErrorPerPropertyElement
	 */
	cFindImageAreaLinearColorSimple( unsigned int uiPropertyType,
		const double dMaxErrorPerPoint = 0,
		const bool bInCanBeAntialised = true,
		const double dMaxErrorPerPropertyElement = 0 );
	
	
	/**
	 * This method is for searching in an image for an area with the linear color.
	 * If the returned structure is antialised, the border points of the
	 * structure, will not be in the structure points of the structure.
	 * @see cImageStructure::bIsAntialised
	 * @see cImageStructure::structureBorderPoints
	 * @see cImageStructure::structurePoints
	 * Also the neighbour points of the generated structure will just contain
	 * points not overlapped in the search structure.
	 * @see cImageStructure::structureNeighbourPoints
	 * @see cImageSearchData::pImageDataOverlapped
	 * @see cImageSearchData::getNotFoundNotOverlappedNeighbours()
	 * In the search structure (pConvertImageToFib->getImageSearchData())
	 * no points should be set as found befor the method start, this method
	 * will set all structure points as found.
	 *
	 * @param paStartPoint the point where to start the search;
	 * 	it will be included in the generated image structure
	 * @param pConvertImageToFib a pointer to the object for converting an
	 * 	image to a Fib object (it should implement methods to get the
	 * 	image search data);
	 * 	The image data (getImageData()) of the search data
	 * 	(pConvertImageToFib->getImageSearchData()) should have a
	 * 	propertyTypeNumber'th property for each point.
	 * @return the found image structure, or the null pointer NULL if non
	 * 	could be found
	 * 	Beware: You have to delete the returned image structure after usage.
	 */
	virtual cImageAreaLinearColor * findImageStructure(
		const pair< long, long> paStartPoint,
		cConvertImageToFib * pConvertImageToFib ) const;
	
	/**
	 * @return the name of this class
	 */
	virtual string getName() const;
	
protected:
	
	/**
	 * This method takes as start point a neighbour of the start point paStartPoint
	 * which has (if possible) no overlapped neighbours (so the start
	 * point can be antialised, without make the evaluation of the
	 * parameters (slope base) difficult).
	 *
	 * @param paStartPoint the original start point
	 * @param dMaxErrorPerValue the maximal error for a value of the matrix
	 * @param pConvertImageToFib a pointer to the object for converting an
	 * 	image to a Fib object (it should implement methods to get the
	 * 	image search data);
	 * 	The image data (getImageData()) of the search data
	 * 	(pConvertImageToFib->getImageSearchData()) should have a
	 * 	propertyTypeNumber'th property for each point.
	 * @return a new start point which is neighbour of the start point
	 * 	paStartPoint and  which has (if possible) no overlapped neighbours
	 */
	pair< unsigned int, unsigned int> findGoodAreaStartPoint(
		const pair< unsigned int, unsigned int> & paStartPoint,
		const double dMaxErrorPerValue,
		cConvertImageToFib * pConvertImageToFib ) const;
	
	/**
	 * This method evalues a good slope value in the first (x) dimension /
	 * direction, for the area which includs the start point paStartPoint,
	 * is not overlapped and has in dimension 3 the given index uiIndexDim3.
	 *
	 * @param uiIndexDim3 the index in dimension 3 for the values for which the
	 * 	slope should be evalued
	 * @param paStartPoint the start point for the area
	 * @param dMaxErrorPerValue the maximal error for a value of the matrix
	 * @param pConvertImageToFib a pointer to the object for converting an
	 * 	image to a Fib object (it should implement methods to get the
	 * 	image search data);
	 * 	The image data (getImageData()) of the search data
	 * 	(pConvertImageToFib->getImageSearchData()) should have a
	 * 	propertyTypeNumber'th property for each point.
	 * @return a good slope parameter
	 */
	doubleFib evalueSlopeXForIndex( const unsigned int uiIndexDim3,
		const pair< unsigned int, unsigned int> & paStartPoint,
		const double dMaxErrorPerValue,
		cConvertImageToFib * pConvertImageToFib ) const;
	
	/**
	 * This method evalues a good slope value in the second (y) dimension /
	 * direction, for the area which includs the start point paStartPoint,
	 * is not overlapped and has in dimension 3 the given index uiIndexDim3.
	 *
	 * @param uiIndexDim3 the index in dimension 3 for the values for which the
	 * 	slope should be evalued
	 * @param paStartPoint the start point for the area
	 * @param dMaxErrorPerValue the maximal error for a value of the matrix
	 * @param pConvertImageToFib a pointer to the object for converting an
	 * 	image to a Fib object (it should implement methods to get the
	 * 	image search data);
	 * 	The image data (getImageData()) of the search data
	 * 	(pConvertImageToFib->getImageSearchData()) should have a
	 * 	propertyTypeNumber'th property for each point.
	 * @return a good slope parameter
	 */
	doubleFib evalueSlopeYForIndex( const unsigned int uiIndexDim3,
		const pair< unsigned int, unsigned int> & paStartPoint,
		const double dMaxErrorPerValue,
		cConvertImageToFib * pConvertImageToFib ) const;
	
	/**
	 * This method evalues a good slope value in the given first derivation
	 * matrix, for the area which includs the start point paStartPoint,
	 * is not overlapped and has in dimension 3 the given index uiIndexDim3.
	 *
	 * @param uiIndexDim3 the index in dimension 3 for the values for which the
	 * 	slope should be evalued
	 * @param paStartPoint the start point for the area
	 * @param dMaxErrorPerValue the maximal error for a value of the matrix
	 * @param pDerivateMatrix the derivation matrix in which the slope
	 * 	parameter should be evalued
	 * @param pImageSearchData the image search data with the overlapped points
	 * 	marked; all points in the slope area will be marked as found
	 * @return a good slope parameter
	 */
	doubleFib searchForGoodSlope( const unsigned int uiIndexDim3,
		const pair< unsigned int, unsigned int> & paStartPoint,
		const double dMaxErrorPerValue,
		const iMatrix3D * pDerivateMatrix,
		cImageSearchData * pImageSearchData ) const;
	
	/**
	 * This method evalues a good base value for the area which includs the
	 * start point paStartPoint, is not overlapped and has in dimension 3 the
	 * given index uiIndexDim3.
	 *
	 * @param uiIndexDim3 the index in dimension 3 for the values for which the
	 * 	base should be evalued
	 * @param paStartPoint the start point for the area
	 * @param dSlopeX the slope in the first (x) direction
	 * @param dSlopeY the slope in the second (y) direction
	 * @param dMaxErrorPerValue the maximal error for a value of the matrix
	 * @param pConvertImageToFib a pointer to the object for converting an
	 * 	image to a Fib object (it should implement methods to get the
	 * 	image search data);
	 * 	The image data (getImageData()) of the search data
	 * 	(pConvertImageToFib->getImageSearchData()) should have a
	 * 	propertyTypeNumber'th property for each point.
	 * @return a good slope parameter
	 */
	doubleFib evalueBaseForIndex( const unsigned int uiIndexDim3,
		const pair< unsigned int, unsigned int> & paStartPoint,
		const doubleFib dSlopeX, const doubleFib dSlopeY,
		const double dMaxErrorPerValue,
		cConvertImageToFib * pConvertImageToFib ) const;
	
	/**
	 * This method searches for all points which can be included into the given
	 * image structure pInOutImageStructure and includes them into it.
	 *
	 * @param pInOutImageStructure the image structure for which the points
	 * 	should be found and in which the points will be included;
	 * 	It should already contain at last one point, at which to start the
	 * 	search (if it contains more than one point they should be in one
	 * 	connected (via neighbours) area).
	 * 	The structure and structure neighbour points will be added, you have
	 * 	to add the structure border points to it.
	 * @param dMaxErrorPerPoint the maximal error for a property of a point
	 * @param pConvertImageToFib a pointer to the object for converting an
	 * 	image to a Fib object (it should implement methods to get the
	 * 	image search data);
	 * 	The image data (getImageData()) of the search data
	 * 	(pConvertImageToFib->getImageSearchData()) should have a
	 * 	propertyTypeNumber'th property for each point.
	 * @return the pointer to the image structure object, wher the points wher
	 * 	added ( pInOutImageStructure ), or NULL if no points could be added
	 */
	cImageAreaLinearColor * findPointsForImageStructure(
		cImageAreaLinearColor * pInOutImageStructure,
		doubleFib dMaxErrorPerPoint,
		cConvertImageToFib * pConvertImageToFib ) const;
	
	
	/**
	 * This function checks if the border neighbours of the given structure
	 * are antialised.
	 * This is a help method for: @see findImageStructure()
	 *
	 * @param pStructureToCheck the structure which neighbours to check
	 * @param pImageSearchData the image search data for the structure,
	 * 	all points in the structure pStructureToCheck and there neighbour
	 * 	points have to be marked as found in pImageSearchData
	 * @return true if the structure border neighbours are antialised else false
	 */
	bool checkIfBorderIsAntialised( cImageAreaLinearColor * pStructureToCheck,
		const cImageSearchData * pImageSearchData ) const;
	
	
};//interface cFindImageAreaLinearColorSimple


};//end namespace nSearchForStructure
};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_SEARCH_FOR_STRUCTURE__C_FIND_IMAGE_AREA_LINEAR_COLOR_SIMPLE_H__
