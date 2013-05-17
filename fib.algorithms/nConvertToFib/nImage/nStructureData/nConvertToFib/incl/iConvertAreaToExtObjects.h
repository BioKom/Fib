/**
 * @file iConvertAreaToExtObjects
 * file name: iConvertAreaToExtObjects.h
 * @author Betti Oesterholz
 * @date 26.01.2013
 * @mail Oesterholz@Fib-development.org
 *
 * System: C++
 *
 * This header specifies a interface to convert an area of points to a list
 * of external objects.
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
 * This header specifies a interface to convert an area of points to a list
 * of external objects.
 *
 * @patter strategy
 */
/*
History:
26.01.2013  Oesterholz  created
*/


#ifndef ___I_CONVERT_AREA_TO_EXT_OBJECTS_H__
#define ___I_CONVERT_AREA_TO_EXT_OBJECTS_H__

#include "version.h"

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


class iConvertAreaToExtObjects{
public:
	
	/**
	 * destructor
	 */
	virtual ~iConvertAreaToExtObjects(){};
	
	/**
	 * This method clones this strategy object.
	 *
	 * @return a clone of this strategie object
	 */
	virtual iConvertAreaToExtObjects * clone() const = 0;
	
	/**
	 * This method converts this cImageStructure to external objects and
	 * returns them.
	 * The generated external objects will have no subobjects and are from
	 * the Fib database.
	 * Beware: You have to check for antialising with isAntialised().
	 * 	(If antialised change external object identifer.)
	 *
	 * @param structurePoints the set with the points of the area to convert
	 * @param pImageSearchData a pointer to the image search data of found
	 * 	image parts, which will overwrite the generated external objects
	 * 	area parts (the external objects areas can be bigger, because some
	 * 	parts of them won't be seen)
	 * @param bIsAntialised if true the converted area should be antialised,
	 * 	(the generated external objects should be for antialising), else
	 * 	the area should not be antialised
	 * @param maxValue the maximum possible value in all evalued parameters
	 * 	of the evalued external object elements will allways have lower
	 * 	absolute values or the input values (parameters) of the external
	 * 	object elements are coordinate values of points;
	 * 	if 0 (standard value) is given, the maximum possible value will
	 * 	be evalued from the given data (absolute maximum in given data * 256)
	 * @param maxErrorPerValue the maximal error for the border points to
	 * 	find on one border point; every point in the area of the generated
	 * 	external objects will have a distance lower or equal maxErrorPerValue
	 * 	to a point in structurePoint or an overlappted point of pImageSearchData
	 * @return a list with the data for the external object elements
	 * 	from the database
	 */
	virtual list< cExtObject * > convertToExtObjects(
		const set<cVectorPosition> & structurePoints,
		const cImageSearchData * pImageSearchData,
		const bool bIsAntialised = false,
		double maxValue = 0.0,
		const double maxErrorPerValue = 0.0 ) const = 0;
	
};//class iConvertAreaToExtObjects


};//end namespace nConvertToFib
};//end namespace nStructureData
};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___I_CONVERT_AREA_TO_EXT_OBJECTS_H__