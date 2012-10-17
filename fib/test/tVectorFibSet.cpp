/**
 * @file tVectorFibSet
 * file name: tVectorFibSet.cpp
 * @author Betti Oesterholz
 * @date 06.12.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cVectorFibSet.
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
 * This file contains the test for the class cVectorFibSet,
 * which represents the vector for positions.
 *
 *
 *
 *  What's tested of class cVectorFibSet:
 * 	- cVectorFibSet( unsignedIntFib iNumberOfElements=2, cFibElement * pDefiningSetElement=NULL );
 * 	- cVectorFibSet( cFibSet & definingSetElement );
 * 	- cVectorFibSet( const cVectorFibSet & vector, cFibElement * definingFibElement = NULL );
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
 */
/*
History:
06.12.2011  Oesterholz  created
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/


#include "version.h"

#include "cVectorFibSet.h"
#include "cVectorArea.h"
#include "cVectorProperty.h"
#include "cTypeFibSet.h"
#include "cTypeVariable.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainIntegerBit.h"
#include "cDomainVector.h"
#include "cDomainVectorOpenEnd.h"
#include "cRoot.h"
#include "cPoint.h"
#include "cFibSet.h"

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
	
	cout<<endl<<"Running Test for cVectorFibSet methods"<<endl;
	cout<<      "======================================"<<endl;

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
 * This method tests the constructors of the cVectorFibSet class.
 *
 * constructors tested:
 * 	- cVectorFibSet( unsignedIntFib iNumberOfElements=2, cFibElement * pDefiningSetElement=NULL );
 * 	- cVectorFibSet( cFibSet & definingSetElement );
 * 	- cVectorFibSet( const cVectorFibSet & vector, cFibElement * definingFibElement = NULL );
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cVectorFibSet"<<endl;

	cout<<"cTypeFibSet typeFibSet;"<<endl;
	cTypeFibSet typeFibSet;
	
	cout<<"cVectorFibSet vecFibSet;"<<endl;
	cVectorFibSet vecFibSet;


	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSet.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSet.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	
	//check the getElementType() methode from cVectorFibSet
	cTypeElement * pTypeFibSet = vecFibSet.getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSet.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSet.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibSet.getNumberOfElements(); 
			uiActualElement++ ){
		
		if ( ! vecFibSet.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibSet.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vecFibSet.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSet.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the set-element vector."<<endl;
		iReturn++;
	}

	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSet.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the set-element vector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibSet with 3 elements"<<endl;

	cout<<"cVectorFibSet vecFibSetE3( 3 );"<<endl;
	cVectorFibSet vecFibSetE3( 3 );


	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3.getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the set-element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibSetE3.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibSet.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibSetE3.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vecFibSetE3.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSetE3.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the set-element vector."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibSet with 4 elements and an defining element"<<endl;

	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;

	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Nat1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Nat1( 1 );
	cout<<"vecDomainsE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomainE1Nat1( vecDomainsE1Nat1 );"<<endl;
	cDomainVector vectorDomainE1Nat1( vecDomainsE1Nat1 );
	delete vecDomainsE1Nat1[ 0 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 3 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE1Nat1;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE1Nat1;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE3Na2Nat3VE1Nat1 );
	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];

	cout<<"rootD2.getDomains()->addDomain( typeFibSet, vectorDomainE3Na2Nat3VE1Nat1 );"<<endl;
	rootD2.getDomains()->addDomain( typeFibSet, vectorDomainE3Na2Nat3VE1Nat1 );

	
	cout<<"cVectorFibSet vecFibSetE4RD2 = cVectorFibSet( 4, &rootD2 );"<<endl;
	cVectorFibSet vecFibSetE4RD2 = cVectorFibSet( 4, &rootD2 );


	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE4RD2.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE4RD2.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE4RD2.getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE4RD2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the set-element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE4RD2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibSetE4RD2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibSetE4RD2.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibSetE4RD2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vecFibSetE4RD2.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE4RD2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecFibSetE4RD2.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSetE4RD2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE1Nat1 == (*(vecFibSetE4RD2.getDomain())) ){
	
		cout<<"The vectorDomainE1Nat1 is the domain for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1Nat1 is not the domain for the set-element vector."<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibSet with a set-element as defining element"<<endl;

	cout<<"cFibSet fibSetV4( 4 );"<<endl;
	cFibSet fibSetV4( 4 );
	
	cout<<"cVectorFibSet vecFibSetE4( 4, &fibSetV4 );"<<endl;
	cVectorFibSet vecFibSetE4( 4, &fibSetV4 );

	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE4.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE4.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE4.getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE4.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the set-element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE4.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibSetE4.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibSetE4.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibSetE4.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vecFibSetE4.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE4.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV4 == vecFibSetE4.getDefiningFibElement() ){
	
		cout<<"The fibSetV4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSetE4.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the set-element vector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibSet with a set-element as defining element, wich has other than the vector elemnts defined variables"<<endl;
	
	cout<<"cVectorFibSet vecFibSetE3V4( 3, &fibSetV4 );"<<endl;
	cVectorFibSet vecFibSetE3V4( 3, &fibSetV4 );

	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3V4.getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the set-element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibSetE3V4.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibSetE3V4.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibSetE3V4.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vecFibSetE3V4.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV4 == vecFibSetE3V4.getDefiningFibElement() ){
	
		cout<<"The fibSetV4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSetE3V4.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the set-element vector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibSet with a set-element as defining element, wich has domain number set"<<endl;
	
	cout<<"cRoot rootDom4;"<<flush<<endl;
	cRoot rootDom4;
	
	cout<<"rootDom4.getDomains()->addDomain( typeFibSet, vectorDomainE3Na2Nat3VE1Nat1 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet, vectorDomainE3Na2Nat3VE1Nat1 );

	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Int2Int3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Int2Int3( 2 );
	cout<<"vecDomainsE2Int2Int3[ 0 ] = new cDomainIntegerBit( 2 );"<<endl;
	vecDomainsE2Int2Int3[ 0 ] = new cDomainIntegerBit( 2 );
	cout<<"vecDomainsE2Int2Int3[ 1 ] = new cDomainIntegerBit( 3 );"<<endl;
	vecDomainsE2Int2Int3[ 1 ] = new cDomainIntegerBit( 3 );
	cout<<"cDomainVector vectorDomainE1Nat1( vecDomainsE2Int2Int3 );"<<endl;
	cDomainVector vectorDomainE2Int2Int3( vecDomainsE2Int2Int3 );
	delete vecDomainsE2Int2Int3[ 0 ];
	delete vecDomainsE2Int2Int3[ 1 ];
	
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int2Int3;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int2Int3;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibSet typeFibSet4( 4 );"<<endl;
	cTypeFibSet typeFibSet4( 4 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibSet4, vectorDomainE3Na4Nat5VE2NInt2Int3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet4, vectorDomainE3Na4Nat5VE2NInt2Int3 );
	
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

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int4Int5;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int4Int5;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibSet typeFibSet5( 5 );"<<endl;
	cTypeFibSet typeFibSet5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibSet5, vectorDomainE3Na4Nat5VE2NInt4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet5, vectorDomainE3Na4Nat5VE2NInt4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainOE1Int8;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainOE1Int8;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibSet typeFibSet6( 6 );"<<endl;
	cTypeFibSet typeFibSet6( 6 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibSet6, vectorDomainE3Na4Nat5VOE1Int8 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet6, vectorDomainE3Na4Nat5VOE1Int8 );
	
	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];
	
	
	cout<<"cFibSet fibSetV3Dom5rootDom4( 3, NULL, &rootDom4 );"<<endl;
	cFibSet fibSetV3Dom5rootDom4( 3, NULL, &rootDom4 );
	cout<<"fibSetV3Dom5rootDom4.setDomainNr( 5 );"<<endl;
	fibSetV3Dom5rootDom4.setDomainNr( 5 );
	
	cout<<"cVectorFibSet vecFibSetE3V4Dom5( 2, &fibSetV3Dom5rootDom4 );"<<endl;
	cVectorFibSet vecFibSetE3V4Dom5( 2, &fibSetV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	if ( typeFibSet5 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet5. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet5 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibSetE3V4Dom5.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibSetE3V4Dom5.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibSetE3V4Dom5.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vecFibSetE3V4Dom5.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3Dom5rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3Dom5rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3Dom5rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE2Int4Int5 == (*(vecFibSetE3V4Dom5.getDomain())) ){
	
		cout<<"The vectorDomainE2Int4Int5 is the domain for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibSet with a set-element as defining element, wich has a not existig domain number set"<<endl;
	
	cout<<"fibSetV3Dom5rootDom4.setDomainNr( 13 );"<<endl;
	fibSetV3Dom5rootDom4.setDomainNr( 13 );
	
	cout<<"cVectorFibSet vecFibSetE3V4Dom13( 2, &fibSetV3Dom5rootDom4 );"<<endl;
	cVectorFibSet vecFibSetE3V4Dom13( 2, &fibSetV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom13.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom13.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	cout<<"cTypeFibSet typeFibSet13( 13 ); "<<endl;
	cTypeFibSet typeFibSet13( 13 );
	pTypeFibSet = vecFibSetE3V4Dom13.getElementType();
	if ( typeFibSet13 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet13. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet13 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom13.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom13.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibSetE3V4Dom13.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibSetE3V4Dom13.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibSetE3V4Dom13.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vecFibSetE3V4Dom13.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom13.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3Dom5rootDom4 == vecFibSetE3V4Dom13.getDefiningFibElement() ){
	
		cout<<"The fibSetV3Dom13rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3Dom13rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom13.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainOE1Int8 == (*(vecFibSetE3V4Dom13.getDomain())) ){
	
		cout<<"The vectorDomainOE1Int8 is the domain for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibSet with just a set-element as defining element"<<endl;

	cout<<"cVectorFibSet vecFibSet2E4( fibSetV4 );"<<endl;
	cVectorFibSet vecFibSet2E4( fibSetV4 );

	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSet2E4.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSet2E4.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSet2E4.getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSet2E4.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the set-element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSet2E4.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibSet2E4.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibSet2E4.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibSet2E4.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vecFibSet2E4.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSet2E4.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV4 == vecFibSet2E4.getDefiningFibElement() ){
	
		cout<<"The fibSetV4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSet2E4.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the set-element vector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibSet with just a set-element as defining element, wich has domain number set"<<endl;
	
	cout<<"fibSetV3Dom5rootDom4.setDomainNr( 5 );"<<endl;
	fibSetV3Dom5rootDom4.setDomainNr( 5 );

	cout<<"cVectorFibSet vecFibSet2E3V4Dom5( fibSetV3Dom5rootDom4 );"<<endl;
	cVectorFibSet vecFibSet2E3V4Dom5( fibSetV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSet2E3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSet2E3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSet2E3V4Dom5.getElementType();
	if ( typeFibSet5 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet5. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet5 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSet2E3V4Dom5.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the set-element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSet2E3V4Dom5.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibSet2E3V4Dom5.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibSet2E3V4Dom5.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibSet2E3V4Dom5.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vecFibSet2E3V4Dom5.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSet2E3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3Dom5rootDom4 == vecFibSet2E3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3Dom5rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3Dom5rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSet2E3V4Dom5.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE2Int4Int5 == (*(vecFibSet2E3V4Dom5.getDomain())) ){
	
		cout<<"The vectorDomainE2Int4Int5 is the domain for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibSet with yust a set-element as defining element, wich has a not existig domain number set"<<endl;
	
	cout<<"fibSetV3Dom5rootDom4.setDomainNr( 13 );"<<endl;
	fibSetV3Dom5rootDom4.setDomainNr( 13 );

	cout<<"cVectorFibSet vecFibSet2E3V4Dom13( fibSetV3Dom5rootDom4 );"<<endl;
	cVectorFibSet vecFibSet2E3V4Dom13( fibSetV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSet2E3V4Dom13.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSet2E3V4Dom13.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSet2E3V4Dom13.getElementType();
	if ( typeFibSet13 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet13. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet13 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSet2E3V4Dom13.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the set-element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSet2E3V4Dom13.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibSet2E3V4Dom13.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibSet2E3V4Dom13.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibSet2E3V4Dom13.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vecFibSet2E3V4Dom13.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSet2E3V4Dom13.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3Dom5rootDom4 == vecFibSet2E3V4Dom13.getDefiningFibElement() ){
	
		cout<<"The fibSetV3Dom13rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3Dom13rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSet2E3V4Dom13.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainOE1Int8 == (*(vecFibSet2E3V4Dom13.getDomain())) ){
	
		cout<<"The vectorDomainOE1Int8 is the domain for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibSet by copying vecFibSetE3"<<endl;
	
	cout<<"cVectorFibSet vecFibSetE3Copy( vecFibSetE3 );"<<endl;
	cVectorFibSet vecFibSetE3Copy( vecFibSetE3 );

	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3Copy.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3Copy.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3Copy.getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3Copy.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the set-element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3Copy.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibSetE3Copy.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibSetE3Copy.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibSetE3Copy.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<< vecFibSetE3Copy.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3Copy.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSetE3Copy.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibSet by copying vecFibSetE4RD2"<<endl;
	
	cout<<"cVectorFibSet vecFibSetE4RD2Copy( vecFibSetE4RD2 );"<<endl;
	cVectorFibSet vecFibSetE4RD2Copy( vecFibSetE4RD2 );

	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE4RD2Copy.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE4RD2Copy.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE4RD2Copy.getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE4RD2Copy.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the set-element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE4RD2Copy.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibSetE4RD2Copy.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibSetE4RD2Copy.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibSetE4RD2Copy.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<< vecFibSetE4RD2Copy.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE4RD2Copy.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecFibSetE4RD2Copy.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSetE4RD2Copy.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE1Nat1 == (*(vecFibSetE4RD2Copy.getDomain())) ){
	
		cout<<"The vectorDomainE1Nat1 is the domain for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1Nat1 is not the domain for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibSet by copying vecFibSetE4RD2 and givin fibSetV3Dom5rootDom4 as an defining element"<<endl;
	
	cout<<"cVectorFibSet vecFibSetE4RD2Copy2( vecFibSetE4RD2, &fibSetV3Dom5rootDom4 );"<<endl;
	cVectorFibSet vecFibSetE4RD2Copy2( vecFibSetE4RD2, &fibSetV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE4RD2Copy2.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE4RD2Copy2.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE4RD2Copy2.getElementType();
	if ( typeFibSet13 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet13. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet13 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE4RD2Copy2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the set-element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE4RD2Copy2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibSetE4RD2Copy2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibSetE4RD2Copy2.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibSetE4RD2Copy2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<< vecFibSetE4RD2Copy2.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE4RD2Copy2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3Dom5rootDom4 == vecFibSetE4RD2Copy2.getDefiningFibElement() ){
	
		cout<<"The fibSetV3Dom5rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3Dom5rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSetE4RD2Copy2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainOE1Int8 == (*(vecFibSetE4RD2Copy2.getDomain())) ){
	
		cout<<"The vectorDomainOE1Int8 is the domain for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibSet by copying vecFibSetRD3 with changed elements"<<endl;
	
	cout<<"rootDom4.setNumberOfInputVariables( 2 );"<<endl;
	rootDom4.setNumberOfInputVariables( 2 );
	cout<<"cFibVariable * pVariable1 = rootDom4.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootDom4.getInputVariable( 1 );
	cout<<"cFibVariable * pVariable2 = rootDom4.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = rootDom4.getInputVariable( 2 );

	cout<<"vecFibSetE4RD2.setValue( 1, 1 );"<<endl;
	vecFibSetE4RD2.setValue( 1, 1 );
	cout<<"vecFibSetE4RD2.setVariable( 2, pVariable1 );"<<endl;
	vecFibSetE4RD2.setVariable( 2, pVariable1 );
	cout<<"vecFibSetE4RD2.setValue( 3, 2 );"<<endl;
	vecFibSetE4RD2.setValue( 3, 2 );
	cout<<"vecFibSetE4RD2.setVariable( 4, pVariable2 );"<<endl;
	vecFibSetE4RD2.setVariable( 4, pVariable2 );
	
	cout<<"cVectorFibSet vecFibSetE4RD2CopyMod( vecFibSetE4RD2 );"<<endl;
	cVectorFibSet vecFibSetE4RD2CopyMod( vecFibSetE4RD2 );

	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE4RD2CopyMod.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE4RD2CopyMod.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE4RD2CopyMod.getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE4RD2Copy2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the set-element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE4RD2Copy2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
		//check the first vectorelement
	if ( ! vecFibSetE4RD2CopyMod.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSetE4RD2CopyMod.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSetE4RD2CopyMod.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecFibSetE4RD2CopyMod.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSetE4RD2CopyMod.getVariable( 2 ) == pVariable1 ){
	
		cout<<"The 2'th element of the set-element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the secound vectorelement
	if ( ! vecFibSetE4RD2CopyMod.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSetE4RD2CopyMod.getValue( 3 ) == (doubleFib)(2) ){
	
		cout<<"The 3'th element of the "<<
			"set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSetE4RD2CopyMod.getValue( 3 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecFibSetE4RD2CopyMod.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSetE4RD2CopyMod.getVariable( 4 ) == pVariable2 ){
	
		cout<<"The 4'th element of the set-element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the set-element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE4RD2CopyMod.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecFibSetE4RD2CopyMod.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSetE4RD2CopyMod.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE1Nat1 == (*(vecFibSetE4RD2CopyMod.getDomain())) ){
	
		cout<<"The vectorDomainE1Nat1 is the domain for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1Nat1 is not the domain for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"Testing the original vector vecFibSetE4RD2:"<<endl;

	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE4RD2.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE4RD2.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE4RD2.getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE4RD2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the set-element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE4RD2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
		//check the first vectorelement
	if ( ! vecFibSetE4RD2.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSetE4RD2.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSetE4RD2.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecFibSetE4RD2.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSetE4RD2.getVariable( 2 ) == pVariable1 ){
	
		cout<<"The 2'th element of the set-element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the secound vectorelement
	if ( ! vecFibSetE4RD2.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSetE4RD2.getValue( 3 ) == (doubleFib)(2) ){
	
		cout<<"The 3'th element of the "<<
			"set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSetE4RD2.getValue( 3 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecFibSetE4RD2.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSetE4RD2.getVariable( 4 ) == pVariable2 ){
	
		cout<<"The 4'th element of the set-element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the set-element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE4RD2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecFibSetE4RD2.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSetE4RD2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE1Nat1 == (*(vecFibSetE4RD2.getDomain())) ){
	
		cout<<"The vectorDomainE1Nat1 is the domain for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1Nat1 is not the domain for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"Changing vecFibSetE4RD2 should not change the copy:"<<endl;

	cout<<"vecFibSetE4RD2.setVariable( 1, pVariable2 );"<<endl;
	vecFibSetE4RD2.setVariable( 1, pVariable2 );
	cout<<"vecFibSetE4RD2.setValue( 2, 9 );"<<endl;
	vecFibSetE4RD2.setValue( 2, 1 );
	cout<<"vecFibSetE4RD2.setValue( 3, 8 );"<<endl;
	vecFibSetE4RD2.setValue( 3, 2 );

	cout<<endl<<"Testing the copied vector vecFibSetE4RD2CopyMod for changed values:"<<endl;
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE4RD2CopyMod.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE4RD2CopyMod.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE4RD2CopyMod.getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE4RD2Copy2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the set-element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE4RD2Copy2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
		//check the first vectorelement
	if ( ! vecFibSetE4RD2CopyMod.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSetE4RD2CopyMod.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSetE4RD2CopyMod.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecFibSetE4RD2CopyMod.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSetE4RD2CopyMod.getVariable( 2 ) == pVariable1 ){
	
		cout<<"The 2'th element of the set-element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the secound vectorelement
	if ( ! vecFibSetE4RD2CopyMod.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSetE4RD2CopyMod.getValue( 3 ) == (doubleFib)(2) ){
	
		cout<<"The 3'th element of the "<<
			"set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSetE4RD2CopyMod.getValue( 3 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecFibSetE4RD2CopyMod.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSetE4RD2CopyMod.getVariable( 4 ) == pVariable2 ){
	
		cout<<"The 4'th element of the set-element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the set-element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE4RD2CopyMod.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecFibSetE4RD2CopyMod.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSetE4RD2CopyMod.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE1Nat1 == (*(vecFibSetE4RD2CopyMod.getDomain())) ){
	
		cout<<"The vectorDomainE1Nat1 is the domain for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1Nat1 is not the domain for the set-element vector."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the method for the domains of the cVectorFibSet class.
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
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3( 3 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 2 ] = &vectorDomainE3Nat1Nat2Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 2 ] = &vectorDomainE3Nat1Nat2Nat3;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3( vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3( vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3 );
	delete vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ];
	delete vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ];

	cout<<"cTypeFibSet typeFibSet;"<<endl;
	cTypeFibSet typeFibSet;

	cout<<"root.getDomains()->addDomain( typeFibSet, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	root.getDomains()->addDomain( typeFibSet, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );

	
	cout<<"cVectorFibSet vecFibSetRD( 3, &root );"<<endl;
	cVectorFibSet vecFibSetRD( 3, &root );
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetRD.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the set-element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetRD.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the getDomain() methode from cVectorFibSet
	if ( vecFibSetRD.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3.getElementDomain( 3 ) ==
			vecFibSetRD.getDomain() ){
	
		cout<<"The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is the domain for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is not the domain for the set-element vector."<<endl;
		iReturn++;
	}

	/*check the getDomain(i=1..n) method of the set-vektor*/
	//test the getType() method
	cout<<"cDomain * pDomainD3 = vecFibSetRD.getDomain();"<<endl;
	cDomain * pDomainD3 = vecFibSetRD.getDomain();
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

	//check the getStandardDomain() method from cVectorFibSet
	cDomain * pDomainStandard = vecFibSetRD.getStandardDomain();
	cDomain * pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibSet domains with domain numbers"<<endl;
	
	cout<<"cRoot rootDom4;"<<flush<<endl;
	cRoot rootDom4;
	
	cout<<"rootDom4.getDomains()->addDomain( typeFibSet, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );

	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Int2Int3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Int2Int3( 2 );
	cout<<"vecDomainsE2Int2Int3[ 0 ] = new cDomainIntegerBit( 2 );"<<endl;
	vecDomainsE2Int2Int3[ 0 ] = new cDomainIntegerBit( 2 );
	cout<<"vecDomainsE2Int2Int3[ 1 ] = new cDomainIntegerBit( 3 );"<<endl;
	vecDomainsE2Int2Int3[ 1 ] = new cDomainIntegerBit( 3 );
	cout<<"cDomainVector vectorDomainE1Nat1( vecDomainsE2Int2Int3 );"<<endl;
	cDomainVector vectorDomainE2Int2Int3( vecDomainsE2Int2Int3 );
	delete vecDomainsE2Int2Int3[ 0 ];
	delete vecDomainsE2Int2Int3[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 3 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int2Int3;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int2Int3;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibSet typeFibSet4( 4 );"<<endl;
	cTypeFibSet typeFibSet4( 4 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibSet4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );
	
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

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int4Int5;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int4Int5;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibSet typeFibSet5( 5 );"<<endl;
	cTypeFibSet typeFibSet5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibSet5, &vectorDomainE3Na4Nat5VE2NInt4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet5, &vectorDomainE3Na4Nat5VE2NInt4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainOE1Int8;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainOE1Int8;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibSet typeFibSet6( 6 );"<<endl;
	cTypeFibSet typeFibSet6( 6 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibSet6, &vectorDomainE3Na4Nat5VOE1Int8 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet6, &vectorDomainE3Na4Nat5VOE1Int8 );
	
	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];
	
	
	cout<<"cFibSet fibSetV3rootDom4( 3, NULL, &rootDom4 );"<<endl;
	cFibSet fibSetV3rootDom4( 3, NULL, &rootDom4 );
	cout<<"fibSetV3rootDom4.setDomainNr( 0 );"<<endl;
	fibSetV3rootDom4.setDomainNr( 0 );
	
	cout<<"cVectorFibSet vecFibSetE3V4Dom5( 2, &fibSetV3rootDom4 );"<<endl;
	cVectorFibSet vecFibSetE3V4Dom5( 2, &fibSetV3rootDom4 );

	//check the getDomain() methode from cVectorFibSet
	cout<<"cDomain * pDomain = vecFibSetE3V4Dom5.getDomain();"<<endl;
	cDomain * pDomain = vecFibSetE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3.getElementDomain( 3 ) ==
				vecFibSetRD.getDomain() ){
		
			cout<<"The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is not the domain for the set-element vector."<<endl;
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

	//check the getStandardDomain() method from cVectorFibSet
	pDomainStandard = vecFibSetE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	cTypeElement * pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibSet domains with domain numbers, setting domain number 1"<<endl;
	
	cout<<"fibSetV3rootDom4.setDomainNr( 1 );"<<endl;
	fibSetV3rootDom4.setDomainNr( 1 );

	//check the getDomain() methode from cVectorFibSet
	cout<<"pDomain = vecFibSetE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibSetE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3.getElementDomain( 3 ) ==
				vecFibSetRD.getDomain() ){
		
			cout<<"The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is not the domain for the set-element vector."<<endl;
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

	//check the getStandardDomain() method from cVectorFibSet
	pDomainStandard = vecFibSetE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	cTypeFibSet typeFibSet1( 1 );
	if ( typeFibSet1 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet1. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet1 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibSet domains with domain numbers, setting domain number 3"<<endl;
	
	cout<<"fibSetV3rootDom4.setDomainNr( 3 );"<<endl;
	fibSetV3rootDom4.setDomainNr( 3 );

	//check the getDomain() methode from cVectorFibSet
	cout<<"pDomain = vecFibSetE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibSetE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3.getElementDomain( 3 ) ==
				vecFibSetRD.getDomain() ){
		
			cout<<"The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is not the domain for the set-element vector."<<endl;
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

	//check the getStandardDomain() method from cVectorFibSet
	pDomainStandard = vecFibSetE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	cTypeFibSet typeFibSet3( 3 );
	if ( typeFibSet3 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet3. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet3 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibSet domains with domain numbers, setting domain number 4"<<endl;
	
	cout<<"fibSetV3rootDom4.setDomainNr( 4 );"<<endl;
	fibSetV3rootDom4.setDomainNr( 4 );

	//check the getDomain() methode from cVectorFibSet
	cout<<"pDomain = vecFibSetE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibSetE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE2Int2Int3 == *pDomain ){
		
			cout<<"The vectorDomainE2Int2Int3 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE2Int2Int3 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na4Nat5VE2NInt2Int3.getElementDomain( 3 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VE2NInt2Int3[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VE2NInt2Int3[ 3 ] is not the domain for the set-element vector."<<endl;
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

	//check the getStandardDomain() method from cVectorFibSet
	pDomainStandard = vecFibSetE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	if ( typeFibSet4 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet4. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet4 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibSet domains with domain numbers, setting domain number 5"<<endl;
	
	cout<<"fibSetV3rootDom4.setDomainNr( 5 );"<<endl;
	fibSetV3rootDom4.setDomainNr( 5 );

	//check the getDomain() methode from cVectorFibSet
	cout<<"pDomain = vecFibSetE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibSetE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE2Int4Int5 == *pDomain ){
		
			cout<<"The vectorDomainE2Int4Int5 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na4Nat5VE2NInt4Int5.getElementDomain( 3 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VE2NInt4Int5[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VE2NInt4Int5[ 3 ] is not the domain for the set-element vector."<<endl;
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

	//check the getStandardDomain() method from cVectorFibSet
	pDomainStandard = vecFibSetE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	if ( typeFibSet5 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet5. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet5 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibSet domains with domain numbers, setting domain number 6"<<endl;
	
	cout<<"fibSetV3rootDom4.setDomainNr( 6 );"<<endl;
	fibSetV3rootDom4.setDomainNr( 6 );

	//check the getDomain() methode from cVectorFibSet
	cout<<"pDomain = vecFibSetE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibSetE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainOE1Int8 == *pDomain ){
		
			cout<<"The vectorDomainOE1Int8 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na4Nat5VOE1Int8.getElementDomain( 3 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VOE1Int8[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VOE1Int8[ 3 ] is not the domain for the set-element vector."<<endl;
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

	//check the getStandardDomain() method from cVectorFibSet
	pDomainStandard = vecFibSetE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	if ( typeFibSet6 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet6. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet6 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibSet domains with domain numbers, setting domain number 13"<<endl;
	
	cout<<"fibSetV3rootDom4.setDomainNr( 13 );"<<endl;
	fibSetV3rootDom4.setDomainNr( 13 );

	//check the getDomain() methode from cVectorFibSet
	cout<<"pDomain = vecFibSetE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibSetE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainOE1Int8 == *pDomain ){
		
			cout<<"The vectorDomainOE1Int8 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na4Nat5VOE1Int8.getElementDomain( 3 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VOE1Int8[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VOE1Int8[ 3 ] is not the domain for the set-element vector."<<endl;
			iReturn++;
		}

		/*check the getDomain(i=1..n) method of the set-vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVectorOpenEnd" ){
		
			cout<<"The type of pDomain is correctly \"DomainVector\". "<<endl;

			cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
			
			//test the getNumberOfElements() method
			if ( pVectorDomain->getNumberOfElements() == 1 ){
			
				cout<<"The number of elements of pDomain is correctly 1. "<<endl;
				
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

	//check the getStandardDomain() method from cVectorFibSet
	pDomainStandard = vecFibSetE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	cTypeFibSet typeFibSet13( 13 );
	if ( typeFibSet13 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet13. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet13 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	return iReturn;
}




/**
 * This method tests the method for the domains of the cVectorFibSet class.
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
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3( 3 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 2 ] = &vectorDomainE3Nat1Nat2Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 2 ] = &vectorDomainE3Nat1Nat2Nat3;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3( vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3( vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3 );
	delete vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ];
	delete vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ];

	cout<<"cTypeFibSet typeFibSet;"<<endl;
	cTypeFibSet typeFibSet;

	cout<<"root.getValueDomains()->addDomain( typeFibSet, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	root.getValueDomains()->addDomain( typeFibSet, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );

	
	cout<<"cVectorFibSet vecFibSetRD( 3, &root );"<<endl;
	cVectorFibSet vecFibSetRD( 3, &root );
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetRD.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the set-element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetRD.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the getValueDomain() methode from cVectorFibSet
	if ( vecFibSetRD.getValueDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3.getElementDomain( 3 ) ==
			vecFibSetRD.getValueDomain() ){
	
		cout<<"The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is the domain for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is not the domain for the set-element vector."<<endl;
		iReturn++;
	}

	/*check the getValueDomain(i=1..n) method of the set-vektor*/
	//test the getType() method
	cout<<"cDomain * pDomainD3 = vecFibSetRD.getValueDomain();"<<endl;
	cDomain * pDomainD3 = vecFibSetRD.getValueDomain();
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

	//check the getStandardDomain() method from cVectorFibSet
	cDomain * pDomainStandard = vecFibSetRD.getStandardDomain();
	cDomain * pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibSet domains with domain numbers"<<endl;
	
	cout<<"cRoot rootDom4;"<<flush<<endl;
	cRoot rootDom4;
	
	cout<<"rootDom4.getDomains()->addDomain( typeFibSet, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );

	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Int2Int3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Int2Int3( 2 );
	cout<<"vecDomainsE2Int2Int3[ 0 ] = new cDomainIntegerBit( 2 );"<<endl;
	vecDomainsE2Int2Int3[ 0 ] = new cDomainIntegerBit( 2 );
	cout<<"vecDomainsE2Int2Int3[ 1 ] = new cDomainIntegerBit( 3 );"<<endl;
	vecDomainsE2Int2Int3[ 1 ] = new cDomainIntegerBit( 3 );
	cout<<"cDomainVector vectorDomainE1Nat1( vecDomainsE2Int2Int3 );"<<endl;
	cDomainVector vectorDomainE2Int2Int3( vecDomainsE2Int2Int3 );
	delete vecDomainsE2Int2Int3[ 0 ];
	delete vecDomainsE2Int2Int3[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 3 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int2Int3;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int2Int3;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibSet typeFibSet4( 4 );"<<endl;
	cTypeFibSet typeFibSet4( 4 );
	cout<<"rootDom4.getValueDomains()->addDomain( typeFibSet4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );"<<endl;
	rootDom4.getValueDomains()->addDomain( typeFibSet4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );
	
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

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int4Int5;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int4Int5;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibSet typeFibSet5( 5 );"<<endl;
	cTypeFibSet typeFibSet5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibSet5, &vectorDomainE3Na4Nat5VE2NInt4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet5, &vectorDomainE3Na4Nat5VE2NInt4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainOE1Int8;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainOE1Int8;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibSet typeFibSet6( 6 );"<<endl;
	cTypeFibSet typeFibSet6( 6 );
	cout<<"rootDom4.getValueDomains()->addDomain( typeFibSet6, &vectorDomainE3Na4Nat5VOE1Int8 );"<<endl;
	rootDom4.getValueDomains()->addDomain( typeFibSet6, &vectorDomainE3Na4Nat5VOE1Int8 );
	
	//create vector domain with
	cout<<"vector<cDomainSingle*> vecDomainsE1Int6( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int6( 1 );
	cout<<"vecDomainsE1Int6[ 0 ] = new cDomainIntegerBit( 6 );"<<endl;
	vecDomainsE1Int6[ 0 ] = new cDomainIntegerBit( 6 );
	cout<<"cDomainVector vectorDomainE1Int6( vecDomainsE1Int6 );"<<endl;
	cDomainVector vectorDomainE1Int6( vecDomainsE1Int6 );
	delete vecDomainsE1Int6[ 0 ];

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE1Int6;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE1Int6;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VOE1Int6( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VOE1Int6( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"rootDom4.getDomains()->addDomain( typeFibSet6, &vectorDomainE3Na4Nat5VOE1Int6 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet6, &vectorDomainE3Na4Nat5VOE1Int6 );

	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];
	
	
	cout<<"cFibSet fibSetV3rootDom4( 3, NULL, &rootDom4 );"<<endl;
	cFibSet fibSetV3rootDom4( 3, NULL, &rootDom4 );
	cout<<"fibSetV3rootDom4.setDomainNr( 0 );"<<endl;
	fibSetV3rootDom4.setDomainNr( 0 );
	
	cout<<"cVectorFibSet vecFibSetE3V4Dom5( 2, &fibSetV3rootDom4 );"<<endl;
	cVectorFibSet vecFibSetE3V4Dom5( 2, &fibSetV3rootDom4 );

	//check the getValueDomain() methode from cVectorFibSet
	cout<<"cDomain * pDomain = vecFibSetE3V4Dom5.getValueDomain();"<<endl;
	cDomain * pDomain = vecFibSetE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3.getElementDomain( 3 ) ==
				vecFibSetRD.getValueDomain() ){
		
			cout<<"The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is not the domain for the set-element vector."<<endl;
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

	//check the getStandardDomain() method from cVectorFibSet
	pDomainStandard = vecFibSetE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	cTypeElement * pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibSet domains with domain numbers, setting domain number 1"<<endl;
	
	cout<<"fibSetV3rootDom4.setDomainNr( 1 );"<<endl;
	fibSetV3rootDom4.setDomainNr( 1 );

	//check the getValueDomain() methode from cVectorFibSet
	cout<<"pDomain = vecFibSetE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecFibSetE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3.getElementDomain( 3 ) ==
				vecFibSetRD.getValueDomain() ){
		
			cout<<"The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is not the domain for the set-element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the set-vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVector" ){
		
			cout<<"The type of pDomain is correctly \"DomainVector\". "<<endl;

			cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
			
			//test the getNumberOfElements() method
			if ( pVectorDomain->getNumberOfElements() == 3 ){
			
				cout<<"The number of elements of pDomain is correctly 3. "<<endl;

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

	//check the getStandardDomain() method from cVectorFibSet
	pDomainStandard = vecFibSetE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	cTypeFibSet typeFibSet1( 1 );
	if ( typeFibSet1 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet1. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet1 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibSet domains with domain numbers, setting domain number 3"<<endl;
	
	cout<<"fibSetV3rootDom4.setDomainNr( 3 );"<<endl;
	fibSetV3rootDom4.setDomainNr( 3 );

	//check the getValueDomain() methode from cVectorFibSet
	cout<<"pDomain = vecFibSetE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecFibSetE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3.getElementDomain( 3 ) ==
				vecFibSetRD.getValueDomain() ){
		
			cout<<"The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is not the domain for the set-element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the set-vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVector" ){
		
			cout<<"The type of pDomain is correctly \"DomainVector\". "<<endl;

			cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
			
			//test the getNumberOfElements() method
			if ( pVectorDomain->getNumberOfElements() == 3 ){
			
				cout<<"The number of elements of pDomain is correctly 3. "<<endl;
				
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

	//check the getStandardDomain() method from cVectorFibSet
	pDomainStandard = vecFibSetE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	cTypeFibSet typeFibSet3( 3 );
	if ( typeFibSet3 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet3. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet3 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibSet domains with domain numbers, setting domain number 4"<<endl;
	
	cout<<"fibSetV3rootDom4.setDomainNr( 4 );"<<endl;
	fibSetV3rootDom4.setDomainNr( 4 );

	//check the getValueDomain() methode from cVectorFibSet
	cout<<"pDomain = vecFibSetE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecFibSetE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE2Int2Int3 == *pDomain ){
		
			cout<<"The vectorDomainE2Int2Int3 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE2Int2Int3 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na4Nat5VE2NInt2Int3.getElementDomain( 3 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VE2NInt2Int3[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VE2NInt2Int3[ 3 ] is not the domain for the set-element vector."<<endl;
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
	
	//check the getValueDomain() methode from cVectorFibSet
	cout<<"pDomain = vecFibSetE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibSetE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3.getElementDomain( 3 ) ==
				vecFibSetRD.getValueDomain() ){
		
			cout<<"The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] is not the domain for the set-element vector."<<endl;
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

	//check the getStandardDomain() method from cVectorFibSet
	pDomainStandard = vecFibSetE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	if ( typeFibSet4 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet4. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet4 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibSet domains with domain numbers, setting domain number 5"<<endl;
	
	cout<<"fibSetV3rootDom4.setDomainNr( 5 );"<<endl;
	fibSetV3rootDom4.setDomainNr( 5 );

	//check the getValueDomain() methode from cVectorFibSet
	cout<<"pDomain = vecFibSetE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecFibSetE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE2Int4Int5 == *pDomain ){
		
			cout<<"The vectorDomainE2Int4Int5 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na4Nat5VE2NInt4Int5.getElementDomain( 3 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VE2NInt4Int5[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VE2NInt4Int5[ 3 ] is not the domain for the set-element vector."<<endl;
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

	//check the getStandardDomain() method from cVectorFibSet
	pDomainStandard = vecFibSetE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	if ( typeFibSet5 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet5. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet5 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibSet domains with domain numbers, setting domain number 6"<<endl;
	
	cout<<"fibSetV3rootDom4.setDomainNr( 6 );"<<endl;
	fibSetV3rootDom4.setDomainNr( 6 );

	//check the getValueDomain() methode from cVectorFibSet
	cout<<"pDomain = vecFibSetE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecFibSetE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainOE1Int8 == *pDomain ){
		
			cout<<"The vectorDomainOE1Int8 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na4Nat5VOE1Int8.getElementDomain( 3 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VOE1Int8[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VOE1Int8[ 3 ] is not the domain for the set-element vector."<<endl;
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
	//check the getValueDomain() methode from cVectorFibSet
	cout<<"pDomain = vecFibSetE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibSetE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE1Int6 == *pDomain ){
		
			cout<<"The vectorDomainE1Int6 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE1Int6 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na4Nat5VOE1Int6.getElementDomain( 3 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VOE1Int6[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VOE1Int6[ 3 ] is not the domain for the set-element vector."<<endl;
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

	//check the getStandardDomain() method from cVectorFibSet
	pDomainStandard = vecFibSetE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	if ( typeFibSet6 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet6. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet6 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibSet domains with domain numbers, setting domain number 13"<<endl;
	
	cout<<"fibSetV3rootDom4.setDomainNr( 13 );"<<endl;
	fibSetV3rootDom4.setDomainNr( 13 );

	//check the getValueDomain() methode from cVectorFibSet
	cout<<"pDomain = vecFibSetE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecFibSetE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainOE1Int8 == *pDomain ){
		
			cout<<"The vectorDomainOE1Int8 is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the set-element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibSet
		if ( vectorDomainE3Na4Nat5VOE1Int8.getElementDomain( 3 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VOE1Int8[ 3 ] is the domain for the set-element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VOE1Int8[ 3 ] is not the domain for the set-element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the set-vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVectorOpenEnd" ){
		
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

	//check the getStandardDomain() method from cVectorFibSet
	pDomainStandard = vecFibSetE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibSet.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 3 ) ) ){
	
			cout<<"The vecFibSetRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibSetRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vecFibSetE3V4Dom5.getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vecFibSetE3V4Dom5.getElementType();
	cTypeFibSet typeFibSet13( 13 );
	if ( typeFibSet13 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet13. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet13 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vecFibSetE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSetE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetV3rootDom4 == vecFibSetE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibSetV3rootDom4 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetV3rootDom4 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	return iReturn;
}




/**
 * This method tests setDefiningFibElement() and getDefiningFibElement()
 * method of the cVectorFibSet class.
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

	cout<<"cFibSet definingElement1( 1 );"<<endl;
	cFibSet definingElement1( 1 );
	cout<<"cFibSet definingElement2( 2 );"<<endl;
	cFibSet definingElement2( 2 );
	
	cout<<"cVectorFibSet vecFibSet;"<<endl;
	cVectorFibSet vecFibSet;

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSet.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the set-element vector."<<endl;
		iReturn++;
	}
	
	cout<<"vecFibSet.setDefiningFibElement( &definingElement1 );"<<endl;
	vecFibSet.setDefiningFibElement( &definingElement1 );

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSet.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &definingElement1 == vecFibSet.getDefiningFibElement() ){
	
		cout<<"The definingElement1 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The definingElement1 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}

	cout<<"vecFibSet.setDefiningFibElement( &definingElement2 );"<<endl;
	vecFibSet.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSet.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecFibSet.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}

	cout<<"vecFibSet.setDefiningFibElement( NULL );"<<endl;
	vecFibSet.setDefiningFibElement( NULL );

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSet.getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the set-element vector."<<endl;
		iReturn++;
	}

	cout<<"vecFibSet.setDefiningFibElement( &definingElement2 );"<<endl;
	vecFibSet.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vecFibSet.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecFibSet.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the set-element vector."<<endl;
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
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3( 3 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 2 ] = &vectorDomainE3Nat1Nat2Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 2 ] = &vectorDomainE3Nat1Nat2Nat3;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3( vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3( vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3 );
	delete vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ];
	delete vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ];

	cout<<"cTypeFibSet typeFibSet;"<<endl;
	cTypeFibSet typeFibSet;
	
	cout<<"rootDom4.getDomains()->addDomain( typeFibSet, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );

	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Int2Int3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Int2Int3( 2 );
	cout<<"vecDomainsE2Int2Int3[ 0 ] = new cDomainIntegerBit( 2 );"<<endl;
	vecDomainsE2Int2Int3[ 0 ] = new cDomainIntegerBit( 2 );
	cout<<"vecDomainsE2Int2Int3[ 1 ] = new cDomainIntegerBit( 3 );"<<endl;
	vecDomainsE2Int2Int3[ 1 ] = new cDomainIntegerBit( 3 );
	cout<<"cDomainVector vectorDomainE1Nat1( vecDomainsE2Int2Int3 );"<<endl;
	cDomainVector vectorDomainE2Int2Int3( vecDomainsE2Int2Int3 );
	delete vecDomainsE2Int2Int3[ 0 ];
	delete vecDomainsE2Int2Int3[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 3 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int2Int3;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int2Int3;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibSet typeFibSet4( 4 );"<<endl;
	cTypeFibSet typeFibSet4( 4 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibSet4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );
	
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

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int4Int5;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int4Int5;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibSet typeFibSet5( 5 );"<<endl;
	cTypeFibSet typeFibSet5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibSet5, &vectorDomainE3Na4Nat5VE2NInt4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet5, &vectorDomainE3Na4Nat5VE2NInt4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainOE1Int8;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainOE1Int8;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibSet typeFibSet6( 6 );"<<endl;
	cTypeFibSet typeFibSet6( 6 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibSet6, &vectorDomainE3Na4Nat5VOE1Int8 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibSet6, &vectorDomainE3Na4Nat5VOE1Int8 );
	
	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];
	
	
	cout<<"cFibSet fibSetDom0( 3, NULL, &rootDom4 );"<<endl;
	cFibSet fibSetDom0( 3, NULL, &rootDom4 );
	cout<<"fibSetDom0.setDomainNr( 0 );"<<endl;
	fibSetDom0.setDomainNr( 0 );
	
	cout<<"cFibSet fibSetDom4( 4, NULL, &fibSetDom0 );"<<endl;
	cFibSet fibSetDom4( 4, NULL, &fibSetDom0 );
	cout<<"fibSetDom4.setDomainNr( 4 );"<<endl;
	fibSetDom4.setDomainNr( 4 );

	cout<<"cFibSet fibSetDom5( 5, NULL, &fibSetDom4 );"<<endl;
	cFibSet fibSetDom5( 5, NULL, &fibSetDom4 );
	cout<<"fibSetDom5.setDomainNr( 5 );"<<endl;
	fibSetDom5.setDomainNr( 5 );

	cout<<"cFibSet fibSetDom6( 6, NULL, &fibSetDom5 );"<<endl;
	cFibSet fibSetDom6( 6, NULL, &fibSetDom5 );
	cout<<"fibSetDom6.setDomainNr( 6 );"<<endl;
	fibSetDom6.setDomainNr( 6 );
	
	cout<<"cFibSet fibSetDom11( 11, NULL, &fibSetDom6 );"<<endl;
	cFibSet fibSetDom11( 11, NULL, &fibSetDom6 );
	cout<<"fibSetDom11.setDomainNr( 11 );"<<endl;
	fibSetDom11.setDomainNr( 11 );


	cout<<"cVectorFibSet vecFibSetE0( 0 );"<<endl;
	cVectorFibSet vecFibSetE0( 0 );
	
	cout<<"vecFibSetE0.setDefiningFibElement( &rootDom4 );"<<endl;
	vecFibSetE0.setDefiningFibElement( &rootDom4 );

	cout<<"cVectorFibSet vecFibSet2E3V0( 3 );"<<endl;
	cVectorFibSet vecFibSet2E3V0( 3 );

	if ( vecFibSetE0 == vecFibSet2E3V0 ){
	
		cout<<"The set-element vector vecFibSetE0 is equal to vecFibSet2E3V0. "<<endl;
	}else{
		cerr<<"Error: The set-element vector vecFibSetE0 is not equal to vecFibSet2E3V0."<<endl;
		iReturn++;
	}
	

	cout<<"cVectorFibSet vecFibSet1E3( 3 );"<<endl;
	cVectorFibSet vecFibSet1E3( 3 );
	cout<<"vecFibSet1E3.setValue( 1, 1);"<<endl;
	vecFibSet1E3.setValue( 1, 1);
	cout<<"vecFibSet1E3.setValue( 2, 2);"<<endl;
	vecFibSet1E3.setValue( 2, 2);

	cout<<"cVectorFibSet vecFibSet1E2( 2 );"<<endl;
	cVectorFibSet vecFibSet1E2( 2 );
	cout<<"vecFibSet1E2.setValue( 1, 3);"<<endl;
	vecFibSet1E2.setValue( 1, 3);
	cout<<"vecFibSet1E2.setValue( 2, 2);"<<endl;
	vecFibSet1E2.setValue( 2, 2);

	cout<<"vecFibSet1E2.setDefiningFibElement( &rootDom4 );"<<endl;
	vecFibSet1E2.setDefiningFibElement( &rootDom4 );

	if ( vecFibSet1E2 == vecFibSet1E3 ){
	
		cout<<"The set-element vector vecFibSet1E2 is equal to vecFibSet1E3. "<<endl;
	}else{
		cerr<<"Error: The set-element vector vecFibSet1E2 is not equal to vecFibSet1E3."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibSet1E2.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecFibSet1E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibSet1E2.getValue( uiActualElement ) ==
					vecFibSet1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly "<< 
					vecFibSet1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is "<<vecFibSet1E2.getValue( uiActualElement )<<
					" and not "<< vecFibSet1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}


	cout<<"vecFibSet1E3.setValue( 1, 0);"<<endl;
	vecFibSet1E3.setValue( 1, 0);
	cout<<"vecFibSet1E3.setValue( 2, 1);"<<endl;
	vecFibSet1E3.setValue( 2, 1);

	cout<<"cVectorFibSet vecFibSet2E3( vecFibSet1E3 );"<<endl;
	cVectorFibSet vecFibSet2E3( vecFibSet1E3 );

	cout<<"vecFibSet2E3.setDefiningFibElement( &rootDom4 );"<<endl;
	vecFibSet2E3.setDefiningFibElement( &rootDom4 );


	if ( vecFibSet2E3 == vecFibSet1E3 ){
	
		cout<<"The set-element vector vecFibSet2E3 is equal to vecFibSet1E3. "<<endl;
	}else{
		cerr<<"Error: The set-element vector vecFibSet2E3 is not equal to vecFibSet1E3."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibSet2E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecFibSet2E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibSet2E3.getValue( uiActualElement ) ==
					vecFibSet1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly "<< 
					vecFibSet1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is "<<vecFibSet2E3.getValue( uiActualElement )<<
					" and not "<< vecFibSet1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	cout<<"vecFibSet1E3.setValue( 1, 0);"<<endl;
	vecFibSet1E3.setValue( 1, 0);
	cout<<"vecFibSet1E3.setValue( 2, 3);"<<endl;
	vecFibSet1E3.setValue( 2, 3);
	cout<<"vecFibSet1E3.setValue( 3, 7);"<<endl;
	vecFibSet1E3.setValue( 3, 7);

	cout<<"cVectorFibSet vecFibSet3E3( 3 );"<<endl;
	cVectorFibSet vecFibSet3E3( 3 );
	cout<<"vecFibSet3E3.setValue( 1, -7 );"<<endl;
	vecFibSet3E3.setValue( 1, -7 );
	cout<<"vecFibSet3E3.setValue( 2, 4 );"<<endl;
	vecFibSet3E3.setValue( 2, 4 );
	cout<<"vecFibSet3E3.setValue( 3, 8 );"<<endl;
	vecFibSet3E3.setValue( 3, 8 );

	cout<<"vecFibSet3E3.setDefiningFibElement( &fibSetDom0 );"<<endl;
	vecFibSet3E3.setDefiningFibElement( &fibSetDom0 );

	if ( vecFibSet3E3 == vecFibSet1E3 ){
	
		cout<<"The set-element vector vecFibSet3E3 is equal to vecFibSet1E3. "<<endl;
	}else{
		cerr<<"Error: The set-element vector vecFibSet3E3 is not equal to vecFibSet1E3."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibSet3E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecFibSet3E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibSet3E3.getValue( uiActualElement ) ==
					vecFibSet1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly "<< 
					vecFibSet1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is "<<vecFibSet3E3.getValue( uiActualElement )<<
					" and not "<< vecFibSet1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	
	cout<<"cVectorFibSet vecFibSet2E4( 4 );"<<endl;
	cVectorFibSet vecFibSet2E4( 4 );
	cout<<"vecFibSet2E4.setValue( 1, -2 );"<<endl;
	vecFibSet2E4.setValue( 1, -2 );
	cout<<"vecFibSet2E4.setValue( 2, 3 );"<<endl;
	vecFibSet2E4.setValue( 2, 3 );

	cout<<"cVectorFibSet vecFibSet3E3( 3 );"<<endl;
	cVectorFibSet vecFibSet4E3( 3 );
	cout<<"vecFibSet4E3.setValue( 1, -7 );"<<endl;
	vecFibSet4E3.setValue( 1, -7 );
	cout<<"vecFibSet4E3.setValue( 2, 4 );"<<endl;
	vecFibSet4E3.setValue( 2, 4 );
	cout<<"vecFibSet4E3.setValue( 3, 8 );"<<endl;
	vecFibSet4E3.setValue( 3, 8 );

	cout<<"vecFibSet4E3.setDefiningFibElement( &fibSetDom4 );"<<endl;
	vecFibSet4E3.setDefiningFibElement( &fibSetDom4 );

	if ( vecFibSet4E3 == vecFibSet2E4 ){
	
		cout<<"The set-element vector vecFibSet4E3 is equal to vecFibSet2E4. "<<endl;
	}else{
		cerr<<"Error: The set-element vector vecFibSet4E3 is not equal to vecFibSet2E4."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibSet4E3.getNumberOfElements();
				uiActualElement++ ){
			
			if ( ! vecFibSet4E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibSet4E3.getValue( uiActualElement ) ==
					vecFibSet2E4.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly "<< 
					vecFibSet2E4.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is "<<vecFibSet4E3.getValue( uiActualElement )<<
					" and not "<< vecFibSet2E4.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	
	cout<<"cVectorFibSet vecFibSet1E5( 5 );"<<endl;
	cVectorFibSet vecFibSet1E5( 5 );
	cout<<"vecFibSet1E5.setValue( 1, -7 );"<<endl;
	vecFibSet1E5.setValue( 1, -7 );
	cout<<"vecFibSet1E5.setValue( 2, 4 );"<<endl;
	vecFibSet1E5.setValue( 2, 4 );

	cout<<"cVectorFibSet vecFibSet5E3( 3 );"<<endl;
	cVectorFibSet vecFibSet5E3( 3 );
	cout<<"vecFibSet5E3.setValue( 1, -7 );"<<endl;
	vecFibSet5E3.setValue( 1, -7 );
	cout<<"vecFibSet5E3.setValue( 2, 4 );"<<endl;
	vecFibSet5E3.setValue( 2, 4 );
	cout<<"vecFibSet5E3.setValue( 3, 8 );"<<endl;
	vecFibSet5E3.setValue( 3, 8 );

	cout<<"vecFibSet5E3.setDefiningFibElement( &fibSetDom5 );"<<endl;
	vecFibSet5E3.setDefiningFibElement( &fibSetDom5 );

	if ( vecFibSet5E3 == vecFibSet1E5 ){
	
		cout<<"The set-element vector vecFibSet5E3 is equal to vecFibSet1E5. "<<endl;
	}else{
		cerr<<"Error: The set-element vector vecFibSet5E3 is not equal to vecFibSet1E5."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibSet5E3.getNumberOfElements();
				uiActualElement++ ){
			
			if ( ! vecFibSet5E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibSet5E3.getValue( uiActualElement ) ==
					vecFibSet1E5.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly "<< 
					vecFibSet1E5.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is "<<vecFibSet5E3.getValue( uiActualElement )<<
					" and not "<< vecFibSet1E5.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	
	
	cout<<"cVectorFibSet vecFibSet1E6( 6 );"<<endl;
	cVectorFibSet vecFibSet1E6( 6 );
	cout<<"vecFibSet1E6.setValue( 1, -7 );"<<endl;
	vecFibSet1E6.setValue( 1, -7 );
	cout<<"vecFibSet1E6.setValue( 2, 127 );"<<endl;
	vecFibSet1E6.setValue( 2, 127 );
	cout<<"vecFibSet1E6.setValue( 3, -128 );"<<endl;
	vecFibSet1E6.setValue( 3, -128 );

	cout<<"cVectorFibSet vecFibSet6E3( 3 );"<<endl;
	cVectorFibSet vecFibSet6E3( 3 );
	cout<<"vecFibSet6E3.setValue( 1, -7 );"<<endl;
	vecFibSet6E3.setValue( 1, -7 );
	cout<<"vecFibSet6E3.setValue( 2, 128 );"<<endl;
	vecFibSet6E3.setValue( 2, 128 );
	cout<<"vecFibSet6E3.setValue( 3, -129 );"<<endl;
	vecFibSet6E3.setValue( 3, -129 );

	cout<<"vecFibSet6E3.setDefiningFibElement( &fibSetDom6 );"<<endl;
	vecFibSet6E3.setDefiningFibElement( &fibSetDom6 );

	if ( vecFibSet6E3 == vecFibSet1E6 ){
	
		cout<<"The set-element vector vecFibSet6E3 is equal to vecFibSet1E6. "<<endl;
	}else{
		cerr<<"Error: The set-element vector vecFibSet6E3 is not equal to vecFibSet1E6."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibSet6E3.getNumberOfElements();
				uiActualElement++ ){
			
			if ( ! vecFibSet6E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibSet6E3.getValue( uiActualElement ) ==
					vecFibSet1E6.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly "<< 
					vecFibSet1E6.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is "<<vecFibSet6E3.getValue( uiActualElement )<<
					" and not "<< vecFibSet1E6.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	
	
	cout<<"cVectorFibSet vecFibSet1E11( 11 );"<<endl;
	cVectorFibSet vecFibSet1E11( 11 );
	cout<<"vecFibSet1E11.setValue( 1, -7 );"<<endl;
	vecFibSet1E11.setValue( 1, -7 );
	cout<<"vecFibSet1E11.setValue( 2, 127 );"<<endl;
	vecFibSet1E11.setValue( 2, 127 );
	cout<<"vecFibSet1E11.setValue( 3, -128 );"<<endl;
	vecFibSet1E11.setValue( 3, -128 );

	cout<<"cVectorFibSet vecFibSet7E3( 3 );"<<endl;
	cVectorFibSet vecFibSet7E3( 3 );
	cout<<"vecFibSet7E3.setValue( 1, -7 );"<<endl;
	vecFibSet7E3.setValue( 1, -7 );
	cout<<"vecFibSet7E3.setValue( 2, 128 );"<<endl;
	vecFibSet7E3.setValue( 2, 128 );
	cout<<"vecFibSet7E3.setValue( 3, -129 );"<<endl;
	vecFibSet7E3.setValue( 3, -129 );

	cout<<"vecFibSet7E3.setDefiningFibElement( &fibSetDom11 );"<<endl;
	vecFibSet7E3.setDefiningFibElement( &fibSetDom11 );

	if ( vecFibSet7E3 == vecFibSet1E11 ){
	
		cout<<"The set-element vector vecFibSet7E3 is equal to vecFibSet1E11. "<<endl;
	}else{
		cerr<<"Error: The set-element vector vecFibSet7E3 is not equal to vecFibSet1E11."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibSet7E3.getNumberOfElements();
				uiActualElement++ ){
			
			if ( ! vecFibSet7E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibSet7E3.getValue( uiActualElement ) ==
					vecFibSet1E11.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly "<< 
					vecFibSet1E11.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is "<<vecFibSet7E3.getValue( uiActualElement )<<
					" and not "<< vecFibSet1E11.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods when a domain is given, but shouldn't be checked"<<endl;
	
	cout<<"cVectorFibSet vecFibSet2E2( 2 );"<<endl;
	cVectorFibSet vecFibSet2E2( 2 );
	cout<<"vecFibSet2E2.setValue( 1, -58 );"<<endl;
	vecFibSet2E2.setValue( 1, -58 );
	cout<<"vecFibSet2E2.setValue( 2, 1234 );"<<endl;
	vecFibSet2E2.setValue( 2, 1234 );
	
	cVectorFibSet vecFibSet3E2( vecFibSet2E2 );

	cout<<"vecFibSet3E2.setDefiningFibElement( &fibSetDom5, false );"<<endl;
	vecFibSet3E2.setDefiningFibElement( &fibSetDom5, false );

	if ( vecFibSet3E2 == vecFibSet2E2 ){
	
		cout<<"The set-element vector vecFibSet3E2 is equal to vecFibSet2E2. "<<endl;
	}else{
		cerr<<"Error: The set-element vector vecFibSet3E2 is not equal to vecFibSet2E2."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibSet3E2.getNumberOfElements() &&
				uiActualElement <= 2;
				uiActualElement++ ){
			
			if ( ! vecFibSet3E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibSet3E2.getValue( uiActualElement ) ==
					vecFibSet2E2.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly "<< 
					vecFibSet3E2.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is "<<vecFibSet3E2.getValue( uiActualElement )<<
					" and not "<< vecFibSet2E2.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	cout<<"cVectorFibSet vecFibSet8E3( 3 );"<<endl;
	cVectorFibSet vecFibSet8E3( 3 );
	cout<<"vecFibSet8E3.setValue( 1, -200 );"<<endl;
	vecFibSet8E3.setValue( 1, -200 );
	cout<<"vecFibSet8E3.setValue( 2, 4 );"<<endl;
	vecFibSet8E3.setValue( 2, 4 );
	cout<<"vecFibSet8E3.setValue( 3, 500 );"<<endl;
	vecFibSet8E3.setValue( 3, 500 );
	
	cVectorFibSet vecFibSet9E3( vecFibSet8E3 );

	cout<<"vecFibSet9E3.setDefiningFibElement( &fibSetDom5, false );"<<endl;
	vecFibSet9E3.setDefiningFibElement( &fibSetDom5, false );

	if ( vecFibSet9E3 == vecFibSet8E3 ){
	
		cout<<"The set-element vector vecFibSet9E3 is equal to vecFibSet8E3. "<<endl;
	}else{
		cerr<<"Error: The set-element vector vecFibSet9E3 is not equal to vecFibSet8E3."<<endl;
		/*check the elements of the set-vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibSet9E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecFibSet9E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibSet9E3.getValue( uiActualElement ) ==
					vecFibSet8E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is correctly "<< 
					vecFibSet8E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"set-element vector is "<<vecFibSet9E3.getValue( uiActualElement )<<
					" and not "<< vecFibSet8E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests cVectorFibSet methods for manipulating the
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

	int iReturn=0;//return value of the test; the number of occured errors

//TODO test if yust values of the domain can be set

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing methods for getting the vectorelementdata"<<endl;
	
	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;
	
	cout<<"cVectorFibSet vecFibSet( 3, &emptyRoot );"<<endl;
	cVectorFibSet vecFibSet( 3, &emptyRoot );

	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibSet.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibSet.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibSet.getValue( uiActualElement ) == (doubleFib)(0.0) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vecFibSet.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
		if ( vecFibSet.getVariable( uiActualElement ) == NULL ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly no variable . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable . "<<endl;
			iReturn++;
		}
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setValue() method"<<endl;

	cout<<"vecFibSet.setValue( 2, 2.2 )"<<endl;
	if ( vecFibSet.setValue( 2, 2.2 ) ){
	
		cout<<"The 2'th element of the set-element vector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecFibSet.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSet.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the set-element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is a variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecFibSet.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 2 ) == (doubleFib)(2.2) ){
	
		cout<<"The 2'th element of the "<<
			"set-element vector is correctly 2.2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSet.getValue( 2 )<<" and not 2.2 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the set-element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is a variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFibSet.setValue( 2, 0.7 )"<<endl;
	if ( vecFibSet.setValue( 2, 0.7 ) ){
	
		cout<<"The 2'th element of the set-element vector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecFibSet.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSet.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the set-element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is a variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecFibSet.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"set-element vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSet.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the set-element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is a variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFibSet.setValue( 1, 11 )"<<endl;
	if ( vecFibSet.setValue( 1, 11 ) ){
	
		cout<<"The 1'th element of the set-element vector is set. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecFibSet.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 1 ) == (doubleFib)(11) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSet.getValue( 1 )<<" and not 11 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the set-element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is a variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecFibSet.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"set-element vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSet.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the set-element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is a variable . "<<endl;
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
	cout<<endl<<"vecFibSet.setVariable( 1, pVariable1 )"<<endl;
	if ( vecFibSet.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the set-element vector is set to the variable 1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not set to the variable 1. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecFibSet.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 1 ) == (doubleFib)(0) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSet.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the set-element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecFibSet.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"set-element vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSet.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the set-element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is a variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable1->setValue( 0.11 );"<<endl;
	pVariable1->setValue( 0.11 );
	
	if ( vecFibSet.getValue( 1 ) == (doubleFib)(0.11) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 0.11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSet.getValue( 1 )<<" and not 0.11 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable1->setValue( 111 );"<<endl;
	pVariable1->setValue( 111 );
	
	if ( vecFibSet.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSet.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4 = emptyRoot.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable4 = emptyRoot.getInputVariable( 4 );
	cout<<endl<<"vecFibSet.setVariable( 2, pVariable4 )"<<endl;
	if ( vecFibSet.setVariable( 2, pVariable4 ) ){
	
		cout<<"The 2'th element of the set-element vector is set to the variable 4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not set to the variable 4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecFibSet.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSet.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the set-element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecFibSet.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 2 ) == (doubleFib)(0.0) ){
	
		cout<<"The 2'th element of the "<<
			"set-element vector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSet.getValue( 2 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the set-element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 123 );"<<endl;
	pVariable4->setValue( 123 );
	
	if ( vecFibSet.getValue( 2 ) == (doubleFib)(123) ){
	
		cout<<"The 2'th element of the "<<
			"set-element vector is correctly 123 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSet.getValue( 2 )<<" and not 123 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 0.321 );"<<endl;
	pVariable4->setValue( 0.321  );
	
	if ( vecFibSet.getValue( 2 ) == (doubleFib)(0.321 ) ){
	
		cout<<"The 2'th element of the "<<
			"set-element vector is correctly 0.321  . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSet.getValue( 2 )<<" and not 0.321  . "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecFibSet.setVariable( 1, pVariable4 )"<<endl;
	if ( vecFibSet.setVariable( 1, pVariable4 ) ){
	
		cout<<"The 1'th element of the set-element vector is set to the variable 4. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not set to the variable 4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecFibSet.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 1 ) == (doubleFib)(0.321) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 0.321 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSet.getValue( 1 )<<" and not 0.321 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 1 ) == pVariable4 ){
	
		cout<<"The 1'th element of the set-element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecFibSet.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 2 ) == (doubleFib)(0.321) ){
	
		cout<<"The 2'th element of the "<<
			"set-element vector is correctly 0.321 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSet.getValue( 2 )<<" and not 0.321 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the set-element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 654.123 );"<<endl;
	pVariable4->setValue( 654.123 );
	
	if ( vecFibSet.getValue( 1 ) == (doubleFib)(654.123) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 654.123 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSet.getValue( 1 )<<" and not 654.123 . "<<endl;
		iReturn++;
	}
	
	if ( vecFibSet.getValue( 2 ) == (doubleFib)(654.123) ){
	
		cout<<"The 2'th element of the "<<
			"set-element vector is correctly 654.123 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSet.getValue( 2 )<<" and not 654.123 . "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setValue() and setVariable() after each other method"<<endl;
	
	cout<<endl<<"vecFibSet.setValue( 1, 17 )"<<endl;
	if ( vecFibSet.setValue( 1, 17 ) ){
	
		cout<<"The 1'th element of the set-element vector is set to the value 17"<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not set to the value 17. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecFibSet.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 1 ) == (doubleFib)(17) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 17 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSet.getValue( 1 )<<" and not 17 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the set-element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is a variable. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecFibSet.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 2 ) == (doubleFib)(654.123 ) ){
	
		cout<<"The 2'th element of the "<<
			"set-element vector is correctly 654.123  . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSet.getValue( 2 )<<" and not 654.123  . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the set-element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 65 );"<<endl;
	pVariable4->setValue( 65 );
	
	if ( vecFibSet.getValue( 2 ) == (doubleFib)(65) ){
	
		cout<<"The 2'th element of the "<<
			"set-element vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSet.getValue( 2 )<<" and not 65 . "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecFibSet.setVariable( 1, pVariable1 )"<<endl;
	if ( vecFibSet.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the set-element vector is set to the varaiable 1"<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not set to the variable 1. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecFibSet.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSet.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the set-element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecFibSet.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 2 ) == (doubleFib)(65 ) ){
	
		cout<<"The 2'th element of the "<<
			"set-element vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSet.getValue( 2 )<<" and not 65  . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the set-element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setVariable() methods with trying to set NULL"<<endl;
	
	cout<<endl<<"vecFibSet.setVariable( 1, NULL )"<<endl;
	if ( ! vecFibSet.setVariable( 1, NULL ) ){
	
		cout<<"The 1'th element of the set-element vector couldn't be set to NULL."<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector could be set to NULL. "<<endl;
		iReturn++;
	}
	cout<<endl<<"vecFibSet.setVariable( 2, NULL )"<<endl;
	if ( ! vecFibSet.setVariable( 2, NULL ) ){
	
		cout<<"The 2'th element of the set-element vector couldn't be set to NULL."<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector could be set to NULL. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecFibSet.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"set-element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is "<<
			vecFibSet.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the set-element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the set-element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecFibSet.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the set-element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getValue( 2 ) == (doubleFib)(65 ) ){
	
		cout<<"The 2'th element of the "<<
			"set-element vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is "<<
			vecFibSet.getValue( 2 )<<" and not 65  . "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the set-element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the set-element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing replaceVariable(), isUsedVariable() and set<cFibVariable*> getUsedVariables() methods"<<endl;
	
	cout<<endl<<"pVariable2 = emptyRoot.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = emptyRoot.getInputVariable( 2 );
	cout<<endl<<"pVariable3 = emptyRoot.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = emptyRoot.getInputVariable( 3 );
	
	//check vecFibSet.isUsedVariable()
	if ( vecFibSet.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecFibSet.isUsedVariable()
	if ( ! vecFibSet.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check isUsedVariable()
	if ( vecFibSet.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	
	set<cFibVariable*> setCorrectUsedVariables;
	setCorrectUsedVariables.insert( pVariable1 );
	setCorrectUsedVariables.insert( pVariable4 );
	//check getUsedVariables()
	cout<<"setUsedVariables = vecFibSet.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = vecFibSet.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	
	cout<<endl<<"vecFibSet.replaceVariable( pVariable1, pVariable4 )"<<endl;
	setCorrectUsedVariables.erase( pVariable1 );
	if ( vecFibSet.replaceVariable( pVariable1, pVariable4 ) ){
	
		cout<<"The pVariable1 of the propertyvector was replaced with pVariable4. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 of the propertyvector was not replaced with pVariable4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecFibSet.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 1 ) == pVariable4 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecFibSet.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check vecFibSet.isUsedVariable()
	if ( ! vecFibSet.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecFibSet.isUsedVariable()
	if ( ! vecFibSet.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecFibSet.isUsedVariable()
	if ( vecFibSet.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecFibSet.getUsedVariables(); "<<endl;
	setUsedVariables = vecFibSet.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFibSet.replaceVariable( pVariable1, pVariable3 )"<<endl;
	if ( vecFibSet.replaceVariable( pVariable1, pVariable3 ) ){
	
		cout<<"The pVariable1 of the propertyvector was replaced with pVariable3. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 of the propertyvector was not replaced with pVariable3. "<<endl;
		iReturn++;
	}
	//check vecFibSet.isUsedVariable()
	if ( ! vecFibSet.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecFibSet.isUsedVariable()
	if ( vecFibSet.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecFibSet.getUsedVariables(); "<<endl;
	setUsedVariables = vecFibSet.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	cout<<endl<<"vecFibSet.replaceVariable( pVariable4, pVariable2 )"<<endl;
	setCorrectUsedVariables.erase( pVariable4 );
	setCorrectUsedVariables.insert( pVariable2 );
	if ( vecFibSet.replaceVariable( pVariable4, pVariable2 ) ){
	
		cout<<"The pVariable4 of the propertyvector was replaced with pVariable2. "<<endl;
	}else{
		cerr<<"Error: The pVariable4 of the propertyvector was not replaced with pVariable2. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecFibSet.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 1 ) == pVariable2 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecFibSet.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibSet.getVariable( 2 ) == pVariable2 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check vecFibSet.isUsedVariable()
	if ( ! vecFibSet.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecFibSet.isUsedVariable()
	if ( vecFibSet.isUsedVariable( pVariable2 ) ){
	
		cout<<"The pVariable2 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable2 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecFibSet.isUsedVariable()
	if ( ! vecFibSet.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecFibSet.isUsedVariable()
	if ( ! vecFibSet.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable4 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecFibSet.getUsedVariables(); "<<endl;
	setUsedVariables = vecFibSet.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	//check vecFibSet.isUsedVariable()
	if ( ! vecFibSet.isUsedVariable( NULL ) ){
	
		cout<<"The NULL is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The NULL is a used varible in the vector.  "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFibSet.replaceVariable( NULL, pVariable2 )"<<endl;
	if ( ! vecFibSet.replaceVariable( NULL, pVariable2 ) ){
	
		cout<<"Can't correctly replace NULL of the propertyvector with pVariable2. "<<endl;
	}else{
		cerr<<"Error: Can replace NULL of the propertyvector with pVariable2. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFibSet.replaceVariable( pVariable2, NULL )"<<endl;
	if ( ! vecFibSet.replaceVariable( pVariable2, NULL ) ){
	
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

	cout<<"cFibSet fibSetEmptyRoot( 2, NULL, &emptyRoot );"<<endl;
	cFibSet fibSetEmptyRoot( 2, NULL, &emptyRoot );

	//create vector domain with two elements
	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Nat1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Nat1( 1 );
	cout<<"vecDomainsE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomainE1Nat1( vecDomainsE1Nat1 );"<<endl;
	cDomainVector vectorDomainE1Nat1( vecDomainsE1Nat1 );
	delete vecDomainsE1Nat1[ 0 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 3 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE1Nat1;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE1Nat1;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE3Na2Nat3VE1Nat1 );
	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];

	cout<<"cTypeFibSet typeFibSet;"<<endl;
	cTypeFibSet typeFibSet;

	cout<<"rootD2.getDomains()->addDomain( typeFibSet, vectorDomainE3Na2Nat3VE1Nat1 );"<<endl;
	rootD2.getDomains()->addDomain( typeFibSet, vectorDomainE3Na2Nat3VE1Nat1 );

	//creat defined variables to set them later in the vector
	cout<<"rootD2.setNumberOfInputVariables( 4 )"<<endl;
	rootD2.setNumberOfInputVariables( 4 );

	cout<<"cFibSet fibSetRootD2( 2, NULL, &rootD2 );"<<endl;
	cFibSet fibSetRootD2( 2, NULL, &rootD2 );

	//create cVectorFibSets to compare
	cout<<"cVectorFibSet vectorFibSetE3( 3 );"<<endl;
	cVectorFibSet vectorFibSetE3( 3 );
	cout<<"cVectorFibSet vectorFibSetE3RD2( 3, &rootD2 );"<<endl;
	cVectorFibSet vectorFibSetE3RD2( 3, &rootD2 );
	cout<<"cVectorFibSet vectorFibSetE2Re( fibSetEmptyRoot );"<<endl;
	cVectorFibSet vectorFibSetE2Re( fibSetEmptyRoot );
	cout<<"cVectorFibSet vectorFibSetE2RD2( 2, &rootD2 );"<<endl;
	cVectorFibSet vectorFibSetE2RD2( 2, &rootD2 );
	cout<<"cVectorFibSet vectorFibSetRD2( fibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetRD2( fibSetRootD2 );
	
	//vectors with changed values
	cout<<"cVectorFibSet vectorFibSetRD2V2g17p2( fibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetRD2V2g17p2( fibSetRootD2 );
	vectorFibSetRD2V2g17p2.setValue( 2, 17.2 );
	
	cout<<"cVectorFibSet vectorFibSetE2RD2V2g17p2( 2, &rootD2 );"<<endl;
	cVectorFibSet vectorFibSetE2RD2V2g17p2( 2, &rootD2 );
	vectorFibSetE2RD2V2g17p2.setValue( 2, 17.2 );

	cout<<"cVectorFibSet vectorFibSetE2RD2V2g17p2001( 2, &rootD2 );"<<endl;
	cVectorFibSet vectorFibSetE2RD2V2g17p2001( 2, &rootD2 );
	vectorFibSetE2RD2V2g17p2001.setValue( 2, 17.2001 );

	cout<<"cVectorFibSet vectorFibSetRD2V1g17p2( fibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetRD2V1g17p2( fibSetRootD2 );
	vectorFibSetRD2V1g17p2.setValue( 1, 17.2 );

	cout<<"cVectorFibSet vectorFibSetRD2V1g1p1V2gm2p2( fibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetRD2V1g1p1V2gm2p2( fibSetRootD2 );
	vectorFibSetRD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorFibSetRD2V1g1p1V2gm2p2.setValue( 2, -2.2 );

	cout<<"cVectorFibSet vectorFibSetE2RD2V1g1p1V2gm2p2( 2, &rootD2 );"<<endl;
	cVectorFibSet vectorFibSetE2RD2V1g1p1V2gm2p2( 2, &rootD2 );
	vectorFibSetE2RD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorFibSetE2RD2V1g1p1V2gm2p2.setValue( 2, -2.2 );
	
	cout<<"cVectorFibSet vectorFibSetRD2V1g1p1V2g2p2( fibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetRD2V1g1p1V2g2p2( fibSetRootD2 );
	vectorFibSetRD2V1g1p1V2g2p2.setValue( 1, 1.1 );
	vectorFibSetRD2V1g1p1V2g2p2.setValue( 2, 2.2 );

	//vectors with variables
	cFibVariable * pVariable1 = rootD2.getInputVariable( 1 );
	cFibVariable * pVariable2 = rootD2.getInputVariable( 2 );
	cFibVariable * pVariable1Re = emptyRoot.getInputVariable( 1 );

	cout<<"cVectorFibSet vectorFibSetRD2V1gV1( fibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetRD2V1gV1( fibSetRootD2 );
	vectorFibSetRD2V1gV1.setVariable( 1, pVariable1 );

	cout<<"cVectorFibSet vectorFibSetE2RD2V1gV1( 2, &rootD2 );"<<endl;
	cVectorFibSet vectorFibSetE2RD2V1gV1( 2, &rootD2 );
	vectorFibSetE2RD2V1gV1.setVariable( 1, pVariable1 );

	cout<<"cVectorFibSet vectorFibSetRD2V2gV1( fibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetRD2V2gV1( fibSetRootD2 );
	vectorFibSetRD2V2gV1.setVariable( 2, pVariable1 );

	cout<<"cVectorFibSet vectorFibSetRD2V2gV2( fibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetRD2V2gV2( fibSetRootD2 );
	vectorFibSetRD2V2gV2.setVariable( 2, pVariable2 );

	cout<<"cVectorFibSet vectorFibSetRD2V1gReV1( fibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetRD2V1gReV1( fibSetRootD2 );
	vectorFibSetRD2V1gReV1.setVariable( 1, pVariable1Re );

	//vectors with changed values and variables
	cout<<"cVectorFibSet vectorFibSetRD2V1gV1V2g1111( fibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetRD2V1gV1V2g1111( fibSetRootD2 );
	vectorFibSetRD2V1gV1V2g1111.setVariable( 1, pVariable1 );
	vectorFibSetRD2V1gV1V2g1111.setValue( 2, 1111 );

	cout<<"cVectorFibSet vectorFibSetE2RD2V1gV1V2g1111( 2, &rootD2 );"<<endl;
	cVectorFibSet vectorFibSetE2RD2V1gV1V2g1111( 2, &rootD2 );
	vectorFibSetE2RD2V1gV1V2g1111.setVariable( 1, pVariable1 );
	vectorFibSetE2RD2V1gV1V2g1111.setValue( 2, 1111 );

	cout<<"cVectorFibSet vectorFibSetRD2V1gV1V2g111( fibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetRD2V1gV1V2g111( fibSetRootD2 );
	vectorFibSetRD2V1gV1V2g111.setVariable( 1, pVariable1 );
	vectorFibSetRD2V1gV1V2g111.setValue( 2, 111 );

	cout<<"cVectorFibSet vectorFibSetRD2V1gV2V1g1111( 2, &rootD2 );"<<endl;
	cVectorFibSet vectorFibSetRD2V1g111V2gV2( 2, &rootD2 );
	vectorFibSetRD2V1g111V2gV2.setVariable( 1, pVariable2 );
	vectorFibSetRD2V1g111V2gV2.setValue( 2, 1111 );

	cout<<"cVectorFibSet vectorFibSetE2RD2V1g1111V2gV2( fibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetE2RD2V1gV2V2g1111( fibSetRootD2 );
	vectorFibSetE2RD2V1gV2V2g1111.setValue( 1, 1111 );
	vectorFibSetE2RD2V1gV2V2g1111.setVariable( 2, pVariable1 );

	cout<<"cVectorFibSet vectorFibSetE2RD2V1gV1V2gV2( 2, &fibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetE2RD2V1gV1V2gV2( 2, &fibSetRootD2 );
	vectorFibSetE2RD2V1gV1V2gV2.setVariable( 1, pVariable1 );
	vectorFibSetE2RD2V1gV1V2gV2.setVariable( 2, pVariable2 );

	
	//check variable from different defining element
	cout<<"cFibSet fibSetFibSetRootD2( 1, NULL, &fibSetRootD2 );"<<endl;
	cFibSet fibSetFibSetRootD2( 1, NULL, &fibSetRootD2 );

	cout<<"cVectorFibSet vectorFibSetE2FS2V1gV1V2gV2( 2, &fibSetFibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetE2FS2V1gV1V2gV2( 2, &fibSetFibSetRootD2 );
	vectorFibSetE2FS2V1gV1V2gV2.setVariable( 1, pVariable1 );
	vectorFibSetE2FS2V1gV1V2gV2.setVariable( 2, pVariable2 );

	//cout<<"pVarFibSet2 = fibSetRootD2.getDefinedVariable( 1 );"<<endl;
	cFibVariable * pVarFibSet2 = fibSetRootD2.getDefinedVariable( 2 );

	cout<<"cVectorFibSet vectorFibSetE2FS22V1gV1V2gVFS2( 2, &fibSetFibSetRootD2 );"<<endl;
	cVectorFibSet vectorFibSetE2FS22V1gV1V2gVFS2( 2, &fibSetFibSetRootD2 );
	vectorFibSetE2FS22V1gV1V2gVFS2.setVariable( 1, pVariable1 );
	vectorFibSetE2FS22V1gV1V2gVFS2.setVariable( 2, pVarFibSet2 );
	
	
	cout<<"cVectorProperty vectorProperty( 1 );"<<endl;
	cVectorProperty vectorProperty( 1 );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with vectorFibSetE3
	cFibVector * actualVector = &vectorFibSetE3;
	string szActualVectorName = "vectorFibSetE3";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetE3RD2
	actualVector = &vectorFibSetE3RD2;
	szActualVectorName = "vectorFibSetE3RD2";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetE2Re
	actualVector = &vectorFibSetE2Re;
	szActualVectorName = "vectorFibSetE2Re";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );
	
	//compare with vectorFibSetE2RD2
	actualVector = &vectorFibSetE2RD2;
	szActualVectorName = "vectorFibSetE2RD2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );
	
	//compare with vectorFibSetE2Re
	actualVector = &vectorFibSetRD2;
	szActualVectorName = "vectorFibSetRD2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetRD2V2g17p2
	actualVector = &vectorFibSetRD2V2g17p2;
	szActualVectorName = "vectorFibSetRD2V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetRD2V2g17p2
	actualVector = &vectorFibSetE2RD2V2g17p2;
	szActualVectorName = "vectorFibSetE2RD2V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetE2RD2V2g17p2001
	actualVector = &vectorFibSetE2RD2V2g17p2001;
	szActualVectorName = "vectorFibSetE2RD2V2g17p2001";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetE2RD2V2g17p2001
	actualVector = &vectorFibSetRD2V1g17p2;
	szActualVectorName = "vectorFibSetRD2V1g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetRD2V1g1p1V2gm2p2
	actualVector = &vectorFibSetRD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorFibSetRD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetE2RD2V1g1p1V2gm2p2
	actualVector = &vectorFibSetE2RD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorFibSetE2RD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetE2RD2V1g1p1V2gm2p2
	actualVector = &vectorFibSetRD2V1g1p1V2g2p2;
	szActualVectorName = "vectorFibSetRD2V1g1p1V2g2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetRD2V1gV1
	actualVector = &vectorFibSetRD2V1gV1;
	szActualVectorName = "vectorFibSetRD2V1gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetE2RD2V1gV1
	actualVector = &vectorFibSetE2RD2V1gV1;
	szActualVectorName = "vectorFibSetE2RD2V1gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetRD2V2gV1
	actualVector = &vectorFibSetRD2V2gV1;
	szActualVectorName = "vectorFibSetRD2V2gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetRD2V2gV2
	actualVector = &vectorFibSetRD2V2gV2;
	szActualVectorName = "vectorFibSetRD2V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetRD2V1gReV1
	actualVector = &vectorFibSetRD2V1gReV1;
	szActualVectorName = "vectorFibSetRD2V1gReV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetRD2V1gV1V2g1111
	actualVector = &vectorFibSetRD2V1gV1V2g1111;
	szActualVectorName = "vectorFibSetRD2V1gV1V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetE2RD2V1gV1V2g1111
	actualVector = &vectorFibSetE2RD2V1gV1V2g1111;
	szActualVectorName = "vectorFibSetE2RD2V1gV1V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetRD2V1gV1V2g111
	actualVector = &vectorFibSetRD2V1gV1V2g111;
	szActualVectorName = "vectorFibSetRD2V1gV1V2g111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetRD2V1g111V2gV2
	actualVector = &vectorFibSetRD2V1g111V2gV2;
	szActualVectorName = "vectorFibSetRD2V1g111V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetE2RD2V1gV2V2g1111
	actualVector = &vectorFibSetE2RD2V1gV2V2g1111;
	szActualVectorName = "vectorFibSetE2RD2V1gV2V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetE2RD2V1gV1V2gV2
	actualVector = &vectorFibSetE2RD2V1gV1V2gV2;
	szActualVectorName = "vectorFibSetE2RD2V1gV1V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetE2FS2V1gV1V2gV2
	actualVector = &vectorFibSetE2FS2V1gV1V2gV2;
	szActualVectorName = "vectorFibSetE2FS2V1gV1V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibSetE2FS22V1gV1V2gVFS2
	actualVector = &vectorFibSetE2FS22V1gV1V2gVFS2;
	szActualVectorName = "vectorFibSetE2FS22V1gV1V2gVFS2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorProperty
	actualVector = &vectorProperty;
	szActualVectorName = "vectorProperty";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3, "vectorFibSetE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE3RD2, "vectorFibSetE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2Re, "vectorFibSetE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2, "vectorFibSetE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2, "vectorFibSetRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2g17p2, "vectorFibSetRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2, "vectorFibSetE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V2g17p2001, "vectorFibSetE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g17p2, "vectorFibSetRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2gm2p2, "vectorFibSetRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1g1p1V2gm2p2, "vectorFibSetE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g1p1V2g2p2, "vectorFibSetRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1, "vectorFibSetRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1, "vectorFibSetE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV1, "vectorFibSetRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V2gV2, "vectorFibSetRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gReV1, "vectorFibSetRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g1111, "vectorFibSetRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2g1111, "vectorFibSetE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1gV1V2g111, "vectorFibSetRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetRD2V1g111V2gV2, "vectorFibSetRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV2V2g1111, "vectorFibSetE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2RD2V1gV1V2gV2, "vectorFibSetE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS2V1gV1V2gV2, "vectorFibSetE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibSetE2FS22V1gV1V2gVFS2, "vectorFibSetE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );


	return iReturn;
}



/**
 * This method tests the createInstance() method of the cVectorFibSet class.
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
	cout<<"cDomainVector vectorDomainE1Nat1( vecDomainsE1Nat1 );"<<endl;
	cDomainVector vectorDomainE1Nat1( vecDomainsE1Nat1 );
	delete vecDomainsE1Nat1[ 0 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 3 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE1Nat1;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE1Nat1;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE3Na2Nat3VE1Nat1 );
	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];
	
	cout<<"cTypeFibSet typeFibSet;"<<endl;
	cTypeFibSet typeFibSet;
	
	cout<<"rootD2.getDomains()->addDomain( typeFibSet, vectorDomainE3Na2Nat3VE1Nat1 );"<<endl;
	rootD2.getDomains()->addDomain( typeFibSet, vectorDomainE3Na2Nat3VE1Nat1 );

	
	cout<<"cVectorFibSet vecFibSetE4RD2 = cVectorFibSet( 4, &rootD2 );"<<endl;
	cVectorFibSet vecFibSetE4RD2 = cVectorFibSet( 4, &rootD2 );

	cout<<"cFibVector * vectorInstanceD1 = vecFibSetE4RD2.createInstance( 1 );"<<endl;
	cFibVector * vectorInstanceD1 = vecFibSetE4RD2.createInstance( 1 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorFibSet
	if ( vectorInstanceD1->getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vectorInstanceD1->getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	cTypeElement * pTypeFibSet = vectorInstanceD1->getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vectorInstanceD1->getNumberOfElements() == (unsignedIntFib)(1) ){
	
		cout<<"The number of elements of the set-element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vectorInstanceD1->getNumberOfElements()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD1->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD1->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD1->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vectorInstanceD1->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vectorInstanceD1->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the set-element vector."<<endl;
	}else if ( &rootD2 == vectorInstanceD1->getDefiningFibElement() ){
	
		cerr<<"Error: The rootD2 is the defining element for the set-element vector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is a defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vectorInstanceD1->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the set-element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the set-element vector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD1;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 3 elements"<<endl;

	cout<<"cTypeFibSet typeFibSetDom3( 3 );"<<endl;
	cTypeFibSet typeFibSetDom3( 3 );

	cout<<"cFibVector * vectorInstanceD3 = vecFibSetE4RD2.createInstance( 3 );"<<endl;
	cFibVector * vectorInstanceD3 = vecFibSetE4RD2.createInstance( 3 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorFibSet
	if ( vectorInstanceD3->getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vectorInstanceD3->getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vectorInstanceD3->getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vectorInstanceD3->getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the set-element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vectorInstanceD3->getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD3->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD3->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD3->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vectorInstanceD3->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vectorInstanceD3->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the set-element vector."<<endl;
	}else if ( &rootD2 == vectorInstanceD3->getDefiningFibElement() ){
	
		cerr<<"Error: The rootD2 is the defining element for the set-element vector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is an defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vectorInstanceD3->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the set-element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the set-element vector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD3;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 2 elements and rootD2 as an defining element"<<endl;

	cout<<"cFibVector * vectorInstanceD2RD2 = vecFibSetE4RD2.createInstance( 2, &rootD2 );"<<endl;
	cFibVector * vectorInstanceD2RD2 = vecFibSetE4RD2.createInstance( 2, &rootD2 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorFibSet
	if ( vectorInstanceD2RD2->getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vectorInstanceD2RD2->getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vectorInstanceD2RD2->getElementType();
	if ( typeFibSet == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vectorInstanceD2RD2->getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vectorInstanceD2RD2->getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD2RD2->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD2RD2->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD2RD2->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vectorInstanceD2RD2->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vectorInstanceD2RD2->getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vectorInstanceD2RD2->getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vectorInstanceD2RD2->getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE1Nat1 == (*(vectorInstanceD2RD2->getDomain())) ){
	
		cout<<"The vectorDomainE1Nat1 is the domain for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1Nat1 is not the domain for the set-element vector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD2RD2;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with different set-element as defining element"<<endl;
	
	cout<<"cFibSet fibSetRd2( 3, NULL, &rootD2 );"<<endl;
	cFibSet fibSetRd2( 3, NULL, &rootD2 );

	cout<<"fibSetRd2.setDomainNr( 5 );"<<endl;
	fibSetRd2.setDomainNr( 5 );
	
	cout<<"cFibVector * vectorInstanceD2FsRD2 = vecFibSetE4RD2.createInstance( 2, &fibSetRd2 );"<<endl;
	cFibVector * vectorInstanceD2FsRD2 = vecFibSetE4RD2.createInstance( 2, &fibSetRd2 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorFibSet
	if ( vectorInstanceD2FsRD2->getVectorType() == "set" ){
	
		cout<<"The name of the set-element vector is correctly \"set\" . "<<endl;
	}else{
		cerr<<"Error: The name of the set-element vector is "<<
			vectorInstanceD2FsRD2->getVectorType()<<" but should be \"set\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibSet
	pTypeFibSet = vectorInstanceD2FsRD2->getElementType();
	cout<<"cTypeFibSet typeFibSet5( 5 );"<<endl;
	cTypeFibSet typeFibSet5( 5 );
	if ( typeFibSet5 == (*pTypeFibSet) ){
	
		cout<<"The type of the set-element vector is correctly equal to typeFibSet5. "<<endl;
	}else{
		cerr<<"Error: The type of set-element vector not equal to typeFibSet5 ."<<endl;
		iReturn++;
	}
	delete pTypeFibSet;
	
	//check the getNumberOfElements() methode from cVectorFibSet
	if ( vectorInstanceD2FsRD2->getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the set-element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the set-element vector is "<<
			vectorInstanceD2FsRD2->getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the set-vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD2FsRD2->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD2FsRD2->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD2FsRD2->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"set-element vector is "<<vectorInstanceD2FsRD2->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibSet
	if ( vectorInstanceD2FsRD2->getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the set-element vector."<<endl;
		iReturn++;	
	}else if ( &fibSetRd2 == vectorInstanceD2FsRD2->getDefiningFibElement() ){
	
		cout<<"The fibSetRd2 is the defining element for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The fibSetRd2 is not the defining element for the set-element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibSet
	if ( vectorInstanceD2FsRD2->getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the set-element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE1Nat1 == (*(vectorInstanceD2FsRD2->getDomain())) ){
	
		cout<<"The vectorDomainE1Nat1 is the domain for the set-element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1Nat1 is not the domain for the set-element vector."<<endl;
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
	
	TiXmlDocument xmlDocVectorFibSet( szFilename );
	bool loadOkay = xmlDocVectorFibSet.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocVectorFibSet );
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
 * This method tests the storeXml() method of the cVectorFibSet class.
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
	
	cout<<"cTypeFibSet typeFibSet;"<<endl;
	cTypeFibSet typeFibSet;
	
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
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE3( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE3( 3 );
	cout<<"vecDomainsE3Na2Nat3VE3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE3[ 2 ] = &vectorDomainE3;"<<endl;
	vecDomainsE3Na2Nat3VE3[ 2 ] = &vectorDomainE3;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE3( vecDomainsE3Na2Nat3VE3 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE3( vecDomainsE3Na2Nat3VE3 );
	delete vecDomainsE3Na2Nat3VE3[ 0 ];
	delete vecDomainsE3Na2Nat3VE3[ 1 ];

	cout<<"rootD3.getDomains()->addDomain( typeFibSet, vectorDomainE3Na2Nat3VE3 );"<<endl;
	rootD3.getDomains()->addDomain( typeFibSet, vectorDomainE3Na2Nat3VE3 );

	//creat defined variables to set them later in the vector
	cout<<"rootD3.setNumberOfInputVariables( 6 )"<<endl;
	rootD3.setNumberOfInputVariables( 6 );

	cout<<"cVectorFibSet vecFibSetE3( 3, &rootD3 );"<<endl;
	cVectorFibSet vecFibSetE3( 3, &rootD3 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	const char * szVectorPostion = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorFibSetEmpty.xml" );
	ofstream fileVectorPostion( szVectorPostion );
	
	bool bStoreSuccesfull = vecFibSetE3.storeXml( fileVectorPostion );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorPostion <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorPostion <<"\" failed."<<endl;
		iReturn++;
	}
	
	vector<char> vecElementTypeFibSet( 5, 'w' );
	vector<double> vecValuesFibSet( 5, 0.0 );
	
	iReturn += testXmlVector( szVectorPostion, "set",
		3, vecElementTypeFibSet, vecValuesFibSet );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector one value set"<<endl;
	
	cout<<"vecFibSetE3.setValue( 1, 111 )"<<endl;
	vecFibSetE3.setValue( 1, 111 );
	vecElementTypeFibSet[0] = 'w';
	vecValuesFibSet[0] = 111;
	
	szFileNameBuffer[0] = 0;
	const char * szVectorFibSetRD3V1g111 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorFibSetRD3V1g111.xml" );
	ofstream fileVectorPostioRD3V1g111n( szVectorFibSetRD3V1g111 );
	
	bStoreSuccesfull = vecFibSetE3.storeXml( fileVectorPostioRD3V1g111n );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorFibSetRD3V1g111 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorFibSetRD3V1g111 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorFibSetRD3V1g111, "set",
		3, vecElementTypeFibSet, vecValuesFibSet );
	
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector all value set"<<endl;
	
	cout<<"vecFibSetE3.setValue( 2, 123.456 )"<<endl;
	vecFibSetE3.setValue( 2, 123.456  );
	vecElementTypeFibSet[1] = 'w';
	vecValuesFibSet[1] = 123.456;
	cout<<"vecFibSetE3.setValue( 3, -123.456 )"<<endl;
	vecFibSetE3.setValue( 3, -123.456 );
	vecElementTypeFibSet[2] = 'w';
	vecValuesFibSet[2] = -123.456;

	szFileNameBuffer[0] = 0;
	const char * szVectorFibSetRD3T3 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorFibSetRD3T3.xml" );
	ofstream fileVectorFibSetRD3T3( szVectorFibSetRD3T3 );
	
	bStoreSuccesfull = vecFibSetE3.storeXml( fileVectorFibSetRD3T3 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorFibSetRD3T3 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorFibSetRD3T3 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorFibSetRD3T3, "set",
		3, vecElementTypeFibSet, vecValuesFibSet );

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
	
	cout<<"vecFibSetE3.setVariable( 1, pVariable1 )"<<endl;
	vecFibSetE3.setVariable( 1, pVariable1  );
	vecElementTypeFibSet[0] = 'v';
	vecValuesFibSet[0] = 1;
	cout<<"vecFibSetE3.setVariable( 2, pVariable2 )"<<endl;
	vecFibSetE3.setVariable( 2, pVariable2 );
	vecElementTypeFibSet[1] = 'v';
	vecValuesFibSet[1] = 2;
	cout<<"vecFibSetE3.setVariable( 3, pVariable3 )"<<endl;
	vecFibSetE3.setVariable( 3, pVariable3 );
	vecElementTypeFibSet[2] = 'v';
	vecValuesFibSet[2] = 3;

	szFileNameBuffer[0] = 0;
	const char * szVectorFibSetRD3T4 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorFibSetRD3T4.xml" );
	ofstream fileVectorFibSetRD3T4( szVectorFibSetRD3T4 );
	
	bStoreSuccesfull = vecFibSetE3.storeXml( fileVectorFibSetRD3T4 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorFibSetRD3T4 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorFibSetRD3T4 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorFibSetRD3T4, "set",
		3, vecElementTypeFibSet, vecValuesFibSet );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector with variables and values"<<endl;
	
	cout<<"vecFibSetE3.setVariable( 1, pVariable1 )"<<endl;
	vecFibSetE3.setVariable( 1, pVariable1  );
	vecElementTypeFibSet[0] = 'v';
	vecValuesFibSet[0] = 1;
	cout<<"vecFibSetE3.setValue( 2, -0.00124 )"<<endl;
	vecFibSetE3.setValue( 2, -0.00124 );
	vecElementTypeFibSet[1] = 'w';
	vecValuesFibSet[1] = -0.00124;
	cout<<"vecFibSetE3.setVariable( 3, pVariable3 )"<<endl;
	vecFibSetE3.setVariable( 3, pVariable3 );
	vecElementTypeFibSet[2] = 'v';
	vecValuesFibSet[2] = 3;

	szFileNameBuffer[0] = 0;
	const char * szVectorFibSetRD3T5 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorFibSetRD3T5.xml" );
	ofstream fileVectorFibSetRD3T5( szVectorFibSetRD3T5 );
	
	bStoreSuccesfull = vecFibSetE3.storeXml( fileVectorFibSetRD3T5 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorFibSetRD3T5 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorFibSetRD3T5 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorFibSetRD3T5, "set",
		3, vecElementTypeFibSet, vecValuesFibSet );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 5 d vector with variables and values"<<endl;
	
	cout<<"cVectorFibSet vecFibSetRD5 = cVectorFibSet( 5, &rootD3 );"<<endl;
	cVectorFibSet vecFibSetRD5 = cVectorFibSet( 5, &rootD3 );

	cout<<"vecFibSetRD5.setVariable( 1, pVariable1 )"<<endl;
	vecFibSetRD5.setVariable( 1, pVariable1  );
	vecElementTypeFibSet[0] = 'v';
	vecValuesFibSet[0] = 1;
	cout<<"vecFibSetRD5.setValue( 2, -0.00124 )"<<endl;
	vecFibSetRD5.setValue( 2, -0.00124 );
	vecElementTypeFibSet[1] = 'w';
	vecValuesFibSet[1] = -0.00124;
	cout<<"vecFibSetRD5.setVariable( 3, pVariable3 )"<<endl;
	vecFibSetRD5.setVariable( 3, pVariable3 );
	vecElementTypeFibSet[2] = 'v';
	vecValuesFibSet[2] = 3;
	cout<<"vecFibSetRD5.setValue( 4, 1234 )"<<endl;
	vecFibSetRD5.setValue( 4, 1234 );
	vecElementTypeFibSet[3] = 'w';
	vecValuesFibSet[3] = 1234;
	cout<<"vecFibSetRD5.setValue( 5, 123.67 )"<<endl;
	vecFibSetRD5.setValue( 5, 123.67   );
	vecElementTypeFibSet[4] = 'w';
	vecValuesFibSet[4] = 123.67 ;

	szFileNameBuffer[0] = 0;
	const char * szVectorFibSetRD3T6 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorFibSetRD3T6.xml" );
	ofstream fileVectorFibSetRD3T6( szVectorFibSetRD3T6 );
	
	bStoreSuccesfull = vecFibSetRD5.storeXml( fileVectorFibSetRD3T6 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorFibSetRD3T6 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorFibSetRD3T6 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorFibSetRD3T6, "set",
		5, vecElementTypeFibSet, vecValuesFibSet );


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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a set-element vector with 0 elements"<<endl;

	cout<<"cVectorFibSet vecFibSetE0( 0 );"<<endl;
	cVectorFibSet vecFibSetE0( 0 );

	//test get compressed size
	unsigned int uiCompressedSize = 0;
	if ( (unsigned int)(vecFibSetE0.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibSetE0.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibSetE0.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	cout<<"vecFibSetE0.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bool bStoreSuccesfull = vecFibSetE0.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cFibSetE0[] = { (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibSetE0, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a set-element vector with 2 elements"<<endl;

	cout<<"cVectorFibSet vecFibSet1E2Ch( 2 );"<<endl;
	cVectorFibSet vecFibSet1E2Ch( 2 );
	cout<<"vecFibSet1E2Ch.setValue( 1, 4 );"<<endl;
	vecFibSet1E2Ch.setValue( 1, 4 );
	cout<<"vecFibSet1E2Ch.setValue( 2, 6 );"<<endl;
	vecFibSet1E2Ch.setValue( 2, 6 );

	//test get compressed size
	uiCompressedSize = 2 * 33;
	if ( (unsigned int)(vecFibSet1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibSet1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibSet1E2Ch.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibSet1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibSet1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cFibSetE2[] = { (char)0x08, (char)0x00, (char)0x00, (char)0x00, (char)0x18, (char)0x00, (char)0x00, (char)0x00, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibSetE2, 9 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a set-element vector with variables"<<endl;

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

	cout<<"vecFibSet1E2Ch.setVariable( 1, pVariable1);"<<endl;
	vecFibSet1E2Ch.setVariable( 1, pVariable1);
	cout<<"vecFibSet1E2Ch.setVariable( 2, pVariable2);"<<endl;
	vecFibSet1E2Ch.setVariable( 2, pVariable2);

	//test get compressed size
	uiCompressedSize = 2 * 9;
	if ( (unsigned int)(vecFibSet1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibSet1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibSet1E2Var.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibSet1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibSet1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cFibSetE2Var[] = { (char)0x03, (char)0x0A, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibSetE2Var, 3 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a set-element vector with domains"<<endl;

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
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE2Nat1Nat2( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE2Nat1Nat2( 3 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat1Nat2[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE2Nat1Nat2[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat1Nat2[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE2Nat1Nat2[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat1Nat2[ 2 ] = &vectorDomainE2;"<<endl;
	vecDomainsE3Na2Nat3VE2Nat1Nat2[ 2 ] = &vectorDomainE2;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE2Nat1Nat2( vecDomainsE3Na2Nat3VE2Nat1Nat2 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE2Nat1Nat2( vecDomainsE3Na2Nat3VE2Nat1Nat2 );
	delete vecDomainsE3Na2Nat3VE2Nat1Nat2[ 0 ];
	delete vecDomainsE3Na2Nat3VE2Nat1Nat2[ 1 ];

	cout<<"cTypeFibSet typeFibSet;"<<endl;
	cTypeFibSet typeFibSet;
	
	cout<<"rootD2.getDomains()->addDomain( typeFibSet, &vectorDomainE3Na2Nat3VE2Nat1Nat2 );"<<endl;
	rootD2.getDomains()->addDomain( typeFibSet, &vectorDomainE3Na2Nat3VE2Nat1Nat2 );

	cout<<"cTypeVariable typeVariable;"<<endl;
	cTypeVariable typeVariable;

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB3( 3 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB3( 3 );

	cout<<"rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB3);"<<endl;
	rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB3);

	cout<<"vecFibSet1E2Ch.setDefiningFibElement( &rootD2 );"<<endl;
	vecFibSet1E2Ch.setDefiningFibElement( &rootD2 );
	
	cout<<"vecFibSet1E2Ch.setValue( 2, 3 );"<<endl;
	vecFibSet1E2Ch.setValue( 2, 3 );

	//test get compressed size
	uiCompressedSize = 4 + 3;
	if ( (unsigned int)(vecFibSet1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibSet1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibSet1E2Dom.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibSet1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibSet1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cFibSetE2Dom[] = { (char)ucRestBitCorrect };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibSetE2Dom, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a set-element vector 3 elements"<<endl;

	cout<<"cVectorFibSet vecFibSet1E3( 3 );"<<endl;
	cVectorFibSet vecFibSet1E3( 3 );
	
	cout<<"vecFibSet1E3.setVariable( 1, pVariable2 );"<<endl;
	vecFibSet1E3.setVariable( 1, pVariable2 );
	cout<<"vecFibSet1E3.setVariable( 2, pVariable1 );"<<endl;
	vecFibSet1E3.setVariable( 2, pVariable1);
	cout<<"vecFibSet1E3.setValue( 3, 5);"<<endl;
	vecFibSet1E3.setValue( 3, 5);

	//test get compressed size
	uiCompressedSize = 2 * 9 + 33;
	if ( (unsigned int)(vecFibSet1E3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibSet1E3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibSet1E3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibSet1E3.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibSet1E3.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cVecFibSet1E3[] = { (char)0x05, (char)0x06, (char)0x28, (char)0x00, (char)0x00, (char)0x00, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cVecFibSet1E3, 7 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a set-element vector with a restbit of 4"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibSet1E3R4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x0F;
	cNumberOfRestBit = 4;
	cout<<"vecFibSet1E3.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibSet1E3.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cVecFibSet1E3R4[] = { (char)0x5F, (char)0x60, (char)0x80, (char)0x02, (char)0x00, (char)0x00, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cVecFibSet1E3R4, 7 );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a set-element vector with domain not 0"<<endl;

	//create vector domain with two elements
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"cDomainVector vectorDomainE2Nat3Nat4( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat3Nat4( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE2Nat3Nat4( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE2Nat3Nat4( 3 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat3Nat4[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE2Nat3Nat4[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat3Nat4[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE2Nat3Nat4[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat3Nat4[ 2 ] = &vectorDomainE2Nat3Nat4;"<<endl;
	vecDomainsE3Na2Nat3VE2Nat3Nat4[ 2 ] = &vectorDomainE2Nat3Nat4;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE2Nat3Nat4( vecDomainsE3Na2Nat3VE2Nat3Nat4 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE2Nat3Nat4( vecDomainsE3Na2Nat3VE2Nat3Nat4 );
	delete vecDomainsE3Na2Nat3VE2Nat3Nat4[ 0 ];
	delete vecDomainsE3Na2Nat3VE2Nat3Nat4[ 1 ];

	cout<<"cTypeFibSet typeFibSet4( 4 );"<<endl;
	cTypeFibSet typeFibSet4( 4 );
	
	cout<<"rootD2.getDomains()->addDomain( typeFibSet4, &vectorDomainE3Na2Nat3VE2Nat3Nat4 );"<<endl;
	rootD2.getDomains()->addDomain( typeFibSet4, &vectorDomainE3Na2Nat3VE2Nat3Nat4 );
	
	cout<<"cFibSet setElement( 2, NULL, &rootD2 );"<<endl;
	cFibSet setElement( 2, NULL, &rootD2 );
	
	cout<<"setElement.setDomainNr( 1 );"<<endl;
	setElement.setDomainNr( 1 );
	
	cout<<"vecFibSet1E2Ch.setDefiningFibElement( &setElement );"<<endl;
	vecFibSet1E2Ch.setDefiningFibElement( &setElement );
	
	//test get compressed size
	uiCompressedSize = 4 + 3;
	if ( (unsigned int)(vecFibSet1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibSet1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibSet1E2Dom1.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibSet1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibSet1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cFibSetE2Dom1[] = { (char)ucRestBitCorrect };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibSetE2Dom1, 1 );
	
	
	cout<<endl<<"setElement.setDomainNr( 3 );"<<endl;
	setElement.setDomainNr( 3 );
	
	cout<<"vecFibSet1E2Ch.setDefiningFibElement( &setElement );"<<endl;
	vecFibSet1E2Ch.setDefiningFibElement( &setElement );
	
	//test get compressed size
	uiCompressedSize = 4 + 3;
	if ( (unsigned int)(vecFibSet1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibSet1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibSet1E2Dom3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibSet1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibSet1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cFibSetE2Dom3[] = { (char)ucRestBitCorrect };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibSetE2Dom3, 1 );

	
	cout<<endl<<"setElement.setDomainNr( 4 );"<<endl;
	setElement.setDomainNr( 4 );
	
	cout<<"vecFibSet1E2Ch.setDefiningFibElement( &setElement );"<<endl;
	vecFibSet1E2Ch.setDefiningFibElement( &setElement );
	
	//test get compressed size
	uiCompressedSize = 4 + 5;
	if ( (unsigned int)(vecFibSet1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibSet1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibSet1E2Dom4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibSet1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibSet1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cFibSetE2Dom4[] = { (char)0x63, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibSetE2Dom4, 2 );

	
	
	cout<<endl<<"setElement.setDomainNr( 5 );"<<endl;
	setElement.setDomainNr( 5 );
	
	cout<<"vecFibSet1E2Ch.setDefiningFibElement( &setElement );"<<endl;
	vecFibSet1E2Ch.setDefiningFibElement( &setElement );
	
	//test get compressed size
	uiCompressedSize = 4 + 5;
	if ( (unsigned int)(vecFibSet1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibSet1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibSet1E2Dom5.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibSet1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibSet1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibSetE2Dom4, 2 );

	
	
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
	
	cout<<"cFibVector * pVecFibSetDestination = new cVectorFibSet();"<<endl;
	cFibVector  * pVecFibSetDestination = new cVectorFibSet();
	
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
			unsigned int uiNumberOfFibSets = 0;
			if ( (rand() % 10) != 0 ){
				uiNumberOfFibSets = (rand() % 3 + 1) * (rand() % 4 + 1) + (rand() % 4);
			}else{
				uiNumberOfFibSets = 0;
			}
			cout<<"pVecSource = new cVectorFibSet( "<< uiNumberOfFibSets <<", &emptyRoot ); "<<endl;
			pVecSource = new cVectorFibSet( uiNumberOfFibSets, &emptyRoot );
			
			pVecEqual = pVecSource;
		}else{//create non position vector
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
			pVecEqual = new cVectorFibSet( pVecSource->getNumberOfElements(), &emptyRoot  );
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
		cout<<"(* pVecFibSetDestination) = (* pVecSource );"<<endl;
		(* pVecFibSetDestination) = (* pVecSource );
		
		//test the created vector
		if ( (*pVecFibSetDestination) == ( * pVecEqual) ){
		
			cout<<"The vecFibSetDestination is correct . "<<endl;
		}else{
			cerr<<"Error: The vecFibSetDestination is not correct ."<<endl;
			iReturn++;
		}
		
		if ( pVecEqual != pVecSource ){
			//pVecEqual and pVecSource are different vectors
			delete pVecEqual;
		}
		delete pVecSource;
	}
	delete pVecFibSetDestination;
	
	return iReturn;
}




















