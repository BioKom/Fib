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
 * call: convertFromFib FILE_MULTIMEDIADATA FILE_OUTPUT [PARAMETER]
 *
 * parameters:
 * 	PATH_FIB_MULTIMEDIADATA
 * 		the path to the to load Fib multimedia data
 * 	FILE_OUTPUT
 * 		The name of the file where the converted multimedia data would be
 * 		stored to. The file ending will determine the output format.
 * 	PARAMETER
 * 		Parameters for converting from the Fib multimedia format
 * 	Possible parameters are:
 * 		-max_evalue_time=VALUE or -maxTm=VALUE
 * 			the maximal time in seconds for evaluing the Fib object;
 * 			if not given or 0, no time limit for evaluing the Fib object is set
 * 		-inVars=[InVar_1], ...,[InVar_n]:
 * 			with this parameter you can give values to possible input
 * 			variables of the Fib object;
 * 			The input variables 1 till n will be set to the given values
 * 			(if the Fib object has more input variables, they will be set to
 * 			their default values; if the Fib object has less input variables,
 * 			the to much given values will be ignored)
 * 			Examples:
 * 				-inVars=13
 * 				-inVars=7,5,9.5
 * 				-inVars=-4.3,0.99
 *
 *
 * examples:
 * 	> convertFromFib inputFib.xml output.png
 * 	> convertFromFib inputFib.fib output.bmp
 * 	> convertFromFib inputFib.fib output.bmp -inVars=3.3,5,-4
 */
/*
History:
25.02.2010  Oesterholz  created
23.08.2010  Oesterholz  output of call info added
23.08.2010  Oesterholz  continue after restor warning
23.10.2012  Oesterholz  changes to store intermediate result
22.04.2013  Oesterholz  input parameter now as a parameter
*/

#include "version.h"
#include "nConvertFromFib.h"
#include "cFibElement.h"
#include "cRoot.h"

#include <string>
#include <iostream>
#include <fstream>



using namespace fib;
using namespace std;

void printShortHelp();


int main(int argc, char* argv[]){

	char * pFileWithOriginalData = NULL;
	/*filename wher to store the Fib object to, if NULL store in XML to
	the standartoutput*/
	char * pFileForStoringData = NULL;
	
	if ( argc < 3 ){
		//no input file -> exit
		printShortHelp();
		return 1;
	}
	//the maximal time for evaluation in seconds
	unsigned long ulMaxEvaluationTimeInSec = 0;
	list< doubleFib > liInputVariables;

	//read parameter
	for ( int iActualParameter = 1; iActualParameter < argc;
			iActualParameter++ ){
		if ( strncmp( argv[ iActualParameter ], "-max_evalue_time=", 17 ) == 0 ){
			ulMaxEvaluationTimeInSec = atol( &( argv[ iActualParameter ][ 17 ] )  );
			cout<<"The specified maximal evalue time is: "<< ulMaxEvaluationTimeInSec << " s" <<endl;
		}else if ( strncmp( argv[ iActualParameter ], "-maxTm=", 7 ) == 0 ){
			ulMaxEvaluationTimeInSec = atol( &( argv[ iActualParameter ][ 7 ] )  );
			cout<<"The specified maximal evalue time is: "<< ulMaxEvaluationTimeInSec << " s" <<endl;
			
		}else if ( strncmp( argv[ iActualParameter ], "-inVars=", 8 ) == 0 ){
			//format: -inVars=[InVar_1], ...,[InVar_n]:
			cout<<"Reading input variables: "<<endl;
			char * cActualPosition = &( argv[ iActualParameter ][ 8 ] );
			unsigned int uiActualVariable = 1;
			while ( ( cActualPosition != NULL ) && ( (*cActualPosition) != 0x0 ) ){
				//read the input variables
				liInputVariables.push_back( atof( cActualPosition ) );
				cout<<"   input variable "<<uiActualVariable<<" is "<<
					liInputVariables.back()<<endl<<flush;
				cActualPosition = strchr( cActualPosition, ',' );
				if ( cActualPosition == NULL ){
					//the char ',' not found
					break;
				}
				cActualPosition++;
				uiActualVariable++;
			}
			cout<<endl;
			
		}else if ( pFileWithOriginalData == NULL ){
			//read original data file
			pFileWithOriginalData = argv[ iActualParameter ];
			cout<<"Name of Fib object file to convert: "<<pFileWithOriginalData<<endl;
		}else if ( pFileForStoringData == NULL ){
			//get parameter filename where to store the Fib object to
			pFileForStoringData = argv[ iActualParameter ];
			cout<<"Name of converted output picture file: "<<pFileForStoringData<<endl;
		}else{
			cerr<<"Unknown parameter: "<<argv[ iActualParameter ]<<endl;
		}
	}
	
	if ( ( pFileWithOriginalData == NULL ) || ( pFileForStoringData == NULL ) ){
		//no input file -> exit
		printShortHelp();
		return 1;
	}
	
	
	//load the multimedia data
//	FREE_IMAGE_FORMAT imageFormat = fipImage::identifyFIF( pFileWithOriginalData );
	
	cFibElement * pRestoredFibObject = NULL;
	
	if ( strcmp( & (pFileWithOriginalData[
			strlen( pFileWithOriginalData ) - 4 ]), ".xml") == 0 ){
		//restore to file in xml -format
		ifstream inFile( pFileWithOriginalData );
		intFib outStatus = 0;
		
		if ( ! inFile.good() ){
			cerr<<"Error: Can't open file."<<endl;
			return 1;
		}
		
		pRestoredFibObject = cFibElement::restoreXml( inFile , &outStatus );
		
		if ( outStatus == 0 ){
			cout<<"Restoring Fib object in the Xml format from the file \""<<
				pFileWithOriginalData <<"\" successfull. "<<endl;
		}else if ( 0 < outStatus ){
			cerr<<"Warning: Restoring Fib object in the Xml format from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
		}else{//( outStatus < 0 )
			cerr<<"Error: Restoring Fib object in the Xml format from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
			return 1;
		}
	}else{//restore to file in compressed format
		ifstream inFile( pFileWithOriginalData, ios_base::in | ios_base::binary );
		intFib outStatus = 0;
		
		if ( ! inFile.good() ){
			cerr<<"Error: Can't open file."<<endl;
			return 1;
		}
		
		pRestoredFibObject = cFibElement::restore( inFile , &outStatus );
		
		if ( outStatus == 0 ){
			cout<<"Restoring Fib object in the compressed format from the file \""<<
				pFileWithOriginalData <<"\" successfull. "<<endl;
		}else if ( 0 < outStatus ){
			cerr<<"Warning: Restoring Fib object in the compressed format from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
		}else{
			cerr<<"Error: Restoring Fib object in the compressed format from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
			return 1;
		}
	}
	if ( pRestoredFibObject == NULL ){
		cerr<<"Error: No Fib object restored."<<endl;
		return 1;
	}
	//set input varibles if given
	if ( ! liInputVariables.empty() ){
		
		if ( pRestoredFibObject->getType() == 'r' ){
			//top most Fib element has to be a root element
			cRoot * pRootElement = ((cRoot*)pRestoredFibObject);
			
			list<cFibVariable*> liRootInputVars =
				pRootElement->getInputVariables();
			
			list< doubleFib >::const_iterator itrInputVarValue =
				liInputVariables.begin();
			for ( list<cFibVariable*>::iterator
					itrInputVar = liRootInputVars.begin();
					( itrInputVar != liRootInputVars.end() ) &&
					( itrInputVarValue != liInputVariables.end() );
					itrInputVar++, itrInputVarValue++ ){
				
				(*itrInputVar)->setValue( *itrInputVarValue );
			}
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
		return 3;
	}
	if ( pRestoredFibObject ){
		cFibElement::deleteObject( pRestoredFibObject );
	}
	return iOutStatus;
}


/**
 * Print short help information.
 */
void printShortHelp(){
	
	cout<<"No input file and output file specified."<<endl;
	cout<<endl;
	cout<<"This program is for converting multimedia objects in the Fib"<<endl;
	cout<<"multimedia formats into other multimedia formats."<<endl;
	cout<<endl;
	cout<<" call: convertFromFib FILE_MULTIMEDIADATA FILE_OUTPUT [PARAMETER]"<<endl;
	cout<<""<<endl;
	cout<<" parameters:"<<endl;
	cout<<" 	PATH_FIB_MULTIMEDIADATA"<<endl;
	cout<<" 		the path to the to load Fib multimedia data"<<endl;
	cout<<" 	FILE_OUTPUT"<<endl;
	cout<<" 		The name of the file where the converted multimedia data would be"<<endl;
	cout<<" 		stored to. The file ending will determine the output format."<<endl;
	cout<<" 	PARAMETER"<<endl;
	cout<<" 		Parameters for converting from the Fib multimedia format"<<endl;
	cout<<" 	Possible parameters are:"<<endl;
	cout<<" 		-max_evalue_time=VALUE or -maxTm=VALUE"<<endl;
	cout<<" 			the maximal time in seconds for evaluing the Fib object;"<<endl;
	cout<<" 			if not given or 0, no time limit for evaluing the Fib object is set"<<endl;
	cout<<" 		-inVars=[InVar_1], ...,[InVar_n]:"<<endl;
	cout<<" 			with this parameter you can give values to possible input"<<endl;
	cout<<" 			variables of the Fib object;"<<endl;
	cout<<" 			The input variables 1 till n will be set to the given values"<<endl;
	cout<<" 			(if the Fib object has more input variables, they will be set to"<<endl;
	cout<<" 			their default values; if the Fib object has less input variables,"<<endl;
	cout<<" 			the to much given values will be ignored)"<<endl;
	cout<<" 			Examples:"<<endl;
	cout<<" 				-inVars=13"<<endl;
	cout<<" 				-inVars=7,5,9.5"<<endl;
	cout<<" 				-inVars=-4.3,0.99"<<endl;
	cout<<endl;
	cout<<"examples:"<<endl;
	cout<<"	> convertFromFib inputFib.xml output.png"<<endl;
	cout<<"	> convertFromFib inputFib.fib output.bmp"<<endl;
	cout<<"	> convertFromFib inputFib.fib output.bmp -inVars=3.3,5,-4"<<endl;
	cout<<endl;
}






