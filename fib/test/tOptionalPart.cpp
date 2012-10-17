/**
 * @file tOptionalPart
 * file name: tOptionalPart.cpp
 * @author Betti Oesterholz
 * @date 01.07.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cOptionalPart.
 *
 * Copyright (C) @c GPL3 2009 Betti Oesterholz
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
 * This file contains the test for the class cOptionalPart, which
 * represents the optionalpart for an root -element.
 *
 *
 *
 * What's tested of class cOptionalPart:
 * 	- cOptionalPart();
 * 	- cOptionalPart *clone() const;
 * 	- unsignedLongFib getNumberOfEntries() const;
 * 	- pair< string, string > getEntry( unsignedLongFib ulEntryNumber ) const;
 * 	- list< pair<string,string> > getEntries( string szKey, bool bFullBegin=true ) const;
 * 	- list< pair<string,string> > findKeyPart( string szKeyPart ) const;
 * 	- unsignedLongFib addEntry( string szKey, string szValue, unsignedLongFib ulPosition=0 );
 * 	- bool deleteEntry( unsignedLongFib ulEntryNumber );
 * 	- unsignedLongFib deleteEntries( string szKey, bool bFullBegin=true );
 * 	- bool equal( const cOptionalPart &optionalPart ) const;
 * 	- bool operator==( const cOptionalPart &optionalPart ) const;
 * 	- bool storeXml( ostream & ostream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream & stream ) const;
 * 	- intFib restore( cReadBits & iBitStream, const unsigned long ulBytsToRead = 0 );
 * 	- bool setCompressionType( unsignedIntFib uiInCompressionType = 1 );
 *
 */
/*
History:
01.07.2009  Oesterholz  created
16.11.2009  Oesterholz  equal comparrissons and storeXml() tested
15.07.2011  Oesterholz  methods for compressed storing tested (@see testStore() )
*/

#include "version.h"

#include "cOptionalPart.h"
#include "cReadBits.h"

#include "tinyxml.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif

using namespace fib;
using namespace std;

ostream& operator<<( ostream &ostream, const pair< string ,string > &stringPair );

int testGetAddEntry( unsigned long &ulTestphase );
int testGetEntries( unsigned long &ulTestphase );
int testFindKeyPart( unsigned long &ulTestphase );
int testDeleteEntry( unsigned long &ulTestphase );
int testDeleteEntries( unsigned long &ulTestphase );
int testClone( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );



/**
 * A vector with strings, to choose random from.
 * @see tGeneratorForFibObjects
 */
extern vector< string > vecRandStrings;

/**
 * This function will fill the vector @see vecRandStrings with strings,
 * to choose random from.
 * @see tGeneratorForFibObjects
 */
extern void initVecRandStrings();


//the size of the random tests
unsigned long MAX_RAND_TEST_SIZE = 256;


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	if ( argc >= 2 ){
		//one parameter given; read parameter iterations
		MAX_RAND_TEST_SIZE = atol( argv[1] );
		if ( MAX_RAND_TEST_SIZE < 1 ){
			MAX_RAND_TEST_SIZE = 1;
		}
	}
	initVecRandStrings();
	
	cout<<endl<<"Running Test for cOptionalPart methods"<<endl;
	cout<<      "======================================"<<endl;

	iReturn += testGetAddEntry( ulTestphase );
	iReturn += testGetEntries( ulTestphase );
	iReturn += testFindKeyPart( ulTestphase );
	iReturn += testDeleteEntry( ulTestphase );
	iReturn += testDeleteEntries( ulTestphase );
	iReturn += testClone( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the getNumberOfEntries(), getEntry() and addEntry()
 * methods of the cOptionalPart class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testGetAddEntry( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cOptionalPart"<<endl;


	cOptionalPart optionalpartTest1=cOptionalPart();

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==0 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			0<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 0."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 0 )==pair< string ,string >("","") ){
	
		cout<<"The 0'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 0'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 0 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 1 )==pair< string ,string >("","") ){
	
		cout<<"The 1'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the addEntry() and getEntry() methods, with adding a entry"<<endl;

	cout<<"optionalpartTest1.addEntry( \"test1\", \"wert1\" ) "<<endl;
	unsignedLongFib addPosition=optionalpartTest1.addEntry( "test1", "wert1" );

	//check the addEntry() methode from cOptionalPart
	if ( addPosition==1 ){
	
		cout<<"The entry was correctly added on the position 1. "<<endl;
	}else{
		cerr<<"Error: The entry was correctly added on the position "<<
			addPosition<<" but should be added on position 1."<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==1 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			1<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 1."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 0 )==pair< string ,string >("","") ){
	
		cout<<"The 0'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 0'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 0 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 1 )==pair< string ,string >("test1", "wert1") ){
	
		cout<<"The 1'th entry is correctly the pair "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 2 )==pair< string ,string >("","") ){
	
		cout<<"The 2'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : adding a second entry"<<endl;

	cout<<"optionalpartTest1.addEntry( \"test2\", \"wert2\" ) "<<endl;
	addPosition=optionalpartTest1.addEntry( "test2", "wert2" );

	//check the addEntry() methode from cOptionalPart
	if ( addPosition==2 ){
	
		cout<<"The entry was correctly added on the position 2. "<<endl;
	}else{
		cerr<<"Error: The entry was correctly added on the position "<<
			addPosition<<" but should be added on position 2."<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==2 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			2<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 2."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 0 )==pair< string ,string >("","") ){
	
		cout<<"The 0'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 0'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 0 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 1 )==pair< string ,string >("test1", "wert1") ){
	
		cout<<"The 1'th entry is correctly the pair "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 2 )==pair< string ,string >("test2", "wert2") ){
	
		cout<<"The 2'th entry is correctly the pair "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 3 )==pair< string ,string >("","") ){
	
		cout<<"The 3'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : adding a third entry to end of list"<<endl;

	cout<<"optionalpartTest1.addEntry( \"test3\", \"wert3\", 7 ) "<<endl;
	addPosition=optionalpartTest1.addEntry( "test3", "wert3", 7 );

	//check the addEntry() methode from cOptionalPart
	if ( addPosition==3 ){
	
		cout<<"The entry was correctly added on the position 3. "<<endl;
	}else{
		cerr<<"Error: The entry was correctly added on the position "<<
			addPosition<<" but should be added on position 3."<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==3 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			3<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 3."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 0 )==pair< string ,string >("","") ){
	
		cout<<"The 0'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 0'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 0 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 1 )==pair< string ,string >("test1", "wert1") ){
	
		cout<<"The 1'th entry is correctly the pair "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 2 )==pair< string ,string >("test2", "wert2") ){
	
		cout<<"The 2'th entry is correctly the pair "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 3 )==pair< string ,string >("test3", "wert3") ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 4 )==pair< string ,string >("","") ){
	
		cout<<"The 4'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 4 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : adding a 4'th entry to position 3 of the list"<<endl;

	cout<<"optionalpartTest1.addEntry( \"test4\", \"wert4\", 3 ) "<<endl;
	addPosition=optionalpartTest1.addEntry( "test4", "wert4", 3 );

	//check the addEntry() methode from cOptionalPart
	if ( addPosition==3 ){
	
		cout<<"The entry was correctly added on the position 3. "<<endl;
	}else{
		cerr<<"Error: The entry was correctly added on the position "<<
			addPosition<<" but should be added on position 3."<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==4 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			4<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 4."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 0 )==pair< string ,string >("","") ){
	
		cout<<"The 0'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 0'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 0 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 1 )==pair< string ,string >("test1", "wert1") ){
	
		cout<<"The 1'th entry is correctly the pair "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 2 )==pair< string ,string >("test2", "wert2") ){
	
		cout<<"The 2'th entry is correctly the pair "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 3 )==pair< string ,string >("test4", "wert4") ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			pair< string ,string >("test4", "wert4")<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should "<<
			pair< string ,string >("test4", "wert4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 4 )==pair< string ,string >("test3", "wert3") ){
	
		cout<<"The 4'th entry is correctly the pair "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 4 )<<" but should "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 5 )==pair< string ,string >("","") ){
	
		cout<<"The 5'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 5'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 5 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : adding a 5'th entry with a allready existing key to the end of the list"<<endl;

	cout<<"optionalpartTest1.addEntry( \"test4\", \"wert2.4\", 7 ) "<<endl;
	addPosition=optionalpartTest1.addEntry( "test4", "wert2.4", 7 );

	//check the addEntry() methode from cOptionalPart
	if ( addPosition==5 ){
	
		cout<<"The entry was correctly added on the position 5. "<<endl;
	}else{
		cerr<<"Error: The entry was correctly added on the position "<<
			addPosition<<" but should be added on position 5."<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==5 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			5<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 5."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 0 )==pair< string ,string >("","") ){
	
		cout<<"The 0'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 0'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 0 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 1 )==pair< string ,string >("test1", "wert1") ){
	
		cout<<"The 1'th entry is correctly the pair "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 2 )==pair< string ,string >("test2", "wert2") ){
	
		cout<<"The 2'th entry is correctly the pair "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 3 )==pair< string ,string >("test4", "wert4") ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			pair< string ,string >("test4", "wert4")<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should "<<
			pair< string ,string >("test4", "wert4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 4 )==pair< string ,string >("test3", "wert3") ){
	
		cout<<"The 4'th entry is correctly the pair "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 4 )<<" but should "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 5 )==pair< string ,string >("test4", "wert2.4") ){
	
		cout<<"The 5'th entry is correctly the pair "<<
			pair< string ,string >("test4", "wert2.4")<<"."<<endl;
	}else{
		cerr<<"Error: The 5'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 5 )<<" but should "<<
			pair< string ,string >("test4", "wert2.4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 6 )==pair< string ,string >("","") ){
	
		cout<<"The 6'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 6'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 6 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : adding a 6'th entry with a allready existing value to the end of the list"<<endl;

	cout<<"optionalpartTest1.addEntry( \"test4.2\", \"wert4\", 7 ) "<<endl;
	addPosition=optionalpartTest1.addEntry( "test4.2", "wert4", 7 );

	//check the addEntry() methode from cOptionalPart
	if ( addPosition==6 ){
	
		cout<<"The entry was correctly added on the position 6. "<<endl;
	}else{
		cerr<<"Error: The entry was correctly added on the position "<<
			addPosition<<" but should be added on position 6."<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==6 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			6<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 6."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 0 )==pair< string ,string >("","") ){
	
		cout<<"The 0'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 0'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 0 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 1 )==pair< string ,string >("test1", "wert1") ){
	
		cout<<"The 1'th entry is correctly the pair "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 2 )==pair< string ,string >("test2", "wert2") ){
	
		cout<<"The 2'th entry is correctly the pair "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 3 )==pair< string ,string >("test4", "wert4") ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			pair< string ,string >("test4", "wert4")<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should "<<
			pair< string ,string >("test4", "wert4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 4 )==pair< string ,string >("test3", "wert3") ){
	
		cout<<"The 4'th entry is correctly the pair "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 4 )<<" but should "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 5 )==pair< string ,string >("test4", "wert2.4") ){
	
		cout<<"The 5'th entry is correctly the pair "<<
			pair< string ,string >("test4", "wert2.4")<<"."<<endl;
	}else{
		cerr<<"Error: The 5'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 5 )<<" but should "<<
			pair< string ,string >("test4", "wert2.4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 6 )==pair< string ,string >("test4.2", "wert4") ){
	
		cout<<"The 6'th entry is correctly the pair "<<
			pair< string ,string >("test4.2", "wert4")<<"."<<endl;
	}else{
		cerr<<"Error: The 6'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 6 )<<" but should "<<
			pair< string ,string >("test4.2", "wert4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 7 )==pair< string ,string >("","") ){
	
		cout<<"The 7'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 7'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 7 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the getEntries() methods of the cOptionalPart class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testGetEntries( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getEntries() method, searching for the full key \"test3\""<<endl;

	//making new cOptionalPart object with entries
	cout<<"cOptionalPart optionalpartTest1=cOptionalPart() "<<endl;
	cOptionalPart optionalpartTest1=cOptionalPart();
	cout<<"optionalpartTest1.addEntry( \"test2\", \"wert2\", 1 ) "<<endl;
	optionalpartTest1.addEntry( "test2", "wert2", 1 );
	cout<<"optionalpartTest1.addEntry( \"test1\", \"wert1\", 2 ) "<<endl;
	optionalpartTest1.addEntry( "test1", "wert1", 2 );
	cout<<"optionalpartTest1.addEntry( \"test4\", \"wert4\", 3 ) "<<endl;
	optionalpartTest1.addEntry( "test4", "wert4", 3 );
	cout<<"optionalpartTest1.addEntry( \"test3\", \"wert3\", 4 ) "<<endl;
	optionalpartTest1.addEntry( "test3", "wert3", 4 );
	cout<<"optionalpartTest1.addEntry( \"test4\", \"wert2.4\", 5 ) "<<endl;
	optionalpartTest1.addEntry( "test4", "wert2.4", 5 );
	cout<<"optionalpartTest1.addEntry( \"test4.2\", \"wert4\", 6 ) "<<endl;
	optionalpartTest1.addEntry( "test4.2", "wert4", 6 );


	cout<<"optionalpartTest1.getEntries(\"test3\") "<<endl;
	list< pair< string ,string > > foundedEntries=
		optionalpartTest1.getEntries("test3");

	cout<<"Founded entries: ";
	for (list< pair< string ,string > >::iterator itrEntry=foundedEntries.begin();
		itrEntry!=foundedEntries.end(); itrEntry++){
		cout<<(*itrEntry)<<"; ";
	}
	cout<<endl;

	//check if one entry was found
	if ( foundedEntries.size()==1 ){
	
		cout<<"Ther was correctly one entry found."<<endl;
	}else{
		cerr<<"Error: Ther wher not one entry found but "<<
			foundedEntries.size()<<"."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	list< pair< string ,string > >::iterator entryFound;
	
	entryFound=find( foundedEntries.begin(), foundedEntries.end(),
		pair< string ,string >("test3", "wert3") );
	
	if ( entryFound!=foundedEntries.end() ){
	
		cout<<"The entry "<<pair< string ,string >("test3", "wert3")<<
			" was correctly found."<<endl;
	}else{
		cerr<<"Error: The entry "<<pair< string ,string >("test3", "wert3")
			<<" could not be found."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : searching for the full key \"test99\""<<endl;
	
	cout<<"optionalpartTest1.getEntries(\"test99\") "<<endl;
	foundedEntries=
		optionalpartTest1.getEntries("test99");

	cout<<"Founded entries: ";
	for (list< pair< string ,string > >::iterator itrEntry=foundedEntries.begin();
		itrEntry!=foundedEntries.end(); itrEntry++){
		cout<<(*itrEntry)<<"; ";
	}
	cout<<endl;

	//check if one entry was found
	if ( foundedEntries.size()==0 ){
	
		cout<<"Ther was correctly no entries found."<<endl;
	}else{
		cerr<<"Error: Ther wher entries found but "<<
			foundedEntries.size()<<"."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : searching for the full key \"test\""<<endl;
	
	cout<<"optionalpartTest1.getEntries(\"test\") "<<endl;
	foundedEntries=
		optionalpartTest1.getEntries("test");

	cout<<"Founded entries: ";
	for (list< pair< string ,string > >::iterator itrEntry=foundedEntries.begin();
		itrEntry!=foundedEntries.end(); itrEntry++){
		cout<<(*itrEntry)<<"; ";
	}
	cout<<endl;

	//check if one entry was found
	if ( foundedEntries.size()==0 ){
	
		cout<<"Ther was correctly no entries found."<<endl;
	}else{
		cerr<<"Error: Ther wher entries found but "<<
			foundedEntries.size()<<"."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : searching for the full key \"test4\""<<endl;
	

	cout<<"optionalpartTest1.getEntries(\"test4\", true) "<<endl;
	foundedEntries=optionalpartTest1.getEntries("test4", true);

	cout<<"Founded entries: ";
	for (list< pair< string ,string > >::iterator itrEntry=foundedEntries.begin();
		itrEntry!=foundedEntries.end(); itrEntry++){
		cout<<(*itrEntry)<<"; ";
	}
	cout<<endl;

	//check if one entry was found
	if ( foundedEntries.size()==2 ){
	
		cout<<"Ther was correctly 2 entries found."<<endl;
	}else{
		cerr<<"Error: Ther wher not 2 entries found but "<<
			foundedEntries.size()<<"."<<endl;
		iReturn++;
	}

	//check if the correct entry ("test4", "wert4") was found
	entryFound=find( foundedEntries.begin(), foundedEntries.end(),
		pair< string ,string >("test4", "wert4") );
	
	if ( entryFound!=foundedEntries.end() ){
	
		cout<<"The entry "<<pair< string ,string >("test4", "wert4")<<
			" was correctly found."<<endl;
	}else{
		cerr<<"Error: The entry "<<pair< string ,string >("test4", "wert4")
			<<" could not be found."<<endl;
		iReturn++;
	}

	//check if the correct entry ("test4", "wert2.4") was found
	entryFound=find( foundedEntries.begin(), foundedEntries.end(),
		pair< string ,string >("test4", "wert2.4") );
	
	if ( entryFound!=foundedEntries.end() ){
	
		cout<<"The entry "<<pair< string ,string >("test4", "wert2.4")<<
			" was correctly found."<<endl;
	}else{
		cerr<<"Error: The entry "<<pair< string ,string >("test4", "wert2.4")
			<<" could not be found."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : searching for the key beginning \"test4\""<<endl;
	

	cout<<"optionalpartTest1.getEntries(\"test4\", false) "<<endl;
	foundedEntries=optionalpartTest1.getEntries("test4", false);

	cout<<"Founded entries: ";
	for (list< pair< string ,string > >::iterator itrEntry=foundedEntries.begin();
		itrEntry!=foundedEntries.end(); itrEntry++){
		cout<<(*itrEntry)<<"; ";
	}
	cout<<endl;

	//check if one entry was found
	if ( foundedEntries.size()==3 ){
	
		cout<<"Ther was correctly 3 entries found."<<endl;
	}else{
		cerr<<"Error: Ther wher not 3 entries found but "<<
			foundedEntries.size()<<"."<<endl;
		iReturn++;
	}

	//check if the correct entry ("test4", "wert4") was found
	entryFound=find( foundedEntries.begin(), foundedEntries.end(),
		pair< string ,string >("test4", "wert4") );
	
	if ( entryFound!=foundedEntries.end() ){
	
		cout<<"The entry "<<pair< string ,string >("test4", "wert4")<<
			" was correctly found."<<endl;
	}else{
		cerr<<"Error: The entry "<<pair< string ,string >("test4", "wert4")
			<<" could not be found."<<endl;
		iReturn++;
	}

	//check if the correct entry ("test4", "wert2.4") was found
	entryFound=find( foundedEntries.begin(), foundedEntries.end(),
		pair< string ,string >("test4", "wert2.4") );
	
	if ( entryFound!=foundedEntries.end() ){
	
		cout<<"The entry "<<pair< string ,string >("test4", "wert2.4")<<
			" was correctly found."<<endl;
	}else{
		cerr<<"Error: The entry "<<pair< string ,string >("test4", "wert2.4")
			<<" could not be found."<<endl;
		iReturn++;
	}

	//check if the correct entry ("test4.2", "wert4") was found
	entryFound=find( foundedEntries.begin(), foundedEntries.end(),
		pair< string ,string >("test4.2", "wert4") );
	
	if ( entryFound!=foundedEntries.end() ){
	
		cout<<"The entry "<<pair< string ,string >("test4.2", "wert4")<<
			" was correctly found."<<endl;
	}else{
		cerr<<"Error: The entry "<<pair< string ,string >("test4.2", "wert4")
			<<" could not be found."<<endl;
		iReturn++;
	}
	return iReturn;
}


/**
 * This method tests the findKeyPart() method of the cOptionalPart class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testFindKeyPart( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the findKeyPart() method, searching for the keypart \"test3\""<<endl;
	
	//making new cOptionalPart object with entries
	cout<<"cOptionalPart optionalpartTest1=cOptionalPart() "<<endl;
	cOptionalPart optionalpartTest1=cOptionalPart();
	cout<<"optionalpartTest1.addEntry( \"test2\", \"wert2\", 1 ) "<<endl;
	optionalpartTest1.addEntry( "test2", "wert2", 1 );
	cout<<"optionalpartTest1.addEntry( \"test1\", \"wert1\", 2 ) "<<endl;
	optionalpartTest1.addEntry( "test1", "wert1", 2 );
	cout<<"optionalpartTest1.addEntry( \"test4\", \"wert4\", 3 ) "<<endl;
	optionalpartTest1.addEntry( "test4", "wert4", 3 );
	cout<<"optionalpartTest1.addEntry( \"test3\", \"wert3\", 4 ) "<<endl;
	optionalpartTest1.addEntry( "test3", "wert3", 4 );
	cout<<"optionalpartTest1.addEntry( \"test4\", \"wert2.4\", 5 ) "<<endl;
	optionalpartTest1.addEntry( "test4", "wert2.4", 5 );
	cout<<"optionalpartTest1.addEntry( \"test4.2\", \"wert4\", 6 ) "<<endl;
	optionalpartTest1.addEntry( "test4.2", "wert4", 6 );


	cout<<"optionalpartTest1.findKeyPart(\"test3\") "<<endl;
	list< pair< string ,string > > foundedEntries=
		optionalpartTest1.findKeyPart("test3");

	cout<<"Founded entries: ";
	for (list< pair< string ,string > >::iterator itrEntry=foundedEntries.begin();
		itrEntry!=foundedEntries.end(); itrEntry++){
		cout<<(*itrEntry)<<"; ";
	}
	cout<<endl;

	//check if one entry was found
	if ( foundedEntries.size()==1 ){
	
		cout<<"Ther was correctly one entry found."<<endl;
	}else{
		cerr<<"Error: Ther wher not one entry found but "<<
			foundedEntries.size()<<"."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	list< pair< string ,string > >::iterator entryFound=
		find( foundedEntries.begin(), foundedEntries.end(),
		pair< string ,string >("test3", "wert3") );
	
	if ( entryFound!=foundedEntries.end() ){
	
		cout<<"The entry "<<pair< string ,string >("test3", "wert3")<<
			" was correctly found."<<endl;
	}else{
		cerr<<"Error: The entry "<<pair< string ,string >("test3", "wert3")
			<<" could not be found."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : searching for the keypart \"test99\""<<endl;
	
	cout<<"optionalpartTest1.findKeyPart(\"test99\") "<<endl;
	foundedEntries=
		optionalpartTest1.findKeyPart("test99");

	cout<<"Founded entries: ";
	for (list< pair< string ,string > >::iterator itrEntry=foundedEntries.begin();
		itrEntry!=foundedEntries.end(); itrEntry++){
		cout<<(*itrEntry)<<"; ";
	}
	cout<<endl;

	//check if one entry was found
	if ( foundedEntries.size()==0 ){
	
		cout<<"Ther was correctly no entries found."<<endl;
	}else{
		cerr<<"Error: Ther wher entries found but "<<
			foundedEntries.size()<<"."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : searching for the keypart \"st3\""<<endl;
	

	cout<<"optionalpartTest1.findKeyPart(\"st3\") "<<endl;
	foundedEntries=
		optionalpartTest1.findKeyPart("st3");

	cout<<"Founded entries: ";
	for (list< pair< string ,string > >::iterator itrEntry=foundedEntries.begin();
		itrEntry!=foundedEntries.end(); itrEntry++){
		cout<<(*itrEntry)<<"; ";
	}
	cout<<endl;

	//check if one entry was found
	if ( foundedEntries.size()==1 ){
	
		cout<<"Ther was correctly one entry found."<<endl;
	}else{
		cerr<<"Error: Ther wher not one entry found but "<<
			foundedEntries.size()<<"."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	entryFound=find( foundedEntries.begin(), foundedEntries.end(),
		pair< string ,string >("test3", "wert3") );
	
	if ( entryFound!=foundedEntries.end() ){
	
		cout<<"The entry "<<pair< string ,string >("test3", "wert3")<<
			" was correctly found."<<endl;
	}else{
		cerr<<"Error: The entry "<<pair< string ,string >("test3", "wert3")
			<<" could not be found."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : searching for the keypart \"t4\""<<endl;

	cout<<"optionalpartTest1.findKeyPart(\"t4\") "<<endl;
	foundedEntries=optionalpartTest1.findKeyPart("t4");

	cout<<"Founded entries: ";
	for (list< pair< string ,string > >::iterator itrEntry=foundedEntries.begin();
		itrEntry!=foundedEntries.end(); itrEntry++){
		cout<<(*itrEntry)<<"; ";
	}
	cout<<endl;

	//check if one entry was found
	if ( foundedEntries.size()==3 ){
	
		cout<<"Ther was correctly 3 entries found."<<endl;
	}else{
		cerr<<"Error: Ther wher not 3 entries found but "<<
			foundedEntries.size()<<"."<<endl;
		iReturn++;
	}

	//check if the correct entry ("test4", "wert4") was found
	entryFound=find( foundedEntries.begin(), foundedEntries.end(),
		pair< string ,string >("test4", "wert4") );
	
	if ( entryFound!=foundedEntries.end() ){
	
		cout<<"The entry "<<pair< string ,string >("test4", "wert4")<<
			" was correctly found."<<endl;
	}else{
		cerr<<"Error: The entry "<<pair< string ,string >("test4", "wert4")
			<<" could not be found."<<endl;
		iReturn++;
	}

	//check if the correct entry ("test4", "wert2.4") was found
	entryFound=find( foundedEntries.begin(), foundedEntries.end(),
		pair< string ,string >("test4", "wert2.4") );
	
	if ( entryFound!=foundedEntries.end() ){
	
		cout<<"The entry "<<pair< string ,string >("test4", "wert2.4")<<
			" was correctly found."<<endl;
	}else{
		cerr<<"Error: The entry "<<pair< string ,string >("test4", "wert2.4")
			<<" could not be found."<<endl;
		iReturn++;
	}


	//check if the correct entry ("test4.2", "wert4") was found
	entryFound=find( foundedEntries.begin(), foundedEntries.end(),
		pair< string ,string >("test4.2", "wert4") );
	
	if ( entryFound!=foundedEntries.end() ){
	
		cout<<"The entry "<<pair< string ,string >("test4.2", "wert4")<<
			" was correctly found."<<endl;
	}else{
		cerr<<"Error: The entry "<<pair< string ,string >("test4.2", "wert4")
			<<" could not be found."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the deleteEntry() method of the cOptionalPart class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testDeleteEntry( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleteEntry(); for value 0 which is not deletebel"<<endl;

	//making new cOptionalPart object with entries
	cout<<"cOptionalPart optionalpartTest1=cOptionalPart() "<<endl;
	cOptionalPart optionalpartTest1=cOptionalPart();
	cout<<"optionalpartTest1.addEntry( \"test2\", \"wert2\", 1 ) "<<endl;
	optionalpartTest1.addEntry( "test2", "wert2", 1 );
	cout<<"optionalpartTest1.addEntry( \"test1\", \"wert1\", 2 ) "<<endl;
	optionalpartTest1.addEntry( "test1", "wert1", 2 );
	cout<<"optionalpartTest1.addEntry( \"test4\", \"wert4\", 3 ) "<<endl;
	optionalpartTest1.addEntry( "test4", "wert4", 3 );
	cout<<"optionalpartTest1.addEntry( \"test3\", \"wert3\", 4 ) "<<endl;
	optionalpartTest1.addEntry( "test3", "wert3", 4 );
	cout<<"optionalpartTest1.addEntry( \"test4\", \"wert2.4\", 5 ) "<<endl;
	optionalpartTest1.addEntry( "test4", "wert2.4", 5 );
	cout<<"optionalpartTest1.addEntry( \"test4.2\", \"wert4\", 6 ) "<<endl;
	optionalpartTest1.addEntry( "test4.2", "wert4", 6 );

	cout<<"optionalpartTest1.deleteEntry( 0 ) "<<endl;
	bool bEntryDeleted=optionalpartTest1.deleteEntry( 7 );

	//check the deleteEntry() methode from cOptionalPart
	if ( !bEntryDeleted ){
	
		cout<<"The entry was correctly not deleted. "<<endl;
	}else{
		cerr<<"Error: The entry was deleted"<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==6 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			6<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 6."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 0 )==pair< string ,string >("","") ){
	
		cout<<"The 0'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 0'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 0 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 1 )==pair< string ,string >("test2", "wert2") ){
	
		cout<<"The 1'th entry is correctly the pair "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 2 )==pair< string ,string >("test1", "wert1") ){
	
		cout<<"The 2'th entry is correctly the pair "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 3 )==pair< string ,string >("test4", "wert4") ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			pair< string ,string >("test4", "wert4")<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should "<<
			pair< string ,string >("test4", "wert4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 4 )==pair< string ,string >("test3", "wert3") ){
	
		cout<<"The 4'th entry is correctly the pair "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 4 )<<" but should "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 5 )==pair< string ,string >("test4", "wert2.4") ){
	
		cout<<"The 5'th entry is correctly the pair "<<
			pair< string ,string >("test4", "wert2.4")<<"."<<endl;
	}else{
		cerr<<"Error: The 5'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 5 )<<" but should "<<
			pair< string ,string >("test4", "wert2.4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 6 )==pair< string ,string >("test4.2", "wert4") ){
	
		cout<<"The 6'th entry is correctly the pair "<<
			pair< string ,string >("test4.2", "wert4")<<"."<<endl;
	}else{
		cerr<<"Error: The 6'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 6 )<<" but should "<<
			pair< string ,string >("test4.2", "wert4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 7 )==pair< string ,string >("","") ){
	
		cout<<"The 7'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 7'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 7 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleteEntry(); for value 7 which is not deletebel"<<endl;

	cout<<"optionalpartTest1.deleteEntry( 7 ) "<<endl;
	bEntryDeleted=optionalpartTest1.deleteEntry( 7 );

	//check the deleteEntry() methode from cOptionalPart
	if ( !bEntryDeleted ){
	
		cout<<"The entry was correctly not deleted. "<<endl;
	}else{
		cerr<<"Error: The entry was deleted"<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==6 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			6<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 6."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 0 )==pair< string ,string >("","") ){
	
		cout<<"The 0'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 0'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 0 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 1 )==pair< string ,string >("test2", "wert2") ){
	
		cout<<"The 1'th entry is correctly the pair "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 2 )==pair< string ,string >("test1", "wert1") ){
	
		cout<<"The 2'th entry is correctly the pair "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 3 )==pair< string ,string >("test4", "wert4") ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			pair< string ,string >("test4", "wert4")<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should "<<
			pair< string ,string >("test4", "wert4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 4 )==pair< string ,string >("test3", "wert3") ){
	
		cout<<"The 4'th entry is correctly the pair "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 4 )<<" but should "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 5 )==pair< string ,string >("test4", "wert2.4") ){
	
		cout<<"The 5'th entry is correctly the pair "<<
			pair< string ,string >("test4", "wert2.4")<<"."<<endl;
	}else{
		cerr<<"Error: The 5'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 5 )<<" but should "<<
			pair< string ,string >("test4", "wert2.4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 6 )==pair< string ,string >("test4.2", "wert4") ){
	
		cout<<"The 6'th entry is correctly the pair "<<
			pair< string ,string >("test4.2", "wert4")<<"."<<endl;
	}else{
		cerr<<"Error: The 6'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 6 )<<" but should "<<
			pair< string ,string >("test4.2", "wert4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 7 )==pair< string ,string >("","") ){
	
		cout<<"The 7'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 7'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 7 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleteEntry(); for value 2 "<<endl;

	cout<<"optionalpartTest1.deleteEntry( 2 ) "<<endl;
	bEntryDeleted=optionalpartTest1.deleteEntry( 2 );

	//check the deleteEntry() methode from cOptionalPart
	if ( bEntryDeleted ){
	
		cout<<"The entry was correctly deleted. "<<endl;
	}else{
		cerr<<"Error: The entry was not deleted"<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==5 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			5<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 5."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 0 )==pair< string ,string >("","") ){
	
		cout<<"The 0'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 0'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 0 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 1 )==pair< string ,string >("test2", "wert2") ){
	
		cout<<"The 1'th entry is correctly the pair "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 2 )==pair< string ,string >("test4", "wert4") ){
	
		cout<<"The 2'th entry is correctly the pair "<<
			pair< string ,string >("test4", "wert4")<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should "<<
			pair< string ,string >("test4", "wert4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 3 )==pair< string ,string >("test3", "wert3") ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 4 )==pair< string ,string >("test4", "wert2.4") ){
	
		cout<<"The 4'th entry is correctly the pair "<<
			pair< string ,string >("test4", "wert2.4")<<"."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 4 )<<" but should "<<
			pair< string ,string >("test4", "wert2.4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 5 )==pair< string ,string >("test4.2", "wert4") ){
	
		cout<<"The 5'th entry is correctly the pair "<<
			pair< string ,string >("test4.2", "wert4")<<"."<<endl;
	}else{
		cerr<<"Error: The 5'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 5 )<<" but should "<<
			pair< string ,string >("test4.2", "wert4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 6 )==pair< string ,string >("","") ){
	
		cout<<"The 6'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 6'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 6 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}

	cout<<"optionalpartTest1.addEntry( \"test1\", \"wert1\", 2 ) "<<endl;
	optionalpartTest1.addEntry( "test1", "wert1", 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleteEntry(); for value 6 "<<endl;

	cout<<"optionalpartTest1.deleteEntry( 6 ) "<<endl;
	bEntryDeleted=optionalpartTest1.deleteEntry( 6 );

	//check the deleteEntry() methode from cOptionalPart
	if ( bEntryDeleted ){
	
		cout<<"The entry was correctly deleted. "<<endl;
	}else{
		cerr<<"Error: The entry was not deleted"<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==5 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			5<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 5."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 0 )==pair< string ,string >("","") ){
	
		cout<<"The 0'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 0'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 0 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 1 )==pair< string ,string >("test2", "wert2") ){
	
		cout<<"The 1'th entry is correctly the pair "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should "<<
			pair< string ,string >("test2", "wert2")<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 2 )==pair< string ,string >("test1", "wert1") ){
	
		cout<<"The 2'th entry is correctly the pair "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should "<<
			pair< string ,string >("test1", "wert1")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 3 )==pair< string ,string >("test4", "wert4") ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			pair< string ,string >("test4", "wert4")<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should "<<
			pair< string ,string >("test4", "wert4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 4 )==pair< string ,string >("test3", "wert3") ){
	
		cout<<"The 4'th entry is correctly the pair "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 4 )<<" but should "<<
			pair< string ,string >("test3", "wert3")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 5 )==pair< string ,string >("test4", "wert2.4") ){
	
		cout<<"The 5'th entry is correctly the pair "<<
			pair< string ,string >("test4", "wert2.4")<<"."<<endl;
	}else{
		cerr<<"Error: The 5'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 5 )<<" but should "<<
			pair< string ,string >("test4", "wert2.4")<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	if ( optionalpartTest1.getEntry( 7 )==pair< string ,string >("","") ){
	
		cout<<"The 7'th entry is correctly a pair of two empty strings."<<endl;
	}else{
		cerr<<"Error: The 7'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 7 )<<" but should be two empty strings."<<endl;
		iReturn++;
	}


	return iReturn;
}


/**
 * This method tests the deleteEntries() method of the cOptionalPart class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testDeleteEntries( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleteEntries(); for key \"test99\" which dosn't exists"<<endl;

	//making new cOptionalPart object with entries
	cout<<"Creating new cOptionalPart object for testing:  "<<endl;
	cout<<"cOptionalPart optionalpartTest1=cOptionalPart() "<<endl;
	cOptionalPart optionalpartTest1=cOptionalPart();
	cout<<"optionalpartTest1.addEntry( \"test1\", \"wert1\", 1 ) "<<endl;
	optionalpartTest1.addEntry( "test1", "wert1", 1 );
	cout<<"optionalpartTest1.addEntry( \"test2\", \"wert2\", 2 ) "<<endl;
	optionalpartTest1.addEntry( "test2", "wert2", 2 );
	cout<<"optionalpartTest1.addEntry( \"test3\", \"wert3\", 3 ) "<<endl;
	optionalpartTest1.addEntry( "test3", "wert3", 3 );
	cout<<"optionalpartTest1.addEntry( \"test3.1\", \"wert3\", 4 ) "<<endl;
	optionalpartTest1.addEntry( "test3.1", "wert3", 4 );
	cout<<"optionalpartTest1.addEntry( \"test3\", \"wert3.1\", 5 ) "<<endl;
	optionalpartTest1.addEntry( "test3", "wert3.1", 5 );
	cout<<"optionalpartTest1.addEntry( \"test3.2\", \"wert3.2\", 6 ) "<<endl;
	optionalpartTest1.addEntry( "test3.2", "wert3.2", 6 );
	cout<<endl;


	cout<<"optionalpartTest1.deleteEntries(\"test99\") "<<endl;
	unsignedLongFib deletedEntries=optionalpartTest1.deleteEntries("test99");

	if ( deletedEntries==0 ){
	
		cout<<"The number of deleted entries is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of deleted entries is "<<
			deletedEntries<<" but should be 0."<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==6 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			6<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 6."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	pair< string ,string > checkPair=pair< string ,string >("test1", "wert1");
	if ( optionalpartTest1.getEntry( 1 )==checkPair ){
	
		cout<<"The 1'th entry is correctly the pair "<<checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test2", "wert2");
	if ( optionalpartTest1.getEntry( 2 )==checkPair){
	
		cout<<"The 2'th entry is correctly the pair "<<checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3", "wert3");
	if ( optionalpartTest1.getEntry( 3 )==checkPair ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3.1", "wert3");
	if ( optionalpartTest1.getEntry( 4 )==checkPair ){
	
		cout<<"The 4'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 4 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3", "wert3.1");
	if ( optionalpartTest1.getEntry( 5 )==checkPair ){
	
		cout<<"The 5'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 5'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 5 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3.2", "wert3.2");
	if ( optionalpartTest1.getEntry( 6 )==checkPair ){
	
		cout<<"The 6'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 6'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 6 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleteEntries(); for key beginning \"test99\" which dosn't exists"<<endl;
	
	cout<<"optionalpartTest1.deleteEntries(\"test99\", false) "<<endl;
	deletedEntries=optionalpartTest1.deleteEntries("test99", false);

	if ( deletedEntries==0 ){
	
		cout<<"The number of deleted entries is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of deleted entries is "<<
			deletedEntries<<" but should be 0."<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==6 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			6<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 6."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test1", "wert1");
	if ( optionalpartTest1.getEntry( 1 )==checkPair ){
	
		cout<<"The 1'th entry is correctly the pair "<<checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test2", "wert2");
	if ( optionalpartTest1.getEntry( 2 )==checkPair){
	
		cout<<"The 2'th entry is correctly the pair "<<checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3", "wert3");
	if ( optionalpartTest1.getEntry( 3 )==checkPair ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3.1", "wert3");
	if ( optionalpartTest1.getEntry( 4 )==checkPair ){
	
		cout<<"The 4'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 4 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3", "wert3.1");
	if ( optionalpartTest1.getEntry( 5 )==checkPair ){
	
		cout<<"The 5'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 5'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 5 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3.2", "wert3.2");
	if ( optionalpartTest1.getEntry( 6 )==checkPair ){
	
		cout<<"The 6'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 6'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 6 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : deleting single full key \"test1\""<<endl;

	cout<<"optionalpartTest1.deleteEntries(\"test1\") "<<endl;
	deletedEntries=optionalpartTest1.deleteEntries("test1");

	if ( deletedEntries==1 ){
	
		cout<<"The number of deleted entries is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of deleted entries is "<<
			deletedEntries<<" but should be 1."<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==5 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			5<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 5."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test2", "wert2");
	if ( optionalpartTest1.getEntry( 1 )==checkPair){
	
		cout<<"The 1'th entry is correctly the pair "<<checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3", "wert3");
	if ( optionalpartTest1.getEntry( 2 )==checkPair ){
	
		cout<<"The 2'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3.1", "wert3");
	if ( optionalpartTest1.getEntry( 3 )==checkPair ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3", "wert3.1");
	if ( optionalpartTest1.getEntry( 4 )==checkPair ){
	
		cout<<"The 4'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 4 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3.2", "wert3.2");
	if ( optionalpartTest1.getEntry( 5 )==checkPair ){
	
		cout<<"The 5'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 5'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 5 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	cout<<"optionalpartTest1.addEntry( \"test1\", \"wert1\", 1 ) "<<endl;
	optionalpartTest1.addEntry( "test1", "wert1", 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : deleting single key beginning \"test1\""<<endl;

	cout<<"optionalpartTest1.deleteEntries(\"test1\", false) "<<endl;
	deletedEntries=optionalpartTest1.deleteEntries("test1", false);

	if ( deletedEntries==1 ){
	
		cout<<"The number of deleted entries is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of deleted entries is "<<
			deletedEntries<<" but should be 1."<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==5 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			5<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 5."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test2", "wert2");
	if ( optionalpartTest1.getEntry( 1 )==checkPair){
	
		cout<<"The 1'th entry is correctly the pair "<<checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3", "wert3");
	if ( optionalpartTest1.getEntry( 2 )==checkPair ){
	
		cout<<"The 2'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3.1", "wert3");
	if ( optionalpartTest1.getEntry( 3 )==checkPair ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3", "wert3.1");
	if ( optionalpartTest1.getEntry( 4 )==checkPair ){
	
		cout<<"The 4'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 4 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3.2", "wert3.2");
	if ( optionalpartTest1.getEntry( 5 )==checkPair ){
	
		cout<<"The 5'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 5'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 5 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	cout<<"optionalpartTest1.addEntry( \"test1\", \"wert1\", 1 ) "<<endl;
	optionalpartTest1.addEntry( "test1", "wert1", 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : deleting single full key \"test3\""<<endl;

	cout<<"optionalpartTest1.deleteEntries(\"test3\", true) "<<endl;
	deletedEntries=optionalpartTest1.deleteEntries("test3", true);

	if ( deletedEntries==2 ){
	
		cout<<"The number of deleted entries is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of deleted entries is "<<
			deletedEntries<<" but should be 2."<<endl;
		iReturn++;
	}

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==4 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			4<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 4."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test1", "wert1");
	if ( optionalpartTest1.getEntry( 1 )==checkPair ){
	
		cout<<"The 1'th entry is correctly the pair "<<checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test2", "wert2");
	if ( optionalpartTest1.getEntry( 2 )==checkPair){
	
		cout<<"The 2'th entry is correctly the pair "<<checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
		
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3.1", "wert3");
	if ( optionalpartTest1.getEntry( 3 )==checkPair ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3.2", "wert3.2");
	if ( optionalpartTest1.getEntry( 4 )==checkPair ){
	
		cout<<"The 4'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 4 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	cout<<"optionalpartTest1.addEntry( \"test3\", \"wert3\", 3 ) "<<endl;
	optionalpartTest1.addEntry( "test3", "wert3", 3 );
	cout<<"optionalpartTest1.addEntry( \"test3\", \"wert3.1\", 5 ) "<<endl;
	optionalpartTest1.addEntry( "test3", "wert3.1", 5 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : deleting single key beginning \"test3\""<<endl;

	cout<<"optionalpartTest1.deleteEntries(\"test3\", false) "<<endl;
	deletedEntries=optionalpartTest1.deleteEntries("test3", false);
	
	if ( deletedEntries==4 ){
	
		cout<<"The number of deleted entries is correctly 4. "<<endl;
	}else{
		cerr<<"Error: The number of deleted entries is "<<
			deletedEntries<<" but should be 4."<<endl;
		iReturn++;
	}


	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==2 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			2<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 2."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test1", "wert1");
	if ( optionalpartTest1.getEntry( 1 )==checkPair ){
	
		cout<<"The 1'th entry is correctly the pair "<<checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test2", "wert2");
	if ( optionalpartTest1.getEntry( 2 )==checkPair){
	
		cout<<"The 2'th entry is correctly the pair "<<checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}



	return iReturn;
}


/**
 * This method tests the getNumberOfEntries(), getEntry() and addEntry()
 * methods of the cOptionalPart class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testClone( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cloning of an empty cOptionalPart"<<endl;


	cOptionalPart optionalpartTest1=cOptionalPart();

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==0 ){
	
		cout<<"The number of entries in the new optional part is correctly "<<
			0<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 0."<<endl;
		iReturn++;
	}
	
	cout<<"cOptionalPart *optionalpartCloneTest1=optionalpartTest1->clone() "<<endl;
	cOptionalPart *optionalpartCloneTest1=optionalpartTest1.clone();

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartCloneTest1->getNumberOfEntries()==0 ){
	
		cout<<"The number of entries in the optional part clone is correctly "<<
			0<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the optional part clone is "<<
			optionalpartCloneTest1->getNumberOfEntries()<<" but should be 0."<<endl;
		iReturn++;
	}
	delete optionalpartCloneTest1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing clonint cOptionalPart with entries"<<endl;

	//making new cOptionalPart object with entries
	cout<<"adding entries in new cOptionalPart object for testing:  "<<endl;
	cout<<"optionalpartTest1.addEntry( \"test1\", \"wert1\", 1 ) "<<endl;
	optionalpartTest1.addEntry( "test1", "wert1", 1 );
	cout<<"optionalpartTest1.addEntry( \"test2\", \"wert2\", 2 ) "<<endl;
	optionalpartTest1.addEntry( "test2", "wert2", 2 );
	cout<<"optionalpartTest1.addEntry( \"test3\", \"wert3\", 3 ) "<<endl;
	optionalpartTest1.addEntry( "test3", "wert3", 3 );
	cout<<"optionalpartTest1.addEntry( \"test3.1\", \"wert3\", 4 ) "<<endl;
	optionalpartTest1.addEntry( "test3.1", "wert3", 4 );
	cout<<"optionalpartTest1.addEntry( \"test3\", \"wert3.1\", 5 ) "<<endl;
	optionalpartTest1.addEntry( "test3", "wert3.1", 5 );
	cout<<"optionalpartTest1.addEntry( \"test3.2\", \"wert3.2\", 6 ) "<<endl;
	optionalpartTest1.addEntry( "test3.2", "wert3.2", 6 );
	cout<<endl;

	cout<<"cOptionalPart *optionalpartCloneTest1=optionalpartTest1->clone()"<<endl;
	optionalpartCloneTest1=optionalpartTest1.clone();

	cout<<endl<<"Checking original cOptionalPart optionalpartTest1 after cloning it:"<<endl;

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartTest1.getNumberOfEntries()==6 ){
	
		cout<<"The number of entries in the original optional part is correctly "<<
			6<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartTest1.getNumberOfEntries()<<" but should be 6."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	pair< string ,string > checkPair=pair< string ,string >("test1", "wert1");
	if ( optionalpartTest1.getEntry( 1 )==checkPair ){
	
		cout<<"The 1'th entry is correctly the pair "<<checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 1 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test2", "wert2");
	if ( optionalpartTest1.getEntry( 2 )==checkPair){
	
		cout<<"The 2'th entry is correctly the pair "<<checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 2 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3", "wert3");
	if ( optionalpartTest1.getEntry( 3 )==checkPair ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 3 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3.1", "wert3");
	if ( optionalpartTest1.getEntry( 4 )==checkPair ){
	
		cout<<"The 4'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 4 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3", "wert3.1");
	if ( optionalpartTest1.getEntry( 5 )==checkPair ){
	
		cout<<"The 5'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 5'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 5 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3.2", "wert3.2");
	if ( optionalpartTest1.getEntry( 6 )==checkPair ){
	
		cout<<"The 6'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 6'th entry of the new optional part is "<<
			optionalpartTest1.getEntry( 6 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}


	cout<<endl<<"Checking cloned cOptionalPart optionalpartCloneTest1:"<<endl;

	//check the getNumberOfEntries() methode from cOptionalPart
	if ( optionalpartCloneTest1->getNumberOfEntries()==6 ){
	
		cout<<"The number of entries in the original optional part is correctly "<<
			6<<". "<<endl;
	}else{
		cerr<<"Error: The number of entries in the new optional part is "<<
			optionalpartCloneTest1->getNumberOfEntries()<<" but should be 6."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test1", "wert1");
	if ( optionalpartCloneTest1->getEntry( 1 )==checkPair ){
	
		cout<<"The 1'th entry is correctly the pair "<<checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 1'th entry of the new optional part is "<<
			optionalpartCloneTest1->getEntry( 1 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test2", "wert2");
	if ( optionalpartCloneTest1->getEntry( 2 )==checkPair){
	
		cout<<"The 2'th entry is correctly the pair "<<checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 2'th entry of the new optional part is "<<
			optionalpartCloneTest1->getEntry( 2 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3", "wert3");
	if ( optionalpartCloneTest1->getEntry( 3 )==checkPair ){
	
		cout<<"The 3'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 3'th entry of the new optional part is "<<
			optionalpartCloneTest1->getEntry( 3 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3.1", "wert3");
	if ( optionalpartCloneTest1->getEntry( 4 )==checkPair ){
	
		cout<<"The 4'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 4'th entry of the new optional part is "<<
			optionalpartCloneTest1->getEntry( 4 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3", "wert3.1");
	if ( optionalpartCloneTest1->getEntry( 5 )==checkPair ){
	
		cout<<"The 5'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 5'th entry of the new optional part is "<<
			optionalpartCloneTest1->getEntry( 5 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}

	//check the getEntry() methode from empty cOptionalPart
	checkPair=pair< string ,string >("test3.2", "wert3.2");
	if ( optionalpartCloneTest1->getEntry( 6 )==checkPair ){
	
		cout<<"The 6'th entry is correctly the pair "<<
			checkPair<<"."<<endl;
	}else{
		cerr<<"Error: The 6'th entry of the new optional part is "<<
			optionalpartCloneTest1->getEntry( 6 )<<" but should be "<<
			checkPair<<"."<<endl;
		iReturn++;
	}
	
	delete optionalpartCloneTest1;

	return iReturn;
}



/**
 * this method outputs a pair of strings to a stream;
 * 
 * @param stringPair the pair to output
 * @param ostream the stream wher to output the pair to
 * @return this pair in the stream
 */
ostream& operator<<( ostream &ostream, const pair< string ,string > &stringPair ){

	ostream<<"(\""<<stringPair.first<<"\";\""<<stringPair.second<<"\")";
	return ostream;
}







/**
 * This method tests the equal() method and the operator== of two given
 * cOptionalPart objects which are equal.
 *
 * @param optPart1 the first optional part to compare
 * @param szNameOptPart1 the name of the first optional part to compare
 * @param optPart2 the secound optional part to compare to
 * @param szNameOptPart2 the name of the secound optional part to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualOptParts( const cOptionalPart & optPart1, const string & szNameOptPart1,
	const cOptionalPart & optPart2, const string & szNameOptPart2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( optPart1.equal( optPart2 ) ){
	
		cout<<"The "<<szNameOptPart1<<" is equal to "<<szNameOptPart2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameOptPart1<<" is not equal to "<<
			szNameOptPart2<<"."<<endl;
		iReturn++;
	}
	if ( optPart1 == optPart2 ){
	
		cout<<"The "<<szNameOptPart1<<" is equal (operator==) to "<<
			szNameOptPart2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameOptPart1<<" is not equal (operator==) to "<<
			szNameOptPart2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}

/**
 * This method tests the equal() method and the operator== of two given
 * cOptionalPart objects which are not equal.
 *
 * @param optPart1 the first optional part to compare
 * @param szNameOptPart1 the name of the first optional part to compare
 * @param optPart2 the secound optional part to compare to
 * @param szNameOptPart2 the name of the secound optional part to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualOptParts( const cOptionalPart & optPart1, const string & szNameOptPart1,
	const cOptionalPart & optPart2, const string & szNameOptPart2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! optPart1.equal( optPart2 ) ){
	
		cout<<"The "<<szNameOptPart1<<" is not equal to "<<szNameOptPart2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameOptPart1<<" is equal to "<<
			szNameOptPart2<<"."<<endl;
		iReturn++;
	}
	if ( ! (optPart1 == optPart2) ){
	
		cout<<"The "<<szNameOptPart1<<" is not equal (operator==) to "<<
			szNameOptPart2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameOptPart1<<" is equal (operator==) to "<<
			szNameOptPart2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the equal() method and the operator== of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testEqual( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equal method and the operator== "<<endl;

	cout<<endl<<"creating cOptionalPart to compare:"<<endl<<endl;

	cout<<"cOptionalPart optPartEmpty1;"<<endl;
	cOptionalPart optPartEmpty1;
	cout<<"cOptionalPart optPartEmpty2;"<<endl;
	cOptionalPart optPartEmpty2;
	
	cout<<"cOptionalPart optPart1E1;"<<endl;
	cOptionalPart optPart1E1;
	cout<<"optPart1E1.addEntry( \"key\", \"value\" );"<<endl;
	optPart1E1.addEntry( "key", "value" );
	
	cout<<"cOptionalPart optPart2E1;"<<endl;
	cOptionalPart optPart2E1;
	cout<<"optPart2E1.addEntry( \"key\", \"value\" );"<<endl;
	optPart2E1.addEntry( "key", "value" );

	cout<<"cOptionalPart optPart2E1Empty;"<<endl;
	cOptionalPart optPart2E1Empty;
	cout<<"optPart2E1Empty.addEntry( \"\", \"\" );"<<endl;
	optPart2E1Empty.addEntry( "", "" );

	cout<<"cOptionalPart optPartE1Dk1;"<<endl;
	cOptionalPart optPartE1Dk1;
	cout<<"optPartE1Dk1.addEntry( \"key1\", \"value\" );"<<endl;
	optPartE1Dk1.addEntry( "key1", "value" );

	cout<<"cOptionalPart optPartE1Dk2;"<<endl;
	cOptionalPart optPartE1Dk2;
	cout<<"optPartE1Dk2.addEntry( \" key\", \"value\" );"<<endl;
	optPartE1Dk2.addEntry( " key", "value" );

	cout<<"cOptionalPart optPartE1Dk3;"<<endl;
	cOptionalPart optPartE1Dk3;
	cout<<"optPartE1Dk3.addEntry( \" keey\", \"value\" );"<<endl;
	optPartE1Dk3.addEntry( " keey", "value" );

	cout<<"cOptionalPart optPartE1Dv1;"<<endl;
	cOptionalPart optPartE1Dv1;
	cout<<"optPartE1Dv1.addEntry( \" key\", \"valued\" );"<<endl;
	optPartE1Dv1.addEntry( " key", "valued" );

	cout<<"cOptionalPart optPartE1Dv2;"<<endl;
	cOptionalPart optPartE1Dv2;
	cout<<"optPartE1Dv2.addEntry( \" key\", \"dvalue\" );"<<endl;
	optPartE1Dv2.addEntry( " key", "dvalue" );

	cout<<"cOptionalPart optPartE1Dv3;"<<endl;
	cOptionalPart optPartE1Dv3;
	cout<<"optPartE1Dv3.addEntry( \" key\", \"varlue\" );"<<endl;
	optPartE1Dv3.addEntry( " key", "varlue" );

	cout<<"cOptionalPart optPartE2Dup;"<<endl;
	cOptionalPart optPartE2Dup;
	cout<<"optPartE2Dup.addEntry( \"key\", \"value\" );"<<endl;
	optPartE2Dup.addEntry( "key", "value" );
	cout<<"optPartE2Dup.addEntry( \"key\", \"value\" );"<<endl;
	optPartE2Dup.addEntry( "key", "value" );

	cout<<"cOptionalPart optPartE2Dk2;"<<endl;
	cOptionalPart optPartE2Dk2;
	cout<<"optPartE2Dk2.addEntry( \"key\", \"value\" );"<<endl;
	optPartE2Dk2.addEntry( "key", "value" );
	cout<<"optPartE2Dk2.addEntry( \"key2\", \"value\" );"<<endl;
	optPartE2Dk2.addEntry( "key2", "value" );

	cout<<"cOptionalPart optPartE2ChOrd;"<<endl;
	cOptionalPart optPartE2ChOrd;
	cout<<"optPartE2ChOrd.addEntry( \"key2\", \"value\" );"<<endl;
	optPartE2ChOrd.addEntry( "key2", "value" );
	cout<<"optPartE2ChOrd.addEntry( \"key\", \"value\" );"<<endl;
	optPartE2ChOrd.addEntry( "key", "value" );

	cout<<"cOptionalPart optPartE2Dv2;"<<endl;
	cOptionalPart optPartE2Dv2;
	cout<<"optPartE2Dv2.addEntry( \"key\", \"value\" );"<<endl;
	optPartE2Dv2.addEntry( "key", "value" );
	cout<<"optPartE2Dv2.addEntry( \"key\", \"value2\" );"<<endl;
	optPartE2Dv2.addEntry( "key", "value2" );

	cout<<"cOptionalPart optPart1E4;"<<endl;
	cOptionalPart optPart1E4;
	cout<<"optPart1E4.addEntry( \"key\", \"value\" );"<<endl;
	optPart1E4.addEntry( "key", "value" );
	cout<<"optPart1E4.addEntry( \"key1\", \"value\" );"<<endl;
	optPart1E4.addEntry( "key1", "value" );
	cout<<"optPart1E4.addEntry( \"key\", \"value1\" );"<<endl;
	optPart1E4.addEntry( "key", "value1" );
	cout<<"optPart1E4.addEntry( \"key1\", \"value1\" );"<<endl;
	optPart1E4.addEntry( "key1", "value1" );

	cout<<"cOptionalPart optPart2E4;"<<endl;
	cOptionalPart optPart2E4;
	cout<<"optPart2E4.addEntry( \"key\", \"value\" );"<<endl;
	optPart2E4.addEntry( "key", "value" );
	cout<<"optPart2E4.addEntry( \"key1\", \"value\" );"<<endl;
	optPart2E4.addEntry( "key1", "value" );
	cout<<"optPart2E4.addEntry( \"key\", \"value1\" );"<<endl;
	optPart2E4.addEntry( "key", "value1" );
	cout<<"optPart2E4.addEntry( \"key1\", \"value1\" );"<<endl;
	optPart2E4.addEntry( "key1", "value1" );

	cout<<"cOptionalPart optPart1E4ChOrd;"<<endl;
	cOptionalPart optPart1E4ChOrd;
	cout<<"optPart1E4ChOrd.addEntry( \"key\", \"value\" );"<<endl;
	optPart1E4ChOrd.addEntry( "key", "value" );
	cout<<"optPart1E4ChOrd.addEntry( \"key1\", \"value1\" );"<<endl;
	optPart1E4ChOrd.addEntry( "key1", "value1" );
	cout<<"optPart1E4ChOrd.addEntry( \"key1\", \"value\" );"<<endl;
	optPart1E4ChOrd.addEntry( "key1", "value" );
	cout<<"optPart1E4ChOrd.addEntry( \"key\", \"value1\" );"<<endl;
	optPart1E4ChOrd.addEntry( "key", "value1" );

	cout<<"cOptionalPart optPart2E4ChOrd;"<<endl;
	cOptionalPart optPart2E4ChOrd;
	cout<<"optPart2E4ChOrd.addEntry( \"key\", \"value\" );"<<endl;
	optPart2E4ChOrd.addEntry( "key", "value" );
	cout<<"optPart2E4ChOrd.addEntry( \"key\", \"value1\" );"<<endl;
	optPart2E4ChOrd.addEntry( "key", "value1" );
	cout<<"optPart2E4ChOrd.addEntry( \"key1\", \"value\" );"<<endl;
	optPart2E4ChOrd.addEntry( "key1", "value" );
	cout<<"optPart1E4ChOrd.addEntry( \"key1\", \"value1\" );"<<endl;
	optPart1E4ChOrd.addEntry( "key1", "value1" );
	
	cout<<"cOptionalPart optPartE4Dup1;"<<endl;
	cOptionalPart optPartE4Dup1;
	cout<<"optPartE4Dup1.addEntry( \"key\", \"value\" );"<<endl;
	optPartE4Dup1.addEntry( "key", "value" );
	cout<<"optPartE4Dup1.addEntry( \"key1\", \"value\" );"<<endl;
	optPartE4Dup1.addEntry( "key1", "value" );
	cout<<"optPartE4Dup1.addEntry( \"key\", \"value\" );"<<endl;
	optPartE4Dup1.addEntry( "key", "value" );
	cout<<"optPartE4Dup1.addEntry( \"key1\", \"value1\" );"<<endl;
	optPartE4Dup1.addEntry( "key1", "value1" );

	cout<<"cOptionalPart optPartE4Dup2;"<<endl;
	cOptionalPart optPartE4Dup2;
	cout<<"optPartE4Dup2.addEntry( \"key\", \"value\" );"<<endl;
	optPartE4Dup2.addEntry( "key", "value" );
	cout<<"optPartE4Dup2.addEntry( \"key\", \"value\" );"<<endl;
	optPartE4Dup2.addEntry( "key", "value" );
	cout<<"optPartE4Dup2.addEntry( \"key\", \"value1\" );"<<endl;
	optPartE4Dup2.addEntry( "key", "value1" );
	cout<<"optPartE4Dup2.addEntry( \"key1\", \"value1\" );"<<endl;
	optPartE4Dup2.addEntry( "key1", "value1" );

	cout<<"cOptionalPart optPart1E5Dup;"<<endl;
	cOptionalPart optPart1E5Dup;
	cout<<"optPart1E5Dup.addEntry( \"key\", \"value\" );"<<endl;
	optPart1E5Dup.addEntry( "key", "value" );
	cout<<"optPart1E5Dup.addEntry( \"key1\", \"value\" );"<<endl;
	optPart1E5Dup.addEntry( "key1", "value" );
	cout<<"optPart1E5Dup.addEntry( \"key\", \"value1\" );"<<endl;
	optPart1E5Dup.addEntry( "key", "value1" );
	cout<<"optPart1E5Dup.addEntry( \"key1\", \"value1\" );"<<endl;
	optPart1E5Dup.addEntry( "key1", "value1" );
	cout<<"optPart1E5Dup.addEntry( \"key1\", \"value1\" );"<<endl;
	optPart1E5Dup.addEntry( "key1", "value1" );



	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with optPartEmpty1
	cOptionalPart * actualOptPart = &optPartEmpty1;
	string szActualOptPartName = "optPartEmpty1";
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPartEmpty1
	actualOptPart = &optPartEmpty2;
	szActualOptPartName = "optPartEmpty2";
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPart1E1
	actualOptPart = &optPart1E1;
	szActualOptPartName = "optPart1E1";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPart2E1
	actualOptPart = &optPart2E1;
	szActualOptPartName = "optPart2E1";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPart2E1Empty
	actualOptPart = &optPart2E1Empty;
	szActualOptPartName = "optPart2E1Empty";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPartE1Dk1
	actualOptPart = &optPartE1Dk1;
	szActualOptPartName = "optPartE1Dk1";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPartE1Dk2
	actualOptPart = &optPartE1Dk2;
	szActualOptPartName = "optPartE1Dk2";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPartE1Dk3
	actualOptPart = &optPartE1Dk3;
	szActualOptPartName = "optPartE1Dk3";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPartE1Dv1
	actualOptPart = &optPartE1Dv1;
	szActualOptPartName = "optPartE1Dv1";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPartE1Dv2
	actualOptPart = &optPartE1Dv2;
	szActualOptPartName = "optPartE1Dv2";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPartE1Dv3
	actualOptPart = &optPartE1Dv3;
	szActualOptPartName = "optPartE1Dv3";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPartE2Dup
	actualOptPart = &optPartE2Dup;
	szActualOptPartName = "optPartE2Dup";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPartE2Dk2
	actualOptPart = &optPartE2Dk2;
	szActualOptPartName = "optPartE2Dk2";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPartE2ChOrd
	actualOptPart = &optPartE2ChOrd;
	szActualOptPartName = "optPartE2ChOrd";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPartE2Dv2
	actualOptPart = &optPartE2Dv2;
	szActualOptPartName = "optPartE2Dv2";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPart1E4
	actualOptPart = &optPart1E4;
	szActualOptPartName = "optPart1E4";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPart2E4
	actualOptPart = &optPart2E4;
	szActualOptPartName = "optPart2E4";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPart1E4ChOrd
	actualOptPart = &optPart1E4ChOrd;
	szActualOptPartName = "optPart1E4ChOrd";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPart2E4ChOrd
	actualOptPart = &optPart2E4ChOrd;
	szActualOptPartName = "optPart2E4ChOrd";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPartE4Dup1
	actualOptPart = &optPartE4Dup1;
	szActualOptPartName = "optPartE4Dup1";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPartE4Dup2
	actualOptPart = &optPartE4Dup2;
	szActualOptPartName = "optPartE4Dup2";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	//compare with optPart1E5Dup
	actualOptPart = &optPart1E5Dup;
	szActualOptPartName = "optPart1E5Dup";
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty1, "optPartEmpty1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartEmpty2, "optPartEmpty2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E1, "optPart1E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1, "optPart2E1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E1Empty, "optPart2E1Empty" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk1, "optPartE1Dk1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk2, "optPartE1Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dk3, "optPartE1Dk3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv1, "optPartE1Dv1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv2, "optPartE1Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE1Dv3, "optPartE1Dv3" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dup, "optPartE2Dup" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dk2, "optPartE2Dk2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2ChOrd, "optPartE2ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE2Dv2, "optPartE2Dv2" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4, "optPart1E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4, "optPart2E4" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E4ChOrd, "optPart1E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPart2E4ChOrd, "optPart2E4ChOrd" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup1, "optPartE4Dup1" );
	iReturn += testCompareTwoNotEqualOptParts( *actualOptPart, szActualOptPartName, optPartE4Dup2, "optPartE4Dup2" );
	iReturn += testCompareTwoEqualOptParts( *actualOptPart, szActualOptPartName, optPart1E5Dup, "optPart1E5Dup" );

	
	return iReturn;
}



/**
 * This method tests a in the xml-format stored cOptionalPart.
 *
 * @param szFilename the name of the file wher the cFibVector is stored
 * @param liPaOptionalInformation the list with the pairs for the optional
 * 	infornation of the stored cOptionalPart
 * @return the number of errors occured in the test
 */
int testXmlOptPart( const string szFilename,
		list< pair< string, string> > liPaOptionalInformation ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored optionalpart:"<<endl;
	
	TiXmlDocument xmlDocVectorProperty( szFilename );
	bool loadOkay = xmlDocVectorProperty.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocVectorProperty );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();

		if ( szElementName == "optionalpart" ){
			cout<<"The root element is correctly named \"optionalpart\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"optionalpart\"."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	xmlHandleRoot = TiXmlHandle( pXmlElement );
	pXmlElement = xmlHandleRoot.FirstChild().Element();
	
	if ( ! liPaOptionalInformation.empty() ){
		if ( pXmlElement == NULL ){
			cerr<<"Error: No elements in this optionalpart."<<endl;
			iReturn++;
			return iReturn;
		}
	}else{
		if ( pXmlElement != NULL ){
			cerr<<"Error: Ther are elements in this optionalpart, but it shouldn't have some."<<endl;
			iReturn++;
		}
	}
	
	list< pair< string, string> >::const_iterator itrActualPair;
	
	for( itrActualPair = liPaOptionalInformation.begin() ;
			( itrActualPair != liPaOptionalInformation.end() ) && pXmlElement;
			itrActualPair++, pXmlElement = pXmlElement->NextSiblingElement() ){
	
		string szElementName = pXmlElement->Value();
		
		if ( szElementName == "pair" ){
			cout<<"The element is correctly named \"pair\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the element is "<< szElementName <<" and not \"pair\"."<<endl;
			iReturn++;
		}

		const char * szVectorXmlKey = pXmlElement->Attribute( "key" );
		
		if ( szVectorXmlKey == NULL ){
			cerr<<"Error: The optionalpart has no key."<<endl;
			iReturn++;
		}else if ( itrActualPair->first == szVectorXmlKey ) {
			cout<<"The key of the optionalpart is correctly \""<< itrActualPair->first <<"\". "<<endl;
		}else{
			cerr<<"Error: The key of the optionalpart is \""<< szVectorXmlKey
				<<"\", but should be \""<< itrActualPair->first <<"\"."<<endl;
			iReturn++;
		}

		const char * szVectorXmlValue = pXmlElement->Attribute( "value" );
		
		if ( szVectorXmlValue == NULL ){
			cerr<<"Error: The optionalpart has no value."<<endl;
			iReturn++;
		}else if ( itrActualPair->second == szVectorXmlValue ) {
			cout<<"The value of the optionalpart is correctly \""<< itrActualPair->second <<"\". "<<endl;
		}else{
			cerr<<"Error: The value of the optionalpart is \""<< szVectorXmlValue
				<<"\", but should be \""<< itrActualPair->second <<"\"."<<endl;
			iReturn++;
		}
	}
	
	
	if ( pXmlElement ){
		cerr<<"Error: Ther are more elements in the stored optionalpart than given."<<endl;
		iReturn++;
	}
	
	if ( itrActualPair != liPaOptionalInformation.end() ){
		cerr<<"Error: Ther are less elements in the stored optionalpart than given."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the storeXml() method of the cVectorProperty class.
 *
 * methods tested:
 * 	- storeXml()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStoreXml( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an empty optionalpart"<<endl;
	
	cout<<"cOptionalPart optionalpart;"<<endl;
	cOptionalPart optionalpart;
	
	list< pair< string, string> > liPaOptionalInformation;
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "optionalpartEmpty.xml" );
	ofstream * pFileOptionalPart = new ofstream( pFileName );
	
	bool bStoreSuccesfull = optionalpart.storeXml( *pFileOptionalPart );
	delete pFileOptionalPart;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlOptPart( pFileName, liPaOptionalInformation );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an optionalpart with one element"<<endl;
	
	cout<<"optionalpart.addEntry( \"\", \"\");"<<endl;
	optionalpart.addEntry( "", "");
	
	liPaOptionalInformation.push_back( make_pair( "", "") );
	
	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "optionalpartE1.xml" );
	pFileOptionalPart = new ofstream( pFileName );
	
	bStoreSuccesfull = optionalpart.storeXml( *pFileOptionalPart );
	delete pFileOptionalPart;

	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlOptPart( pFileName, liPaOptionalInformation );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an optionalpart with 2 elements"<<endl;
	
	cout<<"optionalpart.addEntry( \"key\", \"value\");"<<endl;
	optionalpart.addEntry( "key", "value");
	
	liPaOptionalInformation.push_back( make_pair( "key", "value") );
	
	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "optionalpartE2.xml" );
	pFileOptionalPart = new ofstream( pFileName );
	
	bStoreSuccesfull = optionalpart.storeXml( *pFileOptionalPart );
	delete pFileOptionalPart;

	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlOptPart( pFileName, liPaOptionalInformation );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an optionalpart with 3 elements"<<endl;
	
	cout<<"optionalpart.addEntry( \"key\", \"value\");"<<endl;
	optionalpart.addEntry( "key", "value");
	
	liPaOptionalInformation.push_back( make_pair( "key", "value") );
	
	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "optionalpartE3.xml" );
	pFileOptionalPart = new ofstream( pFileName );
	
	bStoreSuccesfull = optionalpart.storeXml( *pFileOptionalPart );
	delete pFileOptionalPart;

	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlOptPart( pFileName, liPaOptionalInformation );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an optionalpart with 4 elements"<<endl;
	
	cout<<"optionalpart.addEntry( \"key1\", \"value\");"<<endl;
	optionalpart.addEntry( "key1", "value");
	
	liPaOptionalInformation.push_back( make_pair( "key1", "value") );
	
	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "optionalpartE4.xml" );
	pFileOptionalPart = new ofstream( pFileName );
	
	bStoreSuccesfull = optionalpart.storeXml( *pFileOptionalPart );
	delete pFileOptionalPart;

	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlOptPart( pFileName, liPaOptionalInformation );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an optionalpart with 5 elements"<<endl;
	
	cout<<"optionalpart.addEntry( \"name\", \"ich\");"<<endl;
	optionalpart.addEntry( "name", "ich");
	
	liPaOptionalInformation.push_back( make_pair( "name", "ich") );
	
	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "optionalpartE5.xml" );
	pFileOptionalPart = new ofstream( pFileName );
	
	bStoreSuccesfull = optionalpart.storeXml( *pFileOptionalPart );
	delete pFileOptionalPart;

	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlOptPart( pFileName, liPaOptionalInformation );


	return iReturn;
}






/**
 * This method tests the storeXml() method of the cVectorProperty class.
 *
 * methods tested:
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream & stream ) const;
 * 	- intFib restore( cReadBits & iBitStream, const unsigned long ulBytsToRead = 0 );
 * 	- bool setCompressionType( unsignedIntFib uiInCompressionType = 1 );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStore( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for compressed storing for the optional part"<<endl;
	
	
	static unsigned int uiFileIteration = 1;
	
	for ( unsigned long uiIteration = 0; uiIteration < MAX_RAND_TEST_SIZE;
			uiIteration++ ){
		
		cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for compressed storing iteration "<<uiIteration<<endl;
		
		//generate random optional part
		cout<<"cOptionalPart optionalpart;"<<endl;
		cOptionalPart optionalpart;
		
		const unsigned long uiNumberOfEntries =
			( rand() % ( rand() % (rand() % MAX_RAND_TEST_SIZE + 1 ) + 1 ));
		
		for ( unsigned long uiActualEntry = 0;
				uiActualEntry < uiNumberOfEntries; uiActualEntry++ ){
			const size_t iKey = rand() % vecRandStrings.size();
			const size_t iValue = rand() % vecRandStrings.size();
			
//			cout<<"optionalpart.addEntry( szKey=\""<<vecRandStrings[ iKey ]<<
//				"\", szValue=\""<<vecRandStrings[ iValue ]<<"\" ); "<<endl;
			optionalpart.addEntry(
				vecRandStrings[ iKey ], vecRandStrings[ iValue ] );
		}
		cout<<"Number of added entries: "<<uiNumberOfEntries<<endl;
		
		unsignedIntFib uiCorrectCompressionType = 1;
		if ( rand() % 8 ){
			//set random setCompressionType()
			unsignedIntFib uiToSetCompressionType = 1;
			if ( rand() % 4 ){
				//set correct compression type
				uiToSetCompressionType = rand() % 2;
			}else{
				//set maybe incorrect compression type
				uiToSetCompressionType = rand() % 256;
			}
			if ( uiToSetCompressionType <= 1 ){
				//to set compression type is a correct compression type
				uiCorrectCompressionType = uiToSetCompressionType;
			}
			const bool bCompressionTypeSet =
				optionalpart.setCompressionType( uiToSetCompressionType );
			
			if ( bCompressionTypeSet == ( uiToSetCompressionType <= 1 ) ){
				
				cout<<"The compression type "<<uiToSetCompressionType<<
					" was correctly "<<(bCompressionTypeSet?"":"not ")
					<<"set. "<<endl;
			}else{
				cerr<<"Error: The compression type "<<uiToSetCompressionType<<
					" was "<<(bCompressionTypeSet?"":"not ")
					<<"set, but shouldn't be. "<<endl;
				iReturn++;
			}
			
		}//endif set random setCompressionType()
		
		const unsignedLongFib ulCompressedSize =
			optionalpart.getCompressedSize();
		
		//store it (with and without data behind)
		char szFileNameBuffer[ 256 ];
		sprintf ( szFileNameBuffer, "%s%s%u%s", DIR_OUTPUT, "storeOpPart", uiFileIteration ,".fib" );
		
		ofstream * pOutFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
		
		cout<<"Storing optional part in the compressed Fib-format to the file "<< szFileNameBuffer <<" . "<<endl;
	
		const streampos startPosition = pOutFile->tellp();
		bool bStoreSuccesfull = optionalpart.store( *pOutFile );
		const streampos endPosition = pOutFile->tellp();
		
		if ( (rand() % 4) == 0 ){
			//append some random data to stream
			const unsigned int uiCharactersToAdd = rand() % (256 * 256);
			for ( unsigned int uiAddedCharacters = 0;
					uiAddedCharacters < uiCharactersToAdd; uiAddedCharacters++ ){
				
				(*pOutFile)<<((char)( rand() % 256 ));
			}
		}
		
		delete pOutFile;
		
		if ( ! bStoreSuccesfull ){
	
			cerr<<"Error: Storing the data to compressed Fib-format of the generated optional part to the file \""<<
				szFileNameBuffer <<"\" failed."<<endl;
			iReturn++;
		}
		
		//compare storage space with getCompressedSize()
		const unsigned long ulStoredBits = (endPosition - startPosition) * 8;
		if ( ulCompressedSize == ulStoredBits ){
			cout<<"The compressed size is correctly "<<ulCompressedSize<<" ."<<endl;
		}else{
			cerr<<"Error: The compressed size is "<<ulCompressedSize<<
				", but stored size is "<<ulStoredBits<<" . "<<endl;
			iReturn++;
		}
		
		//restore it
		cout<<"cOptionalPart optionalpartReaded;"<<endl;
		cOptionalPart optionalpartReaded;
		
		ifstream inFile( szFileNameBuffer, ios_base::in | ios_base::binary );
	
		cReadBits inputBitStream( inFile );
		cout<<"optionalpartReaded.restore( inputBitStream, storedByts="<<ulStoredBits / 8<<" );"<<endl<<flush;
		const intFib outStatus = optionalpartReaded.restore( inputBitStream, ulStoredBits / 8 );
		
		if ( outStatus == 0 ){
			cout<<"Restoring optional part in the compressed Fib-format from the file "<<
				szFileNameBuffer <<" successfull. "<<endl<<flush;
		}else{
			cerr<<"Error: Restoring optional part in the compressed Fib-format from the file "<<
				szFileNameBuffer <<" not successfull. (return status="<< outStatus <<")"<<endl<<flush;
			iReturn++;
			uiFileIteration++;//store next data into new file
		}
		const streampos endPositionReaded = inputBitStream.getStream()?
			inputBitStream.getStream()->tellg():((streampos)(0));
		if ( endPositionReaded != endPosition ){
			cerr<<"Error: The endposition while storing was "<<endPosition<<
				", but after reading the optional part from the stream it is "<<
				endPositionReaded<<endl;
			iReturn++;
		}
		
		//compare restored with stored object
		if ( 0 <= outStatus ){
			if ( ! optionalpart.equal( optionalpartReaded ) ){
				cerr<<"Error: The restore optional part dosn't equal the stored optional part."<<endl;
				iReturn++;
				
				static unsigned int uiRestoreIteration = 1;
				sprintf ( szFileNameBuffer, "%s%s%u%s%s", DIR_OUTPUT, "storeOpPartOrg", uiRestoreIteration, "Error" ,".xml" );
				ofstream * pOutFileXml = new ofstream( szFileNameBuffer );
				cout<<"Storing orginal optional part in the Xml-format to the file "<< szFileNameBuffer <<" . "<<endl;
				optionalpart.storeXml( *pOutFileXml );
				delete pOutFileXml;
				sprintf ( szFileNameBuffer, "%s%s%u%s%s", DIR_OUTPUT, "storeOpPartRest", uiRestoreIteration, "Error" ,".xml" );
				pOutFileXml = new ofstream( szFileNameBuffer );
				cout<<"Storing restored optional part in the Xml-format to the file "<< szFileNameBuffer <<" . "<<endl;
				optionalpartReaded.storeXml( *pOutFileXml );
				delete pOutFileXml;
				uiRestoreIteration++;
			}
			const unsignedLongFib ulCompressedSizeOfReaded =
				optionalpartReaded.getCompressedSize();
			if ( ulCompressedSize != ulCompressedSizeOfReaded ){
				cerr<<"Error: The size of the original optional part is "<<
					ulCompressedSize<<" , but that of the restored is "<<
					ulCompressedSizeOfReaded<<endl;
				iReturn++;
			}
			
		}else{
			cerr<<"Error: No optional part restored ."<<endl;
			iReturn++;
		}
		if ( uiCorrectCompressionType != 0 ){
			//output data to compare compressed an uncompressed size
			const bool bCompressionTypeSet =
				optionalpart.setCompressionType( 0 );
			if ( bCompressionTypeSet ){
				
				cout<<"The compression type "<<0<<
					" was correctly "<<(bCompressionTypeSet?"":"not ")
					<<"set. "<<endl;
			}else{
				cerr<<"Error: The compression type "<<0<<
					" was "<<(bCompressionTypeSet?"":"not ")
					<<"set, but shouldn't be. "<<endl;
				iReturn++;
			}
			const unsignedLongFib ulUncompressedSize =
				optionalpart.getCompressedSize();
			cout<<"The uncompressed size is: "<<ulUncompressedSize<<
				"  The compressed size is: "<<ulCompressedSize<<endl;
		}
		
	}
	
	return iReturn;
}
















