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
19.02.2013  Oesterholz  clone method and copy constructor added
28.02.2013  Oesterholz  new methods from iMatrix3D added
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
 * @param uiInMaxX the maximum value for the first (x) dimension @see uiBorderIndexX
 * @param uiInMaxY the maximum value for the second (y) dimension @see uiBorderIndexY
 */
cEvalueSimpleRGBA255::cEvalueSimpleRGBA255( const unsigned int uiInMaxX,
		const unsigned int uiInMaxY ):uiBorderIndexX( uiInMaxX + 1 ),
		uiBorderIndexY( uiInMaxY + 1 ), bBackgroundColorExists( false ){
	//init array with 0
	pImageData = (unsigned char*)malloc( uiBorderIndexX * uiBorderIndexY * 4 );
	clear();
}


/**
 * copy constructor
 *
 * @param evalueSimpleRGBA255 the evalueSimpleRGBA255 to copy
 */
cEvalueSimpleRGBA255::cEvalueSimpleRGBA255(
		const cEvalueSimpleRGBA255 & evalueSimpleRGBA255 ):
			uiBorderIndexX( evalueSimpleRGBA255.uiBorderIndexX ),
			uiBorderIndexY( evalueSimpleRGBA255.uiBorderIndexY ),
			bBackgroundColorExists( evalueSimpleRGBA255.bBackgroundColorExists ){
	
	//copy image data
	pImageData = (unsigned char*)malloc( uiBorderIndexX * uiBorderIndexY * 4 );
	memcpy( pImageData, evalueSimpleRGBA255.pImageData, uiBorderIndexX * uiBorderIndexY * 4 );
	
	memcpy( pBackgroundColor, evalueSimpleRGBA255.pBackgroundColor, 4 );
}


/**
 * destructor
 */
cEvalueSimpleRGBA255::~cEvalueSimpleRGBA255(){
	
	free( pImageData );
}


/**
 * @return the name of this class
 */
string cEvalueSimpleRGBA255::getName() const{
	
	return "cEvalueSimpleRGBA255";
}


/**
 * This method clones this object.
 *
 * @return a pointer to the clone of this object
 */
cEvalueSimpleRGBA255 * cEvalueSimpleRGBA255::clone() const{
	
	return new cEvalueSimpleRGBA255( *this );
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
 * 	( 0 =< vPosition.getValue( 1 ) < uiBorderIndexX ) @see uiBorderIndexX
 * Points second dimension ( vPosition.getValue( 2 ) ) can have values
 * from 0 ( including ) to the maximum value for the second (y) dimension.
 * 	( 0 =< vPosition.getValue( 2 ) < uiBorderIndexY ) @see uiBorderIndexY
 * Background points (with 0 elements) are also possible.
 * All other points will be discarded.
 * Property (color RGB or transparency) element values should have a
 * values from 0 to 255 (both including), else they will be rounded
 * into the area.
 *
 * @see pImageData
 * @param vPosition the position of the point, which is evalued
 * @param vProperties a list of the properties of the point
 * @return true if the the point cold be evalued, else false
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
	
	memset( pImageData, 0x0, uiBorderIndexX * uiBorderIndexY * 4 );
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
	for ( unsigned int uiX = 0; uiX < uiBorderIndexX; uiX++ ){
		for ( unsigned int uiY = 0; uiY < uiBorderIndexY; uiY++ ){
			
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
	vecDomainPosition[ 0 ] = new cDomainNaturalNumber( uiBorderIndexX - 1 );
	vecDomainPosition[ 1 ] = new cDomainNaturalNumber( uiBorderIndexY - 1 );
	
	domains.addDomain( typeDimension, cDomainVector( vecDomainPosition ) );

	delete vecDomainPosition[ 0 ];
	delete vecDomainPosition[ 1 ];
	
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
		
		if ( ( lX < 0 ) || ( uiBorderIndexX <= lX ) ){
			//point not in image
			return false;
		}
		const longFib lY = fib::roundToLongFib( vPosition.getValue( 2 ) );
		if ( ( lY < 0 ) || ( uiBorderIndexY <= lY ) ){
			//point not in image
			return false;
		}
		
		pEntry = pImageData + ( ( lX * ((longFib)uiBorderIndexY)  + lY ) * 4 );
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
		
		if ( ( lX < 0 ) || ( uiBorderIndexX <= lX ) ){
			//point not in image
			return list<cVectorProperty>();
		}
		const longFib lY = fib::roundToLongFib( vPosition.getValue( 2 ) );
		if ( ( lY < 0 ) || ( uiBorderIndexY <= lY ) ){
			//point not in image
			return list<cVectorProperty>();
		}
		
		pEntry = pImageData + ( ( lX * ((longFib)uiBorderIndexY)  + lY ) * 4 );
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
iMatrix3D::tErrorValue cEvalueSimpleRGBA255::setValue( const doubleFib dValue,
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiChanel ){
	
	if ( uiBorderIndexX <= uiPositionX ){
		//point not in image
		return ERROR_OUTSIDE_INDEX_DIMENSION_1;
	}
	if ( uiBorderIndexY <= uiPositionY ){
		//point not in image
		return ERROR_OUTSIDE_INDEX_DIMENSION_2;
	}
	if ( 3 < uiChanel ){
		//no such property
		return ERROR_OUTSIDE_INDEX_DIMENSION_3;
	}
	const longFib lValue = fib::roundToLongFib( dValue );
	if ( lValue < 0 ){
		//value outside range
		return ERROR_LOWER_MIN_VALUE;
	}
	if ( 255 < lValue ){
		//value outside range
		return ERROR_GREATER_MAX_VALUE;
	}
	unsigned char * pEntry = pImageData +
		( ( uiPositionX * uiBorderIndexY + uiPositionY ) * 4 ) + uiChanel;
	
	const unsigned char ucValue = ((unsigned char)lValue);
	(*pEntry) = ucValue;
	
	return OK;
}


/**
 * With this method a integer value for a matrix element is set.
 *
 * @param lValue the integer value to set
 * @param uiPositionX the index on the first (x) dimension where to set
 * 	the value lValue
 * @param uiPositionY the index on the second (y) dimension where to set
 * 	the value lValue
 * @param uiChanel the index for the property chanel;
 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
 * @return OK (or 0) if the value could be set, else the error value
 * 	@see tErrorValue
 */
iMatrix3D::tErrorValue cEvalueSimpleRGBA255::setValue( const longFib lValue,
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiChanel ){
	
	if ( uiBorderIndexX <= uiPositionX ){
		//point not in image
		return ERROR_OUTSIDE_INDEX_DIMENSION_1;
	}
	if ( uiBorderIndexY <= uiPositionY ){
		//point not in image
		return ERROR_OUTSIDE_INDEX_DIMENSION_2;
	}
	if ( 3 < uiChanel ){
		//no such property
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
	unsigned char * pEntry = pImageData +
		( ( uiPositionX * uiBorderIndexY  + uiPositionY ) * 4 ) + uiChanel;
	
	const unsigned char ucValue = ((unsigned char)lValue);
	(*pEntry) = ucValue;
	
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
doubleFib cEvalueSimpleRGBA255::getValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	
	if ( uiBorderIndexX <= uiPositionX ){
		//point not in image
		return 0.0;
	}
	if ( uiBorderIndexY <= uiPositionY ){
		//point not in image
		return 0.0;
	}
	if ( 3 < uiChanel ){
		//no such property
		return 0.0;
	}
	
	unsigned char * pEntry = pImageData +
		( ( uiPositionX * uiBorderIndexY  + uiPositionY ) * 4 ) + uiChanel;
	
	const unsigned char ucValue = (*pEntry);
	
	return ((doubleFib)ucValue);
}


/**
 * With this method the integer value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the value
 * @param uiChanel the index for the property chanel;
 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
 * @return the integer value of the given position in the matrix
 */
unsigned int cEvalueSimpleRGBA255::getValueUInt( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	
	if ( uiBorderIndexX <= uiPositionX ){
		//point not in image
		return 0;
	}
	if ( uiBorderIndexY <= uiPositionY ){
		//point not in image
		return 0;
	}
	if ( 3 < uiChanel ){
		//no such property
		return 0;
	}
	
	unsigned char * pEntry = pImageData +
		( ( uiPositionX * uiBorderIndexY  + uiPositionY ) * 4 ) + uiChanel;
	
	const unsigned char ucValue = (*pEntry);
	
	return ((unsigned int)ucValue);
}


/**
 * With this method the minimum value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the minimum value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the minimum value
 * @param uiChanel the index for the property chanel;
 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
 * @return the minimum value of the given position in the matrix
 */
doubleFib cEvalueSimpleRGBA255::getMinValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	
	return 0.0;
}


/**
 * With this method the minimum integer value for a matrix element is returned.
 *
 * @return the minimum integer value for entries in the matrix
 */
longFib cEvalueSimpleRGBA255::getMinValueUInt() const{
	
	return 0;
}


/**
 * With this method the maximum value for a matrix element is returned.
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the maximum value
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the maximum value
 * @param uiChanel the index for the property chanel;
 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
 * @return the maximum value of the given position in the matrix
 */
doubleFib cEvalueSimpleRGBA255::getMaxValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	
	if ( uiChanel < 4 ){
		return 255.0;
	}
	return 0.0;
}


/**
 * With this method the maximum integer value for a matrix element is returned.
 *
 * @return the maximum integer value for entries in the matrix
 */
longFib cEvalueSimpleRGBA255::getMaxValueUInt() const{
	
	return 255;
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
doubleFib cEvalueSimpleRGBA255::getMinDifference( const unsigned int uiPositionX,
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
unsigned int cEvalueSimpleRGBA255::getMaxIndex( const unsigned int uiDirection ) const{
	
	if ( 2 < uiDirection ){
		//no such direction
		return 0;
	}//else
	if ( uiDirection == 0 ){
		return uiBorderIndexX - 1;
	}//else
	if ( uiDirection == 1 ){
		return uiBorderIndexY - 1;
	}//else
	if ( uiDirection == 2 ){
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
bool cEvalueSimpleRGBA255::equal( const iMatrix3D &matrix ) const{
	
	if ( getName() != matrix.getName() ){
		//not the correct matrix type
		return false;
	}
	cEvalueSimpleRGBA255 * pOtherRGBA255 = ((cEvalueSimpleRGBA255*)(&matrix));
	if ( ( uiBorderIndexX != pOtherRGBA255->uiBorderIndexX ) ||
			( uiBorderIndexY != pOtherRGBA255->uiBorderIndexY ) ){
		//the image data don't have the same size
		return false;
	}
	if ( bBackgroundColorExists != pOtherRGBA255->bBackgroundColorExists  ){
		//the image data have both not the same background color
		return false;
	}
	if ( memcmp( pBackgroundColor, pOtherRGBA255->pBackgroundColor, 4 ) != 0 ){
		//the image data have both not the same background color
		return false;
	}
	if ( memcmp( pImageData, pOtherRGBA255->pImageData, uiBorderIndexX * uiBorderIndexY * 4 ) != 0 ){
		//the image data have both not the same color matrix
		return false;
	}
	return true;
}


/**
 * This function evalues the derivate of the matrix in the given
 * direction / dimension.
 *
 * @param uiDirection the direction in which the derivation should
 * 	be evalued (possible values are 0 to 2)
 * @return a pointer to the derivate matrix in the given direction of
 * 	this matrix, or NULL if non exists
 * 	Beware: You have to care that the returnd object is deleted.
 */
iMatrix3D * cEvalueSimpleRGBA255::evalueDerivate(
		const unsigned int uiDirection ) const{
	
	if ( 2 < uiDirection ){
		//no such property
		return NULL;
	}
	
	cMatrix3DInteger * pDerivateMatrix = NULL;
	if ( uiDirection == 0 ){
		//evalue derivation in first (1. or x) dimension
		if ( uiBorderIndexX <= 1 ){
			//just one line in dimension 1 -> can't evalue derivate
			return NULL;
		}
		const unsigned int uiMaxIndexDimX = uiBorderIndexX - 2;
		
		pDerivateMatrix = getEmptyMatrixForDerivate( uiMaxIndexDimX,
			uiBorderIndexY - 1, 3 );
		
		const unsigned int uiBytsPerLine = uiBorderIndexY * 4;
		
		unsigned char * pEntry;
		unsigned char * pNextEntry;
		int iDerivateValue;
		
		pEntry = pImageData;// x
		pNextEntry = pEntry + uiBytsPerLine;// x + 1
			
		for ( unsigned int uiActualIndexDim1 = 0;
				uiActualIndexDim1 <= uiMaxIndexDimX; uiActualIndexDim1++ ){
			//for all x index values
			for ( unsigned int uiActualIndexDim2 = 0;
					uiActualIndexDim2 < uiBorderIndexY; uiActualIndexDim2++ ){
				//for all y index values
				for ( unsigned int uiActualIndexDim3 = 0; uiActualIndexDim3 <= 3;
						uiActualIndexDim3++ ){
					//for all z (chanel) index values
					//evalue derivate value
					iDerivateValue = ((int)(*pNextEntry)) - ((int)(*pEntry));
					//set derivate value
					pDerivateMatrix->setValue( ((longFib)iDerivateValue),
						uiActualIndexDim1, uiActualIndexDim2, uiActualIndexDim3 );
					
					//go to next entry
					pEntry++;
					pNextEntry++;
				}//end for all index in z direction
			}//end for all values in y direction
		}//end for all index in x direction
		
	}else if ( uiDirection == 1 ){
		//evalue derivation in second (2. or y) dimension
		if ( uiBorderIndexY <= 1 ){
			//just one line in dimension 2 -> can't evalue derivate
			return NULL;
		}
		const unsigned int uiMaxIndexDimY = uiBorderIndexY - 2;
		pDerivateMatrix = getEmptyMatrixForDerivate( uiBorderIndexX - 1,
			uiMaxIndexDimY, 3 );
		
		unsigned char * pEntry;
		unsigned char * pNextEntry;
		int iDerivateValue;
		
		pEntry = pImageData;
		pNextEntry = pEntry + 4;
		
		for ( unsigned int uiActualIndexDim1 = 0;
				uiActualIndexDim1 < uiBorderIndexX; uiActualIndexDim1++ ){
			//for all x index values
			for ( unsigned int uiActualIndexDim2 = 0;
					uiActualIndexDim2 <= uiMaxIndexDimY; uiActualIndexDim2++ ){
				//for all y index values
				for ( unsigned int uiActualIndexDim3 = 0; uiActualIndexDim3 <= 3;
						uiActualIndexDim3++ ){
					//for all z (or chanel) index values
					//evalue derivate value
					iDerivateValue = ((int)(*pNextEntry)) - ((int)(*pEntry));
					//set derivate value
					pDerivateMatrix->setValue( ((longFib)iDerivateValue),
						uiActualIndexDim1, uiActualIndexDim2, uiActualIndexDim3 );
					
					//go to next entry
					pEntry++;
					pNextEntry++;
				}//end for all index in z direction
			}//end for all values in y direction
			//go to next line (go to next entry dos the other ++) or skip last entry in line
			pEntry += 4;
			pNextEntry += 4;
		}//end for all index in x direction
		
	}else if ( uiDirection == 2 ){
		//evalue derivation in third (3. or z) dimension
		pDerivateMatrix = getEmptyMatrixForDerivate( uiBorderIndexX - 1,
			uiBorderIndexY - 1, 2 );
		
		unsigned char * pEntry;
		unsigned char * pNextEntry;
		int iDerivateValue;
		
		pEntry = pImageData;
		pNextEntry = pEntry + 1;
		
		for ( unsigned int uiActualIndexDim1 = 0;
				uiActualIndexDim1 < uiBorderIndexX; uiActualIndexDim1++ ){
			//for all x index values
			for ( unsigned int uiActualIndexDim2 = 0;
					uiActualIndexDim2 < uiBorderIndexY; uiActualIndexDim2++ ){
				//for all y index values
				for ( unsigned int uiActualIndexDim3 = 0; uiActualIndexDim3 <= 2;
						uiActualIndexDim3++ ){
					//evalue derivate value
					iDerivateValue = ((int)(*pNextEntry)) - ((int)(*pEntry));
					//set derivate value
					pDerivateMatrix->setValue( ((longFib)iDerivateValue),
						uiActualIndexDim1, uiActualIndexDim2, uiActualIndexDim3 );
					
					//go to next entry
					pEntry++;
					pNextEntry++;
				}//end for all index in z direction
				//go next entry or skip last entry in line
				pEntry++;
				pNextEntry++;
			}//end for all values in y direction
		}//end for all index in x direction
		
	}//else not a valid direction
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
doubleFib cEvalueSimpleRGBA255::getDifference(
		const cVectorPosition & vPosition1,
		const cVectorPosition & vPosition2 ) const{
	
	//TODO background property?
	
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
doubleFib cEvalueSimpleRGBA255::getDifference(
		const unsigned int uiPosition1X, const unsigned int uiPosition1Y,
		const unsigned int uiPosition2X, const unsigned int uiPosition2Y )
			const{
	
	if ( ( uiBorderIndexX <= uiPosition1X ) || ( uiBorderIndexY <= uiPosition1Y ) ||
			( uiBorderIndexX <= uiPosition2X ) || ( uiBorderIndexY <= uiPosition2Y ) ){
		//point not in image -> no difference
		return 0.0;
	}
	
	unsigned char * pEntry1 = pImageData +
		( ( uiPosition1X * uiBorderIndexY  + uiPosition1Y ) * 4 );
	unsigned char * pEntry2 = pImageData +
		( ( uiPosition2X * uiBorderIndexY  + uiPosition2Y ) * 4 );
	
	const unsigned char & ucValue1_1 = (*pEntry1);
	const unsigned char & ucValue1_2 = (*pEntry2);
	unsigned int uiDifference = ( ucValue1_1 < ucValue1_2 ) ?
		( ucValue1_2 - ucValue1_1 ): ( ucValue1_1 - ucValue1_2 );
	
	pEntry1++;
	pEntry2++;
	const unsigned char & ucValue2_1 = (*pEntry1);
	const unsigned char & ucValue2_2 = (*pEntry2);
	uiDifference += ( ucValue2_1 < ucValue2_2 ) ?
		( ucValue2_2 - ucValue2_1 ): ( ucValue2_1 - ucValue2_2 );
	
	pEntry1++;
	pEntry2++;
	const unsigned char & ucValue3_1 = (*pEntry1);
	const unsigned char & ucValue3_2 = (*pEntry2);
	uiDifference += ( ucValue3_1 < ucValue3_2 ) ?
		( ucValue3_2 - ucValue3_1 ): ( ucValue3_1 - ucValue3_2 );
	
	pEntry1++;
	pEntry2++;
	const unsigned char & ucValue4_1 = (*pEntry1);
	const unsigned char & ucValue4_2 = (*pEntry2);
	uiDifference += ( ucValue4_1 < ucValue4_2 ) ?
		( ucValue4_2 - ucValue4_1 ): ( ucValue4_1 - ucValue4_2 );
	
	return ((doubleFib)uiDifference);
}


/**
 * This method returnes the number of properties for the image position.
 * (The properties are given by the third dimension vector on the position.)
 *
 * @param uiPositionX the index on the first (x) dimension of which to
 * 	return the number of property vectors
 * @param uiPositionY the index on the second (y) dimension of which to
 * 	return the number of property vectors
 * @return the number of property vectors for the given position
 */
unsigned int cEvalueSimpleRGBA255::getNumberOfProperties(
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
bool cEvalueSimpleRGBA255::isPropertyTypeIndependentOfPosition() const{
	
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
vector< unsigned int > cEvalueSimpleRGBA255::getDimension3IndexesForPropertyType(
		const unsigned int uiPropertyType,
		const unsigned int uiPositionX, const unsigned int uiPositionY ) const{
	
	vector< unsigned int > vecPropertyTypeIndexes;
	if ( uiPropertyType == cTypeProperty::TRANSPARENCY ){
		//return transparency type indexes
		vecPropertyTypeIndexes.push_back( 0 );
	}else if ( uiPropertyType == cTypeProperty::COLOR_RGB ){
		//return color RGB type indexes
		vecPropertyTypeIndexes.push_back( 1 );
		vecPropertyTypeIndexes.push_back( 2 );
		vecPropertyTypeIndexes.push_back( 3 );
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
unsigned int cEvalueSimpleRGBA255::getPropertyType(
		const unsigned int uiPropertyNumber,
		const unsigned int uiPositionX, const unsigned int uiPositionY ) const{
	
	if ( uiPropertyNumber == 1 ){
		//return transparency type
		return cTypeProperty::TRANSPARENCY;
	}else if ( uiPropertyNumber == 2 ){
		//return color RGB type
		return cTypeProperty::COLOR_RGB;
	}
	return cTypeProperty::NONE;
}


/**
 * This method returns the property number for the given property type for
 * the image position.
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
unsigned int cEvalueSimpleRGBA255::getPropertyNumberForType(
		const unsigned int uiPropertyType,
		const unsigned int uiPositionX, const unsigned int uiPositionY ) const{
	
	if ( uiPropertyType == cTypeProperty::TRANSPARENCY ){
		//return transparency number
		return 1;
	}else if ( uiPropertyType == cTypeProperty::COLOR_RGB ){
		//return color RGB number
		return 2;
	}//else no properties of such type
	return 0;
}


/**
 * This function evalues the difference of two points properties.
 * This difference is the sum of the difference of the property
 * vectors elements or the sum of the distance betwean the third dimension
 * elements for the property on the given positions.
 *
 * @param vPosition1 the first point for the first property vector
 * @param vPosition2 the second point for the second property vector
 * @param uiPropertyType the type number of the property to return the
 * 	distances of (e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @return the sum of distances betwean the vector elements of the
 * 	properties of the first and second point
 */
doubleFib cEvalueSimpleRGBA255::getDifference( const cVectorPosition & vPosition1,
		const cVectorPosition & vPosition2,
		const unsigned int uiPropertyType ) const{
	
	//TODO background property?
	
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
 * This function evalues the difference of two points properties.
 * This difference is the sum of the difference of the property
 * vector elements or the sum of the distance betwean the third dimension
 * elements for the property on the given positions.
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
 * 	third dimension of the property of the first and second point
 */
doubleFib cEvalueSimpleRGBA255::getDifference(
		const unsigned int uiPosition1X, const unsigned int uiPosition1Y,
		const unsigned int uiPosition2X, const unsigned int uiPosition2Y,
		const unsigned int uiPropertyType ) const{
	
	if ( ( uiBorderIndexX <= uiPosition1X ) || ( uiBorderIndexY <= uiPosition1Y ) ||
			( uiBorderIndexX <= uiPosition2X ) || ( uiBorderIndexY <= uiPosition2Y ) ){
		//point not in image -> no difference
		return 0.0;
	}
	
	unsigned char * pEntry1 = pImageData +
		( ( uiPosition1X * uiBorderIndexY  + uiPosition1Y ) * 4 );
	unsigned char * pEntry2 = pImageData +
		( ( uiPosition2X * uiBorderIndexY  + uiPosition2Y ) * 4 );
	
	if ( uiPropertyType == cTypeProperty::COLOR_RGB ){
		pEntry1++;
		pEntry2++;
		const unsigned char & ucValue2_1 = (*pEntry1);
		const unsigned char & ucValue2_2 = (*pEntry2);
		unsigned int uiDifference = (( ucValue2_1 < ucValue2_2 ) ?
			( ucValue2_2 - ucValue2_1 ) : ( ucValue2_1 - ucValue2_2 ));
		
		pEntry1++;
		pEntry2++;
		const unsigned char & ucValue3_1 = (*pEntry1);
		const unsigned char & ucValue3_2 = (*pEntry2);
		uiDifference += (( ucValue3_1 < ucValue3_2 ) ?
			( ucValue3_2 - ucValue3_1 ): ( ucValue3_1 - ucValue3_2 ));
		
		pEntry1++;
		pEntry2++;
		const unsigned char & ucValue4_1 = (*pEntry1);
		const unsigned char & ucValue4_2 = (*pEntry2);
		uiDifference += (( ucValue4_1 < ucValue4_2 ) ?
			( ucValue4_2 - ucValue4_1 ): ( ucValue4_1 - ucValue4_2 ));
		return ((doubleFib)uiDifference);
	}//else
	if ( uiPropertyType == cTypeProperty::TRANSPARENCY ){
		const unsigned char & ucValue1_1 = (*pEntry1);
		const unsigned char & ucValue1_2 = (*pEntry2);
		return ((doubleFib)( ucValue1_1 < ucValue1_2 ) ?
			( ucValue1_2 - ucValue1_1 ): ( ucValue1_1 - ucValue1_2 ) );
	}
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
cVectorProperty cEvalueSimpleRGBA255::getProperty(
		const cVectorPosition & vPosition,
		const unsigned int uiPropertyType ) const{

	if ( vPosition.getNumberOfElements() == 0 ){
		//background point
		if ( ! bBackgroundColorExists ){
			//no background -> no background properties
			return cVectorProperty( cTypeProperty::NONE );
		}
		const unsigned char * pEntry = pBackgroundColor;
		
		if ( uiPropertyType == cTypeProperty::TRANSPARENCY ){
			//convert transparency to property vector
			cVectorProperty vecColorAlpha( cTypeProperty::TRANSPARENCY );
			vecColorAlpha.setValue( 1, *pEntry );
			return vecColorAlpha;
		}//else
		if ( uiPropertyType == cTypeProperty::COLOR_RGB ){
			pEntry++;
			//convert color to property vector
			cVectorProperty vecColorRGB( cTypeProperty::COLOR_RGB );
			vecColorRGB.setValue( 1, *pEntry );
			pEntry++;
			vecColorRGB.setValue( 2, *pEntry );
			pEntry++;
			vecColorRGB.setValue( 3, *pEntry );
			return vecColorRGB;
		}
		return cVectorProperty( cTypeProperty::NONE );
	}//else
	
	const longFib lPositionX = fib::roundToLongFib(
		vPosition.getValue( 1 ) );
	const longFib lPositionY = fib::roundToLongFib(
		vPosition.getValue( 2 ) );
	
	if ( ( lPositionX < 0 ) || ( lPositionY < 0 ) ){
		//index (position) invalid (negativ)
		return cVectorProperty( cTypeProperty::NONE );
	}
	return getProperty( lPositionX, lPositionY, uiPropertyType );
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
cVectorProperty cEvalueSimpleRGBA255::getProperty(
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiPropertyType ) const{

	//normal point
	if ( ( uiBorderIndexX <= uiPositionX ) || ( uiBorderIndexY <= uiPositionY ) ){
		//point not in image
		return cVectorProperty( cTypeProperty::NONE );
	}
	
	const unsigned char * pEntry = pImageData +
		( ( uiPositionX * uiBorderIndexY + uiPositionY ) * 4 );
	
	if ( uiPropertyType == cTypeProperty::COLOR_RGB ){
		pEntry++;
		//convert color to property vector
		cVectorProperty vecColorRGB( cTypeProperty::COLOR_RGB );
		vecColorRGB.setValue( 1, *pEntry );
		pEntry++;
		vecColorRGB.setValue( 2, *pEntry );
		pEntry++;
		vecColorRGB.setValue( 3, *pEntry );
		return vecColorRGB;
	}//else
	if ( uiPropertyType == cTypeProperty::TRANSPARENCY ){
		//convert transparency to property vector
		cVectorProperty vecColorAlpha( cTypeProperty::TRANSPARENCY );
		vecColorAlpha.setValue( 1, *pEntry );
		return vecColorAlpha;
	}//else
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
cVectorProperty cEvalueSimpleRGBA255::getPropertyForNumber(
		const cVectorPosition & vPosition,
		const unsigned int uiPropertyNumber ) const{

	if ( vPosition.getNumberOfElements() == 0 ){
		//background point
		if ( ! bBackgroundColorExists ){
			//no background -> no background properties
			return cVectorProperty( cTypeProperty::NONE );
		}
		const unsigned char * pEntry = pBackgroundColor;
		
		if ( uiPropertyNumber == 1 ){
			//convert transparency to property vector
			cVectorProperty vecColorAlpha( cTypeProperty::TRANSPARENCY );
			vecColorAlpha.setValue( 1, *pEntry );
			return vecColorAlpha;
		}//else
		if ( uiPropertyNumber == 2 ){
			pEntry++;
			//convert color to property vector
			cVectorProperty vecColorRGB( cTypeProperty::COLOR_RGB );
			vecColorRGB.setValue( 1, *pEntry );
			pEntry++;
			vecColorRGB.setValue( 2, *pEntry );
			pEntry++;
			vecColorRGB.setValue( 3, *pEntry );
			return vecColorRGB;
		}
		return cVectorProperty( cTypeProperty::NONE );
	}//else
	
	const longFib lPositionX = fib::roundToLongFib(
		vPosition.getValue( 1 ) );
	const longFib lPositionY = fib::roundToLongFib(
		vPosition.getValue( 2 ) );
	
	if ( ( lPositionX < 0 ) || ( lPositionY < 0 ) ){
		//index (position) invalid (negativ)
		return cVectorProperty( cTypeProperty::NONE );
	}
	return getPropertyForNumber( lPositionX, lPositionY, uiPropertyNumber );
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
cVectorProperty cEvalueSimpleRGBA255::getPropertyForNumber(
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiPropertyNumber ) const{

	//normal point
	if ( ( uiBorderIndexX <= uiPositionX ) || ( uiBorderIndexY <= uiPositionY ) ){
		//point not in image
		return cVectorProperty( cTypeProperty::NONE );
	}
	
	const unsigned char * pEntry = pImageData +
		( ( uiPositionX * uiBorderIndexY + uiPositionY ) * 4 );
	
	if ( uiPropertyNumber == 1 ){
		//convert transparency value to property vector
		cVectorProperty vecColorAlpha( cTypeProperty::TRANSPARENCY );
		vecColorAlpha.setValue( 1, *pEntry );
		return vecColorAlpha;
	}//else
	if ( uiPropertyNumber == 2 ){
		pEntry++;
		//convert color RGB to property vector
		cVectorProperty vecColorRGB( cTypeProperty::COLOR_RGB );
		vecColorRGB.setValue( 1, *pEntry );
		pEntry++;
		vecColorRGB.setValue( 2, *pEntry );
		pEntry++;
		vecColorRGB.setValue( 3, *pEntry );
		return vecColorRGB;
	}//else
	return cVectorProperty( cTypeProperty::NONE );
}


/**
 * This method returns a empty matrix for storing the derivate of this
 * matrix to.
 * With this method child classes of this class can use the same
 * evalueDerivate() method and overwrite this method for the respectivly
 * cMatrix3DInteger child they need for their derivation.
 *
 * @see evalueDerivate()
 * @param uiMaxIndexX the maximal index for the first (1. or x)
 * 	dimension for the to create martrix; All index values in the
 * 	first (1. or x) dimension are positiv (including 0) natural numbers
 * 	lower equal uiMaxIndexX .
 * 	@see uiBorderIndexX
 * @param uiMaxIndexY the maximal index for the second (2. or y)
 * 	dimension for the to create martrix; All index values in the
 * 	second (2. or y) dimension are positiv (including 0) natural numbers
 * 	lower equal uiMaxIndexY .
 * 	@see uiBorderIndexY
 * @param uiMaxIndexZ the maximal index for the third (3. or z)
 * 	dimension for the to create martrix; All index values in the
 * 	third (3. or z) dimension are positiv (including 0) natural numbers
 * 	lower equal uiMaxIndexZ .
 * 	@see uiBorderIndexZ
 * @return a pointer to the cMatrix3DInteger (or child of it) matrix with
 * 	the given size, to store the derivate of this matrix to
 * 	Beware: You have to care that the returnd object is deleted.
 */
cMatrix3DInteger * cEvalueSimpleRGBA255::getEmptyMatrixForDerivate(
		const unsigned int uiMaxIndexX, const unsigned int uiMaxIndexY,
		const unsigned int uiMaxIndexZ ) const{
	
	return new cMatrix3DInteger( uiMaxIndexX, uiMaxIndexY, uiMaxIndexZ, 9 );
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
doubleFib cEvalueSimpleRGBA255::getDifference(
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
doubleFib cEvalueSimpleRGBA255::getDifference(
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
cVectorProperty cEvalueSimpleRGBA255::getProperty(
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
cVectorProperty cEvalueSimpleRGBA255::getPropertyForNumber(
		const pair< unsigned int, unsigned int> & position,
		const unsigned int uiPropertyNumber ) const{
	
	return getPropertyForNumber( position.first, position.second, uiPropertyNumber );
}




