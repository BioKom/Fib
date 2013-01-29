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
 */
/*
History:
14.04.2012  Oesterholz  created
28.01.2013  Oesterholz  COLOR_SW changed to COLOR_GRAYSCALE
*/


#include "cFreeImageData.h"

#include "cDomainVector.h"
#include "cDomainNaturalNumber.h"
#include "cTypeDimension.h"
#include "cTypeProperty.h"


using namespace fib;


/**
 * standard constructor
 *
 * @param fipImageDataObject The object, for which this class is the wraper.
 */
cFreeImageData::cFreeImageData( fipImage & fipImageDataObject ):
		pFipImageDataObject( &fipImageDataObject ){
	//nothing to do
}


/**
 * destructor
 */
cFreeImageData::~cFreeImageData(){
	//nothing to do
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

	delete vecDomainPosition[ 1 ];
	delete vecDomainPosition[ 2 ];
	
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
		const bool bColorValueEvalued =
			pFipImageDataObject->getPixelColor( lX, lY, pColorValue );
		if ( ! bColorValueEvalued ){
			delete pColorValue;
			return false;
		}
	}else{//background point
		pFipImageDataObject->getFileBkColor( pColorValue );
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
		const bool bColorValueEvalued =
			pFipImageDataObject->getPixelColor( lX, lY, pColorValue );
		if ( ! bColorValueEvalued ){
			delete pColorValue;
			return list<cVectorProperty>();
		}
	}else{//background point
		pFipImageDataObject->getFileBkColor( pColorValue );
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










