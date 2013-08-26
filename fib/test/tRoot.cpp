/**
 * @file tRoot
 * file name: tRoot.cpp
 * @author Betti Oesterholz
 * @date 20.11.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cRoot.
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
 * This file contains the test for the class cRoot, which
 * represents a Fib -rootelement.
 *
 *
 * What's tested of class cRoot:
 * 	- cRoot( cFibElement * pInMainFibObject = NULL, cRoot * pInSuperiorRootElement = NULL );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- cMultimediaInfo * getMultimediaInfo();
 * 	- cOptionalPart * getOptionalPart();
 * 	- cVectorChecksum * getChecksum();
 * 	- void setChecksum( const cVectorChecksum * checksum = NULL);
 * 	- cDomains * getDomains();
 * 	- cDomains getValidDomains() const;
 * 	- cDomains * getValueDomains();
 * 	- cDomains getValidValueDomains() const;
 * 	- unsignedIntFib getNumberOfDimensions() const;
 * 	- unsignedIntFib getDimensionMapping( unsignedIntFib iDimensionNumber ) const;
 * 	- unsignedIntFib getNumberOfInputVariables() const;
 * 	- bool setNumberOfInputVariables( unsignedIntFib uiNumberOfInputVariables );
 * 	- list<cFibVariable*> getInputVariables();
 * 	- cFibVariable * getInputVariable( unsignedIntFib uiNumberOfInputVariable );
 * 	- doubleFib getStandardValueOfInputVariable( unsignedIntFib uiNumberOfInputVariable ) const;
 * 	- bool setStandardValueOfInputVariable( unsignedIntFib uiNumberOfInputVariable, doubleFib dValue );
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
 * 	- bool isUsedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool equalValuesSet( const cFibVariable * variableOwn, const cFibElement & fibElement, const cFibVariable * variable ) const;
 * 	- unsignedIntFib getNumberOfExternSubobjects() const;
 * 	- unsignedIntFib getNumberOfOutputVariables( unsignedIntFib uiNumberOfUnderObject ) const;
 * 	- unsignedIntFib getNumberOfSubRootObjects() const;
 * 	- pair<longFib, cRoot*> getSubRootObject( unsignedIntFib uiNumberOfUnderObject );
 * 	- unsignedIntFib getSubRootObjectNumber( longFib lIdentifier ) const;
 * 	- cRoot * getSubRootObjectForIdentifier( longFib lIdentifier );
 * 	- bool addSubRootObject( longFib lIdentifier, cRoot * pRootObject, unsignedIntFib uiPosition=0 );
 * 	- bool deleteSubRootObject( unsignedIntFib uiSubRootObjectNumber, bool bDeleteOld=true );
 * 	- list<longFib> getAllSubRootObjectIdentifiers() const;
 * 	- list<longFib> getAllRootObjectIdentifiers() const;
 * 	- cRoot * getRootObject( longFib lIdentifier );
 * 	- list<longFib> getAllAccessibleRootObjectIdentifiers() const;
 * 	- cRoot * getAccessibleRootObject( longFib lIdentifier );
 * 	- list<longFib> getAllDatabaseObjectIdentifiers() const;
 * 	- for the element: bool cRoot::equal( const cFibElement & fibObject ) const
 * 	- bool equalElement( const cFibElement & fibElement ) const;
 * 	- cRoot( const cRoot &rootElement );
 * 	- cFibElement *copyElement( 'u', 0 ) const;
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- bool setMainFibObject( cFibElement * pInMainFibObject );
 *
 *
 *
 * Test when cExtSubobject is implemented
 * 	-(TODO) unsignedIntFib checkExternSubobjects( intFib * iErrorNumber=NULL );
 * 	-(TODO) bool generateExternSubobjectsDefinitions( intFib * iErrorNumber=NULL );
 *
 *
 * Methods for changing the structur of an fib -object will be tested with
 *	tFibElementStructur. Methods for fib -objects will be tested with
 * Methods for storing and restoring will be tested in tFibElementStore.
 */
/*
History:
20.11.2009  Oesterholz  created
04.12.2009  Oesterholz  replaceVariable() tested
05.12.2009  Oesterholz  getDefinedVariables() tested
01.01.2010  Oesterholz  setMainFibObject(), isUsedVariable( ED_POSITION )
   and getUsedVariables( ED_POSITION ) tested
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
07.11.2011  Oesterholz  ExternUnderObjects to ExternSubobjects
30.11.2011  Oesterholz  cFibDatabase changes added
02.02.2012  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR implemented
28.01.2013  Oesterholz  COLOR_SW changed to COLOR_GRAYSCALE
01.08.2013  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR as default (not case removed)
*/

#include "version.h"

#include "cRoot.h"
#include "cPoint.h"
#include "cVectorPosition.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cTypeVariable.h"
#include "cTypeDimension.h"
#include "cTypeProperty.h"
#include "cTypeInVar.h"
#include "cTypeExtSubobject.h"
#include "cFibDatabase.h"


#include <iostream>
#include <algorithm>


using namespace fib;
using namespace std;

int testCostructor( unsigned long &ulTestphase );
int testInsertObjectInElement( unsigned long &ulTestphase );
int testGetMultimediaInfo( unsigned long &ulTestphase );
int testGetOptionalPart( unsigned long &ulTestphase );
int testChecksum( unsigned long &ulTestphase );
int testDomains( unsigned long &ulTestphase );
int testInputVariables( unsigned long &ulTestphase );
int testExternSubobjects( unsigned long &ulTestphase );
int testSubRootObjects( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testCopyElement( unsigned long &ulTestphase );
int testReplaceVariable( unsigned long &ulTestphase );
int testMainFibObject( unsigned long &ulTestphase );



int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cRoot methods"<<endl;
	cout<<      "=============================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testInsertObjectInElement( ulTestphase );
	iReturn += testGetMultimediaInfo( ulTestphase );
	iReturn += testGetOptionalPart( ulTestphase );
	iReturn += testChecksum( ulTestphase );
	iReturn += testDomains( ulTestphase );
	iReturn += testInputVariables( ulTestphase );
	iReturn += testExternSubobjects( ulTestphase );
	iReturn += testSubRootObjects( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopyElement( ulTestphase );
	iReturn += testReplaceVariable( ulTestphase );
	iReturn += testMainFibObject( ulTestphase );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the constructor of the cRoot class.
 *
 * methods tested:
 * 	- cRoot( cFibElement * pInMainFibObject = NULL, cRoot * pInSuperiorRootElement = NULL );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- unsignedIntFib getNumberOfElement()
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cRoot"<<endl;

	cout<<"cRoot rootEmpty;"<<endl;
	cRoot rootEmpty;

	//check the getType() methode from cRoot
	if ( rootEmpty.getType() == 'r' ){
	
		cout<<"The type of the root -element is correctly 'r' . "<<endl;
	}else{
		cerr<<"Error: The type of the root -element is "<<
			rootEmpty.getType()<<" but should be 'r' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cRoot
	if ( ! rootEmpty.isValidFibElement() ){
	
		cout<<"The root -element is correctly no correct root -element. "<<endl;
	}else{
		cerr<<"Error: The root -element is a correct root -element, but shouldn't be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cRoot
	if ( ! rootEmpty.isMovable() ){
	
		cout<<"The root -element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The root -element is movebel."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cRoot
	if ( rootEmpty.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the root -element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the root -element is "<<
			rootEmpty.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cRoot
	if ( rootEmpty.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the root -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the root -element is not NULL."<<endl;
		iReturn++;
	}

	//check the getNextFibElement() methode from cRoot
	if ( rootEmpty.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the root -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the root -element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cRoot
	if ( rootEmpty.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the root -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the root -element is "<<
			rootEmpty.getSuperiorFibElement() << " and not not NULL."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an root -element with an main fib -object"<<endl;
	cout<<"cPoint pointEmpty;"<<endl;
	cPoint pointEmpty;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootMain( &pointEmpty );"<<endl;
	cRoot rootMain( &pointEmpty );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootMain( NULL, NULL, &pointEmpty );"<<endl;
	cRoot rootMain( NULL, NULL, &pointEmpty );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the getType() methode from cRoot
	if ( rootMain.getType() == 'r' ){
	
		cout<<"The type of the root -element is correctly 'r' . "<<endl;
	}else{
		cerr<<"Error: The type of the root -element is "<<
			rootMain.getType()<<" but should be 'r' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cRoot
	if ( rootMain.isValidFibElement() ){
	
		cout<<"The root -element is correctly a correct root -element. "<<endl;
	}else{
		cerr<<"Error: The root -element is not a correct root -element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cRoot
	if ( ! rootMain.isMovable() ){
	
		cout<<"The root -element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The root -element is movebel."<<endl;
		iReturn++;
	}
	
	//check the isValidFibElement() methode from cRoot
	if ( rootMain.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the root -element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the root -element is "<<
			rootMain.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}

	//check the getNextFibElement() methode from cRoot
	if ( rootMain.getNextFibElement() == &pointEmpty ){
	
		cout<<"The next/ main fib -element for the root -element is correctly pointEmpty. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the root -element is not pointEmpty."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cRoot
	if ( rootMain.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the root -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the root -element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cRoot
	if ( rootMain.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the root -element is correctly rootMain. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the root -element is "<<
			rootMain.getSuperiorFibElement() << " and not not rootMain."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an root -element with an main fib -object and superior"<<endl;

	cout<<"cPoint pointEmpty2;"<<endl;
	cPoint pointEmpty2;

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootMainSup( &pointEmpty2, &rootMain );"<<endl;
	cRoot rootMainSup( &pointEmpty2, &rootMain );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootMainSup( &rootMain, NULL, &pointEmpty2 );"<<endl;
	cRoot rootMainSup( &rootMain, NULL, &pointEmpty2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the getType() methode from cRoot
	if ( rootMainSup.getType() == 'r' ){
	
		cout<<"The type of the root -element is correctly 'r' . "<<endl;
	}else{
		cerr<<"Error: The type of the root -element is "<<
			rootMainSup.getType()<<" but should be 'r' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cRoot
	if ( rootMainSup.isValidFibElement() ){
	
		cout<<"The root -element is correctly a correct root -element. "<<endl;
	}else{
		cerr<<"Error: The root -element is not a correct root -element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cRoot
	if ( ! rootMainSup.isMovable() ){
	
		cout<<"The root -element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The root -element is movebel."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cRoot
	if ( rootMainSup.getNumberOfElement() == 3 ){
	
		cout<<"The number of the fib -element for the root -element is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the root -element is "<<
			rootMainSup.getNumberOfElement() <<", but should be 3."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cRoot
	if ( rootMainSup.getNextFibElement() == &pointEmpty2 ){
	
		cout<<"The next/ main fib -element for the root -element is correctly pointEmpty2. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the root -element is not pointEmpty2."<<endl;
		iReturn++;
	}
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNextFibElement() methode from cRoot
	if ( rootMainSup.getFibElement( -1 ) == &pointEmpty ){
	
		cout<<"The previous fib -element for the root -element is correctly pointEmpty. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the root -element is "<<
			rootMainSup.getFibElement( -1 ) << " and not not pointEmpty."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNextFibElement() methode from cRoot
	if ( rootMainSup.getFibElement( -1 ) == &pointEmpty ){
	
		cout<<"The previous fib -element for the root -element is correctly pointEmpty. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the root -element is "<<
			rootMainSup.getFibElement( -1 ) << " and not not pointEmpty."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the getSuperiorFibElement() methode from cRoot
	if ( rootMainSup.getSuperiorFibElement() == &rootMain ){
	
		cout<<"The superior fib -element for the root -element is correctly rootMain. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the root -element is "<<
			rootMainSup.getSuperiorFibElement() << " and not not rootMain."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an root -element with all parameters given"<<endl;
	
	cout<<"cRoot rootEmpty2;"<<endl;
	cRoot rootEmpty2;
	cout<<"cPoint pointMain;"<<endl;
	cPoint pointMain;
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootFull( &pointMain, &rootEmpty2 );"<<endl;
	cRoot rootFull( &pointMain, &rootEmpty2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootFull( &rootEmpty2, &rootEmpty, &pointMain );"<<endl;
	cRoot rootFull( &rootEmpty2, &rootEmpty, &pointMain );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the getType() methode from cRoot
	if ( rootFull.getType() == 'r' ){
	
		cout<<"The type of the root -element is correctly 'r' . "<<endl;
	}else{
		cerr<<"Error: The type of the root -element is "<<
			rootFull.getType()<<" but should be 'r' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cRoot
	if ( rootFull.isValidFibElement() ){
	
		cout<<"The root -element is correctly a correct root -element. "<<endl;
	}else{
		cerr<<"Error: The root -element is not a correct root -element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cRoot
	if ( ! rootFull.isMovable() ){
	
		cout<<"The root -element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The root -element is movebel."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cRoot
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	if ( rootFull.getNumberOfElement() == 2 ){
		cout<<"The number of the fib -element for the root -element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the root -element is "<<
			rootFull.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	if ( rootFull.getNumberOfElement() == 3 ){
		cout<<"The number of the fib -element for the root -element is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the root -element is "<<
			rootFull.getNumberOfElement() <<", but should be 3."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the getNextFibElement() methode from cRoot
	if ( rootFull.getNextFibElement() == &pointMain ){
	
		cout<<"The next/ main fib -element for the root -element is correctly pointMain. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the root -element is not pointMain."<<endl;
		iReturn++;
	}

	//check the getNextFibElement() methode from cRoot
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	if ( rootFull.getFibElement( -1 ) == &rootEmpty2 ){
	
		cout<<"The previous fib -element for the root -element is correctly &rootEmpty2. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the root -element is "<<
			rootFull.getFibElement( -1 ) << " and not not &rootEmpty2."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	if ( rootFull.getFibElement( -1 ) == &rootEmpty ){
	
		cout<<"The previous fib -element for the root -element is correctly rootEmpty. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the root -element is "<<
			rootFull.getFibElement( -1 ) << " and not not rootEmpty."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getSuperiorFibElement() methode from cRoot
	if ( rootFull.getSuperiorFibElement() == &rootEmpty2 ){
	
		cout<<"The superior fib -element for the root -element is correctly rootEmpty2. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the root -element is "<<
			rootFull.getSuperiorFibElement() << " and not not rootEmpty2."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an root -element with no main -fib -object"<<endl;

	cout<<"cRoot rootEmpty3;"<<endl;
	cRoot rootEmpty3;

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootNoMain( NULL, &rootEmpty3 );"<<endl;
	cRoot rootNoMain( NULL, &rootEmpty3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootNoMain( &rootEmpty3, &rootEmpty2 );"<<endl;
	cRoot rootNoMain( &rootEmpty3, &rootEmpty2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the getType() methode from cRoot
	if ( rootNoMain.getType() == 'r' ){
	
		cout<<"The type of the root -element is correctly 'r' . "<<endl;
	}else{
		cerr<<"Error: The type of the root -element is "<<
			rootNoMain.getType()<<" but should be 'r' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cRoot
	if ( ! rootNoMain.isValidFibElement() ){
	
		cout<<"The root -element is correctly not a correct root -element. "<<endl;
	}else{
		cerr<<"Error: The root -element is a correct root -element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cRoot
	if ( ! rootNoMain.isMovable() ){
	
		cout<<"The root -element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The root -element is movebel."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cRoot
	if ( rootNoMain.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the root -element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the root -element is "<<
			rootNoMain.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}

	//check the getNextFibElement() methode from cRoot
	if ( rootNoMain.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the root -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the root -element is not NULL."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNextFibElement() methode from cRoot
	if ( rootNoMain.getFibElement( -1 ) == &rootEmpty3 ){
	
		cout<<"The previous fib -element for the root -element is correctly rootEmpty3. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the root -element is "<<
			rootNoMain.getFibElement( -1 ) << " and not not rootEmpty3."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNextFibElement() methode from cRoot
	if ( rootNoMain.getFibElement( -1 ) == &rootEmpty2 ){
	
		cout<<"The previous fib -element for the root -element is correctly rootEmpty2. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the root -element is "<<
			rootNoMain.getFibElement( -1 ) << " and not not rootEmpty2."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getSuperiorFibElement() methode from cRoot
	if ( rootNoMain.getSuperiorFibElement() == &rootEmpty3 ){
	
		cout<<"The superior fib -element for the root -element is correctly rootEmpty3. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the root -element is "<<
			rootNoMain.getSuperiorFibElement() << " and not not rootEmpty3."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an root -element with no superior"<<endl;
	
	cout<<"cPoint pointEmpty3;"<<endl;
	cPoint pointEmpty3;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootNoSuperior( &pointEmpty3 );"<<endl;
	cRoot rootNoSuperior( &pointEmpty3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootNoSuperior( NULL, &rootNoMain, &pointEmpty3 );"<<endl;
	cRoot rootNoSuperior( NULL, &rootNoMain, &pointEmpty3 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the getType() methode from cRoot
	if ( rootNoSuperior.getType() == 'r' ){
	
		cout<<"The type of the root -element is correctly 'r' . "<<endl;
	}else{
		cerr<<"Error: The type of the root -element is "<<
			rootNoSuperior.getType()<<" but should be 'r' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cRoot
	if ( rootNoSuperior.isValidFibElement() ){
	
		cout<<"The root -element is correctly a correct root -element. "<<endl;
	}else{
		cerr<<"Error: The root -element is not a correct root -element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cRoot
	if ( ! rootNoSuperior.isMovable() ){
	
		cout<<"The root -element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The root -element is movebel."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cRoot
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	if ( rootNoSuperior.getNumberOfElement() == 1 ){
		cout<<"The number of the fib -element for the root -element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the root -element is "<<
			rootNoSuperior.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	if ( rootNoSuperior.getNumberOfElement() == 3 ){
		cout<<"The number of the fib -element for the root -element is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the root -element is "<<
			rootNoSuperior.getNumberOfElement() <<", but should be 3."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR	

	//check the getNextFibElement() methode from cRoot
	if ( rootNoSuperior.getNextFibElement() == &pointEmpty3 ){
	
		cout<<"The next/ main fib -element for the root -element is correctly pointEmpty3. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the root -element is not pointEmpty3."<<endl;
		iReturn++;
	}

	//check the getNextFibElement() methode from cRoot
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	if ( rootNoSuperior.getFibElement( -1 ) == NULL ){
		cout<<"The previous fib -element for the root -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the root -element is "<<
			rootNoSuperior.getFibElement( -1 ) << " and not not NULL."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	if ( rootNoSuperior.getFibElement( -1 ) == &rootNoMain ){
		cout<<"The previous fib -element for the root -element is correctly rootMain2. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the root -element is "<<
			rootNoSuperior.getFibElement( -1 ) << " and not not rootMain2."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getSuperiorFibElement() methode from cRoot
	if ( rootNoSuperior.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the root -element is correctly rootMain2. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the root -element is "<<
			rootNoSuperior.getSuperiorFibElement() << " and not not rootMain2."<<endl;
		iReturn++;
	}


	return iReturn;
}


/**
 * This method tests the insertObjectInElement() method of the cRoot class.
 *
 * methods tested:
 * 	- bool insertObjectInElement( cFibElement *fibObject, 'u', 0, bool first=true, false );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testInsertObjectInElement( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing insertObjectInElement() for two root -elements"<<endl;

	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	cout<<"cRoot rootEmpty2;"<<endl;
	cRoot rootEmpty2;
	
	cout<<"rootEmpty1.insertObjectInElement( &rootEmpty2 );"<<endl;
	bool bObjectInserted = rootEmpty1.insertObjectInElement( &rootEmpty2 );

	//check the getType() methode from cRoot
	if ( ! bObjectInserted ){
	
		cout<<"Couldn't correctly insert a root -element in an root -element. "<<endl;
	}else{
		cerr<<"Error: Could insert a root -element in an root -element."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cRoot
	if ( ! rootEmpty1.isValidFibElement() ){
	
		cout<<"The root -element is correctly no correct root -element. "<<endl;
	}else{
		cerr<<"Error: The root -element is a correct root -element, but shouldn't be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cRoot
	if ( ! rootEmpty1.isMovable() ){
	
		cout<<"The root -element is correctly not movebel. "<<endl;
	}else{
		cerr<<"Error: The root -element is movebel."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cRoot
	if ( rootEmpty1.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the root -element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the root -element is "<<
			rootEmpty1.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cRoot
	if ( rootEmpty1.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the root -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the root -element is not NULL."<<endl;
		iReturn++;
	}

	//check the getNextFibElement() methode from cRoot
	if ( rootEmpty1.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the root -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the root -element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cRoot
	if ( rootEmpty1.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the root -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the root -element is "<<
			rootEmpty1.getSuperiorFibElement() << " and not not NULL."<<endl;
		iReturn++;
	}


	return iReturn;
}





/**
 * This method tests the getMultimediaInfo() method of the cRoot class.
 *
 * methods tested:
 * 	- cMultimediaInfo * getMultimediaInfo();
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testGetMultimediaInfo( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing getMultimediaInfo()"<<endl;

	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	cout<<"cRoot rootEmpty2;"<<endl;
	cRoot rootEmpty2;
	
	cout<<"multimediainfo1 = rootEmpty1.getMultimediaInfo();"<<endl;
	cMultimediaInfo * multimediainfo1 = rootEmpty1.getMultimediaInfo();
	cout<<"multimediainfo2 = rootEmpty2.getMultimediaInfo();"<<endl;
	cMultimediaInfo * multimediainfo2 = rootEmpty2.getMultimediaInfo();

	if ( multimediainfo1 != NULL ){
	
		cout<<"The root -element rootEmpty1 has an multimediainfo. "<<endl;
	}else{
		cerr<<"Error: The root -element rootEmpty1 has no multimediainfo, multimediainfo1 is NULL."<<endl;
		iReturn++;
		return iReturn;
	}

	if ( multimediainfo2 != NULL ){
	
		cout<<"The root -element rootEmpty2 has an multimediainfo. "<<endl;
	}else{
		cerr<<"Error: The root -element rootEmpty2 has no multimediainfo, multimediainfo2 is NULL."<<endl;
		iReturn++;
		return iReturn;
	}
	
	if ( multimediainfo2 != multimediainfo1 ){
	
		cout<<"The root -element rootEmpty1 and rootEmpty2 dosn't have the same multimediainfo. "<<endl;
	}else{
		cerr<<"Error: The root -element rootEmpty1 and rootEmpty2 have the same multimediainfo."<<endl;
		iReturn++;
	}

	cout<<"multimediainfo1->setFibVersion( 17 );"<<endl;
	multimediainfo1->setFibVersion( 17 );

	if ( rootEmpty1.getMultimediaInfo()->getFibVersion() == 17 ){
	
		cout<<"The fib -version of the rootEmpty1 could be changed in the multimediainfo1. "<<endl;
	}else{
		cerr<<"Error: The fib -version of the rootEmpty1 couldn't be changed correctly in the multimediainfo1."<<endl;
		iReturn++;
	}
	
	cout<<"multimediainfo2->setFibVersion( 13 );"<<endl;
	multimediainfo2->setFibVersion( 13 );

	if ( rootEmpty2.getMultimediaInfo()->getFibVersion() == 13 ){
	
		cout<<"The fib -version of the rootEmpty2 could be changed in the multimediainfo2. "<<endl;
	}else{
		cerr<<"Error: The fib -version of the rootEmpty2 couldn't be changed correctly in the multimediainfo2."<<endl;
		iReturn++;
	}

	if ( rootEmpty1.getMultimediaInfo()->getFibVersion() == 17 ){
	
		cout<<"The fib -version of the rootEmpty1 is correctly 17. "<<endl;
	}else{
		cerr<<"Error: The fib -version of the rootEmpty1 isn't 17, it is "<<
			rootEmpty1.getMultimediaInfo()->getFibVersion() <<" ."<<endl;
		iReturn++;
	}


	return iReturn;
}


/**
 * This method tests getOptionalPart() method of the cRoot class.
 *
 * methods tested:
 * 	- cOptionalPart * getOptionalPart();
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testGetOptionalPart( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing getOptionalPart()"<<endl;

	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	cout<<"cRoot rootEmpty2;"<<endl;
	cRoot rootEmpty2;
	
	cout<<"optionalPart1 = rootEmpty1.getOptionalPart();"<<endl;
	cOptionalPart * optionalPart1 = rootEmpty1.getOptionalPart();
	cout<<"optionalPart2 = rootEmpty2.getOptionalPart();"<<endl;
	cOptionalPart * optionalPart2 = rootEmpty2.getOptionalPart();


	if ( optionalPart1 != NULL ){
	
		cout<<"The root -element rootEmpty1 has an optionalpart. "<<endl;
	}else{
		cerr<<"Error: The root -element rootEmpty1 has no optionalpart, optionalPart1 is NULL."<<endl;
		iReturn++;
		return iReturn;
	}

	if ( optionalPart2 != NULL ){
	
		cout<<"The root -element rootEmpty2 has an optionalpart. "<<endl;
	}else{
		cerr<<"Error: The root -element rootEmpty2 has no optionalpart, optionalPart2 is NULL."<<endl;
		iReturn++;
		return iReturn;
	}
	
	if ( optionalPart1 != optionalPart2 ){
	
		cout<<"The root -element rootEmpty1 and rootEmpty2 dosn't have the same optionalpart. "<<endl;
	}else{
		cerr<<"Error: The root -element rootEmpty1 and rootEmpty2 have the same optionalpart."<<endl;
		iReturn++;
	}

	if ( rootEmpty1.getOptionalPart()->getNumberOfEntries() == 0 ){
	
		cout<<"The rootEmpty1 optionalpart has no entries. "<<endl;
	}else{
		cerr<<"Error: The rootEmpty1 optionalpart has entries."<<endl;
		iReturn++;
	}

	cout<<"optionalPart1->addEntry( \"key\", \"value\" );"<<endl;
	optionalPart1->addEntry( "key", "value" );

	if ( rootEmpty1.getOptionalPart()->getNumberOfEntries() == 1 ){
	
		cout<<"The to the rootEmpty1 optionalpart an entry could be added. "<<endl;
	}else{
		cerr<<"Error: The to the rootEmpty1 optionalpart an entry could be added."<<endl;
		iReturn++;
	}

	if ( rootEmpty2.getOptionalPart()->getNumberOfEntries() == 0 ){
	
		cout<<"The rootEmpty2 optionalpart has no entries. "<<endl;
	}else{
		cerr<<"Error: The rootEmpty2 optionalpart has entries."<<endl;
		iReturn++;
	}


	return iReturn;
}


/**
 * This method tests the checksum methods of the cRoot class.
 *
 * methods tested:
 * 	- cVectorChecksum * getChecksum();
 * 	- void setChecksum( const cVectorChecksum * checksum = NULL);
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testChecksum( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing methods for the checksum"<<endl;

	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;

	cout<<"rootEmpty1.getChecksum()"<<endl;
	if ( rootEmpty1.getChecksum() == NULL ){
	
		cout<<"The rootEmpty1 has no checksum (NULL is returned). "<<endl;
	}else{
		cerr<<"Error: The rootEmpty1 has a checksum."<<endl;
		iReturn++;
	}
	
	cout<<"cVectorChecksum checksum1;"<<endl;
	cVectorChecksum checksum1;

	cout<<"checksum1.setValue( 1, 1 );"<<endl;
	checksum1.setValue( 1, 1 );
	
	cout<<"rootEmpty1.setChecksum( &checksum1 );"<<endl;
	rootEmpty1.setChecksum( &checksum1 );
	
	if ( rootEmpty1.getChecksum() != NULL ){
	
		cout<<"The rootEmpty1 has a checksum. "<<endl;
	}else{
		cerr<<"Error: The rootEmpty1 has no checksum (NULL is returned)."<<endl;
		iReturn++;
		return iReturn;
	}

	if ( checksum1 == (*rootEmpty1.getChecksum()) ){
	
		cout<<"The rootEmpty1 checksum correctly equal to checksum1. "<<endl;
	}else{
		cerr<<"Error: The rootEmpty1 checksum not equal to checksum1."<<endl;
		iReturn++;
	}

	if ( &checksum1 != rootEmpty1.getChecksum() ){
	
		cout<<"The rootEmpty1 checksum correctly not the checksum1 object. "<<endl;
	}else{
		cerr<<"Error: The rootEmpty1 checksum correctly not the checksum1 object."<<endl;
		iReturn++;
	}

	cout<<"rootEmpty1.getChecksum()->setValue( 2, 2 );"<<endl;
	rootEmpty1.getChecksum()->setValue( 2, 2 );

	if ( ! ( checksum1 == (*rootEmpty1.getChecksum()) ) ){
	
		cout<<"The rootEmpty1 checksum correctly not equal anymore to to checksum1. "<<endl;
	}else{
		cerr<<"Error: The rootEmpty1 checksum is still equal to checksum1."<<endl;
		iReturn++;
	}

	cout<<"rootEmpty1.setChecksum( NULL );"<<endl;
	rootEmpty1.setChecksum( NULL );

	cout<<"rootEmpty1.getChecksum()"<<endl;
	if ( rootEmpty1.getChecksum() == NULL ){
	
		cout<<"The rootEmpty1 has no checksum (NULL is returned). "<<endl;
	}else{
		cerr<<"Error: The rootEmpty1 has a checksum."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the domain methods of the cRoot class.
 *
 * methods tested:
 * 	- cDomains * getDomains();
 * 	- cDomains getValidDomains() const;
 * 	- cDomains * getValueDomains();
 * 	- cDomains getValidValueDomains() const;
 * 	- unsignedIntFib getNumberOfDimensions() const;
 * 	- unsignedIntFib getDimensionMapping( unsignedIntFib iDimensionNumber ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testDomains( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing getDomains()"<<endl;

	cout<<"cRoot root1;"<<endl;
	cRoot root1;

	cout<<"root1.getDomains()"<<endl;
	if ( root1.getDomains() != NULL ){
	
		cout<<"The root1 has domains. "<<endl;
	}else{
		cerr<<"Error: The root1 has no domains (NULL is returned)."<<endl;
		iReturn++;
		return iReturn;
	}

	if ( root1.getDomains()->getNumberOfDomains() == 0 ){
	
		cout<<"The root1 domains are empty. "<<endl;
	}else{
		cerr<<"Error: The root1 domains are not empty."<<endl;
		iReturn++;
	}
	//check getNumberOfDimensions()
	if ( root1.getNumberOfDimensions() == 2 ){
	
		cout<<"The root1 number of dimensions is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The root1 number of dimensions is "<<
			root1.getNumberOfDimensions() <<", but should be 2 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( root1.getDimensionMapping( 1 ) == 1 ){
	
		cout<<"The root1 1'th dimensions goes correctly in dirction 1. "<<endl;
	}else{
		cerr<<"Error: The root1 1'th dimensions goes in direction "<<
			root1.getDimensionMapping( 1 ) <<", but should go in direction 1 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( root1.getDimensionMapping( 2 ) == 2 ){
	
		cout<<"The root1 2'th dimensions goes correctly in dirction 2. "<<endl;
	}else{
		cerr<<"Error: The root1 2'th dimensions goes in direction "<<
			root1.getDimensionMapping( 2 ) <<", but should go in direction 2 ."<<endl;
		iReturn++;
	}

	cDomains domains;
	cDomains domainsValueValid;
	
	cout<<"cTypeVariable typeVariable1;"<<endl;
	cTypeVariable typeVariable1;
	cout<<"cDomainNaturalNumberBit domainNaturalNumber1( 1 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumber1( 1 );
	
	cout<<"root1.getDomains()->addDomain( typeVariable1, domainNaturalNumber1 );"<<endl;
	root1.getDomains()->addDomain( typeVariable1, domainNaturalNumber1 );
	domains.addDomain( typeVariable1, domainNaturalNumber1 );
	domainsValueValid.addDomain( typeVariable1, domainNaturalNumber1 );

	if ( root1.getDomains()->getNumberOfDomains() == 1 ){
	
		cout<<"The root1 domains have one element. "<<endl;
	}else{
		cerr<<"Error: The root1 domains have not one element, but "<<
			root1.getDomains()->getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	if ( domains == (*root1.getDomains()) ){
	
		cout<<"The root1 domains have the correct elements. "<<endl;
	}else{
		cerr<<"Error: The root1 domains have not the correct elements."<<endl;
		iReturn++;
	}
	//check getNumberOfDimensions()
	if ( root1.getNumberOfDimensions() == 2 ){
	
		cout<<"The root1 number of dimensions is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The root1 number of dimensions is "<<
			root1.getNumberOfDimensions() <<", but should be 2 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( root1.getDimensionMapping( 1 ) == 1 ){
	
		cout<<"The root1 1'th dimensions goes correctly in dirction 1 . "<<endl;
	}else{
		cerr<<"Error: The root1 1'th dimensions goes in direction "<<
			root1.getDimensionMapping( 1 ) <<", but should go in direction 1 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( root1.getDimensionMapping( 2 ) == 2 ){
	
		cout<<"The root1 2'th dimensions goes correctly in dirction 2. "<<endl;
	}else{
		cerr<<"Error: The root1 2'th dimensions goes in direction "<<
			root1.getDimensionMapping( 2 ) <<", but should go in direction 2 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing getValidDomains()"<<endl;
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootSub1( NULL, &root1 );"<<endl;
	cRoot rootSub1( NULL, &root1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootSub1( &root1 );"<<endl;
	cRoot rootSub1( &root1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"rootSub1.getDomains()"<<endl<<flush;
	if ( rootSub1.getDomains() != NULL ){
	
		cout<<"The rootSub1 has domains. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 has no domains (NULL is returned)."<<endl;
		iReturn++;
		return iReturn;
	}
	if ( rootSub1.getDomains()->getNumberOfDomains() == 0 ){
	
		cout<<"The rootSub1 domains are empty. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 domains are not empty."<<endl;
		iReturn++;
	}

	cout<<"rootSub1.getValidDomains()"<<endl;
	if ( rootSub1.getValidDomains().getNumberOfDomains() == 1 ){
	
		cout<<"The rootSub1 validdomains have one element. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 validdomains have not one element, but "<<
			rootSub1.getValidDomains().getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	if ( domains == rootSub1.getValidDomains() ){
	
		cout<<"The rootSub1 validdomains have the correct elements. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 validdomains have not the correct elements."<<endl;
		iReturn++;
	}

	if ( root1.getDomains()->getDomain( 1 ) == rootSub1.getValidDomains().getDomain( 1 ) ){
	
		cout<<"The rootSub1 validdomains have a reverence domain of the root1 domains. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 validdomains have not a reverence domain of the root1 domains."<<endl;
		iReturn++;
	}
	//check getNumberOfDimensions()
	if ( rootSub1.getNumberOfDimensions() == 2 ){
	
		cout<<"The rootSub1 number of dimensions is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 number of dimensions is "<<
			root1.getNumberOfDimensions() <<", but should be 2 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( rootSub1.getDimensionMapping( 1 ) == 1 ){
	
		cout<<"The rootSub1 1'th dimensions goes correctly in dirction 1. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 1'th dimensions goes in direction "<<
			root1.getDimensionMapping( 1 ) <<", but should go in direction 1 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( rootSub1.getDimensionMapping( 2 ) == 2 ){
	
		cout<<"The rootSub1 2'th dimensions goes correctly in dirction 2. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 2'th dimensions goes in direction "<<
			root1.getDimensionMapping( 2 ) <<", but should go in direction 2 ."<<endl;
		iReturn++;
	}

	cout<<"cTypeDimension testTypeDimensionD1( 1 ); "<<endl<<flush;
	cTypeDimension testTypeDimensionD1( 1 );
	cout<<"vector<unsignedIntFib> dimensionMapping;"<<endl;
	vector<unsignedIntFib> dimensionMapping;
	cout<<"dimensionMapping.push_back( 7 );"<<endl;
	dimensionMapping.push_back( 7 );
	cout<<"dimensionMapping.push_back( 6 );"<<endl;
	dimensionMapping.push_back( 6 );
	cout<<"dimensionMapping.push_back( 5 );"<<endl;
	dimensionMapping.push_back( 5 );
	cout<<"cTypeDimension testTypeDimensionD3( dimensionMapping ); "<<endl<<flush;
	cTypeDimension testTypeDimensionD3( dimensionMapping );
	cout<<"cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB ) "<<endl<<flush;
	cTypeProperty testTypePropertyColorRGB( cTypeProperty::COLOR_RGB );
	cout<<"cTypeProperty testTypePropertyColorSW( cTypeProperty::COLOR_GRAYSCALE ) "<<endl<<flush;
	cTypeProperty testTypePropertyColorSW( cTypeProperty::COLOR_GRAYSCALE );


	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains1( 1 );"<<endl<<flush;
	vector<cDomainSingle*> vecDomains1( 1 );
	cout<<"vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl<<flush;
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomainD1( vecDomains1 );"<<endl<<flush;
	cDomainVector vectorDomainD1( vecDomains1 );
	delete vecDomains1[ 0 ];
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomains2D1( 1 );"<<endl<<flush;
	vector<cDomainSingle*> vecDomains2D1( 1 );
	cout<<"vecDomains2D1[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl<<flush;
	vecDomains2D1[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomain2D1( vecDomains2D1 );"<<endl<<flush;
	cDomainVector vectorDomain2D1( vecDomains2D1 );
	delete vecDomains2D1[ 0 ];

	//create vector domain with tree elements
	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl<<flush;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl<<flush;
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 1 );"<<endl<<flush;
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 1 );"<<endl<<flush;
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomain1D3( vecDomains3 );"<<endl<<flush;
	cDomainVector vectorDomain1D3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	//create vector domain with two elements
	cout<<"vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl<<flush;
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 2 );"<<endl<<flush;
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 2 );"<<endl<<flush;
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomain2D3( vecDomains3 );"<<endl<<flush;
	cDomainVector vectorDomain2D3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	
	cout<<"root1.getDomains()->addDomain( testTypeDimensionD1, vectorDomainD1 );"<<endl;
	root1.getDomains()->addDomain( testTypeDimensionD1, vectorDomainD1 );
	domains.addDomain( testTypeDimensionD1, vectorDomainD1 );
	domainsValueValid.addDomain( testTypeDimensionD1, vectorDomainD1 );
	cout<<"rootSub1.getDomains()->addDomain( testTypeDimensionD3, vectorDomain1D3 );"<<endl;
	rootSub1.getDomains()->addDomain( testTypeDimensionD3, vectorDomain1D3 );
	domains.addDomain( testTypeDimensionD3, vectorDomain1D3 );
	domainsValueValid.addDomain( testTypeDimensionD3, vectorDomain1D3 );

	cout<<"root1.getDomains()->addDomain( testTypePropertyColorRGB, vectorDomain1D3 );"<<endl;
	root1.getDomains()->addDomain( testTypePropertyColorRGB, vectorDomain1D3 );
	domains.addDomain( testTypePropertyColorRGB, vectorDomain1D3 );
	domainsValueValid.addDomain( testTypePropertyColorRGB, vectorDomain1D3 );
	cout<<"root1.getDomains()->addDomain( testTypePropertyColorSW, vectorDomainD1 );"<<endl;
	root1.getDomains()->addDomain( testTypePropertyColorSW, vectorDomainD1 );
	domains.addDomain( testTypePropertyColorSW, vectorDomainD1 );
	domainsValueValid.addDomain( testTypePropertyColorSW, vectorDomainD1 );

	cout<<"rootSub1.getDomains()->addDomain( testTypePropertyColorRGB, vectorDomain2D3 );"<<endl;
	rootSub1.getDomains()->addDomain( testTypePropertyColorRGB, vectorDomain2D3 );
	domains.addDomain( testTypePropertyColorRGB, vectorDomain2D3 );
	domainsValueValid.addDomain( testTypePropertyColorRGB, vectorDomain2D3 );


	if ( root1.getDomains()->getNumberOfDomains() == 4 ){
	
		cout<<"The root1 domains have 4 elements. "<<endl;
	}else{
		cerr<<"Error: The root1 domains have not 4 elements, but "<<
			root1.getDomains()->getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	if ( rootSub1.getDomains()->getNumberOfDomains() == 2 ){
	
		cout<<"The rootSub1 domains have 2 elements. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 domains have not 2 elements, but "<<
			rootSub1.getDomains()->getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	cout<<"rootSub1.getValidDomains().getNumberOfDomains()"<<endl;
	if ( rootSub1.getValidDomains().getNumberOfDomains() == 4 ){
	
		cout<<"The rootSub1 validdomains have 4 elements. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 validdomains have not 4 elements, but "<<
			rootSub1.getValidDomains().getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	if ( domains == rootSub1.getValidDomains() ){
	
		cout<<"The rootSub1 validdomains have the correct elements. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 validdomains have not the correct elements."<<endl;
		iReturn++;
	}
	cout<<"root1.getValidDomains().getNumberOfDomains()"<<endl;
	if ( root1.getValidDomains().getNumberOfDomains() == 4 ){
	
		cout<<"The root1 validdomains have 4 elements. "<<endl;
	}else{
		cerr<<"Error: The root1 validdomains have not 4 elements, but "<<
			root1.getValidDomains().getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	//check getNumberOfDimensions()
	if ( root1.getNumberOfDimensions() == 1 ){
	
		cout<<"The root1 number of dimensions is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The root1 number of dimensions is "<<
			root1.getNumberOfDimensions() <<", but should be 1 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( root1.getDimensionMapping( 1 ) == 1 ){
	
		cout<<"The root1 1'th dimensions goes correctly in dirction 1. "<<endl;
	}else{
		cerr<<"Error: The root1 1'th dimensions goes in direction "<<
			root1.getDimensionMapping( 1 ) <<", but should go in direction 1 ."<<endl;
		iReturn++;
	}
	//check getNumberOfDimensions()
	if ( rootSub1.getNumberOfDimensions() == 3 ){
	
		cout<<"The rootSub1 number of dimensions is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 number of dimensions is "<<
			root1.getNumberOfDimensions() <<", but should be 3 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( rootSub1.getDimensionMapping( 1 ) == 7 ){
	
		cout<<"The rootSub1 1'th dimensions goes correctly in dirction 7. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 1'th dimensions goes in direction "<<
			root1.getDimensionMapping( 1 ) <<", but should go in direction 7 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( rootSub1.getDimensionMapping( 2 ) == 6 ){
	
		cout<<"The rootSub1 2'th dimensions goes correctly in dirction 6. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 2'th dimensions goes in direction "<<
			root1.getDimensionMapping( 2 ) <<", but should go in direction 6 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( rootSub1.getDimensionMapping( 3 ) == 5 ){
	
		cout<<"The rootSub1 3'th dimensions goes correctly in dirction 5. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 3'th dimensions goes in direction "<<
			root1.getDimensionMapping( 3 ) <<", but should go in direction 5 ."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing getValueDomains()"<<endl;

	cout<<"root1.getValueDomains()"<<endl;
	if ( root1.getValueDomains() != NULL ){
	
		cout<<"The root1 has domains. "<<endl;
	}else{
		cerr<<"Error: The root1 has no domains (NULL is returned)."<<endl;
		iReturn++;
		return iReturn;
	}

	if ( root1.getValueDomains()->getNumberOfDomains() == 0 ){
	
		cout<<"The root1 domains are empty. "<<endl;
	}else{
		cerr<<"Error: The root1 domains are not empty."<<endl;
		iReturn++;
	}

	cDomains domainsValue;
	
	cout<<"cTypeVariable typeVariable2;"<<endl;
	cTypeVariable typeVariable2;
	cout<<"cDomainNaturalNumberBit domainNaturalNumber7( 7 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumber7( 7 );
	
	cout<<"root1.getValueDomains()->addDomain( typeVariable2, domainNaturalNumber7 );"<<endl;
	root1.getValueDomains()->addDomain( typeVariable2, domainNaturalNumber7 );
	domainsValue.addDomain( typeVariable2, domainNaturalNumber7 );
	domainsValueValid.addDomain( typeVariable2, domainNaturalNumber7 );

	if ( root1.getValueDomains()->getNumberOfDomains() == 1 ){
	
		cout<<"The root1 domains have one element. "<<endl;
	}else{
		cerr<<"Error: The root1 domains have not one element, but "<<
			root1.getValueDomains()->getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	if ( domainsValue == (*root1.getValueDomains()) ){
	
		cout<<"The root1 domains have the correct elements. "<<endl;
	}else{
		cerr<<"Error: The root1 domains have not the correct elements."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing getValidValueDomains()"<<endl;
	
	cout<<"rootSub1.getValueDomains()"<<endl<<flush;
	if ( rootSub1.getValueDomains() != NULL ){
	
		cout<<"The rootSub1 has domains. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 has no domains (NULL is returned)."<<endl;
		iReturn++;
		return iReturn;
	}
	if ( rootSub1.getValueDomains()->getNumberOfDomains() == 0 ){
	
		cout<<"The rootSub1 domains are empty. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 domains are not empty."<<endl;
		iReturn++;
	}

	cout<<"cDomains domainsValidvaluesRootSub1 = rootSub1.getValidValueDomains()"<<endl;
	cDomains domainsVVRootSub1 = rootSub1.getValidValueDomains();
	if ( domainsVVRootSub1.getNumberOfDomains() == 
			domainsValueValid.getNumberOfDomains() ){
	
		cout<<"The rootSub1 validdomains have "<<
			domainsValueValid.getNumberOfDomains()<<" elements. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 validdomains have not "<<
			domainsValueValid.getNumberOfDomains()<<" element, but "<<
			domainsVVRootSub1.getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	if ( domainsValueValid == domainsVVRootSub1 ){
	
		cout<<"The rootSub1 validvaluedomains have the correct elements. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 validvaluedomains have not the correct elements."<<endl;
		iReturn++;
	}
	if ( root1.getValueDomains()->getDomain( 1 ) == domainsVVRootSub1.getDomain( 1 ) ){
	
		cout<<"The rootSub1 validdomains have a reverence domainsValue of the root1 domains. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 validdomains have not a reverence domainsValue of the root1 domains."<<endl;
		iReturn++;
	}


	cout<<"vector<unsignedIntFib> dimensionMapping2;"<<endl;
	vector<unsignedIntFib> dimensionMapping2;
	cout<<"dimensionMapping2.push_back( 17 );"<<endl;
	dimensionMapping2.push_back( 17 );
	cout<<"dimensionMapping2.push_back( 16 );"<<endl;
	dimensionMapping2.push_back( 16 );
	cout<<"dimensionMapping2.push_back( 15 );"<<endl;
	dimensionMapping2.push_back( 15 );
	cout<<"cTypeDimension testTypeDimension2D3( dimensionMapping2 ); "<<endl<<flush;
	cTypeDimension testTypeDimension2D3( dimensionMapping2 );

	//create vector domainsValue with one elements
	cout<<"vector<cDomainSingle*> vecDomains3D1( 1 );"<<endl<<flush;
	vector<cDomainSingle*> vecDomains3D1( 1 );
	cout<<"vecDomains3D1[ 0 ] = new cDomainNaturalNumberBit( 11 );"<<endl<<flush;
	vecDomains3D1[ 0 ] = new cDomainNaturalNumberBit( 11 );
	cout<<"cDomainVector vectorDomain3D1( vecDomains3D1 );"<<endl<<flush;
	cDomainVector vectorDomain3D1( vecDomains3D1 );
	delete vecDomains3D1[ 0 ];
	
	//create vector domainsValue with 1 elements
	cout<<"vector<cDomainSingle*> vecDomains4D1( 1 );"<<endl<<flush;
	vector<cDomainSingle*> vecDomains4D1( 1 );
	cout<<"vecDomains4D1[ 0 ] = new cDomainNaturalNumberBit( 2 );"<<endl<<flush;
	vecDomains4D1[ 0 ] = new cDomainNaturalNumberBit( 2 );
	cout<<"cDomainVector vectorDomain4D1( vecDomains4D1 );"<<endl<<flush;
	cDomainVector vectorDomain4D1( vecDomains4D1 );
	delete vecDomains4D1[ 0 ];

	//create vector domainsValue with tree elements
	cout<<"vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 11 );"<<endl<<flush;
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 11 );
	cout<<"vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 11 );"<<endl<<flush;
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 11 );
	cout<<"vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 11 );"<<endl<<flush;
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 11 );
	cout<<"cDomainVector vectorDomain3D3( vecDomains3 );"<<endl<<flush;
	cDomainVector vectorDomain3D3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	//create vector domainsValue with two elements
	cout<<"vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 12 );"<<endl<<flush;
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 12 );
	cout<<"vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 12 );"<<endl<<flush;
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 12 );
	cout<<"vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 12 );"<<endl<<flush;
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 12 );
	cout<<"cDomainVector vectorDomain4D3( vecDomains3 );"<<endl<<flush;
	cDomainVector vectorDomain4D3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	
	cout<<"root1.getValueDomains()->addDomain( testTypeDimensionD1, vectorDomain3D1 );"<<endl;
	root1.getValueDomains()->addDomain( testTypeDimensionD1, vectorDomain3D1 );
	domainsValue.addDomain( testTypeDimensionD1, vectorDomain3D1 );
	cout<<"rootSub1.getValueDomains()->addDomain( testTypeDimension2D3, vectorDomain3D3 );"<<endl;
	rootSub1.getValueDomains()->addDomain( testTypeDimension2D3, vectorDomain3D3 );
	domainsValue.addDomain( testTypeDimension2D3, vectorDomain3D3 );

	cout<<"root1.getValueDomains()->addDomain( testTypePropertyColorRGB, vectorDomain3D3 );"<<endl;
	root1.getValueDomains()->addDomain( testTypePropertyColorRGB, vectorDomain3D3 );
	domainsValue.addDomain( testTypePropertyColorRGB, vectorDomain3D3 );
	cout<<"root1.getValueDomains()->addDomain( testTypePropertyColorSW, vectorDomain3D1 );"<<endl;
	root1.getValueDomains()->addDomain( testTypePropertyColorSW, vectorDomain3D1 );
	domainsValue.addDomain( testTypePropertyColorSW, vectorDomain3D1 );

	cout<<"rootSub1.getValueDomains()->addDomain( testTypePropertyColorRGB, vectorDomain4D3 );"<<endl;
	rootSub1.getValueDomains()->addDomain( testTypePropertyColorRGB, vectorDomain4D3 );
	domainsValue.addDomain( testTypePropertyColorRGB, vectorDomain4D3 );


	if ( root1.getValueDomains()->getNumberOfDomains() == 4 ){
	
		cout<<"The root1 domains have 4 elements. "<<endl;
	}else{
		cerr<<"Error: The root1 domains have not 4 elements, but "<<
			root1.getValueDomains()->getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	if ( rootSub1.getValueDomains()->getNumberOfDomains() == 2 ){
	
		cout<<"The rootSub1 domains have 2 elements. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 domains have not 2 elements, but "<<
			rootSub1.getValueDomains()->getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	cout<<"rootSub1.getValidValueDomains().getNumberOfDomains()"<<endl;
	if ( rootSub1.getValidValueDomains().getNumberOfDomains() == 4 ){
	
		cout<<"The rootSub1 validdomains have 4 elements. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 validdomains have not 4 elements, but "<<
			rootSub1.getValidValueDomains().getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	if ( domainsValue == rootSub1.getValidValueDomains() ){
	
		cout<<"The rootSub1 validdomains have the correct elements. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 validdomains have not the correct elements."<<endl;
		iReturn++;
	}
	cout<<"root1.getValidValueDomains().getNumberOfDomains()"<<endl;
	if ( root1.getValidValueDomains().getNumberOfDomains() == 4 ){
	
		cout<<"The root1 validdomains have 4 elements. "<<endl;
	}else{
		cerr<<"Error: The root1 validdomains have not 4 elements, but "<<
			root1.getValidValueDomains().getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	//check getNumberOfDimensions()
	if ( root1.getNumberOfDimensions() == 1 ){
	
		cout<<"The root1 number of dimensions is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The root1 number of dimensions is "<<
			root1.getNumberOfDimensions() <<", but should be 1 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( root1.getDimensionMapping( 1 ) == 1 ){
	
		cout<<"The root1 1'th dimensions goes correctly in dirction 1. "<<endl;
	}else{
		cerr<<"Error: The root1 1'th dimensions goes in direction "<<
			root1.getDimensionMapping( 1 ) <<", but should go in direction 1 ."<<endl;
		iReturn++;
	}
	//check getNumberOfDimensions()
	if ( rootSub1.getNumberOfDimensions() == 3 ){
	
		cout<<"The rootSub1 number of dimensions is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 number of dimensions is "<<
			root1.getNumberOfDimensions() <<", but should be 3 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( rootSub1.getDimensionMapping( 1 ) == 7 ){
	
		cout<<"The rootSub1 1'th dimensions goes correctly in dirction 7. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 1'th dimensions goes in direction "<<
			root1.getDimensionMapping( 1 ) <<", but should go in direction 7 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( rootSub1.getDimensionMapping( 2 ) == 6 ){
	
		cout<<"The rootSub1 2'th dimensions goes correctly in dirction 6. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 2'th dimensions goes in direction "<<
			root1.getDimensionMapping( 2 ) <<", but should go in direction 6 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( rootSub1.getDimensionMapping( 3 ) == 5 ){
	
		cout<<"The rootSub1 3'th dimensions goes correctly in dirction 5. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 3'th dimensions goes in direction "<<
			root1.getDimensionMapping( 3 ) <<", but should go in direction 5 ."<<endl;
		iReturn++;
	}


//getDomains() erneut prüfen
	cout<<endl<<"Checking the domains again: "<<endl;
	if ( root1.getDomains()->getNumberOfDomains() == 4 ){
	
		cout<<"The root1 domains have 4 elements. "<<endl;
	}else{
		cerr<<"Error: The root1 domains have not 4 elements, but "<<
			root1.getDomains()->getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	if ( rootSub1.getDomains()->getNumberOfDomains() == 2 ){
	
		cout<<"The rootSub1 domains have 2 elements. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 domains have not 2 elements, but "<<
			rootSub1.getDomains()->getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	cout<<"rootSub1.getValidDomains().getNumberOfDomains()"<<endl;
	if ( rootSub1.getValidDomains().getNumberOfDomains() == 4 ){
	
		cout<<"The rootSub1 validdomains have 4 elements. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 validdomains have not 4 elements, but "<<
			rootSub1.getValidDomains().getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	if ( domains == rootSub1.getValidDomains() ){
	
		cout<<"The rootSub1 validdomains have the correct elements. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 validdomains have not the correct elements."<<endl;
		iReturn++;
	}
	cout<<"root1.getValidDomains().getNumberOfDomains()"<<endl;
	if ( root1.getValidDomains().getNumberOfDomains() == 4 ){
	
		cout<<"The root1 validdomains have 4 elements. "<<endl;
	}else{
		cerr<<"Error: The root1 validdomains have not 4 elements, but "<<
			root1.getValidDomains().getNumberOfDomains() <<" ."<<endl;
		iReturn++;
	}
	//check getNumberOfDimensions()
	if ( root1.getNumberOfDimensions() == 1 ){
	
		cout<<"The root1 number of dimensions is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The root1 number of dimensions is "<<
			root1.getNumberOfDimensions() <<", but should be 1 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( root1.getDimensionMapping( 1 ) == 1 ){
	
		cout<<"The root1 1'th dimensions goes correctly in dirction 1. "<<endl;
	}else{
		cerr<<"Error: The root1 1'th dimensions goes in direction "<<
			root1.getDimensionMapping( 1 ) <<", but should go in direction 1 ."<<endl;
		iReturn++;
	}
	//check getNumberOfDimensions()
	if ( rootSub1.getNumberOfDimensions() == 3 ){
	
		cout<<"The rootSub1 number of dimensions is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 number of dimensions is "<<
			root1.getNumberOfDimensions() <<", but should be 3 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( rootSub1.getDimensionMapping( 1 ) == 7 ){
	
		cout<<"The rootSub1 1'th dimensions goes correctly in dirction 7. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 1'th dimensions goes in direction "<<
			root1.getDimensionMapping( 1 ) <<", but should go in direction 7 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( rootSub1.getDimensionMapping( 2 ) == 6 ){
	
		cout<<"The rootSub1 2'th dimensions goes correctly in dirction 6. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 2'th dimensions goes in direction "<<
			root1.getDimensionMapping( 2 ) <<", but should go in direction 6 ."<<endl;
		iReturn++;
	}
	//check getDimensionMapping()
	if ( rootSub1.getDimensionMapping( 3 ) == 5 ){
	
		cout<<"The rootSub1 3'th dimensions goes correctly in dirction 5. "<<endl;
	}else{
		cerr<<"Error: The rootSub1 3'th dimensions goes in direction "<<
			root1.getDimensionMapping( 3 ) <<", but should go in direction 5 ."<<endl;
		iReturn++;
	}


	return iReturn;
}


/**
 * This method tests the methods for the input variables of the cRoot class.
 *
 * methods tested:
 * 	- unsignedIntFib getNumberOfInputVariables() const;
 * 	- bool setNumberOfInputVariables( unsignedIntFib uiNumberOfInputVariables );
 * 	- list<cFibVariable*> getInputVariables();
 * 	- cFibVariable * getInputVariable( unsignedIntFib uiNumberOfInputVariable );
 * 	- doubleFib getStandardValueOfInputVariable( unsignedIntFib uiNumberOfInputVariable ) const;
 * 	- bool setStandardValueOfInputVariable( unsignedIntFib uiNumberOfInputVariable, doubleFib dValue );
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- bool isUsedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool equalValuesSet( const cFibVariable * variableOwn, const cFibElement & fibElement, const cFibVariable * variable ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testInputVariables( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the input variables methods"<<endl;

	cout<<"cRoot root1;"<<endl;
	cRoot root1;
	//test getNumberOfInputVariables()
	if ( root1.getNumberOfInputVariables() == 0 ){
	
		cout<<"The root1 has correctly no input variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has input variables."<<endl;
		iReturn++;
	}

	//test setNumberOfInputVariables()
	unsigned int uiNumberOfInputVariables = 4;
	cout<<"root1.setNumberOfInputVariables( "<< uiNumberOfInputVariables <<" ); "<<endl;
	bool bInputVariablesSet = root1.setNumberOfInputVariables( uiNumberOfInputVariables );
	if ( bInputVariablesSet ){
	
		cout<<"Could change the number of input variables. "<<endl;
	}else{
		cerr<<"Error: Couldn't change the number of input variables."<<endl;
		iReturn++;
	}
	//test getNumberOfInputVariables()
	if ( root1.getNumberOfInputVariables() == uiNumberOfInputVariables ){
	
		cout<<"The root1 has correctly "<< uiNumberOfInputVariables <<" input variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has "<< root1.getNumberOfInputVariables() <<
			" input variables, but should have "<< uiNumberOfInputVariables <<" ."<<endl;
		iReturn++;
	}

	for ( unsigned int uiInVar1 = 1; uiInVar1 < uiNumberOfInputVariables; uiInVar1++ ){
		for ( unsigned int uiInVar2 = uiInVar1 + 1; uiInVar2 <= uiNumberOfInputVariables; uiInVar2++ ){
			if ( root1.getInputVariable( uiInVar1 ) == root1.getInputVariable( uiInVar2 ) ){
				cerr<<"Error: The root1 "<< uiInVar1 <<
					" input variable is the same object as the "<< uiInVar2
					<<" input variable."<<endl;
				iReturn++;
			}
		}
	}
	cout<<"liInVariables = root1.getInputVariables();"<<endl;
	list<cFibVariable*> liInVariables = root1.getInputVariables();
	if ( liInVariables.size() == uiNumberOfInputVariables ){
	
		cout<<"The root1 gives back a input variables list with correct size. "<<endl;
	}else{
		cerr<<"Error: The root1 gives back a input variables list with size "<<
			liInVariables.size() <<", but the size should be "<<
			uiNumberOfInputVariables <<" ."<<endl;
		iReturn++;
	}
	list<cFibVariable*>::iterator itrInVariables = liInVariables.begin();
	for ( unsigned int uiInVar1 = 1; (uiInVar1 <= uiNumberOfInputVariables) &&
			itrInVariables != liInVariables.end() ; uiInVar1++, itrInVariables++ ){
		if ( root1.getInputVariable( uiInVar1 ) != (*itrInVariables) ){
			cerr<<"Error: The root1 gives back a input variables list with "<<
				"the wrong "<< uiInVar1 <<"'th variable object ."<<endl;
			iReturn++;
		}
	}
	//check isDefinedVariable()
	cout<<"cFibVariable fibVariable = cFibVariable( &root1 );"<<endl;
	cFibVariable fibVariable = cFibVariable( &root1 );
	if ( ! root1.isDefinedVariable( &fibVariable ) ){
	
		cout<<"The fibVariable is correctly not defined by the root -element. "<<endl;
	}else{
		cerr<<"Error: The fibVariable is defined by the root -element."<<endl;
		iReturn++;
	}
	for ( unsigned int uiInVar1 = 1; (uiInVar1 <= uiNumberOfInputVariables); uiInVar1++ ){
		if ( ! root1.isDefinedVariable( root1.getInputVariable( uiInVar1 ) ) ){
			cerr<<"Error: The root1 defines the variable "<< uiInVar1 <<
				", but dosn't say so."<<endl;
			iReturn++;
		}
	}
	//check getDefinedVariables( ED_POSITION )
	cout<<"liInVariables = root1.getDefinedVariables( ED_POSITION );"<<endl;
	list<cFibVariable*> liDefinedVariables = root1.getDefinedVariables( ED_POSITION );
	if ( liDefinedVariables.size() == uiNumberOfInputVariables ){
	
		cout<<"The root1 gives back a defined variables list with correct size. "<<endl;
	}else{
		cerr<<"Error: The root1 gives back a defined variables list with size "<<
			liDefinedVariables.size() <<", but the size should be "<<
			uiNumberOfInputVariables <<" ."<<endl;
		iReturn++;
	}
	list<cFibVariable*>::iterator itrDefVariables = liDefinedVariables.begin();
	for ( unsigned int uiInVar1 = 1; (uiInVar1 <= uiNumberOfInputVariables) &&
			(itrDefVariables != liDefinedVariables.end()) ; uiInVar1++, itrDefVariables++ ){
		if ( root1.getInputVariable( uiInVar1 ) != (*itrDefVariables) ){
			cerr<<"Error: The root1 gives back a defined variables list with "<<
				"the wrong "<< uiInVar1 <<"'th variable object ."<<endl;
			iReturn++;
		}
	}


	//test setNumberOfInputVariables()
	uiNumberOfInputVariables = 2;
	cout<<"root1.setNumberOfInputVariables( "<< uiNumberOfInputVariables <<" ); "<<endl;
	bInputVariablesSet = root1.setNumberOfInputVariables( uiNumberOfInputVariables );
	if ( bInputVariablesSet ){
	
		cout<<"Could change the number of input variables. "<<endl;
	}else{
		cerr<<"Error: Couldn't change the number of input variables."<<endl;
		iReturn++;
	}
	//test getNumberOfInputVariables()
	if ( root1.getNumberOfInputVariables() == uiNumberOfInputVariables ){
	
		cout<<"The root1 has correctly "<< uiNumberOfInputVariables <<" input variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has "<< root1.getNumberOfInputVariables() <<
			" input variables, but should have "<< uiNumberOfInputVariables <<" ."<<endl;
		iReturn++;
	}

	for ( unsigned int uiInVar1 = 1; uiInVar1 < uiNumberOfInputVariables; uiInVar1++ ){
		for ( unsigned int uiInVar2 = uiInVar1 + 1; uiInVar2 <= uiNumberOfInputVariables; uiInVar2++ ){
			if ( root1.getInputVariable( uiInVar1 ) == root1.getInputVariable( uiInVar2 ) ){
				cerr<<"Error: The root1 "<< uiInVar1 <<
					" input variable is the same object as the "<< uiInVar2
					<<" input variable."<<endl;
				iReturn++;
			}
		}
	}
	cout<<"liInVariables2 = root1.getInputVariables();"<<endl;
	list<cFibVariable*> liInVariables2 = root1.getInputVariables();
	if ( liInVariables2.size() == uiNumberOfInputVariables ){
	
		cout<<"The root1 gives back a input variables list with correct size. "<<endl;
	}else{
		cerr<<"Error: The root1 gives back a input variables list with size "<<
			liInVariables2.size() <<", but the size should be "<<
			uiNumberOfInputVariables <<" ."<<endl;
		iReturn++;
	}
	itrInVariables = liInVariables2.begin();
	for ( unsigned int uiInVar1 = 1; (uiInVar1 <= uiNumberOfInputVariables) &&
			itrInVariables != liInVariables2.end() ; uiInVar1++, itrInVariables++ ){
		if ( root1.getInputVariable( uiInVar1 ) != (*itrInVariables) ){
			cerr<<"Error: The root1 gives back a input variables list with "<<
				"the wrong "<< uiInVar1 <<"'th variable object ."<<endl;
			iReturn++;
		}
	}
	//check isDefinedVariable()
	if ( ! root1.isDefinedVariable( &fibVariable ) ){
	
		cout<<"The fibVariable is correctly not defined by the root -element. "<<endl;
	}else{
		cerr<<"Error: The fibVariable is defined by the root -element."<<endl;
		iReturn++;
	}
	for ( unsigned int uiInVar1 = 1; (uiInVar1 <= uiNumberOfInputVariables); uiInVar1++ ){
		if ( ! root1.isDefinedVariable( root1.getInputVariable( uiInVar1 ) ) ){
			cerr<<"Error: The root1 defines the variable "<< uiInVar1 <<
				", but dosn't say so."<<endl;
			iReturn++;
		}
	}
	//check if the old input variables aren't overwritten
	itrInVariables = liInVariables.begin();
	list<cFibVariable*>::iterator itrInVariables2 = liInVariables2.begin();
	for ( unsigned int uiInVar1 = 1 ; ( itrInVariables != liInVariables.end() ) &&
			( itrInVariables2 != liInVariables2.end() ); 
			itrInVariables++, itrInVariables2++, uiInVar1++ ){

		if ( (*itrInVariables) == (*itrInVariables2) ){
		
			cout<<"The new setNumberOfInputVariables() hasn't correctly recreated the old "<<
				uiInVar1 <<"'th input variable. "<<endl;
		}else{
			cerr<<"Error: The new setNumberOfInputVariables() has recreated the old "<<
				uiInVar1 <<"'th input variable. "<<endl;
			iReturn++;
		}
	}
	//check getDefinedVariables( ED_POSITION )
	cout<<"liInVariables = root1.getDefinedVariables( ED_POSITION );"<<endl;
	liDefinedVariables = root1.getDefinedVariables( ED_POSITION );
	if ( liDefinedVariables.size() == uiNumberOfInputVariables ){
	
		cout<<"The root1 gives back a defined variables list with correct size. "<<endl;
	}else{
		cerr<<"Error: The root1 gives back a defined variables list with size "<<
			liDefinedVariables.size() <<", but the size should be "<<
			uiNumberOfInputVariables <<" ."<<endl;
		iReturn++;
	}
	itrDefVariables = liDefinedVariables.begin();
	for ( unsigned int uiInVar1 = 1; (uiInVar1 <= uiNumberOfInputVariables) &&
			(itrDefVariables != liDefinedVariables.end()) ; uiInVar1++, itrDefVariables++ ){
		if ( root1.getInputVariable( uiInVar1 ) != (*itrDefVariables) ){
			cerr<<"Error: The root1 gives back a defined variables list with "<<
				"the wrong "<< uiInVar1 <<"'th variable object ."<<endl;
			iReturn++;
		}
	}


	//test setNumberOfInputVariables()
	uiNumberOfInputVariables = 5;
	cout<<"root1.setNumberOfInputVariables( "<< uiNumberOfInputVariables <<" ); "<<endl;
	bInputVariablesSet = root1.setNumberOfInputVariables( uiNumberOfInputVariables );
	if ( bInputVariablesSet ){
	
		cout<<"Could change the number of input variables. "<<endl;
	}else{
		cerr<<"Error: Couldn't change the number of input variables."<<endl;
		iReturn++;
	}
	//test getNumberOfInputVariables()
	if ( root1.getNumberOfInputVariables() == uiNumberOfInputVariables ){
	
		cout<<"The root1 has correctly "<< uiNumberOfInputVariables <<" input variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has "<< root1.getNumberOfInputVariables() <<
			" input variables, but should have "<< uiNumberOfInputVariables <<" ."<<endl;
		iReturn++;
	}

	for ( unsigned int uiInVar1 = 1; uiInVar1 < uiNumberOfInputVariables; uiInVar1++ ){
		for ( unsigned int uiInVar2 = uiInVar1 + 1; uiInVar2 <= uiNumberOfInputVariables; uiInVar2++ ){
			if ( root1.getInputVariable( uiInVar1 ) == root1.getInputVariable( uiInVar2 ) ){
				cerr<<"Error: The root1 "<< uiInVar1 <<
					" input variable is the same object as the "<< uiInVar2
					<<" input variable."<<endl;
				iReturn++;
			}
		}
	}
	cout<<"liInVariables = root1.getInputVariables();"<<endl;
	liInVariables = root1.getInputVariables();
	if ( liInVariables.size() == uiNumberOfInputVariables ){
	
		cout<<"The root1 gives back a input variables list with correct size. "<<endl;
	}else{
		cerr<<"Error: The root1 gives back a input variables list with size "<<
			liInVariables.size() <<", but the size should be "<<
			uiNumberOfInputVariables <<" ."<<endl;
		iReturn++;
	}
	itrInVariables = liInVariables.begin();
	for ( unsigned int uiInVar1 = 1; (uiInVar1 <= uiNumberOfInputVariables) &&
			itrInVariables != liInVariables.end() ; uiInVar1++, itrInVariables++ ){
		if ( root1.getInputVariable( uiInVar1 ) != (*itrInVariables) ){
			cerr<<"Error: The root1 gives back a input variables list with "<<
				"the wrong "<< uiInVar1 <<"'th variable object ."<<endl;
			iReturn++;
		}
	}
	//check isDefinedVariable()
	if ( ! root1.isDefinedVariable( &fibVariable ) ){
	
		cout<<"The fibVariable is correctly not defined by the root -element. "<<endl;
	}else{
		cerr<<"Error: The fibVariable is defined by the root -element."<<endl;
		iReturn++;
	}
	for ( unsigned int uiInVar1 = 1; (uiInVar1 <= uiNumberOfInputVariables); uiInVar1++ ){
		if ( ! root1.isDefinedVariable( root1.getInputVariable( uiInVar1 ) ) ){
			cerr<<"Error: The root1 defines the variable "<< uiInVar1 <<
				", but dosn't say so."<<endl;
			iReturn++;
		}
	}
	//check if the old input variables aren't overwritten
	itrInVariables = liInVariables.begin();
	itrInVariables2 = liInVariables2.begin();
	for ( unsigned int uiInVar1 = 1 ; ( itrInVariables != liInVariables.end() ) &&
			( itrInVariables2 != liInVariables2.end() ); 
			itrInVariables++, itrInVariables2++, uiInVar1++ ){

		if ( (*itrInVariables) == (*itrInVariables2) ){
		
			cout<<"The new setNumberOfInputVariables() hasn't correctly recreated the old "<<
				uiInVar1 <<"'th input variable. "<<endl;
		}else{
			cerr<<"Error: The new setNumberOfInputVariables() has recreated the old "<<
				uiInVar1 <<"'th input variable. "<<endl;
			iReturn++;
		}
	}
	//check getDefinedVariables( ED_POSITION )
	cout<<"liInVariables = root1.getDefinedVariables( ED_POSITION );"<<endl;
	liDefinedVariables = root1.getDefinedVariables( ED_POSITION );
	if ( liDefinedVariables.size() == uiNumberOfInputVariables ){
	
		cout<<"The root1 gives back a defined variables list with correct size. "<<endl;
	}else{
		cerr<<"Error: The root1 gives back a defined variables list with size "<<
			liDefinedVariables.size() <<", but the size should be "<<
			uiNumberOfInputVariables <<" ."<<endl;
		iReturn++;
	}
	itrDefVariables = liDefinedVariables.begin();
	for ( unsigned int uiInVar1 = 1; (uiInVar1 <= uiNumberOfInputVariables) &&
			(itrDefVariables != liDefinedVariables.end()) ; uiInVar1++, itrDefVariables++ ){
		if ( root1.getInputVariable( uiInVar1 ) != (*itrDefVariables) ){
			cerr<<"Error: The root1 gives back a defined variables list with "<<
				"the wrong "<< uiInVar1 <<"'th variable object ."<<endl;
			iReturn++;
		}
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing try reduce number of input while one is in use"<<endl;

	cFibElement * usingFibElement1 = (cFibElement*)(new cRoot());
	cVectorProperty vectorproperty1( 1 , usingFibElement1 );

	cout<<"vectorproperty1.setVariable( 1, root1.getInputVariable( 4 ) );"<<endl;
	vectorproperty1.setVariable( 1, root1.getInputVariable( 4 ) );

	//test setNumberOfInputVariables()
	uiNumberOfInputVariables = 3;
	cout<<"root1.setNumberOfInputVariables( "<< uiNumberOfInputVariables <<" ); "<<endl;
	bInputVariablesSet = root1.setNumberOfInputVariables( uiNumberOfInputVariables );
	uiNumberOfInputVariables = 4;
	if ( ! bInputVariablesSet ){
	
		cout<<"Couldn't change the number of input variables to 3. "<<endl;
	}else{
		cerr<<"Error: Could change the number of input variables to 3."<<endl;
		iReturn++;
	}
	//test getNumberOfInputVariables()
	if ( root1.getNumberOfInputVariables() == uiNumberOfInputVariables ){
	
		cout<<"The root1 has correctly "<< uiNumberOfInputVariables <<" input variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has "<< root1.getNumberOfInputVariables() <<
			" input variables, but should have "<< uiNumberOfInputVariables <<" ."<<endl;
		iReturn++;
	}

	for ( unsigned int uiInVar1 = 1; uiInVar1 < uiNumberOfInputVariables; uiInVar1++ ){
		for ( unsigned int uiInVar2 = uiInVar1 + 1; uiInVar2 <= uiNumberOfInputVariables; uiInVar2++ ){
			if ( root1.getInputVariable( uiInVar1 ) == root1.getInputVariable( uiInVar2 ) ){
				cerr<<"Error: The root1 "<< uiInVar1 <<
					" input variable is the same object as the "<< uiInVar2
					<<" input variable."<<endl;
				iReturn++;
			}
		}
	}
	cout<<"liInVariables2 = root1.getInputVariables();"<<endl;
	liInVariables2 = root1.getInputVariables();
	if ( liInVariables2.size() == uiNumberOfInputVariables ){
	
		cout<<"The root1 gives back a input variables list with correct size. "<<endl;
	}else{
		cerr<<"Error: The root1 gives back a input variables list with size "<<
			liInVariables2.size() <<", but the size should be "<<
			uiNumberOfInputVariables <<" ."<<endl;
		iReturn++;
	}
	itrInVariables = liInVariables2.begin();
	for ( unsigned int uiInVar1 = 1; (uiInVar1 <= uiNumberOfInputVariables) &&
			itrInVariables != liInVariables2.end() ; uiInVar1++, itrInVariables++ ){
		if ( root1.getInputVariable( uiInVar1 ) != (*itrInVariables) ){
			cerr<<"Error: The root1 gives back a input variables list with "<<
				"the wrong "<< uiInVar1 <<"'th variable object ."<<endl;
			iReturn++;
		}
	}
	//check isDefinedVariable()
	if ( ! root1.isDefinedVariable( &fibVariable ) ){
	
		cout<<"The fibVariable is correctly not defined by the root -element. "<<endl;
	}else{
		cerr<<"Error: The fibVariable is defined by the root -element."<<endl;
		iReturn++;
	}
	for ( unsigned int uiInVar1 = 1; (uiInVar1 <= uiNumberOfInputVariables); uiInVar1++ ){
		if ( ! root1.isDefinedVariable( root1.getInputVariable( uiInVar1 ) ) ){
			cerr<<"Error: The root1 defines the variable "<< uiInVar1 <<
				", but dosn't say so."<<endl;
			iReturn++;
		}
	}
	//check if the old input variables aren't overwritten
	itrInVariables = liInVariables.begin();
	itrInVariables2 = liInVariables2.begin();
	for ( unsigned int uiInVar1 = 1 ; ( itrInVariables != liInVariables.end() ) &&
			( itrInVariables2 != liInVariables2.end() ); 
			itrInVariables++, itrInVariables2++, uiInVar1++ ){

		if ( (*itrInVariables) == (*itrInVariables2) ){
		
			cout<<"The new setNumberOfInputVariables() hasn't correctly recreated the old "<<
				uiInVar1 <<"'th input variable. "<<endl;
		}else{
			cerr<<"Error: The new setNumberOfInputVariables() has recreated the old "<<
				uiInVar1 <<"'th input variable. "<<endl;
			iReturn++;
		}
	}
	delete usingFibElement1;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing methods for the standard value of the input variable"<<endl;

	cout<<"cTypeInVar typeinVar2( 2 );"<<endl;
	cTypeInVar typeinVar2( 2 );
	cout<<"cDomainNaturalNumberBit naturalNumberDomain2( 2 );"<<endl;
	cDomainNaturalNumberBit naturalNumberDomain2( 2 );
	
	cout<<"root1.getDomains()->addDomain(  typeinVar2, naturalNumberDomain2 );"<<endl;
	root1.getDomains()->addDomain( typeinVar2, naturalNumberDomain2 );

	double aDStandardValues[] = {0.0, 0.0, 0.0, 0.0};

	for ( unsigned int uiInVar1 = 1; uiInVar1 <= uiNumberOfInputVariables; uiInVar1++ ){
		
		if ( root1.getStandardValueOfInputVariable( uiInVar1 ) ==
				aDStandardValues[ uiInVar1 - 1 ] ){
		
			cout<<"The "<< uiInVar1 <<"'th input variables standardvalue is correctly "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" ."<<endl;
		}else{
			cerr<<"Error: The "<< uiInVar1 <<"'th input variables standardvalue is "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" and not "<<
				aDStandardValues[ uiInVar1 - 1 ] <<" ."<<endl;
			iReturn++;
		}
	}
	cout<<"root1.setStandardValueOfInputVariable( 3, 3.0 ); "<<endl;
	bool bStandardValueSet = root1.setStandardValueOfInputVariable( 3, 3.0 );
	aDStandardValues[ 2 ] = 3.0;
	if ( bStandardValueSet ){
	
		cout<<"The standardvalue could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The standardvalue couldn't be set."<<endl;
		iReturn++;
	}
	for ( unsigned int uiInVar1 = 1; uiInVar1 <= uiNumberOfInputVariables; uiInVar1++ ){
		
		if ( root1.getStandardValueOfInputVariable( uiInVar1 ) ==
				aDStandardValues[ uiInVar1 - 1 ] ){
		
			cout<<"The "<< uiInVar1 <<"'th input variables standardvalue is correctly "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" ."<<endl;
		}else{
			cerr<<"Error: The "<< uiInVar1 <<"'th input variables standardvalue is "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" and not "<<
				aDStandardValues[ uiInVar1 - 1 ] <<" ."<<endl;
			iReturn++;
		}
	}
	
	cout<<"root1.setStandardValueOfInputVariable( 4, 4.44 ); "<<endl;
	bStandardValueSet = root1.setStandardValueOfInputVariable( 4, 4.44 );
	if ( ! bStandardValueSet ){
	
		cout<<"The standardvalue correctly could not be set. "<<endl;
	}else{
		cerr<<"Error: The standardvalue could be set."<<endl;
		iReturn++;
	}
	for ( unsigned int uiInVar1 = 1; uiInVar1 <= uiNumberOfInputVariables; uiInVar1++ ){
		
		if ( root1.getStandardValueOfInputVariable( uiInVar1 ) ==
				aDStandardValues[ uiInVar1 - 1 ] ){
		
			cout<<"The "<< uiInVar1 <<"'th input variables standardvalue is correctly "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" ."<<endl;
		}else{
			cerr<<"Error: The "<< uiInVar1 <<"'th input variables standardvalue is "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" and not "<<
				aDStandardValues[ uiInVar1 - 1 ] <<" ."<<endl;
			iReturn++;
		}
	}

	cout<<"root1.setStandardValueOfInputVariable( 2, 4.0 ); "<<endl;
	bStandardValueSet = root1.setStandardValueOfInputVariable( 2, 4.0 );
	if ( ! bStandardValueSet ){
	
		cout<<"The standardvalue correctly could not be set. "<<endl;
	}else{
		cerr<<"Error: The standardvalue could be set."<<endl;
		iReturn++;
	}
	for ( unsigned int uiInVar1 = 1; uiInVar1 <= uiNumberOfInputVariables; uiInVar1++ ){
		
		if ( root1.getStandardValueOfInputVariable( uiInVar1 ) ==
				aDStandardValues[ uiInVar1 - 1 ] ){
		
			cout<<"The "<< uiInVar1 <<"'th input variables standardvalue is correctly "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" ."<<endl;
		}else{
			cerr<<"Error: The "<< uiInVar1 <<"'th input variables standardvalue is "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" and not "<<
				aDStandardValues[ uiInVar1 - 1 ] <<" ."<<endl;
			iReturn++;
		}
	}

	cout<<"root1.setStandardValueOfInputVariable( 1, -1.0 ); "<<endl;
	bStandardValueSet = root1.setStandardValueOfInputVariable( 1, -1.0 );
	if ( ! bStandardValueSet ){
	
		cout<<"The standardvalue correctly could not be set. "<<endl;
	}else{
		cerr<<"Error: The standardvalue could be set."<<endl;
		iReturn++;
	}
	for ( unsigned int uiInVar1 = 1; uiInVar1 <= uiNumberOfInputVariables; uiInVar1++ ){
		
		if ( root1.getStandardValueOfInputVariable( uiInVar1 ) ==
				aDStandardValues[ uiInVar1 - 1 ] ){
		
			cout<<"The "<< uiInVar1 <<"'th input variables standardvalue is correctly "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" ."<<endl;
		}else{
			cerr<<"Error: The "<< uiInVar1 <<"'th input variables standardvalue is "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" and not "<<
				aDStandardValues[ uiInVar1 - 1 ] <<" ."<<endl;
			iReturn++;
		}
	}

	cout<<"root1.setStandardValueOfInputVariable( 1, 1.0 ); "<<endl;
	bStandardValueSet = root1.setStandardValueOfInputVariable( 1, 1.0 );
	aDStandardValues[ 0 ] = 1.0;
	if ( bStandardValueSet ){
	
		cout<<"The standardvalue could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The standardvalue couldn't be set."<<endl;
		iReturn++;
	}
	for ( unsigned int uiInVar1 = 1; uiInVar1 <= uiNumberOfInputVariables; uiInVar1++ ){
		
		if ( root1.getStandardValueOfInputVariable( uiInVar1 ) ==
				aDStandardValues[ uiInVar1 - 1 ] ){
		
			cout<<"The "<< uiInVar1 <<"'th input variables standardvalue is correctly "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" ."<<endl;
		}else{
			cerr<<"Error: The "<< uiInVar1 <<"'th input variables standardvalue is "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" and not "<<
				aDStandardValues[ uiInVar1 - 1 ] <<" ."<<endl;
			iReturn++;
		}
	}

	cout<<"root1.setStandardValueOfInputVariable( 4, 4.0 ); "<<endl;
	bStandardValueSet = root1.setStandardValueOfInputVariable( 4, 4.0 );
	aDStandardValues[ 3 ] = 4.0;
	if ( bStandardValueSet ){
	
		cout<<"The standardvalue could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The standardvalue couldn't be set."<<endl;
		iReturn++;
	}
	for ( unsigned int uiInVar1 = 1; uiInVar1 <= uiNumberOfInputVariables; uiInVar1++ ){
		
		if ( root1.getStandardValueOfInputVariable( uiInVar1 ) ==
				aDStandardValues[ uiInVar1 - 1 ] ){
		
			cout<<"The "<< uiInVar1 <<"'th input variables standardvalue is correctly "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" ."<<endl;
		}else{
			cerr<<"Error: The "<< uiInVar1 <<"'th input variables standardvalue is "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" and not "<<
				aDStandardValues[ uiInVar1 - 1 ] <<" ."<<endl;
			iReturn++;
		}
	}

	cout<<"root1.setStandardValueOfInputVariable( 0, 1.0 ); "<<endl;
	bStandardValueSet = root1.setStandardValueOfInputVariable( 0, 1.0 );
	if ( ! bStandardValueSet ){
	
		cout<<"The standardvalue correctly could not be set. "<<endl;
	}else{
		cerr<<"Error: The standardvalue could be set."<<endl;
		iReturn++;
	}
	cout<<"root1.setStandardValueOfInputVariable( 5, 1.0 ); "<<endl;
	bStandardValueSet = root1.setStandardValueOfInputVariable( 5, 1.0 );
	if ( ! bStandardValueSet ){
	
		cout<<"The standardvalue correctly could not be set. "<<endl;
	}else{
		cerr<<"Error: The standardvalue could be set."<<endl;
		iReturn++;
	}
	for ( unsigned int uiInVar1 = 1; uiInVar1 <= uiNumberOfInputVariables; uiInVar1++ ){
		
		if ( root1.getStandardValueOfInputVariable( uiInVar1 ) ==
				aDStandardValues[ uiInVar1 - 1 ] ){
		
			cout<<"The "<< uiInVar1 <<"'th input variables standardvalue is correctly "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" ."<<endl;
		}else{
			cerr<<"Error: The "<< uiInVar1 <<"'th input variables standardvalue is "<<
				root1.getStandardValueOfInputVariable( uiInVar1 ) <<" and not "<<
				aDStandardValues[ uiInVar1 - 1 ] <<" ."<<endl;
			iReturn++;
		}
	}
	if ( root1.getStandardValueOfInputVariable( 0 ) == 0.0 ){
	
		cout<<"The 0'th input variables standardvalue is correctly 0.0 ."<<endl;
	}else{
		cerr<<"Error: The 0'th input variables standardvalue is "<<
			root1.getStandardValueOfInputVariable( 0 ) <<" and not 0 ."<<endl;
		iReturn++;
	}
	if ( root1.getStandardValueOfInputVariable( 5 ) == 0.0 ){
	
		cout<<"The 5'th input variables standardvalue is correctly 0.0 ."<<endl;
	}else{
		cerr<<"Error: The 5'th input variables standardvalue is "<<
			root1.getStandardValueOfInputVariable( 5 ) <<" and not 0 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equalValuesSet() method"<<endl;
	
	cout<<"cRoot root2;"<<endl;
	cRoot root2;

	unsigned int uiNumberOfInputVariables2 = 3;
	cout<<"root2.setNumberOfInputVariables( "<< uiNumberOfInputVariables2 <<" ); "<<endl;
	bInputVariablesSet = root2.setNumberOfInputVariables( uiNumberOfInputVariables2 );
	if ( bInputVariablesSet ){
	
		cout<<"Could change the number of input variables. "<<endl;
	}else{
		cerr<<"Error: Couldn't change the number of input variables."<<endl;
		iReturn++;
	}

	for ( unsigned int uiInVar1 = 1; uiInVar1 <= uiNumberOfInputVariables; uiInVar1++ ){
		for ( unsigned int uiInVar2 = 1; uiInVar2 <= uiNumberOfInputVariables2; uiInVar2++ ){
		
			if ( uiInVar1 == uiInVar2 ){
				if ( root1.equalValuesSet( root1.getInputVariable( uiInVar1 ),
						root2, root2.getInputVariable( uiInVar2 ) )  ){
				
					cout<<"The "<< uiInVar1 <<"'th input variables of root1 is "<<
						"correctly equalValuesSet to the "<< uiInVar2 <<
						"'th input variables of root2."<<endl;
				}else{
					cerr<<"Error: The "<< uiInVar1 <<"'th input variables of root1 is not "<<
						"equalValuesSet to the "<< uiInVar2 <<"'th input variables of root2."<<endl;
					iReturn++;
				}
				if ( root2.equalValuesSet( root2.getInputVariable( uiInVar2 ),
						root1, root1.getInputVariable( uiInVar1 ))  ){
				
					cout<<"The "<< uiInVar2 <<"'th input variables of root2 is "<<
						"correctly equalValuesSet to the "<< uiInVar1 <<
						"'th input variables of root1."<<endl;
				}else{
					cerr<<"Error: The "<< uiInVar2 <<"'th input variables of root2 is not "<<
						"equalValuesSet to the "<< uiInVar1 <<"'th input variables of root1."<<endl;
					iReturn++;
				}
			}else{
				if ( ! root1.equalValuesSet( root1.getInputVariable( uiInVar1 ),
						root2, root2.getInputVariable( uiInVar2 ) )  ){
				
					cout<<"The "<< uiInVar1 <<"'th input variables of root1 is "<<
						"correctly not equalValuesSet to the "<< uiInVar2 <<
						"'th input variables of root2."<<endl;
				}else{
					cerr<<"Error: The "<< uiInVar1 <<"'th input variables of root1 is "<<
						"equalValuesSet to the "<< uiInVar2 <<"'th input variables of root2."<<endl;
					iReturn++;
				}
				if ( ! root2.equalValuesSet( root2.getInputVariable( uiInVar2 ),
						root1, root1.getInputVariable( uiInVar1 ))  ){
				
					cout<<"The "<< uiInVar2 <<"'th input variables of root2 is "<<
						"correctly not equalValuesSet to the "<< uiInVar1 <<
						"'th input variables of root1."<<endl;
				}else{
					cerr<<"Error: The "<< uiInVar2 <<"'th input variables of root2 is "<<
						"equalValuesSet to the "<< uiInVar1 <<"'th input variables of root1."<<endl;
					iReturn++;
				}
			}
		}
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods isUsedVariable( ED_POSITION ) and getUsedVariables( ED_POSITION )"<<endl;

	//check isUsedVariable()
	if ( ! root1.isUsedVariable( &fibVariable ) ){
	
		cout<<"The fibVariable is correctly not used by the root -element. "<<endl;
	}else{
		cerr<<"Error: The fibVariable is used by the root -element."<<endl;
		iReturn++;
	}
	for ( unsigned int uiInVar1 = 1; (uiInVar1 <= uiNumberOfInputVariables); uiInVar1++ ){
		if ( root1.isUsedVariable( root1.getInputVariable( uiInVar1 ), ED_POSITION ) ){
			cerr<<"Error: The root1 defines the variable "<< uiInVar1 <<
				", but says it uses it."<<endl;
			iReturn++;
		}
	}
	//check getUsedVariables( ED_POSITION )
	cout<<"setUsedVariables = root1.getUsedVariables( ED_POSITION );"<<endl;
	set<cFibVariable*> setUsedVariables = root1.getUsedVariables( ED_POSITION );
	if ( setUsedVariables.size() == 0 ){
	
		cout<<"The root1 gives back a used variables list with correct size 0. "<<endl;
	}else{
		cerr<<"Error: The root1 gives back a used variables list with size "<<
			setUsedVariables.size() <<", but the size should be "<<
			0 <<" ."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the methods for the extern underobject of the cRoot class.
 *
 * methods tested:
 * 	- unsignedIntFib getNumberOfExternSubobjects() const;
 * 	- unsignedIntFib getNumberOfOutputVariables( unsignedIntFib uiNumberOfUnderObject ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testExternSubobjects( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the extern underobjects"<<endl;

	cout<<"cRoot root1;"<<endl;
	cRoot root1;
	
	//test getNumberOfExternSubobjects()
	if ( root1.getNumberOfExternSubobjects() == 0 ){
	
		cout<<"The root1 has correctly no extern underobjects. "<<endl;
	}else{
		cerr<<"Error: The root1 has extern underobjects."<<endl;
		iReturn++;
	}

	//test setNumberOfExternSubobjects()
	unsignedIntFib uiExternSubobjects = 5;
	unsignedIntFib aUiNumberOfOutputVariables[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	//set domain for 5'th external subobject
	cout<<"cTypeExtSubobject typeExtSubobject5( 5 );"<<endl;
	cTypeExtSubobject typeExtSubobject5( 5 );
	
	cout<<"vector<cDomain*> vecDomainE0( 0 );"<<endl;
	vector<cDomain*> vecDomainE0( 0 );
	cout<<"cDomainVector domVectorE0( vecDomainE0 );"<<endl;
	cDomainVector domVectorE0( vecDomainE0 );
	
	cout<<"root1.getDomains()->addDomain( typeExtSubobject5, domVectorE0 );"<<endl;
	root1.getDomains()->addDomain( typeExtSubobject5, domVectorE0 );
	
	//test getNumberOfExternSubobjects()
	if ( root1.getNumberOfExternSubobjects() == uiExternSubobjects ){
	
		cout<<"The root1 has correctly "<< uiExternSubobjects
			<<" extern underobjects. "<<endl;
	}else{
		cerr<<"Error: The root1 has "<< root1.getNumberOfExternSubobjects() <<
			" extern underobjects, but should have "<< uiExternSubobjects <<"."<<endl;
		iReturn++;
	}
	//test getNumberOfOutputVariables()
	for ( unsignedIntFib actualUnderobject = 1;
			actualUnderobject <= uiExternSubobjects; actualUnderobject++ ){
		
		if ( root1.getNumberOfOutputVariables( actualUnderobject ) ==
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] ){
		
			cout<<"The root1 has correctly for the "<< actualUnderobject
				<<"'th extern underobject "<<
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] <<
				" output variables. "<<endl;
		}else{
			cerr<<"Error: The root1 has for the "<< actualUnderobject
				<<"'th extern underobject "<<
				root1.getNumberOfOutputVariables( actualUnderobject )<<
				" output variables, but should have "<<
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] <<
				" output variables. "<<endl;
			iReturn++;
		}
	}
	//check getNumberOfOutputVariables() returnvalues if the number is out of bouderies
	if ( root1.getNumberOfOutputVariables( 0 ) == 0 ){
	
		cout<<"The root1 has correctly for the 0'th extern underobject"<<
			" 0 output variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has for the 0'th extern underobject "<<
			root1.getNumberOfOutputVariables( 0 )<<
			" output variables, but should have 0 output variables. "<<endl;
		iReturn++;
	}
	if ( root1.getNumberOfOutputVariables( uiExternSubobjects + 1 ) == 0 ){
	
		cout<<"The root1 has correctly for the "<<
			uiExternSubobjects + 1 <<"'th extern underobject"<<
			" 0 output variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has for the "<<
			uiExternSubobjects + 1 <<"'th extern underobject "<<
			root1.getNumberOfOutputVariables( uiExternSubobjects + 1 )<<
			" output variables, but should have 0 output variables. "<<endl;
		iReturn++;
	}

	aUiNumberOfOutputVariables[ 2 ] = 3;
	//set domain for 3'th external subobject
	cout<<"cTypeExtSubobject typeExtSubobject3( 3 );"<<endl;
	cTypeExtSubobject typeExtSubobject3( 3 );
	
	cout<<"vector<cDomain*> vecDomainE3( 3 );"<<endl;
	vector<cDomain*> vecDomainE3( 3 );
	vecDomainE3[ 0 ] = new cDomainNaturalNumberBit( 1 );
	vecDomainE3[ 1 ] = new cDomainNaturalNumberBit( 2 );
	vecDomainE3[ 2 ] = new cDomainNaturalNumberBit( 3 );
	
	cout<<"cDomainVector domVectorE3( vecDomainE3 );"<<endl;
	cDomainVector domVectorE3( vecDomainE3 );
	
	delete vecDomainE3[ 0 ];
	delete vecDomainE3[ 1 ];
	delete vecDomainE3[ 2 ];
	
	cout<<"root1.getDomains()->addDomain( typeExtSubobject3, domVectorE3 );"<<endl;
	root1.getDomains()->addDomain( typeExtSubobject3, domVectorE3 );
	
	//test getNumberOfOutputVariables()
	for ( unsignedIntFib actualUnderobject = 1;
			actualUnderobject <= uiExternSubobjects; actualUnderobject++ ){
		
		if ( root1.getNumberOfOutputVariables( actualUnderobject ) ==
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] ){
		
			cout<<"The root1 has correctly for the "<< actualUnderobject
				<<"'th extern underobject "<<
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] <<
				" output variables. "<<endl;
		}else{
			cerr<<"Error: The root1 has for the "<< actualUnderobject
				<<"'th extern underobject "<<
				root1.getNumberOfOutputVariables( actualUnderobject )<<
				" output variables, but should have "<<
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] <<
				" output variables. "<<endl;
			iReturn++;
		}
	}
	//check getNumberOfOutputVariables() returnvalues if the number is out of bouderies
	if ( root1.getNumberOfOutputVariables( 0 ) == 0 ){
	
		cout<<"The root1 has correctly for the 0'th extern underobject"<<
			" 0 output variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has for the 0'th extern underobject "<<
			root1.getNumberOfOutputVariables( 0 )<<
			" output variables, but should have 0 output variables. "<<endl;
		iReturn++;
	}
	if ( root1.getNumberOfOutputVariables( uiExternSubobjects + 1 ) == 0 ){
	
		cout<<"The root1 has correctly for the "<<
			uiExternSubobjects + 1 <<"'th extern underobject"<<
			" 0 output variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has for the "<<
			uiExternSubobjects + 1 <<"'th extern underobject "<<
			root1.getNumberOfOutputVariables( uiExternSubobjects + 1 )<<
			" output variables, but should have 0 output variables. "<<endl;
		iReturn++;
	}

	aUiNumberOfOutputVariables[ 0 ] = 1;
	aUiNumberOfOutputVariables[ 4 ] = 5;
	//set domain for 1'th external subobject
	cout<<"cTypeExtSubobject typeExtSubobject1( 1 );"<<endl;
	cTypeExtSubobject typeExtSubobject1( 1 );
	
	cout<<"vector<cDomain*> vecDomainE1( 1 );"<<endl;
	vector<cDomain*> vecDomainE1( 1 );
	vecDomainE1[ 0 ] = new cDomainNaturalNumberBit( 4 );
	
	cout<<"cDomainVector domVectorE1( vecDomainE1 );"<<endl;
	cDomainVector domVectorE1( vecDomainE1 );
	
	delete vecDomainE1[ 0 ];
	
	cout<<"root1.getDomains()->addDomain( typeExtSubobject1, domVectorE1 );"<<endl;
	root1.getDomains()->addDomain( typeExtSubobject1, domVectorE1 );
	
	//set domain for 5'th external subobject
	cout<<"vector<cDomain*> vecDomainE5( 5 );"<<endl;
	vector<cDomain*> vecDomainE5( 5 );
	vecDomainE5[ 0 ] = new cDomainNaturalNumberBit( 5 );
	vecDomainE5[ 1 ] = new cDomainNaturalNumberBit( 6 );
	vecDomainE5[ 2 ] = new cDomainNaturalNumberBit( 7 );
	vecDomainE5[ 3 ] = new cDomainNaturalNumberBit( 8 );
	vecDomainE5[ 4 ] = new cDomainNaturalNumberBit( 9 );
	
	cout<<"cDomainVector domVectorE5( vecDomainE5 );"<<endl;
	cDomainVector domVectorE5( vecDomainE5 );
	
	delete vecDomainE5[ 0 ];
	delete vecDomainE5[ 1 ];
	delete vecDomainE5[ 2 ];
	delete vecDomainE5[ 3 ];
	delete vecDomainE5[ 4 ];
	
	cout<<"root1.getDomains()->addDomain( typeExtSubobject5, domVectorE5 );"<<endl;
	root1.getDomains()->addDomain( typeExtSubobject5, domVectorE5 );
	
	//test getNumberOfOutputVariables()
	for ( unsignedIntFib actualUnderobject = 1;
			actualUnderobject <= uiExternSubobjects; actualUnderobject++ ){
		
		if ( root1.getNumberOfOutputVariables( actualUnderobject ) ==
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] ){
		
			cout<<"The root1 has correctly for the "<< actualUnderobject
				<<"'th extern underobject "<<
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] <<
				" output variables. "<<endl;
		}else{
			cerr<<"Error: The root1 has for the "<< actualUnderobject
				<<"'th extern underobject "<<
				root1.getNumberOfOutputVariables( actualUnderobject )<<
				" output variables, but should have "<<
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] <<
				" output variables. "<<endl;
			iReturn++;
		}
	}
	//check getNumberOfOutputVariables() returnvalues if the number is out of bouderies
	if ( root1.getNumberOfOutputVariables( 0 ) == 0 ){
	
		cout<<"The root1 has correctly for the 0'th extern underobject"<<
			" 0 output variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has for the 0'th extern underobject "<<
			root1.getNumberOfOutputVariables( 0 )<<
			" output variables, but should have 0 output variables. "<<endl;
		iReturn++;
	}
	if ( root1.getNumberOfOutputVariables( uiExternSubobjects + 1 ) == 0 ){
	
		cout<<"The root1 has correctly for the "<<
			uiExternSubobjects + 1 <<"'th extern underobject"<<
			" 0 output variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has for the "<<
			uiExternSubobjects + 1 <<"'th extern underobject "<<
			root1.getNumberOfOutputVariables( uiExternSubobjects + 1 )<<
			" output variables, but should have 0 output variables. "<<endl;
		iReturn++;
	}

	aUiNumberOfOutputVariables[ 0 ] = 5;
	aUiNumberOfOutputVariables[ 1 ] = 4;
	aUiNumberOfOutputVariables[ 2 ] = 13;
	aUiNumberOfOutputVariables[ 3 ] = 2;
	aUiNumberOfOutputVariables[ 4 ] = 1;
	//set domain for 1'th external subobject
	cout<<"root1.getDomains()->addDomain( typeExtSubobject1, domVectorE5 );"<<endl;
	root1.getDomains()->addDomain( typeExtSubobject1, domVectorE5 );
	
	//set domain for 2'th external subobject
	cout<<"cTypeExtSubobject typeExtSubobject2( 2 );"<<endl;
	cTypeExtSubobject typeExtSubobject2( 2 );
	
	cout<<"vector<cDomain*> vecDomainE4( 4 );"<<endl;
	vector<cDomain*> vecDomainE4( 4 );
	vecDomainE4[ 0 ] = new cDomainNaturalNumberBit( 11 );
	vecDomainE4[ 1 ] = new cDomainNaturalNumberBit( 12 );
	vecDomainE4[ 2 ] = new cDomainNaturalNumberBit( 13 );
	vecDomainE4[ 3 ] = new cDomainNaturalNumberBit( 14 );
	
	cout<<"cDomainVector domVectorE4( vecDomainE4 );"<<endl;
	cDomainVector domVectorE4( vecDomainE4 );
	
	delete vecDomainE4[ 0 ];
	delete vecDomainE4[ 1 ];
	delete vecDomainE4[ 2 ];
	delete vecDomainE4[ 3 ];

	cout<<"root1.getDomains()->addDomain( typeExtSubobject2, domVectorE4 );"<<endl;
	root1.getDomains()->addDomain( typeExtSubobject2, domVectorE4 );
	
	//set domain for 3'th external subobject
	cout<<"vector<cDomain*> vecDomainE13( 13 );"<<endl;
	vector<cDomain*> vecDomainE13( 13 );
	vecDomainE13[ 0 ] = new cDomainNaturalNumberBit( 13 );
	vecDomainE13[ 1 ] = new cDomainNaturalNumberBit( 13 );
	vecDomainE13[ 2 ] = new cDomainNaturalNumberBit( 13 );
	vecDomainE13[ 3 ] = new cDomainNaturalNumberBit( 13 );
	vecDomainE13[ 4 ] = new cDomainNaturalNumberBit( 13 );
	vecDomainE13[ 5 ] = new cDomainNaturalNumberBit( 13 );
	vecDomainE13[ 6 ] = new cDomainNaturalNumberBit( 13 );
	vecDomainE13[ 7 ] = new cDomainNaturalNumberBit( 13 );
	vecDomainE13[ 8 ] = new cDomainNaturalNumberBit( 13 );
	vecDomainE13[ 9 ] = new cDomainNaturalNumberBit( 13 );
	vecDomainE13[ 10 ] = new cDomainNaturalNumberBit( 13 );
	vecDomainE13[ 11 ] = new cDomainNaturalNumberBit( 13 );
	vecDomainE13[ 12 ] = new cDomainNaturalNumberBit( 13 );
	
	cout<<"cDomainVector domVectorE13( vecDomainE13 );"<<endl;
	cDomainVector domVectorE13( vecDomainE13 );
	
	delete vecDomainE13[ 0 ];
	delete vecDomainE13[ 1 ];
	delete vecDomainE13[ 2 ];
	delete vecDomainE13[ 3 ];
	delete vecDomainE13[ 4 ];
	delete vecDomainE13[ 5 ];
	delete vecDomainE13[ 6 ];
	delete vecDomainE13[ 7 ];
	delete vecDomainE13[ 8 ];
	delete vecDomainE13[ 9 ];
	delete vecDomainE13[ 10 ];
	delete vecDomainE13[ 11 ];
	delete vecDomainE13[ 12 ];
	
	cout<<"root1.getDomains()->addDomain( typeExtSubobject3, domVectorE13 );"<<endl;
	root1.getDomains()->addDomain( typeExtSubobject3, domVectorE13 );
	
	
	//set domain for 4'th external subobject
	cout<<"cTypeExtSubobject typeExtSubobject4( 4 );"<<endl;
	cTypeExtSubobject typeExtSubobject4( 4 );
	
	cout<<"vector<cDomain*> vecDomainE2( 2 );"<<endl;
	vector<cDomain*> vecDomainE2( 2 );
	vecDomainE2[ 0 ] = new cDomainNaturalNumberBit( 15 );
	vecDomainE2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	
	cout<<"cDomainVector domVectorE2( vecDomainE2 );"<<endl;
	cDomainVector domVectorE2( vecDomainE2 );
	
	delete vecDomainE2[ 0 ];
	delete vecDomainE2[ 1 ];
	
	cout<<"root1.getDomains()->addDomain( typeExtSubobject4, domVectorE2 );"<<endl;
	root1.getDomains()->addDomain( typeExtSubobject4, domVectorE2 );
	
	
	//set domain for 5'th external subobject
	cout<<"root1.getDomains()->addDomain( typeExtSubobject5, domVectorE1 );"<<endl;
	root1.getDomains()->addDomain( typeExtSubobject5, domVectorE1 );
	
	//test getNumberOfOutputVariables()
	for ( unsignedIntFib actualUnderobject = 1;
			actualUnderobject <= uiExternSubobjects; actualUnderobject++ ){
		
		if ( root1.getNumberOfOutputVariables( actualUnderobject ) ==
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] ){
		
			cout<<"The root1 has correctly for the "<< actualUnderobject
				<<"'th extern underobject "<<
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] <<
				" output variables. "<<endl;
		}else{
			cerr<<"Error: The root1 has for the "<< actualUnderobject
				<<"'th extern underobject "<<
				root1.getNumberOfOutputVariables( actualUnderobject )<<
				" output variables, but should have "<<
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] <<
				" output variables. "<<endl;
			iReturn++;
		}
	}
	//check getNumberOfOutputVariables() returnvalues if the number is out of bouderies
	if ( root1.getNumberOfOutputVariables( 0 ) == 0 ){
	
		cout<<"The root1 has correctly for the 0'th extern underobject"<<
			" 0 output variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has for the 0'th extern underobject "<<
			root1.getNumberOfOutputVariables( 0 )<<
			" output variables, but should have 0 output variables. "<<endl;
		iReturn++;
	}
	if ( root1.getNumberOfOutputVariables( uiExternSubobjects + 1 ) == 0 ){
	
		cout<<"The root1 has correctly for the "<<
			uiExternSubobjects + 1 <<"'th extern underobject"<<
			" 0 output variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has for the "<<
			uiExternSubobjects + 1 <<"'th extern underobject "<<
			root1.getNumberOfOutputVariables( uiExternSubobjects + 1 )<<
			" output variables, but should have 0 output variables. "<<endl;
		iReturn++;
	}


	//test setNumberOfExternSubobjects()
	uiExternSubobjects = 3;
	aUiNumberOfOutputVariables[ 3 ] = 0;
	aUiNumberOfOutputVariables[ 4 ] = 0;
	
	cout<<"root1.getDomains()->deleteDomain( typeExtSubobject4 );"<<endl;
	root1.getDomains()->deleteDomain( typeExtSubobject4 );
	cout<<"root1.getDomains()->deleteDomain( typeExtSubobject5 );"<<endl;
	root1.getDomains()->deleteDomain( typeExtSubobject5 );
	
	//test getNumberOfExternSubobjects()
	if ( root1.getNumberOfExternSubobjects() == uiExternSubobjects ){
	
		cout<<"The root1 has correctly "<< uiExternSubobjects
			<<" extern underobjects. "<<endl;
	}else{
		cerr<<"Error: The root1 has "<< root1.getNumberOfExternSubobjects() <<
			" extern underobjects, but should have "<< uiExternSubobjects <<"."<<endl;
		iReturn++;
	}
	//test getNumberOfOutputVariables()
	for ( unsignedIntFib actualUnderobject = 1;
			actualUnderobject <= uiExternSubobjects; actualUnderobject++ ){
		
		if ( root1.getNumberOfOutputVariables( actualUnderobject ) ==
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] ){
		
			cout<<"The root1 has correctly for the "<< actualUnderobject
				<<"'th extern underobject "<<
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] <<
				" output variables. "<<endl;
		}else{
			cerr<<"Error: The root1 has for the "<< actualUnderobject
				<<"'th extern underobject "<<
				root1.getNumberOfOutputVariables( actualUnderobject )<<
				" output variables, but should have "<<
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] <<
				" output variables. "<<endl;
			iReturn++;
		}
	}
	//check getNumberOfOutputVariables() returnvalues if the number is out of bouderies
	if ( root1.getNumberOfOutputVariables( 0 ) == 0 ){
	
		cout<<"The root1 has correctly for the 0'th extern underobject"<<
			" 0 output variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has for the 0'th extern underobject "<<
			root1.getNumberOfOutputVariables( 0 )<<
			" output variables, but should have 0 output variables. "<<endl;
		iReturn++;
	}
	if ( root1.getNumberOfOutputVariables( uiExternSubobjects + 1 ) == 0 ){
	
		cout<<"The root1 has correctly for the "<<
			uiExternSubobjects + 1 <<"'th extern underobject"<<
			" 0 output variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has for the "<<
			uiExternSubobjects + 1 <<"'th extern underobject "<<
			root1.getNumberOfOutputVariables( uiExternSubobjects + 1 )<<
			" output variables, but should have 0 output variables. "<<endl;
		iReturn++;
	}

	//test setNumberOfExternSubobjects()
	uiExternSubobjects = 10;
	//set domain for 5'th external subobject
	cout<<"cTypeExtSubobject typeExtSubobject10( 10 );"<<endl;
	cTypeExtSubobject typeExtSubobject10( 10 );
	
	cout<<"root1.getDomains()->addDomain( typeExtSubobject10, domVectorE0 );"<<endl;
	root1.getDomains()->addDomain( typeExtSubobject10, domVectorE0 );
	
	//test getNumberOfExternSubobjects()
	if ( root1.getNumberOfExternSubobjects() == uiExternSubobjects ){
	
		cout<<"The root1 has correctly "<< uiExternSubobjects
			<<" extern underobjects. "<<endl;
	}else{
		cerr<<"Error: The root1 has "<< root1.getNumberOfExternSubobjects() <<
			" extern underobjects, but should have "<< uiExternSubobjects <<"."<<endl;
		iReturn++;
	}
	//test getNumberOfOutputVariables()
	for ( unsignedIntFib actualUnderobject = 1;
			actualUnderobject <= uiExternSubobjects; actualUnderobject++ ){
		
		if ( root1.getNumberOfOutputVariables( actualUnderobject ) ==
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] ){
		
			cout<<"The root1 has correctly for the "<< actualUnderobject
				<<"'th extern underobject "<<
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] <<
				" output variables. "<<endl;
		}else{
			cerr<<"Error: The root1 has for the "<< actualUnderobject
				<<"'th extern underobject "<<
				root1.getNumberOfOutputVariables( actualUnderobject )<<
				" output variables, but should have "<<
				aUiNumberOfOutputVariables[ actualUnderobject - 1 ] <<
				" output variables. "<<endl;
			iReturn++;
		}
	}
	//check getNumberOfOutputVariables() returnvalues if the number is out of bouderies
	if ( root1.getNumberOfOutputVariables( 0 ) == 0 ){
	
		cout<<"The root1 has correctly for the 0'th extern underobject"<<
			" 0 output variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has for the 0'th extern underobject "<<
			root1.getNumberOfOutputVariables( 0 )<<
			" output variables, but should have 0 output variables. "<<endl;
		iReturn++;
	}
	if ( root1.getNumberOfOutputVariables( uiExternSubobjects + 1 ) == 0 ){
	
		cout<<"The root1 has correctly for the "<<
			uiExternSubobjects + 1 <<"'th extern underobject"<<
			" 0 output variables. "<<endl;
	}else{
		cerr<<"Error: The root1 has for the "<<
			uiExternSubobjects + 1 <<"'th extern underobject "<<
			root1.getNumberOfOutputVariables( uiExternSubobjects + 1 )<<
			" output variables, but should have 0 output variables. "<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests the methods sub -root -objects of the cRoot class.
 *
 * methods tested:
 * 	- unsignedIntFib getNumberOfSubRootObjects() const;
 * 	- pair<longFib, cRoot*> getSubRootObject( unsignedIntFib uiNumberOfUnderObject );
 * 	- unsignedIntFib getSubRootObjectNumber( longFib lIdentifier ) const;
 * 	- cRoot * getSubRootObjectForIdentifier( longFib lIdentifier );
 * 	- bool addSubRootObject( longFib lIdentifier, cRoot * pRootObject, unsignedIntFib uiPosition=0 );
 * 	- bool deleteSubRootObject( unsignedIntFib uiSubRootObjectNumber, bool bDeleteOld=true );
 * 	- list<longFib> getAllSubRootObjectIdentifiers() const;
 * 	- list<longFib> getAllRootObjectIdentifiers() const;
 * 	- cRoot * getRootObject( longFib lIdentifier );
 * 	- list<longFib> getAllAccessibleRootObjectIdentifiers() const;
 * 	- cRoot * getAccessibleRootObject( longFib lIdentifier );
 * 	- list<longFib> getAllDatabaseObjectIdentifiers() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testSubRootObjects( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the sub -root -objects"<<endl;

	cout<<"cRoot root1;"<<endl;
	cRoot root1;
	
	//test getNumberOfSubRootObjects()
	if ( root1.getNumberOfSubRootObjects() == 0 ){
	
		cout<<"The root1 has correctly no sub -root -objects. "<<endl;
	}else{
		cerr<<"Error: The root1 has sub -root -objects."<<endl;
		iReturn++;
	}

	//test addSubRootObject()
	cout<<"cRoot root2;"<<endl;
	cRoot root2;
	cout<<"root1.addSubRootObject( 2, &root2 );"<<endl;
	bool bSubRootAdded = root1.addSubRootObject( 2, &root2 );
	vector< pair<longFib, cRoot*> > vecSubRootObjects1( 20, make_pair( 0, (cRoot*)NULL) );
	vecSubRootObjects1[1] = make_pair( 2, &root2);
	if ( bSubRootAdded){
	
		cout<<"The root2 was correctly added as an sub -root -objects in root1. "<<endl;
	}else{
		cerr<<"Error:The root2 wasn't added as an sub -root -objects in root1."<<endl;
		iReturn++;
	}
	//test getNumberOfSubRootObjects()
	if ( root1.getNumberOfSubRootObjects() == 1 ){
	
		cout<<"The root1 has correctly one sub -root -objects. "<<endl;
	}else{
		cerr<<"Error: The root1 has "<< root1.getNumberOfSubRootObjects() <<
			" sub -root -objects, but should have one."<<endl;
		iReturn++;
	}

	//test getSubRootObject()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		if ( root1.getSubRootObject( auctualSubRootObject ) ==
				vecSubRootObjects1[ auctualSubRootObject ] ){
		
			cout<<"The "<< auctualSubRootObject <<" sub -root -object of root1 is correct( identifier="<<
				root1.getSubRootObject( auctualSubRootObject ).first << " ). "<<endl;
		}else{
			cerr<<"Error: The "<< auctualSubRootObject <<" sub -root -object of root1 is not correct( identifier="<<
				root1.getSubRootObject( auctualSubRootObject ).first << " )."<<endl;
			iReturn++;
		}
	}
	if ( root1.getSubRootObject( 0 ) ==
			vecSubRootObjects1[ 0 ] ){
	
		cout<<"The "<< 0 <<" sub -root -object of root1 is correct. "<<endl;
	}else{
		cerr<<"Error: The "<< 0 <<" sub -root -object of root1 is not correct."<<endl;
		iReturn++;
	}
	if ( root1.getSubRootObject( root1.getNumberOfSubRootObjects() + 1 ) ==
			vecSubRootObjects1[ root1.getNumberOfSubRootObjects() + 1 ] ){
	
		cout<<"The "<< root1.getNumberOfSubRootObjects() + 1
			<<" sub -root -object of root1 is correct. "<<endl;
	}else{
		cerr<<"Error: The "<< root1.getNumberOfSubRootObjects() + 1
			<<" sub -root -object of root1 is not correct."<<endl;
		iReturn++;
	}

	//test addSubRootObject()
	cout<<"cRoot root3;"<<endl;
	cRoot root3;
	cout<<"root1.addSubRootObject( 3, &root3 );"<<endl;
	bSubRootAdded = root1.addSubRootObject( 3, &root3 );
	vector< pair<longFib, cRoot*> >::iterator itsSubRootInserPos =
		vecSubRootObjects1.begin();
	itsSubRootInserPos++;
	vecSubRootObjects1.insert( itsSubRootInserPos, make_pair( 3, &root3 ) );
	if ( bSubRootAdded){
	
		cout<<"The root -element was correctly added as an sub -root -objects in root1. "<<endl;
	}else{
		cerr<<"Error:The root -element wasn't added as an sub -root -objects in root1."<<endl;
		iReturn++;
	}
	//test getNumberOfSubRootObjects()
	if ( root1.getNumberOfSubRootObjects() == 2 ){
	
		cout<<"The root1 has correctly 2 sub -root -objects. "<<endl;
	}else{
		cerr<<"Error: The root1 has "<< root1.getNumberOfSubRootObjects() <<
			" sub -root -objects, but should have 2."<<endl;
		iReturn++;
	}

	//test getSubRootObject()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		if ( root1.getSubRootObject( auctualSubRootObject ) ==
				vecSubRootObjects1[ auctualSubRootObject ] ){
		
			cout<<"The "<< auctualSubRootObject <<" sub -root -object of root1 is correct( identifier="<<
				root1.getSubRootObject( auctualSubRootObject ).first << " ). "<<endl;
		}else{
			cerr<<"Error: The "<< auctualSubRootObject <<" sub -root -object of root1 is not correct( identifier="<<
				root1.getSubRootObject( auctualSubRootObject ).first << " )."<<endl;
			iReturn++;
		}
	}
	if ( root1.getSubRootObject( 0 ) ==
			vecSubRootObjects1[ 0 ] ){
	
		cout<<"The "<< 0 <<" sub -root -object of root1 is correct. "<<endl;
	}else{
		cerr<<"Error: The "<< 0 <<" sub -root -object of root1 is not correct."<<endl;
		iReturn++;
	}
	if ( root1.getSubRootObject( root1.getNumberOfSubRootObjects() + 1 ) ==
			vecSubRootObjects1[ root1.getNumberOfSubRootObjects() + 1 ] ){
	
		cout<<"The "<< root1.getNumberOfSubRootObjects() + 1
			<<" sub -root -object of root1 is correct. "<<endl;
	}else{
		cerr<<"Error: The "<< root1.getNumberOfSubRootObjects() + 1
			<<" sub -root -object of root1 is not correct."<<endl;
		iReturn++;
	}

	//test addSubRootObject()
	cout<<"cRoot root4;"<<endl;
	cRoot root4;
	cout<<"root1.addSubRootObject( 4, &root4, 0 );"<<endl;
	bSubRootAdded = root1.addSubRootObject( 4, &root4, 0 );
	itsSubRootInserPos = vecSubRootObjects1.begin();
	itsSubRootInserPos++;
	vecSubRootObjects1.insert( itsSubRootInserPos, make_pair( 4, &root4 ) );
	if ( bSubRootAdded){
	
		cout<<"The root -element was correctly added as an sub -root -objects in root1. "<<endl;
	}else{
		cerr<<"Error:The root -element wasn't added as an sub -root -objects in root1."<<endl;
		iReturn++;
	}
	//test getNumberOfSubRootObjects()
	if ( root1.getNumberOfSubRootObjects() == 3 ){
	
		cout<<"The root1 has correctly 3 sub -root -objects. "<<endl;
	}else{
		cerr<<"Error: The root1 has "<< root1.getNumberOfSubRootObjects() <<
			" sub -root -objects, but should have 3."<<endl;
		iReturn++;
	}

	//test getSubRootObject()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		if ( root1.getSubRootObject( auctualSubRootObject ) ==
				vecSubRootObjects1[ auctualSubRootObject ] ){
		
			cout<<"The "<< auctualSubRootObject <<" sub -root -object of root1 is correct( identifier="<<
				root1.getSubRootObject( auctualSubRootObject ).first << " ). "<<endl;
		}else{
			cerr<<"Error: The "<< auctualSubRootObject <<" sub -root -object of root1 is not correct( identifier="<<
				root1.getSubRootObject( auctualSubRootObject ).first << " )."<<endl;
			iReturn++;
		}
	}
	if ( root1.getSubRootObject( 0 ) ==
			vecSubRootObjects1[ 0 ] ){
	
		cout<<"The "<< 0 <<" sub -root -object of root1 is correct. "<<endl;
	}else{
		cerr<<"Error: The "<< 0 <<" sub -root -object of root1 is not correct."<<endl;
		iReturn++;
	}
	if ( root1.getSubRootObject( root1.getNumberOfSubRootObjects() + 1 ) ==
			vecSubRootObjects1[ root1.getNumberOfSubRootObjects() + 1 ] ){
	
		cout<<"The "<< root1.getNumberOfSubRootObjects() + 1
			<<" sub -root -object of root1 is correct. "<<endl;
	}else{
		cerr<<"Error: The "<< root1.getNumberOfSubRootObjects() + 1
			<<" sub -root -object of root1 is not correct."<<endl;
		iReturn++;
	}

	//test addSubRootObject()
	cout<<"cRoot root5;"<<endl;
	cRoot root5;
	cout<<"root1.addSubRootObject( 5, &root5, 10 );"<<endl;
	bSubRootAdded = root1.addSubRootObject( 5, &root5, 10 );
	vecSubRootObjects1[ 4 ] = make_pair( 5, &root5 );
	if ( bSubRootAdded){
	
		cout<<"The root -element was correctly added as an sub -root -objects in root1. "<<endl;
	}else{
		cerr<<"Error:The root -element wasn't added as an sub -root -objects in root1."<<endl;
		iReturn++;
	}
	//test getNumberOfSubRootObjects()
	if ( root1.getNumberOfSubRootObjects() == 4 ){
	
		cout<<"The root1 has correctly 4 sub -root -objects. "<<endl;
	}else{
		cerr<<"Error: The root1 has "<< root1.getNumberOfSubRootObjects() <<
			" sub -root -objects, but should have 4."<<endl;
		iReturn++;
	}

	//test getSubRootObject()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		if ( root1.getSubRootObject( auctualSubRootObject ) ==
				vecSubRootObjects1[ auctualSubRootObject ] ){
		
			cout<<"The "<< auctualSubRootObject <<" sub -root -object of root1 is correct( identifier="<<
				root1.getSubRootObject( auctualSubRootObject ).first << " ). "<<endl;
		}else{
			cerr<<"Error: The "<< auctualSubRootObject <<" sub -root -object of root1 is not correct( identifier="<<
				root1.getSubRootObject( auctualSubRootObject ).first << " )."<<endl;
			iReturn++;
		}
	}
	if ( root1.getSubRootObject( 0 ) ==
			vecSubRootObjects1[ 0 ] ){
	
		cout<<"The "<< 0 <<" sub -root -object of root1 is correct. "<<endl;
	}else{
		cerr<<"Error: The "<< 0 <<" sub -root -object of root1 is not correct."<<endl;
		iReturn++;
	}
	if ( root1.getSubRootObject( root1.getNumberOfSubRootObjects() + 1 ) ==
			vecSubRootObjects1[ root1.getNumberOfSubRootObjects() + 1 ] ){
	
		cout<<"The "<< root1.getNumberOfSubRootObjects() + 1
			<<" sub -root -object of root1 is correct. "<<endl;
	}else{
		cerr<<"Error: The "<< root1.getNumberOfSubRootObjects() + 1
			<<" sub -root -object of root1 is not correct."<<endl;
		iReturn++;
	}

	//test addSubRootObject()
	cout<<"cRoot root6;"<<endl;
	cRoot root6;
	cout<<"root1.addSubRootObject( 6, &root6, 4 );"<<endl;
	bSubRootAdded = root1.addSubRootObject( 6, &root6, 4 );
	vecSubRootObjects1[ 5 ] = vecSubRootObjects1[ 4 ];
	vecSubRootObjects1[ 4 ] = make_pair( 6, &root6 );
	if ( bSubRootAdded){
	
		cout<<"The root -element was correctly added as an sub -root -objects in root1. "<<endl;
	}else{
		cerr<<"Error:The root -element wasn't added as an sub -root -objects in root1."<<endl;
		iReturn++;
	}
	//test getNumberOfSubRootObjects()
	if ( root1.getNumberOfSubRootObjects() == 5 ){
	
		cout<<"The root1 has correctly 5 sub -root -objects. "<<endl;
	}else{
		cerr<<"Error: The root1 has "<< root1.getNumberOfSubRootObjects() <<
			" sub -root -objects, but should have 5."<<endl;
		iReturn++;
	}

	//test getSubRootObject()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		if ( root1.getSubRootObject( auctualSubRootObject ) ==
				vecSubRootObjects1[ auctualSubRootObject ] ){
		
			cout<<"The "<< auctualSubRootObject <<" sub -root -object of root1 is correct ( identifier="<<
				root1.getSubRootObject( auctualSubRootObject ).first << " ). "<<endl;
		}else{
			cerr<<"Error: The "<< auctualSubRootObject <<" sub -root -object of root1 is not correct( identifier="<<
				root1.getSubRootObject( auctualSubRootObject ).first << " )."<<endl;
			iReturn++;
		}
	}
	if ( root1.getSubRootObject( 0 ) ==
			vecSubRootObjects1[ 0 ] ){
	
		cout<<"The "<< 0 <<" sub -root -object of root1 is correct( identifier="<<
				root1.getSubRootObject( 0 ).first << ". "<<endl;
	}else{
		cerr<<"Error: The "<< 0 <<" sub -root -object of root1 is not correct( identifier="<<
			root1.getSubRootObject( 0 ).first << "."<<endl;
		iReturn++;
	}
	if ( root1.getSubRootObject( root1.getNumberOfSubRootObjects() + 1 ) ==
			vecSubRootObjects1[ root1.getNumberOfSubRootObjects() + 1 ] ){
	
		cout<<"The "<< root1.getNumberOfSubRootObjects() + 1
			<<" sub -root -object of root1 is correct( identifier="<<
			root1.getSubRootObject( root1.getNumberOfSubRootObjects() + 1 ).first << " ). "<<endl;
	}else{
		cerr<<"Error: The "<< root1.getNumberOfSubRootObjects() + 1
			<<" sub -root -object of root1 is not correct( identifier="<<
			root1.getSubRootObject( root1.getNumberOfSubRootObjects() + 1 ).first << " )."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the adding a existing identifer again"<<endl;

	//test addSubRootObject()
	cout<<"cRoot rootNo;"<<endl;
	cRoot rootNo;
	cout<<"root1.addSubRootObject( 3, &rootNo );"<<endl;
	bSubRootAdded = root1.addSubRootObject( 3, &rootNo );
	if ( ! bSubRootAdded){
	
		cout<<"The root -element was correctly not added as an sub -root -objects in root1. "<<endl;
	}else{
		cerr<<"Error:The root -element was added as an sub -root -objects in root1."<<endl;
		iReturn++;
	}
	cout<<"root1.addSubRootObject( 2, &root5, 10 );"<<endl;
	bSubRootAdded = root1.addSubRootObject( 2, &root5, 10 );
	if ( ! bSubRootAdded){
	
		cout<<"The root -element was correctly not added as an sub -root -objects in root1. "<<endl;
	}else{
		cerr<<"Error:The root -element was added as an sub -root -objects in root1."<<endl;
		iReturn++;
	}

	//test getNumberOfSubRootObjects()
	if ( root1.getNumberOfSubRootObjects() == 5 ){
	
		cout<<"The root1 has correctly 5 sub -root -objects. "<<endl;
	}else{
		cerr<<"Error: The root1 has "<< root1.getNumberOfSubRootObjects() <<
			" sub -root -objects, but should have 5."<<endl;
		iReturn++;
	}

	//test getSubRootObject()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		if ( root1.getSubRootObject( auctualSubRootObject ) ==
				vecSubRootObjects1[ auctualSubRootObject ] ){
		
			cout<<"The "<< auctualSubRootObject <<" sub -root -object of root1 is correct ( identifier="<<
				root1.getSubRootObject( auctualSubRootObject ).first << " ). "<<endl;
		}else{
			cerr<<"Error: The "<< auctualSubRootObject <<" sub -root -object of root1 is not correct( identifier="<<
				root1.getSubRootObject( auctualSubRootObject ).first << " )."<<endl;
			iReturn++;
		}
	}
	if ( root1.getSubRootObject( 0 ) ==
			vecSubRootObjects1[ 0 ] ){
	
		cout<<"The "<< 0 <<" sub -root -object of root1 is correct( identifier="<<
				root1.getSubRootObject( 0 ).first << ". "<<endl;
	}else{
		cerr<<"Error: The "<< 0 <<" sub -root -object of root1 is not correct( identifier="<<
			root1.getSubRootObject( 0 ).first << "."<<endl;
		iReturn++;
	}
	if ( root1.getSubRootObject( root1.getNumberOfSubRootObjects() + 1 ) ==
			vecSubRootObjects1[ root1.getNumberOfSubRootObjects() + 1 ] ){
	
		cout<<"The "<< root1.getNumberOfSubRootObjects() + 1
			<<" sub -root -object of root1 is correct( identifier="<<
			root1.getSubRootObject( root1.getNumberOfSubRootObjects() + 1 ).first << " ). "<<endl;
	}else{
		cerr<<"Error: The "<< root1.getNumberOfSubRootObjects() + 1
			<<" sub -root -object of root1 is not correct( identifier="<<
			root1.getSubRootObject( root1.getNumberOfSubRootObjects() + 1 ).first << " )."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getSubRootObjectNumber() method"<<endl;

	//test getSubRootObjectNumber()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		if ( root1.getSubRootObjectNumber( vecSubRootObjects1[ auctualSubRootObject ].first ) ==
				auctualSubRootObject ){
		
			cout<<"The sub -root -object with the identifier "<< 
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is correct on position "<<auctualSubRootObject <<
				" . "<<endl;
		}else{
			cerr<<"Error: The sub -root -object with the identifier "<< 
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is not on position "<<auctualSubRootObject <<
				" . "<<endl;
			iReturn++;
		}
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getSubRootObjectForIdentifier() method"<<endl;

	//test getSubRootObjectForIdentifier()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		if ( root1.getSubRootObjectForIdentifier( vecSubRootObjects1[ auctualSubRootObject ].first ) ==
				vecSubRootObjects1[ auctualSubRootObject ].second ){
		
			cout<<"The sub -root -object with the identifier "<< 
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is correctly the object root"<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<" . "<<endl;
		}else{
			cerr<<"Error: The sub -root -object with the identifier "<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is not the object root"<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<" . "<<endl;
			iReturn++;
		}
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getAllSubRootObjectIdentifiers() method"<<endl;

	cout<<"building root -element structur: "<<endl;

	cout<<"cRoot root2_1;"<<endl;
	cRoot root2_1;
	cout<<"root2.addSubRootObject( 21, &root2_1, 10 );"<<endl;
	root2.addSubRootObject( 21, &root2_1, 10 );

	cout<<"cRoot root3_1;"<<endl;
	cRoot root3_1;
	cout<<"root3.addSubRootObject( 31, &root3_1, 10 );"<<endl;
	root3.addSubRootObject( 31, &root3_1, 10 );

	cout<<"cRoot root3_2;"<<endl;
	cRoot root3_2;
	cout<<"root3.addSubRootObject( 32, &root3_2, 10 );"<<endl;
	root3.addSubRootObject( 32, &root3_2, 10 );

	cout<<"cRoot root3_2_1;"<<endl;
	cRoot root3_2_1;
	cout<<"root3_2.addSubRootObject( 321, &root3_2_1, 10 );"<<endl;
	root3_2.addSubRootObject( 321, &root3_2_1, 10 );

	cout<<"cRoot root3_3;"<<endl;
	cRoot root3_3;
	cout<<"root3.addSubRootObject( 33, &root3_3, 10 );"<<endl;
	root3.addSubRootObject( 33, &root3_3, 10 );

	cout<<"cRoot root4_1;"<<endl;
	cRoot root4_1;
	cout<<"root4.addSubRootObject( 41, &root4_1, 10 );"<<endl;
	root4.addSubRootObject( 41, &root4_1, 10 );

	
	cout<<endl;
	cout<<"liAllSubRootObjectId1 = root1.getAllSubRootObjectIdentifiers();"<<endl;
	list<longFib> liAllSubRootObjectId1 = root1.getAllSubRootObjectIdentifiers();

	//test getNumberOfSubRootObjects()
	if ( liAllSubRootObjectId1.size() == 5 ){
	
		cout<<"The liAllSubRootObjectId1 has correctly 5 sub -root -objects. "<<endl;
	}else{
		cerr<<"Error: The liAllSubRootObjectId1 has "<< liAllSubRootObjectId1.size() <<
			" sub -root -objects, but should have 5."<<endl;
		iReturn++;
	}

	//test getSubRootObject()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		list<longFib>::iterator itrSubRootId = find( liAllSubRootObjectId1.begin(),
			liAllSubRootObjectId1.end(),
			root1.getSubRootObject( auctualSubRootObject ).first );
		
		if ( itrSubRootId != liAllSubRootObjectId1.end() ){
		
			cout<<"The "<< auctualSubRootObject <<"'th sub -root -object of root1 "<<
				" was corectly found in liAllSubRootObjectId1. "<<endl;
		}else{
			cerr<<"Error: The "<< auctualSubRootObject <<"'th sub -root -object of root1 "<<
				" was not found in liAllSubRootObjectId1. "<<endl;
			iReturn++;
		}
	}
	
	cout<<endl;
	cout<<"liAllSubRootObjectId1 = root2.getAllSubRootObjectIdentifiers();"<<endl;
	liAllSubRootObjectId1 = root2.getAllSubRootObjectIdentifiers();

	if ( liAllSubRootObjectId1.size() == root2.getNumberOfSubRootObjects() ){
	
		cout<<"The liAllSubRootObjectId1 has correctly "<<
			root2.getNumberOfSubRootObjects()<<" sub -root -objects. "<<endl;
	}else{
		cerr<<"Error: The liAllSubRootObjectId1 has "<< liAllSubRootObjectId1.size() <<
			" sub -root -objects, but should have "<<
			root2.getNumberOfSubRootObjects()<<"."<<endl;
		iReturn++;
	}

	//test getSubRootObject()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root2.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		list<longFib>::iterator itrSubRootId = find( liAllSubRootObjectId1.begin(),
			liAllSubRootObjectId1.end(),
			root2.getSubRootObject( auctualSubRootObject ).first );
		
		if ( itrSubRootId != liAllSubRootObjectId1.end() ){
		
			cout<<"The "<< auctualSubRootObject <<"'th sub -root -object of root2 "<<
				" was corectly found in liAllSubRootObjectId1. "<<endl;
		}else{
			cerr<<"Error: The "<< auctualSubRootObject <<"'th sub -root -object of root2 "<<
				" was not found in liAllSubRootObjectId1. "<<endl;
			iReturn++;
		}
	}

	cout<<endl;
	cout<<"liAllSubRootObjectId1 = root3.getAllSubRootObjectIdentifiers();"<<endl;
	liAllSubRootObjectId1 = root3.getAllSubRootObjectIdentifiers();

	if ( liAllSubRootObjectId1.size() == root3.getNumberOfSubRootObjects() ){
	
		cout<<"The liAllSubRootObjectId1 has correctly "<<
			root3.getNumberOfSubRootObjects()<<" sub -root -objects. "<<endl;
	}else{
		cerr<<"Error: The liAllSubRootObjectId1 has "<< liAllSubRootObjectId1.size() <<
			" sub -root -objects, but should have "<<
			root3.getNumberOfSubRootObjects()<<"."<<endl;
		iReturn++;
	}

	//test getSubRootObject()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root3.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		list<longFib>::iterator itrSubRootId = find( liAllSubRootObjectId1.begin(),
			liAllSubRootObjectId1.end(),
			root3.getSubRootObject( auctualSubRootObject ).first );
		
		if ( itrSubRootId != liAllSubRootObjectId1.end() ){
		
			cout<<"The "<< auctualSubRootObject <<"'th sub -root -object of root3 "<<
				" was corectly found in liAllSubRootObjectId1. "<<endl;
		}else{
			cerr<<"Error: The "<< auctualSubRootObject <<"'th sub -root -object of root3 "<<
				" was not found in liAllSubRootObjectId1. "<<endl;
			iReturn++;
		}
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getAllRootObjectIdentifiers() method"<<endl;
	
	list<longFib> liAllRootObjectIdentifiers;
	
	//add all the identifiers from root 1
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		liAllRootObjectIdentifiers.push_back(
			root1.getSubRootObject( auctualSubRootObject ).first );
	}
	liAllRootObjectIdentifiers.push_back( 21 );
	liAllRootObjectIdentifiers.push_back( 31 );
	liAllRootObjectIdentifiers.push_back( 32 );
	liAllRootObjectIdentifiers.push_back( 321 );
	liAllRootObjectIdentifiers.push_back( 33 );
	liAllRootObjectIdentifiers.push_back( 41 );
	
	//insert database identifiers
	cFibDatabase * pFibDatabase = cFibDatabase::getInstance();
	list< longFib > liAllDatabaseObjects;
	if ( pFibDatabase != NULL ){
		//check the getAllDatabaseObjectIdentifiers() methode from cFibDatabase
		liAllDatabaseObjects = pFibDatabase->getAllDatabaseObjectIdentifiers();
	}
	liAllRootObjectIdentifiers.insert( liAllRootObjectIdentifiers.end(),
		liAllDatabaseObjects.begin(), liAllDatabaseObjects.end() );
	
	cout<<endl<<"liReturnedAllRootObjectIds = root1.getAllRootObjectIdentifiers();"<<endl;
	list<longFib> liReturnedAllRootObjectIds = root1.getAllRootObjectIdentifiers();
	
	if ( liAllRootObjectIdentifiers.size() == liReturnedAllRootObjectIds.size() ){
		
		cout<<"The returned number of sub -root -object is correctly "<<
			liReturnedAllRootObjectIds.size() <<" ."<<endl;
	}else{
		cerr<<"Error: The returned number of sub -root -object is "<<
			liReturnedAllRootObjectIds.size() <<", but should be "<<
			liAllRootObjectIdentifiers.size() <<" ."<<endl;
		iReturn++;
	}
	
	for ( list<longFib>::iterator itrReturnedSubRootIds =
			liReturnedAllRootObjectIds.begin(); 
			itrReturnedSubRootIds != liReturnedAllRootObjectIds.end();
			itrReturnedSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liAllRootObjectIdentifiers.begin(),
			liAllRootObjectIdentifiers.end(),
			(*itrReturnedSubRootIds) );
		
		if ( itrSubRootId != liAllRootObjectIdentifiers.end() ){
		
			cout<<"The identifier "<< (*itrReturnedSubRootIds) <<
				" was correctly given back. "<<endl;
		}else{
			cerr<<"Error: The identifier "<< (*itrReturnedSubRootIds) <<
				" was given back, but shouldn't. "<<endl;
			iReturn++;
		}
	}
	
	for ( list<longFib>::iterator itrSubRootIds =
			liAllRootObjectIdentifiers.begin(); 
			itrSubRootIds != liAllRootObjectIdentifiers.end();
			itrSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liReturnedAllRootObjectIds.begin(),
			liReturnedAllRootObjectIds.end(),
			(*itrSubRootIds) );
		
		if ( itrSubRootId == liReturnedAllRootObjectIds.end() ){
			cerr<<"Error: The identifier "<< (*itrSubRootIds) <<
				" was wasn't found in the returned identifiers. "<<endl;
			iReturn++;
		}
	}

	cout<<endl<<"liReturnedAllRootObjectIds = root2.getAllRootObjectIdentifiers();"<<endl;
	liReturnedAllRootObjectIds = root2.getAllRootObjectIdentifiers();
	
	if ( liAllRootObjectIdentifiers.size() == liReturnedAllRootObjectIds.size() ){
		
		cout<<"The returned number of sub -root -object is correctly "<<
			liReturnedAllRootObjectIds.size() <<" ."<<endl;
	}else{
		cerr<<"Error: The returned number of sub -root -object is "<<
			liReturnedAllRootObjectIds.size() <<", but should be"<<
			liAllRootObjectIdentifiers.size() <<" ."<<endl;
		iReturn++;
	}
	
	for ( list<longFib>::iterator itrReturnedSubRootIds =
			liReturnedAllRootObjectIds.begin(); 
			itrReturnedSubRootIds != liReturnedAllRootObjectIds.end();
			itrReturnedSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liAllRootObjectIdentifiers.begin(),
			liAllRootObjectIdentifiers.end(),
			(*itrReturnedSubRootIds) );
		
		if ( itrSubRootId != liAllRootObjectIdentifiers.end() ){
		
			cout<<"The identifier "<< (*itrReturnedSubRootIds) <<
				" was correctly given back. "<<endl;
		}else{
			cerr<<"Error: The identifier "<< (*itrReturnedSubRootIds) <<
				" was given back, but shouldn't. "<<endl;
			iReturn++;
		}
	}
	
	for ( list<longFib>::iterator itrSubRootIds =
			liAllRootObjectIdentifiers.begin(); 
			itrSubRootIds != liAllRootObjectIdentifiers.end();
			itrSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liReturnedAllRootObjectIds.begin(),
			liReturnedAllRootObjectIds.end(),
			(*itrSubRootIds) );
		
		if ( itrSubRootId == liReturnedAllRootObjectIds.end() ){
			cerr<<"Error: The identifier "<< (*itrSubRootIds) <<
				" was wasn't found in the returned identifiers. "<<endl;
			iReturn++;
		}
	}

	cout<<endl<<"liReturnedAllRootObjectIds = root3_2_1.getAllRootObjectIdentifiers();"<<endl;
	liReturnedAllRootObjectIds = root3_2_1.getAllRootObjectIdentifiers();
	
	if ( liAllRootObjectIdentifiers.size() == liReturnedAllRootObjectIds.size() ){
		
		cout<<"The returned number of sub -root -object is correctly "<<
			liReturnedAllRootObjectIds.size() <<" ."<<endl;
	}else{
		cerr<<"Error: The returned number of sub -root -object is "<<
			liReturnedAllRootObjectIds.size() <<", but should be"<<
			liAllRootObjectIdentifiers.size() <<" ."<<endl;
		iReturn++;
	}
	
	for ( list<longFib>::iterator itrReturnedSubRootIds =
			liReturnedAllRootObjectIds.begin(); 
			itrReturnedSubRootIds != liReturnedAllRootObjectIds.end();
			itrReturnedSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liAllRootObjectIdentifiers.begin(),
			liAllRootObjectIdentifiers.end(),
			(*itrReturnedSubRootIds) );
		
		if ( itrSubRootId != liAllRootObjectIdentifiers.end() ){
		
			cout<<"The identifier "<< (*itrReturnedSubRootIds) <<
				" was correctly given back. "<<endl;
		}else{
			cerr<<"Error: The identifier "<< (*itrReturnedSubRootIds) <<
				" was given back, but shouldn't. "<<endl;
			iReturn++;
		}
	}
	
	for ( list<longFib>::iterator itrSubRootIds =
			liAllRootObjectIdentifiers.begin(); 
			itrSubRootIds != liAllRootObjectIdentifiers.end();
			itrSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liReturnedAllRootObjectIds.begin(),
			liReturnedAllRootObjectIds.end(),
			(*itrSubRootIds) );
		
		if ( itrSubRootId == liReturnedAllRootObjectIds.end() ){
			cerr<<"Error: The identifier "<< (*itrSubRootIds) <<
				" was wasn't found in the returned identifiers. "<<endl;
			iReturn++;
		}
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getRootObject() method for root1"<<endl;

	cout<<"pRoot2 = root1.getRootObject( 2 );"<<endl;
	cRoot * pRoot2 = root1.getRootObject( 2 );
	if ( pRoot2 != NULL ){
		
		if ( pRoot2 == &root2 ){
			
			cout<<"The returned root -object is the correct root -object."<<endl;
		}else{
			cerr<<"Error: The returned root -object is not the correct root -object."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The no sub -root -object was returned (NULL was returned) ."<<endl;
		iReturn++;
	}
	cout<<"pRoot4 = root1.getRootObject( 4 );"<<endl;
	cRoot * pRoot4 = root1.getRootObject( 4 );
	if ( pRoot4 != NULL ){
		
		if ( pRoot4 == &root4 ){
			
			cout<<"The returned root -object is the correct root -object."<<endl;
		}else{
			cerr<<"Error: The returned root -object is not the correct root -object."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The no sub -root -object was returned (NULL was returned) ."<<endl;
		iReturn++;
	}

	cout<<"pRoot2_1 = root1.getRootObject( 21 );"<<endl;
	cRoot * pRoot2_1 = root1.getRootObject( 21 );
	if ( pRoot2_1 != NULL ){
		
		if ( pRoot2_1 == &root2_1 ){
			
			cout<<"The returned root -object is the correct root -object."<<endl;
		}else{
			cerr<<"Error: The returned root -object is not the correct root -object."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The no sub -root -object was returned (NULL was returned) ."<<endl;
		iReturn++;
	}

	cout<<"pRoot3_2_1 = root1.getRootObject( 321 );"<<endl;
	cRoot * pRoot3_2_1 = root1.getRootObject( 321 );
	if ( pRoot3_2_1 != NULL ){
		
		if ( pRoot3_2_1 == &root3_2_1 ){
			
			cout<<"The returned root -object is the correct root -object."<<endl;
		}else{
			cerr<<"Error: The returned root -object is not the correct root -object."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The no sub -root -object was returned (NULL was returned) ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getRootObject() method for root4"<<endl;

	cout<<"pRoot2 = root4.getRootObject( 2 );"<<endl;
	pRoot2 = root4.getRootObject( 2 );
	if ( pRoot2 != NULL ){
		
		if ( pRoot2 == &root2 ){
			
			cout<<"The returned root -object is the correct root -object."<<endl;
		}else{
			cerr<<"Error: The returned root -object is not the correct root -object."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The no sub -root -object was returned (NULL was returned) ."<<endl;
		iReturn++;
	}
	cout<<"pRoot4 = root4.getRootObject( 4 );"<<endl;
	pRoot4 = root4.getRootObject( 4 );
	if ( pRoot4 != NULL ){
		
		if ( pRoot4 == &root4 ){
			
			cout<<"The returned root -object is the correct root -object."<<endl;
		}else{
			cerr<<"Error: The returned root -object is not the correct root -object."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The no sub -root -object was returned (NULL was returned) ."<<endl;
		iReturn++;
	}

	cout<<"pRoot2_1 = root4.getRootObject( 21 );"<<endl;
	pRoot2_1 = root4.getRootObject( 21 );
	if ( pRoot2_1 != NULL ){
		
		if ( pRoot2_1 == &root2_1 ){
			
			cout<<"The returned root -object is the correct root -object."<<endl;
		}else{
			cerr<<"Error: The returned root -object is not the correct root -object."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The no sub -root -object was returned (NULL was returned) ."<<endl;
		iReturn++;
	}

	cout<<"pRoot3_2_1 = root4.getRootObject( 321 );"<<endl;
	pRoot3_2_1 = root4.getRootObject( 321 );
	if ( pRoot3_2_1 != NULL ){
		
		if ( pRoot3_2_1 == &root3_2_1 ){
			
			cout<<"The returned root -object is the correct root -object."<<endl;
		}else{
			cerr<<"Error: The returned root -object is not the correct root -object."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The no sub -root -object was returned (NULL was returned) ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getRootObject() method for root3_2_1"<<endl;

	cout<<"pRoot2 = root3_2_1.getRootObject( 2 );"<<endl;
	pRoot2 = root3_2_1.getRootObject( 2 );
	if ( pRoot2 != NULL ){
		
		if ( pRoot2 == &root2 ){
			
			cout<<"The returned root -object is the correct root -object."<<endl;
		}else{
			cerr<<"Error: The returned root -object is not the correct root -object."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The no sub -root -object was returned (NULL was returned) ."<<endl;
		iReturn++;
	}
	cout<<"pRoot4 = root3_2_1.getRootObject( 4 );"<<endl;
	pRoot4 = root3_2_1.getRootObject( 4 );
	if ( pRoot4 != NULL ){
		
		if ( pRoot4 == &root4 ){
			
			cout<<"The returned root -object is the correct root -object."<<endl;
		}else{
			cerr<<"Error: The returned root -object is not the correct root -object."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The no sub -root -object was returned (NULL was returned) ."<<endl;
		iReturn++;
	}

	cout<<"pRoot2_1 = root3_2_1.getRootObject( 21 );"<<endl;
	pRoot2_1 = root3_2_1.getRootObject( 21 );
	if ( pRoot2_1 != NULL ){
		
		if ( pRoot2_1 == &root2_1 ){
			
			cout<<"The returned root -object is the correct root -object."<<endl;
		}else{
			cerr<<"Error: The returned root -object is not the correct root -object."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The no sub -root -object was returned (NULL was returned) ."<<endl;
		iReturn++;
	}

	cout<<"pRoot3_2_1 = root3_2_1.getRootObject( 321 );"<<endl;
	pRoot3_2_1 = root3_2_1.getRootObject( 321 );
	if ( pRoot3_2_1 != NULL ){
		
		if ( pRoot3_2_1 == &root3_2_1 ){
			
			cout<<"The returned root -object is the correct root -object."<<endl;
		}else{
			cerr<<"Error: The returned root -object is not the correct root -object."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The no sub -root -object was returned (NULL was returned) ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for getting accessible roots for root1"<<endl;

	list<longFib> liAccessibleRootIds;
	//add all the identifiers from root 1
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		liAccessibleRootIds.push_back(
			root1.getSubRootObject( auctualSubRootObject ).first );
	}
	//add database objects
	liAccessibleRootIds.insert( liAccessibleRootIds.end(),
		liAllDatabaseObjects.begin(), liAllDatabaseObjects.end() );
	
	cout<<"liReturnedAccessibleRootIds = root1.getAllAccessibleRootObjectIdentifiers();"<<endl;
	list<longFib> liReturnedAccessibleRootIds = root1.getAllAccessibleRootObjectIdentifiers();
	
	if ( liAccessibleRootIds.size() == liReturnedAccessibleRootIds.size() ){
		
		cout<<"The returned number of accessible sub -root -object is correctly "<<
			liReturnedAccessibleRootIds.size() <<" ."<<endl;
	}else{
		cerr<<"Error: The returned number of accessible sub -root -object is "<<
			liReturnedAccessibleRootIds.size() <<", but should be"<<
			liAccessibleRootIds.size() <<" ."<<endl;
		iReturn++;
	}
	
	for ( list<longFib>::iterator itrReturnedSubRootIds =
			liReturnedAccessibleRootIds.begin();
			itrReturnedSubRootIds != liReturnedAccessibleRootIds.end();
			itrReturnedSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liAccessibleRootIds.begin(),
			liAccessibleRootIds.end(),
			(*itrReturnedSubRootIds) );
		
		if ( itrSubRootId != liAccessibleRootIds.end() ){
		
			cout<<"The identifier "<< (*itrReturnedSubRootIds) <<
				" was correctly given back. "<<endl;
		}else{
			cerr<<"Error: The identifier "<< (*itrReturnedSubRootIds) <<
				" was given back, but shouldn't. "<<endl;
			iReturn++;
		}
	}
	for ( list<longFib>::iterator itrSubRootIds =
			liAccessibleRootIds.begin(); 
			itrSubRootIds != liAccessibleRootIds.end();
			itrSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liReturnedAccessibleRootIds.begin(),
			liReturnedAccessibleRootIds.end(),
			(*itrSubRootIds) );
		
		if ( itrSubRootId == liReturnedAccessibleRootIds.end() ){
			cerr<<"Error: The identifier "<< (*itrSubRootIds) <<
				" was wasn't found in the returned identifiers. "<<endl;
			iReturn++;
		}
	}

	for ( list<longFib>::iterator itrSubRootIds =
			liAccessibleRootIds.begin(); 
			itrSubRootIds != liAccessibleRootIds.end();
			itrSubRootIds++  ){
		
		cout<<"rootAccessible = root1.getAccessibleRootObject( "<< (*itrSubRootIds) <<" );"<<endl;
		cRoot * rootAccessible = root1.getAccessibleRootObject( (*itrSubRootIds) );
		
		if ( rootAccessible != NULL ){
		
			cout<<"The root object for the identifier "<< (*itrSubRootIds) <<
				" was correctly given back. "<<endl;
		}else{
			cerr<<"Error: The root object for the identifier "<< (*itrSubRootIds) <<
				" was not given back, but should. "<<endl;
			iReturn++;
		}

	}
	longFib ulNotAccessibleRoot = 31;
	cout<<"rootAccessible = root1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	cRoot * rootAccessible = root1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}
	ulNotAccessibleRoot = 321;
	cout<<"rootAccessible = root1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}
	ulNotAccessibleRoot = 41;
	cout<<"rootAccessible = root1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for getting accessible roots for root2_1"<<endl;

	liAccessibleRootIds.clear();
	liAccessibleRootIds.push_back( 5 );
	liAccessibleRootIds.push_back( 6 );
	
	//add database objects
	liAccessibleRootIds.insert( liAccessibleRootIds.end(),
		liAllDatabaseObjects.begin(), liAllDatabaseObjects.end() );

	cout<<"liReturnedAccessibleRootIds = root2_1.getAllAccessibleRootObjectIdentifiers();"<<endl;
	liReturnedAccessibleRootIds = root2_1.getAllAccessibleRootObjectIdentifiers();
	
	if ( liAccessibleRootIds.size() == liReturnedAccessibleRootIds.size() ){
		
		cout<<"The returned number of accessible sub -root -object is correctly "<<
			liReturnedAccessibleRootIds.size() <<" ."<<endl;
	}else{
		cerr<<"Error: The returned number of accessible sub -root -object is "<<
			liReturnedAccessibleRootIds.size() <<", but should be "<<
			liAccessibleRootIds.size() <<" ."<<endl;
		iReturn++;
	}
	
	for ( list<longFib>::iterator itrReturnedSubRootIds =
			liReturnedAccessibleRootIds.begin();
			itrReturnedSubRootIds != liReturnedAccessibleRootIds.end();
			itrReturnedSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liAccessibleRootIds.begin(),
			liAccessibleRootIds.end(),
			(*itrReturnedSubRootIds) );
		
		if ( itrSubRootId != liAccessibleRootIds.end() ){
		
			cout<<"The identifier "<< (*itrReturnedSubRootIds) <<
				" was correctly given back. "<<endl;
		}else{
			cerr<<"Error: The identifier "<< (*itrReturnedSubRootIds) <<
				" was given back, but shouldn't. "<<endl;
			iReturn++;
		}
	}
	for ( list<longFib>::iterator itrSubRootIds =
			liAccessibleRootIds.begin(); 
			itrSubRootIds != liAccessibleRootIds.end();
			itrSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liReturnedAccessibleRootIds.begin(),
			liReturnedAccessibleRootIds.end(),
			(*itrSubRootIds) );
		
		if ( itrSubRootId == liReturnedAccessibleRootIds.end() ){
			cerr<<"Error: The identifier "<< (*itrSubRootIds) <<
				" was wasn't found in the returned identifiers. "<<endl;
			iReturn++;
		}
	}

	for ( list<longFib>::iterator itrSubRootIds =
			liAccessibleRootIds.begin(); 
			itrSubRootIds != liAccessibleRootIds.end();
			itrSubRootIds++  ){
		
		cout<<"rootAccessible = root2_1.getAccessibleRootObject( "<< (*itrSubRootIds) <<" );"<<endl;
		cRoot * rootAccessible = root2_1.getAccessibleRootObject( (*itrSubRootIds) );
		
		if ( rootAccessible != NULL ){
		
			cout<<"The root object for the identifier "<< (*itrSubRootIds) <<
				" was correctly given back. "<<endl;
		}else{
			cerr<<"Error: The root object for the identifier "<< (*itrSubRootIds) <<
				" was not given back, but should. "<<endl;
			iReturn++;
		}

	}
	ulNotAccessibleRoot = 2;
	cout<<"rootAccessible = root2_1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root2_1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}

	ulNotAccessibleRoot = 31;
	cout<<"rootAccessible = root2_1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root2_1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}
	ulNotAccessibleRoot = 321;
	cout<<"rootAccessible = root2_1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root2_1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}
	ulNotAccessibleRoot = 41;
	cout<<"rootAccessible = root2_1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root2_1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for getting accessible roots for root3_2_1"<<endl;

	liAccessibleRootIds.clear();
	liAccessibleRootIds.push_back( 2 );
	liAccessibleRootIds.push_back( 5 );
	liAccessibleRootIds.push_back( 6 );
	liAccessibleRootIds.push_back( 33 );

	//add database objects
	liAccessibleRootIds.insert( liAccessibleRootIds.end(),
		liAllDatabaseObjects.begin(), liAllDatabaseObjects.end() );

	cout<<"liReturnedAccessibleRootIds = root3_2_1.getAllAccessibleRootObjectIdentifiers();"<<endl;
	liReturnedAccessibleRootIds = root3_2_1.getAllAccessibleRootObjectIdentifiers();
	
	if ( liAccessibleRootIds.size() == liReturnedAccessibleRootIds.size() ){
		
		cout<<"The returned number of accessible sub -root -object is correctly "<<
			liReturnedAccessibleRootIds.size() <<" ."<<endl;
	}else{
		cerr<<"Error: The returned number of accessible sub -root -object is "<<
			liReturnedAccessibleRootIds.size() <<", but should be "<<
			liAccessibleRootIds.size() <<" ."<<endl;
		iReturn++;
	}
	
	for ( list<longFib>::iterator itrReturnedSubRootIds =
			liReturnedAccessibleRootIds.begin();
			itrReturnedSubRootIds != liReturnedAccessibleRootIds.end();
			itrReturnedSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liAccessibleRootIds.begin(),
			liAccessibleRootIds.end(),
			(*itrReturnedSubRootIds) );
		
		if ( itrSubRootId != liAccessibleRootIds.end() ){
		
			cout<<"The identifier "<< (*itrReturnedSubRootIds) <<
				" was correctly given back. "<<endl;
		}else{
			cerr<<"Error: The identifier "<< (*itrReturnedSubRootIds) <<
				" was given back, but shouldn't. "<<endl;
			iReturn++;
		}
	}
	for ( list<longFib>::iterator itrSubRootIds =
			liAccessibleRootIds.begin(); 
			itrSubRootIds != liAccessibleRootIds.end();
			itrSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liReturnedAccessibleRootIds.begin(),
			liReturnedAccessibleRootIds.end(),
			(*itrSubRootIds) );
		
		if ( itrSubRootId == liReturnedAccessibleRootIds.end() ){
			cerr<<"Error: The identifier "<< (*itrSubRootIds) <<
				" was wasn't found in the returned identifiers. "<<endl;
			iReturn++;
		}
	}

	for ( list<longFib>::iterator itrSubRootIds =
			liAccessibleRootIds.begin(); 
			itrSubRootIds != liAccessibleRootIds.end();
			itrSubRootIds++  ){
		
		cout<<"rootAccessible = root3_2_1.getAccessibleRootObject( "<< (*itrSubRootIds) <<" );"<<endl;
		cRoot * rootAccessible = root3_2_1.getAccessibleRootObject( (*itrSubRootIds) );
		
		if ( rootAccessible != NULL ){
		
			cout<<"The root object for the identifier "<< (*itrSubRootIds) <<
				" was correctly given back. "<<endl;
		}else{
			cerr<<"Error: The root object for the identifier "<< (*itrSubRootIds) <<
				" was not given back, but should. "<<endl;
			iReturn++;
		}

	}
	ulNotAccessibleRoot = 3;
	cout<<"rootAccessible = root3_2_1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root3_2_1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}

	ulNotAccessibleRoot = 31;
	cout<<"rootAccessible = root3_2_1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root3_2_1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}
	ulNotAccessibleRoot = 321;
	cout<<"rootAccessible = root3_2_1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root3_2_1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}
	ulNotAccessibleRoot = 41;
	cout<<"rootAccessible = root3_2_1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root3_2_1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for getting accessible roots for root4_1"<<endl;

	liAccessibleRootIds.clear();
	liAccessibleRootIds.push_back( 2 );
	liAccessibleRootIds.push_back( 3 );
	liAccessibleRootIds.push_back( 5 );
	liAccessibleRootIds.push_back( 6 );

	//add database objects
	liAccessibleRootIds.insert( liAccessibleRootIds.end(),
		liAllDatabaseObjects.begin(), liAllDatabaseObjects.end() );

	cout<<"liReturnedAccessibleRootIds = root4_1.getAllAccessibleRootObjectIdentifiers();"<<endl;
	liReturnedAccessibleRootIds = root4_1.getAllAccessibleRootObjectIdentifiers();
	
	if ( liAccessibleRootIds.size() == liReturnedAccessibleRootIds.size() ){
		
		cout<<"The returned number of accessible sub -root -object is correctly "<<
			liReturnedAccessibleRootIds.size() <<" ."<<endl;
	}else{
		cerr<<"Error: The returned number of accessible sub -root -object is "<<
			liReturnedAccessibleRootIds.size() <<", but should be "<<
			liAccessibleRootIds.size() <<" ."<<endl;
		iReturn++;
	}
	
	for ( list<longFib>::iterator itrReturnedSubRootIds =
			liReturnedAccessibleRootIds.begin();
			itrReturnedSubRootIds != liReturnedAccessibleRootIds.end();
			itrReturnedSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liAccessibleRootIds.begin(),
			liAccessibleRootIds.end(),
			(*itrReturnedSubRootIds) );
		
		if ( itrSubRootId != liAccessibleRootIds.end() ){
		
			cout<<"The identifier "<< (*itrReturnedSubRootIds) <<
				" was correctly given back. "<<endl;
		}else{
			cerr<<"Error: The identifier "<< (*itrReturnedSubRootIds) <<
				" was given back, but shouldn't. "<<endl;
			iReturn++;
		}
	}
	for ( list<longFib>::iterator itrSubRootIds =
			liAccessibleRootIds.begin(); 
			itrSubRootIds != liAccessibleRootIds.end();
			itrSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liReturnedAccessibleRootIds.begin(),
			liReturnedAccessibleRootIds.end(),
			(*itrSubRootIds) );
		
		if ( itrSubRootId == liReturnedAccessibleRootIds.end() ){
			cerr<<"Error: The identifier "<< (*itrSubRootIds) <<
				" was wasn't found in the returned identifiers. "<<endl;
			iReturn++;
		}
	}

	for ( list<longFib>::iterator itrSubRootIds =
			liAccessibleRootIds.begin(); 
			itrSubRootIds != liAccessibleRootIds.end();
			itrSubRootIds++  ){
		
		cout<<"rootAccessible = root4_1.getAccessibleRootObject( "<< (*itrSubRootIds) <<" );"<<endl;
		cRoot * rootAccessible = root4_1.getAccessibleRootObject( (*itrSubRootIds) );
		
		if ( rootAccessible != NULL ){
		
			cout<<"The root object for the identifier "<< (*itrSubRootIds) <<
				" was correctly given back. "<<endl;
		}else{
			cerr<<"Error: The root object for the identifier "<< (*itrSubRootIds) <<
				" was not given back, but should. "<<endl;
			iReturn++;
		}

	}
	ulNotAccessibleRoot = 31;
	cout<<"rootAccessible = root4_1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root4_1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}

	ulNotAccessibleRoot = 32;
	cout<<"rootAccessible = root4_1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root4_1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}
	ulNotAccessibleRoot = 321;
	cout<<"rootAccessible = root4_1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root4_1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}
	ulNotAccessibleRoot = 41;
	cout<<"rootAccessible = root4_1.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root4_1.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for getting accessible roots for root5"<<endl;

	liAccessibleRootIds.clear();

	//add database objects
	liAccessibleRootIds.insert( liAccessibleRootIds.end(),
		liAllDatabaseObjects.begin(), liAllDatabaseObjects.end() );

	cout<<"liReturnedAccessibleRootIds = root5.getAllAccessibleRootObjectIdentifiers();"<<endl;
	liReturnedAccessibleRootIds = root5.getAllAccessibleRootObjectIdentifiers();
	
	if ( liAccessibleRootIds.size() == liReturnedAccessibleRootIds.size() ){
		
		cout<<"The returned number of accessible sub -root -object is correctly "<<
			liReturnedAccessibleRootIds.size() <<" ."<<endl;
	}else{
		cerr<<"Error: The returned number of accessible sub -root -object is "<<
			liReturnedAccessibleRootIds.size() <<", but should be "<<
			liAccessibleRootIds.size() <<" ."<<endl;
		iReturn++;
	}
	
	for ( list<longFib>::iterator itrReturnedSubRootIds =
			liReturnedAccessibleRootIds.begin();
			itrReturnedSubRootIds != liReturnedAccessibleRootIds.end();
			itrReturnedSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liAccessibleRootIds.begin(),
			liAccessibleRootIds.end(),
			(*itrReturnedSubRootIds) );
		
		if ( itrSubRootId != liAccessibleRootIds.end() ){
		
			cout<<"The identifier "<< (*itrReturnedSubRootIds) <<
				" was correctly given back. "<<endl;
		}else{
			cerr<<"Error: The identifier "<< (*itrReturnedSubRootIds) <<
				" was given back, but shouldn't. "<<endl;
			iReturn++;
		}
	}
	for ( list<longFib>::iterator itrSubRootIds =
			liAccessibleRootIds.begin(); 
			itrSubRootIds != liAccessibleRootIds.end();
			itrSubRootIds++  ){
		
		list<longFib>::iterator itrSubRootId = find(
			liReturnedAccessibleRootIds.begin(),
			liReturnedAccessibleRootIds.end(),
			(*itrSubRootIds) );
		
		if ( itrSubRootId == liReturnedAccessibleRootIds.end() ){
			cerr<<"Error: The identifier "<< (*itrSubRootIds) <<
				" was wasn't found in the returned identifiers. "<<endl;
			iReturn++;
		}
	}

	for ( list<longFib>::iterator itrSubRootIds =
			liAccessibleRootIds.begin(); 
			itrSubRootIds != liAccessibleRootIds.end();
			itrSubRootIds++  ){
		
		cout<<"rootAccessible = root5.getAccessibleRootObject( "<< (*itrSubRootIds) <<" );"<<endl;
		cRoot * rootAccessible = root5.getAccessibleRootObject( (*itrSubRootIds) );
		
		if ( rootAccessible != NULL ){
		
			cout<<"The root object for the identifier "<< (*itrSubRootIds) <<
				" was correctly given back. "<<endl;
		}else{
			cerr<<"Error: The root object for the identifier "<< (*itrSubRootIds) <<
				" was not given back, but should. "<<endl;
			iReturn++;
		}

	}
	ulNotAccessibleRoot = 31;
	cout<<"rootAccessible = root5.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root5.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}

	ulNotAccessibleRoot = 32;
	cout<<"rootAccessible = root5.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root5.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}
	ulNotAccessibleRoot = 321;
	cout<<"rootAccessible = root5.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root5.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}
	ulNotAccessibleRoot = 41;
	cout<<"rootAccessible = root5.getAccessibleRootObject( "<< ulNotAccessibleRoot <<" );"<<endl;
	rootAccessible = root5.getAccessibleRootObject( ulNotAccessibleRoot );
	
	if ( rootAccessible == NULL ){
	
		cout<<"No root object for the identifier "<< ulNotAccessibleRoot <<
			" was correctly given back. "<<endl;
	}else{
		cerr<<"Error: The root object for the identifier "<< ulNotAccessibleRoot <<
			" was given back, but shouldn't. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the deleteSubRootObject() method"<<endl;

	cout<<"bSubRootObjectDeleted = root1.deleteSubRootObject( 1, false );"<<endl;
	bool bSubRootObjectDeleted = root1.deleteSubRootObject( 1, false );
	
	vecSubRootObjects1.erase( vecSubRootObjects1.begin() );
	
	if ( bSubRootObjectDeleted ){
	
		cout<<"The sub -root -object could be deleted. "<<endl;
	}else{
		cerr<<"Error: The sub -root -object couldn't be deleted. "<<endl;
		iReturn++;
	}

	//test getSubRootObjectForIdentifier()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		if ( root1.getSubRootObjectForIdentifier( vecSubRootObjects1[ auctualSubRootObject ].first ) ==
				vecSubRootObjects1[ auctualSubRootObject ].second ){
		
			cout<<"The sub -root -object with the identifier "<< 
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is correctly the object root"<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<" . "<<endl;
		}else{
			cerr<<"Error: The sub -root -object with the identifier "<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is not the object root"<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<" . "<<endl;
			iReturn++;
		}
	}

	cout<<endl<<"bSubRootObjectDeleted = root1.deleteSubRootObject( 1, false );"<<endl;
	bSubRootObjectDeleted = root1.deleteSubRootObject( 1, false );
	
	vecSubRootObjects1.erase( vecSubRootObjects1.begin() );
	
	if ( bSubRootObjectDeleted ){
	
		cout<<"The sub -root -object could be deleted. "<<endl;
	}else{
		cerr<<"Error: The sub -root -object couldn't be deleted. "<<endl;
		iReturn++;
	}

	//test getSubRootObjectForIdentifier()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		if ( root1.getSubRootObjectForIdentifier( vecSubRootObjects1[ auctualSubRootObject ].first ) ==
				vecSubRootObjects1[ auctualSubRootObject ].second ){
		
			cout<<"The sub -root -object with the identifier "<< 
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is correctly the object root"<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<" . "<<endl;
		}else{
			cerr<<"Error: The sub -root -object with the identifier "<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is not the object root"<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<" . "<<endl;
			iReturn++;
		}
	}

	cout<<endl<<"bSubRootObjectDeleted = root1.deleteSubRootObject( root1.getNumberOfSubRootObjects(), false );"<<endl;
	bSubRootObjectDeleted = root1.deleteSubRootObject( root1.getNumberOfSubRootObjects(), false );
	
	vecSubRootObjects1.pop_back();
	
	if ( bSubRootObjectDeleted ){
	
		cout<<"The sub -root -object could be deleted. "<<endl;
	}else{
		cerr<<"Error: The sub -root -object couldn't be deleted. "<<endl;
		iReturn++;
	}

	//test getSubRootObjectForIdentifier()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		if ( root1.getSubRootObjectForIdentifier( vecSubRootObjects1[ auctualSubRootObject ].first ) ==
				vecSubRootObjects1[ auctualSubRootObject ].second ){
		
			cout<<"The sub -root -object with the identifier "<< 
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is correctly the object root"<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<" . "<<endl;
		}else{
			cerr<<"Error: The sub -root -object with the identifier "<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is not the object root"<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<" . "<<endl;
			iReturn++;
		}
	}

	cout<<endl<<"bSubRootObjectDeleted = root1.deleteSubRootObject( root1.getNumberOfSubRootObjects() + 1 , false );"<<endl;
	bSubRootObjectDeleted = root1.deleteSubRootObject( root1.getNumberOfSubRootObjects() + 1 , false );
	
	if ( !bSubRootObjectDeleted ){
	
		cout<<"The sub -root -object couldn't correctly be deleted. "<<endl;
	}else{
		cerr<<"Error: The sub -root -object could be deleted. "<<endl;
		iReturn++;
	}

	//test getSubRootObjectForIdentifier()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		if ( root1.getSubRootObjectForIdentifier( vecSubRootObjects1[ auctualSubRootObject ].first ) ==
				vecSubRootObjects1[ auctualSubRootObject ].second ){
		
			cout<<"The sub -root -object with the identifier "<< 
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is correctly the object root"<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<" . "<<endl;
		}else{
			cerr<<"Error: The sub -root -object with the identifier "<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is not the object root"<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<" . "<<endl;
			iReturn++;
		}
	}

	cout<<endl<<"bSubRootObjectDeleted = root1.deleteSubRootObject( 0 , false );"<<endl;
	bSubRootObjectDeleted = root1.deleteSubRootObject( 0 , false );
	
	if ( !bSubRootObjectDeleted ){
	
		cout<<"The sub -root -object couldn't correctly be deleted. "<<endl;
	}else{
		cerr<<"Error: The sub -root -object could be deleted. "<<endl;
		iReturn++;
	}

	//test getSubRootObjectForIdentifier()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		if ( root1.getSubRootObjectForIdentifier( vecSubRootObjects1[ auctualSubRootObject ].first ) ==
				vecSubRootObjects1[ auctualSubRootObject ].second ){
		
			cout<<"The sub -root -object with the identifier "<< 
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is correctly the object root"<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<" . "<<endl;
		}else{
			cerr<<"Error: The sub -root -object with the identifier "<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is not the object root"<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<" . "<<endl;
			iReturn++;
		}
	}

	cout<<endl<<"liReturnedAllRootObjectIds = root2.getAllRootObjectIdentifiers();"<<endl;
	liReturnedAllRootObjectIds = root2.getAllRootObjectIdentifiers();
	
	if ( liReturnedAllRootObjectIds.size() == 3 + liAllDatabaseObjects.size() ){
		
		cout<<"The returned number of sub -root -object is correctly "<<
			liReturnedAllRootObjectIds.size() <<" ."<<endl;
	}else{
		cerr<<"Error: The returned number of sub -root -object is "<<
			liReturnedAllRootObjectIds.size() <<", but should be"<<
			(3 + liAllDatabaseObjects.size()) <<" ."<<endl;
		iReturn++;
	}
	
	
	cout<<"cRoot * pRoot1 = new cRoot();"<<endl;
	cRoot * pRoot1 = new cRoot();
	cout<<"root1.addSubRootObject( 101, pRoot1, 2 );"<<endl;
	bSubRootAdded = root1.addSubRootObject( 101, pRoot1, 2 );
	if ( bSubRootAdded){
	
		cout<<"The root -element was correctly added as an sub -root -objects in root1. "<<endl;
	}else{
		cerr<<"Error:The root -element wasn't added as an sub -root -objects in root1."<<endl;
		iReturn++;
	}
	
	cout<<endl<<"bSubRootObjectDeleted = root1.deleteSubRootObject( 2 , true );"<<endl;
	bSubRootObjectDeleted = root1.deleteSubRootObject( 2 , true );
	
	if ( bSubRootObjectDeleted ){
	
		cout<<"The sub -root -object could correctly be deleted. "<<endl;
	}else{
		cerr<<"Error: The sub -root -object couldn't be deleted. "<<endl;
		iReturn++;
	}

	//test getSubRootObjectForIdentifier()
	for ( unsignedIntFib auctualSubRootObject = 1;
			auctualSubRootObject <= root1.getNumberOfSubRootObjects();
			auctualSubRootObject++ ){
		
		if ( root1.getSubRootObjectForIdentifier( vecSubRootObjects1[ auctualSubRootObject ].first ) ==
				vecSubRootObjects1[ auctualSubRootObject ].second ){
		
			cout<<"The sub -root -object with the identifier "<< 
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is correctly the object root"<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<" . "<<endl;
		}else{
			cerr<<"Error: The sub -root -object with the identifier "<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<
				" of root1 is not the object root"<<
				vecSubRootObjects1[ auctualSubRootObject ].first <<" . "<<endl;
			iReturn++;
		}
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getAllDatabaseObjectIdentifiers() method"<<endl;
	
	
	cout<<"liDbIds = root1.getAllDatabaseObjectIdentifiers();"<<endl;
	list<longFib> liDbIds = root1.getAllDatabaseObjectIdentifiers();
	if ( liDbIds == liAllDatabaseObjects ){
		
		cout<<"The correct database identifiers wher given back."<<endl;
	}else{
		cerr<<"Error: The wrong database identifiers wher given back."<<endl;
		cerr<<"Root object database identifiers liDbIds: ";
		for ( list< longFib >::const_iterator itrIdentifier = liDbIds.begin();
				itrIdentifier != liDbIds.end(); itrIdentifier++ ){
			
			cerr<<(*itrIdentifier)<<"; ";
		}
		cerr<<endl;
		cerr<<"Correct database identifiers: ";
		for ( list< longFib >::const_iterator itrIdentifier = liAllDatabaseObjects.begin();
				itrIdentifier != liAllDatabaseObjects.end(); itrIdentifier++ ){
			
			cerr<<(*itrIdentifier)<<"; ";
		}
		cerr<<endl;
		iReturn++;
	}
	cout<<"liDbIds = root3_2_1.getAllDatabaseObjectIdentifiers();"<<endl;
	liDbIds = root3_2_1.getAllDatabaseObjectIdentifiers();
	if ( liDbIds == liAllDatabaseObjects ){
		
		cout<<"The correct database identifiers wher given back."<<endl;
	}else{
		cerr<<"Error: The wrong database identifiers wher given back."<<endl;
		cerr<<"Root object database identifiers liDbIds: ";
		for ( list< longFib >::const_iterator itrIdentifier = liDbIds.begin();
				itrIdentifier != liDbIds.end(); itrIdentifier++ ){
			
			cerr<<(*itrIdentifier)<<"; ";
		}
		cerr<<endl;
		cerr<<"Correct database identifiers: ";
		for ( list< longFib >::const_iterator itrIdentifier = liAllDatabaseObjects.begin();
				itrIdentifier != liAllDatabaseObjects.end(); itrIdentifier++ ){
			
			cerr<<(*itrIdentifier)<<"; ";
		}
		cerr<<endl;
		iReturn++;
	}

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
 * 	- bool cRoot::equal( const cFibElement & fibObject ) const
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testEqual( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing equal methods for root -elements"<<endl;

	cout<<endl<<"Creating root objects to compare: "<<endl<<endl;
	
	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;

	cout<<"cRoot rootEmpty2;"<<endl;
	cRoot rootEmpty2;

	//roots with superior elements
	cout<<"cRoot rootSupSuperior1;"<<endl;
	cRoot rootSupSuperior1;
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootSuperior1( NULL, &rootSupSuperior1 );"<<endl;
	cRoot rootSuperior1( NULL, &rootSupSuperior1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootSuperior1( &rootSupSuperior1 );"<<endl;
	cRoot rootSuperior1( &rootSupSuperior1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//roots with next and/or previous elements
	cout<<"cRoot rootPrevElem1;"<<endl;
	cRoot rootPrevElem1;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootPrev1( NULL, &rootPrevElem1 );"<<endl;
	cRoot rootPrev1( NULL, &rootPrevElem1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootPrev1( NULL, rootPrevElem1 );"<<endl;
	cRoot rootPrev1( NULL, &rootPrevElem1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"cPoint pointNextElem1;"<<endl;
	cPoint pointNextElem1;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootNext1( &pointNextElem1 );"<<endl;
	cRoot rootNext1( &pointNextElem1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootNext1( NULL,NULL, &pointNextElem1 );"<<endl;
	cRoot rootNext1( NULL, NULL, &pointNextElem1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"cRoot rootPrevElem2;"<<endl;
	cRoot rootPrevElem2;
	cout<<"cPoint pointNextElem2;"<<endl;
	cPoint pointNextElem2;
	cout<<"cRoot rootNextElemSup2( NULL, &rootPrevElem2 );"<<endl;
	cRoot rootNextElemSup2( NULL, &rootPrevElem2 );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootNextPrev1( &pointNextElem2, &rootNextElemSup2 );"<<endl;
	cRoot rootNextPrev1( &pointNextElem2, &rootNextElemSup2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootNextPrev1( NULL, &rootPrevElem2, &pointNextElem2 );"<<endl;
	cRoot rootNextPrev1( NULL, &rootPrevElem2, &pointNextElem2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//roots with multimediainfo
	cout<<"cRoot rootMultimediainfo1;"<<endl;
	cRoot rootMultimediainfo1;
	cout<<"rootMultimediainfo1.getMultimediaInfo()->setFibVersion( 17 );"<<endl;
	rootMultimediainfo1.getMultimediaInfo()->setFibVersion( 17 );
	
	cout<<"cRoot rootMultimediainfo2;"<<endl;
	cRoot rootMultimediainfo2;
	cout<<"rootMultimediainfo2.getMultimediaInfo()->setDatabaseVersion( 17 );"<<endl;
	rootMultimediainfo2.getMultimediaInfo()->setDatabaseVersion( 17 );
	
	//roots with optionalparts
	cout<<"cRoot rootOptionalpart1;"<<endl;
	cRoot rootOptionalpart1;
	cout<<"rootOptionalpart1.getOptionalPart()->addEntry( \"key\", \"value\" );"<<endl;
	rootOptionalpart1.getOptionalPart()->addEntry( "key", "value" );

	cout<<"cRoot rootOptionalpart2;"<<endl;
	cRoot rootOptionalpart2;
	cout<<"rootOptionalpart2.getOptionalPart()->addEntry( \"\", \"\" );"<<endl;
	rootOptionalpart2.getOptionalPart()->addEntry( "", "" );

	//roots with checksum
	cout<<"cRoot rootChecksum1;"<<endl;
	cRoot rootChecksum1;
	cout<<"cVectorChecksum checksum1;"<<endl;
	cVectorChecksum checksum1;
	cout<<"checksum1.setValue( 1, 1 );"<<endl;
	checksum1.setValue( 1, 1 );
	cout<<"rootChecksum1.setChecksum( &checksum1 );"<<endl;
	rootChecksum1.setChecksum( &checksum1 );


	cout<<"cRoot rootChecksum2;"<<endl;
	cRoot rootChecksum2;
	cout<<"cVectorChecksum checksum2;"<<endl;
	cVectorChecksum checksum2;
	cout<<"checksum2.setValue( 2, 2 );"<<endl;
	checksum2.setValue( 2, 2 );
	cout<<"rootChecksum2.setChecksum( &checksum2 );"<<endl;
	rootChecksum2.setChecksum( &checksum2 );

	//roots with domains
	cout<<"cRoot rootDomains1;"<<endl;
	cRoot rootDomains1;
	cout<<"cTypeVariable typeVariable1;"<<endl;
	cTypeVariable typeVariable1;
	cout<<"cDomainNaturalNumberBit domainNaturalNumber1( 1 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumber1( 1 );
	cout<<"rootDomains1.getDomains()->addDomain( typeVariable1, domainNaturalNumber1 );"<<endl;
	rootDomains1.getDomains()->addDomain( typeVariable1, domainNaturalNumber1 );


	cout<<"cRoot rootDomains2;"<<endl;
	cRoot rootDomains2;
	cout<<"cTypeInVar typeInVar1( 1 );"<<endl;
	cTypeInVar typeInVar1( 1 );
	cout<<"rootDomains2.getDomains()->addDomain( typeInVar1, domainNaturalNumber1 );"<<endl;
	rootDomains2.getDomains()->addDomain( typeInVar1, domainNaturalNumber1 );
	
	//roots with valuedomains
	cout<<"cRoot rootValueDomains1;"<<endl;
	cRoot rootValueDomains1;
	cout<<"rootValueDomains1.getValueDomains()->addDomain( typeVariable1, domainNaturalNumber1 );"<<endl;
	rootValueDomains1.getValueDomains()->addDomain( typeVariable1, domainNaturalNumber1 );


	cout<<"cRoot rootValueDomains2;"<<endl;
	cRoot rootValueDomains2;
	cout<<"rootValueDomains2.getValueDomains()->addDomain( typeInVar1, domainNaturalNumber1 );"<<endl;
	rootValueDomains2.getValueDomains()->addDomain( typeInVar1, domainNaturalNumber1 );

	//roots with domains and valuedomains
	cout<<"cRoot rootDDomains1;"<<endl;
	cRoot rootDDomains1;
	cout<<"rootDDomains1.getDomains()->addDomain( typeVariable1, domainNaturalNumber1 );"<<endl;
	rootDDomains1.getDomains()->addDomain( typeVariable1, domainNaturalNumber1 );
	cout<<"rootDDomains1.getValueDomains()->addDomain( typeVariable1, domainNaturalNumber1 );"<<endl;
	rootDDomains1.getValueDomains()->addDomain( typeVariable1, domainNaturalNumber1 );

	cout<<"cRoot rootDDomains2;"<<endl;
	cRoot rootDDomains2;
	cout<<"rootDDomains2.getDomains()->addDomain( typeVariable1, domainNaturalNumber1 );"<<endl;
	rootDDomains2.getDomains()->addDomain( typeVariable1, domainNaturalNumber1 );
	cout<<"rootDDomains2.getValueDomains()->addDomain( typeInVar1, domainNaturalNumber1 );"<<endl;
	rootDDomains2.getValueDomains()->addDomain( typeInVar1, domainNaturalNumber1 );


	//roots with inputvariables
	cout<<"cRoot rootInputVar1;"<<endl;
	cRoot rootInputVar1;
	cout<<"rootInputVar1.setNumberOfInputVariables( 1 );"<<endl;
	rootInputVar1.setNumberOfInputVariables( 1 );

	cout<<"cRoot rootInputVar2;"<<endl;
	cRoot rootInputVar2;
	cout<<"rootInputVar2.setNumberOfInputVariables( 2 );"<<endl;
	rootInputVar2.setNumberOfInputVariables( 2 );

	//roots with inputvariables and changed standardvalues
	cout<<"cRoot rootInputVarV1;"<<endl;
	cRoot rootInputVarV1;
	cout<<"rootInputVarV1.setNumberOfInputVariables( 1 );"<<endl;
	rootInputVarV1.setNumberOfInputVariables( 1 );
	cout<<"rootInputVarV1.setStandardValueOfInputVariable( 1, 1.0 );"<<endl;
	rootInputVarV1.setStandardValueOfInputVariable( 1, 1.0 );

	cout<<"cRoot rootInputVarV2;"<<endl;
	cRoot rootInputVarV2;
	cout<<"rootInputVarV2.setNumberOfInputVariables( 2 );"<<endl;
	rootInputVarV2.setNumberOfInputVariables( 2 );
	cout<<"rootInputVarV2.setStandardValueOfInputVariable( 2, 2.0 );"<<endl;
	rootInputVarV2.setStandardValueOfInputVariable( 2, 2.0 );

	//roots with extern objects
	cout<<"cRoot rootExtObj1;"<<endl;
	cRoot rootExtObj1;
	
	//set domain for 1'th external subobject
	cout<<"cTypeExtSubobject typeExtSubobject1( 1 );"<<endl;
	cTypeExtSubobject typeExtSubobject1( 1 );
	
	cout<<"vector<cDomain*> vecDomainE0( 0 );"<<endl;
	vector<cDomain*> vecDomainE0( 0 );
	cout<<"cDomainVector domVectorE0( vecDomainE0 );"<<endl;
	cDomainVector domVectorE0( vecDomainE0 );
	
	cout<<"rootExtObj1.getDomains()->addDomain( typeExtSubobject1, domVectorE0 );"<<endl;
	rootExtObj1.getDomains()->addDomain( typeExtSubobject1, domVectorE0 );
	

	cout<<"cRoot rootExtObj2;"<<endl;
	cRoot rootExtObj2;
	//set domain for 2'th external subobject
	cout<<"cTypeExtSubobject typeExtSubobject2( 2 );"<<endl;
	cTypeExtSubobject typeExtSubobject2( 2 );
	
	cout<<"rootExtObj2.getDomains()->addDomain( typeExtSubobject2, domVectorE0 );"<<endl;
	rootExtObj2.getDomains()->addDomain( typeExtSubobject2, domVectorE0 );
	

	//roots with extern objects with output values
	cout<<"cRoot rootExtObj1V1g1;"<<endl;
	cRoot rootExtObj1V1g1;
	//set domain for 1'th external subobject
	cout<<"vector<cDomain*> vecDomainE1( 1 );"<<endl;
	vector<cDomain*> vecDomainE1( 1 );
	vecDomainE1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	
	cout<<"cDomainVector domVectorE1( vecDomainE1 );"<<endl;
	cDomainVector domVectorE1( vecDomainE1 );
	
	delete vecDomainE1[ 0 ];
	
	cout<<"rootExtObj1V1g1.getDomains()->addDomain( typeExtSubobject1, domVectorE1 );"<<endl;
	rootExtObj1V1g1.getDomains()->addDomain( typeExtSubobject1, domVectorE1 );
	

	cout<<"cRoot rootExtObj1V1g2;"<<endl;
	cRoot rootExtObj1V1g2;
	//set domain for 1'th external subobject
	cout<<"vector<cDomain*> vecDomainE2( 2 );"<<endl;
	vector<cDomain*> vecDomainE2( 2 );
	vecDomainE2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	vecDomainE2[ 1 ] = new cDomainNaturalNumberBit( 1 );
	
	cout<<"cDomainVector domVectorE2( vecDomainE2 );"<<endl;
	cDomainVector domVectorE2( vecDomainE2 );
	
	delete vecDomainE2[ 0 ];
	delete vecDomainE2[ 1 ];
	
	cout<<"rootExtObj1V1g2.getDomains()->addDomain( typeExtSubobject1, domVectorE2 );"<<endl;
	rootExtObj1V1g2.getDomains()->addDomain( typeExtSubobject1, domVectorE2 );
	

	cout<<"cRoot rootExtObj2V2g2;"<<endl;
	cRoot rootExtObj2V2g2;
	//set domain for 2'th external subobject
	cout<<"rootExtObj2V2g2.getDomains()->addDomain( typeExtSubobject2, domVectorE2 );"<<endl;
	rootExtObj2V2g2.getDomains()->addDomain( typeExtSubobject2, domVectorE2 );
	

	cout<<"cRoot rootExtObj2V1g1;"<<endl;
	cRoot rootExtObj2V1g1;
	//set domain for 2'th external subobject
	cout<<"rootExtObj2V1g1.getDomains()->addDomain( typeExtSubobject2, domVectorE0 );"<<endl;
	rootExtObj2V1g1.getDomains()->addDomain( typeExtSubobject2, domVectorE0 );
	
	cout<<"rootExtObj2V1g1.getDomains()->addDomain( typeExtSubobject1, domVectorE1 );"<<endl;
	rootExtObj2V1g1.getDomains()->addDomain( typeExtSubobject1, domVectorE1 );
	

	//roots with sub -root -objects
	cout<<"cRoot rootSubRoot1;"<<endl;
	cRoot rootSubRoot1;
	cout<<"cRoot rootSubRoot1_1;"<<endl;
	cRoot rootSubRoot1_1;
	cout<<"rootSubRoot1.addSubRootObject( 1, &rootSubRoot1_1 );"<<endl;
	rootSubRoot1.addSubRootObject( 1, &rootSubRoot1_1 );

	cout<<"cRoot rootSubRoot2;"<<endl;
	cRoot rootSubRoot2;
	cout<<"cRoot rootSubRoot2_1;"<<endl;
	cRoot rootSubRoot2_1;
	cout<<"rootSubRoot2.addSubRootObject( 2, &rootSubRoot2_1 );"<<endl;
	rootSubRoot2.addSubRootObject( 2, &rootSubRoot2_1 );

	cout<<"cRoot rootSubRoot3;"<<endl;
	cRoot rootSubRoot3;
	cout<<"cRoot rootSubRoot3_1;"<<endl;
	cRoot rootSubRoot3_1;
	
	//set domain for 1'th external subobject
	cout<<"rootSubRoot3_1.getDomains()->addDomain( typeExtSubobject1, domVectorE0 );"<<endl;
	rootSubRoot3_1.getDomains()->addDomain( typeExtSubobject1, domVectorE0 );
	
	cout<<"rootSubRoot3.addSubRootObject( 1, &rootSubRoot3_1 );"<<endl;
	rootSubRoot3.addSubRootObject( 1, &rootSubRoot3_1 );


	cout<<"cRoot rootSubRoot4;"<<endl;
	cRoot rootSubRoot4;
	cout<<"cRoot rootSubRoot4_1;"<<endl;
	cRoot rootSubRoot4_1;
	cout<<"cRoot rootSubRoot4_2;"<<endl;
	cRoot rootSubRoot4_2;
	cout<<"rootSubRoot4.addSubRootObject( 1, &rootSubRoot4_1 );"<<endl;
	rootSubRoot4.addSubRootObject( 1, &rootSubRoot4_1 );
	cout<<"rootSubRoot4.addSubRootObject( 2, &rootSubRoot4_2 );"<<endl;
	rootSubRoot4.addSubRootObject( 2, &rootSubRoot4_2 );

	cout<<"cRoot rootSubRoot5;"<<endl;
	cRoot rootSubRoot5;
	cout<<"cRoot rootSubRoot5_1;"<<endl;
	cRoot rootSubRoot5_1;
	cout<<"cRoot rootSubRoot5_2;"<<endl;
	cRoot rootSubRoot5_2;
	cout<<"rootSubRoot5.addSubRootObject( 2, &rootSubRoot5_2 );"<<endl;
	rootSubRoot5.addSubRootObject( 2, &rootSubRoot5_2 );
	cout<<"rootSubRoot5.addSubRootObject( 1, &rootSubRoot5_1 );"<<endl;
	rootSubRoot5.addSubRootObject( 1, &rootSubRoot5_1 );

	
	//roots with sub -sub -root -objects
	cout<<"cRoot rootSubSubRoot1;"<<endl;
	cRoot rootSubSubRoot1;
	cout<<"cRoot rootSubSubRoot1_1;"<<endl;
	cRoot rootSubSubRoot1_1;
	cout<<"cRoot rootSubSubRoot1_1_1;"<<endl;
	cRoot rootSubSubRoot1_1_1;
	cout<<"cRoot rootSubSubRoot1_2;"<<endl;
	cRoot rootSubSubRoot1_2;
	cout<<"cRoot rootSubSubRoot1_2_1;"<<endl;
	cRoot rootSubSubRoot1_2_1;
	cout<<"rootSubSubRoot1.addSubRootObject( 1, &rootSubSubRoot1_1 );"<<endl;
	rootSubSubRoot1.addSubRootObject( 1, &rootSubSubRoot1_1 );
	cout<<"rootSubSubRoot1.addSubRootObject( 2, &rootSubSubRoot1_2 );"<<endl;
	rootSubSubRoot1.addSubRootObject( 2, &rootSubSubRoot1_2 );
	cout<<"rootSubSubRoot1_1.addSubRootObject( 1, &rootSubSubRoot1_1_1 );"<<endl;
	rootSubSubRoot1_1.addSubRootObject( 1, &rootSubSubRoot1_1_1 );
	cout<<"rootSubSubRoot1_2.addSubRootObject( 2, &rootSubSubRoot1_2_1 );"<<endl;
	rootSubSubRoot1_2.addSubRootObject( 2, &rootSubSubRoot1_2_1 );

	cout<<"cRoot rootSubSubRoot2;"<<endl;
	cRoot rootSubSubRoot2;
	cout<<"cRoot rootSubSubRoot2_1;"<<endl;
	cRoot rootSubSubRoot2_1;
	cout<<"cRoot rootSubSubRoot2_1_1;"<<endl;
	cRoot rootSubSubRoot2_1_1;
	cout<<"cRoot rootSubSubRoot2_2;"<<endl;
	cRoot rootSubSubRoot2_2;
	cout<<"cRoot rootSubSubRoot2_2_1;"<<endl;
	cRoot rootSubSubRoot2_2_1;
	cout<<"rootSubSubRoot2.addSubRootObject( 1, &rootSubSubRoot2_1 );"<<endl;
	rootSubSubRoot2.addSubRootObject( 1, &rootSubSubRoot2_1 );
	cout<<"rootSubSubRoot2.addSubRootObject( 2, &rootSubSubRoot2_2 );"<<endl;
	rootSubSubRoot2.addSubRootObject( 2, &rootSubSubRoot2_2 );
	cout<<"rootSubSubRoot2_1.addSubRootObject( 1, &rootSubSubRoot2_1_1 );"<<endl;
	rootSubSubRoot2_1.addSubRootObject( 1, &rootSubSubRoot2_1_1 );
	cout<<"rootSubSubRoot2_2.addSubRootObject( 2, &rootSubSubRoot2_2_1 );"<<endl;
	rootSubSubRoot2_2.addSubRootObject( 2, &rootSubSubRoot2_2_1 );

	cout<<"cRoot rootSubSubRoot3;"<<endl;
	cRoot rootSubSubRoot3;
	cout<<"cRoot rootSubSubRoot3_1;"<<endl;
	cRoot rootSubSubRoot3_1;
	cout<<"cRoot rootSubSubRoot3_1_1;"<<endl;
	cRoot rootSubSubRoot3_1_1;
	cout<<"cRoot rootSubSubRoot3_2;"<<endl;
	cRoot rootSubSubRoot3_2;
	cout<<"cRoot rootSubSubRoot3_2_1;"<<endl;
	cRoot rootSubSubRoot3_2_1;
	cout<<"rootSubSubRoot3.addSubRootObject( 1, &rootSubSubRoot3_1 );"<<endl;
	rootSubSubRoot3.addSubRootObject( 1, &rootSubSubRoot3_1 );
	cout<<"rootSubSubRoot3.addSubRootObject( 2, &rootSubSubRoot3_2 );"<<endl;
	rootSubSubRoot3.addSubRootObject( 2, &rootSubSubRoot3_2 );
	cout<<"rootSubSubRoot3_1.addSubRootObject( 1, &rootSubSubRoot3_1_1 );"<<endl;
	rootSubSubRoot3_1.addSubRootObject( 1, &rootSubSubRoot3_1_1 );
	cout<<"rootSubSubRoot3_2.addSubRootObject( 1, &rootSubSubRoot3_2_1 );"<<endl;
	rootSubSubRoot3_2.addSubRootObject( 1, &rootSubSubRoot3_2_1 );

	cout<<"cRoot rootSubSubRoot4;"<<endl;
	cRoot rootSubSubRoot4;
	cout<<"cRoot rootSubSubRoot4_1;"<<endl;
	cRoot rootSubSubRoot4_1;
	cout<<"cRoot rootSubSubRoot4_1_1;"<<endl;
	cRoot rootSubSubRoot4_1_1;
	cout<<"cRoot rootSubSubRoot4_2;"<<endl;
	cRoot rootSubSubRoot4_2;
	cout<<"rootSubSubRoot4.addSubRootObject( 1, &rootSubSubRoot4_1 );"<<endl;
	rootSubSubRoot4.addSubRootObject( 1, &rootSubSubRoot4_1 );
	cout<<"rootSubSubRoot4.addSubRootObject( 2, &rootSubSubRoot4_2 );"<<endl;
	rootSubSubRoot4.addSubRootObject( 2, &rootSubSubRoot4_2 );
	cout<<"rootSubSubRoot4_1.addSubRootObject( 1, &rootSubSubRoot4_1_1 );"<<endl;
	rootSubSubRoot4_1.addSubRootObject( 1, &rootSubSubRoot4_1_1 );



	cout<<endl<<"Beginning comparisson: "<<endl<<endl;


	//compare with rootEmpty1
	cFibElement *actualObject = & rootEmpty1;
	string szActualObjectName = "rootEmpty1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	
	//compare with rootEmpty2
	actualObject = & rootEmpty2;
	szActualObjectName = "rootEmpty2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootSuperior1
	actualObject = & rootSuperior1;
	szActualObjectName = "rootSuperior1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootPrev1
	actualObject = & rootPrev1;
	szActualObjectName = "rootPrev1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootNext1
	actualObject = & rootNext1;
	szActualObjectName = "rootNext1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootNextPrev1
	actualObject = & rootNextPrev1;
	szActualObjectName = "rootNextPrev1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootMultimediainfo1
	actualObject = & rootMultimediainfo1;
	szActualObjectName = "rootMultimediainfo1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootMultimediainfo2
	actualObject = & rootMultimediainfo2;
	szActualObjectName = "rootMultimediainfo2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootOptionalpart1
	actualObject = & rootOptionalpart1;
	szActualObjectName = "rootOptionalpart1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootOptionalpart2
	actualObject = & rootOptionalpart2;
	szActualObjectName = "rootOptionalpart2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootChecksum1
	actualObject = & rootChecksum1;
	szActualObjectName = "rootChecksum1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootChecksum2
	actualObject = & rootChecksum2;
	szActualObjectName = "rootChecksum2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootDomains1
	actualObject = & rootDomains1;
	szActualObjectName = "rootDomains1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootDomains2
	actualObject = & rootDomains2;
	szActualObjectName = "rootDomains2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootValueDomains1
	actualObject = & rootValueDomains1;
	szActualObjectName = "rootValueDomains1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootValueDomains2
	actualObject = & rootValueDomains2;
	szActualObjectName = "rootValueDomains2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootDDomains1
	actualObject = & rootDDomains1;
	szActualObjectName = "rootDDomains1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootDDomains2
	actualObject = & rootDDomains2;
	szActualObjectName = "rootDDomains2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootInputVar1
	actualObject = & rootInputVar1;
	szActualObjectName = "rootInputVar1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootInputVar2
	actualObject = & rootInputVar2;
	szActualObjectName = "rootInputVar2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootInputVar2
	actualObject = & rootInputVarV1;
	szActualObjectName = "rootInputVarV1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootInputVarV2
	actualObject = & rootInputVarV2;
	szActualObjectName = "rootInputVarV2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootExtObj1
	actualObject = & rootExtObj1;
	szActualObjectName = "rootExtObj1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootExtObj2
	actualObject = & rootExtObj2;
	szActualObjectName = "rootExtObj2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootExtObj1V1g1
	actualObject = & rootExtObj1V1g1;
	szActualObjectName = "rootExtObj1V1g1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootExtObj1V1g2
	actualObject = & rootExtObj1V1g2;
	szActualObjectName = "rootExtObj1V1g2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootExtObj2V2g2
	actualObject = & rootExtObj2V2g2;
	szActualObjectName = "rootExtObj2V2g2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootExtObj2V1g1
	actualObject = & rootExtObj2V1g1;
	szActualObjectName = "rootExtObj2V1g1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootSubRoot1
	actualObject = & rootSubRoot1;
	szActualObjectName = "rootSubRoot1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

	//compare with rootSubRoot2
	actualObject = & rootSubRoot2;
	szActualObjectName = "rootSubRoot2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );
	
	//compare with rootSubRoot3
	actualObject = & rootSubRoot3;
	szActualObjectName = "rootSubRoot3";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );
	
	//compare with rootSubRoot4
	actualObject = & rootSubRoot4;
	szActualObjectName = "rootSubRoot4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4", true );
	
	//compare with rootSubRoot5
	actualObject = & rootSubRoot5;
	szActualObjectName = "rootSubRoot5";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );
	
	//compare with rootSubSubRoot1
	actualObject = & rootSubSubRoot1;
	szActualObjectName = "rootSubSubRoot1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4", true );

	//compare with rootSubSubRoot2
	actualObject = & rootSubSubRoot2;
	szActualObjectName = "rootSubSubRoot2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4", true );

	//compare with rootSubSubRoot3
	actualObject = & rootSubSubRoot3;
	szActualObjectName = "rootSubSubRoot3";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4", true );

	//compare with rootSubSubRoot4
	actualObject = & rootSubSubRoot4;
	szActualObjectName = "rootSubSubRoot4";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty1, "rootEmpty1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootEmpty2, "rootEmpty2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSuperior1, "rootSuperior1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootPrev1, "rootPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNext1, "rootNext1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootNextPrev1, "rootNextPrev1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo1, "rootMultimediainfo1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootMultimediainfo2, "rootMultimediainfo2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart1, "rootOptionalpart1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootOptionalpart2, "rootOptionalpart2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum1, "rootChecksum1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootChecksum2, "rootChecksum2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains1, "rootDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDomains2, "rootDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains1, "rootValueDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootValueDomains2, "rootValueDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains1, "rootDDomains1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootDDomains2, "rootDDomains2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar1, "rootInputVar1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVar2, "rootInputVar2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV1, "rootInputVarV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootInputVarV2, "rootInputVarV2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1, "rootExtObj1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2, "rootExtObj2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g1, "rootExtObj1V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj1V1g2, "rootExtObj1V1g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V2g2, "rootExtObj2V2g2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootExtObj2V1g1, "rootExtObj2V1g1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot1, "rootSubRoot1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot2, "rootSubRoot2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot3, "rootSubRoot3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot4, "rootSubRoot4", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubRoot5, "rootSubRoot5" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot1, "rootSubSubRoot1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot2, "rootSubSubRoot2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot3, "rootSubSubRoot3", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, rootSubSubRoot4, "rootSubSubRoot4" );

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
 * This method tests copy element methods of the cRoot class.
 *
 * methods tested:
 * 	- cRoot( const cRoot &rootElement );
 * 	- cFibElement *copyElement( 'u', 0 ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopyElement( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying empty root -element"<<endl;

	cout<<"cRoot root1;"<<endl;
	cRoot root1;
	
	//test copyconstructor
	cout<<"cRoot root1Copy( root1 );"<<endl;
	cRoot root1Copy( root1 );

	iReturn += testCompareTwoEqualObjects( root1, "root1", root1Copy, "root1Copy" );

	//test copyElement( 'u', 0 )
	cout<<"cFibElement * pRoot1Copy = root1.copyElement();"<<endl;
	cFibElement * pRoot1Copy = root1.copyElement();

	iReturn += testCompareTwoEqualObjects( root1, "root1", *pRoot1Copy, "pRoot1Copy" );
	delete pRoot1Copy;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying root -element with previous, next and superior elements"<<endl;
	
	cout<<"cRoot rootPrevElem1;"<<endl;
	cRoot rootPrevElem1;
	cout<<"cRoot pointNextElem1;"<<endl;
	cRoot pointNextElem1;
	cout<<"cRoot rootSupSuperior1( NULL, &rootPrevElem1 );"<<endl;
	cRoot rootSupSuperior1( NULL, &rootPrevElem1 );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootNextPrev1( &pointNextElem1, &rootSupSuperior1 );"<<endl;
	cRoot rootNextPrev1( &pointNextElem1, &rootSupSuperior1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootNextPrev1( &rootSupSuperior1, &rootPrevElem1, &pointNextElem1 );"<<endl;
	cRoot rootNextPrev1( &rootSupSuperior1, &rootPrevElem1, &pointNextElem1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//test copyconstructor
	cout<<"cRoot rootNextPrev1Copy( rootNextPrev1 );"<<endl;
	cRoot rootNextPrev1Copy( rootNextPrev1 );

	if ( rootNextPrev1Copy.equalElement( rootNextPrev1 ) ){

		cout<<"The rootNextPrev1Copy fib -element is equal to rootNextPrev1. "<<endl;
	}else{
		cerr<<"Error: The rootNextPrev1Copy fib -element is not equal to rootNextPrev1."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( rootNextPrev1Copy );

	//test copyElement( 'u', 0 )
	cout<<"cFibElement * pRootNextPrev1Copy = rootNextPrev1.copyElement();"<<endl;
	cFibElement * pRootNextPrev1Copy = rootNextPrev1.copyElement();

	if ( pRootNextPrev1Copy->equalElement( rootNextPrev1 ) ){

		cout<<"The pRootNextPrev1Copy fib -element is equal to rootNextPrev1. "<<endl;
	}else{
		cerr<<"Error: The pRootNextPrev1Copy fib -element is not equal to rootNextPrev1."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pRootNextPrev1Copy );
	delete pRootNextPrev1Copy;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying root -element with multimediainfo"<<endl;
	
	cout<<"cRoot rootMultimediainfo1;"<<endl;
	cRoot rootMultimediainfo1;
	cout<<"rootMultimediainfo1.getMultimediaInfo()->setFibVersion( 17 );"<<endl;
	rootMultimediainfo1.getMultimediaInfo()->setFibVersion( 17 );
	cout<<"rootMultimediainfo1.getMultimediaInfo()->setDatabaseVersion( 17 );"<<endl;
	rootMultimediainfo1.getMultimediaInfo()->setDatabaseVersion( 17 );

	//test copyconstructor
	cout<<"cRoot rootMultimediainfo1Copy( rootMultimediainfo1 );"<<endl;
	cRoot rootMultimediainfo1Copy( rootMultimediainfo1 );

	iReturn += testCompareTwoEqualObjects( rootMultimediainfo1, "rootMultimediainfo1", rootMultimediainfo1Copy, "rootMultimediainfo1Copy" );

	//test copyElement( 'u', 0 )
	cout<<"cFibElement * pRootMultimediainfo1Copy = rootMultimediainfo1.copyElement();"<<endl;
	cFibElement * pRootMultimediainfo1Copy = rootMultimediainfo1.copyElement();

	iReturn += testCompareTwoEqualObjects( rootMultimediainfo1, "rootMultimediainfo1", *pRootMultimediainfo1Copy, "pRootMultimediainfo1Copy" );
	delete pRootMultimediainfo1Copy;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying root -element with optionalpart"<<endl;
	
	cout<<"cRoot rootOptionalpart1;"<<endl;
	cRoot rootOptionalpart1;
	cout<<"rootOptionalpart1.getOptionalPart()->addEntry( \"key\", \"value\" );"<<endl;
	rootOptionalpart1.getOptionalPart()->addEntry( "key", "value" );
	cout<<"rootOptionalpart1.getOptionalPart()->addEntry( \"\", \"\" );"<<endl;
	rootOptionalpart1.getOptionalPart()->addEntry( "", "" );

	//test copyconstructor
	cout<<"cRoot rootOptionalpart1Copy( rootOptionalpart1 );"<<endl;
	cRoot rootOptionalpart1Copy( rootOptionalpart1 );

	iReturn += testCompareTwoEqualObjects( rootOptionalpart1, "rootOptionalpart1", rootOptionalpart1Copy, "rootOptionalpart1Copy" );

	//test copyElement( 'u', 0 )
	cout<<"cFibElement * pRootOptionalpart1Copy = rootOptionalpart1.copyElement();"<<endl;
	cFibElement * pRootOptionalpart1Copy = rootOptionalpart1.copyElement();

	iReturn += testCompareTwoEqualObjects( rootOptionalpart1, "rootOptionalpart1", *pRootOptionalpart1Copy, "pRootOptionalpart1Copy" );
	delete pRootOptionalpart1Copy;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying root -element with checksum"<<endl;
	
	cout<<"cRoot rootChecksum1;"<<endl;
	cRoot rootChecksum1;
	cout<<"cVectorChecksum checksum1;"<<endl;
	cVectorChecksum checksum1;
	cout<<"checksum1.setValue( 1, 1 );"<<endl;
	checksum1.setValue( 1, 1 );
	cout<<"checksum1.setValue( 2, 2 );"<<endl;
	checksum1.setValue( 2, 2 );
	cout<<"rootChecksum1.setChecksum( &checksum1 );"<<endl;
	rootChecksum1.setChecksum( &checksum1 );

	//test copyconstructor
	cout<<"cRoot rootChecksum1Copy( rootChecksum1 );"<<endl;
	cRoot rootChecksum1Copy( rootChecksum1 );

	iReturn += testCompareTwoEqualObjects( rootChecksum1, "rootChecksum1", rootChecksum1Copy, "rootChecksum1Copy" );

	//test copyElement( 'u', 0 )
	cout<<"cFibElement * pRootChecksum1Copy = rootChecksum1.copyElement();"<<endl;
	cFibElement * pRootChecksum1Copy = rootChecksum1.copyElement();

	iReturn += testCompareTwoEqualObjects( rootChecksum1, "rootChecksum1", *pRootChecksum1Copy, "pRootChecksum1Copy" );
	delete pRootChecksum1Copy;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying root -element with domains and value domains"<<endl;
	
	cout<<"cTypeInVar typeInVar1( 1 );"<<endl;
	cTypeInVar typeInVar1( 1 );
	cout<<"cTypeVariable typeVariable1;"<<endl;
	cTypeVariable typeVariable1;
	cout<<"cDomainNaturalNumberBit domainNaturalNumber1( 1 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumber1( 1 );
	cout<<"cDomainNaturalNumberBit domainNaturalNumber2( 2 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumber2( 2 );

	cout<<"cRoot rootDDomains1;"<<endl;
	cRoot rootDDomains1;
	cout<<"rootDDomains1.getDomains()->addDomain( typeVariable1, domainNaturalNumber1 );"<<endl;
	rootDDomains1.getDomains()->addDomain( typeVariable1, domainNaturalNumber1 );
	cout<<"rootDDomains1.getDomains()->addDomain( typeInVar1, domainNaturalNumber2 );"<<endl;
	rootDDomains1.getDomains()->addDomain( typeInVar1, domainNaturalNumber2 );
	cout<<"rootDDomains1.getValueDomains()->addDomain( typeVariable1, domainNaturalNumber1 );"<<endl;
	rootDDomains1.getValueDomains()->addDomain( typeVariable1, domainNaturalNumber1 );

	//test copyconstructor
	cout<<"cRoot rootDDomains1Copy( rootDDomains1 );"<<endl;
	cRoot rootDDomains1Copy( rootDDomains1 );

	iReturn += testCompareTwoEqualObjects( rootDDomains1, "rootDDomains1", rootDDomains1Copy, "rootDDomains1Copy" );

	//test copyElement( 'u', 0 )
	cout<<"cFibElement * pRootDDomains1Copy = rootDDomains1.copyElement();"<<endl;
	cFibElement * pRootDDomains1Copy = rootDDomains1.copyElement();

	iReturn += testCompareTwoEqualObjects( rootDDomains1, "rootDDomains1", *pRootDDomains1Copy, "pRootDDomains1Copy" );
	delete pRootDDomains1Copy;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying root -element with input variables and extern under objects"<<endl;
	
	cout<<"cRoot rootInputVar1;"<<endl;
	cRoot rootInputVar1;
	cout<<"rootInputVar1.setNumberOfInputVariables( 2 );"<<endl;
	rootInputVar1.setNumberOfInputVariables( 2 );
	cout<<"rootInputVar1.setStandardValueOfInputVariable( 1, 1.0 );"<<endl;
	rootInputVar1.setStandardValueOfInputVariable( 1, 1.0 );
	cout<<"rootInputVar1.setStandardValueOfInputVariable( 2, 2.0 );"<<endl;
	rootInputVar1.setStandardValueOfInputVariable( 2, 2.0 );
	
	
	//set domain for 1'th external subobject
	cout<<"cTypeExtSubobject typeExtSubobject1( 1 );"<<endl;
	cTypeExtSubobject typeExtSubobject1( 1 );
	
	cout<<"vector<cDomain*> vecDomainE1( 1 );"<<endl;
	vector<cDomain*> vecDomainE1( 1 );
	vecDomainE1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	
	cout<<"cDomainVector domVectorE1( vecDomainE1 );"<<endl;
	cDomainVector domVectorE1( vecDomainE1 );
	
	delete vecDomainE1[ 0 ];
	
	cout<<"root1.getDomains()->addDomain( typeExtSubobject1, domVectorE1 );"<<endl;
	root1.getDomains()->addDomain( typeExtSubobject1, domVectorE1 );

	//set domain for 2'th external subobject
	cout<<"cTypeExtSubobject typeExtSubobject2( 2 );"<<endl;
	cTypeExtSubobject typeExtSubobject2( 2 );
	
	cout<<"vector<cDomain*> vecDomainE2( 2 );"<<endl;
	vector<cDomain*> vecDomainE2( 2 );
	vecDomainE2[ 0 ] = new cDomainNaturalNumberBit( 1 );
	vecDomainE2[ 1 ] = new cDomainNaturalNumberBit( 2 );
	
	cout<<"cDomainVector domVectorE2( vecDomainE2 );"<<endl;
	cDomainVector domVectorE2( vecDomainE2 );
	
	delete vecDomainE2[ 0 ];
	delete vecDomainE2[ 1 ];
	
	cout<<"root1.getDomains()->addDomain( typeExtSubobject2, domVectorE2 );"<<endl;
	root1.getDomains()->addDomain( typeExtSubobject2, domVectorE2 );
	
	//test copyconstructor
	cout<<"cRoot rootInputVar1Copy( rootInputVar1 );"<<endl;
	cRoot rootInputVar1Copy( rootInputVar1 );

	iReturn += testCompareTwoEqualObjects( rootInputVar1, "rootInputVar1", rootInputVar1Copy, "rootInputVar1Copy" );

	//test copyElement( 'u', 0 )
	cout<<"cFibElement * pRootInputVar1Copy = rootInputVar1.copyElement();"<<endl;
	cFibElement * pRootInputVar1Copy = rootInputVar1.copyElement();

	iReturn += testCompareTwoEqualObjects( rootInputVar1, "rootInputVar1", *pRootInputVar1Copy, "pRootInputVar1Copy" );
	delete pRootInputVar1Copy;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying root -element with sub -root -elements"<<endl;

	cout<<"cRoot rootSubSubRoot1;"<<endl;
	cRoot rootSubSubRoot1;
	cout<<"cRoot rootSubSubRoot1_1;"<<endl;
	cRoot rootSubSubRoot1_1;
	cout<<"cRoot rootSubSubRoot1_1_1;"<<endl;
	cRoot rootSubSubRoot1_1_1;
	cout<<"cRoot rootSubSubRoot1_2;"<<endl;
	cRoot rootSubSubRoot1_2;
	cout<<"cRoot rootSubSubRoot1_2_1;"<<endl;
	cRoot rootSubSubRoot1_2_1;
	cout<<"rootSubSubRoot1.addSubRootObject( 1, &rootSubSubRoot1_1 );"<<endl;
	rootSubSubRoot1.addSubRootObject( 1, &rootSubSubRoot1_1 );
	cout<<"rootSubSubRoot1.addSubRootObject( 2, &rootSubSubRoot1_2 );"<<endl;
	rootSubSubRoot1.addSubRootObject( 2, &rootSubSubRoot1_2 );
	cout<<"rootSubSubRoot1_1.addSubRootObject( 1, &rootSubSubRoot1_1_1 );"<<endl;
	rootSubSubRoot1_1.addSubRootObject( 1, &rootSubSubRoot1_1_1 );
	cout<<"rootSubSubRoot1_2.addSubRootObject( 2, &rootSubSubRoot1_2_1 );"<<endl;
	rootSubSubRoot1_2.addSubRootObject( 2, &rootSubSubRoot1_2_1 );

	//test copyconstructor
	cout<<"cRoot rootSubSubRoot1Copy( rootSubSubRoot1 );"<<endl;
	cRoot rootSubSubRoot1Copy( rootSubSubRoot1 );

	iReturn += testNotConnectedFibElement( rootSubSubRoot1Copy );

	//test copyElement( 'u', 0 )
	cout<<"cFibElement * pRootSubSubRoot1Copy = rootSubSubRoot1.copyElement();"<<endl;
	cFibElement * pRootSubSubRoot1Copy = rootSubSubRoot1.copyElement();

	iReturn += testNotConnectedFibElement( *pRootSubSubRoot1Copy );
	delete pRootSubSubRoot1Copy;


	return iReturn;
}



/**
 * This method tests replaceVariable() methods of the cRoot class.
 *
 * methods tested:
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testReplaceVariable( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the replaceVariable() method"<<endl;

	cout<<"cVectorPosition vecPosition( 3 );"<<endl;
	cVectorPosition vecPosition( 3 );
	
	cout<<"cPoint point1( &vecPosition );"<<endl;
	cPoint point1( &vecPosition );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root1( &point1 );"<<endl;
	cRoot root1( &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root1( NULL, NULL, &point1 );"<<endl;
	cRoot root1( NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	
	cout<<"root1.setNumberOfInputVariables( 10 );"<<endl;
	root1.setNumberOfInputVariables( 10 );
	
	cout<<"pVaraible1 = root1.getInputVariable( 1 );"<<endl;
	cFibVariable * pVaraible1 = root1.getInputVariable( 1 );
	cout<<"pVaraible2 = root1.getInputVariable( 2 );"<<endl;
	cFibVariable * pVaraible2 = root1.getInputVariable( 2 );
	cout<<"pVaraible3 = root1.getInputVariable( 3 );"<<endl;
	cFibVariable * pVaraible3 = root1.getInputVariable( 3 );

	cout<<endl<<"cFibVariable variable1New( NULL );"<<endl<<endl;
	cFibVariable variable1New( NULL );

	cout<<"point1.getPosition()->setVariable( 1, pVaraible1 );"<<endl;
	point1.getPosition()->setVariable( 1, pVaraible1 );
	cout<<"point1.getPosition()->setVariable( 2, pVaraible2 );"<<endl;
	point1.getPosition()->setVariable( 2, pVaraible2 );

	//check the isDefinedVariable() methode from cRoot
	cout<<"root1.isDefinedVariable( pVaraible1 ) "<<endl;
	if ( root1.isDefinedVariable( pVaraible1 ) ){
	
		cout<<"The pVaraible1 is defined in the root1 element. "<<endl;
	}else{
		cerr<<"Error: The pVaraible1 is not defined in the root1 element."<<endl;
		iReturn++;
	}
	//check the isDefinedVariable() methode from cRoot
	cout<<"root1.isDefinedVariable( pVaraible2, ED_ALL ) "<<endl;
	if ( root1.isDefinedVariable( pVaraible2, ED_ALL ) ){
	
		cout<<"The pVaraible2 is defined in the root1 element. "<<endl;
	}else{
		cerr<<"Error: The pVaraible2 is not defined in the root1 element."<<endl;
		iReturn++;
	}
	//check the isDefinedVariable() methode from cRoot
	cout<<"root1.isDefinedVariable( &variable1New ) "<<endl;
	if ( ! root1.isDefinedVariable( &variable1New ) ){
	
		cout<<"The variable1New is not defined in the root1 element. "<<endl;
	}else{
		cerr<<"Error: The variable1New is defined in the root1 element."<<endl;
		iReturn++;
	}

	//check the isUsedvariable() methode from cRoot
	cout<<"root1.isUsedVariable( pVaraible1 ) "<<endl;
	if ( ! root1.isUsedVariable( pVaraible1 ) ){
	
		cout<<"The pVaraible1 is not used in the root1 element. "<<endl;
	}else{
		cerr<<"Error: The pVaraible1 is used in the root1 element."<<endl;
		iReturn++;
	}
	//check the isUsedvariable() methode from cRoot
	cout<<"root1.isUsedVariable( pVaraible1, ED_ALL ) "<<endl;
	if ( root1.isUsedVariable( pVaraible1, ED_ALL ) ){
	
		cout<<"The pVaraible1 is used in the root1 object. "<<endl;
	}else{
		cerr<<"Error: The pVaraible1 is not used in the root1 object."<<endl;
		iReturn++;
	}

	//check the isUsedvariable() methode from cRoot
	cout<<"root1.isUsedVariable( pVaraible2 ) "<<endl;
	if ( ! root1.isUsedVariable( pVaraible2 ) ){
	
		cout<<"The pVaraible2 is not used in the root1 element. "<<endl;
	}else{
		cerr<<"Error: The pVaraible2 is used in the root1 element."<<endl;
		iReturn++;
	}
	//check the isUsedvariable() methode from cRoot
	cout<<"root1.isUsedVariable( pVaraible2, ED_BELOW_EQUAL ) "<<endl;
	if ( root1.isUsedVariable( pVaraible2, ED_BELOW_EQUAL ) ){
	
		cout<<"The pVaraible2 is used in the root1 object. "<<endl;
	}else{
		cerr<<"Error: The pVaraible2 is not used in the root1 object."<<endl;
		iReturn++;
	}

	//check the isUsedvariable() methode from cRoot
	cout<<"root1.isUsedVariable( pVaraible3, ED_ALL ) "<<endl;
	if ( ! root1.isUsedVariable( pVaraible3, ED_ALL ) ){
	
		cout<<"The pVaraible3 is not used in the root1 object. "<<endl;
	}else{
		cerr<<"Error: The pVaraible3 is used in the root1 object."<<endl;
		iReturn++;
	}

	//check the isUsedvariable() methode from cRoot
	cout<<"root1.isUsedVariable( &variable1New ) "<<endl;
	if ( ! root1.isUsedVariable( &variable1New ) ){
	
		cout<<"The variable1New is not used in the root1 element. "<<endl;
	}else{
		cerr<<"Error: The variable1New is used in the root1 element."<<endl;
		iReturn++;
	}
	//check the isUsedvariable() methode from cRoot
	cout<<"root1.isUsedVariable( &variable1New, ED_ALL ) "<<endl;
	if ( ! root1.isUsedVariable( &variable1New, ED_ALL ) ){
	
		cout<<"The variable1New is not used in the root1 object. "<<endl;
	}else{
		cerr<<"Error: The variable1New is used in the root1 object."<<endl;
		iReturn++;
	}


	cout<<endl<<"root1.replaceVariable( pVaraible1, & variable1New ); "<<endl;
	bool bVariableReplaced = root1.replaceVariable( pVaraible1, & variable1New );
	if ( bVariableReplaced ){
	
		cout<<"The pVaraible1 was correctly replaced by variable1New. "<<endl;
	}else{
		cerr<<"Error: The pVaraible1 was not replaced by variable1New."<<endl;
		iReturn++;
	}

	//check the isDefinedVariable() methode from cRoot
	cout<<"root1.isDefinedVariable( pVaraible1 ) "<<endl;
	if ( root1.isDefinedVariable( pVaraible1 ) ){
	
		cout<<"The pVaraible1 is defined in the root1 element. "<<endl;
	}else{
		cerr<<"Error: The pVaraible1 is not defined in the root1 element."<<endl;
		iReturn++;
	}
	//check the isDefinedVariable() methode from cRoot
	cout<<"root1.isDefinedVariable( pVaraible2, ED_ALL ) "<<endl;
	if ( root1.isDefinedVariable( pVaraible2, ED_ALL ) ){
	
		cout<<"The pVaraible2 is defined in the root1 element. "<<endl;
	}else{
		cerr<<"Error: The pVaraible2 is not defined in the root1 element."<<endl;
		iReturn++;
	}
	//check the isDefinedVariable() methode from cRoot
	cout<<"root1.isDefinedVariable( &variable1New ) "<<endl;
	if ( ! root1.isDefinedVariable( &variable1New ) ){
	
		cout<<"The variable1New is not defined in the root1 element. "<<endl;
	}else{
		cerr<<"Error: The variable1New is defined in the root1 element."<<endl;
		iReturn++;
	}

	//check the isUsedvariable() methode from cRoot
	cout<<"root1.isUsedVariable( pVaraible1 ) "<<endl;
	if ( ! root1.isUsedVariable( pVaraible1 ) ){
	
		cout<<"The pVaraible1 is not used in the root1 element. "<<endl;
	}else{
		cerr<<"Error: The pVaraible1 is used in the root1 element."<<endl;
		iReturn++;
	}
	//check the isUsedvariable() methode from cRoot
	cout<<"root1.isUsedVariable( pVaraible1, ED_ALL ) "<<endl;
	if ( ! root1.isUsedVariable( pVaraible1, ED_ALL ) ){
	
		cout<<"The pVaraible1 is not used in the root1 object. "<<endl;
	}else{
		cerr<<"Error: The pVaraible1 is used in the root1 object."<<endl;
		iReturn++;
	}

	//check the isUsedvariable() methode from cRoot
	cout<<"root1.isUsedVariable( pVaraible2 ) "<<endl;
	if ( ! root1.isUsedVariable( pVaraible2 ) ){
	
		cout<<"The pVaraible2 is not used in the root1 element. "<<endl;
	}else{
		cerr<<"Error: The pVaraible2 is used in the root1 element."<<endl;
		iReturn++;
	}
	//check the isUsedvariable() methode from cRoot
	cout<<"root1.isUsedVariable( pVaraible2, ED_BELOW ) "<<endl;
	if ( root1.isUsedVariable( pVaraible2, ED_BELOW ) ){
	
		cout<<"The pVaraible2 is used in the root1 object. "<<endl;
	}else{
		cerr<<"Error: The pVaraible2 is not used in the root1 object."<<endl;
		iReturn++;
	}

	//check the isUsedvariable() methode from cRoot
	cout<<"root1.isUsedVariable( &variable1New ) "<<endl;
	if ( ! root1.isUsedVariable( &variable1New ) ){
	
		cout<<"The variable1New is not used in the root1 element. "<<endl;
	}else{
		cerr<<"Error: The variable1New is used in the root1 element."<<endl;
		iReturn++;
	}
	//check the isUsedvariable() methode from cRoot
	cout<<"root1.isUsedVariable( &variable1New, ED_ALL ) "<<endl;
	if ( root1.isUsedVariable( &variable1New, ED_ALL ) ){
	
		cout<<"The variable1New is used in the root1 object. "<<endl;
	}else{
		cerr<<"Error: The variable1New is not used in the root1 object."<<endl;
		iReturn++;
	}

	return iReturn;
}




/**
 * This method tests setMainFibObject() methods of the cRoot class.
 *
 * methods tested:
 * 	- bool setMainFibObject( cFibElement * pInMainFibObject );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testMainFibObject( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the replaceVariable() method"<<endl;

	cout<<"cVectorPosition vecPosition( 3 );"<<endl;
	cVectorPosition vecPosition( 3 );
	
	cout<<"cPoint point1( &vecPosition );"<<endl;
	cPoint point1( &vecPosition );
	
	cout<<"cPoint point2( &vecPosition );"<<endl;
	cPoint point2( &vecPosition );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root1( NULL, NULL );"<<endl;
	cRoot root1( NULL, NULL );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot root1( NULL, NULL, NULL );"<<endl;
	cRoot root1( NULL, NULL, NULL );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the main fib -object for the root -element
	cout<<"root1.getNextFibElement() "<<endl;
	if ( root1.getNextFibElement() == NULL ){
	
		cout<<"Ther is correctly no main -fib -object in the root -element. "<<endl;
	}else{
		cerr<<"Error: Ther is a main -fib -object in the root -element, it but shouldn't."<<endl;
		iReturn++;
	}
	
	cout<<"root1.setMainFibObject( &point1 ) "<<endl;
	if ( root1.setMainFibObject( &point1 ) ){
	
		cout<<"The main -fib -object in the root -element is correctly set to point1. "<<endl;
	}else{
		cerr<<"Error: The main -fib -object in the root -element couldn't be set to point1"<<endl;
		iReturn++;
	}

	//check the main fib -object for the root -element
	cout<<"root1.getNextFibElement() "<<endl;
	if ( root1.getNextFibElement() == &point1 ){
	
		cout<<"The main -fib -object in the root -element is correctly point1. "<<endl;
	}else{
		cerr<<"Error: The main -fib -object in the root -element is not point1"<<endl;
		iReturn++;
	}
	//check the main fib -object for the root -element
	cout<<"root1.getNextFibElement() "<<endl;
	if ( root1.getNextFibElement() != &point2 ){
	
		cout<<"The main -fib -object in the root -element is correctly not point2. "<<endl;
	}else{
		cerr<<"Error: The main -fib -object in the root -element is point2"<<endl;
		iReturn++;
	}

	cout<<"root1.setMainFibObject( &point2 ) "<<endl;
	if ( root1.setMainFibObject( &point2 ) ){
	
		cout<<"The main -fib -object in the root -element is correctly set to point2. "<<endl;
	}else{
		cerr<<"Error: The main -fib -object in the root -element couldn't be set to point2"<<endl;
		iReturn++;
	}

	//check the main fib -object for the root -element
	cout<<"root1.getNextFibElement() "<<endl;
	if ( root1.getNextFibElement() == &point2 ){
	
		cout<<"The main -fib -object in the root -element is correctly point2. "<<endl;
	}else{
		cerr<<"Error: The main -fib -object in the root -element is not point2"<<endl;
		iReturn++;
	}
	cout<<"root1.getNextFibElement() "<<endl;
	if ( root1.getNextFibElement() != &point1 ){
	
		cout<<"The main -fib -object in the root -element is correctly not point1. "<<endl;
	}else{
		cerr<<"Error: The main -fib -object in the root -element is point1"<<endl;
		iReturn++;
	}

	//try to set NULL as the main -fib -object
	cout<<"root1.setMainFibObject( NULL ) "<<endl;
	if ( ! root1.setMainFibObject( NULL ) ){
	
		cout<<"The main -fib -object in the root -element couldn't correctly set to NULL. "<<endl;
	}else{
		cerr<<"Error: The main -fib -object in the root -element could be set to NULL"<<endl;
		iReturn++;
	}

	//check the main fib -object for the root -element
	cout<<"root1.getNextFibElement() "<<endl;
	if ( root1.getNextFibElement() == &point2 ){
	
		cout<<"The main -fib -object in the root -element is correctly point2. "<<endl;
	}else{
		cerr<<"Error: The main -fib -object in the root -element is not point2"<<endl;
		iReturn++;
	}

	//try to set a root -element as the main -fib -object
	cRoot rootEmpty;
	cout<<"cRoot rootEmpty;"<<endl;
	cout<<"root1.setMainFibObject( &rootEmpty ) "<<endl;
	if ( ! root1.setMainFibObject( &rootEmpty ) ){
	
		cout<<"The main -fib -object in the root -element couldn't correctly set to rootEmpty. "<<endl;
	}else{
		cerr<<"Error: The main -fib -object in the root -element could be set to rootEmpty"<<endl;
		iReturn++;
	}

	//check the main fib -object for the root -element
	cout<<"root1.getNextFibElement() "<<endl;
	if ( root1.getNextFibElement() == &point2 ){
	
		cout<<"The main -fib -object in the root -element is correctly point2. "<<endl;
	}else{
		cerr<<"Error: The main -fib -object in the root -element is not point2"<<endl;
		iReturn++;
	}

	
	return iReturn;
}













