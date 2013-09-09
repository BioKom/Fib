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
24.02.2013  Oesterholz  clone method and copy constructor added
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
 * @param uiInMaxX the maximum value for the first (x) dimension @see uiBorderIndexX
 * @param uiInMaxY the maximum value for the second (y) dimension @see uiBorderIndexY
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
 * copy constructor
 *
 * @param evalueSimpleRGBA255 the cEvalueSimpleRGBA255Scaled to copy
 */
cEvalueSimpleRGBA255Scaled::cEvalueSimpleRGBA255Scaled(
		const cEvalueSimpleRGBA255Scaled & evalueSimpleRGBA255 ):
			cEvalueSimpleRGBA255( evalueSimpleRGBA255 ),
			dScalingFactorAlpha( evalueSimpleRGBA255.dScalingFactorAlpha ),
			dScalingFactorRed( evalueSimpleRGBA255.dScalingFactorRed ),
			dScalingFactorGreen( evalueSimpleRGBA255.dScalingFactorGreen ),
			dScalingFactorBlue( evalueSimpleRGBA255.dScalingFactorBlue ){
	//nothing to do;
}


/**
 * destructor
 */
cEvalueSimpleRGBA255Scaled::~cEvalueSimpleRGBA255Scaled(){
	//nothing to do
}


/**
 * @return the name of this class
 */
string cEvalueSimpleRGBA255Scaled::getName() const{
	
	return "cEvalueSimpleRGBA255Scaled";
}


/**
 * This method clones this object.
 *
 * @return a pointer to the clone of this object
 */
cEvalueSimpleRGBA255Scaled * cEvalueSimpleRGBA255Scaled::clone() const{
	
	return new cEvalueSimpleRGBA255Scaled( *this );
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
		
		if ( ( lX < 0 ) || ( uiBorderIndexX <= lX ) ){
			//point not in image
			return false;
		}
		const longFib lY = fib::roundToLongFib( vPosition.getValue( 2 ) );
		if ( ( lY < 0 ) || ( uiBorderIndexY <= lY ) ){
			//point not in image
			return false;
		}
		
		pEntry = pImageData + ( ( lX * uiBorderIndexY  + lY ) * 4 );
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
		
		if ( ( lX < 0 ) || ( uiBorderIndexX <= lX ) ){
			//point not in image
			return list<cVectorProperty>();
		}
		const longFib lY = fib::roundToLongFib( vPosition.getValue( 2 ) );
		if ( ( lY < 0 ) || ( uiBorderIndexY <= lY ) ){
			//point not in image
			return list<cVectorProperty>();
		}
		
		pEntry = pImageData + ( ( lX * uiBorderIndexY  + lY ) * 4 );
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
iMatrix3D::tErrorValue cEvalueSimpleRGBA255Scaled::setValue( const doubleFib dValue,
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiChanel ){
	
	longFib lValue = -1;
	if ( uiChanel == 0 ){
		//value is transparency value
		lValue = roundToLongFib( dValue * dScalingFactorAlpha );
	}else if ( uiChanel == 1 ){
		//value is red color value
		lValue = roundToLongFib( dValue * dScalingFactorRed );
	}else if ( uiChanel == 2 ){
		//value is green color value
		lValue = roundToLongFib( dValue * dScalingFactorGreen );
	}else if ( uiChanel == 3 ){
		//value is blue color value
		lValue = roundToLongFib( dValue * dScalingFactorBlue );
	}else{
		return ERROR_OUTSIDE_INDEX_DIMENSION_3;
	}
	if ( lValue < 0 ){
		return ERROR_LOWER_MIN_VALUE;
	}
	return setValueUInt( lValue, uiPositionX, uiPositionY, uiChanel );
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
iMatrix3D::tErrorValue cEvalueSimpleRGBA255Scaled::setValue( const longFib lValue,
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiChanel ){
	
	return setValue( doubleFib( lValue ), uiPositionX, uiPositionY, uiChanel );
}


/**
 * With this method a unscaled integer value for a matrix element is set.
 *
 * @param uiValue the value to set
 * @param uiPositionX the index on the first (x) dimension where to set
 * 	the value dValue
 * @param uiPositionY the index on the second (y) dimension where to set
 * 	the value dValue
 * @param uiChanel the index for the property chanel;
 * 	the chanels are: 0 = alpha, 1 = red; 2 = green, 3 = blue
 * @return OK (or 0) if the value could be set, else the error value
 * 	@see tErrorValue
 */
iMatrix3D::tErrorValue cEvalueSimpleRGBA255Scaled::setValueUInt(
		const unsigned int uiValue,
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
	if ( 255 < uiValue ){
		//value outside range
		return ERROR_GREATER_MAX_VALUE;
	}
	const unsigned char ucValue = ((unsigned char)uiValue);
	
	unsigned char * pEntry = pImageData +
		( ( uiPositionX * uiBorderIndexY  + uiPositionY ) * 4 ) + uiChanel;
	
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
doubleFib cEvalueSimpleRGBA255Scaled::getValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	

	if ( uiChanel == 0 ){
		//return transparency value
		return doubleFib( getValueUInt( uiPositionX, uiPositionY,
			uiChanel ) ) / dScalingFactorAlpha;
	}else if ( uiChanel == 1 ){
		//return red color value
		return doubleFib( getValueUInt( uiPositionX, uiPositionY,
			uiChanel ) ) / dScalingFactorRed;
	}else if ( uiChanel == 2 ){
		//return green color value
		return doubleFib( getValueUInt( uiPositionX, uiPositionY,
			uiChanel ) ) / dScalingFactorGreen;
	}else if ( uiChanel == 3 ){
		//return blue color value
		return doubleFib( getValueUInt( uiPositionX, uiPositionY,
			uiChanel ) ) / dScalingFactorBlue;
	}
	return 0;
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
doubleFib cEvalueSimpleRGBA255Scaled::getMinValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	
	return 0.0;
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
doubleFib cEvalueSimpleRGBA255Scaled::getMaxValue( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	
	const doubleFib dMaxValue = getMaxValueUInt();
	
	if ( uiChanel == 0 ){
		//return maximal transparency value
		return dMaxValue / dScalingFactorAlpha;
	}else if ( uiChanel == 1 ){
		//return maximal red color value
		return dMaxValue / dScalingFactorRed;
	}else if ( uiChanel == 2 ){
		//return maximal green color value
		return dMaxValue / dScalingFactorGreen;
	}else if ( uiChanel == 3 ){
		//return maximal blue color value
		return dMaxValue / dScalingFactorBlue;
	}
	return 0.0;
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
doubleFib cEvalueSimpleRGBA255Scaled::getMinDifference( const unsigned int uiPositionX,
		const unsigned int uiPositionY, const unsigned int uiChanel ) const{
	
	if ( uiChanel == 0 ){
		//return maximal transparency value
		return 1.0 / dScalingFactorAlpha;
	}else if ( uiChanel == 1 ){
		//return maximal red color value
		return 1.0 / dScalingFactorRed;
	}else if ( uiChanel == 2 ){
		//return maximal green color value
		return 1.0 / dScalingFactorGreen;
	}else if ( uiChanel == 3 ){
		//return maximal blue color value
		return 1.0 / dScalingFactorBlue;
	}
	return 0.0;
}


/**
 * This method checks if the given matrix is equal to this matrix.
 *
 * @param matrix the matrix, which should be equal to this matrix
 * @return true if the given matrix is equal to this matrix, else false
 */
bool cEvalueSimpleRGBA255Scaled::equal( const iMatrix3D &matrix ) const{
	
	if ( getName() != matrix.getName() ){
		//not the correct matrix type
		return false;
	}
	const cEvalueSimpleRGBA255Scaled * pOtherRGBA255 =
		dynamic_cast<const cEvalueSimpleRGBA255Scaled*>(&matrix);
	if ( ( dScalingFactorAlpha != pOtherRGBA255->dScalingFactorAlpha ) ||
			( dScalingFactorRed != pOtherRGBA255->dScalingFactorRed ) ||
			( dScalingFactorGreen != pOtherRGBA255->dScalingFactorGreen ) ||
			( dScalingFactorBlue != pOtherRGBA255->dScalingFactorBlue ) ){
		//the image data don't have the same size
		return false;
	}
	return cEvalueSimpleRGBA255::equal( matrix );
}



/**
 * This method returns an empty matrix for storing the derivate of this
 * matrix to.
 * With this method child classes of the cEvalueSimpleRGBA255 class can
 * use the same evalueDerivate() method and overwrite this method for the
 * respectivly cMatrix3DInteger child they need for their derivation.
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
 * @param uiBitsPerValue The bits per integer entry value in the created matrix.
 * 	The entry values in the matrix are in the range from
 * 	-1 * 2^(uiBitsPerEntry - 1) to 2^(uiBitsPerEntry - 1) - 1 .
 * 	@see uiBitsPerEntry
 * @return a pointer to the cMatrix3DIntegerScaledDim3 (or child of it) matrix with
 * 	the given size, to store the derivate of this matrix to
 * 	Beware: You have to care that the returnd object is deleted.
 */
cMatrix3DIntegerScaledDim3 * cEvalueSimpleRGBA255Scaled::getEmptyMatrixForDerivate(
		const unsigned int uiMaxIndexX, const unsigned int uiMaxIndexY,
		const unsigned int uiMaxIndexZ, const unsigned int uiBitsPerValue ) const{
	
	vector< doubleFib > vecScalingFactorsDim3;
	vecScalingFactorsDim3.push_back( 1.0 / dScalingFactorAlpha );
	vecScalingFactorsDim3.push_back( 1.0 / dScalingFactorRed );
	vecScalingFactorsDim3.push_back( 1.0 / dScalingFactorGreen );
	
	if ( 2 < uiMaxIndexZ ){
		//third chanel (= third z index) also needed
		vecScalingFactorsDim3.push_back( 1.0 / dScalingFactorBlue );
	}
	return new cMatrix3DIntegerScaledDim3( uiMaxIndexX, uiMaxIndexY, uiMaxIndexZ,
		uiBitsPerValue, vecScalingFactorsDim3 );
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
 * 	properties of the first and second point
 */
doubleFib cEvalueSimpleRGBA255Scaled::getDifference(
		const unsigned int uiPosition1X, const unsigned int uiPosition1Y,
		const unsigned int uiPosition2X, const unsigned int uiPosition2Y ) const{
	
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
	double dDifference = dScalingFactorAlpha * ((double)
		( ucValue1_1 < ucValue1_2 ) ?
			( ucValue1_2 - ucValue1_1 ): ( ucValue1_1 - ucValue1_2 ) );
	
	pEntry1++;
	pEntry2++;
	const unsigned char & ucValue2_1 = (*pEntry1);
	const unsigned char & ucValue2_2 = (*pEntry2);
	dDifference += dScalingFactorRed * ((double)
		( ucValue2_1 < ucValue2_2 ) ?
			( ucValue2_2 - ucValue2_1 ): ( ucValue2_1 - ucValue2_2 ) );
	
	pEntry1++;
	pEntry2++;
	const unsigned char & ucValue3_1 = (*pEntry1);
	const unsigned char & ucValue3_2 = (*pEntry2);
	dDifference += dScalingFactorGreen * ((double)
		( ucValue3_1 < ucValue3_2 ) ?
		 ( ucValue3_2 - ucValue3_1 ): ( ucValue3_1 - ucValue3_2 ) );
	
	pEntry1++;
	pEntry2++;
	const unsigned char & ucValue4_1 = (*pEntry1);
	const unsigned char & ucValue4_2 = (*pEntry2);
	dDifference += dScalingFactorBlue * ((double)
		( ucValue4_1 < ucValue4_2 ) ?
			( ucValue4_2 - ucValue4_1 ): ( ucValue4_1 - ucValue4_2 ) );
	
	return dDifference;
}


/**
 * This method evalues the difference of two points properties.
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
 * 	difference of (e. g. cTypeProperty::COLOR_RGB ) @see cTypeProperty
 * @return the sum of distances betwean the vector elements of the
 * 	third dimension of the property of the first and second point
 */
doubleFib cEvalueSimpleRGBA255Scaled::getDifference(
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
		double dDifference = dScalingFactorRed * ((doubleFib)(
			( ucValue2_1 < ucValue2_2 ) ?
				( ucValue2_2 - ucValue2_1 ): ( ucValue2_1 - ucValue2_2 ) ) );
		
		pEntry1++;
		pEntry2++;
		const unsigned char & ucValue3_1 = (*pEntry1);
		const unsigned char & ucValue3_2 = (*pEntry2);
		dDifference += dScalingFactorGreen *  ((doubleFib)(
			( ucValue3_1 < ucValue3_2 ) ?
				( ucValue3_2 - ucValue3_1 ): ( ucValue3_1 - ucValue3_2 ) ) );
		
		pEntry1++;
		pEntry2++;
		const unsigned char & ucValue4_1 = (*pEntry1);
		const unsigned char & ucValue4_2 = (*pEntry2);
		dDifference += dScalingFactorBlue *  ((doubleFib)(
			( ucValue4_1 < ucValue4_2 ) ?
				( ucValue4_2 - ucValue4_1 ): ( ucValue4_1 - ucValue4_2 ) ) );
		return dDifference;
	}//else
	if ( uiPropertyType == cTypeProperty::TRANSPARENCY ){
		const unsigned char & ucValue1 = (*pEntry1);
		const unsigned char & ucValue2 = (*pEntry2);
		return dScalingFactorAlpha * ((doubleFib)( ucValue1 < ucValue2 ) ?
			( ucValue2 - ucValue1 ): ( ucValue1 - ucValue2 ) );
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
cVectorProperty cEvalueSimpleRGBA255Scaled::getProperty(
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
			vecColorAlpha.setValue( 1, dScalingFactorAlpha * ((double)(*pEntry)) );
			return vecColorAlpha;
		}//else
		if ( uiPropertyType == cTypeProperty::COLOR_RGB ){
			pEntry++;
			//convert color to property vector
			cVectorProperty vecColorRGB( cTypeProperty::COLOR_RGB );
			vecColorRGB.setValue( 1, dScalingFactorRed * ((double)(*pEntry)) );
			pEntry++;
			vecColorRGB.setValue( 2, dScalingFactorGreen * ((double)(*pEntry)) );
			pEntry++;
			vecColorRGB.setValue( 3, dScalingFactorBlue * ((double)(*pEntry)) );
			return vecColorRGB;
		}
		return cVectorProperty( cTypeProperty::NONE );
	}
	
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
cVectorProperty cEvalueSimpleRGBA255Scaled::getProperty(
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiPropertyType ) const{

	//normal point
	if ( ( uiBorderIndexX <= uiPositionX ) || ( uiBorderIndexY <= uiPositionY ) ){
		//point not in image
		return cVectorProperty( cTypeProperty::NONE );
	}
	
	const unsigned char * pEntry =
		pImageData + ( ( uiPositionX * uiBorderIndexY + uiPositionY ) * 4 );
	
	if ( uiPropertyType == cTypeProperty::COLOR_RGB ){
		pEntry++;
		//convert color to property vector
		cVectorProperty vecColorRGB( cTypeProperty::COLOR_RGB );
		vecColorRGB.setValue( 1, dScalingFactorRed * ((double)(*pEntry)) );
		pEntry++;
		vecColorRGB.setValue( 2, dScalingFactorGreen * ((double)(*pEntry)) );
		pEntry++;
		vecColorRGB.setValue( 3, dScalingFactorBlue * ((double)(*pEntry)) );
		return vecColorRGB;
	}//else
	if ( uiPropertyType == cTypeProperty::TRANSPARENCY ){
		//convert transparency to property vector
		cVectorProperty vecColorAlpha( cTypeProperty::TRANSPARENCY );
		vecColorAlpha.setValue( 1, dScalingFactorAlpha * ((double)(*pEntry)) );
		return vecColorAlpha;
	}
	
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
cVectorProperty cEvalueSimpleRGBA255Scaled::getPropertyForNumber(
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
			vecColorAlpha.setValue( 1, dScalingFactorAlpha * ((double)(*pEntry)) );
			return vecColorAlpha;
		}//else
		if ( uiPropertyNumber == 2 ){
			pEntry++;
			//convert color to property vector
			cVectorProperty vecColorRGB( cTypeProperty::COLOR_RGB );
			vecColorRGB.setValue( 1, dScalingFactorRed * ((double)(*pEntry)) );
			pEntry++;
			vecColorRGB.setValue( 2, dScalingFactorGreen * ((double)(*pEntry)) );
			pEntry++;
			vecColorRGB.setValue( 3, dScalingFactorBlue * ((double)(*pEntry)) );
			return vecColorRGB;
		}//else
		return cVectorProperty( cTypeProperty::NONE );
	}
	
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
cVectorProperty cEvalueSimpleRGBA255Scaled::getPropertyForNumber(
		const unsigned int uiPositionX, const unsigned int uiPositionY,
		const unsigned int uiPropertyNumber ) const{

	//normal point
	if ( ( uiBorderIndexX <= uiPositionX ) || ( uiBorderIndexY <= uiPositionY ) ){
		//point not in image
		return cVectorProperty( cTypeProperty::NONE );
	}
	
	const unsigned char * pEntry =
		pImageData + ( ( uiPositionX * uiBorderIndexY + uiPositionY ) * 4 );
	
	if ( uiPropertyNumber == 1 ){
		//convert transparency to property vector
		cVectorProperty vecColorAlpha( cTypeProperty::TRANSPARENCY );
		vecColorAlpha.setValue( 1, dScalingFactorAlpha * ((double)(*pEntry)) );
		return vecColorAlpha;
	}//else
	if ( uiPropertyNumber == 2 ){
		pEntry++;
		//convert color to property vector
		cVectorProperty vecColorRGB( cTypeProperty::COLOR_RGB );
		vecColorRGB.setValue( 1, dScalingFactorRed * ((double)(*pEntry)) );
		pEntry++;
		vecColorRGB.setValue( 2, dScalingFactorGreen * ((double)(*pEntry)) );
		pEntry++;
		vecColorRGB.setValue( 3, dScalingFactorBlue * ((double)(*pEntry)) );
		return vecColorRGB;
	}//else
	
	return cVectorProperty( cTypeProperty::NONE );
}










