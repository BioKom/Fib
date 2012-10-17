/**
 * @file tVectorPosition
 * file name: tVectorPosition.cpp
 * @author Betti Oesterholz
 * @date 14.10.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cVectorPosition.
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
 * This file contains the test for the class cVectorPosition,
 * which represents the vector for positions.
 *
 *
 *
 *  What's tested of class cVectorPosition:
 * 	- cVectorPosition( cFibElement & definingPointElement );
 * 	- cVectorPosition( unsignedIntFib iNumberOfDimensions = 2, cFibElement * definingPointElement = NULL );
 * 	- cVectorPosition( const cVectorPosition & vector, cFibElement * definingFibElement = NULL );
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
14.10.2009  Oesterholz  created
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

#include "cVectorPosition.h"
#include "cVectorArea.h"
#include "cVectorProperty.h"
#include "cTypeDimension.h"
#include "cTypeVariable.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cRoot.h"
#include "cPoint.h"

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
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for cVectorPosition methods"<<endl;
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
 * and getType() method of the cVectorPosition class.
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

	int iReturn=0;//returnvalue of the test; the number of occured Errors

//TODO change  root element to point element
//TODO test constructor with correct domain

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cVectorPosition"<<endl;

	cout<<"cTypeDimension typeDimensionD2( 2 );"<<endl;
	cTypeDimension typeDimensionD2( 2 );
	
	cout<<"cVectorPosition vecPosition = cVectorPosition();"<<endl;
	cVectorPosition vecPosition = cVectorPosition();


	//check the getVectorType() methode from cVectorPosition
	if ( vecPosition.getVectorType() == "position" ){
	
		cout<<"The name of the positionsvector is correctly \"position\" . "<<endl;
	}else{
		cerr<<"Error: The name of the positionsvector is "<<
			vecPosition.getVectorType()<<" but should be \"position\" ."<<endl;
		iReturn++;
	}
	
	
	//check the getElementType() methode from cVectorPosition
	cTypeElement * pTypeDimension = vecPosition.getElementType();
	if ( typeDimensionD2 == (*pTypeDimension) ){
	
		cout<<"The type of the positionsvector is correctly equal to typeDimensionD2. "<<endl;
	}else{
		cerr<<"Error: The type of positionsvector not equal to typeDimensionD2 ."<<endl;
		iReturn++;
	}
	delete pTypeDimension;
	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vecPosition.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the positionsvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vecPosition.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the positionsvektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecPosition.getNumberOfElements(); 
			uiActualElement++ ){
		
		if ( ! vecPosition.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecPosition.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is "<<vecPosition.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPosition.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the positionsvector."<<endl;
		iReturn++;
	}

	//check the getDomain() methode from cVectorPosition
	if ( vecPosition.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the positionsvector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorPosition with 3 dimensions"<<endl;

	cout<<"cTypeDimension typeDimensionD3( 3 );"<<endl;
	cTypeDimension typeDimensionD3( 3 );
	
	cout<<"cVectorPosition vecPositionD3 = cVectorPosition( 3 );"<<endl;
	cVectorPosition vecPositionD3 = cVectorPosition( 3 );


	//check the getVectorType() methode from cVectorPosition
	if ( vecPositionD3.getVectorType() == "position" ){
	
		cout<<"The name of the positionsvector is correctly \"position\" . "<<endl;
	}else{
		cerr<<"Error: The name of the positionsvector is "<<
			vecPositionD3.getVectorType()<<" but should be \"position\" ."<<endl;
		iReturn++;
	}
	
	
	//check the getElementType() methode from cVectorPosition
	pTypeDimension = vecPositionD3.getElementType();
	if ( typeDimensionD3 == (*pTypeDimension) ){
	
		cout<<"The type of the positionsvector is correctly equal to typeDimensionD3. "<<endl;
	}else{
		cerr<<"Error: The type of positionsvector not equal to typeDimensionD3 ."<<endl;
		iReturn++;
	}
	delete pTypeDimension;
	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vecPositionD3.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the positionsvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vecPositionD3.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the positionsvektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecPositionD3.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecPosition.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecPositionD3.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is "<<vecPositionD3.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPositionD3.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the positionsvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorPosition
	if ( vecPositionD3.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the positionsvector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorPosition with 4 dimensions and an defining element"<<endl;

	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;

	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeDimension testTypeDimensionD2( 2 );"<<endl;
	cTypeDimension testTypeDimensionD2( 2 );
	cout<<"testTypeDimensionD2.setDimensionMapping( 1, 4 )"<<endl;
	testTypeDimensionD2.setDimensionMapping( 1, 4 );
	cout<<"testTypeDimensionD2.setDimensionMapping( 2, 3 )"<<endl;
	testTypeDimensionD2.setDimensionMapping( 2, 3 );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomains2( 2 );"<<endl;
	vector<cDomainSingle*> vecDomains2( 2 );
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomainD2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainD2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];

	cout<<"rootD2.getDomains()->addDomain( testTypeDimensionD2, vectorDomainD2);"<<endl;
	rootD2.getDomains()->addDomain( testTypeDimensionD2, vectorDomainD2);

	
	cout<<"cVectorPosition vecPositionD4RD2 = cVectorPosition( 4, &rootD2 );"<<endl;
	cVectorPosition vecPositionD4RD2 = cVectorPosition( 4, &rootD2 );


	//check the getVectorType() methode from cVectorPosition
	if ( vecPositionD4RD2.getVectorType() == "position" ){
	
		cout<<"The name of the positionsvector is correctly \"position\" . "<<endl;
	}else{
		cerr<<"Error: The name of the positionsvector is "<<
			vecPositionD4RD2.getVectorType()<<" but should be \"position\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorPosition
	pTypeDimension = vecPositionD4RD2.getElementType();
	if ( testTypeDimensionD2 == (*pTypeDimension) ){
	
		cout<<"The type of the positionsvector is correctly equal to testTypeDimensionD2. "<<endl;
	}else{
		cerr<<"Error: The type of positionsvector not equal to testTypeDimensionD2 ."<<endl;
		iReturn++;
	}
	delete pTypeDimension;
	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vecPositionD4RD2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the positionsvector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vecPositionD4RD2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the positionsvektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecPositionD4RD2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecPositionD4RD2.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecPositionD4RD2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is "<<vecPositionD4RD2.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPositionD4RD2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecPositionD4RD2.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the positionsvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorPosition
	if ( vecPositionD4RD2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the positionsvector."<<endl;
		iReturn++;	
	}else if ( vectorDomainD2 == (*(vecPositionD4RD2.getDomain())) ){
	
		cout<<"The vectorDomainD2 is the domain for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainD2 is not the domain for the positionsvector."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorPosition with an empty root element"<<endl;

	cout<<"cTypeDimension typeDimensionStandard;"<<endl;
	cTypeDimension typeDimensionStandard;
	
	cout<<"cVectorPosition vecPositionD4RE = cVectorPosition( emptyRoot );"<<endl;
	cVectorPosition vecPositionD4RE = cVectorPosition( emptyRoot );


	//check the getVectorType() methode from cVectorPosition
	if ( vecPositionD4RE.getVectorType() == "position" ){
	
		cout<<"The name of the positionsvector is correctly \"position\" . "<<endl;
	}else{
		cerr<<"Error: The name of the positionsvector is "<<
			vecPositionD4RE.getVectorType()<<" but should be \"position\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorPosition
	pTypeDimension = vecPositionD4RE.getElementType();
	if ( typeDimensionStandard == (*pTypeDimension) ){
	
		cout<<"The type of the positionsvector is correctly equal to typeDimensionStandard. "<<endl;
	}else{
		cerr<<"Error: The type of positionsvector not equal to typeDimensionStandard ."<<endl;
		iReturn++;
	}
	delete pTypeDimension;
	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vecPositionD4RE.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the positionsvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vecPositionD4RE.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the positionsvektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecPositionD4RE.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecPositionD4RE.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecPositionD4RE.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is "<<vecPositionD4RE.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPositionD4RE.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &emptyRoot == vecPositionD4RE.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the positionsvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorPosition
	if ( vecPositionD4RE.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the positionsvector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the positionsvector."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorPosition with the rootD2 root element"<<endl;
	
	cout<<"cVectorPosition vecPositionRD2 = cVectorPosition( rootD2 );"<<endl;
	cVectorPosition vecPositionRD2 = cVectorPosition( rootD2 );

	//check the getVectorType() methode from cVectorPosition
	if ( vecPositionRD2.getVectorType() == "position" ){
	
		cout<<"The name of the positionsvector is correctly \"position\" . "<<endl;
	}else{
		cerr<<"Error: The name of the positionsvector is "<<
			vecPositionRD2.getVectorType()<<" but should be \"position\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorPosition
	pTypeDimension = vecPositionRD2.getElementType();
	if ( testTypeDimensionD2 == (*pTypeDimension) ){
	
		cout<<"The type of the positionsvector is correctly equal to testTypeDimensionD2. "<<endl;
	}else{
		cerr<<"Error: The type of positionsvector not equal to testTypeDimensionD2 ."<<endl;
		iReturn++;
	}
	delete pTypeDimension;
	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vecPositionRD2.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the positionsvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vecPositionRD2.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the positionsvektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecPositionRD2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecPositionRD2.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecPositionRD2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is "<<vecPositionRD2.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPositionRD2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecPositionRD2.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the positionsvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorPosition
	if ( vecPositionRD2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the positionsvector."<<endl;
		iReturn++;	
	}else if ( vectorDomainD2 == (*(vecPositionRD2.getDomain())) ){
	
		cout<<"The vectorDomainD2 is the domain for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainD2 is not the domain for the positionsvector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorPosition with the rootD3 root element"<<endl;
	
	cout<<"cRoot rootD3;"<<flush<<endl;
	cRoot rootD3;
	
	cout<<"cTypeDimension testTypeDimensionD3( 3 );"<<endl;
	cTypeDimension testTypeDimensionD3( 3 );
	cout<<"testTypeDimensionD3.setDimensionMapping( 1, 4 )"<<endl;
	testTypeDimensionD3.setDimensionMapping( 1, 4 );
	cout<<"testTypeDimensionD3.setDimensionMapping( 2, 1 )"<<endl;
	testTypeDimensionD3.setDimensionMapping( 2, 1 );
	cout<<"testTypeDimensionD3.setDimensionMapping( 3, 2 )"<<endl;
	testTypeDimensionD3.setDimensionMapping( 3, 2 );
	
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
	
	cout<<"rootD3.getDomains()->addDomain( testTypeDimensionD3, &vectorDomainD3 );"<<endl;
	rootD3.getDomains()->addDomain( testTypeDimensionD3, &vectorDomainD3 );

	cout<<"cVectorPosition vecPositionRD3 = cVectorPosition( rootD3 );"<<endl;
	cVectorPosition vecPositionRD3 = cVectorPosition( rootD3 );

	//check the getVectorType() methode from cVectorPosition
	if ( vecPositionRD3.getVectorType() == "position" ){
	
		cout<<"The name of the positionsvector is correctly \"position\" . "<<endl;
	}else{
		cerr<<"Error: The name of the positionsvector is "<<
			vecPositionRD3.getVectorType()<<" but should be \"position\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorPosition
	pTypeDimension = vecPositionRD3.getElementType();
	if ( testTypeDimensionD3 == (*pTypeDimension) ){
	
		cout<<"The type of the positionsvector is correctly equal to testTypeDimensionD3. "<<endl;
	}else{
		cerr<<"Error: The type of positionsvector not equal to testTypeDimensionD3 ."<<endl;
		iReturn++;
	}
	delete pTypeDimension;
	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vecPositionRD3.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the positionsvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vecPositionRD3.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the positionsvektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecPositionRD3.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecPositionRD3.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecPositionRD3.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is "<<vecPositionRD3.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPositionRD3.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &rootD3 == vecPositionRD3.getDefiningFibElement() ){
	
		cout<<"The rootD3 is the defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The rootD3 is not the defining element for the positionsvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorPosition
	if ( vecPositionRD3.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainD3 == vecPositionRD3.getDomain() ){
	
		cout<<"The vectorDomainD3 is the domain for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainD3 is not the domain for the positionsvector."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorPosition by copying vecPositionRD3"<<endl;
	
	cout<<"cVectorPosition vecPositionRD3Copy( vecPositionRD3 );"<<endl;
	cVectorPosition vecPositionRD3Copy( vecPositionRD3 );

	//check the getVectorType() methode from cVectorPosition
	if ( vecPositionRD3Copy.getVectorType() == "position" ){
	
		cout<<"The name of the positionsvector is correctly \"position\" . "<<endl;
	}else{
		cerr<<"Error: The name of the positionsvector is "<<
			vecPositionRD3Copy.getVectorType()<<" but should be \"position\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorPosition
	pTypeDimension = vecPositionRD3Copy.getElementType();
	if ( testTypeDimensionD3 == (*pTypeDimension) ){
	
		cout<<"The type of the positionsvector is correctly equal to testTypeDimensionD3. "<<endl;
	}else{
		cerr<<"Error: The type of positionsvector not equal to testTypeDimensionD3 ."<<endl;
		iReturn++;
	}
	delete pTypeDimension;
	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vecPositionRD3Copy.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the positionsvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vecPositionRD3Copy.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the positionsvektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecPositionRD3Copy.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecPositionRD3Copy.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecPositionRD3Copy.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is "<< vecPositionRD3Copy.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPositionRD3Copy.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &rootD3 == vecPositionRD3Copy.getDefiningFibElement() ){
	
		cout<<"The rootD3 is the defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The rootD3 is not the defining element for the positionsvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorPosition
	if ( vecPositionRD3Copy.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainD3 == vecPositionRD3Copy.getDomain() ){
	
		cout<<"The vectorDomainD3 is the domain for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainD3 is not the domain for the positionsvector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorPosition by copying vecPositionRD3 and givin rootD2 as an defining element"<<endl;
	
	cout<<"cVectorPosition vecPositionRD3Copy2 = cVectorPosition( vecPositionRD3, &rootD2 );"<<endl;
	cVectorPosition vecPositionRD3Copy2 = cVectorPosition( vecPositionRD3, &rootD2 );

	//check the getVectorType() methode from cVectorPosition
	if ( vecPositionRD3Copy2.getVectorType() == "position" ){
	
		cout<<"The name of the positionsvector is correctly \"position\" . "<<endl;
	}else{
		cerr<<"Error: The name of the positionsvector is "<<
			vecPositionRD3Copy2.getVectorType()<<" but should be \"position\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorPosition
	pTypeDimension = vecPositionRD3Copy2.getElementType();
	if ( testTypeDimensionD2 == (*pTypeDimension) ){
	
		cout<<"The type of the positionsvector is correctly equal to testTypeDimensionD2. "<<endl;
	}else{
		cerr<<"Error: The type of positionsvector not equal to testTypeDimensionD2 ."<<endl;
		iReturn++;
	}
	delete pTypeDimension;
	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vecPositionRD3Copy2.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the positionsvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vecPositionRD3Copy2.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the positionsvektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecPositionRD3Copy2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecPositionRD3Copy2.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecPositionRD3Copy2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is "<< vecPositionRD3Copy2.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPositionRD3Copy2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecPositionRD3Copy2.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the positionsvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorPosition
	if ( vecPositionRD3Copy2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the positionsvector."<<endl;
		iReturn++;	
	}else if ( vectorDomainD2 == *(vecPositionRD3Copy2.getDomain()) ){
	
		cout<<"The vectorDomainD2 is the domain for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainD2 is not the domain for the positionsvector."<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorPosition by copying vecPositionRD3 with changed elements"<<endl;
	
	cout<<"rootD3.setNumberOfInputVariables( 2 );"<<endl;
	rootD3.setNumberOfInputVariables( 2 );
	cout<<"cFibVariable * pVariable1 = rootD3.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootD3.getInputVariable( 1 );
	cout<<"cFibVariable * pVariable2 = rootD3.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = rootD3.getInputVariable( 2 );

	cout<<"vecPositionRD3.setValue( 1, 1 );"<<endl;
	vecPositionRD3.setValue( 1, 1 );
	cout<<"vecPositionRD3.setValue( 2, 2 );"<<endl;
	vecPositionRD3.setValue( 2, 2 );
	cout<<"vecPositionRD3.setVariable( 3, pVariable1 );"<<endl;
	vecPositionRD3.setVariable( 3, pVariable1 );
	
	cout<<"cVectorPosition vecPositionRD3CopyMod = cVectorPosition( vecPositionRD3 );"<<endl;
	cVectorPosition vecPositionRD3CopyMod = cVectorPosition( vecPositionRD3 );

	//check the getVectorType() methode from cVectorPosition
	if ( vecPositionRD3CopyMod.getVectorType() == "position" ){
	
		cout<<"The name of the positionsvector is correctly \"position\" . "<<endl;
	}else{
		cerr<<"Error: The name of the positionsvector is "<<
			vecPositionRD3CopyMod.getVectorType()<<" but should be \"position\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorPosition
	pTypeDimension = vecPositionRD3CopyMod.getElementType();
	if ( testTypeDimensionD3 == (*pTypeDimension) ){
	
		cout<<"The type of the positionsvector is correctly equal to testTypeDimensionD3. "<<endl;
	}else{
		cerr<<"Error: The type of positionsvector not equal to testTypeDimensionD3 ."<<endl;
		iReturn++;
	}
	delete pTypeDimension;
	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vecPositionRD3CopyMod.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the positionsvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vecPositionRD3CopyMod.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the positionsvektor*/
		//check the first vectorelement
	if ( ! vecPositionRD3CopyMod.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecPositionRD3CopyMod.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPositionRD3CopyMod.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( ! vecPositionRD3CopyMod.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecPositionRD3CopyMod.getValue( 2 ) == (doubleFib)(2) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPositionRD3CopyMod.getValue( 2 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecPositionRD3CopyMod.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPositionRD3CopyMod.getVariable( 3 ) == pVariable1 ){
	
		cout<<"The 3'th element of the positionsvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the positionsvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPositionRD3CopyMod.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &rootD3 == vecPositionRD3Copy.getDefiningFibElement() ){
	
		cout<<"The rootD3 is the defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The rootD3 is not the defining element for the positionsvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorPosition
	if ( vecPositionRD3CopyMod.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainD3 == vecPositionRD3CopyMod.getDomain() ){
	
		cout<<"The vectorDomainD3 is the domain for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainD3 is not the domain for the positionsvector."<<endl;
		iReturn++;
	}


	cout<<endl<<"Testing the original vector vecPositionRD3:"<<endl;

	//check the getVectorType() methode from cVectorPosition
	if ( vecPositionRD3.getVectorType() == "position" ){
	
		cout<<"The name of the positionsvector is correctly \"position\" . "<<endl;
	}else{
		cerr<<"Error: The name of the positionsvector is "<<
			vecPositionRD3.getVectorType()<<" but should be \"position\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorPosition
	pTypeDimension = vecPositionRD3.getElementType();
	if ( testTypeDimensionD3 == (*pTypeDimension) ){
	
		cout<<"The type of the positionsvector is correctly equal to testTypeDimensionD3. "<<endl;
	}else{
		cerr<<"Error: The type of positionsvector not equal to testTypeDimensionD3 ."<<endl;
		iReturn++;
	}
	delete pTypeDimension;
	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vecPositionRD3.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the positionsvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vecPositionRD3.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the positionsvektor*/
		//check the first vectorelement
	if ( ! vecPositionRD3.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecPositionRD3.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPositionRD3.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( ! vecPositionRD3.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecPositionRD3.getValue( 2 ) == (doubleFib)(2) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPositionRD3.getValue( 2 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecPositionRD3.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPositionRD3.getVariable( 3 ) == pVariable1 ){
	
		cout<<"The 3'th element of the positionsvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the positionsvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPositionRD3.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &rootD3 == vecPositionRD3Copy.getDefiningFibElement() ){
	
		cout<<"The rootD3 is the defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The rootD3 is not the defining element for the positionsvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorPosition
	if ( vecPositionRD3.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainD3 == vecPositionRD3.getDomain() ){
	
		cout<<"The vectorDomainD3 is the domain for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainD3 is not the domain for the positionsvector."<<endl;
		iReturn++;
	}

	cout<<endl<<"Changing vecPositionRD3 should not change the copy:"<<endl;

	cout<<"vecPositionRD3.setVariable( 1, pVariable2 );"<<endl;
	vecPositionRD3.setVariable( 1, pVariable2 );
	cout<<"vecPositionRD3.setValue( 2, 9 );"<<endl;
	vecPositionRD3.setValue( 2, 1 );
	cout<<"vecPositionRD3.setValue( 3, 8 );"<<endl;
	vecPositionRD3.setValue( 3, 2 );

	cout<<endl<<"Testing the copied vector vecPositionRD3CopyMod for changed values:"<<endl;
	
	//check the getVectorType() methode from cVectorPosition
	if ( vecPositionRD3CopyMod.getVectorType() == "position" ){
	
		cout<<"The name of the positionsvector is correctly \"position\" . "<<endl;
	}else{
		cerr<<"Error: The name of the positionsvector is "<<
			vecPositionRD3CopyMod.getVectorType()<<" but should be \"position\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorPosition
	pTypeDimension = vecPositionRD3CopyMod.getElementType();
	if ( testTypeDimensionD3 == (*pTypeDimension) ){
	
		cout<<"The type of the positionsvector is correctly equal to testTypeDimensionD3. "<<endl;
	}else{
		cerr<<"Error: The type of positionsvector not equal to testTypeDimensionD3 ."<<endl;
		iReturn++;
	}
	delete pTypeDimension;
	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vecPositionRD3CopyMod.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the positionsvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vecPositionRD3CopyMod.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the positionsvektor*/
		//check the first vectorelement
	if ( ! vecPositionRD3CopyMod.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecPositionRD3CopyMod.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPositionRD3CopyMod.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( ! vecPositionRD3CopyMod.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecPositionRD3CopyMod.getValue( 2 ) == (doubleFib)(2) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPositionRD3CopyMod.getValue( 2 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecPositionRD3CopyMod.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPositionRD3CopyMod.getVariable( 3 ) == pVariable1 ){
	
		cout<<"The 3'th element of the positionsvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the positionsvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPositionRD3CopyMod.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &rootD3 == vecPositionRD3Copy.getDefiningFibElement() ){
	
		cout<<"The rootD3 is the defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The rootD3 is not the defining element for the positionsvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorPosition
	if ( vecPositionRD3CopyMod.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainD3 == vecPositionRD3CopyMod.getDomain() ){
	
		cout<<"The vectorDomainD3 is the domain for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainD3 is not the domain for the positionsvector."<<endl;
		iReturn++;
	}


	return iReturn;
}


/**
 * This method tests the method for the domains of the cVectorPosition class.
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
	
	cout<<"cTypeDimension testTypeDimensionD3( 3 );"<<endl;
	cTypeDimension testTypeDimensionD3( 3 );
	cout<<"testTypeDimensionD3.setDimensionMapping( 1, 4 )"<<endl;
	testTypeDimensionD3.setDimensionMapping( 1, 4 );
	cout<<"testTypeDimensionD3.setDimensionMapping( 2, 1 )"<<endl;
	testTypeDimensionD3.setDimensionMapping( 2, 1 );
	cout<<"testTypeDimensionD3.setDimensionMapping( 3, 2 )"<<endl;
	testTypeDimensionD3.setDimensionMapping( 3, 2 );
	
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
	
	cout<<"rootD3.getDomains()->addDomain( testTypeDimensionD3, &vectorDomainD3 );"<<endl;
	rootD3.getDomains()->addDomain( testTypeDimensionD3, &vectorDomainD3 );

	cout<<"cVectorPosition vecPositionRD3 = cVectorPosition( rootD3 );"<<endl;
	cVectorPosition vecPositionRD3 = cVectorPosition( rootD3 );

	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vecPositionRD3.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the positionsvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vecPositionRD3.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the getDomain() methode from cVectorPosition
	if ( vecPositionRD3.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &vectorDomainD3 == vecPositionRD3.getDomain() ){
	
		cout<<"The vectorDomainD3 is the domain for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainD3 is not the domain for the positionsvector."<<endl;
		iReturn++;
	}

	/*check the getDomain(i=1..n) method of the positionsvektor*/
	//test the getType() method
	cout<<"cDomain * pDomainD3 = vecPositionRD3.getDomain();"<<endl;
	cDomain * pDomainD3 = vecPositionRD3.getDomain();
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

	//check the getStandardDomain() method from cVectorPosition
	cDomain * pDomainStandardD3 = vecPositionRD3.getStandardDomain();
	cDomain * pTypeDomainStandardD3 = testTypeDimensionD3.getStandardDomain();
	
	if ( pDomainStandardD3 == NULL ){
		cerr<<"Error: Ther is no domain defined for the positionsvector."<<endl;
		iReturn++;	
	}else if ( *pDomainStandardD3 == *pTypeDomainStandardD3 ){
	
		cout<<"The vecPositionRD3 has the correct standard domain. "<<endl;
	}else{
		cerr<<"Error: The vecPositionRD3 has not the correct standard domain."<<endl;
		iReturn++;
	}

	delete pDomainStandardD3;
	delete pTypeDomainStandardD3;
	
	return iReturn;
}


/**
 * This method tests setDefiningFibElement() and getDefiningFibElement()
 * method of the cVectorPosition class.
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

	cout<<"cRoot definingElement1;"<<endl;
	cRoot definingElement1;
	cout<<"cRoot definingElement2;"<<endl;
	cRoot definingElement2;

	cout<<"cVectorPosition vecPosition;"<<endl;
	cVectorPosition vecPosition;

	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPosition.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the positionsvector."<<endl;
		iReturn++;
	}
	
	cout<<"vecPosition.setDefiningFibElement( &definingElement1 );"<<endl;
	vecPosition.setDefiningFibElement( &definingElement1 );

	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPosition.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &definingElement1 == vecPosition.getDefiningFibElement() ){
	
		cout<<"The definingElement1 is the defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The definingElement1 is not the defining element for the positionsvector."<<endl;
		iReturn++;
	}

	cout<<"vecPosition.setDefiningFibElement( &definingElement2 );"<<endl;
	vecPosition.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPosition.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecPosition.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the positionsvector."<<endl;
		iReturn++;
	}

	cout<<"vecPosition.setDefiningFibElement( NULL );"<<endl;
	vecPosition.setDefiningFibElement( NULL );

	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPosition.getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the positionsvector."<<endl;
		iReturn++;
	}

	cout<<"vecPosition.setDefiningFibElement( &definingElement2 );"<<endl;
	vecPosition.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vecPosition.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecPosition.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the positionsvector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods when adomain is given"<<endl;
	
	cout<<"cRoot rootD3;"<<flush<<endl;
	cRoot rootD3;
	
	cout<<"cTypeDimension testTypeDimensionD3( 3 );"<<endl;
	cTypeDimension testTypeDimensionD3( 3 );
	cout<<"testTypeDimensionD3.setDimensionMapping( 1, 4 )"<<endl;
	testTypeDimensionD3.setDimensionMapping( 1, 4 );
	cout<<"testTypeDimensionD3.setDimensionMapping( 2, 1 )"<<endl;
	testTypeDimensionD3.setDimensionMapping( 2, 1 );
	cout<<"testTypeDimensionD3.setDimensionMapping( 3, 2 )"<<endl;
	testTypeDimensionD3.setDimensionMapping( 3, 2 );
	
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

	cout<<"rootD3.getDomains()->addDomain( testTypeDimensionD3, &vectorDomainD3 );"<<endl;
	rootD3.getDomains()->addDomain( testTypeDimensionD3, &vectorDomainD3 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint pointD3( NULL, &rootD3 );"<<endl;
	cPoint pointD3( NULL, &rootD3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint pointD3( NULL, &rootD3, &rootD3 );"<<endl;
	cPoint pointD3( NULL, &rootD3, &rootD3 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	
	cout<<"cVectorPosition vecPositionE0( 0 );"<<endl;
	cVectorPosition vecPositionE0( 0 );
	
	cout<<"vecPositionE0.setDefiningFibElement( &pointD3 );"<<endl;
	vecPositionE0.setDefiningFibElement( &pointD3 );

	cout<<"cVectorPosition vecPosition2E0( 0 );"<<endl;
	cVectorPosition vecPosition2E0( 0 );

	if ( vecPositionE0 == vecPosition2E0 ){
	
		cout<<"The positionsvector vecPositionE0 is equal to vecPosition2E0. "<<endl;
	}else{
		cerr<<"Error: The positionsvector vecPositionE0 is not equal to vecPosition2E0."<<endl;
		iReturn++;
	}

	cout<<"cVectorPosition vecPosition1E3( 3 );"<<endl;
	cVectorPosition vecPosition1E3( 3 );
	cout<<"vecPosition1E3.setValue( 1, 1);"<<endl;
	vecPosition1E3.setValue( 1, 1);
	cout<<"vecPosition1E3.setValue( 2, 2);"<<endl;
	vecPosition1E3.setValue( 2, 2);

	cout<<"cVectorPosition vecPosition1E2( 2 );"<<endl;
	cVectorPosition vecPosition1E2( 2 );
	cout<<"vecPosition1E2.setValue( 1, 3);"<<endl;
	vecPosition1E2.setValue( 1, 3);
	cout<<"vecPosition1E2.setValue( 2, 2);"<<endl;
	vecPosition1E2.setValue( 2, 2);

	cout<<"vecPosition1E2.setDefiningFibElement( &pointD3 );"<<endl;
	vecPosition1E2.setDefiningFibElement( &pointD3 );

	if ( vecPosition1E2 == vecPosition1E3 ){
	
		cout<<"The positionsvector vecPosition1E2 is equal to vecPosition1E3. "<<endl;
	}else{
		cerr<<"Error: The positionsvector vecPosition1E2 is not equal to vecPosition1E3."<<endl;
		/*check the elements of the positionsvektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecPosition1E2.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecPosition1E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecPosition1E2.getValue( uiActualElement ) ==
					vecPosition1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is correctly "<< 
					vecPosition1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is "<<vecPosition1E2.getValue( uiActualElement )<<
					" and not "<< vecPosition1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}


	cout<<"vecPosition1E3.setValue( 1, 0);"<<endl;
	vecPosition1E3.setValue( 1, 0);
	cout<<"vecPosition1E3.setValue( 2, 1);"<<endl;
	vecPosition1E3.setValue( 2, 1);

	cout<<"cVectorPosition vecPosition2E3( vecPosition1E3 );"<<endl;
	cVectorPosition vecPosition2E3( vecPosition1E3 );

	cout<<"vecPosition2E3.setDefiningFibElement( &pointD3 );"<<endl;
	vecPosition2E3.setDefiningFibElement( &pointD3 );


	if ( vecPosition2E3 == vecPosition1E3 ){
	
		cout<<"The positionsvector vecPosition2E3 is equal to vecPosition1E3. "<<endl;
	}else{
		cerr<<"Error: The positionsvector vecPosition2E3 is not equal to vecPosition1E3."<<endl;
		/*check the elements of the positionsvektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecPosition2E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecPosition2E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecPosition2E3.getValue( uiActualElement ) ==
					vecPosition1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is correctly "<< 
					vecPosition1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is "<<vecPosition2E3.getValue( uiActualElement )<<
					" and not "<< vecPosition1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	cout<<"vecPosition1E3.setValue( 1, 0);"<<endl;
	vecPosition1E3.setValue( 1, 0);
	cout<<"vecPosition1E3.setValue( 2, 3);"<<endl;
	vecPosition1E3.setValue( 2, 3);
	cout<<"vecPosition1E3.setValue( 3, 7);"<<endl;
	vecPosition1E3.setValue( 3, 7);

	cout<<"cVectorPosition vecPosition3E3( 3 );"<<endl;
	cVectorPosition vecPosition3E3( 3 );
	cout<<"vecPosition3E3.setValue( 1, -7 );"<<endl;
	vecPosition3E3.setValue( 1, -7 );
	cout<<"vecPosition3E3.setValue( 2, 4 );"<<endl;
	vecPosition3E3.setValue( 2, 4 );
	cout<<"vecPosition3E3.setValue( 3, 8 );"<<endl;
	vecPosition3E3.setValue( 3, 8 );

	cout<<"vecPosition3E3.setDefiningFibElement( &pointD3 );"<<endl;
	vecPosition3E3.setDefiningFibElement( &pointD3 );

	if ( vecPosition3E3 == vecPosition1E3 ){
	
		cout<<"The positionsvector vecPosition3E3 is equal to vecPosition1E3. "<<endl;
	}else{
		cerr<<"Error: The positionsvector vecPosition3E3 is not equal to vecPosition1E3."<<endl;
		/*check the elements of the positionsvektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecPosition3E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecPosition3E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecPosition3E3.getValue( uiActualElement ) ==
					vecPosition1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is correctly "<< 
					vecPosition1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is "<<vecPosition3E3.getValue( uiActualElement )<<
					" and not "<< vecPosition1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods when adomain is given but shouldn't be checked"<<endl;
	
	cout<<"cVectorPosition vecPosition2E2( 2 );"<<endl;
	cVectorPosition vecPosition2E2( 2 );
	cout<<"vecPosition2E2.setValue( 1, 3);"<<endl;
	vecPosition2E2.setValue( 1, 3);
	cout<<"vecPosition2E2.setValue( 2, 2);"<<endl;
	vecPosition2E2.setValue( 2, 2);
	
	cVectorPosition vecPosition3E2( vecPosition2E2 );

	cout<<"vecPosition3E2.setDefiningFibElement( &pointD3, false );"<<endl;
	vecPosition3E2.setDefiningFibElement( &pointD3, false );

	if ( vecPosition3E2 == vecPosition2E2 ){
	
		cout<<"The positionsvector vecPosition3E2 is equal to vecPosition2E2. "<<endl;
	}else{
		cerr<<"Error: The positionsvector vecPosition3E2 is not equal to vecPosition2E2."<<endl;
		/*check the elements of the positionsvektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecPosition3E2.getNumberOfElements() &&
				uiActualElement <= 2;
				uiActualElement++ ){
			
			if ( ! vecPosition3E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecPosition3E2.getValue( uiActualElement ) ==
					vecPosition2E2.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is correctly "<< 
					vecPosition3E2.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is "<<vecPosition3E2.getValue( uiActualElement )<<
					" and not "<< vecPosition2E2.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	cout<<"cVectorPosition vecPosition4E3( 3 );"<<endl;
	cVectorPosition vecPosition4E3( 3 );
	cout<<"vecPosition4E3.setValue( 1, -7 );"<<endl;
	vecPosition4E3.setValue( 1, -7 );
	cout<<"vecPosition4E3.setValue( 2, 4 );"<<endl;
	vecPosition4E3.setValue( 2, 4 );
	cout<<"vecPosition4E3.setValue( 3, 8 );"<<endl;
	vecPosition4E3.setValue( 3, 8 );
	
	cVectorPosition vecPosition5E3( vecPosition4E3 );

	cout<<"vecPosition5E3.setDefiningFibElement( &pointD3, false );"<<endl;
	vecPosition5E3.setDefiningFibElement( &pointD3, false );

	if ( vecPosition5E3 == vecPosition4E3 ){
	
		cout<<"The positionsvector vecPosition5E3 is equal to vecPosition4E3. "<<endl;
	}else{
		cerr<<"Error: The positionsvector vecPosition5E3 is not equal to vecPosition4E3."<<endl;
		/*check the elements of the positionsvektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecPosition5E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecPosition5E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecPosition5E3.getValue( uiActualElement ) ==
					vecPosition4E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is correctly "<< 
					vecPosition4E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"positionsvector is "<<vecPosition5E3.getValue( uiActualElement )<<
					" and not "<< vecPosition4E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests cVectorPosition methods for manipulating the
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
	
	cout<<"cVectorPosition vecPosition( emptyRoot );"<<endl;
	cVectorPosition vecPosition( emptyRoot );


	/*check the elements of the positionsvektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecPosition.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecPosition.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecPosition.getValue( uiActualElement ) == (doubleFib)(0.0) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is "<<vecPosition.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
		if ( vecPosition.getVariable( uiActualElement ) == NULL ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly no variable . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is an variable . "<<endl;
			iReturn++;
		}
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setValue() method"<<endl;

	cout<<"vecPosition.setValue( 2, 2.2 )"<<endl;
	if ( vecPosition.setValue( 2, 2.2 ) ){
	
		cout<<"The 2'th element of the positionsvector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecPosition.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPosition.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the positionsvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is an variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecPosition.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 2 ) == (doubleFib)(2.2) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 2.2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPosition.getValue( 2 )<<" and not 2.2 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the positionsvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is an variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecPosition.setValue( 2, 0.7 )"<<endl;
	if ( vecPosition.setValue( 2, 0.7 ) ){
	
		cout<<"The 2'th element of the positionsvector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecPosition.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPosition.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the positionsvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is an variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecPosition.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPosition.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the positionsvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is an variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecPosition.setValue( 1, 11 )"<<endl;
	if ( vecPosition.setValue( 1, 11 ) ){
	
		cout<<"The 1'th element of the positionsvector is set. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecPosition.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 1 ) == (doubleFib)(11) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPosition.getValue( 1 )<<" and not 11 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the positionsvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is an variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecPosition.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPosition.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the positionsvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is an variable . "<<endl;
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
	cout<<endl<<"vecPosition.setVariable( 1, pVariable1 )"<<endl;
	if ( vecPosition.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the positionsvector is set to the variable 1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not set to the variable 1. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecPosition.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 1 ) == (doubleFib)(0) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPosition.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the positionsvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecPosition.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPosition.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the positionsvector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is an variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable1->setValue( 0.11 );"<<endl;
	pVariable1->setValue( 0.11 );
	
	if ( vecPosition.getValue( 1 ) == (doubleFib)(0.11) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 0.11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPosition.getValue( 1 )<<" and not 0.11 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable1->setValue( 111 );"<<endl;
	pVariable1->setValue( 111 );
	
	if ( vecPosition.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPosition.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4 = emptyRoot.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable4 = emptyRoot.getInputVariable( 4 );
	cout<<endl<<"vecPosition.setVariable( 2, pVariable4 )"<<endl;
	if ( vecPosition.setVariable( 2, pVariable4 ) ){
	
		cout<<"The 2'th element of the positionsvector is set to the variable 4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not set to the variable 4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecPosition.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPosition.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the positionsvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecPosition.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 2 ) == (doubleFib)(0.0) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPosition.getValue( 2 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the positionsvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 123 );"<<endl;
	pVariable4->setValue( 123 );
	
	if ( vecPosition.getValue( 2 ) == (doubleFib)(123) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 123 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPosition.getValue( 2 )<<" and not 123 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 0.321 );"<<endl;
	pVariable4->setValue( 0.321  );
	
	if ( vecPosition.getValue( 2 ) == (doubleFib)(0.321 ) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 0.321  . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPosition.getValue( 2 )<<" and not 0.321  . "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecPosition.setVariable( 1, pVariable4 )"<<endl;
	if ( vecPosition.setVariable( 1, pVariable4 ) ){
	
		cout<<"The 1'th element of the positionsvector is set to the variable 4. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not set to the variable 4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecPosition.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 1 ) == (doubleFib)(0.321) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 0.321 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPosition.getValue( 1 )<<" and not 0.321 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 1 ) == pVariable4 ){
	
		cout<<"The 1'th element of the positionsvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecPosition.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 2 ) == (doubleFib)(0.321) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 0.321 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPosition.getValue( 2 )<<" and not 0.321 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the positionsvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 654.123 );"<<endl;
	pVariable4->setValue( 654.123 );
	
	if ( vecPosition.getValue( 1 ) == (doubleFib)(654.123) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 654.123 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPosition.getValue( 1 )<<" and not 654.123 . "<<endl;
		iReturn++;
	}
	
	if ( vecPosition.getValue( 2 ) == (doubleFib)(654.123) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 654.123 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPosition.getValue( 2 )<<" and not 654.123 . "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setValue() and setVariable() after each other method"<<endl;
	
	cout<<endl<<"vecPosition.setValue( 1, 17 )"<<endl;
	if ( vecPosition.setValue( 1, 17 ) ){
	
		cout<<"The 1'th element of the positionsvector is set to the value 17"<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not set to the value 17. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecPosition.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 1 ) == (doubleFib)(17) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 17 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPosition.getValue( 1 )<<" and not 17 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the positionsvector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is an variable. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecPosition.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 2 ) == (doubleFib)(654.123 ) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 654.123  . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPosition.getValue( 2 )<<" and not 654.123  . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the positionsvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 65 );"<<endl;
	pVariable4->setValue( 65 );
	
	if ( vecPosition.getValue( 2 ) == (doubleFib)(65) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPosition.getValue( 2 )<<" and not 65 . "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecPosition.setVariable( 1, pVariable1 )"<<endl;
	if ( vecPosition.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the positionsvector is set to the varaiable 1"<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not set to the variable 1. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecPosition.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPosition.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the positionsvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecPosition.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 2 ) == (doubleFib)(65 ) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPosition.getValue( 2 )<<" and not 65  . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the positionsvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setVariable() methods with trying to set NULL"<<endl;
	
	cout<<endl<<"vecPosition.setVariable( 1, NULL )"<<endl;
	if ( ! vecPosition.setVariable( 1, NULL ) ){
	
		cout<<"The 1'th element of the positionsvector couldn't be set to NULL."<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector could be set to NULL. "<<endl;
		iReturn++;
	}
	cout<<endl<<"vecPosition.setVariable( 2, NULL )"<<endl;
	if ( ! vecPosition.setVariable( 2, NULL ) ){
	
		cout<<"The 2'th element of the positionsvector couldn't be set to NULL."<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector could be set to NULL. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecPosition.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"positionsvector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is "<<
			vecPosition.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the positionsvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the positionsvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecPosition.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the positionsvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getValue( 2 ) == (doubleFib)(65 ) ){
	
		cout<<"The 2'th element of the "<<
			"positionsvector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is "<<
			vecPosition.getValue( 2 )<<" and not 65  . "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the positionsvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the positionsvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing replaceVariable(), isUsedVariable() and set<cFibVariable*> getUsedVariables() methods"<<endl;
	
	cout<<endl<<"pVariable2 = emptyRoot.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = emptyRoot.getInputVariable( 2 );
	cout<<endl<<"pVariable3 = emptyRoot.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = emptyRoot.getInputVariable( 3 );
	
	//check vecPosition.isUsedVariable()
	if ( vecPosition.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecPosition.isUsedVariable()
	if ( ! vecPosition.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check isUsedVariable()
	if ( vecPosition.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	
	set<cFibVariable*> setCorrectUsedVariables;
	setCorrectUsedVariables.insert( pVariable1 );
	setCorrectUsedVariables.insert( pVariable4 );
	//check getUsedVariables()
	cout<<"setUsedVariables = vecPosition.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = vecPosition.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	
	cout<<endl<<"vecPosition.replaceVariable( pVariable1, pVariable4 )"<<endl;
	setCorrectUsedVariables.erase( pVariable1 );
	if ( vecPosition.replaceVariable( pVariable1, pVariable4 ) ){
	
		cout<<"The pVariable1 of the propertyvector was replaced with pVariable4. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 of the propertyvector was not replaced with pVariable4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecPosition.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 1 ) == pVariable4 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecPosition.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check vecPosition.isUsedVariable()
	if ( ! vecPosition.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecPosition.isUsedVariable()
	if ( ! vecPosition.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecPosition.isUsedVariable()
	if ( vecPosition.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecPosition.getUsedVariables(); "<<endl;
	setUsedVariables = vecPosition.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecPosition.replaceVariable( pVariable1, pVariable3 )"<<endl;
	if ( vecPosition.replaceVariable( pVariable1, pVariable3 ) ){
	
		cout<<"The pVariable1 of the propertyvector was replaced with pVariable3. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 of the propertyvector was not replaced with pVariable3. "<<endl;
		iReturn++;
	}
	//check vecPosition.isUsedVariable()
	if ( ! vecPosition.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecPosition.isUsedVariable()
	if ( vecPosition.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecPosition.getUsedVariables(); "<<endl;
	setUsedVariables = vecPosition.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	cout<<endl<<"vecPosition.replaceVariable( pVariable4, pVariable2 )"<<endl;
	setCorrectUsedVariables.erase( pVariable4 );
	setCorrectUsedVariables.insert( pVariable2 );
	if ( vecPosition.replaceVariable( pVariable4, pVariable2 ) ){
	
		cout<<"The pVariable4 of the propertyvector was replaced with pVariable2. "<<endl;
	}else{
		cerr<<"Error: The pVariable4 of the propertyvector was not replaced with pVariable2. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecPosition.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 1 ) == pVariable2 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecPosition.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecPosition.getVariable( 2 ) == pVariable2 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check vecPosition.isUsedVariable()
	if ( ! vecPosition.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecPosition.isUsedVariable()
	if ( vecPosition.isUsedVariable( pVariable2 ) ){
	
		cout<<"The pVariable2 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable2 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecPosition.isUsedVariable()
	if ( ! vecPosition.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecPosition.isUsedVariable()
	if ( ! vecPosition.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable4 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecPosition.getUsedVariables(); "<<endl;
	setUsedVariables = vecPosition.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	//check vecPosition.isUsedVariable()
	if ( ! vecPosition.isUsedVariable( NULL ) ){
	
		cout<<"The NULL is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The NULL is a used varible in the vector.  "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecPosition.replaceVariable( NULL, pVariable2 )"<<endl;
	if ( ! vecPosition.replaceVariable( NULL, pVariable2 ) ){
	
		cout<<"Can't correctly replace NULL of the propertyvector with pVariable2. "<<endl;
	}else{
		cerr<<"Error: Can replace NULL of the propertyvector with pVariable2. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecPosition.replaceVariable( pVariable2, NULL )"<<endl;
	if ( ! vecPosition.replaceVariable( pVariable2, NULL ) ){
	
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

	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeDimension testTypeDimensionD2( 2 );"<<endl;
	cTypeDimension testTypeDimensionD2( 2 );
	cout<<"testTypeDimensionD2.setDimensionMapping( 1, 4 )"<<endl;
	testTypeDimensionD2.setDimensionMapping( 1, 4 );
	cout<<"testTypeDimensionD2.setDimensionMapping( 2, 3 )"<<endl;
	testTypeDimensionD2.setDimensionMapping( 2, 3 );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomains2( 2 );"<<endl;
	vector<cDomainSingle*> vecDomains2( 2 );
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomainD2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainD2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];

	cout<<"rootD2.getDomains()->addDomain( testTypeDimensionD2, vectorDomainD2);"<<endl;
	rootD2.getDomains()->addDomain( testTypeDimensionD2, vectorDomainD2);

	//creat defined variables to set them later in the vector
	cout<<"rootD2.setNumberOfInputVariables( 4 )"<<endl;
	rootD2.setNumberOfInputVariables( 4 );

	//create cVectorPositions to compare
	cout<<"cVectorPosition vectorPositionD3( 3 );"<<endl;
	cVectorPosition vectorPositionD3( 3 );
	cout<<"cVectorPosition vectorPositionD3RD2( 3, &rootD2 );"<<endl;
	cVectorPosition vectorPositionD3RD2( 3, &rootD2 );
	cout<<"cVectorPosition vectorPositionD2Re( emptyRoot );"<<endl;
	cVectorPosition vectorPositionD2Re( emptyRoot );
	cout<<"cVectorPosition vectorPositionD2RD2( 2, &rootD2 );"<<endl;
	cVectorPosition vectorPositionD2RD2( 2, &rootD2 );
	cout<<"cVectorPosition vectorPositionRD2( rootD2 );"<<endl;
	cVectorPosition vectorPositionRD2( rootD2 );
	
	//vectors with changed values
	cout<<"cVectorPosition vectorPositionRD2V2g17p2( rootD2 );"<<endl;
	cVectorPosition vectorPositionRD2V2g17p2( rootD2 );
	vectorPositionRD2V2g17p2.setValue( 2, 17.2 );
	
	cout<<"cVectorPosition vectorPositionD2RD2V2g17p2( 2, &rootD2 );"<<endl;
	cVectorPosition vectorPositionD2RD2V2g17p2( 2, &rootD2 );
	vectorPositionD2RD2V2g17p2.setValue( 2, 17.2 );

	cout<<"cVectorPosition vectorPositionD2RD2V2g17p2001( 2, &rootD2 );"<<endl;
	cVectorPosition vectorPositionD2RD2V2g17p2001( 2, &rootD2 );
	vectorPositionD2RD2V2g17p2001.setValue( 2, 17.2001 );

	cout<<"cVectorPosition vectorPositionRD2V1g17p2( rootD2 );"<<endl;
	cVectorPosition vectorPositionRD2V1g17p2( rootD2 );
	vectorPositionRD2V1g17p2.setValue( 1, 17.2 );

	cout<<"cVectorPosition vectorPositionRD2V1g1p1V2gm2p2( rootD2 );"<<endl;
	cVectorPosition vectorPositionRD2V1g1p1V2gm2p2( rootD2 );
	vectorPositionRD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorPositionRD2V1g1p1V2gm2p2.setValue( 2, -2.2 );

	cout<<"cVectorPosition vectorPositionD2RD2V1g1p1V2gm2p2( 2, &rootD2 );"<<endl;
	cVectorPosition vectorPositionD2RD2V1g1p1V2gm2p2( 2, &rootD2 );
	vectorPositionD2RD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorPositionD2RD2V1g1p1V2gm2p2.setValue( 2, -2.2 );
	
	cout<<"cVectorPosition vectorPositionRD2V1g1p1V2g2p2( rootD2 );"<<endl;
	cVectorPosition vectorPositionRD2V1g1p1V2g2p2( rootD2 );
	vectorPositionRD2V1g1p1V2g2p2.setValue( 1, 1.1 );
	vectorPositionRD2V1g1p1V2g2p2.setValue( 2, 2.2 );

	//vectors with variables
	cFibVariable * pVariable1 = rootD2.getInputVariable( 1 );
	cFibVariable * pVariable2 = rootD2.getInputVariable( 2 );
	cFibVariable * pVariable1Re = emptyRoot.getInputVariable( 1 );

	cout<<"cVectorPosition vectorPositionRD2V1gV1( rootD2 );"<<endl;
	cVectorPosition vectorPositionRD2V1gV1( rootD2 );
	vectorPositionRD2V1gV1.setVariable( 1, pVariable1 );

	cout<<"cVectorPosition vectorPositionD2RD2V1gV1( 2, &rootD2 );"<<endl;
	cVectorPosition vectorPositionD2RD2V1gV1( 2, &rootD2 );
	vectorPositionD2RD2V1gV1.setVariable( 1, pVariable1 );

	cout<<"cVectorPosition vectorPositionRD2V2gV1( rootD2 );"<<endl;
	cVectorPosition vectorPositionRD2V2gV1( rootD2 );
	vectorPositionRD2V2gV1.setVariable( 2, pVariable1 );

	cout<<"cVectorPosition vectorPositionRD2V2gV2( rootD2 );"<<endl;
	cVectorPosition vectorPositionRD2V2gV2( rootD2 );
	vectorPositionRD2V2gV2.setVariable( 2, pVariable2 );

	cout<<"cVectorPosition vectorPositionRD2V1gReV1( rootD2 );"<<endl;
	cVectorPosition vectorPositionRD2V1gReV1( rootD2 );
	vectorPositionRD2V1gReV1.setVariable( 1, pVariable1Re );

//TODO check variable from different defining element


	//vectors with changed values and variables
	cout<<"cVectorPosition vectorPositionRD2V1gV1V2g1111( rootD2 );"<<endl;
	cVectorPosition vectorPositionRD2V1gV1V2g1111( rootD2 );
	vectorPositionRD2V1gV1V2g1111.setVariable( 1, pVariable1 );
	vectorPositionRD2V1gV1V2g1111.setValue( 2, 1111 );

	cout<<"cVectorPosition vectorPositionD2RD2V1gV1V2g1111( 2, &rootD2 );"<<endl;
	cVectorPosition vectorPositionD2RD2V1gV1V2g1111( 2, &rootD2 );
	vectorPositionD2RD2V1gV1V2g1111.setVariable( 1, pVariable1 );
	vectorPositionD2RD2V1gV1V2g1111.setValue( 2, 1111 );

	cout<<"cVectorPosition vectorPositionRD2V1gV1V2g111( rootD2 );"<<endl;
	cVectorPosition vectorPositionRD2V1gV1V2g111( rootD2 );
	vectorPositionRD2V1gV1V2g111.setVariable( 1, pVariable1 );
	vectorPositionRD2V1gV1V2g111.setValue( 2, 111 );

	cout<<"cVectorPosition vectorPositionRD2V1gV2V1g1111( rootD2 );"<<endl;
	cVectorPosition vectorPositionRD2V1g111V2gV2( 2, &rootD2 );
	vectorPositionRD2V1g111V2gV2.setVariable( 1, pVariable2 );
	vectorPositionRD2V1g111V2gV2.setValue( 2, 1111 );

	cout<<"cVectorPosition vectorPositionD2RD2V1g1111V2gV2( rootD2 );"<<endl;
	cVectorPosition vectorPositionD2RD2V1gV2V2g1111( rootD2 );
	vectorPositionD2RD2V1gV2V2g1111.setValue( 1, 1111 );
	vectorPositionD2RD2V1gV2V2g1111.setVariable( 2, pVariable1 );

	cout<<"cVectorPosition vectorPositionD2RD2V1gV1V2gV2( 2, &rootD2 );"<<endl;
	cVectorPosition vectorPositionD2RD2V1gV1V2gV2( 2, &rootD2 );
	vectorPositionD2RD2V1gV1V2gV2.setVariable( 1, pVariable1 );
	vectorPositionD2RD2V1gV1V2gV2.setVariable( 2, pVariable2 );

	cout<<"cVectorProperty vectorProperty( 1 );"<<endl;
	cVectorProperty vectorProperty( 1 );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with vectorPositionD3
	cFibVector * actualVector = &vectorPositionD3;
	string szActualVectorName = "vectorPositionD3";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionD3RD2
	actualVector = &vectorPositionD3RD2;
	szActualVectorName = "vectorPositionD3RD2";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionD2Re
	actualVector = &vectorPositionD2Re;
	szActualVectorName = "vectorPositionD2Re";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionD2RD2
	actualVector = &vectorPositionD2RD2;
	szActualVectorName = "vectorPositionD2RD2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );
	
	//compare with vectorPositionD2Re
	actualVector = &vectorPositionRD2;
	szActualVectorName = "vectorPositionRD2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionRD2V2g17p2
	actualVector = &vectorPositionRD2V2g17p2;
	szActualVectorName = "vectorPositionRD2V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionRD2V2g17p2
	actualVector = &vectorPositionD2RD2V2g17p2;
	szActualVectorName = "vectorPositionD2RD2V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionD2RD2V2g17p2001
	actualVector = &vectorPositionD2RD2V2g17p2001;
	szActualVectorName = "vectorPositionD2RD2V2g17p2001";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionD2RD2V2g17p2001
	actualVector = &vectorPositionRD2V1g17p2;
	szActualVectorName = "vectorPositionRD2V1g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionRD2V1g1p1V2gm2p2
	actualVector = &vectorPositionRD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorPositionRD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionD2RD2V1g1p1V2gm2p2
	actualVector = &vectorPositionD2RD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorPositionD2RD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionD2RD2V1g1p1V2gm2p2
	actualVector = &vectorPositionRD2V1g1p1V2g2p2;
	szActualVectorName = "vectorPositionRD2V1g1p1V2g2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionRD2V1gV1
	actualVector = &vectorPositionRD2V1gV1;
	szActualVectorName = "vectorPositionRD2V1gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionD2RD2V1gV1
	actualVector = &vectorPositionD2RD2V1gV1;
	szActualVectorName = "vectorPositionD2RD2V1gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionRD2V2gV1
	actualVector = &vectorPositionRD2V2gV1;
	szActualVectorName = "vectorPositionRD2V2gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionRD2V2gV2
	actualVector = &vectorPositionRD2V2gV2;
	szActualVectorName = "vectorPositionRD2V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionRD2V1gReV1
	actualVector = &vectorPositionRD2V1gReV1;
	szActualVectorName = "vectorPositionRD2V1gReV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionRD2V1gV1V2g1111
	actualVector = &vectorPositionRD2V1gV1V2g1111;
	szActualVectorName = "vectorPositionRD2V1gV1V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionD2RD2V1gV1V2g1111
	actualVector = &vectorPositionD2RD2V1gV1V2g1111;
	szActualVectorName = "vectorPositionD2RD2V1gV1V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionRD2V1gV1V2g111
	actualVector = &vectorPositionRD2V1gV1V2g111;
	szActualVectorName = "vectorPositionRD2V1gV1V2g111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionRD2V1g111V2gV2
	actualVector = &vectorPositionRD2V1g111V2gV2;
	szActualVectorName = "vectorPositionRD2V1g111V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionD2RD2V1gV2V2g1111
	actualVector = &vectorPositionD2RD2V1gV2V2g1111;
	szActualVectorName = "vectorPositionD2RD2V1gV2V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorPositionD2RD2V1gV1V2gV2
	actualVector = &vectorPositionD2RD2V1gV1V2gV2;
	szActualVectorName = "vectorPositionD2RD2V1gV1V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorProperty
	actualVector = &vectorProperty;
	szActualVectorName = "vectorProperty";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3, "vectorPositionD3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD3RD2, "vectorPositionD3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2Re, "vectorPositionD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2, "vectorPositionD2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2, "vectorPositionRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2g17p2, "vectorPositionRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2, "vectorPositionD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V2g17p2001, "vectorPositionD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g17p2, "vectorPositionRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2gm2p2, "vectorPositionRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1g1p1V2gm2p2, "vectorPositionD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g1p1V2g2p2, "vectorPositionRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1, "vectorPositionRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1, "vectorPositionD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV1, "vectorPositionRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V2gV2, "vectorPositionRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gReV1, "vectorPositionRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g1111, "vectorPositionRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2g1111, "vectorPositionD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1gV1V2g111, "vectorPositionRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionRD2V1g111V2gV2, "vectorPositionRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV2V2g1111, "vectorPositionD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorPositionD2RD2V1gV1V2gV2, "vectorPositionD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	return iReturn;
}


/**
 * This method tests the createInstance() method of the cVectorPosition class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 1 element"<<endl;

	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeDimension typeDimensionD1( 1 );"<<endl;
	cTypeDimension typeDimensionD1( 1 );
	
	cout<<"cTypeDimension testTypeDimensionD2( 2 );"<<endl;
	cTypeDimension testTypeDimensionD2( 2 );
	cout<<"testTypeDimensionD2.setDimensionMapping( 1, 4 )"<<endl;
	testTypeDimensionD2.setDimensionMapping( 1, 4 );
	cout<<"testTypeDimensionD2.setDimensionMapping( 2, 3 )"<<endl;
	testTypeDimensionD2.setDimensionMapping( 2, 3 );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomains2( 2 );"<<endl;
	vector<cDomainSingle*> vecDomains2( 2 );
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomainD2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainD2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];

	cout<<"rootD2.getDomains()->addDomain( testTypeDimensionD2, vectorDomainD2);"<<endl;
	rootD2.getDomains()->addDomain( testTypeDimensionD2, vectorDomainD2);

	
	cout<<"cVectorPosition vecPositionD4RD2 = cVectorPosition( 4, &rootD2 );"<<endl;
	cVectorPosition vecPositionD4RD2 = cVectorPosition( 4, &rootD2 );

	cout<<"cFibVector * vectorInstanceD1 = vecPositionD4RD2.createInstance( 1 );"<<endl;
	cFibVector * vectorInstanceD1 = vecPositionD4RD2.createInstance( 1 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorPosition
	if ( vectorInstanceD1->getVectorType() == "position" ){
	
		cout<<"The name of the positionsvector is correctly \"position\" . "<<endl;
	}else{
		cerr<<"Error: The name of the positionsvector is "<<
			vectorInstanceD1->getVectorType()<<" but should be \"position\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorPosition
	cTypeElement * pTypeDimension = vectorInstanceD1->getElementType();
	if ( typeDimensionD1 == (*pTypeDimension) ){
	
		cout<<"The type of the positionsvector is correctly equal to typeDimensionD2. "<<endl;
	}else{
		cerr<<"Error: The type of positionsvector not equal to typeDimensionD2 ."<<endl;
		iReturn++;
	}
	delete pTypeDimension;
	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vectorInstanceD1->getNumberOfElements() == (unsignedIntFib)(1) ){
	
		cout<<"The number of elements of the positionsvector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vectorInstanceD1->getNumberOfElements()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the positionsvektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD1->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD1->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD1->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is "<<vectorInstanceD1->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vectorInstanceD1->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the positionsvector."<<endl;
	}else if ( &rootD2 == vectorInstanceD1->getDefiningFibElement() ){
	
		cerr<<"Error: The rootD2 is the defining element for the positionsvector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is a defining element for the positionsvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorPosition
	if ( vectorInstanceD1->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the positionsvector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the positionsvector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 3 elements"<<endl;

	cout<<"cTypeDimension typeDimensionD3( 3 );"<<endl;
	cTypeDimension typeDimensionD3( 3 );

	cout<<"cFibVector * vectorInstanceD3 = vecPositionD4RD2.createInstance( 3 );"<<endl;
	cFibVector * vectorInstanceD3 = vecPositionD4RD2.createInstance( 3 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorPosition
	if ( vectorInstanceD3->getVectorType() == "position" ){
	
		cout<<"The name of the positionsvector is correctly \"position\" . "<<endl;
	}else{
		cerr<<"Error: The name of the positionsvector is "<<
			vectorInstanceD3->getVectorType()<<" but should be \"position\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorPosition
	pTypeDimension = vectorInstanceD3->getElementType();
	if ( typeDimensionD3 == (*pTypeDimension) ){
	
		cout<<"The type of the positionsvector is correctly equal to typeDimensionD3. "<<endl;
	}else{
		cerr<<"Error: The type of positionsvector not equal to typeDimensionD3 ."<<endl;
		iReturn++;
	}
	delete pTypeDimension;
	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vectorInstanceD3->getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the positionsvector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vectorInstanceD3->getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the positionsvektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD3->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD3->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD3->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is "<<vectorInstanceD3->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vectorInstanceD3->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the positionsvector."<<endl;
	}else if ( &rootD2 == vectorInstanceD3->getDefiningFibElement() ){
	
		cerr<<"Error: The rootD2 is the defining element for the positionsvector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is an defining element for the positionsvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorPosition
	if ( vectorInstanceD3->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the positionsvector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the positionsvector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD3;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 2 elements and rootD3 as an defining element"<<endl;

	cout<<"cTypeDimension typeDimensionD2( 2 );"<<endl;
	cTypeDimension typeDimensionD2( 2 );

	cout<<"cFibVector * vectorInstanceD2RD2 = vecPositionD4RD2.createInstance( 2, &rootD2 );"<<endl;
	cFibVector * vectorInstanceD2RD2 = vecPositionD4RD2.createInstance( 2, &rootD2 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorPosition
	if ( vectorInstanceD2RD2->getVectorType() == "position" ){
	
		cout<<"The name of the positionsvector is correctly \"position\" . "<<endl;
	}else{
		cerr<<"Error: The name of the positionsvector is "<<
			vectorInstanceD2RD2->getVectorType()<<" but should be \"position\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorPosition
	pTypeDimension = vectorInstanceD2RD2->getElementType();
	if ( testTypeDimensionD2 == (*pTypeDimension) ){
	
		cout<<"The type of the positionsvector is correctly equal to testTypeDimensionD2. "<<endl;
	}else{
		cerr<<"Error: The type of positionsvector not equal to testTypeDimensionD2 ."<<endl;
		iReturn++;
	}
	delete pTypeDimension;
	
	//check the getNumberOfElements() methode from cVectorPosition
	if ( vectorInstanceD2RD2->getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the positionsvector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the positionsvector is "<<
			vectorInstanceD2RD2->getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the positionsvektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD2RD2->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD2RD2->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is an variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD2RD2->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"positionsvector is "<<vectorInstanceD2RD2->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorPosition
	if ( vectorInstanceD2RD2->getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the positionsvector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vectorInstanceD2RD2->getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the positionsvector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorPosition
	if ( vectorInstanceD2RD2->getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the positionsvector."<<endl;
		iReturn++;	
	}else if ( vectorDomainD2 == (*(vectorInstanceD2RD2->getDomain())) ){
	
		cout<<"The vectorDomainD2 is the domain for the positionsvector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainD2 is not the domain for the positionsvector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD2RD2;

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
 * This method tests the storeXml() method of the cVectorPosition class.
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
	
	cout<<"cTypeDimension testTypeDimensionD3( 3 );"<<endl;
	cTypeDimension testTypeDimensionD3( 3 );
	cout<<"testTypeDimensionD3.setDimensionMapping( 1, 4 )"<<endl;
	testTypeDimensionD3.setDimensionMapping( 1, 4 );
	cout<<"testTypeDimensionD3.setDimensionMapping( 2, 1 )"<<endl;
	testTypeDimensionD3.setDimensionMapping( 2, 1 );
	cout<<"testTypeDimensionD3.setDimensionMapping( 3, 2 )"<<endl;
	testTypeDimensionD3.setDimensionMapping( 3, 2 );
	
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
	
	cout<<"rootD3.getDomains()->addDomain( testTypeDimensionD3, &vectorDomainD3 );"<<endl;
	rootD3.getDomains()->addDomain( testTypeDimensionD3, &vectorDomainD3 );

	//creat defined variables to set them later in the vector
	cout<<"rootD3.setNumberOfInputVariables( 6 )"<<endl;
	rootD3.setNumberOfInputVariables( 6 );

	cout<<"cVectorPosition vecPositionRD3 = cVectorPosition( rootD3 );"<<endl;
	cVectorPosition vecPositionRD3 = cVectorPosition( rootD3 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	const char * szVectorPostion = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorPositionEmpty.xml" );
	ofstream fileVectorPostion( szVectorPostion );
	
	bool bStoreSuccesfull = vecPositionRD3.storeXml( fileVectorPostion );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorPostion <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorPostion <<"\" failed."<<endl;
		iReturn++;
	}
	
	vector<char> vecElementTypePosition( 5, 'w' );
	vector<double> vecValuesPosition( 5, 0.0 );
	
	iReturn += testXmlVector( szVectorPostion, "position",
		3, vecElementTypePosition, vecValuesPosition );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector one value set"<<endl;
	
	cout<<"vecPositionRD3.setValue( 1, 111 )"<<endl;
	vecPositionRD3.setValue( 1, 111 );
	vecElementTypePosition[0] = 'w';
	vecValuesPosition[0] = 111;
	
	szFileNameBuffer[0] = 0;
	const char * szVectorPositionRD3V1g111 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorPositionRD3V1g111.xml" );
	ofstream fileVectorPostioRD3V1g111n( szVectorPositionRD3V1g111 );
	
	bStoreSuccesfull = vecPositionRD3.storeXml( fileVectorPostioRD3V1g111n );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorPositionRD3V1g111 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorPositionRD3V1g111 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorPositionRD3V1g111, "position",
		3, vecElementTypePosition, vecValuesPosition );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector all value set"<<endl;
	
	cout<<"vecPositionRD3.setValue( 2, 123.456 )"<<endl;
	vecPositionRD3.setValue( 2, 123.456  );
	vecElementTypePosition[1] = 'w';
	vecValuesPosition[1] = 123.456;
	cout<<"vecPositionRD3.setValue( 3, -123.456 )"<<endl;
	vecPositionRD3.setValue( 3, -123.456 );
	vecElementTypePosition[2] = 'w';
	vecValuesPosition[2] = -123.456;

	szFileNameBuffer[0] = 0;
	const char * szVectorPositionRD3T3 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorPositionRD3T3.xml" );
	ofstream fileVectorPositionRD3T3( szVectorPositionRD3T3 );
	
	bStoreSuccesfull = vecPositionRD3.storeXml( fileVectorPositionRD3T3 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorPositionRD3T3 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorPositionRD3T3 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorPositionRD3T3, "position",
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
	
	cout<<"vecPositionRD3.setVariable( 1, pVariable1 )"<<endl;
	vecPositionRD3.setVariable( 1, pVariable1  );
	vecElementTypePosition[0] = 'v';
	vecValuesPosition[0] = 1;
	cout<<"vecPositionRD3.setVariable( 2, pVariable2 )"<<endl;
	vecPositionRD3.setVariable( 2, pVariable2 );
	vecElementTypePosition[1] = 'v';
	vecValuesPosition[1] = 2;
	cout<<"vecPositionRD3.setVariable( 3, pVariable3 )"<<endl;
	vecPositionRD3.setVariable( 3, pVariable3 );
	vecElementTypePosition[2] = 'v';
	vecValuesPosition[2] = 3;

	szFileNameBuffer[0] = 0;
	const char * szVectorPositionRD3T4 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorPositionRD3T4.xml" );
	ofstream fileVectorPositionRD3T4( szVectorPositionRD3T4 );
	
	bStoreSuccesfull = vecPositionRD3.storeXml( fileVectorPositionRD3T4 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorPositionRD3T4 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorPositionRD3T4 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorPositionRD3T4, "position",
		3, vecElementTypePosition, vecValuesPosition );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector with variables and values"<<endl;
	
	cout<<"vecPositionRD3.setVariable( 1, pVariable1 )"<<endl;
	vecPositionRD3.setVariable( 1, pVariable1  );
	vecElementTypePosition[0] = 'v';
	vecValuesPosition[0] = 1;
	cout<<"vecPositionRD3.setValue( 2, -0.00124 )"<<endl;
	vecPositionRD3.setValue( 2, -0.00124 );
	vecElementTypePosition[1] = 'w';
	vecValuesPosition[1] = -0.00124;
	cout<<"vecPositionRD3.setVariable( 3, pVariable3 )"<<endl;
	vecPositionRD3.setVariable( 3, pVariable3 );
	vecElementTypePosition[2] = 'v';
	vecValuesPosition[2] = 3;

	szFileNameBuffer[0] = 0;
	const char * szVectorPositionRD3T5 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorPositionRD3T5.xml" );
	ofstream fileVectorPositionRD3T5( szVectorPositionRD3T5 );
	
	bStoreSuccesfull = vecPositionRD3.storeXml( fileVectorPositionRD3T5 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorPositionRD3T5 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorPositionRD3T5 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorPositionRD3T5, "position",
		3, vecElementTypePosition, vecValuesPosition );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 5 d vector with variables and values"<<endl;
	
	cout<<"cVectorPosition vecPositionRD5 = cVectorPosition( 5, &rootD3 );"<<endl;
	cVectorPosition vecPositionRD5 = cVectorPosition( 5, &rootD3 );

	cout<<"vecPositionRD5.setVariable( 1, pVariable1 )"<<endl;
	vecPositionRD5.setVariable( 1, pVariable1  );
	vecElementTypePosition[0] = 'v';
	vecValuesPosition[0] = 1;
	cout<<"vecPositionRD5.setValue( 2, -0.00124 )"<<endl;
	vecPositionRD5.setValue( 2, -0.00124 );
	vecElementTypePosition[1] = 'w';
	vecValuesPosition[1] = -0.00124;
	cout<<"vecPositionRD5.setVariable( 3, pVariable3 )"<<endl;
	vecPositionRD5.setVariable( 3, pVariable3 );
	vecElementTypePosition[2] = 'v';
	vecValuesPosition[2] = 3;
	cout<<"vecPositionRD5.setValue( 4, 1234 )"<<endl;
	vecPositionRD5.setValue( 4, 1234 );
	vecElementTypePosition[3] = 'w';
	vecValuesPosition[3] = 1234;
	cout<<"vecPositionRD5.setValue( 5, 123.67 )"<<endl;
	vecPositionRD5.setValue( 5, 123.67   );
	vecElementTypePosition[4] = 'w';
	vecValuesPosition[4] = 123.67 ;

	szFileNameBuffer[0] = 0;
	const char * szVectorPositionRD3T6 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorPositionRD3T6.xml" );
	ofstream fileVectorPositionRD3T6( szVectorPositionRD3T6 );
	
	bStoreSuccesfull = vecPositionRD5.storeXml( fileVectorPositionRD3T6 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorPositionRD3T6 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorPositionRD3T6 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorPositionRD3T6, "position",
		5, vecElementTypePosition, vecValuesPosition );

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

	int iReturn = 0;//returnvalue of the test; the number of occured Errors


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an positionsvector with 0 elements"<<endl;

	cout<<"cVectorPosition vecPositionE0( 0 );"<<endl;
	cVectorPosition vecPositionE0( 0 );

	//test get compressed size
	unsigned int uiCompressedSize = 0;
	if ( (unsigned int)(vecPositionE0.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecPositionE0.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecPositionE0.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	cout<<"vecPositionE0.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bool bStoreSuccesfull = vecPositionE0.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cPositionE0[] = { 0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cPositionE0, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an positionsvector with 2 elements"<<endl;

	cout<<"cVectorPosition vecPosition1E2Ch( 2 );"<<endl;
	cVectorPosition vecPosition1E2Ch( 2 );
	cout<<"vecPosition1E2Ch.setValue( 1, 4 );"<<endl;
	vecPosition1E2Ch.setValue( 1, 4 );
	cout<<"vecPosition1E2Ch.setValue( 2, 6 );"<<endl;
	vecPosition1E2Ch.setValue( 2, 6 );

	//test get compressed size
	uiCompressedSize = 2 * 17;
	if ( (unsigned int)(vecPosition1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecPosition1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecPosition1E2Ch.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecPosition1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecPosition1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	unsigned char ucRestBit = cRestBit;
	unsigned char ucRestBitCorrect = 0x00;
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
	const char cPositionE2[] = { 0x08, 0x00, 0x18, 0x00, 0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cPositionE2, 5 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an positionsvector with variables"<<endl;

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

	cout<<"vecPosition1E2Ch.setVariable( 1, pVariable1);"<<endl;
	vecPosition1E2Ch.setVariable( 1, pVariable1);
	cout<<"vecPosition1E2Ch.setVariable( 2, pVariable2);"<<endl;
	vecPosition1E2Ch.setVariable( 2, pVariable2);

	//test get compressed size
	uiCompressedSize = 2 * 9;
	if ( (unsigned int)(vecPosition1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecPosition1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecPosition1E2Var.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecPosition1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecPosition1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = 0x00;
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
	const char cPositionE2Var[] = { 0x03, 0x0A, 0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cPositionE2Var, 3 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an positionsvector with domains"<<endl;

	cout<<"cTypeDimension typeDimensionD1( 1 );"<<endl;
	cTypeDimension typeDimensionD1( 1 );
	
	cout<<"cTypeDimension testTypeDimensionD2( 2 );"<<endl;
	cTypeDimension testTypeDimensionD2( 2 );
	cout<<"testTypeDimensionD2.setDimensionMapping( 1, 4 )"<<endl;
	testTypeDimensionD2.setDimensionMapping( 1, 4 );
	cout<<"testTypeDimensionD2.setDimensionMapping( 2, 3 )"<<endl;
	testTypeDimensionD2.setDimensionMapping( 2, 3 );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomains2( 2 );"<<endl;
	vector<cDomainSingle*> vecDomains2( 2 );
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomainD2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainD2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];

	cout<<"rootD2.getDomains()->addDomain( testTypeDimensionD2, vectorDomainD2);"<<endl;
	rootD2.getDomains()->addDomain( testTypeDimensionD2, vectorDomainD2);

	cout<<"cTypeVariable typeVariable;"<<endl;
	cTypeVariable typeVariable;

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB3( 3 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB3( 3 );

	cout<<"rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB3);"<<endl;
	rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB3);

	cout<<"vecPosition1E2Ch.setDefiningFibElement( &rootD2 );"<<endl;
	vecPosition1E2Ch.setDefiningFibElement( &rootD2 );
	
	cout<<"vecPosition1E2Ch.setValue( 2, 3);"<<endl;
	vecPosition1E2Ch.setValue( 2, 3);

	//test get compressed size
	uiCompressedSize = 4 + 3;
	if ( (unsigned int)(vecPosition1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecPosition1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecPosition1E2Dom.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecPosition1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecPosition1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = 0x63;
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
	const char cPositionE2Dom[] = { (char)ucRestBitCorrect };
	iReturn += compareBytsWithFile( szFileNameBuffer, cPositionE2Dom, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an positionsvector 3 elements"<<endl;

	cout<<"cVectorPosition vecPosition1E3( 3 );"<<endl;
	cVectorPosition vecPosition1E3( 3 );
	
	cout<<"vecPosition1E3.setVariable( 1, pVariable2 );"<<endl;
	vecPosition1E3.setVariable( 1, pVariable2 );
	cout<<"vecPosition1E3.setVariable( 2, pVariable1 );"<<endl;
	vecPosition1E3.setVariable( 2, pVariable1);
	cout<<"vecPosition1E3.setValue( 3, 5);"<<endl;
	vecPosition1E3.setValue( 3, 5);

	//test get compressed size
	uiCompressedSize = 2 * 9 + 17;
	if ( (unsigned int)(vecPosition1E3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecPosition1E3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecPosition1E3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecPosition1E3.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecPosition1E3.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = 0x00;
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
	const char cVecPosition1E3[] = { 0x05, 0x06, 0x28, 0x00, 0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cVecPosition1E3, 5 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an positionsvector with a restbit of 4"<<endl;

	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecPosition1E3R4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0x0F;
	cNumberOfRestBit = 4;
	cout<<"vecPosition1E3.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecPosition1E3.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = 0x00;
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
	const char cVecPosition1E3R4[] = { (char)0x5F, (char)0x60, (char)0x80, (char)0x02, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cVecPosition1E3R4, 5 );

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
	
	cout<<"cFibVector * pVecPositionDestination = new cVectorPosition();"<<endl;
	cFibVector  * pVecPositionDestination = new cVectorPosition();
	
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
			unsigned int uiNumberOfDimensions = 0;
			if ( (rand() % 10) != 0 ){
				uiNumberOfDimensions = (rand() % 3 + 1) * (rand() % 4 + 1) + (rand() % 4);
			}else{
				uiNumberOfDimensions = 0;
			}
			cout<<"pVecSource = new cVectorPosition( "<< uiNumberOfDimensions <<", &emptyRoot ); "<<endl;
			pVecSource = new cVectorPosition( uiNumberOfDimensions, &emptyRoot );
			
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
			pVecEqual = new cVectorPosition( pVecSource->getNumberOfElements(), &emptyRoot  );
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
		cout<<"(* pVecPositionDestination) = (* pVecSource );"<<endl;
		(* pVecPositionDestination) = (* pVecSource );
		
		//test the created vector
		if ( (*pVecPositionDestination) == ( * pVecEqual) ){
		
			cout<<"The vecPositionDestination is correct . "<<endl;
		}else{
			cerr<<"Error: The vecPositionDestination is not correct ."<<endl;
			iReturn++;
		}
		
		if ( pVecEqual != pVecSource ){
			//pVecEqual and pVecSource are different vectors
			delete pVecEqual;
		}
		delete pVecSource;
	}
	delete pVecPositionDestination;
	
	return iReturn;
}























