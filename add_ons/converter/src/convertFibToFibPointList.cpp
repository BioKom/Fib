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
 * call: convertFibToFibPointList [PARAMETER] FILE_MULTIMEDIADATA [FILE_OUTPUT]
 *
 * parameters:
 * 	PATH_MULTIMEDIADATA
 * 		The path to the to load Fib multimedia data.
 * 	FILE_OUTPUT
 * 		The name of the file where the Fib multimedia data would be
 * 		stored to. If no parameter FILE_OUTPUT is given
 * 		the Fib object data will be written to the standard output.
 * 	PARAMETER
 * 		Parameters for evalung the point list.
 * 	Possible parameters are:
 * 		-remove_duplicates or -rd
 * 			duplicate points will be removed;
 * 			if ther are two equal points in the evalued point list the
 * 			first will be removed with all its properties
 * 		-sort_position_data or -s
 * 			the evalued point list will be sorted;
 * 			duplicate points will be removed and the properties of duplicate
 * 			points merged
 *
 *
 * examples:
 * 	> convertFibToFibPointList inputFib.fib outputFib.xml
 * 	> convertFibToFibPointList inputFib.xml
 * 	> convertFibToFibPointList -rd inputFib.xml
 */
/*
History:
21.01.2013  Oesterholz  created
22.02.2013  Oesterholz  options to remove duplicates and to sort the points
	implemented (see bRemoveDuplicates and bSortPositionsData)
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
		cout<<" 	PARAMETER"<<endl;
		cout<<" 		Parameters for evalung the point list."<<endl;
		cout<<" 	Possible parameters are:"<<endl;
		cout<<" 		-remove_duplicates or -rd"<<endl;
		cout<<" 			duplicate points will be removed;"<<endl;
		cout<<" 			if ther are two equal points in the evalued point list the"<<endl;
		cout<<" 			first will be removed with all its properties"<<endl;
		cout<<" 		-sort_position_data or -s"<<endl;
		cout<<" 			the evalued point list will be sorted;"<<endl;
		cout<<" 			duplicate points will be removed and the properties of duplicate"<<endl;
		cout<<" 			points merged"<<endl;
		cout<<""<<endl;
		cout<<" examples:"<<endl;
		cout<<" 	> convertFibToFibPointList inputFib.fib outputFib.xml"<<endl;
		cout<<" 	> convertFibToFibPointList inputFib.xml"<<endl;
		cout<<" 	> convertFibToFibPointList -rd inputFib.xml"<<endl;
		cout<<endl;
		return 1;
	}
	/* if true duplicate points will be removed;
	 * if ther are two equal points in the evalued point list the first will
	 * be removed with all its properties*/
	bool bRemoveDuplicates  = false;
	/* if true the evalued point list will be sorted;
	 * duplicate points will be removed and the properties of duplicate
	 * points merged
	 * @see cEvaluePositionList::sortPositionsData()
	 */
	bool bSortPositionsData = false;
	
	//read parameter
	for ( int iActualParameter = 1; iActualParameter < argc;
			iActualParameter++ ){
		
		if ( ( strncmp( argv[ iActualParameter ], "-rd", 3 ) == 0 ) ||
				( strncmp( argv[ iActualParameter ], "-remove_duplicates", 15 ) == 0 ) ){
			bRemoveDuplicates = true;
			cout<<"Duplicate points will be removed."<<endl;
			
		}else if ( ( strncmp( argv[ iActualParameter ], "-s", 3 ) == 0 ) ||
				( strncmp( argv[ iActualParameter ], "-sort_position_data", 13 ) == 0 ) ){
			bSortPositionsData = true;
			cout<<"The evalued point list will be sorted."<<endl;
			
		}else if ( argv[ iActualParameter ][ 0 ] == '-' ){
			cerr<<"Unknown parameter: "<<argv[ iActualParameter ]<<endl;
			
		}else if ( pFileWithOriginalData == NULL ){
			//read original data file
			pFileWithOriginalData = argv[ iActualParameter ];
			cout<<"Name of Fib object file to convert: "<<pFileWithOriginalData<<endl;
		}else if ( pFileForStoringData == NULL ){
			//get parameter filename where to store the Fib object to
			pFileForStoringData = argv[ iActualParameter ];
			cout<<"Name of converted output Fib point file file: "<<pFileForStoringData<<endl;
		}else{
			cerr<<"Unknown parameter: "<<argv[ iActualParameter ]<<endl;
		}
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
		
		if ( bRemoveDuplicates ){
			//remove double points
			/* compare every point with every point after it, if a duplicate
			 * point was found -> remove first point and check next point*/
			list< pair< cVectorPosition, list< cVectorProperty > > > &
				liEvaluedPositionData = evaluedPositionData.liEvaluedPositionData;
			for ( list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
					itrActualPoint = liEvaluedPositionData.begin();
					itrActualPoint != liEvaluedPositionData.end(); ){
				
				list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
					itrCompareToPoint = itrActualPoint;
					itrCompareToPoint++;
				for (  ; itrCompareToPoint != liEvaluedPositionData.end();
						itrCompareToPoint++ ){
					
					if ( itrActualPoint->first.equal( itrCompareToPoint->first ) ){
						//equal point found -> remove first point
						itrActualPoint = liEvaluedPositionData.erase( itrActualPoint );
						break;
					}
				}
				if ( itrActualPoint == liEvaluedPositionData.end() ){
					//all points checked
					break;
				}
				if ( itrCompareToPoint == liEvaluedPositionData.end() ){
					//no equal point found -> check next point
					itrActualPoint++;
				}
			}
		}//end if remove duplicate points
		
		if ( bSortPositionsData ){
			//sort the position data, but don't delete empty points
			evaluedPositionData.sortPositionsData( false );
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






