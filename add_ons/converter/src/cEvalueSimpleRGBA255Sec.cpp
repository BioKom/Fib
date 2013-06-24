/**
 * @file cEvalueSimpleRGBA255Sec
 * file name: cEvalueSimpleRGBA255Sec.cpp
 * @author Betti Oesterholz
 * @date 27.04.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class limits the evaluation time of the class @see cEvalueSimpleRGBA255.
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
 * This class limits the evaluation time of the class @see cEvalueSimpleRGBA255.
 */
/*
History:
27.04.2013  Oesterholz  created
*/


#include "cEvalueSimpleRGBA255Sec.h"

#include <iostream>


using namespace fib;


/**
 * standard constructor
 *
 * @param uiInMaxX the maximum value for the first (x) dimension @see uiMaxX
 * @param uiInMaxY the maximum value for the second (y) dimension @see uiMaxY
 * @param ulInMaxEvaluationTimeInSec the maximal time for evaluation in
 * 	seconds, till the creation of this object (if 0 time is unlimeted)
 * 	@see ulMaxEvaluationTimeInSec
 * @param pInPathForFileToStoreIntermediateResultImage the path wher to
 * 	store the intermediate result picture, if NULL non is stored
 * @param ulInSecoundsBetweanIntermediateResultSaves every which
 * 	seconds to store the intermediate result picture
 */
cEvalueSimpleRGBA255Sec::cEvalueSimpleRGBA255Sec( const unsigned int uiInMaxX, const unsigned int uiInMaxY,
		unsigned long ulInMaxEvaluationTimeInSec,
		const char * pInPathForFileToStoreIntermediateResultImage,
		unsigned long ulInSecoundsBetweanIntermediateResultSaves ):
		cEvalueSimpleRGBA255( uiInMaxX, uiInMaxY ),
		lMaxEvaluationTimeInSec( ulInMaxEvaluationTimeInSec ),
		tmStartTime( time( NULL ) )
#ifdef FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE
		,szPathForFileToStoreIntermediateResultImage(""),
		lSecoundsBetweanIntermediateResultSaves(
			( pInPathForFileToStoreIntermediateResultImage != NULL ) ?
				ulInSecoundsBetweanIntermediateResultSaves : -1 ){
	
	if ( pInPathForFileToStoreIntermediateResultImage ){
		szPathForFileToStoreIntermediateResultImage = string(
			pInPathForFileToStoreIntermediateResultImage );
	}
	tmNextIntermediateResultTime = tmStartTime + lSecoundsBetweanIntermediateResultSaves;
}
#else //FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE
{//nothing to do
}
#endif //FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE


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
 * @see cEvalueSimpleRGBA255::evaluePosition()
 * @see pImageData
 * @param vPosition the position of the point, which is evalued
 * @param vProperties a list of the properties of the point
 */
bool cEvalueSimpleRGBA255Sec::evaluePosition( const cVectorPosition & vPosition,
	const list<cVectorProperty> & vProperties ){
	
	const bool bPointEvalued = cEvalueSimpleRGBA255::
		evaluePosition( vPosition, vProperties );
	
	if ( ( lMaxEvaluationTimeInSec != 0 ) &&
			( lMaxEvaluationTimeInSec < ( time( NULL ) - tmStartTime ) ) ){
		//max time reached
		return false;
	}
#ifdef FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE
	checkIntervallToSaveCurrentPicture();
#endif //FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE
	
	return bPointEvalued;
}


#ifdef FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE
/**
 * This method stores the current picture, if it should be stored.
 */
void cEvalueSimpleRGBA255Sec::checkIntervallToSaveCurrentPicture(){
	
	if ( ( 0 <= lSecoundsBetweanIntermediateResultSaves ) &&
			( tmNextIntermediateResultTime <= time( NULL ) ) ){
		//save actual (intermediate result) picture
		fipImage * pCovertedObject = convertToFipImage();
		
		if ( pCovertedObject ){
			//output the multimedia object
			
			/*cout<<"Saving the intermediate result multimedia object to the file \""<<
				szPathForFileToStoreIntermediateResultImage <<"\" . "<<endl;*/
			const bool bObjectConverted = pCovertedObject->save( szPathForFileToStoreIntermediateResultImage.c_str() );
			if ( ! bObjectConverted ){
				cerr<<"Error: Couldn't save to the file \""<< szPathForFileToStoreIntermediateResultImage <<"\" ." <<endl;
			}
			delete pCovertedObject;
		}else{
			cerr<<"Error: Could not convert the data into a multimedia object."<<endl;
		}
		
		tmNextIntermediateResultTime = time( NULL ) +
			lSecoundsBetweanIntermediateResultSaves;
	}
}
#endif //FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE

/**
 * This method converts the data of this class to the @see fipImage
 * format and stores it into a returned fipImage object.
 * (Beware: The background color will be added to the points with
 * colorWithBackgroundColor() .)
 *
 * @see cEvalueSimpleRGBA255::colorWithBackgroundColor()
 * @return a pointer to the fipImage, wher the data was store
 * 	(please delete it after usage)
 */
fipImage * cEvalueSimpleRGBA255Sec::convertToFipImage(){
	
	const unsigned int uiMaxX = getMaxIndex( 0 ) + 1;
	const unsigned int uiMaxY = getMaxIndex( 1 ) + 1;
	
	fipImage * pFipImage = new fipImage( FIT_BITMAP, uiMaxX, uiMaxY, 32 );
	pFipImage->setTransparent( true );
	
	RGBQUAD * pColorValue = new RGBQUAD();
	if ( bBackgroundColorExists ){
		//set background color
		pColorValue->rgbReserved = pBackgroundColor[ 0 ];
		pColorValue->rgbRed   = pBackgroundColor[ 1 ];
		pColorValue->rgbGreen = pBackgroundColor[ 2 ];
		pColorValue->rgbBlue  = pBackgroundColor[ 3 ];
		
//TODO dosn't work correct
//				const bool bBkColorSet =
//					pFipImage->setFileBkColor( pColorValue, FI_COLOR_IS_RGBA_COLOR );
			pFipImage->setFileBkColor( pColorValue );
		
		colorWithBackgroundColor();
	}
	//set the color values of the points
	const unsigned char * pEntry = pImageData;
	for ( unsigned int uiX = 0; uiX < uiMaxX; uiX++ ){
		for ( unsigned int uiY = 0; uiY < uiMaxY; uiY++ ){
			//set color values
			pColorValue->rgbReserved = *pEntry;
			pEntry++;
			pColorValue->rgbRed   = *pEntry;
			pEntry++;
			pColorValue->rgbGreen = *pEntry;
			pEntry++;
			pColorValue->rgbBlue  = *pEntry;
			pEntry++;
			
			pFipImage->setPixelColor( uiX, uiY, pColorValue );
		}
	}//end for set all pixel values
	delete pColorValue;
	
	return pFipImage;
}


