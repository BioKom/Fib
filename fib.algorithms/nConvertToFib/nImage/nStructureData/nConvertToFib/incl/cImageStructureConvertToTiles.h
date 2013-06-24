/**
 * @file cImageStructureConvertToTiles
 * file name: cImageStructureConvertToTiles.h
 * @author Betti Oesterholz
 * @date 29.11.2012
 * @mail Oesterholz@Fib-development.org
 *
 * System: C++
 *
 * This header specifies a class to convert the data of a area of points
 * in an image to tiles.
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
 * This header specifies a class to convert the data of a area of points
 * in an image to tiles.
 *
 * @patter strategy
 */
/*
History:
29.11.2012  Oesterholz  created
*/


#ifndef ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__N_CONVERT_TO_FIB__C_IMAGE_STRUCTURE_CONVERT_TO_TILES_H__
#define ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__N_CONVERT_TO_FIB__C_IMAGE_STRUCTURE_CONVERT_TO_TILES_H__

#include "version.h"

#include "iConvertAreaToExtObjects.h"

#include "cImageSearchData.h"

#include "cExtObject.h"

#include <list>

using namespace std;
using namespace fib;

namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{

namespace nStructureData{

namespace nConvertToFib{


class cImageStructureConvertToTiles: public iConvertAreaToExtObjects{
protected:
	
	/**
	 * The number of parameters for the porder function.
	 * Beware: The values IDENTIFIER_SPLINE_OBJECT_XY and IDENTIFIER_SPLINE_OBJECT_YX
	 * 	should match.
	 * @see IDENTIFIER_SPLINE_OBJECT_XY
	 * @see IDENTIFIER_SPLINE_OBJECT_YX
	 */
	unsigned int NUMBER_OF_SPLINE_PARAMETERS;
	
	/**
	 * The identifier for a tile object in x y direction (spline border is f( x ) )
	 */
	int IDENTIFIER_SPLINE_OBJECT_XY;
	/**
	 * The identifier for a tile object in y x direction (spline border is f( y ) )
	 */
	int IDENTIFIER_SPLINE_OBJECT_YX;

	/**
	 * The identifier for a antialised tile object in x y direction (spline border is f( x ) )
	 */
	int IDENTIFIER_SPLINE_OBJECT_AA_XY;
	/**
	 * The identifier for a antialised tile object in y x direction (spline border is f( y ) )
	 */
	int IDENTIFIER_SPLINE_OBJECT_AA_YX;

	/**
	 * The factor of difference betwean the weigt factors.
	 * if the weight for the i'th parameter p_i is w_i
	 * the weight for the (i-1)'th parameter p_(i-1) is w_(i-1) = w_i * D_WEIGHT_FACTOR
	 * (exsept the 0't parameter weight (the constant) which is allways 0);
	 * The weight parameter for last parameter id allways D_WEIGHT_FACTOR
	 */
	const double D_WEIGHT_FACTOR;
	
	/**
	 * If true, it will be tried to reduce the number of bits for the
	 * parameter of the found splines.
	 */
	bool bReduceBitsForParameter;
	
public:
	
	/**
	 * standard constructor
	 *
	 * @param uiNumberOfSplineParameters the number of parameters for the
	 * 	porder function
	 * 	Beware: Just some values are valid
	 * 	Valid values: 2, 3, 4
	 * 	@see NUMBER_OF_SPLINE_PARAMETERS
	 * @param dWeightFactor the factor of difference betwean the weigt factors
	 * 	@see D_WEIGHT_FACTOR
	 * @param bInReduceBitsForParameter if true, it will be tried to reduce
	 * 	the number of bits for the parameter of the found splines
	 * 	@see bReduceBitsForParameter
	 */
	cImageStructureConvertToTiles( unsigned int uiNumberOfSplineParameters = 3,
			const double dWeightFactor = 0.0001,
			const bool bInReduceBitsForParameter = true );
	
	/**
	 * copy constructor
	 *
	 * @param imageStructureConvertToTiles the cImageStructureConvertToTiles
	 * 	object to copy
	 */
	cImageStructureConvertToTiles(
		const cImageStructureConvertToTiles & imageStructureConvertToTiles );
	
	/**
	 * destructor
	 */
	virtual ~cImageStructureConvertToTiles();
	
	/**
	 * This method clones this strategy object.
	 *
	 * @return a clone of this strategie object
	 */
	virtual cImageStructureConvertToTiles * clone() const;

	/**
	 * This method converts this cImageStructure to tiles and return ther data.
	 * The generated external objects will have no subobjects and are from
	 * the Fib database.
	 * Beware: You have to check for antialising with isAntialised().
	 * 	(If antialised add to tile external object identifer -10 .)
	 *
	 * @param structurePoints the set with the point of the area to convert
	 * @param pImageSearchData a pointer to the image search data of found
	 * 	image parts, which will overwrite tile parts
	 * 	(the tiles can be bigger, because some parts of them won't be seen)
	 * @param bIsAntialised if true the converted area should be antialised,
	 * 	(the generated external objects should be for antialising), else
	 * 	the area should not be antialised
	 * @param maxValue the maximum possible value in all parameters,
	 * 	the evalued spline/function elements will allways have value
	 * 	parameters vecFactors[i] with
	 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< vecFactors.size();
	 * 	if 0 (standard value) is given, the maximum possible value will
	 * 	be evalued from the given data (absolute maximum in given data * 256)
	 * @param maxErrorPerValue the maximal error for the border polynoms to
	 * 	find on one border point; the error on the interpolated polynom
	 * 	for every border point in vecData will be equal or less than
	 * 	maxErrorPerValue
	 * @return a list with the data for the tiles as external object elements
	 * 	from the database with the identifier -70 or -71
	 */
	virtual list< cExtObject * > convertToExtObjects(
		const set<cVectorPosition> & structurePoints,
		const cImageSearchData * pImageSearchData,
		const bool bIsAntialised = false,
		double maxValue = 0.0,
		const double maxErrorPerValue = 0.0 ) const;
	
};//class cImageStructureConvertToTiles


};//end namespace nConvertToFib
};//end namespace nStructureData
};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__N_CONVERT_TO_FIB__C_IMAGE_STRUCTURE_CONVERT_TO_TILES_H__