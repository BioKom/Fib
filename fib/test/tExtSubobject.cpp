/**
 * @file tExtSubobject
 * file name: tExtSubobject.cpp
 * @author Betti Oesterholz
 * @date 09.11.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cExtSubobject.
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
 * This file contains the test for the class cExtSubobject, which
 * represents an external subobject element.
 *
 *
 * What's tested of class cExtSubobject:
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
 * 	- cExtSubobject( unsignedIntFib uiInNumberOfSubobject, cVectorExtSubobject vecInOutputValues, cFibElement * pInSuperiorElement = NULL );
 * 	- cExtSubobject( unsignedIntFib uiInNumberOfSubobject, unsignedIntFib uiNumberOfOutputVariables=0, cFibElement * pInSuperiorElement = NULL );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
 * 	- cExtSubobject( unsignedIntFib uiInNumberOfSubobject, vector< cFibVariable* > vecInOutputVariables=vector< cFibVariable* >(), cFibElement * pInSuperiorElement = NULL );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
 * 	- cExtSubobject( const cExtSubobject & extObjectElement );
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
 * 	- cExtSubobject *copy( const unsignedIntFib iObjectExtSubobject=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementExtSubobject=0 ) const;
 * 	- bool storeXml( ostream &stream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream &stream ) const;
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
 * 	- unsignedIntFib getNumberSubobject() const;
 * 	- bool setNumberSubobject( const unsignedIntFib iInSubobjectNumber );
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
 * 	- cVectorExtSubobject * getOutputVector();
 * 	- const cVectorExtSubobject * cExtSubobject::getOutputVector() const
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
 * 	- unsignedIntFib getNumberOfOutputVariables() const;
 * 	- vector< cFibVariable * > getOutputVariables();
 * 	- bool setOutputVariables( vector< cFibVariable * > vecOutputValues );
 * 	- cFibVariable * getOutputVariable( const unsignedIntFib uiVariableNumber );
 * 	- bool setOutputVariable( const unsignedIntFib uiVariableNumber, cFibVariable * pOutputVariable );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
 *
 *
 * call: tExtSubobject [MAX_RAND_TEST_SIZE]
 *
 * parameters:
 * 	MAX_RAND_TEST_SIZE
 * 		A number for the random test sizes.
 * 		Standardvalue is 256.
 *
 * Test for:
 *
 * Methods for changing the structur of an Fib object will be tested with
 * tFibElementStructur. Methods for Fib objects will be tested with
 * Methods for storing and restoring will be tested in tFibElementStore.
 */
/*
History:
09.11.2011  Oesterholz  created
28.01.2011  Oesterholz  isValidFibElement() just checks the Fib element
29.01.2011  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR implemented:
	the input values are now a vector of values
09.10.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cExtSubobject.h"
#include "cExtObject.h"
#include "cPoint.h"
#include "cRoot.h"
#include "cProperty.h"
#include "cArea.h"
#include "cList.h"

#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	#include "cVectorExtSubobject.h"
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

#include "cVectorArea.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainNaturalNumber.h"
#include "cDomainVector.h"
#include "cTypeVariable.h"
#include "cTypeExtSubobject.h"
#include "cTypeUnderFunction.h"
#include "cTypeInVar.h"
#include "cVectorProperty.h"
#include "cVectorPosition.h"
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
int testNumberSubobject( unsigned long &ulTestphase );
int testOutputValues( unsigned long &ulTestphase );
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
	
	cout<<endl<<"Running Test for cExtSubobject methods"<<endl;
	cout<<      "======================================"<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testEvalueObject( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testNumberSubobject( ulTestphase );
	iReturn += testOutputValues( ulTestphase );
	iReturn += testVariable( ulTestphase );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the constructor of the cExtSubobject class.
 *
 * methods tested:
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
 * 	- cExtSubobject( unsignedIntFib uiInNumberOfSubobject, cVectorExtSubobject vecInOutputValues, cFibElement * pInSuperiorElement = NULL );
 * 	- cExtSubobject( unsignedIntFib uiInNumberOfSubobject, unsignedIntFib uiNumberOfOutputVariables=0, cFibElement * pInSuperiorElement = NULL );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
 * 	- cExtSubobject( unsignedIntFib uiInNumberOfSubobject, vector< cFibVariable* > vecInOutputVariables=vector< cFibVariable* >(), cFibElement * pInSuperiorElement = NULL );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- unsignedIntFib getNumberOfElement()
 * 	- bool hasUnderAllObjects() const;
 * 	- unsignedIntFib getNumberSubobject() const;
 * 	- unsignedIntFib getNumberOfOutputVariables() const;
 * 	- vector< cFibVariable * > getOutputVariables();
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing constructing empty cExtSubobject"<<endl;

	cout<<"cExtSubobject extObjectSimple( 0 );"<<endl;
	cExtSubobject extObjectSimple( 0 );

#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cVectorExtSubobject vecCorrectOutVariables( 0 );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	vector< cFibVariable* > vecCorrectOutVariables;
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	//check the getType() methode from cExtSubobject
	if ( extObjectSimple.getType() == 's' ){
	
		cout<<"The type of the external subobject element is correctly 's' . "<<endl;
	}else{
		cerr<<"Error: The type of the external subobject element is "<<
			extObjectSimple.getType()<<" but should be 's' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cExtSubobject
	if ( extObjectSimple.isValidFibElement() ){
	
		cout<<"The external subobject element is correctly a a correct external subobject element. "<<endl;
	}else{
		cerr<<"Error: The external subobject element is not a correct external subobject element, but should be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cExtSubobject
	if ( ! extObjectSimple.isMovable() ){
	
		cout<<"The external subobject element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The external subobject element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cExtSubobject
	if ( extObjectSimple.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib element for the external subobject element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib element for the external subobject element is "<<
			extObjectSimple.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cExtSubobject
	if ( extObjectSimple.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib element for the external subobject element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element for the external subobject element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cExtSubobject
	if ( extObjectSimple.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib element for the external subobject element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element for the external subobject element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cExtSubobject
	if ( extObjectSimple.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib element for the external subobject element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element for the external subobject element is "<<
			extObjectSimple.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getNumberSubobject() methode from cExtSubobject
	if ( extObjectSimple.getNumberSubobject() == 0 ){
	
		cout<<"The identifier for the external subobject element is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The identifier for the external subobject element is not 0, but "<<
			extObjectSimple.getNumberSubobject()<<" ."<<endl;
		iReturn++;
	}
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//check the getOutputVariables() methode from cExtSubobject
	if ( *(extObjectSimple.getOutputVector()) == vecCorrectOutVariables ){
	
		cout<<"The external subobject element has the correct output values . "<<endl;
	}else{
		cerr<<"Error: The external subobject element has not the correct output values ."<<endl;
		iReturn++;
	}
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//check the getNumberOfOutputVariables() methode from cExtSubobject
	if ( extObjectSimple.getNumberOfOutputVariables() == 0 ){
	
		cout<<"The number of output values for the external subobject element is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of output values for the external subobject element is not 0, but "<<
			extObjectSimple.getNumberOfOutputVariables()<<" ."<<endl;
		iReturn++;
	}
	//check the getOutputVariables() methode from cExtSubobject
	if ( extObjectSimple.getOutputVariables() == vecCorrectOutVariables ){
	
		cout<<"The external subobject element has the correct output values . "<<endl;
	}else{
		cerr<<"Error: The external subobject element has not the correct output values ."<<endl;
		iReturn++;
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	//check the hasUnderAllObjects() methode from cExtSubobject
	if ( extObjectSimple.hasUnderAllObjects()){
	
		cout<<"The external subobject element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The external subobject element is missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing constructing cExtSubobject with output values given"<<endl;

	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	cout<<"root.setNumberOfInputVariables( 10 );"<<endl;
	root.setNumberOfInputVariables( 10 );
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cVectorExtSubobject vecVariables( 4 );"<<endl;
	cVectorExtSubobject vecVariables( 4 );
	
	cout<<"vecVariables.setVariable( 1, root.getInputVariable( 7 ) );"<<endl;
	vecVariables.setVariable( 1, root.getInputVariable( 7 ) );
	cout<<"vecVariables.setValue( 2, 2 );"<<endl;
	vecVariables.setValue( 2, 2 );
	cout<<"vecVariables.setVariable( 3, root.getInputVariable( 4 ) );"<<endl;
	vecVariables.setVariable( 3, root.getInputVariable( 4 ) );
	cout<<"vecVariables.setValue( 4, 4 );"<<endl;
	vecVariables.setValue( 4, 4 );
	
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"root.setNumberOfExternSubobjects( 20 );"<<endl;
	root.setNumberOfExternSubobjects( 20 );
	
	vector< cFibVariable * > vecVariables;
	cout<<"vecVariables.push_back( root.getInputVariable( 7 ) )"<<endl;
	vecVariables.push_back( root.getInputVariable( 7 ) );
	cout<<"vecVariables.push_back( root.getInputVariable( 3 ) )"<<endl;
	vecVariables.push_back( root.getInputVariable( 3 ) );
	cout<<"vecVariables.push_back( root.getInputVariable( 4 ) )"<<endl;
	vecVariables.push_back( root.getInputVariable( 4 ) );
	cout<<"vecVariables.push_back( root.getInputVariable( 3 ) )"<<endl;
	vecVariables.push_back( root.getInputVariable( 3 ) );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	vecCorrectOutVariables = vecVariables;
	
	cout<<"cExtSubobject extObjectInVar( 21, vecVariables );"<<endl;
	cExtSubobject extObjectInVar( 21, vecVariables );
	
	//check the getType() methode from cExtSubobject
	if ( extObjectInVar.getType() == 's' ){
	
		cout<<"The type of the external subobject element is correctly 's' . "<<endl;
	}else{
		cerr<<"Error: The type of the external subobject element is "<<
			extObjectInVar.getType()<<" but should be 's' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cExtSubobject
	if ( extObjectInVar.isValidFibElement() ){
	
		cout<<"The external subobject element is correctly a correct external subobject element. "<<endl;
	}else{
		cerr<<"Error: The external subobject element is not a correct external subobject element, but should be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cExtSubobject
	if ( ! extObjectInVar.isMovable() ){
	
		cout<<"The external subobject element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The external subobject element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cExtSubobject
	if ( extObjectInVar.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib element for the external subobject element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib element for the external subobject element is "<<
			extObjectInVar.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cExtSubobject
	if ( extObjectInVar.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib element for the external subobject element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element for the external subobject element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cExtSubobject
	if ( extObjectInVar.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib element for the external subobject element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element for the external subobject element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cExtSubobject
	if ( extObjectInVar.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib element for the external subobject element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element for the external subobject element is "<<
			extObjectInVar.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getNumberSubobject() methode from cExtSubobject
	if ( extObjectInVar.getNumberSubobject() == 21 ){
	
		cout<<"The identifier for the external subobject element is correctly 21 . "<<endl;
	}else{
		cerr<<"Error: The identifier for the external subobject element is not 21, but "<<
			extObjectInVar.getNumberSubobject()<<" ."<<endl;
		iReturn++;
	}
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//check the getOutputVariables() methode from cExtSubobject
	if ( *(extObjectInVar.getOutputVector()) == vecCorrectOutVariables ){
	
		cout<<"The external subobject element has the correct output values . "<<endl;
	}else{
		cerr<<"Error: The external subobject element has not the correct output values ."<<endl;
		iReturn++;
	}
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//check the getNumberOfOutputVariables() methode from cExtSubobject
	if ( extObjectInVar.getNumberOfOutputVariables() == 4 ){
	
		cout<<"The number of output values for the external subobject element is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of output values for the external subobject element is not 4, but "<<
			extObjectInVar.getNumberOfOutputVariables()<<" ."<<endl;
		iReturn++;
	}
	//check the getOutputVariables() methode from cExtSubobject
	if ( extObjectInVar.getOutputVariables() == vecCorrectOutVariables ){
	
		cout<<"The external subobject element has the correct output values . "<<endl;
	}else{
		cerr<<"Error: The external subobject element has not the correct output values ."<<endl;
		iReturn++;
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//check the hasUnderAllObjects() methode from cExtSubobject
	if ( extObjectInVar.hasUnderAllObjects()){
	
		cout<<"The external subobject element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The external subobject element is missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing constructing cExtSubobject with all parameters given"<<endl;

#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"vecVariables.resize( 3 );"<<endl;
	vecVariables.resize( 3 );
	cout<<"vecVariables.setValue(1, 11 )"<<endl;
	vecVariables.setValue(1, 11 );
	cout<<"vecVariables.setVariable( 2, root.getInputVariable( 3 ) )"<<endl;
	vecVariables.setVariable( 2, root.getInputVariable( 3 ) );
	cout<<"vecVariables.setVariable( 3, root.getInputVariable( 2 ) )"<<endl;
	vecVariables.setVariable( 3, root.getInputVariable( 2 ) );

#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	vecVariables.clear();
	cout<<"vecVariables.push_back( root.getInputVariable( 1 ) )"<<endl;
	vecVariables.push_back( root.getInputVariable( 1 ) );
	cout<<"vecVariables.push_back( root.getInputVariable( 3 ) )"<<endl;
	vecVariables.push_back( root.getInputVariable( 3 ) );
	cout<<"vecVariables.push_back( root.getInputVariable( 2 ) )"<<endl;
	vecVariables.push_back( root.getInputVariable( 2 ) );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	vecCorrectOutVariables = vecVariables;
	
	cout<<"cExtSubobject extObjectFull( 16, vecVariables, &root );"<<endl;
	cExtSubobject extObjectFull( 16, vecVariables, &root );
	
	//check the getType() methode from cExtSubobject
	if ( extObjectFull.getType() == 's' ){
	
		cout<<"The type of the external subobject element is correctly 's' . "<<endl;
	}else{
		cerr<<"Error: The type of the external subobject element is "<<
			extObjectFull.getType()<<" but should be 's' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cExtSubobject
	if ( extObjectFull.isValidFibElement() ){
	
		cout<<"The external subobject element is correctly a correct external subobject element. "<<endl;
	}else{
		cerr<<"Error: The external subobject element is not a correct external subobject element, but should be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cExtSubobject
	if ( ! extObjectFull.isMovable() ){
	
		cout<<"The external subobject element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The external subobject element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cExtSubobject
	if ( extObjectFull.getNumberOfElement() == 2 ){
	
		cout<<"The number of the Fib element for the external subobject element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib element for the external subobject element is "<<
			extObjectFull.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cExtSubobject
	if ( extObjectFull.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib element for the external subobject element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element for the external subobject element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cExtSubobject
	if ( extObjectFull.getFibElement( -1 ) == &root ){
	
		cout<<"The previous Fib element for the external subobject element is correctly root. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element for the external subobject element is not root."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cExtSubobject
	if ( extObjectFull.getSuperiorFibElement() == &root ){
	
		cout<<"The superior Fib element for the external subobject element is correctly root. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element for the external subobject element is "<<
			extObjectFull.getSuperiorFibElement() << " and not root."<<endl;
		iReturn++;
	}
	//check the getNumberSubobject() methode from cExtSubobject
	if ( extObjectFull.getNumberSubobject() == 16 ){
	
		cout<<"The identifier for the external subobject element is correctly 16 . "<<endl;
	}else{
		cerr<<"Error: The identifier for the external subobject element is not 16, but "<<
			extObjectFull.getNumberSubobject()<<" ."<<endl;
		iReturn++;
	}
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//check the getOutputVariables() methode from cExtSubobject
	if ( *(extObjectFull.getOutputVector()) == vecCorrectOutVariables ){
	
		cout<<"The external subobject element has the correct output values . "<<endl;
	}else{
		cerr<<"Error: The external subobject element has not the correct output values ."<<endl;
		iReturn++;
	}
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//check the getNumberOfOutputVariables() methode from cExtSubobject
	if ( extObjectFull.getNumberOfOutputVariables() == 3 ){
	
		cout<<"The number of output values for the external subobject element is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of output values for the external subobject element is not 3, but "<<
			extObjectFull.getNumberOfOutputVariables()<<" ."<<endl;
		iReturn++;
	}
	//check the getOutputVariables() methode from cExtSubobject
	if ( extObjectFull.getOutputVariables() == vecCorrectOutVariables ){
	
		cout<<"The external subobject element has the correct output values . "<<endl;
	}else{
		cerr<<"Error: The external subobject element has not the correct output values ."<<endl;
		iReturn++;
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//check the hasUnderAllObjects() methode from cExtSubobject
	if ( extObjectFull.hasUnderAllObjects()){
	
		cout<<"The external subobject element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The external subobject element is missing a underobject."<<endl;
		iReturn++;
	}


#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing constructing cExtSubobject with number of output values given"<<endl;

	vecCorrectOutVariables.resize( 0 );
	vecCorrectOutVariables.resize( 7 );
	
	cout<<"cExtSubobject extObjectINumber( 4, 7 );"<<endl;
	cExtSubobject extObjectINumber( 4, 7 );
	
	//check the getType() methode from cExtSubobject
	if ( extObjectINumber.getType() == 's' ){
	
		cout<<"The type of the external subobject element is correctly 's' . "<<endl;
	}else{
		cerr<<"Error: The type of the external subobject element is "<<
			extObjectINumber.getType()<<" but should be 's' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cExtSubobject
	if ( extObjectINumber.isValidFibElement() ){
	
		cout<<"The external subobject element is correctly a correct external subobject element. "<<endl;
	}else{
		cerr<<"Error: The external subobject element is not a correct external subobject element, but should be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cExtSubobject
	if ( ! extObjectINumber.isMovable() ){
	
		cout<<"The external subobject element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The external subobject element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cExtSubobject
	if ( extObjectINumber.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib element for the external subobject element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib element for the external subobject element is "<<
			extObjectINumber.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cExtSubobject
	if ( extObjectINumber.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib element for the external subobject element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element for the external subobject element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cExtSubobject
	if ( extObjectINumber.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib element for the external subobject element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib element for the external subobject element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cExtSubobject
	if ( extObjectINumber.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib element for the external subobject element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib element for the external subobject element is "<<
			extObjectINumber.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getNumberSubobject() methode from cExtSubobject
	if ( extObjectINumber.getNumberSubobject() == 4 ){
	
		cout<<"The identifier for the external subobject element is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The identifier for the external subobject element is not 4, but "<<
			extObjectINumber.getNumberSubobject()<<" ."<<endl;
		iReturn++;
	}
	//check the getOutputVariables() methode from cExtSubobject
	if ( *(extObjectINumber.getOutputVector()) == vecCorrectOutVariables ){
	
		cout<<"The external subobject element has the correct output values . "<<endl;
	}else{
		cerr<<"Error: The external subobject element has not the correct output values ."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cExtSubobject
	if ( extObjectINumber.hasUnderAllObjects()){
	
		cout<<"The external subobject element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The external subobject element is missing a underobject."<<endl;
		iReturn++;
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

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
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing evaluing cExtSubobject"<<endl;

	cout<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );
	cout<<"cVectorPosition vecPositionE3( 3 );"<<endl;
	cVectorPosition vecPositionE3( 3 );
	cout<<"cVectorPosition vecPositionE4( 4 );"<<endl;
	cVectorPosition vecPositionE4( 4 );

	cout<<"cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );
	cout<<"vecPropertyColorSW.setValue( 1, 1 );"<<endl;
	vecPropertyColorSW.setValue( 1, 1 );

	cout<<"cExtObject extObject1( 1 );"<<endl;
	cExtObject extObject1( 1 );

	cout<<"cProperty property1( vecPropertyColorSW, &extObject1 );"<<endl;
	cProperty property1( vecPropertyColorSW, &extObject1 );

	cout<<"cRoot root( &property1 );"<<endl;
	cRoot root( &property1 );
	
	cout<<"cPoint point1( &vecPositionE2 );"<<endl;
	cPoint point1( &vecPositionE2 );
	cout<<"extObject1.addSubobject( &point1, 0, 1 );"<<endl;
	extObject1.addSubobject( &point1, 0, 1 );
	cout<<"point1.getPosition()->setValue( 1, 1 );"<<endl;
	point1.getPosition()->setValue( 1, 1 );
	cout<<"point1.getPosition()->setVariable( 2, extObject1.getOutputVariable( 1, 1) );"<<endl;
	point1.getPosition()->setVariable( 2, extObject1.getOutputVariable( 1, 1) );

	cout<<"cPoint point2( &vecPositionE3 );"<<endl;
	cPoint point2( &vecPositionE3 );
	cout<<"extObject1.addSubobject( &point2, 0, 2 );"<<endl;
	extObject1.addSubobject( &point2, 0, 2 );
	cout<<"point2.getPosition()->setValue( 1, 2 );"<<endl;
	point2.getPosition()->setValue( 1, 2 );
	cout<<"point2.getPosition()->setVariable( 2, extObject1.getOutputVariable( 2, 1 ) );"<<endl;
	point2.getPosition()->setVariable( 2, extObject1.getOutputVariable( 2, 1 ) );
	cout<<"point2.getPosition()->setVariable( 3, extObject1.getOutputVariable( 2, 2 ) );"<<endl;
	point2.getPosition()->setVariable( 3, extObject1.getOutputVariable( 2, 2 ) );

	cout<<"cPoint point3( &vecPositionE4 );"<<endl;
	cPoint point3( &vecPositionE4 );
	cout<<"extObject1.addSubobject( &point3, 0, 3 );"<<endl;
	extObject1.addSubobject( &point3, 0, 3 );
	cout<<"point3.getPosition()->setValue( 1, 3 );"<<endl;
	point3.getPosition()->setValue( 1, 3 );
	cout<<"point3.getPosition()->setVariable( 2, extObject1.getOutputVariable( 3, 1 ) );"<<endl;
	point3.getPosition()->setVariable( 2, extObject1.getOutputVariable( 3, 1 ) );
	cout<<"point3.getPosition()->setVariable( 3, extObject1.getOutputVariable( 3, 2 ) );"<<endl;
	point3.getPosition()->setVariable( 3, extObject1.getOutputVariable( 3, 2 ) );
	cout<<"point3.getPosition()->setVariable( 4, extObject1.getOutputVariable( 3, 3 ) );"<<endl;
	point3.getPosition()->setVariable( 4, extObject1.getOutputVariable( 3, 3 ) );


	cout<<"cExtSubobject extSubobject1( 2 );"<<endl;
	cExtSubobject extSubobject1( 2 );
	
	cout<<"vecPropertyColorSW.setValue( 1, 2 );"<<endl;
	vecPropertyColorSW.setValue( 1, 2 );
	cout<<"cProperty property2( vecPropertyColorSW, &extSubobject1 );"<<endl;
	cProperty property2( vecPropertyColorSW, &extSubobject1 );
	
	cout<<"cRoot subroot( &property2 );"<<endl;
	cRoot subroot( &property2 );
	
	cout<<"root.addSubRootObject( 1, &subroot );"<<endl;
	root.addSubRootObject( 1, &subroot );
	
	
	unsigned int uiPointsToEvalue = 1;
	
	unsigned int uiTimeNeeded = 2 + 5 + 3 + 2 + 2 + 4;//= property1 + extObject1 + subroot + property2 + extSubobject1 + point*

	//check the getTimeNeed() methode from cExtSubobject
	cout<<"property1.getTimeNeed()"<<endl;
	if ( property1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cExtSubobject
	cout<<"property1.getTimeNeed( 7 )"<<endl;
	if ( property1.getTimeNeed( 7 ) == 7 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 7 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property1.getTimeNeed( 7 ) <<", but should be "<< 7 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"list<cVectorProperty> liVecProperties;"<<endl;
	list<cVectorProperty> liVecProperties;
	
	//generate to evalue data
	list< pair< const cVectorPosition*, list<cVectorProperty> > > liPointsToEvalue;
	cVectorPosition vecPositionE3V2( 3 );
	vecPositionE3V2.setValue( 1, 2 );
	cVectorProperty vecPropertyColorSWV1( cTypeProperty::COLOR_SW );
	vecPropertyColorSWV1.setValue( 1, 1 );
	cVectorProperty vecPropertyColorSWV2( cTypeProperty::COLOR_SW );
	vecPropertyColorSWV2.setValue( 1, 2 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE3V2, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV2 );
	
	cEvaluePositionList evaluePositionList;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"property1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bool bObjectEvalued = property1.evalueObject( evaluePositionList, 0,  liVecProperties );

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
	cout<<"property1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = property1.evalueObjectSimple( evaluePositionList );

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
	liFibElementsToEvalue.push_back( make_pair( &point2, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV2 );
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<"property1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = property1.evalueObjectSimple( evalueFibElementList );

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
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing evaluing cExtSubobject with a global property list given"<<endl;
	
	cout<<"cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );
	
	list< pair< const cVectorPosition*, list<cVectorProperty> > >::iterator
		itrPositionProperties = liPointsToEvalue.begin();
	itrPositionProperties->second.push_front( vecPropertyLayer );
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"property1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property1.evalueObject( evaluePositionList, 0,  liVecProperties );

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
	itrElementProperties->second.push_front( vecPropertyLayer );

	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing evaluing cExtSubobject for non existing object point 1"<<endl;
	
	uiPointsToEvalue = 0;
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"property1.evalueObject( evaluePositionList, 4,  liVecProperties );"<<endl;
	bObjectEvalued = property1.evalueObject( evaluePositionList, 4,  liVecProperties );

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
	cout<<"property1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );

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
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing evaluing cExtSubobject when returnvalue is false"<<endl;

	uiPointsToEvalue = 1;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	cout<<"property1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property1.evalueObject( evaluePositionList, 0,  liVecProperties );

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
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing evaluing cExtSubobject with differnt elements to evalue"<<endl;

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
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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


	liVecProperties.clear();
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	cout<<"liCFibElementTyps.push_back( 's' );"<<endl;
	liCFibElementTyps.push_back( 's' );
	uiPointsToEvalue = 1;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &extSubobject1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV2 );
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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

	liVecProperties.clear();
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	cout<<"liCFibElementTyps.push_back( 'l' );"<<endl;
	liCFibElementTyps.push_back( 'l' );
	cout<<"liCFibElementTyps.push_back( 's' );"<<endl;
	liCFibElementTyps.push_back( 's' );
	cout<<"liCFibElementTyps.push_back( 'm' );"<<endl;
	liCFibElementTyps.push_back( 'm' );
	uiPointsToEvalue = 1;
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing evaluing cExtSubobject with output vairables given"<<endl;
	
	cout<<"subroot.setNumberOfInputVariables( 10 )"<<endl;
	subroot.setNumberOfInputVariables( 10 );
	cout<<"subroot.setStandardValueOfInputVariable( 1, 11 );"<<endl;
	subroot.setStandardValueOfInputVariable( 1, 11 );
	cout<<"subroot.setStandardValueOfInputVariable( 2, 12 );"<<endl;
	subroot.setStandardValueOfInputVariable( 2, 12 );
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"pVectorExtSubobject = extSubobject1.getOutputVector();"<<endl;
	cVectorExtSubobject * pVectorExtSubobject =
		extSubobject1.getOutputVector();
	
	cout<<"pVectorExtSubobject->resize( 2 );"<<endl;
	pVectorExtSubobject->resize( 2 );
	cout<<"pVectorExtSubobject->setVariable( 1, subroot.getInputVariable( 1 ) );"<<endl;
	pVectorExtSubobject->setVariable( 1, subroot.getInputVariable( 1 ) );
	cout<<"pVectorExtSubobject->setValue( 2, 12 );"<<endl;
	pVectorExtSubobject->setValue( 2, 12 );
	
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"extSubobject1.setOutputVariable( 1, subroot.getInputVariable( 1 ) );"<<endl;
	extSubobject1.setOutputVariable( 1, subroot.getInputVariable( 1 ) );
	cout<<"extSubobject1.setOutputVariable( 2, subroot.getInputVariable( 2 ) );"<<endl;
	extSubobject1.setOutputVariable( 2, subroot.getInputVariable( 2 ) );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	//check the getTimeNeed() methode from cExtSubobject
	cout<<"property1.getTimeNeed()"<<endl;
	if ( property1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cExtSubobject
	cout<<"property1.getTimeNeed( 7 )"<<endl;
	if ( property1.getTimeNeed( 7 ) == 7 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 7 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property1.getTimeNeed( 7 ) <<", but should be "<< 7 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	
	//generate to evalue data
	liPointsToEvalue.clear();
	vecPositionE3V2.setValue( 1, 2 );
	vecPositionE3V2.setValue( 2, 11 );
	vecPositionE3V2.setValue( 3, 12 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE3V2, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV2 );
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"property1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property1.evalueObject( evaluePositionList, 0,  liVecProperties );

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
	cout<<"property1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = property1.evalueObjectSimple( evaluePositionList );

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
	liFibElementsToEvalue.push_back( make_pair( &point2, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV2 );
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<"property1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = property1.evalueObjectSimple( evalueFibElementList );

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
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing evaluing cExtSubobject external subobject for subobject number 1"<<endl;
	
	cout<<"extSubobject1.setNumberSubobject( 1 );"<<endl;
	extSubobject1.setNumberSubobject( 1 );

	uiTimeNeeded = 2 + 5 + 3 + 2 + 2 + 3;//= property1 + extObject1 + subroot + property2 + extSubobject1 + point1
	
//check the getTimeNeed() methode from cExtSubobject
	cout<<"property1.getTimeNeed()"<<endl;
	if ( property1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cExtSubobject
	cout<<"property1.getTimeNeed( 7 )"<<endl;
	if ( property1.getTimeNeed( 7 ) == 7 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 7 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property1.getTimeNeed( 7 ) <<", but should be "<< 7 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	
	//generate to evalue data
	liPointsToEvalue.clear();
	cVectorPosition vecPositionE1V1( 2 );
	vecPositionE1V1.setValue( 1, 1 );
	vecPositionE1V1.setValue( 2, 11 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE1V1, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV2 );
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"property1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property1.evalueObject( evaluePositionList, 0,  liVecProperties );

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
	cout<<"property1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = property1.evalueObjectSimple( evaluePositionList );

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
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV2 );
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<"property1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = property1.evalueObjectSimple( evalueFibElementList );

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
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing evaluing cExtSubobject external subobject for subobject number 3"<<endl;
	
	cout<<"extSubobject1.setNumberSubobject( 3 );"<<endl;
	extSubobject1.setNumberSubobject( 3 );

	uiTimeNeeded = 2 + 5 + 3 + 2 + 2 + 5;//= property1 + extObject1 + subroot + property2 + extSubobject1 + point3
	
//check the getTimeNeed() methode from cExtSubobject
	cout<<"property1.getTimeNeed()"<<endl;
	if ( property1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cExtSubobject
	cout<<"property1.getTimeNeed( 7 )"<<endl;
	if ( property1.getTimeNeed( 7 ) == 7 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 7 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property1.getTimeNeed( 7 ) <<", but should be "<< 7 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	
	//generate to evalue data
	liPointsToEvalue.clear();
	cVectorPosition vecPositionE4V3( 4 );
	vecPositionE4V3.setValue( 1, 3 );
	vecPositionE4V3.setValue( 2, 11 );
	vecPositionE4V3.setValue( 3, 12 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE4V3, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV2 );
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"property1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property1.evalueObject( evaluePositionList, 0,  liVecProperties );

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
	cout<<"property1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = property1.evalueObjectSimple( evaluePositionList );

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
	liFibElementsToEvalue.push_back( make_pair( &point3, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV2 );
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<"property1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = property1.evalueObjectSimple( evalueFibElementList );

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
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing evaluing cExtSubobject external subobject for subobject number 0 that did not exists"<<endl;
	
	cout<<"extSubobject1.setNumberSubobject( 0 );"<<endl;
	extSubobject1.setNumberSubobject( 0 );

	uiTimeNeeded = 2 + 5 + 3 + 2 + 2;//= property1 + extObject1 + subroot + property2 + extSubobject1
	
//check the getTimeNeed() methode from cExtSubobject
	cout<<"property1.getTimeNeed()"<<endl;
	if ( property1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cExtSubobject
	cout<<"property1.getTimeNeed( 5 )"<<endl;
	if ( property1.getTimeNeed( 5 ) == 5 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 5 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property1.getTimeNeed( 5 ) <<", but should be "<< 5 <<" . "<<endl;
		iReturn++;
	}
	
	uiPointsToEvalue = 0;
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"property1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property1.evalueObject( evaluePositionList, 0,  liVecProperties );

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

	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	liFibElementsToEvalue.clear();
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing evaluing cExtSubobject external subobject for subobject number 4 that did not exists"<<endl;
	
	cout<<"extSubobject1.setNumberSubobject( 4 );"<<endl;
	extSubobject1.setNumberSubobject( 4 );

	uiTimeNeeded = 2 + 5 + 3 + 2 + 2;//= property1 + extObject1 + subroot + property2 + extSubobject1
	
//check the getTimeNeed() methode from cExtSubobject
	cout<<"property1.getTimeNeed()"<<endl;
	if ( property1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cExtSubobject
	cout<<"property1.getTimeNeed( 11 )"<<endl;
	if ( property1.getTimeNeed( 11 ) == 11 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 11 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property1.getTimeNeed( 11 ) <<", but should be "<< 11 <<" . "<<endl;
		iReturn++;
	}
	
	uiPointsToEvalue = 0;
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"property1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property1.evalueObject( evaluePositionList, 0,  liVecProperties );

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

	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	liFibElementsToEvalue.clear();
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
			(bEqualElement?"":"not") <<" equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" Fib element is "<<
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
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing equal methods for external subobject elements"<<endl;

	cout<<endl<<"Creating ifobjects objects to compare: "<<endl<<endl;
	
	//if with a empty
	cout<<"cExtSubobject extSubobjSub0_1( 0 );"<<endl;
	cExtSubobject extSubobjSub0_1( 0 );

	cout<<"cExtSubobject extSubobjSub0_2( 0 );"<<endl;
	cExtSubobject extSubobjSub0_2( 0) ;

	//if with an identifier not 0
	cout<<"cExtSubobject extSubobjSub1_1( 1 );"<<endl;
	cExtSubobject extSubobjSub1_1( 1 );

	cout<<"cExtSubobject extSubobjSub32568_1( 32568 );"<<endl;
	cExtSubobject extSubobjSub32568_1( 32568 );
	

	//with one ioutput variable
	cout<<"cRoot rootVariables;"<<flush<<endl;
	cRoot rootVariables;
	cout<<"rootVariables.setNumberOfInputVariables( 10 );"<<flush<<endl;
	rootVariables.setNumberOfInputVariables( 10 );
	
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cVectorExtSubobject vecInOutputVariables1( 1 );"<<endl;
	cVectorExtSubobject vecInOutputVariables1( 1 );
	
	cout<<"vecInOutputVariables1.setVariable( 1, rootVariables.getInputVariable( 1 ) );"<<endl;
	vecInOutputVariables1.setVariable( 1, rootVariables.getInputVariable( 1 ) );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"vector< cFibVariable* > vecInOutputVariables1;"<<flush<<endl;
	vector< cFibVariable* > vecInOutputVariables1;
	cout<<"vecInOutputVariables1.push_back( rootVariables.getInputVariable( 1 ) );"<<flush<<endl;
	vecInOutputVariables1.push_back( rootVariables.getInputVariable( 1 ) );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	cout<<"cExtSubobject extSubobjSub0InVar1( 0, vecInOutputVariables1 );"<<endl;
	cExtSubobject extSubobjSub0InVar1( 0, vecInOutputVariables1 );
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cVectorExtSubobject vecInOutputVariables2( 1 );"<<endl;
	cVectorExtSubobject vecInOutputVariables2( 1 );
	
	cout<<"vecInOutputVariables2.setVariable( 1, rootVariables.getInputVariable( 7 ) );"<<endl;
	vecInOutputVariables2.setVariable( 1, rootVariables.getInputVariable( 7 ) );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"vector< cFibVariable* > vecInOutputVariables2;"<<flush<<endl;
	vector< cFibVariable* > vecInOutputVariables2;
	cout<<"vecInOutputVariables2.push_back( rootVariables.getInputVariable( 7 ) );"<<flush<<endl;
	vecInOutputVariables2.push_back( rootVariables.getInputVariable( 7 ) );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cExtSubobject extSubobjSub0InVar7( 0, vecInOutputVariables2 );"<<endl;
	cExtSubobject extSubobjSub0InVar7( 0, vecInOutputVariables2 );
	
	//with two output values
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"vecInOutputVariables1.resize( 2 );"<<endl;
	vecInOutputVariables1.resize( 2 );
	
	cout<<"vecInOutputVariables1.setValue( 2, 77 );"<<endl;
	vecInOutputVariables1.setValue( 2, 77 );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"vecInOutputVariables1.push_back( rootVariables.getInputVariable( 7 ) );"<<flush<<endl;
	vecInOutputVariables1.push_back( rootVariables.getInputVariable( 7 ) );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cExtSubobject extSubobjSub0InVar1u7( 0, vecInOutputVariables1 );"<<endl;
	cExtSubobject extSubobjSub0InVar1u7( 0, vecInOutputVariables1 );
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"vecInOutputVariables2.resize( 2 );"<<endl;
	vecInOutputVariables2.resize( 2 );
	
	cout<<"vecInOutputVariables2.setValue( 2, 77 );"<<endl;
	vecInOutputVariables2.setValue( 2, 77 );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"vecInOutputVariables2.push_back( rootVariables.getInputVariable( 7 ) );"<<flush<<endl;
	vecInOutputVariables2.push_back( rootVariables.getInputVariable( 7 ) );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cExtSubobject extSubobjSub0InVar7u7( 0, vecInOutputVariables2 );"<<endl;
	cExtSubobject extSubobjSub0InVar7u7( 0, vecInOutputVariables2 );
	
	//with tree output values
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"vecInOutputVariables1.resize( 3 );"<<endl;
	vecInOutputVariables1.resize( 3 );
	
	cout<<"vecInOutputVariables1.setVariable( 3, rootVariables.getInputVariable( 5 ) );"<<endl;
	vecInOutputVariables1.setVariable( 3, rootVariables.getInputVariable( 5 )  );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"vecInOutputVariables1.push_back( rootVariables.getInputVariable( 5 ) );"<<flush<<endl;
	vecInOutputVariables1.push_back( rootVariables.getInputVariable( 5 ) );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cExtSubobject extSubobjSub0InVar1u7u5( 0, vecInOutputVariables1 );"<<endl;
	cExtSubobject extSubobjSub0InVar1u7u5( 0, vecInOutputVariables1 );
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"vecInOutputVariables1.resize( 4 );"<<endl;
	vecInOutputVariables1.resize( 4 );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"vecInOutputVariables1.back() = rootVariables.getInputVariable( 4 );"<<flush<<endl;
	vecInOutputVariables1.back() = rootVariables.getInputVariable( 4 );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cExtSubobject extSubobjSub0InVar1u7u4( 0, vecInOutputVariables1 );"<<endl;
	cExtSubobject extSubobjSub0InVar1u7u4( 0, vecInOutputVariables1 );
	
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//with input vector with one elemnt which is 0
	cout<<"cExtSubobject extSubobjSub0InVarNULL( 0, 1 );"<<endl;
	cExtSubobject extSubobjSub0InVarNULL( 0, 1 );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//with one input variable wich is NULL
	cout<<"vector< cFibVariable* > vecInOutputVariables3;"<<flush<<endl;
	vector< cFibVariable* > vecInOutputVariables3;
	cout<<"vecInOutputVariables3.push_back( NULL );"<<flush<<endl;
	vecInOutputVariables3.push_back( NULL );
	cout<<"cExtSubobject extSubobjSub0InVarNULL( 0, vecInOutputVariables3 );"<<endl;
	cExtSubobject extSubobjSub0InVarNULL( 0, vecInOutputVariables3 );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	//if with superior element
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cExtSubobject extSubobjSub0Sup( 0, 0, &rootSimple1 );"<<endl;
	cExtSubobject extSubobjSub0Sup( 0, 0, &rootSimple1 );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cExtSubobject extSubobjSub0Sup( 0, vector<cFibVariable*>(), &rootSimple1 );"<<endl;
	cExtSubobject extSubobjSub0Sup( 0, vector<cFibVariable*>(), &rootSimple1 );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	
	//other Fib objects
	cout<<"cPoint point;"<<endl;
	cPoint point;

	cout<<"cPoint point1List;"<<endl;
	cPoint point1List;
	cout<<"cPoint point2List;"<<endl;
	cPoint point2List;
	cout<<"cList list( &point1List, &point2List );"<<endl;
	cList list( &point1List, &point2List );



	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with extSubobjSub0_1
	cFibElement *pActualObject = &extSubobjSub0_1;
	string szActualObjectName = "extSubobjSub0_1";
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_1, "extSubobjSub0_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_2, "extSubobjSub0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub1_1, "extSubobjSub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub32568_1, "extSubobjSub32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1, "extSubobjSub0InVar1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7, "extSubobjSub0InVar7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7, "extSubobjSub0InVar1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7u7, "extSubobjSub0InVar7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u5, "extSubobjSub0InVar1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u4, "extSubobjSub0InVar1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVarNULL, "extSubobjSub0InVarNULL" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0Sup, "extSubobjSub0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extSubobjSub0_2
	pActualObject = &extSubobjSub0_2;
	szActualObjectName = "extSubobjSub0_2";
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_1, "extSubobjSub0_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_2, "extSubobjSub0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub1_1, "extSubobjSub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub32568_1, "extSubobjSub32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1, "extSubobjSub0InVar1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7, "extSubobjSub0InVar7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7, "extSubobjSub0InVar1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7u7, "extSubobjSub0InVar7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u5, "extSubobjSub0InVar1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u4, "extSubobjSub0InVar1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVarNULL, "extSubobjSub0InVarNULL" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0Sup, "extSubobjSub0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extSubobjSub1_1
	pActualObject = &extSubobjSub1_1;
	szActualObjectName = "extSubobjSub1_1";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_1, "extSubobjSub0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_2, "extSubobjSub0_2" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub1_1, "extSubobjSub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub32568_1, "extSubobjSub32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1, "extSubobjSub0InVar1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7, "extSubobjSub0InVar7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7, "extSubobjSub0InVar1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7u7, "extSubobjSub0InVar7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u5, "extSubobjSub0InVar1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u4, "extSubobjSub0InVar1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVarNULL, "extSubobjSub0InVarNULL" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0Sup, "extSubobjSub0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extSubobjSub32568_1
	pActualObject = &extSubobjSub32568_1;
	szActualObjectName = "extSubobjSub32568_1";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_1, "extSubobjSub0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_2, "extSubobjSub0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub1_1, "extSubobjSub1_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub32568_1, "extSubobjSub32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1, "extSubobjSub0InVar1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7, "extSubobjSub0InVar7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7, "extSubobjSub0InVar1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7u7, "extSubobjSub0InVar7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u5, "extSubobjSub0InVar1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u4, "extSubobjSub0InVar1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVarNULL, "extSubobjSub0InVarNULL" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0Sup, "extSubobjSub0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extSubobjSub0InVar1
	pActualObject = &extSubobjSub0InVar1;
	szActualObjectName = "extSubobjSub0InVar1";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_1, "extSubobjSub0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_2, "extSubobjSub0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub1_1, "extSubobjSub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub32568_1, "extSubobjSub32568_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1, "extSubobjSub0InVar1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7, "extSubobjSub0InVar7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7, "extSubobjSub0InVar1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7u7, "extSubobjSub0InVar7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u5, "extSubobjSub0InVar1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u4, "extSubobjSub0InVar1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVarNULL, "extSubobjSub0InVarNULL" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0Sup, "extSubobjSub0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extSubobjSub0InVar7
	pActualObject = &extSubobjSub0InVar7;
	szActualObjectName = "extSubobjSub0InVar7";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_1, "extSubobjSub0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_2, "extSubobjSub0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub1_1, "extSubobjSub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub32568_1, "extSubobjSub32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1, "extSubobjSub0InVar1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7, "extSubobjSub0InVar7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7, "extSubobjSub0InVar1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7u7, "extSubobjSub0InVar7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u5, "extSubobjSub0InVar1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u4, "extSubobjSub0InVar1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVarNULL, "extSubobjSub0InVarNULL" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0Sup, "extSubobjSub0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extSubobjSub0InVar1u7
	pActualObject = &extSubobjSub0InVar1u7;
	szActualObjectName = "extSubobjSub0InVar1u7";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_1, "extSubobjSub0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_2, "extSubobjSub0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub1_1, "extSubobjSub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub32568_1, "extSubobjSub32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1, "extSubobjSub0InVar1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7, "extSubobjSub0InVar7" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7, "extSubobjSub0InVar1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7u7, "extSubobjSub0InVar7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u5, "extSubobjSub0InVar1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u4, "extSubobjSub0InVar1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVarNULL, "extSubobjSub0InVarNULL" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0Sup, "extSubobjSub0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extSubobjSub0InVar7u7
	pActualObject = &extSubobjSub0InVar7u7;
	szActualObjectName = "extSubobjSub0InVar7u7";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_1, "extSubobjSub0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_2, "extSubobjSub0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub1_1, "extSubobjSub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub32568_1, "extSubobjSub32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1, "extSubobjSub0InVar1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7, "extSubobjSub0InVar7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7, "extSubobjSub0InVar1u7" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7u7, "extSubobjSub0InVar7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u5, "extSubobjSub0InVar1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u4, "extSubobjSub0InVar1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVarNULL, "extSubobjSub0InVarNULL" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0Sup, "extSubobjSub0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extSubobjSub0InVar1u7u5
	pActualObject = &extSubobjSub0InVar1u7u5;
	szActualObjectName = "extSubobjSub0InVar1u7u5";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_1, "extSubobjSub0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_2, "extSubobjSub0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub1_1, "extSubobjSub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub32568_1, "extSubobjSub32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1, "extSubobjSub0InVar1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7, "extSubobjSub0InVar7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7, "extSubobjSub0InVar1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7u7, "extSubobjSub0InVar7u7" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u5, "extSubobjSub0InVar1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u4, "extSubobjSub0InVar1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVarNULL, "extSubobjSub0InVarNULL" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0Sup, "extSubobjSub0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extSubobjSub0InVar1u7u4
	pActualObject = &extSubobjSub0InVar1u7u4;
	szActualObjectName = "extSubobjSub0InVar1u7u4";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_1, "extSubobjSub0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_2, "extSubobjSub0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub1_1, "extSubobjSub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub32568_1, "extSubobjSub32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1, "extSubobjSub0InVar1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7, "extSubobjSub0InVar7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7, "extSubobjSub0InVar1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7u7, "extSubobjSub0InVar7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u5, "extSubobjSub0InVar1u7u5" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u4, "extSubobjSub0InVar1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVarNULL, "extSubobjSub0InVarNULL" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0Sup, "extSubobjSub0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extSubobjSub0InVarNULL
	pActualObject = &extSubobjSub0InVarNULL;
	szActualObjectName = "extSubobjSub0InVarNULL";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_1, "extSubobjSub0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_2, "extSubobjSub0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub1_1, "extSubobjSub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub32568_1, "extSubobjSub32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1, "extSubobjSub0InVar1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7, "extSubobjSub0InVar7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7, "extSubobjSub0InVar1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7u7, "extSubobjSub0InVar7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u5, "extSubobjSub0InVar1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u4, "extSubobjSub0InVar1u7u4" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVarNULL, "extSubobjSub0InVarNULL" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0Sup, "extSubobjSub0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extSubobjSub0Sup
	pActualObject = &extSubobjSub0Sup;
	szActualObjectName = "extSubobjSub0Sup";
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_1, "extSubobjSub0_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_2, "extSubobjSub0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub1_1, "extSubobjSub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub32568_1, "extSubobjSub32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1, "extSubobjSub0InVar1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7, "extSubobjSub0InVar7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7, "extSubobjSub0InVar1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7u7, "extSubobjSub0InVar7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u5, "extSubobjSub0InVar1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u4, "extSubobjSub0InVar1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVarNULL, "extSubobjSub0InVarNULL" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0Sup, "extSubobjSub0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with point
	pActualObject = &point;
	szActualObjectName = "point";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_1, "extSubobjSub0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_2, "extSubobjSub0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub1_1, "extSubobjSub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub32568_1, "extSubobjSub32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1, "extSubobjSub0InVar1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7, "extSubobjSub0InVar7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7, "extSubobjSub0InVar1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7u7, "extSubobjSub0InVar7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u5, "extSubobjSub0InVar1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u4, "extSubobjSub0InVar1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVarNULL, "extSubobjSub0InVarNULL" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0Sup, "extSubobjSub0Sup" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with list
	pActualObject = &list;
	szActualObjectName = "list";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_1, "extSubobjSub0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0_2, "extSubobjSub0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub1_1, "extSubobjSub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub32568_1, "extSubobjSub32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1, "extSubobjSub0InVar1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7, "extSubobjSub0InVar7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7, "extSubobjSub0InVar1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar7u7, "extSubobjSub0InVar7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u5, "extSubobjSub0InVar1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVar1u7u4, "extSubobjSub0InVar1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extSubobjSub0InVarNULL, "extSubobjSub0InVarNULL" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, list, "list" );


	return iReturn;
}



/**
 * This method tests the equal() method of two given Fib objects, which are
 * equal.
 * It also compares the superior, next and previous Fib element pointers.
 *
 * @param fibObject1 the first Fib object to compare
 * @param szNameObject1 the name of the first Fib object to compare
 * @param fibObject2 the secound Fib object to compare to
 * @param szNameObject2 the name of the secound Fib object to compare
 * @param isClone if true the Fib object is a clone (the pointers are not equal)
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualObjectsStructur(
		const cFibElement &fibObject1, const string &szNameObject1,
		const cFibElement &fibObject2, const string &szNameObject2, bool isClone=false ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	iReturn += testCompareTwoEqualObjects( fibObject1, szNameObject1, fibObject2, szNameObject2 );
	
	if ( ! isClone ){
		//check the getNextFibElement() methode from cExtSubobject
		if ( const_cast<cFibElement*>(&fibObject1)->getNextFibElement() ==
				const_cast<cFibElement*>(&fibObject2)->getNextFibElement() ){
		
			cout<<"The next/ main Fib elementpointer for the external subobject element are correctly equal. "<<endl;
		}else{
			cerr<<"Error: The next/ main Fib elementpointer for the external subobject element are not equal."<<endl;
			iReturn++;
		}
	
		//check the getFibElement() methode from cExtSubobject
		if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) ==
				const_cast<cFibElement*>(&fibObject2)->getFibElement( -1 ) ){
		
			cout<<"The previous Fib elementpointer for the external subobject element are correctly equal. "<<endl;
		}else{
			cerr<<"Error: The previous Fib elementpointer for the external subobject element are not equal."<<endl;
			iReturn++;
		}
		//check the getSuperiorFibElement() methode from cExtSubobject
		if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() ==
				const_cast<cFibElement*>(&fibObject2)->getSuperiorFibElement() ){
		
			cout<<"The superior Fib elementpointer for the external subobject element are correctly equal. "<<endl;
		}else{
			cerr<<"Error: The superior Fib elementpointer for the external subobject element are not equal."<<endl;
			iReturn++;
		}
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
	
		cout<<"The next/ main Fib elementpointer for the point -elements is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib elementpointer for the point -elements is not NULL."<<endl;
		iReturn++;
	}
	//check the getFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib elementpointer for the point -elements is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib elementpointer for the point -elements is not NULL."<<endl;
		iReturn++;
	}
	
	//check the getSuperiorFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib elementpointer for the point -elements is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib elementpointer for the point -elements is not NULL."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the copy methods and copyconstructor of the cExtSubobject class.
 *
 * methods tested:
 * 	- cExtSubobject( const cExtSubobject &ifElement );
 * 	- cFibElement *clone() const;
 * 	- cExtSubobject *copy( const unsignedIntFib iObjectExtSubobject=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementExtSubobject=0 ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing copying a simple cExtSubobject"<<endl;

	cout<<"cExtSubobject extSubobjectSimple( 0 );"<<endl;
	cExtSubobject extSubobjectSimple( 0 );

	cout<<"cExtSubobject extSubobjectSimpleCopyConstruct( extSubobjectSimple );"<<endl;
	cExtSubobject extSubobjectSimpleCopyConstruct( extSubobjectSimple );

	iReturn += testCompareTwoEqualObjectsStructur( extSubobjectSimpleCopyConstruct, "extSubobjectSimpleCopyConstruct", extSubobjectSimple, "extSubobjectSimple" );

	cout<<"cFibElement * pExtSubobjectSimpleClone = extSubobjectSimple.clone();"<<endl;
	cFibElement * pExtSubobjectSimpleClone = extSubobjectSimple.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pExtSubobjectSimpleClone, "pExtSubobjectSimpleClone", extSubobjectSimple, "extSubobjectSimple" );
	delete pExtSubobjectSimpleClone;

	cout<<"cFibElement * pExtSubobjectSimpleCopy = extSubobjectSimple.copy();"<<endl;
	cFibElement * pExtSubobjectSimpleCopy = extSubobjectSimple.copy();

	iReturn += testCompareTwoEqualObjectsStructur( *pExtSubobjectSimpleCopy, "pExtSubobjectSimpleCopy", extSubobjectSimple, "extSubobjectSimple" );
	delete pExtSubobjectSimpleCopy;

	cout<<"cFibElement * pExtSubobjectSimpleCopyElement = extSubobjectSimple.copyElement();"<<endl;
	cFibElement * pExtSubobjectSimpleCopyElement = extSubobjectSimple.copyElement();

	iReturn += testCompareTwoEqualObjectsStructur( *pExtSubobjectSimpleCopyElement, "pExtSubobjectSimpleCopyElement", extSubobjectSimple, "extSubobjectSimple" );
	delete pExtSubobjectSimpleCopyElement;
	

	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing copying for a other object or element point"<<endl;

	cout<<"cFibElement * pExtSubobjectSimpleNoCopy = extSubobjectSimple.copy( 1 );"<<endl;
	cFibElement * pExtSubobjectSimpleNoCopy = extSubobjectSimple.copy( 1 );

	if ( pExtSubobjectSimpleNoCopy == NULL ){
	
		cout<<"The cExtSubobject was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cExtSubobject was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pExtSubobjectSimpleNoCopy;
	}

	cout<<"cFibElement * pExtSubobjectSimpleNoCopyElement = extSubobjectSimple.copyElement( 's', 2 );"<<endl;
	cFibElement * pExtSubobjectSimpleNoCopyElement = extSubobjectSimple.copyElement( 's', 2 );

	if ( pExtSubobjectSimpleNoCopyElement == NULL ){
	
		cout<<"The cExtSubobject -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cExtSubobject -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pExtSubobjectSimpleNoCopyElement;
	}

	cout<<"pExtSubobjectSimpleNoCopyElement = extSubobjectSimple.copyElement( 'u', 2 );"<<endl;
	pExtSubobjectSimpleNoCopyElement = extSubobjectSimple.copyElement( 'u', 2 );

	if ( pExtSubobjectSimpleNoCopyElement == NULL ){
	
		cout<<"The cExtSubobject -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cExtSubobject -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pExtSubobjectSimpleNoCopyElement;
	}

	cout<<"pExtSubobjectSimpleNoCopyElement = extSubobjectSimple.copyElement( 'r', 1 );"<<endl;
	pExtSubobjectSimpleNoCopyElement = extSubobjectSimple.copyElement( 'r', 1 );

	if ( pExtSubobjectSimpleNoCopyElement == NULL ){
	
		cout<<"The cExtSubobject -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cExtSubobject -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pExtSubobjectSimpleNoCopyElement;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing copying a cExtSubobject with all members set"<<endl;

	//if in Fib element structur
	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	cout<<"root.setNumberOfInputVariables( 10 );"<<endl;
	root.setNumberOfInputVariables( 10 );
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cVectorExtSubobject vecVariables( 4 );"<<endl;
	cVectorExtSubobject vecVariables( 4 );
	
	cout<<"vecVariables.setVariable( 1, root.getInputVariable( 7 ) );"<<endl;
	vecVariables.setVariable( 1, root.getInputVariable( 7 ) );
	cout<<"vecVariables.setValue( 2, 2 );"<<endl;
	vecVariables.setValue( 2, 2 );
	cout<<"vecVariables.setVariable( 3, root.getInputVariable( 4 ) );"<<endl;
	vecVariables.setVariable( 3, root.getInputVariable( 4 ) );
	cout<<"vecVariables.setValue( 4, 4 );"<<endl;
	vecVariables.setValue( 4, 4 );
	
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	vector< cFibVariable * > vecVariables;
	cout<<"vecVariables.push_back( root.getInputVariable( 7 ) )"<<endl;
	vecVariables.push_back( root.getInputVariable( 7 ) );
	cout<<"vecVariables.push_back( root.getInputVariable( 3 ) )"<<endl;
	vecVariables.push_back( root.getInputVariable( 3 ) );
	cout<<"vecVariables.push_back( root.getInputVariable( 4 ) )"<<endl;
	vecVariables.push_back( root.getInputVariable( 4 ) );
	cout<<"vecVariables.push_back( root.getInputVariable( 3 ) )"<<endl;
	vecVariables.push_back( root.getInputVariable( 3 ) );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	cout<<"cExtSubobject extSubobj2( 2, vecVariables, &root );"<<endl;
	cExtSubobject extSubobj2( 2, vecVariables, &root  );

	cout<<"cExtSubobject extSubobj2CopyConstruct( extSubobj2 );"<<endl;
	cExtSubobject extSubobj2CopyConstruct( extSubobj2 );

	if ( extSubobj2CopyConstruct.equalElement( extSubobj2 ) ){

		cout<<"The extSubobj2CopyConstruct Fib element is equal to extSubobj2. "<<endl;
	}else{
		cerr<<"Error: The extSubobj2CopyConstruct Fib element is not equal to extSubobj2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( extSubobj2CopyConstruct );

	cout<<"cFibElement * pExtSubobject2E2Copy = extSubobj2.copy();"<<endl;
	cFibElement * pExtSubobject2E2Copy = extSubobj2.copy();
	iReturn += testCompareTwoEqualObjects( *pExtSubobject2E2Copy, "pExtSubobject2E2Copy", extSubobj2, "extSubobj2" );
	//check the getFibElement() methode from cExtSubobject
	if ( NULL == pExtSubobject2E2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous Fib elementpointer for the external subobject element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib elementpointer for the external subobject element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cExtSubobject
	if ( NULL == pExtSubobject2E2Copy->getSuperiorFibElement() ){
	
		cout<<"The superior Fib elementpointer for the external subobject element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib elementpointer for the external subobject element is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( pExtSubobject2E2Copy );

	cout<<"cFibElement * pExtSubobject2E2CopyElement = extSubobj2.copyElement( 'u', 1 );"<<endl;
	cFibElement * pExtSubobject2E2CopyElement = extSubobj2.copyElement( 'u', 1 );

	if ( pExtSubobject2E2CopyElement->equalElement( extSubobj2 ) ){
	
		cout<<"The pExtSubobject2E2CopyElement Fib element is equal to extSubobj2. "<<endl;
	}else{
		cerr<<"Error: The pExtSubobject2E2CopyElement Fib element is not equal to extSubobj2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pExtSubobject2E2CopyElement );
	delete pExtSubobject2E2CopyElement;

	cout<<"cFibElement * pExtSubobject2E2Clone = extSubobj2.clone();"<<endl;
	cFibElement * pExtSubobject2E2Clone = extSubobj2.clone();
	iReturn += testCompareTwoEqualObjectsStructur( *pExtSubobject2E2Clone, "pExtSubobject2E2Clone", root, "root", true );
	pExtSubobject2E2Clone->deleteObject();


	return iReturn;
}



/**
 * This method tests a in the xml -format stored cExtSubobject.
 *
 * @param szFilename the name of the file wher the cFibVector is stored
 * @param lIdentifer the subobject number of the external subobject element
 * @param vecOutputValues the values of the output values
 * @return the number of errors occured in the test
 */
int testXmlExtSubobject( const string szFilename,
		long lSubobjNumber,
		vector< unsigned int > vecOutputValues ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cExtSubobject:"<<endl;
	
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
		
		const string szExtSubobjectElementName = "subobject";
		if ( szElementName == szExtSubobjectElementName ){
			cout<<"The root element is correctly named \""<< szExtSubobjectElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szExtSubobjectElementName <<"\"."<<endl;
			iReturn++;
		}
		
	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	//check the subobject number attribute
	int iReadedSubobjNumber = 0;
	if ( pXmlElement->Attribute( "number", & iReadedSubobjNumber ) ){
		
		if ( iReadedSubobjNumber == lSubobjNumber ){
			cout<<"The external subobject element correctly has the subobject number "<<lSubobjNumber<<". "<<endl;
		}else{
		cerr<<"Error: The external subobject element has the subobject number "<<
			iReadedSubobjNumber<<", but should have the subobject number "<<lSubobjNumber<<" "<<endl;
		iReturn++;
		}
	}else{
		cerr<<"Error: The external subobject element has no attribute subobject number. "<<endl;
		iReturn++;
	}
	
	//check output values
	TiXmlHandle xmlHandleOutputVariables = TiXmlHandle( pXmlElement );
	TiXmlElement * pXmlOutputVariables = xmlHandleOutputVariables.FirstChild().Element();
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	if ( pXmlOutputVariables ) {
		
		const char * szVectorXmlType = pXmlOutputVariables->Attribute( "type" );
		
		if ( szVectorXmlType == NULL ){
			cerr<<"Error: The vector has no type."<<endl;
			iReturn++;
		}else if ( string("externSubobject") == szVectorXmlType ) {
			cout<<"The type of the vector is correctly \"externSubobject\". "<<endl;
		}else{
			cerr<<"Error: The type of the vector is \""<< szVectorXmlType
				<<"\", but should be \"externSubobject\"."<<endl;
			iReturn++;
		}
		
		TiXmlHandle xmlHandleInVectorRoot = TiXmlHandle( pXmlOutputVariables );
		TiXmlElement * pXmlElemOutputValue =
			xmlHandleInVectorRoot.FirstChild().Element();
		
		int iReadedNumberOfElement = 0;
		for( int iNumberOfElement = 1; pXmlElemOutputValue;
				pXmlElemOutputValue = pXmlElemOutputValue->NextSiblingElement(), iNumberOfElement++ ){
		
			const string szElementName = pXmlElemOutputValue->Value();
			
			if ( pXmlElemOutputValue->Attribute( "number", & iReadedNumberOfElement ) ){
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
				cerr<<"Error: Ther couldn't be a 0'th vector element."<<endl;
				iReturn++;
			}else if ( (int)(vecOutputValues.size()) < iNumberOfElement ){
				cerr<<"Error: Ther couldn't be a "<< iNumberOfElement <<
					"'th vector element, because the vector has yust "<<
						vecOutputValues.size() <<" elements."<<endl;
				iReturn++;
			}
			
			if ( szElementName == "value" ){
				const char * pcValue = pXmlElemOutputValue->GetText();
				cout<<"The value of the element is: "<< pcValue <<endl;
				//converting value to double
				if ( (1 <= iNumberOfElement) &&
						( iNumberOfElement <= (int)(vecOutputValues.size()) ) ){
					double dValue;
					int iReadValues = sscanf ( pcValue, "%lf", & dValue );
					if ( iReadValues != 0){
						if ( dValue == vecOutputValues[ iNumberOfElement - 1 ] ){
							cout<<"The value of the element is correct."<<endl;
						}else{
							cerr<<"Error: The value of the element should be : "<<
								vecOutputValues[ iNumberOfElement - 1 ] <<endl;
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
	}//end if ther are output values
	
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	if ( pXmlOutputVariables ) {
		string szElementName = pXmlOutputVariables->Value();

		if ( szElementName == "output_variables" ){
			cout<<"The subelement is correctly named \"output_variables\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the subelement is "<< szElementName <<" and not \"output_variables\"."<<endl;
			iReturn++;
		}
		
		TiXmlHandle xmlHandleInputVariable = TiXmlHandle( pXmlOutputVariables );
		TiXmlElement * pXmlInputVariable = xmlHandleInputVariable.FirstChild().Element();
		
		unsigned int uiActualInputVariable = 0;
		for ( ; pXmlInputVariable; uiActualInputVariable++,
				pXmlInputVariable = pXmlInputVariable->NextSiblingElement() ){
		
			const string szVariableName = pXmlInputVariable->Value();
			if ( szVariableName == "variable" ){
				cout<<"The subelement is correctly named \"variable\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the subelement is "<< szVariableName <<" and not \"variable\"."<<endl;
				iReturn++;
			}
			const char * szVariableSubobjNumber = pXmlInputVariable->GetText();
			
			if ( szVariableSubobjNumber == NULL ){
				cerr<<"Error: The "<<uiActualInputVariable<<"'th output values has no subobject number."<<endl;
				iReturn++;
			}else if ( uiActualInputVariable < vecOutputValues.size() ){
				
				const unsigned int uiCorrectVariableId =
					vecOutputValues[ uiActualInputVariable ];
				const unsigned int uiLoadedVariableId =
					atol( szVariableSubobjNumber );
				
				if ( uiCorrectVariableId == uiLoadedVariableId ){
					cout<<"The "<<uiActualInputVariable<<" input variable subobject number is correctly "<<
						uiCorrectVariableId<<" . "<<endl;
				}else{
					cerr<<"Error: The "<<uiActualInputVariable<<" input variable subobject number is "<<
						uiLoadedVariableId<<", but should be "<<uiCorrectVariableId<<" ."<<endl;
					iReturn++;
				}
		
			}else{// pXmlUnderExtSubobject == NULL
				cerr<<"Error: Ther is an "<<uiActualInputVariable<<
					"'th input varable with the value \""<< szVariableSubobjNumber <<"\"."<<endl;
				iReturn++;
			}
			
		}
		if ( uiActualInputVariable != vecOutputValues.size() ){
			cerr<<"Error: Ther are "<<uiActualInputVariable<<" output values, but it should be "<<
				vecOutputValues.size()<<"."<<endl;
			iReturn++;
		}
		
	}else{// pXmlOutputVariables == NULL
		if ( vecOutputValues.empty() ){
			cout<<"Ther are correctly no output values . "<<endl;
		}else{
			cerr<<"Error: No output values handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
		}
	}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	return iReturn;
}




/**
 * This method tests the storeXml() method of the cExtSubobject class.
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
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the storeXml() method on an empte external subobject"<<endl;

	cout<<"cExtSubobject extSubobjectNr0( 0 );"<<endl;
	cExtSubobject extSubobjectNr0( 0 );
	
	long lSubobjNumber = 0;
	vector< unsigned int > vecOutVarNumbers;
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlExtSubobjectFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extSubobjectNr0.xml" );
	ofstream * pFileVectorPostion = new ofstream( szXmlExtSubobjectFileName );
	
	bool bStoreSuccesfull = extSubobjectNr0.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cExtSubobject was stored successfull to the file \""<< szXmlExtSubobjectFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cExtSubobject to the file \""<< szXmlExtSubobjectFileName <<"\" failed."<<endl;
		iReturn++;
	}	
	iReturn += testXmlExtSubobject( szXmlExtSubobjectFileName, lSubobjNumber, vecOutVarNumbers );


	
	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the storeXml() method on an external subobject with id 7"<<endl;

	cout<<"cExtSubobject extSubobjectNr7( 7 );"<<endl;
	cExtSubobject extSubobjectNr7( 7 );
	
	lSubobjNumber = 7;
	/*vecOutVarNumbers.empty();*/
	
	szFileNameBuffer[0] = 0;
	szXmlExtSubobjectFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extSubobjectNr7.xml" );
	pFileVectorPostion = new ofstream( szXmlExtSubobjectFileName );
	
	bStoreSuccesfull = extSubobjectNr7.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cExtSubobject was stored successfull to the file \""<< szXmlExtSubobjectFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cExtSubobject to the file \""<< szXmlExtSubobjectFileName <<"\" failed."<<endl;
		iReturn++;
	}	
	iReturn += testXmlExtSubobject( szXmlExtSubobjectFileName, lSubobjNumber,
		 vecOutVarNumbers );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the storeXml() method on an external subobject with output values"<<endl;

	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	cout<<"root.setNumberOfInputVariables( 10 );"<<endl;
	root.setNumberOfInputVariables( 10 );
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cVectorExtSubobject vecOutputValues( 3 );"<<endl;
	cVectorExtSubobject vecOutputValues( 3 );
	
	cout<<"vecOutputValues.setValue( 1, 1 );"<<endl;
	vecOutputValues.setValue( 1, 1 );
	vecOutVarNumbers.push_back( 1 );
	cout<<"vecOutputValues.setValue( 2, 5 );"<<endl;
	vecOutputValues.setValue( 2, 5 );
	vecOutVarNumbers.push_back( 5 );
	cout<<"vecOutputValues.setValue( 3, 3 );"<<endl;
	vecOutputValues.setValue( 3, 3 );
	vecOutVarNumbers.push_back( 3 );
	
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	vector< cFibVariable * > vecOutputValues;
	cout<<"root.getInputVariable( 1 )->setValue( 1 )"<<endl;
	root.getInputVariable( 1 )->setValue( 1 );
	vecOutputValues.push_back( root.getInputVariable( 1 ) );
	vecOutVarNumbers.push_back( 1 );
	cout<<"root.getInputVariable( 2 )->setValue( 5 )"<<endl;
	root.getInputVariable( 2 )->setValue( 5 );
	vecOutputValues.push_back( root.getInputVariable( 2 ) );
	vecOutVarNumbers.push_back( 5 );
	cout<<"root.getInputVariable( 5 )->setValue( 3 )"<<endl;
	root.getInputVariable( 5 )->setValue( 3 );
	vecOutputValues.push_back( root.getInputVariable( 5 ) );
	vecOutVarNumbers.push_back( 3 );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	lSubobjNumber = -8;
	cout<<"cExtSubobject extSubobjectNrm8OutVar3( lSubobjNumber, vecOutputValues );"<<endl;
	cExtSubobject extSubobjectNrm8OutVar3( lSubobjNumber, vecOutputValues );
	
	szFileNameBuffer[0] = 0;
	szXmlExtSubobjectFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extSubobjectNrm8OutVar3.xml" );
	pFileVectorPostion = new ofstream( szXmlExtSubobjectFileName );
	
	bStoreSuccesfull = extSubobjectNrm8OutVar3.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cExtSubobject was stored successfull to the file \""<< szXmlExtSubobjectFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cExtSubobject to the file \""<< szXmlExtSubobjectFileName <<"\" failed."<<endl;
		iReturn++;
	}	
	iReturn += testXmlExtSubobject( szXmlExtSubobjectFileName, lSubobjNumber,
		 vecOutVarNumbers );
	
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

	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the store() method on external subobject subobject element"<<endl;

	cout<<"cExtSubobject extSubobjNr0( 0 );"<<endl;
	cExtSubobject extSubobjNr0( 0 );
	
	cout<<"cRoot root( &extSubobjNr0 );"<<endl;
	cRoot root( &extSubobjNr0 );
	
	//test get compressed size
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	unsigned int uiCompressedSize = 4 + 0;
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	unsigned int uiCompressedSize = 4 + 0 + 4;
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	if ( (unsigned int)(extSubobjNr0.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size is "<<
			extSubobjNr0.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extSubobjNr0.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bool bStoreSuccesfull = extSubobjNr0.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cExtSubobject1[] = { (char)0x0E };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtSubobject1, 1 );

	
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the store() method with differnt number"<<endl;

	cout<<"cExtSubobject extSubobjNr7( 7 );"<<endl;
	cExtSubobject extSubobjNr7( 7 );

	cout<<"cRoot rootSub12( &extSubobjNr7 );"<<endl;
	cRoot rootSub12( &extSubobjNr7 );
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	vector<cDomainSingle*> vecDomainsE0( 0 );
	
	cout<<"vectorDomainExtObjE0={ }"<<endl;
	cDomainVector vectorDomainExtObjE0( vecDomainsE0 );
	
	cout<<"rootSub12.getDomains()->addDomain( cTypeExtSubobject( 13 ), vectorDomainExtObjE0 );"<<endl;
	rootSub12.getDomains()->addDomain( cTypeExtSubobject( 13 ), vectorDomainExtObjE0 );
	
	//test get compressed size
	uiCompressedSize = 4 + 4;
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"rootSub12.setNumberOfExternSubobjects( 13 );"<<endl;
	rootSub12.setNumberOfExternSubobjects( 13 );
	//test get compressed size
	uiCompressedSize = 4 + 4 + 4;
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	if ( (unsigned int)(extSubobjNr7.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size is "<<
			extSubobjNr7.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extSubobjNr7.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = extSubobjNr7.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	const char cExtSubobjNr7[] = { (char)0x7E };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtSubobjNr7, 1 );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	const char cExtSubobjNr7[] = { (char)0x7E, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtSubobjNr7, 2 );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR


	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the store() method on external subobject with output values"<<endl;

	cout<<"rootSub12.setNumberOfInputVariables( 10 );"<<endl;
	rootSub12.setNumberOfInputVariables( 10 );
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	vector<cDomainSingle*> vecDomainsE3( 3 );
	
	vecDomainsE3[ 0 ] = new cDomainNaturalNumberBit( 20 );
	vecDomainsE3[ 1 ] = new cDomainNaturalNumber( 28 );
	vecDomainsE3[ 2 ] = new cDomainNaturalNumberBit( 4 );
	
	cout<<"vectorDomainExtObjE3={ cDomainNaturalNumberBit( 20 ), "<<
		"cDomainNaturalNumber( 28 ), cDomainNaturalNumberBit( 4 ) }"<<endl;
	cDomainVector vectorDomainExtObjE3( vecDomainsE3 );
	
	delete vecDomainsE3[ 0 ];
	delete vecDomainsE3[ 1 ];
	delete vecDomainsE3[ 2 ];
	
	cout<<"rootSub12.getDomains()->addDomain( cTypeExtSubobject( 3 ), vectorDomainExtObjE3 );"<<endl;
	rootSub12.getDomains()->addDomain( cTypeExtSubobject( 3 ), vectorDomainExtObjE3 );

	cout<<"cVectorExtSubobject vecOutputValues( 3 );"<<endl;
	cVectorExtSubobject vecOutputValues( 3 );
	
	cout<<"rootSub12.getInputVariable( 1 )->setValue( 1 )"<<endl;
	rootSub12.getInputVariable( 1 )->setValue( 1 );
	cout<<"vecOutputValues.setVariable( 1, rootSub12.getInputVariable( 1 ) );"<<endl;
	vecOutputValues.setVariable( 1, rootSub12.getInputVariable( 1 ) );
	cout<<"vecOutputValues.setValue( 2, 3 );"<<endl;
	vecOutputValues.setValue( 2, 3 );
	cout<<"rootSub12.getInputVariable( 5 )->setValue( 3 )"<<endl;
	rootSub12.getInputVariable( 5 )->setValue( 3 );
	cout<<"vecOutputValues.setVariable( 3, rootSub12.getInputVariable( 5 ) );"<<endl;
	vecOutputValues.setVariable( 3, rootSub12.getInputVariable( 5 ) );
	
	//test get compressed size
	uiCompressedSize = 4 + 4 + (1 + 8) + (1 + 5) + (1 + 8);
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	vector< cFibVariable * > vecOutputValues;
	cout<<"rootSub12.getInputVariable( 1 )->setValue( 1 )"<<endl;
	rootSub12.getInputVariable( 1 )->setValue( 1 );
	vecOutputValues.push_back( rootSub12.getInputVariable( 1 ) );
	cout<<"rootSub12.getInputVariable( 2 )->setValue( 5 )"<<endl;
	rootSub12.getInputVariable( 2 )->setValue( 5 );
	vecOutputValues.push_back( rootSub12.getInputVariable( 2 ) );
	cout<<"rootSub12.getInputVariable( 5 )->setValue( 3 )"<<endl;
	rootSub12.getInputVariable( 5 )->setValue( 3 );
	vecOutputValues.push_back( rootSub12.getInputVariable( 5 ) );
	//test get compressed size
	uiCompressedSize = 4 + 4 + 4 + 3 * 8;
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	cout<<"cExtSubobject extObjectNr3InVar3( 3, vecOutputValues  );"<<endl;
	cExtSubobject extObjectNr3InVar3( 3, vecOutputValues  );
	
	cout<<"rootSub12.setMainFibObject( &extObjectNr3InVar3 );"<<endl;
	rootSub12.setMainFibObject( &extObjectNr3InVar3 );

	if ( (unsigned int)(extObjectNr3InVar3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size is "<<
			extObjectNr3InVar3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extObjectNr3InVar3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = extObjectNr3InVar3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	const char cExtSubobjectNr3InVar3[] = { (char)0x3E, (char)0x03, (char)0x8C, (char)0x03 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtSubobjectNr3InVar3, 4 );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	const char cExtSubobjectNr3InVar3[] = { (char)0x3E, (char)0x13, (char)0x50, (char)0x30, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtSubobjectNr3InVar3, 5 );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR


	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the store() method on external subobject with subobjects with domains"<<endl;
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	//test get compressed size
	uiCompressedSize = 4 + 4 + (1 + 4) + (1 + 5) + (1 + 4);
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cDomainNaturalNumberBit domOutVar( 16 );"<<endl;
	cDomainNaturalNumberBit domOutVar( 16 );
	
	cout<<"rootSub12.getDomains()->addDomain( cTypeExtSubobject(), domOutVar );"<<endl;
	rootSub12.getDomains()->addDomain( cTypeExtSubobject(), domOutVar );
	//test get compressed size
	uiCompressedSize = 4 + 4 + 16 + 3 * 4;
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	cout<<"rootSub12.getDomains()->addDomain( cTypeVariable(), cDomainNaturalNumberBit( 4 ) );"<<endl;
	rootSub12.getDomains()->addDomain( cTypeVariable(), cDomainNaturalNumberBit( 4 ) );
	
	if ( (unsigned int)(extObjectNr3InVar3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size is "<<
			extObjectNr3InVar3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extObjectNr3InVar3Dom.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = extObjectNr3InVar3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	const char cExtObjectNr3InVar3Dom[] = { (char)0x3E, (char)0xC3, (char)0x38 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtObjectNr3InVar3Dom, 3 );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	const char cExtObjectNr3InVar3Dom[] = { (char)0x3E, (char)0x03, (char)0x00, (char)0x51, (char)0x03 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtObjectNr3InVar3Dom, 5 );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

	return iReturn;
}



/**
 * This function tests the number of subobject methods of the class.
 *
 * methods tested:
 * 	- longFib getNumberSubobject() const;
 * 	- void setNumberSubobject( const longFib lInNumberSubobject );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testNumberSubobject( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the number of subobject methods"<<endl;
	
	cout<<"cExtSubobject extSubobject( 0 );"<<endl;
	cExtSubobject extSubobject( 0 );

	for ( unsigned long ulIteration = 0; ulIteration < MAX_RAND_TEST_SIZE;
			ulIteration++ ){
		
		const unsignedIntFib uiNewNumberSubobject = rand() % ((rand() % (256 * 256)) + 1);
		
		cout<<"extSubobject.setNumberSubobject( "<<uiNewNumberSubobject<<" );"<<endl;
		extSubobject.setNumberSubobject( uiNewNumberSubobject );
		
		//check the getNumberSubobject() methode from cExtSubobject
		if ( extSubobject.getNumberSubobject() == uiNewNumberSubobject ){
		
			cout<<"The number of subobject for the external subobject element is correctly "<<
				uiNewNumberSubobject<<" . "<<endl;
		}else{
			cerr<<"Error: The number of subobject for the external subobject element is not "<<
				uiNewNumberSubobject<<", but "<< extSubobject.getNumberSubobject()<<" ."<<endl;
			iReturn++;
		}
	}
	
	return iReturn;
}

#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR


/**
 * This function tests the input variables methods of the class.
 *
 * methods tested:
 * 	- cVectorExtSubobject * getOutputVector();
 * 	- const cVectorExtSubobject * cExtSubobject::getOutputVector() const
 * 	- getOutputVector()->resize(  );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testOutputValues( unsigned long &ulTestphase ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the input variables methods"<<endl;
	
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
	cout<<"pVariable5 = root.getInputVariable( 5 );"<<endl;
	vecVariablesDef.push_back( root.getInputVariable( 5 ) );
	cout<<"pVariable6 = root.getInputVariable( 6 );"<<endl;
	vecVariablesDef.push_back( root.getInputVariable( 6 ) );
	cout<<"pVariable7 = root.getInputVariable( 7 );"<<endl;
	vecVariablesDef.push_back( root.getInputVariable( 7 ) );
	cout<<"pVariable8 = root.getInputVariable( 8 );"<<endl;
	vecVariablesDef.push_back( root.getInputVariable( 8 ) );
	cout<<"pVariable9 = root.getInputVariable( 9 );"<<endl;
	vecVariablesDef.push_back( root.getInputVariable( 9 ) );

	cout<<"cRoot rootNDef;"<<flush<<endl;
	cRoot rootNDef;
	cout<<"rootNDef.setNumberOfInputVariables( 10 );"<<endl;
	rootNDef.setNumberOfInputVariables( 10 );
	vector< cFibVariable * > vecVariablesNDef;
	cout<<"pVariableN1 = rootNDef.getInputVariable( 1 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 1 ) );
	cout<<"pVariableN2 = rootNDef.getInputVariable( 2 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 2 ) );
	cout<<"pVariableN3 = rootNDef.getInputVariable( 3 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 3 ) );
	cout<<"pVariableN4 = rootNDef.getInputVariable( 4 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 4 ) );
	cout<<"pVariableN5 = rootNDef.getInputVariable( 5 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 5 ) );
	cout<<"pVariableN6 = rootNDef.getInputVariable( 6 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 6 ) );
	cout<<"pVariableN7 = rootNDef.getInputVariable( 7 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 7 ) );
	
	set< cFibVariable * > setVariablesNDef( vecVariablesNDef.begin(),
		vecVariablesNDef.end() );

	cVectorExtSubobject vecCorrectOutputValues( 0 );
	cout<<"cExtSubobject extObject( 1, 0, &root );"<<endl;
	cExtSubobject extObject( 1, 0, &root );
	cout<<"const cExtSubobject & constExtSubobject = extObject;"<<endl;
	const cExtSubobject & constExtSubobject = extObject;
	
	unsigned int uiNumberOfOutputValues = 0;
	set< cFibVariable * > setCorrectUsedVariables;
	bool bValidElement = true;
	
//TODO

	for ( unsigned long uiIteration = 1; uiIteration <= MAX_RAND_TEST_SIZE; uiIteration++ ){
		
		cout<<endl<<"Running iteration "<<uiIteration<<endl;
		//make changes

		if ( rand() % 8 != 0 ){
			//change vector of output values
			//choose position wher to change it
			const unsignedIntFib uiPositionToSet =
				rand() % ( uiNumberOfOutputValues + 8 );
			
			if ( rand() % 2 == 0 ){
				//change to value
				//choose output value to set
				const doubleFib dValue = (doubleFib(rand() % ( 256L * 256L ) -
					(128L * 256L) )) / 256.0;
				
				vecCorrectOutputValues.setValue( uiPositionToSet, dValue );
				
				cout<<"extObject.getOutputVector()->setValue( uiPositionToSet, dValue );"<<endl;
				extObject.getOutputVector()->setValue( uiPositionToSet, dValue );
			}else{//change to variable
				//choose output value to set
				cFibVariable * pVariableToSet = NULL;
				if ( rand() % 4 ){
					//choose defined variable
					const int iVariable = rand() % vecVariablesDef.size();
					
					cout<<"pVariableToSet = pVariable"<<(iVariable+1)<<" ; ";
					pVariableToSet = vecVariablesDef[ iVariable ];
				}else if ( rand() % 4 ){//choose not defined variable
					const int iVariable = rand() % vecVariablesNDef.size();
					
					cout<<"pVariableToSet = pVariableN"<<(iVariable+1)<<" ; ";
					pVariableToSet = vecVariablesNDef[ iVariable ];
				}else{//choose NULL pointer as output value
					cout<<"pVariableToSet = NULL; ";
					pVariableToSet = NULL;
				}
				
				vecCorrectOutputValues.setVariable( uiPositionToSet, pVariableToSet );
				
				cout<<"extObject.getOutputVector()->setVariable( uiPositionToSet, pVariableToSet );"<<endl;
				extObject.getOutputVector()->setVariable( uiPositionToSet, pVariableToSet );
			}//end if choose if variable or value to set
		}else{//change with setNumberOfOutputValues()
			//choose new number of output values
			uiNumberOfOutputValues = rand() % ((rand() % 32) + 1);
			
			cout<<"extObject.getOutputVector()->resize( "<<uiNumberOfOutputValues<<" );"<<endl;
			extObject.getOutputVector()->resize( uiNumberOfOutputValues );
			//generate correct vector of output values
			vecCorrectOutputValues.resize( uiNumberOfOutputValues );
	
		}//end if choose change type
		//generate correct vector of used variables
 		setCorrectUsedVariables = vecCorrectOutputValues.getUsedVariables();
		//evalue if the cExtSubobject element is valid
/*TODO weg (if the variable is defined above is not part of the Fib element):
		bValidElement = true;
		for ( set<cFibVariable*>::const_iterator
				itrOutputVariable = setCorrectUsedVariables.begin();
				itrOutputVariable != setCorrectUsedVariables.end(); itrOutputVariable++ ){
			
			if ( (*itrOutputVariable) == NULL ){
				//variable is NULL pointer -> Fib-element not valid
				bValidElement = false;
				break;
			}else if ( setVariablesNDef.find( (*itrOutputVariable) ) !=
					setVariablesNDef.end() ){
				//variable not defined above -> Fib-element not valid
				bValidElement = false;
				break;
			}
		}
*/
		
		//check the getOutputVector()->getNumberOfElements() methode from cExtSubobject
		if ( extObject.getOutputVector()->getNumberOfElements() == uiNumberOfOutputValues ){
		
			cout<<"The extObject has correctly "<<uiNumberOfOutputValues<<
				" output values. "<<endl;
		}else{
			cerr<<"Error: The extObject has "<<extObject.getOutputVector()->getNumberOfElements()<<
				" output values, but sould have "<<uiNumberOfOutputValues<<" . "<<endl;
			iReturn++;
			uiNumberOfOutputValues = extObject.getOutputVector()->getNumberOfElements();
		}
		//check the getOutputVector() methode from cExtSubobject
		if ( extObject.getOutputVector()->equal( vecCorrectOutputValues ) ){
		
			cout<<"The extObject has the correct output values. "<<endl;
		}else{
			cerr<<"Error: The extObject has not the correct output values. "<<endl;
			iReturn++;
		}
		//check the getOutputVector() const methode from cExtSubobject
		if ( ! constExtSubobject.getOutputVector()->equal( vecCorrectOutputValues ) ){
			cerr<<"Error: The constExtSubobject has not the correct output values. "<<endl;
			iReturn++;
		}
		
		//check the isValidFibElement() method
		if ( extObject.isValidFibElement() == bValidElement ){
		
			cout<<"The extObject is correctly a "<<
				(bValidElement?"valid":"not valid")<<" cExtSubobject. "<<endl;
		}else{
			cerr<<"Error: The extObject is "<<(bValidElement?"not a valid":"a valid")<<
				" cExtSubobject, but should"<<(bValidElement?"":"n't")<<" be ."<<endl;
			iReturn++;
		}
		//check getUsedVariables() method
		cout<<"setUsedVariables = extObject.getUsedVariables( ED_POSITION ); "<<endl;
		const set< cFibVariable * > setUsedVariables =
			extObject.getUsedVariables( ED_POSITION );
		if ( setUsedVariables == setCorrectUsedVariables ){
		
			cout<<"The correct used / output values wher given back. "<<endl;
		}else{
			cerr<<"Error: The used / output values given back are wrong. "<<endl;
			iReturn++;
		}
		//check getDefinedVariables() method
		cout<<"liDefinedVariables = extObject.getDefinedVariables( ED_POSITION ); "<<endl;
		const list< cFibVariable * > liDefinedVariables =
			extObject.getDefinedVariables( ED_POSITION );
		if ( liDefinedVariables.empty() ){
		
			cout<<"Ther are correctly no defined variables given back. "<<endl;
		}else{
			cerr<<"Error: Ther are defined variables given back. "<<endl;
			iReturn++;
		}
		
	}//end for rand iteration
	
	
	return iReturn;
}


#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR

/**
 * This function tests the output values methods of the class.
 *
 * methods tested:
 * 	- unsignedIntFib getNumberOfOutputVariables() const;
 * 	- vector< cFibVariable* > getOutputVariables();
 * 	- void setOutputVariables( vector< cFibVariable* > vecInOutputVariables );
 * 	- cFibVariable * getOutputVariable( const unsignedIntFib uiNumberOfOutputVariable );
 * 	- bool setOutputVariable( const unsignedIntFib uiNumberOfOutputVariable, cFibVariable * pOutputVariable );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testOutputValues( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the output values methods"<<endl;
	
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
	cout<<"pVariable5 = root.getInputVariable( 5 );"<<endl;
	vecVariablesDef.push_back( root.getInputVariable( 5 ) );
	cout<<"pVariable6 = root.getInputVariable( 6 );"<<endl;
	vecVariablesDef.push_back( root.getInputVariable( 6 ) );
	cout<<"pVariable7 = root.getInputVariable( 7 );"<<endl;
	vecVariablesDef.push_back( root.getInputVariable( 7 ) );
	cout<<"pVariable8 = root.getInputVariable( 8 );"<<endl;
	vecVariablesDef.push_back( root.getInputVariable( 8 ) );
	cout<<"pVariable9 = root.getInputVariable( 9 );"<<endl;
	vecVariablesDef.push_back( root.getInputVariable( 9 ) );

	cout<<"cRoot rootNDef;"<<flush<<endl;
	cRoot rootNDef;
	cout<<"rootNDef.setNumberOfInputVariables( 10 );"<<endl;
	rootNDef.setNumberOfInputVariables( 10 );
	vector< cFibVariable * > vecVariablesNDef;
	cout<<"pVariableN1 = rootNDef.getInputVariable( 1 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 1 ) );
	cout<<"pVariableN2 = rootNDef.getInputVariable( 2 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 2 ) );
	cout<<"pVariableN3 = rootNDef.getInputVariable( 3 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 3 ) );
	cout<<"pVariableN4 = rootNDef.getInputVariable( 4 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 4 ) );
	cout<<"pVariableN5 = rootNDef.getInputVariable( 5 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 5 ) );
	cout<<"pVariableN6 = rootNDef.getInputVariable( 6 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 6 ) );
	cout<<"pVariableN7 = rootNDef.getInputVariable( 7 );"<<endl;
	vecVariablesNDef.push_back( rootNDef.getInputVariable( 7 ) );
	
	set< cFibVariable * > setVariablesNDef( vecVariablesNDef.begin(),
		vecVariablesNDef.end() );

	cout<<"root.setNumberOfExternSubobjects( 1 );"<<endl;
	root.setNumberOfExternSubobjects( 1 );
	
	vector< cFibVariable * > vecCorrectOutputVariables;
	cout<<"cExtSubobject extSubobject( 1, {}, &root );"<<endl;
	cExtSubobject extSubobject( 1, vecCorrectOutputVariables, &root );
	
	unsigned int uiNumberOfOutputvariables = 0;
	set< cFibVariable * > setCorrectUsedVariables;
	bool bValidElement = true;
	
	for ( unsigned long uiIteration = 1; uiIteration <= MAX_RAND_TEST_SIZE; uiIteration++ ){
		
		cout<<endl<<"Running iteration "<<uiIteration<<endl;
		//make changes
		const unsigned int uiChangeType = rand() % 2;
		
		switch ( uiChangeType ){
			case 0:{//change with setOutputVariable()
				//choose output varible to set
				cFibVariable * pVariableToSet = NULL;
				bool bVariableCanBeSet = true;
				if ( rand() % 4 ){
					//choose defined variable
					const int iVariable = rand() % vecVariablesDef.size();
					
					cout<<"pVariableToSet = pVariable"<<(iVariable+1)<<" ; ";
					pVariableToSet = vecVariablesDef[ iVariable ];
				}else if ( rand() % 4 ){//choose not defined variable
					const int iVariable = rand() % vecVariablesNDef.size();
					
					cout<<"pVariableToSet = pVariableN"<<(iVariable+1)<<" ; ";
					pVariableToSet = vecVariablesNDef[ iVariable ];
				}else{//choose NULL pointer as output variable
					cout<<"pVariableToSet = NULL; ";
					pVariableToSet = NULL;
					bVariableCanBeSet = false;
				}
				
				//choose position wher to set it
				const unsignedIntFib uiPositionToSet =
					rand() % ( vecCorrectOutputVariables.size() + 8 );
				if ( ( pVariableToSet != NULL ) && ( 1 <= uiPositionToSet ) &&
						( uiPositionToSet <= vecCorrectOutputVariables.size() + 1 ) ){
					
					if ( uiPositionToSet != (vecCorrectOutputVariables.size() + 1) ){
						
						vecCorrectOutputVariables[ uiPositionToSet - 1 ] = pVariableToSet;
					}else{//append to end
						vecCorrectOutputVariables.push_back( pVariableToSet );
						uiNumberOfOutputvariables++;
					}
				}else{//position outside bounds
					bVariableCanBeSet = false;
				}
				cout<<"setOutputVariable( "<<uiPositionToSet<<", pVariableToSet="<<pVariableToSet<<" );"<<endl;
				const bool bOutputVariableSet =
					extSubobject.setOutputVariable( uiPositionToSet, pVariableToSet );
				
				if ( bOutputVariableSet == bVariableCanBeSet ){
					cout<<"The output variable pVariableToSet could correctly be "<<
						(bOutputVariableSet?"set":"not set")<<" . "<<endl;
				}else{
					cerr<<"Error: The output variable pVariableToSet was "<<
						(bOutputVariableSet?"set":"not set")<<
						", but should"<<(bVariableCanBeSet?"":"n't")<<" be ."<<endl;
					iReturn++;
				}
				
			}break;
			case 1:{//change with setOutputVariables()
				//choose output varible to set
				uiNumberOfOutputvariables = rand() % ((rand() % 32) + 1);
				vecCorrectOutputVariables.clear();
				cout<<"New output values: ";
				for ( unsigned int uiActualInVar = 1;
					 uiActualInVar <= uiNumberOfOutputvariables; uiActualInVar++){
					
					if ( rand() % 4 ){
						//choose defined variable
						const int iVariable = rand() % vecVariablesDef.size();
						
						vecCorrectOutputVariables.push_back( vecVariablesDef[ iVariable ] );
						cout<<"pVariable"<<(iVariable+1)<<" ; ";
					}else if ( rand() % 4 ){//choose not defined variable
						const int iVariable = rand() % vecVariablesNDef.size();
						
						vecCorrectOutputVariables.push_back( vecVariablesNDef[ iVariable ] );
						cout<<"pVariableN"<<(iVariable+1)<<" ; ";
					}else{//choose NULL pointer as output variable
						vecCorrectOutputVariables.push_back( NULL );
						cout<<"NULL ; ";
					}
				}
				cout<<endl;
				//set new output values
				const vector< cFibVariable * > vecToSetOutputVariables = vecCorrectOutputVariables;
				cout<<"xtSubobject.setOutputVariables( {new output values} );"<<endl;
				extSubobject.setOutputVariables( vecToSetOutputVariables );
				
			}break;
			/*case 2:{//change with setNumberOfOutputVariables()
				//choose new number of output values
				uiNumberOfOutputvariables = rand() % ((rand() % 32) + 1);
				
				cout<<"extSubobject.setNumberOfOutputVariables( "<<uiNumberOfOutputvariables<<" );"<<endl;
				extSubobject.setNumberOfOutputVariables( uiNumberOfOutputvariables );
				//generate correct vector of output values
				vecCorrectOutputVariables.resize( uiNumberOfOutputvariables, NULL );
			}break;*/
			default://Error: Wrong change mode
				cerr<<"Error: Wrong change mode "<<uiChangeType<<endl;
				continue;
		};
		//generate correct vector of used variables
 		setCorrectUsedVariables.clear();
		setCorrectUsedVariables.insert( vecCorrectOutputVariables.begin(),
			vecCorrectOutputVariables.end() );
		setCorrectUsedVariables.erase( ((cFibVariable*)(NULL)) );
/*TODO weg just check Fib element
		//evalue if the cExtSubobject element is valid
		bValidElement = true;
		for ( vector< cFibVariable * >::const_iterator
				itrOutputVariable = vecCorrectOutputVariables.begin();
				itrOutputVariable != vecCorrectOutputVariables.end(); itrOutputVariable++ ){
			
			if ( (*itrOutputVariable) == NULL ){
				//variable is NULL pointer -> Fib element not valid
				bValidElement = false;
				break;
			}else if ( setVariablesNDef.find( (*itrOutputVariable) ) !=
					setVariablesNDef.end() ){
				//variable not defined above -> Fib element not valid
				bValidElement = false;
				break;
			}
		}
*/
		
		//check the getNumberOfOutputVariables() methode from cIf
		if ( extSubobject.getNumberOfOutputVariables() == uiNumberOfOutputvariables ){
		
			cout<<"The extSubobject has correctly "<<uiNumberOfOutputvariables<<
				" output values. "<<endl;
		}else{
			cerr<<"Error: The extSubobject has "<<extSubobject.getNumberOfOutputVariables()<<
				" output values, but sould have "<<uiNumberOfOutputvariables<<" . "<<endl;
			iReturn++;
			uiNumberOfOutputvariables = extSubobject.getNumberOfOutputVariables();
		}
		//check the getNumberOfOutputVariables() methode from cIf
		if ( extSubobject.getOutputVariables() == vecCorrectOutputVariables ){
		
			cout<<"The extSubobject has the correct output values. "<<endl;
		}else{
			cerr<<"Error: The extSubobject has not the correct output values. "<<endl;
			iReturn++;
		}
		//check getOutputVariable() method
		for ( unsigned int uiActualInVar = 1; uiActualInVar <= uiNumberOfOutputvariables;
				uiActualInVar++ ){
			cFibVariable * pActualInVar = extSubobject.getOutputVariable( uiActualInVar );
			
			if ( uiActualInVar <= vecCorrectOutputVariables.size() ){
				if ( pActualInVar == vecCorrectOutputVariables[ uiActualInVar - 1 ] ){
				
					cout<<"The extSubobject has the correct "<<uiActualInVar<<"'th output variable. "<<endl;
				}else{
					cerr<<"Error: The extSubobject has the correct "<<uiActualInVar
						<<"'th output variable, it is "<<pActualInVar<<" but should be "<<
						vecCorrectOutputVariables[ uiActualInVar - 1 ]<<" . "<<endl;
					iReturn++;
				}
			}else{//more output values exists than is correct
				cerr<<"Error: Ther was an "<<uiActualInVar<<"'th output variable ("<<
					pActualInVar<<") given back, but ther should be just "<<
					vecCorrectOutputVariables.size()<<" output values. "<<endl;
				iReturn++;
			}
		}//end for all output values
		
		//check the isValidFibElement() method
		if ( extSubobject.isValidFibElement() == bValidElement ){
		
			cout<<"The extSubobject is correctly a "<<
				(bValidElement?"valid":"not valid")<<" cExtSubobject. "<<endl;
		}else{
			cerr<<"Error: The extSubobject is "<<(bValidElement?"not a valid":"a valid")<<
				" cExtSubobject, but should"<<(bValidElement?"":"n't")<<" be ."<<endl;
			iReturn++;
		}
		//check getUsedVariables() method
		cout<<"setUsedVariables = extSubobject.getUsedVariables( ED_POSITION ); "<<endl;
		const set< cFibVariable * > setUsedVariables =
			extSubobject.getUsedVariables( ED_POSITION );
		if ( setUsedVariables == setCorrectUsedVariables ){
		
			cout<<"The correct used / output values wher given back. "<<endl;
		}else{
			cerr<<"Error: The used / output values given back are wrong. "<<endl;
			iReturn++;
		}
		//check getDefinedVariables() method
		cout<<"liDefinedVariables = extSubobject.getDefinedVariables( ED_POSITION ); "<<endl;
		const list< cFibVariable * > liDefinedVariables =
			extSubobject.getDefinedVariables( ED_POSITION );
		if ( liDefinedVariables.empty() ){
		
			cout<<"Ther are correctly no defined variables given back. "<<endl;
		}else{
			cerr<<"Error: Ther are defined variables given back. "<<endl;
			iReturn++;
		}
		
	}//end for rand iteration
	
	
	return iReturn;
}
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR



/**
 * This methods checks the variables of the given object fibObject.
 *
 * methods tested:
 * 	- bool isUsedVariable( const cFibVariable *variable, edDirection direction=ED_POSITION ) const;
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION and ED_BELOW_EQUAL and ED_HIGHER_EQUAL );
 * 	- cFibVariable * getDefinedVariable();
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION (and ED_HIGHER for subobjects) ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION (and ED_HIGHER for subobjects) );
 *
 * @param fibObject the Fib object to test
 * @param liAllVariables a list with all variables to check
 * @param setCorrectUsedVariables the correct used variables for the Fib object
 * @param liCorrectDefinedVariables the correct defined variables for the Fib object
 * @param direction the direction in wich to check the variables
 * @return the number of erros occured in the test
 */
int checkVariables( cFibElement & fibObject,
		list< cFibVariable* > liAllVariables,
		set< cFibVariable* > setCorrectUsedVariables,
		list< cFibVariable* > liCorrectDefinedVariables,
		edDirection direction=ED_POSITION ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	string szDirectionName;
	switch ( direction ){
		case ED_POSITION:
			szDirectionName = "ED_POSITION";
		break;
		case ED_BELOW_EQUAL:
			szDirectionName = "ED_BELOW_EQUAL";
		break;
		case ED_BELOW:
			szDirectionName = "ED_BELOW";
		break;
		case ED_HIGHER_EQUAL:
			szDirectionName = "ED_HIGHER_EQUAL";
		break;
		case ED_HIGHER:
			szDirectionName = "ED_HIGHER";
		break;
		case ED_ALL:
			szDirectionName = "ED_ALL";
		break;
	}
	
	//check getUsedVariables() method
	cout<<"setUsedVariables = fibObject.getUsedVariables( "<<szDirectionName<<" ); "<<endl;
	set< cFibVariable * > setUsedVariables =
		fibObject.getUsedVariables( direction );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used / output values wher given back. "<<endl;
	}else{
		cerr<<"Error: The used / output values given back are wrong. "<<endl;
		iReturn++;
	}
	//for all setCorrectUsedVariables check isUsedVariable()
	//check used variables
	for ( list< cFibVariable * >::const_iterator
			itrVariable = liAllVariables.begin();
			itrVariable != liAllVariables.end(); itrVariable++ ){
	
		//check the isUsedVariable() methode from cExtSubobject
		if ( setCorrectUsedVariables.find( *itrVariable ) !=
				setCorrectUsedVariables.end() ){
			//variables used
			cout<<"fibObject.isUsedVariable( "<<(*itrVariable)<<", "<<szDirectionName<<" )"<<endl;
			if ( ! fibObject.isUsedVariable( *itrVariable, direction ) ){
				cerr<<"Error: The variable "<<(*itrVariable)<<
					" is given back as not used in the Fib element, but it should be. "<<endl;
				iReturn++;
			}
		}else{//variables not used
			cout<<"fibObject.isUsedVariable( "<<(*itrVariable)<<", "<<szDirectionName<<" )"<<endl;
			if ( fibObject.isUsedVariable( *itrVariable, direction ) ){
				cerr<<"Error: The variable "<<(*itrVariable)<<
					" is given back as used in the Fib element, but it shouldn't be. "<<endl;
				iReturn++;
			}
		}
	}
	
	//check getDefinedVariables() method
	cout<<"liDefinedVariables = fibObject.getDefinedVariables( "<<szDirectionName<<" ); "<<endl;
	list< cFibVariable * > liDefinedVariables =
		fibObject.getDefinedVariables( direction );
	if ( liDefinedVariables == liCorrectDefinedVariables ){
	
		cout<<"The correct defined / output values wher given back. "<<endl;
	}else{
		cerr<<"Error: The defined / output values given back are wrong"<<
			" (given back are "<<liDefinedVariables.size()<<
			", but it should be "<<liCorrectDefinedVariables.size()<<"). "<<endl;
		cerr<<      "   Given Back: ";
		for ( list< cFibVariable * >::const_iterator
				itrOutVar = liDefinedVariables.begin();
				itrOutVar != liDefinedVariables.end(); itrOutVar++ ){
			
			cerr<<(*itrOutVar)<<"; ";
		}
		cerr<<endl<<"   Correct   : ";
		for ( list< cFibVariable * >::const_iterator
				itrOutVar = liCorrectDefinedVariables.begin();
				itrOutVar != liCorrectDefinedVariables.end(); itrOutVar++ ){
			
			cerr<<(*itrOutVar)<<"; ";
		}
		cerr<<endl;
		iReturn++;
	}
	//for all liCorrectDefinedVariables check isDefinedVariable()
	//check defined variables
	for ( list< cFibVariable * >::const_iterator
			itrVariable = liAllVariables.begin();
			itrVariable != liAllVariables.end(); itrVariable++ ){
	
		//check the isDefinedVariable() methode from cExtSubobject
		if ( find( liCorrectDefinedVariables.begin(),
					liCorrectDefinedVariables.end(), *itrVariable ) !=
				liCorrectDefinedVariables.end() ){
			//variables defined
			cout<<"fibObject.isDefinedVariable( "<<(*itrVariable)<<", "<<szDirectionName<<" )"<<endl;
			if ( ! fibObject.isDefinedVariable( *itrVariable, direction ) ){
				cerr<<"Error: The variable "<<(*itrVariable)<<
					" is given back as not defined in the Fib element, but it should be. "<<endl;
				iReturn++;
			}
		}else{//variables not defined
			cout<<"fibObject.isDefinedVariable( "<<(*itrVariable)<<", "<<szDirectionName<<" )"<<endl;
			if ( fibObject.isDefinedVariable( *itrVariable, direction ) ){
				cerr<<"Error: The variable "<<(*itrVariable)<<
					" is given back as defined in the Fib element, but it shouldn't be. "<<endl;
				iReturn++;
			}
		}
	}
	
	return iReturn;
}


/**
 * This method tests the variable methods of the cExtSubobject class.
 *
 * methods tested:
 * 	- bool isUsedVariable( const cFibVariable *variable, edDirection direction=ED_POSITION ) const;
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION and ED_BELOW_EQUAL and ED_HIGHER_EQUAL );
 * 	- cFibVariable * getDefinedVariable();
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION (and ED_HIGHER for subobjects) ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION (and ED_HIGHER for subobjects) );
 * 	- bool setInputVariable( const unsignedIntFib uiNumberOfInputVariable, cFibVariable * pInputVariable );
 * 	- bool setNumberOfInputVariables( const unsignedIntFib uiNumberOfSubobject, const unsignedIntFib uiNumberOfVariables );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testVariable( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the variable methods"<<endl;

	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	cout<<"rootSimple1.setNumberOfInputVariables( 10 );"<<endl;
	rootSimple1.setNumberOfInputVariables( 10 );
	cFibVariable * pVariable1 = rootSimple1.getInputVariable( 1 );
	cout<<"pVariable1(="<<pVariable1<<" = rootSimple1.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable2 = rootSimple1.getInputVariable( 2 );
	cout<<"pVariable2(="<<pVariable2<<" = rootSimple1.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable3 = rootSimple1.getInputVariable( 3 );
	cout<<"pVariable3(="<<pVariable3<<" = rootSimple1.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable4 = rootSimple1.getInputVariable( 4 );
	cout<<"pVariable4(="<<pVariable4<<" = rootSimple1.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable5 = rootSimple1.getInputVariable( 5 );
	cout<<"pVariable5(="<<pVariable5<<" = rootSimple1.getInputVariable( 5 );"<<endl;
	cFibVariable * pVariable6 = rootSimple1.getInputVariable( 6 );
	cout<<"pVariable6(="<<pVariable6<<") = rootSimple1.getInputVariable( 6 );"<<endl;
	list< cFibVariable * > liAllVariables;
	liAllVariables.push_back( pVariable1 );
	liAllVariables.push_back( pVariable2 );
	liAllVariables.push_back( pVariable3 );
	liAllVariables.push_back( pVariable4 );
	liAllVariables.push_back( pVariable5 );
	liAllVariables.push_back( pVariable6 );

#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cExtSubobject extObject1( 1, 5 );"<<endl;
	cExtSubobject extObject1( 1, 5 );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"cExtSubobject extObject1( 1 );"<<endl;
	cExtSubobject extObject1( 1 );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	set< cFibVariable * > setCorrectUsedVariables;
	list< cFibVariable * > liCorrectDefinedVariables;
	
	cout<<endl<<"Checking Variables of the external subobject element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );


	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the variable methods with input / used variables"<<endl;

#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"extObject1.getOutputVector()->setVariable( 1, pVariable4 );"<<endl;
	extObject1.getOutputVector()->setVariable( 1, pVariable4 );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"extObject1.setOutputVariable( 1, pVariable4 );"<<endl;
	extObject1.setOutputVariable( 1, pVariable4 );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	setCorrectUsedVariables.insert( pVariable4 );
	
	cout<<endl<<"Checking Variables of the external subobject element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"extObject1.getOutputVector()->setVariable( 2, pVariable1 );"<<endl;
	extObject1.getOutputVector()->setVariable( 2, pVariable1 );
	cout<<"extObject1.getOutputVector()->setVariable( 3, pVariable4 );"<<endl;
	extObject1.getOutputVector()->setVariable( 3, pVariable4 );
	cout<<"extObject1.getOutputVector()->setVariable( 4, pVariable6 );"<<endl;
	extObject1.getOutputVector()->setVariable( 4, pVariable6 );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<endl<<"extObject1.setOutputVariable( 2, pVariable1 );"<<endl;
	extObject1.setOutputVariable( 2, pVariable1 );
	cout<<"extObject1.setOutputVariable( 3, pVariable4 );"<<endl;
	extObject1.setOutputVariable( 3, pVariable4 );
	cout<<"extObject1.setOutputVariable( 4, pVariable6 );"<<endl;
	extObject1.setOutputVariable( 4, pVariable6 );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	setCorrectUsedVariables.insert( pVariable1 );
	setCorrectUsedVariables.insert( pVariable6 );

	cout<<endl<<"Checking Variables of the external subobject element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );
	
#ifdef FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<"extObject1.getOutputVector()->setVariable( 2, pVariable3 );"<<endl;
	extObject1.getOutputVector()->setVariable( 2, pVariable3 );
#else //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	cout<<endl<<"extObject1.setOutputVariable( 2, pVariable3 );"<<endl;
	extObject1.setOutputVariable( 2, pVariable3 );
#endif //FEATURE_EXT_SUBOBJECT_INPUT_VECTOR
	
	setCorrectUsedVariables.erase( pVariable1 );
	setCorrectUsedVariables.insert( pVariable3 );

	cout<<endl<<"Checking Variables of the external subobject element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );

	
	ulTestphase++;
	cout<<endl<<"TESTPHASE "<<ulTestphase<<" : Testing the replaceVariable() method"<<endl;

	cout<<endl<<"extObject1.replaceVariable( pVariable3, pVariable1 );"<<endl;
	extObject1.replaceVariable( pVariable3, pVariable1 );
	
	setCorrectUsedVariables.erase( pVariable3 );
	setCorrectUsedVariables.insert( pVariable1 );
	//used variables: 1, 2, 4, 5, 6
	
	cout<<endl<<"Checking Variables of the external subobject element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );
	

	cout<<endl<<"extObject1.replaceVariable( pVariable3, pVariable1 );"<<endl;
	extObject1.replaceVariable( pVariable3, pVariable1 );
	//used variables: 1, 2, 4, 5, 6
	
	cout<<endl<<"Checking Variables of the external subobject element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );
	

	cout<<endl<<"extObject1.replaceVariable( pVariable1, pVariable1 );"<<endl;
	extObject1.replaceVariable( pVariable1, pVariable1 );
	//used variables: 1, 2, 4, 5, 6
	
	cout<<endl<<"Checking Variables of the external subobject element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );
	

	cout<<endl<<endl<<"extObject1.replaceVariable( pVariable4, pVariable3 );"<<endl;
	extObject1.replaceVariable( pVariable4, pVariable3 );
	
	setCorrectUsedVariables.erase( pVariable4 );
	setCorrectUsedVariables.insert( pVariable3 );
	//used variables: 1, 2, 5, 6
	
	cout<<endl<<"Checking Variables of the external subobject element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );
	
	
	return iReturn;
}













