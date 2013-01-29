/**
 * @file tExtObject
 * file name: tExtObject.cpp
 * @author Betti Oesterholz
 * @date 24.08.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cExtObject.
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
 * This file contains the test for the class cExtObject, which
 * represents an external object element.
 *
 *
 * What's tested of class cExtObject:
 * 	- cExtObject( const longFib lInIdentifier, const cVectorExtObject & vecInInputValues, cFibElement * pInSuperiorElement = NULL );
 * 	- cExtObject( const longFib lInIdentifier, const unsignedIntFib uiNumberOfInputValues=0, cFibElement * pInSuperiorElement = NULL );
 * 	- cExtObject( const cExtObject & extObjElement );
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
 * 	- cExtObject *copy( const unsignedIntFib iObjectExtObject=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementExtObject=0 ) const;
 * 	- bool storeXml( ostream &stream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream &stream ) const;
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
 * 	- longFib getIdentifier() const;
 * 	- void setIdentifier( const longFib lInIdentifier );
 * 	- cVectorExtObject * getInputVector();
 * 	- const cVectorExtObject * getInputVector() const;
 * 	- unsignedIntFib getNumberOfInputValues() const;
 * 	- void setNumberOfInputValues( const unsignedIntFib uiNumberOfInputValues );
 * 	- unsignedIntFib getNumberOfSubobjects() const;
 * 	- void setNumberOfSubobjects( const unsignedIntFib uiNumberOfSubobjects, bool bDeleteOld=true );
 * 	- cFibElement * getSubobject( const unsignedIntFib uiNumberSubobject );
 * 	- bool setSubobject( const unsignedIntFib uiNumberSubobject, cFibElement* pFibObject, bool bDeleteOld=true );
 * 	- unsignedIntFib getNumberOfOutputVariables( const unsignedIntFib uiNumberOfSubobject ) const;
 * 	- bool setNumberOfOutputVariables( const unsignedIntFib uiNumberOfSubobject, const unsignedIntFib uiNumberOfVariables );
 * 	- vector< cFibVariable* > getOutputVariables( const unsignedIntFib uiNumberOfSubobject );
 * 	- cFibVariable * getOutputVariable( const unsignedIntFib uiNumberOfSubobject, const unsignedIntFib uiNumberOfOutputVariable );
 * 	- bool addSubobject( cFibElement * pSubobject, unsignedIntFib uiPosition = 0, const unsignedIntFib uiNumberOfOutVar = 0 );
 * 	- bool deleteSubobject( unsignedIntFib uiSubobjectNumber, bool bDeleteOld=true );
 *
 *
 * call: tExtObject [MAX_RAND_TEST_SIZE]
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
24.08.2011  Oesterholz  created
10.11.2011  Oesterholz  Bugfix: evalueObject() don't overwrite properties
24.01.2012  Oesterholz  input values changed to input vector
09.10.2012  Oesterholz  Warning removed: "(char)" for char arrays added
28.01.2013  Oesterholz  COLOR_SW changed to COLOR_GRAYSCALE;
   FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS added
*/

#include "version.h"

#include "cExtObject.h"
#include "cPoint.h"
#include "cRoot.h"
#include "cProperty.h"
#include "cArea.h"
#include "cList.h"
#include "cVectorArea.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainNaturalNumber.h"
#include "cDomainVector.h"
#include "cTypeVariable.h"
#include "cTypeExtObject.h"
#include "cTypeExtObjectInput.h"
#include "cTypeUnderFunction.h"
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
int testIdentifier( unsigned long &ulTestphase );
int testInputValues( unsigned long &ulTestphase );
int testSubobjects( unsigned long &ulTestphase );
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
	
	cout<<endl<<"Running Test for cExtObject methods"<<endl;
	cout<<      "==================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testEvalueObject( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testIdentifier( ulTestphase );
	iReturn += testInputValues( ulTestphase );
	iReturn += testSubobjects( ulTestphase );
	iReturn += testVariable( ulTestphase );

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the constructor of the cExtObject class.
 *
 * methods tested:
 * 	- cExtObject( const longFib lInIdentifier, const cVectorExtObject & vecInInputValues, cFibElement * pInSuperiorElement = NULL );
 * 	- cExtObject( const longFib lInIdentifier, const unsignedIntFib uiNumberOfInputValues=0, cFibElement * pInSuperiorElement = NULL );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- unsignedIntFib getNumberOfElement()
 * 	- bool hasUnderAllObjects() const;
 * 	- longFib getIdentifier() const;
 * 	- unsignedIntFib getNumberOfInputValues() const;
 * 	- vector< cFibVariable* > getInputVector();
 * 	- unsignedIntFib getNumberOfSubobjects() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cExtObject"<<endl;

	cout<<"cExtObject extObjectSimple( 0 );"<<endl;
	cExtObject extObjectSimple( 0 );

	cVectorExtObject vecCorrectInValiables( 0 );

	//check the getType() methode from cExtObject
	if ( extObjectSimple.getType() == 'o' ){
	
		cout<<"The type of the external object element is correctly 'o' . "<<endl;
	}else{
		cerr<<"Error: The type of the external object element is "<<
			extObjectSimple.getType()<<" but should be 'o' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cExtObject
	if ( extObjectSimple.isValidFibElement() ){
	
		cout<<"The external object element is correctly a correct external object element. "<<endl;
	}else{
		cerr<<"Error: The external object element is not a correct external object element, but should be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cExtObject
	if ( ! extObjectSimple.isMovable() ){
	
		cout<<"The external object element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The external object element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cExtObject
	if ( extObjectSimple.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib-element for the external object element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-element for the external object element is "<<
			extObjectSimple.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cExtObject
	if ( extObjectSimple.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib-element for the external object element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib-element for the external object element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cExtObject
	if ( extObjectSimple.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib-element for the external object element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-element for the external object element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cExtObject
	if ( extObjectSimple.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib-element for the external object element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-element for the external object element is "<<
			extObjectSimple.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getIdentifier() methode from cExtObject
	if ( extObjectSimple.getIdentifier() == 0 ){
	
		cout<<"The identifier for the external object element is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The identifier for the external object element is not 0, but "<<
			extObjectSimple.getIdentifier()<<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfInputValues() methode from cExtObject
	if ( extObjectSimple.getNumberOfInputValues() == 0 ){
	
		cout<<"The number of input variables for the external object element is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of input variables for the external object element is not 0, but "<<
			extObjectSimple.getNumberOfInputValues()<<" ."<<endl;
		iReturn++;
	}
	//check the getInputVector() methode from cExtObject
	if ( *(extObjectSimple.getInputVector()) == vecCorrectInValiables ){
	
		cout<<"The external object element has the correct input variables . "<<endl;
	}else{
		cerr<<"Error: The external object element has not the correct input variables ."<<endl;
		iReturn++;
	}
	if ( extObjectSimple.getNumberOfSubobjects() == 0 ){
	
		cout<<"The number of subobjects for the external object element is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of subobjects for the external object element is not 0, but "<<
			extObjectSimple.getNumberOfSubobjects()<<" ."<<endl;
		iReturn++;
	}

	//check the hasUnderAllObjects() methode from cExtObject
	if ( extObjectSimple.hasUnderAllObjects()){
	
		cout<<"The external object element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The external object element is missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cExtObject with input variables given"<<endl;

	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	cout<<"root.setNumberOfInputVariables( 10 );"<<endl;
	root.setNumberOfInputVariables( 10 );
	
	cVectorExtObject vecVariables( 4 );
	cout<<"vecVariables.setVariable( 1, root.getInputVariable( 7 ) )"<<endl;
	vecVariables.setVariable( 1, root.getInputVariable( 7 ) );
	cout<<"vecVariables.setVariable( 2, root.getInputVariable( 3 ) )"<<endl;
	vecVariables.setVariable( 2, root.getInputVariable( 3 ) );
	cout<<"vecVariables.setValue( 3, -4 )"<<endl;
	vecVariables.setValue( 3, -4 );
	cout<<"vecVariables.setVariable( 4, root.getInputVariable( 3 ) )"<<endl;
	vecVariables.setVariable( 4, root.getInputVariable( 3 ) );
	
	vecCorrectInValiables = vecVariables;
	
	cout<<"cExtObject extObjectInVal( 21, vecVariables );"<<endl;
	cExtObject extObjectInVal( 21, vecVariables );
	
	//check the getType() methode from cExtObject
	if ( extObjectInVal.getType() == 'o' ){
	
		cout<<"The type of the external object element is correctly 'o' . "<<endl;
	}else{
		cerr<<"Error: The type of the external object element is "<<
			extObjectInVal.getType()<<" but should be 'o' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cExtObject
	if ( extObjectInVal.isValidFibElement() ){
	
		cout<<"The external object element is correctly a correct external object element. "<<endl;
	}else{
		cerr<<"Error: The external object element is not a correct external object element, but should be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cExtObject
	if ( ! extObjectInVal.isMovable() ){
	
		cout<<"The external object element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The external object element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cExtObject
	if ( extObjectInVal.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib-element for the external object element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-element for the external object element is "<<
			extObjectInVal.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cExtObject
	if ( extObjectInVal.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib-element for the external object element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib-element for the external object element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cExtObject
	if ( extObjectInVal.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib-element for the external object element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-element for the external object element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cExtObject
	if ( extObjectInVal.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib-element for the external object element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-element for the external object element is "<<
			extObjectInVal.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getIdentifier() methode from cExtObject
	if ( extObjectInVal.getIdentifier() == 21 ){
	
		cout<<"The identifier for the external object element is correctly 21 . "<<endl;
	}else{
		cerr<<"Error: The identifier for the external object element is not 21, but "<<
			extObjectInVal.getIdentifier()<<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfInputValues() methode from cExtObject
	if ( extObjectInVal.getNumberOfInputValues() == 4 ){
	
		cout<<"The number of input variables for the external object element is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of input variables for the external object element is not 4, but "<<
			extObjectInVal.getNumberOfInputValues()<<" ."<<endl;
		iReturn++;
	}
	//check the getInputVector() methode from cExtObject
	if ( *(extObjectInVal.getInputVector()) == vecCorrectInValiables ){
	
		cout<<"The external object element has the correct input variables . "<<endl;
	}else{
		cerr<<"Error: The external object element has not the correct input variables ."<<endl;
		iReturn++;
	}
	if ( extObjectInVal.getNumberOfSubobjects() == 0 ){
	
		cout<<"The number of subobjects for the external object element is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of subobjects for the external object element is not 0, but "<<
			extObjectInVal.getNumberOfSubobjects()<<" ."<<endl;
		iReturn++;
	}

	//check the hasUnderAllObjects() methode from cExtObject
	if ( extObjectInVal.hasUnderAllObjects()){
	
		cout<<"The external object element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The external object element is missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cExtObject with all parameters given"<<endl;

	vecVariables.resize( 3 );
	cout<<"vecVariables.setValue( 1, 3 )"<<endl;
	vecVariables.setValue( 1, 3 );
	cout<<"vecVariables.setVariable( 2, root.getInputVariable( 3 ) )"<<endl;
	vecVariables.setVariable( 2, root.getInputVariable( 3 ) );
	cout<<"vecVariables.setValue( 3, -7.3 )"<<endl;
	vecVariables.setValue( 3, -7.3 );
	
	vecCorrectInValiables = vecVariables;
	
	cout<<"cExtObject extObjectFull( -16, vecVariables, &root );"<<endl;
	cExtObject extObjectFull( -16, vecVariables, &root );
	
	//check the getType() methode from cExtObject
	if ( extObjectFull.getType() == 'o' ){
	
		cout<<"The type of the external object element is correctly 'o' . "<<endl;
	}else{
		cerr<<"Error: The type of the external object element is "<<
			extObjectFull.getType()<<" but should be 'o' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cExtObject
	if ( extObjectFull.isValidFibElement() ){
	
		cout<<"The external object element is correctly a correct external object element. "<<endl;
	}else{
		cerr<<"Error: The external object element is not a correct external object element, but should be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cExtObject
	if ( ! extObjectFull.isMovable() ){
	
		cout<<"The external object element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The external object element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cExtObject
	if ( extObjectFull.getNumberOfElement() == 2 ){
	
		cout<<"The number of the Fib-element for the external object element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-element for the external object element is "<<
			extObjectFull.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cExtObject
	if ( extObjectFull.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib-element for the external object element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib-element for the external object element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cExtObject
	if ( extObjectFull.getFibElement( -1 ) == &root ){
	
		cout<<"The previous Fib-element for the external object element is correctly root. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-element for the external object element is not root."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cExtObject
	if ( extObjectFull.getSuperiorFibElement() == &root ){
	
		cout<<"The superior Fib-element for the external object element is correctly root. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-element for the external object element is "<<
			extObjectFull.getSuperiorFibElement() << " and not root."<<endl;
		iReturn++;
	}
	//check the getIdentifier() methode from cExtObject
	if ( extObjectFull.getIdentifier() == -16 ){
	
		cout<<"The identifier for the external object element is correctly -16 . "<<endl;
	}else{
		cerr<<"Error: The identifier for the external object element is not -16, but "<<
			extObjectFull.getIdentifier()<<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfInputValues() methode from cExtObject
	if ( extObjectFull.getNumberOfInputValues() == 3 ){
	
		cout<<"The number of input variables for the external object element is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of input variables for the external object element is not 3, but "<<
			extObjectFull.getNumberOfInputValues()<<" ."<<endl;
		iReturn++;
	}
	//check the getInputVector() methode from cExtObject
	if ( *(extObjectFull.getInputVector()) == vecCorrectInValiables ){
	
		cout<<"The external object element has the correct input variables . "<<endl;
	}else{
		cerr<<"Error: The external object element has not the correct input variables ."<<endl;
		iReturn++;
	}
	if ( extObjectFull.getNumberOfSubobjects() == 0 ){
	
		cout<<"The number of subobjects for the external object element is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of subobjects for the external object element is not 0, but "<<
			extObjectFull.getNumberOfSubobjects()<<" ."<<endl;
		iReturn++;
	}

	//check the hasUnderAllObjects() methode from cExtObject
	if ( extObjectFull.hasUnderAllObjects()){
	
		cout<<"The external object element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The external object element is missing a underobject."<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing cExtObject with given input variables number"<<endl;

	vecCorrectInValiables.resize( 0 );
	vecCorrectInValiables.resize( 7 );
	
	cout<<"cExtObject extObjectInVal7( -14, 7 );"<<endl;
	cExtObject extObjectInVal7( -14, 7 );
	
	//check the getType() methode from cExtObject
	if ( extObjectInVal7.getType() == 'o' ){
	
		cout<<"The type of the external object element is correctly 'o' . "<<endl;
	}else{
		cerr<<"Error: The type of the external object element is "<<
			extObjectInVal7.getType()<<" but should be 'o' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cExtObject
	if ( extObjectInVal7.isValidFibElement() ){
	
		cout<<"The external object element is correctly a correct external object element. "<<endl;
	}else{
		cerr<<"Error: The external object element is not a correct external object element, but should be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cExtObject
	if ( ! extObjectInVal7.isMovable() ){
	
		cout<<"The external object element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The external object element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cExtObject
	if ( extObjectInVal7.getNumberOfElement() == 1 ){
	
		cout<<"The number of the Fib-element for the external object element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the Fib-element for the external object element is "<<
			extObjectInVal7.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cExtObject
	if ( extObjectInVal7.getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib-element for the external object element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main Fib-element for the external object element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cExtObject
	if ( extObjectInVal7.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib-element for the external object element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-element for the external object element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cExtObject
	if ( extObjectInVal7.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib-element for the external object element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-element for the external object element is "<<
			extObjectInVal7.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getIdentifier() methode from cExtObject
	if ( extObjectInVal7.getIdentifier() == -14 ){
	
		cout<<"The identifier for the external object element is correctly -14 . "<<endl;
	}else{
		cerr<<"Error: The identifier for the external object element is not -14, but "<<
			extObjectInVal7.getIdentifier()<<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfInputValues() methode from cExtObject
	if ( extObjectInVal7.getNumberOfInputValues() == 7 ){
	
		cout<<"The number of input variables for the external object element is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of input variables for the external object element is not 4, but "<<
			extObjectInVal7.getNumberOfInputValues()<<" ."<<endl;
		iReturn++;
	}
	//check the getInputVector() methode from cExtObject
	if ( *(extObjectInVal7.getInputVector()) == vecCorrectInValiables ){
	
		cout<<"The external object element has the correct input variables . "<<endl;
	}else{
		cerr<<"Error: The external object element has not the correct input variables ."<<endl;
		iReturn++;
	}
	if ( extObjectInVal7.getNumberOfSubobjects() == 0 ){
	
		cout<<"The number of subobjects for the external object element is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of subobjects for the external object element is not 0, but "<<
			extObjectInVal7.getNumberOfSubobjects()<<" ."<<endl;
		iReturn++;
	}

	//check the hasUnderAllObjects() methode from cExtObject
	if ( extObjectInVal7.hasUnderAllObjects()){
	
		cout<<"The external object element has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The external object element is missing a underobject."<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cExtSubobject"<<endl;

	cout<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );

	cout<<"cPoint point( &vecPositionE2 );"<<endl;
	cPoint point( &vecPositionE2 );
	
	cout<<"cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );"<<endl;
	cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );
	
	cout<<"cProperty property( vecPropertyColorSW, &point );"<<endl;
	cProperty property( vecPropertyColorSW, &point );
	
	cout<<"cExtObject extObject1( 1 );"<<endl;
	cExtObject extObject1( 1 );

	cout<<"cRoot root( &extObject1 );"<<endl;
	cRoot root( &extObject1 );
	
	cout<<"cRoot subroot( &property );"<<endl;
	cRoot subroot( &property );
	
	cout<<"root.addSubRootObject( 1, &subroot );"<<endl;
	root.addSubRootObject( 1, &subroot );
	
	cout<<"point.getPosition()->setValue( 1, 1 );"<<endl;
	point.getPosition()->setValue( 1, 1 );
	cout<<"property.getProperty()->setValue( 1, 1 );"<<endl;
	property.getProperty()->setValue( 1, 1 );
	
	unsigned int uiPointsToEvalue = 1;
	
	unsigned int uiTimeNeeded = 5 + 3 + (2 + 3);

	//check the getTimeNeed() methode from cExtObject
	cout<<"extObject1.getTimeNeed()"<<endl;
	if ( extObject1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			extObject1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cExtObject
	cout<<"extObject1.getTimeNeed( 4 )"<<endl;
	if ( extObject1.getTimeNeed( 4 ) == 4 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 4 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			extObject1.getTimeNeed( 4 ) <<", but should be "<< 4 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"list<cVectorProperty> liVecProperties;"<<endl;
	list<cVectorProperty> liVecProperties;
	
	//generate to evalue data
	list< pair< const cVectorPosition*, list<cVectorProperty> > > liPointsToEvalue;
	cVectorPosition vecPositionE2V1( 2 );
	vecPositionE2V1.setValue( 1, 1 );
	cVectorProperty vecPropertyColorSWV1( cTypeProperty::COLOR_GRAYSCALE );
	vecPropertyColorSWV1.setValue( 1, 1 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V1, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	
	cEvaluePositionList evaluePositionList;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"extObject1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bool bObjectEvalued = extObject1.evalueObject( evaluePositionList, 0,  liVecProperties );

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
	cout<<"extObject1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = extObject1.evalueObjectSimple( evaluePositionList );

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
	liFibElementsToEvalue.push_back( make_pair( &point, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	cout<<"extObject1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = extObject1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<"extObject1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = extObject1.evalueObjectSimple( evalueFibElementList );

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cExtObject with a global property list given"<<endl;
	
	cout<<"cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );
	
	list< pair< const cVectorPosition*, list<cVectorProperty> > >::iterator
		itrPositionProperties = liPointsToEvalue.begin();
	itrPositionProperties->second.push_back( vecPropertyLayer );
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"extObject1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = extObject1.evalueObject( evaluePositionList, 0,  liVecProperties );

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

	cout<<"extObject1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = extObject1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cExtObject for non existing object point 1"<<endl;
	
	uiPointsToEvalue = 0;
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"extObject1.evalueObject( evaluePositionList, 4,  liVecProperties );"<<endl;
	bObjectEvalued = extObject1.evalueObject( evaluePositionList, 4,  liVecProperties );

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
	cout<<"extObject1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = extObject1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cExtObject when returnvalue is false"<<endl;

	uiPointsToEvalue = 1;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	cout<<"extObject1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = extObject1.evalueObject( evaluePositionList, 0,  liVecProperties );

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
	cout<<"extObject1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = extObject1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cExtObject with differnt elements to evalue"<<endl;

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
			make_pair( &property, list<cVectorProperty>() ) );
	}
	cout<<"extObject1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = extObject1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<"liCFibElementTyps.push_back( 'o' );"<<endl;
	liCFibElementTyps.push_back( 'o' );
	uiPointsToEvalue = 1;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &extObject1, list<cVectorProperty>() ) );
	cout<<"extObject1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = extObject1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<"liCFibElementTyps.push_back( 'o' );"<<endl;
	liCFibElementTyps.push_back( 'o' );
	cout<<"liCFibElementTyps.push_back( 'm' );"<<endl;
	liCFibElementTyps.push_back( 'm' );
	uiPointsToEvalue = 1;
	cout<<"extObject1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = extObject1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cExtObject if external object for identifier do not exists"<<endl;
	
	cout<<"root.deleteSubRootObject( 1, false );"<<endl;
	root.deleteSubRootObject( 1, false );
	
	uiPointsToEvalue = 0;
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"extObject1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = extObject1.evalueObject( evaluePositionList, 0,  liVecProperties );

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
	cout<<"extObject1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = extObject1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cExtObject with input variables given"<<endl;

	cout<<"cVectorExtObject vecInInputVariables( 5 );"<<endl;
	cVectorExtObject vecInInputVariables( 5 );
	
	cout<<"cFibVariable variable1( &root );"<<endl;
	cFibVariable variable1( &root );
	cout<<"variable1.setIntegerValue( 1 );"<<endl;
	variable1.setIntegerValue( 1 );
	cout<<"vecInInputVariables.setVariable( 1, &variable1 );"<<endl;
	vecInInputVariables.setVariable( 1, &variable1 );
	
	cout<<"cFibVariable variable2( &root );"<<endl;
	cFibVariable variable2( &root );
	cout<<"variable2.setIntegerValue( 2 );"<<endl;
	variable2.setIntegerValue( 2 );
	cout<<"vecInInputVariables.setVariable( 2, &variable2 );"<<endl;
	vecInInputVariables.setVariable( 2, &variable2 );
	
	cout<<"cFibVariable variable3( &root );"<<endl;
	cFibVariable variable3( &root );
	cout<<"variable3.setIntegerValue( 3 );"<<endl;
	variable3.setIntegerValue( 3 );
	cout<<"vecInInputVariables.setVariable( 3, &variable3 );"<<endl;
	vecInInputVariables.setVariable( 3, &variable3 );

	cout<<"cExtObject extObject2( 7, vecInInputVariables );"<<endl;
	cExtObject extObject2( 7, vecInInputVariables );

	cout<<"cRoot root2( &extObject2 );"<<endl;
	cRoot root2( &extObject2 );
	
	cout<<"cPoint point2( &vecPositionE2 );"<<endl;
	cPoint point2( &vecPositionE2 );
	
	cout<<"cVectorProperty vecPropertyColorSW1( cTypeProperty::COLOR_GRAYSCALE );"<<endl;
	cVectorProperty vecPropertyColorSW1( cTypeProperty::COLOR_GRAYSCALE );
	
	cout<<"cProperty property2( vecPropertyColorSW1, &point2 );"<<endl;
	cProperty property2( vecPropertyColorSW1, &point2 );
	
	cout<<"cVectorArea vecArea;"<<endl;
	cVectorArea vecArea;
	
	cout<<"cArea area2( vecArea, &property2 );"<<endl;
	cArea area2( vecArea, &property2 );
	
	cout<<"cRoot subroot2( &area2 );"<<endl;
	cRoot subroot2( &area2 );
	
	cout<<"subroot2.setNumberOfInputVariables( 3 )"<<endl;
	subroot2.setNumberOfInputVariables( 3 );
	
	cout<<"root2.addSubRootObject( 1, &subroot );"<<endl;
	root2.addSubRootObject( 1, &subroot );
	
	cout<<"root2.addSubRootObject( 7, &subroot2 );"<<endl;
	root2.addSubRootObject( 7, &subroot2 );
	
	cout<<"point2.getPosition()->setVariable( 1, &variable1 );"<<endl;
	point2.getPosition()->setVariable( 1, &variable1 );
	cout<<"point2.getPosition()->setVariable( 2, area2.getDefinedVariable() );"<<endl;
	point2.getPosition()->setVariable( 2, area2.getDefinedVariable() );
	cout<<"property2.getProperty()->setVariable( 1, &variable3 );"<<endl;
	property2.getProperty()->setVariable( 1, &variable3 );
	
	cout<<"area2.getSubarea()->setVariable( 1, &variable1 );"<<endl;
	area2.getSubarea()->setVariable( 1, &variable1 );
	cout<<"area2.getSubarea()->setVariable( 2, &variable2 );"<<endl;
	area2.getSubarea()->setVariable( 2, &variable2 );
	
	uiPointsToEvalue = 2;
	
	uiTimeNeeded = 5 + 3 + (1 + 2 * (2 + 3));

	//check the getTimeNeed() methode from cExtObject
	cout<<"extObject2.getTimeNeed()"<<endl;
	if ( extObject2.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			extObject2.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cExtObject
	cout<<"extObject2.getTimeNeed( 7 )"<<endl;
	if ( extObject2.getTimeNeed( 7 ) == 7 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 7 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			extObject2.getTimeNeed( 7 ) <<", but should be "<< 7 <<" . "<<endl;
		iReturn++;
	}
	
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liPointsToEvalue.clear();"<<endl;
	liPointsToEvalue.clear();
	
	//generate to evalue data
	cVectorPosition vecPositionE2V1V1( 2 );
	vecPositionE2V1V1.setValue( 1, 1 );
	vecPositionE2V1V1.setValue( 2, 1 );
	cVectorPosition vecPositionE2V1V2( 2 );
	vecPositionE2V1V2.setValue( 1, 1 );
	vecPositionE2V1V2.setValue( 2, 2 );
	cVectorProperty vecPropertyColorSW1V3( cTypeProperty::COLOR_GRAYSCALE );
	vecPropertyColorSW1V3.setValue( 1, 3 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V1V1, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSW1V3 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V1V2, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSW1V3 );
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"extObject2.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = extObject2.evalueObject( evaluePositionList, 0,  liVecProperties );

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
	cout<<"extObject2.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = extObject2.evalueObjectSimple( evaluePositionList );

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
	
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &point2, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSW1V3 );
	liFibElementsToEvalue.push_back( make_pair( &point2, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSW1V3 );
	cout<<"extObject2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = extObject2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	cout<<"extObject2.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = extObject2.evalueObjectSimple( evalueFibElementList );

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cExtObject with a global property list given"<<endl;
	
	itrPositionProperties = liPointsToEvalue.begin();
	itrPositionProperties->second.push_back( vecPropertyLayer );
	itrPositionProperties++;
	itrPositionProperties->second.push_back( vecPropertyLayer );
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"extObject2.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = extObject2.evalueObject( evaluePositionList, 0,  liVecProperties );

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

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	itrElementProperties = liFibElementsToEvalue.begin();
	itrElementProperties->second.push_back( vecPropertyLayer );
	itrElementProperties++;
	itrElementProperties->second.push_back( vecPropertyLayer );

	cout<<"extObject2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = extObject2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

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
	

/*test with subobjects given in tExtSubobject
		- when they are used
		- when they are not used
*/

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing equal methods for external object elements"<<endl;

	cout<<endl<<"Creating external element objects to compare: "<<endl<<endl;
	
	//if with a empty
	cout<<"cExtObject extObjId0_1( 0 );"<<endl;
	cExtObject extObjId0_1( 0 );

	cout<<"cExtObject extObjId0_2( 0 );"<<endl;
	cExtObject extObjId0_2( 0) ;

	//if with an identifier not 0
	cout<<"cExtObject extObjId1_1( 1 );"<<endl;
	cExtObject extObjId1_1( 1 );

	cout<<"cExtObject extObjId32568_1( 32568 );"<<endl;
	cExtObject extObjId32568_1( 32568 );
	
	cout<<"cExtObject extObjIdm1_1( -1 );"<<endl;
	cExtObject extObjIdm1_1( -1 );


	//with one input variable
	cout<<"cRoot rootVariables;"<<flush<<endl;
	cRoot rootVariables;
	cout<<"rootVariables.setNumberOfInputVariables( 10 );"<<flush<<endl;
	rootVariables.setNumberOfInputVariables( 10 );
	
	cout<<"cVectorExtObject vecInInputVariables1( 1 );"<<flush<<endl;
	cVectorExtObject vecInInputVariables1( 1 );
	cout<<"vecInInputVariables1.setVariable( 1, rootVariables.getInputVariable( 1 ) );"<<flush<<endl;
	vecInInputVariables1.setVariable( 1, rootVariables.getInputVariable( 1 ) );
	cout<<"cExtObject extObjId0InVal1( 0, vecInInputVariables1 );"<<endl;
	cExtObject extObjId0InVal1( 0, vecInInputVariables1 );
	
	cout<<"cVectorExtObject vecInInputVariables2( 1 );"<<flush<<endl;
	cVectorExtObject vecInInputVariables2( 1 );
	cout<<"vecInInputVariables2.setVariable( 1, rootVariables.getInputVariable( 7 ) );"<<flush<<endl;
	vecInInputVariables2.setVariable( 1, rootVariables.getInputVariable( 7 ) );
	cout<<"cExtObject extObjId0InVal7( 0, vecInInputVariables2 );"<<endl;
	cExtObject extObjId0InVal7( 0, vecInInputVariables2 );
	
	//with input values
	cout<<"vecInInputVariables1.setValue( 1, 1 );"<<flush<<endl;
	vecInInputVariables1.setValue( 1, 1 );
	cout<<"cExtObject extObjId0InVal1u7( 0, vecInInputVariables1 );"<<endl;
	cExtObject extObjId0InVal1u7( 0, vecInInputVariables1 );
	
	cout<<"vecInInputVariables2.setValue( 1, -1 );"<<flush<<endl;
	vecInInputVariables2.setValue( 1, -1 );
	cout<<"cExtObject extObjId0InVal7u7( 0, vecInInputVariables2 );"<<endl;
	cExtObject extObjId0InVal7u7( 0, vecInInputVariables2 );
	
	//with tree input values
	cout<<"cVectorExtObject vecInInputVariables3( 3 );"<<flush<<endl;
	cVectorExtObject vecInInputVariables3( 3 );
	cout<<"vecInInputVariables3.setValue( 1, 1 );"<<flush<<endl;
	vecInInputVariables3.setValue( 1, 1 );
	cout<<"cExtObject extObjId0InVal1u7u5( 0, vecInInputVariables3 );"<<endl;
	cExtObject extObjId0InVal1u7u5( 0, vecInInputVariables3 );
	
	cout<<"vecInInputVariables3.setVariable( 3, rootVariables.getInputVariable( 7 ) );"<<flush<<endl;
	vecInInputVariables3.setVariable( 3, rootVariables.getInputVariable( 7 ) );
	cout<<"cExtObject extObjId0InVal1u7u4( 0, vecInInputVariables3 );"<<endl;
	cExtObject extObjId0InVal1u7u4( 0, vecInInputVariables3 );
	
	
	//with one input variable wich is NULL
	cout<<"cVectorExtObject vecInInputVariables4( 1 );"<<flush<<endl;
	cVectorExtObject vecInInputVariables4( 1 );
	cout<<"cExtObject extObjId0InVal0( 0, vecInInputVariables4 );"<<endl;
	cExtObject extObjId0InVal0( 0, vecInInputVariables4 );
	
	
	//if with superior element
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	
	cout<<"cExtObject extObjId0Sup( 0, 0, &rootSimple1 );"<<endl;
	cExtObject extObjId0Sup( 0, 0, &rootSimple1 );


	//with one subobject
	cout<<"cPoint pointSubobj1;"<<endl;
	cPoint pointSubobj1;
	cout<<"cExtObject extObjId0Sub1_1( 0 );"<<endl;
	cExtObject extObjId0Sub1_1( 0 );
	cout<<"extObjId0Sub1_1.addSubobject( &pointSubobj1 );"<<endl;
	extObjId0Sub1_1.addSubobject( &pointSubobj1 );
	
	cout<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );
	cout<<"cPoint pointSubobj2E2( &vecPositionE2 );"<<endl;
	cPoint pointSubobj2E2( &vecPositionE2 );
	cout<<"cExtObject extObjId0Sub1_2( 0 );"<<endl;
	cExtObject extObjId0Sub1_2( 0 );
	cout<<"extObjId0Sub1_2.addSubobject( &pointSubobj2E2 );"<<endl;
	extObjId0Sub1_2.addSubobject( &pointSubobj2E2 );
	
	//with one subobject with output variables
	cout<<"cPoint pointSubobj2;"<<endl;
	cPoint pointSubobj2;
	cout<<"cExtObject extObjId0Sub1ov1_1( 0 );"<<endl;
	cExtObject extObjId0Sub1ov1_1( 0 );
	cout<<"extObjId0Sub1ov1_1.addSubobject( &pointSubobj2 );"<<endl;
	extObjId0Sub1ov1_1.addSubobject( &pointSubobj2 );
	cout<<"extObjId0Sub1ov1_1.setNumberOfOutputVariables( 1, 1 );"<<endl;
	extObjId0Sub1ov1_1.setNumberOfOutputVariables( 1, 1 );
	
	cout<<"cPoint pointSubobj3;"<<endl;
	cPoint pointSubobj3;
	cout<<"cExtObject extObjId0Sub1ov3_1( 0 );"<<endl;
	cExtObject extObjId0Sub1ov3_1( 0 );
	cout<<"extObjId0Sub1ov3_1.addSubobject( &pointSubobj3 );"<<endl;
	extObjId0Sub1ov3_1.addSubobject( &pointSubobj3 );
	cout<<"extObjId0Sub1ov3_1.setNumberOfOutputVariables( 1, 3 );"<<endl;
	extObjId0Sub1ov3_1.setNumberOfOutputVariables( 1, 3 );
	
	//with two subobjects
	cout<<"cPoint pointSubobj4;"<<endl;
	cPoint pointSubobj4;
	cout<<"cPoint pointSubobj5;"<<endl;
	cPoint pointSubobj5;
	cout<<"cExtObject extObjId0Sub2_1( 0 );"<<endl;
	cExtObject extObjId0Sub2_1( 0 );
	cout<<"extObjId0Sub2_1.addSubobject( &pointSubobj4 );"<<endl;
	extObjId0Sub2_1.addSubobject( &pointSubobj4 );
	cout<<"extObjId0Sub2_1.addSubobject( &pointSubobj5 );"<<endl;
	extObjId0Sub2_1.addSubobject( &pointSubobj5 );
	
	//with tree subobjects
	cout<<"cPoint pointSubobj6;"<<endl;
	cPoint pointSubobj6;
	cout<<"cPoint pointSubobj7;"<<endl;
	cPoint pointSubobj7;
	cout<<"cPoint pointSubobj8;"<<endl;
	cPoint pointSubobj8;
	cout<<"cExtObject extObjId0Sub3_1( 0 );"<<endl;
	cExtObject extObjId0Sub3_1( 0 );
	cout<<"extObjId0Sub3_1.addSubobject( &pointSubobj6 );"<<endl;
	extObjId0Sub3_1.addSubobject( &pointSubobj6 );
	cout<<"extObjId0Sub3_1.addSubobject( &pointSubobj7 );"<<endl;
	extObjId0Sub3_1.addSubobject( &pointSubobj7 );
	cout<<"extObjId0Sub3_1.addSubobject( &pointSubobj8 );"<<endl;
	extObjId0Sub3_1.addSubobject( &pointSubobj8 );
	
	//with five subobjects
	cout<<"cPoint pointSubobj9;"<<endl;
	cPoint pointSubobj9;
	cout<<"cPoint pointSubobj10;"<<endl;
	cPoint pointSubobj10;
	cout<<"cPoint pointSubobj11;"<<endl;
	cPoint pointSubobj11;
	cout<<"cPoint pointSubobj12;"<<endl;
	cPoint pointSubobj12;
	cout<<"cPoint pointSubobj13;"<<endl;
	cPoint pointSubobj13;
	cout<<"cExtObject extObjId0Sub5_1( 0 );"<<endl;
	cExtObject extObjId0Sub5_1( 0 );
	cout<<"extObjId0Sub5_1.addSubobject( &pointSubobj9 );"<<endl;
	extObjId0Sub5_1.addSubobject( &pointSubobj9 );
	cout<<"extObjId0Sub5_1.addSubobject( &pointSubobj10 );"<<endl;
	extObjId0Sub5_1.addSubobject( &pointSubobj10 );
	cout<<"extObjId0Sub5_1.addSubobject( &pointSubobj11 );"<<endl;
	extObjId0Sub5_1.addSubobject( &pointSubobj11 );
	cout<<"extObjId0Sub5_1.addSubobject( &pointSubobj12 );"<<endl;
	extObjId0Sub5_1.addSubobject( &pointSubobj12 );
	cout<<"extObjId0Sub5_1.addSubobject( &pointSubobj13 );"<<endl;
	extObjId0Sub5_1.addSubobject( &pointSubobj13 );
	
	//with one subobject which is NULL
	cout<<"cExtObject extObjId0SubNULL_1( 0 );"<<endl;
	cExtObject extObjId0SubNULL_1( 0 );
	cout<<"extObjId0SubNULL_1.setNumberOfSubobjects( 1 );"<<endl;
	extObjId0SubNULL_1.setNumberOfSubobjects( 1 );
	
	//other Fib-object
	cout<<"cPoint point;"<<endl;
	cPoint point;

	cout<<"cPoint point1List;"<<endl;
	cPoint point1List;
	cout<<"cPoint point2List;"<<endl;
	cPoint point2List;
	cout<<"cList list( &point1List, &point2List );"<<endl;
	cList list( &point1List, &point2List );



	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with extObjId0_1
	cFibElement *pActualObject = &extObjId0_1;
	string szActualObjectName = "extObjId0_1";
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
#ifdef FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
#else //FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup", true );
#endif //FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0_2
	pActualObject = &extObjId0_2;
	szActualObjectName = "extObjId0_2";
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
#ifdef FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
#else //FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup", true );
#endif //FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId1_1
	pActualObject = &extObjId1_1;
	szActualObjectName = "extObjId1_1";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId32568_1
	pActualObject = &extObjId32568_1;
	szActualObjectName = "extObjId32568_1";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjIdm1_1
	pActualObject = &extObjIdm1_1;
	szActualObjectName = "extObjIdm1_1";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0InVal1
	pActualObject = &extObjId0InVal1;
	szActualObjectName = "extObjId0InVal1";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0InVal7
	pActualObject = &extObjId0InVal7;
	szActualObjectName = "extObjId0InVal7";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0InVal1u7
	pActualObject = &extObjId0InVal1u7;
	szActualObjectName = "extObjId0InVal1u7";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0InVal7u7
	pActualObject = &extObjId0InVal7u7;
	szActualObjectName = "extObjId0InVal7u7";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0InVal1u7u5
	pActualObject = &extObjId0InVal1u7u5;
	szActualObjectName = "extObjId0InVal1u7u5";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0InVal1u7u4
	pActualObject = &extObjId0InVal1u7u4;
	szActualObjectName = "extObjId0InVal1u7u4";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0InVal0
	pActualObject = &extObjId0InVal0;
	szActualObjectName = "extObjId0InVal0";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0Sup
	pActualObject = &extObjId0Sup;
	szActualObjectName = "extObjId0Sup";
#ifdef FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
#else //FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1", true );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2", true );
#endif //FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0Sub1_1
	pActualObject = &extObjId0Sub1_1;
	szActualObjectName = "extObjId0Sub1_1";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2", true );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1", true );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0Sub1_2
	pActualObject = &extObjId0Sub1_2;
	szActualObjectName = "extObjId0Sub1_2";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1", true );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1", true );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0Sub1ov1_1
	pActualObject = &extObjId0Sub1ov1_1;
	szActualObjectName = "extObjId0Sub1ov1_1";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0Sub1ov3_1
	pActualObject = &extObjId0Sub1ov3_1;
	szActualObjectName = "extObjId0Sub1ov3_1";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0Sub2_1
	pActualObject = &extObjId0Sub2_1;
	szActualObjectName = "extObjId0Sub2_1";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0Sub3_1
	pActualObject = &extObjId0Sub3_1;
	szActualObjectName = "extObjId0Sub3_1";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0Sub5_1
	pActualObject = &extObjId0Sub5_1;
	szActualObjectName = "extObjId0Sub5_1";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with extObjId0SubNULL_1
	pActualObject = &extObjId0SubNULL_1;
	szActualObjectName = "extObjId0SubNULL_1";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1", true );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2", true );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with point
	pActualObject = &point;
	szActualObjectName = "point";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, list, "list" );

	//compare with list
	pActualObject = &list;
	szActualObjectName = "list";
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_1, "extObjId0_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0_2, "extObjId0_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId1_1, "extObjId1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId32568_1, "extObjId32568_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjIdm1_1, "extObjIdm1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1, "extObjId0InVal1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7, "extObjId0InVal7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7, "extObjId0InVal1u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal7u7, "extObjId0InVal7u7" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u5, "extObjId0InVal1u7u5" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal1u7u4, "extObjId0InVal1u7u4" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0InVal0, "extObjId0InVal0" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sup, "extObjId0Sup" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_1, "extObjId0Sub1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1_2, "extObjId0Sub1_2" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov1_1, "extObjId0Sub1ov1_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub1ov3_1, "extObjId0Sub1ov3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub2_1, "extObjId0Sub2_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub3_1, "extObjId0Sub3_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0Sub5_1, "extObjId0Sub5_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, extObjId0SubNULL_1, "extObjId0SubNULL_1" );
	iReturn += testCompareTwoNotEqualObjects( *pActualObject, szActualObjectName, point, "point" );
	iReturn += testCompareTwoEqualObjects( *pActualObject, szActualObjectName, list, "list" );



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
		//check the getNextFibElement() methode from cExtObject
		if ( const_cast<cFibElement*>(&fibObject1)->getNextFibElement() ==
				const_cast<cFibElement*>(&fibObject2)->getNextFibElement() ){
		
			cout<<"The next/ main Fib-elementpointer for the external object element are correctly equal. "<<endl;
		}else{
			cerr<<"Error: The next/ main Fib-elementpointer for the external object element are not equal."<<endl;
			iReturn++;
		}
	
		//check the getFibElement() methode from cExtObject
		if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) ==
				const_cast<cFibElement*>(&fibObject2)->getFibElement( -1 ) ){
		
			cout<<"The previous Fib-elementpointer for the external object element are correctly equal. "<<endl;
		}else{
			cerr<<"Error: The previous Fib-elementpointer for the external object element are not equal."<<endl;
			iReturn++;
		}
		//check the getSuperiorFibElement() methode from cExtObject
		if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() ==
				const_cast<cFibElement*>(&fibObject2)->getSuperiorFibElement() ){
		
			cout<<"The superior Fib-elementpointer for the external object element are correctly equal. "<<endl;
		}else{
			cerr<<"Error: The superior Fib-elementpointer for the external object element are not equal."<<endl;
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
 * This method tests the copy methods and copyconstructor of the cExtObject class.
 *
 * methods tested:
 * 	- cExtObject( const cExtObject &ifElement );
 * 	- cFibElement *clone() const;
 * 	- cExtObject *copy( const unsignedIntFib iObjectExtObject=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementExtObject=0 ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a simple cExtObject"<<endl;

	cout<<"cExtObject extObjectSimple( 0 );"<<endl;
	cExtObject extObjectSimple( 0 );

	cout<<"cExtObject extObjectSimpleCopyConstruct( extObjectSimple );"<<endl;
	cExtObject extObjectSimpleCopyConstruct( extObjectSimple );

	iReturn += testCompareTwoEqualObjectsStructur( extObjectSimpleCopyConstruct, "extObjectSimpleCopyConstruct", extObjectSimple, "extObjectSimple" );

	cout<<"cFibElement * pExtObjectSimpleClone = extObjectSimple.clone();"<<endl;
	cFibElement * pExtObjectSimpleClone = extObjectSimple.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pExtObjectSimpleClone, "pExtObjectSimpleClone", extObjectSimple, "extObjectSimple" );
	delete pExtObjectSimpleClone;

	cout<<"cFibElement * pExtObjectSimpleCopy = extObjectSimple.copy();"<<endl;
	cFibElement * pExtObjectSimpleCopy = extObjectSimple.copy();

	iReturn += testCompareTwoEqualObjectsStructur( *pExtObjectSimpleCopy, "pExtObjectSimpleCopy", extObjectSimple, "extObjectSimple" );
	delete pExtObjectSimpleCopy;

	cout<<"cFibElement * pExtObjectSimpleCopyElement = extObjectSimple.copyElement();"<<endl;
	cFibElement * pExtObjectSimpleCopyElement = extObjectSimple.copyElement();

	iReturn += testCompareTwoEqualObjectsStructur( *pExtObjectSimpleCopyElement, "pExtObjectSimpleCopyElement", extObjectSimple, "extObjectSimple" );
	delete pExtObjectSimpleCopyElement;
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying for a other object or element point"<<endl;

	cout<<"cFibElement * pExtObjectSimpleNoCopy = extObjectSimple.copy( 1 );"<<endl;
	cFibElement * pExtObjectSimpleNoCopy = extObjectSimple.copy( 1 );

	if ( pExtObjectSimpleNoCopy == NULL ){
	
		cout<<"The cExtObject was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cExtObject was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pExtObjectSimpleNoCopy;
	}

	cout<<"cFibElement * pExtObjectSimpleNoCopyElement = extObjectSimple.copyElement( 'o', 2 );"<<endl;
	cFibElement * pExtObjectSimpleNoCopyElement = extObjectSimple.copyElement( 'o', 2 );

	if ( pExtObjectSimpleNoCopyElement == NULL ){
	
		cout<<"The cExtObject -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cExtObject -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pExtObjectSimpleNoCopyElement;
	}

	cout<<"pExtObjectSimpleNoCopyElement = extObjectSimple.copyElement( 'u', 2 );"<<endl;
	pExtObjectSimpleNoCopyElement = extObjectSimple.copyElement( 'u', 2 );

	if ( pExtObjectSimpleNoCopyElement == NULL ){
	
		cout<<"The cExtObject -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cExtObject -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pExtObjectSimpleNoCopyElement;
	}

	cout<<"pExtObjectSimpleNoCopyElement = extObjectSimple.copyElement( 'r', 1 );"<<endl;
	pExtObjectSimpleNoCopyElement = extObjectSimple.copyElement( 'r', 1 );

	if ( pExtObjectSimpleNoCopyElement == NULL ){
	
		cout<<"The cExtObject -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cExtObject -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pExtObjectSimpleNoCopyElement;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cExtObject with all members set"<<endl;

	//if in Fib-element structur
	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	cout<<"root.setNumberOfInputVariables( 10 );"<<endl;
	root.setNumberOfInputVariables( 10 );
	
	cout<<"cVectorExtObject vecInValues( 4 );"<<endl;
	cVectorExtObject vecInValues( 4 );
	cout<<"vecInValues.setVariable( 1, root.getInputVariable( 7 ) )"<<endl;
	vecInValues.setVariable( 1, root.getInputVariable( 7 ) );
	cout<<"vecInValues.setValue( 2, 6 )"<<endl;
	vecInValues.setValue( 2, 6 );
	cout<<"vecInValues.setVariable( 3,  root.getInputVariable( 4 ) )"<<endl;
	vecInValues.setVariable( 3, root.getInputVariable( 4 ) );
	cout<<"vecInValues.setValue( 4, -1 )"<<endl;
	vecInValues.setValue( 4, -1 );
	
	cout<<"cExtObject extObj2E2( 2, vecInValues, &root );"<<endl;
	cExtObject extObj2E2( 2, vecInValues, &root  );

	//set subobjects and output variables
	cout<<"cPoint pointSubobj1;"<<endl;
	cPoint pointSubobj1;
	cout<<"extObj2E2.addSubobject( &pointSubobj1 );"<<endl;
	extObj2E2.addSubobject( &pointSubobj1 );
	cout<<"extObj2E2.setNumberOfOutputVariables( 1, 1 );"<<endl;
	extObj2E2.setNumberOfOutputVariables( 1, 1 );
	cout<<"cPoint pointSubobj2;"<<endl;
	cPoint pointSubobj2;
	cout<<"extObj2E2.addSubobject( &pointSubobj2 );"<<endl;
	extObj2E2.addSubobject( &pointSubobj2 );
	cout<<"extObj2E2.setNumberOfOutputVariables( 2, 4 );"<<endl;
	extObj2E2.setNumberOfOutputVariables( 2, 4 );

	cout<<"cExtObject extObj2E2CopyConstruct( extObj2E2 );"<<endl;
	cExtObject extObj2E2CopyConstruct( extObj2E2 );

	if ( extObj2E2CopyConstruct.equalElement( extObj2E2 ) ){

		cout<<"The extObj2E2CopyConstruct Fib-element is equal to extObj2E2. "<<endl;
	}else{
		cerr<<"Error: The extObj2E2CopyConstruct Fib-element is not equal to extObj2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( extObj2E2CopyConstruct );

	cout<<"cFibElement * pExtObject2E2Copy = extObj2E2.copy();"<<endl;
	cFibElement * pExtObject2E2Copy = extObj2E2.copy();
	iReturn += testCompareTwoEqualObjects( *pExtObject2E2Copy, "pExtObject2E2Copy", extObj2E2, "extObj2E2" );
	//check the getFibElement() methode from cExtObject
	if ( NULL == pExtObject2E2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous Fib-elementpointer for the external object element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-elementpointer for the external object element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cExtObject
	if ( NULL == pExtObject2E2Copy->getSuperiorFibElement() ){
	
		cout<<"The superior Fib-elementpointer for the external object element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-elementpointer for the external object element is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( pExtObject2E2Copy );

	cout<<"cFibElement * pExtObject2E2CopyElement = extObj2E2.copyElement( 'u', 1 );"<<endl;
	cFibElement * pExtObject2E2CopyElement = extObj2E2.copyElement( 'u', 1 );

	if ( pExtObject2E2CopyElement->equalElement( extObj2E2 ) ){
	
		cout<<"The pExtObject2E2CopyElement Fib-element is equal to extObj2E2. "<<endl;
	}else{
		cerr<<"Error: The pExtObject2E2CopyElement Fib-element is not equal to extObj2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pExtObject2E2CopyElement );
	delete pExtObject2E2CopyElement;

	cout<<"cFibElement * pExtObject2E2Clone = extObj2E2.clone();"<<endl;
	cFibElement * pExtObject2E2Clone = extObj2E2.clone();
	iReturn += testCompareTwoEqualObjectsStructur( *pExtObject2E2Clone, "pExtObject2E2Clone", root, "root", true );
	pExtObject2E2Clone->deleteObject();


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a limb with more then one external object element and point element"<<endl;

	//a limb with more then one external object element and point element
	cout<<"cExtObject extObjTree( -4 );"<<endl;
	cExtObject extObjTree( -4 );
	
	cout<<"extObjTree.setNumberOfSubobjects( 5 );"<<endl;
	extObjTree.setNumberOfSubobjects( 5 );
	
	cout<<"cPoint pointSubobj3;"<<endl;
	cPoint pointSubobj3;
	cout<<"extObjTree.setSubobject( 2, &pointSubobj3 );"<<endl;
	extObjTree.setSubobject( 2, &pointSubobj3 );

	cout<<"cExtObject extObjSub( 2 );"<<endl;
	cExtObject extObjSub( 2 );
	cout<<"extObjTree.setSubobject( 4, &extObjSub );"<<endl;
	extObjTree.setSubobject( 4, &extObjSub );
	
	cout<<"extObjTree.setNumberOfOutputVariables( 1, 7 );"<<endl;
	extObjTree.setNumberOfOutputVariables( 1, 7 );
	cout<<"extObjTree.setNumberOfOutputVariables( 2, 1 );"<<endl;
	extObjTree.setNumberOfOutputVariables( 2, 1 );
	cout<<"extObjTree.setNumberOfOutputVariables( 4, 3 );"<<endl;
	extObjTree.setNumberOfOutputVariables( 4, 3 );


	cout<<endl<<"cExtObject extObjTreeCopyConstruct( extObjTree );"<<endl;
	cExtObject extObjTreeCopyConstruct( extObjTree );

	if ( extObjTreeCopyConstruct.equalElement( extObjTree ) ){
	
		cout<<"The extObjTreeCopyConstruct Fib-element is equal to extObjTree. "<<endl;
	}else{
		cerr<<"Error: The extObjTreeCopyConstruct Fib-element is not equal to extObjTree."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( extObjTreeCopyConstruct );

	cout<<"cFibElement * extObjTreeCopy = extObjTree.copy();"<<endl;
	cFibElement * extObjTreeCopy = extObjTree.copy();

	iReturn += testCompareTwoEqualObjects(
		*extObjTreeCopy, "extObjTreeCopy",
		extObjTree, "extObjTree" );
	//check the getFibElement() methode from cExtObject
	if ( NULL == extObjTreeCopy->getFibElement( -1 ) ){
	
		cout<<"The previous Fib-elementpointer for the external object element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous Fib-elementpointer for the external object element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cExtObject
	if ( extObjTreeCopy->getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib-elementpointer for the external object element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior Fib-elementpointer for the external object element is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( extObjTreeCopy );

	cout<<"cFibElement * pExtObject1Obj2 = extObjTree.copyElement();"<<endl;
	cFibElement * pExtObject1Obj2 = extObjTree.copyElement();

	if ( pExtObject1Obj2->equalElement( extObjTree ) ){
	
		cout<<"The pExtObject1Obj2 Fib-element is equal to extObjTree. "<<endl;
	}else{
		cerr<<"Error: The pExtObject1Obj2 Fib-element is not equal to extObjTree."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pExtObject1Obj2 );
	delete pExtObject1Obj2;


	cout<<"cFibElement * pExtObject1Obj2Clone = extObjTree.clone();"<<endl;
	cFibElement * pExtObject1Obj2Clone = extObjTree.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pExtObject1Obj2Clone, "pExtObject1Obj2Clone", extObjTree, "extObjTree", true );
	pExtObject1Obj2Clone->deleteObject();


	return iReturn;
}



/**
 * This method tests a in the xml -format stored cExtObject.
 *
 * @param szFilename the name of the file wher the cFibVector is stored
 * @param lIdentifer the identifier of the external object element
 * @param vecInputValues the values of the input variables
 * @param uiIdFirstOutVar the first free identifier for the output variables
 * @param vecNumberOfOutVar the number of the output variables for the
 * 	different subobjects
 * @return the number of errors occured in the test
 */
int testXmlExtObject( const string szFilename,
		long lIdentifer,
		vector< unsigned int > vecInputValues,
		unsigned int uiIdFirstOutVar,
		vector< unsigned int > vecNumberOfOutVar ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cExtObject:"<<endl;
	
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
		
		const string szExtObjectElementName = "obj";
		if ( szElementName == szExtObjectElementName ){
			cout<<"The root element is correctly named \""<< szExtObjectElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szExtObjectElementName <<"\"."<<endl;
			iReturn++;
		}
		
	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	//check the identifier attribute
	int iReadedIdentifier = 0;
	if ( pXmlElement->Attribute( "identifier", & iReadedIdentifier ) ){
		
		if ( iReadedIdentifier == lIdentifer ){
			cout<<"The external object element correctly has the identifier "<<lIdentifer<<". "<<endl;
		}else{
		cerr<<"Error: The external object element has the identifier "<<
			iReadedIdentifier<<", but should have the identifier "<<lIdentifer<<" "<<endl;
		iReturn++;
		}
	}else{
		cerr<<"Error: The external object element has no attribute identifier. "<<endl;
		iReturn++;
	}
	
	//check input value
	TiXmlHandle xmlHandleInputVariables = TiXmlHandle( pXmlElement );
	TiXmlElement * pXmlInputVariables = xmlHandleInputVariables.FirstChild().Element();
	
	if ( pXmlInputVariables ) {
		
		const char * szVectorXmlType = pXmlInputVariables->Attribute( "type" );
		
		if ( szVectorXmlType == NULL ){
			cerr<<"Error: The vector has no type."<<endl;
			iReturn++;
		}else if ( string("externObjectInput") == szVectorXmlType ) {
			cout<<"The type of the vector is correctly \"externObjectInput\". "<<endl;
		}else{
			cerr<<"Error: The type of the vector is \""<< szVectorXmlType
				<<"\", but should be \"externObjectInput\"."<<endl;
			iReturn++;
		}
		
		TiXmlHandle xmlHandleInVectorRoot = TiXmlHandle( pXmlInputVariables );
		TiXmlElement * pXmlElemInputValue =
			xmlHandleInVectorRoot.FirstChild().Element();
		
		int iReadedNumberOfElement = 0;
		for( int iNumberOfElement = 1; pXmlElemInputValue;
				pXmlElemInputValue = pXmlElemInputValue->NextSiblingElement(), iNumberOfElement++ ){
		
			string szElementName = pXmlElemInputValue->Value();
			
			if ( pXmlElemInputValue->Attribute( "number", & iReadedNumberOfElement ) ){
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
			}else if ( (int)(vecInputValues.size()) < iNumberOfElement ){
				cerr<<"Error: Ther couldn't be a "<< iNumberOfElement <<
					"'th vectorelement, because the vector has yust "<<
						vecInputValues.size() <<" elements."<<endl;
				iReturn++;
			}
			
			if ( szElementName == "value" ){
				const char * pcValue = pXmlElemInputValue->GetText();
				cout<<"The value of the element is: "<< pcValue <<endl;
				//converting value to double
				if ( (1 <= iNumberOfElement) &&
						( iNumberOfElement <= (int)(vecInputValues.size()) ) ){
					double dValue;
					int iReadValues = sscanf ( pcValue, "%lf", & dValue );
					if ( iReadValues != 0){
						if ( dValue == vecInputValues[ iNumberOfElement - 1 ] ){
							cout<<"The value of the element is correct."<<endl;
						}else{
							cerr<<"Error: The value of the element should be : "<<
								vecInputValues[ iNumberOfElement - 1 ] <<endl;
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
	}
	
	//check subobjects
	TiXmlElement * pXmlSubobject = NULL;
	if ( pXmlInputVariables ){
		pXmlSubobject = pXmlInputVariables->NextSiblingElement();
	}
	
	if ( pXmlSubobject == NULL ){
		if ( vecNumberOfOutVar.empty() ){
			cout<<"Ther are correctly no subobjects. "<<endl;
		}else{
			cerr<<"Error: Ther are subobjects, but ther should be non."<<endl;
			iReturn++;
		}
	}else if ( ! vecNumberOfOutVar.empty() ){
		
		unsigned int uiActualSubobject = 0;
		for ( ; pXmlSubobject; uiActualSubobject++,
				pXmlSubobject = pXmlSubobject->NextSiblingElement() ){
		
			const string szSubobjectName = pXmlSubobject->Value();
			
			if ( szSubobjectName != "subobject" ){
				
				cout<<"The "<<uiActualSubobject<<"'th subobject name is "<<
					szSubobjectName<<", but should be \"subobject\" . "<<endl;
			}
			
			//check subelements
			TiXmlHandle xmlHandleSubElement = TiXmlHandle( pXmlSubobject );
			TiXmlElement * pXmlSubElement = xmlHandleSubElement.FirstChild().Element();
			
			string szElementName;
			if ( pXmlSubElement ) {
				szElementName = pXmlSubElement->Value();
		
				if ( ( szElementName == "output_variables" ) ){
					cout<<"The subelement is correctly named \"output_variables\". "<<endl;
				
				}else if ( szElementName == "point" ){
					cout<<"The subelement is correctly named \"point\". "<<endl;
				
				}else{
					cerr<<"Error: The name of the subelement is "<< szElementName <<
						" and not \"output_variables\" or \"point\"."<<endl;
					iReturn++;
				}
			}
			//check output variables
			unsigned int uiNumberOfOutputVariables = 0;
			if ( uiActualSubobject < vecNumberOfOutVar.size() ){
				uiNumberOfOutputVariables = vecNumberOfOutVar[ uiActualSubobject ];
			}
			if ( szElementName == "output_variables" ){
				//read output variables
				TiXmlHandle xmlHandleOutputVariables = TiXmlHandle( pXmlSubElement );
				TiXmlElement * pXmlOutputVariable = xmlHandleOutputVariables.FirstChild().Element();
				
				unsigned int uiActualOutputVariable = 0;
				for ( ; pXmlOutputVariable; uiActualOutputVariable++,
						pXmlOutputVariable = pXmlOutputVariable->NextSiblingElement() ){
					

					const string szVariableName = pXmlOutputVariable->Value();
					if ( szVariableName == "variable" ){
						cout<<"The subelement is correctly named \"variable\". "<<endl;
					
					}else{
						cerr<<"Error: The name of the subelement is "<< szVariableName <<" and not \"variable\"."<<endl;
						iReturn++;
					}
					const char * szVariableIdentifier = pXmlOutputVariable->GetText();
					
					if ( szVariableIdentifier == NULL ){
						cerr<<"Error: The "<<uiActualOutputVariable<<" has no identifier."<<endl;
						iReturn++;
					}else if ( uiActualOutputVariable < uiNumberOfOutputVariables ){
						
						const unsigned int uiCorrectVariableId =
							uiIdFirstOutVar + uiActualOutputVariable;
						const unsigned int uiLoadedVariableId =
							atol( szVariableIdentifier );
						
						if ( uiCorrectVariableId == uiLoadedVariableId ){
							cout<<"The "<<uiActualOutputVariable<<" output variable identifier is correctly "<<
								uiCorrectVariableId<<" . "<<endl;
						}else{
							cerr<<"Error: The "<<uiActualOutputVariable<<" output variable identifier is "<<
								uiLoadedVariableId<<", but should be "<<uiCorrectVariableId<<" ."<<endl;
							iReturn++;
						}
				
					}else{// pXmlUnderExtObject == NULL
						cerr<<"Error: Ther is an "<<uiActualOutputVariable<<
							"'th output varable with the value \""<< szVariableIdentifier <<"\"."<<endl;
						iReturn++;
					}
					
				}
				if ( uiActualOutputVariable != uiNumberOfOutputVariables ){
					cerr<<"Error: Ther are "<<uiActualOutputVariable<<" output variables, but it should be "<<
						uiNumberOfOutputVariables<<"."<<endl;
					iReturn++;
				}
			}else{// szElementName != "output_variables"
				if ( uiNumberOfOutputVariables == 0 ){
					cout<<"Ther are correctly no output variables . "<<endl;
				}else{
					cerr<<"Error: No output variables handle in \""<< szFilename <<"\"."<<endl;
					iReturn++;
				}
			}
			//check subobject
			if ( szElementName != "point" ){
				if ( pXmlSubElement ){
					pXmlSubElement = pXmlSubElement->NextSiblingElement();
				}
				if ( pXmlSubElement ) {
					szElementName = pXmlSubElement->Value();
			
					if ( szElementName == "point" ){
						cout<<"The subelement is correctly named \"point\". "<<endl;
					
					}else{
						cerr<<"Error: The name of the subelement is "<< szElementName <<
							" and not \"output_variables\" or \"point\"."<<endl;
						iReturn++;
					}
				}else{
					cerr<<"Error: Ther is no subobject."<<endl;
					iReturn++;
				}
			}//else (szElementName == "point")
			
		}
		if ( uiActualSubobject != vecNumberOfOutVar.size() ){
			cerr<<"Error: Ther are "<<uiActualSubobject<<" subobjects, but it should be "<<
				vecNumberOfOutVar.size()<<"."<<endl;
			iReturn++;
		}
		
		
	}else{
		if ( pXmlSubobject == NULL ){
			cout<<"Ther are correctly no subobjects. "<<endl;
		}else{
			cerr<<"Error: Ther are subobjects, but ther should be non."<<endl;
			iReturn++;
		}
	}
	
	return iReturn;
}





/**
 * This method tests the storeXml() method of the cExtObject class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an empte external object"<<endl;

	cout<<"cExtObject extObjectId0( 0 );"<<endl;
	cExtObject extObjectId0( 0 );
	
	long lIdentifer = 0;
	vector< unsigned int > vecInValNumbers;
	unsigned int uiIdFirstOutVar = 0;
	vector< unsigned int > vecNumberOfOutVar;
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlExtObjectFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extObjectId0.xml" );
	ofstream * pFileVectorPostion = new ofstream( szXmlExtObjectFileName );
	
	bool bStoreSuccesfull = extObjectId0.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cExtObject was stored successfull to the file \""<< szXmlExtObjectFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cExtObject to the file \""<< szXmlExtObjectFileName <<"\" failed."<<endl;
		iReturn++;
	}	
	iReturn += testXmlExtObject( szXmlExtObjectFileName, lIdentifer,
		 vecInValNumbers, uiIdFirstOutVar, vecNumberOfOutVar );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an external object with id 7"<<endl;

	cout<<"cExtObject extObjectId7( 7 );"<<endl;
	cExtObject extObjectId7( 7 );
	
	lIdentifer = 7;
	/*vecInValNumbers.empty();
	uiIdFirstOutVar = 0;
	vecNumberOfOutVar.empty();*/
	
	szFileNameBuffer[0] = 0;
	szXmlExtObjectFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extObjectId7.xml" );
	pFileVectorPostion = new ofstream( szXmlExtObjectFileName );
	
	bStoreSuccesfull = extObjectId7.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cExtObject was stored successfull to the file \""<< szXmlExtObjectFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cExtObject to the file \""<< szXmlExtObjectFileName <<"\" failed."<<endl;
		iReturn++;
	}	
	iReturn += testXmlExtObject( szXmlExtObjectFileName, lIdentifer,
		 vecInValNumbers, uiIdFirstOutVar, vecNumberOfOutVar );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an external object with input variables"<<endl;

	cout<<"cVectorExtObject vecInputValues( 3 );"<<endl;
	cVectorExtObject vecInputValues( 3 );
	cout<<"vecInputValues.setValue( 1, 1 );"<<endl;
	vecInputValues.setValue( 1, 1 );
	vecInValNumbers.push_back( 1 );
	cout<<"vecInputValues.setValue( 2, 5 );"<<endl;
	vecInputValues.setValue( 2, 5 );
	vecInValNumbers.push_back( 5 );
	cout<<"vecInputValues.setValue( 3, 3 );"<<endl;
	vecInputValues.setValue( 3, 3 );
	vecInValNumbers.push_back( 3 );
	
	lIdentifer = -8;
	cout<<"cExtObject extObjectIdm8InVal3( lIdentifer, vecInputValues );"<<endl;
	cExtObject extObjectIdm8InVal3( lIdentifer, vecInputValues );
	
	/*uiIdFirstOutVar = 0;
	vecNumberOfOutVar.empty();*/
	
	szFileNameBuffer[0] = 0;
	szXmlExtObjectFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extObjectIdm8InVal3.xml" );
	pFileVectorPostion = new ofstream( szXmlExtObjectFileName );
	
	bStoreSuccesfull = extObjectIdm8InVal3.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cExtObject was stored successfull to the file \""<< szXmlExtObjectFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cExtObject to the file \""<< szXmlExtObjectFileName <<"\" failed."<<endl;
		iReturn++;
	}	
	iReturn += testXmlExtObject( szXmlExtObjectFileName, lIdentifer,
		 vecInValNumbers, uiIdFirstOutVar, vecNumberOfOutVar );
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an external object with subobjects"<<endl;
	
	cout<<"cPoint subPoint1;"<<endl;
	cPoint subPoint1;
	cout<<"cPoint subPoint2;"<<endl;
	cPoint subPoint2;
	cout<<"cPoint subPoint31;"<<endl;
	cPoint subPoint3;
	
	lIdentifer = 12345;
	vecInValNumbers.clear();
	cout<<"cExtObject extObjectId12345Subobj3( lIdentifer );"<<endl;
	cExtObject extObjectId12345Subobj3( lIdentifer );
	
	cout<<"extObjectId12345Subobj3.addSubobject( &subPoint1 );"<<endl;
	extObjectId12345Subobj3.addSubobject( &subPoint1 );
	vecNumberOfOutVar.push_back( 0 );
	cout<<"extObjectId12345Subobj3.addSubobject( &subPoint2 );"<<endl;
	extObjectId12345Subobj3.addSubobject( &subPoint2 );
	vecNumberOfOutVar.push_back( 0 );
	cout<<"extObjectId12345Subobj3.addSubobject( &subPoint3 );"<<endl;
	extObjectId12345Subobj3.addSubobject( &subPoint3 );
	vecNumberOfOutVar.push_back( 0 );
	/*uiIdFirstOutVar = 0;*/
	
	szFileNameBuffer[0] = 0;
	szXmlExtObjectFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extObjectId12345Subobj3.xml" );
	pFileVectorPostion = new ofstream( szXmlExtObjectFileName );
	
	bStoreSuccesfull = extObjectId12345Subobj3.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cExtObject was stored successfull to the file \""<< szXmlExtObjectFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cExtObject to the file \""<< szXmlExtObjectFileName <<"\" failed."<<endl;
		iReturn++;
	}	
	iReturn += testXmlExtObject( szXmlExtObjectFileName, lIdentifer,
		 vecInValNumbers, uiIdFirstOutVar, vecNumberOfOutVar );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an external object with subobjects and output variables"<<endl;
	
	uiIdFirstOutVar = 4;
	vecNumberOfOutVar.clear();
	cout<<"extObjectId12345Subobj3.setNumberOfOutputVariables( 1, 2 );"<<endl;
	extObjectId12345Subobj3.setNumberOfOutputVariables( 1, 2 );
	vecNumberOfOutVar.push_back( 2 );
	cout<<"extObjectId12345Subobj3.getOutputVariable( 1, 1 )->setIntegerValue( 4 );"<<endl;
	extObjectId12345Subobj3.getOutputVariable( 1, 1 )->setIntegerValue( 4 );
	cout<<"extObjectId12345Subobj3.getOutputVariable( 1, 2 )->setIntegerValue( 5 );"<<endl;
	extObjectId12345Subobj3.getOutputVariable( 1, 2 )->setIntegerValue( 5 );
	
	cout<<"extObjectId12345Subobj3.setNumberOfOutputVariables( 2, 1 );"<<endl;
	extObjectId12345Subobj3.setNumberOfOutputVariables( 2, 1 );
	vecNumberOfOutVar.push_back( 1 );
	cout<<"extObjectId12345Subobj3.getOutputVariable( 2, 1 )->setIntegerValue( 4 );"<<endl;
	extObjectId12345Subobj3.getOutputVariable( 2, 1 )->setIntegerValue( 4 );
	
	cout<<"extObjectId12345Subobj3.setNumberOfOutputVariables( 3, 3 );"<<endl;
	extObjectId12345Subobj3.setNumberOfOutputVariables( 3, 3 );
	vecNumberOfOutVar.push_back( 3 );
	cout<<"extObjectId12345Subobj3.getOutputVariable( 3, 1 )->setIntegerValue( 4 );"<<endl;
	extObjectId12345Subobj3.getOutputVariable( 3, 1 )->setIntegerValue( 4 );
	cout<<"extObjectId12345Subobj3.getOutputVariable( 3, 2 )->setIntegerValue( 5 );"<<endl;
	extObjectId12345Subobj3.getOutputVariable( 3, 2 )->setIntegerValue( 5 );
	cout<<"extObjectId12345Subobj3.getOutputVariable( 3, 3 )->setIntegerValue( 6 );"<<endl;
	extObjectId12345Subobj3.getOutputVariable( 3, 3 )->setIntegerValue( 6 );
	
	szFileNameBuffer[0] = 0;
	szXmlExtObjectFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extObjectId12345Subobj3Ov2Ov1Ov3.xml" );
	pFileVectorPostion = new ofstream( szXmlExtObjectFileName );
	
	bStoreSuccesfull = extObjectId12345Subobj3.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cExtObject was stored successfull to the file \""<< szXmlExtObjectFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cExtObject to the file \""<< szXmlExtObjectFileName <<"\" failed."<<endl;
		iReturn++;
	}	
	iReturn += testXmlExtObject( szXmlExtObjectFileName, lIdentifer,
		 vecInValNumbers, uiIdFirstOutVar, vecNumberOfOutVar );
	
	
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

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method one external object element"<<endl;

	cout<<"cExtObject extObjId0( 0 );"<<endl;
	cExtObject extObjId0( 0 );

	//test get compressed size
	unsigned int uiCompressedSize = 4 + 32 + 4 + 2;
	if ( (unsigned int)(extObjId0.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size is "<<
			extObjId0.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extObjId0.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bool bStoreSuccesfull = extObjId0.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cExtObject1[] = { (char)0x0D, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtObject1, 6 );

	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method one external with differnt identifer"<<endl;

	cout<<"cExtObject extObjId7( 7 );"<<endl;
	cExtObject extObjId7( 7 );

	//test get compressed size
	uiCompressedSize = 4 + 32 + 4 + 2;
	if ( (unsigned int)(extObjId7.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size is "<<
			extObjId7.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extObjId7.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = extObjId7.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cExtObjId7[] = { (char)0x7D, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtObjId7, 6 );


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method one external with input variables"<<endl;

	cout<<"cVectorExtObject vecInputValues( 3 );"<<endl;
	cVectorExtObject vecInputValues( 3 );
	cout<<"vecInputValues.setValue( 1, 1 );"<<endl;
	vecInputValues.setValue( 1, 1 );
	cout<<"vecInputValues.setValue( 2, 5 );"<<endl;
	vecInputValues.setValue( 2, 5 );
	cout<<"vecInputValues.setValue( 3, 3 );"<<endl;
	vecInputValues.setValue( 3, 3 );
	
	cout<<"cExtObject extObjectIdm1InVal3( -1, vecInputValues  );"<<endl;
	cExtObject extObjectIdm1InVal3( -1, vecInputValues  );

	//test get compressed size
	uiCompressedSize = 4 + 32 + 4 + 3 * (1 + 8) + 2;
	if ( (unsigned int)(extObjectIdm1InVal3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size is "<<
			extObjectIdm1InVal3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extObjectIdm1InVal3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = extObjectIdm1InVal3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cExtObjectIdm1InVal3[] = { (char)0xFD, (char)0xFF, (char)0xFF, (char)0xFF, (char)0x3F, (char)0x02, (char)0x14, (char)0x18, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtObjectIdm1InVal3, 9 );


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method one external with subobjects"<<endl;

	cout<<"cPoint subPoint1;"<<endl;
	cPoint subPoint1;
	cout<<"cPoint subPoint2;"<<endl;
	cPoint subPoint2;
	cout<<"cPoint subPoint3;"<<endl;
	cPoint subPoint3;
	
	cout<<"cExtObject extObjectId12345Subobj3( 12345  );"<<endl;
	cExtObject extObjectId12345Subobj3( 12345  );
	
	cout<<"extObjectId12345Subobj3.addSubobject( &subPoint1 );"<<endl;
	extObjectId12345Subobj3.addSubobject( &subPoint1 );
	cout<<"extObjectId12345Subobj3.addSubobject( &subPoint2 );"<<endl;
	extObjectId12345Subobj3.addSubobject( &subPoint2 );
	cout<<"extObjectId12345Subobj3.addSubobject( &subPoint3 );"<<endl;
	extObjectId12345Subobj3.addSubobject( &subPoint3 );

	//test get compressed size
	uiCompressedSize = 4 + 32 + 4 + 2 + 3 * (2 + 5);
	if ( (unsigned int)(extObjectId12345Subobj3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size is "<<
			extObjectId12345Subobj3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extObjectId12345Subobj3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = extObjectId12345Subobj3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cExtObjectIdm12345Subobj3[] = { (char)0x9D, (char)0x03, (char)0x03, (char)0x00, (char)0x00, (char)0x23, (char)0x91, (char)0x48 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtObjectIdm12345Subobj3, 8 );


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method one external with subobjects with output variables"<<endl;

	cout<<"extObjectId12345Subobj3.setNumberOfOutputVariables( 1, 2 );"<<endl;
	extObjectId12345Subobj3.setNumberOfOutputVariables( 1, 2 );
	cout<<"extObjectId12345Subobj3.getOutputVariable( 1, 1 )->setIntegerValue( 4 );"<<endl;
	extObjectId12345Subobj3.getOutputVariable( 1, 1 )->setIntegerValue( 4 );
	cout<<"extObjectId12345Subobj3.getOutputVariable( 1, 2 )->setIntegerValue( 5 );"<<endl;
	extObjectId12345Subobj3.getOutputVariable( 1, 2 )->setIntegerValue( 5 );
	
	cout<<"extObjectId12345Subobj3.setNumberOfOutputVariables( 2, 1 );"<<endl;
	extObjectId12345Subobj3.setNumberOfOutputVariables( 2, 1 );
	cout<<"extObjectId12345Subobj3.getOutputVariable( 2, 1 )->setIntegerValue( 4 );"<<endl;
	extObjectId12345Subobj3.getOutputVariable( 2, 1 )->setIntegerValue( 4 );
	
	cout<<"extObjectId12345Subobj3.setNumberOfOutputVariables( 3, 3 );"<<endl;
	extObjectId12345Subobj3.setNumberOfOutputVariables( 3, 3 );
	cout<<"extObjectId12345Subobj3.getOutputVariable( 3, 1 )->setIntegerValue( 4 );"<<endl;
	extObjectId12345Subobj3.getOutputVariable( 3, 1 )->setIntegerValue( 4 );
	cout<<"extObjectId12345Subobj3.getOutputVariable( 3, 2 )->setIntegerValue( 5 );"<<endl;
	extObjectId12345Subobj3.getOutputVariable( 3, 2 )->setIntegerValue( 5 );
	cout<<"extObjectId12345Subobj3.getOutputVariable( 3, 3 )->setIntegerValue( 6 );"<<endl;
	extObjectId12345Subobj3.getOutputVariable( 3, 3 )->setIntegerValue( 6 );
	
	//test get compressed size
	uiCompressedSize = 4 + 32 + 4 + 2 + 3 * (2 + 5);
	if ( (unsigned int)(extObjectId12345Subobj3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size is "<<
			extObjectId12345Subobj3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extObjectId12345Subobj3Ov2Ov1Ov3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = extObjectId12345Subobj3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cEextObjectId12345Subobj3Ov2Ov1Ov3[] = { (char)0x9D, (char)0x03, (char)0x03, (char)0x00, (char)0x00, (char)0x2B, (char)0x93, (char)0x4B };
	iReturn += compareBytsWithFile( szFileNameBuffer, cEextObjectId12345Subobj3Ov2Ov1Ov3, 8 );


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method one external with subobjects with domains"<<endl;
	
	cout<<"cRoot root;"<<endl;
	cRoot root;
	
	vector<cDomainSingle*> vecDomains( 4 );
	
	vecDomains[ 0 ] = new cDomainNaturalNumberBit( 20 );
	vecDomains[ 1 ] = new cDomainNaturalNumber( 213 );
	vecDomains[ 2 ] = new cDomainNaturalNumberBit( 4 );
	vecDomains[ 3 ] = new cDomainNaturalNumber( 6 );
	
	cout<<"vectorDomainExtObj={ cDomainNaturalNumberBit( 20 ), "<<
		"cDomainNaturalNumber( 213 ), cDomainNaturalNumberBit( 4 ), "<<
		"cDomainNaturalNumber( 6 ) }"<<endl;
	cDomainVector vectorDomainExtObj( vecDomains );
	
	for ( unsignedIntFib uiActualSubdomain = 0; uiActualSubdomain < 4;
			uiActualSubdomain++ ){
			
		delete vecDomains[ uiActualSubdomain ];
	}
	
	cout<<"root.getDomains()->addDomain( cTypeExtObject(), vectorDomainExtObj );"<<endl;
	root.getDomains()->addDomain( cTypeExtObject(), vectorDomainExtObj );
	cout<<"root.setMainFibObject( &extObjectId12345Subobj3 );"<<endl;
	root.setMainFibObject( &extObjectId12345Subobj3 );
	
	cout<<"root.getDomains()->addDomain( cTypeVariable(), cDomainNaturalNumberBit( 4 ) );"<<endl;
	root.getDomains()->addDomain( cTypeVariable(), cDomainNaturalNumberBit( 4 ) );
	
	
	cout<<"root.getDomains()->addDomain( cTypeExtObject(), vectorDomainExtObj );"<<endl;
	root.getDomains()->addDomain( cTypeExtObject(), vectorDomainExtObj );
	cout<<"root.setMainFibObject( &extObjectId12345Subobj3 );"<<endl;
	root.setMainFibObject( &extObjectId12345Subobj3 );
	
	
	vector<cDomainSingle*> vecDomainsE2( 2 );
	vecDomainsE2[ 0 ] = new cDomainNaturalNumberBit( 6 );
	vecDomainsE2[ 1 ] = new cDomainNaturalNumberBit( 8 );
	
	cout<<"vectorDomainExtObjInput={ cDomainNaturalNumberBit( 6 ), "<<
		"cDomainNaturalNumber( 8 ) }"<<endl;
	cDomainVector vectorDomainExtObjInput( vecDomainsE2 );
	
	delete vecDomainsE2[ 0 ];
	delete vecDomainsE2[ 1 ];

	cout<<"root.getDomains()->addDomain( cTypeExtObjectInput( 12345 ), vectorDomainExtObjInput );"<<endl;
	root.getDomains()->addDomain( cTypeExtObjectInput( 12345 ), vectorDomainExtObjInput );
	
	vecDomainsE2[ 0 ] = new cDomainNaturalNumberBit( 16 );
	vecDomainsE2[ 1 ] = new cDomainNaturalNumberBit( 18 );
	
	cout<<"vectorDomainExtObjInput0={ cDomainNaturalNumberBit( 16 ), "<<
		"cDomainNaturalNumber( 18 ) }"<<endl;
	cDomainVector vectorDomainExtObjInput0( vecDomainsE2 );
	
	delete vecDomainsE2[ 0 ];
	delete vecDomainsE2[ 1 ];

	cout<<"root.getDomains()->addDomain( cTypeExtObjectInput( 0 ), vectorDomainExtObjInput0 );"<<endl;
	root.getDomains()->addDomain( cTypeExtObjectInput( 0 ), vectorDomainExtObjInput0 );
	
	
	cout<<"extObjectId12345Subobj3.setNumberOfInputValues( 2 );"<<endl;
	extObjectId12345Subobj3.setNumberOfInputValues( 2 );
	cout<<"extObjectId12345Subobj3.getInputVector()->setValue( 1, 1 );"<<endl;
	extObjectId12345Subobj3.getInputVector()->setValue( 1, 1 );
	cout<<"extObjectId12345Subobj3.getInputVector()->setValue( 2, 7 );"<<endl;
	extObjectId12345Subobj3.getInputVector()->setValue( 2, 7 );
	
	//test get compressed size
	uiCompressedSize = 4 + 20 + 8 + 16 + 4 + 3 * (3 + 5);
	if ( (unsigned int)(extObjectId12345Subobj3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size is "<<
			extObjectId12345Subobj3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "extObjectId12345Subobj3Ov2Ov1Ov3Dom.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = extObjectId12345Subobj3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cExtObjectId12345Subobj3Ov2Ov1Ov3Dom[] = { (char)0x9D, (char)0x03, (char)0x03,
		(char)0x02, (char)0x02, (char)0x07,
		(char)0x23, (char)0x19, (char)0x39, (char)0x09 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cExtObjectId12345Subobj3Ov2Ov1Ov3Dom, 10 );

	return iReturn;
}



/**
 * This function tests the identifier methods of the class.
 *
 * methods tested:
 * 	- longFib getIdentifier() const;
 * 	- void setIdentifier( const longFib lInIdentifier );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testIdentifier( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the identifier methods"<<endl;
	
	cout<<"cExtObject extObject( 0 );"<<endl;
	cExtObject extObject( 0 );

	for ( unsigned long ulIteration = 0; ulIteration < MAX_RAND_TEST_SIZE;
			ulIteration++ ){
		
		const long lNewIdentifier = rand() % ((rand() % (256 * 256 * 256)) + 1) -
			(128 * 256 * 256);
		
		cout<<"extObject.setIdentifier( "<<lNewIdentifier<<" );"<<endl;
		extObject.setIdentifier( lNewIdentifier );
		
		//check the getIdentifier() methode from cExtObject
		if ( extObject.getIdentifier() == lNewIdentifier ){
		
			cout<<"The identifier for the external object element is correctly "<<
				lNewIdentifier<<" . "<<endl;
		}else{
			cerr<<"Error: The identifier for the external object element is not "<<
				lNewIdentifier<<", but "<< extObject.getIdentifier()<<" ."<<endl;
			iReturn++;
		}
	}
	
	return iReturn;
}


/**
 * This function tests the input variables methods of the class.
 *
 * methods tested:
 * 	- cVectorExtObject * getInputVector();
 * 	- const cVectorExtObject * getInputVector() const;
 * 	- unsignedIntFib getNumberOfInputValues() const;
 * 	- void setNumberOfInputValues( const unsignedIntFib uiNumberOfInputValues );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testInputValues( unsigned long &ulTestphase ){

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

	cVectorExtObject vecCorrectInputValues( 0 );
	cout<<"cExtObject extObject( 1, 0, &root );"<<endl;
	cExtObject extObject( 1, 0, &root );
	cout<<"const cExtObject & constExtObject = extObject;"<<endl;
	const cExtObject & constExtObject = extObject;
	
	unsigned int uiNumberOfInputValues = 0;
	set< cFibVariable * > setCorrectUsedVariables;
	bool bValidElement = true;
	
	for ( unsigned long uiIteration = 1; uiIteration <= MAX_RAND_TEST_SIZE; uiIteration++ ){
		
		cout<<endl<<"Running iteration "<<uiIteration<<endl;
		//make changes

		if ( rand() % 8 != 0 ){
			//change vector of input values
			//choose position wher to change it
			const unsignedIntFib uiPositionToSet =
				rand() % ( uiNumberOfInputValues + 8 );
			
			if ( rand() % 2 == 0 ){
				//change to value
				//choose input value to set
				const doubleFib dValue = (doubleFib(rand() % ( 256L * 256L ) -
					(128L * 256L) )) / 256.0;
				
				vecCorrectInputValues.setValue( uiPositionToSet, dValue );
				
				cout<<"extObject.getInputVector()->setValue( uiPositionToSet, dValue );"<<endl;
				extObject.getInputVector()->setValue( uiPositionToSet, dValue );
			}else{//change to variable
				//choose input value to set
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
				}else{//choose NULL pointer as input value
					cout<<"pVariableToSet = NULL; ";
					pVariableToSet = NULL;
				}
				
				vecCorrectInputValues.setVariable( uiPositionToSet, pVariableToSet );
				
				cout<<"extObject.getInputVector()->setVariable( uiPositionToSet, pVariableToSet );"<<endl;
				extObject.getInputVector()->setVariable( uiPositionToSet, pVariableToSet );
			}//end if choose if variable or value to set
		}else{//change with setNumberOfInputValues()
			//choose new number of input values
			uiNumberOfInputValues = rand() % ((rand() % 32) + 1);
			
			cout<<"extObject.setNumberOfInputValues( "<<uiNumberOfInputValues<<" );"<<endl;
			extObject.setNumberOfInputValues( uiNumberOfInputValues );
			//generate correct vector of input values
			vecCorrectInputValues.resize( uiNumberOfInputValues );
	
		}//end if choose change type
		//generate correct vector of used variables
 		setCorrectUsedVariables = vecCorrectInputValues.getUsedVariables();
		//evalue if the cExtObject element is valid
/*TODO weg (if the variable is defined above is not part of the Fib element):
		bValidElement = true;
		for ( set<cFibVariable*>::const_iterator
				itrInputVariable = setCorrectUsedVariables.begin();
				itrInputVariable != setCorrectUsedVariables.end(); itrInputVariable++ ){
			
			if ( (*itrInputVariable) == NULL ){
				//variable is NULL pointer -> Fib-element not valid
				bValidElement = false;
				break;
			}else if ( setVariablesNDef.find( (*itrInputVariable) ) !=
					setVariablesNDef.end() ){
				//variable not defined above -> Fib-element not valid
				bValidElement = false;
				break;
			}
		}
*/
		
		//check the getNumberOfInputValues() methode from cExtObject
		if ( extObject.getNumberOfInputValues() == uiNumberOfInputValues ){
		
			cout<<"The extObject has correctly "<<uiNumberOfInputValues<<
				" input values. "<<endl;
		}else{
			cerr<<"Error: The extObject has "<<extObject.getNumberOfInputValues()<<
				" input values, but sould have "<<uiNumberOfInputValues<<" . "<<endl;
			iReturn++;
			uiNumberOfInputValues = extObject.getNumberOfInputValues();
		}
		//check the getInputVector() methode from cExtObject
		if ( extObject.getInputVector()->equal( vecCorrectInputValues ) ){
		
			cout<<"The extObject has the correct input values. "<<endl;
		}else{
			cerr<<"Error: The extObject has not the correct input values. "<<endl;
			iReturn++;
		}
		//check the getInputVector() const methode from cExtObject
		if ( ! constExtObject.getInputVector()->equal( vecCorrectInputValues ) ){
			cerr<<"Error: The constExtObject has not the correct input values. "<<endl;
			iReturn++;
		}
		
		//check the isValidFibElement() method
		if ( extObject.isValidFibElement() == bValidElement ){
		
			cout<<"The extObject is correctly a "<<
				(bValidElement?"valid":"not valid")<<" cExtObject. "<<endl;
		}else{
			cerr<<"Error: The extObject is "<<(bValidElement?"not a valid":"a valid")<<
				" cExtObject, but should"<<(bValidElement?"":"n't")<<" be ."<<endl;
			iReturn++;
		}
		//check getUsedVariables() method
		cout<<"setUsedVariables = extObject.getUsedVariables( ED_POSITION ); "<<endl;
		const set< cFibVariable * > setUsedVariables =
			extObject.getUsedVariables( ED_POSITION );
		if ( setUsedVariables == setCorrectUsedVariables ){
		
			cout<<"The correct used / input values wher given back. "<<endl;
		}else{
			cerr<<"Error: The used / input values given back are wrong. "<<endl;
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



/**
 * This function tests the input variables methods of the class.
 *
 * methods tested:
 * 	- unsignedIntFib getNumberOfSubobjects() const;
 * 	- void setNumberOfSubobjects( const unsignedIntFib uiNumberOfSubobjects, bool bDeleteOld=true );
 * 	- cFibElement * getSubobject( const unsignedIntFib uiNumberSubobject );
 * 	- bool setSubobject( const unsignedIntFib uiNumberSubobject, cFibElement* pFibObject, bool bDeleteOld=true );
 * 	- unsignedIntFib getNumberOfOutputVariables( const unsignedIntFib uiNumberOfSubobject ) const;
 * 	- bool setNumberOfOutputVariables( const unsignedIntFib uiNumberOfSubobject, const unsignedIntFib uiNumberOfVariables );
 * 	- vector< cFibVariable* > getOutputVariables( const unsignedIntFib uiNumberOfSubobject );
 * 	- cFibVariable * getOutputVariable( const unsignedIntFib uiNumberOfSubobject, const unsignedIntFib uiNumberOfOutputVariable );
 * 	- bool addSubobject( cFibElement * pSubobject, unsignedIntFib uiPosition = 0, const unsignedIntFib uiNumberOfOutVar = 0 );
 * 	- bool deleteSubobject( unsignedIntFib uiSubobjectNumber, bool bDeleteOld=true );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testSubobjects( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the input variables methods"<<endl;
	
	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	cout<<"root.setNumberOfInputVariables( 10 );"<<endl;
	root.setNumberOfInputVariables( 10 );
	
	cout<<"cExtObject extObject( 1, 0, &root );"<<endl;
	cExtObject extObject( 1, 0, &root );
	
	/*the vector with the subobjects
		first pair element: the subobject
		second pair element: the number of output variables of the subobject
	*/
	vector< pair< cFibElement *, unsignedIntFib > > vecSubobjects;
	list< cFibVariable * > liCorrectDefinedVariables;
	bool bValidElement = true;
	
	for ( unsigned long uiIteration = 1; uiIteration <= MAX_RAND_TEST_SIZE; uiIteration++ ){
		
		cout<<endl<<"Running iteration "<<uiIteration<<endl;
		//choose change to make
		const unsigned int uiChangeType = rand() % 5;
		
		
		switch ( uiChangeType ){
			case 0:{//change number of subobjects with setNumberOfSubobjects()
				//choose new number of subobjects
				const unsigned int uiNumberOfSubobjects =
					rand() % ((rand() % 32) + 1);
				
				//choose if the old subobjects sould be deleted
				const bool bDeleteOld = rand() % 2;
				
				cout<<"extObject.setNumberOfSubobjects( "<<uiNumberOfSubobjects<<
					", bDeleteOld="<<(bDeleteOld?"true":"false")<<" );"<<endl;
				extObject.setNumberOfSubobjects( uiNumberOfSubobjects, bDeleteOld );
				
				if ( ! bDeleteOld ){
					//delete subobjects manualy
					for ( unsigned int uiActualSubObj = uiNumberOfSubobjects;
							uiActualSubObj < vecSubobjects.size(); uiActualSubObj++ ){
						
						if ( vecSubobjects[ uiActualSubObj ].first ){
							vecSubobjects[ uiActualSubObj ].first->deleteObject();
						}
					}
				}
				vecSubobjects.resize( uiNumberOfSubobjects,
					pair< cFibElement *, unsignedIntFib >( NULL, 0 ) );
				
			}break;
			case 1:{//change subobjects with setSubobject()
				//choose number of subobject to change
				const unsigned int uiNumberOfSubobject =
					rand() % (vecSubobjects.size() + 4);
				
				//choose if the old subobjects sould be deleted
				const bool bDeleteOld = rand() % 2;
				//create new subobject
				
				cFibElement * pNewSubObject = NULL;
				cFibElement * pOldSubObject = NULL;
				bool bSubobjectCanBeSet = true;
				if ( rand() % 16 ){
					//set a subobject
					pNewSubObject = new cPoint();
					if ( 1 <= uiNumberOfSubobject ){
						
						if ( vecSubobjects.size() < uiNumberOfSubobject ){
							vecSubobjects.resize( uiNumberOfSubobject,
								pair< cFibElement *, unsignedIntFib >( NULL, 0 ) );
						}else{
							pOldSubObject = vecSubobjects[ uiNumberOfSubobject - 1 ].first;
						}
						vecSubobjects[ uiNumberOfSubobject - 1 ].first = pNewSubObject;
					}else{
						bSubobjectCanBeSet = false;
					}
				}else{//try to set NULL as the subobject
					bSubobjectCanBeSet = false;
				}
				
				cout<<"extObject.setSubobject( uiNumberOfSubobject="<<uiNumberOfSubobject<<
					", pNewSubObject="<<pNewSubObject<<
					", bDeleteOld="<<(bDeleteOld?"true":"false")<<" );"<<endl;
				const bool bSubobjectChanged = extObject.setSubobject(
					uiNumberOfSubobject, pNewSubObject, bDeleteOld );
				
				if ( bSubobjectChanged == bSubobjectCanBeSet ){
					cout<<"The subobject pNewSubObject could correctly be "<<
						(bSubobjectChanged?"set":"not set")<<" . "<<endl;
				}else{
					cerr<<"Error: The subobject pNewSubObject was "<<
						(bSubobjectChanged?"set":"not set")<<
						", but should"<<(bSubobjectCanBeSet?"":"n't")<<" be ."<<endl;
					iReturn++;
				}
				if ( ( ! bSubobjectChanged ) && ( pNewSubObject != NULL ) ){
					//delete new subobject
					pNewSubObject->deleteObject();
				}
				if ( bSubobjectChanged && ( ! bDeleteOld ) && ( pOldSubObject != NULL ) ){
					//delete old subobject
					pOldSubObject->deleteObject();
				}
				
			}break;
			case 2:{//change with number of output variables setNumberOfOutputVariables()
				//choose number of subobject to change the output variables for
				const unsigned int uiNumberOfSubobject =
					rand() % (vecSubobjects.size() + 4);
				//choose number of output variables to set
				const unsigned int uiNumberOfOutvar =
					rand() % ((rand() % 32) + 1);
				
				const bool  bOutvariablesCanBeSet = ( 1 <= uiNumberOfSubobject ) &&
						( uiNumberOfSubobject <= vecSubobjects.size() );
				//set the number of output variables
				cout<<"extObject.setNumberOfOutputVariables( uiNumberOfSubobject="<<
					uiNumberOfSubobject<<", uiNumberOfOutvar="<<uiNumberOfOutvar<<" );"<<endl;
				const unsigned int uiNumberOfOutvarChanged = extObject.setNumberOfOutputVariables(
					uiNumberOfSubobject, uiNumberOfOutvar );
				
				if ( bOutvariablesCanBeSet ){
					
					if ( uiNumberOfOutvarChanged == uiNumberOfOutvar ){
						cout<<uiNumberOfOutvar<<" output variables could correctly be set for the "<<
							uiNumberOfSubobject<<"'th subobject. "<<endl;
					}else{//uiNumberOfOutvarChanged != uiNumberOfOutvar
						cerr<<uiNumberOfOutvar<<" output variables could not be set for the "<<
							uiNumberOfSubobject<<"'th subobject, "<<
							uiNumberOfOutvarChanged<<" wher set. "<<endl;
						iReturn++;
					}
				}else{
					if ( uiNumberOfOutvarChanged == 0 ){
						cout<<"No output variables wher correctly be set for the "<<
							uiNumberOfSubobject<<"'th subobject. "<<endl;
					}else{//uiNumberOfOutvarChanged != uiNumberOfOutvar
						cerr<<"Error: "<<uiNumberOfOutvarChanged<<" output variables where set for the "<<
							uiNumberOfSubobject<<"'th subobject, but shouldn't be any set."<<endl;
						iReturn++;
					}
				}
				if ( bOutvariablesCanBeSet ){
					vecSubobjects[ uiNumberOfSubobject - 1 ].second = uiNumberOfOutvar;
				}
			}break;
			case 3:{//add subobject with addSubobject()
				//choose position wher to add the subobject
				const unsigned int uiPositionForSubobject =
					rand() % (vecSubobjects.size() + 4);
				//choose the number of output variables for the subobject
				const unsigned int uiNumberOfOutvar =
					rand() % ((rand() % 32) + 1);
				
				//create new subobject
				cFibElement * pNewSubObject = NULL;
				if ( rand() % 16 ){
					pNewSubObject = new cPoint();
					if ( ( 1 <= uiPositionForSubobject ) &&
							( uiPositionForSubobject <= vecSubobjects.size() ) ){
						//search for the position wher to add the subobject
						vector< pair< cFibElement *, unsignedIntFib > >::iterator
							itrActualSubobject = vecSubobjects.begin();
						for ( unsigned int uiPosition = 1;
								( itrActualSubobject != vecSubobjects.end() ) &&
								( uiPosition != uiPositionForSubobject );
								itrActualSubobject++, uiPosition++ ){
							//nothing to do
						}
						vecSubobjects.insert( itrActualSubobject,
							pair< cFibElement *, unsignedIntFib >(
								pNewSubObject, uiNumberOfOutvar ) );
					}else{//add to the end of the subobject list
						vecSubobjects.push_back( pair< cFibElement *, unsignedIntFib >(
							pNewSubObject, uiNumberOfOutvar ) );
					}
				}
				
				cout<<"extObject.addSubobject( pNewSubObject="<<pNewSubObject<<
					", uiNumberOfSubobject="<<uiPositionForSubobject<<
					", uiNumberOfOutvar="<<uiNumberOfOutvar<<" );"<<endl;
				const bool bSubobjectAdded = extObject.addSubobject(
					pNewSubObject, uiPositionForSubobject, uiNumberOfOutvar );
				
				if ( bSubobjectAdded ){
					if ( pNewSubObject ){
						cout<<"The subobject pNewSubObject could correctly be added . "<<endl;
					}else{
						cerr<<"Error:The subobject pNewSubObject=NULL could be "<<
							"added, but should not be (because it is NULL) . "<<endl;
						iReturn++;
					}
				}else{
					if ( pNewSubObject == NULL ){
						cout<<"The subobject pNewSubObject=NULL could correctly not be added . "<<endl;
					}else{
						cerr<<"Error: The subobject pNewSubObject was not "<<
							"added, but should be added."<<endl;
						iReturn++;
					}
				}
				if ( ( ! bSubobjectAdded ) && ( pNewSubObject != NULL ) ){
					//delete new subobject
					pNewSubObject->deleteObject();
				}
				
			}break;
			case 4:{//delete subobject with deleteSubobject()
				//choose position wher to delete the subobject
				const unsigned int uiPositionForSubobject =
					rand() % (vecSubobjects.size() + 4);
				//choose if the old subobjects sould be deleted
				const bool bDeleteOld = rand() % 2;
				
				//create new subobject
				bool bSubobjectCanBeDeleted = true;
				cFibElement * pOldSubObject = NULL;
				if ( ( 1 <= uiPositionForSubobject ) &&
						( uiPositionForSubobject <= vecSubobjects.size() ) ){
					//search for the position wher to delete the subobject
					vector< pair< cFibElement *, unsignedIntFib > >::iterator
						itrActualSubobject = vecSubobjects.begin();
					for ( unsigned int uiPosition = 1;
							( itrActualSubobject != vecSubobjects.end() ) &&
							( uiPosition != uiPositionForSubobject );
							itrActualSubobject++, uiPosition++ ){
						//nothing to do
					}
					if ( itrActualSubobject != vecSubobjects.end() ){
						//subobject to delete found
						pOldSubObject = itrActualSubobject->first;
						vecSubobjects.erase( itrActualSubobject );
					}else{//Error: no such subobject
						bSubobjectCanBeDeleted = false;
					}
				}else{//no subobject to delete
					bSubobjectCanBeDeleted = false;
				}
				
				cout<<"extObject.deleteSubobject( uiNumberOfSubobject="<<uiPositionForSubobject<<
					", bDeleteOld="<<bDeleteOld<<" );"<<endl;
				const bool bSubobjectDeleted = extObject.deleteSubobject(
					uiPositionForSubobject, bDeleteOld );
				
				if ( bSubobjectDeleted == bSubobjectCanBeDeleted ){
					cout<<"The "<<uiPositionForSubobject<<"'th subobject could correctly be "<<
						(bSubobjectDeleted?"deleted":"not deleted")<<" . "<<endl;
				}else{
					cerr<<"Error: The "<<uiPositionForSubobject<<"'th subobject was "<<
						(bSubobjectDeleted?"deleted":"not deleted")<<
						", but should"<<(bSubobjectCanBeDeleted?"":"n't")<<" be ."<<endl;
					iReturn++;
				}
				if ( bSubobjectDeleted && ( ! bDeleteOld ) && ( pOldSubObject != NULL ) ){
					//delete new subobject
					pOldSubObject->deleteObject();
				}
				
			}break;
			
			default://Error: Wrong change mode
				cerr<<"Error: Wrong change mode "<<uiChangeType<<endl;
				continue;
		};
		
		
		//evalue if the cExtObject element is valid
		bValidElement = true;
		for ( vector< pair< cFibElement *, unsignedIntFib > >::const_iterator
				itrSubobject = vecSubobjects.begin();
				itrSubobject != vecSubobjects.end(); itrSubobject++ ){
			
			if ( itrSubobject->first == NULL ){
				//subobject is NULL pointer -> Fib-element not valid
				bValidElement = false;
				break;
			}
		}
		
		//check the getNumberOfSubobjects() methode from cExtObject
		if ( extObject.getNumberOfSubobjects() == vecSubobjects.size() ){
		
			cout<<"The extObject has correctly "<<vecSubobjects.size()<<
				" subobjects. "<<endl;
		}else{
			cerr<<"Error: The extObject has "<<extObject.getNumberOfSubobjects()<<
				" subobjects, but sould have "<<vecSubobjects.size()<<" . "<<endl;
			iReturn++;
		}
		//check subobjects
		liCorrectDefinedVariables.clear();
		for ( unsigned int uiActualSubObj = 1; uiActualSubObj <= vecSubobjects.size();
				uiActualSubObj++ ){
			//check the getSubobject() methode
			if ( extObject.getSubobject( uiActualSubObj ) ==
					vecSubobjects[ uiActualSubObj - 1 ].first ){
			
				cout<<"The extObject has the correct "<<uiActualSubObj<<
					"'th subobject ("<<vecSubobjects[ uiActualSubObj - 1 ].first<<"). "<<endl;
			}else{
				cerr<<"Error: The extObject has not the "<<uiActualSubObj<<
					"'th subobject (it is "<<extObject.getSubobject( uiActualSubObj ) <<
					", but should be "<<vecSubobjects[ uiActualSubObj - 1 ].first<<"). "<<endl;
				iReturn++;
			}
			//check the getNumberOfOutputVariables() methode
			const unsigned int uiNumberOfOutVar =
				vecSubobjects[ uiActualSubObj - 1 ].second;
			if ( extObject.getNumberOfOutputVariables( uiActualSubObj ) == uiNumberOfOutVar ){
			
				cout<<"The extObject has the correct number "<<uiNumberOfOutVar<<
					" of output variables for the "<<uiActualSubObj<<
					"'th subobject. "<<endl;
			}else{
				cerr<<"Error: The extObject has the wrong number "<<
					extObject.getNumberOfOutputVariables( uiActualSubObj )<<
					" of output variables for the "<<uiActualSubObj<<
					"'th subobject, it should be "<<uiNumberOfOutVar<<". "<<endl;
				iReturn++;
			}
			
			//check getOutputVariable() method
			for ( unsigned int uiActualOutVar = 1; uiActualOutVar <= uiNumberOfOutVar;
					uiActualOutVar++ ){
				cFibVariable * pActualOutVar = extObject.getOutputVariable(
					uiActualSubObj, uiActualOutVar );
				
				if ( pActualOutVar == NULL ){
					cerr<<"Error: The "<<uiActualOutVar<<"'th output variable of the "<<
						uiActualSubObj<<"'th subobject is NULL."<<endl;
					iReturn++;
				}
				
				liCorrectDefinedVariables.push_back( pActualOutVar );
			}//end for all input variables
			cFibVariable * pActualOutVar = extObject.getOutputVariable(
				uiActualSubObj, 0 );
			if ( pActualOutVar != NULL ){
				cerr<<"Error: The "<<0<<"'th output variable of the "<<
					uiActualSubObj<<"'th subobject is not NULL (it is "<<pActualOutVar<<")."<<endl;
				iReturn++;
			}
			pActualOutVar = extObject.getOutputVariable( uiActualSubObj, uiNumberOfOutVar + 1 );
			if ( pActualOutVar != NULL ){
				cerr<<"Error: The "<<uiNumberOfOutVar + 1<<"'th output variable of the "<<
					uiActualSubObj<<"'th subobject is not NULL (it is "<<pActualOutVar<<")."<<endl;
				iReturn++;
			}
			//check getOutputVariables() method
			const vector< cFibVariable* > vecOutVariables =
				extObject.getOutputVariables( uiActualSubObj );
			
			if ( vecOutVariables.size() == uiNumberOfOutVar ){
			
				cout<<"The extObject gives back the correct number "<<uiNumberOfOutVar<<
					" of output variables for the "<<uiActualSubObj<<
					"'th subobject. "<<endl;
			}else{
				cerr<<"Error:The extObject gives back the wrong number "<<vecOutVariables.size()<<
					" of output variables for the "<<uiActualSubObj<<
					"'th subobject (it should be "<<uiNumberOfOutVar<<"). "<<endl;
				iReturn++;
			}
			
		}
		if ( extObject.getSubobject( 0 ) != NULL ){
			cerr<<"Error: The "<<0<<"'th subobject is not NULL."<<endl;
			iReturn++;
		}
		if ( extObject.getSubobject( vecSubobjects.size() + 1 ) != NULL ){
			cerr<<"Error: The "<<vecSubobjects.size() + 1<<"'th subobject is not NULL."<<endl;
			iReturn++;
		}
		
		//check the isValidFibElement() method
		if ( extObject.isValidFibElement() == bValidElement ){
		
			cout<<"The extObject is correctly a "<<
				(bValidElement?"valid":"not valid")<<" cExtObject. "<<endl;
		}else{
			cerr<<"Error: The extObject is "<<(bValidElement?"not a valid":"a valid")<<
				" cExtObject, but should"<<(bValidElement?"":"n't")<<" be ."<<endl;
			iReturn++;
		}
		//check getDefinedVariables() method
		cout<<"liDefinedVariables = extObject.getDefinedVariables( ED_POSITION ); "<<endl;
		const list< cFibVariable * > liDefinedVariables =
			extObject.getDefinedVariables( ED_POSITION );
		if ( liDefinedVariables == liCorrectDefinedVariables ){
		
			cout<<"The correct defined / output variables wher given back. "<<endl;
		}else{
			cerr<<"Error: The defined / output variables given back are wrong"<<
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
		//check getUsedVariables() method
		cout<<"setUsedVariables = extObject.getUsedVariables( ED_POSITION ); "<<endl;
		const set< cFibVariable * > setUsedVariables =
			extObject.getUsedVariables( ED_POSITION );
		if ( setUsedVariables.empty() ){
		
			cout<<"Ther are correctly no defined variables given back. "<<endl;
		}else{
			cerr<<"Error: Ther are defined variables given back. "<<endl;
			iReturn++;
		}
		
	}//end for rand iteration
	
	extObject.setNumberOfSubobjects( 0, true );
	
	return iReturn;
}


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
	
		cout<<"The correct used / input variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used / input variables given back are wrong. "<<endl;
		iReturn++;
	}
	//for all setCorrectUsedVariables check isUsedVariable()
	//check used variables
	for ( list< cFibVariable * >::const_iterator
			itrVariable = liAllVariables.begin();
			itrVariable != liAllVariables.end(); itrVariable++ ){
	
		//check the isUsedVariable() methode from cExtObject
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
	
		cout<<"The correct defined / output variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The defined / output variables given back are wrong"<<
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
	
		//check the isDefinedVariable() methode from cExtObject
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
 * This method tests the variable methods of the cExtObject class.
 *
 * methods tested:
 * 	- bool isUsedVariable( const cFibVariable *variable, edDirection direction=ED_POSITION ) const;
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION and ED_BELOW_EQUAL and ED_HIGHER_EQUAL );
 * 	- cFibVariable * getDefinedVariable();
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION (and ED_HIGHER for subobjects) ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION (and ED_HIGHER for subobjects) );
 * 	- bool setInputVariable( const unsignedIntFib uiNumberOfInputVariable, cFibVariable * pInputVariable );
 * 	- bool setNumberOfOutputVariables( const unsignedIntFib uiNumberOfSubobject, const unsignedIntFib uiNumberOfVariables );
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

	cout<<"cExtObject extObject1( -1, 5 );"<<endl;
	cExtObject extObject1( -1, 5 );
	
	set< cFibVariable * > setCorrectUsedVariables;
	list< cFibVariable * > liCorrectDefinedVariables;
	
	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the variable methods with input / used variables"<<endl;

	cout<<"extObject1.getInputVector()->setVariable( 1, pVariable4 );"<<endl;
	extObject1.getInputVector()->setVariable( 1, pVariable4 );
	
	setCorrectUsedVariables.insert( pVariable4 );
	
	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );
	
	cout<<endl<<"extObject1.getInputVector()->setVariable( 2, pVariable1 );"<<endl;
	extObject1.getInputVector()->setVariable( 2, pVariable1 );
	cout<<"extObject1.getInputVector()->setVariable( 3, pVariable4 );"<<endl;
	extObject1.getInputVector()->setVariable( 3, pVariable4 );
	cout<<"extObject1.getInputVector()->setVariable( 4, pVariable6 );"<<endl;
	extObject1.getInputVector()->setVariable( 4, pVariable6 );
	
	setCorrectUsedVariables.insert( pVariable1 );
	setCorrectUsedVariables.insert( pVariable6 );

	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );
	
	cout<<endl<<"extObject1.getInputVector()->setVariable( 2, pVariable3 );"<<endl;
	extObject1.getInputVector()->setVariable( 2, pVariable3 );
	
	setCorrectUsedVariables.erase( pVariable1 );
	setCorrectUsedVariables.insert( pVariable3 );

	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the variable methods with one subobject with output / defined variables"<<endl;
	
	cout<<endl<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );
	cout<<endl<<"cPoint subPoint1( &vecPositionE2 );"<<endl;
	cPoint subPoint1( &vecPositionE2 );
	
	cout<<endl<<"extObject1.addSubobject( &subPoint1 );"<<endl;
	extObject1.addSubobject( &subPoint1 );
	cout<<endl<<"extObject1.setNumberOfOutputVariables( 1, 3 );"<<endl;
	extObject1.setNumberOfOutputVariables( 1, 3 );
	
	liCorrectDefinedVariables.push_back( extObject1.getOutputVariable( 1, 1 ) );
	liCorrectDefinedVariables.push_back( extObject1.getOutputVariable( 1, 2 ) );
	liCorrectDefinedVariables.push_back( extObject1.getOutputVariable( 1, 3 ) );

	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );
	
	
	set< cFibVariable * > setCorrectUsedVariablesSubPoint1Position;
	list< cFibVariable * > liCorrectDefinedVariablesSubPoint1Position;
	set< cFibVariable * > setCorrectUsedVariablesSubPoint1HiEq = setCorrectUsedVariables;
	list< cFibVariable * > liCorrectDefinedVariablesSubPoint1PositionHiEq = liCorrectDefinedVariables;
	cout<<endl<<"Checking Variables of the external object element subPoint1:"<<endl;
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_ALL );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the variable methods with two subobject with output / defined variables"<<endl;
	
	cout<<endl<<"cPoint subPoint2( &vecPositionE2 );"<<endl;
	cPoint subPoint2( &vecPositionE2 );
	
	cout<<endl<<"extObject1.addSubobject( &subPoint2 );"<<endl;
	extObject1.addSubobject( &subPoint2 );
	cout<<endl<<"extObject1.setNumberOfOutputVariables( 2, 1 );"<<endl;
	extObject1.setNumberOfOutputVariables( 2, 1 );
	
	liCorrectDefinedVariables.push_back( extObject1.getOutputVariable( 2, 1 ) );

	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );
	
	
	cout<<endl<<"Checking Variables of the external object element subPoint1:"<<endl;
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint2:"<<endl;
	set< cFibVariable * > setCorrectUsedVariablesSubPoint2Position;
	list< cFibVariable * > liCorrectDefinedVariablesSubPoint2Position;
	set< cFibVariable * > setCorrectUsedVariablesSubPoint2HiEq = setCorrectUsedVariables;
	list< cFibVariable * > liCorrectDefinedVariablesSubPoint2PositionHiEq;
	liCorrectDefinedVariablesSubPoint2PositionHiEq.push_back( extObject1.getOutputVariable( 2, 1 ) );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_ALL );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the variable methods with tree subobject with output / defined variables"<<endl;
	
	cout<<endl<<"cPoint subPoint3( &vecPositionE2 );"<<endl;
	cPoint subPoint3( &vecPositionE2 );
	
	cout<<endl<<"extObject1.addSubobject( &subPoint3 );"<<endl;
	extObject1.addSubobject( &subPoint3 );
	cout<<endl<<"extObject1.setNumberOfOutputVariables( 3, 2 );"<<endl;
	extObject1.setNumberOfOutputVariables( 3, 2 );
	
	liCorrectDefinedVariables.push_back( extObject1.getOutputVariable( 3, 1 ) );
	liCorrectDefinedVariables.push_back( extObject1.getOutputVariable( 3, 2 ) );

	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint1:"<<endl;
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint2:"<<endl;
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint3:"<<endl;
	set< cFibVariable * > setCorrectUsedVariablesSubPoint3Position;
	list< cFibVariable * > liCorrectDefinedVariablesSubPoint3Position;
	set< cFibVariable * > setCorrectUsedVariablesSubPoint3HiEq = setCorrectUsedVariables;
	list< cFibVariable * > liCorrectDefinedVariablesSubPoint3PositionHiEq;
	liCorrectDefinedVariablesSubPoint3PositionHiEq.push_back( extObject1.getOutputVariable( 3, 1 ) );
	liCorrectDefinedVariablesSubPoint3PositionHiEq.push_back( extObject1.getOutputVariable( 3, 2 ) );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_ALL );
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the variable methods with seting variables in subobjects"<<endl;
	
	cout<<"subPoint2.getPosition()->setVariable( 2, pVariable1 );"<<endl;
	subPoint2.getPosition()->setVariable( 2, pVariable1 );
	
	set< cFibVariable * > setCorrectUsedVariablesBelowEqual = setCorrectUsedVariables;
	setCorrectUsedVariablesBelowEqual.insert( pVariable1 );
	setCorrectUsedVariablesSubPoint2Position.insert( pVariable1 );
	setCorrectUsedVariablesSubPoint2HiEq.insert( pVariable1 );

	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint1:"<<endl;
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint2:"<<endl;
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint3:"<<endl;
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_ALL );
	
	
	cout<<endl<<"subPoint2.getPosition()->setVariable( 2, pVariable2 );"<<endl;
	subPoint2.getPosition()->setVariable( 2, pVariable2 );
	
	setCorrectUsedVariablesBelowEqual.erase( pVariable1 );
	setCorrectUsedVariablesSubPoint2Position.erase( pVariable1 );
	setCorrectUsedVariablesSubPoint2HiEq.erase( pVariable1 );
	setCorrectUsedVariablesBelowEqual.insert( pVariable2 );
	setCorrectUsedVariablesSubPoint2Position.insert( pVariable2 );
	setCorrectUsedVariablesSubPoint2HiEq.insert( pVariable2 );

	cout<<endl<<"subPoint1.getPosition()->setVariable( 1, pVariable5 );"<<endl;
	subPoint1.getPosition()->setVariable( 1, pVariable5 );
	
	setCorrectUsedVariablesBelowEqual.insert( pVariable5 );
	setCorrectUsedVariablesSubPoint1Position.insert( pVariable5 );
	setCorrectUsedVariablesSubPoint1HiEq.insert( pVariable5 );
	
	cout<<endl<<"subPoint3.getPosition()->setVariable( 1, pVariable5 );"<<endl;
	subPoint3.getPosition()->setVariable( 1, pVariable5 );
	
	setCorrectUsedVariablesBelowEqual.insert( pVariable5 );
	setCorrectUsedVariablesSubPoint3Position.insert( pVariable5 );
	setCorrectUsedVariablesSubPoint3HiEq.insert( pVariable5 );
	
	cout<<endl<<"subPoint3.getPosition()->setVariable( 2, pVariable4 );"<<endl;
	subPoint3.getPosition()->setVariable( 2, pVariable4 );
	
	setCorrectUsedVariablesBelowEqual.insert( pVariable4 );
	setCorrectUsedVariablesSubPoint3Position.insert( pVariable4 );
	setCorrectUsedVariablesSubPoint3HiEq.insert( pVariable4 );
	//used variables: 2, 3, 4, 5, 6
	
	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint1:"<<endl;
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint2:"<<endl;
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint3:"<<endl;
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_ALL );


	cout<<endl<<"subPoint2.getPosition()->setVariable( 1, extObject1.getOutputVariable( 1, 2 ) );"<<endl;
	subPoint2.getPosition()->setVariable( 1, extObject1.getOutputVariable( 1, 2 ) );
	
	setCorrectUsedVariablesBelowEqual.insert( extObject1.getOutputVariable( 1, 2 ) );
	setCorrectUsedVariablesSubPoint2Position.insert( extObject1.getOutputVariable( 1, 2 ) );
	setCorrectUsedVariablesSubPoint2HiEq.insert( extObject1.getOutputVariable( 1, 2 ) );
	
	cout<<endl<<"subPoint1.getPosition()->setVariable( 2, extObject1.getOutputVariable( 1, 2 ) );"<<endl;
	subPoint1.getPosition()->setVariable( 2, extObject1.getOutputVariable( 1, 2 ) );
	setCorrectUsedVariablesSubPoint1Position.insert( extObject1.getOutputVariable( 1, 2 ) );
	setCorrectUsedVariablesSubPoint1HiEq.insert( extObject1.getOutputVariable( 1, 2 ) );
	//used variables: 2, 3, 4, 5, 6, ext( 1,2 )
	
	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint1:"<<endl;
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint2:"<<endl;
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint3:"<<endl;
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_ALL );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the replaceVariable() method"<<endl;

	cout<<endl<<"extObject1.replaceVariable( pVariable3, pVariable1 );"<<endl;
	extObject1.replaceVariable( pVariable3, pVariable1 );
	
	setCorrectUsedVariables.erase( pVariable3 );
	setCorrectUsedVariables.insert( pVariable1 );
	setCorrectUsedVariablesBelowEqual.erase( pVariable3 );
	setCorrectUsedVariablesBelowEqual.insert( pVariable1 );
	setCorrectUsedVariablesSubPoint1HiEq.erase( pVariable3 );
	setCorrectUsedVariablesSubPoint1HiEq.insert( pVariable1 );
	setCorrectUsedVariablesSubPoint2HiEq.erase( pVariable3 );
	setCorrectUsedVariablesSubPoint2HiEq.insert( pVariable1 );
	setCorrectUsedVariablesSubPoint3HiEq.erase( pVariable3 );
	setCorrectUsedVariablesSubPoint3HiEq.insert( pVariable1 );
	//used variables: 1, 2, 4, 5, 6, ext( 1,2 )
	
	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint1:"<<endl;
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint2:"<<endl;
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint3:"<<endl;
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_ALL );

	cout<<endl<<"extObject1.replaceVariable( pVariable3, pVariable1 );"<<endl;
	extObject1.replaceVariable( pVariable3, pVariable1 );
	//used variables: 1, 2, 4, 5, 6, ext( 1,2 )
	
	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint1:"<<endl;
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint2:"<<endl;
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint3:"<<endl;
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_ALL );


	cout<<endl<<"extObject1.replaceVariable( pVariable1, pVariable1 );"<<endl;
	extObject1.replaceVariable( pVariable1, pVariable1 );
	//used variables: 1, 2, 4, 5, 6, ext( 1,2 )
	
	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint1:"<<endl;
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint2:"<<endl;
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint3:"<<endl;
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_ALL );


	cout<<endl<<endl<<"extObject1.replaceVariable( pVariable4, pVariable3 );"<<endl;
	extObject1.replaceVariable( pVariable4, pVariable3 );
	
	setCorrectUsedVariables.erase( pVariable4 );
	setCorrectUsedVariables.insert( pVariable3 );
	setCorrectUsedVariablesBelowEqual.erase( pVariable4 );
	setCorrectUsedVariablesBelowEqual.insert( pVariable3 );
	setCorrectUsedVariablesSubPoint1HiEq.erase( pVariable4 );
	setCorrectUsedVariablesSubPoint1HiEq.insert( pVariable3 );
	setCorrectUsedVariablesSubPoint2HiEq.erase( pVariable4 );
	setCorrectUsedVariablesSubPoint2HiEq.insert( pVariable3 );
	setCorrectUsedVariablesSubPoint3HiEq.erase( pVariable4 );
	setCorrectUsedVariablesSubPoint3HiEq.insert( pVariable3 );
	setCorrectUsedVariablesSubPoint3Position.erase( pVariable4 );
	setCorrectUsedVariablesSubPoint3Position.insert( pVariable3 );
	//used variables: 1, 2, 5, 6, ext( 1,2 )
	
	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint1:"<<endl;
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint2:"<<endl;
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint3:"<<endl;
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_ALL );


	cout<<endl<<endl<<"extObject1.replaceVariable( pVariable5, extObject1.getOutputVariable( 2, 1 ) );"<<endl;
	extObject1.replaceVariable( pVariable5, extObject1.getOutputVariable( 2, 1 ));
	
	setCorrectUsedVariablesBelowEqual.erase( pVariable5 );
	setCorrectUsedVariablesBelowEqual.insert( extObject1.getOutputVariable( 2, 1 ) );
	setCorrectUsedVariablesSubPoint1HiEq.erase( pVariable5 );
	setCorrectUsedVariablesSubPoint1HiEq.insert( extObject1.getOutputVariable( 2, 1 ) );
	setCorrectUsedVariablesSubPoint3HiEq.erase( pVariable5 );
	setCorrectUsedVariablesSubPoint3HiEq.insert( extObject1.getOutputVariable( 2, 1 ) );
	setCorrectUsedVariablesSubPoint1Position.erase( pVariable5 );
	setCorrectUsedVariablesSubPoint1Position.insert( extObject1.getOutputVariable( 2, 1 ) );
	setCorrectUsedVariablesSubPoint3Position.erase( pVariable5 );
	setCorrectUsedVariablesSubPoint3Position.insert( extObject1.getOutputVariable( 2, 1 ) );
	//used variables: 1, 2, 3, 6, ext( 1,2 ), ext( 2,1 )
	
	cout<<endl<<"Checking Variables of the external object element extObject1:"<<endl;
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_BELOW_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariables, liCorrectDefinedVariables, ED_HIGHER_EQUAL );
	iReturn += checkVariables( extObject1, liAllVariables, setCorrectUsedVariablesBelowEqual, liCorrectDefinedVariables, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint1:"<<endl;
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1Position, liCorrectDefinedVariablesSubPoint1Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint1, liAllVariables, setCorrectUsedVariablesSubPoint1HiEq, liCorrectDefinedVariablesSubPoint1PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint2:"<<endl;
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2Position, liCorrectDefinedVariablesSubPoint2Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint2, liAllVariables, setCorrectUsedVariablesSubPoint2HiEq, liCorrectDefinedVariablesSubPoint2PositionHiEq, ED_ALL );
	
	cout<<endl<<"Checking Variables of the external object element subPoint3:"<<endl;
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3Position, liCorrectDefinedVariablesSubPoint3Position, ED_BELOW_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_HIGHER_EQUAL );
	iReturn += checkVariables( subPoint3, liAllVariables, setCorrectUsedVariablesSubPoint3HiEq, liCorrectDefinedVariablesSubPoint3PositionHiEq, ED_ALL );


	return iReturn;
}













