/**
 * @file tVectorExtSubobject
 * file name: tVectorExtSubobject.cpp
 * @author Betti Oesterholz
 * @date 04.05.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cVectorExtSubobject.
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
 * This file contains the test for the class cVectorExtSubobject,
 * which represents the vector for positions.
 *
 *
 *
 *  What's tested of class cVectorExtSubobject:
 * 	- cVectorExtSubobject( unsignedIntFib iNumberOfElements=2, cFibElement * pDefiningSetElement=NULL );
 * 	- cVectorExtSubobject( cExtSubobject & definingSetElement );
 * 	- cVectorExtSubobject( const cVectorExtSubobject & vector, cFibElement * definingFibElement = NULL );
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
04.05.2012  Oesterholz  created
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/


#include "version.h"

#include "cVectorExtSubobject.h"
#include "cVectorArea.h"
#include "cVectorProperty.h"
#include "cTypeExtSubobject.h"
#include "cTypeVariable.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainIntegerBit.h"
#include "cDomainVector.h"
#include "cDomainVectorOpenEnd.h"
#include "cRoot.h"
#include "cPoint.h"
#include "cExtSubobject.h"
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
	
	cout<<endl<<"Running Test for cVectorExtSubobject methods"<<endl;
	cout<<      "============================================"<<endl;

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
 * This method tests the constructors of the cVectorExtSubobject class.
 *
 * constructors tested:
 * 	- cVectorExtSubobject( unsignedIntFib iNumberOfElements=2, cFibElement * pDefiningSetElement=NULL );
 * 	- cVectorExtSubobject( cExtSubobject & definingSetElement );
 * 	- cVectorExtSubobject( const cVectorExtSubobject & vector, cFibElement * definingFibElement = NULL );
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cVectorExtSubobject"<<endl;

	cout<<"cTypeExtSubobject typeExtSubobject( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject( 0 );
	
	cout<<"cVectorExtSubobject vecExtSubobject( 0 );"<<endl;
	cVectorExtSubobject vecExtSubobject( 0 );


	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobject.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobject.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	cTypeElement * pTypeExtSubobject = vecExtSubobject.getElementType();
	if ( typeExtSubobject == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobject.getNumberOfElements() == (unsignedIntFib)(0) ){
	
		cout<<"The number of elements of the external object element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobject.getNumberOfElements()<<" but should be 0 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtSubobject.getNumberOfElements(); 
			uiActualElement++ ){
		
		if ( ! vecExtSubobject.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtSubobject.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtSubobject.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobject.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the external object element vector."<<endl;
		iReturn++;
	}

	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobject.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the external object element vector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtSubobject with 3 elements"<<endl;

	cout<<"cVectorExtSubobject vecExtSubobjectE3( 3 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE3( 3 );


	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3.getElementType();
	if ( typeExtSubobject == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the external object element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtSubobjectE3.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtSubobject.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtSubobjectE3.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtSubobjectE3.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the external object element vector."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtSubobject with 4 elements and an defining element"<<endl;

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

	cout<<"rootD2.getDomains()->addDomain( typeExtSubobject, vectorDomainE3Na2Nat3VE1Nat1 );"<<endl;
	rootD2.getDomains()->addDomain( typeExtSubobject, vectorDomainE3Na2Nat3VE1Nat1 );

	
	cout<<"cVectorExtSubobject vecExtSubobjectE4RD2 = cVectorExtSubobject( 4, &rootD2 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE4RD2 = cVectorExtSubobject( 4, &rootD2 );


	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE4RD2.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE4RD2.getElementType();
	if ( typeExtSubobject == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the external object element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE4RD2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtSubobjectE4RD2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtSubobjectE4RD2.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtSubobjectE4RD2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtSubobjectE4RD2.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecExtSubobjectE4RD2.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE1Nat1 == (*(vecExtSubobjectE4RD2.getDomain())) ){
	
		cout<<"The vectorDomainE3Na2Nat3VE1Nat1 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE1Nat1 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtSubobject with a external object element as defining element"<<endl;

	cout<<"cExtSubobject extObjectV4( 4 );"<<endl;
	cExtSubobject extObjectV4( 4 );
	
	cout<<"cVectorExtSubobject vecExtSubobjectE4( 4, &extObjectV4 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE4( 4, &extObjectV4 );

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE4.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	cTypeExtSubobject typeExtSubobjectInput4( 4 );
	pTypeExtSubobject = vecExtSubobjectE4.getElementType();
	if ( typeExtSubobjectInput4 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to cTypeExtSubobject( 4 ). "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to cTypeExtSubobject( 4 ) ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the external object element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE4.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtSubobjectE4.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtSubobjectE4.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtSubobjectE4.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtSubobjectE4.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV4 == vecExtSubobjectE4.getDefiningFibElement() ){
	
		cout<<"The extObjectV4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtSubobject with a external object element as defining element, wich has other than the vector elemnts defined variables"<<endl;
	
	cout<<"cVectorExtSubobject vecExtSubobjectE3V4( 3, &extObjectV4 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE3V4( 3, &extObjectV4 );

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3V4.getElementType();
	if ( typeExtSubobjectInput4 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to cTypeExtSubobject( 4 ). "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to cTypeExtSubobject( 4 ) ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the external object element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtSubobjectE3V4.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtSubobjectE3V4.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtSubobjectE3V4.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtSubobjectE3V4.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV4 == vecExtSubobjectE3V4.getDefiningFibElement() ){
	
		cout<<"The extObjectV4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtSubobject with a external object element as defining element, wich has domain number set"<<endl;
	
	cout<<"cRoot rootDom4;"<<flush<<endl;
	cRoot rootDom4;
	
	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject, vectorDomainE3Na2Nat3VE1Nat1 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject, vectorDomainE3Na2Nat3VE1Nat1 );

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

	cout<<"cTypeExtSubobject typeExtSubobject4( 4 );"<<endl;
	cTypeExtSubobject typeExtSubobject4( 4 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject4, vectorDomainE3Na4Nat5VE2NInt2Int3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject4, vectorDomainE3Na4Nat5VE2NInt2Int3 );
	
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

	cout<<"cTypeExtSubobject typeExtSubobject5( 5 );"<<endl;
	cTypeExtSubobject typeExtSubobject5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject5, vectorDomainE2Int4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject5, vectorDomainE2Int4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"cTypeExtSubobject typeExtSubobject6( 6 );"<<endl;
	cTypeExtSubobject typeExtSubobject6( 6 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject6, vectorDomainOE1Int8 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject6, vectorDomainOE1Int8 );
	
	
	cout<<"cExtSubobject extObjectV3Dom5rootDom4( 5, 0, &rootDom4 );"<<endl;
	cExtSubobject extObjectV3Dom5rootDom4( 5, 0, &rootDom4 );
	
	cout<<"cVectorExtSubobject vecExtSubobjectE3V4Dom5( 2, &extObjectV3Dom5rootDom4 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE3V4Dom5( 2, &extObjectV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	if ( typeExtSubobject5 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject5. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject5 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtSubobjectE3V4Dom5.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtSubobjectE3V4Dom5.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtSubobjectE3V4Dom5.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtSubobjectE3V4Dom5.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3Dom5rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3Dom5rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3Dom5rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE2Int4Int5 == (*(vecExtSubobjectE3V4Dom5.getDomain())) ){
	
		cout<<"The vectorDomainE2Int4Int5 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtSubobject with a external object element as defining element, wich has a not existig domain number set"<<endl;
	
	cout<<"extObjectV3Dom5rootDom4.setNumberSubobject( 13 );"<<endl;
	extObjectV3Dom5rootDom4.setNumberSubobject( 13 );
	
	cout<<"cVectorExtSubobject vecExtSubobjectE3V4Dom13( 2, &extObjectV3Dom5rootDom4 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE3V4Dom13( 2, &extObjectV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom13.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom13.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	cout<<"cTypeExtSubobject typeExtSubobject13( 13 ); "<<endl;
	cTypeExtSubobject typeExtSubobject13( 13 );
	pTypeExtSubobject = vecExtSubobjectE3V4Dom13.getElementType();
	if ( typeExtSubobject13 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject13. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject13 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom13.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom13.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtSubobjectE3V4Dom13.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtSubobjectE3V4Dom13.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtSubobjectE3V4Dom13.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtSubobjectE3V4Dom13.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom13.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3Dom5rootDom4 == vecExtSubobjectE3V4Dom13.getDefiningFibElement() ){
	
		cout<<"The extObjectV3Dom13rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3Dom13rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom13.getDomain() == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: Ther is a domain defined for the external object element vector."<<endl;
		iReturn++;	
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtSubobject with just a external object element as defining element"<<endl;

	cout<<"cVectorExtSubobject vecExtSubobject2E4( extObjectV4 );"<<endl;
	cVectorExtSubobject vecExtSubobject2E4( extObjectV4 );

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobject2E4.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobject2E4.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobject2E4.getElementType();
	if ( typeExtSubobjectInput4 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobjectInput4. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobjectInput4."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobject2E4.getNumberOfElements() == (unsignedIntFib)(0) ){
	
		cout<<"The number of elements of the external object element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobject2E4.getNumberOfElements()<<" but should be 0 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtSubobject2E4.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtSubobject2E4.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtSubobject2E4.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtSubobject2E4.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobject2E4.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV4 == vecExtSubobject2E4.getDefiningFibElement() ){
	
		cout<<"The extObjectV4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobject2E4.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtSubobject with just a external object element as defining element, wich has domain number set"<<endl;
	
	cout<<"extObjectV3Dom5rootDom4.setNumberSubobject( 5 );"<<endl;
	extObjectV3Dom5rootDom4.setNumberSubobject( 5 );

	cout<<"cVectorExtSubobject vecExtSubobject2E3V4Dom5( extObjectV3Dom5rootDom4 );"<<endl;
	cVectorExtSubobject vecExtSubobject2E3V4Dom5( extObjectV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobject2E3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobject2E3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobject2E3V4Dom5.getElementType();
	if ( typeExtSubobject5 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject5. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject5 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobject2E3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobject2E3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtSubobject2E3V4Dom5.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtSubobject2E3V4Dom5.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtSubobject2E3V4Dom5.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtSubobject2E3V4Dom5.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobject2E3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3Dom5rootDom4 == vecExtSubobject2E3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3Dom5rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3Dom5rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobject2E3V4Dom5.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE2Int4Int5 == (*(vecExtSubobject2E3V4Dom5.getDomain())) ){
	
		cout<<"The vectorDomainE2Int4Int5 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtSubobject with yust a external object element as defining element, wich has a not existig domain number set"<<endl;
	
	cout<<"extObjectV3Dom5rootDom4.setNumberSubobject( 13 );"<<endl;
	extObjectV3Dom5rootDom4.setNumberSubobject( 13 );

	cout<<"cVectorExtSubobject vecExtSubobject2E3V4Dom13( extObjectV3Dom5rootDom4 );"<<endl;
	cVectorExtSubobject vecExtSubobject2E3V4Dom13( extObjectV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobject2E3V4Dom13.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobject2E3V4Dom13.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobject2E3V4Dom13.getElementType();
	if ( typeExtSubobject13 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject13. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject13 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobject2E3V4Dom13.getNumberOfElements() == (unsignedIntFib)(0) ){
	
		cout<<"The number of elements of the external object element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobject2E3V4Dom13.getNumberOfElements()<<" but should be 0 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtSubobject2E3V4Dom13.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtSubobject2E3V4Dom13.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtSubobject2E3V4Dom13.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtSubobject2E3V4Dom13.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobject2E3V4Dom13.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3Dom5rootDom4 == vecExtSubobject2E3V4Dom13.getDefiningFibElement() ){
	
		cout<<"The extObjectV3Dom13rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3Dom13rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobject2E3V4Dom13.getDomain() == NULL ){
		cout<<"Ther is corroctly no domain defined for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: Ther is a domain defined for the external object element vector."<<endl;
		iReturn++;	
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtSubobject by copying vecExtSubobjectE3"<<endl;
	
	cout<<"cVectorExtSubobject vecExtSubobjectE3Copy( vecExtSubobjectE3 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE3Copy( vecExtSubobjectE3 );

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3Copy.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3Copy.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3Copy.getElementType();
	if ( typeExtSubobject == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3Copy.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the external object element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3Copy.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtSubobjectE3Copy.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtSubobjectE3Copy.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtSubobjectE3Copy.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<< vecExtSubobjectE3Copy.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3Copy.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3Copy.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtSubobject by copying vecExtSubobjectE4RD2"<<endl;
	
	cout<<"cVectorExtSubobject vecExtSubobjectE4RD2Copy( vecExtSubobjectE4RD2 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE4RD2Copy( vecExtSubobjectE4RD2 );

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2Copy.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE4RD2Copy.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE4RD2Copy.getElementType();
	if ( typeExtSubobject == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2Copy.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the external object element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE4RD2Copy.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtSubobjectE4RD2Copy.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtSubobjectE4RD2Copy.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtSubobjectE4RD2Copy.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<< vecExtSubobjectE4RD2Copy.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2Copy.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecExtSubobjectE4RD2Copy.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2Copy.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE1Nat1 == (*(vecExtSubobjectE4RD2Copy.getDomain())) ){
	
		cout<<"The vectorDomainE3Na2Nat3VE1Nat1 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE1Nat1 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtSubobject by copying vecExtSubobjectE4RD2 and givin extObjectV3Dom5rootDom4 as an defining element"<<endl;
	
	cout<<"extObjectV3Dom5rootDom4.setNumberSubobject( 5 );"<<endl;
	extObjectV3Dom5rootDom4.setNumberSubobject( 5 );

	cout<<"cVectorExtSubobject vecExtSubobjectE4RD2Copy2( vecExtSubobjectE4RD2, &extObjectV3Dom5rootDom4 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE4RD2Copy2( vecExtSubobjectE4RD2, &extObjectV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2Copy2.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE4RD2Copy2.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE4RD2Copy2.getElementType();
	if ( typeExtSubobject5 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject5. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject5 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2Copy2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the external object element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE4RD2Copy2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtSubobjectE4RD2Copy2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtSubobjectE4RD2Copy2.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtSubobjectE4RD2Copy2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<< vecExtSubobjectE4RD2Copy2.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2Copy2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3Dom5rootDom4 == vecExtSubobjectE4RD2Copy2.getDefiningFibElement() ){
	
		cout<<"The extObjectV3Dom5rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3Dom5rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2Copy2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE2Int4Int5 == (*(vecExtSubobjectE4RD2Copy2.getDomain())) ){
	
		cout<<"The vectorDomainE2Int4Int5 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorExtSubobject by copying vecExtSubobjectRD3 with changed elements"<<endl;
	
	cout<<"rootDom4.setNumberOfInputVariables( 2 );"<<endl;
	rootDom4.setNumberOfInputVariables( 2 );
	cout<<"cFibVariable * pVariable1 = rootDom4.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootDom4.getInputVariable( 1 );
	cout<<"cFibVariable * pVariable2 = rootDom4.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = rootDom4.getInputVariable( 2 );

	cout<<"vecExtSubobjectE4RD2.setValue( 1, 1 );"<<endl;
	vecExtSubobjectE4RD2.setValue( 1, 1 );
	cout<<"vecExtSubobjectE4RD2.setVariable( 2, pVariable1 );"<<endl;
	vecExtSubobjectE4RD2.setVariable( 2, pVariable1 );
	cout<<"vecExtSubobjectE4RD2.setValue( 3, 2 );"<<endl;
	vecExtSubobjectE4RD2.setValue( 3, 2 );
	cout<<"vecExtSubobjectE4RD2.setVariable( 4, pVariable2 );"<<endl;
	vecExtSubobjectE4RD2.setVariable( 4, pVariable2 );
	
	cout<<"cVectorExtSubobject vecExtSubobjectE4RD2CopyMod( vecExtSubobjectE4RD2 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE4RD2CopyMod( vecExtSubobjectE4RD2 );

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2CopyMod.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE4RD2CopyMod.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE4RD2CopyMod.getElementType();
	if ( typeExtSubobject == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2Copy2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the external object element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE4RD2Copy2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
		//check the first vectorelement
	if ( ! vecExtSubobjectE4RD2CopyMod.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobjectE4RD2CopyMod.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobjectE4RD2CopyMod.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecExtSubobjectE4RD2CopyMod.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobjectE4RD2CopyMod.getVariable( 2 ) == pVariable1 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the secound vectorelement
	if ( ! vecExtSubobjectE4RD2CopyMod.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobjectE4RD2CopyMod.getValue( 3 ) == (doubleFib)(2) ){
	
		cout<<"The 3'th element of the "<<
			"external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobjectE4RD2CopyMod.getValue( 3 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecExtSubobjectE4RD2CopyMod.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobjectE4RD2CopyMod.getVariable( 4 ) == pVariable2 ){
	
		cout<<"The 4'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2CopyMod.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecExtSubobjectE4RD2CopyMod.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2CopyMod.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE1Nat1 == (*(vecExtSubobjectE4RD2CopyMod.getDomain())) ){
	
		cout<<"The vectorDomainE3Na2Nat3VE1Nat1 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE1Nat1 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"Testing the original vector vecExtSubobjectE4RD2:"<<endl;

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE4RD2.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE4RD2.getElementType();
	if ( typeExtSubobject == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the external object element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE4RD2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
		//check the first vectorelement
	if ( ! vecExtSubobjectE4RD2.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobjectE4RD2.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobjectE4RD2.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecExtSubobjectE4RD2.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobjectE4RD2.getVariable( 2 ) == pVariable1 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the secound vectorelement
	if ( ! vecExtSubobjectE4RD2.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobjectE4RD2.getValue( 3 ) == (doubleFib)(2) ){
	
		cout<<"The 3'th element of the "<<
			"external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobjectE4RD2.getValue( 3 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecExtSubobjectE4RD2.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobjectE4RD2.getVariable( 4 ) == pVariable2 ){
	
		cout<<"The 4'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecExtSubobjectE4RD2.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE1Nat1 == (*(vecExtSubobjectE4RD2.getDomain())) ){
	
		cout<<"The vectorDomainE3Na2Nat3VE1Nat1 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE1Nat1 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"Changing vecExtSubobjectE4RD2 should not change the copy:"<<endl;

	cout<<"vecExtSubobjectE4RD2.setVariable( 1, pVariable2 );"<<endl;
	vecExtSubobjectE4RD2.setVariable( 1, pVariable2 );
	cout<<"vecExtSubobjectE4RD2.setValue( 2, 9 );"<<endl;
	vecExtSubobjectE4RD2.setValue( 2, 1 );
	cout<<"vecExtSubobjectE4RD2.setValue( 3, 8 );"<<endl;
	vecExtSubobjectE4RD2.setValue( 3, 2 );

	cout<<endl<<"Testing the copied vector vecExtSubobjectE4RD2CopyMod for changed values:"<<endl;
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2CopyMod.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE4RD2CopyMod.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE4RD2CopyMod.getElementType();
	if ( typeExtSubobject == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2Copy2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the external object element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE4RD2Copy2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
		//check the first vectorelement
	if ( ! vecExtSubobjectE4RD2CopyMod.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobjectE4RD2CopyMod.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobjectE4RD2CopyMod.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecExtSubobjectE4RD2CopyMod.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobjectE4RD2CopyMod.getVariable( 2 ) == pVariable1 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the secound vectorelement
	if ( ! vecExtSubobjectE4RD2CopyMod.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobjectE4RD2CopyMod.getValue( 3 ) == (doubleFib)(2) ){
	
		cout<<"The 3'th element of the "<<
			"external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobjectE4RD2CopyMod.getValue( 3 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecExtSubobjectE4RD2CopyMod.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobjectE4RD2CopyMod.getVariable( 4 ) == pVariable2 ){
	
		cout<<"The 4'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2CopyMod.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecExtSubobjectE4RD2CopyMod.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobjectE4RD2CopyMod.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE1Nat1 == (*(vecExtSubobjectE4RD2CopyMod.getDomain())) ){
	
		cout<<"The vectorDomainE3Na2Nat3VE1Nat1 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE1Nat1 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the method for the domains of the cVectorExtSubobject class.
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
	
	cout<<"cTypeExtSubobject typeExtSubobject( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject( 0 );

	cout<<"root.getDomains()->addDomain( typeExtSubobject, &vectorDomainE3Nat1Nat2Nat3 );"<<endl;
	root.getDomains()->addDomain( typeExtSubobject, &vectorDomainE3Nat1Nat2Nat3 );

	
	cout<<"cVectorExtSubobject vecExtSubobjectRD( 3, &root );"<<endl;
	cVectorExtSubobject vecExtSubobjectRD( 3, &root );
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectRD.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the external object element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectRD.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the getDomain() methode from cVectorExtSubobject
	if ( vecExtSubobjectRD.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE3Nat1Nat2Nat3 == vecExtSubobjectRD.getDomain() ){
	
		cout<<"The &vectorDomainE3Nat1Nat2Nat3 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: &vectorDomainE3Nat1Nat2Nat3 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}

	/*check the getDomain(i=1..n) method of the set-vektor*/
	//test the getType() method
	cout<<"cDomain * pDomainD3 = vecExtSubobjectRD.getDomain();"<<endl;
	cDomain * pDomainD3 = vecExtSubobjectRD.getDomain();
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

	//check the getStandardDomain() method from cVectorExtSubobject
	cDomain * pDomainStandard = vecExtSubobjectRD.getStandardDomain();
	cDomain * pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtSubobject domains with domain numbers"<<endl;
	
	cout<<"cRoot rootDom4;"<<flush<<endl;
	cRoot rootDom4;
	
	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject, &vectorDomainE3Nat1Nat2Nat3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject, &vectorDomainE3Nat1Nat2Nat3 );

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
	
	cout<<"cTypeExtSubobject typeExtSubobject4( 4 );"<<endl;
	cTypeExtSubobject typeExtSubobject4( 4 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject4, &vectorDomainE2NInt2Int3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject4, &vectorDomainE2NInt2Int3 );
	
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

	cout<<"cTypeExtSubobject typeExtSubobject5( 5 );"<<endl;
	cTypeExtSubobject typeExtSubobject5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject5, &vectorDomainE2Int4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject5, &vectorDomainE2Int4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"cTypeExtSubobject typeExtSubobject6( 6 );"<<endl;
	cTypeExtSubobject typeExtSubobject6( 6 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject6, &vectorDomainOE1Int8 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject6, &vectorDomainOE1Int8 );
	

	cout<<"cExtSubobject extObjectV3rootDom4( 0, 0, &rootDom4 );"<<endl;
	cExtSubobject extObjectV3rootDom4( 0, 0, &rootDom4 );
	
	cout<<"cVectorExtSubobject vecExtSubobjectE3V4Dom5( 2, &extObjectV3rootDom4 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE3V4Dom5( 2, &extObjectV3rootDom4 );

	//check the getDomain() methode from cVectorExtSubobject
	cout<<"cDomain * pDomain = vecExtSubobjectE3V4Dom5.getDomain();"<<endl;
	cDomain * pDomain = vecExtSubobjectE3V4Dom5.getDomain();
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
		//check the getDomain() methode from cVectorExtSubobject
		if ( &vectorDomainE3Nat1Nat2Nat3 == vecExtSubobjectRD.getDomain() ){
		
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

	//check the getStandardDomain() method from cVectorExtSubobject
	pDomainStandard = vecExtSubobjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	cTypeElement * pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	if ( typeExtSubobject == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtSubobject domains with domain numbers, setting domain number 1"<<endl;
	
	cout<<"extObjectV3rootDom4.setNumberSubobject( 1 );"<<endl;
	extObjectV3rootDom4.setNumberSubobject( 1 );

	//check the getDomain() methode from cVectorExtSubobject
	cout<<"pDomain = vecExtSubobjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtSubobjectE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}

	//check the getStandardDomain() method from cVectorExtSubobject
	pDomainStandard = vecExtSubobjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	cTypeExtSubobject typeExtSubobject1( 1 );
	if ( typeExtSubobject1 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject1. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject1 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtSubobject domains with domain numbers, setting domain number 3"<<endl;
	
	cout<<"extObjectV3rootDom4.setNumberSubobject( 3 );"<<endl;
	extObjectV3rootDom4.setNumberSubobject( 3 );

	//check the getDomain() methode from cVectorExtSubobject
	cout<<"pDomain = vecExtSubobjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtSubobjectE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}


	//check the getStandardDomain() method from cVectorExtSubobject
	pDomainStandard = vecExtSubobjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	cTypeExtSubobject typeExtSubobject3( 3 );
	if ( typeExtSubobject3 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject3. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject3 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtSubobject domains with domain numbers, setting domain number 4"<<endl;
	
	cout<<"extObjectV3rootDom4.setNumberSubobject( 4 );"<<endl;
	extObjectV3rootDom4.setNumberSubobject( 4 );

	//check the getDomain() methode from cVectorExtSubobject
	cout<<"pDomain = vecExtSubobjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtSubobjectE3V4Dom5.getDomain();
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
		//check the getDomain() methode from cVectorExtSubobject
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

	//check the getStandardDomain() method from cVectorExtSubobject
	pDomainStandard = vecExtSubobjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	if ( typeExtSubobject4 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject4. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject4 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtSubobject domains with domain numbers, setting domain number 5"<<endl;
	
	cout<<"extObjectV3rootDom4.setNumberSubobject( 5 );"<<endl;
	extObjectV3rootDom4.setNumberSubobject( 5 );

	//check the getDomain() methode from cVectorExtSubobject
	cout<<"pDomain = vecExtSubobjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtSubobjectE3V4Dom5.getDomain();
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
		//check the getDomain() methode from cVectorExtSubobject
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

	//check the getStandardDomain() method from cVectorExtSubobject
	pDomainStandard = vecExtSubobjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	if ( typeExtSubobject5 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject5. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject5 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtSubobject domains with domain numbers, setting domain number 6"<<endl;
	
	cout<<"extObjectV3rootDom4.setNumberSubobject( 6 );"<<endl;
	extObjectV3rootDom4.setNumberSubobject( 6 );

	//check the getDomain() methode from cVectorExtSubobject
	cout<<"pDomain = vecExtSubobjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtSubobjectE3V4Dom5.getDomain();
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
		//check the getDomain() methode from cVectorExtSubobject
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

	//check the getStandardDomain() method from cVectorExtSubobject
	pDomainStandard = vecExtSubobjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	if ( typeExtSubobject6 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject6. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject6 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtSubobject domains with domain numbers, setting domain number 13"<<endl;
	
	cout<<"extObjectV3rootDom4.setNumberSubobject( 13 );"<<endl;
	extObjectV3rootDom4.setNumberSubobject( 13 );

	//check the getDomain() methode from cVectorExtSubobject
	cout<<"pDomain = vecExtSubobjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtSubobjectE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}


	//check the getStandardDomain() method from cVectorExtSubobject
	pDomainStandard = vecExtSubobjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	cTypeExtSubobject typeExtSubobject13( 13 );
	if ( typeExtSubobject13 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject13. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject13 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	return iReturn;
}




/**
 * This method tests the method for the domains of the cVectorExtSubobject class.
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
	
	cout<<"cTypeExtSubobject typeExtSubobject( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject( 0 );

	cout<<"root.getValueDomains()->addDomain( typeExtSubobject, &vectorDomainE3Nat1Nat2Nat3 );"<<endl;
	root.getValueDomains()->addDomain( typeExtSubobject, &vectorDomainE3Nat1Nat2Nat3 );

	
	cout<<"cVectorExtSubobject vecExtSubobjectRD( 3, &root );"<<endl;
	cVectorExtSubobject vecExtSubobjectRD( 3, &root );
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectRD.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the external object element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectRD.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the getValueDomain() methode from cVectorExtSubobject
	if ( vecExtSubobjectRD.getValueDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainE3Nat1Nat2Nat3 == vecExtSubobjectRD.getValueDomain() ){
	
		cout<<"The &vectorDomainE3Nat1Nat2Nat3 is the domain for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The &vectorDomainE3Nat1Nat2Nat3 is not the domain for the external object element vector."<<endl;
		iReturn++;
	}

	/*check the getValueDomain(i=1..n) method of the set-vektor*/
	//test the getType() method
	cout<<"cDomain * pDomainD3 = vecExtSubobjectRD.getValueDomain();"<<endl;
	cDomain * pDomainD3 = vecExtSubobjectRD.getValueDomain();
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

	//check the getStandardDomain() method from cVectorExtSubobject
	cDomain * pDomainStandard = vecExtSubobjectRD.getStandardDomain();
	cDomain * pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtSubobject domains with domain numbers"<<endl;
	
	cout<<"cRoot rootDom4;"<<flush<<endl;
	cRoot rootDom4;
	
	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject, &vectorDomainE3Nat1Nat2Nat3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject, &vectorDomainE3Nat1Nat2Nat3 );

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
	
	cout<<"cTypeExtSubobject typeExtSubobject4( 4 );"<<endl;
	cTypeExtSubobject typeExtSubobject4( 4 );
	cout<<"rootDom4.getValueDomains()->addDomain( typeExtSubobject4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );"<<endl;
	rootDom4.getValueDomains()->addDomain( typeExtSubobject4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );
	
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

	cout<<"cTypeExtSubobject typeExtSubobject5( 5 );"<<endl;
	cTypeExtSubobject typeExtSubobject5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject5, &vectorDomainE2Int4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject5, &vectorDomainE2Int4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"cTypeExtSubobject typeExtSubobject6( 6 );"<<endl;
	cTypeExtSubobject typeExtSubobject6( 6 );
	cout<<"rootDom4.getValueDomains()->addDomain( typeExtSubobject6, &vectorDomainOE1Int8 );"<<endl;
	rootDom4.getValueDomains()->addDomain( typeExtSubobject6, &vectorDomainOE1Int8 );
	
	//create vector domain with
	cout<<"vector<cDomainSingle*> vecDomainsE1Int6( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int6( 1 );
	cout<<"vecDomainsE1Int6[ 0 ] = new cDomainIntegerBit( 6 );"<<endl;
	vecDomainsE1Int6[ 0 ] = new cDomainIntegerBit( 6 );
	cout<<"cDomainVector vectorDomainE1Int6( vecDomainsE1Int6 );"<<endl;
	cDomainVector vectorDomainE1Int6( vecDomainsE1Int6 );
	delete vecDomainsE1Int6[ 0 ];

	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject6, &vectorDomainE1Int6 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject6, &vectorDomainE1Int6 );

	
	cout<<"cExtSubobject extObjectV3rootDom4( 0, 0, &rootDom4 );"<<endl;
	cExtSubobject extObjectV3rootDom4( 0, 0, &rootDom4 );
	
	cout<<"cVectorExtSubobject vecExtSubobjectE3V4Dom5( 2, &extObjectV3rootDom4 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE3V4Dom5( 2, &extObjectV3rootDom4 );

	//check the getValueDomain() methode from cVectorExtSubobject
	cout<<"cDomain * pDomain = vecExtSubobjectE3V4Dom5.getValueDomain();"<<endl;
	cDomain * pDomain = vecExtSubobjectE3V4Dom5.getValueDomain();
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
		//check the getValueDomain() methode from cVectorExtSubobject
		if ( &vectorDomainE3Nat1Nat2Nat3 == vecExtSubobjectRD.getValueDomain() ){
		
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

	//check the getStandardDomain() method from cVectorExtSubobject
	pDomainStandard = vecExtSubobjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	cTypeElement * pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	if ( typeExtSubobject == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtSubobject domains with domain numbers, setting domain number 1"<<endl;
	
	cout<<"extObjectV3rootDom4.setNumberSubobject( 1 );"<<endl;
	extObjectV3rootDom4.setNumberSubobject( 1 );

	//check the getValueDomain() methode from cVectorExtSubobject
	cout<<"pDomain = vecExtSubobjectE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecExtSubobjectE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain defined for the external object element vector."<<endl;
		iReturn++;
	}

	//check the getStandardDomain() method from cVectorExtSubobject
	pDomainStandard = vecExtSubobjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	cTypeExtSubobject typeExtSubobject1( 1 );
	if ( typeExtSubobject1 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject1. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject1 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtSubobject domains with domain numbers, setting domain number 3"<<endl;
	
	cout<<"extObjectV3rootDom4.setNumberSubobject( 3 );"<<endl;
	extObjectV3rootDom4.setNumberSubobject( 3 );

	//check the getValueDomain() methode from cVectorExtSubobject
	cout<<"pDomain = vecExtSubobjectE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecExtSubobjectE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain defined for the external object element vector."<<endl;
		iReturn++;
	}


	//check the getStandardDomain() method from cVectorExtSubobject
	pDomainStandard = vecExtSubobjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	cTypeExtSubobject typeExtSubobject3( 3 );
	if ( typeExtSubobject3 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject3. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject3 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtSubobject domains with domain numbers, setting domain number 4"<<endl;
	
	cout<<"extObjectV3rootDom4.setNumberSubobject( 4 );"<<endl;
	extObjectV3rootDom4.setNumberSubobject( 4 );

	//check the getValueDomain() methode from cVectorExtSubobject
	cout<<"pDomain = vecExtSubobjectE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecExtSubobjectE3V4Dom5.getValueDomain();
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
		//check the getValueDomain() methode from cVectorExtSubobject
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
	
	//check the getValueDomain() methode from cVectorExtSubobject
	cout<<"pDomain = vecExtSubobjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtSubobjectE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain defined for the external object element vector."<<endl;
		iReturn++;
	}


	//check the getStandardDomain() method from cVectorExtSubobject
	pDomainStandard = vecExtSubobjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	if ( typeExtSubobject4 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject4. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject4 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtSubobject domains with domain numbers, setting domain number 5"<<endl;
	
	cout<<"extObjectV3rootDom4.setNumberSubobject( 5 );"<<endl;
	extObjectV3rootDom4.setNumberSubobject( 5 );

	//check the getValueDomain() methode from cVectorExtSubobject
	cout<<"pDomain = vecExtSubobjectE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecExtSubobjectE3V4Dom5.getValueDomain();
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
		//check the getValueDomain() methode from cVectorExtSubobject
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

	//check the getStandardDomain() method from cVectorExtSubobject
	pDomainStandard = vecExtSubobjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	if ( typeExtSubobject5 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject5. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject5 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtSubobject domains with domain numbers, setting domain number 6"<<endl;
	
	cout<<"extObjectV3rootDom4.setNumberSubobject( 6 );"<<endl;
	extObjectV3rootDom4.setNumberSubobject( 6 );

	//check the getValueDomain() methode from cVectorExtSubobject
	cout<<"pDomain = vecExtSubobjectE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecExtSubobjectE3V4Dom5.getValueDomain();
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
		//check the getValueDomain() methode from cVectorExtSubobject
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
	//check the getValueDomain() methode from cVectorExtSubobject
	cout<<"pDomain = vecExtSubobjectE3V4Dom5.getDomain();"<<endl;
	pDomain = vecExtSubobjectE3V4Dom5.getDomain();
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
		//check the getValueDomain() methode from cVectorExtSubobject
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

	//check the getStandardDomain() method from cVectorExtSubobject
	pDomainStandard = vecExtSubobjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	if ( typeExtSubobject6 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject6. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject6 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorExtSubobject domains with domain numbers, setting domain number 13"<<endl;
	
	cout<<"extObjectV3rootDom4.setNumberSubobject( 13 );"<<endl;
	extObjectV3rootDom4.setNumberSubobject( 13 );

	//check the getValueDomain() methode from cVectorExtSubobject
	cout<<"pDomain = vecExtSubobjectE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecExtSubobjectE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cout<<"Ther is correctly no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain defined for the external object element vector."<<endl;
		iReturn++;
	}


	//check the getStandardDomain() method from cVectorExtSubobject
	pDomainStandard = vecExtSubobjectE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeExtSubobject.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the external object element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *pTypeDomainStandard ){
	
			cout<<"The vecExtSubobjectRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vecExtSubobjectE3V4Dom5.getElementType();
	cTypeExtSubobject typeExtSubobject13( 13 );
	if ( typeExtSubobject13 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject13. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject13 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the external object element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the external object element vector is "<<
			vecExtSubobjectE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobjectE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectV3rootDom4 == vecExtSubobjectE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The extObjectV3rootDom4 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectV3rootDom4 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	return iReturn;
}




/**
 * This method tests setDefiningFibElement() and getDefiningFibElement()
 * method of the cVectorExtSubobject class.
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

	cout<<"cExtSubobject definingElement1( 1 );"<<endl;
	cExtSubobject definingElement1( 1 );
	cout<<"cExtSubobject definingElement2( 2 );"<<endl;
	cExtSubobject definingElement2( 2 );
	
	cout<<"cVectorExtSubobject vecExtSubobject( 2 );"<<endl;
	cVectorExtSubobject vecExtSubobject( 2 );

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobject.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the external object element vector."<<endl;
		iReturn++;
	}
	
	cout<<"vecExtSubobject.setDefiningFibElement( &definingElement1 );"<<endl;
	vecExtSubobject.setDefiningFibElement( &definingElement1 );

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobject.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &definingElement1 == vecExtSubobject.getDefiningFibElement() ){
	
		cout<<"The definingElement1 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The definingElement1 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}

	cout<<"vecExtSubobject.setDefiningFibElement( &definingElement2 );"<<endl;
	vecExtSubobject.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobject.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecExtSubobject.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}

	cout<<"vecExtSubobject.setDefiningFibElement( NULL );"<<endl;
	vecExtSubobject.setDefiningFibElement( NULL );

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobject.getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the external object element vector."<<endl;
		iReturn++;
	}

	cout<<"vecExtSubobject.setDefiningFibElement( &definingElement2 );"<<endl;
	vecExtSubobject.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vecExtSubobject.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecExtSubobject.getDefiningFibElement() ){
	
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
	
	cout<<"cTypeExtSubobject typeExtSubobject( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject( 0 );
	
	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject, &vectorDomainE3Nat1Nat2Nat3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject, &vectorDomainE3Nat1Nat2Nat3 );

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
	
	cout<<"cTypeExtSubobject typeExtSubobject4( 4 );"<<endl;
	cTypeExtSubobject typeExtSubobject4( 4 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject4, &vectorDomainE2Int2Int3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject4, &vectorDomainE2Int2Int3 );
	
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

	cout<<"cTypeExtSubobject typeExtSubobject5( 5 );"<<endl;
	cTypeExtSubobject typeExtSubobject5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject5, &vectorDomainE2Int4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject5, &vectorDomainE2Int4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"cTypeExtSubobject typeExtSubobject6( 6 );"<<endl;
	cTypeExtSubobject typeExtSubobject6( 6 );
	cout<<"rootDom4.getDomains()->addDomain( typeExtSubobject6, &vectorDomainOE1Int8 );"<<endl;
	rootDom4.getDomains()->addDomain( typeExtSubobject6, &vectorDomainOE1Int8 );
	
	
	cout<<"cExtSubobject extObjectDom0( 0, 2, &rootDom4 );"<<endl;
	cExtSubobject extObjectDom0( 0, 2, &rootDom4 );
	
	cout<<"cExtSubobject extObjectDom4( 4, 3, &extObjectDom0 );"<<endl;
	cExtSubobject extObjectDom4( 4, 3, &extObjectDom0 );

	cout<<"cExtSubobject extObjectDom5( 5, 4, &extObjectDom4 );"<<endl;
	cExtSubobject extObjectDom5( 5, 4, &extObjectDom4 );

	cout<<"cExtSubobject extObjectDom6( 6, 5, &extObjectDom5 );"<<endl;
	cExtSubobject extObjectDom6( 6, 5, &extObjectDom5 );
	
	cout<<"cExtSubobject extObjectDom11( 11, 6, &extObjectDom6 );"<<endl;
	cExtSubobject extObjectDom11( 11, 6, &extObjectDom6 );


	cout<<"cVectorExtSubobject vecExtSubobjectE0( 0 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE0( 0 );
	
	cout<<"vecExtSubobjectE0.setDefiningFibElement( &rootDom4 );"<<endl;
	vecExtSubobjectE0.setDefiningFibElement( &rootDom4 );

	cout<<"cVectorExtSubobject vecExtSubobject2E3V0( 3 );"<<endl;
	cVectorExtSubobject vecExtSubobject2E3V0( 3 );

	if ( vecExtSubobjectE0 == vecExtSubobject2E3V0 ){
	
		cout<<"The external object element vector vecExtSubobjectE0 is equal to vecExtSubobject2E3V0. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobjectE0 is not equal to vecExtSubobject2E3V0."<<endl;
		iReturn++;
	}
	

	cout<<"cVectorExtSubobject vecExtSubobject1E3( 3 );"<<endl;
	cVectorExtSubobject vecExtSubobject1E3( 3 );
	cout<<"vecExtSubobject1E3.setValue( 1, 1);"<<endl;
	vecExtSubobject1E3.setValue( 1, 1);
	cout<<"vecExtSubobject1E3.setValue( 2, 2);"<<endl;
	vecExtSubobject1E3.setValue( 2, 2);

	cout<<"cVectorExtSubobject vecExtSubobject1E2( 2 );"<<endl;
	cVectorExtSubobject vecExtSubobject1E2( 2 );
	cout<<"vecExtSubobject1E2.setValue( 1, 3);"<<endl;
	vecExtSubobject1E2.setValue( 1, 3);
	cout<<"vecExtSubobject1E2.setValue( 2, 2);"<<endl;
	vecExtSubobject1E2.setValue( 2, 2);

	cout<<"vecExtSubobject1E2.setDefiningFibElement( &rootDom4 );"<<endl;
	vecExtSubobject1E2.setDefiningFibElement( &rootDom4 );

	if ( vecExtSubobject1E2 == vecExtSubobject1E3 ){
	
		cout<<"The external object element vector vecExtSubobject1E2 is equal to vecExtSubobject1E3. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobject1E2 is not equal to vecExtSubobject1E3."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecExtSubobject1E2.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecExtSubobject1E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecExtSubobject1E2.getValue( uiActualElement ) ==
					vecExtSubobject1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly "<< 
					vecExtSubobject1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is "<<vecExtSubobject1E2.getValue( uiActualElement )<<
					" and not "<< vecExtSubobject1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}


	cout<<"vecExtSubobject1E3.setValue( 1, 0);"<<endl;
	vecExtSubobject1E3.setValue( 1, 0);
	cout<<"vecExtSubobject1E3.setValue( 2, 1);"<<endl;
	vecExtSubobject1E3.setValue( 2, 1);

	cout<<"cVectorExtSubobject vecExtSubobject2E3( vecExtSubobject1E3 );"<<endl;
	cVectorExtSubobject vecExtSubobject2E3( vecExtSubobject1E3 );

	cout<<"vecExtSubobject2E3.setDefiningFibElement( &rootDom4 );"<<endl;
	vecExtSubobject2E3.setDefiningFibElement( &rootDom4 );


	if ( vecExtSubobject2E3 == vecExtSubobject1E3 ){
	
		cout<<"The external object element vector vecExtSubobject2E3 is equal to vecExtSubobject1E3. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobject2E3 is not equal to vecExtSubobject1E3."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecExtSubobject2E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecExtSubobject2E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecExtSubobject2E3.getValue( uiActualElement ) ==
					vecExtSubobject1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly "<< 
					vecExtSubobject1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is "<<vecExtSubobject2E3.getValue( uiActualElement )<<
					" and not "<< vecExtSubobject1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	cout<<"vecExtSubobject1E3.setValue( 1, 0);"<<endl;
	vecExtSubobject1E3.setValue( 1, 0);
	cout<<"vecExtSubobject1E3.setValue( 2, 3);"<<endl;
	vecExtSubobject1E3.setValue( 2, 3);
	cout<<"vecExtSubobject1E3.setValue( 3, 7);"<<endl;
	vecExtSubobject1E3.setValue( 3, 7);

	cout<<"cVectorExtSubobject vecExtSubobject3E3( 3 );"<<endl;
	cVectorExtSubobject vecExtSubobject3E3( 3 );
	cout<<"vecExtSubobject3E3.setValue( 1, -7 );"<<endl;
	vecExtSubobject3E3.setValue( 1, -7 );
	cout<<"vecExtSubobject3E3.setValue( 2, 4 );"<<endl;
	vecExtSubobject3E3.setValue( 2, 4 );
	cout<<"vecExtSubobject3E3.setValue( 3, 8 );"<<endl;
	vecExtSubobject3E3.setValue( 3, 8 );

	cout<<"vecExtSubobject3E3.setDefiningFibElement( &extObjectDom0 );"<<endl;
	vecExtSubobject3E3.setDefiningFibElement( &extObjectDom0 );

	if ( vecExtSubobject3E3 == vecExtSubobject1E3 ){
	
		cout<<"The external object element vector vecExtSubobject3E3 is equal to vecExtSubobject1E3. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobject3E3 is not equal to vecExtSubobject1E3."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecExtSubobject3E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecExtSubobject3E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecExtSubobject3E3.getValue( uiActualElement ) ==
					vecExtSubobject1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly "<< 
					vecExtSubobject1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is "<<vecExtSubobject3E3.getValue( uiActualElement )<<
					" and not "<< vecExtSubobject1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	
	cout<<"cVectorExtSubobject vecExtSubobject2E4( 2 );"<<endl;
	cVectorExtSubobject vecExtSubobject2E4( 2 );
	cout<<"vecExtSubobject2E4.setValue( 1, -2 );"<<endl;
	vecExtSubobject2E4.setValue( 1, -2 );
	cout<<"vecExtSubobject2E4.setValue( 2, 3 );"<<endl;
	vecExtSubobject2E4.setValue( 2, 3 );

	cout<<"cVectorExtSubobject vecExtSubobject3E3( 3 );"<<endl;
	cVectorExtSubobject vecExtSubobject4E3( 3 );
	cout<<"vecExtSubobject4E3.setValue( 1, -7 );"<<endl;
	vecExtSubobject4E3.setValue( 1, -7 );
	cout<<"vecExtSubobject4E3.setValue( 2, 4 );"<<endl;
	vecExtSubobject4E3.setValue( 2, 4 );
	cout<<"vecExtSubobject4E3.setValue( 3, 8 );"<<endl;
	vecExtSubobject4E3.setValue( 3, 8 );

	cout<<"vecExtSubobject4E3.setDefiningFibElement( &extObjectDom4 );"<<endl;
	vecExtSubobject4E3.setDefiningFibElement( &extObjectDom4 );

	if ( vecExtSubobject4E3 == vecExtSubobject2E4 ){
	
		cout<<"The external object element vector vecExtSubobject4E3 is equal to vecExtSubobject2E4. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobject4E3 is not equal to vecExtSubobject2E4."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecExtSubobject4E3.getNumberOfElements();
				uiActualElement++ ){
			
			if ( ! vecExtSubobject4E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecExtSubobject4E3.getValue( uiActualElement ) ==
					vecExtSubobject2E4.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly "<< 
					vecExtSubobject2E4.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is "<<vecExtSubobject4E3.getValue( uiActualElement )<<
					" and not "<< vecExtSubobject2E4.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	
	cout<<"cVectorExtSubobject vecExtSubobject1E5( 2 );"<<endl;
	cVectorExtSubobject vecExtSubobject1E5( 2 );
	cout<<"vecExtSubobject1E5.setValue( 1, -7 );"<<endl;
	vecExtSubobject1E5.setValue( 1, -7 );
	cout<<"vecExtSubobject1E5.setValue( 2, 4 );"<<endl;
	vecExtSubobject1E5.setValue( 2, 4 );

	cout<<"cVectorExtSubobject vecExtSubobject5E3( 3 );"<<endl;
	cVectorExtSubobject vecExtSubobject5E3( 3 );
	cout<<"vecExtSubobject5E3.setValue( 1, -7 );"<<endl;
	vecExtSubobject5E3.setValue( 1, -7 );
	cout<<"vecExtSubobject5E3.setValue( 2, 4 );"<<endl;
	vecExtSubobject5E3.setValue( 2, 4 );
	cout<<"vecExtSubobject5E3.setValue( 3, 8 );"<<endl;
	vecExtSubobject5E3.setValue( 3, 8 );

	cout<<"vecExtSubobject5E3.setDefiningFibElement( &extObjectDom5 );"<<endl;
	vecExtSubobject5E3.setDefiningFibElement( &extObjectDom5 );

	if ( vecExtSubobject5E3 == vecExtSubobject1E5 ){
	
		cout<<"The external object element vector vecExtSubobject5E3 is equal to vecExtSubobject1E5. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobject5E3 is not equal to vecExtSubobject1E5."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecExtSubobject5E3.getNumberOfElements();
				uiActualElement++ ){
			
			if ( ! vecExtSubobject5E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecExtSubobject5E3.getValue( uiActualElement ) ==
					vecExtSubobject1E5.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly "<< 
					vecExtSubobject1E5.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is "<<vecExtSubobject5E3.getValue( uiActualElement )<<
					" and not "<< vecExtSubobject1E5.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	
	
	cout<<"cVectorExtSubobject vecExtSubobject1E6( 1 );"<<endl;
	cVectorExtSubobject vecExtSubobject1E6( 1 );
	cout<<"vecExtSubobject1E6.setValue( 1, -7 );"<<endl;
	vecExtSubobject1E6.setValue( 1, -7 );

	cout<<"cVectorExtSubobject vecExtSubobject6E3( 3 );"<<endl;
	cVectorExtSubobject vecExtSubobject6E3( 3 );
	cout<<"vecExtSubobject6E3.setValue( 1, -7 );"<<endl;
	vecExtSubobject6E3.setValue( 1, -7 );
	cout<<"vecExtSubobject6E3.setValue( 2, 128 );"<<endl;
	vecExtSubobject6E3.setValue( 2, 128 );
	cout<<"vecExtSubobject6E3.setValue( 3, -129 );"<<endl;
	vecExtSubobject6E3.setValue( 3, -129 );

	cout<<"vecExtSubobject6E3.setDefiningFibElement( &extObjectDom6 );"<<endl;
	vecExtSubobject6E3.setDefiningFibElement( &extObjectDom6 );

	if ( vecExtSubobject6E3 == vecExtSubobject1E6 ){
	
		cout<<"The external object element vector vecExtSubobject6E3 is equal to vecExtSubobject1E6. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobject6E3 is not equal to vecExtSubobject1E6."<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtSubobject6E3.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtSubobject1E6.storeXml( cerr );
		
		iReturn++;
	}
	
	
	cout<<"cVectorExtSubobject vecExtSubobjectCor7E3( 3 );"<<endl;
	cVectorExtSubobject vecExtSubobjectCor7E3( 3 );
	cout<<"vecExtSubobjectCor7E3.setValue( 1, -7 );"<<endl;
	vecExtSubobjectCor7E3.setValue( 1, -7 );
	cout<<"vecExtSubobjectCor7E3.setValue( 2, 128 );"<<endl;
	vecExtSubobjectCor7E3.setValue( 2, 128 );
	cout<<"vecExtSubobjectCor7E3.setValue( 3, -129 );"<<endl;
	vecExtSubobjectCor7E3.setValue( 3, -129 );

	cout<<"cVectorExtSubobject vecExtSubobject7E3( 3 );"<<endl;
	cVectorExtSubobject vecExtSubobject7E3( 3 );
	cout<<"vecExtSubobject7E3.setValue( 1, -7 );"<<endl;
	vecExtSubobject7E3.setValue( 1, -7 );
	cout<<"vecExtSubobject7E3.setValue( 2, 128 );"<<endl;
	vecExtSubobject7E3.setValue( 2, 128 );
	cout<<"vecExtSubobject7E3.setValue( 3, -129 );"<<endl;
	vecExtSubobject7E3.setValue( 3, -129 );

	cout<<"vecExtSubobject7E3.setDefiningFibElement( &extObjectDom11 ); (no such domain)"<<endl;
	vecExtSubobject7E3.setDefiningFibElement( &extObjectDom11 );

	if ( vecExtSubobject7E3 == vecExtSubobjectCor7E3 ){
	
		cout<<"The external object element vector vecExtSubobject7E3 is equal to vecExtSubobjectCor7E3. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobject7E3 is not equal to vecExtSubobjectCor7E3."<<endl;
		cerr<<"Changed vector:"<<endl;
		vecExtSubobject7E3.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtSubobjectCor7E3.storeXml( cerr );
		
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods when a domain is given, but shouldn't be checked"<<endl;
	
	cout<<"cVectorExtSubobject vecExtSubobject2E2( 2 );"<<endl;
	cVectorExtSubobject vecExtSubobject2E2( 2 );
	cout<<"vecExtSubobject2E2.setValue( 1, -58 );"<<endl;
	vecExtSubobject2E2.setValue( 1, -58 );
	cout<<"vecExtSubobject2E2.setValue( 2, 1234 );"<<endl;
	vecExtSubobject2E2.setValue( 2, 1234 );
	
	cVectorExtSubobject vecExtSubobject3E2( vecExtSubobject2E2 );

	cout<<"vecExtSubobject3E2.setDefiningFibElement( &extObjectDom5, false );"<<endl;
	vecExtSubobject3E2.setDefiningFibElement( &extObjectDom5, false );

	if ( vecExtSubobject3E2 == vecExtSubobject2E2 ){
	
		cout<<"The external object element vector vecExtSubobject3E2 is equal to vecExtSubobject2E2. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobject3E2 is not equal to vecExtSubobject2E2."<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtSubobject3E2.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtSubobject2E2.storeXml( cerr );
		iReturn++;
	}

	cout<<"cVectorExtSubobject vecExtSubobject8E3( 3 );"<<endl;
	cVectorExtSubobject vecExtSubobject8E3( 3 );
	cout<<"vecExtSubobject8E3.setValue( 1, -200 );"<<endl;
	vecExtSubobject8E3.setValue( 1, -200 );
	cout<<"vecExtSubobject8E3.setValue( 2, 4 );"<<endl;
	vecExtSubobject8E3.setValue( 2, 4 );
	cout<<"vecExtSubobject8E3.setValue( 3, 500 );"<<endl;
	vecExtSubobject8E3.setValue( 3, 500 );
	
	cVectorExtSubobject vecExtSubobject9E3( vecExtSubobject8E3 );

	cout<<"vecExtSubobject9E3.setDefiningFibElement( &extObjectDom5, false );"<<endl;
	vecExtSubobject9E3.setDefiningFibElement( &extObjectDom5, false );

	if ( vecExtSubobject9E3 == vecExtSubobject8E3 ){
	
		cout<<"The external object element vector vecExtSubobject9E3 is equal to vecExtSubobject8E3. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobject9E3 is not equal to vecExtSubobject8E3."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecExtSubobject9E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecExtSubobject9E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecExtSubobject9E3.getValue( uiActualElement ) ==
					vecExtSubobject8E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is correctly "<< 
					vecExtSubobject8E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"external object element vector is "<<vecExtSubobject9E3.getValue( uiActualElement )<<
					" and not "<< vecExtSubobject8E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests cVectorExtSubobject methods for manipulating the
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
	
	cout<<"cVectorExtSubobject vecExtSubobject( 3, &emptyRoot );"<<endl;
	cVectorExtSubobject vecExtSubobject( 3, &emptyRoot );

	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecExtSubobject.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecExtSubobject.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecExtSubobject.getValue( uiActualElement ) == (doubleFib)(0.0) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"external object element vector is "<<vecExtSubobject.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
		if ( vecExtSubobject.getVariable( uiActualElement ) == NULL ){
		
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

	cout<<"vecExtSubobject.setValue( 2, 2.2 )"<<endl;
	if ( vecExtSubobject.setValue( 2, 2.2 ) ){
	
		cout<<"The 2'th element of the external object element vector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecExtSubobject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the external object element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecExtSubobject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 2 ) == (doubleFib)(2.2) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 2.2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 2 )<<" and not 2.2 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the external object element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecExtSubobject.setValue( 2, 0.7 )"<<endl;
	if ( vecExtSubobject.setValue( 2, 0.7 ) ){
	
		cout<<"The 2'th element of the external object element vector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecExtSubobject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the external object element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecExtSubobject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the external object element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecExtSubobject.setValue( 1, 11 )"<<endl;
	if ( vecExtSubobject.setValue( 1, 11 ) ){
	
		cout<<"The 1'th element of the external object element vector is set. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecExtSubobject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 1 ) == (doubleFib)(11) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 1 )<<" and not 11 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the external object element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecExtSubobject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 2 ) == NULL ){
	
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
	cout<<endl<<"vecExtSubobject.setVariable( 1, pVariable1 )"<<endl;
	if ( vecExtSubobject.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the external object element vector is set to the variable 1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not set to the variable 1. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecExtSubobject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 1 ) == (doubleFib)(0) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecExtSubobject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the external object element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is a variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable1->setValue( 0.11 );"<<endl;
	pVariable1->setValue( 0.11 );
	
	if ( vecExtSubobject.getValue( 1 ) == (doubleFib)(0.11) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 0.11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 1 )<<" and not 0.11 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable1->setValue( 111 );"<<endl;
	pVariable1->setValue( 111 );
	
	if ( vecExtSubobject.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4 = emptyRoot.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable4 = emptyRoot.getInputVariable( 4 );
	cout<<endl<<"vecExtSubobject.setVariable( 2, pVariable4 )"<<endl;
	if ( vecExtSubobject.setVariable( 2, pVariable4 ) ){
	
		cout<<"The 2'th element of the external object element vector is set to the variable 4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not set to the variable 4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecExtSubobject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecExtSubobject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 2 ) == (doubleFib)(0.0) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 2 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 123 );"<<endl;
	pVariable4->setValue( 123 );
	
	if ( vecExtSubobject.getValue( 2 ) == (doubleFib)(123) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 123 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 2 )<<" and not 123 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 0.321 );"<<endl;
	pVariable4->setValue( 0.321  );
	
	if ( vecExtSubobject.getValue( 2 ) == (doubleFib)(0.321 ) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 0.321  . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 2 )<<" and not 0.321  . "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecExtSubobject.setVariable( 1, pVariable4 )"<<endl;
	if ( vecExtSubobject.setVariable( 1, pVariable4 ) ){
	
		cout<<"The 1'th element of the external object element vector is set to the variable 4. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not set to the variable 4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecExtSubobject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 1 ) == (doubleFib)(0.321) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 0.321 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 1 )<<" and not 0.321 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 1 ) == pVariable4 ){
	
		cout<<"The 1'th element of the external object element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecExtSubobject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 2 ) == (doubleFib)(0.321) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 0.321 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 2 )<<" and not 0.321 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 654.123 );"<<endl;
	pVariable4->setValue( 654.123 );
	
	if ( vecExtSubobject.getValue( 1 ) == (doubleFib)(654.123) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 654.123 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 1 )<<" and not 654.123 . "<<endl;
		iReturn++;
	}
	
	if ( vecExtSubobject.getValue( 2 ) == (doubleFib)(654.123) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 654.123 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 2 )<<" and not 654.123 . "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setValue() and setVariable() after each other method"<<endl;
	
	cout<<endl<<"vecExtSubobject.setValue( 1, 17 )"<<endl;
	if ( vecExtSubobject.setValue( 1, 17 ) ){
	
		cout<<"The 1'th element of the external object element vector is set to the value 17"<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not set to the value 17. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecExtSubobject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 1 ) == (doubleFib)(17) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 17 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 1 )<<" and not 17 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the external object element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is a variable. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecExtSubobject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 2 ) == (doubleFib)(654.123 ) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 654.123  . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 2 )<<" and not 654.123  . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 65 );"<<endl;
	pVariable4->setValue( 65 );
	
	if ( vecExtSubobject.getValue( 2 ) == (doubleFib)(65) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 2 )<<" and not 65 . "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecExtSubobject.setVariable( 1, pVariable1 )"<<endl;
	if ( vecExtSubobject.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the external object element vector is set to the varaiable 1"<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not set to the variable 1. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecExtSubobject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecExtSubobject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 2 ) == (doubleFib)(65 ) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 2 )<<" and not 65  . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the external object element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setVariable() methods with trying to set NULL"<<endl;
	
	cout<<endl<<"vecExtSubobject.setVariable( 1, NULL )"<<endl;
	if ( ! vecExtSubobject.setVariable( 1, NULL ) ){
	
		cout<<"The 1'th element of the external object element vector couldn't be set to NULL."<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector could be set to NULL. "<<endl;
		iReturn++;
	}
	cout<<endl<<"vecExtSubobject.setVariable( 2, NULL )"<<endl;
	if ( ! vecExtSubobject.setVariable( 2, NULL ) ){
	
		cout<<"The 2'th element of the external object element vector couldn't be set to NULL."<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector could be set to NULL. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecExtSubobject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"external object element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the external object element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the external object element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecExtSubobject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the external object element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getValue( 2 ) == (doubleFib)(65 ) ){
	
		cout<<"The 2'th element of the "<<
			"external object element vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the external object element vector is "<<
			vecExtSubobject.getValue( 2 )<<" and not 65  . "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 2 ) == pVariable4 ){
	
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
	
	//check vecExtSubobject.isUsedVariable()
	if ( vecExtSubobject.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecExtSubobject.isUsedVariable()
	if ( ! vecExtSubobject.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check isUsedVariable()
	if ( vecExtSubobject.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	
	set<cFibVariable*> setCorrectUsedVariables;
	setCorrectUsedVariables.insert( pVariable1 );
	setCorrectUsedVariables.insert( pVariable4 );
	//check getUsedVariables()
	cout<<"setUsedVariables = vecExtSubobject.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = vecExtSubobject.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	
	cout<<endl<<"vecExtSubobject.replaceVariable( pVariable1, pVariable4 )"<<endl;
	setCorrectUsedVariables.erase( pVariable1 );
	if ( vecExtSubobject.replaceVariable( pVariable1, pVariable4 ) ){
	
		cout<<"The pVariable1 of the propertyvector was replaced with pVariable4. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 of the propertyvector was not replaced with pVariable4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecExtSubobject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 1 ) == pVariable4 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecExtSubobject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check vecExtSubobject.isUsedVariable()
	if ( ! vecExtSubobject.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecExtSubobject.isUsedVariable()
	if ( ! vecExtSubobject.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecExtSubobject.isUsedVariable()
	if ( vecExtSubobject.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecExtSubobject.getUsedVariables(); "<<endl;
	setUsedVariables = vecExtSubobject.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecExtSubobject.replaceVariable( pVariable1, pVariable3 )"<<endl;
	if ( vecExtSubobject.replaceVariable( pVariable1, pVariable3 ) ){
	
		cout<<"The pVariable1 of the propertyvector was replaced with pVariable3. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 of the propertyvector was not replaced with pVariable3. "<<endl;
		iReturn++;
	}
	//check vecExtSubobject.isUsedVariable()
	if ( ! vecExtSubobject.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecExtSubobject.isUsedVariable()
	if ( vecExtSubobject.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecExtSubobject.getUsedVariables(); "<<endl;
	setUsedVariables = vecExtSubobject.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	cout<<endl<<"vecExtSubobject.replaceVariable( pVariable4, pVariable2 )"<<endl;
	setCorrectUsedVariables.erase( pVariable4 );
	setCorrectUsedVariables.insert( pVariable2 );
	if ( vecExtSubobject.replaceVariable( pVariable4, pVariable2 ) ){
	
		cout<<"The pVariable4 of the propertyvector was replaced with pVariable2. "<<endl;
	}else{
		cerr<<"Error: The pVariable4 of the propertyvector was not replaced with pVariable2. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecExtSubobject.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 1 ) == pVariable2 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecExtSubobject.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecExtSubobject.getVariable( 2 ) == pVariable2 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check vecExtSubobject.isUsedVariable()
	if ( ! vecExtSubobject.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecExtSubobject.isUsedVariable()
	if ( vecExtSubobject.isUsedVariable( pVariable2 ) ){
	
		cout<<"The pVariable2 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable2 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecExtSubobject.isUsedVariable()
	if ( ! vecExtSubobject.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecExtSubobject.isUsedVariable()
	if ( ! vecExtSubobject.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable4 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecExtSubobject.getUsedVariables(); "<<endl;
	setUsedVariables = vecExtSubobject.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	//check vecExtSubobject.isUsedVariable()
	if ( ! vecExtSubobject.isUsedVariable( NULL ) ){
	
		cout<<"The NULL is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The NULL is a used varible in the vector.  "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecExtSubobject.replaceVariable( NULL, pVariable2 )"<<endl;
	if ( ! vecExtSubobject.replaceVariable( NULL, pVariable2 ) ){
	
		cout<<"Can't correctly replace NULL of the propertyvector with pVariable2. "<<endl;
	}else{
		cerr<<"Error: Can replace NULL of the propertyvector with pVariable2. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecExtSubobject.replaceVariable( pVariable2, NULL )"<<endl;
	if ( ! vecExtSubobject.replaceVariable( pVariable2, NULL ) ){
	
		cout<<"Can't correctly replace pVariable2 of the propertyvector with NULL. "<<endl;
	}else{
		cerr<<"Error: Can replace pVariable2 of the propertyvector with NULL. "<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing resize() method"<<endl;
	
	cout<<"cVectorExtSubobject vecExtSubobjectResize1( 3 );"<<endl;
	cVectorExtSubobject vecExtSubobjectResize1( 3 );
	cout<<"vecExtSubobjectResize1.setValue( 1, -200 );"<<endl;
	vecExtSubobjectResize1.setValue( 1, -200 );
	cout<<"vecExtSubobjectResize1.setValue( 2, 4 );"<<endl;
	vecExtSubobjectResize1.setValue( 2, 4 );
	cout<<"vecExtSubobjectResize1.setValue( 3, 500 );"<<endl;
	vecExtSubobjectResize1.setValue( 3, 500 );
	
	cout<<"vecExtSubobjectResize1.resize( 5 );"<<endl;
	vecExtSubobjectResize1.resize( 5 );
	
	cVectorExtSubobject vecExtSubobjectResize1Correct1( 5 );
	vecExtSubobjectResize1Correct1.setValue( 1, -200 );
	vecExtSubobjectResize1Correct1.setValue( 2, 4 );
	vecExtSubobjectResize1Correct1.setValue( 3, 500 );
	
	if ( vecExtSubobjectResize1 == vecExtSubobjectResize1Correct1 ){
	
		cout<<"The external object element vector vecExtSubobjectResize1 is correctly resized. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobjectResize1 is not correctly resized. "<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtSubobjectResize1.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtSubobjectResize1Correct1.storeXml( cerr );
		iReturn++;
	}

	cout<<"vecExtSubobjectResize1.resize( 1 );"<<endl;
	vecExtSubobjectResize1.resize( 1 );
	
	cVectorExtSubobject vecExtSubobjectResize1Correct2( 1 );
	vecExtSubobjectResize1Correct2.setValue( 1, -200 );
	
	if ( vecExtSubobjectResize1 == vecExtSubobjectResize1Correct2 ){
	
		cout<<"The external object element vector vecExtSubobjectResize1 is correctly resized. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobjectResize1 is not correctly resized. "<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtSubobjectResize1.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtSubobjectResize1Correct2.storeXml( cerr );
		iReturn++;
	}

	cout<<"vecExtSubobjectResize1.resize( 0 );"<<endl;
	vecExtSubobjectResize1.resize( 0 );
	
	cVectorExtSubobject vecExtSubobjectResize1Correct3( 0 );
	
	if ( vecExtSubobjectResize1 == vecExtSubobjectResize1Correct3 ){
	
		cout<<"The external object element vector vecExtSubobjectResize1 is correctly resized. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobjectResize1 is not correctly resized. "<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtSubobjectResize1.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtSubobjectResize1Correct3.storeXml( cerr );
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing resize() method with vector with just variables"<<endl;
	
	cout<<"cVectorExtSubobject vecExtSubobjectResize2( 3 );"<<endl;
	cVectorExtSubobject vecExtSubobjectResize2( 3 );
	cout<<"vecExtSubobjectResize2.setVariable( 1, pVariable1 );"<<endl;
	vecExtSubobjectResize2.setVariable( 1, pVariable1 );
	cout<<"vecExtSubobjectResize2.setVariable( 2, pVariable3 );"<<endl;
	vecExtSubobjectResize2.setVariable( 2, pVariable3 );
	cout<<"vecExtSubobjectResize2.setVariable( 3, pVariable1 );"<<endl;
	vecExtSubobjectResize2.setVariable( 3, pVariable1 );
	
	cout<<"vecExtSubobjectResize2.resize( 5 );"<<endl;
	vecExtSubobjectResize2.resize( 5 );
	
	cVectorExtSubobject vecExtSubobjectResize2Correct1( 5 );
	vecExtSubobjectResize2Correct1.setVariable( 1, pVariable1 );
	vecExtSubobjectResize2Correct1.setVariable( 2, pVariable3 );
	vecExtSubobjectResize2Correct1.setVariable( 3, pVariable1 );
	
	if ( vecExtSubobjectResize2 == vecExtSubobjectResize2Correct1 ){
	
		cout<<"The external object element vector vecExtSubobjectResize2 is correctly resized. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobjectResize2 is not correctly resized. "<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtSubobjectResize2.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtSubobjectResize2Correct1.storeXml( cerr );
		iReturn++;
	}

	cout<<"vecExtSubobjectResize2.resize( 1 );"<<endl;
	vecExtSubobjectResize2.resize( 1 );
	
	cVectorExtSubobject vecExtSubobjectResize2Correct2( 1 );
	vecExtSubobjectResize2Correct2.setVariable( 1, pVariable1 );
	
	if ( vecExtSubobjectResize2 == vecExtSubobjectResize2Correct2 ){
	
		cout<<"The external object element vector vecExtSubobjectResize2 is correctly resized. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobjectResize2 is not correctly resized. "<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtSubobjectResize2.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtSubobjectResize2Correct2.storeXml( cerr );
		iReturn++;
	}

	cout<<"vecExtSubobjectResize2.resize( 0 );"<<endl;
	vecExtSubobjectResize2.resize( 0 );
	
	cVectorExtSubobject vecExtSubobjectResize2Correct3( 0 );
	
	if ( vecExtSubobjectResize2 == vecExtSubobjectResize2Correct3 ){
	
		cout<<"The external object element vector vecExtSubobjectResize2 is correctly resized. "<<endl;
	}else{
		cerr<<"Error: The external object element vector vecExtSubobjectResize2 is not correctly resized. "<<endl;
		/*check the elements of the set-vektor*/
		cerr<<"Changed vector:"<<endl;
		vecExtSubobjectResize2.storeXml( cerr );
		cerr<<"Correct vector:"<<endl;
		vecExtSubobjectResize2Correct3.storeXml( cerr );
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

	cout<<"cExtSubobject extObjectEmptyRoot( 3, 2, &emptyRoot );"<<endl;
	cExtSubobject extObjectEmptyRoot( 3, 2, &emptyRoot );

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
	
	cout<<"cTypeExtSubobject typeExtSubobject( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject( 0 );

	cout<<"rootD2.getDomains()->addDomain( typeExtSubobject, vectorDomainE2Nat4Nat5 );"<<endl;
	rootD2.getDomains()->addDomain( typeExtSubobject, vectorDomainE2Nat4Nat5 );

	//creat defined variables to set them later in the vector
	cout<<"rootD2.setNumberOfInputVariables( 4 )"<<endl;
	rootD2.setNumberOfInputVariables( 4 );

	cout<<"cExtSubobject extObjectRootD2( 4, 3, &rootD2 );"<<endl;
	cExtSubobject extObjectRootD2( 4, 3, &rootD2 );

	//create cVectorExtSubobjects to compare
	cout<<"cVectorExtSubobject vectorExtSubobjectE3( 3 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectE3( 3 );
	cout<<"cVectorExtSubobject vectorExtSubobjectE3RD2( 3, &rootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectE3RD2( 3, &rootD2 );
	cout<<"cVectorExtSubobject vectorExtSubobjectE2Re( 2, &extObjectEmptyRoot );"<<endl;
	cVectorExtSubobject vectorExtSubobjectE2Re( 2, &extObjectEmptyRoot );
	cout<<"cVectorExtSubobject vectorExtSubobjectE2RD2( 2, &rootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectE2RD2( 2, &rootD2 );
	cout<<"cVectorExtSubobject vectorExtSubobjectRD2( extObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectRD2( extObjectRootD2 );
	
	//vectors with changed values
	cout<<"cVectorExtSubobject vectorExtSubobjectRD2V2g17p2( 2, &extObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectRD2V2g17p2( 2, &extObjectRootD2 );
	vectorExtSubobjectRD2V2g17p2.setValue( 2, 17.2 );
	
	cout<<"cVectorExtSubobject vectorExtSubobjectE2RD2V2g17p2( 2, &rootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectE2RD2V2g17p2( 2, &rootD2 );
	vectorExtSubobjectE2RD2V2g17p2.setValue( 2, 17.2 );

	cout<<"cVectorExtSubobject vectorExtSubobjectE2RD2V2g17p2001( 2, &rootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectE2RD2V2g17p2001( 2, &rootD2 );
	vectorExtSubobjectE2RD2V2g17p2001.setValue( 2, 17.2001 );

	cout<<"cVectorExtSubobject vectorExtSubobjectRD2V1g17p2( 2, &extObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectRD2V1g17p2( 2, &extObjectRootD2 );
	vectorExtSubobjectRD2V1g17p2.setValue( 1, 17.2 );

	cout<<"cVectorExtSubobject vectorExtSubobjectRD2V1g1p1V2gm2p2( 2, &extObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectRD2V1g1p1V2gm2p2( 2, &extObjectRootD2 );
	vectorExtSubobjectRD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorExtSubobjectRD2V1g1p1V2gm2p2.setValue( 2, -2.2 );

	cout<<"cVectorExtSubobject vectorExtSubobjectE2RD2V1g1p1V2gm2p2( 2, &rootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectE2RD2V1g1p1V2gm2p2( 2, &rootD2 );
	vectorExtSubobjectE2RD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorExtSubobjectE2RD2V1g1p1V2gm2p2.setValue( 2, -2.2 );
	
	cout<<"cVectorExtSubobject vectorExtSubobjectRD2V1g1p1V2g2p2( 2, &extObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectRD2V1g1p1V2g2p2( 2, &extObjectRootD2 );
	vectorExtSubobjectRD2V1g1p1V2g2p2.setValue( 1, 1.1 );
	vectorExtSubobjectRD2V1g1p1V2g2p2.setValue( 2, 2.2 );

	//vectors with variables
	cFibVariable * pVariable1 = rootD2.getInputVariable( 1 );
	cFibVariable * pVariable2 = rootD2.getInputVariable( 2 );
	cFibVariable * pVariable1Re = emptyRoot.getInputVariable( 1 );
	//cFibVariable * pVariable2Re = emptyRoot.getInputVariable( 2 );

	cout<<"cVectorExtSubobject vectorExtSubobjectRD2V1gV1( 2, &extObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectRD2V1gV1( 2, &extObjectRootD2 );
	vectorExtSubobjectRD2V1gV1.setVariable( 1, pVariable1 );

	cout<<"cVectorExtSubobject vectorExtSubobjectE2RD2V1gV1( 2, &rootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectE2RD2V1gV1( 2, &rootD2 );
	vectorExtSubobjectE2RD2V1gV1.setVariable( 1, pVariable1 );

	cout<<"cVectorExtSubobject vectorExtSubobjectRD2V2gV1( 2, &extObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectRD2V2gV1( 2, &extObjectRootD2 );
	vectorExtSubobjectRD2V2gV1.setVariable( 2, pVariable1 );

	cout<<"cVectorExtSubobject vectorExtSubobjectRD2V2gV2( 2, &extObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectRD2V2gV2( 2, &extObjectRootD2 );
	vectorExtSubobjectRD2V2gV2.setVariable( 2, pVariable2 );

	cout<<"cVectorExtSubobject vectorExtSubobjectRD2V1gReV1( 2, &extObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectRD2V1gReV1( 2, &extObjectRootD2 );
	vectorExtSubobjectRD2V1gReV1.setVariable( 1, pVariable1Re );

	//vectors with changed values and variables
	cout<<"cVectorExtSubobject vectorExtSubobjectRD2V1gV1V2g1111( 2, &extObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectRD2V1gV1V2g1111( 2, &extObjectRootD2 );
	vectorExtSubobjectRD2V1gV1V2g1111.setVariable( 1, pVariable1 );
	vectorExtSubobjectRD2V1gV1V2g1111.setValue( 2, 1111 );

	cout<<"cVectorExtSubobject vectorExtSubobjectE2RD2V1gV1V2g1111( 2, &rootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectE2RD2V1gV1V2g1111( 2, &rootD2 );
	vectorExtSubobjectE2RD2V1gV1V2g1111.setVariable( 1, pVariable1 );
	vectorExtSubobjectE2RD2V1gV1V2g1111.setValue( 2, 1111 );

	cout<<"cVectorExtSubobject vectorExtSubobjectRD2V1gV1V2g111( 2, &extObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectRD2V1gV1V2g111( 2, &extObjectRootD2 );
	vectorExtSubobjectRD2V1gV1V2g111.setVariable( 1, pVariable1 );
	vectorExtSubobjectRD2V1gV1V2g111.setValue( 2, 111 );

	cout<<"cVectorExtSubobject vectorExtSubobjectRD2V1gV2V1g1111( 2, &rootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectRD2V1g111V2gV2( 2, &rootD2 );
	vectorExtSubobjectRD2V1g111V2gV2.setVariable( 1, pVariable2 );
	vectorExtSubobjectRD2V1g111V2gV2.setValue( 2, 1111 );

	cout<<"cVectorExtSubobject vectorExtSubobjectE2RD2V1g1111V2gV2( 2, &extObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectE2RD2V1gV2V2g1111( 2, &extObjectRootD2 );
	vectorExtSubobjectE2RD2V1gV2V2g1111.setValue( 1, 1111 );
	vectorExtSubobjectE2RD2V1gV2V2g1111.setVariable( 2, pVariable1 );

	cout<<"cVectorExtSubobject vectorExtSubobjectE2RD2V1gV1V2gV2( 2, &extObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectE2RD2V1gV1V2gV2( 2, &extObjectRootD2 );
	vectorExtSubobjectE2RD2V1gV1V2gV2.setVariable( 1, pVariable1 );
	vectorExtSubobjectE2RD2V1gV1V2gV2.setVariable( 2, pVariable2 );

	
	//check variable from different defining element

	cout<<"cExtObject extObjectExtObjectRootD2( 1, 2, &extObjectRootD2 );"<<endl;
	cExtObject extObjectExtObjectRootD2( 1, 2, &extObjectRootD2 );
	
	cout<<"extObjectExtObjectRootD2.setNumberOfSubobjects( 1 );"<<endl;
	extObjectExtObjectRootD2.setNumberOfSubobjects( 1 );
	cout<<"extObjectExtObjectRootD2.setNumberOfOutputVariables( 1, 2 );"<<endl;
	extObjectExtObjectRootD2.setNumberOfOutputVariables( 1, 2 );
	
	cout<<"cVectorExtSubobject vectorExtSubobjectE2FS2V1gV1V2gV2( 2, &extObjectExtObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectE2FS2V1gV1V2gV2( 2, &extObjectExtObjectRootD2 );
	vectorExtSubobjectE2FS2V1gV1V2gV2.setVariable( 1, pVariable1 );
	vectorExtSubobjectE2FS2V1gV1V2gV2.setVariable( 2, extObjectExtObjectRootD2.getOutputVariable( 1, 1 ) );

	cout<<"cVectorExtSubobject vectorExtSubobjectE2FS22V1gV1V2gVFS2( 2, &extObjectExtObjectRootD2 );"<<endl;
	cVectorExtSubobject vectorExtSubobjectE2FS22V1gV1V2gVFS2( 2, &extObjectExtObjectRootD2 );
	vectorExtSubobjectE2FS22V1gV1V2gVFS2.setVariable( 1, pVariable2 );
	vectorExtSubobjectE2FS22V1gV1V2gVFS2.setVariable( 2, pVariable1 );
	
	
	cout<<"cVectorProperty vectorProperty( 1 );"<<endl;
	cVectorProperty vectorProperty( 1 );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with vectorExtSubobjectE3
	cFibVector * actualVector = &vectorExtSubobjectE3;
	string szActualVectorName = "vectorExtSubobjectE3";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectE3RD2
	actualVector = &vectorExtSubobjectE3RD2;
	szActualVectorName = "vectorExtSubobjectE3RD2";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectE2Re
	actualVector = &vectorExtSubobjectE2Re;
	szActualVectorName = "vectorExtSubobjectE2Re";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );
	
	//compare with vectorExtSubobjectE2RD2
	actualVector = &vectorExtSubobjectE2RD2;
	szActualVectorName = "vectorExtSubobjectE2RD2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );
	
	//compare with vectorExtSubobjectE2Re
	actualVector = &vectorExtSubobjectRD2;
	szActualVectorName = "vectorExtSubobjectRD2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectRD2V2g17p2
	actualVector = &vectorExtSubobjectRD2V2g17p2;
	szActualVectorName = "vectorExtSubobjectRD2V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectRD2V2g17p2
	actualVector = &vectorExtSubobjectE2RD2V2g17p2;
	szActualVectorName = "vectorExtSubobjectE2RD2V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectE2RD2V2g17p2001
	actualVector = &vectorExtSubobjectE2RD2V2g17p2001;
	szActualVectorName = "vectorExtSubobjectE2RD2V2g17p2001";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectE2RD2V2g17p2001
	actualVector = &vectorExtSubobjectRD2V1g17p2;
	szActualVectorName = "vectorExtSubobjectRD2V1g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectRD2V1g1p1V2gm2p2
	actualVector = &vectorExtSubobjectRD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorExtSubobjectRD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectE2RD2V1g1p1V2gm2p2
	actualVector = &vectorExtSubobjectE2RD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorExtSubobjectE2RD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectE2RD2V1g1p1V2gm2p2
	actualVector = &vectorExtSubobjectRD2V1g1p1V2g2p2;
	szActualVectorName = "vectorExtSubobjectRD2V1g1p1V2g2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectRD2V1gV1
	actualVector = &vectorExtSubobjectRD2V1gV1;
	szActualVectorName = "vectorExtSubobjectRD2V1gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectE2RD2V1gV1
	actualVector = &vectorExtSubobjectE2RD2V1gV1;
	szActualVectorName = "vectorExtSubobjectE2RD2V1gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectRD2V2gV1
	actualVector = &vectorExtSubobjectRD2V2gV1;
	szActualVectorName = "vectorExtSubobjectRD2V2gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectRD2V2gV2
	actualVector = &vectorExtSubobjectRD2V2gV2;
	szActualVectorName = "vectorExtSubobjectRD2V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectRD2V1gReV1
	actualVector = &vectorExtSubobjectRD2V1gReV1;
	szActualVectorName = "vectorExtSubobjectRD2V1gReV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectRD2V1gV1V2g1111
	actualVector = &vectorExtSubobjectRD2V1gV1V2g1111;
	szActualVectorName = "vectorExtSubobjectRD2V1gV1V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectE2RD2V1gV1V2g1111
	actualVector = &vectorExtSubobjectE2RD2V1gV1V2g1111;
	szActualVectorName = "vectorExtSubobjectE2RD2V1gV1V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectRD2V1gV1V2g111
	actualVector = &vectorExtSubobjectRD2V1gV1V2g111;
	szActualVectorName = "vectorExtSubobjectRD2V1gV1V2g111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectRD2V1g111V2gV2
	actualVector = &vectorExtSubobjectRD2V1g111V2gV2;
	szActualVectorName = "vectorExtSubobjectRD2V1g111V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectE2RD2V1gV2V2g1111
	actualVector = &vectorExtSubobjectE2RD2V1gV2V2g1111;
	szActualVectorName = "vectorExtSubobjectE2RD2V1gV2V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectE2RD2V1gV1V2gV2
	actualVector = &vectorExtSubobjectE2RD2V1gV1V2gV2;
	szActualVectorName = "vectorExtSubobjectE2RD2V1gV1V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectE2FS2V1gV1V2gV2
	actualVector = &vectorExtSubobjectE2FS2V1gV1V2gV2;
	szActualVectorName = "vectorExtSubobjectE2FS2V1gV1V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorExtSubobjectE2FS22V1gV1V2gVFS2
	actualVector = &vectorExtSubobjectE2FS22V1gV1V2gVFS2;
	szActualVectorName = "vectorExtSubobjectE2FS22V1gV1V2gVFS2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorProperty
	actualVector = &vectorProperty;
	szActualVectorName = "vectorProperty";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3, "vectorExtSubobjectE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE3RD2, "vectorExtSubobjectE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2Re, "vectorExtSubobjectE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2, "vectorExtSubobjectE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2, "vectorExtSubobjectRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2g17p2, "vectorExtSubobjectRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2, "vectorExtSubobjectE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V2g17p2001, "vectorExtSubobjectE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g17p2, "vectorExtSubobjectRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2gm2p2, "vectorExtSubobjectRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1g1p1V2gm2p2, "vectorExtSubobjectE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g1p1V2g2p2, "vectorExtSubobjectRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1, "vectorExtSubobjectRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1, "vectorExtSubobjectE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV1, "vectorExtSubobjectRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V2gV2, "vectorExtSubobjectRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gReV1, "vectorExtSubobjectRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g1111, "vectorExtSubobjectRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2g1111, "vectorExtSubobjectE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1gV1V2g111, "vectorExtSubobjectRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectRD2V1g111V2gV2, "vectorExtSubobjectRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV2V2g1111, "vectorExtSubobjectE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2RD2V1gV1V2gV2, "vectorExtSubobjectE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS2V1gV1V2gV2, "vectorExtSubobjectE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorExtSubobjectE2FS22V1gV1V2gVFS2, "vectorExtSubobjectE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );


	return iReturn;
}



/**
 * This method tests the createInstance() method of the cVectorExtSubobject class.
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
	
	cout<<"cTypeExtSubobject typeExtSubobject( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject( 0 );
	
	cout<<"rootD2.getDomains()->addDomain( typeExtSubobject, vectorDomainE3Na2Nat3VE1Nat1 );"<<endl;
	rootD2.getDomains()->addDomain( typeExtSubobject, vectorDomainE3Na2Nat3VE1Nat1 );

	
	cout<<"cVectorExtSubobject vecExtSubobjectE4RD2 = cVectorExtSubobject( 4, &rootD2 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE4RD2 = cVectorExtSubobject( 4, &rootD2 );

	cout<<"cFibVector * vectorInstanceD1 = vecExtSubobjectE4RD2.createInstance( 1 );"<<endl;
	cFibVector * vectorInstanceD1 = vecExtSubobjectE4RD2.createInstance( 1 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vectorInstanceD1->getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vectorInstanceD1->getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	cTypeElement * pTypeExtSubobject = vectorInstanceD1->getElementType();
	if ( typeExtSubobject == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
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
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vectorInstanceD1->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the external object element vector."<<endl;
	}else if ( &rootD2 == vectorInstanceD1->getDefiningFibElement() ){
	
		cerr<<"Error: The rootD2 is the defining element for the external object element vector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is a defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vectorInstanceD1->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the external object element vector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD1;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 3 elements"<<endl;

	cout<<"cTypeExtSubobject typeExtSubobjectDom3( 3 );"<<endl;
	cTypeExtSubobject typeExtSubobjectDom3( 3 );

	cout<<"cFibVector * vectorInstanceD3 = vecExtSubobjectE4RD2.createInstance( 3 );"<<endl;
	cFibVector * vectorInstanceD3 = vecExtSubobjectE4RD2.createInstance( 3 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vectorInstanceD3->getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vectorInstanceD3->getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vectorInstanceD3->getElementType();
	if ( typeExtSubobject == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
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
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vectorInstanceD3->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the external object element vector."<<endl;
	}else if ( &rootD2 == vectorInstanceD3->getDefiningFibElement() ){
	
		cerr<<"Error: The rootD2 is the defining element for the external object element vector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is an defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
	if ( vectorInstanceD3->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the external object element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the external object element vector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD3;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 2 elements and rootD2 as an defining element"<<endl;

	cout<<"cFibVector * vectorInstanceD2RD2 = vecExtSubobjectE4RD2.createInstance( 2, &rootD2 );"<<endl;
	cFibVector * vectorInstanceD2RD2 = vecExtSubobjectE4RD2.createInstance( 2, &rootD2 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vectorInstanceD2RD2->getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vectorInstanceD2RD2->getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vectorInstanceD2RD2->getElementType();
	if ( typeExtSubobject == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
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
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vectorInstanceD2RD2->getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vectorInstanceD2RD2->getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
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
	
	cout<<"cExtSubobject extObjectRd2( 5, 3, &rootD2 );"<<endl;
	cExtSubobject extObjectRd2( 5, 3, &rootD2 );
	
	cout<<"cFibVector * vectorInstanceD2FsRD2 = vecExtSubobjectE4RD2.createInstance( 2, &extObjectRd2 );"<<endl;
	cFibVector * vectorInstanceD2FsRD2 = vecExtSubobjectE4RD2.createInstance( 2, &extObjectRd2 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorExtSubobject
	if ( vectorInstanceD2FsRD2->getVectorType() == "externSubobject" ){
	
		cout<<"The name of the external object element vector is correctly \"externSubobject\" . "<<endl;
	}else{
		cerr<<"Error: The name of the external object element vector is "<<
			vectorInstanceD2FsRD2->getVectorType()<<" but should be \"externSubobject\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorExtSubobject
	pTypeExtSubobject = vectorInstanceD2FsRD2->getElementType();
	cout<<"cTypeExtSubobject typeExtSubobject5( 5 );"<<endl;
	cTypeExtSubobject typeExtSubobject5( 5 );
	if ( typeExtSubobject5 == (*pTypeExtSubobject) ){
	
		cout<<"The type of the external object element vector is correctly equal to typeExtSubobject5. "<<endl;
	}else{
		cerr<<"Error: The type of external object element vector not equal to typeExtSubobject5 ."<<endl;
		iReturn++;
	}
	delete pTypeExtSubobject;
	
	//check the getNumberOfElements() methode from cVectorExtSubobject
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
	//check the getDefiningFibElement() methode from cVectorExtSubobject
	if ( vectorInstanceD2FsRD2->getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the external object element vector."<<endl;
		iReturn++;	
	}else if ( &extObjectRd2 == vectorInstanceD2FsRD2->getDefiningFibElement() ){
	
		cout<<"The extObjectRd2 is the defining element for the external object element vector. "<<endl;
	}else{
		cerr<<"Error: The extObjectRd2 is not the defining element for the external object element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorExtSubobject
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
	
	TiXmlDocument xmlDocVectorExtSubobject( szFilename );
	bool loadOkay = xmlDocVectorExtSubobject.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocVectorExtSubobject );
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
 * This method tests the storeXml() method of the cVectorExtSubobject class.
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
	
	cout<<"cTypeExtSubobject typeExtSubobject( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject( 0 );
	
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

	cout<<"rootD3.getDomains()->addDomain( typeExtSubobject, vectorDomainE3 );"<<endl;
	rootD3.getDomains()->addDomain( typeExtSubobject, vectorDomainE3 );

	//creat defined variables to set them later in the vector
	cout<<"rootD3.setNumberOfInputVariables( 6 )"<<endl;
	rootD3.setNumberOfInputVariables( 6 );

	cout<<"cVectorExtSubobject vecExtSubobjectE3( 3, &rootD3 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE3( 3, &rootD3 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	const char * szVectorPostion = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorExtSubobjectEmpty.xml" );
	ofstream fileVectorPostion( szVectorPostion );
	
	bool bStoreSuccesfull = vecExtSubobjectE3.storeXml( fileVectorPostion );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorPostion <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorPostion <<"\" failed."<<endl;
		iReturn++;
	}
	
	vector<char> vecElementTypeExtSubobject( 5, 'w' );
	vector<double> vecValuesExtSubobject( 5, 0.0 );
	
	iReturn += testXmlVector( szVectorPostion, "externSubobject",
		3, vecElementTypeExtSubobject, vecValuesExtSubobject );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector one value set"<<endl;
	
	cout<<"vecExtSubobjectE3.setValue( 1, 111 )"<<endl;
	vecExtSubobjectE3.setValue( 1, 111 );
	vecElementTypeExtSubobject[0] = 'w';
	vecValuesExtSubobject[0] = 111;
	
	szFileNameBuffer[0] = 0;
	const char * szVectorExtSubobjectRD3V1g111 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorExtSubobjectRD3V1g111.xml" );
	ofstream fileVectorPostioRD3V1g111n( szVectorExtSubobjectRD3V1g111 );
	
	bStoreSuccesfull = vecExtSubobjectE3.storeXml( fileVectorPostioRD3V1g111n );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorExtSubobjectRD3V1g111 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorExtSubobjectRD3V1g111 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorExtSubobjectRD3V1g111, "externSubobject",
		3, vecElementTypeExtSubobject, vecValuesExtSubobject );
	
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector all value set"<<endl;
	
	cout<<"vecExtSubobjectE3.setValue( 2, 123.456 )"<<endl;
	vecExtSubobjectE3.setValue( 2, 123.456  );
	vecElementTypeExtSubobject[1] = 'w';
	vecValuesExtSubobject[1] = 123.456;
	cout<<"vecExtSubobjectE3.setValue( 3, -123.456 )"<<endl;
	vecExtSubobjectE3.setValue( 3, -123.456 );
	vecElementTypeExtSubobject[2] = 'w';
	vecValuesExtSubobject[2] = -123.456;

	szFileNameBuffer[0] = 0;
	const char * szVectorExtSubobjectRD3T3 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorExtSubobjectRD3T3.xml" );
	ofstream fileVectorExtSubobjectRD3T3( szVectorExtSubobjectRD3T3 );
	
	bStoreSuccesfull = vecExtSubobjectE3.storeXml( fileVectorExtSubobjectRD3T3 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorExtSubobjectRD3T3 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorExtSubobjectRD3T3 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorExtSubobjectRD3T3, "externSubobject",
		3, vecElementTypeExtSubobject, vecValuesExtSubobject );

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
	
	cout<<"vecExtSubobjectE3.setVariable( 1, pVariable1 )"<<endl;
	vecExtSubobjectE3.setVariable( 1, pVariable1  );
	vecElementTypeExtSubobject[0] = 'v';
	vecValuesExtSubobject[0] = 1;
	cout<<"vecExtSubobjectE3.setVariable( 2, pVariable2 )"<<endl;
	vecExtSubobjectE3.setVariable( 2, pVariable2 );
	vecElementTypeExtSubobject[1] = 'v';
	vecValuesExtSubobject[1] = 2;
	cout<<"vecExtSubobjectE3.setVariable( 3, pVariable3 )"<<endl;
	vecExtSubobjectE3.setVariable( 3, pVariable3 );
	vecElementTypeExtSubobject[2] = 'v';
	vecValuesExtSubobject[2] = 3;

	szFileNameBuffer[0] = 0;
	const char * szVectorExtSubobjectRD3T4 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorExtSubobjectRD3T4.xml" );
	ofstream fileVectorExtSubobjectRD3T4( szVectorExtSubobjectRD3T4 );
	
	bStoreSuccesfull = vecExtSubobjectE3.storeXml( fileVectorExtSubobjectRD3T4 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorExtSubobjectRD3T4 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorExtSubobjectRD3T4 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorExtSubobjectRD3T4, "externSubobject",
		3, vecElementTypeExtSubobject, vecValuesExtSubobject );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector with variables and values"<<endl;
	
	cout<<"vecExtSubobjectE3.setVariable( 1, pVariable1 )"<<endl;
	vecExtSubobjectE3.setVariable( 1, pVariable1  );
	vecElementTypeExtSubobject[0] = 'v';
	vecValuesExtSubobject[0] = 1;
	cout<<"vecExtSubobjectE3.setValue( 2, -0.00124 )"<<endl;
	vecExtSubobjectE3.setValue( 2, -0.00124 );
	vecElementTypeExtSubobject[1] = 'w';
	vecValuesExtSubobject[1] = -0.00124;
	cout<<"vecExtSubobjectE3.setVariable( 3, pVariable3 )"<<endl;
	vecExtSubobjectE3.setVariable( 3, pVariable3 );
	vecElementTypeExtSubobject[2] = 'v';
	vecValuesExtSubobject[2] = 3;

	szFileNameBuffer[0] = 0;
	const char * szVectorExtSubobjectRD3T5 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorExtSubobjectRD3T5.xml" );
	ofstream fileVectorExtSubobjectRD3T5( szVectorExtSubobjectRD3T5 );
	
	bStoreSuccesfull = vecExtSubobjectE3.storeXml( fileVectorExtSubobjectRD3T5 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorExtSubobjectRD3T5 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorExtSubobjectRD3T5 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorExtSubobjectRD3T5, "externSubobject",
		3, vecElementTypeExtSubobject, vecValuesExtSubobject );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 5 d vector with variables and values"<<endl;
	
	cout<<"cVectorExtSubobject vecExtSubobjectRD5 = cVectorExtSubobject( 5, &rootD3 );"<<endl;
	cVectorExtSubobject vecExtSubobjectRD5 = cVectorExtSubobject( 5, &rootD3 );

	cout<<"vecExtSubobjectRD5.setVariable( 1, pVariable1 )"<<endl;
	vecExtSubobjectRD5.setVariable( 1, pVariable1  );
	vecElementTypeExtSubobject[0] = 'v';
	vecValuesExtSubobject[0] = 1;
	cout<<"vecExtSubobjectRD5.setValue( 2, -0.00124 )"<<endl;
	vecExtSubobjectRD5.setValue( 2, -0.00124 );
	vecElementTypeExtSubobject[1] = 'w';
	vecValuesExtSubobject[1] = -0.00124;
	cout<<"vecExtSubobjectRD5.setVariable( 3, pVariable3 )"<<endl;
	vecExtSubobjectRD5.setVariable( 3, pVariable3 );
	vecElementTypeExtSubobject[2] = 'v';
	vecValuesExtSubobject[2] = 3;
	cout<<"vecExtSubobjectRD5.setValue( 4, 1234 )"<<endl;
	vecExtSubobjectRD5.setValue( 4, 1234 );
	vecElementTypeExtSubobject[3] = 'w';
	vecValuesExtSubobject[3] = 1234;
	cout<<"vecExtSubobjectRD5.setValue( 5, 123.67 )"<<endl;
	vecExtSubobjectRD5.setValue( 5, 123.67   );
	vecElementTypeExtSubobject[4] = 'w';
	vecValuesExtSubobject[4] = 123.67 ;

	szFileNameBuffer[0] = 0;
	const char * szVectorExtSubobjectRD3T6 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorExtSubobjectRD3T6.xml" );
	ofstream fileVectorExtSubobjectRD3T6( szVectorExtSubobjectRD3T6 );
	
	bStoreSuccesfull = vecExtSubobjectRD5.storeXml( fileVectorExtSubobjectRD3T6 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorExtSubobjectRD3T6 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorExtSubobjectRD3T6 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorExtSubobjectRD3T6, "externSubobject",
		5, vecElementTypeExtSubobject, vecValuesExtSubobject );


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

	cout<<"cVectorExtSubobject vecExtSubobjectE0( 0 );"<<endl;
	cVectorExtSubobject vecExtSubobjectE0( 0 );

	//test get compressed size
	unsigned int uiCompressedSize = 0;
	if ( (unsigned int)(vecExtSubobjectE0.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtSubobjectE0.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtSubobjectE0.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	cout<<"vecExtSubobjectE0.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bool bStoreSuccesfull = vecExtSubobjectE0.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cExtSubobjectE0[] = { (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtSubobjectE0, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a external object element vector with 2 elements"<<endl;
	
	cout<<"cRoot root1;"<<endl;
	cRoot root1;
	
	cout<<"cVectorExtSubobject vecExtSubobject1E2Ch( 2, &root1 );"<<endl;
	cVectorExtSubobject vecExtSubobject1E2Ch( 2, &root1 );
	cout<<"vecExtSubobject1E2Ch.setValue( 1, 4 );"<<endl;
	vecExtSubobject1E2Ch.setValue( 1, 4 );
	cout<<"vecExtSubobject1E2Ch.setValue( 2, 6 );"<<endl;
	vecExtSubobject1E2Ch.setValue( 2, 6 );
	
	//test get compressed size
	uiCompressedSize = 0;
	if ( (unsigned int)(vecExtSubobject1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtSubobject1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtSubobject1E2Ch.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtSubobject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtSubobject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	short sNumberOfRestBitCorrect = 0;
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
	const char cExtSubobjectE2[] = { (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtSubobjectE2, 1 );

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a external object element vector with 2 elements and a domain"<<endl;

	//create vector domain with tree elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat1Nat7Nat6( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat1Nat7Nat6( 2 );
	cout<<"vecDomainsE2Nat1Nat7Nat6[ 0 ] = new cDomainNaturalNumberBit( 7 );"<<endl;
	vecDomainsE2Nat1Nat7Nat6[ 0 ] = new cDomainNaturalNumberBit( 7 );
	cout<<"vecDomainsE2Nat1Nat7Nat6[ 1 ] = new cDomainNaturalNumberBit( 6 );"<<endl;
	vecDomainsE2Nat1Nat7Nat6[ 1 ] = new cDomainNaturalNumberBit( 6 );
	cout<<"cDomainVector vectorDomainE2Nat1Nat7Nat6( vecDomainsE2Nat1Nat7Nat6 );"<<endl;
	cDomainVector vectorDomainE2Nat1Nat7Nat6( vecDomainsE2Nat1Nat7Nat6 );
	delete vecDomainsE2Nat1Nat7Nat6[ 0 ];
	delete vecDomainsE2Nat1Nat7Nat6[ 1 ];
	
	cout<<"cTypeExtSubobject typeExtSubobject( 0 );"<<endl;
	cTypeExtSubobject typeExtSubobject( 0 );

	cout<<"root1.getDomains()->addDomain( typeExtSubobject, &vectorDomainE2Nat1Nat7Nat6 );"<<endl;
	root1.getDomains()->addDomain( typeExtSubobject, &vectorDomainE2Nat1Nat7Nat6 );
	
	//test get compressed size
	uiCompressedSize = (1 + 7) + (1 + 6);
	if ( (unsigned int)(vecExtSubobject1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtSubobject1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtSubobject1E2ChDomE2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtSubobject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtSubobject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = (char)0x0C;
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
	const char cExtSubobjectE2DomE2[] = { (char)0x08, (char)0x0C };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtSubobjectE2DomE2, 2 );
	
	
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

	cout<<"vecExtSubobject1E2Ch.setVariable( 1, pVariable1);"<<endl;
	vecExtSubobject1E2Ch.setVariable( 1, pVariable1);
	cout<<"vecExtSubobject1E2Ch.setVariable( 2, pVariable2);"<<endl;
	vecExtSubobject1E2Ch.setVariable( 2, pVariable2);

	//test get compressed size
	uiCompressedSize = 2 * 9;
	if ( (unsigned int)(vecExtSubobject1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtSubobject1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtSubobject1E2Var.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtSubobject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtSubobject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cExtSubobjectE2Var[] = { (char)0x03, (char)0x0A, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtSubobjectE2Var, 3 );


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

	cout<<"cTypeExtSubobject typeExtSubobject3( 3 );"<<endl;
	cTypeExtSubobject typeExtSubobject3( 3 );
	
	cout<<"rootD2.getDomains()->addDomain( typeExtSubobject3, &vectorDomainE2 );"<<endl;
	rootD2.getDomains()->addDomain( typeExtSubobject3, &vectorDomainE2 );

	cout<<"cTypeVariable typeVariable;"<<endl;
	cTypeVariable typeVariable;

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB3( 3 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB3( 3 );

	cout<<"rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB3 );"<<endl;
	rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB3 );
	
	cout<<"cExtSubobject defExtSubobjectNr3( 3, 2, &rootD2 );"<<endl;
	cExtSubobject defExtSubobjectNr3( 3, 2, &rootD2  );
	
	cout<<"vecExtSubobject1E2Ch.setDefiningFibElement( &defExtSubobjectNr3 );"<<endl;
	vecExtSubobject1E2Ch.setDefiningFibElement( &defExtSubobjectNr3 );
	
	cout<<"vecExtSubobject1E2Ch.setValue( 2, 3 );"<<endl;
	vecExtSubobject1E2Ch.setValue( 2, 3 );

	//test get compressed size
	uiCompressedSize = 4 + 3;
	if ( (unsigned int)(vecExtSubobject1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtSubobject1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtSubobject1E2DomNr3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtSubobject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtSubobject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cExtSubobjectE2Dom[] = { (char)ucRestBitCorrect };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtSubobjectE2Dom, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a external object element vector 3 elements"<<endl;

	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainE3Nat5Nat8Nat8( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainE3Nat5Nat8Nat8( 3 );
	cout<<"vecDomainE3Nat5Nat8Nat8[ 0 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainE3Nat5Nat8Nat8[ 0 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainE3Nat5Nat8Nat8[ 1 ] = new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomainE3Nat5Nat8Nat8[ 1 ] = new cDomainNaturalNumberBit( 8 );
	cout<<"vecDomainE3Nat5Nat8Nat8[ 2 ] = new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomainE3Nat5Nat8Nat8[ 2 ] = new cDomainNaturalNumberBit( 8 );
	cout<<"cDomainVector vectorDomainE3Nat5Nat8Nat8( vecDomainE3Nat5Nat8Nat8 );"<<endl;
	cDomainVector vectorDomainE3Nat5Nat8Nat8( vecDomainE3Nat5Nat8Nat8 );
	delete vecDomainE3Nat5Nat8Nat8[ 0 ];
	delete vecDomainE3Nat5Nat8Nat8[ 1 ];
	delete vecDomainE3Nat5Nat8Nat8[ 2 ];

	cout<<"cTypeExtSubobject typeExtSubobject9( 9 );"<<endl;
	cTypeExtSubobject typeExtSubobject9( 9 );
	
	cout<<"rootD2.getDomains()->addDomain( typeExtSubobject9, &vectorDomainE3Nat5Nat8Nat8 );"<<endl;
	rootD2.getDomains()->addDomain( typeExtSubobject9, &vectorDomainE3Nat5Nat8Nat8 );

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB8( 8 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB8( 8 );

	cout<<"rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB8 );"<<endl;
	rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB8 );
	
	cout<<"cExtSubobject defExtSubobjectNr9( 9, 3 );"<<endl;
	cExtSubobject defExtSubobjectNr9( 9, 3  );
	
	cout<<"rootD2.setMainFibObject( &defExtSubobjectNr9 );"<<endl;
	rootD2.setMainFibObject( &defExtSubobjectNr9 );
	
	
	cout<<"cVectorExtSubobject vecExtSubobject1E3( 3, &defExtSubobjectNr9 );"<<endl;
	cVectorExtSubobject vecExtSubobject1E3( 3, &defExtSubobjectNr9 );
	
	cout<<"vecExtSubobject1E3.setVariable( 1, pVariable2 );"<<endl;
	vecExtSubobject1E3.setVariable( 1, pVariable2 );
	cout<<"vecExtSubobject1E3.setVariable( 2, pVariable1 );"<<endl;
	vecExtSubobject1E3.setVariable( 2, pVariable1);
	cout<<"vecExtSubobject1E3.setValue( 3, 5 );"<<endl;
	vecExtSubobject1E3.setValue( 3, 5 );

	//test get compressed size
	uiCompressedSize = 2 * 9 + (1 + 8);
	if ( (unsigned int)(vecExtSubobject1E3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtSubobject1E3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtSubobject1E3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtSubobject1E3.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtSubobject1E3.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cVecExtSubobject1E3[] = { (char)0x05, (char)0x06, (char)0x28, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cVecExtSubobject1E3, 4 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a external object element vector with a restbit of 4"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtSubobject1E3R4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x0F;
	cNumberOfRestBit = 4;
	cout<<"vecExtSubobject1E3.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtSubobject1E3.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cVecExtSubobject1E3R4[] = { (char)0x5F, (char)0x60, (char)0x80, (char)0x02 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cVecExtSubobject1E3R4, 4 );
	
	
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

	cout<<"cTypeExtSubobject typeExtSubobject4( 4 );"<<endl;
	cTypeExtSubobject typeExtSubobject4( 4 );
	
	cout<<"rootD2.getDomains()->addDomain( typeExtSubobject4, &vectorDomainE2Nat3Nat4 );"<<endl;
	rootD2.getDomains()->addDomain( typeExtSubobject4, &vectorDomainE2Nat3Nat4 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainE1Nat3( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainE1Nat3( 1 );
	cout<<"vecDomainE1Nat3[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainE1Nat3[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE1Nat3( vecDomainE1Nat3 );"<<endl;
	cDomainVector vectorDomainE1Nat3( vecDomainE1Nat3 );
	delete vecDomainE1Nat3[ 0 ];
	
	cout<<"rootD2.getDomains()->addDomain( typeExtSubobject, &vectorDomainE1Nat3 );"<<endl;
	rootD2.getDomains()->addDomain( typeExtSubobject, &vectorDomainE1Nat3 );

	
	cout<<"rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB3 );"<<endl;
	rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB3 );

	cout<<"cExtSubobject extObjectElementNr4( 4, 2 );"<<endl;
	cExtSubobject extObjectElementNr4( 4, 2 );
	
	cout<<"rootD2.setMainFibObject( &extObjectElementNr4 );"<<endl;
	rootD2.setMainFibObject( &extObjectElementNr4 );
	
	cout<<"vecExtSubobject1E2Ch.setDefiningFibElement( &extObjectElementNr4 );"<<endl;
	vecExtSubobject1E2Ch.setDefiningFibElement( &extObjectElementNr4 );
	
	//test get compressed size
	uiCompressedSize = 4 + 5;
	if ( (unsigned int)(vecExtSubobject1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtSubobject1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtSubobject1E2Dom4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtSubobject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtSubobject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cExtSubobjectE2Dom1[] = { (char)0x63, (char)0x00 };// 001 1  0011 0
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtSubobjectE2Dom1, 2 );
	
	
	cout<<endl<<"extObjectElementNr4.setNumberSubobject( 2 );"<<endl;
	extObjectElementNr4.setNumberSubobject( 2 );
	
	cout<<"vecExtSubobject1E2Ch.setDefiningFibElement( &extObjectElementNr4 );"<<endl;
	vecExtSubobject1E2Ch.setDefiningFibElement( &extObjectElementNr4 );
	
	//test get compressed size
	uiCompressedSize = 0;
	if ( (unsigned int)(vecExtSubobject1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtSubobject1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtSubobject1E2Dom3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtSubobject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtSubobject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cExtSubobjectE2Dom3[] = { (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtSubobjectE2Dom3, 1 );

	
	cout<<endl<<"extObjectElementNr4.setNumberSubobject( 5 );"<<endl;
	extObjectElementNr4.setNumberSubobject( 5 );
	
	cout<<"vecExtSubobject1E2Ch.setDefiningFibElement( &extObjectElementNr4 );"<<endl;
	vecExtSubobject1E2Ch.setDefiningFibElement( &extObjectElementNr4 );
	
	//test get compressed size
	if ( (unsigned int)(vecExtSubobject1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecExtSubobject1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecExtSubobject1E2Dom5.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecExtSubobject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecExtSubobject1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtSubobjectE2Dom3, 1 );

	
	
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
	
	cout<<"cFibVector * pVecExtSubobjectDestination = new cVectorExtSubobject( 2 );"<<endl;
	cFibVector  * pVecExtSubobjectDestination = new cVectorExtSubobject( 2 );
	
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
			unsigned int uiNumberOfExtSubobjects = 0;
			if ( (rand() % 10) != 0 ){
				uiNumberOfExtSubobjects = (rand() % 3 + 1) * (rand() % 4 + 1) + (rand() % 4);
			}else{
				uiNumberOfExtSubobjects = 0;
			}
			cout<<"pVecSource = new cVectorExtSubobject( "<< uiNumberOfExtSubobjects <<", &emptyRoot ); "<<endl;
			pVecSource = new cVectorExtSubobject( uiNumberOfExtSubobjects, &emptyRoot );
			
			pVecEqual = pVecSource;
		}else{//create non cVectorExtSubobject vector
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
			pVecEqual = new cVectorExtSubobject( pVecSource->getNumberOfElements(), &emptyRoot  );
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
		cout<<"(* pVecExtSubobjectDestination) = (* pVecSource );"<<endl;
		(* pVecExtSubobjectDestination) = (* pVecSource );
		
		//test the created vector
		if ( (*pVecExtSubobjectDestination) == ( * pVecEqual) ){
		
			cout<<"The vecExtSubobjectDestination is correct . "<<endl;
		}else{
			cerr<<"Error: The vecExtSubobjectDestination is not correct ."<<endl;
			iReturn++;
		}
		
		if ( pVecEqual != pVecSource ){
			//pVecEqual and pVecSource are different vectors
			delete pVecEqual;
		}
		delete pVecSource;
	}
	delete pVecExtSubobjectDestination;
	
	return iReturn;
}




















