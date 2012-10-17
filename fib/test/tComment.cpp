/**
 * @file tComment
 * file name: tComment.cpp
 * @author Betti Oesterholz
 * @date 30.07.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cComment.
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
 * This file contains the test for the class cComment, which
 * represents a Fib -commentelement.
 *
 *
 * What's tested of class cComment:
 * 	- cComment( const string & szInKey, const string & szInValue, cFibElement * pInUnderobject = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- cComment( const cComment &commentElement );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- bool hasUnderAllObjects( ) const;
 * 	- unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
 * 	- bool evalueObject( iEvaluePosition & evaluePosition, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties ) const;
 * 	- bool evalueObject( iEvalueFibElement & evalueFibElement, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties, const list<char> & liCFibElementTyps );
 * 	- bool equal( const cFibElement & fibObject ) const;
 * 	- bool equalElement( const cFibElement & fibElement ) const;
 * 	- cComment( const cComment &commentElement );
 * 	- cFibElement *clone( ) const;
 * 	- cComment *copy( const unsignedIntFib iObjectComment=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementComment=0 ) const;
 * 	- bool storeXml( ostream &stream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream &stream ) const;
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- cFibVariable * getDefinedVariable();
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
 * 	- string getKey() const;
 * 	- void setKey( const string & szInKey );
 * 	- string getValue() const;
 * 	- void setValue( const string & szInValue );
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
30.07.2010  Oesterholz  created
30.03.2011  Oesterholz  storing to binary stream
10.11.2011  Oesterholz  Bugfix: evalueObject() don't overwrite properties
*/

#include "version.h"

#include "cComment.h"
#include "cPoint.h"
#include "cRoot.h"
#include "cProperty.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cTypeVariable.h"
#include "cTypeComments.h"
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
int testCommentValues( unsigned long &ulTestphase );


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for cComment methods"<<endl;
	cout<<      "================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testEvalueObject( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testCommentValues( ulTestphase );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the constructor of the cComment class.
 *
 * methods tested:
 * 	- cComment( const string & szInKey, const string & szInValue, cFibElement * pInUnderobject = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- cComment( const cComment &commentElement );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- unsignedIntFib getNumberOfElement()
 * 	- bool hasUnderAllObjects() const;
 * 	- string getKey() const;
 * 	- string getValue() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty comment"<<endl;

	string szKey = "";
	string szValue = "";
	cout<<"cComment commentSimple( \""<<szKey<<"\", \""<<szValue<<"\" );"<<endl;
	cComment commentSimple( szKey, szValue );
	
	//check the getType() methode from cComment
	if ( commentSimple.getType() == 'c' ){
	
		cout<<"The type of the commentelement is correctly 'c' . "<<endl;
	}else{
		cerr<<"Error: The type of the commentelement is "<<
			commentSimple.getType()<<" but should be 'c' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cComment
	if ( ! commentSimple.isValidFibElement() ){
	
		cout<<"The commentelement is correctly not a correct commentelement. "<<endl;
	}else{
		cerr<<"Error: The commentelement is a correct commentelement, but should not be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cComment
	if ( commentSimple.isMovable() ){
	
		cout<<"The commentelement is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The commentelement is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cComment
	if ( commentSimple.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the commentelement is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the commentelement is "<<
			commentSimple.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cComment
	if ( commentSimple.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the commentelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the commentelement is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cComment
	if ( commentSimple.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the commentelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the commentelement is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cComment
	if ( commentSimple.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the commentelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the commentelement is "<<
			commentSimple.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getKey() methode from cComment
	if ( commentSimple.getKey() == szKey ){
	
		cout<<"The key for the commentelement is correctly equal to \""<<szKey<<"\". "<<endl;
	}else{
		cerr<<"Error: The key for the commentelement is not equal to \""<<szKey<<
			"\", but is \""<<commentSimple.getKey()<<"\" ."<<endl;
		iReturn++;
	}
	//check the getValue() methode from cComment
	if ( commentSimple.getValue() == szValue ){
	
		cout<<"The value for the commentelement is correctly equal to \""<<szValue<<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szValue<<
			"\", but is \""<<commentSimple.getValue()<<"\". "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cComment
	if ( ! commentSimple.hasUnderAllObjects()){
	
		cout<<"The commentelement has correctly missing a needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The commentelement is not missing a underobject."<<endl;
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cComment with a given key and value"<<endl;

	szKey = "author";
	szValue = "me";
	cout<<"cComment comment1( \""<<szKey<<"\", \""<<szValue<<"\" );"<<endl;
	cComment comment1( szKey, szValue );

	//check the getType() methode from cComment
	if ( comment1.getType() == 'c' ){
	
		cout<<"The type of the commentelement is correctly 'c' . "<<endl;
	}else{
		cerr<<"Error: The type of the commentelement is "<<
			comment1.getType()<<" but should be 'c' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cComment
	if ( ! comment1.isValidFibElement() ){
	
		cout<<"The commentelement is correctly not a correct commentelement. "<<endl;
	}else{
		cerr<<"Error: The commentelement is a correct commentelement, but shouldn't be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cComment
	if ( comment1.isMovable() ){
	
		cout<<"The commentelement is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The commentelement is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cComment
	if ( comment1.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the commentelement is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the commentelement is "<<
			comment1.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cComment
	if ( comment1.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the commentelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the commentelement is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cComment
	if ( comment1.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the commentelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the commentelement is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cComment
	if ( comment1.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the commentelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the commentelement is "<<
			comment1.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getKey() methode from cComment
	if ( comment1.getKey() == szKey ){
	
		cout<<"The key for the commentelement is correctly equal to \""<<szKey<<"\". "<<endl;
	}else{
		cerr<<"Error: The key for the commentelement is not equal to \""<<szKey<<
			"\", but is \""<<comment1.getKey()<<"\" ."<<endl;
		iReturn++;
	}
	//check the getValue() methode from cComment
	if ( comment1.getValue() == szValue ){
	
		cout<<"The value for the commentelement is correctly equal to \""<<szValue<<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szValue<<
			"\", but is \""<<comment1.getValue()<<"\". "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cComment
	if ( ! comment1.hasUnderAllObjects() ){
	
		cout<<"The commentelement has correctly not all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The commentelement is not missing a underobject."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cComment with a superior fib -element"<<endl;

	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	
	szKey = "name";
	szValue = "Mr. X";
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment commentSup( \""<<szKey<<"\", \""<<szValue<<"\", NULL, &rootSimple1 );"<<endl;
	cComment commentSup( szKey, szValue, NULL, &rootSimple1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment commentSup( \""<<szKey<<"\", \""<<szValue<<"\", &rootSimple1 );"<<endl;
	cComment commentSup( szKey, szValue, &rootSimple1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the getType() methode from cComment
	if ( commentSup.getType() == 'c' ){
	
		cout<<"The type of the commentelement is correctly 'c' . "<<endl;
	}else{
		cerr<<"Error: The type of the commentelement is "<<
			commentSup.getType()<<" but should be 'c' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cComment
	if ( ! commentSup.isValidFibElement() ){
	
		cout<<"The commentelement is correctly not a correct commentelement. "<<endl;
	}else{
		cerr<<"Error: The commentelement is a correct commentelement, but shouldn't be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cComment
	if ( commentSup.isMovable() ){
	
		cout<<"The commentelement is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The commentelement is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cComment
	if ( commentSup.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the commentelement is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the commentelement is "<<
			commentSup.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cComment
	if ( commentSup.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the commentelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the commentelement is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cComment
	if ( commentSup.getFibElement( -1 ) == &rootSimple1 ){
	
		cout<<"The previous fib -element for the commentelement is correctly rootSimple1. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the commentelement is not rootSimple1."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cComment
	if ( commentSup.getSuperiorFibElement() == &rootSimple1 ){
	
		cout<<"The superior fib -element for the commentelement is correctly rootSimple1. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the commentelement is "<<
			commentSup.getSuperiorFibElement() << " and not rootSimple1."<<endl;
		iReturn++;
	}
	//check the getKey() methode from cComment
	if ( commentSup.getKey() == szKey ){
	
		cout<<"The key for the commentelement is correctly equal to \""<<szKey<<"\". "<<endl;
	}else{
		cerr<<"Error: The key for the commentelement is not equal to \""<<szKey<<
			"\", but is \""<<commentSup.getKey()<<"\" ."<<endl;
		iReturn++;
	}
	//check the getValue() methode from cComment
	if ( commentSup.getValue() == szValue ){
	
		cout<<"The value for the commentelement is correctly equal to \""<<szValue<<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szValue<<
			"\", but is \""<<commentSup.getValue()<<"\". "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cComment
	if ( ! commentSup.hasUnderAllObjects() ){
	
		cout<<"The commentelement has correctly not all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The commentelement is not missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	szKey = "name";
	szValue = "Mr. X";
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cComment with a next fib -element"<<endl;
	
	cout<<"cComment commentNextPrev( \""<<szKey<<"\", \""<<szValue<<
		"\", &commentSimple );"<<endl;
	cComment commentNextPrev( szKey, szValue, &commentSimple );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cComment with a next and previous fib -element"<<endl;
	
	cout<<"cComment commentNextPrev( \""<<szKey<<"\", \""<<szValue<<
		"\", &NULL, &comment1, &commentSimple );"<<endl;
	cComment commentNextPrev( szKey, szValue, NULL, &comment1, &commentSimple );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the getType() methode from cComment
	if ( commentNextPrev.getType() == 'c' ){
	
		cout<<"The type of the commentelement is correctly 'c' . "<<endl;
	}else{
		cerr<<"Error: The type of the commentelement is "<<
			commentNextPrev.getType()<<" but should be 'c' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cComment
	if ( commentNextPrev.isValidFibElement() ){
	
		cout<<"The commentelement is correctly a correct commentelement. "<<endl;
	}else{
		cerr<<"Error: The commentelement is not a correct commentelement, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cComment
	if ( commentNextPrev.isMovable() ){
	
		cout<<"The commentelement is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The commentelement is not movebel."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNumberOfElement() methode from cComment
	if ( commentNextPrev.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the commentelement is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the commentelement is "<<
			commentNextPrev.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNumberOfElement() methode from cComment
	if ( commentNextPrev.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the commentelement is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the commentelement is "<<
			commentNextPrev.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNextFibElement() methode from cComment
	if ( commentNextPrev.getNextFibElement() == &commentSimple ){
	
		cout<<"The next/ main fib -element for the commentelement is correctly commentSimple. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the commentelement is not commentSimple."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cComment
	if ( commentNextPrev.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the commentelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the commentelement is not NULL."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cComment
	if ( commentNextPrev.getFibElement( -1 ) == &comment1 ){
	
		cout<<"The previous fib -element for the commentelement is correctly comment1. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the commentelement is not comment1."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getSuperiorFibElement() methode from cComment
	if ( commentNextPrev.getSuperiorFibElement() == NULL){
	
		cout<<"The superior fib -element for the commentelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the commentelement is "<<
			commentNextPrev.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getKey() methode from cComment
	if ( commentNextPrev.getKey() == szKey ){
	
		cout<<"The key for the commentelement is correctly equal to \""<<szKey<<"\". "<<endl;
	}else{
		cerr<<"Error: The key for the commentelement is not equal to \""<<szKey<<
			"\", but is \""<<commentNextPrev.getKey()<<"\" ."<<endl;
		iReturn++;
	}
	//check the getValue() methode from cComment
	if ( commentNextPrev.getValue() == szValue ){
	
		cout<<"The value for the commentelement is correctly equal to \""<<szValue<<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szValue<<
			"\", but is \""<<commentNextPrev.getValue()<<"\". "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cComment
	if ( ! commentNextPrev.hasUnderAllObjects()  ){
	
		cout<<"The commentelement has correctly not all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The commentelement is not missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cComment with all parameters given"<<endl;
	
	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cPoint point1;"<<endl;
	cPoint point1;

	szKey = "type";
	szValue = "full";
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment commentFull( \""<<szKey<<"\", \""<<szValue<<
		"\", &point1, &rootD2 );"<<endl;
	cComment commentFull( szKey, szValue, &point1, &rootD2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment commentFull( \""<<szKey<<"\", \""<<szValue<<
		"\", &rootD2, &rootD2, &point1 );"<<endl;
	cComment commentFull( szKey, szValue, &rootD2, &rootD2, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	
	//check the getType() methode from cComment
	if ( commentFull.getType() == 'c' ){
	
		cout<<"The type of the commentelement is correctly 'c' . "<<endl;
	}else{
		cerr<<"Error: The type of the commentelement is "<<
			commentFull.getType()<<" but should be 'c' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cComment
	if ( commentFull.isValidFibElement() ){
	
		cout<<"The commentelement is correctly a correct commentelement. "<<endl;
	}else{
		cerr<<"Error: The commentelement is not a correct commentelement, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cComment
	if ( commentFull.isMovable() ){
	
		cout<<"The commentelement is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The commentelement is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cComment
	if ( commentFull.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the commentelement is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the commentelement is "<<
			commentFull.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cComment
	if ( commentFull.getNextFibElement() == &point1 ){
	
		cout<<"The next/ main fib -element for the commentelement is correctly commentSimple. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the commentelement is not commentSimple."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cComment
	if ( commentFull.getFibElement( -1 ) == &rootD2 ){
	
		cout<<"The previous fib -element for the commentelement is correctly rootD2. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the commentelement is not rootD2."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cComment
	if ( commentFull.getSuperiorFibElement() == &rootD2 ){
	
		cout<<"The superior fib -element for the commentelement is correctly rootD2. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the commentelement is "<<
			commentFull.getSuperiorFibElement() << " and not rootD2."<<endl;
		iReturn++;
	}
	//check the getKey() methode from cComment
	if ( commentFull.getKey() == szKey ){
	
		cout<<"The key for the commentelement is correctly equal to \""<<szKey<<"\". "<<endl;
	}else{
		cerr<<"Error: The key for the commentelement is not equal to \""<<szKey<<
			"\", but is \""<<commentFull.getKey()<<"\" ."<<endl;
		iReturn++;
	}
	//check the getValue() methode from cComment
	if ( commentFull.getValue() == szValue ){
	
		cout<<"The value for the commentelement is correctly equal to \""<<szValue<<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szValue<<
			"\", but is \""<<commentFull.getValue()<<"\". "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cComment
	if ( commentFull.hasUnderAllObjects() ){
	
		cout<<"The commentelement has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The commentelement is missing a underobject."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This comment compares the to given listlists.
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
 * This comment compares the given evalued position lists.
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
 * This comment compares the given evalued fib -element lists.
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
 * This comment compares the given evalued fib -element lists.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing a cComment"<<endl;

	cout<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );
	cout<<"vecPositionE2.setValue( 1, 3 );"<<endl;
	vecPositionE2.setValue( 1, 3 );

	cout<<"cPoint point1( &vecPositionE2 );"<<endl;
	cPoint point1( &vecPositionE2 );
	
	cout<<"cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );
	cout<<"vecPropertyColorSW.setValue( 1, 2 );"<<endl;
	vecPropertyColorSW.setValue( 1, 2 );

	string szKey = "key";
	string szValue = "value";
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property1( vecPropertyColorSW, &point1 );"<<endl;
	cProperty property1( vecPropertyColorSW, &point1 );
	
	cout<<"cComment comment1( \""<<szKey<<"\", \""<<szValue<<"\", &property1 );"<<endl;
	cComment comment1( szKey, szValue, &property1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property1( vecPropertyColorSW, NULL, NULL, &point1 );"<<endl;
	cProperty property1( vecPropertyColorSW, NULL, NULL, &point1 );
	
	cout<<"cComment comment1( \""<<szKey<<"\", \""<<szValue<<
		"\", NULL, NULL, &property1 );"<<endl;
	cComment comment1( szKey, szValue, NULL, NULL, &property1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
		
	unsigned int uiPointsToEvalue = 1;
	
	unsigned int uiTimeNeeded = 1 + 5;

	//check the getTimeNeed() methode from cList
	cout<<"comment1.getTimeNeed()"<<endl;
	if ( comment1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			comment1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cList
	cout<<"comment1.getTimeNeed( 4 )"<<endl;
	if ( comment1.getTimeNeed( 4 ) == 4 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 4 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			comment1.getTimeNeed( 4 ) <<", but should be "<< 4 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"list<cVectorProperty> liVecProperties;"<<endl;
	list<cVectorProperty> liVecProperties;
	
	//generate to evalue data
	list< pair< const cVectorPosition*, list<cVectorProperty> > > liPointsToEvalue;
	cVectorPosition vecPositionE2V1( 2 );
	vecPositionE2V1.setValue( 1, 3 );
	cVectorProperty vecPropertyColorSWV1( cTypeProperty::COLOR_SW );
	vecPropertyColorSWV1.setValue( 1, 2 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V1, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	
	cEvaluePositionList evaluePositionList;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"comment1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bool bObjectEvalued = comment1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"comment1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = comment1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
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
	cout<<"comment1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = comment1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"comment1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = comment1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cComment with a global property list given"<<endl;
	
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
	
	cout<<"comment1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = comment1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
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

	cout<<"comment1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = comment1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cComment with a different key and value"<<endl;

	szKey = "author";
	szValue = "me";
	cout<<"comment1.setKey( \""<<szKey<<"\" );"<<endl;
	comment1.setKey( szKey );
	cout<<"comment1.setValue( \""<<szValue<<"\" );"<<endl;
	comment1.setValue( szValue );
	
	uiPointsToEvalue = 1;
	
	//generate to evalue data
	liPointsToEvalue.clear();
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V1, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV1 );

	uiTimeNeeded = 1 + uiPointsToEvalue * 5;

	//check the getTimeNeed() methode from cList
	cout<<"comment1.getTimeNeed()"<<endl;
	if ( comment1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			comment1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}

	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"comment1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = comment1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	
	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"comment1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = comment1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
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
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV1 );
	
	cout<<"comment1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = comment1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"comment1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = comment1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cComment for non existing object point 1"<<endl;
	
	uiPointsToEvalue = 0;
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"comment1.evalueObject( evaluePositionList, 4,  liVecProperties );"<<endl;
	bObjectEvalued = comment1.evalueObject( evaluePositionList, 4,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The comment was correctly not evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	liFibElementsToEvalue.clear();
	cout<<"comment1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = comment1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The comment was correctly not evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cComment when returnvalue is false"<<endl;

	uiPointsToEvalue = 1;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	cout<<"comment1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = comment1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. with result false "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evaluePositionList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedPoints( evaluePositionList.liEvaluedPositionData, liPointsToEvalue );

	
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 0;
	cout<<"comment1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = comment1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. with result false "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back true. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
			evaluePositionList.ulCountOfEvalueMethodCalled <<" times, but should be called "<<
			uiPointsToEvalue <<" times."<<endl;
		iReturn++;
	}
	iReturn += compairEvaluedFibElements( evalueFibElementList.liEvaluedElementData, liFibElementsToEvalue );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cComment with differnt elements to evalue"<<endl;

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
	cout<<"comment1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = comment1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
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
	cout<<"liCFibElementTyps.push_back( 'c' );"<<endl;
	liCFibElementTyps.push_back( 'c' );
	uiPointsToEvalue = 1;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &comment1, list<cVectorProperty>() ) );
	cout<<"comment1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = comment1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
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
	cout<<"liCFibElementTyps.push_back( 'c' );"<<endl;
	liCFibElementTyps.push_back( 'c' );
	cout<<"liCFibElementTyps.push_back( 'm' );"<<endl;
	liCFibElementTyps.push_back( 'm' );
	uiPointsToEvalue = 1;
	cout<<"comment1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = comment1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The comment was correctly evalued. "<<endl;
	}else{
		cerr<<"Error: The method evalueObject() gives back false. "<<endl;
		iReturn++;
	}
	if ( evalueFibElementList.ulCountOfEvalueMethodCalled == uiPointsToEvalue ){
	
		cout<<"The evaluePositionList() comment was correctly called "<<
			uiPointsToEvalue <<" times."<<endl;
	}else{
		cerr<<"Error: The evaluePositionList() comment was called "<<
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing equal methods for commentelements"<<endl;

	cout<<endl<<"Creating commentobjects objects to compare: "<<endl<<endl;

	//comment with a empty commentvector
	cout<<"cComment comment1( \"\", \"\" );"<<endl;
	cComment comment1( "", "" );

	cout<<"cComment comment2( \"\", \"\" );"<<endl;
	cComment comment2( "", "" );

	//comment with one changed undercomment
	cout<<"cComment comment3( \"key\", \"value\" );"<<endl;
	cComment comment3( "key", "value" );

	cout<<"cComment commentK1( \"key1\", \"value\" );"<<endl;
	cComment commentK1( "key1", "value" );
	
	cout<<"cComment commentV1( \"key\", \"value1\" );"<<endl;
	cComment commentV1( "key", "value1" );
	
	cout<<"cComment commentK1V1( \"key1\", \"value1\" );"<<endl;
	cComment commentK1V1( "key1", "value1" );

	//comment with supperior element
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment commentSup( \"\", \"\", NULL, &rootSimple1 );"<<endl;
	cComment commentSup( "", "", NULL, &rootSimple1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment commentSup( \"\", \"\", &rootSimple1 );"<<endl;
	cComment commentSup( "", "", &rootSimple1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//comment in fib -element structur
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment commentNextPrev( \"\", \"\", &poinNext );"<<endl;
	cComment commentNextPrev( "", "", &poinNext );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinPrev;"<<endl;
	cPoint poinPrev;
	cout<<"cComment commentNextPrev( \"\", \"\", NULL, &poinPrev, &poinNext );"<<endl;
	cComment commentNextPrev( "", "", NULL, &poinPrev, &poinNext );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	cout<<"cPoint poinNext2;"<<endl;
	cPoint poinNext2;
	cout<<"cRoot root1;"<<flush<<endl;
	cRoot root1;
	
	cout<<"cTypeComments testTypeComment;"<<endl;
	cTypeComments testTypeComment;
	
	//create vector domain with two elements
	cout<<"cDomainNaturalNumberBit domainNat8( 8 );"<<endl;
	cDomainNaturalNumberBit domainNat8( 8 );

	cout<<"root1.getDomains()->addDomain( testTypeComment, &domainNat8 );"<<endl;
	root1.getDomains()->addDomain( testTypeComment, &domainNat8 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment commentFull(  \"\", \"\", &poinNext2, &root1 );"<<endl;
	cComment commentFull( "", "", &poinNext2, &root1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinPrev2;"<<endl;
	cPoint poinPrev2;
	cout<<"cComment commentFull(  \"\", \"\", &root1, &poinPrev2, &poinNext2 );"<<endl;
	cComment commentFull( "", "", &root1, &poinPrev2, &poinNext2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//comments with a contained pointelement
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment commentPoint1(  \"\", \"\", &point1 );"<<endl;
	cComment commentPoint1( "", "", &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment commentPoint1(  \"\", \"\", NULL, NULL, &point1 );"<<endl;
	cComment commentPoint1( "", "", NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"cVectorPosition vecPosition;"<<endl;
	cVectorPosition vecPosition;
	cout<<"cPoint point2( &vecPosition );"<<endl;
	cPoint point2( &vecPosition );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment commentPoint2(  \"\", \"\", &point2 );"<<endl;
	cComment commentPoint2( "", "", &point2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment commentPoint2(  \"\", \"\", NULL, NULL, &point2 );"<<endl;
	cComment commentPoint2( "", "", NULL, NULL, &point2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR



	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with comment1
	cFibElement *actualObject = &comment1;
	string szActualObjectName = "comment1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, comment1, "comment1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, comment2, "comment2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment3, "comment3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1, "commentK1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentV1, "commentV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1V1, "commentK1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentSup, "commentSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentNextPrev, "commentNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentFull, "commentFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint1, "commentPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint2, "commentPoint2", true );

	//compare with comment2
	actualObject = &comment2;
	szActualObjectName = "comment2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, comment1, "comment1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, comment2, "comment2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment3, "comment3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1, "commentK1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentV1, "commentV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1V1, "commentK1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentSup, "commentSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentNextPrev, "commentNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentFull, "commentFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint1, "commentPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint2, "commentPoint2", true );

	//compare with comment3
	actualObject = &comment3;
	szActualObjectName = "comment3";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment1, "comment1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment2, "comment2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, comment3, "comment3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1, "commentK1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentV1, "commentV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1V1, "commentK1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentSup, "commentSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentNextPrev, "commentNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentFull, "commentFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint1, "commentPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint2, "commentPoint2" );

	//compare with commentK1
	actualObject = &commentK1;
	szActualObjectName = "commentK1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment1, "comment1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment2, "comment2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment3, "comment3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentK1, "commentK1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentV1, "commentV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1V1, "commentK1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentSup, "commentSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentNextPrev, "commentNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentFull, "commentFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint1, "commentPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint2, "commentPoint2" );

	//compare with commentV1
	actualObject = &commentV1;
	szActualObjectName = "commentV1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment1, "comment1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment2, "comment2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment3, "comment3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1, "commentK1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentV1, "commentV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1V1, "commentK1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentSup, "commentSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentNextPrev, "commentNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentFull, "commentFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint1, "commentPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint2, "commentPoint2" );
	
	//compare with commentK1V1
	actualObject = &commentK1V1;
	szActualObjectName = "commentK1V1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment1, "comment1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment2, "comment2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment3, "comment3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1, "commentK1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentV1, "commentV1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentK1V1, "commentK1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentSup, "commentSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentNextPrev, "commentNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentFull, "commentFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint1, "commentPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint2, "commentPoint2" );

	//compare with commentSup
	actualObject = &commentSup;
	szActualObjectName = "commentSup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, comment1, "comment1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, comment2, "comment2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment3, "comment3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1, "commentK1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentV1, "commentV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1V1, "commentK1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentSup, "commentSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentNextPrev, "commentNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentFull, "commentFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint1, "commentPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint2, "commentPoint2", true );

	//compare with commentNextPrev
	actualObject = &commentNextPrev;
	szActualObjectName = "commentNextPrev";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment1, "comment1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment2, "comment2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment3, "comment3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1, "commentK1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentV1, "commentV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1V1, "commentK1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentSup, "commentSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentNextPrev, "commentNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentFull, "commentFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentPoint1, "commentPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint2, "commentPoint2", true );

	//compare with commentFull
	actualObject = &commentFull;
	szActualObjectName = "commentFull";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment1, "comment1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment2, "comment2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment3, "comment3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1, "commentK1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentV1, "commentV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1V1, "commentK1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentSup, "commentSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentNextPrev, "commentNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentFull, "commentFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentPoint1, "commentPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint2, "commentPoint2", true );

	//compare with commentPoint1
	actualObject = &commentPoint1;
	szActualObjectName = "commentPoint1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment1, "comment1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment2, "comment2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment3, "comment3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1, "commentK1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentV1, "commentV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1V1, "commentK1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentSup, "commentSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentNextPrev, "commentNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentFull, "commentFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentPoint1, "commentPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint2, "commentPoint2", true );

	//compare with commentPoint2
	actualObject = &commentPoint2;
	szActualObjectName = "commentPoint2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment1, "comment1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment2, "comment2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, comment3, "comment3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1, "commentK1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentV1, "commentV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentK1V1, "commentK1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentSup, "commentSup", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentNextPrev, "commentNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentFull, "commentFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, commentPoint1, "commentPoint1", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, commentPoint2, "commentPoint2" );


	return iReturn;
}



/**
 * This method tests the equal() method of two given fib -objects which are
 * equal.
 * It also compares the superior, next and previous fib -element commenters.
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
	
	//check the getNextFibElement() methode from cComment
	if ( const_cast<cFibElement*>(&fibObject1)->getNextFibElement() ==
			const_cast<cFibElement*>(&fibObject2)->getNextFibElement() ){
	
		cout<<"The next/ main fib -elementpointer for the commentelement are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -elementpointer for the commentelement are not equal."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cComment
	if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) ==
			const_cast<cFibElement*>(&fibObject2)->getFibElement( -1 ) ){
	
		cout<<"The previous fib -elementpointer for the commentelement are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the commentelement are not equal."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cComment
	if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() ==
			const_cast<cFibElement*>(&fibObject2)->getSuperiorFibElement() ){
	
		cout<<"The superior fib -elementpointer for the commentelement are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the commentelement are not equal."<<endl;
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
 * This method tests the copy methods and copyconstructor of the cComment class.
 *
 * methods tested:
 * 	- cComment( const cComment &commentElement );
 * 	- cFibElement *clone( ) const;
 * 	- cComment *copy( const unsignedIntFib iObjectComment=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementComment=0 ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a simple cComment"<<endl;

	string szKey = "";
	string szValue = "";
	cout<<"cComment commentSimple( \""<<szKey<<"\", \""<<szValue<<"\" );"<<endl;
	cComment commentSimple( szKey, szValue );

	cout<<"cComment commentSimpleCopyConstruct( commentSimple );"<<endl;
	cComment commentSimpleCopyConstruct( commentSimple );

	iReturn += testCompareTwoEqualObjectsStructur( commentSimpleCopyConstruct, "commentSimpleCopyConstruct", commentSimple, "commentSimple" );

	cout<<"cFibElement * pCommentSimpleClone = commentSimple.clone();"<<endl;
	cFibElement * pCommentSimpleClone = commentSimple.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pCommentSimpleClone, "pCommentSimpleClone", commentSimple, "commentSimple" );
	delete pCommentSimpleClone;

	cout<<"cFibElement * pCommentSimpleCopy = commentSimple.copy();"<<endl;
	cFibElement * pCommentSimpleCopy = commentSimple.copy();

	iReturn += testCompareTwoEqualObjectsStructur( *pCommentSimpleCopy, "pCommentSimpleCopy", commentSimple, "commentSimple" );
	delete pCommentSimpleCopy;

	cout<<"cFibElement * pCommentSimpleCopyElement = commentSimple.copyElement();"<<endl;
	cFibElement * pCommentSimpleCopyElement = commentSimple.copyElement();

	iReturn += testCompareTwoEqualObjectsStructur( *pCommentSimpleCopyElement, "pCommentSimpleCopyElement", commentSimple, "commentSimple" );
	delete pCommentSimpleCopyElement;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying for a other object or elementpoint"<<endl;

	cout<<"cFibElement * pCommentSimpleNoCopy = commentSimple.copy( 1 );"<<endl;
	cFibElement * pCommentSimpleNoCopy = commentSimple.copy( 1 );

	if ( pCommentSimpleNoCopy == NULL ){
	
		cout<<"The cComment was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cComment was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pCommentSimpleNoCopy;
	}

	cout<<"cFibElement * pCommentSimpleNoCopyElement = commentSimple.copyElement( 'f', 2 );"<<endl;
	cFibElement * pCommentSimpleNoCopyElement = commentSimple.copyElement( 'f', 2 );

	if ( pCommentSimpleNoCopyElement == NULL ){
	
		cout<<"The cComment -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cComment -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pCommentSimpleNoCopyElement;
	}

	cout<<"pCommentSimpleNoCopyElement = commentSimple.copyElement( 'u', 2 );"<<endl;
	pCommentSimpleNoCopyElement = commentSimple.copyElement( 'u', 2 );

	if ( pCommentSimpleNoCopyElement == NULL ){
	
		cout<<"The cComment -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cComment -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pCommentSimpleNoCopyElement;
	}

	cout<<"pCommentSimpleNoCopyElement = commentSimple.copyElement( 'r', 1 );"<<endl;
	pCommentSimpleNoCopyElement = commentSimple.copyElement( 'r', 1 );

	if ( pCommentSimpleNoCopyElement == NULL ){
	
		cout<<"The cComment -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cComment -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pCommentSimpleNoCopyElement;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cComment with all members set"<<endl;

	//comment in fib -element structur
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;

	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeComments testTypeComment;"<<endl;
	cTypeComments testTypeComment;
	
	//create vector domain with two elements
	cout<<"cDomainNaturalNumberBit domainsNat9( 9 );"<<endl;
	cDomainNaturalNumberBit domainsNat9( 9 );

	cout<<"rootD2.getDomains()->addDomain( testTypeComment, &domainsNat9 );"<<endl;
	rootD2.getDomains()->addDomain( testTypeComment, &domainsNat9 );

	szKey = "type";
	szValue = "all set";
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment comment2E2( \""<<szKey<<"\", \""<<szValue<<
		"\", &poinNext, &rootD2 );"<<endl;
	cComment comment2E2( szKey, szValue, &poinNext, &rootD2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinPrev;"<<endl;
	cPoint poinPrev;
	
	cout<<"cComment comment2E2( \""<<szKey<<"\", \""<<szValue<<
		"\", &rootD2, &poinPrev, &poinNext );"<<endl;
	cComment comment2E2( szKey, szValue, &rootD2, &poinPrev, &poinNext );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"cComment comment2E2CopyConstruct( comment2E2 );"<<endl;
	cComment comment2E2CopyConstruct( comment2E2 );

	if ( comment2E2CopyConstruct.equalElement( comment2E2 ) ){

		cout<<"The comment2E2CopyConstruct fib -element is equal to comment2E2. "<<endl;
	}else{
		cerr<<"Error: The comment2E2CopyConstruct fib -element is not equal to comment2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( comment2E2CopyConstruct );

	cout<<"cFibElement * pComment2E2Copy = comment2E2.copy();"<<endl;
	cFibElement * pComment2E2Copy = comment2E2.copy();
	iReturn += testCompareTwoEqualObjects( *pComment2E2Copy, "pComment2E2Copy", comment2E2, "comment2E2" );
	//check the getFibElement() methode from cComment
	if ( NULL == pComment2E2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous fib -elementpointer for the commentelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the commentelement is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cComment
	if ( NULL == pComment2E2Copy->getSuperiorFibElement() ){
	
		cout<<"The superior fib -elementpointer for the commentelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the commentelement is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( pComment2E2Copy );

	cout<<"cFibElement * pComment2E2CopyElement = comment2E2.copyElement( 'u', 1 );"<<endl;
	cFibElement * pComment2E2CopyElement = comment2E2.copyElement( 'u', 1 );

	if ( pComment2E2CopyElement->equalElement( comment2E2 ) ){
	
		cout<<"The pComment2E2CopyElement fib -element is equal to comment2E2. "<<endl;
	}else{
		cerr<<"Error: The pComment2E2CopyElement fib -element is not equal to comment2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pComment2E2CopyElement );
	delete pComment2E2CopyElement;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a limb with more then one commentelement and pointelement"<<endl;

	//a limb with more then one commentelement and pointelement
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment comment3( \"name\", \"comment3\", &point1 );"<<endl;
	cComment comment3( "name", "comment3", &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment comment3( \"name\", \"comment3\", NULL, NULL, &point1 );"<<endl;
	cComment comment3( "name", "comment3", NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	szKey = "debug";
	szValue = "error";
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment comment1Obj2( \""<<szKey<<"\", \""<<szValue<<
		"\", &comment3 );"<<endl;
	cComment comment1Obj2( szKey, szValue, &comment3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment comment1Obj2( \""<<szKey<<"\", \""<<szValue<<
		"\", NULL, NULL, &comment3 );"<<endl;
	cComment comment1Obj2( szKey, szValue, NULL, NULL, &comment3 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<endl<<"cComment comment1Obj2CopyConstruct( comment1Obj2 );"<<endl;
	cComment comment1Obj2CopyConstruct( comment1Obj2 );

	if ( comment1Obj2CopyConstruct.equalElement( comment1Obj2 ) ){
	
		cout<<"The comment1Obj2CopyConstruct fib -element is equal to comment1Obj2. "<<endl;
	}else{
		cerr<<"Error: The comment1Obj2CopyConstruct fib -element is not equal to comment1Obj2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( comment1Obj2CopyConstruct );

	cout<<"cFibElement * pComment1ColorSwO2LayerO1CopyConstructCopy = comment1Obj2CopyConstruct.copy();"<<endl;
	cFibElement * comment1Obj2Copy =
		comment1Obj2.copy();

	iReturn += testCompareTwoEqualObjects(
		*comment1Obj2Copy, "comment1Obj2Copy",
		comment1Obj2, "comment1Obj2" );
	//check the getFibElement() methode from cComment
	if ( NULL == comment1Obj2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous fib -elementpointer for the commentelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the commentelement is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cComment
	if ( comment1Obj2Copy->getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -elementpointer for the commentelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the commentelement is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( comment1Obj2Copy );

	cout<<"cFibElement * pComment1Obj2 = comment1Obj2.copyElement();"<<endl;
	cFibElement * pComment1Obj2 = comment1Obj2.copyElement();

	if ( pComment1Obj2->equalElement( comment1Obj2 ) ){
	
		cout<<"The pComment1Obj2 fib -element is equal to comment1Obj2. "<<endl;
	}else{
		cerr<<"Error: The pComment1Obj2 fib -element is not equal to comment1Obj2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pComment1Obj2 );
	delete pComment1Obj2;

	return iReturn;
}



/**
 * This method tests a in the xml -format stored cComment.
 *
 * @param szFilename the name of the file wher the cFibVector is stored
 * @param szKey the key string the stored comment should have
 * @param szValue the value string the stored comment should have
 * @return the number of errors occured in the test
 */
int testXmlComment( const string szFilename, string szKey, string szValue ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cComment:"<<endl;
	
	TiXmlDocument xmlDocCommentValue( szFilename );
	bool loadOkay = xmlDocCommentValue.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocCommentValue );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();
		
		const string szCommentElementName = "comment";
		if ( szElementName == szCommentElementName ){
			cout<<"The root element is correctly named \""<< szCommentElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szCommentElementName <<"\"."<<endl;
			iReturn++;
		}
		
		const char * szKeyValue = pXmlElement->Attribute( "key" );
		
		if ( szKeyValue == NULL ){
			cerr<<"Error: The comment has no key attribue."<<endl;
			iReturn++;
		}else{
			 if ( szKey.compare( szKeyValue ) == 0 ) {
				cout<<"The key of the comment is correctly \""<< szKey <<"\". "<<endl;
			}else{
				cerr<<"Error: The key of the comment is \""<< szKeyValue
					<<"\", but should be \""<< szKey <<"\"."<<endl;
				iReturn++;
			}
		}
		const char * szValueValue = pXmlElement->Attribute( "value" );
		
		if ( szValueValue == NULL ){
			cerr<<"Error: The comment has no value attribue."<<endl;
			iReturn++;
		}else{
			 if ( szValue.compare( szValueValue ) == 0 ) {
				cout<<"The value of the comment is correctly \""<< szValue <<"\". "<<endl;
			}else{
				cerr<<"Error: The value of the comment is \""<< szValueValue
					<<"\", but should be \""<< szValue <<"\"."<<endl;
				iReturn++;
			}
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	return iReturn;
}


/**
 * This method tests the storeXml() method of the cComment class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an comment with an empty undercomment"<<endl;

	string szKey = "";
	string szValue = "";
	cout<<"cComment comment1( \""<<szKey<<"\", \""<<szValue<< "\" );"<<endl;
	cComment comment1( szKey, szValue );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlCommentFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "comment1.xml" );
	ofstream * pFileVectorPostion = new ofstream( szXmlCommentFileName );
	
	bool bStoreSuccesfull = comment1.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cComment was stored successfull to the file \""<< szXmlCommentFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cComment to the file \""<< szXmlCommentFileName <<"\" failed."<<endl;
		iReturn++;
	}	
	iReturn += testXmlComment( szXmlCommentFileName, szKey, szValue );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an comment, with the key and value set"<<endl;

	szKey = "key";
	szValue = "value";
	cout<<"cComment comment2( \""<<szKey<<"\", \""<<szValue<< "\" );"<<endl;
	cComment comment2( szKey, szValue );
	
	szFileNameBuffer[0] = 0;
	szXmlCommentFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "comment2.xml" );
	pFileVectorPostion = new ofstream( szXmlCommentFileName );
	
	bStoreSuccesfull = comment2.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cComment was stored successfull to the file \""<< szXmlCommentFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cComment to the file \""<< szXmlCommentFileName <<"\" failed."<<endl;
		iReturn++;
	}

	iReturn += testXmlComment( szXmlCommentFileName, szKey, szValue );

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

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method one undercomment"<<endl;

	cout<<"cPoint point1;"<<flush<<endl;
	cPoint point1;

	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	
	cout<<"cTypeComments typeComments;"<<endl;
	cTypeComments typeComments;
	
	cout<<"cDomainNaturalNumberBit domNatB4( 4 );"<<endl;
	cDomainNaturalNumberBit domNatB4( 4 );

	cout<<"root.getDomains()->addDomain( typeComments, &domNatB4 );"<<endl;
	root.getDomains()->addDomain( typeComments, &domNatB4 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment comment1( \"key\", \"value\", &point1, &root );"<<endl;
	cComment comment1( "key", "value", &point1, &root );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cComment comment1( \"key\", \"value\", &root, &root, &point1 );"<<endl;
	cComment comment1( "key", "value", &root, &root, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"comment1.ulCommentNumber = 1;"<<endl;
	comment1.ulCommentNumber = 1;
	
	//test get compressed size
	unsigned int uiCompressedSize = 4 + 4 + 5;
	if ( (unsigned int)(comment1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			comment1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "comment1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bool bStoreSuccesfull = comment1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cComment1[] = { 0x17, 0x12  };
	iReturn += compareBytsWithFile( szFileNameBuffer, cComment1, 2 );


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with other values"<<endl;

	cout<<"comment1.ulCommentNumber = 5;"<<endl;
	comment1.ulCommentNumber = 5;
	
	//test get compressed size
	uiCompressedSize = 4 + 4 + 5;
	if ( (unsigned int)(comment1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			comment1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "commentChV.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = comment1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char szCommentChV[] = { 0x57, 0x12 };
	iReturn += compareBytsWithFile( szFileNameBuffer, szCommentChV, 2 );

	return iReturn;
}



/**
 * This method positions methods of the class.
 *
 * methods tested:
 * 	- string getKey() const;
 * 	- void setKey( const string & szInKey );
 * 	- string getValue() const;
 * 	- void setValue( const string & szInValue );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCommentValues( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the comments key and value methods"<<endl;
	
	string szKey = "";
	string szValue = "";
	cout<<"cComment comment1( \""<<szKey<<"\", \""<<szValue<<"\" );"<<endl;
	cComment comment1( szKey, szValue );
	
	//testing the getKey() method
	if ( szKey == comment1.getKey() ){
	
		cout<<"The key for the commentelement is correctly \""<<szKey <<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szKey<<
			"\", but is \""<<comment1.getKey()<<"\". "<<endl;
		iReturn++;
	}
	//check the getValue() methode from cComment
	if ( comment1.getValue() == szValue ){
	
		cout<<"The value for the commentelement is correctly equal to \""<<szValue<<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szValue<<
			"\", but is \""<<comment1.getValue()<<"\". "<<endl;
		iReturn++;
	}

	szKey = "key";
	cout<<"comment1.setKey( \""<<szKey<<"\" );"<<endl;
	comment1.setKey( szKey );
	//testing the getKey() method
	if ( szKey == comment1.getKey() ){
	
		cout<<"The key for the commentelement is correctly \""<<szKey <<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szKey<<
			"\", but is \""<<comment1.getKey()<<"\". "<<endl;
		iReturn++;
	}
	//check the getValue() methode from cComment
	if ( comment1.getValue() == szValue ){
	
		cout<<"The value for the commentelement is correctly equal to \""<<szValue<<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szValue<<
			"\", but is \""<<comment1.getValue()<<"\". "<<endl;
		iReturn++;
	}
	
	szValue = "value";
	cout<<"comment1.setValue( \""<<szValue<<"\" );"<<endl;
	comment1.setValue( szValue );
	//testing the getKey() method
	if ( szKey == comment1.getKey() ){
	
		cout<<"The key for the commentelement is correctly \""<<szKey <<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szKey<<
			"\", but is \""<<comment1.getKey()<<"\". "<<endl;
		iReturn++;
	}
	//check the getValue() methode from cComment
	if ( comment1.getValue() == szValue ){
	
		cout<<"The value for the commentelement is correctly equal to \""<<szValue<<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szValue<<
			"\", but is \""<<comment1.getValue()<<"\". "<<endl;
		iReturn++;
	}

	szKey = "key";
	cout<<"comment1.setKey( \""<<szKey<<"\" );"<<endl;
	comment1.setKey( szKey );
	//testing the getKey() method
	if ( szKey == comment1.getKey() ){
	
		cout<<"The key for the commentelement is correctly \""<<szKey <<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szKey<<
			"\", but is \""<<comment1.getKey()<<"\". "<<endl;
		iReturn++;
	}
	//check the getValue() methode from cComment
	if ( comment1.getValue() == szValue ){
	
		cout<<"The value for the commentelement is correctly equal to \""<<szValue<<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szValue<<
			"\", but is \""<<comment1.getValue()<<"\". "<<endl;
		iReturn++;
	}

	szKey = "key1";
	cout<<"comment1.setKey( \""<<szKey<<"\" );"<<endl;
	comment1.setKey( szKey );
	//testing the getKey() method
	if ( szKey == comment1.getKey() ){
	
		cout<<"The key for the commentelement is correctly \""<<szKey <<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szKey<<
			"\", but is \""<<comment1.getKey()<<"\". "<<endl;
		iReturn++;
	}
	//check the getValue() methode from cComment
	if ( comment1.getValue() == szValue ){
	
		cout<<"The value for the commentelement is correctly equal to \""<<szValue<<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szValue<<
			"\", but is \""<<comment1.getValue()<<"\". "<<endl;
		iReturn++;
	}

	szValue = "value1";
	cout<<"comment1.setValue( \""<<szValue<<"\" );"<<endl;
	comment1.setValue( szValue );
	//testing the getKey() method
	if ( szKey == comment1.getKey() ){
	
		cout<<"The key for the commentelement is correctly \""<<szKey <<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szKey<<
			"\", but is \""<<comment1.getKey()<<"\". "<<endl;
		iReturn++;
	}
	//check the getValue() methode from cComment
	if ( comment1.getValue() == szValue ){
	
		cout<<"The value for the commentelement is correctly equal to \""<<szValue<<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szValue<<
			"\", but is \""<<comment1.getValue()<<"\". "<<endl;
		iReturn++;
	}

	szValue = "value1";
	cout<<"comment1.setValue( \""<<szValue<<"\" );"<<endl;
	comment1.setValue( szValue );
	//testing the getKey() method
	if ( szKey == comment1.getKey() ){
	
		cout<<"The key for the commentelement is correctly \""<<szKey <<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szKey<<
			"\", but is \""<<comment1.getKey()<<"\". "<<endl;
		iReturn++;
	}
	//check the getValue() methode from cComment
	if ( comment1.getValue() == szValue ){
	
		cout<<"The value for the commentelement is correctly equal to \""<<szValue<<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szValue<<
			"\", but is \""<<comment1.getValue()<<"\". "<<endl;
		iReturn++;
	}

	szValue = "";
	cout<<"comment1.setValue( \""<<szValue<<"\" );"<<endl;
	comment1.setValue( szValue );
	//testing the getKey() method
	if ( szKey == comment1.getKey() ){
	
		cout<<"The key for the commentelement is correctly \""<<szKey <<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szKey<<
			"\", but is \""<<comment1.getKey()<<"\". "<<endl;
		iReturn++;
	}
	//check the getValue() methode from cComment
	if ( comment1.getValue() == szValue ){
	
		cout<<"The value for the commentelement is correctly equal to \""<<szValue<<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szValue<<
			"\", but is \""<<comment1.getValue()<<"\". "<<endl;
		iReturn++;
	}

	szKey = "";
	cout<<"comment1.setKey( \""<<szKey<<"\" );"<<endl;
	comment1.setKey( szKey );
	//testing the getKey() method
	if ( szKey == comment1.getKey() ){
	
		cout<<"The key for the commentelement is correctly \""<<szKey <<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szKey<<
			"\", but is \""<<comment1.getKey()<<"\". "<<endl;
		iReturn++;
	}
	//check the getValue() methode from cComment
	if ( comment1.getValue() == szValue ){
	
		cout<<"The value for the commentelement is correctly equal to \""<<szValue<<"\". "<<endl;
	}else{
		cerr<<"Error: The value for the commentelement is not equal to \""<<szValue<<
			"\", but is \""<<comment1.getValue()<<"\". "<<endl;
		iReturn++;
	}

	return iReturn;
}































