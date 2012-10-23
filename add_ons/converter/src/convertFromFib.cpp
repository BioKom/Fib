/**
 * @file convertFromFib
 * file name: convertFromFib.cpp
 * @author Betti Oesterholz
 * @date 25.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This program is for converting multimedia objects in the fib
 * multimedia formats into oter multimedia formats.
 *
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
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
 * This program is for converting multimedia objects in the Fib
 * multimedia formats into other multimedia formats.
 *
 *
 * call: convertFromFib FILE_MULTIMEDIADATA FILE_OUTPUT [MAX_EVALUE_TIME]
 *
 * parameters:
 * 	PATH_FIB_MULTIMEDIADATA
 * 		the path to the to load Fib multimedia data
 * 	FILE_OUTPUT
 * 		The name of the file where the converted multimedia data would be
 * 		stored to. The file ending will determine the output format.
 * 	MAX_EVALUE_TIME
 * 		if given and not 0, the maximal time in seconds for evaluing the
 * 		Fib object;
 * 		if not given or 0, no time limit for evaluing the Fib object is set
 *
 * examples:
 * 	> convertFromFib inputFib.xml output.png
 * 	> convertFromFib inputFib.fib output.bmp
 */
/*
History:
25.02.2010  Oesterholz  created
23.08.2010  Oesterholz  output of call info added
23.08.2010  Oesterholz  continue after restor warning
23.10.2012  Oesterholz  changes to store intermediate result
*/

#include "version.h"
#include "nConvertFromFib.h"
#include "cFibElement.h"

#include <string>
#include <iostream>
#include <fstream>



using namespace fib;
using namespace std;



int main(int argc, char* argv[]){

	char * pFileWithOriginalData = NULL;
	/*filename wher to store the Fib object to, if NULL store in XML to
	the standartoutput*/
	char * pFileForStoringData = NULL;
	
	if ( argc < 3 ){
		//no input file -> exit
		cout<<"No input file and output file specified."<<endl;
		cout<<endl;
		cout<<"This program is for converting multimedia objects in the Fib"<<endl;
		cout<<"multimedia formats into other multimedia formats."<<endl;
		cout<<endl;
		cout<<"call: convertFromFib FILE_MULTIMEDIADATA FILE_OUTPUT [MAX_EVALUE_TIME]"<<endl;
		cout<<endl;
		cout<<"parameters:"<<endl;
		cout<<"	PATH_FIB_MULTIMEDIADATA"<<endl;
		cout<<"		the path to the to load Fib multimedia data"<<endl;
		cout<<"	FILE_OUTPUT"<<endl;
		cout<<"		The name of the file where the converted multimedia data would be"<<endl;
		cout<<"		stored to. The file ending will determine the output format."<<endl;
		cout<<"	MAX_EVALUE_TIME"<<endl;
		cout<<"		if given and not 0, the maximal time in seconds for evaluing the"<<endl;
		cout<<"		Fib object;"<<endl;
		cout<<"		if not given or 0, no time limit for evaluing the Fib object is set"<<endl;
		cout<<endl;
		cout<<"examples:"<<endl;
		cout<<"	> convertFromFib inputFib.xml output.png"<<endl;
		cout<<"	> convertFromFib inputFib.fib output.bmp"<<endl;
		cout<<endl;
		return 1;
	}
	pFileWithOriginalData = argv[1];
	pFileForStoringData   = argv[2];
	//the maximal time for evaluation in seconds
	unsigned long ulMaxEvaluationTimeInSec = 0;
	if ( argc >= 4 ){
		//tree parameter given; get the maximal time for evaluation
		ulMaxEvaluationTimeInSec = atol( argv[3] );
		cout<<"The specified maximal evalue time is: "<< ulMaxEvaluationTimeInSec << " s" <<endl;
	}

	//load the multimedia data
//	FREE_IMAGE_FORMAT imageFormat = fipImage::identifyFIF( pFileWithOriginalData );
	
	cFibElement * pRestoredFibObject = NULL;
	
	if ( strcmp( & (pFileWithOriginalData[
			strlen( pFileWithOriginalData ) - 4 ]), ".xml") == 0 ){
		//restore to file in xml -format
		ifstream inFile( pFileWithOriginalData );
		intFib outStatus = 0;
		
		pRestoredFibObject = cFibElement::restoreXml( inFile , &outStatus );
		
		if ( outStatus == 0 ){
			cout<<"Restoring Fib object in the Xml format from the file \""<<
				pFileWithOriginalData <<"\" successfull. "<<endl;
		}else if ( 0 < outStatus ){
			cerr<<"Warning: Restoring Fib object in the Xml format from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
		}else{//( outStatus < 0 )
			cerr<<"Error: Restoring Fib object in the Xml format from the file \""<<
				pFileWithOriginalData <<"\" not successfull. "<<endl;
			return 1;
		}
	}else{//restore to file in compressed format
		ifstream inFile( pFileWithOriginalData, ios_base::in | ios_base::binary );
		intFib outStatus = 0;
		
		pRestoredFibObject = cFibElement::restore( inFile , &outStatus );
		
		if ( outStatus == 0 ){
			cout<<"Restoring Fib object in the compressed format from the file \""<<
				pFileWithOriginalData <<"\" successfull. "<<endl;
		}else if ( 0 < outStatus ){
			cerr<<"Warning: Restoring Fib object in the compressed format from the file \""<<
				pFileWithOriginalData <<"\" not successfull. "<<endl;
		}else{
			cerr<<"Error: Restoring Fib object in the compressed format from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
			return 1;
		}
	}
	//convert into a multimedia object
	int iOutStatus = 0;
	fipImage * pCovertedObject = nConvertFromFib::convertToFipImage(
		*pRestoredFibObject, ulMaxEvaluationTimeInSec, &iOutStatus,
		pFileForStoringData );
	
	if ( iOutStatus != 0 ){
		cout<<"The output status is: "<< iOutStatus <<endl;
	}
	
	if ( pCovertedObject ){
		//output the multimedia object
		
		cout<<"Saving the converted multimedia object to the file \""<<
			pFileForStoringData <<"\" . "<<endl;
		const bool bObjectConverted = pCovertedObject->save( pFileForStoringData );
		if ( ! bObjectConverted ){
			cerr<<"Error: Couldn't save to the file \""<< pFileForStoringData <<"\" ." <<endl;
			if ( pRestoredFibObject ){
				cFibElement::deleteObject( pRestoredFibObject );
			}
			if ( pCovertedObject ){
				delete pCovertedObject;
			}
			return 4;
		}
		delete pCovertedObject;
	}else{
		cerr<<"Error: Could not convert the data into a multimedia object."<<endl;
		if ( pRestoredFibObject ){
			cFibElement::deleteObject( pRestoredFibObject );
		}
		if ( pCovertedObject ){
			delete pCovertedObject;
		}
		return 3;
	}
	if ( pRestoredFibObject ){
		cFibElement::deleteObject( pRestoredFibObject );
	}
	return iOutStatus;
}









