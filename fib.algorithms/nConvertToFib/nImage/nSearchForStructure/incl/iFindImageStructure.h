/**
 * @file iFindImageStructure
 * file name: iFindImageStructure.h
 * @author Betti Oesterholz
 * @date 18.02.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a interface for searching for a structure in an
 * image.
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
 * This header specifies a interface for searching for a structure
 * (cImageStructure) in an image.
 * For this a method findImageStructure() is defined.
 * If you want to convert an image to Fib structures, you have to search
 * the image for structures, which can be converted to Fib.
 * For this you can use this class.
 * @see findImageStructure()
 *
 * @pattern Strategy
 * @see cConvertImageToFib
 * @see cImageStructure
 * @see iConvertImageStructureToFib
 */
/*
History:
18.02.2013  Oesterholz  created
*/


#ifndef ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_SEARCH_FOR_STRUCTURE__I_FIND_IMAGE_STRUCTURE_H__
#define ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_SEARCH_FOR_STRUCTURE__I_FIND_IMAGE_STRUCTURE_H__

#include "version.h"

#include "cImageStructure.h"
#include "cConvertImageToFib.h"

#include <string>


using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;
using std::string;

namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{

namespace nSearchForStructure{


class iFindImageStructure{
public:
	
	/**
	 * destructor
	 */
	virtual ~iFindImageStructure(){};
	
	/**
	 * This method is for searching in an image for a structure.
	 *
	 * @param paStartPoint the point wher to start the search;
	 * 	it should be included in the generated image structure
	 * @param pConvertImageToFib a pointer to the object for converting an
	 * 	image to a Fib object (it shhould implement methods to get the
	 * 	image and image search data)
	 * @return the found image structure, or the null pointer NULL if non
	 * 	could be found
	 * 	Beware: You have to delete the returned image structure after usage.
	 */
	virtual cImageStructure * findImageStructure(
		const pair< long, long> paStartPoint,
		cConvertImageToFib * pConvertImageToFib ) const = 0;
	
	/**
	 * @return the name of this class
	 */
	virtual string getName() const = 0;
	
};//interface iFindImageStructure


};//end namespace nSearchForStructure
};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_SEARCH_FOR_STRUCTURE__I_FIND_IMAGE_STRUCTURE_H__
