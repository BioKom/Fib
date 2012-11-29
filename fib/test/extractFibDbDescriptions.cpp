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
 * 			-m: wiki Markdown
 * 	DATABASE_PATH: the path to the Fib database to load
 *
 */
/*
History:
02.12.2011  Oesterholz  created
27.06.2011  Oesterholz  check string length befor checking for "description" ending
29.11.2011  Oesterholz  changes for option "-m": wiki Markdown
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
#include <string>


using namespace fib;
using namespace std;


int extractAllDbObjectsDescriptions( const char cFormat );


/**
 * class for the head lines for the database objects
 */
class cDBHeadline{
public:
	
	/**
	 * The identifier befor which to write the headline.
	 * (Identifiers are positiv absolut values.)
	 */
	unsigned long uiIdentifierBeginArea;
	
	/**
	 * The text of the headline.
	 */
	string szHeadline;
	
	/**
	 * The headline level.
	 * 0 is the top most headline level
	 */
	unsigned int uiHeadlineLevel;
	
	
	/**
	 * parameter constructor
	 */
	cDBHeadline( const unsigned int uiInIdentifierBeginArea,
			const string & szInHeadline,
			const unsigned int uiInHeadlineLevel=0 ):
			uiIdentifierBeginArea( uiInIdentifierBeginArea ),
			szHeadline( szInHeadline ), uiHeadlineLevel( uiInHeadlineLevel ){
		
	}
	
	
	/**
	 * This method compares on lower for this headline.
	 *
	 * @see uiIdentifierBeginArea
	 * @see uiHeadlineLevel
	 * @param otherHeadline the Fib DB headline to compare to
	 * @return true if this headline has a lower uiIdentifierBeginArea than
	 * 	that of otherHeadline, else if the uiIdentifierBeginArea are equal true
	 * 	if the uiHeadlineLevel of this is lower, else false
	 */
	virtual bool operator<( const cDBHeadline & otherHeadline ) const{
		
		if ( uiIdentifierBeginArea == otherHeadline.uiIdentifierBeginArea ){
			
			return uiHeadlineLevel < otherHeadline.uiHeadlineLevel;
		}
		
		return uiIdentifierBeginArea < otherHeadline.uiIdentifierBeginArea;
	}
	
};//end class cDBHeadline


/**
 * The list with the sorted headlines for the data base.
 */
list< cDBHeadline > liHeadlines;


/**
 * This method fills the liHeadlines with the headlines.
 * @see liHeadlines
 */
void createHedlines(){
	
	liHeadlines.push_back( cDBHeadline( 0, "Nothing" ) );
	liHeadlines.push_back( cDBHeadline( 1, "-1 till -9 points (abs( Identifier ) = number of dimensions" ) );
	liHeadlines.push_back( cDBHeadline( 10, "-10 till -19 License" ) );
	liHeadlines.push_back( cDBHeadline( 20, "-20 till -999 2 dimensional objects" ) );
	liHeadlines.push_back( cDBHeadline( 20, "-20 till -29 lines", 1 ) );
	liHeadlines.push_back( cDBHeadline( 30, "-30 till -39 triangles", 1 ) );
	liHeadlines.push_back( cDBHeadline( 40, "-40 till -49 rectangles", 1 ) );
	liHeadlines.push_back( cDBHeadline( 50, "-50 till -59 circles", 1 ) );
	liHeadlines.push_back( cDBHeadline( 60, "-60 till -69 open for futur use", 1 ) );
	liHeadlines.push_back( cDBHeadline( 70, "-70 till -89 tiles", 1 ) );
	liHeadlines.push_back( cDBHeadline( 90, "-90 till -99 functions", 1 ) );
	liHeadlines.push_back( cDBHeadline( 200, "-200 till -299 lines 2", 1 ) );
	liHeadlines.push_back( cDBHeadline( 300, "-300 till -399 triangles 2", 1 ) );
	liHeadlines.push_back( cDBHeadline( 400, "-400 till -499 rectangles 2", 1 ) );
	liHeadlines.push_back( cDBHeadline( 500, "-500 till -599 circles 2", 1 ) );
	liHeadlines.push_back( cDBHeadline( 600, "-600 till -899 open for futur use", 1 ) );
	liHeadlines.push_back( cDBHeadline( 900, "-900 till -999 functions 2", 1 ) );
	liHeadlines.push_back( cDBHeadline( 1000, "-1000 till -1999 algorithms" ) );
	liHeadlines.push_back( cDBHeadline( 2000, "-2000 till -2999 descriptions" ) );
	liHeadlines.push_back( cDBHeadline( 3000, "-3000 till -3999 3 dimensional objects" ) );
	liHeadlines.push_back( cDBHeadline( 4000, "-4000 till -4999 4 dimensional objects" ) );
	liHeadlines.push_back( cDBHeadline( 5000, "-5000 till -5100 stickmans" ) );
	
	liHeadlines.sort();
}



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
	
	createHedlines();
	
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
 * 		-m: wiki Markdown
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
	
	list< cDBHeadline >::const_iterator itrNextHeadline = liHeadlines.begin();
	
	for ( list< longFib >::iterator itrActualIdentifier = liAllDatabaseObjects.begin();
			itrActualIdentifier != liAllDatabaseObjects.end(); itrActualIdentifier++ ){
		
		longFib & lActualIdentifier = (*itrActualIdentifier);
		
		while ( ( itrNextHeadline != liHeadlines.end() ) &&
				( itrNextHeadline->uiIdentifierBeginArea <= (unsigned long)( 0 - lActualIdentifier ) ) ){
			//write next headline
			cout<<endl;
			cout<<endl;
			if ( cFormat == 'm' ){
				//format markdown
				for ( unsigned int uiLevel = 0;
						uiLevel < itrNextHeadline->uiHeadlineLevel; uiLevel++ ){
					cout<<"#";
				}
				cout<<"# "<<itrNextHeadline->szHeadline<<endl;
			}else{//default
				for ( unsigned int uiLevel = 0;
						uiLevel < itrNextHeadline->uiHeadlineLevel; uiLevel++ ){
					cout<<"#";
				}
				cout<<"# "<<itrNextHeadline->szHeadline<<" #";
				for ( unsigned int uiLevel = 0;
						uiLevel < itrNextHeadline->uiHeadlineLevel; uiLevel++ ){
					cout<<"#";
				}
				cout<<endl;
			}
			cout<<endl;
			
			itrNextHeadline++;
		}
		
		
		cRoot * pRootLoaded = pFibDatabase->getFibObject( lActualIdentifier );
		if ( pRootLoaded == NULL ){
			cerr<<"Error: Could not load database object with identifier: "<<lActualIdentifier<<" : "<<endl;
			continue;
		}
		
		if ( cFormat == 'm' ){
			//format markdown
			cout<<"* ";
		}else{//default
			cout<<" - ";
		}
		cout<<lActualIdentifier<<" : ";
		
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
				if ( cFormat == 'm' ){
					//format markdown
					cout<<"   * ";
				}else{//default
					cout<<"    - ";
				}
			}
			
			cout<<szFirstPart<<paEntry.second<<endl;
		}
		
		pFibDatabase->freeFibObject( lActualIdentifier );
	}
	cout<<endl;
	
	return iReturn;
}












