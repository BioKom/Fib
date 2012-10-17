/**
 * @file convertFibToFib
 * file name: convertFibToFib.cpp
 * @author Betti Oesterholz
 * @date 18.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This program is for converting Fib multimedia objects in one format
 * into a Fib object in an other format.
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
 * This program is for converting Fib multimedia objects in one format
 * into a Fib object in another format.
 *
 *
 * call: convertFibToFib FILE_MULTIMEDIADATA [FILE_OUTPUT]
 *
 * parameters:
 * 	PATH_MULTIMEDIADATA
 * 		The path to the to load Fib multimedia data.
 * 	FILE_OUTPUT
 * 		The name of the file where the Fib multimedia data would be
 * 		stored to. If the file ending is ".xml" the data will be written
 * 		in the Fib Xml format. If no parameter FILE_OUTPUT is given
 * 		the Fib object will be stored in the Fib Xml format to the
 * 		standard output.
 *
 * examples:
 * 	> convertFibToFib inputFib.xml outputFib.fib
 * 	> convertFibToFib inputFib.fib outputFib.xml
 */
/*
History:
18.06.2010  Oesterholz  created
23.08.2010  Oesterholz  output of call info added
06.09.2011  Oesterholz  if TEST a restored pictur with warnings on loading
	will be stored
*/

#include "version.h"
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
	
	if ( argc < 2 ){
		//no input file -> exit
		cout<<"No input file with the original multimedia data given."<<endl;
		cout<<endl;
		cout<<"This program is for converting Fib multimedia objects in one format"<<endl;
		cout<<"into a Fib object in another format."<<endl;
		cout<<endl;
		cout<<" call: convertFibToFib FILE_MULTIMEDIADATA [FILE_OUTPUT]"<<endl;
		cout<<endl;
		cout<<" parameters:"<<endl;
		cout<<" 	PATH_MULTIMEDIADATA"<<endl;
		cout<<" 		The path to the to load Fib multimedia data."<<endl;
		cout<<" 	FILE_OUTPUT"<<endl;
		cout<<" 		The name of the file where the Fib multimedia data would be"<<endl;
		cout<<" 		stored to. If the file ending is \".xml\" the data will be written"<<endl;
		cout<<" 		in the Fib Xml format. If no parameter FILE_OUTPUT is given"<<endl;
		cout<<" 		the Fib object will be stored in the Fib Xml format to the"<<endl;
		cout<<" 		standard output."<<endl;
		cout<<endl;
		cout<<" examples:"<<endl;
		cout<<" 	> convertFibToFib inputFib.xml outputFib.fib"<<endl;
		cout<<" 	> convertFibToFib inputFib.fib outputFib.xml"<<endl;
		cout<<endl;
		return 1;
	}
	pFileWithOriginalData = argv[1];
	
	if ( argc >= 3 ){
		//two parameter given; get parameter filename wher to store the Fib object to
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
			cout<<"Restoring Fib object in the Xml -format from the file \""<<
				pFileWithOriginalData <<"\" successfull. "<<endl;
		}else{
			cerr<<"Restoring Fib object in the Xml -format from the file \""<<
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
	}else{//restore to file in compressedformat
		ifstream inFile( pFileWithOriginalData, ios_base::in | ios_base::binary );
		intFib outStatus = 0;
		
		pRestoredFibObject = cFibElement::restore( inFile , &outStatus );
		
		if ( outStatus == 0 ){
			cout<<"Restoring Fib object in the compressedformat from the file \""<<
				pFileWithOriginalData <<"\" successfull. "<<endl;
		}else{
			cerr<<"Restoring Fib object in the compressedformat from the file \""<<
				pFileWithOriginalData <<"\" not successfull. (return status="<< outStatus <<")"<<endl;
			
			if ( pRestoredFibObject ){
				cFibElement::deleteObject( pRestoredFibObject );
			}
			return 1;
		}
	}
	
	if ( pRestoredFibObject ){
		//output the multimediaobject
		
		if ( pFileForStoringData == 0 ){
			//store to standard output in Xml format
			bool bStoreSuccesfull = pRestoredFibObject->storeXml( cout );
			
			if ( ! bStoreSuccesfull ){
		
				cerr<<"Error: Storing the data of the converted Fib object "<<
					"in the Xml format to the standard output failed."<<endl;
				return 4;
			}
		
		}else if ( strcmp( & (pFileForStoringData[
				strlen ( pFileForStoringData ) - 4 ]), ".xml") == 0 ){
			//store to file in Xml format
			ofstream outFile( pFileForStoringData );
			
			cout<<"Storing Fib object in the Xml format to the file "<< pFileForStoringData <<" . "<<endl;
			
			const bool bStoreSuccesfull = pRestoredFibObject->storeXml( outFile );
			
			if ( ! bStoreSuccesfull ){
		
				cerr<<"Error: Storing the data of the converted Fib object "<<
					"in the Xml format to the file "<< pFileForStoringData <<" failed."<<endl;
				
			}

		}else{//store to file in compressedformat
			ofstream outFile( pFileForStoringData, ios_base::out | ios_base::binary );
			
			cout<<"Storing Fib object in the Xml format to the file "<< pFileForStoringData <<" . "<<endl;
			
			const bool bStoreSuccesfull = pRestoredFibObject->store( outFile );
			
			if ( ! bStoreSuccesfull ){
		
				cerr<<"Error: Storing the data of the converted Fib object "<<
					"in the compressed Fib format to the file "<< pFileForStoringData <<" failed."<<endl;
			}
		}
		
		cFibElement::deleteObject( pRestoredFibObject );
	}else{
		cerr<<"Error: Could not convert the data into a Fib multimediaobject."<<endl;
		return 3;
	}
	
	return 0;
}









