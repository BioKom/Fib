/**
 * @file convertFibToFibPointList
 * file name: convertFibToFibPointList.cpp
 * @author Betti Oesterholz
 * @date 21.01.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This program is for converting Fib multimedia objects to a list of
 * Fib points with ther properties.
 *
 * Copyright (C) @c GPL3 2013 Betti Oesterholz
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
 * This program is for converting Fib multimedia objects to a list of
 * Fib points with ther properties.
 * The output will be in Xml. The root element is data in this element
 * the point data is stored after each other.
 * The points and properties are stored in the order ther wher evalued.
 * Every point is followed by its properties.
 *
 *
 * call: convertFibToFibPointList FILE_MULTIMEDIADATA [FILE_OUTPUT]
 *
 * parameters:
 * 	PATH_MULTIMEDIADATA
 * 		The path to the to load Fib multimedia data.
 * 	FILE_OUTPUT
 * 		The name of the file where the Fib multimedia data would be
 * 		stored to. If no parameter FILE_OUTPUT is given
 * 		the Fib object data will be written to the standard output.
 *
 * examples:
 * 	> convertFibToFibPointList inputFib.fib outputFib.xml
 * 	> convertFibToFibPointList inputFib.xml
 */
/*
History:
21.01.2013  Oesterholz  created
*/

#include "version.h"
#include "cFibElement.h"
#include "cEvaluePositionList.h"

#include <string>
#include <iostream>
#include <fstream>



using namespace fib;
using namespace std;



int main(int argc, char* argv[]){

	char * pFileWithOriginalData = NULL;
	/*file name wher to store the Fib object to, if NULL store in XML to
	the standard output*/
	char * pFileForStoringData = NULL;
	
	if ( argc < 2 ){
		//no input file -> exit
		cout<<"No input file with the original multimedia data given."<<endl;
		cout<<endl;
		cout<<"This program is for converting Fib multimedia objects to a list of"<<endl;
		cout<<"Fib points with ther properties."<<endl;
		cout<<endl;
		cout<<" call: convertFibToFibPointList FILE_MULTIMEDIADATA [FILE_OUTPUT]"<<endl;
		cout<<endl;
		cout<<" parameters:"<<endl;
		cout<<" 	PATH_MULTIMEDIADATA"<<endl;
		cout<<" 		The path to the to load Fib multimedia data."<<endl;
		cout<<" 	FILE_OUTPUT"<<endl;
		cout<<" 		The name of the file where the Fib multimedia data would be"<<endl;
		cout<<" 		stored to. If no parameter FILE_OUTPUT is given"<<endl;
		cout<<" 		the Fib object data will be written to the standard output."<<endl;
		cout<<endl;
		cout<<" examples:"<<endl;
		cout<<" 	> convertFibToFibPointList inputFib.fib outputFib.xml"<<endl;
		cout<<" 	> convertFibToFibPointList inputFib.xml"<<endl;
		cout<<endl;
		return 1;
	}
	pFileWithOriginalData = argv[1];
	
	if ( argc >= 3 ){
		//two parameter given; get parameter file name wher to store the Fib object to
		pFileForStoringData = argv[2];
	}

	//load the multimedia data
	cFibElement * pRestoredFibObject = NULL;
	
	if ( strcmp( & (pFileWithOriginalData[
			strlen( pFileWithOriginalData ) - 4 ]), ".xml") == 0 ){
		//restore to file in Xml format
		ifstream inFile( pFileWithOriginalData, ios_base::in );
		intFib outStatus = 0;
		
		pRestoredFibObject = cFibElement::restoreXml( inFile , &outStatus );
		
		if ( outStatus == 0 ){
			cout<<"Restoring Fib object in the Xml format from the file \""<<
				pFileWithOriginalData <<"\" successfull. "<<endl;
		}else{
			cerr<<"Restoring Fib object in the Xml format from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
#ifdef TEST
			if ( outStatus < 0 ){
				if ( pRestoredFibObject ){
					cFibElement::deleteObject( pRestoredFibObject );
				}
				return 1;
			}//else try to store the restored parts
#else //TEST
			if ( pRestoredFibObject ){
				cFibElement::deleteObject( pRestoredFibObject );
			}
			return 1;
#endif //TEST
		}
	}else{//restore to file in compressed format
		ifstream inFile( pFileWithOriginalData, ios_base::in | ios_base::binary );
		intFib outStatus = 0;
		
		pRestoredFibObject = cFibElement::restore( inFile , &outStatus );
		
		if ( outStatus == 0 ){
			cout<<"Restoring Fib object in the compressed format from the file \""<<
				pFileWithOriginalData <<"\" successfull. "<<endl;
		}else{
			cerr<<"Restoring Fib object in the compressed format from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
			
			if ( pRestoredFibObject ){
				cFibElement::deleteObject( pRestoredFibObject );
			}
			return 1;
		}
	}
	
	if ( pRestoredFibObject ){
		//evalue multimedia object
		cEvaluePositionList evaluedPositionData;
		
		const bool bObjectEvalued = pRestoredFibObject->evalueObjectSimple(
			evaluedPositionData );
		
		if ( ! bObjectEvalued ){
			
			cerr<<"Error: Loaded object could not be evalued."<<endl;
			cFibElement::deleteObject( pRestoredFibObject );
			return 2;
		}
		
		//stream wher to store the evalued data to
		ostream * pOutputStream = NULL;
		
		if ( pFileForStoringData == 0 ){
			//store to standard output in Xml format
			pOutputStream = &cout;
			
			cout<<"Storing Fib object in the Xml format to the standard output . "<<endl;
		}else{//store to file in Xml
			pOutputStream = new ofstream( pFileForStoringData );
			cout<<"Storing Fib object in the Xml format to the file "<< pFileForStoringData <<" . "<<endl;
		}
		//store point data
		(*pOutputStream)<<"<data>"<<endl;
		for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
				itrPosition = evaluedPositionData.liEvaluedPositionData.begin();
				itrPosition != evaluedPositionData.liEvaluedPositionData.end();
				itrPosition++ ){
			
			itrPosition->first.storeXml( (*pOutputStream) );
			
			for ( list< cVectorProperty >::const_iterator
					itrProperty = itrPosition->second.begin();
					itrProperty != itrPosition->second.end(); itrProperty++ ){
						
				itrProperty->storeXml( (*pOutputStream) );
			}
		}
		(*pOutputStream)<<"</data>"<<endl;
		
		if ( pOutputStream != (&cout) ){
			//data written to file -> destroy file stream
			delete pOutputStream;
		}
		cFibElement::deleteObject( pRestoredFibObject );
	}else{
		cerr<<"Error: Could not convert the data."<<endl;
		return 3;
	}
	
	return 0;
}






