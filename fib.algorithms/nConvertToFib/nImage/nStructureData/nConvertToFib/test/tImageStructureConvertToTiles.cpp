/**
 * @file tImageStructureConvertToTiles
 * file name: tImageStructureConvertToTiles.cpp
 * @author Betti Oesterholz
 * @date 05.01.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for testing the class cImageStructureConvertToTiles.
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
 * This test is for testing the class cImageStructureConvertToTiles.
 * It will test if the cImageStructureConvertToTiles::convertToTiles()
 * method converts given areas into a good list of Fib object tile objects.
 *
 * The Fib test objects are loaded from the files in the subdirectories of
 * the folder pDirTestObjects.
 * Every testcase consists of two files one with the data of the area to
 * convert and one with the points for the cImageSearchData of the overlapt
 * points.
 * The names of these files will be loaded from the test case file
 * (FILE_TESTOBJECTS_IMAGE_STRUCTURE_CONVERT_TO_TILES). Every line of this
 * file is for one testcase. The two file names are seperated by a
 * semicolon ';'. The first file name of a line contains the data of the
 * area and the second the data for the overlaped points.
 * E.g.: "areaToFind.xml;allreadyFoundPoints.xml"
 * The overlaped points area loaded into an cImageSearchData objects.
 * The points of the area to convert will be loaded into an
 * cImageStructureConvertToTiles object.
 * With the loaded data the convertToTiles() method of
 * cImageStructureConvertToTiles is called and the result evalued.
 * The evalued result will then be checked with the original loaded data.
 *
 * The data, in the test files, is stored in the Fib XML format. The files
 * (for the test data) have as the root XML element, a XML element with the
 * name "data". The "data" XML element contains the list with the positions
 * vectors of the area.
 *
 *
 * call: tImageStructureConvertToTiles [DIR_TESTDATA] [MAX_ITERATION]
 *
 * parameters:
 * 	DIR_TESTDATA
 * 		The path wher the testdata could be found. The standard folder is
 * 		"testObjects/".
 * 	MAX_ITERATION
 * 		The number of iterations for the random tests (test with given
 * 		parameters for convertToTiles()).
 * 		Just works with the DIR_TESTDATA parameter given.
 */
/*
History:
05.01.2013  Oesterholz  created
*/

#include "version.h"
#include "fibDatatyps.h"

#include "cImageStructureConvertToTiles.h"
#include "cImageSearchData.h"

#include "cList.h"
#include "cPoint.h"
#include "cProperty.h"
#include "cRoot.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"
#include "cEvaluePositionList.h"
#include "cEvalueFibElementList.h"

#include "cFolder.h"


#include <string>
#include <utility>
#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <ctime>

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif

#ifndef DIR_TESTOBJECTS_NIMAGE
	#define DIR_TESTOBJECTS_NIMAGE "../../testObjects/"
#endif
#ifndef FILE_TESTOBJECTS_IMAGE_STRUCTURE_CONVERT_TO_TILES
	#define FILE_TESTOBJECTS_IMAGE_STRUCTURE_CONVERT_TO_TILES "tImageStructureConvertToTiles.txt"
#endif


using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;
using namespace fib::algorithms::nConvertToFib::nImage::nStructureData::nConvertToFib;
using namespace fib;
using namespace std;




const char * pDirTestObjects = DIR_TESTOBJECTS_NIMAGE;
unsigned long MAX_ITERATION = 4;


unsigned int testConvertForObject( const string szActualAreaData,
		const string szActualSearchData,
		const bool bGiveParameters = false, double maxValue = 65536.0,
		const double maxErrorPerValue = 0.0 );
list< pair< string, string > > loadTestFileList( const string szFilePath );
set< cVectorPosition > loadPositionData( const char * szFilename );



int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test
	int iReturn = 0;//return value of the test; the number of occured Errors
	set< pair< string, string  > > setErrorsInTestCase;
	
	srand( time(NULL) );
	
	cout<<endl<<"Running Test for the tImageStructureConvertToTiles::convertToTiles() method"<<endl;
	cout<<      "==========================================================================="<<endl;
	
	if ( 1 < argc ){
		//one parameter given; get parameter test data path
		pDirTestObjects = argv[1];
	}
	cout<<endl<<"The folder with the test data is "<<pDirTestObjects<<endl;
	
	if ( 2 < argc ){
		//two parameters given; read parameter iterations
		MAX_ITERATION = atol( argv[1] );
		if ( MAX_ITERATION < 1 ){
			MAX_ITERATION = 1;
		}
	}
	cout<<endl<<"Number of maximal iterations is "<<MAX_ITERATION<<endl;
	
	//load the testfolder list
	string szFilePath = string( pDirTestObjects ) + FILE_TESTOBJECTS_IMAGE_STRUCTURE_CONVERT_TO_TILES;
	
	list< pair< string, string > > liTestFolders = loadTestFileList( szFilePath );
	if ( liTestFolders.empty() ){
		cerr<<"Error: No testfolders to test."<<endl;
		iReturn++;
		return iReturn;
	}
	
	//for each testfolder
	for ( list< pair< string, string > >::iterator itrTestCase = liTestFolders.begin();
			itrTestCase != liTestFolders.end(); itrTestCase++ ){
		
		const string szActualAreaData  = itrTestCase->first;
		const string szActualSearchData = itrTestCase->second;
		ulTestphase++;
		cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing converting the area of \""<<
			szActualAreaData <<"\" with the search data of \""<<szActualSearchData<<"\""<<endl;
		
		unsigned int iErrorsInLastTestCase =
			testConvertForObject( szActualAreaData, szActualSearchData );
		
		for ( unsigned int uiActualIteration = 0;
				uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
			
			const double maxValue = 1024.0 + (double(rand() % 65536)) *
				(double(rand() % 65536));
			
			iErrorsInLastTestCase +=
				testConvertForObject( szActualAreaData, szActualSearchData, true,
					maxValue );
		}
		/*TODO for error parameters testConvertForObject() not implemented
		for ( unsigned int uiActualIteration = 0;
				uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
			
			const double maxValue = 1024.0 + (double(rand() % 65536)) *
				(double(rand() % 65536));
			const double maxErrorPerValue =
				(double(rand() % 255)) * (double(rand() % 255));
			
			iErrorsInLastTestCase +=
				testConvertForObject( szActualAreaData, szActualSearchData, true,
					maxValue, maxErrorPerValue );
		}
		*/
		//TODO test for antialised
		
		iReturn += iErrorsInLastTestCase;
		if ( 0 < iErrorsInLastTestCase ){
			//add area test file to error in test case list
			setErrorsInTestCase.insert( pair< string, string >( *itrTestCase ) );
		}
		
	}
	
	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured in "<<setErrorsInTestCase.size()<<" test cases"<<endl;
		
		cerr<<"Errors wher in test files: ";
		for ( set< pair< string, string  > >::const_iterator
				itrTestCase = setErrorsInTestCase.begin();
				itrTestCase != setErrorsInTestCase.end(); itrTestCase++ ){
			
			cerr<<"\""<<(itrTestCase->first)<<"\",\""<<(itrTestCase->second)<<"\";"<<endl;
		}
		cerr<<endl;
	}

	return iReturn;
}


/**
 * This function compares two points.
 * The elements of the points are rounded to interger values for comparrison.
 *
 * @param point1 the first point to compare
 * @param point2 the second point to compare
 * @return if the points are equal, else false
 */
bool pointsEqual( const cVectorPosition & point1, const cVectorPosition & point2 ){
	
	const unsigned int uiNumberOfElements = point1.getNumberOfElements();
	if ( uiNumberOfElements != point2.getNumberOfElements() ){
		//points don't have equal number of elements
		return false;
	}
	
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ){
		
		const long lValue1 = roundToLongFib( point1.getValue( uiActualElement ) );
		const long lValue2 = roundToLongFib( point2.getValue( uiActualElement ) );
		
		if ( lValue1 != lValue2 ){
			//values not equal -> points not equal
			return false;
		}
		
	}
	return true;
}


/**
 * This function test the cImageStructureConvertToTiles::convertToTiles()
 * method for one test case.
 *
 * @param szActualAreaData the file wher the to convert object data is stored
 * @param szActualSearchData the file wher the search data is stored
 * @param bGiveParameters if true the convertToTiles() is given the
 * 	maxValue, maxErrorPerValue and maxError parameters
 * @param maxValue the maxValue parameter for the convertToTiles() method
 * @param maxErrorPerValue the maxErrorPerValue parameter for the convertToTiles() method
 * @return the number of errors occured in the test
 */
unsigned int testConvertForObject( const string szActualAreaData,
		const string szActualSearchData, const bool bGiveParameters,
		double maxValue, const double maxErrorPerValue ){
	
	int iReturn = 0;//return value of the test; the number of occured Errors
	
	//evalue the files in the testfolder
	const string szActualAreaDataPath = string( pDirTestObjects ) +
		szActualAreaData ;
	const string szActualSearchDataPath = string( pDirTestObjects ) +
		szActualSearchData ;
	
	//load the the area to convert
	const set< cVectorPosition > setAreaPointsLoaded =
		loadPositionData( szActualAreaDataPath.c_str() );
		
	//load the the search data
	const set< cVectorPosition > setSearchDataLoaded =
		loadPositionData( szActualAreaDataPath.c_str() );
		
	//dertermine image higth and width
	//evalue max points
	longFib lMaxX = 0;
	longFib lMaxY = 0;
	for ( set<cVectorPosition>::const_iterator
			itrActualPoint = setSearchDataLoaded.begin();
			itrActualPoint != setSearchDataLoaded.end(); itrActualPoint++ ){
		
		lMaxX = fib::max( lMaxX,
			roundToLongFib( itrActualPoint->getValue( 1 ) ) );
		lMaxY = fib::max( lMaxY,
			roundToLongFib( itrActualPoint->getValue( 2 ) ) );
	}
	
	cImageSearchData imageSearchData( lMaxX + 1 , lMaxY + 1 );
	imageSearchData.registerOverlapped( setSearchDataLoaded );
	
	//convert area to subobjects with default values
	
	//the list with the converted Fib objects
	cImageStructureConvertToTiles areaConvertStrategy;
	list< cExtObject * > liConvertedFibObjects;
	
	/*convertToExtObjects(
		const set<cVectorPosition> & structurePoints,
		const cImageSearchData * pImageSearchData,
		const bool bIsAntialised = false,
		double maxValue = 0.0,
		const double maxErrorPerValue = 0.0 )*/
	if ( bGiveParameters ){
		cout<<endl<<"areaConvertStrategy.convertToTiles( setAreaPointsLoaded"<<
			", &imageSearchData, maxValue="<<maxValue<<
			", maxErrorPerValue="<<maxErrorPerValue<<" );"<<endl;
		liConvertedFibObjects =
			areaConvertStrategy.convertToExtObjects(
				setAreaPointsLoaded, &imageSearchData,
				false, maxValue, maxErrorPerValue );
	}else{//give no parameters
		cout<<endl<<"areaConvertStrategy.convertToTiles( setAreaPointsLoaded, &imageSearchData );"<<endl;
		liConvertedFibObjects =
			areaConvertStrategy.convertToExtObjects(
				setAreaPointsLoaded, &imageSearchData );
	}
	//evalue converted Fib objects
	cEvaluePositionList evaluedPositionData;
	
	for ( list< cExtObject * >::const_iterator
			itrActualObject = liConvertedFibObjects.begin();
			itrActualObject != liConvertedFibObjects.end(); itrActualObject++ ){
		
		const bool bObjectEvalued = (*itrActualObject)->evalueObjectSimple(
			evaluedPositionData );
		
		if ( ! bObjectEvalued ){
			cerr<<"Error: Object could not be evalued:"<<endl;
			iReturn++;
			(*itrActualObject)->storeXml( cerr );
		}
	}//end for all evalued external objects (evalue them)
	
	if ( bGiveParameters ){
		//check parameters
		for ( list< cExtObject * >::const_iterator
				itrActualObject = liConvertedFibObjects.begin();
				itrActualObject != liConvertedFibObjects.end(); itrActualObject++ ){
			
			//check max values
			cVectorExtObject * vecExtObject = (*itrActualObject)->getInputVector();
			
			if ( vecExtObject->getNumberOfElements() != 6 ){
				cerr<<"Error: External object has not than 6 input values, but "<<
					vecExtObject->getNumberOfElements()<<endl;
				iReturn++;
				(*itrActualObject)->storeXml( cerr );
			}
			
			for ( unsigned int uiNumberActualValue = 3;
				uiNumberActualValue <= 6; uiNumberActualValue++ ){
				
				if ( maxValue < abs( vecExtObject->getValue( uiNumberActualValue ) ) ){
					cerr<<"Error: The "<<uiNumberActualValue<<
						" absulute input value of the external object is bigger as the maxValue (of "<<
							maxValue<<") , it is "<<
							vecExtObject->getValue( uiNumberActualValue )<<endl;
					iReturn++;
				}
			}
			
			//check error parameters
			/*TODO
			cEvaluePositionList evaluedPositionDataActual;
			const bool bObjectEvalued = (*itrActualObject)->evalueObjectSimple(
				evaluedPositionDataActual );
			
			if ( ! bObjectEvalued ){
				cerr<<"Error: Object could not be evalued:"<<endl;
				iReturn++;
				break;
			}
			*/
			//TODO how to evalue error?
			
			//not to much outside overlapt area
			
			
			
		}//end for all evalued external objects (evalue them)
		
		//TODO check not to much missing points in an line
		
	}
	
	
	/*check if all evalued points are in loaded area setAreaPointsLoaded
		or overlapt by the overlapt points in the search area setSearchDataLoaded*/
	//the area copy is for checking if all points wher removed
	set< cVectorPosition > setAreaPointsLoadedCopy = setAreaPointsLoaded;
	for ( list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
			itrActualPoint = evaluedPositionData.liEvaluedPositionData.begin();
			itrActualPoint != evaluedPositionData.liEvaluedPositionData.end();
			itrActualPoint++ ){
		
		//find the evalued point in the loaded area points
		set< cVectorPosition >::iterator
			itrLoadedPoint = setAreaPointsLoaded.begin();
		for ( ; itrLoadedPoint != setAreaPointsLoaded.end(); itrLoadedPoint++ ){
			
			if ( pointsEqual( *itrLoadedPoint, itrActualPoint->first ) ){
				//point evalued point found in the loaded area points
				break;
			}//else check next loaded point
		}
		
		if ( itrLoadedPoint != setAreaPointsLoaded.end() ){
			//point found in area -> everything is OK + remove it from copy
			
			set< cVectorPosition >::iterator
				itrLoadedPoint = setAreaPointsLoadedCopy.begin();
			for ( ; itrLoadedPoint != setAreaPointsLoadedCopy.end(); itrLoadedPoint++ ){
				
				if ( pointsEqual( *itrLoadedPoint, itrActualPoint->first ) ){
					//point evalued point found in the loaded area points
					break;
				}//else check next loaded point
			}
			if ( itrLoadedPoint != setAreaPointsLoadedCopy.end() ){
				//point found in loaded -> erase it from remaining loaded not found points
				setAreaPointsLoadedCopy.erase( itrLoadedPoint );
			}
		}else{//point not found in area -> check if it is overwritten
			const longFib lX = roundToLongFib(
				itrActualPoint->first.getValue( 1 ) );
			const longFib lY = roundToLongFib(
				itrActualPoint->first.getValue( 2 ) );
			
			if ( ! imageSearchData.isOverlapped( lX, lY ) ){
				
				if ( maxErrorPerValue == 0.0 ){
					cerr<<"Error: Point not in loaded area and not overwritten:"<<endl;
					itrActualPoint->first.storeXml( cerr );
					iReturn++;
				}//else TODO change for given parameters
			}
		}
	}//end for all evalued points
	
	
	if ( maxErrorPerValue == 0.0 ){
		if ( ! setAreaPointsLoadedCopy.empty() ){
			
			cerr<<endl<<"Error: Some points in loaded area wher not in converted area:"<<endl;
			
			for ( set< cVectorPosition >::iterator
					itrActualPoint = setAreaPointsLoadedCopy.begin();
					itrActualPoint != setAreaPointsLoadedCopy.end();
					itrActualPoint++ ){
				
				itrActualPoint->storeXml( cerr );
			}
			cerr<<endl;
			iReturn++;
		}
	}
	if (  0 < iReturn ){
		cerr<<"Generated external objects for tiles:"<<endl;
		for ( list< cExtObject * >::const_iterator
				itrActualObject = liConvertedFibObjects.begin();
				itrActualObject != liConvertedFibObjects.end(); itrActualObject++ ){
			
			(*itrActualObject)->storeXml( cerr );
			
		}//end for all evalued external objects (evalue them)
	}
	for ( list< cExtObject * >::const_iterator
			itrActualObject = liConvertedFibObjects.begin();
			itrActualObject != liConvertedFibObjects.end(); itrActualObject++ ){
		
		(*itrActualObject)->deleteObject();
	}
	return iReturn;
}



/**
 * This function reads the given file and returns a list with its lines.
 * The lines in the files should be the two semicolon ';' seperated data
 * files to check.
 * The two file names are seperated by a semicolon ';'. The first file name
 * of a line contains the data of the area and the second the data for the
 * overlaped points.
 *
 * @param szFilePath the path wher the file list to check is stored
 * @return a list with the files to check
 * 	pair elements:
 * 		first: the name for the file with the data of the area to convert
 * 		second: the name for the file with the data for the overlaped points
 */
list< pair< string, string > > loadTestFileList( const string szFilePath ){
	
	list< pair< string, string > > liFiles;
	
	ifstream ifStream( szFilePath.c_str() );
	
	if ( ! ifStream.good() ){
		
		cerr<<"Error: Couldn't read the folder list "<< szFilePath <<endl;
		return liFiles;
	}
	char szBuffer[ 1024 ];
	char cNull = ((char)(0x00));
	
	while( ifStream.good() ){
		
		ifStream.getline( szBuffer, 1024 );
		
		char * szSemikolon = strchr ( szBuffer, ';' );
		if ( szSemikolon != 0 ){
			(*szSemikolon) = (char)(0x00);//terminate area file string
			szSemikolon++;//set to search data file string
		}else{
			//no semicolon found
			szSemikolon = &cNull;
		}
		
		string szAreaFile( szBuffer );
		if ( szAreaFile != "" ){
			liFiles.push_back( pair< string, string >(
				szAreaFile, string( szSemikolon ) ) );
		}
	}
	return liFiles;
}


/**
 * This function loads the data of positions from the given file.
 *
 * @param szFilename the path of the file, from which the positions data
 * 	should be loaded from
 * @return the loaded positions data
 */
set< cVectorPosition > loadPositionData( const char * szFilename ){
	
	/*every setLoadedData element is created by loading a point vector and
	then property vectors till the next point vector*/
	set< cVectorPosition > setLoadedData;
	
	TiXmlDocument xmlDocData( szFilename );
	bool loadOkay = xmlDocData.LoadFile();
	if ( ! loadOkay ){
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
	}

	TiXmlHandle xmlHandle( &xmlDocData );
	TiXmlElement * pXmlElementData = xmlHandle.FirstChildElement().Element();
	
	if ( pXmlElementData ) {
		string szElementName = pXmlElementData->Value();

		if ( szElementName != "data" ){
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"data\"."<<endl;
		}
	
	}else{// pXmlElementData == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		return setLoadedData;
	}
	
	TiXmlHandle xmlHandleData( pXmlElementData );
	TiXmlElement * pXmlElement = xmlHandleData.FirstChild().Element();
	
	//no variables defined
	list<cFibVariable*> liDefinedVariables;
	intFib outStatus = 0;
	
	for( ; pXmlElement; pXmlElement = pXmlElement->NextSiblingElement() ){
		//load the vector lists for setLoadedData
		string szElementName = pXmlElement->Value();

		if ( szElementName != "vector" ){
			cerr<<"Error: The name of the data list element is "<< szElementName <<" and not \"vector\"."<<endl;
		}
		const char * szVectorXmlType = pXmlElement->Attribute( "type" );
		
		if ( szVectorXmlType == NULL ){
			cerr<<"Error: The vector has no type."<<endl;
		}else if ( string( szVectorXmlType ) == "position" ) {
		
			setLoadedData.insert(
				cVectorPosition( pXmlElement, outStatus, liDefinedVariables ) );
		}else{
			cerr<<"Error: The vector type is \""<<szVectorXmlType<<"\" and not \"position\"."<<endl;
		}
		if ( outStatus != 0 ){
			cerr<<"Error: While loading a "<< szVectorXmlType <<
				" vector. (outStatus="<< outStatus <<" )"<<endl;
			outStatus = 0;
		}
	}
	return setLoadedData;
}
















