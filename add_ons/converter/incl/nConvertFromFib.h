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
23.10.2012  Oesterholz  changes to store intermediate result
*/

#ifndef ___FIB__N_CONVERT_TO_FIB__N_CONVERT_FROM_FIB_H__
#define ___FIB__N_CONVERT_TO_FIB__N_CONVERT_FROM_FIB_H__

#include "version.h"

#include "cFibElement.h"

#ifdef FEATURE_OWN_FREE_IMAGE_WARPER
	//no FreeImagePlus wraper for windows -> use own
	#include "fipImage.h"
#else //WINDOWS
	#include <FreeImagePlus.h>
#endif //WINDOWS


using namespace std;
using namespace fib;

namespace nConvertFromFib{

	/**
	 * This function converts the given multimediaobject into a fib-object.
	 *
	 * @param multimediaObject the fib -multimedaobject to convert into fib
	 * @param ulMaxEvaluationTimeInSec the maximal time for evaluation in seconds;
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
	 * 	INTERVALL_TO_SAVE_CURRENT_PICTURE secounds
	* 	@see cEvalueSimpleRGBA255Sec
	 * @return the created FreeImagePlus object (pleas delete it after usage)
	 * 	or NULL, if non could be created
	 */
	fipImage * convertToFipImage( const cFibElement & fibMultimediaObject,
		unsigned long ulMaxEvaluationTimeInSec = 0, int * pOutStatus = NULL,
		const char * pPathForFileToStoreImage = NULL );


}//end namespace nConvertFromFib


#endif //___FIB__N_CONVERT_TO_FIB__N_CONVERT_FROM_FIB_H__







