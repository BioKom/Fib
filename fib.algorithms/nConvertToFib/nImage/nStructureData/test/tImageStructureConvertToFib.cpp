/**
 * @file tImageStructureConvertToFib
 * file name: tImageStructureConvertToFib.cpp
 * @author Betti Oesterholz
 * @date 04.02.2013
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for testing the convertToFib() method of the child classes
 * of cImageStructure.
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
 * This test is for testing mainly the convertToFib() method of the child
 * classes of cImageStructure.
 * It will test if the iConvertImageStructureToFib::convertToFib()
 * method converts given areas into a  equivalent Fib object.
 * @see iConvertImageStructureToFib::convertToFib()
 * It will also test the cImageStructure methods.
 * @see cImageStructure
 *
 * The Fib test objects for the convertToFib() test are loaded from the
 * files in the subdirectories of the folder pDirTestObjects.
 *
 * Every testcase consists of three files: one with the image structure data,
 * one with the points for the cImageSearchData of the overlapt points and
 * one with the data of the converted area.
 * The names of these files will be loaded from the test case file.
 * Every line of this file is for one testcase. The three file names are
 * seperated by a semicolon ';'. The first file name of a line contains the
 * data of the image structure to convert, the second the data for the
 * overlaped points and the third the data of the converted area (to
 * compare with).
 * E.g.: "imageStructureToConvert.xml;allreadyFoundPoints.xml;correctArea.xml"
 * The image structure is leaoded with the cImageStructure::restoreXml()
 * function.
 * The overlaped points area loaded into a cImageSearchData object.
 * The points of the correct area will be loaded into a list with points
 * and ther properties.
 * With the loaded image structure data the convertToTiles() methods of
 * cImageStructure object is called and the result evalued.
 * The evalued result will then be checked with the loaded data of the
 * correct area.
 *
 * The data, in the test files, is stored in the Fib XML format. Files with
 * the area data (or rather all files except the image structure file) have
 * as the root XML element, a XML element with the name "data". In the
 * "data" XML element contains the list with Fib elements, which are evalued.
 * Every list element is an evalued Fib element (a positions vector)
 * followed by it's properties as property vectors (for the correct area,
 * the search data has no properties).
 *
 *
 * call: tImageStructureConvertToFib [DIR_TESTDATA] [MAX_ITERATION]
 *
 * parameters:
 * 	DIR_TESTDATA
 * 		The path wher the testdata could be found. The standard folder is
 * 		"testObjects/".
 * 	MAX_ITERATION
 * 		The number of iterators for the random tests (test with given
 * 		parameters for convertToTiles()).
 * 		Just works with the DIR_TESTDATA parameter given.
 */
/*
History:
04.02.2013  Oesterholz  created
*/

//TODO check


//TODO test equal

#include "version.h"
#include "fibDatatyps.h"

#include "cImageStructure.h"
#include "cImageAreaSameColor.h"
#include "cImageAreaLinearColor.h"
#include "cImageSearchData.h"

#include "cList.h"
#include "cPoint.h"
#include "cProperty.h"
#include "cRoot.h"
#include "cArea.h"
#include "cFunction.h"
#include "cFibSet.h"
#include "cFibMatrix.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"
#include "cTypeProperty.h"
#include "cEvaluePositionList.h"
#include "cEvalueFibElementList.h"

#include "nBits.h"


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
	#define DIR_TESTOBJECTS_NIMAGE "../testObjects/"
#endif


#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif

//if true the stored file will be overwritten from the next stored file
bool bOverwriteFiles = false;


using namespace fib::algorithms::nConvertToFib::nImage::nStructureData;
using namespace fib;
using namespace std;


const char * pDirTestObjects = DIR_TESTOBJECTS_NIMAGE;
unsigned long MAX_ITERATION = 256;


enum tActualClass { C_IMAGE_STRUCTURE = 0,
	C_IMAGE_AREA_SAME_COLOR = 1,
	C_IMAGE_AREA_LINEAR_COLOR = 2
} actualClass;


cImageStructure * getActualClass();
cImageStructure * copyImageStructure( cImageStructure * pImageStructureToCopy );
string getActualClassName();

int testImageStructurePoints( unsigned long &ulTestphase );
int testConvertToFib( unsigned long &ulTestphase );


unsigned int testConvertForObject( const string szActualImageStructureData,
		const string szActualSearchData, const string szActualAreaData,
		const bool bGiveParameters = false,
		double maxValue = 65536.0, const long ulMaxErrorPerPoint = 0.0 );


/**
 * The class with the data of the test files.
 */
class cTestDataFiles{
public:
	/**
	 * The file with the to test image structure.
	 */
	string szImageStructureData;
	
	/**
	 * The file with the search data for convering the image structure.
	 */
	string szSearchData;
	
	/**
	 * The file with the data of the area to convert.
	 */
	string szAreaData;
	
	/**
	 * Standard constructor
	 */
	cTestDataFiles( const string szInStructureData = "",
		const string szInSearchData = "", const string szInAreaData = "" ):
			szImageStructureData( szInStructureData ),
			szSearchData( szInSearchData ), szAreaData( szInAreaData ){
		//nothing to do
	}
	
	
};

list< cTestDataFiles > loadTestFileList( const string szFilePath );
set<cVectorPosition> loadPositionData( const char * szFilename );
list< pair< cVectorPosition, list< cVectorProperty > > >
	loadPositionPropertyData( const char * szFilename );
void createPath( const char * path );


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test
	int iReturn = 0;//return value of the test; the number of occured Errors
	
	srand( time(NULL) );
	
	//create the test output folder DIR_OUTPUT if not existing
	createPath( DIR_OUTPUT );
	
	
	cout<<endl<<"Running Test for the cImageStructure methods"<<endl;
	cout<<      "============================================"<<endl;
	cout<<      "============================================"<<endl;
	
	if ( 1 < argc ){
		//one parameter given; get parameter test data path
		pDirTestObjects = argv[1];
	}
	cout<<endl<<"The folder with the test data is "<<pDirTestObjects<<endl;
	
	if ( 2 < argc ){
		//two parameters given; read parameter iterators
		MAX_ITERATION = atol( argv[1] );
		if ( MAX_ITERATION < 1 ){
			MAX_ITERATION = 1;
		}
	}
	cout<<endl<<"Number of maximal iterators is "<<MAX_ITERATION<<endl;
	
	
//TODO enlarge tested
	for ( unsigned int uiActualClass = 0;
			uiActualClass <= 3; uiActualClass++ ){
		
		switch ( uiActualClass ){
			case 0:
				actualClass = C_IMAGE_STRUCTURE;
			break;
			case 1:
				actualClass = C_IMAGE_AREA_SAME_COLOR;
			break;
			case 2:
				actualClass = C_IMAGE_AREA_LINEAR_COLOR;
			break;
		}
		
		
		cout<<endl<<"Running Test for the "<<getActualClassName()<<" methods"<<endl;
		cout<<      "=============================================="<<endl;
		
		//test the cImageStructure methods
		//TODO comment in
		iReturn += testImageStructurePoints( ulTestphase );
		
		
		//test the iConvertImageStructureToFib::convertToFib()
		iReturn += testConvertToFib( ulTestphase );
		
		if ( iReturn == 0 ){
		
			cout<<endl<<endl<<"Test for "<<getActualClassName()<<
				" successfull: no errors occoured"<<endl;
		}else{
			cerr<<endl<<endl<<"Test for "<<getActualClassName()<<" failed: "<<
				iReturn<<" errors occoured"<<endl;
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
 * This functions returns a pointer to the actual class to test.
 *
 * @return pointer to the actual class to test
 * 	Beware: You have to delete the class after usage.
 */
cImageStructure * getActualClass(){
	
	switch ( actualClass ){
		case C_IMAGE_STRUCTURE:
			return new cImageStructure();
		break;
		case C_IMAGE_AREA_SAME_COLOR:
			return new cImageAreaSameColor( cVectorProperty(
				cTypeProperty( 1 ) ) );
		break;
		case C_IMAGE_AREA_LINEAR_COLOR:
			return new cImageAreaLinearColor(
				cVectorProperty( cTypeProperty( 1 ) ),
				cVectorProperty( cTypeProperty( 1 ) ),
				cVectorProperty( cTypeProperty( 1 ) ) );
		break;
	}
	
	return new cImageStructure();
}


/**
 * This functions returns a pointer to a copy of the given object.
 * The object should have the type of the actual class.
 *
 * @param pImageStructureToCopy the class to copy
 * @return pointer to the copy of the given object
 * 	Beware: You have to delete the class after usage.
 */
cImageStructure * copyImageStructure( cImageStructure * pImageStructureToCopy ){
	
	switch ( actualClass ){
		case C_IMAGE_STRUCTURE:
			return new cImageStructure( *pImageStructureToCopy );
		break;
		case C_IMAGE_AREA_SAME_COLOR:
			return new cImageAreaSameColor(
				*((cImageAreaSameColor*)pImageStructureToCopy) );
		break;
		case C_IMAGE_AREA_LINEAR_COLOR:
			return new cImageAreaLinearColor(
				*((cImageAreaLinearColor*)pImageStructureToCopy) );
		break;
	}
	
	return getActualClass();
}


/**
 * This functions returns the actual class name.
 *
 * @return the actual class name
 */
string getActualClassName(){
	
	switch ( actualClass ){
		case C_IMAGE_STRUCTURE:
			return "ImageStructure";
		break;
		case C_IMAGE_AREA_SAME_COLOR:
			return "ImageAreaSameColor";
		break;
		case C_IMAGE_AREA_LINEAR_COLOR:
			return "ImageAreaLinearColor";
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
		case C_IMAGE_STRUCTURE:
			return ((const char *)("tImageStructure.txt"));
		break;
		case C_IMAGE_AREA_SAME_COLOR:
			return ((const char *)("tImageAreaSameColor.txt"));
		break;
		case C_IMAGE_AREA_LINEAR_COLOR:
			return ((const char *)("tImageAreaLinearColor.txt"));
		break;
	}
	
	return ((const char *)(""));
}


/**
 * @return generates a random point
 */
cVectorPosition generateRandomPoint(){
	
	cVectorPosition position( 2 );
	
	position.setValue( 1, rand() % 1024 );
	position.setValue( 2, rand() % 1024 );
	
	return position;
}


/**
 * This method prints the given points to the given stream.
 *
 * @param streamToPrintTo the points to print the points to
 * @param setPoints the points to print
 */
void printPoints( ostream & streamToPrintTo, set<cVectorPosition> setPoints ){
	
	for ( set<cVectorPosition>::iterator itrPoint = setPoints.begin();
			itrPoint != setPoints.end(); itrPoint++ ){
		
		itrPoint->storeXml( streamToPrintTo );
	}
}


/**
 * This function compares the two given points sets.
 *
 * @param correctPoints the correct points to compare
 * @param wrongPoints the wrong points to compare
 */
void comparePoints( set<cVectorPosition> setCorrectPoints,
		set<cVectorPosition> setWrongPoints ){
	
	set<cVectorPosition> setToMuchCorrectPoints = setCorrectPoints;
	set<cVectorPosition> setToMuchWrongPoints = setWrongPoints;
	set<cVectorPosition> setMissingCorrectPoints;
	set<cVectorPosition> setMissingWrongPoints;
	
	for ( set<cVectorPosition>::iterator
			itrCorrectPoint = setCorrectPoints.begin();
			itrCorrectPoint != setCorrectPoints.end(); itrCorrectPoint++ ){
		
		const unsigned int uiPointsErased =
			setToMuchWrongPoints.erase( *itrCorrectPoint );
		if ( uiPointsErased == 0 ){
			//point not in wrong points
			setMissingWrongPoints.insert( *itrCorrectPoint );
		}
	}
	for ( set<cVectorPosition>::iterator
			itrWrongPoint = setWrongPoints.begin();
			itrWrongPoint != setWrongPoints.end(); itrWrongPoint++ ){
		
		const unsigned int uiPointsErased =
			setToMuchCorrectPoints.erase( *itrWrongPoint );
		if ( uiPointsErased == 0 ){
			//point not in wrong points
			setMissingCorrectPoints.insert( *itrWrongPoint );
		}
	}
	if ( ! setToMuchCorrectPoints.empty() ){
		cerr<<endl<<"Error: To much correct points."<<endl;
		printPoints( cerr, setToMuchCorrectPoints );
	}
	if ( ! setMissingCorrectPoints.empty() ){
		cerr<<endl<<"Error: Missing correct points."<<endl;
		printPoints( cerr, setMissingCorrectPoints );
	}
	if ( ! setToMuchWrongPoints.empty() ){
		cerr<<endl<<"Error: To much wrong points."<<endl;
		printPoints( cerr, setToMuchWrongPoints );
	}
	if ( ! setMissingWrongPoints.empty() ){
		cerr<<endl<<"Error: Missing wrong points."<<endl;
		printPoints( cerr, setMissingWrongPoints );
	}
	
}








/**
 * This function tests the cImageStructure methods.
 *
 * @param ulTestphase a reference to the number for the test phase
 * @return the number of errors occured in the test
 */
int testImageStructurePoints( unsigned long &ulTestphase ){
	
	int iReturn = 0;//return value of the test; the number of occured errors
	
	cImageStructure * pImageStructure = getActualClass();
	const cImageStructure * pImageStructureConst = pImageStructure;
	
	bool bIsAntialised = false;
	
	set<cVectorPosition> structurePoints;
	set<cVectorPosition> structureBorderPoints;
	set<cVectorPosition> structureNeighbourPoints;
	
	//test the initial values
	if ( getActualClassName() == pImageStructure->getName() ){
		cout<<"The image structure class name is correctly \""<<
			pImageStructure->getName()<<"\" ."<<endl;
	}else{
		cerr<<"Error: The image structure class name is \""<<
			pImageStructure->getName()<<"\", but should be \""<<
			getActualClassName()<<"\"."<<endl;
		iReturn++;
	}
	
	if ( ! pImageStructure->isAntialised() ){
		cout<<"The image structure is correctly not antialised."<<endl;
	}else{
		cerr<<"Error: The image structure is antialised, but shouldn't be."<<endl;
		iReturn++;
	}
	{
		set<cVectorPosition> structorPointsRet =
			pImageStructure->getStructurePoints();
		if ( structurePoints == structorPointsRet ){
			cout<<"The image structure points are correct."<<endl;
		}else{
			cerr<<"Error: The image structure points are not correct."<<endl;
			comparePoints( structurePoints, structorPointsRet );
			iReturn++;
		}
		
		const set<cVectorPosition> & structorPointsRetConst =
			pImageStructureConst->getStructurePointsConst();
		if ( structurePoints == structorPointsRetConst ){
			cout<<"The const image structure points are correct."<<endl;
		}else{
			cerr<<"Error: The const image structure points are not correct."<<endl;
			comparePoints( structurePoints, structorPointsRetConst );
			iReturn++;
		}
		
		set<cVectorPosition> structorBorderPointsRet =
			pImageStructure->getStructureBorderPoints();
		if ( structureBorderPoints == structorBorderPointsRet ){
			cout<<"The image structure border points are correct."<<endl;
		}else{
			cerr<<"Error: The image structure border points are not correct."<<endl;
			comparePoints( structureBorderPoints, structorBorderPointsRet );
			iReturn++;
		}
		
		const set<cVectorPosition> & structorBorderPointsRetConst =
			pImageStructureConst->getStructureBorderPointsConst();
		if ( structureBorderPoints == structorBorderPointsRetConst ){
			cout<<"The image structure const border points are correct."<<endl;
		}else{
			cerr<<"Error: The image structure const border points are not correct."<<endl;
			comparePoints( structureBorderPoints, structorBorderPointsRetConst );
			iReturn++;
		}
		
		set<cVectorPosition> structureNeighbourPointsRet =
			pImageStructure->getStructureNeighbourPoints();
		if ( structureNeighbourPoints == structureNeighbourPointsRet ){
			cout<<"The image structure neighbour points are correct."<<endl;
		}else{
			cerr<<"Error: The image structure neighbour points are not correct."<<endl;
			comparePoints( structureNeighbourPoints, structureNeighbourPointsRet );
			iReturn++;
		}
		
		const set<cVectorPosition> & structureNeighbourPointsRetConst =
			pImageStructureConst->getStructureNeighbourPointsConst();
		if ( structureNeighbourPoints == structureNeighbourPointsRetConst ){
			cout<<"The image structure const neighbour points are correct."<<endl;
		}else{
			cerr<<"Error: The image structure const neighbour points are not correct."<<endl;
			comparePoints( structureNeighbourPoints, structureNeighbourPointsRetConst );
			iReturn++;
		}
		
	}
	
	for ( unsigned int uiActualIteration = 0;
			uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
		cout<<endl;
		//call random change method
		const unsigned int uiChangeMethod = rand() % 19;
		switch ( uiChangeMethod ){
			case 0:{
				const unsigned int uiSetAntialised = rand() % 3;
				
				switch ( uiSetAntialised ){
					case 0:
						cout<<"pImageStructure->setAntialised( false );"<<endl;
						pImageStructure->setAntialised( false );
						bIsAntialised = false;
					break;
					case 1:
						cout<<"pImageStructure->setAntialised( true );"<<endl;
						pImageStructure->setAntialised( true );
						bIsAntialised = true;
					break;
					case 2:
						cout<<"pImageStructure->setAntialised();"<<endl;
						pImageStructure->setAntialised();
						bIsAntialised = true;
					break;
				};
			}break;
			case 1:
			case 2:
			case 3:{
				//generate points to set
				const unsigned int uiNumberOfPointsToSet = rand() % 64;
				cout<<"setting points (setPointsToSet):"<<endl;
				set<cVectorPosition> setPointsToSet;
				for ( unsigned int uiActualPoint = 0;
						uiActualPoint < uiNumberOfPointsToSet; uiActualPoint++ ){
					
					cVectorPosition vecGeneratedPoint = generateRandomPoint();
					vecGeneratedPoint.storeXml( cout );
				
					setPointsToSet.insert( vecGeneratedPoint );
				}
				
				switch ( uiChangeMethod ){
					case 1:
						cout<<"pImageStructure->setStructurePoints( setPointsToSet );"<<endl;
						pImageStructure->setStructurePoints( setPointsToSet );
						structurePoints = setPointsToSet;
					break;
					case 2:
						cout<<"pImageStructure->setStructureBorderPoints( setPointsToSet );"<<endl;
						pImageStructure->setStructureBorderPoints( setPointsToSet );
						structureBorderPoints = setPointsToSet;
					break;
					case 3:
						cout<<"pImageStructure->setStructureNeighbourPoints( setPointsToSet );"<<endl;
						pImageStructure->setStructureNeighbourPoints( setPointsToSet );
						structureNeighbourPoints = setPointsToSet;
					break;
				}
			}break;
			case 4:
			case 5:
			case 6:{
				//generate points to set
				const unsigned int uiNumberOfPointsToSet = rand() % 64;
				cout<<"adding points ( setPointsToAdd ):"<<endl;
				set<cVectorPosition> setPointsToAdd;
				for ( unsigned int uiActualPoint = 0;
						uiActualPoint < uiNumberOfPointsToSet; uiActualPoint++ ){
					
					cVectorPosition vecGeneratedPoint = generateRandomPoint();
					vecGeneratedPoint.storeXml( cout );
				
					setPointsToAdd.insert( vecGeneratedPoint );
				}
				
				switch ( uiChangeMethod ){
					case 4:
						cout<<"pImageStructure->addStructurePoints( setPointsToAdd );"<<endl;
						pImageStructure->addStructurePoints( setPointsToAdd );
						
						for ( set<cVectorPosition>::iterator
								itrPointToAdd = setPointsToAdd.begin();
								itrPointToAdd != setPointsToAdd.end(); itrPointToAdd++ ){
							
							structurePoints.insert( *itrPointToAdd );
						}
					break;
					case 5:
						cout<<"pImageStructure->addStructureBorderPoints( setPointsToAdd );"<<endl;
						pImageStructure->addStructureBorderPoints( setPointsToAdd );
						
						for ( set<cVectorPosition>::iterator
								itrPointToAdd = setPointsToAdd.begin();
								itrPointToAdd != setPointsToAdd.end(); itrPointToAdd++ ){
							
							structureBorderPoints.insert( *itrPointToAdd );
						}
					break;
					case 6:
						cout<<"pImageStructure->addStructureNeighbourPoints( setPointsToAdd );"<<endl;
						pImageStructure->addStructureNeighbourPoints( setPointsToAdd );
						
						for ( set<cVectorPosition>::iterator
								itrPointToAdd = setPointsToAdd.begin();
								itrPointToAdd != setPointsToAdd.end(); itrPointToAdd++ ){
							
							structureNeighbourPoints.insert( *itrPointToAdd );
						}
					break;
				}
			}break;
			case 7:
			case 8:
			case 9:{
				//generate points to set
				cout<<"adding point ( vecGeneratedPoint ):"<<endl;
				
				cVectorPosition vecGeneratedPoint = generateRandomPoint();
				vecGeneratedPoint.storeXml( cout );
				
				switch ( uiChangeMethod ){
					case 7:
						cout<<"pImageStructure->addStructurePoint( vecGeneratedPoint );"<<endl;
						pImageStructure->addStructurePoint( vecGeneratedPoint );
						
						structurePoints.insert( vecGeneratedPoint );
					break;
					case 8:
						cout<<"pImageStructure->addStructureBorderPoint( vecGeneratedPoint );"<<endl;
						pImageStructure->addStructureBorderPoint( vecGeneratedPoint );
						
						structureBorderPoints.insert( vecGeneratedPoint );
					break;
					case 9:
						cout<<"pImageStructure->addStructureNeighbourPoint( vecGeneratedPoint );"<<endl;
						pImageStructure->addStructureNeighbourPoint( vecGeneratedPoint );
						
						structureNeighbourPoints.insert( vecGeneratedPoint );
					break;
				}
			}break;
			case 10:{
				//choose points to delete
				set<cVectorPosition> setPointsToDelete;
				const unsigned int uiNumberOfPointsToDelete =
					rand() % ( structurePoints.size() + 4 );
				
				cout<<"deleting points ( setPointsToDelete ):"<<endl;
				
				for ( unsigned int uiActualPoint = 0;
						uiActualPoint < uiNumberOfPointsToDelete; uiActualPoint++ ){
					
					if ( ( ( rand() % 16 ) != 0 ) && ( ! structurePoints.empty() ) ){
						
						const unsigned int uiChoosenPointsToDelete =
							rand() % structurePoints.size();
						
						set<cVectorPosition>::iterator itrPointToDelete =
							structurePoints.begin();
						for( unsigned int uiActualPointToDelete = 0;
								uiActualPointToDelete < uiChoosenPointsToDelete;
								uiActualPointToDelete++, itrPointToDelete++ ){
							//nothing to do
						}
						itrPointToDelete->storeXml( cout );
						
						setPointsToDelete.insert( *itrPointToDelete );
						
						structurePoints.erase( itrPointToDelete );
						
					}else{//choose non existing point
						cVectorPosition vecGeneratedPoint = generateRandomPoint();
						cout<<"not existing:"<<endl;
						vecGeneratedPoint.storeXml( cout );
					
						setPointsToDelete.insert( vecGeneratedPoint );
						structurePoints.erase( vecGeneratedPoint );
					}
				}
				cout<<"pImageStructure->deleteStructurePoints( setPointsToDelete );"<<endl;
				pImageStructure->deleteStructurePoints( setPointsToDelete );
				
			}break;
			case 11:{
				//choose points to delete
				set<cVectorPosition> setPointsToDelete;
				const unsigned int uiNumberOfPointsToDelete =
					rand() % ( structureBorderPoints.size() + 4 );
				
				cout<<"deleting points ( setPointsToDelete ):"<<endl;
				
				for ( unsigned int uiActualPoint = 0;
						uiActualPoint < uiNumberOfPointsToDelete; uiActualPoint++ ){
					
					if ( ( ( rand() % 16 ) != 0 ) && ( ! structureBorderPoints.empty() ) ){
						
						const unsigned int uiChoosenPointsToDelete =
							rand() % structureBorderPoints.size();
						
						set<cVectorPosition>::iterator itrPointToDelete =
							structureBorderPoints.begin();
						for( unsigned int uiActualPointToDelete = 0;
								uiActualPointToDelete < uiChoosenPointsToDelete;
								uiActualPointToDelete++, itrPointToDelete++ ){
							//nothing to do
						}
						itrPointToDelete->storeXml( cout );
						
						setPointsToDelete.insert( *itrPointToDelete );
						
						structureBorderPoints.erase( itrPointToDelete );
						
					}else{//choose non existing point
						cVectorPosition vecGeneratedPoint = generateRandomPoint();
						cout<<"not existing:"<<endl;
						vecGeneratedPoint.storeXml( cout );
					
						setPointsToDelete.insert( vecGeneratedPoint );
						structureBorderPoints.erase( vecGeneratedPoint );
					}
				}
				cout<<"pImageStructure->deleteStructureBorderPoints( setPointsToDelete );"<<endl;
				pImageStructure->deleteStructureBorderPoints( setPointsToDelete );
				
			}break;
			case 12:{
				//choose points to delete
				set<cVectorPosition> setPointsToDelete;
				const unsigned int uiNumberOfPointsToDelete =
					rand() % ( structureNeighbourPoints.size() + 4 );
				
				cout<<"deleting points ( setPointsToDelete ):"<<endl;
				
				for ( unsigned int uiActualPoint = 0;
						uiActualPoint < uiNumberOfPointsToDelete; uiActualPoint++ ){
					
					if ( ( ( rand() % 16 ) != 0 ) && ( ! structureNeighbourPoints.empty() ) ){
						
						const unsigned int uiChoosenPointsToDelete =
							rand() % structureNeighbourPoints.size();
						
						set<cVectorPosition>::iterator itrPointToDelete =
							structureNeighbourPoints.begin();
						for( unsigned int uiActualPointToDelete = 0;
								uiActualPointToDelete < uiChoosenPointsToDelete;
								uiActualPointToDelete++, itrPointToDelete++ ){
							//nothing to do
						}
						itrPointToDelete->storeXml( cout );
						
						setPointsToDelete.insert( *itrPointToDelete );
						
						structureNeighbourPoints.erase( itrPointToDelete );
						
					}else{//choose non existing point
						cVectorPosition vecGeneratedPoint = generateRandomPoint();
						cout<<"not existing:"<<endl;
						vecGeneratedPoint.storeXml( cout );
					
						setPointsToDelete.insert( vecGeneratedPoint );
						structureNeighbourPoints.erase( vecGeneratedPoint );
					}
				}
				cout<<"pImageStructure->deleteStructureNeighbourPoints( setPointsToDelete );"<<endl;
				pImageStructure->deleteStructureNeighbourPoints( setPointsToDelete );
				
			}break;
			
			case 13:{
				//choose points to delete
				cVectorPosition vecPointToDelete;
				
				if ( ( ( rand() % 16 ) != 0 ) && ( ! structurePoints.empty() ) ){
					
					const unsigned int uiChoosenPointsToDelete =
						rand() % structurePoints.size();
					
					set<cVectorPosition>::iterator itrPointToDelete =
						structurePoints.begin();
					for( unsigned int uiActualPointToDelete = 0;
							uiActualPointToDelete < uiChoosenPointsToDelete;
							uiActualPointToDelete++, itrPointToDelete++ ){
						//nothing to do
					}
					cout<<"deleting point:"<<endl;
					itrPointToDelete->storeXml( cout );
					
					vecPointToDelete = *itrPointToDelete;
					
					structurePoints.erase( itrPointToDelete );
					
				}else{//choose non existing point
					vecPointToDelete = generateRandomPoint();
					cout<<"deleting not existing point:"<<endl;
					vecPointToDelete.storeXml( cout );
					
					structurePoints.erase( vecPointToDelete );
				}
				
				cout<<"pImageStructure->deleteStructurePoint( vecPointToDelete );"<<endl;
				pImageStructure->deleteStructurePoint( vecPointToDelete );
				
			}break;
			case 14:{
				//choose points to delete
				cVectorPosition vecPointToDelete;
				
				if ( ( ( rand() % 16 ) != 0 ) && ( ! structureBorderPoints.empty() ) ){
					
					const unsigned int uiChoosenPointsToDelete =
						rand() % structureBorderPoints.size();
					
					set<cVectorPosition>::iterator itrPointToDelete =
						structureBorderPoints.begin();
					for( unsigned int uiActualPointToDelete = 0;
							uiActualPointToDelete < uiChoosenPointsToDelete;
							uiActualPointToDelete++, itrPointToDelete++ ){
						//nothing to do
					}
					cout<<"deleting point:"<<endl;
					itrPointToDelete->storeXml( cout );
					
					vecPointToDelete = *itrPointToDelete;
					
					structureBorderPoints.erase( itrPointToDelete );
					
				}else{//choose non existing point
					vecPointToDelete = generateRandomPoint();
					cout<<"deleting not existing point:"<<endl;
					vecPointToDelete.storeXml( cout );
					
					structureBorderPoints.erase( vecPointToDelete );
				}
				
				cout<<"pImageStructure->deleteStructureBorderPoint( vecPointToDelete );"<<endl;
				pImageStructure->deleteStructureBorderPoint( vecPointToDelete );
				
			}break;
			case 15:{
				//choose points to delete
				cVectorPosition vecPointToDelete;
				
				if ( ( ( rand() % 16 ) != 0 ) && ( ! structureNeighbourPoints.empty() ) ){
					
					const unsigned int uiChoosenPointsToDelete =
						rand() % structureNeighbourPoints.size();
					
					set<cVectorPosition>::iterator itrPointToDelete =
						structureNeighbourPoints.begin();
					for( unsigned int uiActualPointToDelete = 0;
							uiActualPointToDelete < uiChoosenPointsToDelete;
							uiActualPointToDelete++, itrPointToDelete++ ){
						//nothing to do
					}
					cout<<"deleting points:"<<endl;
					itrPointToDelete->storeXml( cout );
					
					vecPointToDelete = *itrPointToDelete;
					
					structureNeighbourPoints.erase( vecPointToDelete );
					
				}else{//choose non existing point
					vecPointToDelete = generateRandomPoint();
					cout<<"deleting not existing points:"<<endl;
					vecPointToDelete.storeXml( cout );
					
					structureNeighbourPoints.erase( vecPointToDelete );
				}
				
				cout<<"pImageStructure->deleteStructureNeighbourPoint( vecPointToDelete );"<<endl;
				pImageStructure->deleteStructureNeighbourPoint( vecPointToDelete );
				
			}break;
			case 16:{//use copy constructor
				cout<<"c"<<getActualClassName()<<"( *pImageStructure );"<<endl;
				cImageStructure * pImageStructureCopy = copyImageStructure(
					pImageStructure );
				delete pImageStructure;
				
				pImageStructure = pImageStructureCopy;
				pImageStructureConst = pImageStructure;
			}break;
			case 17:{//use clone
				cout<<"pImageStructure->clone();"<<endl;
				cImageStructure * pImageStructureCopy =
					pImageStructure->clone();
				delete pImageStructure;
				
				pImageStructure = pImageStructureCopy;
				pImageStructureConst = pImageStructure;
			}break;
			case 18:{//test store and restore
				
				//create file name wher to store
				static unsigned int uiXmlFileIteration = 0;
				if ( ! bOverwriteFiles ){
					uiXmlFileIteration++;
				}
				char szFileNameBuffer[256];
				sprintf ( szFileNameBuffer, "%s%s%u%s", DIR_OUTPUT, "storeImageStructureXml", uiXmlFileIteration ,".xml" );
				//store image structure
				ofstream * pOfFile = new ofstream( szFileNameBuffer );
				
				bool bStoreSuccesfull = pImageStructure->storeXml( *pOfFile );
				delete pOfFile;
				
				if ( ! bStoreSuccesfull ){
					
					cerr<<"Error: Storing the image structure to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
					iReturn++;
					continue;
				}
				
				//restoring image structure
				ifstream inFile( szFileNameBuffer );
				
				intFib outStatus = 0;
				cImageStructure * pImageStructureRestored =
					cImageStructure::restoreXml( inFile , &outStatus );
				
				if ( outStatus == 0 ){
					cout<<"Restoring the image structur in the Xml format from the file "<<
						szFileNameBuffer <<" successfull. "<<endl;
				}else{
					cerr<<"Error: Restoring the image structur in the Xml format from the file "<<
						szFileNameBuffer <<" not successfull. (return status="<< outStatus <<")"<<endl;
					iReturn++;
					continue;
				}
				//switching to restored image structure
				delete pImageStructure;
				
				pImageStructure = pImageStructureRestored;
				pImageStructureConst = pImageStructure;
			}break;
			
		}
		
		
		//test the members of the class
		if ( getActualClassName() != pImageStructure->getName() ){
			cerr<<"Error: The image structure class name is \""<<
				pImageStructure->getName()<<"\", but should be \""<<
				getActualClassName()<<"\"."<<endl;
			iReturn++;
		}
		if ( pImageStructure->isAntialised() != bIsAntialised ){
			cerr<<"Error: The image structure "<<getActualClassName()<<
				" is "<<(pImageStructure->isAntialised()?"":"not ")<<
				"antialised, but should"<<(bIsAntialised?"":"n't")<<" be."<<endl;
			bIsAntialised = pImageStructure->isAntialised();
			iReturn++;
		}
		
		//check the area points
		set<cVectorPosition> structorPointsRet =
			pImageStructure->getStructurePoints();
		if ( structurePoints == structorPointsRet ){
			cout<<"The image structure points are correct."<<endl;
		}else{
			cerr<<"Error: The image structure points are not correct."<<endl;
			comparePoints( structurePoints, structorPointsRet );
			iReturn++;
		}
		
		const set<cVectorPosition> & structorPointsRetConst =
			pImageStructureConst->getStructurePointsConst();
		if ( structurePoints == structorPointsRetConst ){
			cout<<"The const image structure points are correct."<<endl;
		}else{
			cerr<<"Error: The const image structure points are not correct."<<endl;
			comparePoints( structurePoints, structorPointsRetConst );
			iReturn++;
		}
		//check the area borders points
		set<cVectorPosition> structorBorderPointsRet =
			pImageStructure->getStructureBorderPoints();
		if ( structureBorderPoints == structorBorderPointsRet ){
			cout<<"The image structure border points are correct."<<endl;
		}else{
			cerr<<"Error: The image structure border points are not correct."<<endl;
			comparePoints( structureBorderPoints, structorBorderPointsRet );
			iReturn++;
		}
		
		const set<cVectorPosition> & structorBorderPointsRetConst =
			pImageStructureConst->getStructureBorderPointsConst();
		if ( structureBorderPoints == structorBorderPointsRetConst ){
			cout<<"The image structure const border points are correct."<<endl;
		}else{
			cerr<<"Error: The image structure const border points are not correct."<<endl;
			comparePoints( structureBorderPoints, structorBorderPointsRetConst );
			iReturn++;
		}
		//check the area neighbour points
		set<cVectorPosition> structureNeighbourPointsRet =
			pImageStructure->getStructureNeighbourPoints();
		if ( structureNeighbourPoints == structureNeighbourPointsRet ){
			cout<<"The image structure neighbour points are correct."<<endl;
		}else{
			cerr<<"Error: The image structure neighbour points are not correct."<<endl;
			comparePoints( structureNeighbourPoints, structureNeighbourPointsRet );
			iReturn++;
		}
		
		const set<cVectorPosition> & structureNeighbourPointsRetConst =
			pImageStructureConst->getStructureNeighbourPointsConst();
		if ( structureNeighbourPoints == structureNeighbourPointsRetConst ){
			cout<<"The image structure const neighbour points are correct."<<endl;
		}else{
			cerr<<"Error: The image structure const neighbour points are not correct."<<endl;
			comparePoints( structureNeighbourPoints, structureNeighbourPointsRetConst );
			iReturn++;
		}
		
	}//end iterate random test
	delete pImageStructure;
	
	return iReturn;
}



/**
 * This function tests the iConvertImageStructureToFib::convertToFib()
 * methods.
 *
 * @param ulTestphase a reference to the number for the test phase
 * @return the number of errors occured in the test
 */
int testConvertToFib( unsigned long &ulTestphase ){
	
	list< cTestDataFiles > setErrorsInTestCase;
	int iReturn = 0;//return value of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for the tImageStructureConvertToFib::convertToTiles() method"<<endl;
	cout<<      "========================================================================="<<endl;
	
	//load the testfolder list
	string szFilePath = string( pDirTestObjects ) + getActualClassTestCaseFile();
	
	list< cTestDataFiles > liTestFolders = loadTestFileList( szFilePath );
	if ( liTestFolders.empty() ){
		cerr<<"Error: No testfolders to test."<<endl;
		iReturn++;
		return iReturn;
	}
	
	//for each testfolder
	for ( list< cTestDataFiles >::iterator itrTestCase = liTestFolders.begin();
			itrTestCase != liTestFolders.end(); itrTestCase++ ){
		
		const string & szActualImageStructureData  = itrTestCase->szImageStructureData;
		const string & szActualSearchData = itrTestCase->szSearchData;
		const string & szActualAreaData = itrTestCase->szAreaData;
		ulTestphase++;
		cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing converting the image structure of \""<<
			szActualImageStructureData <<"\" with the search data of \""<<szActualSearchData<<
			"\" and the area data of \""<<szActualAreaData<<"\""<<endl;
		
		unsigned int iErrorsInLastTestCase =
			testConvertForObject( szActualImageStructureData,
				szActualSearchData, szActualAreaData );
		
		for ( unsigned int uiActualIteration = 0;
				uiActualIteration < ( 1 + MAX_ITERATION % 32 ); uiActualIteration++ ){
			
			const double maxValue = 1024.0 + (double(rand() % 65536)) *
				(double(rand() % 65536));
			
			iErrorsInLastTestCase +=
				testConvertForObject( szActualImageStructureData,
					szActualSearchData, szActualAreaData, true, maxValue );
		}
		/*TODO for error parameters testConvertForObject() not implemented
		for ( unsigned int uiActualIteration = 0;
				uiActualIteration < MAX_ITERATION; uiActualIteration++ ){
			
			const double maxValue = 1024.0 + (double(rand() % 65536)) *
				(double(rand() % 65536));
			const double maxErrorPerValue =
				(double(rand() % 255)) * (double(rand() % 255));
			
			iErrorsInLastTestCase +=
				testConvertForObject( szActualImageStructureData,
					szActualSearchData, szActualAreaData,
					true, maxValue, maxErrorPerValue );
		}
		*/
		iReturn += iErrorsInLastTestCase;
		if ( 0 < iErrorsInLastTestCase ){
			//add area test file to error in test case list
			setErrorsInTestCase.push_back( *itrTestCase );
		}
		
	}
	
	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test part successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test part failed: "<<iReturn<<" errors occoured in "<<setErrorsInTestCase.size()<<" test cases"<<endl;
		
		cerr<<"Errors wher in test files: ";
		for ( list< cTestDataFiles >::const_iterator
				itrTestCase = setErrorsInTestCase.begin();
				itrTestCase != setErrorsInTestCase.end(); itrTestCase++ ){
			
			cout<<"\""<<(itrTestCase->szImageStructureData)<<"\",\""<<
				(itrTestCase->szSearchData)<<"\",\""<<
				(itrTestCase->szAreaData)<<"\" ;"<<endl;
		}
		cout<<endl;
	}
	return iReturn;
}


/**
 * This function checks the values of the given vector.
 *
 * @param pFibVector the vector to check
 * @param maxValue the maximal value the vector should have
 * @return the number of errors occured in the test
 */
unsigned int checkVectorValues( const cFibVector * pFibVector,
		const double maxValue ){
	
	int iReturn = 0;//return value of the test; the number of occured Errors
	
	const unsignedIntFib uiNumberVectorElements =
		pFibVector->getNumberOfElements();
	for ( unsigned int uiNumberActualValue = 0;
			uiNumberActualValue <= uiNumberVectorElements;
			uiNumberActualValue++ ){
		
		if ( ( ! pFibVector->isVariable( uiNumberActualValue ) ) &&
				( maxValue < abs( pFibVector->getValue( uiNumberActualValue ) ) ) ){
			cerr<<"Error: The "<<uiNumberActualValue<<
				" absolute value of the vector is bigger as the maxValue (of "<<
					maxValue<<") , it is "<<
					pFibVector->getValue( uiNumberActualValue )<<endl;
			iReturn++;
		}
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
 * This function test the cImageStructureConvertToTiles::convertToFib()
 * method for one test case.
 *
 * @param szActualImageStructureData the file wher the to convert image
 * 	structure data is stored
 * @param szActualSearchData the file wher the search data is stored
 * @param bGiveParameters if true the convertToFib() is given the
 * 	maxValue, ulMaxErrorPerPoint and maxError parameters
 * @param maxValue the maxValue parameter for the convertToFib() method
 * @param ulMaxErrorPerPoint the ulMaxErrorPerPoint parameter for the
 * 	convertToFib() method
 * @return the number of errors occured in the test
 */
unsigned int testConvertForObject( const string szActualImageStructureData,
		const string szActualSearchData, const string szActualAreaData, const bool bGiveParameters,
		double maxValue, const long ulMaxErrorPerPoint ){
	
	
	int iReturn = 0;//return value of the test; the number of occured Errors
	
	cout<<endl<<"TEST : convert image structure to Fib object (image structure of \""<<
		szActualImageStructureData <<
		"\" with the search data of \""<<szActualSearchData<<
		"\" and the area data of \""<<szActualAreaData<<
		"\"; parameter are "<<(bGiveParameters?"":"not ")<<"given; "
		"maxValue="<<maxValue<<"; ulMaxErrorPerPoint="<<ulMaxErrorPerPoint<<")"<<endl;

	//evalue the files in the testfolder
	const string szActualImageStructureDataPath = string( pDirTestObjects ) +
		szActualImageStructureData;
	const string szActualSearchDataPath = string( pDirTestObjects ) +
		szActualSearchData;
	const string szActualAreaDataPath = string( pDirTestObjects ) +
		szActualAreaData;
	
	//load the the area to convert
	list< pair< cVectorPosition, list< cVectorProperty > > >
		liAreaPointsLoaded = loadPositionPropertyData( szActualAreaDataPath.c_str() );
	
	//load the the search data
	set< cVectorPosition > setSearchDataLoaded;
	//max points
	longFib lMaxX = -1;
	longFib lMaxY = -1;
	
	if ( bGiveParameters ){
		setSearchDataLoaded = loadPositionData( szActualSearchDataPath.c_str() );
		
		//dertermine image higth and width
		//evalue max points
		for ( set<cVectorPosition>::const_iterator
				itrActualPoint = setSearchDataLoaded.begin();
				itrActualPoint != setSearchDataLoaded.end(); itrActualPoint++ ){
			
			lMaxX = fib::max( lMaxX,
				roundToLongFib( itrActualPoint->getValue( 1 ) ) );
			lMaxY = fib::max( lMaxY,
				roundToLongFib( itrActualPoint->getValue( 2 ) ) );
		}
	}
	
	cImageSearchData imageSearchData( lMaxX + 1 , lMaxY + 1 );
	if ( bGiveParameters ){
		imageSearchData.registerOverlapped( setSearchDataLoaded );
	}
	
	//load to convert image structure
	ifstream inFile( szActualImageStructureDataPath.c_str() );
	
	intFib outStatus = 0;
	cImageStructure * pImageStructure =
		cImageStructure::restoreXml( inFile , &outStatus );
	
	if ( outStatus == 0 ){
		cout<<"Restoring the image structur in the Xml format from the file "<<
			szActualImageStructureData <<" successfull."<<endl;
	}else{
		cerr<<"Error: Restoring the image structur in the Xml format from the file "<<
			szActualImageStructureData <<" not successfull. (return status="<< outStatus <<")"<<endl;
		iReturn++;
		return iReturn;
	}
	
	//evalue maximal value of positions vectors dMaxPositionValue
	double dMaxPositionValue = 0;
	const set<cVectorPosition> & setPointsOfStructure =
		pImageStructure->getStructurePointsConst();
	
	for ( set<cVectorPosition>::const_iterator
			itrActualPoint = setPointsOfStructure.begin();
			itrActualPoint != setPointsOfStructure.end(); itrActualPoint++ ){
		
		dMaxPositionValue = std::max( dMaxPositionValue,
			std::abs( itrActualPoint->getValue( 1 ) ) );
		dMaxPositionValue = std::max( dMaxPositionValue,
			std::abs( itrActualPoint->getValue( 2 ) ) );
	}
	
	
	cRoot * pConvertedObject = NULL;
	if ( bGiveParameters ){
		cout<<endl<<"pImageStructure->convertToFib( &imageSearchData, maxValue="<<
			maxValue<<" , ulMaxErrorPerPoint="<<ulMaxErrorPerPoint<<" );"<<endl;
		pConvertedObject = pImageStructure->convertToFib(
				&imageSearchData, maxValue, ulMaxErrorPerPoint );
	}else{//no give parameters
		cout<<endl<<"pImageStructure->convertToFib();"<<endl;
		pConvertedObject = pImageStructure->convertToFib();
	}
	if ( pConvertedObject == NULL ){
		cerr<<"Error: Image structure could not be converted."<<endl;
		iReturn++;
		return iReturn;
	}
	cout<<"created object:"<<endl;
	pConvertedObject->storeXml( cout );
	cout<<endl<<endl;
	
	//evalue converted Fib object
	cEvaluePositionList evaluedPositionData;
	
	const bool bObjectEvalued = pConvertedObject->evalueObjectSimple(
		evaluedPositionData );
	
	if ( ! bObjectEvalued ){
		cerr<<"Error: Object could not be evalued:"<<endl;
		iReturn++;
		pConvertedObject->storeXml( cerr );
	}
	
	if ( bGiveParameters ){
		//check the parameters of the generated objects
		int iWrongValues = 0;
		
		const double dMaxVectorValue = std::max( maxValue, dMaxPositionValue );
		
		//check parameters of external objects
		for ( cExtObject * pActualExtObject = ((cExtObject*)
					pConvertedObject->getNextFibElement( 'o' ) );
				pActualExtObject != NULL;
				pActualExtObject = ((cExtObject*)
					pActualExtObject->getNextFibElement( 'o' ) ) ){
			
			//check max values
			cVectorExtObject * pVecExtObject = pActualExtObject->getInputVector();
			
			iWrongValues += checkVectorValues( pVecExtObject, dMaxVectorValue );
			
		}//end for all evalued external objects
		//check parameters of points objects
		for ( cPoint * pActualPoint = ((cPoint*)
					pConvertedObject->getNextFibElement( 'p' ) );
				pActualPoint != NULL;
				pActualPoint = ((cPoint*)
					pActualPoint->getNextFibElement( 'p' ) ) ){
			
			//check max values
			cFibVector * pVecExtObject = pActualPoint->getPosition();
			
			iWrongValues += checkVectorValues( pVecExtObject, dMaxVectorValue );
			
		}//end for all evalued points objects
		//check parameters of set elements
		for ( cFibSet * pActualSetElement = ((cFibSet*)
					pConvertedObject->getNextFibElement( 'v' ) );
				pActualSetElement != NULL;
				pActualSetElement = ((cFibSet*)
					pActualSetElement->getNextFibElement( 'v' ) ) ){
			
			const vector< cVectorFibSet > & setVectors =
				pActualSetElement->getVectors();
			
			//check max values
			for (  vector< cVectorFibSet >::const_iterator
					itrVector = setVectors.begin();
					itrVector != setVectors.end(); itrVector++ ){
				
				iWrongValues += checkVectorValues( &(*itrVector), dMaxVectorValue );
			}
		}//end for all evalued set elements
		//check parameters of matrix elements
		for ( cFibMatrix * pActualMatrixElement = ((cFibMatrix*)
					pConvertedObject->getNextFibElement( 'm' ) );
				pActualMatrixElement != NULL;
				pActualMatrixElement = ((cFibMatrix*)
					pActualMatrixElement->getNextFibElement( 'm' ) ) ){
			
			const vector< cVectorFibMatrix > & setVectors =
				pActualMatrixElement->getVectors();
			
			//check max values
			for (  vector< cVectorFibMatrix >::const_iterator
					itrVector = setVectors.begin();
					itrVector != setVectors.end(); itrVector++ ){
				
				iWrongValues += checkVectorValues( &(*itrVector), dMaxVectorValue );
			}
		}//end for all evalued matrix objects
		//check parameters of area objects
		for ( cArea * pActualArea = ((cArea*)
					pConvertedObject->getNextFibElement( 'a' ) );
				pActualArea != NULL;
				pActualArea = ((cArea*)
					pActualArea->getNextFibElement( 'a' ) ) ){
			
			//check max values
			const unsignedIntFib uiNumberOfSubareas =
				pActualArea->getNumberOfSubareas();
			
			for ( unsignedIntFib uiActualArea = 1;
					uiActualArea <= uiNumberOfSubareas; uiActualArea++ ){
				
				cFibVector * pVecSubarea = pActualArea->getSubarea( uiActualArea );
				
				iWrongValues += checkVectorValues( pVecSubarea, dMaxVectorValue );
			}
		}//end for all evalued area objects
		
		//check parameters of subfunctions
		list< doubleFib > liValuesInValueSubfunctions =
			algorithms::nAnalyse::nFibObject::nBits::evalueFunctionValues(
				pConvertedObject );
		for ( list< doubleFib >::const_iterator
				itrValue = liValuesInValueSubfunctions.begin();
				itrValue != liValuesInValueSubfunctions.end(); itrValue++ ){
			
			if ( dMaxVectorValue < abs( *itrValue ) ){
				cerr<<"Error: A subfunction value is bigger as the maxValue (of "<<
						maxValue<<") , it is "<<(*itrValue)<<endl;
				iReturn++;
			}
			
		}//end for all evalued functions objects
		
		if ( iWrongValues != 0 ){
			//some values wher wrong
			cerr<<endl<<"The generated Fib object wher the to big values wher found:"<<endl;
			pConvertedObject->storeXml( cerr );
			iReturn += iWrongValues;
		}
		
	}

	/* check if all evalued points are in loaded area liAreaPointsLoaded
	or overlapt by the overlapt points in the search area setSearchDataLoaded*/
	//the area copy is for checking if all points wher removed
	list< pair< cVectorPosition, list< cVectorProperty > > >
		liAreaPointsLoadedCopy = liAreaPointsLoaded;
	
	const bool bIsAntialised = pImageStructure->isAntialised();
	//the data in the structure are just neede if antialised (to check neighbours)
	//max points in structure
	longFib lMaxStructureX = -1;
	longFib lMaxStructureY = -1;
	if ( bIsAntialised ){
		const set<cVectorPosition> & setImageStructurPoints =
			pImageStructure->getStructurePointsConst();
			
		for ( set<cVectorPosition>::const_iterator
				itrActualPoint = setImageStructurPoints.begin();
				itrActualPoint != setImageStructurPoints.end(); itrActualPoint++ ){
			
			lMaxStructureX = fib::max( lMaxStructureX,
				roundToLongFib( itrActualPoint->getValue( 1 ) ) );
			lMaxStructureY = fib::max( lMaxStructureY,
				roundToLongFib( itrActualPoint->getValue( 2 ) ) );
		}
		
	}
	cImageSearchData setDataInStructure( lMaxStructureX + 1, lMaxStructureY + 1 );
	if ( bIsAntialised ){
		setDataInStructure.registerFound( pImageStructure );
	}
	
	for ( list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
			itrActualPoint = evaluedPositionData.liEvaluedPositionData.begin();
			itrActualPoint != evaluedPositionData.liEvaluedPositionData.end();
			itrActualPoint++ ){
		
		//find the evalued point in the loaded area points
		list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
			itrLoadedPoint = liAreaPointsLoaded.begin();
		for ( ; itrLoadedPoint != liAreaPointsLoaded.end(); itrLoadedPoint++ ){
			
			if ( pointsEqual( itrLoadedPoint->first, itrActualPoint->first ) ){
				//point evalued point found in the loaded area points
				break;
			}//else check next loaded point
		}
		
		if ( itrLoadedPoint != liAreaPointsLoaded.end() ){
			//point found in area ->  remove it from copy
			list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
				itrLoadedPointCopy = liAreaPointsLoadedCopy.begin();
			for ( ; itrLoadedPointCopy != liAreaPointsLoadedCopy.end();
					itrLoadedPointCopy++ ){
				
				if ( pointsEqual( itrLoadedPointCopy->first, itrActualPoint->first ) ){
					//point evalued point found in the loaded area points
					break;
				}//else check next loaded point
			}
			if ( itrLoadedPointCopy != liAreaPointsLoadedCopy.end() ){
				liAreaPointsLoadedCopy.erase( itrLoadedPointCopy );
			}
			//check properties of the point
			
			//compare the properties
			list< cVectorProperty >::const_iterator
				itrProperty1 = itrActualPoint->second.begin();
			list< cVectorProperty >::const_iterator
				itrProperty2 = itrLoadedPoint->second.begin();
			/* normaly just one point should exists, if more exists
			 * (transparency) the order is important*/
			unsigned int uiNumberOfProperty = 1;
			for ( ; (itrProperty1 != itrActualPoint->second.end() ) &&
					(itrProperty2 != itrLoadedPoint->second.end() );
					itrProperty1++, itrProperty2++, uiNumberOfProperty++ ){
				
				bool bErrorOccured = false;
			
				if ( itrProperty1->getPropertyType() == cTypeProperty::TRANSPARENCY ){
					/*the transparency property for the antialising do not have
					 to match perfect*/
					if ( itrProperty2->getPropertyType() != cTypeProperty::TRANSPARENCY ){
						//error not both transparency properties
						bErrorOccured = true;
					}else if ( ( itrProperty1->getNumberOfElements() != 1 ) ||
							( itrProperty2->getNumberOfElements() != 1 ) ){
						//error not correct transparency properties
						bErrorOccured = true;
					}else if ( itrProperty1->getValue( 1 ) <
								( ( itrProperty2->getValue( 1 ) - 0.2 ) ) &&
							( ( itrProperty2->getValue( 1 ) + 0.2 ) <
								itrProperty1->getValue( 1 ) ) ){
						/* if ( valueCorrect - 0.2 =< valueEvalued =< valueCorrect + 0.2 ) ->
						 * a 0.2 = 20 per cent margin of error for evalued value allowed;
						 * error not "equal" transparency properties*/
						bErrorOccured = true;
					}//else no error
					
				}else if ( ! ( (*itrProperty1) == (*itrProperty2) ) ){
					bErrorOccured = true;
				}
				
				if ( bErrorOccured ){
					cerr<<"Error: The "<< uiNumberOfProperty <<"'th property isn't equal."<<endl;
					cerr<<"Point for property: "<<endl;
					itrActualPoint->first.storeXml( cerr );
					cerr<<"   correct property:"<<endl;
					itrProperty2->storeXml( cerr );
					cerr<<"   evalued property:"<<endl;
					itrProperty1->storeXml( cerr );
					
					iReturn++;
				}
			}
			
		}else{//point not found in area -> check if it is overwritten
			const longFib lX = roundToLongFib(
				itrActualPoint->first.getValue( 1 ) );
			const longFib lY = roundToLongFib(
				itrActualPoint->first.getValue( 2 ) );
			
			if ( ! imageSearchData.isOverlapped( lX, lY ) ){
				
				if ( ! bIsAntialised ){
				
					if ( ( ulMaxErrorPerPoint == 0.0 )  ){
						cerr<<"Error: Point not in loaded area and not overwritten:"<<endl;
						itrActualPoint->first.storeXml( cerr );
						iReturn++;
					}//else TODO change for given parameters
				}else{
					//if antialised -> points could be included for antialising
					//check if a neighbour point is in structure
					double dTrancparency = 0.0;//default full opacity
					for ( list< cVectorProperty >::const_iterator
							itrActualProperty = itrActualPoint->second.begin();
							itrActualProperty != itrActualPoint->second.end();
							itrActualProperty++ ){
						
						if ( itrActualProperty->getPropertyType() == cTypeProperty::TRANSPARENCY ){
							//remember tranparency value
							dTrancparency = itrActualProperty->getValue( 1 );
							break;
						}
					}
					if ( dTrancparency < 0.9 ){
						//TODO needed?
						//if ( 0.5 < dTrancparency ){
							//point is transparent
							const set<cVectorPosition> setNeigbourPointsInStructure =
								setDataInStructure.getFoundNeighbours( itrActualPoint->first );
							
							if ( setNeigbourPointsInStructure.empty() ){
								cerr<<"Error: Point not in loaded area, not overwritten and no neighbour in area (transparency="<<dTrancparency<<" )"<<endl;
								itrActualPoint->first.storeXml( cerr );
								iReturn++;
							}
						/*}else{
							cerr<<"Error: Point not in loaded area, not overwritten and transparency ("<<dTrancparency<<") lower 0.5"<<endl;
							itrActualPoint->first.storeXml( cerr );
							iReturn++;
						}*/
					}//else ignore points with 0.95 < dTrancparency (you don't see them)
				}
			}
			//ignore property because they are overwritten
		}
			
			//check error parameters
			
			//TODO how to evalue error?
			
			//not to much outside overlapt area
			
			
		
		//TODO check not to much missing points in a line
		
	}//end for all evalued points
	
	if ( bIsAntialised ){
		/* if antialised remove points in liAreaPointsLoadedCopy wich have a
		 * neighbour in the generated area*/
		//for easy neighbour finding, generate search structure for converted data
		longFib lMaxConvertedStructureX = lMaxX;
		longFib lMaxConvertedStructureY = lMaxY;
		
		for ( list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
				itrActualPoint = evaluedPositionData.liEvaluedPositionData.begin();
				itrActualPoint != evaluedPositionData.liEvaluedPositionData.end();
				itrActualPoint++ ){
			
			lMaxConvertedStructureX = fib::max( lMaxConvertedStructureX,
				roundToLongFib( itrActualPoint->first.getValue( 1 ) ) );
			lMaxConvertedStructureY = fib::max( lMaxConvertedStructureY,
				roundToLongFib( itrActualPoint->first.getValue( 2 ) ) );
		}
		cImageSearchData setDataInConvertedStructure(
			lMaxConvertedStructureX + 1, lMaxConvertedStructureY + 1 );
		
		for ( list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
				itrActualPoint = evaluedPositionData.liEvaluedPositionData.begin();
				itrActualPoint != evaluedPositionData.liEvaluedPositionData.end();
				itrActualPoint++ ){
			
			setDataInConvertedStructure.registerFound( itrActualPoint->first );
		}
		
		for ( list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
				itrActualPoint = liAreaPointsLoadedCopy.begin();
				itrActualPoint != liAreaPointsLoadedCopy.end(); ){
			
			const set<cVectorPosition> setNeigbourPointsInStructure =
				setDataInConvertedStructure.getFoundNeighbours(
					itrActualPoint->first );
			
			if ( setNeigbourPointsInStructure.empty() ){
				//point has no neighbour in converted area -> check next
				itrActualPoint++;
			}else{
				//point has neighbour in converted area -> remove it
				itrActualPoint = liAreaPointsLoadedCopy.erase( itrActualPoint );
			}
		}//for all not found points
	}//end if antialised remove points in liAreaPointsLoadedCopy
	
	if ( ulMaxErrorPerPoint == 0.0 ){
		if ( ! liAreaPointsLoadedCopy.empty() ){
			
			cerr<<endl<<"Error: Some points in loaded area ("<<szActualAreaDataPath<<
				") wher not in converted area:"<<endl;
			for ( list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
					itrActualPoint = liAreaPointsLoadedCopy.begin();
					itrActualPoint != liAreaPointsLoadedCopy.end();
					itrActualPoint++ ){
				
				itrActualPoint->first.storeXml( cerr );
			}
			cerr<<endl;
			cerr<<endl<<"Points evalued:"<<endl;
			for ( list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
					itrActualPoint = evaluedPositionData.liEvaluedPositionData.begin();
					itrActualPoint != evaluedPositionData.liEvaluedPositionData.end();
					itrActualPoint++ ){
				
				itrActualPoint->first.storeXml( cerr );
			}
			cerr<<endl;
			iReturn++;
		}
	}
	
	pConvertedObject->deleteObject();
	delete pImageStructure;
	
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
list< cTestDataFiles > loadTestFileList( const string szFilePath ){

	list< cTestDataFiles > liFiles;
	
	ifstream ifStream( szFilePath.c_str() );
	
	if ( ! ifStream.good() ){
		
		cerr<<"Error: Couldn't read the folder list "<< szFilePath <<endl;
		return liFiles;
	}
	char szBuffer[ 1024 ];
	char cNull = ((char)(0x00));
	
	while( ifStream.good() ){
		
		cTestDataFiles testDataFiles;
		
		ifStream.getline( szBuffer, 1024 );
		
		char * szSemicolon = strchr( szBuffer, ';' );
		if ( szSemicolon != 0 ){
			(*szSemicolon) = (char)(0x00);//terminate area file string
			szSemicolon++;//set to search data file string
		}else{
			//no semicolon found
			szSemicolon = &cNull;
		}
		testDataFiles.szImageStructureData = string( szBuffer );
		
		if ( szSemicolon != &cNull ){
			//semicolon found
			char * szSemicolon2 = strchr( szSemicolon, ';' );
			if ( szSemicolon2 != 0 ){
				(*szSemicolon2) = (char)(0x00);//terminate area file string
				szSemicolon2++;//set to search data file string
			}else{
				//no semicolon found
				szSemicolon2 = &cNull;
			}
			testDataFiles.szAreaData = string( szSemicolon2 );
		}
		testDataFiles.szSearchData = string( szSemicolon );
		
		if ( testDataFiles.szImageStructureData != "" ){
			liFiles.push_back( testDataFiles );
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
	
	/*every liLoadedData element is created by loading a point vector and
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



/**
 * This function loads the data of positions with ther properties from
 * the given file.
 *
 * @param szFilename the path of the file, from which the positions data
 * 	should be loaded from
 * @return the loaded positions data with ther properties
 */
list< pair< cVectorPosition, list< cVectorProperty > > >
		loadPositionPropertyData( const char * szFilename ){
	
	/*every liLoadedData element is created by loading a point vector and
	then property vectors till the next point vector*/
	list< pair< cVectorPosition, list< cVectorProperty > > > liLoadedData;
	
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
		return liLoadedData;
	}
	
	TiXmlHandle xmlHandleData( pXmlElementData );
	TiXmlElement * pXmlElement = xmlHandleData.FirstChild().Element();
	
	//no variables defined
	list<cFibVariable*> liDefinedVariables;
	intFib outStatus = 0;
	
	for( ; pXmlElement; pXmlElement = pXmlElement->NextSiblingElement() ){
		//load the vector lists for liLoadedData
		string szElementName = pXmlElement->Value();

		if ( szElementName != "vector" ){
			cerr<<"Error: The name of the data list element is "<< szElementName <<" and not \"vector\"."<<endl;
		}
		const char * szVectorXmlType = pXmlElement->Attribute( "type" );
		
		if ( szVectorXmlType == NULL ){
			cerr<<"Error: The vector has no type."<<endl;
		}else if ( string( szVectorXmlType ) == "position" ) {
		
			liLoadedData.push_back( make_pair(
				cVectorPosition( pXmlElement, outStatus, liDefinedVariables ),
				list< cVectorProperty >() ) );
		}else{//property vector
			
			liLoadedData.back().second.push_back(
				cVectorProperty( pXmlElement, outStatus, liDefinedVariables ) );
		}
		if ( outStatus != 0 ){
			cerr<<"Error: While loading a "<< szVectorXmlType <<
				" vector. (outStatus="<< outStatus <<" )"<<endl;
			outStatus = 0;
		}
	}
	return liLoadedData;
}




/** @def PATH_SEPERATOR the operatingsystem dependent seperator in filepath */
#ifdef linux
	#define PATH_SEPERATOR      '/'
	#define NOT_PATH_SEPERATOR  '\\'
#else//dos/windows
	#define PATH_SEPERATOR      '\\'
	#define NOT_PATH_SEPERATOR  '/'
#endif


/**
 * checks if a file for the given path exists and can be opened
 * @param path a string for the path to be cheked
 * @return true if the path exists, else false
 */
bool checkPath( char* path ){

	if  ( path==NULL ){
		return false;
	}
	ifstream test( path );
	if( test ){
		test.close();
		return true;
	}
	return false;
}


/**
 * if the path folders are not existing, this function creats them
 * @param path the string of the path that should be existing
 */
void createPath( const char* path ){

	unsigned long maxC=0,count=0,count2=0;//maxC= maximal chars to read; to avoid infinity loops
	if  ( path==NULL ){
		return;
	}
	//begin with the first folder, check if the folder exists and if not creat it
	char folder[1000],mkDir[1020];
	for ( ; (maxC<100000) && (path[count]!=0) ; maxC++ ){
		//check next folder
		for ( ; (maxC<100000) && (path[count]!=0) ; maxC++ ){
			//read folder from path
			if ( path[count]==PATH_SEPERATOR){
			
				folder[count2]=PATH_SEPERATOR;
				count++;
				count2++;
				break;
			}else{
				folder[count2]=path[count];
				count++;
				count2++;
			}
		}
		folder[count2]=0;
		if ( (count2!=0) &&
				!( (count2==1) && (folder[0]==PATH_SEPERATOR) ) &&
				!( (count2==2) && (folder[0]=='.') && (folder[1]==PATH_SEPERATOR) )
				&& !(checkPath(folder)) 
				){
			// if in folder stands a valid path
			sprintf( mkDir, "mkdir %s ", folder );
			system( mkDir );
		}
		if ( path[count]==0 ){
			return;
		}
	}
}












