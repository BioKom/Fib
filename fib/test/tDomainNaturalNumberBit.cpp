/**
 * @file tDomainNaturalNumberBit
 * file name: tDomainNaturalNumberBit.cpp
 * @author Betti Oesterholz
 * @date 13.05.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for domains of the class cDomainNaturalNumberBit.
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
 * This file contains the test for the class cDomainNaturalNumberBit,
 * which represents a domain for natural numbers.
 *
 *
 *
 *  What's tested of class cDomainNaturalNumberBit:
 * 	- cDomainNaturalNumberBit( unsignedIntFib iBits );
 * 	- cDomainNaturalNumberBit( unsignedIntFib iBits, doubleFib dScalingFactor );
 * 	- cDomainNaturalNumberBit( const cDomainNaturalNumberBit &domain );
 * 	- string getType() const;
 * 	- bool isElement( const doubleFib dValue ) const;
 * 	- doubleFib round( const doubleFib dValue ) const;
 * 	- doubleFib getMaximum( ) const ;
 * 	- doubleFib getMinimum() const
 * 	- doubleFib getNull( ) const;
 * 	- bool isUnscaledElement( const longFib lValue ) const;
 * 	- longFib roundUnscaled( const longFib lValue ) const;
 * 	- longFib getMaximumUnscaled( ) const;
 * 	- longFib getMinimumUnscaled( ) const;
 * 	- longFib getNullUnscaled( ) const;
 * 	- cDomainNaturalNumberBit *clone() const;
 * 	- operator==( const cDomain &domain ) const;
 * 	- equal( const cDomain &domain ) const;
 * 	- bool storeXml( ostringstream & ostream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 * 	- unsignedIntFib getCompressedSizeForValue() const;
 * 	- bool storeValue( doubleFib dValue, ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 * 	- bool storeUnscaledValue( longFib lValue, ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 */
/*
History:
13.05.2009  Oesterholz  created
11.10.2009  Oesterholz  tests for store -methods
13.05.2010  Oesterholz  the ordering of bits for the compressed storing corrected
30.03.2011  Oesterholz  storing to binary stream
23.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/



#include "version.h"

#include "cDomainIntegerBasis.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <iomanip>
#include <vector>

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
int testEqual( unsigned long &ulTestphase );
int testConstructor( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );
int testStoreValue( unsigned long &ulTestphase );


int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cDomainNaturalNumberBit methods"<<endl;
	cout<<      "================================================="<<endl;

	iReturn += testConstructor( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testStoreValue( ulTestphase );

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
 * 	- cDomainNaturalNumberBit( unsignedIntFib iBits );
 * 	- cDomainNaturalNumberBit( unsignedIntFib iBits, doubleFib dScalingFactor );
 * 	- cDomainNaturalNumberBit( const cDomainNaturalNumberBit &domain );
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
 * 	- cDomainNaturalNumberBit *clone() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testConstructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with 4 Bits and scaling factor 1"<<endl;
	
	cDomainNaturalNumberBit *testDomainNaturalNumber1 = new cDomainNaturalNumberBit( (unsignedIntFib)(4) );
	
	//check the getType() methode
	if ( testDomainNaturalNumber1->getType()=="DomainNaturalNumberBit" ){
	
		cout<<"The correct type \"DomainNaturalNumberBit\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not \"DomainNaturalNumberBit\" ; it is : "<<testDomainNaturalNumber1->getType()<<endl;
		iReturn++;
	}
	
	iReturn += testIntegerDomainLong( testDomainNaturalNumber1, 0, 15, 1.0 );
	delete testDomainNaturalNumber1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain 8 Bits and scaling factor 1"<<endl;
	
	testDomainNaturalNumber1 = new cDomainNaturalNumberBit( (unsignedIntFib)(8) );
	
	//check the getType() methode
	if ( testDomainNaturalNumber1->getType()=="DomainNaturalNumberBit" ){
	
		cout<<"The correct type \"DomainNaturalNumberBit\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not \"cDomainNaturalNumberBit\" ; it is : "<<testDomainNaturalNumber1->getType()<<endl;
		iReturn++;
	}
	
	iReturn += testIntegerDomainLong( testDomainNaturalNumber1, 0, 255, 1.0 );
	delete testDomainNaturalNumber1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain 8 Bits and scaling factor 1/16"<<endl;
	
	testDomainNaturalNumber1 = new cDomainNaturalNumberBit( (unsignedIntFib)(8), 1.0/16.0 );
		
	iReturn += testIntegerDomainLong( testDomainNaturalNumber1, 0, 255, 1.0/16.0 );
	delete testDomainNaturalNumber1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain 32 Bits and scaling factor 1/256"<<endl;
	
	testDomainNaturalNumber1 = new cDomainNaturalNumberBit( (unsignedIntFib)(32), 1.0/256.0 );
	
	iReturn += testIntegerDomainShort( testDomainNaturalNumber1, 0, 4294967295UL, 1.0/256.0 );
	delete testDomainNaturalNumber1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain 16 Bits and scaling factor 1/19"<<endl;
	
	testDomainNaturalNumber1 = new cDomainNaturalNumberBit( (unsignedIntFib)(16), 1.0/19.0 );
		
	iReturn += testIntegerDomainShort( testDomainNaturalNumber1, 0, 65535, 1.0/19.0 );
	delete testDomainNaturalNumber1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain 13 Bits and scaling factor 19"<<endl;
	
	testDomainNaturalNumber1 = new cDomainNaturalNumberBit( (unsignedIntFib)(13), 19.0 );
		
	iReturn += testIntegerDomainShort( testDomainNaturalNumber1, 0, 8191, 19.0 );
	delete testDomainNaturalNumber1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain 17 Bits and scaling factor 123456789"<<endl;
	
	testDomainNaturalNumber1 = new cDomainNaturalNumberBit( (unsignedIntFib)(17), 123456789.0 );
		
	iReturn += testIntegerDomainShort( testDomainNaturalNumber1, 0, 131071, 123456789.0 );


	//test the copy constructor
	cDomainNaturalNumberBit *testDomainNaturalNumberCopy1=
		new cDomainNaturalNumberBit( *testDomainNaturalNumber1 );
	
	iReturn += testIntegerDomainShort( testDomainNaturalNumberCopy1, 0, 131071, 123456789.0 );
	delete testDomainNaturalNumberCopy1;
	
	//test the clone function
	cDomainNaturalNumberBit * testDomainNaturalNumberClone1=
		testDomainNaturalNumber1->clone();
	
	iReturn += testIntegerDomainShort( testDomainNaturalNumberClone1, 0, 131071, 123456789.0 );
	delete testDomainNaturalNumberClone1;

	delete testDomainNaturalNumber1;

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
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	if ( domain1.equal( domain2 ) ){
	
		cout<<"The "<<szNameDomain1<<" is equal to "<<szNameDomain2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is not equal to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	if ( domain1==domain2 ){
	
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
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	if ( ! domain1.equal( domain2 ) ){
	
		cout<<"The "<<szNameDomain1<<" is not equal to "<<szNameDomain2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is equal to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	if ( ! (domain1==domain2) ){
	
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
 * This method tests the equal() method and the operator== of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testEqual( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equal method and the operator== "<<endl;

	//create cDomainNaturalNumberBits to compare
	cout<<"cDomainNaturalNumberBit domainInteger1Bit8( (unsignedIntFib)(8) );"<<endl;
	cDomainNaturalNumberBit domainInteger1Bit8( (unsignedIntFib)(8) );
	cout<<"cDomainNaturalNumberBit domainInteger2Bit8( (unsignedIntFib)(8) );"<<endl;
	cDomainNaturalNumberBit domainInteger2Bit8( (unsignedIntFib)(8) );
	cout<<"cDomainNaturalNumberBit domainInteger1Bit3( (unsignedIntFib)(3) );"<<endl;
	cDomainNaturalNumberBit domainInteger1Bit3( (unsignedIntFib)(3) );
	cout<<"cDomainNaturalNumberBit domainInteger2Bit3( (unsignedIntFib)(3) );"<<endl;
	cDomainNaturalNumberBit domainInteger2Bit3( (unsignedIntFib)(3) );
	cout<<"cDomainNaturalNumberBit domainInteger1Bit5( (unsignedIntFib)(5) );"<<endl;
	cDomainNaturalNumberBit domainInteger1Bit5( (unsignedIntFib)(5) );
	cout<<"cDomainNaturalNumberBit domainInteger2Bit5( (unsignedIntFib)(5) );"<<endl;
	cDomainNaturalNumberBit domainInteger2Bit5( (unsignedIntFib)(5) );
	cout<<"cDomainNaturalNumberBit domainInteger1Bit5Scale0p02( (unsignedIntFib)(5), 0.02 );"<<endl;
	cDomainNaturalNumberBit domainInteger1Bit5Scale0p02( (unsignedIntFib)(5), 0.02 );
	cout<<"cDomainNaturalNumberBit domainInteger2Bit5Scale0p02( (unsignedIntFib)(5), 0.02 );"<<endl;
	cDomainNaturalNumberBit domainInteger2Bit5Scale0p02( (unsignedIntFib)(5), 0.02 );
	
	
	cout<<"vector<cDomainSingle*> vElementdomains( 1 );"<<endl;
	vector<cDomainSingle*> vElementdomains( 1 );
	cout<<"vElementdomains[0]=&domainInteger2Bit5;"<<endl;
	vElementdomains[0]=(&domainInteger2Bit5);
	cout<<"cDomainVector domainVector( 1 );"<<endl;
	cDomainVector domainVector( vElementdomains );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with domainInteger1Bit8
	cDomain *actualDomain=&domainInteger1Bit8;
	string szActualDomainName="domainInteger1Bit8";
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit3, "domainInteger1Bit3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit3, "domainInteger2Bit3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5, "domainInteger1Bit5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5Scale0p02, "domainInteger1Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5Scale0p02, "domainInteger2Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger2Bit8
	actualDomain=&domainInteger2Bit8;
	szActualDomainName="domainInteger2Bit8";
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit3, "domainInteger1Bit3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit3, "domainInteger2Bit3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5, "domainInteger1Bit5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5Scale0p02, "domainInteger1Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5Scale0p02, "domainInteger2Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Bit3
	actualDomain=&domainInteger1Bit3;
	szActualDomainName="domainInteger1Bit3";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit3, "domainInteger1Bit3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit3, "domainInteger2Bit3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5, "domainInteger1Bit5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5Scale0p02, "domainInteger1Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5Scale0p02, "domainInteger2Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger2Bit3
	actualDomain=&domainInteger2Bit3;
	szActualDomainName="domainInteger2Bit3";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit3, "domainInteger1Bit3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit3, "domainInteger2Bit3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5, "domainInteger1Bit5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5Scale0p02, "domainInteger1Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5Scale0p02, "domainInteger2Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Bit5
	actualDomain=&domainInteger1Bit5;
	szActualDomainName="domainInteger1Bit5";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit3, "domainInteger1Bit3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit3, "domainInteger2Bit3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5, "domainInteger1Bit5" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5Scale0p02, "domainInteger1Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5Scale0p02, "domainInteger2Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger2Bit5
	actualDomain=&domainInteger2Bit5;
	szActualDomainName="domainInteger2Bit5";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit3, "domainInteger1Bit3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit3, "domainInteger2Bit3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5, "domainInteger1Bit5" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5Scale0p02, "domainInteger1Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5Scale0p02, "domainInteger2Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Bit5Scale0p02
	actualDomain=&domainInteger1Bit5Scale0p02;
	szActualDomainName="domainInteger1Bit5Scale0p02";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit3, "domainInteger1Bit3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit3, "domainInteger2Bit3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5, "domainInteger1Bit5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5Scale0p02, "domainInteger1Bit5Scale0p02" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5Scale0p02, "domainInteger2Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger2Bit5Scale0p02
	actualDomain=&domainInteger2Bit5Scale0p02;
	szActualDomainName="domainInteger2Bit5Scale0p02";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit3, "domainInteger1Bit3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit3, "domainInteger2Bit3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5, "domainInteger1Bit5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5Scale0p02, "domainInteger1Bit5Scale0p02" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5Scale0p02, "domainInteger2Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainVector
	actualDomain=&domainVector;
	szActualDomainName="domainVector";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit3, "domainInteger1Bit3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit3, "domainInteger2Bit3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5, "domainInteger1Bit5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit5Scale0p02, "domainInteger1Bit5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5Scale0p02, "domainInteger2Bit5Scale0p02" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	return iReturn;
}



/**
 * This method tests a in the xml -format stored cDomainNaturalNumberBit.
 *
 * @param szFilename the name of the file wher the cDomainNaturalNumberBit is stored
 * @param uiBits the bits the cDomainNaturalNumberBit has
 * @param dScalingfactor the scalingfactor for the cDomainNaturalNumberBit domain
 * @return the number of errors occured in the test
 */
int testXmlDomain( const string szFilename, const unsigned int uiBits,
		const double dScalingfactor ){
	
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

		if ( szElementName == "naturalNumberB" ){
			cout<<"The root element is correctly named \"naturalNumberB\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"naturalNumberB\"."<<endl;
			iReturn++;
		}
		
		int iBitsLoaded = 0;
		const char * pcAttributBits = pXmlElement->Attribute( "bit", &iBitsLoaded );
		
		if ( pcAttributBits == NULL ){
			cerr<<"Error: The domain has no attribute bits."<<endl;
			iReturn++;
		}else if ( iBitsLoaded == (int)uiBits ) {
			cout<<"The number of bits of the domain are correctly \""<< uiBits <<"\". "<<endl;
		}else{
			cerr<<"Error: The number of bits of the loaded domain are \""<< iBitsLoaded
				<<"\", but should be \""<< uiBits <<"\"."<<endl;
			iReturn++;
		}

		const char * pcAttributeScalingfactor =
			pXmlElement->Attribute( "scalingfactor" );
		
		longFib lfMantissa;
		longFib lfExponent;
		decomposeDoubleFib( dScalingfactor, & lfMantissa, & lfExponent );

		if ( ( dScalingfactor == 1.0 ) && ( pcAttributeScalingfactor == NULL ) ){
			//no scalingfactor needed
			cout<<"No scalingfactor attribut. This is correct because the scalingfactor is 1.0 . "<<endl;
		}else{
			if ( pcAttributeScalingfactor == NULL ){
				cerr<<"Error: The domain has no attribute scalingfactor."<<endl;
				iReturn++;
			}else{
				long long lMantissa = 0;
				long long lExponent = 0;
				// construct an istream containing a number
				stringstream sinScalingfactor( pcAttributeScalingfactor );

				// read the number -- the crucial bit
				char c = 0;
				sinScalingfactor >> lMantissa;
				while ( (c != '(') && sinScalingfactor ){
					sinScalingfactor >> c;
				}
				sinScalingfactor >> lExponent;

				if ( ( lfMantissa == lMantissa ) &&  ( lfExponent == lExponent ) ) {
					 cout<<"The scalingfactor of the domain is correctly \""<< pcAttributeScalingfactor <<"\". "<<endl;
				}else{
					 cerr<<"Error: The scalingfactor of the loaded domain is \""<< pcAttributeScalingfactor<<
						"\" (=\""<<lMantissa <<" * 2^("<< lExponent <<")\") "<<
						", but should be \""<< dScalingfactor <<"\" (=\""<<
						lfMantissa <<" * 2^("<< lfExponent <<")\")."<<endl;
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

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with 4 Bits and scaling factor 1 to Xml"<<endl;
	
	cout<<"cDomainNaturalNumberBit testDomainNaturalNumberB4( 4 );"<<endl;
	cDomainNaturalNumberBit testDomainNaturalNumberB4( 4 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberBitB4.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	bool bStoreSuccesfull = testDomainNaturalNumberB4.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, 4, 1 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with 16 Bits and scaling factor 0.214 to Xml"<<endl;
	
	cout<<"cDomainNaturalNumberBit testDomainNaturalNumberB16S0p214( 16, 0.214 );"<<endl;
	cDomainNaturalNumberBit testDomainNaturalNumberB16S0p214( 16, 0.214 );
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberB16S0p214.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = testDomainNaturalNumberB16S0p214.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, 16, 0.214 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with 58 Bits and scaling factor 64.125 to Xml"<<endl;
	
	cout<<"cDomainNaturalNumberBit testDomainNaturalNumberB58S64p125( 58, 64.125 );"<<endl;
	cDomainNaturalNumberBit testDomainNaturalNumberB58S64p125( 58, 64.125 );
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberB58S64p125.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = testDomainNaturalNumberB58S64p125.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, 58, 64.125 );

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with 4 Bits and scaling factor 1"<<endl;
	
	cout<<"cDomainNaturalNumberBit testDomainNaturalNumberB4( 4 );"<<endl;
	cDomainNaturalNumberBit testDomainNaturalNumberB4( 4 );

	//test get compressed size
	if ( testDomainNaturalNumberB4.getCompressedSize() == 16 ){
	
		cout<<"The compressed size of the domain is correctly 16 . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			testDomainNaturalNumberB4.getCompressedSize() << ", but should be 16 . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberBitB4.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = testDomainNaturalNumberB4.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cTestDomainNaturalNumberB4Byts[] = {(char)0x00, (char)0x04, (char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberB4Byts, 3 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with 16 Bits and scaling factor 0.214"<<endl;
	
	cout<<"cDomainNaturalNumberBit testDomainNaturalNumberB16S0p214( 16, 0.214 );"<<endl;
	cDomainNaturalNumberBit testDomainNaturalNumberB16S0p214( 16, 0.214 );
	
	//test get compressed size
	if ( testDomainNaturalNumberB16S0p214.getCompressedSize() == 8 + 8 + 8 + 2 * 56 ){
	
		cout<<"The compressed size of the domain is correctly 132 . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			testDomainNaturalNumberB16S0p214.getCompressedSize() << ", but should be 132 . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberB16S0p214.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = testDomainNaturalNumberB16S0p214.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cTestDomainNaturalNumberB16S0p214[] = {(char)0x02, (char)0x10, (char)0x07,
		(char)0x31, (char)0x08, (char)0xAC, (char)0x1C, (char)0x5A, (char)0x64, (char)0x1B,
		(char)0xC9, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberB16S0p214, 18 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with 58 Bits and scaling factor 64.125"<<endl;
	
	cout<<"cDomainNaturalNumberBit testDomainNaturalNumberB58S64p125( 58, 64.125 );"<<endl;
	cDomainNaturalNumberBit testDomainNaturalNumberB58S64p125( 58, 64.125 );
	
	//test get compressed size
	unsigned int compressedSize = 16 + 8 + 16 * 2;
	if ( testDomainNaturalNumberB58S64p125.getCompressedSize() == compressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< compressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			testDomainNaturalNumberB58S64p125.getCompressedSize() <<
			", but should be "<< compressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberB58S64p125.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = testDomainNaturalNumberB58S64p125.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cTestDomainNaturalNumberB58S64p125[] = {(char)0x02, (char)0x3A, (char)0x02,
		(char)0x01, (char)0x02, (char)0xFD, (char)0xFF, (char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberB58S64p125, 8 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with 25 Bits and scaling factor 64.125 and a 4 Bit shift with restbit (char)0x05"<<endl;
	
	cout<<"cDomainNaturalNumberBit testDomainNaturalNumberB58S64p125S4( 25, 64.125 );"<<endl;
	cDomainNaturalNumberBit testDomainNaturalNumberB58S64p125S4( 25, 64.125 );
	
	//test get compressed size
	compressedSize = 16 + 8 + 16 * 2;
	if ( testDomainNaturalNumberB58S64p125S4.getCompressedSize() == compressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< compressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			testDomainNaturalNumberB58S64p125S4.getCompressedSize() <<
			", but should be "<< compressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberB58S64p125S4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x05;
	cNumberOfRestBit = 4 ;
	bStoreSuccesfull = testDomainNaturalNumberB58S64p125S4.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	unsigned char ucRestBit = (unsigned char)(cRestBit);
	if ( ( ucRestBit == (char)0x0F ) && ( cNumberOfRestBit == 4 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x0F and number of restbit should be 4 . "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTestDomainNaturalNumberB58S64p125S4[] = {(char)0x25, (char)0x90, (char)0x21,
		(char)0x10, (char)0x20, (char)0xD0, (char)0xFF, (char)0x0F};
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberB58S64p125S4, 8 );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with 25 Bits and scaling factor 64.125 and a 3 Bit shift with restbit (char)0x04"<<endl;
	
	cout<<"cDomainNaturalNumberBit testDomainNaturalNumberB58S64p125S3( 25, 64.125 );"<<endl;
	cDomainNaturalNumberBit testDomainNaturalNumberB58S64p125S3( 25, 64.125 );
	
	//test get compressed size
	compressedSize = 16 + 8 + 16 * 2;
	if ( testDomainNaturalNumberB58S64p125S3.getCompressedSize() == compressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< compressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			testDomainNaturalNumberB58S64p125S3.getCompressedSize() <<
			", but should be "<< compressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberB58S64p125S3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x04;
	cNumberOfRestBit = 3 ;
	bStoreSuccesfull = testDomainNaturalNumberB58S64p125S4.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = (unsigned char)(cRestBit);
	if ( ( ucRestBit == (char)0x07 ) && ( cNumberOfRestBit == 3 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x07 and number of restbit should be 3 . "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTestDomainNaturalNumberB58S64p125S3[] = {(char)0x14, (char)0xC8, (char)0x10, (char)0x08, (char)0x10, (char)0xE8, (char)0xFF, (char)0x07};
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberB58S64p125S3, 8 );

	return iReturn;
}



/**
 * This method store -value -method of the class.
 *
 * methods tested:
 * 	- unsignedIntFib getCompressedSizeForValue() const;
 * 	- bool storeValue( doubleFib dValue, ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 * 	- bool storeUnscaledValue( longFib lValue, ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStoreValue( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 423.0 in a Domain with 13 Bits and scaling factor 1"<<endl;
	
	unsigned int uiBitsOfDomain = 13;
	cout<<"cDomainNaturalNumberBit testDomainNaturalNumberB13( uiBitsOfDomain );"<<endl;
	cDomainNaturalNumberBit testDomainNaturalNumberB13( uiBitsOfDomain );

	//test get compressed size
	if ( testDomainNaturalNumberB13.getCompressedSizeForValue() == uiBitsOfDomain ){
	
		cout<<"The compressed size for a domainvalue is correctly "<<
			uiBitsOfDomain <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size for a domainvalue is "<<
			testDomainNaturalNumberB13.getCompressedSizeForValue() <<
			", but should be "<< uiBitsOfDomain <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberBitB13V423.fib" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	double dValueToStore = 423.0;
	bool bStoreSuccesfull = testDomainNaturalNumberB13.storeValue(
		dValueToStore, *fileXml, cRestBit, cNumberOfRestBit );
	(*fileXml) << cRestBit;
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	unsigned char ucRestBit = (unsigned char)cRestBit;
	if ( ( ucRestBit == (char)0x01 ) && ( cNumberOfRestBit == 5 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x01 and number of restbit should be 5 . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cTestDomainNaturalNumberB13V423[] = {(char)0xA7, (char)0x01};//dValueToStore = 01A7
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberB13V423, 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 423 in a Domain with 13 Bits and scaling factor 1"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberBitB13Vu423.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	long lValueToStore = 423;
	bStoreSuccesfull = testDomainNaturalNumberB13.storeUnscaledValue(
		lValueToStore, *fileXml, cRestBit, cNumberOfRestBit );
	(*fileXml) << cRestBit;
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = (unsigned char)cRestBit;
	if ( ( ucRestBit == (char)0x01 ) && ( cNumberOfRestBit == 5 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x01 and number of restbit should be 5 . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cTestDomainNaturalNumberB13Vu423[] = {(char)0xA7, (char)0x01};//dValueToStore = 01A7
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberB13Vu423, 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 423.4 in a Domain with 13 Bits and scaling factor 1"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberBitB13V423p4.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	dValueToStore = 423.4;
	bStoreSuccesfull = testDomainNaturalNumberB13.storeValue(
		dValueToStore, *fileXml, cRestBit, cNumberOfRestBit );
	(*fileXml) << cRestBit;
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = (unsigned char)cRestBit;
	if ( ( ucRestBit == (char)0x01 ) && ( cNumberOfRestBit == 5 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x01 and number of restbit should be 5 . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cTestDomainNaturalNumberB13V423p4[] = {(char)0xA7, (char)0x01};//dValueToStore = 01A7
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberB13V423p4, 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 422.51 in a Domain with 13 Bits and scaling factor 1"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberBitB13V422p51.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	dValueToStore = 422.51;
	bStoreSuccesfull = testDomainNaturalNumberB13.storeValue(
		dValueToStore, *fileXml, cRestBit, cNumberOfRestBit );
	(*fileXml) << cRestBit;
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = (unsigned char)cRestBit;
	if ( ( ucRestBit == (char)0x01 ) && ( cNumberOfRestBit == 5 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x01 and number of restbit should be 5 . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cTestDomainNaturalNumberB13V422p5[] = {(char)0xA7, (char)0x01};//dValueToStore = 01A7
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberB13V422p5, 2 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number -22.5 in a Domain with 13 Bits and scaling factor 1"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberBitB13Vm22p5.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	dValueToStore = -22.5;
	bStoreSuccesfull = testDomainNaturalNumberB13.storeValue(
		dValueToStore, *fileXml, cRestBit, cNumberOfRestBit );
	(*fileXml) << cRestBit;
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = (unsigned char)cRestBit;
	if ( ( ucRestBit == (char)0x00 ) && ( cNumberOfRestBit == 5 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x00 and number of restbit should be 5 . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cTestDomainNaturalNumberB13Vm22p5[] = {(char)0x00, (char)0x00};//dValueToStore = 0
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberB13Vm22p5, 2 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 10000.0 in a Domain with 13 Bits and scaling factor 1"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberBitB13V10000.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	dValueToStore = 10000.0;
	bStoreSuccesfull = testDomainNaturalNumberB13.storeValue(
		dValueToStore, *fileXml, cRestBit, cNumberOfRestBit );
	(*fileXml) << cRestBit;
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = (unsigned char)cRestBit;
	if ( ( ucRestBit == (char)0x1F ) && ( cNumberOfRestBit == 5 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x1F and number of restbit should be 5 . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cTestDomainNaturalNumberB13V10000[] = {(char)0xFF, (char)0x1F};//dValueToStore = 0
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberB13V10000, 2 );



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 614 in a Domain with 12 Bits and scaling factor 1.25"<<endl;
	
	uiBitsOfDomain = 12;
	cout<<"cDomainNaturalNumberBit testDomainNaturalNumberB12S1p25( uiBitsOfDomain, 1.25 );"<<endl;
	cDomainNaturalNumberBit testDomainNaturalNumberB12S1p25( uiBitsOfDomain, 1.25 );

	//test get compressed size
	if ( testDomainNaturalNumberB12S1p25.getCompressedSizeForValue() == uiBitsOfDomain ){
	
		cout<<"The compressed size for a domainvalue is correctly "<<
			uiBitsOfDomain <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size for a domainvalue is "<<
			testDomainNaturalNumberB12S1p25.getCompressedSizeForValue() <<
			", but should be "<< uiBitsOfDomain <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberBitB12S1p25V614.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	lValueToStore = 614;
	bStoreSuccesfull = testDomainNaturalNumberB12S1p25.storeUnscaledValue(
		lValueToStore, *fileXml, cRestBit, cNumberOfRestBit );
	(*fileXml) << cRestBit;
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = (unsigned char)cRestBit;
	if ( ( ucRestBit == (char)0x02 ) && ( cNumberOfRestBit == 4 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x02 and number of restbit should be 4 . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cDomainNaturalNumberBitB12S1p25V614[] = {(char)0x66, (char)0x02};//dValueToStore = (char)0x266
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainNaturalNumberBitB12S1p25V614, 2 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 767.5 in a Domain with 12 Bits and scaling factor 1.25"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberBitB12S1p25V767p5.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	dValueToStore = 767.5;
	bStoreSuccesfull = testDomainNaturalNumberB12S1p25.storeValue(
		dValueToStore, *fileXml, cRestBit, cNumberOfRestBit );
	(*fileXml) << cRestBit;
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = (unsigned char)cRestBit;
	if ( ( ucRestBit == (char)0x02 ) && ( cNumberOfRestBit == 4 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x02 and number of restbit should be 4 . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cDomainNaturalNumberBitB12S1p25V767p5[] = {(char)0x66, (char)0x02};//dValueToStore = (char)0x266
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainNaturalNumberBitB12S1p25V767p5, 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 3906.3 and 3716.20 in a Domain with 12 Bits and scaling factor 1.25"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberBitB12S1p25V3906p3V3716p20.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	dValueToStore = 3906.3;
	bStoreSuccesfull = testDomainNaturalNumberB12S1p25.storeValue(
		dValueToStore, *fileXml, cRestBit, cNumberOfRestBit );
	(*fileXml) << flush;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = (unsigned char)cRestBit;
	if ( ( ucRestBit == (char)0x0C ) && ( cNumberOfRestBit == 4 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x0C and number of restbit should be 4 . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cDomainNaturalNumberBitB12S1p25V3906p3[] = {(char)0x35};//dValueToStore = (char)0xC35
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainNaturalNumberBitB12S1p25V3906p3, 1 );


	dValueToStore = 3716.20;
	bStoreSuccesfull = testDomainNaturalNumberB12S1p25.storeValue(
		dValueToStore, *fileXml, cRestBit, cNumberOfRestBit );
	(*fileXml) << cRestBit;
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = (unsigned char)cRestBit;
	if ( ( ucRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x00 and number of restbit should be 0 . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cDomainNaturalNumberBitB12S1p25V3906p3V3716p20[] = {(char)0x35, (char)0xDC, (char)0xB9, (char)0x00};//dValueToStore = (char)0xB9D
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainNaturalNumberBitB12S1p25V3906p3V3716p20, 4 );


	return iReturn;
}
























