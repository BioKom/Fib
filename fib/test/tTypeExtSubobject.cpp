/**
 * @file tTypeExtSubobject
 * file name: tTypeExtSubobject.cpp
 * @author Betti Oesterholz
 * @date 06.11.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cTypeExtSubobject.
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
 * This file contains the test for the class cTypeExtSubobject,
 * which represents the type for external subobjects.
 *
 *
 *  What's tested of class cTypeExtSubobject:
 * 	- cTypeExtSubobject( const unsignedIntFib iInNumberExtSubobject )
 * 	- unsignedIntFib getNumberOfExtSubobject() const
 * 	- unsignedIntFib getType() const
 * 	- bool isCompatible( const cDomain &domain ) const
 * 	- cDomain *getStandardDomain( ) const
 * 	- bool equal( const cTypeElement &typeElement ) const
 * 	- bool operator==( const cTypeElement &typeElement ) const
 * 	- cTypeElement *clone() const
 * 	- bool equalElementType( const cTypeElement & typeElement ) const
 * 	- bool storeXml( ostream & ostream, const cDomain * domain = NULL ) const
 * 	- unsignedLongFib getCompressedSize() const
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const
 *
 */
/*
History:
06.11.2011  Oesterholz  created
02.02.2012  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR implemented
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
01.08.2013  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR as default (not case removed)
*/

#include "version.h"

#include "cTypeExtSubobject.h"
#include "cTypeProperty.h"
#include "cTypeInVar.h"
#include "cTypeDimension.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainInteger.h"
#include "cDomainVector.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <iomanip>

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif


using namespace fib;
using namespace std;


int testCostructor( unsigned long &ulTestphase );//+getNumberOfDimension()
int testIsCompatibleGetStandardDomain( unsigned long &ulTestphase );
int testClone( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testEqualElementType( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );

int testExtSubobjNumber( unsigned long &ulTestphase );


int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cTypeExtSubobject methods"<<endl;
	cout<<      "=========================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testIsCompatibleGetStandardDomain( ulTestphase );
	iReturn += testClone( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testEqualElementType( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );

	iReturn += testExtSubobjNumber( ulTestphase );
	
	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * This method tests the constructors and the getNumberOfDimension()
 * and getType() method of the cTypeExtSubobject class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cTypeExtSubobject"<<endl;

	cout<<"cTypeExtSubobject typeExtSubobject( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject( 0 );

	//check the getType() methode from cTypeExtSubobject
	if ( typeExtSubobject.getType() == (unsignedIntFib)(13) ){
	
		cout<<"The type of external subobjects is correctly 13 . "<<endl;
	}else{
		cerr<<"Error: The type of external subobjects is "<<
			typeExtSubobject.getType()<<" but should be 13 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfExtSubobject() methode from cTypeExtSubobject
	if ( typeExtSubobject.getNumberOfExtSubobject() == (unsignedIntFib)(0) ){
	
		cout<<"The type of external subobjects is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The type of external subobjects is "<<
			typeExtSubobject.getNumberOfExtSubobject()<<" but should be 0 ."<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cTypeExtSubobject with the subobject number 4"<<endl;
	
	cout<<"cTypeExtSubobject typeExtSubobjectNr4( 4 );"<<endl;
	cTypeExtSubobject typeExtSubobjectNr4( 4 );

	//check the getType() methode from cTypeExtSubobject
	if ( typeExtSubobjectNr4.getType() == (unsignedIntFib)(13) ){
	
		cout<<"The type of external subobjects is correctly 13 . "<<endl;
	}else{
		cerr<<"Error: The type of external subobjects is "<<
			typeExtSubobjectNr4.getType()<<" but should be 13 ."<<endl;
		iReturn++;
	}
	//check the getNumberOfExtSubobject() methode from cTypeExtSubobject
	if ( typeExtSubobjectNr4.getNumberOfExtSubobject() == (unsignedIntFib)(4) ){
	
		cout<<"The type of external subobjects is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The type of external subobjects is "<<
			typeExtSubobjectNr4.getNumberOfExtSubobject()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the isCompatible() and getStandardDomain() method of
 * the cTypeExtSubobject class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testIsCompatibleGetStandardDomain( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the global standard domain for the cTypeExtSubobject"<<endl;
	
	cout<<"cTypeExtSubobject typeExtSubobject( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject( 0 );

	//check the getType() methode from cTypeExtSubobject
	if ( typeExtSubobject.getType() == (unsignedIntFib)(13) ){
	
		cout<<"The type of external subobjects is correctly 13 . "<<endl;
	}else{
		cerr<<"Error: The type of external subobjects is "<<
			typeExtSubobject.getType()<<" but should be 13 ."<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cout<<"domainInt = new cDomainNaturalNumberBit( 12 ); "<<endl;
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for integer domain
	if ( ! typeExtSubobject.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to the integer domain domainInt. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the integer domain domainInt."<<endl;
		iReturn++;
	}
	delete domainInt;
	
	//check compatible for integer domain
	cout<<"domainInt =  cDomainInteger( 2, 10 ); "<<endl;
	domainInt = new cDomainInteger( 2, 10 );
	
	//check the isCompatible() methode for integer domain
	if ( ! typeExtSubobject.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to the integer domain domainInt. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the integer domain domainInt."<<endl;
		iReturn++;
	}
	delete domainInt;
	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( typeExtSubobject.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( typeExtSubobject.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( typeExtSubobject.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( typeExtSubobject.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;
	
	//test the getStandardDomain() method of the property
	cDomain * pStandardDomain = typeExtSubobject.getStandardDomain();
	
	if ( pStandardDomain == NULL ){
	
		cerr<<"Error: The standard domain is not given back, but the Null pointer NULL."<<endl;
		iReturn++;
		
	}else if ( pStandardDomain->getType()=="DomainVector" ){
	
		cDomainVector * pDomainVector = (cDomainVector*)pStandardDomain;
		
		if ( pDomainVector->getNumberOfElements() == 0 ){
		
			cout<<"The domain has correctly 0 elements. "<<endl;
		}else{
			cerr<<"Error: The domain has "<<
				pDomainVector->getNumberOfElements()<<" elements, but should have 0."<<endl;
			iReturn++;
		}
		
		delete pStandardDomain;
	}else{
		cerr<<"Error: The standard domain has the type "<<
			pStandardDomain->getType()<<" and not the type DomainVector."<<endl;
		iReturn++;
		delete pStandardDomain;
	}

	return iReturn;
}


/**
 * This method tests the clone() method of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testClone( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the clone() method"<<endl;

	cout<<"cTypeExtSubobject typeExtSubobject( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject( 0 );

	cout<<"cTypeExtSubobject *typeExtSubobjectClone1 = typeExtSubobject.clone();"<<endl;
	cTypeExtSubobject *typeExtSubobjectClone1 = typeExtSubobject.clone();


	cout<<endl<<"checking the clone:"<<endl;
	//check the getType() methode from cTypeExtSubobject
	if ( typeExtSubobjectClone1->getType() == (unsignedIntFib)(13) ){
	
		cout<<"The type of external subobjects is correctly 13 . "<<endl;
	}else{
		cerr<<"Error: The type of external subobjects is "<<
			typeExtSubobjectClone1->getType()<<" but should be 13 ."<<endl;
		iReturn++;
	}
	delete typeExtSubobjectClone1;

	return iReturn;
}


/**
 * This method tests the equal() method and the operator== of two given
 * cTypeElement objects which are equal.
 *
 * @param typeElement1 the first type to compare
 * @param szNameType1 the name of the first type to compare
 * @param typeElement2 the secound type to compare to
 * @param szNameType2 the name of the secound type to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualTyps( const cTypeElement &typeElement1, const string &szNameType1,
	const cTypeElement &typeElement2, const string &szNameType2 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	if ( typeElement1.equal( typeElement2 ) ){
	
		cout<<"The "<<szNameType1<<" is equal to "<<szNameType2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameType1<<" is not equal to "<<
			szNameType2<<"."<<endl;
		iReturn++;
	}
	if ( typeElement1==typeElement2 ){
	
		cout<<"The "<<szNameType1<<" is equal (operator==) to "<<
			szNameType2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameType1<<" is not equal (operator==) to "<<
			szNameType2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the equal() method and the operator== of two given
 * cTypeElement objects which are not equal.
 *
 * @param typeElement1 the first type to compare
 * @param szNameType1 the name of the first type to compare
 * @param typeElement2 the secound type to compare to
 * @param szNameType2 the name of the secound type to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualTyps( const cTypeElement &typeElement1, const string &szNameType1,
	const cTypeElement &typeElement2, const string &szNameType2 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	if ( ! typeElement1.equal( typeElement2 ) ){
	
		cout<<"The "<<szNameType1<<" is not equal to "<<szNameType2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameType1<<" is equal to "<<
			szNameType2<<"."<<endl;
		iReturn++;
	}
	if ( ! (typeElement1==typeElement2) ){
	
		cout<<"The "<<szNameType1<<" is not equal (operator==) to "<<
			szNameType2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameType1<<" is equal (operator==) to "<<
			szNameType2<<"."<<endl;
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

	//create cTypeExtSubobjects to compare
	cout<<"cTypeExtSubobject typeExtSubobject1( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject1( 0 );
	cout<<"cTypeExtSubobject typeExtSubobject2( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject2( 0 );

	cout<<"cTypeExtSubobject typeExtSubobjectNr1( 1 );"<<endl;
	cTypeExtSubobject typeExtSubobjectNr1( 1 );

	cout<<"cTypeExtSubobject typeExtSubobjectNr333( 333 );"<<endl;
	cTypeExtSubobject typeExtSubobjectNr333( 333 );
	
	cout<<"cTypeInVar typeInVar1N1( 1 );"<<endl;
	cTypeInVar typeInVar1N1( 1 );

	cout<<"cTypeProperty typeProperty( 1 );"<<endl;
	cTypeProperty typeProperty( 1 );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with typeExtSubobject1
	cTypeElement *actualType=&typeExtSubobject1;
	string szActualTypeName="typeExtSubobject1";
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeExtSubobject1, "typeExtSubobject1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeExtSubobject2, "typeExtSubobject2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobjectNr1, "typeExtSubobjectNr1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobjectNr333, "typeExtSubobjectNr333" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeExtSubobject2
	actualType=&typeExtSubobject2;
	szActualTypeName="typeExtSubobject2";
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeExtSubobject1, "typeExtSubobject1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeExtSubobject2, "typeExtSubobject2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobjectNr1, "typeExtSubobjectNr1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobjectNr333, "typeExtSubobjectNr333" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );
	
	//compare with typeExtSubobjectNr1
	actualType=&typeExtSubobjectNr1;
	szActualTypeName="typeExtSubobjectNr1";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobject1, "typeExtSubobject1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobject2, "typeExtSubobject2" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeExtSubobjectNr1, "typeExtSubobjectNr1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobjectNr333, "typeExtSubobjectNr333" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeExtSubobjectNr333
	actualType=&typeExtSubobjectNr333;
	szActualTypeName="typeExtSubobjectNr333";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobject1, "typeExtSubobject1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobject2, "typeExtSubobject2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobjectNr1, "typeExtSubobjectNr1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeExtSubobjectNr333, "typeExtSubobjectNr333" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeInVar1N1
	actualType=&typeInVar1N1;
	szActualTypeName="typeInVar1N1";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobject1, "typeExtSubobject1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobject2, "typeExtSubobject2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobjectNr1, "typeExtSubobjectNr1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobjectNr333, "typeExtSubobjectNr333" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeProperty
	actualType=&typeProperty;
	szActualTypeName="typeProperty";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobject1, "typeExtSubobject1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobject2, "typeExtSubobject2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobjectNr1, "typeExtSubobjectNr1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeExtSubobjectNr333, "typeExtSubobjectNr333" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	return iReturn;
}


/**
 * This method tests the equalElementType() method of the class.
 *
 * methods tested:
 * 	- bool equalElementType( const cTypeElement & typeElement ) const
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testEqualElementType( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equalElementType method "<<endl;

	//create cTypeDimensions to compare
	cout<<"cTypeExtSubobject typeExtSubobject1( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject1( 0 );
	
	cout<<"cTypeExtSubobject typeExtSubobject2( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject2( 0 );

	cout<<"cTypeExtSubobject typeExtSubobjectNr1( 1 );"<<endl;
	cTypeExtSubobject typeExtSubobjectNr1( 1 );

	cout<<"cTypeInVar typeInVar1( 1 );"<<endl;
	cTypeInVar typeInVar1( 1 );

	cout<<"cTypeProperty typeProperty( 1 );"<<endl;
	cTypeProperty typeProperty( 1 );

	cout<<"cTypeDimension typeDimension1D3( 3 );"<<endl;
	cTypeDimension typeDimension1D3( 3 );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	if ( typeExtSubobject1.equalElementType( typeExtSubobject1 ) ){
	
		cout<<"The typeExtSubobject1 is of the same type as typeExtSubobject1. "<<endl;
	}else{
		cerr<<"Error: The typeExtSubobject1 is not of the same type as typeExtSubobject1."<<endl;
		iReturn++;
	}
	if ( typeExtSubobject1.equalElementType( typeExtSubobject2 ) ){
	
		cout<<"The typeExtSubobject1 is of the same type as typeExtSubobject2. "<<endl;
	}else{
		cerr<<"Error: The typeExtSubobject1 is not of the same type as typeExtSubobject2."<<endl;
		iReturn++;
	}
	if ( ! typeExtSubobject1.equalElementType( typeExtSubobjectNr1 ) ){
	
		cout<<"The typeExtSubobject1 is not of the same type as typeExtSubobjectNr1. "<<endl;
	}else{
		cerr<<"Error: The typeExtSubobject1 is of the same type as typeExtSubobjectNr1."<<endl;
		iReturn++;
	}

	if ( ! typeExtSubobject1.equalElementType( typeInVar1 ) ){
	
		cout<<"The typeExtSubobject1 is not of the same type as typeInVar1. "<<endl;
	}else{
		cerr<<"Error: The typeExtSubobject1 is of the same type as typeInVar1."<<endl;
		iReturn++;
	}
	if ( ! typeExtSubobject1.equalElementType( typeProperty ) ){
	
		cout<<"The typeExtSubobject1 is not of the same type as typeProperty. "<<endl;
	}else{
		cerr<<"Error: The typeExtSubobject1 is of the same type as typeProperty."<<endl;
		iReturn++;
	}

	if ( ! typeExtSubobject1.equalElementType( typeDimension1D3 ) ){
	
		cout<<"The typeExtSubobject1 is not of the same type as typeDimension1D3. "<<endl;
	}else{
		cerr<<"Error: The typeExtSubobject1 is of the same type as typeDimension1D3."<<endl;
		iReturn++;
	}

	if ( ! typeExtSubobjectNr1.equalElementType( typeExtSubobject2 ) ){
	
		cout<<"The typeExtSubobjectNr1 is of the same type as typeExtSubobject2. "<<endl;
	}else{
		cerr<<"Error: The typeExtSubobjectNr1 is not of the same type as typeExtSubobject2."<<endl;
		iReturn++;
	}
	if ( typeExtSubobjectNr1.equalElementType( typeExtSubobjectNr1 ) ){
	
		cout<<"The typeExtSubobjectNr1 is not of the same type as typeExtSubobjectNr1. "<<endl;
	}else{
		cerr<<"Error: The typeExtSubobjectNr1 is of the same type as typeExtSubobjectNr1."<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests a in the xml -format stored cDomainVector with
 * cDomainNaturalNumberBit domains.
 *
 * @param szFilename the name of the file wher the cDomainNaturalNumberBit is stored
 * @param uiNumberOfExtObject the number of the external object
 * @param bHasDomain if true a domain was stored with the type
 * @param uiBits a vector with the bits the cDomainNaturalNumberBit
 * 	domains have
 * @param scalingfactor a vector with the scalingfactors for the
 * 	cDomainNaturalNumberBit domains have
 * @return the number of errors occured in the test
 */
int testXmlType( const string szFilename,
		const unsigned int uiNumberOfExtObject,
		bool bHasDomain, unsigned int uiBits, double dScalingfactor ){
	
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

		if ( szElementName == "externSubobject" ){
			cout<<"The root element is correctly named \"externSubobject\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"externSubobject\"."<<endl;
			iReturn++;
		}
		
		int iNumberOfExtobjectLoaded = 0;
		const char * pcAttributNumber = pXmlElement->Attribute( "number",
			&iNumberOfExtobjectLoaded );
		
		if ( pcAttributNumber == NULL ){
			cerr<<"Error: The type has no attribute \"number\"."<<endl;
			iReturn++;
		}else if ( iNumberOfExtobjectLoaded == (int)uiNumberOfExtObject ) {
			cout<<"The number of the external subobject is correctly \""<<uiNumberOfExtObject <<"\". "<<endl;
		}else{
			cerr<<"Error: The number of the external subobject is \""<<
				iNumberOfExtobjectLoaded <<"\", but should be \""<<
				uiNumberOfExtObject <<"\"."<<endl;
			iReturn++;
		}
		
	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}

	if ( bHasDomain ){
		//read the subdomain
	
		xmlRootHandle = xmlHandle.FirstChildElement();
	
		pXmlElement = xmlRootHandle.FirstChildElement().Element();
	
		// should always have a valid root but handle gracefully if it does
		string szElementName = pXmlElement->Value();
	
		if ( szElementName == "naturalNumberB" ){
			cout<<"The  element is correctly named \"naturalNumberB\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the element is \""<< szElementName <<"\" and not \"naturalNumberB\"."<<endl;
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
		
		long lMantissa = lfMantissa;
		long lExponent = lfExponent;
	
		char szScalingfactorBuffer[128];
		szScalingfactorBuffer[0] = 0;
		sprintf ( szScalingfactorBuffer, "%li * 2^(%li)", lMantissa, lExponent );
		
		string szScalingfactor( szScalingfactorBuffer );
		
		if ( ( dScalingfactor == 1.0 ) && ( pcAttributeScalingfactor == NULL ) ){
			//no scalingfactor needed
			cout<<"No scalingfactor attribut. This is correct because the scalingfactor is 1.0 . "<<endl;
		}else{
			if ( pcAttributeScalingfactor == NULL ){
				cerr<<"Error: The domain has no attribute scalingfactor."<<endl;
				iReturn++;
			}else if ( szScalingfactor == pcAttributeScalingfactor ) {
				cout<<"The scalingfactor of the domain is correctly \""<< pcAttributeScalingfactor <<"\". "<<endl;
			}else{
				cerr<<"Error: The scalingfactor of the loaded domain is \""<< pcAttributeScalingfactor
					<<"\", but should be \""<< dScalingfactor <<"\" (=\""<< szScalingfactor <<"\")."<<endl;
				iReturn++;
			}
		}
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple external subobjects type"<<endl;

	cout<<"cTypeExtSubobject typeExtSubobject1( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject1( 0 );

	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtSubobject1.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeExtSubobject1.storeXml( *fileXml );"<<endl;
	bool bStoreSuccesfull = typeExtSubobject1.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, 0, false, 0, 0.0 );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a external subobjects type with a different subobject number"<<endl;

	cout<<"cTypeExtSubobject typeExtSubobjectNr4( 4 );"<<endl;
	cTypeExtSubobject typeExtSubobjectNr4( 4 );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtSubobjectNr4.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeExtSubobjectNr4.storeXml( *fileXml );"<<endl;
	bStoreSuccesfull = typeExtSubobjectNr4.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer,
		4, false, 0, 0.0 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a 5'th external subobjects type with a domain"<<endl;

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB4( 4 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB4( 4 );
	unsigned int uiBits = 4;
	double dScalingfactor = 1.0;

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtSubobject1Dom.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeExtSubobject1.storeXml( *fileXml, &domainNaturalNumberB4 );"<<endl;
	bStoreSuccesfull = typeExtSubobject1.storeXml( *fileXml, &domainNaturalNumberB4 );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer,
		0,
		true, uiBits, dScalingfactor );


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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple external subobjekt type for number 0"<<endl;
	
	cout<<"cTypeExtSubobject typeExtSubobjElement1( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobjElement1( 0 );

	//test get compressed size
	unsigned int uiCompressedSize = 8;
	if ( (unsigned int)(typeExtSubobjElement1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeExtSubobjElement1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[168];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtSubobjElement1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = typeExtSubobjElement1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeExtSubobject1[] = { (char)0xC8,
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeExtSubobject1, 2 );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a external subobjekt type for number 1"<<endl;
	
	cout<<"cTypeExtSubobject typeExtSubobjElementId1( 1 );"<<endl;
	cTypeExtSubobject typeExtSubobjElementId1( 1 );

	//test get compressed size
	uiCompressedSize = 16;
	if ( (unsigned int)(typeExtSubobjElementId1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeExtSubobjElementId1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtSubobjElementId1.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeExtSubobjElementId1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeExtSubobjectNr1[] = { (char)0xCA,
		(char)0x01, (char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeExtSubobjectNr1, 3 );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a external subobjekt type for number 127"<<endl;
	
	cout<<"cTypeExtSubobject typeExtSubobjElementId127( 127 );"<<endl;
	cTypeExtSubobject typeExtSubobjElementId127( 127 );

	//test get compressed size
	uiCompressedSize = 16;
	if ( (unsigned int)(typeExtSubobjElementId127.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeExtSubobjElementId127.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtSubobjElementId127.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeExtSubobjElementId127.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeExtSubobject255[] = { (char)0xCA,
		(char)0x7F, (char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeExtSubobject255, 3 );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a external subobjekt type for number 256"<<endl;
	
	cout<<"cTypeExtSubobject typeExtSubobjElementId128( 256 );"<<endl;
	cTypeExtSubobject typeExtSubobjElementId128( 256 );

	//test get compressed size
	uiCompressedSize = 72;
	if ( (unsigned int)(typeExtSubobjElementId128.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeExtSubobjElementId128.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtSubobjElementId128.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeExtSubobjElementId128.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}
	//test stored data
	const char cTypeExtSubobjectId128[] = { (char)0xCC,
		(char)0x00, (char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeExtSubobjectId128, 10 );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a external subobjekt type with 5 restbits"<<endl;

	//test get compressed size
	uiCompressedSize = 8;
	if ( (unsigned int)(typeExtSubobjElement1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeExtSubobjElement1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeExtSubobjElement1R5.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x05;
	cNumberOfRestBit = 5 ;
	bStoreSuccesfull = typeExtSubobjElement1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	unsigned char ucRestBit = cRestBit;
	if ( ( ucRestBit == (unsigned char)((char)0x19) ) && ( cNumberOfRestBit == 5 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x19 and number of restbit should be 5. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeExtSubobject5[] = { (char)0x05, (char)0x19 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeExtSubobject5, 2 );

	return iReturn;
}



/**
 * This method getNumberOfExtSubobject() method of the class.
 *
 * methods tested:
 * 	- unsignedIntFib getNumberOfExtSubobject() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testExtSubobjNumber( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing getNumberOfExtSubobject() method"<<endl;
	
	for ( unsigned int iteration = 0; iteration < 128; iteration++ ){
		
		const unsigned int uiNumberOfExtSubobject = (long)(rand() % ( 1 + rand() % (
			1 + rand() % (256L * 256L) ) ));
		
		cout<<"cTypeExtSubobject typeExtSubobjElement( "<<uiNumberOfExtSubobject<<" );"<<endl;
		cTypeExtSubobject typeExtSubobjElement( uiNumberOfExtSubobject );
		
			//check the getNumberOfInputComments() methode from cTypeExtSubobject
		if ( typeExtSubobjElement.getNumberOfExtSubobject() == uiNumberOfExtSubobject ){
		
			cout<<"The type of external subobjekt number is correctly "<<
				typeExtSubobjElement.getNumberOfExtSubobject()<<" . "<<endl;
		}else{
			cerr<<"Error: The type external subobjekt number is "<<
				typeExtSubobjElement.getType()<<" but should be "<<
				uiNumberOfExtSubobject<<" ."<<endl;
			iReturn++;
		}
	}

	return iReturn;
}




