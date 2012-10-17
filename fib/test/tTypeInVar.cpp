/**
 * @file tTypeInVar
 * file name: tTypeInVar.cpp
 * @author Betti Oesterholz
 * @date 14.10.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cTypeInVar.
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
 * This file contains the test for the class cTypeInVar,
 * which represents the type for input variable.
 *
 *
 *
 *  What's tested of class cTypeInVar:
 * 	- cTypeInVar( unsignedIntFib iNumberOIfInputVariable )
 * 	- unsignedIntFib getType() const
 * 	- bool isCompatible( const cDomain &domain ) const
 * 	- cDomain *getStandardDomain( ) const
 * 	- bool equal( const cTypeElement &typeElement ) const
 * 	- bool operator==( const cTypeElement &typeElement ) const
 * 	- cTypeElement *clone() const
 * 	- unsignedIntFib getNumberOfInputVariable()
 * 	- bool equalElementType( const cTypeElement & typeElement ) const
 * 	- bool storeXml( ostream & ostream, const cDomain * domain = NULL ) const
 * 	- unsignedLongFib getCompressedSize() const
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const
 *
 */
/*
History:
14.10.2009  Oesterholz  created
11.11.2009  Oesterholz  store*(), getCompressedSize() and equalElementType() tested
13.05.2010  Oesterholz  the ordering of bits for the compressed storing corrected
04.04.2011  Oesterholz  storing to binary stream
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cTypeInVar.h"
#include "cTypeProperty.h"
#include "cTypeDimension.h"
#include "cDomainNaturalNumberBit.h"
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

int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cTypeInVar methods"<<endl;
	cout<<      "==================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testIsCompatibleGetStandardDomain( ulTestphase );
	iReturn += testClone( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testEqualElementType( ulTestphase );
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
 * This method tests the constructors and the getNumberOfDimension()
 * and getType() method of the cTypeInVar class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cTypeInVar"<<endl;

	cout<<"cTypeInVar typeInVar=cTypeInVar( 1 );"<<endl;
	cTypeInVar typeInVar=cTypeInVar( 1 );

	//check the getNumberOfInputVariable() methode from cTypeInVar
	if ( typeInVar.getType() == (unsignedIntFib)(5) ){
	
		cout<<"The type of input variable is correctly 5 . "<<endl;
	}else{
		cerr<<"Error: The type of input variable is "<<
			typeInVar.getType()<<" but should be 5 ."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfInputVariable() methode from cTypeInVar
	if ( typeInVar.getNumberOfInputVariable() == (unsignedIntFib)(1) ){
	
		cout<<"The number of input variable is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of input variable is "<<
			typeInVar.getNumberOfInputVariable()<<" but should be 1 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cTypeInVar for the 5 variable"<<endl;

	cout<<"cTypeInVar typeInVar5=cTypeInVar( 5 );"<<endl;
	cTypeInVar typeInVar5=cTypeInVar( 5 );

	//check the getNumberOfInputVariable() methode from cTypeInVar
	if ( typeInVar.getType() == (unsignedIntFib)(5) ){
	
		cout<<"The type of input variable is correctly 5 . "<<endl;
	}else{
		cerr<<"Error: The type of input variable is "<<
			typeInVar.getType()<<" but should be 5 ."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfInputVariable() methode from cTypeInVar
	if ( typeInVar5.getNumberOfInputVariable()==(unsignedIntFib)(5) ){
	
		cout<<"The number of input variable is correctly 5 . "<<endl;
	}else{
		cerr<<"Error: The number of input variable is "<<
			typeInVar5.getNumberOfInputVariable()<<" but should be 5 ."<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests the isCompatible() and getStandardDomain() method of
 * the cTypeInVar class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testIsCompatibleGetStandardDomain( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the global standard domain for the cTypeInVar"<<endl;
	
	cout<<"cTypeInVar typeInVar=cTypeInVar( 2 );"<<endl;
	cTypeInVar typeInVar=cTypeInVar( 2 );

	//check the getNumberOfInputVariable() methode from cTypeInVar
	if ( typeInVar.getType() == (unsignedIntFib)(5) ){
	
		cout<<"The type of input variable is correctly 5 . "<<endl;
	}else{
		cerr<<"Error: The type of input variable is "<<
			typeInVar.getType()<<" but should be 5 ."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfInputVariable() methode from cTypeInVar
	if ( typeInVar.getNumberOfInputVariable()==(unsignedIntFib)(2) ){
	
		cout<<"The number of input variable is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of input variable is "<<
			typeInVar.getNumberOfInputVariable()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt=new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( typeInVar.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly compatible to an integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to a integer domain."<<endl;
		iReturn++;
	}
	delete domainInt;

	//TODO test more single domains
	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain=new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! typeInVar.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1=new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( ! typeInVar.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ]=new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ]=new cDomainNaturalNumberBit( 16 );
	vectorDomain=new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! typeInVar.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 8 );
	vectorDomain=new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeInVar.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain = typeInVar.getStandardDomain();
	
	if ( standardDomain == NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainNaturalNumberBit" ){
	
		cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)standardDomain;
		
		const doubleFib lowerBound=0;
		const doubleFib upperBound=65535;
		
		if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
				(domainNaturalNumberBit->getMaximum()==upperBound) ){
		
			cout<<"The domain goes correctly from "<<lowerBound<<
				" to "<<upperBound<<". "<<endl;
		}else{
			cerr<<"Error: The domain goes correctly from "<<lowerBound<<
				" to "<<upperBound<<", but it goes from "<<
				domainNaturalNumberBit->getMinimum()<<" to "<< 
				domainNaturalNumberBit->getMaximum()<<"."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainNaturalNumberBit."<<endl;
		iReturn++;
		delete standardDomain;
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

	cout<<"cTypeInVar typeInVar=cTypeInVar( 4 );"<<endl;
	cTypeInVar typeInVar=cTypeInVar( 4 );

	cout<<"cTypeInVar *pTypeInVarClone1=typeInVar.clone();"<<endl;
	cTypeInVar *pTypeInVarClone1=typeInVar.clone();


	cout<<endl<<"checking the clone:"<<endl;
	//check the getNumberOfInputVariable() methode from cTypeInVar
	if ( pTypeInVarClone1->getNumberOfInputVariable()==(unsignedIntFib)(4) ){
	
		cout<<"The number of input variable is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of input variable is "<<
			pTypeInVarClone1->getNumberOfInputVariable()<<" but should be 4 ."<<endl;
		iReturn++;
	}

	cout<<endl<<"checking the original:"<<endl;
	//check the getNumberOfInputVariable() methode from cTypeInVar
	if ( typeInVar.getNumberOfInputVariable()==(unsignedIntFib)(4) ){
	
		cout<<"The number of input variable is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of input variable is "<<
			typeInVar.getNumberOfInputVariable()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	delete pTypeInVarClone1;

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

	//create cTypeInVars to compare
	cout<<"cTypeInVar typeInVar1N1=cTypeInVar( 1 );"<<endl;
	cTypeInVar typeInVar1N1=cTypeInVar( 1 );
	cout<<"cTypeInVar typeInVar2N1=cTypeInVar( 1 );"<<endl;
	cTypeInVar typeInVar2N1=cTypeInVar( 1 );
	cout<<"cTypeInVar typeInVar1N3=cTypeInVar( 3 );"<<endl;
	cTypeInVar typeInVar1N3=cTypeInVar( 3 );
	cout<<"cTypeInVar typeInVar2N3=cTypeInVar( 3 );"<<endl;
	cTypeInVar typeInVar2N3=cTypeInVar( 3 );
	cout<<"cTypeInVar typeInVar1N5=cTypeInVar( 5 );"<<endl;
	cTypeInVar typeInVar1N5=cTypeInVar( 5 );
	cout<<"cTypeInVar typeInVar2N5=cTypeInVar( 5 );"<<endl;
	cTypeInVar typeInVar2N5=cTypeInVar( 5 );

	cout<<"cTypeProperty typeProperty( 1 );"<<endl;
	cTypeProperty typeProperty( 1 );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with typeInVar1N1
	cTypeElement *actualType=&typeInVar1N1;
	string szActualTypeName="typeInVar1N1";
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar2N1, "typeInVar2N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N3, "typeInVar1N3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N3, "typeInVar2N3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N5, "typeInVar1N5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N5, "typeInVar2N5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeInVar2N1
	actualType=&typeInVar2N1;
	szActualTypeName="typeInVar2N1";
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar2N1, "typeInVar2N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N3, "typeInVar1N3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N3, "typeInVar2N3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N5, "typeInVar1N5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N5, "typeInVar2N5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeInVar1N3
	actualType=&typeInVar1N3;
	szActualTypeName="typeInVar1N3";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N1, "typeInVar2N1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar1N3, "typeInVar1N3" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar2N3, "typeInVar2N3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N5, "typeInVar1N5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N5, "typeInVar2N5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeInVar2N3
	actualType=&typeInVar2N3;
	szActualTypeName="typeInVar2N3";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N1, "typeInVar2N1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar1N3, "typeInVar1N3" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar2N3, "typeInVar2N3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N5, "typeInVar1N5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N5, "typeInVar2N5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeInVar1N5
	actualType=&typeInVar1N5;
	szActualTypeName="typeInVar1N5";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N1, "typeInVar2N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N3, "typeInVar1N3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N3, "typeInVar2N3" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar1N5, "typeInVar1N5" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar2N5, "typeInVar2N5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeInVar2N5
	actualType=&typeInVar2N5;
	szActualTypeName="typeInVar2N5";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N1, "typeInVar2N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N3, "typeInVar1N3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N3, "typeInVar2N3" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar1N5, "typeInVar1N5" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar2N5, "typeInVar2N5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeProperty
	actualType=&typeProperty;
	szActualTypeName="typeProperty";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N1, "typeInVar2N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N3, "typeInVar1N3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N3, "typeInVar2N3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N5, "typeInVar1N5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar2N5, "typeInVar2N5" );
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
	cout<<"cTypeInVar typeInVar1( 1 );"<<endl;
	cTypeInVar typeInVar1( 1 );
	
	cout<<"cTypeInVar typeInVar2( 2 );"<<endl;
	cTypeInVar typeInVar2( 2 );

	cout<<"cTypeInVar typeInVar144( 144 );"<<endl;
	cTypeInVar typeInVar144( 144 );

	cout<<"cTypeProperty typeProperty( 1 );"<<endl;
	cTypeProperty typeProperty( 1 );

	cout<<"cTypeDimension typeDimension1D3( 3 );"<<endl;
	cTypeDimension typeDimension1D3( 3 );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	if ( typeInVar1.equalElementType( typeInVar1 ) ){
	
		cout<<"The typeInVar1 is of the same type as typeInVar1. "<<endl;
	}else{
		cerr<<"Error: The typeInVar1 is not of the same type as typeInVar1."<<endl;
		iReturn++;
	}
	if ( ! typeInVar1.equalElementType( typeInVar2 ) ){
	
		cout<<"The typeInVar1 is not of the same type as typeInVar2. "<<endl;
	}else{
		cerr<<"Error: The typeInVar1 is of the same type as typeInVar2."<<endl;
		iReturn++;
	}
	if ( ! typeInVar1.equalElementType( typeInVar144 ) ){
	
		cout<<"The typeInVar1 is not of the same type as typeInVar144. "<<endl;
	}else{
		cerr<<"Error: The typeInVar1 is of the same type as typeInVar144."<<endl;
		iReturn++;
	}

	if ( ! typeInVar1.equalElementType( typeProperty ) ){
	
		cout<<"The typeInVar1 is not of the same type as typeProperty. "<<endl;
	}else{
		cerr<<"Error: The typeInVar1 is of the same type as typeProperty."<<endl;
		iReturn++;
	}

	if ( ! typeInVar1.equalElementType( typeDimension1D3 ) ){
	
		cout<<"The typeInVar1 is not of the same type as typeDimension1D3. "<<endl;
	}else{
		cerr<<"Error: The typeInVar1 is of the same type as typeDimension1D3."<<endl;
		iReturn++;
	}


	if ( ! typeInVar144.equalElementType( typeInVar1 ) ){
	
		cout<<"The typeInVar144 is not of the same type as typeInVar1. "<<endl;
	}else{
		cerr<<"Error: The typeInVar144 is of the same type as typeInVar1."<<endl;
		iReturn++;
	}
	if ( ! typeInVar144.equalElementType( typeInVar2 ) ){
	
		cout<<"The typeInVar144 is not of the same type as typeInVar2. "<<endl;
	}else{
		cerr<<"Error: The typeInVar144 is of the same type as typeInVar2."<<endl;
		iReturn++;
	}

	if ( typeInVar144.equalElementType( typeInVar144 ) ){
	
		cout<<"The typeInVar144 is of the same type as typeInVar144. "<<endl;
	}else{
		cerr<<"Error: The typeInVar144 is not of the same type as typeInVar144."<<endl;
		iReturn++;
	}

	if ( ! typeInVar144.equalElementType( typeProperty ) ){
	
		cout<<"The typeInVar144 is not of the same type as typeProperty. "<<endl;
	}else{
		cerr<<"Error: The typeInVar144 is of the same type as typeProperty."<<endl;
		iReturn++;
	}

	if ( ! typeInVar144.equalElementType( typeDimension1D3 ) ){
	
		cout<<"The typeInVar144 is not of the same type as typeDimension1D3. "<<endl;
	}else{
		cerr<<"Error: The typeInVar144 is of the same type as typeDimension1D3."<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests a in the xml -format stored cDomainVector with
 * cDomainNaturalNumberBit domains.
 *
 * @param szFilename the name of the file wher the cDomainNaturalNumberBit is stored
 * @param uiInVarNumber the number of the input variable for the type
 * @param bHasDomain if true the domain is stored to the type
 * @param uiBits a vector with the bits the cDomainNaturalNumberBit
 * 	domains have
 * @param dScalingfactor a vector with the scalingfactors for the
 * 	cDomainNaturalNumberBit domains have
 * @return the number of errors occured in the test
 */
int testXmlType( const string szFilename, unsigned int uiInVarNumber,
		bool bHasDomain, unsigned int uiBits, double dScalingfactor ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored type:"<<endl;
	
	TiXmlDocument xmlDocType( szFilename );
	bool loadOkay = xmlDocType.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the type was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocType );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlRootHandle( 0 );

	pXmlElement = xmlHandle.FirstChildElement().Element();
	
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();

		if ( szElementName == "inVar" ){
			cout<<"The root element is correctly named \"inVar\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"inVar\"."<<endl;
			iReturn++;
		}
		
		int iNumberOfInVarLoaded = 0;
		const char * pcAttributNumber = pXmlElement->Attribute( "number",
			&iNumberOfInVarLoaded );
		
		if ( pcAttributNumber == NULL ){
			cerr<<"Error: The type has no attribute \"number\"."<<endl;
			iReturn++;
		}else if ( iNumberOfInVarLoaded == (int)uiInVarNumber ) {
			cout<<"The number of the input variable is correctly \""<<
				uiInVarNumber <<"\". "<<endl;
		}else{
			cerr<<"Error: The number of the input variable is \""<<
				iNumberOfInVarLoaded <<"\", but should be \""<<
				uiInVarNumber <<"\"."<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple input variable type for the 1'th input variable"<<endl;

	unsigned int uiNumberInVar = 1;
	cout<<"cTypeInVar typeInVar1( "<< uiNumberInVar <<" );"<<endl;
	cTypeInVar typeInVar1( uiNumberInVar );

	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeInVar1.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeInVar1.storeXml( *fileXml );"<<endl;
	bool bStoreSuccesfull = typeInVar1.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, uiNumberInVar, false,
		0, 0.0 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a 5'th input variable type with a domain"<<endl;

	uiNumberInVar = 5;
	cout<<"cTypeInVar typeInVar5( "<< uiNumberInVar <<" );"<<endl;
	cTypeInVar typeInVar5( uiNumberInVar );

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB4( 4 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB4( 4 );
	unsigned int uiBits = 4;
	double dScalingfactor = 1.0;

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeInVar5.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeInVar5.storeXml( *fileXml, &domainNaturalNumberB4 );"<<endl;
	bStoreSuccesfull = typeInVar5.storeXml( *fileXml, &domainNaturalNumberB4 );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, uiNumberInVar, true,
		uiBits, dScalingfactor );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a 34'th input variable type with a domain"<<endl;

	uiNumberInVar = 34;
	cout<<"cTypeInVar typeInVar34( "<< uiNumberInVar <<" );"<<endl;
	cTypeInVar typeInVar34( uiNumberInVar );

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB13( 13, 1.24 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB13(  13, 1.24 );
	uiBits = 13;
	dScalingfactor = 1.24;

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeInVar34.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeInVar34.storeXml( *fileXml, &domainNaturalNumberB13 );"<<endl;
	bStoreSuccesfull = typeInVar34.storeXml( *fileXml, &domainNaturalNumberB13 );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, uiNumberInVar, true,
		uiBits, dScalingfactor );


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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple input variable type for the 1'th input variable"<<endl;
	
	cout<<"cTypeInVar typeInVar1( 1 );"<<endl;
	cTypeInVar typeInVar1( 1 );

	//test get compressed size
	unsigned int uiCompressedSize = 8 + 8;
	if ( (unsigned int)(typeInVar1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeInVar1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeInVar1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = typeInVar1.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cTypeInVar1[] = { (char)0x2A,
		(char)0x01, //number of the input variable
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeInVar1, 3 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a input variable type for the 10000'th input variable"<<endl;
	
	cout<<"cTypeInVar typeInVar10000( 10000 );"<<endl;
	cTypeInVar typeInVar10000( 10000 );

	//test get compressed size
	uiCompressedSize = 8 + 64;
	if ( (unsigned int)(typeInVar10000.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeInVar10000.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeInVar10000.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeInVar10000.store( *pFile, cRestBit, cNumberOfRestBit );
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
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeInVar10000[] = { (char)0x2C,
		(char)0x10, (char)0x27, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, //number of the input variable
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeInVar10000, 10 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a 5'th input variable type with 5 restbitsbits"<<endl;
	
	cout<<"cTypeInVar typeInVar5( 5 );"<<endl;
	cTypeInVar typeInVar5( 5 );

	//test get compressed size
	uiCompressedSize = 8 + 8;
	if ( (unsigned int)(typeInVar5.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeInVar5.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeInVar5.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x08;
	cNumberOfRestBit = 5;
	bStoreSuccesfull = typeInVar5.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	if ( ( ucRestBit == (unsigned char)((char)0x00) ) && ( cNumberOfRestBit == 5 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x00 and number of restbit should be 5. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeInVar5[] = { (char)0x48, (char)0xA5,
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeInVar5, 3 );


	return iReturn;
}




