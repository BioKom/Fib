/**
 * @file tList
 * file name: tList.cpp
 * @author Betti Oesterholz
 * @date 09.12.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cList.
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
 * This file contains the test for the class cList, which
 * represents a Fib -listelement.
 *
 *
 * What's tested of class cList:
 * 	- cList( cFibElement * pFibObject1, cFibElement * pFibObject2, cFibElement * pInSuperiorElement = NULL );
 * 	-(TODO) cList( list< cFibElement * > liUnderObjects, cFibElement * pInSuperiorElement = NULL );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- bool hasUnderAllObjects() const;
 * 	- unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
 * 	- bool evalueObject( iEvaluePosition & evaluePosition, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties ) const;
 * 	- bool evalueObject( iEvalueFibElement & evalueFibElement, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties, const list<char> & liCFibElementTyps );
 * 	- bool equal( const cFibElement & fibObject ) const;
 * 	- bool equalElement( const cFibElement & fibElement ) const;
 * 	- cList( const cList &listElement );
 * 	- cFibElement *clone( ) const;
 * 	- cList *copy( const unsignedIntFib iObjectList=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementList=0 ) const;
 * 	- bool storeXml( ostream &stream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream &stream ) const;
 * 	- unsignedIntFib getNumberOfUnderobjects() const;
 * 	- cFibElement * getUnderobject( unsignedIntFib iNumberOfUnderobject=1 );
 * 	- list< cFibElement * > getUnderobjects( unsignedIntFib iNumberOfFirstUnderobject=1, unsignedIntFib iNumberOfToReturnUnderobjects=0 )
 * 	- bool addUnderobject( cFibElement * pUnderobject, unsignedIntFib iPosition=1 );
 * 	- unsignedIntFib addUnderobjects( list<cFibElement*> liUnderobjects, unsignedIntFib iPosition=1 );
 * 	- bool deleteUnderobject( unsignedIntFib iPositionUnderobject, bool bDeleteOld=true);
 * 	- bool deleteUnderobjects( unsignedIntFib iNumberOfFirstUnderobject, unsignedIntFib iNumberOfToDeleteUnderobjects, bool bDeleteOld=true )
 * 	- bool replaceAllUnderobjects( list<cFibElement*> liUnderobjects, bool bDeleteOld )
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables();
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
 *
 *
 * call: tList [ITERATIONS]
 *
 * parameters:
 * 	ITERATIONS
 * 		The iterations for the test with random generated underobejcts.
 * 		Standardvalue is 256.
 *
 *
 * Methods for changing the structur of an fib -object will be tested with
 * tFibElementStructur. Methods for fib -objects will be tested with
 * Methods for storing and restoring will be tested in tFibElementStore.
 */
/*
History:
09.12.2009  Oesterholz  created
01.01.2010  Oesterholz  isUsedVariable( ED_POSITION ) and getUsedVariables( ED_POSITION ) tested
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
21.05.2010  Oesterholz  addUnderobjects() tested
25.01.2011  Oesterholz  test function testUnderobjectsRand() implemented with new random test for:
	getUnderobjects(), deleteUnderobjects() and replaceAllUnderobjects() methods
04.04.2011  Oesterholz  storing to binary stream
06.06.2011  Oesterholz  number atribute in XML-vector is now optional
26.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cList.h"
#include "cPoint.h"
#include "cProperty.h"
#include "cRoot.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
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
int testUnderobject( unsigned long &ulTestphase );
int testUnderobjectsRand( unsigned long &ulTestphase );
int testVariable( unsigned long &ulTestphase );


unsigned long MAX_ITERATION = 256;


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	if ( argc >= 2 ){
		//one parameter given; read parameter iterations
		MAX_ITERATION = atol( argv[1] );
		if ( MAX_ITERATION < 1 ){
			MAX_ITERATION = 1;
		}
	}
	
	cout<<endl<<"Running Test for cList methods"<<endl;
	cout<<      "=============================="<<endl;

	
	iReturn += testCostructor( ulTestphase );
	iReturn += testEvalueObject( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testUnderobject( ulTestphase );
	iReturn += testUnderobjectsRand( ulTestphase );
	iReturn += testVariable( ulTestphase );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the constructor of the cList class.
 *
 * methods tested:
 * 	- cList( cFibElement * pFibObject1, cFibElement * pFibObject2, cFibElement * pInSuperiorElement = NULL, cFibElement * pInPreviousFibElement = NULL );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- unsignedIntFib getNumberOfElement();
 * 	- bool hasUnderAllObjects() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing list with no underobjects"<<endl;


	cout<<"cList listEmpty1( NULL, NULL );"<<endl;
	cList listEmpty1( NULL, NULL );

	//check the getType() methode from cList
	if ( listEmpty1.getType() == 'l' ){
	
		cout<<"The type of the listelement is correctly 'l' . "<<endl;
	}else{
		cerr<<"Error: The type of the listelement is "<<
			listEmpty1.getType()<<" but should be 'l' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cList
	if ( ! listEmpty1.isValidFibElement() ){
	
		cout<<"The listelement is correctly not a correct listelement. "<<endl;
	}else{
		cerr<<"Error: The listelement is a correct listelement, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cList
	if ( ! listEmpty1.isMovable() ){
	
		cout<<"The listelement is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The listelement is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cList
	if ( listEmpty1.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the listelement is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the listelement is "<<
			listEmpty1.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cList
	if ( listEmpty1.getNextFibElement() == NULL ){
	
		cout<<"The next fib -element for the listelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next fib -element for the listelement is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cList
	if ( listEmpty1.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the listelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the listelement is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cList
	if ( listEmpty1.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the listelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the listelement is "<<
			listEmpty1.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cList
	if ( ! listEmpty1.hasUnderAllObjects()){
	
		cout<<"The listelement is correctly missing a needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement is missing no underobjects."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing list with two empty pointelements"<<endl;

	cout<<"cPoint pointEmpty1;"<<endl;
	cPoint pointEmpty1;
	cout<<"cPoint pointEmpty2;"<<endl;
	cPoint pointEmpty2;

	cout<<"cList listEmpty( &pointEmpty1, &pointEmpty2 );"<<endl;
	cList listEmpty( &pointEmpty1, &pointEmpty2 );

	//check the getType() methode from cList
	if ( listEmpty.getType() == 'l' ){
	
		cout<<"The type of the listelement is correctly 'l' . "<<endl;
	}else{
		cerr<<"Error: The type of the listelement is "<<
			listEmpty.getType()<<" but should be 'l' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cList
	if ( listEmpty.isValidFibElement() ){
	
		cout<<"The listelement is correctly a correct listelement. "<<endl;
	}else{
		cerr<<"Error: The listelement is not a correct listelement, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cList
	if ( ! listEmpty.isMovable() ){
	
		cout<<"The listelement is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The listelement is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cList
	if ( listEmpty.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the listelement is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the listelement is "<<
			listEmpty.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cList
	if ( listEmpty.getNextFibElement() == &pointEmpty1 ){
	
		cout<<"The next fib -element for the listelement is correctly pointEmpty1. "<<endl;
	}else{
		cerr<<"Error: The next fib -element for the listelement is not pointEmpty1."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cList
	if ( listEmpty.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the listelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the listelement is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cList
	if ( listEmpty.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the listelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the listelement is "<<
			listEmpty.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cList
	if ( listEmpty.hasUnderAllObjects()){
	
		cout<<"The listelement has correctly missing all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement is missing a underobject."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cList with a superior fib -element"<<endl;

	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	
	cout<<"cList listSup( NULL, NULL, &rootEmpty1 );"<<endl;
	cList listSup( NULL, NULL, &rootEmpty1 );

	//check the getType() methode from cList
	if ( listSup.getType() == 'l' ){
	
		cout<<"The type of the listelement is correctly 'l' . "<<endl;
	}else{
		cerr<<"Error: The type of the listelement is "<<
			listSup.getType()<<" but should be 'l' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cList
	if ( ! listSup.isValidFibElement() ){
	
		cout<<"The listelement is correctly not a correct listelement. "<<endl;
	}else{
		cerr<<"Error: The listelement is a correct listelement, but shouldn't be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cList
	if ( ! listSup.isMovable() ){
	
		cout<<"The listelement is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The listelement is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cList
	if ( listSup.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the listelement is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the listelement is "<<
			listSup.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cList
	if ( listSup.getNextFibElement() == NULL ){
	
		cout<<"The next fib -element for the listelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next fib -element for the listelement is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cList
	if ( listSup.getFibElement( -1 ) == &rootEmpty1 ){
	
		cout<<"The previous fib -element for the listelement is correctly rootEmpty1. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the listelement is not rootEmpty1."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cList
	if ( listSup.getSuperiorFibElement() == &rootEmpty1 ){
	
		cout<<"The superior fib -element for the listelement is correctly rootEmpty1. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the listelement is "<<
			listSup.getSuperiorFibElement() << " and not rootEmpty1."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cList
	if ( ! listSup.hasUnderAllObjects() ){
	
		cout<<"The listelement has correctly not all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement is not missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cList with a next fib -element"<<endl;
	
	cout<<"cList listNextPrev( &pointEmpty1, &pointEmpty2, NULL );"<<endl;
	cList listNextPrev( &pointEmpty1, &pointEmpty2, NULL );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cList with a next and previous fib -element"<<endl;
	
	cout<<"cList listNextPrev( &pointEmpty1, &pointEmpty2, NULL, &listEmpty );"<<endl;
	cList listNextPrev( &pointEmpty1, &pointEmpty2, NULL, &listEmpty );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	//check the getType() methode from cList
	if ( listNextPrev.getType() == 'l' ){
	
		cout<<"The type of the listelement is correctly 'l' . "<<endl;
	}else{
		cerr<<"Error: The type of the listelement is "<<
			listNextPrev.getType()<<" but should be 'l' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cList
	if ( listNextPrev.isValidFibElement() ){
	
		cout<<"The listelement is correctly a correct listelement. "<<endl;
	}else{
		cerr<<"Error: The listelement is not a correct listelement, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cList
	if ( ! listNextPrev.isMovable() ){
	
		cout<<"The listelement is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The listelement is movebel."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNumberOfElement() methode from cList
	if ( listNextPrev.getNumberOfElement() == 1 ){
		cout<<"The number of the fib -element for the listelement is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the listelement is "<<
			listNextPrev.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	if ( listNextPrev.getNumberOfElement() == 2 ){
		cout<<"The number of the fib -element for the listelement is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the listelement is "<<
			listNextPrev.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	
	//check the getNextFibElement() methode from cList
	if ( listNextPrev.getNextFibElement() == &pointEmpty1 ){
	
		cout<<"The next fib -element for the listelement is correctly pointEmpty1. "<<endl;
	}else{
		cerr<<"Error: The next fib -element for the listelement is not pointEmpty1."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cList
	if ( listNextPrev.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the listelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the listelement is not NULL."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cList
	if ( listNextPrev.getFibElement( -1 ) == &listEmpty ){
	
		cout<<"The previous fib -element for the listelement is correctly list1. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the listelement is not list1."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getSuperiorFibElement() methode from cList
	if ( listNextPrev.getSuperiorFibElement() == NULL){
	
		cout<<"The superior fib -element for the listelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the listelement is "<<
			listNextPrev.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cList
	if ( listNextPrev.hasUnderAllObjects()  ){
	
		cout<<"The listelement has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement is missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cList with all parameters given"<<endl;
	
	cout<<"cRoot rootD3;"<<flush<<endl;
	cRoot rootD3;
	
	cout<<"cPoint point1;"<<endl;
	cPoint point1;

	cout<<"cPoint point2;"<<endl;
	cPoint point2;

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cList listFull( &point1, &point2, &rootD3 );"<<endl;
	cList listFull( &point1, &point2, &rootD3  );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cList listFull( &point1, &listEmpty, &rootD3, &point2 );"<<endl;
	cList listFull( &point1, &listEmpty, &rootD3, &point2  );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	//check the getType() methode from cList
	if ( listFull.getType() == 'l' ){
	
		cout<<"The type of the listelement is correctly 'l' . "<<endl;
	}else{
		cerr<<"Error: The type of the listelement is "<<
			listFull.getType()<<" but should be 'l' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cList
	if ( listFull.isValidFibElement() ){
	
		cout<<"The listelement is correctly a correct listelement. "<<endl;
	}else{
		cerr<<"Error: The listelement is not a correct listelement, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cList
	if ( ! listFull.isMovable() ){
	
		cout<<"The listelement is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The listelement is movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cList
	if ( listFull.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the listelement is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the listelement is "<<
			listFull.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cList
	if ( listFull.getNextFibElement() == &point1 ){
	
		cout<<"The next fib -element for the listelement is correctly point1. "<<endl;
	}else{
		cerr<<"Error: The next fib -element for the listelement is not point1."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cList
	if ( listFull.getFibElement( -1 ) == &rootD3 ){
	
		cout<<"The previous fib -element for the listelement is correctly rootD3. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the listelement is not rootD3."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cList
	if ( listFull.getFibElement( -1 ) == &point2 ){
	
		cout<<"The previous fib -element for the listelement is correctly point2. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the listelement is not point2."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getSuperiorFibElement() methode from cList
	if ( listFull.getSuperiorFibElement() == &rootD3 ){
	
		cout<<"The superior fib -element for the listelement is correctly rootD3. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the listelement is "<<
			listFull.getSuperiorFibElement() << " and not rootD3."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderobjects() methode from cList
	if ( listFull.getNumberOfUnderobjects() == 2 ){
	
		cout<<"The number of the underobjects of the listelement is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of underobjects for the listelement is "<<
			listFull.getNumberOfUnderobjects() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cList
	if ( listFull.hasUnderAllObjects() ){
	
		cout<<"The listelement has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement is missing a underobject."<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cList with 3 dimensional listvector"<<endl;

	cout<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );

	cout<<"cPoint point1( &vecPositionE2 );"<<endl;
	cPoint point1( &vecPositionE2 );
	cout<<"cPoint point2( &vecPositionE2 );"<<endl;
	cPoint point2( &vecPositionE2 );

	cout<<"cList list1( &point1, &point2 );"<<endl;
	cList list1( &point1, &point2 );
	unsigned int uiPointsToEvalue = 2;
	
	list< pair< const cVectorPosition*, list<cVectorProperty> > > liPointsToEvalue;
	liPointsToEvalue.push_back( make_pair( &vecPositionE2, list<cVectorProperty>() ) );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2, list<cVectorProperty>() ) );
	
	unsigned int uiTimeNeeded = 1 + 3 + 3;

	//check the getTimeNeed() methode from cList
	cout<<"list1.getTimeNeed()"<<endl;
	if ( list1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			list1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cList
	cout<<"list1.getTimeNeed( 2 )"<<endl;
	if ( list1.getTimeNeed( 2 ) == 2 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 2 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			list1.getTimeNeed( 2 ) <<", but should be "<< 2 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"list<cVectorProperty> liVecProperties;"<<endl;
	list<cVectorProperty> liVecProperties;
	
	cout<<"cEvaluePositionList evaluePositionList;"<<endl;
	cEvaluePositionList evaluePositionList;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"list1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bool bObjectEvalued = list1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The list was correctly evalued. "<<endl;
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

	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.liEvaluedPositionData.clear();
	cout<<"list1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = list1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The list was correctly evalued. "<<endl;
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

	cout<<"cEvalueFibElementList evalueFibElementList;"<<endl;
	cEvalueFibElementList evalueFibElementList;
	cout<<"list<char> liCFibElementTyps;"<<endl;
	list<char> liCFibElementTyps;
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	list< pair< const cFibElement*, list<cVectorProperty> > > liFibElementsToEvalue;
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.push_back( make_pair( &point2, list<cVectorProperty>() ) );
	cout<<"list1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = list1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The list was correctly evalued. "<<endl;
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
	cout<<"list1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = list1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The list was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cList with two underobjects"<<endl;
	
	cout<<"cVectorProperty vecPropertyColorRgb1( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyColorRgb1( cTypeProperty::COLOR_RGB );
	cout<<"vecPropertyColorRgb1.setValue( 1, 5 );"<<endl;
	vecPropertyColorRgb1.setValue( 1, 5 );
	cout<<"vecPropertyColorRgb1.setValue( 2, 3 );"<<endl;
	vecPropertyColorRgb1.setValue( 2, 3 );
	
	cout<<"cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );
	cout<<"vecPropertyColorSW.setValue( 1, 14 );"<<endl;
	vecPropertyColorSW.setValue( 1, 14 );
	
	cout<<"cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );
	cout<<"vecPropertyLayer.setValue( 1, 2 );"<<endl;
	vecPropertyLayer.setValue( 1, 2 );
	
	cout<<"cVectorPosition vecPosition2E2( 2 );"<<endl;
	cVectorPosition vecPosition2E2( 2 );
	cout<<"vecPosition2E2.setValue( 1, 1 );"<<endl;
	vecPosition2E2.setValue( 1, 1 );
	
	cout<<"cPoint point3( &vecPositionE2 );"<<endl;
	cPoint point3( &vecPositionE2 );
	
	cout<<"cPoint point4( &vecPosition2E2 );"<<endl;
	cPoint point4( &vecPosition2E2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyColorRgb( vecPropertyColorRgb1, &point3 );"<<endl;
	cProperty propertyColorRgb( vecPropertyColorRgb1, &point3 );
	
	cout<<"cProperty propertyColorSw( vecPropertyColorSW, &point4 );"<<endl;
	cProperty propertyColorSw( vecPropertyColorSW, &point4 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyColorRgb( vecPropertyColorRgb1 , NULL, NULL, &point3 );"<<endl;
	cProperty propertyColorRgb( vecPropertyColorRgb1 , NULL, NULL, &point3 );
	
	cout<<"cProperty propertyColorSw( vecPropertyColorSW , NULL, NULL, &point4 );"<<endl;
	cProperty propertyColorSw( vecPropertyColorSW , NULL, NULL, &point4 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	
	cout<<"cList list2( &propertyColorRgb, &propertyColorSw );"<<endl;
	cList list2( &propertyColorRgb, &propertyColorSw );
	
	uiPointsToEvalue = 2;
	
	liPointsToEvalue.clear();
	liPointsToEvalue.push_back( make_pair( &vecPositionE2, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorRgb1 );
	liPointsToEvalue.push_back( make_pair( &vecPosition2E2, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSW );
	
	uiTimeNeeded = 1 + 4 + 3 + 2 + 3;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	cout<<"list2.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = list2.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The list was correctly evalued. "<<endl;
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
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &point3, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorRgb1 );
	liFibElementsToEvalue.push_back( make_pair( &point4, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSW );

	cout<<"list2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = list2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The list was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cList with a global property list given"<<endl;
	
	list< pair< const cVectorPosition*, list<cVectorProperty> > >::iterator
		itrPositionProperties = liPointsToEvalue.begin();
	itrPositionProperties->second.push_back( vecPropertyLayer );
	itrPositionProperties++;
	itrPositionProperties->second.push_back( vecPropertyLayer );
	
	uiTimeNeeded = 1 + 4 + 3 + 2 + 3;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	cout<<"list2.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = list2.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The list was correctly evalued. "<<endl;
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
	list< pair< const cFibElement*, list<cVectorProperty> > >::iterator
		itrElementProperties = liFibElementsToEvalue.begin();
	itrElementProperties->second.push_back( vecPropertyLayer );
	itrElementProperties++;
	itrElementProperties->second.push_back( vecPropertyLayer );

	cout<<"list2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = list2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The list was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cList with tree underobjects"<<endl;
	
	cout<<"cVectorProperty vecPropertyColorRgb2( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyColorRgb2( cTypeProperty::COLOR_RGB );
	cout<<"vecPropertyColorRgb2.setValue( 1, 2 );"<<endl;
	vecPropertyColorRgb2.setValue( 1, 2 );
	cout<<"vecPropertyColorRgb2.setValue( 2, 2 );"<<endl;
	vecPropertyColorRgb2.setValue( 2, 2 );
	
	cout<<"cVectorPosition vecPosition3E2( 2 );"<<endl;
	cVectorPosition vecPosition3E2( 2 );
	cout<<"vecPosition3E2.setValue( 1, 3 );"<<endl;
	vecPosition3E2.setValue( 1, 3 );
	cout<<"vecPosition3E2.setValue( 2, 3 );"<<endl;
	vecPosition3E2.setValue( 2, 3 );
	
	cout<<"cPoint point5( &vecPosition3E2 );"<<endl;
	cPoint point5( &vecPosition3E2 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyColorRgb2( vecPropertyColorRgb2, &point5 );"<<endl;
	cProperty propertyColorRgb2( vecPropertyColorRgb2, &point5 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyColorRgb2( vecPropertyColorRgb2 , NULL, NULL, &point5 );"<<endl;
	cProperty propertyColorRgb2( vecPropertyColorRgb2 , NULL, NULL, &point5 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"list2.addUnderobject( &propertyColorRgb2, 3 );"<<endl;
	list2.addUnderobject( &propertyColorRgb2, 3 );
	
	uiPointsToEvalue = 3;

	liPointsToEvalue.push_back( make_pair( &vecPosition3E2, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorRgb2 );
	liPointsToEvalue.back().second.push_back( vecPropertyLayer );
	
	uiTimeNeeded = 1 + 4 + 3 + 2 + 3 + 4 + 3;

	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	cout<<"list2.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = list2.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The list was correctly evalued. "<<endl;
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


	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.liEvaluedElementData.clear();
	liFibElementsToEvalue.push_back( make_pair( &point5, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorRgb2 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyLayer );

	cout<<"list2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = list2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The list was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cList for non existing object point 4"<<endl;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	liPointsToEvalue.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	uiPointsToEvalue = 0;
	cout<<"list1.evalueObject( evaluePositionList, 4,  liVecProperties );"<<endl;
	bObjectEvalued = list1.evalueObject( evaluePositionList, 4,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The list was correctly not evalued. "<<endl;
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
	evalueFibElementList.liEvaluedElementData.clear();
	liFibElementsToEvalue.clear();
	cout<<"list1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = list1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The list was correctly not evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cList when returnvalue is false"<<endl;

	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	uiPointsToEvalue = 0;
	cout<<"list2.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = list2.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The list was correctly evalued. with result false "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == 1 ){
	
		cout<<"The evaluePositionList() function was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() function was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	
	evalueFibElementList.lNumberOfTrueEvalueCalls = 0;
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.liEvaluedElementData.clear();
	liFibElementsToEvalue.clear();
	cout<<"list2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = list2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The list was correctly evalued. with result false "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == 1 ){
	
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cList with differnt elements to evalue"<<endl;

	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.liEvaluedElementData.clear();
	cout<<"liCFibElementTyps.push_back( 'l' );"<<endl;
	liCFibElementTyps.push_back( 'l' );
	uiPointsToEvalue = 1;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &list2, list<cVectorProperty>() ) );
	cout<<"list2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = list2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The list was correctly evalued. "<<endl;
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
	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	cout<<"liCFibElementTyps.push_back( 'y' );"<<endl;
	liCFibElementTyps.push_back( 'y' );
	uiPointsToEvalue = 3;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &propertyColorRgb, list<cVectorProperty>() ) );
	liFibElementsToEvalue.push_back( make_pair( &propertyColorSw, list<cVectorProperty>() ) );
	liFibElementsToEvalue.push_back( make_pair( &propertyColorRgb2, list<cVectorProperty>() ) );
	cout<<"list2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = list2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The list was correctly evalued. "<<endl;
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
	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	cout<<"liCFibElementTyps.push_back( 'r' );"<<endl;
	liCFibElementTyps.push_back( 'r' );
	cout<<"liCFibElementTyps.push_back( 'l' );"<<endl;
	liCFibElementTyps.push_back( 'l' );
	cout<<"liCFibElementTyps.push_back( 'm' );"<<endl;
	liCFibElementTyps.push_back( 'm' );
	uiPointsToEvalue = 1;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &list2, list<cVectorProperty>() ) );
	cout<<"list2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = list2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The list was correctly evalued. "<<endl;
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


	return iReturn;
}



/**
 * This method tests the equal() method of two given fib -objects which are
 * equal.
 *
 * @param fibObject1 the first fib -object to compare
 * @param szNameObject1 the name of the first fib -object to compare
 * @param fibObject2 the second fib -object to compare to
 * @param szNameObject2 the name of the second fib -object to compare
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
	
		cout<<"The "<<szNameObject1<<" listelement is equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" listelement is not equal to "<<
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
 * @param fibObject2 the second fib -object to compare to
 * @param szNameObject2 the name of the second fib -object to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualObjects( const cFibElement &fibObject1, const string &szNameObject1,
	const cFibElement &fibObject2, const string &szNameObject2 ){
	
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
	if ( fibObject1.equalElement( fibObject2 ) ){
	
		cout<<"The "<<szNameObject1<<" listelement is equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" listelement is not equal to "<<
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing equal methods for root -elements"<<endl;

	cout<<endl<<"Creating listobjects objects to compare: "<<endl<<endl;

	//empty list
	cout<<"cList listEmpty1( NULL, NULL );"<<endl;
	cList listEmpty1( NULL, NULL );

	//list with one underobject
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cList listE1P1( &point1, NULL );"<<endl;
	cList listE1P1( &point1, NULL );

	cout<<"cPoint point2;"<<endl;
	cPoint point2;
	cout<<"cList listE1P2( NULL, &point2 );"<<endl;
	cList listE1P2( NULL, &point2 );

	//list with two underobjects
	cout<<"cPoint point3;"<<endl;
	cPoint point3;
	cout<<"cPoint point4;"<<endl;
	cPoint point4;
	cout<<"cList list1E2PE( &point3, &point4 );"<<endl;
	cList list1E2PE( &point3, &point4 );

	cout<<"cPoint point5;"<<endl;
	cPoint point5;
	cout<<"cPoint point6;"<<endl;
	cPoint point6;
	cout<<"cList list2E2PE( &point5, &point6 );"<<endl;
	cList list2E2PE( &point5, &point6 );

	cout<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );
	cout<<"cPoint pointE2( &vecPositionE2 );"<<endl;
	cPoint pointE2( &vecPositionE2 );;
	cout<<"cPoint point7;"<<endl;
	cPoint point7;
	cout<<"cList list1E2PE2PE( &pointE2, &point7 );"<<endl;
	cList list1E2PE2PE( &pointE2, &point7 );

	cout<<"cVectorPosition vecPosition2E2( 2 );"<<endl;
	cVectorPosition vecPosition2E2( 2 );
	cout<<"cPoint point2E2( &vecPosition2E2 );"<<endl;
	cPoint point2E2( &vecPosition2E2 );;
	cout<<"cPoint point8;"<<endl;
	cPoint point8;
	cout<<"cList list1E2PEPE2( &point8, &point2E2 );"<<endl;
	cList list1E2PEPE2( &point8, &point2E2 );

	//list with tree underobjects
	cout<<"cPoint point9;"<<endl;
	cPoint point9;
	cout<<"cPoint point10;"<<endl;
	cPoint point10;
	cout<<"cPoint point11;"<<endl;
	cPoint point11;
	cout<<"cList list2E3( &point9, &point10 );"<<endl;
	cList list2E3( &point9, &point10 );
	cout<<"list2E3.addUnderobject( &point11 );"<<endl;
	list2E3.addUnderobject( &point11 );


	//list with four underobjects
	cout<<"cPoint point12;"<<endl;
	cPoint point12;
	cout<<"cPoint point13;"<<endl;
	cPoint point13;
	cout<<"cPoint point14;"<<endl;
	cPoint point14;
	cout<<"cPoint point15;"<<endl;
	cPoint point15;
	cout<<"cList list1E4( &point12, &point13 );"<<endl;
	cList list1E4( &point12, &point13 );
	cout<<"list1E4.addUnderobject( &point14 );"<<endl;
	list1E4.addUnderobject( &point14 );
	cout<<"list1E4.addUnderobject( &point15 );"<<endl;
	list1E4.addUnderobject( &point15 );

	cout<<"cPoint point16;"<<endl;
	cPoint point16;
	cout<<"cPoint point17;"<<endl;
	cPoint point17;
	cout<<"cPoint point18;"<<endl;
	cPoint point18;
	cout<<"cVectorPosition vecPosition3E2( 2 );"<<endl;
	cVectorPosition vecPosition3E2( 2 );
	cout<<"cPoint point3E2( &vecPosition3E2 );"<<endl;
	cPoint point3E2( &vecPosition3E2 );;
	cout<<"cList list2E4( &point16, &point3E2 );"<<endl;
	cList list2E4( &point16, &point3E2 );
	cout<<"list2E4.addUnderobject( &point17 );"<<endl;
	list2E4.addUnderobject( &point17 );
	cout<<"list2E4.addUnderobject( &point18 );"<<endl;
	list2E4.addUnderobject( &point18 );

	cout<<"cPoint point19;"<<endl;
	cPoint point19;
	cout<<"cPoint point20;"<<endl;
	cPoint point20;
	cout<<"cPoint point21;"<<endl;
	cPoint point21;
	cout<<"cVectorPosition vecPosition4E2( 2 );"<<endl;
	cVectorPosition vecPosition4E2( 2 );
	cout<<"cPoint point4E2( &vecPosition4E2 );"<<endl;
	cPoint point4E2( &vecPosition4E2 );;
	cout<<"cList list3E4( &point19, &point20 );"<<endl;
	cList list3E4( &point19, &point20 );
	cout<<"list3E4.addUnderobject( &point21 );"<<endl;
	list3E4.addUnderobject( &point21 );
	cout<<"list3E4.addUnderobject( &point4E2 );"<<endl;
	list3E4.addUnderobject( &point4E2 );

	cout<<"cPoint point22;"<<endl;
	cPoint point22;
	cout<<"cPoint point23;"<<endl;
	cPoint point23;
	cout<<"cPoint point24;"<<endl;
	cPoint point24;
	cout<<"cVectorPosition vecPosition5E2( 2 );"<<endl;
	cVectorPosition vecPosition5E2( 2 );
	cout<<"cPoint point5E2( &vecPosition5E2 );"<<endl;
	cPoint point5E2( &vecPosition5E2 );;
	cout<<"cList list4E4( &point22, &point23 );"<<endl;
	cList list4E4( &point22, &point23 );
	cout<<"list4E4.addUnderobject( &point5E2 );"<<endl;
	list4E4.addUnderobject( &point5E2 );
	cout<<"list4E4.addUnderobject( &point24 );"<<endl;
	list4E4.addUnderobject( &point24 );

	//list which contains a list
	cout<<"cPoint point25;"<<endl;
	cPoint point25;
	cout<<"cPoint point26;"<<endl;
	cPoint point26;
	cout<<"cPoint point27;"<<endl;
	cPoint point27;
	cout<<"cList list1E2Contained( &point25, &point26 );"<<endl;
	cList list1E2Contained( &point25, &point26 );
	cout<<"cList listE2L1( &list1E2Contained, &point27 );"<<endl;
	cList listE2L1( &list1E2Contained, &point27 );

	cout<<"cPoint point28;"<<endl;
	cPoint point28;
	cout<<"cPoint point29;"<<endl;
	cPoint point29;
	cout<<"cPoint point30;"<<endl;
	cPoint point30;
	cout<<"cList list2E2Contained( &point28, &point29 );"<<endl;
	cList list2E2Contained( &point28, &point29 );
	cout<<"cList listE2L2( &point30, &list2E2Contained );"<<endl;
	cList listE2L2( &point30, &list2E2Contained );

	
	//list with superior element
	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	cout<<"cPoint point31;"<<endl;
	cPoint point31;
	cout<<"cPoint point32;"<<endl;
	cPoint point32;
	cout<<"cList listSup( &point31, &point32, &rootEmpty1 );"<<endl;
	cList listSup( &point31, &point32, &rootEmpty1 );

	//list in fib -element structur
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;
	cout<<"cPoint point33;"<<endl;
	cPoint point33;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cList listNextPrev( &poinNext, &point33 );"<<endl;
	cList listNextPrev( &poinNext, &point33 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinPrev;"<<endl;
	cPoint poinPrev;
	cout<<"cList listNextPrev( &poinNext, &point33, NULL, &poinPrev );"<<endl;
	cList listNextPrev( &poinNext, &point33,  NULL, &poinPrev );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"cPoint poinNext2;"<<endl;
	cPoint poinNext2;
	cout<<"cPoint point34;"<<endl;
	cPoint point34;
	cout<<"cRoot rootEmpty2;"<<flush<<endl;
	cRoot rootEmpty2;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cList listFull( &poinNext2, &point34, &rootEmpty2 );"<<endl;
	cList listFull( &poinNext2, &point34, &rootEmpty2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinPrev2;"<<endl;
	cPoint poinPrev2;
	cout<<"cList listFull( &poinNext2, &point34, &rootEmpty2, &poinPrev2);"<<endl;
	cList listFull( &poinNext2, &point34, &rootEmpty2, &poinPrev2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR



	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with listEmpty1
	cFibElement *actualObject = &listEmpty1;
	string szActualObjectName = "listEmpty1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with listE1P1
	actualObject = &listE1P1;
	szActualObjectName = "listE1P1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with listE1P2
	actualObject = &listE1P2;
	szActualObjectName = "listE1P2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with list1E2PE
	actualObject = &list1E2PE;
	szActualObjectName = "list1E2PE";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with list2E2PE
	actualObject = &list2E2PE;
	szActualObjectName = "list2E2PE";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with list1E2PE2PE
	actualObject = &list1E2PE2PE;
	szActualObjectName = "list1E2PE2PE";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with list1E2PEPE2
	actualObject = &list1E2PEPE2;
	szActualObjectName = "list1E2PEPE2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with list2E3
	actualObject = &list2E3;
	szActualObjectName = "list2E3";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with list1E4
	actualObject = &list1E4;
	szActualObjectName = "list1E4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );
	
	//compare with list2E4
	actualObject = &list2E4;
	szActualObjectName = "list2E4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with list3E4
	actualObject = &list3E4;
	szActualObjectName = "list3E4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with list4E4
	actualObject = &list4E4;
	szActualObjectName = "list4E4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with listE2L1
	actualObject = &listE2L1;
	szActualObjectName = "listE2L1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with listE2L2
	actualObject = &listE2L2;
	szActualObjectName = "listE2L2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with listSup
	actualObject = &listSup;
	szActualObjectName = "listSup";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with listNextPrev
	actualObject = &listNextPrev;
	szActualObjectName = "listNextPrev";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );

	//compare with listFull
	actualObject = &listFull;
	szActualObjectName = "listFull";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listEmpty1, "listEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P1, "listE1P1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE1P2, "listE1P2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list1E2PE, "list1E2PE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, list2E2PE, "list2E2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PE2PE, "list1E2PE2PE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E2PEPE2, "list1E2PEPE2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E3, "list2E3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list1E4, "list1E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list2E4, "list2E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list3E4, "list3E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, list4E4, "list4E4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L1, "listE2L1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, listE2L2, "listE2L2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listSup, "listSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listNextPrev, "listNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, listFull, "listFull" );


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
 * This method tests the copy methods and copyconstructor of the cList class.
 *
 * methods tested:
 * 	- cList( const cList &listElement );
 * 	- cFibElement *clone( ) const;
 * 	- cList *copy( const unsignedIntFib iObjectList=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementList=0 ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a empty cList"<<endl;

	cout<<"cList listEmpty( NULL, NULL );"<<endl;
	cList listEmpty( NULL, NULL );

	cout<<"cList listEmptyCopyConstruct( listEmpty );"<<endl;
	cList listEmptyCopyConstruct( listEmpty );

	iReturn += testCompareTwoEqualObjectsStructur( listEmptyCopyConstruct, "listEmptyCopyConstruct", listEmpty, "listEmpty" );
	iReturn += testNotConnectedFibElement( listEmptyCopyConstruct );

	cout<<"cFibElement * pListEmptyClone = listEmpty.clone();"<<endl;
	cFibElement * pListEmptyClone = listEmpty.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pListEmptyClone, "pListEmptyClone", listEmpty, "listEmpty" );
	delete pListEmptyClone;

	cout<<"cFibElement * pListEmptyCopy = listEmpty.copy();"<<endl;
	cFibElement * pListEmptyCopy = listEmpty.copy();

	iReturn += testCompareTwoEqualObjectsStructur( *pListEmptyCopy, "pListEmptyCopy", listEmpty, "listEmpty" );
	delete pListEmptyCopy;

	cout<<"cFibElement * pListEmptyCopyElement = listEmpty.copyElement();"<<endl;
	cFibElement * pListEmptyCopyElement = listEmpty.copyElement();

	iReturn += testCompareTwoEqualObjectsStructur( *pListEmptyCopyElement, "pListEmptyCopyElement", listEmpty, "listEmpty" );
	delete pListEmptyCopyElement;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying for a other object or elementpoint"<<endl;

	cout<<"cFibElement * pListEmptyNoCopy = listEmpty.copy( 1 );"<<endl;
	cFibElement * pListEmptyNoCopy = listEmpty.copy( 1 );

	if ( pListEmptyNoCopy == NULL ){
	
		cout<<"The cList was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cList was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pListEmptyNoCopy;
	}

	cout<<"cFibElement * pListEmptyNoCopyElement = listEmpty.copyElement( 'l', 2 );"<<endl;
	cFibElement * pListEmptyNoCopyElement = listEmpty.copyElement( 'l', 2 );

	if ( pListEmptyNoCopyElement == NULL ){
	
		cout<<"The cList -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cList -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pListEmptyNoCopyElement;
	}

	cout<<"pListEmptyNoCopyElement = listEmpty.copyElement( 'u', 2 );"<<endl;
	pListEmptyNoCopyElement = listEmpty.copyElement( 'u', 2 );

	if ( pListEmptyNoCopyElement == NULL ){
	
		cout<<"The cList -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cList -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pListEmptyNoCopyElement;
	}

	cout<<"pListEmptyNoCopyElement = listEmpty.copyElement( 'r', 1 );"<<endl;
	pListEmptyNoCopyElement = listEmpty.copyElement( 'r', 1 );

	if ( pListEmptyNoCopyElement == NULL ){
	
		cout<<"The cList -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cList -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pListEmptyNoCopyElement;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cList with all members set"<<endl;

	//list in fib -element structur
	cout<<"cPoint poinPrev;"<<endl;
	cPoint poinPrev;
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;
	cout<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );
	cout<<"cPoint pointE2( &vecPositionE2 );"<<endl;
	cPoint pointE2( &vecPositionE2 );;

	cout<<"cRoot rootD3;"<<flush<<endl;
	cRoot rootD3;
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cList list2E2( &poinNext, &pointE2, &rootD3 );"<<endl;
	cList list2E2( &poinNext, &pointE2, &rootD3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cList list2E2( &poinNext, &pointE2, &rootD3, &poinPrev );"<<endl;
	cList list2E2( &poinNext, &pointE2, &rootD3, &poinPrev );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"cList list2E2CopyConstruct( list2E2 );"<<endl;
	cList list2E2CopyConstruct( list2E2 );

	if ( list2E2CopyConstruct.equalElement( list2E2 ) ){
	
		cout<<"The list2E2CopyConstruct fib -element is equal to list2E2. "<<endl;
	}else{
		cerr<<"Error: The list2E2CopyConstruct fib -element is not equal to list2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( list2E2CopyConstruct );

	cout<<"cFibElement * pList2E2Copy = list2E2.copy();"<<endl;
	cFibElement * pList2E2Copy = list2E2.copy();

	iReturn += testCompareTwoEqualObjects( *pList2E2Copy, "pList2E2Copy", list2E2, "list2E2" );
	//check the getFibElement() methode from cList
	if ( NULL == pList2E2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous fib -elementpointer for the listelement are correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the listelement are not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cList
	if ( NULL == pList2E2Copy->getSuperiorFibElement() ){
	
		cout<<"The superior fib -elementpointer for the listelement are correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the listelement are not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( pList2E2Copy );

	cout<<"cFibElement * pList2E2CopyElement = list2E2.copyElement( 'u', 1 );"<<endl;
	cFibElement * pList2E2CopyElement = list2E2.copyElement( 'u', 1 );

	if ( pList2E2CopyElement->equalElement( list2E2 ) ){
	
		cout<<"The pList2E2CopyElement fib -element is equal to list2E2. "<<endl;
	}else{
		cerr<<"Error: The pList2E2CopyElement fib -element is not equal to list2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pList2E2CopyElement );
	delete pList2E2CopyElement;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a listobject with more then one listelement and more than two underobjects"<<endl;

	//a limb with more then one listelement and pointelement
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cPoint point2;"<<endl;
	cPoint point2;
	cout<<"cVectorPosition vecPosition1E2( 2 );"<<endl;
	cVectorPosition vecPosition1E2( 2 );
	cout<<"cPoint point1E2( &vecPosition1E2 );"<<endl;
	cPoint point1E2( &vecPosition1E2 );
	cout<<"cVectorPosition vecPosition2E2( 2 );"<<endl;
	cVectorPosition vecPosition2E2( 2 );
	cout<<"vecPosition2E2.setValue( 1, 1 );"<<endl;
	vecPosition2E2.setValue( 1, 1 );
	cout<<"cPoint point2E2( &vecPosition2E2 );"<<endl;
	cPoint point2E2( &vecPosition2E2 );
	cout<<"cVectorPosition vecPosition3E2( 2 );"<<endl;
	cVectorPosition vecPosition3E2( 2 );
	cout<<"vecPosition3E2.setValue( 2, 2 );"<<endl;
	vecPosition3E2.setValue( 2, 2 );
	cout<<"cPoint point3E2( &vecPosition3E2 );"<<endl;
	cPoint point3E2( &vecPosition3E2 );
	cout<<"cVectorPosition vecPosition4E2( 2 );"<<endl;
	cVectorPosition vecPosition4E2( 2 );
	cout<<"vecPosition4E2.setValue( 1, 2 );"<<endl;
	vecPosition4E2.setValue( 1, 2 );
	cout<<"vecPosition4E2.setValue( 2, 2 );"<<endl;
	vecPosition4E2.setValue( 2, 2 );
	cout<<"cPoint point4E2( &vecPosition4E2 );"<<endl;
	cPoint point4E2( &vecPosition4E2 );
	cout<<"cList list1E2( &point1, &point1E2 );"<<endl;
	cList list1E2( &point1, &point1E2 );
	cout<<"cList list1E4( &point2, &point2E2 );"<<endl;
	cList list1E4( &point2, &point2E2 );
	cout<<"list1E4.addUnderobject( &list1E2 );"<<endl;
	list1E4.addUnderobject( &list1E2 );
	cout<<"list1E4.addUnderobject( &point3E2 );"<<endl;
	list1E4.addUnderobject( &point3E2 );
	cout<<"list1E4.addUnderobject( &point4E2 );"<<endl;
	list1E4.addUnderobject( &point4E2 );

	cout<<endl<<"cList pList1E4CopyConstruct( list1E4 );"<<endl;
	cList pList1E4CopyConstruct( list1E4 );

	if ( pList1E4CopyConstruct.equalElement( list1E4 ) ){
	
		cout<<"The pList1E4CopyConstruct fib -element is equal to list1E4. "<<endl;
	}else{
		cerr<<"Error: The pList1E4CopyConstruct fib -element is not equal to list1E4."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( pList1E4CopyConstruct );

	cout<<"cFibElement * pList1E4Copy = list1E4.copy();"<<endl;
	cFibElement * pList1E4Copy = list1E4.copy();

	iReturn += testCompareTwoEqualObjects(
		*pList1E4Copy, "pList1E4Copy",
		list1E4, "list1E4" );
	//check the getFibElement() methode from cList
	if ( list1E4.getFibElement( -1 ) == pList1E4Copy->getFibElement( -1 ) ){
	
		cout<<"The previous fib -elementpointer for the listelement are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the listelement are not equal."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cList
	if ( list1E4.getSuperiorFibElement() == pList1E4Copy->getSuperiorFibElement() ){
	
		cout<<"The superior fib -elementpointer for the listelement are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the listelement are not equal."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( pList1E4Copy );

	cout<<"cFibElement * pList1E4CopyElement = list1E4.copyElement();"<<endl;
	cFibElement * pList1E4CopyElement = list1E4.copyElement();

	if ( pList1E4CopyElement->equalElement( list1E4 ) ){
	
		cout<<"The pList1E4CopyElement fib -element is equal to list1E4. "<<endl;
	}else{
		cerr<<"Error: The pList1E4CopyElement fib -element is not equal to list1E4."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pList1E4CopyElement );
	delete pList1E4CopyElement;


	return iReturn;
}




/**
 * This method tests a in the xml -format stored cList.
 * The listelement can just have points as underobjects. Every
 * pointunderobject has an Positionsvector with exactly oner value.
 *
 * @param szFilename the name of the file wher the cList is stored
 * @param uiNumberUnderPoints the number of underobjects which are points
 * 	in the listelement
 * @param vecPointValues a vector with values of the positionsvectors in
 * 	the pointunderobjects
 * @return the number of errors occured in the test
 */
int testXmlList( const string szFilename,
	unsigned int uiNumberUnderPoints, vector<int> vecPointValues){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cList:"<<endl;
	
	TiXmlDocument xmlDocVectorProperty( szFilename );
	bool loadOkay = xmlDocVectorProperty.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocVectorProperty );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();
		
		const string szListElementName = "list";
		if ( szElementName == szListElementName ){
			cout<<"The root element is correctly named \""<< szListElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szListElementName <<"\"."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	xmlHandleRoot = TiXmlHandle( pXmlElement );
	TiXmlElement * pXmlElementPoint = xmlHandleRoot.FirstChild().Element();
	
	if ( uiNumberUnderPoints == 0 ){
	
		if ( ! pXmlElementPoint ){
			cout<<"The list contains correctly no underobjects. "<<endl;
		
		}else{
			cerr<<"Error: The list contains underobjects, but it shouldn't."<<endl;
			iReturn++;
		}
		return iReturn;
	}//else
	
	TiXmlHandle xmlHandlePoint(0);
	unsigned int uiActualUnderPoint = 1;
	
	for( ; pXmlElementPoint;
			pXmlElementPoint = pXmlElementPoint->NextSiblingElement(), uiActualUnderPoint++ ){
	
		if ( pXmlElementPoint ) {
			string szElementName = pXmlElementPoint->Value();
			
			const string szListElementName = "point";
			if ( szElementName == szListElementName ){
				cout<<"The underobject element is correctly named \""<< szListElementName <<"\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the underobject element is "<< szElementName <<" and not \""<< szListElementName <<"\"."<<endl;
				iReturn++;
			}
	
		}else{// pXmlElement == NULL ->no root handle
			cerr<<"Error: No pointelement handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
			return iReturn;
		}

		xmlHandlePoint = TiXmlHandle( pXmlElementPoint );
		pXmlElement = xmlHandlePoint.FirstChild().Element();

		if ( pXmlElement ) {
			string szElementName = pXmlElement->Value();
	
			if ( szElementName == "vector" ){
				cout<<"The root element is correctly named \"vector\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"vector\"."<<endl;
				iReturn++;
			}
			const char * szVectorXmlType = pXmlElement->Attribute( "type" );
			const string szVectorName( "position" );
			
			if ( szVectorXmlType == NULL ){
				cerr<<"Error: The vector has no type."<<endl;
				iReturn++;
			}else if ( szVectorName == szVectorXmlType ) {
				cout<<"The type of the vector is correctly \""<< szVectorName <<"\". "<<endl;
			}else{
				cerr<<"Error: The type of the vector is \""<< szVectorXmlType
					<<"\", but should be \""<< szVectorName <<"\"."<<endl;
				iReturn++;
			}
	
		}else{// pXmlElement == NULL ->no root handle
			cerr<<"Error: No vector handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
			return iReturn;
		}
		
		TiXmlHandle xmlHandleVectorRoot = TiXmlHandle( pXmlElement );
		pXmlElement = xmlHandleVectorRoot.FirstChild().Element();
		
		if ( pXmlElement == NULL ){
			cerr<<"Error: No elements in this vector."<<endl;
			iReturn++;
			return iReturn;
		}
	
		string szElementName = pXmlElement->Value();
		
		int iNumberOfElement = 1;
		int iReadedNumberOfElement = 0;
		if ( pXmlElement->Attribute( "number", & iReadedNumberOfElement ) ){
			iNumberOfElement = iReadedNumberOfElement;
			
			cout<<"Reading the "<< iNumberOfElement <<"'th numbert element of the type "<<
				szElementName <<" . "<<endl;
		}else{
			cout<<"Reading the "<< iNumberOfElement <<"'th element of the type "<<
				szElementName <<" . "<<endl;
		}
		
		//the elementtype the actual element should have
		string szTargetElementType( "value" );
		
		if ( iNumberOfElement < 1 ){
			cerr<<"Error: Ther couldn't be a 0'th vectorelement."<<endl;
			iReturn++;
		}else if ( 1 < iNumberOfElement ){
			cerr<<"Error: Ther couldn't be a "<< iNumberOfElement <<
				"'th vectorelement, because the vector has yust "<<
					1 <<" elements."<<endl;
			iReturn++;
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
			if ( iNumberOfElement == 1 ){
				double dValue;
				int iReadValues = sscanf ( pcValue, "%lf", & dValue );
				if ( iReadValues != 0){
					if ( dValue == vecPointValues[ uiActualUnderPoint - 1 ] ){
						cout<<"The value of the element is correct."<<endl;
					}else{
						cerr<<"Error: The value of the element should be : "<<
							vecPointValues[ uiActualUnderPoint - 1 ] <<endl;
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
	if ( uiNumberUnderPoints != uiActualUnderPoint - 1 ){
		cerr<<"Error: Ther are "<< (uiActualUnderPoint - 1) <<
			" underobjects in the listelement, but it should be "<<
			uiNumberUnderPoints <<" ."<<endl;
		iReturn++;
	}
	
	return iReturn;
}




/**
 * This method tests the storeXml() method of the cList class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an list with no elements"<<endl;

	cout<<"listEmpty listColorSw1( NULL, NULL );"<<endl;
	cList listEmpty( NULL, NULL );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlListFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "listEmpty.xml" );
	ofstream * pFileVectorPostion = new ofstream( szXmlListFileName );
	
	bool bStoreSuccesfull = listEmpty.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cList was stored successfull to the file \""<< szXmlListFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cList to the file \""<< szXmlListFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	vector<int> vecPointValues( 5, 0 );
	
	iReturn += testXmlList( szXmlListFileName, 0, vecPointValues );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an list with 3 points as underobjects"<<endl;

	//list with 3 D Listvector
	cout<<"cVectorPosition vecPosition1E1( 1 );"<<endl;
	cVectorPosition vecPosition1E1( 1 );
	cout<<"vecPosition1E1.setValue( 1, 1 );"<<endl;
	vecPosition1E1.setValue( 1, 1 );
	vecPointValues[0] = 1;
	cout<<"cPoint point1E1( &vecPosition1E1 );"<<endl;
	cPoint point1E1( &vecPosition1E1 );
	cout<<"vecPosition1E1.setValue( 1, 2 );"<<endl;
	vecPosition1E1.setValue( 1, 2 );
	vecPointValues[1] = 2;
	cout<<"cPoint point2E1( &vecPosition1E1 );"<<endl;
	cPoint point2E1( &vecPosition1E1 );
	cout<<"vecPosition1E1.setValue( 1, 3 );"<<endl;
	vecPosition1E1.setValue( 1, 3 );
	vecPointValues[2] = 3;
	cout<<"cPoint point3E1( &vecPosition1E1 );"<<endl;
	cPoint point3E1( &vecPosition1E1 );

	cout<<"cList listE3( &point1E1, &point2E1 );"<<endl;
	cList listE3( &point1E1, &point2E1 );
	cout<<"listE3.addUnderobject( &point3E1, 3 );"<<endl;
	listE3.addUnderobject( &point3E1, 3  );

	szFileNameBuffer[0] = 0;
	szXmlListFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "listE3.xml" );
	pFileVectorPostion = new ofstream( szXmlListFileName );
	
	bStoreSuccesfull = listE3.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cList was stored successfull to the file \""<< szXmlListFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cList to the file \""<< szXmlListFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlList( szXmlListFileName, 3, vecPointValues );

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an empty list"<<endl;

	cout<<"cList listEmpty( NULL, NULL );"<<endl;
	cList listEmpty( NULL, NULL );


	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "listEmpty.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bool bStoreSuccesfull = listEmpty.store( *pFile );
	delete pFile;
	
	if ( ! bStoreSuccesfull ){
	
		cout<<"The data was correctly not stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" was successfull."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an list with one underobject"<<endl;

	cout<<"cVectorPosition vecPosition1E1( 1 );"<<endl;
	cVectorPosition vecPosition1E1( 1 );
	cout<<"vecPosition1E1.setValue( 1, 1 );"<<endl;
	vecPosition1E1.setValue( 1, 1 );
	cout<<"cPoint point1E1( &vecPosition1E1 );"<<endl;
	cPoint point1E1( &vecPosition1E1 );
	cout<<"cList listE1( &point1E1, NULL );"<<endl;
	cList listE1( &point1E1, NULL );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "listE1.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = listE1.store( *pFile );
	delete pFile;
	
	if ( ! bStoreSuccesfull ){
	
		cout<<"The data was correctly not stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" was successfull."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an list with two underobjects"<<endl;

	cout<<"vecPosition1E1.setValue( 1, 2 );"<<endl;
	vecPosition1E1.setValue( 1, 2 );
	cout<<"cPoint point2E1( &vecPosition1E1 );"<<endl;
	cPoint point2E1( &vecPosition1E1 );
	cout<<"cList listE2( &point1E1, &point2E1 );"<<endl;
	cList listE2( &point1E1, &point2E1 );

	//test get compressed size
	unsigned int uiCompressedSize = 4 + 21 + 21;
	if ( (unsigned int)(listE2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			listE2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "listE2.fib" );
	 pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = listE2.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cListE2[] = { (char)0x14, (char)0x02, (char)0x00, (char)0x82, (char)0x00, (char)0x00  };//Bits: 0001 0100 ; 0000 0010; 0000 0000; 1000 0010; 0000 0000; 0000 0000
	iReturn += compareBytsWithFile( szFileNameBuffer, cListE2, 6 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an list with tree underobjects"<<endl;

	cout<<"vecPosition1E1.setValue( 1, 3 );"<<endl;
	vecPosition1E1.setValue( 1, 3 );
	cout<<"cPoint point3E1( &vecPosition1E1 );"<<endl;
	cPoint point3E1( &vecPosition1E1 );
	cout<<"cList listE3( &point1E1, &point2E1 );"<<endl;
	cList listE3( &point1E1, &point2E1 );
	cout<<"listE3.addUnderobject( &point3E1, 3 );"<<endl;
	listE3.addUnderobject( &point3E1, 3  );

	//test get compressed size
	uiCompressedSize = 4 + 8 + 21 + 21 + 21;
	if ( (unsigned int)(listE3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			listE3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "listE3.fib" );
	 pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = listE3.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cListE3[] = { (char)0x35, (char)0x10, (char)0x02, (char)0x00, (char)0x82, (char)0x00, (char)0x40, (char)0x18, (char)0x00, (char)0x00  };
		//Bits:0011 0100 ; 0001 0000; 0000 0010; 0000 0000; 1000 0010; 0000 0000; 0100 0000; 0001 1000; 0000 0000; 0000 0000
	iReturn += compareBytsWithFile( szFileNameBuffer, cListE3, 10 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an list with 255 underobjects"<<endl;

	cout<<"cList * pListE255 = new cList( NULL, NULL );"<<endl;
	cList * pListE255 = new cList( NULL, NULL );
	
	uiCompressedSize = 4 + 8 + 5 * 255;
	char cListE255[ uiCompressedSize / 8 + 1 ];
	memset( cListE255, (char)0x00 , (uiCompressedSize / 8 + 1) );
	
	cListE255[0] = (char)0xF5;
	cListE255[1] = (char)0x0F;
	
	const char cPointEmptyBits = (char)0x12;
	unsigned int uiActualBit = 12;
	
	for ( unsigned int uiActualUnderobject = 1; uiActualUnderobject <= 255;
			uiActualUnderobject++, uiActualBit += 5 ){
		
		pListE255->addUnderobject( new cPoint() );
		
		cListE255[ uiActualBit / 8 ] |= cPointEmptyBits << (uiActualBit % 8);
		cListE255[ uiActualBit / 8 + 1 ] |= cPointEmptyBits >> (8 - (uiActualBit % 8));
	}
	
	//test get compressed size
	if ( (unsigned int)(pListE255->getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			pListE255->getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "listE255.fib" );
	 pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = pListE255->store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	iReturn += compareBytsWithFile( szFileNameBuffer, cListE255, (uiCompressedSize / 8 + 1) );
	cFibElement::deleteObject( pListE255 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an list with 256 underobjects"<<endl;

	cout<<"cList * pListE256 = new cList( NULL, NULL )"<<endl;
	cList * pListE256 = new cList( NULL, NULL );
	
	uiCompressedSize = 4 + 64 + 5 * 256;
	char cListE256[ uiCompressedSize / 8 + 1 ];
	memset( cListE256, (char)0x00 , (uiCompressedSize / 8 + 1) );
	
	cListE256[0] = (char)0x06;
	cListE256[1] = (char)0x10;
	cListE256[2] = (char)0x00;
	cListE256[3] = (char)0x00;
	cListE256[4] = (char)0x00;
	cListE256[5] = (char)0x00;
	cListE256[6] = (char)0x00;
	cListE256[7] = (char)0x00;
	cListE256[8] = (char)0x00;
	
	uiActualBit = 4 + 64;
	
	for ( unsigned int uiActualUnderobject = 1; uiActualUnderobject <= 256;
			uiActualUnderobject++, uiActualBit += 5 ){
		
		pListE256->addUnderobject( new cPoint() );
		
		cListE256[ uiActualBit / 8 ] |= cPointEmptyBits << (uiActualBit % 8);
		cListE256[ uiActualBit / 8 + 1 ] |= cPointEmptyBits >> (8 - (uiActualBit % 8));
	}
	
	//test get compressed size
	if ( (unsigned int)(pListE256->getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			pListE256->getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "listE256.fib" );
	 pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = pListE256->store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	iReturn += compareBytsWithFile( szFileNameBuffer, cListE256, (uiCompressedSize / 8 + 1) );
	cFibElement::deleteObject( pListE256 );


	return iReturn;
}


/**
 * This function tests the methods for the underobjects of the list.
 *
 * methods tested:
 * 	- unsignedIntFib getNumberOfUnderobjects() const;
 * 	- cFibElement * getUnderobject( unsignedIntFib iNumberOfUnderobject=1 );
 * 	- bool addUnderobject( cFibElement * pUnderobject, unsignedIntFib iPosition=1 );
 * 	- unsignedIntFib addUnderobjects( list<cFibElement*> liUnderobjects, unsignedIntFib iPosition=1 );
 * 	- bool deleteUnderobject( unsignedIntFib iPositionUnderobject, bool bDeleteOld=true);
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testUnderobject( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the underobjects of the list"<<endl;

	cout<<"cList list1( NULL, NULL );"<<endl;
	cList list1( NULL, NULL );
	
	list<cFibElement*> liListElements;

	//test getNumberOfUnderobjects()
	if ( list1.getNumberOfUnderobjects() == liListElements.size() ){
	
		cout<<"The listelement has correctly "<< list1.getNumberOfUnderobjects()
			<<" underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement has "<< list1.getNumberOfUnderobjects() <<
			", but should have "<<liListElements.size() <<endl;
		iReturn++;
	}
	//test getUnderobject()
	list<cFibElement*>::iterator itrListElement = liListElements.begin();
	for ( unsignedIntFib uiActualFibElement = 1;
			uiActualFibElement <= list1.getNumberOfUnderobjects();
			uiActualFibElement++ ){
		
		if ( itrListElement != liListElements.end() ){
			const cFibElement * pUnderObject = list1.getUnderobject( uiActualFibElement );
			if ( pUnderObject != NULL ){
				if ( pUnderObject == (*itrListElement) ){
				
					cout<<"The "<< uiActualFibElement <<"'th underobject is correct. "<<endl;
				}else{
					cerr<<"Error: The "<< uiActualFibElement <<"'th underobject is not correct." <<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Ther is no "<< uiActualFibElement <<"'th underobject (NULL is returned)." <<endl;
				iReturn++;
			}
			itrListElement++;
		}else{
			cerr<<"Error: The list has an "<< uiActualFibElement <<
				"'th underobject, but shouldn't have one."<<endl;
			iReturn++;
		}
	}
	cFibElement * pUnderObject0 = list1.getUnderobject( 0 );
	if ( pUnderObject0 == NULL ){
		cout<<"Ther is correctly no "<< 0 <<"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< 0 <<"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	cFibElement * pUnderObjectEnd = list1.getUnderobject( list1.getNumberOfUnderobjects() + 1 );
	if ( pUnderObjectEnd == NULL ){
		cout<<"Ther is correctly no "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing addUnderobject() method"<<endl;
	
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	//test addUnderobject()
	cout<<"list1.addUnderobject( &point1 );"<<endl;
	list1.addUnderobject( &point1 );
	liListElements.push_back( &point1 );

	//test getNumberOfUnderobjects()
	if ( list1.getNumberOfUnderobjects() == liListElements.size() ){
	
		cout<<"The listelement has correctly "<< list1.getNumberOfUnderobjects()
			<<" underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement has "<< list1.getNumberOfUnderobjects() <<
			", but should have "<<liListElements.size() <<endl;
		iReturn++;
	}
	//test getUnderobject()
	itrListElement = liListElements.begin();
	for ( unsignedIntFib uiActualFibElement = 1;
			uiActualFibElement <= list1.getNumberOfUnderobjects();
			uiActualFibElement++ ){
		
		if ( itrListElement != liListElements.end() ){
			const cFibElement * pUnderObject = list1.getUnderobject( uiActualFibElement );
			if ( pUnderObject != NULL ){
				if ( pUnderObject == (*itrListElement) ){
				
					cout<<"The "<< uiActualFibElement <<"'th underobject is correct. "<<endl;
				}else{
					cerr<<"Error: The "<< uiActualFibElement <<"'th underobject is not correct." <<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Ther is no "<< uiActualFibElement <<"'th underobject (NULL is returned)." <<endl;
				iReturn++;
			}
			itrListElement++;
		}else{
			cerr<<"Error: The list has an "<< uiActualFibElement <<
				"'th underobject, but shouldn't have one."<<endl;
			iReturn++;
		}
	}
	pUnderObject0 = list1.getUnderobject( 0 );
	if ( pUnderObject0 == NULL ){
		cout<<"Ther is correctly no "<< 0 <<"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< 0 <<"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	pUnderObjectEnd = list1.getUnderobject( list1.getNumberOfUnderobjects() + 1 );
	if ( pUnderObjectEnd == NULL ){
		cout<<"Ther is correctly no "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}

	cout<<"cPoint point2;"<<endl;
	cPoint point2;
	//test addUnderobject()
	cout<<"list1.addUnderobject( &point2 );"<<endl;
	list1.addUnderobject( &point2 );
	liListElements.push_front( &point2 );

	//test getNumberOfUnderobjects()
	if ( list1.getNumberOfUnderobjects() == liListElements.size() ){
	
		cout<<"The listelement has correctly "<< list1.getNumberOfUnderobjects()
			<<" underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement has "<< list1.getNumberOfUnderobjects() <<
			", but should have "<<liListElements.size() <<endl;
		iReturn++;
	}
	//test getUnderobject()
	itrListElement = liListElements.begin();
	for ( unsignedIntFib uiActualFibElement = 1;
			uiActualFibElement <= list1.getNumberOfUnderobjects();
			uiActualFibElement++ ){
		
		if ( itrListElement != liListElements.end() ){
			const cFibElement * pUnderObject = list1.getUnderobject( uiActualFibElement );
			if ( pUnderObject != NULL ){
				if ( pUnderObject == (*itrListElement) ){
				
					cout<<"The "<< uiActualFibElement <<"'th underobject is correct. "<<endl;
				}else{
					cerr<<"Error: The "<< uiActualFibElement <<"'th underobject is not correct." <<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Ther is no "<< uiActualFibElement <<"'th underobject (NULL is returned)." <<endl;
				iReturn++;
			}
			itrListElement++;
		}else{
			cerr<<"Error: The list has an "<< uiActualFibElement <<
				"'th underobject, but shouldn't have one."<<endl;
			iReturn++;
		}
	}
	pUnderObject0 = list1.getUnderobject( 0 );
	if ( pUnderObject0 == NULL ){
		cout<<"Ther is correctly no "<< 0 <<"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< 0 <<"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	pUnderObjectEnd = list1.getUnderobject( list1.getNumberOfUnderobjects() + 1 );
	if ( pUnderObjectEnd == NULL ){
		cout<<"Ther is correctly no "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}

	cout<<"cPoint point3;"<<endl;
	cPoint point3;
	cout<<"cPoint point4;"<<endl;
	cPoint point4;
	cout<<"cPoint point5;"<<endl;
	cPoint point5;
	//test addUnderobject()
	cout<<"list1.addUnderobject( &point3 );"<<endl;
	list1.addUnderobject( &point3 );
	liListElements.push_front( &point3 );
	cout<<"list1.addUnderobject( &point4 );"<<endl;
	list1.addUnderobject( &point4 );
	liListElements.push_front( &point4 );
	cout<<"list1.addUnderobject( &point5 );"<<endl;
	list1.addUnderobject( &point5 );
	liListElements.push_front( &point5 );

	//test getNumberOfUnderobjects()
	if ( list1.getNumberOfUnderobjects() == liListElements.size() ){
	
		cout<<"The listelement has correctly "<< list1.getNumberOfUnderobjects()
			<<" underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement has "<< list1.getNumberOfUnderobjects() <<
			", but should have "<<liListElements.size() <<endl;
		iReturn++;
	}
	//test getUnderobject()
	itrListElement = liListElements.begin();
	for ( unsignedIntFib uiActualFibElement = 1;
			uiActualFibElement <= list1.getNumberOfUnderobjects();
			uiActualFibElement++ ){
		
		if ( itrListElement != liListElements.end() ){
			const cFibElement * pUnderObject = list1.getUnderobject( uiActualFibElement );
			if ( pUnderObject != NULL ){
				if ( pUnderObject == (*itrListElement) ){
				
					cout<<"The "<< uiActualFibElement <<"'th underobject is correct. "<<endl;
				}else{
					cerr<<"Error: The "<< uiActualFibElement <<"'th underobject is not correct." <<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Ther is no "<< uiActualFibElement <<"'th underobject (NULL is returned)." <<endl;
				iReturn++;
			}
			itrListElement++;
		}else{
			cerr<<"Error: The list has an "<< uiActualFibElement <<
				"'th underobject, but shouldn't have one."<<endl;
			iReturn++;
		}
	}
	pUnderObject0 = list1.getUnderobject( 0 );
	if ( pUnderObject0 == NULL ){
		cout<<"Ther is correctly no "<< 0 <<"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< 0 <<"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	pUnderObjectEnd = list1.getUnderobject( list1.getNumberOfUnderobjects() + 1 );
	if ( pUnderObjectEnd == NULL ){
		cout<<"Ther is correctly no "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing adding underobjects to the end of the list"<<endl;
	
	cout<<"cPoint point6;"<<endl;
	cPoint point6;
	//test addUnderobject()
	cout<<"list1.addUnderobject( &point6, liListElements.size() + 1 );"<<endl;
	list1.addUnderobject( &point6, liListElements.size() + 1 );
	liListElements.push_back( &point6 );

	//test getNumberOfUnderobjects()
	if ( list1.getNumberOfUnderobjects() == liListElements.size() ){
	
		cout<<"The listelement has correctly "<< list1.getNumberOfUnderobjects()
			<<" underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement has "<< list1.getNumberOfUnderobjects() <<
			", but should have "<<liListElements.size() <<endl;
		iReturn++;
	}
	//test getUnderobject()
	itrListElement = liListElements.begin();
	for ( unsignedIntFib uiActualFibElement = 1;
			uiActualFibElement <= list1.getNumberOfUnderobjects();
			uiActualFibElement++ ){
		
		if ( itrListElement != liListElements.end() ){
			const cFibElement * pUnderObject = list1.getUnderobject( uiActualFibElement );
			if ( pUnderObject != NULL ){
				if ( pUnderObject == (*itrListElement) ){
				
					cout<<"The "<< uiActualFibElement <<"'th underobject is correct. "<<endl;
				}else{
					cerr<<"Error: The "<< uiActualFibElement <<"'th underobject is not correct." <<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Ther is no "<< uiActualFibElement <<"'th underobject (NULL is returned)." <<endl;
				iReturn++;
			}
			itrListElement++;
		}else{
			cerr<<"Error: The list has an "<< uiActualFibElement <<
				"'th underobject, but shouldn't have one."<<endl;
			iReturn++;
		}
	}
	pUnderObject0 = list1.getUnderobject( 0 );
	if ( pUnderObject0 == NULL ){
		cout<<"Ther is correctly no "<< 0 <<"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< 0 <<"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	pUnderObjectEnd = list1.getUnderobject( list1.getNumberOfUnderobjects() + 1 );
	if ( pUnderObjectEnd == NULL ){
		cout<<"Ther is correctly no "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}


	cout<<"cPoint point7;"<<endl;
	cPoint point7;
	//test addUnderobject()
	cout<<"list1.addUnderobject( &point7, 102544 );"<<endl;
	list1.addUnderobject( &point7, 102544 );
	liListElements.push_back( &point7 );

	//test getNumberOfUnderobjects()
	if ( list1.getNumberOfUnderobjects() == liListElements.size() ){
	
		cout<<"The listelement has correctly "<< list1.getNumberOfUnderobjects()
			<<" underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement has "<< list1.getNumberOfUnderobjects() <<
			", but should have "<<liListElements.size() <<endl;
		iReturn++;
	}
	//test getUnderobject()
	itrListElement = liListElements.begin();
	for ( unsignedIntFib uiActualFibElement = 1;
			uiActualFibElement <= list1.getNumberOfUnderobjects();
			uiActualFibElement++ ){
		
		if ( itrListElement != liListElements.end() ){
			const cFibElement * pUnderObject = list1.getUnderobject( uiActualFibElement );
			if ( pUnderObject != NULL ){
				if ( pUnderObject == (*itrListElement) ){
				
					cout<<"The "<< uiActualFibElement <<"'th underobject is correct. "<<endl;
				}else{
					cerr<<"Error: The "<< uiActualFibElement <<"'th underobject is not correct." <<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Ther is no "<< uiActualFibElement <<"'th underobject (NULL is returned)." <<endl;
				iReturn++;
			}
			itrListElement++;
		}else{
			cerr<<"Error: The list has an "<< uiActualFibElement <<
				"'th underobject, but shouldn't have one."<<endl;
			iReturn++;
		}
	}
	pUnderObject0 = list1.getUnderobject( 0 );
	if ( pUnderObject0 == NULL ){
		cout<<"Ther is correctly no "<< 0 <<"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< 0 <<"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	pUnderObjectEnd = list1.getUnderobject( list1.getNumberOfUnderobjects() + 1 );
	if ( pUnderObjectEnd == NULL ){
		cout<<"Ther is correctly no "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing adding underobjects on position 1"<<endl;
	
	cout<<"cPoint point8;"<<endl;
	cPoint point8;
	//test addUnderobject()
	cout<<"list1.addUnderobject( &point8, 1 );"<<endl;
	list1.addUnderobject( &point8, 1 );
	liListElements.push_front( &point8 );

	//test getNumberOfUnderobjects()
	if ( list1.getNumberOfUnderobjects() == liListElements.size() ){
	
		cout<<"The listelement has correctly "<< list1.getNumberOfUnderobjects()
			<<" underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement has "<< list1.getNumberOfUnderobjects() <<
			", but should have "<<liListElements.size() <<endl;
		iReturn++;
	}
	//test getUnderobject()
	itrListElement = liListElements.begin();
	for ( unsignedIntFib uiActualFibElement = 1;
			uiActualFibElement <= list1.getNumberOfUnderobjects();
			uiActualFibElement++ ){
		
		if ( itrListElement != liListElements.end() ){
			const cFibElement * pUnderObject = list1.getUnderobject( uiActualFibElement );
			if ( pUnderObject != NULL ){
				if ( pUnderObject == (*itrListElement) ){
				
					cout<<"The "<< uiActualFibElement <<"'th underobject is correct. "<<endl;
				}else{
					cerr<<"Error: The "<< uiActualFibElement <<"'th underobject is not correct." <<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Ther is no "<< uiActualFibElement <<"'th underobject (NULL is returned)." <<endl;
				iReturn++;
			}
			itrListElement++;
		}else{
			cerr<<"Error: The list has an "<< uiActualFibElement <<
				"'th underobject, but shouldn't have one."<<endl;
			iReturn++;
		}
	}
	pUnderObject0 = list1.getUnderobject( 0 );
	if ( pUnderObject0 == NULL ){
		cout<<"Ther is correctly no "<< 0 <<"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< 0 <<"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	pUnderObjectEnd = list1.getUnderobject( list1.getNumberOfUnderobjects() + 1 );
	if ( pUnderObjectEnd == NULL ){
		cout<<"Ther is correctly no "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing adding underobjects on position 3"<<endl;
	
	cout<<"cPoint point9;"<<endl;
	cPoint point9;
	//test addUnderobject()
	cout<<"list1.addUnderobject( &point9, 3 );"<<endl;
	list1.addUnderobject( &point9, 3 );
	itrListElement = liListElements.begin();
	itrListElement++;
	itrListElement++;
	liListElements.insert( itrListElement, &point9 );

	//test getNumberOfUnderobjects()
	if ( list1.getNumberOfUnderobjects() == liListElements.size() ){
	
		cout<<"The listelement has correctly "<< list1.getNumberOfUnderobjects()
			<<" underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement has "<< list1.getNumberOfUnderobjects() <<
			", but should have "<<liListElements.size() <<endl;
		iReturn++;
	}
	//test getUnderobject()
	itrListElement = liListElements.begin();
	for ( unsignedIntFib uiActualFibElement = 1;
			uiActualFibElement <= list1.getNumberOfUnderobjects();
			uiActualFibElement++ ){
		
		if ( itrListElement != liListElements.end() ){
			const cFibElement * pUnderObject = list1.getUnderobject( uiActualFibElement );
			if ( pUnderObject != NULL ){
				if ( pUnderObject == (*itrListElement) ){
				
					cout<<"The "<< uiActualFibElement <<"'th underobject is correct. "<<endl;
				}else{
					cerr<<"Error: The "<< uiActualFibElement <<"'th underobject is not correct." <<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Ther is no "<< uiActualFibElement <<"'th underobject (NULL is returned)." <<endl;
				iReturn++;
			}
			itrListElement++;
		}else{
			cerr<<"Error: The list has an "<< uiActualFibElement <<
				"'th underobject, but shouldn't have one."<<endl;
			iReturn++;
		}
	}
	pUnderObject0 = list1.getUnderobject( 0 );
	if ( pUnderObject0 == NULL ){
		cout<<"Ther is correctly no "<< 0 <<"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< 0 <<"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	pUnderObjectEnd = list1.getUnderobject( list1.getNumberOfUnderobjects() + 1 );
	if ( pUnderObjectEnd == NULL ){
		cout<<"Ther is correctly no "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleting underobjects on position 1"<<endl;
	
	//test deleteUnderobject()
	cout<<"list1.deleteUnderobject( 1, false );"<<endl;
	list1.deleteUnderobject( 1, false );
	liListElements.pop_front();

	//test getNumberOfUnderobjects()
	if ( list1.getNumberOfUnderobjects() == liListElements.size() ){
	
		cout<<"The listelement has correctly "<< list1.getNumberOfUnderobjects()
			<<" underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement has "<< list1.getNumberOfUnderobjects() <<
			", but should have "<<liListElements.size() <<endl;
		iReturn++;
	}
	//test getUnderobject()
	itrListElement = liListElements.begin();
	for ( unsignedIntFib uiActualFibElement = 1;
			uiActualFibElement <= list1.getNumberOfUnderobjects();
			uiActualFibElement++ ){
		
		if ( itrListElement != liListElements.end() ){
			const cFibElement * pUnderObject = list1.getUnderobject( uiActualFibElement );
			if ( pUnderObject != NULL ){
				if ( pUnderObject == (*itrListElement) ){
				
					cout<<"The "<< uiActualFibElement <<"'th underobject is correct. "<<endl;
				}else{
					cerr<<"Error: The "<< uiActualFibElement <<"'th underobject is not correct." <<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Ther is no "<< uiActualFibElement <<"'th underobject (NULL is returned)." <<endl;
				iReturn++;
			}
			itrListElement++;
		}else{
			cerr<<"Error: The list has an "<< uiActualFibElement <<
				"'th underobject, but shouldn't have one."<<endl;
			iReturn++;
		}
	}
	pUnderObject0 = list1.getUnderobject( 0 );
	if ( pUnderObject0 == NULL ){
		cout<<"Ther is correctly no "<< 0 <<"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< 0 <<"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	pUnderObjectEnd = list1.getUnderobject( list1.getNumberOfUnderobjects() + 1 );
	if ( pUnderObjectEnd == NULL ){
		cout<<"Ther is correctly no "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleting underobjects from the end of the list"<<endl;
	
	//test deleteUnderobject()
	cout<<"list1.deleteUnderobject( list1.getNumberOfUnderobjects(), false );"<<endl;
	list1.deleteUnderobject( list1.getNumberOfUnderobjects(), false );
	liListElements.pop_back();

	//test getNumberOfUnderobjects()
	if ( list1.getNumberOfUnderobjects() == liListElements.size() ){
	
		cout<<"The listelement has correctly "<< list1.getNumberOfUnderobjects()
			<<" underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement has "<< list1.getNumberOfUnderobjects() <<
			", but should have "<<liListElements.size() <<endl;
		iReturn++;
	}
	//test getUnderobject()
	itrListElement = liListElements.begin();
	for ( unsignedIntFib uiActualFibElement = 1;
			uiActualFibElement <= list1.getNumberOfUnderobjects();
			uiActualFibElement++ ){
		
		if ( itrListElement != liListElements.end() ){
			const cFibElement * pUnderObject = list1.getUnderobject( uiActualFibElement );
			if ( pUnderObject != NULL ){
				if ( pUnderObject == (*itrListElement) ){
				
					cout<<"The "<< uiActualFibElement <<"'th underobject is correct. "<<endl;
				}else{
					cerr<<"Error: The "<< uiActualFibElement <<"'th underobject is not correct." <<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Ther is no "<< uiActualFibElement <<"'th underobject (NULL is returned)." <<endl;
				iReturn++;
			}
			itrListElement++;
		}else{
			cerr<<"Error: The list has an "<< uiActualFibElement <<
				"'th underobject, but shouldn't have one."<<endl;
			iReturn++;
		}
	}
	pUnderObject0 = list1.getUnderobject( 0 );
	if ( pUnderObject0 == NULL ){
		cout<<"Ther is correctly no "<< 0 <<"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< 0 <<"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	pUnderObjectEnd = list1.getUnderobject( list1.getNumberOfUnderobjects() + 1 );
	if ( pUnderObjectEnd == NULL ){
		cout<<"Ther is correctly no "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleting underobjects on position 3"<<endl;
	
	//test deleteUnderobject()
	cout<<"list1.deleteUnderobject( 3, false );"<<endl;
	list1.deleteUnderobject( 3, false );
	itrListElement = liListElements.begin();
	itrListElement++;
	itrListElement++;
	liListElements.erase( itrListElement );

	//test getNumberOfUnderobjects()
	if ( list1.getNumberOfUnderobjects() == liListElements.size() ){
	
		cout<<"The listelement has correctly "<< list1.getNumberOfUnderobjects()
			<<" underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement has "<< list1.getNumberOfUnderobjects() <<
			", but should have "<<liListElements.size() <<endl;
		iReturn++;
	}
	//test getUnderobject()
	itrListElement = liListElements.begin();
	for ( unsignedIntFib uiActualFibElement = 1;
			uiActualFibElement <= list1.getNumberOfUnderobjects();
			uiActualFibElement++ ){
		
		if ( itrListElement != liListElements.end() ){
			const cFibElement * pUnderObject = list1.getUnderobject( uiActualFibElement );
			if ( pUnderObject != NULL ){
				if ( pUnderObject == (*itrListElement) ){
				
					cout<<"The "<< uiActualFibElement <<"'th underobject is correct. "<<endl;
				}else{
					cerr<<"Error: The "<< uiActualFibElement <<"'th underobject is not correct." <<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Ther is no "<< uiActualFibElement <<"'th underobject (NULL is returned)." <<endl;
				iReturn++;
			}
			itrListElement++;
		}else{
			cerr<<"Error: The list has an "<< uiActualFibElement <<
				"'th underobject, but shouldn't have one."<<endl;
			iReturn++;
		}
	}
	pUnderObject0 = list1.getUnderobject( 0 );
	if ( pUnderObject0 == NULL ){
		cout<<"Ther is correctly no "<< 0 <<"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< 0 <<"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	pUnderObjectEnd = list1.getUnderobject( list1.getNumberOfUnderobjects() + 1 );
	if ( pUnderObjectEnd == NULL ){
		cout<<"Ther is correctly no "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleting underobjects on position 4"<<endl;
	
	//test deleteUnderobject()
	cout<<"list1.deleteUnderobject( 4, false );"<<endl;
	list1.deleteUnderobject( 4, false );
	itrListElement = liListElements.begin();
	itrListElement++;
	itrListElement++;
	itrListElement++;
	liListElements.erase( itrListElement );

	//test getNumberOfUnderobjects()
	if ( list1.getNumberOfUnderobjects() == liListElements.size() ){
	
		cout<<"The listelement has correctly "<< list1.getNumberOfUnderobjects()
			<<" underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement has "<< list1.getNumberOfUnderobjects() <<
			", but should have "<<liListElements.size() <<endl;
		iReturn++;
	}
	//test getUnderobject()
	itrListElement = liListElements.begin();
	for ( unsignedIntFib uiActualFibElement = 1;
			uiActualFibElement <= list1.getNumberOfUnderobjects();
			uiActualFibElement++ ){
		
		if ( itrListElement != liListElements.end() ){
			const cFibElement * pUnderObject = list1.getUnderobject( uiActualFibElement );
			if ( pUnderObject != NULL ){
				if ( pUnderObject == (*itrListElement) ){
				
					cout<<"The "<< uiActualFibElement <<"'th underobject is correct. "<<endl;
				}else{
					cerr<<"Error: The "<< uiActualFibElement <<"'th underobject is not correct." <<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Ther is no "<< uiActualFibElement <<"'th underobject (NULL is returned)." <<endl;
				iReturn++;
			}
			itrListElement++;
		}else{
			cerr<<"Error: The list has an "<< uiActualFibElement <<
				"'th underobject, but shouldn't have one."<<endl;
			iReturn++;
		}
	}
	pUnderObject0 = list1.getUnderobject( 0 );
	if ( pUnderObject0 == NULL ){
		cout<<"Ther is correctly no "<< 0 <<"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< 0 <<"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	pUnderObjectEnd = list1.getUnderobject( list1.getNumberOfUnderobjects() + 1 );
	if ( pUnderObjectEnd == NULL ){
		cout<<"Ther is correctly no "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing deleting an underobject from memory"<<endl;
	
	//test deleteUnderobject()
	cout<<"cPoint * pPoint1 = new cPoint();"<<endl;
	cPoint * pPoint1 = new cPoint();
	cout<<"list1.addUnderobject( pPoint1 );"<<endl;
	list1.addUnderobject( pPoint1 );
	cout<<"list1.deleteUnderobject( 1, true );"<<endl;
	list1.deleteUnderobject( 1, true );

	//test getNumberOfUnderobjects()
	if ( list1.getNumberOfUnderobjects() == liListElements.size() ){
	
		cout<<"The listelement has correctly "<< list1.getNumberOfUnderobjects()
			<<" underobjects. "<<endl;
	}else{
		cerr<<"Error: The listelement has "<< list1.getNumberOfUnderobjects() <<
			", but should have "<<liListElements.size() <<endl;
		iReturn++;
	}
	//test getUnderobject()
	itrListElement = liListElements.begin();
	for ( unsignedIntFib uiActualFibElement = 1;
			uiActualFibElement <= list1.getNumberOfUnderobjects();
			uiActualFibElement++ ){
		
		if ( itrListElement != liListElements.end() ){
			const cFibElement * pUnderObject = list1.getUnderobject( uiActualFibElement );
			if ( pUnderObject != NULL ){
				if ( pUnderObject == (*itrListElement) ){
				
					cout<<"The "<< uiActualFibElement <<"'th underobject is correct. "<<endl;
				}else{
					cerr<<"Error: The "<< uiActualFibElement <<"'th underobject is not correct." <<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Ther is no "<< uiActualFibElement <<"'th underobject (NULL is returned)." <<endl;
				iReturn++;
			}
			itrListElement++;
		}else{
			cerr<<"Error: The list has an "<< uiActualFibElement <<
				"'th underobject, but shouldn't have one."<<endl;
			iReturn++;
		}
	}
	pUnderObject0 = list1.getUnderobject( 0 );
	if ( pUnderObject0 == NULL ){
		cout<<"Ther is correctly no "<< 0 <<"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< 0 <<"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}
	pUnderObjectEnd = list1.getUnderobject( list1.getNumberOfUnderobjects() + 1 );
	if ( pUnderObjectEnd == NULL ){
		cout<<"Ther is correctly no "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject (NULL is returned)."<<endl;
	}else{
		cerr<<"Error: Ther is an "<< list1.getNumberOfUnderobjects() + 1 <<
			"'th underobject, but shouldn't." <<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing addUnderobjects()"<<endl;
	
	cout<<"pListTest = new cList( NULL, NULL );"<<endl;
	cList * pListTest = new cList( NULL, NULL );
	cList * pListCompare = new cList( NULL, NULL );
	unsigned long ulPointCounter = 0;
	for ( unsigned int iteration = 0; iteration < 256; iteration++ ){
		
		if ( rand() % 16 == 0 ){
			//create a new listelement
			cFibElement::deleteObject( pListTest );
			cFibElement::deleteObject( pListCompare );
			cout<<endl<<"pListTest = new cList( NULL, NULL );"<<endl;
			pListTest = new cList( NULL, NULL );
			pListCompare = new cList( NULL, NULL );
		}
		//choos position wher to add
		unsignedIntFib iPosition = rand() % (pListTest->getNumberOfUnderobjects() + 16);
		//create pointelements to insert
		cout<<endl<<"list<cFibElement*> liPointsToInsert;"<<endl;
		list<cFibElement*> liPointsToInsert;
		const unsigned int uiCountPointsToInsert = rand() % 64;
		cout<<"Creating "<< uiCountPointsToInsert <<" underobjects to insert:"<<endl;
		for ( unsigned int uiActualPoint = 0;
				uiActualPoint < uiCountPointsToInsert; uiActualPoint++ ){
			
			ulPointCounter++;
			cout<<"   cVectorPosition vecPosition( 1 );"<<endl;
			cVectorPosition vecPosition( 1 );
			cout<<"   vecPosition.setValue( 1, ulPointCounter );"<<endl;
			vecPosition.setValue( 1, ulPointCounter );
			cout<<"   cPoint * pPoint = new cPoint( &vecPosition );"<<endl;
			cPoint * pPoint = new cPoint( &vecPosition );
			cout<<"   liPointsToInsert.push_back( pPoint );"<<endl;
			liPointsToInsert.push_back( pPoint );
			
			cPoint * pPointCompare = new cPoint( &vecPosition );
			if ( 0 < iPosition ){
				pListCompare->addUnderobject( pPointCompare, iPosition + uiActualPoint );
			}else{
				pListCompare->addUnderobject( pPointCompare, uiActualPoint + 1 );
			}
		}
		//add points
		cout<<"pListTest->addUnderobjects( liPointsToInsert, iPosition );"<<endl;
		pListTest->addUnderobjects( liPointsToInsert, iPosition );
	
		if ( pListTest->equal( *pListCompare ) ){
		
			cout<<"The underobjects wher correctly added. "<<endl;
		}else{
			cerr<<"Error: The underobjects wher not correctly added."<<endl;
			iReturn++;
		}
	}
	cFibElement::deleteObject( pListTest );
	cFibElement::deleteObject( pListCompare );

	return iReturn;
}


/**
 * This function tests the methods for the underobjects of the list.
 * The test uses random generated underobjects and checks random methods.
 *
 * methods tested:
 * 	- unsignedIntFib getNumberOfUnderobjects() const;
 * 	- cFibElement * getUnderobject( unsignedIntFib iNumberOfUnderobject=1 );
 * 	- list< cFibElement * > getUnderobjects( unsignedIntFib iNumberOfFirstUnderobject=1, unsignedIntFib iNumberOfToReturnUnderobjects=0 )
 * 	- bool addUnderobject( cFibElement * pUnderobject, unsignedIntFib iPosition=1 );
 * 	- unsignedIntFib addUnderobjects( list<cFibElement*> liUnderobjects, unsignedIntFib iPosition=1 );
 * 	- bool deleteUnderobject( unsignedIntFib iPositionUnderobject, bool bDeleteOld=true);
 * 	- bool deleteUnderobjects( unsignedIntFib iNumberOfFirstUnderobject, unsignedIntFib iNumberOfToDeleteUnderobjects, bool bDeleteOld=true )
 * 	- bool replaceAllUnderobjects( list<cFibElement*> liUnderobjects, bool bDeleteOld )
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testUnderobjectsRand( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the underobjects of the list"<<endl;

	cout<<"pList = new cList( NULL, NULL );"<<endl;
	cList * pList = new cList( NULL, NULL );
	
	list< cFibElement * > liCorrectsUnderobjects;
	
	for ( unsigned int uiIteration = 0; uiIteration < MAX_ITERATION; uiIteration++ ){
		//choos a method to use check
		if ( rand() % 8 ){
			if ( rand() % 2 ){
				//use the addUnderobject() method
				cPoint * pNewPoint = new cPoint();
				//the position to add the new underobject
				const unsignedIntFib uiPosition = rand() % ( liCorrectsUnderobjects.size() + 3 );
				cout<<"pList->addUnderobject( "<<pNewPoint<<", "<<uiPosition<<" );"<<endl;
				pList->addUnderobject( pNewPoint, uiPosition );
				
				//update liCorrectsUnderobjects
				if ( uiPosition <= 1 ){
					//add to front
					liCorrectsUnderobjects.push_front( pNewPoint );
				}else if ( liCorrectsUnderobjects.size() < uiPosition ){
					//add to back
					liCorrectsUnderobjects.push_back( pNewPoint );
				}else{
					list< cFibElement * >::iterator itrPosition =
						liCorrectsUnderobjects.begin();
					for ( unsignedIntFib uiActualPosition = 1;
							( uiActualPosition != uiPosition ) &&
							( itrPosition != liCorrectsUnderobjects.end() );
							uiActualPosition++, itrPosition++ ){
						//nothing to do
					}
					liCorrectsUnderobjects.insert( itrPosition, pNewPoint );
				}
			}else{//use the deleteUnderobject() method
				//the position to delete the underobject from
				const unsignedIntFib uiPosition = rand() % ( liCorrectsUnderobjects.size() + 3 );
				const bool bDeleteOld = rand() % 2;
				
				cout<<"pList->deleteUnderobject( "<<uiPosition<<", "<<(bDeleteOld?"true":"false")<<" )= ";
				const bool bObjectDeleted =
					pList->deleteUnderobject( uiPosition, bDeleteOld );
				
				if ( bObjectDeleted != ( ( 2 < liCorrectsUnderobjects.size() ) &&
						( ( 1 <= uiPosition ) && ( uiPosition <= liCorrectsUnderobjects.size() ) ) ) ){
					cerr<<endl<<"Error: The underobject wher "<<
						(bObjectDeleted?"":"not ")<<"deleted, but shouldn't be. "<<
						"( underobjects in list "<<liCorrectsUnderobjects.size()<<" )"<<endl<<flush;
					iReturn++;
				}
				
				if ( bObjectDeleted ){
					//update liCorrectsUnderobjects
					if ( ( 1 <= uiPosition ) && ( uiPosition <= liCorrectsUnderobjects.size() ) ){
						list< cFibElement * >::iterator itrPosition =
							liCorrectsUnderobjects.begin();
						for ( unsignedIntFib uiActualPosition = 1;
								( uiActualPosition != uiPosition ) &&
								( itrPosition != liCorrectsUnderobjects.end() );
								uiActualPosition++, itrPosition++ ){
							//nothing to do
						}
						cout<<(*itrPosition)<<endl;
						if ( ! bDeleteOld ){
							//delete the underobject from memory outside of the deleteUnderobject method
							(*itrPosition)->deleteObject();
						}
						liCorrectsUnderobjects.erase( itrPosition );
					}else{
						cout<<endl;
					}
				}else{
					cout<<endl;
				}
			}
		}else{
			if ( rand() % 4 ){
				if ( rand() % 2 ){
					//use the addUnderobjects() method
					const unsignedIntFib uiNumberOfUnderobjectsToAdd =
						rand() % (rand() % 256 + 1);
					cout<<"liUnderobjectsToAdd= ";
					list< cFibElement * > liUnderobjectsToAdd;
					for( unsignedIntFib uiActualUnderobject = 0;
							uiActualUnderobject < uiNumberOfUnderobjectsToAdd;
							uiActualUnderobject++ ){
						
						liUnderobjectsToAdd.push_back( new cPoint() );
						cout<<liUnderobjectsToAdd.back()<<"; ";
					}
					cout<<endl;
					//the position to add the new underobject
					const unsignedIntFib uiPosition = rand() % ( liCorrectsUnderobjects.size() + 3 );
					cout<<"pList->addUnderobject( liUnderobjectsToAdd, "<<uiPosition<<" );"<<endl;
					const unsignedIntFib uiUnderobjectsAdded =
						pList->addUnderobjects( liUnderobjectsToAdd, uiPosition );
						
					if ( uiNumberOfUnderobjectsToAdd == uiUnderobjectsAdded ){
						cout<<"Ther wher correctly "<<uiUnderobjectsAdded<<" underobjects added "<<endl;
					}else{
						cerr<<"Error: Ther wher "<<uiUnderobjectsAdded<<
							" underobjects added, but it should be "<<
							uiNumberOfUnderobjectsToAdd<<endl;
						iReturn++;
					}
					
					//update liCorrectsUnderobjects
					if ( uiPosition <= 1 ){
						//add to front
						liCorrectsUnderobjects.insert( liCorrectsUnderobjects.begin(),
							liUnderobjectsToAdd.begin(), liUnderobjectsToAdd.end() );
					}else if ( liCorrectsUnderobjects.size() < uiPosition ){
						//add to back
						liCorrectsUnderobjects.insert( liCorrectsUnderobjects.end(),
							liUnderobjectsToAdd.begin(), liUnderobjectsToAdd.end() );
					}else{
						list< cFibElement * >::iterator itrPosition =
							liCorrectsUnderobjects.begin();
						for ( unsignedIntFib uiActualPosition = 1;
								( uiActualPosition != uiPosition ) &&
								( itrPosition != liCorrectsUnderobjects.end() );
								uiActualPosition++, itrPosition++ ){
							//nothing to do
						}
						liCorrectsUnderobjects.insert( itrPosition,
							liUnderobjectsToAdd.begin(), liUnderobjectsToAdd.end() );
					}
				}else{//use the deleteUnderobjects() method
					const unsignedIntFib uiPosition = rand() % ( liCorrectsUnderobjects.size() + 3 );
					const unsignedIntFib uiDeleteUnderobjects =
						rand() % ( liCorrectsUnderobjects.size() - uiPosition + 3 );
					//two underobjects must remain in the list
					const unsignedIntFib uiFirstUnderobjectToDelete = ( uiPosition == 0 ) ?
						1 : ( ( uiPosition <= liCorrectsUnderobjects.size() ) ?
							uiPosition :
							liCorrectsUnderobjects.size() + 1 );
					const unsignedIntFib uiLastUnderobjectToDelete =
						(uiDeleteUnderobjects == 0) ?
							liCorrectsUnderobjects.size():
							(((uiFirstUnderobjectToDelete - 1 + uiDeleteUnderobjects) <= liCorrectsUnderobjects.size()) ?
								(uiFirstUnderobjectToDelete - 1 + uiDeleteUnderobjects) :
								liCorrectsUnderobjects.size());
					const unsignedIntFib uiNumberOfToDeleteUnderobjects =
						( uiFirstUnderobjectToDelete <= liCorrectsUnderobjects.size() ) ?
							( uiLastUnderobjectToDelete - uiFirstUnderobjectToDelete + 1 ) :
							0;
					const unsignedIntFib uiRemainingUnderobjects =
						liCorrectsUnderobjects.size() - uiNumberOfToDeleteUnderobjects;
					
					const bool bCanDelete = ( 2 <= uiRemainingUnderobjects ) &&
						( uiPosition <= liCorrectsUnderobjects.size() );
					
					const bool bDeleteOld = rand() % 2;
					
					cout<<"pList->deleteUnderobjects( "<<uiPosition<<", "<<
						uiDeleteUnderobjects<<", "<<(bDeleteOld?"true":"false")<<" ) = ("<<
							"from "<<uiFirstUnderobjectToDelete<<" to "<<
							uiLastUnderobjectToDelete<<" -> #"<<uiNumberOfToDeleteUnderobjects<<
							"(from "<<liCorrectsUnderobjects.size()<<") ) =";
					const bool bObjectsDeleted =
						pList->deleteUnderobjects( uiPosition, uiDeleteUnderobjects, bDeleteOld );
						
					
					if ( bObjectsDeleted != bCanDelete ){
						cerr<<endl<<"Error: The underobjects wher "<<
							(bObjectsDeleted?"":"not ")<<"deleted, but shouldn't be. "<<
							"( underobjects in list are "<<liCorrectsUnderobjects.size()<<", which means that "<<
							uiRemainingUnderobjects<<" underobjects will remain in the list)"<<endl<<flush;
						iReturn++;
					}
					
					if ( bObjectsDeleted ){
						//find first underobject to delete
						list< cFibElement * >::iterator itrFirstUnderobjectToDelete=
							liCorrectsUnderobjects.begin();
						for ( unsignedIntFib uiActualPosition = 1;
								( uiActualPosition != uiFirstUnderobjectToDelete ) &&
								( itrFirstUnderobjectToDelete != liCorrectsUnderobjects.end() );
								uiActualPosition++, itrFirstUnderobjectToDelete++ ){
							//nothing to do
						}
						//update liCorrectsUnderobjects
						list< cFibElement * >::iterator itrActualUnderobject =
							itrFirstUnderobjectToDelete;
						for ( unsignedIntFib uiDeletedUnderobjects = 0;
								( uiDeletedUnderobjects < uiNumberOfToDeleteUnderobjects ) &&
								( itrActualUnderobject != liCorrectsUnderobjects.end() );
								uiDeletedUnderobjects++ ){
							
							cout<<(*itrActualUnderobject)<<"; ";
							if ( ! bDeleteOld ){
								//delete the underobject from memory outside of the deleteUnderobject method
								(*itrActualUnderobject)->deleteObject();
							}
							itrActualUnderobject = liCorrectsUnderobjects.erase( itrActualUnderobject );
						}
					}
					cout<<endl;
				}
			}else{//use the replaceAllUnderobjects() method
				const unsignedIntFib uiNumberOfUnderobjectsToAdd =
					rand() % (rand() % 256 + 1);
				cout<<"liUnderobjectsToAdd= ";
				list< cFibElement * > liUnderobjectsToAdd;
				for( unsignedIntFib uiActualUnderobject = 0;
						uiActualUnderobject < uiNumberOfUnderobjectsToAdd;
						uiActualUnderobject++ ){
					
					liUnderobjectsToAdd.push_back( new cPoint() );
					cout<<liUnderobjectsToAdd.back()<<"; ";
				}
				cout<<endl;
				//the position to add the new underobject
				const bool bDeleteOld = rand() % 2;
				cout<<"pList->replaceAllUnderobjects( liUnderobjectsToAdd, "<<(bDeleteOld?"true":"false")<<" );"<<endl;
				const bool bUnderobjectsReplaced =
					pList->replaceAllUnderobjects( liUnderobjectsToAdd, bDeleteOld );
					
				if ( bUnderobjectsReplaced == ( 2 <= uiNumberOfUnderobjectsToAdd ) ){
					cout<<"The underobjects wher correctly "<<
						(bUnderobjectsReplaced?"":"not ")<<"replaced."<<endl<<flush;
				}else{
					cerr<<"Error: The underobjects wher "<<
						(bUnderobjectsReplaced?"":"not ")<<"replaced, but shouldn't be. "<<endl<<flush;
					iReturn++;
				}
				//update liCorrectsUnderobjects
				if ( bUnderobjectsReplaced ){
					if ( ! bDeleteOld ){
						//delete the underobject from memory outside of the deleteUnderobject method
						for ( list< cFibElement * >::iterator itrPosition =
								liCorrectsUnderobjects.begin();
								itrPosition != liCorrectsUnderobjects.end();
								itrPosition++ ){
							
							(*itrPosition)->deleteObject();
						}
					}
					liCorrectsUnderobjects = liUnderobjectsToAdd;
				}else{//delete to add underobjects
					for ( list< cFibElement * >::iterator itrPosition =
							liUnderobjectsToAdd.begin();
							itrPosition != liUnderobjectsToAdd.end();
							itrPosition++ ){
						
						(*itrPosition)->deleteObject();
					}
				}
			}
		}
		
		//check getNumberOfUnderobjects()
		if ( pList->getNumberOfUnderobjects() != liCorrectsUnderobjects.size() ){
			cerr<<"Error: Ther are "<<pList->getNumberOfUnderobjects()<<
				" underobjects in the listelement, but it should be "<<
				liCorrectsUnderobjects.size()<<" ." <<endl;
			iReturn++;
		}
		//check getUnderobject()
		list<cFibElement*>::iterator itrListElement = liCorrectsUnderobjects.begin();
		for ( unsignedIntFib uiActualFibElement = 1;
				uiActualFibElement <= pList->getNumberOfUnderobjects();
				uiActualFibElement++ ){
			
			if ( itrListElement != liCorrectsUnderobjects.end() ){
				const cFibElement * pUnderObject = pList->getUnderobject( uiActualFibElement );
				if ( pUnderObject != NULL ){
					if ( pUnderObject != (*itrListElement) ){
						cerr<<"Error: The "<< uiActualFibElement <<"'th underobject is not correct, it is "<<
							pUnderObject<<" but should be "<<(*itrListElement)<<" ." <<endl;
						iReturn++;
					}
				}else{
					cerr<<"Error: Ther is no "<< uiActualFibElement <<"'th underobject (NULL is returned)." <<endl;
					iReturn++;
				}
				itrListElement++;
			}else{
				cerr<<"Error: The list has an "<< uiActualFibElement <<
					"'th underobject, but shouldn't have one."<<endl;
				iReturn++;
			}
		}
		//check getUnderobjects()
		const list< cFibElement * > liActualUnderobjects = pList->getUnderobjects();
		if ( liActualUnderobjects != liCorrectsUnderobjects ){
			cerr<<"Error: The returned list with underobjects is not correct." <<endl;
			
			liCorrectsUnderobjects = liActualUnderobjects;
			iReturn++;
		}
	}
	
	cFibElement::deleteObject( pList );

	return iReturn;
}


/**
 * This method tests the variable methods of the cList class.
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

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

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
	cout<<"pVariable5 = rootEmpty1.getInputVariable( 5 );"<<endl;
	cFibVariable * pVariable5 = rootEmpty1.getInputVariable( 5 );
	
	cout<<"cVectorPosition vecPosition1E3( 3 );"<<endl;
	cVectorPosition vecPosition1E3( 3 );
	cout<<"cPoint point1( &vecPosition1E3 );"<<endl;
	cPoint point1( &vecPosition1E3 );
	cout<<"cPoint point2( &vecPosition1E3 );"<<endl;
	cPoint point2( &vecPosition1E3 );
	cout<<"cPoint point3( &vecPosition1E3 );"<<endl;
	cPoint point3( &vecPosition1E3 );

	cout<<"cList list1( &point1, &point2 );"<<endl;
	cList list1( &point1, &point2 );
	cout<<"list1.addUnderobject( &point3, 3 );"<<endl;
	list1.addUnderobject( &point3, 3 );

	//check the isUsedVariable() methode from cList
	cout<<"list1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! list1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the listelement. "<<endl;
		iReturn++;
	}
	set<cFibVariable*> setCorrectUsedVariables;
	
	//check getUsedVariables()
	cout<<"setUsedVariables = list1.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = list1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cList
	cout<<"list1.isUsedVariable( pVariable1, ED_BELOW_EQUAL )"<<endl;
	if ( ! list1.isUsedVariable( pVariable1, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the listelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = list1.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = list1.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"point1.getPosition()->setVariable( 3, pVariable1 );"<<endl;
	point1.getPosition()->setVariable( 3, pVariable1 );
	setCorrectUsedVariables.insert( pVariable1 );

	//check the isUsedVariable() methode from cList
	cout<<"list1.isUsedVariable( pVariable1  )"<<endl;
	if ( ! list1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the listelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = list1.getUsedVariables(); "<<endl;
	setUsedVariables = list1.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cList
	cout<<"list1.isUsedVariable( pVariable1, ED_BELOW_EQUAL )"<<endl;
	if ( list1.isUsedVariable( pVariable1, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable1 is correctly used in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the listelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = list1.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = list1.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	cout<<"point2.getPosition()->setVariable( 1, pVariable2 );"<<endl;
	point2.getPosition()->setVariable( 1, pVariable2 );
	setCorrectUsedVariables.insert( pVariable2 );

	//check the isUsedVariable() methode from cList
	cout<<"list1.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( list1.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly used in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the listelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = list1.getUsedVariables(); "<<endl;
	setUsedVariables = list1.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cList
	cout<<"list1.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( list1.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly used in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the listelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = list1.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = list1.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	cout<<"list1.replaceVariable( pVariable2, pVariable3 );"<<endl;
	bool bVariableReplaced = list1.replaceVariable( pVariable2, pVariable3 );
	setCorrectUsedVariables.erase( pVariable2 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cList
	cout<<"list1.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( ! list1.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the listelement. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cList
	cout<<"list1.isUsedVariable( pVariable3, ED_BELOW_EQUAL )"<<endl;
	if ( list1.isUsedVariable( pVariable3, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the listelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = list1.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = list1.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"Try replacing non existing variable pVariable2:"<<endl;
	cout<<"list1.replaceVariable( pVariable2, pVariable4 );"<<endl;
	bVariableReplaced = list1.replaceVariable( pVariable2, pVariable4 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = list1.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = list1.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cList
	cout<<"list1.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( ! list1.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the listelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cList
	cout<<"list1.isUsedVariable( pVariable4, ED_BELOW_EQUAL )"<<endl;
	if ( ! list1.isUsedVariable( pVariable4, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable4 is correctly not used in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is used in the listelement. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cList
	cout<<"list1.isUsedVariable( pVariable3, ED_BELOW_EQUAL )"<<endl;
	if ( list1.isUsedVariable( pVariable3, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the listelement. "<<endl;
		iReturn++;
	}

	cout<<"point3.getPosition()->setVariable( 1, pVariable4 );"<<endl;
	point3.getPosition()->setVariable( 1, pVariable4 );
	setCorrectUsedVariables.insert( pVariable4 );
	//check the isUsedVariable() methode from cList
	cout<<"list1.isUsedVariable( pVariable4, ED_BELOW_EQUAL )"<<endl;
	if ( list1.isUsedVariable( pVariable4, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable4 is correctly used in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is not used in the listelement. "<<endl;
		iReturn++;
	}


	cout<<"point1.getPosition()->setVariable( 2, pVariable4 );"<<endl;
	point1.getPosition()->setVariable( 2, pVariable4 );
	cout<<"point2.getPosition()->setVariable( 2, pVariable4 );"<<endl;
	point2.getPosition()->setVariable( 2, pVariable4 );
	cout<<"point3.getPosition()->setVariable( 2, pVariable4 );"<<endl;
	point3.getPosition()->setVariable( 2, pVariable4 );

	//check getUsedVariables()
	cout<<"setUsedVariables = list1.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = list1.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	cout<<"list1.replaceVariable( pVariable4, pVariable5 );"<<endl;
	bVariableReplaced = list1.replaceVariable( pVariable4, pVariable5 );
	setCorrectUsedVariables.erase( pVariable4 );
	setCorrectUsedVariables.insert( pVariable5 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cList
	cout<<"list1.isUsedVariable( pVariable4, ED_BELOW_EQUAL )"<<endl;
	if ( ! list1.isUsedVariable( pVariable4, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable4 is correctly not used in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is used in the listelement. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cList
	cout<<"list1.isUsedVariable( pVariable5, ED_BELOW_EQUAL )"<<endl;
	if ( list1.isUsedVariable( pVariable5, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable5 is correctly used in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable5 is not used in the listelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = list1.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = list1.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods isDefinedVariable( ED_POSITION ) and getDefinedVariables( ED_POSITION )"<<endl;

	//check the isDefinedVariable() methode from cList
	cout<<"list1.isDefinedVariable( pVariable1, ED_POSITION )"<<endl;
	if ( ! list1.isDefinedVariable( pVariable1, ED_POSITION ) ){
	
		cout<<"The variable pVariable1 is correctly not defined in the listelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is defined in the listelement. "<<endl;
		iReturn++;
	}

	//check getDefinedVariables()
	cout<<"liDefinedVariables = list1.getDefinedVariables( ED_POSITION ); "<<endl;
	list<cFibVariable*> liDefinedVariables = list1.getDefinedVariables( ED_POSITION );
	if ( liDefinedVariables.empty() ){
	
		cout<<"Ther are correctly no variables defines. "<<endl;
	}else{
		cerr<<"Error: Ther are variables defines. "<<endl;
		iReturn++;
	}

	return iReturn;
}






