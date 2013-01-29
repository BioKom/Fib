/**
 * @file tFibDatabase
 * file name: tFibDatabase.cpp
 * @author Betti Oesterholz
 * @date 28.11.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cFibDatabase.
 *
 * Copyright (C) @c GPL3 2011 Betti Oesterholz
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
 * This file contains the test for the class cFibDatabase, which
 * represents the Fib database.
 *
 *
 * What's tested of class cFibDatabase:
 * 	- static cFibDatabase * getInstance();
 * 	- std::list< longFib > getAllDatabaseObjectIdentifiers() const;
 * 	- cRoot * getFibObject( const longFib lIdentifer );
 * 	- void loadFibObject( const longFib lIdentifer );
 * 	- void freeFibObject( const longFib lIdentifer );
 * 	- std::map< longFib, cRoot * > getLoadedDatabaseObjects();
 * 	- static std::string getDatabasePath();
 * 	- static bool setDatabasePath( const char * szInDatabasePath );
 * 	- static bool setDatabasePath( const std::string szInDatabasePath );
 * 	- static bool searchForDatabasePath();
 * 	- bool reloadDatabase();
 *
 * call: tFibDatabase [MAX_RAND_TEST_SIZE] [DIR_TEST_DATABASE]
 *
 * parameters:
 * 	MAX_RAND_TEST_SIZE
 * 		A number for the random test sizes.
 * 		Standardvalue is 256.
 * 	DIR_TEST_DATABASE
 * 		The path wher the test datapath could be found. The standardfolder
 * 		is "testObjects/testFibDatabase/".
 *
 */
/*
History:
28.11.2011  Oesterholz  created
24.01.2012  Oesterholz  cExtObject: input values changed to input vector
28.01.2013  Oesterholz  COLOR_SW changed to COLOR_GRAYSCALE
*/

#include "version.h"

#include "cFibDatabase.h"
#include "cPoint.h"
#include "cRoot.h"
#include "cExtObject.h"
#include "cProperty.h"
#include "cEvaluePositionList.h"
#include "cEvalueFibElementList.h"

#include "tinyxml.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>
#include <list>
#include <map>

//TODO weg:
//#include <sys/time.h>
//#include <unistd.h>
#include <utility>
//#include <cmath>

#include "tCompareBits.inc"


using namespace fib;
using namespace std;


int testCreation( unsigned long &ulTestphase );
int testDatabaseObjects( unsigned long &ulTestphase );
int testDatabasePath( unsigned long &ulTestphase );
int testEvalue( unsigned long &ulTestphase );
int testAllDatabaseObjects( unsigned long &ulTestphase );



//the size of the random tests
unsigned long MAX_RAND_TEST_SIZE = 256;

//the path to the test database
const char * pDirTestDatabase = "testObjects/testFibDatabase/";

//the standard database path
const string szStandardDatabasePathEnd("fibDatabase/");


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//return value of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	if ( argc >= 2 ){
		//one parameter given; read parameter iterations
		MAX_RAND_TEST_SIZE = atol( argv[ 1 ] );
		if ( MAX_RAND_TEST_SIZE < 1 ){
			MAX_RAND_TEST_SIZE = 1;
		}
		if ( argc >= 3 ){
			//two parameter given; get parameter for the test database
			pDirTestDatabase = argv[ 2 ];
		}
	}
	
	cout<<endl<<"Running Test for cFibDatabase methods"<<endl;
	cout<<      "====================================="<<endl;

	//database path has to be checked befor an instance of the database was created
	iReturn += testDatabasePath( ulTestphase );
	iReturn += testCreation( ulTestphase );
	iReturn += testDatabaseObjects( ulTestphase );
	iReturn += testEvalue( ulTestphase );
	iReturn += testAllDatabaseObjects( ulTestphase );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}

#ifdef WINDOWS
	#include "Windows.h"
#endif//WINDOWS


/**
 * This function will sleep for the given number of milli seconds.
 *
 * @param ulMilliSecondsToSleep the milliseconds to sleep
 */
void fibMilliSleep( unsigned long ulMilliSecondsToSleep ){

#ifdef WINDOWS
	Sleep( ulMilliSecondsToSleep );
#else//WINDOWS
	struct timespec timeToWait;
	struct timespec remainingTime;
	timeToWait.tv_sec  = 0;
	timeToWait.tv_nsec = ulMilliSecondsToSleep * 1000000L; //1000000L = 1 ms
	nanosleep( &timeToWait, &remainingTime );
#endif//WINDOWS
}



/**
 * This function tests the creation of the cFibDatabase instance.
 *
 * methods tested:
 * 	- static cFibDatabase * getInstance();
 * 	- static std::string getDatabasePath();
 * 	- std::list< longFib > getAllDatabaseObjectIdentifiers() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCreation( unsigned long &ulTestphase ){

	int iReturn = 0;//return value of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the creation of an cFibDatabase instance"<<endl;

	//check the getInstance() methode from cFibDatabase
	cout<<"cFibDatabase * pFibDatabase = cFibDatabase::getInstance();"<<endl;
	cFibDatabase * pFibDatabase = cFibDatabase::getInstance();
	
	if ( pFibDatabase == NULL ){
		cerr<<"Error: The Fib database object was given back."<<endl;
		iReturn++;
		return iReturn;
	}
	
	//check the getDatabasePath() methode from cFibDatabase
	cout<<"std::string szDatabasePath = cFibDatabase::getDatabasePath();"<<endl;
	std::string szDatabasePath = cFibDatabase::getDatabasePath();
	if ( szDatabasePath.compare( szDatabasePath.length() - szStandardDatabasePathEnd.length(),
			szStandardDatabasePathEnd.length(), szStandardDatabasePathEnd ) == 0 ){
	
		cout<<"The database path "<<szDatabasePath<<" is Ok. (it has "<<
			szStandardDatabasePathEnd<<" at its end)"<<endl;
	}else{
		cerr<<"Error: The database path "<<szDatabasePath<<" is not Ok. (it has not "<<
			szStandardDatabasePathEnd<<" at its end)"<<endl;
		iReturn++;
	}
	//check the getDatabasePath() methode from cFibDatabase
	cout<<"szDatabasePath = pFibDatabase->getDatabasePath();"<<endl;
	szDatabasePath = pFibDatabase->getDatabasePath();
	if ( szDatabasePath.compare( szDatabasePath.length() - szStandardDatabasePathEnd.length(),
			szStandardDatabasePathEnd.length(), szStandardDatabasePathEnd ) == 0 ){
	
		cout<<"The database path "<<szDatabasePath<<" is Ok. (it has "<<
			szStandardDatabasePathEnd<<" at its end)"<<endl;
	}else{
		cerr<<"Error: The database path "<<szDatabasePath<<" is not Ok. (it has not "<<
			szStandardDatabasePathEnd<<" at its end)"<<endl;
		iReturn++;
	}

	//check the getAllDatabaseObjectIdentifiers() methode from cFibDatabase
	cout<<"list< longFib > liAllDatabaseObjects = pFibDatabase->getAllDatabaseObjectIdentifiers();"<<endl;
	list< longFib > liAllDatabaseObjects = pFibDatabase->getAllDatabaseObjectIdentifiers();

	if ( ! liAllDatabaseObjects.empty() ){
	
		cout<<"Ther wher correctly database object identifiers given back. "<<endl;
		cout<<"Existing database identifiers: ";
		for ( list< longFib >::const_iterator itrIdentifier = liAllDatabaseObjects.begin();
				itrIdentifier != liAllDatabaseObjects.end(); itrIdentifier++ ){
			
			cout<<(*itrIdentifier)<<"; ";
		}
		cout<<endl;
	}else{
		cerr<<"Error: Ther wher no database object identifiers given back. "<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This function tests the methods for the database objects.
 *
 * methods tested:
 * 	- cRoot * getFibObject( const longFib lIdentifer );
 * 	- void loadFibObject( const longFib lIdentifer );
 * 	- void freeFibObject( const longFib lIdentifer );
 * 	- std::map< longFib, cRoot * > getLoadedDatabaseObjects();
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testDatabaseObjects( unsigned long &ulTestphase ){

	int iReturn = 0;//return value of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the methods for the database objects"<<endl;

	//check the getInstance() methode from cFibDatabase
	cout<<"cFibDatabase * pFibDatabase = cFibDatabase::getInstance();"<<endl;
	cFibDatabase * pFibDatabase = cFibDatabase::getInstance();
	
	if ( pFibDatabase == NULL ){
		cerr<<"Error: The Fib database object was given back."<<endl;
		iReturn++;
		return iReturn;
	}
	//check the getAllDatabaseObjectIdentifiers() methode from cFibDatabase
	cout<<"list< longFib > liAllDatabaseObjects = pFibDatabase->getAllDatabaseObjectIdentifiers();"<<endl;
	list< longFib > liAllDatabaseObjects =
		pFibDatabase->getAllDatabaseObjectIdentifiers();

	if ( ! liAllDatabaseObjects.empty() ){
	
		cout<<"Ther wher correctly database object identifiers given back. "<<endl;
		cout<<"Existing database identifiers: ";
		for ( list< longFib >::const_iterator itrIdentifier = liAllDatabaseObjects.begin();
				itrIdentifier != liAllDatabaseObjects.end(); itrIdentifier++ ){
			
			cout<<(*itrIdentifier)<<"; ";
		}
		cout<<endl;
	}else{
		cerr<<"Error: Ther wher no database object identifiers given back. "<<endl;
		iReturn++;
		return iReturn;//can not run this thest -> abbord it
	}
	
	//check the getLoadedDatabaseObjects() methode from cFibDatabase
	cout<<"map< longFib, cRoot * > mapLoadedDbObjects = pFibDatabase->getLoadedDatabaseObjects();;"<<endl;
	map< longFib, cRoot * > mapLoadedDbObjects =
		pFibDatabase->getLoadedDatabaseObjects();
	if ( mapLoadedDbObjects.empty() ){
	
		cout<<"Ther wher correctly no loaded database object given back. "<<endl;
	}else{
		cerr<<"Error: Ther wher loaded database object identifiers given back. "<<endl;
		cerr<<"Loaded database identifiers: ";
		for ( map< longFib, cRoot * >::const_iterator itrIdentifier = mapLoadedDbObjects.begin();
				itrIdentifier != mapLoadedDbObjects.end(); itrIdentifier++ ){
			
			cout<<itrIdentifier->first<<"; ";
		}
		cerr<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the methods for the database objects with random test"<<endl;

	map< longFib, cRoot * > mapCorrectLoadedDbObjects;
	
	//generate some not existing database objects
	list< longFib > liNotExistingDbObjects;
	const unsigned long ulToGenerateNotExistingDbObjects = 4 +
		( (MAX_RAND_TEST_SIZE < liAllDatabaseObjects.size())?
			MAX_RAND_TEST_SIZE : liAllDatabaseObjects.size() );
	while ( liNotExistingDbObjects.size() < ulToGenerateNotExistingDbObjects ){
		
		long lIdentifier = ((long)(rand() % (256 * 256 * 256))) - (256L * 256L * 128L);
		if ( find( liAllDatabaseObjects.begin(), liAllDatabaseObjects.end(), 
					lIdentifier ) != liAllDatabaseObjects.end() ){
			//database identifier allready exists -> don't add it
			continue;
		}
		if ( find( liNotExistingDbObjects.begin(), liNotExistingDbObjects.end(), 
					lIdentifier ) != liNotExistingDbObjects.end() ){
			//database identifier allready added as not existing -> don't add it again
			continue;
		}
		
		liNotExistingDbObjects.push_back( lIdentifier );
	}
	for ( unsigned long ulIteration = 0; ulIteration < MAX_RAND_TEST_SIZE; 
			ulIteration++ ){
		
		//execute a method
		const unsigned int uiChoosenFunction = rand() % 7;
		
		switch ( uiChoosenFunction ){
			case 0:{//call getFibObject() on existing database object
				cout<<endl<<"Iteration "<<ulIteration<<" : Calling getFibObject() on existing database object"<<endl;
				//choose existing database object
				unsigned long ulChoosenElement = 1 + rand() % liAllDatabaseObjects.size();
				list< longFib >::iterator itrChoosenElement = getListElement(
					liAllDatabaseObjects, ulChoosenElement );
				
				longFib & lIdentifer = (*itrChoosenElement);
				
				cRoot * pRootLoaded =
					pFibDatabase->getFibObject( lIdentifer );
				cout<<"pRootLoaded("<<pRootLoaded<<") = pFibDatabase->getFibObject( "<<lIdentifer<<" )"<<endl;
				
				if ( pRootLoaded == NULL ){
					
					cerr<<"Error: The returned Fib-object is NULL."<<endl;
					iReturn++;
				}
				mapCorrectLoadedDbObjects.insert( make_pair( lIdentifer, pRootLoaded ) );
			};break;
			case 1:{//call loadFibObject() on existing database object
				cout<<endl<<"Iteration "<<ulIteration<<" : Calling getFibObject() on existing database object"<<endl;
				//choose existing database object
				unsigned long ulChoosenElement = 1 + rand() % liAllDatabaseObjects.size();
				list< longFib >::iterator itrChoosenElement = getListElement(
					liAllDatabaseObjects, ulChoosenElement );
				
				longFib & lIdentifer = (*itrChoosenElement);
				
				cout<<"pFibDatabase->loadFibObject( "<<lIdentifer<<" )"<<endl;
				pFibDatabase->loadFibObject( lIdentifer );
				
				time_t startTime = time( NULL );
				while ( true ){
					map< longFib, cRoot * > mapActualLoadedDbObjects =
						pFibDatabase->getLoadedDatabaseObjects();
					
					map< longFib, cRoot * >::iterator itrFoundDbObject =
						mapActualLoadedDbObjects.find( lIdentifer );
					
					if ( itrFoundDbObject != mapActualLoadedDbObjects.end() ){
						//loaded database object found
						mapCorrectLoadedDbObjects.insert( make_pair(
							itrFoundDbObject->first, itrFoundDbObject->second ) );
						if ( itrFoundDbObject->second == NULL ){
							
							cerr<<"Error: The loaded Fib-object is NULL."<<endl;
							iReturn++;
						}
						break;
					}//wait a little bit
					if ( 10 < (time( NULL ) - startTime) ){
						
						cerr<<"Error: Waited more than 10 second for load of the fib object. Abbording "<<endl;
						iReturn++;
						break;
					}
					fibMilliSleep( 1 );
				}
			};break;
			case 2:{//call getFibObject() not existing database object
				cout<<endl<<"Iteration "<<ulIteration<<" : Calling getFibObject() on not existing database object"<<endl;
				//choose existing database object
				unsigned long ulChoosenElement = 1 + rand() % liNotExistingDbObjects.size();
				list< longFib >::iterator itrChoosenElement = getListElement(
					liNotExistingDbObjects, ulChoosenElement );
				
				longFib & lIdentifer = (*itrChoosenElement);
				
				cRoot * pRootLoaded =
					pFibDatabase->getFibObject( lIdentifer );
				cout<<"pRootLoaded("<<pRootLoaded<<") = pFibDatabase->getFibObject( "<<lIdentifer<<" )"<<endl;
				if ( pRootLoaded != NULL ){
					
					cerr<<"Error: The returned Fib-object is not NULL, it is "<<pRootLoaded<<" ."<<endl;
					iReturn++;
				}
			};break;
			case 3:{//call loadFibObject() on not existing database object
				cout<<endl<<"Iteration "<<ulIteration<<" : Calling loadFibObject() on not existing database object"<<endl;
				//choose existing database object
				unsigned long ulChoosenElement = 1 + rand() % liNotExistingDbObjects.size();
				list< longFib >::iterator itrChoosenElement = getListElement(
					liNotExistingDbObjects, ulChoosenElement );
				
				longFib & lIdentifer = (*itrChoosenElement);
				
				cout<<"pFibDatabase->loadFibObject( "<<lIdentifer<<" )"<<endl;
				pFibDatabase->loadFibObject( lIdentifer );
			};break;
			case 4:{//call freeFibObject() on loaded database object
				if ( mapCorrectLoadedDbObjects.empty() ){
					cout<<endl<<"Iteration "<<ulIteration<<" : could not call freeFibObject() because no loaded object"<<endl;
					break;
				}
				cout<<endl<<"Iteration "<<ulIteration<<" : Calling freeFibObject() on loaded database object"<<endl;
				unsigned long ulChoosenElement = rand() % mapCorrectLoadedDbObjects.size();
				map< longFib, cRoot * >::iterator itrLoadedDbObject =
					mapCorrectLoadedDbObjects.begin();
				for ( unsigned long ulActualElement = 0;
						ulActualElement < ulChoosenElement;
						ulActualElement++, itrLoadedDbObject++ ){
					//nothing to do
				}
				
				cout<<"pFibDatabase->freeFibObject( "<<itrLoadedDbObject->first<<" );"<<endl;
				pFibDatabase->freeFibObject( itrLoadedDbObject->first );
				
				mapCorrectLoadedDbObjects.erase( itrLoadedDbObject );
			};break;
			case 5:{//call freeFibObject() on not loaded database object
				set< longFib > setRemainingDbObjects( liAllDatabaseObjects.begin(),
					liAllDatabaseObjects.end() );
				for ( map< longFib, cRoot * >::const_iterator
						itrIdentifier = mapCorrectLoadedDbObjects.begin();
						itrIdentifier != mapCorrectLoadedDbObjects.end(); itrIdentifier++ ){
					
					setRemainingDbObjects.erase( itrIdentifier->first );
				}
				if ( setRemainingDbObjects.empty() ){
					cout<<endl<<"Iteration "<<ulIteration<<" : could not call freeFibObject() because no not loaded object"<<endl;
					break;
				}
				cout<<endl<<"Iteration "<<ulIteration<<" : Calling freeFibObject() on not loaded database object"<<endl;
				unsigned long ulChoosenElement = rand() % setRemainingDbObjects.size();
				set< longFib >::iterator itrNotLoadedDbObject =
					setRemainingDbObjects.begin();
				for ( unsigned long ulActualElement = 0;
						ulActualElement < ulChoosenElement;
						ulActualElement++, itrNotLoadedDbObject++ ){
					//nothing to do
				}
				
				cout<<"pFibDatabase->freeFibObject( "<<(*itrNotLoadedDbObject)<<" );"<<endl;
				pFibDatabase->freeFibObject( *itrNotLoadedDbObject );
			};break;
			case 6:{//call freeFibObject() on not existing database object
				
				if ( liNotExistingDbObjects.empty() ){
					cout<<endl<<"Iteration "<<ulIteration<<" : could not call freeFibObject() because no not existing object"<<endl;
					break;
				}
				cout<<endl<<"Iteration "<<ulIteration<<" : Calling freeFibObject() on not existing database object"<<endl;
				unsigned long ulChoosenElement = 1 + rand() % liNotExistingDbObjects.size();
				list< longFib >::iterator itrChoosenElement = getListElement(
					liNotExistingDbObjects, ulChoosenElement );
				
				cout<<"pFibDatabase->freeFibObject( "<<(*itrChoosenElement)<<" );"<<endl;
				pFibDatabase->freeFibObject( *itrChoosenElement );
			};break;
			default:
				cerr<<"Error: No existing method choosen. "<<endl;
				iReturn++;
			continue;
		}//end switch choose method
		
		//check values
		
		//check the getLoadedDatabaseObjects() methode from cFibDatabase
		map< longFib, cRoot * > mapActualLoadedDbObjects =
			pFibDatabase->getLoadedDatabaseObjects();
		if ( mapCorrectLoadedDbObjects != mapActualLoadedDbObjects ){
		
			cerr<<"Error: The database object identifiers given back are wrong. "<<endl;
			cerr<<"Actual loaded database identifiers: ";
			for ( map< longFib, cRoot * >::const_iterator itrIdentifier = mapLoadedDbObjects.begin();
					itrIdentifier != mapLoadedDbObjects.end(); itrIdentifier++ ){
				
				cout<<itrIdentifier->first<<"; ";
			}
			cerr<<endl;
			cerr<<"Correct loaded database identifiers: ";
			for ( map< longFib, cRoot * >::const_iterator
					itrIdentifier = mapCorrectLoadedDbObjects.begin();
					itrIdentifier != mapCorrectLoadedDbObjects.end(); itrIdentifier++ ){
				
				cout<<itrIdentifier->first<<"; ";
			}
			cerr<<endl;
			iReturn++;
		}
		map< longFib, cRoot * >::const_iterator
			itrCorrectIdentifier = mapCorrectLoadedDbObjects.begin();
		for ( map< longFib, cRoot * >::const_iterator itrIdentifier = mapLoadedDbObjects.begin();
				( itrIdentifier != mapLoadedDbObjects.end() ) &&
				( itrCorrectIdentifier != mapCorrectLoadedDbObjects.end() ); 
				itrIdentifier++, itrCorrectIdentifier++ ){
			
			if ( itrIdentifier->first != itrCorrectIdentifier->first ){
				
				cerr<<"Error: The identifiers of actual and correct loaded "<<
					"database objects are not equal it is "<<
					itrIdentifier->first<<" but should be "<<
					itrCorrectIdentifier->first<<" . "<<endl;
				iReturn++;
			}
			if ( itrIdentifier->second != itrCorrectIdentifier->second ){
				
				cerr<<"Error: The database object for identifier "<<
					itrIdentifier->first<<" is wrong, it is "<<itrIdentifier->second<<
					" but should be "<<itrCorrectIdentifier->second<<" . "<<endl;
				iReturn++;
			}
		}
		//check the getAllDatabaseObjectIdentifiers() methode from cFibDatabase
		list< longFib > liAllDatabaseObjectsActual = pFibDatabase->getAllDatabaseObjectIdentifiers();
		if ( liAllDatabaseObjects != liAllDatabaseObjectsActual ){
		
			cerr<<"Error: The database object identifiers given back changed. "<<endl;
			cerr<<"Actual existing database identifiers: ";
			for ( list< longFib >::const_iterator itrIdentifier = liAllDatabaseObjects.begin();
					itrIdentifier != liAllDatabaseObjects.end(); itrIdentifier++ ){
				
				cout<<(*itrIdentifier)<<"; ";
			}
			cerr<<endl;
			iReturn++;
		}
		
	}//end random test

	return iReturn;
}


/**
 * This function tests the methods for the database objects.
 *
 * methods tested:
 * 	- static std::string getDatabasePath();
 * 	- static bool setDatabasePath( const char * szInDatabasePath );
 * 	- static bool setDatabasePath( const std::string szInDatabasePath );
 * 	- static bool searchForDatabasePath();
 * 	- bool reloadDatabase();
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testDatabasePath( unsigned long &ulTestphase ){

	int iReturn = 0;//return value of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing database path functions"<<endl;
	
	//check the getDatabasePath() methode from cFibDatabase
	cout<<"szDatabasePath = pFibDatabase::getDatabasePath();"<<endl;
	string szDatabasePath = cFibDatabase::getDatabasePath();
	if ( szDatabasePath.empty() ){
	
		cout<<"The database path \""<<szDatabasePath<<"\" is Ok. (ther "<<
			" is no database instance so ther is no automatic path)"<<endl;
	}else{
		cerr<<"Error: The database path \""<<szDatabasePath<<"\" is not Ok. (ther "<<
			" is no database instance so ther should be no automatic path)"<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing setting a not existing database path"<<endl;

	cout<<"bPathSet = cFibDatabase::setDatabasePath( (char*)(\"\") );"<<endl;
	string szDatabasePathToSet( "" );
	bool bPathSet = cFibDatabase::setDatabasePath( szDatabasePathToSet.c_str() );
	if ( ! bPathSet ){
	
		cout<<"The database path \"\" could correctly not set."<<endl;
	}else{
		cerr<<"Error: The database path \"\" could be set."<<endl;
		iReturn++;
	}
	cout<<"szDatabasePath = pFibDatabase::getDatabasePath();"<<endl;
	szDatabasePath = cFibDatabase::getDatabasePath();
	if ( szDatabasePath.empty() ){
	
		cout<<"The database path \""<<szDatabasePath<<"\" is Ok. (ther "<<
			" is no database instance so ther is no automatic path)"<<endl;
	}else{
		cerr<<"Error: The database path \""<<szDatabasePath<<"\" is not Ok. (ther "<<
			" is no database instance so ther should be no automatic path)"<<endl;
		iReturn++;
	}
	
	cout<<"bPathSet = cFibDatabase::setDatabasePath( (char*)(\"x/1234/xx/1234/\") );"<<endl;
	szDatabasePathToSet = "x/1234/xx/1234/";
	bPathSet = cFibDatabase::setDatabasePath( szDatabasePathToSet.c_str() );
	if ( ! bPathSet ){
	
		cout<<"The database path \"\" could correctly not set."<<endl;
	}else{
		cerr<<"Error: The database path \"\" could be set."<<endl;
		iReturn++;
	}
	cout<<"szDatabasePath = pFibDatabase::getDatabasePath();"<<endl;
	szDatabasePath = cFibDatabase::getDatabasePath();
	if ( szDatabasePath.empty() ){
	
		cout<<"The database path \""<<szDatabasePath<<"\" is Ok. (ther "<<
			" is no database instance so ther is no automatic path)"<<endl;
	}else{
		cerr<<"Error: The database path \""<<szDatabasePath<<"\" is not Ok. (ther "<<
			" is no database instance so ther should be no automatic path)"<<endl;
		iReturn++;
	}

	
	cout<<"bPathSet = cFibDatabase::setDatabasePath( string( \"\" ) );"<<endl;
	szDatabasePathToSet = "";
	bPathSet = cFibDatabase::setDatabasePath( szDatabasePathToSet );
	if ( ! bPathSet ){
	
		cout<<"The database path \"\" could correctly not set."<<endl;
	}else{
		cerr<<"Error: The database path \"\" could be set."<<endl;
		iReturn++;
	}
	cout<<"szDatabasePath = pFibDatabase::getDatabasePath();"<<endl;
	szDatabasePath = cFibDatabase::getDatabasePath();
	if ( szDatabasePath.empty() ){
	
		cout<<"The database path \""<<szDatabasePath<<"\" is Ok. (ther "<<
			" is no database instance so ther is no automatic path)"<<endl;
	}else{
		cerr<<"Error: The database path \""<<szDatabasePath<<"\" is not Ok. (ther "<<
			" is no database instance so ther should be no automatic path)"<<endl;
		iReturn++;
	}
	
	cout<<"bPathSet = cFibDatabase::setDatabasePath( string( \"x/1234/xx/1234/\" ) );"<<endl;
	szDatabasePathToSet = string( "x/1234/xx/1234/" );
	bPathSet = cFibDatabase::setDatabasePath( szDatabasePathToSet );
	if ( ! bPathSet ){
	
		cout<<"The database path \"\" could correctly not set."<<endl;
	}else{
		cerr<<"Error: The database path \"\" could be set."<<endl;
		iReturn++;
	}
	cout<<"szDatabasePath = pFibDatabase::getDatabasePath();"<<endl;
	szDatabasePath = cFibDatabase::getDatabasePath();
	if ( szDatabasePath.empty() ){
	
		cout<<"The database path \""<<szDatabasePath<<"\" is Ok. (ther "<<
			" is no database instance so ther is no automatic path)"<<endl;
	}else{
		cerr<<"Error: The database path \""<<szDatabasePath<<"\" is not Ok. (ther "<<
			" is no database instance so ther should be no automatic path)"<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing setting a existing database path"<<endl;

	cout<<"bPathSet = cFibDatabase::setDatabasePath( (char*)(\""<<pDirTestDatabase<<"\") );"<<endl;
	bPathSet = cFibDatabase::setDatabasePath( pDirTestDatabase );
	if ( bPathSet ){
	
		cout<<"The database path \""<<pDirTestDatabase<<"\" could correctly be set."<<endl;
	}else{
		cerr<<"Error: The database path \""<<pDirTestDatabase<<"\" could not be set."<<endl;
		iReturn++;
	}
	//check the getDatabasePath() methode from cFibDatabase
	szDatabasePathToSet = string( pDirTestDatabase );
	cout<<"szDatabasePath = pFibDatabase::getDatabasePath();"<<endl;
	szDatabasePath = cFibDatabase::getDatabasePath();
	if ( szDatabasePath == szDatabasePathToSet ){
	
		cout<<"The database path \")"<<szDatabasePath<<"\") is Ok."<<endl;
	}else{
		cerr<<"Error: The database path "<<szDatabasePath<<" is not Ok. (it is not \""<<
			szDatabasePathToSet<<"\")"<<endl;
		iReturn++;
	}
	
	cout<<"bPathSet = cFibDatabase::searchForDatabasePath();"<<endl;
	bPathSet = cFibDatabase::searchForDatabasePath();
	if ( bPathSet ){
	
		cout<<"The database path \""<<pDirTestDatabase<<"\" could correctly be set."<<endl;
	}else{
		cerr<<"Error: The database path \""<<pDirTestDatabase<<"\" could not be set."<<endl;
		iReturn++;
	}
	//check the getDatabasePath() methode from cFibDatabase
	cout<<"szDatabasePath = pFibDatabase::getDatabasePath();"<<endl;
	szDatabasePath = cFibDatabase::getDatabasePath();
	if ( szDatabasePath.compare( szDatabasePath.length() - szStandardDatabasePathEnd.length(),
			szStandardDatabasePathEnd.length(), szStandardDatabasePathEnd ) == 0 ){
	
		cout<<"The database path \""<<szDatabasePath<<"\" is Ok. (it has \""<<
			szStandardDatabasePathEnd<<"\" at its end)"<<endl;
	}else{
		cerr<<"Error: The database path \""<<szDatabasePath<<"\" is not Ok. (it has not \""<<
			szStandardDatabasePathEnd<<"\" at its end)"<<endl;
		iReturn++;
	}
	
	
	szDatabasePathToSet = string( pDirTestDatabase );
	cout<<"bPathSet = cFibDatabase::setDatabasePath( (string)(\""<<pDirTestDatabase<<"\") );"<<endl;
	bPathSet = cFibDatabase::setDatabasePath( szDatabasePathToSet );
	if ( bPathSet ){
	
		cout<<"The database path \""<<szDatabasePathToSet<<"\" could correctly be set."<<endl;
	}else{
		cerr<<"Error: The database path \""<<szDatabasePathToSet<<"\" could not be set."<<endl;
		iReturn++;
	}
	//check the getDatabasePath() methode from cFibDatabase
	cout<<"szDatabasePath = pFibDatabase::getDatabasePath();"<<endl;
	szDatabasePath = cFibDatabase::getDatabasePath();
	if ( szDatabasePath == szDatabasePathToSet ){
	
		cout<<"The database path \""<<szDatabasePath<<"\" is Ok."<<endl;
	}else{
		cerr<<"Error: The database path "<<szDatabasePath<<" is not Ok. (it is not \""<<
			szDatabasePathToSet<<"\")"<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing function reloadDatabase()"<<endl;
	
	//check the getInstance() methode from cFibDatabase
	cout<<"cFibDatabase * pFibDatabase = cFibDatabase::getInstance();"<<endl;
	cFibDatabase * pFibDatabase = cFibDatabase::getInstance();
	
	if ( pFibDatabase == NULL ){
		cerr<<"Error: The Fib database object was given back."<<endl;
		iReturn++;
		return iReturn;
	}
	//check the getDatabasePath() methode from cFibDatabase
	cout<<"szDatabasePath = pFibDatabase::getDatabasePath();"<<endl;
	szDatabasePath = cFibDatabase::getDatabasePath();
	if ( szDatabasePath == szDatabasePathToSet ){
	
		cout<<"The database path \""<<szDatabasePath<<"\" is Ok."<<endl;
	}else{
		cerr<<"Error: The database path "<<szDatabasePath<<" is not Ok. (it is not \""<<
			szDatabasePathToSet<<"\")"<<endl;
		iReturn++;
	}
	cout<<"pFibDatabase->getFibObject( -1 )"<<endl;
	pFibDatabase->getFibObject( -1 );
	cout<<"pFibDatabase->getFibObject( -2 )"<<endl;
	pFibDatabase->getFibObject( -2 );

	//check the getAllDatabaseObjectIdentifiers() methode from cFibDatabase
	cout<<"list< longFib > liAllDatabaseObjects1 = pFibDatabase->getAllDatabaseObjectIdentifiers();"<<endl;
	list< longFib > liAllDatabaseObjects1 =
		pFibDatabase->getAllDatabaseObjectIdentifiers();
	if ( liAllDatabaseObjects1.size() == 5 ){
	
		cout<<"Ther wher correctly 5 database object identifiers given back. "<<endl;
		cout<<"Database identifiers given back: ";
		for ( list< longFib >::const_iterator itrIdentifier = liAllDatabaseObjects1.begin();
				itrIdentifier != liAllDatabaseObjects1.end(); itrIdentifier++ ){
			
			cout<<(*itrIdentifier)<<"; ";
		}
		cout<<endl;
	}else{
		cerr<<"Error: Ther wher "<<liAllDatabaseObjects1.size()<<" database object identifiers given back. "<<endl;
		cerr<<"Database identifiers given back: ";
		for ( list< longFib >::const_iterator itrIdentifier = liAllDatabaseObjects1.begin();
				itrIdentifier != liAllDatabaseObjects1.end(); itrIdentifier++ ){
			
			cerr<<(*itrIdentifier)<<"; ";
		}
		cerr<<endl;
		iReturn++;
	}
	
	//check the getLoadedDatabaseObjects() methode from cFibDatabase
	cout<<"map< longFib, cRoot * > mapLoadedDbObjects = pFibDatabase->getLoadedDatabaseObjects();;"<<endl;
	map< longFib, cRoot * > mapLoadedDbObjects =
		pFibDatabase->getLoadedDatabaseObjects();
	if ( mapLoadedDbObjects.size() == 2 ){
	
		cout<<"Ther wher correctly two loaded database object given back. "<<endl;
	}else{
		cerr<<"Error: Ther wher "<<mapLoadedDbObjects.size()<<" loaded database object identifiers given back. "<<endl;
		iReturn++;
	}
	
	cout<<"bDatabaseReloaded = pFibDatabase->reloadDatabase();"<<endl;
	bool bDatabaseReloaded = pFibDatabase->reloadDatabase();
	if ( bDatabaseReloaded ){
	
		cout<<"The database could correctly be reloaded."<<endl;
	}else{
		cerr<<"Error: The database could not be reloaded."<<endl;
		iReturn++;
	}
	
	//check the getAllDatabaseObjectIdentifiers() methode from cFibDatabase
	cout<<"list< longFib > liAllDatabaseObjects2 = pFibDatabase->getAllDatabaseObjectIdentifiers();"<<endl;
	list< longFib > liAllDatabaseObjects2 =
		pFibDatabase->getAllDatabaseObjectIdentifiers();
	if ( liAllDatabaseObjects1 == liAllDatabaseObjects2 ){
	
		cout<<"The database object identifiers given back befor and after reload are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The database object identifiers given back befor and after reload are not equal. "<<endl;
		iReturn++;
	}
	//check the getLoadedDatabaseObjects() methode from cFibDatabase
	cout<<"mapLoadedDbObjects = pFibDatabase->getLoadedDatabaseObjects();;"<<endl;
	mapLoadedDbObjects = pFibDatabase->getLoadedDatabaseObjects();
	if ( mapLoadedDbObjects.empty() ){
	
		cout<<"Ther wher correctly no loaded database object given back. "<<endl;
	}else{
		cerr<<"Error: Ther wher loaded database object identifiers given back. "<<endl;
		cerr<<"Loaded database identifiers: ";
		for ( map< longFib, cRoot * >::const_iterator itrIdentifier = mapLoadedDbObjects.begin();
				itrIdentifier != mapLoadedDbObjects.end(); itrIdentifier++ ){
			
			cout<<itrIdentifier->first<<"; ";
		}
		cerr<<endl;
		iReturn++;
	}

	cout<<"bPathSet = cFibDatabase::searchForDatabasePath();"<<endl;
	bPathSet = cFibDatabase::searchForDatabasePath();
	if ( bPathSet ){
	
		cout<<"The database path \""<<pDirTestDatabase<<"\" could correctly be set."<<endl;
	}else{
		cerr<<"Error: The database path \""<<pDirTestDatabase<<"\" could not be set."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This if compares the to given listlists.
 * It ignores the orter of the elements in the lists.
 *
 * @param liEvaluedProperties the first list with the listvectors,
 * 	which are to be compared; this listlist sould be evalued
 * @param liToGiveBackPropertyVectors the second list with the listvectors,
 * 	which are to be compared; this listlist sould be the correct properties
 */
int comparePropertyLists( const list<cVectorProperty> & liEvaluedProperties,
		const list<cVectorProperty> & liToGiveBackPropertyVectors ){
	
	int iReturn = 0;
	
	if ( liEvaluedProperties.size() == liToGiveBackPropertyVectors.size() ){
	
		cout<<"Ther are correctly "<< liEvaluedProperties.size() <<
			" properties given back. "<<endl;
		
		bool bPropertiesCorrect = true;
		unsigned int uiListPosition = 1;
		for ( list<cVectorProperty>::const_iterator itrListVector =
				liToGiveBackPropertyVectors.begin();
				itrListVector != liToGiveBackPropertyVectors.end();
				itrListVector++, uiListPosition++ ){
			
			list<cVectorProperty>::const_iterator itrFoundVector =
				find( liEvaluedProperties.begin(), liEvaluedProperties.end(), *itrListVector );
			
			if ( itrFoundVector == liEvaluedProperties.end() ){
				cerr<<"Error: The "<< uiListPosition <<
					"'th property couldn't be found in the evalued propertylist.  "<<endl;
				iReturn++;
				bPropertiesCorrect = false;
			}
		}
		uiListPosition = 1;
		for ( list<cVectorProperty>::const_iterator itrListVector =
				liEvaluedProperties.begin();
				itrListVector != liEvaluedProperties.end();
				itrListVector++, uiListPosition++ ){
			
			list<cVectorProperty>::const_iterator itrFoundVector =
				find ( liToGiveBackPropertyVectors.begin(), liToGiveBackPropertyVectors.end(),
				*itrListVector );
			
			if ( itrFoundVector == liToGiveBackPropertyVectors.end() ){
				cerr<<"Error: The "<< uiListPosition <<
					"'th property couldn't be found in the to evalue propertylist.  "<<endl;
				iReturn++;
				bPropertiesCorrect = false;
			}
		}
		if ( bPropertiesCorrect ){
			cout<<"All evalued properties are correct. "<<endl;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< liEvaluedProperties.size() <<
			" properties evalued, but it should be "<<
			liToGiveBackPropertyVectors.size() <<".  "<<endl;
		iReturn++;
	}
	return iReturn;
}


/**
 * This if compares the given evalued position lists.
 *
 * @param liEvaluedPositionData the first list with the positions and ther properties,
 * 	which are to be compared; this list sould be evalued
 * @param liToGiveBackPoints the second list with the positions and ther properties,
 * 	which are to be compared; this listlist sould be the correct properties
 */
int compairEvaluedPoints(
		const list< pair< cVectorPosition, list<cVectorProperty> > > & liEvaluedPositionData,
		const list< pair< const cVectorPosition *, list<cVectorProperty> > > & liToGiveBackPoints ){
	
	int iReturn = 0;
	
	if ( liEvaluedPositionData.size() == liToGiveBackPoints.size() ){
	
		cout<<"Ther are correctly "<< liEvaluedPositionData.size() <<
			" points evalued. "<<endl;
		
		unsigned int uiListPosition = 1;
		list< pair< cVectorPosition, list<cVectorProperty> > >::const_iterator
			itrListPair1 = liEvaluedPositionData.begin();
		for ( list< pair< const cVectorPosition *, list<cVectorProperty> > >::const_iterator
				itrListPair2 = liToGiveBackPoints.begin();
				(itrListPair1 != liEvaluedPositionData.end()) &&
				(itrListPair2 != liToGiveBackPoints.end());
				itrListPair1++, itrListPair2++, uiListPosition++ ){
			
			//compair the points
			cout<<"Comparing the "<< uiListPosition <<"'th point:"<<endl;
			if ( (itrListPair1->first) == *(itrListPair2->first) ){
				cout<<"The positions are equal."<<endl;
			}else{
				cerr<<"Error: The positions are not equal."<<endl;
				iReturn++;
			}
			//compair the properties
			iReturn += comparePropertyLists( itrListPair1->second, itrListPair2->second );
		}
	}else{
		cerr<<"Error: Ther wher "<< liEvaluedPositionData.size() <<
			" points evalued, but it should be "<<
			liToGiveBackPoints.size() <<".  "<<endl;
		iReturn++;
	}
	return iReturn;
}


/**
 * This if compares the given evalued Fib-element lists.
 *
 * @param liEvaluedElements the first list with the Fib-elements and ther properties,
 * 	which are to be compared; this list sould be evalued
 * @param liToGiveBackElements the second list with the Fib-elements and ther properties,
 * 	which are to be compared; this listlist sould be the correct properties
 */
int compairEvaluedFibElements(
		const list< pair< cFibElement*, list<cVectorProperty> > > & liEvaluedElements,
		const list< pair< const cFibElement*, list<cVectorProperty> > > & liToGiveBackElements ){
	
	int iReturn = 0;
	
	if ( liEvaluedElements.size() == liToGiveBackElements.size() ){
	
		cout<<"Ther are correctly "<< liEvaluedElements.size() <<
			" points evalued. "<<endl;
		
		unsigned int uiListPosition = 1;
		list< pair< cFibElement*, list<cVectorProperty> > >::const_iterator
			itrListPair1 = liEvaluedElements.begin();
		for ( list< pair< const cFibElement*, list<cVectorProperty> > >::const_iterator
				itrListPair2 = liToGiveBackElements.begin();
				(itrListPair1 != liEvaluedElements.end()) &&
				(itrListPair2 != liToGiveBackElements.end());
				itrListPair1++, itrListPair2++, uiListPosition++ ){
			
			//compair the points
			cout<<"Comparing the "<< uiListPosition <<"'th point:"<<endl;
			if ( (itrListPair1->first) == (itrListPair2->first) ){
				cout<<"The Fib-elements are equal."<<endl;
			}else{
				cerr<<"Error: The Fib-elements are not equal."<<endl;
				iReturn++;
			}
			//compair the properties
			iReturn += comparePropertyLists( itrListPair1->second, itrListPair2->second );
		}
	}else{
		cerr<<"Error: Ther wher "<< liEvaluedElements.size() <<
			" points evalued, but it should be "<<
			liToGiveBackElements.size() <<".  "<<endl;
		iReturn++;
	}
	return iReturn;
}


/**
 * This function tests evaluation of a database object.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testEvalue( unsigned long &ulTestphase ){

	int iReturn = 0;//return value of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing database evaluation"<<endl;
	
	cout<<"cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );"<<endl;
	cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );
	cout<<"vecPropertyColorSW.setValue( 1, 1 );"<<endl;
	vecPropertyColorSW.setValue( 1, 1 );
	
	cout<<"cExtObject extObject1( -2, 2 );"<<endl;
	cExtObject extObject1( -2, 2 );

	cout<<"cProperty property( vecPropertyColorSW, &extObject1 );"<<endl;
	cProperty property( vecPropertyColorSW, &extObject1 );
	
	cout<<"cRoot root( &property );"<<endl;
	cRoot root( &property );
	
	cout<<"root.setNumberOfInputVariables( 3 );"<<endl;
	root.setNumberOfInputVariables( 3 );
	
	cout<<"root.setStandardValueOfInputVariable( 1, 1 );"<<endl;
	root.setStandardValueOfInputVariable( 1, 1 );
	cout<<"root.setStandardValueOfInputVariable( 2, 2 );"<<endl;
	root.setStandardValueOfInputVariable( 2, 2 );
	
	cout<<"extObject1.getInputVector()->setVariable( 1, root.getInputVariable( 1 ) );"<<endl;
	extObject1.getInputVector()->setVariable( 1, root.getInputVariable( 1 ) );
	cout<<"extObject1.getInputVector()->setVariable( 2, root.getInputVariable( 2 ) );"<<endl;
	extObject1.getInputVector()->setVariable( 2, root.getInputVariable( 2 ) );
	
	unsigned int uiPointsToEvalue = 1;
	
	unsigned int uiTimeNeeded = 5 + 3 + 2 + 3;

	//check the getTimeNeed() methode from cExtObject
	cout<<"property.getTimeNeed()"<<endl;
	if ( property.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cExtObject
	cout<<"property.getTimeNeed( 4 )"<<endl;
	if ( property.getTimeNeed( 4 ) == 4 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 4 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property.getTimeNeed( 4 ) <<", but should be "<< 4 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"list<cVectorProperty> liVecProperties;"<<endl;
	list<cVectorProperty> liVecProperties;
	
	//generate to evalue data
	list< pair< const cVectorPosition*, list<cVectorProperty> > > liPointsToEvalue;
	cVectorPosition vecPositionE2V1( 2 );
	vecPositionE2V1.setValue( 1, 1 );
	vecPositionE2V1.setValue( 2, 2 );
	cVectorProperty vecPropertyColorSWV1( cTypeProperty::COLOR_GRAYSCALE );
	vecPropertyColorSWV1.setValue( 1, 1 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V1, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	
	cEvaluePositionList evaluePositionList;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"property.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bool bObjectEvalued = property.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The object was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"property.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = property.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The object was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );
	
	//check the getInstance() methode from cFibDatabase
	cout<<"cFibDatabase * pFibDatabase = cFibDatabase::getInstance();"<<endl;
	cFibDatabase * pFibDatabase = cFibDatabase::getInstance();
	
	if ( pFibDatabase == NULL ){
		cerr<<"Error: The Fib database object was given back."<<endl;
		iReturn++;
		return iReturn;
	}
	
	cRoot * pRootIdm2 = pFibDatabase->getFibObject( -2 );
	cPoint * pPointIdm2 = (cPoint*)(pRootIdm2->getNextFibElement( 'p' ));
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"list<char> liCFibElementTyps;"<<endl;
	list<char> liCFibElementTyps;
	
	cEvalueFibElementList evalueFibElementList;
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	list< pair< const cFibElement*, list<cVectorProperty> > > liFibElementsToEvalue;
	liFibElementsToEvalue.push_back( make_pair( pPointIdm2, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	cout<<"property.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The object was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"property.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = property.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The object was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing database object with a global property list given"<<endl;
	
	cout<<"cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );
	
	list< pair< const cVectorPosition*, list<cVectorProperty> > >::iterator
		itrPositionProperties = liPointsToEvalue.begin();
	itrPositionProperties->second.push_back( vecPropertyLayer );
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"property.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The object was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	list< pair< const cFibElement*, list<cVectorProperty> > >::iterator
		itrElementProperties = liFibElementsToEvalue.begin();
	itrElementProperties->second.push_back( vecPropertyLayer );

	cout<<"property.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The object was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing database object when return value is false"<<endl;

	uiPointsToEvalue = 1;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	cout<<"property.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The object was correctly evalued. with result false "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	liPointsToEvalue.clear();
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 0;
	cout<<"property.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The object was correctly evalued. with result false "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	liFibElementsToEvalue.clear();
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing database object with differnt elements to evalue"<<endl;

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"liCFibElementTyps.push_back( 'y' );"<<endl;
	liCFibElementTyps.push_back( 'y' );
	liVecProperties.clear();
	liFibElementsToEvalue.clear();
	uiPointsToEvalue = 1;
	for ( unsigned int uiEvaluesElement = 0;
			uiEvaluesElement < uiPointsToEvalue; uiEvaluesElement++ ){
		liFibElementsToEvalue.push_back(
			make_pair( &property, list<cVectorProperty>() ) );
	}
	cout<<"property.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The object was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	cout<<"liCFibElementTyps.push_back( 'o' );"<<endl;
	liCFibElementTyps.push_back( 'o' );
	uiPointsToEvalue = 1;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &extObject1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	
	cout<<"property.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The object was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );
	
	liVecProperties.clear();
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	cout<<"liCFibElementTyps.push_back( 'r' );"<<endl;
	liCFibElementTyps.push_back( 'r' );
	cout<<"liCFibElementTyps.push_back( 'o' );"<<endl;
	liCFibElementTyps.push_back( 'o' );
	cout<<"liCFibElementTyps.push_back( 'm' );"<<endl;
	liCFibElementTyps.push_back( 'm' );
	uiPointsToEvalue = 1;
	cout<<"property.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The object was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	
	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing database evaluation for different database object"<<endl;
	
	cout<<"extObject1.setIdentifier( -3 );"<<endl;
	extObject1.setIdentifier( -3 );
	
	cout<<"root.setStandardValueOfInputVariable( 3, 3 );"<<endl;
	root.setStandardValueOfInputVariable( 3, 3 );
	
	cout<<"extObject1.setNumberOfInputValues( 3 );"<<endl;
	extObject1.setNumberOfInputValues( 3 );
	cout<<"extObject1.getInputVector()->setVariable( 3, root.getInputVariable( 3 ) );"<<endl;
	extObject1.getInputVector()->setVariable( 3, root.getInputVariable( 3 ) );
	
	uiPointsToEvalue = 1;
	
	uiTimeNeeded = 5 + 3 + 2 + 4;

	//check the getTimeNeed() methode from cExtObject
	cout<<"property.getTimeNeed()"<<endl;
	if ( property.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cExtObject
	cout<<"property.getTimeNeed( 4 )"<<endl;
	if ( property.getTimeNeed( 4 ) == 4 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 4 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property.getTimeNeed( 4 ) <<", but should be "<< 4 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"liVecProperties.clear();;"<<endl;
	liVecProperties.clear();
	
	//generate to evalue data
	liPointsToEvalue.clear();
	cVectorPosition vecPositionE3( 3 );
	vecPositionE3.setValue( 1, 1 );
	vecPositionE3.setValue( 2, 2 );
	vecPositionE3.setValue( 3, 3 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE3, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"property.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The object was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"property.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = property.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The object was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );
	
	cRoot * pRootIdm3 = pFibDatabase->getFibObject( -3 );
	cPoint * pPointIdm3 = (cPoint*)(pRootIdm3->getNextFibElement( 'p' ));
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( pPointIdm3, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	cout<<"property.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The object was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"property.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = property.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The object was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	return iReturn;
}








/**
 * This function tests loading all database objects an checking them.
 *
 * methods tested:
 * 	- std::list< longFib > getAllDatabaseObjectIdentifiers() const;
 * 	- cRoot * getFibObject( const longFib lIdentifer );
 * 	- void loadFibObject( const longFib lIdentifer );
 * 	- void freeFibObject( const longFib lIdentifer );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testAllDatabaseObjects( unsigned long &ulTestphase ){

	int iReturn = 0;//return value of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing loading all database objects"<<endl;

	//check the getInstance() methode from cFibDatabase
	cout<<"cFibDatabase * pFibDatabase = cFibDatabase::getInstance();"<<endl;
	cFibDatabase * pFibDatabase = cFibDatabase::getInstance();
	
	if ( pFibDatabase == NULL ){
		cerr<<"Error: The Fib database object was given back."<<endl;
		iReturn++;
		return iReturn;
	}
	//check the getAllDatabaseObjectIdentifiers() methode from cFibDatabase
	cout<<"list< longFib > liAllDatabaseObjects = pFibDatabase->getAllDatabaseObjectIdentifiers();"<<endl;
	list< longFib > liAllDatabaseObjects =
		pFibDatabase->getAllDatabaseObjectIdentifiers();

	if ( ! liAllDatabaseObjects.empty() ){
	
		cout<<"Ther wher correctly database object identifiers given back. "<<endl;
		cout<<"Existing database identifiers: ";
		for ( list< longFib >::const_iterator itrIdentifier = liAllDatabaseObjects.begin();
				itrIdentifier != liAllDatabaseObjects.end(); itrIdentifier++ ){
			
			cout<<(*itrIdentifier)<<"; ";
		}
		cout<<endl;
	}else{
		cerr<<"Error: Ther wher no database object identifiers given back. "<<endl;
		iReturn++;
		return iReturn;//can not run this thest -> abbord it
	}

	bool bNewTextBeginning = true;
	for ( list< longFib >::iterator itrActualIdentifier = liAllDatabaseObjects.begin();
			itrActualIdentifier != liAllDatabaseObjects.end(); itrActualIdentifier++ ){
		
		longFib & lActualIdentifier = (*itrActualIdentifier);
		if ( bNewTextBeginning ){
			cout<<"Loading and checking database object: ";
			bNewTextBeginning = false;
		}
		cout<<lActualIdentifier<<"; ";
		if ( 0 < lActualIdentifier ){
			cerr<<endl<<"Error: The identifier "<<lActualIdentifier<<" is positiv. "<<
				"(database identifier should be negative) "<<endl;
			iReturn++;
		}
		cRoot * pRootLoaded = pFibDatabase->getFibObject( lActualIdentifier );
		if ( pRootLoaded == NULL ){
			
			cerr<<endl<<"Error: The returned Fib-object is NULL."<<endl;
			iReturn++;
			bNewTextBeginning = true;
			continue;
		}
		if ( pRootLoaded->getNumberOfElements() == 0 ){
			
			cerr<<endl<<"Error: No Fib elements in loaded Fib object."<<endl;
			iReturn++;
			bNewTextBeginning = true;
		}
		if ( pRootLoaded->getCompressedSize() == 0 ){
			
			cerr<<endl<<"Error: Fib object has compressed size 0."<<endl;
			iReturn++;
			bNewTextBeginning = true;
		}
		if ( ! pRootLoaded->hasUnderAllObjects() ){
			
			cerr<<endl<<"Error: Fib object has not all underobjects."<<endl;
			iReturn++;
			bNewTextBeginning = true;
		}
		pFibDatabase->freeFibObject( lActualIdentifier );
	}
	cout<<endl;
	
	return iReturn;
}






