/**
 * @file tFibMatrix
 * file name: tFibMatrix.cpp
 * @author Betti Oesterholz
 * @date 22.12.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cFibMatrix.
 *
 * Copyright (C) @c GPL3 2011 Betti Oesterholz
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
 * This file contains the test for the class cFibMatrix, which
 * represents a Fib matrix element.
 *
 *
 * What's tested of class cFibMatrix:
 * 	- cFibMatrix( const unsignedIntFib iuNumberOfDimensions, const unsignedIntFib iuNumberOfVectorElements, cFibElement * pInSubobject = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- cFibMatrix( const cFibMatrix &matrixElement );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- bool hasUnderAllObjects( ) const;
 * 	- unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
 * 	- bool evalueObject( iEvaluePosition & evaluePosition, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties ) const;
 * 	- bool evalueObject( iEvalueFibElement & evalueFibElement, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties, const list<char> & liCFibElementTyps );
 * 	- bool equal( const cFibElement & fibObject ) const;
 * 	- bool equalElement( const cFibElement & fibElement ) const;
 * 	- cFibElement *clone( ) const;
 * 	- cFibMatrix *copy( const unsignedIntFib iObjectFibMatrix=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementFibMatrix=0 ) const;
 * 	- bool storeXml( ostream &stream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream &stream ) const;
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
 * 	- unsignedIntFib getNumberOfMatrixDimensions() const;
 * 	- unsignedIntFib getNumberOfVectorElements() const;
 * 	- cFibVariable * getDefinedVariable( const unsignedLongFib uiPosition );
 * 	- unsignedIntFib getDomainNr() const;
 * 	- void setDomainNr( const unsignedLongFib uiInDomainNumber );
 * 	- cVectorArea * getArea( const unsignedIntFib uiDimension=1 );
 * 	- unsignedLongFib getNumberOfVectors() const;
 * 	- const vector< cVectorFibMatrix > getVectors();
 * 	- bool setVectors( const vector< cVectorFibMatrix > & vecMatrixs );
 * 	- cVectorFibMatrix * getVector( const unsignedLongFib uiPosition );
 * 	- bool setVector( const cVectorFibMatrix & vecMatrix, const unsignedLongFib uiPosition );
 * 	- bool addVector( const cVectorFibMatrix & vecMatrix, const unsignedLongFib uiPosition=0 );
 * 	- bool deleteVector( const unsignedLongFib uiPosition );
 * 
 *
 * 
 * Test for:
 *
 * Methods for changing the structur of an Fib object will be tested with
 * tFibElementStructur. Methods for Fib objects will be tested with
 * Methods for storing and restoring will be tested in tFibElementStore.
 */
/*
History:
07.01.2012  Oesterholz  created
09.10.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cFibMatrix.h"
#include "cPoint.h"
#include "cRoot.h"
#include "cProperty.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainIntegerBit.h"
#include "cDomainVector.h"
#include "cDomainVectorOpenEnd.h"
#include "cTypeVariable.h"
#include "cTypeFibMatrix.h"
#include "cTypeInVar.h"
#include "cVectorProperty.h"
#include "cEvaluePositionList.h"
#include "cEvalueFibElementList.h"


#include "tinyxml.h"

#include <algorithm>
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
int testEvalueObject( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testCopy( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );
int testDomainNr( unsigned long &ulTestphase );
int testVectors( unsigned long &ulTestphase );//+ area vectors
int testVariable( unsigned long &ulTestphase );


//the size of the random tests
unsigned long MAX_RAND_TEST_SIZE = 256;

int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	if ( argc >= 2 ){
		//one parameter given; read parameter iterations
		MAX_RAND_TEST_SIZE = atol( argv[ 1 ] );
		if ( MAX_RAND_TEST_SIZE < 1 ){
			MAX_RAND_TEST_SIZE = 1;
		}
	}
	
	cout<<endl<<"Running Test for cFibMatrix methods"<<endl;
	cout<<      "==================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testEvalueObject( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testDomainNr( ulTestphase );
	iReturn += testVectors( ulTestphase );
	iReturn += testVariable( ulTestphase );
	
	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * This method tests the constructor of the cFibMatrix class.
 *
 * methods tested:
 * 	- cFibMatrix( const unsignedIntFib iuNumberOfDimensions, const unsignedIntFib iuNumberOfVectorElements, cFibElement * pInSubobject = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- cFibMatrix( const cFibMatrix &matrixElement );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- unsignedIntFib getNumberOfElement()
 * 	- bool hasUnderAllObjects() const;
 * 	- unsignedIntFib getDomainNr() const;
 * 	- unsignedIntFib getNumberOfMatrixDimensions() const;
 * 	- cVectorArea * getArea( const unsignedIntFib uiDimension=1 );
 * 	- unsignedIntFib getNumberOfVectorElements() const;
 * 	- unsignedLongFib getNumberOfVectors() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cFibMatrix"<<endl;

	cout<<"cFibMatrix fibMatrixEmpty( 0, 0 );"<<endl;
	cFibMatrix fibMatrixEmpty( 0, 0 );
	
	//check the getType() methode from cFibMatrix
	if ( fibMatrixEmpty.getType() == 'm' ){
	
		cout<<"The type of the matrix element is correctly 'm' . "<<endl;
	}else{
		cerr<<"Error: The type of the matrix element is "<<
			fibMatrixEmpty.getType()<<" but should be 'm' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFibMatrix
	if ( fibMatrixEmpty.isValidFibElement() ){
	
		cout<<"The matrix element is correctly a correct matrix element. "<<endl;
	}else{
		cerr<<"Error: The matrix element is not a correct matrix element, but should be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFibMatrix
	if ( fibMatrixEmpty.isMovable() ){
	
		cout<<"The matrix element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The matrix element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFibMatrix
	if ( fibMatrixEmpty.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib element for the matrix element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib element for the matrix element is "<<
			fibMatrixEmpty.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFibMatrix
	if ( fibMatrixEmpty.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib element for the matrix element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element for the matrix element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFibMatrix
	if ( fibMatrixEmpty.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib element for the matrix element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element for the matrix element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibMatrix
	if ( fibMatrixEmpty.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib element for the matrix element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element for the matrix element is "<<
			fibMatrixEmpty.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFibMatrix
	if ( ! fibMatrixEmpty.hasUnderAllObjects()){
	
		cout<<"The matrix element has correctly missing a needed subobjects. "<<endl;
	}else{
		cerr<<"Error: The matrix element is not missing a subobject."<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrixEmpty.getNumberOfMatrixDimensions() == 1 ){
	
		cout<<"The number of dimension variables is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of dimension variables is "<<
			fibMatrixEmpty.getNumberOfMatrixDimensions()<<", but should be 1. "<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrixEmpty.getNumberOfVectorElements() == 0 ){
	
		cout<<"The number of vector elements is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of vector elements is "<<
		fibMatrixEmpty.getNumberOfVectorElements()<<", but should be 1. "<<endl;
		iReturn++;
	}
	//check the getDomainNr() methode from cFibMatrix
	if ( fibMatrixEmpty.getDomainNr() == 0 ){
	
		cout<<"The domain number is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The domain number is "<<fibMatrixEmpty.getDomainNr()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the getArea() methode from cFibMatrix
	cVectorArea vecAreaCorrect( &fibMatrixEmpty );
	cout<<"pAreaVector = fibMatrixEmpty.getArea( 1 ); "<<endl;
	cVectorArea * pAreaVector = fibMatrixEmpty.getArea( 1 );
	if ( pAreaVector == NULL ){
		cerr<<"Error: The 1'th area vector is NULL. "<<endl;
		iReturn++;
	}else if ( (*pAreaVector) == vecAreaCorrect ){
	
		cout<<"The 1'th area vector is correctly (0,0). "<<endl;
	}else{
		cerr<<"Error: The 1'th area vector is not (0,0). "<<endl;
		iReturn++;
	}
	cout<<"pAreaVector = fibMatrixEmpty.getArea( 0 ); "<<endl;
	pAreaVector = fibMatrixEmpty.getArea( 0 );
	if ( pAreaVector == NULL ){
	
		cout<<"The 0'th area vector is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The 0'th area vector is not NULL. "<<endl;
		iReturn++;
	}
	cout<<"pAreaVector = fibMatrixEmpty.getArea( 2 ); "<<endl;
	pAreaVector = fibMatrixEmpty.getArea( 2 );
	if ( pAreaVector == NULL ){
	
		cout<<"The 2'th area vector is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The 2'th area vector is not NULL. "<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrixEmpty.getNumberOfVectors() == 0 ){
	
		cout<<"The number of vectors is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of vectors is "<<fibMatrixEmpty.getNumberOfVectors()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cFibMatrix with 2 dimension variables and 3 vector elements"<<endl;

	cout<<"cFibMatrix fibMatrix4( 2, 3 );"<<endl;
	cFibMatrix fibMatrix4( 2, 3 );

	//check the getType() methode from cFibMatrix
	if ( fibMatrix4.getType() == 'm' ){
	
		cout<<"The type of the matrix element is correctly 'm' . "<<endl;
	}else{
		cerr<<"Error: The type of the matrix element is "<<
			fibMatrix4.getType()<<" but should be 'm' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFibMatrix
	if ( fibMatrix4.isValidFibElement() ){
	
		cout<<"The matrix element is correctly a correct matrix element. "<<endl;
	}else{
		cerr<<"Error: The matrix element is not a correct matrix element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFibMatrix
	if ( fibMatrix4.isMovable() ){
	
		cout<<"The matrix element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The matrix element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFibMatrix
	if ( fibMatrix4.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib element for the matrix element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib element for the matrix element is "<<
			fibMatrix4.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFibMatrix
	if ( fibMatrix4.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib element for the matrix element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element for the matrix element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFibMatrix
	if ( fibMatrix4.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib element for the matrix element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element for the matrix element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibMatrix
	if ( fibMatrix4.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib element for the matrix element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element for the matrix element is "<<
			fibMatrix4.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrix4.getNumberOfVectorElements() == 3 ){
	
		cout<<"The number of variables is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of variables is "<<fibMatrix4.getNumberOfVectorElements()<<
			", but should be 3. "<<endl;
		iReturn++;
	}
	//check the getDomainNr() methode from cFibMatrix
	if ( fibMatrix4.getDomainNr() == 0 ){
	
		cout<<"The domain number is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The domain number is "<<fibMatrix4.getDomainNr()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFibMatrix
	if ( ! fibMatrix4.hasUnderAllObjects() ){
	
		cout<<"The matrix element has correctly not all needed subobjects. "<<endl;
	}else{
		cerr<<"Error: The matrix element is not missing a subobject."<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrix4.getNumberOfMatrixDimensions() == 2 ){
	
		cout<<"The number of dimension variables is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of dimension variables is "<<
			fibMatrix4.getNumberOfMatrixDimensions()<<", but should be 2. "<<endl;
		iReturn++;
	}
	//check the getArea() methode from cFibMatrix
	cout<<"pAreaVector = fibMatrix4.getArea( 1 ); "<<endl;
	pAreaVector = fibMatrix4.getArea( 1 );
	if ( pAreaVector == NULL ){
		cerr<<"Error: The 1'th area vector is NULL. "<<endl;
		iReturn++;
	}else if ( (*pAreaVector) == vecAreaCorrect ){
	
		cout<<"The 1'th area vector is correctly (0,0). "<<endl;
	}else{
		cerr<<"Error: The 1'th area vector is not (0,0). "<<endl;
		iReturn++;
	}
	cout<<"pAreaVector = fibMatrix4.getArea( 2 ); "<<endl;
	pAreaVector = fibMatrix4.getArea( 2 );
	if ( pAreaVector == NULL ){
		cerr<<"Error: The 2'th area vector is NULL. "<<endl;
		iReturn++;
	}else if ( (*pAreaVector) == vecAreaCorrect ){
	
		cout<<"The 2'th area vector is correctly (0,0). "<<endl;
	}else{
		cerr<<"Error: The 2'th area vector is not (0,0). "<<endl;
		iReturn++;
	}
	cout<<"pAreaVector = fibMatrix4.getArea( 0 ); "<<endl;
	pAreaVector = fibMatrix4.getArea( 0 );
	if ( pAreaVector == NULL ){
	
		cout<<"The 0'th area vector is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The 0'th area vector is not NULL. "<<endl;
		iReturn++;
	}
	cout<<"pAreaVector = fibMatrix4.getArea( 3 ); "<<endl;
	pAreaVector = fibMatrix4.getArea( 3 );
	if ( pAreaVector == NULL ){
	
		cout<<"The 3'th area vector is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The 3'th area vector is not NULL. "<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrix4.getNumberOfVectors() == 0 ){
	
		cout<<"The number of vectors is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of vectors is "<<fibMatrix4.getNumberOfVectors()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cFibMatrix with a superior Fib element"<<endl;

	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	
	cout<<"cFibMatrix fibMatrixSup( 3, 2, NULL, &rootEmpty1 );"<<endl;
	cFibMatrix fibMatrixSup( 3, 2, NULL, &rootEmpty1 );

	//check the getType() methode from cFibMatrix
	if ( fibMatrixSup.getType() == 'm' ){
	
		cout<<"The type of the matrix element is correctly 'm' . "<<endl;
	}else{
		cerr<<"Error: The type of the matrix element is "<<
			fibMatrixSup.getType()<<" but should be 'm' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFibMatrix
	if ( fibMatrixSup.isValidFibElement() ){
	
		cout<<"The matrix element is correctly a correct matrix element. "<<endl;
	}else{
		cerr<<"Error: The matrix element is a not correct matrix element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFibMatrix
	if ( fibMatrixSup.isMovable() ){
	
		cout<<"The matrix element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The matrix element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFibMatrix
	if ( fibMatrixSup.getNumberOfElement() == 2 ){
	
		cout<<"The number of the Fib element for the matrix element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib element for the matrix element is "<<
			fibMatrixSup.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFibMatrix
	if ( fibMatrixSup.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib element for the matrix element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element for the matrix element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFibMatrix
	if ( fibMatrixSup.getFibElement( -1 ) == &rootEmpty1 ){
	
		cout<<"The previous Fib element for the matrix element is correctly rootEmpty1. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element for the matrix element is not rootEmpty1."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibMatrix
	if ( fibMatrixSup.getSuperiorFibElement() == &rootEmpty1 ){
	
		cout<<"The superior Fib element for the matrix element is correctly rootEmpty1. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element for the matrix element is "<<
			fibMatrixSup.getSuperiorFibElement() << " and not rootEmpty1."<<endl;
		iReturn++;
	}
	//check the getDomainNr() methode from cFibMatrix
	if ( fibMatrixSup.getDomainNr() == 0 ){
	
		cout<<"The domain number is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The domain number is "<<fibMatrixSup.getDomainNr()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFibMatrix
	if ( ! fibMatrixSup.hasUnderAllObjects() ){
	
		cout<<"The matrix element has correctly not all needed subobjects. "<<endl;
	}else{
		cerr<<"Error: The matrix element is not missing a subobject."<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrixSup.getNumberOfMatrixDimensions() == 3 ){
	
		cout<<"The number of dimension variables is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of dimension variables is "<<
			fibMatrixSup.getNumberOfMatrixDimensions()<<", but should be 3. "<<endl;
		iReturn++;
	}
	//check the getArea() methode from cFibMatrix
	cout<<"pAreaVector = fibMatrixSup.getArea( 1 ); "<<endl;
	pAreaVector = fibMatrixSup.getArea( 1 );
	if ( pAreaVector == NULL ){
		cerr<<"Error: The 1'th area vector is NULL. "<<endl;
		iReturn++;
	}else if ( (*pAreaVector) == vecAreaCorrect ){
	
		cout<<"The 1'th area vector is correctly (0,0). "<<endl;
	}else{
		cerr<<"Error: The 1'th area vector is not (0,0). "<<endl;
		iReturn++;
	}
	cout<<"pAreaVector = fibMatrixSup.getArea( 2 ); "<<endl;
	pAreaVector = fibMatrixSup.getArea( 2 );
	if ( pAreaVector == NULL ){
		cerr<<"Error: The 2'th area vector is NULL. "<<endl;
		iReturn++;
	}else if ( (*pAreaVector) == vecAreaCorrect ){
	
		cout<<"The 2'th area vector is correctly (0,0). "<<endl;
	}else{
		cerr<<"Error: The 2'th area vector is not (0,0). "<<endl;
		iReturn++;
	}
	cout<<"pAreaVector = fibMatrixSup.getArea( 3 ); "<<endl;
	pAreaVector = fibMatrixSup.getArea( 3 );
	if ( pAreaVector == NULL ){
		cerr<<"Error: The 3'th area vector is NULL. "<<endl;
		iReturn++;
	}else if ( (*pAreaVector) == vecAreaCorrect ){
	
		cout<<"The 3'th area vector is correctly (0,0). "<<endl;
	}else{
		cerr<<"Error: The 3'th area vector is not (0,0). "<<endl;
		iReturn++;
	}
	cout<<"pAreaVector = fibMatrixSup.getArea( 0 ); "<<endl;
	pAreaVector = fibMatrixSup.getArea( 0 );
	if ( pAreaVector == NULL ){
	
		cout<<"The 0'th area vector is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The 0'th area vector is not NULL. "<<endl;
		iReturn++;
	}
	cout<<"pAreaVector = fibMatrixSup.getArea( 4 ); "<<endl;
	pAreaVector = fibMatrixSup.getArea( 4 );
	if ( pAreaVector == NULL ){
	
		cout<<"The 4'th area vector is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The 4'th area vector is not NULL. "<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrixSup.getNumberOfVectorElements() == 2 ){
	
		cout<<"The number of variables is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of variables is "<<fibMatrixSup.getNumberOfVectorElements()<<
			", but should be 2. "<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrixSup.getNumberOfVectors() == 0 ){
	
		cout<<"The number of vectors is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of vectors is "<<fibMatrixSup.getNumberOfVectors()<<
			", but should be 0. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cFibMatrix with a subobject"<<endl;
	
	cout<<"cFibMatrix fibMatrixNextPrev( 2, 7, &fibMatrixEmpty );"<<endl;
	cFibMatrix fibMatrixNextPrev( 2, 7, &fibMatrixEmpty );

	//check the getType() methode from cFibMatrix
	if ( fibMatrixNextPrev.getType() == 'm' ){
	
		cout<<"The type of the matrix element is correctly 'm' . "<<endl;
	}else{
		cerr<<"Error: The type of the matrix element is "<<
			fibMatrixNextPrev.getType()<<" but should be 'm' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFibMatrix
	if ( fibMatrixNextPrev.isValidFibElement() ){
	
		cout<<"The matrix element is correctly a correct matrix element. "<<endl;
	}else{
		cerr<<"Error: The matrix element is not a correct matrix element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFibMatrix
	if ( fibMatrixNextPrev.isMovable() ){
	
		cout<<"The matrix element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The matrix element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFibMatrix
	if ( fibMatrixNextPrev.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib element for the matrix element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib element for the matrix element is "<<
			fibMatrixNextPrev.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFibMatrix
	if ( fibMatrixNextPrev.getNextFibElement() == &fibMatrixEmpty ){
	
		cout<<"The next/ main Fib element for the matrix element is correctly fibMatrixEmpty. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element for the matrix element is not fibMatrixEmpty."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFibMatrix
	if ( fibMatrixNextPrev.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib element for the matrix element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element for the matrix element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibMatrix
	if ( fibMatrixNextPrev.getSuperiorFibElement() == NULL){
	
		cout<<"The superior Fib element for the matrix element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element for the matrix element is "<<
			fibMatrixNextPrev.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrixNextPrev.getNumberOfVectorElements() == 7 ){
	
		cout<<"The number of variables is correctly 7. "<<endl;
	}else{
		cerr<<"Error: The number of variables is "<<fibMatrixNextPrev.getNumberOfVectorElements()<<
			", but should be 7. "<<endl;
		iReturn++;
	}
	//check the getDomainNr() methode from cFibMatrix
	if ( fibMatrixNextPrev.getDomainNr() == 0 ){
	
		cout<<"The domain number is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The domain number is "<<fibMatrixNextPrev.getDomainNr()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFibMatrix
	if ( ! fibMatrixNextPrev.hasUnderAllObjects()  ){
	
		cout<<"The matrix element has correctly not all needed subobjects. "<<endl;
	}else{
		cerr<<"Error: The matrix element is not missing a subobject."<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrixNextPrev.getNumberOfMatrixDimensions() == 2 ){
	
		cout<<"The number of dimension variables is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of dimension variables is "<<
			fibMatrixNextPrev.getNumberOfMatrixDimensions()<<", but should be 2. "<<endl;
		iReturn++;
	}
	//check the getArea() methode from cFibMatrix
	cout<<"pAreaVector = fibMatrixNextPrev.getArea( 1 ); "<<endl;
	pAreaVector = fibMatrixNextPrev.getArea( 1 );
	if ( pAreaVector == NULL ){
		cerr<<"Error: The 1'th area vector is NULL. "<<endl;
		iReturn++;
	}else if ( (*pAreaVector) == vecAreaCorrect ){
	
		cout<<"The 1'th area vector is correctly (0,0). "<<endl;
	}else{
		cerr<<"Error: The 1'th area vector is not (0,0). "<<endl;
		iReturn++;
	}
	cout<<"pAreaVector = fibMatrixNextPrev.getArea( 2 ); "<<endl;
	pAreaVector = fibMatrixNextPrev.getArea( 2 );
	if ( pAreaVector == NULL ){
		cerr<<"Error: The 2'th area vector is NULL. "<<endl;
		iReturn++;
	}else if ( (*pAreaVector) == vecAreaCorrect ){
	
		cout<<"The 2'th area vector is correctly (0,0). "<<endl;
	}else{
		cerr<<"Error: The 2'th area vector is not (0,0). "<<endl;
		iReturn++;
	}
	cout<<"pAreaVector = fibMatrixNextPrev.getArea( 0 ); "<<endl;
	pAreaVector = fibMatrixNextPrev.getArea( 0 );
	if ( pAreaVector == NULL ){
	
		cout<<"The 0'th area vector is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The 0'th area vector is not NULL. "<<endl;
		iReturn++;
	}
	cout<<"pAreaVector = fibMatrixNextPrev.getArea( 3 ); "<<endl;
	pAreaVector = fibMatrixNextPrev.getArea( 3 );
	if ( pAreaVector == NULL ){
	
		cout<<"The 3'th area vector is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The 3'th area vector is not NULL. "<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrixNextPrev.getNumberOfVectors() == 0 ){
	
		cout<<"The number of vectors is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of vectors is "<<fibMatrixNextPrev.getNumberOfVectors()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrixNextPrev.getNumberOfVectorElements() == 7 ){
	
		cout<<"The number of variables is correctly 7. "<<endl;
	}else{
		cerr<<"Error: The number of variables is "<<fibMatrixNextPrev.getNumberOfVectorElements()<<
			", but should be 7. "<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cFibMatrix with all parameters given"<<endl;
	
	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeFibMatrix testTypeFibMatrix;"<<endl;
	cTypeFibMatrix testTypeFibMatrix;
	
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

	cout<<"rootD2.getDomains()->addDomain( typeFibMatrix, &vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3 );"<<endl;
	rootD2.getDomains()->addDomain( typeFibMatrix, &vectorDomainE3Na2Nat3VE2Nat5Nat3VE3Nat1Nat2Nat3 );

	cout<<"cPoint point1;"<<endl;
	cPoint point1;

	cout<<"cFibMatrix fibMatrixFull( 1, 2, &point1, &rootD2 );"<<endl;
	cFibMatrix fibMatrixFull( 1, 2, &point1, &rootD2 );

	//check the getType() methode from cFibMatrix
	if ( fibMatrixFull.getType() == 'm' ){
	
		cout<<"The type of the matrix element is correctly 'm' . "<<endl;
	}else{
		cerr<<"Error: The type of the matrix element is "<<
			fibMatrixFull.getType()<<" but should be 'm' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFibMatrix
	if ( fibMatrixFull.isValidFibElement() ){
	
		cout<<"The matrix element is correctly a correct matrix element. "<<endl;
	}else{
		cerr<<"Error: The matrix element is not a correct matrix element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFibMatrix
	if ( fibMatrixFull.isMovable() ){
	
		cout<<"The matrix element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The matrix element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFibMatrix
	if ( fibMatrixFull.getNumberOfElement() == 2 ){
	
		cout<<"The number of the Fib element for the matrix element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib element for the matrix element is "<<
			fibMatrixFull.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFibMatrix
	if ( fibMatrixFull.getNextFibElement() == &point1 ){
	
		cout<<"The next/ main Fib element for the matrix element is correctly fibMatrixEmpty. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element for the matrix element is not fibMatrixEmpty."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFibMatrix
	if ( fibMatrixFull.getFibElement( -1 ) == &rootD2 ){
	
		cout<<"The previous Fib element for the matrix element is correctly rootD2. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element for the matrix element is not rootD2."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibMatrix
	if ( fibMatrixFull.getSuperiorFibElement() == &rootD2 ){
	
		cout<<"The superior Fib element for the matrix element is correctly rootD2. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element for the matrix element is "<<
			fibMatrixFull.getSuperiorFibElement() << " and not rootD2."<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrixFull.getNumberOfVectorElements() == 2 ){
	
		cout<<"The number of variables is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of variables is "<<fibMatrixFull.getNumberOfVectorElements()<<
			", but should be 2. "<<endl;
		iReturn++;
	}
	//check the getDomainNr() methode from cFibMatrix
	if ( fibMatrixFull.getDomainNr() == 0 ){
	
		cout<<"The domain number is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The domain number is "<<fibMatrixFull.getDomainNr()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFibMatrix
	if ( fibMatrixFull.hasUnderAllObjects() ){
	
		cout<<"The matrix element has correctly all needed subobjects. "<<endl;
	}else{
		cerr<<"Error: The matrix element is missing a subobject."<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrixFull.getNumberOfMatrixDimensions() == 1 ){
	
		cout<<"The number of dimension variables is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of dimension variables is "<<
			fibMatrixFull.getNumberOfMatrixDimensions()<<", but should be 1. "<<endl;
		iReturn++;
	}
	//check the getArea() methode from cFibMatrix
	cout<<"pAreaVector = fibMatrixFull.getArea( 1 ); "<<endl;
	pAreaVector = fibMatrixFull.getArea( 1 );
	if ( pAreaVector == NULL ){
		cerr<<"Error: The 1'th area vector is NULL. "<<endl;
		iReturn++;
	}else if ( (*pAreaVector) == vecAreaCorrect ){
	
		cout<<"The 1'th area vector is correctly (0,0). "<<endl;
	}else{
		cerr<<"Error: The 1'th area vector is not (0,0). "<<endl;
		iReturn++;
	}
	cout<<"pAreaVector = fibMatrixFull.getArea( 0 ); "<<endl;
	pAreaVector = fibMatrixFull.getArea( 0 );
	if ( pAreaVector == NULL ){
	
		cout<<"The 0'th area vector is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The 0'th area vector is not NULL. "<<endl;
		iReturn++;
	}
	cout<<"pAreaVector = fibMatrixFull.getArea( 2 ); "<<endl;
	pAreaVector = fibMatrixFull.getArea( 2 );
	if ( pAreaVector == NULL ){
	
		cout<<"The 3'th area vector is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The 3'th area vector is not NULL. "<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrixFull.getNumberOfVectorElements() == 2 ){
	
		cout<<"The number of variables is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of variables is "<<fibMatrixFull.getNumberOfVectorElements()<<
			", but should be 2. "<<endl;
		iReturn++;
	}
	//check the getNumberOfVectorElements() methode from cFibMatrix
	if ( fibMatrixFull.getNumberOfVectors() == 0 ){
	
		cout<<"The number of vectors is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of vectors is "<<fibMatrixFull.getNumberOfVectors()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	
	return iReturn;
}




/**
 * This if compares the to given listlists.
 * It ignores the orter of the elements in the lists.
 *
 * @param liEvaluedProperties the first list with the listvectors,
 * 	which are to be compared; this listlist sould be evalued
 * @param liToGiveBackPropertyVectors the second list with the listvectors,
 * 	which are to be compared; this listlist sould be the correct properties
 */
int comparePropertyLists( const list<cVectorProperty> & liEvaluedProperties,
		const list<cVectorProperty> & liToGiveBackPropertyVectors ){
	
	int iReturn = 0;
	
	if ( liEvaluedProperties.size() == liToGiveBackPropertyVectors.size() ){
	
		cout<<"Ther are correctly "<< liEvaluedProperties.size() <<
			" properties given back. "<<endl;
		
		bool bPropertiesCorrect = true;
		unsigned int uiListPosition = 1;
		list<cVectorProperty>::const_iterator itrEvaluedListVector =
			liEvaluedProperties.begin();
		for ( list<cVectorProperty>::const_iterator itrListVector =
				liToGiveBackPropertyVectors.begin();
				itrListVector != liToGiveBackPropertyVectors.end();
				itrListVector++, itrEvaluedListVector++, uiListPosition++ ){
			
			if ( (*itrListVector) != (*itrEvaluedListVector) ){
				cerr<<"Error: The "<< uiListPosition <<
					"'th property couldn't be found in the evalued propertylist.  "<<endl;
				iReturn++;
				bPropertiesCorrect = false;
			}
		}
		if ( bPropertiesCorrect ){
			cout<<"All evalued properties are correct. "<<endl;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< liEvaluedProperties.size() <<
			" properties evalued, but it should be "<<
			liToGiveBackPropertyVectors.size() <<".  "<<endl;
		iReturn++;
	}
	return iReturn;
}


/**
 * This if compares the given evalued position lists.
 *
 * @param liEvaluedPositionData the first list with the positions and ther properties,
 * 	which are to be compared; this list sould be evalued
 * @param liToGiveBackPoints the second list with the positions and ther properties,
 * 	which are to be compared; this listlist sould be the correct properties
 */
int compairEvaluedPoints(
		const list< pair< cVectorPosition, list<cVectorProperty> > > & liEvaluedPositionData,
		const list< pair< const cVectorPosition *, list<cVectorProperty> > > & liToGiveBackPoints ){
	
	int iReturn = 0;
	
	if ( liEvaluedPositionData.size() == liToGiveBackPoints.size() ){
	
		cout<<"Ther are correctly "<< liEvaluedPositionData.size() <<
			" points evalued. "<<endl;
		
		unsigned int uiListPosition = 1;
		list< pair< cVectorPosition, list<cVectorProperty> > >::const_iterator
			itrListPair1 = liEvaluedPositionData.begin();
		for ( list< pair< const cVectorPosition *, list<cVectorProperty> > >::const_iterator
				itrListPair2 = liToGiveBackPoints.begin();
				(itrListPair1 != liEvaluedPositionData.end()) &&
				(itrListPair2 != liToGiveBackPoints.end());
				itrListPair1++, itrListPair2++, uiListPosition++ ){
			
			//compair the points
			cout<<"Comparing the "<< uiListPosition <<"'th point:"<<endl;
			if ( (itrListPair1->first) == *(itrListPair2->first) ){
				cout<<"The positions are equal."<<endl;
			}else{
				cerr<<"Error: The positions are not equal."<<endl;
				cerr<<"Evalued position: "<<endl;
				itrListPair1->first.storeXml( cerr );
				cerr<<"Correct position: "<<endl;
				itrListPair2->first->storeXml( cerr );
				cerr<<endl;
				iReturn++;
			}
			//compair the properties
			iReturn += comparePropertyLists( itrListPair1->second, itrListPair2->second );
		}
	}else{
		cerr<<"Error: Ther wher "<< liEvaluedPositionData.size() <<
			" points evalued, but it should be "<<
			liToGiveBackPoints.size() <<".  "<<endl;
		iReturn++;
	}
	return iReturn;
}


/**
 * This if compares the given evalued Fib element lists.
 *
 * @param liEvaluedElements the first list with the Fib elements and ther properties,
 * 	which are to be compared; this list sould be evalued
 * @param liToGiveBackElements the second list with the Fib elements and ther properties,
 * 	which are to be compared; this listlist sould be the correct properties
 */
int compairEvaluedFibElements(
		const list< pair< cFibElement*, list<cVectorProperty> > > & liEvaluedElements,
		const list< pair< const cFibElement*, list<cVectorProperty> > > & liToGiveBackElements ){
	
	int iReturn = 0;
	
	if ( liEvaluedElements.size() == liToGiveBackElements.size() ){
	
		cout<<"Ther are correctly "<< liEvaluedElements.size() <<
			" points evalued. "<<endl;
		
		unsigned int uiListPosition = 1;
		list< pair< cFibElement*, list<cVectorProperty> > >::const_iterator
			itrListPair1 = liEvaluedElements.begin();
		for ( list< pair< const cFibElement*, list<cVectorProperty> > >::const_iterator
				itrListPair2 = liToGiveBackElements.begin();
				(itrListPair1 != liEvaluedElements.end()) &&
				(itrListPair2 != liToGiveBackElements.end());
				itrListPair1++, itrListPair2++, uiListPosition++ ){
			
			//compair the points
			cout<<"Comparing the "<< uiListPosition <<"'th point:"<<endl;
			if ( (itrListPair1->first) == (itrListPair2->first) ){
				cout<<"The Fib elements are equal."<<endl;
			}else{
				cerr<<"Error: The Fib elements are not equal."<<endl;
				iReturn++;
			}
			//compair the properties
			iReturn += comparePropertyLists( itrListPair1->second, itrListPair2->second );
		}
	}else{
		cerr<<"Error: Ther wher "<< liEvaluedElements.size() <<
			" points evalued, but it should be "<<
			liToGiveBackElements.size() <<".  "<<endl;
		iReturn++;
	}
	return iReturn;
}



/**
 * This if compares the given evalued Fib element lists.
 *
 * @param liEvaluedElements the first list with the Fib elements and ther properties,
 * 	which are to be compared; this list sould be evalued
 * @param liToGiveBackElements the second list with the Fib elements and ther properties,
 * 	which are to be compared; this listlist sould be the correct properties
 */
int compairEvaluedFibElements(
		const list< pair< const cFibElement*, list<cVectorProperty> > > & liEvaluedElements,
		const list< pair< const cFibElement*, list<cVectorProperty> > > & liToGiveBackElements ){
	
	int iReturn = 0;
	
	if ( liEvaluedElements.size() == liToGiveBackElements.size() ){
	
		cout<<"Ther are correctly "<< liEvaluedElements.size() <<
			" points evalued. "<<endl;
		
		unsigned int uiListPosition = 1;
		list< pair< const cFibElement*, list<cVectorProperty> > >::const_iterator
			itrListPair1 = liEvaluedElements.begin();
		for ( list< pair< const cFibElement*, list<cVectorProperty> > >::const_iterator
				itrListPair2 = liToGiveBackElements.begin();
				(itrListPair1 != liEvaluedElements.end()) &&
				(itrListPair2 != liToGiveBackElements.end());
				itrListPair1++, itrListPair2++, uiListPosition++ ){
			
			//compair the points
			cout<<"Comparing the "<< uiListPosition <<"'th point:"<<endl;
			if ( (itrListPair1->first) == (itrListPair2->first) ){
				cout<<"The Fib elements are equal."<<endl;
			}else{
				cerr<<"Error: The Fib elements are not equal."<<endl;
				iReturn++;
			}
			//compair the properties
			iReturn += comparePropertyLists( itrListPair1->second, itrListPair2->second );
		}
	}else{
		cerr<<"Error: Ther wher "<< liEvaluedElements.size() <<
			" points evalued, but it should be "<<
			liToGiveBackElements.size() <<".  "<<endl;
		iReturn++;
	}
	return iReturn;
}


/**
 * This method tests the constructor of the cList class.
 *
 * methods tested:
 * 	- unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
 * 	- bool evalueObject( iEvaluePosition & evaluePosition, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties ) const;
 * 	- bool evalueObject( iEvalueFibElement & evalueFibElement, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties, const list<char> & liCFibElementTyps );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testEvalueObject( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibMatrix with the vector with values to set from 3 and 6"<<endl;

	cout<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );

	cout<<"cPoint point1( &vecPositionE2 );"<<endl;
	cPoint point1( &vecPositionE2 );
	
	cout<<"cVectorProperty vecPropertyColorRGB( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyColorRGB( cTypeProperty::COLOR_RGB );
	cout<<"cProperty property1( vecPropertyColorRGB, &point1 );"<<endl;
	cProperty property1( vecPropertyColorRGB, &point1 );

	cout<<"cFibMatrix fibMatrix1( 1, 1, &property1 );"<<endl;
	cFibMatrix fibMatrix1( 1, 1, &property1 );

	cout<<"fibMatrix1.getArea( 1 )->setLowerBoundValue( 1 );"<<endl;
	fibMatrix1.getArea( 1 )->setLowerBoundValue( 1 );
	cout<<"fibMatrix1.getArea( 1 )->setUpperBoundValue( 7 );"<<endl;
	fibMatrix1.getArea( 1 )->setUpperBoundValue( 7 );
	
	cout<<"cVectorFibMatrix vecFibMatrixE1V1( fibMatrix1 );"<<endl;
	cVectorFibMatrix vecFibMatrixE1V1( fibMatrix1 );
	cout<<"vecFibMatrixE1V1.setValue( 1, 3 );"<<endl;
	vecFibMatrixE1V1.setValue( 1, 3 );
	cout<<"fibMatrix1.addVector( vecFibMatrixE1V1 );"<<endl;
	fibMatrix1.addVector( vecFibMatrixE1V1 );
	
	cout<<"cVectorFibMatrix vecFibMatrixE1V2( fibMatrix1 );"<<endl;
	cVectorFibMatrix vecFibMatrixE1V2( fibMatrix1 );
	cout<<"vecFibMatrixE1V2.setValue( 1, 6 );"<<endl;
	vecFibMatrixE1V2.setValue( 1, 6 );
	cout<<"fibMatrix1.addVector( vecFibMatrixE1V2 );"<<endl;
	fibMatrix1.addVector( vecFibMatrixE1V2 );

	cout<<"point1.getPosition()->setVariable( 1, fibMatrix1.getDefinedVariable( 1 ) );"<<endl;
	point1.getPosition()->setVariable( 1, fibMatrix1.getDefinedVariable( 1 ) );
	cout<<"point1.getPosition()->setVariable( 2, fibMatrix1.getDefinedVariable( 2 ) );"<<endl;
	point1.getPosition()->setVariable( 2, fibMatrix1.getDefinedVariable( 2 ) );

	cout<<"property1.getProperty()->setVariable( 1, fibMatrix1.getDefinedVariable( 1 ) );"<<endl;
	property1.getProperty()->setVariable( 1, fibMatrix1.getDefinedVariable( 1 ) );
	cout<<"property1.getProperty()->setVariable( 2, fibMatrix1.getDefinedVariable( 2 ) );"<<endl;
	property1.getProperty()->setVariable( 2, fibMatrix1.getDefinedVariable( 2 ) );
	
	unsigned int uiPointsToEvalue = 2;
	
	unsigned int uiTimeNeeded = 2 * (2 + (3 + 4));

	//check the getTimeNeed() methode from cList
	cout<<"fibMatrix1.getTimeNeed()"<<endl;
	if ( fibMatrix1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibMatrix1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cList
	cout<<"fibMatrix1.getTimeNeed( 4 )"<<endl;
	if ( fibMatrix1.getTimeNeed( 4 ) == 4 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 4 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibMatrix1.getTimeNeed( 4 ) <<", but should be "<< 4 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"list<cVectorProperty> liVecProperties;"<<endl;
	list<cVectorProperty> liVecProperties;
	
	//generate to evalue data
	list< pair< const cVectorPosition*, list<cVectorProperty> > > liPointsToEvalue;
	cVectorPosition vecPositionE2V1( 2 );
	vecPositionE2V1.setValue( 1, 1 );
	vecPositionE2V1.setValue( 2, 3 );
	cVectorProperty vecPropertyColorRGBV1( cTypeProperty::COLOR_RGB );
	vecPropertyColorRGBV1.setValue( 1, 1 );
	vecPropertyColorRGBV1.setValue( 2, 3 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V1, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorRGBV1 );
	cVectorPosition vecPositionE2V2( 2 );
	vecPositionE2V2.setValue( 1, 2 );
	vecPositionE2V2.setValue( 2, 6 );
	cVectorProperty vecPropertyColorRGBV2( cTypeProperty::COLOR_RGB );
	vecPropertyColorRGBV2.setValue( 1, 2 );
	vecPropertyColorRGBV2.setValue( 2, 6 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V2, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorRGBV2 );
	
	cEvaluePositionList evaluePositionList;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"fibMatrix1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bool bObjectEvalued = fibMatrix1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrix1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );


	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"list<char> liCFibElementTyps;"<<endl;
	list<char> liCFibElementTyps;
	
	cEvalueFibElementList evalueFibElementList;
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	list< pair< const cFibElement*, list<cVectorProperty> > > liFibElementsToEvalue;
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorRGBV1 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorRGBV2 );
	cout<<"fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrix1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibMatrix with a global property list given"<<endl;
	
	cout<<"cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );
	
	list< pair< const cVectorPosition*, list<cVectorProperty> > >::iterator
		itrPositionProperties = liPointsToEvalue.begin();
	itrPositionProperties->second.push_front( vecPropertyLayer );
	itrPositionProperties++;
	itrPositionProperties->second.push_front( vecPropertyLayer );
	
	uiTimeNeeded = 2 * (2 + (3 + 4));

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"fibMatrix1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	list< pair< const cFibElement*, list<cVectorProperty> > >::iterator
		itrElementProperties = liFibElementsToEvalue.begin();
	itrElementProperties->second.push_front( vecPropertyLayer );
	itrElementProperties++;
	itrElementProperties->second.push_front( vecPropertyLayer );

	cout<<"fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibMatrix with the a vector with values to set from 3, 6, 5 and 4"<<endl;

	cout<<"cVectorFibMatrix vecFibMatrixE1V5( fibMatrix1 );"<<endl;
	cVectorFibMatrix vecFibMatrixE1V5( fibMatrix1 );
	cout<<"vecFibMatrixE1V5.setValue( 1, 5);"<<endl;
	vecFibMatrixE1V5.setValue( 1, 5);
	cout<<"fibMatrix1.addVector( vecFibMatrixE1V5 );"<<endl;
	fibMatrix1.addVector( vecFibMatrixE1V5 );
	
	cout<<"cVectorFibMatrix vecFibMatrixE1V4( fibMatrix1 );"<<endl;
	cVectorFibMatrix vecFibMatrixE1V4( fibMatrix1 );
	cout<<"vecFibMatrixE1V4.setValue( 1, 4);"<<endl;
	vecFibMatrixE1V4.setValue( 1, 4);
	cout<<"fibMatrix1.addVector( vecFibMatrixE1V4 );"<<endl;
	fibMatrix1.addVector( vecFibMatrixE1V4 );
	
	uiPointsToEvalue = 4;
	
	//generate to evalue data
	cVectorProperty vecPropertyColorRGBV5( cTypeProperty::COLOR_RGB );
	vecPropertyColorRGBV5.setValue( 1, 3 );
	vecPropertyColorRGBV5.setValue( 2, 5 );
	cVectorProperty vecPropertyColorRGBV4( cTypeProperty::COLOR_RGB );
	vecPropertyColorRGBV4.setValue( 1, 4 );
	vecPropertyColorRGBV4.setValue( 2, 4 );

	cVectorPosition vecPositionE2V3( 2 );
	vecPositionE2V3.setValue( 1, 3 );
	vecPositionE2V3.setValue( 2, 5 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V3, list<cVectorProperty>() ) );
	cVectorPosition vecPositionE2V4( 2 );
	vecPositionE2V4.setValue( 1, 4 );
	vecPositionE2V4.setValue( 2, 4 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V4, list<cVectorProperty>() ) );
	
	itrPositionProperties = liPointsToEvalue.begin();
	itrPositionProperties->second.clear();
	itrPositionProperties->second.push_back( vecPropertyColorRGBV1 );
	itrPositionProperties++;
	itrPositionProperties->second.clear();
	itrPositionProperties->second.push_back( vecPropertyColorRGBV2 );
	itrPositionProperties++;
	itrPositionProperties->second.push_back( vecPropertyColorRGBV5 );
	itrPositionProperties++;
	itrPositionProperties->second.push_back( vecPropertyColorRGBV4 );

	uiTimeNeeded = uiPointsToEvalue * (2 + (3 + 4));

	//check the getTimeNeed() methode from cList
	cout<<"fibMatrix1.getTimeNeed()"<<endl;
	if ( fibMatrix1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibMatrix1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}

	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrix1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	
	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrix1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	
	itrElementProperties = liFibElementsToEvalue.begin();
	itrElementProperties->second.clear();
	itrElementProperties->second.push_back( vecPropertyColorRGBV1 );
	itrElementProperties++;
	itrElementProperties->second.clear();
	itrElementProperties->second.push_back( vecPropertyColorRGBV2 );
	itrElementProperties++;
	itrElementProperties->second.push_back( vecPropertyColorRGBV5 );
	itrElementProperties++;
	itrElementProperties->second.push_back( vecPropertyColorRGBV4 );
	cout<<"fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrix1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibMatrix with the a vector with values to set from 3, 6, 5, 4, 5, 5, 13, -1 "<<endl;

	cout<<"fibMatrix1.addVector( vecFibMatrixE1V5 );"<<endl;
	fibMatrix1.addVector( vecFibMatrixE1V5 );
	cout<<"fibMatrix1.addVector( vecFibMatrixE1V5 );"<<endl;
	fibMatrix1.addVector( vecFibMatrixE1V5 );

	cout<<"cVectorFibMatrix vecFibMatrixE1V13( fibMatrix1 );"<<endl;
	cVectorFibMatrix vecFibMatrixE1V13( fibMatrix1 );
	cout<<"vecFibMatrixE1V13.setValue( 1, 13 );"<<endl;
	vecFibMatrixE1V13.setValue( 1, 13 );
	cout<<"fibMatrix1.addVector( vecFibMatrixE1V13 );"<<endl;
	fibMatrix1.addVector( vecFibMatrixE1V13 );

	cout<<"cVectorFibMatrix vecFibMatrixE1Vm1( fibMatrix1 );"<<endl;
	cVectorFibMatrix vecFibMatrixE1Vm1( fibMatrix1 );
	cout<<"vecFibMatrixE1Vm1.setValue( 1, -1 );"<<endl;
	vecFibMatrixE1Vm1.setValue( 1, -1 );
	cout<<"fibMatrix1.addVector( vecFibMatrixE1Vm1 );"<<endl;
	fibMatrix1.addVector( vecFibMatrixE1Vm1 );
	
	uiPointsToEvalue = 7;
	
	//generate to evalue data
	cVectorProperty vecPropertyColorRGBV7( cTypeProperty::COLOR_RGB );
	vecPropertyColorRGBV7.setValue( 1, 5 );
	vecPropertyColorRGBV7.setValue( 2, 5 );
	cVectorProperty vecPropertyColorRGBV8( cTypeProperty::COLOR_RGB );
	vecPropertyColorRGBV8.setValue( 1, 6 );
	vecPropertyColorRGBV8.setValue( 2, 5 );
	cVectorProperty vecPropertyColorRGBV9( cTypeProperty::COLOR_RGB );
	vecPropertyColorRGBV9.setValue( 1, 7 );
	vecPropertyColorRGBV9.setValue( 2, 13 );

	cVectorPosition vecPositionE2V5( 2 );
	vecPositionE2V5.setValue( 1, 5 );
	vecPositionE2V5.setValue( 2, 5 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V5, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorRGBV7 );
	cVectorPosition vecPositionE2V6( 2 );
	vecPositionE2V6.setValue( 1, 6 );
	vecPositionE2V6.setValue( 2, 5 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V6, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorRGBV8 );
	cVectorPosition vecPositionE2V7( 2 );
	vecPositionE2V7.setValue( 1, 7 );
	vecPositionE2V7.setValue( 2, 13 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V7, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorRGBV9 );
	
	uiTimeNeeded = uiPointsToEvalue * (2 + (3 + 4));

	//check the getTimeNeed() methode from cList
	cout<<"fibMatrix1.getTimeNeed()"<<endl;
	if ( fibMatrix1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibMatrix1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}

	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrix1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrix1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorRGBV7 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorRGBV8 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorRGBV9 );
	
	cout<<"fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrix1.evalueObjectSimple( storeEvaluedElement );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibMatrix with the a vector with values to set from 1 till 2, 5 till 4, 5, 5, 13, -1, 1.25, 1.24, 1.26 "<<endl;

	cout<<"fibMatrix1.getArea( 1 )->setUpperBoundValue( 20 );"<<endl;
	fibMatrix1.getArea( 1 )->setUpperBoundValue( 20 );
	
	cVectorProperty vecPropertyColorRGBV10( cTypeProperty::COLOR_RGB );
	vecPropertyColorRGBV10.setValue( 1, 8 );
	vecPropertyColorRGBV10.setValue( 2, -1 );
	
	cVectorPosition vecPositionE2V8( 2 );
	vecPositionE2V8.setValue( 1, 8 );
	vecPositionE2V8.setValue( 2, -1 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V8, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorRGBV10 );
	
	cout<<"cVectorFibMatrix vecFibMatrixE1( fibMatrix1 );"<<endl;
	cVectorFibMatrix vecFibMatrixE1( fibMatrix1 );
	cout<<"vecFibMatrixE1.setValue( 1 1.25 );"<<endl;
	vecFibMatrixE1.setValue( 1, 1.25 );
	cout<<"fibMatrix1.addVector( vecFibMatrixE1 );"<<endl;
	fibMatrix1.addVector( vecFibMatrixE1 );
	cout<<"vecFibMatrixE1.setValue( 1 1.24 );"<<endl;
	vecFibMatrixE1.setValue( 1, 1.24 );
	cout<<"fibMatrix1.addVector( vecFibMatrixE1 );"<<endl;
	fibMatrix1.addVector( vecFibMatrixE1 );
	cout<<"vecFibMatrixE1.setValue( 1, 1.26 );"<<endl;
	vecFibMatrixE1.setValue( 1, 1.26 );
	cout<<"fibMatrix1.addVector( vecFibMatrixE1 );"<<endl;
	fibMatrix1.addVector( vecFibMatrixE1 );
	
	uiPointsToEvalue = 11;
	
	//generate to evalue data
	cVectorProperty vecPropertyColorRGBE1( cTypeProperty::COLOR_RGB );

	cVectorPosition vecPositionE2V9( 2 );
	vecPositionE2V9.setValue( 1, 9 );
	vecPositionE2V9.setValue( 2, 1.25 );
	vecPropertyColorRGBE1.setValue( 1, 9 );
	vecPropertyColorRGBE1.setValue( 2, 1.25 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V9, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorRGBE1 );
	cVectorPosition vecPositionE2V10( 2 );
	vecPositionE2V10.setValue( 1, 10);
	vecPositionE2V10.setValue( 2, 1.24 );
	vecPropertyColorRGBE1.setValue( 1, 10 );
	vecPropertyColorRGBE1.setValue( 2, 1.24 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V10, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorRGBE1 );
	cVectorPosition vecPositionE2V11( 2 );
	vecPositionE2V11.setValue( 1, 11 );
	vecPositionE2V11.setValue( 2, 1.26 );
	vecPropertyColorRGBE1.setValue( 1, 11 );
	vecPropertyColorRGBE1.setValue( 2, 1.26 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V11, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorRGBE1 );

	uiTimeNeeded = uiPointsToEvalue * (2 + (3 + 4));

	//check the getTimeNeed() methode from cList
	cout<<"fibMatrix1.getTimeNeed()"<<endl;
	if ( fibMatrix1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibMatrix1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}

	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrix1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrix1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	vecPropertyColorRGBE1.setValue( 1, 8 );
	vecPropertyColorRGBE1.setValue( 2, -1);
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorRGBE1 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	vecPropertyColorRGBE1.setValue( 1, 9 );
	vecPropertyColorRGBE1.setValue( 2, 1.25 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorRGBE1 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	vecPropertyColorRGBE1.setValue( 1, 10 );
	vecPropertyColorRGBE1.setValue( 2, 1.24 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorRGBE1 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	vecPropertyColorRGBE1.setValue( 1, 11 );
	vecPropertyColorRGBE1.setValue( 2, 1.26 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorRGBE1 );
	
	cout<<"fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrix1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibMatrix for non existing object point 1"<<endl;
	
	uiPointsToEvalue = 0;
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrix1.evalueObject( evaluePositionList, 4,  liVecProperties );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evaluePositionList, 4,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly not evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	liFibElementsToEvalue.clear();
	cout<<"fibMatrix1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly not evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibMatrix when return value is false"<<endl;

	uiPointsToEvalue = 1;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	cout<<"fibMatrix1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. with result false "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 0;
	cout<<"fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. with result false "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibMatrix with differnt elements to evalue"<<endl;

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"liCFibElementTyps.push_back( 'y' );"<<endl;
	liCFibElementTyps.push_back( 'y' );
	liVecProperties.clear();
	liFibElementsToEvalue.clear();
	uiPointsToEvalue = 11;
	for ( unsigned int uiEvaluesElement = 0;
			uiEvaluesElement < uiPointsToEvalue; uiEvaluesElement++ ){
		liFibElementsToEvalue.push_back(
			make_pair( &property1, list<cVectorProperty>() ) );
	}
	cout<<"fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evalueFibElementList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	cout<<"liCFibElementTyps.push_back( 'm' );"<<endl;
	liCFibElementTyps.push_back( 'm' );
	uiPointsToEvalue = 1;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &fibMatrix1, list<cVectorProperty>() ) );
	cout<<"fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	cout<<"liCFibElementTyps.push_back( 'r' );"<<endl;
	liCFibElementTyps.push_back( 'r' );
	cout<<"liCFibElementTyps.push_back( 'v' );"<<endl;
	liCFibElementTyps.push_back( 'v' );
	cout<<"liCFibElementTyps.push_back( 'm' );"<<endl;
	liCFibElementTyps.push_back( 'm' );
	uiPointsToEvalue = 1;
	cout<<"fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibMatrix1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibMatrix with two dimensions and tree vector elements"<<endl;

	cout<<"cVectorPosition vecPositionE5( 5 );"<<endl;
	cVectorPosition vecPositionE5( 5 );

	cout<<"cPoint pointE5( &vecPositionE5 );"<<endl;
	cPoint pointE5( &vecPositionE5 );
	
	cout<<"cProperty propertyRGB( vecPropertyColorRGB, &pointE5 );"<<endl;
	cProperty propertyRGB( vecPropertyColorRGB, &pointE5 );
	
	cout<<"cProperty propertyRGB_RGB( vecPropertyColorRGB, &propertyRGB );"<<endl;
	cProperty propertyRGB_RGB( vecPropertyColorRGB, &propertyRGB );

	cout<<"cFibMatrix fibMatrixDef3( 2, 3, &propertyRGB_RGB );"<<endl;
	cFibMatrix fibMatrixDef3( 2, 3, &propertyRGB_RGB );

	cout<<"fibMatrixDef3.getArea( 1 )->setLowerBoundValue( 3 );"<<endl;
	fibMatrixDef3.getArea( 1 )->setLowerBoundValue( 3 );
	cout<<"fibMatrixDef3.getArea( 1 )->setUpperBoundValue( 2 );"<<endl;
	fibMatrixDef3.getArea( 1 )->setUpperBoundValue( 2 );
	cout<<"fibMatrixDef3.getArea( 2 )->setLowerBoundValue( 8 );"<<endl;
	fibMatrixDef3.getArea( 2 )->setLowerBoundValue( 8 );
	cout<<"fibMatrixDef3.getArea( 2 )->setUpperBoundValue( 6 );"<<endl;
	fibMatrixDef3.getArea( 2 )->setUpperBoundValue( 6 );
	
	
	cout<<"pointE5.getPosition()->setVariable( 1, fibMatrixDef3.getDefinedVariable( 1 ) );"<<endl;
	pointE5.getPosition()->setVariable( 1, fibMatrixDef3.getDefinedVariable( 1 ) );
	cout<<"pointE5.getPosition()->setVariable( 2, fibMatrixDef3.getDefinedVariable( 2 ) );"<<endl;
	pointE5.getPosition()->setVariable( 2, fibMatrixDef3.getDefinedVariable( 2 ) );
	cout<<"pointE5.getPosition()->setVariable( 3, fibMatrixDef3.getDefinedVariable( 3 ) );"<<endl;
	pointE5.getPosition()->setVariable( 3, fibMatrixDef3.getDefinedVariable( 3 ) );
	cout<<"pointE5.getPosition()->setVariable( 4, fibMatrixDef3.getDefinedVariable( 4 ) );"<<endl;
	pointE5.getPosition()->setVariable( 4, fibMatrixDef3.getDefinedVariable( 4 ) );
	cout<<"pointE5.getPosition()->setVariable( 5, fibMatrixDef3.getDefinedVariable( 5 ) );"<<endl;
	pointE5.getPosition()->setVariable( 5, fibMatrixDef3.getDefinedVariable( 5 ) );

	cout<<"propertyRGB.getProperty()->setVariable( 1, fibMatrixDef3.getDefinedVariable( 3 ) );"<<endl;
	propertyRGB.getProperty()->setVariable( 1, fibMatrixDef3.getDefinedVariable( 3 ) );
	cout<<"propertyRGB.getProperty()->setVariable( 2, fibMatrixDef3.getDefinedVariable( 2 ) );"<<endl;
	propertyRGB.getProperty()->setVariable( 2, fibMatrixDef3.getDefinedVariable( 2 ) );
	cout<<"propertyRGB.getProperty()->setVariable( 3, fibMatrixDef3.getDefinedVariable( 1 ) );"<<endl;
	propertyRGB.getProperty()->setVariable( 3, fibMatrixDef3.getDefinedVariable( 1 ) );

	cout<<"propertyRGB_RGB.getProperty()->setVariable( 1, fibMatrixDef3.getDefinedVariable( 3 ) );"<<endl;
	propertyRGB_RGB.getProperty()->setVariable( 1, fibMatrixDef3.getDefinedVariable( 3 ) );
	cout<<"propertyRGB_RGB.getProperty()->setVariable( 2, fibMatrixDef3.getDefinedVariable( 4 ) );"<<endl;
	propertyRGB_RGB.getProperty()->setVariable( 2, fibMatrixDef3.getDefinedVariable( 4 ) );
	cout<<"propertyRGB_RGB.getProperty()->setVariable( 3, fibMatrixDef3.getDefinedVariable( 5 ) );"<<endl;
	propertyRGB_RGB.getProperty()->setVariable( 3, fibMatrixDef3.getDefinedVariable( 5 ) );
	
	cout<<"cVectorFibMatrix vecFibMatrixE3( fibMatrixDef3 );={1,2,3}"<<endl;
	cVectorFibMatrix vecFibMatrixE3( fibMatrixDef3 );
	vecFibMatrixE3.setValue( 1, 1 );
	vecFibMatrixE3.setValue( 2, 2 );
	vecFibMatrixE3.setValue( 3, 3 );
	cout<<"fibMatrixDef3.addVector( vecFibMatrixE3 );"<<endl;
	fibMatrixDef3.addVector( vecFibMatrixE3 );

	vecFibMatrixE3.setValue( 1, 1 );
	vecFibMatrixE3.setValue( 2, 2 );
	vecFibMatrixE3.setValue( 3, 3 );
	cout<<"fibMatrixDef3.addVector( vecFibMatrixE3={1, 2, 3 };"<<endl;
	fibMatrixDef3.addVector( vecFibMatrixE3 );

	vecFibMatrixE3.setValue( 1, 3 );
	vecFibMatrixE3.setValue( 2, 2 );
	vecFibMatrixE3.setValue( 3, 1 );
	cout<<"fibMatrixDef3.addVector( vecFibMatrixE3={3, 2, 1 };"<<endl;
	fibMatrixDef3.addVector( vecFibMatrixE3 );

	vecFibMatrixE3.setValue( 1, -12 );
	vecFibMatrixE3.setValue( 2, -1.1 );
	vecFibMatrixE3.setValue( 3, -6.7 );
	cout<<"fibMatrixDef3.addVector( vecFibMatrixE3={-12, -1.1, -6.7 };"<<endl;
	fibMatrixDef3.addVector( vecFibMatrixE3 );

	vecFibMatrixE3.setValue( 1, 3.3 );
	vecFibMatrixE3.setValue( 2, 3.3 );
	vecFibMatrixE3.setValue( 3, 3.3 );
	cout<<"fibMatrixDef3.addVector( vecFibMatrixE3={3.3, 3.3, 3.3 };"<<endl;
	fibMatrixDef3.addVector( vecFibMatrixE3 );

	uiPointsToEvalue = 5;
	
	uiTimeNeeded = uiPointsToEvalue * ( 5 + (4 + 4 + 6) );

	//check the getTimeNeed() methode from cList
	cout<<"fibMatrixDef3.getTimeNeed()"<<endl;
	if ( fibMatrixDef3.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibMatrixDef3.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cList
	cout<<"fibMatrixDef3.getTimeNeed( 4 )"<<endl;
	if ( fibMatrixDef3.getTimeNeed( 4 ) == 4 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 4 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibMatrixDef3.getTimeNeed( 4 ) <<", but should be "<< 4 <<" . "<<endl;
		iReturn++;
	}

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	
	//generate to evalue data
	liPointsToEvalue.clear();
	cVectorPosition vecPosition2E5( 5 );
	vecPosition2E5.setValue( 1, 3 );
	vecPosition2E5.setValue( 2, 8 );
	vecPosition2E5.setValue( 3, 1 );
	vecPosition2E5.setValue( 4, 2 );
	vecPosition2E5.setValue( 5, 3 );
	liPointsToEvalue.push_back( make_pair( &vecPosition2E5, list<cVectorProperty>() ) );
	cVectorProperty vecPropertyColor2RGB( cTypeProperty::COLOR_RGB );
	vecPropertyColor2RGB.setValue( 1, 1 );
	vecPropertyColor2RGB.setValue( 2, 2 );
	vecPropertyColor2RGB.setValue( 3, 3 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	vecPropertyColor2RGB.setValue( 1, 1 );
	vecPropertyColor2RGB.setValue( 2, 8 );
	vecPropertyColor2RGB.setValue( 3, 3 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	cVectorPosition vecPosition3E5( 5 );
	vecPosition3E5.setValue( 1, 2 );
	vecPosition3E5.setValue( 2, 8 );
	vecPosition3E5.setValue( 3, 1 );
	vecPosition3E5.setValue( 4, 2 );
	vecPosition3E5.setValue( 5, 3 );
	liPointsToEvalue.push_back( make_pair( &vecPosition3E5, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 1 );
	vecPropertyColor2RGB.setValue( 2, 2 );
	vecPropertyColor2RGB.setValue( 3, 3 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	vecPropertyColor2RGB.setValue( 1, 1 );
	vecPropertyColor2RGB.setValue( 2, 8 );
	vecPropertyColor2RGB.setValue( 3, 2 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	cVectorPosition vecPosition4E5( 5 );
	vecPosition4E5.setValue( 1, 3 );
	vecPosition4E5.setValue( 2, 7 );
	vecPosition4E5.setValue( 3, 3 );
	vecPosition4E5.setValue( 4, 2 );
	vecPosition4E5.setValue( 5, 1 );
	liPointsToEvalue.push_back( make_pair( &vecPosition4E5, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 3 );
	vecPropertyColor2RGB.setValue( 2, 2 );
	vecPropertyColor2RGB.setValue( 3, 1 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	vecPropertyColor2RGB.setValue( 1, 3 );
	vecPropertyColor2RGB.setValue( 2, 7 );
	vecPropertyColor2RGB.setValue( 3, 3 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	cVectorPosition vecPosition5E5( 5 );
	vecPosition5E5.setValue( 1, 2 );
	vecPosition5E5.setValue( 2, 7 );
	vecPosition5E5.setValue( 3, -12 );
	vecPosition5E5.setValue( 4, -1.1 );
	vecPosition5E5.setValue( 5, -6.7 );
	liPointsToEvalue.push_back( make_pair( &vecPosition5E5, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, -12 );
	vecPropertyColor2RGB.setValue( 2, -1.1 );
	vecPropertyColor2RGB.setValue( 3, -6.7 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	vecPropertyColor2RGB.setValue( 1, -12 );
	vecPropertyColor2RGB.setValue( 2, 7 );
	vecPropertyColor2RGB.setValue( 3, 2 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	cVectorPosition vecPosition6E5( 5 );
	vecPosition6E5.setValue( 1, 3 );
	vecPosition6E5.setValue( 2, 6 );
	vecPosition6E5.setValue( 3, 3.3 );
	vecPosition6E5.setValue( 4, 3.3 );
	vecPosition6E5.setValue( 5, 3.3 );
	liPointsToEvalue.push_back( make_pair( &vecPosition6E5, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 3.3 );
	vecPropertyColor2RGB.setValue( 2, 3.3 );
	vecPropertyColor2RGB.setValue( 3, 3.3 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	vecPropertyColor2RGB.setValue( 1, 3.3 );
	vecPropertyColor2RGB.setValue( 2, 6 );
	vecPropertyColor2RGB.setValue( 3, 3 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"fibMatrixDef3.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = fibMatrixDef3.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );
	
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrixDef3.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = fibMatrixDef3.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );


	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &pointE5, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 1 );
	vecPropertyColor2RGB.setValue( 2, 2 );
	vecPropertyColor2RGB.setValue( 3, 3 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	vecPropertyColor2RGB.setValue( 1, 1 );
	vecPropertyColor2RGB.setValue( 2, 8 );
	vecPropertyColor2RGB.setValue( 3, 3 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	liFibElementsToEvalue.push_back( make_pair( &pointE5, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 1 );
	vecPropertyColor2RGB.setValue( 2, 2 );
	vecPropertyColor2RGB.setValue( 3, 3 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	vecPropertyColor2RGB.setValue( 1, 1 );
	vecPropertyColor2RGB.setValue( 2, 8 );
	vecPropertyColor2RGB.setValue( 3, 2 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	liFibElementsToEvalue.push_back( make_pair( &pointE5, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 3 );
	vecPropertyColor2RGB.setValue( 2, 2 );
	vecPropertyColor2RGB.setValue( 3, 1 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	vecPropertyColor2RGB.setValue( 1, 3 );
	vecPropertyColor2RGB.setValue( 2, 7 );
	vecPropertyColor2RGB.setValue( 3, 3 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	liFibElementsToEvalue.push_back( make_pair( &pointE5, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, -12 );
	vecPropertyColor2RGB.setValue( 2, -1.1 );
	vecPropertyColor2RGB.setValue( 3, -6.7 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	vecPropertyColor2RGB.setValue( 1, -12 );
	vecPropertyColor2RGB.setValue( 2, 7 );
	vecPropertyColor2RGB.setValue( 3, 2 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	liFibElementsToEvalue.push_back( make_pair( &pointE5, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 3.3 );
	vecPropertyColor2RGB.setValue( 2, 3.3 );
	vecPropertyColor2RGB.setValue( 3, 3.3 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	vecPropertyColor2RGB.setValue( 1, 3.3 );
	vecPropertyColor2RGB.setValue( 2, 6 );
	vecPropertyColor2RGB.setValue( 3, 3 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	cout<<"fibMatrixDef3.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibMatrixDef3.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrixDef3.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = fibMatrixDef3.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibMatrix with tree dimensions and no vectors to set"<<endl;

	cout<<"cVectorPosition vecPositionE3( 3 );"<<endl;
	cVectorPosition vecPositionE3( 3 );

	cout<<"cPoint pointE3( &vecPositionE3 );"<<endl;
	cPoint pointE3( &vecPositionE3 );
	
	cout<<"cProperty propertyRGB_PE3( vecPropertyColorRGB, &pointE3 );"<<endl;
	cProperty propertyRGB_PE3( vecPropertyColorRGB, &pointE3 );
	
	cout<<"cFibMatrix fibMatrixDim3Vec0( 3, 4, &propertyRGB_PE3 );"<<endl;
	cFibMatrix fibMatrixDim3Vec0( 3, 4, &propertyRGB_PE3 );

	cout<<"fibMatrixDim3Vec0.getArea( 1 )->setLowerBoundValue( 7 );"<<endl;
	fibMatrixDim3Vec0.getArea( 1 )->setLowerBoundValue( 7 );
	cout<<"fibMatrixDim3Vec0.getArea( 1 )->setUpperBoundValue( 8 );"<<endl;
	fibMatrixDim3Vec0.getArea( 1 )->setUpperBoundValue( 8 );
	cout<<"fibMatrixDim3Vec0.getArea( 2 )->setLowerBoundValue( 5 );"<<endl;
	fibMatrixDim3Vec0.getArea( 2 )->setLowerBoundValue( 5 );
	cout<<"fibMatrixDim3Vec0.getArea( 2 )->setUpperBoundValue( 3 );"<<endl;
	fibMatrixDim3Vec0.getArea( 2 )->setUpperBoundValue( 3 );
	cout<<"fibMatrixDim3Vec0.getArea( 3 )->setLowerBoundValue( -2 );"<<endl;
	fibMatrixDim3Vec0.getArea( 3 )->setLowerBoundValue( -2 );
	cout<<"fibMatrixDim3Vec0.getArea( 3 )->setUpperBoundValue( -1 );"<<endl;
	fibMatrixDim3Vec0.getArea( 3 )->setUpperBoundValue( -1 );
	
	
	cout<<"pointE3.getPosition()->setVariable( 1, fibMatrixDim3Vec0.getDefinedVariable( 1 ) );"<<endl;
	pointE3.getPosition()->setVariable( 1, fibMatrixDim3Vec0.getDefinedVariable( 1 ) );
	cout<<"pointE3.getPosition()->setVariable( 2, fibMatrixDim3Vec0.getDefinedVariable( 2 ) );"<<endl;
	pointE3.getPosition()->setVariable( 2, fibMatrixDim3Vec0.getDefinedVariable( 2 ) );
	cout<<"pointE3.getPosition()->setVariable( 3, fibMatrixDim3Vec0.getDefinedVariable( 3 ) );"<<endl;
	pointE3.getPosition()->setVariable( 3, fibMatrixDim3Vec0.getDefinedVariable( 3 ) );

	cout<<"propertyRGB_PE3.getProperty()->setVariable( 1, fibMatrixDim3Vec0.getDefinedVariable( 1 ) );"<<endl;
	propertyRGB_PE3.getProperty()->setVariable( 1, fibMatrixDim3Vec0.getDefinedVariable( 1 ) );
	cout<<"propertyRGB_PE3.getProperty()->setVariable( 2, fibMatrixDim3Vec0.getDefinedVariable( 2 ) );"<<endl;
	propertyRGB_PE3.getProperty()->setVariable( 2, fibMatrixDim3Vec0.getDefinedVariable( 2 ) );
	cout<<"propertyRGB_PE3.getProperty()->setVariable( 3, fibMatrixDim3Vec0.getDefinedVariable( 3 ) );"<<endl;
	propertyRGB_PE3.getProperty()->setVariable( 3, fibMatrixDim3Vec0.getDefinedVariable( 3 ) );
	
	uiPointsToEvalue = 12;
	
	uiTimeNeeded = uiPointsToEvalue * ( 3 + (4 + 4) );

	//check the getTimeNeed() methode from cList
	cout<<"fibMatrixDim3Vec0.getTimeNeed()"<<endl;
	if ( fibMatrixDim3Vec0.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibMatrixDim3Vec0.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cList
	cout<<"fibMatrixDim3Vec0.getTimeNeed( 4 )"<<endl;
	if ( fibMatrixDim3Vec0.getTimeNeed( 4 ) == 4 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 4 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibMatrixDim3Vec0.getTimeNeed( 4 ) <<", but should be "<< 4 <<" . "<<endl;
		iReturn++;
	}

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	
	//generate to evalue data
	liPointsToEvalue.clear();
	cVectorPosition vecPosition2E3( 3 );
	vecPosition2E3.setValue( 1, 7 );
	vecPosition2E3.setValue( 2, 5 );
	vecPosition2E3.setValue( 3, -2 );
	liPointsToEvalue.push_back( make_pair( &vecPosition2E3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 7 );
	vecPropertyColor2RGB.setValue( 2, 5 );
	vecPropertyColor2RGB.setValue( 3, -2 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	cVectorPosition vecPosition3E3( 3 );
	vecPosition3E3.setValue( 1, 8 );
	vecPosition3E3.setValue( 2, 5 );
	vecPosition3E3.setValue( 3, -2 );
	liPointsToEvalue.push_back( make_pair( &vecPosition3E3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 8 );
	vecPropertyColor2RGB.setValue( 2, 5 );
	vecPropertyColor2RGB.setValue( 3, -2 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	cVectorPosition vecPosition4E3( 3 );
	vecPosition4E3.setValue( 1, 7 );
	vecPosition4E3.setValue( 2, 4 );
	vecPosition4E3.setValue( 3, -2 );
	liPointsToEvalue.push_back( make_pair( &vecPosition4E3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 7 );
	vecPropertyColor2RGB.setValue( 2, 4 );
	vecPropertyColor2RGB.setValue( 3, -2 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	cVectorPosition vecPosition5E3( 3 );
	vecPosition5E3.setValue( 1, 8 );
	vecPosition5E3.setValue( 2, 4 );
	vecPosition5E3.setValue( 3, -2 );
	liPointsToEvalue.push_back( make_pair( &vecPosition5E3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 8 );
	vecPropertyColor2RGB.setValue( 2, 4 );
	vecPropertyColor2RGB.setValue( 3, -2 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	cVectorPosition vecPosition6E3( 3 );
	vecPosition6E3.setValue( 1, 7 );
	vecPosition6E3.setValue( 2, 3 );
	vecPosition6E3.setValue( 3, -2 );
	liPointsToEvalue.push_back( make_pair( &vecPosition6E3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 7 );
	vecPropertyColor2RGB.setValue( 2, 3 );
	vecPropertyColor2RGB.setValue( 3, -2 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	cVectorPosition vecPosition7E3( 3 );
	vecPosition7E3.setValue( 1, 8 );
	vecPosition7E3.setValue( 2, 3 );
	vecPosition7E3.setValue( 3, -2 );
	liPointsToEvalue.push_back( make_pair( &vecPosition7E3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 8 );
	vecPropertyColor2RGB.setValue( 2, 3 );
	vecPropertyColor2RGB.setValue( 3, -2 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	
	cVectorPosition vecPosition12E3( 3 );
	vecPosition12E3.setValue( 1, 7 );
	vecPosition12E3.setValue( 2, 5 );
	vecPosition12E3.setValue( 3, -1 );
	liPointsToEvalue.push_back( make_pair( &vecPosition12E3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 7 );
	vecPropertyColor2RGB.setValue( 2, 5 );
	vecPropertyColor2RGB.setValue( 3, -1 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	cVectorPosition vecPosition13E3( 3 );
	vecPosition13E3.setValue( 1, 8 );
	vecPosition13E3.setValue( 2, 5 );
	vecPosition13E3.setValue( 3, -1 );
	liPointsToEvalue.push_back( make_pair( &vecPosition13E3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 8 );
	vecPropertyColor2RGB.setValue( 2, 5 );
	vecPropertyColor2RGB.setValue( 3, -1 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	cVectorPosition vecPosition14E3( 3 );
	vecPosition14E3.setValue( 1, 7 );
	vecPosition14E3.setValue( 2, 4 );
	vecPosition14E3.setValue( 3, -1 );
	liPointsToEvalue.push_back( make_pair( &vecPosition14E3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 7 );
	vecPropertyColor2RGB.setValue( 2, 4 );
	vecPropertyColor2RGB.setValue( 3, -1 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	cVectorPosition vecPosition15E3( 3 );
	vecPosition15E3.setValue( 1, 8 );
	vecPosition15E3.setValue( 2, 4 );
	vecPosition15E3.setValue( 3, -1 );
	liPointsToEvalue.push_back( make_pair( &vecPosition15E3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 8 );
	vecPropertyColor2RGB.setValue( 2, 4 );
	vecPropertyColor2RGB.setValue( 3, -1 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	cVectorPosition vecPosition16E3( 3 );
	vecPosition16E3.setValue( 1, 7 );
	vecPosition16E3.setValue( 2, 3 );
	vecPosition16E3.setValue( 3, -1 );
	liPointsToEvalue.push_back( make_pair( &vecPosition16E3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 7 );
	vecPropertyColor2RGB.setValue( 2, 3 );
	vecPropertyColor2RGB.setValue( 3, -1 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	cVectorPosition vecPosition17E3( 3 );
	vecPosition17E3.setValue( 1, 8 );
	vecPosition17E3.setValue( 2, 3 );
	vecPosition17E3.setValue( 3, -1 );
	liPointsToEvalue.push_back( make_pair( &vecPosition17E3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 8 );
	vecPropertyColor2RGB.setValue( 2, 3 );
	vecPropertyColor2RGB.setValue( 3, -1 );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"fibMatrixDim3Vec0.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = fibMatrixDim3Vec0.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );
	

	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrixDim3Vec0.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = fibMatrixDim3Vec0.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );


	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 7 );
	vecPropertyColor2RGB.setValue( 2, 5 );
	vecPropertyColor2RGB.setValue( 3, -2 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 8 );
	vecPropertyColor2RGB.setValue( 2, 5 );
	vecPropertyColor2RGB.setValue( 3, -2 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 7 );
	vecPropertyColor2RGB.setValue( 2, 4 );
	vecPropertyColor2RGB.setValue( 3, -2 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 8 );
	vecPropertyColor2RGB.setValue( 2, 4 );
	vecPropertyColor2RGB.setValue( 3, -2 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 7 );
	vecPropertyColor2RGB.setValue( 2, 3 );
	vecPropertyColor2RGB.setValue( 3, -2 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 8 );
	vecPropertyColor2RGB.setValue( 2, 3 );
	vecPropertyColor2RGB.setValue( 3, -2 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	
	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 7 );
	vecPropertyColor2RGB.setValue( 2, 5 );
	vecPropertyColor2RGB.setValue( 3, -1 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 8 );
	vecPropertyColor2RGB.setValue( 2, 5 );
	vecPropertyColor2RGB.setValue( 3, -1 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 7 );
	vecPropertyColor2RGB.setValue( 2, 4 );
	vecPropertyColor2RGB.setValue( 3, -1 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 8 );
	vecPropertyColor2RGB.setValue( 2, 4 );
	vecPropertyColor2RGB.setValue( 3, -1 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 7 );
	vecPropertyColor2RGB.setValue( 2, 3 );
	vecPropertyColor2RGB.setValue( 3, -1 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	vecPropertyColor2RGB.setValue( 1, 8 );
	vecPropertyColor2RGB.setValue( 2, 3 );
	vecPropertyColor2RGB.setValue( 3, -1 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	
	cout<<"fibMatrixDim3Vec0.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibMatrixDim3Vec0.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibMatrixDim3Vec0.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = fibMatrixDim3Vec0.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The fibMatrix was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	return iReturn;
}



/**
 * This method tests the equal() method of two given Fib objects which are
 * equal.
 *
 * @param fibObject1 the first Fib object to compare
 * @param szNameObject1 the name of the first Fib object to compare
 * @param fibObject2 the secound Fib object to compare to
 * @param szNameObject2 the name of the secound Fib object to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualObjects( const cFibElement &fibObject1, const string &szNameObject1,
	const cFibElement &fibObject2, const string &szNameObject2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( fibObject1.equal( fibObject2 ) ){
	
		cout<<"The "<<szNameObject1<<" is equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is not equal to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}
/* no operator== for cFibElement
	if ( fibObject1 == fibObject2 ){
	
		cout<<"The "<<szNameObject1<<" is equal (operator==) to "<<
			szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is not equal (operator==) to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}
*/
	if ( fibObject1.equalElement( fibObject2 ) ){
	
		cout<<"The "<<szNameObject1<<" Fib element is equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" Fib element is not equal to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}

	return iReturn;
}

/**
 * This method tests the equal() method of two given Fib objects which are
 * not equal.
 *
 * @param fibObject1 the first Fib object to compare
 * @param szNameObject1 the name of the first Fib object to compare
 * @param fibObject2 the secound Fib object to compare to
 * @param szNameObject2 the name of the secound Fib object to compare
 * @param bEqualElement if true the highest Fib elements of the
 * 	Fib objects are equal, else ther are not equal
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualObjects( const cFibElement &fibObject1, const string &szNameObject1,
	const cFibElement &fibObject2, const string &szNameObject2, bool bEqualElement=false ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! fibObject1.equal( fibObject2 ) ){
	
		cout<<"The "<<szNameObject1<<" is not equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is equal to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}
/* no operator== for cFibElement
	if ( ! (fibObject1==fibObject2) ){
	
		cout<<"The "<<szNameObject1<<" is not equal (operator==) to "<<
			szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is equal (operator==) to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}
*/
	if ( fibObject1.equalElement( fibObject2 ) == bEqualElement ){
	
		cout<<"The "<<szNameObject1<<" Fib element is "<<
			(bEqualElement?"":"not ") <<"equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" Fib element is "<<
			(bEqualElement?"not ":"") <<"equal to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests equal method of the cRoot class.
 *
 * methods tested:
 * 	- bool equal( const cFibElement & fibObject ) const
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testEqual( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing equal methods for matrix elements"<<endl;

	cout<<endl<<"Creating fibMatrixobjects objects to compare: "<<endl<<endl;

	//fibMatrix with a empty fibMatrixvector
	cout<<"cFibMatrix fibMatrix1V1( 1, 1 );"<<endl;
	cFibMatrix fibMatrix1V1( 1, 1 );

	cout<<"cFibMatrix fibMatrix2V1( 1, 1 );"<<endl;
	cFibMatrix fibMatrix2V1( 1, 1 );

	//with differnt number of defined variables
	cout<<"cFibMatrix fibMatrixV2( 1, 2 );"<<endl;
	cFibMatrix fibMatrixV2( 1, 2 );

	cout<<"cFibMatrix fibMatrixV5( 3, 2 );"<<endl;
	cFibMatrix fibMatrixV5( 3, 2 );
	
	//fibMatrix with one changed area vector
	cout<<"cFibMatrix fibMatrixVDVA1C( 3, 2 );"<<endl;
	cFibMatrix fibMatrixVDVA1C( 3, 2 );
	cout<<"fibMatrixVDVA1C.getArea( 1 )->setValue( 2, 4 );"<<endl;
	fibMatrixVDVA1C.getArea( 1 )->setValue( 2, 4 );

	cout<<"cFibMatrix fibMatrixVDVA2C( 3, 2 );"<<endl;
	cFibMatrix fibMatrixVDVA2C( 3, 2 );
	cout<<"fibMatrixVDVA2C.getArea( 2 )->setValue( 2, 4 );"<<endl;
	fibMatrixVDVA2C.getArea( 2 )->setValue( 2, 4 );

	cout<<"cFibMatrix fibMatrixVDVA3C( 3, 2 );"<<endl;
	cFibMatrix fibMatrixVDVA3C( 3, 2 );
	cout<<"fibMatrixVDVA3C.getArea( 3 )->setValue( 2, 4 );"<<endl;
	fibMatrixVDVA3C.getArea( 3 )->setValue( 2, 4 );
	
	//fibMatrix with one changed vector with values to set
	cout<<"cFibMatrix fibMatrixV1g4( 1, 2 );"<<endl;
	cFibMatrix fibMatrixV1g4( 1, 2 );
	cout<<"cVectorFibMatrix vecFibMatrixV1g4;"<<endl;
	cVectorFibMatrix vecFibMatrixV1g4;
	cout<<"vecFibMatrixV1g4.setValue( 1, 4);"<<endl;
	vecFibMatrixV1g4.setValue( 1, 4);
	cout<<"fibMatrixV1g4.addVector( vecFibMatrixV1g4 );"<<endl;
	fibMatrixV1g4.addVector( vecFibMatrixV1g4 );
	
	cout<<"cFibMatrix fibMatrixV2g4( 1, 2 );"<<endl;
	cFibMatrix fibMatrixV2g4( 1, 2 );
	cout<<"cVectorFibMatrix vecFibMatrixV2g4;"<<endl;
	cVectorFibMatrix vecFibMatrixV2g4;
	cout<<"vecFibMatrixV2g4.setValue( 2, 4);"<<endl;
	vecFibMatrixV2g4.setValue( 2, 4);
	cout<<"fibMatrixV2g4.addVector( vecFibMatrixV2g4 );"<<endl;
	fibMatrixV2g4.addVector( vecFibMatrixV2g4 );
	
	//with differnt domain number
	cout<<"cFibMatrix fibMatrixV1Dom1( 1, 1 );"<<endl;
	cFibMatrix fibMatrixV1Dom1( 1, 1 );
	cout<<"fibMatrixV1Dom1.setDomainNr( 1 );"<<endl;
	fibMatrixV1Dom1.setDomainNr( 1 );
	
	cout<<"cFibMatrix fibMatrixV1Dom3( 1, 1 );"<<endl;
	cFibMatrix fibMatrixV1Dom3( 1, 1 );
	cout<<"fibMatrixV1Dom3.setDomainNr( 3 );"<<endl;
	fibMatrixV1Dom3.setDomainNr( 3 );
	
	//fibMatrix with two vector with values to sets
	cout<<"cFibMatrix fibMatrixE2E1V1g4E2V2g4( 1, 2 );"<<endl;
	cFibMatrix fibMatrixE2E1V1g4E2V2g4( 1, 2 );
	cout<<"fibMatrixE2E1V1g4E2V2g4.addVector( vecFibMatrixV1g4 );"<<endl;
	fibMatrixE2E1V1g4E2V2g4.addVector( vecFibMatrixV1g4 );
	cout<<"fibMatrixE2E1V1g4E2V2g4.addVector( vecFibMatrixV2g4 );"<<endl;
	fibMatrixE2E1V1g4E2V2g4.addVector( vecFibMatrixV2g4 );
	
	cout<<"cFibMatrix fibMatrixE2E1V2g4E2V1g4( 1, 2 );"<<endl;
	cFibMatrix fibMatrixE2E1V2g4E2V1g4( 1, 2 );
	cout<<"fibMatrixE2E1V2g4E2V1g4.addVector( vecFibMatrixV2g4 );"<<endl;
	fibMatrixE2E1V2g4E2V1g4.addVector( vecFibMatrixV2g4 );
	cout<<"fibMatrixE2E1V2g4E2V1g4.addVector( vecFibMatrixV1g4 );"<<endl;
	fibMatrixE2E1V2g4E2V1g4.addVector( vecFibMatrixV1g4 );

	//fibMatrix with tree vectors with values to sets
	cout<<"cFibMatrix fibMatrix1E1V1g4E2V2g4E3V2g4( 1, 2 );"<<endl;
	cFibMatrix fibMatrix1E1V1g4E2V2g4E3V2g4( 1, 2 );
	cout<<"fibMatrix1E1V1g4E2V2g4E3V2g4.addVector( vecFibMatrixV2g4 );"<<endl;
	fibMatrix1E1V1g4E2V2g4E3V2g4.addVector( vecFibMatrixV2g4 );
	cout<<"fibMatrix1E1V1g4E2V2g4E3V2g4.addVector( vecFibMatrixV2g4 );"<<endl;
	fibMatrix1E1V1g4E2V2g4E3V2g4.addVector( vecFibMatrixV2g4 );
	cout<<"fibMatrix1E1V1g4E2V2g4E3V2g4.addVector( vecFibMatrixV2g4 );"<<endl;
	fibMatrix1E1V1g4E2V2g4E3V2g4.addVector( vecFibMatrixV2g4 );
	
	
	//fibMatrix with supperior element
	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	
	cout<<"cFibMatrix fibMatrixSup( 1, 1, NULL, &rootEmpty1 );"<<endl;
	cFibMatrix fibMatrixSup( 1, 1, NULL, &rootEmpty1 );

	//fibMatrix in Fib element structur
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;
	cout<<"cFibMatrix fibMatrixNextPrev( 1, 1, &poinNext );"<<endl;
	cFibMatrix fibMatrixNextPrev( 1, 1, &poinNext );


	cout<<"cPoint poinNext2;"<<endl;
	cPoint poinNext2;
	cout<<"cRoot root1;"<<flush<<endl;
	cRoot root1;
	
	cout<<"cTypeFibMatrix testTypeFibMatrix;"<<endl;
	cTypeFibMatrix testTypeFibMatrix;
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2( 2 );
	cout<<"vecDomainsE2[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomainsE2[ 1 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE2[ 1 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomainE2( vecDomainsE2 );"<<endl;
	cDomainVector vectorDomainE2( vecDomainsE2 );
	delete vecDomainsE2[ 0 ];
	delete vecDomainsE2[ 1 ];

	cout<<"root1.getDomains()->addDomain( testTypeFibMatrix, &vectorDomainE2 );"<<endl;
	root1.getDomains()->addDomain( testTypeFibMatrix, &vectorDomainE2 );

	cout<<"cFibMatrix fibMatrixFull( 1, 1, &poinNext2, &root1 );"<<endl;
	cFibMatrix fibMatrixFull( 1, 1, &poinNext2, &root1 );

	//fibMatrixs with a contained point element
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cFibMatrix fibMatrixPoint1( 1, 1, &point1 );"<<endl;
	cFibMatrix fibMatrixPoint1( 1, 1, &point1 );

	cout<<"cVectorPosition vecPosition;"<<endl;
	cVectorPosition vecPosition;
	cout<<"cPoint point2( &vecPosition );"<<endl;
	cPoint point2( &vecPosition );
	cout<<"cFibMatrix fibMatrixPoint2( 1, 1, &point2 );"<<endl;
	cFibMatrix fibMatrixPoint2( 1, 1, &point2 );

	//other Fib element
	cout<<"cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );
	cout<<"cProperty property1( vecPropertyColorSW );"<<endl;
	cProperty property1( vecPropertyColorSW );
	
	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with fibMatrix1
	cFibElement *actualObject = &fibMatrix1V1;
	string szActualObjectName = "fibMatrix1V1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrix2V1
	actualObject = &fibMatrix2V1;
	szActualObjectName = "fibMatrix2V1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrixV2
	actualObject = &fibMatrixV2;
	szActualObjectName = "fibMatrixV2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrixV5
	actualObject = &fibMatrixV5;
	szActualObjectName = "fibMatrixV5";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrixVDVA1C
	actualObject = &fibMatrixVDVA1C;
	szActualObjectName = "fibMatrixVDVA1C";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrixVDVA2C
	actualObject = &fibMatrixVDVA2C;
	szActualObjectName = "fibMatrixVDVA2C";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrixVDVA3C
	actualObject = &fibMatrixVDVA3C;
	szActualObjectName = "fibMatrixVDVA3C";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );
	
	//compare with fibMatrixV1g4
	actualObject = &fibMatrixV1g4;
	szActualObjectName = "fibMatrixV1g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrixV2g4
	actualObject = &fibMatrixV2g4;
	szActualObjectName = "fibMatrixV2g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrixV1Dom1
	actualObject = &fibMatrixV1Dom1;
	szActualObjectName = "fibMatrixV1Dom1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrixV1Dom3
	actualObject = &fibMatrixV1Dom3;
	szActualObjectName = "fibMatrixV1Dom3";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );
	
	//compare with fibMatrixE2E1V1g4E2V2g4
	actualObject = &fibMatrixE2E1V1g4E2V2g4;
	szActualObjectName = "fibMatrixE2E1V1g4E2V2g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrixE2E1V2g4E2V1g4
	actualObject = &fibMatrixE2E1V2g4E2V1g4;
	szActualObjectName = "fibMatrixE2E1V2g4E2V1g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrix1E1V1g4E2V2g4E3V2g4
	actualObject = &fibMatrix1E1V1g4E2V2g4E3V2g4;
	szActualObjectName = "fibMatrix1E1V1g4E2V2g4E3V2g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrixSup
	actualObject = &fibMatrixSup;
	szActualObjectName = "fibMatrixSup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrixNextPrev
	actualObject = &fibMatrixNextPrev;
	szActualObjectName = "fibMatrixNextPrev";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrixFull
	actualObject = &fibMatrixFull;
	szActualObjectName = "fibMatrixFull";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrixPoint1
	actualObject = &fibMatrixPoint1;
	szActualObjectName = "fibMatrixPoint1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibMatrixPoint2
	actualObject = &fibMatrixPoint2;
	szActualObjectName = "fibMatrixPoint2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with property1
	actualObject = &property1;
	szActualObjectName = "property1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1V1, "fibMatrix1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix2V1, "fibMatrix2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2, "fibMatrixV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV5, "fibMatrixV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA1C, "fibMatrixVDVA1C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA2C, "fibMatrixVDVA2C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixVDVA3C, "fibMatrixVDVA3C" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1g4, "fibMatrixV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV2g4, "fibMatrixV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom1, "fibMatrixV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixV1Dom3, "fibMatrixV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V1g4E2V2g4, "fibMatrixE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixE2E1V2g4E2V1g4, "fibMatrixE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrix1E1V1g4E2V2g4E3V2g4, "fibMatrix1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixSup, "fibMatrixSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixNextPrev, "fibMatrixNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixFull, "fibMatrixFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint1, "fibMatrixPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibMatrixPoint2, "fibMatrixPoint2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	return iReturn;
}


/**
 * This method tests the equal() method of two given Fib objects which are
 * equal.
 * It also compares the superior, next and previous Fib element fibMatrixers.
 *
 * @param fibObject1 the first Fib object to compare
 * @param szNameObject1 the name of the first Fib object to compare
 * @param fibObject2 the secound Fib object to compare to
 * @param szNameObject2 the name of the secound Fib object to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualObjectsStructur(
		const cFibElement &fibObject1, const string &szNameObject1,
		const cFibElement &fibObject2, const string &szNameObject2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	iReturn += testCompareTwoEqualObjects( fibObject1, szNameObject1, fibObject2, szNameObject2 );
	
	//check the getNextFibElement() methode from cFibMatrix
	if ( const_cast<cFibElement*>(&fibObject1)->getNextFibElement() ==
			const_cast<cFibElement*>(&fibObject2)->getNextFibElement() ){
	
		cout<<"The next/ main Fib element pointer for the matrix element are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element pointer for the matrix element are not equal."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFibMatrix
	if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) ==
			const_cast<cFibElement*>(&fibObject2)->getFibElement( -1 ) ){
	
		cout<<"The previous Fib element pointer for the matrix element are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element pointer for the matrix element are not equal."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibMatrix
	if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() ==
			const_cast<cFibElement*>(&fibObject2)->getSuperiorFibElement() ){
	
		cout<<"The superior Fib element pointer for the matrix element are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element pointer for the matrix element are not equal."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests if the given Fib element is not conected to other
 * Fib elements.
 *
 * @param fibObject1 the Fib element to check
 * @return the number of errors occured in the test
 */
int testNotConnectedFibElement( const cFibElement &fibObject1 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	//check the getNextFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getNumberOfElements() == 1 ){
	
		cout<<"The Fib object includes just one Fib element. "<<endl;
	}else{
		cerr<<"Error: The Fib object includes just not one Fib element, but "<<
			const_cast<cFibElement*>(&fibObject1)->getNumberOfElements() <<" ."<<endl;
		iReturn++;
	}
	
	//check the getNextFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib element pointer for the point -elements is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element pointer for the point -elements is not NULL."<<endl;
		iReturn++;
	}
	//check the getFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib element pointer for the point -elements is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element pointer for the point -elements is not NULL."<<endl;
		iReturn++;
	}
	
	//check the getSuperiorFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib element pointer for the point -elements is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element pointer for the point -elements is not NULL."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the copy methods and copyconstructor of the cFibMatrix class.
 *
 * methods tested:
 * 	- cFibMatrix( const cFibMatrix &matrixElement );
 * 	- cFibElement *clone( ) const;
 * 	- cFibMatrix *copy( const unsignedIntFib iObjectFibMatrix=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementFibMatrix=0 ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a empty cFibMatrix"<<endl;
	
	cout<<"cFibMatrix fibMatrixEmpty( 0, 0 );"<<endl;
	cFibMatrix fibMatrixEmpty( 0, 0 );

	cout<<"cFibMatrix fibMatrixEmptyCopyConstruct( fibMatrixEmpty );"<<endl;
	cFibMatrix fibMatrixEmptyCopyConstruct( fibMatrixEmpty );

	iReturn += testCompareTwoEqualObjectsStructur( fibMatrixEmptyCopyConstruct, "fibMatrixEmptyCopyConstruct", fibMatrixEmpty, "fibMatrixEmpty" );

	cout<<"cFibElement * pFibMatrixEmptyClone = fibMatrixEmpty.clone();"<<endl;
	cFibElement * pFibMatrixEmptyClone = fibMatrixEmpty.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pFibMatrixEmptyClone, "pFibMatrixEmptyClone", fibMatrixEmpty, "fibMatrixEmpty" );
	delete pFibMatrixEmptyClone;

	cout<<"cFibElement * pFibMatrixEmptyCopy = fibMatrixEmpty.copy();"<<endl;
	cFibElement * pFibMatrixEmptyCopy = fibMatrixEmpty.copy();

	iReturn += testCompareTwoEqualObjectsStructur( *pFibMatrixEmptyCopy, "pFibMatrixEmptyCopy", fibMatrixEmpty, "fibMatrixEmpty" );
	delete pFibMatrixEmptyCopy;

	cout<<"cFibElement * pFibMatrixEmptyCopyElement = fibMatrixEmpty.copyElement();"<<endl;
	cFibElement * pFibMatrixEmptyCopyElement = fibMatrixEmpty.copyElement();

	iReturn += testCompareTwoEqualObjectsStructur( *pFibMatrixEmptyCopyElement, "pFibMatrixEmptyCopyElement", fibMatrixEmpty, "fibMatrixEmpty" );
	delete pFibMatrixEmptyCopyElement;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying for a other object or elementpoint"<<endl;

	cout<<"cFibElement * pFibMatrixEmptyNoCopy = fibMatrixEmpty.copy( 1 );"<<endl;
	cFibElement * pFibMatrixEmptyNoCopy = fibMatrixEmpty.copy( 1 );

	if ( pFibMatrixEmptyNoCopy == NULL ){
	
		cout<<"The cFibMatrix was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cFibMatrix was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pFibMatrixEmptyNoCopy;
	}

	cout<<"cFibElement * pFibMatrixEmptyNoCopyElement = fibMatrixEmpty.copyElement( 'm', 2 );"<<endl;
	cFibElement * pFibMatrixEmptyNoCopyElement = fibMatrixEmpty.copyElement( 'm', 2 );

	if ( pFibMatrixEmptyNoCopyElement == NULL ){
	
		cout<<"The cFibMatrix -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cFibMatrix -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pFibMatrixEmptyNoCopyElement;
	}

	cout<<"pFibMatrixEmptyNoCopyElement = fibMatrixEmpty.copyElement( 'u', 2 );"<<endl;
	pFibMatrixEmptyNoCopyElement = fibMatrixEmpty.copyElement( 'u', 2 );

	if ( pFibMatrixEmptyNoCopyElement == NULL ){
	
		cout<<"The cFibMatrix -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cFibMatrix -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pFibMatrixEmptyNoCopyElement;
	}

	cout<<"pFibMatrixEmptyNoCopyElement = fibMatrixEmpty.copyElement( 'r', 1 );"<<endl;
	pFibMatrixEmptyNoCopyElement = fibMatrixEmpty.copyElement( 'r', 1 );

	if ( pFibMatrixEmptyNoCopyElement == NULL ){
	
		cout<<"The cFibMatrix -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cFibMatrix -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pFibMatrixEmptyNoCopyElement;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFibMatrix with all members set"<<endl;

	//fibMatrix in Fib element structur
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;

	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeFibMatrix testTypeFibMatrix( 3 );"<<endl;
	cTypeFibMatrix testTypeFibMatrix( 3 );
	
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

	cout<<"vector<cDomain*> vecDomainsE4( 4 );"<<endl;
	vector<cDomain*> vecDomainsE4( 4 );
	cout<<"vecDomainsE4[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE4[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE4[ 1 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE4[ 1 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE4[ 2 ] = &vectorDomainD2;"<<endl;
	vecDomainsE4[ 2 ] = &vectorDomainD2;
	cout<<"vecDomainsE4[ 3 ] = &vectorDomainD2;"<<endl;
	vecDomainsE4[ 3 ] = &vectorDomainD2;
	cout<<"cDomainVector vectorDomainE4( vecDomainsE4 );"<<endl;
	cDomainVector vectorDomainE4( vecDomainsE4 );
	delete vecDomainsE4[ 0 ];
	delete vecDomainsE4[ 1 ];
	
	cout<<"rootD2.getDomains()->addDomain( testTypeFibMatrix, &vectorDomainE4 );"<<endl;
	rootD2.getDomains()->addDomain( testTypeFibMatrix, &vectorDomainE4 );

	cout<<"cFibMatrix fibMatrix2E2( 3, 2, &poinNext, &rootD2 );"<<endl;
	cFibMatrix fibMatrix2E2( 3, 2, &poinNext, &rootD2 );
	
	cout<<"fibMatrix2E2.getArea( 1 )->setValue( 1, 1 );"<<endl;
	fibMatrix2E2.getArea( 1 )->setValue( 1, 1 );
	cout<<"fibMatrix2E2.getArea( 1 )->setValue( 2, -1 );"<<endl;
	fibMatrix2E2.getArea( 1 )->setValue( 2, -1 );
	cout<<"fibMatrix2E2.getArea( 2 )->setValue( 1, 17 );"<<endl;
	fibMatrix2E2.getArea( 2 )->setValue( 1, 17 );
	cout<<"fibMatrix2E2.getArea( 2 )->setValue( 2, -6 );"<<endl;
	fibMatrix2E2.getArea( 2 )->setValue( 2, -6 );
	cout<<"fibMatrix2E2.getArea( 3 )->setValue( 1, 5 );"<<endl;
	fibMatrix2E2.getArea( 3 )->setValue( 1, 5 );
	cout<<"fibMatrix2E2.getArea( 3 )->setValue( 2, 6 );"<<endl;
	fibMatrix2E2.getArea( 3 )->setValue( 2, 6 );
	
	cout<<"fibMatrix2E2.setDomainNr( 3 );"<<endl;
	fibMatrix2E2.setDomainNr( 3 );

	cout<<"cVectorFibMatrix vecFibMatrix2;"<<endl;
	cVectorFibMatrix vecFibMatrix2;
	cout<<"vecFibMatrix2.setValue( 1, 1 );"<<endl;
	vecFibMatrix2.setValue( 1, 1 );
	cout<<"vecFibMatrix2.setValue( 2, 2 );"<<endl;
	vecFibMatrix2.setValue( 2, 2 );
	cout<<"fibMatrix2E2.addVector( vecFibMatrix2 );"<<endl;
	fibMatrix2E2.addVector( vecFibMatrix2 );
	cout<<"vecFibMatrix2.setValue( 1, 5 );"<<endl;
	vecFibMatrix2.setValue( 1, 5 );
	cout<<"vecFibMatrix2.setValue( 2, 3 );"<<endl;
	vecFibMatrix2.setValue( 2, 3 );
	cout<<"fibMatrix2E2.addVector( vecFibMatrix2 );"<<endl;
	fibMatrix2E2.addVector( vecFibMatrix2 );
	cout<<"vecFibMatrix2.setValue( 1, -3 );"<<endl;
	vecFibMatrix2.setValue( 1, -3 );
	cout<<"vecFibMatrix2.setValue( 2, 7 );"<<endl;
	vecFibMatrix2.setValue( 2, 7 );
	cout<<"fibMatrix2E2.addVector( vecFibMatrix2 );"<<endl;
	fibMatrix2E2.addVector( vecFibMatrix2 );

	cout<<"cFibMatrix fibMatrix2E2CopyConstruct( fibMatrix2E2 );"<<endl;
	cFibMatrix fibMatrix2E2CopyConstruct( fibMatrix2E2 );

	if ( fibMatrix2E2CopyConstruct.equalElement( fibMatrix2E2 ) ){

		cout<<"The fibMatrix2E2CopyConstruct Fib element is equal to fibMatrix2E2. "<<endl;
	}else{
		cerr<<"Error: The fibMatrix2E2CopyConstruct Fib element is not equal to fibMatrix2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( fibMatrix2E2CopyConstruct );

	cout<<"cFibElement * pFibMatrix2E2Copy = fibMatrix2E2.copy();"<<endl;
	cFibElement * pFibMatrix2E2Copy = fibMatrix2E2.copy();
	iReturn += testCompareTwoEqualObjects( *pFibMatrix2E2Copy, "pFibMatrix2E2Copy", fibMatrix2E2, "fibMatrix2E2" );
	//check the getFibElement() methode from cFibMatrix
	if ( NULL == pFibMatrix2E2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous Fib element pointer for the matrix element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element pointer for the matrix element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibMatrix
	if ( NULL == pFibMatrix2E2Copy->getSuperiorFibElement() ){
	
		cout<<"The superior Fib element pointer for the matrix element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element pointer for the matrix element is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( pFibMatrix2E2Copy );

	cout<<"cFibElement * pFibMatrix2E2CopyElement = fibMatrix2E2.copyElement( 'u', 1 );"<<endl;
	cFibElement * pFibMatrix2E2CopyElement = fibMatrix2E2.copyElement( 'u', 1 );

	if ( pFibMatrix2E2CopyElement->equalElement( fibMatrix2E2 ) ){
	
		cout<<"The pFibMatrix2E2CopyElement Fib element is equal to fibMatrix2E2. "<<endl;
	}else{
		cerr<<"Error: The pFibMatrix2E2CopyElement Fib element is not equal to fibMatrix2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pFibMatrix2E2CopyElement );
	delete pFibMatrix2E2CopyElement;

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a limb with more then one matrix element and point element"<<endl;

	//a limb with more then one matrix element and pointelement
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cFibMatrix fibMatrix3( 1, 3, &point1 );"<<endl;
	cFibMatrix fibMatrix3( 1, 3, &point1 );
	cout<<"cFibMatrix fibMatrix1Obj2( 2, 2, &fibMatrix3 );"<<endl;
	cFibMatrix fibMatrix1Obj2( 2, 2, &fibMatrix3 );


	cout<<endl<<"cFibMatrix fibMatrix1Obj2CopyConstruct( fibMatrix1Obj2 );"<<endl;
	cFibMatrix fibMatrix1Obj2CopyConstruct( fibMatrix1Obj2 );

	if ( fibMatrix1Obj2CopyConstruct.equalElement( fibMatrix1Obj2 ) ){
	
		cout<<"The fibMatrix1Obj2CopyConstruct Fib element is equal to fibMatrix1Obj2. "<<endl;
	}else{
		cerr<<"Error: The fibMatrix1Obj2CopyConstruct Fib element is not equal to fibMatrix1Obj2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( fibMatrix1Obj2CopyConstruct );

	cout<<"cFibElement * pFibMatrix1ColorSwO2LayerO1CopyConstructCopy = fibMatrix1Obj2CopyConstruct.copy();"<<endl;
	cFibElement * fibMatrix1Obj2Copy =
		fibMatrix1Obj2.copy();

	iReturn += testCompareTwoEqualObjects(
		*fibMatrix1Obj2Copy, "fibMatrix1Obj2Copy",
		fibMatrix1Obj2, "fibMatrix1Obj2" );
	//check the getFibElement() methode from cFibMatrix
	if ( NULL == fibMatrix1Obj2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous Fib element pointer for the matrix element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element pointer for the matrix element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibMatrix
	if ( fibMatrix1Obj2Copy->getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib element pointer for the matrix element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element pointer for the matrix element is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( fibMatrix1Obj2Copy );

	cout<<"cFibElement * pFibMatrix1Obj2 = fibMatrix1Obj2.copyElement();"<<endl;
	cFibElement * pFibMatrix1Obj2 = fibMatrix1Obj2.copyElement();

	if ( pFibMatrix1Obj2->equalElement( fibMatrix1Obj2 ) ){
	
		cout<<"The pFibMatrix1Obj2 Fib element is equal to fibMatrix1Obj2. "<<endl;
	}else{
		cerr<<"Error: The pFibMatrix1Obj2 Fib element is not equal to fibMatrix1Obj2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pFibMatrix1Obj2 );
	delete pFibMatrix1Obj2;

	return iReturn;
}



/**
 * This method tests a in the xml -format stored cFibVector.
 *
 * @param szFilename the name of the file wher the cFibVector is stored
 * @param uiFirstDefinedVariableValue the number / value of the first
 * 	defined variable
 * @param uiNumberOfDefinedVariables the number / count of defined variables
 * @param uiDomainNumber the number of the domain
 * @param uiNumberOfDimensions the number of area vectors in the fibMatrix
 * @param vecAreaElementType a vector with the typs of the area vector elements
 * 	(w=value; v=variable)
 * @param vecAreaValues the values of the area vector elements (the on even
 * 	indexes are the lower bounds and on add the upperbounds )
 * @param uiMatrixVectors the number of vector with values to sets in the fibMatrix
 * @param vecElementType a vector with the typs of the vector elements
 * 	(w=value; v=variable; the indexes mode
 * 	vector elements (uiFirstDefinedVariableValue - uiNumberOfDimensions)
 * 	are the indexes of the vectors elements)
 * @param vecValues the values of the vector elements (the indexes mode
 * 	vector elements (uiFirstDefinedVariableValue - uiNumberOfDimensions)
 * 	are the indexes of the vectors elements)
 * @param bHasPointSubobject if true the stored Fib matrix element has an
 * 	point element as an subobject, else it has no subobject
 * @return the number of errors occured in the test
 */
int testXmlFibMatrix( const string szFilename,
		unsigned int uiFirstDefinedVariableValue,
		unsigned int uiNumberOfDefinedVariables,
		unsigned int uiDomainNumber,
		unsigned int uiNumberOfDimensions, vector<char> vecAreaElementType,
			vector<long> vecAreaValues,
		unsigned int uiMatrixVectors, vector<char> vecElementType,
			vector<long> vecValues,
		bool bHasPointSubobject = true ){
	
	unsigned int iReturn = 0;
	
	unsigned int uiVectorElements =
		uiNumberOfDefinedVariables - uiNumberOfDimensions;
	
	cout<<endl<<"Checking stored cFibMatrix:"<<endl;
	
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
		const string szElementName = pXmlElement->Value();
		
		const string szFibMatrixElementName = "matrix";
		if ( szElementName == szFibMatrixElementName ){
			cout<<"The root element is correctly named \""<< szFibMatrixElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szFibMatrixElementName <<"\"."<<endl;
			iReturn++;
		}
		
		//read dimensions number
		const char * szNumberOfDimensions = pXmlElement->Attribute( "dimensions" );
		
		if ( szNumberOfDimensions == NULL ){
			
			cerr<<"Error: The Fib matrix element has no number of dimensions attribute, but it should be "<<
				uiDomainNumber<<" ."<<endl;
		}else{
			unsigned long uiNumberOfDimensionsStored = atol( szNumberOfDimensions );
			 if ( uiNumberOfDimensionsStored == uiNumberOfDimensions ) {
				cout<<"The number of dimensions of the Fib matrix element is correctly \""<<
					uiNumberOfDimensions <<"\". "<<endl;
			}else{
				cerr<<"Error: The number of dimensions of the Fib matrix element is \""<< uiNumberOfDimensionsStored
					<<"\", but should be \""<< uiNumberOfDimensions <<"\"."<<endl;
				iReturn++;
			}
		}

		//read optional domain number
		const char * szDefinedVariableValue = pXmlElement->Attribute( "domainNr" );
		
		if ( szDefinedVariableValue == NULL ){
			if ( uiDomainNumber == 0 ){
				cout<<"Ther is correctly no domain number (it is 0) . "<<endl;
			}else{
				cerr<<"Error: The Fib matrix element has no domain number, but it should be "<<
					uiDomainNumber<<" ."<<endl;
				iReturn++;
			}
		}else{
			unsigned long uiDomainNumberStored = atol( szDefinedVariableValue );
			 if ( uiDomainNumberStored == uiDomainNumber ) {
				cout<<"The defined variable of the Fib matrix element is correctly \""<< uiDomainNumber <<"\". "<<endl;
			}else{
				cerr<<"Error: The defined variable of the Fib matrix element is \""<< uiDomainNumberStored
					<<"\", but should be \""<< uiDomainNumber <<"\"."<<endl;
				iReturn++;
			}
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	//check subelements
	TiXmlHandle xmlHandleSubElement = TiXmlHandle( pXmlElement );
	TiXmlElement * pXmlSubElement = xmlHandleSubElement.FirstChild().Element();
	
	if ( pXmlSubElement == NULL ) {
		cerr<<"Error: No subelement handle."<<endl;
		iReturn++;
		return iReturn;
	}

	const string szDefVarElementName = pXmlSubElement->Value();
	//read / check defined variables
	if ( szDefVarElementName == "defined_variables" ){
		//read defined variables
		cout<<"The subelement is correctly named \"defined_variables\". "<<endl;

		TiXmlHandle xmlHandleDefinedVariables = TiXmlHandle( pXmlSubElement );
		TiXmlElement * pXmlDefinedVariable = xmlHandleDefinedVariables.FirstChild().Element();
		
		unsigned int uiActualDefinedVariable = 0;
		for ( ; pXmlDefinedVariable; uiActualDefinedVariable++,
				pXmlDefinedVariable = pXmlDefinedVariable->NextSiblingElement() ){
			

			const string szVariableName = pXmlDefinedVariable->Value();
			if ( szVariableName == "variable" ){
				cout<<"The subelement is correctly named \"variable\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the subelement is "<< szVariableName <<" and not \"variable\"."<<endl;
				iReturn++;
			}
			const char * szVariableIdentifier = pXmlDefinedVariable->GetText();
			
			if ( szVariableIdentifier == NULL ){
				cerr<<"Error: The "<<uiActualDefinedVariable<<" has no identifier."<<endl;
				iReturn++;
			}else if ( uiActualDefinedVariable < uiNumberOfDefinedVariables ){
				
				const unsigned int uiCorrectVariableId =
					uiFirstDefinedVariableValue + uiActualDefinedVariable;
				const unsigned int uiLoadedVariableId =
					atol( szVariableIdentifier );
				
				if ( uiCorrectVariableId == uiLoadedVariableId ){
					cout<<"The "<<uiActualDefinedVariable<<" defined variable identifier is correctly "<<
						uiCorrectVariableId<<" . "<<endl;
				}else{
					cerr<<"Error: The "<<uiActualDefinedVariable<<" defined variable identifier is "<<
						uiLoadedVariableId<<", but should be "<<uiCorrectVariableId<<" ."<<endl;
					iReturn++;
				}
		
			}else{// uiNumberOfDefinedVariables < =uiActualDefinedVariable
				cerr<<"Error: Ther is a "<<uiActualDefinedVariable<<
					"'th defined varable with the value \""<< szVariableIdentifier <<"\"."<<endl;
				iReturn++;
			}
			
		}
		if ( uiActualDefinedVariable != uiNumberOfDefinedVariables ){
			cerr<<"Error: Ther are "<<uiActualDefinedVariable<<" defined variables, but it should be "<<
				uiNumberOfDefinedVariables<<"."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The Fib matrix element has no element for the defined variables."<<endl;
		iReturn++;
		return iReturn;
	}
	
	//read vectors with values to set (element "areas")
	pXmlSubElement = pXmlSubElement->NextSiblingElement();
	
	if ( uiNumberOfDimensions == 0 ){
	
		if ( ! pXmlSubElement ){
			cout<<"The Fib matrix element contains correctly no vectors. "<<endl;
		
		}else{
			TiXmlHandle xmlHandleSubElementMatrix = TiXmlHandle( pXmlSubElement );
			TiXmlElement * pXmlSubElementMatrix = xmlHandleSubElementMatrix.FirstChild().Element();

			if ( pXmlSubElementMatrix ){
				cerr<<"Error: The Fib matrix element contains area vectors, but it shouldn't."<<endl;
				iReturn++;
			}
			const string szVectorsElementName = pXmlSubElement->Value();
			//read / check defined variables
			if ( szVectorsElementName == "areas" ){
				//skip values element
				pXmlSubElement = pXmlSubElement->NextSiblingElement();
			}
		}
	}else{//ther should be vectors
	
		const string szVectorsElementName = pXmlSubElement->Value();
		//read / check defined variables
		if ( szVectorsElementName == "areas" ){
			
			TiXmlHandle xmlHandleSubElementMatrix = TiXmlHandle( pXmlSubElement );
			TiXmlElement * pXmlSubElementMatrix = xmlHandleSubElementMatrix.FirstChild().Element();
			
			unsigned int uiLoadedSubFibArea = 0;
			for( ; pXmlSubElementMatrix; pXmlSubElementMatrix = pXmlSubElementMatrix->NextSiblingElement() ){
				uiLoadedSubFibArea++;
				
				if ( pXmlSubElementMatrix ) {
					string szElementName = pXmlSubElementMatrix->Value();
			
					if ( szElementName == "vector" ){
						cout<<"The root element is correctly named \"vector\". "<<endl;
					
					}else{
						cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"vector\"."<<endl;
						iReturn++;
					}
					const char * szVectorXmlType = pXmlSubElementMatrix->Attribute( "type" );
					
					if ( szVectorXmlType == NULL ){
						cerr<<"Error: The vector has no type."<<endl;
						iReturn++;
					}else if ( string("area") == szVectorXmlType ) {
						cout<<"The type of the vector is correctly \"area\". "<<endl;
					}else{
						cerr<<"Error: The type of the vector is \""<< szVectorXmlType
							<<"\", but should be \"area\"."<<endl;
						iReturn++;
					}
			
				}else{// pXmlElement == NULL
					cerr<<"Error: No vector handle in \""<< szFilename <<"\"."<<endl;
					iReturn++;
					return iReturn;
				}
				
				TiXmlHandle xmlHandleVectorRoot = TiXmlHandle( pXmlSubElementMatrix );
				pXmlElement = xmlHandleVectorRoot.FirstChild().Element();
				
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
					
					const unsigned int uiIndex =
						(uiLoadedSubFibArea - 1) * 2 +
						iNumberOfElement - 1;
					
					//the elementtype the actual element should have
					string szTargetElementType( "non" );
					
					if ( iNumberOfElement < 1 ){
						cerr<<"Error: Ther couldn't be a 0'th vector element."<<endl;
						iReturn++;
					}else if ( (int)2 < iNumberOfElement ){
						cerr<<"Error: Ther couldn't be a "<< iNumberOfElement <<
							"'th vector element, because a vector with values to set has yust "<<
							2 <<" elements."<<endl;
						iReturn++;
					}else{
						switch ( vecAreaElementType[ uiIndex ] ){
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
					if ( szElementName == "undefined" ){
						//no value for type "undefined" ->nothing to do
					}else if ( szElementName == "value" ){
						const char * pcValue = pXmlElement->GetText();
						cout<<"The value of the element is: "<< pcValue <<endl;
						//converting value to double
						if ( (1 <= iNumberOfElement) &&
								( iNumberOfElement <= (int)2 ) ){
							long lValue;
							int iReadValues = sscanf ( pcValue, "%ld", & lValue );
							if ( iReadValues != 0){
								if ( lValue == vecAreaValues[ uiIndex ] ){
									cout<<"The value of the element is correct."<<endl;
								}else{
									cerr<<"Error: The value of the element should be : "<<
										vecAreaValues[ uiIndex ] <<endl;
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
						if ( (1 <= iNumberOfElement) &&
								( iNumberOfElement <= (int)2 ) ){
							long lValue;
							int iReadValues = sscanf ( pcValue, "%ld", & lValue );
							if ( iReadValues != 0){
								if ( lValue == vecAreaValues[ uiIndex ] ){
									cout<<"The variablenumber of the element is correct."<<endl;
								}else{
									cerr<<"Error: The variablenumber of the element should be : "<<
										vecAreaValues[ uiIndex ] <<endl;
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
			}//end for all vectors
			if ( uiNumberOfDimensions != uiLoadedSubFibArea ){
				cerr<<"Error: "<< uiLoadedSubFibArea <<" area vector loded, but ther schould be "<<
					uiNumberOfDimensions <<" area vectors."<<endl;
				iReturn++;
			}
		}//end read vectors
		pXmlSubElement = pXmlSubElement->NextSiblingElement();
	}
	
	//read vectors with values to set (element "values")
	if ( uiMatrixVectors == 0 ){
	
		if ( ! pXmlSubElement ){
			cout<<"The Fib matrix element contains correctly no vectors. "<<endl;
		
		}else{
			TiXmlHandle xmlHandleSubElementMatrix = TiXmlHandle( pXmlSubElement );
			TiXmlElement * pXmlSubElementMatrix = xmlHandleSubElementMatrix.FirstChild().Element();

			if ( pXmlSubElementMatrix ){
				cerr<<"Error: The Fib matrix element contains vectors, but it shouldn't."<<endl;
				iReturn++;
			}
			const string szVectorsElementName = pXmlSubElement->Value();
			//read / check defined variables
			if ( szVectorsElementName == "values" ){
				//skip values element
				pXmlSubElement = pXmlSubElement->NextSiblingElement();
			}
		}
	}else{//ther should be vectors
	
		const string szVectorsElementName = pXmlSubElement->Value();
		//read / check defined variables
		if ( szVectorsElementName == "values" ){
			
			TiXmlHandle xmlHandleSubElementMatrix = TiXmlHandle( pXmlSubElement );
			TiXmlElement * pXmlSubElementMatrix = xmlHandleSubElementMatrix.FirstChild().Element();
			
			unsigned int uiLoadedSubFibVector = 0;
			for( ; pXmlSubElementMatrix; pXmlSubElementMatrix = pXmlSubElementMatrix->NextSiblingElement() ){
				uiLoadedSubFibVector++;
				
				if ( pXmlSubElementMatrix ) {
					string szElementName = pXmlSubElementMatrix->Value();
			
					if ( szElementName == "vector" ){
						cout<<"The root element is correctly named \"vector\". "<<endl;
					
					}else{
						cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"vector\"."<<endl;
						iReturn++;
					}
					const char * szVectorXmlType = pXmlSubElementMatrix->Attribute( "type" );
					
					if ( szVectorXmlType == NULL ){
						cerr<<"Error: The vector has no type."<<endl;
						iReturn++;
					}else if ( string("matrix") == szVectorXmlType ) {
						cout<<"The type of the vector is correctly \"matrix\". "<<endl;
					}else{
						cerr<<"Error: The type of the vector is \""<< szVectorXmlType
							<<"\", but should be \"matrix\"."<<endl;
						iReturn++;
					}
			
				}else{// pXmlElement == NULL
					cerr<<"Error: No vector handle in \""<< szFilename <<"\"."<<endl;
					iReturn++;
					return iReturn;
				}
				
				TiXmlHandle xmlHandleVectorRoot = TiXmlHandle( pXmlSubElementMatrix );
				pXmlElement = xmlHandleVectorRoot.FirstChild().Element();
				
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
					
					const unsigned int uiIndex =
						(uiLoadedSubFibVector - 1) * uiVectorElements +
						iNumberOfElement - 1;
					
					//the elementtype the actual element should have
					string szTargetElementType( "non" );
					
					if ( iNumberOfElement < 1 ){
						cerr<<"Error: Ther couldn't be a 0'th vector element."<<endl;
						iReturn++;
					}else if ( (int)uiVectorElements < iNumberOfElement ){
						cerr<<"Error: Ther couldn't be a "<< iNumberOfElement <<
							"'th vector element, because a vector with values to set has yust "<<
							uiVectorElements <<" elements."<<endl;
						iReturn++;
					}else{
						switch ( vecElementType[ uiIndex ] ){
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
					if ( szElementName == "undefined" ){
						//no value for type "undefined" ->nothing to do
					}else if ( szElementName == "value" ){
						const char * pcValue = pXmlElement->GetText();
						cout<<"The value of the element is: "<< pcValue <<endl;
						//converting value to double
						if ( (1 <= iNumberOfElement) &&
								( iNumberOfElement <= (int)uiVectorElements ) ){
							long lValue;
							int iReadValues = sscanf ( pcValue, "%ld", & lValue );
							if ( iReadValues != 0){
								if ( lValue == vecValues[ uiIndex ] ){
									cout<<"The value of the element is correct."<<endl;
								}else{
									cerr<<"Error: The value of the element should be : "<<
										vecValues[ uiIndex ] <<endl;
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
						if ( (1 <= iNumberOfElement) &&
								( iNumberOfElement <= (int)uiVectorElements ) ){
							long lValue;
							int iReadValues = sscanf ( pcValue, "%ld", & lValue );
							if ( iReadValues != 0){
								if ( lValue == vecValues[ uiIndex ] ){
									cout<<"The variablenumber of the element is correct."<<endl;
								}else{
									cerr<<"Error: The variablenumber of the element should be : "<<
										vecValues[ uiIndex ] <<endl;
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
			}//end for all vectors
			if ( uiMatrixVectors != uiLoadedSubFibVector ){
				cerr<<"Error: "<< uiLoadedSubFibVector <<" vector with values to sets loded, but ther schould be "<<
					uiMatrixVectors <<" vectors with values to set."<<endl;
				iReturn++;
			}
		}//end read vectors
		pXmlSubElement = pXmlSubElement->NextSiblingElement();
	}
	
	//check subobject
	if ( bHasPointSubobject ){
		
		if ( pXmlSubElement ){
			const string szSubobjectElementName = pXmlSubElement->Value();
			//read / check defined variables
			if ( szSubobjectElementName == "point" ){
				cout<<"The Fib matrix element subobject name is correctly point. "<<endl;
			}else{
				cerr<<"Error: The Fib matrix element subobject name is not point."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The Fib matrix element contains no subobject, but it should."<<endl;
			iReturn++;
		}

	}else{//the matrix element has no subobject
		if ( ! pXmlSubElement ){
			cout<<"The Fib matrix element contains correctly no subobject. "<<endl;
		
		}else{
			cerr<<"Error: The Fib matrix element contains a subobject, but it shouldn't."<<endl;
			iReturn++;
		}
	}
	
	return iReturn;
}



/**
 * This method tests the storeXml() method of the cFibMatrix class.
 * Just storing properties with no subobjects is tested.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a matrix element"<<endl;

	cout<<"cFibMatrix fibMatrix1( 0, 0 );"<<endl;
	cFibMatrix fibMatrix1( 0, 0 );
	
	if ( fibMatrix1.getDefinedVariable( 1 ) ){
		cout<<"fibMatrix1.getDefinedVariable( 1 )->setValue( 1 );"<<endl;
		fibMatrix1.getDefinedVariable( 1 )->setValue( 1 );
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlFibMatrixFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrix1.xml" );
	ofstream * pFileVectorPostion = new ofstream( szXmlFibMatrixFileName );
	
	bool bStoreSuccesfull = fibMatrix1.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibMatrix was stored successfull to the file \""<< szXmlFibMatrixFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibMatrix to the file \""<< szXmlFibMatrixFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	vector<char> vecAreaElementTypePosition( 32, 'w' );
	vector<long> vecAreaValuesPosition( 32, 0 );
	vector<char> vecElementTypePosition( 32, 'w' );
	vector<long> vecValuesPosition( 32, 0 );
	
	iReturn += testXmlFibMatrix( szXmlFibMatrixFileName, 1,
		1, 0, 1, vecAreaElementTypePosition, vecAreaValuesPosition,
		0, vecElementTypePosition, vecValuesPosition, false );
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a matrix element with one area vector and one vector"<<endl;

	cout<<"cFibMatrix fibMatrixDef1S1E1V1( 1, 1 );"<<endl;
	cFibMatrix fibMatrixDef1S1E1V1( 1, 1 );
	
	cout<<"fibMatrixDef1S1E1V1.getArea( 1 )->setValue( 1, 1 );"<<endl;
	fibMatrixDef1S1E1V1.getArea( 1 )->setValue( 1, 1 );
	vecAreaValuesPosition[ 0 ] = 1;
	cout<<"fibMatrixDef1S1E1V1.getArea( 1 )->setValue( 2, 2 );"<<endl;
	fibMatrixDef1S1E1V1.getArea( 1 )->setValue( 2, 2 );
	vecAreaValuesPosition[ 1 ] = 2;
	
	cout<<"cVectorFibMatrix vecFibMatrixE1( fibMatrixDef1S1E1V1 );"<<endl;
	cVectorFibMatrix vecFibMatrixE1( fibMatrixDef1S1E1V1 );
	cout<<"vecFibMatrixE1.setValue( 1, 1 );"<<endl;
	vecFibMatrixE1.setValue( 1, 1 );
	vecValuesPosition[ 0 ] = 1;
	cout<<"fibMatrixDef1S1E1V1.addVector( vecFibMatrixE1 );"<<endl;
	fibMatrixDef1S1E1V1.addVector( vecFibMatrixE1 );
	
	if ( fibMatrixDef1S1E1V1.getDefinedVariable( 1 ) ){
		cout<<"fibMatrixDef1S1E1V1.getDefinedVariable( 1 )->setValue( 1 );"<<endl;
		fibMatrixDef1S1E1V1.getDefinedVariable( 1 )->setValue( 1 );
	}
	if ( fibMatrixDef1S1E1V1.getDefinedVariable( 2 ) ){
		cout<<"fibMatrixDef1S1E1V1.getDefinedVariable( 2 )->setValue( 2 );"<<endl;
		fibMatrixDef1S1E1V1.getDefinedVariable( 2 )->setValue( 2 );
	}
	
	szFileNameBuffer[0] = 0;
	szXmlFibMatrixFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixDef1S1E1V1.xml" );
	pFileVectorPostion = new ofstream( szXmlFibMatrixFileName );
	
	bStoreSuccesfull = fibMatrixDef1S1E1V1.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibMatrix was stored successfull to the file \""<< szXmlFibMatrixFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibMatrix to the file \""<< szXmlFibMatrixFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibMatrix( szXmlFibMatrixFileName, 1,
		2, 0, 1, vecAreaElementTypePosition, vecAreaValuesPosition,
		1, vecElementTypePosition, vecValuesPosition, false );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a matrix element with some area vectors and vectors"<<endl;

	cout<<"cFibMatrix fibMatrixDef3S1E3V1( 2, 3 );"<<endl;
	cFibMatrix fibMatrixDef3S1E3V1( 2, 3 );
	cout<<"fibMatrixDef3S1E3V1.getArea( 1 )->setValue( 1, 3 );"<<endl;
	fibMatrixDef3S1E3V1.getArea( 1 )->setValue( 1, 3 );
	vecAreaValuesPosition[ 0 ] = 3;
	cout<<"fibMatrixDef3S1E3V1.getArea( 1 )->setValue( 2, -2 );"<<endl;
	fibMatrixDef3S1E3V1.getArea( 1 )->setValue( 2, -2 );
	vecAreaValuesPosition[ 1 ] = -2;
	cout<<"fibMatrixDef3S1E3V1.getArea( 2 )->setValue( 1, 55 );"<<endl;
	fibMatrixDef3S1E3V1.getArea( 2 )->setValue( 1, 55 );
	vecAreaValuesPosition[ 2 ] = 55;
	cout<<"fibMatrixDef3S1E3V1.getArea( 2 )->setValue( 2, 57 );"<<endl;
	fibMatrixDef3S1E3V1.getArea( 2 )->setValue( 2, 57 );
	vecAreaValuesPosition[ 3 ] = 57;
	
	cout<<"cVectorFibMatrix vecFibMatrixE3( fibMatrixDef3S1E3V1 );"<<endl;
	cVectorFibMatrix vecFibMatrixE3( fibMatrixDef3S1E3V1 );
	cout<<"vecFibMatrixE3.setValue( 1, 1 );"<<endl;
	vecFibMatrixE3.setValue( 1, 1 );
	vecValuesPosition[ 0 ] = 1;
	cout<<"vecFibMatrixE3.setValue( 2, 2 );"<<endl;
	vecFibMatrixE3.setValue( 2, 2 );
	vecValuesPosition[ 1 ] = 2;
	cout<<"vecFibMatrixE3.setValue( 3, 3 );"<<endl;
	vecFibMatrixE3.setValue( 3, 3 );
	vecValuesPosition[ 2 ] = 3;
	cout<<"fibMatrixDef3S1E3V1.addVector( vecFibMatrixE3 );"<<endl;
	fibMatrixDef3S1E3V1.addVector( vecFibMatrixE3 );
	
	cout<<"vecFibMatrixE3.setValue( 1, 5 );"<<endl;
	vecFibMatrixE3.setValue( 1, 5 );
	vecValuesPosition[ 3 ] = 5;
	cout<<"vecFibMatrixE3.setValue( 2, 21 );"<<endl;
	vecFibMatrixE3.setValue( 2, 21 );
	vecValuesPosition[ 4 ] = 21;
	cout<<"vecFibMatrixE3.setValue( 3, 12 );"<<endl;
	vecFibMatrixE3.setValue( 3, 12 );
	vecValuesPosition[ 5 ] = 12;
	cout<<"fibMatrixDef3S1E3V1.addVector( vecFibMatrixE3 );"<<endl;
	fibMatrixDef3S1E3V1.addVector( vecFibMatrixE3 );
	
	if ( fibMatrixDef3S1E3V1.getDefinedVariable( 1 ) ){
		cout<<"fibMatrixDef3S1E3V1.getDefinedVariable( 1 )->setValue( 1 );"<<endl;
		fibMatrixDef3S1E3V1.getDefinedVariable( 1 )->setValue( 1 );
	}
	if ( fibMatrixDef3S1E3V1.getDefinedVariable( 2 ) ){
		cout<<"fibMatrixDef3S1E3V1.getDefinedVariable( 2 )->setValue( 2 );"<<endl;
		fibMatrixDef3S1E3V1.getDefinedVariable( 2 )->setValue( 2 );
	}
	if ( fibMatrixDef3S1E3V1.getDefinedVariable( 3 ) ){
		cout<<"fibMatrixDef3S1E3V1.getDefinedVariable( 3 )->setValue( 3 );"<<endl;
		fibMatrixDef3S1E3V1.getDefinedVariable( 3 )->setValue( 3 );
	}
	if ( fibMatrixDef3S1E3V1.getDefinedVariable( 4 ) ){
		cout<<"fibMatrixDef3S1E3V1.getDefinedVariable( 4 )->setValue( 4 );"<<endl;
		fibMatrixDef3S1E3V1.getDefinedVariable( 4 )->setValue( 4 );
	}
	if ( fibMatrixDef3S1E3V1.getDefinedVariable( 5 ) ){
		cout<<"fibMatrixDef3S1E3V1.getDefinedVariable( 5 )->setValue( 5 );"<<endl;
		fibMatrixDef3S1E3V1.getDefinedVariable( 5 )->setValue( 5 );
	}
	
	szFileNameBuffer[0] = 0;
	szXmlFibMatrixFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixDef3S1E3V1.xml" );
	pFileVectorPostion = new ofstream( szXmlFibMatrixFileName );
	
	bStoreSuccesfull = fibMatrixDef3S1E3V1.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibMatrix was stored successfull to the file \""<< szXmlFibMatrixFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibMatrix to the file \""<< szXmlFibMatrixFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibMatrix( szXmlFibMatrixFileName, 1,
		5, 0, 2, vecAreaElementTypePosition, vecAreaValuesPosition,
		2, vecElementTypePosition, vecValuesPosition, false );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a matrix element with a point subobject"<<endl;

	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cFibMatrix fibMatrixDef2( 1, 2, &point1 );"<<endl;
	cFibMatrix fibMatrixDef2( 1, 2, &point1 );
	
	cout<<"fibMatrixDef2.getArea( 1 )->setValue( 1, 7 );"<<endl;
	fibMatrixDef2.getArea( 1 )->setValue( 1, 7 );
	vecAreaValuesPosition[ 0 ] = 7;
	cout<<"fibMatrixDef2.getArea( 1 )->setValue( 2, 4 );"<<endl;
	fibMatrixDef2.getArea( 1 )->setValue( 2, 4 );
	vecAreaValuesPosition[ 1 ] = 4;
	
	cout<<"cVectorFibMatrix vecFibMatrixE2( fibMatrixDef2 );"<<endl;
	cVectorFibMatrix vecFibMatrixE2( fibMatrixDef2 );
	cout<<"vecFibMatrixE2.setValue( 1, 5 );"<<endl;
	vecFibMatrixE2.setValue( 1, 5 );
	vecValuesPosition[ 0 ] = 5;
	cout<<"vecFibMatrixE2.setValue( 2, -7 );"<<endl;
	vecFibMatrixE2.setValue( 2, -7 );
	vecValuesPosition[ 1 ] = -7;
	cout<<"fibMatrixDef2.addVector( vecFibMatrixE2 );"<<endl;
	fibMatrixDef2.addVector( vecFibMatrixE2 );
	
	if ( fibMatrixDef2.getDefinedVariable( 1 ) ){
		cout<<"fibMatrixDef2.getDefinedVariable( 1 )->setValue( 3 );"<<endl;
		fibMatrixDef2.getDefinedVariable( 1 )->setValue( 3 );
	}
	if ( fibMatrixDef2.getDefinedVariable( 2 ) ){
		cout<<"fibMatrixDef2.getDefinedVariable( 2 )->setValue( 4 );"<<endl;
		fibMatrixDef2.getDefinedVariable( 2 )->setValue( 4 );
	}
	if ( fibMatrixDef2.getDefinedVariable( 3 ) ){
		cout<<"fibMatrixDef2.getDefinedVariable( 3 )->setValue( 5 );"<<endl;
		fibMatrixDef2.getDefinedVariable( 3 )->setValue( 5 );
	}
	
	szFileNameBuffer[0] = 0;
	szXmlFibMatrixFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixDef2Point.xml" );
	pFileVectorPostion = new ofstream( szXmlFibMatrixFileName );
	
	bStoreSuccesfull = fibMatrixDef2.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibMatrix was stored successfull to the file \""<< szXmlFibMatrixFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibMatrix to the file \""<< szXmlFibMatrixFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibMatrix( szXmlFibMatrixFileName, 3,
		3, 0, 1, vecAreaElementTypePosition, vecAreaValuesPosition,
		1, vecElementTypePosition, vecValuesPosition, true );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a matrix element with a domain number"<<endl;

	cout<<"fibMatrixDef2.setDomainNr( 7 )"<<endl;
	fibMatrixDef2.setDomainNr( 7 );
	
	szFileNameBuffer[0] = 0;
	szXmlFibMatrixFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixDef2Dom7.xml" );
	pFileVectorPostion = new ofstream( szXmlFibMatrixFileName );
	
	bStoreSuccesfull = fibMatrixDef2.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibMatrix was stored successfull to the file \""<< szXmlFibMatrixFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibMatrix to the file \""<< szXmlFibMatrixFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibMatrix( szXmlFibMatrixFileName, 3,
		3, 7, 1, vecAreaElementTypePosition, vecAreaValuesPosition,
		1, vecElementTypePosition, vecValuesPosition, true );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a matrix element with two vectors with values set"<<endl;

	cout<<"vecFibMatrixE2.setValue( 1, -1 );"<<endl;
	vecFibMatrixE2.setValue( 1, -1 );
	vecValuesPosition[ 2 ] = -1;
	cout<<"vecFibMatrixE2.setValue( 2, 4 );"<<endl;
	vecFibMatrixE2.setValue( 2, 4 );
	vecValuesPosition[ 3 ] = 4;
	cout<<"fibMatrixDef2.addVector( vecFibMatrixE2 );"<<endl;
	fibMatrixDef2.addVector( vecFibMatrixE2 );
	
	szFileNameBuffer[0] = 0;
	szXmlFibMatrixFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixDef2Vec2.xml" );
	pFileVectorPostion = new ofstream( szXmlFibMatrixFileName );
	
	bStoreSuccesfull = fibMatrixDef2.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibMatrix was stored successfull to the file \""<< szXmlFibMatrixFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibMatrix to the file \""<< szXmlFibMatrixFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibMatrix( szXmlFibMatrixFileName, 3,
		3, 7, 1, vecAreaElementTypePosition, vecAreaValuesPosition,
		2, vecElementTypePosition, vecValuesPosition, true );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a matrix element with 5 vectors with values set"<<endl;

	cout<<"vecFibMatrixE2.setValue( 1, 3 );"<<endl;
	vecFibMatrixE2.setValue( 1, 3 );
	vecValuesPosition[ 4 ] = 3;
	cout<<"vecFibMatrixE2.setValue( 2, 99 );"<<endl;
	vecFibMatrixE2.setValue( 2, 99 );
	vecValuesPosition[ 5 ] = 99;
	cout<<"fibMatrixDef2.addVector( vecFibMatrixE2 );"<<endl;
	fibMatrixDef2.addVector( vecFibMatrixE2 );
	cout<<"vecFibMatrixE2.setValue( 1, 4 );"<<endl;
	vecFibMatrixE2.setValue( 1, 4 );
	vecValuesPosition[ 6 ] = 4;
	cout<<"vecFibMatrixE2.setValue( 2, -19 );"<<endl;
	vecFibMatrixE2.setValue( 2, -19 );
	vecValuesPosition[ 7 ] = -19;
	cout<<"fibMatrixDef2.addVector( vecFibMatrixE2 );"<<endl;
	fibMatrixDef2.addVector( vecFibMatrixE2 );
	cout<<"vecFibMatrixE2.setValue( 1, 5 );"<<endl;
	vecFibMatrixE2.setValue( 1, 5 );
	vecValuesPosition[ 8 ] = 5;
	cout<<"vecFibMatrixE2.setValue( 2, 33 );"<<endl;
	vecFibMatrixE2.setValue( 2, 33 );
	vecValuesPosition[ 9 ] = 33;
	cout<<"fibMatrixDef2.addVector( vecFibMatrixE2 );"<<endl;
	fibMatrixDef2.addVector( vecFibMatrixE2 );
	
	szFileNameBuffer[0] = 0;
	szXmlFibMatrixFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixDef2Vec5.xml" );
	pFileVectorPostion = new ofstream( szXmlFibMatrixFileName );
	
	bStoreSuccesfull = fibMatrixDef2.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibMatrix was stored successfull to the file \""<< szXmlFibMatrixFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibMatrix to the file \""<< szXmlFibMatrixFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibMatrix( szXmlFibMatrixFileName, 3,
		3, 7, 1, vecAreaElementTypePosition, vecAreaValuesPosition,
		5, vecElementTypePosition, vecValuesPosition, true );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a matrix element with variables set"<<endl;

	cout<<"vecFibMatrixE2.setValue( 1, 22 );"<<endl;
	vecFibMatrixE2.setValue( 1, 22 );
	vecValuesPosition[ 4 ] = 22;
	cout<<"vecFibMatrixE2.setVariable( 2, fibMatrixDef3S1E3V1.getDefinedVariable( 3 ) );"<<endl;
	vecFibMatrixE2.setVariable( 2, fibMatrixDef3S1E3V1.getDefinedVariable( 3 ) );
	vecElementTypePosition[ 5 ] = 'v';
	vecValuesPosition[ 5 ] = 3;
	cout<<"fibMatrixDef2.setVector( vecFibMatrixE2, 3 );"<<endl;
	fibMatrixDef2.setVector( vecFibMatrixE2, 3 );
	
	cout<<"vecFibMatrixE2.setVariable( 1, fibMatrixDef3S1E3V1.getDefinedVariable( 1 ) );"<<endl;
	vecFibMatrixE2.setVariable( 1, fibMatrixDef3S1E3V1.getDefinedVariable( 1 ) );
	vecElementTypePosition[ 6 ] = 'v';
	vecValuesPosition[ 6 ] = 1;
	cout<<"vecFibMatrixE2.setValue( 2, -8 );"<<endl;
	vecFibMatrixE2.setValue( 2, -8 );
	vecValuesPosition[ 7 ] = -8;
	cout<<"fibMatrixDef2.setVector( vecFibMatrixE2, 4 );"<<endl;
	fibMatrixDef2.setVector( vecFibMatrixE2, 4 );
	
	szFileNameBuffer[0] = 0;
	szXmlFibMatrixFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixDef2Vec5.xml" );
	pFileVectorPostion = new ofstream( szXmlFibMatrixFileName );
	
	bStoreSuccesfull = fibMatrixDef2.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibMatrix was stored successfull to the file \""<< szXmlFibMatrixFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibMatrix to the file \""<< szXmlFibMatrixFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibMatrix( szXmlFibMatrixFileName, 3,
		3, 7, 1, vecAreaElementTypePosition, vecAreaValuesPosition,
		5, vecElementTypePosition, vecValuesPosition, true );
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a matrix element with some area vectors and vectors"<<endl;

	cout<<"cFibMatrix fibMatrixDim4VE3( 4, 3, &point1 );"<<endl;
	cFibMatrix fibMatrixDim4VE3( 4, 3, &point1 );
	cout<<"fibMatrixDim4VE3.getArea( 1 )->setVariable( 1, fibMatrixDef3S1E3V1.getDefinedVariable( 3 ) );"<<endl;
	fibMatrixDim4VE3.getArea( 1 )->setVariable( 1, fibMatrixDef3S1E3V1.getDefinedVariable( 3 ) );
	vecAreaElementTypePosition[ 0 ] = 'v';
	vecAreaValuesPosition[ 0 ] = 3;
	cout<<"fibMatrixDim4VE3.getArea( 1 )->setValue( 2, -2 );"<<endl;
	fibMatrixDim4VE3.getArea( 1 )->setValue( 2, -2 );
	vecAreaValuesPosition[ 1 ] = -2;
	cout<<"fibMatrixDim4VE3.getArea( 2 )->setVariable( 1, fibMatrixDef3S1E3V1.getDefinedVariable( 1 ) );"<<endl;
	fibMatrixDim4VE3.getArea( 2 )->setVariable( 1, fibMatrixDef3S1E3V1.getDefinedVariable( 1 ) );
	vecAreaElementTypePosition[ 2 ] = 'v';
	vecAreaValuesPosition[ 2 ] = 1;
	cout<<"fibMatrixDim4VE3.getArea( 2 )->setValue( 2, 57 );"<<endl;
	fibMatrixDim4VE3.getArea( 2 )->setValue( 2, 57 );
	vecAreaValuesPosition[ 3 ] = 57;
	cout<<"fibMatrixDim4VE3.getArea( 3 )->setValue( 1, 55 );"<<endl;
	fibMatrixDim4VE3.getArea( 3 )->setValue( 1, 55 );
	vecAreaValuesPosition[ 4 ] = 55;
	cout<<"fibMatrixDim4VE3.getArea( 3 )->setVariable( 2, fibMatrixDef3S1E3V1.getDefinedVariable( 2 ) );"<<endl;
	fibMatrixDim4VE3.getArea( 3 )->setVariable( 2, fibMatrixDef3S1E3V1.getDefinedVariable( 2 ) );
	vecAreaElementTypePosition[ 5 ] = 'v';
	vecAreaValuesPosition[ 5 ] = 2;
	cout<<"fibMatrixDim4VE3.getArea( 4 )->setValue( 1, 55 );"<<endl;
	fibMatrixDim4VE3.getArea( 4 )->setValue( 1, 55 );
	vecAreaValuesPosition[ 6 ] = 55;
	cout<<"fibMatrixDim4VE3.getArea( 4 )->setVariable( 2, fibMatrixDef3S1E3V1.getDefinedVariable( 1 ) );"<<endl;
	fibMatrixDim4VE3.getArea( 4 )->setVariable( 2, fibMatrixDef3S1E3V1.getDefinedVariable( 1 ) );
	vecAreaElementTypePosition[ 7 ] = 'v';
	vecAreaValuesPosition[ 7 ] = 1;
	
	cout<<"vecFibMatrixE3.setValue( 1, 1 );"<<endl;
	vecFibMatrixE3.setValue( 1, 1 );
	vecValuesPosition[ 0 ] = 1;
	cout<<"vecFibMatrixE3.setVariable( 2, fibMatrixDef3S1E3V1.getDefinedVariable( 2 ) );"<<endl;
	vecFibMatrixE3.setVariable( 2, fibMatrixDef3S1E3V1.getDefinedVariable( 2 ) );
	vecElementTypePosition[ 1 ] = 'v';
	vecValuesPosition[ 1 ] = 2;
	cout<<"vecFibMatrixE3.setValue( 3, 3 );"<<endl;
	vecFibMatrixE3.setValue( 3, 3 );
	vecValuesPosition[ 2 ] = 3;
	cout<<"fibMatrixDim4VE3.addVector( vecFibMatrixE3 );"<<endl;
	fibMatrixDim4VE3.addVector( vecFibMatrixE3 );
	
	cout<<"vecFibMatrixE3.setValue( 1, 5 );"<<endl;
	vecFibMatrixE3.setValue( 1, 5 );
	vecValuesPosition[ 3 ] = 5;
	cout<<"vecFibMatrixE3.setValue( 2, 21 );"<<endl;
	vecFibMatrixE3.setValue( 2, 21 );
	vecValuesPosition[ 4 ] = 21;
	cout<<"vecFibMatrixE3.setVariable( 3, fibMatrixDef3S1E3V1.getDefinedVariable( 3 ) );"<<endl;
	vecFibMatrixE3.setVariable( 3, fibMatrixDef3S1E3V1.getDefinedVariable( 3 ) );
	vecElementTypePosition[ 5 ] = 'v';
	vecValuesPosition[ 5 ] = 3;
	cout<<"fibMatrixDim4VE3.addVector( vecFibMatrixE3 );"<<endl;
	fibMatrixDim4VE3.addVector( vecFibMatrixE3 );
	
	cout<<"vecFibMatrixE3.setVariable( 1, fibMatrixDef3S1E3V1.getDefinedVariable( 3 ) );"<<endl;
	vecFibMatrixE3.setVariable( 1, fibMatrixDef3S1E3V1.getDefinedVariable( 3 ) );
	vecElementTypePosition[ 6 ] = 'v';
	vecValuesPosition[ 6 ] = 3;
	cout<<"vecFibMatrixE3.setValue( 2, 21 );"<<endl;
	vecFibMatrixE3.setValue( 2, 21 );
	vecValuesPosition[ 7 ] = 21;
	cout<<"vecFibMatrixE3.setVariable( 3, fibMatrixDef3S1E3V1.getDefinedVariable( 1 ) );"<<endl;
	vecFibMatrixE3.setVariable( 3, fibMatrixDef3S1E3V1.getDefinedVariable( 1 ) );
	vecElementTypePosition[ 8 ] = 'v';
	vecValuesPosition[ 8 ] = 1;
	cout<<"fibMatrixDim4VE3.addVector( vecFibMatrixE3 );"<<endl;
	fibMatrixDim4VE3.addVector( vecFibMatrixE3 );
	
	if ( fibMatrixDim4VE3.getDefinedVariable( 1 ) ){
		cout<<"fibMatrixDim4VE3.getDefinedVariable( 1 )->setValue( 2 );"<<endl;
		fibMatrixDim4VE3.getDefinedVariable( 1 )->setValue( 2 );
	}
	if ( fibMatrixDim4VE3.getDefinedVariable( 2 ) ){
		cout<<"fibMatrixDim4VE3.getDefinedVariable( 2 )->setValue( 3 );"<<endl;
		fibMatrixDim4VE3.getDefinedVariable( 2 )->setValue( 3 );
	}
	if ( fibMatrixDim4VE3.getDefinedVariable( 3 ) ){
		cout<<"fibMatrixDim4VE3.getDefinedVariable( 3 )->setValue( 4 );"<<endl;
		fibMatrixDim4VE3.getDefinedVariable( 3 )->setValue( 4 );
	}
	if ( fibMatrixDim4VE3.getDefinedVariable( 4 ) ){
		cout<<"fibMatrixDim4VE3.getDefinedVariable( 4 )->setValue( 5 );"<<endl;
		fibMatrixDim4VE3.getDefinedVariable( 4 )->setValue( 5 );
	}
	if ( fibMatrixDim4VE3.getDefinedVariable( 5 ) ){
		cout<<"fibMatrixDim4VE3.getDefinedVariable( 5 )->setValue( 6 );"<<endl;
		fibMatrixDim4VE3.getDefinedVariable( 5 )->setValue( 6 );
	}
	if ( fibMatrixDim4VE3.getDefinedVariable( 6 ) ){
		cout<<"fibMatrixDim4VE3.getDefinedVariable( 6 )->setValue( 7 );"<<endl;
		fibMatrixDim4VE3.getDefinedVariable( 6 )->setValue( 7 );
	}
	if ( fibMatrixDim4VE3.getDefinedVariable( 7 ) ){
		cout<<"fibMatrixDim4VE3.getDefinedVariable( 7 )->setValue( 8 );"<<endl;
		fibMatrixDim4VE3.getDefinedVariable( 7 )->setValue( 8 );
	}
	
	szFileNameBuffer[0] = 0;
	szXmlFibMatrixFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixDim4VE3.xml" );
	pFileVectorPostion = new ofstream( szXmlFibMatrixFileName );
	
	bStoreSuccesfull = fibMatrixDim4VE3.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibMatrix was stored successfull to the file \""<< szXmlFibMatrixFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibMatrix to the file \""<< szXmlFibMatrixFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibMatrix( szXmlFibMatrixFileName, 2,
		7, 0, 4, vecAreaElementTypePosition, vecAreaValuesPosition,
		3, vecElementTypePosition, vecValuesPosition, true );
	
	
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

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a empty cFibMatrix"<<endl;

	cout<<"cVectorPosition vecPosition( 0 );"<<flush<<endl;
	cVectorPosition vecPosition( 0 );

	cout<<"cPoint point1( &vecPosition );"<<flush<<endl;
	cPoint point1( &vecPosition );

	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;

	cout<<"cFibMatrix fibMatrixDef1( 1, 2, &point1, &root );"<<endl;
	cFibMatrix fibMatrixDef1( 1, 2, &point1, &root );

	//test get compressed size
	//introduction + count dimensions + count vector elements variables + count vectors + area vectors + point
	unsigned int uiCompressedSize = 17 + 8 + 8 + 32 + 34 + 5;
	if ( (unsigned int)(fibMatrixDef1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			fibMatrixDef1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixDef1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bool bStoreSuccesfull = fibMatrixDef1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cFibMatrix1[] = { (char)0x2F, (char)0x00, (char)0x02, (char)0x04, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x10 };
	// 00010   0000 0000  0000 0000 0  0000 0000  0000 0000 0   0000 0000  0000 0000  0000 0000  0000 0000   0000 0010  0000 0001 0 0000 0000 0010 1111 <-
	// =0010 1111  0000 0000  0000 0010  0000 0100  0000 0000  0000 0000  0000 0000  0000 0000  0000 0000  0000 0000  0000 0000  0000 0000  0001 0000
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibMatrix1, 13 );

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with one vector and changed area vector"<<endl;

	cout<<"fibMatrixDef1.getDefinedVariable( 1 )->setIntegerValue( 1 ); (should not change anything)"<<endl;
	fibMatrixDef1.getDefinedVariable( 1 )->setIntegerValue( 1 );
	cout<<"fibMatrixDef1.getDefinedVariable( 3 )->setIntegerValue( 6 ); (should not change anything)"<<endl;
	fibMatrixDef1.getDefinedVariable( 3 )->setIntegerValue( 6 );
	
	cout<<"fibMatrixDef1.getArea()->setLowerBoundValue( 5 );"<<endl;
	fibMatrixDef1.getArea()->setLowerBoundValue( 5 );
	cout<<"fibMatrixDef1.getArea()->setUpperBoundValue( 1 );"<<endl;
	fibMatrixDef1.getArea()->setUpperBoundValue( 1 );
	
	cout<<"cVectorFibMatrix vecFibMatrixE1( fibMatrixDef1 );"<<endl;
	cVectorFibMatrix vecFibMatrixE1( fibMatrixDef1 );
	cout<<"vecFibMatrixE1.setValue( 1, 2 );"<<endl;
	vecFibMatrixE1.setValue( 1, 2 );
	cout<<"vecFibMatrixE1.setValue( 2, 3 );"<<endl;
	vecFibMatrixE1.setValue( 2, 3 );
	cout<<"fibMatrixDef1.addVector( vecFibMatrixE1 );"<<endl;
	fibMatrixDef1.addVector( vecFibMatrixE1 );
	
	//test get compressed size
	//introduction + count dimensions + count vector elements variables + count vectors + area vectors + vectors + point
	uiCompressedSize = 17 + 8 + 8 + 32 + 1 * 34 + 1 *(2 *(1 + 32)) + 5;
	if ( (unsigned int)(fibMatrixDef1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			fibMatrixDef1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixVec1E1V2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = fibMatrixDef1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char szFibMatrixVec1E1V2[] = { (char)0x2F, (char)0x00, (char)0x02, (char)0x04, (char)0x02, (char)0x00, (char)0x00, (char)0x00, (char)0x14, (char)0x00, (char)0x08, (char)0x00, (char)0x20, (char)0x00, (char)0x00, (char)0x00, (char)0x60, (char)0x00, (char)0x00, (char)0x00, (char)0x40, (char)0x00 };
	//   00010   0000 0000  0000 0000  0000 0000  0000 0011 0  0000 0000  0000 0000  0000 0000  0000 0010 0   0000 0000  0000 0001 0  0000 0000  0000 0101 0   0000 0000  0000 0000  0000 0000  0000 0001   0000 0010  0000 0001 0 0000 0000 0010 1111 <-
	//->=0010 1111  0000 0000  0000 0010  0000 0100  0000 0010  0000 0000  0000 0000  0000 0000  0001 0100  0000 0000  0000 1000  0000 0000  0010 0000  0000 0000  0000 0000  0000 0000  0110 0000  0000 0000  0000 0000  0000 0000  0100 0000  00
	iReturn += compareBytsWithFile( szFileNameBuffer, szFibMatrixVec1E1V2, 22 );

	

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with more than one variable"<<endl;

	cout<<"cPoint point2( &vecPosition );"<<flush<<endl;
	cPoint point2( &vecPosition );

	cout<<"cRoot root2;"<<flush<<endl;
	cRoot root2;

	cout<<"cFibMatrix fibMatrixDef3( 2, 3, &point2, &root2 );"<<endl;
	cFibMatrix fibMatrixDef3( 2, 3, &point2, &root2 );
	
	cout<<"fibMatrixDef3.getArea( 1 )->setLowerBoundValue( 1 );"<<endl;
	fibMatrixDef3.getArea( 1 )->setLowerBoundValue( 1 );
	cout<<"fibMatrixDef3.getArea( 1 )->setUpperBoundValue( 5 );"<<endl;
	fibMatrixDef3.getArea( 1 )->setUpperBoundValue( 5 );
	
	cout<<"fibMatrixDef3.getArea( 2 )->setLowerBoundValue( 4 );"<<endl;
	fibMatrixDef3.getArea( 2 )->setLowerBoundValue( 4 );
	cout<<"fibMatrixDef3.getArea( 2 )->setUpperBoundValue( 3 );"<<endl;
	fibMatrixDef3.getArea( 2 )->setUpperBoundValue( 3 );
	
	
	cout<<"cVectorFibMatrix vecFibMatrixE3( fibMatrixDef3 );"<<endl;
	cVectorFibMatrix vecFibMatrixE3( fibMatrixDef3 );
	cout<<"vecFibMatrixE3.setValue( 1, 2 );"<<endl;
	vecFibMatrixE3.setValue( 1, 2 );
	cout<<"vecFibMatrixE3.setValue( 2, 3 );"<<endl;
	vecFibMatrixE3.setValue( 2, 3 );
	cout<<"vecFibMatrixE3.setValue( 3, 5 );"<<endl;
	vecFibMatrixE3.setValue( 3, 5 );
	cout<<"fibMatrixDef3.addVector( vecFibMatrixE3 );"<<endl;
	fibMatrixDef3.addVector( vecFibMatrixE3 );
	
	//test get compressed size
	//introduction + count dimensions + count vector elements variables + count vectors + area vectors + vectors + point
	uiCompressedSize = 17 + 8 + 8 + 32 + 2 * 34 + 1 *(3 *(1 + 32)) + 5;
	if ( (unsigned int)(fibMatrixDef3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			fibMatrixDef3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixDef3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = fibMatrixDef3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char szFibMatrixDef3[] = { (char)0x2F, (char)0x00, (char)0x04, (char)0x06, (char)0x02, (char)0x00, (char)0x00, (char)0x00, (char)0x04, (char)0x00, (char)0x28, (char)0x00, (char)0x40, (char)0x00, (char)0x60, (char)0x00, (char)0x80, (char)0x00, (char)0x00, (char)0x00, (char)0x80, (char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x05, (char)0x00, (char)0x00, (char)0x00, (char)0x02  };
	//   00010   0000 0000  0000 0000  0000 0000  0000 0101 0   0000 0000  0000 0000  0000 0000  0000 0011 0  0000 0000  0000 0000  0000 0000  0000 0010 0   0000 0000  0000 0011 0  0000 0000  0000 0100 0   0000 0000  0000 0101 0  0000 0000  0000 0001 0   0000 0000  0000 0000  0000 0000  0000 0001   0000 0011  0000 0010 0 0000 0000 0010 1111 <-
	//->=0010 1111  0000 0000  0000 0100  0000 0110  0000 0010  0000 0000  0000 0000  0000 0000  0000 0100  0000 0000  0010 1000  0000 0000  0100 0000  0000 0000  0110 0000  0000 0000  1000 0000  0000 0000  0000 0000  0000 0000  1000 0000  0000 0001  0000 0000  0000 0000  0000 0000  0000 0101  0000 0000  0000 0000  0000 0000  0000 0010
	iReturn += compareBytsWithFile( szFileNameBuffer, szFibMatrixDef3, 30 );

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with domain number set"<<endl;

	//create vector domain with tree elements
	cout<<"vector<cDomainSingle*> vecDomainsE3Nat4Nat6Nat3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3Nat4Nat6Nat3( 3 );
	cout<<"vecDomainsE3Nat4Nat6Nat3[ 0 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE3Nat4Nat6Nat3[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE3Nat4Nat6Nat3[ 1 ] = new cDomainNaturalNumberBit( 6 );"<<endl;
	vecDomainsE3Nat4Nat6Nat3[ 1 ] = new cDomainNaturalNumberBit( 6 );
	cout<<"vecDomainsE3Nat4Nat6Nat3[ 2 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Nat4Nat6Nat3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"cDomainVector vectorDomainE3Nat4Nat6Nat3( vecDomainsE3Nat4Nat6Nat3 );"<<endl;
	cDomainVector vectorDomainE3Nat4Nat6Nat3( vecDomainsE3Nat4Nat6Nat3 );
	delete vecDomainsE3Nat4Nat6Nat3[ 0 ];
	delete vecDomainsE3Nat4Nat6Nat3[ 1 ];
	delete vecDomainsE3Nat4Nat6Nat3[ 2 ];
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Int5Int9( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Int5Int9( 2 );
	cout<<"vecDomainsE2Int5Int9[ 0 ] = new cDomainIntegerBit( 5 );"<<endl;
	vecDomainsE2Int5Int9[ 0 ] = new cDomainIntegerBit( 5 );
	cout<<"vecDomainsE2Int5Int9[ 1 ] = new cDomainIntegerBit( 9 );"<<endl;
	vecDomainsE2Int5Int9[ 1 ] = new cDomainIntegerBit( 9 );
	cout<<"cDomainVector vectorDomainE2Int5Int9( vecDomainsE2Int5Int9 );"<<endl;
	cDomainVector vectorDomainE2Int5Int9( vecDomainsE2Int5Int9 );
	delete vecDomainsE2Int5Int9[ 0 ];
	delete vecDomainsE2Int5Int9[ 1 ];

	cout<<"vector<cDomain*> vecDomainsE3N2N7VE2N5N9VE3N4N6N3( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3N2N7VE2N5N9VE3N4N6N3( 4 );
	cout<<"vecDomainsE3N2N7VE2N5N9VE3N4N6N3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3N2N7VE2N5N9VE3N4N6N3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3N2N7VE2N5N9VE3N4N6N3[ 1 ] = new cDomainNaturalNumberBit( 7 );"<<endl;
	vecDomainsE3N2N7VE2N5N9VE3N4N6N3[ 1 ] = new cDomainNaturalNumberBit( 7 );
	cout<<"vecDomainsE3N2N7VE2N5N9VE3N4N6N3[ 2 ] = &vectorDomainE2Int5Int9;"<<endl;
	vecDomainsE3N2N7VE2N5N9VE3N4N6N3[ 2 ] = &vectorDomainE2Int5Int9;
	cout<<"vecDomainsE3N2N7VE2N5N9VE3N4N6N3[ 3 ] = &vectorDomainE3Nat4Nat6Nat3;"<<endl;
	vecDomainsE3N2N7VE2N5N9VE3N4N6N3[ 3 ] = &vectorDomainE3Nat4Nat6Nat3;
	cout<<"cDomainVector vectorDomainE3N2N7VE2N5N9VE3N4N6N3( vecDomainsE3N2N7VE2N5N9VE3N4N6N3 );"<<endl;
	cDomainVector vectorDomainE3N2N7VE2N5N9VE3N4N6N3( vecDomainsE3N2N7VE2N5N9VE3N4N6N3 );
	delete vecDomainsE3N2N7VE2N5N9VE3N4N6N3[ 0 ];
	delete vecDomainsE3N2N7VE2N5N9VE3N4N6N3[ 1 ];

	cout<<"cTypeFibMatrix typeFibMatrix;"<<endl;
	cTypeFibMatrix typeFibMatrix;

	cout<<"root2.getValueDomains()->addDomain( typeFibMatrix, &vectorDomainE3N2N7VE2N5N9VE3N4N6N3 );"<<endl;
	root2.getValueDomains()->addDomain( typeFibMatrix, &vectorDomainE3N2N7VE2N5N9VE3N4N6N3 );

	//create vector domain
	cout<<"vector<cDomainSingle*> vecDomainsE3Nat6Nat7Nat8( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3Nat6Nat7Nat8( 3 );
	cout<<"vecDomainsE3Nat6Nat7Nat8[ 0 ] = new cDomainNaturalNumberBit( 6 );"<<endl;
	vecDomainsE3Nat6Nat7Nat8[ 0 ] = new cDomainNaturalNumberBit( 6 );
	cout<<"vecDomainsE3Nat6Nat7Nat8[ 1 ] = new cDomainNaturalNumberBit( 7 );"<<endl;
	vecDomainsE3Nat6Nat7Nat8[ 1 ] = new cDomainNaturalNumberBit( 7 );
	cout<<"vecDomainsE3Nat6Nat7Nat8[ 2 ] = new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomainsE3Nat6Nat7Nat8[ 2 ] = new cDomainNaturalNumberBit( 8 );
	cout<<"cDomainVector vectorDomainE3Nat6Nat7Nat8( vecDomainsE3Nat6Nat7Nat8 );"<<endl;
	cDomainVector vectorDomainE3Nat6Nat7Nat8( vecDomainsE3Nat6Nat7Nat8 );
	delete vecDomainsE3Nat6Nat7Nat8[ 0 ];
	delete vecDomainsE3Nat6Nat7Nat8[ 1 ];
	delete vecDomainsE3Nat6Nat7Nat8[ 2 ];
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Int4Int10( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Int4Int10( 2 );
	cout<<"vecDomainsE2Int4Int10[ 0 ] = new cDomainIntegerBit( 4 );"<<endl;
	vecDomainsE2Int4Int10[ 0 ] = new cDomainIntegerBit( 4 );
	cout<<"vecDomainsE2Int4Int10[ 1 ] = new cDomainIntegerBit( 10 );"<<endl;
	vecDomainsE2Int4Int10[ 1 ] = new cDomainIntegerBit( 10 );
	cout<<"cDomainVector vectorDomainE1Nat1( vecDomainsE2Int4Int10 );"<<endl;
	cDomainVector vectorDomainE2Int4Int10( vecDomainsE2Int4Int10 );
	delete vecDomainsE2Int4Int10[ 0 ];
	delete vecDomainsE2Int4Int10[ 1 ];

	cout<<"vector<cDomain*> vecDomainsE3N3N5VE2N4N10VE3N6N7N8( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3N3N5VE2N4N10VE3N6N7N8( 4 );
	cout<<"vecDomainsE3N3N5VE2N4N10VE3N6N7N8[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3N3N5VE2N4N10VE3N6N7N8[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3N3N5VE2N4N10VE3N6N7N8[ 1 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE3N3N5VE2N4N10VE3N6N7N8[ 1 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE3N3N5VE2N4N10VE3N6N7N8[ 2 ] = &vectorDomainE2Int4Int10;"<<endl;
	vecDomainsE3N3N5VE2N4N10VE3N6N7N8[ 2 ] = &vectorDomainE2Int4Int10;
	cout<<"vecDomainsE3N3N5VE2N4N10VE3N6N7N8[ 3 ] = &vectorDomainE3Nat6Nat7Nat8;"<<endl;
	vecDomainsE3N3N5VE2N4N10VE3N6N7N8[ 3 ] = &vectorDomainE3Nat6Nat7Nat8;
	cout<<"cDomainVector vectorDomainE3N3N5VE2N4N10VE3N6N7N8( vecDomainsE3N3N5VE2N4N10VE3N6N7N8 );"<<endl;
	cDomainVector vectorDomainE3N3N5VE2N4N10VE3N6N7N8( vecDomainsE3N3N5VE2N4N10VE3N6N7N8 );
	delete vecDomainsE3N3N5VE2N4N10VE3N6N7N8[ 0 ];
	delete vecDomainsE3N3N5VE2N4N10VE3N6N7N8[ 1 ];

	cout<<"cTypeFibMatrix typeFibMatrix4( 4 );"<<endl;
	cTypeFibMatrix typeFibMatrix4( 4 );
	cout<<"root2.getValueDomains()->addDomain( typeFibMatrix4, &vectorDomainE3N3N5VE2N4N10VE3N6N7N8 );"<<endl;
	root2.getValueDomains()->addDomain( typeFibMatrix4, &vectorDomainE3N3N5VE2N4N10VE3N6N7N8 );
	
	cout<<"cTypeFibMatrix typeFibMatrix9( 9 );"<<endl;
	cTypeFibMatrix typeFibMatrix9( 9 );
	cDomain * pStandardDomain = typeFibMatrix9.getStandardDomain();
	cout<<"root2.getDomains()->addDomain( typeFibMatrix9, typeFibMatrix9.getStandardDomain() );"<<endl;
	root2.getDomains()->addDomain( typeFibMatrix9, *pStandardDomain );
	delete pStandardDomain;
	
	//create vector domain
	cout<<"vector<cDomainSingle*> vecDomainsE3Int8Int6Int7( 3 );"<<endl;
	vector<cDomainSingle*> vecDomainsE3Int8Int6Int7( 3 );
	cout<<"vecDomainsE3Int8Int6Int7[ 0 ] = new cDomainIntegerBit( 8 );"<<endl;
	vecDomainsE3Int8Int6Int7[ 0 ] = new cDomainIntegerBit( 8 );
	cout<<"vecDomainsE3Int8Int6Int7[ 1 ] = new cDomainIntegerBit( 6 );"<<endl;
	vecDomainsE3Int8Int6Int7[ 1 ] = new cDomainIntegerBit( 6 );
	cout<<"vecDomainsE3Int8Int6Int7[ 2 ] = new cDomainIntegerBit( 7 );"<<endl;
	vecDomainsE3Int8Int6Int7[ 2 ] = new cDomainIntegerBit( 7 );
	cout<<"cDomainVector vectorDomainE3Int8Int6Int7( vecDomainsE3Int8Int6Int7 );"<<endl;
	cDomainVector vectorDomainE3Int8Int6Int7( vecDomainsE3Int8Int6Int7 );
	delete vecDomainsE3Int8Int6Int7[ 0 ];
	delete vecDomainsE3Int8Int6Int7[ 1 ];
	delete vecDomainsE3Int8Int6Int7[ 2 ];
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE2Nat7Nat7( 2 );"<<endl;
	vector<cDomainSingle*> vecDomainsE2Nat7Nat7( 2 );
	cout<<"vecDomainsE2Nat7Nat7[ 0 ] = new cDomainNaturalNumberBit( 7 );"<<endl;
	vecDomainsE2Nat7Nat7[ 0 ] = new cDomainNaturalNumberBit( 7 );
	cout<<"vecDomainsE2Nat7Nat7[ 1 ] = new cDomainNaturalNumberBit( 7 );"<<endl;
	vecDomainsE2Nat7Nat7[ 1 ] = new cDomainNaturalNumberBit( 7 );
	cout<<"cDomainVector vectorDomainE1Nat1( vecDomainsE2Nat7Nat7 );"<<endl;
	cDomainVector vectorDomainE2Nat7Nat7( vecDomainsE2Nat7Nat7 );
	delete vecDomainsE2Nat7Nat7[ 0 ];
	delete vecDomainsE2Nat7Nat7[ 1 ];

	cout<<"vector<cDomain*> vecDomainsE3N5N9VE2NI7I7VE3I8I6I7( 4 );"<<endl;
	vector<cDomain*> vecDomainsE3N5N9VE2NI7I7VE3I8I6I7( 4 );
	cout<<"vecDomainsE3N5N9VE2NI7I7VE3I8I6I7[ 0 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE3N5N9VE2NI7I7VE3I8I6I7[ 0 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE3N5N9VE2NI7I7VE3I8I6I7[ 1 ] = new cDomainNaturalNumberBit( 9 );"<<endl;
	vecDomainsE3N5N9VE2NI7I7VE3I8I6I7[ 1 ] = new cDomainNaturalNumberBit( 9 );
	cout<<"vecDomainsE3N5N9VE2NI7I7VE3I8I6I7[ 2 ] = &vectorDomainE2Nat7Nat7;"<<endl;
	vecDomainsE3N5N9VE2NI7I7VE3I8I6I7[ 2 ] = &vectorDomainE2Nat7Nat7;
	cout<<"vecDomainsE3N5N9VE2NI7I7VE3I8I6I7[ 3 ] = &vectorDomainE3Int8Int6Int7;"<<endl;
	vecDomainsE3N5N9VE2NI7I7VE3I8I6I7[ 3 ] = &vectorDomainE3Int8Int6Int7;
	cout<<"cDomainVector vectorDomainE3N5N9VE2NI7I7VE3I8I6I7( vecDomainsE3N5N9VE2NI7I7VE3I8I6I7 );"<<endl;
	cDomainVector vectorDomainE3N5N9VE2NI7I7VE3I8I6I7( vecDomainsE3N5N9VE2NI7I7VE3I8I6I7 );

	cout<<"cTypeFibMatrix typeFibMatrix13( 13 );"<<endl;
	cTypeFibMatrix typeFibMatrix13( 13 );
	cout<<"root2.getValueDomains()->addDomain( typeFibMatrix13, &vectorDomainE3N5N9VE2NI7I7VE3I8I6I7 );"<<endl;
	root2.getValueDomains()->addDomain( typeFibMatrix13, &vectorDomainE3N5N9VE2NI7I7VE3I8I6I7 );

	
	//create vector domain with
	cout<<"vector<cDomainSingle*> vecDomainsE1Int7( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int7( 1 );
	cout<<"vecDomainsE1Int7[ 0 ] = new cDomainIntegerBit( 7 );"<<endl;
	vecDomainsE1Int7[ 0 ] = new cDomainIntegerBit( 7 );
	cout<<"cDomainVectorOpenEnd vectorDomainE1Int7( vecDomainsE1Int7 );"<<endl;
	cDomainVectorOpenEnd vectorDomainE1Int7( vecDomainsE1Int7 );
	delete vecDomainsE1Int7[ 0 ];

	cout<<"vecDomainsE3N5N9VE2NI7I7VE3I8I6I7[ 3 ] = &vectorDomainE1Int7;"<<endl;
	vecDomainsE3N5N9VE2NI7I7VE3I8I6I7[ 3 ] = &vectorDomainE1Int7;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VOE1Int7( vecDomainsE3N5N9VE2NI7I7VE3I8I6I7 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VOE1Int7( vecDomainsE3N5N9VE2NI7I7VE3I8I6I7 );
	delete vecDomainsE3N5N9VE2NI7I7VE3I8I6I7[ 0 ];
	delete vecDomainsE3N5N9VE2NI7I7VE3I8I6I7[ 1 ];

	cout<<"root2.getDomains()->addDomain( typeFibMatrix13, &vectorDomainE3Na4Nat5VOE1Int7 );"<<endl;
	root2.getDomains()->addDomain( typeFibMatrix13, &vectorDomainE3Na4Nat5VOE1Int7 );

	
	cout<<"fibMatrixDef3.setDomainNr( 4 );"<<endl;
	fibMatrixDef3.setDomainNr( 4 );
	
	//test get compressed size
	//introduction + count dimensions + count vector elements variables + count vectors + area vectors + vectors + point
	uiCompressedSize = 17 + 4 + 2 * 3 + 5 + 2 * (2 + 4 + 10) + 1 * (3 + 6 + 7 + 8) + 5;
	if ( (unsigned int)(fibMatrixDef3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			fibMatrixDef3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixDef3Dom4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = fibMatrixDef3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char szFibMatrixDef3Dom4[] = { (char)0x2F, (char)0x00, (char)0x49, (char)0x0B, (char)0x42, (char)0x01, (char)0xC8, (char)0x00, (char)0x04, (char)0x03, (char)0x05, (char)0x02 };
	//   00010   0000 0101 0   000 0011 0  00 0010 0   00  0000 0011 0  0100 0   00  0000 0101 0  0001 0   0 0001   011  010 0100 1 0000 0000 0010 1111 <-
	//->=0010 1111  0000 0000  0100 1001  0000 1011  0100 0010  0000 0001  1100 1000  0000 0000  0000 0100  0000 0011  0000 0101  0 0010 
	iReturn += compareBytsWithFile( szFileNameBuffer, szFibMatrixDef3Dom4, 12 );

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with domain"<<endl;
	
	cout<<"fibMatrixDef3.setDomainNr( 13 );"<<endl;
	fibMatrixDef3.setDomainNr( 13 );
	
	//test get compressed size
	//introduction + count dimensions + count vector elements variables + area vectors + vectors + point
	uiCompressedSize = 17 + 4 + 2 * 5 + 9 + 2 * (2 + 7 + 7) + 1 * (3 + 8 + 6 + 7) + 5;
	if ( (unsigned int)(fibMatrixDef3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			fibMatrixDef3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixDef3Dom13.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = fibMatrixDef3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char szFibMatrixDef3Dom13[] = { (char)0x2F, (char)0x00, (char)0x5B, (char)0x8C, (char)0x00, (char)0x02, (char)0x0A, (char)0x08, (char)0x06, (char)0x04, (char)0x0C, (char)0x0A, (char)0x02 };
	//   00010   000 0101 0   00 0011 0  0000 0010 0   000 0011 0  000 0100 0   000 0101 0  000 0001 0   0  0000 0001   00011  00010 1101 1 0000 0000 0010 1111 <-
	//->=0010 1111  0000 0000  0101 1011  1000 1100  0000 0000  0000 0010  0000 1010  0000 1000  0000 0110  0000 0100  0000 1100  0000 1010  0 0010 
	iReturn += compareBytsWithFile( szFileNameBuffer, szFibMatrixDef3Dom13, 13 );

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with two vectors"<<endl;
	
	cout<<"vecFibMatrixE3.setValue( 1, 1 );"<<endl;
	vecFibMatrixE3.setValue( 1, 1 );
	cout<<"vecFibMatrixE3.setValue( 2, 7 );"<<endl;
	vecFibMatrixE3.setValue( 2, 7 );
	cout<<"vecFibMatrixE3.setValue( 3, 12 );"<<endl;
	vecFibMatrixE3.setValue( 3, 12 );
	cout<<"fibMatrixDef3.addVector( vecFibMatrixE3 );"<<endl;
	fibMatrixDef3.addVector( vecFibMatrixE3 );
	
	//test get compressed size
	//introduction + count dimensions + count vector elements variables + count vectors + area vectors + vectors + point
	uiCompressedSize = 17 + 4 + 2 * 5 + 9 + 2 * (2 + 7 + 7) + 2 * (3 + 8 + 6 + 7) + 5;
	if ( (unsigned int)(fibMatrixDef3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			fibMatrixDef3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixDef3Dom13Vec2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = fibMatrixDef3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char szFibMatrixDef3Dom13Vec2[] = { (char)0x2F, (char)0x00, (char)0x5B, (char)0x0C, (char)0x01, (char)0x02, (char)0x0A, (char)0x08, (char)0x06, (char)0x04, (char)0x0C, (char)0x0A, (char)0x02, (char)0x1C, (char)0x18, (char)0x02 };
	//   00010   000 1100 0   00 0111 0  0000 0001 0   000 0101 0   00 0011 0  0000 0010 0   000 0011 0  000 0100 0   000 0101 0  000 0001 0   0  0000 0010   00011  00010 1101 1 0000 0000 0010 1111 <-
	//->=0010 1111  0000 0000  0101 1011  0000 1100  0000 0001  0000 0010  0000 1010  0000 1000  0000 0110  0000 0100  0000 1100  0000 1010  0000 0010  0001 1100  0001 1000   0 0010 
	iReturn += compareBytsWithFile( szFileNameBuffer, szFibMatrixDef3Dom13Vec2, 16 );

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with five vectors"<<endl;
	
	cout<<"vecFibMatrixE3.setValue( 1, 3 );"<<endl;
	vecFibMatrixE3.setValue( 1, 3 );
	cout<<"vecFibMatrixE3.setValue( 2, 16 );"<<endl;
	vecFibMatrixE3.setValue( 2, 16 );
	cout<<"vecFibMatrixE3.setValue( 3, 32 );"<<endl;
	vecFibMatrixE3.setValue( 3, 32 );
	cout<<"fibMatrixDef3.addVector( vecFibMatrixE3 );"<<endl;
	fibMatrixDef3.addVector( vecFibMatrixE3 );

	cout<<"vecFibMatrixE3.setValue( 1, 4 );"<<endl;
	vecFibMatrixE3.setValue( 1, 4 );
	cout<<"vecFibMatrixE3.setValue( 2, 31 );"<<endl;
	vecFibMatrixE3.setValue( 2, 31 );
	cout<<"vecFibMatrixE3.setValue( 3, -1 );"<<endl;
	vecFibMatrixE3.setValue( 3, -1 );
	cout<<"fibMatrixDef3.addVector( vecFibMatrixE3 );"<<endl;
	fibMatrixDef3.addVector( vecFibMatrixE3 );

	cout<<"vecFibMatrixE3.setValue( 1, 5 );"<<endl;
	vecFibMatrixE3.setValue( 1, 5 );
	cout<<"vecFibMatrixE3.setValue( 2, 1 );"<<endl;
	vecFibMatrixE3.setValue( 2, 1 );
	cout<<"vecFibMatrixE3.setValue( 3, -64 );"<<endl;
	vecFibMatrixE3.setValue( 3, -64 );
	cout<<"fibMatrixDef3.addVector( vecFibMatrixE3 );"<<endl;
	fibMatrixDef3.addVector( vecFibMatrixE3 );

	//test get compressed size
	//introduction + count dimensions + count vector elements variables + count vectors + area vectors + vectors + point
	uiCompressedSize = 17 + 4 + 2 * 5 + 9 + 2 * (2 + 7 + 7) + 5 * (3 + 8 + 6 + 7) + 5;
	if ( (unsigned int)(fibMatrixDef3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			fibMatrixDef3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibMatrixDef3Dom13Vec5.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = fibMatrixDef3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char szFibMatrixDef3Dom13Vec5[] = { (char)0x2F, (char)0x00, (char)0x5B, (char)0x8C, (char)0x02, (char)0x02, (char)0x0A, (char)0x08, (char)0x06, (char)0x04, (char)0x0C, (char)0x0A, (char)0x02, (char)0x1C, (char)0x18, (char)0x06, (char)0x40, (char)0x40, (char)0x08, (char)0x7C, (char)0xFE, (char)0x0A, (char)0x04, (char)0x80, (char)0x02 };
	//   00010   100 0000 0   00 0001 0  0000 0101 0   111 1111 0   01 1111 0  0000 0100 0   010 0000 0   01 0000 0  0000 0011 0   000 1100 0   00 0111 0  0000 0001 0   000 0101 0   00 0011 0  0000 0010 0   000 0011 0  000 0100 0   000 0101 0  000 0001 0   0  0000 0101   00011  00010 1101 1 0000 0000 0010 1111 <-
	//->=0010 1111  0000 0000  0101 1011  1000 1100  0000 0010  0000 0010  0000 1010  0000 1000  0000 0110  0000 0100  0000 1100  0000 1010  0000 0010  0001 1100  0001 1000     0000 0110  0100 0000  0100 0000  0000 1000  0111 1100  1111 1110  0000 1010  0000 0100  1000 0000    0 0010 
	iReturn += compareBytsWithFile( szFileNameBuffer, szFibMatrixDef3Dom13Vec5, 25 );

	
	return iReturn;
}



/**
 * This method checks the domain number methods of the class.
 *
 * methods tested:
 * 	- unsignedIntFib getDomainNr() const;
 * 	- void setDomainNr( const unsignedLongFib uiInDomainNumber );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testDomainNr( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the domain number methods of cFibMatrix"<<endl;

	unsigned long ulCorrectDomainNr = 0;
	
	cFibMatrix fibMatrix( 1, 2 );
	const cFibMatrix * pFibMatrixConst = &fibMatrix;
	
	for ( unsigned long uiIteration = 0; uiIteration < MAX_RAND_TEST_SIZE; uiIteration++ ){
		
		//choos random new domain number
		ulCorrectDomainNr = rand() % MAX_RAND_TEST_SIZE;
		
		cout<<"fibMatrix.setDomainNr( "<<ulCorrectDomainNr<<" );"<<endl;
		fibMatrix.setDomainNr( ulCorrectDomainNr );
		
		//check the getDomainNr() methode from const cFibMatrix
		if ( fibMatrix.getDomainNr() == ulCorrectDomainNr ){
		
			cout<<"The domain number is correctly "<<ulCorrectDomainNr<<" . "<<endl;
		}else{
			cerr<<"Error: The domain number is "<<fibMatrix.getDomainNr()<<
				", but should be "<<ulCorrectDomainNr<<" . "<<endl;
			iReturn++;
		}
		//check the getDomainNr() methode from cFibMatrix
		if ( pFibMatrixConst->getDomainNr() != ulCorrectDomainNr ){
			cerr<<"Error: The domain number is "<<fibMatrix.getDomainNr()<<
				", but should be "<<ulCorrectDomainNr<<" (on const fibMatrix). "<<endl;
			iReturn++;
		}
	}

	return iReturn;
}



/**
 * This method checks the vector methods of the class.
 *
 * methods tested:
 * 	- unsignedIntFib getNumberOfMatrixDimensions() const;
 * 	- unsignedIntFib getNumberOfVectorElements() const;
 * 	- cVectorArea * getArea( const unsignedIntFib uiDimension=1 );
 * 	- cFibVariable * getDefinedVariable( const unsignedLongFib uiPosition );
 * 	- unsignedLongFib getNumberOfVectors() const;
 * 	- const vector< cVectorFibMatrix > getVectors();
 * 	- bool setVectors( const vector< cVectorFibMatrix > & vecMatrixs );
 * 	- cVectorFibMatrix * getVector( const unsignedLongFib uiPosition );
 * 	- bool setVector( const cVectorFibMatrix & vecMatrix, const unsignedLongFib uiPosition );
 * 	- bool addVector( const cVectorFibMatrix & vecMatrix, const unsignedLongFib uiPosition=0 );
 * 	- bool deleteVector( const unsignedLongFib uiPosition );
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
 * 
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testVectors( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the vector methods"<<endl;

	//controll data
	vector< cVectorFibMatrix > vecVectors;
	vector< cVectorArea > vecAreaVectors;
	
	vector< cFibVariable * > vecDefinedVariables;
	
	cout<<"cRoot root;"<<endl;
	cRoot root;
	
	root.setNumberOfInputVariables( 10 );
	vector< cFibVariable* > vecPossibleVariables;
	vecPossibleVariables.push_back( root.getInputVariable( 1 ) );
	vecPossibleVariables.push_back( root.getInputVariable( 2 ) );
	vecPossibleVariables.push_back( root.getInputVariable( 3 ) );
	vecPossibleVariables.push_back( root.getInputVariable( 4 ) );
	vecPossibleVariables.push_back( root.getInputVariable( 5 ) );
	vecPossibleVariables.push_back( root.getInputVariable( 6 ) );
	vecPossibleVariables.push_back( root.getInputVariable( 7 ) );
	vecPossibleVariables.push_back( root.getInputVariable( 8 ) );
	vecPossibleVariables.push_back( root.getInputVariable( 9 ) );
	vecPossibleVariables.push_back( root.getInputVariable( 10 ) );
	
	cout<<"cFibMatrix * pFibMatrix = new cFibMatrix( 1, 1, NULL, &root );"<<endl;
	cFibMatrix * pFibMatrix = new cFibMatrix( 1, 1, NULL, &root );
	vecDefinedVariables.push_back( pFibMatrix->getDefinedVariable( 1 ) );
	vecDefinedVariables.push_back( pFibMatrix->getDefinedVariable( 2 ) );
	const cFibMatrix * pFibMatrixConst = pFibMatrix;
	
	cFibMatrix dummyMatrix( 0, 0 );
	unsignedIntFib uiNumberOfDimensions = 1;
	vecAreaVectors.push_back( cVectorArea( &dummyMatrix ) );
	
	const unsigned long ulChangeFibMatrixEveryIteration = ( MAX_RAND_TEST_SIZE < 64 ) ?
		(MAX_RAND_TEST_SIZE / 8 + 4):(MAX_RAND_TEST_SIZE / (8 + log( MAX_RAND_TEST_SIZE ) ) + 4);
		
	const unsigned long ulChangeAllVectorsEveryItr = ulChangeFibMatrixEveryIteration / 4 + 2;
	
	cout<<"Changing the matrix element in average all iterations: "<<
		ulChangeFibMatrixEveryIteration<<endl;
	cout<<"Changing all matrix element vectors in average all iterations: "<<
		ulChangeAllVectorsEveryItr<<endl;

	for ( unsigned long uiIteration = 0; uiIteration < MAX_RAND_TEST_SIZE; uiIteration++ ){
		
		cout<<"ITERATION: "<<uiIteration<<endl;
		
		//choose if the cFibMatrix should change
		if ( rand() % ulChangeFibMatrixEveryIteration ){
			//change vectors
			
			if ( rand() % ulChangeAllVectorsEveryItr ){
				if ( rand() % 2 ){
					//change a vector
					if ( rand() % 2 ){
						//change area vector
						const unsigned int uiChangeVectorNumber =
							rand() % (uiNumberOfDimensions + 4);
						//check if position is correct
						const bool bCanChangeVector = ( 1 <= uiChangeVectorNumber ) &&
							( uiChangeVectorNumber <= vecAreaVectors.size() );
						cout<<"pFibMatrix->getArea( "<< uiChangeVectorNumber <<" );";
						cVectorArea * pVectorAreaMatrix = pFibMatrix->getArea( uiChangeVectorNumber );
						
						if ( bCanChangeVector == (pVectorAreaMatrix != NULL) ){
							cout<<"= "<<pVectorAreaMatrix<<endl;
						}else{//error
							cout<<endl;
							cerr<<"Error: Could"<<((pVectorAreaMatrix != NULL)?"":"n't")<<" get the vector on the position "<<
								uiChangeVectorNumber <<".(size="<< vecAreaVectors.size() <<")"<<endl;
							iReturn++;
							continue;
						}
						if ( pVectorAreaMatrix != NULL ){
							//vector was returned -> change a value
							vector< cVectorArea >::iterator itrInsertMatrixVector =
								vecAreaVectors.begin();
							
							for ( unsigned int uiActualMatrixVector = 1;
									( uiActualMatrixVector < uiChangeVectorNumber ) &&
									( itrInsertMatrixVector != vecAreaVectors.end() );
									uiActualMatrixVector++, itrInsertMatrixVector++ ){
								//nothing to do
							}

							const unsignedIntFib uiNumberOfElements =
								pVectorAreaMatrix->getNumberOfElements();
							
							const unsignedIntFib uiChoosenElement =
								1 + rand() % uiNumberOfElements;
							if ( rand() % 3 ){
								//set value
								const double dValueToSet = ( (rand() % ( 256L * 256L * 256L )) -
									128L * 256L * 256L );
								cout<<"pVectorAreaMatrix("<<pVectorAreaMatrix<<")->setValue( "<<
									uiChoosenElement<<", "<<dValueToSet<<" );"<<endl;
								pVectorAreaMatrix->setValue( uiChoosenElement, dValueToSet );
								if ( itrInsertMatrixVector != vecAreaVectors.end() ){
									itrInsertMatrixVector->setValue( uiChoosenElement, dValueToSet );
								}
							}else{//set variable
								const unsigned int uiVariableToMatrix =
									rand() % vecPossibleVariables.size();
								cout<<"pVectorAreaMatrix("<<pVectorAreaMatrix<<")->setValue( "<<
									uiChoosenElement<<", variable["<<uiVariableToMatrix<<"] );"<<endl;
								pVectorAreaMatrix->setVariable( 
									uiChoosenElement, vecPossibleVariables[ uiVariableToMatrix ] );
								if ( itrInsertMatrixVector != vecAreaVectors.end() ){
									itrInsertMatrixVector->setVariable(
										uiChoosenElement, vecPossibleVariables[ uiVariableToMatrix ] );
								}
							}
						}
					}else{//change vector with value to set
						const unsigned int uiChangeVectorNumber =
							rand() % (vecDefinedVariables.size() - uiNumberOfDimensions + 4);
						
						//check if position is correct
						const bool bCanChangeVector = ( 1 <= uiChangeVectorNumber ) &&
							( uiChangeVectorNumber <= vecVectors.size() );
						cout<<"pFibMatrix->getVector( "<< uiChangeVectorNumber <<" );";
						cVectorFibMatrix * pVectorMatrix = pFibMatrix->getVector( uiChangeVectorNumber );
						
						if ( bCanChangeVector == (pVectorMatrix != NULL) ){
							cout<<"= "<<pVectorMatrix<<endl;
						}else{//error
							cout<<endl;
							cerr<<"Error: Could"<<((pVectorMatrix != NULL)?"":"n't")<<" get the vector on the position "<<
								uiChangeVectorNumber <<".(size="<< vecVectors.size() <<")"<<endl;
							iReturn++;
							continue;
						}
						if ( pVectorMatrix != NULL ){
							//vector was returned -> change a value
							const unsignedIntFib uiNumberOfElements =
								pVectorMatrix->getNumberOfElements();
							if ( uiNumberOfElements != 0 ){
								//change a vector element
								vector< cVectorFibMatrix >::iterator itrInsertMatrixVector =
									vecVectors.begin();
								
								for ( unsigned int uiActualMatrixVector = 1;
										( uiActualMatrixVector < uiChangeVectorNumber ) &&
										( itrInsertMatrixVector != vecVectors.end() );
										uiActualMatrixVector++, itrInsertMatrixVector++ ){
									//nothing to do
								}

								const unsignedIntFib uiChoosenElement =
									1 + rand() % uiNumberOfElements;
								if ( rand() % 3 ){
									//set value
									const double dValueToSet = ( ((double)( rand() % ( 256LL * 256LL * 256LL * 256LL ) -
										128LL * 256LL * 256LL * 256LL )) / ( 256.0 * 256.0 ) );
									cout<<"pVectorMatrix("<<pVectorMatrix<<")->setValue( "<<
										uiChoosenElement<<", "<<dValueToSet<<" );"<<endl;
									pVectorMatrix->setValue( uiChoosenElement, dValueToSet );
									if ( itrInsertMatrixVector != vecVectors.end() ){
										itrInsertMatrixVector->setValue( uiChoosenElement, dValueToSet );
									}
								}else{//set variable
									const unsigned int uiVariableToMatrix =
										rand() % vecPossibleVariables.size();
									cout<<"pVectorMatrix("<<pVectorMatrix<<")->setValue( "<<
										uiChoosenElement<<", variable["<<uiVariableToMatrix<<"] );"<<endl;
									pVectorMatrix->setVariable( 
										uiChoosenElement, vecPossibleVariables[ uiVariableToMatrix ] );
									if ( itrInsertMatrixVector != vecVectors.end() ){
										itrInsertMatrixVector->setVariable(
											uiChoosenElement, vecPossibleVariables[ uiVariableToMatrix ] );
									}
								}
							}//else the vector has no element to change -> skip changing
						}//end if vector was given back
					}//end if change area vector or vector
				}else{
					//choos random vector with values to set to change
					const unsigned int uiNumberOfVectorElements =
						vecDefinedVariables.size() - uiNumberOfDimensions;
					const unsigned int uiChangeVectorNumber =
						rand() % (uiNumberOfVectorElements + 4);
					
					//choos if delete or add a vector with values to set
					if ( rand() % 3 ){
						//generate vector to set
						cVectorFibMatrix * pVectorToMatrix = NULL;
						bool bVectorOk = true;
						if ( rand() % 8 ){
							//vector without error
							if ( rand() % 2 ){
								cout<<"pVectorToMatrix = new cVectorFibMatrix( *pFibMatrix )={";
								pVectorToMatrix = new cVectorFibMatrix( *pFibMatrix );
							}else{
								cout<<"pVectorToMatrix = new cVectorFibMatrix( "<<uiNumberOfVectorElements<<" )={";
								pVectorToMatrix = new cVectorFibMatrix( uiNumberOfVectorElements );
							}
						}else{//vector with error
							const unsigned int uiVectorElements = rand() % ( rand() % 256 + 1 );
							pVectorToMatrix = new cVectorFibMatrix( uiVectorElements );
							bVectorOk = ( uiVectorElements == uiNumberOfVectorElements );
							cout<<"pVectorToMatrix = new cVectorFibMatrix( "<<uiVectorElements<<
								"="<<(bVectorOk?"OK":"not Ok")<<" )={";
						}
						//set the vector elements to values
						const unsigned int uiVectorElements = pVectorToMatrix->getNumberOfElements();
						for ( unsigned int uiActualElement = 1;
								uiActualElement <= uiVectorElements; uiActualElement++ ){
							
							if ( rand() % 3 ){
								//set value
								const double dValueToSet = ( ((double)( rand() % ( 256LL * 256LL * 256LL * 256LL ) -
									128LL * 256LL * 256LL * 256LL )) / ( 256.0 * 256.0 ) );
								pVectorToMatrix->setValue( uiActualElement, dValueToSet );
								cout<<dValueToSet<<";";
							}else{//set variable
								const unsigned int uiVariableToMatrix =
									rand() % vecPossibleVariables.size();
								pVectorToMatrix->setVariable( uiActualElement,
									vecPossibleVariables[ uiVariableToMatrix ] );
								cout<<"variable["<<uiVariableToMatrix<<"];";
							}
						}
						cout<<"}"<<endl;
						
						//choose if add or set vector
						if ( rand() % 2 ){
							//add a vector with values to set
							cout<<"pFibMatrix->addVector( vecFibMatrix , "<< uiChangeVectorNumber <<" );";
							const bool bVectorAdded = pFibMatrix->addVector( *pVectorToMatrix, uiChangeVectorNumber );
							if ( bVectorAdded == bVectorOk ){
								cout<<"Ok "<<(bVectorAdded?"added":"not added")<<endl;
							}else{//error
								cout<<endl;
								cerr<<"Error: Could"<<(bVectorAdded?"":"n't")<<" add the vector on the position "<<
									uiChangeVectorNumber <<".(size="<< vecVectors.size() <<")"<<endl;
								iReturn++;
								continue;
							}
							if ( bVectorAdded ){
								//vector was added
								if ( ( uiChangeVectorNumber != 0 ) &&
										( uiChangeVectorNumber < (vecVectors.size() + 1) ) ){
									//insert the new vector with values to set in the control vector
									vector< cVectorFibMatrix >::iterator itrInsertMatrixVector =
										vecVectors.begin();
									
									for ( unsigned int uiActualMatrixVector = 1;
											uiActualMatrixVector < uiChangeVectorNumber;
											uiActualMatrixVector++, itrInsertMatrixVector++ ){
										//nothing to do
									}
									vecVectors.insert( itrInsertMatrixVector, *pVectorToMatrix );
								}else{//insert on back
									vecVectors.push_back( *pVectorToMatrix );
								}
							}
						}else{//set a vector with values to set
							//check if position is correct
							const bool bPositionOk = ( 1 <= uiChangeVectorNumber ) &&
								( uiChangeVectorNumber <= vecVectors.size() );
							const bool bCanAddVector = bVectorOk && bPositionOk;
							cout<<"pFibMatrix->setVector( vecFibMatrix , "<< uiChangeVectorNumber <<" );";
							const bool bVectorMatrix = pFibMatrix->setVector( *pVectorToMatrix, uiChangeVectorNumber );
							
							if ( bVectorMatrix == bCanAddVector ){
								cout<<"Ok "<<(bVectorMatrix?"set":"not set")<<endl;
							}else{//error
								cout<<endl;
								cerr<<"Error: Could"<<(bVectorMatrix?"":"n't")<<" insert the vector on the position "<<
									uiChangeVectorNumber <<".(size="<< vecVectors.size() <<")"<<endl;
								iReturn++;
								continue;
							}
							if ( bVectorMatrix ){
								//vector was set
								if ( bPositionOk ){
									//insert the new vector with values to set in the control vector
									vector< cVectorFibMatrix >::iterator itrInsertMatrixVector =
										vecVectors.begin();
									
									for ( unsigned int uiActualMatrixVector = 1;
											uiActualMatrixVector < uiChangeVectorNumber;
											uiActualMatrixVector++, itrInsertMatrixVector++ ){
										//nothing to do
									}
									*itrInsertMatrixVector = *pVectorToMatrix;
								}
							}
						}
						delete pVectorToMatrix;
					}else{//delete a vector with values to set
						const bool bPositionOk = ( 1 <= uiChangeVectorNumber ) &&
							( uiChangeVectorNumber <= vecVectors.size() );
						
						cout<<"pFibMatrix->deleteVector( "<< uiChangeVectorNumber <<" );";
						const bool bVectorDeleted = pFibMatrix->deleteVector( uiChangeVectorNumber );
						if ( bVectorDeleted == bPositionOk ){
							cout<<"Ok "<<(bVectorDeleted?"deleted":"not deleted")<<endl;
						}else{//error
							cout<<endl;
							cerr<<"Error: Could"<<(bVectorDeleted?"":"n't")<<" delete the vector on the position "<<
								uiChangeVectorNumber <<".(size="<< vecVectors.size() <<")"<<endl;
							iReturn++;
							continue;
						}

						if ( bPositionOk ){
							//insert the new vector with values to set in the controlllist
							vector< cVectorFibMatrix >::iterator itrDeletedSubfibMatrix =
								vecVectors.begin();
							
							for ( unsigned int uiActualMatrixVector = 1;
									uiActualMatrixVector < uiChangeVectorNumber;
									uiActualMatrixVector++, itrDeletedSubfibMatrix++ ){
								//nothing to do
							}
							vecVectors.erase( itrDeletedSubfibMatrix );
						}
					}
				}//change existing vector or overwrite it
				
			}else{//change all vectors: setVectors()
				const bool bWithError = (rand() % 8 == 0);
				unsigned int uiNumberVectorsToMatrix = rand() % (4 + rand() % (4 +
					rand() % 256 ) );
				bool bVectorsOk = true;
				const unsigned int uiNumberOfVectorElements =
					vecDefinedVariables.size() - uiNumberOfDimensions;
				vector< cVectorFibMatrix > vecToMatrixVectors;
				
				cout<<"Creating "<<uiNumberVectorsToMatrix<<" vectors "<<
					(bWithError?"with errors possible :":":")<<endl;
				for ( unsigned int uiActualVector = 0;
						uiActualVector < uiNumberVectorsToMatrix; uiActualVector++ ){
					
					if ( ( ! bWithError ) || (rand() % 8) ){
						//vector without error
						if ( rand() % 2 ){
							cout<<"   vecToMatrixVectors["<<uiActualVector<<
								"] = new cVectorFibMatrix( *pFibMatrix )={";
							vecToMatrixVectors.push_back( cVectorFibMatrix( *pFibMatrix ) );
						}else{
							cout<<"   vecToMatrixVectors["<<uiActualVector<<
								"] = new cVectorFibMatrix( "<<uiNumberOfVectorElements<<" )={";
							vecToMatrixVectors.push_back( cVectorFibMatrix( uiNumberOfVectorElements ) );
						}
					}else{//vector with error
						const unsigned int uiVectorElements = rand() % ( rand() % 256 + 1 );
						vecToMatrixVectors.push_back( cVectorFibMatrix( uiVectorElements ) );
						bVectorsOk &= ( uiVectorElements == uiNumberOfVectorElements );
						cout<<"   vecToMatrixVectors["<<uiActualVector<<
							"] = new cVectorFibMatrix( "<<uiVectorElements<<
							"="<<(bVectorsOk?"OK":"not Ok")<<" )={";
					}
					//set the vector elements to values
					cVectorFibMatrix * pVectorToMatrix = &(vecToMatrixVectors.back());
					const unsigned int uiVectorElements = pVectorToMatrix->getNumberOfElements();
					for ( unsigned int uiActualElement = 1;
							uiActualElement <= uiVectorElements; uiActualElement++ ){
						
						if ( rand() % 3 ){
							//set value
							const double dValueToSet = ( ((double)( rand() % ( 256LL * 256LL * 256LL * 256LL ) -
								128LL * 256LL * 256LL * 256LL )) / ( 256.0 * 256.0 ) );
							pVectorToMatrix->setValue( uiActualElement, dValueToSet );
							cout<<dValueToSet<<";";
						}else{//set variable
							const unsigned int uiVariableToMatrix =
								rand() % vecPossibleVariables.size();
							pVectorToMatrix->setVariable( uiActualElement,
								vecPossibleVariables[ uiVariableToMatrix ] );
							cout<<"variable["<<uiVariableToMatrix<<"];";
						}
					}
					cout<<"}"<<endl;
				}
				const bool bVectorsMatrix = pFibMatrix->setVectors( vecToMatrixVectors );
				
				if ( bVectorsMatrix == bVectorsOk ){
					cout<<"Ok "<<(bVectorsMatrix?"set":"not set")<<endl;
				}else{//error
					cout<<endl;
					cerr<<"Error: Could"<<(bVectorsMatrix?"":"n't")<<" set the "<<
						"vectors. (size="<< vecVectors.size() <<")"<<endl;
					iReturn++;
					continue;
				}
				if ( bVectorsMatrix ){
					//vector was set
					vecVectors = vecToMatrixVectors;
				}
			}
		}else{//change cFibMatrix
			//delete old data
			cout<<endl<<endl;
			delete pFibMatrix;
			vecVectors.clear();
			vecDefinedVariables.clear();
			vecAreaVectors.clear();
			//create new data
			const unsigned int uiDimensionVariables = rand() % (3 + rand() %
				(1 + rand() % ( 1 + rand() % 64 )));
			const unsigned int uiVectorElements = rand() % (3 + rand() %
				(1 + rand() % ( 1 + rand() % 64 )));
			cout<<"pFibMatrix = new cFibMatrix( "<<uiDimensionVariables<<
				", "<<uiVectorElements<<", NULL, &root );"<<endl;
			pFibMatrix = new cFibMatrix( uiDimensionVariables, uiVectorElements, NULL, &root );
			pFibMatrixConst = pFibMatrix;
			
			if ( uiDimensionVariables != 0 ){
				//add all defined variables
				uiNumberOfDimensions = uiDimensionVariables;
			}else{//minimum one dimension variable
				uiNumberOfDimensions = 1;
			}
			//add all defined variables
			const unsigned int uiDefinedVariables =
				uiNumberOfDimensions + uiVectorElements;
			for ( unsigned int uiActualDefVariable = 1;
					uiActualDefVariable <= uiDefinedVariables; uiActualDefVariable++ ){
				
				vecDefinedVariables.push_back(
					pFibMatrix->getDefinedVariable( uiActualDefVariable ) );
			}
			//add empty area vectors
			for ( unsigned int uiActualDimension = 1;
					uiActualDimension <= uiNumberOfDimensions; uiActualDimension++ ){
				
				vecAreaVectors.push_back( cVectorArea( &dummyMatrix ) );
			}
		}
		
		//check the vector with values to sets
		//check getNumberOfVectors()
		if ( pFibMatrixConst->getNumberOfVectors() != vecVectors.size() ){
			cerr<<"Error: The pFibMatrix has "<< pFibMatrixConst->getNumberOfVectors() <<
				" vector with values to sets, but should have "<< vecVectors.size() <<endl;
			iReturn++;
		}
		//check getVectors()
		if ( pFibMatrix->getVectors() != vecVectors ){
			cerr<<"Error: The pFibMatrix returns the wrong vectors (getVectors()). "<<
				"(number of vectors "<<vecVectors.size()<<")"<<endl;
			iReturn++;
		}
		//check getVector()
		set<cFibVariable*> setCorrectUsedVariables;
		
		//check getArea()
		vector< cVectorArea >::iterator itrMatrixArea = vecAreaVectors.begin();
		for ( unsigned int uiSubfibMatrix = 1;
				uiSubfibMatrix <= pFibMatrixConst->getNumberOfMatrixDimensions();
				uiSubfibMatrix++ ){
				
			cVectorArea * pSubFibMatrix = pFibMatrix->getArea( uiSubfibMatrix );
			if ( pSubFibMatrix == NULL ){
				cerr<<"Error: Ther is no "<<uiSubfibMatrix <<"'th area vector. (size="<<
					vecAreaVectors.size() <<")"<<endl;
				iReturn++;
			}else{
				//check the area vector bounds
				if ( (*itrMatrixArea) != (*pSubFibMatrix) ){
					cerr<<"Error: The "<<uiSubfibMatrix <<"'th area vector is wrong."<<endl;
					cerr<<"pFibMatrix->getArea( "<<uiSubfibMatrix<<" ) :"<<endl;
					pSubFibMatrix->storeXml( cerr );
					cerr<<"correct vector :"<<endl;
					itrMatrixArea->storeXml( cerr );
					iReturn++;
				}
				//check the defining Fib element of the area vector
				if ( pSubFibMatrix->getDefiningFibElement() != pFibMatrixConst ){
					cerr<<"Error: The "<<uiSubfibMatrix <<"'th area vector has the wrong defining element."<<endl;
					cerr<<"   correct defining element: "<< pFibMatrixConst <<
						" given defining element: "<< pSubFibMatrix->getDefiningFibElement() <<endl;
					iReturn++;
				}
				//evalue used variables vor later
				set<cFibVariable*> setActualUsedVariables =
					pSubFibMatrix->getUsedVariables();
				setCorrectUsedVariables.insert( setActualUsedVariables.begin(),
					setActualUsedVariables.end() );
			}
			if ( itrMatrixArea != vecAreaVectors.end() ){
				itrMatrixArea++;
			}else{
				cerr<<"Error: Ther are more area vectors in the pFibMatrix than ther should be. (size="<<
					vecAreaVectors.size() <<")"<<endl;
				iReturn++;
			}
		}
		//check out of bounderie area vectors
		cVectorArea * pMatrixAreaVector = pFibMatrix->getArea( 0 );
		if ( pMatrixAreaVector != NULL ){
			cerr<<"Error: Ther is a "<<0 <<"'th area vector. (size="<<
				vecVectors.size() <<")"<<endl;
			iReturn++;
		}
		pMatrixAreaVector = pFibMatrix->getArea( vecAreaVectors.size() + 1 );
		if ( pMatrixAreaVector != NULL ){
			cerr<<"Error: Ther is a "<< vecAreaVectors.size() + 1 <<"'th area vector. (size="<<
				vecVectors.size() <<")"<<endl;
			iReturn++;
		}
		
		//check getVector()
		vector< cVectorFibMatrix >::iterator itrMatrixVector = vecVectors.begin();
		for ( unsigned int uiSubfibMatrix = 1;
				uiSubfibMatrix <= pFibMatrixConst->getNumberOfVectors();
				uiSubfibMatrix++ ){
				
			cVectorFibMatrix * pSubFibMatrix = pFibMatrix->getVector( uiSubfibMatrix );
			if ( pSubFibMatrix == NULL ){
				cerr<<"Error: Ther is no "<<uiSubfibMatrix <<"'th vector with values to set. (size="<<
					vecVectors.size() <<")"<<endl;
				iReturn++;
			}else{
				//check the vector with values to set bounds
				if ( (*itrMatrixVector) != (*pSubFibMatrix) ){
					cerr<<"Error: The "<<uiSubfibMatrix <<"'th vector with values to set is wrong."<<endl;
					cerr<<"pFibMatrix->getVector( "<<uiSubfibMatrix<<" ) :"<<endl;
					pSubFibMatrix->storeXml( cerr );
					cerr<<"correct vector :"<<endl;
					itrMatrixVector->storeXml( cerr );
					iReturn++;
				}
				//check the defining Fib element of the vector with values to set
				if ( pSubFibMatrix->getDefiningFibElement() != pFibMatrixConst ){
					cerr<<"Error: The "<<uiSubfibMatrix <<"'th vector with values to set has the wrong defining element."<<endl;
					cerr<<"   correct defining element: "<< pFibMatrixConst <<
						" given defining element: "<< pSubFibMatrix->getDefiningFibElement() <<endl;
					iReturn++;
				}
				//evalue used variables vor later
				set<cFibVariable*> setActualUsedVariables =
					pSubFibMatrix->getUsedVariables();
				setCorrectUsedVariables.insert( setActualUsedVariables.begin(),
					setActualUsedVariables.end() );
			}
			if ( itrMatrixVector != vecVectors.end() ){
				itrMatrixVector++;
			}else{
				cerr<<"Error: Ther are more vector with values to sets in the pFibMatrix than ther should be. (size="<<
					vecVectors.size() <<")"<<endl;
				iReturn++;
			}
		}
		//check out of bounderie vector with values to sets
		cVectorFibMatrix * pMatrixVector = pFibMatrix->getVector( 0 );
		if ( pMatrixVector != NULL ){
			cerr<<"Error: Ther is a "<<0 <<"'th vector with values to set. (size="<<
				vecVectors.size() <<")"<<endl;
			iReturn++;
		}
		pMatrixVector = pFibMatrix->getVector( vecVectors.size() + 1 );
		if ( pMatrixVector != NULL ){
			cerr<<"Error: Ther is a "<< vecVectors.size() + 1 <<"'th vector with values to set. (size="<<
				vecVectors.size() <<")"<<endl;
			iReturn++;
		}
		//check getDefinedVariable(), isDefinedVariable() and getDefinedVariables()
		const list<cFibVariable*> liDefinedVariables =
			pFibMatrix->getDefinedVariables( ED_POSITION );
		//check getNumberOfVectorElements()
		if ( ( pFibMatrixConst->getNumberOfVectorElements() +
				uiNumberOfDimensions ) != liDefinedVariables.size() ){
			cerr<<"Error: The pFibMatrix has "<< pFibMatrixConst->getNumberOfVectorElements() + uiNumberOfDimensions<<
				" defined variables, but by getDefinedVariables() are given back "<<
				liDefinedVariables.size() <<endl;
			iReturn++;
		}
		
		unsignedLongFib uiPosition = 1;
		list<cFibVariable*>::const_iterator itrLiDefVar = liDefinedVariables.begin();
		for ( vector< cFibVariable * >::iterator
				itrDefVariable = vecDefinedVariables.begin();
				itrDefVariable != vecDefinedVariables.end();
				itrDefVariable++, uiPosition++ ){
			
			cFibVariable * pFibVariable = pFibMatrix->getDefinedVariable( uiPosition );
			
			if ( pFibVariable != (*itrDefVariable) ){
				cerr<<"Error: The "<<uiPosition<<"'th defined variables is "<<
					pFibVariable<<", but should be "<<(*itrDefVariable)<<" ."<<endl;
				iReturn++;
			}
			
			if ( ! pFibMatrix->isDefinedVariable( (*itrDefVariable) , ED_POSITION ) ){
				cerr<<"Error: The "<<uiPosition<<"'th defined variable ("<<
					(*itrDefVariable)<<") is not recognised by isDefinedVariable( "<<
					(*itrDefVariable)<<", ED_POSITION )  ."<<endl;
				iReturn++;
			}
			if ( pFibVariable != (*itrLiDefVar) ){
				cerr<<"Error: The "<<uiPosition<<"'th defined variables is "<<
					pFibVariable<<", but getDefinedVariables() gave back "<<
					(*itrLiDefVar)<<" ."<<endl;
				iReturn++;
			}
			if ( itrLiDefVar != liDefinedVariables.end() ){
				
				itrLiDefVar++;
			}
		}
		//check getNumberOfMatrixDimensions()
		if ( pFibMatrixConst->getNumberOfMatrixDimensions() != uiNumberOfDimensions ){
			cerr<<"Error: The pFibMatrix has "<< pFibMatrixConst->getNumberOfMatrixDimensions() <<
				" defined variables, but should have "<< uiNumberOfDimensions <<endl;
			iReturn++;
		}
		//check getNumberOfVectorElements()
		if ( pFibMatrixConst->getNumberOfVectorElements() != (
				vecDefinedVariables.size() - uiNumberOfDimensions) ){
			cerr<<"Error: The pFibMatrix has "<< pFibMatrixConst->getNumberOfVectorElements() <<
				" defined variables, but should have "<< (
				vecDefinedVariables.size() - uiNumberOfDimensions)<<endl;
			iReturn++;
		}
		//check out of bounderie vector with values to sets
		cFibVariable * pDefVariable = pFibMatrix->getDefinedVariable( 0 );
		if ( pDefVariable != NULL ){
			cerr<<"Error: Ther is a "<<0 <<"'th defined variable. (size="<<
				vecDefinedVariables.size() <<")"<<endl;
			iReturn++;
		}
		pDefVariable = pFibMatrix->getDefinedVariable( vecDefinedVariables.size() + 1 );
		if ( pDefVariable != NULL ){
			cerr<<"Error: Ther is a "<< (vecDefinedVariables.size() + 1) <<"'th defined variable. (size="<<
				vecDefinedVariables.size() <<")"<<endl;
			iReturn++;
		}
		
		/*check isDefinedVariable( ED_POSITION ) on variables not defined on
		the position ( variables in vecPossibleVariables )*/
		for ( vector< cFibVariable * >::iterator
				itrDefVariable = vecPossibleVariables.begin();
				itrDefVariable != vecPossibleVariables.end();
				itrDefVariable++ ){
			
			if ( pFibMatrix->isDefinedVariable( (*itrDefVariable) , ED_POSITION ) ){
				cerr<<"Error: The variable ("<<(*itrDefVariable)<<") is given back by isDefinedVariable( "<<
					(*itrDefVariable)<<", ED_POSITION ) as a defined variable, but shouldn't ."<<endl;
				iReturn++;
			}
		}
		
		//check getUsedVariables( ED_POSITION )
		const set<cFibVariable*> setUsedVariables =
			pFibMatrix->getUsedVariables( ED_POSITION );
		if ( setCorrectUsedVariables != setUsedVariables ){
			cerr<<"Error: The used variables given back are not correct."<<
				"(given back "<<setUsedVariables.size()<<
				", correct "<<setCorrectUsedVariables.size()<<")"<<endl;
			iReturn++;
		}
		//check isUsedVariable( ED_POSITION )
		for ( set<cFibVariable*>::iterator
				itrUsedVariable = setCorrectUsedVariables.begin();
				itrUsedVariable != setCorrectUsedVariables.end();
				itrUsedVariable++ ){
			
			if ( ! pFibMatrix->isUsedVariable( (*itrUsedVariable) , ED_POSITION ) ){
				cerr<<"Error: The variable ("<<(*itrUsedVariable)<<
					") is evalued as not used by isUsedVariable( "<<
					(*itrUsedVariable)<<", ED_POSITION ), but should be used ."<<endl;
				iReturn++;
			}
		}
		//check isUsedVariable( ED_POSITION ) on not used (/defined) variables
		for ( vector< cFibVariable * >::iterator
				itrDefVariable = vecDefinedVariables.begin();
				itrDefVariable != vecDefinedVariables.end(); itrDefVariable++ ){
			
			if ( pFibMatrix->isUsedVariable( (*itrDefVariable) , ED_POSITION ) ){
				cerr<<"Error: The defined variable ("<<(*itrDefVariable)<<
					") is evalued as used by isUsedVariable( "<<
					(*itrDefVariable)<<", ED_POSITION ), but shouldn't ."<<endl;
				iReturn++;
			}
		}
		
	}

	delete pFibMatrix;
	
	return iReturn;
}



/**
 * This method tests the variable methods of the cFibMatrix class.
 *
 * methods tested:
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testVariable( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the variable methods"<<endl;
	
	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	cout<<"rootEmpty1.setNumberOfInputVariables( 10 );"<<endl;
	rootEmpty1.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 = rootEmpty1.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootEmpty1.getInputVariable( 1 );
	cout<<"pVariable2 = rootEmpty1.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = rootEmpty1.getInputVariable( 2 );
	cout<<"pVariable3 = rootEmpty1.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = rootEmpty1.getInputVariable( 3 );
	cout<<"pVariable4 = rootEmpty1.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable4 = rootEmpty1.getInputVariable( 4 );
	
	cout<<"cFibMatrix fibMatrix1( 1, 2 );"<<endl;
	cFibMatrix fibMatrix1( 1, 2 );
	
	cout<<"cVectorFibMatrix vecFibMatrix1( fibMatrix1 );"<<endl;
	cVectorFibMatrix vecFibMatrix1( fibMatrix1 );
	cout<<"vecFibMatrix1.setValue( 1, 4);"<<endl;
	vecFibMatrix1.setValue( 1, 4);
	cout<<"vecFibMatrix1.setValue( 2, 7);"<<endl;
	vecFibMatrix1.setValue( 2, 7);
	cout<<"fibMatrix1.addVector( vecFibMatrix1 );"<<endl;
	fibMatrix1.addVector( vecFibMatrix1 );
	
	cout<<"cVectorFibMatrix vecFibMatrix2( fibMatrix1 );"<<endl;
	cVectorFibMatrix vecFibMatrix2( fibMatrix1 );
	cout<<"vecFibMatrix2.setValue( 1, 2);"<<endl;
	vecFibMatrix2.setValue( 1, 2);
	cout<<"fibMatrix1.addVector( vecFibMatrix2 );"<<endl;
	fibMatrix1.addVector( vecFibMatrix2 );

	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrix1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! fibMatrix1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the matrix element. "<<endl;
		iReturn++;
	}
	set<cFibVariable*> setCorrectUsedVariables;
	
	//check getUsedVariables()
	cout<<"setUsedVariables = fibMatrix1.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = fibMatrix1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"fibMatrix1.getVector( 2 )->setVariable( 1, pVariable1 );"<<endl;
	fibMatrix1.getVector( 2 )->setVariable( 1, pVariable1 );
	setCorrectUsedVariables.insert( pVariable1 );

	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrix1.isUsedVariable( pVariable1 )"<<endl;
	if ( fibMatrix1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the matrix element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibMatrix1.getUsedVariables(); "<<endl;
	setUsedVariables = fibMatrix1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"fibMatrix1.getVector( 1 )->setVariable( 1, pVariable2 );"<<endl;
	fibMatrix1.getVector( 1 )->setVariable( 1, pVariable2 );
	setCorrectUsedVariables.insert( pVariable2 );

	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrix1.isUsedVariable( pVariable2 )"<<endl;
	if ( fibMatrix1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the matrix element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibMatrix1.getUsedVariables(); "<<endl;
	setUsedVariables = fibMatrix1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"fibMatrix1.getVector( 1 )->setVariable( 2, pVariable4 );"<<endl;
	fibMatrix1.getVector( 1 )->setVariable( 2, pVariable4 );
	setCorrectUsedVariables.insert( pVariable4 );

	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrix1.isUsedVariable( pVariable4 )"<<endl;
	if ( fibMatrix1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable4 is correctly used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is not used in the matrix element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibMatrix1.getUsedVariables(); "<<endl;
	setUsedVariables = fibMatrix1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"fibMatrix1.getVector( 1 )->setVariable( 2, pVariable1 );"<<endl;
	fibMatrix1.getVector( 1 )->setVariable( 2, pVariable1 );
	setCorrectUsedVariables.erase( pVariable4 );
	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrix1.isUsedVariable( pVariable1 )"<<endl;
	if ( fibMatrix1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the matrix element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibMatrix1.getUsedVariables(); "<<endl;
	setUsedVariables = fibMatrix1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"fibMatrix1.replaceVariable( pVariable2, pVariable3 );"<<endl;
	bool bVariableReplaced = fibMatrix1.replaceVariable( pVariable2, pVariable3 );
	setCorrectUsedVariables.erase( pVariable2 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrix1.isUsedVariable( pVariable2 )"<<endl;
	if ( ! fibMatrix1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the matrix element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrix1.isUsedVariable( pVariable3 )"<<endl;
	if ( fibMatrix1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the matrix element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibMatrix1.getUsedVariables(); "<<endl;
	setUsedVariables = fibMatrix1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"Try replacing non existing variable pVariable2:"<<endl;
	cout<<"fibMatrix1.replaceVariable( pVariable2, pVariable4 );"<<endl;
	bVariableReplaced = fibMatrix1.replaceVariable( pVariable2, pVariable4 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibMatrix1.getUsedVariables(); "<<endl;
	setUsedVariables = fibMatrix1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrix1.isUsedVariable( pVariable2 )"<<endl;
	if ( ! fibMatrix1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the matrix element. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrix1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! fibMatrix1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable4 is correctly not used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is used in the matrix element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrix1.isUsedVariable( pVariable3 )"<<endl;
	if ( fibMatrix1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the matrix element. "<<endl;
		iReturn++;
	}

	cout<<"fibMatrix1.replaceVariable( pVariable1, pVariable3 );"<<endl;
	bVariableReplaced = fibMatrix1.replaceVariable( pVariable1, pVariable3 );
	setCorrectUsedVariables.erase( pVariable1 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrix1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! fibMatrix1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the matrix element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrix1.isUsedVariable( pVariable3 )"<<endl;
	if ( fibMatrix1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the matrix element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibMatrix1.getUsedVariables(); "<<endl;
	setUsedVariables = fibMatrix1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing variable methods on a fibMatrix with a containing point"<<endl;

	cout<<"cVectorPosition vecPositionE3( 3 );"<<endl;
	cVectorPosition vecPositionE3( 3 );

	cout<<"cPoint point1( &vecPositionE3 );"<<endl;
	cPoint point1( &vecPositionE3 );
	cout<<"cFibMatrix fibMatrixPoint( 3, 2, &point1 );"<<endl;
	cFibMatrix fibMatrixPoint( 3, 2, &point1 );
	cout<<"fibMatrixPoint.addVector( vecFibMatrix1 );"<<endl;
	fibMatrixPoint.addVector( vecFibMatrix1 );

	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrixPoint.isUsedVariable( pVariable1 )"<<endl;
	if ( ! fibMatrixPoint.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the matrix element. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.clear();
	
	//check getUsedVariables()
	cout<<"setUsedVariables = fibMatrixPoint.getUsedVariables(); "<<endl;
	setUsedVariables = fibMatrixPoint.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"point1.getPosition()->setVariable( 3, pVariable1 );"<<endl;
	point1.getPosition()->setVariable( 3, pVariable1 );

	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrixPoint.isUsedVariable( pVariable1 )"<<endl;
	if ( ! fibMatrixPoint.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the matrix element. "<<endl;
		iReturn++;
	}
	cout<<"point1.isUsedVariable( pVariable1 )"<<endl;
	if ( point1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the matrix element. "<<endl;
		iReturn++;
	}
	cout<<"fibMatrixPoint.isUsedVariable( pVariable1, ED_BELOW_EQUAL )"<<endl;
	if ( fibMatrixPoint.isUsedVariable( pVariable1, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable1 is correctly used ED_BELOW_EQUAL the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used ED_BELOW_EQUAL the matrix element. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = fibMatrixPoint.getUsedVariables(); "<<endl;
	setUsedVariables = fibMatrixPoint.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.insert( pVariable1 );
	//check getUsedVariables()
	cout<<"setUsedVariables = fibMatrixPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = fibMatrixPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back for ED_BELOW_EQUAL. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong for ED_BELOW_EQUAL. "<<endl;
		iReturn++;
	}

	cout<<"point1.getPosition()->setVariable( 1, pVariable2 );"<<endl;
	point1.getPosition()->setVariable( 1, pVariable2 );
	
	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrixPoint.isUsedVariable( pVariable2 )"<<endl;
	if ( ! fibMatrixPoint.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the matrix element. "<<endl;
		iReturn++;
	}
	cout<<"point1.isUsedVariable( pVariable2 )"<<endl;
	if ( point1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the matrix element. "<<endl;
		iReturn++;
	}
	cout<<"fibMatrixPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( fibMatrixPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly used ED_BELOW_EQUAL the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used ED_BELOW_EQUAL the matrix element. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = fibMatrixPoint.getUsedVariables(); "<<endl;
	setUsedVariables = fibMatrixPoint.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.insert( pVariable2 );
	//check getUsedVariables()
	cout<<"setUsedVariables = fibMatrixPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = fibMatrixPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back for ED_BELOW_EQUAL. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong for ED_BELOW_EQUAL. "<<endl;
		iReturn++;
	}
	
	cout<<"fibMatrixPoint.getArea( 1 )->setVariable( 2, pVariable2 );"<<endl;
	fibMatrixPoint.getArea( 1 )->setVariable( 2, pVariable2 );
	cout<<"fibMatrixPoint.getArea( 3 )->setVariable( 1, pVariable2 );"<<endl;
	fibMatrixPoint.getArea( 3 )->setVariable( 1, pVariable2 );

	cout<<"fibMatrixPoint.replaceVariable( pVariable2, pVariable3 );"<<endl;
	bVariableReplaced = fibMatrixPoint.replaceVariable( pVariable2, pVariable3 );
	setCorrectUsedVariables.erase( pVariable2 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrixPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( ! fibMatrixPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly not used ED_BELOW_EQUAL the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used ED_BELOW_EQUAL the matrix element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibMatrix
	cout<<"fibMatrixPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL )"<<endl;
	if ( fibMatrixPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_BELOW_EQUAL the matrix element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_BELOW_EQUAL the matrix element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibMatrixPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = fibMatrixPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	return iReturn;
}





