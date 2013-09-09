/**
 * @file tFindImageStructure
 * file name: tFindImageStructure.cpp
 * @author Betti Oesterholz
 * @date 04.02.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for testing the findImageStructure() method of the child
 * classes of iFindImageStructure.
 *
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
 * This test is for testing the findImageStructure() method of the child
 * classes of iFindImageStructure.
 * It will test if the iFindImageStructure::findImageStructure()
 * method finds the structure.
 * @see iFindImageStructure::findImageStructure()
 *
 * The Fib test objects for the convertToFib() test are loaded from the
 * files in the subdirectories of the folder pDirTestObjects.
 *
 * Every testcase consists of one files with the image structure data.
 *
 * The names of these files will be loaded from the test case file.
 * @see getActualClassTestCaseFile()
 * Every line of this file is for one testcase. It contains the name of the
 * file for the testcase image structure.
 * The image structure is leaoded with the iFindImageStructure::restoreXml()
 * function.
 *
 *
 * call: tFindImageStructure [DIR_TESTDATA] [MAX_ITERATION]
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
04.02.2013  Oesterholz  created
*/


#include "version.h"
#include "fibDatatyps.h"

#include "cFindImageAreaSameColorSimple.h"
#include "cFindImageAreaLinearColorSimple.h"

#include "iFindImageStructure.h"
#include "cImageAreaSameColor.h"
#include "cImageAreaLinearColor.h"
#include "cImageSearchData.h"

#include "cPoint.h"
#include "cProperty.h"
#include "cRoot.h"

#include "cFibVector.h"
#include "cVectorPosition.h"
#include "cVectorProperty.h"
#include "cTypeProperty.h"
#include "cEvaluePositionList.h"
#include "cEvalueSimpleRGBA255.h"


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

#ifndef DIR_TESTOBJECTS_NIMAGE
	#define DIR_TESTOBJECTS_NIMAGE "../testObjects/"
#endif



using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;
using namespace fib::algorithms::nConvertToFib::nImage::nSearchForStructure;
using namespace fib::algorithms::nConvertToFib::nImage;
using namespace fib;
using namespace std;


const char * pDirTestObjects = DIR_TESTOBJECTS_NIMAGE;
unsigned long MAX_ITERATION  = 256;


enum tActualClass {
	C_FIND_IMAGE_AREA_SAME_COLOR_SIMPLE = 0,
	C_FIND_IMAGE_AREA_LINEAR_COLOR_SIMPLE = 1
} actualClass;


string getActualClassName();

int testFindImageStructure( unsigned long &ulTestphase );
unsigned int testFindImageStructureGiven(
		const cImageStructure * pImageStructureToUse,
		const double maxErrorPerValue,
		const set< pair< unsigned int, unsigned int> > setOverlappedPoints =
			set< pair< unsigned int, unsigned int> >() );



list< string > loadTestFileList( const string & szFilePath );
void createPath( const char * path );


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 1;//actual phase of the test
	int iReturn = 0;//return value of the test; the number of occured errors
	
	srand( time(NULL) );
	
	
	cout<<endl<<"Running test for the iFindImageStructure methods"<<endl;
	cout<<      "================================================"<<endl;
	cout<<      "================================================"<<endl;
	
	if ( 1 < argc ){
		//one parameter given; get parameter test data path
		pDirTestObjects = argv[1];
	}
	cout<<endl<<"The folder with the test data is "<<pDirTestObjects<<endl;
	
	if ( 2 < argc ){
		//two parameters given; read parameter iterators
		MAX_ITERATION = atol( argv[2] );
		if ( MAX_ITERATION < 1 ){
			MAX_ITERATION = 1;
		}
	}
	cout<<endl<<"Number of maximal iterators is "<<MAX_ITERATION<<endl;
	
	
//TODO enlarge tested
	for ( unsigned int uiActualClass = 0;
			uiActualClass <= 1; uiActualClass++ ){//valid from 0 till 1
		
		switch ( uiActualClass ){
			case 0:
				actualClass = C_FIND_IMAGE_AREA_SAME_COLOR_SIMPLE;
			break;
			case 1:
				actualClass = C_FIND_IMAGE_AREA_LINEAR_COLOR_SIMPLE;
			break;
		}
		
		
		cout<<endl<<"Running test for the "<<getActualClassName()<<" methods"<<endl;
		cout<<      "================================================"<<endl;
		
		//test the iConvertImageStructureToFib::convertToFib()
		const unsigned int iReturnTestCase = testFindImageStructure( ulTestphase );
		
		if ( iReturnTestCase == 0 ){
		
			cout<<endl<<endl<<"Test for "<<getActualClassName()<<
				" successfull: no errors occoured"<<endl;
		}else{
			cerr<<endl<<endl<<"Test for "<<getActualClassName()<<" failed: "<<
				iReturnTestCase<<" errors occoured"<<endl;
			iReturn += iReturnTestCase;
		}
	}
	
	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}
	
	return iReturn;
}



/**
 * This functions returns the actual class name.
 *
 * @return the actual class name
 */
string getActualClassName(){
	
	switch ( actualClass ){
		case C_FIND_IMAGE_AREA_SAME_COLOR_SIMPLE:
			return "cFindImageAreaSameColorSimple";
		break;
		case C_FIND_IMAGE_AREA_LINEAR_COLOR_SIMPLE:
			return "cFindImageAreaLinearColorSimple";
		break;
	}
	
	return "";
}


/**
 * This functions returns a string for the name of the actual class test
 * case file.
 *
 * @return name of the actual class test case file
 */
const char * getActualClassTestCaseFile(){
	
	switch ( actualClass ){
		case C_FIND_IMAGE_AREA_SAME_COLOR_SIMPLE:
			return ((const char *)("tFindImageAreaSameColorSimple.txt"));
		break;
		case C_FIND_IMAGE_AREA_LINEAR_COLOR_SIMPLE:
			return ((const char *)("tFindImageAreaLinearColorSimple.txt"));
		break;
	}
	
	return ((const char *)(""));
}


/**
 * This method prints the given vector to the given stream.
 *
 * @param streamToPrintTo the stream to print the vector to
 * @param pVector a pointer to the vector to print
 */
void printVector( ostream & streamToPrintTo,
		const cFibVector * pVector ){
	
	if ( pVector == NULL ){
		streamToPrintTo<<" no vector (NULL);"<<endl;
		return;
	}
	const unsigned int uiNumberOfElements =
		pVector->getNumberOfElements();
	
	streamToPrintTo<<" (";
	if ( 1 <= uiNumberOfElements ){
		//print the first vector element
		streamToPrintTo<<(pVector->getValue( 1 ));
	}
	for ( unsigned int uiActualElement = 2;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ){
		
		streamToPrintTo<<", "<<(pVector->getValue( uiActualElement ));
	}
	streamToPrintTo<<");"<<endl;
}


/**
 * This method prints the given points to the given stream.
 *
 * @param streamToPrintTo the stream to print the points to
 * @param setPoints the points to print
 */
void printPoints( ostream & streamToPrintTo,
		const set< pair< unsigned int, unsigned int> > & setPoints ){
	
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrPoint = setPoints.begin();
			itrPoint != setPoints.end(); itrPoint++ ){
		
		streamToPrintTo<<" ("<<itrPoint->first<<", "<<itrPoint->second<<");";
	}
	streamToPrintTo<<endl;
}


/**
 * This function compares the two given points sets.
 *
 * @param setPointsOriginal the correct points to compare
 * @param setPointsGenerated the wrong points to compare
 * @return the number of errors occured in the test
 */
unsigned int comparePoints(
		const set< pair< unsigned int, unsigned int> > & setPointsOriginal,
		const set< pair< unsigned int, unsigned int> > & setPointsGenerated ){
	
	unsigned int iReturn = 0;
	
	set< pair< unsigned int, unsigned int> > setToMuchCorrectPoints = setPointsOriginal;
	set< pair< unsigned int, unsigned int> > setToMuchWrongPoints = setPointsGenerated;
	set< pair< unsigned int, unsigned int> > setMissingCorrectPoints;
	set< pair< unsigned int, unsigned int> > setMissingWrongPoints;
	
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrCorrectPoint = setPointsOriginal.begin();
			itrCorrectPoint != setPointsOriginal.end(); itrCorrectPoint++ ){
		
		const unsigned int uiPointsErased =
			setToMuchWrongPoints.erase( *itrCorrectPoint );
		if ( uiPointsErased == 0 ){
			//point not in wrong points
			setMissingWrongPoints.insert( *itrCorrectPoint );
		}
	}
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrWrongPoint = setPointsGenerated.begin();
			itrWrongPoint != setPointsGenerated.end(); itrWrongPoint++ ){
		
		const unsigned int uiPointsErased =
			setToMuchCorrectPoints.erase( *itrWrongPoint );
		if ( uiPointsErased == 0 ){
			//point not in wrong points
			setMissingCorrectPoints.insert( *itrWrongPoint );
		}
	}
	if ( ! setToMuchCorrectPoints.empty() ){
		cerr<<endl<<"Error: To much original points."<<endl;
		printPoints( cerr, setToMuchCorrectPoints );
		iReturn++;
	}
	if ( ! setMissingCorrectPoints.empty() ){
		cerr<<endl<<"Error: Missing original points."<<endl;
		printPoints( cerr, setMissingCorrectPoints );
		iReturn++;
	}
	if ( ! setToMuchWrongPoints.empty() ){
		cerr<<endl<<"Error: To much generated points."<<endl;
		printPoints( cerr, setToMuchWrongPoints );
		cerr<<endl;
		iReturn++;
	}
	if ( ! setMissingWrongPoints.empty() ){
		cerr<<endl<<"Error: Missing generated points."<<endl;
		printPoints( cerr, setMissingWrongPoints );
		cerr<<endl;
		iReturn++;
	}
	return iReturn;
}


/**
 * This functions generates a number of points in an area.
 * All points coordinates are bigger equal 0 .
 *
 * @param uiSizeX the size of the area in the first / x dimension;
 * 	every returned point first element is lower as this value
 * @param uiSizeY the size of the area in the second / y dimension;
 * 	every returned point second element is lower as this value
 * @param uiNumberOfSeedPoints the number of start points to generate for
 * 	the area
 * @param ulRandomNeighbourPointsIterations the number of iterations
 * 	to generate new random neighbour points of the existing points
 * @return a set with random generated points
 */
set< pair< unsigned int, unsigned int> > generateRandomArea(
		unsigned int uiSizeX, unsigned int uiSizeY,
		unsigned int uiNumberOfSeedPoints,
		unsigned long ulRandomNeighbourPointsIterations ){
	
	set< pair< unsigned int, unsigned int> > setRandomStructurePoints;
	
	if ( uiNumberOfSeedPoints == 0 ){
		//no points to generate
		return setRandomStructurePoints;
	}
	
	pair< unsigned int, unsigned int> randomStructurePoint;
	for ( unsigned int uiActualSeedPoint = 0;
			uiActualSeedPoint < uiNumberOfSeedPoints; uiActualSeedPoint++ ){
		//generate and add seed point
		randomStructurePoint.first  = rand() % uiSizeX;
		randomStructurePoint.second = rand() % uiSizeY;
		
		setRandomStructurePoints.insert( randomStructurePoint );
	}//end for generate random structur points
	//generate random neighbour points
	for ( unsigned long ulIterationNeighbour = 0;
			ulIterationNeighbour < ulRandomNeighbourPointsIterations;
			ulIterationNeighbour++ ){
		//choose random point from structure
		const unsigned int uiPointChoosen =
			rand() % setRandomStructurePoints.size();
		
		set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setRandomStructurePoints.begin();
		for ( unsigned int uiActualPoint = 0; uiActualPoint < uiPointChoosen;
				uiActualPoint++, itrActualPoint++ ){
			//nothing to do
		}
		if ( itrActualPoint == setRandomStructurePoints.end() ){
			//Error: no structure point choosen
			continue;
		}
		//generate some of its neighbours
		if ( ( ( itrActualPoint->first + 1 ) < uiSizeX ) && ( rand() % 2 ) ){
			randomStructurePoint = (*itrActualPoint);
			randomStructurePoint.first++;
			setRandomStructurePoints.insert( randomStructurePoint );
		}
		if ( ( 0 < itrActualPoint->first ) && ( rand() % 2 ) ){
			randomStructurePoint = (*itrActualPoint);
			randomStructurePoint.first--;
			setRandomStructurePoints.insert( randomStructurePoint );
		}
		if ( ( ( itrActualPoint->second + 1 ) < uiSizeY ) && ( rand() % 2 ) ){
			randomStructurePoint = (*itrActualPoint);
			randomStructurePoint.second++;
			setRandomStructurePoints.insert( randomStructurePoint );
		}
		if ( ( 0 < itrActualPoint->second ) && ( rand() % 2 ) ){
			randomStructurePoint = (*itrActualPoint);
			randomStructurePoint.second--;
			setRandomStructurePoints.insert( randomStructurePoint );
		}
	}
	return setRandomStructurePoints;
}


/**
 * @param maxValue the maximum value to generate;
 * 	all generate values absolute will be lower equal tis value
 * @return a random positiv double value
 */
double randDouble( const double & maxValue){
	
	return ( ( ((double)rand()) - ( RAND_MAX / 2 ) ) /
		((double)((RAND_MAX - 1) / 2 + 1)) ) * maxValue;
}


/**
 * This function evalues the maximal coordinate values of the given points.
 *
 * @param setSetOfPoints the set with the points, of which to evalue the
 * 	maximal coordinate value (all coordinate values have to be positiv)
 * @return a pair with the maximal coordinate values;
 * 	if no maximal value could be evalued -1 is returned
 */
pair< longFib, longFib > evalueMaxCoordinates(
		const set< cVectorPosition > & setSetOfPoints ){
	//evalue the maximum dimension coordinate values
	
	//default if no point exists
	longFib lMaxX = -1;
	longFib lMaxY = -1;
	for ( set<cVectorPosition>::const_iterator
			itrActualPoint = setSetOfPoints.begin();
			itrActualPoint != setSetOfPoints.end(); itrActualPoint++ ){
		
		lMaxX = fib::max( lMaxX,
			roundToLongFib( itrActualPoint->getValue( 1 ) ) );
		lMaxY = fib::max( lMaxY,
			roundToLongFib( itrActualPoint->getValue( 2 ) ) );
	}
	return pair< longFib, longFib >( lMaxX, lMaxY );
}


/**
 * This function evalues the maximal coordinate values of the given points.
 *
 * @param setSetOfPoints the set with the points, of which to evalue the
 * 	maximal coordinate value (all coordinate values have to be positiv)
 * @return a pair with the maximal coordinate values;
 * 	if no maximal value could be evalued -1 is returned
 */
pair< longFib, longFib > evalueMaxCoordinates(
		const set< pair< unsigned int, unsigned int> > & setSetOfPoints ){
	//evalue the maximum dimension coordinate values
	
	//default if no point exists
	longFib lMaxX = -1;
	longFib lMaxY = -1;
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setSetOfPoints.begin();
			itrActualPoint != setSetOfPoints.end(); itrActualPoint++ ){
		
		lMaxX = fib::max( lMaxX, ((longFib)itrActualPoint->first) );
		lMaxY = fib::max( lMaxY, ((longFib)itrActualPoint->second) );
	}
	return pair< longFib, longFib >( lMaxX, lMaxY );
}


/**
 * This function evalues all border points of the given points.
 *
 * @param setStructurePoints the points from which to evalue the border points
 * @param pImageSearchData the search data for evaluing the border points;
 * 	every border point should have a not found and not overlapped neighbour
 * 	(if NULL a search structure will be evalued)
 * @return all border points of the given points
 */
set< pair< unsigned int, unsigned int> > evalueBorderPoints(
		const set< pair< unsigned int, unsigned int> > & setStructurePoints,
		const cImageSearchData * pImageSearchData ){
	
	set< pair< unsigned int, unsigned int> > setBorderStructurePoints;
	bool bOwnSearchData = false;
	if ( pImageSearchData == NULL ){
		//evalue image search data
		const pair< longFib, longFib > paMaxCoordinates =
			evalueMaxCoordinates( setStructurePoints );
		
		if ( ( paMaxCoordinates.first < 0 ) ||
				( paMaxCoordinates.second < 0 ) ){
			//can't choose border points
			return setBorderStructurePoints;
		}
		//create image data
		pImageSearchData = new cImageSearchData(
			paMaxCoordinates.first + 2, paMaxCoordinates.second + 2 );
		bOwnSearchData = true;
	}
	/*note: It would be faster to mark all points setStructurePoints in the
		 image structure pImageSearchData as found and then just check if
		 they have not found neighbours. But the test code should be
		 different to the source code.*/
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setStructurePoints.begin();
			itrActualPoint != setStructurePoints.end(); itrActualPoint++ ){
		
		const set< pair< unsigned int, unsigned int> > setPointNeighbours =
			pImageSearchData->getNotFoundNotOverlappedNeighbours(
				*itrActualPoint );
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrNeighbourPoint = setPointNeighbours.begin();
				itrNeighbourPoint != setPointNeighbours.end();
				itrNeighbourPoint++ ){
			
			set< pair< unsigned int, unsigned int> >::const_iterator
				itrPointInStructure = setStructurePoints.find(
					*itrNeighbourPoint );
			if ( itrPointInStructure == setStructurePoints.end() ){
				//neighbour point not found in structure -> point is border point
				setBorderStructurePoints.insert( *itrActualPoint );
				break;//check next point
			}
		}//end for all neighbour points
	}//end for all structure points
	if ( bOwnSearchData ){
		//delete created image data
		delete pImageSearchData;
	}
	return setBorderStructurePoints;
}




/**
 * This method chooses uiBorderPointsToGenerate random border points from
 * the given structure points.
 *
 * @param setStructurePoints the points from which to choose the border points
 * @param uiBorderPointsToGenerate the number of border points to choose (if possible)
 * @param pImageSearchData the search data for evaluing the border points;
 * 	every border point should have a not found and not overlapped neighbour;
 * 	(if NULL a search structure will be evalued)
 * @return a set of uiBorderPointsToGenerate border points from setStructurePoints
 */
set< pair< unsigned int, unsigned int> > chooseRandomBorderPoints(
		const set< pair< unsigned int, unsigned int> > & setStructurePoints,
		const unsigned int uiBorderPointsToGenerate,
		const cImageSearchData * pImageSearchData = NULL ){
	
	set< pair< unsigned int, unsigned int> > setRandomBorderPoints;
	if ( ( setStructurePoints.empty() ) || ( uiBorderPointsToGenerate == 0 ) ){
		//nothing to choose
		return setRandomBorderPoints;
	}
	set< pair< unsigned int, unsigned int> > setBorderPoints =
		evalueBorderPoints( setStructurePoints, pImageSearchData );
	
	if ( setBorderPoints.size() <= uiBorderPointsToGenerate ){
		//choose all border points
		return setBorderPoints;
	}
	
	for ( unsigned int uiActualBorder = 0;
			uiActualBorder < uiBorderPointsToGenerate; uiActualBorder++ ){
		//choose random point from structure
		const unsigned int uiPointChoosen =
			rand() % setBorderPoints.size();
		
		set< pair< unsigned int, unsigned int> >::iterator
			itrActualPoint = setBorderPoints.begin();
		for ( unsigned int uiActualPoint = 0; uiActualPoint < uiPointChoosen;
				uiActualPoint++, itrActualPoint++ ){
			//nothing to do
		}
		if ( itrActualPoint != setBorderPoints.end() ){
			
			setRandomBorderPoints.insert( *itrActualPoint );
			setBorderPoints.erase( itrActualPoint );
			
			if ( setBorderPoints.empty() ){
				//no more border points to choose
				break;
			}
		}else{
			cerr<<"Error: No structure border point to choosen as border point."<<endl;
			continue;
		}
	}//end for add random border points
	return setRandomBorderPoints;
}


/**
 * This function evalues points which are neighbours to the given
 * structure border points, but not in the structure.
 * This points can be added as overlapped points.
 *
 * @param pRandomImageStructure the image structure for which border points
 * 	to evalue the neighbour points
 * @param uiDistance the distance till which to evalue the neighbours
 * @return a list with the neighbours of the given structure border points
 */
set< pair< unsigned int, unsigned int> > overlappBorderNeighbours(
		const cImageStructure * pRandomImageStructure, unsigned int uiDistance = 4 ){
	
	const set< pair< unsigned int, unsigned int> > setStructurePoints =
		pRandomImageStructure->getStructurePointsPair();
	
	set< pair< unsigned int, unsigned int> > setNeighbourPoints =
		pRandomImageStructure->getStructureBorderPointsPair();
	if ( ( setStructurePoints.empty() ) ||
			( setNeighbourPoints.empty() ) || ( uiDistance == 0 ) ){
		//nothing to choose
		return setNeighbourPoints;
	}
	//evalue image search data
	pair< longFib, longFib > paMaxCoordinates =
		evalueMaxCoordinates( setStructurePoints );
	
	if ( ( paMaxCoordinates.first < 0 ) ||
			( paMaxCoordinates.second < 0 ) ){
		//can't choose border points
		return set< pair< unsigned int, unsigned int> >();
	}
	//create image data
	cImageSearchData imageSearchData(
		paMaxCoordinates.first + uiDistance, paMaxCoordinates.second + uiDistance );
	
	set< pair< unsigned int, unsigned int> > setNeighbourActual =
		setNeighbourPoints;
	set< pair< unsigned int, unsigned int> > setNeighbourNext;
	for ( unsigned int uiActualDistance = 0; uiActualDistance < uiDistance;
			uiActualDistance++ ){
		
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrActualNeighbour = setNeighbourActual.begin();
				itrActualNeighbour != setNeighbourActual.end();
				itrActualNeighbour++ ){
			
			const set< pair< unsigned int, unsigned int> > setNeighboursPoint =
				imageSearchData.getNeighbours( *itrActualNeighbour );
			
			setNeighbourNext.insert( setNeighboursPoint.begin(),
				setNeighboursPoint.end() );
		}
		/*weg
		cout<<"actual neighbour points:"<<endl<<flush;
		printPoints( cout, setNeighbourActual );
		cout<<"next neighbour points:"<<endl<<flush;
		printPoints( cout, setNeighbourNext );*/
		
		setNeighbourPoints.insert( setNeighbourNext.begin(),
			setNeighbourNext.end() );
		setNeighbourActual = setNeighbourNext;
		setNeighbourNext.clear();
	}
	/*weg
	cout<<"neighbour points (removing structure points):"<<endl<<flush;
	printPoints( cout, setNeighbourPoints );*/
	
	//remove points of the structure
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrPoint = setStructurePoints.begin();
			itrPoint != setStructurePoints.end(); itrPoint++ ){
		
		setNeighbourPoints.erase( *itrPoint );
	}
	/*weg
	cout<<"neighbour points (without structure points):"<<endl<<flush;
	printPoints( cout, setNeighbourPoints );
	*/
	return setNeighbourPoints;
}



/**
 * This function tests the iConvertImageStructureToFib::convertToFib()
 * methods.
 *
 * @param ulTestphase a reference to the number for the test phase
 * @return the number of errors occured in the test
 */
int testFindImageStructure( unsigned long &ulTestphase ){
	
	list< string > setErrorsInTestCase;
	int iReturn = 0;//return value of the test; the number of occured errors
	
	cout<<endl<<"Running test for the tFindImageStructure::convertToTiles() method"<<endl;
	cout<<      "================================================================="<<endl;
	
	//load the test file list
	const string szFilePath = string( pDirTestObjects ) + getActualClassTestCaseFile();
	
	list< string > liTestFiles = loadTestFileList( szFilePath );

	if ( ! liTestFiles.empty() ){
		//for each test file
		for ( list< string >::iterator itrTestCase = liTestFiles.begin();
				itrTestCase != liTestFiles.end(); itrTestCase++ ){
			
			ulTestphase++;
			cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing for finding an image structure for \""<<
				(*itrTestCase) <<"\""<<endl;
			
			//create path to test file
			const string szActualImageStructureDataPath =
				string( pDirTestObjects ) + (*itrTestCase);
			//load to use image structure
			ifstream inFile( szActualImageStructureDataPath.c_str() );
			
			intFib outStatus = 0;
			cImageStructure * pImageStructure =
				cImageStructure::restoreXml( inFile , &outStatus );
			
			if ( outStatus == 0 ){
				cout<<"Restoring the image structur in the Xml format from the file "<<
					szActualImageStructureDataPath<<" successfull."<<endl;
			}else{
				cerr<<"Error: Restoring the image structur in the Xml format from the file "<<
					szActualImageStructureDataPath<<" not successfull. (return status="<< outStatus <<")"<<endl;
				iReturn++;
				if ( pImageStructure != NULL ){
					delete pImageStructure;
				}
				//skip test case
				continue;
			}
			const set<cVectorPosition> & setStructureBorderPoints =
				pImageStructure->getStructureBorderPointsConst();
			if ( setStructureBorderPoints.empty() ){
				//no border points -> add some random border point
				cout<<"no border points -> add some random structure points as border points"<<endl;
				set< pair< unsigned int, unsigned int> > setRandomBorderPoints =
					chooseRandomBorderPoints(
						pImageStructure->getStructurePointsPair(), 3 );
				
				if ( ! setRandomBorderPoints.empty() ){
					pImageStructure->addStructureBorderPoints( setRandomBorderPoints );
				}else{
					cerr<<"Error: No structure points choosen as border poinst."<<endl;
					iReturn++;
					continue;
				}
			}
			set< pair< unsigned int, unsigned int> > setOverlappedPoints =
				overlappBorderNeighbours( pImageStructure );
			cout<<"Structure points:"<<endl<<flush;
			printPoints( cout, pImageStructure->getStructurePointsPair() );
			cout<<"Structure border points:"<<endl<<flush;
			printPoints( cout, pImageStructure->getStructureBorderPointsPair() );
			cout<<"Structure neighbour points:"<<endl<<flush;
			printPoints( cout, pImageStructure->getStructureNeighbourPointsPair() );
			cout<<endl<<flush;
			cout<<"Points which are marked as overlapped:"<<endl<<flush;
			printPoints( cout, setOverlappedPoints );
			
			
			//test for the given image structure
			unsigned int iErrorsInLastTestCase =
				testFindImageStructureGiven( pImageStructure, 0.0, setOverlappedPoints );
			
			for ( unsigned int uiActualIteration = 0;
					uiActualIteration < ( 1 + MAX_ITERATION / 32 ); uiActualIteration++ ){
				
				const double maxErrorPerValue = (double(rand() % 16));
				
				iErrorsInLastTestCase +=
					testFindImageStructureGiven( pImageStructure,
						maxErrorPerValue, setOverlappedPoints );
			}
			if ( 0 < iErrorsInLastTestCase ){
				//add area test file to error in test case list
				setErrorsInTestCase.push_back( *itrTestCase );
				iReturn += iErrorsInLastTestCase;
			}
			delete pImageStructure;
		}//end for all test cases
		
	}else{//if test file don't exists
		cerr<<"Error: No test files to test."<<endl;
		iReturn++;
	}//end if test file exists
	
	for ( unsigned long iteration = 0; iteration < MAX_ITERATION; iteration++ ){
		/*test for random generated image structure:
			- generate random image structure (MAX_ITERATION^(1/2) as max x and y size)
				- generate rand() % (rand() % (rand() % (log( MAX_ITERATION )+ 1 ) + 1) + 1 ) + 1 random seed points
				- generate random neighbour points for (rand % ((MAX_ITERATION^(1/2)*2)) * (rand % ((MAX_ITERATION^(1/2)*2)) iterations)
					- choose existing point and add some of its neighbours to the structure*/
		const unsigned long ulImageSize = sqrt( MAX_ITERATION ) + 1;
		const unsigned int  uiNumberOfSeedPoints =
			rand() % (rand() % (rand() % (
				((unsigned int)log( MAX_ITERATION )) + 1 ) + 1) + 1 ) + 1;
		const unsigned long ulRandomNeighbourPointsIterations =
			(rand() % (ulImageSize / 2 + 1)) * (rand() % (ulImageSize / 2 + 1));
		
		cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Generate new random image structure"<<
			"(image size="<<ulImageSize<<" #seed points="<<uiNumberOfSeedPoints<<
			" iterations for neighbour generation="<<ulRandomNeighbourPointsIterations<<endl;
		
		cImageStructure * pRandomImageStructure = NULL;
		//choose type of to generate image structure
		/*TODO change testFindImageStructureGiven to support other properties:
		const unsigned int uiPropertyTypeNumber = rand() % 4;
		unsignedIntFib uiPropertyType = 0;
		switch ( uiPropertyType ){
			0: uiPropertyType = cTypeProperty::COLOR_RGB;
			break;
			1: uiPropertyType = cTypeProperty::COLOR_GRAYSCALE;
			break;
			2: uiPropertyType = cTypeProperty::TRANSPARENCY;
			break;
			3: uiPropertyType = cTypeProperty::KELVIN;
			break;
		}*/
		switch ( actualClass ){
			case C_FIND_IMAGE_AREA_SAME_COLOR_SIMPLE:{
				cout<<"cVectorProperty vecBaseColor( cTypeProperty::COLOR_RGB ) = ( ";
				cVectorProperty vecBaseColor( cTypeProperty::COLOR_RGB );
				for ( unsigned int uiActualElement = 1;
						uiActualElement <= vecBaseColor.getNumberOfElements();
						uiActualElement++ ){
					const doubleFib dValueToSet = rand() % 256;
					cout<<dValueToSet<<", ";
					vecBaseColor.setValue( uiActualElement, rand() % 256 );
				}
				cout<<" )"<<endl;
				cout<<"pRandomImageStructure = new cImageAreaSameColor( vecBaseColor );"<<endl;
				pRandomImageStructure = new cImageAreaSameColor( vecBaseColor );
			}break;
			case C_FIND_IMAGE_AREA_LINEAR_COLOR_SIMPLE:{
				cout<<"cVectorProperty vecBaseColor( cTypeProperty::COLOR_RGB ) = ( ";
				cVectorProperty vecBaseColor( cTypeProperty::COLOR_RGB );
				for ( unsigned int uiActualElement = 1;
						uiActualElement <= vecBaseColor.getNumberOfElements();
						uiActualElement++ ){
					const doubleFib dValueToSet = rand() % 256;
					cout<<dValueToSet<<", ";
					vecBaseColor.setValue( uiActualElement, dValueToSet );
				}
				cout<<" )"<<endl;
				cout<<"cVectorProperty vecSlopeX( cTypeProperty::COLOR_RGB ) = ( ";
				cVectorProperty vecSlopeX( cTypeProperty::COLOR_RGB );
				for ( unsigned int uiActualElement = 1;
						uiActualElement <= vecSlopeX.getNumberOfElements();
						uiActualElement++ ){
					const doubleFib dValueToSet = ((doubleFib)(rand() % 256)) / 64.0;
					cout<<dValueToSet<<", ";
					vecSlopeX.setValue( uiActualElement, dValueToSet );
				}
				cout<<" )"<<endl;
				cout<<"cVectorProperty vecSlopeY( cTypeProperty::COLOR_RGB ) = ( ";
				cVectorProperty vecSlopeY( cTypeProperty::COLOR_RGB );
				for ( unsigned int uiActualElement = 1;
						uiActualElement <= vecSlopeY.getNumberOfElements();
						uiActualElement++ ){
					const doubleFib dValueToSet = ((doubleFib)(rand() % 256)) / 64.0;
					cout<<dValueToSet<<", ";
					vecSlopeY.setValue( uiActualElement, dValueToSet );
				}
				cout<<" )"<<endl;
				cout<<"pRandomImageStructure = new cImageAreaLinearColor( "<<
					"vecBaseColor, vecSlopeX, vecSlopeY );"<<endl;
				pRandomImageStructure = new cImageAreaLinearColor( vecBaseColor, vecSlopeX, vecSlopeY );
			}break;
			//TODO more structure types
		}
		/* generate rand() % (rand() % (rand() % (log( MAX_ITERATION )+ 1 )) + 1 ) + 1 random seed points*/
		set< pair< unsigned int, unsigned int> > setRandomStructurePoints =
			generateRandomArea( ulImageSize, ulImageSize,
				uiNumberOfSeedPoints, ulRandomNeighbourPointsIterations );
		
		
		cout<<"Number of generated structure points: "<<
			setRandomStructurePoints.size()<<endl<<flush;
		pRandomImageStructure->addStructurePoints( setRandomStructurePoints );
		//add border points for start points
		const unsigned int uiBorderPointsToGenerate =
			rand() % ((rand() % setRandomStructurePoints.size()) + 1) + 1;
		
		set< pair< unsigned int, unsigned int> > setRandomBorderPoints =
			chooseRandomBorderPoints( setRandomStructurePoints, uiBorderPointsToGenerate );
		
		cout<<"Number of generated structure border points: "<<
			setRandomBorderPoints.size()<<endl<<flush;
		pRandomImageStructure->addStructureBorderPoints( setRandomBorderPoints );
		
		cout<<"Structure points:"<<endl<<flush;
		printPoints( cout, setRandomStructurePoints );
		cout<<"Structure border points:"<<endl<<flush;
		printPoints( cout, setRandomBorderPoints );
		cout<<endl<<flush;
		
		set< pair< unsigned int, unsigned int> > setOverlappedPoints =
			overlappBorderNeighbours( pRandomImageStructure );
		if ( rand() % 8 != 0 ){
			//generate overlapped points
			set< pair< unsigned int, unsigned int> >
				setRandomOverlappedPoints = generateRandomArea( ulImageSize,
					ulImageSize, uiNumberOfSeedPoints, ulRandomNeighbourPointsIterations );
			//remove points in the structure from the overlapped points
			for ( set< pair< unsigned int, unsigned int> >::const_iterator
					itrActualPoint = setRandomStructurePoints.begin();
					itrActualPoint != setRandomStructurePoints.end();
					itrActualPoint++ ){
				setRandomOverlappedPoints.erase( *itrActualPoint );
			}
			setOverlappedPoints.insert( setRandomOverlappedPoints.begin(),
				setRandomOverlappedPoints.end() );
		}
		cout<<"Points which are marked as overlapped:"<<endl<<flush;
		printPoints( cout, setOverlappedPoints );
		
		//test for the given image structure
		unsigned int iErrorsInLastTestCase =
			testFindImageStructureGiven( pRandomImageStructure, 0.0,
				setOverlappedPoints );
		
		for ( unsigned int uiActualIteration = 0;
				uiActualIteration < ( 1 + MAX_ITERATION / 32 ); uiActualIteration++ ){
			
			const double maxErrorPerValue = (double(rand() % 16));
			
			iErrorsInLastTestCase +=
				testFindImageStructureGiven( pRandomImageStructure, maxErrorPerValue,
				setOverlappedPoints );
		}
		if ( 0 < iErrorsInLastTestCase ){
			//add area test file to error in test case list
			setErrorsInTestCase.push_back( "random structure" );
			iReturn += iErrorsInLastTestCase;
		}
		delete pRandomImageStructure;
	}
	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test part successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test part failed: "<<iReturn<<" errors occoured in "<<setErrorsInTestCase.size()<<" test cases"<<endl;
		
		cerr<<"Errors wher in test files: ";
		for ( list< string >::const_iterator
				itrTestCase = setErrorsInTestCase.begin();
				itrTestCase != setErrorsInTestCase.end(); itrTestCase++ ){
			
			cout<<"\""<<(*itrTestCase)<<"\""<<endl;
		}
		cout<<endl;
	}
	return iReturn;
}


/**
 * This function checks the distance of two vectors.
 *
 * @param pVector1 a pointer to the first vector to check
 * @param pVector2 a pointer to the second vector to check
 * @param dMaxDistance the maximal distance the vector should have
 * @param pImageData the image data for the propertys (to evalue the
 * 	minimal distance of properties)
 * @param bWarning if true a to great distance is not an error, but an warning
 * @return true if the distance of the vectors is lower equal dMaxDistance,
 * 	else false
 */
bool checkDistance( const cVectorProperty * pVector1, const cVectorProperty * pVector2,
		const double dMaxDistance, iImageData * pImageData, bool bWarning = false ){
	
	const unsigned int uiNumberOfElements = pVector1->getNumberOfElements();
	if ( uiNumberOfElements != pVector2->getNumberOfElements() ){
		//vectors don't have equal number of elements
		cerr<<"Error: Can't evalue distance, not equal number of elements."<<endl;
		return false;
	}
	const string strErrorType = ( bWarning ? "Warning" : "Error" );
	double dDistance = 0.0;
	
	//evalue half min distance
	const unsigned int uiPropertyType = pVector1->getPropertyType();
	const vector< unsigned int > vecIndexDim3 =
		pImageData->getDimension3IndexesForPropertyType( uiPropertyType );
	vector< double > vecMinDistanceHalf;
	vecMinDistanceHalf.push_back( 0.0 );//index counting starts with 1
	for ( vector< unsigned int >::const_iterator
			itrActualIndex = vecIndexDim3.begin();
			itrActualIndex != vecIndexDim3.end(); itrActualIndex++ ){
		
		const doubleFib dMinDistanceHalf = pImageData->getMinDifference(
			0, 0, (*itrActualIndex) ) / 2.0;
		vecMinDistanceHalf.push_back( dMinDistanceHalf );
	}
	
	
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ){
		
		const double dValue1 = pVector1->getValue( uiActualElement );
		const double dValue2 = pVector2->getValue( uiActualElement );
		
		double dDistanceElement = abs( dValue2 - dValue1 );
		
		if ( vecMinDistanceHalf[ uiActualElement ] < dDistanceElement ){
			//reduce distance with half minimum distance
			dDistanceElement -= vecMinDistanceHalf[ uiActualElement ];
		}else{//element has no error
			dDistanceElement = 0.0;
		}
		
		dDistance += dDistanceElement;
	}
	bool bDistanceOk = true;
	
	//check evalued distance
	if ( dMaxDistance == 0.0 ){
		//use number near 0 because of rounding errors
		if ( 0.000001 < dDistance ){
			//distance to great
			bDistanceOk = false;
		}
	}else{
		if ( dMaxDistance < dDistance ){
			//distance to great
			bDistanceOk = false;
		}
	}
	
	if ( ! bDistanceOk ){
		//distance to great
		cerr<<strErrorType<<": The distance of the original and generated property is to great ("<<
			"it is "<<dDistance<<", but should be lower equal "<<dMaxDistance<<")"<<endl;
		cerr<<"   original:"<<endl;
		printVector( cerr, pVector1 );
		cerr<<"   generated:"<<endl;
		printVector( cerr, pVector2 );
	}
	return bDistanceOk;
}


/**
 * This function checks if the distance of two vectors is to great.
 *
 * @param pVector1 a pointer to the first vector to check
 * @param pVector2 a pointer to the second vector to check
 * @param dMaxDistance the maximal distance the vector should have
 * @param pImageData the image data for the propertys (to evalue the
 * 	minimal distance of properties)
 * @param bWarning if true a to low distance is not an error, but an warning
 * @return true if the distance of the vectors is lower equal dMaxDistance,
 * 	else false
 */
bool checkDistanceToGreat( const cVectorProperty * pVector1, const cVectorProperty * pVector2,
		const double dMaxDistance, iImageData * pImageData, bool bWarning = false ){
	
	const unsigned int uiNumberOfElements = pVector1->getNumberOfElements();
	if ( uiNumberOfElements != pVector2->getNumberOfElements() ){
		//points don't have equal number of elements
		cerr<<"Error: Can't evalue distance, not equal number of elements."<<endl;
		return false;
	}
	const string strErrorType = ( bWarning ? "Warning" : "Error" );
	double dDistance = 0.0;
	for ( unsigned int uiActualElement = 1;
			uiActualElement <= uiNumberOfElements; uiActualElement++ ){
		
		const double dValue1 = pVector1->getValue( uiActualElement );
		const double dValue2 = pVector2->getValue( uiActualElement );
		
		if ( dValue1 < dValue2 ){
			dDistance += dValue2 - dValue1;
		}else{
			dDistance += dValue1 - dValue2;
		}
	}
	//check evalued distance
	bool bDistanceOk = true;
	
	//check evalued distance
	if ( dDistance < dMaxDistance ){
		//distance not big enough
		bDistanceOk = false;
	}
	if ( ! bDistanceOk ){
		//check minimal distance of points
		const unsigned int uiPropertyType = pVector1->getPropertyType();
		
		const vector< unsigned int > vecIndexDim3 =
			pImageData->getDimension3IndexesForPropertyType( uiPropertyType );
		unsigned int uiActualElement = 1;
		bDistanceOk = true;
		for ( vector< unsigned int >::const_iterator
				itrActualIndex = vecIndexDim3.begin();
				itrActualIndex != vecIndexDim3.end();
				itrActualIndex++, uiActualElement++ ){
			
			const doubleFib dMinDistanceHalf = pImageData->getMinDifference(
				0, 0, (*itrActualIndex) ) / 2.0;
			
			const doubleFib dValue1 = pVector1->getValue( uiActualElement );
			const doubleFib dValue2 = pVector2->getValue( uiActualElement );
			
			if ( abs( dValue1 - dValue2 ) < dMinDistanceHalf ){
				//distance smaaler than the half min distance -> distance not big enough
				bDistanceOk = false;
				break;
			}
		}//end for all dimension 3 index
	}
	
	if ( ! bDistanceOk ){
		//distance to great
		cerr<<strErrorType<<": The distance of the original and generated property is to great ("<<
			"it is "<<dDistance<<", but should be greater "<<dMaxDistance<<")"<<endl;
		cerr<<"   original:"<<endl;
		printVector( cerr, pVector1 );
		cerr<<"   generated:"<<endl;
		printVector( cerr, pVector2 );
	}
	
	return true;
}


/**
 * Dummy cConvertImageToFib for testing.
 */
class cConvertImageToFibDummy: public cConvertImageToFib{
public:
	/**
	 * constructor
	 *
	 * @param pInImageData a pointer to the image data to convert;
	 * 	Beware this object won't be copied, so keep it alive as long as
	 * 	this object exists. @see pImageData
	 */
	cConvertImageToFibDummy( const iImageData * pInImageData ):
			cConvertImageToFib( pInImageData ){
		//do nothing
	}
	
	/**
	 * This method is for converting the image data to a Fib object.
	 *
	 * @pattern Factory Method
	 * @return NULL (this object is a dummy)
	 */
	virtual cRoot * convertToFib(){
		//do nothing
		return NULL;
	}

};//end class cConvertImageToFibDummy


/**
 * This function test the iFindImageStructure::findImageStructure()
 * method for one test case.
 *
 * @param pImageStructureToUse the image structure for the to find image structure
 * @param maxErrorPerValue the maxErrorPerValue parameter for the
 * 	iFindImageStructure class
 * @param setOverlappedPoints a set with overlapped points for the search data
 * @return the number of errors occured in the test
 */
unsigned int testFindImageStructureGiven(
		const cImageStructure * pImageStructureToUse,
		const double maxErrorPerValue,
		const set< pair< unsigned int, unsigned int> > setOverlappedPoints ){
	
	unsigned int iReturn = 0;//return value of the test; the number of occured errors
	cout<<endl;
	
	if ( pImageStructureToUse == NULL ){
		
		cerr<<"Error: No image structure to use given."<<endl;
		iReturn++;
		return iReturn;
	}
	//minimum distance betwean property values
	const double MIN_DISTANCE = 1.0;
	
	//evalue the maximum dimension values
	pair< longFib, longFib > paMaxCoordinates( -1, -1 );
	{
		set< cVectorPosition > setPointsOfStructure =
			pImageStructureToUse->getStructurePoints();
		
		setPointsOfStructure.insert(
			pImageStructureToUse->getStructureBorderPointsConst().begin(),
			pImageStructureToUse->getStructureBorderPointsConst().end() );
		setPointsOfStructure.insert(
			pImageStructureToUse->getStructureNeighbourPointsConst().begin(),
			pImageStructureToUse->getStructureNeighbourPointsConst().end() );
		
		paMaxCoordinates = evalueMaxCoordinates( setPointsOfStructure );
	}
	//max points
	if ( ( paMaxCoordinates.first < 0 ) || ( paMaxCoordinates.second < 0 ) ){
		
		cerr<<"Error: Image with incorrect size: maximum X: "<<paMaxCoordinates.first<<
			" maximum Y: "<<paMaxCoordinates.second<<endl;
		iReturn++;
		return iReturn;
	}
	const longFib lMaxX = paMaxCoordinates.first + 2;
	const longFib lMaxY = paMaxCoordinates.second + 2;
	
	cout<<"Maximal image size x="<<lMaxX<<" y="<<lMaxY<<endl;
	//create image data
	cEvalueSimpleRGBA255 imageDataCorrect( lMaxX, lMaxY );
	//create image search data
	cImageSearchData * pImageSearchData = new cImageSearchData(
		&imageDataCorrect );
	//fill image data with correct points
	// add overlapped points to search structure wich are not in image structure
	pImageSearchData->registerOverlapped( setOverlappedPoints );
	
	cout<<"Evaluing image data matrix for correct data"<<endl<<flush;
	pImageStructureToUse->evalue( imageDataCorrect );
	
	if ( maxErrorPerValue != 0.0 ){
		//if maxErrorPerValue was given (not 0) add random error to points imageDataCorrect
		//for all structur points
		const set< pair< unsigned int, unsigned int> > setStructureData =
			pImageStructureToUse->getStructurePointsPair();
		const unsigned int uiMaxIndex = imageDataCorrect.getMaxIndex( 2 );
		
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrActualPoint = setStructureData.begin();
				itrActualPoint != setStructureData.end(); itrActualPoint++ ){
			//add random value to property elements
			//the sum of the error should be smaaler maxErrorPerValue
			double dRemainingErrorValue = maxErrorPerValue - MIN_DISTANCE;
			
			const unsigned int & uiX = itrActualPoint->first;
			const unsigned int & uiY = itrActualPoint->second;
			
			for ( unsigned int uiActualIndex = 0;
					( uiActualIndex <= uiMaxIndex ) &&
					( MIN_DISTANCE / 2.0 < dRemainingErrorValue );
					uiActualIndex++ ){
				
				if ( ( rand() % 2 ) == 0 ){
					//don't change value
					continue;
				}
				const double dErrorValue = randDouble( dRemainingErrorValue );
				dRemainingErrorValue -= abs( dErrorValue );
				
				const double dNewValue = imageDataCorrect.getValue(
					uiX, uiY, uiActualIndex );
				imageDataCorrect.setValue( dNewValue + dErrorValue,
					uiX, uiY, uiActualIndex );
			}//end for all property elements
		}//end for all structure points
	}//end if maximal error given
	
	bool bIsAntialised = pImageStructureToUse->isAntialised();
	unsigned long ulAntialisedPoints    = 0;
	unsigned long ulNotAntialisedPoints = 0;
	if ( bIsAntialised ){
		//antialise the border of area
		//evalue border point
		set< pair< unsigned int, unsigned int> > setStructurePoints =
			pImageStructureToUse->getStructurePointsPair();
		const set< pair< unsigned int, unsigned int> > setBorderStructurePoints =
			evalueBorderPoints( setStructurePoints, pImageSearchData );
		cout<<"Antialising the "<<setBorderStructurePoints.size()<<" border points."<<flush;
		/*set for the border points a property betwean area and its neighbour
		 *property (which is 0)*/
		//ignore maximal 1 / 11 of the border points
		unsigned int uiBorderPointsWhichCanBeIgnored =
			setBorderStructurePoints.size() / 11;
		const unsigned int uiNumberOfPropertyElements =
			imageDataCorrect.getMaxIndex( 2 );
		//longFib lMaxErrorInBorder = 0;
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrBorderPoint = setBorderStructurePoints.begin();
				itrBorderPoint != setBorderStructurePoints.end();
				itrBorderPoint++ ){
			
			if ( uiBorderPointsWhichCanBeIgnored != 0 ){
				if ( ( rand() % 11 ) == 0 ){
					//ignore border point
					uiBorderPointsWhichCanBeIgnored--;
					continue;
				}//else antialise border point
			}
			longFib lErrorInBorderPoint = 0;
			for ( unsigned int uiActualElement = 0;
					uiActualElement <= uiNumberOfPropertyElements;
					uiActualElement++ ){
				
				const unsigned int uiActualValue = imageDataCorrect.getValueUInt(
					itrBorderPoint->first, itrBorderPoint->second, uiActualElement );
				
				if ( uiActualValue < 2 ){
					//no values betwean uiActualValue and 0
					continue;
				}//else evaluate new value betwean 0 and uiActualValue
				const longFib lNewValue = rand() % ( uiActualValue - 1 ) + 1;
				lErrorInBorderPoint += uiActualValue - lNewValue;
				
				imageDataCorrect.setValue( lNewValue,
					itrBorderPoint->first, itrBorderPoint->second, uiActualElement );
			}
			if ( maxErrorPerValue < ((double)lErrorInBorderPoint) ){
				//error of point to great -> point have to be antialised
				ulAntialisedPoints++;
			}else{//error of point to low -> point is not antialised
				ulNotAntialisedPoints++;
			}
		}//end for change all border points
		cout<<" ("<<ulAntialisedPoints<<" antialised points and "<<
			ulNotAntialisedPoints<<" not antialised points)"<<endl;
	}//end if create antialising
	
	
	const unsigned int uiPropertyType = cTypeProperty::COLOR_RGB;
	//create find image structure strategy
	iFindImageStructure * pFindImageStructure = NULL;
	
	switch ( actualClass ){
		case C_FIND_IMAGE_AREA_SAME_COLOR_SIMPLE:{
			cout<<"pFindImageStructure = new cFindImageAreaSameColorSimple("<<
				"uiPropertyType=cTypeProperty::COLOR_RGB, maxErrorPerValue="<<maxErrorPerValue<<
				", bIsAntialised="<<(bIsAntialised?"true":"false")<<" );"<<endl<<flush;
			pFindImageStructure = new cFindImageAreaSameColorSimple(
				uiPropertyType, maxErrorPerValue, bIsAntialised );
		}break;
		case C_FIND_IMAGE_AREA_LINEAR_COLOR_SIMPLE:{
			cout<<"pFindImageStructure = new cFindImageAreaLinearColorSimple("<<
				"uiPropertyType=cTypeProperty::COLOR_RGB, maxErrorPerValue="<<maxErrorPerValue<<
				", bIsAntialised="<<(bIsAntialised?"true":"false")<<
				", dMaxErrorPerPropertyElement="<<(maxErrorPerValue / 3.0)<<" );"<<endl<<flush;
			pFindImageStructure = new cFindImageAreaLinearColorSimple(
				uiPropertyType, maxErrorPerValue, bIsAntialised,
				(maxErrorPerValue / 3.0) );
		}break;
	}
	if ( pFindImageStructure == NULL ){
		cerr<<"Error: No valid iFindImageStructure type."<<endl;
		iReturn++;
		delete pImageSearchData;
		return iReturn;
	}
	
	//create dummy cConvertImageToFib
	cConvertImageToFibDummy convertImageToFibDummy( &imageDataCorrect );
	//register overlapped points in search data
	(convertImageToFibDummy.getImageSearchData())->registerOverlapped(
		setOverlappedPoints );
	
	//run findImageStructure for random border point of pImageStructureToUse
	pair< long, long> paStartPoint;
	const set<cVectorPosition> & setStructureBorderPoints =
		pImageStructureToUse->getStructureBorderPointsConst();
	const unsigned int uiNumberOfBorderPoints =
		setStructureBorderPoints.size();
	if ( uiNumberOfBorderPoints < 1 ){
		cerr<<"Error: No border points to choose from."<<endl;
		iReturn++;
		delete pImageSearchData;
		delete pFindImageStructure;
		return iReturn;
	}
	//select a random start point
	long uiChoosenPoint = rand() % uiNumberOfBorderPoints;
	set<cVectorPosition>::const_iterator
			itrActualPoint = setStructureBorderPoints.begin();
	for ( ; ( 0 < uiChoosenPoint ) &&
			( itrActualPoint != setStructureBorderPoints.end() );
			uiChoosenPoint--, itrActualPoint++ ){
		//nothing to do
	}
	if ( itrActualPoint == setStructureBorderPoints.end() ){
		cerr<<"Error: Can not choose a point from the "<<
			uiNumberOfBorderPoints<<" border points of the structure."<<endl;
		iReturn++;
		delete pImageSearchData;
		delete pFindImageStructure;
		return iReturn;
	}
	paStartPoint.first  = roundToLongFib( itrActualPoint->getValue( 1 ) );
	paStartPoint.second = roundToLongFib( itrActualPoint->getValue( 2 ) );
	
	if ( bIsAntialised ){
		//set one neighbour point of start point not in structure as overlapped
		cImageSearchData * pSearchDataForFinding =
			convertImageToFibDummy.getImageSearchData();
		
		const set< pair< unsigned int, unsigned int> > setNeighboursOfStartPoint =
			pSearchDataForFinding->getNeighbours( paStartPoint );
		
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrActualNeighbour = setNeighboursOfStartPoint.begin();
				itrActualNeighbour != setNeighboursOfStartPoint.end();
				itrActualNeighbour++ ){
			if ( ! pImageStructureToUse->isStructurePoint( *itrActualNeighbour ) ){
				//point not in structure
				cout<<"registering neighbour point ("<<itrActualNeighbour->first<<
					", "<<itrActualNeighbour->second<<") of start point as overlapped (for antialising)"<<endl;
				pSearchDataForFinding->registerOverlapped( *itrActualNeighbour );
				break;
			}
		}
	}
	cout<<endl<<"pGeneratedImageStructure = pFindImageStructure->findImageStructure( "<<
		"paStartPoint=("<<paStartPoint.first<<", "<<paStartPoint.second<<"), "<<
		"&convertImageToFibDummy );"<<endl<<flush;
	cImageStructure * pGeneratedImageStructure =
		pFindImageStructure->findImageStructure( paStartPoint,
			&convertImageToFibDummy );
	
	//convert found image structure to found Fib object
	if ( pGeneratedImageStructure == NULL ){
		cerr<<"Error: Can not find a image structure (pGeneratedImageStructure=NULL)."<<endl;
		iReturn++;
		delete pImageSearchData;
		delete pFindImageStructure;
		return iReturn;
	}
	
	//convert found Fib object (found image structure) to found image data
	//create image data
	cEvalueSimpleRGBA255 imageDataFound( lMaxX, lMaxY );
	//fill image data with found points
	pGeneratedImageStructure->evalue( imageDataFound );
	
	//compare the points of the correct image data and found image data
	const set< pair< unsigned int, unsigned int> > setGenStructurePoints =
		pGeneratedImageStructure->getStructurePointsPair();
	const set< pair< unsigned int, unsigned int> > setGenStructureBorderPoints =
		pGeneratedImageStructure->getStructureBorderPointsPair();
	const set< pair< unsigned int, unsigned int> > setGenStructureNeighbourPoints =
		pGeneratedImageStructure->getStructureNeighbourPointsPair();
	const bool bGenStructureIsAntialised = pGeneratedImageStructure->isAntialised();
	//output generated structure
	cout<<"Points of generated "<<(bIsAntialised?"antialised ":"")<<"structure:"<<endl;
	printPoints( cout, setGenStructurePoints );
	cout<<"Border points of generated structure:"<<endl;
	printPoints( cout, setGenStructureBorderPoints );
	cout<<"Neighbour points of generated structure:"<<endl;
	printPoints( cout, setGenStructureNeighbourPoints );
	
	/* check image search structure data:
	 * 	-- structure points are markted as found and not overlapped
	 * 	-- structure border points are markted as found and not overlapped
	 * 	-- structure border points have not found neighbours
	 * 	-- structure neighbours are not (found or overlapped)
	 * 	-- all found points in search structure are in image structure
	 * 		(depending on antialised or not, border points are structure points or not)
	*/
	const cImageSearchData * pGenImageSearchData =
		convertImageToFibDummy.getImageSearchData();
	
	if ( bIsAntialised ){
		//antialised
		if ( ! bGenStructureIsAntialised ){
			/* check if the border neighbour points of the generated structure can be antialised
			 * - neighbour points property in original image betwean neighbour
			 *   property for gernerated structure and property in original
			 *   image for its neighbour*/
			unsigned long ulAntialisedPointsGen = 0;
			unsigned long ulNotAntialisedPointsGen = 0;
			for ( set< pair< unsigned int, unsigned int> >::const_iterator
					itrNeighbourPoint = setGenStructureNeighbourPoints.begin();
					itrNeighbourPoint != setGenStructureNeighbourPoints.end();
					itrNeighbourPoint++ ){
				
				const set< pair< unsigned int, unsigned int> > setNeighboursNeigh =
					pGenImageSearchData->getNotFoundNotOverlappedNeighbours( *itrNeighbourPoint );
				if ( setNeighboursNeigh.empty() ){
					continue;
				}
				const pair< unsigned int, unsigned int> & paNeighbourNeigh =
					*(setNeighboursNeigh.begin());
				
				const cVectorProperty vecNeighbour      =
					pGeneratedImageStructure->getProperty( *itrNeighbourPoint, uiPropertyType, true );
				const cVectorProperty vecNeighbourOrg   =
					imageDataCorrect.getProperty( *itrNeighbourPoint, uiPropertyType );
				const cVectorProperty vecNeighbourNeigh =
					imageDataCorrect.getProperty( paNeighbourNeigh, uiPropertyType );
				
				const unsignedIntFib uiNumberOfElements =
					vecNeighbour.getNumberOfElements();
				
				bool bOneDirection = true;
				for ( unsignedIntFib uiActualElement = 1;
						uiActualElement <= uiNumberOfElements; uiActualElement++ ){
					
					if ( ( vecNeighbour.getValue( uiActualElement ) < vecNeighbourOrg.getValue( uiActualElement ) ) ==
							( vecNeighbourNeigh.getValue( uiActualElement ) < vecNeighbourOrg.getValue( uiActualElement ) ) ){
						
						if ( ( vecNeighbourOrg.getValue( uiActualElement ) != vecNeighbour.getValue( uiActualElement ) ) &&
								( vecNeighbourOrg.getValue( uiActualElement ) != vecNeighbourNeigh.getValue( uiActualElement ) ) ){
							bOneDirection = false;
							break;
						}
					}
				}
				if ( bOneDirection ){
					//neighbour is antialised
					ulAntialisedPointsGen++;
				}else{//neighbour is not antialised
					ulNotAntialisedPointsGen++;
				}
			}//end for check all generated neighbour points if antialised
			
			if ( ( ulNotAntialisedPointsGen * 32 ) < ulAntialisedPointsGen ){
				//if 32 times more points are antialised then not -> create Error
				cerr<<"Error: The generated Fib object is not antialised"<<
					", but should be antialised "<<
					"("<<ulAntialisedPointsGen<<" antialised points and "<<
					ulNotAntialisedPointsGen<<" not antialised points; in orginal "<<
					ulAntialisedPoints<<" antialised points and "<<
					ulNotAntialisedPoints<<" not antialised points)."<<endl;
				iReturn++;
			}else{
				if ( ((ulNotAntialisedPointsGen + 1) * 10) < ulAntialisedPointsGen ){
					//if 10 times more points are antialised then not -> create warning
					cout<<"Warning: The generated Fib object is not antialised"<<
						", but should be antialised"<<
						"("<<ulAntialisedPointsGen<<" antialised points and "<<
						ulNotAntialisedPointsGen<<" not antialised points; in orginal "<<
						ulAntialisedPoints<<" antialised points and "<<
						ulNotAntialisedPoints<<" not antialised points)."<<endl;
				}
			}
			bIsAntialised = pGeneratedImageStructure->isAntialised();
		}
	}else{//not antialised
		if ( bGenStructureIsAntialised ){
			cerr<<"Error: The generated Fib object is antialised"<<
				", but should be not antialised."<<endl;
			iReturn++;
			bIsAntialised = pGeneratedImageStructure->isAntialised();
		}
	}
	
	
	//check if structure points are markted as found and not overlapped
	unsigned int uiErrorsInStructureMarkedCorrect = 0;
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setGenStructurePoints.begin();
			itrActualPoint != setGenStructurePoints.end(); itrActualPoint++ ){
		
		if ( ! pGenImageSearchData->isFound( *itrActualPoint ) ){
			cerr<<"Error: The point ("<<itrActualPoint->first<<", "<<
				itrActualPoint->second<<") of the generated structure "<<
				"was not market as found in the image search structure."<<endl;
			uiErrorsInStructureMarkedCorrect++;
		}
		if ( pGenImageSearchData->isOverlapped( *itrActualPoint ) ){
			cerr<<"Error: The point ("<<itrActualPoint->first<<", "<<
				itrActualPoint->second<<") of the generated structure "<<
				"was market as overlapped in the image search structure."<<endl;
			uiErrorsInStructureMarkedCorrect++;
		}
	}
	if ( uiErrorsInStructureMarkedCorrect != 0 ){
		cerr<<"Error: Ther where points of the generated structure marked incorrect."<<endl;
		cerr<<"Structure points:"<<endl;
		printPoints( cerr, setGenStructurePoints );
		iReturn++;
	}
	/*check if structure border points are markted as found and not overlapped
	and check if structure border points have not found neighbours */
	unsigned int uiErrorsInStructureBorderMarkedCorrect = 0;
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setGenStructureBorderPoints.begin();
			itrActualPoint != setGenStructureBorderPoints.end(); itrActualPoint++ ){
		
		if ( ! pGenImageSearchData->isFound( *itrActualPoint ) ){
			cerr<<"Error: The border point ("<<itrActualPoint->first<<", "<<
				itrActualPoint->second<<") of the generated structure "<<
				"was not market as found in the image search structure."<<endl;
			uiErrorsInStructureBorderMarkedCorrect++;
		}
		if ( pGenImageSearchData->isOverlapped( *itrActualPoint ) ){
			cerr<<"Error: The border point ("<<itrActualPoint->first<<", "<<
				itrActualPoint->second<<") of the generated structure "<<
				"was market as overlapped in the image search structure."<<endl;
			uiErrorsInStructureBorderMarkedCorrect++;
		}
		if ( ! bIsAntialised ){
			if ( ! pGenImageSearchData->hasNotFoundNotOverlappedNeighbours( *itrActualPoint ) ){
				cerr<<"Error: The border point ("<<itrActualPoint->first<<", "<<
					itrActualPoint->second<<") of the generated structure "<<
					"has no not found and no not overlapped neighbours."<<endl;
				uiErrorsInStructureBorderMarkedCorrect++;
			}
		}//else if antialised there can be border points with no neighbours
	}
	if ( uiErrorsInStructureBorderMarkedCorrect != 0 ){
		cerr<<"Error: Ther where border points of the generated structure marked incorrect."<<endl;
		cerr<<"Structure border points:"<<endl;
		printPoints( cerr, setGenStructureBorderPoints );
		iReturn++;
	}
	//check if structure neighbours are not (found or overlapped)
	unsigned int uiErrorsInStructureNeighbourMarkedCorrect = 0;
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setGenStructureNeighbourPoints.begin();
			itrActualPoint != setGenStructureNeighbourPoints.end();
			itrActualPoint++ ){
		
		if ( pGenImageSearchData->isFound( *itrActualPoint ) ){
			cerr<<"Error: The neighbour point ("<<itrActualPoint->first<<", "<<
				itrActualPoint->second<<") of the generated structure "<<
				"was market as found in the image search structure."<<endl;
			uiErrorsInStructureNeighbourMarkedCorrect++;
		}
		if ( pGenImageSearchData->isOverlapped( *itrActualPoint ) ){
			cerr<<"Error: The neighbour point ("<<itrActualPoint->first<<", "<<
				itrActualPoint->second<<") of the generated structure "<<
				"was market as overlapped in the image search structure."<<endl;
			uiErrorsInStructureNeighbourMarkedCorrect++;
		}
	}
	if ( uiErrorsInStructureNeighbourMarkedCorrect != 0 ){
		cerr<<"Error: Ther where neighbour points of the generated structure marked incorrect."<<endl;
		cerr<<"Structure neighbour points:"<<endl;
		printPoints( cerr, setGenStructureNeighbourPoints );
		iReturn++;
	}
	/* all found points in search structure are in image structure
	 * (depending on antialised or not, border points are structure points or not)*/
	unsigned int uiErrorsMarkedCorrectInStructure = 0;
	const set< pair< unsigned int, unsigned int> > setGenImageSearchDataFoundPoints =
		pGenImageSearchData->getFoundPointsAsPair();
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setGenImageSearchDataFoundPoints.begin();
			itrActualPoint != setGenImageSearchDataFoundPoints.end();
			itrActualPoint++ ){
		
		set< pair< unsigned int, unsigned int> >::const_iterator
			itrFoundPoint = setGenStructureBorderPoints.find( *itrActualPoint );
		const bool bPointInBorderPoints =
			( itrFoundPoint != setGenStructureBorderPoints.end() );
		
		if ( ( ! bGenStructureIsAntialised ) || ( ! bPointInBorderPoints ) ){
			//found point needs to be also in structure points
			set< pair< unsigned int, unsigned int> >::const_iterator
				itrFoundPoint = setGenStructurePoints.find( *itrActualPoint );
			const bool bPointInStructurePoints =
				( itrFoundPoint != setGenStructurePoints.end() );
			
			if ( ! bPointInStructurePoints ){
				cerr<<"Error: The found point ("<<itrActualPoint->first<<", "<<
					itrActualPoint->second<<") of the image search structure "<<
					"was not in the generated structure points"<<
					( bPointInBorderPoints ? ", but in the structure border points." : ".")<<endl;
				uiErrorsMarkedCorrectInStructure++;
			}
		}//else if found structure is antialised and point in border points -> it is OK
	}
	if ( uiErrorsMarkedCorrectInStructure != 0 ){
		cerr<<"Error: Ther where wrong marked structure points."<<endl;
		cerr<<"Marked as found points:"<<endl;
		printPoints( cerr, setGenImageSearchDataFoundPoints );
		if ( uiErrorsInStructureMarkedCorrect == 0 ){
			cerr<<"Structure points:"<<endl;
			printPoints( cerr, setGenStructurePoints );
		}
		if ( uiErrorsInStructureBorderMarkedCorrect == 0 ){
			cerr<<"Structure border points:"<<endl;
			printPoints( cerr, setGenStructureBorderPoints );
		}
		iReturn++;
	}
	//check if border points are in the structure points or not
	unsigned int uiErrorsBorderPointsInStructure = 0;
	cout<<"check if border points are in the structure points or not:"<<endl;
	if ( ! bGenStructureIsAntialised ){
		//if not antialised: check if border points are in structure points
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrActualPoint = setGenStructureBorderPoints.begin();
				itrActualPoint != setGenStructureBorderPoints.end(); itrActualPoint++ ){
			
			set< pair< unsigned int, unsigned int> >::const_iterator
				itrFoundPoint = setGenStructurePoints.find( *itrActualPoint );
			if ( itrFoundPoint == setGenStructurePoints.end() ){
				cerr<<"Error: The border point ("<<itrActualPoint->first<<", "<<
					itrActualPoint->second<<") of the generated structure "<<
					"is not in the generated structure points (not antialised)."<<endl;
				uiErrorsBorderPointsInStructure++;
			}
		}
	}else{//if antialised: check if border points are not in structure points
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrActualPoint = setGenStructureBorderPoints.begin();
				itrActualPoint != setGenStructureBorderPoints.end(); itrActualPoint++ ){
			
			set< pair< unsigned int, unsigned int> >::const_iterator
				itrFoundPoint = setGenStructurePoints.find( *itrActualPoint );
			if ( itrFoundPoint != setGenStructurePoints.end() ){
				cerr<<"Error: The border point ("<<itrActualPoint->first<<", "<<
					itrActualPoint->second<<") of the generated structure "<<
					"is in the generated structure points (antialised)."<<endl;
				uiErrorsBorderPointsInStructure++;
			}
		}
	}
	if ( uiErrorsBorderPointsInStructure != 0 ){
		cerr<<"Error: Not all border points are "<<
			(bGenStructureIsAntialised?"not in ":"in ")<<
			"the structure points."<<endl;
		cerr<<"Structure points:"<<endl;
		printPoints( cerr, setGenStructurePoints );
		cerr<<"Structure border points:"<<endl;
		printPoints( cerr, setGenStructureBorderPoints );
		iReturn++;
	}
	/*for all points in generated area check if the error to correct
		points is lower maxErrorPerValue*/
	cout<<"checking generated structure points:"<<endl;
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setGenStructurePoints.begin();
			itrActualPoint != setGenStructurePoints.end(); itrActualPoint++ ){
		
		const cVectorProperty vecCorrectProperty =
			imageDataCorrect.getProperty( *itrActualPoint, uiPropertyType );
		const cVectorProperty vecGeneratedProperty =
			pGeneratedImageStructure->getProperty( *itrActualPoint, uiPropertyType );
		//exclude paStartPoint
		const bool bWarning = ( paStartPoint.first == itrActualPoint->first ) &&
			( paStartPoint.second == itrActualPoint->second ) &&
			( 1 < setGenStructurePoints.size() );
		
		if ( ! checkDistance( &vecCorrectProperty, &vecGeneratedProperty,
				maxErrorPerValue, &imageDataCorrect, bWarning ) ){
			
			cerr<<"   point =("<<itrActualPoint->first<<", "<<itrActualPoint->second<< ")"<<endl;
			if ( ! bWarning ){
				iReturn++;
			}
		}
	}
	if ( ! bIsAntialised ){
		cout<<"checking generated structure border points:"<<endl;
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrActualPoint = setGenStructureBorderPoints.begin();
				itrActualPoint != setGenStructureBorderPoints.end(); itrActualPoint++ ){
			
			const cVectorProperty vecCorrectProperty =
				imageDataCorrect.getProperty( *itrActualPoint, uiPropertyType );
			const cVectorProperty vecGeneratedProperty =
				pGeneratedImageStructure->getProperty( *itrActualPoint, uiPropertyType );
			//exclude paStartPoint
			const bool bWarning = ( paStartPoint.first == itrActualPoint->first ) &&
				( paStartPoint.second == itrActualPoint->second ) &&
				( 1 < setGenStructurePoints.size() );
			
			if ( ! checkDistance( &vecCorrectProperty, &vecGeneratedProperty,
					maxErrorPerValue, &imageDataCorrect, bWarning ) ){
				
				cerr<<"   point =("<<itrActualPoint->first<<", "<<itrActualPoint->second<< ")"<<endl;
				if ( ! bWarning ){
					iReturn++;
				}
			}
		}
		/*for all neighbour points of generated area: check if there error
		is greater than maxErrorPerValue*/
		cout<<"checking generated structure neighbour points:"<<endl;
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrActualPoint = setGenStructureNeighbourPoints.begin();
				itrActualPoint != setGenStructureNeighbourPoints.end();
				itrActualPoint++ ){
			
			const cVectorProperty vecCorrectProperty =
				imageDataCorrect.getProperty( *itrActualPoint, uiPropertyType );
			const cVectorProperty vecGeneratedProperty =
				pGeneratedImageStructure->getProperty(
					*itrActualPoint, uiPropertyType, true );
			if ( ! checkDistanceToGreat( &vecCorrectProperty, &vecGeneratedProperty,
					maxErrorPerValue, &imageDataCorrect ) ){
				cerr<<"   point =("<<itrActualPoint->first<<", "<<itrActualPoint->second<< ")"<<endl;
				iReturn++;
			}
		}
	}else{//if bIsAntialised the error of border points should be greater than max error
		/*for all neighbour points of generated area: check if there error
		is greater than maxErrorPerValue*/
		cout<<"checking generated antialised structure border points:"<<endl;
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrActualPoint = setGenStructureBorderPoints.begin();
				itrActualPoint != setGenStructureBorderPoints.end();
				itrActualPoint++ ){
			
			const cVectorProperty vecCorrectProperty =
				imageDataCorrect.getProperty( *itrActualPoint, uiPropertyType );
			const cVectorProperty vecGeneratedProperty =
				pGeneratedImageStructure->getProperty(
					*itrActualPoint, uiPropertyType, true );
			//exclude paStartPoint
			const bool bWarning = ( paStartPoint.first == itrActualPoint->first ) &&
				( paStartPoint.second == itrActualPoint->second ) &&
				( 1 < setGenStructurePoints.size() );
			
			if ( ! checkDistanceToGreat( &vecCorrectProperty, &vecGeneratedProperty,
					maxErrorPerValue, &imageDataCorrect, bWarning ) ){
				
				cerr<<"   point =("<<itrActualPoint->first<<", "<<itrActualPoint->second<< ")"<<endl;
				if ( ! bWarning ){
					iReturn++;
				}
			}
		}
		
		//check if the border points are antialised points
		unsigned long ulAntialisedPointsGen = 0;
		unsigned long ulNotAntialisedPointsGen = 0;
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrBorderPoint = setGenStructureBorderPoints.begin();
				itrBorderPoint != setGenStructureBorderPoints.end();
				itrBorderPoint++ ){
			
			const set< pair< unsigned int, unsigned int> > setBorderPointNeigh =
				pGenImageSearchData->getNotFoundNotOverlappedNeighbours( *itrBorderPoint );
			if ( setBorderPointNeigh.empty() ){
				//border points with no neighbours can't be checked
				continue;
			}
			const pair< unsigned int, unsigned int> & paBorderNeigh =
				*(setBorderPointNeigh.begin());
			
			const cVectorProperty vecBorder      =
				pGeneratedImageStructure->getProperty( *itrBorderPoint, uiPropertyType, true );
			const cVectorProperty vecBorderOrg   =
				imageDataCorrect.getProperty( *itrBorderPoint, uiPropertyType );
			const cVectorProperty vecBorderNeigh =
				imageDataCorrect.getProperty( paBorderNeigh, uiPropertyType );
			
			const unsignedIntFib uiNumberOfElements =
				vecBorder.getNumberOfElements();
			
			bool bOneDirection = true;
			for ( unsignedIntFib uiActualElement = 1;
					uiActualElement <= uiNumberOfElements; uiActualElement++ ){
				
				if ( ( vecBorder.getValue( uiActualElement ) < vecBorderOrg.getValue( uiActualElement ) ) ==
						( vecBorderNeigh.getValue( uiActualElement ) < vecBorderOrg.getValue( uiActualElement ) ) ){
					
					if ( ( vecBorderOrg.getValue( uiActualElement ) != vecBorder.getValue( uiActualElement ) ) &&
							( vecBorderOrg.getValue( uiActualElement ) != vecBorderNeigh.getValue( uiActualElement ) ) ){
						bOneDirection = false;
						break;
					}
				}
			}
			if ( bOneDirection ){
				//border point is antialised
				ulAntialisedPointsGen++;
			}else{//border point is not antialised
				ulNotAntialisedPointsGen++;
			}
		}//end for check all generated border point points if antialised
		if ( 0 < ulNotAntialisedPointsGen ){
			//if not antialised points exists
			if ( ulAntialisedPointsGen < ( ulNotAntialisedPointsGen * 4 ) ){
				//if the antialised points are less than 4 times the not antialised points -> create Error
				cerr<<"Error: The generated Fib object is antialised"<<
					", but should be not antialised "<<
					"("<<ulAntialisedPointsGen<<" antialised points and "<<
					ulNotAntialisedPointsGen<<" not antialised points; in orginal "<<
					ulAntialisedPoints<<" antialised points and "<<
					ulNotAntialisedPoints<<" not antialised points)."<<endl;
				iReturn++;
			}else{
				if ( ulAntialisedPointsGen < ( ( ulNotAntialisedPointsGen - 1) * 10) ){
					//if the antialised points are less than 10 times the not antialised points -> create warning
					cout<<"Warning: The generated Fib object is not antialised"<<
						", but should be not antialised "<<
						"("<<ulAntialisedPointsGen<<" antialised points and "<<
						ulNotAntialisedPointsGen<<" not antialised points; in orginal "<<
						ulAntialisedPoints<<" antialised points and "<<
						ulNotAntialisedPoints<<" not antialised points)."<<endl;
				}
			}
		}
		
		
	}
	
	
	/*check if all neighbour points of generated area points are in
		structure as neighbour points and if all, and just these,
		structure points with neighbours outside of the structure are
		border points  */
	//evalue correct border and neighbour points of the generated structure points
	set< pair< unsigned int, unsigned int> > setBorderPoints;
	set< pair< unsigned int, unsigned int> > setNeighbourPoints;
	
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setGenStructurePoints.begin();
			itrActualPoint != setGenStructurePoints.end(); itrActualPoint++ ){
		
		set< pair< unsigned int, unsigned int> >
			setNotFoundNotOverlappedNeighbours =
				pGenImageSearchData->getNotFoundNotOverlappedNeighbours(
					*itrActualPoint );
		
		if ( ! setNotFoundNotOverlappedNeighbours.empty() ){
			//point has neighbours
			setBorderPoints.insert( *itrActualPoint );
			setNeighbourPoints.insert(
				setNotFoundNotOverlappedNeighbours.begin(),
				setNotFoundNotOverlappedNeighbours.end() );
		}
	}
	for ( set< pair< unsigned int, unsigned int> >::const_iterator
			itrActualPoint = setGenStructureBorderPoints.begin();
			itrActualPoint != setGenStructureBorderPoints.end(); itrActualPoint++ ){
		
		set< pair< unsigned int, unsigned int> >
			setNotFoundNotOverlappedNeighbours =
				pGenImageSearchData->getNotFoundNotOverlappedNeighbours(
					*itrActualPoint );
		
		if ( ! setNotFoundNotOverlappedNeighbours.empty() ){
			//point has neighbours
			setBorderPoints.insert( *itrActualPoint );
			setNeighbourPoints.insert(
				setNotFoundNotOverlappedNeighbours.begin(),
				setNotFoundNotOverlappedNeighbours.end() );
		}
	}
	//compare
	cout<<"Check structure border points:"<<endl;
	if ( ! bIsAntialised ){
		if ( comparePoints( setBorderPoints, setGenStructureBorderPoints ) != 0 ){
			cerr<<"Border points the image structure should have:"<<endl;
			printPoints( cerr, setBorderPoints );
			cerr<<"Generated structure border points:"<<endl;
			printPoints( cerr, setGenStructureBorderPoints );
			iReturn++;
		}
	}else{//if antialised border points can be in the area without neighbours outside
		//check if all found border points are in the generated structure
		for ( set< pair< unsigned int, unsigned int> >::const_iterator
				itrActualPoint = setGenStructureBorderPoints.begin();
				itrActualPoint != setGenStructureBorderPoints.end(); itrActualPoint++ ){
			
			setBorderPoints.erase( *itrActualPoint );
		}
		if ( ! setBorderPoints.empty() ){
			cerr<<"Error: There are border points which are not in the "<<
				"antialised image structure."<<endl;
			cerr<<"border points which are not in the antialised image structure:"<<endl;
			printPoints( cerr, setBorderPoints );
			iReturn++;
		}
	}
	cout<<"Check structure neighbour points:"<<endl;
	if ( comparePoints( setNeighbourPoints, setGenStructureNeighbourPoints ) != 0 ){
		cerr<<"Neighbour points the image structure should have:"<<endl;
		printPoints( cerr, setNeighbourPoints );
		cerr<<"Generated structure neighbour points:"<<endl;
		printPoints( cerr, setGenStructureNeighbourPoints );
		iReturn++;
	}
	if ( 0 < iReturn ){
		cerr<<endl<<"Errors occured for generated image structure:"<<endl;
		pGeneratedImageStructure->storeXml( cerr );
		cerr<<endl;
	}
	
	//cout<<"delete pGeneratedImageStructure;"<<endl<<flush;
	delete pGeneratedImageStructure;
	//cout<<"delete pImageSearchData;"<<endl<<flush;
	delete pImageSearchData;
	//cout<<"delete pFindImageStructure;"<<endl<<flush;
	delete pFindImageStructure;
	cout<<"Errors in test: "<<iReturn<<endl<<flush;
	
	return iReturn;
}



/**
 * This function reads the given file and returns a list with its lines.
 * Every line of this file is for one testcase. It contains the name of the
 * file for the testcase image structure.
 *
 * @param szFilePath the path wher the file list to check is stored
 * @return a list with the files to check
 */
list< string > loadTestFileList( const string & szFilePath ){

	list< string > liFiles;
	
	ifstream ifStream( szFilePath.c_str() );
	
	if ( ! ifStream.good() ){
		
		cerr<<"Error: Couldn't read the folder list "<< szFilePath <<endl;
		return liFiles;
	}
	char szBuffer[ 1024 ];
	
	while( ifStream.good() ){
		
		string testDataFiles;
		
		ifStream.getline( szBuffer, 1024 );
		
		const string szImageStructureData = string( szBuffer );
		if ( szImageStructureData.empty() ){
			//no file name
			continue;
		}//else store file name
		
		liFiles.push_back( szImageStructureData );
	}
	return liFiles;
}



/** @def PATH_SEPERATOR the operating system dependent seperator in a filepath */
#ifdef linux
	#define PATH_SEPERATOR      '/'
	#define NOT_PATH_SEPERATOR  '\\'
#else//dos/windows
	#define PATH_SEPERATOR      '\\'
	#define NOT_PATH_SEPERATOR  '/'
#endif


/**
 * This function checks if a file for the given path exists and can be opened.
 *
 * @param path a string for the path to be cheked
 * @return true if the path exists, else false
 */
bool checkPath( const char* szPath ){

	if  ( szPath == NULL ){
		//no path given
		return false;
	}
	ifstream testFile( szPath );
	if( testFile ){
		//test file exists
		testFile.close();
		return true;
	}//else test file dos not exists
	return false;
}


/**
 * If the path folders are not existing, this function creats them.
 *
 * @param szPath the string of the path that should be existing
 */
void createPath( const char * szPath ){
	//maxC = maximal chars to read; to avoid infinity loops
	unsigned long maxC  = 0;
	unsigned long count = 0;
	if  ( szPath == NULL ){
		return;
	}
	//begin with the first folder, check if the folder exists and if not creat it
	char szFolder[ 1024 ];
	char mkDir[ 1024 ];
	for ( ; ( maxC < 100000 ) && ( szPath[ count ] != 0x0 ) ; maxC++ ){
		//check next szFolder
		for ( ; ( maxC < 100000 ) && ( szPath[ count ] != 0x0 ) ; maxC++ ){
			//read szFolder from szPath
			if ( szPath[ count ] == PATH_SEPERATOR ){
				
				szFolder[ count ] = PATH_SEPERATOR;
				count++;
				break;
			}else{
				szFolder[ count ] = szPath[ count ];
				count++;
			}
		}
		szFolder[ count ] = 0;
		if ( ( count != 0 ) &&
				! ( ( count == 1 ) && ( szFolder[0] == PATH_SEPERATOR ) ) &&
				! ( ( count == 2) && (szFolder[0] == '.' ) &&
					( szFolder[1] == PATH_SEPERATOR ) ) &&
				! ( checkPath( szFolder ) )
				){
			// if in szFolder is a valid path
			sprintf( mkDir, "mkdir %s ", szFolder );
			system( mkDir );
		}
		if ( szPath[ count ] == 0 ){
			return;
		}
	}
}












