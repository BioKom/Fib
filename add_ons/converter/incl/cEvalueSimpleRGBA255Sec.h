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
 *
 * This class limits the evaluation time of the class @see cEvalueSimpleRGBA255.
 */
/*
History:
27.04.2013  Oesterholz  created
*/


#ifndef ___FIB__C_EVALUE_SIMPLE_RGBA_255_SEC_H__
#define ___FIB__C_EVALUE_SIMPLE_RGBA_255_SEC_H__

#include "cEvalueSimpleRGBA255.h"

#include "fipImage.h"


namespace fib{


class cEvalueSimpleRGBA255Sec: public virtual cEvalueSimpleRGBA255{
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
			unsigned long ulInSecoundsBetweanIntermediateResultSaves = 10 );

	
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
		const list<cVectorProperty> & vProperties );
	
	
#ifdef FEATURE_CONVERT_FROM_FIB_INTERVALL_TO_SAVE_CURRENT_PICTURE
	/**
	 * This method stores the current picture, if it should be stored.
	 */
	void checkIntervallToSaveCurrentPicture();
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
	fipImage * convertToFipImage();
	
	
};//end class cEvalueSimpleRGBA255Sec

};//end namespace fib

#endif //___FIB__C_EVALUE_SIMPLE_RGBA_255_SEC_H__



