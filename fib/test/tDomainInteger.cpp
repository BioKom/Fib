/**
 * @file tDomainInteger
 * file name: tDomainInteger.cpp
 * @author Betti Oesterholz
 * @date 16.05.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for domains of the class cDomainInteger.
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
 * This file contains the test for the class cDomainInteger,
 * which represents a domain for natural numbers.
 *
 *
 *
 *  What's tested of class cDomainInteger:
 * 	- cDomainInteger( longFib lInMinNumber, longFib lInMaxNumber );
 * 	- cDomainInteger( longFib lInMinNumber, longFib lInMaxNumber, doubleFib dScalingFactor );
 * 	- cDomainInteger( const cDomainInteger &domain );
 * 	- string getType() const;
 * 	- bool isElement( const doubleFib dValue ) const;
 * 	- doubleFib round( const doubleFib dValue ) const;
 * 	- doubleFib getMaximum( ) const;
 * 	- doubleFib getMinimum() const
 * 	- doubleFib getNull( ) const;
 * 	- bool isUnscaledElement( const longFib lValue ) const;
 * 	- longFib roundUnscaled( const longFib lValue ) const;
 * 	- longFib getMaximumUnscaled( ) const;
 * 	- longFib getMinimumUnscaled( ) const;
 * 	- longFib getNullUnscaled( ) const;
 * 	- cDomainInteger *clone() const;
 * 	- operator==( const cDomain &domain ) const;
 * 	- equal( const cDomain &domain ) const;
 * 	- bool storeXml( ostringstream & ostream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream & stream, char & cRestBit, unsigned char & uiRestMaxPosition ) const;
 * 	- unsignedIntFib getCompressedSizeForValue() const;
 * 	- bool storeValue( doubleFib dValue, ostream & stream, char & cRestBit, unsigned char & uiRestMaxPosition ) const;
 * 	- bool storeUnscaledValue( longFib lValue, ostream & stream, char & cRestBit, unsigned char & uiRestMaxPosition ) const;
 * 	- doubleFib restoreValue( cReadBits & iBitStream, intFib & outStatus ) const;
 * 	- longFib restoreIntegerValue( cReadBits & iBitStream, intFib & outStatus )
 *
 * 	- static cDomainIntegerBasis * cDomainIntegerBasis::createGoodDomain( list< longFib > & liValues );
 */
/*
History:
16.05.2010  Oesterholz  created
28.09.2010  Oesterholz  createGoodDomain() added
30.03.2011  Oesterholz  storing to binary stream
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
12.05.2013  Oesterholz  getDigits() andling changed (now version for integers)
03.09.2013  Oesterholz  reading scaling factor adapted
*/



#include "version.h"

#include "cDomainIntegerBasis.h"
#include "cDomainInteger.h"
#include "cDomainNaturalNumber.h"
#include "cDomainVector.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <iomanip>
#include <vector>
#include <ctime>

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif


using namespace fib;
using namespace std;

/*used methods from tDomainTools*/
extern int testIntegerDomainShort( cDomainIntegerBasis *domainToTest,
	longFib lMinNumber, longFib lMaxNumber, doubleFib dScalingFactor );
extern int testIntegerDomainLong( cDomainIntegerBasis *domainToTest,
	longFib lMinNumber, longFib lMaxNumber, doubleFib dScalingFactor );

//testmethods
int testConstructor( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testCopy( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );
int testStoreValue( unsigned long &ulTestphase );

int testCreateGoodDomain( unsigned long &ulTestphase );


int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time(NULL) );
	
	cout<<endl<<"Running Test for cDomainInteger methods"<<endl;
	cout<<      "======================================="<<endl;

	iReturn += testConstructor( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testStoreValue( ulTestphase );
	//cDomainIntegerBasis
	iReturn += testCreateGoodDomain( ulTestphase );

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}
	
	return iReturn;
}


/**
 * This method tests the constructors of the class.
 *
 * methods tested:
 * 	- cDomainInteger( longFib lInMinNumber, longFib lInMaxNumber );
 * 	- cDomainInteger( longFib lInMinNumber, longFib lInMaxNumber, doubleFib dScalingFactor );
 * 	- string getType() const;
 * 	- bool isElement( const doubleFib dValue ) const;
 * 	- doubleFib round( const doubleFib dValue ) const;
 * 	- doubleFib getMaximum( ) const ;
 * 	- doubleFib getNull( ) const;
 * 	- bool isUnscaledElement( const longFib lValue ) const;
 * 	- longFib roundUnscaled( const longFib lValue ) const;
 * 	- longFib getMaximumUnscaled( ) const;
 * 	- longFib getMinimumUnscaled( ) const;
 * 	- longFib getNullUnscaled( ) const;
 * 	- cDomainInteger *clone() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testConstructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with minimal number 0, maximal number 4 and scaling factor 1"<<endl;
	
	cout<<"testDomainInteger1 = new cDomainInteger( 0, 4 );"<<endl;
	cDomainInteger *testDomainInteger1 = new cDomainInteger( 0, 4 );
	
	//check the getType() methode
	if ( testDomainInteger1->getType() == "DomainInteger" ){
	
		cout<<"The correct type \"DomainInteger\" is given."<<endl;
	}else{
		cerr<<"Error: The type given is not \"DomainInteger\" ; it is : "<<testDomainInteger1->getType()<<endl;
		iReturn++;
	}
	
	iReturn += testIntegerDomainLong( testDomainInteger1, 0, 4, 1.0 );
	delete testDomainInteger1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with minimal number -5, maximal number 13 and scaling factor 1"<<endl;
	
	cout<<"testDomainInteger1 = new cDomainInteger( -5, 13 );"<<endl;
	testDomainInteger1 = new cDomainInteger( -5, 13 );
	
	//check the getType() methode
	if ( testDomainInteger1->getType() == "DomainInteger" ){
	
		cout<<"The correct type \"DomainInteger\" is given."<<endl;
	}else{
		cerr<<"Error: The type given is not \"cDomainInteger\" ; it is : "<<testDomainInteger1->getType()<<endl;
		iReturn++;
	}
	
	iReturn += testIntegerDomainLong( testDomainInteger1, -5, 13, 1.0 );
	delete testDomainInteger1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with minimal number 6, maximal number 13 and scaling factor 1"<<endl;
	
	cout<<"testDomainInteger1 = new cDomainInteger( 6, 13 );"<<endl;
	testDomainInteger1 = new cDomainInteger( 6, 13 );
	
	//check the getType() methode
	if ( testDomainInteger1->getType() == "DomainInteger" ){
	
		cout<<"The correct type \"DomainInteger\" is given."<<endl;
	}else{
		cerr<<"Error: The type given is not \"cDomainInteger\" ; it is : "<<testDomainInteger1->getType()<<endl;
		iReturn++;
	}
	
	iReturn += testIntegerDomainLong( testDomainInteger1, 6, 13, 1.0 );
	delete testDomainInteger1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with minimal number -29, maximal number 126 and scaling factor 1/16"<<endl;
	
	cout<<"testDomainInteger1 = new cDomainInteger( -29, 126, 1.0/16.0 );"<<endl;
	testDomainInteger1 = new cDomainInteger( -29, 126, 1.0/16.0 );
	
	//check the getType() methode
	if ( testDomainInteger1->getType() == "DomainInteger" ){
	
		cout<<"The correct type \"DomainInteger\" is given."<<endl;
	}else{
		cerr<<"Error: The type given is not \"cDomainInteger\" ; it is : "<<testDomainInteger1->getType()<<endl;
		iReturn++;
	}
	iReturn += testIntegerDomainLong( testDomainInteger1, -29, 126, 1.0/16.0 );
	delete testDomainInteger1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with minimal number 12945, maximal number 81384 and scaling factor 1/256"<<endl;
	
	cout<<"testDomainInteger1 = new cDomainInteger( 12945, 81384, 1.0/256.0 );"<<endl;
	testDomainInteger1 = new cDomainInteger( 12945, 81384, 1.0/256.0 );
	
	iReturn += testIntegerDomainShort( testDomainInteger1, 12945, 81384, 1.0/256.0 );
	delete testDomainInteger1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with minimal number -38627, maximal number 813 and scaling factor 1/19"<<endl;
	
	cout<<"testDomainInteger1 = new cDomainInteger( -38627, 813, 1.0/19.0 );"<<endl;
	testDomainInteger1 = new cDomainInteger( -38627, 813, 1.0/19.0 );
	
	iReturn += testIntegerDomainShort( testDomainInteger1, -38627, 813, 1.0/19.0 );
	delete testDomainInteger1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with minimal number -256, maximal number 256 and scaling factor 19"<<endl;
	
	cout<<"testDomainInteger1 = new cDomainInteger( -256, 256, 19.0 );"<<endl;
	testDomainInteger1 = new cDomainInteger( -256, 256, 19.0 );
	
	iReturn += testIntegerDomainShort( testDomainInteger1, -256, 256, 19.0 );
	delete testDomainInteger1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with minimal number 0, maximal number 0 and scaling factor 19"<<endl;
	
	cout<<"testDomainInteger1 = new cDomainInteger( 0, 0, 19.0 );"<<endl;
	testDomainInteger1 = new cDomainInteger( 0, 0, 19.0 );
		
	iReturn += testIntegerDomainShort( testDomainInteger1, 0, 0, 19.0 );
	delete testDomainInteger1;
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple with minimal number -12, maximal number 48 and scaling factor 123456789"<<endl;
	
	cout<<"testDomainInteger1 = new cDomainInteger( -12, 48, 123456789.0 );"<<endl;
	testDomainInteger1 = new cDomainInteger( -12, 48, 123456789.0 );
	
	iReturn += testIntegerDomainShort( testDomainInteger1, -12, 48, 123456789.0 );
	delete testDomainInteger1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with minimal number 256, maximal number -256 and scaling factor 5"<<endl;
	
	cout<<"testDomainInteger1 = new cDomainInteger( 256, -256, 5.0 );"<<endl;
	testDomainInteger1 = new cDomainInteger( 256, -256, 5.0 );
	
	iReturn += testIntegerDomainShort( testDomainInteger1, -256, 256, 5.0 );
	delete testDomainInteger1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with minimal number -45, maximal number -256 and scaling factor 5"<<endl;
	
	cout<<"testDomainInteger1 = new cDomainInteger( -45, -256, 5.0 );"<<endl;
	testDomainInteger1 = new cDomainInteger( -45, -256, 5.0 );
	
	iReturn += testIntegerDomainShort( testDomainInteger1, -256, -45, 5.0 );
	delete testDomainInteger1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with minimal number 5621, maximal number 2998 and scaling factor 31"<<endl;
	
	cout<<"testDomainInteger1 = new cDomainInteger( 5621, 2998, 31.0 );"<<endl;
	testDomainInteger1 = new cDomainInteger( 5621, 2998, 31.0 );
	
	iReturn += testIntegerDomainShort( testDomainInteger1, 2998, 5621, 31.0 );
	delete testDomainInteger1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with minimal number 5621, maximal number 2998 and scaling factor -5"<<endl;
	
	cout<<"testDomainInteger1 = new cDomainInteger( 5621, 2998, -5 );"<<endl;
	testDomainInteger1 = new cDomainInteger( 5621, 2998, -5 );
	
	iReturn += testIntegerDomainShort( testDomainInteger1, 2998, 5621, 5 );
	delete testDomainInteger1;


	return iReturn;
}



/**
 * This method tests the equal() method and the operator== of two given
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
	
		cout<<"The "<<szNameDomain1<<" is equal to "<<szNameDomain2<<"."<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is not equal to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	if ( domain1==domain2 ){
	
		cout<<"The "<<szNameDomain1<<" is equal (operator==) to "<<
			szNameDomain2<<"."<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is not equal (operator==) to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the equal() method and the operator== of two given
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
	
		cout<<"The "<<szNameDomain1<<" is not equal to "<<szNameDomain2<<"."<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is equal to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	if ( ! (domain1==domain2) ){
	
		cout<<"The "<<szNameDomain1<<" is not equal (operator==) to "<<
			szNameDomain2<<"."<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is equal (operator==) to "<<
			szNameDomain2<<"."<<endl;
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

	//create cDomainIntegers to compare
	cout<<"cDomainInteger domainInteger1Min0Max8( 0, 8 );"<<endl;
	cDomainInteger domainInteger1Min0Max8( 0, 8 );
	cout<<"cDomainInteger domainInteger2Min0Max8( 0, 8 );"<<endl;
	cDomainInteger domainInteger2Min0Max8( 0, 8 );
	cout<<"cDomainInteger domainInteger1Min8Max0( 8, 0 );"<<endl;
	cDomainInteger domainInteger1Min8Max0( 8, 0 );
	cout<<"cDomainInteger domainInteger1Min0Max9( 0, 9 );"<<endl;
	cDomainInteger domainInteger1Min0Max9( 0, 9 );
	cout<<"cDomainInteger domainInteger1Minm3Max8( -3, 8 );"<<endl;
	cDomainInteger domainInteger1Minm3Max8( -3, 8 );
	cout<<"cDomainInteger domainInteger1Minm8Max0( -8, 0 );"<<endl;
	cDomainInteger domainInteger1Minm8Max0( -8, 0 );
	cout<<"cDomainInteger domainInteger1Minm2Max8( 2, 8 );"<<endl;
	cDomainInteger domainInteger1Minm2Max8( 2, 8 );
	cout<<"cDomainInteger domainInteger1Min0Max8Scale0p02( 0, 8, 0.02 );"<<endl;
	cDomainInteger domainInteger1Min0Max8Scale0p02( 0, 8, 0.02 );
	cout<<"cDomainInteger domainInteger1Min0Max8Scale1p02( 0, 8, 1.02 );"<<endl;
	cDomainInteger domainInteger1Min0Max8Scale1p02( 0, 8, 1.02 );
	
	cout<<"cDomainNaturalNumber domainInteger1Max8( 0, 8 );"<<endl;
	cDomainNaturalNumber domainInteger1Max8( 0, 8 );
	
	cout<<"vector<cDomainSingle*> vElementdomains( 1 );"<<endl;
	vector<cDomainSingle*> vElementdomains( 1 );
	cout<<"vElementdomains[0] = &domainInteger1Max8;"<<endl;
	vElementdomains[0] = (&domainInteger1Max8);
	cout<<"cDomainVector domainVector( vElementdomains );"<<endl;
	cDomainVector domainVector( vElementdomains );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with domainInteger1Min0Max8
	cDomain *actualDomain=&domainInteger1Min0Max8;
	string szActualDomainName="domainInteger1Min0Max8";
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8, "domainInteger1Min0Max8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Min0Max8, "domainInteger2Min0Max8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min8Max0, "domainInteger1Min8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max9, "domainInteger1Min0Max9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm3Max8, "domainInteger1Minm3Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm8Max0, "domainInteger1Minm8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm2Max8, "domainInteger1Minm2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale0p02, "domainInteger1Min0Max8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale1p02, "domainInteger1Min0Max8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger2Min0Max8
	actualDomain=&domainInteger2Min0Max8;
	szActualDomainName="domainInteger2Min0Max8";
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8, "domainInteger1Min0Max8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Min0Max8, "domainInteger2Min0Max8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min8Max0, "domainInteger1Min8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max9, "domainInteger1Min0Max9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm3Max8, "domainInteger1Minm3Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm8Max0, "domainInteger1Minm8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm2Max8, "domainInteger1Minm2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale0p02, "domainInteger1Min0Max8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale1p02, "domainInteger1Min0Max8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Min8Max0
	actualDomain=&domainInteger1Min8Max0;
	szActualDomainName="domainInteger1Min8Max0";
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8, "domainInteger1Min0Max8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Min0Max8, "domainInteger2Min0Max8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min8Max0, "domainInteger1Min8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max9, "domainInteger1Min0Max9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm3Max8, "domainInteger1Minm3Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm8Max0, "domainInteger1Minm8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm2Max8, "domainInteger1Minm2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale0p02, "domainInteger1Min0Max8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale1p02, "domainInteger1Min0Max8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Min0Max9
	actualDomain=&domainInteger1Min0Max9;
	szActualDomainName="domainInteger1Min0Max9";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8, "domainInteger1Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Min0Max8, "domainInteger2Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min8Max0, "domainInteger1Min8Max0" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max9, "domainInteger1Min0Max9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm3Max8, "domainInteger1Minm3Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm8Max0, "domainInteger1Minm8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm2Max8, "domainInteger1Minm2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale0p02, "domainInteger1Min0Max8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale1p02, "domainInteger1Min0Max8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Minm3Max8
	actualDomain=&domainInteger1Minm3Max8;
	szActualDomainName="domainInteger1Minm3Max8";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8, "domainInteger1Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Min0Max8, "domainInteger2Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min8Max0, "domainInteger1Min8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max9, "domainInteger1Min0Max9" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm3Max8, "domainInteger1Minm3Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm8Max0, "domainInteger1Minm8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm2Max8, "domainInteger1Minm2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale0p02, "domainInteger1Min0Max8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale1p02, "domainInteger1Min0Max8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Minm8Max0
	actualDomain=&domainInteger1Minm8Max0;
	szActualDomainName="domainInteger1Minm8Max0";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8, "domainInteger1Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Min0Max8, "domainInteger2Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min8Max0, "domainInteger1Min8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max9, "domainInteger1Min0Max9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm3Max8, "domainInteger1Minm3Max8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm8Max0, "domainInteger1Minm8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm2Max8, "domainInteger1Minm2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale0p02, "domainInteger1Min0Max8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale1p02, "domainInteger1Min0Max8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Minm2Max8
	actualDomain=&domainInteger1Minm2Max8;
	szActualDomainName="domainInteger1Minm2Max8";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8, "domainInteger1Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Min0Max8, "domainInteger2Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min8Max0, "domainInteger1Min8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max9, "domainInteger1Min0Max9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm3Max8, "domainInteger1Minm3Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm8Max0, "domainInteger1Minm8Max0" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm2Max8, "domainInteger1Minm2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale0p02, "domainInteger1Min0Max8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale1p02, "domainInteger1Min0Max8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Min0Max8Scale0p02
	actualDomain=&domainInteger1Min0Max8Scale0p02;
	szActualDomainName="domainInteger1Min0Max8Scale0p02";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8, "domainInteger1Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Min0Max8, "domainInteger2Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min8Max0, "domainInteger1Min8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max9, "domainInteger1Min0Max9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm3Max8, "domainInteger1Minm3Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm8Max0, "domainInteger1Minm8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm2Max8, "domainInteger1Minm2Max8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale0p02, "domainInteger1Min0Max8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale1p02, "domainInteger1Min0Max8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Min0Max8Scale1p02
	actualDomain=&domainInteger1Min0Max8Scale1p02;
	szActualDomainName="domainInteger1Min0Max8Scale1p02";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8, "domainInteger1Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Min0Max8, "domainInteger2Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min8Max0, "domainInteger1Min8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max9, "domainInteger1Min0Max9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm3Max8, "domainInteger1Minm3Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm8Max0, "domainInteger1Minm8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm2Max8, "domainInteger1Minm2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale0p02, "domainInteger1Min0Max8Scale0p02" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale1p02, "domainInteger1Min0Max8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Max8
	actualDomain=&domainInteger1Max8;
	szActualDomainName="domainInteger1Max8";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8, "domainInteger1Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Min0Max8, "domainInteger2Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min8Max0, "domainInteger1Min8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max9, "domainInteger1Min0Max9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm3Max8, "domainInteger1Minm3Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm8Max0, "domainInteger1Minm8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm2Max8, "domainInteger1Minm2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale0p02, "domainInteger1Min0Max8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale1p02, "domainInteger1Min0Max8Scale1p02" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainVector
	actualDomain=&domainVector;
	szActualDomainName="domainVector";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8, "domainInteger1Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Min0Max8, "domainInteger2Min0Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min8Max0, "domainInteger1Min8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max9, "domainInteger1Min0Max9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm3Max8, "domainInteger1Minm3Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm8Max0, "domainInteger1Minm8Max0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Minm2Max8, "domainInteger1Minm2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale0p02, "domainInteger1Min0Max8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Min0Max8Scale1p02, "domainInteger1Min0Max8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
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

	cout<<"cDomainInteger domInteger1Min0Max8( 0, 8 );"<<endl;
	cDomainInteger domInteger1Min0Max8( 0, 8 );
	
	cout<<"cDomainInteger domInteger1Min0Max8Org( 0, 8 );"<<endl;
	cDomainInteger domInteger1Min0Max8Org( 0, 8 );
	
	cout<<"cDomainInteger domInteger1Min0Max8Copy( domInteger1Min0Max8 );"<<endl;
	cDomainInteger domInteger1Min0Max8Copy( domInteger1Min0Max8 );
	
	iReturn+=testCompareTwoEqualDomains( domInteger1Min0Max8Copy, "domInteger1Min0Max8Copy", domInteger1Min0Max8Org, "domInteger1Min0Max8Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger1Min0Max8, "domInteger1Min0Max8", domInteger1Min0Max8Org, "domInteger1Min0Max8Org" );

	cout<<"cDomainInteger * pDomainInteger1Min0Max8Clone = domInteger1Min0Max8Copy.clone();"<<endl;
	cDomainInteger * pDomainInteger1Min0Max8Clone = domInteger1Min0Max8Copy.clone();

	iReturn+=testCompareTwoEqualDomains( *pDomainInteger1Min0Max8Clone, "pDomainInteger1Min0Max8Clone", domInteger1Min0Max8Org, "domInteger1Min0Max8Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger1Min0Max8Copy, "domInteger1Min0Max8Copy", domInteger1Min0Max8Org, "domInteger1Min0Max8Org" );
	delete pDomainInteger1Min0Max8Clone;


	cout<<endl;
	cout<<"cDomainInteger domInteger1Minm5Max17( -5, 17 );"<<endl;
	cDomainInteger domInteger1Minm5Max17( -5, 17 );
	
	cout<<"cDomainInteger domInteger1Minm5Max17Org( -5, 17 );"<<endl;
	cDomainInteger domInteger1Minm5Max17Org( -5, 17 );

	cout<<"cDomainInteger domInteger1Minm5Max17Copy( domInteger1Minm5Max17 );"<<endl;
	cDomainInteger domInteger1Minm5Max17Copy( domInteger1Minm5Max17 );
	
	iReturn+=testCompareTwoEqualDomains( domInteger1Minm5Max17Copy, "domInteger1Minm5Max17Copy", domInteger1Minm5Max17Org, "domInteger1Minm5Max17Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger1Minm5Max17, "domInteger1Minm5Max17", domInteger1Minm5Max17Org, "domInteger1Minm5Max17Org" );

	cout<<"cDomainInteger * pDomInteger1Minm5Max17Clone = domInteger1Minm5Max17Copy.clone();"<<endl;
	cDomainInteger * pDomInteger1Minm5Max17Clone = domInteger1Minm5Max17Copy.clone();

	iReturn+=testCompareTwoEqualDomains( *pDomInteger1Minm5Max17Clone, "pDomInteger1Minm5Max17Clone", domInteger1Minm5Max17Org, "domInteger1Minm5Max17Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger1Minm5Max17, "domInteger1Minm5Max17", domInteger1Minm5Max17Org, "domInteger1Minm5Max17Org" );
	delete pDomInteger1Minm5Max17Clone;


	cout<<endl;
	cout<<"cDomainInteger domIntegerMinm10Maxm4( -10, -4 );"<<endl;
	cDomainInteger domIntegerMinm10Maxm4( -10, -4 );
	
	cout<<"cDomainInteger domIntegerMinm10Maxm4Org( -10, -4 );"<<endl;
	cDomainInteger domIntegerMinm10Maxm4Org( -10, -4 );

	cout<<"cDomainInteger domIntegerMinm10Maxm4Copy( domIntegerMinm10Maxm4 );"<<endl;
	cDomainInteger domIntegerMinm10Maxm4Copy( domIntegerMinm10Maxm4 );
	
	iReturn+=testCompareTwoEqualDomains( domIntegerMinm10Maxm4Copy, "domIntegerMinm10Maxm4Copy", domIntegerMinm10Maxm4Org, "domIntegerMinm10Maxm4Org" );
	iReturn+=testCompareTwoEqualDomains( domIntegerMinm10Maxm4, "domIntegerMinm10Maxm4", domIntegerMinm10Maxm4Org, "domIntegerMinm10Maxm4Org" );

	cout<<"cDomainInteger * pDomIntegerMinm10Maxm4Clone = domIntegerMinm10Maxm4Copy.clone();"<<endl;
	cDomainInteger * pDomIntegerMinm10Maxm4Clone = domIntegerMinm10Maxm4Copy.clone();

	iReturn+=testCompareTwoEqualDomains( *pDomIntegerMinm10Maxm4Clone, "pDomIntegerMinm10Maxm4Clone", domIntegerMinm10Maxm4Org, "domIntegerMinm10Maxm4Org" );
	iReturn+=testCompareTwoEqualDomains( domIntegerMinm10Maxm4, "domIntegerMinm10Maxm4", domIntegerMinm10Maxm4Org, "domIntegerMinm10Maxm4Org" );
	delete pDomIntegerMinm10Maxm4Clone;


	cout<<endl;
	cout<<"cDomainInteger domInteger1( 60, 1569, 0.02 );"<<endl;
	cDomainInteger domInteger1( 60, 1569, 0.02 );
	
	cout<<"cDomainInteger domInteger1Org( 60, 1569, 0.02 );"<<endl;
	cDomainInteger domInteger1Org( 60, 1569, 0.02 );

	cout<<"cDomainInteger domInteger1Copy( domInteger1 );"<<endl;
	cDomainInteger domInteger1Copy( domInteger1 );
	
	iReturn+=testCompareTwoEqualDomains( domInteger1Copy, "domInteger1Copy", domInteger1Org, "domInteger1Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger1, "domInteger1", domInteger1Org, "domInteger1Org" );

	cout<<"cDomainInteger * pDomInteger1Clone = domInteger1Copy.clone();"<<endl;
	cDomainInteger * pDomInteger1Clone = domInteger1Copy.clone();

	iReturn+=testCompareTwoEqualDomains( *pDomInteger1Clone, "pDomInteger1Clone", domInteger1Org, "domInteger1Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger1, "domInteger1", domInteger1Org, "domInteger1Org" );
	delete pDomInteger1Clone;


	cout<<endl;
	cout<<"cDomainInteger domInteger2( -4, 648, 236 );"<<endl;
	cDomainInteger domInteger2( -4, 648, 236 );
	
	cout<<"cDomainInteger domInteger2Org( -4, 648, 236 );"<<endl;
	cDomainInteger domInteger2Org( -4, 648, 236 );

	cout<<"cDomainInteger domInteger2Copy( domInteger2 );"<<endl;
	cDomainInteger domInteger2Copy( domInteger2 );
	
	iReturn+=testCompareTwoEqualDomains( domInteger2Copy, "domInteger2Copy", domInteger2Org, "domInteger2Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger2, "domInteger2", domInteger2Org, "domInteger2Org" );

	cout<<"cDomainInteger * pDomInteger2Clone = domInteger2Copy.clone();"<<endl;
	cDomainInteger * pDomInteger2Clone = domInteger2Copy.clone();

	iReturn+=testCompareTwoEqualDomains( *pDomInteger2Clone, "pDomInteger2Clone", domInteger2Org, "domInteger2Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger2, "domInteger2", domInteger2Org, "domInteger2Org" );
	delete pDomInteger2Clone;


	return iReturn;
}



/**
 * This method tests a in the xml -format stored cDomainInteger.
 *
 * @param szFilename the name of the file wher the cDomainInteger is stored
 * @param uiMin the minimal number the cDomainInteger has
 * @param uiMax the maximal number the cDomainInteger has
 * @param dScalingFactor the scalingfactor for the cDomainInteger domain
 * @return the number of errors occured in the test
 */
int testXmlDomain( const string szFilename, const unsigned int uiMin,
		const unsigned int uiMax, const double dScalingFactor ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored domain:"<<endl;
	
	TiXmlDocument xmlDocVectorPosition( szFilename );
	bool loadOkay = xmlDocVectorPosition.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\"."<<endl;
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

		if ( szElementName == "integer" ){
			cout<<"The root element is correctly named \"integer\"."<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"integer\"."<<endl;
			iReturn++;
		}
		
		int iMinLoaded = 0;
		const char * pcAttributMin = pXmlElement->Attribute( "min", &iMinLoaded );
		
		if ( pcAttributMin == NULL ){
			cerr<<"Error: The domain has no attribute min."<<endl;
			iReturn++;
		}else if ( iMinLoaded == (int)uiMin ) {
			cout<<"The number of minimum of the domain are correctly \""<< uiMin <<"\"."<<endl;
		}else{
			cerr<<"Error: The number of minimum of the loaded domain are \""<< iMinLoaded
				<<"\", but should be \""<< uiMin <<"\"."<<endl;
			iReturn++;
		}
		
		int iMaxLoaded = 0;
		const char * pcAttributMax = pXmlElement->Attribute( "max", &iMaxLoaded );
		
		if ( pcAttributMax == NULL ){
			cerr<<"Error: The domain has no attribute max."<<endl;
			iReturn++;
		}else if ( iMaxLoaded == (int)uiMax ) {
			cout<<"The number of maximum of the domain are correctly \""<< uiMax <<"\"."<<endl;
		}else{
			cerr<<"Error: The number of maximum of the loaded domain are \""<< iMaxLoaded
				<<"\", but should be \""<< uiMax <<"\"."<<endl;
			iReturn++;
		}

		const char * pcAttributeScalingFactor =
			pXmlElement->Attribute( "scalingfactor" );
		
		if ( ( dScalingFactor == 1.0 ) && ( pcAttributeScalingFactor == NULL ) ){
			//no scalingfactor needed
			cout<<"No scalingfactor attribut. This is correct because the scalingfactor is 1.0 ."<<endl;
		}else{
			if ( pcAttributeScalingFactor == NULL ){
				cerr<<"Error: The domain has no attribute scaling factor."<<endl;
				iReturn++;
			}else{
				const double dReadScalingFactor =
					readDoubleFromFunction( pcAttributeScalingFactor );
				
				if ( dScalingFactor == dReadScalingFactor ) {
					cout<<"The scaling factor of the domain is correctly \""<< pcAttributeScalingFactor <<"\"."<<endl;
				}else{
					cerr<<"Error: The scaling factor of the loaded domain is \""<<
						pcAttributeScalingFactor<<"\"(="<<dReadScalingFactor<<
						"), but should be \""<<dScalingFactor <<"\" ."<<endl;
					iReturn++;
				}
			}
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with minimum 0, maximal 4 and scaling factor 1 to Xml"<<endl;
	
	cout<<"cDomainInteger testDomainIntegerMin0Max4( 0, 4 );"<<endl;
	cDomainInteger testDomainIntegerMin0Max4( 0, 4 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerMin0Max4.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	bool bStoreSuccesfull = testDomainIntegerMin0Max4.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, 0, 4, 1 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with minimum -5, maximal 16 Max and scaling factor 0.214 to Xml"<<endl;
	
	cout<<"cDomainInteger domainIntegerMinm5Max16S0p214( -5, 16, 0.214 );"<<endl;
	cDomainInteger domainIntegerMinm5Max16S0p214( -5, 16, 0.214 );
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerMinm5Max16S0p214.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = domainIntegerMinm5Max16S0p214.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, -5, 16, 0.214 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with minimum 17, maximal 58 and scaling factor 64.125 to Xml"<<endl;
	
	cout<<"cDomainInteger domainIntegerMin17Max58S64p125( 17, 58, 64.125 );"<<endl;
	cDomainInteger domainIntegerMin17Max58S64p125( 17, 58, 64.125 );
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerMin17Max58S64p125.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = domainIntegerMin17Max58S64p125.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, 17, 58, 64.125 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with minimum -234, maximal -567 and scaling factor 0.125 to Xml"<<endl;
	
	cout<<"cDomainInteger domainIntegerMinm234Maxm567S0p125( -234, -567, 0.125 );"<<endl;
	cDomainInteger domainIntegerMinm234Maxm567S0p125( -234, -567, 0.125 );
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerMinm234Maxm567S0p125.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = domainIntegerMinm234Maxm567S0p125.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, -567, -234, 0.125 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with minimum 0, maximal 0 and scaling factor 0.01 to Xml"<<endl;
	
	cout<<"cDomainInteger domainIntegerMin0Max0S0p01( 0, 0, 0.01 );"<<endl;
	cDomainInteger domainIntegerMin0Max0S0p01( 0, 0, 0.01 );
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerMin0Max0S0p01.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = domainIntegerMin0Max0S0p01.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, 0, 0, 0.01 );


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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with a minumum 0, maximal 4 and scaling factor 1"<<endl;
	
	cout<<"cDomainInteger domainIntegerMin0Max4( 0, 4 );"<<endl;
	cDomainInteger domainIntegerMin0Max4( 0, 4 );

	//test get compressed size
	unsigned int uiCompressedSize = 8 + 2 * 64;
	if ( domainIntegerMin0Max4.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< uiCompressedSize <<" ."<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domainIntegerMin0Max4.getCompressedSize() << ", but should be "<< uiCompressedSize <<" ."<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerMin0Max4.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = domainIntegerMin0Max4.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<"."<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0."<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomainIntegerMin0Max4Byts[] = {(char)0x44, //type
		(char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, //min
		(char)0x04, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, //max
		(char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainIntegerMin0Max4Byts, uiCompressedSize / 8 + 1 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with a minimum 16, maximal 256 and scaling factor 0.214"<<endl;
	
	cout<<"cDomainInteger domainIntegerMin16Max256S0p214( 16, 256, 0.214 );"<<endl;
	cDomainInteger domainIntegerMin16Max256S0p214( 16, 256, 0.214 );
	
	//test get compressed size
	uiCompressedSize = 8 + 2 * 64 + 8 + 2 * 56;
	if ( domainIntegerMin16Max256S0p214.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< uiCompressedSize <<" ."<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domainIntegerMin16Max256S0p214.getCompressedSize() << ", but should be "<< uiCompressedSize <<" ."<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerMin16Max256S0p214.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = domainIntegerMin16Max256S0p214.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<"."<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0."<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomainIntegerMin16Max256S0p214[] = {(char)0x46, //domaintype
		(char)0x10, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, //min
		(char)0x00, (char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, //max
		(char)0x07, //scalingfactor
		(char)0x31, (char)0x08, (char)0xAC, (char)0x1C, (char)0x5A, (char)0x64, (char)0x1B,
		(char)0xC9, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF,
		(char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainIntegerMin16Max256S0p214, (uiCompressedSize + 7) / 8 + 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with a minimum -8, maximal 58 and scaling factor 64.125"<<endl;
	
	cout<<"cDomainInteger domainIntegerMinm8Max58S64p125( -8, 58, 64.125 );"<<endl;
	cDomainInteger domainIntegerMinm8Max58S64p125( -8, 58, 64.125 );
	
	//test get compressed size
	uiCompressedSize = 8 + 2 * 64 + 8 + 16 * 2;
	if ( domainIntegerMinm8Max58S64p125.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< uiCompressedSize <<" ."<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domainIntegerMinm8Max58S64p125.getCompressedSize() <<
			", but should be "<< uiCompressedSize <<" ."<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerMinm8Max58S64p125.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = domainIntegerMinm8Max58S64p125.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<"."<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0."<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomainIntegerMinm8Max58S64p125[] = {(char)0x46,
		(char)0xF8, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF,
		(char)0x3A, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
		(char)0x02,
		(char)0x01, (char)0x02, (char)0xFD, (char)0xFF, (char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainIntegerMinm8Max58S64p125, (uiCompressedSize + 7) / 8 + 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with the minimum 3, maximal 25 and scaling factor 64.125 and a 4 bit shift with restbit (char)0x05"<<endl;
	
	cout<<"cDomainInteger domainIntegerMin3Max58S64p125S4( 3, 25, 64.125 );"<<endl;
	cDomainInteger domainIntegerMin3Max58S64p125S4( 3, 25, 64.125 );
	
	//test get compressed size
	uiCompressedSize = 8 + 2 * 64 + 8 + 16 * 2;
	if ( domainIntegerMin3Max58S64p125S4.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< uiCompressedSize <<" ."<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domainIntegerMin3Max58S64p125S4.getCompressedSize() <<
			", but should be "<< uiCompressedSize <<" ."<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerMin3Max58S64p125S4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x05;
	cNumberOfRestBit = 4 ;
	bStoreSuccesfull = domainIntegerMin3Max58S64p125S4.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	unsigned char ucRestBit = (unsigned char)(cRestBit);
	if ( ( ucRestBit == (char)0x0F ) && ( cNumberOfRestBit == 4 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<"."<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x0F and number of restbit should be 4 ."<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomainIntegerMin3Max58S64p125S4[] = {(char)0x65,
		(char)0x34, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
		(char)0x90, (char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
		(char)0x20,
		(char)0x10, (char)0x20, (char)0xD0, (char)0xFF, (char)0x0F };
		
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainIntegerMin3Max58S64p125S4, (uiCompressedSize + cNumberOfRestBit) / 8 + 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with a minimum 1, maximal 1 and scaling factor 87 * 2^1 = 174"<<endl;
	
	cout<<"cDomainInteger domainIntegerMinm1Max1S174( 1, 1, 174 );"<<endl;
	cDomainInteger domainIntegerMinm1Max1S174( 1, 1, 174 );
	
	//test get compressed size
	uiCompressedSize = 8 + 2 * 64 + 8 + 8 * 2;
	if ( domainIntegerMinm1Max1S174.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< uiCompressedSize <<" ."<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domainIntegerMinm1Max1S174.getCompressedSize() <<
			", but should be "<< uiCompressedSize <<" ."<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerMinm8Max58S64p125.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = domainIntegerMinm1Max1S174.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<"."<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0."<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomainIntegerMinm1Max1S174[] = {(char)0x46,
		(char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
		(char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
		(char)0x01,
		(char)0x57, (char)0x01, (char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainIntegerMinm1Max1S174, (uiCompressedSize + 7) / 8 + 1 );


	return iReturn;
}



/**
 * This method store -value -method of the class.
 *
 * methods tested:
 * 	- unsignedIntFib getCompressedSizeForValue() const;
 * 	- bool storeValue( doubleFib dValue, ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 * 	- bool storeUnscaledValue( longFib lValue, ostream & stream, char & cRestBit, unsigned char & uiRestMaxPosition ) const;
 * 	- doubleFib restoreValue( cReadBits & iBitStream, intFib & outStatus ) const
 * 	- longFib restoreIntegerValue( cReadBits & iBitStream, intFib & outStatus )
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
		const long lMin = rand() % 1024 - 512;
		const long lMax = lMin + rand() % 1024;
		
		doubleFib dScaligFactor = 1.0;
		if ( ( rand() % 10 ) != 0 ){
			dScaligFactor = double(rand() % 1024) / 32.0;
		}
		
		cout<<"cDomainInteger domInteger( "<<lMin <<" ,"<< lMax <<", "<< dScaligFactor <<" );"<<endl;
		cDomainInteger domInteger( lMin, lMax, dScaligFactor );
		
		//test getCompressedSizeForValue()
		const unsigned long uiCompressedSizeForValue =
			getDigits( ((unsigned long long)(lMax - lMin)) );
		if ( domInteger.getCompressedSizeForValue() == uiCompressedSizeForValue ){
		
			cout<<"The compressed size of the domain is correctly "<<
				uiCompressedSizeForValue <<" ."<<endl;
		}else{
			cerr<<"Error: The compressed size of the domain is "<<
				domInteger.getCompressedSizeForValue() << ", but should be "<<
				uiCompressedSizeForValue <<" ."<<endl;
			iReturn++;
		}

		//for some random values, even some not in the domain
		for ( unsigned int iterationValue = 0; iterationValue < 64; iterationValue++ ){
			
			long lValue = 0;
			if ( rand() % 16 == 0 ){
				//mantissa outside domain
				cout<<"generating above maximum ("<<lMax<<")"<<endl;
				lValue = lMax + 1 + ( rand() % (lMax - lMin + 1) );
			}else if ( rand() % 16 == 0 ){
				//mantissa outside domain
				cout<<"generating below minimum ("<<lMin<<")"<<endl;
				lValue = lMin - 1 - ( rand() % (lMax - lMin + 1) );
			}else{
				lValue = ( rand() % (lMax - lMin + 1) ) + lMin;
			}
			const doubleFib dValue = (double)lValue * dScaligFactor;
			
			//store number (with restbit from 0 till 7)
			char szFileNameBuffer[128];
			szFileNameBuffer[0] = 0;
			strcat( strcat( szFileNameBuffer,
				(char*)DIR_OUTPUT ), "domIntegerValue.fib" );
			ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
			
			unsigned char cNumberOfRestBit = rand() % 8;
			const unsigned char cNumberOfRestBitOrg = cNumberOfRestBit;
			char cRestBit = rand() % 256;
			cRestBit = ((unsigned char)(cRestBit)) >> (8 - cNumberOfRestBit);
			const char cRestBitOrg = cRestBit;
			cout<<"domInteger.storeValue( "<< dValue <<", *pFile, (char)0x"<<
				hex<<(unsigned short)(cRestBit)<<dec <<", "<< (int)cNumberOfRestBit <<" );"<<endl;
			bool bStoreSuccesfull = domInteger.storeValue( dValue,
				*pFile, cRestBit, cNumberOfRestBit );
			(*pFile) << cRestBit;
			delete pFile;
			
			if ( bStoreSuccesfull ){
			
				cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
			}else{
				cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
				iReturn++;
			}
			
			unsigned char cNumberOfRestBitCorrect = (cNumberOfRestBitOrg + uiCompressedSizeForValue) % 8;
			if ( cNumberOfRestBit == cNumberOfRestBitCorrect ){
				cout<<"The number of restbit is "<< (unsigned short)cNumberOfRestBit <<"."<<endl;
			}else{
				cerr<<"Error: The number of restbit is "<< (unsigned short)cNumberOfRestBit <<
					", but the number of restbit should be "<< (unsigned short)cNumberOfRestBitCorrect <<" ."<<endl;
				iReturn++;
			}
			
			//restore number
			ifstream * fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
			char cRestBitLoaded = (char)0x00;
			cReadBits iBitStream( * fileInXml );
			unsigned int uiBitsLoaded = iBitStream.readBits( &cRestBitLoaded, cNumberOfRestBitOrg );
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
			const doubleFib dValueLoaded = domInteger.restoreValue( iBitStream, outStatus );
			delete fileInXml;
			
			if ( outStatus == 0 ){
			
				cout<<"The data was loaded successfull."<<endl;
			}else{
				cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
				iReturn++;
			}
			//check if restored number equals the rounded stored number
			const doubleFib dValueRouded = domInteger.round( dValue );
			
			if ( dValueLoaded == dValueRouded ){
				cout<<"The restored number is correctly "<< dValueLoaded <<" ."<<endl;

			}else{
				cerr<<"Error: The restored number is "<< dValueLoaded <<
					" , but should be "<< dValueRouded <<" ."<<endl;
				iReturn++;
			}
			
			//store integer number (with restbit from 0 till 7)
			szFileNameBuffer[0] = 0;
			strcat( strcat( szFileNameBuffer,
				(char*)DIR_OUTPUT ), "domIntegerValueUnscaled.fib" );
			pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
			
			cNumberOfRestBit = cNumberOfRestBitOrg;
			cRestBit = cRestBitOrg;
			cout<<"domInteger.storeUnscaledValue( "<< lValue <<", *pFile, (char)0x"<<
				hex<<(unsigned short)(cRestBit)<<dec <<", "<< (int)cNumberOfRestBit <<" );"<<endl;
			bStoreSuccesfull = domInteger.storeUnscaledValue( lValue,
				*pFile, cRestBit, cNumberOfRestBit );
			(*pFile) << cRestBit;
			delete pFile;
			
			if ( bStoreSuccesfull ){
			
				cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
			}else{
				cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
				iReturn++;
			}
			
			cNumberOfRestBitCorrect = (cNumberOfRestBitOrg + uiCompressedSizeForValue) % 8;
			if ( cNumberOfRestBit == cNumberOfRestBitCorrect ){
				cout<<"The number of restbit is "<< (unsigned short)cNumberOfRestBit <<"."<<endl;
			}else{
				cerr<<"Error: The number of restbit is "<< (unsigned short)cNumberOfRestBit <<
					", but the number of restbit should be "<< (unsigned short)cNumberOfRestBitCorrect <<" ."<<endl;
				iReturn++;
			}
			
			//restore number
			fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
			cRestBitLoaded = (char)0x00;
			cReadBits iBitStream1( * fileInXml );
			uiBitsLoaded = iBitStream1.readBits( &cRestBitLoaded, cNumberOfRestBitOrg );
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
			outStatus = 0;
			const long lValueLoaded = domInteger.restoreIntegerValue( iBitStream1, outStatus );
			delete fileInXml;
			
			if ( outStatus == 0 ){
			
				cout<<"The data was loaded successfull."<<endl;
			}else{
				cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
				iReturn++;
			}
			//check if restored number equals the rounded stored number
			const longFib lValueRouded = domInteger.roundUnscaled( lValue );
			
			if ( lValueLoaded == lValueRouded ){
				cout<<"The restored number is correctly "<< lValueLoaded <<" ."<<endl;

			}else{
				cerr<<"Error: The restored number is "<< lValueLoaded <<
					" , but should be "<< lValueRouded <<" ."<<endl;
				iReturn++;
			}
		}
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed restoring more bits than in file"<<endl;

	cout<<"cDomainInteger domIntegerB8( 0, 255 );"<<endl;
	cDomainInteger domIntegerB8( 0, 255 );

	//test getCompressedSizeForValue()
	const unsigned long uiCompressedSizeForValue = 8;
	if ( domIntegerB8.getCompressedSizeForValue() == uiCompressedSizeForValue ){
	
		cout<<"The compressed size of the domain is correctly "<<
			uiCompressedSizeForValue <<" ."<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domIntegerB8.getCompressedSizeForValue() << ", but should be "<<
			uiCompressedSizeForValue <<" ."<<endl;
		iReturn++;
	}

	const doubleFib dValue = 255;
	
	//store number (with restbit from 0 till 7)
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domIntegerB8Value.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	unsigned char cNumberOfRestBit = 0;
	char cRestBit = (char)0x00;
	cout<<"domIntegerB8.storeValue( "<< dValue <<", *pFile, (char)0x"<<
		hex<<(unsigned short)(cRestBit)<<dec <<", "<< (int)cNumberOfRestBit <<" );"<<endl;
	const bool bStoreSuccesfull = domIntegerB8.storeValue( dValue,
		*pFile, cRestBit, cNumberOfRestBit );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\"."<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( cNumberOfRestBit == 0 ){
		cout<<"The number of restbit is "<< (unsigned short)cNumberOfRestBit <<"."<<endl;
	}else{
		cerr<<"Error: The number of restbit is "<< (unsigned short)cNumberOfRestBit <<
			", but the number of restbit should be 0 ."<<endl;
		iReturn++;
	}
	
	cout<<"cDomainInteger domIntegerB16( 0, "<< 255 * 255 <<" );"<<endl;
	cDomainInteger domIntegerB16( 0, 255 * 255 );
	//restore number
	ifstream * fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
	cReadBits iBitStream( * fileInXml );
	intFib outStatus = 0;
	const doubleFib dValueLoaded = domIntegerB16.restoreValue( iBitStream, outStatus );
	delete fileInXml;
	
	if ( outStatus != 0 ){
	
		cout<<"The data was correctly not loaded. (outStatus="<< outStatus <<")."<<endl;
	}else{
		cerr<<"Error: The data was loaded."<<endl;
		iReturn++;
	}
	if ( dValueLoaded == 0.0 ){
		cout<<"The restored number is correctly "<< dValueLoaded <<" ."<<endl;

	}else{
		cerr<<"Error: The restored number is "<< dValueLoaded <<
			" , but should be "<< 0.0 <<" ."<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests the createGoodDomain() function of the
 * cDomainIntegerBasis class.
 *
 * functions tested:
 * 	- static cDomainIntegerBasis * cDomainIntegerBasis::
 * 		createGoodDomain( list< longFib > & liValues );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCreateGoodDomain( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the createGoodDomain() function of the cDomainIntegerBasis class on an empty list"<<endl;
	
	cout<<"list< longFib > liValues;"<<endl;
	list< longFib > liValues;
	
	cout<<"cDomainIntegerBasis * pDomainIntegerBasis = cDomainIntegerBasis::createGoodDomain( liValues );"<<endl;
	cDomainIntegerBasis * pDomainIntegerBasis =
		cDomainIntegerBasis::createGoodDomain( liValues );
	
	iReturn += testIntegerDomainLong( pDomainIntegerBasis, 0, 0, 1.0 );
	delete pDomainIntegerBasis;
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the createGoodDomain() function on an list with the numbers 1, 2 and 3"<<endl;
	
	cout<<"liValues.push_back( 1 );"<<endl;
	liValues.push_back( 1 );
	cout<<"liValues.push_back( 2 );"<<endl;
	liValues.push_back( 2 );
	cout<<"liValues.push_back( 3 );"<<endl;
	liValues.push_back( 3 );

	cout<<"pDomainIntegerBasis = cDomainIntegerBasis::createGoodDomain( liValues );"<<endl;
	pDomainIntegerBasis = cDomainIntegerBasis::createGoodDomain( liValues );
	
	iReturn += testIntegerDomainLong( pDomainIntegerBasis, 1, 3, 1.0 );
	delete pDomainIntegerBasis;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the createGoodDomain() function on random lists "<<endl;
	
	for ( unsigned int iteration = 1; iteration <= 64; iteration++ ){
		
		longFib lMinNumber = rand() % 65536 - 32768;
		longFib lMaxNumber = lMinNumber;
		
		list< longFib > liValues2;
		liValues2.push_back( lMinNumber );
		unsigned long ulNumberOfValues = (rand() % 256) * (rand() % 256) + 1;
		
		cout<<endl<<"Creating random list with "<< ulNumberOfValues <<" values."<<endl;
		cout<<"Values generated: "<<lMinNumber;
		
		for ( unsigned long ulActualNumber = 1;
				ulActualNumber < ulNumberOfValues; ulActualNumber++ ){
			
			const longFib lNumber = rand() % 65536 - 32768;
			liValues2.push_back( lNumber );
			
			if ( lNumber < lMinNumber ){
				lMinNumber = lNumber;
			}
			if ( lMaxNumber < lNumber ){
				lMaxNumber = lNumber;
			}
			cout<<";"<<lNumber;
		}
		cout<<endl;
		
		cout<<"pDomainIntegerBasis = cDomainIntegerBasis::createGoodDomain( liValues2 );"<<endl;
		pDomainIntegerBasis = cDomainIntegerBasis::createGoodDomain( liValues2 );
		
		iReturn += testIntegerDomainShort( pDomainIntegerBasis, lMinNumber, lMaxNumber, 1.0 );
		delete pDomainIntegerBasis;
	}

	return iReturn;
}
















