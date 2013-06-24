/**
 * @file cConvertImageToFib
 * file name: cConvertImageToFib.cpp
 * @author Betti Oesterholz
 * @date 25.02.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header implements a class for converting a image to a Fib object.
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
 * This header implements a class for converting an image to a Fib object.
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
25.02.2013  Oesterholz  created
*/



#include "cConvertImageToFib.h"

#include "cDomains.h"
#include "cDomainSingle.h"
#include "cDomainVectorBasis.h"
#include "cTypeDimension.h"




using namespace fib::algorithms::nConvertToFib::nImage;
using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;


/**
 * constructor
 */
cConvertImageToFib::cConvertImageToFib():
		pImageData( NULL ), isImageDataCopy( false ),
		pImageSearchData( NULL ){
	//nothing to do
}


/**
 * constructor
 *
 * @param imageData the image data to convert;
 * 	The given image data object will be copied. @see pImageData
 */
cConvertImageToFib::cConvertImageToFib( const iImageData & imageData ):
		pImageData( imageData.clone() ), isImageDataCopy( true ),
		pImageSearchData( new cImageSearchData( pImageData ) ){
	//nothing to do
}


/**
 * constructor
 *
 * @param pInImageData a pointer to the image data to convert;
 * 	Beware this object won't be copied, so keep it alive as long as
 * 	this object exists. @see pImageData
 */
cConvertImageToFib::cConvertImageToFib( const iImageData * pInImageData ):
		pImageData( pInImageData ), isImageDataCopy( false ),
		pImageSearchData( new cImageSearchData( pImageData ) ){
	//nothing to do
}


/**
 * destructor
 */
cConvertImageToFib::~cConvertImageToFib(){
	
	//delete image data if it is a copy
	if ( isImageDataCopy && ( pImageData != NULL ) ){
		delete pImageData;
	}
	//delete derivate lists
	for ( map< list< unsigned int >, const iMatrix3D * >::iterator
			itrDerivate = mapEvaluedDerivations.begin();
			itrDerivate != mapEvaluedDerivations.end(); itrDerivate++ ){
		
		delete itrDerivate->second;
	}
	if ( pImageSearchData ){
		delete pImageSearchData;
	}
}


/**
 * @return the name of this class
 */
string cConvertImageToFib::getName() const{
	
	return "cConvertImageToFib";
}


/**
 * @return a pointer to the data of the to convert image
 * 	@see pImageData
 */
const iImageData * cConvertImageToFib::getImageData() const{
	
	return pImageData;
}


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
const iMatrix3D * cConvertImageToFib::getDerivation(
		const list< unsigned int > liDirection ) const{
	
	const iMatrix3D * pActualDerivate = pImageData;
	if ( liDirection.empty() ){
		//no derivate to evalue -> return original
		return pActualDerivate;
	}
	list< unsigned int >::const_iterator itrActualDerivate = liDirection.end();
	//the actual derivate
	list< unsigned int > liActualDerivate = liDirection;
	/*itrActualDerivate points after the last element in liActualDerivate or
	 itrActualDerivate points to the next direction number after the
	 last in liActualDerivate to evalue a derivate for*/
	//search if the derivate or a derivate of lesser order was evalued befor
	for ( ;itrActualDerivate != liDirection.begin(); itrActualDerivate-- ){
		
		map< list< unsigned int >, const iMatrix3D * >::const_iterator
			itrMapDerivate = mapEvaluedDerivations.find( liActualDerivate );
		
		if ( itrMapDerivate != mapEvaluedDerivations.end() ){
			//the derivate was evalued befor
			pActualDerivate = itrMapDerivate->second;
			break;
		}
		liActualDerivate.pop_back();
	}
	
	//evalue needed derivations
	for ( ;itrActualDerivate != liDirection.end(); itrActualDerivate++ ){
		
		const unsigned int uiActualDirection = (*itrActualDerivate);
		if ( 1 < uiActualDirection ){
			//not a valid direction
			return NULL;
		}
		liActualDerivate.push_back( uiActualDirection );
		
		//implement and use iMatrix3D::evalueDerivate()
		pActualDerivate = pActualDerivate->evalueDerivate( uiActualDirection );
		
		if ( pActualDerivate == NULL ){
			//no derivate could be evalued
			return NULL;
		}//else remember derivat
		mapEvaluedDerivations.insert( pair< list< unsigned int >, const iMatrix3D * >(
			liActualDerivate, pActualDerivate ) );
	}
	return pActualDerivate;
}


/**
 * This method evalues the first derivation of the image data.
 * (This object will also buffer the created derivations, so they will
 * not be evalued every time a new.)
 * @see mapEvaluedDerivations
 * @see getDerivation()
 *
 * @param uiDirection the direction in which the derivation should be evalued
 * 	(the only valid directions are 0 or 1)
 * @return a pointer to the data of the to convert image derivation
 * 	(This object will delete the evalued derivation on destructing,
 * 	so do not delete them youself.)
 */
const iMatrix3D * cConvertImageToFib::getDerivation(
		const unsigned int uiDirection ) const{
	
	list< unsigned int > liDirection;
	liDirection.push_back( uiDirection );
	
	return getDerivation( liDirection );
}


/**
 * @return a pointer to the actual search data of the to convert image
 * 	(search methods should adapt it)
 */
cImageSearchData * cConvertImageToFib::getImageSearchData(){
	
	return pImageSearchData;
}








