/**
 * @file tVectorProperty
 * file name: tVectorProperty.cpp
 * @author Betti Oesterholz
 * @date 16.11.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class tVectorProperty.
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
 * This file contains the test for the class tVectorProperty,
 * which represents the vector for properties.
 *
 *
 *
 *  What's tested of class cVectorProperty:
 * 	- cVectorProperty( unsignedIntFib uiPropertyType, cFibElement & definingPointElement );
 * 	- cVectorProperty( const cVectorProperty & vector, cFibElement * definingFibElement = NULL );
 * 	- cVectorProperty( unsignedIntFib uiPropertyType, unsignedIntFib iNumberOfElements, cFibElement *pDefiningPropertyElement=NULL );
 * 	- cVectorProperty( const cTypeProperty & typeProperty );
 * 	- getElementType()
 * 	- getNumberOfElements()
 * 	- getVectorType()
 * 	- getDomain()
 * 	- getDomain(i=1..n)
 * 	- getStandardDomain()
 * 	- getDefiningFibElement()
 * 	- setDefiningFibElement( cFibElement *fibElement, bool bCheckDomains )
 * 	- isVariable(i=1..n)
 * 	- bool isUsedVariable( const cFibVariable * pVariable ) const
 * 	- set<cFibVariable*> getUsedVariables()
 * 	- setValue(i=1..n)
 * 	- getValue(i=1..n)
 * 	- setVariable(i=1..n)
 * 	- getVariable(i=1..n)
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- equal()
 * 	- operator==()
 * 	- operator=( const cFibVector &vector ) 
 * 	- createInstance( unsignedIntFib iNumberOfElements=2, cFibElement *definingPropertyElement=NULL )
 * 	- storeXml()
 * 	- store()
 * 	- unsignedLongFib getCompressedSize() const
 * 	- intFib getPropertyType() const;
 *
 */
/*
History:
16.11.2009  Oesterholz  created
03.12.2009  Oesterholz  setDefiningFibElement(): new testcases, the vectorsize will be adapted to the domain;
	new tests for: isUsedVariable(), replaceVariable(), store(), getCompressedSize(), getUsedVariables();
	test for storeXml() adapted no undefined elements anymore
27.12.2009  Oesterholz  using function (tCompareBits:)compareDoubleFib() for comparing doubles from restored xml
20.02.2011  Oesterholz  sscanf() reads long long "%lld" instead of long
04.04.2011  Oesterholz  storing to binary stream
29.04.2011  Oesterholz  sscanf() "%lld" for windows to "%I64d"
06.06.2011  Oesterholz  number atribute in XML-vector is now optional
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/


#include "version.h"

#include "cVectorProperty.h"
#include "cVectorPosition.h"
#include "cVectorArea.h"
#include "cTypeProperty.h"
#include "cTypeVariable.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cRoot.h"
#include "cPoint.h"
#include "cProperty.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif


using namespace fib;
using namespace std;


int testCostructor( unsigned long &ulTestphase );
int testDomain( unsigned long &ulTestphase );
int testGetSetDefiningElement( unsigned long &ulTestphase );
int testVectorElements( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testCreateInstance( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );
int testAssignment( unsigned long &ulTestphase );



int testCompareTwoEqualVectors( const cFibVector & vector1, const string & szNameVector1,
	const cFibVector & vector2, const string & szNameVector2 );
int testCompareTwoNotEqualVectors( const cFibVector & vector1, const string & szNameVector1,
	const cFibVector & vector2, const string & szNameVector2 );



int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cVectorProperty methods"<<endl;
	cout<<      "========================================"<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testDomain( ulTestphase );
	iReturn += testGetSetDefiningElement( ulTestphase );
	iReturn += testVectorElements( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCreateInstance( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testAssignment( ulTestphase );


	if ( iReturn==0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * This method tests the constructors and the getNumberOfDimension()
 * and getType() method of the cVectorProperty class.
 *
 * methods tested:
 * 	- cVectorProperty( intFib iPropertyType, cFibElement & definingPointElement );
 * 	- cVectorProperty( intFib iPropertyType, unsignedIntFib iNumberOfElements , cFibElement *pDefiningPropertyElement=NULL );
 * 	- cVectorProperty( const cVectorProperty & vector, cFibElement * definingFibElement = NULL );
 * 	- cVectorProperty( const cTypeProperty & typeProperty );
 * 	- getElementType()
 * 	- getNumberOfElements()
 * 	- isVariable(i=1..n)==false
 * 	- getValue(i=1..n)==0
 * 	- getDomain()
 * 	- getElementType()
 * 	- getDefiningFibElement()
 * 	- getVectorType()
 * 	- intFib getPropertyType() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

//TODO test constructor with correct domain

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cVectorProperty"<<endl;

	cout<<"cTypeProperty typeProperty1( 1 );"<<endl;
	cTypeProperty typeProperty1( 1 );
	
	cout<<"cVectorProperty vecProperty( 1 );"<<endl;
	cVectorProperty vecProperty( 1 );


	//check the getVectorType() methode from cVectorProperty
	if ( vecProperty.getVectorType() == "property.colorRGB" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorRGB\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecProperty.getVectorType()<<" but should be \"property.colorRGB\" ."<<endl;
		iReturn++;
	}
	//check the getPropertyType() methode from cVectorProperty
	if ( vecProperty.getPropertyType() == 1 ){
	
		cout<<"The type of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecProperty.getPropertyType()<<" but should be 1 ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorProperty
	cTypeElement * pTypeProperty = vecProperty.getElementType();
	if ( typeProperty1 == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to typeProperty1. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to typeProperty1 ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecProperty.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the propertyvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecProperty.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecProperty.getNumberOfElements(); 
			uiActualElement++ ){
		
		if ( ! vecProperty.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecProperty.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vecProperty.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the propertyvector."<<endl;
		iReturn++;
	}

	//check the getDomain() methode from cVectorProperty
	if ( vecProperty.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the propertyvector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorProperty for colorSW"<<endl;

	cout<<"cTypeProperty typeProperty2( 2 );"<<endl;
	cTypeProperty typeProperty2( 2 );
	
	cout<<"cVectorProperty vecProperty2( 2 );"<<endl;
	cVectorProperty vecProperty2( 2 );


	//check the getVectorType() methode from cVectorProperty
	if ( vecProperty2.getVectorType() == "property.colorSW" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorSW\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecProperty2.getVectorType()<<" but should be \"property.colorSW\" ."<<endl;
		iReturn++;
	}
	if ( vecProperty2.getPropertyType() == 2 ){
	
		cout<<"The type of the propertyvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecProperty2.getPropertyType()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecProperty2.getElementType();
	if ( typeProperty2 == typeProperty2 ){
	
		cout<<"The type of the propertyvector is correctly equal to typeProperty2. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to typeProperty2 ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecProperty2.getNumberOfElements() == (unsignedIntFib)(1) ){
	
		cout<<"The number of elements of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecProperty2.getNumberOfElements()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecProperty2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecProperty.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecProperty2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vecProperty2.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty2.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vecProperty2.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the propertyvector."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorProperty with 3 dimensions and an defining element"<<endl;

	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;

	cout<<"cRoot rootColorRgb;"<<flush<<endl;
	cRoot rootColorRgb;
	
	cout<<"cTypeProperty testTypePropertyColorRgb( cTypeProperty::COLOR_RGB );"<<endl;
	cTypeProperty testTypePropertyColorRgb( cTypeProperty::COLOR_RGB );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3( 3 );
	cout<<"vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE3( vecDomainsE3 );"<<endl;
	cDomainVector vectorDomainE3( vecDomainsE3 );
	delete vecDomainsE3[ 0 ];
	delete vecDomainsE3[ 1 ];
	delete vecDomainsE3[ 2 ];

	cout<<"rootColorRgb.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainE3);"<<endl;
	rootColorRgb.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainE3);

	
	cout<<"cVectorProperty vecProperty1RootColorRgb1( 1, &rootColorRgb );"<<endl;
	cVectorProperty vecProperty1RootColorRgb1( 1, &rootColorRgb );


	//check the getVectorType() methode from cVectorProperty
	if ( vecProperty1RootColorRgb1.getVectorType() == "property.colorRGB" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorRGB\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecProperty1RootColorRgb1.getVectorType()<<" but should be \"property.colorRGB\" ."<<endl;
		iReturn++;
	}
	if ( vecProperty1RootColorRgb1.getPropertyType() == 1 ){
	
		cout<<"The type of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecProperty1RootColorRgb1.getPropertyType()<<" but should be 1 ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecProperty1RootColorRgb1.getElementType();
	if ( testTypePropertyColorRgb == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertyColorRgb. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertyColorRgb ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecProperty1RootColorRgb1.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the propertyvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecProperty1RootColorRgb1.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecProperty1RootColorRgb1.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecProperty1RootColorRgb1.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecProperty1RootColorRgb1.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vecProperty1RootColorRgb1.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty1RootColorRgb1.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &rootColorRgb == vecProperty1RootColorRgb1.getDefiningFibElement() ){
	
		cout<<"The rootColorRgb is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The rootColorRgb is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vecProperty1RootColorRgb1.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the propertyvector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3 == (*(vecProperty1RootColorRgb1.getDomain())) ){
	
		cout<<"The vectorDomainE3 is the domain for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the propertyvector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorProperty with an empty root element"<<endl;

	cout<<"cTypeProperty typePropertyRgbStandard( 1 );"<<endl;
	cTypeProperty typePropertyRgbStandard( 1 );
	
	cout<<"cVectorProperty vecProperty1RE( 1, &emptyRoot );"<<endl;
	cVectorProperty vecProperty1RE( 1, &emptyRoot );


	//check the getVectorType() methode from cVectorProperty
	if ( vecProperty1RE.getVectorType() == "property.colorRGB" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorRGB\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecProperty1RE.getVectorType()<<" but should be \"property.colorRGB\" ."<<endl;
		iReturn++;
	}
	if ( vecProperty1RE.getPropertyType() == 1 ){
	
		cout<<"The type of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecProperty1RE.getPropertyType()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecProperty1RE.getElementType();
	if ( typePropertyRgbStandard == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to typePropertyRgbStandard. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to typePropertyRgbStandard ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecProperty1RE.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the propertyvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecProperty1RE.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecProperty1RE.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecProperty1RE.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecProperty1RE.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vecProperty1RE.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty1RE.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &emptyRoot == vecProperty1RE.getDefiningFibElement() ){
	
		cout<<"The rootColorRgb is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The rootColorRgb is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vecProperty1RE.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the propertyvector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the propertyvector."<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorProperty with the rootColorRgb root element"<<endl;
	
	cout<<"cVectorProperty vecProperty1RootColorRgb( 1, &rootColorRgb );"<<endl;
	cVectorProperty vecProperty1RootColorRgb( 1, &rootColorRgb );

	//check the getVectorType() methode from cVectorProperty
	if ( vecProperty1RootColorRgb.getVectorType() == "property.colorRGB" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorRGB\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecProperty1RootColorRgb.getVectorType()<<" but should be \"property.colorRGB\" ."<<endl;
		iReturn++;
	}
	if ( vecProperty1RootColorRgb.getPropertyType() == 1 ){
	
		cout<<"The type of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecProperty1RootColorRgb.getPropertyType()<<" but should be 1 ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecProperty1RootColorRgb.getElementType();
	if ( testTypePropertyColorRgb == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertyColorRgb. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertyColorRgb ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecProperty1RootColorRgb.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the propertyvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecProperty1RootColorRgb.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecProperty1RootColorRgb.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecProperty1RootColorRgb.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecProperty1RootColorRgb.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vecProperty1RootColorRgb.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty1RootColorRgb.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &rootColorRgb == vecProperty1RootColorRgb.getDefiningFibElement() ){
	
		cout<<"The rootColorRgb is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The rootColorRgb is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vecProperty1RootColorRgb.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the propertyvector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3 == (*(vecProperty1RootColorRgb.getDomain())) ){
	
		cout<<"The vectorDomainE3 is the domain for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the propertyvector."<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorProperty with the rootD3 root element"<<endl;
	
	cout<<"cRoot rootD3;"<<flush<<endl;
	cRoot rootD3;
	
	cout<<"cTypeProperty testTypePropertyLayer( cTypeProperty::LAYER );"<<endl;
	cTypeProperty testTypePropertyLayer( cTypeProperty::LAYER );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1( 1 );
	cout<<"vecDomainsE1[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomainE1( vecDomainsE1 );"<<endl;
	cDomainVector vectorDomainE1( vecDomainsE1 );
	delete vecDomainsE1[ 0 ];

	cout<<"rootD3.getDomains()->addDomain( testTypePropertyLayer, &vectorDomainE1 );"<<endl;
	rootD3.getDomains()->addDomain( testTypePropertyLayer, &vectorDomainE1 );

	cout<<"cVectorProperty vecPropertyLayerRD3( cTypeProperty::LAYER, &rootD3 );"<<endl;
	cVectorProperty vecPropertyLayerRD3( cTypeProperty::LAYER, &rootD3 );

	//check the getVectorType() methode from cVectorProperty
	if ( vecPropertyLayerRD3.getVectorType() == "property.layer" ){
	
		cout<<"The name of the propertyvector is correctly \"property.layer\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecPropertyLayerRD3.getVectorType()<<" but should be \"property.layer\" ."<<endl;
		iReturn++;
	}
	if ( (unsignedIntFib)(vecPropertyLayerRD3.getPropertyType()) == cTypeProperty::LAYER ){
	
		cout<<"The type of the propertyvector is correctly LAYER . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecPropertyLayerRD3.getPropertyType()<<" but should be LAYER ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecPropertyLayerRD3.getElementType();
	if ( testTypePropertyLayer == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertyLayer. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertyLayer ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecPropertyLayerRD3.getNumberOfElements() == (unsignedIntFib)(1) ){
	
		cout<<"The number of elements of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecPropertyLayerRD3.getNumberOfElements()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecPropertyLayerRD3.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecPropertyLayerRD3.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecPropertyLayerRD3.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vecPropertyLayerRD3.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecPropertyLayerRD3.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &rootD3 == vecPropertyLayerRD3.getDefiningFibElement() ){
	
		cout<<"The rootD3 is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The rootD3 is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vecPropertyLayerRD3.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE1 == vecPropertyLayerRD3.getDomain() ){
	
		cout<<"The vectorDomainE1 is the domain for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1 is not the domain for the propertyvector."<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorProperty by copying vecPropertyLayerRD3"<<endl;
	
	cout<<"cVectorProperty vecPropertyLayerRD3Copy( vecPropertyLayerRD3 );"<<endl;
	cVectorProperty vecPropertyLayerRD3Copy( vecPropertyLayerRD3 );

	//check the getVectorType() methode from cVectorProperty
	if ( vecPropertyLayerRD3Copy.getVectorType() == "property.layer" ){
	
		cout<<"The name of the propertyvector is correctly \"property.layer\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecPropertyLayerRD3Copy.getVectorType()<<" but should be \"property.layer\" ."<<endl;
		iReturn++;
	}
	if ( (unsignedIntFib)(vecPropertyLayerRD3Copy.getPropertyType()) == cTypeProperty::LAYER ){
	
		cout<<"The type of the propertyvector is correctly LAYER . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecPropertyLayerRD3Copy.getPropertyType()<<" but should be LAYER ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecPropertyLayerRD3Copy.getElementType();
	if ( testTypePropertyLayer == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertyLayer. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertyLayer ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecPropertyLayerRD3Copy.getNumberOfElements() == (unsignedIntFib)(1) ){
	
		cout<<"The number of elements of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecPropertyLayerRD3Copy.getNumberOfElements()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecPropertyLayerRD3Copy.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecPropertyLayerRD3Copy.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecPropertyLayerRD3Copy.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<< vecPropertyLayerRD3Copy.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecPropertyLayerRD3Copy.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &rootD3 == vecPropertyLayerRD3Copy.getDefiningFibElement() ){
	
		cout<<"The rootD3 is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The rootD3 is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vecPropertyLayerRD3Copy.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE1 == vecPropertyLayerRD3Copy.getDomain() ){
	
		cout<<"The vectorDomainE1 is the domain for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1 is not the domain for the propertyvector."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorProperty by copying vecPropertyLayerRD3 and givin rootColorRgb as an defining element"<<endl;
	
	cout<<"cVectorProperty vecPropertyLayerRD3Copy2 = cVectorProperty( vecPropertyLayerRD3, &rootColorRgb );"<<endl;
	cVectorProperty vecPropertyLayerRD3Copy2 = cVectorProperty( vecPropertyLayerRD3, &rootColorRgb );

	//check the getVectorType() methode from cVectorProperty
	if ( vecPropertyLayerRD3Copy2.getVectorType() == "property.layer" ){
	
		cout<<"The name of the propertyvector is correctly \"property.layer\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecPropertyLayerRD3Copy2.getVectorType()<<" but should be \"property.layer\" ."<<endl;
		iReturn++;
	}
	if ( (unsignedIntFib)( vecPropertyLayerRD3Copy2.getPropertyType() ) == cTypeProperty::LAYER ){
	
		cout<<"The type of the propertyvector is correctly LAYER . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecPropertyLayerRD3Copy2.getPropertyType()<<" but should be LAYER ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecPropertyLayerRD3Copy2.getElementType();
	if ( testTypePropertyLayer == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertyColorRgb. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertyColorRgb ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecPropertyLayerRD3Copy2.getNumberOfElements() == (unsignedIntFib)(1) ){
	
		cout<<"The number of elements of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecPropertyLayerRD3Copy2.getNumberOfElements()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecPropertyLayerRD3Copy2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecPropertyLayerRD3Copy2.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecPropertyLayerRD3Copy2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<< vecPropertyLayerRD3Copy2.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecPropertyLayerRD3Copy2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &rootColorRgb == vecPropertyLayerRD3Copy2.getDefiningFibElement() ){
	
		cout<<"The rootColorRgb is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The rootColorRgb is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vecPropertyLayerRD3Copy2.getDomain() == NULL ){
		cout<<"Ther is correctly no domain defined for the propertyvector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain defined for the propertyvector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorProperty by copying vecPropertyLayerRD3 with changed elements"<<endl;
	
	cout<<"rootD3.setNumberOfInputVariables( 2 );"<<endl;
	rootD3.setNumberOfInputVariables( 2 );
	cout<<"cFibVariable * pVariable1 = rootD3.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootD3.getInputVariable( 1 );
	cout<<"cFibVariable * pVariable2 = rootD3.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = rootD3.getInputVariable( 2 );

	cout<<"vecProperty1RootColorRgb.setValue( 1, 1 );"<<endl;
	vecProperty1RootColorRgb.setValue( 1, 1 );
	cout<<"vecProperty1RootColorRgb.setValue( 2, 2 );"<<endl;
	vecProperty1RootColorRgb.setValue( 2, 2 );
	cout<<"vecProperty1RootColorRgb.setVariable( 3, pVariable1 );"<<endl;
	vecProperty1RootColorRgb.setVariable( 3, pVariable1 );
	
	cout<<"cVectorProperty vecProperty1RootColorRgbCopyMod( vecProperty1RootColorRgb );"<<endl;
	cVectorProperty vecProperty1RootColorRgbCopyMod( vecProperty1RootColorRgb );

	//check the getVectorType() methode from cVectorProperty
	if ( vecProperty1RootColorRgbCopyMod.getVectorType() == "property.colorRGB" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorRGB\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecProperty1RootColorRgbCopyMod.getVectorType()<<" but should be \"property.colorRGB\" ."<<endl;
		iReturn++;
	}
	if ( vecProperty1RootColorRgbCopyMod.getPropertyType() == 1 ){
	
		cout<<"The type of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecProperty1RootColorRgbCopyMod.getPropertyType()<<" but should be 1 ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecProperty1RootColorRgbCopyMod.getElementType();
	if ( testTypePropertyColorRgb == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertyColorRgb. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertyColorRgb ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecProperty1RootColorRgbCopyMod.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the propertyvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecProperty1RootColorRgbCopyMod.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
		//check the first vectorelement
	if ( ! vecProperty1RootColorRgbCopyMod.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty1RootColorRgbCopyMod.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is "<<
			vecProperty1RootColorRgbCopyMod.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( ! vecProperty1RootColorRgbCopyMod.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty1RootColorRgbCopyMod.getValue( 2 ) == (doubleFib)(2) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty1RootColorRgbCopyMod.getValue( 2 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecProperty1RootColorRgbCopyMod.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty1RootColorRgbCopyMod.getVariable( 3 ) == pVariable1 ){
	
		cout<<"The 3'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty1RootColorRgbCopyMod.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &rootColorRgb == vecProperty1RootColorRgbCopyMod.getDefiningFibElement() ){
	
		cout<<"The rootColorRgb is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The rootColorRgb is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vecProperty1RootColorRgbCopyMod.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE3 == vecProperty1RootColorRgbCopyMod.getDomain() ){
	
		cout<<"The vectorDomainE3 is the domain for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the propertyvector."<<endl;
		iReturn++;
	}

	
	cout<<endl<<"Testing the original vector vecProperty1RootColorRgb:"<<endl;

	//check the getVectorType() methode from cVectorProperty
	if ( vecProperty1RootColorRgb.getVectorType() == "property.colorRGB" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorRGB\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecProperty1RootColorRgb.getVectorType()<<" but should be \"property.colorRGB\" ."<<endl;
		iReturn++;
	}
	if ( vecProperty1RootColorRgb.getPropertyType() == 1 ){
	
		cout<<"The type of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecProperty1RootColorRgb.getPropertyType()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecProperty1RootColorRgb.getElementType();
	if ( testTypePropertyColorRgb == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertyColorRgb. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertyColorRgb ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecProperty1RootColorRgb.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the propertyvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecProperty1RootColorRgb.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
		//check the first vectorelement
	if ( ! vecProperty1RootColorRgb.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty1RootColorRgb.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is "<<
			vecProperty1RootColorRgb.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( ! vecProperty1RootColorRgb.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty1RootColorRgb.getValue( 2 ) == (doubleFib)(2) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty1RootColorRgb.getValue( 2 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecProperty1RootColorRgb.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty1RootColorRgb.getVariable( 3 ) == pVariable1 ){
	
		cout<<"The 3'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty1RootColorRgb.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &rootColorRgb == vecProperty1RootColorRgb.getDefiningFibElement() ){
	
		cout<<"The rootColorRgb is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The rootColorRgb is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vecProperty1RootColorRgb.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE3 == vecProperty1RootColorRgb.getDomain() ){
	
		cout<<"The vectorDomainE3 is the domain for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the propertyvector."<<endl;
		iReturn++;
	}

	cout<<endl<<"Changing vecProperty1RootColorRgb should not change the copy:"<<endl;


	cout<<"vecProperty1RootColorRgb.setVariable( 1, pVariable2 );"<<endl;
	vecProperty1RootColorRgb.setVariable( 1, pVariable2 );
	

	cout<<"vecProperty1RootColorRgb.setValue( 2, 1 );"<<endl;
	vecProperty1RootColorRgb.setValue( 2, 1 );
	cout<<"vecProperty1RootColorRgb.setValue( 3, 2 );"<<endl;
	vecProperty1RootColorRgb.setValue( 3, 2 );


	cout<<endl<<"Testing the copied vector vecProperty1RootColorRgbCopyMod for changed values:"<<endl;
	
	//check the getVectorType() methode from cVectorProperty
	if ( vecProperty1RootColorRgbCopyMod.getVectorType() == "property.colorRGB" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorRGB\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecProperty1RootColorRgbCopyMod.getVectorType()<<" but should be \"property.colorRGB\" ."<<endl;
		iReturn++;
	}
	if ( vecProperty1RootColorRgbCopyMod.getPropertyType() == 1 ){
	
		cout<<"The type of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecProperty1RootColorRgbCopyMod.getPropertyType()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecProperty1RootColorRgbCopyMod.getElementType();
	if ( testTypePropertyColorRgb == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertyLayer. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertyLayer ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecProperty1RootColorRgbCopyMod.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the propertyvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecProperty1RootColorRgbCopyMod.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
		//check the first vectorelement
	if ( ! vecProperty1RootColorRgbCopyMod.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty1RootColorRgbCopyMod.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is "<<
			vecProperty1RootColorRgbCopyMod.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( ! vecProperty1RootColorRgbCopyMod.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty1RootColorRgbCopyMod.getValue( 2 ) == (doubleFib)(2) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty1RootColorRgbCopyMod.getValue( 2 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecProperty1RootColorRgbCopyMod.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty1RootColorRgbCopyMod.getVariable( 3 ) == pVariable1 ){
	
		cout<<"The 3'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty1RootColorRgbCopyMod.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &rootD3 == vecPropertyLayerRD3Copy.getDefiningFibElement() ){
	
		cout<<"The rootD3 is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The rootD3 is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vecProperty1RootColorRgbCopyMod.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE3 == vecProperty1RootColorRgbCopyMod.getDomain() ){
	
		cout<<"The vectorDomainE3 is the domain for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the propertyvector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorProperty for color RGB properties but 2 elements"<<endl;
	
	cout<<"cVectorProperty vecProperty1E2RootColorRgb( 1, 2, &rootColorRgb );"<<endl;
	cVectorProperty vecProperty1E2RootColorRgb( 1, 2, &rootColorRgb );

	//check the getVectorType() methode from cVectorProperty
	if ( vecProperty1E2RootColorRgb.getVectorType() == "property.colorRGB" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorRGB\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecProperty1E2RootColorRgb.getVectorType()<<" but should be \"property.colorRGB\" ."<<endl;
		iReturn++;
	}
	if ( vecProperty1E2RootColorRgb.getPropertyType() == 1 ){
	
		cout<<"The type of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecProperty1E2RootColorRgb.getPropertyType()<<" but should be 1 ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecProperty1E2RootColorRgb.getElementType();
	if ( testTypePropertyColorRgb == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertyColorRgb. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertyColorRgb ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecProperty1E2RootColorRgb.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the propertyvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecProperty1E2RootColorRgb.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecProperty1E2RootColorRgb.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecProperty1E2RootColorRgb.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecProperty1E2RootColorRgb.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vecProperty1E2RootColorRgb.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty1E2RootColorRgb.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &rootColorRgb == vecProperty1E2RootColorRgb.getDefiningFibElement() ){
	
		cout<<"The rootColorRgb is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The rootColorRgb is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vecProperty1E2RootColorRgb.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the propertyvector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3 == (*(vecProperty1E2RootColorRgb.getDomain())) ){
	
		cout<<"The vectorDomainE3 is the domain for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the propertyvector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorProperty for color RGB properties but 5 elements"<<endl;
	
	cout<<"cVectorProperty vecProperty1E5RootColorRgb( 1, 5, &rootColorRgb );"<<endl;
	cVectorProperty vecProperty1E5RootColorRgb( 1, 5, &rootColorRgb );

	//check the getVectorType() methode from cVectorProperty
	if ( vecProperty1E5RootColorRgb.getVectorType() == "property.colorRGB" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorRGB\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecProperty1E5RootColorRgb.getVectorType()<<" but should be \"property.colorRGB\" ."<<endl;
		iReturn++;
	}
	if ( vecProperty1E5RootColorRgb.getPropertyType() == 1 ){
	
		cout<<"The type of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecProperty1E5RootColorRgb.getPropertyType()<<" but should be 1 ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecProperty1E5RootColorRgb.getElementType();
	if ( testTypePropertyColorRgb == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertyColorRgb. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertyColorRgb ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecProperty1E5RootColorRgb.getNumberOfElements() == (unsignedIntFib)(5) ){
	
		cout<<"The number of elements of the propertyvector is correctly 5 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecProperty1E5RootColorRgb.getNumberOfElements()<<" but should be 5 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecProperty1E5RootColorRgb.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecProperty1E5RootColorRgb.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecProperty1E5RootColorRgb.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vecProperty1E5RootColorRgb.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty1E5RootColorRgb.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &rootColorRgb == vecProperty1E5RootColorRgb.getDefiningFibElement() ){
	
		cout<<"The rootColorRgb is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The rootColorRgb is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vecProperty1E5RootColorRgb.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the propertyvector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3 == (*(vecProperty1E5RootColorRgb.getDomain())) ){
	
		cout<<"The vectorDomainE3 is the domain for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the propertyvector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorProperty for SOUND_POLARIZED wher the number of elements coms from the root domain"<<endl;
	
	cout<<"cTypeProperty testTypePropertySoundP( cTypeProperty::SOUND_POLARIZED, 4 );"<<endl;
	cTypeProperty testTypePropertySoundP( cTypeProperty::SOUND_POLARIZED, 4 );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE7( 7 );"<<endl;
	vector<cDomainSingle*> vecDomainsE7( 7 );
	cout<<"vecDomainsE7[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE7[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE7[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE7[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE7[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE7[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE7[ 3 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE7[ 3 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE7[ 4 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE7[ 4 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE7[ 5 ] = new cDomainNaturalNumberBit( 6 );"<<endl;
	vecDomainsE7[ 5 ] = new cDomainNaturalNumberBit( 6 );
	cout<<"vecDomainsE7[ 6 ] = new cDomainNaturalNumberBit( 7 );"<<endl;
	vecDomainsE7[ 6 ] = new cDomainNaturalNumberBit( 7 );
	cout<<"cDomainVector vectorDomainE7( vecDomainsE7 );"<<endl;
	cDomainVector vectorDomainE7( vecDomainsE7 );
	delete vecDomainsE7[ 0 ];
	delete vecDomainsE7[ 1 ];
	delete vecDomainsE7[ 2 ];
	delete vecDomainsE7[ 3 ];
	delete vecDomainsE7[ 4 ];
	delete vecDomainsE7[ 5 ];
	delete vecDomainsE7[ 6 ];

	cout<<"rootColorRgb.getDomains()->addDomain( testTypePropertySoundP, &vectorDomainE7);"<<endl;
	rootColorRgb.getDomains()->addDomain( testTypePropertySoundP, &vectorDomainE7);
	
	cout<<"cVectorProperty vecProperty1E7SoundP( cTypeProperty::SOUND_POLARIZED, &rootColorRgb );"<<endl;
	cVectorProperty vecProperty1E7SoundP( cTypeProperty::SOUND_POLARIZED, &rootColorRgb );

	//check the getVectorType() methode from cVectorProperty
	if ( vecProperty1E7SoundP.getVectorType() == "property.soundPolarized" ){
	
		cout<<"The name of the propertyvector is correctly \"property.soundPolarized\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecProperty1E7SoundP.getVectorType()<<" but should be \"property.soundPolarized\" ."<<endl;
		iReturn++;
	}
	if ( vecProperty1E7SoundP.getPropertyType() == (intFib)(cTypeProperty::SOUND_POLARIZED) ){
	
		cout<<"The type of the propertyvector is correctly "<<
			cTypeProperty::SOUND_POLARIZED<<" . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecProperty1E7SoundP.getPropertyType()<<" but should be "<<
			cTypeProperty::SOUND_POLARIZED<<" ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecProperty1E7SoundP.getElementType();
	if ( testTypePropertySoundP == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertySoundP. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertySoundP ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecProperty1E7SoundP.getNumberOfElements() == (unsignedIntFib)(7) ){
	
		cout<<"The number of elements of the propertyvector is correctly 7 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecProperty1E7SoundP.getNumberOfElements()<<" but should be 7 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecProperty1E7SoundP.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecProperty1E7SoundP.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecProperty1E7SoundP.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vecProperty1E7SoundP.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty1E7SoundP.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &rootColorRgb == vecProperty1E7SoundP.getDefiningFibElement() ){
	
		cout<<"The rootColorRgb is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The rootColorRgb is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vecProperty1E7SoundP.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the propertyvector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE7 == (*(vecProperty1E7SoundP.getDomain())) ){
	
		cout<<"The vectorDomainE7 is the domain for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE7 is not the domain for the propertyvector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorProperty for a given propertytype"<<endl;

	cout<<"cVectorProperty vecPropertyTypeColorRgb( testTypePropertyColorRgb );"<<endl;
	cVectorProperty vecPropertyTypeColorRgb( testTypePropertyColorRgb );


	//check the getVectorType() methode from cVectorProperty
	if ( vecPropertyTypeColorRgb.getVectorType() == "property.colorRGB" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorRGB\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecPropertyTypeColorRgb.getVectorType()<<" but should be \"property.colorRGB\" ."<<endl;
		iReturn++;
	}
	//check the getPropertyType() methode from cVectorProperty
	if ( vecPropertyTypeColorRgb.getPropertyType() == 1 ){
	
		cout<<"The type of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of the propertyvector is "<<
			vecPropertyTypeColorRgb.getPropertyType()<<" but should be 1 ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecPropertyTypeColorRgb.getElementType();
	if ( testTypePropertyColorRgb == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertyColorRgb. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertyColorRgb ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecPropertyTypeColorRgb.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the propertyvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecPropertyTypeColorRgb.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecPropertyTypeColorRgb.getNumberOfElements(); 
			uiActualElement++ ){
		
		if ( ! vecPropertyTypeColorRgb.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecPropertyTypeColorRgb.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vecPropertyTypeColorRgb.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecPropertyTypeColorRgb.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the propertyvector."<<endl;
		iReturn++;
	}

	//check the getDomain() methode from cVectorProperty
	if ( vecPropertyTypeColorRgb.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the propertyvector."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorProperty for a given different propertytype"<<endl;

	cout<<"cVectorProperty vecPropertyTypeLayer( testTypePropertyLayer );"<<endl;
	cVectorProperty vecPropertyTypeLayer( testTypePropertyLayer );

	//check the getVectorType() methode from cVectorProperty
	if ( vecPropertyTypeLayer.getVectorType() == "property.layer" ){
	
		cout<<"The name of the propertyvector is correctly \"property.layer\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vecPropertyTypeLayer.getVectorType()<<" but should be \"property.layer\" ."<<endl;
		iReturn++;
	}

	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vecPropertyTypeLayer.getElementType();
	if ( testTypePropertyLayer == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertyLayer. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertyLayer ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecPropertyTypeLayer.getNumberOfElements() == (unsignedIntFib)(1) ){
	
		cout<<"The number of elements of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecPropertyTypeLayer.getNumberOfElements()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecPropertyTypeLayer.getNumberOfElements(); 
			uiActualElement++ ){
		
		if ( ! vecPropertyTypeLayer.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecPropertyTypeLayer.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vecPropertyTypeLayer.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecPropertyTypeLayer.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the propertyvector."<<endl;
		iReturn++;
	}

	//check the getDomain() methode from cVectorProperty
	if ( vecPropertyTypeLayer.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the propertyvector."<<endl;
		iReturn++;
	}


	return iReturn;
}



/**
 * This method tests the method for the domains of the cVectorProperty class.
 *
 * methods tested:
 * 	- getDomain()
 * 	- getDomain(i=1..n)
 * 	- getStandardDomain()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testDomain( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get Domain methods"<<endl;
	
	cout<<"cRoot rootD3;"<<flush<<endl;
	cRoot rootD3;
	
	cout<<"cTypeProperty testTypePropertyColorRgb( 1 );"<<endl;
	cTypeProperty testTypePropertyColorRgb( 1 );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3( 3 );
	cout<<"vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE3( vecDomainsE3 );"<<endl;
	cDomainVector vectorDomainE3( vecDomainsE3 );
	delete vecDomainsE3[ 0 ];
	delete vecDomainsE3[ 1 ];
	delete vecDomainsE3[ 2 ];
	
	cout<<"rootD3.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainE3 );"<<endl;
	rootD3.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainE3 );

	cout<<"cVectorProperty vecPropertyColorRgbRD3( 1, &rootD3 );"<<endl;
	cVectorProperty vecPropertyColorRgbRD3( 1, &rootD3 );

	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vecPropertyColorRgbRD3.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the propertyvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vecPropertyColorRgbRD3.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the getDomain() methode from cVectorProperty
	if ( vecPropertyColorRgbRD3.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE3 == vecPropertyColorRgbRD3.getDomain() ){
	
		cout<<"The vectorDomainE3 is the domain for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the propertyvector."<<endl;
		iReturn++;
	}

	/*check the getDomain(i=1..n) method of the positionsvektor*/
	//test the getType() method
	cout<<"cDomain * pDomainD3 = vecPropertyColorRgbRD3.getDomain();"<<endl;
	cDomain * pDomainD3 = vecPropertyColorRgbRD3.getDomain();
	if ( pDomainD3->getType() == "DomainVector" ){
	
		cout<<"The type of pDomainD3 is correctly \"DomainVector\". "<<endl;

		cDomainVector * pVectorDomainD3 = (cDomainVector*)pDomainD3;
		
		//test the getNumberOfElements() method
		if ( pVectorDomainD3->getNumberOfElements() == 3 ){
		
			cout<<"The number of elements of pDomainD3 is correctly 3. "<<endl;
			
			//check domains of vector domain elements
			
			cDomainNaturalNumberBit domainNaturalNumberBit1 = cDomainNaturalNumberBit( 1 );
			if ( pVectorDomainD3->getElementDomain( 1 ) == NULL ){
				cerr<<"Error: The first element domain is NULL. "<<endl;
				iReturn++;
			}else if ( (*(pVectorDomainD3->getElementDomain( 1 ))) == domainNaturalNumberBit1 ){
			
				cout<<"The first element domain is correctly an cDomainNaturalNumberBit domain with 1 bits. "<<endl;
			}else{
				cerr<<"Error: The first element domain is not an cDomainNaturalNumberBit domain with 1 bits. "<<endl;
				iReturn++;
			}
	
			cDomainNaturalNumberBit domainNaturalNumberBit2 = cDomainNaturalNumberBit( 2 );
			if ( pVectorDomainD3->getElementDomain( 2 )==NULL ){
				cerr<<"Error: The secound element domain is NULL. "<<endl;
				iReturn++;
			}else if ( (*(pVectorDomainD3->getElementDomain( 2 ))) == domainNaturalNumberBit2 ){
			
				cout<<"The secound element domain is correctly an cDomainNaturalNumberBit domain with 2 bits. "<<endl;
			}else{
				cerr<<"Error: The secound element domain is not an cDomainNaturalNumberBit domain with 2 bits. "<<endl;
				iReturn++;
			}
	
			cDomainNaturalNumberBit domainNaturalNumberBit3 = cDomainNaturalNumberBit( 3 );
			
			if ( pVectorDomainD3->getElementDomain( 3 ) == NULL ){
				cerr<<"Error: The third element domain is NULL. "<<endl;
				iReturn++;
			}else if ( (*(pVectorDomainD3->getElementDomain( 3 ))) == domainNaturalNumberBit3 ){
			
				cout<<"The third element domain is correctly an cDomainNaturalNumberBit domain with 3 bits. "<<endl;
			}else{
				cerr<<"Error: The third element domain is not an cDomainNaturalNumberBit domain with 3 bits. "<<endl;
				iReturn++;
			}
	
			//check bounderies
			if ( pVectorDomainD3->getElementDomain( 0 ) == NULL ){
				cerr<<"The is no 0'th element domain."<<endl;
			}
	
			if ( pVectorDomainD3->getElementDomain( 4 ) == NULL ){
				cerr<<"The is no 4'th element domain."<<endl;
			}
	
	
		}else{
			cerr<<"Error: The number of elements of vectorDomain3 is "<<
				pVectorDomainD3->getNumberOfElements() <<" and not 3 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The type of pDomainD3 is "<<pDomainD3->getType() <<
			" and not \"DomainVector\""<<endl;
		iReturn++;
	}

	//check the getStandardDomain() method from cVectorProperty
	cDomain * pDomainStandardD3 = vecPropertyColorRgbRD3.getStandardDomain();
	cDomain * pTypeDomainStandardD3 = testTypePropertyColorRgb.getStandardDomain();
	
	if ( pDomainStandardD3 == NULL ){
		cerr<<"Error: Ther is no domain defined for the propertyvector."<<endl;
		iReturn++;	
	}else if ( *pDomainStandardD3 == *pTypeDomainStandardD3 ){
	
		cout<<"The vecPropertyLayerRD3 has the correct standard domain. "<<endl;
	}else{
		cerr<<"Error: The vecPropertyLayerRD3 has not the correct standard domain."<<endl;
		iReturn++;
	}

	delete pDomainStandardD3;
	delete pTypeDomainStandardD3;
	
	return iReturn;
}



/**
 * This method tests setDefiningFibElement() and getDefiningFibElement()
 * method of the cVectorProperty class.
 *
 * methods tested:
 * 	- setDefiningFibElement( cFibElement *fibElement, bool bCheckDomains )
 * 	- getDefiningFibElement()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testGetSetDefiningElement( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods"<<endl;

	cout<<"cPoint definingElement1;"<<endl;
	cPoint definingElement1;
	cout<<"cPoint definingElement2;"<<endl;
	cPoint definingElement2;

	cout<<"cVectorProperty vecProperty = cVectorProperty( 1 );"<<endl;
	cVectorProperty vecProperty = cVectorProperty( 1 );

	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the propertyvector."<<endl;
		iReturn++;
	}
	
	cout<<"vecProperty.setDefiningFibElement( &definingElement1 );"<<endl;
	vecProperty.setDefiningFibElement( &definingElement1 );

	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &definingElement1 == vecProperty.getDefiningFibElement() ){
	
		cout<<"The definingElement1 is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The definingElement1 is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}

	cout<<"vecProperty.setDefiningFibElement( &definingElement2 );"<<endl;
	vecProperty.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecProperty.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}

	cout<<"vecProperty.setDefiningFibElement( NULL );"<<endl;
	vecProperty.setDefiningFibElement( NULL );

	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty.getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the propertyvector."<<endl;
		iReturn++;
	}

	cout<<"vecProperty.setDefiningFibElement( &definingElement2 );"<<endl;
	vecProperty.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vecProperty.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecProperty.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods when a domain is given"<<endl;
	
	cout<<"cRoot rootD3;"<<flush<<endl;
	cRoot rootD3;
	
	cout<<"cTypeProperty testTypePropertyColorRgb( cTypeProperty::COLOR_RGB );"<<endl;
	cTypeProperty testTypePropertyColorRgb( cTypeProperty::COLOR_RGB );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainD3( vecDomains3 );"<<endl;
	cDomainVector vectorDomainD3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	cout<<"rootD3.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainD3 );"<<endl;
	rootD3.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainD3 );
	
	cout<<"cVectorProperty vecPropertyE0( cTypeProperty::COLOR_RGB, 0, NULL );"<<endl;
	cVectorProperty vecPropertyE0( cTypeProperty::COLOR_RGB, 0, NULL );
	
	cout<<"vecPropertyE0.setDefiningFibElement( &rootD3 );"<<endl;
	vecPropertyE0.setDefiningFibElement( &rootD3 );

	cout<<"cVectorProperty vecProperty1E3( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecProperty1E3( cTypeProperty::COLOR_RGB );

	if ( vecPropertyE0 == vecProperty1E3 ){
	
		cout<<"The propertievector vecPropertyE0 is equal to vecProperty1E3. "<<endl;
	}else{
		cerr<<"Error: The propertievector vecPropertyE0 is not equal to vecProperty1E3."<<endl;
		iReturn++;
	}

	cout<<"vecProperty1E3.setValue( 1, 1);"<<endl;
	vecProperty1E3.setValue( 1, 1);
	cout<<"vecProperty1E3.setValue( 2, 2);"<<endl;
	vecProperty1E3.setValue( 2, 2);

	cout<<"cVectorProperty vecProperty1E2( cTypeProperty::COLOR_RGB, 2, NULL );"<<endl;
	cVectorProperty vecProperty1E2( cTypeProperty::COLOR_RGB, 2, NULL );
	cout<<"vecProperty1E2.setValue( 1, 3);"<<endl;
	vecProperty1E2.setValue( 1, 3);
	cout<<"vecProperty1E2.setValue( 2, 2);"<<endl;
	vecProperty1E2.setValue( 2, 2);

	cout<<"vecProperty1E2.setDefiningFibElement( &rootD3 );"<<endl;
	vecProperty1E2.setDefiningFibElement( &rootD3 );

	if ( vecProperty1E2 == vecProperty1E3 ){
	
		cout<<"The propertievector vecProperty1E2 is equal to vecProperty1E3. "<<endl;
	}else{
		cerr<<"Error: The propertievector vecProperty1E2 is not equal to vecProperty1E3."<<endl;
		/*check the elements of the propertievektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecProperty1E2.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecProperty1E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"propertievector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"propertievector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecProperty1E2.getValue( uiActualElement ) ==
					vecProperty1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"propertievector is correctly "<< 
					vecProperty1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"propertievector is "<<vecProperty1E2.getValue( uiActualElement )<<
					" and not "<< vecProperty1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}


	cout<<"vecProperty1E3.setValue( 1, 0);"<<endl;
	vecProperty1E3.setValue( 1, 0);
	cout<<"vecProperty1E3.setValue( 2, 1);"<<endl;
	vecProperty1E3.setValue( 2, 1);

	cout<<"cVectorProperty vecProperty2E3( vecProperty1E3 );"<<endl;
	cVectorProperty vecProperty2E3( vecProperty1E3 );

	cout<<"vecProperty2E3.setDefiningFibElement( &rootD3 );"<<endl;
	vecProperty2E3.setDefiningFibElement( &rootD3 );


	if ( vecProperty2E3 == vecProperty1E3 ){
	
		cout<<"The propertievector vecProperty2E3 is equal to vecProperty1E3. "<<endl;
	}else{
		cerr<<"Error: The propertievector vecProperty2E3 is not equal to vecProperty1E3."<<endl;
		/*check the elements of the propertievektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecProperty2E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecProperty2E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"propertievector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"propertievector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecProperty2E3.getValue( uiActualElement ) ==
					vecProperty1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"propertievector is correctly "<< 
					vecProperty1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"propertievector is "<<vecProperty2E3.getValue( uiActualElement )<<
					" and not "<< vecProperty1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	cout<<"vecProperty1E3.setValue( 1, 0);"<<endl;
	vecProperty1E3.setValue( 1, 0);
	cout<<"vecProperty1E3.setValue( 2, 3);"<<endl;
	vecProperty1E3.setValue( 2, 3);
	cout<<"vecProperty1E3.setValue( 3, 7);"<<endl;
	vecProperty1E3.setValue( 3, 7);

	cout<<"cVectorProperty vecProperty3E3( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecProperty3E3( cTypeProperty::COLOR_RGB );
	cout<<"vecProperty3E3.setValue( 1, -7 );"<<endl;
	vecProperty3E3.setValue( 1, -7 );
	cout<<"vecProperty3E3.setValue( 2, 4 );"<<endl;
	vecProperty3E3.setValue( 2, 4 );
	cout<<"vecProperty3E3.setValue( 3, 8 );"<<endl;
	vecProperty3E3.setValue( 3, 8 );

	cout<<"vecProperty3E3.setDefiningFibElement( &rootD3 );"<<endl;
	vecProperty3E3.setDefiningFibElement( &rootD3 );

	if ( vecProperty3E3 == vecProperty1E3 ){
	
		cout<<"The propertievector vecProperty3E3 is equal to vecProperty1E3. "<<endl;
	}else{
		cerr<<"Error: The propertievector vecProperty3E3 is not equal to vecProperty1E3."<<endl;
		/*check the elements of the propertievektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecProperty3E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecProperty3E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"propertievector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"propertievector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecProperty3E3.getValue( uiActualElement ) ==
					vecProperty1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"propertievector is correctly "<< 
					vecProperty1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"propertievector is "<<vecProperty3E3.getValue( uiActualElement )<<
					" and not "<< vecProperty1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods when a domain is given and colorSw property"<<endl;

	cout<<"cVectorProperty vecPropertyColorSwE2( cTypeProperty::COLOR_SW, 2, NULL );"<<endl;
	cVectorProperty vecPropertyColorSwE2( cTypeProperty::COLOR_SW, 2, NULL );
	cout<<"vecPropertyColorSwE2.setValue( 1, 8 );"<<endl;
	vecPropertyColorSwE2.setValue( 1, 8 );
	cout<<"vecPropertyColorSwE2.setValue( 2, 14 );"<<endl;
	vecPropertyColorSwE2.setValue( 2, 14 );
	
	cout<<"vecPropertyColorSwE2.setDefiningFibElement( &rootD3 );"<<endl;
	vecPropertyColorSwE2.setDefiningFibElement( &rootD3 );

	cout<<"cVectorProperty vecPropertyColorSw2E2( cTypeProperty::COLOR_SW, 2, NULL );"<<endl;
	cVectorProperty vecPropertyColorSw2E2( cTypeProperty::COLOR_SW, 2, NULL );
	cout<<"vecPropertyColorSw2E2.setValue( 1, 8 );"<<endl;
	vecPropertyColorSw2E2.setValue( 1, 8 );
	cout<<"vecPropertyColorSw2E2.setValue( 2, 14 );"<<endl;
	vecPropertyColorSw2E2.setValue( 2, 14 );

	if ( vecPropertyColorSwE2 == vecPropertyColorSw2E2 ){
	
		cout<<"The propertievector vecPropertyColorSwE2 is equal to vecPropertyColorSw2E2. "<<endl;
	}else{
		cerr<<"Error: The propertievector vecPropertyColorSwE2 is not equal to vecPropertyColorSw2E2."<<endl;
		iReturn++;
	}

	cout<<"cTypeProperty testTypePropertyColorSw( cTypeProperty::COLOR_SW );"<<endl;
	cTypeProperty testTypePropertyColorSw( cTypeProperty::COLOR_SW );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsD1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsD1( 1 );
	cout<<"vecDomainsD1[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsD1[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainD1( vecDomainsD1 );"<<endl;
	cDomainVector vectorDomainD1( vecDomainsD1 );
	delete vecDomainsD1[ 0 ];

	cout<<"rootD3.getDomains()->addDomain( testTypePropertyColorSw, &vectorDomainD1 );"<<endl;
	rootD3.getDomains()->addDomain( testTypePropertyColorSw, &vectorDomainD1 );

	if ( vecPropertyColorSwE2 == vecPropertyColorSw2E2 ){
	
		cout<<"The propertievector vecPropertyColorSwE2 is equal to vecPropertyColorSw2E2. "<<endl;
	}else{
		cerr<<"Error: The propertievector vecPropertyColorSwE2 is not equal to vecPropertyColorSw2E2."<<endl;
		iReturn++;
	}

	cout<<"vecPropertyColorSwE2.setDefiningFibElement( &rootD3 );"<<endl;
	vecPropertyColorSwE2.setDefiningFibElement( &rootD3 );

	cout<<"cVectorProperty vecPropertyColorSw1E1( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSw1E1( cTypeProperty::COLOR_SW );
	cout<<"vecPropertyColorSw1E1.setValue( 1, 7 );"<<endl;
	vecPropertyColorSw1E1.setValue( 1, 7 );

	if ( vecPropertyColorSwE2 == vecPropertyColorSw1E1 ){
	
		cout<<"The propertievector vecPropertyColorSwE2 is equal to vecPropertyColorSw1E1. "<<endl;
	}else{
		cerr<<"Error: The propertievector vecPropertyColorSwE2 is not equal to vecPropertyColorSw1E1."<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods when a domain is given but shouldn't be checked"<<endl;
	
	cout<<"cVectorProperty vecProperty1E0( cTypeProperty::COLOR_RGB, 0, NULL );"<<endl;
	cVectorProperty vecProperty1E0( cTypeProperty::COLOR_RGB, 0, NULL );
	
	cout<<"cVectorProperty vecProperty2E0( vecProperty1E0 );"<<endl;
	cVectorProperty vecProperty2E0( vecProperty1E0 );
	
	cout<<"vecProperty2E0.setDefiningFibElement( &rootD3, false );"<<endl;
	vecProperty2E0.setDefiningFibElement( &rootD3, false  );

	if ( vecProperty2E0 == vecProperty1E0 ){
	
		cout<<"The propertievector vecProperty2E0 is equal to vecProperty1E0. "<<endl;
	}else{
		cerr<<"Error: The propertievector vecProperty2E0 is not equal to vecProperty1E0."<<endl;
		iReturn++;
	}

	cout<<"cVectorProperty vecProperty2E2( cTypeProperty::COLOR_RGB, 2, NULL );"<<endl;
	cVectorProperty vecProperty2E2( cTypeProperty::COLOR_RGB, 2, NULL );
	cout<<"vecProperty2E2.setValue( 1, 3);"<<endl;
	vecProperty2E2.setValue( 1, 3);
	cout<<"vecProperty2E2.setValue( 2, 2);"<<endl;
	vecProperty2E2.setValue( 2, 2);
	
	cout<<"cVectorProperty vecProperty3E2( vecProperty2E2 );"<<endl;
	cVectorProperty vecProperty3E2( vecProperty2E2 );

	cout<<"vecProperty3E2.setDefiningFibElement( &rootD3, false );"<<endl;
	vecProperty3E2.setDefiningFibElement( &rootD3, false );

	if ( vecProperty3E2 == vecProperty2E2 ){
	
		cout<<"The propertievector vecProperty3E2 is equal to vecProperty2E2. "<<endl;
	}else{
		cerr<<"Error: The propertievector vecProperty3E2 is not equal to vecProperty2E2."<<endl;
		/*check the elements of the propertievektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecProperty3E2.getNumberOfElements() &&
				uiActualElement <= 2;
				uiActualElement++ ){
			
			if ( ! vecProperty3E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"propertievector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"propertievector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecProperty3E2.getValue( uiActualElement ) ==
					vecProperty2E2.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"propertievector is correctly "<< 
					vecProperty2E2.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"propertievector is "<<vecProperty3E2.getValue( uiActualElement )<<
					" and not "<< vecProperty2E2.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	cout<<"cVectorProperty vecProperty4E3( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecProperty4E3( cTypeProperty::COLOR_RGB );
	
	cout<<"vecProperty4E3.setValue( 1, 0);"<<endl;
	vecProperty4E3.setValue( 1, 0);
	cout<<"vecProperty4E3.setValue( 2, -7);"<<endl;
	vecProperty4E3.setValue( 2, -7);

	cout<<"cVectorProperty vecProperty5E3( vecProperty4E3 );"<<endl;
	cVectorProperty vecProperty5E3( vecProperty4E3 );

	cout<<"vecProperty5E3.setDefiningFibElement( &rootD3, false );"<<endl;
	vecProperty5E3.setDefiningFibElement( &rootD3, false );


	if ( vecProperty5E3 == vecProperty4E3 ){
	
		cout<<"The propertievector vecProperty5E3 is equal to vecProperty4E3. "<<endl;
	}else{
		cerr<<"Error: The propertievector vecProperty5E3 is not equal to vecProperty4E3."<<endl;
		/*check the elements of the propertievektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecProperty5E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecProperty5E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"propertievector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"propertievector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecProperty5E3.getValue( uiActualElement ) ==
					vecProperty4E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"propertievector is correctly "<< 
					vecProperty4E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"propertievector is "<<vecProperty5E3.getValue( uiActualElement )<<
					" and not "<< vecProperty4E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	cout<<"cVectorProperty vecProperty6E3( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecProperty6E3( cTypeProperty::COLOR_RGB );
	cout<<"vecProperty6E3.setValue( 1, -7 );"<<endl;
	vecProperty6E3.setValue( 1, -7 );
	cout<<"vecProperty6E3.setValue( 2, 4 );"<<endl;
	vecProperty6E3.setValue( 2, 4 );
	cout<<"vecProperty6E3.setValue( 3, 8 );"<<endl;
	vecProperty6E3.setValue( 3, 8 );

	cout<<"cVectorProperty vecProperty7E3( vecProperty6E3 );"<<endl;
	cVectorProperty vecProperty7E3( vecProperty6E3 );

	cout<<"vecProperty7E3.setDefiningFibElement( &rootD3, false );"<<endl;
	vecProperty7E3.setDefiningFibElement( &rootD3, false );

	if ( vecProperty7E3 == vecProperty6E3 ){
	
		cout<<"The propertievector vecProperty7E3 is equal to vecProperty6E3. "<<endl;
	}else{
		cerr<<"Error: The propertievector vecProperty7E3 is not equal to vecProperty6E3."<<endl;
		/*check the elements of the propertievektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecProperty7E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecProperty7E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"propertievector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"propertievector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecProperty7E3.getValue( uiActualElement ) ==
					vecProperty6E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"propertievector is correctly "<< 
					vecProperty6E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"propertievector is "<<vecProperty7E3.getValue( uiActualElement )<<
					" and not "<< vecProperty6E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods when a domain is given and colorSw property but shouldn't be checked"<<endl;

	cout<<"cVectorProperty vecPropertyColorSw4E2( cTypeProperty::COLOR_SW, 2, NULL );"<<endl;
	cVectorProperty vecPropertyColorSw4E2( cTypeProperty::COLOR_SW, 2, NULL );
	cout<<"vecPropertyColorSw4E2.setValue( 1, 8 );"<<endl;
	vecPropertyColorSw4E2.setValue( 1, 8 );
	cout<<"vecPropertyColorSw4E2.setValue( 2, 14 );"<<endl;
	vecPropertyColorSw4E2.setValue( 2, 14 );
	
	cout<<"cVectorProperty vecPropertyColorSw3E2( vecPropertyColorSw4E2 );"<<endl;
	cVectorProperty vecPropertyColorSw3E2( vecPropertyColorSw4E2 );


	cout<<"vecPropertyColorSw3E2.setDefiningFibElement( &rootD3, false );"<<endl;
	vecPropertyColorSw3E2.setDefiningFibElement( &rootD3, false );

	if ( vecPropertyColorSw3E2 == vecPropertyColorSw4E2 ){
	
		cout<<"The propertievector vecPropertyColorSw3E2 is equal to vecPropertyColorSw4E2. "<<endl;
	}else{
		cerr<<"Error: The propertievector vecPropertyColorSw3E2 is not equal to vecPropertyColorSw4E2."<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests cVectorProperty methods for manipulating the
 * vectorelements.
 *
 * methods tested:
 * 	- setValue()
 * 	- getValue()
 * 	- setVariable()
 * 	- getVariable()
 * 	- isVariable()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testVectorElements( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

//TODO test if yust values of the domain can be set

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing methods for getting the vectorelementdata"<<endl;
	
	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;
	
	cout<<"cVectorProperty vecProperty( 1, &emptyRoot );"<<endl;
	cVectorProperty vecProperty( 1, &emptyRoot );


	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecProperty.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecProperty.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecProperty.getValue( uiActualElement ) == (doubleFib)(0.0) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vecProperty.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
		if ( vecProperty.getVariable( uiActualElement ) == NULL ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly no variable . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable . "<<endl;
			iReturn++;
		}
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setValue() method"<<endl;

	cout<<"vecProperty.setValue( 2, 2.2 )"<<endl;
	if ( vecProperty.setValue( 2, 2.2 ) ){
	
		cout<<"The 2'th element of the propertyvector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecProperty.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"propertyvector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is "<<
			vecProperty.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the propertyvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is an variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecProperty.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 2 ) == (doubleFib)(2.2) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 2.2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty.getValue( 2 )<<" and not 2.2 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the propertyvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is an variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecProperty.setValue( 2, 0.7 )"<<endl;
	if ( vecProperty.setValue( 2, 0.7 ) ){
	
		cout<<"The 2'th element of the propertyvector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecProperty.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"propertyvector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is "<<
			vecProperty.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the propertyvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is an variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecProperty.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the propertyvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is an variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecProperty.setValue( 1, 11 )"<<endl;
	if ( vecProperty.setValue( 1, 11 ) ){
	
		cout<<"The 1'th element of the propertyvector is set. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecProperty.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 1 ) == (doubleFib)(11) ){
	
		cout<<"The 1'th element of the "<<
			"propertyvector is correctly 11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is "<<
			vecProperty.getValue( 1 )<<" and not 11 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the propertyvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is an variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecProperty.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the propertyvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is an variable . "<<endl;
		iReturn++;
	}

	cout<<"vecProperty.setValue( 0, 2.2 )"<<endl;
	if ( ! vecProperty.setValue( 0, 2.2 ) ){
	
		cout<<"The 0'th element of the propertyvector could correctly not set. "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the propertyvector is was set. "<<endl;
		iReturn++;
	}
	cout<<"vecProperty.setValue( 4, 2.2 )"<<endl;
	if ( ! vecProperty.setValue( 4, 2.2 ) ){
	
		cout<<"The 0'th element of the propertyvector could correctly not set. "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the propertyvector is was set. "<<endl;
		iReturn++;
	}
	if ( ! vecProperty.isVariable( 0 ) ){
	
		cout<<"The 0'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 0 ) == (doubleFib)(0.0) ){
	
		cout<<"The 0'th element of the "<<
			"propertyvector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the propertyvector is "<<
			vecProperty.getValue( 2 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 0 ) == NULL ){
	
		cout<<"The 0'th element of the propertyvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the propertyvector is an variable . "<<endl;
		iReturn++;
	}
	if ( ! vecProperty.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 4 ) == (doubleFib)(0.0) ){
	
		cout<<"The 0'th element of the "<<
			"propertyvector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the propertyvector is "<<
			vecProperty.getValue( 4 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 4 ) == NULL ){
	
		cout<<"The 4'th element of the propertyvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the propertyvector is an variable . "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setVariable() method"<<endl;
	
	//creat defined variables to set them later in the vector
	cout<<"emptyRoot.setNumberOfInputVariables( 6 )"<<endl;
	bool bVariableSet = emptyRoot.setNumberOfInputVariables( 6 );
	if ( bVariableSet ){
	
		cout<<"6 variables are set for the root -element. "<<endl;
	}else{
		cerr<<"Error: 6 variables are not set for the root -element. "<<endl;
		iReturn++;
	}
	//check if the variables are created
	for ( unsignedIntFib uiActualVariable = 1;
			uiActualVariable <= emptyRoot.getNumberOfInputVariables();
			uiActualVariable++ ){

		cFibVariable * pVariable = emptyRoot.getInputVariable( uiActualVariable );
		if ( pVariable ){
		
			cout<<"Could get variable "<<uiActualVariable<<
				"'th from the root -element emptyRoot. "<<endl;
		}else{
			cerr<<"Error: Couldn't get variable "<<uiActualVariable<<
				"'th from the root -element emptyRoot.  "<<endl;
			iReturn++;
		}
	}

	cout<<endl<<"pVariable1 = emptyRoot.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = emptyRoot.getInputVariable( 1 );
	cout<<endl<<"vecProperty.setVariable( 1, pVariable1 )"<<endl;
	if ( vecProperty.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the propertyvector is set to the variable 1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not set to the variable 1. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecProperty.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 1 ) == (doubleFib)(0) ){
	
		cout<<"The 1'th element of the "<<
			"propertyvector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is "<<
			vecProperty.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecProperty.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the propertyvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is an variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable1->setValue( 0.11 );"<<endl;
	pVariable1->setValue( 0.11 );
	
	if ( vecProperty.getValue( 1 ) == (doubleFib)(0.11) ){
	
		cout<<"The 1'th element of the "<<
			"propertyvector is correctly 0.11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is "<<
			vecProperty.getValue( 1 )<<" and not 0.11 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable1->setValue( 111 );"<<endl;
	pVariable1->setValue( 111 );
	
	if ( vecProperty.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"propertyvector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is "<<
			vecProperty.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4 = emptyRoot.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable4 = emptyRoot.getInputVariable( 4 );
	cout<<endl<<"vecProperty.setVariable( 2, pVariable4 )"<<endl;
	if ( vecProperty.setVariable( 2, pVariable4 ) ){
	
		cout<<"The 2'th element of the propertyvector is set to the variable 4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not set to the variable 4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecProperty.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"propertyvector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is "<<
			vecProperty.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecProperty.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 2 ) == (doubleFib)(0.0) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty.getValue( 2 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 123 );"<<endl;
	pVariable4->setValue( 123 );
	
	if ( vecProperty.getValue( 2 ) == (doubleFib)(123) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 123 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty.getValue( 2 )<<" and not 123 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 0.321 );"<<endl;
	pVariable4->setValue( 0.321  );
	
	if ( vecProperty.getValue( 2 ) == (doubleFib)(0.321 ) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 0.321  . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty.getValue( 2 )<<" and not 0.321  . "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecProperty.setVariable( 1, pVariable4 )"<<endl;
	if ( vecProperty.setVariable( 1, pVariable4 ) ){
	
		cout<<"The 1'th element of the propertyvector is set to the variable 4. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not set to the variable 4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecProperty.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 1 ) == (doubleFib)(0.321) ){
	
		cout<<"The 1'th element of the "<<
			"propertyvector is correctly 0.321 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is "<<
			vecProperty.getValue( 1 )<<" and not 0.321 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 1 ) == pVariable4 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecProperty.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 2 ) == (doubleFib)(0.321) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 0.321 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty.getValue( 2 )<<" and not 0.321 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 654.123 );"<<endl;
	pVariable4->setValue( 654.123 );
	
	if ( vecProperty.getValue( 1 ) == (doubleFib)(654.123) ){
	
		cout<<"The 1'th element of the "<<
			"propertyvector is correctly 654.123 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is "<<
			vecProperty.getValue( 1 )<<" and not 654.123 . "<<endl;
		iReturn++;
	}
	
	if ( vecProperty.getValue( 2 ) == (doubleFib)(654.123) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 654.123 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty.getValue( 2 )<<" and not 654.123 . "<<endl;
		iReturn++;
	}

	cout<<"vecProperty.setVariable( 0, pVariable4 )"<<endl;
	if ( ! vecProperty.setVariable( 0, pVariable4 ) ){

		cout<<"The 0'th element of the propertyvector could correctly not set to a variable. "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the propertyvector is was set to a variable. "<<endl;
		iReturn++;
	}
	cout<<"vecProperty.setVariable( 4, pVariable4 )"<<endl;
	if ( ! vecProperty.setVariable( 4, pVariable4 ) ){

		cout<<"The 4'th element of the propertyvector could correctly not set to a variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the propertyvector is was set to a variable. "<<endl;
		iReturn++;
	}
	if ( ! vecProperty.isVariable( 0 ) ){
	
		cout<<"The 0'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 0 ) == (doubleFib)(0.0) ){
	
		cout<<"The 0'th element of the "<<
			"propertyvector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the propertyvector is "<<
			vecProperty.getValue( 2 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 0 ) == NULL ){
	
		cout<<"The 0'th element of the propertyvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the propertyvector is an variable . "<<endl;
		iReturn++;
	}
	if ( ! vecProperty.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 4 ) == (doubleFib)(0.0) ){
	
		cout<<"The 0'th element of the "<<
			"propertyvector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 0'th element of the propertyvector is "<<
			vecProperty.getValue( 4 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 4 ) == NULL ){
	
		cout<<"The 4'th element of the propertyvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the propertyvector is an variable . "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setValue() and setVariable() after each other method"<<endl;
	
	cout<<endl<<"vecProperty.setValue( 1, 17 )"<<endl;
	if ( vecProperty.setValue( 1, 17 ) ){
	
		cout<<"The 1'th element of the propertyvector is set to the value 17"<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not set to the value 17. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecProperty.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 1 ) == (doubleFib)(17) ){
	
		cout<<"The 1'th element of the "<<
			"propertyvector is correctly 17 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is "<<
			vecProperty.getValue( 1 )<<" and not 17 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the propertyvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is an variable. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecProperty.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 2 ) == (doubleFib)(654.123 ) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 654.123  . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty.getValue( 2 )<<" and not 654.123  . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 65 );"<<endl;
	pVariable4->setValue( 65 );
	
	if ( vecProperty.getValue( 2 ) == (doubleFib)(65) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty.getValue( 2 )<<" and not 65 . "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecProperty.setVariable( 1, pVariable1 )"<<endl;
	if ( vecProperty.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the propertyvector is set to the varaiable 1"<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not set to the variable 1. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecProperty.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"propertyvector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is "<<
			vecProperty.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecProperty.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 2 ) == (doubleFib)(65 ) ){
	
		cout<<"The 2'th element of the "<<
			"propertyvector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is "<<
			vecProperty.getValue( 2 )<<" and not 65  . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setVariable() methods with trying to set NULL"<<endl;
	
	cout<<endl<<"vecProperty.setVariable( 1, NULL )"<<endl;
	if ( ! vecProperty.setVariable( 1, NULL ) ){
	
		cout<<"The 1'th element of the positionsvector couldn't be set to NULL."<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector could be set to NULL. "<<endl;
		iReturn++;
	}
	cout<<endl<<"vecProperty.setVariable( 2, NULL )"<<endl;
	if ( ! vecProperty.setVariable( 2, NULL ) ){
	
		cout<<"The 2'th element of the positionsvector couldn't be set to NULL."<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector could be set to NULL. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecProperty.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecProperty.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the positionsvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecProperty.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getValue( 2 ) == (doubleFib)(65 ) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecProperty.getValue( 2 )<<" and not 65  . "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the positionsvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing replaceVariable(), isUsedVariable() and getUsedVariables() methods"<<endl;
	
	cout<<endl<<"pVariable2 = emptyRoot.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = emptyRoot.getInputVariable( 2 );
	cout<<endl<<"pVariable3 = emptyRoot.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = emptyRoot.getInputVariable( 3 );
	
	//check vecProperty.isUsedVariable()
	if ( vecProperty.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecProperty.isUsedVariable()
	if ( ! vecProperty.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecProperty.isUsedVariable()
	if ( vecProperty.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	set<cFibVariable*> setCorrectUsedVariables;
	setCorrectUsedVariables.insert( pVariable1 );
	setCorrectUsedVariables.insert( pVariable4 );
	//check getUsedVariables()
	cout<<"setUsedVariables = vecProperty.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = vecProperty.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	cout<<endl<<"vecProperty.replaceVariable( pVariable1, pVariable4 )"<<endl;
	setCorrectUsedVariables.erase( pVariable1 );
	if ( vecProperty.replaceVariable( pVariable1, pVariable4 ) ){
	
		cout<<"The pVariable1 of the propertyvector was replaced with pVariable4. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 of the propertyvector was not replaced with pVariable4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecProperty.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 1 ) == pVariable4 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecProperty.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check vecProperty.isUsedVariable()
	if ( ! vecProperty.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecProperty.isUsedVariable()
	if ( ! vecProperty.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecProperty.isUsedVariable()
	if ( vecProperty.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecProperty.getUsedVariables(); "<<endl;
	setUsedVariables = vecProperty.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	cout<<endl<<"vecProperty.replaceVariable( pVariable1, pVariable3 )"<<endl;
	if ( vecProperty.replaceVariable( pVariable1, pVariable3 ) ){
	
		cout<<"The pVariable1 of the propertyvector was replaced with pVariable3. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 of the propertyvector was not replaced with pVariable3. "<<endl;
		iReturn++;
	}
	//check vecProperty.isUsedVariable()
	if ( ! vecProperty.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecProperty.isUsedVariable()
	if ( vecProperty.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecProperty.getUsedVariables(); "<<endl;
	setUsedVariables = vecProperty.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	
	cout<<endl<<"vecProperty.replaceVariable( pVariable4, pVariable2 )"<<endl;
	setCorrectUsedVariables.erase( pVariable4 );
	setCorrectUsedVariables.insert( pVariable2 );
	if ( vecProperty.replaceVariable( pVariable4, pVariable2 ) ){
	
		cout<<"The pVariable4 of the propertyvector was replaced with pVariable2. "<<endl;
	}else{
		cerr<<"Error: The pVariable4 of the propertyvector was not replaced with pVariable2. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecProperty.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 1 ) == pVariable2 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecProperty.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecProperty.getVariable( 2 ) == pVariable2 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check vecProperty.isUsedVariable()
	if ( ! vecProperty.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecProperty.isUsedVariable()
	if ( vecProperty.isUsedVariable( pVariable2 ) ){
	
		cout<<"The pVariable2 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable2 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecProperty.isUsedVariable()
	if ( ! vecProperty.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecProperty.isUsedVariable()
	if ( ! vecProperty.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable4 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecProperty.getUsedVariables(); "<<endl;
	setUsedVariables = vecProperty.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	//check vecProperty.isUsedVariable()
	if ( ! vecProperty.isUsedVariable( NULL ) ){
	
		cout<<"The NULL is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The NULL is a used varible in the vector.  "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecProperty.replaceVariable( NULL, pVariable2 )"<<endl;
	if ( ! vecProperty.replaceVariable( NULL, pVariable2 ) ){
	
		cout<<"Can't correctly replace NULL of the propertyvector with pVariable2. "<<endl;
	}else{
		cerr<<"Error: Can replace NULL of the propertyvector with pVariable2. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecProperty.replaceVariable( pVariable2, NULL )"<<endl;
	if ( ! vecProperty.replaceVariable( pVariable2, NULL ) ){
	
		cout<<"Can't correctly replace pVariable2 of the propertyvector with NULL. "<<endl;
	}else{
		cerr<<"Error: Can replace pVariable2 of the propertyvector with NULL. "<<endl;
		iReturn++;
	}


	return iReturn;
}


/**
 * This method tests the equal() method and the operator== of two given
 * cFibVectors objects which are equal.
 *
 * @param vector1 the first vector to compare
 * @param szNameVector1 the name of the first vector to compare
 * @param vector2 the secound vector to compare to
 * @param szNameVector2 the name of the secound vector to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualVectors( const cFibVector & vector1, const string & szNameVector1,
	const cFibVector & vector2, const string & szNameVector2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( vector1.equal( vector2 ) ){
	
		cout<<"The "<<szNameVector1<<" is equal to "<<szNameVector2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVector1<<" is not equal to "<<
			szNameVector2<<"."<<endl;
		iReturn++;
	}
	if ( vector1 == vector2 ){
	
		cout<<"The "<<szNameVector1<<" is equal (operator==) to "<<
			szNameVector2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVector1<<" is not equal (operator==) to "<<
			szNameVector2<<"."<<endl;
		iReturn++;
	}
	
	if ( ! (vector1 != vector2) ){
	
		cout<<"The "<<szNameVector1<<" is not not equal (operator!=) to "<<
			szNameVector2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVector1<<" is not equal (operator!=) to "<<
			szNameVector2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}

/**
 * This method tests the equal() method and the operator== of two given
 * cFibVectors objects which are not equal.
 *
 * @param vector1 the first vector to compare
 * @param szNameVector1 the name of the first vector to compare
 * @param vector2 the secound vector to compare to
 * @param szNameVector2 the name of the secound vector to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualVectors( const cFibVector & vector1, const string & szNameVector1,
	const cFibVector & vector2, const string & szNameVector2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! vector1.equal( vector2 ) ){
	
		cout<<"The "<<szNameVector1<<" is not equal to "<<szNameVector2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVector1<<" is equal to "<<
			szNameVector2<<"."<<endl;
		iReturn++;
	}
	if ( ! (vector1 == vector2) ){
	
		cout<<"The "<<szNameVector1<<" is not equal (operator==) to "<<
			szNameVector2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVector1<<" is equal (operator==) to "<<
			szNameVector2<<"."<<endl;
		iReturn++;
	}
	
	if ( vector1 != vector2 ){
	
		cout<<"The "<<szNameVector1<<" is not equal (operator!=) to "<<
			szNameVector2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVector1<<" is equal (operator!=) to "<<
			szNameVector2<<"."<<endl;
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

	cout<<endl<<"creating vectors to compare:"<<endl<<endl;
	
	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;
	
	//creat defined variables to set them later in the vector
	cout<<"emptyRoot.setNumberOfInputVariables( 2 )"<<endl;
	emptyRoot.setNumberOfInputVariables( 2 );

	cout<<"cRoot rootColorRgb;"<<flush<<endl;
	cRoot rootColorRgb;
	
	cout<<"cTypeProperty testTypePropertyColorRgb( 1 );"<<endl;
	cTypeProperty testTypePropertyColorRgb( 1 );

	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3( 3 );
	cout<<"vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainD3( vecDomainsE3 );"<<endl;
	cDomainVector vectorDomainD3( vecDomainsE3 );
	delete vecDomainsE3[ 0 ];
	delete vecDomainsE3[ 1 ];
	delete vecDomainsE3[ 2 ];

	cout<<"rootColorRgb.getDomains()->addDomain( testTypePropertyColorRgb, vectorDomainD3);"<<endl;
	rootColorRgb.getDomains()->addDomain( testTypePropertyColorRgb, vectorDomainD3);

	//creat defined variables to set them later in the vector
	cout<<"rootColorRgb.setNumberOfInputVariables( 4 )"<<endl;
	rootColorRgb.setNumberOfInputVariables( 4 );

	//create cVectorPropertys to compare
	cout<<"cVectorProperty vectorProperty100( 100 );"<<endl;
	cVectorProperty vectorProperty100( 100 );
	cout<<"cVectorProperty vectorProperty100RD2( 100, &rootColorRgb );"<<endl;
	cVectorProperty vectorProperty100RD2( 100, &rootColorRgb );
	
	
	cout<<"cVectorProperty vectorPropertyD3Re( 1, &emptyRoot );"<<endl;
	cVectorProperty vectorPropertyD3Re( 1 ,&emptyRoot );
	cout<<"cVectorProperty vectorPropertyD3RD2( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyD3RD2( 1, &rootColorRgb );
	cout<<"cVectorProperty vectorPropertyRD3( 2, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyRD3( 2, &rootColorRgb );
	
	//vectors with changed values
	cout<<"cVectorProperty vectorPropertyRD3V2g17p2( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyRD3V2g17p2( 1, &rootColorRgb );
	vectorPropertyRD3V2g17p2.setValue( 2, 17.2 );
	
	cout<<"cVectorProperty vectorPropertyD3RD2V2g17p2( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyD3RD2V2g17p2( 1, &rootColorRgb );
	vectorPropertyD3RD2V2g17p2.setValue( 2, 17.2 );

	cout<<"cVectorProperty vectorPropertyD3RD2V2g17p2001( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyD3RD2V2g17p2001( 1, &rootColorRgb );
	vectorPropertyD3RD2V2g17p2001.setValue( 2, 17.2001 );

	cout<<"cVectorProperty vectorPropertyRD2V1g17p2( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyRD2V1g17p2( 1, &rootColorRgb );
	vectorPropertyRD2V1g17p2.setValue( 1, 17.2 );

	cout<<"cVectorProperty vectorPropertyRD2V1g1p1V2gm2p2( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyRD2V1g1p1V2gm2p2( 1, &rootColorRgb );
	vectorPropertyRD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorPropertyRD2V1g1p1V2gm2p2.setValue( 2, -2.2 );

	cout<<"cVectorProperty vectorPropertyD2RD2V1g1p1V2gm2p2( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyD2RD2V1g1p1V2gm2p2( 1, &rootColorRgb );
	vectorPropertyD2RD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorPropertyD2RD2V1g1p1V2gm2p2.setValue( 2, -2.2 );
	
	cout<<"cVectorProperty vectorPropertyRD2V1g1p1V2g2p2( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyRD2V1g1p1V2g2p2( 1, &rootColorRgb );
	vectorPropertyRD2V1g1p1V2g2p2.setValue( 1, 1.1 );
	vectorPropertyRD2V1g1p1V2g2p2.setValue( 2, 2.2 );

	//vectors with variables
	cFibVariable * pVariable1 = rootColorRgb.getInputVariable( 1 );
	cFibVariable * pVariable2 = rootColorRgb.getInputVariable( 2 );
	cFibVariable * pVariable1Re = emptyRoot.getInputVariable( 1 );

	cout<<"cVectorProperty vectorPropertyRD2V1gV1( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyRD2V1gV1( 1, &rootColorRgb );
	vectorPropertyRD2V1gV1.setVariable( 1, pVariable1 );

	cout<<"cVectorProperty vectorPropertyD2RD2V1gV1( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyD2RD2V1gV1( 1, &rootColorRgb );
	vectorPropertyD2RD2V1gV1.setVariable( 1, pVariable1 );

	cout<<"cVectorProperty vectorPropertyRD2V2gV1( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyRD2V2gV1( 1, &rootColorRgb );
	vectorPropertyRD2V2gV1.setVariable( 2, pVariable1 );

	cout<<"cVectorProperty vectorPropertyRD2V2gV2( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyRD2V2gV2( 1, &rootColorRgb );
	vectorPropertyRD2V2gV2.setVariable( 2, pVariable2 );

	cout<<"cVectorProperty vectorPropertyRD2V1gReV1( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyRD2V1gReV1( 1, &rootColorRgb );
	vectorPropertyRD2V1gReV1.setVariable( 1, pVariable1Re );

	//vectors with changed values and variables
	cout<<"cVectorProperty vectorPropertyRD2V1gV1V2g1111( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyRD2V1gV1V2g1111( 1, &rootColorRgb );
	vectorPropertyRD2V1gV1V2g1111.setVariable( 1, pVariable1 );
	vectorPropertyRD2V1gV1V2g1111.setValue( 2, 1111 );

	cout<<"cVectorProperty vectorPropertyD2RD2V1gV1V2g1111( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyD2RD2V1gV1V2g1111( 1, &rootColorRgb );
	vectorPropertyD2RD2V1gV1V2g1111.setVariable( 1, pVariable1 );
	vectorPropertyD2RD2V1gV1V2g1111.setValue( 2, 1111 );

	cout<<"cVectorProperty vectorPropertyRD2V1gV1V2g111( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyRD2V1gV1V2g111( 1, &rootColorRgb );
	vectorPropertyRD2V1gV1V2g111.setVariable( 1, pVariable1 );
	vectorPropertyRD2V1gV1V2g111.setValue( 2, 111 );

	cout<<"cVectorProperty vectorPropertyRD2V1gV2V1g1111( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyRD2V1g111V2gV2( 1, &rootColorRgb );
	vectorPropertyRD2V1g111V2gV2.setVariable( 1, pVariable2 );
	vectorPropertyRD2V1g111V2gV2.setValue( 2, 1111 );

	cout<<"cVectorProperty vectorPropertyD2RD2V1g1111V2gV2( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyD2RD2V1gV2V2g1111( 1, &rootColorRgb );
	vectorPropertyD2RD2V1gV2V2g1111.setValue( 1, 1111 );
	vectorPropertyD2RD2V1gV2V2g1111.setVariable( 2, pVariable1 );

	cout<<"cVectorProperty vectorPropertyD2RD2V1gV1V2gV2( 1, &rootColorRgb );"<<endl;
	cVectorProperty vectorPropertyD2RD2V1gV1V2gV2( 1, &rootColorRgb );
	vectorPropertyD2RD2V1gV1V2gV2.setVariable( 1, pVariable1 );
	vectorPropertyD2RD2V1gV1V2gV2.setVariable( 2, pVariable2 );

	cout<<"cVectorProperty vectorPropertyColorRgbE4( 1, 4 );"<<endl;
	cVectorProperty vectorPropertyColorRgbE4( 1 , 4 );

	cout<<"cVectorPosition vectorPosition( 1 );"<<endl;
	cVectorPosition vectorPosition( 1 );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with vectorPropertyD3
	cFibVector * actualVector = &vectorProperty100;
	string szActualVectorName = "vectorProperty100";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );


	//compare with vectorPropertyD3RD2
	actualVector = &vectorProperty100RD2;
	szActualVectorName = "vectorProperty100RD2";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyD2Re
	actualVector = &vectorPropertyD3Re;
	szActualVectorName = "vectorPropertyD3Re";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyD2RD2
	actualVector = &vectorPropertyD3RD2;
	szActualVectorName = "vectorPropertyD3RD2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyD2Re
	actualVector = &vectorPropertyRD3;
	szActualVectorName = "vectorPropertyRD3";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyRD3V2g17p2
	actualVector = &vectorPropertyRD3V2g17p2;
	szActualVectorName = "vectorPropertyRD3V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyRD3V2g17p2
	actualVector = &vectorPropertyD3RD2V2g17p2;
	szActualVectorName = "vectorPropertyD3RD2V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyD3RD2V2g17p2001
	actualVector = &vectorPropertyD3RD2V2g17p2001;
	szActualVectorName = "vectorPropertyD3RD2V2g17p2001";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyD3RD2V2g17p2001
	actualVector = &vectorPropertyRD2V1g17p2;
	szActualVectorName = "vectorPropertyRD2V1g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyRD2V1g1p1V2gm2p2
	actualVector = &vectorPropertyRD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorPropertyRD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyD2RD2V1g1p1V2gm2p2
	actualVector = &vectorPropertyD2RD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorPropertyD2RD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyD2RD2V1g1p1V2gm2p2
	actualVector = &vectorPropertyRD2V1g1p1V2g2p2;
	szActualVectorName = "vectorPropertyRD2V1g1p1V2g2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyRD2V1gV1
	actualVector = &vectorPropertyRD2V1gV1;
	szActualVectorName = "vectorPropertyRD2V1gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyD2RD2V1gV1
	actualVector = &vectorPropertyD2RD2V1gV1;
	szActualVectorName = "vectorPropertyD2RD2V1gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyRD2V2gV1
	actualVector = &vectorPropertyRD2V2gV1;
	szActualVectorName = "vectorPropertyRD2V2gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyRD2V2gV2
	actualVector = &vectorPropertyRD2V2gV2;
	szActualVectorName = "vectorPropertyRD2V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyRD2V1gReV1
	actualVector = &vectorPropertyRD2V1gReV1;
	szActualVectorName = "vectorPropertyRD2V1gReV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyRD2V1gV1V2g1111
	actualVector = &vectorPropertyRD2V1gV1V2g1111;
	szActualVectorName = "vectorPropertyRD2V1gV1V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyD2RD2V1gV1V2g1111
	actualVector = &vectorPropertyD2RD2V1gV1V2g1111;
	szActualVectorName = "vectorPropertyD2RD2V1gV1V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyRD2V1gV1V2g111
	actualVector = &vectorPropertyRD2V1gV1V2g111;
	szActualVectorName = "vectorPropertyRD2V1gV1V2g111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyRD2V1g111V2gV2
	actualVector = &vectorPropertyRD2V1g111V2gV2;
	szActualVectorName = "vectorPropertyRD2V1g111V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyD2RD2V1gV2V2g1111
	actualVector = &vectorPropertyD2RD2V1gV2V2g1111;
	szActualVectorName = "vectorPropertyD2RD2V1gV2V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorPropertyD2RD2V1gV1V2gV2
	actualVector = &vectorPropertyD2RD2V1gV1V2gV2;
	szActualVectorName = "vectorPropertyD2RD2V1gV1V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorProperty
	actualVector = &vectorPosition;
	szActualVectorName = "vectorPosition";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	//compare with vectorProperty
	actualVector = &vectorPropertyColorRgbE4;
	szActualVectorName = "vectorPropertyColorRgbE4";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100, "vectorProperty100" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty100RD2, "vectorProperty100RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3Re, "vectorPropertyD3Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2, "vectorPropertyD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3, "vectorPropertyRD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD3V2g17p2, "vectorPropertyRD3V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2, "vectorPropertyD3RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD3RD2V2g17p2001, "vectorPropertyD3RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g17p2, "vectorPropertyRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2gm2p2, "vectorPropertyRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1g1p1V2gm2p2, "vectorPropertyD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g1p1V2g2p2, "vectorPropertyRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1, "vectorPropertyRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1, "vectorPropertyD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV1, "vectorPropertyRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V2gV2, "vectorPropertyRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gReV1, "vectorPropertyRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g1111, "vectorPropertyRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2g1111, "vectorPropertyD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1gV1V2g111, "vectorPropertyRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyRD2V1g111V2gV2, "vectorPropertyRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV2V2g1111, "vectorPropertyD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPropertyD2RD2V1gV1V2gV2, "vectorPropertyD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPosition, "vectorPosition" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPropertyColorRgbE4, "vectorPropertyColorRgbE4" );

	return iReturn;
}






/**
 * This method tests the createInstance() method of the cVectorProperty class.
 *
 * methods tested:
 * 	- createInstance()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCreateInstance( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a color -RGB -propertyvector with one element"<<endl;

	cout<<"cRoot rootColorRgb;"<<flush<<endl;
	cRoot rootColorRgb;
	
	cout<<"cTypeProperty typePropertyColorRgb( 1 );"<<endl;
	cTypeProperty typePropertyColorRgb( 1 );
	
	cout<<"cTypeProperty testTypePropertyColorRgb( 1 );"<<endl;
	cTypeProperty testTypePropertyColorRgb( 1 );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3( 3 );
	cout<<"vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainD2( vecDomainsE3 );"<<endl;
	cDomainVector vectorDomainE3( vecDomainsE3 );
	delete vecDomainsE3[ 0 ];
	delete vecDomainsE3[ 1 ];
	delete vecDomainsE3[ 2 ];

	cout<<"rootColorRgb.getDomains()->addDomain( testTypePropertyColorRgb, vectorDomainE3);"<<endl;
	rootColorRgb.getDomains()->addDomain( testTypePropertyColorRgb, vectorDomainE3);

	
	cout<<"cVectorProperty vecProperty1RootColorRgb1( 1, &rootColorRgb );"<<endl;
	cVectorProperty vecProperty1RootColorRgb1( 1, &rootColorRgb );

	cout<<"cFibVector * vectorInstanceColorRgb = vecProperty1RootColorRgb1.createInstance( 1 );"<<endl;
	cFibVector * vectorInstanceColorRgb = vecProperty1RootColorRgb1.createInstance( 1 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorProperty
	if ( vectorInstanceColorRgb->getVectorType() == "property.colorRGB" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorRGB\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vectorInstanceColorRgb->getVectorType()<<" but should be \"property.colorRGB\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorProperty
	cTypeElement * pTypeProperty = vectorInstanceColorRgb->getElementType();
	if ( typePropertyColorRgb == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to typePropertyColorRgb. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to typePropertyColorRgb ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vectorInstanceColorRgb->getNumberOfElements() == (unsignedIntFib)(1) ){
	
		cout<<"The number of elements of the propertyvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vectorInstanceColorRgb->getNumberOfElements()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceColorRgb->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceColorRgb->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceColorRgb->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vectorInstanceColorRgb->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vectorInstanceColorRgb->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the propertyvector."<<endl;
	}else if ( &rootColorRgb == vectorInstanceColorRgb->getDefiningFibElement() ){
	
		cerr<<"Error: The rootColorRgb is the defining element for the propertyvector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is a defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vectorInstanceColorRgb->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the propertyvector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the propertyvector."<<endl;
		iReturn++;
	}
	delete vectorInstanceColorRgb;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 3 elements"<<endl;

	cout<<"cFibVector * vectorInstanceE3 = vecProperty1RootColorRgb1.createInstance( 3 );"<<endl;
	cFibVector * vectorInstanceE3 = vecProperty1RootColorRgb1.createInstance( 3 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorProperty
	if ( vectorInstanceE3->getVectorType() == "property.colorRGB" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorRGB\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vectorInstanceE3->getVectorType()<<" but should be \"property.colorRGB\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vectorInstanceE3->getElementType();
	if ( typePropertyColorRgb == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to typeProperty2. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to typeProperty2 ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vectorInstanceE3->getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the propertyvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vectorInstanceE3->getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceE3->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceE3->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceE3->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vectorInstanceE3->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vectorInstanceE3->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the propertyvector."<<endl;
	}else if ( &rootColorRgb == vectorInstanceE3->getDefiningFibElement() ){
	
		cerr<<"Error: The rootColorRgb is the defining element for the propertyvector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is an defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vectorInstanceE3->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the propertyvector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the propertyvector."<<endl;
		iReturn++;
	}
	delete vectorInstanceE3;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 2 elements and rootD3 as an defining element"<<endl;

	cout<<"cFibVector * vectorInstanceE2RD2 = vecProperty1RootColorRgb1.createInstance( 2, &rootColorRgb );"<<endl;
	cFibVector * vectorInstanceE2RD2 = vecProperty1RootColorRgb1.createInstance( 2, &rootColorRgb );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorProperty
	if ( vectorInstanceE2RD2->getVectorType() == "property.colorRGB" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorRGB\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vectorInstanceE2RD2->getVectorType()<<" but should be \"property.colorRGB\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vectorInstanceE2RD2->getElementType();
	if ( testTypePropertyColorRgb == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertyColorRgb. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertyColorRgb ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vectorInstanceE2RD2->getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the propertyvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vectorInstanceE2RD2->getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceE2RD2->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceE2RD2->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceE2RD2->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vectorInstanceE2RD2->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vectorInstanceE2RD2->getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the propertyvector."<<endl;
		iReturn++;	
	}else if ( &rootColorRgb == vectorInstanceE2RD2->getDefiningFibElement() ){
	
		cout<<"The rootColorRgb is the defining element for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The rootColorRgb is not the defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vectorInstanceE2RD2->getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the propertyvector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3 == (*(vectorInstanceE2RD2->getDomain())) ){
	
		cout<<"The vectorDomainE3 is the domain for the propertyvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3 is not the domain for the propertyvector."<<endl;
		iReturn++;
	}
	delete vectorInstanceE2RD2;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a color -SW -propertyvector with two elements"<<endl;
	
	cout<<"cTypeProperty testTypePropertyColorSW( 2 );"<<endl;
	cTypeProperty testTypePropertyColorSW( 2 );

	cout<<"cVectorProperty vecProperty1RootColorSW( 2, &rootColorRgb );"<<endl;
	cVectorProperty vecProperty1RootColorSW( 2, &rootColorRgb );

	cout<<"cFibVector * vectorInstanceColorSW = vecProperty1RootColorSW.createInstance( 2 );"<<endl;
	cFibVector * vectorInstanceColorSW = vecProperty1RootColorSW.createInstance( 2 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorProperty
	if ( vectorInstanceColorSW->getVectorType() == "property.colorSW" ){
	
		cout<<"The name of the propertyvector is correctly \"property.colorSW\" . "<<endl;
	}else{
		cerr<<"Error: The name of the propertyvector is "<<
			vectorInstanceColorSW->getVectorType()<<" but should be \"property.colorSW\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorProperty
	pTypeProperty = vectorInstanceColorSW->getElementType();
	if ( testTypePropertyColorSW == (*pTypeProperty) ){
	
		cout<<"The type of the propertyvector is correctly equal to testTypePropertyColorSW. "<<endl;
	}else{
		cerr<<"Error: The type of propertyvector not equal to testTypePropertyColorSW ."<<endl;
		iReturn++;
	}
	delete pTypeProperty;
	
	//check the getNumberOfElements() methode from cVectorProperty
	if ( vectorInstanceColorSW->getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the propertyvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the propertyvector is "<<
			vectorInstanceColorSW->getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	//check the elements of the positionsvektor
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceColorSW->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceColorSW->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceColorSW->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"propertyvector is "<<vectorInstanceColorSW->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorProperty
	if ( vectorInstanceColorSW->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the propertyvector."<<endl;
	}else if ( &rootColorRgb == vectorInstanceColorSW->getDefiningFibElement() ){
	
		cerr<<"Error: The rootColorRgb is the defining element for the propertyvector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is a defining element for the propertyvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorProperty
	if ( vectorInstanceColorSW->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the propertyvector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the propertyvector."<<endl;
		iReturn++;
	}
	delete vectorInstanceColorSW;

	return iReturn;
}



/**
 * This method tests a in the xml -format stored cFibVector.
 *
 * @param szFilename the name of the file wher the cFibVector is stored
 * @param szVectorType the name of the type for the vector
 * @param uiVectorElements the number of elements in the vector
 * @param vecElementType a vector with the typs of the vectorelements
 * 	(w=value; v=variable)
 * @param vecValues the values of the vectorelements
 * @return the number of errors occured in the test
 */
int testXmlVector( const string szFilename, const string szVectorType,
		unsigned int uiVectorElements, vector<char> vecElementType,
		vector<double> vecValues ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored vector:"<<endl;
	
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

		if ( szElementName == "vector" ){
			cout<<"The root element is correctly named \"vector\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"vector\"."<<endl;
			iReturn++;
		}
		const char * szVectorXmlType = pXmlElement->Attribute( "type" );
		
		if ( szVectorXmlType == NULL ){
			cerr<<"Error: The vector has no type."<<endl;
			iReturn++;
		}else if ( szVectorType == szVectorXmlType ) {
			cout<<"The type of the vector is correctly \""<< szVectorType <<"\". "<<endl;
		}else{
			cerr<<"Error: The type of the vector is \""<< szVectorXmlType
				<<"\", but should be \""<< szVectorType <<"\"."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	xmlHandleRoot = TiXmlHandle( pXmlElement );
	pXmlElement = xmlHandleRoot.FirstChild().Element();
	
	if ( uiVectorElements != 0 ){
		if ( pXmlElement == NULL ){
			cerr<<"Error: No elements in this vector."<<endl;
			iReturn++;
			return iReturn;
		}
	}else{
		if ( pXmlElement != NULL ){
			cerr<<"Error: Ther are elements in this vector, but it shouldn't hafe some."<<endl;
			iReturn++;
		}
	}
	int iReadedNumberOfElement = 0;
	for( int iNumberOfElement = 1; pXmlElement;
			pXmlElement = pXmlElement->NextSiblingElement(), iNumberOfElement++ ){
	
		string szElementName = pXmlElement->Value();
		
		if ( pXmlElement->Attribute( "number", & iReadedNumberOfElement ) ){
			iNumberOfElement = iReadedNumberOfElement;
			
			cout<<"Reading the "<< iNumberOfElement <<"'th numbert element of the type "<<
				szElementName <<" . "<<endl;
		}else{
			cout<<"Reading the "<< iNumberOfElement <<"'th element of the type "<<
				szElementName <<" . "<<endl;
		}
		
		//the elementtype the actual element should have
		string szTargetElementType( "non" );
		
		if ( iNumberOfElement < 1 ){
			cerr<<"Error: Ther couldn't be a 0'th vectorelement."<<endl;
			iReturn++;
		}else if ( (int)(uiVectorElements) < iNumberOfElement ){
			cerr<<"Error: Ther couldn't be a "<< iNumberOfElement <<
				"'th vectorelement, because the vector has yust "<<
					uiVectorElements <<" elements."<<endl;
			iReturn++;
		}else{
			switch ( vecElementType[ iNumberOfElement-1 ] ){
				case 'w': 
					szTargetElementType = "value";
				break;
				case 'v': 
					szTargetElementType = "variable";
				break;
			}
		}
		
		if ( szTargetElementType != szElementName ){
			cerr<<"Error: The element is of type \""<< szElementName <<
				"\", but should be of the type \""<<  szTargetElementType <<"\"."<<endl;
			iReturn++;
		}
		
		if ( szElementName == "value" ){
			const char * pcValue = pXmlElement->GetText();
			cout<<"The value of the element is: "<< pcValue <<endl;
			//converting value to double
			if ( (1 <= iNumberOfElement) && ( iNumberOfElement <= (int)(uiVectorElements) ) ){
				double dValue1 = 0.0;
				int iReadValues = sscanf ( pcValue, "%lf", & dValue1 );
				
				long long lMantissa = 0;
				long long lExponent = 0;
#ifdef WINDOWS
				sscanf( pcValue, "%I64d * 2^(%I64d", & lMantissa, & lExponent );
#else //WINDOWS
				sscanf( pcValue, "%lld * 2^(%lld", & lMantissa, & lExponent );
#endif //WINDOWS
				
				//mantissa and exponent readed
				double dValue2 = ((doubleFib)lMantissa) * pow( 2.0, (doubleFib)lExponent );

				if ( iReadValues != 0){
					if ( compareDoubleFib(dValue1, vecValues[ iNumberOfElement - 1 ]) ||
							compareDoubleFib(dValue2, vecValues[ iNumberOfElement - 1 ]) ){
						cout<<"The value of the element is correct."<<endl;
					}else{
						cerr<<"Error: The value of the element should be : "<<
							vecValues[ iNumberOfElement - 1 ] <<endl;
						iReturn++;
					}
				}else{
					cerr<<"Error: The element text is not a number."<<endl;
					iReturn++;
				}
			}//else can't compare with a value
		
		}else if ( szElementName == "variable" ){
		
			const char * pcValue = pXmlElement->GetText();
			cout<<"The variablenumber of the element is: "<< pcValue <<endl;
			//converting value to integer
			if ( (1 <= iNumberOfElement) && ( iNumberOfElement <= (int)(uiVectorElements) ) ){
				long lValue;
				int iReadValues = sscanf ( pcValue, "%ld", & lValue );
				if ( iReadValues != 0){
					if ( (double)(lValue) == vecValues[ iNumberOfElement - 1 ] ){
						cout<<"The variablenumber of the element is correct."<<endl;
					}else{
						cerr<<"Error: The variablenumber of the element should be : "<<
							vecValues[ iNumberOfElement - 1 ] <<endl;
						iReturn++;
					}
				}else{
					cerr<<"Error: The element text is not a number."<<endl;
					iReturn++;
				}
			}//else can't compare with a value

		}else{
			cerr<<"Error: Unknown element type."<<endl;
			iReturn++;
		}
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an empty 3 d vector"<<endl;
	
	cout<<"cRoot rootD3;"<<flush<<endl;
	cRoot rootD3;
	
	cout<<"cTypeProperty testTypePropertyColorRgb( 1 );"<<endl;
	cTypeProperty testTypePropertyColorRgb( 1 );

	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3( 3 );
	cout<<"vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE3( vecDomainsE3 );"<<endl;
	cDomainVector vectorDomainE3( vecDomainsE3 );
	delete vecDomainsE3[ 0 ];
	delete vecDomainsE3[ 1 ];
	delete vecDomainsE3[ 2 ];
	
	cout<<"rootD3.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainE3 );"<<endl;
	rootD3.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainE3 );

	//creat defined variables to set them later in the vector
	cout<<"rootD3.setNumberOfInputVariables( 6 )"<<endl;
	rootD3.setNumberOfInputVariables( 6 );

	cout<<"cVectorProperty vecPropertyColorRgb( 1, &rootD3 );"<<endl;
	cVectorProperty vecPropertyColorRgb( 1, &rootD3 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecPropertyColorRgbEmpty.xml" );
	ofstream fileVectorProperty( pFileName );
	
	bool bStoreSuccesfull = vecPropertyColorRgb.storeXml( fileVectorProperty );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	vector<char> vecElementTypePosition( 5, 'w' );
	vector<double> vecValuesPosition( 5, 0.0 );
	
	iReturn += testXmlVector( pFileName, "property.colorRGB",
		3, vecElementTypePosition, vecValuesPosition );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector one value set"<<endl;
	
	cout<<"vecPropertyColorRgb.setValue( 1, 111 )"<<endl;
	vecPropertyColorRgb.setValue( 1, 111 );
	vecElementTypePosition[0] = 'w';
	vecValuesPosition[0] = 111;
	
	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecPropertyColorRgbV1g111.xml" );
	ofstream fileVectorPropertyRD3V1g111n( pFileName );
	
	bStoreSuccesfull = vecPropertyColorRgb.storeXml( fileVectorPropertyRD3V1g111n );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( pFileName, "property.colorRGB",
		3, vecElementTypePosition, vecValuesPosition );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector all value set"<<endl;
	
	cout<<"vecPropertyColorRgb.setValue( 2, 123.456 )"<<endl;
	vecPropertyColorRgb.setValue( 2, 123.456  );
	vecElementTypePosition[1] = 'w';
	vecValuesPosition[1] = 123.456;
	cout<<"vecPropertyColorRgb.setValue( 3, -123.456 )"<<endl;
	vecPropertyColorRgb.setValue( 3, -123.456 );
	vecElementTypePosition[2] = 'w';
	vecValuesPosition[2] = -123.456;

	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorPropertyRD3T3.xml" );
	ofstream fileVectorPropertyRD3T3( pFileName );
	
	bStoreSuccesfull = vecPropertyColorRgb.storeXml( fileVectorPropertyRD3T3 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szFileNameBuffer, "property.colorRGB",
		3, vecElementTypePosition, vecValuesPosition );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector with variables"<<endl;
	
	cout<<"cFibVariable * pVariable1 = rootD3.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootD3.getInputVariable( 1 );
	cout<<"pVariable1->setValue( 1 );"<<endl;
	pVariable1->setValue( 1 );
	cout<<"cFibVariable * pVariable2 = rootD3.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = rootD3.getInputVariable( 2 );
	cout<<"pVariable2->setIntegerValue( 2 );"<<endl;
	pVariable2->setIntegerValue( 2 );
	cout<<"cFibVariable * pVariable3 = rootD3.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = rootD3.getInputVariable( 3 );
	cout<<"pVariable3->setIntegerValue( 3 );"<<endl;
	pVariable3->setIntegerValue( 3 );
	
	cout<<"vecPropertyColorRgb.setVariable( 1, pVariable1 )"<<endl;
	vecPropertyColorRgb.setVariable( 1, pVariable1  );
	vecElementTypePosition[0] = 'v';
	vecValuesPosition[0] = 1;
	cout<<"vecPropertyColorRgb.setVariable( 2, pVariable2 )"<<endl;
	vecPropertyColorRgb.setVariable( 2, pVariable2 );
	vecElementTypePosition[1] = 'v';
	vecValuesPosition[1] = 2;
	cout<<"vecPropertyColorRgb.setVariable( 3, pVariable3 )"<<endl;
	vecPropertyColorRgb.setVariable( 3, pVariable3 );
	vecElementTypePosition[2] = 'v';
	vecValuesPosition[2] = 3;

	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorPropertyRD3T4.xml" );
	ofstream fileVectorPropertyRD3T4( pFileName );
	
	bStoreSuccesfull = vecPropertyColorRgb.storeXml( fileVectorPropertyRD3T4 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( pFileName, "property.colorRGB",
		3, vecElementTypePosition, vecValuesPosition );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector with variables and values"<<endl;
	
	cout<<"vecPropertyColorRgb.setVariable( 1, pVariable1 )"<<endl;
	vecPropertyColorRgb.setVariable( 1, pVariable1  );
	vecElementTypePosition[0] = 'v';
	vecValuesPosition[0] = 1;
	cout<<"vecPropertyColorRgb.setValue( 2, -0.00124 )"<<endl;
	vecPropertyColorRgb.setValue( 2, -0.00124 );
	vecElementTypePosition[1] = 'w';
	vecValuesPosition[1] = -0.00124;
	cout<<"vecPropertyColorRgb.setVariable( 3, pVariable3 )"<<endl;
	vecPropertyColorRgb.setVariable( 3, pVariable3 );
	vecElementTypePosition[2] = 'v';
	vecValuesPosition[2] = 3;

	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorPropertyRD3T5.xml" );
	ofstream fileVectorPropertyRD3T5( pFileName );
	
	bStoreSuccesfull = vecPropertyColorRgb.storeXml( fileVectorPropertyRD3T5 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( pFileName, "property.colorRGB",
		3, vecElementTypePosition, vecValuesPosition );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 5 d vector with variables and values"<<endl;
	
	cout<<"cVectorProperty vecPropertyRD5 ( cTypeProperty::SOUND_POLARIZED, 5 , &rootD3 );"<<endl;
	cVectorProperty vecPropertyRD5( cTypeProperty::SOUND_POLARIZED, 5, &rootD3 );

	cout<<"vecPropertyRD5.setVariable( 1, pVariable1 )"<<endl;
	vecPropertyRD5.setVariable( 1, pVariable1  );
	vecElementTypePosition[0] = 'v';
	vecValuesPosition[0] = 1;
	cout<<"vecPropertyRD5.setValue( 2, -0.00124 )"<<endl;
	vecPropertyRD5.setValue( 2, -0.00124 );
	vecElementTypePosition[1] = 'w';
	vecValuesPosition[1] = -0.00124;
	cout<<"vecPropertyRD5.setVariable( 3, pVariable3 )"<<endl;
	vecPropertyRD5.setVariable( 3, pVariable3 );
	vecElementTypePosition[2] = 'v';
	vecValuesPosition[2] = 3;
	cout<<"vecPropertyRD5.setValue( 4, 1234 )"<<endl;
	vecPropertyRD5.setValue( 4, 1234 );
	vecElementTypePosition[3] = 'w';
	vecValuesPosition[3] = 1234;
	cout<<"vecPropertyRD5.setValue( 5, 123.67 )"<<endl;
	vecPropertyRD5.setValue( 5, 123.67   );
	vecElementTypePosition[4] = 'w';
	vecValuesPosition[4] = 123.67 ;

	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorPropertyRD3T6.xml" );
	ofstream fileVectorPropertyRD3T6( pFileName );
	
	bStoreSuccesfull = vecPropertyRD5.storeXml( fileVectorPropertyRD3T6 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( pFileName, "property.soundPolarized",
		5, vecElementTypePosition, vecValuesPosition );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an colorSW vector with values"<<endl;
	
	cout<<"cVectorProperty vecPropertyColorSw ( cTypeProperty::COLOR_SW , &rootD3 );"<<endl;
	cVectorProperty vecPropertyColorSw( cTypeProperty::COLOR_SW, &rootD3 );

	cout<<"vecPropertyColorSw.setValue( 1, -124 )"<<endl;
	vecPropertyColorSw.setValue( 1, -124 );
	vecElementTypePosition[0] = 'w';
	vecValuesPosition[0] = -124;

	szFileNameBuffer[0] = 0;
	pFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorPropertyColorSw.xml" );
	ofstream fileVectorPropertyColorSw( pFileName );
	
	bStoreSuccesfull = vecPropertyColorSw.storeXml( fileVectorPropertyColorSw );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< pFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< pFileName <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( pFileName, "property.colorSW",
		1, vecElementTypePosition, vecValuesPosition );


	return iReturn;
}


/**
 * This method methods for storing of the class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an propertysvector with 0 elements"<<endl;

	cout<<"cVectorProperty vecPropertyE0( cTypeProperty::COLOR_SW, 0, NULL );"<<endl;
	cVectorProperty vecPropertyE0( cTypeProperty::COLOR_SW, 0, NULL );

	//test get compressed size
	unsigned int uiCompressedSize = 0;
	if ( (unsigned int)(vecPropertyE0.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecPropertyE0.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecPropertyE0.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = vecPropertyE0.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cPropertyE0[] = { (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cPropertyE0, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an propertysvector with 3 elements"<<endl;

	cout<<"cVectorProperty vecProperty1E3Ch( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecProperty1E3Ch( cTypeProperty::COLOR_RGB );
	cout<<"vecProperty1E3Ch.setValue( 1, 4 );"<<endl;
	vecProperty1E3Ch.setValue( 1, 4 );
	cout<<"vecProperty1E3Ch.setValue( 2, 6 );"<<endl;
	vecProperty1E3Ch.setValue( 2, 6 );
	cout<<"vecProperty1E3Ch.setValue( 3, 7 );"<<endl;
	vecProperty1E3Ch.setValue( 3, 7 );

	//test get compressed size
	uiCompressedSize = 3 * 9;
	if ( (unsigned int)(vecProperty1E3Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecProperty1E3Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecProperty1E3Ch.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = vecProperty1E3Ch.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	unsigned char ucRestBit = cRestBit;
	unsigned char ucRestBitCorrect = (char)0x00;
	short sNumberOfRestBitCorrect = 3;
	if ( ( ucRestBit == ucRestBitCorrect ) && ( cNumberOfRestBit == sNumberOfRestBitCorrect ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be "<< (unsigned short)ucRestBitCorrect <<
			" and number of restbit should be "<< sNumberOfRestBitCorrect <<" . "<<endl;
		iReturn++;
	}

	
	//test stored data
	const char cPropertyE3[] = { (char)0x08, (char)0x18, (char)0x38, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cPropertyE3, 4 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an propertysvector with variables"<<endl;

	cout<<"cRoot rootD3;"<<flush<<endl;
	cRoot rootD3;

	cout<<"rootD3.setNumberOfInputVariables( 6 );"<<flush<<endl;
	rootD3.setNumberOfInputVariables( 6 );
	
	cout<<"pVariable1 = rootD3.getInputVariable( 1 );"<<flush<<endl;
	cFibVariable * pVariable1 = rootD3.getInputVariable( 1 );
	cout<<"pVariable2 = rootD3.getInputVariable( 2 );"<<flush<<endl;
	cFibVariable * pVariable2 = rootD3.getInputVariable( 2 );
	cout<<"pVariable3 = rootD3.getInputVariable( 3 );"<<flush<<endl;
	cFibVariable * pVariable3 = rootD3.getInputVariable( 3 );

	cout<<"pVariable1->setValue( 1 );"<<flush<<endl;
	pVariable1->setValue( 1 );
	cout<<"pVariable2->setValue( 2 );"<<flush<<endl;
	pVariable2->setValue( 2 );
	cout<<"pVariable3->setValue( 3 );"<<flush<<endl;
	pVariable3->setValue( 3 );

	cout<<"vecProperty1E3Ch.setVariable( 1, pVariable1);"<<endl;
	vecProperty1E3Ch.setVariable( 1, pVariable1);
	cout<<"vecProperty1E3Ch.setVariable( 2, pVariable2);"<<endl;
	vecProperty1E3Ch.setVariable( 2, pVariable2);
	cout<<"vecProperty1E3Ch.setVariable( 3, pVariable3);"<<endl;
	vecProperty1E3Ch.setVariable( 3, pVariable3);

	//test get compressed size
	uiCompressedSize = 3 * 9;
	if ( (unsigned int)(vecProperty1E3Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecProperty1E3Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecProperty1E3Var.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = vecProperty1E3Ch.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = (char)0x00;
	sNumberOfRestBitCorrect = 3;
	if ( ( ucRestBit == ucRestBitCorrect ) && ( cNumberOfRestBit == sNumberOfRestBitCorrect ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be "<< (unsigned short)ucRestBitCorrect <<
			" and number of restbit should be "<< sNumberOfRestBitCorrect <<" . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cPropertyE3Var[] = { (char)0x03, (char)0x0A, (char)0x1C, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cPropertyE3Var, 4 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an propertysvector with domains"<<endl;

	cout<<"cTypeProperty typePropertyColorRgb( cTypeProperty::COLOR_RGB );"<<endl;
	cTypeProperty typePropertyColorRgb( cTypeProperty::COLOR_RGB );


	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainD3( vecDomains2 );"<<endl;
	cDomainVector vectorDomainD3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	cout<<"rootD3.getDomains()->addDomain( typePropertyColorRgb, vectorDomainD3);"<<endl;
	rootD3.getDomains()->addDomain( typePropertyColorRgb, vectorDomainD3);

	cout<<"cTypeVariable typeVariable;"<<endl;
	cTypeVariable typeVariable;

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB3( 3 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB3( 3 );

	cout<<"rootD3.getDomains()->addDomain( typeVariable, domainNaturalNumberB3);"<<endl;
	rootD3.getDomains()->addDomain( typeVariable, domainNaturalNumberB3);

	cout<<"vecProperty1E3Ch.setDefiningFibElement( &rootD3 );"<<endl;
	vecProperty1E3Ch.setDefiningFibElement( &rootD3 );
	
	cout<<"vecProperty1E3Ch.setValue( 2, 3);"<<endl;
	vecProperty1E3Ch.setValue( 2, 3);

	//test get compressed size
	uiCompressedSize = 4 + 3 + 4;
	if ( (unsigned int)(vecProperty1E3Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecProperty1E3Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecProperty1E3Dom.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = vecProperty1E3Ch.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = (char)0x03;
	sNumberOfRestBitCorrect = uiCompressedSize % 8;
	if ( ( ucRestBit == ucRestBitCorrect ) && ( cNumberOfRestBit == sNumberOfRestBitCorrect ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be "<< (unsigned short)ucRestBitCorrect <<
			" and number of restbit should be "<< sNumberOfRestBitCorrect <<" . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cPropertyE3Dom[] = { (char)0xE3, (char)0x03 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cPropertyE3Dom, 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an propertysvector with domains and all values"<<endl;


	cout<<"vecProperty1E3Ch.setValue( 1, 0);"<<endl;
	vecProperty1E3Ch.setValue( 1, 0);
	cout<<"vecProperty1E3Ch.setValue( 2, 2);"<<endl;
	vecProperty1E3Ch.setValue( 2, 2);
	cout<<"vecProperty1E3Ch.setValue( 3, 5);"<<endl;
	vecProperty1E3Ch.setValue( 3, 5);

	//test get compressed size
	uiCompressedSize = 2 + 3 + 4;
	if ( (unsigned int)(vecProperty1E3Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecProperty1E3Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecProperty1E3DomAllVal.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = vecProperty1E3Ch.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = (char)0x01;
	sNumberOfRestBitCorrect = uiCompressedSize % 8;
	if ( ( ucRestBit == ucRestBitCorrect ) && ( cNumberOfRestBit == sNumberOfRestBitCorrect ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be "<< (unsigned short)ucRestBitCorrect <<
			" and number of restbit should be "<< sNumberOfRestBitCorrect <<" . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cPropertyE3DomAllVal[] = { (char)0x50, (char)0x01 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cPropertyE3DomAllVal, 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an propertysvector 1 elements"<<endl;

	cout<<"cVectorProperty vecProperty1E1( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecProperty1E1( cTypeProperty::LAYER  );
	
	cout<<"vecProperty1E1.setVariable( 1, pVariable2 );"<<endl;
	vecProperty1E1.setVariable( 1, pVariable2 );

	//test get compressed size
	uiCompressedSize = 9;
	if ( (unsigned int)(vecProperty1E1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecProperty1E1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecProperty1E1.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = vecProperty1E1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = (char)0x00;
	sNumberOfRestBitCorrect = 1;
	if ( ( ucRestBit == ucRestBitCorrect ) && ( cNumberOfRestBit == sNumberOfRestBitCorrect ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be "<< (unsigned short)ucRestBitCorrect <<
			" and number of restbit should be "<< sNumberOfRestBitCorrect <<" . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cVecProperty1E1[] = { (char)0x05, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cVecProperty1E1, 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an propertysvector with a restbit of 3"<<endl;

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecProperty1E1R3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x01;
	cNumberOfRestBit = 3;
	bStoreSuccesfull = vecProperty1E1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = (char)0x00;
	sNumberOfRestBitCorrect = 4;
	if ( ( ucRestBit == ucRestBitCorrect ) && ( cNumberOfRestBit == sNumberOfRestBitCorrect ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be "<< (unsigned short)ucRestBitCorrect <<
			" and number of restbit should be "<< sNumberOfRestBitCorrect <<" . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cVecProperty1E1R3[] = { (char)0x29, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cVecProperty1E1R3, 2 );


	return iReturn;
}


/**
 * This method tests the assignment method of the class.
 *
 * methods tested:
 * 	-operator=( const cFibVector &vector ) 
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testAssignment( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the operator=() method"<<endl;
	
	cout<<"cFibVector * pVecPropertyDestination = new cVectorProperty( 1 );"<<endl;
	cFibVector  * pVecPropertyDestination = new cVectorProperty( 1 );
	
	cFibVector * pVecSource;
	cFibVector * pVecEqual;
	
	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;
	
	const unsigned int uiNumberOfVariables = 32;
	cout<<"emptyRoot.setNumberOfInputVariables( uiNumberOfVariables )"<<endl;
	emptyRoot.setNumberOfInputVariables( uiNumberOfVariables );

	const unsigned int pPossiblePropertyTyps[] = {
		1, 2, 100, 200, 300, 301, 305, 310, 311, 312, 400, 410, 600, 46, 0
	};

	
	for ( unsigned int uiIteration = 0; uiIteration < 1024; uiIteration++ ){
		cout<<endl;
		//create source vector
		unsigned int uiNumberOfDimensions = 0;
		if ( (rand() % 10) != 0 ){
			uiNumberOfDimensions = (rand() % 3 + 1) * (rand() % 4 + 1) + (rand() % 4);
		}else{
			uiNumberOfDimensions = 0;
		}
		if ( (rand() % 10) != 0 ){
			unsigned int uiChoosenPropertyType = pPossiblePropertyTyps[ rand() %
				( sizeof( pPossiblePropertyTyps ) / sizeof( unsigned int ) ) ];
			cout<<"pVecSource = new cVectorProperty( "<< uiChoosenPropertyType<<
				", "<< uiNumberOfDimensions <<", &emptyRoot ); "<<endl;
			pVecSource = new cVectorProperty( uiChoosenPropertyType,
				uiNumberOfDimensions, &emptyRoot );
			
			pVecEqual = pVecSource;
		}else{//create non position vector
			const unsigned int uiVectorType = rand() % 2;
			switch( uiVectorType ){
				case 0:{
					cout<<"pVecSource = new cVectorArea( &emptyRoot ); "<<endl;
					pVecSource = new cVectorArea( &emptyRoot );
					
					pVecEqual = new cVectorProperty(
						((cVectorProperty *)(pVecPropertyDestination))->getPropertyType(),
						2, &emptyRoot );
				}break;
				default:{
					//create a positions vector
					cout<<"pVecSource = new cVectorPosition( "<< uiNumberOfDimensions <<", &emptyRoot ); "<<endl;
					pVecSource = new cVectorPosition( uiNumberOfDimensions, &emptyRoot );
					
					pVecEqual = new cVectorProperty(
						((cVectorProperty *)(pVecPropertyDestination))->getPropertyType(),
						uiNumberOfDimensions, &emptyRoot );
				}
			};
		}
		//set the vector elements
		for ( unsigned int uiElement = 1;
				uiElement <= pVecSource->getNumberOfElements(); uiElement++ ){
			
			if ( (rand() % 3) != 0 ){
				//set value
				pVecSource->setValue( uiElement, ((double)(rand() % 1000000)) / 1000.0 );
				cout<<"pVecSource->setValue( "<< uiElement <<", "<<
					pVecSource->getValue( uiElement ) <<" ); "<<endl;
			}else{//set variable
				pVecSource->setVariable( uiElement,
					emptyRoot.getInputVariable( rand() % uiNumberOfVariables + 1 ) );
				cout<<"pVecSource->setVariable( "<< uiElement <<", "<<
					pVecSource->getVariable( uiElement ) <<" ); "<<endl;
			}
			
		}
		if ( pVecEqual != pVecSource ){
			//set the vector elements of the compare to vector
			for ( unsigned int uiElement = 1;
					uiElement <= pVecEqual->getNumberOfElements(); uiElement++ ){
				
				if ( pVecSource->isVariable( uiElement ) ){
					//set variable
					pVecEqual->setVariable( uiElement, pVecSource->getVariable( uiElement ) );
				}else{
					//set value
					pVecEqual->setValue( uiElement, pVecSource->getValue( uiElement ) );
				}
				
			}
		}
		//call operator=()
		cout<<"(* pVecPropertyDestination) = (* pVecSource );"<<endl;
		(* pVecPropertyDestination) = (* pVecSource );
		
		//test the created vector
		if ( ( * pVecPropertyDestination ) == ( * pVecEqual) ){
		
			cout<<"The pVecPropertyDestination is correct . "<<endl;
		}else{
			cerr<<"Error: The pVecPropertyDestination is not correct ."<<endl;
			iReturn++;
		}
		
		if ( pVecEqual != pVecSource ){
			//pVecEqual and pVecSource are different vectors
			delete pVecEqual;
		}
		delete pVecSource;
	}
	delete pVecPropertyDestination;
	
	return iReturn;
}

































