/**
 * @file tEvalueObject
 * file name: tEvalueObject.cpp
 * @author Betti Oesterholz
 * @date 07.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for testing evaluating  Fib objects.
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
 * This test is for testing evaluating  Fib objects.
 * The Fib-testobjects are loaded from the files in the subdirectories of the
 * folde pDirTestObjects. Ther are also stored the resultdata which evalue
 * calls should produce. With this data the evaluecalls are check on the
 * restoed Fib object.
 * When loading partobjects with variables, ther variable storevalue
 * should be ther number (counting form 1) in the list of all variables in
 * the original Fib object counted in the order which
 * getDefinedVariables() returns.
 *
 * Every testcase is stored in a seperate underfolder in the DIR_TESTDATA
 * folder. (The standardfolder for DIR_TESTDATA is "testObjects/".)
 * In the "testWithEvalue.txt" in the DIR_TESTDATA the testcasefolders are
 * listed. Every folder stands in "testWithEvalue.txt" in a seperate line.
 *
 * The data, in the testfiles in the testcasefolder [TESTCASE], is stored
 * in the Fib-xml  format. Files with the testdata (or rather all files
 * except the [TESTCASE].xml file) have as the root xml -element, an
 * xml -element with the name "data". In the "data" xml -element contains
 * the list with Fib-elements, which are evalued. Every listelement is an
 * evalued Fib-element (an positionsvector or an Fib object) followed
 * by it's properties as propertyvectors.
 * Testfile in a testcasefolder [TESTCASE]:
 * 	- [TESTCASE].xml : file with the Fib object which should be evalued
 * 	  (e.g. "test.xml")
 * Optional testfiles (with the testdata) in a testcasefolder [TESTCASE]:
 * 	- [TESTCASE]EvP.xml : file with the evalued data of the whool Fib object
 * 	  (e.g. "testEvP.xml")
 * 	- [TESTCASE]EvP_Po[NUMBER].xml : file with the evalued data of the
 * 	  [NUMBER]'th underobject of the Fib object
 * 	  (e.g. "testEvP_Po1.xml" and "testEvP_Po3.xml")
 * 	- [TESTCASE]EvE[TYPS].xml : file with the evalued data of the whool
 * 	  Fib object for the given [TYPS], the typs are given as a list of
 * 	  the characters for the Fib-elementtyps (@see cFibElement::getType())
 * 	  (e.g. "testEvEy.xml" and "testEvEyl.xml" (="testEvEly.xml") )
 * 	- [TESTCASE]EvE[TYPS]_Po[NUMBER].xml : file with the evalued data of
 * 	  the [NUMBER]'th underobject of the Fib object for the given [TYPS],
 * 	  the typs are given as a list of the characters for the
 * 	  Fib-elementtyps (@see cFibElement::getType())
 * 	  (e.g. "testEvEy_Po1.xml" and "testEvEl_Po3.xml")
 *
 *
 * What's tested of class cFibElement -class:
 * 	- bool evalueObjectSimple( iEvaluePosition & evaluePosition, const unsignedIntFib objectPoint = 0 ) const;
 * 	- bool evalueObject( iEvaluePosition & evaluePosition, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties ) const;
 * 	- bool evalueObjectSimple( bool evalueElement( iEvalueFibElement & evalueFibElement, const unsignedIntFib objectPoint = 0, const list<char> liCFibElementTyps = list<char>() );
 * 	- bool evalueObject( iEvalueFibElement & evalueFibElement, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties, const list<char> & liCFibElementTyps );
 *
 *
 * Fib-elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 *
 * call: tEvalueObject [DIR_TESTDATA]
 *
 * parameters:
 * 	DIR_TESTDATA
 * 		The path wher the testdata could be found. The standardfolder is "testObjects/".
 */
/*
History:
07.02.2010  Oesterholz  created
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
10.11.2011  Oesterholz  Bugfix: evalueObject() don't overwrite properties
29.11.2011  Oesterholz  evalue number of folders wher errors occured
22.10.2012  Oesterholz  if an error occured when evaluing points: output data
*/

#include "version.h"
#include "fibDatatyps.h"

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

#ifndef DIR_TESTOBJECTS
	#define DIR_TESTOBJECTS "testObjects/"
#endif
#ifndef FILE_TESTOBJECTS
	#define FILE_TESTOBJECTS "testWithEvalue.txt"
#endif


using namespace fib;
using namespace std;




const char * pDirTestObjects = DIR_TESTOBJECTS;


list< string > loadTestFolderList( const string szFilePath );
list< string > loadTestFileList( const string szTestFolderName );
unsigned int comparePositionData( const list< pair< cVectorPosition, list< cVectorProperty > > > & liPositionDataCorrect,
		const list< pair< cVectorPosition, list< cVectorProperty > > > & liPositionDataEvalued );
unsigned int compareElementData( const list< pair< cFibElement*, list< cVectorProperty > > > & liElementDataCorrect,
		const list< pair< cFibElement*, list< cVectorProperty > > > & liElementDataEvalued );
void clearEvaluedElementData( list< pair< cFibElement*, list< cVectorProperty > > >
		& liListToClear );
list< cVectorProperty > generateRandomProperties();
list< pair< cVectorPosition, list< cVectorProperty > > > addPropertiesToAll(
		list< pair< cVectorPosition, list< cVectorProperty > > > liData,
		const list< cVectorProperty > & liProperties );
list< pair< cFibElement*, list< cVectorProperty > > > addPropertiesToAll(
		list< pair< cFibElement*, list< cVectorProperty > > > liData,
		const list< cVectorProperty > & liProperties );
list< pair< cVectorPosition, list< cVectorProperty > > > loadPositionData(
		const char * szFilename );
list< pair< cFibElement*, list< cVectorProperty > > > loadElementData(
		const char * szFilename,
		list<cFibVariable*> liDefinedVariables = list<cFibVariable*>() );
void enumerateVariables( list<cFibVariable*> & liVariables );


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	int iFailedTestphases = 0;//returnvalue of the test; the number of occured Errors
	list< string > liErrorsInTestFolders;
	
	srand( time(NULL) );
	
	if ( argc >= 2 ){
		//one parameter given; get parameter test data path
		pDirTestObjects = argv[1];
	}
	
	cout<<endl<<"Running Test for Fib object evalue methods"<<endl;
	cout<<      "==========================================="<<endl;
	
	//load the testfolder list
	string szFilePath = string( pDirTestObjects ) + FILE_TESTOBJECTS;
	
	list< string > liTestfolders = loadTestFolderList( szFilePath );
	if ( liTestfolders.empty() ){
		cerr<<"Error: No testfolders to test."<<endl;
		iReturn++;
		return iReturn;
	}
	
	//for each testfolder
	for ( list< string >::iterator itrTestFolder = liTestfolders.begin();
			itrTestFolder != liTestfolders.end(); itrTestFolder++ ){
		
		unsigned int uiErrorsInTestphase = 0;
		const string szActualTestFolder = *itrTestFolder;
		ulTestphase++;
		cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the Fib object in folder \""<< szActualTestFolder <<"\""<<endl;
		
		//evalue the files in the testfolder
		const string szActualTestPath = string( pDirTestObjects ) +
			szActualTestFolder + "/";
		list< string > liTestFiles = loadTestFileList( szActualTestPath );
		
		string szEvaluePointAll = "";
		/* files for evalue Elements; the first pair element is the filename
		and the second the pair for the parameters; the parameter pairs first
		element ist the partobject to evalue and the second the to evalue
		Fib-elements*/
		list< pair< string, pair< unsigned int , list< char > > > > liEvalueElementAll;
		
		/*evalue with evaluePoint() for a partobject;
		the first pair parameter is the filename with the data and the
		second the number of the partobject to evalue*/
		list< pair< string, unsigned int > > liEvaluePointPartObject;
		
		bool bFibObjectToTestOnExists = false;
		//seperate the evalued files for the differnt test typs
		for ( list< string >::iterator itrTestFile = liTestFiles.begin();
				itrTestFile != liTestFiles.end(); itrTestFile++ ){
			
			if ( (*itrTestFile) == (*itrTestFolder) + ".xml" ){
				
				cout<<"Fib object to test on: "<< (*itrTestFile) << endl;
				bFibObjectToTestOnExists = true;
			}else if ( (*itrTestFile) == (*itrTestFolder) + "EvP.xml" ){
				
				szEvaluePointAll = (*itrTestFile);
				cout<<"File with data of evaluing the wool object with evaluePoint() : "<< (*itrTestFile) << endl;
			}else if ( itrTestFile->compare( 0, itrTestFolder->size() + 3, (*itrTestFolder) + "EvE" ) == 0 ){
				
				liEvalueElementAll.push_back( make_pair( *itrTestFile,
					make_pair( 0, list<char>() ) ) );
				cout<<"File with data of evaluing with evalueElement() : "<< (*itrTestFile) << endl;
				cout<<"   Evaluing for typs: ";
				char cActualChar = ' ';
				unsigned int uiPosition = 0;
				for ( uiPosition = (itrTestFolder->size() + 3);
						uiPosition <= itrTestFile->size(); uiPosition++ ){
					
					cActualChar = (*itrTestFile)[uiPosition];
					if ( (cActualChar == '.') || (cActualChar == '_') ){
						break;
					}
					cout<<"'"<< cActualChar <<"'; ";
					liEvalueElementAll.back().second.second.push_back( cActualChar );
				}
				cout<<endl;
			
				if ( cActualChar == '_' ){
					//evalue the partobject to evalue
					const char * pPartobjectNumber =
						&((itrTestFile->c_str())[ uiPosition + 3 ]);
					
					liEvalueElementAll.back().second.first = atol( pPartobjectNumber );
					cout<<"   Evaluing the partobject: "<<
						liEvalueElementAll.back().second.first <<endl;
				}else{
					cout<<"   Evaluing for the wool objects. "<<endl;
				}
			}else if ( itrTestFile->compare( 0, itrTestFolder->size() + 4, (*itrTestFolder) + "EvP_" ) == 0 ){
				
				liEvaluePointPartObject.push_back( make_pair( *itrTestFile, 0 ) );
				//evalue the partobject to evalue
				const char * pPartobjectNumber =
					&((itrTestFile->c_str())[ itrTestFolder->size() + 6 ]);
				liEvaluePointPartObject.back().second = atol( pPartobjectNumber );
				
				cout<<"File with data of evaluing with evaluePoint() the "<<
					liEvaluePointPartObject.back().second <<
					"'th partobject : "<< (*itrTestFile) << endl;
				
			}else{
				cout<<"Skipping file "<< (*itrTestFile) <<" because the type is unknown."<<endl;
			}
		}
		if ( ! bFibObjectToTestOnExists ){
			cerr<<"Error: Ther is no file "<< (*itrTestFolder) <<" with the Fib object to test on in the testfolder."<<endl;
			uiErrorsInTestphase++;
			iReturn += uiErrorsInTestphase;
			iFailedTestphases++;
			liErrorsInTestFolders.push_back( szActualTestFolder );
			continue;//skip this testfolder
		}
		cout<<endl;
		//load the Fib object to check
		const string szPathFibObjectToTest = szActualTestPath +
			((*itrTestFolder) + ".xml");
		ifstream inFile( szPathFibObjectToTest.c_str() );
		
		intFib outStatus = 0;
		cFibElement * pFibObjectToTest = cFibElement::restoreXml( inFile , &outStatus );
		
		if ( (outStatus == 0) && (pFibObjectToTest != NULL) ){
			cout<<"Restoring Fib object in the Xml format from the file "<<
				szPathFibObjectToTest <<" successfull."<<endl;
		}else{
			cerr<<"Error: Restoring Fib object in the Xml format from the file "<<
				szPathFibObjectToTest <<" not successfull. (return status="<< outStatus <<")"<<endl;
			uiErrorsInTestphase++;
			iReturn += uiErrorsInTestphase;
			iFailedTestphases++;
			if ( pFibObjectToTest ){
				pFibObjectToTest->deleteObject();
			}
			liErrorsInTestFolders.push_back( szActualTestFolder );
			continue;
		}
		const cFibElement * pFibObjectToTestConst = pFibObjectToTest;
		//create a clone on the fib object to check
		cFibElement * pFibObjectToTestClone = pFibObjectToTest->clone();
		
	//for evaluePoint()
		//test evalue evalueObjectSimple() and evalueObject() on the whool object with no given propertylists
		//load the data of the correctly evalued object
		cout<<endl<<"Checking the evalue methods with evaluePoint():"<<endl;
		list< pair< cVectorPosition, list< cVectorProperty > > > liEvaluePointAllLoaded =
			loadPositionData( (szActualTestPath + szEvaluePointAll).c_str() );
		
		//evalue the Fib object
		cEvaluePositionList evaluePositionList;
		evaluePositionList.ulCountOfEvalueMethodCalled = 0;
		evaluePositionList.lNumberOfTrueEvalueCalls = -1;
		cout<<"Calling evalueObjectSimple() on wool object."<<endl;
		bool bObjectEvalued = pFibObjectToTestConst->evalueObjectSimple( evaluePositionList );
		if ( bObjectEvalued == liEvaluePointAllLoaded.empty() ){
			cerr<<"Error: The method evalueObjectSimple() returns "<<
				(bObjectEvalued?"true":"false") <<" but ther are "<<
				(liEvaluePointAllLoaded.empty()?"no ":"") <<"points to evalue."<<endl;
			uiErrorsInTestphase++;
		}
		//compare evalued data with the loaded data
		uiErrorsInTestphase += comparePositionData( liEvaluePointAllLoaded, evaluePositionList.liEvaluedPositionData );
		
		//evalue the Fib object
		cout<<"Calling evalueObject() on wool object."<<endl;
		list<cVectorProperty> liVecProperties;
		evaluePositionList.clear();
		evaluePositionList.ulCountOfEvalueMethodCalled = 0;
		evaluePositionList.lNumberOfTrueEvalueCalls = -1;
		bObjectEvalued = pFibObjectToTestConst->
			evalueObject( evaluePositionList, 0, liVecProperties );
		if ( bObjectEvalued == liEvaluePointAllLoaded.empty() ){
			cerr<<"Error: The method evalueObject() returns "<<
				(bObjectEvalued?"true":"false") <<" but ther are "<<
				(liEvaluePointAllLoaded.empty()?"no ":"") <<"points to evalue."<<endl;
			uiErrorsInTestphase++;
		}
		//compare evalued data with the loaded data
		uiErrorsInTestphase += comparePositionData( liEvaluePointAllLoaded, evaluePositionList.liEvaluedPositionData );
		liVecProperties.clear();
		
		//test evalue evalueObject() on the whool object with a given propertylists, with random properties
		const list< cVectorProperty > liRandomProperties = generateRandomProperties();
		list< pair< cVectorPosition, list< cVectorProperty > > > liEvaluePointAllLoadedPlusRandom =
			addPropertiesToAll( liEvaluePointAllLoaded, liRandomProperties );
		
		//evalue the Fib object
		cout<<"Calling evalueObject() on wool object with given random property vectores."<<endl;
		list< cVectorProperty > liRandomPropertiesCopy = liRandomProperties;
		evaluePositionList.clear();
		evaluePositionList.ulCountOfEvalueMethodCalled = 0;
		evaluePositionList.lNumberOfTrueEvalueCalls = -1;
		bObjectEvalued = pFibObjectToTestConst->evalueObject( evaluePositionList, 0, liRandomPropertiesCopy );
		if ( bObjectEvalued == liEvaluePointAllLoaded.empty() ){
			cerr<<"Error: The method evalueObject() returns "<<
				(bObjectEvalued?"true":"false") <<" but ther are "<<
				(liEvaluePointAllLoaded.empty()?"no ":"") <<"points to evalue."<<endl;
			uiErrorsInTestphase++;
		}
		//compare evalued data with the loaded data
		uiErrorsInTestphase += comparePositionData( liEvaluePointAllLoadedPlusRandom, evaluePositionList.liEvaluedPositionData );
		
		
		for ( list< pair< string, unsigned int > >::const_iterator
				itrEvalueParameter = liEvaluePointPartObject.begin();
				itrEvalueParameter != liEvaluePointPartObject.end();
				itrEvalueParameter++ ){
			
			//test evalue evalueObjectSimple() and evalueObject() on the given objectpoints with no given propertylists
			cout<<"The testfile is: "<< itrEvalueParameter->first <<endl;
			list< pair< cVectorPosition, list< cVectorProperty > > > liEvaluePointPartLoaded =
				loadPositionData( (szActualTestPath + itrEvalueParameter->first).c_str() );
			
			cEvaluePositionList evaluePositionListPart;
			evaluePositionListPart.ulCountOfEvalueMethodCalled = 0;
			evaluePositionListPart.lNumberOfTrueEvalueCalls = 100000;
			//evalue the Fib object
			cout<<"Calling evalueObjectSimple() on the "<<
				itrEvalueParameter->second <<"'th partobject."<<endl;
			bObjectEvalued = pFibObjectToTestConst->evalueObjectSimple(
				evaluePositionListPart, itrEvalueParameter->second );
			if ( bObjectEvalued == liEvaluePointPartLoaded.empty() ){
				cerr<<"Error: The method evalueObjectSimple() returns "<<
					(bObjectEvalued?"true":"false") <<" but ther are "<<
					(liEvaluePointPartLoaded.empty()?"no ":"") <<"points to evalue."<<endl;
				uiErrorsInTestphase++;
			}
			//compare evalued data with the loaded data
			uiErrorsInTestphase += comparePositionData( liEvaluePointPartLoaded, evaluePositionListPart.liEvaluedPositionData );
			
			evaluePositionListPart.clear();
			evaluePositionListPart.ulCountOfEvalueMethodCalled = 0;
			evaluePositionListPart.lNumberOfTrueEvalueCalls = 100000;
			//evalue the Fib object
			cout<<"Calling evalueObject() on the "<<
				itrEvalueParameter->second <<"'th partobject."<<endl;
			bObjectEvalued = pFibObjectToTestConst->evalueObject( evaluePositionListPart,
				itrEvalueParameter->second, liVecProperties );
			if ( bObjectEvalued == liEvaluePointPartLoaded.empty() ){
				cerr<<"Error: The method evalueObject() returns "<<
					(bObjectEvalued?"true":"false") <<" but ther are "<<
					(liEvaluePointPartLoaded.empty()?"no ":"") <<"points to evalue."<<endl;
				uiErrorsInTestphase++;
			}
			//compare evalued data with the loaded data
			uiErrorsInTestphase += comparePositionData( liEvaluePointPartLoaded, evaluePositionListPart.liEvaluedPositionData );
			liVecProperties.clear();
			
			//test evalue evalueObject() on the given objectpoints with a given propertylists, with random properties
			list< pair< cVectorPosition, list< cVectorProperty > > > liEvaluePointPartLoadedPlusRandom =
				addPropertiesToAll( liEvaluePointPartLoaded, liRandomProperties );
			
			liRandomPropertiesCopy = liRandomProperties;
			evaluePositionListPart.clear();
			evaluePositionListPart.ulCountOfEvalueMethodCalled = 0;
			evaluePositionListPart.lNumberOfTrueEvalueCalls = 100000;
			//evalue the Fib object
			cout<<"Calling evalueObject() on the "<<
				itrEvalueParameter->second <<"'th partobject with given random property vectores."<<endl;
			liRandomPropertiesCopy = liRandomProperties;
			bObjectEvalued = pFibObjectToTestConst->evalueObject( evaluePositionListPart,
				itrEvalueParameter->second , liRandomPropertiesCopy );
			if ( bObjectEvalued == liEvaluePointPartLoaded.empty() ){
				cerr<<"Error: The method evalueObject() returns "<<
					(bObjectEvalued?"true":"false") <<" but ther are "<<
					(liEvaluePointPartLoaded.empty()?"no ":"") <<"points to evalue."<<endl;
				uiErrorsInTestphase++;
			}
			//compare evalued data with the loaded data
			uiErrorsInTestphase += comparePositionData( liEvaluePointPartLoadedPlusRandom, evaluePositionListPart.liEvaluedPositionData );
		}
	
	//for evalueElement() on given elementtyps
		//evalue the defined variables of the Fib object
		list<cFibVariable*> liDefinedVariables =
			pFibObjectToTest->getDefinedVariables( ED_ALL );
		
		cout<<endl<<"Checking the evalue methods with evalueElement():"<<endl;
		
		
		for ( list< pair< string, pair< unsigned int , list< char > > > >::const_iterator
				itrEvalueParameter = liEvalueElementAll.begin();
				itrEvalueParameter != liEvalueElementAll.end();
				itrEvalueParameter++ ){
			
			//test evalue evalueObjectSimple() and evalueObject() on the given objectpoints with no given propertylists
			cout<<"The testfile is: "<< itrEvalueParameter->first <<endl;
			list< pair< cFibElement*, list< cVectorProperty > > > liEvalueElementPartLoaded =
				loadElementData((szActualTestPath + itrEvalueParameter->first).c_str(),
				liDefinedVariables );

			cEvalueFibElementList evalueFibElementListPart( true );
			evalueFibElementListPart.ulCountOfEvalueMethodCalled = 0;
			evalueFibElementListPart.lNumberOfTrueEvalueCalls = 100000;
			//evalue the Fib object
			cout<<"Calling evalueObjectSimple() on the "<<
				itrEvalueParameter->second.first <<"'th partobject."<<endl;
			bObjectEvalued = pFibObjectToTest->evalueObjectSimple( evalueFibElementListPart,
				itrEvalueParameter->second.first, itrEvalueParameter->second.second );
				
			if ( bObjectEvalued == liEvalueElementPartLoaded.empty() ){
				cerr<<"Error: The method evalueObjectSimple() returns "<<
					(bObjectEvalued?"true":"false") <<" but ther are "<<
					(liEvalueElementPartLoaded.empty()?"no ":"") <<"points to evalue."<<endl;
				uiErrorsInTestphase++;
			}
			//compare evalued data with the loaded data
			uiErrorsInTestphase += compareElementData( liEvalueElementPartLoaded, evalueFibElementListPart.liEvaluedElementData );

			evalueFibElementListPart.clear();
			evalueFibElementListPart.ulCountOfEvalueMethodCalled = 0;
			evalueFibElementListPart.lNumberOfTrueEvalueCalls = 100000;
			//evalue the Fib object
			cout<<"Calling evalueObject() on the "<<
				itrEvalueParameter->second.first <<"'th partobject."<<endl;
			bObjectEvalued = pFibObjectToTest->evalueObject( evalueFibElementListPart,
				itrEvalueParameter->second.first, liVecProperties,
				itrEvalueParameter->second.second );
			if ( bObjectEvalued == liEvalueElementPartLoaded.empty() ){
				cerr<<"Error: The method evalueObject() returns "<<
					(bObjectEvalued?"true":"false") <<" but ther are "<<
					(liEvalueElementPartLoaded.empty()?"no ":"") <<"points to evalue."<<endl;
				uiErrorsInTestphase++;
			}
			//compare evalued data with the loaded data
			uiErrorsInTestphase += compareElementData( liEvalueElementPartLoaded, evalueFibElementListPart.liEvaluedElementData );
			liVecProperties.clear();
			
			evalueFibElementListPart.clear();
			evalueFibElementListPart.ulCountOfEvalueMethodCalled = 0;
			evalueFibElementListPart.lNumberOfTrueEvalueCalls = 100000;
			
			//test evalue evalueObject() on the given objectpoints with a given propertylists, with random properties
			list< pair< cFibElement*, list< cVectorProperty > > > liEvalueElementPartLoadedPlusRandom =
				addPropertiesToAll( liEvalueElementPartLoaded, liRandomProperties );
			
			//evalue the Fib object
			cout<<"Calling evalueObject() on the "<<
				itrEvalueParameter->second.first <<"'th partobject with given random property vectores."<<endl;
			liRandomPropertiesCopy = liRandomProperties;
			bObjectEvalued = pFibObjectToTest->evalueObject( evalueFibElementListPart,
				itrEvalueParameter->second.first, liRandomPropertiesCopy,
				itrEvalueParameter->second.second );
			if ( bObjectEvalued == liEvalueElementPartLoaded.empty() ){
				cerr<<"Error: The method evalueObject() returns "<<
					(bObjectEvalued?"true":"false") <<" but ther are "<<
					(liEvalueElementPartLoaded.empty()?"no ":"") <<"points to evalue."<<endl;
				uiErrorsInTestphase++;
			}
			
			//compare evalued data with the loaded data
			uiErrorsInTestphase += compareElementData( liEvalueElementPartLoadedPlusRandom, evalueFibElementListPart.liEvaluedElementData );

			clearEvaluedElementData( liEvalueElementPartLoaded );
		}

	//check the case when evaluePoint() or evalueElement() retun false
		cout<<endl<<"Checking the case when the evalue*() methods return false after some calls."<<endl;
		
	//for evaluePoint()
		//test evalue evalueObjectSimple() and evalueObject() on the whool object with no given propertylists
		if ( ! liEvaluePointAllLoaded.empty() ){
			cout<<endl<<"Checking the evalue methods with evaluePoint():"<<endl;
			list< pair< cVectorPosition, list< cVectorProperty > > >
				liEvaluePointAllResized = liEvaluePointAllLoaded;
		
			evaluePositionList.clear();
			evaluePositionList.ulCountOfEvalueMethodCalled = 0;
			evaluePositionList.lNumberOfTrueEvalueCalls = rand() % liEvaluePointAllLoaded.size();;
			liEvaluePointAllResized.resize( evaluePositionList.lNumberOfTrueEvalueCalls );
			//evalue the Fib object
			cout<<"Calling evalueObjectSimple() on wool object."<<endl;
			bObjectEvalued = pFibObjectToTestConst->evalueObjectSimple( evaluePositionList );
			if ( bObjectEvalued ){
				cerr<<"Error: The method evalueObjectSimple() returns true."<<endl;
				uiErrorsInTestphase++;
			}
			//compare evalued data with the loaded data
			uiErrorsInTestphase += comparePositionData( liEvaluePointAllResized, evaluePositionList.liEvaluedPositionData );
			
			evaluePositionList.clear();
			evaluePositionList.ulCountOfEvalueMethodCalled = 0;
			evaluePositionList.lNumberOfTrueEvalueCalls = liEvaluePointAllResized.size();
			//evalue the Fib object
			cout<<"Calling evalueObject() on wool object."<<endl;
			bObjectEvalued = pFibObjectToTestConst->
				evalueObject( evaluePositionList, 0, liVecProperties );
			if ( bObjectEvalued ){
				cerr<<"Error: The method evalueObject() returns true."<<endl;
				uiErrorsInTestphase++;
			}
			//compare evalued data with the loaded data
			uiErrorsInTestphase += comparePositionData( liEvaluePointAllResized, evaluePositionList.liEvaluedPositionData );
			liVecProperties.clear();
			
			//test evalue evalueObject() on the whool object with a given propertylists, with random properties
			list< pair< cVectorPosition, list< cVectorProperty > > > liEvaluePointAllResizedPlusRandom =
				addPropertiesToAll( liEvaluePointAllResized, liRandomProperties );
			
			evaluePositionList.clear();
			evaluePositionList.ulCountOfEvalueMethodCalled = 0;
			evaluePositionList.lNumberOfTrueEvalueCalls = liEvaluePointAllResized.size();
			//evalue the Fib object
			cout<<"Calling evalueObject() on wool object with given random property vectores."<<endl;
			liRandomPropertiesCopy = liRandomProperties;
			bObjectEvalued = pFibObjectToTestConst->evalueObject(
				evaluePositionList, 0, liRandomPropertiesCopy );
			if ( bObjectEvalued ){
				cerr<<"Error: The method evalueObject() returns true."<<endl;
				uiErrorsInTestphase++;
			}
			//compare evalued data with the loaded data
			uiErrorsInTestphase += comparePositionData( liEvaluePointAllResizedPlusRandom, evaluePositionList.liEvaluedPositionData );
		}
		for ( list< pair< string, unsigned int > >::const_iterator
				itrEvalueParameter = liEvaluePointPartObject.begin();
				itrEvalueParameter != liEvaluePointPartObject.end();
				itrEvalueParameter++ ){
			
			//test evalue evalueObjectSimple() and evalueObject() on the given objectpoints with no given propertylists
			cout<<"The testfile is: "<< itrEvalueParameter->first <<endl;
			list< pair< cVectorPosition, list< cVectorProperty > > > liEvaluePointPartLoaded =
				loadPositionData( (szActualTestPath + itrEvalueParameter->first).c_str() );
			if ( liEvaluePointPartLoaded.empty() ){
				//nothing to evalue -> evalue can't fail
				cout<<"Nothing to evalue for "<<itrEvalueParameter->first<<" -> evalue can't fail -> skip it"<<endl;
				continue;
			}
			
			evaluePositionList.clear();
			evaluePositionList.ulCountOfEvalueMethodCalled = 0;
			evaluePositionList.lNumberOfTrueEvalueCalls = rand() % liEvaluePointPartLoaded.size();
			list< pair< cVectorPosition, list< cVectorProperty > > >
				liEvaluePointPartResized = liEvaluePointPartLoaded;
			liEvaluePointPartResized.resize( evaluePositionList.lNumberOfTrueEvalueCalls );
			//evalue the Fib object
			cout<<"Calling evalueObjectSimple() on the "<<
				itrEvalueParameter->second <<"'th partobject."<<endl;
			bObjectEvalued = pFibObjectToTestConst->evalueObjectSimple(
				evaluePositionList, itrEvalueParameter->second );
			if ( bObjectEvalued ){
				cerr<<"Error: The method evalueObjectSimple() returns true."<<endl;
				uiErrorsInTestphase++;
			}
			//compare evalued data with the loaded data
			uiErrorsInTestphase += comparePositionData( liEvaluePointPartResized, evaluePositionList.liEvaluedPositionData );
			
			evaluePositionList.clear();
			evaluePositionList.ulCountOfEvalueMethodCalled = 0;
			evaluePositionList.lNumberOfTrueEvalueCalls = liEvaluePointPartResized.size();
			//evalue the Fib object
			cout<<"Calling evalueObject() on the "<<
				itrEvalueParameter->second <<"'th partobject."<<endl;
			bObjectEvalued = pFibObjectToTestConst->evalueObject( evaluePositionList,
				itrEvalueParameter->second, liVecProperties );
			if ( bObjectEvalued ){
				cerr<<"Error: The method evalueObject() returns true."<<endl;
				uiErrorsInTestphase++;
			}
			//compare evalued data with the loaded data
			uiErrorsInTestphase += comparePositionData( liEvaluePointPartResized, evaluePositionList.liEvaluedPositionData );
			liVecProperties.clear();
			
			//test evalue evalueObject() on the given objectpoints with a given propertylists, with random properties
			list< pair< cVectorPosition, list< cVectorProperty > > > liEvaluePointPartResizedPlusRandom =
				addPropertiesToAll( liEvaluePointPartResized, liRandomProperties );
			
			evaluePositionList.clear();
			evaluePositionList.ulCountOfEvalueMethodCalled = 0;
			evaluePositionList.lNumberOfTrueEvalueCalls = liEvaluePointPartResized.size();
			//evalue the Fib object
			cout<<"Calling evalueObject() on the "<<
				itrEvalueParameter->second <<"'th partobject with given random property vectores."<<endl;
			liRandomPropertiesCopy = liRandomProperties;
			bObjectEvalued = pFibObjectToTestConst->evalueObject( evaluePositionList,
				itrEvalueParameter->second , liRandomPropertiesCopy );
			if ( bObjectEvalued ){
				cerr<<"Error: The method evalueObject() returns true."<<endl;
				uiErrorsInTestphase++;
			}
			//compare evalued data with the loaded data
			uiErrorsInTestphase += comparePositionData( liEvaluePointPartResizedPlusRandom, evaluePositionList.liEvaluedPositionData );
		}
	//for evalueElement() on given elementtyps
		cout<<endl<<"Checking the evalue methods with evalueElement():"<<endl;
		for ( list< pair< string, pair< unsigned int , list< char > > > >::const_iterator
				itrEvalueParameter = liEvalueElementAll.begin();
				itrEvalueParameter != liEvalueElementAll.end();
				itrEvalueParameter++ ){
			
			//test evalue evalueObjectSimple() and evalueObject() on the given objectpoints with no given propertylists
			cout<<"The testfile is: "<< itrEvalueParameter->first <<endl;
			list< pair< cFibElement*, list< cVectorProperty > > > liEvalueElementPartLoaded =
				loadElementData( (szActualTestPath + itrEvalueParameter->first).c_str(),
				liDefinedVariables );
			if ( liEvalueElementPartLoaded.empty() ){
				//nothing to evalue -> evalue can't fail
				cout<<"Nothing to evalue for "<<itrEvalueParameter->first<<" -> evalue can't fail -> skip it"<<endl;
				continue;
			}
			
			cEvalueFibElementList evalueFibElementListPart( true );
			evalueFibElementListPart.ulCountOfEvalueMethodCalled = 0;
			evalueFibElementListPart.lNumberOfTrueEvalueCalls = rand() % liEvalueElementPartLoaded.size();
			list< pair< cFibElement*, list< cVectorProperty > > >
				liEvalueElementPartResized = liEvalueElementPartLoaded;
			liEvalueElementPartResized.resize( evalueFibElementListPart.lNumberOfTrueEvalueCalls );
			
			//evalue the Fib object
			cout<<"Calling evalueObjectSimple() on the "<<
				itrEvalueParameter->second.first <<"'th partobject."<<endl;
			bObjectEvalued = pFibObjectToTest->evalueObjectSimple( evalueFibElementListPart,
				itrEvalueParameter->second.first, itrEvalueParameter->second.second );
			if ( bObjectEvalued ){
				cerr<<"Error: The method evalueObjectSimple() returns true."<<endl;
				uiErrorsInTestphase++;
			}
			//compare evalued data with the loaded data
			uiErrorsInTestphase += compareElementData( liEvalueElementPartResized, evalueFibElementListPart.liEvaluedElementData );
			
			//evalue the Fib object
			cout<<"Calling evalueObject() on the "<<
				itrEvalueParameter->second.first <<"'th partobject."<<endl;
			evalueFibElementListPart.clear();
			evalueFibElementListPart.ulCountOfEvalueMethodCalled = 0;
			evalueFibElementListPart.lNumberOfTrueEvalueCalls = liEvalueElementPartResized.size();
			bObjectEvalued = pFibObjectToTest->evalueObject( evalueFibElementListPart,
				itrEvalueParameter->second.first, liVecProperties,
				itrEvalueParameter->second.second );
			if ( bObjectEvalued ){
				cerr<<"Error: The method evalueObject() returns true."<<endl;
				uiErrorsInTestphase++;
			}
			//compare evalued data with the loaded data
			uiErrorsInTestphase += compareElementData( liEvalueElementPartResized, evalueFibElementListPart.liEvaluedElementData );
			liVecProperties.clear();
			
			//test evalue evalueObject() on the given objectpoints with a given propertylists, with random properties
			list< pair< cFibElement*, list< cVectorProperty > > > liEvalueElementPartResizedPlusRandom =
				addPropertiesToAll( liEvalueElementPartResized, liRandomProperties );
			
			//evalue the Fib object
			cout<<"Calling evalueObject() on the "<<
				itrEvalueParameter->second.first <<"'th partobject with given random property vectores."<<endl;
			evalueFibElementListPart.clear();
			evalueFibElementListPart.ulCountOfEvalueMethodCalled = 0;
			evalueFibElementListPart.lNumberOfTrueEvalueCalls = liEvalueElementPartResized.size();
			liRandomPropertiesCopy = liRandomProperties;
			bObjectEvalued = pFibObjectToTest->evalueObject( evalueFibElementListPart,
				itrEvalueParameter->second.first, liRandomPropertiesCopy,
				itrEvalueParameter->second.second );
			if ( bObjectEvalued ){
				cerr<<"Error: The method evalueObject() returns true."<<endl;
				uiErrorsInTestphase++;
			}
			//compare evalued data with the loaded data
			uiErrorsInTestphase += compareElementData( liEvalueElementPartResizedPlusRandom, evalueFibElementListPart.liEvaluedElementData );
			evalueFibElementListPart.clear();
			clearEvaluedElementData( liEvalueElementPartLoaded );
		}
		
		
	//try evalue of a objectpoint that dosn't exists
		const unsignedIntFib uiAfterNumberOfObjectPoints =
			pFibObjectToTest->getNumberOfObjectPoints() + 1;
		
		//for evaluePoint()
		cout<<"Calling evalueObjectSimple() on the non existing "<<
			uiAfterNumberOfObjectPoints <<"'th partobject."<<endl;
		evaluePositionList.clear();
		evaluePositionList.ulCountOfEvalueMethodCalled = 0;
		evaluePositionList.lNumberOfTrueEvalueCalls = -1;
		bObjectEvalued = pFibObjectToTestConst->evalueObjectSimple(
			evaluePositionList, uiAfterNumberOfObjectPoints );
		if ( bObjectEvalued ){
			cerr<<"Error: The method evalueObjectSimple() returns true."<<endl;
			uiErrorsInTestphase++;
		}
		//compare evalued data with the loaded data
		if ( ! evaluePositionList.liEvaluedPositionData.empty() ){
			cerr<<"Error: Some positionsdata evalued."<<endl;
			uiErrorsInTestphase++;
		}
		
		//evalue the Fib object
		cout<<"Calling evalueObject() on the non existing "<<
			uiAfterNumberOfObjectPoints <<"'th partobject."<<endl;
		evaluePositionList.clear();
		evaluePositionList.ulCountOfEvalueMethodCalled = 0;
		evaluePositionList.lNumberOfTrueEvalueCalls = -1;
		bObjectEvalued = pFibObjectToTestConst->evalueObject( evaluePositionList,
			uiAfterNumberOfObjectPoints, liVecProperties );
		if ( bObjectEvalued ){
			cerr<<"Error: The method evalueObject() returns true."<<endl;
			uiErrorsInTestphase++;
		}
		//compare evalued data with the loaded data
		if ( ! evaluePositionList.liEvaluedPositionData.empty() ){
			cerr<<"Error: Some positionsdata evalued."<<endl;
			uiErrorsInTestphase++;
		}
		liVecProperties.clear();
		
		//test evalue evalueObject() on the given objectpoints with a given propertylists, with random properties
		
		//evalue the Fib object
		cout<<"Calling evalueObject() on the non existing "<<
			uiAfterNumberOfObjectPoints <<"'th partobject with given random property vectores."<<endl;
		evaluePositionList.clear();
		evaluePositionList.ulCountOfEvalueMethodCalled = 0;
		evaluePositionList.lNumberOfTrueEvalueCalls = -1;
		liRandomPropertiesCopy = liRandomProperties;
		bObjectEvalued = pFibObjectToTestConst->evalueObject( evaluePositionList,
			uiAfterNumberOfObjectPoints, liRandomPropertiesCopy );
		if ( bObjectEvalued ){
			cerr<<"Error: The method evalueObject() returns true."<<endl;
			uiErrorsInTestphase++;
		}
		//compare evalued data with the loaded data
		if ( ! evaluePositionList.liEvaluedPositionData.empty() ){
			cerr<<"Error: Some positionsdata evalued."<<endl;
			uiErrorsInTestphase++;
		}
		liVecProperties.clear();

		//for evalueElement() on given elementtyp 'p'
		list<char> liFibElementTyps;
		liFibElementTyps.push_back( 'p' );
		cout<<"Calling evalueObjectSimple() on the non existing "<<
			uiAfterNumberOfObjectPoints <<"'th partobject."<<endl;
		cEvalueFibElementList evalueFibElementList( true );
		evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
		evalueFibElementList.lNumberOfTrueEvalueCalls = 100000;
		bObjectEvalued = pFibObjectToTest->evalueObjectSimple( evalueFibElementList,
			uiAfterNumberOfObjectPoints, liFibElementTyps );
		if ( bObjectEvalued ){
			cerr<<"Error: The method evalueObject() returns true."<<endl;
			uiErrorsInTestphase++;
		}
		//compare evalued data with the loaded data
		if ( ! evalueFibElementList.liEvaluedElementData.empty() ){
			cerr<<"Error: Some positionsdata evalued."<<endl;
			uiErrorsInTestphase++;
		}
		
		//evalue the Fib object
		cout<<"Calling evalueObject() on the non existing "<<
			uiAfterNumberOfObjectPoints <<"'th partobject."<<endl;
		evalueFibElementList.clear();
		evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
		evalueFibElementList.lNumberOfTrueEvalueCalls = 100000;
		bObjectEvalued = pFibObjectToTest->evalueObject( evalueFibElementList,
			uiAfterNumberOfObjectPoints, liVecProperties,
			liFibElementTyps );
		if ( bObjectEvalued ){
			cerr<<"Error: The method evalueObject() returns true."<<endl;
			uiErrorsInTestphase++;
		}
		//compare evalued data with the loaded data
		if ( ! evalueFibElementList.liEvaluedElementData.empty() ){
			cerr<<"Error: Some positionsdata evalued."<<endl;
			uiErrorsInTestphase++;
		}
		//compare evalued data with the loaded data
		liVecProperties.clear();
		
		//test evalue evalueObject() on the given objectpoints with a given propertylists, with random properties
		//evalue the Fib object
		cout<<"Calling evalueObject() on the non existing "<<
			uiAfterNumberOfObjectPoints <<"'th partobject with given random property vectores."<<endl;
		liRandomPropertiesCopy = liRandomProperties;
		evalueFibElementList.clear();
		evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
		evalueFibElementList.lNumberOfTrueEvalueCalls = 100000;
		bObjectEvalued = pFibObjectToTest->evalueObject( evalueFibElementList,
			uiAfterNumberOfObjectPoints, liRandomPropertiesCopy,
			liFibElementTyps );
		if ( bObjectEvalued ){
			cerr<<"Error: The method evalueObject() returns true."<<endl;
			uiErrorsInTestphase++;
		}
		//compare evalued data with the loaded data
		if ( ! evalueFibElementList.liEvaluedElementData.empty() ){
			cerr<<"Error: Some positionsdata evalued."<<endl;
			uiErrorsInTestphase++;
		}

		//check if the Fib object hasn't changed
		if ( pFibObjectToTestClone != NULL ){
			if ( ! pFibObjectToTest->equal( *pFibObjectToTestClone ) ){
				cerr<<"Error: The Fib object has changed while storing ."<<endl;
				uiErrorsInTestphase++;
			}
			cFibElement::deleteObject( pFibObjectToTestClone );
		}else{
			cerr<<"Error: No clone could be created from the Fib object to test."<<endl;
			uiErrorsInTestphase++;
		}

		//destroy the loaded object
		if ( uiErrorsInTestphase != 0 ){
			iReturn += uiErrorsInTestphase;
			iFailedTestphases++;
			liErrorsInTestFolders.push_back( szActualTestFolder );
		}
		cFibElement::deleteObject( pFibObjectToTest );
	}
	
	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured in "<<iFailedTestphases<<" folders"<<endl;
		
		cerr<<"Errors wher in testfolders: ";
		for ( list< string >::const_iterator
				itrTestFolder = liErrorsInTestFolders.begin();
				itrTestFolder != liErrorsInTestFolders.end(); itrTestFolder++ ){
			
			cout<<(*itrTestFolder)<<"; ";
		}
		cout<<endl;
	}

	return iReturn;
}



/**
 * This function reads the given file and returns a list with its lines.
 * The lines in the files should be the subfolders to check.
 *
 * @param szFilePath the path wher the folderlist to check is stored;
 * 	each folder to check is writen in a seperate line
 * @return a list with the folders to check
 */
list< string > loadTestFolderList( const string szFilePath ){
	
	list< string > liFolders;
	
	ifstream ifStream( szFilePath.c_str() );
	
	if ( ! ifStream.good() ){
		
		cerr<<"Error: Couldn't read the folder list "<< szFilePath <<endl;
		return liFolders;
	}
	char szBuffer[ 1024 ];
	
	while( ifStream.good() ){
	
		ifStream.getline( szBuffer, 1024 );
		string szFolder( szBuffer );
		if ( szFolder != "" ){
			liFolders.push_back( szFolder );
		}
	}
	return liFolders;
}


/**
 * This function reads the given directory and gives back all filenames
 * of files it contains.
 * This files should be used as a testcase.
 *
 * @param szTestFolderName the name of the folder, which contains the files
 * 	with the testdata
 * @return the list of files in the given folder
 */
list< string > loadTestFileList( const string szTestFolderName ){
	
	cFolder folder( szTestFolderName );
	
	return folder.getFiles();
}


/**
 * This function compares the given list of positionvectors with ther properties.
 *
 * @param liPositionDataCorrect the correct positionsdata
 * @param liPositionDataEvalued the evalued positionsdata
 * @return 0 if the two given lists are equal, else the number of errors occured
 */
unsigned int comparePositionData( const list< pair< cVectorPosition, list< cVectorProperty > > > & liPositionDataCorrect,
		const list< pair< cVectorPosition, list< cVectorProperty > > > & liPositionDataEvalued ){
	
	int iReturn = 0;
	if ( liPositionDataCorrect.size() != liPositionDataEvalued.size() ){
		cerr<<"Error: The number of evalued position is wrong."<<endl;
		cerr<<"   correct: "<< liPositionDataCorrect.size() <<
			" evalued: "<< liPositionDataEvalued.size() <<endl;
		iReturn++;
	}
	list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
		itrList1 = liPositionDataCorrect.begin();
	list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
		itrList2 = liPositionDataEvalued.begin();
	unsigned int uiNumberOfPositions = 1;
	for ( ; (itrList1 != liPositionDataCorrect.end()) &&
			(itrList2 != liPositionDataEvalued.end());
			itrList1++, itrList2++, uiNumberOfPositions++ ){
		
		if ( ! ( itrList1->first == itrList2->first ) ){
			cerr<<"Error: The "<< uiNumberOfPositions <<"'th position isn't equal."<<endl;
			iReturn++;
		}
		if ( itrList1->second.size() != itrList2->second.size() ){
			cerr<<"Error: The number of properties of the "<< uiNumberOfPositions<<
				"'th position isn't equal."<<endl;
			cerr<<"   correct: "<< itrList1->second.size() <<
				" evalued: "<< itrList2->second.size() <<endl;
			iReturn++;
		}
		//compare the properties
		list< cVectorProperty >::const_iterator
			itrProperty1 = itrList1->second.begin();
		list< cVectorProperty >::const_iterator
			itrProperty2 = itrList2->second.begin();
		unsigned int uiNumberOfProperty = 1;
		for ( ; (itrProperty1 != itrList1->second.end() ) &&
				 (itrProperty2 != itrList2->second.end() );
				 itrProperty1++, itrProperty2++, uiNumberOfProperty++ ){
			if ( ! ( (*itrProperty1) == (*itrProperty2) ) ){
				cerr<<"Error: The "<< uiNumberOfProperty <<"'th property of the "<<
					uiNumberOfPositions <<"'th position isn't equal."<<endl;
				cerr<<"   correct type: "<<itrProperty1->getPropertyType()<<
					" value 1: "<<itrProperty1->getValue( 1 )<<endl;
				cerr<<"   evalued type: "<<itrProperty2->getPropertyType()<<
					" value 1: "<<itrProperty2->getValue( 1 )<<endl;
				iReturn++;
			}
		}
	}
	if ( 0 < iReturn ){
		//if errors occured
		cerr<<endl<<endl<<"Correct data:"<<endl<<flush;
	
		for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
					itrPosition = liPositionDataCorrect.begin();
				itrPosition != liPositionDataCorrect.end(); itrPosition++ ){
			
			itrPosition->first.storeXml( cerr );
			
			for ( list< cVectorProperty >::const_iterator
						itrProperty = itrPosition->second.begin();
					itrProperty != itrPosition->second.end(); itrProperty++ ){
						
				itrProperty->storeXml( cerr );
			}
		}
		
		cerr<<flush<<endl<<endl<<"Evalued data:"<<endl<<flush;
	
		for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
				itrPosition = liPositionDataEvalued.begin();
				itrPosition != liPositionDataEvalued.end(); itrPosition++ ){
			
			itrPosition->first.storeXml( cerr );
			
			for ( list< cVectorProperty >::const_iterator
						itrProperty = itrPosition->second.begin();
					itrProperty != itrPosition->second.end(); itrProperty++ ){
				
				itrProperty->storeXml( cerr );
			}
		}
		cerr<<endl<<endl<<flush;
	}
	return iReturn;
}


/**
 * This function compares the given list of Fib-elements with ther properties.
 *
 * @param liElementDataCorrect the correct data
 * @param liElementDataEvalued the evalued data
 * @return 0 if the two given lists are equal, else the number of errors occured
 */
unsigned int compareElementData( const list< pair< cFibElement*, list< cVectorProperty > > > & liElementDataCorrect,
		const list< pair< cFibElement*, list< cVectorProperty > > > & liElementDataEvalued ){
	
	int iReturn = 0;
	if ( liElementDataCorrect.size() != liElementDataEvalued.size() ){
		cerr<<"Error: The number of evalued Fib-elements is wrong."<<endl;
		cerr<<"   correct: "<< liElementDataCorrect.size() <<
			" evalued: "<< liElementDataEvalued.size() <<endl;
		iReturn++;
	}
	list< pair< cFibElement*, list< cVectorProperty > > >::const_iterator
		itrList1 = liElementDataCorrect.begin();
	list< pair< cFibElement*, list< cVectorProperty > > >::const_iterator
		itrList2 = liElementDataEvalued.begin();
	unsigned int uiNumberOfElement = 1;
	for ( ; (itrList1 != liElementDataCorrect.end()) &&
			(itrList2 != liElementDataEvalued.end());
			itrList1++, itrList2++, uiNumberOfElement++ ){
		
		if ( ! ( itrList1->first->equal( *(itrList2->first) ) ) ){
			cerr<<"Error: The "<< uiNumberOfElement <<"'th Fib-element isn't equal."<<endl;
			iReturn++;
		}
		if ( itrList1->second.size() != itrList2->second.size() ){
			cerr<<"Error: The number of properties of the "<< uiNumberOfElement<<
				"'th Fib-element isn't equal."<<endl;
			cerr<<"   correct: "<< itrList1->second.size() <<
				" evalued: "<< itrList2->second.size() <<endl;
			iReturn++;
		}
		//compare the properties
		list< cVectorProperty >::const_iterator
			itrProperty1 = itrList1->second.begin();
		list< cVectorProperty >::const_iterator
			itrProperty2 = itrList2->second.begin();
		unsigned int uiNumberOfProperty = 1;
		for ( ; (itrProperty1 != itrList1->second.end() ) &&
				 (itrProperty2 != itrList2->second.end() );
				 itrProperty1++, itrProperty2++, uiNumberOfProperty++ ){
			if ( ! ( (*itrProperty1) == (*itrProperty2) ) ){
				cerr<<"Error: The "<< uiNumberOfProperty <<"'th property of the "<<
					uiNumberOfElement <<"'th Fib-element isn't equal."<<endl;
				cerr<<"   correct type: "<<itrProperty1->getPropertyType()<<
					" value 1: "<<itrProperty1->getValue( 1 )<<endl;
				cerr<<"   evalued type: "<<itrProperty2->getPropertyType()<<
					" value 1: "<<itrProperty2->getValue( 1 )<<endl;
				iReturn++;
			}
		}
	}
	return iReturn;
}


/**
 * This method clears the data from the list with the evalued element data
 * liListToClear. It deletes all Fib objects the list contain.
 * After the function call the list will be empty.
 *
 * @param liListToClear a reference to the list to clear
 */
void clearEvaluedElementData( list< pair< cFibElement*, list< cVectorProperty > > >
		& liListToClear ){
	
	for ( list< pair< cFibElement*, list< cVectorProperty > > >::iterator
			itrEvaluedData = liListToClear.begin();
			itrEvaluedData != liListToClear.end(); itrEvaluedData++ ){
		
		if ( itrEvaluedData->first != NULL ){
			cFibElement::deleteObject( itrEvaluedData->first );
		}
	}
	liListToClear.clear();
}


/**
 * @return a list of random generated propertyvectors
 */
list< cVectorProperty > generateRandomProperties(){
	
	const unsignedIntFib aUiChoosebelPropertyTyps[] = {
		1, 2, 100, 200, 300, 301, 305, 310, 311, 312, 400, 410,
		//no existing typs
		46, 152 };
	const unsigned int uiCountOfChoosebelTyps =
		sizeof(aUiChoosebelPropertyTyps) / sizeof( unsignedIntFib );
	const unsigned int uiNumberOfPropertiesToChoos =
		(rand() % 6) % ((rand() % 6) + 1);
	list< cVectorProperty > liGeneratedProperties;
	
	for ( unsigned int uiPropertiesChoosen = 0;
			uiPropertiesChoosen < uiNumberOfPropertiesToChoos; uiPropertiesChoosen++ ){
		
		cVectorProperty vecProperty( aUiChoosebelPropertyTyps[
			rand() % uiCountOfChoosebelTyps ] );
		//don't add properties that would be overwriten by existing properties
		cTypeProperty * typeOfToInsertProperty = (cTypeProperty*)(
			vecProperty.getElementType());
		bool bSkipVector = false;
		for ( list<cVectorProperty>::iterator itrProperties = liGeneratedProperties.begin();
				itrProperties != liGeneratedProperties.end(); itrProperties++ ){

			cTypeProperty * typeOfProperty = (cTypeProperty*)(itrProperties->getElementType());
			list<cTypeProperty> liOverwritenTyps = typeOfProperty->getOverwritenTyps();
			
			for ( list<cTypeProperty>::iterator itrPropertyType = liOverwritenTyps.begin();
					itrPropertyType != liOverwritenTyps.end(); itrPropertyType++ ){
				
				if ( typeOfToInsertProperty->equalElementType( *itrPropertyType ) ){
					bSkipVector = true;
					break;
				}
			}
			delete typeOfProperty;
			if ( bSkipVector ){
				//skip this vector becaus it would be overwriten by existing vectors
				break;
			}
		}
		delete typeOfToInsertProperty;
		if ( bSkipVector ){
			//skip this vector becaus it would be overwriten by existing vectors
			continue;
		}
		
		liGeneratedProperties.push_back( vecProperty );
		const unsigned int uiNumberOfElements =
			liGeneratedProperties.back().getNumberOfElements();
		//generate random values
		for ( unsigned int uiActualElement = 1;
				uiActualElement < uiNumberOfElements; uiActualElement++ ){
			liGeneratedProperties.back().setValue( uiActualElement, rand() % 1024 );
		}
	}
	return liGeneratedProperties;
}


/**
 * This function adds all property vectores of the liPropertiesToAdd to
 * the front of liPropertiesToAddTo
 * #ifndef FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY:
 * 	, which are not overwritten by propertyvectors in liPropertiesToAddTo.
 *
 * @param liPropertiesToAddTo a reference to the propertyvectorlist to add to
 * @param liPropertiesToAdd the list with the propertyvectors add to
 */
void addPropertiesToPropertyList( list< cVectorProperty > & liPropertiesToAddTo,
		const list< cVectorProperty > liPropertiesToAdd ){
	
	for ( list< cVectorProperty >::const_reverse_iterator itrPropertyToAdd =
				liPropertiesToAdd.rbegin();
			itrPropertyToAdd != liPropertiesToAdd.rend(); itrPropertyToAdd++ ){

#ifndef FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY
		//don't add properties that would be overwriten by existing properties
		cTypeProperty * typeOfToInsertProperty = (cTypeProperty*)(
			itrPropertyToAdd->getElementType());
		bool bSkipVector = false;
		for ( list<cVectorProperty>::iterator itrProperties = liPropertiesToAddTo.begin();
				itrProperties != liPropertiesToAddTo.end(); itrProperties++ ){

			cTypeProperty * typeOfProperty = (cTypeProperty*)(itrProperties->getElementType());
			list<cTypeProperty> liOverwritenTyps = typeOfProperty->getOverwritenTyps();
			
			for ( list<cTypeProperty>::iterator itrPropertyType = liOverwritenTyps.begin();
					itrPropertyType != liOverwritenTyps.end(); itrPropertyType++ ){
				
				if ( typeOfToInsertProperty->equalElementType( *itrPropertyType ) ){
					bSkipVector = true;
					break;
				}
			}
			delete typeOfProperty;
			if ( bSkipVector ){
				//skip this vector becaus it would be overwriten by existing vectors
				break;
			}
		}
		delete typeOfToInsertProperty;
		if ( bSkipVector ){
			//skip this vector becaus it would be overwriten by existing vectors
			continue;
		}
#endif //not FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY
		
		liPropertiesToAddTo.push_front( *itrPropertyToAdd );
	}
}


/**
 * This function adds given properties to all second elements of a list of
 * pairs. Just properties that would not overwritten by the dataproperties
 * will be inserted.
 *
 * @param liData the pair list date to which elements second element the
 * 	properties should be added
 * @param liProperties the properties to add
 * @return the pair list data wher to the elements second element the
 * 	properties wher added
 */
list< pair< cVectorPosition, list< cVectorProperty > > > addPropertiesToAll(
		list< pair< cVectorPosition, list< cVectorProperty > > > liData,
		const list< cVectorProperty > & liProperties ){
	
	list< pair< cVectorPosition, list< cVectorProperty > > >::iterator itrElement;
	for ( itrElement = liData.begin(); itrElement != liData.end(); itrElement++ ){
		//add all properties that dosn't get overwritten
		addPropertiesToPropertyList( itrElement->second, liProperties );
	}
	return liData;
}

/**
 * This function adds given properties to all second elements of a list of
 * pairs. Just properties that would not overwritten by the dataproperties
 * will be inserted.
 *
 * @param liData the pair list date to which elements second element the
 * 	properties should be added
 * @param liProperties the properties to add
 * @return the pair list data wher to the elements second element the
 * 	properties wher added
 */
list< pair< cFibElement*, list< cVectorProperty > > > addPropertiesToAll(
		list< pair< cFibElement*, list< cVectorProperty > > > liData,
		const list< cVectorProperty > & liProperties ){
	
	list< pair< cFibElement*, list< cVectorProperty > > >::iterator itrElement;
	for ( itrElement = liData.begin(); itrElement != liData.end(); itrElement++ ){
		//add all properties that dosn't get overwritten
		addPropertiesToPropertyList( itrElement->second, liProperties );
	}
	return liData;
}


/**
 * This function loads the data of positions with ther properties from
 * the given file.
 *
 * @param szFilename the path of the file, from which the positionsdata
 * 	should be loaded from
 * @return the loaded positionsdata
 */
list< pair< cVectorPosition, list< cVectorProperty > > > loadPositionData(
		const char * szFilename ){
	
	/*every liLoadedData element is created by loading a pointvector and
	then propertyvectors till the next pointvector*/
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
		/*load the vectorlists for liLoadedData*/
		string szElementName = pXmlElement->Value();

		if ( szElementName != "vector" ){
			cerr<<"Error: The name of the datalistelement is "<< szElementName <<" and not \"vector\"."<<endl;
		}
		const char * szVectorXmlType = pXmlElement->Attribute( "type" );
		
		if ( szVectorXmlType == NULL ){
			cerr<<"Error: The vector has no type."<<endl;
		}else if ( string( szVectorXmlType ) == "position" ) {
		
			liLoadedData.push_back( make_pair(
				cVectorPosition( pXmlElement, outStatus, liDefinedVariables ),
				list< cVectorProperty >() ) );
		}else{//propertyvector
			
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


/**
 * This function loads the data of Fib objects with ther properties from
 * the given file.
 * Beware: Don't forget to delete the restored Fib objects.
 *
 * @param szFilename the path of the file, from which the Fib objectdata
 * 	should be loaded from
 * @param liDefinedVariables a list with the pointers to the variables
 * 	defined for the to load Fib objects
 * @return the loaded Fib objectdata
 */
list< pair< cFibElement*, list< cVectorProperty > > > loadElementData(
		const char * szFilename, list<cFibVariable*> liDefinedVariables ){
	
	enumerateVariables( liDefinedVariables );
	
	/*every liLoadedData element is created by loading a Fib object and
	then propertyvectors till the next pointvector*/
	list< pair< cFibElement*, list< cVectorProperty > > > liLoadedData;
	
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
	
	intFib outStatus = 0;
	
	for( ; pXmlElement; pXmlElement = pXmlElement->NextSiblingElement() ){
		/*load the vectorlists for liLoadedData*/
		string szElementName = pXmlElement->Value();

		if ( szElementName != "vector" ){
			//load Fib object
			liLoadedData.push_back( make_pair(
				cFibElement::restoreXml( pXmlElement, outStatus, liDefinedVariables ),
				list< cVectorProperty >() ) );
		}else{//load property vector

			liLoadedData.back().second.push_back(
				cVectorProperty( pXmlElement, outStatus, liDefinedVariables ) );
		}
		if ( outStatus != 0 ){
			cerr<<"Error: While loading a "<< szElementName <<
				" -element. (outStatus="<< outStatus <<" )"<<endl;
			outStatus = 0;
		}
	}
	
	return liLoadedData;
}


/**
 * Enumerates the variables in the given list from 1 to liVariables.size().
 */
void enumerateVariables( list<cFibVariable*> & liVariables ){
	
	unsigned int uiVariableNumber = 1;
	for ( list<cFibVariable*>::iterator
			itrVariable = liVariables.begin();
			itrVariable != liVariables.end();
			itrVariable++, uiVariableNumber++ ){
		
		(*itrVariable)->setIntegerValue( uiVariableNumber );
	}
}














