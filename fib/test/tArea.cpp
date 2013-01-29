/**
 * @file tArea
 * file name: tArea.cpp
 * @author Betti Oesterholz
 * @date 15.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cArea.
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
 * This file contains the test for the class cArea, which
 * represents a Fib -areaelement.
 *
 *
 * What's tested of class cArea:
 * 	- cArea( const cVectorArea & inVectorArea, cFibElement * pInUnderobject = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- cArea( const cArea &areaElement );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- bool hasUnderAllObjects( ) const;
 * 	- unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
 * 	- bool evalueObject( iEvaluePosition & evaluePosition, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties ) const;
 * 	- bool evalueObject( iEvalueFibElement & evalueFibElement, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties, const list<char> & liCFibElementTyps );
 * 	- bool equal( const cFibElement & fibObject ) const;
 * 	- bool equalElement( const cFibElement & fibElement ) const;
 * 	- cArea( const cArea &areaElement );
 * 	- cFibElement *clone( ) const;
 * 	- cArea *copy( const unsignedIntFib iObjectArea=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementArea=0 ) const;
 * 	- bool storeXml( ostream &stream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream &stream ) const;
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- cFibVariable * getDefinedVariable();
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
 * 	- unsignedIntFib getNumberOfSubareas() const;
 * 	- cVectorArea * getSubarea( unsignedIntFib iSubarea=1 );
 * 	- bool addSubarea( const cVectorArea &underArea, unsignedIntFib uiPosition=0 );
 * 	- bool deleteSubarea( unsignedIntFib uiSubareaPosition );
 * 	- bool sort();
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
15.02.2010  Oesterholz  created
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
28.03.2011  Oesterholz  storing to binary stream
06.06.2011  Oesterholz  number atribute in XML-vector is now optional
05.08.2011  Oesterholz  FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES implemented
25.08.2011  Oesterholz  subarea to subarea
10.11.2011  Oesterholz  Bugfix: evalueObject() don't overwrite properties
02.01.2012  Oesterholz  cTypeSubArea to cTypeArea and domain for subare counter
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
28.01.2013  Oesterholz  COLOR_SW changed to COLOR_GRAYSCALE
*/

#include "version.h"

#include "cArea.h"
#include "cPoint.h"
#include "cRoot.h"
#include "cProperty.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cTypeVariable.h"
#include "cTypeArea.h"
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
int testSubAreas( unsigned long &ulTestphase );
int testVariable( unsigned long &ulTestphase );
int testSort( unsigned long &ulTestphase );


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for cArea methods"<<endl;
	cout<<      "=============================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testEvalueObject( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testSubAreas( ulTestphase );
	iReturn += testVariable( ulTestphase );
	iReturn += testSort( ulTestphase );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the constructor of the cArea class.
 *
 * methods tested:
 * 	- cArea( const cVectorArea & inVectorArea, cFibElement * pInUnderobject = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- cArea( const cArea &areaElement );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- unsignedIntFib getNumberOfElement()
 * 	- cVectorArea * getSubarea( 1 );
 * 	- bool hasUnderAllObjects() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cAreavector"<<endl;

	cout<<"cVectorArea vecArea1;"<<endl;
	cVectorArea vecArea1;

	cout<<"cArea areaEmpty( vecArea1 );"<<endl;
	cArea areaEmpty( vecArea1 );

	//check the getType() methode from cArea
	if ( areaEmpty.getType() == 'a' ){
	
		cout<<"The type of the areaelement is correctly 'a' . "<<endl;
	}else{
		cerr<<"Error: The type of the areaelement is "<<
			areaEmpty.getType()<<" but should be 'a' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cArea
	if ( ! areaEmpty.isValidFibElement() ){
	
		cout<<"The areaelement is correctly not a correct areaelement. "<<endl;
	}else{
		cerr<<"Error: The areaelement is a correct areaelement, but should not be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cArea
	if ( areaEmpty.isMovable() ){
	
		cout<<"The areaelement is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The areaelement is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cArea
	if ( areaEmpty.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the areaelement is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the areaelement is "<<
			areaEmpty.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cArea
	if ( areaEmpty.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the areaelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the areaelement is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cArea
	if ( areaEmpty.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the areaelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the areaelement is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cArea
	if ( areaEmpty.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the areaelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the areaelement is "<<
			areaEmpty.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfSubareas() methode from cArea
	if ( areaEmpty.getNumberOfSubareas() == 1 ){
	
		cout<<"The areaelement has correctly one subarea. "<<endl;
	}else{
		cerr<<"Error: The areaelement has not one subarea, but "<<
			areaEmpty.getNumberOfSubareas() <<" ."<<endl;
		iReturn++;
	}
	//check the getSubarea( 1 ) methode from cArea
	if ( *areaEmpty.getSubarea( 1 ) == vecArea1 ){
	
		cout<<"The first subarea for the areaelement is correctly equal to vecArea1. "<<endl;
	}else{
		cerr<<"Error: The first subarea for the areaelement is not equal to vecArea1."<<endl;
		iReturn++;
	}
	//check the getSubarea( 1 ) methode from cArea
	if ( areaEmpty.getSubarea( 1 ) != &vecArea1 ){
	
		cout<<"The first subarea for the areaelement is correctly not the vecArea1 object. "<<endl;
	}else{
		cerr<<"Error: The first subarea for the areaelement is the vecArea1 object."<<endl;
		iReturn++;
	}
	//check the getSubarea( 0 ) methode from cArea
	if ( areaEmpty.getSubarea( 0 ) == NULL ){
	
		cout<<"Ther is correctly no 0'th subarea. "<<endl;
	}else{
		cerr<<"Error: Ther is a 0'th subarea."<<endl;
		iReturn++;
	}
	//check the getSubarea( 1 ) methode from cArea
	if ( areaEmpty.getSubarea( 2 ) == NULL ){
	
		cout<<"Ther is correctly no second subarea. "<<endl;
	}else{
		cerr<<"Error: Ther is a second subarea."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cArea
	if ( ! areaEmpty.hasUnderAllObjects()){
	
		cout<<"The areaelement has correctly missing a needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The areaelement is not missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cArea with a changed subarea"<<endl;

	cout<<"cVectorArea vecArea;"<<endl;
	cVectorArea vecArea;
	cout<<"vecArea.setValue( 1, 1);"<<endl;
	vecArea.setValue( 1, 1);
	cout<<"vecArea.setValue( 2, 2);"<<endl;
	vecArea.setValue( 2, 2);

	cout<<"cArea area1( vecArea );"<<endl;
	cArea area1( vecArea );

	//check the getType() methode from cArea
	if ( area1.getType() == 'a' ){
	
		cout<<"The type of the areaelement is correctly 'a' . "<<endl;
	}else{
		cerr<<"Error: The type of the areaelement is "<<
			area1.getType()<<" but should be 'a' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cArea
	if ( ! area1.isValidFibElement() ){
	
		cout<<"The areaelement is correctly not a correct areaelement. "<<endl;
	}else{
		cerr<<"Error: The areaelement is a correct areaelement, but shouldn't be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cArea
	if ( area1.isMovable() ){
	
		cout<<"The areaelement is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The areaelement is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cArea
	if ( area1.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the areaelement is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the areaelement is "<<
			area1.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cArea
	if ( area1.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the areaelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the areaelement is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cArea
	if ( area1.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the areaelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the areaelement is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cArea
	if ( area1.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the areaelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the areaelement is "<<
			area1.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getNumberOfSubareas() methode from cArea
	if ( areaEmpty.getNumberOfSubareas() == 1 ){
	
		cout<<"The areaelement has correctly one subarea. "<<endl;
	}else{
		cerr<<"Error: The areaelement has not one subarea, but "<<
			areaEmpty.getNumberOfSubareas() <<" ."<<endl;
		iReturn++;
	}
	//check the getSubarea( 1 ) methode from cArea
	if ( area1.getSubarea( 1 ) != NULL ){
	
		if ( vecArea == *(area1.getSubarea( 1 )) ){
		
			cout<<"The area has the correct first subarea vecArea. "<<endl;
		}else{
			cerr<<"Error: The area has a not the correct first subarea vecArea. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The area has a first subarea (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the getSubarea( 0 ) methode from cArea
	if ( areaEmpty.getSubarea( 0 ) == NULL ){
	
		cout<<"Ther is correctly no 0'th subarea. "<<endl;
	}else{
		cerr<<"Error: Ther is a 0'th subarea."<<endl;
		iReturn++;
	}
	//check the getSubarea( 1 ) methode from cArea
	if ( areaEmpty.getSubarea( 2 ) == NULL ){
	
		cout<<"Ther is correctly no second subarea. "<<endl;
	}else{
		cerr<<"Error: Ther is a second subarea."<<endl;
		iReturn++;
	}

	//check the hasUnderAllObjects() methode from cArea
	if ( ! area1.hasUnderAllObjects() ){
	
		cout<<"The areaelement has correctly not all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The areaelement is not missing a underobject."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cArea with a superior fib -element"<<endl;

	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea areaSup( vecArea, NULL, &rootEmpty1 );"<<endl;
	cArea areaSup( vecArea, NULL, &rootEmpty1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea areaSup( vecArea, &rootEmpty1 );"<<endl;
	cArea areaSup( vecArea, &rootEmpty1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the getType() methode from cArea
	if ( areaSup.getType() == 'a' ){
	
		cout<<"The type of the areaelement is correctly 'a' . "<<endl;
	}else{
		cerr<<"Error: The type of the areaelement is "<<
			areaSup.getType()<<" but should be 'a' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cArea
	if ( ! areaSup.isValidFibElement() ){
	
		cout<<"The areaelement is correctly not a correct areaelement. "<<endl;
	}else{
		cerr<<"Error: The areaelement is a correct areaelement, but shouldn't be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cArea
	if ( areaSup.isMovable() ){
	
		cout<<"The areaelement is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The areaelement is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cArea
	if ( areaSup.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the areaelement is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the areaelement is "<<
			areaSup.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cArea
	if ( areaSup.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the areaelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the areaelement is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cArea
	if ( areaSup.getFibElement( -1 ) == &rootEmpty1 ){
	
		cout<<"The previous fib -element for the areaelement is correctly rootEmpty1. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the areaelement is not rootEmpty1."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cArea
	if ( areaSup.getSuperiorFibElement() == &rootEmpty1 ){
	
		cout<<"The superior fib -element for the areaelement is correctly rootEmpty1. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the areaelement is "<<
			areaSup.getSuperiorFibElement() << " and not rootEmpty1."<<endl;
		iReturn++;
	}
	//check the getNumberOfSubareas() methode from cArea
	if ( areaEmpty.getNumberOfSubareas() == 1 ){
	
		cout<<"The areaelement has correctly one subarea. "<<endl;
	}else{
		cerr<<"Error: The areaelement has not one subarea, but "<<
			areaEmpty.getNumberOfSubareas() <<" ."<<endl;
		iReturn++;
	}
	//check the getSubarea( 1 ) methode from cArea
	if ( *areaSup.getSubarea( 1 ) == vecArea ){
	
		cout<<"The area has the correctly subarea equal to vecArea. "<<endl;

	}else{
		cerr<<"Error: The area has a subareaequal not equal to vecArea. "<<endl;
		iReturn++;
	}
	//check the getSubarea( 0 ) methode from cArea
	if ( areaEmpty.getSubarea( 0 ) == NULL ){
	
		cout<<"Ther is correctly no 0'th subarea. "<<endl;
	}else{
		cerr<<"Error: Ther is a 0'th subarea."<<endl;
		iReturn++;
	}
	//check the getSubarea( 1 ) methode from cArea
	if ( areaEmpty.getSubarea( 2 ) == NULL ){
	
		cout<<"Ther is correctly no second subarea. "<<endl;
	}else{
		cerr<<"Error: Ther is a second subarea."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cArea
	if ( ! areaSup.hasUnderAllObjects() ){
	
		cout<<"The areaelement has correctly not all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The areaelement is not missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cArea with a underobject"<<endl;
	
	cout<<"cArea areaNextPrev( vecArea, &areaEmpty );"<<endl;
	cArea areaNextPrev( vecArea, &areaEmpty );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cArea with a next and previous fib -element"<<endl;
	
	cout<<"cArea areaNextPrev( vecArea, NULL, &area1, &areaEmpty );"<<endl;
	cArea areaNextPrev( vecArea, NULL, &area1, &areaEmpty );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	//check the getType() methode from cArea
	if ( areaNextPrev.getType() == 'a' ){
	
		cout<<"The type of the areaelement is correctly 'a' . "<<endl;
	}else{
		cerr<<"Error: The type of the areaelement is "<<
			areaNextPrev.getType()<<" but should be 'a' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cArea
	if ( areaNextPrev.isValidFibElement() ){
	
		cout<<"The areaelement is correctly a correct areaelement. "<<endl;
	}else{
		cerr<<"Error: The areaelement is not a correct areaelement, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cArea
	if ( areaNextPrev.isMovable() ){
	
		cout<<"The areaelement is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The areaelement is not movebel."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNumberOfElement() methode from cArea
	if ( areaNextPrev.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the areaelement is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the areaelement is "<<
			areaNextPrev.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNumberOfElement() methode from cArea
	if ( areaNextPrev.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the areaelement is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the areaelement is "<<
			areaNextPrev.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNextFibElement() methode from cArea
	if ( areaNextPrev.getNextFibElement() == &areaEmpty ){
	
		cout<<"The next/ main fib -element for the areaelement is correctly areaEmpty. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the areaelement is not areaEmpty."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cArea
	if ( areaNextPrev.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the areaelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the areaelement is not NULL."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cArea
	if ( areaNextPrev.getFibElement( -1 ) == &area1 ){
	
		cout<<"The previous fib -element for the areaelement is correctly area1. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the areaelement is not area1."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getSuperiorFibElement() methode from cArea
	if ( areaNextPrev.getSuperiorFibElement() == NULL){
	
		cout<<"The superior fib -element for the areaelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the areaelement is "<<
			areaNextPrev.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getNumberOfSubareas() methode from cArea
	if ( areaEmpty.getNumberOfSubareas() == 1 ){
	
		cout<<"The areaelement has correctly one subarea. "<<endl;
	}else{
		cerr<<"Error: The areaelement has not one subarea, but "<<
			areaEmpty.getNumberOfSubareas() <<" ."<<endl;
		iReturn++;
	}
	//check the getSubarea( 1 ) methode from cArea
	if ( areaNextPrev.getSubarea( 1 ) != NULL ){
	
		if ( vecArea == *(areaNextPrev.getSubarea( 1 )) ){
		
			cout<<"The area has the correct subarea vecArea. "<<endl;
		}else{
			cerr<<"Error: The area has a not the correct subarea vecArea. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The area has a no subarea (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the getSubarea( 0 ) methode from cArea
	if ( areaEmpty.getSubarea( 0 ) == NULL ){
	
		cout<<"Ther is correctly no 0'th subarea. "<<endl;
	}else{
		cerr<<"Error: Ther is a 0'th subarea."<<endl;
		iReturn++;
	}
	//check the getSubarea( 1 ) methode from cArea
	if ( areaEmpty.getSubarea( 2 ) == NULL ){
	
		cout<<"Ther is correctly no second subarea. "<<endl;
	}else{
		cerr<<"Error: Ther is a second subarea."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cArea
	if ( ! areaNextPrev.hasUnderAllObjects()  ){
	
		cout<<"The areaelement has correctly not all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The areaelement is not missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cArea with all parameters given"<<endl;
	
	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeArea testTypeArea;"<<endl;
	cTypeArea testTypeArea;
	
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

	cout<<"rootD2.getDomains()->addDomain( testTypeArea, &vectorDomainD2 );"<<endl;
	rootD2.getDomains()->addDomain( testTypeArea, &vectorDomainD2 );

	cout<<"cPoint point1;"<<endl;
	cPoint point1;

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea areaFull( vecArea, &point1, &rootD2 );"<<endl;
	cArea areaFull( vecArea, &point1, &rootD2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea areaFull( vecArea, &rootD2, &area1, &point1 );"<<endl;
	cArea areaFull( vecArea, &rootD2, &area1, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the getType() methode from cArea
	if ( areaFull.getType() == 'a' ){
	
		cout<<"The type of the areaelement is correctly 'a' . "<<endl;
	}else{
		cerr<<"Error: The type of the areaelement is "<<
			areaFull.getType()<<" but should be 'a' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cArea
	if ( areaFull.isValidFibElement() ){
	
		cout<<"The areaelement is correctly a correct areaelement. "<<endl;
	}else{
		cerr<<"Error: The areaelement is not a correct areaelement, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cArea
	if ( areaFull.isMovable() ){
	
		cout<<"The areaelement is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The areaelement is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cArea
	if ( areaFull.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the areaelement is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the areaelement is "<<
			areaFull.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cArea
	if ( areaFull.getNextFibElement() == &point1 ){
	
		cout<<"The next/ main fib -element for the areaelement is correctly areaEmpty. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the areaelement is not areaEmpty."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cArea
	if ( areaFull.getFibElement( -1 ) == &rootD2 ){
	
		cout<<"The previous fib -element for the areaelement is correctly rootD2. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the areaelement is not rootD2."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cArea
	if ( areaFull.getFibElement( -1 ) == &area1 ){
	
		cout<<"The previous fib -element for the areaelement is correctly area1. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the areaelement is not area1."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getSuperiorFibElement() methode from cArea
	if ( areaFull.getSuperiorFibElement() == &rootD2 ){
	
		cout<<"The superior fib -element for the areaelement is correctly rootD2. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the areaelement is "<<
			areaFull.getSuperiorFibElement() << " and not rootD2."<<endl;
		iReturn++;
	}
	//check the getNumberOfSubareas() methode from cArea
	if ( areaEmpty.getNumberOfSubareas() == 1 ){
	
		cout<<"The areaelement has correctly one subarea. "<<endl;
	}else{
		cerr<<"Error: The areaelement has not one subarea, but "<<
			areaEmpty.getNumberOfSubareas() <<" ."<<endl;
		iReturn++;
	}
	//check the getSubarea( 1 ) methode from cArea
	if ( areaFull.getSubarea( 1 ) != NULL ){
	
		if ( vecArea == *(areaFull.getSubarea( 1 )) ){
		
			cout<<"The area has the correct subarea vecArea. "<<endl;
		}else{
			cerr<<"Error: The area has a not the correct subarea vecArea. "<<endl;
			cerr<<"The subarea has "<< areaFull.getSubarea( 1 )->getNumberOfElements() <<" elements. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The area has a no subarea (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the getSubarea( 0 ) methode from cArea
	if ( areaEmpty.getSubarea( 0 ) == NULL ){
	
		cout<<"Ther is correctly no 0'th subarea. "<<endl;
	}else{
		cerr<<"Error: Ther is a 0'th subarea."<<endl;
		iReturn++;
	}
	//check the getSubarea( 1 ) methode from cArea
	if ( areaEmpty.getSubarea( 2 ) == NULL ){
	
		cout<<"Ther is correctly no second subarea. "<<endl;
	}else{
		cerr<<"Error: Ther is a second subarea."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cArea
	if ( areaFull.hasUnderAllObjects() ){
	
		cout<<"The areaelement has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The areaelement is missing a underobject."<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cArea with the subarea from 1 to 2"<<endl;

	cout<<"cVectorPosition vecPositionE2( 2 );"<<endl;
	cVectorPosition vecPositionE2( 2 );

	cout<<"cPoint point1( &vecPositionE2 );"<<endl;
	cPoint point1( &vecPositionE2 );
	
	cout<<"cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );"<<endl;
	cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property1( vecPropertyColorSW, &point1 );"<<endl;
	cProperty property1( vecPropertyColorSW, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property1( vecPropertyColorSW, NULL, NULL, &point1 );"<<endl;
	cProperty property1( vecPropertyColorSW, NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"cVectorArea vecArea;"<<endl;
	cVectorArea vecArea;
	cout<<"vecArea.setValue( 1, 1);"<<endl;
	vecArea.setValue( 1, 1);
	cout<<"vecArea.setValue( 2, 2);"<<endl;
	vecArea.setValue( 2, 2);

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea area1( vecArea, &property1 );"<<endl;
	cArea area1( vecArea, &property1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea area1( vecArea, NULL, NULL, &property1 );"<<endl;
	cArea area1( vecArea, NULL, NULL, &property1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"point1.getPosition()->setVariable( 1, area1.getDefinedVariable() );"<<endl;
	point1.getPosition()->setVariable( 1, area1.getDefinedVariable() );

	cout<<"property1.getProperty()->setVariable( 1, area1.getDefinedVariable() );"<<endl;
	property1.getProperty()->setVariable( 1, area1.getDefinedVariable() );
	
	unsigned int uiPointsToEvalue = 2;
	
	unsigned int uiTimeNeeded = 1 + 2 * 5;

	//check the getTimeNeed() methode from cList
	cout<<"area1.getTimeNeed()"<<endl;
	if ( area1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			area1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cList
	cout<<"area1.getTimeNeed( 4 )"<<endl;
	if ( area1.getTimeNeed( 4 ) == 4 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 4 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			area1.getTimeNeed( 4 ) <<", but should be "<< 4 <<" . "<<endl;
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
	cVectorPosition vecPositionE2V2( 2 );
	vecPositionE2V2.setValue( 1, 2 );
	cVectorProperty vecPropertyColorSWV2( cTypeProperty::COLOR_GRAYSCALE );
	vecPropertyColorSWV2.setValue( 1, 2 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V2, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV2 );
	
	cEvaluePositionList evaluePositionList;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"area1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bool bObjectEvalued = area1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<"area1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = area1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<"area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<"area1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = area1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cArea with a global property list given"<<endl;
	
	cout<<"cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );
	
	list< pair< const cVectorPosition*, list<cVectorProperty> > >::iterator
		itrPositionProperties = liPointsToEvalue.begin();
	itrPositionProperties->second.push_back( vecPropertyLayer );
	itrPositionProperties++;
	itrPositionProperties->second.push_back( vecPropertyLayer );
	
	uiTimeNeeded = 1 + 2 * 5;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"area1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = area1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	itrElementProperties->second.push_back( vecPropertyLayer );
	itrElementProperties++;
	itrElementProperties->second.push_back( vecPropertyLayer );

	cout<<"area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cArea with the a subarea from 1 till 2 and 5 till 4"<<endl;

	cout<<"cVectorArea vecArea5t4;"<<endl;
	cVectorArea vecArea5t4;
	cout<<"vecArea5t4.setValue( 1, 5);"<<endl;
	vecArea5t4.setValue( 1, 5);
	cout<<"vecArea5t4.setValue( 2, 4);"<<endl;
	vecArea5t4.setValue( 2, 4);
	
	cout<<"area1.addSubarea( vecArea5t4 );"<<endl;
	area1.addSubarea( vecArea5t4 );
	
	uiPointsToEvalue = 4;
	
	//generate to evalue data
	cVectorProperty vecPropertyColorSWV5( cTypeProperty::COLOR_GRAYSCALE );
	vecPropertyColorSWV5.setValue( 1, 5 );
	cVectorProperty vecPropertyColorSWV4( cTypeProperty::COLOR_GRAYSCALE );
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

	uiTimeNeeded = 1 + uiPointsToEvalue * 5;

	//check the getTimeNeed() methode from cList
	cout<<"area1.getTimeNeed()"<<endl;
	if ( area1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			area1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}

	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"area1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = area1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<"area1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = area1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<"area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<"area1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = area1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cArea with the a subarea from 1 till 2, 5 till 4 and 7 till 10"<<endl;

	cout<<"cVectorArea vecArea7t10;"<<endl;
	cVectorArea vecArea7t10;
	cout<<"vecArea7t10.setValue( 1, 7);"<<endl;
	vecArea7t10.setValue( 1, 7);
	cout<<"vecArea7t10.setValue( 2, 10);"<<endl;
	vecArea7t10.setValue( 2, 10);
	
	cout<<"area1.addSubarea( vecArea7t10 );"<<endl;
	area1.addSubarea( vecArea7t10 );
	
	uiPointsToEvalue = 8;
	
	//generate to evalue data
	cVectorProperty vecPropertyColorSWV7( cTypeProperty::COLOR_GRAYSCALE );
	vecPropertyColorSWV7.setValue( 1, 7 );
	cVectorProperty vecPropertyColorSWV8( cTypeProperty::COLOR_GRAYSCALE );
	vecPropertyColorSWV8.setValue( 1, 8 );
	cVectorProperty vecPropertyColorSWV9( cTypeProperty::COLOR_GRAYSCALE );
	vecPropertyColorSWV9.setValue( 1, 9 );
	cVectorProperty vecPropertyColorSWV10( cTypeProperty::COLOR_GRAYSCALE );
	vecPropertyColorSWV10.setValue( 1, 10 );

	cVectorPosition vecPositionE2V5( 2 );
	vecPositionE2V5.setValue( 1, 7 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V5, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV7 );
	cVectorPosition vecPositionE2V6( 2 );
	vecPositionE2V6.setValue( 1, 8 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V6, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV8 );
	cVectorPosition vecPositionE2V7( 2 );
	vecPositionE2V7.setValue( 1, 9 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V7, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV9 );
	cVectorPosition vecPositionE2V8( 2 );
	vecPositionE2V8.setValue( 1, 10 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V8, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV10 );
	

	uiTimeNeeded = 1 + uiPointsToEvalue * 5;

	//check the getTimeNeed() methode from cList
	cout<<"area1.getTimeNeed()"<<endl;
	if ( area1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			area1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}

	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"area1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = area1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<"area1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = area1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	
	cout<<"area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<"area1.evalueObjectSimple( storeEvaluedElement );"<<endl;
	bObjectEvalued = area1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cArea with the a subarea from 1 till 2, 5 till 4, 7 till 10 and 9 till 11"<<endl;

	cout<<"cVectorArea vecArea9t11;"<<endl;
	cVectorArea vecArea9t11;
	cout<<"vecArea9t11.setValue( 1, 9);"<<endl;
	vecArea9t11.setValue( 1, 9);
	cout<<"vecArea9t11.setValue( 2, 11);"<<endl;
	vecArea9t11.setValue( 2, 11);
	
	cout<<"area1.addSubarea( vecArea9t11 );"<<endl;
	area1.addSubarea( vecArea9t11 );
	
	uiPointsToEvalue = 11;
	
	//generate to evalue data
	cVectorProperty vecPropertyColorSWV11( cTypeProperty::COLOR_GRAYSCALE );
	vecPropertyColorSWV11.setValue( 1, 11 );

	cVectorPosition vecPositionE2V9( 2 );
	vecPositionE2V9.setValue( 1, 9 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V9, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV9 );
	cVectorPosition vecPositionE2V10( 2 );
	vecPositionE2V10.setValue( 1, 10 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V10, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV10 );
	cVectorPosition vecPositionE2V11( 2 );
	vecPositionE2V11.setValue( 1, 11 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V11, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV11 );

	uiTimeNeeded = 1 + uiPointsToEvalue * 5;

	//check the getTimeNeed() methode from cList
	cout<<"area1.getTimeNeed()"<<endl;
	if ( area1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			area1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}

	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"area1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = area1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<"area1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = area1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV9 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV10 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV11 );
	
	cout<<"area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<"area1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = area1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cArea with the a subarea from 1 till 2, 5 till 4, 7 till 10, 9 till 11 and 8 till 9"<<endl;

	cout<<"cVectorArea vecArea8t9;"<<endl;
	cVectorArea vecArea8t9;
	cout<<"vecArea8t9.setValue( 1, 8);"<<endl;
	vecArea8t9.setValue( 1, 8);
	cout<<"vecArea8t9.setValue( 2, 9);"<<endl;
	vecArea8t9.setValue( 2, 9);
	
	cout<<"area1.addSubarea( vecArea8t9 );"<<endl;
	area1.addSubarea( vecArea8t9 );
	
	uiPointsToEvalue = 13;
	
	//generate to evalue data
	cVectorPosition vecPositionE2V12( 2 );
	vecPositionE2V12.setValue( 1, 8 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V12, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV8 );
	cVectorPosition vecPositionE2V13( 2 );
	vecPositionE2V13.setValue( 1, 9 );
	liPointsToEvalue.push_back( make_pair( &vecPositionE2V13, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSWV9 );

	uiTimeNeeded = 1 + uiPointsToEvalue * 5;

	//check the getTimeNeed() methode from cList
	cout<<"area1.getTimeNeed()"<<endl;
	if ( area1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			area1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}

	liVecProperties.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"area1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = area1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<"area1.evalueObjectSimple( evaluePositionList );"<<endl;
	bObjectEvalued = area1.evalueObjectSimple( evaluePositionList );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV8 );
	liFibElementsToEvalue.push_back( make_pair( &point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSWV9 );
	
	cout<<"area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<"area1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = area1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cArea for non existing object point 1"<<endl;
	
	uiPointsToEvalue = 0;
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"area1.evalueObject( evaluePositionList, 4,  liVecProperties );"<<endl;
	bObjectEvalued = area1.evalueObject( evaluePositionList, 4,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The area was correctly not evalued. "<<endl;
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
	cout<<"area1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = area1.evalueObject( evalueFibElementList, 4,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The area was correctly not evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cArea when returnvalue is false"<<endl;

	uiPointsToEvalue = 1;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	cout<<"area1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = area1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The area was correctly evalued. with result false "<<endl;
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
	cout<<"area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The area was correctly evalued. with result false "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cArea with differnt elements to evalue"<<endl;

	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"liCFibElementTyps.push_back( 'y' );"<<endl;
	liCFibElementTyps.push_back( 'y' );
	liVecProperties.clear();
	liFibElementsToEvalue.clear();
	uiPointsToEvalue = 13;
	for ( unsigned int uiEvaluesElement = 0;
			uiEvaluesElement < uiPointsToEvalue; uiEvaluesElement++ ){
		liFibElementsToEvalue.push_back(
			make_pair( &property1, list<cVectorProperty>() ) );
	}
	cout<<"area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<"liCFibElementTyps.push_back( 'a' );"<<endl;
	liCFibElementTyps.push_back( 'a' );
	uiPointsToEvalue = 1;
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( &area1, list<cVectorProperty>() ) );
	cout<<"area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<"liCFibElementTyps.push_back( 'a' );"<<endl;
	liCFibElementTyps.push_back( 'a' );
	cout<<"liCFibElementTyps.push_back( 'm' );"<<endl;
	liCFibElementTyps.push_back( 'm' );
	uiPointsToEvalue = 1;
	cout<<"area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = area1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The area was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing equal methods for areaelements"<<endl;

	cout<<endl<<"Creating areaobjects objects to compare: "<<endl<<endl;

	//area with a empty areavector
	cout<<"cVectorArea vecArea1;"<<endl;
	cVectorArea vecArea1;
	cout<<"cArea area1( vecArea1 );"<<endl;
	cArea area1( vecArea1 );

	cout<<"cVectorArea vecArea2;"<<endl;
	cVectorArea vecArea2;
	cout<<"cArea area2( vecArea2 );"<<endl;
	cArea area2( vecArea2 );

	//area with one changed subarea
	cout<<"cVectorArea vecAreaV1g4;"<<endl;
	cVectorArea vecAreaV1g4;
	cout<<"vecAreaV1g4.setValue( 1, 4);"<<endl;
	vecAreaV1g4.setValue( 1, 4);
	cout<<"cArea areaV1g4( vecAreaV1g4 );"<<endl;
	cArea areaV1g4( vecAreaV1g4 );

	cout<<"cVectorArea vecAreaV2g4;"<<endl;
	cVectorArea vecAreaV2g4;
	cout<<"vecAreaV2g4.setValue( 2, 4);"<<endl;
	vecAreaV2g4.setValue( 2, 4);
	cout<<"cArea areaV2g4( vecAreaV2g4 );"<<endl;
	cArea areaV2g4( vecAreaV2g4 );

	//area with two subareas
	cout<<"cArea areaE2E1V1g4E2V2g4( vecAreaV1g4 );"<<endl;
	cArea areaE2E1V1g4E2V2g4( vecAreaV1g4 );
	cout<<"areaE2E1V1g4E2V2g4.addSubarea( vecAreaV2g4 );"<<endl;
	areaE2E1V1g4E2V2g4.addSubarea( vecAreaV2g4 );
	
	cout<<"cArea areaE2E1V2g4E2V1g4( vecAreaV2g4 );"<<endl;
	cArea areaE2E1V2g4E2V1g4( vecAreaV2g4 );
	cout<<"areaE2E1V2g4E2V1g4.addSubarea( vecAreaV1g4 );"<<endl;
	areaE2E1V2g4E2V1g4.addSubarea( vecAreaV1g4 );

	//area with tree subareas
	cout<<"cArea area1E1V1g4E2V2g4E3V2g4( vecAreaV1g4 );"<<endl;
	cArea area1E1V1g4E2V2g4E3V2g4( vecAreaV1g4 );
	cout<<"area1E1V1g4E2V2g4E3V2g4.addSubarea( vecAreaV2g4 );"<<endl;
	area1E1V1g4E2V2g4E3V2g4.addSubarea( vecAreaV2g4 );
	cout<<"area1E1V1g4E2V2g4E3V2g4.addSubarea( vecAreaV2g4 );"<<endl;
	area1E1V1g4E2V2g4E3V2g4.addSubarea( vecAreaV2g4 );
	cout<<"area1E1V1g4E2V2g4E3V2g4.addSubarea( vecAreaV2g4 );"<<endl;
	area1E1V1g4E2V2g4E3V2g4.addSubarea( vecAreaV2g4 );
	
	//area with supperior element
	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea areaSup( vecArea1, NULL, &rootEmpty1 );"<<endl;
	cArea areaSup( vecArea1, NULL, &rootEmpty1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea areaSup( vecArea1, &rootEmpty1 );"<<endl;
	cArea areaSup( vecArea1, &rootEmpty1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//area in fib -element structur
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea areaNextPrev( vecArea1, &poinNext );"<<endl;
	cArea areaNextPrev( vecArea1, &poinNext );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinPrev;"<<endl;
	cPoint poinPrev;
	cout<<"cArea areaNextPrev( vecArea1, NULL, &poinPrev, &poinNext );"<<endl;
	cArea areaNextPrev( vecArea1, NULL, &poinPrev, &poinNext );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	cout<<"cPoint poinNext2;"<<endl;
	cPoint poinNext2;
	cout<<"cRoot root1;"<<flush<<endl;
	cRoot root1;
	
	cout<<"cTypeArea testTypeArea;"<<endl;
	cTypeArea testTypeArea;
	
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

	cout<<"root1.getDomains()->addDomain( testTypeArea, &vectorDomainE2 );"<<endl;
	root1.getDomains()->addDomain( testTypeArea, &vectorDomainE2 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea areaFull( vecArea1, &poinNext2, &root1 );"<<endl;
	cArea areaFull( vecArea1, &poinNext2, &root1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinPrev2;"<<endl;
	cPoint poinPrev2;
	cout<<"cArea areaFull( vecArea1, &root1, &poinPrev2, &poinNext2 );"<<endl;
	cArea areaFull( vecArea1, &root1, &poinPrev2, &poinNext2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//areas with a contained pointelement
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea areaPoint1( vecArea1, &point1 );"<<endl;
	cArea areaPoint1( vecArea1, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea areaPoint1( vecArea1, NULL, NULL, &point1 );"<<endl;
	cArea areaPoint1( vecArea1, NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"cVectorPosition vecPosition;"<<endl;
	cVectorPosition vecPosition;
	cout<<"cPoint point2( &vecPosition );"<<endl;
	cPoint point2( &vecPosition );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea areaPoint2( vecArea1, &point2 );"<<endl;
	cArea areaPoint2( vecArea1, &point2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea areaPoint2( vecArea1, NULL, NULL, &point2 );"<<endl;
	cArea areaPoint2( vecArea1, NULL, NULL, &point2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR



	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with area1
	cFibElement *actualObject = &area1;
	string szActualObjectName = "area1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, area1, "area1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, area2, "area2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV1g4, "areaV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV2g4, "areaV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V1g4E2V2g4, "areaE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V2g4E2V1g4, "areaE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1E1V1g4E2V2g4E3V2g4, "area1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaSup, "areaSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaNextPrev, "areaNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaFull, "areaFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint1, "areaPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint2, "areaPoint2", true );

	//compare with area2
	actualObject = &area2;
	szActualObjectName = "area2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, area1, "area1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, area2, "area2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV1g4, "areaV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV2g4, "areaV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V1g4E2V2g4, "areaE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V2g4E2V1g4, "areaE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1E1V1g4E2V2g4E3V2g4, "area1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaSup, "areaSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaNextPrev, "areaNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaFull, "areaFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint1, "areaPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint2, "areaPoint2", true );

	//compare with areaV1g4
	actualObject = &areaV1g4;
	szActualObjectName = "areaV1g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1, "area1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area2, "area2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaV1g4, "areaV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV2g4, "areaV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V1g4E2V2g4, "areaE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V2g4E2V1g4, "areaE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1E1V1g4E2V2g4E3V2g4, "area1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaSup, "areaSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaNextPrev, "areaNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaFull, "areaFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint1, "areaPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint2, "areaPoint2" );

	//compare with areaV2g4
	actualObject = &areaV2g4;
	szActualObjectName = "areaV2g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1, "area1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area2, "area2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV1g4, "areaV1g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaV2g4, "areaV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V1g4E2V2g4, "areaE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V2g4E2V1g4, "areaE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1E1V1g4E2V2g4E3V2g4, "area1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaSup, "areaSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaNextPrev, "areaNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaFull, "areaFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint1, "areaPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint2, "areaPoint2" );

	//compare with areaE2E1V1g4E2V2g4
	actualObject = &areaE2E1V1g4E2V2g4;
	szActualObjectName = "areaE2E1V1g4E2V2g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1, "area1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area2, "area2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV1g4, "areaV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV2g4, "areaV2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaE2E1V1g4E2V2g4, "areaE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V2g4E2V1g4, "areaE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1E1V1g4E2V2g4E3V2g4, "area1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaSup, "areaSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaNextPrev, "areaNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaFull, "areaFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint1, "areaPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint2, "areaPoint2" );

	//compare with areaE2E1V2g4E2V1g4
	actualObject = &areaE2E1V2g4E2V1g4;
	szActualObjectName = "areaE2E1V2g4E2V1g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1, "area1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area2, "area2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV1g4, "areaV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV2g4, "areaV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V1g4E2V2g4, "areaE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaE2E1V2g4E2V1g4, "areaE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1E1V1g4E2V2g4E3V2g4, "area1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaSup, "areaSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaNextPrev, "areaNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaFull, "areaFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint1, "areaPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint2, "areaPoint2" );

	//compare with area1E1V1g4E2V2g4E3V2g4
	actualObject = &area1E1V1g4E2V2g4E3V2g4;
	szActualObjectName = "area1E1V1g4E2V2g4E3V2g4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1, "area1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area2, "area2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV1g4, "areaV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV2g4, "areaV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V1g4E2V2g4, "areaE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V2g4E2V1g4, "areaE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, area1E1V1g4E2V2g4E3V2g4, "area1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaSup, "areaSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaNextPrev, "areaNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaFull, "areaFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint1, "areaPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint2, "areaPoint2" );

	//compare with areaSup
	actualObject = &areaSup;
	szActualObjectName = "areaSup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, area1, "area1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, area2, "area2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV1g4, "areaV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV2g4, "areaV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V1g4E2V2g4, "areaE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V2g4E2V1g4, "areaE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1E1V1g4E2V2g4E3V2g4, "area1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaSup, "areaSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaNextPrev, "areaNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaFull, "areaFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint1, "areaPoint1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint2, "areaPoint2", true );

	//compare with areaNextPrev
	actualObject = &areaNextPrev;
	szActualObjectName = "areaNextPrev";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1, "area1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area2, "area2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV1g4, "areaV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV2g4, "areaV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V1g4E2V2g4, "areaE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V2g4E2V1g4, "areaE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1E1V1g4E2V2g4E3V2g4, "area1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaSup, "areaSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaNextPrev, "areaNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaFull, "areaFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaPoint1, "areaPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint2, "areaPoint2", true );

	//compare with areaFull
	actualObject = &areaFull;
	szActualObjectName = "areaFull";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1, "area1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area2, "area2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV1g4, "areaV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV2g4, "areaV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V1g4E2V2g4, "areaE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V2g4E2V1g4, "areaE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1E1V1g4E2V2g4E3V2g4, "area1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaSup, "areaSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaNextPrev, "areaNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaFull, "areaFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaPoint1, "areaPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint2, "areaPoint2", true );

	//compare with areaPoint1
	actualObject = &areaPoint1;
	szActualObjectName = "areaPoint1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1, "area1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area2, "area2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV1g4, "areaV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV2g4, "areaV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V1g4E2V2g4, "areaE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V2g4E2V1g4, "areaE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1E1V1g4E2V2g4E3V2g4, "area1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaSup, "areaSup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaNextPrev, "areaNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaFull, "areaFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaPoint1, "areaPoint1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint2, "areaPoint2", true );

	//compare with areaPoint2
	actualObject = &areaPoint2;
	szActualObjectName = "areaPoint2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1, "area1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area2, "area2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV1g4, "areaV1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaV2g4, "areaV2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V1g4E2V2g4, "areaE2E1V1g4E2V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaE2E1V2g4E2V1g4, "areaE2E1V2g4E2V1g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, area1E1V1g4E2V2g4E3V2g4, "area1E1V1g4E2V2g4E3V2g4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaSup, "areaSup", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaNextPrev, "areaNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaFull, "areaFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, areaPoint1, "areaPoint1", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, areaPoint2, "areaPoint2" );


	return iReturn;
}


/**
 * This method tests the equal() method of two given fib -objects which are
 * equal.
 * It also compares the superior, next and previous fib -element areaers.
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
	
	//check the getNextFibElement() methode from cArea
	if ( const_cast<cFibElement*>(&fibObject1)->getNextFibElement() ==
			const_cast<cFibElement*>(&fibObject2)->getNextFibElement() ){
	
		cout<<"The next/ main fib -elementpointer for the areaelement are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -elementpointer for the areaelement are not equal."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cArea
	if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) ==
			const_cast<cFibElement*>(&fibObject2)->getFibElement( -1 ) ){
	
		cout<<"The previous fib -elementpointer for the areaelement are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the areaelement are not equal."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cArea
	if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() ==
			const_cast<cFibElement*>(&fibObject2)->getSuperiorFibElement() ){
	
		cout<<"The superior fib -elementpointer for the areaelement are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the areaelement are not equal."<<endl;
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
 * This method tests the copy methods and copyconstructor of the cArea class.
 *
 * methods tested:
 * 	- cArea( const cArea &areaElement );
 * 	- cFibElement *clone( ) const;
 * 	- cArea *copy( const unsignedIntFib iObjectArea=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementArea=0 ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a empty cArea"<<endl;

	cout<<"cVectorArea vecArea1;"<<endl;
	cVectorArea vecArea1;
	cout<<"cArea areaEmpty( vecArea1 );"<<endl;
	cArea areaEmpty( vecArea1 );

	cout<<"cArea areaEmptyCopyConstruct( areaEmpty );"<<endl;
	cArea areaEmptyCopyConstruct( areaEmpty );

	iReturn += testCompareTwoEqualObjectsStructur( areaEmptyCopyConstruct, "areaEmptyCopyConstruct", areaEmpty, "areaEmpty" );

	cout<<"cFibElement * pAreaEmptyClone = areaEmpty.clone();"<<endl;
	cFibElement * pAreaEmptyClone = areaEmpty.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pAreaEmptyClone, "pAreaEmptyClone", areaEmpty, "areaEmpty" );
	delete pAreaEmptyClone;

	cout<<"cFibElement * pAreaEmptyCopy = areaEmpty.copy();"<<endl;
	cFibElement * pAreaEmptyCopy = areaEmpty.copy();

	iReturn += testCompareTwoEqualObjectsStructur( *pAreaEmptyCopy, "pAreaEmptyCopy", areaEmpty, "areaEmpty" );
	delete pAreaEmptyCopy;

	cout<<"cFibElement * pAreaEmptyCopyElement = areaEmpty.copyElement();"<<endl;
	cFibElement * pAreaEmptyCopyElement = areaEmpty.copyElement();

	iReturn += testCompareTwoEqualObjectsStructur( *pAreaEmptyCopyElement, "pAreaEmptyCopyElement", areaEmpty, "areaEmpty" );
	delete pAreaEmptyCopyElement;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying for a other object or elementpoint"<<endl;

	cout<<"cFibElement * pAreaEmptyNoCopy = areaEmpty.copy( 1 );"<<endl;
	cFibElement * pAreaEmptyNoCopy = areaEmpty.copy( 1 );

	if ( pAreaEmptyNoCopy == NULL ){
	
		cout<<"The cArea was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cArea was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pAreaEmptyNoCopy;
	}

	cout<<"cFibElement * pAreaEmptyNoCopyElement = areaEmpty.copyElement( 'a', 2 );"<<endl;
	cFibElement * pAreaEmptyNoCopyElement = areaEmpty.copyElement( 'a', 2 );

	if ( pAreaEmptyNoCopyElement == NULL ){
	
		cout<<"The cArea -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cArea -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pAreaEmptyNoCopyElement;
	}

	cout<<"pAreaEmptyNoCopyElement = areaEmpty.copyElement( 'u', 2 );"<<endl;
	pAreaEmptyNoCopyElement = areaEmpty.copyElement( 'u', 2 );

	if ( pAreaEmptyNoCopyElement == NULL ){
	
		cout<<"The cArea -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cArea -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pAreaEmptyNoCopyElement;
	}

	cout<<"pAreaEmptyNoCopyElement = areaEmpty.copyElement( 'r', 1 );"<<endl;
	pAreaEmptyNoCopyElement = areaEmpty.copyElement( 'r', 1 );

	if ( pAreaEmptyNoCopyElement == NULL ){
	
		cout<<"The cArea -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cArea -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pAreaEmptyNoCopyElement;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cArea with all members set"<<endl;

	//area in fib -element structur
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;

	cout<<"cRoot rootD2;"<<flush<<endl;
	cRoot rootD2;
	
	cout<<"cTypeArea testTypeArea;"<<endl;
	cTypeArea testTypeArea;
	
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

	cout<<"rootD2.getDomains()->addDomain( testTypeArea, &vectorDomainD2 );"<<endl;
	rootD2.getDomains()->addDomain( testTypeArea, &vectorDomainD2 );

	cout<<"cVectorArea vecArea2;"<<endl;
	cVectorArea vecArea2;
	cout<<"vecArea2.setValue( 1, 1 );"<<endl;
	vecArea2.setValue( 1, 1 );
	cout<<"vecArea2.setValue( 2, 2 );"<<endl;
	vecArea2.setValue( 2, 2 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea area2E2( vecArea2, &poinNext, &rootD2 );"<<endl;
	cArea area2E2( vecArea2, &poinNext, &rootD2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinPrev;"<<endl;
	cPoint poinPrev;
	cout<<"cArea area2E2( vecArea2, &rootD2, &poinPrev, &poinNext );"<<endl;
	cArea area2E2( vecArea2, &rootD2, &poinPrev, &poinNext );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"cArea area2E2CopyConstruct( area2E2 );"<<endl;
	cArea area2E2CopyConstruct( area2E2 );

	if ( area2E2CopyConstruct.equalElement( area2E2 ) ){

		cout<<"The area2E2CopyConstruct fib -element is equal to area2E2. "<<endl;
	}else{
		cerr<<"Error: The area2E2CopyConstruct fib -element is not equal to area2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( area2E2CopyConstruct );

	cout<<"cFibElement * pArea2E2Copy = area2E2.copy();"<<endl;
	cFibElement * pArea2E2Copy = area2E2.copy();
	iReturn += testCompareTwoEqualObjects( *pArea2E2Copy, "pArea2E2Copy", area2E2, "area2E2" );
	//check the getFibElement() methode from cArea
	if ( NULL == pArea2E2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous fib -elementpointer for the areaelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the areaelement is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cArea
	if ( NULL == pArea2E2Copy->getSuperiorFibElement() ){
	
		cout<<"The superior fib -elementpointer for the areaelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the areaelement is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( pArea2E2Copy );

	cout<<"cFibElement * pArea2E2CopyElement = area2E2.copyElement( 'u', 1 );"<<endl;
	cFibElement * pArea2E2CopyElement = area2E2.copyElement( 'u', 1 );

	if ( pArea2E2CopyElement->equalElement( area2E2 ) ){
	
		cout<<"The pArea2E2CopyElement fib -element is equal to area2E2. "<<endl;
	}else{
		cerr<<"Error: The pArea2E2CopyElement fib -element is not equal to area2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pArea2E2CopyElement );
	delete pArea2E2CopyElement;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a limb with more then one areaelement and pointelement"<<endl;

	//a limb with more then one areaelement and pointelement
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea area3( vecArea2, &point1 );"<<endl;
	cArea area3( vecArea2, &point1 );
	cout<<"cVectorArea vecArea3;"<<endl;
	cVectorArea vecArea3;
	cout<<"cArea area1Obj2( vecArea3, &area3 );"<<endl;
	cArea area1Obj2( vecArea3, &area3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea area3( vecArea2, NULL, NULL, &point1 );"<<endl;
	cArea area3( vecArea2, NULL, NULL, &point1 );
	cout<<"cVectorArea vecArea3;"<<endl;
	cVectorArea vecArea3;
	cout<<"cArea area1Obj2( vecArea3, NULL, NULL, &area3 );"<<endl;
	cArea area1Obj2( vecArea3, NULL, NULL, &area3 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	cout<<endl<<"cArea area1Obj2CopyConstruct( area1Obj2 );"<<endl;
	cArea area1Obj2CopyConstruct( area1Obj2 );

	if ( area1Obj2CopyConstruct.equalElement( area1Obj2 ) ){
	
		cout<<"The area1Obj2CopyConstruct fib -element is equal to area1Obj2. "<<endl;
	}else{
		cerr<<"Error: The area1Obj2CopyConstruct fib -element is not equal to area1Obj2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( area1Obj2CopyConstruct );

	cout<<"cFibElement * pArea1ColorSwO2LayerO1CopyConstructCopy = area1Obj2CopyConstruct.copy();"<<endl;
	cFibElement * area1Obj2Copy =
		area1Obj2.copy();

	iReturn += testCompareTwoEqualObjects(
		*area1Obj2Copy, "area1Obj2Copy",
		area1Obj2, "area1Obj2" );
	//check the getFibElement() methode from cArea
	if ( NULL == area1Obj2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous fib -elementpointer for the areaelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the areaelement is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cArea
	if ( area1Obj2Copy->getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -elementpointer for the areaelement is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the areaelement is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( area1Obj2Copy );

	cout<<"cFibElement * pArea1Obj2 = area1Obj2.copyElement();"<<endl;
	cFibElement * pArea1Obj2 = area1Obj2.copyElement();

	if ( pArea1Obj2->equalElement( area1Obj2 ) ){
	
		cout<<"The pArea1Obj2 fib -element is equal to area1Obj2. "<<endl;
	}else{
		cerr<<"Error: The pArea1Obj2 fib -element is not equal to area1Obj2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pArea1Obj2 );
	delete pArea1Obj2;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cArea with more than one subarea"<<endl;

	cout<<"cArea areaSa3( vecArea1 );"<<endl;
	cArea areaSa3( vecArea1 );
	cout<<"areaSa3.addSubarea( vecArea2 );"<<endl;
	areaSa3.addSubarea( vecArea2 );
	
	cout<<"cVectorArea vecArea4;"<<endl;
	cVectorArea vecArea4;
	cout<<"vecArea4.setValue( 1, 2 );"<<endl;
	vecArea4.setValue( 1, 2 );
	cout<<"vecArea4.setValue( 2, 3 );"<<endl;
	vecArea4.setValue( 2, 3 );
	cout<<"areaSa3.addSubarea( vecArea4 );"<<endl;
	areaSa3.addSubarea( vecArea4 );

	cout<<"cArea areaSa3CopyConstruct( areaSa3 );"<<endl;
	cArea areaSa3CopyConstruct( areaSa3 );

	iReturn += testCompareTwoEqualObjectsStructur( areaSa3CopyConstruct, "areaSa3CopyConstruct", areaSa3, "areaSa3" );

	cout<<"cFibElement * pAreaSa3Clone = areaSa3.clone();"<<endl;
	cFibElement * pAreaSa3Clone = areaSa3.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pAreaSa3Clone, "pAreaSa3Clone", areaSa3, "areaSa3" );
	delete pAreaSa3Clone;

	cout<<"cFibElement * pAreaSa3Copy = areaSa3.copy();"<<endl;
	cFibElement * pAreaSa3Copy = areaSa3.copy();

	iReturn += testCompareTwoEqualObjectsStructur( *pAreaSa3Copy, "pAreaSa3Copy", areaSa3, "areaSa3" );
	delete pAreaSa3Copy;

	cout<<"cFibElement * pAreaSa3CopyElement = areaSa3.copyElement();"<<endl;
	cFibElement * pAreaSa3CopyElement = areaSa3.copyElement();

	iReturn += testCompareTwoEqualObjectsStructur( *pAreaSa3CopyElement, "pAreaSa3CopyElement", areaSa3, "areaSa3" );
	delete pAreaSa3CopyElement;


	return iReturn;
}



/**
 * This method tests a in the xml -format stored cFibVector.
 *
 * @param szFilename the name of the file wher the cFibVector is stored
 * @param uiDefinedVariableValue the number of the defined variable
 * @param uiSubAreas the number of subareas in the area
 * @param vecElementType a vector with the typs of the vectorelements
 * 	(w=value; v=variable)
 * @param vecValues the values of the vectorelements (the on even indexes
 * 	are the lower bounds and on add the upperbounds )
 * @return the number of errors occured in the test
 */
int testXmlArea( const string szFilename, unsigned int uiDefinedVariableValue,
		unsigned int uiSubAreas, vector<char> vecElementType,
		vector<long> vecValues ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cArea:"<<endl;
	
	TiXmlDocument xmlDocVectorArea( szFilename );
	bool loadOkay = xmlDocVectorArea.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocVectorArea );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();
		
		const string szAreaElementName = "area";
		if ( szElementName == szAreaElementName ){
			cout<<"The root element is correctly named \""<< szAreaElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szAreaElementName <<"\"."<<endl;
			iReturn++;
		}
		
		const char * szDefinedVariableValue = pXmlElement->Attribute( "define_variable" );
		
		if ( szDefinedVariableValue == NULL ){
			cerr<<"Error: The area has no defined variable."<<endl;
			iReturn++;
		}else{
			unsigned long uiDefinedVariableValueStored = atol( szDefinedVariableValue );
			 if ( uiDefinedVariableValueStored == uiDefinedVariableValue ) {
				cout<<"The defined variable of the area is correctly \""<< uiDefinedVariableValue <<"\". "<<endl;
			}else{
				cerr<<"Error: The defined variable of the area is \""<< szDefinedVariableValue
					<<"\", but should be \""<< uiDefinedVariableValue <<"\"."<<endl;
				iReturn++;
			}
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	xmlHandleRoot = TiXmlHandle( pXmlElement );
	TiXmlElement * pXmlSubarea = xmlHandleRoot.FirstChild().Element();
	
	if ( uiSubAreas == 0 ){
	
		if ( ! pXmlSubarea ){
			cout<<"The area contains correctly no vector. "<<endl;
		
		}else{
			cerr<<"Error: The area contains vector, but it shouldn't."<<endl;
			iReturn++;
		}
		return iReturn;
	}//else
	
	unsigned int uiLoadedSubAreas = 0;
	for( ; pXmlSubarea; pXmlSubarea = pXmlSubarea->NextSiblingElement() ){
		uiLoadedSubAreas++;
		
		if ( pXmlSubarea ) {
			string szElementName = pXmlSubarea->Value();
	
			if ( szElementName == "vector" ){
				cout<<"The root element is correctly named \"vector\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"vector\"."<<endl;
				iReturn++;
			}
			const char * szVectorXmlType = pXmlSubarea->Attribute( "type" );
			
			if ( szVectorXmlType == NULL ){
				cerr<<"Error: The vector has no type."<<endl;
				iReturn++;
			}else if ( string("subarea") == szVectorXmlType ) {
				cout<<"The type of the vector is correctly \"subarea\". "<<endl;
			}else{
				cerr<<"Error: The type of the vector is \""<< szVectorXmlType
					<<"\", but should be \"subarea\"."<<endl;
				iReturn++;
			}
	
		}else{// pXmlElement == NULL
			cerr<<"Error: No vector handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
			return iReturn;
		}
		
		TiXmlHandle xmlHandleVectorRoot = TiXmlHandle( pXmlSubarea );
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
				(uiLoadedSubAreas - 1) * 2 + iNumberOfElement - 1;
			
			//the elementtype the actual element should have
			string szTargetElementType( "non" );
			
			if ( iNumberOfElement < 1 ){
				cerr<<"Error: Ther couldn't be a 0'th vectorelement."<<endl;
				iReturn++;
			}else if ( 2 < iNumberOfElement ){
				cerr<<"Error: Ther couldn't be a "<< iNumberOfElement <<
					"'th vectorelement, because a subarea has yust "<<
					2 <<" elements."<<endl;
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
				if ( (1 <= iNumberOfElement) && ( iNumberOfElement <= 2 ) ){
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
				if ( (1 <= iNumberOfElement) && ( iNumberOfElement <= 2 ) ){
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
	}
	
	if ( uiSubAreas != uiLoadedSubAreas ){
		cerr<<"Error: "<< uiLoadedSubAreas <<" subareas loded, but ther schould be "<<
			uiSubAreas <<" subareas."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the storeXml() method of the cArea class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an area with an empty subarea"<<endl;

	cout<<"cVectorArea vecArea1;"<<endl;
	cVectorArea vecArea1;
	cout<<"cArea area1( vecArea1 );"<<endl;
	cArea area1( vecArea1 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlAreaFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "area1.xml" );
	ofstream * pFileVectorPostion = new ofstream( szXmlAreaFileName );
	
	bool bStoreSuccesfull = area1.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cArea was stored successfull to the file \""<< szXmlAreaFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cArea to the file \""<< szXmlAreaFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	vector<char> vecElementTypePosition( 8, 'w' );
	vector<long> vecValuesPosition( 8, 0 );
	
	iReturn += testXmlArea( szXmlAreaFileName, 0,
		1, vecElementTypePosition, vecValuesPosition );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an area with two subareas"<<endl;

	cout<<"cVectorArea vecArea2;"<<endl;
	cVectorArea vecArea2;
	cout<<"vecArea2.setValue( 1, 3 );"<<endl;
	vecArea2.setValue( 1, 3 );
	cout<<"vecArea2.setValue( 2, 5 );"<<endl;
	vecArea2.setValue( 2, 5 );
	cout<<"area1.addSubarea( vecArea2 );"<<endl;
	area1.addSubarea( vecArea2 );
	
	cout<<"area1.getDefinedVariable()->setIntegerValue( 3 );"<<endl;
	area1.getDefinedVariable()->setIntegerValue( 3 );
	
	szFileNameBuffer[0] = 0;
	szXmlAreaFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "areaE2.xml" );
	pFileVectorPostion = new ofstream( szXmlAreaFileName );
	
	bStoreSuccesfull = area1.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cArea was stored successfull to the file \""<< szXmlAreaFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cArea to the file \""<< szXmlAreaFileName <<"\" failed."<<endl;
		iReturn++;
	}
	vecValuesPosition[2] = 3;
	vecValuesPosition[3] = 5;
	
	iReturn += testXmlArea( szXmlAreaFileName, 3,
		2, vecElementTypePosition, vecValuesPosition );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an area with four subareas"<<endl;

	cout<<"cVectorArea vecArea3;"<<endl;
	cVectorArea vecArea3;
	cout<<"vecArea3.setValue( 1, 5 );"<<endl;
	vecArea3.setValue( 1, 5 );
	cout<<"vecArea3.setValue( 2, 3 );"<<endl;
	vecArea3.setValue( 2, 3 );
	vecValuesPosition[4] = 5;
	vecValuesPosition[5] = 3;
	cout<<"area1.addSubarea( vecArea3 );"<<endl;
	area1.addSubarea( vecArea3 );
	
	cout<<"cVectorArea vecArea4;"<<endl;
	cVectorArea vecArea4;
	cout<<"vecArea4.setValue( 1, 10 );"<<endl;
	vecArea4.setValue( 1, 10 );
	cout<<"vecArea4.setValue( 2, 8 );"<<endl;
	vecArea4.setValue( 2, 8 );
	vecValuesPosition[6] = 10;
	vecValuesPosition[7] = 8;
	cout<<"area1.addSubarea( vecArea4 );"<<endl;
	area1.addSubarea( vecArea4 );
	
	szFileNameBuffer[0] = 0;
	szXmlAreaFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "areaE4.xml" );
	pFileVectorPostion = new ofstream( szXmlAreaFileName );
	
	bStoreSuccesfull = area1.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cArea was stored successfull to the file \""<< szXmlAreaFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cArea to the file \""<< szXmlAreaFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlArea( szXmlAreaFileName, 3,
		4, vecElementTypePosition, vecValuesPosition );

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

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method one subarea"<<endl;

	cout<<"cPoint point1;"<<flush<<endl;
	cPoint point1;

	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	
	cout<<"cVectorArea vecArea1;"<<endl;
	cVectorArea vecArea1;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea area1( vecArea1, &point1, &root );"<<endl;
	cArea area1( vecArea1, &point1, &root );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea area1( vecArea1, &root, &root, &point1 );"<<endl;
	cArea area1( vecArea1, &root, &root, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//test get compressed size
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	unsigned int uiCompressedSize = 4 + 8 + 2 * 17 + 5;
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	unsigned int uiCompressedSize = 4 + 8 + 8 + 2 * 17 + 5;
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	if ( (unsigned int)(area1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			area1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "area1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bool bStoreSuccesfull = area1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	const char cArea1[] = { (char)0x18, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x80, (char)0x04  };
	iReturn += compareBytsWithFile( szFileNameBuffer, cArea1, 7 );
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	const char cArea1[] = { (char)0x18, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x80, (char)0x04  };
	iReturn += compareBytsWithFile( szFileNameBuffer, cArea1, 8 );
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with changed values"<<endl;

	cout<<"area1.getDefinedVariable()->setIntegerValue( 1 );"<<endl;
	area1.getDefinedVariable()->setIntegerValue( 1 );
	
	cout<<"area1.getSubarea( 1 )->setValue( 1, 2 );"<<endl;
	area1.getSubarea( 1 )->setValue( 1, 2 );
	cout<<"area1.getSubarea( 1 )->setValue( 2, 3 );"<<endl;
	area1.getSubarea( 1 )->setValue( 2, 3 );
	
	//test get compressed size
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	uiCompressedSize = 4 + 8 + 2 * 17 + 5;
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	uiCompressedSize = 4 + 8 + 8 + 2 * 17 + 5;
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	if ( (unsigned int)(area1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			area1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "areaChV.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = area1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	const char szAreaChV[] = { (char)0x18, (char)0x40, (char)0x00, (char)0xC0, (char)0x00, (char)0x80, (char)0x04  };
	iReturn += compareBytsWithFile( szFileNameBuffer, szAreaChV, 7 );
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	const char szAreaChV[] = { (char)0x18, (char)0x10, (char)0x00, (char)0x00, (char)0xC0, (char)0x00, (char)0x80, (char)0x04  };
	iReturn += compareBytsWithFile( szFileNameBuffer, szAreaChV, 8 );
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with given domains"<<endl;

	cout<<"cTypeArea testTypeArea;"<<endl;
	cTypeArea testTypeArea;
	
	//create vector domain with two elements
	cout<<"vector<cDomain*> vecDomainsE2( 2 );"<<endl;
	vector<cDomain*> vecDomainsE2( 2 );
	cout<<"vecDomainsE2[ 0 ] = new cDomainNaturalNumberBit( 7 );"<<endl;
	vecDomainsE2[ 0 ] = new cDomainNaturalNumberBit( 7 );
	cout<<"vecDomainsE2[ 1 ] = new cDomainNaturalNumberBit( 15 );"<<endl;
	vecDomainsE2[ 1 ] = new cDomainNaturalNumberBit( 15 );
	cout<<"cDomainVector vecDomainSubareaE2( vecDomainsE2 );"<<endl;
	cDomainVector vecDomainSubareaE2( vecDomainsE2 );
	delete vecDomainsE2[ 0 ];
	delete vecDomainsE2[ 1 ];
	
	cout<<"vecDomainsE2[ 0 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomainsE2[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"vecDomainsE2[ 1 ] = &vecDomainSubareaE2;"<<endl;
	vecDomainsE2[ 1 ] = &vecDomainSubareaE2;
	cout<<"cDomainVector vectorDomainAreaE2( vecDomainsE2 );"<<endl;
	cDomainVector vectorDomainAreaE2( vecDomainsE2 );
	delete vecDomainsE2[ 0 ];
	
	cout<<"root.getDomains()->addDomain( testTypeArea, &vectorDomainAreaE2 );"<<endl;
	root.getDomains()->addDomain( testTypeArea, &vectorDomainAreaE2 );
	
	cout<<"cTypeVariable testTypeVariable;"<<endl;
	cTypeVariable testTypeVariable;
	
	cDomainNaturalNumberBit naturalNumberDomainB4( 4 );
	
	cout<<"root.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB4 );"<<endl;
	root.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB4 );

	cout<<"area1.getDefinedVariable()->setIntegerValue( 2 );"<<endl;
	area1.getDefinedVariable()->setIntegerValue( 2 );
	
	cout<<"area1.getSubarea( 1 )->setValue( 1, 5 );"<<endl;
	area1.getSubarea( 1 )->setValue( 1, 5 );
	cout<<"area1.getSubarea( 1 )->setValue( 2, 2 );"<<endl;
	area1.getSubarea( 1 )->setValue( 2, 2 );
	
	//test get compressed size
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	uiCompressedSize = 4 + 4 + 8 + 16 + 5;
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	uiCompressedSize = 4 + 4 + 4 + 8 + 16 + 5;
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	if ( (unsigned int)(area1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			area1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "areaDom.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = area1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	const char szAreaDom[] = { (char)0x18, (char)0x0A, (char)0x04, (char)0x00, (char)0x12 };
	iReturn += compareBytsWithFile( szFileNameBuffer, szAreaDom, 5 );
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	const char szAreaDom[] = { (char)0x28, (char)0x1A, (char)0x40, (char)0x00, (char)0x20, (char)0x01 };
	iReturn += compareBytsWithFile( szFileNameBuffer, szAreaDom, 6 );
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with 2 subareas"<<endl;

	cout<<"cDomainNaturalNumberBit naturalNumberDomainB8( 8 );"<<endl;
	cDomainNaturalNumberBit naturalNumberDomainB8( 8 );
	
	cout<<"root.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB8 );"<<endl;
	root.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB8 );

	cout<<"cVectorArea vecArea2;"<<endl;
	cVectorArea vecArea2;
	cout<<"vecArea2.setValue( 1, 2 );"<<endl;
	vecArea2.setValue( 1, 2 );
	cout<<"vecArea2.setValue( 2, 5 );"<<endl;
	vecArea2.setValue( 2, 5 );
	
	cout<<"area1.addSubarea( vecArea2 );"<<endl;
	area1.addSubarea( vecArea2 );
	
	cout<<"area1.getSubarea( 1 )->setValue( 1, 1 );"<<endl;
	area1.getSubarea( 1 )->setValue( 1, 1 );
	cout<<"area1.getSubarea( 1 )->setValue( 2, 1 );"<<endl;
	area1.getSubarea( 1 )->setValue( 2, 1 );
	
	//test get compressed size
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	uiCompressedSize = 4 + 4 + 2 * (8 + 16) + 5;
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	uiCompressedSize = 4 + 8 + 4 + 2 * (8 + 16) + 5;
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	if ( (unsigned int)(area1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			area1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "areaE2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = area1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	const char szAreaE2[] = { (char)0x28, (char)0x02, (char)0x02, (char)0x00, (char)0x04, (char)0x0A, (char)0x00, (char)0x12 };
	iReturn += compareBytsWithFile( szFileNameBuffer, szAreaE2, 8 );
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	const char szAreaE2[] = { (char)0x28, (char)0x20, (char)0x02, (char)0x02, (char)0x00, (char)0x04, (char)0x0A, (char)0x00, (char)0x12 };
	iReturn += compareBytsWithFile( szFileNameBuffer, szAreaE2, 9 );
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with 15 subareas"<<endl;
	
	unsigned int uiSubareas = 15;
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	uiCompressedSize = 4 + 4 + uiSubareas * (8 + 16) + 5;
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	uiCompressedSize = 4 + 8 + 4 + uiSubareas * (8 + 16) + 5;
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	
	char szAreaE15[ uiCompressedSize / 8 + 1 ];
	
	cout<<"vecArea2.setValue( 1, 1 );"<<endl;
	vecArea2.setValue( 1, 1 );
	cout<<"vecArea2.setValue( 2, 1 );"<<endl;
	vecArea2.setValue( 2, 1 );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root1;"<<flush<<endl;
	cRoot root1;
	cout<<"root1.getDomains()->addDomain( testTypeArea, &vectorDomainAreaE2 );"<<endl;
	root1.getDomains()->addDomain( testTypeArea, &vectorDomainAreaE2 );
	cout<<"root1.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB8 );"<<endl;
	root1.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB8 );
	cout<<"cArea area15( vecArea2, &point1, &root1 );"<<endl;
	cArea area15( vecArea2, &point1, &root1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea area15( vecArea2, &root, &root, &point1 );"<<endl;
	cArea area15( vecArea2, &root, &root, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"area15.getDefinedVariable()->setIntegerValue( 3 );"<<endl;
	area15.getDefinedVariable()->setIntegerValue( 3 );
	
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	szAreaE15[ 0 ] = (char)0xF8;
	unsigned int uiActualByte = 1;
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	szAreaE15[ 0 ] = (char)0x38;
	szAreaE15[ 1 ] = (char)0xF0;
	unsigned int uiActualByte = 2;
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES

	szAreaE15[ uiActualByte ] = (char)0x02;
	uiActualByte++;
	szAreaE15[ uiActualByte ] = (char)0x02;
	uiActualByte++;
	szAreaE15[ uiActualByte ] = (char)0x00;
	uiActualByte++;
	
	for ( unsigned int uiSubarea = 2; uiSubarea <= uiSubareas; uiSubarea++ ){
		
		cout<<"vecArea2.setValue( 1, "<< uiSubarea <<" );"<<endl;
		vecArea2.setValue( 1, uiSubarea );
		cout<<"vecArea2.setValue( 2, "<< uiSubarea <<" );"<<endl;
		vecArea2.setValue( 2, uiSubarea );
		cout<<"area15.addSubarea( vecArea2 );"<<endl;
		area15.addSubarea( vecArea2 );

		szAreaE15[ uiActualByte ] = (char)(uiSubarea * 2);
		uiActualByte++;
		szAreaE15[ uiActualByte ] = (char)(uiSubarea * 2);
		uiActualByte++;
		szAreaE15[ uiActualByte ] = (char)0x00;
		uiActualByte++;
	}
	//point
	szAreaE15[ uiActualByte ] = (char)0x12;
	uiActualByte++;

	//test get compressed size
	if ( (unsigned int)(area15.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			area1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "areaE15.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = area15.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	iReturn += compareBytsWithFile( szFileNameBuffer, szAreaE15, (uiCompressedSize / 8 + 1) );


	
	

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with 16 subareas"<<endl;
	
	uiSubareas = 16;
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	uiCompressedSize = 4 + 64 + uiSubareas * (8 + 16) + 5;
#else //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	uiCompressedSize = 4 + 4 + 64 + uiSubareas * (8 + 16) + 5;
#endif //FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	
	char szAreaE16[ uiCompressedSize / 8 + 1 ];
	
	cout<<"vecArea2.setValue( 1, 1 );"<<endl;
	vecArea2.setValue( 1, 1 );
	cout<<"vecArea2.setValue( 2, 1 );"<<endl;
	vecArea2.setValue( 2, 1 );
	
	//create vector domain with two elements
	cout<<"vecDomainsE2[ 0 ] = new cDomainNaturalNumberBit( 64 );"<<endl;
	vecDomainsE2[ 0 ] = new cDomainNaturalNumberBit( 64 );
	cout<<"vecDomainsE2[ 1 ] = &vecDomainSubareaE2;"<<endl;
	vecDomainsE2[ 1 ] = &vecDomainSubareaE2;
	cout<<"cDomainVector vectorDomainAreaE2Nat64( vecDomainsE2 );"<<endl;
	cDomainVector vectorDomainAreaE2Nat64( vecDomainsE2 );
	delete vecDomainsE2[ 0 ];
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root2;"<<flush<<endl;
	cRoot root2;
	cout<<"root2.getDomains()->addDomain( testTypeArea, &vectorDomainAreaE2Nat64 );"<<endl;
	root2.getDomains()->addDomain( testTypeArea, &vectorDomainAreaE2Nat64 );
	cout<<"root2.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB4 );"<<endl;
	root2.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB4 );
	cout<<"cArea area16( vecArea2, &point1, &root2 );"<<endl;
	cArea area16( vecArea2, &point1, &root2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"root.getDomains()->addDomain( testTypeVariable, &vectorDomainAreaE2Nat64 );"<<endl;
	root.getDomains()->addDomain( testTypeVariable, &vectorDomainAreaE2Nat64 );
	cout<<"cArea area16( vecArea2, &root, &root, &point1 );"<<endl;
	cArea area16( vecArea2, &root, &root, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"area16.getDefinedVariable()->setIntegerValue( 3 );"<<endl;
	area16.getDefinedVariable()->setIntegerValue( 3 );
	
#ifdef FEATURE_STORE_COMPRESSED_NO_DEFINED_VARIABLES
	szAreaE16[ 0 ] = (char)0x08;
	szAreaE16[ 1 ] = (char)0x01;
	szAreaE16[ 2 ] = (char)0x00;
	szAreaE16[ 3 ] = (char)0x00;
	szAreaE16[ 4 ] = (char)0x00;
	szAreaE16[ 5 ] = (char)0x00;
	szAreaE16[ 6 ] = (char)0x00;
	szAreaE16[ 7 ] = (char)0x00;
	szAreaE16[ 8 ] = (char)0x00;
	uiActualByte = 8;

	szAreaE16[ uiActualByte ] = (char)0x20;
	uiActualByte++;
	szAreaE16[ uiActualByte ] = (char)0x20;
	uiActualByte++;
	szAreaE16[ uiActualByte ] = (char)0x00;
	uiActualByte++;
	
	for ( unsigned int uiSubarea = 2; uiSubarea <= uiSubareas; uiSubarea++ ){
		
		cout<<"vecArea2.setValue( 1, "<< uiSubarea <<" );"<<endl;
		vecArea2.setValue( 1, uiSubarea );
		cout<<"vecArea2.setValue( 2, "<< uiSubarea <<" );"<<endl;
		vecArea2.setValue( 2, uiSubarea );
		cout<<"area16.addSubarea( vecArea2 );"<<endl;
		area16.addSubarea( vecArea2 );

		szAreaE16[ uiActualByte ] = ((unsigned char)(uiSubarea * 2))<<4;
		uiActualByte++;
		szAreaE16[ uiActualByte ] = ((unsigned char)(uiSubarea * 2))>>4;
		szAreaE16[ uiActualByte ] |= ((unsigned char)(uiSubarea * 2))<<4;
		uiActualByte++;
		szAreaE16[ uiActualByte ] = ((unsigned char)(uiSubarea * 2))>>4;
		uiActualByte++;
	}
	//point
	szAreaE16[ uiActualByte ] = (char)0x20;
	uiActualByte++;
	szAreaE16[ uiActualByte ] = (char)0x01;
	uiActualByte++;
#else //FEATURE_SIMPLE_CONSTRUCTOR
	szAreaE16[ 0 ] = (char)0x38;
	szAreaE16[ 1 ] = (char)0x10;
	szAreaE16[ 2 ] = (char)0x00;
	szAreaE16[ 3 ] = (char)0x00;
	szAreaE16[ 4 ] = (char)0x00;
	szAreaE16[ 5 ] = (char)0x00;
	szAreaE16[ 6 ] = (char)0x00;
	szAreaE16[ 7 ] = (char)0x00;
	szAreaE16[ 8 ] = (char)0x00;
	uiActualByte = 9;

	szAreaE16[ uiActualByte ] = (char)0x02;
	uiActualByte++;
	szAreaE16[ uiActualByte ] = (char)0x02;
	uiActualByte++;
	szAreaE16[ uiActualByte ] = (char)0x00;
	uiActualByte++;
	
	for ( unsigned int uiSubarea = 2; uiSubarea <= uiSubareas; uiSubarea++ ){
		
		cout<<"vecArea2.setValue( 1, "<< uiSubarea <<" );"<<endl;
		vecArea2.setValue( 1, uiSubarea );
		cout<<"vecArea2.setValue( 2, "<< uiSubarea <<" );"<<endl;
		vecArea2.setValue( 2, uiSubarea );
		cout<<"area16.addSubarea( vecArea2 );"<<endl;
		area16.addSubarea( vecArea2 );

		szAreaE16[ uiActualByte ] = (char)(uiSubarea * 2);
		uiActualByte++;
		szAreaE16[ uiActualByte ] = (char)(uiSubarea * 2);
		uiActualByte++;
		szAreaE16[ uiActualByte ] = (char)0x00;
		uiActualByte++;
	}
	//point
	szAreaE16[ uiActualByte ] = (char)0x12;
	uiActualByte++;
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//test get compressed size
	if ( (unsigned int)(area16.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			area1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "areaE16.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = area16.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	iReturn += compareBytsWithFile( szFileNameBuffer, szAreaE16, (uiCompressedSize / 8 + 1) );


	return iReturn;
}


/**
 * This method positions methods of the class.
 *
 * methods tested:
 * 	- unsignedIntFib getNumberOfSubareas() const;
 * 	- cVectorArea * getSubarea( unsignedIntFib iSubarea=1 );
 * 	- bool addSubarea( const cVectorArea &underArea, unsignedIntFib uiPosition=0 );
 * 	- bool deleteSubarea( unsignedIntFib uiSubareaPosition );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testSubAreas( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the subarea -methods"<<endl;
	
	//controlllist
	list< pair<long, long> > liSubareas;

	const long uiLowerBound1 = rand() % 1024 - 512;
	const long uiUpperBound1 = rand() % 1024 - 512;
	cVectorArea vecArea1( uiLowerBound1, uiUpperBound1 );
	cArea area( vecArea1 );
	liSubareas.push_back( make_pair( uiLowerBound1, uiUpperBound1 ) );
	const cArea * pAreaConst = &area;
	
	for ( unsigned int uiIteration = 0; uiIteration < 1000; uiIteration++ ){
		
		//choos random subarea to change
		const unsigned int uiChangeSubarea = rand() % (liSubareas.size() + 1);
		
		//choos if delete or add a subarea
		if ( rand() % 2 == 0 ){
			const long uiLowerBound = rand() % 1024 - 512;
			const long uiUpperBound = rand() % 1024 - 512;
			cVectorArea vecArea( uiLowerBound, uiUpperBound );
			//add a subarea
			cout<<"area.addSubarea( vecArea("<< uiLowerBound <<
				", "<< uiUpperBound <<" ) , "<< uiChangeSubarea <<" );"<<endl;
			const bool bSubAreaAdded = area.addSubarea( vecArea, uiChangeSubarea );
			if ( ! bSubAreaAdded ){
				cerr<<"Error: Couldn't insert the subarea from "<< uiLowerBound <<
					" to "<< uiUpperBound <<" on the position "<<
					uiChangeSubarea <<".(size="<< liSubareas.size() <<")"<<endl;
				iReturn++;
				continue;
			}
			if ( (uiChangeSubarea != 0) && (uiChangeSubarea < liSubareas.size()) ){
				//insert the new subarea in the controlllist
				list< pair<long, long> >::iterator itrInsertSubarea = liSubareas.begin();
				
				for ( unsigned int uiActualSubarea = 1;
						uiActualSubarea < uiChangeSubarea;
						uiActualSubarea++, itrInsertSubarea++ ){
					//nothing to do
				}
				liSubareas.insert( itrInsertSubarea, make_pair( uiLowerBound, uiUpperBound ) );
			}else{//insert on back
				liSubareas.push_back( make_pair( uiLowerBound, uiUpperBound ) );
			}
			
		}else{
			//delete a subarea
			cout<<"area.deleteSubarea( "<< uiChangeSubarea <<" );"<<endl;
			const bool bSubAreaDeleted = area.deleteSubarea( uiChangeSubarea );
			if ( ! bSubAreaDeleted ){
				if ( (uiChangeSubarea != 0) && ( 1 < liSubareas.size() ) ){
					cerr<<"Error: Couldn't delete the subarea from the position "<<
						uiChangeSubarea <<".(size="<< liSubareas.size() <<")"<<endl;
					iReturn++;
				}
				continue;
			}
			if ( (uiChangeSubarea == 0) || ( liSubareas.size() < 2 ) ){
				cerr<<"Error: Could delete the subarea from the position "<<
					uiChangeSubarea <<".(size="<< liSubareas.size() <<")"<<endl;
				iReturn++;
				continue;
			}

			if ( (uiChangeSubarea != 0) && (uiChangeSubarea < liSubareas.size()) ){
				//insert the new subarea in the controlllist
				list< pair<long, long> >::iterator itrDeletedSubarea = liSubareas.begin();
				
				for ( unsigned int uiActualSubarea = 1;
						uiActualSubarea < uiChangeSubarea;
						uiActualSubarea++, itrDeletedSubarea++ ){
					//nothing to do
				}
				liSubareas.erase( itrDeletedSubarea );
			}else{//insert on back
				liSubareas.pop_back();
			}
		}
		//check the subareas
		
		if ( pAreaConst->getNumberOfSubareas() != liSubareas.size() ){
			cerr<<"Error: The area has "<< pAreaConst->getNumberOfSubareas() <<
				" subareas, but should have "<< liSubareas.size() <<endl;
			iReturn++;
		}
		list< pair<long, long> >::iterator itrSubarea = liSubareas.begin();
		for ( unsigned int uiSubarea = 1;
				uiSubarea <= pAreaConst->getNumberOfSubareas();
				uiSubarea++ ){
				
			cVectorArea * pSubArea = area.getSubarea( uiSubarea );
			if ( pSubArea == NULL ){
				cerr<<"Error: Ther is no "<<uiSubarea <<"'th subarea. (size="<<
					liSubareas.size() <<")"<<endl;
				iReturn++;
			}else{
				//check the subarea bounds
				if ( (pSubArea->getLowerBound() != itrSubarea->first) ||
						(pSubArea->getUpperBound() != itrSubarea->second) ){
					cerr<<"Error: The "<<uiSubarea <<"'th subarea is wrong."<<endl;
					cerr<<"   correct lowerbound: "<< itrSubarea->first <<
						" given lowerbound: "<< pSubArea->getLowerBound() <<endl;
					cerr<<"   correct upperbound: "<< itrSubarea->second <<
						" given upperbound: "<< pSubArea->getUpperBound() <<endl;
					iReturn++;
				}
				//check the defining fib -element of the subarea
				if ( pSubArea->getDefiningFibElement() != pAreaConst ){
					cerr<<"Error: The "<<uiSubarea <<"'th subarea has the wrong definingelement."<<endl;
					cerr<<"   correct definingelement: "<< pAreaConst <<
						" given definingelement: "<< pSubArea->getDefiningFibElement() <<endl;
					iReturn++;
				}
			}
			if ( itrSubarea != liSubareas.end() ){
				itrSubarea++;
			}else{
				cerr<<"Error: Ther are more subareas in the area than ther should be. (size="<<
					liSubareas.size() <<")"<<endl;
				iReturn++;
			}
		}
		//check out of bounderie subareas
		cVectorArea * pSubArea = area.getSubarea( 0 );
		if ( pSubArea != NULL ){
			cerr<<"Error: Ther is a "<<0 <<"'th subarea. (size="<<
				liSubareas.size() <<")"<<endl;
			iReturn++;
		}
		pSubArea = area.getSubarea( liSubareas.size() + 1 );
		if ( pSubArea != NULL ){
			cerr<<"Error: Ther is a "<< liSubareas.size() + 1 <<"'th subarea. (size="<<
				liSubareas.size() <<")"<<endl;
			iReturn++;
		}
	}

	return iReturn;
}


/**
 * This method tests the variable methods of the cArea class.
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
	
	cout<<"cVectorArea vecArea1;"<<endl;
	cVectorArea vecArea1;
	cout<<"vecArea1.setValue( 1, 4);"<<endl;
	vecArea1.setValue( 1, 4);
	cout<<"vecArea1.setValue( 2, 7);"<<endl;
	vecArea1.setValue( 2, 7);
	
	cout<<"cVectorArea vecArea2;"<<endl;
	cVectorArea vecArea2;
	cout<<"vecArea2.setValue( 1, 2);"<<endl;
	vecArea2.setValue( 1, 2);

	cout<<"cArea area1( vecArea1 );"<<endl;
	cArea area1( vecArea1 );
	
	cout<<"area1.addSubarea( vecArea2 );"<<endl;
	area1.addSubarea( vecArea2 );

	//check the isUsedVariable() methode from cArea
	cout<<"area1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! area1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the areaelement. "<<endl;
		iReturn++;
	}
	set<cFibVariable*> setCorrectUsedVariables;
	
	//check getUsedVariables()
	cout<<"setUsedVariables = area1.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = area1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"area1.getSubarea( 2 )->setVariable( 1, pVariable1 );"<<endl;
	area1.getSubarea( 2 )->setVariable( 1, pVariable1 );
	setCorrectUsedVariables.insert( pVariable1 );

	//check the isUsedVariable() methode from cArea
	cout<<"area1.isUsedVariable( pVariable1 )"<<endl;
	if ( area1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the areaelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = area1.getUsedVariables(); "<<endl;
	setUsedVariables = area1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"area1.getSubarea( 1 )->setVariable( 1, pVariable2 );"<<endl;
	area1.getSubarea( 1 )->setVariable( 1, pVariable2 );
	setCorrectUsedVariables.insert( pVariable2 );

	//check the isUsedVariable() methode from cArea
	cout<<"area1.isUsedVariable( pVariable2 )"<<endl;
	if ( area1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the areaelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = area1.getUsedVariables(); "<<endl;
	setUsedVariables = area1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"area1.getSubarea( 1 )->setVariable( 2, pVariable4 );"<<endl;
	area1.getSubarea( 1 )->setVariable( 2, pVariable4 );
	setCorrectUsedVariables.insert( pVariable4 );

	//check the isUsedVariable() methode from cArea
	cout<<"area1.isUsedVariable( pVariable4 )"<<endl;
	if ( area1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable4 is correctly used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is not used in the areaelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = area1.getUsedVariables(); "<<endl;
	setUsedVariables = area1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"area1.getSubarea( 1 )->setVariable( 2, pVariable1 );"<<endl;
	area1.getSubarea( 1 )->setVariable( 2, pVariable1 );
	setCorrectUsedVariables.erase( pVariable4 );
	//check the isUsedVariable() methode from cArea
	cout<<"area1.isUsedVariable( pVariable1 )"<<endl;
	if ( area1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the areaelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = area1.getUsedVariables(); "<<endl;
	setUsedVariables = area1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"area1.replaceVariable( pVariable2, pVariable3 );"<<endl;
	bool bVariableReplaced = area1.replaceVariable( pVariable2, pVariable3 );
	setCorrectUsedVariables.erase( pVariable2 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cArea
	cout<<"area1.isUsedVariable( pVariable2 )"<<endl;
	if ( ! area1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the areaelement. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cArea
	cout<<"area1.isUsedVariable( pVariable3 )"<<endl;
	if ( area1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the areaelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = area1.getUsedVariables(); "<<endl;
	setUsedVariables = area1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"Try replacing non existing variable pVariable2:"<<endl;
	cout<<"area1.replaceVariable( pVariable2, pVariable4 );"<<endl;
	bVariableReplaced = area1.replaceVariable( pVariable2, pVariable4 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = area1.getUsedVariables(); "<<endl;
	setUsedVariables = area1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cArea
	cout<<"area1.isUsedVariable( pVariable2 )"<<endl;
	if ( ! area1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the areaelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cArea
	cout<<"area1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! area1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable4 is correctly not used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is used in the areaelement. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cArea
	cout<<"area1.isUsedVariable( pVariable3 )"<<endl;
	if ( area1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the areaelement. "<<endl;
		iReturn++;
	}

	cout<<"area1.replaceVariable( pVariable1, pVariable3 );"<<endl;
	bVariableReplaced = area1.replaceVariable( pVariable1, pVariable3 );
	setCorrectUsedVariables.erase( pVariable1 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cArea
	cout<<"area1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! area1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the areaelement. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cArea
	cout<<"area1.isUsedVariable( pVariable3 )"<<endl;
	if ( area1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the areaelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = area1.getUsedVariables(); "<<endl;
	setUsedVariables = area1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing variable methods on a area with a containing point"<<endl;

	cout<<"cVectorPosition vecPositionE3( 3 );"<<endl;
	cVectorPosition vecPositionE3( 3 );

	cout<<"cPoint point1( &vecPositionE3 );"<<endl;
	cPoint point1( &vecPositionE3 );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea areaPoint( vecArea1, &point1 );"<<endl;
	cArea areaPoint( vecArea1, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cArea areaPoint( vecArea1, NULL, NULL, &point1 );"<<endl;
	cArea areaPoint( vecArea1, NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the isUsedVariable() methode from cArea
	cout<<"areaPoint.isUsedVariable( pVariable1 )"<<endl;
	if ( ! areaPoint.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the areaelement. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.clear();
	
	//check getUsedVariables()
	cout<<"setUsedVariables = areaPoint.getUsedVariables(); "<<endl;
	setUsedVariables = areaPoint.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"point1.getPosition()->setVariable( 3, pVariable1 );"<<endl;
	point1.getPosition()->setVariable( 3, pVariable1 );

	//check the isUsedVariable() methode from cArea
	cout<<"areaPoint.isUsedVariable( pVariable1 )"<<endl;
	if ( ! areaPoint.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the areaelement. "<<endl;
		iReturn++;
	}
	cout<<"point1.isUsedVariable( pVariable1 )"<<endl;
	if ( point1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the areaelement. "<<endl;
		iReturn++;
	}
	cout<<"areaPoint.isUsedVariable( pVariable1, ED_BELOW_EQUAL )"<<endl;
	if ( areaPoint.isUsedVariable( pVariable1, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable1 is correctly used ED_BELOW_EQUAL the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used ED_BELOW_EQUAL the areaelement. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = areaPoint.getUsedVariables(); "<<endl;
	setUsedVariables = areaPoint.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.insert( pVariable1 );
	//check getUsedVariables()
	cout<<"setUsedVariables = areaPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = areaPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back for ED_BELOW_EQUAL. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong for ED_BELOW_EQUAL. "<<endl;
		iReturn++;
	}

	cout<<"point1.getPosition()->setVariable( 1, pVariable2 );"<<endl;
	point1.getPosition()->setVariable( 1, pVariable2 );
	
	//check the isUsedVariable() methode from cArea
	cout<<"areaPoint.isUsedVariable( pVariable2 )"<<endl;
	if ( ! areaPoint.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the areaelement. "<<endl;
		iReturn++;
	}
	cout<<"point1.isUsedVariable( pVariable2 )"<<endl;
	if ( point1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the areaelement. "<<endl;
		iReturn++;
	}
	cout<<"areaPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( areaPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly used ED_BELOW_EQUAL the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used ED_BELOW_EQUAL the areaelement. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = areaPoint.getUsedVariables(); "<<endl;
	setUsedVariables = areaPoint.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.insert( pVariable2 );
	//check getUsedVariables()
	cout<<"setUsedVariables = areaPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = areaPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back for ED_BELOW_EQUAL. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong for ED_BELOW_EQUAL. "<<endl;
		iReturn++;
	}
	
	cout<<"areaPoint.replaceVariable( pVariable2, pVariable3 );"<<endl;
	bVariableReplaced = areaPoint.replaceVariable( pVariable2, pVariable3 );
	setCorrectUsedVariables.erase( pVariable2 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cArea
	cout<<"areaPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( ! areaPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly not used ED_BELOW_EQUAL the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used ED_BELOW_EQUAL the areaelement. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cArea
	cout<<"areaPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL )"<<endl;
	if ( areaPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_BELOW_EQUAL the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_BELOW_EQUAL the areaelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = areaPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = areaPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods getDefinedVariable(), isDefinedVariable( ED_POSITION ) and getDefinedVariables( ED_POSITION )"<<endl;

	cout<<"pDefinedVariable = areaPoint.getDefinedVariable()"<<endl;
	cFibVariable * pDefinedVariable = areaPoint.getDefinedVariable();

	if ( pDefinedVariable != NULL ){
	
		cout<<"The fib -element correctly defines a variable. "<<endl;
	}else{
		cerr<<"Error: The fib -element dosn't defines a variable.(NULL is returned) "<<endl;
		iReturn++;
	}
	
	//check the isDefinedVariable() methode from cList
	cout<<"areaPoint.isDefinedVariable( pDefinedVariable, ED_POSITION )"<<endl;
	if ( areaPoint.isDefinedVariable( pDefinedVariable, ED_POSITION ) ){
	
		cout<<"The variable pDefinedVariable is correctly defined in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pDefinedVariable isn't defined in the areaelement. "<<endl;
		iReturn++;
	}
	//check the isDefinedVariable() methode from cList
	cout<<"areaPoint.isDefinedVariable( pVariable1, ED_POSITION )"<<endl;
	if ( ! areaPoint.isDefinedVariable( pVariable1, ED_POSITION ) ){
	
		cout<<"The variable pVariable1 is correctly not defined in the areaelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is defined in the areaelement. "<<endl;
		iReturn++;
	}

	//check getDefinedVariables()
	cout<<"liDefinedVariables = areaPoint.getDefinedVariables( ED_POSITION ); "<<endl;
	list<cFibVariable*> liDefinedVariables = areaPoint.getDefinedVariables( ED_POSITION );
	
	list<cFibVariable*> liDefinedVariablesCorrect;
	liDefinedVariablesCorrect.push_back( pDefinedVariable);
	
	if ( liDefinedVariables == liDefinedVariablesCorrect ){
	
		cout<<"Ther are the correct variables defined in the areaelement. "<<endl;
	}else{
		cerr<<"Error: Ther aren't the correct variables defined in the areaelement. "<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the sort() method of the cArea class.
 *
 * methods tested:
 * 	- bool sort();
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testSort( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing sorting the subarea bounderies"<<endl;

	cout<<"cVectorArea vecArea1;"<<endl;
	cVectorArea vecArea1;

	cout<<"cArea area( vecArea1 );"<<endl;
	cArea area( vecArea1 );
	cout<<"area.addSubarea( vecArea1 );"<<endl;
	area.addSubarea( vecArea1 );
	cout<<"area.addSubarea( vecArea1 );"<<endl;
	area.addSubarea( vecArea1 );

	cArea areaSorted( vecArea1 );
	areaSorted.addSubarea( vecArea1 );
	areaSorted.addSubarea( vecArea1 );

	cout<<"area.getSubarea( 1 )->setLowerBoundValue( 1 );"<<endl;
	area.getSubarea( 1 )->setLowerBoundValue( 1 );
	cout<<"area.getSubarea( 1 )->setUpperBoundValue( 2 );"<<endl;
	area.getSubarea( 1 )->setUpperBoundValue( 2 );
	areaSorted.getSubarea( 1 )->setLowerBoundValue( 1 );
	areaSorted.getSubarea( 1 )->setUpperBoundValue( 2 );
	
	cout<<"area.getSubarea( 2 )->setLowerBoundValue( 5 );"<<endl;
	area.getSubarea( 2 )->setLowerBoundValue( 5 );
	cout<<"area.getSubarea( 2 )->setUpperBoundValue( 4 );"<<endl;
	area.getSubarea( 2 )->setUpperBoundValue( 4 );
	areaSorted.getSubarea( 2 )->setLowerBoundValue( 4 );
	areaSorted.getSubarea( 2 )->setUpperBoundValue( 5 );

	cout<<"area.getSubarea( 3 )->setLowerBoundValue( 7 );"<<endl;
	area.getSubarea( 3 )->setLowerBoundValue( 7 );
	cout<<"area.getSubarea( 3 )->setUpperBoundValue( 7 );"<<endl;
	area.getSubarea( 3 )->setUpperBoundValue( 7 );
	areaSorted.getSubarea( 3 )->setLowerBoundValue( 7 );
	areaSorted.getSubarea( 3 )->setUpperBoundValue( 7 );

	cout<<"area.sort();"<<endl;
	bool bAreaSorted = area.sort();
	if ( bAreaSorted ){
	
		if ( area.equalElement( areaSorted ) ){
		
			cout<<"The area was correctly sorted. "<<endl;
		}else{
			cerr<<"Error: The area wasn't correctly sorted. "<<endl;
			cerr<<"sorted: "<<endl;
			area.storeXml( cerr );
			cerr<<endl<<"correct: "<<endl;
			areaSorted.storeXml( cerr );
			cerr<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The area couldn't be sorted. "<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing sorting the subarea in increasing order"<<endl;

	cout<<"area.getSubarea( 1 )->setLowerBoundValue( 7 );"<<endl;
	area.getSubarea( 1 )->setLowerBoundValue( 7 );
	cout<<"area.getSubarea( 1 )->setUpperBoundValue( 7 );"<<endl;
	area.getSubarea( 1 )->setUpperBoundValue( 7 );
	
	cout<<"area.getSubarea( 2 )->setLowerBoundValue( 4 );"<<endl;
	area.getSubarea( 2 )->setLowerBoundValue( 4 );
	cout<<"area.getSubarea( 2 )->setUpperBoundValue( 5 );"<<endl;
	area.getSubarea( 2 )->setUpperBoundValue( 5 );

	cout<<"area.getSubarea( 3 )->setLowerBoundValue( 1 );"<<endl;
	area.getSubarea( 3 )->setLowerBoundValue( 1 );
	cout<<"area.getSubarea( 3 )->setUpperBoundValue( 2 );"<<endl;
	area.getSubarea( 3 )->setUpperBoundValue( 2 );

	cout<<"area.sort();"<<endl;
	bAreaSorted = area.sort();
	if ( bAreaSorted ){
	
		if ( area.equalElement( areaSorted ) ){
		
			cout<<"The area was correctly sorted. "<<endl;
		}else{
			cerr<<"Error: The area wasn't correctly sorted. "<<endl;
			cerr<<"sorted: "<<endl;
			area.storeXml( cerr );
			cerr<<endl<<"correct: "<<endl;
			areaSorted.storeXml( cerr );
			cerr<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The area couldn't be sorted. "<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing sorting the subarea with intersections of subareas"<<endl;

	cout<<"area.addSubarea( vecArea1 );"<<endl;
	area.addSubarea( vecArea1 );
	cout<<"area.addSubarea( vecArea1 );"<<endl;
	area.addSubarea( vecArea1 );

	cout<<"area.getSubarea( 1 )->setLowerBoundValue( 3 );"<<endl;
	area.getSubarea( 1 )->setLowerBoundValue( 3 );
	cout<<"area.getSubarea( 1 )->setUpperBoundValue( 6 );"<<endl;
	area.getSubarea( 1 )->setUpperBoundValue( 6 );
	
	cout<<"area.getSubarea( 2 )->setLowerBoundValue( 5 );"<<endl;
	area.getSubarea( 2 )->setLowerBoundValue( 5 );
	cout<<"area.getSubarea( 2 )->setUpperBoundValue( 8 );"<<endl;
	area.getSubarea( 2 )->setUpperBoundValue( 8 );

	cout<<"area.getSubarea( 3 )->setLowerBoundValue( 0 );"<<endl;
	area.getSubarea( 3 )->setLowerBoundValue( 0 );
	cout<<"area.getSubarea( 3 )->setUpperBoundValue( 0 );"<<endl;
	area.getSubarea( 3 )->setUpperBoundValue( 0 );
	
	cout<<"area.getSubarea( 4 )->setLowerBoundValue( -2 );"<<endl;
	area.getSubarea( 4 )->setLowerBoundValue( -2 );
	cout<<"area.getSubarea( 4 )->setUpperBoundValue( -5 );"<<endl;
	area.getSubarea( 4 )->setUpperBoundValue( -5 );

	cout<<"area.getSubarea( 5 )->setLowerBoundValue( 1 );"<<endl;
	area.getSubarea( 5 )->setLowerBoundValue( 1 );
	cout<<"area.getSubarea( 5 )->setUpperBoundValue( 1 );"<<endl;
	area.getSubarea( 5 )->setUpperBoundValue( 1 );

	areaSorted.getSubarea( 1 )->setLowerBoundValue( -5 );
	areaSorted.getSubarea( 1 )->setUpperBoundValue( -2 );
	areaSorted.getSubarea( 2 )->setLowerBoundValue( 0 );
	areaSorted.getSubarea( 2 )->setUpperBoundValue( 1 );
	areaSorted.getSubarea( 3 )->setLowerBoundValue( 3 );
	areaSorted.getSubarea( 3 )->setUpperBoundValue( 8 );

	cout<<"area.sort();"<<endl;
	bAreaSorted = area.sort();
	if ( bAreaSorted ){
	
		if ( area.equalElement( areaSorted ) ){
		
			cout<<"The area was correctly sorted. "<<endl;
		}else{
			cerr<<"Error: The area wasn't correctly sorted. "<<endl;
			cerr<<"sorted: "<<endl;
			area.storeXml( cerr );
			cerr<<endl<<"correct: "<<endl;
			areaSorted.storeXml( cerr );
			cerr<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The area couldn't be sorted. "<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing sorting the subarea with a subareas is part of an other"<<endl;

	cout<<"area.addSubarea( vecArea1 );"<<endl;
	area.addSubarea( vecArea1 );
	cout<<"area.addSubarea( vecArea1 );"<<endl;
	area.addSubarea( vecArea1 );
	cout<<"area.addSubarea( vecArea1 );"<<endl;
	area.addSubarea( vecArea1 );
	cout<<"area.addSubarea( vecArea1 );"<<endl;
	area.addSubarea( vecArea1 );

	cout<<"area.getSubarea( 1 )->setLowerBoundValue( 3 );"<<endl;
	area.getSubarea( 1 )->setLowerBoundValue( 3 );
	cout<<"area.getSubarea( 1 )->setUpperBoundValue( 6 );"<<endl;
	area.getSubarea( 1 )->setUpperBoundValue( 6 );
	
	cout<<"area.getSubarea( 2 )->setLowerBoundValue( 5 );"<<endl;
	area.getSubarea( 2 )->setLowerBoundValue( 5 );
	cout<<"area.getSubarea( 2 )->setUpperBoundValue( 8 );"<<endl;
	area.getSubarea( 2 )->setUpperBoundValue( 8 );

	cout<<"area.getSubarea( 3 )->setLowerBoundValue( 0 );"<<endl;
	area.getSubarea( 3 )->setLowerBoundValue( 0 );
	cout<<"area.getSubarea( 3 )->setUpperBoundValue( 0 );"<<endl;
	area.getSubarea( 3 )->setUpperBoundValue( 0 );
	
	cout<<"area.getSubarea( 4 )->setLowerBoundValue( -2 );"<<endl;
	area.getSubarea( 4 )->setLowerBoundValue( -2 );
	cout<<"area.getSubarea( 4 )->setUpperBoundValue( -5 );"<<endl;
	area.getSubarea( 4 )->setUpperBoundValue( -5 );

	cout<<"area.getSubarea( 5 )->setLowerBoundValue( 1 );"<<endl;
	area.getSubarea( 5 )->setLowerBoundValue( 1 );
	cout<<"area.getSubarea( 5 )->setUpperBoundValue( 1 );"<<endl;
	area.getSubarea( 5 )->setUpperBoundValue( 1 );

	cout<<"area.getSubarea( 6 )->setLowerBoundValue( -4 );"<<endl;
	area.getSubarea( 6 )->setLowerBoundValue( -4 );
	cout<<"area.getSubarea( 6 )->setUpperBoundValue( -3 );"<<endl;
	area.getSubarea( 6 )->setUpperBoundValue( -3 );

	cout<<"area.getSubarea( 7 )->setLowerBoundValue( 8 );"<<endl;
	area.getSubarea( 7 )->setLowerBoundValue( 8 );
	cout<<"area.getSubarea( 7 )->setUpperBoundValue( 8 );"<<endl;
	area.getSubarea( 7 )->setUpperBoundValue( 8 );

	cout<<"area.sort();"<<endl;
	bAreaSorted = area.sort();
	if ( bAreaSorted ){
	
		if ( area.equalElement( areaSorted ) ){
		
			cout<<"The area was correctly sorted. "<<endl;
		}else{
			cerr<<"Error: The area wasn't correctly sorted. "<<endl;
			cerr<<"sorted: "<<endl;
			area.storeXml( cerr );
			cerr<<endl<<"correct: "<<endl;
			areaSorted.storeXml( cerr );
			cerr<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The area couldn't be sorted. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing sorting the subarea with variables"<<endl;
	
	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	cout<<"rootEmpty1.setNumberOfInputVariables( 10 );"<<endl;
	rootEmpty1.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 = rootEmpty1.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootEmpty1.getInputVariable( 1 );
	cout<<"pVariable1->setIntegerValue( 8 );"<<endl;
	pVariable1->setIntegerValue( 8 );
	cout<<"pVariable2 = rootEmpty1.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = rootEmpty1.getInputVariable( 2 );
	cout<<"pVariable2->setIntegerValue( -2 );"<<endl;
	pVariable2->setIntegerValue( -2 );
	cout<<"pVariable3 = rootEmpty1.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = rootEmpty1.getInputVariable( 3 );
	cout<<"pVariable3->setIntegerValue( 9 );"<<endl;
	pVariable3->setIntegerValue( 9 );
	
	cout<<"area.addSubarea( vecArea1 );"<<endl;
	area.addSubarea( vecArea1 );
	cout<<"area.addSubarea( vecArea1 );"<<endl;
	area.addSubarea( vecArea1 );
	cout<<"area.addSubarea( vecArea1 );"<<endl;
	area.addSubarea( vecArea1 );
	cout<<"area.addSubarea( vecArea1 );"<<endl;
	area.addSubarea( vecArea1 );

	cout<<"area.getSubarea( 1 )->setLowerBoundValue( 3 );"<<endl;
	area.getSubarea( 1 )->setLowerBoundValue( 3 );
	cout<<"area.getSubarea( 1 )->setUpperBoundValue( 6 );"<<endl;
	area.getSubarea( 1 )->setUpperBoundValue( 6 );
	
	cout<<"area.getSubarea( 2 )->setLowerBoundValue( 5 );"<<endl;
	area.getSubarea( 2 )->setLowerBoundValue( 5 );
	cout<<"area.getSubarea( 2 )->setUpperBoundVariable( pVariable1 );"<<endl;
	area.getSubarea( 2 )->setUpperBoundVariable( pVariable1 );

	cout<<"area.getSubarea( 3 )->setLowerBoundValue( 0 );"<<endl;
	area.getSubarea( 3 )->setLowerBoundValue( 0 );
	cout<<"area.getSubarea( 3 )->setUpperBoundValue( 0 );"<<endl;
	area.getSubarea( 3 )->setUpperBoundValue( 0 );
	
	cout<<"area.getSubarea( 4 )->setLowerBoundVariable( pVariable2 );"<<endl;
	area.getSubarea( 4 )->setLowerBoundVariable( pVariable2 );
	cout<<"area.getSubarea( 4 )->setUpperBoundValue( -5 );"<<endl;
	area.getSubarea( 4 )->setUpperBoundValue( -5 );

	cout<<"area.getSubarea( 5 )->setLowerBoundValue( 1 );"<<endl;
	area.getSubarea( 5 )->setLowerBoundValue( 1 );
	cout<<"area.getSubarea( 5 )->setUpperBoundValue( 1 );"<<endl;
	area.getSubarea( 5 )->setUpperBoundValue( 1 );

	cout<<"area.getSubarea( 6 )->setLowerBoundValue( -4 );"<<endl;
	area.getSubarea( 6 )->setLowerBoundValue( -4 );
	cout<<"area.getSubarea( 6 )->setUpperBoundValue( -3 );"<<endl;
	area.getSubarea( 6 )->setUpperBoundValue( -3 );

	cout<<"area.getSubarea( 7 )->setLowerBoundVariable( pVariable3 );"<<endl;
	area.getSubarea( 7 )->setLowerBoundVariable( pVariable3 );
	cout<<"area.getSubarea( 7 )->setUpperBoundValue( 8 );"<<endl;
	area.getSubarea( 7 )->setUpperBoundValue( 8 );

	areaSorted.addSubarea( vecArea1 );
	areaSorted.addSubarea( vecArea1 );
	areaSorted.addSubarea( vecArea1 );
	areaSorted.getSubarea( 1 )->setLowerBoundValue( 5 );
	areaSorted.getSubarea( 1 )->setUpperBoundVariable( pVariable1 );
	areaSorted.getSubarea( 2 )->setLowerBoundVariable( pVariable2 );
	areaSorted.getSubarea( 2 )->setUpperBoundValue( -5 );
	areaSorted.getSubarea( 3 )->setLowerBoundValue( -4 );
	areaSorted.getSubarea( 3 )->setUpperBoundValue( -3 );
	areaSorted.getSubarea( 4 )->setLowerBoundValue( 0 );
	areaSorted.getSubarea( 4 )->setUpperBoundValue( 1 );
	areaSorted.getSubarea( 5 )->setLowerBoundValue( 3 );
	areaSorted.getSubarea( 5 )->setUpperBoundValue( 6 );
	areaSorted.getSubarea( 6 )->setLowerBoundVariable( pVariable3 );
	areaSorted.getSubarea( 6 )->setUpperBoundValue( 8 );

	cout<<"area.sort();"<<endl;
	bAreaSorted = area.sort();
	if ( bAreaSorted ){
	
		if ( area.equalElement( areaSorted ) ){
		
			cout<<"The area was correctly sorted. "<<endl;
		}else{
			cerr<<"Error: The area wasn't correctly sorted. "<<endl;
			cerr<<"sorted: "<<endl;
			area.storeXml( cerr );
			cerr<<endl<<"correct: "<<endl;
			areaSorted.storeXml( cerr );
			cerr<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The area couldn't be sorted. "<<endl;
		iReturn++;
	}
	
	return iReturn;
}






