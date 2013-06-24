/**
 * @file cFindImageAreaSameColorSimple
 * file name: cFindImageAreaSameColorSimple.h
 * @author Betti Oesterholz
 * @date 18.02.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for searching for a structure with
 * constant color in an image.
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
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This header specifies a class for searching for a structure with
 * constant color in an image.
 * For this a method findImageStructure() is defined.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * For this you can use this class.
 * @see findImageStructure()
 *
 * @pattern Strategy
 * @see cImageAreaSameColor
 * @see cConvertImageToFib
 * @see iFindImageStructure
 * @see iConvertImageStructureToFib
 */
/*
History:
18.02.2013  Oesterholz  created
*/


#ifndef ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_SEARCH_FOR_STRUCTURE__C_FIND_IMAGE_AREA_SAME_COLOR_SIMPLE_H__
#define ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_SEARCH_FOR_STRUCTURE__C_FIND_IMAGE_AREA_SAME_COLOR_SIMPLE_H__

#include "version.h"

#include "iFindImageStructure.h"

#include "cImageAreaSameColor.h"



namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{

namespace nSearchForStructure{


class cFindImageAreaSameColorSimple: public iFindImageStructure{
protected:
	
	/**
	 * The type number of the property to use. (e. g. cTypeProperty::COLOR_RGB )
	 * @see fib::cTypeProperty
	 * @see iImageData::getNumberOfProperties()
	 * @see iImageData::getProperty()
	 * @see maxErrorPerPoint
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
	 * The number of maximal retrys to find a better color for the area.
	 * Note if maxErrorPerPoint is 0 this property is irrelevant.
	 * @see maxErrorPerPoint
	 * @see propertyTypeNumber
	 */
	unsigned int uiNumberOfMaxCenterColorAdaptions;
	
	/**
	 * A realy smaal value, error values lower will be taken as zero.
	 * Just for internal use.
	 */
	mutable double zeroErrorValue;
	
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
	 * @param uiInNumberOfMaxCenterColorAdaptions The number of maximal
	 * 	retrys to find a better color for the area.
	 * 	Note if maxErrorPerPoint is 0 this property is irrelevant.
	 * 	@see uiNumberOfMaxCenterColorAdaptions
	 */
	cFindImageAreaSameColorSimple( unsigned int uiPropertyType,
		const double dMaxErrorPerPoint = 0, const bool bInCanBeAntialised = true,
		const unsigned int uiInNumberOfMaxCenterColorAdaptions = 3 );
	
	
	/**
	 * This method is for searching in an image for an area with the same color.
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
	virtual cImageAreaSameColor * findImageStructure(
		const pair< long, long> paStartPoint,
		cConvertImageToFib * pConvertImageToFib ) const;
	
	/**
	 * @return the name of this class
	 */
	virtual string getName() const;
	
protected:
	
	/**
	 * This method is for searching in an image for an area with the same color.
	 * The neighbour points of the generated structure will just contain
	 * points not overlapped in the search structure.
	 * @see cImageStructure::structureNeighbourPoints
	 * @see cImageSearchData::pImageDataOverlapped
	 * In the search structure (pConvertImageToFib->getImageSearchData()) this
	 * method will set all structure points and there neighbour points as found.
	 * This is a help method for: @see findImageStructure()
	 *
	 * @param vecStartPoint the point where to start the search;
	 * 	it will be included in the generated image structure setOutStructurePoints
	 * @param vecCenterPropertyPoint point with the the property the area
	 * 	should have; it is the center property to which the distance for
	 * 	dMaxErrorPerPoint will be evalued
	 * @param dMaxErrorPerPoint the maximal error for a point of the area
	 * @param pConvertImageToFib a pointer to the object for converting an
	 * 	image to a Fib object (it should implement methods to get the
	 * 	image search data);
	 * 	The image data (getImageData()) of the search data
	 * 	(pConvertImageToFib->getImageSearchData()) should have a
	 * 	propertyTypeNumber'th property for each point.
	 * @param setOutStructurePoints a reference to a set to output the
	 * 	structure points to
	 * @param setOutStructureNeighboursPoints a reference to a set to output
	 * 	the structure neighbour points to
	 * @return a pointer to a point, for which property it could be usefull
	 * 	to generate a new area
	 * 	Beware: You have to delete the returned point after usage.
	 */
	pair< unsigned int, unsigned int> * convertToAreaAndSearchForBetterColor(
		const pair< unsigned int, unsigned int> & vecStartPoint,
		const pair< unsigned int, unsigned int> & vecCenterPropertyPoint,
		const double dMaxErrorPerPoint,
		cConvertImageToFib * pConvertImageToFib,
		set< pair< unsigned int, unsigned int> > & setOutStructurePoints,
		set< pair< unsigned int, unsigned int> > & setOutStructureNeighboursPoints ) const;
	
	/**
	 * This method is for searching in an image for an area with the same color.
	 * The neighbour points of the generated structure will just contain
	 * points not overlapped in the search structure.
	 * @see cImageStructure::structureNeighbourPoints
	 * @see cImageSearchData::pImageDataOverlapped
	 * In the search structure (pConvertImageToFib->getImageSearchData()) this
	 * method will set all structure points and there neighbour points as found.
	 * This is a help method for: @see findImageStructure()
	 *
	 * @param vecStartPoint the point where to start the search;
	 * 	it will be included in the generated image structure setOutStructurePoints
	 * @param vecCenterPropertyPoint point with the the property the area
	 * 	should have; it is the center property to which the distance for
	 * 	dMaxErrorPerPoint will be evalued
	 * @param dMaxErrorPerPoint the maximal error for a point of the area
	 * @param pConvertImageToFib a pointer to the object for converting an
	 * 	image to a Fib object (it should implement methods to get the
	 * 	image search data);
	 * 	The image data (getImageData()) of the search data
	 * 	(pConvertImageToFib->getImageSearchData()) should have a
	 * 	propertyTypeNumber'th property for each point.
	 * @param setOutStructurePoints a reference to a set to output the
	 * 	structure points to
	 * @param setOutStructureNeighboursPoints a reference to a set to output
	 * 	the structure neighbour points to
	 */
	void convertToArea(
		const pair< unsigned int, unsigned int> & vecStartPoint,
		const pair< unsigned int, unsigned int> & vecCenterPropertyPoint,
		const double dMaxErrorPerPoint,
		cConvertImageToFib * pConvertImageToFib,
		set< pair< unsigned int, unsigned int> > & setOutStructurePoints,
		set< pair< unsigned int, unsigned int> > & setOutStructureNeighboursPoints ) const;

	/**
	 * This method is for searching in an image for an area with the same color.
	 * The neighbour points of the generated structure will just contain
	 * points not overlapped in the search structure.
	 * @see cImageStructure::structureNeighbourPoints
	 * @see cImageSearchData::pImageDataOverlapped
	 * In the search structure (pConvertImageToFib->getImageSearchData()) this
	 * method will set all structure points and there neighbour points as found.
	 * (Note every maxErrorPerPoint will be ignored, properties have to
	 * match perfect.)
	 * This is a help method for: @see findImageStructure()
	 *
	 * @param vecStartPoint the point where to start the search;
	 * 	it will be included in the generated image structure setOutStructurePoints
	 * @param pConvertImageToFib a pointer to the object for converting an
	 * 	image to a Fib object (it should implement methods to get the
	 * 	image search data);
	 * 	The image data (getImageData()) of the search data
	 * 	(pConvertImageToFib->getImageSearchData()) should have a
	 * 	propertyTypeNumber'th property for each point.
	 * @param setOutStructurePoints a reference to a set to output the
	 * 	structure points to
	 * @param setOutStructureNeighboursPoints a reference to a set to output
	 * 	the structure neighbour points to
	 */
	void convertToArea(
		const pair< unsigned int, unsigned int> & vecStartPoint,
		cConvertImageToFib * pConvertImageToFib,
		set< pair< unsigned int, unsigned int> > & setOutStructurePoints,
		set< pair< unsigned int, unsigned int> > & setOutStructureNeighboursPoints ) const;
	
	/**
	 * This method checks if the area should be antialised and returns a
	 * new starting point not in the antialised border of the area.
	 * This is a help method for: @see findImageStructure()
	 *
	 * @param vecStartPoint the point where to start the search
	 * @param dMaxErrorPerPoint the maximal error for a point of the area
	 * @param pConvertImageToFib a pointer to the object for converting an
	 * 	image to a Fib object (it should implement methods to get the
	 * 	image search data);
	 * 	The image data (getImageData()) of the search data
	 * 	(pConvertImageToFib->getImageSearchData()) should have a
	 * 	propertyTypeNumber'th property for each point.
	 * @return the point wich should be used as the start point because the
	 * 	area is antialised, or NULL if the start point is not antialised
	 * 	Beware: You have to delete the returned point after usage.
	 */
	pair< unsigned int, unsigned int> * checkIfStartPointIsAntialised(
		const pair< unsigned int, unsigned int> & vecStartPoint,
		const double dMaxErrorPerPoint,
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
	 * @param setOutStructureNeighboursNeighboursPoints a set to output
	 * 	the structure neighbours neighbours of points not in the structure
	 * 	or its neighbours
	 * @return true if the structure border neighbours are antialised else false
	 */
	bool checkIfBorderIsAntialised( const cImageAreaSameColor * pStructureToCheck,
			const cImageSearchData * pImageSearchData,
			set< pair< unsigned int, unsigned int> > &
				setOutStructureNeighboursNeighboursPoints ) const;
	
	
};//interface cFindImageAreaSameColorSimple


};//end namespace nSearchForStructure
};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_SEARCH_FOR_STRUCTURE__C_FIND_IMAGE_AREA_SAME_COLOR_SIMPLE_H__
