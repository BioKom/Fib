/**
 * @file tNReduceFibObject
 * file name: tNReduceFibObject.cpp
 * @author Betti Oesterholz
 * @date 15.06.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the namespace nReduceFibObject.
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
 * This test is for the namespace nReduceFibObject.
 *
 *
 *  What's tested of namespace nReduceFibObject:
 * 	- bool removeOverwrittenUnderObjects( cFibElement & fibElementToReduce );
 * 	- bool removeOverwrittenProperties( cFibElement & fibElementToReduce );
 *
 */
/*
History:
15.06.2010  Oesterholz  created
03.12.2010  Oesterholz  test for removeOverwrittenProperties() added
*/


#include "version.h"

#include "nReduceFibObject.h"

#include "cFibElement.h"
#include "cRoot.h"
#include "cPoint.h"

#include "cFolder.h"

#include <utility>
#include <iostream>
#include <fstream>
#include <ostream>

using namespace fib;
using namespace fib::algorithms::nReduceFibObject;
using namespace std;

int testRemoveOverwrittenUnderObjects( unsigned long &ulTestphase );
int testRemoveOverwrittenProperties( unsigned long &ulTestphase );

list< string > loadTestFolderList( const string szFilePath );
list< string > loadTestFileList( const string szTestFolderName );


#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif

#ifndef DIR_TESTOBJECTS
	#define DIR_TESTOBJECTS "testObjects/"
#endif
#ifndef FILE_TESTOBJECTS_REMOVE_UNDEROBJECTS
	#define FILE_TESTOBJECTS_REMOVE_UNDEROBJECTS "testWithRemoveOverwrittenUnderObjects.txt"
#endif
#ifndef FILE_TESTOBJECTS_REMOVE_PROPERTIES
	#define FILE_TESTOBJECTS_REMOVE_PROPERTIES "testWithRemoveOverwrittenProperties.txt"
#endif

const char * pDirTestObjects = DIR_TESTOBJECTS;


int main(int argc,char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( argc >= 2 ){
		//one parameter given; get parameter max size
		pDirTestObjects = argv[1];
	}

	cout<<endl<<"Running Test for nReduceFibObject functions"<<endl;
	cout<<      "==========================================="<<endl;

	iReturn += testRemoveOverwrittenUnderObjects( ulTestphase );
	iReturn += testRemoveOverwrittenProperties( ulTestphase );

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the removeOverwrittenUnderObjects() function of the
 * nReduceFibObject namespace.
 *
 * functions tested:
 * 	- bool removeOverwrittenUnderObjects( cFibElement & fibElementToReduce );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testRemoveOverwrittenUnderObjects( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing function removeOverwrittenUnderObjects()"<<endl;

	//load the testfolder list
	string szFilePath = string( pDirTestObjects ) + FILE_TESTOBJECTS_REMOVE_UNDEROBJECTS;
	
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
					( itrTestFile->compare ( itrTestFile->size() - 11, 11, "OverwUO.xml" ) != 0 ) ){
				//skip non "*OverwUO.xml" files
				continue;
			}
			
			cout<<endl<<"Checking result fib -object of removeOverwrittenUnderObjects() in file: "<< (*itrTestFile) <<endl;
			
			//load the fib -object to compare with
			const string szPathCompareFibObject = szActualTestPath + (*itrTestFile);
			ifstream inFileCompareFibObject( szPathCompareFibObject.c_str() );
			
			outStatus = 0;
			cFibElement * pFibObjectOverwUO = cFibElement::restoreXml( inFileCompareFibObject , &outStatus );
			
			if ( (outStatus != 0) || (pFibObjectOverwUO == NULL) ){
				cerr<<"Error: Restoring result to fib -object in the Xml -format from the file "<<
					szPathCompareFibObject <<" not successfull. (return status="<< outStatus <<")"<<endl;
				iReturn++;
				if ( pFibObjectOverwUO ){
					cFibElement::deleteObject( pFibObjectOverwUO );
				}
				continue;
			}
			cFibElement * pOriginalFibObjectClone = pOriginalFibObject->clone();
			
			cout<<"bUnderobjectRemoved = removeOverwrittenUnderObjects( * pOriginalFibObject ); " <<endl;
			const bool bUnderobjectRemoved =
				removeOverwrittenUnderObjects( * pOriginalFibObject );
			
			if ( pOriginalFibObjectClone->equal( * pFibObjectOverwUO ) ){
				if ( bUnderobjectRemoved ){
					cerr<<"Error: Ther was an underobject removed, but it shouldn't be."<<endl;
					iReturn++;
				}
			}else{
				if ( ! bUnderobjectRemoved ){
					cerr<<"Error: Ther was not an underobject removed, but it should be."<<endl;
					iReturn++;
				}
			}
			if ( pOriginalFibObject->equal( * pFibObjectOverwUO ) ){
				cout<<"The returned fib -object is correct."<<endl;
			}else{
				cerr<<"Error: The returned fib -object is not correct."<<endl;
				iReturn++;
			
				char szFileNameBuffer[256];
				sprintf ( szFileNameBuffer, "%s%s%s%s", DIR_OUTPUT, itrTestFile->c_str(), "Error" ,".xml" );
				ofstream * pOutFile = new ofstream( szFileNameBuffer );
				cout<<"Storing restored fib -object in the Xml -format to the file "<< szFileNameBuffer <<" . "<<endl;
				pOriginalFibObject->storeXml( *pOutFile );
				delete pOutFile;
			}
			
			if ( pOriginalFibObjectClone != NULL ){
				cFibElement::deleteObject( pOriginalFibObjectClone );
			}
			if ( pFibObjectOverwUO != NULL ){
				cFibElement::deleteObject( pFibObjectOverwUO );
			}
		}
		if ( pOriginalFibObject ){
			cFibElement::deleteObject( pOriginalFibObject );
		}
	}

	return iReturn;
}


/**
 * This method tests the removeOverwrittenProperties() function of the
 * nReduceFibObject namespace.
 *
 * functions tested:
 * 	- bool removeOverwrittenProperties( cFibElement & fibElementToReduce );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testRemoveOverwrittenProperties( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing function removeOverwrittenProperties()"<<endl;

	//load the testfolder list
	string szFilePath = string( pDirTestObjects ) + FILE_TESTOBJECTS_REMOVE_PROPERTIES;
	
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
					( itrTestFile->compare ( itrTestFile->size() - 11, 11, "OverwUO.xml" ) != 0 ) ){
				//skip non "*OverwUO.xml" files
				continue;
			}
			
			cout<<endl<<"Checking result fib -object of removeOverwrittenUnderObjects() in file: "<< (*itrTestFile) <<endl;
			
			//load the fib -object to compare with
			const string szPathCompareFibObject = szActualTestPath + (*itrTestFile);
			ifstream inFileCompareFibObject( szPathCompareFibObject.c_str() );
			
			outStatus = 0;
			cFibElement * pFibObjectOverwUO = cFibElement::restoreXml( inFileCompareFibObject , &outStatus );
			
			if ( (outStatus != 0) || (pFibObjectOverwUO == NULL) ){
				cerr<<"Error: Restoring result to fib -object in the Xml -format from the file "<<
					szPathCompareFibObject <<" not successfull. (return status="<< outStatus <<")"<<endl;
				iReturn++;
				if ( pFibObjectOverwUO ){
					cFibElement::deleteObject( pFibObjectOverwUO );
				}
				continue;
			}
			cFibElement * pOriginalFibObjectClone = pOriginalFibObject->clone();
			
			cout<<"bPropertiesRemoved = removeOverwrittenProperties( * pOriginalFibObject ); " <<endl;
			const bool bPropertiesRemoved =
				removeOverwrittenProperties( * pOriginalFibObject );
			
			if ( pOriginalFibObjectClone->equal( * pFibObjectOverwUO ) ){
				if ( bPropertiesRemoved ){
					cerr<<"Error: Ther was an underobject removed, but it shouldn't be."<<endl;
					iReturn++;
				}
			}else{
				if ( ! bPropertiesRemoved ){
					cerr<<"Error: Ther was not an underobject removed, but it should be."<<endl;
					iReturn++;
				}
			}
			if ( pOriginalFibObject->equal( * pFibObjectOverwUO ) ){
				cout<<"The returned fib -object is correct."<<endl;
			}else{
				cerr<<"Error: The returned fib -object is not correct."<<endl;
				iReturn++;
			
				char szFileNameBuffer[256];
				sprintf ( szFileNameBuffer, "%s%s%s%s", DIR_OUTPUT, itrTestFile->c_str(), "Error" ,".xml" );
				ofstream * pOutFile = new ofstream( szFileNameBuffer );
				cout<<"Storing restored fib -object in the Xml -format to the file "<< szFileNameBuffer <<" . "<<endl;
				pOriginalFibObject->storeXml( *pOutFile );
				delete pOutFile;
			}
			
			if ( pOriginalFibObjectClone != NULL ){
				cFibElement::deleteObject( pOriginalFibObjectClone );
			}
			if ( pFibObjectOverwUO != NULL ){
				cFibElement::deleteObject( pFibObjectOverwUO );
			}
		}
		if ( pOriginalFibObject ){
			cFibElement::deleteObject( pOriginalFibObject );
		}
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








