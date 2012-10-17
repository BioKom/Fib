/**
 * @file nConvertToFib
 * file name: nConvertToFib.h
 * @author Betti Oesterholz
 * @date 23.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions with which multimediaobjects in non fib
 * multimediaformats can be converted into fib -objects.
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This header specifies functions with which multimediaobjects in non fib
 * multimediaformats can be converted into fib -objects.
 *
 */
/*
History:
23.02.2010  Oesterholz  created
07.03.2011  Oesterholz  function convertOptimized() added
*/

#ifndef ___N_CONVERT_TO_FIB_H__
#define ___N_CONVERT_TO_FIB_H__

#include "version.h"

#include "cFibElement.h"
#ifdef FEATURE_OWN_FREE_IMAGE_WARPER
	//no FreeImagePlus wraper for windows -> use own
	#include "fipImage.h"
#else //WINDOWS
	#include <FreeImagePlus.h>
#endif //WINDOWS


#include <map>


using namespace std;
using namespace fib;

namespace nConvertToFib{

	/**
	 * This function converts the given multimediaobject into a fib -object.
	 *
	 * @param multimediaObject the multimedaobject to convert into fib;
	 * 	the inputformat is in the FreeImagePlus fipImage object
	 * @return the created fib -object
	 */
	cFibElement * convert( const fipImage & multimediaObject );

	/**
	 * This function converts the given multimediaobject into a fib -object.
	 * It creats a fib -object with one master root -element which contains a
	 * listelement as main -fib -object.
	 * the function will try to compress the pictur data. It will:
	 * 	- sperate the points in respect of ther colors (properties)
	 * 	- will create area fib-objects, for areas with the same color
	 * if bCreatebackground is true;
	 * 	- will set a background color, if non is given
	 *
	 * @see convert()
	 * @param multimediaObject the multimedaobject to convert into fib;
	 * 	the inputformat is in the FreeImagePlus fipImage object
	 * @param bCreatebackground if true, this function will set a background
	 * 	color, if non is given
	 * @param bCorrectPoints if wrong points should be corrected, in the
	 * 	last compressing step
	 * @return the created fib -object
	 */
	cFibElement * convertOptimized( const fipImage & multimediaObject,
		bool bCreatebackground=true, const bool bCorrectPoints=false );

	/**
	 * This function converts the given multimediaobject into a fib -object.
	 * It will reduce the data to compress, so not all points in the created
	 * fib-object will have the correct color.
	 * It creats a fib -object with one master root -element which contains a
	 * listelement as main -fib -object.
	 * the function will try to compress the pictur data. It will:
	 * 	- sperate the points in respect of ther colors (properties)
	 * 	- will create area fib-objects, for areas with the similar color
	 * if bCreatebackground is true;
	 * 	- will set a background color, if non is given
	 *
	 * @see convert()
	 * @param multimediaObject the multimedaobject to convert into fib;
	 * 	the inputformat is in the FreeImagePlus fipImage object
	 * @param bCreatebackground if true, this function will set a background
	 * 	color, if non is given
	 * @param ulMaxAreaDiff the maximal difference of color values in an area
	 * 	(as the sum of the color vector element distances)
	 * @param ulMinPoints if an area with less than ulMinPoints points exists and
	 * 	it layes beside an area with a color, wich has a less difference as
	 * 	ulMaxDiff to the color of the first area, both areas will be
	 * 	combinde with the color of the second area (if the first area has
	 * 	more than one area as a neibour, which fulfill ulMaxDiff, the one
	 * 	with the minimum color distance is taken)
	 * @param ulMaxDiff @see ulMinPoints
	 * @param uiMinPointsNeighbourAreas all neighbour areas with less than
	 * 	this number of points, will be subsumed by the area
	 * @param bCorrectPoints if wrong points should be corrected, in the
	 * 	last compressing step
	 * @param bCorrectMissingPoints correct points, wich are missing in the
	 * 	created area fib-objects
	 * @param bAddNeighbours add to the areas ther neigbours and remove not needed areas
	 * @param bReduceFunctionDomains reduce the bits to store the function (values)
	 * @param bReplaceAreasWithPoints rreplace areas, which need more bits
	 * 	to store than ther points, with ther points
	 * @param uiInMinPointsForArea the minimal number of points an area
	 * 	should have, to create an area object for it;
	 * 	if 0 the standad value will be taken
	 * @param maxError the maximal error for the area border polynoms to find;
	 * 	the error on the interpolated polynoms for the borders of the areas
	 * 	will beequal or less than maxError
	 * @return the created fib -object
	 */
	cFibElement * convertReduced( const fipImage & multimediaObject,
		bool bCreatebackground=true, const unsigned long ulMaxAreaDiff=3,
		const unsigned long ulMinPoints=4, const unsigned long ulMaxDiff=16,
		const unsigned int uiMinPointsNeighbourAreas=0,
		const bool bCorrectPoints=false, const bool bCorrectMissingPoints=false,
		const bool bAddNeighbours=false, const bool bReduceFunctionDomains=false,
		const bool bReplaceAreasWithPoints=false, const unsigned int uiInMinPointsForArea=0,
		const double maxError=0 );


	/**
	 * This function conts how oftern the different colors occure in the
	 * given pictur.
	 *
	 * @param multimediaObject the multimedaobject wher to count the colors
	 * @return a map with the color values and ther counts
	 */
	map< vector< unsigned int >, unsigned long > countColors(
		const fipImage & multimediaObject );


	/**
	 * This function maps the colors of the given pictur accordingly to the
	 * given mapping.
	 * Colors not in the map won't be changed.
	 *
	 * @param multimediaObject the multimedaobject wher to change the colors
	 * @param mapColorMapping the mapping for the colors:
	 * 	key: the source color
	 * 	value: to which color the color should be mapped
	 * 	(BEWARE: all color vectors of the map should have the correct size.)
	 */
	void mapColors( fipImage & multimediaObject,
		const map< vector< unsigned int >, vector< unsigned int > > & mapColorMapping );

}//end namespace nConvertToFib


#endif //___N_CONVERT_TO_FIB_H__







