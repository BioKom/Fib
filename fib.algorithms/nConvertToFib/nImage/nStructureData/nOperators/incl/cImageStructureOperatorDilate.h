/**
 * @file cImageStructureOperatorDilate
 * file name: cImageStructureOperatorDilate.h
 * @author Betti Oesterholz
 * @date 07.05.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for the dilate operator on an image structure.
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
 * This header specifies a class for the dilate operator on an image structure.
 * The operator will add all the (not found and) not overlapped neighbour
 * points of the structure to the structure and set the new neighbours of
 * the changed structure.
 * For this a operator operator() is defined.
 * The operator will change an image structure and adapt the given search data.
 *
 * @pattern Strategy
 * @see iImageStructureSearchOperator
 * @see cImageStructureOperatorErode
 * @see cImageStructure
 * @see cConvertImageToFib
 */
/*
History:
07.05.2013  Oesterholz  created
*/


#ifndef ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__N_OPERATORS__C_IMAGE_STRUCTURE_OPERATOR_DILATE_H__
#define ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__N_OPERATORS__C_IMAGE_STRUCTURE_OPERATOR_DILATE_H__

#include "version.h"

#include "cImageStructure.h"
#include "cImageSearchData.h"

#include "iImageStructureSearchOperator.h"

#include <string>

using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;
using std::string;


namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{

namespace nStructureData{

namespace nOperators{


class cImageStructureOperatorDilate: public iImageStructureSearchOperator{
public:
	
	/**
	 * destructor
	 */
	virtual ~cImageStructureOperatorDilate();
	
	/**
	 * This method is for execute this operator on the given image structure.
	 *
	 * @param pImageStructure the image structure on which to execute this operator
	 * 	(Beware it will be changed)
	 * @param pSearchData the image search data to update;
	 * 	Points of the given image structure should be marked as found.
	 * 	This operator will add all points added to the image structure
	 * 	as found in the image search data pSearchData and set all
	 * 	points as not found, which it deletes from the image structure
	 * 	(After the call all points in the image structure and just these
	 * 	will be marked as found.)
	 * @return true if the operator was successful, else false
	 */
	virtual bool operator()( cImageStructure * pImageStructure,
		cImageSearchData * pSearchData ) const;
	
	
	/**
	 * @return the name of this class
	 */
	virtual string getName() const;
	
};//interface cImageStructureOperatorDilate


};//end namespace nOperators
};//end namespace nStructureData
};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__N_STRUCTURE_DATA__N_OPERATORS__C_IMAGE_STRUCTURE_OPERATOR_DILATE_H__
