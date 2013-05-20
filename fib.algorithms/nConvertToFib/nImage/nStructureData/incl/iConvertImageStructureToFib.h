/**
 * @file iConvertImageStructureToFib
 * file name: iConvertImageStructureToFib.h
 * @author Betti Oesterholz
 * @date 22.08.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a interface for converting data to a Fib object.
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
 *
 * This header specifies a interface for converting data to a Fib object.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * To convert a image structure, classes can use this interface.
 *
 * For this an method convertToFib() is defined.
 *
 */
/*
History:
22.08.2012  Oesterholz  created
*/


#ifndef ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__I_CONVERT_IMAGE_STRUCTURE_TO_FIB_H__
#define ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__I_CONVERT_IMAGE_STRUCTURE_TO_FIB_H__

#include "version.h"

#include "iConvertToFib.h"

#include "cImageSearchData.h"



namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{

namespace nStructureData{


class iConvertImageStructureToFib:
		public fib::algorithms::nConvertToFib::iConvertToFib{
public:
	
	/**
	 * This method is for converting data to a Fib object.
	 *
	 * @return a Fib-object which represents the data of this object
	 * 	Beware: You have to delete the returned Fib object after usage.
	 * 		Also the given root element will contain no domains, you have to
	 * 		create them if needed (eg. with cRoot::generateNeededDomains() ).
	 */
	virtual cRoot * convertToFib() const = 0;
	
	/**
	 * This method is for converting data to a Fib object.
	 *
	 * @param pImageSearchData a pointer to the image search data of found
	 * 	image parts, which will overwrite tile parts
	 * 	(the evaled area can be bigger, because some parts of it won't be seen)
	 * @param maxValue the maximum possible value in all evalued parameters
	 * 	of the evalued elements will allways have lower absolute values or
	 * 	the values (parameters) of the elements are coordinate values of points;
	 * 	if 0 (standard value) is given, the maximum possible value will
	 * 	be evalued from the given data (absolute maximum in given data * 256)
	 * @param ulMaxErrorPerPoint the maximal error of a point or
	 * 	the maximal distance a point can be outside the area and the
	 * 	search area
	 * @return a Fib object which represents the data of this object
	 * 	Beware: You have to delete the returned Fib object after usage.
	 * 		Also the given root element will contain no domains, you have to
	 * 		create them if needed (eg. with cRoot::generateNeededDomains() ).
	 */
	virtual cRoot * convertToFib( const cImageSearchData * pImageSearchData,
		const double maxValue = 65536.0,
		const unsigned long ulMaxErrorPerPoint = 0.0 ) const = 0;
	
	
};//interface iConvertImageStructureToFib


};//end namespace nStructureData
};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__I_CONVERT_IMAGE_STRUCTURE_TO_FIB_H__
