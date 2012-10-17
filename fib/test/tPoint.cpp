/**
 * @file tPoint
 * file name: tPoint.cpp
 * @author Betti Oesterholz
 * @date 28.11.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cPoint.
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
 * This file contains the test for the class cPoint, which
 * represents a Fib -pointelement.
 *
 *
 * What's tested of class cPoint:
 * 	- cPoint( cVectorPosition * pInVectorPosition = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- bool hasUnderAllObjects( ) const;
 * 	- unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
 * 	- bool evalueObject( iEvaluePosition & evaluePosition, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties ) const;
 * 	- bool evalueObject( iEvalueFibElement & evalueFibElement, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties, const list<char> & liCFibElementTyps );
 * 	- bool equal( const cFibElement & fibObject ) const;
 * 	- bool equalElement( const cFibElement & fibElement ) const;
 * 	- cPoint( const cPoint &pointElement );
 * 	- cFibElement *clone( ) const;
 * 	- cPoint *copy( const unsignedIntFib iObjectPoint=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementPoint=0 ) const;
 * 	- bool storeXml( ostream &stream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream &stream ) const;
 * 	- cVectorPosition *getPosition();
 * 	- void setPosition( const cVectorPosition *vecPositon=NULL );
 * 	- bool isUsedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
 *
 *
 * Methods for changing the structur of an fib -object will be tested with
 *	tFibElementStructur. Methods for fib -objects will be tested with
 * Methods for storing and restoring will be tested in tFibElementStore.
 */
/*
History:
28.11.2009  Oesterholz  created
01.01.2010  Oesterholz  isUsedVariable( ED_POSITION ) and getUsedVariables( ED_POSITION ) tested
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
04.04.2011  Oesterholz  storing to binary stream
06.06.2011  Oesterholz  number atribute in XML-vector is now optional
26.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cPoint.h"
#include "cRoot.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cTypeVariable.h"
#include "cTypeDimension.h"
#include "cTypeProperty.h"
#include "cTypeInVar.h"
#include "cEvaluePositionList.h"
#include "cEvalueFibElementList.h"

#include "tinyxml.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>

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
int testPosition( unsigned long &ulTestphase );
int testVariable( unsigned long &ulTestphase );


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cPoint methods"<<endl;
	cout<<      "==============================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testEvalueObject( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testPosition( ulTestphase );
	iReturn += testVariable( ulTestphase );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the constructor of the cPoint class.
 *
 * methods tested:
 * 	- cPoint( cVectorPosition * pInVectorPosition = NULL, cFibElement * pInSuperiorElement = NULL, cFibElement * pInPreviousFibElement = NULL, cFibElement * pInNextFibElement = NULL );
 * 	- cPoint( const cPoint &pointElement );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- unsignedIntFib getNumberOfElement()
 * 	- cVectorPosition *getPosition();
 * 	- bool hasUnderAllObjects( ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cPoint"<<endl;

	cout<<"cPoint pointEmpty;"<<endl;
	cPoint pointEmpty;

	//check the getType() methode from cPoint
	if ( pointEmpty.getType() == 'p' ){
	
		cout<<"The type of the point -element is correctly 'p' . "<<endl;
	}else{
		cerr<<"Error: The type of the point -element is "<<
			pointEmpty.getType()<<" but should be 'p' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cPoint
	if ( pointEmpty.isValidFibElement() ){
	
		cout<<"The point -element is correctly a correct point -element. "<<endl;
	}else{
		cerr<<"Error: The point -element is not a point -element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cPoint
	if ( ! pointEmpty.isMovable() ){
	
		cout<<"The point -element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The point -element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cPoint
	if ( pointEmpty.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the point -element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the point -element is "<<
			pointEmpty.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cPoint
	if ( pointEmpty.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the point -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the point -element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cPoint
	if ( pointEmpty.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the point -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the point -element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cPoint
	if ( pointEmpty.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the point -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the point -element is "<<
			pointEmpty.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getPosition() methode from cPoint
	if ( pointEmpty.getPosition() == NULL ){
	
		cout<<"The positionsvector for the point -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The positionsvector for the point -element is "<<
			pointEmpty.getPosition() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cPoint
	if ( pointEmpty.hasUnderAllObjects() == true ){
	
		cout<<"The pointelement has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The pointelement is missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cPoint with a positionsvector"<<endl;

	cout<<"cVectorPosition vecPosition;"<<endl;
	cVectorPosition vecPosition;
	cout<<"vecPosition.setValue( 1, 4);"<<endl;
	vecPosition.setValue( 1, 4);

	cout<<"cPoint pointPosition( & vecPosition );"<<endl;
	cPoint pointPosition( & vecPosition );

	//check the getType() methode from cPoint
	if ( pointPosition.getType() == 'p' ){
	
		cout<<"The type of the point -element is correctly 'p' . "<<endl;
	}else{
		cerr<<"Error: The type of the point -element is "<<
			pointPosition.getType()<<" but should be 'p' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cPoint
	if ( pointPosition.isValidFibElement() ){
	
		cout<<"The point -element is correctly a correct point -element. "<<endl;
	}else{
		cerr<<"Error: The point -element is not a point -element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cPoint
	if ( ! pointPosition.isMovable() ){
	
		cout<<"The point -element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The point -element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cPoint
	if ( pointPosition.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the point -element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the point -element is "<<
			pointPosition.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cPoint
	if ( pointPosition.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the point -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the point -element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cPoint
	if ( pointPosition.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the point -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the point -element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cPoint
	if ( pointPosition.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the point -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the point -element is "<<
			pointPosition.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getPosition() methode from cPoint
	if ( pointPosition.getPosition() != NULL ){
	
		if ( vecPosition == *(pointPosition.getPosition()) ){
		
			cout<<"The point has the correct positionsvector. "<<endl;
		}else{
			cerr<<"Error: The point has a not the correct positionsvector. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The point has a no positionsvector (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cPoint
	if ( pointPosition.hasUnderAllObjects() == true ){
	
		cout<<"The pointelement has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The pointelement is missing a underobject."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cPoint with a superior fib -element"<<endl;

	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	
	cout<<"cPoint pointSup( NULL, &rootEmpty1 );"<<endl;
	cPoint pointSup( NULL, &rootEmpty1 );


	//check the getType() methode from cPoint
	if ( pointSup.getType() == 'p' ){
	
		cout<<"The type of the point -element is correctly 'p' . "<<endl;
	}else{
		cerr<<"Error: The type of the point -element is "<<
			pointSup.getType()<<" but should be 'p' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cPoint
	if ( pointSup.isValidFibElement() ){
	
		cout<<"The point -element is correctly a correct point -element. "<<endl;
	}else{
		cerr<<"Error: The point -element is not a valid point -element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cPoint
	if ( ! pointSup.isMovable() ){
	
		cout<<"The point -element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The point -element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cPoint
	if ( pointSup.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the point -element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the point -element is "<<
			pointSup.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cPoint
	if ( pointSup.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the point -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the point -element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cPoint
	if ( pointSup.getFibElement( -1 ) == &rootEmpty1 ){
	
		cout<<"The previous fib -element for the point -element is correctly rootEmpty1. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the point -element is not rootEmpty1."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cPoint
	if ( pointSup.getSuperiorFibElement() == &rootEmpty1 ){
	
		cout<<"The superior fib -element for the point -element is correctly rootEmpty1. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the point -element is "<<
			pointSup.getSuperiorFibElement() << " and not rootEmpty1."<<endl;
		iReturn++;
	}
	//check the getPosition() methode from cPoint
	if ( pointSup.getPosition() == NULL ){
	
		cout<<"The point has the correctly no positionsvector (NULL is given back). "<<endl;

	}else{
		cerr<<"Error: The point has a positionsvector. "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cPoint
	if ( pointSup.hasUnderAllObjects() == true ){
	
		cout<<"The pointelement has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The pointelement is missing a underobject."<<endl;
		iReturn++;
	}


#ifndef FEATURE_SIMPLE_CONSTRUCTOR
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cPoint with a next and previous fib -element"<<endl;
	
	cout<<"cPoint pointNextPrev( NULL, NULL, &pointPosition, &pointEmpty );"<<endl;
	cPoint pointNextPrev( NULL, NULL, &pointPosition, &pointEmpty );


	//check the getType() methode from cPoint
	if ( pointNextPrev.getType() == 'p' ){
	
		cout<<"The type of the point -element is correctly 'p' . "<<endl;
	}else{
		cerr<<"Error: The type of the point -element is "<<
			pointNextPrev.getType()<<" but should be 'p' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cPoint
	if ( pointNextPrev.isValidFibElement() ){
	
		cout<<"The point -element is correctly a correct point -element. "<<endl;
	}else{
		cerr<<"Error: The point -element is not a point -element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cPoint
	if ( ! pointNextPrev.isMovable() ){
	
		cout<<"The point -element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The point -element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cPoint
	if ( pointNextPrev.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the point -element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the point -element is "<<
			pointNextPrev.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cPoint
	if ( pointNextPrev.getNextFibElement() == &pointEmpty ){
	
		cout<<"The next/ main fib -element for the point -element is correctly pointEmpty. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the point -element is not pointEmpty."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cPoint
	if ( pointNextPrev.getFibElement( -1 ) == &pointPosition ){
	
		cout<<"The previous fib -element for the point -element is correctly pointPosition. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the point -element is not pointPosition."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cPoint
	if ( pointNextPrev.getSuperiorFibElement() == NULL){
	
		cout<<"The superior fib -element for the point -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the point -element is "<<
			pointNextPrev.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getPosition() methode from cPoint
	if ( pointNextPrev.getPosition() == NULL ){
	
		cout<<"The point has the correctly no positionsvector (NULL is given back). "<<endl;

	}else{
		cerr<<"Error: The point has a positionsvector. "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cPoint
	if ( pointNextPrev.hasUnderAllObjects() == true ){
	
		cout<<"The pointelement has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The pointelement is missing a underobject."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cPoint with all parameters given"<<endl;
	
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

	cout<<"cVectorPosition vecPositionE0( 0 );"<<endl;
	cVectorPosition vecPositionE0( 0 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint point1( &vecPositionE0, &rootD3 );"<<endl;
	cPoint point1( &vecPositionE0, &rootD3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint point1( &vecPositionE0, &rootD3, &pointPosition, &pointEmpty );"<<endl;
	cPoint point1( &vecPositionE0, &rootD3, &pointPosition, &pointEmpty );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	//check the getType() methode from cPoint
	if ( point1.getType() == 'p' ){
	
		cout<<"The type of the point -element is correctly 'p' . "<<endl;
	}else{
		cerr<<"Error: The type of the point -element is "<<
			point1.getType()<<" but should be 'p' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cPoint
	if ( point1.isValidFibElement() ){
	
		cout<<"The point -element is correctly a correct point -element. "<<endl;
	}else{
		cerr<<"Error: The point -element is not a point -element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cPoint
	if ( ! point1.isMovable() ){
	
		cout<<"The point -element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The point -element is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cPoint
	if ( point1.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the point -element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the point -element is "<<
			point1.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNextFibElement() methode from cPoint
	if ( point1.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the point -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the point -element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cPoint
	if ( point1.getFibElement( -1 ) == &rootD3 ){
	
		cout<<"The previous fib -element for the point -element is correctly rootD3. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the point -element is not rootD3."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNextFibElement() methode from cPoint
	if ( point1.getNextFibElement() == &pointEmpty ){
	
		cout<<"The next/ main fib -element for the point -element is correctly pointEmpty. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the point -element is not pointEmpty."<<endl;
		iReturn++;
	}
	//check the getFibElement() methode from cPoint
	if ( point1.getFibElement( -1 ) == &pointPosition ){
	
		cout<<"The previous fib -element for the point -element is correctly pointPosition. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the point -element is not pointPosition."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getSuperiorFibElement() methode from cPoint
	if ( point1.getSuperiorFibElement() == &rootD3 ){
	
		cout<<"The superior fib -element for the point -element is correctly rootD3. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the point -element is "<<
			point1.getSuperiorFibElement() << " and not rootD3."<<endl;
		iReturn++;
	}
	//check the getPosition() methode from cPoint
	if ( point1.getPosition() != NULL ){
	
		if ( vecPositionE0 == *(point1.getPosition()) ){
		
			cout<<"The point has the correct positionsvector vecPositionE0. "<<endl;
		}else{
			cerr<<"Error: The point has a not the correct positionsvector vecPositionE0. "<<endl;
			cerr<<"The positionsvector has "<< point1.getPosition()->getNumberOfElements() <<" elements. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The point has a no positionsvector (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cPoint
	if ( point1.hasUnderAllObjects() == true ){
	
		cout<<"The pointelement has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The pointelement is missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cPoint with a 3 D domain and a 2 D Positionsvector"<<endl;
	
	cout<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );
	cout<<"vecPositionE2.setValue( 1, 11.0 );"<<endl;
	vecPositionE2.setValue( 1, 11.0 );
	cout<<"vecPositionE2.setValue( 2, 2.0 );"<<endl;
	vecPositionE2.setValue( 2, 2.0 );

	cout<<"cVectorPosition vecPositionE3( 3 );"<<endl;
	cVectorPosition vecPositionE3( 3 );
	cout<<"vecPositionE3.setValue( 1, 1.0 );"<<endl;
	vecPositionE3.setValue( 1, 1.0 );
	cout<<"vecPositionE3.setValue( 2, 2.0 );"<<endl;
	vecPositionE3.setValue( 2, 2.0 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root2D3;"<<flush<<endl;
	cRoot root2D3;
	cout<<"root2D3.getDomains()->addDomain( testTypeDimensionD3, &vectorDomainD3 );"<<endl;
	root2D3.getDomains()->addDomain( testTypeDimensionD3, &vectorDomainD3 );
	
	cout<<"cPoint point2( &vecPositionE2, &root2D3 );"<<endl;
	cPoint point2( &vecPositionE2, &root2D3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint point2Pre( NULL, &rootD3, &rootD3, &pointEmpty );"<<endl;
	cPoint point2Pre( NULL, &rootD3, &rootD3, &pointEmpty );
	
	cout<<"cPoint point2( &vecPositionE2, &rootD3, &point2Pre, &pointEmpty );"<<endl;
	cPoint point2( &vecPositionE2, &rootD3, &point2Pre, &pointEmpty );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	//check the getType() methode from cPoint
	if ( point2.getType() == 'p' ){
	
		cout<<"The type of the point -element is correctly 'p' . "<<endl;
	}else{
		cerr<<"Error: The type of the point -element is "<<
			point2.getType()<<" but should be 'p' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cPoint
	if ( point2.isValidFibElement() ){
	
		cout<<"The point -element is correctly a correct point -element. "<<endl;
	}else{
		cerr<<"Error: The point -element is not a valid point -element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cPoint
	if ( ! point2.isMovable() ){
	
		cout<<"The point -element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The point -element is movebel."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNumberOfElement() methode from cPoint
	if ( point2.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the point -element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the point -element is "<<
			point2.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cPoint
	if ( point2.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the point -element is correctly pointEmpty. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the point -element is not pointEmpty."<<endl;
		iReturn++;
	}
	//check the getFibElement() methode from cPoint
	if ( point2.getFibElement( -1 ) == &root2D3 ){
	
		cout<<"The previous fib -element for the point -element is correctly root2D3. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the point -element is not root2D3."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cPoint
	if ( point2.getSuperiorFibElement() == &root2D3 ){
	
		cout<<"The superior fib -element for the point -element is correctly root2D3. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the point -element is "<<
			point2.getSuperiorFibElement() << " and not root2D3."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNumberOfElement() methode from cPoint
	if ( point2.getNumberOfElement() == 3 ){
	
		cout<<"The number of the fib -element for the point -element is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the point -element is "<<
			point2.getNumberOfElement() <<", but should be 3."<<endl;
		iReturn++;
	}

	//check the getNextFibElement() methode from cPoint
	if ( point2.getNextFibElement() == &pointEmpty ){
	
		cout<<"The next/ main fib -element for the point -element is correctly pointEmpty. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the point -element is not pointEmpty."<<endl;
		iReturn++;
	}
	//check the getFibElement() methode from cPoint
	if ( point2.getFibElement( -1 ) == &point2Pre ){
	
		cout<<"The previous fib -element for the point -element is correctly point2Pre. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the point -element is not point2Pre."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cPoint
	if ( point2.getSuperiorFibElement() == &rootD3 ){
	
		cout<<"The superior fib -element for the point -element is correctly rootD3. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the point -element is "<<
			point2.getSuperiorFibElement() << " and not rootD3."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getPosition() methode from cPoint
	if ( point2.getPosition() != NULL ){
	
		if ( vecPositionE3 == *(point2.getPosition()) ){
		
			cout<<"The point has the correct positionsvector vecPositionE3. "<<endl;
		}else{
			cerr<<"Error: The point has a not the correct positionsvector vecPositionE3. "<<endl;
			cerr<<"The positionsvector has "<< point2.getPosition()->getNumberOfElements() <<" elements. "<<endl;
			/*check the elements of the positionsvektor*/
			for ( unsignedIntFib uiActualElement = 1;
					uiActualElement <= point2.getPosition()->getNumberOfElements();
					uiActualElement++ ){
				
				if ( ! point2.getPosition()->isVariable( uiActualElement ) ){
				
					cout<<"The "<<uiActualElement<<"'th element of the "<<
						"positionsvector is correctly not an variable. "<<endl;
				}else{
					cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
						"positionsvector is an variable. "<<endl;
					iReturn++;
				}
				if ( point2.getPosition()->getValue( uiActualElement ) ==
						vecPositionE3.getValue( uiActualElement ) ){
				
					cout<<"The "<<uiActualElement<<"'th element of the "<<
						"positionsvector is correctly "<<
						vecPositionE3.getValue( uiActualElement ) <<" . "<<endl;
				}else{
					cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
						"positionsvector is "<<point2.getPosition()->getValue( uiActualElement )<<
						" and not "<<
						vecPositionE3.getValue( uiActualElement ) <<" . "<<endl;
					iReturn++;
				}
			}
			iReturn++;
		}
	}else{
		cerr<<"Error: The point has a no positionsvector (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cPoint
	if ( point2.hasUnderAllObjects() == true ){
	
		cout<<"The pointelement has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The pointelement is missing a underobject."<<endl;
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
 * This method tests the constructor of the cPoint class.
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

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint with 2 dimensional positionsvector"<<endl;

	cout<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );
	cout<<"vecPositionE2.setValue( 1, 4 );"<<endl;
	vecPositionE2.setValue( 1, 4 );
	cout<<"vecPositionE2.setValue( 2, 7 );"<<endl;
	vecPositionE2.setValue( 2, 7 );

	cout<<"cPoint pointPosition( & vecPositionE2 );"<<endl;
	cPoint pointPosition( & vecPositionE2 );
	unsigned int uiTimeNeeded = 3;

	//check the getTimeNeed() methode from cPoint
	if ( pointPosition.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			pointPosition.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cPoint
	if ( pointPosition.getTimeNeed( 2 ) == 2 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 2 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			pointPosition.getTimeNeed( 2 ) <<", but should be "<< 2 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"list<cVectorProperty> liVecProperties;"<<endl;
	list<cVectorProperty> liVecProperties;
	unsigned int uiPointsToEvalue = 1;
	
	list< pair< const cVectorPosition*, list<cVectorProperty> > > liPointsToEvalue;
	liPointsToEvalue.push_back( make_pair( &vecPositionE2, list<cVectorProperty>() ) );
	cEvaluePositionList evaluePositionList;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"pointPosition.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bool bObjectEvalued = pointPosition.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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
	
	list< pair< const cFibElement*, list<cVectorProperty> > > liFibElementsToEvalue;
	liFibElementsToEvalue.push_back( make_pair( & pointPosition, list<cVectorProperty>() ) );
	cEvalueFibElementList evalueFibElementList;
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;

	cout<<"pointPosition.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPosition.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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
	
	
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.liEvaluedElementData.clear();
	cout<<"pointPosition.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = pointPosition.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint with a propertylist given"<<endl;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	
	cout<<"cVectorProperty vecPropertyColorRgb1( 1 );"<<endl;
	cVectorProperty vecPropertyColorRgb1( 1 );
	
	cout<<"vecPropertyColorRgb1.setValue( 1, 5 );"<<endl;
	vecPropertyColorRgb1.setValue( 1, 5 );
	cout<<"vecPropertyColorRgb1.setValue( 2, 3 );"<<endl;
	vecPropertyColorRgb1.setValue( 2, 3 );
	
	cout<<"liVecProperties.push_back( vecPropertyColorRgb1 );"<<endl;
	liVecProperties.push_back( vecPropertyColorRgb1 );
	
	cout<<"cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );
	cout<<"vecPropertyLayer.setValue( 1, 2 );"<<endl;
	vecPropertyLayer.setValue( 1, 2 );

	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );


	liPointsToEvalue.clear();
	liPointsToEvalue.push_back( make_pair( &vecPositionE2, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorRgb1 );
	liPointsToEvalue.back().second.push_back( vecPropertyLayer );
	
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( & pointPosition, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorRgb1 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyLayer );


	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	cout<<"pointPosition.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = pointPosition.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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


	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.liEvaluedElementData.clear();
	cout<<"pointPosition.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPosition.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint for non existing object point 1"<<endl;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	cout<<"pointPosition.evalueObject( evaluePositionList, 1,  liVecProperties );"<<endl;
	bObjectEvalued = pointPosition.evalueObject( evaluePositionList, 1,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The property was correctly not evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );


	liFibElementsToEvalue.clear();
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"pointPosition.evalueObject( evalueFibElementList, 1,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPosition.evalueObject( evalueFibElementList, 1,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The property was correctly not evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint when returnvalue is false"<<endl;

	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	cout<<"pointPosition.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = pointPosition.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The point was correctly evalued. with result false "<<endl;
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
	cout<<"pointPosition.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPosition.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The point was correctly evalued. with result false "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint with differnt elements to evalue"<<endl;

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( & pointPosition, list<cVectorProperty>() ) );

	cout<<"liCFibElementTyps.push_back( 'p' );"<<endl;
	liCFibElementTyps.push_back( 'p' );
	cout<<"pointPosition.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPosition.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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
	cout<<"pointPosition.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPosition.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint with 0 dimensional positionsvector"<<endl;

	cout<<"cVectorPosition vecPositionE0( 0 );"<<endl;
	cVectorPosition vecPositionE0( 0 );

	cout<<"cPoint pointPositionE0E0( & vecPositionE0 );"<<endl;
	cPoint pointPositionE0( & vecPositionE0 );
	uiTimeNeeded = 1;

	//check the getTimeNeed() methode from cPoint
	if ( pointPositionE0.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			pointPositionE0.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.push_back( make_pair( & vecPositionE0, list<cVectorProperty>() ) );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"pointPositionE0.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = pointPositionE0.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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
	liFibElementsToEvalue.push_back( make_pair( & pointPositionE0, list<cVectorProperty>() ) );
	
	cout<<"pointPositionE0.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPositionE0.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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
	cout<<"pointPositionE0.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = pointPositionE0.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint with a propertylist given"<<endl;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyColorRgb1 );"<<endl;
	liVecProperties.push_back( vecPropertyColorRgb1 );
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	
	liPointsToEvalue.clear();
	liPointsToEvalue.push_back( make_pair( &vecPositionE0, liVecProperties ) );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	
	cout<<"pointPositionE0.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = pointPositionE0.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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


	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( & pointPositionE0, liVecProperties ) );
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.liEvaluedElementData.clear();
	
	cout<<"pointPositionE0.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPositionE0.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint for non existing object point 1"<<endl;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	
	cout<<"pointPositionE0.evalueObject( evaluePositionList, 1,  liVecProperties );"<<endl;
	bObjectEvalued = pointPositionE0.evalueObject( evaluePositionList, 1,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The property was correctly not evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );


	liFibElementsToEvalue.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.liEvaluedElementData.clear();
	cout<<"pointPositionE0.evalueObject( evalueFibElementList, 1,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPositionE0.evalueObject( evalueFibElementList, 1,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The property was correctly not evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evalueFibElementList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint when returnvalue is false"<<endl;

	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	
	cout<<"pointPositionE0.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = pointPositionE0.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The point was correctly evalued. with result false "<<endl;
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


	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 0;
	evalueFibElementList.liEvaluedElementData.clear();
	cout<<"pointPositionE0.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPositionE0.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The point was correctly evalued. with result false "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
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


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint with 3 dimensional positionsvector"<<endl;

	cout<<"cVectorPosition vecPositionE3( 3 );"<<endl;
	cVectorPosition vecPositionE3( 3 );

	cout<<"cPoint pointPositionE3( & vecPositionE3 );"<<endl;
	cPoint pointPositionE3( & vecPositionE3 );
	uiTimeNeeded = 4;

	//check the getTimeNeed() methode from cPoint
	if ( pointPositionE3.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			pointPositionE3.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.push_back( make_pair( &vecPositionE3, list<cVectorProperty>() ) );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"pointPositionE3.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = pointPositionE3.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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
	
	liFibElementsToEvalue.push_back( make_pair( & pointPositionE3, list<cVectorProperty>() ) );
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"pointPositionE3.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPositionE3.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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

	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.liEvaluedElementData.clear();
	
	cout<<"pointPositionE3.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = pointPositionE3.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint with a propertylist given"<<endl;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyColorRgb1 );"<<endl;
	liVecProperties.push_back( vecPropertyColorRgb1 );
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	
	liPointsToEvalue.clear();
	liPointsToEvalue.push_back( make_pair( & vecPositionE3, liVecProperties ) );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	
	cout<<"pointPositionE3.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = pointPositionE3.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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


	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( & pointPositionE3, liVecProperties ) );
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.liEvaluedElementData.clear();
	
	cout<<"pointPositionE3.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPositionE3.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
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

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint for non existing object point 1"<<endl;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	cout<<"pointPositionE3.evalueObject( evaluePositionList, 1,  liVecProperties );"<<endl;
	bObjectEvalued = pointPositionE3.evalueObject( evaluePositionList, 1,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The property was correctly not evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );


	liFibElementsToEvalue.clear();
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	cout<<"pointPositionE3.evalueObject( evalueFibElementList, 1,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPositionE3.evalueObject( evalueFibElementList, 1,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The property was correctly not evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint when returnvalue is false"<<endl;

	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	cout<<"pointPositionE3.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = pointPositionE3.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The point was correctly evalued. with result false "<<endl;
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
	cout<<"pointPositionE3.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPositionE3.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The point was correctly evalued. with result false "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint with no positionsvector"<<endl;

	cout<<"cPoint pointPositionEmpty;"<<endl;
	cPoint pointPositionEmpty;
	uiTimeNeeded = 1;

	//check the getTimeNeed() methode from cPoint
	if ( pointPositionEmpty.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			pointPositionEmpty.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"pointPositionEmpty.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = pointPositionEmpty.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			0 <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );


	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	liFibElementsToEvalue.clear();
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"pointPositionEmpty.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPositionEmpty.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			0 <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"pointPositionEmpty.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = pointPositionEmpty.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			0 <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint with a propertylist given"<<endl;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyColorRgb1 );"<<endl;
	liVecProperties.push_back( vecPropertyColorRgb1 );
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	cout<<"pointPositionEmpty.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = pointPositionEmpty.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			0 <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );


	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.liEvaluedElementData.clear();
	cout<<"pointPositionEmpty.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPositionEmpty.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			0 <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evalueFibElementList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint for non existing object point 1"<<endl;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	cout<<"pointPositionEmpty.evalueObject( evaluePositionList, 1,  liVecProperties );"<<endl;
	bObjectEvalued = pointPositionEmpty.evalueObject( evaluePositionList, 1,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The property was correctly not evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			0 <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.liEvaluedElementData.clear();
	cout<<"pointPositionEmpty.evalueObject( evalueFibElementList, 1,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPositionEmpty.evalueObject( evalueFibElementList, 1,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The property was correctly not evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			0 <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cPoint when returnvalue is false"<<endl;

	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	cout<<"pointPositionEmpty.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = pointPositionEmpty.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			0 <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.lNumberOfTrueEvalueCalls = 0;
	cout<<"pointPositionEmpty.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = pointPositionEmpty.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The point was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == 0 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			0 <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			0 <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );


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
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
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
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
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

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing equal methods for root -elements"<<endl;

	cout<<endl<<"Creating pointobjects objects to compare: "<<endl<<endl;
	
	cout<<"cPoint poinEmpty1;"<<endl;
	cPoint poinEmpty1;

	cout<<"cPoint poinEmpty2;"<<endl;
	cPoint poinEmpty2;

	//point with 0 D Positionsvector
	cout<<"cVectorPosition vecPositionE0( 0 );"<<endl;
	cVectorPosition vecPositionE0( 0 );
	cout<<"cPoint pointE0( & vecPositionE0 );"<<endl;
	cPoint pointE0( & vecPositionE0 );

	//point with 2 D Positionsvector
	cout<<"cVectorPosition vecPosition1E2( 2 );"<<endl;
	cVectorPosition vecPosition1E2( 2 );
	cout<<"cPoint point1E2( & vecPosition1E2 );"<<endl;
	cPoint point1E2( & vecPosition1E2 );
	
	cout<<"cVectorPosition vecPosition1E2Ch( 2 );"<<endl;
	cVectorPosition vecPosition1E2Ch( 2 );
	cout<<"vecPosition1E2Ch.setValue( 1, 4);"<<endl;
	vecPosition1E2Ch.setValue( 1, 4);
	cout<<"cPoint point1E2Ch( & vecPosition1E2Ch );"<<endl;
	cPoint point1E2Ch( & vecPosition1E2Ch );

	cout<<"cVectorPosition vecPosition2E2Ch( 2 );"<<endl;
	cVectorPosition vecPosition2E2Ch( 2 );
	cout<<"vecPosition2E2Ch.setValue( 2, 4);"<<endl;
	vecPosition2E2Ch.setValue( 2, 4);
	cout<<"cPoint point2E2Ch( & vecPosition2E2Ch );"<<endl;
	cPoint point2E2Ch( & vecPosition2E2Ch );

	//point with 3 D Positionsvector
	cout<<"cVectorPosition vecPosition1E3( 3 );"<<endl;
	cVectorPosition vecPosition1E3( 3 );
	cout<<"cPoint point1E3( & vecPosition1E3 );"<<endl;
	cPoint point1E3( & vecPosition1E3 );
	
	cout<<"cVectorPosition vecPosition1E3Ch( 3 );"<<endl;
	cVectorPosition vecPosition1E3Ch( 3 );
	cout<<"vecPosition1E3Ch.setValue( 1, 4);"<<endl;
	vecPosition1E3Ch.setValue( 1, 4);
	cout<<"cPoint point1E3Ch( & vecPosition1E3Ch );"<<endl;
	cPoint point1E3Ch( & vecPosition1E3Ch );

	cout<<"cVectorPosition vecPosition2E3Ch( 3 );"<<endl;
	cVectorPosition vecPosition2E3Ch( 3 );
	cout<<"vecPosition2E3Ch.setValue( 2, 4);"<<endl;
	vecPosition2E3Ch.setValue( 2, 4);
	cout<<"cPoint point2E3Ch( & vecPosition2E3Ch );"<<endl;
	cPoint point2E3Ch( & vecPosition2E3Ch );


	//point with supperior element
	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	
	cout<<"cPoint pointSup( NULL, &rootEmpty1 );"<<endl;
	cPoint pointSup( NULL, &rootEmpty1 );

	//point in fib -element structur
	cout<<"cPoint poinPrev;"<<endl;
	cPoint poinPrev;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//point with supperior element
	cout<<"cRoot rootEmpty2;"<<endl;
	cRoot rootEmpty2;
	cout<<"cRoot rootP;"<<endl;
	cRoot rootP;
	cout<<"rootP.addSubRootObject( 1, &rootEmpty2 );"<<endl;
	rootP.addSubRootObject( 1, &rootEmpty2 );
	
	cout<<"cPoint pointNextPrev( NULL, &rootP );"<<endl;
	cPoint pointNextPrev( NULL, &rootP );

#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;
	cout<<"cPoint pointNextPrev( NULL, NULL, &poinPrev, &poinNext );"<<endl;
	cPoint pointNextPrev( NULL, NULL, &poinPrev, &poinNext );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeDimension testTypeDimensionD2( 2 );"<<endl;
	cTypeDimension testTypeDimensionD2( 2 );
	cout<<"testTypeDimensionD2.setDimensionMapping( 1, 4 )"<<endl;
	testTypeDimensionD2.setDimensionMapping( 1, 4 );
	cout<<"testTypeDimensionD2.setDimensionMapping( 2, 1 )"<<endl;
	testTypeDimensionD2.setDimensionMapping( 2, 1 );
	
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

	cout<<"rootD2.getDomains()->addDomain( testTypeDimensionD2, &vectorDomainD2 );"<<endl;
	rootD2.getDomains()->addDomain( testTypeDimensionD2, &vectorDomainD2 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint point2E2( &vecPosition1E2, &rootD2 );"<<endl;
	cPoint point2E2( &vecPosition1E2, &rootD2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint point2E2( &vecPosition1E2, &rootD2, &poinPrev, &poinNext );"<<endl;
	cPoint point2E2( &vecPosition1E2, &rootD2, &poinPrev, &poinNext );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with poinEmpty1
	cFibElement *actualObject = & poinEmpty1;
	string szActualObjectName = "poinEmpty1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, poinEmpty1, "poinEmpty1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, poinEmpty2, "poinEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointE0, "pointE0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2, "point1E2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2Ch, "point1E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2Ch, "point2E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3, "point1E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3Ch, "point1E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E3Ch, "point2E3Ch" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, pointSup, "pointSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, pointNextPrev, "pointNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2, "point2E2" );

	//compare with poinEmpty2
	actualObject = & poinEmpty2;
	szActualObjectName = "poinEmpty2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, poinEmpty1, "poinEmpty1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, poinEmpty2, "poinEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointE0, "pointE0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2, "point1E2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2Ch, "point1E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2Ch, "point2E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3, "point1E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3Ch, "point1E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E3Ch, "point2E3Ch" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, pointSup, "pointSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, pointNextPrev, "pointNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2, "point2E2" );

	//compare with pointE0
	actualObject = & pointE0;
	szActualObjectName = "pointE0";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty1, "poinEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty2, "poinEmpty2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, pointE0, "pointE0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2, "point1E2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2Ch, "point1E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2Ch, "point2E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3, "point1E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3Ch, "point1E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E3Ch, "point2E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointSup, "pointSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointNextPrev, "pointNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2, "point2E2" );

	//compare with point1E2
	actualObject = & point1E2;
	szActualObjectName = "point1E2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty1, "poinEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty2, "poinEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointE0, "pointE0" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, point1E2, "point1E2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2Ch, "point1E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2Ch, "point2E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3, "point1E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3Ch, "point1E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E3Ch, "point2E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointSup, "pointSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointNextPrev, "pointNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, point2E2, "point2E2" );

	//compare with point1E2Ch
	actualObject = & point1E2Ch;
	szActualObjectName = "point1E2Ch";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty1, "poinEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty2, "poinEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointE0, "pointE0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2, "point1E2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, point1E2Ch, "point1E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2Ch, "point2E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3, "point1E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3Ch, "point1E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E3Ch, "point2E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointSup, "pointSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointNextPrev, "pointNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2, "point2E2" );

	//compare with point2E2Ch
	actualObject = & point2E2Ch;
	szActualObjectName = "point2E2Ch";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty1, "poinEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty2, "poinEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointE0, "pointE0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2, "point1E2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2Ch, "point1E2Ch" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, point2E2Ch, "point2E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3, "point1E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3Ch, "point1E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E3Ch, "point2E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointSup, "pointSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointNextPrev, "pointNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2, "point2E2" );

	//compare with point1E3
	actualObject = & point1E3;
	szActualObjectName = "point1E3";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty1, "poinEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty2, "poinEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointE0, "pointE0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2, "point1E2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2Ch, "point1E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2Ch, "point2E2Ch" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, point1E3, "point1E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3Ch, "point1E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E3Ch, "point2E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointSup, "pointSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointNextPrev, "pointNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2, "point2E2" );

	//compare with point1E3Ch
	actualObject = & point1E3Ch;
	szActualObjectName = "point1E3Ch";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty1, "poinEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty2, "poinEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointE0, "pointE0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2, "point1E2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2Ch, "point1E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2Ch, "point2E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3, "point1E3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, point1E3Ch, "point1E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E3Ch, "point2E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointSup, "pointSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointNextPrev, "pointNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2, "point2E2" );

	//compare with point2E3Ch
	actualObject = & point2E3Ch;
	szActualObjectName = "point2E3Ch";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty1, "poinEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty2, "poinEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointE0, "pointE0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2, "point1E2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2Ch, "point1E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2Ch, "point2E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3, "point1E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3Ch, "point1E3Ch" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, point2E3Ch, "point2E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointSup, "pointSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointNextPrev, "pointNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2, "point2E2" );

	//compare with pointSup
	actualObject = & pointSup;
	szActualObjectName = "pointSup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, poinEmpty1, "poinEmpty1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, poinEmpty2, "poinEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointE0, "pointE0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2, "point1E2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2Ch, "point1E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2Ch, "point2E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3, "point1E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3Ch, "point1E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E3Ch, "point2E3Ch" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, pointSup, "pointSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, pointNextPrev, "pointNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2, "point2E2" );

	//compare with pointNextPrev
	actualObject = & pointNextPrev;
	szActualObjectName = "pointNextPrev";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, poinEmpty1, "poinEmpty1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, poinEmpty2, "poinEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointE0, "pointE0" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2, "point1E2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2Ch, "point1E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2Ch, "point2E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3, "point1E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3Ch, "point1E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E3Ch, "point2E3Ch" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, pointSup, "pointSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, pointNextPrev, "pointNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2, "point2E2" );

	//compare with point2E2
	actualObject = & point2E2;
	szActualObjectName = "point2E2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty1, "poinEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, poinEmpty2, "poinEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointE0, "pointE0" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, point1E2, "point1E2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E2Ch, "point1E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E2Ch, "point2E2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3, "point1E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point1E3Ch, "point1E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, point2E3Ch, "point2E3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointSup, "pointSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, pointNextPrev, "pointNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, point2E2, "point2E2" );


	return iReturn;
}



/**
 * This method tests the equal() method of two given fib -objects which are
 * equal.
 * It also compares the superior, next and previous fib -element pointers.
 *
 * @param fibObject1 the first fib -object to compare
 * @param szNameObject1 the name of the first fib -object to compare
 * @param fibObject2 the secound fib -object to compare to
 * @param szNameObject2 the name of the secound fib -object to compare
 * @param bCheckPreviousPointer is true (standard) the previous
 * 	fib-element will be checked
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualObjectsStructur(
		const cFibElement &fibObject1, const string &szNameObject1,
		const cFibElement &fibObject2, const string &szNameObject2,
		bool bCheckPreviousPointer = true ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	iReturn += testCompareTwoEqualObjects( fibObject1, szNameObject1, fibObject2, szNameObject2 );
	
	//check the getNextFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getNextFibElement() ==
			const_cast<cFibElement*>(&fibObject2)->getNextFibElement() ){
	
		cout<<"The next/ main fib -elementpointer for the point -elements are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -elementpointer for the point -elements are not equal."<<endl;
		iReturn++;
	}
	if ( bCheckPreviousPointer ){
		//check the getFibElement() methode from cPoint
		if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) ==
				const_cast<cFibElement*>(&fibObject2)->getFibElement( -1 ) ){
		
			cout<<"The previous fib -elementpointer for the point -elements are correctly equal. "<<endl;
		}else{
			cerr<<"Error: The previous fib -elementpointer for the point -elements are not equal."<<endl;
			iReturn++;
		}
	}
	//check the getSuperiorFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() ==
			const_cast<cFibElement*>(&fibObject2)->getSuperiorFibElement() ){
	
		cout<<"The superior fib -elementpointer for the point -elements are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the point -elements are not equal."<<endl;
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
 * This method tests the copy methods and copyconstructor of the cPoint class.
 *
 * methods tested:
 * 	- cPoint( const cPoint &pointElement );
 * 	- cFibElement *clone( ) const;
 * 	- cPoint *copy( const unsignedIntFib iObjectPoint=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementPoint=0 ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a empty cPoint"<<endl;

	cout<<"cPoint pointEmpty;"<<endl;
	cPoint pointEmpty;

	cout<<"cPoint pointEmptyCopyConstruct( pointEmpty );"<<endl;
	cPoint pointEmptyCopyConstruct( pointEmpty );

	iReturn += testCompareTwoEqualObjectsStructur( pointEmptyCopyConstruct, "pointEmptyCopyConstruct", pointEmpty, "pointEmpty" );

	cout<<"cFibElement * pPointEmptyClone = pointEmpty.clone();"<<endl;
	cFibElement * pPointEmptyClone = pointEmpty.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pPointEmptyClone, "pPointEmptyClone", pointEmpty, "pointEmpty" );
	delete pPointEmptyClone;

	cout<<"cFibElement * pPointEmptyCopy = pointEmpty.copy();"<<endl;
	cFibElement * pPointEmptyCopy = pointEmpty.copy();

	iReturn += testCompareTwoEqualObjectsStructur( *pPointEmptyCopy, "pPointEmptyCopy", pointEmpty, "pointEmpty" );
	delete pPointEmptyCopy;

	cout<<"cFibElement * pPointEmptyCopyElement = pointEmpty.copyElement();"<<endl;
	cFibElement * pPointEmptyCopyElement = pointEmpty.copyElement();

	if ( pointEmpty.equalElement( *pPointEmptyCopyElement ) ){
	
		cout<<"The pointEmpty fib -element is equal to pPointEmptyCopyElement. "<<endl;
	}else{
		cerr<<"Error: The pointEmpty fib -element is not equal to pPointEmptyCopyElement."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pPointEmptyCopyElement );
	delete pPointEmptyCopyElement;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying for a other object or elementpoint"<<endl;

	cout<<"cFibElement * pPointEmptyNoCopy = pointEmpty.copy( 1 );"<<endl;
	cFibElement * pPointEmptyNoCopy = pointEmpty.copy( 1 );

	if ( pPointEmptyNoCopy == NULL ){
	
		cout<<"The cPoint was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cPoint was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pPointEmptyNoCopy;
	}

	cout<<"cFibElement * pPointEmptyNoCopyElement = pointEmpty.copyElement( 'p', 2 );"<<endl;
	cFibElement * pPointEmptyNoCopyElement = pointEmpty.copyElement( 'p', 2 );

	if ( pPointEmptyNoCopyElement == NULL ){
	
		cout<<"The cPoint -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cPoint -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pPointEmptyNoCopyElement;
	}

	cout<<"pPointEmptyNoCopyElement = pointEmpty.copyElement( 'u', 2 );"<<endl;
	pPointEmptyNoCopyElement = pointEmpty.copyElement( 'u', 2 );

	if ( pPointEmptyNoCopyElement == NULL ){
	
		cout<<"The cPoint -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cPoint -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pPointEmptyNoCopyElement;
	}

	cout<<"pPointEmptyNoCopyElement = pointEmpty.copyElement( 'r', 1 );"<<endl;
	pPointEmptyNoCopyElement = pointEmpty.copyElement( 'r', 1 );

	if ( pPointEmptyNoCopyElement == NULL ){
	
		cout<<"The cPoint -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cPoint -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pPointEmptyNoCopyElement;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cPoint with a positionsvector with 0 elements"<<endl;

	//point with 0 D Positionsvector
	cout<<"cVectorPosition vecPositionE0( 0 );"<<endl;
	cVectorPosition vecPositionE0( 0 );
	cout<<"cPoint pointE0( & vecPositionE0 );"<<endl;
	cPoint pointE0( & vecPositionE0 );

	cout<<"cPoint pointE0CopyConstruct( pointE0 );"<<endl;
	cPoint pointE0CopyConstruct( pointE0 );

	iReturn += testCompareTwoEqualObjectsStructur( pointE0CopyConstruct, "pointE0CopyConstruct", pointE0, "pointE0" );

	cout<<"cFibElement * pPointE0Clone = pointE0.clone();"<<endl;
	cFibElement * pPointE0Clone = pointE0.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pPointE0Clone, "pPointE0Clone", pointE0, "pointE0" );
	delete pPointE0Clone;

	cout<<"cFibElement * pPointE0Copy = pointE0.copy( 0 );"<<endl;
	cFibElement * pPointE0Copy = pointE0.copy( 0 );

	iReturn += testCompareTwoEqualObjectsStructur( *pPointE0Copy, "pPointE0Copy", pointE0, "pointE0" );
	delete pPointE0Copy;

	cout<<"cFibElement * pPointE0CopyElement = pointE0.copyElement( 0 );"<<endl;
	cFibElement * pPointE0CopyElement = pointE0.copyElement( 0 );

	if ( pointE0.equalElement( *pPointE0CopyElement ) ){
	
		cout<<"The pPointE0CopyElement fib -element is equal to pointE0. "<<endl;
	}else{
		cerr<<"Error: The pPointE0CopyElement fib -element is not equal to pointE0."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pPointE0CopyElement );
	delete pPointE0CopyElement;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cPoint with a positionsvector with 2 elements"<<endl;

	//point with 2 D Positionsvector
	cout<<"cVectorPosition vecPosition1E2Ch( 2 );"<<endl;
	cVectorPosition vecPosition1E2Ch( 2 );
	cout<<"vecPosition1E2Ch.setValue( 1, 4);"<<endl;
	vecPosition1E2Ch.setValue( 1, 4);
	cout<<"vecPosition1E2Ch.setValue( 2, 9);"<<endl;
	vecPosition1E2Ch.setValue( 2, 9);
	cout<<"cPoint pointE2( & vecPosition1E2Ch );"<<endl;
	cPoint pointE2( & vecPosition1E2Ch );

	cout<<"cPoint pointE2CopyConstruct( pointE2 );"<<endl;
	cPoint pointE2CopyConstruct( pointE2 );

	if ( pointE2.equalElement( pointE2CopyConstruct ) ){
	
		cout<<"The pointE2CopyConstruct fib -element is equal to pointE2. "<<endl;
	}else{
		cerr<<"Error: The pointE2CopyConstruct fib -element is not equal to pointE2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( pointE2CopyConstruct );

	cout<<"cFibElement * pPointE2Clone = pointE2.clone();"<<endl;
	cFibElement * pPointE2Clone = pointE2.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pPointE2Clone, "pPointE2Clone", pointE2, "pointE2" );
	delete pPointE2Clone;

	cout<<"cFibElement * pPointE2Copy = pointE2.copy();"<<endl;
	cFibElement * pPointE2Copy = pointE2.copy();

	iReturn += testCompareTwoEqualObjectsStructur( *pPointE2Copy, "pPointE2Copy", pointE2, "pointE2" );
	delete pPointE2Copy;

	cout<<"cFibElement * pPointE2CopyElement = pointE2.copyElement( 'p', 1 );"<<endl;
	cFibElement * pPointE2CopyElement = pointE2.copyElement( 'p', 1 );

	if ( pointE2.equalElement( *pPointE2CopyElement ) ){
	
		cout<<"The pPointE2CopyElement fib -element is equal to pointE2. "<<endl;
	}else{
		cerr<<"Error: The pPointE2CopyElement fib -element is not equal to pointE2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pPointE2CopyElement );
	delete pPointE2CopyElement;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cPoint with a positionsvector with 3 elements"<<endl;

	//point with 3 D Positionsvector
	cout<<"cVectorPosition vecPosition1E3Ch( 3 );"<<endl;
	cVectorPosition vecPosition1E3Ch( 3 );
	cout<<"vecPosition1E3Ch.setValue( 1, 4);"<<endl;
	vecPosition1E3Ch.setValue( 1, 4);
	cout<<"vecPosition1E3Ch.setValue( 2, 3);"<<endl;
	vecPosition1E3Ch.setValue( 2, 3);
	cout<<"vecPosition1E3Ch.setValue( 3, 2);"<<endl;
	vecPosition1E3Ch.setValue( 3, 2);
	cout<<"cPoint pointE3( & vecPosition1E3Ch );"<<endl;
	cPoint pointE3( & vecPosition1E3Ch );

	cout<<"cPoint pointE3CopyConstruct( pointE3 );"<<endl;
	cPoint pointE3CopyConstruct( pointE3 );

	if ( pointE3.equalElement( pointE3CopyConstruct ) ){
	
		cout<<"The pointE3CopyConstruct fib -element is equal to pointE3. "<<endl;
	}else{
		cerr<<"Error: The pointE3CopyConstruct fib -element is not equal to pointE3."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( pointE3CopyConstruct );

	cout<<"cFibElement * pPointE3Clone = pointE3.clone();"<<endl;
	cFibElement * pPointE3Clone = pointE3.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pPointE3Clone, "pPointE3Clone", pointE3, "pointE3" );
	delete pPointE3Clone;

	cout<<"cFibElement * pPointE3Copy = pointE3.copy();"<<endl;
	cFibElement * pPointE3Copy = pointE3.copy();

	iReturn += testCompareTwoEqualObjectsStructur( *pPointE3Copy, "pPointE3Copy", pointE3, "pointE3" );
	delete pPointE3Copy;

	cout<<"cFibElement * pPointE3CopyElement = pointE3.copyElement();"<<endl;
	cFibElement * pPointE3CopyElement = pointE3.copyElement();

	if ( pointE3.equalElement( *pPointE3CopyElement ) ){
	
		cout<<"The pPointE3CopyElement fib -element is equal to pointE3. "<<endl;
	}else{
		cerr<<"Error: The pPointE3CopyElement fib -element is not equal to pointE3."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pPointE3CopyElement );
	delete pPointE3CopyElement;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cPoint with all members set"<<endl;


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
	cout<<"cPoint point2E2( &vecPosition1E2Ch, &rootD3 );"<<endl;
	cPoint point2E2( &vecPosition1E2Ch, &rootD3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//point in fib -element structur
	cout<<"cPoint poinPrev;"<<endl;
	cPoint poinPrev;
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;
	
	cout<<"cPoint point2E2( &vecPosition1E2Ch, &rootD3, &poinPrev, &poinNext );"<<endl;
	cPoint point2E2( &vecPosition1E2Ch, &rootD3, &poinPrev, &poinNext );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	cout<<"cPoint point2E2CopyConstruct( point2E2 );"<<endl;
	cPoint point2E2CopyConstruct( point2E2 );

	if ( point2E2.equalElement( point2E2CopyConstruct ) ){
	
		cout<<"The point2E2CopyConstruct fib -element is equal to point2E2. "<<endl;
	}else{
		cerr<<"Error: The point2E2CopyConstruct fib -element is not equal to point2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( point2E2CopyConstruct );

	cout<<"cFibElement * pPoint2E2Copy = point2E2.copy();"<<endl;
	cFibElement * pPoint2E2Copy = point2E2.copy();

	if ( point2E2.equal( *pPoint2E2Copy ) ){
	
		cout<<"The pPoint2E2Copy fib -object is equal to point2E2. "<<endl;
	}else{
		cerr<<"Error: The pPoint2E2Copy fib -object is not equal to point2E2."<<endl;
		iReturn++;
	}
	delete pPoint2E2Copy;

	cout<<"cFibElement * pPoint2E2CopyElement = point2E2.copyElement( 'u', 1 );"<<endl;
	cFibElement * pPoint2E2CopyElement = point2E2.copyElement( 'u', 1 );

	if ( point2E2.equalElement( *pPoint2E2CopyElement ) ){
	
		cout<<"The pPoint2E2CopyElement fib -element is equal to point2E2. "<<endl;
	}else{
		cerr<<"Error: The pPoint2E2CopyElement fib -element is not equal to point2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pPoint2E2CopyElement );
	delete pPoint2E2CopyElement;


	return iReturn;
}



/**
 * This method tests a in the xml -format stored cFibVector.
 *
 * @param szFilename the name of the file wher the cFibVector is stored
 * @param szPointName the name of point (point or background)
 * @param uiVectorElements the number of elements in the vector
 * @param vecElementType a vector with the typs of the vectorelements
 * 	(w=value; v=variable, u=undefined)
 * @param vecValues the values of the vectorelements
 * @return the number of errors occured in the test
 */
int testXmlPoint( const string szFilename, const string szPointName,
		bool bHasVector, unsigned int uiVectorElements, vector<char> vecElementType,
		vector<double> vecValues ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cPoint:"<<endl;
	
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

		if ( szElementName == szPointName ){
			cout<<"The root element is correctly named \""<< szPointName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szPointName <<"\"."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	xmlHandleRoot = TiXmlHandle( pXmlElement );
	pXmlElement = xmlHandleRoot.FirstChild().Element();
	
	if ( ! bHasVector ){
	
		if ( ! pXmlElement ){
			cout<<"The point contains correctly no vector. "<<endl;
		
		}else{
			cerr<<"Error: The point contains vector, bur it shouldn't."<<endl;
			iReturn++;
		}
		return iReturn;
	}//else
	
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
		}else if ( string("position") == szVectorXmlType ) {
			cout<<"The type of the vector is correctly \"position\". "<<endl;
		}else{
			cerr<<"Error: The type of the vector is \""<< szVectorXmlType
				<<"\", but should be \"position\"."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No vector handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	TiXmlHandle xmlHandleVectorRoot = TiXmlHandle( pXmlElement );
	pXmlElement = xmlHandleVectorRoot.FirstChild().Element();
	
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
				case 'u': 
					szTargetElementType = "undefined";
				break;
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
			if ( (1 <= iNumberOfElement) && ( iNumberOfElement <= (int)(uiVectorElements) ) ){
				double dValue;
				int iReadValues = sscanf ( pcValue, "%lf", & dValue );
				if ( iReadValues != 0){
					if ( dValue == vecValues[ iNumberOfElement - 1 ] ){
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
 * This method tests the storeXml() method of the cPoint class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an empty point"<<endl;

	cout<<"cPoint pointEmpty;"<<endl;
	cPoint pointEmpty;
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlPointFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "pointEmpty.xml" );
	ofstream * pFileVectorPostion = new ofstream( szXmlPointFileName );
	
	bool bStoreSuccesfull = pointEmpty.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cPoint was stored successfull to the file \""<< szXmlPointFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cPoint to the file \""<< szXmlPointFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	vector<char> vecElementTypePosition( 5, 'u' );
	vector<double> vecValuesPosition( 5, 0.0 );
	
	iReturn += testXmlPoint( szXmlPointFileName, "point", false,
		0, vecElementTypePosition, vecValuesPosition );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an point with a positionsvector with 0 elements"<<endl;

	cout<<"cVectorPosition vecPositionE0( 0 );"<<endl;
	cVectorPosition vecPositionE0( 0 );
	cout<<"cPoint pointE0( & vecPositionE0 );"<<endl;
	cPoint pointE0( & vecPositionE0 );
	
	szFileNameBuffer[0] = 0;
	szXmlPointFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "pointE0.xml" );
	pFileVectorPostion = new ofstream( szXmlPointFileName );
	
	bStoreSuccesfull = pointE0.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cPoint was stored successfull to the file \""<< szXmlPointFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cPoint to the file \""<< szXmlPointFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlPoint( szXmlPointFileName, "background", false,
		0, vecElementTypePosition, vecValuesPosition );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an point with a positionsvector with 2 elements"<<endl;

	cout<<"cVectorPosition vecPosition1E2Ch( 2 );"<<endl;
	cVectorPosition vecPosition1E2Ch( 2 );
	cout<<"vecPosition1E2Ch.setValue( 1, 4);"<<endl;
	vecPosition1E2Ch.setValue( 1, 4);
	vecElementTypePosition[0] = 'w';
	vecValuesPosition[0] = 4;
	cout<<"vecPosition1E2Ch.setValue( 2, 4);"<<endl;
	vecPosition1E2Ch.setValue( 2, 6);
	vecElementTypePosition[1] = 'w';
	vecValuesPosition[1] = 6;
	cout<<"cPoint pointE2( & vecPosition1E2Ch );"<<endl;
	cPoint pointE2( & vecPosition1E2Ch );
	
	szFileNameBuffer[0] = 0;
	szXmlPointFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "pointE2.xml" );
	pFileVectorPostion = new ofstream( szXmlPointFileName );
	
	bStoreSuccesfull = pointE2.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cPoint was stored successfull to the file \""<< szXmlPointFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cPoint to the file \""<< szXmlPointFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlPoint( szXmlPointFileName, "point", true,
		2, vecElementTypePosition, vecValuesPosition );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an point with a positionsvector with 3 elements"<<endl;

	//point with 3 D Positionsvector
	cout<<"cVectorPosition vecPosition1E3Ch( 3 );"<<endl;
	cVectorPosition vecPosition1E3Ch( 3 );
	cout<<"vecPosition1E3Ch.setValue( 1, 4);"<<endl;
	vecPosition1E3Ch.setValue( 1, 4);
	vecElementTypePosition[0] = 'w';
	vecValuesPosition[0] = 4;
	cout<<"vecPosition1E3Ch.setValue( 2, 3);"<<endl;
	vecPosition1E3Ch.setValue( 2, 3);
	vecElementTypePosition[1] = 'w';
	vecValuesPosition[1] = 3;
	cout<<"vecPosition1E3Ch.setValue( 3, 2);"<<endl;
	vecPosition1E3Ch.setValue( 3, 2);
	vecElementTypePosition[2] = 'w';
	vecValuesPosition[2] = 2;
	cout<<"cPoint pointE3( & vecPosition1E3Ch );"<<endl;
	cPoint pointE3( & vecPosition1E3Ch );
	
	szFileNameBuffer[0] = 0;
	szXmlPointFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "pointE3.xml" );
	pFileVectorPostion = new ofstream( szXmlPointFileName );
	
	bStoreSuccesfull = pointE3.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cPoint was stored successfull to the file \""<< szXmlPointFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cPoint to the file \""<< szXmlPointFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlPoint( szXmlPointFileName, "point", true,
		3, vecElementTypePosition, vecValuesPosition );


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

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an empty point"<<endl;

	cout<<"cPoint pointEmpty;"<<endl;
	cPoint pointEmpty;

	//test get compressed size
	unsigned int uiCompressedSize = 5;
	if ( (unsigned int)(pointEmpty.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			pointEmpty.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "pointEmpty.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bool bStoreSuccesfull = pointEmpty.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cPointEmpty[] = { (char)0x12 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cPointEmpty, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an point with a positionsvector with 0 elements"<<endl;

	cout<<"cVectorPosition vecPositionE0( 0 );"<<endl;
	cVectorPosition vecPositionE0( 0 );
	cout<<"cPoint pointE0( & vecPositionE0 );"<<endl;
	cPoint pointE0( & vecPositionE0 );

	//test get compressed size
	uiCompressedSize = 5;
	if ( (unsigned int)(pointE0.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			pointE0.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "pointE0.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = pointE0.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cPointE0[] = { (char)0x02 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cPointE0, 1 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an point with a positionsvector with 2 elements"<<endl;

	cout<<"cVectorPosition vecPosition1E2Ch( 2 );"<<endl;
	cVectorPosition vecPosition1E2Ch( 2 );
	cout<<"vecPosition1E2Ch.setValue( 1, 4);"<<endl;
	vecPosition1E2Ch.setValue( 1, 4);
	cout<<"vecPosition1E2Ch.setValue( 2, 6);"<<endl;
	vecPosition1E2Ch.setValue( 2, 6);
	cout<<"cPoint pointE2( & vecPosition1E2Ch );"<<endl;
	cPoint pointE2( & vecPosition1E2Ch );

	//test get compressed size
	uiCompressedSize = 4 + 2 * 17;
	if ( (unsigned int)(pointE2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			pointE2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "pointE2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = pointE2.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cPointE2[] = { (char)0x81, (char)0x00, (char)0x80, (char)0x01, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cPointE2, 5 );


	return iReturn;
}



/**
 * This method positions methods of the class.
 *
 * methods tested:
 * 	- cVectorPosition *getPosition();
 * 	- void setPosition( const cVectorPosition *vecPositon=NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testPosition( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getPosition() and setPosition() methods"<<endl;

	cout<<"cPoint point;"<<endl;
	cPoint point;

	//test getPosition()
	cout<<"point.getPosition()"<<endl;
	if ( point.getPosition() == NULL ){
	
		cout<<"The positionsvectorpointer is correctly NULL . "<<endl;
	}else{
		cerr<<"Error:The positionsvectorpointer is not NULL ."<<endl;
		iReturn++;
	}

	cout<<"cVectorPosition vecPosition1E2( 2 );"<<endl;
	cVectorPosition vecPosition1E2( 2 );
	cout<<"vecPosition1E2.setValue( 1, 4);"<<endl;
	vecPosition1E2.setValue( 1, 4);
	cout<<"vecPosition1E2.setValue( 2, 4);"<<endl;
	vecPosition1E2.setValue( 2, 6);
	
	cVectorPosition vecPosition2E2( vecPosition1E2 );
	
	cout<<"point.setPosition( &vecPosition1E2 )"<<endl;
	point.setPosition( &vecPosition1E2 );

	//test getPosition()
	cout<<"point.getPosition()"<<endl;
	if ( point.getPosition() != NULL ){
	
		if ( *point.getPosition() == vecPosition1E2 ){
		
			cout<<"The positionsvector is equal to vecPosition1E2. "<<endl;
		}else{
			cerr<<"Error: The positionsvector is not equal to vecPosition1E2."<<endl;
			iReturn++;
		}
		if ( point.getPosition() != &vecPosition1E2 ){
		
			cout<<"The positionsvectorpointer is not equal to vecPosition1E2. "<<endl;
		}else{
			cerr<<"Error: The positionsvectorpointer is equal to vecPosition1E2."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error:The positionsvectorpointer is NULL ."<<endl;
		iReturn++;
	}

	cout<<"point.getPosition()->setValue( 1, 1 );"<<endl;
	point.getPosition()->setValue( 1, 1 );
	vecPosition2E2.setValue( 1, 1 );

	//test getPosition()
	cout<<"point.getPosition()"<<endl;
	if ( point.getPosition() != NULL ){
	
		if ( ! (*point.getPosition() == vecPosition1E2) ){
		
			cout<<"The positionsvector is not anymore equal to vecPosition1E2. "<<endl;
		}else{
			cerr<<"Error: The positionsvector is equal to vecPosition1E2."<<endl;
			iReturn++;
		}
		if ( *point.getPosition() == vecPosition2E2 ){
		
			cout<<"The positionsvector has the correct values. "<<endl;
		}else{
			cerr<<"Error: The positionsvector hasn't the correct values."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error:The positionsvectorpointer is NULL ."<<endl;
		iReturn++;
	}

	cout<<"point.setPosition( NULL )"<<endl;
	point.setPosition( NULL );

	//test getPosition()
	cout<<"point.getPosition()"<<endl;
	if ( point.getPosition() == NULL ){
	
		cout<<"The positionsvectorpointer is correctly NULL . "<<endl;
	}else{
		cerr<<"Error:The positionsvectorpointer is not NULL ."<<endl;
		iReturn++;
	}

	cout<<"cVectorPosition vecPositionE0( 0 );"<<endl;
	cVectorPosition vecPositionE0( 0 );

	cout<<"point.setPosition( &vecPositionE0 )"<<endl;
	point.setPosition( &vecPositionE0 );

	//test getPosition()
	cout<<"point.getPosition()"<<endl;
	if ( point.getPosition() != NULL ){
	
		if ( *point.getPosition() == vecPositionE0 ){
		
			cout<<"The positionsvector is equal to vecPositionE0. "<<endl;
		}else{
			cerr<<"Error: The positionsvector is not equal to vecPositionE0."<<endl;
			iReturn++;
		}
		if ( point.getPosition() != &vecPositionE0 ){
		
			cout<<"The positionsvectorpointer is not equal to vecPositionE0. "<<endl;
		}else{
			cerr<<"Error: The positionsvectorpointer is equal to vecPositionE0."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error:The positionsvectorpointer is NULL ."<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getPosition() and setPosition() methods on a point with a accessible domain"<<endl;

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


	cout<<"cPoint point1( &vecPositionE0, &rootD3 );"<<endl;
	cPoint point1( &vecPositionE0, &rootD3 );

	//test getPosition()
	cout<<"point1.getPosition()"<<endl;
	if ( point1.getPosition() != NULL ){
	
		if ( *point1.getPosition() == vecPositionE0 ){
		
			cout<<"The positionsvector is equal to vecPositionE0. "<<endl;
		}else{
			cerr<<"Error: The positionsvector is not equal to vecPositionE0."<<endl;
			iReturn++;
		}
		if ( point1.getPosition() != &vecPositionE0 ){
		
			cout<<"The positionsvectorpointer is not equal to vecPositionE0. "<<endl;
		}else{
			cerr<<"Error: The positionsvectorpointer is equal to vecPositionE0."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error:The positionsvectorpointer is NULL ."<<endl;
		iReturn++;
	}

	cout<<"cVectorPosition vecPosition1E3( 3 );"<<endl;
	cVectorPosition vecPosition1E3( 3 );
	cout<<"vecPosition1E3.setValue( 1, 1);"<<endl;
	vecPosition1E3.setValue( 1, 1);
	cout<<"vecPosition1E3.setValue( 2, 2);"<<endl;
	vecPosition1E3.setValue( 2, 2);
	
	cout<<"vecPosition1E2.setValue( 2, 2);"<<endl;
	vecPosition1E2.setValue( 2, 2);

	cout<<"point1.setPosition( &vecPosition1E2 )"<<endl;
	point1.setPosition( &vecPosition1E2 );

	//test getPosition()
	cout<<"point1.getPosition()"<<endl;
	if ( point1.getPosition() != NULL ){
	
		if ( *point1.getPosition() == vecPosition1E3 ){
		
			cout<<"The positionsvector is equal to vecPosition1E3. "<<endl;
		}else{
			cerr<<"Error: The positionsvector is not equal to vecPosition1E3."<<endl;
			/*check the elements of the positionsvektor*/
			for ( unsignedIntFib uiActualElement = 1;
					uiActualElement <= point1.getPosition()->getNumberOfElements() &&
					uiActualElement <= 3;
					uiActualElement++ ){
				
				if ( ! point1.getPosition()->isVariable( uiActualElement ) ){
				
					cout<<"The "<<uiActualElement<<"'th element of the "<<
						"positionsvector is correctly not an variable. "<<endl;
				}else{
					cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
						"positionsvector is an variable. "<<endl;
					iReturn++;
				}
				if ( point1.getPosition()->getValue( uiActualElement ) ==
						vecPosition1E3.getValue( uiActualElement ) ){
				
					cout<<"The "<<uiActualElement<<"'th element of the "<<
						"positionsvector is correctly "<< 
						vecPosition1E3.getValue( uiActualElement ) <<" . "<<endl;
				}else{
					cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
						"positionsvector is "<<point1.getPosition()->getValue( uiActualElement )<<
						" and not "<< vecPosition1E3.getValue( uiActualElement ) <<" . "<<endl;
					iReturn++;
				}
			}
			iReturn++;
		}
	}else{
		cerr<<"Error:The positionsvectorpointer is NULL ."<<endl;
		iReturn++;
	}

	cout<<"vecPosition1E3.setValue( 1, 0);"<<endl;
	vecPosition1E3.setValue( 1, 0);
	cout<<"vecPosition1E3.setValue( 2, 1);"<<endl;
	vecPosition1E3.setValue( 2, 1);

	cout<<"point1.setPosition( &vecPosition1E3 )"<<endl;
	point1.setPosition( &vecPosition1E3 );

	//test getPosition()
	cout<<"point1.getPosition()"<<endl;
	if ( point1.getPosition() != NULL ){
	
		if ( *point1.getPosition() == vecPosition1E3 ){
		
			cout<<"The positionsvector is equal to vecPosition1E3. "<<endl;
		}else{
			cerr<<"Error: The positionsvector is not equal to vecPosition1E3."<<endl;
			/*check the elements of the positionsvektor*/
			for ( unsignedIntFib uiActualElement = 1;
					uiActualElement <= point1.getPosition()->getNumberOfElements() &&
					uiActualElement <= 3;
					uiActualElement++ ){
				
				if ( ! point1.getPosition()->isVariable( uiActualElement ) ){
				
					cout<<"The "<<uiActualElement<<"'th element of the "<<
						"positionsvector is correctly not an variable. "<<endl;
				}else{
					cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
						"positionsvector is an variable. "<<endl;
					iReturn++;
				}
				if ( point1.getPosition()->getValue( uiActualElement ) ==
						vecPosition1E3.getValue( uiActualElement ) ){
				
					cout<<"The "<<uiActualElement<<"'th element of the "<<
						"positionsvector is correctly "<< 
						vecPosition1E3.getValue( uiActualElement ) <<" . "<<endl;
				}else{
					cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
						"positionsvector is "<<point1.getPosition()->getValue( uiActualElement )<<
						" and not "<< vecPosition1E3.getValue( uiActualElement ) <<" . "<<endl;
					iReturn++;
				}
			}
			iReturn++;
		}
	}else{
		cerr<<"Error:The positionsvectorpointer is NULL ."<<endl;
		iReturn++;
	}


	return iReturn;
}




/**
 * This method tests the variable methods of the cPoint class.
 *
 * methods tested:
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testVariable( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing isUsedVariable(), replaceVariable() and getUsedVariables() methods"<<endl;

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
	
	cout<<"cVectorPosition vecPositionE3( 3 );"<<endl;
	cVectorPosition vecPositionE3( 3 );
	cout<<"vecPositionE3.setValue( 1, 4 );"<<endl;
	vecPositionE3.setValue( 1, 4 );
	cout<<"vecPositionE3.setValue( 2, 7 );"<<endl;
	vecPositionE3.setValue( 2, 7 );

	cout<<"cPoint pointE3( & vecPositionE3 );"<<endl;
	cPoint pointE3( & vecPositionE3 );

	//check the isUsedVariable() methode from cPoint
	cout<<"pointE3.isUsedVariable( pVariable1 )"<<endl;
	if ( ! pointE3.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the point -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the point -element. "<<endl;
		iReturn++;
	}
	set<cFibVariable*> setCorrectUsedVariables;
	
	//check getUsedVariables()
	cout<<"setUsedVariables = pointE3.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = pointE3.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"pointE3.getPosition()->setVariable( 3, pVariable1 );"<<endl;
	pointE3.getPosition()->setVariable( 3, pVariable1 );
	setCorrectUsedVariables.insert( pVariable1 );

	//check the isUsedVariable() methode from cPoint
	cout<<"pointE3.isUsedVariable( pVariable1 )"<<endl;
	if ( pointE3.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the point -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the point -element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = pointE3.getUsedVariables(); "<<endl;
	setUsedVariables = pointE3.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"pointE3.getPosition()->setVariable( 1, pVariable2 );"<<endl;
	pointE3.getPosition()->setVariable( 1, pVariable2 );
	setCorrectUsedVariables.insert( pVariable2 );

	//check the isUsedVariable() methode from cPoint
	cout<<"pointE3.isUsedVariable( pVariable2 )"<<endl;
	if ( pointE3.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the point -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the point -element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = pointE3.getUsedVariables(); "<<endl;
	setUsedVariables = pointE3.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"pointE3.getPosition()->setVariable( 2, pVariable4 );"<<endl;
	pointE3.getPosition()->setVariable( 2, pVariable4 );
	setCorrectUsedVariables.insert( pVariable4 );

	//check the isUsedVariable() methode from cPoint
	cout<<"pointE3.isUsedVariable( pVariable4 )"<<endl;
	if ( pointE3.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable4 is correctly used in the point -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is not used in the point -element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = pointE3.getUsedVariables(); "<<endl;
	setUsedVariables = pointE3.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"pointE3.getPosition()->setVariable( 2, pVariable1 );"<<endl;
	pointE3.getPosition()->setVariable( 2, pVariable1 );
	setCorrectUsedVariables.erase( pVariable4 );
	//check the isUsedVariable() methode from cPoint
	cout<<"pointE3.isUsedVariable( pVariable1 )"<<endl;
	if ( pointE3.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the point -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the point -element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = pointE3.getUsedVariables(); "<<endl;
	setUsedVariables = pointE3.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"pointE3.replaceVariable( pVariable2, pVariable3 );"<<endl;
	bool bVariableReplaced = pointE3.replaceVariable( pVariable2, pVariable3 );
	setCorrectUsedVariables.erase( pVariable2 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cPoint
	cout<<"pointE3.isUsedVariable( pVariable2 )"<<endl;
	if ( ! pointE3.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the point -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the point -element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cPoint
	cout<<"pointE3.isUsedVariable( pVariable3 )"<<endl;
	if ( pointE3.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the point -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the point -element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = pointE3.getUsedVariables(); "<<endl;
	setUsedVariables = pointE3.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"Try replacing non existing variable pVariable2:"<<endl;
	cout<<"pointE3.replaceVariable( pVariable2, pVariable4 );"<<endl;
	bVariableReplaced = pointE3.replaceVariable( pVariable2, pVariable4 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = pointE3.getUsedVariables(); "<<endl;
	setUsedVariables = pointE3.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cPoint
	cout<<"pointE3.isUsedVariable( pVariable2 )"<<endl;
	if ( ! pointE3.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the point -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the point -element. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cPoint
	cout<<"pointE3.isUsedVariable( pVariable4 )"<<endl;
	if ( ! pointE3.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable4 is correctly not used in the point -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is used in the point -element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cPoint
	cout<<"pointE3.isUsedVariable( pVariable3 )"<<endl;
	if ( pointE3.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the point -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the point -element. "<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods isDefinedVariable( ED_POSITION ) and getDefinedVariables( ED_POSITION )"<<endl;

	//check the isDefinedVariable() methode from cList
	cout<<"pointE3.isDefinedVariable( pVariable1, ED_POSITION )"<<endl;
	if ( ! pointE3.isDefinedVariable( pVariable1, ED_POSITION ) ){
	
		cout<<"The variable pVariable1 is correctly not defined in the pointelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is defined in the pointelement. "<<endl;
		iReturn++;
	}

	//check getDefinedVariables()
	cout<<"liDefinedVariables = pointE3.getDefinedVariables( ED_POSITION ); "<<endl;
	list<cFibVariable*> liDefinedVariables = pointE3.getDefinedVariables( ED_POSITION );
	if ( liDefinedVariables.empty() ){
	
		cout<<"Ther are correctly no variables defines. "<<endl;
	}else{
		cerr<<"Error: Ther are variables defines. "<<endl;
		iReturn++;
	}


	return iReturn;
}










