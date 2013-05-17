/**
 * @class cFreeImageData
 * file name: cFreeImageData.cpp
 * @author Betti Oesterholz
 * @date 14.04.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains a warper class for FreeImage image data with the
 * iImageData interface.
 * Copyright (C) @c LGPL3 2012 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This file contains a warper class for FreeImage image data with the
 * iImageData interface.
 * (TODO: Just implemented for RGB images. No palettized image implemented.)
 * @pattern Fassade
 */
/*
History:
14.04.2012  Oesterholz  created
28.01.2013  Oesterholz  COLOR_SW changed to COLOR_GRAYSCALE
19.02.2013  Oesterholz  clone method and copy constructor added
*/


#include "cFreeImageData.h"

#include "cDomainVector.h"
#include "cDomainNaturalNumber.h"
#include "cTypeDimension.h"
#include "cTypeProperty.h"
#include "cMatrix3DInteger.h"


using namespace fib;


/**
 * standard constructor
 *
 * @param pInFipImageDataObject a pointer to the object, for which this
 * 	class is the wraper
 */
cFreeImageData::cFreeImageData( fipImage * pInFipImageDataObject ):
		pFipImageDataObject( pInFipImageDataObject ){
	//nothing to do
}


/**
 * copy constructor
 *
 * @param freeImageData the cFreeImageData object to copy
 */
cFreeImageData::cFreeImageData( cFreeImageData & freeImageData ):
		pFipImageDataObject( freeImageData.pFipImageDataObject ){
	//nothing to do
}


/**
 * destructor
 */
cFreeImageData::~cFreeImageData(){
	//nothing to do
}


/**
 * @return the name of this class
 */
string cFreeImageData::getName() const{
	
	return "cFreeImageData";
}


/**
 * This method clones this object.
 *
 * @return a pointer to the clone of this object
 */
cFreeImageData * cFreeImageData::clone() const{
	
	return new cFreeImageData( *(const_cast<cFreeImageData*>(this) ) );
}


/**
 * This method returns the domains for the color and transparency properties.
 *
 * @return the domains for the color and transparency properties
 */
cDomains cFreeImageData::getPropertyDomains() const{
	
	cDomains domains;
	
	if ( pFipImageDataObject->isTransparent() ){
		//transparency exists
		vector<cDomainSingle*> vecDomainTransparency( 1 );
		vecDomainTransparency[ 0 ] = new cDomainNaturalNumberBit( 8 );

		domains.addDomain( cTypeProperty( cTypeProperty::TRANSPARENCY ),
			cDomainVector( vecDomainTransparency ) );
		
		delete vecDomainTransparency[ 0 ];
	}
	
	cTypeProperty typeProperty( cTypeProperty::COLOR_RGB );
	const bool bSWColor = pFipImageDataObject->isGrayscale();
	if ( bSWColor ){
		typeProperty = cTypeProperty( cTypeProperty::COLOR_GRAYSCALE );
	}
	RGBQUAD * pColorPalette = pFipImageDataObject->getPalette();
	unsigned int uiBitsPerColor = 0;
	if ( pColorPalette == NULL ){
		uiBitsPerColor = pFipImageDataObject->getBitsPerPixel();
	}else{
		if ( bSWColor ){
			uiBitsPerColor = 8;
		}else{
			uiBitsPerColor = 24;
		}
	}
	
	//generate color domain
	vector<cDomainSingle*> * pVecDomainColor = NULL;
	if ( bSWColor ){
		pVecDomainColor = new vector<cDomainSingle*>( 1, ((cDomainSingle*)NULL) );
		(*pVecDomainColor)[ 0 ] = new cDomainNaturalNumberBit( uiBitsPerColor );
	}else{
		pVecDomainColor = new vector<cDomainSingle*>( 3, ((cDomainSingle*)NULL) );
		if ( pFipImageDataObject->getColorType() == FIC_RGB ){
			(*pVecDomainColor)[ 0 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 3 );
			(*pVecDomainColor)[ 1 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 3 );
			(*pVecDomainColor)[ 2 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 3 );
		}else{//TODO include other color typs
			//for FIC_RGBALPHA
			(*pVecDomainColor)[ 0 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 4 );
			(*pVecDomainColor)[ 1 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 4 );
			(*pVecDomainColor)[ 2 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 4 );
		}
	}
	
	domains.addDomain( typeProperty, cDomainVector( *pVecDomainColor ) );

	for ( unsigned int uiVectorElement = 0;
			uiVectorElement < pVecDomainColor->size(); uiVectorElement++ ){
		
		delete ((*pVecDomainColor)[ uiVectorElement ]);
	}
	delete pVecDomainColor;
	
	return domains;
}


/**
 * This method returns the domains for the positions (dimension domain).
 *
 * @return the domains for the positions (dimension domain)
 */
cDomains cFreeImageData::getPositionDomain() const{
	
	cDomains domains;
	
	vector<unsignedIntFib> vecDimensionMapping;
	vecDimensionMapping.push_back( 1 );
	vecDimensionMapping.push_back( 2 );
	
	const cTypeDimension typeDimension( vecDimensionMapping );
	
	vector<cDomainSingle*> vecDomainPosition( 2 );
	vecDomainPosition[ 0 ] = new cDomainNaturalNumber(
		pFipImageDataObject->getWidth() - 1 );
	vecDomainPosition[ 1 ] = new cDomainNaturalNumber(
		pFipImageDataObject->getHeight() - 1 );
	
	domains.addDomain( typeDimension, cDomainVector( vecDomainPosition ) );

	delete vecDomainPosition[ 0 ];
	delete vecDomainPosition[ 1 ];
	
	return domains;
}


/**
 * With this method the properties for a points are set.
 * Beware: No scaling is done. The position coordinate values are taken
 * as index values (counting starts at 0) for the image matrix. Color and
 * transparency values should be numbers from 0 to 255 (inclusive).
 *
 * @param vPosition the position of the point to set
 * @param vProperties a list of the properties of the point
 * @return true if the properties for the point cold be set, else false
 */
bool cFreeImageData::setPoint( const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties ){
	
	RGBQUAD * pColorValue = new RGBQUAD();
	RGBQUAD * pColorPalette = pFipImageDataObject->getPalette();
	
	longFib lX = -1;
	longFib lY = -1;
	if ( vPosition.getNumberOfElements() != 0 ){
		//normal point
		//get the correct position
		lX = fib::roundToLongFib( vPosition.getValue( 1 ) );
		
		if ( ( lX < 0 ) || ( ((longFib)(pFipImageDataObject->getWidth())) <= lX ) ){
			//point not in image
			delete pColorValue;
			return false;
		}
		lY = fib::roundToLongFib( vPosition.getValue( 2 ) );
		if ( ( lY < 0 ) || ( ((longFib)(pFipImageDataObject->getHeight())) <= lY ) ){
			//point not in image
			delete pColorValue;
			return false;
		}
		if ( pColorPalette == NULL ){
			const bool bColorValueEvalued =
				pFipImageDataObject->getPixelColor( lX, lY, pColorValue );
			if ( ! bColorValueEvalued ){
				delete pColorValue;
				return false;
			}
		}else{//use color pallette
			BYTE * pIndexValue = new BYTE();
			const bool bColorValueEvalued =
				pFipImageDataObject->getPixelIndex( lX, lY, pIndexValue );
			
			if ( ( ! bColorValueEvalued ) ||
					( pFipImageDataObject->getPaletteSize() <= (*pIndexValue) ) ){
				delete pColorValue;
				delete pIndexValue;
				return false;
			}
			(*pColorValue) = pColorPalette[ *pIndexValue ];
			delete pIndexValue;
		}
	}else{//background point
		const bool bColorValueEvalued =
			pFipImageDataObject->getFileBkColor( pColorValue );
		if ( ! bColorValueEvalued ){
			delete pColorValue;
			return false;
		}
		
		if ( pColorPalette != NULL ){
			if ( pFipImageDataObject->getPaletteSize() <=
					(pColorValue->rgbReserved) ){
				delete pColorValue;
				return false;
			}
			(*pColorValue) = pColorPalette[ pColorValue->rgbReserved ];
		}
	}
	
	/*the last found alpha value for the point;
	 init with 1 because transparency standard value is 0*/
	float fLastAlpha = 1.0;
	bool bNoAlpha = true;//no transparency property set
	
	for ( list<cVectorProperty>::const_iterator
			itrProperty = vProperties.begin();
			itrProperty != vProperties.end(); itrProperty++ ){
		
		const unsignedIntFib uiPropertytype = itrProperty->getPropertyType();
		
		if ( uiPropertytype == cTypeProperty::COLOR_RGB ){
			//RGB color:
			//color_new = color_actual * alpha_last + color_matrix * alpha_matrix * ( 1 - alpha_last )
			if ( bNoAlpha ){
				//no transparency -> transparency = 0 -> alpha = 1
				pColorValue->rgbReserved = 255;
				bNoAlpha = false;
			}
			const float fAlphaMatrix = ((float)(pColorValue->rgbReserved)) / 255.0;
			
			//red
			const longFib lColorR = fib::roundToLongFib(
				itrProperty->getValue( 1 ) );
			const float fColorR = ( lColorR <= 0 ) ? 0 :
				( 255 <= lColorR ) ? 255 : lColorR;
			
			pColorValue->rgbRed = fColorR * fLastAlpha +
				((float)(pColorValue->rgbRed)) * fAlphaMatrix * ( 1.0 - fLastAlpha );
			
			//green
			const longFib lColorG = fib::roundToLongFib(
				itrProperty->getValue( 2 ) );
			const float fColorG = ( lColorG <= 0 ) ? 0 :
				( 255 <= lColorG ) ? 255 : lColorG;
			
			pColorValue->rgbGreen = fColorG * fLastAlpha +
				((float)(pColorValue->rgbGreen)) * fAlphaMatrix * ( 1.0 - fLastAlpha );
			
			//blue
			const longFib lColorB = fib::roundToLongFib(
				itrProperty->getValue( 3 ) );
			const float fColorB = ( lColorB <= 0 ) ? 0 :
				( 255 <= lColorB ) ? 255 : lColorB;
			
			pColorValue->rgbBlue = fColorB * fLastAlpha +
				((float)(pColorValue->rgbBlue)) * fAlphaMatrix * ( 1.0 - fLastAlpha );
			
		}else if ( uiPropertytype == cTypeProperty::COLOR_GRAYSCALE ){
			//RGB color:
			//color_new = color_actual * alpha_last + color_matrix * alpha_matrix * ( 1 - alpha_last )
			if ( bNoAlpha ){
				//no transparency -> transparency = 0 -> alpha = 1
				pColorValue->rgbReserved = 255;
				bNoAlpha = false;
			}
			const float fAlphaMatrix = ((float)(pColorValue->rgbReserved)) / 255.0;
		//TODO how to set grayscale color?
			//red
			const longFib lColorSW = fib::roundToLongFib(
				itrProperty->getValue( 1 ) );
			const float fColorSW = ( lColorSW <= 0 ) ? 0 :
				( 255 <= lColorSW ) ? 255 : lColorSW;
			
			pColorValue->rgbRed = fColorSW * fLastAlpha +
				((float)(pColorValue->rgbRed)) * fAlphaMatrix * ( 1.0 - fLastAlpha );
			
			pColorValue->rgbGreen = pColorValue->rgbRed ;
			pColorValue->rgbBlue = pColorValue->rgbRed ;
			
		}else if ( uiPropertytype == cTypeProperty::TRANSPARENCY ){
			//transparency
			// alpha_new = alpha_matrix + alpha_new ( 1 - alpha_matrix )
			const longFib lTransparency = fib::roundToLongFib(
				itrProperty->getValue( 1 ) );
			//alpha_new = 255 - transparency;
			const unsigned int uiFoundAlpha = ( lTransparency <= 0 ) ? 255 :
				( 255 <= lTransparency ) ? 0 :
					(255 - lTransparency);
			fLastAlpha = ( lTransparency <= 0 ) ? 1.0 :
				( 255 <= lTransparency ) ? 0.0 :
					((float)(255 - lTransparency)) / 255.0;
			
			//const float fOldAlpha = ((float)(*pEntry)) / 255.0;
			//alpha_matrix_new = 255.0 * ( fLastAlpha + fOldAlpha * ( 1 - fLastAlpha ) );
			pColorValue->rgbReserved = uiFoundAlpha +
				((float)(pColorValue->rgbReserved)) * ( 1.0 - fLastAlpha );
			bNoAlpha = false;//transparency value set
		}//else discard property
		
	}//end for all properties for the point
	
	if ( 0 <= lX ){
		//normal point
		const bool bColorValueSet =
			pFipImageDataObject->setPixelColor( lX, lY, pColorValue );
		if ( ! bColorValueSet ){
			delete pColorValue;
			return false;
		}
	}else{//background point
		pFipImageDataObject->setFileBkColor( pColorValue );
	}
	
	delete pColorValue;
	return true;
}


/**
 * With this method the properties for given points are returned.
 *
 * @param vPosition the position of the point, for which the properties
 * 	should be returned
 * @return a list of the properties of the point
 */
list<cVectorProperty> cFreeImageData::getPointProperties(
		const cVectorPosition & vPosition ) const{
	
	RGBQUAD * pColorValue = new RGBQUAD();
	RGBQUAD * pColorPalette = pFipImageDataObject->getPalette();
	
	longFib lX = -1;
	longFib lY = -1;
	if ( vPosition.getNumberOfElements() != 0 ){
		//normal point
		//get the correct position
		lX = fib::roundToLongFib( vPosition.getValue( 1 ) );
		
		if ( ( lX < 0 ) || ( ((longFib)(pFipImageDataObject->getWidth())) <= lX ) ){
			//point not in image
			delete pColorValue;
			return list<cVectorProperty>();
		}
		lY = fib::roundToLongFib( vPosition.getValue( 2 ) );
		if ( ( lY < 0 ) || ( ((longFib)(pFipImageDataObject->getHeight())) <= lY ) ){
			//point not in image
			delete pColorValue;
			return list<cVectorProperty>();
		}
		//get color of pixle
		if ( pColorPalette == NULL ){
			const bool bColorValueEvalued =
				pFipImageDataObject->getPixelColor( lX, lY, pColorValue );
			if ( ! bColorValueEvalued ){
				delete pColorValue;
				return list<cVectorProperty>();
			}
		}else{//use color pallette
			BYTE * pIndexValue = new BYTE();
			const bool bColorValueEvalued =
				pFipImageDataObject->getPixelIndex( lX, lY, pIndexValue );
			
			if ( ( ! bColorValueEvalued ) ||
					( pFipImageDataObject->getPaletteSize() <= (*pIndexValue) ) ){
				delete pColorValue;
				delete pIndexValue;
				return list<cVectorProperty>();
			}
			(*pColorValue) = pColorPalette[ *pIndexValue ];
			delete pIndexValue;
		}
	}else{//background point
		const bool bColorValueEvalued =
			pFipImageDataObject->getFileBkColor( pColorValue );
		if ( ! bColorValueEvalued ){
			delete pColorValue;
			return list<cVectorProperty>();
		}
		
		if ( pColorPalette != NULL ){
			if ( pFipImageDataObject->getPaletteSize() <=
					(pColorValue->rgbReserved) ){
				delete pColorValue;
				return list<cVectorProperty>();
			}
			(*pColorValue) = pColorPalette[ pColorValue->rgbReserved ];
		}
	}
	//convert color values to Fib vectors
	list<cVectorProperty> liVecProperties;
	
	if ( pFipImageDataObject->isTransparent() ){
		//transparency exists -> convert transparency to property vector
		liVecProperties.push_back( cVectorProperty(
			cTypeProperty( cTypeProperty::TRANSPARENCY ) ) );
		
		liVecProperties.back().setValue( 1, pColorValue->rgbReserved );
	}
	
	//convert color to property vector
	const bool bSWColor = pFipImageDataObject->isGrayscale();
	if ( bSWColor ){
		//grayscale color
		liVecProperties.push_back( cVectorProperty(
			cTypeProperty( cTypeProperty::COLOR_GRAYSCALE ) ) );
		liVecProperties.back().setValue( 1, pColorValue->rgbRed );
	}else{//RGB color
		liVecProperties.push_back( cVectorProperty(
			cTypeProperty( cTypeProperty::COLOR_RGB ) ) );
		cVectorProperty & vecColorRGB = liVecProperties.back();
		vecColorRGB.setValue( 1, pColorValue->rgbRed );
		vecColorRGB.setValue( 2, pColorValue->rgbGreen );
		vecColorRGB.setValue( 3, pColorValue->rgbBlue );
	}
	
	return liVecProperties;
}


/**
 * This method clears the data from the list with the evalued position data
 * liEvaluedPositionData.
 * After the function call the liEvaluedPositionData list will be empty.
 *
 * @see liEvaluedPositionData
 */
void cFreeImageData::clear(){
	
	pFipImageDataObject->unload();
}



/**
 * With this method the value for a matrix element is set.
 *
 * @param dValue the value to set
 * @param uiPositionX the index on the first (x) dimension where to set
 * 	the value dValue
 * @param uiPositionY the index on the second (y) dimension where to set
 * 	the value dValue
 * @param uiChanel the index for the property chanel;
 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
 * @return OK (or 0) if the value could be set, else the error value
 * 	@see tErrorValue
 */
iMatrix3D::tErrorValue cFreeImageData::setValue( const doubleFib dValue,
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiChanel ){
	
	return setValue( roundToLongFib( dValue ),
		uiPositionX, uiPositionY, uiChanel );
}


/**
 * With this method a integer value for a matrix element is set.
 *
 * @param lValue the value to set
 * @param uiPositionX the index on the first (x) dimension where to set
 * 	the value dValue
 * @param uiPositionY the index on the second (y) dimension where to set
 * 	the value dValue
 * @param uiChanel the index for the property chanel;
 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
 * @return OK (or 0) if the value could be set, else the error value
 * 	@see tErrorValue
 */
iMatrix3D::tErrorValue cFreeImageData::setValue( const longFib lValue,
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiChanel ){
	
	//check if position inside borders
	if ( ( uiPositionX < 0 ) ||
			( ((longFib)(pFipImageDataObject->getWidth())) <= uiPositionX ) ){
		//point not in image
		return ERROR_OUTSIDE_INDEX_DIMENSION_1;
	}
	if ( ( uiPositionY < 0 ) ||
			( ((longFib)(pFipImageDataObject->getHeight())) <= uiPositionY ) ){
		//point not in image
		return ERROR_OUTSIDE_INDEX_DIMENSION_2;
	}
	if ( 3 < uiChanel ){
		//no such property chanel
		return ERROR_OUTSIDE_INDEX_DIMENSION_3;
	}
	if ( lValue < 0 ){
		//value outside range
		return ERROR_LOWER_MIN_VALUE;
	}
	if ( 255 < lValue ){
		//value outside range
		return ERROR_GREATER_MAX_VALUE;
	}
	RGBQUAD * pColorValue = new RGBQUAD();
	
	RGBQUAD * pColorPalette = pFipImageDataObject->getPalette();
	if ( pColorPalette == NULL ){
		const bool bColorValueEvalued =
			pFipImageDataObject->getPixelColor( uiPositionX, uiPositionY, pColorValue );
		if ( ! bColorValueEvalued ){
			delete pColorValue;
			return ERROR;
		}
	}else{//use color pallette
		BYTE * pIndexValue = new BYTE();
		const bool bColorValueEvalued =
			pFipImageDataObject->getPixelIndex( uiPositionX, uiPositionY, pIndexValue );
		
		if ( ( ! bColorValueEvalued ) ||
				( pFipImageDataObject->getPaletteSize() <= (*pIndexValue) ) ){
			delete pColorValue;
			delete pIndexValue;
			return ERROR;
		}
		(*pColorValue) = pColorPalette[ *pIndexValue ];
		delete pIndexValue;
	}
	if ( uiChanel == 0 ){
		//chanel 0 -> set alpha value
		pColorValue->rgbReserved = lValue;
	}else if ( uiChanel == 1 ){
		//chanel 1 -> set red color value
		pColorValue->rgbRed = lValue;
	}else if ( uiChanel == 2 ){
		//chanel 1 -> set green color value
		pColorValue->rgbGreen = lValue;
	}else if ( uiChanel == 3 ){
		//chanel 1 -> set blue color value
		pColorValue->rgbBlue = lValue;
	}
	const bool bColorValueSet =
		pFipImageDataObject->setPixelColor( uiPositionX, uiPositionY, pColorValue );
	if ( ! bColorValueSet ){
		delete pColorValue;
		return ERROR;
	}
	delete pColorValue;
	
	return OK;
}


/**
 * With this method the value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the value
 * @param uiChanel the index for the property chanel;
 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
 * @return the value of the given position in the matrix
 */
doubleFib cFreeImageData::getValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	
	return ((doubleFib)getValueUInt( uiPositionX, uiPositionY, uiChanel ) );
}


/**
 * With this method the value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the value
 * @param uiChanel the index for the property chanel;
 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
 * @return the value of the given position in the matrix
 */
unsigned int cFreeImageData::getValueUInt( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	
	//check if position inside borders
	if ( ((unsigned int)(pFipImageDataObject->getWidth())) <= uiPositionX ){
		//point not in image
		return 0;
	}
	if ( ((unsigned int)(pFipImageDataObject->getHeight())) <= uiPositionY ){
		//point not in image
		return 0;
	}
	if ( 3 < uiChanel ){
		//no such property chanel
		return 0;
	}
	RGBQUAD * pColorValue = new RGBQUAD();
	
	RGBQUAD * pColorPalette = pFipImageDataObject->getPalette();
	if ( pColorPalette == NULL ){
		const bool bColorValueEvalued =
			pFipImageDataObject->getPixelColor( uiPositionX, uiPositionY, pColorValue );
		if ( ! bColorValueEvalued ){
			delete pColorValue;
			return 0;
		}
	}else{//use color pallette
		BYTE * pIndexValue = new BYTE();
		const bool bColorValueEvalued =
			pFipImageDataObject->getPixelIndex( uiPositionX, uiPositionY, pIndexValue );
		
		if ( ( ! bColorValueEvalued ) ||
				( pFipImageDataObject->getPaletteSize() <= (*pIndexValue) ) ){
			delete pColorValue;
			delete pIndexValue;
			return 0;
		}
		(*pColorValue) = pColorPalette[ *pIndexValue ];
		delete pIndexValue;
	}
	unsigned int uiValue = 0;
	if ( uiChanel == 0 ){
		//chanel 0 -> set alpha value
		uiValue = pColorValue->rgbReserved;
	}else if ( uiChanel == 1 ){
		//chanel 1 -> set red color value
		uiValue = pColorValue->rgbRed;
	}else if ( uiChanel == 2 ){
		//chanel 1 -> set green color value
		uiValue = pColorValue->rgbGreen;
	}else if ( uiChanel == 3 ){
		//chanel 1 -> set blue color value
		uiValue = pColorValue->rgbBlue;
	}
	delete pColorValue;
	
	return uiValue;
}


/**
 * With this method the minimum value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the minimum value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the minimum value
 * @param uiPositionZ the index on the third (z) dimension of which to
 * 	return the minimum value
 * @return the minimum value of the given position in the matrix
 */
doubleFib cFreeImageData::getMinValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	
	return 0.0;
}


/**
 * With this method the minimum integer value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the minimum value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the minimum value
 * @param uiPositionZ the index on the third (z) dimension of which to
 * 	return the minimum value
 * @return the minimum integer value of the given position in the matrix
 */
unsigned int cFreeImageData::getMinValueUInt( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	
	return 0;
}


/**
 * With this method the maximum value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the maximum value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the maximum value
 * @param uiPositionZ the index on the third (z) dimension of which to
 * 	return the maximum value
 * @return the maximum value of the given position in the matrix
 */
doubleFib cFreeImageData::getMaxValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	
	if ( uiChanel < 4 ){
		//TODO adapt for other color depths
		return 255.0;
	}
	return 0.0;
}


/**
 * With this method the maximum integer value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the maximum value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the maximum value
 * @param uiPositionZ the index on the third (z) dimension of which to
 * 	return the maximum value
 * @return the maximum integer value of the given position in the matrix
 */
unsigned int cFreeImageData::getMaxValueUInt( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	
	if ( uiChanel < 4 ){
		//TODO adapt for other color depths
		return 255;
	}
	return 0;
}


/**
 * With this method the minimal difference betwean two values for the
 * matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the minimal difference value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the minimal difference value
 * @param uiChanel the index on the third (z) dimension of which to
 * 	return the minimal difference value
 * @return the minimal difference betwean two values for the
 * 	matrix element
 */
doubleFib cFreeImageData::getMinDifference( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	
	if ( uiChanel < 4 ){
		return 1.0;
	}
	return 0.0;
}


/**
 * This method returns the maximum index value of the given direction/
 * dimension.
 * All index values for the direction uiDirection should be natural
 * numbers betwean (including) 0 and the returned value.
 *
 * @param uiDirection the direction for which the maximum value should
 * 	be returned (possible values are 0 to 2)
 * @return the maximum index value for the direction uiDirection
 */
unsigned int cFreeImageData::getMaxIndex( const unsigned int uiDirection ) const{
	
	if ( 2 < uiDirection ){
		//no such direction
		return 0;
	}//else
	if ( uiDirection == 0 ){
		return ((unsigned int)(pFipImageDataObject->getWidth()));
	}//else
	if ( uiDirection == 1 ){
		return ((unsigned int)(pFipImageDataObject->getHeight()));
	}//else
	if ( uiDirection == 2 ){
		//4 submatrixs RGBA
		return 3;
	}//else
	//no such dimension -> maximal index 0
	return 0;
}


/**
 * This method checks if the given matrix is equal to this matrix.
 *
 * @param matrix the matrix, which should be equal to this matrix
 * @return true if the given matrix is equal to this matrix, else false
 */
bool cFreeImageData::equal( const iMatrix3D &matrix ) const{
	
	if ( getName() != matrix.getName() ){
		//matrix not of same type (class) ->  matrix not equal
		return false;
	}//else
	//compare matrix size
	const unsigned int uiMaxIndexX = getMaxIndex( 0 );
	const unsigned int uiMaxIndexY = getMaxIndex( 1 );
	const unsigned int uiMaxIndexZ = getMaxIndex( 2 );
	
	if ( matrix.getMaxIndex( 0 ) != uiMaxIndexX ){
		//size in dimension 1 not equal -> matrix not equal
		return false;
	}//else
	if ( matrix.getMaxIndex( 1 ) != uiMaxIndexY ){
		//size in dimension 2 not equal -> matrix not equal
		return false;
	}//else
	if ( matrix.getMaxIndex( 2 ) != uiMaxIndexZ ){
		//size in dimension 3 not equal -> matrix not equal
		return false;
	}//else
	cFreeImageData * pFreeImageMatrix = ((cFreeImageData*)&matrix);
	//compare matrix entries
	for ( unsigned int uiIndexX = 0; uiIndexX <= uiMaxIndexX; uiIndexX++ ){
		for ( unsigned int uiIndexY = 0; uiIndexY <= uiMaxIndexY; uiIndexY++ ){
			for ( unsigned int uiIndexZ = 0; uiIndexZ <= uiMaxIndexZ; uiIndexZ++ ){
				
				if ( getValueUInt( uiMaxIndexX, uiIndexY, uiIndexZ ) !=
						pFreeImageMatrix->getValueUInt( uiMaxIndexX, uiIndexY, uiIndexZ ) ){
					//entry not equal -> matrix not equal
					return false;
				}
			}//end for index in dimension 3 (z)
		}//end for index in dimension 2 (y)
	}//end for index in dimension 1 (x)
	//matrix equal
	return true;
}


/**
 * This method evalues the derivate of the matrix in the given
 * direction / dimension.
 *
 * @param uiDirection the direction in which the derivation should
 * 	be evalued (possible values are 0 to 2)
 * @return a pointer to the derivate matrix in the given direction of
 * 	this matrix, or NULL if non exists
 * 	Beware: You have to care that the returnd object is deleted.
 */
iMatrix3D * cFreeImageData::evalueDerivate(
		const unsigned int uiDirection ) const{
	
	if ( 2 < uiDirection ){
		//no such property
		return NULL;
	}
	//get matrix size
	const unsigned int uiMaxIndexX = getMaxIndex( 0 );
	const unsigned int uiMaxIndexY = getMaxIndex( 1 );
	const unsigned int uiMaxIndexZ = getMaxIndex( 2 );
	//TODO adapt
	const unsigned int uiBitsPerDerivateEntry = 9;
	
	cMatrix3DInteger * pDerivateMatrix = NULL;
	if ( uiDirection == 0 ){
		//evalue derivation in first (1. or x) dimension
		if ( uiMaxIndexX < 1 ){
			//just one line in dimension 1 -> can't evalue derivate
			return NULL;
		}
		const unsigned int uiMaxIndexDimX = uiMaxIndexX - 1;
		
		pDerivateMatrix = new cMatrix3DInteger( uiMaxIndexDimX,
			uiMaxIndexY, uiMaxIndexZ, uiBitsPerDerivateEntry );
	
		//compare matrix entries
		for ( unsigned int uiIndexX = 0; uiIndexX <= uiMaxIndexDimX; uiIndexX++ ){
			for ( unsigned int uiIndexY = 0; uiIndexY <= uiMaxIndexY; uiIndexY++ ){
				for ( unsigned int uiIndexZ = 0; uiIndexZ <= uiMaxIndexZ; uiIndexZ++ ){
					
					const longFib lDerivateValue =
						getValueUInt( uiMaxIndexX + 1, uiIndexY, uiIndexZ ) -
						getValueUInt( uiMaxIndexX, uiIndexY, uiIndexZ );
					pDerivateMatrix->setValue( lDerivateValue,
						uiMaxIndexX, uiIndexY, uiIndexZ );
				}//end for index in dimension 3 (z)
			}//end for index in dimension 2 (y)
		}//end for index in dimension 1 (x)
		
	}else if ( uiDirection == 1 ){
		//evalue derivation in second (2. or y) dimension
		if ( uiMaxIndexY < 1 ){
			//just one line in dimension 2 -> can't evalue derivate
			return NULL;
		}
		const unsigned int uiMaxIndexDimY = uiMaxIndexY - 1;
		
		pDerivateMatrix = new cMatrix3DInteger( uiMaxIndexX,
			uiMaxIndexDimY, uiMaxIndexZ, uiBitsPerDerivateEntry );
	
		//compare matrix entries
		for ( unsigned int uiIndexX = 0; uiIndexX <= uiMaxIndexX; uiIndexX++ ){
			for ( unsigned int uiIndexY = 0; uiIndexY <= uiMaxIndexDimY; uiIndexY++ ){
				for ( unsigned int uiIndexZ = 0; uiIndexZ <= uiMaxIndexZ; uiIndexZ++ ){
					
					const longFib lDerivateValue =
						getValueUInt( uiMaxIndexX, uiIndexY + 1, uiIndexZ ) -
						getValueUInt( uiMaxIndexX, uiIndexY, uiIndexZ );
					pDerivateMatrix->setValue( lDerivateValue,
						uiMaxIndexX, uiIndexY, uiIndexZ );
				}//end for index in dimension 3 (z)
			}//end for index in dimension 2 (y)
		}//end for index in dimension 1 (x)
		
	}else if ( uiDirection == 2 ){
		//evalue derivation in third (3. or y) dimension
		if ( uiMaxIndexZ < 1 ){
			//just one line in dimension 3 -> can't evalue derivate
			return NULL;
		}
		const unsigned int uiMaxIndexDimZ = uiMaxIndexZ - 1;
		
		pDerivateMatrix = new cMatrix3DInteger( uiMaxIndexX,
			uiMaxIndexY, uiMaxIndexDimZ, uiBitsPerDerivateEntry );
	
		//compare matrix entries
		for ( unsigned int uiIndexX = 0; uiIndexX <= uiMaxIndexX; uiIndexX++ ){
			for ( unsigned int uiIndexY = 0; uiIndexY <= uiMaxIndexY; uiIndexY++ ){
				for ( unsigned int uiIndexZ = 0; uiIndexZ <= uiMaxIndexDimZ; uiIndexZ++ ){
					
					const longFib lDerivateValue =
						getValueUInt( uiMaxIndexX, uiIndexY, uiIndexZ + 1 ) -
						getValueUInt( uiMaxIndexX, uiIndexY, uiIndexZ );
					pDerivateMatrix->setValue( lDerivateValue,
						uiMaxIndexX, uiIndexY, uiIndexZ );
				}//end for index in dimension 3 (z)
			}//end for index in dimension 2 (y)
		}//end for index in dimension 1 (x)
		
	}
	return pDerivateMatrix;
}



/**
 * This method evalues the difference of two points properties.
 * This difference is the sum of the difference of the property
 * vectors elements or the sum of the distance betwean the third dimension
 * elements on the given positions.
 *
 * @param vPosition1 the first point for the first property vector
 * @param vPosition2 the second point for the second property vector
 * @return the sum of distances betwean the vector elements of the
 * 	properties of the first and second point
 */
doubleFib cFreeImageData::getDifference(
		const cVectorPosition & vPosition1,
		const cVectorPosition & vPosition2 ) const{
	
	const longFib lPosition1X = fib::roundToLongFib(
		vPosition1.getValue( 1 ) );
	const longFib lPosition1Y = fib::roundToLongFib(
		vPosition1.getValue( 2 ) );
	const longFib lPosition2X = fib::roundToLongFib(
		vPosition2.getValue( 1 ) );
	const longFib lPosition2Y = fib::roundToLongFib(
		vPosition2.getValue( 2 ) );
	
	if ( ( lPosition1X < 0 ) || ( lPosition1Y < 0 ) ||
			( lPosition2X < 0 ) || ( lPosition2Y < 0 ) ){
		//index (position) invalid (negativ)
		return 0.0;
	}
	return getDifference( lPosition1X, lPosition1Y,
			lPosition2X, lPosition2Y );
}


/**
 * This method evalues the difference of two points properties.
 * This difference is the sum of the difference of the property
 * vector elements or the sum of the distance betwean the third dimension
 * elements on the given positions.
 *
 * @param uiPositionX the index on the first (x) dimension of the first
 * 	point for the first property vector
 * @param uiPositionY the index on the second (y) dimension of the first
 * 	point for the first property vector
 * @param uiPositionX the index on the first (x) dimension of the second
 * 	point for the second property vector
 * @param uiPositionY the index on the second (y) dimension of the second
 * 	point for the second property vector
 * @return the sum of distances betwean the vector elements of the
 * 	third dimension (properties) of the first and second point
 */
doubleFib cFreeImageData::getDifference(
		const unsigned int uiPosition1X, const unsigned int uiPosition1Y,
		const unsigned int uiPosition2X, const unsigned int uiPosition2Y )
			const{
	
	//check if position inside borders
	if ( ((longFib)(pFipImageDataObject->getWidth())) <= uiPosition1X ){
		//point not in image
		return 0.0;
	}
	if (  ((longFib)(pFipImageDataObject->getHeight())) <= uiPosition1Y ){
		//point not in image
		return 0.0;
	}
	if ( ((longFib)(pFipImageDataObject->getWidth())) <= uiPosition2X ){
		//point not in image
		return 0.0;
	}
	if (  ((longFib)(pFipImageDataObject->getHeight())) <= uiPosition2Y ){
		//point not in image
		return 0.0;
	}
	RGBQUAD * pColorValue1 = new RGBQUAD();
	
	RGBQUAD * pColorPalette = pFipImageDataObject->getPalette();
	if ( pColorPalette == NULL ){
		const bool bColorValueEvalued1 =
			pFipImageDataObject->getPixelColor( uiPosition1X, uiPosition1Y, pColorValue1 );
		if ( ! bColorValueEvalued1 ){
			delete pColorValue1;
			return 0.0;
		}
	}else{//use color pallette
		BYTE * pIndexValue = new BYTE();
		const bool bColorValueEvalued1 =
			pFipImageDataObject->getPixelIndex( uiPosition1X, uiPosition1Y, pIndexValue );
		
		if ( ( ! bColorValueEvalued1 ) ||
				( pFipImageDataObject->getPaletteSize() <= (*pIndexValue) ) ){
			delete pColorValue1;
			delete pIndexValue;
			return 0.0;
		}
		(*pColorValue1) = pColorPalette[ *pIndexValue ];
		delete pIndexValue;
	}
	RGBQUAD * pColorValue2 = new RGBQUAD();
	if ( pColorPalette == NULL ){
		const bool bColorValueEvalued2 =
			pFipImageDataObject->getPixelColor( uiPosition2X, uiPosition2Y, pColorValue2 );
		if ( ! bColorValueEvalued2 ){
			delete pColorValue1;
			delete pColorValue2;
			return 0.0;
		}
	}else{//use color pallette
		BYTE * pIndexValue = new BYTE();
		const bool bColorValueEvalued2 =
			pFipImageDataObject->getPixelIndex( uiPosition2X, uiPosition2Y, pIndexValue );
		
		if ( ( ! bColorValueEvalued2 ) ||
				( pFipImageDataObject->getPaletteSize() <= (*pIndexValue) ) ){
			delete pColorValue1;
			delete pColorValue2;
			delete pIndexValue;
			return 0.0;
		}
		(*pColorValue2) = pColorPalette[ *pIndexValue ];
		delete pIndexValue;
	}
	unsigned int uiDifference =
		( pColorValue1->rgbReserved < pColorValue2->rgbReserved ) ?
			( pColorValue2->rgbReserved - pColorValue1->rgbReserved ):
			( pColorValue1->rgbReserved - pColorValue2->rgbReserved );
	uiDifference +=
		( pColorValue1->rgbRed < pColorValue2->rgbRed ) ?
			( pColorValue2->rgbRed - pColorValue1->rgbRed ):
			( pColorValue1->rgbRed - pColorValue2->rgbRed );
	uiDifference +=
		( pColorValue1->rgbGreen < pColorValue2->rgbGreen ) ?
			( pColorValue2->rgbGreen - pColorValue1->rgbGreen ):
			( pColorValue1->rgbGreen - pColorValue2->rgbGreen );
	uiDifference +=
		( pColorValue1->rgbBlue < pColorValue2->rgbBlue ) ?
			( pColorValue2->rgbBlue - pColorValue1->rgbBlue ):
			( pColorValue1->rgbBlue - pColorValue2->rgbBlue );
	
	delete pColorValue1;
	delete pColorValue2;
	
	return ((doubleFib)uiDifference);
}


/**
 * This method returns the number of properties for the image position.
 * (The properties are given by the third dimension vector on the position.)
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the number of property vectors
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the number of property vectors
 * @return the number of property vectors for the given position
 */
unsigned int cFreeImageData::getNumberOfProperties(
		const unsigned int uiPositionX, const unsigned int uiPositionY ) const{
	
	return 2;
}


/**
 * @return true if the property types don't depend on the position of the
 * 	point, else false;
 * 	If true you can for example ignore the position parameters of:
 * 		@see getPropertyType()
 * 		@see getPropertyNumberForType()
 * 		@see getDimension3IndexesForPropertyType()
 */
bool cFreeImageData::isPropertyTypeIndependentOfPosition() const{
	
	return true;
}


/**
 * This method returns the indexes in the third dimension of the
 * property vector elements of the given type.
 * The returned vector elements are ordered like the property vector
 * elements. So the first property vector element has the index in
 * dimension 3 of the returned vector element with index 0 .
 * Example:
 * vector< unsigned int > vecPropertyTypeIndexes =
 * 	getDimension3IndexesForPropertyType( t ,x, y );
 * getValue( x, y, vecPropertyTypeIndexes[ 1 ] ) ==
 * 	getProperty( x, y, t ).getValue( 2 )
 * @see isPropertyTypeIndependentOfPosition
 *
 * @param uiPropertyType the type number of the property to return the
 * 	indexes of (e. g. cTypeProperty::COLOR_RGB )
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the property indexes
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the property indexes
 * @return the dimension 3 indexes of the property of the given type
 */
vector< unsigned int > cFreeImageData::getDimension3IndexesForPropertyType(
		const unsigned int uiPropertyType,
		const unsigned int uiPositionX, const unsigned int uiPositionY ) const{
	
	vector< unsigned int > vecPropertyTypeIndexes;
	if ( uiPropertyType == cTypeProperty::TRANSPARENCY ){
		//return transparency type indexes
		vecPropertyTypeIndexes.push_back( 0 );
	}else if ( uiPropertyType == cTypeProperty::COLOR_GRAYSCALE ){
		//return type of color
		const bool bSWColor = pFipImageDataObject->isGrayscale();
		if ( bSWColor ){
			//return grayscale color
			vecPropertyTypeIndexes.push_back( 1 );
		}//else no such property
	}else if ( uiPropertyType == cTypeProperty::COLOR_RGB ){
		//return type of color
		const bool bSWColor = pFipImageDataObject->isGrayscale();
		if ( ! bSWColor ){
			//return color RGB type
			vecPropertyTypeIndexes.push_back( 1 );
			vecPropertyTypeIndexes.push_back( 2 );
			vecPropertyTypeIndexes.push_back( 3 );
		}//else no such property
	}
	return vecPropertyTypeIndexes;
}


/**
 * This method returns the number of the uiPropertyNumber'th property
 * type for the image position.
 * (The properties are given by the third dimension vector on the position.)
 * @see cTypeProperty
 *
 * @param uiPropertyNumber the number of the property to return the type of;
 * 	counting starts with 1; @see getNumberOfProperties()
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the property type
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the property type
 * @return the number of the type of the uiPropertyNumber'th property
 * 	on the given position, or cTypeProperty::NONE if non exists
 * 	@see cTypeProperty
 */
unsigned int cFreeImageData::getPropertyType(
		const unsigned int uiPropertyNumber,
		const unsigned int uiPositionX, const unsigned int uiPositionY ) const{
	
	if ( uiPropertyNumber == 1 ){
		//return transparency type
		return cTypeProperty::TRANSPARENCY;
	}else if ( uiPropertyNumber == 2 ){
		//return type of color
		const bool bSWColor = pFipImageDataObject->isGrayscale();
		if ( bSWColor ){
			//return grayscale color
			return cTypeProperty::COLOR_GRAYSCALE;
		}else{
			//return color RGB type
			return cTypeProperty::COLOR_RGB;
		}
	}
	return cTypeProperty::NONE;
}


/**
 * This method returns the number for the given property type for the
 * image position.
 * @see cTypeProperty
 * @see getPropertyType()
 * @see getNumberOfProperties()
 *
 * @param uiPropertyType the type number of the property to return the
 * 	number of (e. g. cTypeProperty::COLOR_RGB )
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the property number
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the property number
 * @return the number for the given property type for the image position,
 * 	or 0 if no such property extists
 * 	@see cTypeProperty
 */
unsigned int cFreeImageData::getPropertyNumberForType(
		const unsigned int uiPropertyType,
		const unsigned int uiPositionX, const unsigned int uiPositionY ) const{
	
	if ( uiPropertyType == cTypeProperty::TRANSPARENCY ){
		//return transparency number
		return 1;
	}else if ( uiPropertyType == cTypeProperty::COLOR_RGB ){
		//check color type
		const bool bSWColor = pFipImageDataObject->isGrayscale();
		if ( bSWColor ){
			//return no RGB color
			return 0;
		}//else return color RGB number
		return 2;
	}else if ( uiPropertyType == cTypeProperty::COLOR_GRAYSCALE ){
		//check color type
		const bool bSWColor = pFipImageDataObject->isGrayscale();
		if ( bSWColor ){
			//return grayscale color
			return 2;
		}//else return no color RGB
		return 0;
	}//else no properties of such type
	return 0;
}


/**
 * This method evalues the difference of two points properties.
 * This difference is the sum of the difference of the property
 * vectors elements or the sum of the distance betwean the third dimension
 * elements on the given positions.
 *
 * @param vPosition1 the first point for the first property vector
 * @param vPosition2 the second point for the second property vector
 * @param uiPropertyType the type number of the property to return the
 * 	distances of (e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @return the sum of distances betwean the vector elements of the
 * 	properties of the first and second point
 */
doubleFib cFreeImageData::getDifference(
		const cVectorPosition & vPosition1,
		const cVectorPosition & vPosition2,
		const unsigned int uiPropertyType ) const{
	
	const longFib lPosition1X = fib::roundToLongFib(
		vPosition1.getValue( 1 ) );
	const longFib lPosition1Y = fib::roundToLongFib(
		vPosition1.getValue( 2 ) );
	const longFib lPosition2X = fib::roundToLongFib(
		vPosition2.getValue( 1 ) );
	const longFib lPosition2Y = fib::roundToLongFib(
		vPosition2.getValue( 2 ) );
	
	if ( ( lPosition1X < 0 ) || ( lPosition1Y < 0 ) ||
			( lPosition2X < 0 ) || ( lPosition2Y < 0 ) ){
		//index (position) invalid (negativ)
		return 0.0;
	}
	return getDifference( lPosition1X, lPosition1Y,
			lPosition2X, lPosition2Y, uiPropertyType );
}


/**
 * This method evalues the difference of two points properties.
 * This difference is the sum of the difference of the property
 * vector elements or the sum of the distance betwean the third dimension
 * elements on the given positions.
 *
 * @param uiPositionX the index on the first (x) dimension of the first
 * 	point for the first property vector
 * @param uiPositionY the index on the second (y) dimension of the first
 * 	point for the first property vector
 * @param uiPositionX the index on the first (x) dimension of the second
 * 	point for the second property vector
 * @param uiPositionY the index on the second (y) dimension of the second
 * 	point for the second property vector
 * @param uiPropertyType the type number of the property to return the
 * 	distances of (e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @return the sum of distances betwean the vector elements of the
 * 	third dimension values of the property of the first and second point
 */
doubleFib cFreeImageData::getDifference(
		const unsigned int uiPosition1X, const unsigned int uiPosition1Y,
		const unsigned int uiPosition2X, const unsigned int uiPosition2Y,
		const unsigned int uiPropertyType )
			const{
	
	//check if position inside borders
	if ( ( ((unsigned int)(pFipImageDataObject->getWidth())) <= uiPosition1X ) ||
			( ((unsigned int)(pFipImageDataObject->getHeight())) <= uiPosition1Y ) ||
			( ((unsigned int)(pFipImageDataObject->getWidth())) <= uiPosition2X ) ||
			( ((unsigned int)(pFipImageDataObject->getHeight())) <= uiPosition2Y ) ){
		//point not in image
		return 0.0;
	}
	if ( ( uiPropertyType != cTypeProperty::TRANSPARENCY ) &&
			( uiPropertyType != cTypeProperty::COLOR_GRAYSCALE ) &&
			( uiPropertyType != cTypeProperty::COLOR_RGB ) ){
		//not a valid property
		return 0.0;
	}
	if ( uiPropertyType == cTypeProperty::COLOR_GRAYSCALE ){
		//check if image is grayscale
		const bool bSWColor = pFipImageDataObject->isGrayscale();
		if ( ! bSWColor ){
			//not a valid property
			return 0.0;
		}
	}
	if ( uiPropertyType == cTypeProperty::COLOR_RGB ){
		//check if image is RGB color
		const bool bSWColor = pFipImageDataObject->isGrayscale();
		if ( bSWColor ){
			//not a valid property
			return 0.0;
		}
	}
	
	RGBQUAD * pColorValue1 = new RGBQUAD();
	
	RGBQUAD * pColorPalette = pFipImageDataObject->getPalette();
	if ( pColorPalette == NULL ){
		const bool bColorValueEvalued1 =
			pFipImageDataObject->getPixelColor( uiPosition1X, uiPosition1Y, pColorValue1 );
		if ( ! bColorValueEvalued1 ){
			delete pColorValue1;
			return 0.0;
		}
	}else{//use color pallette
		BYTE * pIndexValue = new BYTE();
		const bool bColorValueEvalued =
			pFipImageDataObject->getPixelIndex( uiPosition1X, uiPosition1Y, pIndexValue );
		
		if ( ( ! bColorValueEvalued ) ||
				( pFipImageDataObject->getPaletteSize() <= (*pIndexValue) ) ){
			delete pColorValue1;
			delete pIndexValue;
			return 0.0;
		}
		(*pColorValue1) = pColorPalette[ *pIndexValue ];
		delete pIndexValue;
	}
	RGBQUAD * pColorValue2 = new RGBQUAD();
	if ( pColorPalette == NULL ){
		const bool bColorValueEvalued2 =
			pFipImageDataObject->getPixelColor( uiPosition2X, uiPosition2Y, pColorValue2 );
		if ( ! bColorValueEvalued2 ){
			delete pColorValue1;
			delete pColorValue2;
			return 0.0;
		}
	}else{//use color pallette
		BYTE * pIndexValue = new BYTE();
		const bool bColorValueEvalued =
			pFipImageDataObject->getPixelIndex( uiPosition2X, uiPosition2Y, pIndexValue );
		
		if ( ( ! bColorValueEvalued ) ||
				( pFipImageDataObject->getPaletteSize() <= (*pIndexValue) ) ){
			delete pColorValue1;
			delete pColorValue2;
			delete pIndexValue;
			return 0.0;
		}
		(*pColorValue2) = pColorPalette[ *pIndexValue ];
		delete pIndexValue;
	}
	
	if ( uiPropertyType == cTypeProperty::TRANSPARENCY ){
		const unsigned int uiDifference =
			( pColorValue1->rgbReserved < pColorValue2->rgbReserved ) ?
			( pColorValue2->rgbReserved - pColorValue1->rgbReserved ):
			( pColorValue1->rgbReserved - pColorValue2->rgbReserved );
		delete pColorValue1;
		delete pColorValue2;
		return ((doubleFib)uiDifference);
	}else if ( uiPropertyType == cTypeProperty::COLOR_GRAYSCALE ){
		unsigned int uiDifference =
			( pColorValue1->rgbRed < pColorValue2->rgbRed ) ?
				( pColorValue2->rgbRed - pColorValue1->rgbRed ):
				( pColorValue1->rgbRed - pColorValue2->rgbRed );
		
		delete pColorValue1;
		delete pColorValue2;
		return ((doubleFib)uiDifference);
	}else if ( uiPropertyType == cTypeProperty::COLOR_RGB ){
		unsigned int uiDifference =
			( pColorValue1->rgbRed < pColorValue2->rgbRed ) ?
				( pColorValue2->rgbRed - pColorValue1->rgbRed ):
				( pColorValue1->rgbRed - pColorValue2->rgbRed );
		uiDifference +=
			( pColorValue1->rgbGreen < pColorValue2->rgbGreen ) ?
				( pColorValue2->rgbGreen - pColorValue1->rgbGreen ):
				( pColorValue1->rgbGreen - pColorValue2->rgbGreen );
		uiDifference +=
			( pColorValue1->rgbBlue < pColorValue2->rgbBlue ) ?
				( pColorValue2->rgbBlue - pColorValue1->rgbBlue ):
				( pColorValue1->rgbBlue - pColorValue2->rgbBlue );
		
		delete pColorValue1;
		delete pColorValue2;
		return ((doubleFib)uiDifference);
	}
	//no such property
	delete pColorValue1;
	delete pColorValue2;
	return 0.0;
}



/**
 * This method returns the property of the given type for the image
 * position.
 * (The properties are given by the third dimension vector on the position.)
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the property vector
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the property vector
 * @param uiPropertyType the type number of the property to return
 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @return the property for the given type uiPropertyType from the given
 * 	position or the property of type cTypeProperty::NONE if non exists
 */
cVectorProperty cFreeImageData::getProperty(
		const cVectorPosition & vPosition,
		const unsigned int uiPropertyType ) const{
	
	RGBQUAD * pColorValue = new RGBQUAD();
	RGBQUAD * pColorPalette = pFipImageDataObject->getPalette();
	
	longFib lX = -1;
	longFib lY = -1;
	if ( vPosition.getNumberOfElements() != 0 ){
		//normal point
		//get the correct position
		lX = fib::roundToLongFib( vPosition.getValue( 1 ) );
		
		if ( ( lX < 0 ) || ( ((longFib)(pFipImageDataObject->getWidth())) <= lX ) ){
			//point not in image
			delete pColorValue;
			return cVectorProperty( cTypeProperty::NONE );
		}
		lY = fib::roundToLongFib( vPosition.getValue( 2 ) );
		if ( ( lY < 0 ) || ( ((longFib)(pFipImageDataObject->getHeight())) <= lY ) ){
			//point not in image
			delete pColorValue;
			return cVectorProperty( cTypeProperty::NONE );
		}
		if ( pColorPalette == NULL ){
			const bool bColorValueEvalued =
				pFipImageDataObject->getPixelColor( lX, lY, pColorValue );
			if ( ! bColorValueEvalued ){
				delete pColorValue;
				return cVectorProperty( cTypeProperty::NONE );
			}
		}else{//use color pallette
			BYTE * pIndexValue = new BYTE();
			const bool bColorValueEvalued =
				pFipImageDataObject->getPixelIndex( lX, lY, pIndexValue );
			
			if ( ( ! bColorValueEvalued ) ||
					( pFipImageDataObject->getPaletteSize() <= (*pIndexValue) ) ){
				delete pColorValue;
				delete pIndexValue;
				return cVectorProperty( cTypeProperty::NONE );
			}
			(*pColorValue) = pColorPalette[ *pIndexValue ];
			delete pIndexValue;
		}
	}else{//background point
		const bool bColorValueEvalued =
			pFipImageDataObject->getFileBkColor( pColorValue );
		if ( ! bColorValueEvalued ){
			delete pColorValue;
			return cVectorProperty( cTypeProperty::NONE );
		}
		
		if ( pColorPalette != NULL ){
			if ( pFipImageDataObject->getPaletteSize() <=
					(pColorValue->rgbReserved) ){
				delete pColorValue;
				return cVectorProperty( cTypeProperty::NONE );
			}
			(*pColorValue) = pColorPalette[ pColorValue->rgbReserved ];
		}
	}
	//convert color values to Fib vectors
	
	if ( uiPropertyType == cTypeProperty::TRANSPARENCY ){
		if ( pFipImageDataObject->isTransparent() ){
			//transparency exists -> convert transparency to property vector
			cVectorProperty vecTransparency( cTypeProperty::TRANSPARENCY );
			vecTransparency.setValue( 1, pColorValue->rgbReserved );
			delete pColorValue;
			return vecTransparency;
		}
	}else if ( uiPropertyType == cTypeProperty::COLOR_GRAYSCALE ){
		//convert color to property vector
		const bool bSWColor = pFipImageDataObject->isGrayscale();
		if ( bSWColor ){
			//grayscale color
			cVectorProperty vecColorGrayscale( cTypeProperty::COLOR_GRAYSCALE );
			vecColorGrayscale.setValue( 1, pColorValue->rgbRed );
			delete pColorValue;
			return vecColorGrayscale;
		}//RGB color in image but grayscale color to return
	}else if ( uiPropertyType == cTypeProperty::COLOR_RGB ){
		//convert color to property vector
		const bool bSWColor = pFipImageDataObject->isGrayscale();
		if ( ! bSWColor ){//RGB color
			cVectorProperty vecColorRGB( cTypeProperty::COLOR_RGB );
			vecColorRGB.setValue( 1, pColorValue->rgbRed );
			vecColorRGB.setValue( 2, pColorValue->rgbGreen );
			vecColorRGB.setValue( 3, pColorValue->rgbBlue );
			delete pColorValue;
			return vecColorRGB;
		}//grayscale color in image but RGB color to return
	}
	delete pColorValue;
	return cVectorProperty( cTypeProperty::NONE );
}


/**
 * This method returns the property of the given type for the image
 * position.
 * (The properties are given by the third dimension vector on the position.)
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the property vector
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the property vector
 * @param uiPropertyType the type number of the property to return
 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @return the property for the given type uiPropertyType from the given
 * 	position or the property of type cTypeProperty::NONE if non exists
 */
cVectorProperty cFreeImageData::getProperty(
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiPropertyType ) const{
	
	//normal point
	//get the correct position
	if ( ( ((unsigned int)(pFipImageDataObject->getWidth())) <= uiPositionX ) ||
			( ((unsigned int)(pFipImageDataObject->getHeight())) <= uiPositionY ) ){
		//point not in image
		return cVectorProperty( cTypeProperty::NONE );
	}
	RGBQUAD * pColorValue = new RGBQUAD();
	RGBQUAD * pColorPalette = pFipImageDataObject->getPalette();
	if ( pColorPalette == NULL ){
		const bool bColorValueEvalued =
			pFipImageDataObject->getPixelColor( uiPositionX, uiPositionY, pColorValue );
		if ( ! bColorValueEvalued ){
			delete pColorValue;
			return cVectorProperty( cTypeProperty::NONE );
		}
	}else{//use color pallette
		BYTE * pIndexValue = new BYTE();
		const bool bColorValueEvalued =
			pFipImageDataObject->getPixelIndex( uiPositionX, uiPositionY, pIndexValue );
		
		if ( ( ! bColorValueEvalued ) ||
				( pFipImageDataObject->getPaletteSize() <= (*pIndexValue) ) ){
			delete pColorValue;
			delete pIndexValue;
			return cVectorProperty( cTypeProperty::NONE );
		}
		(*pColorValue) = pColorPalette[ *pIndexValue ];
		delete pIndexValue;
	}
	//convert color values to Fib vectors
	
	if ( uiPropertyType == cTypeProperty::TRANSPARENCY ){
		if ( pFipImageDataObject->isTransparent() ){
			//transparency exists -> convert transparency to property vector
			cVectorProperty vecTransparency( cTypeProperty::TRANSPARENCY );
			vecTransparency.setValue( 1, pColorValue->rgbReserved );
			delete pColorValue;
			return vecTransparency;
		}
	}else if ( uiPropertyType == cTypeProperty::COLOR_GRAYSCALE ){
		//convert color to property vector
		const bool bSWColor = pFipImageDataObject->isGrayscale();
		if ( bSWColor ){
			//grayscale color
			cVectorProperty vecColorGrayscale( cTypeProperty::COLOR_GRAYSCALE );
			vecColorGrayscale.setValue( 1, pColorValue->rgbRed );
			delete pColorValue;
			return vecColorGrayscale;
		}//RGB color in image but grayscale color to return
	}else if ( uiPropertyType == cTypeProperty::COLOR_RGB ){
		//convert color to property vector
		const bool bSWColor = pFipImageDataObject->isGrayscale();
		if ( ! bSWColor ){//RGB color
			cVectorProperty vecColorRGB( cTypeProperty::COLOR_RGB );
			vecColorRGB.setValue( 1, pColorValue->rgbRed );
			vecColorRGB.setValue( 2, pColorValue->rgbGreen );
			vecColorRGB.setValue( 3, pColorValue->rgbBlue );
			delete pColorValue;
			return vecColorRGB;
		}//grayscale color in image but RGB color to return
	}
	delete pColorValue;
	return cVectorProperty( cTypeProperty::NONE );
}


/**
 * This method returns the uiPropertyNumber'th property for the image
 * position.
 * (The properties are given by the third dimension vector on the position.)
 *
 * @param vPosition the position of which to return the property vector
 * @param uiPropertyNumber the number of the property to return;
 * 	counting starts with 1; @see getNumberOfProperties()
 * @return the uiPropertyNumber'th property from the given position or the
 * 	property of type cTypeProperty::NONE if non exists
 */
cVectorProperty cFreeImageData::getPropertyForNumber(
		const cVectorPosition & vPosition,
		const unsigned int uiPropertyNumber ) const{
	
	RGBQUAD * pColorValue = new RGBQUAD();
	RGBQUAD * pColorPalette = pFipImageDataObject->getPalette();
	
	longFib lX = -1;
	longFib lY = -1;
	if ( vPosition.getNumberOfElements() != 0 ){
		//normal point
		//get the correct position
		lX = fib::roundToLongFib( vPosition.getValue( 1 ) );
		
		if ( ( lX < 0 ) || ( ((longFib)(pFipImageDataObject->getWidth())) <= lX ) ){
			//point not in image
			delete pColorValue;
			return cVectorProperty( cTypeProperty::NONE );
		}
		lY = fib::roundToLongFib( vPosition.getValue( 2 ) );
		if ( ( lY < 0 ) || ( ((longFib)(pFipImageDataObject->getHeight())) <= lY ) ){
			//point not in image
			delete pColorValue;
			return cVectorProperty( cTypeProperty::NONE );
		}
		if ( pColorPalette == NULL ){
			const bool bColorValueEvalued =
				pFipImageDataObject->getPixelColor( lX, lY, pColorValue );
			if ( ! bColorValueEvalued ){
				delete pColorValue;
				return cVectorProperty( cTypeProperty::NONE );
			}
		}else{//use color pallette
			BYTE * pIndexValue = new BYTE();
			const bool bColorValueEvalued =
				pFipImageDataObject->getPixelIndex( lX, lY, pIndexValue );
			
			if ( ( ! bColorValueEvalued ) ||
					( pFipImageDataObject->getPaletteSize() <= (*pIndexValue) ) ){
				delete pColorValue;
				delete pIndexValue;
				return cVectorProperty( cTypeProperty::NONE );
			}
			(*pColorValue) = pColorPalette[ *pIndexValue ];
			delete pIndexValue;
		}
	}else{//background point
		const bool bColorValueEvalued =
			pFipImageDataObject->getFileBkColor( pColorValue );
		if ( ! bColorValueEvalued ){
			delete pColorValue;
			return cVectorProperty( cTypeProperty::NONE );
		}
		
		if ( pColorPalette != NULL ){
			if ( pFipImageDataObject->getPaletteSize() <=
					(pColorValue->rgbReserved) ){
				delete pColorValue;
				return cVectorProperty( cTypeProperty::NONE );
			}
			(*pColorValue) = pColorPalette[ pColorValue->rgbReserved ];
		}
	}
	//convert color values to Fib vectors
	
	if ( uiPropertyNumber == 1 ){
		if ( pFipImageDataObject->isTransparent() ){
			//transparency exists -> convert transparency to property vector
			cVectorProperty vecTransparency( cTypeProperty::TRANSPARENCY );
			vecTransparency.setValue( 1, pColorValue->rgbReserved );
			delete pColorValue;
			return vecTransparency;
		}
	}else if ( uiPropertyNumber == 2 ){
		//convert color to property vector
		const bool bSWColor = pFipImageDataObject->isGrayscale();
		if ( bSWColor ){
			//grayscale color
			cVectorProperty vecColorGrayscale( cTypeProperty::COLOR_GRAYSCALE );
			vecColorGrayscale.setValue( 1, pColorValue->rgbRed );
			delete pColorValue;
			return vecColorGrayscale;
		}else{//RGB color
			cVectorProperty vecColorRGB( cTypeProperty::COLOR_RGB );
			vecColorRGB.setValue( 1, pColorValue->rgbRed );
			vecColorRGB.setValue( 2, pColorValue->rgbGreen );
			vecColorRGB.setValue( 3, pColorValue->rgbBlue );
			delete pColorValue;
			return vecColorRGB;
		}
	}
	delete pColorValue;
	return cVectorProperty( cTypeProperty::NONE );
}


/**
 * This method returns the uiPropertyNumber'th property for the image
 * position.
 * (The properties are given by the third dimension vector on the position.)
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the property vector
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the property vector
 * @param uiPropertyNumber the number of the property to return;
 * 	counting starts with 1; @see getNumberOfProperties()
 * @return the uiPropertyNumber'th property from the given position or the
 * 	property of type cTypeProperty::NONE if non exists
 */
cVectorProperty cFreeImageData::getPropertyForNumber(
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiPropertyNumber ) const{
	
	//normal point
	//get the correct position
	if ( ((longFib)(pFipImageDataObject->getWidth())) <= uiPositionX ){
		//point not in image
		return cVectorProperty( cTypeProperty::NONE );
	}
	if ( ((longFib)(pFipImageDataObject->getHeight())) <= uiPositionY ){
		//point not in image
		return cVectorProperty( cTypeProperty::NONE );
	}
	RGBQUAD * pColorValue = new RGBQUAD();

	RGBQUAD * pColorPalette = pFipImageDataObject->getPalette();
	if ( pColorPalette == NULL ){
		const bool bColorValueEvalued =
			pFipImageDataObject->getPixelColor( uiPositionX, uiPositionY, pColorValue );
		if ( ! bColorValueEvalued ){
			delete pColorValue;
			return cVectorProperty( cTypeProperty::NONE );
		}
	}else{//use color pallette
		BYTE * pIndexValue = new BYTE();
		const bool bColorValueEvalued =
			pFipImageDataObject->getPixelIndex( uiPositionX, uiPositionY, pIndexValue );
		
		if ( ( ! bColorValueEvalued ) ||
				( pFipImageDataObject->getPaletteSize() <= (*pIndexValue) ) ){
			delete pColorValue;
			delete pIndexValue;
			return cVectorProperty( cTypeProperty::NONE );
		}
		(*pColorValue) = pColorPalette[ *pIndexValue ];
		delete pIndexValue;
	}
	//convert color values to Fib vectors
	
	if ( uiPropertyNumber == 1 ){
		if ( pFipImageDataObject->isTransparent() ){
			//transparency exists -> convert transparency to property vector
			cVectorProperty vecTransparency( cTypeProperty::TRANSPARENCY );
			vecTransparency.setValue( 1, pColorValue->rgbReserved );
			delete pColorValue;
			return vecTransparency;
		}
	}else if ( uiPropertyNumber == 2 ){
		//convert color to property vector
		const bool bSWColor = pFipImageDataObject->isGrayscale();
		if ( bSWColor ){
			//grayscale color
			cVectorProperty vecColorGrayscale( cTypeProperty::COLOR_GRAYSCALE );
			vecColorGrayscale.setValue( 1, pColorValue->rgbRed );
			delete pColorValue;
			return vecColorGrayscale;
		}else{//RGB color
			cVectorProperty vecColorRGB( cTypeProperty::COLOR_RGB );
			vecColorRGB.setValue( 1, pColorValue->rgbRed );
			vecColorRGB.setValue( 2, pColorValue->rgbGreen );
			vecColorRGB.setValue( 3, pColorValue->rgbBlue );
			delete pColorValue;
			return vecColorRGB;
		}
	}
	delete pColorValue;
	return cVectorProperty( cTypeProperty::NONE );
}


//methods for points given as unsigned int pairs:

/**
 * This method evalues the difference of two points properties.
 * This difference is the sum of the difference of the property
 * vectors elements or the sum of the distance betwean the third dimension
 * elements on the given positions.
 *
 * @param position1 the first point for the first property vector
 * @param position2 the second point for the second property vector
 * @return the sum of distances betwean the vector elements of the
 * 	properties of the first and second point
 */
doubleFib cFreeImageData::getDifference(
			const pair< unsigned int, unsigned int> & position1,
			const pair< unsigned int, unsigned int> & position2 ) const{
	
	return getDifference( position1.first, position1.second,
			position2.first, position2.second );
}


/**
 * This method evalues the difference of two points properties.
 * This difference is the sum of the difference of the property
 * vectors elements or the sum of the distance betwean the third dimension
 * elements for the property on the given positions.
 *
 * @param position1 the first point for the first property vector
 * @param position2 the second point for the second property vector
 * @param uiPropertyType the type number of the property to return the
 * 	distances of (e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @return the sum of distances betwean the vector elements of the
 * 	properties of the first and second point
 */
doubleFib cFreeImageData::getDifference(
		const pair< unsigned int, unsigned int> & position1,
		const pair< unsigned int, unsigned int> & position2,
		const unsigned int uiPropertyType ) const{
	
	return getDifference( position1.first, position1.second,
			position2.first, position2.second, uiPropertyType );
}


/**
 * This method returns the property of the given type for the image
 * position.
 * (The properties are given by the third dimension vector on the position.)
 *
 * @param position the position of which to return the property vector
 * @param uiPropertyType the type number of the property to return
 * 	(e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @return the property for the given type uiPropertyType from the given
 * 	position or the property of type cTypeProperty::NONE if non exists
 */
cVectorProperty cFreeImageData::getProperty(
		const pair< unsigned int, unsigned int> & position,
		const unsigned int uiPropertyType ) const{
	
	return getProperty( position.first, position.second, uiPropertyType );
}


/**
 * This method returns the uiPropertyNumber'th property for the image
 * position.
 * (The properties are given by the third dimension vector on the position.)
 *
 * @param position the position of which to return the property vector
 * @param uiPropertyNumber the number of the property to return;
 * 	counting starts with 1; @see getNumberOfProperties()
 * @return the uiPropertyNumber'th property from the given position or the
 * 	property of type cTypeProperty::NONE if non exists
 */
cVectorProperty cFreeImageData::getPropertyForNumber(
		const pair< unsigned int, unsigned int> & position,
		const unsigned int uiPropertyNumber ) const{
	
	return getPropertyForNumber( position.first, position.second, uiPropertyNumber );
}




