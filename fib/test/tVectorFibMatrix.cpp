/**
 * @file tVectorFibMatrix
 * file name: tVectorFibMatrix.cpp
 * @author Betti Oesterholz
 * @date 06.12.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cVectorFibMatrix.
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
 * This file contains the test for the class cVectorFibMatrix,
 * which represents the vector for positions.
 *
 *
 *
 *  What's tested of class cVectorFibMatrix:
 * 	- cVectorFibMatrix( unsignedIntFib iNumberOfElements=2, cFibElement * pDefiningMatrixElement=NULL );
 * 	- cVectorFibMatrix( cFibMatrix & definingMatrixElement );
 * 	- cVectorFibMatrix( const cVectorFibMatrix & vector, cFibElement * definingFibElement = NULL );
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
07.01.2012  Oesterholz  created
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/


#include "version.h"

#include "cVectorFibMatrix.h"
#include "cVectorArea.h"
#include "cVectorProperty.h"
#include "cTypeFibMatrix.h"
#include "cTypeVariable.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainIntegerBit.h"
#include "cDomainVector.h"
#include "cDomainVectorOpenEnd.h"
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
int testValueDomain( unsigned long &ulTestphase );
int testGetMatrixDefiningElement( unsigned long &ulTestphase );
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
	
	cout<<endl<<"Running Test for cVectorFibMatrix methods"<<endl;
	cout<<      "========================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testDomain( ulTestphase );
	iReturn += testValueDomain( ulTestphase );
	iReturn += testGetMatrixDefiningElement( ulTestphase );
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
 * This method tests the constructors of the cVectorFibMatrix class.
 *
 * constructors tested:
 * 	- cVectorFibMatrix( unsignedIntFib iNumberOfElements=2, cFibElement * pDefiningMatrixElement=NULL );
 * 	- cVectorFibMatrix( cFibMatrix & definingMatrixElement );
 * 	- cVectorFibMatrix( const cVectorFibMatrix & vector, cFibElement * definingFibElement = NULL );
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cVectorFibMatrix"<<endl;

	cout<<"cTypeFibMatrix typeFibMatrix;"<<endl;
	cTypeFibMatrix typeFibMatrix;
	
	cout<<"cVectorFibMatrix vecFibMatrix;"<<endl;
	cVectorFibMatrix vecFibMatrix;


	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrix.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrix.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	
	//check the getElementType() methode from cVectorFibMatrix
	cTypeElement * pTypeFibMatrix = vecFibMatrix.getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrix.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrix.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibMatrix.getNumberOfElements(); 
			uiActualElement++ ){
		
		if ( ! vecFibMatrix.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibMatrix.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vecFibMatrix.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrix.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the matrix element vector."<<endl;
		iReturn++;
	}

	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrix.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the matrix element vector."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibMatrix with 3 elements"<<endl;

	cout<<"cVectorFibMatrix vecFibMatrixE3( 3 );"<<endl;
	cVectorFibMatrix vecFibMatrixE3( 3 );


	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3.getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibMatrixE3.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibMatrix.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibMatrixE3.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vecFibMatrixE3.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrixE3.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the matrix element vector."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibMatrix with 4 elements and an defining element"<<endl;

	cout<<"cRoot emptyRoot;"<<endl;
	cRoot emptyRoot;

	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Nat1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Nat1( 1 );
	cout<<"vecDomainsE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomainE1Nat1( vecDomainsE1Nat1 );"<<endl;
	cDomainVector vectorDomainE1Nat1( vecDomainsE1Nat1 );
	delete vecDomainsE1Nat1[ 0 ];
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat2Nat3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat2Nat3( 2 );
	cout<<"vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat2Nat3 );
	delete vecDomainsE2Nat2Nat3[ 0 ];
	delete vecDomainsE2Nat2Nat3[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE4Na2Nat3VE2Nat2Nat3VE1Nat1( 4 );"<<endl;
	vector<cDomain*> vecDomainsE4Na2Nat3VE2Nat2Nat3VE1Nat1( 4 );
	cout<<"vecDomainsE4Na2Nat3VE2Nat2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE4Na2Nat3VE2Nat2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE4Na2Nat3VE2Nat2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE4Na2Nat3VE2Nat2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE4Na2Nat3VE2Nat2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat2Nat3;"<<endl;
	vecDomainsE4Na2Nat3VE2Nat2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat2Nat3;
	cout<<"vecDomainsE4Na2Nat3VE2Nat2Nat3VE1Nat1[ 3 ] = &vectorDomainE1Nat1;"<<endl;
	vecDomainsE4Na2Nat3VE2Nat2Nat3VE1Nat1[ 3 ] = &vectorDomainE1Nat1;
	cout<<"cDomainVector vectorDomainE4Na2Nat3VE2Nar2Nar3E1Nat1( vecDomainsE4Na2Nat3VE2Nat2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE4Na2Nat3VE2Nar2Nar3E1Nat1( vecDomainsE4Na2Nat3VE2Nat2Nat3VE1Nat1 );
	delete vecDomainsE4Na2Nat3VE2Nat2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE4Na2Nat3VE2Nat2Nat3VE1Nat1[ 1 ];

	cout<<"rootD2.getDomains()->addDomain( typeFibMatrix, vectorDomainE4Na2Nat3VE2Nar2Nar3E1Nat1 );"<<endl;
	rootD2.getDomains()->addDomain( typeFibMatrix, vectorDomainE4Na2Nat3VE2Nar2Nar3E1Nat1 );

	
	cout<<"cVectorFibMatrix vecFibMatrixE4RD2 = cVectorFibMatrix( 4, &rootD2 );"<<endl;
	cVectorFibMatrix vecFibMatrixE4RD2 = cVectorFibMatrix( 4, &rootD2 );

	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE4RD2.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE4RD2.getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE4RD2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibMatrixE4RD2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibMatrixE4RD2.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibMatrixE4RD2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vecFibMatrixE4RD2.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecFibMatrixE4RD2.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE1Nat1 == (*(vecFibMatrixE4RD2.getDomain())) ){
	
		cout<<"The vectorDomainE1Nat1 is the domain for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1Nat1 is not the domain for the matrix element vector."<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibMatrix with a matrix element as defining element"<<endl;

	cout<<"cFibMatrix fibMatrixV4( 1, 4 );"<<endl;
	cFibMatrix fibMatrixV4( 1, 4 );
	
	cout<<"cVectorFibMatrix vecFibMatrixE4( 4, &fibMatrixV4 );"<<endl;
	cVectorFibMatrix vecFibMatrixE4( 4, &fibMatrixV4 );

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE4.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE4.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE4.getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE4.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE4.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibMatrixE4.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibMatrixE4.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibMatrixE4.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vecFibMatrixE4.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE4.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV4 == vecFibMatrixE4.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrixE4.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the matrix element vector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibMatrix with a matrix element as defining element, wich has other than the vector elemnts defined variables"<<endl;
	
	cout<<"cVectorFibMatrix vecFibMatrixE3V4( 3, &fibMatrixV4 );"<<endl;
	cVectorFibMatrix vecFibMatrixE3V4( 3, &fibMatrixV4 );

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3V4.getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibMatrixE3V4.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibMatrixE3V4.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibMatrixE3V4.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vecFibMatrixE3V4.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV4 == vecFibMatrixE3V4.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the matrix element vector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibMatrix with a matrix element as defining element, wich has domain number set"<<endl;
	
	cout<<"cRoot rootDom4;"<<flush<<endl;
	cRoot rootDom4;
	
	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix, vectorDomainE4Na2Nat3VE2Nar2Nar3E1Nat1 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix, vectorDomainE4Na2Nat3VE2Nar2Nar3E1Nat1 );

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
	
	cout<<"vecDomainsE2Nat2Nat3[ 0 ] = new cDomainIntegerBit( 5 );"<<endl;
	vecDomainsE2Nat2Nat3[ 0 ] = new cDomainIntegerBit( 5 );
	cout<<"vecDomainsE2Nat2Nat3[ 1 ] = new cDomainIntegerBit( 7 );"<<endl;
	vecDomainsE2Nat2Nat3[ 1 ] = new cDomainIntegerBit( 7 );
	cout<<"cDomainVector vectorDomainE2Int5Int7( vecDomainsE2Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE2Int5Int7( vecDomainsE2Nat2Nat3 );
	delete vecDomainsE2Nat2Nat3[ 0 ];
	delete vecDomainsE2Nat2Nat3[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 4 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int5Int7;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int5Int7;
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int2Int3;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int2Int3;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibMatrix typeFibMatrix4( 4 );"<<endl;
	cTypeFibMatrix typeFibMatrix4( 4 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix4, vectorDomainE3Na4Nat5VE2NInt2Int3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix4, vectorDomainE3Na4Nat5VE2NInt2Int3 );
	
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

	cout<<"vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 7 );"<<endl;
	vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 7 );
	cout<<"vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"cDomainVector vectorDomainE2Int7Int5( vecDomainsE2Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE2Int7Int5( vecDomainsE2Nat2Nat3 );
	delete vecDomainsE2Nat2Nat3[ 0 ];
	delete vecDomainsE2Nat2Nat3[ 1 ];

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int7Int5;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int7Int5;
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int4Int5;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int4Int5;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibMatrix typeFibMatrix5( 5 );"<<endl;
	cTypeFibMatrix typeFibMatrix5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix5, vectorDomainE3Na4Nat5VE2NInt4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix5, vectorDomainE3Na4Nat5VE2NInt4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"cDomainVector vectorDomainE2Nat4Nat4( vecDomainsE2Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE2Nat4Nat4( vecDomainsE2Nat2Nat3 );
	delete vecDomainsE2Nat2Nat3[ 0 ];
	delete vecDomainsE2Nat2Nat3[ 1 ];
	
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat4Nat4;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat4Nat4;
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainOE1Int8;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainOE1Int8;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibMatrix typeFibMatrix6( 6 );"<<endl;
	cTypeFibMatrix typeFibMatrix6( 6 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix6, vectorDomainE3Na4Nat5VOE1Int8 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix6, vectorDomainE3Na4Nat5VOE1Int8 );
	
	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];
	
	
	cout<<"cFibMatrix fibMatrixV3Dom5rootDom4( 1, 3, NULL, &rootDom4 );"<<endl;
	cFibMatrix fibMatrixV3Dom5rootDom4( 1, 3, NULL, &rootDom4 );
	cout<<"fibMatrixV3Dom5rootDom4.setDomainNr( 5 );"<<endl;
	fibMatrixV3Dom5rootDom4.setDomainNr( 5 );
	
	cout<<"cVectorFibMatrix vecFibMatrixE3V4Dom5( 2, &fibMatrixV3Dom5rootDom4 );"<<endl;
	cVectorFibMatrix vecFibMatrixE3V4Dom5( 2, &fibMatrixV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	if ( typeFibMatrix5 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix5. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix5 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibMatrixE3V4Dom5.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibMatrixE3V4Dom5.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibMatrixE3V4Dom5.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vecFibMatrixE3V4Dom5.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3Dom5rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3Dom5rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3Dom5rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE2Int4Int5 == (*(vecFibMatrixE3V4Dom5.getDomain())) ){
	
		cout<<"The vectorDomainE2Int4Int5 is the domain for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibMatrix with a matrix element as defining element, wich has a not existig domain number set"<<endl;
	
	cout<<"fibMatrixV3Dom5rootDom4.setDomainNr( 13 );"<<endl;
	fibMatrixV3Dom5rootDom4.setDomainNr( 13 );
	
	cout<<"cVectorFibMatrix vecFibMatrixE3V4Dom13( 2, &fibMatrixV3Dom5rootDom4 );"<<endl;
	cVectorFibMatrix vecFibMatrixE3V4Dom13( 2, &fibMatrixV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom13.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom13.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	cout<<"cTypeFibMatrix typeFibMatrix13( 13 ); "<<endl;
	cTypeFibMatrix typeFibMatrix13( 13 );
	pTypeFibMatrix = vecFibMatrixE3V4Dom13.getElementType();
	if ( typeFibMatrix13 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix13. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix13 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom13.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom13.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibMatrixE3V4Dom13.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibMatrixE3V4Dom13.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibMatrixE3V4Dom13.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vecFibMatrixE3V4Dom13.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom13.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3Dom5rootDom4 == vecFibMatrixE3V4Dom13.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3Dom13rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3Dom13rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom13.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainOE1Int8 == (*(vecFibMatrixE3V4Dom13.getDomain())) ){
	
		cout<<"The vectorDomainOE1Int8 is the domain for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibMatrix with just a matrix element as defining element"<<endl;

	cout<<"cVectorFibMatrix vecFibMatrix2E4( fibMatrixV4 );"<<endl;
	cVectorFibMatrix vecFibMatrix2E4( fibMatrixV4 );

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrix2E4.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrix2E4.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrix2E4.getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrix2E4.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrix2E4.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibMatrix2E4.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibMatrix2E4.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibMatrix2E4.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vecFibMatrix2E4.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrix2E4.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV4 == vecFibMatrix2E4.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrix2E4.getDomain() == NULL ){
		cout<<"Ther is no domain defined for the matrix element vector."<<endl;
	}else{
		cerr<<"Error: The is a the domain for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibMatrix with just a matrix element as defining element, wich has domain number set"<<endl;
	
	cout<<"fibMatrixV3Dom5rootDom4.setDomainNr( 5 );"<<endl;
	fibMatrixV3Dom5rootDom4.setDomainNr( 5 );

	cout<<"cVectorFibMatrix vecFibMatrix2E3V4Dom5( fibMatrixV3Dom5rootDom4 );"<<endl;
	cVectorFibMatrix vecFibMatrix2E3V4Dom5( fibMatrixV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrix2E3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrix2E3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrix2E3V4Dom5.getElementType();
	if ( typeFibMatrix5 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix5. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix5 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrix2E3V4Dom5.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrix2E3V4Dom5.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibMatrix2E3V4Dom5.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibMatrix2E3V4Dom5.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibMatrix2E3V4Dom5.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vecFibMatrix2E3V4Dom5.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrix2E3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3Dom5rootDom4 == vecFibMatrix2E3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3Dom5rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3Dom5rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrix2E3V4Dom5.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE2Int4Int5 == (*(vecFibMatrix2E3V4Dom5.getDomain())) ){
	
		cout<<"The vectorDomainE2Int4Int5 is the domain for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibMatrix with yust a matrix element as defining element, wich has a not existig domain number set"<<endl;
	
	cout<<"fibMatrixV3Dom5rootDom4.setDomainNr( 13 );"<<endl;
	fibMatrixV3Dom5rootDom4.setDomainNr( 13 );

	cout<<"cVectorFibMatrix vecFibMatrix2E3V4Dom13( fibMatrixV3Dom5rootDom4 );"<<endl;
	cVectorFibMatrix vecFibMatrix2E3V4Dom13( fibMatrixV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrix2E3V4Dom13.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrix2E3V4Dom13.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrix2E3V4Dom13.getElementType();
	if ( typeFibMatrix13 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix13. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix13 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrix2E3V4Dom13.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrix2E3V4Dom13.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibMatrix2E3V4Dom13.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibMatrix2E3V4Dom13.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibMatrix2E3V4Dom13.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vecFibMatrix2E3V4Dom13.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrix2E3V4Dom13.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3Dom5rootDom4 == vecFibMatrix2E3V4Dom13.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3Dom13rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3Dom13rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrix2E3V4Dom13.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainOE1Int8 == (*(vecFibMatrix2E3V4Dom13.getDomain())) ){
	
		cout<<"The vectorDomainOE1Int8 is the domain for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibMatrix by copying vecFibMatrixE3"<<endl;
	
	cout<<"cVectorFibMatrix vecFibMatrixE3Copy( vecFibMatrixE3 );"<<endl;
	cVectorFibMatrix vecFibMatrixE3Copy( vecFibMatrixE3 );

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3Copy.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3Copy.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3Copy.getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3Copy.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3Copy.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibMatrixE3Copy.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibMatrixE3Copy.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibMatrixE3Copy.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<< vecFibMatrixE3Copy.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3Copy.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrixE3Copy.getDomain() == NULL ){
	
		cout<<"Ther is no domain defined for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The is an domain defined for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibMatrix by copying vecFibMatrixE4RD2"<<endl;
	
	cout<<"cVectorFibMatrix vecFibMatrixE4RD2Copy( vecFibMatrixE4RD2 );"<<endl;
	cVectorFibMatrix vecFibMatrixE4RD2Copy( vecFibMatrixE4RD2 );

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2Copy.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE4RD2Copy.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE4RD2Copy.getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2Copy.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE4RD2Copy.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibMatrixE4RD2Copy.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibMatrixE4RD2Copy.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibMatrixE4RD2Copy.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<< vecFibMatrixE4RD2Copy.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2Copy.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecFibMatrixE4RD2Copy.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2Copy.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE1Nat1 == (*(vecFibMatrixE4RD2Copy.getDomain())) ){
	
		cout<<"The vectorDomainE1Nat1 is the domain for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1Nat1 is not the domain for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibMatrix by copying vecFibMatrixE4RD2 and givin fibMatrixV3Dom5rootDom4 as an defining element"<<endl;
	
	cout<<"cVectorFibMatrix vecFibMatrixE4RD2Copy2( vecFibMatrixE4RD2, &fibMatrixV3Dom5rootDom4 );"<<endl;
	cVectorFibMatrix vecFibMatrixE4RD2Copy2( vecFibMatrixE4RD2, &fibMatrixV3Dom5rootDom4 );

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2Copy2.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE4RD2Copy2.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE4RD2Copy2.getElementType();
	if ( typeFibMatrix13 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix13. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix13 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2Copy2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE4RD2Copy2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibMatrixE4RD2Copy2.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibMatrixE4RD2Copy2.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibMatrixE4RD2Copy2.getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<< vecFibMatrixE4RD2Copy2.getValue( uiActualElement ) <<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2Copy2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3Dom5rootDom4 == vecFibMatrixE4RD2Copy2.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3Dom5rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3Dom5rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2Copy2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainOE1Int8 == (*(vecFibMatrixE4RD2Copy2.getDomain())) ){
	
		cout<<"The vectorDomainOE1Int8 is the domain for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cVectorFibMatrix by copying vecFibMatrixRD3 with changed elements"<<endl;
	
	cout<<"rootDom4.setNumberOfInputVariables( 2 );"<<endl;
	rootDom4.setNumberOfInputVariables( 2 );
	cout<<"cFibVariable * pVariable1 = rootDom4.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootDom4.getInputVariable( 1 );
	cout<<"cFibVariable * pVariable2 = rootDom4.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = rootDom4.getInputVariable( 2 );

	cout<<"vecFibMatrixE4RD2.setValue( 1, 1 );"<<endl;
	vecFibMatrixE4RD2.setValue( 1, 1 );
	cout<<"vecFibMatrixE4RD2.setVariable( 2, pVariable1 );"<<endl;
	vecFibMatrixE4RD2.setVariable( 2, pVariable1 );
	cout<<"vecFibMatrixE4RD2.setValue( 3, 2 );"<<endl;
	vecFibMatrixE4RD2.setValue( 3, 2 );
	cout<<"vecFibMatrixE4RD2.setVariable( 4, pVariable2 );"<<endl;
	vecFibMatrixE4RD2.setVariable( 4, pVariable2 );
	
	cout<<"cVectorFibMatrix vecFibMatrixE4RD2CopyMod( vecFibMatrixE4RD2 );"<<endl;
	cVectorFibMatrix vecFibMatrixE4RD2CopyMod( vecFibMatrixE4RD2 );

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2CopyMod.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE4RD2CopyMod.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE4RD2CopyMod.getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2Copy2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE4RD2Copy2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
		//check the first vectorelement
	if ( ! vecFibMatrixE4RD2CopyMod.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrixE4RD2CopyMod.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrixE4RD2CopyMod.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecFibMatrixE4RD2CopyMod.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrixE4RD2CopyMod.getVariable( 2 ) == pVariable1 ){
	
		cout<<"The 2'th element of the matrix element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the secound vectorelement
	if ( ! vecFibMatrixE4RD2CopyMod.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrixE4RD2CopyMod.getValue( 3 ) == (doubleFib)(2) ){
	
		cout<<"The 3'th element of the "<<
			"matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrixE4RD2CopyMod.getValue( 3 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecFibMatrixE4RD2CopyMod.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrixE4RD2CopyMod.getVariable( 4 ) == pVariable2 ){
	
		cout<<"The 4'th element of the matrix element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the matrix element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2CopyMod.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecFibMatrixE4RD2CopyMod.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2CopyMod.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE1Nat1 == (*(vecFibMatrixE4RD2CopyMod.getDomain())) ){
	
		cout<<"The vectorDomainE1Nat1 is the domain for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1Nat1 is not the domain for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"Testing the original vector vecFibMatrixE4RD2:"<<endl;

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE4RD2.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE4RD2.getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE4RD2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
		//check the first vectorelement
	if ( ! vecFibMatrixE4RD2.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrixE4RD2.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrixE4RD2.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecFibMatrixE4RD2.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrixE4RD2.getVariable( 2 ) == pVariable1 ){
	
		cout<<"The 2'th element of the matrix element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the secound vectorelement
	if ( ! vecFibMatrixE4RD2.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrixE4RD2.getValue( 3 ) == (doubleFib)(2) ){
	
		cout<<"The 3'th element of the "<<
			"matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrixE4RD2.getValue( 3 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecFibMatrixE4RD2.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrixE4RD2.getVariable( 4 ) == pVariable2 ){
	
		cout<<"The 4'th element of the matrix element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the matrix element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecFibMatrixE4RD2.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE1Nat1 == (*(vecFibMatrixE4RD2.getDomain())) ){
	
		cout<<"The vectorDomainE1Nat1 is the domain for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1Nat1 is not the domain for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"Changing vecFibMatrixE4RD2 should not change the copy:"<<endl;

	cout<<"vecFibMatrixE4RD2.setVariable( 1, pVariable2 );"<<endl;
	vecFibMatrixE4RD2.setVariable( 1, pVariable2 );
	cout<<"vecFibMatrixE4RD2.setValue( 2, 9 );"<<endl;
	vecFibMatrixE4RD2.setValue( 2, 1 );
	cout<<"vecFibMatrixE4RD2.setValue( 3, 8 );"<<endl;
	vecFibMatrixE4RD2.setValue( 3, 2 );

	cout<<endl<<"Testing the copied vector vecFibMatrixE4RD2CopyMod for changed values:"<<endl;
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2CopyMod.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE4RD2CopyMod.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE4RD2CopyMod.getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2Copy2.getNumberOfElements() == (unsignedIntFib)(4) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE4RD2Copy2.getNumberOfElements()<<" but should be 4 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
		//check the first vectorelement
	if ( ! vecFibMatrixE4RD2CopyMod.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrixE4RD2CopyMod.getValue( 1 ) == (doubleFib)(1) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrixE4RD2CopyMod.getValue( 1 )<<" and not 1 "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecFibMatrixE4RD2CopyMod.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrixE4RD2CopyMod.getVariable( 2 ) == pVariable1 ){
	
		cout<<"The 2'th element of the matrix element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the secound vectorelement
	if ( ! vecFibMatrixE4RD2CopyMod.isVariable( 3 ) ){
	
		cout<<"The 3'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 3'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrixE4RD2CopyMod.getValue( 3 ) == (doubleFib)(2) ){
	
		cout<<"The 3'th element of the "<<
			"matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrixE4RD2CopyMod.getValue( 3 )<<" and not 2 . "<<endl;
		iReturn++;
	}

	//check the secound vectorelement
	if ( vecFibMatrixE4RD2CopyMod.isVariable( 4 ) ){
	
		cout<<"The 4'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrixE4RD2CopyMod.getVariable( 4 ) == pVariable2 ){
	
		cout<<"The 4'th element of the matrix element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 4'th element of the matrix element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2CopyMod.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vecFibMatrixE4RD2CopyMod.getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrixE4RD2CopyMod.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE1Nat1 == (*(vecFibMatrixE4RD2CopyMod.getDomain())) ){
	
		cout<<"The vectorDomainE1Nat1 is the domain for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1Nat1 is not the domain for the matrix element vector."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the method for the domains of the cVectorFibMatrix class.
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
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat5Nat3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat5Nat3( 2 );
	cout<<"vecDomainsE2Nat5Nat3[ 0 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE2Nat5Nat3[ 0 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE2Nat5Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE2Nat5Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE2Nat5Nat3( vecDomainsE2Nat5Nat3 );"<<endl;
	cDomainVector vectorDomainE2Nat5Nat3( vecDomainsE2Nat5Nat3 );
	delete vecDomainsE2Nat5Nat3[ 0 ];
	delete vecDomainsE2Nat5Nat3[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3( 4 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 2 ] = &vectorDomainE2Nat5Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 2 ] = &vectorDomainE2Nat5Nat3;
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] = &vectorDomainE3Nat1Nat2Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] = &vectorDomainE3Nat1Nat2Nat3;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3( vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3( vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3 );
	delete vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ];
	delete vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ];

	cout<<"cTypeFibMatrix typeFibMatrix;"<<endl;
	cTypeFibMatrix typeFibMatrix;

	cout<<"root.getDomains()->addDomain( typeFibMatrix, &vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3 );"<<endl;
	root.getDomains()->addDomain( typeFibMatrix, &vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3 );

	
	cout<<"cVectorFibMatrix vecFibMatrixRD( 3, &root );"<<endl;
	cVectorFibMatrix vecFibMatrixRD( 3, &root );
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixRD.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixRD.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the getDomain() methode from cVectorFibMatrix
	if ( vecFibMatrixRD.getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3.getElementDomain( 4 ) ==
			vecFibMatrixRD.getDomain() ){
	
		cout<<"The vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3[ 4 ] is the domain for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3[ 4 ] is not the domain for the matrix element vector."<<endl;
		iReturn++;
	}

	/*check the getDomain(i=1..n) method of the matrix vektor*/
	//test the getType() method
	cout<<"cDomain * pDomainD3 = vecFibMatrixRD.getDomain();"<<endl;
	cDomain * pDomainD3 = vecFibMatrixRD.getDomain();
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

	//check the getStandardDomain() method from cVectorFibMatrix
	cDomain * pDomainStandard = vecFibMatrixRD.getStandardDomain();
	cDomain * pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibMatrix domains with domain numbers"<<endl;
	
	cout<<"cRoot rootDom4;"<<flush<<endl;
	cRoot rootDom4;
	
	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix, &vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix, &vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3 );

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
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat3Nat7( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat3Nat7( 2 );
	cout<<"vecDomainsE2Nat3Nat7[ 0 ] = new cDomainNaturalNumberBit( 7 );"<<endl;
	vecDomainsE2Nat3Nat7[ 0 ] = new cDomainNaturalNumberBit( 7 );
	cout<<"vecDomainsE2Nat3Nat7[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE2Nat3Nat7[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat3Nat7 );"<<endl;
	cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat3Nat7 );
	delete vecDomainsE2Nat3Nat7[ 0 ];
	delete vecDomainsE2Nat3Nat7[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 4 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat2Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat2Nat3;
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int2Int3;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int2Int3;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibMatrix typeFibMatrix4( 4 );"<<endl;
	cTypeFibMatrix typeFibMatrix4( 4 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );
	
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
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat5Nat5( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat5Nat5( 2 );
	cout<<"vecDomainsE2Nat5Nat5[ 0 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE2Nat5Nat5[ 0 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE2Nat5Nat5[ 1 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE2Nat5Nat5[ 1 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"cDomainVector vectorDomainE2Nat5Nat5( vecDomainsE2Nat5Nat5 );"<<endl;
	cDomainVector vectorDomainE2Nat5Nat5( vecDomainsE2Nat5Nat5 );
	delete vecDomainsE2Nat5Nat5[ 0 ];
	delete vecDomainsE2Nat5Nat5[ 1 ];
	
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat5Nat5;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat5Nat5;
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int4Int5;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int4Int5;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibMatrix typeFibMatrix5( 5 );"<<endl;
	cTypeFibMatrix typeFibMatrix5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix5, &vectorDomainE3Na4Nat5VE2NInt4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix5, &vectorDomainE3Na4Nat5VE2NInt4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainOE1Int8;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainOE1Int8;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibMatrix typeFibMatrix6( 6 );"<<endl;
	cTypeFibMatrix typeFibMatrix6( 6 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix6, &vectorDomainE3Na4Nat5VOE1Int8 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix6, &vectorDomainE3Na4Nat5VOE1Int8 );
	
	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];
	
	
	cout<<"cFibMatrix fibMatrixV3rootDom4( 1, 3, NULL, &rootDom4 );"<<endl;
	cFibMatrix fibMatrixV3rootDom4( 1, 3, NULL, &rootDom4 );
	cout<<"fibMatrixV3rootDom4.setDomainNr( 0 );"<<endl;
	fibMatrixV3rootDom4.setDomainNr( 0 );
	
	cout<<"cVectorFibMatrix vecFibMatrixE3V4Dom5( 2, &fibMatrixV3rootDom4 );"<<endl;
	cVectorFibMatrix vecFibMatrixE3V4Dom5( 2, &fibMatrixV3rootDom4 );

	//check the getDomain() methode from cVectorFibMatrix
	cout<<"cDomain * pDomain = vecFibMatrixE3V4Dom5.getDomain();"<<endl;
	cDomain * pDomain = vecFibMatrixE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3.getElementDomain( 4 ) ==
				vecFibMatrixRD.getDomain() ){
		
			cout<<"The vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getDomain(i=1..n) method of the matrix vektor*/
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

	//check the getStandardDomain() method from cVectorFibMatrix
	pDomainStandard = vecFibMatrixE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	cTypeElement * pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibMatrix domains with domain numbers, setting domain number 1"<<endl;
	
	cout<<"fibMatrixV3rootDom4.setDomainNr( 1 );"<<endl;
	fibMatrixV3rootDom4.setDomainNr( 1 );

	//check the getDomain() methode from cVectorFibMatrix
	cout<<"pDomain = vecFibMatrixE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibMatrixE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3.getElementDomain( 4 ) ==
				vecFibMatrixRD.getDomain() ){
		
			cout<<"The vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getDomain(i=1..n) method of the matrix vektor*/
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

	//check the getStandardDomain() method from cVectorFibMatrix
	pDomainStandard = vecFibMatrixE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	cTypeFibMatrix typeFibMatrix1( 1 );
	if ( typeFibMatrix1 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix1. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix1 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibMatrix domains with domain numbers, setting domain number 3"<<endl;
	
	cout<<"fibMatrixV3rootDom4.setDomainNr( 3 );"<<endl;
	fibMatrixV3rootDom4.setDomainNr( 3 );

	//check the getDomain() methode from cVectorFibMatrix
	cout<<"pDomain = vecFibMatrixE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibMatrixE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3.getElementDomain( 4 ) ==
				vecFibMatrixRD.getDomain() ){
		
			cout<<"The vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getDomain(i=1..n) method of the matrix vektor*/
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

	//check the getStandardDomain() method from cVectorFibMatrix
	pDomainStandard = vecFibMatrixE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	cTypeFibMatrix typeFibMatrix3( 3 );
	if ( typeFibMatrix3 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix3. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix3 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibMatrix domains with domain numbers, setting domain number 4"<<endl;
	
	cout<<"fibMatrixV3rootDom4.setDomainNr( 4 );"<<endl;
	fibMatrixV3rootDom4.setDomainNr( 4 );

	//check the getDomain() methode from cVectorFibMatrix
	cout<<"pDomain = vecFibMatrixE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibMatrixE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE2Int2Int3 == *pDomain ){
		
			cout<<"The vectorDomainE2Int2Int3 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE2Int2Int3 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na4Nat5VE2NInt2Int3.getElementDomain( 4 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VE2NInt2Int3[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VE2NInt2Int3[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getDomain(i=1..n) method of the matrix vektor*/
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

	//check the getStandardDomain() method from cVectorFibMatrix
	pDomainStandard = vecFibMatrixE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	if ( typeFibMatrix4 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix4. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix4 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibMatrix domains with domain numbers, setting domain number 5"<<endl;
	
	cout<<"fibMatrixV3rootDom4.setDomainNr( 5 );"<<endl;
	fibMatrixV3rootDom4.setDomainNr( 5 );

	//check the getDomain() methode from cVectorFibMatrix
	cout<<"pDomain = vecFibMatrixE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibMatrixE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE2Int4Int5 == *pDomain ){
		
			cout<<"The vectorDomainE2Int4Int5 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na4Nat5VE2NInt4Int5.getElementDomain( 4 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VE2NInt4Int5[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VE2NInt4Int5[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getDomain(i=1..n) method of the matrix vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVector" ){
		
			cout<<"The type of pDomain is correctly \"DomainVector\". "<<endl;

			cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
			
			//test the getNumberOfElements() method
			if ( pVectorDomain->getNumberOfElements() == 2 ){
			
				cout<<"The number of elements of pDomain is correctly 3. "<<endl;
				
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

	//check the getStandardDomain() method from cVectorFibMatrix
	pDomainStandard = vecFibMatrixE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	if ( typeFibMatrix5 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix5. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix5 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibMatrix domains with domain numbers, setting domain number 6"<<endl;
	
	cout<<"fibMatrixV3rootDom4.setDomainNr( 6 );"<<endl;
	fibMatrixV3rootDom4.setDomainNr( 6 );

	//check the getDomain() methode from cVectorFibMatrix
	cout<<"pDomain = vecFibMatrixE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibMatrixE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainOE1Int8 == *pDomain ){
		
			cout<<"The vectorDomainOE1Int8 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na4Nat5VOE1Int8.getElementDomain( 4 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VOE1Int8[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VOE1Int8[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getDomain(i=1..n) method of the matrix vektor*/
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

	//check the getStandardDomain() method from cVectorFibMatrix
	pDomainStandard = vecFibMatrixE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	if ( typeFibMatrix6 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix6. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix6 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibMatrix domains with domain numbers, setting domain number 13"<<endl;
	
	cout<<"fibMatrixV3rootDom4.setDomainNr( 13 );"<<endl;
	fibMatrixV3rootDom4.setDomainNr( 13 );

	//check the getDomain() methode from cVectorFibMatrix
	cout<<"pDomain = vecFibMatrixE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibMatrixE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainOE1Int8 == *pDomain ){
		
			cout<<"The vectorDomainOE1Int8 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na4Nat5VOE1Int8.getElementDomain( 4 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VOE1Int8[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VOE1Int8[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getDomain(i=1..n) method of the matrix vektor*/
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

	//check the getStandardDomain() method from cVectorFibMatrix
	pDomainStandard = vecFibMatrixE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	cTypeFibMatrix typeFibMatrix13( 13 );
	if ( typeFibMatrix13 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix13. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix13 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	return iReturn;
}




/**
 * This method tests the method for the domains of the cVectorFibMatrix class.
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
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat5Nat3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat5Nat3( 2 );
	cout<<"vecDomainsE2Nat5Nat3[ 0 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE2Nat5Nat3[ 0 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE2Nat5Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE2Nat5Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE2Nat5Nat3( vecDomainsE2Nat5Nat3 );"<<endl;
	cDomainVector vectorDomainE2Nat5Nat3( vecDomainsE2Nat5Nat3 );
	delete vecDomainsE2Nat5Nat3[ 0 ];
	delete vecDomainsE2Nat5Nat3[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3( 4 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 2 ] = &vectorDomainE2Nat5Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 2 ] = &vectorDomainE2Nat5Nat3;
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] = &vectorDomainE3Nat1Nat2Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] = &vectorDomainE3Nat1Nat2Nat3;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3( vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3( vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3 );
	delete vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ];
	delete vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ];

	cout<<"cTypeFibMatrix typeFibMatrix;"<<endl;
	cTypeFibMatrix typeFibMatrix;

	cout<<"root.getValueDomains()->addDomain( typeFibMatrix, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	root.getValueDomains()->addDomain( typeFibMatrix, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );

	
	cout<<"cVectorFibMatrix vecFibMatrixRD( 3, &root );"<<endl;
	cVectorFibMatrix vecFibMatrixRD( 3, &root );
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixRD.getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixRD.getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	//check the getValueDomain() methode from cVectorFibMatrix
	if ( vecFibMatrixRD.getValueDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3.getElementDomain( 4 ) ==
			vecFibMatrixRD.getValueDomain() ){
	
		cout<<"The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 4 ] is the domain for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 4 ] is not the domain for the matrix element vector."<<endl;
		iReturn++;
	}

	/*check the getValueDomain(i=1..n) method of the matrix vektor*/
	//test the getType() method
	cout<<"cDomain * pDomainD3 = vecFibMatrixRD.getValueDomain();"<<endl;
	cDomain * pDomainD3 = vecFibMatrixRD.getValueDomain();
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

	//check the getStandardDomain() method from cVectorFibMatrix
	cDomain * pDomainStandard = vecFibMatrixRD.getStandardDomain();
	cDomain * pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibMatrix domains with domain numbers"<<endl;
	
	cout<<"cRoot rootDom4;"<<flush<<endl;
	cRoot rootDom4;
	
	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );

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
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat3Nat7( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat3Nat7( 2 );
	cout<<"vecDomainsE2Nat3Nat7[ 0 ] = new cDomainNaturalNumberBit( 7 );"<<endl;
	vecDomainsE2Nat3Nat7[ 0 ] = new cDomainNaturalNumberBit( 7 );
	cout<<"vecDomainsE2Nat3Nat7[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE2Nat3Nat7[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat3Nat7 );"<<endl;
	cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat3Nat7 );
	delete vecDomainsE2Nat3Nat7[ 0 ];
	delete vecDomainsE2Nat3Nat7[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 4 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat2Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat2Nat3;
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int2Int3;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int2Int3;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibMatrix typeFibMatrix4( 4 );"<<endl;
	cTypeFibMatrix typeFibMatrix4( 4 );
	cout<<"rootDom4.getValueDomains()->addDomain( typeFibMatrix4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );"<<endl;
	rootDom4.getValueDomains()->addDomain( typeFibMatrix4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );
	
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

	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat5Nat5( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat5Nat5( 2 );
	cout<<"vecDomainsE2Nat5Nat5[ 0 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE2Nat5Nat5[ 0 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE2Nat5Nat5[ 1 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE2Nat5Nat5[ 1 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"cDomainVector vectorDomainE2Nat5Nat5( vecDomainsE2Nat5Nat5 );"<<endl;
	cDomainVector vectorDomainE2Nat5Nat5( vecDomainsE2Nat5Nat5 );
	delete vecDomainsE2Nat5Nat5[ 0 ];
	delete vecDomainsE2Nat5Nat5[ 1 ];
	
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat5Nat5;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat5Nat5;
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int4Int5;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int4Int5;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibMatrix typeFibMatrix5( 5 );"<<endl;
	cTypeFibMatrix typeFibMatrix5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix5, &vectorDomainE3Na4Nat5VE2NInt4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix5, &vectorDomainE3Na4Nat5VE2NInt4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainOE1Int8;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainOE1Int8;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibMatrix typeFibMatrix6( 6 );"<<endl;
	cTypeFibMatrix typeFibMatrix6( 6 );
	cout<<"rootDom4.getValueDomains()->addDomain( typeFibMatrix6, &vectorDomainE3Na4Nat5VOE1Int8 );"<<endl;
	rootDom4.getValueDomains()->addDomain( typeFibMatrix6, &vectorDomainE3Na4Nat5VOE1Int8 );
	
	//create vector domain with
	cout<<"vector<cDomainSingle*> vecDomainsE1Int6( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int6( 1 );
	cout<<"vecDomainsE1Int6[ 0 ] = new cDomainIntegerBit( 6 );"<<endl;
	vecDomainsE1Int6[ 0 ] = new cDomainIntegerBit( 6 );
	cout<<"cDomainVector vectorDomainE1Int6( vecDomainsE1Int6 );"<<endl;
	cDomainVector vectorDomainE1Int6( vecDomainsE1Int6 );
	delete vecDomainsE1Int6[ 0 ];

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE1Int6;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE1Int6;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VOE1Int6( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VOE1Int6( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix6, &vectorDomainE3Na4Nat5VOE1Int6 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix6, &vectorDomainE3Na4Nat5VOE1Int6 );

	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];
	
	
	cout<<"cFibMatrix fibMatrixV3rootDom4( 1, 3, NULL, &rootDom4 );"<<endl;
	cFibMatrix fibMatrixV3rootDom4( 1, 3, NULL, &rootDom4 );
	cout<<"fibMatrixV3rootDom4.setDomainNr( 0 );"<<endl;
	fibMatrixV3rootDom4.setDomainNr( 0 );
	
	cout<<"cVectorFibMatrix vecFibMatrixE3V4Dom5( 2, &fibMatrixV3rootDom4 );"<<endl;
	cVectorFibMatrix vecFibMatrixE3V4Dom5( 2, &fibMatrixV3rootDom4 );

	//check the getValueDomain() methode from cVectorFibMatrix
	cout<<"cDomain * pDomain = vecFibMatrixE3V4Dom5.getValueDomain();"<<endl;
	cDomain * pDomain = vecFibMatrixE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3.getElementDomain( 4 ) ==
				vecFibMatrixRD.getValueDomain() ){
		
			cout<<"The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the matrix vektor*/
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

	//check the getStandardDomain() method from cVectorFibMatrix
	pDomainStandard = vecFibMatrixE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	cTypeElement * pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibMatrix domains with domain numbers, setting domain number 1"<<endl;
	
	cout<<"fibMatrixV3rootDom4.setDomainNr( 1 );"<<endl;
	fibMatrixV3rootDom4.setDomainNr( 1 );

	//check the getValueDomain() methode from cVectorFibMatrix
	cout<<"pDomain = vecFibMatrixE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecFibMatrixE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3.getElementDomain( 4 ) ==
				vecFibMatrixRD.getValueDomain() ){
		
			cout<<"The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the matrix vektor*/
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

	//check the getStandardDomain() method from cVectorFibMatrix
	pDomainStandard = vecFibMatrixE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	cTypeFibMatrix typeFibMatrix1( 1 );
	if ( typeFibMatrix1 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix1. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix1 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibMatrix domains with domain numbers, setting domain number 3"<<endl;
	
	cout<<"fibMatrixV3rootDom4.setDomainNr( 3 );"<<endl;
	fibMatrixV3rootDom4.setDomainNr( 3 );

	//check the getValueDomain() methode from cVectorFibMatrix
	cout<<"pDomain = vecFibMatrixE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecFibMatrixE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3.getElementDomain( 4 ) ==
				vecFibMatrixRD.getValueDomain() ){
		
			cout<<"The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the matrix vektor*/
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

	//check the getStandardDomain() method from cVectorFibMatrix
	pDomainStandard = vecFibMatrixE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	cTypeFibMatrix typeFibMatrix3( 3 );
	if ( typeFibMatrix3 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix3. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix3 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibMatrix domains with domain numbers, setting domain number 4"<<endl;
	
	cout<<"fibMatrixV3rootDom4.setDomainNr( 4 );"<<endl;
	fibMatrixV3rootDom4.setDomainNr( 4 );

	//check the getValueDomain() methode from cVectorFibMatrix
	cout<<"pDomain = vecFibMatrixE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecFibMatrixE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE2Int2Int3 == *pDomain ){
		
			cout<<"The vectorDomainE2Int2Int3 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE2Int2Int3 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na4Nat5VE2NInt2Int3.getElementDomain( 4 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VE2NInt2Int3[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VE2NInt2Int3[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the matrix vektor*/
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
	
	//check the getValueDomain() methode from cVectorFibMatrix
	cout<<"pDomain = vecFibMatrixE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibMatrixE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE3Nat1Nat2Nat3 == *pDomain ){
		
			cout<<"The vectorDomainE3Nat1Nat2Nat3 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Nat1Nat2Nat3 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3.getElementDomain( 4 ) ==
				vecFibMatrixRD.getValueDomain() ){
		
			cout<<"The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the matrix vektor*/
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

	//check the getStandardDomain() method from cVectorFibMatrix
	pDomainStandard = vecFibMatrixE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	if ( typeFibMatrix4 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix4. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix4 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibMatrix domains with domain numbers, setting domain number 5"<<endl;
	
	cout<<"fibMatrixV3rootDom4.setDomainNr( 5 );"<<endl;
	fibMatrixV3rootDom4.setDomainNr( 5 );

	//check the getValueDomain() methode from cVectorFibMatrix
	cout<<"pDomain = vecFibMatrixE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecFibMatrixE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE2Int4Int5 == *pDomain ){
		
			cout<<"The vectorDomainE2Int4Int5 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE2Int4Int5 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na4Nat5VE2NInt4Int5.getElementDomain( 4 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VE2NInt4Int5[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VE2NInt4Int5[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the matrix vektor*/
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

	//check the getStandardDomain() method from cVectorFibMatrix
	pDomainStandard = vecFibMatrixE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	if ( typeFibMatrix5 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix5. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix5 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibMatrix domains with domain numbers, setting domain number 6"<<endl;
	
	cout<<"fibMatrixV3rootDom4.setDomainNr( 6 );"<<endl;
	fibMatrixV3rootDom4.setDomainNr( 6 );

	//check the getValueDomain() methode from cVectorFibMatrix
	cout<<"pDomain = vecFibMatrixE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecFibMatrixE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainOE1Int8 == *pDomain ){
		
			cout<<"The vectorDomainOE1Int8 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na4Nat5VOE1Int8.getElementDomain( 4 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VOE1Int8[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VOE1Int8[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the matrix vektor*/
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
	//check the getValueDomain() methode from cVectorFibMatrix
	cout<<"pDomain = vecFibMatrixE3V4Dom5.getDomain();"<<endl;
	pDomain = vecFibMatrixE3V4Dom5.getDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainE1Int6 == *pDomain ){
		
			cout<<"The vectorDomainE1Int6 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE1Int6 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na4Nat5VOE1Int6.getElementDomain( 4 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VOE1Int6[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VOE1Int6[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the matrix vektor*/
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

	//check the getStandardDomain() method from cVectorFibMatrix
	pDomainStandard = vecFibMatrixE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	if ( typeFibMatrix6 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix6. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix6 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cVectorFibMatrix domains with domain numbers, setting domain number 13"<<endl;
	
	cout<<"fibMatrixV3rootDom4.setDomainNr( 13 );"<<endl;
	fibMatrixV3rootDom4.setDomainNr( 13 );

	//check the getValueDomain() methode from cVectorFibMatrix
	cout<<"pDomain = vecFibMatrixE3V4Dom5.getValueDomain();"<<endl;
	pDomain = vecFibMatrixE3V4Dom5.getValueDomain();
	if ( pDomain == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else{
		if ( vectorDomainOE1Int8 == *pDomain ){
		
			cout<<"The vectorDomainOE1Int8 is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainOE1Int8 is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}
		//check the getValueDomain() methode from cVectorFibMatrix
		if ( vectorDomainE3Na4Nat5VOE1Int8.getElementDomain( 4 ) == pDomain ){
		
			cout<<"The vectorDomainE3Na4Nat5VOE1Int8[ 4 ] is the domain for the matrix element vector. "<<endl;
		}else{
			cerr<<"Error: The vectorDomainE3Na4Nat5VOE1Int8[ 4 ] is not the domain for the matrix element vector."<<endl;
			iReturn++;
		}

		/*check the getValueDomain(i=1..n) method of the matrix vektor*/
		//test the getType() method
		if ( pDomain->getType() == "DomainVectorOpenEnd" ){
		
			cout<<"The type of pDomain is correctly \"DomainVector\". "<<endl;

			cDomainVector * pVectorDomain = (cDomainVector*)pDomain;
			
			//test the getNumberOfElements() method
			if ( pVectorDomain->getNumberOfElements() == 1 ){
			
				cout<<"The number of elements of pDomain is correctly 3. "<<endl;
				
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

	//check the getStandardDomain() method from cVectorFibMatrix
	pDomainStandard = vecFibMatrixE3V4Dom5.getStandardDomain();
	pTypeDomainStandard = typeFibMatrix.getStandardDomain();
	
	if ( pDomainStandard == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;
	}else{
		if ( *pDomainStandard == *( ((cDomainVectorBasis*)(
				pTypeDomainStandard))->getElementDomain( 4 ) ) ){
	
			cout<<"The vecFibMatrixRD has the correct standard domain. "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixRD has not the correct standard domain."<<endl;
			iReturn++;
		}
		delete pDomainStandard;
	}
	delete pTypeDomainStandard;
	
	
	//check the getVectorType() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vecFibMatrixE3V4Dom5.getElementType();
	cTypeFibMatrix typeFibMatrix13( 13 );
	if ( typeFibMatrix13 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix13. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix13 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vecFibMatrixE3V4Dom5.getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrixE3V4Dom5.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixV3rootDom4 == vecFibMatrixE3V4Dom5.getDefiningFibElement() ){
	
		cout<<"The fibMatrixV3rootDom4 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixV3rootDom4 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	return iReturn;
}




/**
 * This method tests setDefiningFibElement() and getDefiningFibElement()
 * method of the cVectorFibMatrix class.
 *
 * methods tested:
 * 	- setDefiningFibElement( cFibElement *fibElement, bool bCheckDomains )
 * 	- getDefiningFibElement()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testGetMatrixDefiningElement( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods"<<endl;

	cout<<"cFibMatrix definingElement1( 1, 1 );"<<endl;
	cFibMatrix definingElement1( 1, 1 );
	cout<<"cFibMatrix definingElement2( 1, 2 );"<<endl;
	cFibMatrix definingElement2( 1, 2 );
	
	cout<<"cVectorFibMatrix vecFibMatrix;"<<endl;
	cVectorFibMatrix vecFibMatrix;

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrix.getDefiningFibElement() == NULL ){
	
		cout<<"Ther is no defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	
	cout<<"vecFibMatrix.setDefiningFibElement( &definingElement1 );"<<endl;
	vecFibMatrix.setDefiningFibElement( &definingElement1 );

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrix.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &definingElement1 == vecFibMatrix.getDefiningFibElement() ){
	
		cout<<"The definingElement1 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The definingElement1 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}

	cout<<"vecFibMatrix.setDefiningFibElement( &definingElement2 );"<<endl;
	vecFibMatrix.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrix.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecFibMatrix.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}

	cout<<"vecFibMatrix.setDefiningFibElement( NULL );"<<endl;
	vecFibMatrix.setDefiningFibElement( NULL );

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrix.getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The is an defining element for the matrix element vector."<<endl;
		iReturn++;
	}

	cout<<"vecFibMatrix.setDefiningFibElement( &definingElement2 );"<<endl;
	vecFibMatrix.setDefiningFibElement( &definingElement2 );

	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vecFibMatrix.getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &definingElement2 == vecFibMatrix.getDefiningFibElement() ){
	
		cout<<"The definingElement2 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The definingElement2 is not the defining element for the matrix element vector."<<endl;
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
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat2Nat3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat2Nat3( 2 );
	cout<<"vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat2Nat3 );
	delete vecDomainsE2Nat2Nat3[ 0 ];
	delete vecDomainsE2Nat2Nat3[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3( 4 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 2 ] = &vectorDomainE2Nat2Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 2 ] = &vectorDomainE2Nat2Nat3;
	cout<<"vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] = &vectorDomainE3Nat1Nat2Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 3 ] = &vectorDomainE3Nat1Nat2Nat3;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3( vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3( vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3 );
	delete vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 0 ];
	delete vecDomainsE3Na2Nat3VE3Nat1Nat2Nat3[ 1 ];

	cout<<"cTypeFibMatrix typeFibMatrix;"<<endl;
	cTypeFibMatrix typeFibMatrix;
	
	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );

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
	
	cout<<"vecDomainsE2Nat2Nat3[ 0 ] = new cDomainIntegerBit( 5 );"<<endl;
	vecDomainsE2Nat2Nat3[ 0 ] = new cDomainIntegerBit( 5 );
	cout<<"vecDomainsE2Nat2Nat3[ 1 ] = new cDomainIntegerBit( 7 );"<<endl;
	vecDomainsE2Nat2Nat3[ 1 ] = new cDomainIntegerBit( 7 );
	cout<<"cDomainVector vectorDomainE2Int5Int7( vecDomainsE2Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE2Int5Int7( vecDomainsE2Nat2Nat3 );
	delete vecDomainsE2Nat2Nat3[ 0 ];
	delete vecDomainsE2Nat2Nat3[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 4 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int5Int7;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int5Int7;
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int2Int3;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int2Int3;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibMatrix typeFibMatrix4( 4 );"<<endl;
	cTypeFibMatrix typeFibMatrix4( 4 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );
	
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

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int4Int5;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE2Int4Int5;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt4Int5( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibMatrix typeFibMatrix5( 5 );"<<endl;
	cTypeFibMatrix typeFibMatrix5( 5 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix5, &vectorDomainE3Na4Nat5VE2NInt4Int5 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix5, &vectorDomainE3Na4Nat5VE2NInt4Int5 );
	
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];

	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainOE1Int8;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainOE1Int8;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibMatrix typeFibMatrix6( 6 );"<<endl;
	cTypeFibMatrix typeFibMatrix6( 6 );
	cout<<"rootDom4.getDomains()->addDomain( typeFibMatrix6, &vectorDomainE3Na4Nat5VOE1Int8 );"<<endl;
	rootDom4.getDomains()->addDomain( typeFibMatrix6, &vectorDomainE3Na4Nat5VOE1Int8 );
	
	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];
	
	
	cout<<"cFibMatrix fibMatrixDom0( 1, 3, NULL, &rootDom4 );"<<endl;
	cFibMatrix fibMatrixDom0( 1, 3, NULL, &rootDom4 );
	cout<<"fibMatrixDom0.setDomainNr( 0 );"<<endl;
	fibMatrixDom0.setDomainNr( 0 );
	
	cout<<"cFibMatrix fibMatrixDom4( 1, 4, NULL, &fibMatrixDom0 );"<<endl;
	cFibMatrix fibMatrixDom4( 1, 4, NULL, &fibMatrixDom0 );
	cout<<"fibMatrixDom4.setDomainNr( 4 );"<<endl;
	fibMatrixDom4.setDomainNr( 4 );

	cout<<"cFibMatrix fibMatrixDom5( 1, 5, NULL, &fibMatrixDom4 );"<<endl;
	cFibMatrix fibMatrixDom5( 1, 5, NULL, &fibMatrixDom4 );
	cout<<"fibMatrixDom5.setDomainNr( 5 );"<<endl;
	fibMatrixDom5.setDomainNr( 5 );

	cout<<"cFibMatrix fibMatrixDom6( 1, 6, NULL, &fibMatrixDom5 );"<<endl;
	cFibMatrix fibMatrixDom6( 1, 6, NULL, &fibMatrixDom5 );
	cout<<"fibMatrixDom6.setDomainNr( 6 );"<<endl;
	fibMatrixDom6.setDomainNr( 6 );
	
	cout<<"cFibMatrix fibMatrixDom11( 1, 11, NULL, &fibMatrixDom6 );"<<endl;
	cFibMatrix fibMatrixDom11( 1, 11, NULL, &fibMatrixDom6 );
	cout<<"fibMatrixDom11.setDomainNr( 11 );"<<endl;
	fibMatrixDom11.setDomainNr( 11 );


	cout<<"cVectorFibMatrix vecFibMatrixE0( 0 );"<<endl;
	cVectorFibMatrix vecFibMatrixE0( 0 );
	
	cout<<"vecFibMatrixE0.setDefiningFibElement( &rootDom4 );"<<endl;
	vecFibMatrixE0.setDefiningFibElement( &rootDom4 );

	cout<<"cVectorFibMatrix vecFibMatrix2E3V0( 3 );"<<endl;
	cVectorFibMatrix vecFibMatrix2E3V0( 3 );

	if ( vecFibMatrixE0 == vecFibMatrix2E3V0 ){
	
		cout<<"The matrix element vector vecFibMatrixE0 is equal to vecFibMatrix2E3V0. "<<endl;
	}else{
		cerr<<"Error: The matrix element vector vecFibMatrixE0 is not equal to vecFibMatrix2E3V0."<<endl;
		iReturn++;
	}
	

	cout<<"cVectorFibMatrix vecFibMatrix1E3( 3 );"<<endl;
	cVectorFibMatrix vecFibMatrix1E3( 3 );
	cout<<"vecFibMatrix1E3.setValue( 1, 1);"<<endl;
	vecFibMatrix1E3.setValue( 1, 1);
	cout<<"vecFibMatrix1E3.setValue( 2, 2);"<<endl;
	vecFibMatrix1E3.setValue( 2, 2);

	cout<<"cVectorFibMatrix vecFibMatrix1E2( 2 );"<<endl;
	cVectorFibMatrix vecFibMatrix1E2( 2 );
	cout<<"vecFibMatrix1E2.setValue( 1, 3);"<<endl;
	vecFibMatrix1E2.setValue( 1, 3);
	cout<<"vecFibMatrix1E2.setValue( 2, 2);"<<endl;
	vecFibMatrix1E2.setValue( 2, 2);

	cout<<"vecFibMatrix1E2.setDefiningFibElement( &rootDom4 );"<<endl;
	vecFibMatrix1E2.setDefiningFibElement( &rootDom4 );

	if ( vecFibMatrix1E2 == vecFibMatrix1E3 ){
	
		cout<<"The matrix element vector vecFibMatrix1E2 is equal to vecFibMatrix1E3. "<<endl;
	}else{
		cerr<<"Error: The matrix element vector vecFibMatrix1E2 is not equal to vecFibMatrix1E3."<<endl;
		/*check the elements of the matrix vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibMatrix1E2.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecFibMatrix1E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibMatrix1E2.getValue( uiActualElement ) ==
					vecFibMatrix1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly "<< 
					vecFibMatrix1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is "<<vecFibMatrix1E2.getValue( uiActualElement )<<
					" and not "<< vecFibMatrix1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}


	cout<<"vecFibMatrix1E3.setValue( 1, 0);"<<endl;
	vecFibMatrix1E3.setValue( 1, 0);
	cout<<"vecFibMatrix1E3.setValue( 2, 1);"<<endl;
	vecFibMatrix1E3.setValue( 2, 1);

	cout<<"cVectorFibMatrix vecFibMatrix2E3( vecFibMatrix1E3 );"<<endl;
	cVectorFibMatrix vecFibMatrix2E3( vecFibMatrix1E3 );

	cout<<"vecFibMatrix2E3.setDefiningFibElement( &rootDom4 );"<<endl;
	vecFibMatrix2E3.setDefiningFibElement( &rootDom4 );


	if ( vecFibMatrix2E3 == vecFibMatrix1E3 ){
	
		cout<<"The matrix element vector vecFibMatrix2E3 is equal to vecFibMatrix1E3. "<<endl;
	}else{
		cerr<<"Error: The matrix element vector vecFibMatrix2E3 is not equal to vecFibMatrix1E3."<<endl;
		/*check the elements of the matrix vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibMatrix2E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecFibMatrix2E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibMatrix2E3.getValue( uiActualElement ) ==
					vecFibMatrix1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly "<< 
					vecFibMatrix1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is "<<vecFibMatrix2E3.getValue( uiActualElement )<<
					" and not "<< vecFibMatrix1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	cout<<"vecFibMatrix1E3.setValue( 1, 0);"<<endl;
	vecFibMatrix1E3.setValue( 1, 0);
	cout<<"vecFibMatrix1E3.setValue( 2, 3);"<<endl;
	vecFibMatrix1E3.setValue( 2, 3);
	cout<<"vecFibMatrix1E3.setValue( 3, 7);"<<endl;
	vecFibMatrix1E3.setValue( 3, 7);

	cout<<"cVectorFibMatrix vecFibMatrix3E3( 3 );"<<endl;
	cVectorFibMatrix vecFibMatrix3E3( 3 );
	cout<<"vecFibMatrix3E3.setValue( 1, -7 );"<<endl;
	vecFibMatrix3E3.setValue( 1, -7 );
	cout<<"vecFibMatrix3E3.setValue( 2, 4 );"<<endl;
	vecFibMatrix3E3.setValue( 2, 4 );
	cout<<"vecFibMatrix3E3.setValue( 3, 8 );"<<endl;
	vecFibMatrix3E3.setValue( 3, 8 );

	cout<<"vecFibMatrix3E3.setDefiningFibElement( &fibMatrixDom0 );"<<endl;
	vecFibMatrix3E3.setDefiningFibElement( &fibMatrixDom0 );

	if ( vecFibMatrix3E3 == vecFibMatrix1E3 ){
	
		cout<<"The matrix element vector vecFibMatrix3E3 is equal to vecFibMatrix1E3. "<<endl;
	}else{
		cerr<<"Error: The matrix element vector vecFibMatrix3E3 is not equal to vecFibMatrix1E3."<<endl;
		/*check the elements of the matrix vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibMatrix3E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecFibMatrix3E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibMatrix3E3.getValue( uiActualElement ) ==
					vecFibMatrix1E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly "<< 
					vecFibMatrix1E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is "<<vecFibMatrix3E3.getValue( uiActualElement )<<
					" and not "<< vecFibMatrix1E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	
	cout<<"cVectorFibMatrix vecFibMatrix2E4( 4 );"<<endl;
	cVectorFibMatrix vecFibMatrix2E4( 4 );
	cout<<"vecFibMatrix2E4.setValue( 1, -2 );"<<endl;
	vecFibMatrix2E4.setValue( 1, -2 );
	cout<<"vecFibMatrix2E4.setValue( 2, 3 );"<<endl;
	vecFibMatrix2E4.setValue( 2, 3 );

	cout<<"cVectorFibMatrix vecFibMatrix3E3( 3 );"<<endl;
	cVectorFibMatrix vecFibMatrix4E3( 3 );
	cout<<"vecFibMatrix4E3.setValue( 1, -7 );"<<endl;
	vecFibMatrix4E3.setValue( 1, -7 );
	cout<<"vecFibMatrix4E3.setValue( 2, 4 );"<<endl;
	vecFibMatrix4E3.setValue( 2, 4 );
	cout<<"vecFibMatrix4E3.setValue( 3, 8 );"<<endl;
	vecFibMatrix4E3.setValue( 3, 8 );

	cout<<"vecFibMatrix4E3.setDefiningFibElement( &fibMatrixDom4 );"<<endl;
	vecFibMatrix4E3.setDefiningFibElement( &fibMatrixDom4 );

	if ( vecFibMatrix4E3 == vecFibMatrix2E4 ){
	
		cout<<"The matrix element vector vecFibMatrix4E3 is equal to vecFibMatrix2E4. "<<endl;
	}else{
		cerr<<"Error: The matrix element vector vecFibMatrix4E3 is not equal to vecFibMatrix2E4."<<endl;
		/*check the elements of the matrix vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibMatrix4E3.getNumberOfElements();
				uiActualElement++ ){
			
			if ( ! vecFibMatrix4E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibMatrix4E3.getValue( uiActualElement ) ==
					vecFibMatrix2E4.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly "<< 
					vecFibMatrix2E4.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is "<<vecFibMatrix4E3.getValue( uiActualElement )<<
					" and not "<< vecFibMatrix2E4.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	
	cout<<"cVectorFibMatrix vecFibMatrix1E5( 5 );"<<endl;
	cVectorFibMatrix vecFibMatrix1E5( 5 );
	cout<<"vecFibMatrix1E5.setValue( 1, -7 );"<<endl;
	vecFibMatrix1E5.setValue( 1, -7 );
	cout<<"vecFibMatrix1E5.setValue( 2, 4 );"<<endl;
	vecFibMatrix1E5.setValue( 2, 4 );

	cout<<"cVectorFibMatrix vecFibMatrix5E3( 3 );"<<endl;
	cVectorFibMatrix vecFibMatrix5E3( 3 );
	cout<<"vecFibMatrix5E3.setValue( 1, -7 );"<<endl;
	vecFibMatrix5E3.setValue( 1, -7 );
	cout<<"vecFibMatrix5E3.setValue( 2, 4 );"<<endl;
	vecFibMatrix5E3.setValue( 2, 4 );
	cout<<"vecFibMatrix5E3.setValue( 3, 8 );"<<endl;
	vecFibMatrix5E3.setValue( 3, 8 );

	cout<<"vecFibMatrix5E3.setDefiningFibElement( &fibMatrixDom5 );"<<endl;
	vecFibMatrix5E3.setDefiningFibElement( &fibMatrixDom5 );

	if ( vecFibMatrix5E3 == vecFibMatrix1E5 ){
	
		cout<<"The matrix element vector vecFibMatrix5E3 is equal to vecFibMatrix1E5. "<<endl;
	}else{
		cerr<<"Error: The matrix element vector vecFibMatrix5E3 is not equal to vecFibMatrix1E5."<<endl;
		/*check the elements of the matrix vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibMatrix5E3.getNumberOfElements();
				uiActualElement++ ){
			
			if ( ! vecFibMatrix5E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibMatrix5E3.getValue( uiActualElement ) ==
					vecFibMatrix1E5.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly "<< 
					vecFibMatrix1E5.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is "<<vecFibMatrix5E3.getValue( uiActualElement )<<
					" and not "<< vecFibMatrix1E5.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	
	
	cout<<"cVectorFibMatrix vecFibMatrix1E6( 6 );"<<endl;
	cVectorFibMatrix vecFibMatrix1E6( 6 );
	cout<<"vecFibMatrix1E6.setValue( 1, -7 );"<<endl;
	vecFibMatrix1E6.setValue( 1, -7 );
	cout<<"vecFibMatrix1E6.setValue( 2, 127 );"<<endl;
	vecFibMatrix1E6.setValue( 2, 127 );
	cout<<"vecFibMatrix1E6.setValue( 3, -128 );"<<endl;
	vecFibMatrix1E6.setValue( 3, -128 );

	cout<<"cVectorFibMatrix vecFibMatrix6E3( 3 );"<<endl;
	cVectorFibMatrix vecFibMatrix6E3( 3 );
	cout<<"vecFibMatrix6E3.setValue( 1, -7 );"<<endl;
	vecFibMatrix6E3.setValue( 1, -7 );
	cout<<"vecFibMatrix6E3.setValue( 2, 128 );"<<endl;
	vecFibMatrix6E3.setValue( 2, 128 );
	cout<<"vecFibMatrix6E3.setValue( 3, -129 );"<<endl;
	vecFibMatrix6E3.setValue( 3, -129 );

	cout<<"vecFibMatrix6E3.setDefiningFibElement( &fibMatrixDom6 );"<<endl;
	vecFibMatrix6E3.setDefiningFibElement( &fibMatrixDom6 );

	if ( vecFibMatrix6E3 == vecFibMatrix1E6 ){
	
		cout<<"The matrix element vector vecFibMatrix6E3 is equal to vecFibMatrix1E6. "<<endl;
	}else{
		cerr<<"Error: The matrix element vector vecFibMatrix6E3 is not equal to vecFibMatrix1E6."<<endl;
		/*check the elements of the matrix vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibMatrix6E3.getNumberOfElements();
				uiActualElement++ ){
			
			if ( ! vecFibMatrix6E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibMatrix6E3.getValue( uiActualElement ) ==
					vecFibMatrix1E6.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly "<< 
					vecFibMatrix1E6.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is "<<vecFibMatrix6E3.getValue( uiActualElement )<<
					" and not "<< vecFibMatrix1E6.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	
	
	cout<<"cVectorFibMatrix vecFibMatrix1E11( 11 );"<<endl;
	cVectorFibMatrix vecFibMatrix1E11( 11 );
	cout<<"vecFibMatrix1E11.setValue( 1, -7 );"<<endl;
	vecFibMatrix1E11.setValue( 1, -7 );
	cout<<"vecFibMatrix1E11.setValue( 2, 127 );"<<endl;
	vecFibMatrix1E11.setValue( 2, 127 );
	cout<<"vecFibMatrix1E11.setValue( 3, -128 );"<<endl;
	vecFibMatrix1E11.setValue( 3, -128 );

	cout<<"cVectorFibMatrix vecFibMatrix7E3( 3 );"<<endl;
	cVectorFibMatrix vecFibMatrix7E3( 3 );
	cout<<"vecFibMatrix7E3.setValue( 1, -7 );"<<endl;
	vecFibMatrix7E3.setValue( 1, -7 );
	cout<<"vecFibMatrix7E3.setValue( 2, 128 );"<<endl;
	vecFibMatrix7E3.setValue( 2, 128 );
	cout<<"vecFibMatrix7E3.setValue( 3, -129 );"<<endl;
	vecFibMatrix7E3.setValue( 3, -129 );

	cout<<"vecFibMatrix7E3.setDefiningFibElement( &fibMatrixDom11 );"<<endl;
	vecFibMatrix7E3.setDefiningFibElement( &fibMatrixDom11 );

	if ( vecFibMatrix7E3 == vecFibMatrix1E11 ){
	
		cout<<"The matrix element vector vecFibMatrix7E3 is equal to vecFibMatrix1E11. "<<endl;
	}else{
		cerr<<"Error: The matrix element vector vecFibMatrix7E3 is not equal to vecFibMatrix1E11."<<endl;
		/*check the elements of the matrix vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibMatrix7E3.getNumberOfElements();
				uiActualElement++ ){
			
			if ( ! vecFibMatrix7E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibMatrix7E3.getValue( uiActualElement ) ==
					vecFibMatrix1E11.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly "<< 
					vecFibMatrix1E11.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is "<<vecFibMatrix7E3.getValue( uiActualElement )<<
					" and not "<< vecFibMatrix1E11.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the get and setDefiningFibElement() methods when a domain is given, but shouldn't be checked"<<endl;
	
	cout<<"cVectorFibMatrix vecFibMatrix2E2( 2 );"<<endl;
	cVectorFibMatrix vecFibMatrix2E2( 2 );
	cout<<"vecFibMatrix2E2.setValue( 1, -58 );"<<endl;
	vecFibMatrix2E2.setValue( 1, -58 );
	cout<<"vecFibMatrix2E2.setValue( 2, 1234 );"<<endl;
	vecFibMatrix2E2.setValue( 2, 1234 );
	
	cVectorFibMatrix vecFibMatrix3E2( vecFibMatrix2E2 );

	cout<<"vecFibMatrix3E2.setDefiningFibElement( &fibMatrixDom5, false );"<<endl;
	vecFibMatrix3E2.setDefiningFibElement( &fibMatrixDom5, false );

	if ( vecFibMatrix3E2 == vecFibMatrix2E2 ){
	
		cout<<"The matrix element vector vecFibMatrix3E2 is equal to vecFibMatrix2E2. "<<endl;
	}else{
		cerr<<"Error: The matrix element vector vecFibMatrix3E2 is not equal to vecFibMatrix2E2."<<endl;
		/*check the elements of the matrix vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibMatrix3E2.getNumberOfElements() &&
				uiActualElement <= 2;
				uiActualElement++ ){
			
			if ( ! vecFibMatrix3E2.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibMatrix3E2.getValue( uiActualElement ) ==
					vecFibMatrix2E2.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly "<< 
					vecFibMatrix3E2.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is "<<vecFibMatrix3E2.getValue( uiActualElement )<<
					" and not "<< vecFibMatrix2E2.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	cout<<"cVectorFibMatrix vecFibMatrix8E3( 3 );"<<endl;
	cVectorFibMatrix vecFibMatrix8E3( 3 );
	cout<<"vecFibMatrix8E3.setValue( 1, -200 );"<<endl;
	vecFibMatrix8E3.setValue( 1, -200 );
	cout<<"vecFibMatrix8E3.setValue( 2, 4 );"<<endl;
	vecFibMatrix8E3.setValue( 2, 4 );
	cout<<"vecFibMatrix8E3.setValue( 3, 500 );"<<endl;
	vecFibMatrix8E3.setValue( 3, 500 );
	
	cVectorFibMatrix vecFibMatrix9E3( vecFibMatrix8E3 );

	cout<<"vecFibMatrix9E3.setDefiningFibElement( &fibMatrixDom5, false );"<<endl;
	vecFibMatrix9E3.setDefiningFibElement( &fibMatrixDom5, false );

	if ( vecFibMatrix9E3 == vecFibMatrix8E3 ){
	
		cout<<"The matrix element vector vecFibMatrix9E3 is equal to vecFibMatrix8E3. "<<endl;
	}else{
		cerr<<"Error: The matrix element vector vecFibMatrix9E3 is not equal to vecFibMatrix8E3."<<endl;
		/*check the elements of the matrix vektor*/
		for ( unsignedIntFib uiActualElement = 1;
				uiActualElement <= vecFibMatrix9E3.getNumberOfElements() &&
				uiActualElement <= 3;
				uiActualElement++ ){
			
			if ( ! vecFibMatrix9E3.isVariable( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly not a variable. "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is a variable. "<<endl;
				iReturn++;
			}
			if ( vecFibMatrix9E3.getValue( uiActualElement ) ==
					vecFibMatrix8E3.getValue( uiActualElement ) ){
			
				cout<<"The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is correctly "<< 
					vecFibMatrix8E3.getValue( uiActualElement ) <<" . "<<endl;
			}else{
				cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
					"matrix element vector is "<<vecFibMatrix9E3.getValue( uiActualElement )<<
					" and not "<< vecFibMatrix8E3.getValue( uiActualElement ) <<" . "<<endl;
				iReturn++;
			}
		}
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests cVectorFibMatrix methods for manipulating the
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
	
	cout<<"cVectorFibMatrix vecFibMatrix( 3, &emptyRoot );"<<endl;
	cVectorFibMatrix vecFibMatrix( 3, &emptyRoot );

	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vecFibMatrix.getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vecFibMatrix.isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vecFibMatrix.getValue( uiActualElement ) == (doubleFib)(0.0) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vecFibMatrix.getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
		if ( vecFibMatrix.getVariable( uiActualElement ) == NULL ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly no variable . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable . "<<endl;
			iReturn++;
		}
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setValue() method"<<endl;

	cout<<"vecFibMatrix.setValue( 2, 2.2 )"<<endl;
	if ( vecFibMatrix.setValue( 2, 2.2 ) ){
	
		cout<<"The 2'th element of the matrix element vector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecFibMatrix.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the matrix element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is a variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecFibMatrix.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 2 ) == (doubleFib)(2.2) ){
	
		cout<<"The 2'th element of the "<<
			"matrix element vector is correctly 2.2 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 2 )<<" and not 2.2 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the matrix element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is a variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFibMatrix.setValue( 2, 0.7 )"<<endl;
	if ( vecFibMatrix.setValue( 2, 0.7 ) ){
	
		cout<<"The 2'th element of the matrix element vector is set. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecFibMatrix.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 1 ) == (doubleFib)(0.0) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the matrix element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is a variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecFibMatrix.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"matrix element vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the matrix element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is a variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFibMatrix.setValue( 1, 11 )"<<endl;
	if ( vecFibMatrix.setValue( 1, 11 ) ){
	
		cout<<"The 1'th element of the matrix element vector is set. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not set. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecFibMatrix.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 1 ) == (doubleFib)(11) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 1 )<<" and not 11 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the matrix element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is a variable . "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecFibMatrix.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"matrix element vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the matrix element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is a variable . "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setVariable() method"<<endl;
	
	//creat defined variables to set them later in the vector
	cout<<"emptyRoot.setNumberOfInputVariables( 6 )"<<endl;
	bool bVariableMatrix = emptyRoot.setNumberOfInputVariables( 6 );
	if ( bVariableMatrix ){
	
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
	cout<<endl<<"vecFibMatrix.setVariable( 1, pVariable1 )"<<endl;
	if ( vecFibMatrix.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the matrix element vector is set to the variable 1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not set to the variable 1. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecFibMatrix.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 1 ) == (doubleFib)(0) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 1 )<<" and not 0 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the matrix element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( ! vecFibMatrix.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 2 ) == (doubleFib)(0.7) ){
	
		cout<<"The 2'th element of the "<<
			"matrix element vector is correctly 0.7 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 2 )<<" and not 0.7 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 2 ) == NULL ){
	
		cout<<"The 2'th element of the matrix element vector is correctly no variable . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is a variable . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable1->setValue( 0.11 );"<<endl;
	pVariable1->setValue( 0.11 );
	
	if ( vecFibMatrix.getValue( 1 ) == (doubleFib)(0.11) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 0.11 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 1 )<<" and not 0.11 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable1->setValue( 111 );"<<endl;
	pVariable1->setValue( 111 );
	
	if ( vecFibMatrix.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4 = emptyRoot.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable4 = emptyRoot.getInputVariable( 4 );
	cout<<endl<<"vecFibMatrix.setVariable( 2, pVariable4 )"<<endl;
	if ( vecFibMatrix.setVariable( 2, pVariable4 ) ){
	
		cout<<"The 2'th element of the matrix element vector is set to the variable 4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not set to the variable 4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecFibMatrix.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the matrix element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecFibMatrix.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 2 ) == (doubleFib)(0.0) ){
	
		cout<<"The 2'th element of the "<<
			"matrix element vector is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 2 )<<" and not 0.0 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the matrix element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 123 );"<<endl;
	pVariable4->setValue( 123 );
	
	if ( vecFibMatrix.getValue( 2 ) == (doubleFib)(123) ){
	
		cout<<"The 2'th element of the "<<
			"matrix element vector is correctly 123 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 2 )<<" and not 123 . "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 0.321 );"<<endl;
	pVariable4->setValue( 0.321  );
	
	if ( vecFibMatrix.getValue( 2 ) == (doubleFib)(0.321 ) ){
	
		cout<<"The 2'th element of the "<<
			"matrix element vector is correctly 0.321  . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 2 )<<" and not 0.321  . "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecFibMatrix.setVariable( 1, pVariable4 )"<<endl;
	if ( vecFibMatrix.setVariable( 1, pVariable4 ) ){
	
		cout<<"The 1'th element of the matrix element vector is set to the variable 4. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not set to the variable 4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecFibMatrix.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 1 ) == (doubleFib)(0.321) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 0.321 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 1 )<<" and not 0.321 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 1 ) == pVariable4 ){
	
		cout<<"The 1'th element of the matrix element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecFibMatrix.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 2 ) == (doubleFib)(0.321) ){
	
		cout<<"The 2'th element of the "<<
			"matrix element vector is correctly 0.321 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 2 )<<" and not 0.321 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the matrix element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 654.123 );"<<endl;
	pVariable4->setValue( 654.123 );
	
	if ( vecFibMatrix.getValue( 1 ) == (doubleFib)(654.123) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 654.123 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 1 )<<" and not 654.123 . "<<endl;
		iReturn++;
	}
	
	if ( vecFibMatrix.getValue( 2 ) == (doubleFib)(654.123) ){
	
		cout<<"The 2'th element of the "<<
			"matrix element vector is correctly 654.123 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 2 )<<" and not 654.123 . "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setValue() and setVariable() after each other method"<<endl;
	
	cout<<endl<<"vecFibMatrix.setValue( 1, 17 )"<<endl;
	if ( vecFibMatrix.setValue( 1, 17 ) ){
	
		cout<<"The 1'th element of the matrix element vector is set to the value 17"<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not set to the value 17. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( ! vecFibMatrix.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 1 ) == (doubleFib)(17) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 17 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 1 )<<" and not 17 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 1 ) == NULL ){
	
		cout<<"The 1'th element of the matrix element vector is correctly not a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is a variable. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecFibMatrix.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 2 ) == (doubleFib)(654.123 ) ){
	
		cout<<"The 2'th element of the "<<
			"matrix element vector is correctly 654.123  . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 2 )<<" and not 654.123  . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the matrix element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}

	cout<<endl<<"pVariable4->setValue( 65 );"<<endl;
	pVariable4->setValue( 65 );
	
	if ( vecFibMatrix.getValue( 2 ) == (doubleFib)(65) ){
	
		cout<<"The 2'th element of the "<<
			"matrix element vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 2 )<<" and not 65 . "<<endl;
		iReturn++;
	}
	
	cout<<endl<<"vecFibMatrix.setVariable( 1, pVariable1 )"<<endl;
	if ( vecFibMatrix.setVariable( 1, pVariable1 ) ){
	
		cout<<"The 1'th element of the matrix element vector is set to the varaiable 1"<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not set to the variable 1. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecFibMatrix.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the matrix element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecFibMatrix.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 2 ) == (doubleFib)(65 ) ){
	
		cout<<"The 2'th element of the "<<
			"matrix element vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 2 )<<" and not 65  . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the matrix element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setVariable() methods with trying to set NULL"<<endl;
	
	cout<<endl<<"vecFibMatrix.setVariable( 1, NULL )"<<endl;
	if ( ! vecFibMatrix.setVariable( 1, NULL ) ){
	
		cout<<"The 1'th element of the matrix element vector couldn't be set to NULL."<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector could be set to NULL. "<<endl;
		iReturn++;
	}
	cout<<endl<<"vecFibMatrix.setVariable( 2, NULL )"<<endl;
	if ( ! vecFibMatrix.setVariable( 2, NULL ) ){
	
		cout<<"The 2'th element of the matrix element vector couldn't be set to NULL."<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector could be set to NULL. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecFibMatrix.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 1 ) == (doubleFib)(111) ){
	
		cout<<"The 1'th element of the "<<
			"matrix element vector is correctly 111 . "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 1 )<<" and not 111 . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 1 ) == pVariable1 ){
	
		cout<<"The 1'th element of the matrix element vector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the matrix element vector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecFibMatrix.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the matrix element vector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getValue( 2 ) == (doubleFib)(65 ) ){
	
		cout<<"The 2'th element of the "<<
			"matrix element vector is correctly 65 . "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is "<<
			vecFibMatrix.getValue( 2 )<<" and not 65  . "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the matrix element vector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the matrix element vector is not the variable pVariable4. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing replaceVariable(), isUsedVariable() and set<cFibVariable*> getUsedVariables() methods"<<endl;
	
	cout<<endl<<"pVariable2 = emptyRoot.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = emptyRoot.getInputVariable( 2 );
	cout<<endl<<"pVariable3 = emptyRoot.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = emptyRoot.getInputVariable( 3 );
	
	//check vecFibMatrix.isUsedVariable()
	if ( vecFibMatrix.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecFibMatrix.isUsedVariable()
	if ( ! vecFibMatrix.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check isUsedVariable()
	if ( vecFibMatrix.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	
	set<cFibVariable*> setCorrectUsedVariables;
	setCorrectUsedVariables.insert( pVariable1 );
	setCorrectUsedVariables.insert( pVariable4 );
	//check getUsedVariables()
	cout<<"setUsedVariables = vecFibMatrix.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = vecFibMatrix.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	
	cout<<endl<<"vecFibMatrix.replaceVariable( pVariable1, pVariable4 )"<<endl;
	setCorrectUsedVariables.erase( pVariable1 );
	if ( vecFibMatrix.replaceVariable( pVariable1, pVariable4 ) ){
	
		cout<<"The pVariable1 of the propertyvector was replaced with pVariable4. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 of the propertyvector was not replaced with pVariable4. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecFibMatrix.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 1 ) == pVariable4 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecFibMatrix.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 2 ) == pVariable4 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check vecFibMatrix.isUsedVariable()
	if ( ! vecFibMatrix.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecFibMatrix.isUsedVariable()
	if ( ! vecFibMatrix.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecFibMatrix.isUsedVariable()
	if ( vecFibMatrix.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecFibMatrix.getUsedVariables(); "<<endl;
	setUsedVariables = vecFibMatrix.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFibMatrix.replaceVariable( pVariable1, pVariable3 )"<<endl;
	if ( vecFibMatrix.replaceVariable( pVariable1, pVariable3 ) ){
	
		cout<<"The pVariable1 of the propertyvector was replaced with pVariable3. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 of the propertyvector was not replaced with pVariable3. "<<endl;
		iReturn++;
	}
	//check vecFibMatrix.isUsedVariable()
	if ( ! vecFibMatrix.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecFibMatrix.isUsedVariable()
	if ( vecFibMatrix.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecFibMatrix.getUsedVariables(); "<<endl;
	setUsedVariables = vecFibMatrix.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	cout<<endl<<"vecFibMatrix.replaceVariable( pVariable4, pVariable2 )"<<endl;
	setCorrectUsedVariables.erase( pVariable4 );
	setCorrectUsedVariables.insert( pVariable2 );
	if ( vecFibMatrix.replaceVariable( pVariable4, pVariable2 ) ){
	
		cout<<"The pVariable4 of the propertyvector was replaced with pVariable2. "<<endl;
	}else{
		cerr<<"Error: The pVariable4 of the propertyvector was not replaced with pVariable2. "<<endl;
		iReturn++;
	}
	//check the first vectorelement
	if ( vecFibMatrix.isVariable( 1 ) ){
	
		cout<<"The 1'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 1 ) == pVariable2 ){
	
		cout<<"The 1'th element of the propertyvector is correctly the variable pVariable1. "<<endl;
	}else{
		cerr<<"Error: The 1'th element of the propertyvector is not the variable pVariable1. "<<endl;
		iReturn++;
	}
	//check the secound vectorelement
	if ( vecFibMatrix.isVariable( 2 ) ){
	
		cout<<"The 2'th element of the propertyvector is correctly a variable. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not a variable. "<<endl;
		iReturn++;
	}
	if ( vecFibMatrix.getVariable( 2 ) == pVariable2 ){
	
		cout<<"The 2'th element of the propertyvector is correctly the variable pVariable4. "<<endl;
	}else{
		cerr<<"Error: The 2'th element of the propertyvector is not the variable pVariable4. "<<endl;
		iReturn++;
	}
	//check vecFibMatrix.isUsedVariable()
	if ( ! vecFibMatrix.isUsedVariable( pVariable1 ) ){
	
		cout<<"The pVariable1 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable1 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecFibMatrix.isUsedVariable()
	if ( vecFibMatrix.isUsedVariable( pVariable2 ) ){
	
		cout<<"The pVariable2 is correctly a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable2 is not a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecFibMatrix.isUsedVariable()
	if ( ! vecFibMatrix.isUsedVariable( pVariable3 ) ){
	
		cout<<"The pVariable3 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable3 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check vecFibMatrix.isUsedVariable()
	if ( ! vecFibMatrix.isUsedVariable( pVariable4 ) ){
	
		cout<<"The pVariable4 is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The pVariable4 is a used varible in the vector.  "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = vecFibMatrix.getUsedVariables(); "<<endl;
	setUsedVariables = vecFibMatrix.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	//check vecFibMatrix.isUsedVariable()
	if ( ! vecFibMatrix.isUsedVariable( NULL ) ){
	
		cout<<"The NULL is correctly not a used varible in the vector. "<<endl;
	}else{
		cerr<<"Error: The NULL is a used varible in the vector.  "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFibMatrix.replaceVariable( NULL, pVariable2 )"<<endl;
	if ( ! vecFibMatrix.replaceVariable( NULL, pVariable2 ) ){
	
		cout<<"Can't correctly replace NULL of the propertyvector with pVariable2. "<<endl;
	}else{
		cerr<<"Error: Can replace NULL of the propertyvector with pVariable2. "<<endl;
		iReturn++;
	}

	cout<<endl<<"vecFibMatrix.replaceVariable( pVariable2, NULL )"<<endl;
	if ( ! vecFibMatrix.replaceVariable( pVariable2, NULL ) ){
	
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

	cout<<"cFibMatrix fibMatrixEmptyRoot( 1, 2, NULL, &emptyRoot );"<<endl;
	cFibMatrix fibMatrixEmptyRoot( 1, 2, NULL, &emptyRoot );

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
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat2Nat3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat2Nat3( 2 );
	cout<<"vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat2Nat3 );
	delete vecDomainsE2Nat2Nat3[ 0 ];
	delete vecDomainsE2Nat2Nat3[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 4 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat2Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat2Nat3;
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE1Nat1;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE1Nat1;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE3Na2Nat3VE1Nat1 );
	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];

	cout<<"cTypeFibMatrix typeFibMatrix;"<<endl;
	cTypeFibMatrix typeFibMatrix;

	cout<<"rootD2.getDomains()->addDomain( typeFibMatrix, vectorDomainE3Na2Nat3VE1Nat1 );"<<endl;
	rootD2.getDomains()->addDomain( typeFibMatrix, vectorDomainE3Na2Nat3VE1Nat1 );

	//creat defined variables to set them later in the vector
	cout<<"rootD2.setNumberOfInputVariables( 4 )"<<endl;
	rootD2.setNumberOfInputVariables( 4 );

	cout<<"cFibMatrix fibMatrixRootD2( 2, 2, NULL, &rootD2 );"<<endl;
	cFibMatrix fibMatrixRootD2( 2, 2, NULL, &rootD2 );

	//create cVectorFibMatrixs to compare
	cout<<"cVectorFibMatrix vectorFibMatrixE3( 3 );"<<endl;
	cVectorFibMatrix vectorFibMatrixE3( 3 );
	cout<<"cVectorFibMatrix vectorFibMatrixE3RD2( 3, &rootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixE3RD2( 3, &rootD2 );
	cout<<"cVectorFibMatrix vectorFibMatrixE2Re( fibMatrixEmptyRoot );"<<endl;
	cVectorFibMatrix vectorFibMatrixE2Re( fibMatrixEmptyRoot );
	cout<<"cVectorFibMatrix vectorFibMatrixE2RD2( 2, &rootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixE2RD2( 2, &rootD2 );
	cout<<"cVectorFibMatrix vectorFibMatrixRD2( fibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixRD2( fibMatrixRootD2 );
	
	//vectors with changed values
	cout<<"cVectorFibMatrix vectorFibMatrixRD2V2g17p2( fibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixRD2V2g17p2( fibMatrixRootD2 );
	vectorFibMatrixRD2V2g17p2.setValue( 2, 17.2 );
	
	cout<<"cVectorFibMatrix vectorFibMatrixE2RD2V2g17p2( 2, &rootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixE2RD2V2g17p2( 2, &rootD2 );
	vectorFibMatrixE2RD2V2g17p2.setValue( 2, 17.2 );

	cout<<"cVectorFibMatrix vectorFibMatrixE2RD2V2g17p2001( 2, &rootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixE2RD2V2g17p2001( 2, &rootD2 );
	vectorFibMatrixE2RD2V2g17p2001.setValue( 2, 17.2001 );

	cout<<"cVectorFibMatrix vectorFibMatrixRD2V1g17p2( fibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixRD2V1g17p2( fibMatrixRootD2 );
	vectorFibMatrixRD2V1g17p2.setValue( 1, 17.2 );

	cout<<"cVectorFibMatrix vectorFibMatrixRD2V1g1p1V2gm2p2( fibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixRD2V1g1p1V2gm2p2( fibMatrixRootD2 );
	vectorFibMatrixRD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorFibMatrixRD2V1g1p1V2gm2p2.setValue( 2, -2.2 );

	cout<<"cVectorFibMatrix vectorFibMatrixE2RD2V1g1p1V2gm2p2( 2, &rootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixE2RD2V1g1p1V2gm2p2( 2, &rootD2 );
	vectorFibMatrixE2RD2V1g1p1V2gm2p2.setValue( 1, 1.1 );
	vectorFibMatrixE2RD2V1g1p1V2gm2p2.setValue( 2, -2.2 );
	
	cout<<"cVectorFibMatrix vectorFibMatrixRD2V1g1p1V2g2p2( fibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixRD2V1g1p1V2g2p2( fibMatrixRootD2 );
	vectorFibMatrixRD2V1g1p1V2g2p2.setValue( 1, 1.1 );
	vectorFibMatrixRD2V1g1p1V2g2p2.setValue( 2, 2.2 );

	//vectors with variables
	cFibVariable * pVariable1 = rootD2.getInputVariable( 1 );
	cFibVariable * pVariable2 = rootD2.getInputVariable( 2 );
	cFibVariable * pVariable1Re = emptyRoot.getInputVariable( 1 );

	cout<<"cVectorFibMatrix vectorFibMatrixRD2V1gV1( fibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixRD2V1gV1( fibMatrixRootD2 );
	vectorFibMatrixRD2V1gV1.setVariable( 1, pVariable1 );

	cout<<"cVectorFibMatrix vectorFibMatrixE2RD2V1gV1( 2, &rootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixE2RD2V1gV1( 2, &rootD2 );
	vectorFibMatrixE2RD2V1gV1.setVariable( 1, pVariable1 );

	cout<<"cVectorFibMatrix vectorFibMatrixRD2V2gV1( fibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixRD2V2gV1( fibMatrixRootD2 );
	vectorFibMatrixRD2V2gV1.setVariable( 2, pVariable1 );

	cout<<"cVectorFibMatrix vectorFibMatrixRD2V2gV2( fibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixRD2V2gV2( fibMatrixRootD2 );
	vectorFibMatrixRD2V2gV2.setVariable( 2, pVariable2 );

	cout<<"cVectorFibMatrix vectorFibMatrixRD2V1gReV1( fibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixRD2V1gReV1( fibMatrixRootD2 );
	vectorFibMatrixRD2V1gReV1.setVariable( 1, pVariable1Re );

	//vectors with changed values and variables
	cout<<"cVectorFibMatrix vectorFibMatrixRD2V1gV1V2g1111( fibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixRD2V1gV1V2g1111( fibMatrixRootD2 );
	vectorFibMatrixRD2V1gV1V2g1111.setVariable( 1, pVariable1 );
	vectorFibMatrixRD2V1gV1V2g1111.setValue( 2, 1111 );

	cout<<"cVectorFibMatrix vectorFibMatrixE2RD2V1gV1V2g1111( 2, &rootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixE2RD2V1gV1V2g1111( 2, &rootD2 );
	vectorFibMatrixE2RD2V1gV1V2g1111.setVariable( 1, pVariable1 );
	vectorFibMatrixE2RD2V1gV1V2g1111.setValue( 2, 1111 );

	cout<<"cVectorFibMatrix vectorFibMatrixRD2V1gV1V2g111( fibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixRD2V1gV1V2g111( fibMatrixRootD2 );
	vectorFibMatrixRD2V1gV1V2g111.setVariable( 1, pVariable1 );
	vectorFibMatrixRD2V1gV1V2g111.setValue( 2, 111 );

	cout<<"cVectorFibMatrix vectorFibMatrixRD2V1gV2V1g1111( 2, &rootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixRD2V1g111V2gV2( 2, &rootD2 );
	vectorFibMatrixRD2V1g111V2gV2.setVariable( 1, pVariable2 );
	vectorFibMatrixRD2V1g111V2gV2.setValue( 2, 1111 );

	cout<<"cVectorFibMatrix vectorFibMatrixE2RD2V1g1111V2gV2( fibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixE2RD2V1gV2V2g1111( fibMatrixRootD2 );
	vectorFibMatrixE2RD2V1gV2V2g1111.setValue( 1, 1111 );
	vectorFibMatrixE2RD2V1gV2V2g1111.setVariable( 2, pVariable1 );

	cout<<"cVectorFibMatrix vectorFibMatrixE2RD2V1gV1V2gV2( 2, &fibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixE2RD2V1gV1V2gV2( 2, &fibMatrixRootD2 );
	vectorFibMatrixE2RD2V1gV1V2gV2.setVariable( 1, pVariable1 );
	vectorFibMatrixE2RD2V1gV1V2gV2.setVariable( 2, pVariable2 );

	
	//check variable from different defining element
	cout<<"cFibMatrix fibMatrixFibMatrixRootD2( 3, 1, NULL, &fibMatrixRootD2 );"<<endl;
	cFibMatrix fibMatrixFibMatrixRootD2( 3, 1, NULL, &fibMatrixRootD2 );

	cout<<"cVectorFibMatrix vectorFibMatrixE2FS2V1gV1V2gV2( 2, &fibMatrixFibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixE2FS2V1gV1V2gV2( 2, &fibMatrixFibMatrixRootD2 );
	vectorFibMatrixE2FS2V1gV1V2gV2.setVariable( 1, pVariable1 );
	vectorFibMatrixE2FS2V1gV1V2gV2.setVariable( 2, pVariable2 );

	//cout<<"pVarFibMatrix2 = fibMatrixRootD2.getDefinedVariable( 1 );"<<endl;
	cFibVariable * pVarFibMatrix2 = fibMatrixRootD2.getDefinedVariable( 2 );

	cout<<"cVectorFibMatrix vectorFibMatrixE2FS22V1gV1V2gVFS2( 2, &fibMatrixFibMatrixRootD2 );"<<endl;
	cVectorFibMatrix vectorFibMatrixE2FS22V1gV1V2gVFS2( 2, &fibMatrixFibMatrixRootD2 );
	vectorFibMatrixE2FS22V1gV1V2gVFS2.setVariable( 1, pVariable1 );
	vectorFibMatrixE2FS22V1gV1V2gVFS2.setVariable( 2, pVarFibMatrix2 );
	
	
	cout<<"cVectorProperty vectorProperty( 1 );"<<endl;
	cVectorProperty vectorProperty( 1 );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with vectorFibMatrixE3
	cFibVector * actualVector = &vectorFibMatrixE3;
	string szActualVectorName = "vectorFibMatrixE3";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixE3RD2
	actualVector = &vectorFibMatrixE3RD2;
	szActualVectorName = "vectorFibMatrixE3RD2";
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixE2Re
	actualVector = &vectorFibMatrixE2Re;
	szActualVectorName = "vectorFibMatrixE2Re";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );
	
	//compare with vectorFibMatrixE2RD2
	actualVector = &vectorFibMatrixE2RD2;
	szActualVectorName = "vectorFibMatrixE2RD2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );
	
	//compare with vectorFibMatrixE2Re
	actualVector = &vectorFibMatrixRD2;
	szActualVectorName = "vectorFibMatrixRD2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixRD2V2g17p2
	actualVector = &vectorFibMatrixRD2V2g17p2;
	szActualVectorName = "vectorFibMatrixRD2V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixRD2V2g17p2
	actualVector = &vectorFibMatrixE2RD2V2g17p2;
	szActualVectorName = "vectorFibMatrixE2RD2V2g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixE2RD2V2g17p2001
	actualVector = &vectorFibMatrixE2RD2V2g17p2001;
	szActualVectorName = "vectorFibMatrixE2RD2V2g17p2001";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixE2RD2V2g17p2001
	actualVector = &vectorFibMatrixRD2V1g17p2;
	szActualVectorName = "vectorFibMatrixRD2V1g17p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixRD2V1g1p1V2gm2p2
	actualVector = &vectorFibMatrixRD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorFibMatrixRD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixE2RD2V1g1p1V2gm2p2
	actualVector = &vectorFibMatrixE2RD2V1g1p1V2gm2p2;
	szActualVectorName = "vectorFibMatrixE2RD2V1g1p1V2gm2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixE2RD2V1g1p1V2gm2p2
	actualVector = &vectorFibMatrixRD2V1g1p1V2g2p2;
	szActualVectorName = "vectorFibMatrixRD2V1g1p1V2g2p2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixRD2V1gV1
	actualVector = &vectorFibMatrixRD2V1gV1;
	szActualVectorName = "vectorFibMatrixRD2V1gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixE2RD2V1gV1
	actualVector = &vectorFibMatrixE2RD2V1gV1;
	szActualVectorName = "vectorFibMatrixE2RD2V1gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixRD2V2gV1
	actualVector = &vectorFibMatrixRD2V2gV1;
	szActualVectorName = "vectorFibMatrixRD2V2gV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixRD2V2gV2
	actualVector = &vectorFibMatrixRD2V2gV2;
	szActualVectorName = "vectorFibMatrixRD2V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixRD2V1gReV1
	actualVector = &vectorFibMatrixRD2V1gReV1;
	szActualVectorName = "vectorFibMatrixRD2V1gReV1";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixRD2V1gV1V2g1111
	actualVector = &vectorFibMatrixRD2V1gV1V2g1111;
	szActualVectorName = "vectorFibMatrixRD2V1gV1V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixE2RD2V1gV1V2g1111
	actualVector = &vectorFibMatrixE2RD2V1gV1V2g1111;
	szActualVectorName = "vectorFibMatrixE2RD2V1gV1V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixRD2V1gV1V2g111
	actualVector = &vectorFibMatrixRD2V1gV1V2g111;
	szActualVectorName = "vectorFibMatrixRD2V1gV1V2g111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixRD2V1g111V2gV2
	actualVector = &vectorFibMatrixRD2V1g111V2gV2;
	szActualVectorName = "vectorFibMatrixRD2V1g111V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixE2RD2V1gV2V2g1111
	actualVector = &vectorFibMatrixE2RD2V1gV2V2g1111;
	szActualVectorName = "vectorFibMatrixE2RD2V1gV2V2g1111";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixE2RD2V1gV1V2gV2
	actualVector = &vectorFibMatrixE2RD2V1gV1V2gV2;
	szActualVectorName = "vectorFibMatrixE2RD2V1gV1V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixE2FS2V1gV1V2gV2
	actualVector = &vectorFibMatrixE2FS2V1gV1V2gV2;
	szActualVectorName = "vectorFibMatrixE2FS2V1gV1V2gV2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorFibMatrixE2FS22V1gV1V2gVFS2
	actualVector = &vectorFibMatrixE2FS22V1gV1V2gVFS2;
	szActualVectorName = "vectorFibMatrixE2FS22V1gV1V2gVFS2";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );

	//compare with vectorProperty
	actualVector = &vectorProperty;
	szActualVectorName = "vectorProperty";
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3, "vectorFibMatrixE3" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE3RD2, "vectorFibMatrixE3RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2Re, "vectorFibMatrixE2Re" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2, "vectorFibMatrixE2RD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2, "vectorFibMatrixRD2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2g17p2, "vectorFibMatrixRD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2, "vectorFibMatrixE2RD2V2g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V2g17p2001, "vectorFibMatrixE2RD2V2g17p2001" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g17p2, "vectorFibMatrixRD2V1g17p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2gm2p2, "vectorFibMatrixRD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1g1p1V2gm2p2, "vectorFibMatrixE2RD2V1g1p1V2gm2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g1p1V2g2p2, "vectorFibMatrixRD2V1g1p1V2g2p2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1, "vectorFibMatrixRD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1, "vectorFibMatrixE2RD2V1gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV1, "vectorFibMatrixRD2V2gV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V2gV2, "vectorFibMatrixRD2V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gReV1, "vectorFibMatrixRD2V1gReV1" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g1111, "vectorFibMatrixRD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2g1111, "vectorFibMatrixE2RD2V1gV1V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1gV1V2g111, "vectorFibMatrixRD2V1gV1V2g111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixRD2V1g111V2gV2, "vectorFibMatrixRD2V1g111V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV2V2g1111, "vectorFibMatrixE2RD2V1gV2V2g1111" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2RD2V1gV1V2gV2, "vectorFibMatrixE2RD2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS2V1gV1V2gV2, "vectorFibMatrixE2FS2V1gV1V2gV2" );
	iReturn += testCompareTwoNotEqualVectors( *actualVector, szActualVectorName, vectorFibMatrixE2FS22V1gV1V2gVFS2, "vectorFibMatrixE2FS22V1gV1V2gVFS2" );
	iReturn += testCompareTwoEqualVectors( *actualVector, szActualVectorName, vectorProperty, "vectorProperty" );


	return iReturn;
}



/**
 * This method tests the createInstance() method of the cVectorFibMatrix class.
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
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat2Nat3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat2Nat3( 2 );
	cout<<"vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat2Nat3 );
	delete vecDomainsE2Nat2Nat3[ 0 ];
	delete vecDomainsE2Nat2Nat3[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE1Nat1( 4 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat2Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Nat2Nat3;
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE1Nat1;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 3 ] = &vectorDomainE1Nat1;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE1Nat1( vecDomainsE3Na2Nat3VE1Nat1 );
	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];
	
	cout<<"cTypeFibMatrix typeFibMatrix;"<<endl;
	cTypeFibMatrix typeFibMatrix;
	
	cout<<"rootD2.getDomains()->addDomain( typeFibMatrix, vectorDomainE3Na2Nat3VE1Nat1 );"<<endl;
	rootD2.getDomains()->addDomain( typeFibMatrix, vectorDomainE3Na2Nat3VE1Nat1 );

	
	cout<<"cVectorFibMatrix vecFibMatrixE4RD2 = cVectorFibMatrix( 4, &rootD2 );"<<endl;
	cVectorFibMatrix vecFibMatrixE4RD2 = cVectorFibMatrix( 4, &rootD2 );

	cout<<"cFibVector * vectorInstanceD1 = vecFibMatrixE4RD2.createInstance( 1 );"<<endl;
	cFibVector * vectorInstanceD1 = vecFibMatrixE4RD2.createInstance( 1 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vectorInstanceD1->getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vectorInstanceD1->getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	cTypeElement * pTypeFibMatrix = vectorInstanceD1->getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vectorInstanceD1->getNumberOfElements() == (unsignedIntFib)(1) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vectorInstanceD1->getNumberOfElements()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD1->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD1->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD1->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vectorInstanceD1->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vectorInstanceD1->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the matrix element vector."<<endl;
	}else if ( &rootD2 == vectorInstanceD1->getDefiningFibElement() ){
	
		cerr<<"Error: The rootD2 is the defining element for the matrix element vector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is a defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vectorInstanceD1->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the matrix element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the matrix element vector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD1;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 3 elements"<<endl;

	cout<<"cTypeFibMatrix typeFibMatrixDom3( 3 );"<<endl;
	cTypeFibMatrix typeFibMatrixDom3( 3 );

	cout<<"cFibVector * vectorInstanceD3 = vecFibMatrixE4RD2.createInstance( 3 );"<<endl;
	cFibVector * vectorInstanceD3 = vecFibMatrixE4RD2.createInstance( 3 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vectorInstanceD3->getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vectorInstanceD3->getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vectorInstanceD3->getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vectorInstanceD3->getNumberOfElements() == (unsignedIntFib)(3) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vectorInstanceD3->getNumberOfElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD3->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD3->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD3->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vectorInstanceD3->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vectorInstanceD3->getDefiningFibElement() == NULL ){
		cout<<"Ther is no defining element for the matrix element vector."<<endl;
	}else if ( &rootD2 == vectorInstanceD3->getDefiningFibElement() ){
	
		cerr<<"Error: The rootD2 is the defining element for the matrix element vector. "<<endl;
		iReturn++;	
	}else{
		cerr<<"Error: Ther is an defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vectorInstanceD3->getDomain() == NULL ){
		cout<<"Ther is no domain defined for the matrix element vector."<<endl;
	}else{
		cerr<<"Error: Ther is a domain for the matrix element vector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD3;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with 2 elements and rootD2 as an defining element"<<endl;

	cout<<"cFibVector * vectorInstanceD2RD2 = vecFibMatrixE4RD2.createInstance( 2, &rootD2 );"<<endl;
	cFibVector * vectorInstanceD2RD2 = vecFibMatrixE4RD2.createInstance( 2, &rootD2 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vectorInstanceD2RD2->getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vectorInstanceD2RD2->getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vectorInstanceD2RD2->getElementType();
	if ( typeFibMatrix == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vectorInstanceD2RD2->getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vectorInstanceD2RD2->getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD2RD2->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD2RD2->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD2RD2->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vectorInstanceD2RD2->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vectorInstanceD2RD2->getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &rootD2 == vectorInstanceD2RD2->getDefiningFibElement() ){
	
		cout<<"The rootD2 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The rootD2 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vectorInstanceD2RD2->getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE1Nat1 == (*(vectorInstanceD2RD2->getDomain())) ){
	
		cout<<"The vectorDomainE1Nat1 is the domain for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1Nat1 is not the domain for the matrix element vector."<<endl;
		iReturn++;
	}
	delete vectorInstanceD2RD2;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing create instance for a vector with different matrix element as defining element"<<endl;
	
	cout<<"cFibMatrix fibMatrixRd2( 1, 3, NULL, &rootD2 );"<<endl;
	cFibMatrix fibMatrixRd2( 1, 3, NULL, &rootD2 );

	cout<<"fibMatrixRd2.setDomainNr( 5 );"<<endl;
	fibMatrixRd2.setDomainNr( 5 );
	
	cout<<"cFibVector * vectorInstanceD2FsRD2 = vecFibMatrixE4RD2.createInstance( 2, &fibMatrixRd2 );"<<endl;
	cFibVector * vectorInstanceD2FsRD2 = vecFibMatrixE4RD2.createInstance( 2, &fibMatrixRd2 );

	cout<<endl<<"Testing the created instance:"<<flush<<endl;

	//check the getVectorType() methode from cVectorFibMatrix
	if ( vectorInstanceD2FsRD2->getVectorType() == "matrix" ){
	
		cout<<"The name of the matrix element vector is correctly \"matrix\" . "<<endl;
	}else{
		cerr<<"Error: The name of the matrix element vector is "<<
			vectorInstanceD2FsRD2->getVectorType()<<" but should be \"matrix\" ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cVectorFibMatrix
	pTypeFibMatrix = vectorInstanceD2FsRD2->getElementType();
	cout<<"cTypeFibMatrix typeFibMatrix5( 5 );"<<endl;
	cTypeFibMatrix typeFibMatrix5( 5 );
	if ( typeFibMatrix5 == (*pTypeFibMatrix) ){
	
		cout<<"The type of the matrix element vector is correctly equal to typeFibMatrix5. "<<endl;
	}else{
		cerr<<"Error: The type of matrix element vector not equal to typeFibMatrix5 ."<<endl;
		iReturn++;
	}
	delete pTypeFibMatrix;
	
	//check the getNumberOfElements() methode from cVectorFibMatrix
	if ( vectorInstanceD2FsRD2->getNumberOfElements() == (unsignedIntFib)(2) ){
	
		cout<<"The number of elements of the matrix element vector is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of elements of the matrix element vector is "<<
			vectorInstanceD2FsRD2->getNumberOfElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	
	/*check the elements of the matrix vektor*/
	for ( unsignedIntFib uiActualElement = 1;
			uiActualElement <= vectorInstanceD2FsRD2->getNumberOfElements();
			uiActualElement++ ){
		
		if ( ! vectorInstanceD2FsRD2->isVariable( uiActualElement ) ){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly not a variable. "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is a variable. "<<endl;
			iReturn++;
		}
		if ( vectorInstanceD2FsRD2->getValue( uiActualElement ) == (doubleFib)(0.0)){
		
			cout<<"The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is correctly 0 . "<<endl;
		}else{
			cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
				"matrix element vector is "<<vectorInstanceD2FsRD2->getValue( uiActualElement )<<
				" and not 0 . "<<endl;
			iReturn++;
		}
	}
	//check the getDefiningFibElement() methode from cVectorFibMatrix
	if ( vectorInstanceD2FsRD2->getDefiningFibElement() == NULL ){
		cerr<<"Error: Ther is no defining element for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( &fibMatrixRd2 == vectorInstanceD2FsRD2->getDefiningFibElement() ){
	
		cout<<"The fibMatrixRd2 is the defining element for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The fibMatrixRd2 is not the defining element for the matrix element vector."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cVectorFibMatrix
	if ( vectorInstanceD2FsRD2->getDomain() == NULL ){
		cerr<<"Error: Ther is no domain defined for the matrix element vector."<<endl;
		iReturn++;	
	}else if ( vectorDomainE1Nat1 == (*(vectorInstanceD2FsRD2->getDomain())) ){
	
		cout<<"The vectorDomainE1Nat1 is the domain for the matrix element vector. "<<endl;
	}else{
		cerr<<"Error: The vectorDomainE1Nat1 is not the domain for the matrix element vector."<<endl;
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
	
	TiXmlDocument xmlDocVectorFibMatrix( szFilename );
	bool loadOkay = xmlDocVectorFibMatrix.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocVectorFibMatrix );
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
 * This method tests the storeXml() method of the cVectorFibMatrix class.
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
	
	cout<<"cTypeFibMatrix typeFibMatrix;"<<endl;
	cTypeFibMatrix typeFibMatrix;
	
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
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat2Nat3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat2Nat3( 2 );
	cout<<"vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat2Nat3 );
	delete vecDomainsE2Nat2Nat3[ 0 ];
	delete vecDomainsE2Nat2Nat3[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE3( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE3( 4 );
	cout<<"vecDomainsE3Na2Nat3VE3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE3[ 2 ] = &vectorDomainE2Nat2Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE3[ 2 ] = &vectorDomainE2Nat2Nat3;
	cout<<"vecDomainsE3Na2Nat3VE3[ 3 ] = &vectorDomainE3;"<<endl;
	vecDomainsE3Na2Nat3VE3[ 3 ] = &vectorDomainE3;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE3( vecDomainsE3Na2Nat3VE3 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE3( vecDomainsE3Na2Nat3VE3 );
	delete vecDomainsE3Na2Nat3VE3[ 0 ];
	delete vecDomainsE3Na2Nat3VE3[ 1 ];

	cout<<"rootD3.getDomains()->addDomain( typeFibMatrix, vectorDomainE3Na2Nat3VE3 );"<<endl;
	rootD3.getDomains()->addDomain( typeFibMatrix, vectorDomainE3Na2Nat3VE3 );

	//creat defined variables to set them later in the vector
	cout<<"rootD3.setNumberOfInputVariables( 6 )"<<endl;
	rootD3.setNumberOfInputVariables( 6 );

	cout<<"cVectorFibMatrix vecFibMatrixE3( 3, &rootD3 );"<<endl;
	cVectorFibMatrix vecFibMatrixE3( 3, &rootD3 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	const char * szVectorPostion = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorFibMatrixEmpty.xml" );
	ofstream fileVectorPostion( szVectorPostion );
	
	bool bStoreSuccesfull = vecFibMatrixE3.storeXml( fileVectorPostion );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorPostion <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorPostion <<"\" failed."<<endl;
		iReturn++;
	}
	
	vector<char> vecElementTypeFibMatrix( 5, 'w' );
	vector<double> vecValuesFibMatrix( 5, 0.0 );
	
	iReturn += testXmlVector( szVectorPostion, "matrix",
		3, vecElementTypeFibMatrix, vecValuesFibMatrix );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector one value set"<<endl;
	
	cout<<"vecFibMatrixE3.setValue( 1, 111 )"<<endl;
	vecFibMatrixE3.setValue( 1, 111 );
	vecElementTypeFibMatrix[0] = 'w';
	vecValuesFibMatrix[0] = 111;
	
	szFileNameBuffer[0] = 0;
	const char * szVectorFibMatrixRD3V1g111 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorFibMatrixRD3V1g111.xml" );
	ofstream fileVectorPostioRD3V1g111n( szVectorFibMatrixRD3V1g111 );
	
	bStoreSuccesfull = vecFibMatrixE3.storeXml( fileVectorPostioRD3V1g111n );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorFibMatrixRD3V1g111 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorFibMatrixRD3V1g111 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorFibMatrixRD3V1g111, "matrix",
		3, vecElementTypeFibMatrix, vecValuesFibMatrix );
	
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector all value set"<<endl;
	
	cout<<"vecFibMatrixE3.setValue( 2, 123.456 )"<<endl;
	vecFibMatrixE3.setValue( 2, 123.456  );
	vecElementTypeFibMatrix[1] = 'w';
	vecValuesFibMatrix[1] = 123.456;
	cout<<"vecFibMatrixE3.setValue( 3, -123.456 )"<<endl;
	vecFibMatrixE3.setValue( 3, -123.456 );
	vecElementTypeFibMatrix[2] = 'w';
	vecValuesFibMatrix[2] = -123.456;

	szFileNameBuffer[0] = 0;
	const char * szVectorFibMatrixRD3T3 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorFibMatrixRD3T3.xml" );
	ofstream fileVectorFibMatrixRD3T3( szVectorFibMatrixRD3T3 );
	
	bStoreSuccesfull = vecFibMatrixE3.storeXml( fileVectorFibMatrixRD3T3 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorFibMatrixRD3T3 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorFibMatrixRD3T3 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorFibMatrixRD3T3, "matrix",
		3, vecElementTypeFibMatrix, vecValuesFibMatrix );

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
	
	cout<<"vecFibMatrixE3.setVariable( 1, pVariable1 )"<<endl;
	vecFibMatrixE3.setVariable( 1, pVariable1  );
	vecElementTypeFibMatrix[0] = 'v';
	vecValuesFibMatrix[0] = 1;
	cout<<"vecFibMatrixE3.setVariable( 2, pVariable2 )"<<endl;
	vecFibMatrixE3.setVariable( 2, pVariable2 );
	vecElementTypeFibMatrix[1] = 'v';
	vecValuesFibMatrix[1] = 2;
	cout<<"vecFibMatrixE3.setVariable( 3, pVariable3 )"<<endl;
	vecFibMatrixE3.setVariable( 3, pVariable3 );
	vecElementTypeFibMatrix[2] = 'v';
	vecValuesFibMatrix[2] = 3;

	szFileNameBuffer[0] = 0;
	const char * szVectorFibMatrixRD3T4 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorFibMatrixRD3T4.xml" );
	ofstream fileVectorFibMatrixRD3T4( szVectorFibMatrixRD3T4 );
	
	bStoreSuccesfull = vecFibMatrixE3.storeXml( fileVectorFibMatrixRD3T4 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorFibMatrixRD3T4 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorFibMatrixRD3T4 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorFibMatrixRD3T4, "matrix",
		3, vecElementTypeFibMatrix, vecValuesFibMatrix );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 3 d vector with variables and values"<<endl;
	
	cout<<"vecFibMatrixE3.setVariable( 1, pVariable1 )"<<endl;
	vecFibMatrixE3.setVariable( 1, pVariable1  );
	vecElementTypeFibMatrix[0] = 'v';
	vecValuesFibMatrix[0] = 1;
	cout<<"vecFibMatrixE3.setValue( 2, -0.00124 )"<<endl;
	vecFibMatrixE3.setValue( 2, -0.00124 );
	vecElementTypeFibMatrix[1] = 'w';
	vecValuesFibMatrix[1] = -0.00124;
	cout<<"vecFibMatrixE3.setVariable( 3, pVariable3 )"<<endl;
	vecFibMatrixE3.setVariable( 3, pVariable3 );
	vecElementTypeFibMatrix[2] = 'v';
	vecValuesFibMatrix[2] = 3;

	szFileNameBuffer[0] = 0;
	const char * szVectorFibMatrixRD3T5 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorFibMatrixRD3T5.xml" );
	ofstream fileVectorFibMatrixRD3T5( szVectorFibMatrixRD3T5 );
	
	bStoreSuccesfull = vecFibMatrixE3.storeXml( fileVectorFibMatrixRD3T5 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorFibMatrixRD3T5 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorFibMatrixRD3T5 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorFibMatrixRD3T5, "matrix",
		3, vecElementTypeFibMatrix, vecValuesFibMatrix );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an 5 d vector with variables and values"<<endl;
	
	cout<<"cVectorFibMatrix vecFibMatrixRD5 = cVectorFibMatrix( 5, &rootD3 );"<<endl;
	cVectorFibMatrix vecFibMatrixRD5 = cVectorFibMatrix( 5, &rootD3 );

	cout<<"vecFibMatrixRD5.setVariable( 1, pVariable1 )"<<endl;
	vecFibMatrixRD5.setVariable( 1, pVariable1  );
	vecElementTypeFibMatrix[0] = 'v';
	vecValuesFibMatrix[0] = 1;
	cout<<"vecFibMatrixRD5.setValue( 2, -0.00124 )"<<endl;
	vecFibMatrixRD5.setValue( 2, -0.00124 );
	vecElementTypeFibMatrix[1] = 'w';
	vecValuesFibMatrix[1] = -0.00124;
	cout<<"vecFibMatrixRD5.setVariable( 3, pVariable3 )"<<endl;
	vecFibMatrixRD5.setVariable( 3, pVariable3 );
	vecElementTypeFibMatrix[2] = 'v';
	vecValuesFibMatrix[2] = 3;
	cout<<"vecFibMatrixRD5.setValue( 4, 1234 )"<<endl;
	vecFibMatrixRD5.setValue( 4, 1234 );
	vecElementTypeFibMatrix[3] = 'w';
	vecValuesFibMatrix[3] = 1234;
	cout<<"vecFibMatrixRD5.setValue( 5, 123.67 )"<<endl;
	vecFibMatrixRD5.setValue( 5, 123.67   );
	vecElementTypeFibMatrix[4] = 'w';
	vecValuesFibMatrix[4] = 123.67 ;

	szFileNameBuffer[0] = 0;
	const char * szVectorFibMatrixRD3T6 = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vectorFibMatrixRD3T6.xml" );
	ofstream fileVectorFibMatrixRD3T6( szVectorFibMatrixRD3T6 );
	
	bStoreSuccesfull = vecFibMatrixRD5.storeXml( fileVectorFibMatrixRD3T6 );
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the vector was stored successfull to the file \""<< szVectorFibMatrixRD3T6 <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the vector to the file \""<< szVectorFibMatrixRD3T6 <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlVector( szVectorFibMatrixRD3T6, "matrix",
		5, vecElementTypeFibMatrix, vecValuesFibMatrix );


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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a matrix element vector with 0 elements"<<endl;

	cout<<"cVectorFibMatrix vecFibMatrixE0( 0 );"<<endl;
	cVectorFibMatrix vecFibMatrixE0( 0 );

	//test get compressed size
	unsigned int uiCompressedSize = 0;
	if ( (unsigned int)(vecFibMatrixE0.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibMatrixE0.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibMatrixE0.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	cout<<"vecFibMatrixE0.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bool bStoreSuccesfull = vecFibMatrixE0.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cFibMatrixE0[] = { (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibMatrixE0, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a matrix element vector with 2 elements"<<endl;

	cout<<"cVectorFibMatrix vecFibMatrix1E2Ch( 2 );"<<endl;
	cVectorFibMatrix vecFibMatrix1E2Ch( 2 );
	cout<<"vecFibMatrix1E2Ch.setValue( 1, 4 );"<<endl;
	vecFibMatrix1E2Ch.setValue( 1, 4 );
	cout<<"vecFibMatrix1E2Ch.setValue( 2, 6 );"<<endl;
	vecFibMatrix1E2Ch.setValue( 2, 6 );

	//test get compressed size
	uiCompressedSize = 2 * 33;
	if ( (unsigned int)(vecFibMatrix1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibMatrix1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibMatrix1E2Ch.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibMatrix1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibMatrix1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cFibMatrixE2[] = { (char)0x08, (char)0x00, (char)0x00, (char)0x00, (char)0x18, (char)0x00, (char)0x00, (char)0x00, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibMatrixE2, 9 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a matrix element vector with variables"<<endl;

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

	cout<<"vecFibMatrix1E2Ch.setVariable( 1, pVariable1);"<<endl;
	vecFibMatrix1E2Ch.setVariable( 1, pVariable1);
	cout<<"vecFibMatrix1E2Ch.setVariable( 2, pVariable2);"<<endl;
	vecFibMatrix1E2Ch.setVariable( 2, pVariable2);

	//test get compressed size
	uiCompressedSize = 2 * 9;
	if ( (unsigned int)(vecFibMatrix1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibMatrix1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibMatrix1E2Var.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibMatrix1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibMatrix1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cFibMatrixE2Var[] = { (char)0x03, (char)0x0A, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibMatrixE2Var, 3 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a matrix element vector with domains"<<endl;

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
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat2Nat3( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat2Nat3( 2 );
	cout<<"vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE2Nat2Nat3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE2Nat2Nat3[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE2Nat2Nat3( vecDomainsE2Nat2Nat3 );
	delete vecDomainsE2Nat2Nat3[ 0 ];
	delete vecDomainsE2Nat2Nat3[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE2Nat1Nat2( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE2Nat1Nat2( 4 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat1Nat2[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE2Nat1Nat2[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat1Nat2[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE2Nat1Nat2[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat1Nat2[ 2 ] = &vectorDomainE2Nat2Nat3;"<<endl;
	vecDomainsE3Na2Nat3VE2Nat1Nat2[ 2 ] = &vectorDomainE2Nat2Nat3;
	cout<<"vecDomainsE3Na2Nat3VE2Nat1Nat2[ 3 ] = &vectorDomainE2;"<<endl;
	vecDomainsE3Na2Nat3VE2Nat1Nat2[ 3 ] = &vectorDomainE2;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE2Nat1Nat2( vecDomainsE3Na2Nat3VE2Nat1Nat2 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE2Nat1Nat2( vecDomainsE3Na2Nat3VE2Nat1Nat2 );
	delete vecDomainsE3Na2Nat3VE2Nat1Nat2[ 0 ];
	delete vecDomainsE3Na2Nat3VE2Nat1Nat2[ 1 ];

	cout<<"cTypeFibMatrix typeFibMatrix;"<<endl;
	cTypeFibMatrix typeFibMatrix;
	
	cout<<"rootD2.getDomains()->addDomain( typeFibMatrix, &vectorDomainE3Na2Nat3VE2Nat1Nat2 );"<<endl;
	rootD2.getDomains()->addDomain( typeFibMatrix, &vectorDomainE3Na2Nat3VE2Nat1Nat2 );

	cout<<"cTypeVariable typeVariable;"<<endl;
	cTypeVariable typeVariable;

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB3( 3 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB3( 3 );

	cout<<"rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB3);"<<endl;
	rootD2.getDomains()->addDomain( typeVariable, domainNaturalNumberB3);

	cout<<"vecFibMatrix1E2Ch.setDefiningFibElement( &rootD2 );"<<endl;
	vecFibMatrix1E2Ch.setDefiningFibElement( &rootD2 );
	
	cout<<"vecFibMatrix1E2Ch.setValue( 2, 3 );"<<endl;
	vecFibMatrix1E2Ch.setValue( 2, 3 );

	//test get compressed size
	uiCompressedSize = 4 + 3;
	if ( (unsigned int)(vecFibMatrix1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibMatrix1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibMatrix1E2Dom.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibMatrix1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibMatrix1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cFibMatrixE2Dom[] = { (char)ucRestBitCorrect };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibMatrixE2Dom, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a matrix element vector 3 elements"<<endl;

	cout<<"cVectorFibMatrix vecFibMatrix1E3( 3 );"<<endl;
	cVectorFibMatrix vecFibMatrix1E3( 3 );
	
	cout<<"vecFibMatrix1E3.setVariable( 1, pVariable2 );"<<endl;
	vecFibMatrix1E3.setVariable( 1, pVariable2 );
	cout<<"vecFibMatrix1E3.setVariable( 2, pVariable1 );"<<endl;
	vecFibMatrix1E3.setVariable( 2, pVariable1);
	cout<<"vecFibMatrix1E3.setValue( 3, 5);"<<endl;
	vecFibMatrix1E3.setValue( 3, 5);

	//test get compressed size
	uiCompressedSize = 2 * 9 + 33;
	if ( (unsigned int)(vecFibMatrix1E3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibMatrix1E3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibMatrix1E3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibMatrix1E3.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibMatrix1E3.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cVecFibMatrix1E3[] = { (char)0x05, (char)0x06, (char)0x28, (char)0x00, (char)0x00, (char)0x00, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cVecFibMatrix1E3, 7 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a matrix element vector with a restbit of 4"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibMatrix1E3R4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x0F;
	cNumberOfRestBit = 4;
	cout<<"vecFibMatrix1E3.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibMatrix1E3.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cVecFibMatrix1E3R4[] = { (char)0x5F, (char)0x60, (char)0x80, (char)0x02, (char)0x00, (char)0x00, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cVecFibMatrix1E3R4, 7 );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a matrix element vector with domain not 0"<<endl;

	//create vector domain with two elements
	cout<<"vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"cDomainVector vectorDomainE2Nat3Nat4( vecDomains2 );"<<endl;
	cDomainVector vectorDomainE2Nat3Nat4( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	
	cout<<"vecDomainsE2Nat2Nat3[ 0 ] = new cDomainIntegerBit( 5 );"<<endl;
	vecDomainsE2Nat2Nat3[ 0 ] = new cDomainIntegerBit( 5 );
	cout<<"vecDomainsE2Nat2Nat3[ 1 ] = new cDomainIntegerBit( 7 );"<<endl;
	vecDomainsE2Nat2Nat3[ 1 ] = new cDomainIntegerBit( 7 );
	cout<<"cDomainVector vectorDomainE2Int5Int7( vecDomainsE2Nat2Nat3 );"<<endl;
	cDomainVector vectorDomainE2Int5Int7( vecDomainsE2Nat2Nat3 );
	delete vecDomainsE2Nat2Nat3[ 0 ];
	delete vecDomainsE2Nat2Nat3[ 1 ];
	
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE2Nat3Nat4( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE2Nat3Nat4( 4 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat3Nat4[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE2Nat3Nat4[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat3Nat4[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE2Nat3Nat4[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat3Nat4[ 2 ] = &vectorDomainE2Int5Int7;"<<endl;
	vecDomainsE3Na2Nat3VE2Nat3Nat4[ 2 ] = &vectorDomainE2Int5Int7;
	cout<<"vecDomainsE3Na2Nat3VE2Nat3Nat4[ 3 ] = &vectorDomainE2Nat3Nat4;"<<endl;
	vecDomainsE3Na2Nat3VE2Nat3Nat4[ 3 ] = &vectorDomainE2Nat3Nat4;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE2Nat3Nat4( vecDomainsE3Na2Nat3VE2Nat3Nat4 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE2Nat3Nat4( vecDomainsE3Na2Nat3VE2Nat3Nat4 );
	delete vecDomainsE3Na2Nat3VE2Nat3Nat4[ 0 ];
	delete vecDomainsE3Na2Nat3VE2Nat3Nat4[ 1 ];

	cout<<"cTypeFibMatrix typeFibMatrix4( 4 );"<<endl;
	cTypeFibMatrix typeFibMatrix4( 4 );
	
	cout<<"rootD2.getDomains()->addDomain( typeFibMatrix4, &vectorDomainE3Na2Nat3VE2Nat3Nat4 );"<<endl;
	rootD2.getDomains()->addDomain( typeFibMatrix4, &vectorDomainE3Na2Nat3VE2Nat3Nat4 );
	
	cout<<"cFibMatrix setElement( 2, 2, NULL, &rootD2 );"<<endl;
	cFibMatrix setElement( 2, 2, NULL, &rootD2 );
	
	cout<<"setElement.setDomainNr( 1 );"<<endl;
	setElement.setDomainNr( 1 );
	
	cout<<"vecFibMatrix1E2Ch.setDefiningFibElement( &setElement );"<<endl;
	vecFibMatrix1E2Ch.setDefiningFibElement( &setElement );
	
	//test get compressed size
	uiCompressedSize = 4 + 3;
	if ( (unsigned int)(vecFibMatrix1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibMatrix1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibMatrix1E2Dom1.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibMatrix1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibMatrix1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cFibMatrixE2Dom1[] = { (char)ucRestBitCorrect };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibMatrixE2Dom1, 1 );
	
	
	cout<<endl<<"setElement.setDomainNr( 3 );"<<endl;
	setElement.setDomainNr( 3 );
	
	cout<<"vecFibMatrix1E2Ch.setDefiningFibElement( &setElement );"<<endl;
	vecFibMatrix1E2Ch.setDefiningFibElement( &setElement );
	
	//test get compressed size
	uiCompressedSize = 4 + 3;
	if ( (unsigned int)(vecFibMatrix1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibMatrix1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibMatrix1E2Dom3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibMatrix1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibMatrix1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cFibMatrixE2Dom3[] = { (char)ucRestBitCorrect };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibMatrixE2Dom3, 1 );

	
	cout<<endl<<"setElement.setDomainNr( 4 );"<<endl;
	setElement.setDomainNr( 4 );
	
	cout<<"vecFibMatrix1E2Ch.setDefiningFibElement( &setElement );"<<endl;
	vecFibMatrix1E2Ch.setDefiningFibElement( &setElement );
	
	//test get compressed size
	uiCompressedSize = 4 + 5;
	if ( (unsigned int)(vecFibMatrix1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibMatrix1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibMatrix1E2Dom4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibMatrix1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibMatrix1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	const char cFibMatrixE2Dom4[] = { (char)0x63, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibMatrixE2Dom4, 2 );

	
	
	cout<<endl<<"setElement.setDomainNr( 5 );"<<endl;
	setElement.setDomainNr( 5 );
	
	cout<<"vecFibMatrix1E2Ch.setDefiningFibElement( &setElement );"<<endl;
	vecFibMatrix1E2Ch.setDefiningFibElement( &setElement );
	
	//test get compressed size
	uiCompressedSize = 4 + 5;
	if ( (unsigned int)(vecFibMatrix1E2Ch.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			vecFibMatrix1E2Ch.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "vecFibMatrix1E2Dom5.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	cout<<"vecFibMatrix1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );"<<endl;
	bStoreSuccesfull = vecFibMatrix1E2Ch.store( *pFile, cRestBit, cNumberOfRestBit );
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
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibMatrixE2Dom4, 2 );

	
	
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
	
	cout<<"cFibVector * pVecFibMatrixDestination = new cVectorFibMatrix();"<<endl;
	cFibVector  * pVecFibMatrixDestination = new cVectorFibMatrix();
	
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
			unsigned int uiNumberOfFibMatrixs = 0;
			if ( (rand() % 10) != 0 ){
				uiNumberOfFibMatrixs = (rand() % 3 + 1) * (rand() % 4 + 1) + (rand() % 4);
			}else{
				uiNumberOfFibMatrixs = 0;
			}
			cout<<"pVecSource = new cVectorFibMatrix( "<< uiNumberOfFibMatrixs <<", &emptyRoot ); "<<endl;
			pVecSource = new cVectorFibMatrix( uiNumberOfFibMatrixs, &emptyRoot );
			
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
			pVecEqual = new cVectorFibMatrix( pVecSource->getNumberOfElements(), &emptyRoot  );
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
		cout<<"(* pVecFibMatrixDestination) = (* pVecSource );"<<endl;
		(* pVecFibMatrixDestination) = (* pVecSource );
		
		//test the created vector
		if ( (*pVecFibMatrixDestination) == ( * pVecEqual) ){
		
			cout<<"The vecFibMatrixDestination is correct . "<<endl;
		}else{
			cerr<<"Error: The vecFibMatrixDestination is not correct ."<<endl;
			iReturn++;
		}
		
		if ( pVecEqual != pVecSource ){
			//pVecEqual and pVecSource are different vectors
			delete pVecEqual;
		}
		delete pVecSource;
	}
	delete pVecFibMatrixDestination;
	
	return iReturn;
}




















