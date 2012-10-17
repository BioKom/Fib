/**
 * @file tCEvalueUnderObjects
 * file name: tCEvalueUnderObjects.cpp
 * @author Betti Oesterholz
 * @date 11.12.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cEvalueUnderObjects.
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
 * This test is for the class cEvalueUnderObjects.
 *
 *
 *  What's tested of namespace nReduceFibObject:
 * 	- list< pair< cVectorProperty, unsigned long> > countPropertyElementsOverwritebelByBg() const;
 *
 */
/*
History:
11.12.2010  Oesterholz  created
*/


#include "version.h"

#include "cEvalueUnderObjects.h"

#include "cFibElement.h"
#include "cRoot.h"
#include "cPoint.h"
#include "cProperty.h"
#include "cList.h"
#include "cVectorPosition.h"
#include "cVectorProperty.h"
#include "cTypeDimension.h"
#include "cDomains.h"
#include "cDomainVectorBasis.h"

#include "cFolder.h"

#include <utility>
#include <iostream>
#include <fstream>
#include <ostream>

using namespace fib;
using namespace fib::algorithms::nEvalueFibObject::nNeededUnderobjects;
using namespace std;

int testCountPropertyElementsOverwritebelByBg( unsigned long &ulTestphase );

list< pair< cVectorProperty, unsigned long> > loadPropertyCounts( const string & szPathCompareFibObject );

list< string > loadTestFolderList( const string szFilePath );
list< string > loadTestFileList( const string szTestFolderName );


#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif

#ifndef DIR_TESTOBJECTS
	#define DIR_TESTOBJECTS "testObjects/"
#endif
#ifndef FILE_TESTOBJECTS_COUNT_PROPERTY_ELEMENTS_OVERWRITEBEL_BY_BG
	#define FILE_TESTOBJECTS_COUNT_PROPERTY_ELEMENTS_OVERWRITEBEL_BY_BG "testCountPropertyElementsOverwritebelByBg.txt"
#endif

const char * pDirTestObjects = DIR_TESTOBJECTS;


int main(int argc,char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( argc >= 2 ){
		//one parameter given; get parameter max size
		pDirTestObjects = argv[1];
	}

	cout<<endl<<"Running Test for cEvalueUnderObjects functions"<<endl;
	cout<<      "=============================================="<<endl;

	iReturn += testCountPropertyElementsOverwritebelByBg( ulTestphase );

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the countPropertyElementsOverwritebelByBg() function of the
 * cEvalueUnderObjects class.
 *
 * functions tested:
 * 	- list< pair< cVectorProperty, unsigned long> > countPropertyElementsOverwritebelByBg() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCountPropertyElementsOverwritebelByBg( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing function countPropertyElementsOverwritebelByBg()"<<endl;

	//load the testfolder list
	string szFilePath = string( pDirTestObjects ) + FILE_TESTOBJECTS_COUNT_PROPERTY_ELEMENTS_OVERWRITEBEL_BY_BG;
	
	cout<<endl<<"Loading testfolders from the file: "<<szFilePath<<endl;
	list< string > liTestfolders = loadTestFolderList( szFilePath );
	if ( liTestfolders.empty() ){
		cerr<<"Error: No testfolders to test."<<endl;
		iReturn++;
		return iReturn;
	}

	for ( list< string >::iterator itrTestFolder = liTestfolders.begin();
			itrTestFolder != liTestfolders.end(); itrTestFolder++ ){
		
		const string szActualTestFolder = *itrTestFolder;
		ulTestphase++;
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the fib -object in folder \""<< szActualTestFolder <<"\""<<endl;
		
		const string szActualTestPath = string( pDirTestObjects ) +
			szActualTestFolder + "/";
		//load original fib -object
		const string szOriginalFile = szActualTestFolder + ".xml";
		
		const string szPathOriginalFibObject = szActualTestPath + szOriginalFile;
		ifstream inFile( szPathOriginalFibObject.c_str() );
		
		intFib outStatus = 0;
		cFibElement * pOriginalFibObject = cFibElement::restoreXml( inFile , &outStatus );
		
		if ( (outStatus == 0) && (pOriginalFibObject != NULL) ){
			cout<<"Restoring original fib -object in the Xml -format from the file "<<
				szPathOriginalFibObject <<" successfull. "<<endl;
		}else{
			cerr<<"Error: Restoring originalfib -object in the Xml -format from the file "<<
				szPathOriginalFibObject <<" not successfull. (return status="<< outStatus <<")"<<endl;
			iReturn++;
			continue;
		}
			
		//evalue the files in the testfolder
		list< string > liTestFiles = loadTestFileList( szActualTestPath );
		
		for ( list< string >::iterator itrTestFile = liTestFiles.begin();
				itrTestFile != liTestFiles.end(); itrTestFile++ ){
			
			if ( ( itrTestFile->size() <= 11 ) ||
					( itrTestFile->compare ( itrTestFile->size() - 11, 11, "CPOvBBg.xml" ) != 0 ) ){
				//skip non "*CPOvBBg.xml" files
				continue;
			}
			
			cout<<endl<<"Checking result fib -object of countPropertyElementsOverwritebelByBg() in file: "<< (*itrTestFile) <<endl;
			
			//load the fib -object to compare with
			const string szPathCompareFibObject = szActualTestPath + (*itrTestFile);
			
			const list< pair< cVectorProperty, unsigned long> >
				liLoadedPropertyCounts = loadPropertyCounts( szPathCompareFibObject );
			
			//evalue the fib -object
			//evalue the dimensions of the original fib -object
			const cDomains validDomains = pOriginalFibObject->getValidDomains();
			const cDomainVectorBasis * pDomainDimension = (cDomainVectorBasis*)(
				validDomains.getDomainForElement( cTypeDimension() ));
			
			cEvalueUnderObjects evaluedData( pDomainDimension );
			//search for all properties and points and create a data object for them
			evaluedData.findAllFibElementData( *pOriginalFibObject );
			
			/*evalue fib-object:
			- stop at each property remember it and store it later to the position
			- if a point is reached store it to the object for the position on the
				last position, with all underobjects it is contained in and
				all its properties*/
			list<cVectorProperty> liVecProperties;
			list<char> liCFibElementTyps;
			liCFibElementTyps.push_back( 'p' );
			liCFibElementTyps.push_back( 'y' );
			
			const bool bObjectEvalued = pOriginalFibObject->evalueObject(
					evaluedData, 0, liVecProperties, liCFibElementTyps );
			if ( ! bObjectEvalued ){
				cerr<<"Error: The object couldn't be evalued."<<endl;
				iReturn++;
				continue;
			}
			cout<<"evaluedData.markOverwrittenFibElements(); " <<endl;
			evaluedData.markOverwrittenFibElements();
			
			cout<<">>> bUnderobjectRemoved = countPropertyElementsOverwritebelByBg();<<< " <<endl;
			list< pair< cVectorProperty, unsigned long> > liCountedProperties =
				evaluedData.countPropertyElementsOverwritebelByBg();
			
			if ( liCountedProperties == liLoadedPropertyCounts ){
				cout<<"The counts are correct."<<endl;
			}else{
				cerr<<"Error: The counts are not correct."<<endl;
				cerr<<"The evalued counts are:"<<endl;
				iReturn++;
				for ( list< pair< cVectorProperty, unsigned long> >::iterator
						itrCount = liCountedProperties.begin();
						itrCount != liCountedProperties.end(); itrCount++ ){
					
					cout<<"count: "<< itrCount->second<<endl;
					itrCount->first.storeXml( cout );
					cout<<endl;
				}
				cerr<<endl<<"The loaded counts are:"<<endl;
				iReturn++;
				for ( list< pair< cVectorProperty, unsigned long> >::const_iterator
						itrCount = liLoadedPropertyCounts.begin();
						itrCount != liLoadedPropertyCounts.end(); itrCount++ ){
					
					cout<<"count: "<< itrCount->second<<endl;
					itrCount->first.storeXml( cout );
					cout<<endl;
				}
			}
			
		}
		if ( pOriginalFibObject ){
			cFibElement::deleteObject( pOriginalFibObject );
		}
	}

	return iReturn;
}


/**
 * This functions loads the counts for the properties from the given file.
 * The property counts are stored as an fib object. The fib object 
 * countains a list which countains for every count an subobject.
 * Each subobject is an property element which contains an point.
 * The property element vector is the property vector for the count.
 * The fist element of the point vector position is the count value.
 *
 * @param szPathCompareFibObject the file, wher to load the counts from
 * @return the loaded counts
 */
list< pair< cVectorProperty, unsigned long> > loadPropertyCounts(
		const string & szPathCompareFibObject ){
	
	list< pair< cVectorProperty, unsigned long> > liLoadedPropertyCounts;
	
	ifstream inFileCompareFibObject( szPathCompareFibObject.c_str() );
	intFib outStatus = 0;
	cFibElement * pFibObjectLoaded = cFibElement::restoreXml( inFileCompareFibObject , &outStatus );
	
	if ( (outStatus != 0) || (pFibObjectLoaded == NULL) ){
		cerr<<"Error: Restoring result to fib -object in the Xml -format from the file "<<
			szPathCompareFibObject <<" not successfull. (return status="<< outStatus <<")"<<endl;
		if ( pFibObjectLoaded ){
			cFibElement::deleteObject( pFibObjectLoaded );
		}
		return liLoadedPropertyCounts;
	}
	//converting fib object to counts
	cList * pMainList = (cList*)(pFibObjectLoaded->getNextFibElement( 'l' ));
	if ( pMainList == NULL ){
		//no property counts
		cout<<"no property counts"<<endl;
		return liLoadedPropertyCounts;
	}
	
	list< cFibElement * > liCounts = pMainList->getUnderobjects();
	
	for ( list< cFibElement * >::iterator itrCount = liCounts.begin();
			itrCount != liCounts.end(); itrCount++ ){
		//get the property value
		if ( ((*itrCount) == NULL) || ((*itrCount)->getType() != 'y') ){
			cerr<<"No property element for the count"<<endl;
			continue;
		}
		cProperty * pProperty = (cProperty*)(*itrCount);
		if ( pProperty->getProperty() == NULL ){
			cerr<<"No property vector for the count"<<endl;
			continue;
		}
		cVectorProperty vecProperty = *(pProperty->getProperty());
		//get the count value
		cPoint * pPoint = (cPoint*)(pProperty->getNextFibElement( 'p' ));
		if ( (pPoint == NULL) || (pPoint->getPosition() == NULL) ){
			cerr<<"No count (point) element for the count"<<endl;
			continue;
		}
		cVectorPosition * pVecPosition = pPoint->getPosition();
		
		unsigned long ulCount = pVecPosition->getValue( 1 );
		
		liLoadedPropertyCounts.push_back( make_pair( vecProperty, ulCount ) );
	}
	
	if ( pFibObjectLoaded ){
		cFibElement::deleteObject( pFibObjectLoaded );
	}
	return liLoadedPropertyCounts;
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








