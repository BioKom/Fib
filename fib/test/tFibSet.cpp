/**
 * @file tFibSet
 * file name: tFibSet.cpp
 * @author Betti Oesterholz
 * @date 22.12.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cFibSet.
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
 * This file contains the test for the class cFibSet, which
 * represents a Fib set-element.
 *
 *
 * What's tested of class cFibSet:
 * 	- cFibSet( const unsignedIntFib iuNumberOfVariables, cFibElement * pInSubobject = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- cFibSet( const cFibSet &setElement );
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
 * 	- cFibSet *copy( const unsignedIntFib iObjectFibSet=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementFibSet=0 ) const;
 * 	- bool storeXml( ostream &stream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream &stream ) const;
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
 * 	- unsignedIntFib getNumberOfVariables() const;
 * 	- cFibVariable * getDefinedVariable( const unsignedLongFib uiPosition );
 * 	- unsignedIntFib getDomainNr() const;
 * 	- void setDomainNr( const unsignedLongFib uiInDomainNumber );
 * 	- unsignedLongFib getNumberOfVectors() const;
 * 	- const vector< cVectorFibSet > getVectors();
 * 	- bool setVectors( const vector< cVectorFibSet > & vecSets );
 * 	- cVectorFibSet * getVector( const unsignedLongFib uiPosition );
 * 	- bool setVector( const cVectorFibSet & vecSet, const unsignedLongFib uiPosition );
 * 	- bool addVector( const cVectorFibSet & vecSet, const unsignedLongFib uiPosition=0 );
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
22.12.2010  Oesterholz  created
09.10.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cFibSet.h"
#include "cPoint.h"
#include "cRoot.h"
#include "cProperty.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainIntegerBit.h"
#include "cDomainVector.h"
#include "cDomainVectorOpenEnd.h"
#include "cTypeVariable.h"
#include "cTypeFibSet.h"
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
int testVectors( unsigned long &ulTestphase );
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
	
	cout<<endl<<"Running Test for cFibSet methods"<<endl;
	cout<<      "================================"<<endl;

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
 * This method tests the constructor of the cFibSet class.
 *
 * methods tested:
 * 	- cFibSet( const unsignedIntFib iuNumberOfVariables, cFibElement * pInSubobject = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- cFibSet( const cFibSet &setElement );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- unsignedIntFib getNumberOfElement()
 * 	- bool hasUnderAllObjects() const;
 * 	- unsignedIntFib getDomainNr() const;
 * 	- unsignedIntFib getNumberOfVariables() const;
 * 	- unsignedLongFib getNumberOfVectors() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cFibSet"<<endl;

	cout<<"cFibSet fibSetEmpty( 0 );"<<endl;
	cFibSet fibSetEmpty( 0 );
	
	//check the getType() methode from cFibSet
	if ( fibSetEmpty.getType() == 'v' ){
	
		cout<<"The type of the set-element is correctly 'v' . "<<endl;
	}else{
		cerr<<"Error: The type of the set-element is "<<
			fibSetEmpty.getType()<<" but should be 'v' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFibSet
	if ( ! fibSetEmpty.isValidFibElement() ){
	
		cout<<"The set-element is correctly not a correct set-element. "<<endl;
	}else{
		cerr<<"Error: The set-element is a correct set-element, but should not be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFibSet
	if ( fibSetEmpty.isMovable() ){
	
		cout<<"The set-element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The set-element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFibSet
	if ( fibSetEmpty.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib element for the set-element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib element for the set-element is "<<
			fibSetEmpty.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFibSet
	if ( fibSetEmpty.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib element for the set-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element for the set-element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFibSet
	if ( fibSetEmpty.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib element for the set-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element for the set-element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibSet
	if ( fibSetEmpty.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib element for the set-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element for the set-element is "<<
			fibSetEmpty.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFibSet
	if ( ! fibSetEmpty.hasUnderAllObjects()){
	
		cout<<"The set-element has correctly missing a needed subobjects. "<<endl;
	}else{
		cerr<<"Error: The set-element is not missing a subobject."<<endl;
		iReturn++;
	}
	//check the getNumberOfVariables() methode from cFibSet
	if ( fibSetEmpty.getNumberOfVariables() == 1 ){
	
		cout<<"The number of variables is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of variables is "<<fibSetEmpty.getNumberOfVariables()<<
			", but should be 1. "<<endl;
		iReturn++;
	}
	//check the getDomainNr() methode from cFibSet
	if ( fibSetEmpty.getDomainNr() == 0 ){
	
		cout<<"The domain number is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The domain number is "<<fibSetEmpty.getDomainNr()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the getNumberOfVariables() methode from cFibSet
	if ( fibSetEmpty.getNumberOfVectors() == 0 ){
	
		cout<<"The number of vectors is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of vectors is "<<fibSetEmpty.getNumberOfVectors()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cFibSet with 4 defined variables"<<endl;

	cout<<"cFibSet fibSet4( 4 );"<<endl;
	cFibSet fibSet4( 4 );

	//check the getType() methode from cFibSet
	if ( fibSet4.getType() == 'v' ){
	
		cout<<"The type of the set-element is correctly 'v' . "<<endl;
	}else{
		cerr<<"Error: The type of the set-element is "<<
			fibSet4.getType()<<" but should be 'v' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFibSet
	if ( ! fibSet4.isValidFibElement() ){
	
		cout<<"The set-element is correctly not a correct set-element. "<<endl;
	}else{
		cerr<<"Error: The set-element is a correct set-element, but shouldn't be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFibSet
	if ( fibSet4.isMovable() ){
	
		cout<<"The set-element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The set-element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFibSet
	if ( fibSet4.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib element for the set-element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib element for the set-element is "<<
			fibSet4.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFibSet
	if ( fibSet4.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib element for the set-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element for the set-element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFibSet
	if ( fibSet4.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib element for the set-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element for the set-element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibSet
	if ( fibSet4.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib element for the set-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element for the set-element is "<<
			fibSet4.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getNumberOfVariables() methode from cFibSet
	if ( fibSet4.getNumberOfVariables() == 4 ){
	
		cout<<"The number of variables is correctly 4. "<<endl;
	}else{
		cerr<<"Error: The number of variables is "<<fibSet4.getNumberOfVariables()<<
			", but should be 4. "<<endl;
		iReturn++;
	}
	//check the getDomainNr() methode from cFibSet
	if ( fibSet4.getDomainNr() == 0 ){
	
		cout<<"The domain number is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The domain number is "<<fibSet4.getDomainNr()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the getNumberOfVariables() methode from cFibSet
	if ( fibSet4.getNumberOfVectors() == 0 ){
	
		cout<<"The number of vectors is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of vectors is "<<fibSet4.getNumberOfVectors()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFibSet
	if ( ! fibSet4.hasUnderAllObjects() ){
	
		cout<<"The set-element has correctly not all needed subobjects. "<<endl;
	}else{
		cerr<<"Error: The set-element is not missing a subobject."<<endl;
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cFibSet with a superior Fib element"<<endl;

	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	
	cout<<"cFibSet fibSetSup( 3, NULL, &rootEmpty1 );"<<endl;
	cFibSet fibSetSup( 3, NULL, &rootEmpty1 );

	//check the getType() methode from cFibSet
	if ( fibSetSup.getType() == 'v' ){
	
		cout<<"The type of the set-element is correctly 'v' . "<<endl;
	}else{
		cerr<<"Error: The type of the set-element is "<<
			fibSetSup.getType()<<" but should be 'v' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFibSet
	if ( ! fibSetSup.isValidFibElement() ){
	
		cout<<"The set-element is correctly not a correct set-element. "<<endl;
	}else{
		cerr<<"Error: The set-element is a correct set-element, but shouldn't be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFibSet
	if ( fibSetSup.isMovable() ){
	
		cout<<"The set-element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The set-element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFibSet
	if ( fibSetSup.getNumberOfElement() == 2 ){
	
		cout<<"The number of the Fib element for the set-element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib element for the set-element is "<<
			fibSetSup.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFibSet
	if ( fibSetSup.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib element for the set-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element for the set-element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFibSet
	if ( fibSetSup.getFibElement( -1 ) == &rootEmpty1 ){
	
		cout<<"The previous Fib element for the set-element is correctly rootEmpty1. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element for the set-element is not rootEmpty1."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibSet
	if ( fibSetSup.getSuperiorFibElement() == &rootEmpty1 ){
	
		cout<<"The superior Fib element for the set-element is correctly rootEmpty1. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element for the set-element is "<<
			fibSetSup.getSuperiorFibElement() << " and not rootEmpty1."<<endl;
		iReturn++;
	}
	//check the getNumberOfVariables() methode from cFibSet
	if ( fibSetSup.getNumberOfVariables() == 3 ){
	
		cout<<"The number of variables is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of variables is "<<fibSetSup.getNumberOfVariables()<<
			", but should be 3. "<<endl;
		iReturn++;
	}
	//check the getDomainNr() methode from cFibSet
	if ( fibSetSup.getDomainNr() == 0 ){
	
		cout<<"The domain number is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The domain number is "<<fibSetSup.getDomainNr()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the getNumberOfVariables() methode from cFibSet
	if ( fibSetEmpty.getNumberOfVectors() == 0 ){
	
		cout<<"The number of vectors is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of vectors is "<<fibSetEmpty.getNumberOfVectors()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFibSet
	if ( ! fibSetSup.hasUnderAllObjects() ){
	
		cout<<"The set-element has correctly not all needed subobjects. "<<endl;
	}else{
		cerr<<"Error: The set-element is not missing a subobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cFibSet with a subobject"<<endl;
	
	cout<<"cFibSet fibSetNextPrev( 7, &fibSetEmpty );"<<endl;
	cFibSet fibSetNextPrev( 7, &fibSetEmpty );

	//check the getType() methode from cFibSet
	if ( fibSetNextPrev.getType() == 'v' ){
	
		cout<<"The type of the set-element is correctly 'v' . "<<endl;
	}else{
		cerr<<"Error: The type of the set-element is "<<
			fibSetNextPrev.getType()<<" but should be 'v' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFibSet
	if ( ! fibSetNextPrev.isValidFibElement() ){
	
		cout<<"The set-element is correctly not a correct set-element. "<<endl;
	}else{
		cerr<<"Error: The set-element is a correct set-element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFibSet
	if ( fibSetNextPrev.isMovable() ){
	
		cout<<"The set-element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The set-element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFibSet
	if ( fibSetNextPrev.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib element for the set-element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib element for the set-element is "<<
			fibSetNextPrev.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFibSet
	if ( fibSetNextPrev.getNextFibElement() == &fibSetEmpty ){
	
		cout<<"The next/ main Fib element for the set-element is correctly fibSetEmpty. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element for the set-element is not fibSetEmpty."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFibSet
	if ( fibSetNextPrev.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib element for the set-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element for the set-element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibSet
	if ( fibSetNextPrev.getSuperiorFibElement() == NULL){
	
		cout<<"The superior Fib element for the set-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element for the set-element is "<<
			fibSetNextPrev.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getNumberOfVariables() methode from cFibSet
	if ( fibSetNextPrev.getNumberOfVariables() == 7 ){
	
		cout<<"The number of variables is correctly 7. "<<endl;
	}else{
		cerr<<"Error: The number of variables is "<<fibSetNextPrev.getNumberOfVariables()<<
			", but should be 7. "<<endl;
		iReturn++;
	}
	//check the getDomainNr() methode from cFibSet
	if ( fibSetNextPrev.getDomainNr() == 0 ){
	
		cout<<"The domain number is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The domain number is "<<fibSetNextPrev.getDomainNr()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the getNumberOfVariables() methode from cFibSet
	if ( fibSetNextPrev.getNumberOfVectors() == 0 ){
	
		cout<<"The number of vectors is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of vectors is "<<fibSetNextPrev.getNumberOfVectors()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFibSet
	if ( ! fibSetNextPrev.hasUnderAllObjects()  ){
	
		cout<<"The set-element has correctly not all needed subobjects. "<<endl;
	}else{
		cerr<<"Error: The set-element is not missing a subobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cFibSet with all parameters given"<<endl;
	
	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeFibSet testTypeFibSet;"<<endl;
	cTypeFibSet testTypeFibSet;
	
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
	
	//create vector domain with two elements
	cout<<"vector<cDomain*> vecDomainsE3Na2Nat3VE2Nat1Nat2( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3Na2Nat3VE2Nat1Nat2( 3 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat1Nat2[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl;
	vecDomainsE3Na2Nat3VE2Nat1Nat2[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat1Nat2[ 1 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE2Nat1Nat2[ 1 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3Na2Nat3VE2Nat1Nat2[ 2 ] = &vectorDomainD2;"<<endl;
	vecDomainsE3Na2Nat3VE2Nat1Nat2[ 2 ] = &vectorDomainD2;
	cout<<"cDomainVector vectorDomainE3Na2Nat3VE2Nat1Nat2( vecDomainsE3Na2Nat3VE2Nat1Nat2 );"<<endl;
	cDomainVector vectorDomainE3Na2Nat3VE2Nat1Nat2( vecDomainsE3Na2Nat3VE2Nat1Nat2 );
	delete vecDomainsE3Na2Nat3VE2Nat1Nat2[ 0 ];
	delete vecDomainsE3Na2Nat3VE2Nat1Nat2[ 1 ];
	
	cout<<"rootD2.getDomains()->addDomain( testTypeFibSet, &vectorDomainE3Na2Nat3VE2Nat1Nat2 );"<<endl;
	rootD2.getDomains()->addDomain( testTypeFibSet, &vectorDomainE3Na2Nat3VE2Nat1Nat2 );

	cout<<"cPoint point1;"<<endl;
	cPoint point1;

	cout<<"cFibSet fibSetFull( 2, &point1, &rootD2 );"<<endl;
	cFibSet fibSetFull( 2, &point1, &rootD2 );

	//check the getType() methode from cFibSet
	if ( fibSetFull.getType() == 'v' ){
	
		cout<<"The type of the set-element is correctly 'v' . "<<endl;
	}else{
		cerr<<"Error: The type of the set-element is "<<
			fibSetFull.getType()<<" but should be 'v' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFibSet
	if ( ! fibSetFull.isValidFibElement() ){
	
		cout<<"The set-element is correctly not a correct set-element. "<<endl;
	}else{
		cerr<<"Error: The set-element is a correct set-element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFibSet
	if ( fibSetFull.isMovable() ){
	
		cout<<"The set-element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The set-element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFibSet
	if ( fibSetFull.getNumberOfElement() == 2 ){
	
		cout<<"The number of the Fib element for the set-element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib element for the set-element is "<<
			fibSetFull.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFibSet
	if ( fibSetFull.getNextFibElement() == &point1 ){
	
		cout<<"The next/ main Fib element for the set-element is correctly fibSetEmpty. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element for the set-element is not fibSetEmpty."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFibSet
	if ( fibSetFull.getFibElement( -1 ) == &rootD2 ){
	
		cout<<"The previous Fib element for the set-element is correctly rootD2. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element for the set-element is not rootD2."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibSet
	if ( fibSetFull.getSuperiorFibElement() == &rootD2 ){
	
		cout<<"The superior Fib element for the set-element is correctly rootD2. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element for the set-element is "<<
			fibSetFull.getSuperiorFibElement() << " and not rootD2."<<endl;
		iReturn++;
	}
	//check the getNumberOfVariables() methode from cFibSet
	if ( fibSetFull.getNumberOfVariables() == 2 ){
	
		cout<<"The number of variables is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of variables is "<<fibSetFull.getNumberOfVariables()<<
			", but should be 2. "<<endl;
		iReturn++;
	}
	//check the getDomainNr() methode from cFibSet
	if ( fibSetFull.getDomainNr() == 0 ){
	
		cout<<"The domain number is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The domain number is "<<fibSetFull.getDomainNr()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the getNumberOfVariables() methode from cFibSet
	if ( fibSetFull.getNumberOfVectors() == 0 ){
	
		cout<<"The number of vectors is correctly 0. "<<endl;
	}else{
		cerr<<"Error: The number of vectors is "<<fibSetFull.getNumberOfVectors()<<
			", but should be 0. "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFibSet
	if ( fibSetFull.hasUnderAllObjects() ){
	
		cout<<"The set-element has correctly all needed subobjects. "<<endl;
	}else{
		cerr<<"Error: The set-element is missing a subobject."<<endl;
		iReturn++;
	}
	
	cout<<"cVectorFibSet vecSet( fibSetFull ); "<<endl;
	cVectorFibSet vecSet( fibSetFull );
	cout<<"fibSetFull.addVector( vecSet ); "<<endl;
	fibSetFull.addVector( vecSet );
	
	//check the isValidFibElement() methode from cFibSet
	if ( fibSetFull.isValidFibElement() ){
	
		cout<<"The set-element is correctly a correct set-element. "<<endl;
	}else{
		cerr<<"Error: The set-element is not a correct set-element, but should be ."<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibSet with the vector with values to set from 1 to 2"<<endl;

	cout<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );

	cout<<"cPoint point1( &vecPositionE2 );"<<endl;
	cPoint point1( &vecPositionE2 );
	
	cout<<"cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );
	cout<<"cProperty property1( vecPropertyColorSW, &point1 );"<<endl;
	cProperty property1( vecPropertyColorSW, &point1 );

	cout<<"cFibSet fibSet1( 1, &property1 );"<<endl;
	cFibSet fibSet1( 1, &property1 );

	cout<<"cVectorFibSet vecFibSetE1V1( fibSet1 );"<<endl;
	cVectorFibSet vecFibSetE1V1( fibSet1 );
	cout<<"vecFibSetE1V1.setValue( 1, 1);"<<endl;
	vecFibSetE1V1.setValue( 1, 1);
	cout<<"fibSet1.addVector( vecFibSetE1V1 );"<<endl;
	fibSet1.addVector( vecFibSetE1V1 );
	
	cout<<"cVectorFibSet vecFibSetE1V2( fibSet1 );"<<endl;
	cVectorFibSet vecFibSetE1V2( fibSet1 );
	cout<<"vecFibSetE1V2.setValue( 1, 2);"<<endl;
	vecFibSetE1V2.setValue( 1, 2);
	cout<<"fibSet1.addVector( vecFibSetE1V2 );"<<endl;
	fibSet1.addVector( vecFibSetE1V2 );

	cout<<"point1.getPosition()->setVariable( 1, fibSet1.getDefinedVariable( 1 ) );"<<endl;
	point1.getPosition()->setVariable( 1, fibSet1.getDefinedVariable( 1 ) );

	cout<<"property1.getProperty()->setVariable( 1, fibSet1.getDefinedVariable( 1 ) );"<<endl;
	property1.getProperty()->setVariable( 1, fibSet1.getDefinedVariable( 1 ) );
	
	unsigned int uiPointsToEvalue = 2;
	
	unsigned int uiTimeNeeded = 2 + 2 * 5;

	//check the getTimeNeed() methode from cList
	cout<<"fibSet1.getTimeNeed()"<<endl;
	if ( fibSet1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibSet1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cList
	cout<<"fibSet1.getTimeNeed( 4 )"<<endl;
	if ( fibSet1.getTimeNeed( 4 ) == 4 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 4 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibSet1.getTimeNeed( 4 ) <<", but should be "<< 4 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"list<cVectorProperty> liVecProperties;"<<endl;
	list<cVectorProperty> liVecProperties;
	
	//generate to evalue data
	list< pair< const cVectorPosition*, list<cVectorProperty> > > liPointsToEvalue;
	cVectorPosition vecPositionE2V1( 2 );
	vecPositionE2V1.setValue( 1, 1 );
	cVectorProperty vecPropertyColorSWV1( cTypeProperty::COLOR_SW );
	vecPropertyColorSWV1.setValue( 1, 1 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V1, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	cVectorPosition vecPositionE2V2( 2 );
	vecPositionE2V2.setValue( 1, 2 );
	cVectorProperty vecPropertyColorSWV2( cTypeProperty::COLOR_SW );
	vecPropertyColorSWV2.setValue( 1, 2 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V2, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV2 );
	
	cEvaluePositionList evaluePositionList;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"fibSet1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bool bObjectEvalued = fibSet1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<"fibSet1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = fibSet1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV2 );
	cout<<"fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<"fibSet1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = fibSet1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibSet with a global property list given"<<endl;
	
	cout<<"cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );
	
	list< pair< const cVectorPosition*, list<cVectorProperty> > >::iterator
		itrPositionProperties = liPointsToEvalue.begin();
	itrPositionProperties->second.push_front( vecPropertyLayer );
	itrPositionProperties++;
	itrPositionProperties->second.push_front( vecPropertyLayer );
	
	uiTimeNeeded = 2 + 2 * 5;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"fibSet1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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

	cout<<"fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibSet with the a vector with values to set from 1 till 2 and 5 till 4"<<endl;

	cout<<"cVectorFibSet vecFibSetE1V5( fibSet1 );"<<endl;
	cVectorFibSet vecFibSetE1V5( fibSet1 );
	cout<<"vecFibSetE1V5.setValue( 1, 5);"<<endl;
	vecFibSetE1V5.setValue( 1, 5);
	cout<<"fibSet1.addVector( vecFibSetE1V5 );"<<endl;
	fibSet1.addVector( vecFibSetE1V5 );
	
	cout<<"cVectorFibSet vecFibSetE1V4( fibSet1 );"<<endl;
	cVectorFibSet vecFibSetE1V4( fibSet1 );
	cout<<"vecFibSetE1V4.setValue( 1, 4);"<<endl;
	vecFibSetE1V4.setValue( 1, 4);
	cout<<"fibSet1.addVector( vecFibSetE1V4 );"<<endl;
	fibSet1.addVector( vecFibSetE1V4 );
	
	uiPointsToEvalue = 4;
	
	//generate to evalue data
	cVectorProperty vecPropertyColorSWV5( cTypeProperty::COLOR_SW );
	vecPropertyColorSWV5.setValue( 1, 5 );
	cVectorProperty vecPropertyColorSWV4( cTypeProperty::COLOR_SW );
	vecPropertyColorSWV4.setValue( 1, 4 );

	cVectorPosition vecPositionE2V3( 2 );
	vecPositionE2V3.setValue( 1, 5 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V3, list<cVectorProperty>() ) );
	cVectorPosition vecPositionE2V4( 2 );
	vecPositionE2V4.setValue( 1, 4 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V4, list<cVectorProperty>() ) );
	
	itrPositionProperties = liPointsToEvalue.begin();
	itrPositionProperties->second.clear();
	itrPositionProperties->second.push_back( vecPropertyColorSWV1 );
	itrPositionProperties++;
	itrPositionProperties->second.clear();
	itrPositionProperties->second.push_back( vecPropertyColorSWV2 );
	itrPositionProperties++;
	itrPositionProperties->second.push_back( vecPropertyColorSWV5 );
	itrPositionProperties++;
	itrPositionProperties->second.push_back( vecPropertyColorSWV4 );

	uiTimeNeeded = uiPointsToEvalue + uiPointsToEvalue * 5;

	//check the getTimeNeed() methode from cList
	cout<<"fibSet1.getTimeNeed()"<<endl;
	if ( fibSet1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibSet1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}

	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibSet1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<"fibSet1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = fibSet1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	itrElementProperties->second.push_back( vecPropertyColorSWV1 );
	itrElementProperties++;
	itrElementProperties->second.clear();
	itrElementProperties->second.push_back( vecPropertyColorSWV2 );
	itrElementProperties++;
	itrElementProperties->second.push_back( vecPropertyColorSWV5 );
	itrElementProperties++;
	itrElementProperties->second.push_back( vecPropertyColorSWV4 );
	cout<<"fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<"fibSet1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = fibSet1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibSet with the a vector with values to set from 1 till 2, 5 till 4, 5, 5, 13, -1 "<<endl;

	cout<<"fibSet1.addVector( vecFibSetE1V5 );"<<endl;
	fibSet1.addVector( vecFibSetE1V5 );
	cout<<"fibSet1.addVector( vecFibSetE1V5 );"<<endl;
	fibSet1.addVector( vecFibSetE1V5 );

	cout<<"cVectorFibSet vecFibSetE1V13( fibSet1 );"<<endl;
	cVectorFibSet vecFibSetE1V13( fibSet1 );
	cout<<"vecFibSetE1V13.setValue( 1, 13 );"<<endl;
	vecFibSetE1V13.setValue( 1, 13 );
	cout<<"fibSet1.addVector( vecFibSetE1V13 );"<<endl;
	fibSet1.addVector( vecFibSetE1V13 );

	cout<<"cVectorFibSet vecFibSetE1Vm1( fibSet1 );"<<endl;
	cVectorFibSet vecFibSetE1Vm1( fibSet1 );
	cout<<"vecFibSetE1Vm1.setValue( 1, -1 );"<<endl;
	vecFibSetE1Vm1.setValue( 1, -1 );
	cout<<"fibSet1.addVector( vecFibSetE1Vm1 );"<<endl;
	fibSet1.addVector( vecFibSetE1Vm1 );
	
	uiPointsToEvalue = 8;
	
	//generate to evalue data
	cVectorProperty vecPropertyColorSWV7( cTypeProperty::COLOR_SW );
	vecPropertyColorSWV7.setValue( 1, 5 );
	cVectorProperty vecPropertyColorSWV8( cTypeProperty::COLOR_SW );
	vecPropertyColorSWV8.setValue( 1, 5 );
	cVectorProperty vecPropertyColorSWV9( cTypeProperty::COLOR_SW );
	vecPropertyColorSWV9.setValue( 1, 13 );
	cVectorProperty vecPropertyColorSWV10( cTypeProperty::COLOR_SW );
	vecPropertyColorSWV10.setValue( 1, -1 );

	cVectorPosition vecPositionE2V5( 2 );
	vecPositionE2V5.setValue( 1, 5 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V5, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV7 );
	cVectorPosition vecPositionE2V6( 2 );
	vecPositionE2V6.setValue( 1, 5 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V6, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV8 );
	cVectorPosition vecPositionE2V7( 2 );
	vecPositionE2V7.setValue( 1, 13 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V7, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV9 );
	cVectorPosition vecPositionE2V8( 2 );
	vecPositionE2V8.setValue( 1, -1 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V8, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV10 );
	
	uiTimeNeeded = uiPointsToEvalue + uiPointsToEvalue * 5;

	//check the getTimeNeed() methode from cList
	cout<<"fibSet1.getTimeNeed()"<<endl;
	if ( fibSet1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibSet1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}

	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibSet1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<"fibSet1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = fibSet1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV7 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV8 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV9 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV10 );
	
	cout<<"fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<"fibSet1.evalueObjectSimple( storeEvaluedElement );"<<endl;
	bObjectEvalued = fibSet1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibSet with the a vector with values to set from 1 till 2, 5 till 4, 5, 5, 13, -1, 1.25, 1.24, 1.26 "<<endl;

	cout<<"cVectorFibSet vecFibSetE1( fibSet1 );"<<endl;
	cVectorFibSet vecFibSetE1( fibSet1 );
	cout<<"vecFibSetE1.setValue( 1 1.25 );"<<endl;
	vecFibSetE1.setValue( 1, 1.25 );
	cout<<"fibSet1.addVector( vecFibSetE1 );"<<endl;
	fibSet1.addVector( vecFibSetE1 );
	cout<<"vecFibSetE1.setValue( 1 1.24 );"<<endl;
	vecFibSetE1.setValue( 1, 1.24 );
	cout<<"fibSet1.addVector( vecFibSetE1 );"<<endl;
	fibSet1.addVector( vecFibSetE1 );
	cout<<"vecFibSetE1.setValue( 1, 1.26 );"<<endl;
	vecFibSetE1.setValue( 1, 1.26 );
	cout<<"fibSet1.addVector( vecFibSetE1 );"<<endl;
	fibSet1.addVector( vecFibSetE1 );
	
	uiPointsToEvalue = 11;
	
	//generate to evalue data
	cVectorProperty vecPropertyColorSWE1( cTypeProperty::COLOR_SW );

	cVectorPosition vecPositionE2V9( 2 );
	vecPositionE2V9.setValue( 1, 1.25 );
	vecPropertyColorSWE1.setValue( 1, 1.25 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V9, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWE1 );
	cVectorPosition vecPositionE2V10( 2 );
	vecPositionE2V10.setValue( 1, 1.24 );
	vecPropertyColorSWE1.setValue( 1, 1.24 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V10, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWE1 );
	cVectorPosition vecPositionE2V11( 2 );
	vecPositionE2V11.setValue( 1, 1.26 );
	vecPropertyColorSWE1.setValue( 1, 1.26 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V11, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWE1 );

	uiTimeNeeded = uiPointsToEvalue + uiPointsToEvalue * 5;

	//check the getTimeNeed() methode from cList
	cout<<"fibSet1.getTimeNeed()"<<endl;
	if ( fibSet1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibSet1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}

	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibSet1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<"fibSet1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = fibSet1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	vecPropertyColorSWE1.setValue( 1, 1.25 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWE1 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	vecPropertyColorSWE1.setValue( 1, 1.24 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWE1 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	vecPropertyColorSWE1.setValue( 1, 1.26 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWE1 );
	
	cout<<"fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<"fibSet1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = fibSet1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibSet for non existing object point 1"<<endl;
	
	uiPointsToEvalue = 0;
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"fibSet1.evalueObject( evaluePositionList, 4,  liVecProperties );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evaluePositionList, 4,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The fibSet was correctly not evalued. "<<endl;
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
	cout<<"fibSet1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The fibSet was correctly not evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibSet when returnvalue is false"<<endl;

	uiPointsToEvalue = 1;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	cout<<"fibSet1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. with result false "<<endl;
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
	cout<<"fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. with result false "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibSet with differnt elements to evalue"<<endl;

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
	cout<<"fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<"liCFibElementTyps.push_back( 'v' );"<<endl;
	liCFibElementTyps.push_back( 'v' );
	uiPointsToEvalue = 1;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &fibSet1, list<cVectorProperty>() ) );
	cout<<"fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<"fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibSet1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFibSet with tree defined variables"<<endl;

	cout<<"cVectorPosition vecPositionE3( 3 );"<<endl;
	cVectorPosition vecPositionE3( 3 );

	cout<<"cPoint pointE3( &vecPositionE3 );"<<endl;
	cPoint pointE3( &vecPositionE3 );
	
	cout<<"cVectorProperty vecPropertyColorRGB( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyColorRGB( cTypeProperty::COLOR_RGB );
	cout<<"cProperty propertyRGB( vecPropertyColorRGB, &pointE3 );"<<endl;
	cProperty propertyRGB( vecPropertyColorRGB, &pointE3 );

	cout<<"cFibSet fibSetDef3( 3, &propertyRGB );"<<endl;
	cFibSet fibSetDef3( 3, &propertyRGB );

	cout<<"pointE3.getPosition()->setVariable( 1, fibSetDef3.getDefinedVariable( 1 ) );"<<endl;
	pointE3.getPosition()->setVariable( 1, fibSetDef3.getDefinedVariable( 1 ) );
	cout<<"pointE3.getPosition()->setVariable( 2, fibSetDef3.getDefinedVariable( 2 ) );"<<endl;
	pointE3.getPosition()->setVariable( 2, fibSetDef3.getDefinedVariable( 2 ) );
	cout<<"pointE3.getPosition()->setVariable( 3, fibSetDef3.getDefinedVariable( 3 ) );"<<endl;
	pointE3.getPosition()->setVariable( 3, fibSetDef3.getDefinedVariable( 3 ) );

	cout<<"propertyRGB.getProperty()->setVariable( 1, fibSetDef3.getDefinedVariable( 3 ) );"<<endl;
	propertyRGB.getProperty()->setVariable( 1, fibSetDef3.getDefinedVariable( 3 ) );
	cout<<"propertyRGB.getProperty()->setVariable( 2, fibSetDef3.getDefinedVariable( 2 ) );"<<endl;
	propertyRGB.getProperty()->setVariable( 2, fibSetDef3.getDefinedVariable( 2 ) );
	cout<<"propertyRGB.getProperty()->setVariable( 3, fibSetDef3.getDefinedVariable( 1 ) );"<<endl;
	propertyRGB.getProperty()->setVariable( 3, fibSetDef3.getDefinedVariable( 1 ) );
	
	cout<<"cVectorFibSet vecFibSetE3( fibSetDef3 );={1,2,3}"<<endl;
	cVectorFibSet vecFibSetE3( fibSetDef3 );
	vecFibSetE3.setValue( 1, 1 );
	vecFibSetE3.setValue( 2, 2 );
	vecFibSetE3.setValue( 3, 3 );
	cout<<"fibSetDef3.addVector( vecFibSetE3 );"<<endl;
	fibSetDef3.addVector( vecFibSetE3 );

	vecFibSetE3.setValue( 1, 1 );
	vecFibSetE3.setValue( 2, 2 );
	vecFibSetE3.setValue( 3, 3 );
	cout<<"fibSetDef3.addVector( vecFibSetE3={1, 2, 3 };"<<endl;
	fibSetDef3.addVector( vecFibSetE3 );

	vecFibSetE3.setValue( 1, 3 );
	vecFibSetE3.setValue( 2, 2 );
	vecFibSetE3.setValue( 3, 1 );
	cout<<"fibSetDef3.addVector( vecFibSetE3={3, 2, 1 };"<<endl;
	fibSetDef3.addVector( vecFibSetE3 );

	vecFibSetE3.setValue( 1, -12 );
	vecFibSetE3.setValue( 2, -1.1 );
	vecFibSetE3.setValue( 3, -6.7 );
	cout<<"fibSetDef3.addVector( vecFibSetE3={-12, -1.1, -6.7 };"<<endl;
	fibSetDef3.addVector( vecFibSetE3 );

	vecFibSetE3.setValue( 1, 3.3 );
	vecFibSetE3.setValue( 2, 3.3 );
	vecFibSetE3.setValue( 3, 3.3 );
	cout<<"fibSetDef3.addVector( vecFibSetE3={3.3, 3.3, 3.3 };"<<endl;
	fibSetDef3.addVector( vecFibSetE3 );

	uiPointsToEvalue = 5;
	
	uiTimeNeeded = uiPointsToEvalue * ( 3 + 8 );

	//check the getTimeNeed() methode from cList
	cout<<"fibSetDef3.getTimeNeed()"<<endl;
	if ( fibSetDef3.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibSetDef3.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cList
	cout<<"fibSetDef3.getTimeNeed( 4 )"<<endl;
	if ( fibSetDef3.getTimeNeed( 4 ) == 4 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 4 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			fibSetDef3.getTimeNeed( 4 ) <<", but should be "<< 4 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	
	//generate to evalue data
	liPointsToEvalue.clear();
	cVectorPosition vecPosition2E3( 3 );
	vecPosition2E3.setValue( 1, 1 );
	vecPosition2E3.setValue( 2, 2 );
	vecPosition2E3.setValue( 3, 3 );
	cVectorProperty vecPropertyColor2RGB( cTypeProperty::COLOR_RGB );
	vecPropertyColor2RGB.setValue( 1, 3 );
	vecPropertyColor2RGB.setValue( 2, 2 );
	vecPropertyColor2RGB.setValue( 3, 1 );
	liPointsToEvalue.push_back( make_pair( &vecPosition2E3, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	cVectorPosition vecPosition3E3( 3 );
	vecPosition3E3.setValue( 1, 1 );
	vecPosition3E3.setValue( 2, 2 );
	vecPosition3E3.setValue( 3, 3 );
	vecPropertyColor2RGB.setValue( 1, 3 );
	vecPropertyColor2RGB.setValue( 2, 2 );
	vecPropertyColor2RGB.setValue( 3, 1 );
	liPointsToEvalue.push_back( make_pair( &vecPosition3E3, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	cVectorPosition vecPosition4E3( 3 );
	vecPosition4E3.setValue( 1, 3 );
	vecPosition4E3.setValue( 2, 2 );
	vecPosition4E3.setValue( 3, 1 );
	vecPropertyColor2RGB.setValue( 1, 1 );
	vecPropertyColor2RGB.setValue( 2, 2 );
	vecPropertyColor2RGB.setValue( 3, 3 );
	liPointsToEvalue.push_back( make_pair( &vecPosition4E3, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	cVectorPosition vecPosition5E3( 3 );
	vecPosition5E3.setValue( 1, -12 );
	vecPosition5E3.setValue( 2, -1.1 );
	vecPosition5E3.setValue( 3, -6.7 );
	vecPropertyColor2RGB.setValue( 1, -6.7 );
	vecPropertyColor2RGB.setValue( 2, -1.1 );
	vecPropertyColor2RGB.setValue( 3, -12 );
	liPointsToEvalue.push_back( make_pair( &vecPosition5E3, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	cVectorPosition vecPosition6E3( 3 );
	vecPosition6E3.setValue( 1, 3.3 );
	vecPosition6E3.setValue( 2, 3.3 );
	vecPosition6E3.setValue( 3, 3.3 );
	vecPropertyColor2RGB.setValue( 1, 3.3 );
	vecPropertyColor2RGB.setValue( 2, 3.3 );
	vecPropertyColor2RGB.setValue( 3, 3.3 );
	liPointsToEvalue.push_back( make_pair( &vecPosition6E3, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"fibSetDef3.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = fibSetDef3.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<"fibSetDef3.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = fibSetDef3.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	vecPropertyColor2RGB.setValue( 1, 3 );
	vecPropertyColor2RGB.setValue( 2, 2 );
	vecPropertyColor2RGB.setValue( 3, 1 );
	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	vecPropertyColor2RGB.setValue( 1, 1 );
	vecPropertyColor2RGB.setValue( 2, 2 );
	vecPropertyColor2RGB.setValue( 3, 3 );
	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	vecPropertyColor2RGB.setValue( 1, -6.7 );
	vecPropertyColor2RGB.setValue( 2, -1.1 );
	vecPropertyColor2RGB.setValue( 3, -12 );
	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );

	vecPropertyColor2RGB.setValue( 1, 3.3 );
	vecPropertyColor2RGB.setValue( 2, 3.3 );
	vecPropertyColor2RGB.setValue( 3, 3.3 );
	liFibElementsToEvalue.push_back( make_pair( &pointE3, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColor2RGB );
	
	cout<<"fibSetDef3.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = fibSetDef3.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<"fibSetDef3.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = fibSetDef3.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The fibSet was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing equal methods for set-elements"<<endl;

	cout<<endl<<"Creating fibSetobjects objects to compare: "<<endl<<endl;

	//fibSet with a empty fibSetvector
	cout<<"cFibSet fibSet1V1( 1 );"<<endl;
	cFibSet fibSet1V1( 1 );

	cout<<"cFibSet fibSet2V1( 1 );"<<endl;
	cFibSet fibSet2V1( 1 );

	//with differnt number of defined variables
	cout<<"cFibSet fibSetV2( 2 );"<<endl;
	cFibSet fibSetV2( 2 );

	cout<<"cFibSet fibSetV5( 5 );"<<endl;
	cFibSet fibSetV5( 5 );
	
	//fibSet with one changed vector with values to set
	cout<<"cFibSet fibSetV1g4( 2 );"<<endl;
	cFibSet fibSetV1g4( 2 );
	cout<<"cVectorFibSet vecFibSetV1g4;"<<endl;
	cVectorFibSet vecFibSetV1g4;
	cout<<"vecFibSetV1g4.setValue( 1, 4);"<<endl;
	vecFibSetV1g4.setValue( 1, 4);
	cout<<"fibSetV1g4.addVector( vecFibSetV1g4 );"<<endl;
	fibSetV1g4.addVector( vecFibSetV1g4 );
	
	cout<<"cFibSet fibSetV2g4( 2 );"<<endl;
	cFibSet fibSetV2g4( 2 );
	cout<<"cVectorFibSet vecFibSetV2g4;"<<endl;
	cVectorFibSet vecFibSetV2g4;
	cout<<"vecFibSetV2g4.setValue( 2, 4);"<<endl;
	vecFibSetV2g4.setValue( 2, 4);
	cout<<"fibSetV2g4.addVector( vecFibSetV2g4 );"<<endl;
	fibSetV2g4.addVector( vecFibSetV2g4 );
	
	//with differnt domain number
	cout<<"cFibSet fibSetV1Dom1( 1 );"<<endl;
	cFibSet fibSetV1Dom1( 1 );
	cout<<"fibSetV1Dom1.setDomainNr( 1 );"<<endl;
	fibSetV1Dom1.setDomainNr( 1 );
	
	cout<<"cFibSet fibSetV1Dom3( 3 );"<<endl;
	cFibSet fibSetV1Dom3( 3 );
	cout<<"fibSetV1Dom3.setDomainNr( 3 );"<<endl;
	fibSetV1Dom3.setDomainNr( 3 );
	
	//fibSet with two vector with values to sets
	cout<<"cFibSet fibSetE2E1V1g4E2V2g4( 2 );"<<endl;
	cFibSet fibSetE2E1V1g4E2V2g4( 2 );
	cout<<"fibSetE2E1V1g4E2V2g4.addVector( vecFibSetV1g4 );"<<endl;
	fibSetE2E1V1g4E2V2g4.addVector( vecFibSetV1g4 );
	cout<<"fibSetE2E1V1g4E2V2g4.addVector( vecFibSetV2g4 );"<<endl;
	fibSetE2E1V1g4E2V2g4.addVector( vecFibSetV2g4 );
	
	cout<<"cFibSet fibSetE2E1V2g4E2V1g4( 2 );"<<endl;
	cFibSet fibSetE2E1V2g4E2V1g4( 2 );
	cout<<"fibSetE2E1V2g4E2V1g4.addVector( vecFibSetV2g4 );"<<endl;
	fibSetE2E1V2g4E2V1g4.addVector( vecFibSetV2g4 );
	cout<<"fibSetE2E1V2g4E2V1g4.addVector( vecFibSetV1g4 );"<<endl;
	fibSetE2E1V2g4E2V1g4.addVector( vecFibSetV1g4 );

	//fibSet with tree vectors with values to sets
	cout<<"cFibSet fibSet1E1V1g4E2V2g4E3V2g4( 2 );"<<endl;
	cFibSet fibSet1E1V1g4E2V2g4E3V2g4( 2 );
	cout<<"fibSet1E1V1g4E2V2g4E3V2g4.addVector( vecFibSetV2g4 );"<<endl;
	fibSet1E1V1g4E2V2g4E3V2g4.addVector( vecFibSetV2g4 );
	cout<<"fibSet1E1V1g4E2V2g4E3V2g4.addVector( vecFibSetV2g4 );"<<endl;
	fibSet1E1V1g4E2V2g4E3V2g4.addVector( vecFibSetV2g4 );
	cout<<"fibSet1E1V1g4E2V2g4E3V2g4.addVector( vecFibSetV2g4 );"<<endl;
	fibSet1E1V1g4E2V2g4E3V2g4.addVector( vecFibSetV2g4 );
	
	
	//fibSet with supperior element
	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	
	cout<<"cFibSet fibSetSup( 1, NULL, &rootEmpty1 );"<<endl;
	cFibSet fibSetSup( 1, NULL, &rootEmpty1 );

	//fibSet in Fib element structur
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;
	cout<<"cFibSet fibSetNextPrev( 1, &poinNext );"<<endl;
	cFibSet fibSetNextPrev( 1, &poinNext );


	cout<<"cPoint poinNext2;"<<endl;
	cPoint poinNext2;
	cout<<"cRoot root1;"<<flush<<endl;
	cRoot root1;
	
	cout<<"cTypeFibSet testTypeFibSet;"<<endl;
	cTypeFibSet testTypeFibSet;
	
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

	cout<<"root1.getDomains()->addDomain( testTypeFibSet, &vectorDomainE2 );"<<endl;
	root1.getDomains()->addDomain( testTypeFibSet, &vectorDomainE2 );

	cout<<"cFibSet fibSetFull( 1, &poinNext2, &root1 );"<<endl;
	cFibSet fibSetFull( 1, &poinNext2, &root1 );

	//fibSets with a contained point element
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cFibSet fibSetPoint1( 1, &point1 );"<<endl;
	cFibSet fibSetPoint1( 1, &point1 );

	cout<<"cVectorPosition vecPosition;"<<endl;
	cVectorPosition vecPosition;
	cout<<"cPoint point2( &vecPosition );"<<endl;
	cPoint point2( &vecPosition );
	cout<<"cFibSet fibSetPoint2( 1, &point2 );"<<endl;
	cFibSet fibSetPoint2( 1, &point2 );

	//other Fib element
	cout<<"cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );
	cout<<"cProperty property1( vecPropertyColorSW );"<<endl;
	cProperty property1( vecPropertyColorSW );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with fibSet1
	cFibElement *actualObject = &fibSet1V1;
	string szActualObjectName = "fibSet1V1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibSet2V1
	actualObject = &fibSet2V1;
	szActualObjectName = "fibSet2V1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibSetV2
	actualObject = &fibSetV2;
	szActualObjectName = "fibSetV2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibSetV5
	actualObject = &fibSetV5;
	szActualObjectName = "fibSetV5";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibSetV1g4
	actualObject = &fibSetV1g4;
	szActualObjectName = "fibSetV1g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibSetV2g4
	actualObject = &fibSetV2g4;
	szActualObjectName = "fibSetV2g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibSetV1Dom1
	actualObject = &fibSetV1Dom1;
	szActualObjectName = "fibSetV1Dom1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibSetV1Dom3
	actualObject = &fibSetV1Dom3;
	szActualObjectName = "fibSetV1Dom3";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );
	
	//compare with fibSetE2E1V1g4E2V2g4
	actualObject = &fibSetE2E1V1g4E2V2g4;
	szActualObjectName = "fibSetE2E1V1g4E2V2g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibSetE2E1V2g4E2V1g4
	actualObject = &fibSetE2E1V2g4E2V1g4;
	szActualObjectName = "fibSetE2E1V2g4E2V1g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibSet1E1V1g4E2V2g4E3V2g4
	actualObject = &fibSet1E1V1g4E2V2g4E3V2g4;
	szActualObjectName = "fibSet1E1V1g4E2V2g4E3V2g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibSetSup
	actualObject = &fibSetSup;
	szActualObjectName = "fibSetSup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibSetNextPrev
	actualObject = &fibSetNextPrev;
	szActualObjectName = "fibSetNextPrev";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibSetFull
	actualObject = &fibSetFull;
	szActualObjectName = "fibSetFull";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibSetPoint1
	actualObject = &fibSetPoint1;
	szActualObjectName = "fibSetPoint1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with fibSetPoint2
	actualObject = &fibSetPoint2;
	szActualObjectName = "fibSetPoint2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	//compare with property1
	actualObject = &property1;
	szActualObjectName = "property1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1V1, "fibSet1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet2V1, "fibSet2V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2, "fibSetV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV5, "fibSetV5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1g4, "fibSetV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV2g4, "fibSetV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom1, "fibSetV1Dom1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetV1Dom3, "fibSetV1Dom3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V1g4E2V2g4, "fibSetE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetE2E1V2g4E2V1g4, "fibSetE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSet1E1V1g4E2V2g4E3V2g4, "fibSet1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetSup, "fibSetSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetNextPrev, "fibSetNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetFull, "fibSetFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint1, "fibSetPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, fibSetPoint2, "fibSetPoint2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, property1, "property1" );

	return iReturn;
}


/**
 * This method tests the equal() method of two given Fib objects which are
 * equal.
 * It also compares the superior, next and previous Fib element fibSeters.
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
	
	//check the getNextFibElement() methode from cFibSet
	if ( const_cast<cFibElement*>(&fibObject1)->getNextFibElement() ==
			const_cast<cFibElement*>(&fibObject2)->getNextFibElement() ){
	
		cout<<"The next/ main Fib element pointer for the set-element are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element pointer for the set-element are not equal."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFibSet
	if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) ==
			const_cast<cFibElement*>(&fibObject2)->getFibElement( -1 ) ){
	
		cout<<"The previous Fib element pointer for the set-element are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element pointer for the set-element are not equal."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibSet
	if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() ==
			const_cast<cFibElement*>(&fibObject2)->getSuperiorFibElement() ){
	
		cout<<"The superior Fib element pointer for the set-element are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element pointer for the set-element are not equal."<<endl;
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
 * This method tests the copy methods and copyconstructor of the cFibSet class.
 *
 * methods tested:
 * 	- cFibSet( const cFibSet &setElement );
 * 	- cFibElement *clone( ) const;
 * 	- cFibSet *copy( const unsignedIntFib iObjectFibSet=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementFibSet=0 ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a empty cFibSet"<<endl;
	
	cout<<"cFibSet fibSetEmpty( 0 );"<<endl;
	cFibSet fibSetEmpty( 0 );

	cout<<"cFibSet fibSetEmptyCopyConstruct( fibSetEmpty );"<<endl;
	cFibSet fibSetEmptyCopyConstruct( fibSetEmpty );

	iReturn += testCompareTwoEqualObjectsStructur( fibSetEmptyCopyConstruct, "fibSetEmptyCopyConstruct", fibSetEmpty, "fibSetEmpty" );

	cout<<"cFibElement * pFibSetEmptyClone = fibSetEmpty.clone();"<<endl;
	cFibElement * pFibSetEmptyClone = fibSetEmpty.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pFibSetEmptyClone, "pFibSetEmptyClone", fibSetEmpty, "fibSetEmpty" );
	delete pFibSetEmptyClone;

	cout<<"cFibElement * pFibSetEmptyCopy = fibSetEmpty.copy();"<<endl;
	cFibElement * pFibSetEmptyCopy = fibSetEmpty.copy();

	iReturn += testCompareTwoEqualObjectsStructur( *pFibSetEmptyCopy, "pFibSetEmptyCopy", fibSetEmpty, "fibSetEmpty" );
	delete pFibSetEmptyCopy;

	cout<<"cFibElement * pFibSetEmptyCopyElement = fibSetEmpty.copyElement();"<<endl;
	cFibElement * pFibSetEmptyCopyElement = fibSetEmpty.copyElement();

	iReturn += testCompareTwoEqualObjectsStructur( *pFibSetEmptyCopyElement, "pFibSetEmptyCopyElement", fibSetEmpty, "fibSetEmpty" );
	delete pFibSetEmptyCopyElement;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying for a other object or elementpoint"<<endl;

	cout<<"cFibElement * pFibSetEmptyNoCopy = fibSetEmpty.copy( 1 );"<<endl;
	cFibElement * pFibSetEmptyNoCopy = fibSetEmpty.copy( 1 );

	if ( pFibSetEmptyNoCopy == NULL ){
	
		cout<<"The cFibSet was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cFibSet was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pFibSetEmptyNoCopy;
	}

	cout<<"cFibElement * pFibSetEmptyNoCopyElement = fibSetEmpty.copyElement( 'v', 2 );"<<endl;
	cFibElement * pFibSetEmptyNoCopyElement = fibSetEmpty.copyElement( 'v', 2 );

	if ( pFibSetEmptyNoCopyElement == NULL ){
	
		cout<<"The cFibSet -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cFibSet -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pFibSetEmptyNoCopyElement;
	}

	cout<<"pFibSetEmptyNoCopyElement = fibSetEmpty.copyElement( 'u', 2 );"<<endl;
	pFibSetEmptyNoCopyElement = fibSetEmpty.copyElement( 'u', 2 );

	if ( pFibSetEmptyNoCopyElement == NULL ){
	
		cout<<"The cFibSet -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cFibSet -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pFibSetEmptyNoCopyElement;
	}

	cout<<"pFibSetEmptyNoCopyElement = fibSetEmpty.copyElement( 'r', 1 );"<<endl;
	pFibSetEmptyNoCopyElement = fibSetEmpty.copyElement( 'r', 1 );

	if ( pFibSetEmptyNoCopyElement == NULL ){
	
		cout<<"The cFibSet -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cFibSet -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pFibSetEmptyNoCopyElement;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFibSet with all members set"<<endl;

	//fibSet in Fib element structur
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;

	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeFibSet testTypeFibSet( 3 );"<<endl;
	cTypeFibSet testTypeFibSet( 3 );
	
	//create vector domain for cFibSet
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
	
	cout<<"vector<cDomain*> vecDomainsE3( 3 );"<<endl;
	vector<cDomain*> vecDomainsE3( 3 );
	cout<<"vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 3 );
	cout<<"vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE3[ 1 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE3[ 2 ] = &vectorDomainD2;"<<endl;
	vecDomainsE3[ 2 ] = &vectorDomainD2;
	cout<<"cDomainVector vectorDomainE3( vecDomainsE3 );"<<endl;
	cDomainVector vectorDomainE3( vecDomainsE3 );
	delete vecDomainsE3[ 0 ];
	delete vecDomainsE3[ 1 ];

	
	cout<<"rootD2.getDomains()->addDomain( testTypeFibSet, &vectorDomainE3 );"<<endl;
	rootD2.getDomains()->addDomain( testTypeFibSet, &vectorDomainE3 );

	cout<<"cFibSet fibSet2E2( 2, &poinNext, &rootD2 );"<<endl;
	cFibSet fibSet2E2( 2, &poinNext, &rootD2 );

	cout<<"fibSet2E2.setDomainNr( 3 );"<<endl;
	fibSet2E2.setDomainNr( 3 );

	cout<<"cVectorFibSet vecFibSet2;"<<endl;
	cVectorFibSet vecFibSet2;
	cout<<"vecFibSet2.setValue( 1, 1 );"<<endl;
	vecFibSet2.setValue( 1, 1 );
	cout<<"vecFibSet2.setValue( 2, 2 );"<<endl;
	vecFibSet2.setValue( 2, 2 );
	cout<<"fibSet2E2.addVector( vecFibSet2 );"<<endl;
	fibSet2E2.addVector( vecFibSet2 );
	cout<<"vecFibSet2.setValue( 1, 5 );"<<endl;
	vecFibSet2.setValue( 1, 5 );
	cout<<"vecFibSet2.setValue( 2, 3 );"<<endl;
	vecFibSet2.setValue( 2, 3 );
	cout<<"fibSet2E2.addVector( vecFibSet2 );"<<endl;
	fibSet2E2.addVector( vecFibSet2 );
	cout<<"vecFibSet2.setValue( 1, -3 );"<<endl;
	vecFibSet2.setValue( 1, -3 );
	cout<<"vecFibSet2.setValue( 2, 7 );"<<endl;
	vecFibSet2.setValue( 2, 7 );
	cout<<"fibSet2E2.addVector( vecFibSet2 );"<<endl;
	fibSet2E2.addVector( vecFibSet2 );

	cout<<"cFibSet fibSet2E2CopyConstruct( fibSet2E2 );"<<endl;
	cFibSet fibSet2E2CopyConstruct( fibSet2E2 );

	if ( fibSet2E2CopyConstruct.equalElement( fibSet2E2 ) ){

		cout<<"The fibSet2E2CopyConstruct Fib element is equal to fibSet2E2. "<<endl;
	}else{
		cerr<<"Error: The fibSet2E2CopyConstruct Fib element is not equal to fibSet2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( fibSet2E2CopyConstruct );

	cout<<"cFibElement * pFibSet2E2Copy = fibSet2E2.copy();"<<endl;
	cFibElement * pFibSet2E2Copy = fibSet2E2.copy();
	iReturn += testCompareTwoEqualObjects( *pFibSet2E2Copy, "pFibSet2E2Copy", fibSet2E2, "fibSet2E2" );
	//check the getFibElement() methode from cFibSet
	if ( NULL == pFibSet2E2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous Fib element pointer for the set-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element pointer for the set-element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibSet
	if ( NULL == pFibSet2E2Copy->getSuperiorFibElement() ){
	
		cout<<"The superior Fib element pointer for the set-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element pointer for the set-element is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( pFibSet2E2Copy );

	cout<<"cFibElement * pFibSet2E2CopyElement = fibSet2E2.copyElement( 'u', 1 );"<<endl;
	cFibElement * pFibSet2E2CopyElement = fibSet2E2.copyElement( 'u', 1 );

	if ( pFibSet2E2CopyElement->equalElement( fibSet2E2 ) ){
	
		cout<<"The pFibSet2E2CopyElement Fib element is equal to fibSet2E2. "<<endl;
	}else{
		cerr<<"Error: The pFibSet2E2CopyElement Fib element is not equal to fibSet2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pFibSet2E2CopyElement );
	delete pFibSet2E2CopyElement;

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a limb with more then one set-element and point element"<<endl;

	//a limb with more then one set-element and pointelement
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cFibSet fibSet3( 3, &point1 );"<<endl;
	cFibSet fibSet3( 3, &point1 );
	cout<<"cFibSet fibSet1Obj2( 2, &fibSet3 );"<<endl;
	cFibSet fibSet1Obj2( 2, &fibSet3 );


	cout<<endl<<"cFibSet fibSet1Obj2CopyConstruct( fibSet1Obj2 );"<<endl;
	cFibSet fibSet1Obj2CopyConstruct( fibSet1Obj2 );

	if ( fibSet1Obj2CopyConstruct.equalElement( fibSet1Obj2 ) ){
	
		cout<<"The fibSet1Obj2CopyConstruct Fib element is equal to fibSet1Obj2. "<<endl;
	}else{
		cerr<<"Error: The fibSet1Obj2CopyConstruct Fib element is not equal to fibSet1Obj2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( fibSet1Obj2CopyConstruct );

	cout<<"cFibElement * pFibSet1ColorSwO2LayerO1CopyConstructCopy = fibSet1Obj2CopyConstruct.copy();"<<endl;
	cFibElement * fibSet1Obj2Copy =
		fibSet1Obj2.copy();

	iReturn += testCompareTwoEqualObjects(
		*fibSet1Obj2Copy, "fibSet1Obj2Copy",
		fibSet1Obj2, "fibSet1Obj2" );
	//check the getFibElement() methode from cFibSet
	if ( NULL == fibSet1Obj2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous Fib element pointer for the set-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element pointer for the set-element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFibSet
	if ( fibSet1Obj2Copy->getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib element pointer for the set-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element pointer for the set-element is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( fibSet1Obj2Copy );

	cout<<"cFibElement * pFibSet1Obj2 = fibSet1Obj2.copyElement();"<<endl;
	cFibElement * pFibSet1Obj2 = fibSet1Obj2.copyElement();

	if ( pFibSet1Obj2->equalElement( fibSet1Obj2 ) ){
	
		cout<<"The pFibSet1Obj2 Fib element is equal to fibSet1Obj2. "<<endl;
	}else{
		cerr<<"Error: The pFibSet1Obj2 Fib element is not equal to fibSet1Obj2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pFibSet1Obj2 );
	delete pFibSet1Obj2;

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
 * @param uiSubFibSets the number of vector with values to sets in the fibSet
 * @param vecElementType a vector with the typs of the vectorelements
 * 	(w=value; v=variable)
 * @param vecValues the values of the vectorelements (the on even indexes
 * 	are the lower bounds and on add the upperbounds )
 * @param bHasPointSubobject if true the stored Fib set-element has an
 * 	point element as an subobject, else it has no subobject
 * @return the number of errors occured in the test
 */
int testXmlFibSet( const string szFilename,
		unsigned int uiFirstDefinedVariableValue,
		unsigned int uiNumberOfDefinedVariables,
		unsigned int uiDomainNumber,
		unsigned int uiSubFibSets, vector<char> vecElementType,
		vector<long> vecValues,
		bool bHasPointSubobject = true ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cFibSet:"<<endl;
	
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
		const string szElementName = pXmlElement->Value();
		
		const string szFibSetElementName = "set";
		if ( szElementName == szFibSetElementName ){
			cout<<"The root element is correctly named \""<< szFibSetElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szFibSetElementName <<"\"."<<endl;
			iReturn++;
		}
		
		//read optional domain number
		const char * szDefinedVariableValue = pXmlElement->Attribute( "domainNr" );
		
		if ( szDefinedVariableValue == NULL ){
			if ( uiDomainNumber == 0 ){
				cout<<"Ther is correctly no domain number (it is 0) . "<<endl;
			}else{
				cerr<<"Error: The Fib set-element has no domain number, but it should be "<<
					uiDomainNumber<<" ."<<endl;
				iReturn++;
			}
		}else{
			unsigned long uiDomainNumberStored = atol( szDefinedVariableValue );
			 if ( uiDomainNumberStored == uiDomainNumber ) {
				cout<<"The defined variable of the Fib set-element is correctly \""<< uiDomainNumber <<"\". "<<endl;
			}else{
				cerr<<"Error: The defined variable of the Fib set-element is \""<< uiDomainNumberStored
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
		cerr<<"Error: The Fib set-element has no element for the defined variables."<<endl;
		iReturn++;
		return iReturn;
	}
	
	//read vectors with values to set (element "values")
	pXmlSubElement = pXmlSubElement->NextSiblingElement();
	
	if ( uiSubFibSets == 0 ){
	
		if ( ! pXmlSubElement ){
			cout<<"The Fib set-element contains correctly no vectors. "<<endl;
		
		}else{
			TiXmlHandle xmlHandleSubElementSet = TiXmlHandle( pXmlSubElement );
			TiXmlElement * pXmlSubElementSet = xmlHandleSubElementSet.FirstChild().Element();

			if ( pXmlSubElementSet ){
				cerr<<"Error: The Fib set-element contains vectors, but it shouldn't."<<endl;
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
			
			TiXmlHandle xmlHandleSubElementSet = TiXmlHandle( pXmlSubElement );
			TiXmlElement * pXmlSubElementSet = xmlHandleSubElementSet.FirstChild().Element();
			
			unsigned int uiLoadedSubFibSets = 0;
			for( ; pXmlSubElementSet; pXmlSubElementSet = pXmlSubElementSet->NextSiblingElement() ){
				uiLoadedSubFibSets++;
				
				if ( pXmlSubElementSet ) {
					string szElementName = pXmlSubElementSet->Value();
			
					if ( szElementName == "vector" ){
						cout<<"The root element is correctly named \"vector\". "<<endl;
					
					}else{
						cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"vector\"."<<endl;
						iReturn++;
					}
					const char * szVectorXmlType = pXmlSubElementSet->Attribute( "type" );
					
					if ( szVectorXmlType == NULL ){
						cerr<<"Error: The vector has no type."<<endl;
						iReturn++;
					}else if ( string("set") == szVectorXmlType ) {
						cout<<"The type of the vector is correctly \"set\". "<<endl;
					}else{
						cerr<<"Error: The type of the vector is \""<< szVectorXmlType
							<<"\", but should be \"set\"."<<endl;
						iReturn++;
					}
			
				}else{// pXmlElement == NULL
					cerr<<"Error: No vector handle in \""<< szFilename <<"\"."<<endl;
					iReturn++;
					return iReturn;
				}
				
				TiXmlHandle xmlHandleVectorRoot = TiXmlHandle( pXmlSubElementSet );
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
						(uiLoadedSubFibSets - 1) * uiNumberOfDefinedVariables +
						iNumberOfElement - 1;
					
					//the elementtype the actual element should have
					string szTargetElementType( "non" );
					
					if ( iNumberOfElement < 1 ){
						cerr<<"Error: Ther couldn't be a 0'th vectorelement."<<endl;
						iReturn++;
					}else if ( (int)uiNumberOfDefinedVariables < iNumberOfElement ){
						cerr<<"Error: Ther couldn't be a "<< iNumberOfElement <<
							"'th vectorelement, because a vector with values to set has yust "<<
							uiNumberOfDefinedVariables <<" elements."<<endl;
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
								( iNumberOfElement <= (int)uiNumberOfDefinedVariables ) ){
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
								( iNumberOfElement <= (int)uiNumberOfDefinedVariables ) ){
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
			if ( uiSubFibSets != uiLoadedSubFibSets ){
				cerr<<"Error: "<< uiLoadedSubFibSets <<" vector with values to sets loded, but ther schould be "<<
					uiSubFibSets <<" vector with values to sets."<<endl;
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
				cout<<"The Fib set-element subobject name is correctly point. "<<endl;
			}else{
				cerr<<"Error: The Fib set-element subobject name is not point."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The Fib set-element contains no subobject, but it should."<<endl;
			iReturn++;
		}

	}else{//the set-element has no subobject
		if ( ! pXmlSubElement ){
			cout<<"The Fib set-element contains correctly no subobject. "<<endl;
		
		}else{
			cerr<<"Error: The Fib set-element contains a subobject, but it shouldn't."<<endl;
			iReturn++;
		}
	}
	
	return iReturn;
}



/**
 * This method tests the storeXml() method of the cFibSet class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a set-element"<<endl;

	cout<<"cFibSet fibSet1( 0 );"<<endl;
	cFibSet fibSet1( 0 );
	
	if ( fibSet1.getDefinedVariable( 1 ) ){
		cout<<"fibSet1.getDefinedVariable( 1 )->setValue( 1 );"<<endl;
		fibSet1.getDefinedVariable( 1 )->setValue( 1 );
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlFibSetFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSet1.xml" );
	ofstream * pFileVectorPostion = new ofstream( szXmlFibSetFileName );
	
	bool bStoreSuccesfull = fibSet1.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibSet was stored successfull to the file \""<< szXmlFibSetFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibSet to the file \""<< szXmlFibSetFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	vector<char> vecElementTypePosition( 32, 'w' );
	vector<long> vecValuesPosition( 32, 0 );
	
	iReturn += testXmlFibSet( szXmlFibSetFileName, 1,
		1, 0, 0, vecElementTypePosition, vecValuesPosition, false );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a set-element with an with one vector"<<endl;

	cout<<"cFibSet fibSetDef1S1E1V1( 1 );"<<endl;
	cFibSet fibSetDef1S1E1V1( 1 );
	cout<<"cVectorFibSet vecFibSetE1( fibSetDef1S1E1V1 );"<<endl;
	cVectorFibSet vecFibSetE1( fibSetDef1S1E1V1 );
	cout<<"vecFibSetE1.setValue( 1, 1 );"<<endl;
	vecFibSetE1.setValue( 1, 1 );
	vecValuesPosition[ 0 ] = 1;
	cout<<"fibSetDef1S1E1V1.addVector( vecFibSetE1 );"<<endl;
	fibSetDef1S1E1V1.addVector( vecFibSetE1 );
	
	if ( fibSetDef1S1E1V1.getDefinedVariable( 1 ) ){
		cout<<"fibSetDef1S1E1V1.getDefinedVariable( 1 )->setValue( 1 );"<<endl;
		fibSetDef1S1E1V1.getDefinedVariable( 1 )->setValue( 1 );
	}
	
	szFileNameBuffer[0] = 0;
	szXmlFibSetFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSetDef1S1E1V1.xml" );
	pFileVectorPostion = new ofstream( szXmlFibSetFileName );
	
	bStoreSuccesfull = fibSetDef1S1E1V1.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibSet was stored successfull to the file \""<< szXmlFibSetFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibSet to the file \""<< szXmlFibSetFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibSet( szXmlFibSetFileName, 1,
		1, 0, 1, vecElementTypePosition, vecValuesPosition, false );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a set-element with more than one defined variable"<<endl;

	cout<<"cFibSet fibSetDef3S1E3V1( 3 );"<<endl;
	cFibSet fibSetDef3S1E3V1( 3 );
	cout<<"cVectorFibSet vecFibSetE3( fibSetDef3S1E3V1 );"<<endl;
	cVectorFibSet vecFibSetE3( fibSetDef3S1E3V1 );
	cout<<"vecFibSetE3.setValue( 1, 1 );"<<endl;
	vecFibSetE3.setValue( 1, 1 );
	vecValuesPosition[ 0 ] = 1;
	cout<<"vecFibSetE3.setValue( 2, 2 );"<<endl;
	vecFibSetE3.setValue( 2, 2 );
	vecValuesPosition[ 1 ] = 2;
	cout<<"vecFibSetE3.setValue( 3, 3 );"<<endl;
	vecFibSetE3.setValue( 3, 3 );
	vecValuesPosition[ 2 ] = 3;
	cout<<"fibSetDef3S1E3V1.addVector( vecFibSetE3 );"<<endl;
	fibSetDef3S1E3V1.addVector( vecFibSetE3 );
	
	if ( fibSetDef3S1E3V1.getDefinedVariable( 1 ) ){
		cout<<"fibSetDef3S1E3V1.getDefinedVariable( 1 )->setValue( 1 );"<<endl;
		fibSetDef3S1E3V1.getDefinedVariable( 1 )->setValue( 1 );
	}
	if ( fibSetDef3S1E3V1.getDefinedVariable( 2 ) ){
		cout<<"fibSetDef3S1E3V1.getDefinedVariable( 2 )->setValue( 2 );"<<endl;
		fibSetDef3S1E3V1.getDefinedVariable( 2 )->setValue( 2 );
	}
	if ( fibSetDef3S1E3V1.getDefinedVariable( 3 ) ){
		cout<<"fibSetDef3S1E3V1.getDefinedVariable( 3 )->setValue( 3 );"<<endl;
		fibSetDef3S1E3V1.getDefinedVariable( 3 )->setValue( 3 );
	}
	
	szFileNameBuffer[0] = 0;
	szXmlFibSetFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSetDef3S1E3V1.xml" );
	pFileVectorPostion = new ofstream( szXmlFibSetFileName );
	
	bStoreSuccesfull = fibSetDef3S1E3V1.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibSet was stored successfull to the file \""<< szXmlFibSetFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibSet to the file \""<< szXmlFibSetFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibSet( szXmlFibSetFileName, 1,
		3, 0, 1, vecElementTypePosition, vecValuesPosition, false );

	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a set-element with a point subobject"<<endl;

	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cFibSet fibSetDef2( 2, &point1 );"<<endl;
	cFibSet fibSetDef2( 2, &point1 );
	cout<<"cVectorFibSet vecFibSetE2( fibSetDef2 );"<<endl;
	cVectorFibSet vecFibSetE2( fibSetDef2 );
	cout<<"vecFibSetE2.setValue( 1, 5 );"<<endl;
	vecFibSetE2.setValue( 1, 5 );
	vecValuesPosition[ 0 ] = 5;
	cout<<"vecFibSetE2.setValue( 2, -7 );"<<endl;
	vecFibSetE2.setValue( 2, -7 );
	vecValuesPosition[ 1 ] = -7;
	cout<<"fibSetDef2.addVector( vecFibSetE2 );"<<endl;
	fibSetDef2.addVector( vecFibSetE2 );
	
	if ( fibSetDef2.getDefinedVariable( 1 ) ){
		cout<<"fibSetDef2.getDefinedVariable( 1 )->setValue( 3 );"<<endl;
		fibSetDef2.getDefinedVariable( 1 )->setValue( 3 );
	}
	if ( fibSetDef2.getDefinedVariable( 2 ) ){
		cout<<"fibSetDef2.getDefinedVariable( 2 )->setValue( 4 );"<<endl;
		fibSetDef2.getDefinedVariable( 2 )->setValue( 4 );
	}
	
	szFileNameBuffer[0] = 0;
	szXmlFibSetFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSetDef2Point.xml" );
	pFileVectorPostion = new ofstream( szXmlFibSetFileName );
	
	bStoreSuccesfull = fibSetDef2.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibSet was stored successfull to the file \""<< szXmlFibSetFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibSet to the file \""<< szXmlFibSetFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibSet( szXmlFibSetFileName, 3,
		2, 0, 1, vecElementTypePosition, vecValuesPosition, true );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a set-element with a domain number"<<endl;

	cout<<"fibSetDef2.setDomainNr( 7 )"<<endl;
	fibSetDef2.setDomainNr( 7 );
	
	szFileNameBuffer[0] = 0;
	szXmlFibSetFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSetDef2Dom7.xml" );
	pFileVectorPostion = new ofstream( szXmlFibSetFileName );
	
	bStoreSuccesfull = fibSetDef2.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibSet was stored successfull to the file \""<< szXmlFibSetFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibSet to the file \""<< szXmlFibSetFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibSet( szXmlFibSetFileName, 3,
		2, 7, 1, vecElementTypePosition, vecValuesPosition, true );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a set-element with two vectors with values set"<<endl;

	cout<<"vecFibSetE2.setValue( 1, -1 );"<<endl;
	vecFibSetE2.setValue( 1, -1 );
	vecValuesPosition[ 2 ] = -1;
	cout<<"vecFibSetE2.setValue( 2, 4 );"<<endl;
	vecFibSetE2.setValue( 2, 4 );
	vecValuesPosition[ 3 ] = 4;
	cout<<"fibSetDef2.addVector( vecFibSetE2 );"<<endl;
	fibSetDef2.addVector( vecFibSetE2 );
	
	szFileNameBuffer[0] = 0;
	szXmlFibSetFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSetDef2Vec2.xml" );
	pFileVectorPostion = new ofstream( szXmlFibSetFileName );
	
	bStoreSuccesfull = fibSetDef2.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibSet was stored successfull to the file \""<< szXmlFibSetFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibSet to the file \""<< szXmlFibSetFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibSet( szXmlFibSetFileName, 3,
		2, 7, 2, vecElementTypePosition, vecValuesPosition, true );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a set-element with 5 vectors with values set"<<endl;

	cout<<"vecFibSetE2.setValue( 1, 3 );"<<endl;
	vecFibSetE2.setValue( 1, 3 );
	vecValuesPosition[ 4 ] = 3;
	cout<<"vecFibSetE2.setValue( 2, 99 );"<<endl;
	vecFibSetE2.setValue( 2, 99 );
	vecValuesPosition[ 5 ] = 99;
	cout<<"fibSetDef2.addVector( vecFibSetE2 );"<<endl;
	fibSetDef2.addVector( vecFibSetE2 );
	cout<<"vecFibSetE2.setValue( 1, 4 );"<<endl;
	vecFibSetE2.setValue( 1, 4 );
	vecValuesPosition[ 6 ] = 4;
	cout<<"vecFibSetE2.setValue( 2, -19 );"<<endl;
	vecFibSetE2.setValue( 2, -19 );
	vecValuesPosition[ 7 ] = -19;
	cout<<"fibSetDef2.addVector( vecFibSetE2 );"<<endl;
	fibSetDef2.addVector( vecFibSetE2 );
	cout<<"vecFibSetE2.setValue( 1, 5 );"<<endl;
	vecFibSetE2.setValue( 1, 5 );
	vecValuesPosition[ 8 ] = 5;
	cout<<"vecFibSetE2.setValue( 2, 33 );"<<endl;
	vecFibSetE2.setValue( 2, 33 );
	vecValuesPosition[ 9 ] = 33;
	cout<<"fibSetDef2.addVector( vecFibSetE2 );"<<endl;
	fibSetDef2.addVector( vecFibSetE2 );
	
	szFileNameBuffer[0] = 0;
	szXmlFibSetFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSetDef2Vec5.xml" );
	pFileVectorPostion = new ofstream( szXmlFibSetFileName );
	
	bStoreSuccesfull = fibSetDef2.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibSet was stored successfull to the file \""<< szXmlFibSetFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibSet to the file \""<< szXmlFibSetFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibSet( szXmlFibSetFileName, 3,
		2, 7, 5, vecElementTypePosition, vecValuesPosition, true );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on a set-element with variables set"<<endl;

	cout<<"vecFibSetE2.setValue( 1, 22 );"<<endl;
	vecFibSetE2.setValue( 1, 22 );
	vecValuesPosition[ 4 ] = 22;
	cout<<"vecFibSetE2.setVariable( 2, fibSetDef3S1E3V1.getDefinedVariable( 3 ) );"<<endl;
	vecFibSetE2.setVariable( 2, fibSetDef3S1E3V1.getDefinedVariable( 3 ) );
	vecElementTypePosition[ 5 ] = 'v';
	vecValuesPosition[ 5 ] = 3;
	cout<<"fibSetDef2.setVector( vecFibSetE2, 3 );"<<endl;
	fibSetDef2.setVector( vecFibSetE2, 3 );
	
	cout<<"vecFibSetE2.setVariable( 1, fibSetDef3S1E3V1.getDefinedVariable( 1 ) );"<<endl;
	vecFibSetE2.setVariable( 1, fibSetDef3S1E3V1.getDefinedVariable( 1 ) );
	vecElementTypePosition[ 6 ] = 'v';
	vecValuesPosition[ 6 ] = 1;
	cout<<"vecFibSetE2.setValue( 2, -8 );"<<endl;
	vecFibSetE2.setValue( 2, -8 );
	vecValuesPosition[ 7 ] = -8;
	cout<<"fibSetDef2.setVector( vecFibSetE2, 4 );"<<endl;
	fibSetDef2.setVector( vecFibSetE2, 4 );
	
	szFileNameBuffer[0] = 0;
	szXmlFibSetFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSetDef2Vec5.xml" );
	pFileVectorPostion = new ofstream( szXmlFibSetFileName );
	
	bStoreSuccesfull = fibSetDef2.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFibSet was stored successfull to the file \""<< szXmlFibSetFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFibSet to the file \""<< szXmlFibSetFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlFibSet( szXmlFibSetFileName, 3,
		2, 7, 5, vecElementTypePosition, vecValuesPosition, true );
	
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

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on a empty cFibSet"<<endl;

	cout<<"cVectorPosition vecPosition( 0 );"<<flush<<endl;
	cVectorPosition vecPosition( 0 );

	cout<<"cPoint point1( &vecPosition );"<<flush<<endl;
	cPoint point1( &vecPosition );

	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;

	cout<<"cFibSet fibSetDef1( 1, &point1, &root );"<<endl;
	cFibSet fibSetDef1( 1, &point1, &root );

	//test get compressed size
	unsigned int uiCompressedSize = 17 + 8 + 32 + 5;//introduction + count defined variables + count vectors + point
	if ( (unsigned int)(fibSetDef1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			fibSetDef1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSetDef1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bool bStoreSuccesfull = fibSetDef1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cFibSet1[] = { (char)0x1F, (char)0x00, (char)0x02, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x04 };
	// 00010  0000 0000  0000 0000  0000 0000  0000 0000  0000 0001 0 0000 0000 0001 1111 <-
	// =0001 1111 0000 0000 0 0000 0001  0000 0000  0000 0000  0000 0000 0000 0000 00010
	// =0001 1111  0000 0000  0000 0010  0000 0000  0000 0000  0000 0000  0000 0000  0000 0100
	iReturn += compareBytsWithFile( szFileNameBuffer, cFibSet1, 8 );

	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with one vector"<<endl;

	cout<<"fibSetDef1.getDefinedVariable( 1 )->setIntegerValue( 1 ); (should not change anything)"<<endl;
	fibSetDef1.getDefinedVariable( 1 )->setIntegerValue( 1 );
	
	cout<<"cVectorFibSet vecFibSetE1( fibSetDef1 );"<<endl;
	cVectorFibSet vecFibSetE1( fibSetDef1 );
	
	cout<<"vecFibSetE1.setValue( 1, 2 );"<<endl;
	vecFibSetE1.setValue( 1, 2 );
	cout<<"fibSetDef1.addVector( vecFibSetE1 );"<<endl;
	fibSetDef1.addVector( vecFibSetE1 );
	
	//test get compressed size
	uiCompressedSize = 17 + 8 + 32 + 1 *(32 + 1) + 5;//introduction + count defined variables + count vectors + vectors + point
	if ( (unsigned int)(fibSetDef1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			fibSetDef1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSetVec1E1V2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = fibSetDef1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char szFibSetVec1E1V2[] = { (char)0x1F, (char)0x00, (char)0x02, (char)0x02, (char)0x00, (char)0x00, (char)0x00, (char)0x08, (char)0x00, (char)0x00, (char)0x00, (char)0x08 };
	//   00010   0000 0000  0000 0000  0000 0000  0000 0010 0   0000 0000  0000 0000  0000 0000  0000 0001   0000 0001   0   0000 0000 0001 1111 <-
	//->=0001 1111  0000 0000  0000 0010  0000 0010  0000 0000  0000 0000  0000 0000  0000 1000  0000 0000  0000 0000  0000 0000  0000 1000
	iReturn += compareBytsWithFile( szFileNameBuffer, szFibSetVec1E1V2, 12 );

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with more than one variable"<<endl;

	cout<<"cPoint point2( &vecPosition );"<<flush<<endl;
	cPoint point2( &vecPosition );

	cout<<"cRoot root2;"<<flush<<endl;
	cRoot root2;

	cout<<"cFibSet fibSetDef3( 3, &point2, &root2 );"<<endl;
	cFibSet fibSetDef3( 3, &point2, &root2 );

	cout<<"cVectorFibSet vecFibSetE3( fibSetDef3 );"<<endl;
	cVectorFibSet vecFibSetE3( fibSetDef3 );
	
	cout<<"vecFibSetE3.setValue( 1, 2 );"<<endl;
	vecFibSetE3.setValue( 1, 2 );
	cout<<"vecFibSetE3.setValue( 2, 3 );"<<endl;
	vecFibSetE3.setValue( 2, 3 );
	cout<<"vecFibSetE3.setValue( 3, 5 );"<<endl;
	vecFibSetE3.setValue( 3, 5 );
	cout<<"fibSetDef3.addVector( vecFibSetE3 );"<<endl;
	fibSetDef3.addVector( vecFibSetE3 );
	
	//test get compressed size
	uiCompressedSize = 17 + 8 + 32 + 3 *(32 + 1) + 5;//introduction + count defined variables + count vectors + vectors + point
	if ( (unsigned int)(fibSetDef3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			fibSetDef3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSetDef3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = fibSetDef3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char szFibSetDef3[] = { (char)0x1F, (char)0x00, (char)0x06, (char)0x02, (char)0x00, (char)0x00, (char)0x00, (char)0x08, (char)0x00, (char)0x00, (char)0x00, (char)0x18, (char)0x00, (char)0x00, (char)0x00, (char)0x50, (char)0x00, (char)0x00, (char)0x00, (char)0x20, (char)0x00 };
	//   00010   0000 0000  0000 0000  0000 0000  0000 0101 0   0000 0000  0000 0000  0000 0000  0000 0011 0   0000 0000  0000 0000  0000 0000  0000 0010 0   0000 0000  0000 0000  0000 0000  0000 0001  0000 0011   0   0000 0000 0001 1111 <-
	//->=0001 1111  0000 0000  0000 0110  0000 0010  0000 0000  0000 0000  0000 0000  0000 1000  0000 0000  0000 0000  0000 0000  0001 1000  0000 0000  0000 0000  0000 0000  0101 0000  0000 0000  0000 0000  0000 0000  0010 0000  0
	iReturn += compareBytsWithFile( szFileNameBuffer, szFibSetDef3, 21 );

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with domain number set"<<endl;

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

	cout<<"root2.getValueDomains()->addDomain( typeFibSet, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );"<<endl;
	root2.getValueDomains()->addDomain( typeFibSet, &vectorDomainE3Na2Nat3VE3Nat1Nat2Nat3 );

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
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 5 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 5 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 7 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 7 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int2Int3;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainE2Int2Int3;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VE2NInt2Int3( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibSet typeFibSet4( 4 );"<<endl;
	cTypeFibSet typeFibSet4( 4 );
	cout<<"root2.getValueDomains()->addDomain( typeFibSet4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );"<<endl;
	root2.getValueDomains()->addDomain( typeFibSet4, &vectorDomainE3Na4Nat5VE2NInt2Int3 );
	
	cout<<"cTypeFibSet typeFibSet9( 9 );"<<endl;
	cTypeFibSet typeFibSet9( 9 );
	cDomain * pStandardDomain = typeFibSet9.getStandardDomain();
	cout<<"root2.getDomains()->addDomain( typeFibSet9, typeFibSet9.getStandardDomain() );"<<endl;
	root2.getDomains()->addDomain( typeFibSet9, *pStandardDomain );
	delete pStandardDomain;
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1Int8( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1Int8( 1 );
	cout<<"vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 7 );"<<endl;
	vecDomainsE1Int8[ 0 ] = new cDomainIntegerBit( 7 );
	cout<<"cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );"<<endl;
	cDomainVectorOpenEnd vectorDomainOE1Int8( vecDomainsE1Int8 );
	delete vecDomainsE1Int8[ 0 ];
	
	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 3 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 0 ] = new cDomainNaturalNumberBit( 3 );
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 1 ] = new cDomainNaturalNumberBit( 8 );
	cout<<"vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainOE1Int8;"<<endl;
	vecDomainsE3Na2Nat3VE1Nat1[ 2 ] = &vectorDomainOE1Int8;
	cout<<"cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );"<<endl;
	cDomainVector vectorDomainE3Na4Nat5VOE1Int8( vecDomainsE3Na2Nat3VE1Nat1 );

	cout<<"cTypeFibSet typeFibSet13( 13 );"<<endl;
	cTypeFibSet typeFibSet13( 13 );
	cout<<"root2.getValueDomains()->addDomain( typeFibSet13, &vectorDomainE3Na4Nat5VOE1Int8 );"<<endl;
	root2.getValueDomains()->addDomain( typeFibSet13, &vectorDomainE3Na4Nat5VOE1Int8 );
	
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
	delete vecDomainsE3Na2Nat3VE1Nat1[ 0 ];
	delete vecDomainsE3Na2Nat3VE1Nat1[ 1 ];

	cout<<"root2.getDomains()->addDomain( typeFibSet13, &vectorDomainE3Na4Nat5VOE1Int6 );"<<endl;
	root2.getDomains()->addDomain( typeFibSet13, &vectorDomainE3Na4Nat5VOE1Int6 );

	
	cout<<"fibSetDef3.setDomainNr( 9 );"<<endl;
	fibSetDef3.setDomainNr( 9 );
	
	//test get compressed size
	uiCompressedSize = 17 + 4 + 8 + 32 + 3 *(32 + 1) + 5;//introduction + count defined variables + count vectors + vectors + point
	if ( (unsigned int)(fibSetDef3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			fibSetDef3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSetDef3Dom9.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = fibSetDef3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char szFibSetDef3Dom9[] = { (char)0x1F, (char)0x00, (char)0x73, (char)0x20, (char)0x00, (char)0x00, (char)0x00, (char)0x80, (char)0x00, (char)0x00, (char)0x00, (char)0x80, (char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x05, (char)0x00, (char)0x00, (char)0x00, (char)0x02 };
	//   00010   0000 0000  0000 0000  0000 0000  0000 0101 0   0000 0000  0000 0000  0000 0000  0000 0011 0   0000 0000  0000 0000  0000 0000  0000 0010 0   0000 0000  0000 0000  0000 0000  0000 0001  0000 0011  1001  1   0000 0000 0001 1111 <-
	//->=0001 1111  0000 0000  0111 0011  0010 0000  0000 0000  0000 0000  0000 0000  1000 0000  0000 0000  0000 0000  0000 0000  1000 0000  0000 0001  0000 0000  0000 0000  0000 0000  0000 0101  0000 0000  0000 0000  0000 0000  0 0010
	iReturn += compareBytsWithFile( szFileNameBuffer, szFibSetDef3Dom9, 21 );

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with domain"<<endl;
	
	cout<<"fibSetDef3.setDomainNr( 13 );"<<endl;
	fibSetDef3.setDomainNr( 13 );
	
	//test get compressed size
	uiCompressedSize = 17 + 4 + 3 + 8 + 3 *(7 + 1) + 5;//introduction + count defined variables + count vectors + vectors + point
	if ( (unsigned int)(fibSetDef3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			fibSetDef3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSetDef3Dom13.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = fibSetDef3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char szFibSetDef3Dom13[] = { (char)0x1F, (char)0x00, (char)0x7B, (char)0x01, (char)0x04, (char)0x06, (char)0x0A, (char)0x02 };
	//   00010   000 0101 0   000 0011 0   000 0010 0    0000 0001   011   1101  1  0000 0000 0001 1111 <-
	//->=0001 1111  0000 0000  0111 1011  0000 0001  0000 0100  0000 0110  0000 1010  0 0010
	iReturn += compareBytsWithFile( szFileNameBuffer, szFibSetDef3Dom13, 8 );

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with two vectors"<<endl;
	
	cout<<"vecFibSetE3.setValue( 1, 1 );"<<endl;
	vecFibSetE3.setValue( 1, 1 );
	cout<<"vecFibSetE3.setValue( 2, 7 );"<<endl;
	vecFibSetE3.setValue( 2, 7 );
	cout<<"vecFibSetE3.setValue( 3, 12 );"<<endl;
	vecFibSetE3.setValue( 3, 12 );
	cout<<"fibSetDef3.addVector( vecFibSetE3 );"<<endl;
	fibSetDef3.addVector( vecFibSetE3 );
	
	//test get compressed size
	uiCompressedSize = 17 + 4 + 3 + 8 + 2 * 3 *(7 + 1) + 5;//introduction + count defined variables + count vectors + vectors + point
	if ( (unsigned int)(fibSetDef3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			fibSetDef3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSetDef3Dom13Vec2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = fibSetDef3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char szFibSetDef3Dom13Vec2[] = { (char)0x1F, (char)0x00, (char)0x7B, (char)0x02, (char)0x04, (char)0x06, (char)0x0A, (char)0x02, (char)0x0E, (char)0x18, (char)0x02 };
	//   00010  000 1100 0   000 0111 0   000 0001 0    000 0101 0   000 0011 0   000 0010 0    0000 0010   011   1101  1  0000 0000 0001 1111 <-
	//->=0001 1111  0000 0000  0111 1011  0000 0010  0000 0100  0000 0110  0000 1010   0000 0010  0000 1110  0001 1000   0 0010
	iReturn += compareBytsWithFile( szFileNameBuffer, szFibSetDef3Dom13Vec2, 11 );

	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with five vectors"<<endl;
	
	cout<<"vecFibSetE3.setValue( 1, 3 );"<<endl;
	vecFibSetE3.setValue( 1, 3 );
	cout<<"vecFibSetE3.setValue( 2, 16 );"<<endl;
	vecFibSetE3.setValue( 2, 16 );
	cout<<"vecFibSetE3.setValue( 3, 32 );"<<endl;
	vecFibSetE3.setValue( 3, 32 );
	cout<<"fibSetDef3.addVector( vecFibSetE3 );"<<endl;
	fibSetDef3.addVector( vecFibSetE3 );

	cout<<"vecFibSetE3.setValue( 1, 4 );"<<endl;
	vecFibSetE3.setValue( 1, 4 );
	cout<<"vecFibSetE3.setValue( 2, 63 );"<<endl;
	vecFibSetE3.setValue( 2, 63 );
	cout<<"vecFibSetE3.setValue( 3, -64 );"<<endl;
	vecFibSetE3.setValue( 3, -64 );
	cout<<"fibSetDef3.addVector( vecFibSetE3 );"<<endl;
	fibSetDef3.addVector( vecFibSetE3 );

	cout<<"vecFibSetE3.setValue( 1, 5 );"<<endl;
	vecFibSetE3.setValue( 1, 5 );
	cout<<"vecFibSetE3.setValue( 2, 1 );"<<endl;
	vecFibSetE3.setValue( 2, 1 );
	cout<<"vecFibSetE3.setValue( 3, -1 );"<<endl;
	vecFibSetE3.setValue( 3, -1 );
	cout<<"fibSetDef3.addVector( vecFibSetE3 );"<<endl;
	fibSetDef3.addVector( vecFibSetE3 );

	//test get compressed size
	uiCompressedSize = 17 + 4 + 3 + 8 + 5 * 3 *(7 + 1) + 5;//introduction + count defined variables + count vectors + vectors + point
	if ( (unsigned int)(fibSetDef3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			fibSetDef3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "fibSetDef3Dom13Vec5.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = fibSetDef3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char szFibSetDef3Dom13Vec5[] = { (char)0x1F, (char)0x00, (char)0x7B, (char)0x05, (char)0x04, (char)0x06, (char)0x0A, (char)0x02, (char)0x0E, (char)0x18, (char)0x06, (char)0x20, (char)0x40, (char)0x08, (char)0x7E, (char)0x80, (char)0x0A, (char)0x02, (char)0xFE,  (char)0x02 };
	//   00010 ... 000 1100 0   000 0111 0   000 0001 0    000 0101 0   000 0011 0   000 0010 0    0000 0101   011   1101  1  0000 0000 0001 1111 <-
	//->=0001 1111  0000 0000  0111 1011  0000 0101  0000 0100  0000 0110  0000 1010   0000 0010  0000 1110  0001 1000  T 0000 0110  0010 0000  0100 0000   0000 1000  0111 1110  1000 0000   0000 1010  0000 0010  1111 1110   0 0010
	iReturn += compareBytsWithFile( szFileNameBuffer, szFibSetDef3Dom13Vec5, 20 );


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

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the domain number methods of cFibSet"<<endl;

	unsigned long ulCorrectDomainNr = 0;
	
	cFibSet fibSet( 2 );
	const cFibSet * pFibSetConst = &fibSet;
	
	for ( unsigned long uiIteration = 0; uiIteration < MAX_RAND_TEST_SIZE; uiIteration++ ){
		
		//choos random new domain number
		ulCorrectDomainNr = rand() % MAX_RAND_TEST_SIZE;
		
		cout<<"fibSet.setDomainNr( "<<ulCorrectDomainNr<<" );"<<endl;
		fibSet.setDomainNr( ulCorrectDomainNr );
		
		//check the getDomainNr() methode from const cFibSet
		if ( fibSet.getDomainNr() == ulCorrectDomainNr ){
		
			cout<<"The domain number is correctly "<<ulCorrectDomainNr<<" . "<<endl;
		}else{
			cerr<<"Error: The domain number is "<<fibSet.getDomainNr()<<
				", but should be "<<ulCorrectDomainNr<<" . "<<endl;
			iReturn++;
		}
		//check the getDomainNr() methode from cFibSet
		if ( pFibSetConst->getDomainNr() != ulCorrectDomainNr ){
			cerr<<"Error: The domain number is "<<fibSet.getDomainNr()<<
				", but should be "<<ulCorrectDomainNr<<" (on const fibSet). "<<endl;
			iReturn++;
		}
	}

	return iReturn;
}



/**
 * This method checks the vector methods of the class.
 *
 * methods tested:
 * 	- unsignedIntFib getNumberOfVariables() const;
 * 	- cFibVariable * getDefinedVariable( const unsignedLongFib uiPosition );
 * 	- unsignedLongFib getNumberOfVectors() const;
 * 	- const vector< cVectorFibSet > getVectors();
 * 	- bool setVectors( const vector< cVectorFibSet > & vecSets );
 * 	- cVectorFibSet * getVector( const unsignedLongFib uiPosition );
 * 	- bool setVector( const cVectorFibSet & vecSet, const unsignedLongFib uiPosition );
 * 	- bool addVector( const cVectorFibSet & vecSet, const unsignedLongFib uiPosition=0 );
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

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the vector with values to set -methods"<<endl;

	//controll data
	vector< cVectorFibSet > vecVectors;
	
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
	
	cout<<"cFibSet * pFibSet = new cFibSet( 1, NULL, &root );"<<endl;
	cFibSet * pFibSet = new cFibSet( 1, NULL, &root );
	vecDefinedVariables.push_back( pFibSet->getDefinedVariable( 1 ) );
	const cFibSet * pFibSetConst = pFibSet;
	
	const unsigned long ulChangeFibSetEveryIteration = ( MAX_RAND_TEST_SIZE < 64 ) ?
		(MAX_RAND_TEST_SIZE / 8 + 4):(MAX_RAND_TEST_SIZE / (8 + log( MAX_RAND_TEST_SIZE ) ) + 4);
		
	const unsigned long ulChangeAllVectorsEveryItr = ulChangeFibSetEveryIteration / 4 + 2;
	
	cout<<"Changing the set-element in average all iterations: "<<
		ulChangeFibSetEveryIteration<<endl;
	cout<<"Changing all set-element vectors in average all iterations: "<<
		ulChangeAllVectorsEveryItr<<endl;

	for ( unsigned long uiIteration = 0; uiIteration < MAX_RAND_TEST_SIZE; uiIteration++ ){
		
		cout<<"ITERATION: "<<uiIteration<<endl;
		
		//choose if the cFibSet should change
		if ( rand() % ulChangeFibSetEveryIteration ){
			//change vectors
			
			if ( rand() % ulChangeAllVectorsEveryItr ){
				if ( rand() % 4 == 0 ){
					//change vector with value to set
					const unsigned int uiChangeVectorNumber =
						rand() % (vecDefinedVariables.size() + 4);
					
					//check if position is correct
					const bool bCanChangeVector = ( 1 <= uiChangeVectorNumber ) &&
						( uiChangeVectorNumber <= vecVectors.size() );
					cout<<"pFibSet->getVector( "<< uiChangeVectorNumber <<" );";
					cVectorFibSet * pVectorSet = pFibSet->getVector( uiChangeVectorNumber );
					
					if ( bCanChangeVector == (pVectorSet != NULL) ){
						cout<<"= "<<pVectorSet<<endl;
					}else{//error
						cout<<endl;
						cerr<<"Error: Could"<<((pVectorSet != NULL)?"":"n't")<<" get the vector on the position "<<
							uiChangeVectorNumber <<".(size="<< vecVectors.size() <<")"<<endl;
						iReturn++;
						continue;
					}
					if ( pVectorSet != NULL ){
						//vector was returned -> change a value
						vector< cVectorFibSet >::iterator itrInsertSetVector =
							vecVectors.begin();
						
						for ( unsigned int uiActualSetVector = 1;
								( uiActualSetVector < uiChangeVectorNumber ) &&
								( itrInsertSetVector != vecVectors.end() );
								uiActualSetVector++, itrInsertSetVector++ ){
							//nothing to do
						}

						const unsignedIntFib uiNumberOfElements =
							pVectorSet->getNumberOfElements();
						
						const unsignedIntFib uiChoosenElement =
							1 + rand() % uiNumberOfElements;
						if ( rand() % 3 ){
							//set value
							const double dValueToSet = ( ((double)( rand() % ( 256LL * 256LL * 256LL * 256LL ) -
								128LL * 256LL * 256LL * 256LL )) / ( 256.0 * 256.0 ) );
							cout<<"pVectorSet("<<pVectorSet<<")->setValue( "<<
								uiChoosenElement<<", "<<dValueToSet<<" );"<<endl;
							pVectorSet->setValue( uiChoosenElement, dValueToSet );
							if ( itrInsertSetVector != vecVectors.end() ){
								itrInsertSetVector->setValue( uiChoosenElement, dValueToSet );
							}
						}else{//set variable
							const unsigned int uiVariableToSet =
								rand() % vecPossibleVariables.size();
							cout<<"pVectorSet("<<pVectorSet<<")->setValue( "<<
								uiChoosenElement<<", variable["<<uiVariableToSet<<"] );"<<endl;
							pVectorSet->setVariable( 
								uiChoosenElement, vecPossibleVariables[ uiVariableToSet ] );
							if ( itrInsertSetVector != vecVectors.end() ){
								itrInsertSetVector->setVariable(
									uiChoosenElement, vecPossibleVariables[ uiVariableToSet ] );
							}
						}
						
					}//end if vector was given back
				}else{//change wool vector
					//choos random vector with values to set to change
					const unsigned int uiChangeVectorNumber =
						rand() % (vecDefinedVariables.size() + 4);
					
					//choos if delete or add a vector with values to set
					if ( rand() % 3 ){
						//generate vector to set
						cVectorFibSet * pVectorToSet = NULL;
						bool bVectorOk = true;
						if ( rand() % 8 ){
							//vector without error
							if ( rand() % 2 ){
								cout<<"pVectorToSet = new cVectorFibSet( *pFibSet )={";
								pVectorToSet = new cVectorFibSet( *pFibSet );
							}else{
								cout<<"pVectorToSet = new cVectorFibSet( "<<vecDefinedVariables.size()<<" )={";
								pVectorToSet = new cVectorFibSet( vecDefinedVariables.size() );
							}
						}else{//vector with error
							const unsigned int uiVectorElements = rand() % ( rand() % 256 + 1 );
							pVectorToSet = new cVectorFibSet( uiVectorElements );
							bVectorOk = ( uiVectorElements == vecDefinedVariables.size() );
							cout<<"pVectorToSet = new cVectorFibSet( "<<uiVectorElements<<
								"="<<(bVectorOk?"OK":"not Ok")<<" )={";
						}
						//set the vector elements to values
						const unsigned int uiVectorElements = pVectorToSet->getNumberOfElements();
						for ( unsigned int uiActualElement = 1;
								uiActualElement <= uiVectorElements; uiActualElement++ ){
							
							if ( rand() % 3 ){
								//set value
								const double dValueToSet = ( ((double)( rand() % ( 256LL * 256LL * 256LL * 256LL ) -
									128LL * 256LL * 256LL * 256LL )) / ( 256.0 * 256.0 ) );
								pVectorToSet->setValue( uiActualElement, dValueToSet );
								cout<<dValueToSet<<";";
							}else{//setvariable
								const unsigned int uiVariableToSet =
									rand() % vecPossibleVariables.size();
								pVectorToSet->setVariable( uiActualElement,
									vecPossibleVariables[ uiVariableToSet ] );
								cout<<"variable["<<uiVariableToSet<<"];";
							}
						}
						cout<<"}"<<endl;
						
						//choose if add or set vector
						if ( rand() % 2 ){
							//add a vector with values to set
							cout<<"pFibSet->addVector( vecFibSet , "<< uiChangeVectorNumber <<" );";
							const bool bVectorAdded = pFibSet->addVector( *pVectorToSet, uiChangeVectorNumber );
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
									vector< cVectorFibSet >::iterator itrInsertSubfibSet =
										vecVectors.begin();
									
									for ( unsigned int uiActualSubfibSet = 1;
											uiActualSubfibSet < uiChangeVectorNumber;
											uiActualSubfibSet++, itrInsertSubfibSet++ ){
										//nothing to do
									}
									vecVectors.insert( itrInsertSubfibSet, *pVectorToSet );
								}else{//insert on back
									vecVectors.push_back( *pVectorToSet );
								}
							}
						}else{//set a vector with values to set
							//check if position is correct
							const bool bPositionOk = ( 1 <= uiChangeVectorNumber ) &&
								( uiChangeVectorNumber <= vecVectors.size() );
							const bool bCanAddVector = bVectorOk && bPositionOk;
							cout<<"pFibSet->setVector( vecFibSet , "<< uiChangeVectorNumber <<" );";
							const bool bVectorSet = pFibSet->setVector( *pVectorToSet, uiChangeVectorNumber );
							
							if ( bVectorSet == bCanAddVector ){
								cout<<"Ok "<<(bVectorSet?"set":"not set")<<endl;
							}else{//error
								cout<<endl;
								cerr<<"Error: Could"<<(bVectorSet?"":"n't")<<" insert the vector on the position "<<
									uiChangeVectorNumber <<".(size="<< vecVectors.size() <<")"<<endl;
								iReturn++;
								continue;
							}
							if ( bVectorSet ){
								//vector was set
								if ( bPositionOk ){
									//insert the new vector with values to set in the control vector
									vector< cVectorFibSet >::iterator itrInsertSubfibSet =
										vecVectors.begin();
									
									for ( unsigned int uiActualSubfibSet = 1;
											uiActualSubfibSet < uiChangeVectorNumber;
											uiActualSubfibSet++, itrInsertSubfibSet++ ){
										//nothing to do
									}
									*itrInsertSubfibSet = *pVectorToSet;
								}
							}
						}
						delete pVectorToSet;
					}else{//delete a vector with values to set
						const bool bPositionOk = ( 1 <= uiChangeVectorNumber ) &&
							( uiChangeVectorNumber <= vecVectors.size() );
						
						cout<<"pFibSet->deleteVector( "<< uiChangeVectorNumber <<" );";
						const bool bVectorDeleted = pFibSet->deleteVector( uiChangeVectorNumber );
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
							vector< cVectorFibSet >::iterator itrDeletedSubfibSet =
								vecVectors.begin();
							
							for ( unsigned int uiActualSubfibSet = 1;
									uiActualSubfibSet < uiChangeVectorNumber;
									uiActualSubfibSet++, itrDeletedSubfibSet++ ){
								//nothing to do
							}
							vecVectors.erase( itrDeletedSubfibSet );
						}
					}
				}
			}else{//change all vectors: setVectors()
				const bool bWithError = (rand() % 8 == 0);
				unsigned int uiNumberVectorsToSet = rand() % (4 + rand() % (4 +
					rand() % 256 ) );
				bool bVectorsOk = true;
				vector< cVectorFibSet > vecToSetVectors;
				
				cout<<"Creating "<<uiNumberVectorsToSet<<" vectors "<<
					(bWithError?"with errors possible :":":")<<endl;
				for ( unsigned int uiActualVector = 0;
						uiActualVector < uiNumberVectorsToSet; uiActualVector++ ){
					
					if ( ( ! bWithError ) || (rand() % 8) ){
						//vector without error
						if ( rand() % 2 ){
							cout<<"   vecToSetVectors["<<uiActualVector<<
								"] = new cVectorFibSet( *pFibSet )={";
							vecToSetVectors.push_back( cVectorFibSet( *pFibSet ) );
						}else{
							cout<<"   vecToSetVectors["<<uiActualVector<<
								"] = new cVectorFibSet( "<<vecDefinedVariables.size()<<" )={";
							vecToSetVectors.push_back( cVectorFibSet( vecDefinedVariables.size() ) );
						}
					}else{//vector with error
						const unsigned int uiVectorElements = rand() % ( rand() % 256 + 1 );
						vecToSetVectors.push_back( cVectorFibSet( uiVectorElements ) );
						bVectorsOk &= ( uiVectorElements == vecDefinedVariables.size() );
						cout<<"   vecToSetVectors["<<uiActualVector<<
							"] = new cVectorFibSet( "<<uiVectorElements<<
							"="<<(bVectorsOk?"OK":"not Ok")<<" )={";
					}
					//set the vector elements to values
					cVectorFibSet * pVectorToSet = &(vecToSetVectors.back());
					const unsigned int uiVectorElements = pVectorToSet->getNumberOfElements();
					for ( unsigned int uiActualElement = 1;
							uiActualElement <= uiVectorElements; uiActualElement++ ){
						
						if ( rand() % 3 ){
							//set value
							const double dValueToSet = ( ((double)( rand() % ( 256LL * 256LL * 256LL * 256LL ) -
								128LL * 256LL * 256LL * 256LL )) / ( 256.0 * 256.0 ) );
							pVectorToSet->setValue( uiActualElement, dValueToSet );
							cout<<dValueToSet<<";";
						}else{//setvariable
							const unsigned int uiVariableToSet =
								rand() % vecPossibleVariables.size();
							pVectorToSet->setVariable( uiActualElement,
								vecPossibleVariables[ uiVariableToSet ] );
							cout<<"variable["<<uiVariableToSet<<"];";
						}
					}
					cout<<"}"<<endl;
				}
				const bool bVectorsSet = pFibSet->setVectors( vecToSetVectors );
				
				if ( bVectorsSet == bVectorsOk ){
					cout<<"Ok "<<(bVectorsSet?"set":"not set")<<endl;
				}else{//error
					cout<<endl;
					cerr<<"Error: Could"<<(bVectorsSet?"":"n't")<<" set the "<<
						"vectors. (size="<< vecVectors.size() <<")"<<endl;
					iReturn++;
					continue;
				}
				if ( bVectorsSet ){
					//vector was set
					vecVectors = vecToSetVectors;
				}
			}
		}else{//change cFibSet
			//delete old data
			cout<<endl<<endl;
			delete pFibSet;
			vecVectors.clear();
			vecDefinedVariables.clear();
			//create new data
			const unsigned int uiDefinedVariables = rand() % (3 + rand() %
				(1 + rand() % ( 1 + rand() % 64 )));
			cout<<"pFibSet = new cFibSet( "<<uiDefinedVariables<<", NULL, &root );"<<endl;
			pFibSet = new cFibSet( uiDefinedVariables, NULL, &root );
			pFibSetConst = pFibSet;
			
			if ( uiDefinedVariables != 0 ){
				//add all defined variables
				for ( unsigned int uiActualDefVariable = 1;
						uiActualDefVariable <= uiDefinedVariables; uiActualDefVariable++ ){
					
					vecDefinedVariables.push_back(
						pFibSet->getDefinedVariable( uiActualDefVariable ) );
				}
			}else{//minimum one defined variable
				vecDefinedVariables.push_back( pFibSet->getDefinedVariable( 1 ) );
			}
		}
		
		//check the vector with values to sets
		//check getNumberOfVectors()
		if ( pFibSetConst->getNumberOfVectors() != vecVectors.size() ){
			cerr<<"Error: The pFibSet has "<< pFibSetConst->getNumberOfVectors() <<
				" vector with values to sets, but should have "<< vecVectors.size() <<endl;
			iReturn++;
		}
		//check getVectors()
		if ( pFibSet->getVectors() != vecVectors ){
			cerr<<"Error: The pFibSet returns the wrong vectors (getVectors()). "<<
				"(number of vectors "<<vecVectors.size()<<")"<<endl;
			iReturn++;
		}
		//check getVector()
		set<cFibVariable*> setCorrectUsedVariables;
		
		vector< cVectorFibSet >::iterator itrSubfibSet = vecVectors.begin();
		for ( unsigned int uiSubfibSet = 1;
				uiSubfibSet <= pFibSetConst->getNumberOfVectors();
				uiSubfibSet++ ){
				
			cVectorFibSet * pSubFibSet = pFibSet->getVector( uiSubfibSet );
			if ( pSubFibSet == NULL ){
				cerr<<"Error: Ther is no "<<uiSubfibSet <<"'th vector with values to set. (size="<<
					vecVectors.size() <<")"<<endl;
				iReturn++;
			}else{
				//check the vector with values to set bounds
				if ( (*itrSubfibSet) != (*pSubFibSet) ){
					cerr<<"Error: The "<<uiSubfibSet <<"'th vector with values to set is wrong."<<endl;
					cerr<<"pFibSet->getVector( "<<uiSubfibSet<<" ) :"<<endl;
					pSubFibSet->storeXml( cerr );
					cerr<<"correct vector :"<<endl;
					itrSubfibSet->storeXml( cerr );
					iReturn++;
				}
				//check the defining Fib element of the vector with values to set
				if ( pSubFibSet->getDefiningFibElement() != pFibSetConst ){
					cerr<<"Error: The "<<uiSubfibSet <<"'th vector with values to set has the wrong definingelement."<<endl;
					cerr<<"   correct definingelement: "<< pFibSetConst <<
						" given definingelement: "<< pSubFibSet->getDefiningFibElement() <<endl;
					iReturn++;
				}
				//evalue used variables vor later
				set<cFibVariable*> setActualUsedVariables =
					pSubFibSet->getUsedVariables();
				setCorrectUsedVariables.insert( setActualUsedVariables.begin(),
					setActualUsedVariables.end() );
			}
			if ( itrSubfibSet != vecVectors.end() ){
				itrSubfibSet++;
			}else{
				cerr<<"Error: Ther are more vector with values to sets in the pFibSet than ther should be. (size="<<
					vecVectors.size() <<")"<<endl;
				iReturn++;
			}
		}
		//check out of bounderie vector with values to sets
		cVectorFibSet * pSubFibSet = pFibSet->getVector( 0 );
		if ( pSubFibSet != NULL ){
			cerr<<"Error: Ther is a "<<0 <<"'th vector with values to set. (size="<<
				vecVectors.size() <<")"<<endl;
			iReturn++;
		}
		pSubFibSet = pFibSet->getVector( vecVectors.size() + 1 );
		if ( pSubFibSet != NULL ){
			cerr<<"Error: Ther is a "<< vecVectors.size() + 1 <<"'th vector with values to set. (size="<<
				vecVectors.size() <<")"<<endl;
			iReturn++;
		}
		//check getDefinedVariable(), isDefinedVariable() and getDefinedVariables()
		const list<cFibVariable*> liDefinedVariables =
			pFibSet->getDefinedVariables( ED_POSITION );
		//check getNumberOfVariables()
		if ( pFibSetConst->getNumberOfVariables() != liDefinedVariables.size() ){
			cerr<<"Error: The pFibSet has "<< pFibSetConst->getNumberOfVariables() <<
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
			
			cFibVariable * pFibVariable = pFibSet->getDefinedVariable( uiPosition );
			
			if ( pFibVariable != (*itrDefVariable) ){
				cerr<<"Error: The "<<uiPosition<<"'th defined variables is "<<
					pFibVariable<<", but should be "<<(*itrDefVariable)<<" ."<<endl;
				iReturn++;
			}
			
			if ( ! pFibSet->isDefinedVariable( (*itrDefVariable) , ED_POSITION ) ){
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
		//check getNumberOfVariables()
		if ( pFibSetConst->getNumberOfVariables() != vecDefinedVariables.size() ){
			cerr<<"Error: The pFibSet has "<< pFibSetConst->getNumberOfVariables() <<
				" defined variables, but should have "<< vecDefinedVariables.size() <<endl;
			iReturn++;
		}
		//check out of bounderie vector with values to sets
		cFibVariable * pDefVariable = pFibSet->getDefinedVariable( 0 );
		if ( pDefVariable != NULL ){
			cerr<<"Error: Ther is a "<<0 <<"'th defined variable. (size="<<
				vecDefinedVariables.size() <<")"<<endl;
			iReturn++;
		}
		pDefVariable = pFibSet->getDefinedVariable( vecDefinedVariables.size() + 1 );
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
			
			if ( pFibSet->isDefinedVariable( (*itrDefVariable) , ED_POSITION ) ){
				cerr<<"Error: The variable ("<<(*itrDefVariable)<<") is given back by isDefinedVariable( "<<
					(*itrDefVariable)<<", ED_POSITION ) as a defined variable, but shouldn't ."<<endl;
				iReturn++;
			}
		}
		
		//check getUsedVariables( ED_POSITION )
		const set<cFibVariable*> setUsedVariables =
			pFibSet->getUsedVariables( ED_POSITION );
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
			
			if ( ! pFibSet->isUsedVariable( (*itrUsedVariable) , ED_POSITION ) ){
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
			
			if ( pFibSet->isUsedVariable( (*itrDefVariable) , ED_POSITION ) ){
				cerr<<"Error: The defined variable ("<<(*itrDefVariable)<<
					") is evalued as used by isUsedVariable( "<<
					(*itrDefVariable)<<", ED_POSITION ), but shouldn't ."<<endl;
				iReturn++;
			}
		}
		
	}

	delete pFibSet;
	
	return iReturn;
}



/**
 * This method tests the variable methods of the cFibSet class.
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
	
	cout<<"cFibSet fibSet1( 2 );"<<endl;
	cFibSet fibSet1( 2 );
	
	cout<<"cVectorFibSet vecFibSet1( fibSet1 );"<<endl;
	cVectorFibSet vecFibSet1( fibSet1 );
	cout<<"vecFibSet1.setValue( 1, 4);"<<endl;
	vecFibSet1.setValue( 1, 4);
	cout<<"vecFibSet1.setValue( 2, 7);"<<endl;
	vecFibSet1.setValue( 2, 7);
	cout<<"fibSet1.addVector( vecFibSet1 );"<<endl;
	fibSet1.addVector( vecFibSet1 );
	
	cout<<"cVectorFibSet vecFibSet2( fibSet1 );"<<endl;
	cVectorFibSet vecFibSet2( fibSet1 );
	cout<<"vecFibSet2.setValue( 1, 2);"<<endl;
	vecFibSet2.setValue( 1, 2);
	cout<<"fibSet1.addVector( vecFibSet2 );"<<endl;
	fibSet1.addVector( vecFibSet2 );

	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSet1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! fibSet1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the set-element. "<<endl;
		iReturn++;
	}
	set<cFibVariable*> setCorrectUsedVariables;
	
	//check getUsedVariables()
	cout<<"setUsedVariables = fibSet1.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = fibSet1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"fibSet1.getVector( 2 )->setVariable( 1, pVariable1 );"<<endl;
	fibSet1.getVector( 2 )->setVariable( 1, pVariable1 );
	setCorrectUsedVariables.insert( pVariable1 );

	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSet1.isUsedVariable( pVariable1 )"<<endl;
	if ( fibSet1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the set-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibSet1.getUsedVariables(); "<<endl;
	setUsedVariables = fibSet1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"fibSet1.getVector( 1 )->setVariable( 1, pVariable2 );"<<endl;
	fibSet1.getVector( 1 )->setVariable( 1, pVariable2 );
	setCorrectUsedVariables.insert( pVariable2 );

	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSet1.isUsedVariable( pVariable2 )"<<endl;
	if ( fibSet1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the set-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibSet1.getUsedVariables(); "<<endl;
	setUsedVariables = fibSet1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"fibSet1.getVector( 1 )->setVariable( 2, pVariable4 );"<<endl;
	fibSet1.getVector( 1 )->setVariable( 2, pVariable4 );
	setCorrectUsedVariables.insert( pVariable4 );

	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSet1.isUsedVariable( pVariable4 )"<<endl;
	if ( fibSet1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable4 is correctly used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is not used in the set-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibSet1.getUsedVariables(); "<<endl;
	setUsedVariables = fibSet1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"fibSet1.getVector( 1 )->setVariable( 2, pVariable1 );"<<endl;
	fibSet1.getVector( 1 )->setVariable( 2, pVariable1 );
	setCorrectUsedVariables.erase( pVariable4 );
	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSet1.isUsedVariable( pVariable1 )"<<endl;
	if ( fibSet1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the set-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibSet1.getUsedVariables(); "<<endl;
	setUsedVariables = fibSet1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"fibSet1.replaceVariable( pVariable2, pVariable3 );"<<endl;
	bool bVariableReplaced = fibSet1.replaceVariable( pVariable2, pVariable3 );
	setCorrectUsedVariables.erase( pVariable2 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSet1.isUsedVariable( pVariable2 )"<<endl;
	if ( ! fibSet1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the set-element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSet1.isUsedVariable( pVariable3 )"<<endl;
	if ( fibSet1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the set-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibSet1.getUsedVariables(); "<<endl;
	setUsedVariables = fibSet1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"Try replacing non existing variable pVariable2:"<<endl;
	cout<<"fibSet1.replaceVariable( pVariable2, pVariable4 );"<<endl;
	bVariableReplaced = fibSet1.replaceVariable( pVariable2, pVariable4 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibSet1.getUsedVariables(); "<<endl;
	setUsedVariables = fibSet1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSet1.isUsedVariable( pVariable2 )"<<endl;
	if ( ! fibSet1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the set-element. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSet1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! fibSet1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable4 is correctly not used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is used in the set-element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSet1.isUsedVariable( pVariable3 )"<<endl;
	if ( fibSet1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the set-element. "<<endl;
		iReturn++;
	}

	cout<<"fibSet1.replaceVariable( pVariable1, pVariable3 );"<<endl;
	bVariableReplaced = fibSet1.replaceVariable( pVariable1, pVariable3 );
	setCorrectUsedVariables.erase( pVariable1 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSet1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! fibSet1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the set-element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSet1.isUsedVariable( pVariable3 )"<<endl;
	if ( fibSet1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the set-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibSet1.getUsedVariables(); "<<endl;
	setUsedVariables = fibSet1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing variable methods on a fibSet with a containing point"<<endl;

	cout<<"cVectorPosition vecPositionE3( 3 );"<<endl;
	cVectorPosition vecPositionE3( 3 );

	cout<<"cPoint point1( &vecPositionE3 );"<<endl;
	cPoint point1( &vecPositionE3 );
	cout<<"cFibSet fibSetPoint( 2, &point1 );"<<endl;
	cFibSet fibSetPoint( 2, &point1 );
	cout<<"fibSetPoint.addVector( vecFibSet1 );"<<endl;
	fibSetPoint.addVector( vecFibSet1 );

	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSetPoint.isUsedVariable( pVariable1 )"<<endl;
	if ( ! fibSetPoint.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the set-element. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.clear();
	
	//check getUsedVariables()
	cout<<"setUsedVariables = fibSetPoint.getUsedVariables(); "<<endl;
	setUsedVariables = fibSetPoint.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"point1.getPosition()->setVariable( 3, pVariable1 );"<<endl;
	point1.getPosition()->setVariable( 3, pVariable1 );

	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSetPoint.isUsedVariable( pVariable1 )"<<endl;
	if ( ! fibSetPoint.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the set-element. "<<endl;
		iReturn++;
	}
	cout<<"point1.isUsedVariable( pVariable1 )"<<endl;
	if ( point1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the set-element. "<<endl;
		iReturn++;
	}
	cout<<"fibSetPoint.isUsedVariable( pVariable1, ED_BELOW_EQUAL )"<<endl;
	if ( fibSetPoint.isUsedVariable( pVariable1, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable1 is correctly used ED_BELOW_EQUAL the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used ED_BELOW_EQUAL the set-element. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = fibSetPoint.getUsedVariables(); "<<endl;
	setUsedVariables = fibSetPoint.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.insert( pVariable1 );
	//check getUsedVariables()
	cout<<"setUsedVariables = fibSetPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = fibSetPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back for ED_BELOW_EQUAL. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong for ED_BELOW_EQUAL. "<<endl;
		iReturn++;
	}

	cout<<"point1.getPosition()->setVariable( 1, pVariable2 );"<<endl;
	point1.getPosition()->setVariable( 1, pVariable2 );
	
	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSetPoint.isUsedVariable( pVariable2 )"<<endl;
	if ( ! fibSetPoint.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the set-element. "<<endl;
		iReturn++;
	}
	cout<<"point1.isUsedVariable( pVariable2 )"<<endl;
	if ( point1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the set-element. "<<endl;
		iReturn++;
	}
	cout<<"fibSetPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( fibSetPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly used ED_BELOW_EQUAL the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used ED_BELOW_EQUAL the set-element. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = fibSetPoint.getUsedVariables(); "<<endl;
	setUsedVariables = fibSetPoint.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.insert( pVariable2 );
	//check getUsedVariables()
	cout<<"setUsedVariables = fibSetPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = fibSetPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back for ED_BELOW_EQUAL. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong for ED_BELOW_EQUAL. "<<endl;
		iReturn++;
	}
	
	cout<<"fibSetPoint.replaceVariable( pVariable2, pVariable3 );"<<endl;
	bVariableReplaced = fibSetPoint.replaceVariable( pVariable2, pVariable3 );
	setCorrectUsedVariables.erase( pVariable2 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSetPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( ! fibSetPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly not used ED_BELOW_EQUAL the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used ED_BELOW_EQUAL the set-element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFibSet
	cout<<"fibSetPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL )"<<endl;
	if ( fibSetPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_BELOW_EQUAL the set-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_BELOW_EQUAL the set-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = fibSetPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = fibSetPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	return iReturn;
}





