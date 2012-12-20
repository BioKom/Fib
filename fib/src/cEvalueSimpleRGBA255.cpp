/**
 * @class cEvalueSimpleRGBA255
 * file name: cEvalueSimpleRGBA255.cpp
 * @author Betti Oesterholz
 * @date 18.03.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the class for evaluing Fib objects as a matrix of
 * a RGBA image.
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
 * This file contains the class for evaluing Fib objects as a matrix of
 * a RGBA image. @see pImageData
 * Just colors and transparency is evalued. The data is stored into an
 * array. The array is two dimensional and goes in the first dimension
 * from 0 to ulMaxX and in the second from 0 to ulMaxY. Every entry of the
 * array consists of tree values with 8 bit each (values from 0 to 255).
 * This class should keep the evaluing of a normal image (e.g. Bitmap image)
 * as simple as possible.
 */
/*
History:
18.03.2012  Oesterholz  created
10.04.2012  Oesterholz  methods of interface iImageData added
19.12.2012  Oesterholz  alpha handling corrected
*/

#include "cEvalueSimpleRGBA255.h"

#include "cPoint.h"
#include "cProperty.h"
#include "cTypeDimension.h"
#include "cTypeProperty.h"
#include "cDomainVector.h"
#include "cDomainNaturalNumber.h"
#include "cDomainNaturalNumberBit.h"


using namespace fib;


/**
 * standard constructor
 *
 * @param uiInMaxX the maximum value for the first (x) dimension @see uiMaxX
 * @param uiInMaxY the maximum value for the second (y) dimension @see uiMaxY
 */
cEvalueSimpleRGBA255::cEvalueSimpleRGBA255( const unsigned int uiInMaxX,
		const unsigned int uiInMaxY ):uiMaxX( uiInMaxX ), uiMaxY( uiInMaxY ),
		bBackgroundColorExists( false ){
	//init array with 0
	pImageData = (unsigned char*)malloc( uiMaxX * uiMaxY * 4 );
	clear();
}


/**
 * destructor
 */
cEvalueSimpleRGBA255::~cEvalueSimpleRGBA255(){
	
	free( pImageData );
}


/**
 * The method with wich the evalued points with ther properties are
 * inserted. Everytime a point (to evalue) is reached in the
 * evaluation, this method is called with the position and the
 * properties of the point and stores the data into @see pImageData
 * This method will just evalue two dimensional points and properties
 * for RGB and transparency.
 * Points first dimension can have values from 0 ( including ) to the
 * maximum value for the first (x) dimension.
 * 	( 0 =< vPosition.getValue( 1 ) < uiMaxX ) @see uiMaxX
 * Points second dimension ( vPosition.getValue( 2 ) ) can have values
 * from 0 ( including ) to the maximum value for the second (y) dimension.
 * 	( 0 =< vPosition.getValue( 2 ) < uiMaxY ) @see uiMaxY
 * Background points (with 0 elements) are also possible.
 * All other points will be discarded.
 * Property (color RGB or transparency) element values should have a
 * values from 0 to 255 (both including), else they will be rounded
 * into the area.
 *
 * @see pImageData
 * @param vPosition the position of the point, which is evalued
 * @param vProperties a list of the properties of the point
 */
bool cEvalueSimpleRGBA255::evaluePosition( const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties ){
	
	setPoint( vPosition, vProperties );
	
	return true;
}


/**
 * This method clears the image data.
 *
 * @see pImageData
 */
void cEvalueSimpleRGBA255::clear(){
	
	memset( pImageData, 0x0, uiMaxX * uiMaxY * 4 );
	memset( pBackgroundColor, 0x0, 4 );
	bBackgroundColorExists = false;
}


/**
 * Adds the background color pBackgroundColor to the image data matrix
 * pImageData, if existing.
 *
 * @see pBackgroundColor
 * @see pImageData
 * @return true if the background color was added the image data matrix,
 * 	else false
 */
bool cEvalueSimpleRGBA255::colorWithBackgroundColor(){
	
	if ( ! bBackgroundColorExists ){
		//no background color to set
		return false;
	}
	const unsigned char ucBgAlpha = pBackgroundColor[ 0 ];
	if ( ucBgAlpha == 0 ){
		//background total transparenc -> nothing to change
		return true;
	}
	const unsigned char ucBgRed   = pBackgroundColor[ 1 ];
	const unsigned char ucBgGreen = pBackgroundColor[ 2 ];
	const unsigned char ucBgBlue  = pBackgroundColor[ 3 ];

	const float fBgAlpha      = ((float)(ucBgAlpha)) / 255.0;
	const float fBgRedAlpha   = ((float)(ucBgRed)) * fBgAlpha / 255.0;
	const float fBgGreenAlpha = ((float)(ucBgGreen)) * fBgAlpha / 255.0;
	const float fBgBlueAlpha  = ((float)(ucBgBlue)) * fBgAlpha / 255.0;
	
	//set the color values of all points
	unsigned char * pEntry = pImageData;
	for ( unsigned int uiX = 0; uiX < uiMaxX; uiX++ ){
		for ( unsigned int uiY = 0; uiY < uiMaxY; uiY++ ){
			
			const unsigned char ucPointAlpha = (*pEntry);
			if ( ucPointAlpha == 255 ){
				//point totaly untransparenc no background to see -> skip it
				pEntry += 4;
				continue;
			}
			//alpha_matrix_new = 255.0 * ( fPointAlpha + fBgAlpha * ( 1 - fAlphaPoint ) );
			(*pEntry) = ucPointAlpha + fBgAlpha * ( 255 - ucPointAlpha );
			pEntry++;
			//color_new = color_actual + color_bg * fBgAlpha * ( 1 - fAlphaPoint )
			(*pEntry) = (*pEntry) + fBgRedAlpha * ( 255 - ucPointAlpha );
			pEntry++;
			(*pEntry) = (*pEntry) + fBgGreenAlpha * ( 255 - ucPointAlpha );
			pEntry++;
			(*pEntry) = (*pEntry) + fBgBlueAlpha * ( 255 - ucPointAlpha );
			pEntry++;
		}//end for uiY
	}//end for uiX
	return true;
}



//methods of interface iImageData:

/**
 * This method returns the domains for the color and transparency properties.
 *
 * @return the domains for the color and transparency properties
 */
cDomains cEvalueSimpleRGBA255::getPropertyDomains() const{
	
	//vector( 1, IntegerB(8) )
	vector<cDomainSingle*> vecDomainTransparency( 1 );
	vecDomainTransparency[ 0 ] = new cDomainNaturalNumberBit( 8 );

	//vector( 3, IntegerB(8), IntegerB(8) , IntegerB(8) )
	vector<cDomainSingle*> vecDomainColorRGB( 3 );
	vecDomainColorRGB[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomainColorRGB[ 1 ] = new cDomainNaturalNumberBit( 8 );
	vecDomainColorRGB[ 2 ] = new cDomainNaturalNumberBit( 8 );
	
	cDomains domains;
	
	domains.addDomain( cTypeProperty( cTypeProperty::TRANSPARENCY ),
		cDomainVector( vecDomainTransparency ) );
	
	domains.addDomain( cTypeProperty( cTypeProperty::COLOR_RGB ),
		cDomainVector( vecDomainColorRGB ) );

	delete vecDomainTransparency[ 0 ];

	delete vecDomainColorRGB[ 0 ];
	delete vecDomainColorRGB[ 1 ];
	delete vecDomainColorRGB[ 2 ];
	
	return domains;
}


/**
 * This method returns the domains for the positions (dimension domain).
 *
 * @return the domains for the positions (dimension domain)
 */
cDomains cEvalueSimpleRGBA255::getPositionDomain() const{
	
	cDomains domains;
	
	vector<unsignedIntFib> vecDimensionMapping;
	vecDimensionMapping.push_back( 1 );
	vecDimensionMapping.push_back( 2 );
	
	const cTypeDimension typeDimension( vecDimensionMapping );
	
	vector<cDomainSingle*> vecDomainPosition( 2 );
	vecDomainPosition[ 0 ] = new cDomainNaturalNumber( uiMaxX - 1 );
	vecDomainPosition[ 1 ] = new cDomainNaturalNumber( uiMaxY - 1 );
	
	domains.addDomain( typeDimension, cDomainVector( vecDomainPosition ) );

	delete vecDomainPosition[ 1 ];
	delete vecDomainPosition[ 2 ];
	
	return domains;
}


/**
 * With this method the properties for a points are set.
 *
 * @param vPosition the position of the point to set
 * @param vProperties a list of the properties of the point
 * @return true if the properties for the point cold be set, else false
 */
bool cEvalueSimpleRGBA255::setPoint(  const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties ){
	
	unsigned char * pEntry = NULL;
	if ( vPosition.getNumberOfElements() != 0 ){
		//normal point
		//get the correct position
		const longFib lX = fib::roundToLongFib( vPosition.getValue( 1 ) );
		
		if ( ( lX < 0 ) || ( uiMaxX <= lX ) ){
			//point not in image
			return false;
		}
		const longFib lY = fib::roundToLongFib( vPosition.getValue( 2 ) );
		if ( ( lY < 0 ) || ( uiMaxY <= lY ) ){
			//point not in image
			return false;
		}
		
		pEntry = pImageData + ( ( lX * ((longFib)uiMaxY)  + lY ) * 4 );
	}else{//background point
		pEntry = pBackgroundColor;
		bBackgroundColorExists = true;
	}
	
	/*the last found alpha value for the point;
	 init with 1 because transparency standard value is 0*/
	float fLastAlpha = 1.0;
	const float fOldAlpha = ((float)(*pEntry)) / 255.0;
	
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
				(*pEntry) = 255;
				bNoAlpha = false;
			}
			const float fAlphaMatrix = ((float)(*pEntry)) / 255.0;
			
			unsigned char * pColorValue = pEntry;
			//red
			pColorValue++;
			
			const longFib lColorR = fib::roundToLongFib(
				itrProperty->getValue( 1 ) );
			const float fColorR = ( lColorR <= 0 ) ? 0 :
				( 255 <= lColorR ) ? 255 : lColorR;
			
			(*pColorValue) = fColorR * fLastAlpha +
				((float)(*pColorValue)) * fAlphaMatrix * ( 1.0 - fLastAlpha );
			//green
			pColorValue++;
			
			const longFib lColorG = fib::roundToLongFib(
				itrProperty->getValue( 2 ) );
			const float fColorG = ( lColorG <= 0 ) ? 0 :
				( 255 <= lColorG ) ? 255 : lColorG;
			
			(*pColorValue) = fColorG * fLastAlpha +
				((float)(*pColorValue)) * fAlphaMatrix * ( 1.0 - fLastAlpha );
			//blue
			pColorValue++;
			
			const longFib lColorB = fib::roundToLongFib(
				itrProperty->getValue( 3 ) );
			const float fColorB = ( lColorB <= 0 ) ? 0 :
				( 255 <= lColorB ) ? 255 : lColorB;
			
			(*pColorValue) = fColorB * fLastAlpha +
				((float)(*pColorValue)) * fAlphaMatrix * ( 1.0 - fLastAlpha );
			
		}else if ( uiPropertytype == cTypeProperty::TRANSPARENCY ){
			//transparency
			// alpha_new = alpha_matrix + alpha_new ( 1 - alpha_matrix )
			const longFib lTransparency = fib::roundToLongFib(
				itrProperty->getValue( 1 ) );
			//alpha_new = 255 - transparency;
			fLastAlpha *= ( lTransparency <= 0 ) ? 1.0 :
				( 255 <= lTransparency ) ? 0 : (255 - lTransparency) / 255.0;
			
			//alpha_matrix_new = 255.0 * ( fLastAlpha + fOldAlpha * ( 1 - fLastAlpha ) );
			(*pEntry) = 255.0 * ( fLastAlpha + fOldAlpha * ( 1.0 - fLastAlpha ) );
			
			bNoAlpha = false;//transparency value set
		}//else discard property
		
	}//end for all properties for the point
	
	return true;
}


/**
 * With this method the properties for given points are returned.
 *
 * @param vPosition the position of the point, for which the properties
 * 	should be returned
 * @return a list of the properties of the point
 */
list<cVectorProperty> cEvalueSimpleRGBA255::getPointProperties(
		const cVectorPosition & vPosition ) const{

	const unsigned char * pEntry = NULL;
	if ( vPosition.getNumberOfElements() != 0 ){
		//normal point
		//get the correct position
		const longFib lX = fib::roundToLongFib( vPosition.getValue( 1 ) );
		
		if ( ( lX < 0 ) || ( uiMaxX <= lX ) ){
			//point not in image
			return list<cVectorProperty>();
		}
		const longFib lY = fib::roundToLongFib( vPosition.getValue( 2 ) );
		if ( ( lY < 0 ) || ( uiMaxY <= lY ) ){
			//point not in image
			return list<cVectorProperty>();
		}
		
		pEntry = pImageData + ( ( lX * ((longFib)uiMaxY)  + lY ) * 4 );
	}else{//background point
		if ( ! bBackgroundColorExists ){
			//no background -> no background properties
			return list<cVectorProperty>();
		}
		pEntry = pBackgroundColor;
	}
	list<cVectorProperty> liVecProperties;
	//convert transparency to property vector
	liVecProperties.push_back( cVectorProperty( cTypeProperty::TRANSPARENCY ) );
	liVecProperties.back().setValue( 1, *pEntry );
	
	pEntry++;
	//convert color to property vector
	liVecProperties.push_back( cVectorProperty( cTypeProperty::COLOR_RGB ) );
	cVectorProperty & vecColorRGB = liVecProperties.back();
	vecColorRGB.setValue( 1, *pEntry );
	pEntry++;
	vecColorRGB.setValue( 2, *pEntry );
	pEntry++;
	vecColorRGB.setValue( 3, *pEntry );
	
	return liVecProperties;
}


