/**
 * @file tVectorArea
 * file name: tVectorArea.cpp
 * @author Betti Oesterholz
 * @date 13.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cVectorArea.
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
 * This file contains the test for the class cVectorArea,
 * which represents the vector for subareas.
 *
 *
 *
 *  What's tested of class cVectorArea:
 * 	- cVectorArea( cFibElement * pDefiningAreaElement );
 * 	- cVectorArea( const cVectorArea & vector, cFibElement * definingFibElement = NULL );
 * 	- cVectorArea( longFib lLowerBound, longFib lUpperBound, cFibElement * pDefiningAreaElement = NULL );
 * 	- cVectorArea( longFib lLowerBound, cFibVariable * pVariableUpperBound, cFibElement * pDefiningAreaElement = NULL );
 * 	- cVectorArea( cFibVariable * pVariableLowerBound, longFib lUpperBound, cFibElement * pDefiningAreaElement = NULL );
 * 	- cVectorArea( cFibVariable * pVariableLowerBound, cFibVariable * pVariableUpperBound, cFibElement * pDefiningAreaElement = NULL );
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
 * 	- longFib getLowerBound();
 * 	- longFib getUpperBound();
 * 	- list<longFib> getAreaValues();
 * 	- bool setLowerBoundValue( longFib lValue );
 * 	- bool setUpperBoundValue( longFib lValue );
 * 	- bool setLowerBoundVariable( cFibVariable *pVariable );
 * 	- bool setUpperBoundVariable( cFibVariable *pVariable );
 */
/*
History:
13.02.2010  Oesterholz  created
27.12.2009  Oesterholz  using function (tCompareBits:)compareDoubleFib() for comparing doubles from restored xml
20.02.2011  Oesterholz  sscanf() reads long long "%lld" instead of long
23.02.2011  Oesterholz  function testAreaBounderies() sets variable also to double values
04.04.2011  Oesterholz  storing to binary stream
29.04.2011  Oesterholz  sscanf() "%lld" for windows to "%I64d"
06.06.2011  Oesterholz  number atribute in XML-vector is now optional
25.08.2011  Oesterholz  cTypeUnderarea to cTypeSubarea
02.01.2011  Oesterholz  cTypeSubarea to cTypeArea;
   cTypeFibMatrix vector vor matrix element
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/


#include "version.h"

#include "cVectorArea.h"
#include "cTypeArea.h"
#include "cTypeFibMatrix.h"
#include "cTypeVariable.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cRoot.h"
#include "cPoint.h"
#include "cFibMatrix.h"

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
int testAreaBounderies( unsigned long &ulTestphase, unsigned int uiIterations );
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
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for cVectorArea methods"<<endl;
	cout<<      "===================================="<<endl;
	
	iReturn += testCostructor( ulTestphase );
	iReturn += testDomain( ulTestphase );
	iReturn += testGetSetDefiningElement( ulTestphase );
	iReturn += testVectorElements( ulTestphase );
	iReturn += testAreaBounderies( ulTestphase, 1024 );
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
 * and getType() method of the cVectorArea class.
 *
 * methods tested:
 * 	- cVectorArea( cFibElement * pDefiningAreaElement );
 * 	- cVectorArea( const cVectorArea & vector, cFibElement * definingFibElement = NULL );
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

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cVectorArea"<<endl;

	cout<<"cTypeArea typeArea;"<<endl;
	cTypeArea typeArea;
	
	cout<<"cVectorArea vecArea;"<<endl;
	cVectorArea vecArea;

	//check the getVectorType() methode from cVectorArea
	if ( vecArea.getVectorType() == "subarea" ){
	
		cout<<"The name of the subarea vector is correctly \"subarea\" . "<<endl;
	}else{
		cerr<<"Error: The name of the subarea vector is "<<
			vecArea.getVectorType()<<" but should be \"subarea\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorArea
	cTypeElement * pTypeSubarea = vecArea.getElementType();
	if ( typeArea == (*pTypeSubarea) ){
	
		cout<<"The type of the subarea vector is correctly equal to typeArea. "<<endl;
	}else{
		cerr<<"Error: The type of subarea vector not equal to typeArea ."<<endl;
		iReturn++;
	}
	delete pTypeSubarea;
	
	//check the getNumberOfElements() methode from cVectorArea
	if ( vecArea.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the subarea vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the subarea vector is "<<
			vecArea.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the subarea vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecArea.getNumberOfElements(); 
			uiActualElement++ ){
		
		if ( ! vecArea.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecArea.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is "<<vecArea.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorArea
	if ( vecArea.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the subarea vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the subarea vector."<<endl;
		iReturn++;
	}

	//check the getDomain() methode from cVectorArea
	if ( vecArea.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the subarea vector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the subarea vector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorArea with an empty root element"<<endl;

	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;
	
	cout<<"cVectorArea vecAreaRE( &emptyRoot );"<<endl;
	cVectorArea vecAreaRE( &emptyRoot );


	//check the getVectorType() methode from cVectorArea
	if ( vecAreaRE.getVectorType() == "subarea" ){
	
		cout<<"The name of the subarea vector is correctly \"subarea\" . "<<endl;
	}else{
		cerr<<"Error: The name of the subarea vector is "<<
			vecAreaRE.getVectorType()<<" but should be \"subarea\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorArea
	pTypeSubarea = vecAreaRE.getElementType();
	if ( typeArea == (*pTypeSubarea) ){
	
		cout<<"The type of the subarea vector is correctly equal to typeArea. "<<endl;
	}else{
		cerr<<"Error: The type of subarea vector not equal to typeArea ."<<endl;
		iReturn++;
	}
	delete pTypeSubarea;
	
	//check the getNumberOfElements() methode from cVectorArea
	if ( vecAreaRE.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the subarea vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the subarea vector is "<<
			vecAreaRE.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the subarea vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecAreaRE.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecAreaRE.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecAreaRE.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is "<<vecAreaRE.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorArea
	if ( vecAreaRE.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the subarea vector."<<endl;
		iReturn++;	
	}else if ( &emptyRoot == vecAreaRE.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the subarea vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the subarea vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorArea
	if ( vecAreaRE.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the subarea vector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the subarea vector."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorArea with the rootD2 root element"<<endl;
	
	cout<<"cRoot rootDom;"<<flush<<endl;
	cRoot rootDom;
	
	//create vector domain with two elements
	cout<<"vector<cDomain*> vecDomains2( 2 );"<<endl;
	vector<cDomain*> vecDomains2( 2 );
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomainE2Nat1Nat2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat1Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomains2[ 1 ] = &vectorDomainE2Nat1Nat2;"<<endl;
	vecDomains2[ 1 ] = &vectorDomainE2Nat1Nat2;
	cout<<"cDomainVector vectorDomainE2Nat3VE2Nat1Nat2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat3VE2Nat1Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];
	
	cout<<"rootDom.getDomains()->addDomain( typeArea, &vectorDomainE2Nat3VE2Nat1Nat2 );"<<endl;
	rootDom.getDomains()->addDomain( typeArea, &vectorDomainE2Nat3VE2Nat1Nat2 );

	cout<<"cVectorArea vecAreaRD2( &rootDom );"<<endl;
	cVectorArea vecAreaRD2( &rootDom );

	//check the getVectorType() methode from cVectorArea
	if ( vecAreaRD2.getVectorType() == "subarea" ){
	
		cout<<"The name of the subarea vector is correctly \"subarea\" . "<<endl;
	}else{
		cerr<<"Error: The name of the subarea vector is "<<
			vecAreaRD2.getVectorType()<<" but should be \"subarea\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorArea
	pTypeSubarea = vecAreaRD2.getElementType();
	if ( typeArea == (*pTypeSubarea) ){
	
		cout<<"The type of the subarea vector is correctly equal to typeArea. "<<endl;
	}else{
		cerr<<"Error: The type of subarea vector not equal to typeArea ."<<endl;
		iReturn++;
	}
	delete pTypeSubarea;
	
	//check the getNumberOfElements() methode from cVectorArea
	if ( vecAreaRD2.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the subarea vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the subarea vector is "<<
			vecAreaRD2.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the subarea vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecAreaRD2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecAreaRD2.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecAreaRD2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is "<<vecAreaRD2.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorArea
	if ( vecAreaRD2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the subarea vector."<<endl;
		iReturn++;	
	}else if ( &rootDom == vecAreaRD2.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the subarea vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the subarea vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorArea
	if ( vecAreaRD2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the subarea vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE2Nat1Nat2 == (*(vecAreaRD2.getDomain())) ){
	
		cout<<"The vectorDomainE2Nat1Nat2 is the domain for the subarea vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE2Nat1Nat2 is not the domain for the subarea vector."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the method for the domains of the cVectorArea class.
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
	
	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeArea typeArea;"<<endl;
	cTypeArea typeArea;
	
	//create vector domain with two elements
	cout<<"vector<cDomain*> vecDomains2( 2 );"<<endl;
	vector<cDomain*> vecDomains2( 2 );
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomainE2Nat1Nat2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat1Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomains2[ 1 ] = &vectorDomainE2Nat1Nat2;"<<endl;
	vecDomains2[ 1 ] = &vectorDomainE2Nat1Nat2;
	cout<<"cDomainVector vectorDomainE2Nat3VE2Nat1Nat2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat3VE2Nat1Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];
	
	cout<<"rootD2.getDomains()->addDomain( typeArea, &vectorDomainE2Nat3VE2Nat1Nat2 );"<<endl;
	rootD2.getDomains()->addDomain( typeArea, &vectorDomainE2Nat3VE2Nat1Nat2 );

	cout<<"cVectorArea vecAreaRD2 = cVectorArea( &rootD2 );"<<endl;
	cVectorArea vecAreaRD2 = cVectorArea( &rootD2 );
	
	//check the getNumberOfElements() methode from cVectorArea
	if ( vecAreaRD2.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the subarea vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the subarea vector is "<<
			vecAreaRD2.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	//check the getDomain() methode from cVectorArea
	if ( vecAreaRD2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the subarea vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE2Nat3VE2Nat1Nat2.getElementDomain( 2 ) ==
			vecAreaRD2.getDomain() ){
	
		cout<<"The vectorDomainE2Nat3VE2Nat1Nat2[ 2 ] is the domain for the subarea vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE2Nat3VE2Nat1Nat2[ 2 ] is not the domain for the subarea vector."<<endl;
		iReturn++;
	}

	/*check the getDomain(i=1..n) method of the subarea vektor*/
	//test the getType() method
	cout<<"cDomain * pDomainD2 = vecAreaRD2.getDomain();"<<endl;
	cDomain * pDomainD2 = vecAreaRD2.getDomain();
	if ( pDomainD2->getType() == "DomainVector" ){
	
		cout<<"The type of pDomainD2 is correctly \"DomainVector\". "<<endl;

		cDomainVector * pVectorDomainD3 = (cDomainVector*)pDomainD2;
		
		//test the getNumberOfElements() method
		if ( pVectorDomainD3->getNumberOfElements() == 2 ){
		
			cout<<"The number of elements of pDomainD2 is correctly 2. "<<endl;
			
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
		cerr<<"Error: The type of pDomainD2 is "<<pDomainD2->getType() <<
			" and not \"DomainVector\""<<endl;
		iReturn++;
	}

	//check the getStandardDomain() method from cVectorArea
	cDomain * pDomainStandardD2 = vecAreaRD2.getStandardDomain();
	cDomain * pTypeDomainStandardD2 = typeArea.getStandardDomain();
	
	if ( pDomainStandardD2 == NULL ){
		cerr<<"Error: Ther is no domain defined for the subarea vector."<<endl;
		iReturn++;	
	}else if ( *pDomainStandardD2 == *(((cDomainVector*)pTypeDomainStandardD2)->
			getElementDomain( 2 )) ){
	
		cout<<"The vecAreaRD2 has the correct standard domain. "<<endl;
	}else{
		cerr<<"Error: The vecAreaRD2 has not the correct standard domain."<<endl;
		iReturn++;
	}

	delete pDomainStandardD2;
	delete pTypeDomainStandardD2;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get Domain methods for the matrix element"<<endl;
		
	cout<<"cTypeFibMatrix typeFibMatrix;"<<endl;
	cTypeFibMatrix typeFibMatrix;
	
	//create vector domain with two elements
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 7 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 7 );
	cout<<"cDomainVector vectorDomainE2Nat5Nat7( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat5Nat7( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	cout<<"vector<cDomain*> vecDomains4( 4 );"<<endl;
	vector<cDomain*> vecDomains4( 4 );
	cout<<"vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomains4[ 2 ] = &vectorDomainE2Nat5Nat7;"<<endl;
	vecDomains4[ 2 ] = &vectorDomainE2Nat5Nat7;
	cout<<"vecDomains4[ 3 ] = &vectorDomainE2Nat1Nat2;"<<endl;
	vecDomains4[ 3 ] = &vectorDomainE2Nat1Nat2;
	cout<<"cDomainVector vectorDomainE4Nat5Nat7VE2Nat2Nat4VE2Nat1Nat2( vecDomains4 );"<<endl;
	cDomainVector vectorDomainE4Nat5Nat7VE2Nat2Nat4VE2Nat1Nat2( vecDomains4 );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	
	cout<<"rootD2.getDomains()->addDomain( typeFibMatrix, &vectorDomainE4Nat5Nat7VE2Nat2Nat4VE2Nat1Nat2 );"<<endl;
	rootD2.getDomains()->addDomain( typeFibMatrix, &vectorDomainE4Nat5Nat7VE2Nat2Nat4VE2Nat1Nat2 );

	
	cout<<"cFibMatrix matrix( 1, 2, NULL, &rootD2 );"<<endl;
	cFibMatrix matrix( 1, 2, NULL, &rootD2 );

	cout<<"cVectorArea vecAreaMatrix( &matrix );"<<endl;
	cVectorArea vecAreaMatrix( &matrix );
	
	//check the getNumberOfElements() methode from cVectorArea
	if ( vecAreaMatrix.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the subarea vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the subarea vector is "<<
			vecAreaMatrix.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	//check the getDomain() methode from cVectorArea
	if ( vecAreaMatrix.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the subarea vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE4Nat5Nat7VE2Nat2Nat4VE2Nat1Nat2.getElementDomain( 3 ) ==
			vecAreaMatrix.getDomain() ){
	
		cout<<"The vectorDomainE4Nat5Nat7VE2Nat2Nat4VE2Nat1Nat2[ 3 ] is the domain for the subarea vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE4Nat5Nat7VE2Nat2Nat4VE2Nat1Nat2[ 3 ] is not the domain for the subarea vector."<<endl;
		iReturn++;
	}

	/*check the getDomain(i=1..n) method of the subarea vektor*/
	//test the getType() method
	cout<<"cDomain * pDomain = vecAreaMatrix.getDomain();"<<endl;
	cDomain * pDomain = vecAreaMatrix.getDomain();
	if ( pDomain->getType() == "DomainVector" ){
	
		cout<<"The type of pDomain is correctly \"DomainVector\". "<<endl;

		cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
		
		//test the getNumberOfElements() method
		if ( pVectorDomain->getNumberOfElements() == 2 ){
		
			cout<<"The number of elements of pDomain is correctly 2. "<<endl;
			
			//check domains of vector domain elements
			
			cDomainNaturalNumberBit domainNaturalNumberBit5( 5 );
			if ( pVectorDomain->getElementDomain( 1 ) == NULL ){
				cerr<<"Error: The first element domain is NULL. "<<endl;
				iReturn++;
			}else if ( (*(pVectorDomain->getElementDomain( 1 ))) == domainNaturalNumberBit5 ){
			
				cout<<"The first element domain is correctly an cDomainNaturalNumberBit domain with 5 bits. "<<endl;
			}else{
				cerr<<"Error: The first element domain is not an cDomainNaturalNumberBit domain with 5 bits. "<<endl;
				iReturn++;
			}
	
			cDomainNaturalNumberBit domainNaturalNumberBit7( 7 );
			if ( pVectorDomain->getElementDomain( 2 )==NULL ){
				cerr<<"Error: The secound element domain is NULL. "<<endl;
				iReturn++;
			}else if ( (*(pVectorDomain->getElementDomain( 2 ))) == domainNaturalNumberBit7 ){
			
				cout<<"The secound element domain is correctly an cDomainNaturalNumberBit domain with 7 bits. "<<endl;
			}else{
				cerr<<"Error: The secound element domain is not an cDomainNaturalNumberBit domain with 7 bits. "<<endl;
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
			cerr<<"Error: The number of elements of pVectorDomain is "<<
				pVectorDomain->getNumberOfElements() <<" and not 3 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The type of pDomain is "<<pDomain->getType() <<
			" and not \"DomainVector\""<<endl;
		iReturn++;
	}

	//check the getStandardDomain() method from cVectorArea
	cDomain * pDomainStandard = vecAreaMatrix.getStandardDomain();
	cDomain * pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the subarea vector."<<endl;
		iReturn++;	
	}else if ( *pDomainStandard == *(((cDomainVector*)pTypeDomainStandard)->
			getElementDomain( 3 )) ){
	
		cout<<"The vecAreaMatrix has the correct standard domain. "<<endl;
	}else{
		cerr<<"Error: The vecAreaMatrix has not the correct standard domain."<<endl;
		iReturn++;
	}

	delete pDomainStandard;
	delete pTypeDomainStandard;
	
	return iReturn;
}


/**
 * This method tests setDefiningFibElement() and getDefiningFibElement()
 * method of the cVectorArea class.
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

	cout<<"cVectorArea vecArea;"<<endl;
	cVectorArea vecArea;

	//check the getDefiningFibElement() methode from cVectorArea
	if ( vecArea.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the subarea vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the subarea vector."<<endl;
		iReturn++;
	}
	
	cout<<"vecArea.setDefiningFibElement( &definingElement1 );"<<endl;
	vecArea.setDefiningFibElement( &definingElement1 );

	//check the getDefiningFibElement() methode from cVectorArea
	if ( vecArea.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the subarea vector."<<endl;
		iReturn++;	
	}else if ( &definingElement1 == vecArea.getDefiningFibElement() ){
	
		cout<<"The definingElement1 is the defining element for the subarea vector. "<<endl;
	}else{
		cerr<<"Error: The definingElement1 is not the defining element for the subarea vector."<<endl;
		iReturn++;
	}

	cout<<"vecArea.setDefiningFibElement( &definingElement2 );"<<endl;
	vecArea.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorArea
	if ( vecArea.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the subarea vector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecArea.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the subarea vector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the subarea vector."<<endl;
		iReturn++;
	}

	cout<<"vecArea.setDefiningFibElement( NULL );"<<endl;
	vecArea.setDefiningFibElement( NULL );

	//check the getDefiningFibElement() methode from cVectorArea
	if ( vecArea.getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the subarea vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the subarea vector."<<endl;
		iReturn++;
	}

	cout<<"vecArea.setDefiningFibElement( &definingElement2 );"<<endl;
	vecArea.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorArea
	if ( vecArea.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the subarea vector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecArea.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the subarea vector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the subarea vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods when a domain is given"<<endl;
	
	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeArea typeArea;"<<endl;
	cTypeArea typeArea;
	
	//create vector domain with two elements
	cout<<"vector<cDomain*> vecDomains2( 2 );"<<endl;
	vector<cDomain*> vecDomains2( 2 );
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomainE2Nat1Nat2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat1Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomains2[ 1 ] = &vectorDomainE2Nat1Nat2;"<<endl;
	vecDomains2[ 1 ] = &vectorDomainE2Nat1Nat2;
	cout<<"cDomainVector vectorDomainE2Nat3VE2Nat1Nat2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat3VE2Nat1Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];

	cout<<"rootD2.getDomains()->addDomain( typeArea, &vectorDomainE2Nat3VE2Nat1Nat2 );"<<endl;
	rootD2.getDomains()->addDomain( typeArea, &vectorDomainE2Nat3VE2Nat1Nat2 );

	
	cout<<"cTypeFibMatrix typeFibMatrix;"<<endl;
	cTypeFibMatrix typeFibMatrix;
	
	//create vector domain with two elements
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 7 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 7 );
	cout<<"cDomainVector vectorDomainE2Nat5Nat7( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat5Nat7( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	cout<<"vector<cDomain*> vecDomains4( 4 );"<<endl;
	vector<cDomain*> vecDomains4( 4 );
	cout<<"vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomains4[ 2 ] = &vectorDomainE2Nat5Nat7;"<<endl;
	vecDomains4[ 2 ] = &vectorDomainE2Nat5Nat7;
	cout<<"vecDomains4[ 3 ] = &vectorDomainE2Nat1Nat2;"<<endl;
	vecDomains4[ 3 ] = &vectorDomainE2Nat1Nat2;
	cout<<"cDomainVector vectorDomainE4Nat5Nat7VE2Nat2Nat4VE2Nat1Nat2( vecDomains4 );"<<endl;
	cDomainVector vectorDomainE4Nat5Nat7VE2Nat2Nat4VE2Nat1Nat2( vecDomains4 );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	
	cout<<"rootD2.getDomains()->addDomain( typeFibMatrix, &vectorDomainE4Nat5Nat7VE2Nat2Nat4VE2Nat1Nat2 );"<<endl;
	rootD2.getDomains()->addDomain( typeFibMatrix, &vectorDomainE4Nat5Nat7VE2Nat2Nat4VE2Nat1Nat2 );

	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint pointD2( NULL, &rootD2 );"<<endl;
	cPoint pointD2( NULL, &rootD2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint pointD2( NULL, &rootD2, &rootD2 );"<<endl;
	cPoint pointD2( NULL, &rootD2, &rootD2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	
	cout<<"cVectorArea vecAreaPD2;"<<endl;
	cVectorArea vecAreaPD2;
	
	cout<<"vecAreaPD2.setDefiningFibElement( &pointD2 );"<<endl;
	vecAreaPD2.setDefiningFibElement( &pointD2 );

	cout<<"cVectorArea vecArea2D2;"<<endl;
	cVectorArea vecArea2D2;

	if ( vecAreaPD2 == vecArea2D2 ){
	
		cout<<"The subarea vector vecAreaPD2 is equal to vecArea2D2. "<<endl;
	}else{
		cerr<<"Error: The subarea vector vecAreaPD2 is not equal to vecArea2D2."<<endl;
		iReturn++;
	}

	cout<<"cVectorArea vecArea1E2;"<<endl;
	cVectorArea vecArea1E2;
	cout<<"vecArea1E2.setValue( 1, 1);"<<endl;
	vecArea1E2.setValue( 1, 1);
	cout<<"vecArea1E2.setValue( 2, 2);"<<endl;
	vecArea1E2.setValue( 2, 2);

	cout<<"cVectorArea vecArea2E2;"<<endl;
	cVectorArea vecArea2E2;
	cout<<"vecArea2E2.setValue( 1, 3);"<<endl;
	vecArea2E2.setValue( 1, 3);
	cout<<"vecArea2E2.setValue( 2, 2);"<<endl;
	vecArea2E2.setValue( 2, 2);

	cout<<"vecArea2E2.setDefiningFibElement( &pointD2 );"<<endl;
	vecArea2E2.setDefiningFibElement( &pointD2 );

	if ( vecArea2E2 == vecArea1E2 ){
	
		cout<<"The subarea vector vecArea2E2 is equal to vecArea1E2. "<<endl;
	}else{
		cerr<<"Error: The subarea vector vecArea2E2 is not equal to vecArea1E2."<<endl;
		/*check the elements of the subarea vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecArea2E2.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecArea2E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecArea2E2.getValue( uiActualElement ) ==
					vecArea1E2.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is correctly "<< 
					vecArea1E2.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is "<<vecArea2E2.getValue( uiActualElement )<<
					" and not "<< vecArea1E2.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	cout<<"vecArea1E2.setValue( 1, 0);"<<endl;
	vecArea1E2.setValue( 1, 0);
	cout<<"vecArea1E2.setValue( 2, 1);"<<endl;
	vecArea1E2.setValue( 2, 1);

	cout<<"cVectorArea vecArea3E2( vecArea1E2 );"<<endl;
	cVectorArea vecArea3E2( vecArea1E2 );

	cout<<"vecArea3E2.setDefiningFibElement( &pointD2 );"<<endl;
	vecArea3E2.setDefiningFibElement( &pointD2 );


	if ( vecArea3E2 == vecArea1E2 ){
	
		cout<<"The subarea vector vecArea3E2 is equal to vecArea1E2. "<<endl;
	}else{
		cerr<<"Error: The subarea vector vecArea3E2 is not equal to vecArea1E2."<<endl;
		/*check the elements of the subarea vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecArea3E2.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecArea3E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecArea3E2.getValue( uiActualElement ) ==
					vecArea1E2.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is correctly "<< 
					vecArea1E2.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is "<<vecArea3E2.getValue( uiActualElement )<<
					" and not "<< vecArea1E2.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}


	cout<<"vecArea1E2.setValue( 1, 0 );"<<endl;
	vecArea1E2.setValue( 1, 0 );
	cout<<"vecArea1E2.setValue( 2, 3 );"<<endl;
	vecArea1E2.setValue( 2, 3 );

	cout<<"cVectorArea vecArea4E2;"<<endl;
	cVectorArea vecArea4E2;
	cout<<"vecArea4E2.setValue( 1, -7 );"<<endl;
	vecArea4E2.setValue( 1, -7 );
	cout<<"vecArea4E2.setValue( 2, 4 );"<<endl;
	vecArea4E2.setValue( 2, 4 );

	cout<<"vecArea4E2.setDefiningFibElement( &pointD2 );"<<endl;
	vecArea4E2.setDefiningFibElement( &pointD2 );

	if ( vecArea4E2 == vecArea1E2 ){
	
		cout<<"The subarea vector vecArea4E2 is equal to vecArea1E2. "<<endl;
	}else{
		cerr<<"Error: The subarea vector vecArea4E2 is not equal to vecArea1E2."<<endl;
		/*check the elements of the subarea vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecArea4E2.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecArea4E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecArea4E2.getValue( uiActualElement ) ==
					vecArea1E2.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is correctly "<< 
					vecArea1E2.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is "<<vecArea4E2.getValue( uiActualElement )<<
					" and not "<< vecArea1E2.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	
	
	cout<<"cFibMatrix fibMatrixCorr( 2, 1 );"<<endl;
	cFibMatrix fibMatrixCorr( 2, 1 );
	cout<<"cVectorArea vecAreaMatrixCorr( &fibMatrixCorr );"<<endl;
	cVectorArea vecAreaMatrixCorr( &fibMatrixCorr );
	cout<<"vecAreaMatrixCorr.setValue( 1, 31 );"<<endl;
	vecAreaMatrixCorr.setValue( 1, 31 );
	cout<<"vecAreaMatrixCorr.setValue( 2, 127 );"<<endl;
	vecAreaMatrixCorr.setValue( 2, 127 );

	cout<<"cVectorArea vecAreaMatrix;"<<endl;
	cVectorArea vecAreaMatrix;
	cout<<"vecAreaMatrix.setValue( 1, 51 );"<<endl;
	vecAreaMatrix.setValue( 1, 51 );
	cout<<"vecAreaMatrix.setValue( 2, 200 );"<<endl;
	vecAreaMatrix.setValue( 2, 200 );
	
	cout<<"cFibMatrix fibMatrix( 1, 2 );"<<endl;
	cFibMatrix fibMatrix( 1, 2 );
	cout<<"rootD2.setMainFibObject( &fibMatrix );"<<endl;
	rootD2.setMainFibObject( &fibMatrix );
	
	cout<<"vecAreaMatrix.setDefiningFibElement( &fibMatrix );"<<endl;
	vecAreaMatrix.setDefiningFibElement( &fibMatrix );

	if ( vecAreaMatrix == vecAreaMatrixCorr ){
	
		cout<<"The subarea vector vecAreaMatrix is equal to vecAreaMatrixCorr. "<<endl;
	}else{
		cerr<<"Error: The subarea vector vecAreaMatrix is not equal to vecAreaMatrixCorr."<<endl;
		//check the elements of the subarea vektor
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecAreaMatrix.getNumberOfElements();
				uiActualElement++ ){
			
			if ( ! vecAreaMatrix.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecAreaMatrix.getValue( uiActualElement ) ==
					vecAreaMatrixCorr.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is correctly "<< 
					vecAreaMatrixCorr.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is "<<vecAreaMatrix.getValue( uiActualElement )<<
					" and not "<< vecAreaMatrixCorr.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods when adomain is given but shouldn't be checked"<<endl;
	
	cout<<"cVectorArea vecArea5E2;"<<endl;
	cVectorArea vecArea5E2;
	cout<<"vecArea5E2.setValue( 1, 3);"<<endl;
	vecArea5E2.setValue( 1, 3);
	cout<<"vecArea5E2.setValue( 2, 2);"<<endl;
	vecArea5E2.setValue( 2, 2);
	
	cVectorArea vecArea6E2( vecArea5E2 );

	cout<<"vecArea6E2.setDefiningFibElement( &pointD2, false );"<<endl;
	vecArea6E2.setDefiningFibElement( &pointD2, false );

	if ( vecArea6E2 == vecArea5E2 ){
	
		cout<<"The subarea vector vecArea6E2 is equal to vecArea5E2. "<<endl;
	}else{
		cerr<<"Error: The subarea vector vecArea6E2 is not equal to vecArea5E2."<<endl;
		/*check the elements of the subarea vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecArea6E2.getNumberOfElements() &&
				uiActualElement <= 2;
				uiActualElement++ ){
			
			if ( ! vecArea6E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecArea6E2.getValue( uiActualElement ) ==
					vecArea5E2.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is correctly "<< 
					vecArea6E2.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is "<<vecArea6E2.getValue( uiActualElement )<<
					" and not "<< vecArea5E2.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	cout<<"cVectorArea vecArea7E2;"<<endl;
	cVectorArea vecArea7E2;
	cout<<"vecArea7E2.setValue( 1, -7 );"<<endl;
	vecArea7E2.setValue( 1, -7 );
	cout<<"vecArea7E2.setValue( 2, 4 );"<<endl;
	vecArea7E2.setValue( 2, 4 );
	
	cVectorArea vecArea58E2( vecArea7E2 );

	cout<<"vecArea58E2.setDefiningFibElement( &pointD2, false );"<<endl;
	vecArea58E2.setDefiningFibElement( &pointD2, false );

	if ( vecArea58E2 == vecArea7E2 ){
	
		cout<<"The subarea vector vecArea58E2 is equal to vecArea7E2. "<<endl;
	}else{
		cerr<<"Error: The subarea vector vecArea58E2 is not equal to vecArea7E2."<<endl;
		/*check the elements of the subarea vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecArea58E2.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecArea58E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is correctly not an variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is an variable. "<<endl;
				iReturn++;
			}
			if ( vecArea58E2.getValue( uiActualElement ) ==
					vecArea7E2.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is correctly "<< 
					vecArea7E2.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"subarea vector is "<<vecArea58E2.getValue( uiActualElement )<<
					" and not "<< vecArea7E2.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	

	return iReturn;
}



/**
 * This method tests cVectorArea methods for manipulating the
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

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

//TODO test if yust values of the domain can be set

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing methods for getting the vectorelementdata"<<endl;
	
	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;
	
	cout<<"cVectorArea vecArea( &emptyRoot );"<<endl;
	cVectorArea vecArea( &emptyRoot );


	/*check the elements of the subarea vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecArea.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecArea.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is an variable. "<<endl;
			iReturn++;
		}
		if ( vecArea.getValue( uiActualElement ) == (doubleFib)(0.0) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is "<<vecArea.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
		if ( vecArea.getVariable( uiActualElement ) == NULL ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly no variable . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is an variable . "<<endl;
			iReturn++;
		}
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setValue() method"<<endl;

	cout<<"vecArea.setValue( 2, 2.2 )"<<endl;
	if ( vecArea.setValue( 2, 2.2 ) ){
	
		cout<<"The 2'th element of the subarea vector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecArea.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the subarea vector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"subarea vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is "<<
			vecArea.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the subarea vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is an variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecArea.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the subarea vector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 2 ) == (doubleFib)(2.2) ){
	
		cout<<"The 2'th element of the "<<
			"subarea vector is correctly 2.2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is "<<
			vecArea.getValue( 2 )<<" and not 2.2 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the subarea vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is an variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecArea.setValue( 2, 0.7 )"<<endl;
	if ( vecArea.setValue( 2, 0.7 ) ){
	
		cout<<"The 2'th element of the subarea vector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecArea.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the subarea vector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"subarea vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is "<<
			vecArea.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the subarea vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is an variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecArea.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the subarea vector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"subarea vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is "<<
			vecArea.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the subarea vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is an variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecArea.setValue( 1, 11 )"<<endl;
	if ( vecArea.setValue( 1, 11 ) ){
	
		cout<<"The 1'th element of the subarea vector is set. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecArea.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the subarea vector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 1 ) == (doubleFib)(11) ){
	
		cout<<"The 1'th element of the "<<
			"subarea vector is correctly 11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is "<<
			vecArea.getValue( 1 )<<" and not 11 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the subarea vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is an variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecArea.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the subarea vector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"subarea vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is "<<
			vecArea.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the subarea vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is an variable . "<<endl;
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
	cout<<endl<<"vecArea.setVariable( 1, pVariable1 )"<<endl;
	if ( vecArea.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the subarea vector is set to the variable 1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not set to the variable 1. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecArea.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the subarea vector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 1 ) == (doubleFib)(0) ){
	
		cout<<"The 1'th element of the "<<
			"subarea vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is "<<
			vecArea.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the subarea vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecArea.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the subarea vector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"subarea vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is "<<
			vecArea.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the subarea vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is an variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable1->setValue( 0.11 );"<<endl;
	pVariable1->setValue( 0.11 );
	
	if ( vecArea.getValue( 1 ) == (doubleFib)(0.11) ){
	
		cout<<"The 1'th element of the "<<
			"subarea vector is correctly 0.11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is "<<
			vecArea.getValue( 1 )<<" and not 0.11 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable1->setValue( 111 );"<<endl;
	pVariable1->setValue( 111 );
	
	if ( vecArea.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"subarea vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is "<<
			vecArea.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4 = emptyRoot.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable4 = emptyRoot.getInputVariable( 4 );
	cout<<endl<<"vecArea.setVariable( 2, pVariable4 )"<<endl;
	if ( vecArea.setVariable( 2, pVariable4 ) ){
	
		cout<<"The 2'th element of the subarea vector is set to the variable 4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is not set to the variable 4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecArea.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the subarea vector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"subarea vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is "<<
			vecArea.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the subarea vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecArea.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the subarea vector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 2 ) == (doubleFib)(0.0) ){
	
		cout<<"The 2'th element of the "<<
			"subarea vector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is "<<
			vecArea.getValue( 2 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the subarea vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 123 );"<<endl;
	pVariable4->setValue( 123 );
	
	if ( vecArea.getValue( 2 ) == (doubleFib)(123) ){
	
		cout<<"The 2'th element of the "<<
			"subarea vector is correctly 123 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is "<<
			vecArea.getValue( 2 )<<" and not 123 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 0.321 );"<<endl;
	pVariable4->setValue( 0.321  );
	
	if ( vecArea.getValue( 2 ) == (doubleFib)(0.321 ) ){
	
		cout<<"The 2'th element of the "<<
			"subarea vector is correctly 0.321  . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is "<<
			vecArea.getValue( 2 )<<" and not 0.321  . "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecArea.setVariable( 1, pVariable4 )"<<endl;
	if ( vecArea.setVariable( 1, pVariable4 ) ){
	
		cout<<"The 1'th element of the subarea vector is set to the variable 4. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not set to the variable 4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecArea.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the subarea vector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 1 ) == (doubleFib)(0.321) ){
	
		cout<<"The 1'th element of the "<<
			"subarea vector is correctly 0.321 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is "<<
			vecArea.getValue( 1 )<<" and not 0.321 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 1 ) == pVariable4 ){
	
		cout<<"The 1'th element of the subarea vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecArea.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the subarea vector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 2 ) == (doubleFib)(0.321) ){
	
		cout<<"The 2'th element of the "<<
			"subarea vector is correctly 0.321 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is "<<
			vecArea.getValue( 2 )<<" and not 0.321 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the subarea vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 654.123 );"<<endl;
	pVariable4->setValue( 654.123 );
	
	if ( vecArea.getValue( 1 ) == (doubleFib)(654.123) ){
	
		cout<<"The 1'th element of the "<<
			"subarea vector is correctly 654.123 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is "<<
			vecArea.getValue( 1 )<<" and not 654.123 . "<<endl;
		iReturn++;
	}
	
	if ( vecArea.getValue( 2 ) == (doubleFib)(654.123) ){
	
		cout<<"The 2'th element of the "<<
			"subarea vector is correctly 654.123 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is "<<
			vecArea.getValue( 2 )<<" and not 654.123 . "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setValue() and setVariable() after each other method"<<endl;
	
	cout<<endl<<"vecArea.setValue( 1, 17 )"<<endl;
	if ( vecArea.setValue( 1, 17 ) ){
	
		cout<<"The 1'th element of the subarea vector is set to the value 17"<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not set to the value 17. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecArea.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the subarea vector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 1 ) == (doubleFib)(17) ){
	
		cout<<"The 1'th element of the "<<
			"subarea vector is correctly 17 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is "<<
			vecArea.getValue( 1 )<<" and not 17 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the subarea vector is correctly not an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is an variable. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecArea.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the subarea vector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 2 ) == (doubleFib)(654.123 ) ){
	
		cout<<"The 2'th element of the "<<
			"subarea vector is correctly 654.123  . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is "<<
			vecArea.getValue( 2 )<<" and not 654.123  . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the subarea vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 65 );"<<endl;
	pVariable4->setValue( 65 );
	
	if ( vecArea.getValue( 2 ) == (doubleFib)(65) ){
	
		cout<<"The 2'th element of the "<<
			"subarea vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is "<<
			vecArea.getValue( 2 )<<" and not 65 . "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecArea.setVariable( 1, pVariable1 )"<<endl;
	if ( vecArea.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the subarea vector is set to the varaiable 1"<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not set to the variable 1. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecArea.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the subarea vector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"subarea vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is "<<
			vecArea.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the subarea vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecArea.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the subarea vector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 2 ) == (doubleFib)(65 ) ){
	
		cout<<"The 2'th element of the "<<
			"subarea vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is "<<
			vecArea.getValue( 2 )<<" and not 65  . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the subarea vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setVariable() methods with trying to set NULL"<<endl;
	
	cout<<endl<<"vecArea.setVariable( 1, NULL )"<<endl;
	if ( ! vecArea.setVariable( 1, NULL ) ){
	
		cout<<"The 1'th element of the subarea vector couldn't be set to NULL."<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector could be set to NULL. "<<endl;
		iReturn++;
	}
	cout<<endl<<"vecArea.setVariable( 2, NULL )"<<endl;
	if ( ! vecArea.setVariable( 2, NULL ) ){
	
		cout<<"The 2'th element of the subarea vector couldn't be set to NULL."<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector could be set to NULL. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecArea.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the subarea vector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"subarea vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is "<<
			vecArea.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the subarea vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the subarea vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecArea.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the subarea vector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getValue( 2 ) == (doubleFib)(65 ) ){
	
		cout<<"The 2'th element of the "<<
			"subarea vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is "<<
			vecArea.getValue( 2 )<<" and not 65  . "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the subarea vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the subarea vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing replaceVariable(), isUsedVariable() and getUsedVariables() methods"<<endl;
	
	cout<<endl<<"pVariable2 = emptyRoot.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = emptyRoot.getInputVariable( 2 );
	cout<<endl<<"pVariable3 = emptyRoot.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = emptyRoot.getInputVariable( 3 );
	
	//check vecArea.isUsedVariable()
	if ( vecArea.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecArea.isUsedVariable()
	if ( ! vecArea.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check isUsedVariable()
	if ( vecArea.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	
	set<cFibVariable*> setCorrectUsedVariables;
	setCorrectUsedVariables.insert( pVariable1 );
	setCorrectUsedVariables.insert( pVariable4 );
	//check getUsedVariables()
	cout<<"setUsedVariables = vecArea.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = vecArea.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	
	cout<<endl<<"vecArea.replaceVariable( pVariable1, pVariable4 )"<<endl;
	setCorrectUsedVariables.erase( pVariable1 );
	if ( vecArea.replaceVariable( pVariable1, pVariable4 ) ){
	
		cout<<"The pVariable1 of the propertyvector was replaced with pVariable4. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 of the propertyvector was not replaced with pVariable4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecArea.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 1 ) == pVariable4 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecArea.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check vecArea.isUsedVariable()
	if ( ! vecArea.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecArea.isUsedVariable()
	if ( ! vecArea.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecArea.isUsedVariable()
	if ( vecArea.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecArea.getUsedVariables(); "<<endl;
	setUsedVariables = vecArea.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecArea.replaceVariable( pVariable1, pVariable3 )"<<endl;
	if ( vecArea.replaceVariable( pVariable1, pVariable3 ) ){
	
		cout<<"The pVariable1 of the propertyvector was replaced with pVariable3. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 of the propertyvector was not replaced with pVariable3. "<<endl;
		iReturn++;
	}
	//check vecArea.isUsedVariable()
	if ( ! vecArea.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecArea.isUsedVariable()
	if ( vecArea.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecArea.getUsedVariables(); "<<endl;
	setUsedVariables = vecArea.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	cout<<endl<<"vecArea.replaceVariable( pVariable4, pVariable2 )"<<endl;
	setCorrectUsedVariables.erase( pVariable4 );
	setCorrectUsedVariables.insert( pVariable2 );
	if ( vecArea.replaceVariable( pVariable4, pVariable2 ) ){
	
		cout<<"The pVariable4 of the propertyvector was replaced with pVariable2. "<<endl;
	}else{
		cerr<<"Error: The pVariable4 of the propertyvector was not replaced with pVariable2. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecArea.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 1 ) == pVariable2 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecArea.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly an variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not an variable. "<<endl;
		iReturn++;
	}
	if ( vecArea.getVariable( 2 ) == pVariable2 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check vecArea.isUsedVariable()
	if ( ! vecArea.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecArea.isUsedVariable()
	if ( vecArea.isUsedVariable( pVariable2 ) ){
	
		cout<<"The pVariable2 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable2 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecArea.isUsedVariable()
	if ( ! vecArea.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecArea.isUsedVariable()
	if ( ! vecArea.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable4 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecArea.getUsedVariables(); "<<endl;
	setUsedVariables = vecArea.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	//check vecArea.isUsedVariable()
	if ( ! vecArea.isUsedVariable( NULL ) ){
	
		cout<<"The NULL is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The NULL is a used varible in the vector.  "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecArea.replaceVariable( NULL, pVariable2 )"<<endl;
	if ( ! vecArea.replaceVariable( NULL, pVariable2 ) ){
	
		cout<<"Can't correctly replace NULL of the propertyvector with pVariable2. "<<endl;
	}else{
		cerr<<"Error: Can replace NULL of the propertyvector with pVariable2. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecArea.replaceVariable( pVariable2, NULL )"<<endl;
	if ( ! vecArea.replaceVariable( pVariable2, NULL ) ){
	
		cout<<"Can't correctly replace pVariable2 of the propertyvector with NULL. "<<endl;
	}else{
		cerr<<"Error: Can replace pVariable2 of the propertyvector with NULL. "<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests cVectorArea methods for manipulating the
 * vectorelements.
 *
 * methods tested:
 * 	- cVectorArea( longFib lLowerBound, longFib lUpperBound, cFibElement * pDefiningAreaElement = NULL );
 * 	- cVectorArea( longFib lLowerBound, cFibVariable * pVariableUpperBound, cFibElement * pDefiningAreaElement = NULL );
 * 	- cVectorArea( cFibVariable * pVariableLowerBound, longFib lUpperBound, cFibElement * pDefiningAreaElement = NULL );
 * 	- cVectorArea( cFibVariable * pVariableLowerBound, cFibVariable * pVariableUpperBound, cFibElement * pDefiningAreaElement = NULL );
 * 	- longFib getLowerBound();
 * 	- longFib getUpperBound();
 * 	- list<longFib> getAreaValues();
 * 	- bool setLowerBoundValue( longFib lValue );
 * 	- bool setUpperBoundValue( longFib lValue );
 * 	- bool setLowerBoundVariable( cFibVariable *pVariable );
 * 	- bool setUpperBoundVariable( cFibVariable *pVariable );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testAreaBounderies( unsigned long &ulTestphase, unsigned int uiIterations ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructors and area bounderies methods"<<endl;

//TODO test if yust values of the domain can be set
	cVectorArea * pVectorArea = new cVectorArea();
	bool bLowerBoundIsValue = true;
	bool bUpperBoundIsValue = true;
	
	cFibElement * pDefiningFibElement = NULL;
	cRoot root;
	//create variables which can be set
	const unsigned int uiNumberOfVariables = 10;
	cout<<"root.setNumberOfInputVariables( uiNumberOfVariables )"<<endl;
	root.setNumberOfInputVariables( uiNumberOfVariables );
	
	vector<cFibVariable*> vecVariables;
	for ( unsigned int uiVariable = 1; uiVariable <= uiNumberOfVariables;
			uiVariable++ ){
		
		vecVariables.push_back( root.getInputVariable( uiVariable ) );
	}

	for ( unsigned int uiIteration = 0; uiIteration <= uiIterations;
			uiIteration++ ){
		
		//set sometimes new random value vor random variable
		if ( rand() % 2 == 0 ){
			//set variable to integer value
			cFibVariable * pVariableToChange = vecVariables[ rand() % uiNumberOfVariables ];
			pVariableToChange->setIntegerValue( rand() % 1024 - 512 );
			cout<< pVariableToChange <<"->setIntegerValue( "<<
				pVariableToChange->getIntegerValue() <<" );"<<endl;
		}else if ( rand() % 3 == 0 ){
			//set variable to double value
			cFibVariable * pVariableToChange = vecVariables[ rand() % uiNumberOfVariables ];
			pVariableToChange->setValue(
				((double)(rand() % 10000 - 5000)) / ((double)( rand() % 20 + 1)) );
			cout<< pVariableToChange <<"->setValue( "<<
				pVariableToChange->getValue() <<" );"<<endl;
		}
		
		bLowerBoundIsValue = ! pVectorArea->isVariable( 1 );
		bUpperBoundIsValue = ! pVectorArea->isVariable( 2 );
		longFib lValue1 = roundToLongFib( pVectorArea->getValue( 1 ) );
		longFib lValue2 = roundToLongFib( pVectorArea->getValue( 2 ) );
		cFibVariable * pVariable1 = pVectorArea->getVariable( 1 );
		cFibVariable * pVariable2 = pVectorArea->getVariable( 2 );
		
		if ( rand() % 10 == 0 ){
			if ( rand() % 2 == 0 ){
				pDefiningFibElement = &root;
			}else{
				pDefiningFibElement = NULL;
			}
			cVectorArea * pOldVectorArea = pVectorArea;
			//from create random new underare
			switch ( rand() % 6 ){
				case 0:{
					cout<<"pVectorArea = new cVectorArea( "<< pDefiningFibElement <<" );"<<endl;
					pVectorArea = new cVectorArea( pDefiningFibElement );
					bLowerBoundIsValue = true;
					bUpperBoundIsValue = true;
					lValue1 = 0;
					lValue2 = 0;
					pVariable1 = NULL;
					pVariable2 = NULL;
				}break;
				case 1:{
					lValue1 = rand() % 1024 - 512;
					pVariable1 = NULL;
					lValue2 = rand() % 1024 - 512;
					pVariable2 = NULL;
					bLowerBoundIsValue = true;
					bUpperBoundIsValue = true;
					cout<<"pVectorArea = new cVectorArea( "<< lValue1 <<" , "<<
						lValue2 <<", "<< pDefiningFibElement <<" );"<<endl;
					pVectorArea = new cVectorArea( lValue1 , lValue2, pDefiningFibElement );
				}break;
				case 2:{
					bLowerBoundIsValue = true;
					lValue1 = rand() % 1024 - 512;
					pVariable1 = NULL;
					if ( rand() % 10 != 0 ){
						pVariable2 = vecVariables[ rand() % uiNumberOfVariables] ;
						lValue2 = pVariable2->getIntegerValue();
						bUpperBoundIsValue = false;
					}else{//try to set NULL as variable
						pVariable2 = NULL;
						lValue2 = 0;
						bUpperBoundIsValue = true;
					}
					cout<<"pVectorArea = new cVectorArea( "<< lValue1 <<", "<<
						pVariable2 <<", "<< pDefiningFibElement <<" );"<<endl;
					pVectorArea = new cVectorArea( lValue1, pVariable2, pDefiningFibElement );
				}break;
				case 3:{
					if ( rand() % 10 != 0 ){
						bLowerBoundIsValue = false;
						pVariable1 = vecVariables[ rand() % uiNumberOfVariables ];
						lValue1 = pVariable1->getIntegerValue();
					}else{//try to set NULL as variable
						bLowerBoundIsValue = true;
						pVariable1 = NULL;
						lValue1 = 0;
					}
					bUpperBoundIsValue = true;
					lValue2 = rand() % 1024 - 512;
					pVariable2 = NULL;
					cout<<"pVectorArea = new cVectorArea( "<< pVariable1 <<", "<<
						lValue2 <<", "<< pDefiningFibElement <<" );"<<endl;
					pVectorArea = new cVectorArea( pVariable1, lValue2, pDefiningFibElement );
				}break;
				case 4:{
					if ( rand() % 10 != 0 ){
						bLowerBoundIsValue = false;
						pVariable1 = vecVariables[ rand() % uiNumberOfVariables ];
						lValue1 = pVariable1->getIntegerValue();
					}else{//try to set NULL as variable
						bLowerBoundIsValue = true;
						pVariable1 = NULL;
						lValue1 = 0;
					}
					if ( rand() % 10 != 0 ){
						bUpperBoundIsValue = false;
						pVariable2 = vecVariables[ rand() % uiNumberOfVariables ];
						lValue2 = pVariable2->getIntegerValue();
					}else{//try to set NULL as variable
						bUpperBoundIsValue = true;
						pVariable2 = NULL;
						lValue2 = 0;
					}
					cout<<"pVectorArea = new cVectorArea( "<< pVariable1 <<", "<<
						pVariable2 <<", "<< pDefiningFibElement <<" );"<<endl;
					pVectorArea = new cVectorArea( pVariable1, pVariable2, pDefiningFibElement );
				}break;
				case 5:{
					cout<<"pVectorArea = new cVectorArea( "<< pOldVectorArea <<
						", "<< pDefiningFibElement <<" );"<<endl;
					pVectorArea = new cVectorArea( *pOldVectorArea, pDefiningFibElement );
					if ( pDefiningFibElement == NULL ){
						//the defing element of the old vector is taken
						pDefiningFibElement = pOldVectorArea->getDefiningFibElement();
					}
				}break;
			};
			if ( pOldVectorArea && (pOldVectorArea != pVectorArea) ){
				//delete the old vector
				delete pOldVectorArea;
			}
		}else{
			//choos random operation
			switch ( rand() % 4 ){
				case 0:{
					lValue1 = rand() % 1024 - 512;
					pVariable1 = NULL;
					cout<<"pVectorArea->setLowerBoundValue( "<< lValue1 <<" )"<<endl;
					const bool bValueSet = pVectorArea->setLowerBoundValue( lValue1 );
					bLowerBoundIsValue = true;
					if ( ! bValueSet ){
						cerr<<"Error: Couldn't set the lower bound to the value "<<
							lValue1 <<". "<<endl;
						iReturn++;
					}
				}break;
				case 1:{
					lValue2 = rand() % 1024 - 512;
					pVariable2 = NULL;
					cout<<"pVectorArea->setUpperBoundValue( "<< lValue2 <<" );"<<endl;
					const bool bValueSet = pVectorArea->setUpperBoundValue( lValue2 );
					bUpperBoundIsValue = true;
					if ( ! bValueSet ){
						cerr<<"Error: Couldn't set the upper bound to the value "<<
							lValue2 <<". "<<endl;
						iReturn++;
					}
				}break;
				case 2:{
					if ( rand() % 10 != 0 ){
						pVariable1 = vecVariables[ rand() % uiNumberOfVariables ];
						lValue1 = pVariable1->getIntegerValue();
						cout<<"pVectorArea->setLowerBoundVariable( "<< pVariable1 <<" );"<<endl;
						const bool bValueSet = pVectorArea->setLowerBoundVariable( pVariable1 );
						bLowerBoundIsValue = false;
						if ( ! bValueSet ){
							cerr<<"Error: Couldn't set the lower bound to a variable. "<<endl;
							iReturn++;
						}
					}else{//try to set NULL
						cout<<"pVectorArea->setLowerBoundVariable( NULL );"<<endl;
						const bool bValueSet = pVectorArea->setLowerBoundVariable( NULL );
						if ( bValueSet ){
							cerr<<"Error: Could set the lower bound to NULL. "<<endl;
							iReturn++;
						}
					}
				}break;
				case 3:{
					if ( rand() % 10 != 0 ){
						pVariable2 = vecVariables[ rand() % uiNumberOfVariables ];
						lValue2 = pVariable2->getIntegerValue();
						cout<<"pVectorArea->setUpperBoundVariable( "<< pVariable2 <<" );"<<endl;
						const bool bValueSet = pVectorArea->setUpperBoundVariable( pVariable2 );
						bUpperBoundIsValue = false;
						if ( ! bValueSet ){
							cerr<<"Error: Couldn't set the upper bound to a variable. "<<endl;
							iReturn++;
						}
					}else{//try to set NULL
						cout<<"pVectorArea->setUpperBoundVariable( NULL );"<<endl;
						const bool bValueSet = pVectorArea->setUpperBoundVariable( NULL );
						if ( bValueSet ){
							cerr<<"Error: Could set the upper bound to NULL. "<<endl;
							iReturn++;
						}
					}
				}break;
			};
		}
		
		//check values
		if ( bLowerBoundIsValue == pVectorArea->isVariable( 1 ) ){
			cerr<<"Error: The first vectorelement is a "<<
				(pVectorArea->isVariable( 1 )?"variable":"value")<<" but shouldn't be. "<<endl;
			iReturn++;
		}
		if ( bUpperBoundIsValue == pVectorArea->isVariable( 2 ) ){
			cerr<<"Error: The second vectorelement is a "<<
				(pVectorArea->isVariable( 2 )?"variable":"value")<<" but shouldn't be. "<<endl;
			iReturn++;
		}
		if ( lValue1 != pVectorArea->getLowerBound() ){
			cerr<<"Error: The lowerbound should be "<< lValue1 <<
				" but is "<< pVectorArea->getLowerBound() <<". "<<endl;
			iReturn++;
		}
		if ( lValue2 != pVectorArea->getUpperBound() ){
			cerr<<"Error: The upperbound should be "<< lValue2 <<
				" but is "<< pVectorArea->getUpperBound() <<". "<<endl;
			iReturn++;
		}
		if ( lValue1 != roundToLongFib( pVectorArea->getValue( 1 ) ) ){
			cerr<<"Error: The first vectorelement (lowerbound) should be "<< lValue1 <<
				" but is "<< (longFib)(pVectorArea->getValue( 1 )) <<". "<<endl;
			iReturn++;
		}
		if ( lValue2 != roundToLongFib( pVectorArea->getValue( 2 ) ) ){
			cerr<<"Error: The second vectorelement (upperbound) should be "<< lValue2 <<
				" but is "<< (longFib)(pVectorArea->getValue( 2 )) <<". "<<endl;
			iReturn++;
		}
		if ( pVariable1 != pVectorArea->getVariable( 1 ) ){
			cerr<<"Error: The first vectorelement should be a variable "<< pVariable1 <<
				" but is "<< pVectorArea->getVariable( 1 ) <<". "<<endl;
			iReturn++;
		}
		if ( pVariable2 != pVectorArea->getVariable( 2 ) ){
			cerr<<"Error: The second vectorelement should be a variable "<< pVariable2 <<
				" but is "<< pVectorArea->getVariable( 2 ) <<". "<<endl;
			iReturn++;
		}
		
		list<longFib> liAreaValues = pVectorArea->getAreaValues();
		lValue1 = roundToLongFib( pVectorArea->getValue( 1 ) );
		lValue2 = roundToLongFib( pVectorArea->getValue( 2 ) );
		if ( lValue1 <= lValue2 ){
			//go in increasing order
			list<longFib>::iterator itrValue = liAreaValues.begin();
			for ( longFib lActualValue = lValue1; lActualValue <= lValue2;
					lActualValue++ ){
				if ( (*itrValue) != lActualValue ){
					cerr<<"Error: The "<< (lActualValue - lValue1 + 1) <<
						"'th areavalue should be "<< lActualValue <<" but is "<<
						(*itrValue) <<". "<<endl;
					iReturn++;
				}
				itrValue++;
			}
			if ( itrValue != liAreaValues.end() ){
				cerr<<"Error: Ther are "<< liAreaValues.size() <<
					" values in the area but it should be "<<
					( lValue2 - lValue1 + 1 ) <<" . "<<endl;
				iReturn++;
			}
		}else{
			//go in decreasing order
			list<longFib>::iterator itrValue = liAreaValues.begin();
			for ( longFib lActualValue = lValue1; lActualValue >= lValue2;
					lActualValue-- ){
				if ( (*itrValue) != lActualValue ){
					cerr<<"Error: The "<< (lValue1 - lActualValue + 1) <<
						"'th areavalue should be "<< lActualValue <<" but is "<<
						(*itrValue) <<". "<<endl;
					iReturn++;
				}
				itrValue++;
			}
			if ( itrValue != liAreaValues.end() ){
				cerr<<"Error: Ther are "<< liAreaValues.size() <<
					" values in the area but it should be "<<
					( lValue1 - lValue2 + 1 ) <<" . "<<endl;
				iReturn++;
			}
		}
		
		if ( pVectorArea->getDefiningFibElement() != pDefiningFibElement ){
				cerr<<"Error: Ther defining element is "<<
					pVectorArea->getDefiningFibElement()  <<" but it should be "<<
					pDefiningFibElement <<" . "<<endl;
				iReturn++;
		}
	}
	if ( pVectorArea ){
		delete pVectorArea;
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

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

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
	
	cout<<"cTypeArea typeArea;"<<endl;
	cTypeArea typeArea;
	
	//create vector domain with two elements
	cout<<"vector<cDomain*> vecDomains2( 2 );"<<endl;
	vector<cDomain*> vecDomains2( 2 );
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomainE2Nat1Nat2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat1Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomains2[ 1 ] = &vectorDomainE2Nat1Nat2;"<<endl;
	vecDomains2[ 1 ] = &vectorDomainE2Nat1Nat2;
	cout<<"cDomainVector vectorDomainE2Nat3VE2Nat1Nat2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat3VE2Nat1Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];

	cout<<"rootD2.getDomains()->addDomain( typeArea, vectorDomainE2Nat3VE2Nat1Nat2);"<<endl;
	rootD2.getDomains()->addDomain( typeArea, vectorDomainE2Nat3VE2Nat1Nat2);

	//creat defined variables to set them later in the vector
	cout<<"rootD2.setNumberOfInputVariables( 4 )"<<endl;
	rootD2.setNumberOfInputVariables( 4 );

	//create cVectorAreas to compare
	cout<<"cVectorArea vectorAreaD2Re( &emptyRoot );"<<endl;
	cVectorArea vectorAreaD2Re( &emptyRoot );
	cout<<"cVectorArea vectorAreaRD2( &rootD2 );"<<endl;
	cVectorArea vectorAreaRD2( &rootD2 );
	
	//vectors with changed values
	cout<<"cVectorArea vectorAreaRD2V2g17p2( &rootD2 );"<<endl;
	cVectorArea vectorAreaRD2V2g17p2( &rootD2 );
	vectorAreaRD2V2g17p2.setValue( 2, 17.2 );
	
	cout<<"cVectorArea vectorAreaD2RD2V2g17p2( &rootD2 );"<<endl;
	cVectorArea vectorAreaD2RD2V2g17p2( &rootD2 );
	vectorAreaD2RD2V2g17p2.setValue( 2, 17.2 );

	cout<<"cVectorArea vectorAreaD2RD2V2g17p2001( &rootD2 );"<<endl;
	cVectorArea vectorAreaD2RD2V2g17p2001( &rootD2 );
	vectorAreaD2RD2V2g17p2001.setValue( 2, 17.2001 );

	cout<<"cVectorArea vectorAreaRD2V1g17p2( &rootD2 );"<<endl;
	cVectorArea vectorAreaRD2V1g17p2( &rootD2 );
	vectorAreaRD2V1g17p2.setValue( 1, 17.2 );

	cout<<"cVectorArea vectorAreaRD2V1g1p1V2gm2p2( &rootD2 );"<<endl;
	cVectorArea vectorAreaRD2V1g1p1V2gm2p2( &rootD2 );
	vectorAreaRD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorAreaRD2V1g1p1V2gm2p2.setValue( 2, -2.2 );

	cout<<"cVectorArea vectorAreaD2RD2V1g1p1V2gm2p2( &rootD2 );"<<endl;
	cVectorArea vectorAreaD2RD2V1g1p1V2gm2p2( &rootD2 );
	vectorAreaD2RD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorAreaD2RD2V1g1p1V2gm2p2.setValue( 2, -2.2 );
	
	cout<<"cVectorArea vectorAreaRD2V1g1p1V2g2p2( &rootD2 );"<<endl;
	cVectorArea vectorAreaRD2V1g1p1V2g2p2( &rootD2 );
	vectorAreaRD2V1g1p1V2g2p2.setValue( 1, 1.1 );
	vectorAreaRD2V1g1p1V2g2p2.setValue( 2, 2.2 );

	//vectors with variables
	cFibVariable * pVariable1 = rootD2.getInputVariable( 1 );
	cFibVariable * pVariable2 = rootD2.getInputVariable( 2 );
	cFibVariable * pVariable1Re = emptyRoot.getInputVariable( 1 );

	cout<<"cVectorArea vectorAreaRD2V1gV1( &rootD2 );"<<endl;
	cVectorArea vectorAreaRD2V1gV1( &rootD2 );
	vectorAreaRD2V1gV1.setVariable( 1, pVariable1 );

	cout<<"cVectorArea vectorAreaD2RD2V1gV1( &rootD2 );"<<endl;
	cVectorArea vectorAreaD2RD2V1gV1( &rootD2 );
	vectorAreaD2RD2V1gV1.setVariable( 1, pVariable1 );

	cout<<"cVectorArea vectorAreaRD2V2gV1( &rootD2 );"<<endl;
	cVectorArea vectorAreaRD2V2gV1( &rootD2 );
	vectorAreaRD2V2gV1.setVariable( 2, pVariable1 );

	cout<<"cVectorArea vectorAreaRD2V2gV2( &rootD2 );"<<endl;
	cVectorArea vectorAreaRD2V2gV2( &rootD2 );
	vectorAreaRD2V2gV2.setVariable( 2, pVariable2 );

	cout<<"cVectorArea vectorAreaRD2V1gReV1(& rootD2 );"<<endl;
	cVectorArea vectorAreaRD2V1gReV1( &rootD2 );
	vectorAreaRD2V1gReV1.setVariable( 1, pVariable1Re );

//TODO check variable from different defining elements


	//vectors with changed values and variables
	cout<<"cVectorArea vectorAreaRD2V1gV1V2g1111( &rootD2 );"<<endl;
	cVectorArea vectorAreaRD2V1gV1V2g1111( &rootD2 );
	vectorAreaRD2V1gV1V2g1111.setVariable( 1, pVariable1 );
	vectorAreaRD2V1gV1V2g1111.setValue( 2, 1111 );

	cout<<"cVectorArea vectorAreaD2RD2V1gV1V2g1111( &rootD2 );"<<endl;
	cVectorArea vectorAreaD2RD2V1gV1V2g1111( &rootD2 );
	vectorAreaD2RD2V1gV1V2g1111.setVariable( 1, pVariable1 );
	vectorAreaD2RD2V1gV1V2g1111.setValue( 2, 1111 );

	cout<<"cVectorArea vectorAreaRD2V1gV1V2g111( &rootD2 );"<<endl;
	cVectorArea vectorAreaRD2V1gV1V2g111( &rootD2 );
	vectorAreaRD2V1gV1V2g111.setVariable( 1, pVariable1 );
	vectorAreaRD2V1gV1V2g111.setValue( 2, 111 );

	cout<<"cVectorArea vectorAreaRD2V1gV2V1g1111( &rootD2 );"<<endl;
	cVectorArea vectorAreaRD2V1g111V2gV2( &rootD2 );
	vectorAreaRD2V1g111V2gV2.setVariable( 1, pVariable2 );
	vectorAreaRD2V1g111V2gV2.setValue( 2, 1111 );

	cout<<"cVectorArea vectorAreaD2RD2V1g1111V2gV2( &rootD2 );"<<endl;
	cVectorArea vectorAreaD2RD2V1gV2V2g1111( &rootD2 );
	vectorAreaD2RD2V1gV2V2g1111.setValue( 1, 1111 );
	vectorAreaD2RD2V1gV2V2g1111.setVariable( 2, pVariable1 );

	cout<<"cVectorArea vectorAreaD2RD2V1gV1V2gV2( &rootD2 );"<<endl;
	cVectorArea vectorAreaD2RD2V1gV1V2gV2( &rootD2 );
	vectorAreaD2RD2V1gV1V2gV2.setVariable( 1, pVariable1 );
	vectorAreaD2RD2V1gV1V2gV2.setVariable( 2, pVariable2 );

	cout<<"cVectorProperty vectorProperty( 1 );"<<endl;
	cVectorProperty vectorProperty( 1 );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with vectorAreaD3
	cFibVector * actualVector = &vectorAreaD2Re;
	string szActualVectorName = "vectorAreaD2Re";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );


	//compare with vectorAreaD2Re
	actualVector = &vectorAreaRD2;
	szActualVectorName = "vectorAreaRD2";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaRD2V2g17p2
	actualVector = &vectorAreaRD2V2g17p2;
	szActualVectorName = "vectorAreaRD2V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaRD2V2g17p2
	actualVector = &vectorAreaD2RD2V2g17p2;
	szActualVectorName = "vectorAreaD2RD2V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaD2RD2V2g17p2001
	actualVector = &vectorAreaD2RD2V2g17p2001;
	szActualVectorName = "vectorAreaD2RD2V2g17p2001";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaD2RD2V2g17p2001
	actualVector = &vectorAreaRD2V1g17p2;
	szActualVectorName = "vectorAreaRD2V1g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaRD2V1g1p1V2gm2p2
	actualVector = &vectorAreaRD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorAreaRD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaD2RD2V1g1p1V2gm2p2
	actualVector = &vectorAreaD2RD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorAreaD2RD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaD2RD2V1g1p1V2gm2p2
	actualVector = &vectorAreaRD2V1g1p1V2g2p2;
	szActualVectorName = "vectorAreaRD2V1g1p1V2g2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaRD2V1gV1
	actualVector = &vectorAreaRD2V1gV1;
	szActualVectorName = "vectorAreaRD2V1gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaD2RD2V1gV1
	actualVector = &vectorAreaD2RD2V1gV1;
	szActualVectorName = "vectorAreaD2RD2V1gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaRD2V2gV1
	actualVector = &vectorAreaRD2V2gV1;
	szActualVectorName = "vectorAreaRD2V2gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaRD2V2gV2
	actualVector = &vectorAreaRD2V2gV2;
	szActualVectorName = "vectorAreaRD2V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaRD2V1gReV1
	actualVector = &vectorAreaRD2V1gReV1;
	szActualVectorName = "vectorAreaRD2V1gReV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaRD2V1gV1V2g1111
	actualVector = &vectorAreaRD2V1gV1V2g1111;
	szActualVectorName = "vectorAreaRD2V1gV1V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaD2RD2V1gV1V2g1111
	actualVector = &vectorAreaD2RD2V1gV1V2g1111;
	szActualVectorName = "vectorAreaD2RD2V1gV1V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaRD2V1gV1V2g111
	actualVector = &vectorAreaRD2V1gV1V2g111;
	szActualVectorName = "vectorAreaRD2V1gV1V2g111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaRD2V1g111V2gV2
	actualVector = &vectorAreaRD2V1g111V2gV2;
	szActualVectorName = "vectorAreaRD2V1g111V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaD2RD2V1gV2V2g1111
	actualVector = &vectorAreaD2RD2V1gV2V2g1111;
	szActualVectorName = "vectorAreaD2RD2V1gV2V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorAreaD2RD2V1gV1V2gV2
	actualVector = &vectorAreaD2RD2V1gV1V2gV2;
	szActualVectorName = "vectorAreaD2RD2V1gV1V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorProperty
	actualVector = &vectorProperty;
	szActualVectorName = "vectorProperty";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2Re, "vectorAreaD2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2, "vectorAreaRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2g17p2, "vectorAreaRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2, "vectorAreaD2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V2g17p2001, "vectorAreaD2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g17p2, "vectorAreaRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2gm2p2, "vectorAreaRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1g1p1V2gm2p2, "vectorAreaD2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g1p1V2g2p2, "vectorAreaRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1, "vectorAreaRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1, "vectorAreaD2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV1, "vectorAreaRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V2gV2, "vectorAreaRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gReV1, "vectorAreaRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g1111, "vectorAreaRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2g1111, "vectorAreaD2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1gV1V2g111, "vectorAreaRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaRD2V1g111V2gV2, "vectorAreaRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV2V2g1111, "vectorAreaD2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorAreaD2RD2V1gV1V2gV2, "vectorAreaD2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	return iReturn;
}


/**
 * This method tests the createInstance() method of the cVectorArea class.
 *
 * methods tested:
 * 	- createInstance()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCreateInstance( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 1 element"<<endl;

	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeArea typeArea;"<<endl;
	cTypeArea typeArea;
	
	//create vector domain with two elements
	cout<<"vector<cDomain*> vecDomains2( 2 );"<<endl;
	vector<cDomain*> vecDomains2( 2 );
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomainE2Nat1Nat2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat1Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomains2[ 1 ] = &vectorDomainE2Nat1Nat2;"<<endl;
	vecDomains2[ 1 ] = &vectorDomainE2Nat1Nat2;
	cout<<"cDomainVector vectorDomainE2Nat3VE2Nat1Nat2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat3VE2Nat1Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];

	cout<<"rootD2.getDomains()->addDomain( typeArea, vectorDomainE2Nat3VE2Nat1Nat2);"<<endl;
	rootD2.getDomains()->addDomain( typeArea, vectorDomainE2Nat3VE2Nat1Nat2);

	
	cout<<"cVectorArea vecArea1RD2( &rootD2 );"<<endl;
	cVectorArea vecArea1RD2( &rootD2 );

	cout<<"cFibVector * vectorInstanceD1 = vecArea1RD2.createInstance( 1 );"<<endl;
	cFibVector * vectorInstanceD1 = vecArea1RD2.createInstance( 1 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorArea
	if ( vectorInstanceD1->getVectorType() == "subarea" ){
	
		cout<<"The name of the subarea vector is correctly \"subarea\" . "<<endl;
	}else{
		cerr<<"Error: The name of the subarea vector is "<<
			vectorInstanceD1->getVectorType()<<" but should be \"subarea\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorArea
	cTypeElement * pTypeSubarea = vectorInstanceD1->getElementType();
	if ( typeArea == (*pTypeSubarea) ){
	
		cout<<"The type of the subarea vector is correctly equal to typeArea. "<<endl;
	}else{
		cerr<<"Error: The type of subarea vector not equal to typeArea ."<<endl;
		iReturn++;
	}
	delete pTypeSubarea;
	
	//check the getNumberOfElements() methode from cVectorArea
	if ( vectorInstanceD1->getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the subarea vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the subarea vector is "<<
			vectorInstanceD1->getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the subarea vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD1->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD1->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is an variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD1->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is "<<vectorInstanceD1->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorArea
	if ( vectorInstanceD1->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the subarea vector."<<endl;
	}else if ( &rootD2 == vectorInstanceD1->getDefiningFibElement() ){
	
		cerr<<"Error: The rootD2 is the defining element for the subarea vector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is a defining element for the subarea vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorArea
	if ( vectorInstanceD1->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the subarea vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the subarea vector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 3 elements"<<endl;


	cout<<"cFibVector * vectorInstanceD3 = vecArea1RD2.createInstance( 3 );"<<endl;
	cFibVector * vectorInstanceD3 = vecArea1RD2.createInstance( 3 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorArea
	if ( vectorInstanceD3->getVectorType() == "subarea" ){
	
		cout<<"The name of the subarea vector is correctly \"subarea\" . "<<endl;
	}else{
		cerr<<"Error: The name of the subarea vector is "<<
			vectorInstanceD3->getVectorType()<<" but should be \"subarea\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorArea
	pTypeSubarea = vectorInstanceD3->getElementType();
	if ( typeArea == (*pTypeSubarea) ){
	
		cout<<"The type of the subarea vector is correctly equal to typeArea. "<<endl;
	}else{
		cerr<<"Error: The type of subarea vector not equal to typeArea ."<<endl;
		iReturn++;
	}
	delete pTypeSubarea;
	
	//check the getNumberOfElements() methode from cVectorArea
	if ( vectorInstanceD3->getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the subarea vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the subarea vector is "<<
			vectorInstanceD3->getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the subarea vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD3->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD3->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is an variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD3->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is "<<vectorInstanceD3->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorArea
	if ( vectorInstanceD3->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the subarea vector."<<endl;
	}else if ( &rootD2 == vectorInstanceD3->getDefiningFibElement() ){
	
		cerr<<"Error: The rootD2 is the defining element for the subarea vector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is an defining element for the subarea vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorArea
	if ( vectorInstanceD3->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the subarea vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the subarea vector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD3;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 5 elements and rootD2 as an defining element"<<endl;

	cout<<"cFibVector * vectorInstanceD2RD2 = vecArea1RD2.createInstance( 5, &rootD2 );"<<endl;
	cFibVector * vectorInstanceD2RD2 = vecArea1RD2.createInstance( 5, &rootD2 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorArea
	if ( vectorInstanceD2RD2->getVectorType() == "subarea" ){
	
		cout<<"The name of the subarea vector is correctly \"subarea\" . "<<endl;
	}else{
		cerr<<"Error: The name of the subarea vector is "<<
			vectorInstanceD2RD2->getVectorType()<<" but should be \"subarea\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorArea
	pTypeSubarea = vectorInstanceD2RD2->getElementType();
	if ( typeArea == (*pTypeSubarea) ){
	
		cout<<"The type of the subarea vector is correctly equal to typeArea. "<<endl;
	}else{
		cerr<<"Error: The type of subarea vector not equal to typeArea ."<<endl;
		iReturn++;
	}
	delete pTypeSubarea;
	
	//check the getNumberOfElements() methode from cVectorArea
	if ( vectorInstanceD2RD2->getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the subarea vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the subarea vector is "<<
			vectorInstanceD2RD2->getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the subarea vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD2RD2->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD2RD2->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly not an variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is an variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD2RD2->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"subarea vector is "<<vectorInstanceD2RD2->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorArea
	if ( vectorInstanceD2RD2->getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the subarea vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vectorInstanceD2RD2->getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the subarea vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the subarea vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorArea
	if ( vectorInstanceD2RD2->getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the subarea vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE2Nat1Nat2 == (*(vectorInstanceD2RD2->getDomain())) ){
	
		cout<<"The vectorDomainE2Nat1Nat2 is the domain for the subarea vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE2Nat1Nat2 is not the domain for the subarea vector."<<endl;
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
	
	TiXmlDocument xmlDocVectorArea( szFilename );
	bool loadOkay = xmlDocVectorArea.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocVectorArea );
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
 * This method tests the storeXml() method of the cVectorArea class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an empty 2 d vector"<<endl;
	
	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeArea typeArea;"<<endl;
	cTypeArea typeArea;
	
	//create vector domain with two elements
	cout<<"vector<cDomain*> vecDomains2( 2 );"<<endl;
	vector<cDomain*> vecDomains2( 2 );
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomainE2Nat1Nat2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat1Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomains2[ 1 ] = &vectorDomainE2Nat1Nat2;"<<endl;
	vecDomains2[ 1 ] = &vectorDomainE2Nat1Nat2;
	cout<<"cDomainVector vectorDomainE2Nat3VE2Nat1Nat2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat3VE2Nat1Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];

	cout<<"rootD2.getDomains()->addDomain( typeArea, vectorDomainE2Nat3VE2Nat1Nat2 );"<<endl;
	rootD2.getDomains()->addDomain( typeArea, vectorDomainE2Nat3VE2Nat1Nat2 );

	//creat defined variables to set them later in the vector
	cout<<"rootD2.setNumberOfInputVariables( 6 )"<<endl;
	rootD2.setNumberOfInputVariables( 6 );

	cout<<"cVectorArea vecAreaRD2( &rootD2 );"<<endl;
	cVectorArea vecAreaRD2( &rootD2 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	const char * szVectorPostion = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorAreaEmpty.xml" );
	ofstream fileVectorPostion( szVectorPostion );
	
	bool bStoreSuccesfull = vecAreaRD2.storeXml( fileVectorPostion );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorPostion <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorPostion <<"\" failed."<<endl;
		iReturn++;
	}
	
	vector<char> vecElementTypeArea( 2, 'w' );
	vector<double> vecValuesArea( 2, 0.0 );
	
	iReturn += testXmlVector( szVectorPostion, "subarea",
		2, vecElementTypeArea, vecValuesArea );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 2 d vector one value set"<<endl;
	
	cout<<"vecAreaRD2.setValue( 1, 111 )"<<endl;
	vecAreaRD2.setValue( 1, 111 );
	vecElementTypeArea[0] = 'w';
	vecValuesArea[0] = 111;
	
	szFileNameBuffer[0] = 0;
	const char * szVectorAreaRD2V1g111 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorAreaRD2V1g111.xml" );
	ofstream fileVectorAreaRD2V1g111n( szVectorAreaRD2V1g111 );
	
	bStoreSuccesfull = vecAreaRD2.storeXml( fileVectorAreaRD2V1g111n );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorAreaRD2V1g111 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorAreaRD2V1g111 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorAreaRD2V1g111, "subarea",
		2, vecElementTypeArea, vecValuesArea );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 2 d vector all value set"<<endl;
	
	cout<<"vecAreaRD2.setValue( 2, 123.456 )"<<endl;
	vecAreaRD2.setValue( 2, 123.456  );
	vecElementTypeArea[1] = 'w';
	vecValuesArea[1] = 123.456;

	szFileNameBuffer[0] = 0;
	const char * szVectorAreaRD2T3 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorAreaRD2T3.xml" );
	ofstream fileVectorAreaRD2T3( szVectorAreaRD2T3 );
	
	bStoreSuccesfull = vecAreaRD2.storeXml( fileVectorAreaRD2T3 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorAreaRD2T3 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorAreaRD2T3 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorAreaRD2T3, "subarea",
		2, vecElementTypeArea, vecValuesArea );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 2 d vector with variables"<<endl;
	
	cout<<"cFibVariable * pVariable1 = rootD2.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootD2.getInputVariable( 1 );
	cout<<"pVariable1->setValue( 1 );"<<endl;
	pVariable1->setValue( 1 );
	cout<<"cFibVariable * pVariable2 = rootD2.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = rootD2.getInputVariable( 2 );
	cout<<"pVariable2->setIntegerValue( 2 );"<<endl;
	pVariable2->setIntegerValue( 2 );
	cout<<"cFibVariable * pVariable3 = rootD2.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = rootD2.getInputVariable( 3 );
	cout<<"pVariable3->setIntegerValue( 3 );"<<endl;
	pVariable3->setIntegerValue( 3 );
	
	cout<<"vecAreaRD2.setVariable( 1, pVariable1 )"<<endl;
	vecAreaRD2.setVariable( 1, pVariable1  );
	vecElementTypeArea[0] = 'v';
	vecValuesArea[0] = 1;
	cout<<"vecAreaRD2.setVariable( 2, pVariable2 )"<<endl;
	vecAreaRD2.setVariable( 2, pVariable2 );
	vecElementTypeArea[1] = 'v';
	vecValuesArea[1] = 2;

	szFileNameBuffer[0] = 0;
	const char * szVectorAreaRD2T4 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorAreaRD2T4.xml" );
	ofstream fileVectorAreaRD2T4( szVectorAreaRD2T4 );
	
	bStoreSuccesfull = vecAreaRD2.storeXml( fileVectorAreaRD2T4 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorAreaRD2T4 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorAreaRD2T4 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorAreaRD2T4, "subarea",
		2, vecElementTypeArea, vecValuesArea );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 2 d vector with variables and values"<<endl;
	
	cout<<"vecAreaRD2.setVariable( 1, pVariable1 )"<<endl;
	vecAreaRD2.setVariable( 1, pVariable1  );
	vecElementTypeArea[0] = 'v';
	vecValuesArea[0] = 1;
	cout<<"vecAreaRD2.setValue( 2, -0.00124 )"<<endl;
	vecAreaRD2.setValue( 2, -0.00124 );
	vecElementTypeArea[1] = 'w';
	vecValuesArea[1] = -0.00124;

	szFileNameBuffer[0] = 0;
	const char * szVectorAreaRD2T5 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorAreaRD2T5.xml" );
	ofstream fileVectorAreaRD2T5( szVectorAreaRD2T5 );
	
	bStoreSuccesfull = vecAreaRD2.storeXml( fileVectorAreaRD2T5 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorAreaRD2T5 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorAreaRD2T5 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorAreaRD2T5, "subarea",
		2, vecElementTypeArea, vecValuesArea );


	return iReturn;
}



/**
 * This method tests the store methods of the class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an subarea vector with 2 elements"<<endl;

	cout<<"cVectorArea vecAreaPD2;"<<endl;
	cVectorArea vecAreaPD2;

	//test get compressed size
	unsigned int uiCompressedSize = 2 * 17;
	if ( (unsigned int)(vecAreaPD2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecAreaPD2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecAreaPD2.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = vecAreaPD2.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cAreaE0[] = { (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cAreaE0, 5 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an subarea vector with 2 elements"<<endl;

	cout<<"cVectorArea vecArea2E2Ch;"<<endl;
	cVectorArea vecArea2E2Ch;
	cout<<"vecArea2E2Ch.setValue( 1, 4 );"<<endl;
	vecArea2E2Ch.setValue( 1, 4 );
	cout<<"vecArea2E2Ch.setValue( 2, 6 );"<<endl;
	vecArea2E2Ch.setValue( 2, 6 );

	//test get compressed size
	uiCompressedSize = 2 * 17;
	if ( (unsigned int)(vecArea2E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecArea2E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecArea2E2Ch.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = vecArea2E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cAreaE2[] = { (char)0x08, (char)0x00, (char)0x18, (char)0x00, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cAreaE2, 5 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an subarea vector with variables"<<endl;

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

	cout<<"vecArea2E2Ch.setVariable( 1, pVariable1);"<<endl;
	vecArea2E2Ch.setVariable( 1, pVariable1);
	cout<<"vecArea2E2Ch.setVariable( 2, pVariable2);"<<endl;
	vecArea2E2Ch.setVariable( 2, pVariable2);

	//test get compressed size
	uiCompressedSize = 2 * 9;
	if ( (unsigned int)(vecArea2E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecArea2E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecArea2E2Var.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = vecArea2E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cAreaE2Var[] = { (char)0x03, (char)0x0A, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cAreaE2Var, 3 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an subarea vector with domains"<<endl;

	cout<<"cTypeArea typeArea;"<<endl;
	cTypeArea typeArea;
	
	//create vector domain with two elements
	cout<<"vector<cDomain*> vecDomains2( 2 );"<<endl;
	vector<cDomain*> vecDomains2( 2 );
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomainE2Nat1Nat2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat1Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomains2[ 1 ] = &vectorDomainE2Nat1Nat2;"<<endl;
	vecDomains2[ 1 ] = &vectorDomainE2Nat1Nat2;
	cout<<"cDomainVector vectorDomainE2Nat3VE2Nat1Nat2( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat3VE2Nat1Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];

	cout<<"rootD2.getDomains()->addDomain( typeArea, vectorDomainE2Nat3VE2Nat1Nat2);"<<endl;
	rootD2.getDomains()->addDomain( typeArea, vectorDomainE2Nat3VE2Nat1Nat2);

	cout<<"cTypeVariable typeVariable;"<<endl;
	cTypeVariable typeVariable;

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB3( 3 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB3( 3 );

	cout<<"rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB3);"<<endl;
	rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB3);

	cout<<"vecArea2E2Ch.setDefiningFibElement( &rootD2 );"<<endl;
	vecArea2E2Ch.setDefiningFibElement( &rootD2 );
	
	cout<<"vecArea2E2Ch.setValue( 2, 3);"<<endl;
	vecArea2E2Ch.setValue( 2, 3);

	//test get compressed size
	uiCompressedSize = 4 + 3;
	if ( (unsigned int)(vecArea2E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecArea2E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecArea2E2Dom.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = vecArea2E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cAreaE2Dom[] = { (char)ucRestBitCorrect };
	iReturn += compareBytsWithFile( szFileNameBuffer, cAreaE2Dom, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an subarea vector with a restbit of 4"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecArea2E2R4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x0F;
	cNumberOfRestBit = 4;
	bStoreSuccesfull = vecArea2E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = (char)0x06;
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
	const char cVecArea1E3R4[] = { (char)0x3F, (char)0x06 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cVecArea1E3R4, 2 );

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the operator=() method on an subarea vector with values set"<<endl;

	cout<<"cVectorArea vecAreaDestination;"<<endl;
	cVectorArea vecAreaDestination;
	
	cout<<"cVectorArea vectorAreaValues;"<<endl;
	cVectorArea vectorAreaValues;
	cout<<"vectorAreaValues.setValue( 1, 1.1 );"<<endl;
	vectorAreaValues.setValue( 1, 1.1 );
	cout<<"vectorAreaValues.setValue( 2, -2.2 );"<<endl;
	vectorAreaValues.setValue( 2, -2.2 );
	
	cout<<"vecAreaDestination = vectorAreaValues;"<<endl;
	vecAreaDestination = vectorAreaValues;
	
	if ( vecAreaDestination == vectorAreaValues ){
	
		cout<<"The vectorAreaValues is equal to the vectorAreaValues . "<<endl;
	}else{
		cerr<<"Error: The vectorAreaValues is not equal to the vectorAreaValues ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the operator=() method on an subarea vector with variables set"<<endl;

	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;
	
	//creat defined variables to set them later in the vector
	cout<<"emptyRoot.setNumberOfInputVariables( 2 )"<<endl;
	emptyRoot.setNumberOfInputVariables( 2 );
	cFibVariable * pVariable1 = emptyRoot.getInputVariable( 1 );
	cFibVariable * pVariable2 = emptyRoot.getInputVariable( 2 );

	cout<<"cVectorArea vectorAreaVariables( &emptyRoot );"<<endl;
	cVectorArea vectorAreaVariables( &emptyRoot );
	cout<<"vectorAreaVariables.setVariable( 1, pVariable1 );"<<endl;
	vectorAreaVariables.setVariable( 1, pVariable1 );
	cout<<"vectorAreaVariables.setVariable( 2, pVariable2 );"<<endl;
	vectorAreaVariables.setVariable( 2, pVariable2 );

	cout<<"vecAreaDestination = vectorAreaVariables;"<<endl;
	vecAreaDestination = vectorAreaVariables;
	
	if ( vecAreaDestination == vectorAreaVariables ){
	
		cout<<"The vectorAreaValues is equal to the vectorAreaVariables . "<<endl;
	}else{
		cerr<<"Error: The vectorAreaValues is not equal to the vectorAreaVariables ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the operator=() method on an position vector with 3 elements"<<endl;

	//creat defined variables to set them later in the vector
	cout<<"cVectorPosition vectorPositionD3( 3 );"<<endl;
	cVectorPosition vectorPositionD3( 3 );
	cout<<"vectorPositionD3.setValue( 1, 1 );"<<endl;
	vectorPositionD3.setValue( 1, 1 );
	cout<<"vectorPositionD3.setValue( 2, 2 );"<<endl;
	vectorPositionD3.setValue( 2, 2 );
	cout<<"vectorPositionD3.setValue( 3, 3 );"<<endl;
	vectorPositionD3.setValue( 3, 3 );

	cout<<"cVectorArea vectorAreaValues2;"<<endl;
	cVectorArea vectorAreaValues2;
	cout<<"vectorAreaValues2.setValue( 1, 1 );"<<endl;
	vectorAreaValues2.setValue( 1, 1 );
	cout<<"vectorAreaValues2.setValue( 2, 2 );"<<endl;
	vectorAreaValues2.setValue( 2, 2 );

	
	cout<<"vecAreaDestination = vectorPositionD3;"<<endl;
	vecAreaDestination = vectorPositionD3;
	
	if ( vecAreaDestination != vectorPositionD3 ){
	
		cout<<"The vectorAreaValues is correctly not equal to the vectorPositionD3 . "<<endl;
	}else{
		cerr<<"Error: The vectorAreaValues is equal to the vectorPositionD3 ."<<endl;
		iReturn++;
	}

	if ( vecAreaDestination == vectorAreaValues2 ){
	
		cout<<"The vectorAreaValues is equal to the vectorAreaValues2 . "<<endl;
	}else{
		cerr<<"Error: The vectorAreaValues is not equal to the vectorAreaValues2 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the operator=() method on an position vector with 1 element"<<endl;

	//creat defined variables to set them later in the vector
	cout<<"cVectorPosition vectorPositionD1( 1 );"<<endl;
	cVectorPosition vectorPositionD1( 1 );
	cout<<"vectorPositionD1.setValue( 1, 10 );"<<endl;
	vectorPositionD1.setValue( 1, 10 );

	cout<<"vectorAreaValues2.setValue( 1, 10 );"<<endl;
	vectorAreaValues2.setValue( 1, 10 );
	cout<<"vectorAreaValues2.setValue( 2, 0 );"<<endl;
	vectorAreaValues2.setValue( 2, 0 );
	
	cout<<"vecAreaDestination = vectorPositionD1;"<<endl;
	vecAreaDestination = vectorPositionD1;
	
	if ( vecAreaDestination != vectorPositionD1 ){
	
		cout<<"The vectorAreaValues is correctly not equal to the vectorPositionD1 . "<<endl;
	}else{
		cerr<<"Error: The vectorAreaValues is equal to the vectorPositionD1 ."<<endl;
		iReturn++;
	}

	if ( vecAreaDestination == vectorAreaValues2 ){
	
		cout<<"The vectorAreaValues is equal to the vectorAreaValues2 . "<<endl;
	}else{
		cerr<<"Error: The vectorAreaValues is not equal to the vectorAreaValues2 ."<<endl;
		iReturn++;
	}


	return iReturn;
}
























