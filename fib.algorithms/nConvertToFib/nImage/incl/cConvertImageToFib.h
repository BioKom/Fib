/**
 * @file cConvertImageToFib
 * file name: cConvertImageToFib.h
 * @author Betti Oesterholz
 * @date 17.02.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies a class for converting a image to a Fib object.
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
 * This header specifies a class for converting an image to a Fib object.
 * For this a virtual method convertToFib() is defined (but not implemented).
 * This class should be the parent class of classes to convert an image to
 * a Fib object.
 * The parameter for converting should be set in the child classes.
 * The classes which implement the iFindImageStructure interface, should
 * do the searching of image structures. They should return objects
 * which implements cImageStructure, and can be converted to image
 * structures.
 * The parameter for converting should be given to the children of this
 * class. Which in turn will pass them to the classes which implement the
 * iFindImageStructure interface.
 *
 * @pattern Strategy
 * @see iFindImageStructure
 * @see cImageStructure
 */
/*
History:
17.02.2013  Oesterholz  created
*/


#ifndef ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__C_CONVERT_IMAGE_TO_FIB_H__
#define ___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__C_CONVERT_IMAGE_TO_FIB_H__


#include "version.h"

#include "iImageData.h"
#include "iConvertToFib.h"

#include "cImageSearchData.h"

#include <string>

using std::string;


namespace fib{

namespace algorithms{

namespace nConvertToFib{

namespace nImage{


class cConvertImageToFib{
protected:
	
	/**
	 * The image data to convert.
	 *
	 * @see isImageDataCopy
	 */
	const iImageData * pImageData;
	
	/**
	 * If true the image data pImageData is a copy of the origianl image
	 * data and needs to be deleted on destructiong this object.
	 * Else if false the pointer pImageData points to the original data
	 * and should not be deleted.
	 *
	 * @see pImageData
	 */
	bool isImageDataCopy;
	
	
	/**
	 * A map with the buffered derivations of this object.
	 */
	mutable map< list< unsigned int >, const iMatrix3D * > mapEvaluedDerivations;
	
	
	/**
	 * The actual search data of the to convert image.
	 */
	fib::algorithms::nConvertToFib::nImage::nStructureData::cImageSearchData *
		pImageSearchData;
	
	
	/**
	 * constructor
	 * (Constructs an empty object, childs have to fill the member fields.)
	 */
	cConvertImageToFib();
	
public:
	
	/**
	 * constructor
	 *
	 * @param imageData the image data to convert;
	 * 	The given image data object will be copied. @see pImageData
	 */
	cConvertImageToFib( const iImageData & imageData );
	
	/**
	 * constructor
	 *
	 * @param pInImageData a pointer to the image data to convert;
	 * 	Beware this object won't be copied, so keep it alive as long as
	 * 	this object exists. @see pImageData
	 */
	cConvertImageToFib( const iImageData * pInImageData );
	
	/**
	 * destructor
	 */
	virtual ~cConvertImageToFib();
	
	
	
	/**
	 * This method is for converting the image data to a Fib object.
	 *
	 * @pattern Factory Method
	 * @return a Fib object which represents the the image data of this object
	 * 	or NULL if non could be generated
	 * 	Beware: You have to delete the returned Fib object after usage.
	 */
	virtual cRoot * convertToFib() = 0;
	
	
	/**
	 * @return the name of this class
	 */
	virtual string getName() const;
	
	/**
	 * @return a pointer to the data of the to convert image
	 * 	@see pImageData
	 */
	const iImageData * getImageData() const;
	
	
	/**
	 * This method evalues the derivation of the image data.
	 * (This object will also buffer the created derivations, so they will
	 * not be evalued every time a new.)
	 * @see mapEvaluedDerivations
	 *
	 * @param liDirection a list with the direction in which the
	 * 	derivation should be evalued; the first derivat will be evalued
	 * 	for the first element of the list and so on
	 * 	(the only valid directions are 0 or 1)
	 * @return a pointer to the data of the to convert image derivation
	 * 	(This object will delete the evalued derivation on destructing,
	 * 	so do not delete them youself.)
	 */
	const iMatrix3D * getDerivation(
		const list< unsigned int > liDirection ) const;
	
	/**
	 * This method evalues the first derivation of the image data.
	 * (This object will also buffer the created derivations, so they will
	 * not be evalued every time a new.)
	 * @see mapEvaluedDerivations
	 *
	 * @param uiDirection the direction in which the derivation should be evalued
	 * 	(the only valid directions are 0 or 1)
	 * @return a pointer to the data of the to convert image derivation
	 * 	(This object will delete the evalued derivation on destructing,
	 * 	so do not delete them youself.)
	 */
	const iMatrix3D * getDerivation( const unsigned int uiDirection ) const;
	
	
	/**
	 * @return a pointer to the actual search data of the to convert image
	 * 	(search methods should adapt it)
	 */
	fib::algorithms::nConvertToFib::nImage::nStructureData::cImageSearchData *
		getImageSearchData();
	
	
};//interface cConvertImageToFib


};//end namespace nImage
};//end namespace nConvertToFib
};//end namespace algorithms
};//end namespace fib


#endif //___FIB__ALGORITHMS__N_CONVERT_TO_FIB__N_IMAGE__C_CONVERT_IMAGE_TO_FIB_H__
