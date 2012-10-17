/**
 * @file tVectorExtObject
 * file name: tVectorExtObject.cpp
 * @author Betti Oesterholz
 * @date 06.12.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cVectorExtObject.
 *
 * Copyright (C) @c GPL3 2012 Betti Oesterholz
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
 * This file contains the test for the class cVectorExtObject,
 * which represents the vector for positions.
 *
 *
 *
 *  What's tested of class cVectorExtObject:
 * 	- cVectorExtObject( unsignedIntFib iNumberOfElements=2, cFibElement * pDefiningSetElement=NULL );
 * 	- cVectorExtObject( cExtObject & definingSetElement );
 * 	- cVectorExtObject( const cVectorExtObject & vector, cFibElement * definingFibElement = NULL );
 * 	- getElementType()
 * 	- getNumberOfElements()
 * 	- getVectorType()
 * 	- getDomain()
 * 	- getValueDomain()
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
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew )
 * 	- equal()
 * 	- operator==()
 * 	- operator=( const cFibVector &vector ) 
 * 	- createInstance()
 * 	- storeXml()
 * 	- store()
 * 	- unsignedLongFib getCompressedSize() const
 * 	- void resize( unsigned int uiNumberOfVectorElements );
 */
/*
History:
26.01.2012  Oesterholz  created
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/


#include "version.h"

#include "cVectorExtObject.h"
#include "cVectorArea.h"
#include "cVectorProperty.h"
#include "cTypeExtObjectInput.h"
#include "cTypeVariable.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainIntegerBit.h"
#include "cDomainVector.h"
#include "cDomainVectorOpenEnd.h"
#include "cRoot.h"
#include "cPoint.h"
#include "cExtObject.h"

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
int testValueDomain( unsigned long &ulTestphase );
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
	int iReturn=0;//return value of the test; the number of occured errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for cVectorExtObject methods"<<endl;
	cout<<      "========================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testDomain( ulTestphase );
	iReturn += testValueDomain( ulTestphase );
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
 * This method tests the constructors of the cVectorExtObject class.
 *
 * constructors tested:
 * 	- cVectorExtObject( unsignedIntFib iNumberOfElements=2, cFibElement * pDefiningSetElement=NULL );
 * 	- cVectorExtObject( cExtObject & definingSetElement );
 * 	- cVectorExtObject( const cVectorExtObject & vector, cFibElement * definingFibElement = NULL );
 * 
 * methods tested:
 * 	- getElementType()
 * 	- getNumberOfElements()
 * 	- isVariable(i=1..n)==false
 * 	- getValue(i=1..n)==0
 * 	- getDomain()
 * 	- getElementType()
 * 	- getDefiningFibElement()
 * 	- getVectorType()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn=0;//return value of the test; the number of occured errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cVectorExtObject"<<endl;

	cout<<"cTypeExtObjectInput typeExtObject( 0 );"<<endl;
	cTypeExtObjectInput typeExtObject( 0 );
	
	cout<<"cVectorExtObject vecExtObject( 0 );"<<endl;
	cVectorExtObject vecExtObject( 0 );


	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObject.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObject.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	
	//check the getElementType() methode from cVectorExtObject
	cTypeElement * pTypeExtObject = vecExtObject.getElementType();
	if ( typeExtObject == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObject.getNumberOfElements() == (unsignedIntFib)(0) ){
	
		cout<<"The number of elements of the external object element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObject.getNumberOfElements()<<" but should be 0 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtObject.getNumberOfElements(); 
			uiActualElement++ ){
		
		if ( ! vecExtObject.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtObject.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtObject.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObject.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the external object element vector."<<endl;
		iReturn++;
	}

	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObject.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the external object element vector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtObject with 3 elements"<<endl;

	cout<<"cVectorExtObject vecExtObjectE3( 3 );"<<endl;
	cVectorExtObject vecExtObjectE3( 3 );


	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3.getElementType();
	if ( typeExtObject == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the external object element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtObjectE3.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtObject.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtObjectE3.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtObjectE3.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObjectE3.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the external object element vector."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtObject with 4 elements and an defining element"<<endl;

	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;

	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	//create vector domain with two elements
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3Nat4( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3Nat4( 3 );
	cout<<"vecDomainsE3Na2Nat3Nat4[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3Nat4[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3Nat4[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3Nat4[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3Nat4[ 2 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE3Na2Nat3Nat4[ 2 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE3Na2Nat3Nat4 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE3Na2Nat3Nat4 );
	delete vecDomainsE3Na2Nat3Nat4[ 0 ];
	delete vecDomainsE3Na2Nat3Nat4[ 1 ];
	delete vecDomainsE3Na2Nat3Nat4[ 2 ];

	cout<<"rootD2.getDomains()->addDomain( typeExtObject, vectorDomainE3Na2Nat3VE1Nat1 );"<<endl;
	rootD2.getDomains()->addDomain( typeExtObject, vectorDomainE3Na2Nat3VE1Nat1 );

	
	cout<<"cVectorExtObject vecExtObjectE4RD2 = cVectorExtObject( 4, &rootD2 );"<<endl;
	cVectorExtObject vecExtObjectE4RD2 = cVectorExtObject( 4, &rootD2 );


	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE4RD2.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE4RD2.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE4RD2.getElementType();
	if ( typeExtObject == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE4RD2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the external object element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE4RD2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtObjectE4RD2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtObjectE4RD2.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtObjectE4RD2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtObjectE4RD2.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE4RD2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecExtObjectE4RD2.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObjectE4RD2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE1Nat1 == (*(vecExtObjectE4RD2.getDomain())) ){
	
		cout<<"The vectorDomainE3Na2Nat3VE1Nat1 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE1Nat1 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtObject with a external object element as defining element"<<endl;

	cout<<"cExtObject extObjectV4( 4 );"<<endl;
	cExtObject extObjectV4( 4 );
	
	cout<<"cVectorExtObject vecExtObjectE4( 4, &extObjectV4 );"<<endl;
	cVectorExtObject vecExtObjectE4( 4, &extObjectV4 );

	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE4.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE4.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	cTypeExtObjectInput typeExtObjectInput4( 4 );
	pTypeExtObject = vecExtObjectE4.getElementType();
	if ( typeExtObjectInput4 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to cTypeExtObjectInput( 4 ). "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to cTypeExtObjectInput( 4 ) ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE4.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the external object element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE4.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtObjectE4.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtObjectE4.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtObjectE4.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtObjectE4.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE4.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV4 == vecExtObjectE4.getDefiningFibElement() ){
	
		cout<<"The extObjectV4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObjectE4.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtObject with a external object element as defining element, wich has other than the vector elemnts defined variables"<<endl;
	
	cout<<"cVectorExtObject vecExtObjectE3V4( 3, &extObjectV4 );"<<endl;
	cVectorExtObject vecExtObjectE3V4( 3, &extObjectV4 );

	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3V4.getElementType();
	if ( typeExtObjectInput4 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to cTypeExtObjectInput( 4 ). "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to cTypeExtObjectInput( 4 ) ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the external object element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtObjectE3V4.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtObjectE3V4.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtObjectE3V4.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtObjectE3V4.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV4 == vecExtObjectE3V4.getDefiningFibElement() ){
	
		cout<<"The extObjectV4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObjectE3V4.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtObject with a external object element as defining element, wich has domain number set"<<endl;
	
	cout<<"cRoot rootDom4;"<<flush<<endl;
	cRoot rootDom4;
	
	cout<<"rootDom4.getDomains()->addDomain( typeExtObject, vectorDomainE3Na2Nat3VE1Nat1 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject, vectorDomainE3Na2Nat3VE1Nat1 );

	//create vector domain with tree elements
	cout<<"vecDomainsE3Na2Nat3Nat4[ 0 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE3Na2Nat3Nat4[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE3Na2Nat3Nat4[ 1 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE3Na2Nat3Nat4[ 1 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE3Na2Nat3Nat4[ 2 ] =  new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE3Na2Nat3Nat4[ 2 ] =  new cDomainNaturalNumberBit( 5 );
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3Nat4 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3Nat4 );
	delete vecDomainsE3Na2Nat3Nat4[ 0 ];
	delete vecDomainsE3Na2Nat3Nat4[ 1 ];
	delete vecDomainsE3Na2Nat3Nat4[ 2 ];

	cout<<"cTypeExtObjectInput typeExtObject4( 4 );"<<endl;
	cTypeExtObjectInput typeExtObject4( 4 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtObject4, vectorDomainE3Na4Nat5VE2NInt2Int3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject4, vectorDomainE3Na4Nat5VE2NInt2Int3 );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Int4Int5( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Int4Int5( 2 );
	cout<<"vecDomainsE2Int4Int5[ 0 ] = new cDomainIntegerBit( 4 );"<<endl;
	vecDomainsE2Int4Int5[ 0 ] = new cDomainIntegerBit( 4 );
	cout<<"vecDomainsE2Int4Int5[ 1 ] = new cDomainIntegerBit( 5 );"<<endl;
	vecDomainsE2Int4Int5[ 1 ] = new cDomainIntegerBit( 5 );
	cout<<"cDomainVector vectorDomainE2Int4Int5( vecDomainsE2Int4Int5 );"<<endl;
	cDomainVector vectorDomainE2Int4Int5( vecDomainsE2Int4Int5 );
	delete vecDomainsE2Int4Int5[ 0 ];
	delete vecDomainsE2Int4Int5[ 1 ];

	cout<<"cTypeExtObjectInput typeExtObject5( 5 );"<<endl;
	cTypeExtObjectInput typeExtObject5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtObject5, vectorDomainE2Int4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject5, vectorDomainE2Int4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"cTypeExtObjectInput typeExtObject6( 6 );"<<endl;
	cTypeExtObjectInput typeExtObject6( 6 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtObject6, vectorDomainOE1Int8 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject6, vectorDomainOE1Int8 );
	
	
	cout<<"cExtObject extObjectV3Dom5rootDom4( 5, 0, &rootDom4 );"<<endl;
	cExtObject extObjectV3Dom5rootDom4( 5, 0, &rootDom4 );
	
	cout<<"cVectorExtObject vecExtObjectE3V4Dom5( 2, &extObjectV3Dom5rootDom4 );"<<endl;
	cVectorExtObject vecExtObjectE3V4Dom5( 2, &extObjectV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	if ( typeExtObject5 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject5. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject5 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtObjectE3V4Dom5.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtObjectE3V4Dom5.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtObjectE3V4Dom5.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtObjectE3V4Dom5.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3Dom5rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3Dom5rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3Dom5rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE2Int4Int5 == (*(vecExtObjectE3V4Dom5.getDomain())) ){
	
		cout<<"The vectorDomainE2Int4Int5 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtObject with a external object element as defining element, wich has a not existig domain number set"<<endl;
	
	cout<<"extObjectV3Dom5rootDom4.setIdentifier( 13 );"<<endl;
	extObjectV3Dom5rootDom4.setIdentifier( 13 );
	
	cout<<"cVectorExtObject vecExtObjectE3V4Dom13( 2, &extObjectV3Dom5rootDom4 );"<<endl;
	cVectorExtObject vecExtObjectE3V4Dom13( 2, &extObjectV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom13.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom13.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	cout<<"cTypeExtObjectInput typeExtObject13( 13 ); "<<endl;
	cTypeExtObjectInput typeExtObject13( 13 );
	pTypeExtObject = vecExtObjectE3V4Dom13.getElementType();
	if ( typeExtObject13 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject13. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject13 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom13.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom13.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtObjectE3V4Dom13.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtObjectE3V4Dom13.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtObjectE3V4Dom13.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtObjectE3V4Dom13.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom13.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3Dom5rootDom4 == vecExtObjectE3V4Dom13.getDefiningFibElement() ){
	
		cout<<"The extObjectV3Dom13rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3Dom13rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom13.getDomain() == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: Ther is a domain defined for the external object element vector."<<endl;
		iReturn++;	
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtObject with just a external object element as defining element"<<endl;

	cout<<"cVectorExtObject vecExtObject2E4( extObjectV4 );"<<endl;
	cVectorExtObject vecExtObject2E4( extObjectV4 );

	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObject2E4.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObject2E4.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObject2E4.getElementType();
	if ( typeExtObjectInput4 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObjectInput4. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObjectInput4."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObject2E4.getNumberOfElements() == (unsignedIntFib)(0) ){
	
		cout<<"The number of elements of the external object element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObject2E4.getNumberOfElements()<<" but should be 0 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtObject2E4.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtObject2E4.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtObject2E4.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtObject2E4.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObject2E4.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV4 == vecExtObject2E4.getDefiningFibElement() ){
	
		cout<<"The extObjectV4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObject2E4.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtObject with just a external object element as defining element, wich has domain number set"<<endl;
	
	cout<<"extObjectV3Dom5rootDom4.setIdentifier( 5 );"<<endl;
	extObjectV3Dom5rootDom4.setIdentifier( 5 );

	cout<<"cVectorExtObject vecExtObject2E3V4Dom5( extObjectV3Dom5rootDom4 );"<<endl;
	cVectorExtObject vecExtObject2E3V4Dom5( extObjectV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObject2E3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObject2E3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObject2E3V4Dom5.getElementType();
	if ( typeExtObject5 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject5. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject5 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObject2E3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObject2E3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtObject2E3V4Dom5.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtObject2E3V4Dom5.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtObject2E3V4Dom5.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtObject2E3V4Dom5.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObject2E3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3Dom5rootDom4 == vecExtObject2E3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3Dom5rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3Dom5rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObject2E3V4Dom5.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE2Int4Int5 == (*(vecExtObject2E3V4Dom5.getDomain())) ){
	
		cout<<"The vectorDomainE2Int4Int5 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtObject with yust a external object element as defining element, wich has a not existig domain number set"<<endl;
	
	cout<<"extObjectV3Dom5rootDom4.setIdentifier( 13 );"<<endl;
	extObjectV3Dom5rootDom4.setIdentifier( 13 );

	cout<<"cVectorExtObject vecExtObject2E3V4Dom13( extObjectV3Dom5rootDom4 );"<<endl;
	cVectorExtObject vecExtObject2E3V4Dom13( extObjectV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObject2E3V4Dom13.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObject2E3V4Dom13.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObject2E3V4Dom13.getElementType();
	if ( typeExtObject13 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject13. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject13 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObject2E3V4Dom13.getNumberOfElements() == (unsignedIntFib)(0) ){
	
		cout<<"The number of elements of the external object element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObject2E3V4Dom13.getNumberOfElements()<<" but should be 0 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtObject2E3V4Dom13.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtObject2E3V4Dom13.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtObject2E3V4Dom13.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtObject2E3V4Dom13.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObject2E3V4Dom13.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3Dom5rootDom4 == vecExtObject2E3V4Dom13.getDefiningFibElement() ){
	
		cout<<"The extObjectV3Dom13rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3Dom13rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObject2E3V4Dom13.getDomain() == NULL ){
		cout<<"Ther is corroctly no domain defined for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: Ther is a domain defined for the external object element vector."<<endl;
		iReturn++;	
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtObject by copying vecExtObjectE3"<<endl;
	
	cout<<"cVectorExtObject vecExtObjectE3Copy( vecExtObjectE3 );"<<endl;
	cVectorExtObject vecExtObjectE3Copy( vecExtObjectE3 );

	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3Copy.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3Copy.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3Copy.getElementType();
	if ( typeExtObject == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3Copy.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the external object element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3Copy.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtObjectE3Copy.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtObjectE3Copy.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtObjectE3Copy.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<< vecExtObjectE3Copy.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3Copy.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObjectE3Copy.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtObject by copying vecExtObjectE4RD2"<<endl;
	
	cout<<"cVectorExtObject vecExtObjectE4RD2Copy( vecExtObjectE4RD2 );"<<endl;
	cVectorExtObject vecExtObjectE4RD2Copy( vecExtObjectE4RD2 );

	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE4RD2Copy.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE4RD2Copy.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE4RD2Copy.getElementType();
	if ( typeExtObject == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE4RD2Copy.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the external object element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE4RD2Copy.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtObjectE4RD2Copy.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtObjectE4RD2Copy.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtObjectE4RD2Copy.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<< vecExtObjectE4RD2Copy.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE4RD2Copy.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecExtObjectE4RD2Copy.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObjectE4RD2Copy.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE1Nat1 == (*(vecExtObjectE4RD2Copy.getDomain())) ){
	
		cout<<"The vectorDomainE3Na2Nat3VE1Nat1 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE1Nat1 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtObject by copying vecExtObjectE4RD2 and givin extObjectV3Dom5rootDom4 as an defining element"<<endl;
	
	cout<<"extObjectV3Dom5rootDom4.setIdentifier( 5 );"<<endl;
	extObjectV3Dom5rootDom4.setIdentifier( 5 );

	cout<<"cVectorExtObject vecExtObjectE4RD2Copy2( vecExtObjectE4RD2, &extObjectV3Dom5rootDom4 );"<<endl;
	cVectorExtObject vecExtObjectE4RD2Copy2( vecExtObjectE4RD2, &extObjectV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE4RD2Copy2.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE4RD2Copy2.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE4RD2Copy2.getElementType();
	if ( typeExtObject5 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject5. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject5 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE4RD2Copy2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the external object element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE4RD2Copy2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtObjectE4RD2Copy2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtObjectE4RD2Copy2.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtObjectE4RD2Copy2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<< vecExtObjectE4RD2Copy2.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE4RD2Copy2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3Dom5rootDom4 == vecExtObjectE4RD2Copy2.getDefiningFibElement() ){
	
		cout<<"The extObjectV3Dom5rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3Dom5rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObjectE4RD2Copy2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE2Int4Int5 == (*(vecExtObjectE4RD2Copy2.getDomain())) ){
	
		cout<<"The vectorDomainE2Int4Int5 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtObject by copying vecExtObjectRD3 with changed elements"<<endl;
	
	cout<<"rootDom4.setNumberOfInputVariables( 2 );"<<endl;
	rootDom4.setNumberOfInputVariables( 2 );
	cout<<"cFibVariable * pVariable1 = rootDom4.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootDom4.getInputVariable( 1 );
	cout<<"cFibVariable * pVariable2 = rootDom4.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = rootDom4.getInputVariable( 2 );

	cout<<"vecExtObjectE4RD2.setValue( 1, 1 );"<<endl;
	vecExtObjectE4RD2.setValue( 1, 1 );
	cout<<"vecExtObjectE4RD2.setVariable( 2, pVariable1 );"<<endl;
	vecExtObjectE4RD2.setVariable( 2, pVariable1 );
	cout<<"vecExtObjectE4RD2.setValue( 3, 2 );"<<endl;
	vecExtObjectE4RD2.setValue( 3, 2 );
	cout<<"vecExtObjectE4RD2.setVariable( 4, pVariable2 );"<<endl;
	vecExtObjectE4RD2.setVariable( 4, pVariable2 );
	
	cout<<"cVectorExtObject vecExtObjectE4RD2CopyMod( vecExtObjectE4RD2 );"<<endl;
	cVectorExtObject vecExtObjectE4RD2CopyMod( vecExtObjectE4RD2 );

	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE4RD2CopyMod.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE4RD2CopyMod.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE4RD2CopyMod.getElementType();
	if ( typeExtObject == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE4RD2Copy2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the external object element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE4RD2Copy2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
		//check the first vectorelement
	if ( ! vecExtObjectE4RD2CopyMod.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObjectE4RD2CopyMod.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObjectE4RD2CopyMod.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecExtObjectE4RD2CopyMod.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObjectE4RD2CopyMod.getVariable( 2 ) == pVariable1 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the secound vectorelement
	if ( ! vecExtObjectE4RD2CopyMod.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObjectE4RD2CopyMod.getValue( 3 ) == (doubleFib)(2) ){
	
		cout<<"The 3'th element of the "<<
			"external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObjectE4RD2CopyMod.getValue( 3 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecExtObjectE4RD2CopyMod.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObjectE4RD2CopyMod.getVariable( 4 ) == pVariable2 ){
	
		cout<<"The 4'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE4RD2CopyMod.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecExtObjectE4RD2CopyMod.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObjectE4RD2CopyMod.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE1Nat1 == (*(vecExtObjectE4RD2CopyMod.getDomain())) ){
	
		cout<<"The vectorDomainE3Na2Nat3VE1Nat1 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE1Nat1 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"Testing the original vector vecExtObjectE4RD2:"<<endl;

	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE4RD2.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE4RD2.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE4RD2.getElementType();
	if ( typeExtObject == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE4RD2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the external object element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE4RD2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
		//check the first vectorelement
	if ( ! vecExtObjectE4RD2.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObjectE4RD2.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObjectE4RD2.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecExtObjectE4RD2.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObjectE4RD2.getVariable( 2 ) == pVariable1 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the secound vectorelement
	if ( ! vecExtObjectE4RD2.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObjectE4RD2.getValue( 3 ) == (doubleFib)(2) ){
	
		cout<<"The 3'th element of the "<<
			"external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObjectE4RD2.getValue( 3 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecExtObjectE4RD2.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObjectE4RD2.getVariable( 4 ) == pVariable2 ){
	
		cout<<"The 4'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE4RD2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecExtObjectE4RD2.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObjectE4RD2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE1Nat1 == (*(vecExtObjectE4RD2.getDomain())) ){
	
		cout<<"The vectorDomainE3Na2Nat3VE1Nat1 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE1Nat1 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"Changing vecExtObjectE4RD2 should not change the copy:"<<endl;

	cout<<"vecExtObjectE4RD2.setVariable( 1, pVariable2 );"<<endl;
	vecExtObjectE4RD2.setVariable( 1, pVariable2 );
	cout<<"vecExtObjectE4RD2.setValue( 2, 9 );"<<endl;
	vecExtObjectE4RD2.setValue( 2, 1 );
	cout<<"vecExtObjectE4RD2.setValue( 3, 8 );"<<endl;
	vecExtObjectE4RD2.setValue( 3, 2 );

	cout<<endl<<"Testing the copied vector vecExtObjectE4RD2CopyMod for changed values:"<<endl;
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE4RD2CopyMod.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE4RD2CopyMod.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE4RD2CopyMod.getElementType();
	if ( typeExtObject == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE4RD2Copy2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the external object element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE4RD2Copy2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
		//check the first vectorelement
	if ( ! vecExtObjectE4RD2CopyMod.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObjectE4RD2CopyMod.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObjectE4RD2CopyMod.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecExtObjectE4RD2CopyMod.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObjectE4RD2CopyMod.getVariable( 2 ) == pVariable1 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the secound vectorelement
	if ( ! vecExtObjectE4RD2CopyMod.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObjectE4RD2CopyMod.getValue( 3 ) == (doubleFib)(2) ){
	
		cout<<"The 3'th element of the "<<
			"external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObjectE4RD2CopyMod.getValue( 3 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecExtObjectE4RD2CopyMod.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObjectE4RD2CopyMod.getVariable( 4 ) == pVariable2 ){
	
		cout<<"The 4'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE4RD2CopyMod.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecExtObjectE4RD2CopyMod.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObjectE4RD2CopyMod.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE1Nat1 == (*(vecExtObjectE4RD2CopyMod.getDomain())) ){
	
		cout<<"The vectorDomainE3Na2Nat3VE1Nat1 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE1Nat1 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the method for the domains of the cVectorExtObject class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get domain methods"<<endl;
	
	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	
	//create vector domain with tree elements
	cout<<"vector<cDomainSingle*> vecDomainsE3Nat1Nat2Nat3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3Nat1Nat2Nat3( 3 );
	cout<<"vecDomainsE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Nat1Nat2Nat3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Nat1Nat2Nat3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE3Nat1Nat2Nat3( vecDomainsE3Nat1Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE3Nat1Nat2Nat3( vecDomainsE3Nat1Nat2Nat3 );
	delete vecDomainsE3Nat1Nat2Nat3[ 0 ];
	delete vecDomainsE3Nat1Nat2Nat3[ 1 ];
	delete vecDomainsE3Nat1Nat2Nat3[ 2 ];
	
	cout<<"cTypeExtObjectInput typeExtObject( 0 );"<<endl;
	cTypeExtObjectInput typeExtObject( 0 );

	cout<<"root.getDomains()->addDomain( typeExtObject, &vectorDomainE3Nat1Nat2Nat3 );"<<endl;
	root.getDomains()->addDomain( typeExtObject, &vectorDomainE3Nat1Nat2Nat3 );

	
	cout<<"cVectorExtObject vecExtObjectRD( 3, &root );"<<endl;
	cVectorExtObject vecExtObjectRD( 3, &root );
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectRD.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the external object element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectRD.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the getDomain() methode from cVectorExtObject
	if ( vecExtObjectRD.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE3Nat1Nat2Nat3 == vecExtObjectRD.getDomain() ){
	
		cout<<"The &vectorDomainE3Nat1Nat2Nat3 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: &vectorDomainE3Nat1Nat2Nat3 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}

	/*check the getDomain(i=1..n) method of the set-vektor*/
	//test the getType() method
	cout<<"cDomain * pDomainD3 = vecExtObjectRD.getDomain();"<<endl;
	cDomain * pDomainD3 = vecExtObjectRD.getDomain();
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

	//check the getStandardDomain() method from cVectorExtObject
	cDomain * pDomainStandard = vecExtObjectRD.getStandardDomain();
	cDomain * pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtObject domains with domain numbers"<<endl;
	
	cout<<"cRoot rootDom4;"<<flush<<endl;
	cRoot rootDom4;
	
	cout<<"rootDom4.getDomains()->addDomain( typeExtObject, &vectorDomainE3Nat1Nat2Nat3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject, &vectorDomainE3Nat1Nat2Nat3 );

	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Int2Int3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Int2Int3( 2 );
	cout<<"vecDomainsE2Int2Int3[ 0 ] = new cDomainIntegerBit( 2 );"<<endl;
	vecDomainsE2Int2Int3[ 0 ] = new cDomainIntegerBit( 2 );
	cout<<"vecDomainsE2Int2Int3[ 1 ] = new cDomainIntegerBit( 3 );"<<endl;
	vecDomainsE2Int2Int3[ 1 ] = new cDomainIntegerBit( 3 );
	cout<<"cDomainVector vectorDomainE2NInt2Int3( vecDomainsE2Int2Int3 );"<<endl;
	cDomainVector vectorDomainE2NInt2Int3( vecDomainsE2Int2Int3 );
	delete vecDomainsE2Int2Int3[ 0 ];
	delete vecDomainsE2Int2Int3[ 1 ];
	
	cout<<"cTypeExtObjectInput typeExtObject4( 4 );"<<endl;
	cTypeExtObjectInput typeExtObject4( 4 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtObject4, &vectorDomainE2NInt2Int3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject4, &vectorDomainE2NInt2Int3 );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Int4Int5( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Int4Int5( 2 );
	cout<<"vecDomainsE2Int4Int5[ 0 ] = new cDomainIntegerBit( 4 );"<<endl;
	vecDomainsE2Int4Int5[ 0 ] = new cDomainIntegerBit( 4 );
	cout<<"vecDomainsE2Int4Int5[ 1 ] = new cDomainIntegerBit( 5 );"<<endl;
	vecDomainsE2Int4Int5[ 1 ] = new cDomainIntegerBit( 5 );
	cout<<"cDomainVector vectorDomainE2Int4Int5( vecDomainsE2Int4Int5 );"<<endl;
	cDomainVector vectorDomainE2Int4Int5( vecDomainsE2Int4Int5 );
	delete vecDomainsE2Int4Int5[ 0 ];
	delete vecDomainsE2Int4Int5[ 1 ];

	cout<<"cTypeExtObjectInput typeExtObject5( 5 );"<<endl;
	cTypeExtObjectInput typeExtObject5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtObject5, &vectorDomainE2Int4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject5, &vectorDomainE2Int4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"cTypeExtObjectInput typeExtObject6( 6 );"<<endl;
	cTypeExtObjectInput typeExtObject6( 6 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtObject6, &vectorDomainOE1Int8 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject6, &vectorDomainOE1Int8 );
	

	cout<<"cExtObject extObjectV3rootDom4( 0, 0, &rootDom4 );"<<endl;
	cExtObject extObjectV3rootDom4( 0, 0, &rootDom4 );
	
	cout<<"cVectorExtObject vecExtObjectE3V4Dom5( 2, &extObjectV3rootDom4 );"<<endl;
	cVectorExtObject vecExtObjectE3V4Dom5( 2, &extObjectV3rootDom4 );

	//check the getDomain() methode from cVectorExtObject
	cout<<"cDomain * pDomain = vecExtObjectE3V4Dom5.getDomain();"<<endl;
	cDomain * pDomain = vecExtObjectE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorExtObject
		if ( &vectorDomainE3Nat1Nat2Nat3 == vecExtObjectRD.getDomain() ){
		
			cout<<"The &vectorDomainE3Nat1Nat2Nat3 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The &vectorDomainE3Nat1Nat2Nat3 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}

		/*check the getDomain(i=1..n) method of the set-vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVector" ){
		
			cout<<"The type of pDomain is correctly \"DomainVector\". "<<endl;

			cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
			
			//test the getNumberOfElements() method
			if ( pVectorDomain->getNumberOfElements() == 3 ){
			
				cout<<"The number of elements of pDomain is correctly 3. "<<endl;
				
				//check domains of vector domain elements
				
				cDomainNaturalNumberBit domainNaturalNumberBit1 = cDomainNaturalNumberBit( 1 );
				if ( pVectorDomain->getElementDomain( 1 ) == NULL ){
					cerr<<"Error: The first element domain is NULL. "<<endl;
					iReturn++;
				}else if ( (*(pVectorDomain->getElementDomain( 1 ))) == domainNaturalNumberBit1 ){
				
					cout<<"The first element domain is correctly an cDomainNaturalNumberBit domain with 1 bits. "<<endl;
				}else{
					cerr<<"Error: The first element domain is not an cDomainNaturalNumberBit domain with 1 bits. "<<endl;
					iReturn++;
				}
		
				cDomainNaturalNumberBit domainNaturalNumberBit2 = cDomainNaturalNumberBit( 2 );
				if ( pVectorDomain->getElementDomain( 2 )==NULL ){
					cerr<<"Error: The secound element domain is NULL. "<<endl;
					iReturn++;
				}else if ( (*(pVectorDomain->getElementDomain( 2 ))) == domainNaturalNumberBit2 ){
				
					cout<<"The secound element domain is correctly an cDomainNaturalNumberBit domain with 2 bits. "<<endl;
				}else{
					cerr<<"Error: The secound element domain is not an cDomainNaturalNumberBit domain with 2 bits. "<<endl;
					iReturn++;
				}
		
				cDomainNaturalNumberBit domainNaturalNumberBit3 = cDomainNaturalNumberBit( 3 );
				
				if ( pVectorDomain->getElementDomain( 3 ) == NULL ){
					cerr<<"Error: The third element domain is NULL. "<<endl;
					iReturn++;
				}else if ( (*(pVectorDomain->getElementDomain( 3 ))) == domainNaturalNumberBit3 ){
				
					cout<<"The third element domain is correctly an cDomainNaturalNumberBit domain with 3 bits. "<<endl;
				}else{
					cerr<<"Error: The third element domain is not an cDomainNaturalNumberBit domain with 3 bits. "<<endl;
					iReturn++;
				}
		
				//check bounderies
				if ( pVectorDomain->getElementDomain( 0 ) == NULL ){
					cerr<<"The is no 0'th element domain."<<endl;
				}
		
				if ( pVectorDomain->getElementDomain( 4 ) == NULL ){
					cerr<<"The is no 4'th element domain."<<endl;
				}
		
		
			}else{
				cerr<<"Error: The number of elements of pDomain is "<<
					pVectorDomain->getNumberOfElements() <<" and not 3 ."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The type of pDomain is "<<pDomain->getType() <<
				" and not \"DomainVector\""<<endl;
			iReturn++;
		}
	}

	//check the getStandardDomain() method from cVectorExtObject
	pDomainStandard = vecExtObjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	cTypeElement * pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	if ( typeExtObject == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtObject domains with domain numbers, setting domain number 1"<<endl;
	
	cout<<"extObjectV3rootDom4.setIdentifier( 1 );"<<endl;
	extObjectV3rootDom4.setIdentifier( 1 );

	//check the getDomain() methode from cVectorExtObject
	cout<<"pDomain = vecExtObjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtObjectE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}

	//check the getStandardDomain() method from cVectorExtObject
	pDomainStandard = vecExtObjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	cTypeExtObjectInput typeExtObject1( 1 );
	if ( typeExtObject1 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject1. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject1 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtObject domains with domain numbers, setting domain number 3"<<endl;
	
	cout<<"extObjectV3rootDom4.setIdentifier( 3 );"<<endl;
	extObjectV3rootDom4.setIdentifier( 3 );

	//check the getDomain() methode from cVectorExtObject
	cout<<"pDomain = vecExtObjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtObjectE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}


	//check the getStandardDomain() method from cVectorExtObject
	pDomainStandard = vecExtObjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	cTypeExtObjectInput typeExtObject3( 3 );
	if ( typeExtObject3 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject3. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject3 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtObject domains with domain numbers, setting domain number 4"<<endl;
	
	cout<<"extObjectV3rootDom4.setIdentifier( 4 );"<<endl;
	extObjectV3rootDom4.setIdentifier( 4 );

	//check the getDomain() methode from cVectorExtObject
	cout<<"pDomain = vecExtObjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtObjectE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE2NInt2Int3 == *pDomain ){
		
			cout<<"The vectorDomainE2NInt2Int3 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE2NInt2Int3 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorExtObject
		if ( &vectorDomainE2NInt2Int3 == pDomain ){
		
			cout<<"The &vectorDomainE2NInt2Int3 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: &vectorDomainE2NInt2Int3 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}

		/*check the getDomain(i=1..n) method of the set-vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVector" ){
		
			cout<<"The type of pDomain is correctly \"DomainVector\". "<<endl;

			cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
			
			//test the getNumberOfElements() method
			if ( pVectorDomain->getNumberOfElements() == 2 ){
			
				cout<<"The number of elements of pDomain is correctly 3. "<<endl;
				
				//check domains of vector domain elements
				cDomainIntegerBit domainIntegerBit2( 2 );
				if ( pVectorDomain->getElementDomain( 1 ) == NULL ){
					cerr<<"Error: The first element domain is NULL. "<<endl;
					iReturn++;
				}else if ( (*(pVectorDomain->getElementDomain( 1 ))) == domainIntegerBit2 ){
				
					cout<<"The first element domain is correctly an cDomainIntegerBit domain with 2 bits. "<<endl;
				}else{
					cerr<<"Error: The first element domain is not an cDomainIntegerBit domain with 2 bits. "<<endl;
					iReturn++;
				}
		
				cDomainIntegerBit domainIntegerBit3( 3 );
				if ( pVectorDomain->getElementDomain( 2 )==NULL ){
					cerr<<"Error: The secound element domain is NULL. "<<endl;
					iReturn++;
				}else if ( (*(pVectorDomain->getElementDomain( 2 ))) == domainIntegerBit3 ){
				
					cout<<"The secound element domain is correctly an cDomainIntegerBit domain with 3 bits. "<<endl;
				}else{
					cerr<<"Error: The secound element domain is not an cDomainIntegerBit domain with 3 bits. "<<endl;
					iReturn++;
				}

				//check bounderies
				if ( pVectorDomain->getElementDomain( 0 ) == NULL ){
					cerr<<"The is no 0'th element domain."<<endl;
				}
		
				if ( pVectorDomain->getElementDomain( 3 ) == NULL ){
					cerr<<"The is no 3'th element domain."<<endl;
				}
			}else{
				cerr<<"Error: The number of elements of pDomain is "<<
					pVectorDomain->getNumberOfElements() <<" and not 2 ."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The type of pDomain is "<<pDomain->getType() <<
				" and not \"DomainVector\""<<endl;
			iReturn++;
		}
	}

	//check the getStandardDomain() method from cVectorExtObject
	pDomainStandard = vecExtObjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	if ( typeExtObject4 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject4. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject4 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtObject domains with domain numbers, setting domain number 5"<<endl;
	
	cout<<"extObjectV3rootDom4.setIdentifier( 5 );"<<endl;
	extObjectV3rootDom4.setIdentifier( 5 );

	//check the getDomain() methode from cVectorExtObject
	cout<<"pDomain = vecExtObjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtObjectE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE2Int4Int5 == *pDomain ){
		
			cout<<"The vectorDomainE2Int4Int5 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorExtObject
		if ( &vectorDomainE2Int4Int5 == pDomain ){
		
			cout<<"The &vectorDomainE2Int4Int5 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The &vectorDomainE2Int4Int5 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}

		/*check the getDomain(i=1..n) method of the set-vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVector" ){
		
			cout<<"The type of pDomain is correctly \"DomainVector\". "<<endl;

			cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
			
			//test the getNumberOfElements() method
			if ( pVectorDomain->getNumberOfElements() == 2 ){
			
				cout<<"The number of elements of pDomain is correctly 2. "<<endl;
				
				//check domains of vector domain elements
				cDomainIntegerBit domainIntegerBit4( 4 );
				if ( pVectorDomain->getElementDomain( 1 ) == NULL ){
					cerr<<"Error: The first element domain is NULL. "<<endl;
					iReturn++;
				}else if ( (*(pVectorDomain->getElementDomain( 1 ))) == domainIntegerBit4 ){
				
					cout<<"The first element domain is correctly an cDomainIntegerBit domain with 4 bits. "<<endl;
				}else{
					cerr<<"Error: The first element domain is not an cDomainIntegerBit domain with 4 bits. "<<endl;
					iReturn++;
				}
		
				cDomainIntegerBit domainIntegerBit5( 5 );
				if ( pVectorDomain->getElementDomain( 2 )==NULL ){
					cerr<<"Error: The secound element domain is NULL. "<<endl;
					iReturn++;
				}else if ( (*(pVectorDomain->getElementDomain( 2 ))) == domainIntegerBit5 ){
				
					cout<<"The secound element domain is correctly an cDomainIntegerBit domain with 5 bits. "<<endl;
				}else{
					cerr<<"Error: The secound element domain is not an cDomainIntegerBit domain with 5 bits. "<<endl;
					iReturn++;
				}

				//check bounderies
				if ( pVectorDomain->getElementDomain( 0 ) == NULL ){
					cerr<<"The is no 0'th element domain."<<endl;
				}
		
				if ( pVectorDomain->getElementDomain( 3 ) == NULL ){
					cerr<<"The is no 3'th element domain."<<endl;
				}
			}else{
				cerr<<"Error: The number of elements of pDomain is "<<
					pVectorDomain->getNumberOfElements() <<" and not 2 ."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The type of pDomain is "<<pDomain->getType() <<
				" and not \"DomainVector\""<<endl;
			iReturn++;
		}
	}

	//check the getStandardDomain() method from cVectorExtObject
	pDomainStandard = vecExtObjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	if ( typeExtObject5 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject5. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject5 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtObject domains with domain numbers, setting domain number 6"<<endl;
	
	cout<<"extObjectV3rootDom4.setIdentifier( 6 );"<<endl;
	extObjectV3rootDom4.setIdentifier( 6 );

	//check the getDomain() methode from cVectorExtObject
	cout<<"pDomain = vecExtObjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtObjectE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainOE1Int8 == *pDomain ){
		
			cout<<"The vectorDomainOE1Int8 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorExtObject
		if ( &vectorDomainOE1Int8 == pDomain ){
		
			cout<<"The &vectorDomainOE1Int8 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The &vectorDomainOE1Int8 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}

		/*check the getDomain(i=1..n) method of the set-vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVectorOpenEnd" ){
		
			cout<<"The type of pDomain is correctly \"DomainVector\". "<<endl;

			cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
			
			//test the getNumberOfElements() method
			if ( pVectorDomain->getNumberOfElements() == 1 ){
			
				cout<<"The number of elements of pDomain is correctly 3. "<<endl;
				
				//check domains of vector domain elements
				cDomainIntegerBit domainIntegerBit8( 8 );
				if ( pVectorDomain->getElementDomain( 1 ) == NULL ){
					cerr<<"Error: The first element domain is NULL. "<<endl;
					iReturn++;
				}else if ( (*(pVectorDomain->getElementDomain( 1 ))) == domainIntegerBit8 ){
				
					cout<<"The first element domain is correctly an cDomainIntegerBit domain with 8 bits. "<<endl;
				}else{
					cerr<<"Error: The first element domain is not an cDomainIntegerBit domain with 8 bits. "<<endl;
					iReturn++;
				}
				//all following domains are the same
				if ( pVectorDomain->getElementDomain( 2 ) == NULL ){
					cerr<<"Error: The secound element domain is NULL. "<<endl;
					iReturn++;
				}else if ( (*(pVectorDomain->getElementDomain( 2 ))) == domainIntegerBit8 ){
				
					cout<<"The secound element domain is correctly an cDomainIntegerBit domain with 8 bits. "<<endl;
				}else{
					cerr<<"Error: The secound element domain is not an cDomainIntegerBit domain with 8 bits. "<<endl;
					iReturn++;
				}
				
				if ( pVectorDomain->getElementDomain( 256 ) == NULL ){
					cerr<<"Error: The 256'th element domain is NULL. "<<endl;
					iReturn++;
				}else if ( (*(pVectorDomain->getElementDomain( 256 ))) == domainIntegerBit8 ){
				
					cout<<"The 256'th element domain is correctly an cDomainIntegerBit domain with 8 bits. "<<endl;
				}else{
					cerr<<"Error: The 256'th element domain is not an cDomainIntegerBit domain with 8 bits. "<<endl;
					iReturn++;
				}

				//check bounderies
				if ( pVectorDomain->getElementDomain( 0 ) == NULL ){
					cerr<<"The is no 0'th element domain."<<endl;
				}
		
			}else{
				cerr<<"Error: The number of elements of pDomain is "<<
					pVectorDomain->getNumberOfElements() <<" and not 1 ."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The type of pDomain is "<<pDomain->getType() <<
				" and not \"DomainVectorOpenEnd\""<<endl;
			iReturn++;
		}
	}

	//check the getStandardDomain() method from cVectorExtObject
	pDomainStandard = vecExtObjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	if ( typeExtObject6 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject6. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject6 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtObject domains with domain numbers, setting domain number 13"<<endl;
	
	cout<<"extObjectV3rootDom4.setIdentifier( 13 );"<<endl;
	extObjectV3rootDom4.setIdentifier( 13 );

	//check the getDomain() methode from cVectorExtObject
	cout<<"pDomain = vecExtObjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtObjectE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}


	//check the getStandardDomain() method from cVectorExtObject
	pDomainStandard = vecExtObjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	cTypeExtObjectInput typeExtObject13( 13 );
	if ( typeExtObject13 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject13. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject13 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	return iReturn;
}




/**
 * This method tests the method for the domains of the cVectorExtObject class.
 *
 * methods tested:
 * 	- getValueDomain()
 * 	- getStandardDomain()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testValueDomain( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get value domain methods"<<endl;
	
	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	
	//create vector domain with tree elements
	cout<<"vector<cDomainSingle*> vecDomainsE3Nat1Nat2Nat3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3Nat1Nat2Nat3( 3 );
	cout<<"vecDomainsE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Nat1Nat2Nat3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Nat1Nat2Nat3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE3Nat1Nat2Nat3( vecDomainsE3Nat1Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE3Nat1Nat2Nat3( vecDomainsE3Nat1Nat2Nat3 );
	delete vecDomainsE3Nat1Nat2Nat3[ 0 ];
	delete vecDomainsE3Nat1Nat2Nat3[ 1 ];
	delete vecDomainsE3Nat1Nat2Nat3[ 2 ];
	
	cout<<"cTypeExtObjectInput typeExtObject( 0 );"<<endl;
	cTypeExtObjectInput typeExtObject( 0 );

	cout<<"root.getValueDomains()->addDomain( typeExtObject, &vectorDomainE3Nat1Nat2Nat3 );"<<endl;
	root.getValueDomains()->addDomain( typeExtObject, &vectorDomainE3Nat1Nat2Nat3 );

	
	cout<<"cVectorExtObject vecExtObjectRD( 3, &root );"<<endl;
	cVectorExtObject vecExtObjectRD( 3, &root );
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectRD.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the external object element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectRD.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the getValueDomain() methode from cVectorExtObject
	if ( vecExtObjectRD.getValueDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE3Nat1Nat2Nat3 == vecExtObjectRD.getValueDomain() ){
	
		cout<<"The &vectorDomainE3Nat1Nat2Nat3 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The &vectorDomainE3Nat1Nat2Nat3 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}

	/*check the getValueDomain(i=1..n) method of the set-vektor*/
	//test the getType() method
	cout<<"cDomain * pDomainD3 = vecExtObjectRD.getValueDomain();"<<endl;
	cDomain * pDomainD3 = vecExtObjectRD.getValueDomain();
	if ( pDomainD3->getType() == "DomainVector" ){
	
		cout<<"The type of pDomainD3 is correctly \"DomainVector\". "<<endl;

		cDomainVector * pVectorDomainD3 = (cDomainVector*)pDomainD3;
		
		//test the getNumberOfElements() method
		if ( pVectorDomainD3->getNumberOfElements() == 3 ){
		
			cout<<"The number of elements of pDomainD3 is correctly 3. "<<endl;
			
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

	//check the getStandardDomain() method from cVectorExtObject
	cDomain * pDomainStandard = vecExtObjectRD.getStandardDomain();
	cDomain * pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtObject domains with domain numbers"<<endl;
	
	cout<<"cRoot rootDom4;"<<flush<<endl;
	cRoot rootDom4;
	
	cout<<"rootDom4.getDomains()->addDomain( typeExtObject, &vectorDomainE3Nat1Nat2Nat3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject, &vectorDomainE3Nat1Nat2Nat3 );

	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Int2Int3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Int2Int3( 2 );
	cout<<"vecDomainsE2Int2Int3[ 0 ] = new cDomainIntegerBit( 2 );"<<endl;
	vecDomainsE2Int2Int3[ 0 ] = new cDomainIntegerBit( 2 );
	cout<<"vecDomainsE2Int2Int3[ 1 ] = new cDomainIntegerBit( 3 );"<<endl;
	vecDomainsE2Int2Int3[ 1 ] = new cDomainIntegerBit( 3 );
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE2Int2Int3 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE2Int2Int3 );
	delete vecDomainsE2Int2Int3[ 0 ];
	delete vecDomainsE2Int2Int3[ 1 ];
	
	cout<<"cTypeExtObjectInput typeExtObject4( 4 );"<<endl;
	cTypeExtObjectInput typeExtObject4( 4 );
	cout<<"rootDom4.getValueDomains()->addDomain( typeExtObject4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );"<<endl;
	rootDom4.getValueDomains()->addDomain( typeExtObject4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Int4Int5( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Int4Int5( 2 );
	cout<<"vecDomainsE2Int4Int5[ 0 ] = new cDomainIntegerBit( 4 );"<<endl;
	vecDomainsE2Int4Int5[ 0 ] = new cDomainIntegerBit( 4 );
	cout<<"vecDomainsE2Int4Int5[ 1 ] = new cDomainIntegerBit( 5 );"<<endl;
	vecDomainsE2Int4Int5[ 1 ] = new cDomainIntegerBit( 5 );
	cout<<"cDomainVector vectorDomainE2Int4Int5( vecDomainsE2Int4Int5 );"<<endl;
	cDomainVector vectorDomainE2Int4Int5( vecDomainsE2Int4Int5 );
	delete vecDomainsE2Int4Int5[ 0 ];
	delete vecDomainsE2Int4Int5[ 1 ];

	cout<<"cTypeExtObjectInput typeExtObject5( 5 );"<<endl;
	cTypeExtObjectInput typeExtObject5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtObject5, &vectorDomainE2Int4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject5, &vectorDomainE2Int4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"cTypeExtObjectInput typeExtObject6( 6 );"<<endl;
	cTypeExtObjectInput typeExtObject6( 6 );
	cout<<"rootDom4.getValueDomains()->addDomain( typeExtObject6, &vectorDomainOE1Int8 );"<<endl;
	rootDom4.getValueDomains()->addDomain( typeExtObject6, &vectorDomainOE1Int8 );
	
	//create vector domain with
	cout<<"vector<cDomainSingle*> vecDomainsE1Int6( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int6( 1 );
	cout<<"vecDomainsE1Int6[ 0 ] = new cDomainIntegerBit( 6 );"<<endl;
	vecDomainsE1Int6[ 0 ] = new cDomainIntegerBit( 6 );
	cout<<"cDomainVector vectorDomainE1Int6( vecDomainsE1Int6 );"<<endl;
	cDomainVector vectorDomainE1Int6( vecDomainsE1Int6 );
	delete vecDomainsE1Int6[ 0 ];

	cout<<"rootDom4.getDomains()->addDomain( typeExtObject6, &vectorDomainE1Int6 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject6, &vectorDomainE1Int6 );

	
	cout<<"cExtObject extObjectV3rootDom4( 0, 0, &rootDom4 );"<<endl;
	cExtObject extObjectV3rootDom4( 0, 0, &rootDom4 );
	
	cout<<"cVectorExtObject vecExtObjectE3V4Dom5( 2, &extObjectV3rootDom4 );"<<endl;
	cVectorExtObject vecExtObjectE3V4Dom5( 2, &extObjectV3rootDom4 );

	//check the getValueDomain() methode from cVectorExtObject
	cout<<"cDomain * pDomain = vecExtObjectE3V4Dom5.getValueDomain();"<<endl;
	cDomain * pDomain = vecExtObjectE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorExtObject
		if ( &vectorDomainE3Nat1Nat2Nat3 == vecExtObjectRD.getValueDomain() ){
		
			cout<<"The &vectorDomainE3Nat1Nat2Nat3 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The &vectorDomainE3Nat1Nat2Nat3 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the set-vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVector" ){
		
			cout<<"The type of pDomain is correctly \"DomainVector\". "<<endl;

			cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
			
			//test the getNumberOfElements() method
			if ( pVectorDomain->getNumberOfElements() == 3 ){
			
				cout<<"The number of elements of pDomainD3 is correctly 3. "<<endl;
				
			}else{
				cerr<<"Error: The number of elements of pVectorDomain is "<<
					pVectorDomain->getNumberOfElements() <<" and not 3 ."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The type of pDomain is "<<pDomain->getType() <<
				" and not \"DomainVector\""<<endl;
			iReturn++;
		}
	}

	//check the getStandardDomain() method from cVectorExtObject
	pDomainStandard = vecExtObjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	cTypeElement * pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	if ( typeExtObject == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtObject domains with domain numbers, setting domain number 1"<<endl;
	
	cout<<"extObjectV3rootDom4.setIdentifier( 1 );"<<endl;
	extObjectV3rootDom4.setIdentifier( 1 );

	//check the getValueDomain() methode from cVectorExtObject
	cout<<"pDomain = vecExtObjectE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecExtObjectE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain defined for the external object element vector."<<endl;
		iReturn++;
	}

	//check the getStandardDomain() method from cVectorExtObject
	pDomainStandard = vecExtObjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	cTypeExtObjectInput typeExtObject1( 1 );
	if ( typeExtObject1 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject1. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject1 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtObject domains with domain numbers, setting domain number 3"<<endl;
	
	cout<<"extObjectV3rootDom4.setIdentifier( 3 );"<<endl;
	extObjectV3rootDom4.setIdentifier( 3 );

	//check the getValueDomain() methode from cVectorExtObject
	cout<<"pDomain = vecExtObjectE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecExtObjectE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain defined for the external object element vector."<<endl;
		iReturn++;
	}


	//check the getStandardDomain() method from cVectorExtObject
	pDomainStandard = vecExtObjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	cTypeExtObjectInput typeExtObject3( 3 );
	if ( typeExtObject3 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject3. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject3 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtObject domains with domain numbers, setting domain number 4"<<endl;
	
	cout<<"extObjectV3rootDom4.setIdentifier( 4 );"<<endl;
	extObjectV3rootDom4.setIdentifier( 4 );

	//check the getValueDomain() methode from cVectorExtObject
	cout<<"pDomain = vecExtObjectE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecExtObjectE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Na4Nat5VE2NInt2Int3 == *pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VE2NInt2Int3 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VE2NInt2Int3 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorExtObject
		if ( &vectorDomainE3Na4Nat5VE2NInt2Int3 == pDomain ){
		
			cout<<"The &vectorDomainE3Na4Nat5VE2NInt2Int3 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The &vectorDomainE3Na4Nat5VE2NInt2Int3 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the set-vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVector" ){
		
			cout<<"The type of pDomain is correctly \"DomainVector\". "<<endl;

			cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
			
			//test the getNumberOfElements() method
			if ( pVectorDomain->getNumberOfElements() == 2 ){
			
				cout<<"The number of elements of pDomain is correctly 2. "<<endl;
				
			}else{
				cerr<<"Error: The number of elements of pDomain is "<<
					pVectorDomain->getNumberOfElements() <<" and not 2 ."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The type of pDomain is "<<pDomain->getType() <<
				" and not \"DomainVector\""<<endl;
			iReturn++;
		}
	}
	
	//check the getValueDomain() methode from cVectorExtObject
	cout<<"pDomain = vecExtObjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtObjectE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain defined for the external object element vector."<<endl;
		iReturn++;
	}


	//check the getStandardDomain() method from cVectorExtObject
	pDomainStandard = vecExtObjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	if ( typeExtObject4 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject4. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject4 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtObject domains with domain numbers, setting domain number 5"<<endl;
	
	cout<<"extObjectV3rootDom4.setIdentifier( 5 );"<<endl;
	extObjectV3rootDom4.setIdentifier( 5 );

	//check the getValueDomain() methode from cVectorExtObject
	cout<<"pDomain = vecExtObjectE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecExtObjectE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE2Int4Int5 == *pDomain ){
		
			cout<<"The vectorDomainE2Int4Int5 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorExtObject
		if ( &vectorDomainE2Int4Int5 == pDomain ){
		
			cout<<"The &vectorDomainE2Int4Int5 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The &vectorDomainE2Int4Int5 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the set-vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVector" ){
		
			cout<<"The type of pDomain is correctly \"DomainVector\". "<<endl;

			cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
			
			//test the getNumberOfElements() method
			if ( pVectorDomain->getNumberOfElements() == 2 ){
			
				cout<<"The number of elements of pDomain is correctly 2. "<<endl;
				
			}else{
				cerr<<"Error: The number of elements of pDomain is "<<
					pVectorDomain->getNumberOfElements() <<" and not 2 ."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The type of pDomain is "<<pDomain->getType() <<
				" and not \"DomainVector\""<<endl;
			iReturn++;
		}
	}

	//check the getStandardDomain() method from cVectorExtObject
	pDomainStandard = vecExtObjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	if ( typeExtObject5 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject5. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject5 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtObject domains with domain numbers, setting domain number 6"<<endl;
	
	cout<<"extObjectV3rootDom4.setIdentifier( 6 );"<<endl;
	extObjectV3rootDom4.setIdentifier( 6 );

	//check the getValueDomain() methode from cVectorExtObject
	cout<<"pDomain = vecExtObjectE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecExtObjectE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainOE1Int8 == *pDomain ){
		
			cout<<"The vectorDomainOE1Int8 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorExtObject
		if ( &vectorDomainOE1Int8 == pDomain ){
		
			cout<<"The &vectorDomainOE1Int8 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The &vectorDomainOE1Int8 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the set-vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVectorOpenEnd" ){
		
			cout<<"The type of pDomain is correctly \"DomainVectorOpenEnd\". "<<endl;

			cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
			
			//test the getNumberOfElements() method
			if ( pVectorDomain->getNumberOfElements() == 1 ){
			
				cout<<"The number of elements of pDomain is correctly 1. "<<endl;
				
			}else{
				cerr<<"Error: The number of elements of pDomain is "<<
					pVectorDomain->getNumberOfElements() <<" and not 1 ."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The type of pDomain is "<<pDomain->getType() <<
				" and not \"DomainVectorOpenEnd\""<<endl;
			iReturn++;
		}
	}
	//check the getValueDomain() methode from cVectorExtObject
	cout<<"pDomain = vecExtObjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtObjectE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE1Int6 == *pDomain ){
		
			cout<<"The vectorDomainE1Int6 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE1Int6 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorExtObject
		if ( &vectorDomainE1Int6 == pDomain ){
		
			cout<<"The &vectorDomainE1Int6 is the domain for the external object element vector. "<<endl;
		}else{
			cerr<<"Error: The &vectorDomainE1Int6 is not the domain for the external object element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the set-vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVector" ){
		
			cout<<"The type of pDomain is correctly \"DomainVector\". "<<endl;

			cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
			
			//test the getNumberOfElements() method
			if ( pVectorDomain->getNumberOfElements() == 1 ){
			
				cout<<"The number of elements of pDomain is correctly 1. "<<endl;
				
			}else{
				cerr<<"Error: The number of elements of pDomain is "<<
					pVectorDomain->getNumberOfElements() <<" and not 1 ."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The type of pDomain is "<<pDomain->getType() <<
				" and not \"DomainVectorOpenEnd\""<<endl;
			iReturn++;
		}
	}

	//check the getStandardDomain() method from cVectorExtObject
	pDomainStandard = vecExtObjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	if ( typeExtObject6 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject6. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject6 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtObject domains with domain numbers, setting domain number 13"<<endl;
	
	cout<<"extObjectV3rootDom4.setIdentifier( 13 );"<<endl;
	extObjectV3rootDom4.setIdentifier( 13 );

	//check the getValueDomain() methode from cVectorExtObject
	cout<<"pDomain = vecExtObjectE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecExtObjectE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain defined for the external object element vector."<<endl;
		iReturn++;
	}


	//check the getStandardDomain() method from cVectorExtObject
	pDomainStandard = vecExtObjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtObject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtObjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vecExtObjectE3V4Dom5.getElementType();
	cTypeExtObjectInput typeExtObject13( 13 );
	if ( typeExtObject13 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject13. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject13 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtObjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtObjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	return iReturn;
}




/**
 * This method tests setDefiningFibElement() and getDefiningFibElement()
 * method of the cVectorExtObject class.
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

	cout<<"cExtObject definingElement1( 1 );"<<endl;
	cExtObject definingElement1( 1 );
	cout<<"cExtObject definingElement2( 2 );"<<endl;
	cExtObject definingElement2( 2 );
	
	cout<<"cVectorExtObject vecExtObject( 2 );"<<endl;
	cVectorExtObject vecExtObject( 2 );

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObject.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	cout<<"vecExtObject.setDefiningFibElement( &definingElement1 );"<<endl;
	vecExtObject.setDefiningFibElement( &definingElement1 );

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObject.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &definingElement1 == vecExtObject.getDefiningFibElement() ){
	
		cout<<"The definingElement1 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The definingElement1 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}

	cout<<"vecExtObject.setDefiningFibElement( &definingElement2 );"<<endl;
	vecExtObject.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObject.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecExtObject.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}

	cout<<"vecExtObject.setDefiningFibElement( NULL );"<<endl;
	vecExtObject.setDefiningFibElement( NULL );

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObject.getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the external object element vector."<<endl;
		iReturn++;
	}

	cout<<"vecExtObject.setDefiningFibElement( &definingElement2 );"<<endl;
	vecExtObject.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vecExtObject.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecExtObject.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods when a domain is given"<<endl;
	
	cout<<"cRoot rootDom4;"<<flush<<endl;
	cRoot rootDom4;
	
	//create vector domain with tree elements
	cout<<"vector<cDomainSingle*> vecDomainsE3Nat1Nat2Nat3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3Nat1Nat2Nat3( 3 );
	cout<<"vecDomainsE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Nat1Nat2Nat3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Nat1Nat2Nat3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE3Nat1Nat2Nat3( vecDomainsE3Nat1Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE3Nat1Nat2Nat3( vecDomainsE3Nat1Nat2Nat3 );
	delete vecDomainsE3Nat1Nat2Nat3[ 0 ];
	delete vecDomainsE3Nat1Nat2Nat3[ 1 ];
	delete vecDomainsE3Nat1Nat2Nat3[ 2 ];
	
	cout<<"cTypeExtObjectInput typeExtObject( 0 );"<<endl;
	cTypeExtObjectInput typeExtObject( 0 );
	
	cout<<"rootDom4.getDomains()->addDomain( typeExtObject, &vectorDomainE3Nat1Nat2Nat3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject, &vectorDomainE3Nat1Nat2Nat3 );

	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Int2Int3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Int2Int3( 2 );
	cout<<"vecDomainsE2Int2Int3[ 0 ] = new cDomainIntegerBit( 2 );"<<endl;
	vecDomainsE2Int2Int3[ 0 ] = new cDomainIntegerBit( 2 );
	cout<<"vecDomainsE2Int2Int3[ 1 ] = new cDomainIntegerBit( 3 );"<<endl;
	vecDomainsE2Int2Int3[ 1 ] = new cDomainIntegerBit( 3 );
	cout<<"cDomainVector vectorDomainE2Int2Int3( vecDomainsE2Int2Int3 );"<<endl;
	cDomainVector vectorDomainE2Int2Int3( vecDomainsE2Int2Int3 );
	delete vecDomainsE2Int2Int3[ 0 ];
	delete vecDomainsE2Int2Int3[ 1 ];
	
	cout<<"cTypeExtObjectInput typeExtObject4( 4 );"<<endl;
	cTypeExtObjectInput typeExtObject4( 4 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtObject4, &vectorDomainE2Int2Int3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject4, &vectorDomainE2Int2Int3 );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Int4Int5( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Int4Int5( 2 );
	cout<<"vecDomainsE2Int4Int5[ 0 ] = new cDomainIntegerBit( 4 );"<<endl;
	vecDomainsE2Int4Int5[ 0 ] = new cDomainIntegerBit( 4 );
	cout<<"vecDomainsE2Int4Int5[ 1 ] = new cDomainIntegerBit( 5 );"<<endl;
	vecDomainsE2Int4Int5[ 1 ] = new cDomainIntegerBit( 5 );
	cout<<"cDomainVector vectorDomainE2Int4Int5( vecDomainsE2Int4Int5 );"<<endl;
	cDomainVector vectorDomainE2Int4Int5( vecDomainsE2Int4Int5 );
	delete vecDomainsE2Int4Int5[ 0 ];
	delete vecDomainsE2Int4Int5[ 1 ];

	cout<<"cTypeExtObjectInput typeExtObject5( 5 );"<<endl;
	cTypeExtObjectInput typeExtObject5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtObject5, &vectorDomainE2Int4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject5, &vectorDomainE2Int4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"cTypeExtObjectInput typeExtObject6( 6 );"<<endl;
	cTypeExtObjectInput typeExtObject6( 6 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtObject6, &vectorDomainOE1Int8 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtObject6, &vectorDomainOE1Int8 );
	
	
	cout<<"cExtObject extObjectDom0( 0, 2, &rootDom4 );"<<endl;
	cExtObject extObjectDom0( 0, 2, &rootDom4 );
	
	cout<<"cExtObject extObjectDom4( 4, 3, &extObjectDom0 );"<<endl;
	cExtObject extObjectDom4( 4, 3, &extObjectDom0 );

	cout<<"cExtObject extObjectDom5( 5, 4, &extObjectDom4 );"<<endl;
	cExtObject extObjectDom5( 5, 4, &extObjectDom4 );

	cout<<"cExtObject extObjectDom6( 6, 5, &extObjectDom5 );"<<endl;
	cExtObject extObjectDom6( 6, 5, &extObjectDom5 );
	
	cout<<"cExtObject extObjectDom11( 11, 6, &extObjectDom6 );"<<endl;
	cExtObject extObjectDom11( 11, 6, &extObjectDom6 );


	cout<<"cVectorExtObject vecExtObjectE0( 0 );"<<endl;
	cVectorExtObject vecExtObjectE0( 0 );
	
	cout<<"vecExtObjectE0.setDefiningFibElement( &rootDom4 );"<<endl;
	vecExtObjectE0.setDefiningFibElement( &rootDom4 );

	cout<<"cVectorExtObject vecExtObject2E3V0( 3 );"<<endl;
	cVectorExtObject vecExtObject2E3V0( 3 );

	if ( vecExtObjectE0 == vecExtObject2E3V0 ){
	
		cout<<"The external object element vector vecExtObjectE0 is equal to vecExtObject2E3V0. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObjectE0 is not equal to vecExtObject2E3V0."<<endl;
		iReturn++;
	}
	

	cout<<"cVectorExtObject vecExtObject1E3( 3 );"<<endl;
	cVectorExtObject vecExtObject1E3( 3 );
	cout<<"vecExtObject1E3.setValue( 1, 1);"<<endl;
	vecExtObject1E3.setValue( 1, 1);
	cout<<"vecExtObject1E3.setValue( 2, 2);"<<endl;
	vecExtObject1E3.setValue( 2, 2);

	cout<<"cVectorExtObject vecExtObject1E2( 2 );"<<endl;
	cVectorExtObject vecExtObject1E2( 2 );
	cout<<"vecExtObject1E2.setValue( 1, 3);"<<endl;
	vecExtObject1E2.setValue( 1, 3);
	cout<<"vecExtObject1E2.setValue( 2, 2);"<<endl;
	vecExtObject1E2.setValue( 2, 2);

	cout<<"vecExtObject1E2.setDefiningFibElement( &rootDom4 );"<<endl;
	vecExtObject1E2.setDefiningFibElement( &rootDom4 );

	if ( vecExtObject1E2 == vecExtObject1E3 ){
	
		cout<<"The external object element vector vecExtObject1E2 is equal to vecExtObject1E3. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObject1E2 is not equal to vecExtObject1E3."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecExtObject1E2.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecExtObject1E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecExtObject1E2.getValue( uiActualElement ) ==
					vecExtObject1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly "<< 
					vecExtObject1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is "<<vecExtObject1E2.getValue( uiActualElement )<<
					" and not "<< vecExtObject1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}


	cout<<"vecExtObject1E3.setValue( 1, 0);"<<endl;
	vecExtObject1E3.setValue( 1, 0);
	cout<<"vecExtObject1E3.setValue( 2, 1);"<<endl;
	vecExtObject1E3.setValue( 2, 1);

	cout<<"cVectorExtObject vecExtObject2E3( vecExtObject1E3 );"<<endl;
	cVectorExtObject vecExtObject2E3( vecExtObject1E3 );

	cout<<"vecExtObject2E3.setDefiningFibElement( &rootDom4 );"<<endl;
	vecExtObject2E3.setDefiningFibElement( &rootDom4 );


	if ( vecExtObject2E3 == vecExtObject1E3 ){
	
		cout<<"The external object element vector vecExtObject2E3 is equal to vecExtObject1E3. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObject2E3 is not equal to vecExtObject1E3."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecExtObject2E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecExtObject2E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecExtObject2E3.getValue( uiActualElement ) ==
					vecExtObject1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly "<< 
					vecExtObject1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is "<<vecExtObject2E3.getValue( uiActualElement )<<
					" and not "<< vecExtObject1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	cout<<"vecExtObject1E3.setValue( 1, 0);"<<endl;
	vecExtObject1E3.setValue( 1, 0);
	cout<<"vecExtObject1E3.setValue( 2, 3);"<<endl;
	vecExtObject1E3.setValue( 2, 3);
	cout<<"vecExtObject1E3.setValue( 3, 7);"<<endl;
	vecExtObject1E3.setValue( 3, 7);

	cout<<"cVectorExtObject vecExtObject3E3( 3 );"<<endl;
	cVectorExtObject vecExtObject3E3( 3 );
	cout<<"vecExtObject3E3.setValue( 1, -7 );"<<endl;
	vecExtObject3E3.setValue( 1, -7 );
	cout<<"vecExtObject3E3.setValue( 2, 4 );"<<endl;
	vecExtObject3E3.setValue( 2, 4 );
	cout<<"vecExtObject3E3.setValue( 3, 8 );"<<endl;
	vecExtObject3E3.setValue( 3, 8 );

	cout<<"vecExtObject3E3.setDefiningFibElement( &extObjectDom0 );"<<endl;
	vecExtObject3E3.setDefiningFibElement( &extObjectDom0 );

	if ( vecExtObject3E3 == vecExtObject1E3 ){
	
		cout<<"The external object element vector vecExtObject3E3 is equal to vecExtObject1E3. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObject3E3 is not equal to vecExtObject1E3."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecExtObject3E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecExtObject3E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecExtObject3E3.getValue( uiActualElement ) ==
					vecExtObject1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly "<< 
					vecExtObject1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is "<<vecExtObject3E3.getValue( uiActualElement )<<
					" and not "<< vecExtObject1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	
	cout<<"cVectorExtObject vecExtObject2E4( 2 );"<<endl;
	cVectorExtObject vecExtObject2E4( 2 );
	cout<<"vecExtObject2E4.setValue( 1, -2 );"<<endl;
	vecExtObject2E4.setValue( 1, -2 );
	cout<<"vecExtObject2E4.setValue( 2, 3 );"<<endl;
	vecExtObject2E4.setValue( 2, 3 );

	cout<<"cVectorExtObject vecExtObject3E3( 3 );"<<endl;
	cVectorExtObject vecExtObject4E3( 3 );
	cout<<"vecExtObject4E3.setValue( 1, -7 );"<<endl;
	vecExtObject4E3.setValue( 1, -7 );
	cout<<"vecExtObject4E3.setValue( 2, 4 );"<<endl;
	vecExtObject4E3.setValue( 2, 4 );
	cout<<"vecExtObject4E3.setValue( 3, 8 );"<<endl;
	vecExtObject4E3.setValue( 3, 8 );

	cout<<"vecExtObject4E3.setDefiningFibElement( &extObjectDom4 );"<<endl;
	vecExtObject4E3.setDefiningFibElement( &extObjectDom4 );

	if ( vecExtObject4E3 == vecExtObject2E4 ){
	
		cout<<"The external object element vector vecExtObject4E3 is equal to vecExtObject2E4. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObject4E3 is not equal to vecExtObject2E4."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecExtObject4E3.getNumberOfElements();
				uiActualElement++ ){
			
			if ( ! vecExtObject4E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecExtObject4E3.getValue( uiActualElement ) ==
					vecExtObject2E4.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly "<< 
					vecExtObject2E4.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is "<<vecExtObject4E3.getValue( uiActualElement )<<
					" and not "<< vecExtObject2E4.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	
	cout<<"cVectorExtObject vecExtObject1E5( 2 );"<<endl;
	cVectorExtObject vecExtObject1E5( 2 );
	cout<<"vecExtObject1E5.setValue( 1, -7 );"<<endl;
	vecExtObject1E5.setValue( 1, -7 );
	cout<<"vecExtObject1E5.setValue( 2, 4 );"<<endl;
	vecExtObject1E5.setValue( 2, 4 );

	cout<<"cVectorExtObject vecExtObject5E3( 3 );"<<endl;
	cVectorExtObject vecExtObject5E3( 3 );
	cout<<"vecExtObject5E3.setValue( 1, -7 );"<<endl;
	vecExtObject5E3.setValue( 1, -7 );
	cout<<"vecExtObject5E3.setValue( 2, 4 );"<<endl;
	vecExtObject5E3.setValue( 2, 4 );
	cout<<"vecExtObject5E3.setValue( 3, 8 );"<<endl;
	vecExtObject5E3.setValue( 3, 8 );

	cout<<"vecExtObject5E3.setDefiningFibElement( &extObjectDom5 );"<<endl;
	vecExtObject5E3.setDefiningFibElement( &extObjectDom5 );

	if ( vecExtObject5E3 == vecExtObject1E5 ){
	
		cout<<"The external object element vector vecExtObject5E3 is equal to vecExtObject1E5. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObject5E3 is not equal to vecExtObject1E5."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecExtObject5E3.getNumberOfElements();
				uiActualElement++ ){
			
			if ( ! vecExtObject5E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecExtObject5E3.getValue( uiActualElement ) ==
					vecExtObject1E5.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly "<< 
					vecExtObject1E5.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is "<<vecExtObject5E3.getValue( uiActualElement )<<
					" and not "<< vecExtObject1E5.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	
	
	cout<<"cVectorExtObject vecExtObject1E6( 5 );"<<endl;
	cVectorExtObject vecExtObject1E6( 5 );
	cout<<"vecExtObject1E6.setValue( 1, -7 );"<<endl;
	vecExtObject1E6.setValue( 1, -7 );
	cout<<"vecExtObject1E6.setValue( 2, 127 );"<<endl;
	vecExtObject1E6.setValue( 2, 127 );
	cout<<"vecExtObject1E6.setValue( 3, -128 );"<<endl;
	vecExtObject1E6.setValue( 3, -128 );

	cout<<"cVectorExtObject vecExtObject6E3( 3 );"<<endl;
	cVectorExtObject vecExtObject6E3( 3 );
	cout<<"vecExtObject6E3.setValue( 1, -7 );"<<endl;
	vecExtObject6E3.setValue( 1, -7 );
	cout<<"vecExtObject6E3.setValue( 2, 128 );"<<endl;
	vecExtObject6E3.setValue( 2, 128 );
	cout<<"vecExtObject6E3.setValue( 3, -129 );"<<endl;
	vecExtObject6E3.setValue( 3, -129 );

	cout<<"vecExtObject6E3.setDefiningFibElement( &extObjectDom6 );"<<endl;
	vecExtObject6E3.setDefiningFibElement( &extObjectDom6 );

	if ( vecExtObject6E3 == vecExtObject1E6 ){
	
		cout<<"The external object element vector vecExtObject6E3 is equal to vecExtObject1E6. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObject6E3 is not equal to vecExtObject1E6."<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtObject6E3.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtObject1E6.storeXml( cerr );
		
		iReturn++;
	}
	
	
	cout<<"cVectorExtObject vecExtObject1E11( 3 );"<<endl;
	cVectorExtObject vecExtObject1E11( 3 );
	cout<<"vecExtObject1E11.setValue( 1, -7 );"<<endl;
	vecExtObject1E11.setValue( 1, -7 );
	cout<<"vecExtObject1E11.setValue( 2, 128 );"<<endl;
	vecExtObject1E11.setValue( 2, 128 );
	cout<<"vecExtObject1E11.setValue( 3, -129 );"<<endl;
	vecExtObject1E11.setValue( 3, -129 );

	cout<<"cVectorExtObject vecExtObject7E3( 3 );"<<endl;
	cVectorExtObject vecExtObject7E3( 3 );
	cout<<"vecExtObject7E3.setValue( 1, -7 );"<<endl;
	vecExtObject7E3.setValue( 1, -7 );
	cout<<"vecExtObject7E3.setValue( 2, 128 );"<<endl;
	vecExtObject7E3.setValue( 2, 128 );
	cout<<"vecExtObject7E3.setValue( 3, -129 );"<<endl;
	vecExtObject7E3.setValue( 3, -129 );

	cout<<"vecExtObject7E3.setDefiningFibElement( &extObjectDom11 ); (no such domain)"<<endl;
	vecExtObject7E3.setDefiningFibElement( &extObjectDom11 );

	if ( vecExtObject7E3 == vecExtObject1E11 ){
	
		cout<<"The external object element vector vecExtObject7E3 is equal to vecExtObject1E11. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObject7E3 is not equal to vecExtObject1E11."<<endl;
		cerr<<"Changed vector:"<<endl;
		vecExtObject7E3.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtObject1E11.storeXml( cerr );
		
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods when a domain is given, but shouldn't be checked"<<endl;
	
	cout<<"cVectorExtObject vecExtObject2E2( 2 );"<<endl;
	cVectorExtObject vecExtObject2E2( 2 );
	cout<<"vecExtObject2E2.setValue( 1, -58 );"<<endl;
	vecExtObject2E2.setValue( 1, -58 );
	cout<<"vecExtObject2E2.setValue( 2, 1234 );"<<endl;
	vecExtObject2E2.setValue( 2, 1234 );
	
	cVectorExtObject vecExtObject3E2( vecExtObject2E2 );

	cout<<"vecExtObject3E2.setDefiningFibElement( &extObjectDom5, false );"<<endl;
	vecExtObject3E2.setDefiningFibElement( &extObjectDom5, false );

	if ( vecExtObject3E2 == vecExtObject2E2 ){
	
		cout<<"The external object element vector vecExtObject3E2 is equal to vecExtObject2E2. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObject3E2 is not equal to vecExtObject2E2."<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtObject3E2.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtObject2E2.storeXml( cerr );
		iReturn++;
	}

	cout<<"cVectorExtObject vecExtObject8E3( 3 );"<<endl;
	cVectorExtObject vecExtObject8E3( 3 );
	cout<<"vecExtObject8E3.setValue( 1, -200 );"<<endl;
	vecExtObject8E3.setValue( 1, -200 );
	cout<<"vecExtObject8E3.setValue( 2, 4 );"<<endl;
	vecExtObject8E3.setValue( 2, 4 );
	cout<<"vecExtObject8E3.setValue( 3, 500 );"<<endl;
	vecExtObject8E3.setValue( 3, 500 );
	
	cVectorExtObject vecExtObject9E3( vecExtObject8E3 );

	cout<<"vecExtObject9E3.setDefiningFibElement( &extObjectDom5, false );"<<endl;
	vecExtObject9E3.setDefiningFibElement( &extObjectDom5, false );

	if ( vecExtObject9E3 == vecExtObject8E3 ){
	
		cout<<"The external object element vector vecExtObject9E3 is equal to vecExtObject8E3. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObject9E3 is not equal to vecExtObject8E3."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecExtObject9E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecExtObject9E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecExtObject9E3.getValue( uiActualElement ) ==
					vecExtObject8E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly "<< 
					vecExtObject8E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is "<<vecExtObject9E3.getValue( uiActualElement )<<
					" and not "<< vecExtObject8E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests cVectorExtObject methods for manipulating the
 * vectorelements.
 *
 * methods tested:
 * 	- setValue()
 * 	- getValue()
 * 	- setVariable()
 * 	- getVariable()
 * 	- isVariable()
 * 	- void resize( unsigned int uiNumberOfVectorElements );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testVectorElements( unsigned long &ulTestphase ){

	int iReturn=0;//return value of the test; the number of occured errors

//TODO test if yust values of the domain can be set

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing methods for getting the vectorelementdata"<<endl;
	
	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;
	
	cout<<"cVectorExtObject vecExtObject( 3, &emptyRoot );"<<endl;
	cVectorExtObject vecExtObject( 3, &emptyRoot );

	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtObject.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtObject.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtObject.getValue( uiActualElement ) == (doubleFib)(0.0) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtObject.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
		if ( vecExtObject.getVariable( uiActualElement ) == NULL ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly no variable . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable . "<<endl;
			iReturn++;
		}
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setValue() method"<<endl;

	cout<<"vecExtObject.setValue( 2, 2.2 )"<<endl;
	if ( vecExtObject.setValue( 2, 2.2 ) ){
	
		cout<<"The 2'th element of the external object element vector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecExtObject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObject.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the external object element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecExtObject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 2 ) == (doubleFib)(2.2) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 2.2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObject.getValue( 2 )<<" and not 2.2 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the external object element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecExtObject.setValue( 2, 0.7 )"<<endl;
	if ( vecExtObject.setValue( 2, 0.7 ) ){
	
		cout<<"The 2'th element of the external object element vector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecExtObject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObject.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the external object element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecExtObject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObject.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the external object element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecExtObject.setValue( 1, 11 )"<<endl;
	if ( vecExtObject.setValue( 1, 11 ) ){
	
		cout<<"The 1'th element of the external object element vector is set. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecExtObject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 1 ) == (doubleFib)(11) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObject.getValue( 1 )<<" and not 11 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the external object element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecExtObject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObject.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the external object element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable . "<<endl;
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
	cout<<endl<<"vecExtObject.setVariable( 1, pVariable1 )"<<endl;
	if ( vecExtObject.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the external object element vector is set to the variable 1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not set to the variable 1. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecExtObject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 1 ) == (doubleFib)(0) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObject.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecExtObject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObject.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the external object element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable1->setValue( 0.11 );"<<endl;
	pVariable1->setValue( 0.11 );
	
	if ( vecExtObject.getValue( 1 ) == (doubleFib)(0.11) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 0.11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObject.getValue( 1 )<<" and not 0.11 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable1->setValue( 111 );"<<endl;
	pVariable1->setValue( 111 );
	
	if ( vecExtObject.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObject.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4 = emptyRoot.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable4 = emptyRoot.getInputVariable( 4 );
	cout<<endl<<"vecExtObject.setVariable( 2, pVariable4 )"<<endl;
	if ( vecExtObject.setVariable( 2, pVariable4 ) ){
	
		cout<<"The 2'th element of the external object element vector is set to the variable 4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not set to the variable 4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecExtObject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObject.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecExtObject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 2 ) == (doubleFib)(0.0) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObject.getValue( 2 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 123 );"<<endl;
	pVariable4->setValue( 123 );
	
	if ( vecExtObject.getValue( 2 ) == (doubleFib)(123) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 123 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObject.getValue( 2 )<<" and not 123 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 0.321 );"<<endl;
	pVariable4->setValue( 0.321  );
	
	if ( vecExtObject.getValue( 2 ) == (doubleFib)(0.321 ) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 0.321  . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObject.getValue( 2 )<<" and not 0.321  . "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecExtObject.setVariable( 1, pVariable4 )"<<endl;
	if ( vecExtObject.setVariable( 1, pVariable4 ) ){
	
		cout<<"The 1'th element of the external object element vector is set to the variable 4. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not set to the variable 4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecExtObject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 1 ) == (doubleFib)(0.321) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 0.321 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObject.getValue( 1 )<<" and not 0.321 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 1 ) == pVariable4 ){
	
		cout<<"The 1'th element of the external object element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecExtObject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 2 ) == (doubleFib)(0.321) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 0.321 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObject.getValue( 2 )<<" and not 0.321 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 654.123 );"<<endl;
	pVariable4->setValue( 654.123 );
	
	if ( vecExtObject.getValue( 1 ) == (doubleFib)(654.123) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 654.123 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObject.getValue( 1 )<<" and not 654.123 . "<<endl;
		iReturn++;
	}
	
	if ( vecExtObject.getValue( 2 ) == (doubleFib)(654.123) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 654.123 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObject.getValue( 2 )<<" and not 654.123 . "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setValue() and setVariable() after each other method"<<endl;
	
	cout<<endl<<"vecExtObject.setValue( 1, 17 )"<<endl;
	if ( vecExtObject.setValue( 1, 17 ) ){
	
		cout<<"The 1'th element of the external object element vector is set to the value 17"<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not set to the value 17. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecExtObject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 1 ) == (doubleFib)(17) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 17 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObject.getValue( 1 )<<" and not 17 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecExtObject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 2 ) == (doubleFib)(654.123 ) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 654.123  . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObject.getValue( 2 )<<" and not 654.123  . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 65 );"<<endl;
	pVariable4->setValue( 65 );
	
	if ( vecExtObject.getValue( 2 ) == (doubleFib)(65) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObject.getValue( 2 )<<" and not 65 . "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecExtObject.setVariable( 1, pVariable1 )"<<endl;
	if ( vecExtObject.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the external object element vector is set to the varaiable 1"<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not set to the variable 1. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecExtObject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObject.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecExtObject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 2 ) == (doubleFib)(65 ) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObject.getValue( 2 )<<" and not 65  . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setVariable() methods with trying to set NULL"<<endl;
	
	cout<<endl<<"vecExtObject.setVariable( 1, NULL )"<<endl;
	if ( ! vecExtObject.setVariable( 1, NULL ) ){
	
		cout<<"The 1'th element of the external object element vector couldn't be set to NULL."<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector could be set to NULL. "<<endl;
		iReturn++;
	}
	cout<<endl<<"vecExtObject.setVariable( 2, NULL )"<<endl;
	if ( ! vecExtObject.setVariable( 2, NULL ) ){
	
		cout<<"The 2'th element of the external object element vector couldn't be set to NULL."<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector could be set to NULL. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecExtObject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtObject.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecExtObject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getValue( 2 ) == (doubleFib)(65 ) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtObject.getValue( 2 )<<" and not 65  . "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing replaceVariable(), isUsedVariable() and set<cFibVariable*> getUsedVariables() methods"<<endl;
	
	cout<<endl<<"pVariable2 = emptyRoot.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = emptyRoot.getInputVariable( 2 );
	cout<<endl<<"pVariable3 = emptyRoot.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = emptyRoot.getInputVariable( 3 );
	
	//check vecExtObject.isUsedVariable()
	if ( vecExtObject.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecExtObject.isUsedVariable()
	if ( ! vecExtObject.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check isUsedVariable()
	if ( vecExtObject.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	
	set<cFibVariable*> setCorrectUsedVariables;
	setCorrectUsedVariables.insert( pVariable1 );
	setCorrectUsedVariables.insert( pVariable4 );
	//check getUsedVariables()
	cout<<"setUsedVariables = vecExtObject.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = vecExtObject.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	
	cout<<endl<<"vecExtObject.replaceVariable( pVariable1, pVariable4 )"<<endl;
	setCorrectUsedVariables.erase( pVariable1 );
	if ( vecExtObject.replaceVariable( pVariable1, pVariable4 ) ){
	
		cout<<"The pVariable1 of the propertyvector was replaced with pVariable4. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 of the propertyvector was not replaced with pVariable4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecExtObject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 1 ) == pVariable4 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecExtObject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check vecExtObject.isUsedVariable()
	if ( ! vecExtObject.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecExtObject.isUsedVariable()
	if ( ! vecExtObject.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecExtObject.isUsedVariable()
	if ( vecExtObject.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecExtObject.getUsedVariables(); "<<endl;
	setUsedVariables = vecExtObject.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecExtObject.replaceVariable( pVariable1, pVariable3 )"<<endl;
	if ( vecExtObject.replaceVariable( pVariable1, pVariable3 ) ){
	
		cout<<"The pVariable1 of the propertyvector was replaced with pVariable3. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 of the propertyvector was not replaced with pVariable3. "<<endl;
		iReturn++;
	}
	//check vecExtObject.isUsedVariable()
	if ( ! vecExtObject.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecExtObject.isUsedVariable()
	if ( vecExtObject.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecExtObject.getUsedVariables(); "<<endl;
	setUsedVariables = vecExtObject.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	cout<<endl<<"vecExtObject.replaceVariable( pVariable4, pVariable2 )"<<endl;
	setCorrectUsedVariables.erase( pVariable4 );
	setCorrectUsedVariables.insert( pVariable2 );
	if ( vecExtObject.replaceVariable( pVariable4, pVariable2 ) ){
	
		cout<<"The pVariable4 of the propertyvector was replaced with pVariable2. "<<endl;
	}else{
		cerr<<"Error: The pVariable4 of the propertyvector was not replaced with pVariable2. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecExtObject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 1 ) == pVariable2 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecExtObject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtObject.getVariable( 2 ) == pVariable2 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check vecExtObject.isUsedVariable()
	if ( ! vecExtObject.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecExtObject.isUsedVariable()
	if ( vecExtObject.isUsedVariable( pVariable2 ) ){
	
		cout<<"The pVariable2 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable2 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecExtObject.isUsedVariable()
	if ( ! vecExtObject.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecExtObject.isUsedVariable()
	if ( ! vecExtObject.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable4 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecExtObject.getUsedVariables(); "<<endl;
	setUsedVariables = vecExtObject.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	//check vecExtObject.isUsedVariable()
	if ( ! vecExtObject.isUsedVariable( NULL ) ){
	
		cout<<"The NULL is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The NULL is a used varible in the vector.  "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecExtObject.replaceVariable( NULL, pVariable2 )"<<endl;
	if ( ! vecExtObject.replaceVariable( NULL, pVariable2 ) ){
	
		cout<<"Can't correctly replace NULL of the propertyvector with pVariable2. "<<endl;
	}else{
		cerr<<"Error: Can replace NULL of the propertyvector with pVariable2. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecExtObject.replaceVariable( pVariable2, NULL )"<<endl;
	if ( ! vecExtObject.replaceVariable( pVariable2, NULL ) ){
	
		cout<<"Can't correctly replace pVariable2 of the propertyvector with NULL. "<<endl;
	}else{
		cerr<<"Error: Can replace pVariable2 of the propertyvector with NULL. "<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing resize() method"<<endl;
	
	cout<<"cVectorExtObject vecExtObjectResize1( 3 );"<<endl;
	cVectorExtObject vecExtObjectResize1( 3 );
	cout<<"vecExtObjectResize1.setValue( 1, -200 );"<<endl;
	vecExtObjectResize1.setValue( 1, -200 );
	cout<<"vecExtObjectResize1.setValue( 2, 4 );"<<endl;
	vecExtObjectResize1.setValue( 2, 4 );
	cout<<"vecExtObjectResize1.setValue( 3, 500 );"<<endl;
	vecExtObjectResize1.setValue( 3, 500 );
	
	cout<<"vecExtObjectResize1.resize( 5 );"<<endl;
	vecExtObjectResize1.resize( 5 );
	
	cVectorExtObject vecExtObjectResize1Correct1( 5 );
	vecExtObjectResize1Correct1.setValue( 1, -200 );
	vecExtObjectResize1Correct1.setValue( 2, 4 );
	vecExtObjectResize1Correct1.setValue( 3, 500 );
	
	if ( vecExtObjectResize1 == vecExtObjectResize1Correct1 ){
	
		cout<<"The external object element vector vecExtObjectResize1 is correctly resized. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObjectResize1 is not correctly resized. "<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtObjectResize1.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtObjectResize1Correct1.storeXml( cerr );
		iReturn++;
	}

	cout<<"vecExtObjectResize1.resize( 1 );"<<endl;
	vecExtObjectResize1.resize( 1 );
	
	cVectorExtObject vecExtObjectResize1Correct2( 1 );
	vecExtObjectResize1Correct2.setValue( 1, -200 );
	
	if ( vecExtObjectResize1 == vecExtObjectResize1Correct2 ){
	
		cout<<"The external object element vector vecExtObjectResize1 is correctly resized. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObjectResize1 is not correctly resized. "<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtObjectResize1.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtObjectResize1Correct2.storeXml( cerr );
		iReturn++;
	}

	cout<<"vecExtObjectResize1.resize( 0 );"<<endl;
	vecExtObjectResize1.resize( 0 );
	
	cVectorExtObject vecExtObjectResize1Correct3( 0 );
	
	if ( vecExtObjectResize1 == vecExtObjectResize1Correct3 ){
	
		cout<<"The external object element vector vecExtObjectResize1 is correctly resized. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObjectResize1 is not correctly resized. "<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtObjectResize1.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtObjectResize1Correct3.storeXml( cerr );
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing resize() method with vector with just variables"<<endl;
	
	cout<<"cVectorExtObject vecExtObjectResize2( 3 );"<<endl;
	cVectorExtObject vecExtObjectResize2( 3 );
	cout<<"vecExtObjectResize2.setVariable( 1, pVariable1 );"<<endl;
	vecExtObjectResize2.setVariable( 1, pVariable1 );
	cout<<"vecExtObjectResize2.setVariable( 2, pVariable3 );"<<endl;
	vecExtObjectResize2.setVariable( 2, pVariable3 );
	cout<<"vecExtObjectResize2.setVariable( 3, pVariable1 );"<<endl;
	vecExtObjectResize2.setVariable( 3, pVariable1 );
	
	cout<<"vecExtObjectResize2.resize( 5 );"<<endl;
	vecExtObjectResize2.resize( 5 );
	
	cVectorExtObject vecExtObjectResize2Correct1( 5 );
	vecExtObjectResize2Correct1.setVariable( 1, pVariable1 );
	vecExtObjectResize2Correct1.setVariable( 2, pVariable3 );
	vecExtObjectResize2Correct1.setVariable( 3, pVariable1 );
	
	if ( vecExtObjectResize2 == vecExtObjectResize2Correct1 ){
	
		cout<<"The external object element vector vecExtObjectResize2 is correctly resized. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObjectResize2 is not correctly resized. "<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtObjectResize2.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtObjectResize2Correct1.storeXml( cerr );
		iReturn++;
	}

	cout<<"vecExtObjectResize2.resize( 1 );"<<endl;
	vecExtObjectResize2.resize( 1 );
	
	cVectorExtObject vecExtObjectResize2Correct2( 1 );
	vecExtObjectResize2Correct2.setVariable( 1, pVariable1 );
	
	if ( vecExtObjectResize2 == vecExtObjectResize2Correct2 ){
	
		cout<<"The external object element vector vecExtObjectResize2 is correctly resized. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObjectResize2 is not correctly resized. "<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtObjectResize2.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtObjectResize2Correct2.storeXml( cerr );
		iReturn++;
	}

	cout<<"vecExtObjectResize2.resize( 0 );"<<endl;
	vecExtObjectResize2.resize( 0 );
	
	cVectorExtObject vecExtObjectResize2Correct3( 0 );
	
	if ( vecExtObjectResize2 == vecExtObjectResize2Correct3 ){
	
		cout<<"The external object element vector vecExtObjectResize2 is correctly resized. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtObjectResize2 is not correctly resized. "<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtObjectResize2.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtObjectResize2Correct3.storeXml( cerr );
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
	
	int iReturn = 0;//return value of the test; the number of occured errors
	
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
	
	int iReturn = 0;//return value of the test; the number of occured errors
	
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

	int iReturn=0;//return value of the test; the number of occured errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equal method and the operator== "<<endl;

	cout<<endl<<"creating vectors to compare:"<<endl<<endl;
	
	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;
	
	//creat defined variables to set them later in the vector
	cout<<"emptyRoot.setNumberOfInputVariables( 2 )"<<endl;
	emptyRoot.setNumberOfInputVariables( 2 );

	cout<<"cExtObject extObjectEmptyRoot( 3, 2, &emptyRoot );"<<endl;
	cExtObject extObjectEmptyRoot( 3, 2, &emptyRoot );

	//create vector domain with two elements
	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	cout<<"rootD2.setNumberOfInputVariables( 2 )"<<endl;
	rootD2.setNumberOfInputVariables( 2 );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat4Nat5( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat4Nat5( 2 );
	cout<<"vecDomainsE2Nat4Nat5[ 0 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE2Nat4Nat5[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE2Nat4Nat5[ 1 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE2Nat4Nat5[ 1 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"cDomainVector vectorDomainE2Nat4Nat5( vecDomainsE2Nat4Nat5 );"<<endl;
	cDomainVector vectorDomainE2Nat4Nat5( vecDomainsE2Nat4Nat5 );
	delete vecDomainsE2Nat4Nat5[ 0 ];
	delete vecDomainsE2Nat4Nat5[ 1 ];
	
	cout<<"cTypeExtObjectInput typeExtObject( 0 );"<<endl;
	cTypeExtObjectInput typeExtObject( 0 );

	cout<<"rootD2.getDomains()->addDomain( typeExtObject, vectorDomainE2Nat4Nat5 );"<<endl;
	rootD2.getDomains()->addDomain( typeExtObject, vectorDomainE2Nat4Nat5 );

	//creat defined variables to set them later in the vector
	cout<<"rootD2.setNumberOfInputVariables( 4 )"<<endl;
	rootD2.setNumberOfInputVariables( 4 );

	cout<<"cExtObject extObjectRootD2( 4, 3, &rootD2 );"<<endl;
	cExtObject extObjectRootD2( 4, 3, &rootD2 );

	//create cVectorExtObjects to compare
	cout<<"cVectorExtObject vectorExtObjectE3( 3 );"<<endl;
	cVectorExtObject vectorExtObjectE3( 3 );
	cout<<"cVectorExtObject vectorExtObjectE3RD2( 3, &rootD2 );"<<endl;
	cVectorExtObject vectorExtObjectE3RD2( 3, &rootD2 );
	cout<<"cVectorExtObject vectorExtObjectE2Re( 2, &extObjectEmptyRoot );"<<endl;
	cVectorExtObject vectorExtObjectE2Re( 2, &extObjectEmptyRoot );
	cout<<"cVectorExtObject vectorExtObjectE2RD2( 2, &rootD2 );"<<endl;
	cVectorExtObject vectorExtObjectE2RD2( 2, &rootD2 );
	cout<<"cVectorExtObject vectorExtObjectRD2( extObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectRD2( extObjectRootD2 );
	
	//vectors with changed values
	cout<<"cVectorExtObject vectorExtObjectRD2V2g17p2( 2, &extObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectRD2V2g17p2( 2, &extObjectRootD2 );
	vectorExtObjectRD2V2g17p2.setValue( 2, 17.2 );
	
	cout<<"cVectorExtObject vectorExtObjectE2RD2V2g17p2( 2, &rootD2 );"<<endl;
	cVectorExtObject vectorExtObjectE2RD2V2g17p2( 2, &rootD2 );
	vectorExtObjectE2RD2V2g17p2.setValue( 2, 17.2 );

	cout<<"cVectorExtObject vectorExtObjectE2RD2V2g17p2001( 2, &rootD2 );"<<endl;
	cVectorExtObject vectorExtObjectE2RD2V2g17p2001( 2, &rootD2 );
	vectorExtObjectE2RD2V2g17p2001.setValue( 2, 17.2001 );

	cout<<"cVectorExtObject vectorExtObjectRD2V1g17p2( 2, &extObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectRD2V1g17p2( 2, &extObjectRootD2 );
	vectorExtObjectRD2V1g17p2.setValue( 1, 17.2 );

	cout<<"cVectorExtObject vectorExtObjectRD2V1g1p1V2gm2p2( 2, &extObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectRD2V1g1p1V2gm2p2( 2, &extObjectRootD2 );
	vectorExtObjectRD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorExtObjectRD2V1g1p1V2gm2p2.setValue( 2, -2.2 );

	cout<<"cVectorExtObject vectorExtObjectE2RD2V1g1p1V2gm2p2( 2, &rootD2 );"<<endl;
	cVectorExtObject vectorExtObjectE2RD2V1g1p1V2gm2p2( 2, &rootD2 );
	vectorExtObjectE2RD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorExtObjectE2RD2V1g1p1V2gm2p2.setValue( 2, -2.2 );
	
	cout<<"cVectorExtObject vectorExtObjectRD2V1g1p1V2g2p2( 2, &extObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectRD2V1g1p1V2g2p2( 2, &extObjectRootD2 );
	vectorExtObjectRD2V1g1p1V2g2p2.setValue( 1, 1.1 );
	vectorExtObjectRD2V1g1p1V2g2p2.setValue( 2, 2.2 );

	//vectors with variables
	cFibVariable * pVariable1 = rootD2.getInputVariable( 1 );
	cFibVariable * pVariable2 = rootD2.getInputVariable( 2 );
	cFibVariable * pVariable1Re = emptyRoot.getInputVariable( 1 );
	//cFibVariable * pVariable2Re = emptyRoot.getInputVariable( 2 );

	cout<<"cVectorExtObject vectorExtObjectRD2V1gV1( 2, &extObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectRD2V1gV1( 2, &extObjectRootD2 );
	vectorExtObjectRD2V1gV1.setVariable( 1, pVariable1 );

	cout<<"cVectorExtObject vectorExtObjectE2RD2V1gV1( 2, &rootD2 );"<<endl;
	cVectorExtObject vectorExtObjectE2RD2V1gV1( 2, &rootD2 );
	vectorExtObjectE2RD2V1gV1.setVariable( 1, pVariable1 );

	cout<<"cVectorExtObject vectorExtObjectRD2V2gV1( 2, &extObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectRD2V2gV1( 2, &extObjectRootD2 );
	vectorExtObjectRD2V2gV1.setVariable( 2, pVariable1 );

	cout<<"cVectorExtObject vectorExtObjectRD2V2gV2( 2, &extObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectRD2V2gV2( 2, &extObjectRootD2 );
	vectorExtObjectRD2V2gV2.setVariable( 2, pVariable2 );

	cout<<"cVectorExtObject vectorExtObjectRD2V1gReV1( 2, &extObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectRD2V1gReV1( 2, &extObjectRootD2 );
	vectorExtObjectRD2V1gReV1.setVariable( 1, pVariable1Re );

	//vectors with changed values and variables
	cout<<"cVectorExtObject vectorExtObjectRD2V1gV1V2g1111( 2, &extObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectRD2V1gV1V2g1111( 2, &extObjectRootD2 );
	vectorExtObjectRD2V1gV1V2g1111.setVariable( 1, pVariable1 );
	vectorExtObjectRD2V1gV1V2g1111.setValue( 2, 1111 );

	cout<<"cVectorExtObject vectorExtObjectE2RD2V1gV1V2g1111( 2, &rootD2 );"<<endl;
	cVectorExtObject vectorExtObjectE2RD2V1gV1V2g1111( 2, &rootD2 );
	vectorExtObjectE2RD2V1gV1V2g1111.setVariable( 1, pVariable1 );
	vectorExtObjectE2RD2V1gV1V2g1111.setValue( 2, 1111 );

	cout<<"cVectorExtObject vectorExtObjectRD2V1gV1V2g111( 2, &extObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectRD2V1gV1V2g111( 2, &extObjectRootD2 );
	vectorExtObjectRD2V1gV1V2g111.setVariable( 1, pVariable1 );
	vectorExtObjectRD2V1gV1V2g111.setValue( 2, 111 );

	cout<<"cVectorExtObject vectorExtObjectRD2V1gV2V1g1111( 2, &rootD2 );"<<endl;
	cVectorExtObject vectorExtObjectRD2V1g111V2gV2( 2, &rootD2 );
	vectorExtObjectRD2V1g111V2gV2.setVariable( 1, pVariable2 );
	vectorExtObjectRD2V1g111V2gV2.setValue( 2, 1111 );

	cout<<"cVectorExtObject vectorExtObjectE2RD2V1g1111V2gV2( 2, &extObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectE2RD2V1gV2V2g1111( 2, &extObjectRootD2 );
	vectorExtObjectE2RD2V1gV2V2g1111.setValue( 1, 1111 );
	vectorExtObjectE2RD2V1gV2V2g1111.setVariable( 2, pVariable1 );

	cout<<"cVectorExtObject vectorExtObjectE2RD2V1gV1V2gV2( 2, &extObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectE2RD2V1gV1V2gV2( 2, &extObjectRootD2 );
	vectorExtObjectE2RD2V1gV1V2gV2.setVariable( 1, pVariable1 );
	vectorExtObjectE2RD2V1gV1V2gV2.setVariable( 2, pVariable2 );

	
	//check variable from different defining element

	cout<<"cExtObject extObjectExtObjectRootD2( 1, 2, &extObjectRootD2 );"<<endl;
	cExtObject extObjectExtObjectRootD2( 1, 2, &extObjectRootD2 );
	
	cout<<"extObjectExtObjectRootD2.setNumberOfSubobjects( 1 );"<<endl;
	extObjectExtObjectRootD2.setNumberOfSubobjects( 1 );
	cout<<"extObjectExtObjectRootD2.setNumberOfOutputVariables( 1, 2 );"<<endl;
	extObjectExtObjectRootD2.setNumberOfOutputVariables( 1, 2 );
	
	cout<<"cVectorExtObject vectorExtObjectE2FS2V1gV1V2gV2( 2, &extObjectExtObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectE2FS2V1gV1V2gV2( 2, &extObjectExtObjectRootD2 );
	vectorExtObjectE2FS2V1gV1V2gV2.setVariable( 1, pVariable1 );
	vectorExtObjectE2FS2V1gV1V2gV2.setVariable( 2, extObjectExtObjectRootD2.getOutputVariable( 1, 1 ) );

	cout<<"cVectorExtObject vectorExtObjectE2FS22V1gV1V2gVFS2( 2, &extObjectExtObjectRootD2 );"<<endl;
	cVectorExtObject vectorExtObjectE2FS22V1gV1V2gVFS2( 2, &extObjectExtObjectRootD2 );
	vectorExtObjectE2FS22V1gV1V2gVFS2.setVariable( 1, pVariable2 );
	vectorExtObjectE2FS22V1gV1V2gVFS2.setVariable( 2, pVariable1 );
	
	
	cout<<"cVectorProperty vectorProperty( 1 );"<<endl;
	cVectorProperty vectorProperty( 1 );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with vectorExtObjectE3
	cFibVector * actualVector = &vectorExtObjectE3;
	string szActualVectorName = "vectorExtObjectE3";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectE3RD2
	actualVector = &vectorExtObjectE3RD2;
	szActualVectorName = "vectorExtObjectE3RD2";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectE2Re
	actualVector = &vectorExtObjectE2Re;
	szActualVectorName = "vectorExtObjectE2Re";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );
	
	//compare with vectorExtObjectE2RD2
	actualVector = &vectorExtObjectE2RD2;
	szActualVectorName = "vectorExtObjectE2RD2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );
	
	//compare with vectorExtObjectE2Re
	actualVector = &vectorExtObjectRD2;
	szActualVectorName = "vectorExtObjectRD2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectRD2V2g17p2
	actualVector = &vectorExtObjectRD2V2g17p2;
	szActualVectorName = "vectorExtObjectRD2V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectRD2V2g17p2
	actualVector = &vectorExtObjectE2RD2V2g17p2;
	szActualVectorName = "vectorExtObjectE2RD2V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectE2RD2V2g17p2001
	actualVector = &vectorExtObjectE2RD2V2g17p2001;
	szActualVectorName = "vectorExtObjectE2RD2V2g17p2001";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectE2RD2V2g17p2001
	actualVector = &vectorExtObjectRD2V1g17p2;
	szActualVectorName = "vectorExtObjectRD2V1g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectRD2V1g1p1V2gm2p2
	actualVector = &vectorExtObjectRD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorExtObjectRD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectE2RD2V1g1p1V2gm2p2
	actualVector = &vectorExtObjectE2RD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorExtObjectE2RD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectE2RD2V1g1p1V2gm2p2
	actualVector = &vectorExtObjectRD2V1g1p1V2g2p2;
	szActualVectorName = "vectorExtObjectRD2V1g1p1V2g2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectRD2V1gV1
	actualVector = &vectorExtObjectRD2V1gV1;
	szActualVectorName = "vectorExtObjectRD2V1gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectE2RD2V1gV1
	actualVector = &vectorExtObjectE2RD2V1gV1;
	szActualVectorName = "vectorExtObjectE2RD2V1gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectRD2V2gV1
	actualVector = &vectorExtObjectRD2V2gV1;
	szActualVectorName = "vectorExtObjectRD2V2gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectRD2V2gV2
	actualVector = &vectorExtObjectRD2V2gV2;
	szActualVectorName = "vectorExtObjectRD2V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectRD2V1gReV1
	actualVector = &vectorExtObjectRD2V1gReV1;
	szActualVectorName = "vectorExtObjectRD2V1gReV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectRD2V1gV1V2g1111
	actualVector = &vectorExtObjectRD2V1gV1V2g1111;
	szActualVectorName = "vectorExtObjectRD2V1gV1V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectE2RD2V1gV1V2g1111
	actualVector = &vectorExtObjectE2RD2V1gV1V2g1111;
	szActualVectorName = "vectorExtObjectE2RD2V1gV1V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectRD2V1gV1V2g111
	actualVector = &vectorExtObjectRD2V1gV1V2g111;
	szActualVectorName = "vectorExtObjectRD2V1gV1V2g111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectRD2V1g111V2gV2
	actualVector = &vectorExtObjectRD2V1g111V2gV2;
	szActualVectorName = "vectorExtObjectRD2V1g111V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectE2RD2V1gV2V2g1111
	actualVector = &vectorExtObjectE2RD2V1gV2V2g1111;
	szActualVectorName = "vectorExtObjectE2RD2V1gV2V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectE2RD2V1gV1V2gV2
	actualVector = &vectorExtObjectE2RD2V1gV1V2gV2;
	szActualVectorName = "vectorExtObjectE2RD2V1gV1V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectE2FS2V1gV1V2gV2
	actualVector = &vectorExtObjectE2FS2V1gV1V2gV2;
	szActualVectorName = "vectorExtObjectE2FS2V1gV1V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtObjectE2FS22V1gV1V2gVFS2
	actualVector = &vectorExtObjectE2FS22V1gV1V2gVFS2;
	szActualVectorName = "vectorExtObjectE2FS22V1gV1V2gVFS2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorProperty
	actualVector = &vectorProperty;
	szActualVectorName = "vectorProperty";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3, "vectorExtObjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE3RD2, "vectorExtObjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2Re, "vectorExtObjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2, "vectorExtObjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2, "vectorExtObjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2g17p2, "vectorExtObjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2, "vectorExtObjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V2g17p2001, "vectorExtObjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g17p2, "vectorExtObjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2gm2p2, "vectorExtObjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1g1p1V2gm2p2, "vectorExtObjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g1p1V2g2p2, "vectorExtObjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1, "vectorExtObjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1, "vectorExtObjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV1, "vectorExtObjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V2gV2, "vectorExtObjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gReV1, "vectorExtObjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g1111, "vectorExtObjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2g1111, "vectorExtObjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1gV1V2g111, "vectorExtObjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectRD2V1g111V2gV2, "vectorExtObjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV2V2g1111, "vectorExtObjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2RD2V1gV1V2gV2, "vectorExtObjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS2V1gV1V2gV2, "vectorExtObjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtObjectE2FS22V1gV1V2gVFS2, "vectorExtObjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );


	return iReturn;
}



/**
 * This method tests the createInstance() method of the cVectorExtObject class.
 *
 * methods tested:
 * 	- createInstance()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCreateInstance( unsigned long &ulTestphase ){

	int iReturn=0;//return value of the test; the number of occured errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 1 element"<<endl;

	
	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Nat1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Nat1( 1 );
	cout<<"vecDomainsE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE1Nat1 );
	delete vecDomainsE1Nat1[ 0 ];
	
	cout<<"cTypeExtObjectInput typeExtObject( 0 );"<<endl;
	cTypeExtObjectInput typeExtObject( 0 );
	
	cout<<"rootD2.getDomains()->addDomain( typeExtObject, vectorDomainE3Na2Nat3VE1Nat1 );"<<endl;
	rootD2.getDomains()->addDomain( typeExtObject, vectorDomainE3Na2Nat3VE1Nat1 );

	
	cout<<"cVectorExtObject vecExtObjectE4RD2 = cVectorExtObject( 4, &rootD2 );"<<endl;
	cVectorExtObject vecExtObjectE4RD2 = cVectorExtObject( 4, &rootD2 );

	cout<<"cFibVector * vectorInstanceD1 = vecExtObjectE4RD2.createInstance( 1 );"<<endl;
	cFibVector * vectorInstanceD1 = vecExtObjectE4RD2.createInstance( 1 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorExtObject
	if ( vectorInstanceD1->getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vectorInstanceD1->getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	cTypeElement * pTypeExtObject = vectorInstanceD1->getElementType();
	if ( typeExtObject == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vectorInstanceD1->getNumberOfElements() == (unsignedIntFib)(1) ){
	
		cout<<"The number of elements of the external object element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vectorInstanceD1->getNumberOfElements()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD1->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD1->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD1->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vectorInstanceD1->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vectorInstanceD1->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the external object element vector."<<endl;
	}else if ( &rootD2 == vectorInstanceD1->getDefiningFibElement() ){
	
		cerr<<"Error: The rootD2 is the defining element for the external object element vector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is a defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vectorInstanceD1->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the external object element vector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD1;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 3 elements"<<endl;

	cout<<"cTypeExtObjectInput typeExtObjectDom3( 3 );"<<endl;
	cTypeExtObjectInput typeExtObjectDom3( 3 );

	cout<<"cFibVector * vectorInstanceD3 = vecExtObjectE4RD2.createInstance( 3 );"<<endl;
	cFibVector * vectorInstanceD3 = vecExtObjectE4RD2.createInstance( 3 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorExtObject
	if ( vectorInstanceD3->getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vectorInstanceD3->getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vectorInstanceD3->getElementType();
	if ( typeExtObject == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vectorInstanceD3->getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the external object element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vectorInstanceD3->getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD3->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD3->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD3->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vectorInstanceD3->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vectorInstanceD3->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the external object element vector."<<endl;
	}else if ( &rootD2 == vectorInstanceD3->getDefiningFibElement() ){
	
		cerr<<"Error: The rootD2 is the defining element for the external object element vector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is an defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vectorInstanceD3->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the external object element vector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD3;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 2 elements and rootD2 as an defining element"<<endl;

	cout<<"cFibVector * vectorInstanceD2RD2 = vecExtObjectE4RD2.createInstance( 2, &rootD2 );"<<endl;
	cFibVector * vectorInstanceD2RD2 = vecExtObjectE4RD2.createInstance( 2, &rootD2 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorExtObject
	if ( vectorInstanceD2RD2->getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vectorInstanceD2RD2->getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vectorInstanceD2RD2->getElementType();
	if ( typeExtObject == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vectorInstanceD2RD2->getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vectorInstanceD2RD2->getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD2RD2->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD2RD2->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD2RD2->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vectorInstanceD2RD2->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vectorInstanceD2RD2->getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vectorInstanceD2RD2->getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vectorInstanceD2RD2->getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE1Nat1 == (*(vectorInstanceD2RD2->getDomain())) ){
	
		cout<<"The vectorDomainE3Na2Nat3VE1Nat1 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE1Nat1 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD2RD2;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with different external object element as defining element"<<endl;
	
	cout<<"cExtObject extObjectRd2( 5, 3, &rootD2 );"<<endl;
	cExtObject extObjectRd2( 5, 3, &rootD2 );
	
	cout<<"cFibVector * vectorInstanceD2FsRD2 = vecExtObjectE4RD2.createInstance( 2, &extObjectRd2 );"<<endl;
	cFibVector * vectorInstanceD2FsRD2 = vecExtObjectE4RD2.createInstance( 2, &extObjectRd2 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorExtObject
	if ( vectorInstanceD2FsRD2->getVectorType() == "externObjectInput" ){
	
		cout<<"The name of the external object element vector is correctly \"externObjectInput\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vectorInstanceD2FsRD2->getVectorType()<<" but should be \"externObjectInput\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtObject
	pTypeExtObject = vectorInstanceD2FsRD2->getElementType();
	cout<<"cTypeExtObjectInput typeExtObject5( 5 );"<<endl;
	cTypeExtObjectInput typeExtObject5( 5 );
	if ( typeExtObject5 == (*pTypeExtObject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtObject5. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtObject5 ."<<endl;
		iReturn++;
	}
	delete pTypeExtObject;
	
	//check the getNumberOfElements() methode from cVectorExtObject
	if ( vectorInstanceD2FsRD2->getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vectorInstanceD2FsRD2->getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD2FsRD2->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD2FsRD2->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD2FsRD2->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vectorInstanceD2FsRD2->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtObject
	if ( vectorInstanceD2FsRD2->getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectRd2 == vectorInstanceD2FsRD2->getDefiningFibElement() ){
	
		cout<<"The extObjectRd2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectRd2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtObject
	if ( vectorInstanceD1->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the external object element vector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD2FsRD2;
	
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
	
	TiXmlDocument xmlDocVectorExtObject( szFilename );
	bool loadOkay = xmlDocVectorExtObject.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocVectorExtObject );
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
					if ( compareDoubleFib( dValue1, vecValues[ iNumberOfElement - 1 ]) ||
							compareDoubleFib( dValue2, vecValues[ iNumberOfElement - 1 ]) ){
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
 * This method tests the storeXml() method of the cVectorExtObject class.
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
	
	cout<<"cTypeExtObjectInput typeExtObject( 0 );"<<endl;
	cTypeExtObjectInput typeExtObject( 0 );
	
	//create vector domain with tree elements
	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE3( vecDomains3 );"<<endl;
	cDomainVector vectorDomainE3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	cout<<"rootD3.getDomains()->addDomain( typeExtObject, vectorDomainE3 );"<<endl;
	rootD3.getDomains()->addDomain( typeExtObject, vectorDomainE3 );

	//creat defined variables to set them later in the vector
	cout<<"rootD3.setNumberOfInputVariables( 6 )"<<endl;
	rootD3.setNumberOfInputVariables( 6 );

	cout<<"cVectorExtObject vecExtObjectE3( 3, &rootD3 );"<<endl;
	cVectorExtObject vecExtObjectE3( 3, &rootD3 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	const char * szVectorPostion = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorExtObjectEmpty.xml" );
	ofstream fileVectorPostion( szVectorPostion );
	
	bool bStoreSuccesfull = vecExtObjectE3.storeXml( fileVectorPostion );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorPostion <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorPostion <<"\" failed."<<endl;
		iReturn++;
	}
	
	vector<char> vecElementTypeExtObject( 5, 'w' );
	vector<double> vecValuesExtObject( 5, 0.0 );
	
	iReturn += testXmlVector( szVectorPostion, "externObjectInput",
		3, vecElementTypeExtObject, vecValuesExtObject );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector one value set"<<endl;
	
	cout<<"vecExtObjectE3.setValue( 1, 111 )"<<endl;
	vecExtObjectE3.setValue( 1, 111 );
	vecElementTypeExtObject[0] = 'w';
	vecValuesExtObject[0] = 111;
	
	szFileNameBuffer[0] = 0;
	const char * szVectorExtObjectRD3V1g111 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorExtObjectRD3V1g111.xml" );
	ofstream fileVectorPostioRD3V1g111n( szVectorExtObjectRD3V1g111 );
	
	bStoreSuccesfull = vecExtObjectE3.storeXml( fileVectorPostioRD3V1g111n );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorExtObjectRD3V1g111 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorExtObjectRD3V1g111 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorExtObjectRD3V1g111, "externObjectInput",
		3, vecElementTypeExtObject, vecValuesExtObject );
	
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector all value set"<<endl;
	
	cout<<"vecExtObjectE3.setValue( 2, 123.456 )"<<endl;
	vecExtObjectE3.setValue( 2, 123.456  );
	vecElementTypeExtObject[1] = 'w';
	vecValuesExtObject[1] = 123.456;
	cout<<"vecExtObjectE3.setValue( 3, -123.456 )"<<endl;
	vecExtObjectE3.setValue( 3, -123.456 );
	vecElementTypeExtObject[2] = 'w';
	vecValuesExtObject[2] = -123.456;

	szFileNameBuffer[0] = 0;
	const char * szVectorExtObjectRD3T3 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorExtObjectRD3T3.xml" );
	ofstream fileVectorExtObjectRD3T3( szVectorExtObjectRD3T3 );
	
	bStoreSuccesfull = vecExtObjectE3.storeXml( fileVectorExtObjectRD3T3 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorExtObjectRD3T3 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorExtObjectRD3T3 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorExtObjectRD3T3, "externObjectInput",
		3, vecElementTypeExtObject, vecValuesExtObject );

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
	
	cout<<"vecExtObjectE3.setVariable( 1, pVariable1 )"<<endl;
	vecExtObjectE3.setVariable( 1, pVariable1  );
	vecElementTypeExtObject[0] = 'v';
	vecValuesExtObject[0] = 1;
	cout<<"vecExtObjectE3.setVariable( 2, pVariable2 )"<<endl;
	vecExtObjectE3.setVariable( 2, pVariable2 );
	vecElementTypeExtObject[1] = 'v';
	vecValuesExtObject[1] = 2;
	cout<<"vecExtObjectE3.setVariable( 3, pVariable3 )"<<endl;
	vecExtObjectE3.setVariable( 3, pVariable3 );
	vecElementTypeExtObject[2] = 'v';
	vecValuesExtObject[2] = 3;

	szFileNameBuffer[0] = 0;
	const char * szVectorExtObjectRD3T4 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorExtObjectRD3T4.xml" );
	ofstream fileVectorExtObjectRD3T4( szVectorExtObjectRD3T4 );
	
	bStoreSuccesfull = vecExtObjectE3.storeXml( fileVectorExtObjectRD3T4 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorExtObjectRD3T4 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorExtObjectRD3T4 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorExtObjectRD3T4, "externObjectInput",
		3, vecElementTypeExtObject, vecValuesExtObject );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector with variables and values"<<endl;
	
	cout<<"vecExtObjectE3.setVariable( 1, pVariable1 )"<<endl;
	vecExtObjectE3.setVariable( 1, pVariable1  );
	vecElementTypeExtObject[0] = 'v';
	vecValuesExtObject[0] = 1;
	cout<<"vecExtObjectE3.setValue( 2, -0.00124 )"<<endl;
	vecExtObjectE3.setValue( 2, -0.00124 );
	vecElementTypeExtObject[1] = 'w';
	vecValuesExtObject[1] = -0.00124;
	cout<<"vecExtObjectE3.setVariable( 3, pVariable3 )"<<endl;
	vecExtObjectE3.setVariable( 3, pVariable3 );
	vecElementTypeExtObject[2] = 'v';
	vecValuesExtObject[2] = 3;

	szFileNameBuffer[0] = 0;
	const char * szVectorExtObjectRD3T5 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorExtObjectRD3T5.xml" );
	ofstream fileVectorExtObjectRD3T5( szVectorExtObjectRD3T5 );
	
	bStoreSuccesfull = vecExtObjectE3.storeXml( fileVectorExtObjectRD3T5 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorExtObjectRD3T5 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorExtObjectRD3T5 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorExtObjectRD3T5, "externObjectInput",
		3, vecElementTypeExtObject, vecValuesExtObject );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 5 d vector with variables and values"<<endl;
	
	cout<<"cVectorExtObject vecExtObjectRD5 = cVectorExtObject( 5, &rootD3 );"<<endl;
	cVectorExtObject vecExtObjectRD5 = cVectorExtObject( 5, &rootD3 );

	cout<<"vecExtObjectRD5.setVariable( 1, pVariable1 )"<<endl;
	vecExtObjectRD5.setVariable( 1, pVariable1  );
	vecElementTypeExtObject[0] = 'v';
	vecValuesExtObject[0] = 1;
	cout<<"vecExtObjectRD5.setValue( 2, -0.00124 )"<<endl;
	vecExtObjectRD5.setValue( 2, -0.00124 );
	vecElementTypeExtObject[1] = 'w';
	vecValuesExtObject[1] = -0.00124;
	cout<<"vecExtObjectRD5.setVariable( 3, pVariable3 )"<<endl;
	vecExtObjectRD5.setVariable( 3, pVariable3 );
	vecElementTypeExtObject[2] = 'v';
	vecValuesExtObject[2] = 3;
	cout<<"vecExtObjectRD5.setValue( 4, 1234 )"<<endl;
	vecExtObjectRD5.setValue( 4, 1234 );
	vecElementTypeExtObject[3] = 'w';
	vecValuesExtObject[3] = 1234;
	cout<<"vecExtObjectRD5.setValue( 5, 123.67 )"<<endl;
	vecExtObjectRD5.setValue( 5, 123.67   );
	vecElementTypeExtObject[4] = 'w';
	vecValuesExtObject[4] = 123.67 ;

	szFileNameBuffer[0] = 0;
	const char * szVectorExtObjectRD3T6 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorExtObjectRD3T6.xml" );
	ofstream fileVectorExtObjectRD3T6( szVectorExtObjectRD3T6 );
	
	bStoreSuccesfull = vecExtObjectRD5.storeXml( fileVectorExtObjectRD3T6 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorExtObjectRD3T6 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorExtObjectRD3T6 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorExtObjectRD3T6, "externObjectInput",
		5, vecElementTypeExtObject, vecValuesExtObject );


	return iReturn;
}


/**
 * This method store methods of the class.
 *
 * methods tested:
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostringstream & ostream ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStore( unsigned long &ulTestphase ){

	int iReturn = 0;//return value of the test; the number of occured errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a external object element vector with 0 elements"<<endl;

	cout<<"cVectorExtObject vecExtObjectE0( 0 );"<<endl;
	cVectorExtObject vecExtObjectE0( 0 );

	//test get compressed size
	unsigned int uiCompressedSize = 0;
	if ( (unsigned int)(vecExtObjectE0.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtObjectE0.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtObjectE0.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	cout<<"vecExtObjectE0.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bool bStoreSuccesfull = vecExtObjectE0.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cExtObjectE0[] = { (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtObjectE0, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a external object element vector with 2 elements"<<endl;

	cout<<"cVectorExtObject vecExtObject1E2Ch( 2 );"<<endl;
	cVectorExtObject vecExtObject1E2Ch( 2 );
	cout<<"vecExtObject1E2Ch.setValue( 1, 4 );"<<endl;
	vecExtObject1E2Ch.setValue( 1, 4 );
	cout<<"vecExtObject1E2Ch.setValue( 2, 6 );"<<endl;
	vecExtObject1E2Ch.setValue( 2, 6 );

	//test get compressed size
	uiCompressedSize = 2 * (1 + 8);
	if ( (unsigned int)(vecExtObject1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtObject1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtObject1E2Ch.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtObject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtObject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	short sNumberOfRestBitCorrect = 2;
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
	const char cExtObjectE2[] = { (char)0x08, (char)0x18, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtObjectE2, 3 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a external object element vector with variables"<<endl;

	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;

	cout<<"rootD2.setNumberOfInputVariables( 6 );"<<flush<<endl;
	rootD2.setNumberOfInputVariables( 6 );
	
	cout<<"pVariable1 = rootD2.getInputVariable( 1 );"<<flush<<endl;
	cFibVariable * pVariable1 = rootD2.getInputVariable( 1 );
	cout<<"pVariable2 = rootD2.getInputVariable( 2 );"<<flush<<endl;
	cFibVariable * pVariable2 = rootD2.getInputVariable( 2 );

	cout<<"pVariable1->setValue( 1 );"<<flush<<endl;
	pVariable1->setValue( 1 );
	cout<<"pVariable2->setValue( 2 );"<<flush<<endl;
	pVariable2->setValue( 2 );

	cout<<"vecExtObject1E2Ch.setVariable( 1, pVariable1);"<<endl;
	vecExtObject1E2Ch.setVariable( 1, pVariable1);
	cout<<"vecExtObject1E2Ch.setVariable( 2, pVariable2);"<<endl;
	vecExtObject1E2Ch.setVariable( 2, pVariable2);

	//test get compressed size
	uiCompressedSize = 2 * 9;
	if ( (unsigned int)(vecExtObject1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtObject1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtObject1E2Var.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtObject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtObject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	sNumberOfRestBitCorrect = 2;
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
	const char cExtObjectE2Var[] = { (char)0x03, (char)0x0A, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtObjectE2Var, 3 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a external object element vector with domains"<<endl;

	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomains2( 2 );"<<endl;
	vector<cDomainSingle*> vecDomains2( 2 );
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomainE2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];

	cout<<"cTypeExtObjectInput typeExtObject( 0 );"<<endl;
	cTypeExtObjectInput typeExtObject( 0 );
	
	cout<<"rootD2.getDomains()->addDomain( typeExtObject, &vectorDomainE2 );"<<endl;
	rootD2.getDomains()->addDomain( typeExtObject, &vectorDomainE2 );

	cout<<"cTypeVariable typeVariable;"<<endl;
	cTypeVariable typeVariable;

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB3( 3 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB3( 3 );

	cout<<"rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB3 );"<<endl;
	rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB3 );

	cout<<"vecExtObject1E2Ch.setDefiningFibElement( &rootD2 );"<<endl;
	vecExtObject1E2Ch.setDefiningFibElement( &rootD2 );
	
	cout<<"vecExtObject1E2Ch.setValue( 2, 3 );"<<endl;
	vecExtObject1E2Ch.setValue( 2, 3 );

	//test get compressed size
	uiCompressedSize = 4 + 3;
	if ( (unsigned int)(vecExtObject1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtObject1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtObject1E2Dom.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtObject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtObject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = (char)0x63;
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
	const char cExtObjectE2Dom[] = { (char)ucRestBitCorrect };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtObjectE2Dom, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a external object element vector 3 elements"<<endl;

	cout<<"cVectorExtObject vecExtObject1E3( 3 );"<<endl;
	cVectorExtObject vecExtObject1E3( 3 );
	
	cout<<"vecExtObject1E3.setVariable( 1, pVariable2 );"<<endl;
	vecExtObject1E3.setVariable( 1, pVariable2 );
	cout<<"vecExtObject1E3.setVariable( 2, pVariable1 );"<<endl;
	vecExtObject1E3.setVariable( 2, pVariable1);
	cout<<"vecExtObject1E3.setValue( 3, 5);"<<endl;
	vecExtObject1E3.setValue( 3, 5);

	//test get compressed size
	uiCompressedSize = 2 * 9 + (1 + 8);
	if ( (unsigned int)(vecExtObject1E3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtObject1E3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtObject1E3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtObject1E3.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtObject1E3.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cVecExtObject1E3[] = { (char)0x05, (char)0x06, (char)0x28, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cVecExtObject1E3, 4 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a external object element vector with a restbit of 4"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtObject1E3R4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x0F;
	cNumberOfRestBit = 4;
	cout<<"vecExtObject1E3.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtObject1E3.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = (char)0x02;
	sNumberOfRestBitCorrect = 7;
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
	const char cVecExtObject1E3R4[] = { (char)0x5F, (char)0x60, (char)0x80, (char)0x02 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cVecExtObject1E3R4, 4 );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an external object element vector with domain not 0"<<endl;

	//create vector domain with two elements
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"cDomainVector vectorDomainE2Nat3Nat4( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat3Nat4( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];

	cout<<"cTypeExtObjectInput typeExtObject4( 4 );"<<endl;
	cTypeExtObjectInput typeExtObject4( 4 );
	
	cout<<"rootD2.getDomains()->addDomain( typeExtObject4, &vectorDomainE2Nat3Nat4 );"<<endl;
	rootD2.getDomains()->addDomain( typeExtObject4, &vectorDomainE2Nat3Nat4 );
	
	cout<<"cExtObject extObjectElement( 4, 2, &rootD2 );"<<endl;
	cExtObject extObjectElement( 4, 2, &rootD2 );
	
	cout<<"vecExtObject1E2Ch.setDefiningFibElement( &extObjectElement );"<<endl;
	vecExtObject1E2Ch.setDefiningFibElement( &extObjectElement );
	
	//test get compressed size
	uiCompressedSize = 4 + 5;
	if ( (unsigned int)(vecExtObject1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtObject1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtObject1E2Dom4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtObject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtObject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cExtObjectE2Dom1[] = { (char)0x63, (char)0x00 };// 001 1  0011 0
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtObjectE2Dom1, 2 );
	
	
	cout<<endl<<"extObjectElement.setIdentifier( 3 );"<<endl;
	extObjectElement.setIdentifier( 3 );
	
	cout<<"vecExtObject1E2Ch.setDefiningFibElement( &extObjectElement );"<<endl;
	vecExtObject1E2Ch.setDefiningFibElement( &extObjectElement );
	
	//test get compressed size
	uiCompressedSize = (1 + 3) + (1 + 8);
	if ( (unsigned int)(vecExtObject1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtObject1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtObject1E2Dom3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtObject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtObject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cExtObjectE2Dom3[] = { (char)0x63, (char)0x00 };// 001 1   0000 0011 0
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtObjectE2Dom3, 2 );

	
	cout<<endl<<"extObjectElement.setIdentifier( 5 );"<<endl;
	extObjectElement.setIdentifier( 5 );
	
	cout<<"vecExtObject1E2Ch.setDefiningFibElement( &extObjectElement );"<<endl;
	vecExtObject1E2Ch.setDefiningFibElement( &extObjectElement );
	
	//test get compressed size
	if ( (unsigned int)(vecExtObject1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtObject1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtObject1E2Dom5.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtObject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtObject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtObjectE2Dom3, 2 );

	
	
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

	int iReturn = 0;//return value of the test; the number of occured errors


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the operator=() method"<<endl;
	
	cout<<"cFibVector * pVecExtObjectDestination = new cVectorExtObject( 2 );"<<endl;
	cFibVector  * pVecExtObjectDestination = new cVectorExtObject( 2 );
	
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
		if ( (rand() % 10) != 0 ){
			//create a positions vector
			unsigned int uiNumberOfExtObjects = 0;
			if ( (rand() % 10) != 0 ){
				uiNumberOfExtObjects = (rand() % 3 + 1) * (rand() % 4 + 1) + (rand() % 4);
			}else{
				uiNumberOfExtObjects = 0;
			}
			cout<<"pVecSource = new cVectorExtObject( "<< uiNumberOfExtObjects <<", &emptyRoot ); "<<endl;
			pVecSource = new cVectorExtObject( uiNumberOfExtObjects, &emptyRoot );
			
			pVecEqual = pVecSource;
		}else{//create non cVectorExtObject vector
			const unsigned int uiVectorType = rand() % 2;
			switch( uiVectorType ){
				case 0:{
					cout<<"pVecSource = new cVectorArea( &emptyRoot ); "<<endl;
					pVecSource = new cVectorArea( &emptyRoot );
				}break;
				default:{
					unsigned int uiChoosenPropertyType = pPossiblePropertyTyps[ rand() %
						( sizeof( pPossiblePropertyTyps ) / sizeof( unsigned int ) ) ];
					cout<<"pVecSource = new cVectorProperty( "<<
						uiChoosenPropertyType <<", &emptyRoot ); "<<endl;
					pVecSource = new cVectorProperty( uiChoosenPropertyType, &emptyRoot );
				}
			};
			pVecEqual = new cVectorExtObject( pVecSource->getNumberOfElements(), &emptyRoot  );
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
		cout<<"(* pVecExtObjectDestination) = (* pVecSource );"<<endl;
		(* pVecExtObjectDestination) = (* pVecSource );
		
		//test the created vector
		if ( (*pVecExtObjectDestination) == ( * pVecEqual) ){
		
			cout<<"The vecExtObjectDestination is correct . "<<endl;
		}else{
			cerr<<"Error: The vecExtObjectDestination is not correct ."<<endl;
			iReturn++;
		}
		
		if ( pVecEqual != pVecSource ){
			//pVecEqual and pVecSource are different vectors
			delete pVecEqual;
		}
		delete pVecSource;
	}
	delete pVecExtObjectDestination;
	
	return iReturn;
}




















