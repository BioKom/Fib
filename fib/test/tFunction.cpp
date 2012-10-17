/**
 * @file tFunction
 * file name: tFunction.cpp
 * @author Betti Oesterholz
 * @date 23.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cFunction.
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
 * This file contains the test for the class cFunction, which
 * represents a Fib function element.
 *
 *
 * What's tested of class cFunction:
 * 	- cFunction( const cUnderFunction & inUnderFunction, cFibElement * pInUnderobject = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- cFunction( const cFunction &functionElement );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- bool hasUnderAllObjects( ) const;
 * 	- unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
 * 	- bool evalueObject( iEvaluePosition & evaluePosition, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties ) const;
 * 	- bool evalueObject( iEvalueFibElement & evalueFibElement, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties, const list<char> & liCFibElementTyps );
 * 	- bool equal( const cFibElement & fibObject ) const;
 * 	- bool equalElement( const cFibElement & fibElement ) const;
 * 	- cFunction( const cFunction &functionElement );
 * 	- cFibElement *clone( ) const;
 * 	- cFunction *copy( const unsignedIntFib iObjectFunction=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementFunction=0 ) const;
 * 	- bool storeXml( ostream &stream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream &stream ) const;
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- cFibVariable * getDefinedVariable();
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
 * 	- cUnderFunction * getUnderFunction() const;
 * 	- bool setUnderFunction( const cUnderFunction & underFunction );
 *
 *
 * Underfunctions tested:
 * 	- cFunctionValue
 * 	- cFunctionVariable
 * 	- cFunctionAbs
 * 	- cFunctionSin
 * 	- cFunctionLog
 * 	- cFunctionArcsin
 * 	- cFunctionRound
 * 	- cFunctionAdd
 * 	- cFunctionSub
 * 	- cFunctionMult
 * 	- cFunctionDiv
 * 	- cFunctionExp
 * 	- cFunctionMin
 * 	- cFunctionMax
 * 	- cFunctionIf
 *
 *
 * Test for:
 *
 * Methods for changing the structur of an fib -object will be tested with
 * tFibElementStructur. Methods for fib -objects will be tested with
 * Methods for storing and restoring will be tested in tFibElementStore.
 */
/*
History:
23.04.2010  Oesterholz  created
30.03.2011  Oesterholz  storing to binary stream
06.05.2011  Oesterholz  isValidFibElement() checks the underfunction
20.06.2011  Oesterholz  cFunctionIf added
23.06.2011  Oesterholz  cFunctionRound added
21.07.2011  Oesterholz  for the Xml-format "underfunction" to "subfunction"
05.08.2011  Oesterholz  FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES implemented
10.11.2011  Oesterholz  Bugfix: evalueObject() don't overwrite properties
26.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cFunction.h"
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

#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cFunctionAbs.h"
#include "cFunctionSin.h"
#include "cFunctionLog.h"
#include "cFunctionArcsin.h"
#include "cFunctionRound.h"
#include "cFunctionAdd.h"
#include "cFunctionSub.h"
#include "cFunctionMult.h"
#include "cFunctionDiv.h"
#include "cFunctionExp.h"
#include "cFunctionMin.h"
#include "cFunctionMax.h"
#include "cFunctionIf.h"

#include "cConditionTrue.h"
#include "cConditionFalse.h"


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
int testUnderFunction( unsigned long &ulTestphase );
int testVariable( unsigned long &ulTestphase );


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for cFunction methods"<<endl;
	cout<<      "=================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testEvalueObject( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testUnderFunction( ulTestphase );
	iReturn += testVariable( ulTestphase );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the constructor of the cFunction class.
 *
 * methods tested:
 * 	- cFunction( const cUnderFunction & inUnderFunction, cFibElement * pInUnderobject = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- cFunction( const cFunction &functionElement );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- unsignedIntFib getNumberOfElement()
 * 	- cFunctionValue * getUnderFunction();
 * 	- bool hasUnderAllObjects() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cFunctionvector"<<endl;

	cout<<"cFunctionValue underFunction1( 1 );"<<endl;
	cFunctionValue underFunction1( 1 );

	cout<<"cFunction functionSimple( underFunction1 );"<<endl;
	cFunction functionSimple( underFunction1 );

	//check the getType() methode from cFunction
	if ( functionSimple.getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			functionSimple.getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFunction
	if ( ! functionSimple.isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should not be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFunction
	if ( functionSimple.isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFunction
	if ( functionSimple.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the function element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the function element is "<<
			functionSimple.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFunction
	if ( functionSimple.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the function element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the function element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFunction
	if ( functionSimple.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the function element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the function element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFunction
	if ( functionSimple.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the function element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the function element is "<<
			functionSimple.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getUnderFunction() methode from cFunction
	if ( *functionSimple.getUnderFunction() == underFunction1 ){
	
		cout<<"The underfunction for the function element is correctly equal to underFunction1. "<<endl;
	}else{
		cerr<<"Error: The underfunction for the function element is not equal to underFunction1."<<endl;
		iReturn++;
	}
	//check the getUnderFunction() methode from cFunction
	if ( functionSimple.getUnderFunction() != &underFunction1 ){
	
		cout<<"The underfunction for the function element is correctly not the underFunction1 object. "<<endl;
	}else{
		cerr<<"Error: The underfunction for the function element is the underFunction1 object."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the underfunction
	if ( functionSimple.getUnderFunction()->getDefiningFibElement() == &functionSimple  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			functionSimple.getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			functionSimple.getUnderFunction()->getDefiningFibElement() <<
			" but should be functionSimple="<< &functionSimple <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from the underfunction
	if ( functionSimple.getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			functionSimple.getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			functionSimple.getUnderFunction()->getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from the underfunction
	if ( ! functionSimple.getUnderFunction()->isValid()  ){
	
		cout<<"The underfunction is correctly not valid. "<<endl;
	}else{
		cerr<<"Error: The underfunction is valid."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( ! functionSimple.hasUnderAllObjects()){
	
		cout<<"The function element has correctly missing a needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is not missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cFunction with a differnt underfunction"<<endl;

	cout<<"cFunctionValue underFunction( 17.23 );"<<endl;
	cFunctionValue underFunction( 17.23 );

	cout<<"cFunction function1( underFunction );"<<endl;
	cFunction function1( underFunction );

	//check the getType() methode from cFunction
	if ( function1.getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			function1.getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFunction
	if ( ! function1.isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but shouldn't be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFunction
	if ( function1.isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFunction
	if ( function1.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the function element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the function element is "<<
			function1.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFunction
	if ( function1.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the function element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the function element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFunction
	if ( function1.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the function element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the function element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFunction
	if ( function1.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the function element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the function element is "<<
			function1.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getUnderFunction() methode from cFunction
	if ( function1.getUnderFunction() != NULL ){
	
		if ( underFunction == *(function1.getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction underFunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction underFunction. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the underfunction
	if ( function1.getUnderFunction()->getDefiningFibElement() == &function1  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			function1.getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			function1.getUnderFunction()->getDefiningFibElement() <<
			" but should be function1="<< &function1 <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from the underfunction
	if ( ! function1.getUnderFunction()->isValid()  ){
	
		cout<<"The underfunction is correctly not valid. "<<endl;
	}else{
		cerr<<"Error: The underfunction is valid."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from the underfunction
	if ( function1.getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			function1.getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			function1.getUnderFunction()->getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( ! function1.hasUnderAllObjects() ){
	
		cout<<"The function element has correctly not all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is not missing a underobject."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cFunction with a superior fib -element"<<endl;

	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSup( underFunction, NULL, &rootSimple1 );"<<endl;
	cFunction functionSup( underFunction, NULL, &rootSimple1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSup( underFunction, &rootSimple1 );"<<endl;
	cFunction functionSup( underFunction, &rootSimple1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the getType() methode from cFunction
	if ( functionSup.getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			functionSup.getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFunction
	if ( ! functionSup.isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but shouldn't be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFunction
	if ( functionSup.isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFunction
	if ( functionSup.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the function element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the function element is "<<
			functionSup.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFunction
	if ( functionSup.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the function element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the function element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFunction
	if ( functionSup.getFibElement( -1 ) == &rootSimple1 ){
	
		cout<<"The previous fib -element for the function element is correctly rootSimple1. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the function element is not rootSimple1."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFunction
	if ( functionSup.getSuperiorFibElement() == &rootSimple1 ){
	
		cout<<"The superior fib -element for the function element is correctly rootSimple1. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the function element is "<<
			functionSup.getSuperiorFibElement() << " and not rootSimple1."<<endl;
		iReturn++;
	}
	//check the getUnderFunction() methode from cFunction
	if ( *functionSup.getUnderFunction() == underFunction ){
	
		cout<<"The function has the correctly underfunction equal to underFunction. "<<endl;

	}else{
		cerr<<"Error: The function has a underfunctionequal not equal to underFunction. "<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the underfunction
	if ( functionSup.getUnderFunction()->getDefiningFibElement() == &functionSup  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			functionSup.getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			functionSup.getUnderFunction()->getDefiningFibElement() <<
			" but should be functionSup="<< &functionSup <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from the underfunction
	if ( functionSup.getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			functionSup.getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			functionSup.getUnderFunction()->getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from the underfunction
	if ( ! functionSup.getUnderFunction()->isValid()  ){
	
		cout<<"The underfunction is correctly not valid. "<<endl;
	}else{
		cerr<<"Error: The underfunction is valid."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( ! functionSup.hasUnderAllObjects() ){
	
		cout<<"The function element has correctly not all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is not missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cFunction with a next fib -element"<<endl;
	
	cout<<"cFunction functionNextPrev( underFunction, &functionSimple );"<<endl;
	cFunction functionNextPrev( underFunction, &functionSimple );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cFunction with a next and previous fib -element"<<endl;
	
	cout<<"cFunction functionNextPrev( underFunction, NULL, &function1, &functionSimple );"<<endl;
	cFunction functionNextPrev( underFunction, NULL, &function1, &functionSimple );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	//check the getType() methode from cFunction
	if ( functionNextPrev.getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			functionNextPrev.getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFunction
	if ( ! functionNextPrev.isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFunction
	if ( functionNextPrev.isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNumberOfElement() methode from cFunction
	if ( functionNextPrev.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the function element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the function element is "<<
			functionNextPrev.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNumberOfElement() methode from cFunction
	if ( functionNextPrev.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the function element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the function element is "<<
			functionNextPrev.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNextFibElement() methode from cFunction
	if ( functionNextPrev.getNextFibElement() == &functionSimple ){
	
		cout<<"The next/ main fib -element for the function element is correctly functionSimple. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the function element is not functionSimple."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cFunction
	if ( functionNextPrev.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the function element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the function element is not NULL."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cFunction
	if ( functionNextPrev.getFibElement( -1 ) == &function1 ){
	
		cout<<"The previous fib -element for the function element is correctly function1. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the function element is not function1."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getSuperiorFibElement() methode from cFunction
	if ( functionNextPrev.getSuperiorFibElement() == NULL){
	
		cout<<"The superior fib -element for the function element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the function element is "<<
			functionNextPrev.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getUnderFunction() methode from cFunction
	if ( functionNextPrev.getUnderFunction() != NULL ){
	
		if ( underFunction == *(functionNextPrev.getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction underFunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction underFunction. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the underfunction
	if ( functionNextPrev.getUnderFunction()->getDefiningFibElement() == &functionNextPrev  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			functionNextPrev.getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			functionNextPrev.getUnderFunction()->getDefiningFibElement() <<
			" but should be functionNextPrev="<< &functionNextPrev <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from the underfunction
	if ( functionNextPrev.getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			functionNextPrev.getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			functionNextPrev.getUnderFunction()->getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from the underfunction
	if ( ! functionNextPrev.getUnderFunction()->isValid()  ){
	
		cout<<"The underfunction is correctly not valid. "<<endl;
	}else{
		cerr<<"Error: The underfunction is valid."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( ! functionNextPrev.hasUnderAllObjects()  ){
	
		cout<<"The function element has correctly not all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is not missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cFunction with all parameters given"<<endl;
	
	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeUnderFunction testTypeFunction;"<<endl;
	cTypeUnderFunction testTypeFunction;
	
	//create vector domain with two elements
	cout<<"cDomainNaturalNumberBit natDomain8( 8 );"<<endl;
	cDomainNaturalNumberBit natDomain8( 8 );

	cout<<"rootD2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	rootD2.getDomains()->addDomain( testTypeFunction, &natDomain8 );

	cout<<"cPoint point1;"<<endl;
	cPoint point1;

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionFull( underFunction1, &point1, &rootD2 );"<<endl;
	cFunction functionFull( underFunction1, &point1, &rootD2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionFull( underFunction1, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionFull( underFunction1, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the getType() methode from cFunction
	if ( functionFull.getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			functionFull.getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFunction
	if ( functionFull.isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFunction
	if ( functionFull.isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFunction
	if ( functionFull.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the function element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the function element is "<<
			functionFull.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFunction
	if ( functionFull.getNextFibElement() == &point1 ){
	
		cout<<"The next/ main fib -element for the function element is correctly functionSimple. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the function element is not functionSimple."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFunction
	if ( functionFull.getFibElement( -1 ) == &rootD2 ){
	
		cout<<"The previous fib -element for the function element is correctly rootD2. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the function element is not rootD2."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFunction
	if ( functionFull.getSuperiorFibElement() == &rootD2 ){
	
		cout<<"The superior fib -element for the function element is correctly rootD2. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the function element is "<<
			functionFull.getSuperiorFibElement() << " and not rootD2."<<endl;
		iReturn++;
	}
	//check the getUnderFunction() methode from cFunction
	if ( functionFull.getUnderFunction() != NULL ){
	
		if ( underFunction1 == *(functionFull.getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction underFunction1. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction underFunction1. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the underfunction
	if ( functionFull.getUnderFunction()->getDefiningFibElement() == &functionFull  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			functionFull.getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			functionFull.getUnderFunction()->getDefiningFibElement() <<
			" but should be functionFull="<< &functionFull <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from the underfunction
	if ( functionFull.getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			functionFull.getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			functionFull.getUnderFunction()->getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from the underfunction
	if ( functionFull.getUnderFunction()->isValid() ){
	
		cout<<"The underfunction is correctly valid. "<<endl;
	}else{
		cerr<<"Error: The underfunction is not valid."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( functionFull.hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cFunction with all parameters given but wrong domain"<<endl;
	
	cout<<"cRoot root2D2;"<<flush<<endl;
	cRoot root2D2;
	cout<<"root2D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root2D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionFullWD( underFunction, &point1, &root2D2 );"<<endl;
	cFunction functionFullWD( underFunction, &point1, &root2D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionFullWD( underFunction, &root2D2, &root2D2, &point1 );"<<endl;
	cFunction functionFullWD( underFunction, &root2D2, &root2D2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cUnderFunction * pUnderFunction = &underFunction;
	
	//check the getType() methode from cFunction
	if ( functionFullWD.getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			functionFullWD.getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cFunction
	if ( ! functionFullWD.isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cFunction
	if ( functionFullWD.isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cFunction
	if ( functionFullWD.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the function element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the function element is "<<
			functionFullWD.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cFunction
	if ( functionFullWD.getNextFibElement() == &point1 ){
	
		cout<<"The next/ main fib -element for the function element is correctly functionSimple. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the function element is not functionSimple."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFunction
	if ( functionFullWD.getFibElement( -1 ) == &root2D2 ){
	
		cout<<"The previous fib -element for the function element is correctly root2D2. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the function element is not root2D2."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFunction
	if ( functionFullWD.getSuperiorFibElement() == &root2D2 ){
	
		cout<<"The superior fib -element for the function element is correctly root2D2. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the function element is "<<
			functionFullWD.getSuperiorFibElement() << " and not root2D2."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( functionFullWD.getUnderFunction() != NULL ){
	
		if ( pUnderFunction != functionFullWD.getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(functionFullWD.getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( functionFullWD.getUnderFunction()->getDefiningFibElement() == &functionFullWD  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				functionFullWD.getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				functionFullWD.getUnderFunction()->getDefiningFibElement() <<
				" but should be functionFullWD="<< &functionFullWD <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! functionFullWD.getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( functionFullWD.getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				functionFullWD.getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				functionFullWD.getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( functionFullWD.hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a variable underfunction"<<endl;
	
	cout<<"cRoot root3D2;"<<flush<<endl;
	cRoot root3D2;
	cout<<"root3D2.setNumberOfInputVariables( 10 );"<<endl;
	root3D2.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 = root3D2.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = root3D2.getInputVariable( 1 );
	
	cout<<"cFunctionVariable underFunctionVariable( pVariable1 );"<<endl;
	cFunctionVariable underFunctionVariable( pVariable1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionFull2( underFunctionVariable, &point1, &root3D2 );"<<endl;
	cFunction functionFull2( underFunctionVariable, &point1, &root3D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionFull2( underFunctionVariable, &root3D2, &root3D2, &point1 );"<<endl;
	cFunction functionFull2( underFunctionVariable, &root3D2, &root3D2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pUnderFunction = &underFunctionVariable;
	
	//check the getType() methode from cFunction
	if ( functionFull2.getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			functionFull2.getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( functionFull2.isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( functionFull2.isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( functionFull2.getUnderFunction() != NULL ){
	
		if ( pUnderFunction != functionFull2.getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(functionFull2.getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( functionFull2.getUnderFunction()->getDefiningFibElement() == &functionFull2  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				functionFull2.getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				functionFull2.getUnderFunction()->getDefiningFibElement() <<
				" but should be functionFull2="<< &functionFull2 <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( functionFull2.getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( functionFull2.getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				functionFull2.getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				functionFull2.getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( functionFull2.hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a variable underfunction with variable not defined higher"<<endl;
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionVar1( underFunctionVariable, &point1 );"<<endl;
	cFunction functionVar1( underFunctionVariable, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionVar1( underFunctionVariable, NULL, NULL, &point1 );"<<endl;
	cFunction functionVar1( underFunctionVariable, NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pUnderFunction = &underFunctionVariable;
	
	//check the getType() methode from cFunction
	if ( functionVar1.getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			functionVar1.getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( ! functionVar1.isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( functionVar1.isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( functionVar1.getUnderFunction() != NULL ){
	
		if ( pUnderFunction != functionVar1.getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(functionVar1.getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( functionVar1.getUnderFunction()->getDefiningFibElement() == &functionVar1  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				functionVar1.getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				functionVar1.getUnderFunction()->getDefiningFibElement() <<
				" but should be functionVar1="<< &functionVar1 <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! functionVar1.getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( functionVar1.getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				functionVar1.getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				functionVar1.getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( functionVar1.hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a absolutvalue underfunction which is valid"<<endl;
	
	cout<<"cFunctionAbs underFunctionAbs( &underFunction1 );"<<endl;
	cFunctionAbs underFunctionAbs( &underFunction1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root4D2;"<<flush<<endl;
	cRoot root4D2;
	cout<<"root4D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root4D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionAbs( underFunctionAbs, &point1, &root4D2 );"<<endl;
	cFunction functionAbs( underFunctionAbs, &point1, &root4D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionAbs( underFunctionAbs, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionAbs( underFunctionAbs, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cFunction * pFunctionToTest = &functionAbs;
	pUnderFunction = &underFunctionAbs;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionAbs="<< &functionAbs <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a absolutvalue underfunction which is not valid"<<endl;
	
	cout<<"cFunctionAbs underFunctionAbsNV( &underFunction );"<<endl;
	cFunctionAbs underFunctionAbsNV( &underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionAbsNV( underFunctionAbsNV, &point1 );"<<endl;
	cFunction functionAbsNV( underFunctionAbsNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionAbsNV( underFunctionAbsNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionAbsNV( underFunctionAbsNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionAbsNV;
	pUnderFunction = &underFunctionAbsNV;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionAbs="<< &functionAbs <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( ! pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a sinusvalue underfunction which is valid"<<endl;
	
	cout<<"cFunctionSin underFunctionSin( &underFunction1 );"<<endl;
	cFunctionSin underFunctionSin( &underFunction1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root5D2;"<<flush<<endl;
	cRoot root5D2;
	cout<<"root5D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root5D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionSin( underFunctionSin, &point1, &root5D2 );"<<endl;
	cFunction functionSin( underFunctionSin, &point1, &root5D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSin( underFunctionSin, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionSin( underFunctionSin, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionSin;
	pUnderFunction = &underFunctionSin;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionSin="<< &functionSin <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a sinusvalue underfunction which is not valid"<<endl;
	
	cout<<"cFunctionSin underFunctionSinNV( &underFunction );"<<endl;
	cFunctionSin underFunctionSinNV( &underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSinNV( underFunctionSinNV, &point1 );"<<endl;
	cFunction functionSinNV( underFunctionSinNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSinNV( underFunctionSinNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionSinNV( underFunctionSinNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionSinNV;
	pUnderFunction = &underFunctionSinNV;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionSin="<< &functionSin <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( ! pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a logarithmus underfunction which is valid"<<endl;
	
	cout<<"cFunctionLog underFunctionLog( &underFunction1 );"<<endl;
	cFunctionLog underFunctionLog( &underFunction1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root6D2;"<<flush<<endl;
	cRoot root6D2;
	cout<<"root6D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root6D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionLog( underFunctionLog, &point1, &root6D2 );"<<endl;
	cFunction functionLog( underFunctionLog, &point1, &root6D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionLog( underFunctionLog, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionLog( underFunctionLog, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionLog;
	pUnderFunction = &underFunctionLog;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionLog="<< &functionLog <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a logarithmus underfunction which is not valid"<<endl;
	
	cout<<"cFunctionLog underFunctionLogNV( &underFunction );"<<endl;
	cFunctionLog underFunctionLogNV( &underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionLogNV( underFunctionLogNV, &point1 );"<<endl;
	cFunction functionLogNV( underFunctionLogNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionLogNV( underFunctionLogNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionLogNV( underFunctionLogNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionLogNV;
	pUnderFunction = &underFunctionLogNV;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionLog="<< &functionLog <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( ! pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a arcus sinus underfunction which is valid"<<endl;
	
	cout<<"cFunctionArcsin underFunctionArcsin( &underFunction1 );"<<endl;
	cFunctionArcsin underFunctionArcsin( &underFunction1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root7D2;"<<flush<<endl;
	cRoot root7D2;
	cout<<"root7D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root7D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionArcsin( underFunctionArcsin, &point1, &root7D2 );"<<endl;
	cFunction functionArcsin( underFunctionArcsin, &point1, &root7D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionArcsin( underFunctionArcsin, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionArcsin( underFunctionArcsin, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionArcsin;
	pUnderFunction = &underFunctionArcsin;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionArcsin="<< &functionArcsin <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a arcus sinus underfunction which is not valid"<<endl;
	
	cout<<"cFunctionArcsin underFunctionArcsinNV( &underFunction );"<<endl;
	cFunctionArcsin underFunctionArcsinNV( &underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionArcsinNV( underFunctionArcsinNV, &point1 );"<<endl;
	cFunction functionArcsinNV( underFunctionArcsinNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionArcsinNV( underFunctionArcsinNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionArcsinNV( underFunctionArcsinNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionArcsinNV;
	pUnderFunction = &underFunctionArcsinNV;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionArcsin="<< &functionArcsin <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( ! pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a round underfunction which is valid"<<endl;
	
	cout<<"cFunctionRound underFunctionRound( &underFunction1 );"<<endl;
	cFunctionRound underFunctionRound( &underFunction1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootRound;"<<flush<<endl;
	cRoot rootRound;
	cout<<"rootRound.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	rootRound.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionRound( underFunctionRound, &point1, &rootRound );"<<endl;
	cFunction functionRound( underFunctionRound, &point1, &rootRound );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionRound( underFunctionRound, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionRound( underFunctionRound, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionRound;
	pUnderFunction = &underFunctionRound;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionRound="<< &functionRound <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a round underfunction which is not valid"<<endl;
	
	cout<<"cFunctionRound underFunctionRoundNV( &underFunction );"<<endl;
	cFunctionRound underFunctionRoundNV( &underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionRoundNV( underFunctionRoundNV, &point1 );"<<endl;
	cFunction functionRoundNV( underFunctionRoundNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionRoundNV( underFunctionRoundNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionRoundNV( underFunctionRoundNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionRoundNV;
	pUnderFunction = &underFunctionRoundNV;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionRound="<< &functionRound <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( ! pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a adding underfunction which is valid"<<endl;
	
	cout<<"cFunctionValue underFunction2( 2.0 );"<<endl;
	cFunctionValue underFunction2( 2.0 );
	
	cout<<"cFunctionAdd underFunctionAdd( underFunction1, underFunction2 );"<<endl;
	cFunctionAdd underFunctionAdd( underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root8D2;"<<flush<<endl;
	cRoot root8D2;
	cout<<"root8D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root8D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionAdd( underFunctionAdd, &point1, &root8D2 );"<<endl;
	cFunction functionAdd( underFunctionAdd, &point1, &root8D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionAdd( underFunctionAdd, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionAdd( underFunctionAdd, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionAdd;
	pUnderFunction = &underFunctionAdd;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionAdd="<< &functionAdd <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a adding underfunction which is not valid"<<endl;
	
	cout<<"cFunctionAdd underFunctionAddNV( underFunction1, underFunction );"<<endl;
	cFunctionAdd underFunctionAddNV( underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionAddNV( underFunctionAddNV, &point1 );"<<endl;
	cFunction functionAddNV( underFunctionAddNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionAddNV( underFunctionAddNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionAddNV( underFunctionAddNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionAddNV;
	pUnderFunction = &underFunctionAddNV;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionAdd="<< &functionAdd <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( ! pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a subtraction underfunction which is valid"<<endl;
	
	cout<<"cFunctionSub underFunctionSub( underFunction1, underFunction2 );"<<endl;
	cFunctionSub underFunctionSub( underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root9D2;"<<flush<<endl;
	cRoot root9D2;
	cout<<"root9D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root9D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionSub( underFunctionSub, &point1, &root9D2 );"<<endl;
	cFunction functionSub( underFunctionSub, &point1, &root9D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSub( underFunctionSub, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionSub( underFunctionSub, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionSub;
	pUnderFunction = &underFunctionSub;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionSub="<< &functionSub <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a subtraction underfunction which is not valid"<<endl;
	
	cout<<"cFunctionSub underFunctionSubNV( underFunction1, underFunction );"<<endl;
	cFunctionSub underFunctionSubNV( underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSubNV( underFunctionSubNV, &point1 );"<<endl;
	cFunction functionSubNV( underFunctionSubNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSubNV( underFunctionSubNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionSubNV( underFunctionSubNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionSubNV;
	pUnderFunction = &underFunctionSubNV;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionSub="<< &functionSub <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( ! pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a multiplication underfunction which is valid"<<endl;
	
	cout<<"cFunctionMult underFunctionMult( underFunction1, underFunction2 );"<<endl;
	cFunctionMult underFunctionMult( underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root10D2;"<<flush<<endl;
	cRoot root10D2;
	cout<<"root10D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root10D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionMult( underFunctionMult, &point1, &root10D2 );"<<endl;
	cFunction functionMult( underFunctionMult, &point1, &root10D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMult( underFunctionMult, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionMult( underFunctionMult, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionMult;
	pUnderFunction = &underFunctionMult;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionMult="<< &functionMult <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a multiplication underfunction which is not valid"<<endl;
	
	cout<<"cFunctionMult underFunctionMultNV( underFunction1, underFunction );"<<endl;
	cFunctionMult underFunctionMultNV( underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMultNV( underFunctionMultNV, &point1 );"<<endl;
	cFunction functionMultNV( underFunctionMultNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMultNV( underFunctionMultNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionMultNV( underFunctionMultNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionMultNV;
	pUnderFunction = &underFunctionMultNV;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionMult="<< &functionMult <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( ! pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a division underfunction which is valid"<<endl;
	
	cout<<"cFunctionDiv underFunctionDiv( underFunction1, underFunction2 );"<<endl;
	cFunctionDiv underFunctionDiv( underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root11D2;"<<flush<<endl;
	cRoot root11D2;
	cout<<"root11D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root11D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionDiv( underFunctionDiv, &point1, &root11D2 );"<<endl;
	cFunction functionDiv( underFunctionDiv, &point1, &root11D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionDiv( underFunctionDiv, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionDiv( underFunctionDiv, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionDiv;
	pUnderFunction = &underFunctionDiv;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionDiv="<< &functionDiv <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a division underfunction which is not valid"<<endl;
	
	cout<<"cFunctionDiv underFunctionDivNV( underFunction1, underFunction );"<<endl;
	cFunctionDiv underFunctionDivNV( underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionDivNV( underFunctionDivNV, &point1 );"<<endl;
	cFunction functionDivNV( underFunctionDivNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionDivNV( underFunctionDivNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionDivNV( underFunctionDivNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionDivNV;
	pUnderFunction = &underFunctionDivNV;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionDiv="<< &functionDiv <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( ! pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a exponent underfunction which is valid"<<endl;
	
	cout<<"cFunctionExp underFunctionExp( underFunction1, underFunction2 );"<<endl;
	cFunctionExp underFunctionExp( underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root12D2;"<<flush<<endl;
	cRoot root12D2;
	cout<<"root12D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root12D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionExp( underFunctionExp, &point1, &root12D2 );"<<endl;
	cFunction functionExp( underFunctionExp, &point1, &root12D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionExp( underFunctionExp, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionExp( underFunctionExp, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionExp;
	pUnderFunction = &underFunctionExp;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionExp="<< &functionExp <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a exponent underfunction which is not valid"<<endl;
	
	cout<<"cFunctionExp underFunctionExpNV( underFunction1, underFunction );"<<endl;
	cFunctionExp underFunctionExpNV( underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionExpNV( underFunctionExpNV, &point1 );"<<endl;
	cFunction functionExpNV( underFunctionExpNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionExpNV( underFunctionExpNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionExpNV( underFunctionExpNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionExpNV;
	pUnderFunction = &underFunctionExpNV;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionExp="<< &functionExp <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( ! pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a minimum underfunction which is valid"<<endl;
	
	cout<<"cFunctionMin underFunctionMin( underFunction1, underFunction2 );"<<endl;
	cFunctionMin underFunctionMin( underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root13D2;"<<flush<<endl;
	cRoot root13D2;
	cout<<"root13D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root13D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionMin( underFunctionMin, &point1, &root13D2 );"<<endl;
	cFunction functionMin( underFunctionMin, &point1, &root13D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMin( underFunctionMin, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionMin( underFunctionMin, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionMin;
	pUnderFunction = &underFunctionMin;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionMin="<< &functionMin <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a minimum underfunction which is not valid"<<endl;
	
	cout<<"cFunctionMin underFunctionMinNV( underFunction1, underFunction );"<<endl;
	cFunctionMin underFunctionMinNV( underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMinNV( underFunctionMinNV, &point1 );"<<endl;
	cFunction functionMinNV( underFunctionMinNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMinNV( underFunctionMinNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionMinNV( underFunctionMinNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionMinNV;
	pUnderFunction = &underFunctionMinNV;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionMin="<< &functionMin <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( ! pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a maximum underfunction which is valid"<<endl;
	
	cout<<"cFunctionMax underFunctionMax( underFunction1, underFunction2 );"<<endl;
	cFunctionMax underFunctionMax( underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root14D2;"<<flush<<endl;
	cRoot root14D2;
	cout<<"root14D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root14D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionMax( underFunctionMax, &point1, &root14D2 );"<<endl;
	cFunction functionMax( underFunctionMax, &point1, &root14D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMax( underFunctionMax, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionMax( underFunctionMax, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionMax;
	pUnderFunction = &underFunctionMax;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionMax="<< &functionMax <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a maximum underfunction which is not valid"<<endl;
	
	cout<<"cFunctionMax underFunctionMaxNV( underFunction1, underFunction );"<<endl;
	cFunctionMax underFunctionMaxNV( underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMaxNV( underFunctionMaxNV, &point1 );"<<endl;
	cFunction functionMaxNV( underFunctionMaxNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMaxNV( underFunctionMaxNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionMaxNV( underFunctionMaxNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionMaxNV;
	pUnderFunction = &underFunctionMaxNV;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionMax="<< &functionMax <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( ! pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a if-underfunction which is valid"<<endl;
	
	cout<<"cConditionTrue conditionTrue;"<<endl;
	cConditionTrue conditionTrue;
	cout<<"cFunctionIf underFunctionIf( conditionTrue, underFunction1, underFunction2 );"<<endl;
	cFunctionIf underFunctionIf( conditionTrue, underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root15D2;"<<flush<<endl;
	cRoot root15D2;
	cout<<"root15D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root15D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionIf( underFunctionIf, &point1, &root15D2 );"<<endl;
	cFunction functionIf( underFunctionIf, &point1, &root15D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionIf( underFunctionIf, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionIf( underFunctionIf, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionIf;
	pUnderFunction = &underFunctionIf;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionIf="<< &functionIf <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is not a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a if-underfunction which is not valid"<<endl;
	
	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;
	cout<<"cFunctionIf underFunctionIfNV( conditionFalse, underFunction1, underFunction );"<<endl;
	cFunctionIf underFunctionIfNV( conditionFalse, underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionIfNV( underFunctionIfNV, &point1 );"<<endl;
	cFunction functionIfNV( underFunctionIfNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionIfNV( underFunctionIfNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionIfNV( underFunctionIfNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionIfNV;
	pUnderFunction = &underFunctionIfNV;
	
	//check the getType() methode from cFunction
	if ( pFunctionToTest->getType() == 'f' ){
	
		cout<<"The type of the function element is correctly 'f' . "<<endl;
	}else{
		cerr<<"Error: The type of the function element is "<<
			pFunctionToTest->getType()<<" but should be 'f' ."<<endl;
		iReturn++;
	}
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionIf="<< &functionIf <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the isValidFibElement() methode from cFunction
	if ( ! pFunctionToTest->isValidFibElement() ){
	
		cout<<"The function element is correctly not a correct function element. "<<endl;
	}else{
		cerr<<"Error: The function element is a correct function element, but should be ."<<endl;
		iReturn++;
	}
	//check the isMovable() methode from cFunction
	if ( pFunctionToTest->isMovable() ){
	
		cout<<"The function element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The function element is not movebel."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cFunction
	if ( pFunctionToTest->hasUnderAllObjects() ){
	
		cout<<"The function element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The function element is missing a underobject."<<endl;
		iReturn++;
	}
	

	return iReturn;
}


/**
 * This function compares the to given listlists.
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
 * This function compares the given evalued position lists.
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
 * This function compares the given evalued fib -element lists.
 *
 * @param liEvaluedElements the first list with the fib -elements and ther properties,
 * 	which are to be compared; this list sould be evalued
 * @param liToGiveBackElements the second list with the fib -elements and ther properties,
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
				cout<<"The fib -elements are equal."<<endl;
			}else{
				cerr<<"Error: The fib -elements are not equal."<<endl;
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
 * This function compares the given evalued fib -element lists.
 *
 * @param liEvaluedElements the first list with the fib -elements and ther properties,
 * 	which are to be compared; this list sould be evalued
 * @param liToGiveBackElements the second list with the fib -elements and ther properties,
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
				cout<<"The fib -elements are equal."<<endl;
			}else{
				cerr<<"Error: The fib -elements are not equal."<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFunction with the underfunction from 1 to 2"<<endl;

	cout<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );

	cout<<"cPoint point1( &vecPositionE2 );"<<endl;
	cPoint point1( &vecPositionE2 );
	
	cout<<"cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );
	
	cout<<"cFunctionValue underFunction( 3 );"<<endl;
	cFunctionValue underFunction( 3 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property1( vecPropertyColorSW, &point1 );"<<endl;
	cProperty property1( vecPropertyColorSW, &point1 );

	cout<<"cFunction function1( underFunction, &property1 );"<<endl;
	cFunction function1( underFunction, &property1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property1( vecPropertyColorSW, NULL, NULL, &point1 );"<<endl;
	cProperty property1( vecPropertyColorSW, NULL, NULL, &point1 );
	
	cout<<"cFunction function1( underFunction, NULL, NULL, &property1 );"<<endl;
	cFunction function1( underFunction, NULL, NULL, &property1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	
	cout<<"point1.getPosition()->setVariable( 1, function1.getDefinedVariable() );"<<endl;
	point1.getPosition()->setVariable( 1, function1.getDefinedVariable() );

	cout<<"property1.getProperty()->setVariable( 1, function1.getDefinedVariable() );"<<endl;
	property1.getProperty()->setVariable( 1, function1.getDefinedVariable() );
	
	unsigned int uiPointsToEvalue = 1;
	
	unsigned int uiTimeNeeded = 1 + 5;

	//check the getTimeNeed() methode from cList
	cout<<"function1.getTimeNeed()"<<endl;
	if ( function1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			function1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cList
	cout<<"function1.getTimeNeed( 4 )"<<endl;
	if ( function1.getTimeNeed( 4 ) == 4 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 4 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			function1.getTimeNeed( 4 ) <<", but should be "<< 4 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"list<cVectorProperty> liVecProperties;"<<endl;
	list<cVectorProperty> liVecProperties;
	
	//generate to evalue data
	list< pair< const cVectorPosition*, list<cVectorProperty> > > liPointsToEvalue;
	cVectorPosition vecPositionE2V1( 2 );
	vecPositionE2V1.setValue( 1, 3 );
	cVectorProperty vecPropertyColorSWV1( cTypeProperty::COLOR_SW );
	vecPropertyColorSWV1.setValue( 1, 3 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V1, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	
	cEvaluePositionList evaluePositionList;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"function1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bool bObjectEvalued = function1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The function was correctly evalued. "<<endl;
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
	cout<<"function1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = function1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The function was correctly evalued. "<<endl;
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
	cout<<"function1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = function1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The function was correctly evalued. "<<endl;
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
	cout<<"function1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = function1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The function was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFunction with a global property list given"<<endl;
	
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
	
	cout<<"function1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = function1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The function was correctly evalued. "<<endl;
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
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	list< pair< const cFibElement*, list<cVectorProperty> > >::iterator
		itrElementProperties = liFibElementsToEvalue.begin();
	itrElementProperties->second.push_back( vecPropertyLayer );

	cout<<"function1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = function1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The function was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFunction with a different underfunction"<<endl;

	cout<<"cFunctionValue underFunction5( 5 );"<<endl;
	cFunctionValue underFunction5( 5 );

	
	cout<<"function1.setUnderFunction( underFunction5 );"<<endl;
	function1.setUnderFunction( underFunction5 );
	
	uiPointsToEvalue = 1;
	
	//generate to evalue data
	cVectorProperty vecPropertyColorSWV5( cTypeProperty::COLOR_SW );
	vecPropertyColorSWV5.setValue( 1, 5 );
	
	liPointsToEvalue.clear();
	cVectorPosition vecPositionE2V5( 2 );
	vecPositionE2V5.setValue( 1, 5 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V5, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV5 );

	uiTimeNeeded = 1 + uiPointsToEvalue * 5;

	//check the getTimeNeed() methode from cList
	cout<<"function1.getTimeNeed()"<<endl;
	if ( function1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			function1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}

	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"function1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = function1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The function was correctly evalued. "<<endl;
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
	cout<<"function1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = function1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The function was correctly evalued. "<<endl;
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
	
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV5 );
	
	cout<<"function1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = function1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The function was correctly evalued. "<<endl;
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
	cout<<"function1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = function1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The function was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFunction for non existing object point 1"<<endl;
	
	uiPointsToEvalue = 0;
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"function1.evalueObject( evaluePositionList, 4,  liVecProperties );"<<endl;
	bObjectEvalued = function1.evalueObject( evaluePositionList, 4,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The function was correctly not evalued. "<<endl;
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
	cout<<"function1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = function1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The function was correctly not evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFunction when returnvalue is false"<<endl;

	uiPointsToEvalue = 1;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	cout<<"function1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = function1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The function was correctly evalued. with result false "<<endl;
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
	cout<<"function1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = function1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The function was correctly evalued. with result false "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cFunction with differnt elements to evalue"<<endl;

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
			make_pair( &property1, list<cVectorProperty>() ) );
	}
	cout<<"function1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = function1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The function was correctly evalued. "<<endl;
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
	cout<<"liCFibElementTyps.push_back( 'f' );"<<endl;
	liCFibElementTyps.push_back( 'f' );
	uiPointsToEvalue = 1;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &function1, list<cVectorProperty>() ) );
	cout<<"function1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = function1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The function was correctly evalued. "<<endl;
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
	cout<<"liCFibElementTyps.push_back( 'f' );"<<endl;
	liCFibElementTyps.push_back( 'f' );
	cout<<"liCFibElementTyps.push_back( 'm' );"<<endl;
	liCFibElementTyps.push_back( 'm' );
	uiPointsToEvalue = 1;
	cout<<"function1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = function1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The function was correctly evalued. "<<endl;
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
 * This method tests the equal() method of two given fib -objects which are
 * equal.
 *
 * @param fibObject1 the first fib -object to compare
 * @param szNameObject1 the name of the first fib -object to compare
 * @param fibObject2 the secound fib -object to compare to
 * @param szNameObject2 the name of the secound fib -object to compare
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
	
		cout<<"The "<<szNameObject1<<" fib -element is equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" fib -element is not equal to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}

	return iReturn;
}

/**
 * This method tests the equal() method of two given fib -objects which are
 * not equal.
 *
 * @param fibObject1 the first fib -object to compare
 * @param szNameObject1 the name of the first fib -object to compare
 * @param fibObject2 the secound fib -object to compare to
 * @param szNameObject2 the name of the secound fib -object to compare
 * @param bEqualElement if true the highest fib -elements of the
 * 	fib -objects are equal, else ther are not equal
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
	
		cout<<"The "<<szNameObject1<<" fib -element is "<<
			(bEqualElement?"":"not") <<" equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" fib -element is "<<
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing equal methods for function elements"<<endl;

	cout<<endl<<"Creating functionobjects objects to compare: "<<endl<<endl;

	//function with a empty functionvector
	cout<<"cFunctionValue underFunction1( 1 );"<<endl;
	cFunctionValue underFunction1( 1 );
	cout<<"cFunction function1( underFunction1 );"<<endl;
	cFunction function1( underFunction1 );

	cout<<"cFunctionValue underFunction2( 1 );"<<endl;
	cFunctionValue underFunction2( 1 );
	cout<<"cFunction function2( underFunction2 );"<<endl;
	cFunction function2( underFunction2 );

	//function with one changed underfunction
	cout<<"cFunctionValue underFunction3( 3 );"<<endl;
	cFunctionValue underFunction3( 3 );
	cout<<"cFunction function3( underFunction3 );"<<endl;
	cFunction function3( underFunction3 );

	cout<<"cFunctionValue underFunction3p3( 3.3 );"<<endl;
	cFunctionValue underFunction3p3( 3.3 );
	cout<<"cFunction function3p3( underFunction3p3 );"<<endl;
	cFunction function3p3( underFunction3p3 );

	//function with supperior element
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSup( underFunction1, NULL, &rootSimple1 );"<<endl;
	cFunction functionSup( underFunction1, NULL, &rootSimple1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSup( underFunction1, &rootSimple1 );"<<endl;
	cFunction functionSup( underFunction1, &rootSimple1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//function in fib -element structur
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionNextPrev( underFunction1, &poinNext );"<<endl;
	cFunction functionNextPrev( underFunction1, &poinNext );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinPrev;"<<endl;
	cPoint poinPrev;
	cout<<"cFunction functionNextPrev( underFunction1, NULL, &poinPrev, &poinNext );"<<endl;
	cFunction functionNextPrev( underFunction1, NULL, &poinPrev, &poinNext );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	cout<<"cPoint poinNext2;"<<endl;
	cPoint poinNext2;
	cout<<"cRoot root1;"<<flush<<endl;
	cRoot root1;
	
	cout<<"cTypeUnderFunction testTypeFunction;"<<endl;
	cTypeUnderFunction testTypeFunction;
	
	//create vector domain with two elements
	cout<<"cDomainNaturalNumberBit domainNat8( 8 );"<<endl;
	cDomainNaturalNumberBit domainNat8( 8 );

	cout<<"root1.getDomains()->addDomain( testTypeFunction, &domainNat8 );"<<endl;
	root1.getDomains()->addDomain( testTypeFunction, &domainNat8 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionFull( underFunction1, &poinNext2, &root1 );"<<endl;
	cFunction functionFull( underFunction1, &poinNext2, &root1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinPrev2;"<<endl;
	cPoint poinPrev2;
	cout<<"cFunction functionFull( underFunction1, &root1, &poinPrev2, &poinNext2 );"<<endl;
	cFunction functionFull( underFunction1, &root1, &poinPrev2, &poinNext2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//functions with a contained pointelement
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionPoint1( underFunction1, &point1 );"<<endl;
	cFunction functionPoint1( underFunction1, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionPoint1( underFunction1, NULL, NULL, &point1 );"<<endl;
	cFunction functionPoint1( underFunction1, NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"cVectorPosition vecPosition;"<<endl;
	cVectorPosition vecPosition;
	cout<<"cPoint point2( &vecPosition );"<<endl;
	cPoint point2( &vecPosition );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionPoint2( underFunction1, &point2 );"<<endl;
	cFunction functionPoint2( underFunction1, &point2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionPoint2( underFunction1, NULL, NULL, &point2 );"<<endl;
	cFunction functionPoint2( underFunction1, NULL, NULL, &point2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR



	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with function1
	cFibElement *actualObject = &function1;
	string szActualObjectName = "function1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, function1, "function1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, function2, "function2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3, "function3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3p3, "function3p3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionNextPrev, "functionNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionPoint1, "functionPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionPoint2, "functionPoint2", true );

	//compare with function2
	actualObject = &function2;
	szActualObjectName = "function2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, function1, "function1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, function2, "function2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3, "function3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3p3, "function3p3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionNextPrev, "functionNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionPoint1, "functionPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionPoint2, "functionPoint2", true );

	//compare with function3
	actualObject = &function3;
	szActualObjectName = "function3";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function1, "function1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function2, "function2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, function3, "function3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3p3, "function3p3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionNextPrev, "functionNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionPoint1, "functionPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionPoint2, "functionPoint2" );

	//compare with function3p3
	actualObject = &function3p3;
	szActualObjectName = "function3p3";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function1, "function1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function2, "function2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3, "function3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, function3p3, "function3p3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionNextPrev, "functionNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionPoint1, "functionPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionPoint2, "functionPoint2" );

	//compare with functionSup
	actualObject = &functionSup;
	szActualObjectName = "functionSup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, function1, "function1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, function2, "function2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3, "function3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3p3, "function3p3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionNextPrev, "functionNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionPoint1, "functionPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionPoint2, "functionPoint2", true );

	//compare with functionNextPrev
	actualObject = &functionNextPrev;
	szActualObjectName = "functionNextPrev";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function1, "function1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function2, "function2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3, "function3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3p3, "function3p3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionNextPrev, "functionNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionPoint1, "functionPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionPoint2, "functionPoint2", true );

	//compare with functionFull
	actualObject = &functionFull;
	szActualObjectName = "functionFull";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function1, "function1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function2, "function2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3, "function3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3p3, "function3p3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionNextPrev, "functionNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionPoint1, "functionPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionPoint2, "functionPoint2", true );

	//compare with functionPoint1
	actualObject = &functionPoint1;
	szActualObjectName = "functionPoint1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function1, "function1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function2, "function2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3, "function3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3p3, "function3p3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionNextPrev, "functionNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionPoint1, "functionPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionPoint2, "functionPoint2", true );

	//compare with functionPoint2
	actualObject = &functionPoint2;
	szActualObjectName = "functionPoint2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function1, "function1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function2, "function2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3, "function3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, function3p3, "function3p3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionNextPrev, "functionNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionPoint1, "functionPoint1", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionPoint2, "functionPoint2" );


	return iReturn;
}



/**
 * This method tests the equal() method of two given fib -objects which are
 * equal.
 * It also compares the superior, next and previous fib -element functioners.
 *
 * @param fibObject1 the first fib -object to compare
 * @param szNameObject1 the name of the first fib -object to compare
 * @param fibObject2 the secound fib -object to compare to
 * @param szNameObject2 the name of the secound fib -object to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualObjectsStructur(
		const cFibElement &fibObject1, const string &szNameObject1,
		const cFibElement &fibObject2, const string &szNameObject2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	iReturn += testCompareTwoEqualObjects( fibObject1, szNameObject1, fibObject2, szNameObject2 );
	
	//check the getNextFibElement() methode from cFunction
	if ( const_cast<cFibElement*>(&fibObject1)->getNextFibElement() ==
			const_cast<cFibElement*>(&fibObject2)->getNextFibElement() ){
	
		cout<<"The next/ main fib -elementpointer for the function element are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -elementpointer for the function element are not equal."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cFunction
	if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) ==
			const_cast<cFibElement*>(&fibObject2)->getFibElement( -1 ) ){
	
		cout<<"The previous fib -elementpointer for the function element are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the function element are not equal."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFunction
	if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() ==
			const_cast<cFibElement*>(&fibObject2)->getSuperiorFibElement() ){
	
		cout<<"The superior fib -elementpointer for the function element are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the function element are not equal."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests if the given fib -element is not conected to other
 * fib -elements.
 *
 * @param fibObject1 the fib -element to check
 * @return the number of errors occured in the test
 */
int testNotConnectedFibElement( const cFibElement &fibObject1 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	//check the getNextFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getNumberOfElements() == 1 ){
	
		cout<<"The fib -object includes just one fib -element. "<<endl;
	}else{
		cerr<<"Error: The fib -object includes just not one fib -element, but "<<
			const_cast<cFibElement*>(&fibObject1)->getNumberOfElements() <<" ."<<endl;
		iReturn++;
	}
	
	//check the getNextFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -elementpointer for the point -elements is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -elementpointer for the point -elements is not NULL."<<endl;
		iReturn++;
	}
	//check the getFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -elementpointer for the point -elements is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the point -elements is not NULL."<<endl;
		iReturn++;
	}
	
	//check the getSuperiorFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -elementpointer for the point -elements is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the point -elements is not NULL."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the copy methods and copyconstructor of the cFunction class.
 *
 * methods tested:
 * 	- cFunction( const cFunction &functionElement );
 * 	- cFibElement *clone( ) const;
 * 	- cFunction *copy( const unsignedIntFib iObjectFunction=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementFunction=0 ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a simple cFunction"<<endl;

	cout<<"cFunctionValue underFunction1( 1.0 );"<<endl;
	cFunctionValue underFunction1( 1.0 );
	cout<<"cFunction functionSimple( underFunction1 );"<<endl;
	cFunction functionSimple( underFunction1 );

	cout<<"cFunction functionSimpleCopyConstruct( functionSimple );"<<endl;
	cFunction functionSimpleCopyConstruct( functionSimple );

	iReturn += testCompareTwoEqualObjectsStructur( functionSimpleCopyConstruct, "functionSimpleCopyConstruct", functionSimple, "functionSimple" );

	cout<<"cFibElement * pFunctionSimpleClone = functionSimple.clone();"<<endl;
	cFibElement * pFunctionSimpleClone = functionSimple.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pFunctionSimpleClone, "pFunctionSimpleClone", functionSimple, "functionSimple" );
	delete pFunctionSimpleClone;

	cout<<"cFibElement * pFunctionSimpleCopy = functionSimple.copy();"<<endl;
	cFibElement * pFunctionSimpleCopy = functionSimple.copy();

	iReturn += testCompareTwoEqualObjectsStructur( *pFunctionSimpleCopy, "pFunctionSimpleCopy", functionSimple, "functionSimple" );
	delete pFunctionSimpleCopy;

	cout<<"cFibElement * pFunctionSimpleCopyElement = functionSimple.copyElement();"<<endl;
	cFibElement * pFunctionSimpleCopyElement = functionSimple.copyElement();

	iReturn += testCompareTwoEqualObjectsStructur( *pFunctionSimpleCopyElement, "pFunctionSimpleCopyElement", functionSimple, "functionSimple" );
	delete pFunctionSimpleCopyElement;
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying for a other object or elementpoint"<<endl;

	cout<<"cFibElement * pFunctionSimpleNoCopy = functionSimple.copy( 1 );"<<endl;
	cFibElement * pFunctionSimpleNoCopy = functionSimple.copy( 1 );

	if ( pFunctionSimpleNoCopy == NULL ){
	
		cout<<"The cFunction was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cFunction was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pFunctionSimpleNoCopy;
	}

	cout<<"cFibElement * pFunctionSimpleNoCopyElement = functionSimple.copyElement( 'f', 2 );"<<endl;
	cFibElement * pFunctionSimpleNoCopyElement = functionSimple.copyElement( 'f', 2 );

	if ( pFunctionSimpleNoCopyElement == NULL ){
	
		cout<<"The cFunction -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cFunction -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pFunctionSimpleNoCopyElement;
	}

	cout<<"pFunctionSimpleNoCopyElement = functionSimple.copyElement( 'u', 2 );"<<endl;
	pFunctionSimpleNoCopyElement = functionSimple.copyElement( 'u', 2 );

	if ( pFunctionSimpleNoCopyElement == NULL ){
	
		cout<<"The cFunction -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cFunction -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pFunctionSimpleNoCopyElement;
	}

	cout<<"pFunctionSimpleNoCopyElement = functionSimple.copyElement( 'r', 1 );"<<endl;
	pFunctionSimpleNoCopyElement = functionSimple.copyElement( 'r', 1 );

	if ( pFunctionSimpleNoCopyElement == NULL ){
	
		cout<<"The cFunction -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cFunction -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pFunctionSimpleNoCopyElement;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunction with all members set"<<endl;

	//function in fib -element structur
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;

	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeUnderFunction testTypeFunction;"<<endl;
	cTypeUnderFunction testTypeFunction;
	
	//create vector domain with two elements
	cout<<"cDomainNaturalNumberBit domainsNat9( 9 );"<<endl;
	cDomainNaturalNumberBit domainsNat9( 9 );

	cout<<"rootD2.getDomains()->addDomain( testTypeFunction, &domainsNat9 );"<<endl;
	rootD2.getDomains()->addDomain( testTypeFunction, &domainsNat9 );

	cout<<"cFunctionValue underFunction2( 2.2 );"<<endl;
	cFunctionValue underFunction2( 2.2 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction function2E2( underFunction2, &poinNext, &rootD2 );"<<endl;
	cFunction function2E2( underFunction2, &poinNext, &rootD2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinPrev;"<<endl;
	cPoint poinPrev;
	cout<<"cFunction function2E2( underFunction2, &rootD2, &poinPrev, &poinNext );"<<endl;
	cFunction function2E2( underFunction2, &rootD2, &poinPrev, &poinNext );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"cFunction function2E2CopyConstruct( function2E2 );"<<endl;
	cFunction function2E2CopyConstruct( function2E2 );

	if ( function2E2CopyConstruct.equalElement( function2E2 ) ){

		cout<<"The function2E2CopyConstruct fib -element is equal to function2E2. "<<endl;
	}else{
		cerr<<"Error: The function2E2CopyConstruct fib -element is not equal to function2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( function2E2CopyConstruct );

	cout<<"cFibElement * pFunction2E2Copy = function2E2.copy();"<<endl;
	cFibElement * pFunction2E2Copy = function2E2.copy();
	iReturn += testCompareTwoEqualObjects( *pFunction2E2Copy, "pFunction2E2Copy", function2E2, "function2E2" );
	//check the getFibElement() methode from cFunction
	if ( NULL == pFunction2E2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous fib -elementpointer for the function element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the function element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFunction
	if ( NULL == pFunction2E2Copy->getSuperiorFibElement() ){
	
		cout<<"The superior fib -elementpointer for the function element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the function element is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( pFunction2E2Copy );

	cout<<"cFibElement * pFunction2E2CopyElement = function2E2.copyElement( 'u', 1 );"<<endl;
	cFibElement * pFunction2E2CopyElement = function2E2.copyElement( 'u', 1 );

	if ( pFunction2E2CopyElement->equalElement( function2E2 ) ){
	
		cout<<"The pFunction2E2CopyElement fib -element is equal to function2E2. "<<endl;
	}else{
		cerr<<"Error: The pFunction2E2CopyElement fib -element is not equal to function2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pFunction2E2CopyElement );
	delete pFunction2E2CopyElement;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a limb with more then one function element and pointelement"<<endl;

	//a limb with more then one function element and pointelement
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cFunction function3( underFunction2 );"<<endl;
	cFunction function3( underFunction2 );
	cout<<"cFunctionValue underFunction3( 3.0 );"<<endl;
	cFunctionValue underFunction3( 3.0 );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction function1Obj2( underFunction3, &function3 );"<<endl;
	cFunction function1Obj2( underFunction3, &function3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction function1Obj2( underFunction3, NULL, NULL, &function3 );"<<endl;
	cFunction function1Obj2( underFunction3, NULL, NULL, &function3 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<endl<<"cFunction function1Obj2CopyConstruct( function1Obj2 );"<<endl;
	cFunction function1Obj2CopyConstruct( function1Obj2 );

	if ( function1Obj2CopyConstruct.equalElement( function1Obj2 ) ){
	
		cout<<"The function1Obj2CopyConstruct fib -element is equal to function1Obj2. "<<endl;
	}else{
		cerr<<"Error: The function1Obj2CopyConstruct fib -element is not equal to function1Obj2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( function1Obj2CopyConstruct );

	cout<<"cFibElement * pFunction1ColorSwO2LayerO1CopyConstructCopy = function1Obj2CopyConstruct.copy();"<<endl;
	cFibElement * function1Obj2Copy =
		function1Obj2.copy();

	iReturn += testCompareTwoEqualObjects(
		*function1Obj2Copy, "function1Obj2Copy",
		function1Obj2, "function1Obj2" );
	//check the getFibElement() methode from cFunction
	if ( NULL == function1Obj2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous fib -elementpointer for the function element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the function element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cFunction
	if ( function1Obj2Copy->getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -elementpointer for the function element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the function element is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( function1Obj2Copy );

	cout<<"cFibElement * pFunction1Obj2 = function1Obj2.copyElement();"<<endl;
	cFibElement * pFunction1Obj2 = function1Obj2.copyElement();

	if ( pFunction1Obj2->equalElement( function1Obj2 ) ){
	
		cout<<"The pFunction1Obj2 fib -element is equal to function1Obj2. "<<endl;
	}else{
		cerr<<"Error: The pFunction1Obj2 fib -element is not equal to function1Obj2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pFunction1Obj2 );
	delete pFunction1Obj2;


	return iReturn;
}



/**
 * This method tests a in the xml -format stored cFunction.
 * The underfunction of the cFunction should be a value underfunction
 * ( cFunctionValue ).
 *
 * @param szFilename the name of the file wher the cFibVector is stored
 * @param uiDefinedVariableValue the number of the defined variable
 * @return the number of errors occured in the test
 */
int testXmlFunction( const string szFilename, unsigned int uiDefinedVariableValue ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cFunction:"<<endl;
	
	TiXmlDocument xmlDocFunctionValue( szFilename );
	bool loadOkay = xmlDocFunctionValue.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocFunctionValue );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();
		
		const string szFunctionElementName = "function";
		if ( szElementName == szFunctionElementName ){
			cout<<"The root element is correctly named \""<< szFunctionElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szFunctionElementName <<"\"."<<endl;
			iReturn++;
		}
		
		const char * szDefinedVariableValue = pXmlElement->Attribute( "define_variable" );
		
		if ( szDefinedVariableValue == NULL ){
			cerr<<"Error: The function has no defined variable."<<endl;
			iReturn++;
		}else{
			unsigned long uiDefinedVariableValueStored = atol( szDefinedVariableValue );
			 if ( uiDefinedVariableValueStored == uiDefinedVariableValue ) {
				cout<<"The defined variable of the function is correctly \""<< uiDefinedVariableValue <<"\". "<<endl;
			}else{
				cerr<<"Error: The defined variable of the function is \""<< szDefinedVariableValue
					<<"\", but should be \""<< uiDefinedVariableValue <<"\"."<<endl;
				iReturn++;
			}
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	TiXmlHandle xmlHandleUnderFunction = TiXmlHandle( pXmlElement );
	TiXmlElement * pXmlUnderFunction = xmlHandleUnderFunction.FirstChild().Element();
	
	if ( pXmlUnderFunction ) {
		string szElementName = pXmlUnderFunction->Value();

		if ( szElementName == "subfunction" ){
			cout<<"The subelement is correctly named \"subfunction\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the subelement is "<< szElementName <<" and not \"subfunction\"."<<endl;
			iReturn++;
		}
		
		xmlHandleUnderFunction = TiXmlHandle( pXmlUnderFunction );
		pXmlUnderFunction = xmlHandleUnderFunction.FirstChild().Element();
		
		if ( pXmlUnderFunction ){
			string szElementName = pXmlUnderFunction->Value();
	
			if ( szElementName == "value" ){
				cout<<"The subelement is correctly named \"value\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the subelement is "<< szElementName <<" and not \"value\"."<<endl;
				iReturn++;
			}
	
		}else{// pXmlUnderFunction == NULL
			cerr<<"Error: No underfunction 2 handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
			return iReturn;
		}

	}else{// pXmlUnderFunction == NULL
		cerr<<"Error: No underfunction handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	return iReturn;
}


/**
 * This method tests the storeXml() method of the cFunction class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an function with an empty underfunction"<<endl;

	cout<<"cFunctionValue underFunction1( 1 );"<<endl;
	cFunctionValue underFunction1( 1 );
	cout<<"cFunction function1( underFunction1 );"<<endl;
	cFunction function1( underFunction1 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlFunctionFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "function1.xml" );
	ofstream * pFileVectorPostion = new ofstream( szXmlFunctionFileName );
	
	bool bStoreSuccesfull = function1.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFunction was stored successfull to the file \""<< szXmlFunctionFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFunction to the file \""<< szXmlFunctionFileName <<"\" failed."<<endl;
		iReturn++;
	}	
	iReturn += testXmlFunction( szXmlFunctionFileName, 0 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an function with the variable value set"<<endl;

	cout<<"cFunctionValue underFunction2( 2.2 );"<<endl;
	cFunctionValue underFunction2( 2.2 );
	cout<<"function1.setUnderFunction( underFunction2 );"<<endl;
	function1.setUnderFunction( underFunction2 );
	
	cout<<"function1.getDefinedVariable()->setIntegerValue( 3 );"<<endl;
	function1.getDefinedVariable()->setIntegerValue( 3 );
	
	szFileNameBuffer[0] = 0;
	szXmlFunctionFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "function2p2.xml" );
	pFileVectorPostion = new ofstream( szXmlFunctionFileName );
	
	bStoreSuccesfull = function1.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFunction was stored successfull to the file \""<< szXmlFunctionFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFunction to the file \""<< szXmlFunctionFileName <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlFunction( szXmlFunctionFileName, 3 );

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

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method one underfunction"<<endl;

	cout<<"cPoint point1;"<<flush<<endl;
	cPoint point1;

	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	
	cout<<"cFunctionValue underFunction1( 1 );"<<endl;
	cFunctionValue underFunction1( 1 );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction function1( underFunction1, &point1, &root );"<<endl;
	cFunction function1( underFunction1, &point1, &root );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction function1( underFunction1, &root, &root, &point1 );"<<endl;
	cFunction function1( underFunction1, &root, &root, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//test get compressed size
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	unsigned int uiCompressedSize = 4 + (2 + 16) + 5;
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	unsigned int uiCompressedSize = 4 + 8 + (2 + 16) + 5;
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	if ( (unsigned int)(function1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			function1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "function1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bool bStoreSuccesfull = function1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	const char cFunction1[] = { (char)0x4B, (char)0x00, (char)0x80, (char)0x04  };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFunction1, 4 );
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	const char cFunction1[] = { (char)0x0B, (char)0x40, (char)0x00, (char)0x80, (char)0x04  };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFunction1, 5 );
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with changed values"<<endl;

	cout<<"cFunctionValue underFunction2( 9 );"<<endl;
	cFunctionValue underFunction2( 9 );
	cout<<"function1.setUnderFunction( underFunction2 );"<<endl;
	function1.setUnderFunction( underFunction2 );
	
	cout<<"function1.getDefinedVariable()->setIntegerValue( 1 );"<<endl;
	function1.getDefinedVariable()->setIntegerValue( 1 );
	
	//test get compressed size
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	uiCompressedSize = 4 + (2 + 16) + 5;
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	uiCompressedSize = 4 + 8 + (2 + 16) + 5;
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	if ( (unsigned int)(function1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			function1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "functionChV.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = function1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	const char szFunctionChV[] = { (char)0x4B, (char)0x02, (char)0x80, (char)0x04  };
	iReturn += compareBytsWithFile( szFileNameBuffer, szFunctionChV, 4 );
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	const char szFunctionChV[] = { (char)0x1B, (char)0x40, (char)0x02, (char)0x80, (char)0x04  };
	iReturn += compareBytsWithFile( szFileNameBuffer, szFunctionChV, 5 );
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with given domains"<<endl;

	cout<<"cTypeUnderFunction testTypeFunction;"<<endl;
	cTypeUnderFunction testTypeFunction;
	
	//create vector domain with two elements
	cout<<"cDomainNaturalNumberBit domainsNatB6( 6 );"<<endl;
	cDomainNaturalNumberBit domainsNatB6( 6 );

	cout<<"root.getDomains()->addDomain( testTypeFunction, &domainsNatB6 );"<<endl;
	root.getDomains()->addDomain( testTypeFunction, &domainsNatB6 );
	
	cout<<"cTypeVariable testTypeVariable;"<<endl;
	cTypeVariable testTypeVariable;
	
	cout<<"cDomainNaturalNumberBit naturalNumberDomainB4( 4 );"<<endl;
	cDomainNaturalNumberBit naturalNumberDomainB4( 4 );
	
	cout<<"root.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB4 );"<<endl;
	root.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB4 );

	cout<<"function1.getDefinedVariable()->setIntegerValue( 2 );"<<endl;
	function1.getDefinedVariable()->setIntegerValue( 2 );
	
	//test get compressed size
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	uiCompressedSize = 4 + (2 + 6) + 5;
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	uiCompressedSize = 4 + 4 + (2 + 6) + 5;
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	if ( (unsigned int)(function1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			function1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "functionDom.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = function1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	const char szFunctionDom[] = { (char)0x4B, (char)0x22, (char)0x01  };
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	const char szFunctionDom[] = { (char)0x2B, (char)0x24, (char)0x12  };
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	iReturn += compareBytsWithFile( szFileNameBuffer, szFunctionDom, 3 );


	return iReturn;
}




/**
 * This method positions methods of the class.
 *
 * methods tested:
 * 	- cUnderFunction * getUnderFunction() const;
 * 	- bool setUnderFunction( const cUnderFunction & underFunction );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testUnderFunction( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the underfunction -methods"<<endl;
	
	cout<<"cFunctionValue underFunction1( 1 );"<<endl;
	cFunctionValue underFunction1( 1 );
	cout<<"cFunction function1( underFunction1 );"<<endl;
	cFunction function1( underFunction1 );
	
	//check the getUnderFunction() methode from cFunction
	if ( function1.getUnderFunction() != NULL ){
	
		if ( function1.getUnderFunction() != &underFunction1 ){
		
			cout<<"The underfunction for the function element is correctly not the underFunction1 object. "<<endl;
		}else{
			cerr<<"Error: The underfunction for the function element is the underFunction1 object."<<endl;
			iReturn++;
		}
		if ( underFunction1 == *(function1.getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction underFunction1. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction underFunction1. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the underfunction
	if ( function1.getUnderFunction()->getDefiningFibElement() == &function1  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			function1.getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			function1.getUnderFunction()->getDefiningFibElement() <<
			" but should be function1="<< &function1 <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from the underfunction
	if ( function1.getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			function1.getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			function1.getUnderFunction()->getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}


	cout<<"cFunctionValue underFunction2( 2.0 );"<<endl;
	cFunctionValue underFunction2( 2.0 );
	cout<<"function1.setUnderFunction( underFunction2 );"<<endl;
	function1.setUnderFunction( underFunction2 );

	//check the getUnderFunction() methode from cFunction
	if ( function1.getUnderFunction() != NULL ){
	
		if ( function1.getUnderFunction() != &underFunction2 ){
		
			cout<<"The underfunction for the function element is correctly not the underFunction2 object. "<<endl;
		}else{
			cerr<<"Error: The underfunction for the function element is the underFunction2 object."<<endl;
			iReturn++;
		}
		if ( underFunction2 == *(function1.getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction underFunction2. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction underFunction2. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the underfunction
	if ( function1.getUnderFunction()->getDefiningFibElement() == &function1  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			function1.getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			function1.getUnderFunction()->getDefiningFibElement() <<
			" but should be function1="<< &function1 <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from the underfunction
	if ( function1.getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			function1.getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			function1.getUnderFunction()->getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a variable underfunction"<<endl;
	
	cout<<"cRoot rootEmpty;"<<endl;
	cRoot rootEmpty;
	cout<<"rootEmpty.setNumberOfInputVariables( 10 );"<<endl;
	rootEmpty.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 =  rootEmpty.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 =  rootEmpty.getInputVariable( 1 );
	
	cout<<"cFunctionVariable underFunctionVariable( pVariable1 );"<<endl;
	cFunctionVariable underFunctionVariable( pVariable1 );
	cout<<"function1.setUnderFunction( underFunctionVariable );"<<endl;
	function1.setUnderFunction( underFunctionVariable );

	//check the getUnderFunction() methode from cFunction
	if ( function1.getUnderFunction() != NULL ){
	
		if ( function1.getUnderFunction() != &underFunctionVariable ){
		
			cout<<"The underfunction for the function element is correctly not the underFunctionVariable object. "<<endl;
		}else{
			cerr<<"Error: The underfunction for the function element is the underFunctionVariable object."<<endl;
			iReturn++;
		}
		if ( underFunctionVariable == *(function1.getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction underFunctionVariable. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction underFunctionVariable. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from the underfunction
	if ( function1.getUnderFunction()->getDefiningFibElement() == &function1  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			function1.getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			function1.getUnderFunction()->getDefiningFibElement() <<
			" but should be function1="<< &function1 <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from the underfunction
	if ( function1.getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			function1.getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			function1.getUnderFunction()->getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a absolutvalue underfunction which is valid"<<endl;
	
	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeUnderFunction testTypeFunction;"<<endl;
	cTypeUnderFunction testTypeFunction;
	
	//create vector domain with two elements
	cout<<"cDomainNaturalNumberBit natDomain8( 8 );"<<endl;
	cDomainNaturalNumberBit natDomain8( 8 );

	cout<<"rootD2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	rootD2.getDomains()->addDomain( testTypeFunction, &natDomain8 );

	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	
	
	cout<<"cFunctionAbs underFunctionAbs( & underFunction1 );"<<endl;
	cFunctionAbs underFunctionAbs( & underFunction1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionAbs( underFunctionAbs, &point1, &rootD2 );"<<endl;
	cFunction functionAbs( underFunctionAbs, &point1, &rootD2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionAbs( underFunctionAbs, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionAbs( underFunctionAbs, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cFunction * pFunctionToTest = &functionAbs;
	cUnderFunction * pUnderFunction = &underFunctionAbs;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionAbs="<< &functionAbs <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a absolutvalue underfunction which is not valid"<<endl;
	
	cout<<"cFunctionValue underFunction( 24.102 );"<<endl;
	cFunctionValue underFunction( 24.102 );

	cout<<"cFunctionAbs underFunctionAbsNV( &underFunction );"<<endl;
	cFunctionAbs underFunctionAbsNV( &underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionAbsNV( underFunctionAbsNV, &point1 );"<<endl;
	cFunction functionAbsNV( underFunctionAbsNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionAbsNV( underFunctionAbsNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionAbsNV( underFunctionAbsNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionAbsNV;
	pUnderFunction = &underFunctionAbsNV;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionAbs="<< &functionAbs <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a sinus underfunction which is valid"<<endl;
	
	cout<<"cFunctionSin underFunctionSin( & underFunction1 );"<<endl;
	cFunctionSin underFunctionSin( & underFunction1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root3D2;"<<flush<<endl;
	cRoot root3D2;
	cout<<"root3D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root3D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionSin( underFunctionSin, &point1, &root3D2 );"<<endl;
	cFunction functionSin( underFunctionSin, &point1, &root3D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSin( underFunctionSin, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionSin( underFunctionSin, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionSin;
	pUnderFunction = &underFunctionSin;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionSin="<< &functionSin <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a sinus underfunction which is not valid"<<endl;
	
	cout<<"cFunctionSin underFunctionSinNV( &underFunction );"<<endl;
	cFunctionSin underFunctionSinNV( &underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSinNV( underFunctionSinNV, &point1 );"<<endl;
	cFunction functionSinNV( underFunctionSinNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSinNV( underFunctionSinNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionSinNV( underFunctionSinNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionSinNV;
	pUnderFunction = &underFunctionSinNV;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionSin="<< &functionSin <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a logarithm underfunction which is valid"<<endl;
	
	cout<<"cFunctionLog underFunctionLog( & underFunction1 );"<<endl;
	cFunctionLog underFunctionLog( & underFunction1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root4D2;"<<flush<<endl;
	cRoot root4D2;
	cout<<"root4D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root4D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionLog( underFunctionLog, &point1, &root4D2 );"<<endl;
	cFunction functionLog( underFunctionLog, &point1, &root4D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionLog( underFunctionLog, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionLog( underFunctionLog, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionLog;
	pUnderFunction = &underFunctionLog;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionLog="<< &functionLog <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a logarithm underfunction which is not valid"<<endl;
	
	cout<<"cFunctionLog underFunctionLogNV( &underFunction );"<<endl;
	cFunctionLog underFunctionLogNV( &underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionLogNV( underFunctionLogNV, &point1 );"<<endl;
	cFunction functionLogNV( underFunctionLogNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionLogNV( underFunctionLogNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionLogNV( underFunctionLogNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionLogNV;
	pUnderFunction = &underFunctionLogNV;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionLog="<< &functionLog <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a arcus sinus underfunction which is valid"<<endl;
	
	cout<<"cFunctionArcsin underFunctionArcsin( & underFunction1 );"<<endl;
	cFunctionArcsin underFunctionArcsin( & underFunction1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root5D2;"<<flush<<endl;
	cRoot root5D2;
	cout<<"root5D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root5D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionArcsin( underFunctionArcsin, &point1, &root5D2 );"<<endl;
	cFunction functionArcsin( underFunctionArcsin, &point1, &root5D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionArcsin( underFunctionArcsin, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionArcsin( underFunctionArcsin, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionArcsin;
	pUnderFunction = &underFunctionArcsin;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionArcsin="<< &functionArcsin <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a arcus sinus underfunction which is not valid"<<endl;
	
	cout<<"cFunctionArcsin underFunctionArcsinNV( &underFunction );"<<endl;
	cFunctionArcsin underFunctionArcsinNV( &underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionArcsinNV( underFunctionArcsinNV, &point1 );"<<endl;
	cFunction functionArcsinNV( underFunctionArcsinNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionArcsinNV( underFunctionArcsinNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionArcsinNV( underFunctionArcsinNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionArcsinNV;
	pUnderFunction = &underFunctionArcsinNV;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionArcsin="<< &functionArcsin <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a round underfunction which is valid"<<endl;
	
	cout<<"cFunctionRound underFunctionRound( & underFunction1 );"<<endl;
	cFunctionRound underFunctionRound( & underFunction1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootRound;"<<flush<<endl;
	cRoot rootRound;
	cout<<"rootRound.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	rootRound.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionRound( underFunctionRound, &point1, &rootRound );"<<endl;
	cFunction functionRound( underFunctionRound, &point1, &rootRound );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionRound( underFunctionRound, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionRound( underFunctionRound, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionRound;
	pUnderFunction = &underFunctionRound;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionRound="<< &functionRound <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a round underfunction which is not valid"<<endl;
	
	cout<<"cFunctionRound underFunctionRoundNV( &underFunction );"<<endl;
	cFunctionRound underFunctionRoundNV( &underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionRoundNV( underFunctionRoundNV, &point1 );"<<endl;
	cFunction functionRoundNV( underFunctionRoundNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionRoundNV( underFunctionRoundNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionRoundNV( underFunctionRoundNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionRoundNV;
	pUnderFunction = &underFunctionRoundNV;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionRound="<< &functionRound <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a addition underfunction which is valid"<<endl;
	
	cout<<"cFunctionAdd underFunctionAdd( underFunction1, underFunction2 );"<<endl;
	cFunctionAdd underFunctionAdd( underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root6D2;"<<flush<<endl;
	cRoot root6D2;
	cout<<"root6D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root6D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionAdd( underFunctionAdd, &point1, &root6D2 );"<<endl;
	cFunction functionAdd( underFunctionAdd, &point1, &root6D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionAdd( underFunctionAdd, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionAdd( underFunctionAdd, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionAdd;
	pUnderFunction = &underFunctionAdd;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionAdd="<< &functionAdd <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a addition underfunction which is not valid"<<endl;
	
	cout<<"cFunctionAdd underFunctionAddNV( underFunction1, underFunction );"<<endl;
	cFunctionAdd underFunctionAddNV( underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionAddNV( underFunctionAddNV, &point1 );"<<endl;
	cFunction functionAddNV( underFunctionAddNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionAddNV( underFunctionAddNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionAddNV( underFunctionAddNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionAddNV;
	pUnderFunction = &underFunctionAddNV;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionAdd="<< &functionAdd <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a subtraction underfunction which is valid"<<endl;
	
	cout<<"cFunctionSub underFunctionSub( underFunction1, underFunction2 );"<<endl;
	cFunctionSub underFunctionSub( underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root7D2;"<<flush<<endl;
	cRoot root7D2;
	cout<<"root7D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root7D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionSub( underFunctionSub, &point1, &root7D2 );"<<endl;
	cFunction functionSub( underFunctionSub, &point1, &root7D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSub( underFunctionSub, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionSub( underFunctionSub, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionSub;
	pUnderFunction = &underFunctionSub;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionSub="<< &functionSub <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a subtraction underfunction which is not valid"<<endl;
	
	cout<<"cFunctionSub underFunctionSubNV( underFunction1, underFunction );"<<endl;
	cFunctionSub underFunctionSubNV( underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSubNV( underFunctionSubNV, &point1 );"<<endl;
	cFunction functionSubNV( underFunctionSubNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionSubNV( underFunctionSubNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionSubNV( underFunctionSubNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionSubNV;
	pUnderFunction = &underFunctionSubNV;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionSub="<< &functionSub <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a multiplication underfunction which is valid"<<endl;
	
	cout<<"cFunctionMult underFunctionMult( underFunction1, underFunction2 );"<<endl;
	cFunctionMult underFunctionMult( underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root8D2;"<<flush<<endl;
	cRoot root8D2;
	cout<<"root8D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root8D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionMult( underFunctionMult, &point1, &root8D2 );"<<endl;
	cFunction functionMult( underFunctionMult, &point1, &root8D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMult( underFunctionMult, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionMult( underFunctionMult, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionMult;
	pUnderFunction = &underFunctionMult;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionMult="<< &functionMult <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a multiplication underfunction which is not valid"<<endl;
	
	cout<<"cFunctionMult underFunctionMultNV( underFunction1, underFunction );"<<endl;
	cFunctionMult underFunctionMultNV( underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMultNV( underFunctionMultNV, &point1 );"<<endl;
	cFunction functionMultNV( underFunctionMultNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMultNV( underFunctionMultNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionMultNV( underFunctionMultNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionMultNV;
	pUnderFunction = &underFunctionMultNV;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionMult="<< &functionMult <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a division underfunction which is valid"<<endl;
	
	cout<<"cFunctionDiv underFunctionDiv( underFunction1, underFunction2 );"<<endl;
	cFunctionDiv underFunctionDiv( underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root9D2;"<<flush<<endl;
	cRoot root9D2;
	cout<<"root9D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root9D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionDiv( underFunctionDiv, &point1, &root9D2 );"<<endl;
	cFunction functionDiv( underFunctionDiv, &point1, &root9D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionDiv( underFunctionDiv, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionDiv( underFunctionDiv, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionDiv;
	pUnderFunction = &underFunctionDiv;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionDiv="<< &functionDiv <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a division underfunction which is not valid"<<endl;
	
	cout<<"cFunctionDiv underFunctionDivNV( underFunction1, underFunction );"<<endl;
	cFunctionDiv underFunctionDivNV( underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionDivNV( underFunctionDivNV, &point1 );"<<endl;
	cFunction functionDivNV( underFunctionDivNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionDivNV( underFunctionDivNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionDivNV( underFunctionDivNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionDivNV;
	pUnderFunction = &underFunctionDivNV;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionDiv="<< &functionDiv <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a exponent underfunction which is valid"<<endl;
	
	cout<<"cFunctionExp underFunctionExp( underFunction1, underFunction2 );"<<endl;
	cFunctionExp underFunctionExp( underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root10D2;"<<flush<<endl;
	cRoot root10D2;
	cout<<"root10D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root10D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionExp( underFunctionExp, &point1, &root10D2 );"<<endl;
	cFunction functionExp( underFunctionExp, &point1, &root10D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionExp( underFunctionExp, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionExp( underFunctionExp, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionExp;
	pUnderFunction = &underFunctionExp;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionExp="<< &functionExp <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a exponent underfunction which is not valid"<<endl;
	
	cout<<"cFunctionExp underFunctionExpNV( underFunction1, underFunction );"<<endl;
	cFunctionExp underFunctionExpNV( underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionExpNV( underFunctionExpNV, &point1 );"<<endl;
	cFunction functionExpNV( underFunctionExpNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionExpNV( underFunctionExpNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionExpNV( underFunctionExpNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionExpNV;
	pUnderFunction = &underFunctionExpNV;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionExp="<< &functionExp <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a minimum underfunction which is valid"<<endl;
	
	cout<<"cFunctionMin underFunctionMin( underFunction1, underFunction2 );"<<endl;
	cFunctionMin underFunctionMin( underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root11D2;"<<flush<<endl;
	cRoot root11D2;
	cout<<"root11D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root11D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionMin( underFunctionMin, &point1, &root11D2 );"<<endl;
	cFunction functionMin( underFunctionMin, &point1, &root11D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMin( underFunctionMin, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionMin( underFunctionMin, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionMin;
	pUnderFunction = &underFunctionMin;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionMin="<< &functionMin <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a minimum underfunction which is not valid"<<endl;
	
	cout<<"cFunctionMin underFunctionMinNV( underFunction1, underFunction );"<<endl;
	cFunctionMin underFunctionMinNV( underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMinNV( underFunctionMinNV, &point1 );"<<endl;
	cFunction functionMinNV( underFunctionMinNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMinNV( underFunctionMinNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionMinNV( underFunctionMinNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionMinNV;
	pUnderFunction = &underFunctionMinNV;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionMin="<< &functionMin <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a maximum underfunction which is valid"<<endl;
	
	cout<<"cFunctionMax underFunctionMax( underFunction1, underFunction2 );"<<endl;
	cFunctionMax underFunctionMax( underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root12D2;"<<flush<<endl;
	cRoot root12D2;
	cout<<"root12D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root12D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionMax( underFunctionMax, &point1, &root12D2 );"<<endl;
	cFunction functionMax( underFunctionMax, &point1, &root12D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMax( underFunctionMax, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionMax( underFunctionMax, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionMax;
	pUnderFunction = &underFunctionMax;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionMax="<< &functionMax <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a maximum underfunction which is not valid"<<endl;
	
	cout<<"cFunctionMax underFunctionMaxNV( underFunction1, underFunction );"<<endl;
	cFunctionMax underFunctionMaxNV( underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMaxNV( underFunctionMaxNV, &point1 );"<<endl;
	cFunction functionMaxNV( underFunctionMaxNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionMaxNV( underFunctionMaxNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionMaxNV( underFunctionMaxNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionMaxNV;
	pUnderFunction = &underFunctionMaxNV;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionMax="<< &functionMax <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a if-underfunction which is valid"<<endl;
	
	cout<<"cConditionTrue conditionTrue;"<<endl;
	cConditionTrue conditionTrue;
	cout<<"cFunctionIf underFunctionIf( conditionTrue, underFunction1, underFunction2 );"<<endl;
	cFunctionIf underFunctionIf( conditionTrue, underFunction1, underFunction2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root13D2;"<<flush<<endl;
	cRoot root13D2;
	cout<<"root13D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );"<<endl;
	root13D2.getDomains()->addDomain( testTypeFunction, &natDomain8 );
	cout<<"cFunction functionIf( underFunctionIf, &point1, &root13D2 );"<<endl;
	cFunction functionIf( underFunctionIf, &point1, &root13D2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionIf( underFunctionIf, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionIf( underFunctionIf, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionIf;
	pUnderFunction = &underFunctionIf;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionIf="<< &functionIf <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->isValid()  ){
		
			cout<<"The underfunction is correctly valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is not valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setting a if-underfunction which is not valid"<<endl;
	
	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;
	cout<<"cFunctionIf underFunctionIfNV( conditionFalse, underFunction1, underFunction );"<<endl;
	cFunctionIf underFunctionIfNV( conditionFalse, underFunction1, underFunction );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionIfNV( underFunctionIfNV, &point1 );"<<endl;
	cFunction functionIfNV( underFunctionIfNV, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionIfNV( underFunctionIfNV, &rootD2, &rootD2, &point1 );"<<endl;
	cFunction functionIfNV( underFunctionIfNV, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	pFunctionToTest = &functionIfNV;
	pUnderFunction = &underFunctionIfNV;
	
	//check the underFunction method from cFunction
	if ( pFunctionToTest->getUnderFunction() != NULL ){
	
		if ( pUnderFunction != pFunctionToTest->getUnderFunction() ){
		
			cout<<"The functions underfunction correctly dosn't point to the given underfunction. "<<endl;
		}else{
			cerr<<"Error: The functions underfunction do point to the given underfunction. "<<endl;
			iReturn++;
		}
		if ( *pUnderFunction == *(pFunctionToTest->getUnderFunction()) ){
		
			cout<<"The function has the correct underfunction. "<<endl;
		}else{
			cerr<<"Error: The function has a not the correct underfunction. "<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getDefiningFibElement() == pFunctionToTest  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				pFunctionToTest->getUnderFunction()->getDefiningFibElement() <<
				" but should be functionIf="<< &functionIf <<" ."<<endl;
			iReturn++;
		}
		//check the isValid() methode from the underfunction
		if ( ! (pFunctionToTest->getUnderFunction()->isValid())  ){
		
			cout<<"The underfunction is correctly not valid. "<<endl;
		}else{
			cerr<<"Error: The underfunction is valid."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from the underfunction
		if ( pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() == NULL  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				pFunctionToTest->getUnderFunction()->getSuperiorUnderFunction() <<
				" but should be NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The function has a no underfunction (NULL is given back). "<<endl;
		iReturn++;
	}
	
	
	return iReturn;
}


/**
 * This method tests the variable methods of the cFunction class.
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
	
	cout<<"cFunctionValue underFunction1( 1 );"<<endl;
	cFunctionValue underFunction1( 1 );
	
	cout<<"cFunctionValue underFunction2( 2.2 );"<<endl;
	cFunctionValue underFunction2( 2.2 );

	cout<<"cFunction function1( underFunction1 );"<<endl;
	cFunction function1( underFunction1 );
	
	//check the isUsedVariable() methode from cFunction
	cout<<"function1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! function1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the function element. "<<endl;
		iReturn++;
	}
	set<cFibVariable*> setCorrectUsedVariables;
	
	//check getUsedVariables()
	cout<<"setUsedVariables = function1.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = function1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing variable methods on a function with a containing point"<<endl;

	cout<<"cVectorPosition vecPositionE3( 3 );"<<endl;
	cVectorPosition vecPositionE3( 3 );

	cout<<"cPoint point1( &vecPositionE3 );"<<endl;
	cPoint point1( &vecPositionE3 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionPoint( underFunction1, &point1 );"<<endl;
	cFunction functionPoint( underFunction1, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cFunction functionPoint( underFunction1, NULL, NULL, &point1 );"<<endl;
	cFunction functionPoint( underFunction1, NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the isUsedVariable() methode from cFunction
	cout<<"functionPoint.isUsedVariable( pVariable1 )"<<endl;
	if ( ! functionPoint.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the function element. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.clear();
	
	//check getUsedVariables()
	cout<<"setUsedVariables = functionPoint.getUsedVariables(); "<<endl;
	setUsedVariables = functionPoint.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"point1.getPosition()->setVariable( 3, pVariable1 );"<<endl;
	point1.getPosition()->setVariable( 3, pVariable1 );

	//check the isUsedVariable() methode from cFunction
	cout<<"functionPoint.isUsedVariable( pVariable1 )"<<endl;
	if ( ! functionPoint.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the function element. "<<endl;
		iReturn++;
	}
	cout<<"point1.isUsedVariable( pVariable1 )"<<endl;
	if ( point1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the function element. "<<endl;
		iReturn++;
	}
	cout<<"functionPoint.isUsedVariable( pVariable1, ED_BELOW_EQUAL )"<<endl;
	if ( functionPoint.isUsedVariable( pVariable1, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable1 is correctly used ED_BELOW_EQUAL the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used ED_BELOW_EQUAL the function element. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = functionPoint.getUsedVariables(); "<<endl;
	setUsedVariables = functionPoint.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.insert( pVariable1 );
	//check getUsedVariables()
	cout<<"setUsedVariables = functionPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = functionPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back for ED_BELOW_EQUAL. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong for ED_BELOW_EQUAL. "<<endl;
		iReturn++;
	}

	cout<<"point1.getPosition()->setVariable( 1, pVariable2 );"<<endl;
	point1.getPosition()->setVariable( 1, pVariable2 );
	
	//check the isUsedVariable() methode from cFunction
	cout<<"functionPoint.isUsedVariable( pVariable2 )"<<endl;
	if ( ! functionPoint.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the function element. "<<endl;
		iReturn++;
	}
	cout<<"point1.isUsedVariable( pVariable2 )"<<endl;
	if ( point1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the function element. "<<endl;
		iReturn++;
	}
	cout<<"functionPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( functionPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly used ED_BELOW_EQUAL the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used ED_BELOW_EQUAL the function element. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = functionPoint.getUsedVariables(); "<<endl;
	setUsedVariables = functionPoint.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.insert( pVariable2 );
	//check getUsedVariables()
	cout<<"setUsedVariables = functionPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = functionPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back for ED_BELOW_EQUAL. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong for ED_BELOW_EQUAL. "<<endl;
		iReturn++;
	}
	
	cout<<"functionPoint.replaceVariable( pVariable2, pVariable3 );"<<endl;
	bool bVariableReplaced = functionPoint.replaceVariable( pVariable2, pVariable3 );
	setCorrectUsedVariables.erase( pVariable2 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFunction
	cout<<"functionPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( ! functionPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly not used ED_BELOW_EQUAL the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used ED_BELOW_EQUAL the function element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFunction
	cout<<"functionPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL )"<<endl;
	if ( functionPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_BELOW_EQUAL the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_BELOW_EQUAL the function element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = functionPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = functionPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods getDefinedVariable(), isDefinedVariable( ED_POSITION ) and getDefinedVariables( ED_POSITION )"<<endl;

	cout<<"pDefinedVariable = functionPoint.getDefinedVariable()"<<endl;
	cFibVariable * pDefinedVariable = functionPoint.getDefinedVariable();

	if ( pDefinedVariable != NULL ){
	
		cout<<"The fib -element correctly defines a variable. "<<endl;
	}else{
		cerr<<"Error: The fib -element dosn't defines a variable.(NULL is returned) "<<endl;
		iReturn++;
	}
	
	//check the isDefinedVariable() methode from cList
	cout<<"functionPoint.isDefinedVariable( pDefinedVariable, ED_POSITION )"<<endl;
	if ( functionPoint.isDefinedVariable( pDefinedVariable, ED_POSITION ) ){
	
		cout<<"The variable pDefinedVariable is correctly defined in the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pDefinedVariable isn't defined in the function element. "<<endl;
		iReturn++;
	}
	//check the isDefinedVariable() methode from cList
	cout<<"functionPoint.isDefinedVariable( pVariable1, ED_POSITION )"<<endl;
	if ( ! functionPoint.isDefinedVariable( pVariable1, ED_POSITION ) ){
	
		cout<<"The variable pVariable1 is correctly not defined in the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is defined in the function element. "<<endl;
		iReturn++;
	}

	//check getDefinedVariables()
	cout<<"liDefinedVariables = functionPoint.getDefinedVariables( ED_POSITION ); "<<endl;
	list<cFibVariable*> liDefinedVariables = functionPoint.getDefinedVariables( ED_POSITION );
	
	list<cFibVariable*> liDefinedVariablesCorrect;
	liDefinedVariablesCorrect.push_back( pDefinedVariable);
	
	if ( liDefinedVariables == liDefinedVariablesCorrect ){
	
		cout<<"Ther are the correct variables defined in the function element. "<<endl;
	}else{
		cerr<<"Error: Ther aren't the correct variables defined in the function element. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a function with a underfunction which contains a variable"<<endl;
	
	cout<<"cFunctionVariable ufVariable1( pVariable1 );"<<endl;
	cFunctionVariable ufVariable1( pVariable1 );
	
	cout<<"cFunction functionV1( ufVariable1 );"<<endl;
	cFunction functionV1( ufVariable1 );
	
	setCorrectUsedVariables.clear();
	setCorrectUsedVariables.insert( pVariable1 );
	
	//check the isUsedVariable() methode from cFunction
	cout<<"functionV1.isUsedVariable( pVariable1 )"<<endl;
	if ( functionV1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the function element. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = functionV1.getUsedVariables(); "<<endl;
	setUsedVariables = functionV1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"functionV1.replaceVariable( pVariable1, pVariable2 );"<<endl;
	bVariableReplaced = functionV1.replaceVariable( pVariable1, pVariable2 );
	setCorrectUsedVariables.erase( pVariable1 );
	setCorrectUsedVariables.insert( pVariable2 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFunction
	cout<<"functionV1.isUsedVariable( pVariable1, ED_BELOW_EQUAL )"<<endl;
	if ( ! functionV1.isUsedVariable( pVariable1, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly not used ED_BELOW_EQUAL the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used ED_BELOW_EQUAL the function element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFunction
	cout<<"functionV1.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( functionV1.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_BELOW_EQUAL the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_BELOW_EQUAL the function element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = functionV1.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = functionV1.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"functionV1.replaceVariable( pVariable1, pVariable1 );"<<endl;
	bVariableReplaced = functionV1.replaceVariable( pVariable1, pVariable1 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFunction
	cout<<"functionV1.isUsedVariable( pVariable1, ED_POSITION )"<<endl;
	if ( ! functionV1.isUsedVariable( pVariable1, ED_POSITION ) ){
	
		cout<<"The variable pVariable2 is correctly not used ED_POSITION the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used ED_POSITION the function element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFunction
	cout<<"functionV1.isUsedVariable( pVariable2, ED_POSITION )"<<endl;
	if ( functionV1.isUsedVariable( pVariable2, ED_POSITION ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_POSITION the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_POSITION the function element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = functionV1.getUsedVariables( ED_POSITION ); "<<endl;
	setUsedVariables = functionV1.getUsedVariables( ED_POSITION );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"functionV1.replaceVariable( pVariable2, pVariable2 );"<<endl;
	bVariableReplaced = functionV1.replaceVariable( pVariable2, pVariable2 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFunction
	cout<<"functionV1.isUsedVariable( pVariable1, ED_HIGHER_EQUAL )"<<endl;
	if ( ! functionV1.isUsedVariable( pVariable1, ED_HIGHER_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly not used ED_HIGHER_EQUAL the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used ED_HIGHER_EQUAL the function element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cFunction
	cout<<"functionV1.isUsedVariable( pVariable2, ED_HIGHER_EQUAL )"<<endl;
	if ( functionV1.isUsedVariable( pVariable2, ED_HIGHER_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_HIGHER_EQUAL the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_HIGHER_EQUAL the function element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = functionV1.getUsedVariables( ED_HIGHER_EQUAL ); "<<endl;
	setUsedVariables = functionV1.getUsedVariables( ED_HIGHER_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	return iReturn;
}





