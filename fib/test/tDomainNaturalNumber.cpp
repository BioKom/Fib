/**
 * @file tDomainNaturalNumber
 * file name: tDomainNaturalNumber.cpp
 * @author Betti Oesterholz
 * @date 01.01.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for domains of the class cDomainNaturalNumber.
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
 * This file contains the test for the class cDomainNaturalNumber,
 * which represents a domain for natural numbers.
 *
 *
 *
 *  What's tested of class cDomainNaturalNumber:
 * 	- cDomainNaturalNumber( unsignedLongFib ulMaxNumber );
 * 	- cDomainNaturalNumber( unsignedLongFib ulMaxNumber, doubleFib dScalingFactor );
 * 	- cDomainNaturalNumber( const cDomainNaturalNumber &domain );
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
 * 	- cDomainNaturalNumber *clone() const;
 * 	- operator==( const cDomain &domain ) const;
 * 	- equal( const cDomain &domain ) const;
 * 	- bool storeXml( ostringstream & ostream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream & stream, char & cRestBit, unsigned char & uiRestMaxPosition ) const;
 * 	- unsignedIntFib getCompressedSizeForValue() const;
 * 	- bool storeValue( doubleFib dValue, ostream & stream, char & cRestBit, unsigned char & uiRestMaxPosition ) const;
 * 	- bool storeUnscaledValue( longFib lValue, ostream & stream, char & cRestBit, unsigned char & uiRestMaxPosition ) const;
 */
/*
History:
01.01.2010  Oesterholz  created
13.05.2010  Oesterholz  the ordering of bits for the compressed storing corrected
30.03.2011  Oesterholz  storing to binary stream
23.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/



#include "version.h"

#include "cDomainIntegerBasis.h"
#include "cDomainNaturalNumber.h"
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
	
	cout<<endl<<"Running Test for cDomainNaturalNumber methods"<<endl;
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
 * 	- cDomainNaturalNumber( unsignedLongFib ulMaxNumber );
 * 	- cDomainNaturalNumber( unsignedLongFib ulMaxNumber, doubleFib dScalingFactor );
 * 	- cDomainNaturalNumber( const cDomainNaturalNumber &domain );
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
 * 	- cDomainNaturalNumber *clone() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testConstructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with maximal number 4 and scaling factor 1"<<endl;
	
	cDomainNaturalNumber *testDomainNaturalNumber1 = new cDomainNaturalNumber( (unsignedIntFib)(4) );
	
	//check the getType() methode
	if ( testDomainNaturalNumber1->getType() == "DomainNaturalNumber" ){
	
		cout<<"The correct type \"DomainNaturalNumber\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not \"DomainNaturalNumber\" ; it is : "<<testDomainNaturalNumber1->getType()<<endl;
		iReturn++;
	}
	
	iReturn += testIntegerDomainLong( testDomainNaturalNumber1, 0, 4, 1.0 );
	delete testDomainNaturalNumber1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with maximal number 13 and scaling factor 1"<<endl;
	
	testDomainNaturalNumber1 = new cDomainNaturalNumber( 13 );
	
	//check the getType() methode
	if ( testDomainNaturalNumber1->getType() == "DomainNaturalNumber" ){
	
		cout<<"The correct type \"DomainNaturalNumber\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not \"cDomainNaturalNumber\" ; it is : "<<testDomainNaturalNumber1->getType()<<endl;
		iReturn++;
	}
	
	iReturn += testIntegerDomainLong( testDomainNaturalNumber1, 0, 13, 1.0 );
	delete testDomainNaturalNumber1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with maximal number 126 and scaling factor 1/16"<<endl;
	
	testDomainNaturalNumber1 = new cDomainNaturalNumber( 126, 1.0/16.0 );
		
	iReturn += testIntegerDomainLong( testDomainNaturalNumber1, 0, 126, 1.0/16.0 );
	delete testDomainNaturalNumber1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with maximal number 81384 and scaling factor 1/256"<<endl;
	
	testDomainNaturalNumber1 = new cDomainNaturalNumber( 81384, 1.0/256.0 );
		
	iReturn += testIntegerDomainShort( testDomainNaturalNumber1, 0, 81384, 1.0/256.0 );
	delete testDomainNaturalNumber1;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with maximal number 813 and scaling factor 1/19"<<endl;
	
	testDomainNaturalNumber1 = new cDomainNaturalNumber( 813, 1.0/19.0 );
		
	iReturn += testIntegerDomainShort( testDomainNaturalNumber1, 0, 813, 1.0/19.0 );
	delete testDomainNaturalNumber1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with maximal number 256 and scaling factor 19"<<endl;
	
	testDomainNaturalNumber1 = new cDomainNaturalNumber( 256, 19.0 );
		
	iReturn += testIntegerDomainShort( testDomainNaturalNumber1, 0, 256, 19.0 );
	delete testDomainNaturalNumber1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple domain with maximal number 0 and scaling factor 19"<<endl;
	
	testDomainNaturalNumber1 = new cDomainNaturalNumber( 0, 19.0 );
		
	iReturn += testIntegerDomainShort( testDomainNaturalNumber1, 0, 0, 19.0 );
	delete testDomainNaturalNumber1;

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a simple with maximal number 48 and scaling factor 123456789"<<endl;
	
	testDomainNaturalNumber1 = new cDomainNaturalNumber( 48, 123456789.0 );
		
	iReturn += testIntegerDomainShort( testDomainNaturalNumber1, 0, 48, 123456789.0 );


	//test the copy constructor
	cDomainNaturalNumber *testDomainNaturalNumberCopy1=
		new cDomainNaturalNumber( *testDomainNaturalNumber1 );
	
	iReturn += testIntegerDomainShort( testDomainNaturalNumberCopy1, 0, 48, 123456789.0 );
	delete testDomainNaturalNumberCopy1;
	
	//test the clone function
	cDomainNaturalNumber * testDomainNaturalNumberClone1=
		testDomainNaturalNumber1->clone();
	
	iReturn += testIntegerDomainShort( testDomainNaturalNumberClone1, 0, 48, 123456789.0 );
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

	//create cDomainNaturalNumbers to compare
	cout<<"cDomainNaturalNumber domainInteger1Max8( (unsignedIntFib)(8) );"<<endl;
	cDomainNaturalNumber domainInteger1Max8( (unsignedIntFib)(8) );
	cout<<"cDomainNaturalNumber domainInteger2Max8( (unsignedIntFib)(8) );"<<endl;
	cDomainNaturalNumber domainInteger2Max8( (unsignedIntFib)(8) );
	cout<<"cDomainNaturalNumber domainInteger1Max3( (unsignedIntFib)(3) );"<<endl;
	cDomainNaturalNumber domainInteger1Max3( (unsignedIntFib)(3) );
	cout<<"cDomainNaturalNumber domainInteger2Max3( (unsignedIntFib)(3) );"<<endl;
	cDomainNaturalNumber domainInteger2Max3( (unsignedIntFib)(3) );
	cout<<"cDomainNaturalNumber domainInteger1Max5( (unsignedIntFib)(5) );"<<endl;
	cDomainNaturalNumber domainInteger1Max5( (unsignedIntFib)(5) );
	cout<<"cDomainNaturalNumber domainInteger2Max5( (unsignedIntFib)(5) );"<<endl;
	cDomainNaturalNumber domainInteger2Max5( (unsignedIntFib)(5) );
	cout<<"cDomainNaturalNumber domainInteger1Max5Scale0p02( (unsignedIntFib)(5), 0.02 );"<<endl;
	cDomainNaturalNumber domainInteger1Max5Scale0p02( (unsignedIntFib)(5), 0.02 );
	cout<<"cDomainNaturalNumber domainInteger2Max5Scale0p02( (unsignedIntFib)(5), 0.02 );"<<endl;
	cDomainNaturalNumber domainInteger2Max5Scale0p02( (unsignedIntFib)(5), 0.02 );
	
	
	cout<<"vector<cDomainSingle*> vElementdomains( 1 );"<<endl;
	vector<cDomainSingle*> vElementdomains( 1 );
	cout<<"vElementdomains[0] = &domainInteger2Max5;"<<endl;
	vElementdomains[0] = (&domainInteger2Max5);
	cout<<"cDomainVector domainVector( vElementdomains );"<<endl;
	cDomainVector domainVector( vElementdomains );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with domainInteger1Max8
	cDomain *actualDomain=&domainInteger1Max8;
	string szActualDomainName="domainInteger1Max8";
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max8, "domainInteger2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max3, "domainInteger1Max3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max3, "domainInteger2Max3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5, "domainInteger1Max5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5, "domainInteger2Max5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5Scale0p02, "domainInteger1Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5Scale0p02, "domainInteger2Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger2Max8
	actualDomain=&domainInteger2Max8;
	szActualDomainName="domainInteger2Max8";
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max8, "domainInteger2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max3, "domainInteger1Max3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max3, "domainInteger2Max3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5, "domainInteger1Max5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5, "domainInteger2Max5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5Scale0p02, "domainInteger1Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5Scale0p02, "domainInteger2Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Max3
	actualDomain=&domainInteger1Max3;
	szActualDomainName="domainInteger1Max3";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max8, "domainInteger2Max8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max3, "domainInteger1Max3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max3, "domainInteger2Max3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5, "domainInteger1Max5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5, "domainInteger2Max5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5Scale0p02, "domainInteger1Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5Scale0p02, "domainInteger2Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger2Max3
	actualDomain=&domainInteger2Max3;
	szActualDomainName="domainInteger2Max3";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max8, "domainInteger2Max8" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max3, "domainInteger1Max3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max3, "domainInteger2Max3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5, "domainInteger1Max5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5, "domainInteger2Max5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5Scale0p02, "domainInteger1Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5Scale0p02, "domainInteger2Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Max5
	actualDomain=&domainInteger1Max5;
	szActualDomainName="domainInteger1Max5";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max8, "domainInteger2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max3, "domainInteger1Max3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max3, "domainInteger2Max3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5, "domainInteger1Max5" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5, "domainInteger2Max5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5Scale0p02, "domainInteger1Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5Scale0p02, "domainInteger2Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger2Max5
	actualDomain=&domainInteger2Max5;
	szActualDomainName="domainInteger2Max5";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max8, "domainInteger2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max3, "domainInteger1Max3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max3, "domainInteger2Max3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5, "domainInteger1Max5" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5, "domainInteger2Max5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5Scale0p02, "domainInteger1Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5Scale0p02, "domainInteger2Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger1Max5Scale0p02
	actualDomain=&domainInteger1Max5Scale0p02;
	szActualDomainName="domainInteger1Max5Scale0p02";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max8, "domainInteger2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max3, "domainInteger1Max3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max3, "domainInteger2Max3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5, "domainInteger1Max5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5, "domainInteger2Max5" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5Scale0p02, "domainInteger1Max5Scale0p02" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5Scale0p02, "domainInteger2Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainInteger2Max5Scale0p02
	actualDomain=&domainInteger2Max5Scale0p02;
	szActualDomainName="domainInteger2Max5Scale0p02";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max8, "domainInteger2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max3, "domainInteger1Max3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max3, "domainInteger2Max3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5, "domainInteger1Max5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5, "domainInteger2Max5" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5Scale0p02, "domainInteger1Max5Scale0p02" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5Scale0p02, "domainInteger2Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	//compare with domainVector
	actualDomain=&domainVector;
	szActualDomainName="domainVector";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max8, "domainInteger1Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max8, "domainInteger2Max8" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max3, "domainInteger1Max3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max3, "domainInteger2Max3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5, "domainInteger1Max5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5, "domainInteger2Max5" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger1Max5Scale0p02, "domainInteger1Max5Scale0p02" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Max5Scale0p02, "domainInteger2Max5Scale0p02" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainVector, "domainVector" );

	return iReturn;
}



/**
 * This method tests a in the xml -format stored cDomainNaturalNumber.
 *
 * @param szFilename the name of the file wher the cDomainNaturalNumber is stored
 * @param uiMax the maxs the cDomainNaturalNumber has
 * @param dScalingfactor the scalingfactor for the cDomainNaturalNumber domain
 * @return the number of errors occured in the test
 */
int testXmlDomain( const string szFilename, const unsigned int uiMax,
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

		if ( szElementName == "naturalNumber" ){
			cout<<"The root element is correctly named \"naturalNumber\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"naturalNumber\"."<<endl;
			iReturn++;
		}
		
		int iMaxLoaded = 0;
		const char * pcAttributMax = pXmlElement->Attribute( "max", &iMaxLoaded );
		
		if ( pcAttributMax == NULL ){
			cerr<<"Error: The domain has no attribute maxs."<<endl;
			iReturn++;
		}else if ( iMaxLoaded == (int)uiMax ) {
			cout<<"The number of maxs of the domain are correctly \""<< uiMax <<"\". "<<endl;
		}else{
			cerr<<"Error: The number of maxs of the loaded domain are \""<< iMaxLoaded
				<<"\", but should be \""<< uiMax <<"\"."<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with maximal number 4 and scaling factor 1 to Xml"<<endl;
	
	cout<<"cDomainNaturalNumber testDomainNaturalNumberMax4( 4 );"<<endl;
	cDomainNaturalNumber testDomainNaturalNumberMax4( 4 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax4.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	bool bStoreSuccesfull = testDomainNaturalNumberMax4.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, 4, 1 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with maximal number 16 Max and scaling factor 0.214 to Xml"<<endl;
	
	cout<<"cDomainNaturalNumber testDomainNaturalNumberMax16S0p214( 16, 0.214 );"<<endl;
	cDomainNaturalNumber testDomainNaturalNumberMax16S0p214( 16, 0.214 );
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax16S0p214.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = testDomainNaturalNumberMax16S0p214.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, 16, 0.214 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with maximal number 58 and scaling factor 64.125 to Xml"<<endl;
	
	cout<<"cDomainNaturalNumber testDomainNaturalNumberMax58S64p125( 58, 64.125 );"<<endl;
	cDomainNaturalNumber testDomainNaturalNumberMax58S64p125( 58, 64.125 );
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax58S64p125.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = testDomainNaturalNumberMax58S64p125.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, 58, 64.125 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with maximal number 3 and scaling factor 0.125 to Xml"<<endl;
	
	cout<<"cDomainNaturalNumber testDomainNaturalNumberMax3S0p125( 3, 0.125 );"<<endl;
	cDomainNaturalNumber testDomainNaturalNumberMax3S0p125( 3, 0.125 );
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax3S0p125.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = testDomainNaturalNumberMax3S0p125.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlDomain( szFileNameBuffer, 3, 0.125 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple domain with maximal number 0 and scaling factor 0.01 to Xml"<<endl;
	
	cout<<"cDomainNaturalNumber testDomainNaturalNumberMax0S0p01( 0, 0.01 );"<<endl;
	cDomainNaturalNumber testDomainNaturalNumberMax0S0p01( 0, 0.01 );
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax0S0p01.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = testDomainNaturalNumberMax0S0p01.storeXml( *fileXml );
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with a maximal number of 4 and scaling factor 1"<<endl;
	
	cout<<"cDomainNaturalNumber testDomainNaturalNumberMax4( 4 );"<<endl;
	cDomainNaturalNumber testDomainNaturalNumberMax4( 4 );

	//test get compressed size
	if ( testDomainNaturalNumberMax4.getCompressedSize() == 72 ){
	
		cout<<"The compressed size of the domain is correctly 72 . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			testDomainNaturalNumberMax4.getCompressedSize() << ", but should be 72 . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax4.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = testDomainNaturalNumberMax4.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cTestDomainNaturalNumberMax4Byts[] = {(char)0x04, (char)0x04, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberMax4Byts, 10 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with a maximal number of 256 and scaling factor 0.214"<<endl;
	
	cout<<"cDomainNaturalNumber testDomainNaturalNumberMax256S0p214( 256, 0.214 );"<<endl;
	cDomainNaturalNumber testDomainNaturalNumberMax256S0p214( 256, 0.214 );
	
	//test get compressed size
	if ( testDomainNaturalNumberMax256S0p214.getCompressedSize() == 8 + 64 + 8 + 2 * 56 ){
	
		cout<<"The compressed size of the domain is correctly 188 . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			testDomainNaturalNumberMax256S0p214.getCompressedSize() << ", but should be 188 . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax256S0p214.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = testDomainNaturalNumberMax256S0p214.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cTestDomainNaturalNumberMax16S0p214[] = {(char)0x06,
		(char)0x00, (char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
		(char)0x07,
		(char)0x31, (char)0x08, (char)0xAC, (char)0x1C, (char)0x5A, (char)0x64, (char)0x1B,
		(char)0xC9, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberMax16S0p214,25 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with a maximal number of 58 and scaling factor 64.125"<<endl;
	
	cout<<"cDomainNaturalNumber testDomainNaturalNumberMax58S64p125( 58, 64.125 );"<<endl;
	cDomainNaturalNumber testDomainNaturalNumberMax58S64p125( 58, 64.125 );
	
	//test get compressed size
	unsigned int uiCompressedSize = 72 + 8 + 16 * 2;
	if ( testDomainNaturalNumberMax58S64p125.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			testDomainNaturalNumberMax58S64p125.getCompressedSize() <<
			", but should be "<< uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax58S64p125.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = testDomainNaturalNumberMax58S64p125.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cTestDomainNaturalNumberMax58S64p125[] = {(char)0x06,
		(char)0x3A, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
		(char)0x02,
		(char)0x01, (char)0x02, (char)0xFD, (char)0xFF, (char)0x00};
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberMax58S64p125, 15 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple domain with the maximal number of 25 and scaling factor 64.125 and a 4 bit shift with restbit (char)0x05"<<endl;
	
	cout<<"cDomainNaturalNumber testDomainNaturalNumberMax58S64p125S4( 25, 64.125 );"<<endl;
	cDomainNaturalNumber testDomainNaturalNumberMax58S64p125S4( 25, 64.125 );
	
	//test get compressed size
	uiCompressedSize = 72 + 8 + 16 * 2;
	if ( testDomainNaturalNumberMax58S64p125S4.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<< uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			testDomainNaturalNumberMax58S64p125S4.getCompressedSize() <<
			", but should be "<< uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax25S64p125S4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x05;
	cNumberOfRestBit = 4 ;
	bStoreSuccesfull = testDomainNaturalNumberMax58S64p125S4.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cTestDomainNaturalNumberMax58S64p125S4[] = {(char)0x65,
		(char)0x90, (char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x20,
		(char)0x10, (char)0x20, (char)0xD0, (char)0xFF, (char)0x0F};
		
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberMax58S64p125S4, 15 );


	return iReturn;
}



/**
 * This method store -value -method of the class.
 *
 * methods tested:
 * 	- unsignedIntFib getCompressedSizeForValue() const;
 * 	- bool storeValue( doubleFib dValue, ostream & stream, char & cRestBit, unsigned char & uiRestMaxPosition ) const;
 * 	- bool storeUnscaledValue( longFib lValue, ostream & stream, char & cRestBit, unsigned char & uiRestMaxPosition ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStoreValue( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 423.0 in a Domain with maximum of 6921 and scaling factor 1"<<endl;
	
	unsigned int uiBitsOfDomain = 13;
	cout<<"cDomainNaturalNumber testDomainNaturalNumberMax6921( 6921 );"<<endl;
	cDomainNaturalNumber testDomainNaturalNumberMax6921( 6921 );

	//test get compressed size
	if ( testDomainNaturalNumberMax6921.getCompressedSizeForValue() == uiBitsOfDomain ){
	
		cout<<"The compressed size for a domainvalue is correctly "<<
			uiBitsOfDomain <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size for a domainvalue is "<<
			testDomainNaturalNumberMax6921.getCompressedSizeForValue() <<
			", but should be "<< uiBitsOfDomain <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax6921V423.fib" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	double dValueToStore = 423.0;
	bool bStoreSuccesfull = testDomainNaturalNumberMax6921.storeValue(
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
	const char cTestDomainNaturalNumberMax13V423[] = {(char)0xA7, (char)0x01};//dValueToStore = 01A7
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberMax13V423, 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 423 in a Domain with maximum of 6921 and scaling factor 1"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax6921Vu423.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	long lValueToStore = 423;
	bStoreSuccesfull = testDomainNaturalNumberMax6921.storeUnscaledValue(
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
	const char cTestDomainNaturalNumberMax13Vu423[] = {(char)0xA7, (char)0x01};//dValueToStore = 01A7
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberMax13Vu423, 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 423.4 in a Domain with maximum of 6921 and scaling factor 1"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax6921V423p4.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	dValueToStore = 423.4;
	bStoreSuccesfull = testDomainNaturalNumberMax6921.storeValue(
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
	const char cTestDomainNaturalNumberMax13V423p4[] = {(char)0xA7, (char)0x01};//dValueToStore = 01A7
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberMax13V423p4, 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 422.51 in a Domain with maximum of 6921 and scaling factor 1"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax6921V422p51.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	dValueToStore = 422.51;
	bStoreSuccesfull = testDomainNaturalNumberMax6921.storeValue(
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
	const char cTestDomainNaturalNumberMax13V422p5[] = {(char)0xA7, (char)0x01};//dValueToStore = 01A7
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberMax13V422p5, 2 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number -22.5 in a Domain with maximum of 6921 and scaling factor 1"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax6921Vm22p5.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	dValueToStore = -22.5;
	bStoreSuccesfull = testDomainNaturalNumberMax6921.storeValue(
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
	const char cTestDomainNaturalNumberMax13Vm22p5[] = {(char)0x00, (char)0x00};//dValueToStore = 0
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberMax13Vm22p5, 2 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 10000.0 in a Domain with maximum of 6921 and scaling factor 1"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax6921V10000.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	dValueToStore = 10000.0;
	bStoreSuccesfull = testDomainNaturalNumberMax6921.storeValue(
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
	if ( ( ucRestBit == (char)0x1b ) && ( cNumberOfRestBit == 5 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x1b and number of restbit should be 5 . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cTestDomainNaturalNumberMax13V10000[] = {(char)0x09, (char)0x1b};//dValueToStore = (char)0x1B09
	iReturn += compareBytsWithFile( szFileNameBuffer, cTestDomainNaturalNumberMax13V10000, 2 );



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 614 in a Domain with maximum of 3914 and scaling factor 1.25"<<endl;
	
	uiBitsOfDomain = 12;
	cout<<"cDomainNaturalNumber testDomainNaturalNumberMax3914S1p25( 3914, 1.25 );"<<endl;
	cDomainNaturalNumber testDomainNaturalNumberMax3914S1p25( 3914, 1.25 );

	//test get compressed size
	if ( testDomainNaturalNumberMax3914S1p25.getCompressedSizeForValue() == uiBitsOfDomain ){
	
		cout<<"The compressed size for a domainvalue is correctly "<<
			uiBitsOfDomain <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size for a domainvalue is "<<
			testDomainNaturalNumberMax3914S1p25.getCompressedSizeForValue() <<
			", but should be "<< uiBitsOfDomain <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax3914S1p25V614.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	lValueToStore = 614;
	bStoreSuccesfull = testDomainNaturalNumberMax3914S1p25.storeUnscaledValue(
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
	const char cDomainNaturalNumberMax3914S1p25V614[] = {(char)0x66, (char)0x02};//dValueToStore = (char)0x266
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainNaturalNumberMax3914S1p25V614, 2 );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 767.5 in a Domain with maximum of 3914 and scaling factor 1.25"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax3914S1p25V767p5.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	dValueToStore = 767.5;
	bStoreSuccesfull = testDomainNaturalNumberMax3914S1p25.storeValue(
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
	const char cDomainNaturalNumberMax3914S1p25V767p5[] = {(char)0x66, (char)0x02};//dValueToStore = (char)0x266
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainNaturalNumberMax3914S1p25V767p5, 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a the number 3906.3 and 3716.20 in a Domain with maximum of 3914 and scaling factor 1.25"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainNaturalNumberMax3914S1p25V3906p3V3716p20.fib" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	dValueToStore = 3906.3;
	bStoreSuccesfull = testDomainNaturalNumberMax3914S1p25.storeValue(
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
	const char cDomainNaturalNumberMax3914S1p25V3906p3[] = {(char)0x35};//dValueToStore = (char)0xC35
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainNaturalNumberMax3914S1p25V3906p3, 1 );


	dValueToStore = 3716.20;
	bStoreSuccesfull = testDomainNaturalNumberMax3914S1p25.storeValue(
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
	const char cDomainNaturalNumberMax3914S1p25V3906p3V3716p20[] = {(char)0x35, (char)0xDC, (char)0xB9, (char)0x00};//dValueToStore = (char)0xB9D
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainNaturalNumberMax3914S1p25V3906p3V3716p20, 4 );


	return iReturn;
}
























