/**
 * @file iConvertToFib
 * file name: iConvertToFib.h
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
 * GNU Lesser General Public License for more details.
 *
 * This header specifies a class to store the data for a search on image data.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * To mark for which points structures wher found and which points you can
 * set to any overwritten property because the points are overwritten, you
 * can use this class.
 *
 * This header specifies a interface for converting data to a Fib object.
 * For this an method convertToFib() is defined.
 *
 */
/*
History:
22.08.2012  Oesterholz  created
*/


#ifndef ___I_CONVERT_TO_FIB_H__
#define ___I_CONVERT_TO_FIB_H__

#include "version.h"

#include "cFibElement.h"



namespace fib{

namespace algorithms{

namespace nConvertToFib{


class iConvertToFib{
public:
	
	/**
	 * This method is for converting data to a Fib object.
	 *
	 * @return a Fib-object which represents the data of this object
	 * 	Beware: You have to delete the returned Fib-object after usage.
	 */
	virtual cFibElement * convertToFib() const = 0;
	
	
};//interface iConvertToFib

};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___I_CONVERT_TO_FIB_H__
