/**
 * @file extractFibDbDescriptions
 * file name: extractFibDbDescriptions.cpp
 * @author Betti Oesterholz
 * @date 28.11.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This programm extracts all descriptions of Fib Database objects.
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
 * This programm extracts all descriptions of Fib Database objects.
 *
 *
 * call: extractFibDbDescriptions [FORMAT] [DATABASE_PATH]
 *
 * parameters:
 * 	FORMAT
 * 		The format in which the extracted descriptions should be printed.
 * 		possible formats are:
 * 			-n: normal
 * 	DATABASE_PATH: the path to the Fib database to load
 *
 */
/*
History:
02.12.2011  Oesterholz  created
27.06.2011  Oesterholz  check string length befor checking for "description" ending
*/

#include "version.h"

#include "cFibDatabase.h"
#include "cRoot.h"
#include "cOptionalPart.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>
#include <list>
#include <map>


using namespace fib;
using namespace std;


int extractAllDbObjectsDescriptions( const char cFormat );


int main(int argc, char* argv[]){

	int iReturn = 0;//return value of the test; the number of occured Errors
	
	cout<<endl<<"Extract all descriptions of Fib Database objects"<<endl;
	cout<<      "================================================"<<endl<<endl;

	/*the type for the output format:
	 * 	-n: normal
	 */
	char cFormat = 'n';
	
	if ( argc >= 2 ){
		//one parameter given; read parameter for the output format
		cFormat = argv[ 1 ][ 1 ];
		if ( argc >= 3 ){
			//two parameter given; get parameter for the database path
			cout<<"Setting Database path: "<<argv[ 2 ]<<" "<<endl;
			const bool bPathSet = cFibDatabase::setDatabasePath( argv[ 2 ] );
			if ( ! bPathSet ){
				cerr<<"Error: Could not set database path."<<endl;
			}
		}
	}

	//database path has to be checked befor an instance of the database was created
	iReturn += extractAllDbObjectsDescriptions( cFormat );


	if ( iReturn != 0 ){
		cerr<<endl<<endl<<"Extraction failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * This function extracts all descriptions of Fib Database objects.
 *
 * @param cFormat The format in which the extracted descriptions should be printed.
 * 	possible formats are:
 * 		-n: normal
 * @return the number of erros occured in the test
 */
int extractAllDbObjectsDescriptions( const char cFormat ){

	int iReturn = 0;//return value of the test; the number of occured Errors

	//check the getInstance() methode from cFibDatabase
	cFibDatabase * pFibDatabase = cFibDatabase::getInstance();
	
	if ( pFibDatabase == NULL ){
		cerr<<"Error: The Fib database object was given back."<<endl;
		iReturn++;
		return iReturn;
	}
	//check the getAllDatabaseObjectIdentifiers() methode from cFibDatabase
	list< longFib > liAllDatabaseObjects =
		pFibDatabase->getAllDatabaseObjectIdentifiers();
	
	liAllDatabaseObjects.sort();
	liAllDatabaseObjects.reverse();

	for ( list< longFib >::iterator itrActualIdentifier = liAllDatabaseObjects.begin();
			itrActualIdentifier != liAllDatabaseObjects.end(); itrActualIdentifier++ ){
		
		longFib & lActualIdentifier = (*itrActualIdentifier);

		cRoot * pRootLoaded = pFibDatabase->getFibObject( lActualIdentifier );
		if ( pRootLoaded == NULL ){
			cerr<<"Error: Could not load database object with identifier: "<<lActualIdentifier<<" : "<<endl;
			continue;
		}
		
		cout<<" - "<<lActualIdentifier<<" : ";
		
		//write the optional part information
		cOptionalPart * pOptionalPart = pRootLoaded->getOptionalPart();
		
		if ( pOptionalPart == NULL ){
			cout<<"no information"<<endl;
			pFibDatabase->freeFibObject( lActualIdentifier );
			continue;
		}
		
		const unsignedLongFib uiNumberOfEntries = pOptionalPart->getNumberOfEntries();
		if ( uiNumberOfEntries == 0 ){
			cout<<"no information"<<endl;
		}
		for ( unsignedLongFib uiActualEntry = 1;
				uiActualEntry <= uiNumberOfEntries; uiActualEntry++ ){
			
			const pair< string, string > paEntry =
				pOptionalPart->getEntry( uiActualEntry );
			
			const string & szKey = paEntry.first;
			string szFirstPart = szKey;
			
			if ( szKey == "name" ){
				szFirstPart = "";
			}else if ( ( 13 < szKey.length() ) &&
					( szKey.compare( szKey.length() - 13, 13, "::description" ) == 0 ) ){
				
				szFirstPart.resize( szFirstPart.length() - 13 );
				szFirstPart.append(" : ");
			}else{
				szFirstPart.append(" : ");
			}
			
			if ( uiActualEntry != 1 ){
				cout<<"    - ";
			}
			
			cout<<szFirstPart<<paEntry.second<<endl;
		}
		
		pFibDatabase->freeFibObject( lActualIdentifier );
	}
	cout<<endl;
	
	return iReturn;
}












