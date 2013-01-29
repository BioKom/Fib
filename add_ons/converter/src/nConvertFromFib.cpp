/**
 * @file nConvertFromFib
 * file name: nConvertFromFib.h
 * @author Betti Oesterholz
 * @date 25.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions with which multimediaobjects in the fib
 * multimediaformats can be converted into other multimediaformats.
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This header specifies functions with which multimediaobjects in the fib
 * multimediaformats can be converted into other multimediaformats.
 *
 */
/*
History:
25.02.2010  Oesterholz  created
11.05.2010  Oesterholz  max time for evaluation included
17.11.2010  Oesterholz  FEATURE_FROM_FIB_BITS_PER_RGB_COLOR_VALUE added;
	ulCountOutputValues changed to ulMaxOutputValues (less subtracting 1)
01.12.2011  Oesterholz  rounding dimension positions values
01.12.2011  Oesterholz  changes for: cDomainVector has as elements now
	cDomain and not cDomainSingle 
22.03.2012  Oesterholz  possibility to decode image with transparency
	implemented ( with the help of cEvalueSimpleRGBA255 )
23.10.2012  Oesterholz  changes to store intermediate result
28.01.2013  Oesterholz  COLOR_SW changed to COLOR_GRAYSCALE
*/

//TODO for testing
#define DEBUG
//#define TEST_OUTPUT

#include "nConvertFromFib.h"

#include "cRoot.h"
#include "cPoint.h"
#include "cList.h"
#include "cProperty.h"
#include "cTypeProperty.h"
#include "cTypeDimension.h"
#include "cVectorProperty.h"
#include "cVectorPosition.h"
#include "cDomainIntegerBasis.h"
#include "cDomainNaturalNumber.h"
#include "cDomainVector.h"
#include "cDomainVectorBasis.h"
#include "cEvaluePositionListMemLimit.h"
#include "cEvalueSimpleRGBA255.h"


#include <ctime>

#ifdef TEST_OUTPUT
	#include <iostream>
	#include <fstream>
#endif


using namespace nConvertFromFib;



/**
 * @class cEvaluePositionListMemLimitSec This class limits the
 * evaluation time.
 */
class cEvaluePositionListMemLimitSec: public cEvaluePositionListMemLimit{
public:
	
	/**
	 * the maximal time for evaluation in seconds, till the creation of
	 * this object
	 */
	long lMaxEvaluationTimeInSec;
	
	/**
	 * the time this object was created
	 */
	time_t tmStartTime;
	
	/**
	 * standard constructor
	 *
	 * @param ulInMaximalPointsAddToList The number of positions, which
	 * 	should be added to the positionslist, befor it is sorted and
	 * 	reduced. (@see ulMaximalPointsAddToList)
	 * @param pInVecDomainDimension The dimension domain for the positions.
	 * 	No position outside this domain will be added.
	 * 	If NULL no check will be executed. (@see pVecDomainDimension)
	 * @param ulInMaxEvaluationTimeInSec the maximal time for evaluation in
	 * 	seconds, till the creation of this object (if 0 time is unlimeted)
	 * 	@see ulMaxEvaluationTimeInSec
	 * @param bInDeleteEmptyPoints if true points without properties will be
	 * 	deleted when the positionslist is reduced, else (if false) points
	 * 	without properties won't be deleted (@see bDeleteEmptyPoints)
	 */
	cEvaluePositionListMemLimitSec( unsigned long long ulInMaximalPointsAddToList,
			const cDomainVectorBasis * pInVecDomainDimension = NULL,
			unsigned long ulInMaxEvaluationTimeInSec = 0,
			bool bInDeleteEmptyPoints = true ):
			cEvaluePositionListMemLimit( ulInMaximalPointsAddToList,
				pInVecDomainDimension, bInDeleteEmptyPoints ),
			lMaxEvaluationTimeInSec( ulInMaxEvaluationTimeInSec ),
			tmStartTime( time( NULL ) ){
		//nothing to do
	}

	
	/**
	 * The method with wich the evalued points with ther properties are
	 * inserted. Everytime a point (to evalue) is reached in the
	 * evaluation, this method is called with the position and the
	 * properties of the point and stores the copies of this data
	 * to the end of the list @see liEvaluedPositionData .
	 *
	 * @see liEvaluedPositionData
	 * @param vPosition the position of the point, which is evalued
	 * @param vProperties a list of the properties of the point
	 */
	virtual bool evaluePosition( const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties ){
		
		const bool bPointEvalued = cEvaluePositionListMemLimit::
			evaluePosition( vPosition, vProperties );
		
		if ( ( lMaxEvaluationTimeInSec != 0 ) &&
				( lMaxEvaluationTimeInSec < ( time( NULL ) - tmStartTime ) ) ){
			//max time reached
			return false;
		}
		return bPointEvalued;
	}
	
};//end class cEvaluePositionListMemLimitSec




/**
 * @class cEvalueSimpleRGBA255Sec This class limits the evaluation time
 * of the class @see cEvalueSimpleRGBA255.
 */
class cEvalueSimpleRGBA255Sec: public cEvalueSimpleRGBA255{
public:
	
	/**
	 * the maximal time for evaluation in seconds, till the creation of
	 * this object
	 */
	long lMaxEvaluationTimeInSec;
	
	/**
	 * the time this object was created
	 */
	time_t tmStartTime;
	
	
#ifdef FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE
	/**
	 * The path wher to store the intermediate result picture.
	 */
	string szPathForFileToStoreIntermediateResultImage;
	
	/**
	 * Every which seconds to store the intermediate result picture.
	 */
	long lSecoundsBetweanIntermediateResultSaves;
	
	/**
	 * Time after which to store the next intermediate result.
	 */
	time_t tmNextIntermediateResultTime;
	
#endif //FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE
	
	
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
	cEvalueSimpleRGBA255Sec( const unsigned int uiInMaxX, const unsigned int uiInMaxY,
			unsigned long ulInMaxEvaluationTimeInSec = 0,
			const char * pInPathForFileToStoreIntermediateResultImage = NULL,
			unsigned long ulInSecoundsBetweanIntermediateResultSaves = 10 ):
			cEvalueSimpleRGBA255( uiInMaxX, uiInMaxY ),
			lMaxEvaluationTimeInSec( ulInMaxEvaluationTimeInSec ),
			tmStartTime( time( NULL ) )
#ifdef FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE
			, szPathForFileToStoreIntermediateResultImage(
				pInPathForFileToStoreIntermediateResultImage ),
			lSecoundsBetweanIntermediateResultSaves(
				( pInPathForFileToStoreIntermediateResultImage != NULL ) ? ulInSecoundsBetweanIntermediateResultSaves : -1 ){
		
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
	virtual bool evaluePosition( const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties ){
		
		const bool bPointEvalued = cEvalueSimpleRGBA255::
			evaluePosition( vPosition, vProperties );
		
		if ( ( lMaxEvaluationTimeInSec != 0 ) &&
				( lMaxEvaluationTimeInSec < ( time( NULL ) - tmStartTime ) ) ){
			//max time reached
			return false;
		}
		
#ifdef FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE
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
#endif //FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE
		
		return bPointEvalued;
	}
	
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
	fipImage * convertToFipImage(){
		
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
	
	
};//end class cEvalueSimpleRGBA255Sec



/**
 * This function converts the given multimediaobject into a Fib object.
 *
 * @param multimediaObject the Fib multimedaobject to convert into fib
 * @param ulMaxEvaluationTimeInSec the maximal time for evaluation in seconds
 * 	if 0 the evalue time is unbound
 * @param pOutStatus the output status of this method
 * 	possible values are:
 * 		0: everthing is ok
 * 		1: the ulMaxEvaluationTimeInSec was reached, the object was not
 * 			fully evalued
 * 		-1: an error occurrd
 * @param pPathForFileToStoreImage a string to the path wher to store the
 * 	actual picture, if the functionality for the file type exists, the
 * 	current evalued picture data will be saved to the file every
 * 	FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE seconds
 * 	@see cEvalueSimpleRGBA255Sec
 * @return the created FreeImagePlus object (please delete it after usage)
 * 	or NULL, if non could be created
 */
fipImage * nConvertFromFib::convertToFipImage( const cFibElement & fibMultimediaObject,
		unsigned long ulMaxEvaluationTimeInSec, int * pOutStatus,
		const char * pPathForFileToStoreImage ){
	
	DEBUG_OUT_L1( <<"nConvertFromFib::convertToFipImage() started"<<endl; );
	
	if ( pOutStatus ){
		*pOutStatus = 0;
	}
	/*evalue the size of the image and include a corresponding dimension
	domain in the root -element*/
	if ( fibMultimediaObject.getNumberOfDimensions() != 2 ){
		DEBUG_OUT_EL1( <<"Error: No 2 dimensional Fib object."<<endl; );
		if ( pOutStatus ){
			*pOutStatus = -1;
		}
		return NULL;
	}
	
	const unsignedIntFib dimensionMapping1 = fibMultimediaObject.getDimensionMapping( 1 );
	const unsignedIntFib dimensionMapping2 = fibMultimediaObject.getDimensionMapping( 2 );
	bool bDimensionXY = true;
	if ( ( dimensionMapping1 == cTypeDimension::DIRECTION_HORIZONTAL ) &&
			( dimensionMapping2 == cTypeDimension::DIRECTION_VERTICAL ) ){
		bDimensionXY = true;
	}else if ( ( dimensionMapping1 == cTypeDimension::DIRECTION_VERTICAL ) &&
			( dimensionMapping2 == cTypeDimension::DIRECTION_HORIZONTAL ) ){
		bDimensionXY = false;
	}else{
		DEBUG_OUT_EL1( <<"Error: Wrong Dimensionmappings ("<< dimensionMapping1 <<"; "<< dimensionMapping2 <<")."<<endl; );
		if ( pOutStatus ){
			*pOutStatus = -1;
		}
		return NULL;
	}
	
	cDomain * pDomainDimension = fibMultimediaObject.
		getValidDomains().getDomainForElement( cTypeDimension() );
	
	if ( pDomainDimension == NULL ){
		DEBUG_OUT_EL1( <<"Error: No dimension domain."<<endl; );
		if ( pOutStatus ){
			*pOutStatus = -1;
		}
		return NULL;
	}
	cDomainVectorBasis * pVecDomainDimension = (cDomainVectorBasis*)pDomainDimension;
	
	if ( pVecDomainDimension->getNumberOfElements() != 2 ){
		DEBUG_OUT_EL1( <<"Error: No 2 dimensional dimensiondomain in Fib object."<<endl; );
		if ( pOutStatus ){
			*pOutStatus = -1;
		}
		return NULL;
	}
	if ( ( ! pVecDomainDimension->getElementDomain( 1 )->isScalar() ) ||
			( ! pVecDomainDimension->getElementDomain( 2 )->isScalar() ) ){
		DEBUG_OUT_EL1( <<"Error: A dimension subdomain in the Fib object is not a scalar."<<endl; );
		if ( pOutStatus ){
			*pOutStatus = -1;
		}
		return NULL;
	}
	cDomainSingle * pDirection1Domain = (cDomainSingle*)(
		pVecDomainDimension->getElementDomain( 1 ) );
	cDomainSingle * pDirection2Domain = (cDomainSingle*)(
		pVecDomainDimension->getElementDomain( 2 ) );
	
	const doubleFib dDirection1Minimum = pDirection1Domain->getMinimum();
	const doubleFib dDirection1Maximum = pDirection1Domain->getMaximum();
	doubleFib dDirection1Scaling = 1.0;
	string szDomainElementType = pDirection1Domain->getType();
	if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
				(szDomainElementType.compare( 0, 13, "DomainInteger" ) == 0) ){
		//cDomainIntegerBasis
		dDirection1Scaling = ((cDomainIntegerBasis*)pDirection1Domain)->getScalingFactor();
	}
	const doubleFib dDirection2Minimum = pDirection2Domain->getMinimum();
	const doubleFib dDirection2Maximum = pDirection2Domain->getMaximum();
	doubleFib dDirection2Scaling = 1.0;
	szDomainElementType = pDirection2Domain->getType();
	if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
				(szDomainElementType.compare( 0, 13, "DomainInteger" ) == 0) ){
		//cDomainIntegerBasis
		dDirection2Scaling = ((cDomainIntegerBasis*)pDirection2Domain)->getScalingFactor();
	}
	
	const unsigned long ulWidth = (unsigned long)(
		(dDirection1Maximum - dDirection1Minimum) / dDirection1Scaling) + 1;
	const unsigned long ulHeight = (unsigned long)(
		(dDirection2Maximum - dDirection2Minimum) / dDirection2Scaling) + 1;
	
	DEBUG_OUT_L1( <<"image size width="<< ulWidth <<" (= (" << dDirection1Maximum <<" - "<< dDirection1Minimum<<") /" <<dDirection1Scaling<< " + 1)" );
	DEBUG_OUT_L1( <<" height="<< ulWidth <<" (= (" << dDirection2Maximum <<" - "<< dDirection2Minimum<<") /" <<dDirection2Scaling<< " + 1)"<<endl );
	
	//evalue transparency of the Fib object
	cTypeProperty typePropertyColorTransparency( cTypeProperty::TRANSPARENCY );
	
	cDomain * pDomainTransparency = fibMultimediaObject.
		getValidDomains().getDomainForElement( typePropertyColorTransparency );
	
	const bool bTransparencyUsed = (pDomainTransparency != NULL);
	doubleFib dMaxTransparencyValue = 0.0;
	doubleFib dMinTransparencyValue = 0.0;
	unsigned long ulCountTransparencyValues = 0;
	
	if ( bTransparencyUsed ){
		//get the values for the transparency
		cDomainVectorBasis * pVecDomainTransparency =
			(cDomainVectorBasis*)pDomainTransparency;
		
		cDomainSingle * pTransparencyDomain = (cDomainSingle*)(
				pVecDomainTransparency->getElementDomain( 1 ));
		
		dMinTransparencyValue = pTransparencyDomain->getMinimum();
		dMaxTransparencyValue = pTransparencyDomain->getMaximum();
		doubleFib dTransparencyScaling = 1.0;
		szDomainElementType = pTransparencyDomain->getType();
		if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
				(szDomainElementType.compare( 0, 13, "DomainInteger" ) == 0) ){
			//cDomainIntegerBasis
			dTransparencyScaling = ((cDomainIntegerBasis*)pTransparencyDomain)->
				getScalingFactor();
		}
		ulCountTransparencyValues =
			(unsigned long)( (dMaxTransparencyValue - dMinTransparencyValue) /
				dTransparencyScaling) + 1;
		
		DEBUG_OUT_L2( <<"Transparency used with min="<< dMinTransparencyValue <<" max=" << dMaxTransparencyValue <<" and count values="<< ulCountTransparencyValues<<" (scaling=" <<dTransparencyScaling<< ")"<<endl );
	}
	//evalue the color and colormode of the Fib object
	
	bool bColorRGB = true;
	unsigned int uiBitsPerPixel = 0;
	
	doubleFib dMaxRedValue = 0.0;
	doubleFib dMinRedValue = 0.0;
	unsigned long ulCountRedValues = 0;
	doubleFib dMaxGreenValue = 0.0;
	doubleFib dMinGreenValue = 0.0;
	unsigned long ulCountGreenValues = 0;
	doubleFib dMaxBlueValue = 0.0;
	doubleFib dMinBlueValue = 0.0;
	unsigned long ulCountBlueValues = 0;
	
	doubleFib dMaxGrayValue = 0.0;
	doubleFib dMinGrayValue = 0.0;
	unsigned long ulCountGrayValues = 0;
	
	unsigned long ulMaxOutputValues = 0;
	
	cTypeProperty typePropertyColorRgb( cTypeProperty::COLOR_RGB );
	cTypeProperty typePropertyColorSw( cTypeProperty::COLOR_GRAYSCALE );
	cDomain * pDomainColor = fibMultimediaObject.
		getValidDomains().getDomainForElement( typePropertyColorRgb );
	if ( pDomainColor != NULL ){
		bColorRGB = true;
		
		cDomainVectorBasis * pVecDomainColorRgb = (cDomainVectorBasis*)pDomainColor;
		
		if ( pVecDomainColorRgb->getNumberOfElements() != 3 ){
			DEBUG_OUT_EL1( <<"Error: No 3 elements in the color RGB domain in Fib object."<<endl; );
			if ( pOutStatus ){
				*pOutStatus = -1;
			}
			return NULL;
		}
		if ( ( ! pVecDomainColorRgb->getElementDomain( 1 )->isScalar() ) ||
				( ! pVecDomainColorRgb->getElementDomain( 2 )->isScalar() ) ||
				( ! pVecDomainColorRgb->getElementDomain( 3 )->isScalar() ) ){
			DEBUG_OUT_EL1( <<"Error: A color RGB subdomain in the Fib object is not a scalar."<<endl; );
			if ( pOutStatus ){
				*pOutStatus = -1;
			}
			return NULL;
		}
		cDomainSingle * pColorRedDomain   = (cDomainSingle*)(
			pVecDomainColorRgb->getElementDomain( 1 ) );
		cDomainSingle * pColorGreenDomain = (cDomainSingle*)(
			pVecDomainColorRgb->getElementDomain( 2 ) );
		cDomainSingle * pColorBlueDomain  = (cDomainSingle*)(
			pVecDomainColorRgb->getElementDomain( 3 ) );
		
		dMinRedValue = pColorRedDomain->getMinimum();
		dMaxRedValue = pColorRedDomain->getMaximum();
		doubleFib dColorRedScaling = 1.0;
		szDomainElementType = pColorRedDomain->getType();
		if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
					(szDomainElementType.compare( 0, 13, "DomainInteger" ) == 0) ){
			//cDomainIntegerBasis
			dColorRedScaling = ((cDomainIntegerBasis*)pColorRedDomain)->getScalingFactor();
		}
		ulCountRedValues = (unsigned long)( (dMaxRedValue - dMinRedValue) /
			dColorRedScaling) + 1;
		
		DEBUG_OUT_L2( <<"color red used with min="<< dMinRedValue <<" max=" << dMaxRedValue <<" and count values="<< ulCountRedValues<<" (scaling=" <<dColorRedScaling<< ")"<<endl );

		dMinGreenValue = pColorGreenDomain->getMinimum();
		dMaxGreenValue = pColorGreenDomain->getMaximum();
		doubleFib dColorGreenScaling = 1.0;
		szDomainElementType = pColorGreenDomain->getType();
		if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
					(szDomainElementType.compare( 0, 13, "DomainInteger" ) == 0) ){
			//cDomainIntegerBasis
			dColorGreenScaling = ((cDomainIntegerBasis*)pColorGreenDomain)->getScalingFactor();
		}
		ulCountGreenValues = (unsigned long)( (dMaxGreenValue -
			dMinGreenValue) / dColorGreenScaling) + 1;
		
		DEBUG_OUT_L2( <<"color green used with min="<< dMinGreenValue <<" max=" << dMaxGreenValue <<" and count values="<< ulCountGreenValues<<" (scaling=" <<dColorGreenScaling<< ")"<<endl );

		dMinBlueValue = pColorBlueDomain->getMinimum();
		dMaxBlueValue = pColorBlueDomain->getMaximum();
		doubleFib dColorBlueScaling = 1.0;
		szDomainElementType = pColorBlueDomain->getType();
		if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
					(szDomainElementType.compare( 0, 13, "DomainInteger" ) == 0) ){
			//cDomainIntegerBasis
			dColorBlueScaling = ((cDomainIntegerBasis*)pColorBlueDomain)->getScalingFactor();
		}
		ulCountBlueValues = (unsigned long)( (dMaxBlueValue - dMinBlueValue) /
			dColorBlueScaling) + 1;
		
		DEBUG_OUT_L2( <<"color blue used with min="<< dMinBlueValue <<" max=" << dMaxBlueValue <<" and count values="<< ulCountBlueValues<<" (scaling=" <<dColorBlueScaling<< ")"<<endl );
		
#ifdef FEATURE_FROM_FIB_BITS_PER_RGB_COLOR_VALUE

		ulMaxOutputValues = (1L << FEATURE_FROM_FIB_BITS_PER_RGB_COLOR_VALUE) - 1;
		
		uiBitsPerPixel = 3 * FEATURE_FROM_FIB_BITS_PER_RGB_COLOR_VALUE;
#else //FEATURE_FROM_FIB_BITS_PER_RGB_COLOR_VALUE
		//getPixel per bit
		uiBitsPerPixel = getDigits( std::max( ulCountRedValues,
			std::max( ulCountGreenValues, ulCountBlueValues ) ) );
		
		if ( uiBitsPerPixel <= 8 ){
			uiBitsPerPixel = 8;
		}else if ( uiBitsPerPixel <= 16 ){
			uiBitsPerPixel = 16;
		}else{
			uiBitsPerPixel = 32;
		}
		
		ulMaxOutputValues = (1L << uiBitsPerPixel) - 1;
		
		uiBitsPerPixel = uiBitsPerPixel * 3;
#endif //FEATURE_FROM_FIB_BITS_PER_RGB_COLOR_VALUE
		
		
		if ( bDimensionXY && ( ( ! bTransparencyUsed ) ||
				( ( dMinTransparencyValue == 0.0 ) && ( dMaxTransparencyValue == 255.0 ) &&
					( ulCountTransparencyValues == 256 ) ) // no transparency or int transparency from 0 ... 255
				) && (//check color red
					( ( ( dMinRedValue == 0.0 ) && ( dMaxRedValue == 255.0 ) &&
						( ulCountRedValues == 256 ) ) ) && //check color blue
					( ( ( dMinBlueValue == 0.0 ) && ( dMaxBlueValue == 255.0 ) &&
						( ulCountBlueValues == 256 ) ) ) && //check color green
					( ( ( dMinGreenValue == 0.0 ) && ( dMaxGreenValue == 255.0 ) &&
						( ulCountGreenValues == 256 ) ) )
				) && (//check dimensions
					( ( dDirection1Scaling == 1.0 ) && ( dDirection1Minimum == 0.0 ) &&
						( dDirection1Maximum < 32000.0 ) ) &&
					( ( dDirection2Scaling == 1.0 ) && ( dDirection2Minimum == 0.0 ) &&
						( dDirection2Maximum < 32000.0 ) )
				) ){
			/* transparency + color RGB with elements 0 ... 255 +
			 * + size in both directions from 0 and natural numbers
			 * object for cEvalueSimpleRGBA255Sec*/
			DEBUG_OUT_L1( <<"Using cEvalueSimpleRGBA255Sec to evalue image data"<<endl );
			
			cEvalueSimpleRGBA255Sec evalueSimpleRGBA255Sec( ulWidth, ulHeight, ulMaxEvaluationTimeInSec
#ifdef FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE
				,pPathForFileToStoreImage, FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE
#endif //FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE
				);
			const bool bObjectEvalued = fibMultimediaObject.evalueObjectSimple(
				evalueSimpleRGBA255Sec );
			
			if ( ! bObjectEvalued ){
				if ( (ulMaxEvaluationTimeInSec != 0 ) &&
						( evalueSimpleRGBA255Sec.lMaxEvaluationTimeInSec <
							( time( NULL ) - (evalueSimpleRGBA255Sec.tmStartTime ) ) ) ){
					DEBUG_OUT_EL1( <<"Warning: Max time reached object not evalued fully."<<endl );
					if ( pOutStatus ){
						*pOutStatus = 1;
					}
				}else{
					DEBUG_OUT_EL1( <<"Error: The given Fib object couldn't be evalued."<<endl );
					return NULL;
				}
			}
			DEBUG_OUT_L1( <<"nConvertFromFib::convert() ended correctly (valueSimpleRGBA255Sec.convertToFipImage())"<<endl );
			return evalueSimpleRGBA255Sec.convertToFipImage();
		}
		
	}else{
		cDomain * pDomainSw = fibMultimediaObject.
			getValidDomains().getDomainForElement( typePropertyColorSw );
		if ( pDomainSw != NULL ){
			bColorRGB = false;
			
			cDomainVectorBasis * pVecDomainColorSW = (cDomainVectorBasis*)pDomainSw;
			
			if ( pVecDomainColorSW->getNumberOfElements() != 1 ){
				DEBUG_OUT_EL1( <<"Error: No 1 elements in the colorGrayscale domain in Fib object."<<endl; );
				if ( pOutStatus ){
					*pOutStatus = -1;
				}
				return NULL;
			}
			if ( ! pVecDomainColorSW->getElementDomain( 1 )->isScalar() ){
				DEBUG_OUT_EL1( <<"Error: The monocrome color subdomain in the Fib object is not a scalar."<<endl; );
				if ( pOutStatus ){
					*pOutStatus = -1;
				}
				return NULL;
			}
			cDomainSingle * pColorSWDomain = (cDomainSingle*)(
					pVecDomainColorSW->getElementDomain( 1 ));
			
			dMinGrayValue = pColorSWDomain->getMinimum();
			dMaxGrayValue = pColorSWDomain->getMaximum();
			doubleFib dColorGrayScaling = 1.0;
			szDomainElementType = pColorSWDomain->getType();
			if ( ( szDomainElementType.compare( 0, 19, "DomainNaturalNumber" ) == 0 ) ||
						(szDomainElementType.compare( 0, 13, "DomainInteger" ) == 0) ){
				//cDomainIntegerBasis
				dColorGrayScaling = ((cDomainIntegerBasis*)pColorSWDomain)->getScalingFactor();
			}
			ulCountGrayValues = (unsigned long)( (dMaxGrayValue -
				dMinGrayValue) / dColorGrayScaling) + 1;
			
			//getPixel per bit
			uiBitsPerPixel = getDigits( ulCountGrayValues );
			
			if ( uiBitsPerPixel <= 1 ){
				uiBitsPerPixel = 1;
			}else if ( uiBitsPerPixel <= 4 ){
				uiBitsPerPixel = 4;
			}else{
				uiBitsPerPixel = 8;
			}
			
			ulMaxOutputValues = (1L << uiBitsPerPixel) - 1;
			
		}else{
			DEBUG_OUT_EL1( <<"Error: No colordomain in Fib object."<<endl; );
			if ( pOutStatus ){
				*pOutStatus = -1;
			}
			return NULL;
		}
	}
	//create the FreeImage object
	fipImage * pFipImage = new fipImage( FIT_BITMAP, ulWidth, ulHeight, uiBitsPerPixel );
	
	if ( ! bColorRGB ){
		//convert to grayscale
		pFipImage->convertToGrayscale();
	}
	
	//evalue the Fib object
	bool bObjectEvalued = false;
	cEvaluePositionList * pEvaluePositionList = NULL;
	
	if ( ulMaxEvaluationTimeInSec == 0 ){
		pEvaluePositionList = new cEvaluePositionListMemLimit(
			(ulWidth * ulHeight * 2), pVecDomainDimension );
	}else{
		pEvaluePositionList = new cEvaluePositionListMemLimitSec(
			(ulWidth * ulHeight * 2), pVecDomainDimension, ulMaxEvaluationTimeInSec );
	}
	bObjectEvalued = fibMultimediaObject.evalueObjectSimple(
		*pEvaluePositionList );
	if ( ! bObjectEvalued ){
		if ( (ulMaxEvaluationTimeInSec != 0 ) &&
				(((cEvaluePositionListMemLimitSec*)pEvaluePositionList)->lMaxEvaluationTimeInSec <
					( time( NULL ) - ((cEvaluePositionListMemLimitSec*)pEvaluePositionList)->tmStartTime ) ) ){
			DEBUG_OUT_EL1( <<"Warning: Max time reached object not evalued fully."<<endl );
			if ( pOutStatus ){
				*pOutStatus = 1;
			}
		}else{
		
			DEBUG_OUT_EL1( <<"Error: The given Fib object couldn't be evalued."<<endl );
			delete pEvaluePositionList;
			delete pFipImage;
			return NULL;
		}
	}
#ifdef TEST_OUTPUT
	ofstream ofFileUnsorted( "./dataUnsorted.txt" );
	cEvaluePositionList::printPositionsData(
		pEvaluePositionList->liEvaluedPositionData,
		ofFileUnsorted );
	ofFileUnsorted.close();
#endif
	pEvaluePositionList->sortPositionsData();
	
#ifdef TEST_OUTPUT
	ofstream ofFileSorted( "./dataSorted.txt" );
	cEvaluePositionList::printPositionsData(
		pEvaluePositionList->liEvaluedPositionData,
		ofFileSorted );
	ofFileSorted.close();
#endif
	
	/*for every point evalued from the Fib object set the
	corresponding pixel color into the fipImage*/
	RGBQUAD * colorValue = new RGBQUAD();
	BYTE * colorIndexValue = new BYTE();
	
	//check for background color
	for ( list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
			itrList = pEvaluePositionList->liEvaluedPositionData.begin();
			(itrList != pEvaluePositionList->liEvaluedPositionData.end()); ){
		if ( itrList->first.getNumberOfElements() == 0 ){
			//background color
			
			for ( list< cVectorProperty >::const_iterator
					itrProperty = itrList->second.begin();
					itrProperty != itrList->second.end(); itrProperty++ ){
				
				bool bColorProperty = false;
				if ( itrProperty->getPropertyType() == cTypeProperty::COLOR_RGB ){
					//set color values
					colorValue->rgbRed   = (unsigned long)((itrProperty->getValue( 1 ) - dMinRedValue) /
						(doubleFib)(ulCountRedValues) * (doubleFib)(ulMaxOutputValues));
					colorValue->rgbGreen = (unsigned long)((itrProperty->getValue( 2 ) - dMinGreenValue) /
						(doubleFib)(ulCountGreenValues) * (doubleFib)(ulMaxOutputValues));
					colorValue->rgbBlue  = (unsigned long)((itrProperty->getValue( 3 ) - dMinBlueValue) /
						(doubleFib)(ulCountBlueValues) * (doubleFib)(ulMaxOutputValues));
					
					bColorProperty= true;
				}else if ( itrProperty->getPropertyType() == cTypeProperty::COLOR_GRAYSCALE ){
					//set color values
					colorValue->rgbRed   = (unsigned long)((itrProperty->getValue( 1 ) - dMinGrayValue) /
						(doubleFib)(ulCountGrayValues) * (doubleFib)(ulMaxOutputValues));
					colorValue->rgbGreen = colorValue->rgbRed;
					colorValue->rgbBlue  = colorValue->rgbRed;
					
					bColorProperty= true;
				}//else ignore property
				if ( bColorProperty ){
//TODO dosn't work correct
//					const bool bBkColorSet =
						pFipImage->setFileBkColor( colorValue );
					
//					if ( ! bBkColorSet ){
						
						for ( unsigned long ulX = 0; ulX < ulWidth; ulX++ ){
							for ( unsigned long ulY = 0; ulY < ulHeight; ulY++ ){
								
								pFipImage->setPixelColor( ulX, ulY, colorValue );
							}
						}
//					}
				}
			}
			
			itrList = pEvaluePositionList->liEvaluedPositionData.erase( itrList );
		}else{
			itrList++;
		}
	}
#ifdef TEST_OUTPUT
	ofstream ofFilePixel( "./dataPixel.txt" );
	
	ofFilePixel<<"ulMaxOutputValues="<< ulMaxOutputValues <<endl;
	ofFilePixel<<"dMinRedValue="<< dMinRedValue <<endl;
	ofFilePixel<<"dMaxRedValue="<< dMaxRedValue <<endl;
	ofFilePixel<<"ulCountRedValues="<< ulCountRedValues <<endl;
	ofFilePixel<<"dMinGreenValue="<< dMinGreenValue <<endl;
	ofFilePixel<<"dMaxGreenValue="<< dMaxGreenValue <<endl;
	ofFilePixel<<"ulCountGreenValues="<< ulCountGreenValues <<endl;
	ofFilePixel<<"dMinBlueValue="<< dMinBlueValue <<endl;
	ofFilePixel<<"dMaxBlueValue="<< dMaxBlueValue <<endl;
	ofFilePixel<<"ulCountBlueValues="<< ulCountBlueValues <<endl;

#endif
	for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
			itrList = pEvaluePositionList->liEvaluedPositionData.begin();
			(itrList != pEvaluePositionList->liEvaluedPositionData.end());
			itrList++ ){
		//store color properties
		for ( list< cVectorProperty >::const_iterator
				itrProperty = itrList->second.begin();
				itrProperty != itrList->second.end(); itrProperty++ ){
			
			if ( itrList->first.getNumberOfElements() == 0 ){
				continue;
			}else if ( itrProperty->getPropertyType() == cTypeProperty::COLOR_RGB ){
				//evalue the pixel position
				unsigned int uiX;
				if ( bDimensionXY ){
					uiX = fib::roundToLongFib( ( itrList->first.getValue( 1 ) -
						dDirection1Minimum ) * dDirection1Scaling );
				}else{
					uiX = fib::roundToLongFib( ( itrList->first.getValue( 2 ) -
						dDirection2Minimum ) * dDirection2Scaling );
				}
				unsigned int uiY;
				if ( bDimensionXY ){
					uiY = fib::roundToLongFib( ( itrList->first.getValue( 2 ) -
						dDirection2Minimum ) * dDirection2Scaling );
				}else{
					uiY = fib::roundToLongFib( ( itrList->first.getValue( 1 ) -
						dDirection1Minimum ) * dDirection1Scaling );
				}
				//set color values
				colorValue->rgbRed   = (unsigned long)((itrProperty->getValue( 1 ) - dMinRedValue) /
					(doubleFib)(ulCountRedValues) * (doubleFib)(ulMaxOutputValues));
				colorValue->rgbGreen = (unsigned long)((itrProperty->getValue( 2 ) - dMinGreenValue) /
					(doubleFib)(ulCountGreenValues) * (doubleFib)(ulMaxOutputValues));
				colorValue->rgbBlue  = (unsigned long)((itrProperty->getValue( 3 ) - dMinBlueValue) /
					(doubleFib)(ulCountBlueValues) * (doubleFib)(ulMaxOutputValues));
				
				pFipImage->setPixelColor( uiX, uiY, colorValue );
#ifdef TEST_OUTPUT
				ofFilePixel<<"( "<< uiX <<"; "<< uiY <<")->"<<
					"( "<< itrProperty->getValue( 1 ) <<"; "<<
					itrProperty->getValue( 2 ) << "; "<<
					itrProperty->getValue( 3 ) <<" )"<<endl;
				
				ofFilePixel<<"( "<< uiX <<"; "<< uiY <<")->"<<
					"( "<< (int)(colorValue->rgbRed) <<"; "<< (int)(colorValue->rgbGreen) <<
					"; "<< (int)(colorValue->rgbBlue) <<" )"<<endl;
#endif

			}else if ( itrProperty->getPropertyType() == cTypeProperty::COLOR_GRAYSCALE ){
				//evalue the pixel position
				unsigned int uiX;
				if ( bDimensionXY ){
					uiX = itrList->first.getValue( 1 ) - dDirection1Minimum * dDirection1Scaling;
				}else{
					uiX = itrList->first.getValue( 2 ) - dDirection2Minimum * dDirection2Scaling;
				}
				unsigned int uiY;
				if ( bDimensionXY ){
					uiY = itrList->first.getValue( 2 ) - dDirection2Minimum * dDirection2Scaling;
				}else{
					uiY = itrList->first.getValue( 1 ) - dDirection1Minimum * dDirection1Scaling;
				}
				if ( ! bColorRGB ){
					//set color values
					colorValue->rgbRed   = (unsigned long)((itrProperty->getValue( 1 ) - dMinGrayValue) /
						(doubleFib)(ulCountGrayValues) * (doubleFib)(ulMaxOutputValues));
					colorValue->rgbGreen = colorValue->rgbRed;
					colorValue->rgbBlue  = colorValue->rgbRed;
					
					pFipImage->setPixelColor( uiX, uiY, colorValue );
				}else{
					*colorIndexValue = (unsigned long)((itrProperty->getValue( 1 ) - dMinGrayValue) /
						(doubleFib)(ulCountGrayValues) * (doubleFib)(ulMaxOutputValues));
					
					pFipImage->setPixelIndex( uiX, uiY, colorIndexValue );
				}
			}//else ignore property
		}
	}
	delete colorValue;
	delete colorIndexValue;
	delete pEvaluePositionList;


	/*include image description data from the optionalpart of the
	root -element*/
	//TODO

	DEBUG_OUT_L1( <<"nConvertFromFib::convert() ended correctly"<<endl );
	
	return pFipImage;
}







