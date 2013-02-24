/**
 * @class cEvalueSimpleRGBA255Scaled
 * file name: cEvalueSimpleRGBA255Scaled.cpp
 * @author Betti Oesterholz
 * @date 23.02.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the class for evaluing Fib objects as a matrix of
 * a RGBA image.
 *
 * Copyright (C) @c LGPL3 2013 Betti Oesterholz
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
 * The input property vector values will be scaled with given scaling factors.
 */
/*
History:
23.02.2013  Oesterholz  created
*/

#include "cEvalueSimpleRGBA255Scaled.h"

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
 * The given scaling factors should be a values, so that all evalued
 * property values multiplied by the scaling factor are betwean
 * (including) 0 and 255.
 *
 * @param uiInMaxX the maximum value for the first (x) dimension @see uiMaxX
 * @param uiInMaxY the maximum value for the second (y) dimension @see uiMaxY
 * @param dInScalingFactorAlpha the scaling factor for the color alpha
 * 	@see dScalingFactorAlpha
 * @param dInScalingFactorRed the scaling factor for the color red
 * 	@see dScalingFactorRed
 * @param dInScalingFactorGreen the scaling factor for the color green
 * 	@see dScalingFactorGreen
 * @param dInScalingFactorBlue the scaling factor for the color blue
 * 	@see dScalingFactorBlue
 */
cEvalueSimpleRGBA255Scaled::cEvalueSimpleRGBA255Scaled( const unsigned int uiInMaxX,
		const unsigned int uiInMaxY,
		const doubleFib dInScalingFactorAlpha,
		const doubleFib dInScalingFactorRed,
		const doubleFib dInScalingFactorGreen,
		const doubleFib dInScalingFactorBlue ):
			cEvalueSimpleRGBA255( uiInMaxX, uiInMaxY ),
			dScalingFactorAlpha( dInScalingFactorAlpha ),
			dScalingFactorRed( dInScalingFactorRed ),
			dScalingFactorGreen( dInScalingFactorGreen ),
			dScalingFactorBlue( dInScalingFactorBlue ){
	//nothing to do;
}


/**
 * destructor
 */
cEvalueSimpleRGBA255Scaled::~cEvalueSimpleRGBA255Scaled(){
	//nothing to do
}


//methods of interface iImageData:

/**
 * This method returns the domains for the color and transparency properties.
 *
 * @return the domains for the color and transparency properties
 */
cDomains cEvalueSimpleRGBA255Scaled::getPropertyDomains() const{
	
	//vector( 1, IntegerB(8) )
	vector<cDomainSingle*> vecDomainTransparency( 1 );
	vecDomainTransparency[ 0 ] = new cDomainNaturalNumberBit(
			8, 1.0 / dScalingFactorAlpha );

	//vector( 3, IntegerB(8), IntegerB(8) , IntegerB(8) )
	vector<cDomainSingle*> vecDomainColorRGB( 3 );
	vecDomainColorRGB[ 0 ] = new cDomainNaturalNumberBit(
		8, 1.0 / dScalingFactorRed );
	vecDomainColorRGB[ 1 ] = new cDomainNaturalNumberBit(
		8, 1.0 / dScalingFactorGreen );
	vecDomainColorRGB[ 2 ] = new cDomainNaturalNumberBit(
		8, 1.0 / dScalingFactorBlue );
	
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
 * With this method the properties for a point are set.
 *
 * @param vPosition the position of the point to set
 * @param vProperties a list of the properties of the point
 * @return true if the properties for the point cold be set, else false
 */
bool cEvalueSimpleRGBA255Scaled::setPoint(  const cVectorPosition & vPosition,
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
				itrProperty->getValue( 1 ) * dScalingFactorRed );
			const float fColorR = ( lColorR <= 0 ) ? 0 :
				( 255 <= lColorR ) ? 255 : lColorR;
			
			(*pColorValue) = fColorR * fLastAlpha +
				((float)(*pColorValue)) * fAlphaMatrix * ( 1.0 - fLastAlpha );
			//green
			pColorValue++;
			
			const longFib lColorG = fib::roundToLongFib(
				itrProperty->getValue( 2 ) * dScalingFactorGreen );
			const float fColorG = ( lColorG <= 0 ) ? 0 :
				( 255 <= lColorG ) ? 255 : lColorG;
			
			(*pColorValue) = fColorG * fLastAlpha +
				((float)(*pColorValue)) * fAlphaMatrix * ( 1.0 - fLastAlpha );
			//blue
			pColorValue++;
			
			const longFib lColorB = fib::roundToLongFib(
				itrProperty->getValue( 3 ) * dScalingFactorBlue );
			const float fColorB = ( lColorB <= 0 ) ? 0 :
				( 255 <= lColorB ) ? 255 : lColorB;
			
			(*pColorValue) = fColorB * fLastAlpha +
				((float)(*pColorValue)) * fAlphaMatrix * ( 1.0 - fLastAlpha );
			
		}else if ( uiPropertytype == cTypeProperty::TRANSPARENCY ){
			//transparency
			// alpha_new = alpha_matrix + alpha_new ( 1 - alpha_matrix )
			const longFib lTransparency = fib::roundToLongFib(
				itrProperty->getValue( 1 ) * dScalingFactorAlpha );
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
 * With this method the properties for given point are returned.
 *
 * @param vPosition the position of the point, for which the properties
 * 	should be returned
 * @return a list of the properties of the point
 */
list<cVectorProperty> cEvalueSimpleRGBA255Scaled::getPointProperties(
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
	liVecProperties.back().setValue( 1, (doubleFib(*pEntry)) / dScalingFactorAlpha );
	
	pEntry++;
	//convert color to property vector
	liVecProperties.push_back( cVectorProperty( cTypeProperty::COLOR_RGB ) );
	cVectorProperty & vecColorRGB = liVecProperties.back();
	vecColorRGB.setValue( 1, (doubleFib(*pEntry)) / dScalingFactorRed );
	pEntry++;
	vecColorRGB.setValue( 2, (doubleFib(*pEntry)) / dScalingFactorGreen );
	pEntry++;
	vecColorRGB.setValue( 3, (doubleFib(*pEntry)) / dScalingFactorBlue );
	
	return liVecProperties;
}


