/**
 * @file tDomains
 * file name: tDomains.cpp
 * @author Betti Oesterholz
 * @date 10.06.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cDomains.
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
 * This file contains the test for the class cDomains,
 * which represents an domain list in an root -element.
 *
 *
 * What's tested of class cDomains:
 * 	- cDomains();
 * 	- unsignedIntFib getNumberOfDomains() const;
 * 	- cDomain * getDomain( unsignedIntFib iDomainNumber ) const;
 * 	- cTypeElement * getType( unsignedIntFib iTypeNumber ) const;
 * 	- cDomain * getDomainForElement( const cTypeElement &type ) const;
 * 	- cDomain * getDirectDomain( const unsignedIntFib iDomainNumber ) const;
 * 	- cDomain * getDomainForReferenceDomain( cDomainReference * pDomainReference, cTypeElement * pTypeElementForWhich = NULL ) const;
 * 	- unsignedIntFib addDomain( const cTypeElement &type, const cDomain &domain );
 * 	- unsignedIntFib addDomain( const cTypeElement &type, cDomain * domain );
 * 	- unsignedIntFib setStandardDomain( const cTypeElement &type );
 * 	- bool deleteDomain( unsignedIntFib iDomainNumber );
 * 	- bool deleteDomain( const cTypeElement &type );
 * 	- cDomains *clone() const;
 * 	- bool equal( const cDomains &domains ) const;
 * 	- bool operator==( const cDomains &domains ) const;
 * 	- cDomains & operator=( const cDomains &domains )
 * 	- bool storeXml( ostream & ostream, string szName=string("domains") ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 *
 * Call: tDomains [MAX_RAND_TEST_SIZE]
 * Parameter:
 * 	MAX_RAND_TEST_SIZE: a number for the size of random tests
 *
 */
/*
History:
07.06.2009  Oesterholz  created
12.11.2009  Oesterholz  store*() and getCompressedSize() tested
13.05.2010  Oesterholz  the ordering of bits for the compressed storing corrected
30.03.2011  Oesterholz  storing to binary stream
16.02.2012  Oesterholz  testDomainReference() implemented for cDomainReference
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
28.01.2013  Oesterholz  COLOR_SW changed to COLOR_GRAYSCALE
*/

#include "version.h"

#include "cDomains.h"
#include "cTypeDimension.h"
#include "cTypeProperty.h"
#include "cTypeInVar.h"
#include "cTypeArea.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cDomainReference.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <iomanip>
#include <ctime>

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif

using namespace fib;
using namespace std;

int testAddDomain_GetNumberOfDomains( unsigned long &ulTestphase );
int testAddDomain_GetDomainForElement( unsigned long &ulTestphase );
int testSetStandardDomain( unsigned long &ulTestphase );
int testDeleteDomain( unsigned long &ulTestphase );
int testGetType( unsigned long &ulTestphase );
int testClone( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testAssignation( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );
int testDomainReference( unsigned long &ulTestphase );

//the size of the random tests
unsigned long MAX_RAND_TEST_SIZE = 256;


int main(int argc,char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	if ( argc >= 2 ){
		//one parameter given; read parameter iterations
		MAX_RAND_TEST_SIZE = atol( argv[ 1 ] );
		if ( MAX_RAND_TEST_SIZE < 1 ){
			MAX_RAND_TEST_SIZE = 1;
		}
	}
	
	cout<<endl<<"Running Test for cDomains methods"<<endl;
	cout<<      "================================="<<endl;
	
	iReturn += testAddDomain_GetNumberOfDomains( ulTestphase );
	iReturn += testAddDomain_GetDomainForElement( ulTestphase );
	iReturn += testSetStandardDomain( ulTestphase );
	iReturn += testDeleteDomain( ulTestphase );
	iReturn += testGetType( ulTestphase );
	iReturn += testClone( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testAssignation( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testDomainReference( ulTestphase );

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
};


/**
 * This method tests the addDomain() and getNumberOfDomains()
 * methods of the cDomains class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testAddDomain_GetNumberOfDomains( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing an simple domain list addDomain() and getNumberOfDomains() methods"<<endl;


	//check construktor
	cDomains testDomains1;

	cTypeDimension testTypeDimension1( 1 );
	cTypeDimension testTypeDimension2( 2 );

	cDomainNaturalNumberBit domainNaturalNumberBit1(1);


	//check the getNumberOfDomains() methode from cDomains
	if ( testDomains1.getNumberOfDomains() == 0 ){
	
		cout<<"The number of elements in the new domainlist is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomains1.getNumberOfDomains()<<" but should be 0."<<endl;
		iReturn++;
	}

	cout<<"testDomains1.addDomain( testTypeDimension1, domainNaturalNumberBit1 ) "<<endl;
	testDomains1.addDomain( testTypeDimension1, domainNaturalNumberBit1 );

	//check the getNumberOfDomains() methode from cDomains
	if ( testDomains1.getNumberOfDomains() == 1 ){
	
		cout<<"The number of elements in the new domainlist is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomains1.getNumberOfDomains()<<" but should be 1."<<endl;
		iReturn++;
	}

	cout<<"testDomains1.addDomain( testTypeDimension1, domainNaturalNumberBit1 ) "<<endl;
	testDomains1.addDomain( testTypeDimension1, domainNaturalNumberBit1 );

	//check the getNumberOfDomains() methode from cDomains
	if ( testDomains1.getNumberOfDomains() == 1 ){
	
		cout<<"The number of elements in the new domainlist is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomains1.getNumberOfDomains()<<" but should be 1."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the addDomain() and getDomainForElement()
 * methods of the cDomains class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testAddDomain_GetDomainForElement( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : adding secound type; Testing addDomain() and getDomainForElement() methods"<<endl;

	cDomains testDomains1;

	cTypeDimension testTypeDimensionD1( 1 );
	cTypeDimension testTypeDimensionD3( 3 );
	cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB );
	cTypeProperty testTypePropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );

	//create vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	cDomainVector vectorDomainD1( vecDomains1 );
	delete vecDomains1[ 0 ];
	
	//create vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 1 );
	cDomainVector vectorDomainD2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];

	//create vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector vectorDomainD3Standard( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	//create vector domain with two elements
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 14 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 12 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 12 );
	cDomainVector vectorDomain2D3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];


	cout<<"testDomains1.addDomain( testTypeDimensionD1, vectorDomainD1 ) "<<endl;
	testDomains1.addDomain( testTypeDimensionD1, vectorDomainD1 );

	cout<<"testDomains1.addDomain( testTypePropertyColorRGB, vectorDomainD3Standard ) "<<endl;
	unsignedIntFib iInsertPosition = testDomains1.addDomain(
		testTypePropertyColorRGB, vectorDomainD3Standard );

	//check the getNumberOfDomains() methode from cDomains
	if ( testDomains1.getNumberOfDomains() == 2 ){
	
		cout<<"The number of elements in the new domainlist is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomains1.getNumberOfDomains()<<" but should be 2."<<endl;
		iReturn++;
	}

	//check the method getDomainForElement()
	cDomain *domain = testDomains1.getDomainForElement( testTypePropertyColorRGB );
	
	//check if the domainpointer points to the original domain
	if ( domain != &vectorDomainD3Standard ){
	
		cout<<"The domainpointer is correctly not the vectorDomainD3Standard . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is the domain vectorDomainD3Standard  ."<<endl;
		iReturn++;
	}

	if ( (*domain) == vectorDomainD3Standard ){
	
		cout<<"The domain of for the type testTypePropertyColorRGB is correctly the vectorDomainD3Standard domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for testTypePropertyColorRGB is not the vectorDomainD3Standard domain."<<endl;
		iReturn++;
	}

	//check the method getDomainForElement()
	domain = testDomains1.getDomainForElement( testTypeDimensionD1 );
	
	//check if the domainpointer points to the original domain
	if ( domain != &vectorDomainD1 ){
	
		cout<<"The domainpointer is correctly not the vectorDomainD1 . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is the domain vectorDomainD1  ."<<endl;
		iReturn++;
	}
	
	if ( (*domain) == vectorDomainD1 ){
	
		cout<<"The domain of for the type testTypeDimensionD1 is correctly the vectorDomainD1 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for testTypeDimensionD1 is not the vectorDomainD1 domain."<<endl;
		iReturn++;
	}

	//check the method getDomain()
	domain = testDomains1.getDomain( iInsertPosition );
	
	//check if the domainpointer points to the original domain
	if ( domain != &vectorDomainD3Standard ){
	
		cout<<"The domainpointer is correctly not the vectorDomainD3Standard . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is the domain vectorDomainD3Standard  ."<<endl;
		iReturn++;
	}
	
	if ( (*domain) == vectorDomainD3Standard  ){
	
		cout<<"The given domain for the insert position "<<
			iInsertPosition<<" is correctly the vectorDomainD3Standard domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the insert position "<<
			iInsertPosition<<" is not the vectorDomainD3Standard domain."<<endl;
		iReturn++;
	}

	//check the method getDomainForElement()
	domain = testDomains1.getDomainForElement( testTypePropertyColorSW );
	
	if ( domain == NULL ){
	
		cout<<"Correct: The type testTypePropertyColorSW don't exists, because it wasn't added. "<<endl;

	}else{
		cerr<<"Error: The type testTypePropertyColorSW exists, but it wasn't added."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : adding secound type a secound time with an other domain"<<endl<<flush;
	

	iInsertPosition=testDomains1.addDomain( testTypePropertyColorRGB, vectorDomain2D3 );
	cout<<"testDomains1.addDomain( testTypePropertyColorRGB, vectorDomain2D3 ) "<<endl;

	//check the getNumberOfDomains() methode from cDomains
	if ( testDomains1.getNumberOfDomains() == 2 ){
	
		cout<<"The number of elements in the new domainlist is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomains1.getNumberOfDomains()<<" but should be 2."<<endl;
		iReturn++;
	}

	//check the method getDomainForElement()
	domain = testDomains1.getDomainForElement( testTypePropertyColorRGB );
	
	//check if the domainpointer points to the original domain
	if ( domain != &vectorDomain2D3 ){
	
		cout<<"The domainpointer is correctly not the vectorDomain2D3 . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is the domain vectorDomain2D3  ."<<endl;
		iReturn++;
	}
	
	if ( (*domain) == vectorDomain2D3 ){
	
		cout<<"The domain of for the type testTypePropertyColorRGB is correctly the vectorDomain2D3 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for testTypePropertyColorRGB is not the vectorDomain2D3 domain."<<endl;
		iReturn++;
	}

	//check the method getDomain()
	domain = testDomains1.getDomain( iInsertPosition );

	//check if the domainpointer points to the original domain
	if ( domain != &vectorDomain2D3 ){
	
		cout<<"The domainpointer is correctly not the vectorDomain2D3 . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is the domain vectorDomain2D3  ."<<endl;
		iReturn++;
	}
	if ( (*domain)==vectorDomain2D3  ){
	
		cout<<"The given domain for the insert position "<<
			iInsertPosition<<" is correctly the vectorDomain2D3 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the insert position "<<
			iInsertPosition<<" is not the vectorDomain2D3 domain."<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : adding secound type a secound time with an same domain again"<<endl<<flush;
	
	iInsertPosition=testDomains1.addDomain( testTypePropertyColorRGB, vectorDomain2D3 );
	cout<<"testDomains1.addDomain( testTypePropertyColorRGB, vectorDomain2D3 ) "<<endl;

	//check the getNumberOfDomains() methode from cDomains
	if ( testDomains1.getNumberOfDomains() == 2 ){
	
		cout<<"The number of elements in the new domainlist is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomains1.getNumberOfDomains()<<" but should be 2."<<endl;
		iReturn++;
	}

	//check the method getDomainForElement()
	domain = testDomains1.getDomainForElement( testTypePropertyColorRGB );
	
	//check if the domainpointer points to the original domain
	if ( domain != &vectorDomain2D3 ){
	
		cout<<"The domainpointer is correctly not the vectorDomain2D3 . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is the domain vectorDomain2D3  ."<<endl;
		iReturn++;
	}
	if ( (*domain) == vectorDomain2D3 ){
	
		cout<<"The domain of for the type testTypePropertyColorRGB is correctly the vectorDomain2D3 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for testTypePropertyColorRGB is not the vectorDomain2D3 domain."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : adding third type with incompatible domain"<<endl<<flush;

	iInsertPosition=testDomains1.addDomain( testTypePropertyColorSW, vectorDomainD2 );
	cout<<"testDomains1.addDomain( testTypePropertyColorSW, vectorDomainD2 ) "<<endl;

	//check the getNumberOfDomains() methode from cDomains
	if ( testDomains1.getNumberOfDomains() == 3 ){
	
		cout<<"The number of elements in the new domainlist is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomains1.getNumberOfDomains()<<" but should be 3."<<endl;
		iReturn++;
	}

	//check the method getDomain() for type 2 (old type dosn't get overwritten)
	//check the method getDomainForElement()
	domain = testDomains1.getDomainForElement( testTypeDimensionD1 );
	
	if ( (*domain) == vectorDomainD1 ){
	
		cout<<"The domain of for the type testTypeDimensionD1 is correctly the vectorDomainD1 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for testTypeDimensionD1 is not the vectorDomainD1 domain."<<endl;
		iReturn++;
	}

	//check the method getDomainForElement()
	domain = testDomains1.getDomainForElement( testTypePropertyColorRGB );
	
	if ( (*domain) == vectorDomain2D3 ){
	
		cout<<"The domain of for the type testTypePropertyColorRGB is correctly the vectorDomain2D3 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for testTypePropertyColorRGB is not the vectorDomain2D3 domain."<<endl;
		iReturn++;
	}
	
	//check the method getDomain()
	domain = testDomains1.getDomainForElement( testTypePropertyColorSW );
	
	if ( (*domain) == vectorDomainD1 ){
	
		cout<<"The domain of for the type testTypePropertyColorSW is correctly the vectorDomainD1 standard domain. "<<endl;
	}else{
		cerr<<"Error: The given domain for testTypePropertyColorSW is not the vectorDomainD1 standard domain."<<endl;
		iReturn++;
	}

	//check the method getDomain()
	domain = testDomains1.getDomain( iInsertPosition );

	if ( (*domain) == vectorDomainD1 ){
	
		cout<<"The domain of for the iInsertPosition="<<
			iInsertPosition<<" is correctly the vectorDomainD1 standard domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the iInsertPosition="<<
			iInsertPosition<<" is not the vectorDomainD1 standard domain."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : adding a refernce for a domain"<<endl;

	cout<<"cDomains testDomains2 "<<endl;
	cDomains testDomains2;

	cout<<"testDomains2.addDomain( testTypeDimensionD1, &vectorDomainD1 ) "<<endl;
	testDomains2.addDomain( testTypeDimensionD1, &vectorDomainD1 );

	//check the getNumberOfDomains() methode from cDomains
	if ( testDomains2.getNumberOfDomains() == 1 ){
	
		cout<<"The number of elements in the new domainlist is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomains2.getNumberOfDomains()<<" but should be 1."<<endl;
		iReturn++;
	}

	//check the method getDomainForElement()
	cout<<"domain = testDomains2.getDomainForElement( testTypeDimensionD3 );"<<endl;
	domain = testDomains2.getDomainForElement( testTypeDimensionD3 );
	
	//check if the domainpointer points to the original domain
	if ( domain == &vectorDomainD1 ){
	
		cout<<"The domainpointer is correctly the vectorDomainD1 . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is not the domain vectorDomainD1  ."<<endl;
		iReturn++;
	}

	if ( (*domain) == vectorDomainD1 ){
	
		cout<<"The domain of for the type testTypeDimensionD3 is correctly the vectorDomainD1 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for testTypeDimensionD3 is not the vectorDomainD1 domain."<<endl;
		iReturn++;
	}
	
	cout<<"testDomains2.addDomain( testTypeDimensionD3, vectorDomain2D3 ) "<<endl;
	testDomains2.addDomain( testTypeDimensionD3, vectorDomain2D3 );

	//check the getNumberOfDomains() methode from cDomains
	if ( testDomains2.getNumberOfDomains() == 1 ){
	
		cout<<"The number of elements in the new domainlist is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomains2.getNumberOfDomains()<<" but should be 1."<<endl;
		iReturn++;
	}

	//check the method getDomainForElement()
	cout<<"domain = testDomains2.getDomainForElement( testTypeDimensionD1 );"<<endl;
	domain = testDomains2.getDomainForElement( testTypeDimensionD1 );
	
	//check if the domainpointer points to the original domain
	if ( domain != &vectorDomain2D3 ){
	
		cout<<"The domainpointer is correctly not the vectorDomain2D3 . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is the domain vectorDomain2D3  ."<<endl;
		iReturn++;
	}

	if ( (*domain) == vectorDomain2D3 ){
	
		cout<<"The domain of for the type testTypeDimensionD1 is correctly the vectorDomain2D3 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for testTypeDimensionD1 is not the vectorDomain2D3 domain."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the testSetStandardDomain() methods of the cDomains
 * class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testSetStandardDomain( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing an simple domain list setStandardDomain() methods for testTypeDimension2"<<endl;

	//check construktor
	cDomains testDomains1;

	cout<<"cTypeDimension testTypeDimensionD1( 1 ); "<<endl<<flush;
	cTypeDimension testTypeDimensionD1( 1 );
	cout<<"cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB ) "<<endl<<flush;
	cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB );
	cout<<"cTypeProperty testTypePropertyColorSW( cTypeProperty::COLOR_GRAYSCALE ) "<<endl<<flush;
	cTypeProperty testTypePropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );

	//create vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomainD1( vecDomains1 ) "<<endl<<flush;
	cDomainVector vectorDomainD1( vecDomains1 );
	delete vecDomains1[ 0 ];

	//create vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainD3( vecDomains3 ) "<<endl<<flush;
	cDomainVector vectorDomainD3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];



	cout<<"testDomains1.addDomain( testTypeDimensionD1, vectorDomainD1 ) "<<endl<<flush;
	testDomains1.addDomain( testTypeDimensionD1, vectorDomainD1 );
	cout<<"testDomains1.addDomain( testTypePropertyColorRGB, vectorDomainD3 ) "<<endl;
	testDomains1.addDomain( testTypePropertyColorRGB, vectorDomainD3 );
	cout<<"testDomains1.addDomain( testTypePropertyColorSW, vectorDomainD1 ) "<<endl;
	testDomains1.addDomain( testTypePropertyColorSW, vectorDomainD1 );

	//check the method getDomain()
	cDomain *domain=testDomains1.getDomainForElement( testTypePropertyColorRGB );

	if ( (*domain)==vectorDomainD3 ){
	
		cout<<"The domain of for the testTypePropertyColorRGB is correctly the vectorDomainD3 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypePropertyColorRGB is not the vectorDomainD3 domain."<<endl;
		iReturn++;
	}

	//check the method setStandardDomain()
	testDomains1.setStandardDomain( testTypePropertyColorRGB );
	cDomain * pDomainStandard = testTypePropertyColorRGB.getStandardDomain();

	domain = testDomains1.getDomainForElement( testTypePropertyColorRGB );
	
	if ( ! ((*domain) == vectorDomainD3 ) ){
	
		cout<<"The domain of for the testTypePropertyColorRGB is correctly not the vectorDomainD3 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypePropertyColorRGB is the vectorDomainD3 domain."<<endl;
		iReturn++;
	}

	
	if ( (*domain) == (*pDomainStandard) ){
	
		cout<<"The domain of for the testTypePropertyColorRGB is correctly the standard domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypePropertyColorRGB is not the standard domain."<<endl;
		iReturn++;
	}
	delete pDomainStandard;

	//check the method getDomain()
	domain = testDomains1.getDomainForElement( testTypeDimensionD1 );

	if ( (*domain) == vectorDomainD1 ){
	
		cout<<"The domain of for the testTypeDimensionD1 is correctly the vectorDomainD1 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypeDimensionD1 is not the vectorDomainD1 domain."<<endl;
		iReturn++;
	}
	
	//check the method setStandardDomain()
	testDomains1.setStandardDomain( testTypeDimensionD1 );
	pDomainStandard = testTypeDimensionD1.getStandardDomain();

	domain = testDomains1.getDomainForElement( testTypeDimensionD1 );
	
	if ( (*domain) == (*pDomainStandard) ){
	
		cout<<"The domain of for the testTypeDimensionD1 is correctly the standard domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypeDimensionD1 is not the standard domain."<<endl;
		iReturn++;
	}
	delete pDomainStandard;

	return iReturn;
}

/**
 * This method tests the deleteDomain() methods of the cDomains
 * class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testDeleteDomain( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleteDomain() of testTypeDimension2 for an listposition"<<endl<<flush;

	//check construktor
	cDomains testDomains1;

	cout<<"cTypeDimension testTypeDimensionD1( 1 ); "<<endl<<flush;
	cTypeDimension testTypeDimensionD1( 1 );
	cout<<"cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB ) "<<endl<<flush;
	cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB );
	cout<<"cTypeProperty testTypePropertyColorSW( cTypeProperty::COLOR_GRAYSCALE ) "<<endl<<flush;
	cTypeProperty testTypePropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );

	//create vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomainD1( vecDomains1 ) "<<endl<<flush;
	cDomainVector vectorDomainD1( vecDomains1 );
	delete vecDomains1[ 0 ];

	//create vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainD3( vecDomains3 ) "<<endl<<flush;
	cDomainVector vectorDomainD3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];



	cout<<"testDomains1.addDomain( testTypeDimensionD1, vectorDomainD1 ) "<<endl<<flush;
	testDomains1.addDomain( testTypeDimensionD1, vectorDomainD1 );
	cout<<"testDomains1.addDomain( testTypePropertyColorRGB, vectorDomainD3 ) "<<endl;
	unsignedIntFib iInsertPosition = testDomains1.addDomain( testTypePropertyColorRGB, vectorDomainD3 );
	cout<<"testDomains1.addDomain( testTypePropertyColorSW, vectorDomainD1 ) "<<endl;
	testDomains1.addDomain( testTypePropertyColorSW, vectorDomainD1 );

	//check the deleteDomain() methode from cDomains
	if ( testDomains1.deleteDomain( iInsertPosition ) ){
	
		cout<<"The delete method returns correctly true. "<<endl;
	}else{
		cerr<<"Error: The delete method returns false."<<endl;
		iReturn++;
	}

	//check the method getDomainForElement()
	cDomain * domain = testDomains1.getDomainForElement( testTypePropertyColorRGB );
	
	if ( domain == NULL ){
	
		cout<<"Correct: The type testTypePropertyColorRGB don't exists, because it was deleted. "<<endl;

	}else{
		cerr<<"Error: The type testTypePropertyColorRGB exists, but it was deleted."<<endl;
		iReturn++;
	}

	//check the getNumberOfDomains() methode from an listposition
	if ( testDomains1.getNumberOfDomains() == 2 ){
	
		cout<<"The number of elements in the new domainlist is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomains1.getNumberOfDomains()<<" but should be 2."<<endl;
		iReturn++;
	}

	//check if remaining types and domains are correctl
	
	//check the method getDomain()
	domain = testDomains1.getDomainForElement( testTypeDimensionD1 );
	
	if ( domain == NULL ){
		cerr<<"Error: The given domain for the testTypeDimensionD1 is NULL."<<endl;
		iReturn++;
	}else if ( (*domain) == vectorDomainD1 ){
	
		cout<<"The domain of for the testTypeDimensionD1 is correctly the vectorDomainD1 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypeDimensionD1 is not the vectorDomainD1 domain."<<endl;
		iReturn++;
	}

	//check the method getDomain()
	domain=testDomains1.getDomainForElement( testTypePropertyColorSW );
	
	if ( domain == NULL ){
		cerr<<"Error: The given domain for the testTypePropertyColorSW is NULL."<<endl;
		iReturn++;
	}else if ( (*domain) == vectorDomainD1 ){
	
		cout<<"The domain of for the testTypePropertyColorSW is correctly the vectorDomainD1 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypePropertyColorSW is not the vectorDomainD1 domain."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleteDomain() of testTypeDimension2 for an type"<<endl<<flush;

	iInsertPosition = testDomains1.addDomain( testTypePropertyColorRGB, vectorDomainD3 );
	cout<<"testDomains1.addDomain( testTypePropertyColorRGB, vectorDomainD3 ) "<<endl;

	cout<<"testDomains1.deleteDomain( testTypePropertyColorRGB ) "<<endl;
	
	//check the deleteDomain() methode from cDomains
	if ( testDomains1.deleteDomain( testTypePropertyColorRGB ) ){
	
		cout<<"The delete method returns correctly true. "<<endl;
	}else{
		cerr<<"Error: The delete method returns false."<<endl;
		iReturn++;
	}

	//check the method getDomainForElement()
	domain=testDomains1.getDomainForElement( testTypePropertyColorRGB );
	
	if ( domain == NULL ){
	
		cout<<"Correct: The type testTypePropertyColorRGB don't exists, because it was deleted. "<<endl;

	}else{
		cerr<<"Error: The type testTypePropertyColorRGB exists, but it was deleted."<<endl;
		iReturn++;
	}

	//check the getNumberOfDomains() methode from an type
	if ( testDomains1.getNumberOfDomains() == 2 ){
	
		cout<<"The number of elements in the new domainlist is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomains1.getNumberOfDomains()<<" but should be 2."<<endl;
		iReturn++;
	}

	cout<<"testDomains1.deleteDomain( testTypePropertyColorRGB ) "<<endl;
	//check the deleteDomain() methode from an type
	if ( !testDomains1.deleteDomain( testTypePropertyColorRGB ) ){
	
		cout<<"The delete method returns correctly false. The type was deleted befor."<<endl;
	}else{
		cerr<<"Error: The delete method returns true. The type was deleted befor"<<endl;
		iReturn++;
	}

	//check the getNumberOfDomains() methode from cDomains
	if ( testDomains1.getNumberOfDomains() == 2 ){
	
		cout<<"The number of elements in the new domainlist is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomains1.getNumberOfDomains()<<" but should be 2."<<endl;
		iReturn++;
	}

	//check if remaining types and domains are correctl
	
	//check the method getDomain()
	domain=testDomains1.getDomainForElement( testTypeDimensionD1 );
	
	if ( (*domain) == vectorDomainD1 ){
	
		cout<<"The domain of for the testTypeDimensionD1 is correctly the vectorDomainD1 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypeDimensionD1 is not the vectorDomainD1 domain."<<endl;
		iReturn++;
	}

	//check the method getDomain()
	domain=testDomains1.getDomainForElement( testTypePropertyColorSW );
	
	if ( (*domain) == vectorDomainD1 ){
	
		cout<<"The domain of for the testTypePropertyColorSW is correctly the vectorDomainD1 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypePropertyColorSW is not the vectorDomainD1 domain."<<endl;
		iReturn++;
	}

	return iReturn;
}

/**
 * This method tests the getType() method of the cDomains
 * class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testGetType( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing getType() method"<<endl<<flush;

	//check construktor
	cDomains testDomains1;

	cout<<"cTypeDimension testTypeDimensionD1( 1 ); "<<endl<<flush;
	cTypeDimension testTypeDimensionD1( 1 );
	cout<<"cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB ) "<<endl<<flush;
	cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB );

	//create vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomainD1( vecDomains1 ) "<<endl<<flush;
	cDomainVector vectorDomainD1( vecDomains1 );
	delete vecDomains1[ 0 ];

	//create vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainD3( vecDomains3 ) "<<endl<<flush;
	cDomainVector vectorDomainD3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];


	//check the getType() methode from cDomains
	if ( testDomains1.getType( 1 ) == NULL ){
		cout<<"Ther is correctly the nullpointer NULL returned, becaus ther"<<
			" is no element in the domains object. "<<endl;
	}else{
		cerr<<"Error: It was not the nullpointer NULL for the type returned,"<<
			" but ther is no element in the domains object. "<<endl;
		iReturn++;
	}

	cout<<"testDomains1.addDomain( testTypeDimensionD1, vectorDomainD1 ) "<<endl;
	unsignedIntFib iInsertPosition=testDomains1.addDomain( testTypeDimensionD1, vectorDomainD1 );

	//check the getType() methode from cDomains
	if ( *(testDomains1.getType( iInsertPosition )) == testTypeDimensionD1 ){
		cout<<"The type on position "<<iInsertPosition<<
			" is correctly testTypeDimensionD1. "<<endl;
	}else{
		cerr<<"Error: The type on position "<<iInsertPosition<<
			" is not testTypeDimensionD1."<<endl;
		iReturn++;
	}

	cout<<"testDomains1.addDomain( testTypePropertyColorRGB, vectorDomainD3 ) "<<endl;
	iInsertPosition=testDomains1.addDomain( testTypePropertyColorRGB, vectorDomainD3 );
	
	//check the getType() methode from cDomains
	if ( *(testDomains1.getType( iInsertPosition )) == testTypePropertyColorRGB ){
		cout<<"The type on position "<<iInsertPosition<<
			" is correctly testTypePropertyColorRGB. "<<endl;
	}else{
		cerr<<"Error: The type on position "<<iInsertPosition<<
			" is not testTypePropertyColorRGB."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the clone() method of the cDomains
 * class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testClone( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing clone() method on an empty cDomains object"<<endl<<flush;

	//check construktor
	cout<<"cDomains testDomains1"<<endl;
	cDomains testDomains1;

	cout<<"testDomainsClone1 = testDomains1.clone()"<<endl;
	cDomains *testDomainsClone1 = testDomains1.clone();

	//check the getNumberOfDomains() methode from an type
	if ( testDomainsClone1->getNumberOfDomains() == 0 ){
	
		cout<<"The number of elements in the cloned domainlist is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the cloned domainlist is "<<
			testDomainsClone1->getNumberOfDomains()<<" but should be 0."<<endl;
		iReturn++;
	}
	delete testDomainsClone1;
	//check the getNumberOfDomains() methode from an type
	if ( testDomains1.getNumberOfDomains() == 0 ){
	
		cout<<"The number of elements in the new domainlist is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomains1.getNumberOfDomains()<<" but should be 0."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing clone() method"<<endl<<flush;

	cout<<"cTypeDimension testTypeDimensionD1( 1 ); "<<endl<<flush;
	cTypeDimension testTypeDimensionD1( 1 );
	cout<<"cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB ) "<<endl<<flush;
	cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB );
	cout<<"cTypeProperty testTypePropertyColorSW( cTypeProperty::COLOR_GRAYSCALE ) "<<endl<<flush;
	cTypeProperty testTypePropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );

	//create vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomainD1( vecDomains1 ) "<<endl<<flush;
	cDomainVector vectorDomainD1( vecDomains1 );
	delete vecDomains1[ 0 ];

	//create vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainD3( vecDomains3 ) "<<endl<<flush;
	cDomainVector vectorDomainD3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	cout<<"testDomains1.addDomain( testTypeDimensionD1, vectorDomainD1 ) "<<endl<<flush;
	testDomains1.addDomain( testTypeDimensionD1, vectorDomainD1 );
	cout<<"testDomains1.addDomain( testTypePropertyColorRGB, &vectorDomainD3 ) "<<endl;
	testDomains1.addDomain( testTypePropertyColorRGB, &vectorDomainD3 );
	cout<<"testDomains1.addDomain( testTypePropertyColorSW, vectorDomainD1 ) "<<endl;
	testDomains1.addDomain( testTypePropertyColorSW, vectorDomainD1 );

	cout<<"testDomainsClone1 = testDomains1.clone()"<<endl;
	testDomainsClone1 = testDomains1.clone();


	cout<<endl<<"Checking cloned domains object:"<<endl;
	//check the getNumberOfDomains() methode from an type
	if ( testDomainsClone1->getNumberOfDomains()==3 ){
	
		cout<<"The number of elements in the domainlist is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomainsClone1->getNumberOfDomains()<<" but should be 3."<<endl;
		iReturn++;
	}

	//check if no domains or types are lost
	cDomain *domain = testDomainsClone1->getDomainForElement( testTypeDimensionD1 );
	
	//check if the domainpointer points to the original domain
	if ( domain != &vectorDomainD1 ){
	
		cout<<"The domainpointer is correctly not the vectorDomainD1 . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is the domain vectorDomainD1  ."<<endl;
		iReturn++;
	}
	
	if ( (*domain) == vectorDomainD1 ){
	
		cout<<"The domain of for the testTypeDimensionD1 is correctly the vectorDomainD1 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypeDimensionD1 is not the vectorDomainD1 domain."<<endl;
		iReturn++;
	}

	domain = testDomainsClone1->getDomainForElement( testTypePropertyColorRGB );
	
	//check if the domainpointer points to the original domain
	if ( domain == &vectorDomainD3 ){
	
		cout<<"The domainpointer is correctly the vectorDomainD3 . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is not the domain vectorDomainD3  ."<<endl;
		iReturn++;
	}
	
	if ( (*domain)== vectorDomainD3 ){
	
		cout<<"The domain of for the testTypePropertyColorRGB is correctly the vectorDomainD3 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypePropertyColorRGB is not the vectorDomainD3 domain."<<endl;
		iReturn++;
	}

	domain = testDomainsClone1->getDomainForElement( testTypePropertyColorSW );
	
	//check if the domainpointer points to the original domain
	if ( domain != &vectorDomainD1 ){
	
		cout<<"The domainpointer is correctly not the vectorDomainD1 . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is the domain vectorDomainD1  ."<<endl;
		iReturn++;
	}
	if ( (*domain) == vectorDomainD1 ){
	
		cout<<"The domain of for the testTypePropertyColorSW is correctly the vectorDomainD1 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypePropertyColorSW is not the vectorDomainD1 domain."<<endl;
		iReturn++;
	}
	delete testDomainsClone1;

	cout<<endl<<"Checking original domains object:"<<endl;
	
	//check the getNumberOfDomains() methode from an type
	if ( testDomains1.getNumberOfDomains() == 3 ){
	
		cout<<"The number of elements in the domainlist is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of elements in the domainlist is "<<
			testDomains1.getNumberOfDomains()<<" but should be 3."<<endl;
		iReturn++;
	}
	
	//check if no domains or types are lost
	domain = testDomains1.getDomainForElement( testTypeDimensionD1 );
	
	//check if the domainpointer points to the original domain
	if ( domain != &vectorDomainD1 ){
	
		cout<<"The domainpointer is correctly not the vectorDomainD1 . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is the domain vectorDomainD1  ."<<endl;
		iReturn++;
	}
	
	if ( (*domain) == vectorDomainD1 ){
	
		cout<<"The domain of for the testTypeDimensionD1 is correctly the vectorDomainD1 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypeDimensionD1 is not the vectorDomainD1 domain."<<endl;
		iReturn++;
	}

	domain = testDomains1.getDomainForElement( testTypePropertyColorRGB );
	
	//check if the domainpointer points to the original domain
	if ( domain == &vectorDomainD3 ){
	
		cout<<"The domainpointer is correctly the vectorDomainD3 . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is not the domain vectorDomainD3  ."<<endl;
		iReturn++;
	}
	if ( (*domain)== vectorDomainD3 ){
	
		cout<<"The domain of for the testTypePropertyColorRGB is correctly the vectorDomainD3 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypePropertyColorRGB is not the vectorDomainD3 domain."<<endl;
		iReturn++;
	}

	domain = testDomains1.getDomainForElement( testTypePropertyColorSW );
	
	//check if the domainpointer points to the original domain
	if ( domain != &vectorDomainD1 ){
	
		cout<<"The domainpointer is correctly not the vectorDomainD1 . "<<endl;
	}else{
		cerr<<"Error: The domainpointer is the domain vectorDomainD1  ."<<endl;
		iReturn++;
	}
	if ( (*domain) == vectorDomainD1 ){
	
		cout<<"The domain of for the testTypePropertyColorSW is correctly the vectorDomainD1 domain. "<<endl;
		
	}else{
		cerr<<"Error: The given domain for the testTypePropertyColorSW is not the vectorDomainD1 domain."<<endl;
		iReturn++;
	}


	return iReturn;
}


/**
 * This method tests the equal() method and the operator== of two given
 * cDomains objects which are equal.
 *
 * @param domains1 the first domainlist to compare
 * @param szNameDomains1 the name of the first domainlist to compare
 * @param domains2 the secound domainlist to compare to
 * @param szNameDomains2 the name of the secound domainlist to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualDomains( const cDomains & domains1, const string & szNameDomains1,
	const cDomains & domains2, const string & szNameDomains2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( domains1.equal( domains2 ) ){
	
		cout<<"The "<<szNameDomains1<<" is equal to "<<szNameDomains2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomains1<<" is not equal to "<<
			szNameDomains2<<"."<<endl;
		iReturn++;
	}
	if ( domains1 == domains2 ){
	
		cout<<"The "<<szNameDomains1<<" is equal (operator==) to "<<
			szNameDomains2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomains1<<" is not equal (operator==) to "<<
			szNameDomains2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}

/**
 * This method tests the equal() method and the operator== of two given
 * cDomains objects which are not equal.
 *
 * @param domains1 the first domainlist to compare
 * @param szNameDomains1 the name of the first domainlist to compare
 * @param domains2 the secound domainlist to compare to
 * @param szNameDomains2 the name of the secound domainlist to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualDomains( const cDomains & domains1, const string & szNameDomains1,
	const cDomains & domains2, const string & szNameDomains2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! domains1.equal( domains2 ) ){
	
		cout<<"The "<<szNameDomains1<<" is not equal to "<<szNameDomains2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomains1<<" is equal to "<<
			szNameDomains2<<"."<<endl;
		iReturn++;
	}
	if ( ! (domains1 == domains2) ){
	
		cout<<"The "<<szNameDomains1<<" is not equal (operator==) to "<<
			szNameDomains2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomains1<<" is equal (operator==) to "<<
			szNameDomains2<<"."<<endl;
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

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equal method and the operator== "<<endl;

	cout<<endl<<"creating domainlists to compare:"<<endl<<endl;
	
	cout<<"cTypeDimension testTypeDimensionD1( 1 );"<<endl;
	cTypeDimension testTypeDimensionD1( 1 );
	cout<<"cTypeDimension testTypeDimensionD3( 3 );"<<endl;
	cTypeDimension testTypeDimensionD3( 3 );
	cout<<"cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB );"<<endl;
	cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB );
	cout<<"cTypeProperty testTypePropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );"<<endl;
	cTypeProperty testTypePropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );

	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomains1( 1 );
	cout<<"vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	cout<<"cDomainVector vectorDomain1D1( vecDomains1 );"<<endl;
	cDomainVector vectorDomain1D1( vecDomains1 );
	delete vecDomains1[ 0 ];

	cout<<"vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 13 );"<<endl;
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 13 );
	cout<<"cDomainVector vectorDomain2D1( vecDomains1 );"<<endl;
	cDomainVector vectorDomain2D1( vecDomains1 );
	delete vecDomains1[ 0 ];

	//create vector domain with tree elements
	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cout<<"vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	cout<<"vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 16 );
	cout<<"cDomainVector vectorDomain1D3( vecDomains3 );"<<endl;
	cDomainVector vectorDomain1D3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	//create vector domain with two elements
	cout<<"vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 14 );"<<endl;
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 14 );
	cout<<"vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 12 );"<<endl;
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 12 );
	cout<<"vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 12 );"<<endl;
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 12 );
	cout<<"cDomainVector vectorDomain2D3( vecDomains3 );"<<endl;
	cDomainVector vectorDomain2D3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	
	cout<<"cDomains domains1Empty;"<<endl;
	cDomains domains1Empty;
	cout<<"cDomains domains2Empty;"<<endl;
	cDomains domains2Empty;
	
	cout<<"cDomains domains1DimD1;"<<endl;
	cDomains domains1DimD1;
	cout<<"domains1DimD1.addDomain( testTypeDimensionD1, vectorDomain1D1 ) "<<endl;
	domains1DimD1.addDomain( testTypeDimensionD1, vectorDomain1D1 );

	cout<<"cDomains domains2DimRD1;"<<endl;
	cDomains domains2DimRD1;
	cout<<"domains2DimRD1.addDomain( testTypeDimensionD1, &vectorDomain1D1 ) "<<endl;
	domains2DimRD1.addDomain( testTypeDimensionD1, &vectorDomain1D1 );

	cout<<"cDomains domainsCswRD1;"<<endl;
	cDomains domainsCswRD1;
	cout<<"domainsCswRD1.addDomain( testTypePropertyColorSW, vectorDomain1D1 ) "<<endl;
	domainsCswRD1.addDomain( testTypePropertyColorSW, vectorDomain1D1 );

	cout<<"cDomains domainsDim2D1;"<<endl;
	cDomains domainsDim2D1;
	cout<<"domainsDim2D1.addDomain( testTypeDimensionD1, vectorDomain2D1 ) "<<endl;
	domainsDim2D1.addDomain( testTypeDimensionD1, vectorDomain2D1 );

	cout<<"cDomains domainsDimD3;"<<endl;
	cDomains domainsDimD3;
	cout<<"domainsDimD3.addDomain( testTypeDimensionD3, &vectorDomain1D3 ) "<<endl;
	domainsDimD3.addDomain( testTypeDimensionD3, &vectorDomain1D3 );

	cout<<"cDomains domainsDimD3St;"<<endl;
	cDomains domainsDimD3St;
	cout<<"domainsDimD3St.setStandardDomain( testTypeDimensionD3 ) "<<endl;
	domainsDimD3St.setStandardDomain( testTypeDimensionD3 );

	cout<<"cDomains domainsDim2D3;"<<endl;
	cDomains domainsDim2D3;
	cout<<"domainsDim2D3.addDomain( testTypeDimensionD3, &vectorDomain2D3 ) "<<endl;
	domainsDim2D3.addDomain( testTypeDimensionD3, &vectorDomain2D3 );

	cout<<"cDomains domainsDimD3CrD3;"<<endl;
	cDomains domainsDimD3CrD3;
	cout<<"domainsDimD3CrD3.addDomain( testTypeDimensionD3, vectorDomain1D3 ) "<<endl;
	domainsDimD3CrD3.addDomain( testTypeDimensionD3, vectorDomain1D3 );
	cout<<"domainsDimD3CrD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 ) "<<endl;
	domainsDimD3CrD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 );

	cout<<"cDomains domainsCrD3DimD3;"<<endl;
	cDomains domainsCrD3DimD3;
	cout<<"domainsCrD3DimD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 ) "<<endl;
	domainsCrD3DimD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 );
	cout<<"domainsCrD3DimD3.addDomain( testTypeDimensionD3, vectorDomain1D3 ) "<<endl;
	domainsCrD3DimD3.addDomain( testTypeDimensionD3, vectorDomain1D3 );

	cout<<"cDomains domainsDimD1CrD3;"<<endl;
	cDomains domainsDimD1CrD3;
	cout<<"domainsDimD1CrD3.addDomain( testTypeDimensionD1, vectorDomain1D1 ) "<<endl;
	domainsDimD1CrD3.addDomain( testTypeDimensionD1, vectorDomain1D1 );
	cout<<"domainsDimD1CrD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 ) "<<endl;
	domainsDimD1CrD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 );

	cout<<"cDomains domainsDimD3CrD3CswD1;"<<endl;
	cDomains domainsDimD3CrD3CswD1;
	cout<<"domainsDimD3CrD3CswD1.addDomain( testTypeDimensionD3, vectorDomain1D3 ) "<<endl;
	domainsDimD3CrD3CswD1.addDomain( testTypeDimensionD3, vectorDomain1D3 );
	cout<<"domainsDimD3CrD3CswD1.addDomain( testTypePropertyColorRGB, vectorDomain1D3 ) "<<endl;
	domainsDimD3CrD3CswD1.addDomain( testTypePropertyColorRGB, vectorDomain1D3 );
	cout<<"domainsDimD3CrD3CswD1.addDomain( testTypePropertyColorSW, vectorDomain1D1 ) "<<endl;
	domainsDimD3CrD3CswD1.addDomain( testTypePropertyColorSW, vectorDomain1D1 );

	cout<<"cDomains domainsCrD3DimD3CswD1;"<<endl;
	cDomains domainsCrD3DimD3CswD1;
	cout<<"domainsCrD3DimD3CswD1.addDomain( testTypePropertyColorRGB, vectorDomain1D3 ) "<<endl;
	domainsCrD3DimD3CswD1.addDomain( testTypePropertyColorRGB, vectorDomain1D3 );
	cout<<"domainsCrD3DimD3CswD1.addDomain( testTypeDimensionD3, vectorDomain1D3 ) "<<endl;
	domainsCrD3DimD3CswD1.addDomain( testTypeDimensionD3, vectorDomain1D3 );
	cout<<"domainsCrD3DimD3CswD1.addDomain( testTypePropertyColorSW, vectorDomain1D1 ) "<<endl;
	domainsCrD3DimD3CswD1.addDomain( testTypePropertyColorSW, vectorDomain1D1 );

	cout<<"cDomains domainsCrD3CswD1DimRD3;"<<endl;
	cDomains domainsCrD3CswD1DimRD3;
	cout<<"domainsCrD3CswD1DimRD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 ) "<<endl;
	domainsCrD3CswD1DimRD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 );
	cout<<"domainsCrD3CswD1DimRD3.addDomain( testTypePropertyColorSW, vectorDomain1D1 ) "<<endl;
	domainsCrD3CswD1DimRD3.addDomain( testTypePropertyColorSW, vectorDomain1D1 );
	cout<<"domainsCrD3CswD1DimRD3.addDomain( testTypeDimensionD3, &vectorDomain1D3 ) "<<endl;
	domainsCrD3CswD1DimRD3.addDomain( testTypeDimensionD3, &vectorDomain1D3 );

	cout<<"cDomains domainsCr2D3CswD1DimRD3;"<<endl;
	cDomains domainsCr2D3CswD1DimRD3;
	cout<<"domainsCr2D3CswD1DimRD3.addDomain( testTypePropertyColorRGB, vectorDomain2D3 ) "<<endl;
	domainsCr2D3CswD1DimRD3.addDomain( testTypePropertyColorRGB, vectorDomain2D3 );
	cout<<"domainsCr2D3CswD1DimRD3.addDomain( testTypePropertyColorSW, vectorDomain1D1 ) "<<endl;
	domainsCr2D3CswD1DimRD3.addDomain( testTypePropertyColorSW, vectorDomain1D1 );
	cout<<"domainsCr2D3CswD1DimRD3.addDomain( testTypeDimensionD3, &vectorDomain1D3 ) "<<endl;
	domainsCr2D3CswD1DimRD3.addDomain( testTypeDimensionD3, &vectorDomain1D3 );

	cout<<"cDomains domainsCrD3CswD1Dim2RD3;"<<endl;
	cDomains domainsCrD3CswD1Dim2RD3;
	cout<<"domainsCrD3CswD1Dim2RD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 ) "<<endl;
	domainsCrD3CswD1Dim2RD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 );
	cout<<"domainsCrD3CswD1Dim2RD3.addDomain( testTypePropertyColorSW, vectorDomain1D1 ) "<<endl;
	domainsCrD3CswD1Dim2RD3.addDomain( testTypePropertyColorSW, vectorDomain1D1 );
	cout<<"domainsCrD3CswD1Dim2RD3.addDomain( testTypeDimensionD3, &vectorDomain2D3 ) "<<endl;
	domainsCrD3CswD1Dim2RD3.addDomain( testTypeDimensionD3, &vectorDomain2D3 );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with domains1Empty
	cDomains * actualDomains = &domains1Empty;
	string szActualDomainsName = "domains1Empty";
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domains2Empty
	actualDomains = &domains2Empty;
	szActualDomainsName = "domains2Empty";
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domains1DimD1
	actualDomains = &domains1DimD1;
	szActualDomainsName = "domains1DimD1";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domains2DimRD1
	actualDomains = &domains2DimRD1;
	szActualDomainsName = "domains2DimRD1";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domainsCswRD1
	actualDomains = &domainsCswRD1;
	szActualDomainsName = "domainsCswRD1";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domainsDim2D1
	actualDomains = &domainsDim2D1;
	szActualDomainsName = "domainsDim2D1";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domainsDimD3
	actualDomains = &domainsDimD3;
	szActualDomainsName = "domainsDimD3";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domainsDimD3St
	actualDomains = &domainsDimD3St;
	szActualDomainsName = "domainsDimD3St";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domainsDim2D3
	actualDomains = &domainsDim2D3;
	szActualDomainsName = "domainsDim2D3";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domainsDimD3CrD3
	actualDomains = &domainsDimD3CrD3;
	szActualDomainsName = "domainsDimD3CrD3";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domainsCrD3DimD3
	actualDomains = &domainsCrD3DimD3;
	szActualDomainsName = "domainsCrD3DimD3";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domainsDimD1CrD3
	actualDomains = &domainsDimD1CrD3;
	szActualDomainsName = "domainsDimD1CrD3";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domainsDimD3CrD3CswD1
	actualDomains = &domainsDimD3CrD3CswD1;
	szActualDomainsName = "domainsDimD3CrD3CswD1";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domainsCrD3DimD3CswD1
	actualDomains = &domainsCrD3DimD3CswD1;
	szActualDomainsName = "domainsCrD3DimD3CswD1";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domainsCrD3CswD1DimRD3
	actualDomains = &domainsCrD3CswD1DimRD3;
	szActualDomainsName = "domainsCrD3CswD1DimRD3";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domainsCr2D3CswD1DimRD3
	actualDomains = &domainsCr2D3CswD1DimRD3;
	szActualDomainsName = "domainsCr2D3CswD1DimRD3";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	//compare with domainsCrD3CswD1Dim2RD3
	actualDomains = &domainsCrD3CswD1Dim2RD3;
	szActualDomainsName = "domainsCrD3CswD1Dim2RD3";
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1Empty, "domains1Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2Empty, "domains2Empty" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains1DimD1, "domains1DimD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domains2DimRD1, "domains2DimRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCswRD1, "domainsCswRD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D1, "domainsDim2D1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3, "domainsDimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3St, "domainsDimD3St" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDim2D3, "domainsDim2D3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3, "domainsDimD3CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3, "domainsCrD3DimD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD1CrD3, "domainsDimD1CrD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3DimD3CswD1, "domainsCrD3DimD3CswD1" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1DimRD3, "domainsCrD3CswD1DimRD3" );
	iReturn += testCompareTwoNotEqualDomains( *actualDomains, szActualDomainsName, domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3" );
	iReturn += testCompareTwoEqualDomains( *actualDomains, szActualDomainsName, domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3" );

	return iReturn;
}



/**
 * This method tests the operator= of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testAssignation( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the operator= "<<endl;

	cout<<endl<<"creating domainlists to compare:"<<endl<<endl;
	
	cout<<"cTypeDimension testTypeDimensionD1( 1 );"<<endl;
	cTypeDimension testTypeDimensionD1( 1 );
	cout<<"cTypeDimension testTypeDimensionD3( 3 );"<<endl;
	cTypeDimension testTypeDimensionD3( 3 );
	cout<<"cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB );"<<endl;
	cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB );
	cout<<"cTypeProperty testTypePropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );"<<endl;
	cTypeProperty testTypePropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );

	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomains1( 1 );
	cout<<"vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	cout<<"cDomainVector vectorDomain1D1( vecDomains1 );"<<endl;
	cDomainVector vectorDomain1D1( vecDomains1 );
	delete vecDomains1[ 0 ];


	cout<<"vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 13 );"<<endl;
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 13 );
	cout<<"cDomainVector vectorDomain2D1( vecDomains1 );"<<endl;
	cDomainVector vectorDomain2D1( vecDomains1 );
	delete vecDomains1[ 0 ];

	//create vector domain with tree elements
	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cout<<"vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	cout<<"vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 16 );
	cout<<"cDomainVector vectorDomain1D3( vecDomains3 );"<<endl;
	cDomainVector vectorDomain1D3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	//create vector domain with two elements
	cout<<"vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 14 );"<<endl;
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 14 );
	cout<<"vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 12 );"<<endl;
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 12 );
	cout<<"vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 12 );"<<endl;
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 12 );
	cout<<"cDomainVector vectorDomain2D3( vecDomains3 );"<<endl;
	cDomainVector vectorDomain2D3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	
	cout<<"cDomains domains1Empty;"<<endl;
	cDomains domains1Empty;
	
	cout<<"cDomains domains1DimD1;"<<endl;
	cDomains domains1DimD1;
	cout<<"domains1DimD1.addDomain( testTypeDimensionD1, vectorDomain1D1 ) "<<endl;
	domains1DimD1.addDomain( testTypeDimensionD1, vectorDomain1D1 );

	cout<<"cDomains domains1;"<<endl;
	cDomains domains1;

	iReturn += testCompareTwoEqualDomains( domains1Empty, "domains1Empty", domains1, "domains1" );
	iReturn += testCompareTwoNotEqualDomains( domains1DimD1, "domains1DimD1", domains1, "domains1" );
	cout<<"domains1 = domains1DimD1;"<<endl;
	domains1 = domains1DimD1;
	iReturn += testCompareTwoEqualDomains( domains1DimD1, "domains1DimD1", domains1, "domains1" );

	
	cout<<"cDomains domainsCswRD1;"<<endl;
	cDomains domainsCswRD1;
	cout<<"domainsCswRD1.addDomain( testTypePropertyColorSW, vectorDomain1D1 ) "<<endl;
	domainsCswRD1.addDomain( testTypePropertyColorSW, vectorDomain1D1 );

	iReturn += testCompareTwoNotEqualDomains( domainsCswRD1, "domainsCswRD1", domains1, "domains1" );
	cout<<"domains1 = domainsCswRD1;"<<endl;
	domains1 = domainsCswRD1;
	iReturn += testCompareTwoEqualDomains( domainsCswRD1, "domainsCswRD1", domains1, "domains1" );


	cout<<"cDomains domainsDim2D1;"<<endl;
	cDomains domainsDim2D1;
	cout<<"domainsDim2D1.addDomain( testTypeDimensionD1, vectorDomain2D1 ) "<<endl;
	domainsDim2D1.addDomain( testTypeDimensionD1, vectorDomain2D1 );

	iReturn += testCompareTwoNotEqualDomains( domainsDim2D1, "domainsDim2D1", domains1, "domains1" );
	cout<<"domains1 = domainsDim2D1;"<<endl;
	domains1 = domainsDim2D1;
	iReturn += testCompareTwoEqualDomains( domainsDim2D1, "domainsDim2D1", domains1, "domains1" );


	cout<<"cDomains domainsDim2D3;"<<endl;
	cDomains domainsDim2D3;
	cout<<"domainsDim2D3.addDomain( testTypeDimensionD3, &vectorDomain2D3 ) "<<endl;
	domainsDim2D3.addDomain( testTypeDimensionD3, &vectorDomain2D3 );

	iReturn += testCompareTwoNotEqualDomains( domainsDim2D3, "domainsDim2D3", domains1, "domains1" );
	cout<<"domains1 = domainsDim2D3;"<<endl;
	domains1 = domainsDim2D3;
	iReturn += testCompareTwoEqualDomains( domainsDim2D3, "domainsDim2D3", domains1, "domains1" );


	cout<<"cDomains domainsDimD3CrD3;"<<endl;
	cDomains domainsDimD3CrD3;
	cout<<"domainsDimD3CrD3.addDomain( testTypeDimensionD3, vectorDomain1D3 ) "<<endl;
	domainsDimD3CrD3.addDomain( testTypeDimensionD3, vectorDomain1D3 );
	cout<<"domainsDimD3CrD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 ) "<<endl;
	domainsDimD3CrD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 );

	iReturn += testCompareTwoNotEqualDomains( domainsDimD3CrD3, "domainsDimD3CrD3", domains1, "domains1" );
	cout<<"domains1 = domainsDimD3CrD3;"<<endl;
	domains1 = domainsDimD3CrD3;
	iReturn += testCompareTwoEqualDomains( domainsDimD3CrD3, "domainsDimD3CrD3", domains1, "domains1" );


	cout<<"cDomains domainsDimD1CrD3;"<<endl;
	cDomains domainsDimD1CrD3;
	cout<<"domainsDimD1CrD3.addDomain( testTypeDimensionD1, vectorDomain1D1 ) "<<endl;
	domainsDimD1CrD3.addDomain( testTypeDimensionD1, vectorDomain1D1 );
	cout<<"domainsDimD1CrD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 ) "<<endl;
	domainsDimD1CrD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 );

	iReturn += testCompareTwoNotEqualDomains( domainsDimD1CrD3, "domainsDimD1CrD3", domains1, "domains1" );
	cout<<"domains1 = domainsDimD1CrD3;"<<endl;
	domains1 = domainsDimD1CrD3;
	iReturn += testCompareTwoEqualDomains( domainsDimD1CrD3, "domainsDimD1CrD3", domains1, "domains1" );


	cout<<"cDomains domainsDimD3CrD3CswD1;"<<endl;
	cDomains domainsDimD3CrD3CswD1;
	cout<<"domainsDimD3CrD3CswD1.addDomain( testTypeDimensionD3, vectorDomain1D3 ) "<<endl;
	domainsDimD3CrD3CswD1.addDomain( testTypeDimensionD3, vectorDomain1D3 );
	cout<<"domainsDimD3CrD3CswD1.addDomain( testTypePropertyColorRGB, vectorDomain1D3 ) "<<endl;
	domainsDimD3CrD3CswD1.addDomain( testTypePropertyColorRGB, vectorDomain1D3 );
	cout<<"domainsDimD3CrD3CswD1.addDomain( testTypePropertyColorSW, vectorDomain1D1 ) "<<endl;
	domainsDimD3CrD3CswD1.addDomain( testTypePropertyColorSW, vectorDomain1D1 );

	iReturn += testCompareTwoNotEqualDomains( domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1", domains1, "domains1" );
	cout<<"domains1 = domainsDimD3CrD3CswD1;"<<endl;
	domains1 = domainsDimD3CrD3CswD1;
	iReturn += testCompareTwoEqualDomains( domainsDimD3CrD3CswD1, "domainsDimD3CrD3CswD1", domains1, "domains1" );


	cout<<"cDomains domainsCr2D3CswD1DimRD3;"<<endl;
	cDomains domainsCr2D3CswD1DimRD3;
	cout<<"domainsCr2D3CswD1DimRD3.addDomain( testTypePropertyColorRGB, vectorDomain2D3 ) "<<endl;
	domainsCr2D3CswD1DimRD3.addDomain( testTypePropertyColorRGB, vectorDomain2D3 );
	cout<<"domainsCr2D3CswD1DimRD3.addDomain( testTypePropertyColorSW, vectorDomain1D1 ) "<<endl;
	domainsCr2D3CswD1DimRD3.addDomain( testTypePropertyColorSW, vectorDomain1D1 );
	cout<<"domainsCr2D3CswD1DimRD3.addDomain( testTypeDimensionD3, &vectorDomain1D3 ) "<<endl;
	domainsCr2D3CswD1DimRD3.addDomain( testTypeDimensionD3, &vectorDomain1D3 );

	iReturn += testCompareTwoNotEqualDomains( domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3", domains1, "domains1" );
	cout<<"domains1 = domainsCr2D3CswD1DimRD3;"<<endl;
	domains1 = domainsCr2D3CswD1DimRD3;
	iReturn += testCompareTwoEqualDomains( domainsCr2D3CswD1DimRD3, "domainsCr2D3CswD1DimRD3", domains1, "domains1" );


	cout<<"cDomains domainsCrD3CswD1Dim2RD3;"<<endl;
	cDomains domainsCrD3CswD1Dim2RD3;
	cout<<"domainsCrD3CswD1Dim2RD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 ) "<<endl;
	domainsCrD3CswD1Dim2RD3.addDomain( testTypePropertyColorRGB, vectorDomain1D3 );
	cout<<"domainsCrD3CswD1Dim2RD3.addDomain( testTypePropertyColorSW, vectorDomain1D1 ) "<<endl;
	domainsCrD3CswD1Dim2RD3.addDomain( testTypePropertyColorSW, vectorDomain1D1 );
	cout<<"domainsCrD3CswD1Dim2RD3.addDomain( testTypeDimensionD3, &vectorDomain2D3 ) "<<endl;
	domainsCrD3CswD1Dim2RD3.addDomain( testTypeDimensionD3, &vectorDomain2D3 );

	iReturn += testCompareTwoNotEqualDomains( domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3", domains1, "domains1" );
	cout<<"domains1 = domainsCrD3CswD1Dim2RD3;"<<endl;
	domains1 = domainsCrD3CswD1Dim2RD3;
	iReturn += testCompareTwoEqualDomains( domainsCrD3CswD1Dim2RD3, "domainsCrD3CswD1Dim2RD3", domains1, "domains1" );


	return iReturn;
}




/**
 * This method tests a in the xml -format stored cDomains with
 * cDomainElements are stored.
 * The cDomainElements won't be tested, yust ther count is checked.
 * ( cDomainElements  are tested with tDomainElements)
 *
 * @param szFilename the name of the file wher the cDomainNaturalNumberBit is stored
 * @param uiNumberOfElements the number of elements in the vector domain;
 * 	every element is an cDomainNaturalNumberBit
 * @return the number of errors occured in the test
 */
int testXmlType( const string szFilename,
		const unsigned int uiNumberOfElements ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored type:"<<endl;
	
	TiXmlDocument xmlDocVectorPosition( szFilename );
	bool loadOkay = xmlDocVectorPosition.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the type was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocVectorPosition );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlRootHandle( 0 );

	pXmlElement = xmlHandle.FirstChildElement().Element();
	
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();

		if ( szElementName == "domains" ){
			cout<<"The root element is correctly named \"domains\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"domains\"."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}

	//read the dimensionmappings
	xmlRootHandle = xmlHandle.FirstChildElement();

	pXmlElement = xmlRootHandle.FirstChild().Element();
	
	unsigned int uiActualDomain = 0;
	//for every subdomain
	for( uiActualDomain = 0; pXmlElement;
			pXmlElement = pXmlElement->NextSiblingElement() ){
		//count the domainelements
		uiActualDomain++;
	}
	
	if ( uiActualDomain == uiNumberOfElements ){
		cout<<"The number of domainelements is correct. "<<endl;
	
	}else{
		cerr<<"Error: The number of domainelements is "<< uiActualDomain <<
			", but should be "<< uiNumberOfElements <<"."<<endl;
		iReturn++;
	}


	return iReturn;
}


/**
 * This method storeXml() method of the class.
 *
 * methods tested:
 * 	- bool storeXml( ostringstream & ostream ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStoreXml( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing xml -storing a empty domainlist"<<endl;

	cout<<"cDomains domains1;"<<endl;
	cDomains domains1;

	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domains1.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"domains1.storeXml( *fileXml );"<<endl;
	bool bStoreSuccesfull = domains1.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, 0 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing xml -storing a empty domainlist with one element"<<endl;

	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomains1( 1 );
	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4 );
	cout<<"cDomainVector domainVectorE1( vecDomains1 );"<<endl;
	cDomainVector domainVectorE1( vecDomains1 );
	delete vecDomains1[ 0 ];

	unsigned int uiPropertyType = 2;
	cout<<"cTypeProperty typeProperty2( "<< uiPropertyType <<" );"<<endl;
	cTypeProperty typeProperty2( uiPropertyType );
	
	cout<<"domains1.addDomain( typeProperty2, domainVectorE1 );"<<endl;
	domains1.addDomain( typeProperty2, domainVectorE1 );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domains1E1.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"domains1.storeXml( *fileXml );"<<endl;
	bStoreSuccesfull = domains1.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlType( szFileNameBuffer, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing xml -storing a empty domainlist with two elements"<<endl;

	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1, 1.0 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1, 1.0 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2, 0.125 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2, 0.125 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3, 3.0 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3, 3.0 );
	cout<<"cDomainVector domainVectorE3( vecDomains1 );"<<endl;
	cDomainVector domainVectorE3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	cout<<"cTypeDimension dimensionD3( 3 );"<<endl;
	cTypeDimension dimensionD3( 3 );
	
	cout<<"domains1.addDomain( dimensionD3, domainVectorE3 );"<<endl;
	domains1.addDomain( dimensionD3, domainVectorE3 );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domains1E2.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"domains1.storeXml( *fileXml );"<<endl;
	bStoreSuccesfull = domains1.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlType( szFileNameBuffer, 2 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing xml -storing a empty domainlist with 5 elements"<<endl;

	cout<<"cTypeProperty typeProperty1( 1 );"<<endl;
	cTypeProperty typeProperty1( 1 );
	
	cout<<"cTypeProperty typeProperty100( 100 );"<<endl;
	cTypeProperty typeProperty100( 100 );
	
	cout<<"cTypeProperty typeProperty200( 200 );"<<endl;
	cTypeProperty typeProperty200( 200 );
	
	cout<<"domains1.addDomain( typeProperty1, domainVectorE3 );"<<endl;
	domains1.addDomain( typeProperty1, domainVectorE3 );

	cout<<"domains1.addDomain( typeProperty100, domainVectorE1 );"<<endl;
	domains1.addDomain( typeProperty100, domainVectorE1 );
	cout<<"domains1.setStandardDomain( typeProperty200 );"<<endl;
	domains1.setStandardDomain( typeProperty200 );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domains1E5.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"domains1.storeXml( *fileXml );"<<endl;
	bStoreSuccesfull = domains1.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlType( szFileNameBuffer, 5 );


	return iReturn;
}




/**
 * This method store() method of the class.
 *
 * methods tested:
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostringstream & ostream ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStore( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a empty domainlist"<<endl;

	cout<<"cDomains domains1;"<<endl;
	cDomains domains1;

	//test get compressed size
	unsigned int uiCompressedSize = 64;
	if ( (unsigned int)(domains1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			domains1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domains1E0.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = domains1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	unsigned char ucRestBit = cRestBit;
	if ( ( ucRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomains1E0[] = {
		(char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, //64 bit parameter for number of elements
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomains1E0, 9 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a empty domainlist with one element"<<endl;

	//create vector domain with one elements
	unsigned int uiPropertyType = 2;
	cout<<"cTypeProperty typeProperty2( "<< uiPropertyType <<" );"<<endl;
	cTypeProperty typeProperty2( uiPropertyType );
	
	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomains1( 1 );
	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector domainVectorE1( vecDomains1 );"<<endl;
	cDomainVector domainVectorE1( vecDomains1 );
	delete vecDomains1[ 0 ];
	
	cout<<"domains1.addDomain( typeProperty2, domainVectorE1 );"<<endl;
	domains1.addDomain( typeProperty2, domainVectorE1 );


	//test get compressed size
	uiCompressedSize = 64 + 8 + 8 + 32;
	if ( (unsigned int)(domains1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			domains1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domains1E1.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = domains1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	if ( ( ucRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomains1E1[] = {
		(char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, //64 bit parameter for number of elements
		(char)0x22,   //property
		(char)0x02,   //type of the property
		(char)0xC0,   //vector domain
		(char)0x01, //8 bit parameter for number of elements
		(char)0x00, (char)0x03, //natural number domain
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomains1E1, 15 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a empty domainlist with two elements"<<endl;

	cout<<"cTypeDimension dimensionD1( 1 );"<<endl;
	cTypeDimension dimensionD1( 1 );
	
	cout<<"domains1.addDomain( dimensionD1, domainVectorE1 );"<<endl;
	domains1.addDomain( dimensionD1, domainVectorE1 );


	//test get compressed size
	uiCompressedSize = 64 + (8 + 8 + 32) +  (8 + 16 + 16 + 8 + 32);
	if ( (unsigned int)(domains1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			domains1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domains1E2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = domains1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	if ( ( ucRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomains1E2[] = {
		(char)0x02, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, //64 bit parameter for number of elements
		(char)0x22,   //property
		(char)0x02,   //type of the property
		(char)0xC0,   //vector domain
		(char)0x01,   //8 bit parameter for number of elements
		(char)0x00, (char)0x03, //natural number domain
		(char)0x0E,   //type dimension
		(char)0x03, (char)0x00, //length of parameterlist in byte
		(char)0x01, (char)0x00, //number of dimensione
		(char)0x01,   // dimension
		(char)0xC0,   //vector domain
		(char)0x01,   //8 bit parameter for number of elements
		(char)0x00, (char)0x03, //natural number domain
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomains1E2, 17 + 8 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a empty domainlist with 5 elements"<<endl;

	//create vector domain with one elements
	cout<<"cTypeProperty typeProperty100( 100 );"<<endl;
	cTypeProperty typeProperty100( 100 );

	cout<<"cTypeProperty typeProperty200( 200 );"<<endl;
	cTypeProperty typeProperty200( 200 );
	
	cout<<"cTypeProperty typeProperty400( 400 );"<<endl;
	cTypeProperty typeProperty400( 400 );
	
	cout<<"domains1.addDomain( typeProperty100, domainVectorE1 );"<<endl;
	domains1.addDomain( typeProperty100, domainVectorE1 );
	cout<<"domains1.addDomain( typeProperty200, domainVectorE1 );"<<endl;
	domains1.addDomain( typeProperty200, domainVectorE1 );
	cout<<"domains1.addDomain( typeProperty400, domainVectorE1 );"<<endl;
	domains1.addDomain( typeProperty400, domainVectorE1 );


	//test get compressed size
	uiCompressedSize = 64 + (8 + 8 + 32) + (8 + 16 + 16 + 8 + 32) + (8 + 8 + 32) +(8 + 8 + 32) + (8 + 64 + 32);
	if ( (unsigned int)(domains1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			domains1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domains1E5.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = domains1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	if ( ( ucRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomains1E5[] = {
		(char)0x05, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, //64 bit parameter for number of elements
		
		(char)0x22,   //property
		(char)0x02,   //type of the property
		(char)0xC0,   //vector domain
		(char)0x01,   //8 bit parameter for number of elements
		(char)0x00, (char)0x03, //natural number domain
		(char)0x0E,   //type dimension
		(char)0x03, (char)0x00, //length of parameterlist in byte
		(char)0x01, (char)0x00, //number of dimensione
		
		(char)0x01,   // dimension
		(char)0xC0,   //vector domain
		(char)0x01,   //8 bit parameter for number of elements
		(char)0x00, (char)0x03, //natural number domain
		
		(char)0x22,   //property
		(char)0x64,   //type of the property
		(char)0xC0,   //vector domain
		(char)0x01,   //8 bit parameter for number of elements
		(char)0x00, (char)0x03, //natural number domain
		
		(char)0x22,   //property
		(char)0xC8,   //type of the property
		(char)0xC0,   //vector domain
		(char)0x01,   //8 bit parameter for number of elements
		(char)0x00, (char)0x03, //natural number domain
		
		(char)0x24,   //property
		(char)0x90, (char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,   //type of the property
		(char)0xC0,   //vector domain
		(char)0x01,   //8 bit parameter for number of elements
		(char)0x00, (char)0x03, //natural number domain

		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomains1E5, 17 + 8 + 6 + 13 + 6);


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a empty domainlist with 5 elements and a restbit of 4"<<endl;

	//test get compressed size
	uiCompressedSize = 64 + (8 + 8 + 32) + (8 + 16 + 16 + 8 + 32) + (8 + 8 + 32) +(8 + 8 + 32) + (8 + 64 + 32);
	if ( (unsigned int)(domains1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			domains1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domains1E1S4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x0F;
	cNumberOfRestBit = 4;
	bStoreSuccesfull = domains1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	if ( ( ucRestBit == (char)0x00 ) && ( cNumberOfRestBit == 4 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x00 and number of restbit should be 4. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomains1E5S4[] = {
		(char)0x5F, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, //64 bit parameter for number of elements
		
		(char)0x20,   //property
		(char)0x22,   //type of the property
		(char)0x00,   //vector domain
		(char)0x1C,   //8 bit parameter for number of elements
		(char)0x00, (char)0x30, //natural number domain
		(char)0xE0,   //type dimension
		(char)0x30, (char)0x00, //length of parameterlist in byte
		(char)0x10, (char)0x00, //number of dimension
		
		(char)0x10,   // dimension
		(char)0x00,   //vector domain
		(char)0x1C,   //8 bit parameter for number of elements
		(char)0x00, (char)0x30, //natural number domain
		
		(char)0x20,   //property
		(char)0x42,   //type of the property
		(char)0x06,   //vector domain
		(char)0x1C,   //8 bit parameter for number of elements
		(char)0x00, (char)0x30, //natural number domain
		
		(char)0x20,   //property
		(char)0x82,   //type of the property
		(char)0x0C,   //vector domain
		(char)0x1C,   //8 bit parameter for number of elements
		(char)0x00, (char)0x30, //natural number domain
		
		(char)0x40,   //property
		(char)0x02, (char)0x19, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,   //type of the property
		(char)0x00,   //vector domain
		(char)0x1C,   //8 bit parameter for number of elements
		(char)0x00, (char)0x30, //natural number domain

		(char)0x00 }; //restbit
	
	
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomains1E5S4, 17 + 8 + 6 + 13 + 6);


	return iReturn;
}


/**
 * This method tests the reference domains ( @see cDomainReference )
 * methods for the cDomains class.
 *
 * methods tested:
 * 	- cDomain * getDomain( unsignedIntFib iDomainNumber ) const;
 * 	- cDomain * getDomainForElement( const cTypeElement &type ) const;
 * 	- cDomain * getDirectDomain( const unsignedIntFib iDomainNumber ) const;
 * 	- cDomain * getDomainForReferenceDomain( cDomainReference * pDomainReference, cTypeElement * pTypeElementForWhich = NULL ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testDomainReference( unsigned long &ulTestphase ){

//#define DEBUG_TEST_DOMAIN_REFERENCE
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the reference domains methods for the cDomains class"<<endl;
	
	cDomains domains;
	
	//a list with the existing domains
	list< pair< cTypeElement* , cDomain * > > liExistingDirectDomains;
	
	//the size of the random tests
	for ( unsigned long uiIteration = 0; uiIteration < MAX_RAND_TEST_SIZE;
			uiIteration++ ){
		
		cout<<endl<<"Iteration: "<<uiIteration;
		
		if ( rand() % 2 ){//add domain
			
			const unsigned int uiChoosenFunction = rand() % 3;
			cout<<"  (add function="<<uiChoosenFunction<<")"<<endl;
			
			//generate type to add
			cTypeElement * pTypeElement = NULL;
			
			const unsigned int uiChoosenType = rand() % 10;
			
			cout<<"domains.addDomain( ";
			switch ( uiChoosenType ){
				case 0:
					pTypeElement = new cTypeProperty( 0 );
					cout<<"cTypeProperty( 0 ), ";
				break;
				case 1:
					pTypeElement = new cTypeProperty( cTypeProperty::COLOR_RGB );
					cout<<"cTypeProperty( cTypeProperty::COLOR_RGB ), ";
				break;
				case 2:
					pTypeElement = new cTypeProperty( cTypeProperty::LAYER );
					cout<<"cTypeProperty( cTypeProperty::LAYER ), ";
				break;
				case 3:
					pTypeElement = new cTypeProperty( cTypeProperty::TRANSPARENCY );
					cout<<"cTypeProperty( cTypeProperty::TRANSPARENCY ), ";
				break;
				case 4:
					pTypeElement = new cTypeProperty( cTypeProperty::SOUND );
					cout<<"cTypeProperty( cTypeProperty::SOUND ), ";
				break;
				case 5:
					pTypeElement = new cTypeProperty( cTypeProperty::SOUND_POLARIZED );
					cout<<"cTypeProperty( cTypeProperty::SOUND_POLARIZED ), ";
				break;
				case 6:
					pTypeElement = new cTypeProperty( cTypeProperty::KELVIN );
					cout<<"cTypeProperty( cTypeProperty::KELVIN ), ";
				break;
				default:{
					const unsigned int uiNumberInVar = rand() % 32;
					pTypeElement = new cTypeInVar( uiNumberInVar );
					cout<<"cTypeInVar( "<<uiNumberInVar<<" ), ";
				}break;
			};
			
			cDomain * pDomain = NULL;
			cDomain * pStandardDomain = pTypeElement->getStandardDomain();
			
			switch ( uiChoosenFunction ){
				case 0:{//add normal domain
					//generate domain to add (domain with same number of elements as standar domain)
					
					if ( pStandardDomain->isScalar() ){
						//scalar domain
						const unsigned int uiNumberOfBits =
							rand() % 32;
						pDomain = new cDomainNaturalNumberBit( uiNumberOfBits );
						cout<<"cDomainNaturalNumberBit( "<<uiNumberOfBits<<" ) ";
						
					}else{//vector domain
						const unsigned int uiNumberOfDomainElements =
							((cDomainVectorBasis*)pStandardDomain)->getNumberOfElements();
						
						vector< cDomain * > vecDomain( uiNumberOfDomainElements );
						cout<<"cDomainVector( "<<uiNumberOfDomainElements<<","<<endl;
						
						for( unsigned int uiActualElement = 0;
								uiActualElement < uiNumberOfDomainElements;
								uiActualElement++ ){
							
							const unsigned int uiNumberOfBits =
								rand() % 32;
							vecDomain[ uiActualElement ] =
								new cDomainNaturalNumberBit( uiNumberOfBits );
							
							cout<<"   cDomainNaturalNumberBit( "<<uiNumberOfBits<<" ),"<<endl;
						}
						pDomain = new cDomainVector( vecDomain );
						cout<<"   )"<<endl;
						for( unsigned int uiActualElement = 0;
								uiActualElement < uiNumberOfDomainElements;
								uiActualElement++ ){
							
							delete vecDomain[ uiActualElement ];
						}
					}
					
				}break;
				case 1:{//add reference domain to existing type
					if ( domains.getNumberOfDomains() == 0 ){
						//no domain to refer to
						delete pStandardDomain;
						delete pTypeElement;
						cout<<" ) no domain to refer to -> abord"<<endl;
						continue;
					}
					//choose type to refer to
					const unsignedIntFib uiTypeToReferTo =
						1 + rand() % domains.getNumberOfDomains();
					
					cTypeElement * pTypeToReferTo = domains.getType( uiTypeToReferTo );
					
					cDomain * pStandardDomainForReferTo =
						pTypeToReferTo->getStandardDomain();
					
					cout<<"cDomainReference( "<<endl;
					pTypeToReferTo->storeXml( cout );
					
					vector<unsignedIntFib> vecInElementDomains;
					if ( rand() % 5 ){
						//use existing subdomain number
						if ( pStandardDomain->isScalar() ){
							//the to add type needs a scalar domain
							if ( pStandardDomainForReferTo->isVector() ){
								//choose subdomain number
								const unsignedIntFib uiChoosenSubdomain = 1 + rand() %
									((cDomainVectorBasis*)pStandardDomainForReferTo)->
										getNumberOfElements();
								
								vecInElementDomains.push_back( uiChoosenSubdomain );
								
								cout<<", {"<<uiChoosenSubdomain<<" (is OK) }";
							}//don't use subdomain number
						}//don't use subdomain number
						
					}else{//use not existing subdomain number
						unsigned int uiToGenerateSubdomainsNumbers = rand() % 8;
						
						cout<<", {";
						for ( unsigned int uiActualSubdomainNumber = 0;
								uiActualSubdomainNumber < uiToGenerateSubdomainsNumbers;
								uiActualSubdomainNumber++ ){
							
								const unsignedIntFib uiChoosenSubdomain = rand() % 16;
								
								vecInElementDomains.push_back( uiChoosenSubdomain );
								
								cout<<uiChoosenSubdomain<<", ";
						}
						cout<<"}";
					}
					cout<<" ) (=existing)"<<endl;
					delete pStandardDomainForReferTo;
					
					if ( ( ! vecInElementDomains.empty() ) || ( rand() % 2 == 0 ) ){
						//use subdomain numbers
						pDomain = new cDomainReference( *pTypeToReferTo, vecInElementDomains );
					}else{//don't use subdomain numbers
						pDomain = new cDomainReference( *pTypeToReferTo );
					}
					
				}break;
				case 2:{//add reference domain to not existing type
					
					cTypeElement * pTypeToReferTo = NULL;
					
					if ( rand() % 16 ){
						//add reference domain with new type
						
						const unsigned int uiChoosenType = rand() % 8;
						
						cout<<"cDomainReference( ";
						switch ( uiChoosenType ){
							case 0:
								pTypeToReferTo = new cTypeProperty( 0 );
								cout<<"cTypeProperty( cTypeProperty::SOUND_AMPLITUDE ), ";
							break;
							case 1:
								pTypeToReferTo = new cTypeProperty( cTypeProperty::COLOR_RGB );
								cout<<"cTypeProperty( cTypeProperty::SOUND_BARRIER ), ";
							break;
							case 2:
								pTypeToReferTo = new cTypeProperty( cTypeProperty::LAYER );
								cout<<"cTypeProperty( cTypeProperty::SOUND_REFLECTED ), ";
							break;
							case 3:
								pTypeToReferTo = new cTypeProperty( cTypeProperty::TRANSPARENCY );
								cout<<"cTypeProperty( cTypeProperty::SOUND_DAMPING ), ";
							break;
							case 4:
								pTypeToReferTo = new cTypeProperty( cTypeProperty::SOUND );
								cout<<"cTypeProperty( cTypeProperty::ELECTRO_MAGNETIC ), ";
							break;
							case 5:
								pTypeToReferTo = new cTypeProperty( cTypeProperty::SOUND_POLARIZED );
								cout<<"cTypeProperty( cTypeProperty::CHECKSUM ), ";
							break;
							default:{
								pTypeToReferTo = new cTypeArea();
								cout<<"cTypeArea(), ";
							}break;
						};
					}else{
						//add reference domain with type NULL
						pTypeToReferTo = NULL;
						cout<<"NULL, ";
					}
					
					vector<unsignedIntFib> vecInElementDomains;
					if ( rand() % 3 ){
						//add number of subelements
						unsigned int uiToGenerateSubdomainsNumbers = rand() % 8;
						
						cout<<"{";
						for ( unsigned int uiActualSubdomainNumber = 0;
								uiActualSubdomainNumber < uiToGenerateSubdomainsNumbers;
								uiActualSubdomainNumber++ ){
							
								const unsignedIntFib uiChoosenSubdomain = rand() % 8;
								
								vecInElementDomains.push_back( uiChoosenSubdomain );
								
								cout<<uiChoosenSubdomain<<", ";
						}
						cout<<"}";
					}
					
					cout<<" ) (=not existing)"<<endl;
					if ( ( ! vecInElementDomains.empty() ) || ( rand() % 2 == 0 ) ){
						//use subdomain numbers
						pDomain = new cDomainReference( *pTypeToReferTo, vecInElementDomains );
					}else{//don't use subdomain numbers
						pDomain = new cDomainReference( *pTypeToReferTo );
					}
					if ( pTypeToReferTo ){
						delete pTypeToReferTo;
					}
				}break;
				default://Warning: wrong choosen number
					cerr<<"Warning: wrong choosen number."<<endl;
					delete pTypeElement;
					delete pStandardDomain;
					continue;
				break;
			};
			const bool bDomainAdded = domains.addDomain( *pTypeElement, *pDomain );
			cout<<");"<<endl;
			if ( bDomainAdded ){
				cout<<" OK"<<endl;
			}else{
				cout<<endl;
				cerr<<"Error: The domain could not be added."<<endl;
				iReturn++;
			}
			//delete old domain for the same type
			for ( list< pair< cTypeElement* , cDomain * > >::iterator
					itrActualDomain = liExistingDirectDomains.begin();
					itrActualDomain != liExistingDirectDomains.end(); itrActualDomain++ ){
				
				if (  itrActualDomain->first->equalElementType( *pTypeElement ) ){
					delete itrActualDomain->first;
					delete itrActualDomain->second;
					liExistingDirectDomains.erase( itrActualDomain );
					break;
				}
			}
			liExistingDirectDomains.push_back( pair<cTypeElement* , cDomain*>(
				pTypeElement, pDomain ) );
			
			delete pStandardDomain;
		}else{//delete domain
			cout<<"  (delete domain)"<<endl;
			if ( domains.getNumberOfDomains() == 0 ){
				//no domain to delete
				continue;
			}
			const unsignedIntFib iDomainNumber = 1 + rand() %
				domains.getNumberOfDomains();
			
			cTypeElement * pToDeleteType = domains.getType( iDomainNumber );
			if ( pToDeleteType ){
				//delete old domain for the type
				for ( list< pair< cTypeElement* , cDomain * > >::iterator
						itrActualDomain = liExistingDirectDomains.begin();
						itrActualDomain != liExistingDirectDomains.end(); itrActualDomain++ ){
					
					if (  itrActualDomain->first->equalElementType( *pToDeleteType ) ){
						delete itrActualDomain->first;
						itrActualDomain->first = NULL;
						delete itrActualDomain->second;
						itrActualDomain->second = NULL;
						liExistingDirectDomains.erase( itrActualDomain );
						break;
					}
				}
			}

			const bool bDomainDeleted = domains.deleteDomain( iDomainNumber );
			cout<<"domains.deleteDomain( "<<iDomainNumber<<" );";
			
			if ( bDomainDeleted ){
				cout<<" OK"<<endl;
				
			}else{
				cout<<endl;
				cerr<<"Error: The domain could not be deleted."<<endl;
				iReturn++;
			}
		}
		list< pair< cTypeElement* , cDomain* > >
			liNotFoundDirectDomains = liExistingDirectDomains;
		
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
		cout<<endl<<"Existing domains:"<<endl<<flush;
		for ( list< pair< cTypeElement* , cDomain* > >::iterator
				itrActualDomain = liExistingDirectDomains.begin();
				itrActualDomain != liExistingDirectDomains.end(); itrActualDomain++ ){
			
			cout<<"The type is:"<<endl<<flush;
			itrActualDomain->first->storeXml( cout );
			cout<<"The domain is:"<<endl<<flush;
			itrActualDomain->second->storeXml( cout );
			cout<<endl<<endl;
		}
		cout<<endl<<"Evaluing refered to domains"<<endl<<flush;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
		map< cTypeElement* , cDomain* > mapExistingIndirectDomains;
		map< cTypeElement* , cDomainReference* > mapExistingReferenceDomains;
		
		//find and evalue reference domains
		for ( list< pair< cTypeElement* , cDomain* > >::iterator
				itrActualDomain = liExistingDirectDomains.begin();
				itrActualDomain != liExistingDirectDomains.end(); itrActualDomain++ ){
			
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
			if ( itrActualDomain->second == NULL ){
				cerr<<"Error actual liExistingDirectDomains Domain is NULL"<<endl<<flush;
				iReturn++;
			}
#endif //DEBUG_TEST_DOMAIN_REFERENCE
			
			cDomain * pActualDomain = itrActualDomain->second;
			
			if ( pActualDomain->isReference() ){
				/*actual domain is reference domain
				-> find domain to wich it refers*/
				mapExistingReferenceDomains.insert( make_pair(
					itrActualDomain->first, (cDomainReference*)pActualDomain ) );
				
				cDomain * pActualReferedToDomain = pActualDomain->clone();
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
				cout<<"actual domain is reference domain -> find domain to wich it refers"<<endl<<flush;
				cout<<"The type is:"<<endl;
				itrActualDomain->first->storeXml( cout );
				cout<<endl;
				cout<<"The domain is:"<<endl;
				itrActualDomain->second->storeXml( cout );
				cout<<endl;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
				bool bStopEvaluation = false;
				
				set< cDomain * > setFoundDomains;
				setFoundDomains.insert( pActualDomain );
				
				while ( ( pActualReferedToDomain->isReference() ) &&
						( ! bStopEvaluation ) ){
					
					cDomainReference * pActualReferenceDomain =
						(cDomainReference*)pActualReferedToDomain;
					
					const cTypeElement * pActualReferedToType =
						pActualReferenceDomain->getTypeElement();
					
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
					cout<<"The reference domain is:"<<endl<<flush;
					pActualReferedToDomain->storeXml( cout );
					cout<<endl;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
					if ( pActualReferedToType != NULL ){
						//find domain for element
						bool bTypeFound = false;
						for ( list< pair< cTypeElement* , cDomain * > >::iterator
								itrActualCompareDomain = liExistingDirectDomains.begin();
								itrActualCompareDomain != liExistingDirectDomains.end(); itrActualCompareDomain++ ){
							
							if ( itrActualCompareDomain->first->equalElementType(
									*pActualReferedToType ) ){
								//domain to which it is refered found
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
								cout<<"domain to which it is refered found"<<endl<<flush;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
								bTypeFound = true;
								//check for cyclic dependencies
								if ( setFoundDomains.find( itrActualCompareDomain->second ) !=
										setFoundDomains.end() ){
									//domain found befor -> return standard domain
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
									cout<<"domain found befor -> return standard domain"<<endl<<flush;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
									delete pActualReferedToDomain;
									pActualReferedToDomain =
										itrActualDomain->first->getStandardDomain();
									bStopEvaluation = true;
									break;
								}
								setFoundDomains.insert( itrActualCompareDomain->second );
								
								//choose subelement
								const vector<unsignedIntFib> vecNumberSubdomain =
									pActualReferenceDomain->getElement();
								
								delete pActualReferedToDomain;
								
								if ( vecNumberSubdomain.empty() ){
									//no subelement to choose
									pActualReferedToDomain = itrActualCompareDomain->second->clone();
								}else{//choose subelement
									
									cDomain * pActualSubdomain =
										itrActualCompareDomain->second;
									pActualReferedToDomain = pActualSubdomain;
									bool bCompatibleDomainFound = false;
									
									for ( vector<unsignedIntFib>::const_iterator
											itrActualSubdomain = vecNumberSubdomain.begin();
											itrActualSubdomain != vecNumberSubdomain.end();
											itrActualSubdomain++ ){
										
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
										cout<<"   Choosing "<<(*itrActualSubdomain)<<"'th subdomain"<<endl<<flush;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
										if ( ! pActualSubdomain->isVector() ){
											/*no vector domain -> no subelements
											 -> stop evaluation and use actual subdomain*/
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
											cout<<"   The domain is not a vector domain -> can't choose"<<endl<<flush;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
											break;
										}
										cDomainVectorBasis * pActualVectorSubdomain =
											(cDomainVectorBasis*)pActualSubdomain;
										
										if ( pActualVectorSubdomain->getElementDomain(
												*itrActualSubdomain ) ){
											//use subdomain for the actual subdomain number
											pActualSubdomain = pActualVectorSubdomain->
												getElementDomain( *itrActualSubdomain );
										}else if ( pActualVectorSubdomain->getElementDomain(
												pActualVectorSubdomain->getNumberOfElements() ) ){
											//use last subdomain of domain
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
											cout<<"   use last subdomain of domain"<<endl<<flush;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
											pActualSubdomain =
												pActualVectorSubdomain->getElementDomain(
													pActualVectorSubdomain->getNumberOfElements()  );
										}else{//no such subdomain
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
											cout<<"   no such subdomain"<<endl<<flush;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
											break;
										}
										if ( itrActualDomain->first->isCompatible(
												*pActualSubdomain ) ){
											/*the domain is compatible with the actual type
											 -> use it */
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
											cout<<"   the subdomain is compatible"<<endl<<flush;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
											pActualReferedToDomain = pActualSubdomain;
											bCompatibleDomainFound = true;
										}else if ( ! bCompatibleDomainFound ){
											/*no compatible domain for the actual type found
											 -> use it */
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
											cout<<"   no compatible domain for the actual type found"<<endl<<flush;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
											pActualReferedToDomain = pActualSubdomain;
										}//end if compatible
									}
									pActualReferedToDomain = pActualReferedToDomain->clone();
								}
								break;
							}
						}
						if ( ! bTypeFound ){
							//no refered to domain found -> use standard domain
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
							cout<<"no refered to domain found -> use standard domain"<<endl<<flush;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
							delete pActualReferedToDomain;
							pActualReferedToDomain =
								itrActualDomain->first->getStandardDomain();
							bStopEvaluation = true;
						}
					}else{/*pActualReferedToType == NULL
						-> refer to standard type of actual element */
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
							cout<<"pActualReferedToType == NULL -> refer to standard type of actual element"<<endl<<flush;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
						delete pActualReferedToDomain;
						pActualReferedToDomain =
							itrActualDomain->first->getStandardDomain();
						bStopEvaluation = true;
					}
					
				}//end while as long as a reference domain
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
				cout<<"Inserting refered to domain:"<<endl<<flush;
				cout<<"The type is:"<<endl;
				itrActualDomain->first->storeXml( cout );
				cout<<endl;
				cout<<"The domain is:"<<endl;
				pActualReferedToDomain->storeXml( cout );
				cout<<endl;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
				mapExistingIndirectDomains.insert( make_pair(
					itrActualDomain->first, pActualReferedToDomain ) );
			}
		}
		const unsigned int uiNumberofDomains = domains.getNumberOfDomains();
		
		if ( liExistingDirectDomains.size() != uiNumberofDomains ){
			
			cerr<<"Error: The number of domains is "<<uiNumberofDomains<<
				", but should be "<<liExistingDirectDomains.size()<<". "<<endl;
			iReturn++;
		}
		
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
		cout<<"start testing get*Domain( uiActualDomain ) for all domain numbers"<<endl<<flush;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
		//for all domains
		for ( unsigned int uiActualDomain = 1;
				uiActualDomain <= uiNumberofDomains; uiActualDomain++ ){
			
			cTypeElement * pActualType = domains.getType( uiActualDomain );
			
			//find type in liNotFoundDirectDomains
			list< pair< cTypeElement* , cDomain* > >::iterator
				itrActualNotFound = liNotFoundDirectDomains.end();
				
			for ( list< pair< cTypeElement* , cDomain * > >::iterator
					itrActualNotFoundDomain = liNotFoundDirectDomains.begin();
					itrActualNotFoundDomain != liNotFoundDirectDomains.end();
					itrActualNotFoundDomain++ ){
				
				if ( itrActualNotFoundDomain->first->equalElementType(
						*pActualType ) ){
					itrActualNotFound = itrActualNotFoundDomain;
					break;
				}
			}
			if ( itrActualNotFound == liNotFoundDirectDomains.end() ){
				cerr<<"Error: The "<<uiActualDomain<<"'th domain type was found befor in the domain list."<<endl;
				iReturn++;
				continue;
			}
			
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
			cout<<"domains.getDirectDomain( "<<uiActualDomain<<" );"<<endl<<flush;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
			//check cDomainReference * getDomainReference( const unsignedIntFib iDomainNumber ) const;
			cDomain * pActualDirectDomain =
				domains.getDirectDomain( uiActualDomain );

			if ( pActualDirectDomain != NULL ){
				//check the domain from liNotFoundDirectDomains is equal
				if ( ! pActualDirectDomain->equal( *(itrActualNotFound->second) ) ){
					cerr<<"Error: The "<<uiActualDomain<<"'th direct domain is not the correct domain."<<endl;
					cerr<<"Actual type:"<<endl;
					pActualType->storeXml( cerr );
					cerr<<"The domain is:"<<endl;
					pActualDirectDomain->storeXml( cerr );
					cerr<<endl<<"But should be:"<<endl;
					itrActualNotFound->second->storeXml( cerr );
					cerr<<endl;
					iReturn++;
				}
				
				if ( pActualDirectDomain->isReference() ){
					//check is in mapExistingIndirectDomains
					if( mapExistingIndirectDomains.find( itrActualNotFound->first ) ==
							mapExistingIndirectDomains.end() ){
						
						cerr<<"Error: The "<<uiActualDomain<<"'th direct domain "<<
							"is a reference domain but could not found in the "<<
							"reference domain list (mapExistingIndirectDomains)."<<endl;
						iReturn++;
					}
				}
			}else{
				cerr<<"Error: The "<<uiActualDomain<<"'th direct domain is NULL."<<endl;
				iReturn++;
			}
			
#ifdef DEBUG_TEST_DOMAIN_REFERENCE
			cout<<"domains.getDomain( "<<uiActualDomain<<" );"<<endl<<flush;
#endif //DEBUG_TEST_DOMAIN_REFERENCE
			//check cDomain * getDomain( unsignedIntFib iDomainNumber )
			cDomain * pActualDomain = domains.getDomain( uiActualDomain );
			
			if ( pActualDomain != NULL ){
				
				if ( ! itrActualNotFound->second->isReference() ){
					//check the domain from liNotFoundDirectDomains is equal
					if ( ! pActualDomain->equal( *(itrActualNotFound->second) ) ){
						cerr<<"Error: The "<<uiActualDomain<<"'th domain is not the correct domain."<<endl;
						cerr<<"Actual type:"<<endl;
						pActualType->storeXml( cerr );
						cerr<<"The domain is:"<<endl;
						pActualDirectDomain->storeXml( cerr );
						cerr<<endl<<"But should be:"<<endl;
						itrActualNotFound->second->storeXml( cerr );
						cerr<<endl;
						iReturn++;
					}
				}else{//the domain is a reference domain
					//check the domain from liNotFoundDirectDomains is not equal
					if ( pActualDomain->equal( *(itrActualNotFound->second) ) ){
						cerr<<"Error: The "<<uiActualDomain<<"'th domain is not "<<
							"the correct domain, because it is equal to the direct "<<
							"domain, but this in turn is a reference domain."<<endl;
						cerr<<"Actual type:"<<endl;
						pActualType->storeXml( cerr );
						cerr<<"The domain is:"<<endl;
						pActualDomain->storeXml( cerr );
						cerr<<endl<<"But the direct domain is:"<<endl;
						itrActualNotFound->second->storeXml( cerr );
						cerr<<endl;
						iReturn++;
					}

					//check is equal to mapExistingIndirectDomains
					map< cTypeElement* , cDomain* >::iterator itrExistingIndirectDomains =
						mapExistingIndirectDomains.find( itrActualNotFound->first );
					
					if( itrExistingIndirectDomains == mapExistingIndirectDomains.end() ){
						
						cerr<<"Error: The "<<uiActualDomain<<"'th direct domain "<<
							"is a reference domain but could not found in the "<<
							"reference domain list (mapExistingIndirectDomains)."<<endl;
						iReturn++;
					}else{//compare the domains to which it is referd
						if ( ! itrExistingIndirectDomains->second->equal( *pActualDomain ) ){
							cerr<<"Error: The "<<uiActualDomain<<"'th refered to domain is not "<<
								"the correct the domain."<<endl;
							cerr<<"Actual type:"<<endl;
							pActualType->storeXml( cerr );
							cerr<<"The domain is:"<<endl;
							pActualDomain->storeXml( cerr );
							cerr<<endl<<"But the correct refered to domain is:"<<endl;
							itrExistingIndirectDomains->second->storeXml( cerr );
							cerr<<endl;
							iReturn++;
						}
					}//end check mapExistingIndirectDomains
				}
			}else{
				cerr<<"Error: The "<<uiActualDomain<<"'th domain is NULL. "<<endl;
				iReturn++;
			}
			
			//the actual domain was found -> erase it from the not found list
			liNotFoundDirectDomains.erase( itrActualNotFound );
		}//end for all domains numbers
		
		if ( ! liNotFoundDirectDomains.empty() ){
			cerr<<"Error: Ther are some direct domains which should exists, but whern't found."<<endl;
			iReturn++;
		}
		if ( domains.getDomain( 0 ) != NULL ){
			cerr<<"Error: Ther is a 0'th domain."<<endl;
			iReturn++;
		}
		if ( domains.getDirectDomain( 0 ) != NULL ){
			cerr<<"Error: Ther is a 0'th direct domain."<<endl;
			iReturn++;
		}
		if ( domains.getDomain( uiNumberofDomains + 1 ) != NULL ){
			cerr<<"Error: Ther is a "<<(uiNumberofDomains + 1)<<"'th domain."<<endl;
			iReturn++;
		}
		if ( domains.getDirectDomain( uiNumberofDomains + 1 ) != NULL ){
			cerr<<"Error: Ther is a "<<(uiNumberofDomains + 1)<<"'th direct domain."<<endl;
			iReturn++;
		}
		//check cDomain * getDomainForElement( const cTypeElement &type ) const;
		for ( list< pair< cTypeElement* , cDomain* > >::iterator
				itrActualDomain = liExistingDirectDomains.begin();
				itrActualDomain != liExistingDirectDomains.end(); itrActualDomain++ ){
			
			const cTypeElement * pActualType = itrActualDomain->first;
			
			cDomain * pActualDomain = domains.getDomainForElement( *pActualType );
		
			if ( pActualDomain != NULL ){
				
				if ( ! itrActualDomain->second->isReference() ){
					//check the domain from liExistingDirectDomains is equal
					if ( ! pActualDomain->equal( *(itrActualDomain->second) ) ){
						cerr<<"Error: The domain is not the correct domain."<<endl;
						cerr<<"Actual type:"<<endl;
						pActualType->storeXml( cerr );
						cerr<<endl<<"The domain is:"<<endl;
						pActualDomain->storeXml( cerr );
						cerr<<endl<<"But should be:"<<endl;
						itrActualDomain->second->storeXml( cerr );
						cerr<<endl;
						iReturn++;
					}
				}else{//the domain is a reference domain
					//check the domain from liExistingDirectDomains is not equal
					if ( pActualDomain->equal( *(itrActualDomain->second) ) ){
						cerr<<"Error: The domain is not "<<
							"the correct domain, because it is equal to the direct "<<
							"domain, but this in turn is a reference domain."<<endl;
						cerr<<"Actual type:"<<endl;
						pActualType->storeXml( cerr );
						cerr<<endl<<"The domain is:"<<endl;
						pActualDomain->storeXml( cerr );
						cerr<<endl<<"But the direct domain is:"<<endl;
						itrActualDomain->second->storeXml( cerr );
						cerr<<endl;
						iReturn++;
					}

					//check is equal to mapExistingIndirectDomains
					map< cTypeElement* , cDomain* >::iterator itrExistingIndirectDomains =
						mapExistingIndirectDomains.find( itrActualDomain->first );
					
					if( itrExistingIndirectDomains == mapExistingIndirectDomains.end() ){
						
						cerr<<"Error: The indirect domain "<<
							"is a reference domain but could not found in the "<<
							"reference domain list (mapExistingIndirectDomains)."<<endl;
						cerr<<"Actual type:"<<endl;
						pActualType->storeXml( cerr );
						cerr<<endl;
						iReturn++;
					}else{//compare the domains to which it is referd
						if ( ! itrExistingIndirectDomains->second->equal( *pActualDomain ) ){
							cerr<<"Error: The refered to domain is not the correct the domain."<<endl;
							cerr<<"Actual type:"<<endl;
							pActualType->storeXml( cerr );
							cerr<<endl<<"The domain is:"<<endl;
							pActualDomain->storeXml( cerr );
							cerr<<endl<<"But the direct domain is:"<<endl;
							itrExistingIndirectDomains->second->storeXml( cerr );
							cerr<<endl;
							iReturn++;
						}
					}//end check mapExistingIndirectDomains
				}
			}else{
				cerr<<"Error: The domain is NULL."<<endl;
				cerr<<"Actual type:"<<endl;
				pActualType->storeXml( cerr );
				iReturn++;
			}
		}//end for check getDomainForElement()
		
		//check cDomain * getDomainForReferenceDomain( cDomainReference * pDomainReference, cTypeElement * pTypeElementForWhich = NULL ) const;
		for ( map< cTypeElement* , cDomain* >::iterator
				itrIndirectDomain = mapExistingIndirectDomains.begin();
				itrIndirectDomain != mapExistingIndirectDomains.end();
				itrIndirectDomain++ ){
			
			cTypeElement * pActualType = itrIndirectDomain->first;
			
			cDomainReference * pReferenceDomain =
				mapExistingReferenceDomains[ pActualType ];
			
			cDomain * pActualDomain = domains.getDomainForReferenceDomain(
				pReferenceDomain, pActualType );
			//TODO?? check for pActualType == NULL
			
			if ( pActualDomain != NULL ){
				
				//check is equal to mapExistingIndirectDomains
				if ( ! itrIndirectDomain->second->equal( *pActualDomain ) ){
					cerr<<"Error: The evalued refered to domain is not the correct the domain."<<endl;
					cerr<<"Actual type:"<<endl;
					pActualType->storeXml( cerr );
					cerr<<endl<<"The domain is:"<<endl;
					pActualDomain->storeXml( cerr );
					cerr<<endl<<"But the direct domain is:"<<endl;
					itrIndirectDomain->second->storeXml( cerr );
					cerr<<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: The evalued refered to domain is NULL."<<endl;
				cerr<<"Actual type:"<<endl;
				pActualType->storeXml( cerr );
				iReturn++;
			}
			
		}//end for check getDomainForReferenceDomain()
		cDomain * pReferenceNullDomain = domains.getDomainForReferenceDomain(
			NULL, NULL );
		if ( pReferenceNullDomain != NULL ){
			cerr<<"Error: A Domain was given back for: domains.getDomainForReferenceDomain( NULL, NULL );"<<endl;
			iReturn++;
		}
		
		//delete the domains from list with indirect domains (ther are clones)
		for ( map< cTypeElement* , cDomain* >::iterator
				itrActualDomain = mapExistingIndirectDomains.begin();
				itrActualDomain != mapExistingIndirectDomains.end(); itrActualDomain++ ){
			
			delete itrActualDomain->second;
		}
	}
	//delete the still existing domains
	for ( list< pair< cTypeElement* , cDomain* > >::iterator
			itrActualDomain = liExistingDirectDomains.begin();
			itrActualDomain != liExistingDirectDomains.end(); itrActualDomain++ ){
		
		delete itrActualDomain->first;
		delete itrActualDomain->second;
	}

	return iReturn;
}















