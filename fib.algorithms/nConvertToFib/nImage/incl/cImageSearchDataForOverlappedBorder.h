/**
 * @file cImageSearchDataForOverlappedBorder
 * file name: cImageSearchDataForOverlappedBorder.h
 * @author Betti Oesterholz
 * @date 29.04.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class to store the data for a search on image
 * data and data for the border of the overlapped area.
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
 * This header specifies a class to store the data for a search on image
 * data and data for the border of the overlapped area.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * To mark for which points structures wher found and which points you can
 * set to any overwritten property because the points are overwritten, you
 * can use this class.
 *
 * This class will also help to get border points of the overlapped area
 * @see getBorderPoint()
 * and to mark points of a Fib object as overlapped. @see evaluePosition()
 *
 * All positions vectors (cVectorPosition) elements should be positiv
 * integers from 0 to ulBorderX or ulBorderY respectively.
 *
 */
/*
History:
29.04.2013  Oesterholz  created
*/


#ifndef ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__C_IMAGE_SEARCH_DATA_FOR_OVERLAPPED_BORDER_H__
#define ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__C_IMAGE_SEARCH_DATA_FOR_OVERLAPPED_BORDER_H__

#include "version.h"

#include "cImageSearchData.h"
#include "iEvaluePosition.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"

#include <queue>
#include <list>


using namespace std;
using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;

namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{


class cImageSearchDataForOverlappedBorder: public cImageSearchData,
	public iEvaluePosition{
protected:
	
	/**
	 * The container for possible points, which are not overlapped, but near
	 * overlapped points.
	 */
	queue< pair< unsigned int, unsigned int> > qePossibleOverlappedBorderPoints;
	
	/**
	 * Just points with a lower transparency value will be marked as
	 * overlapped when evalued by @see evaluePosition()
	 */
	const double dTransparencyThreshold;
	
public:
	
	/**
	 * parameter constructor
	 *
	 * @param ulInWidth the width of the image to search @see ulBorderX
	 * @param ulInHeight the height of the image to search @see ulBorderY
	 * @param dInTransparencyThreshold just points with a lower or equal transparency
	 * 	value will be marked as overlapped when evalued by @see evaluePosition()
	 * 	@see dTransparencyThreshold
	 */
	cImageSearchDataForOverlappedBorder(
			const unsigned long ulInWidth, const unsigned long ulInHeight,
			const double dInTransparencyThreshold = 0.01 );

	/**
	 * parameter constructor
	 *
	 * @param pInImageData pointer to the image data, of the image to convert
	 * 	@see pImageData
	 * @param dInTransparencyThreshold just points with a lower or equal transparency
	 * 	value will be marked as overlapped when evalued by @see evaluePosition()
	 * 	@see dTransparencyThreshold
	 */
	cImageSearchDataForOverlappedBorder( const iImageData * pInImageData,
			const double dInTransparencyThreshold = 0.01 );
	
	/**
	 * copy constructor
	 *
	 * @param pInImageData pointer to the image search data to copy
	 */
	cImageSearchDataForOverlappedBorder(
			const cImageSearchDataForOverlappedBorder & imageSearchData );
	
	
	/**
	 * destructor
	 */
	virtual ~cImageSearchDataForOverlappedBorder();
	
	
	/**
	 * This method clones this object.
	 *
	 * @return a pointer to the clone of this object
	 */
	cImageSearchDataForOverlappedBorder * clone() const;
	
	
	/**
	 * @return the transparency threshold value
	 * 	@see dTransparencyThreshold
	 */
	double getTransparencyThreshold() const;
	
	/**
	 * @return true and a point near the overlapped points but not overlapped
	 * 	itself, or false
	 * 		first: if a border point exists
	 * 		second: if first is true the point near the overlapped points but
	 * 			not overlapped
	 */
	pair< bool, pair< unsigned int, unsigned int> > getBorderPoint();
	
	/**
	 * This method will mark every point with a transparency value lower or
	 * equal the transparency threshold (or no transparency) as overlapped.
	 * @see dTransparencyThreshold
	 *
	 * @param vPosition the position of the point, which is evalued
	 * @param vProperties a list of the properties of the point
	 */
	virtual bool evaluePosition( const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties );
	
};//class cImageSearchDataForOverlappedBorder


};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__C_IMAGE_SEARCH_DATA_FOR_OVERLAPPED_BORDER_H__
