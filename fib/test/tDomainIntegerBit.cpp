/**
 * @file tDomainIntegerBit
 * file name: tDomainIntegerBit.cpp
 * @author Betti Oesterholz
 * @date 17.05.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for domains of the class cDomainIntegerBit.
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
 * This file contains the test for the class cDomainIntegerBit,
 * which represents a domain for natural numbers.
 *
 *
 *
 *  What's tested of class cDomainIntegerBit:
 * 	- cDomainIntegerBit( unsignedIntFib iBits );
 * 	- cDomainIntegerBit( unsignedIntFib iBits, doubleFib dScalingFactor );
 * 	- cDomainIntegerBit( const cDomainIntegerBit &domain );
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
 * 	- cDomainIntegerBit *clone() const;
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
 */
/*
History:
17.05.2010  Oesterholz  created
30.03.2011  Oesterholz  storing to binary stream
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/



#include "version.h"

#include "cDomainIntegerBasis.h"
#include "cDomainIntegerBit.h"
#include "cDomainNaturalNumber.h"
#include "cDomainVector.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <iomanip>
#include <vector>
#include <cmath>

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



int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cDomainIntegerBit methods"<<endl;
	cout<<      "=========================================="<<endl;

	iReturn += testConstructor( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
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
 * 	- cDomainIntegerBit( unsignedIntFib iBits );
 * 	- cDomainIntegerBit( unsignedIntFib iBits, doubleFib dScalingFactor );
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
 * 	- cDomainIntegerBit *clone() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testConstructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with 2 bits and scaling factor 1"<<endl;
	
	cout<<"testDomainIntegerBit1 = new cDomainIntegerBit( 2 );"<<endl;
	cDomainIntegerBit *testDomainIntegerBit1 = new cDomainIntegerBit( 2 );
	
	//check the getType() methode
	if ( testDomainIntegerBit1->getType() == "DomainIntegerBit" ){
	
		cout<<"The correct type \"DomainIntegerBit\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not \"DomainIntegerBit\" ; it is : "<<testDomainIntegerBit1->getType()<<endl;
		iReturn++;
	}
	
	iReturn += testIntegerDomainLong( testDomainIntegerBit1, -2, 1, 1.0 );
	delete testDomainIntegerBit1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with 8 bits and scaling factor 1"<<endl;
	
	cout<<"testDomainIntegerBit1 = new cDomainIntegerBit( 8 );"<<endl;
	testDomainIntegerBit1 = new cDomainIntegerBit( 8 );
	
	//check the getType() methode
	if ( testDomainIntegerBit1->getType() == "DomainIntegerBit" ){
	
		cout<<"The correct type \"DomainIntegerBit\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not \"cDomainIntegerBit\" ; it is : "<<testDomainIntegerBit1->getType()<<endl;
		iReturn++;
	}
	
	iReturn += testIntegerDomainLong( testDomainIntegerBit1, -128, 127, 1.0 );
	delete testDomainIntegerBit1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with 7 bits and scaling factor 1/16"<<endl;
	
	cout<<"testDomainIntegerBit1 = new cDomainIntegerBit( 7, 1.0/16.0 );"<<endl;
	testDomainIntegerBit1 = new cDomainIntegerBit( 7, 1.0/16.0 );
	
	//check the getType() methode
	if ( testDomainIntegerBit1->getType() == "DomainIntegerBit" ){
	
		cout<<"The correct type \"DomainIntegerBit\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not \"cDomainIntegerBit\" ; it is : "<<testDomainIntegerBit1->getType()<<endl;
		iReturn++;
	}
	iReturn += testIntegerDomainLong( testDomainIntegerBit1, -64, 63, 1.0/16.0 );
	delete testDomainIntegerBit1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with 13 bits and scaling factor 1/256"<<endl;
	
	cout<<"testDomainIntegerBit1 = new cDomainIntegerBit( 13, 1.0/256.0 );"<<endl;
	testDomainIntegerBit1 = new cDomainIntegerBit( 13, 1.0/256.0 );
	
	iReturn += testIntegerDomainShort( testDomainIntegerBit1, -4096, 4095, 1.0/256.0 );
	delete testDomainIntegerBit1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with 25 bits and scaling factor 1/19"<<endl;
	
	cout<<"testDomainIntegerBit1 = new cDomainIntegerBit( 25, 1.0/19.0 );"<<endl;
	testDomainIntegerBit1 = new cDomainIntegerBit( 25, 1.0/19.0 );
	
	iReturn += testIntegerDomainShort( testDomainIntegerBit1, -16777216, 16777215, 1.0/19.0 );
	delete testDomainIntegerBit1;

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple with 6 bits and scaling factor 123456789"<<endl;
	
	cout<<"testDomainIntegerBit1 = new cDomainIntegerBit( 6, 123456789.0 );"<<endl;
	testDomainIntegerBit1 = new cDomainIntegerBit( 6, 123456789.0 );
	
	iReturn += testIntegerDomainShort( testDomainIntegerBit1, -32, 31, 123456789.0 );
	delete testDomainIntegerBit1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple with 0 bits and scaling factor 0"<<endl;
	
	cout<<"testDomainIntegerBit1 = new cDomainIntegerBit( 0, 0.0 );"<<endl;
	testDomainIntegerBit1 = new cDomainIntegerBit( 0, 0.0 );
	
	iReturn += testIntegerDomainShort( testDomainIntegerBit1, 0, 0, 1.0 );
	delete testDomainIntegerBit1;


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

	//create cDomainIntegerBits to compare
	cout<<"cDomainIntegerBit domainInteger1Bit8( 8 );"<<endl;
	cDomainIntegerBit domainInteger1Bit8( 8 );
	cout<<"cDomainIntegerBit domainInteger2Bit8( 8 );"<<endl;
	cDomainIntegerBit domainInteger2Bit8( 8 );
	cout<<"cDomainIntegerBit domainInteger1Bit7( 7 );"<<endl;
	cDomainIntegerBit domainInteger1Bit7( 7 );
	cout<<"cDomainIntegerBit domainInteger1Bit9( 9 );"<<endl;
	cDomainIntegerBit domainInteger1Bit9( 9 );
	cout<<"cDomainIntegerBit domainInteger1Bit0( 0 );"<<endl;
	cDomainIntegerBit domainInteger1Bit0( 0 );
	cout<<"cDomainIntegerBit domainInteger1Bit31( 31 );"<<endl;
	cDomainIntegerBit domainInteger1Bit31( 31 );
	cout<<"cDomainIntegerBit domainInteger1Bit8S11( 8, 11 );"<<endl;
	cDomainIntegerBit domainInteger1Bit8S11( 8, 11 );
	cout<<"cDomainIntegerBit domainInteger1Bit8Scale0p02( 8, 0.02 );"<<endl;
	cDomainIntegerBit domainInteger1Bit8Scale0p02( 8, 0.02 );
	cout<<"cDomainIntegerBit domainInteger1Bit8Scale1p02( 8, 1.02 );"<<endl;
	cDomainIntegerBit domainInteger1Bit8Scale1p02( 8, 1.02 );
	
	cout<<"cDomainNaturalNumberBit domainNatural1Bit8( 8 );"<<endl;
	cDomainNaturalNumberBit domainNatural1Bit8( 8 );
	
	cout<<"vector<cDomainSingle*> vElementdomains( 1 );"<<endl;
	vector<cDomainSingle*> vElementdomains( 1 );
	cout<<"vElementdomains[0] = &domainNatural1Bit8;"<<endl;
	vElementdomains[0] = (&domainNatural1Bit8);
	cout<<"cDomainVector domainVector( vElementdomains );"<<endl;
	cDomainVector domainVector( vElementdomains );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with domainInteger1Bit8
	cDomain *actualDomain=&domainInteger1Bit8;
	string szActualDomainName="domainInteger1Bit8";
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit7, "domainInteger1Bit7" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit9, "domainInteger1Bit9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit0, "domainInteger1Bit0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit31, "domainInteger1Bit31" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8S11, "domainInteger1Bit8S11" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale0p02, "domainInteger1Bit8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale1p02, "domainInteger1Bit8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainNatural1Bit8, "domainNatural1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger2Bit8
	actualDomain=&domainInteger2Bit8;
	szActualDomainName="domainInteger2Bit8";
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit7, "domainInteger1Bit7" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit9, "domainInteger1Bit9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit0, "domainInteger1Bit0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit31, "domainInteger1Bit31" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8S11, "domainInteger1Bit8S11" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale0p02, "domainInteger1Bit8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale1p02, "domainInteger1Bit8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainNatural1Bit8, "domainNatural1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Bit7
	actualDomain=&domainInteger1Bit7;
	szActualDomainName="domainInteger1Bit7";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit7, "domainInteger1Bit7" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit9, "domainInteger1Bit9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit0, "domainInteger1Bit0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit31, "domainInteger1Bit31" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8S11, "domainInteger1Bit8S11" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale0p02, "domainInteger1Bit8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale1p02, "domainInteger1Bit8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainNatural1Bit8, "domainNatural1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Bit9
	actualDomain=&domainInteger1Bit9;
	szActualDomainName="domainInteger1Bit9";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit7, "domainInteger1Bit7" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit9, "domainInteger1Bit9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit0, "domainInteger1Bit0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit31, "domainInteger1Bit31" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8S11, "domainInteger1Bit8S11" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale0p02, "domainInteger1Bit8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale1p02, "domainInteger1Bit8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainNatural1Bit8, "domainNatural1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Bit0
	actualDomain=&domainInteger1Bit0;
	szActualDomainName="domainInteger1Bit0";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit7, "domainInteger1Bit7" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit9, "domainInteger1Bit9" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit0, "domainInteger1Bit0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit31, "domainInteger1Bit31" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8S11, "domainInteger1Bit8S11" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale0p02, "domainInteger1Bit8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale1p02, "domainInteger1Bit8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainNatural1Bit8, "domainNatural1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Bit31
	actualDomain=&domainInteger1Bit31;
	szActualDomainName="domainInteger1Bit31";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit7, "domainInteger1Bit7" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit9, "domainInteger1Bit9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit0, "domainInteger1Bit0" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit31, "domainInteger1Bit31" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8S11, "domainInteger1Bit8S11" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale0p02, "domainInteger1Bit8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale1p02, "domainInteger1Bit8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainNatural1Bit8, "domainNatural1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Bit8S11
	actualDomain=&domainInteger1Bit8S11;
	szActualDomainName="domainInteger1Bit8S11";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit7, "domainInteger1Bit7" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit9, "domainInteger1Bit9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit0, "domainInteger1Bit0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit31, "domainInteger1Bit31" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8S11, "domainInteger1Bit8S11" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale0p02, "domainInteger1Bit8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale1p02, "domainInteger1Bit8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainNatural1Bit8, "domainNatural1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Bit8Scale0p02
	actualDomain=&domainInteger1Bit8Scale0p02;
	szActualDomainName="domainInteger1Bit8Scale0p02";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit7, "domainInteger1Bit7" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit9, "domainInteger1Bit9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit0, "domainInteger1Bit0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit31, "domainInteger1Bit31" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8S11, "domainInteger1Bit8S11" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale0p02, "domainInteger1Bit8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale1p02, "domainInteger1Bit8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainNatural1Bit8, "domainNatural1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Bit8Scale1p02
	actualDomain=&domainInteger1Bit8Scale1p02;
	szActualDomainName="domainInteger1Bit8Scale1p02";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit7, "domainInteger1Bit7" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit9, "domainInteger1Bit9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit0, "domainInteger1Bit0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit31, "domainInteger1Bit31" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8S11, "domainInteger1Bit8S11" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale0p02, "domainInteger1Bit8Scale0p02" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale1p02, "domainInteger1Bit8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainNatural1Bit8, "domainNatural1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainNatural1Bit8
	actualDomain=&domainNatural1Bit8;
	szActualDomainName="domainNatural1Bit8";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit7, "domainInteger1Bit7" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit9, "domainInteger1Bit9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit0, "domainInteger1Bit0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit31, "domainInteger1Bit31" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8S11, "domainInteger1Bit8S11" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale0p02, "domainInteger1Bit8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale1p02, "domainInteger1Bit8Scale1p02" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainNatural1Bit8, "domainNatural1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainVector
	actualDomain=&domainVector;
	szActualDomainName="domainVector";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8, "domainInteger1Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit8, "domainInteger2Bit8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit7, "domainInteger1Bit7" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit9, "domainInteger1Bit9" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit0, "domainInteger1Bit0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit31, "domainInteger1Bit31" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8S11, "domainInteger1Bit8S11" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale0p02, "domainInteger1Bit8Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Bit8Scale1p02, "domainInteger1Bit8Scale1p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainNatural1Bit8, "domainNatural1Bit8" );
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

	cout<<"cDomainIntegerBit domInteger1Bit8( 8 );"<<endl;
	cDomainIntegerBit domInteger1Bit8( 8 );
	
	cout<<"cDomainIntegerBit domInteger1Bit8Org( 8 );"<<endl;
	cDomainIntegerBit domInteger1Bit8Org( 8 );
	
	cout<<"cDomainIntegerBit domInteger1Bit8Copy( domInteger1Bit8 );"<<endl;
	cDomainIntegerBit domInteger1Bit8Copy( domInteger1Bit8 );
	
	iReturn+=testCompareTwoEqualDomains( domInteger1Bit8Copy, "domInteger1Bit8Copy", domInteger1Bit8Org, "domInteger1Bit8Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger1Bit8, "domInteger1Bit8", domInteger1Bit8Org, "domInteger1Bit8Org" );

	cout<<"cDomainIntegerBit * pDomainIntegerBit1Bit8Clone = domInteger1Bit8Copy.clone();"<<endl;
	cDomainIntegerBit * pDomainIntegerBit1Bit8Clone = domInteger1Bit8Copy.clone();

	iReturn+=testCompareTwoEqualDomains( *pDomainIntegerBit1Bit8Clone, "pDomainIntegerBit1Bit8Clone", domInteger1Bit8Org, "domInteger1Bit8Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger1Bit8Copy, "domInteger1Bit8Copy", domInteger1Bit8Org, "domInteger1Bit8Org" );
	delete pDomainIntegerBit1Bit8Clone;


	cout<<endl;
	cout<<"cDomainIntegerBit domInteger1Bit17( 17 );"<<endl;
	cDomainIntegerBit domInteger1Bit17( 17 );
	
	cout<<"cDomainIntegerBit domInteger1Bit17Org( 17 );"<<endl;
	cDomainIntegerBit domInteger1Bit17Org( 17 );

	cout<<"cDomainIntegerBit domInteger1Bit17Copy( domInteger1Bit17 );"<<endl;
	cDomainIntegerBit domInteger1Bit17Copy( domInteger1Bit17 );
	
	iReturn+=testCompareTwoEqualDomains( domInteger1Bit17Copy, "domInteger1Bit17Copy", domInteger1Bit17Org, "domInteger1Bit17Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger1Bit17, "domInteger1Bit17", domInteger1Bit17Org, "domInteger1Bit17Org" );

	cout<<"cDomainIntegerBit * pDomInteger1Minm5Max17Clone = domInteger1Bit17Copy.clone();"<<endl;
	cDomainIntegerBit * pDomInteger1Minm5Max17Clone = domInteger1Bit17Copy.clone();

	iReturn+=testCompareTwoEqualDomains( *pDomInteger1Minm5Max17Clone, "pDomInteger1Minm5Max17Clone", domInteger1Bit17Org, "domInteger1Bit17Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger1Bit17, "domInteger1Bit17", domInteger1Bit17Org, "domInteger1Bit17Org" );
	delete pDomInteger1Minm5Max17Clone;


	cout<<endl;
	cout<<"cDomainIntegerBit domInteger1( 9, 0.02 );"<<endl;
	cDomainIntegerBit domInteger1( 9, 0.02 );
	
	cout<<"cDomainIntegerBit domInteger1Org( 9, 0.02 );"<<endl;
	cDomainIntegerBit domInteger1Org( 9, 0.02 );

	cout<<"cDomainIntegerBit domInteger1Copy( domInteger1 );"<<endl;
	cDomainIntegerBit domInteger1Copy( domInteger1 );
	
	iReturn+=testCompareTwoEqualDomains( domInteger1Copy, "domInteger1Copy", domInteger1Org, "domInteger1Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger1, "domInteger1", domInteger1Org, "domInteger1Org" );

	cout<<"cDomainIntegerBit * pDomInteger1Clone = domInteger1Copy.clone();"<<endl;
	cDomainIntegerBit * pDomInteger1Clone = domInteger1Copy.clone();

	iReturn+=testCompareTwoEqualDomains( *pDomInteger1Clone, "pDomInteger1Clone", domInteger1Org, "domInteger1Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger1, "domInteger1", domInteger1Org, "domInteger1Org" );
	delete pDomInteger1Clone;


	cout<<endl;
	cout<<"cDomainIntegerBit domInteger2( 13, 236 );"<<endl;
	cDomainIntegerBit domInteger2( 13, 236 );
	
	cout<<"cDomainIntegerBit domInteger2Org( 13, 236 );"<<endl;
	cDomainIntegerBit domInteger2Org( 13, 236 );

	cout<<"cDomainIntegerBit domInteger2Copy( domInteger2 );"<<endl;
	cDomainIntegerBit domInteger2Copy( domInteger2 );
	
	iReturn+=testCompareTwoEqualDomains( domInteger2Copy, "domInteger2Copy", domInteger2Org, "domInteger2Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger2, "domInteger2", domInteger2Org, "domInteger2Org" );

	cout<<"cDomainIntegerBit * pDomInteger2Clone = domInteger2Copy.clone();"<<endl;
	cDomainIntegerBit * pDomInteger2Clone = domInteger2Copy.clone();

	iReturn+=testCompareTwoEqualDomains( *pDomInteger2Clone, "pDomInteger2Clone", domInteger2Org, "domInteger2Org" );
	iReturn+=testCompareTwoEqualDomains( domInteger2, "domInteger2", domInteger2Org, "domInteger2Org" );
	delete pDomInteger2Clone;


	return iReturn;
}



/**
 * This method tests a in the xml -format stored cDomainIntegerBit.
 *
 * @param szFilename the name of the file wher the cDomainIntegerBit is stored
 * @param uiBits the number of bits the cDomainIntegerBit has
 * @param dScalingfactor the scalingfactor for the cDomainIntegerBit domain
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

		if ( szElementName == "integerB" ){
			cout<<"The root element is correctly named \"integerB\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"integerB\"."<<endl;
			iReturn++;
		}
		
		int iBitLoaded = 0;
		const char * pcAttributBit = pXmlElement->Attribute( "bit", &iBitLoaded );
		
		if ( pcAttributBit == NULL ){
			cerr<<"Error: The domain has no attribute bit."<<endl;
			iReturn++;
		}else if ( iBitLoaded == (int)uiBits ) {
			cout<<"The number of bits of the domain are correctly \""<< uiBits <<"\". "<<endl;
		}else{
			cerr<<"Error: The number of bits of the loaded domain are \""<< iBitLoaded
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with 4 bits and scaling factor 1 to Xml"<<endl;
	
	cout<<"cDomainIntegerBit domainIntegerBit4( 4 );"<<endl;
	cDomainIntegerBit domainIntegerBit4( 4 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerBit4.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	bool bStoreSuccesfull = domainIntegerBit4.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, 4, 1 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with 16 bits and scaling factor 0.214 to Xml"<<endl;
	
	cout<<"cDomainIntegerBit domainIntegerBit16S0p214( 16, 0.214 );"<<endl;
	cDomainIntegerBit domainIntegerBit16S0p214( 16, 0.214 );
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerBit16S0p214.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = domainIntegerBit16S0p214.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, 16, 0.214 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with 58 bits and scaling factor 64.125 to Xml"<<endl;
	
	cout<<"cDomainIntegerBit domainIntegerBit58S64p125( 58, 64.125 );"<<endl;
	cDomainIntegerBit domainIntegerBit58S64p125( 58, 64.125 );
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerBit58S64p125.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = domainIntegerBit58S64p125.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, 58, 64.125 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with 0 bits and scaling factor 0.01 to Xml"<<endl;
	
	cout<<"cDomainIntegerBit domainIntegerBits0S0p01( 0, 0.01 );"<<endl;
	cDomainIntegerBit domainIntegerBits0S0p01( 0, 0.01 );
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerBits0S0p01.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = domainIntegerBits0S0p01.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, 0, 0.01 );


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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with 4 bits and scaling factor 1"<<endl;
	
	cout<<"cDomainIntegerBit domainIntegerBit4( 4 );"<<endl;
	cDomainIntegerBit domainIntegerBit4( 4 );

	//test get compressed size
	unsigned int uiCompressedSize = 8 + 8;
	if ( domainIntegerBit4.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domainIntegerBit4.getCompressedSize() << ", but should be "<< uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerBit4.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = domainIntegerBit4.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cDomainIntegerBitMin0Max4Byts[] = {(char)0x40, //type
		(char)0x04, //bit
		(char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainIntegerBitMin0Max4Byts, 3 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with 16 bit and scaling factor 0.214"<<endl;
	
	cout<<"cDomainIntegerBit domainIntegerBit16S0p214( 16, 0.214 );"<<endl;
	cDomainIntegerBit domainIntegerBit16S0p214( 16, 0.214 );
	
	//test get compressed size
	uiCompressedSize = 16 + 8 + 2 * 56;
	if ( domainIntegerBit16S0p214.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domainIntegerBit16S0p214.getCompressedSize() << ", but should be "<< uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerBit16S0p214.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary  );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = domainIntegerBit16S0p214.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cDomainIntegerBitMin16Max256S0p214[] = {(char)0x42, //domaintype
		(char)0x10, //bit
		(char)0x07, //scalingfactor
		(char)0x31, (char)0x08, (char)0xAC, (char)0x1C, (char)0x5A, (char)0x64, (char)0x1B,
		(char)0xC9, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF,
		(char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainIntegerBitMin16Max256S0p214, (uiCompressedSize + 7) / 8 + 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with 58 bit and scaling factor 64.125"<<endl;
	
	cout<<"cDomainIntegerBit domainIntegerBit58S64p125( 58, 64.125 );"<<endl;
	cDomainIntegerBit domainIntegerBit58S64p125( 58, 64.125 );
	
	//test get compressed size
	uiCompressedSize = 16 + 8 + 16 * 2;
	if ( domainIntegerBit58S64p125.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domainIntegerBit58S64p125.getCompressedSize() <<
			", but should be "<< uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerBit58S64p125.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary  );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = domainIntegerBit58S64p125.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cDomainIntegerBitMinm8Max58S64p125[] = {(char)0x42,
		(char)0x3A, //bit
		(char)0x02,
		(char)0x01, (char)0x02, (char)0xFD, (char)0xFF, (char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainIntegerBitMinm8Max58S64p125, (uiCompressedSize + 7) / 8 + 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with 3 bit and scaling factor 64.125 and a 4 bit shift with restbit (char)0x05"<<endl;
	
	cout<<"cDomainIntegerBit domainIntegerBit3S64p125S4( 3, 64.125 );"<<endl;
	cDomainIntegerBit domainIntegerBit3S64p125S4( 3, 64.125 );
	
	//test get compressed size
	uiCompressedSize = 8 + 8 + 8 + 16 * 2;
	if ( domainIntegerBit3S64p125S4.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domainIntegerBit3S64p125S4.getCompressedSize() <<
			", but should be "<< uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerBit3S64p125S4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary  );
	
	cRestBit = (char)0x05;
	cNumberOfRestBit = 4 ;
	bStoreSuccesfull = domainIntegerBit3S64p125S4.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cDomainIntegerBitMin3Max58S64p125S4[] = {(char)0x25,
		(char)0x34,
		(char)0x20,
		(char)0x10, (char)0x20, (char)0xD0, (char)0xFF, (char)0x0F };
		
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainIntegerBitMin3Max58S64p125S4, (uiCompressedSize + cNumberOfRestBit) / 8 + 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with 0 bit and scaling factor 87 * 2^1 = 174"<<endl;
	
	cout<<"cDomainIntegerBit domainIntegerBit0S174( 0, 174 );"<<endl;
	cDomainIntegerBit domainIntegerBit0S174( 0, 174 );
	
	//test get compressed size
	uiCompressedSize = 16 + 8 + 8 * 2;
	if ( domainIntegerBit0S174.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domainIntegerBit0S174.getCompressedSize() <<
			", but should be "<< uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainIntegerBit0S174.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary  );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = domainIntegerBit0S174.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cDomainIntegerBit0S174[] = {(char)0x42,
		(char)0x00, //bit
		(char)0x01, (char)0x57, (char)0x01, (char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainIntegerBit0S174, (uiCompressedSize + 7) / 8 + 1 );

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
		const unsigned int uiBit = rand() % 32;
		long lMin = pow( 2, uiBit - 1 ) * -1;
		long lMax = pow( 2, uiBit - 1 ) - 1;
		if ( uiBit == 0 ){
			lMin = 0;
			lMax = 0;
		}
		
		doubleFib dScaligFactor = 1.0;
		if ( ( rand() % 10 ) != 0 ){
			dScaligFactor = double(rand() % 1024) / 32.0;
		}
		
		cout<<"cDomainIntegerBit domInteger( "<< uiBit <<", "<< dScaligFactor <<" );"<<endl;
		cDomainIntegerBit domInteger( uiBit, dScaligFactor );
		
		//test getCompressedSizeForValue()
		const unsigned long uiCompressedSizeForValue = uiBit;
		if ( domInteger.getCompressedSizeForValue() == uiCompressedSizeForValue ){
		
			cout<<"The compressed size of the domain is correctly "<<
				uiCompressedSizeForValue <<" . "<<endl;
		}else{
			cerr<<"Error: The compressed size of the domain is "<<
				domInteger.getCompressedSizeForValue() << ", but should be "<<
				uiCompressedSizeForValue <<" . "<<endl;
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
			
				cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
			}else{
				cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
				iReturn++;
			}
			
			unsigned char cNumberOfRestBitCorrect = (cNumberOfRestBitOrg + uiCompressedSizeForValue) % 8;
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
			
				cout<<"The data was loaded successfull. "<<endl;
			}else{
				cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
				iReturn++;
			}
			//check if restored number equals the rounded stored number
			const doubleFib dValueRouded = domInteger.round( dValue );
			
			if ( dValueLoaded == dValueRouded ){
				cout<<"The restored number is correctly "<< dValueLoaded <<" . "<<endl;

			}else{
				cerr<<"Error: The restored number is "<< dValueLoaded <<
					" , but should be "<< dValueRouded <<" . "<<endl;
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
			
				cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
			}else{
				cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
				iReturn++;
			}
			
			cNumberOfRestBitCorrect = (cNumberOfRestBitOrg + uiCompressedSizeForValue) % 8;
			if ( cNumberOfRestBit == cNumberOfRestBitCorrect ){
				cout<<"The number of restbit is "<< (unsigned short)cNumberOfRestBit <<". "<<endl;
			}else{
				cerr<<"Error: The number of restbit is "<< (unsigned short)cNumberOfRestBit <<
					", but the number of restbit should be "<< (unsigned short)cNumberOfRestBitCorrect <<" . "<<endl;
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
			
				cout<<"The data was loaded successfull. "<<endl;
			}else{
				cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
				iReturn++;
			}
			//check if restored number equals the rounded stored number
			const longFib lValueRouded = domInteger.roundUnscaled( lValue );
			
			if ( lValueLoaded == lValueRouded ){
				cout<<"The restored number is correctly "<< lValueLoaded <<" . "<<endl;

			}else{
				cerr<<"Error: The restored number is "<< lValueLoaded <<
					" , but should be "<< lValueRouded <<" . "<<endl;
				iReturn++;
			}
		}
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed restoring more bits than in file"<<endl;

	cout<<"cDomainIntegerBit domIntegerB8( 8 );"<<endl;
	cDomainIntegerBit domIntegerB8( 8 );

	//test getCompressedSizeForValue()
	const unsigned long uiCompressedSizeForValue = 8;
	if ( domIntegerB8.getCompressedSizeForValue() == uiCompressedSizeForValue ){
	
		cout<<"The compressed size of the domain is correctly "<<
			uiCompressedSizeForValue <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domIntegerB8.getCompressedSizeForValue() << ", but should be "<<
			uiCompressedSizeForValue <<" . "<<endl;
		iReturn++;
	}

	const doubleFib dValue = 127;
	
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
	
	cout<<"cDomainIntegerBit domIntegerB16( "<< 16 <<" );"<<endl;
	cDomainIntegerBit domIntegerB16( 16 );
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
		cout<<"The restored number is correctly "<< dValueLoaded <<" . "<<endl;

	}else{
		cerr<<"Error: The restored number is "<< dValueLoaded <<
			" , but should be "<< 0.0 <<" . "<<endl;
		iReturn++;
	}
	
	return iReturn;
}






















