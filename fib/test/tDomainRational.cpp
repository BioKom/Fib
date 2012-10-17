/**
 * @file tDomainRational
 * file name: tDomainRational.cpp
 * @author Betti Oesterholz
 * @date 13.05.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for domains of the class cDomainRational.
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
 * This file contains the test for the class cDomainRational,
 * which represents a domain for natural numbers.
 *
 *
 *
 *  What's tested of class cDomainRational:
 * 	- cDomainRational( const cDomainIntegerBasis &dfMantissa, const cDomainIntegerBasis &dfExponent );
 * 	- cDomainRational( const TiXmlElement * pXmlElement, intFib & outStatus );
 * 	- cDomainRational( const cDomainRational &domain );
 * 	- string getType() const;
 * 	- bool isElement( const doubleFib dValue ) const;
 * 	- doubleFib round( const doubleFib dValue ) const;
 * 	- doubleFib getMaximum() const ;
 * 	- doubleFib getMinimum() const
 * 	- doubleFib getNull() const;
 * 	- cDomainRational *clone() const;
 * 	- operator==( const cDomain &domain ) const;
 * 	- equal( const cDomain &domain ) const;
 * 	- bool storeXml( ostringstream & ostream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 * 	- unsignedIntFib getCompressedSizeForValue() const;
 * 	- bool storeValue( doubleFib dValue, ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 * 	- doubleFib restoreValue( cReadBits & iBitStream, intFib & outStatus ) const
 *
 * 	- static cDomainSingle * cDomainSingle::createGoodDomain( list< doubleFib > & liValues );
 */
/*
History:
13.05.2010  Oesterholz  created
28.09.2010  Oesterholz  createGoodDomain() added
30.03.2011  Oesterholz  storing to binary stream
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/



#include "version.h"

#include "cDomainRational.h"

#include "cDomainNaturalNumberBit.h"
#include "cDomainNaturalNumber.h"
#include "cDomainInteger.h"
#include "cDomainVector.h"
#include "cReadBits.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cmath>

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif


using namespace fib;
using namespace std;


extern int testIntegerDomainLong( cDomainIntegerBasis *domainToTest,
	longFib lMinNumber, longFib lMaxNumber, doubleFib dScalingFactor );

//testmethods
int testConstructor( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testCopy( unsigned long &ulTestphase );
int testValues( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );
int testStoreValue( unsigned long &ulTestphase );

int testCreateGoodDomain( unsigned long &ulTestphase );


int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for cDomainRational methods"<<endl;
	cout<<      "========================================"<<endl;

	iReturn += testConstructor( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testValues( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testStoreValue( ulTestphase );

	//cDomainSingle
	iReturn += testCreateGoodDomain( ulTestphase );

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}
	
	return iReturn;
}

/**
 * This function tests the constructors of the class.
 *
 * methods tested:
 * 	- cDomainRational( const cDomainIntegerBasis &dfMantissa, const cDomainIntegerBasis &dfExponent );
 * 	- doubleFib getMaximum() const ;
 * 	- doubleFib getMinimum() const
 * 	- doubleFib getNull() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testConstructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with mantissa domain with 1 bits and exponent domain with 2 bit"<<endl;
	
	cout<<"cDomainNaturalNumberBit domNaturalNumber1( 1 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumber1( 1 );
	cout<<"cDomainNaturalNumberBit domNaturalNumber2( 2 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumber2( 2 );
	
	cout<<"cDomainRational *testRational1 = new cDomainRational( "<<
		"domNaturalNumber1, domNaturalNumber2 );"<<endl;
	cDomainRational *testRational1 = new cDomainRational(
		domNaturalNumber1, domNaturalNumber2 );

	//check the getType() methode
	if ( testRational1->getType() == "DomainRational" ){
	
		cout<<"The correct type \"DomainRational\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not \"DomainRational\" ; it is : "<<testRational1->getType()<<endl;
		iReturn++;
	}
	//check the getMaximum() methode
	if ( testRational1->getMaximum() == 8.0  ){
	
		cout<<"The maximum is correctly "<< 8.0 <<" . "<<endl;
	}else{
		cerr<<"Error: The maximum is "<<testRational1->getMaximum() <<", but should be "<< 8.0 <<" . "<<endl;
		iReturn++;
	}
	//check the getMinimum() methode
	if ( testRational1->getMinimum() == 0.0  ){
	
		cout<<"The maximum is correctly "<< 0.0 <<" . "<<endl;
	}else{
		cerr<<"Error: The maximum is "<<testRational1->getMinimum() <<", but should be "<< 0.0 <<" . "<<endl;
		iReturn++;
	}
	//check the getMinimum() methode
	if ( testRational1->getNull() == 0.0  ){
	
		cout<<"The maximum is correctly "<< 0.0 <<" . "<<endl;
	}else{
		cerr<<"Error: The maximum is "<<testRational1->getNull() <<", but should be "<< 0.0 <<" . "<<endl;
		iReturn++;
	}
	delete testRational1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with mantissa domain with 3 bits and exponent domain with 0 bit"<<endl;
	
	cout<<"cDomainNaturalNumberBit domNaturalNumber3( 3 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumber3( 3 );
	
		cout<<"cDomainNaturalNumberBit domNaturalNumber0( 0 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumber0( 0 );

	cout<<"testRational1 = new cDomainRational( domNaturalNumber3, domNaturalNumber0 );"<<endl;
	testRational1 = new cDomainRational( domNaturalNumber3, domNaturalNumber0 );

	//check the getType() methode
	if ( testRational1->getType() == "DomainRational" ){
	
		cout<<"The correct type \"DomainRational\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not \"DomainRational\" ; it is : "<<testRational1->getType()<<endl;
		iReturn++;
	}
	//check the getMaximum() methode
	if ( testRational1->getMaximum() == 7.0  ){
	
		cout<<"The maximum is correctly "<< 7.0 <<" . "<<endl;
	}else{
		cerr<<"Error: The maximum is "<<testRational1->getMaximum() <<", but should be "<< 7.0 <<" . "<<endl;
		iReturn++;
	}
	//check the getMinimum() methode
	if ( testRational1->getMinimum() == 0.0  ){
	
		cout<<"The maximum is correctly "<< 0.0 <<" . "<<endl;
	}else{
		cerr<<"Error: The maximum is "<<testRational1->getMinimum() <<", but should be "<< 0.0 <<" . "<<endl;
		iReturn++;
	}
	//check the getMinimum() methode
	if ( testRational1->getNull() == 0.0  ){
	
		cout<<"The maximum is correctly "<< 0.0 <<" . "<<endl;
	}else{
		cerr<<"Error: The maximum is "<<testRational1->getNull() <<", but should be "<< 0.0 <<" . "<<endl;
		iReturn++;
	}
	delete testRational1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with mantissa domain with 3 bits and exponent domain with 1 bit"<<endl;
	
	cout<<"testRational1 = new cDomainRational( domNaturalNumber3, domNaturalNumber1 );"<<endl;
	testRational1 = new cDomainRational( domNaturalNumber3, domNaturalNumber1 );

	//check the getType() methode
	if ( testRational1->getType() == "DomainRational" ){
	
		cout<<"The correct type \"DomainRational\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not \"DomainRational\" ; it is : "<<testRational1->getType()<<endl;
		iReturn++;
	}
	//check the getMaximum() methode
	if ( testRational1->getMaximum() == 14.0  ){
	
		cout<<"The maximum is correctly "<< 14.0 <<" . "<<endl;
	}else{
		cerr<<"Error: The maximum is "<<testRational1->getMaximum() <<", but should be "<< 14.0 <<" . "<<endl;
		iReturn++;
	}
	//check the getMinimum() methode
	if ( testRational1->getMinimum() == 0.0  ){
	
		cout<<"The maximum is correctly "<< 0.0 <<" . "<<endl;
	}else{
		cerr<<"Error: The maximum is "<<testRational1->getMinimum() <<", but should be "<< 0.0 <<" . "<<endl;
		iReturn++;
	}
	//check the getMinimum() methode
	if ( testRational1->getNull() == 0.0  ){
	
		cout<<"The maximum is correctly "<< 0.0 <<" . "<<endl;
	}else{
		cerr<<"Error: The maximum is "<<testRational1->getNull() <<", but should be "<< 0.0 <<" . "<<endl;
		iReturn++;
	}
	delete testRational1;


	return iReturn;
}



/**
 * This function tests the equal() method and the operator== of two given
 * cDomain objects which are equal.
 *
 * @param domain1 the first domain to compare
 * @param szNameDomain1 the name of the first domain to compare
 * @param domain2 the secound domain to compare to
 * @param szNameDomain2 the name of the secound domain to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualDomains( const cDomain &domain1, const string &szNameDomain1,
	const cDomain &domain2, const string &szNameDomain2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( domain1.equal( domain2 ) ){
	
		cout<<"The "<<szNameDomain1<<" is equal to "<<szNameDomain2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is not equal to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	if ( domain1 == domain2 ){
	
		cout<<"The "<<szNameDomain1<<" is equal (operator==) to "<<
			szNameDomain2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is not equal (operator==) to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}

/**
 * This function tests the equal() method and the operator== of two given
 * cDomain objects which are not equal.
 *
 * @param domain1 the first domain to compare
 * @param szNameDomain1 the name of the first domain to compare
 * @param domain2 the secound domain to compare to
 * @param szNameDomain2 the name of the secound domain to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualDomains( const cDomain &domain1, const string &szNameDomain1,
	const cDomain &domain2, const string &szNameDomain2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! domain1.equal( domain2 ) ){
	
		cout<<"The "<<szNameDomain1<<" is not equal to "<<szNameDomain2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is equal to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	if ( ! (domain1 == domain2) ){
	
		cout<<"The "<<szNameDomain1<<" is not equal (operator==) to "<<
			szNameDomain2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is equal (operator==) to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This function tests the equal() method and the operator== of the class.
 *
 * methods tested:
 * 	- operator==( const cDomain &domain ) const;
 * 	- equal( const cDomain &domain ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testEqual( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equal method and the operator== "<<endl;

	//create cDomainRationals to compare
	cout<<"cDomainNaturalNumberBit domNaturalNumberBit1( 1 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumberBit1( 1 );
	cout<<"cDomainNaturalNumberBit domNaturalNumberBit2( 2 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumberBit2( 2 );
	cout<<"cDomainNaturalNumberBit domNaturalNumberBit3( 3 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumberBit3( 3 );
	
	cout<<"cDomainNaturalNumber domNaturalNumber3( 3 );"<<endl;
	cDomainNaturalNumber domNaturalNumber3( 3 );

	cout<<"cDomainRational domRational1Nb1Nb2( domNaturalNumberBit1, domNaturalNumberBit2 );"<<endl;
	cDomainRational domRational1Nb1Nb2( domNaturalNumberBit1, domNaturalNumberBit2 );
	
	cout<<"cDomainRational domRational2Nb1Nb2( domNaturalNumberBit1, domNaturalNumberBit2 );"<<endl;
	cDomainRational domRational2Nb1Nb2( domNaturalNumberBit1, domNaturalNumberBit2 );

	cout<<"cDomainRational domRational1Nb2Nb1( domNaturalNumberBit2, domNaturalNumberBit1 );"<<endl;
	cDomainRational domRational1Nb2Nb1( domNaturalNumberBit2, domNaturalNumberBit1 );
	
	cout<<"cDomainRational domRational1Nb1Nb3( domNaturalNumberBit1, domNaturalNumberBit3 );"<<endl;
	cDomainRational domRational1Nb1Nb3( domNaturalNumberBit1, domNaturalNumberBit3 );
	
	cout<<"cDomainRational domRational1Nb1N3( domNaturalNumberBit1, domNaturalNumber3 );"<<endl;
	cDomainRational domRational1Nb1N3( domNaturalNumberBit1, domNaturalNumber3 );
	
	
	cout<<"vector<cDomainSingle*> vElementdomains( 1 );"<<endl;
	vector<cDomainSingle*> vElementdomains( 1 );
	cout<<"vElementdomains[0]=&domNaturalNumber3;"<<endl;
	vElementdomains[0]=(&domNaturalNumber3);
	cout<<"cDomainVector domainVector( vElementdomains );"<<endl;
	cDomainVector domainVector( vElementdomains );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with domRational1Nb1Nb2
	cDomain *actualDomain=&domRational1Nb1Nb2;
	string szActualDomainName="domRational1Nb1Nb2";
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1Nb2, "domRational1Nb1Nb2" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domRational2Nb1Nb2, "domRational2Nb1Nb2" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb2Nb1, "domRational1Nb2Nb1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1Nb3, "domRational1Nb1Nb3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1N3, "domRational1Nb1N3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domNaturalNumberBit1, "domNaturalNumberBit1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domRational2Nb1Nb2
	actualDomain=&domRational2Nb1Nb2;
	szActualDomainName="domRational2Nb1Nb2";
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1Nb2, "domRational1Nb1Nb2" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domRational2Nb1Nb2, "domRational2Nb1Nb2" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb2Nb1, "domRational1Nb2Nb1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1Nb3, "domRational1Nb1Nb3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1N3, "domRational1Nb1N3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domNaturalNumberBit1, "domNaturalNumberBit1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domRational1Nb2Nb1
	actualDomain=&domRational1Nb2Nb1;
	szActualDomainName="domRational1Nb2Nb1";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1Nb2, "domRational1Nb1Nb2" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational2Nb1Nb2, "domRational2Nb1Nb2" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domRational1Nb2Nb1, "domRational1Nb2Nb1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1Nb3, "domRational1Nb1Nb3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1N3, "domRational1Nb1N3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domNaturalNumberBit1, "domNaturalNumberBit1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domRational1Nb1Nb3
	actualDomain=&domRational1Nb1Nb3;
	szActualDomainName="domRational1Nb1Nb3";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1Nb2, "domRational1Nb1Nb2" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational2Nb1Nb2, "domRational2Nb1Nb2" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb2Nb1, "domRational1Nb2Nb1" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1Nb3, "domRational1Nb1Nb3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1N3, "domRational1Nb1N3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domNaturalNumberBit1, "domNaturalNumberBit1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domRational1Nb1N3
	actualDomain=&domRational1Nb1N3;
	szActualDomainName="domRational1Nb1N3";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1Nb2, "domRational1Nb1Nb2" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational2Nb1Nb2, "domRational2Nb1Nb2" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb2Nb1, "domRational1Nb2Nb1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1Nb3, "domRational1Nb1Nb3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1N3, "domRational1Nb1N3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domNaturalNumberBit1, "domNaturalNumberBit1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domNaturalNumberBit1
	actualDomain=&domNaturalNumberBit1;
	szActualDomainName="domNaturalNumberBit1";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1Nb2, "domRational1Nb1Nb2" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational2Nb1Nb2, "domRational2Nb1Nb2" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb2Nb1, "domRational1Nb2Nb1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1Nb3, "domRational1Nb1Nb3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1N3, "domRational1Nb1N3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domNaturalNumberBit1, "domNaturalNumberBit1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainVector
	actualDomain=&domainVector;
	szActualDomainName="domainVector";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1Nb2, "domRational1Nb1Nb2" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational2Nb1Nb2, "domRational2Nb1Nb2" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb2Nb1, "domRational1Nb2Nb1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1Nb3, "domRational1Nb1Nb3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domRational1Nb1N3, "domRational1Nb1N3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domNaturalNumberBit1, "domNaturalNumberBit1" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );


	return iReturn;
}


/**
 * This function tests the copyconstructor and clone() method of the class.
 *
 * methods tested:
 * 	- cDomainRational( const cDomainRational &domain );
 * 	- cDomainRational *clone() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCopy( unsigned long &ulTestphase ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the copyconstructor and the clone method "<<endl;

	cout<<"cDomainNaturalNumberBit domNaturalNumber1( 1 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumber1( 1 );
	cout<<"cDomainNaturalNumberBit domNaturalNumber2( 2 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumber2( 2 );
	
	cout<<"cDomainRational domRationalNB1NB2( domNaturalNumber1, domNaturalNumber2 );"<<endl;
	cDomainRational domRationalNB1NB2( domNaturalNumber1, domNaturalNumber2 );
	
	cout<<"cDomainRational domRationalNB1NB2Org( domNaturalNumber1, domNaturalNumber2 );"<<endl;
	cDomainRational domRationalNB1NB2Org( domNaturalNumber1, domNaturalNumber2 );
	
	cout<<"cDomainRational domRationalNB1NB2Copy( domRationalNB1NB2 );"<<endl;
	cDomainRational domRationalNB1NB2Copy( domRationalNB1NB2 );
	
	iReturn+=testCompareTwoEqualDomains( domRationalNB1NB2Copy, "domRationalNB1NB2Copy", domRationalNB1NB2Org, "domRationalNB1NB2Org" );
	iReturn+=testCompareTwoEqualDomains( domRationalNB1NB2, "domRationalNB1NB2", domRationalNB1NB2Org, "domRationalNB1NB2Org" );

	cout<<"cDomainRational * pDomRationalNB1NB2Clone = domRationalNB1NB2Copy.clone();"<<endl;
	cDomainRational * pDomRationalNB1NB2Clone = domRationalNB1NB2Copy.clone();

	iReturn+=testCompareTwoEqualDomains( *pDomRationalNB1NB2Clone, "pDomRationalNB1NB2Clone", domRationalNB1NB2Org, "domRationalNB1NB2Org" );
	iReturn+=testCompareTwoEqualDomains( domRationalNB1NB2Copy, "domRationalNB1NB2Copy", domRationalNB1NB2Org, "domRationalNB1NB2Org" );
	delete pDomRationalNB1NB2Clone;

	cout<<endl;
	cout<<"cDomainNaturalNumber domNaturalNumber3( 3 );"<<endl;
	cDomainNaturalNumber domNaturalNumber3( 3 );
	cout<<"cDomainNaturalNumberBit domNaturalNumberBit7( 7 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumberBit7( 7 );
	
	cout<<"cDomainRational domRationalNB7N3( domNaturalNumberBit7, domNaturalNumber3 );"<<endl;
	cDomainRational domRationalNB7N3( domNaturalNumberBit7, domNaturalNumber3 );
	
	cout<<"cDomainRational domRationalNB7N3Org( domNaturalNumberBit7, domNaturalNumber3 );"<<endl;
	cDomainRational domRationalNB7N3Org( domNaturalNumberBit7, domNaturalNumber3 );

	cout<<"cDomainRational domRationalNB7N3Copy( domRationalNB7N3 );"<<endl;
	cDomainRational domRationalNB7N3Copy( domRationalNB7N3 );
	
	iReturn+=testCompareTwoEqualDomains( domRationalNB7N3Copy, "domRationalNB7N3Copy", domRationalNB7N3Org, "domRationalNB7N3Org" );
	iReturn+=testCompareTwoEqualDomains( domRationalNB7N3, "domRationalNB7N3", domRationalNB7N3Org, "domRationalNB7N3Org" );

	cout<<"cDomainRational * pDomRationalNB7N3Clone = domRationalNB7N3Copy.clone();"<<endl;
	cDomainRational * pDomRationalNB7N3Clone = domRationalNB7N3Copy.clone();

	iReturn+=testCompareTwoEqualDomains( *pDomRationalNB7N3Clone, "pDomRationalNB7N3Clone", domRationalNB7N3Org, "domRationalNB7N3Org" );
	iReturn+=testCompareTwoEqualDomains( domRationalNB7N3Copy, "domRationalNB7N3Copy", domRationalNB7N3Org, "domRationalNB7N3Org" );
	delete pDomRationalNB7N3Clone;


	return iReturn;
}



/**
 * This function tests if the given value is in the given domain.
 *
 * methods tested:
 * 	- doubleFib round( const doubleFib dValue ) const;
 * 	- bool isElement( const doubleFib dValue ) const;
 *
 * @param domain the domain which should contain the given value
 * @param dMaxValue the value which the domain should contain
 * @return the number of errors occured in the test
 */
int checkInDomain( cDomainSingle & domain, doubleFib dValue ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	if ( domain.isElement( dValue ) ){
		cout<<"The value "<< dValue <<" is correctly inside the domain. "<<endl;
	}else{
		cerr<<"Error: The value "<< dValue <<" is not in the domain."<<endl;
		iReturn++;
	}
	const doubleFib dRoundedValue = domain.round( dValue );
	if ( dValue == dRoundedValue ){
		cout<<"The value "<< dValue <<" is correctly rounded from the domain to the value "<< dRoundedValue <<" . "<<endl;
	}else{
		cerr<<"Error: The value "<< dValue <<" is rounded from the domain to the value "<< dRoundedValue <<" . "<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This function tests if the given value is not in the given domain.
 *
 * methods tested:
 * 	- doubleFib round( const doubleFib dValue ) const;
 * 	- bool isElement( const doubleFib dValue ) const;
 *
 * @param domain the domain which should not contain the given value
 * @param dMaxValue the value which the domain shouldn't contain
 * @return the number of errors occured in the test
 */
int checkOutsideDomain( cDomainSingle & domain, doubleFib dValue ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	if ( ! domain.isElement( dValue ) ){
		cout<<"The value "<< dValue <<" is correctly not inside the domain. "<<endl;
	}else{
		cerr<<"Error: The value "<< dValue <<" is in the domain."<<endl;
		iReturn++;
	}
	const doubleFib dRoundedValue = domain.round( dValue );
	if ( dValue != dRoundedValue ){
		cout<<"The value "<< dValue <<" is correctly rounded from the domain to a different value . "<<endl;
	}else{
		cerr<<"Error: The value "<< dValue <<" is rounded from the domain to the value "<<
			dRoundedValue <<" , which is not different . "<<endl;
		iReturn++;
	}

	return iReturn;
}




/**
 * This function tests the value methods of the class.
 *
 * methods tested:
 * 	- doubleFib round( const doubleFib dValue ) const;
 * 	- bool isElement( const doubleFib dValue ) const;
 * 	- doubleFib getMaximum() const ;
 * 	- doubleFib getMinimum() const
 * 	- doubleFib getNull() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testValues( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the value methods"<<endl;
	
	for ( unsigned int iterationDom = 0; iterationDom < 64; iterationDom++ ){
		cout<<endl<<endl;
		//generate random rational domain
		const long lMinMantissa = rand() % 1024 - 512;
		const long lMinExponent = rand() % 32 - 16;
		const long lMaxMantissa = lMinMantissa + rand() % 1024;
		const long lMaxExponent = lMinExponent + rand() % 32;
		
		doubleFib dScaligFactorMantissa  = 1.0;
		if ( ( rand() % 10 ) == 0 ){
			dScaligFactorMantissa = double(rand() % 1024) / 32.0;
		}
		doubleFib dScaligFactorlExponent = 1.0;
		if ( ( rand() % 10 ) == 0 ){
			dScaligFactorlExponent = double(rand() % 1024) / 32.0;
		}
		
		cout<<"cDomainInteger domMantissa( "<< lMinMantissa <<", "<< lMaxMantissa <<", "<< dScaligFactorMantissa <<" );"<<endl;
		cDomainInteger domMantissa( lMinMantissa, lMaxMantissa, dScaligFactorMantissa );
		cout<<"cDomainInteger domExponent( "<< lMinExponent <<" ,"<< lMaxExponent <<", "<< dScaligFactorlExponent <<" );"<<endl;
		cDomainInteger domExponent( lMinExponent, lMaxExponent, dScaligFactorlExponent );
		
		cout<<"cDomainRational domRational( domMantissa, domExponent );"<<endl;
		cDomainRational domRational( domMantissa, domExponent );
		
		//test the values of the domain
		//test the minimum of the domain
		double dMinValue = (double)lMinMantissa * pow( 2.0, (double)lMaxExponent );
		double dOutsideMinMantissa = 0.0;
		if ( (double)(lMinMantissa - 1) * pow( 2.0, (double)lMaxExponent ) <
				(double)(lMinMantissa + 1) * pow( 2.0, (double)lMaxExponent ) ){
			dOutsideMinMantissa = (double)(lMinMantissa - 1) * pow( 2.0, (double)lMaxExponent );
		}else{
			dOutsideMinMantissa = (double)(lMinMantissa + 1) * pow( 2.0, (double)lMaxExponent );
		}
		double dOutsideMinExponent = 0.0;
		if ( (double)(lMinMantissa) * pow( 2.0, (double)lMaxExponent + 1 ) <
				(double)(lMinMantissa) * pow( 2.0, (double)lMaxExponent - 1 ) ){
			dOutsideMinExponent = (double)(lMinMantissa) * pow( 2.0, (double)lMaxExponent + 1 );
		}else{
			dOutsideMinExponent = (double)(lMinMantissa) * pow( 2.0, (double)lMaxExponent - 1 );
		}
		if ( ((double)lMinMantissa * pow( 2.0, (double)lMinExponent )) < (double)dMinValue ){
			dMinValue = lMinMantissa * pow( 2.0, lMinExponent );
			
			if ( (lMinMantissa - 1) * pow( 2.0, lMinExponent ) <
					(lMinMantissa + 1) * pow( 2.0, lMinExponent ) ){
				dOutsideMinMantissa = (double)(lMinMantissa - 1) * pow( 2.0, lMinExponent );
			}else{
				dOutsideMinMantissa = (double)(lMinMantissa + 1) * pow( 2.0, lMinExponent );
			}
			if ( (double)(lMinMantissa) * pow( 2.0, lMinExponent - 1 ) <
					(double)(lMinMantissa) * pow( 2.0, lMinExponent + 1 ) ){
				dOutsideMinExponent = (double)(lMinMantissa) * pow( 2.0, lMinExponent - 1 );
			}else{
				dOutsideMinExponent = (double)(lMinMantissa) * pow( 2.0, lMinExponent + 1 );
			}
		}
		if ( ((double)lMaxMantissa * pow( 2.0, (double)lMaxExponent )) < dMinValue ){
			dMinValue = (double)lMaxMantissa * pow( 2.0, (double)lMaxExponent );
			
			if ( (lMaxMantissa + 1) * pow( 2.0, lMaxExponent ) <
					(lMaxMantissa - 1) * pow( 2.0, lMaxExponent ) ){
				dOutsideMinMantissa = (double)(lMaxMantissa + 1) * pow( 2.0, lMaxExponent );
			}else{
				dOutsideMinMantissa = (double)(lMaxMantissa - 1) * pow( 2.0, lMaxExponent );
			}
			if ( (double)(lMaxMantissa) * pow( 2.0, lMaxExponent + 1 ) <
					(double)(lMaxMantissa) * pow( 2.0, lMaxExponent - 1 ) ){
				dOutsideMinExponent = (double)(lMaxMantissa) * pow( 2.0, lMaxExponent + 1 );
			}else{
				dOutsideMinExponent = (double)(lMaxMantissa) * pow( 2.0, lMaxExponent - 1 );
			}
		}
		if ( ((double)lMaxMantissa * pow( 2.0, (double)lMinExponent )) < dMinValue ){
			dMinValue = (double)lMaxMantissa * pow( 2.0, (double)lMinExponent );
			
			if ( (lMaxMantissa + 1) * pow( 2.0, lMinExponent ) <
					(lMaxMantissa - 1) * pow( 2.0, lMinExponent ) ){
				dOutsideMinMantissa = (double)(lMaxMantissa + 1) * pow( 2.0, lMinExponent );
			}else{
				dOutsideMinMantissa = (double)(lMaxMantissa - 1) * pow( 2.0, lMinExponent );
			}
			if ( (double)(lMaxMantissa) * pow( 2.0, lMinExponent - 1 ) <
					(double)(lMaxMantissa) * pow( 2.0, lMinExponent + 1 ) ){
				dOutsideMinExponent = (double)(lMaxMantissa) * pow( 2.0, lMinExponent - 1 );
			}else{
				dOutsideMinExponent = (double)(lMaxMantissa) * pow( 2.0, lMinExponent + 1 );
			}
		}
		if ( domRational.getMinimum() == dMinValue ){
			cout<<"The minimum of the created domain is correctly "<< dMinValue <<" . "<<endl;
		}else{
			cerr<<"Error: The minimum of the created domain is "<<
				domRational.getMinimum() <<", but should be "<< dMinValue <<""<<endl;
			iReturn++;
		}
		//test the maximum of the domain
		double dMaxValue = (double)lMinMantissa * pow( 2.0, (double)lMaxExponent );
		double dOutsideMaxMantissa = 0.0;
		if ( (double)(lMinMantissa - 1) * pow( 2.0, (double)lMaxExponent ) <
				(double)(lMinMantissa + 1) * pow( 2.0, (double)lMaxExponent ) ){
			dOutsideMaxMantissa = (double)(lMinMantissa - 1) * pow( 2.0, (double)lMaxExponent );
		}else{
			dOutsideMaxMantissa = (double)(lMinMantissa + 1) * pow( 2.0, (double)lMaxExponent );
		}
		double dOutsideMaxExponent = (double)(lMinMantissa) * pow( 2.0, (double)lMaxExponent + 1 );
		if ( dMaxValue < ((double)lMinMantissa * pow( 2.0, (double)lMinExponent )) ){
			dMaxValue = (double)lMinMantissa * pow( 2.0, (double)lMinExponent );
			
			if ( (double)(lMinMantissa + 1) * pow( 2.0, (double)lMinExponent ) <
					(double)(lMinMantissa - 1) * pow( 2.0, (double)lMinExponent ) ){
				dOutsideMaxMantissa = (double)(lMinMantissa - 1) * pow( 2.0, (double)lMinExponent );
			}else{
				dOutsideMaxMantissa = (double)(lMinMantissa + 1) * pow( 2.0, (double)lMinExponent );
			}
			if ( (double)(lMinMantissa) * pow( 2.0, (double)lMinExponent - 1 ) <
					(double)(lMinMantissa) * pow( 2.0, (double)lMinExponent + 1 ) ){
				dOutsideMaxExponent = (double)(lMinMantissa) * pow( 2.0, (double)lMinExponent + 1 );
			}else{
				dOutsideMaxExponent = (double)(lMinMantissa) * pow( 2.0, (double)lMinExponent - 1 );
			}
		}
		if ( dMaxValue < ((double)lMaxMantissa * pow( 2.0, (double)lMaxExponent )) ){
			dMaxValue = (double)lMaxMantissa * pow( 2.0, (double)lMaxExponent );
			
			if ( (double)(lMaxMantissa - 1) * pow( 2.0, (double)lMaxExponent ) <
					(double)(lMaxMantissa + 1) * pow( 2.0, (double)lMaxExponent ) ){
				dOutsideMaxMantissa = (double)(lMaxMantissa + 1) * pow( 2.0, (double)lMaxExponent );
			}else{
				dOutsideMaxMantissa = (double)(lMaxMantissa - 1) * pow( 2.0, (double)lMaxExponent );
			}
			if ( (double)(lMaxMantissa) * pow( 2.0, (double)lMaxExponent + 1 ) <
					(double)(lMaxMantissa) * pow( 2.0, (double)lMaxExponent - 1 ) ){
				dOutsideMaxExponent = (double)(lMaxMantissa) * pow( 2.0, (double)lMaxExponent - 1 );
			}else{
				dOutsideMaxExponent = (double)(lMaxMantissa) * pow( 2.0, (double)lMaxExponent + 1 );
			}
		}
		if ( dMaxValue < ((double)lMaxMantissa * pow( 2.0, (double)lMinExponent ))){
			dMaxValue = (double)lMaxMantissa * pow( 2.0, (double)lMinExponent );
			
			if ( (double)(lMaxMantissa - 1) * pow( 2.0, (double)lMinExponent ) <
					(double)(lMaxMantissa + 1) * pow( 2.0, (double)lMinExponent ) ){
				dOutsideMaxMantissa = (double)(lMaxMantissa + 1) * pow( 2.0, (double)lMinExponent );
			}else{
				dOutsideMaxMantissa = (double)(lMaxMantissa - 1) * pow( 2.0, (double)lMinExponent );
			}
			if ( (double)(lMaxMantissa) * pow( 2.0, (double)lMinExponent - 1 ) <
					(double)(lMaxMantissa) * pow( 2.0, (double)lMinExponent + 1 ) ){
				dOutsideMaxExponent = (double)(lMaxMantissa) * pow( 2.0, (double)lMinExponent + 1 );
			}else{
				dOutsideMaxExponent = (double)(lMaxMantissa) * pow( 2.0, (double)lMinExponent - 1 );
			}
		}
		if ( domRational.getMaximum() == dMaxValue ){
			cout<<"The maximum of the created domain is correctly "<< dMaxValue <<" . "<<endl;
		}else{
			cerr<<"Error: The maximum of the created domain is "<<
				domRational.getMaximum() <<", but should be "<< dMaxValue <<""<<endl;
			iReturn++;
		}
		//test the nullvalue of the domain
		double dNullValue = 0.0;
		if ( 0.0 < dMinValue  ){
			dNullValue = dMinValue;
		}else if ( dMaxValue < 0.0 ){
			dNullValue = dMaxValue;
		}else{
			dNullValue = domMantissa.getNull() * pow( 2.0, domExponent.getNull() );
		}
		if ( domRational.getNull() == dNullValue ){
			cout<<"The nullvalue of the created domain is correctly "<< dNullValue <<" . "<<endl;
		}else{
			cerr<<"Error: The nullvalue of the created domain is "<<
				domRational.getNull() <<", but should be "<< dNullValue <<""<<endl;
			iReturn++;
		}
		//test the domain bounderies
		cout<<endl<<"Testing the domain bounderies:"<<endl;
		
		if ( dOutsideMinExponent == 0.0 ){
			//mantissa is 0
			dOutsideMinExponent = -1.0;
		}
		if ( dOutsideMaxExponent == 0.0 ){
			//mantissa is 0
			dOutsideMaxExponent = 1.0;
		}
		
		iReturn += checkInDomain( domRational, dMinValue );
		iReturn += checkOutsideDomain( domRational, dOutsideMinMantissa );
		iReturn += checkOutsideDomain( domRational, dOutsideMinExponent );
		iReturn += checkInDomain( domRational, dMaxValue );
		iReturn += checkOutsideDomain( domRational, dOutsideMaxMantissa );
		iReturn += checkOutsideDomain( domRational, dOutsideMaxExponent );

		for ( unsigned int iterationValue = 0; iterationValue < 256; iterationValue++ ){
			//test if random values are in domain
			const long lMantissa = ( rand() % (lMaxMantissa - lMinMantissa + 1) ) + lMinMantissa;
			const long lExponent = ( rand() % (lMaxExponent - lMinExponent + 1) ) + lMinExponent;
			const doubleFib dValue  = domRational.round( (double)lMantissa * pow( 2.0, (double)lExponent ) );
			cout<<"Checking if value "<< dValue <<" ( "<< lMantissa <<" * 2^"<<
				lExponent <<" = "<< (double)lMantissa * pow( 2.0, (double)lExponent ) <<
				" ) is in the domain:"<<endl;
			iReturn += checkInDomain( domRational, dValue );
		}
		for ( unsigned int iterationValue = 0; iterationValue < 64; iterationValue++ ){
			//test if random values are outside domain
			bool bOneOutside = false;
			long lMantissa = 0;
			long lExponent = 0;
			if ( rand() % 2 == 0 ){
				//mantissa outside domain
				cout<<"generating above maximum mantissa ("<<lMaxMantissa<<")"<<endl;
				lMantissa = lMaxMantissa + 1 + ( rand() % (lMaxMantissa - lMinMantissa + 1) );
				bOneOutside = true;
			}else if ( rand() % 2 == 0 ){
				//mantissa outside domain
				cout<<"generating below minimum mantissa ("<<lMinMantissa<<")"<<endl;
				lMantissa = lMinMantissa - 1 - ( rand() % (lMaxMantissa - lMinMantissa + 1) );
				bOneOutside = true;
			}else{
				lMantissa = ( rand() % (lMaxMantissa - lMinMantissa + 1) ) + lMinMantissa;
			}
			if ( rand() % 2 == 0 ){
				//exponent outside domain
				cout<<"generating above maximum exponent ("<<lMaxExponent<<")"<<endl;
				lExponent = lMaxExponent + 1 + ( rand() % (lMaxExponent - lMinExponent + 1) );
				bOneOutside = true;
			}else if ( rand() % 2 == 0 ){
				//exponent outside domain
				cout<<"generating below minimum exponent ("<<lMinExponent<<")"<<endl;
				lExponent = lMinExponent - 1 - ( rand() % (lMaxExponent - lMinExponent + 1) );
				bOneOutside = true;
			}else{
				lExponent = ( rand() % (lMaxExponent - lMinExponent + 1) ) + lMinExponent;
			}
			if ( lMaxMantissa < lMantissa ){
				
				long lTestExponent = lExponent;
				long lTestMantissa = lMantissa;
				if ( ( 0 < lMaxMantissa ) && ( 0 < lMantissa ) ){
					while ( lMaxMantissa < lTestMantissa ){
						if (lTestMantissa / 2 * 2 != lTestMantissa){
							break;
						}
						lTestMantissa /= 2;
						lTestExponent++;
					}
				}
				if ( ( lMaxMantissa < 0 ) && ( lTestMantissa < 0 )  ){
					while ( lMaxMantissa < lTestMantissa ){
						lTestMantissa *= 2;
						lTestExponent--;
					}
				}
				if ( ( lMinMantissa <= lTestMantissa ) && ( lTestMantissa <= lMaxMantissa ) &&
						( lMinExponent <= lTestExponent ) && ( lTestExponent <= lMaxExponent ) ){
					bOneOutside = false;
				}
			}
			if ( lMantissa < lMinMantissa ){
				
				long lTestExponent = lExponent;
				long lTestMantissa = lMantissa;
				if ( ( lMinMantissa < 0 ) && ( lTestMantissa < 0 ) ){
					while ( lTestMantissa < lMinMantissa ){
						if (lTestMantissa / 2 * 2 != lTestMantissa){
							break;
						}
						lTestMantissa /= 2;
						lTestExponent++;
					}
				}
				if ( ( 0 < lMinMantissa ) && ( 0 < lTestMantissa ) ){
					while ( lTestMantissa < lMinMantissa ){
						lTestMantissa *= 2;
						lTestExponent--;
					}
				}
				if ( ( lMinMantissa <= lTestMantissa ) && ( lTestMantissa <= lMaxMantissa ) &&
						( lMinExponent <= lTestExponent ) && ( lTestExponent <= lMaxExponent ) ){
					bOneOutside = false;
				}
			}
			if ( lMaxExponent < lExponent ){
				
				long lTestExponent = lExponent;
				long lTestMantissa = lMantissa;
				while ( lMaxExponent < lTestExponent ){
					lTestMantissa *= 2;
					lTestExponent--;
				}
				if ( ( lMinMantissa <= lTestMantissa ) && ( lTestMantissa <= lMaxMantissa ) &&
						( lMinExponent <= lTestExponent ) && ( lTestExponent <= lMaxExponent ) ){
					bOneOutside = false;
				}
			}
			if ( lExponent < lMinExponent ){
				
				long lTestExponent = lExponent;
				long lTestMantissa = lMantissa;
				while ( lTestExponent < lMinExponent ){
					if (lTestMantissa / 2 * 2 != lTestMantissa){
						break;
					}
					lTestMantissa /= 2;
					lTestExponent++;
				}
				if ( ( lMinMantissa <= lTestMantissa ) && ( lTestMantissa <= lMaxMantissa ) &&
						( lMinExponent <= lTestExponent ) && ( lTestExponent <= lMaxExponent ) ){
					bOneOutside = false;
				}
			}
			
			if ( bOneOutside ){
				const doubleFib dValue = (double)lMantissa * pow( 2.0, (double)lExponent );
				cout<<"Checking if value "<< dValue <<" ( "<< lMantissa <<" * 2^"<<
					lExponent <<" = "<< (double)lMantissa * pow( 2.0, (double)lExponent ) <<
					" ) is not in the domain:"<<endl;
				iReturn += checkOutsideDomain( domRational, dValue );
			}else{//bouth inside the doamin
				const doubleFib dValue = domRational.round( (double)lMantissa * pow( 2.0, (double)lExponent ) );
				cout<<"Checking if value "<< dValue <<" ( "<< lMantissa <<" * 2^"<<
					lExponent <<" = "<< (double)lMantissa * pow( 2.0, (double)lExponent ) <<
					" ) is in the domain:"<<endl;
				iReturn += checkInDomain( domRational, dValue );
			}
		}
	}

	return iReturn;
}



/**
 * This function tests a in the xml -format stored cDomainRational.
 * The stored cDomainRational should contain two cDomainNaturalNumberBit
 * domains as it's mantissa and exponent domain.
 *
 * @param szFilename the name of the file wher the cDomainRational is stored
 * @param uiBitsMantissa the bits the mantissa domain has
 * @param uiBitsExponent the bits the exponent domain has
 * @return the number of errors occured in the test
 */
int testXmlDomain( const string szFilename, const unsigned int uiBitsMantissa,
		const unsigned int uiBitsExponent ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored domain:"<<endl;
	
	TiXmlDocument xmlDocVectorPosition( szFilename );
	bool loadOkay = xmlDocVectorPosition.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocVectorPosition );
	TiXmlElement * pXmlElement;

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();

		if ( szElementName == "rational" ){
			cout<<"The root element is correctly named \"rational\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"rational\"."<<endl;
			iReturn++;
		}
		
		TiXmlHandle xmlSubDomainHandle = xmlHandle.FirstChildElement();
	
		TiXmlElement * pXmlMantissaDomain = xmlSubDomainHandle.FirstChild().Element();
		if ( pXmlMantissaDomain ) {
			string szElementName = pXmlMantissaDomain->Value();
	
			if ( szElementName == "naturalNumberB" ){
				cout<<"The mantissa domainelement is correctly named \"naturalNumberB\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the mantissa domainelement is "<< szElementName <<" and not \"naturalNumberB\"."<<endl;
				iReturn++;
			}
			
			int iBitsLoaded = 0;
			const char * pcAttributBits = pXmlMantissaDomain->Attribute( "bit", &iBitsLoaded );
			
			if ( pcAttributBits == NULL ){
				cerr<<"Error: The mantissa domain has no attribute bits."<<endl;
				iReturn++;
			}else if ( iBitsLoaded == (int)uiBitsMantissa ) {
				cout<<"The number of bits of the mantissa domain are correctly \""<< uiBitsMantissa <<"\". "<<endl;
			}else{
				cerr<<"Error: The number of bits of the mantissa domain are \""<< iBitsLoaded
					<<"\", but should be \""<< uiBitsMantissa <<"\"."<<endl;
				iReturn++;
			}
		}else{// pXmlElement == NULL ->no mantissa handle
			cerr<<"Error: No mantissa domain handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
			return iReturn;
		}
		
		TiXmlElement * pXmlExponentDomain = pXmlMantissaDomain->NextSiblingElement();
		if ( pXmlExponentDomain ) {
			string szElementName = pXmlExponentDomain->Value();
	
			if ( szElementName == "naturalNumberB" ){
				cout<<"The exponent domainelement is correctly named \"naturalNumberB\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the exponent domainelement is "<< szElementName <<" and not \"naturalNumberB\"."<<endl;
				iReturn++;
			}
			
			int iBitsLoaded = 0;
			const char * pcAttributBits = pXmlExponentDomain->Attribute( "bit", &iBitsLoaded );
			
			if ( pcAttributBits == NULL ){
				cerr<<"Error: The exponent domain has no attribute bits."<<endl;
				iReturn++;
			}else if ( iBitsLoaded == (int)uiBitsExponent ) {
				cout<<"The number of bits of the exponent domain are correctly \""<< uiBitsExponent <<"\". "<<endl;
			}else{
				cerr<<"Error: The number of bits of the exponent domain are \""<< iBitsLoaded
					<<"\", but should be \""<< uiBitsExponent <<"\"."<<endl;
				iReturn++;
			}
		}else{// pXmlElement == NULL ->no exponent handle
			cerr<<"Error: No exponent domain handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
			return iReturn;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain to Xml, with 1 bit mantissa and 2 bit exponent domain "<<endl;
	
	cout<<"cDomainNaturalNumberBit domNaturalNumberBit1( 1 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumberBit1( 1 );
	cout<<"cDomainNaturalNumberBit domNaturalNumberBit2( 2 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumberBit2( 2 );
	
	cout<<"cDomainRational domRational1Nb1Nb2( domNaturalNumberBit1, domNaturalNumberBit2 );"<<endl;
	cDomainRational domRational1Nb1Nb2( domNaturalNumberBit1, domNaturalNumberBit2 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domRational1Nb1Nb2.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	bool bStoreSuccesfull = domRational1Nb1Nb2.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlDomain( szFileNameBuffer, 1, 2 );
	
	TiXmlDocument xmlDomRational1Nb1Nb2( szFileNameBuffer );
	bool loadOkay = xmlDomRational1Nb1Nb2.LoadFile();
	if ( loadOkay ){
		intFib outStatus = 0;
		cout<<"TiXmlHandle xmlHandle( &xmlDomRational1Nb1Nb2 ); "<<endl;
		TiXmlHandle xmlHandle( &xmlDomRational1Nb1Nb2 );
		
		cout<<"cDomainRational domRational1Nb1Nb2Loaded( xmlHandle.FirstChildElement().Element(), outStatus ); "<<endl;
		cDomainRational domRational1Nb1Nb2Loaded( xmlHandle.FirstChildElement().Element(), outStatus );
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualDomains( domRational1Nb1Nb2Loaded, "domRational1Nb1Nb2Loaded", domRational1Nb1Nb2, "domRational1Nb1Nb2" );
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain to Xml, with 43 bit mantissa and 7 bit exponent domain "<<endl;
	
	cout<<"cDomainNaturalNumberBit domNaturalNumberBit43( 43 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumberBit43( 43 );
	cout<<"cDomainNaturalNumberBit domNaturalNumberBit7( 7 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumberBit7( 7 );
	
	cout<<"cDomainRational domRational1Nb43Nb7( domNaturalNumberBit43, domNaturalNumberBit7 );"<<endl;
	cDomainRational domRational1Nb43Nb7( domNaturalNumberBit43, domNaturalNumberBit7 );
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domRational1Nb43Nb7.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = domRational1Nb43Nb7.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlDomain( szFileNameBuffer, 43, 7 );

	TiXmlDocument xmlDomRational1Nb43Nb7( szFileNameBuffer );
	loadOkay = xmlDomRational1Nb43Nb7.LoadFile();
	if ( loadOkay ){
		intFib outStatus = 0;
		cout<<"TiXmlHandle xmlHandle( &xmlDomRational1Nb43Nb7 ); "<<endl;
		TiXmlHandle xmlHandle( &xmlDomRational1Nb43Nb7 );
		
		cout<<"cDomainRational domRational1Nb43Nb7Loaded( xmlHandle.FirstChildElement().Element(), outStatus ); "<<endl;
		cDomainRational domRational1Nb43Nb7Loaded( xmlHandle.FirstChildElement().Element(), outStatus );
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualDomains( domRational1Nb43Nb7Loaded, "domRational1Nb43Nb7Loaded", domRational1Nb43Nb7, "domRational1Nb43Nb7" );
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a reational domain, with 1 bit mantissa and 2 bit exponent domain"<<endl;
	
	cout<<"cDomainNaturalNumberBit domNaturalNumberBit1( 1 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumberBit1( 1 );
	cout<<"cDomainNaturalNumberBit domNaturalNumberBit2( 2 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumberBit2( 2 );
	
	cout<<"cDomainRational domRational1Nb1Nb2( domNaturalNumberBit1, domNaturalNumberBit2 );"<<endl;
	cDomainRational domRational1Nb1Nb2( domNaturalNumberBit1, domNaturalNumberBit2 );

	//test get compressed size
	unsigned int uiCompressedSize = 8 + domNaturalNumberBit1.getCompressedSize()
		 + domNaturalNumberBit1.getCompressedSize();
	if ( domRational1Nb1Nb2.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domRational1Nb1Nb2.getCompressedSize() << ", but should be "<< uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domRational1Nb1Nb2.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	cout<<"domRational1Nb43Nb7.store( *pFile, (char)0x"<< hex<<(unsigned short)(cRestBit)<<dec <<", "<< (int)cNumberOfRestBit <<" );"<<endl;
	bool bStoreSuccesfull = domRational1Nb1Nb2.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTestDomRational1Nb1Nb2Byts[] = {(char)0x80, (char)0x00, (char)0x01, (char)0x00, (char)0x02, (char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomRational1Nb1Nb2Byts, (uiCompressedSize + cNumberOfRestBit + 8) / 8 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a reational domain, with 43 bit mantissa and 7 bit exponent domain "<<endl;
	
	cout<<"cDomainNaturalNumberBit domNaturalNumberBit43( 43 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumberBit43( 43 );
	cout<<"cDomainNaturalNumberBit domNaturalNumberBit7( 7 );"<<endl;
	cDomainNaturalNumberBit domNaturalNumberBit7( 7 );
	
	cout<<"cDomainRational domRational1Nb43Nb7( domNaturalNumberBit43, domNaturalNumberBit7 );"<<endl;
	cDomainRational domRational1Nb43Nb7( domNaturalNumberBit43, domNaturalNumberBit7 );

	//test get compressed size
	uiCompressedSize = 8 + domNaturalNumberBit43.getCompressedSize()
		 + domNaturalNumberBit7.getCompressedSize();
	if ( domRational1Nb43Nb7.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domRational1Nb43Nb7.getCompressedSize() << ", but should be "<< uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domRational1Nb43Nb7.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"domRational1Nb43Nb7.store( *pFile, (char)0x"<< hex<<(unsigned short)(cRestBit)<<dec <<", "<< (int)cNumberOfRestBit <<" );"<<endl;
	bStoreSuccesfull = domRational1Nb43Nb7.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTestDomRational1Nb43Nb7Byts[] = {(char)0x80, (char)0x00, (char)0x2B, (char)0x00, (char)0x07, (char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomRational1Nb43Nb7Byts, (uiCompressedSize + cNumberOfRestBit + 8) / 8 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a reational domain, with 3 Bit shift with restbit (char)0x05"<<endl;
	
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domRational1Nb43Nb7S3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x05;
	cNumberOfRestBit = 3;
	cout<<"domRational1Nb43Nb7.store( *pFile, (char)0x"<< hex<<cRestBit<<dec <<", "<< (int)cNumberOfRestBit <<" );"<<endl;
	bStoreSuccesfull = domRational1Nb43Nb7.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 3 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTestDomRational1Nb43Nb7S3Byts[] = {(char)0x05, (char)0x04, (char)0x58, (char)0x01, (char)0x38, (char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomRational1Nb43Nb7S3Byts, (uiCompressedSize + cNumberOfRestBit + 8) / 8 );


	return iReturn;
}



/**
 * This method store -value -method of the class.
 *
 * methods tested:
 * 	- unsignedIntFib getCompressedSizeForValue() const;
 * 	- bool storeValue( doubleFib dValue, ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 * 	- doubleFib restoreValue( cReadBits & iBitStream, intFib & outStatus ) const
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStoreValue( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing and restoring of numbers"<<endl;

	for ( unsigned int iterationDom = 0; iterationDom < 64; iterationDom++ ){
		cout<<endl<<endl;
		//generate random rational domain
		const long lMinMantissa = rand() % 1024 - 512;
		const long lMinExponent = rand() % 32 - 16;
		const long lMaxMantissa = lMinMantissa + rand() % 1024;
		const long lMaxExponent = lMinExponent +rand() % 32;
		
		doubleFib dScaligFactorMantissa  = 1.0;
		if ( ( rand() % 10 ) == 0 ){
			dScaligFactorMantissa = double(rand() % 1024) / 32.0;
		}
		doubleFib dScaligFactorlExponent = 1.0;
		if ( ( rand() % 10 ) == 0 ){
			dScaligFactorlExponent = double(rand() % 1024) / 32.0;
		}
		
		cout<<"cDomainInteger domMantissa( "<< lMinMantissa <<", "<< lMaxMantissa <<", "<< dScaligFactorMantissa <<" );"<<endl;
		cDomainInteger domMantissa( lMinMantissa, lMaxMantissa, dScaligFactorMantissa );
		cout<<"cDomainInteger domExponent( "<< lMinExponent <<" ,"<< lMaxExponent <<", "<< dScaligFactorlExponent <<" );"<<endl;
		cDomainInteger domExponent( lMinExponent, lMaxExponent, dScaligFactorlExponent );
		
		cout<<"cDomainRational domRational( domMantissa, domExponent );"<<endl;
		cDomainRational domRational( domMantissa, domExponent );

		//test getCompressedSizeForValue()
		const unsigned long uiCompressedSizeForValue =
			domMantissa.getCompressedSizeForValue() +
			domExponent.getCompressedSizeForValue();
		if ( domRational.getCompressedSizeForValue() == uiCompressedSizeForValue ){
		
			cout<<"The compressed size of the domain is correctly "<<
				uiCompressedSizeForValue <<" . "<<endl;
		}else{
			cerr<<"Error: The compressed size of the domain is "<<
				domRational.getCompressedSizeForValue() << ", but should be "<<
				uiCompressedSizeForValue <<" . "<<endl;
			iReturn++;
		}

		//for some random values, even some not in the domain
		for ( unsigned int iterationValue = 0; iterationValue < 64; iterationValue++ ){
			
			long lMantissa = 0;
			long lExponent = 0;
			if ( rand() % 16 == 0 ){
				//mantissa outside domain
				cout<<"generating above maximum mantissa ("<<lMaxMantissa<<")"<<endl;
				lMantissa = lMaxMantissa + 1 + ( rand() % (lMaxMantissa - lMinMantissa + 1) );
			}else if ( rand() % 16 == 0 ){
				//mantissa outside domain
				cout<<"generating below minimum mantissa ("<<lMinMantissa<<")"<<endl;
				lMantissa = lMinMantissa - 1 - ( rand() % (lMaxMantissa - lMinMantissa + 1) );
			}else{
				lMantissa = ( rand() % (lMaxMantissa - lMinMantissa + 1) ) + lMinMantissa;
			}
			if ( rand() % 16 == 0 ){
				//exponent outside domain
				cout<<"generating above maximum exponent ("<<lMaxExponent<<")"<<endl;
				lExponent = lMaxExponent + 1 + ( rand() % (lMaxExponent - lMinExponent + 1) );
			}else if ( rand() % 16 == 0 ){
				//exponent outside domain
				cout<<"generating below minimum exponent ("<<lMinExponent<<")"<<endl;
				lExponent = lMinExponent - 1 - ( rand() % (lMaxExponent - lMinExponent + 1) );
			}else{
				lExponent = ( rand() % (lMaxExponent - lMinExponent + 1) ) + lMinExponent;
			}
			const doubleFib dValue = (double)lMantissa * pow( 2.0, (double)lExponent );
			
			//store number (with restbit from 0 till 7)
			char szFileNameBuffer[128];
			szFileNameBuffer[0] = 0;
			strcat( strcat( szFileNameBuffer,
				(char*)DIR_OUTPUT ), "domRationalValue.fib" );
			ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
			
			unsigned char cNumberOfRestBit = rand() % 8;
			const unsigned char cNumberOfRestBitOrg = cNumberOfRestBit;
			char cRestBit = rand() % 256;
			cRestBit = ((unsigned char)(cRestBit)) >> (8 - cNumberOfRestBit);
			const char cRestBitOrg = cRestBit;
			cout<<"domRational.storeValue( "<< dValue <<", *pFile, (char)0x"<<
				hex<<(unsigned short)(cRestBit)<<dec <<", "<< (int)cNumberOfRestBit <<" );"<<endl;
			const bool bStoreSuccesfull = domRational.storeValue( dValue,
				*pFile, cRestBit, cNumberOfRestBit );
			(*pFile) << cRestBit;
			delete pFile;
			
			if ( bStoreSuccesfull ){
			
				cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
			}else{
				cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
				iReturn++;
			}
			
			const unsigned char cNumberOfRestBitCorrect = (cNumberOfRestBitOrg + uiCompressedSizeForValue) % 8;
			if ( cNumberOfRestBit == cNumberOfRestBitCorrect ){
				cout<<"The number of restbit is "<< (unsigned short)cNumberOfRestBit <<". "<<endl;
			}else{
				cerr<<"Error: The number of restbit is "<< (unsigned short)cNumberOfRestBit <<
					", but the number of restbit should be "<< (unsigned short)cNumberOfRestBitCorrect <<" . "<<endl;
				iReturn++;
			}
			
			//restore number
			ifstream * fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
			char cRestBitLoaded = (char)0x00;
			cReadBits iBitStream( * fileInXml );
			const unsigned int uiBitsLoaded = iBitStream.readBits( &cRestBitLoaded, cNumberOfRestBitOrg );
			if ( uiBitsLoaded != cNumberOfRestBitOrg ){
				cerr<<"Error: The laoded number of (rest)bits is "<< uiBitsLoaded <<
					" , but it should be "<< cNumberOfRestBitOrg <<" ."<<endl;
				iReturn++;
			}
			if ( cRestBitOrg != cRestBitLoaded ){
				cerr<<"Error: The loaded restbit is "<<hex<<(unsigned short)(cRestBitLoaded)<<dec <<
					" , but it should be "<<hex<<(unsigned short)(cRestBitOrg)<<dec <<" ."<<endl;
				iReturn++;
			}
			intFib outStatus = 0;
			const doubleFib dValueLoaded = domRational.restoreValue( iBitStream, outStatus );
			delete fileInXml;
			
			if ( outStatus == 0 ){
			
				cout<<"The data was loaded successfull. "<<endl;
			}else{
				cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
				iReturn++;
			}
			//check if restored number equals the rounded stored number
			const doubleFib dValueRouded = domRational.round( dValue );
			
			if ( dValueLoaded == dValueRouded ){
				cout<<"The restored number is correctly "<< dValueLoaded <<" . "<<endl;

			}else{
				cerr<<"Error: The restored number is "<< dValueLoaded <<
					" , but should be "<< dValueRouded <<" . "<<endl;
				iReturn++;
			}
		}
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed restoring more bits than in file"<<endl;

	cout<<"cDomainNaturalNumberBit domMantissaB4( 4 );"<<endl;
	cDomainNaturalNumberBit domMantissaB4( 4 );
	cout<<"cDomainNaturalNumberBit domExponentB4( 4 );"<<endl;
	cDomainNaturalNumberBit domExponentB4( 4 );
	
	cout<<"cDomainRational domRationalB8( domMantissaB4, domExponentB4 );"<<endl;
	cDomainRational domRationalB8( domMantissaB4, domExponentB4 );

	//test getCompressedSizeForValue()
	const unsigned long uiCompressedSizeForValue = 8;
	if ( domRationalB8.getCompressedSizeForValue() == uiCompressedSizeForValue ){
	
		cout<<"The compressed size of the domain is correctly "<<
			uiCompressedSizeForValue <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domRationalB8.getCompressedSizeForValue() << ", but should be "<<
			uiCompressedSizeForValue <<" . "<<endl;
		iReturn++;
	}

	long lMantissa = 15;
	long lExponent = 15;
	const doubleFib dValue = (double)lMantissa * pow( 2.0, (double)lExponent );
	
	//store number (with restbit from 0 till 7)
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domRationalValueB8.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	unsigned char cNumberOfRestBit = 0;
	char cRestBit = (char)0x00;
	cout<<"domRationalB8.storeValue( "<< dValue <<", *pFile, (char)0x"<<
		hex<<(unsigned short)(cRestBit)<<dec <<", "<< (int)cNumberOfRestBit <<" );"<<endl;
	const bool bStoreSuccesfull = domRationalB8.storeValue( dValue,
		*pFile, cRestBit, cNumberOfRestBit );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( cNumberOfRestBit == 0 ){
		cout<<"The number of restbit is "<< (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The number of restbit is "<< (unsigned short)cNumberOfRestBit <<
			", but the number of restbit should be 0 . "<<endl;
		iReturn++;
	}
	
	cout<<"cDomainNaturalNumberBit domMantissaB8( 8 );"<<endl;
	cDomainNaturalNumberBit domMantissaB8( 8 );
	cout<<"cDomainNaturalNumberBit domExponentB8( 8 );"<<endl;
	cDomainNaturalNumberBit domExponentB8( 8 );
	
	cout<<"cDomainRational domRationalB16( domMantissaB8, domExponentB8 );"<<endl;
	cDomainRational domRationalB16( domMantissaB8, domExponentB8 );
	//restore number
	ifstream * fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
	cReadBits iBitStream( * fileInXml );
	intFib outStatus = 0;
	const doubleFib dValueLoaded = domRationalB16.restoreValue( iBitStream, outStatus );
	delete fileInXml;
	
	if ( outStatus != 0 ){
	
		cout<<"The data was correctly not loaded. (outStatus="<< outStatus <<")."<<endl;
	}else{
		cerr<<"Error: The data was loaded."<<endl;
		iReturn++;
	}
	if ( dValueLoaded == 0.0 ){
		cout<<"The restored number is correctly "<< dValueLoaded <<" . "<<endl;

	}else{
		cerr<<"Error: The restored number is "<< dValueLoaded <<
			" , but should be "<< 0.0 <<" . "<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests the createGoodDomain() function of the
 * cDomainSingle class.
 *
 * functions tested:
 * 	- static cDomainSingle * cDomainSingle::
 * 		createGoodDomain( list< doubleFib > & liValues );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCreateGoodDomain( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the createGoodDomain() function of the cDomainSingle class on an empty list"<<endl;
	
	cout<<"list< doubleFib > liValues;"<<endl;
	list< doubleFib > liValues;
	
	cout<<"cDomainSingle * pDomainSingle = cDomainSingle::createGoodDomain( liValues );"<<endl;
	cDomainSingle * pDomainSingle = cDomainSingle::createGoodDomain( liValues );
	
	//check the getType() methode
	if ( pDomainSingle->getType() == "DomainNaturalNumberBit" ){
	
		iReturn += testIntegerDomainLong( ((cDomainIntegerBasis*)pDomainSingle), 0, 0, 1.0 );
	}else{
		cerr<<"Error: The type generated is not \"DomainNaturalNumberBit\" ; it is : "<<pDomainSingle->getType()<<endl;
		iReturn++;
	}
	delete pDomainSingle;
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the createGoodDomain() function on an list with the numbers 1, 2 and 3"<<endl;
	
	cout<<"liValues.push_back( 1 );"<<endl;
	liValues.push_back( 1 );
	cout<<"liValues.push_back( 2 );"<<endl;
	liValues.push_back( 2 );
	cout<<"liValues.push_back( 3 );"<<endl;
	liValues.push_back( 3 );

	cout<<"pDomainSingle = cDomainSingle::createGoodDomain( liValues );"<<endl;
	pDomainSingle = cDomainSingle::createGoodDomain( liValues );
	
	//check the getType() methode
	if ( pDomainSingle->getType() == "DomainInteger" ){
	
		iReturn += testIntegerDomainLong( ((cDomainIntegerBasis*)pDomainSingle), 1, 3, 1.0 );
	}else{
		cerr<<"Error: The type generated is not \"DomainInteger\" ; it is : "<<pDomainSingle->getType()<<endl;
		iReturn++;
	}
	delete pDomainSingle;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the createGoodDomain() function on random lists "<<endl;
	
	const unsigned long long RAND_MAX_HALF = RAND_MAX / 2;
	
	for ( unsigned int iteration = 1; iteration <= 256; iteration++ ){
		
		list< doubleFib > liValues2;
		unsigned long ulNumberOfValues = (rand() % 64) * (rand() % 64) + 1;
		
		cout<<endl<<"Creating random list with "<< ulNumberOfValues <<" values. "<<endl;
		cout<<"Values generated: ";
		
		for ( unsigned long ulActualNumber = 1;
				ulActualNumber < ulNumberOfValues; ulActualNumber++ ){
			
			const doubleFib dNumber = ((doubleFib)(rand() - RAND_MAX_HALF)) / 256.0;
			liValues2.push_back( dNumber );
			cout<<dNumber<<";";
		}
		cout<<endl;
		
		cout<<"pDomainSingle = cDomainSingle::createGoodDomain( liValues2 );"<<endl;
		pDomainSingle = cDomainSingle::createGoodDomain( liValues2 );
		
		cout<<"Testing generated domain: ";
		bool bTestOk = true;
		for ( list< doubleFib >::iterator itrValue = liValues2.begin();
				itrValue != liValues2.end(); itrValue++ ){
			
			if ( ! pDomainSingle->isElement( * itrValue ) ){
				cerr<<"Error: The value "<< (* itrValue) <<" is not in the domain."<<endl;
				iReturn++;
				bTestOk = false;
			}
		}
		if ( bTestOk ){
			cout<<"OK"<<endl;
		}else{
			cout<<"FAIL"<<endl;
		}
		
		delete pDomainSingle;
	}

	return iReturn;
}





















