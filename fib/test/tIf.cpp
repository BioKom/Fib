/**
 * @file tIf
 * file name: tIf.cpp
 * @author Betti Oesterholz
 * @date 02.05.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cIf.
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
 * This file contains the test for the class cIf, which
 * represents a Fib-if-element.
 *
 *
 * What's tested of class cIf:
 * 	- cIf( const cCondition & inCondition, cFibElement * pInUnderobjectTrueCase = NULL, cFibElement * pInUnderobjectFalseCase = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- cIf( const cIf & ifElement );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- bool hasUnderAllObjects( ) const;
 * 	- unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
 * 	- bool evalueObject( iEvaluePosition & evaluePosition, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties ) const;
 * 	- bool evalueObject( iEvalueFibElement & evalueFibElement, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties, const list<char> & liCFibElementTyps );
 * 	- bool equal( const cFibElement & fibObject ) const;
 * 	- bool equalElement( const cFibElement & fibElement ) const;
 * 	- cFibElement *clone() const;
 * 	- cIf *copy( const unsignedIntFib iObjectIf=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementIf=0 ) const;
 * 	- bool storeXml( ostream &stream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream &stream ) const;
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
 * 	- cCondition * getCondition() const;
 * 	- bool setCondition( const cCondition & condition );
 * 	- cFibElement * getTrueCase();
 * 	- bool setTrueCase( cFibElement * fibObjectTrue, bool bDeleteOld=true );
 * 	- cFibElement * getFalseCase();
 * 	- bool setFalseCase( cFibElement * fibObjectFalse, bool bDeleteOld=true );
 *
 *
 * Conditions tested:
 * 	- cConditionTrue
 * 	- cConditionFalse
 * 	- cConditionOr
 * 	- cConditionAnd
 * 	- cConditionXor
 * 	- cConditionEqualInteger
 * 	- cConditionGreater
 * 	- cConditionLower
 *
 *
 * call: tIf [MAX_RAND_TEST_SIZE]
 *
 * parameters:
 * 	MAX_RAND_TEST_SIZE
 * 		A number for the random test sizes.
 * 		Standardvalue is 256.
 *
 * Test for:
 *
 * Methods for changing the structur of an Fib-object will be tested with
 * tFibElementStructur. Methods for Fib-objects will be tested with
 * Methods for storing and restoring will be tested in tFibElementStore.
 */
/*
History:
02.05.2011  Oesterholz  created
27.08.2011  Oesterholz  more conditions included
10.11.2011  Oesterholz  Bugfix: evalueObject() don't overwrite properties
09.10.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cIf.h"
#include "cPoint.h"
#include "cRoot.h"
#include "cProperty.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cTypeVariable.h"
#include "cTypeUnderFunction.h"
#include "cTypeInVar.h"
#include "cVectorProperty.h"
#include "cEvaluePositionList.h"
#include "cEvalueFibElementList.h"

#include "cConditionTrue.h"
#include "cConditionFalse.h"
#include "cConditionOr.h"
#include "cConditionAnd.h"
#include "cConditionXor.h"
#include "cConditionEqualInteger.h"
#include "cConditionGreater.h"
#include "cConditionLower.h"

#include "cFunctionValue.h"
#include "cFunctionVariable.h"


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
int testCondition( unsigned long &ulTestphase );
int testCases( unsigned long &ulTestphase );
int testVariable( unsigned long &ulTestphase );


//the size of the random tests
unsigned long MAX_RAND_TEST_SIZE = 256;


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	if ( argc >= 2 ){
		//one parameter given; read parameter iterations
		MAX_RAND_TEST_SIZE = atol( argv[1] );
		if ( MAX_RAND_TEST_SIZE < 1 ){
			MAX_RAND_TEST_SIZE = 1;
		}
	}
	
	cout<<endl<<"Running Test for cIf methods"<<endl;
	cout<<      "=================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testEvalueObject( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testCondition( ulTestphase );
	iReturn += testCases( ulTestphase );
	iReturn += testVariable( ulTestphase );

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the constructor of the cIf class.
 *
 * methods tested:
 * 	- cIf( const cCondition & inCondition, cFibElement * pInUnderobjectTrueCase = NULL, cFibElement * pInUnderobjectFalseCase = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- unsignedIntFib getNumberOfElement()
 * 	- bool hasUnderAllObjects() const;
 * 	- cCondition * getCondition() const;
 * 	- cFibElement * getTrueCase();
 * 	- cFibElement * getFalseCase();
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cIf"<<endl;

	cout<<"cConditionTrue conditionTrue;"<<endl;
	cConditionTrue conditionTrue;
	
	cout<<"cIf ifSimple( conditionTrue );"<<endl;
	cIf ifSimple( conditionTrue );

	//check the getType() methode from cIf
	if ( ifSimple.getType() == 'i' ){
	
		cout<<"The type of the if-element is correctly 'i' . "<<endl;
	}else{
		cerr<<"Error: The type of the if-element is "<<
			ifSimple.getType()<<" but should be 'i' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cIf
	if ( ! ifSimple.isValidFibElement() ){
	
		cout<<"The if-element is correctly not a correct if-element. "<<endl;
	}else{
		cerr<<"Error: The if-element is a correct if-element, but should not be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cIf
	if ( ! ifSimple.isMovable() ){
	
		cout<<"The if-element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The if-element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cIf
	if ( ifSimple.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib-element for the if-element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-element for the if-element is "<<
			ifSimple.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cIf
	if ( ifSimple.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib-element for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib-element for the if-element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cIf
	if ( ifSimple.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib-element for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-element for the if-element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cIf
	if ( ifSimple.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib-element for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-element for the if-element is "<<
			ifSimple.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cIf
	if ( *ifSimple.getCondition() == conditionTrue ){
	
		cout<<"The condition for the if-element is correctly equal to conditionTrue. "<<endl;
	}else{
		cerr<<"Error: The condition for the if-element is not equal to conditionTrue."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cIf
	if ( ifSimple.getCondition() != &conditionTrue ){
	
		cout<<"The condition for the if-element is correctly not the conditionTrue object. "<<endl;
	}else{
		cerr<<"Error: The condition for the if-element is the conditionTrue object."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the condition
	if ( ifSimple.getCondition()->getDefiningFibElement() == &ifSimple ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			ifSimple.getCondition()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			ifSimple.getCondition()->getDefiningFibElement() <<
			" but should be ifSimple="<< &ifSimple <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from the condition
	if ( ifSimple.getCondition()->getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			ifSimple.getCondition()->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			ifSimple.getCondition()->getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from the condition
	if ( ifSimple.getCondition()->isValid() ){
	
		cout<<"The condition is correctly not valid. "<<endl;
	}else{
		cerr<<"Error: The condition is valid."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cIf
	if ( ! ifSimple.hasUnderAllObjects()){
	
		cout<<"The if-element has correctly missing needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The if-element is not missing a underobject."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifSimple.getTrueCase() == NULL ){
	
		cout<<"The if-element has correctly no true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has an true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifSimple.getFalseCase() == NULL ){
	
		cout<<"The if-element has correctly no false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has an false case."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cIf with a differnt condition"<<endl;

	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;

	cout<<"cIf ifFalse( conditionFalse );"<<endl;
	cIf ifFalse( conditionFalse );

	//check the getType() methode from cIf
	if ( ifFalse.getType() == 'i' ){
	
		cout<<"The type of the if-element is correctly 'i' . "<<endl;
	}else{
		cerr<<"Error: The type of the if-element is "<<
			ifFalse.getType()<<" but should be 'i' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cIf
	if ( ! ifFalse.isValidFibElement() ){
	
		cout<<"The if-element is correctly not a correct if-element. "<<endl;
	}else{
		cerr<<"Error: The if-element is a correct if-element, but should not be."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cIf
	if ( ! ifFalse.isMovable() ){
	
		cout<<"The if-element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The if-element is movebel."<<endl;
		iReturn++;
	}
	//check the getNumberOfElement() methode from cIf
	if ( ifFalse.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib-element for the if-element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-element for the if-element is "<<
			ifFalse.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cIf
	if ( ifFalse.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib-element for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib-element for the if-element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cIf
	if ( ifFalse.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib-element for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-element for the if-element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cIf
	if ( ifFalse.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib-element for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-element for the if-element is "<<
			ifFalse.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cIf
	if ( *ifFalse.getCondition() == conditionFalse ){
	
		cout<<"The condition for the if-element is correctly equal to conditionFalse. "<<endl;
	}else{
		cerr<<"Error: The condition for the if-element is not equal to conditionFalse."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cIf
	if ( ifFalse.getCondition() != &conditionFalse ){
	
		cout<<"The condition for the if-element is correctly not the conditionFalse object. "<<endl;
	}else{
		cerr<<"Error: The condition for the if-element is the conditionFalse object."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the condition
	if ( ifFalse.getCondition()->getDefiningFibElement() == &ifFalse ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			ifFalse.getCondition()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			ifFalse.getCondition()->getDefiningFibElement() <<
			" but should be ifFalse="<< &ifFalse <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from the condition
	if ( ifFalse.getCondition()->getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			ifFalse.getCondition()->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			ifFalse.getCondition()->getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from the condition
	if ( ifFalse.getCondition()->isValid() ){
	
		cout<<"The condition is correctly not valid. "<<endl;
	}else{
		cerr<<"Error: The condition is valid."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cIf
	if ( ! ifFalse.hasUnderAllObjects()){
	
		cout<<"The if-element has correctly missing needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The if-element is not missing a underobject."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifFalse.getTrueCase() == NULL ){
	
		cout<<"The if-element has correctly no true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has an true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifFalse.getFalseCase() == NULL ){
	
		cout<<"The if-element has correctly no false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has an false case."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cIf with a superior Fib-element"<<endl;

	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	
	cout<<"cIf ifSup( conditionFalse, NULL, NULL, &rootSimple1 );"<<endl;
	cIf ifSup( conditionFalse, NULL, NULL, &rootSimple1 );

	//check the getType() methode from cIf
	if ( ifSup.getType() == 'i' ){
	
		cout<<"The type of the if-element is correctly 'i' . "<<endl;
	}else{
		cerr<<"Error: The type of the if-element is "<<
			ifSup.getType()<<" but should be 'i' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cIf
	if ( ! ifSup.isValidFibElement() ){
	
		cout<<"The if-element is correctly not a correct if-element. "<<endl;
	}else{
		cerr<<"Error: The if-element is a correct if-element, but should not be."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cIf
	if ( ! ifSup.isMovable() ){
	
		cout<<"The if-element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The if-element is movebel."<<endl;
		iReturn++;
	}
	//check the getNumberOfElement() methode from cIf
	if ( ifSup.getNumberOfElement() == 2 ){
	
		cout<<"The number of the Fib-element for the if-element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-element for the if-element is "<<
			ifSup.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cIf
	if ( ifSup.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib-element for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib-element for the if-element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cIf
	if ( ifSup.getFibElement( -1 ) == &rootSimple1 ){
	
		cout<<"The previous Fib-element for the if-element is correctly rootSimple1. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-element for the if-element is not rootSimple1."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cIf
	if ( ifSup.getSuperiorFibElement() == &rootSimple1 ){
	
		cout<<"The superior Fib-element for the if-element is correctly rootSimple1. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-element for the if-element is "<<
			ifSup.getSuperiorFibElement() << " and not rootSimple1."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cIf
	if ( *ifSup.getCondition() == conditionFalse ){
	
		cout<<"The condition for the if-element is correctly equal to conditionFalse. "<<endl;
	}else{
		cerr<<"Error: The condition for the if-element is not equal to conditionFalse."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cIf
	if ( ifSup.getCondition() != &conditionFalse ){
	
		cout<<"The condition for the if-element is correctly not the conditionFalse object. "<<endl;
	}else{
		cerr<<"Error: The condition for the if-element is the conditionFalse object."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the condition
	if ( ifSup.getCondition()->getDefiningFibElement() == &ifSup ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			ifSup.getCondition()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			ifSup.getCondition()->getDefiningFibElement() <<
			" but should be ifSup="<< &ifSup <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from the condition
	if ( ifSup.getCondition()->getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			ifSup.getCondition()->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			ifSup.getCondition()->getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from the condition
	if ( ifSup.getCondition()->isValid() ){
	
		cout<<"The condition is correctly not valid. "<<endl;
	}else{
		cerr<<"Error: The condition is valid."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cIf
	if ( ! ifSup.hasUnderAllObjects()){
	
		cout<<"The if-element has correctly missing needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The if-element is not missing a underobject."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifSup.getTrueCase() == NULL ){
	
		cout<<"The if-element has correctly no true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has an true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifSup.getFalseCase() == NULL ){
	
		cout<<"The if-element has correctly no false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has an false case."<<endl;
		iReturn++;
	}
	


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cIf with a next Fib-element as true case"<<endl;
	
	cout<<"cIf ifTrueCase( conditionFalse, &ifSimple );"<<endl;
	cIf ifTrueCase( conditionFalse, &ifSimple );


	//check the getType() methode from cIf
	if ( ifTrueCase.getType() == 'i' ){
	
		cout<<"The type of the if-element is correctly 'i' . "<<endl;
	}else{
		cerr<<"Error: The type of the if-element is "<<
			ifTrueCase.getType()<<" but should be 'i' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cIf
	if ( ! ifTrueCase.isValidFibElement() ){
	
		cout<<"The if-element is correctly not a correct if-element. "<<endl;
	}else{
		cerr<<"Error: The if-element is a correct if-element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cIf
	if ( ! ifTrueCase.isMovable() ){
	
		cout<<"The if-element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The if-element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cIf
	if ( ifTrueCase.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib-element for the if-element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-element for the if-element is "<<
			ifTrueCase.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cIf
	if ( ifTrueCase.getNextFibElement() == &ifSimple ){
	
		cout<<"The next/ main Fib-element for the if-element is correctly ifSimple. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib-element for the if-element is not ifSimple."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cIf
	if ( ifTrueCase.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib-element for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-element for the if-element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cIf
	if ( ifTrueCase.getSuperiorFibElement() == NULL){
	
		cout<<"The superior Fib-element for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-element for the if-element is "<<
			ifTrueCase.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cIf
	if ( *ifTrueCase.getCondition() == conditionFalse ){
	
		cout<<"The condition for the if-element is correctly equal to conditionFalse. "<<endl;
	}else{
		cerr<<"Error: The condition for the if-element is not equal to conditionFalse."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cIf
	if ( ifTrueCase.getCondition() != &conditionFalse ){
	
		cout<<"The condition for the if-element is correctly not the conditionFalse object. "<<endl;
	}else{
		cerr<<"Error: The condition for the if-element is the conditionFalse object."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the condition
	if ( ifTrueCase.getCondition()->getDefiningFibElement() == &ifTrueCase ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			ifTrueCase.getCondition()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			ifTrueCase.getCondition()->getDefiningFibElement() <<
			" but should be ifTrueCase="<< &ifTrueCase <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from the condition
	if ( ifTrueCase.getCondition()->getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			ifTrueCase.getCondition()->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			ifTrueCase.getCondition()->getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from the condition
	if ( ifTrueCase.getCondition()->isValid() ){
	
		cout<<"The condition is correctly not valid. "<<endl;
	}else{
		cerr<<"Error: The condition is valid."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cIf
	if ( ! ifTrueCase.hasUnderAllObjects()){
	
		cout<<"The if-element has correctly missing needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The if-element is not missing a underobject."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifTrueCase.getTrueCase() == &ifSimple ){
	
		cout<<"The if-element has correctly ifSimple as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not ifSimple as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifTrueCase.getFalseCase() == NULL ){
	
		cout<<"The if-element has correctly no false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has an false case."<<endl;
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cIf with a next Fib-element as false case"<<endl;
	
	cout<<"cIf ifFalseCase( conditionFalse, NULL, &ifFalse );"<<endl;
	cIf ifFalseCase( conditionFalse, NULL, &ifFalse );


	//check the getType() methode from cIf
	if ( ifFalseCase.getType() == 'i' ){
	
		cout<<"The type of the if-element is correctly 'i' . "<<endl;
	}else{
		cerr<<"Error: The type of the if-element is "<<
			ifFalseCase.getType()<<" but should be 'i' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cIf
	if ( ! ifFalseCase.isValidFibElement() ){
	
		cout<<"The if-element is correctly not a correct if-element. "<<endl;
	}else{
		cerr<<"Error: The if-element is a correct if-element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cIf
	if ( ! ifFalseCase.isMovable() ){
	
		cout<<"The if-element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The if-element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cIf
	if ( ifFalseCase.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib-element for the if-element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-element for the if-element is "<<
			ifFalseCase.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cIf
	if ( ifFalseCase.getNextFibElement() == &ifFalse ){
	
		cout<<"The next/ main Fib-element for the if-element is correctly ifFalse. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib-element for the if-element is not ifFalse."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cIf
	if ( ifFalseCase.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib-element for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-element for the if-element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cIf
	if ( ifFalseCase.getSuperiorFibElement() == NULL){
	
		cout<<"The superior Fib-element for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-element for the if-element is "<<
			ifFalseCase.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cIf
	if ( *ifFalseCase.getCondition() == conditionFalse ){
	
		cout<<"The condition for the if-element is correctly equal to conditionFalse. "<<endl;
	}else{
		cerr<<"Error: The condition for the if-element is not equal to conditionFalse."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cIf
	if ( ifFalseCase.getCondition() != &conditionFalse ){
	
		cout<<"The condition for the if-element is correctly not the conditionFalse object. "<<endl;
	}else{
		cerr<<"Error: The condition for the if-element is the conditionFalse object."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the condition
	if ( ifFalseCase.getCondition()->getDefiningFibElement() == &ifFalseCase ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			ifFalseCase.getCondition()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			ifFalseCase.getCondition()->getDefiningFibElement() <<
			" but should be ifFalseCase="<< &ifFalseCase <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from the condition
	if ( ifFalseCase.getCondition()->getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			ifFalseCase.getCondition()->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			ifFalseCase.getCondition()->getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from the condition
	if ( ifFalseCase.getCondition()->isValid() ){
	
		cout<<"The condition is correctly not valid. "<<endl;
	}else{
		cerr<<"Error: The condition is valid."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cIf
	if ( ! ifFalseCase.hasUnderAllObjects()){
	
		cout<<"The if-element has correctly missing needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The if-element is not missing a underobject."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifFalseCase.getTrueCase() == NULL ){
	
		cout<<"The if-element has correctly no true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has an true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifFalseCase.getFalseCase() == &ifFalse ){
	
		cout<<"The if-element has correctly ifFalse as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not ifFalse as the false case."<<endl;
		iReturn++;
	}
	


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cIf with true and false case"<<endl;
	
	cout<<"cIf ifTrueFalseCase( conditionFalse, &ifSimple, &ifFalse );"<<endl;
	cIf ifTrueFalseCase( conditionFalse, &ifSimple, &ifFalse );


	//check the getType() methode from cIf
	if ( ifTrueFalseCase.getType() == 'i' ){
	
		cout<<"The type of the if-element is correctly 'i' . "<<endl;
	}else{
		cerr<<"Error: The type of the if-element is "<<
			ifTrueFalseCase.getType()<<" but should be 'i' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cIf
	if ( ifTrueFalseCase.isValidFibElement() ){
	
		cout<<"The if-element is correctly a correct if-element. "<<endl;
	}else{
		cerr<<"Error: The if-element is not a correct if-element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cIf
	if ( ! ifTrueFalseCase.isMovable() ){
	
		cout<<"The if-element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The if-element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cIf
	if ( ifTrueFalseCase.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib-element for the if-element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-element for the if-element is "<<
			ifTrueFalseCase.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cIf
	if ( ifTrueFalseCase.getNextFibElement() == &ifSimple ){
	
		cout<<"The next/ main Fib-element for the if-element is correctly ifSimple. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib-element for the if-element is not ifSimple."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cIf
	if ( ifTrueFalseCase.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib-element for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-element for the if-element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cIf
	if ( ifTrueFalseCase.getSuperiorFibElement() == NULL){
	
		cout<<"The superior Fib-element for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-element for the if-element is "<<
			ifTrueFalseCase.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cIf
	if ( *ifTrueFalseCase.getCondition() == conditionFalse ){
	
		cout<<"The condition for the if-element is correctly equal to conditionFalse. "<<endl;
	}else{
		cerr<<"Error: The condition for the if-element is not equal to conditionFalse."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cIf
	if ( ifTrueFalseCase.getCondition() != &conditionFalse ){
	
		cout<<"The condition for the if-element is correctly not the conditionFalse object. "<<endl;
	}else{
		cerr<<"Error: The condition for the if-element is the conditionFalse object."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the condition
	if ( ifTrueFalseCase.getCondition()->getDefiningFibElement() == &ifTrueFalseCase ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			ifTrueFalseCase.getCondition()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			ifTrueFalseCase.getCondition()->getDefiningFibElement() <<
			" but should be ifTrueFalseCase="<< &ifTrueFalseCase <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from the condition
	if ( ifTrueFalseCase.getCondition()->getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			ifTrueFalseCase.getCondition()->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			ifTrueFalseCase.getCondition()->getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from the condition
	if ( ifTrueFalseCase.getCondition()->isValid() ){
	
		cout<<"The condition is correctly not valid. "<<endl;
	}else{
		cerr<<"Error: The condition is valid."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cIf
	if ( ! ifTrueFalseCase.hasUnderAllObjects() ){
	
		cout<<"The if-element has correctly not all underobjects. "<<endl;
	}else{
		cerr<<"Error: The if-element is not missing a underobject."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifTrueFalseCase.getTrueCase() == &ifSimple ){
	
		cout<<"The if-element has correctly ifSimple as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not ifSimple as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifTrueFalseCase.getFalseCase() == &ifFalse ){
	
		cout<<"The if-element has correctly ifFalse as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not ifFalse as the false case."<<endl;
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cIf with all parameters given"<<endl;
	
	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cPoint pointTrue;"<<endl;
	cPoint pointTrue;
	
	cout<<"cPoint pointFalse;"<<endl;
	cPoint pointFalse;

	cout<<"cIf ifFull( conditionTrue, &pointTrue, &pointFalse, &rootD2 );"<<endl;
	cIf ifFull( conditionTrue, &pointTrue, &pointFalse, &rootD2 );


	//check the getType() methode from cIf
	if ( ifFull.getType() == 'i' ){
	
		cout<<"The type of the if-element is correctly 'i' . "<<endl;
	}else{
		cerr<<"Error: The type of the if-element is "<<
			ifFull.getType()<<" but should be 'i' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cIf
	if ( ifFull.isValidFibElement() ){
	
		cout<<"The if-element is correctly a correct if-element. "<<endl;
	}else{
		cerr<<"Error: The if-element is not a correct if-element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cIf
	if ( ! ifFull.isMovable() ){
	
		cout<<"The if-element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The if-element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cIf
	if ( ifFull.getNumberOfElement() == 2 ){
	
		cout<<"The number of the Fib-element for the if-element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-element for the if-element is "<<
			ifFull.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cIf
	if ( ifFull.getNextFibElement() == &pointTrue ){
	
		cout<<"The next/ main Fib-element for the if-element is correctly ifSimple. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib-element for the if-element is not ifSimple."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cIf
	if ( ifFull.getFibElement( -1 ) == &rootD2 ){
	
		cout<<"The previous Fib-element for the if-element is correctly rootD2. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-element for the if-element is not rootD2."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cIf
	if ( ifFull.getSuperiorFibElement() == &rootD2 ){
	
		cout<<"The superior Fib-element for the if-element is correctly rootD2. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-element for the if-element is "<<
			ifFull.getSuperiorFibElement() << " and not rootD2."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cIf
	if ( *ifFull.getCondition() == conditionTrue ){
	
		cout<<"The condition for the if-element is correctly equal to conditionFalse. "<<endl;
	}else{
		cerr<<"Error: The condition for the if-element is not equal to conditionFalse."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cIf
	if ( ifFull.getCondition() != &conditionTrue ){
	
		cout<<"The condition for the if-element is correctly not the conditionFalse object. "<<endl;
	}else{
		cerr<<"Error: The condition for the if-element is the conditionFalse object."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the condition
	if ( ifFull.getCondition()->getDefiningFibElement() == &ifFull ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			ifFull.getCondition()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			ifFull.getCondition()->getDefiningFibElement() <<
			" but should be ifFull="<< &ifFull <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from the condition
	if ( ifFull.getCondition()->getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			ifFull.getCondition()->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			ifFull.getCondition()->getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from the condition
	if ( ifFull.getCondition()->isValid() ){
	
		cout<<"The condition is correctly not valid. "<<endl;
	}else{
		cerr<<"Error: The condition is valid."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cIf
	if ( ifFull.hasUnderAllObjects()){
	
		cout<<"The if-element has correctly all underobjects. "<<endl;
	}else{
		cerr<<"Error: The if-element is missing a underobject."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifFull.getTrueCase() == &pointTrue ){
	
		cout<<"The if-element has correctly pointTrue as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointTrue as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifFull.getFalseCase() == &pointFalse ){
	
		cout<<"The if-element has correctly pointFalse as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointFalse as the false case."<<endl;
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
		for ( list<cVectorProperty>::const_iterator itrListVector =
				liToGiveBackPropertyVectors.begin();
				itrListVector != liToGiveBackPropertyVectors.end();
				itrListVector++, uiListPosition++ ){
			
			list<cVectorProperty>::const_iterator itrFoundVector =
				find( liEvaluedProperties.begin(), liEvaluedProperties.end(), *itrListVector );
			
			if ( itrFoundVector == liEvaluedProperties.end() ){
				cerr<<"Error: The "<< uiListPosition <<
					"'th property couldn't be found in the evalued propertylist.  "<<endl;
				iReturn++;
				bPropertiesCorrect = false;
			}
		}
		uiListPosition = 1;
		for ( list<cVectorProperty>::const_iterator itrListVector =
				liEvaluedProperties.begin();
				itrListVector != liEvaluedProperties.end();
				itrListVector++, uiListPosition++ ){
			
			list<cVectorProperty>::const_iterator itrFoundVector =
				find ( liToGiveBackPropertyVectors.begin(), liToGiveBackPropertyVectors.end(),
				*itrListVector );
			
			if ( itrFoundVector == liToGiveBackPropertyVectors.end() ){
				cerr<<"Error: The "<< uiListPosition <<
					"'th property couldn't be found in the to evalue propertylist.  "<<endl;
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
 * This if compares the given evalued Fib-element lists.
 *
 * @param liEvaluedElements the first list with the Fib-elements and ther properties,
 * 	which are to be compared; this list sould be evalued
 * @param liToGiveBackElements the second list with the Fib-elements and ther properties,
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
				cout<<"The Fib-elements are equal."<<endl;
			}else{
				cerr<<"Error: The Fib-elements are not equal."<<endl;
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
 * This if compares the given evalued Fib-element lists.
 *
 * @param liEvaluedElements the first list with the Fib-elements and ther properties,
 * 	which are to be compared; this list sould be evalued
 * @param liToGiveBackElements the second list with the Fib-elements and ther properties,
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
				cout<<"The Fib-elements are equal."<<endl;
			}else{
				cerr<<"Error: The Fib-elements are not equal."<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cIf with a true condition"<<endl;

	cout<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );

	cout<<"cPoint pointTrue( &vecPositionE2 );"<<endl;
	cPoint pointTrue( &vecPositionE2 );
	
	cout<<"cPoint pointFalse( &vecPositionE2 );"<<endl;
	cPoint pointFalse( &vecPositionE2 );
	
	cout<<"cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );
	
	cout<<"cProperty propertyTrue( vecPropertyColorSW, &pointTrue );"<<endl;
	cProperty propertyTrue( vecPropertyColorSW, &pointTrue );
	
	cout<<"cProperty propertyFalse( vecPropertyColorSW, &pointFalse );"<<endl;
	cProperty propertyFalse( vecPropertyColorSW, &pointFalse );

	cout<<"cConditionTrue conditionTrue;"<<endl;
	cConditionTrue conditionTrue;

	cout<<"cIf ifTrue( conditionTrue, &propertyTrue, &propertyFalse );"<<endl;
	cIf ifTrue( conditionTrue, &propertyTrue, &propertyFalse );

	
	cout<<"pointTrue.getPosition()->setValue( 1, 1 );"<<endl;
	pointTrue.getPosition()->setValue( 1, 1 );
	cout<<"propertyTrue.getProperty()->setValue( 1, 1 );"<<endl;
	propertyTrue.getProperty()->setValue( 1, 1 );
	
	cout<<"pointFalse.getPosition()->setValue( 1, 2 );"<<endl;
	pointFalse.getPosition()->setValue( 1, 2 );
	cout<<"propertyFalse.getProperty()->setValue( 1, 2 );"<<endl;
	propertyFalse.getProperty()->setValue( 1, 2 );
	
	unsigned int uiPointsToEvalue = 1;
	
	unsigned int uiTimeNeeded = 1 + 5;

	//check the getTimeNeed() methode from cList
	cout<<"if1.getTimeNeed()"<<endl;
	if ( ifTrue.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			ifTrue.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cList
	cout<<"ifTrue.getTimeNeed( 4 )"<<endl;
	if ( ifTrue.getTimeNeed( 4 ) == 4 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 4 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			ifTrue.getTimeNeed( 4 ) <<", but should be "<< 4 <<" . "<<endl;
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
	
	cEvaluePositionList evaluePositionList;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"ifTrue.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bool bObjectEvalued = ifTrue.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"ifTrue.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = ifTrue.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
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
	liFibElementsToEvalue.push_back( make_pair( &pointTrue, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	cout<<"ifTrue.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = ifTrue.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"ifTrue.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = ifTrue.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cIf with a global property list given"<<endl;
	
	cout<<"cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );
	
	list< pair< const cVectorPosition*, list<cVectorProperty> > >::iterator
		itrPositionProperties = liPointsToEvalue.begin();
	itrPositionProperties->second.push_back( vecPropertyLayer );
	
	uiTimeNeeded = 1 + 5;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"ifTrue.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = ifTrue.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	list< pair< const cFibElement*, list<cVectorProperty> > >::iterator
		itrElementProperties = liFibElementsToEvalue.begin();
	itrElementProperties->second.push_back( vecPropertyLayer );

	cout<<"ifTrue.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = ifTrue.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cIf with a false condition"<<endl;

	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;

	cout<<"cIf ifFalse( conditionFalse, &propertyTrue, &propertyFalse );"<<endl;
	cIf ifFalse( conditionFalse, &propertyTrue, &propertyFalse );

		
	uiPointsToEvalue = 1;
	uiTimeNeeded = 1 + 5;

	//check the getTimeNeed() methode from cList
	cout<<"if1.getTimeNeed()"<<endl;
	if ( ifFalse.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			ifFalse.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cList
	cout<<"ifFalse.getTimeNeed( 4 )"<<endl;
	if ( ifFalse.getTimeNeed( 4 ) == 4 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 4 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			ifFalse.getTimeNeed( 4 ) <<", but should be "<< 4 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	
	//generate to evalue data
	liPointsToEvalue.clear();
	vecPositionE2V1.setValue( 1, 2 );
	vecPropertyColorSWV1.setValue( 1, 2 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V1, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"ifFalse.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = ifFalse.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"ifFalse.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = ifFalse.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
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
	liFibElementsToEvalue.push_back( make_pair( &pointFalse, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	cout<<"ifFalse.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = ifFalse.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"ifFalse.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = ifFalse.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cIf with a global property list given"<<endl;
	
	itrPositionProperties = liPointsToEvalue.begin();
	itrPositionProperties->second.push_back( vecPropertyLayer );
	
	uiTimeNeeded = 1 + 5;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"ifFalse.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = ifFalse.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	itrElementProperties = liFibElementsToEvalue.begin();
	itrElementProperties->second.push_back( vecPropertyLayer );

	cout<<"ifFalse.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = ifFalse.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cIf for non existing object point 1"<<endl;
	
	uiPointsToEvalue = 0;
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"ifTrue.evalueObject( evaluePositionList, 4,  liVecProperties );"<<endl;
	bObjectEvalued = ifTrue.evalueObject( evaluePositionList, 4,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The if was correctly not evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	liFibElementsToEvalue.clear();
	cout<<"ifTrue.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = ifTrue.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The if was correctly not evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cIf when returnvalue is false"<<endl;

	uiPointsToEvalue = 1;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	cout<<"ifTrue.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = ifTrue.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The if was correctly evalued. with result false "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 0;
	cout<<"ifTrue.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = ifTrue.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The if was correctly evalued. with result false "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cIf with differnt elements to evalue"<<endl;

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"liCFibElementTyps.push_back( 'y' );"<<endl;
	liCFibElementTyps.push_back( 'y' );
	liVecProperties.clear();
	liFibElementsToEvalue.clear();
	uiPointsToEvalue = 1;
	for ( unsigned int uiEvaluesElement = 0;
			uiEvaluesElement < uiPointsToEvalue; uiEvaluesElement++ ){
		liFibElementsToEvalue.push_back(
			make_pair( &propertyTrue, list<cVectorProperty>() ) );
	}
	cout<<"ifTrue.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = ifTrue.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
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
	cout<<"liCFibElementTyps.push_back( 'i' );"<<endl;
	liCFibElementTyps.push_back( 'i' );
	uiPointsToEvalue = 1;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &ifTrue, list<cVectorProperty>() ) );
	cout<<"ifTrue.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = ifTrue.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
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
	cout<<"liCFibElementTyps.push_back( 'i' );"<<endl;
	liCFibElementTyps.push_back( 'i' );
	cout<<"liCFibElementTyps.push_back( 'm' );"<<endl;
	liCFibElementTyps.push_back( 'm' );
	uiPointsToEvalue = 1;
	cout<<"ifTrue.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = ifTrue.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The if was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() if was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() if was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );



	return iReturn;
}



/**
 * This method tests the equal() method of two given Fib-objects which are
 * equal.
 *
 * @param fibObject1 the first Fib-object to compare
 * @param szNameObject1 the name of the first Fib-object to compare
 * @param fibObject2 the secound Fib-object to compare to
 * @param szNameObject2 the name of the secound Fib-object to compare
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
	
		cout<<"The "<<szNameObject1<<" Fib-element is equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" Fib-element is not equal to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}

	return iReturn;
}

/**
 * This method tests the equal() method of two given Fib-objects which are
 * not equal.
 *
 * @param fibObject1 the first Fib-object to compare
 * @param szNameObject1 the name of the first Fib-object to compare
 * @param fibObject2 the secound Fib-object to compare to
 * @param szNameObject2 the name of the secound Fib-object to compare
 * @param bEqualElement if true the highest Fib-elements of the
 * 	Fib-objects are equal, else ther are not equal
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
	
		cout<<"The "<<szNameObject1<<" Fib-element is "<<
			(bEqualElement?"":"not") <<" equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" Fib-element is "<<
			(bEqualElement?"not":"") <<" equal to "<<
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing equal methods for if-elements"<<endl;

	cout<<endl<<"Creating ifobjects objects to compare: "<<endl<<endl;

	//if with a empty ifvector
	cout<<"cConditionTrue conditionTrue1;"<<endl;
	cConditionTrue conditionTrue1;
	cout<<"cIf ifTrue1( conditionTrue1 );"<<endl;
	cIf ifTrue1( conditionTrue1 );

	cout<<"cConditionTrue conditionTrue2;"<<endl;
	cConditionTrue conditionTrue2;
	cout<<"cIf ifTrue2( conditionTrue2 );"<<endl;
	cIf ifTrue2( conditionTrue2 );

	//if with one changed condition
	cout<<"cConditionFalse conditionFalse1;"<<endl;
	cConditionFalse conditionFalse1;
	cout<<"cIf ifFalse( conditionFalse1 );"<<endl;
	cIf ifFalse( conditionFalse1 );

	
	//if with supperior element
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	
	cout<<"cIf ifSup( conditionTrue1, NULL, NULL, &rootSimple1 );"<<endl;
	cIf ifSup( conditionTrue1, NULL, NULL, &rootSimple1 );

	//if in Fib-element structur
	cout<<"cPoint poinNextTrue;"<<endl;
	cPoint poinNextTrue;
	cout<<"cIf ifTrueCase( conditionTrue1, &poinNextTrue );"<<endl;
	cIf ifTrueCase( conditionTrue1, &poinNextTrue );

	cout<<"cPoint poinNextFalse;"<<endl;
	cPoint poinNextFalse;
	cout<<"cIf ifFalseCase( conditionTrue1, NULL, &poinNextFalse );"<<endl;
	cIf ifFalseCase( conditionTrue1, NULL, &poinNextFalse );



	cout<<"cPoint poinNext2;"<<endl;
	cPoint poinNext2;
	cout<<"cPoint poinNext3;"<<endl;
	cPoint poinNext3;
	cout<<"cRoot root1;"<<flush<<endl;
	cRoot root1;
	
	cout<<"cIf ifFull( conditionTrue1, &poinNext2, &poinNext3, &root1 );"<<endl;
	cIf ifFull( conditionTrue1, &poinNext2, &poinNext3, &root1 );


	//ifs with a contained pointelement
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cPoint point2;"<<endl;
	cPoint point2;
	cout<<"cIf ifPoint1( conditionTrue1, &point1, &point2 );"<<endl;
	cIf ifPoint1( conditionTrue1, &point1, &point2 );

	cout<<"cVectorPosition vecPosition;"<<endl;
	cVectorPosition vecPosition;
	cout<<"cPoint pointPos( &vecPosition );"<<endl;
	cPoint pointPos( &vecPosition );
	cout<<"cIf ifPoint2( conditionTrue1, &pointPos );"<<endl;
	cIf ifPoint2( conditionTrue1, &pointPos );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with ifTrue1
	cFibElement *actualObject = &ifTrue1;
	string szActualObjectName = "ifTrue1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifTrue1, "ifTrue1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifTrue2, "ifTrue2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalse, "ifFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalseCase, "ifFalseCase", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifSup, "ifSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrueCase, "ifTrueCase", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFull, "ifFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint1, "ifPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint2, "ifPoint2", true );

	//compare with ifTrue2
	actualObject = &ifTrue2;
	szActualObjectName = "ifTrue2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifTrue1, "ifTrue1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifTrue2, "ifTrue2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalse, "ifFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalseCase, "ifFalseCase", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifSup, "ifSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrueCase, "ifTrueCase", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFull, "ifFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint1, "ifPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint2, "ifPoint2", true );

	//compare with ifFalse
	actualObject = &ifFalse;
	szActualObjectName = "ifFalse";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrue1, "ifTrue1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrue2, "ifTrue2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifFalse, "ifFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalseCase, "ifFalseCase" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifSup, "ifSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrueCase, "ifTrueCase" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFull, "ifFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint1, "ifPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint2, "ifPoint2" );

	//compare with ifFalseCase
	actualObject = &ifFalseCase;
	szActualObjectName = "ifFalseCase";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrue1, "ifTrue1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrue2, "ifTrue2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalse, "ifFalse" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifFalseCase, "ifFalseCase" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifSup, "ifSup", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrueCase, "ifTrueCase", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFull, "ifFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint1, "ifPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint2, "ifPoint2", true );

	//compare with ifSup
	actualObject = &ifSup;
	szActualObjectName = "ifSup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifTrue1, "ifTrue1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifTrue2, "ifTrue2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalse, "ifFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalseCase, "ifFalseCase", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifSup, "ifSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrueCase, "ifTrueCase", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFull, "ifFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint1, "ifPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint2, "ifPoint2", true );

	//compare with ifTrueCase
	actualObject = &ifTrueCase;
	szActualObjectName = "ifTrueCase";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrue1, "ifTrue1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrue2, "ifTrue2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalse, "ifFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalseCase, "ifFalseCase", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifSup, "ifSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifTrueCase, "ifTrueCase" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFull, "ifFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint1, "ifPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint2, "ifPoint2", true );

	//compare with ifFull
	actualObject = &ifFull;
	szActualObjectName = "ifFull";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrue1, "ifTrue1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrue2, "ifTrue2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalse, "ifFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalseCase, "ifFalseCase", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifSup, "ifSup", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrueCase, "ifTrueCase", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifFull, "ifFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifPoint1, "ifPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint2, "ifPoint2", true );

	//compare with ifPoint1
	actualObject = &ifPoint1;
	szActualObjectName = "ifPoint1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrue1, "ifTrue1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrue2, "ifTrue2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalse, "ifFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalseCase, "ifFalseCase", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifSup, "ifSup", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrueCase, "ifTrueCase", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifFull, "ifFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifPoint1, "ifPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint2, "ifPoint2", true );

	//compare with ifPoint2
	actualObject = &ifPoint2;
	szActualObjectName = "ifPoint2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrue1, "ifTrue1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrue2, "ifTrue2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalse, "ifFalse" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFalseCase, "ifFalseCase", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifSup, "ifSup", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifTrueCase, "ifTrueCase", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifFull, "ifFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, ifPoint1, "ifPoint1", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, ifPoint2, "ifPoint2" );


	return iReturn;
}



/**
 * This method tests the equal() method of two given Fib-objects, which are
 * equal.
 * It also compares the superior, next and previous Fib-element pointers.
 *
 * @param fibObject1 the first Fib-object to compare
 * @param szNameObject1 the name of the first Fib-object to compare
 * @param fibObject2 the secound Fib-object to compare to
 * @param szNameObject2 the name of the secound Fib-object to compare
 * @param isClone if true the Fib-object is a clone (the pointers are not equal)
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualObjectsStructur(
		const cFibElement &fibObject1, const string &szNameObject1,
		const cFibElement &fibObject2, const string &szNameObject2, bool isClone=false ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	iReturn += testCompareTwoEqualObjects( fibObject1, szNameObject1, fibObject2, szNameObject2 );
	
	if ( ! isClone ){
		//check the getNextFibElement() methode from cIf
		if ( const_cast<cFibElement*>(&fibObject1)->getNextFibElement() ==
				const_cast<cFibElement*>(&fibObject2)->getNextFibElement() ){
		
			cout<<"The next/ main Fib-elementpointer for the if-element are correctly equal. "<<endl;
		}else{
			cerr<<"Error: The next/ main Fib-elementpointer for the if-element are not equal."<<endl;
			iReturn++;
		}
	
		//check the getFibElement() methode from cIf
		if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) ==
				const_cast<cFibElement*>(&fibObject2)->getFibElement( -1 ) ){
		
			cout<<"The previous Fib-elementpointer for the if-element are correctly equal. "<<endl;
		}else{
			cerr<<"Error: The previous Fib-elementpointer for the if-element are not equal."<<endl;
			iReturn++;
		}
		//check the getSuperiorFibElement() methode from cIf
		if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() ==
				const_cast<cFibElement*>(&fibObject2)->getSuperiorFibElement() ){
		
			cout<<"The superior Fib-elementpointer for the if-element are correctly equal. "<<endl;
		}else{
			cerr<<"Error: The superior Fib-elementpointer for the if-element are not equal."<<endl;
			iReturn++;
		}
	}
	
	return iReturn;
}


/**
 * This method tests if the given Fib-element is not conected to other
 * Fib-elements.
 *
 * @param fibObject1 the Fib-element to check
 * @return the number of errors occured in the test
 */
int testNotConnectedFibElement( const cFibElement &fibObject1 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	//check the getNextFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getNumberOfElements() == 1 ){
	
		cout<<"The Fib-object includes just one Fib-element. "<<endl;
	}else{
		cerr<<"Error: The Fib-object includes just not one Fib-element, but "<<
			const_cast<cFibElement*>(&fibObject1)->getNumberOfElements() <<" ."<<endl;
		iReturn++;
	}
	
	//check the getNextFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib-elementpointer for the point -elements is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib-elementpointer for the point -elements is not NULL."<<endl;
		iReturn++;
	}
	//check the getFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib-elementpointer for the point -elements is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-elementpointer for the point -elements is not NULL."<<endl;
		iReturn++;
	}
	
	//check the getSuperiorFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib-elementpointer for the point -elements is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-elementpointer for the point -elements is not NULL."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the copy methods and copyconstructor of the cIf class.
 *
 * methods tested:
 * 	- cIf( const cIf &ifElement );
 * 	- cFibElement *clone() const;
 * 	- cIf *copy( const unsignedIntFib iObjectIf=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementIf=0 ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a simple cIf"<<endl;

	cout<<"cConditionTrue conditionTrue;"<<endl;
	cConditionTrue conditionTrue;
	cout<<"cIf ifSimple( conditionTrue );"<<endl;
	cIf ifSimple( conditionTrue );

	cout<<"cIf ifSimpleCopyConstruct( ifSimple );"<<endl;
	cIf ifSimpleCopyConstruct( ifSimple );

	iReturn += testCompareTwoEqualObjectsStructur( ifSimpleCopyConstruct, "ifSimpleCopyConstruct", ifSimple, "ifSimple" );

	cout<<"cFibElement * pIfSimpleClone = ifSimple.clone();"<<endl;
	cFibElement * pIfSimpleClone = ifSimple.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pIfSimpleClone, "pIfSimpleClone", ifSimple, "ifSimple" );
	delete pIfSimpleClone;

	cout<<"cFibElement * pIfSimpleCopy = ifSimple.copy();"<<endl;
	cFibElement * pIfSimpleCopy = ifSimple.copy();

	iReturn += testCompareTwoEqualObjectsStructur( *pIfSimpleCopy, "pIfSimpleCopy", ifSimple, "ifSimple" );
	delete pIfSimpleCopy;

	cout<<"cFibElement * pIfSimpleCopyElement = ifSimple.copyElement();"<<endl;
	cFibElement * pIfSimpleCopyElement = ifSimple.copyElement();

	iReturn += testCompareTwoEqualObjectsStructur( *pIfSimpleCopyElement, "pIfSimpleCopyElement", ifSimple, "ifSimple" );
	delete pIfSimpleCopyElement;
	


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying for a other object or elementpoint"<<endl;

	cout<<"cFibElement * pIfSimpleNoCopy = ifSimple.copy( 1 );"<<endl;
	cFibElement * pIfSimpleNoCopy = ifSimple.copy( 1 );

	if ( pIfSimpleNoCopy == NULL ){
	
		cout<<"The cIf was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cIf was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pIfSimpleNoCopy;
	}

	cout<<"cFibElement * pIfSimpleNoCopyElement = ifSimple.copyElement( 'i', 2 );"<<endl;
	cFibElement * pIfSimpleNoCopyElement = ifSimple.copyElement( 'i', 2 );

	if ( pIfSimpleNoCopyElement == NULL ){
	
		cout<<"The cIf -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cIf -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pIfSimpleNoCopyElement;
	}

	cout<<"pIfSimpleNoCopyElement = ifSimple.copyElement( 'u', 2 );"<<endl;
	pIfSimpleNoCopyElement = ifSimple.copyElement( 'u', 2 );

	if ( pIfSimpleNoCopyElement == NULL ){
	
		cout<<"The cIf -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cIf -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pIfSimpleNoCopyElement;
	}

	cout<<"pIfSimpleNoCopyElement = ifSimple.copyElement( 'r', 1 );"<<endl;
	pIfSimpleNoCopyElement = ifSimple.copyElement( 'r', 1 );

	if ( pIfSimpleNoCopyElement == NULL ){
	
		cout<<"The cIf -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cIf -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pIfSimpleNoCopyElement;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cIf with all members set"<<endl;

	//if in Fib-element structur
	cout<<"cPoint poinTrue;"<<endl;
	cPoint poinTrue;
	cout<<"cPoint poinFalse;"<<endl;
	cPoint poinFalse;

	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	

	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;

	cout<<"cIf if2E2( conditionFalse, &poinTrue, &poinFalse, &rootD2 );"<<endl;
	cIf if2E2( conditionFalse, &poinTrue, &poinFalse, &rootD2 );


	cout<<"cIf if2E2CopyConstruct( if2E2 );"<<endl;
	cIf if2E2CopyConstruct( if2E2 );

	if ( if2E2CopyConstruct.equalElement( if2E2 ) ){

		cout<<"The if2E2CopyConstruct Fib-element is equal to if2E2. "<<endl;
	}else{
		cerr<<"Error: The if2E2CopyConstruct Fib-element is not equal to if2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( if2E2CopyConstruct );

	cout<<"cFibElement * pIf2E2Copy = if2E2.copy();"<<endl;
	cFibElement * pIf2E2Copy = if2E2.copy();
	iReturn += testCompareTwoEqualObjects( *pIf2E2Copy, "pIf2E2Copy", if2E2, "if2E2" );
	//check the getFibElement() methode from cIf
	if ( NULL == pIf2E2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous Fib-elementpointer for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-elementpointer for the if-element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cIf
	if ( NULL == pIf2E2Copy->getSuperiorFibElement() ){
	
		cout<<"The superior Fib-elementpointer for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-elementpointer for the if-element is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( pIf2E2Copy );

	cout<<"cFibElement * pIf2E2CopyElement = if2E2.copyElement( 'u', 1 );"<<endl;
	cFibElement * pIf2E2CopyElement = if2E2.copyElement( 'u', 1 );

	if ( pIf2E2CopyElement->equalElement( if2E2 ) ){
	
		cout<<"The pIf2E2CopyElement Fib-element is equal to if2E2. "<<endl;
	}else{
		cerr<<"Error: The pIf2E2CopyElement Fib-element is not equal to if2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pIf2E2CopyElement );
	delete pIf2E2CopyElement;


	cout<<"cFibElement * pIf2E2Clone = if2E2.clone();"<<endl;
	cFibElement * pIf2E2Clone = if2E2.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pIf2E2Clone, "pIf2E2Clone", rootD2, "rootD2", true );
	pIf2E2Clone->deleteObject();



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a limb with more then one if-element and pointelement"<<endl;

	//a limb with more then one if-element and pointelement
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cIf if3( conditionTrue );"<<endl;
	cIf if3( conditionTrue );
	
	cout<<"cIf if1Obj2( conditionFalse, NULL, &if3 );"<<endl;
	cIf if1Obj2( conditionFalse, NULL, &if3 );


	cout<<endl<<"cIf if1Obj2CopyConstruct( if1Obj2 );"<<endl;
	cIf if1Obj2CopyConstruct( if1Obj2 );

	if ( if1Obj2CopyConstruct.equalElement( if1Obj2 ) ){
	
		cout<<"The if1Obj2CopyConstruct Fib-element is equal to if1Obj2. "<<endl;
	}else{
		cerr<<"Error: The if1Obj2CopyConstruct Fib-element is not equal to if1Obj2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( if1Obj2CopyConstruct );

	cout<<"cFibElement * if1Obj2Copy = if1Obj2.copy();"<<endl;
	cFibElement * if1Obj2Copy = if1Obj2.copy();

	iReturn += testCompareTwoEqualObjects(
		*if1Obj2Copy, "if1Obj2Copy",
		if1Obj2, "if1Obj2" );
	//check the getFibElement() methode from cIf
	if ( NULL == if1Obj2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous Fib-elementpointer for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-elementpointer for the if-element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cIf
	if ( if1Obj2Copy->getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib-elementpointer for the if-element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-elementpointer for the if-element is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( if1Obj2Copy );

	cout<<"cFibElement * pIf1Obj2 = if1Obj2.copyElement();"<<endl;
	cFibElement * pIf1Obj2 = if1Obj2.copyElement();

	if ( pIf1Obj2->equalElement( if1Obj2 ) ){
	
		cout<<"The pIf1Obj2 Fib-element is equal to if1Obj2. "<<endl;
	}else{
		cerr<<"Error: The pIf1Obj2 Fib-element is not equal to if1Obj2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pIf1Obj2 );
	delete pIf1Obj2;


	cout<<"cFibElement * pIf1Obj2Clone = if1Obj2.clone();"<<endl;
	cFibElement * pIf1Obj2Clone = if1Obj2.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pIf1Obj2Clone, "pIf1Obj2Clone", if1Obj2, "if1Obj2", true );
	pIf1Obj2Clone->deleteObject();



	return iReturn;
}



/**
 * This method tests a in the xml -format stored cIf.
 * The condition of the cIf should be a value condition
 * ( cConditionTrue ).
 *
 * @param szFilename the name of the file wher the cFibVector is stored
 * @param bHasUnderObjects if true the if element has two underobjects
 * 	(true and false case), else it has non
 * @return the number of errors occured in the test
 */
int testXmlIf( const string szFilename, bool bHasUnderObjects=false ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cIf:"<<endl;
	
	TiXmlDocument xmlDocConditionTrue( szFilename );
	bool loadOkay = xmlDocConditionTrue.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocConditionTrue );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();
		
		const string szIfElementName = "if";
		if ( szElementName == szIfElementName ){
			cout<<"The root element is correctly named \""<< szIfElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szIfElementName <<"\"."<<endl;
			iReturn++;
		}
		
	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	TiXmlElement * pXmlIfElement = pXmlElement;
	
	TiXmlHandle xmlHandleCondition = TiXmlHandle( pXmlElement );
	TiXmlElement * pXmlCondition = xmlHandleCondition.FirstChild().Element();
	
	if ( pXmlCondition ) {
		string szElementName = pXmlCondition->Value();

		if ( szElementName == "condition" ){
			cout<<"The subelement is correctly named \"condition\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the subelement is "<< szElementName <<" and not \"condition\"."<<endl;
			iReturn++;
		}
		
		xmlHandleCondition = TiXmlHandle( pXmlCondition );
		pXmlCondition = xmlHandleCondition.FirstChild().Element();
		
		if ( pXmlCondition ){
			string szElementName = pXmlCondition->Value();
	
			if ( szElementName == "true" ){
				cout<<"The subelement is correctly named \"true\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the subelement is "<< szElementName <<" and not \"true\"."<<endl;
				iReturn++;
			}
	
		}else{// pXmlUnderIf == NULL
			cerr<<"Error: No condition 2 handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
			return iReturn;
		}

	}else{// pXmlUnderIf == NULL
		cerr<<"Error: No condition handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	if ( bHasUnderObjects ){
		
		TiXmlHandle xmlHandleUnderObject = TiXmlHandle( pXmlIfElement );
		TiXmlElement * pXmlUnderObject = xmlHandleUnderObject.FirstChild().Element();
		
		pXmlUnderObject = pXmlUnderObject->NextSiblingElement();
		//check the under objects
		if ( pXmlUnderObject ) {
			
			string szElementName = pXmlUnderObject->Value();
	
			if ( szElementName == "point" ){
				cout<<"The name of true case underobject is correctly named \"point\". "<<endl;
			
			}else{
				cerr<<"Error: The name true case underobject is "<< szElementName <<" and not \"point\"."<<endl;
				iReturn++;
			}
			
		}else{// pXmlUnderIf == NULL
			cerr<<"Error: No true case handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
			return iReturn;
		}
		pXmlUnderObject = pXmlUnderObject->NextSiblingElement();
		//check the under objects
		if ( pXmlUnderObject ) {
			
			string szElementName = pXmlUnderObject->Value();
	
			if ( szElementName == "point" ){
				cout<<"The name of false case underobject is correctly named \"point\". "<<endl;
			
			}else{
				cerr<<"Error: The name false case underobject is "<< szElementName <<" and not \"point\"."<<endl;
				iReturn++;
			}
			
		}else{// pXmlUnderIf == NULL
			cerr<<"Error: No false case handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
			return iReturn;
		}
		
	}
	
	return iReturn;
}



/**
 * This method tests the storeXml() method of the cIf class.
 * Just storing properties with no underobjects is tested.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an if with an true condition"<<endl;

	cout<<"cConditionTrue conditionTrue;"<<endl;
	cConditionTrue conditionTrue;
	cout<<"cIf if1( conditionTrue );"<<endl;
	cIf if1( conditionTrue );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlIfFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "if1.xml" );
	ofstream * pFileVectorPostion = new ofstream( szXmlIfFileName );
	
	bool bStoreSuccesfull = if1.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cIf was stored successfull to the file \""<< szXmlIfFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cIf to the file \""<< szXmlIfFileName <<"\" failed."<<endl;
		iReturn++;
	}	
	iReturn += testXmlIf( szXmlIfFileName );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an if with two underobjects"<<endl;

	cout<<"cPoint pointTrue;"<<flush<<endl;
	cPoint pointTrue;
	cout<<"cPoint pointFalse;"<<flush<<endl;
	cPoint pointFalse;

	cout<<"cIf ifUnderObj( conditionTrue, &pointTrue, &pointFalse );"<<endl;
	cIf ifUnderObj( conditionTrue, &pointTrue, &pointFalse );
	
	szFileNameBuffer[0] = 0;
	szXmlIfFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "ifUnderObj.xml" );
	pFileVectorPostion = new ofstream( szXmlIfFileName );
	
	bStoreSuccesfull = ifUnderObj.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cIf was stored successfull to the file \""<< szXmlIfFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cIf to the file \""<< szXmlIfFileName <<"\" failed."<<endl;
		iReturn++;
	}	
	iReturn += testXmlIf( szXmlIfFileName, true );
	


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

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method one if-element"<<endl;

	cout<<"cPoint pointTrue;"<<flush<<endl;
	cPoint pointTrue;
	cout<<"cPoint pointFalse;"<<flush<<endl;
	cPoint pointFalse;

	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	
	cout<<"cConditionTrue conditionTrue;"<<endl;
	cConditionTrue conditionTrue;
	cout<<"cIf if1( conditionTrue, &pointTrue, &pointFalse, &root );"<<endl;
	cIf if1( conditionTrue, &pointTrue, &pointFalse, &root );

	//test get compressed size
	unsigned int uiCompressedSize = 4 + 4 + 2 * 5;
	if ( (unsigned int)(if1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			if1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "if1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bool bStoreSuccesfull = if1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cIf1[] = { (char)0xFC, (char)0x52, (char)0x02 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cIf1, 3 );


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with false condition"<<endl;

	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;
	
	cout<<"if1.setCondition( conditionFalse );"<<endl;
	if1.setCondition( conditionFalse );
	
	//test get compressed size
	uiCompressedSize = 4 + 4 + 2 * 5;
	if ( (unsigned int)(if1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			if1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "ifFalse.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = if1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char szIfFalse[] = { (char)0x0C, (char)0x52, (char)0x02 };
	iReturn += compareBytsWithFile( szFileNameBuffer, szIfFalse, 3 );


	return iReturn;
}




/**
 * This function tests the condition methods of the class.
 *
 * methods tested:
 * 	- cCondition * getCondition() const;
 * 	- bool setCondition( const cCondition & condition );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCondition( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the condition -methods"<<endl;
	
	cout<<"cConditionTrue conditionTrue;"<<endl;
	cConditionTrue conditionTrue;
	cout<<"cIf if1( conditionTrue );"<<endl;
	cIf if1( conditionTrue );
	
	//check the getCondition() methode from cIf
	if ( if1.getCondition() != NULL ){
	
		if ( if1.getCondition() != &conditionTrue ){
		
			cout<<"The condition for the if-element is correctly not the conditionTrue object. "<<endl;
		}else{
			cerr<<"Error: The condition for the if-element is the conditionTrue object."<<endl;
			iReturn++;
		}
		if ( conditionTrue == *(if1.getCondition()) ){
		
			cout<<"The if has the correct condition conditionTrue. "<<endl;
		}else{
			cerr<<"Error: The if has a not the correct condition conditionTrue. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The if has a no condition (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the condition
	if ( if1.getCondition()->getDefiningFibElement() == &if1 ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			if1.getCondition()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			if1.getCondition()->getDefiningFibElement() <<
			" but should be if1="<< &if1 <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from the condition
	if ( if1.getCondition()->getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			if1.getCondition()->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			if1.getCondition()->getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}


	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;
	cout<<"if1.setCondition( conditionFalse );"<<endl;
	if1.setCondition( conditionFalse );

	//check the getCondition() methode from cIf
	if ( if1.getCondition() != NULL ){
	
		if ( if1.getCondition() != &conditionFalse ){
		
			cout<<"The condition for the if-element is correctly not the conditionFalse object. "<<endl;
		}else{
			cerr<<"Error: The condition for the if-element is the conditionFalse object."<<endl;
			iReturn++;
		}
		if ( conditionFalse == *(if1.getCondition()) ){
		
			cout<<"The if has the correct condition conditionFalse. "<<endl;
		}else{
			cerr<<"Error: The if has a not the correct condition conditionFalse. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The if has a no condition (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the condition
	if ( if1.getCondition()->getDefiningFibElement() == &if1 ){
	
		cout<<"The condition defining Fib-element is correctly "<<
			if1.getCondition()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition defining Fib-element is "<<
			if1.getCondition()->getDefiningFibElement() <<
			" but should be if1="<< &if1 <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorCondition() methode from the condition
	if ( if1.getCondition()->getSuperiorCondition() == NULL ){
	
		cout<<"The superior condition of the condition correctly "<<
			if1.getCondition()->getSuperiorCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior condition of the condition is "<<
			if1.getCondition()->getSuperiorCondition() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}

	
	cout<<"cPoint pointTrue;"<<endl;
	cPoint pointTrue;
	cout<<"cPoint pointFalse;"<<endl;
	cPoint pointFalse;
	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	cout<<"root.setNumberOfInputVariables( 10 );"<<endl;
	root.setNumberOfInputVariables( 10 );
	vector< cFibVariable * > vecVariablesDef;
	cout<<"pVariable1 = root.getInputVariable( 1 );"<<endl;
	vecVariablesDef.push_back( root.getInputVariable( 1 ) );
	cout<<"pVariable2 = root.getInputVariable( 2 );"<<endl;
	vecVariablesDef.push_back( root.getInputVariable( 2 ) );
	cout<<"pVariable3 = root.getInputVariable( 3 );"<<endl;
	vecVariablesDef.push_back( root.getInputVariable( 3 ) );
	cout<<"pVariable4 = root.getInputVariable( 4 );"<<endl;
	vecVariablesDef.push_back( root.getInputVariable( 4 ) );

	cout<<"cRoot rootNDef;"<<flush<<endl;
	cRoot rootNDef;
	cout<<"rootNDef.setNumberOfInputVariables( 10 );"<<endl;
	rootNDef.setNumberOfInputVariables( 10 );
	vector< cFibVariable * > vecVariablesNDef;
	cout<<"pVariable1 = rootNDef.getInputVariable( 1 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 1 ) );
	cout<<"pVariable2 = rootNDef.getInputVariable( 2 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 2 ) );
	cout<<"pVariable3 = rootNDef.getInputVariable( 3 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 3 ) );
	cout<<"pVariable4 = rootNDef.getInputVariable( 4 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 4 ) );


	cout<<"cIf ifFull( conditionTrue, &pointTrue, &pointFalse, &root );"<<endl;
	cIf ifFull( conditionTrue, &pointTrue, &pointFalse, &root );
	
	//if1, ifFull, ifNew
	cIf * pIfToTest = NULL;
	bool bDeleteIf = false;
	cCondition * pCondition = NULL;
	string szCondition;
	//if the Condition if valid
	bool bValid;
	//if the fib-element if valid
	bool bValidElement;
	set< cFibVariable * > setCorrectUsedVariables;
	for ( unsigned long uiIteration = 1; uiIteration <= MAX_RAND_TEST_SIZE; uiIteration++ ){
		
		//choose condition to test
		unsigned int uiCondition = rand() % 8 + 1;
		setCorrectUsedVariables.clear();
		
		switch ( uiCondition ){
			case 1://condition true
				pCondition = new cConditionTrue();
				szCondition = "true";
				bValid = true;
			break;
			case 2://condition false
				pCondition = new cConditionFalse();
				szCondition = "true condition";
				bValid = true;
			break;
			
			case 3://condition or
			case 4://condition and
			case 5:{//condition xor
				bValid = true;
				//create first subcondition
				cCondition * pSubcondition1 = NULL;
				string szSubcondition1;
				switch ( rand() % 3 ){
					case 0://true subcondition
						pSubcondition1 = new cConditionTrue();
						szSubcondition1 = "true";
					break;
					case 1://false subcondition
						pSubcondition1 = new cConditionFalse();
						szSubcondition1 = "false";
					break;
					case 2://no subcondition
						pSubcondition1 = NULL;
						szSubcondition1 = "NULL";
						bValid = false;
					break;
				}
				//create socond subcondition
				cCondition * pSubcondition2 = NULL;
				string szSubcondition2;
				switch ( rand() % 3 ){
					case 0://true subcondition
						pSubcondition2 = new cConditionTrue();
						szSubcondition2 = "true";
					break;
					case 1://false subcondition
						pSubcondition2 = new cConditionFalse();
						szSubcondition2 = "false";
					break;
					case 2://no subcondition
						pSubcondition2 = NULL;
						szSubcondition2 = "NULL";
						bValid = false;
					break;
				}
				
				switch ( uiCondition ){
					case 3://condition or
						szCondition = string("condition or( ") + szSubcondition1 +
							", " + szSubcondition2 + " )";
						pCondition = new cConditionOr( pSubcondition1, pSubcondition2 );
					break;
					case 4://condition and
						szCondition = string("condition and( ") + szSubcondition1 +
							", " + szSubcondition2 + " )";
						pCondition = new cConditionAnd( pSubcondition1, pSubcondition2 );
					break;
					case 5://condition xor
						szCondition = string("condition xor( ") + szSubcondition1 +
							", " + szSubcondition2 + " )";
						pCondition = new cConditionXor( pSubcondition1, pSubcondition2 );
					break;
				}
			}break;
			
			case 6://condition cConditionEqualInteger
			case 7://condition cConditionGreater
			case 8:{//condition cConditionLower
				bValid = true;
				//create first subcondition
				cUnderFunction * pSubfunctions1 = NULL;
				string szSubfunction1;
				char szBuffer[ 256 ];
				switch ( rand() % 4 ){
					case 0:{//value subfunction
						const double dValue = double(rand() % 256 * 256) / 256.0;
						pSubfunctions1 = new cFunctionValue( dValue );
						sprintf( szBuffer, "%f", dValue );
						szSubfunction1 = szBuffer;
					}break;
					case 1:{//variable subfunction with defined variables
						const int iVariable = rand() % vecVariablesDef.size();
						pSubfunctions1 = new cFunctionVariable(
							vecVariablesDef[ iVariable ] );
						sprintf( szBuffer, "varDefined[ %d ]", iVariable );
						szSubfunction1 = szBuffer;
						setCorrectUsedVariables.insert( vecVariablesDef[ iVariable ] );
					}break;
					case 2:{//variable subfunction with not defined variables
						const int iVariable = rand() % vecVariablesNDef.size();
						pSubfunctions1 = new cFunctionVariable(
							vecVariablesNDef[ iVariable ] );
						sprintf( szBuffer, "varNotDefined[ %d ]", iVariable );
						szSubfunction1 = szBuffer;
						setCorrectUsedVariables.insert( vecVariablesNDef[ iVariable ] );
						bValid = false;
					}break;
					case 3:{//variable subfunction with no variable
						pSubfunctions1 = new cFunctionVariable( NULL );
						szSubfunction1 = "variable=NULL";
						bValid = false;
					}break;
				}
				//create socond subcondition
				cUnderFunction * pSubfunctions2 = NULL;
				string szSubfunction2;
				switch ( rand() % 4 ){
					case 0:{//value subfunction
						const double dValue = double(rand() % 256 * 256) / 256.0;
						pSubfunctions2 = new cFunctionValue( dValue );
						sprintf( szBuffer, "%f", dValue );
						szSubfunction2 = szBuffer;
					}break;
					case 1:{//variable subfunction with defined variables
						const int iVariable = rand() % vecVariablesDef.size();
						pSubfunctions2 = new cFunctionVariable(
							vecVariablesDef[ iVariable ] );
						sprintf( szBuffer, "varDefined[ %d ]", iVariable );
						setCorrectUsedVariables.insert( vecVariablesDef[ iVariable ] );
						szSubfunction2 = szBuffer;
					}break;
					case 2:{//variable subfunction with not defined variables
						const int iVariable = rand() % vecVariablesNDef.size();
						pSubfunctions2 = new cFunctionVariable(
							vecVariablesNDef[ iVariable ] );
						sprintf( szBuffer, "varNotDefined[ %d ]", iVariable );
						setCorrectUsedVariables.insert( vecVariablesNDef[ iVariable ] );
						szSubfunction2 = szBuffer;
						bValid = false;
					}break;
					case 3:{//variable subfunction with no variable
						pSubfunctions2 = new cFunctionVariable( NULL );
						szSubfunction2 = "variable=NULL";
						bValid = false;
					}break;
				}
				
				switch ( uiCondition ){
					case 6://condition cConditionEqualInteger
						szCondition = string("condition eqInt( ") + szSubfunction1 +
							", " + szSubfunction2 + " )";
						pCondition = new cConditionEqualInteger( pSubfunctions1, pSubfunctions2 );
					break;
					case 7://condition cConditionGreater
						szCondition = string("condition gr( ") + szSubfunction1 +
							", " + szSubfunction2 + " )";
						pCondition = new cConditionGreater( pSubfunctions1, pSubfunctions2 );
					break;
					case 8://condition cConditionLower
						szCondition = string("condition lo( ") + szSubfunction1 +
							", " + szSubfunction2 + " )";
						pCondition = new cConditionLower( pSubfunctions1, pSubfunctions2 );
					break;
				}
			}break;
			

			/*TODO
				- more conditions
			*/
		};
		
		{//choose Fib-element
			unsigned int uiIfElement = rand() % 3 + 1;
			
			cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a "<<szCondition<<
				" condition"<<endl;
			
			//choose if element to test
			switch ( uiIfElement ){
				case 1:
					pIfToTest = &if1;
					bDeleteIf = false;
					cout<<"if1.setCondition( condition );"<<endl;
					if1.setCondition( *pCondition );
					bValidElement = false;
				break;
				case 2:
					pIfToTest = &ifFull;
					bDeleteIf = false;
					cout<<"ifFull.setCondition( condition );"<<endl;
					ifFull.setCondition( *pCondition );
					bValidElement = true;
				break;
				case 3:
					cout<<"cIf if( *pCondition );"<<endl;
					pIfToTest = new cIf( *pCondition );
					bDeleteIf = true;
					bValidElement = false;
				break;
			};
			bValid = pIfToTest->getCondition()->isValid();
			cout<<"The condition is "<<(bValid?"valid":"not valid")<<endl;
			bValidElement = bValidElement && bValid;
			
			//check the underIf method from cIf
			if ( pIfToTest->getCondition() != NULL ){
			
				if ( pCondition != pIfToTest->getCondition() ){
				
					cout<<"The ifs condition correctly dosn't point to the given condition. "<<endl;
				}else{
					cerr<<"Error: The ifs condition do point to the given condition. "<<endl;
					iReturn++;
				}
				if ( *pCondition == *(pIfToTest->getCondition()) ){
				
					cout<<"The if has the correct condition. "<<endl;
				}else{
					cerr<<"Error: The if has a not the correct condition. "<<endl;
					iReturn++;
				}
				//check the getDefiningFibElement() methode from the condition
				if ( pIfToTest->getCondition()->getDefiningFibElement() == pIfToTest ){
				
					cout<<"The condition defining Fib-element is correctly "<<
						pIfToTest->getCondition()->getDefiningFibElement() <<" . "<<endl;
				}else{
					cerr<<"Error: The condition defining Fib-element is "<<
						pIfToTest->getCondition()->getDefiningFibElement() <<
						" but should be "<< pIfToTest <<" ."<<endl;
					iReturn++;
				}
				//check the isValidFibElement() methode from cIf
				if ( pIfToTest->isValidFibElement() == bValidElement ){
				
					cout<<"The if-element is correctly a "<<
						(bValidElement?"valid":"not valid")<<" if-element. "<<endl;
				}else{
					cerr<<"Error: The if-element is "<<(bValidElement?"not a valid":"a valid")<<
						" if-element, but should"<<(bValidElement?"":"n't")<<" be ."<<endl;
					iReturn++;
				}
				//check the getSuperiorCondition() methode from the condition
				if ( pIfToTest->getCondition()->getSuperiorCondition() == NULL ){
				
					cout<<"The superior condition of the condition correctly "<<
						pIfToTest->getCondition()->getSuperiorCondition() <<" . "<<endl;
				}else{
					cerr<<"Error: The superior condition of the condition is "<<
						pIfToTest->getCondition()->getSuperiorCondition() <<
						" but should be NULL ."<<endl;
					iReturn++;
				}
				//check getUsedVariables()
				cout<<"setUsedVariables = pIfToTest->getUsedVariables( ED_POSITION ); "<<endl;
				set< cFibVariable * > setUsedVariables =
					pIfToTest->getUsedVariables( ED_POSITION );
				if ( setUsedVariables == setCorrectUsedVariables ){
				
					cout<<"The correct used variables wher given back. "<<endl;
				}else{
					cerr<<"Error: The used variables given back are wrong. "<<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: The if has a no condition (NULL is given back). "<<endl;
				iReturn++;
			}
			
			
			if ( bDeleteIf && ( pIfToTest != NULL ) ){
				delete pIfToTest;
				pIfToTest = NULL;
			}
		}//end for if-eleemnt
		if ( pCondition ){
			delete pCondition;
			pCondition = NULL;
		}
	}//end for condition
	
	
	return iReturn;
}


/**
 * This method tests the cases methods of the cIf class.
 *
 * methods tested:
 * 	- cFibElement * getTrueCase();
 * 	- bool setTrueCase( cFibElement * fibObjectTrue, bool bDeleteOld=true );
 * 	- cFibElement * getFalseCase();
 * 	- bool setFalseCase( cFibElement * fibObjectFalse, bool bDeleteOld=true );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCases( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the cases methods"<<endl;
	
	cout<<"cConditionTrue conditionTrue;"<<endl;
	cConditionTrue conditionTrue;
	
	cout<<"cPoint pointTrue;"<<endl;
	cPoint pointTrue;
	
	cout<<"cPoint pointFalse;"<<endl;
	cPoint pointFalse;

	cout<<"cIf ifFull( conditionTrue, &pointTrue, &pointFalse );"<<endl;
	cIf ifFull( conditionTrue, &pointTrue, &pointFalse );

	//check the getTrueCase() methode from the condition
	if ( ifFull.getTrueCase() == &pointTrue ){
	
		cout<<"The if-element has correctly pointTrue as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointTrue as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifFull.getFalseCase() == &pointFalse ){
	
		cout<<"The if-element has correctly pointFalse as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointFalse as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the true case
	if ( ifFull.getNextFibElement() == &pointTrue ){
	
		cout<<"The next Fib-element is correctly the true case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the true case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifFull.getNumberOfElements() == 3 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifFull.getNumberOfElements() <<", but should be 3."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setting other true case"<<endl;
	
	cout<<"cPoint * pPointTrue2 = new cPoint();"<<endl;
	cPoint * pPointTrue2 = new cPoint();
	
	cout<<"ifFull.setTrueCase( pPointTrue2, false );"<<endl;
	bool bCaseChanged = ifFull.setTrueCase( pPointTrue2, false );
	
	if ( bCaseChanged ){
		cout<<"The case was correctly changed. "<<endl;
	}else{
		cerr<<"Error: The case was not changed."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifFull.getTrueCase() == pPointTrue2 ){
	
		cout<<"The if-element has correctly pPointTrue2 as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pPointTrue2 as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifFull.getFalseCase() == &pointFalse ){
	
		cout<<"The if-element has correctly pointFalse as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointFalse as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the true case
	if ( ifFull.getNextFibElement() == pPointTrue2 ){
	
		cout<<"The next Fib-element is correctly the true case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the true case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifFull.getNumberOfElements() == 3 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifFull.getNumberOfElements() <<", but should be 3."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setting a NULL true case"<<endl;
	
	cout<<"ifFull.setTrueCase( NULL );"<<endl;
	bCaseChanged = ifFull.setTrueCase( NULL );
	
	if ( ! bCaseChanged ){
		cout<<"The case was correctly not changed. "<<endl;
	}else{
		cerr<<"Error: The case was changed."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifFull.getTrueCase() == pPointTrue2 ){
	
		cout<<"The if-element has correctly pPointTrue2 as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pPointTrue2 as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifFull.getFalseCase() == &pointFalse ){
	
		cout<<"The if-element has correctly pointFalse as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointFalse as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the true case
	if ( ifFull.getNextFibElement() == pPointTrue2 ){
	
		cout<<"The next Fib-element is correctly the true case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the true case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifFull.getNumberOfElements() == 3 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifFull.getNumberOfElements() <<", but should be 3."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setting other false case"<<endl;
	
	cout<<"cPoint * pPointFalse2 = new cPoint();"<<endl;
	cPoint * pPointFalse2 = new cPoint();
	
	cout<<"ifFull.setFalseCase( pPointFalse2, false );"<<endl;
	bCaseChanged = ifFull.setFalseCase( pPointFalse2, false );
	
	if ( bCaseChanged ){
		cout<<"The case was correctly changed. "<<endl;
	}else{
		cerr<<"Error: The case was not changed."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifFull.getTrueCase() == pPointTrue2 ){
	
		cout<<"The if-element has correctly pPointTrue2 as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pPointTrue2 as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifFull.getFalseCase() == pPointFalse2 ){
	
		cout<<"The if-element has correctly pPointFalse2 as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pPointFalse2 as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the true case
	if ( ifFull.getNextFibElement() == pPointTrue2 ){
	
		cout<<"The next Fib-element is correctly the true case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the true case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifFull.getNumberOfElements() == 3 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifFull.getNumberOfElements() <<", but should be 3."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing setting a NULL true case"<<endl;

	cout<<"ifFull.setFalseCase( NULL );"<<endl;
	bCaseChanged = ifFull.setFalseCase( NULL );
	
	if ( ! bCaseChanged ){
		cout<<"The case was correctly not changed. "<<endl;
	}else{
		cerr<<"Error: The case was changed."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifFull.getTrueCase() == pPointTrue2 ){
	
		cout<<"The if-element has correctly pPointTrue2 as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not poipPointTrue2ntTrue as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifFull.getFalseCase() == pPointFalse2 ){
	
		cout<<"The if-element has correctly pPointFalse2 as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pPointFalse2 as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the true case
	if ( ifFull.getNextFibElement() == pPointTrue2 ){
	
		cout<<"The next Fib-element is correctly the true case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the true case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifFull.getNumberOfElements() == 3 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifFull.getNumberOfElements() <<", but should be 3."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing overwriting true case"<<endl;
	
	cout<<"ifFull.setTrueCase( &pointTrue );"<<endl;
	bCaseChanged = ifFull.setTrueCase( &pointTrue );
	
	if ( bCaseChanged ){
		cout<<"The case was correctly changed. "<<endl;
	}else{
		cerr<<"Error: The case was not changed."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifFull.getTrueCase() == &pointTrue ){
	
		cout<<"The if-element has correctly pointTrue as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointTrue as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifFull.getFalseCase() == pPointFalse2 ){
	
		cout<<"The if-element has correctly pPointFalse2 as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pPointFalse2 as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the true case
	if ( ifFull.getNextFibElement() == &pointTrue ){
	
		cout<<"The next Fib-element is correctly the true case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the true case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifFull.getNumberOfElements() == 3 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifFull.getNumberOfElements() <<", but should be 3."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing overwriting false case"<<endl;
	
	cout<<"ifFull.setFalseCase( &pointFalse );"<<endl;
	bCaseChanged = ifFull.setFalseCase( &pointFalse );
	
	if ( bCaseChanged ){
		cout<<"The case was correctly changed. "<<endl;
	}else{
		cerr<<"Error: The case was not changed."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifFull.getTrueCase() == &pointTrue ){
	
		cout<<"The if-element has correctly pointTrue as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointTrue as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifFull.getFalseCase() == &pointFalse ){
	
		cout<<"The if-element has correctly pointFalse as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointFalse as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the true case
	if ( ifFull.getNextFibElement() == &pointTrue ){
	
		cout<<"The next Fib-element is correctly the true case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the true case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifFull.getNumberOfElements() == 3 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifFull.getNumberOfElements() <<", but should be 3."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the overwriting NULL false and then true"<<endl;
	
	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;
	
	cout<<"cIf ifNull1( conditionFalse );"<<endl;
	cIf ifNull1( conditionFalse );

	//check the getTrueCase() methode from the condition
	if ( ifNull1.getTrueCase() == NULL ){
	
		cout<<"The if-element has correctly NULL as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not NULL as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifNull1.getFalseCase() == NULL ){
	
		cout<<"The if-element has correctly NULL as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not NULL as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the true case
	if ( ifNull1.getNextFibElement() == NULL ){
	
		cout<<"The next Fib-element is correctly the true case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the true case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifNull1.getNumberOfElements() == 1 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifNull1.getNumberOfElements() <<", but should be 1."<<endl;
		iReturn++;
	}
	
	
	cout<<"ifNull1.setFalseCase( &pointFalse );"<<endl;
	bCaseChanged = ifNull1.setFalseCase( &pointFalse );
	
	if ( bCaseChanged ){
		cout<<"The case was correctly changed. "<<endl;
	}else{
		cerr<<"Error: The case was not changed."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifNull1.getTrueCase() == NULL ){
	
		cout<<"The if-element has correctly NULL as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not NULL as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifNull1.getFalseCase() == &pointFalse ){
	
		cout<<"The if-element has correctly pointFalse as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointFalse as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the only (false) case
	if ( ifNull1.getNextFibElement() == &pointFalse ){
	
		cout<<"The next Fib-element is correctly the false case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the false case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifNull1.getNumberOfElements() == 2 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifNull1.getNumberOfElements() <<", but should be 2."<<endl;
		iReturn++;
	}


	cout<<"ifNull1.setFalseCase( &pointFalse, false );"<<endl;
	bCaseChanged = ifNull1.setFalseCase( &pointFalse, false );
	
	if ( bCaseChanged ){
		cout<<"The case was correctly changed. "<<endl;
	}else{
		cerr<<"Error: The case was not changed."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifNull1.getTrueCase() == NULL ){
	
		cout<<"The if-element has correctly NULL as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not NULL as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifNull1.getFalseCase() == &pointFalse ){
	
		cout<<"The if-element has correctly pointFalse as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointFalse as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the only (false) case
	if ( ifNull1.getNextFibElement() == &pointFalse ){
	
		cout<<"The next Fib-element is correctly the false case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the false case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifNull1.getNumberOfElements() == 2 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifNull1.getNumberOfElements() <<", but should be 2."<<endl;
		iReturn++;
	}


	cout<<"ifNull1.setTrueCase( &pointTrue );"<<endl;
	bCaseChanged = ifNull1.setTrueCase( &pointTrue );
	
	if ( bCaseChanged ){
		cout<<"The case was correctly changed. "<<endl;
	}else{
		cerr<<"Error: The case was not changed."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifNull1.getTrueCase() == &pointTrue ){
	
		cout<<"The if-element has correctly pointTrue as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointTrue as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifNull1.getFalseCase() == &pointFalse ){
	
		cout<<"The if-element has correctly pointFalse as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointFalse as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the true case
	if ( ifNull1.getNextFibElement() == &pointTrue ){
	
		cout<<"The next Fib-element is correctly the true case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the true case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifNull1.getNumberOfElements() == 3 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifNull1.getNumberOfElements() <<", but should be 3."<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the overwriting NULL true and then false"<<endl;
	
	cout<<"cIf ifNull2( conditionTrue );"<<endl;
	cIf ifNull2( conditionTrue );

	//check the getTrueCase() methode from the condition
	if ( ifNull2.getTrueCase() == NULL ){
	
		cout<<"The if-element has correctly NULL as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not NULL as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifNull2.getFalseCase() == NULL ){
	
		cout<<"The if-element has correctly NULL as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not NULL as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the true case
	if ( ifNull2.getNextFibElement() == NULL ){
	
		cout<<"The next Fib-element is correctly the true case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the true case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifNull2.getNumberOfElements() == 1 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifNull2.getNumberOfElements() <<", but should be 1."<<endl;
		iReturn++;
	}
	
	
	cout<<"ifNull2.setTrueCase( &pointTrue );"<<endl;
	bCaseChanged = ifNull2.setTrueCase( &pointTrue );
	
	if ( bCaseChanged ){
		cout<<"The case was correctly changed. "<<endl;
	}else{
		cerr<<"Error: The case was not changed."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifNull2.getTrueCase() == &pointTrue ){
	
		cout<<"The if-element has correctly pointTrue as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointTrue as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifNull2.getFalseCase() == NULL ){
	
		cout<<"The if-element has correctly NULL as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not NULL as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the only (true) case
	if ( ifNull2.getNextFibElement() == &pointTrue ){
	
		cout<<"The next Fib-element is correctly the true case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the true case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifNull2.getNumberOfElements() == 2 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifNull2.getNumberOfElements() <<", but should be 2."<<endl;
		iReturn++;
	}
	
	cout<<"ifNull2.setTrueCase( &pointTrue, false );"<<endl;
	bCaseChanged = ifNull2.setTrueCase( &pointTrue, false );
	
	if ( bCaseChanged ){
		cout<<"The case was correctly changed. "<<endl;
	}else{
		cerr<<"Error: The case was not changed."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifNull2.getTrueCase() == &pointTrue ){
	
		cout<<"The if-element has correctly pointTrue as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointTrue as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifNull2.getFalseCase() == NULL ){
	
		cout<<"The if-element has correctly NULL as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not NULL as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the only (true) case
	if ( ifNull2.getNextFibElement() == &pointTrue ){
	
		cout<<"The next Fib-element is correctly the true case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the true case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifNull2.getNumberOfElements() == 2 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifNull2.getNumberOfElements() <<", but should be 2."<<endl;
		iReturn++;
	}


	cout<<"ifNull2.setFalseCase( &pointFalse );"<<endl;
	bCaseChanged = ifNull2.setFalseCase( &pointFalse );
	
	if ( bCaseChanged ){
		cout<<"The case was correctly changed. "<<endl;
	}else{
		cerr<<"Error: The case was not changed."<<endl;
		iReturn++;
	}
	//check the getTrueCase() methode from the condition
	if ( ifNull2.getTrueCase() == &pointTrue ){
	
		cout<<"The if-element has correctly pointTrue as the true case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointTrue as the true case."<<endl;
		iReturn++;
	}
	//check the getFalseCase() methode from the condition
	if ( ifNull2.getFalseCase() == &pointFalse ){
	
		cout<<"The if-element has correctly pointFalse as the false case. "<<endl;
	}else{
		cerr<<"Error: The if-element has not pointFalse as the false case."<<endl;
		iReturn++;
	}
	//check the if the next fib-element is the true case
	if ( ifNull2.getNextFibElement() == &pointTrue ){
	
		cout<<"The next Fib-element is correctly the true case. "<<endl;
	}else{
		cerr<<"Error: The next Fib-element is not the true case."<<endl;
		iReturn++;
	}
	//check the number of fib-elements in the if-element
	if ( ifNull2.getNumberOfElements() == 3 ){
	
		cout<<"The number of the Fib-elements in the if-element is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-elements in the if-element is "<<
			ifNull2.getNumberOfElements() <<", but should be 3."<<endl;
		iReturn++;
	}
	
	
	return iReturn;
}


/**
 * This method tests the variable methods of the cIf class.
 *
 * methods tested:
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- cFibVariable * getDefinedVariable();
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

	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	cout<<"rootSimple1.setNumberOfInputVariables( 10 );"<<endl;
	rootSimple1.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 = rootSimple1.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootSimple1.getInputVariable( 1 );
	cout<<"pVariable2 = rootSimple1.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = rootSimple1.getInputVariable( 2 );
	cout<<"pVariable3 = rootSimple1.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = rootSimple1.getInputVariable( 3 );
	cout<<"pVariable4 = rootSimple1.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable4 = rootSimple1.getInputVariable( 4 );
	
	cout<<"cConditionTrue conditionTrue;"<<endl;
	cConditionTrue conditionTrue;
	
	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;

	cout<<"cIf if1( conditionTrue );"<<endl;
	cIf if1( conditionTrue );
	
	//check the isUsedVariable() methode from cIf
	cout<<"if1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! if1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the if-element. "<<endl;
		iReturn++;
	}
	set<cFibVariable*> setCorrectUsedVariables;
	
	//check getUsedVariables()
	cout<<"setUsedVariables = if1.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = if1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing variable methods on a if with a containing point as true case"<<endl;

	cout<<"cVectorPosition vecPositionE3( 3 );"<<endl;
	cVectorPosition vecPositionE3( 3 );

	cout<<"cPoint pointTrue( &vecPositionE3 );"<<endl;
	cPoint pointTrue( &vecPositionE3 );

	cout<<"cIf ifPoint( conditionFalse, &pointTrue );"<<endl;
	cIf ifPoint( conditionFalse, &pointTrue );

	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable1 )"<<endl;
	if ( ! ifPoint.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the if-element. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.clear();
	
	//check getUsedVariables()
	cout<<"setUsedVariables = ifPoint.getUsedVariables(); "<<endl;
	setUsedVariables = ifPoint.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"pointTrue.getPosition()->setVariable( 3, pVariable1 );"<<endl;
	pointTrue.getPosition()->setVariable( 3, pVariable1 );

	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable1 )"<<endl;
	if ( ! ifPoint.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the if-element. "<<endl;
		iReturn++;
	}
	cout<<"pointTrue.isUsedVariable( pVariable1 )"<<endl;
	if ( pointTrue.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the if-element. "<<endl;
		iReturn++;
	}
	cout<<"ifPoint.isUsedVariable( pVariable1, ED_BELOW_EQUAL )"<<endl;
	if ( ifPoint.isUsedVariable( pVariable1, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable1 is correctly used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = ifPoint.getUsedVariables(); "<<endl;
	setUsedVariables = ifPoint.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.insert( pVariable1 );
	//check getUsedVariables()
	cout<<"setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back for ED_BELOW_EQUAL. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong for ED_BELOW_EQUAL. "<<endl;
		iReturn++;
	}

	cout<<"pointTrue.getPosition()->setVariable( 1, pVariable2 );"<<endl;
	pointTrue.getPosition()->setVariable( 1, pVariable2 );
	
	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable2 )"<<endl;
	if ( ! ifPoint.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the if-element. "<<endl;
		iReturn++;
	}
	cout<<"pointTrue.isUsedVariable( pVariable2 )"<<endl;
	if ( pointTrue.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the pointTrue element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the pointTrue element. "<<endl;
		iReturn++;
	}
	cout<<"ifPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( ifPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = ifPoint.getUsedVariables(); "<<endl;
	setUsedVariables = ifPoint.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.insert( pVariable2 );
	//check getUsedVariables()
	cout<<"setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back for ED_BELOW_EQUAL. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong for ED_BELOW_EQUAL. "<<endl;
		iReturn++;
	}
	
	cout<<"ifPoint.replaceVariable( pVariable2, pVariable3 );"<<endl;
	bool bVariableReplaced = ifPoint.replaceVariable( pVariable2, pVariable3 );
	setCorrectUsedVariables.erase( pVariable2 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( ! ifPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly not used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL )"<<endl;
	if ( ifPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods isDefinedVariable( ED_POSITION ) and getDefinedVariables( ED_POSITION )"<<endl;

	//check the isDefinedVariable() methode from cList
	cout<<"ifPoint.isDefinedVariable( pVariable1, ED_POSITION )"<<endl;
	if ( ! ifPoint.isDefinedVariable( pVariable1, ED_POSITION ) ){
	
		cout<<"The variable pVariable1 is correctly not defined in the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is defined in the if-element. "<<endl;
		iReturn++;
	}

	//check getDefinedVariables()
	cout<<"liDefinedVariables = ifPoint.getDefinedVariables( ED_POSITION ); "<<endl;
	list<cFibVariable*> liDefinedVariables = ifPoint.getDefinedVariables( ED_POSITION );
	
	list<cFibVariable*> liDefinedVariablesCorrect;
	
	if ( liDefinedVariables == liDefinedVariablesCorrect ){
	
		cout<<"Ther are the correct variables defined in the if-element. "<<endl;
	}else{
		cerr<<"Error: Ther aren't the correct variables defined in the if-element. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing variable methods on a if with a containing point as false case"<<endl;


	cout<<"cPoint pointFalse( &vecPositionE3 );"<<endl;
	cPoint pointFalse( &vecPositionE3 );

	cout<<"ifPoint.setFalseCase( &pointFalse );"<<endl;
	ifPoint.setFalseCase( &pointFalse );

	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( ! ifPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly not used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL )"<<endl;
	if ( ifPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"pointFalse.getPosition()->setVariable( 2, pVariable1 );"<<endl;
	pointFalse.getPosition()->setVariable( 2, pVariable1 );

	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable1 )"<<endl;
	if ( ! ifPoint.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the if-element. "<<endl;
		iReturn++;
	}
	cout<<"pointFalse.isUsedVariable( pVariable1 )"<<endl;
	if ( pointFalse.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the pointFalse element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the pointFalse element. "<<endl;
		iReturn++;
	}
	cout<<"ifPoint.isUsedVariable( pVariable1, ED_BELOW_EQUAL )"<<endl;
	if ( ifPoint.isUsedVariable( pVariable1, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable1 is correctly used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	set<cFibVariable*> setCorrectUsedVariablesPosition;
	cout<<"setUsedVariables = ifPoint.getUsedVariables(); "<<endl;
	setUsedVariables = ifPoint.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariablesPosition ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.insert( pVariable1 );
	//check getUsedVariables()
	cout<<"setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back for ED_BELOW_EQUAL. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong for ED_BELOW_EQUAL. "<<endl;
		iReturn++;
	}

	cout<<"pointFalse.getPosition()->setVariable( 3, pVariable4 );"<<endl;
	pointFalse.getPosition()->setVariable( 3, pVariable4 );
	
	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable4 )"<<endl;
	if ( ! ifPoint.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable4 is correctly not used in the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is used in the if-element. "<<endl;
		iReturn++;
	}
	cout<<"pointFalse.isUsedVariable( pVariable4 )"<<endl;
	if ( pointFalse.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable4 is correctly used in the pointFalse element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is not used in the pointFalse element. "<<endl;
		iReturn++;
	}
	cout<<"ifPoint.isUsedVariable( pVariable4, ED_BELOW_EQUAL )"<<endl;
	if ( ifPoint.isUsedVariable( pVariable4, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable4 is correctly used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is not used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = ifPoint.getUsedVariables(); "<<endl;
	setUsedVariables = ifPoint.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.insert( pVariable4 );
	//check getUsedVariables()
	cout<<"setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back for ED_BELOW_EQUAL. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong for ED_BELOW_EQUAL. "<<endl;
		iReturn++;
	}
	
	cout<<"ifPoint.replaceVariable( pVariable1, pVariable4 );"<<endl;
	bVariableReplaced = ifPoint.replaceVariable( pVariable1, pVariable4 );
	setCorrectUsedVariables.erase( pVariable1 );
	setCorrectUsedVariables.insert( pVariable4 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( ! ifPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly not used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable4, ED_BELOW_EQUAL )"<<endl;
	if ( ifPoint.isUsedVariable( pVariable4, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable4 is correctly used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is not used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL )"<<endl;
	if ( ifPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"ifPoint.replaceVariable( pVariable4, pVariable3 );"<<endl;
	bVariableReplaced = ifPoint.replaceVariable( pVariable4, pVariable3 );
	setCorrectUsedVariables.erase( pVariable4 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable4, ED_BELOW_EQUAL )"<<endl;
	if ( ! ifPoint.isUsedVariable( pVariable4, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable4 is correctly not used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL )"<<endl;
	if ( ifPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"ifPoint.replaceVariable( pVariable3, pVariable2 );"<<endl;
	bVariableReplaced = ifPoint.replaceVariable( pVariable3, pVariable2 );
	setCorrectUsedVariables.erase( pVariable3 );
	setCorrectUsedVariables.insert( pVariable2 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL )"<<endl;
	if ( ! ifPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly not used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( ifPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = ifPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a if with a condition which contains a variable"<<endl;
	
	cout<<"cConditionGreater ufVariable1( pVariable1, 1.0 );"<<endl;
	cConditionGreater ufVariable1( new cFunctionVariable( pVariable1 ),
		new cFunctionValue( 1.0 ) );
	
	cout<<"cIf ifV1( ufVariable1 );"<<endl;
	cIf ifV1( ufVariable1 );
	
	setCorrectUsedVariables.clear();
	setCorrectUsedVariables.insert( pVariable1 );
	
	//check the isUsedVariable() methode from cIf
	cout<<"ifV1.isUsedVariable( pVariable1 )"<<endl;
	if ( ifV1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the if-element. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = ifV1.getUsedVariables(); "<<endl;
	setUsedVariables = ifV1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"ifV1.replaceVariable( pVariable1, pVariable2 );"<<endl;
	bVariableReplaced = ifV1.replaceVariable( pVariable1, pVariable2 );
	setCorrectUsedVariables.erase( pVariable1 );
	setCorrectUsedVariables.insert( pVariable2 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifV1.isUsedVariable( pVariable1, ED_BELOW_EQUAL )"<<endl;
	if ( ! ifV1.isUsedVariable( pVariable1, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly not used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifV1.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( ifV1.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_BELOW_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_BELOW_EQUAL the if-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = ifV1.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = ifV1.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"ifV1.replaceVariable( pVariable1, pVariable1 );"<<endl;
	bVariableReplaced = ifV1.replaceVariable( pVariable1, pVariable1 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifV1.isUsedVariable( pVariable1, ED_POSITION )"<<endl;
	if ( ! ifV1.isUsedVariable( pVariable1, ED_POSITION ) ){
	
		cout<<"The variable pVariable2 is correctly not used ED_POSITION the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used ED_POSITION the if-element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifV1.isUsedVariable( pVariable2, ED_POSITION )"<<endl;
	if ( ifV1.isUsedVariable( pVariable2, ED_POSITION ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_POSITION the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_POSITION the if-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = ifV1.getUsedVariables( ED_POSITION ); "<<endl;
	setUsedVariables = ifV1.getUsedVariables( ED_POSITION );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"ifV1.replaceVariable( pVariable2, pVariable2 );"<<endl;
	bVariableReplaced = ifV1.replaceVariable( pVariable2, pVariable2 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifV1.isUsedVariable( pVariable1, ED_HIGHER_EQUAL )"<<endl;
	if ( ! ifV1.isUsedVariable( pVariable1, ED_HIGHER_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly not used ED_HIGHER_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used ED_HIGHER_EQUAL the if-element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cIf
	cout<<"ifV1.isUsedVariable( pVariable2, ED_HIGHER_EQUAL )"<<endl;
	if ( ifV1.isUsedVariable( pVariable2, ED_HIGHER_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_HIGHER_EQUAL the if-element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_HIGHER_EQUAL the if-element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = ifV1.getUsedVariables( ED_HIGHER_EQUAL ); "<<endl;
	setUsedVariables = ifV1.getUsedVariables( ED_HIGHER_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	return iReturn;
}




