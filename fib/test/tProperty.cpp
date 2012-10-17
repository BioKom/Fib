/**
 * @file tProperty
 * file name: tProperty.cpp
 * @author Betti Oesterholz
 * @date 09.12.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cProperty.
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
 * This file contains the test for the class cProperty, which
 * represents a Fib -propertyelement.
 *
 *
 * What's tested of class cProperty:
 * 	- cProperty( cVectorProperty * pInVectorPosition = NULL, cFibElement * pInUnderobject = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- bool hasUnderAllObjects( ) const;
 * 	- unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
 * 	- bool evalueObject( iEvaluePosition & evaluePosition, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties ) const;
 * 	- bool evalueObject( iEvalueFibElement & evalueFibElement, const unsignedIntFib objectPoint, list<cVectorProperty> & liVecProperties, const list<char> & liCFibElementTyps );
 * 	- bool equal( const cFibElement & fibObject ) const;
 * 	- bool equalElement( const cFibElement & fibElement ) const;
 * 	- cProperty( const cProperty &propertyElement );
 * 	- cFibElement *clone( ) const;
 * 	- cProperty *copy( const unsignedIntFib iObjectProperty=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementProperty=0 ) const;
 * 	- bool storeXml( ostream &stream ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- bool store( ostream &stream ) const;
 * 	- cVectorProperty * getProperty();
 * 	- bool isUsedVariable( const cFibVariable *variable , edDirection direction=ED_POSITION ) const;
 * 	- set<cFibVariable*> getUsedVariables( ED_POSITION );
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- bool isDefinedVariable( const cFibVariable *variable , ED_POSITION ) const;
 * 	- list<cFibVariable*> getDefinedVariables( ED_POSITION );
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
09.12.2009  Oesterholz  created
01.01.2010  Oesterholz  isUsedVariable( ED_POSITION ) and getUsedVariables( ED_POSITION ) tested
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
04.04.2011  Oesterholz  storing to binary stream
06.06.2011  Oesterholz  number atribute in XML-vector is now optional
10.11.2011  Oesterholz  new feature FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY implemented;
	Bugfix: evalueObject() don't overwrite properties
26.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cProperty.h"
#include "cPoint.h"
#include "cRoot.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cTypeVariable.h"
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


//global variable which is given back from storeEvaluedPoint() and storeEvaluedElement()
bool bEvalueReturn = false;
//global variables wher storeEvaluedPoint() and storeEvaluedElement() store ther values
const cVectorPosition * vecEvaluedPosition = NULL;
list<cVectorProperty> liEvaluedProperties;
const cFibElement * pEvaluedFibElement = NULL;
bool bEvalueMethodCalled;


int testCostructor( unsigned long &ulTestphase );
int testEvalueObject( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testCopy( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );
int testProperty( unsigned long &ulTestphase );
int testVariable( unsigned long &ulTestphase );


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cProperty methods"<<endl;
	cout<<      "==============================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testEvalueObject( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testProperty( ulTestphase );
	iReturn += testVariable( ulTestphase );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the constructor of the cProperty class.
 *
 * methods tested:
 * 	- cProperty( cVectorProperty * pInVectorPosition = NULL, cFibElement * pInUnderobject = NULL, cFibElement * pInSuperiorElement = NULL );
 * 	- cProperty( const cProperty &propertyElement );
 * 	- char getType() const;
 * 	- bool isValidFibElement() const;
 * 	- bool isMovable() const;
 * 	- unsignedIntFib getNumberOfElement()
 * 	- cVectorProperty * getProperty();
 * 	- bool hasUnderAllObjects() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cPropertyvector"<<endl;

	cout<<"cVectorProperty vecPropertyTranspa( cTypeProperty::TRANSPARENCY );"<<endl;
	cVectorProperty vecPropertyTranspa( cTypeProperty::TRANSPARENCY );

	cout<<"cProperty propertyEmpty( vecPropertyTranspa );"<<endl;
	cProperty propertyEmpty( vecPropertyTranspa );

	//check the getType() methode from cProperty
	if ( propertyEmpty.getType() == 'y' ){
	
		cout<<"The type of the property -element is correctly 'y' . "<<endl;
	}else{
		cerr<<"Error: The type of the property -element is "<<
			propertyEmpty.getType()<<" but should be 'y' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cProperty
	if ( ! propertyEmpty.isValidFibElement() ){
	
		cout<<"The property -element is correctly not a correct property -element. "<<endl;
	}else{
		cerr<<"Error: The property -element is a correct property -element, but should not be."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cProperty
	if ( propertyEmpty.isMovable() ){
	
		cout<<"The property -element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The property -element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cProperty
	if ( propertyEmpty.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the property -element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the property -element is "<<
			propertyEmpty.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cProperty
	if ( propertyEmpty.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the property -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the property -element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cProperty
	if ( propertyEmpty.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the property -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the property -element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cProperty
	if ( propertyEmpty.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the property -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the property -element is "<<
			propertyEmpty.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getProperty() methode from cProperty
	if ( *propertyEmpty.getProperty() == vecPropertyTranspa ){
	
		cout<<"The propertyvector for the property -element is correctly equal to vecPropertyTranspa. "<<endl;
	}else{
		cerr<<"Error: The propertyvector for the property -element is not equal to vecPropertyTranspa."<<endl;
		iReturn++;
	}
	//check the getProperty() methode from cProperty
	if ( propertyEmpty.getProperty() != &vecPropertyTranspa ){
	
		cout<<"The propertyvector for the property -element is correctly not the vecPropertyTranspa object. "<<endl;
	}else{
		cerr<<"Error: The propertyvector for the property -element is the vecPropertyTranspa object."<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cProperty
	if ( ! propertyEmpty.hasUnderAllObjects()){
	
		cout<<"The propertyelement has correctly missing a needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The propertyelement is not missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cProperty with a changed propertyvector"<<endl;

	cout<<"cVectorProperty vecProperty( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecProperty( cTypeProperty::COLOR_RGB );
	cout<<"vecProperty.setValue( 1, 1);"<<endl;
	vecProperty.setValue( 1, 1);
	cout<<"vecProperty.setValue( 2, 2);"<<endl;
	vecProperty.setValue( 2, 2);
	cout<<"vecProperty.setValue( 3, 3);"<<endl;
	vecProperty.setValue( 3, 3);

	cout<<"cProperty property1( vecProperty );"<<endl;
	cProperty property1( vecProperty );

	//check the getType() methode from cProperty
	if ( property1.getType() == 'y' ){
	
		cout<<"The type of the property -element is correctly 'y' . "<<endl;
	}else{
		cerr<<"Error: The type of the property -element is "<<
			property1.getType()<<" but should be 'y' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cProperty
	if ( ! property1.isValidFibElement() ){
	
		cout<<"The property -element is correctly not a correct property -element. "<<endl;
	}else{
		cerr<<"Error: The property -element is a correct property -element, but shouldn't be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cProperty
	if ( property1.isMovable() ){
	
		cout<<"The property -element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The property -element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cProperty
	if ( property1.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the property -element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the property -element is "<<
			property1.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cProperty
	if ( property1.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the property -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the property -element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cProperty
	if ( property1.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the property -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the property -element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cProperty
	if ( property1.getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -element for the property -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the property -element is "<<
			property1.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getProperty() methode from cProperty
	if ( property1.getProperty() != NULL ){
	
		if ( vecProperty == *(property1.getProperty()) ){
		
			cout<<"The property has the correct propertyvector vecProperty. "<<endl;
		}else{
			cerr<<"Error: The property has a not the correct propertyvector vecProperty. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The property has a no propertyvector (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cProperty
	if ( ! property1.hasUnderAllObjects() ){
	
		cout<<"The propertyelement has correctly not all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The propertyelement is not missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cProperty with a superior fib -element"<<endl;

	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertySup( vecProperty, NULL, &rootEmpty1 );"<<endl;
	cProperty propertySup( vecProperty, NULL, &rootEmpty1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertySup( vecProperty, &rootEmpty1 );"<<endl;
	cProperty propertySup( vecProperty, &rootEmpty1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the getType() methode from cProperty
	if ( propertySup.getType() == 'y' ){
	
		cout<<"The type of the property -element is correctly 'y' . "<<endl;
	}else{
		cerr<<"Error: The type of the property -element is "<<
			propertySup.getType()<<" but should be 'y' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cProperty
	if ( ! propertySup.isValidFibElement() ){
	
		cout<<"The property -element is correctly not a correct property -element. "<<endl;
	}else{
		cerr<<"Error: The property -element is a correct property -element, but shouldn't be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cProperty
	if ( propertySup.isMovable() ){
	
		cout<<"The property -element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The property -element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cProperty
	if ( propertySup.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the property -element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the property -element is "<<
			propertySup.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cProperty
	if ( propertySup.getNextFibElement() == NULL ){
	
		cout<<"The next/ main fib -element for the property -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the property -element is not NULL."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cProperty
	if ( propertySup.getFibElement( -1 ) == &rootEmpty1 ){
	
		cout<<"The previous fib -element for the property -element is correctly rootEmpty1. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the property -element is not rootEmpty1."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cProperty
	if ( propertySup.getSuperiorFibElement() == &rootEmpty1 ){
	
		cout<<"The superior fib -element for the property -element is correctly rootEmpty1. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the property -element is "<<
			propertySup.getSuperiorFibElement() << " and not rootEmpty1."<<endl;
		iReturn++;
	}
	//check the getProperty() methode from cProperty
	if ( *propertySup.getProperty() == vecProperty ){
	
		cout<<"The property has the correctly propertyvector equal to vecProperty. "<<endl;

	}else{
		cerr<<"Error: The property has a propertyvectorequal not equal to vecProperty. "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cProperty
	if ( ! propertySup.hasUnderAllObjects() ){
	
		cout<<"The propertyelement has correctly not all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The propertyelement is not missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cProperty with a next fib -element"<<endl;
	
	cout<<"cProperty propertyNextPrev( vecProperty, &propertyEmpty );"<<endl;
	cProperty propertyNextPrev( vecProperty, &propertyEmpty );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cProperty with a next and previous fib -element"<<endl;
	
	cout<<"cProperty propertyNextPrev( vecProperty, NULL, &property1, &propertyEmpty );"<<endl;
	cProperty propertyNextPrev( vecProperty, NULL, &property1, &propertyEmpty );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	//check the getType() methode from cProperty
	if ( propertyNextPrev.getType() == 'y' ){
	
		cout<<"The type of the property -element is correctly 'y' . "<<endl;
	}else{
		cerr<<"Error: The type of the property -element is "<<
			propertyNextPrev.getType()<<" but should be 'y' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cProperty
	if ( propertyNextPrev.isValidFibElement() ){
	
		cout<<"The property -element is correctly a correct property -element. "<<endl;
	}else{
		cerr<<"Error: The property -element is not a correct property -element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cProperty
	if ( propertyNextPrev.isMovable() ){
	
		cout<<"The property -element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The property -element is not movebel."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNumberOfElement() methode from cProperty
	if ( propertyNextPrev.getNumberOfElement() == 1 ){
	
		cout<<"The number of the fib -element for the property -element is correctly 1. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the property -element is "<<
			propertyNextPrev.getNumberOfElement() <<", but should be 1."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNumberOfElement() methode from cProperty
	if ( propertyNextPrev.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the property -element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the property -element is "<<
			propertyNextPrev.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNextFibElement() methode from cProperty
	if ( propertyNextPrev.getNextFibElement() == &propertyEmpty ){
	
		cout<<"The next/ main fib -element for the property -element is correctly propertyEmpty. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the property -element is not propertyEmpty."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cProperty
	if ( propertyNextPrev.getFibElement( -1 ) == NULL ){
	
		cout<<"The previous fib -element for the property -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the property -element is not NULL."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cProperty
	if ( propertyNextPrev.getFibElement( -1 ) == &property1 ){
	
		cout<<"The previous fib -element for the property -element is correctly property1. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the property -element is not property1."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getSuperiorFibElement() methode from cProperty
	if ( propertyNextPrev.getSuperiorFibElement() == NULL){
	
		cout<<"The superior fib -element for the property -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the property -element is "<<
			propertyNextPrev.getSuperiorFibElement() << " and not NULL."<<endl;
		iReturn++;
	}
	//check the getProperty() methode from cProperty
	if ( propertyNextPrev.getProperty() != NULL ){
	
		if ( vecProperty == *(propertyNextPrev.getProperty()) ){
		
			cout<<"The property has the correct propertyvector vecProperty. "<<endl;
		}else{
			cerr<<"Error: The property has a not the correct propertyvector vecProperty. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The property has a no propertyvector (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cProperty
	if ( ! propertyNextPrev.hasUnderAllObjects()  ){
	
		cout<<"The propertyelement has correctly not all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The propertyelement is not missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cProperty with all parameters given"<<endl;
	
	cout<<"cRoot rootD3;"<<flush<<endl;
	cRoot rootD3;
	
	cout<<"cTypeProperty testTypePropertyColorRgb( cTypeProperty::COLOR_RGB );"<<endl;
	cTypeProperty testTypePropertyColorRgb( cTypeProperty::COLOR_RGB );
	
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

	cout<<"rootD3.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainD3 );"<<endl;
	rootD3.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainD3 );

	cout<<"cPoint point1;"<<endl;
	cPoint point1;

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyFull( vecProperty, &point1, &rootD3 );"<<endl;
	cProperty propertyFull( vecProperty, &point1, &rootD3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyFull( vecProperty, &rootD3, &property1, &point1 );"<<endl;
	cProperty propertyFull( vecProperty, &rootD3, &property1, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	//check the getType() methode from cProperty
	if ( propertyFull.getType() == 'y' ){
	
		cout<<"The type of the property -element is correctly 'y' . "<<endl;
	}else{
		cerr<<"Error: The type of the property -element is "<<
			propertyFull.getType()<<" but should be 'y' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cProperty
	if ( propertyFull.isValidFibElement() ){
	
		cout<<"The property -element is correctly a correct property -element. "<<endl;
	}else{
		cerr<<"Error: The property -element is not a correct property -element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cProperty
	if ( propertyFull.isMovable() ){
	
		cout<<"The property -element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The property -element is not movebel."<<endl;
		iReturn++;
	}

	//check the getNumberOfElement() methode from cProperty
	if ( propertyFull.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the property -element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the property -element is "<<
			propertyFull.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
	//check the getNextFibElement() methode from cProperty
	if ( propertyFull.getNextFibElement() == &point1 ){
	
		cout<<"The next/ main fib -element for the property -element is correctly propertyEmpty. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the property -element is not propertyEmpty."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cProperty
	if ( propertyFull.getFibElement( -1 ) == &rootD3 ){
	
		cout<<"The previous fib -element for the property -element is correctly rootD3. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the property -element is not rootD3."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cProperty
	if ( propertyFull.getFibElement( -1 ) == &property1 ){
	
		cout<<"The previous fib -element for the property -element is correctly property1. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the property -element is not property1."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getSuperiorFibElement() methode from cProperty
	if ( propertyFull.getSuperiorFibElement() == &rootD3 ){
	
		cout<<"The superior fib -element for the property -element is correctly rootD3. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the property -element is "<<
			propertyFull.getSuperiorFibElement() << " and not rootD3."<<endl;
		iReturn++;
	}
	//check the getProperty() methode from cProperty
	if ( propertyFull.getProperty() != NULL ){
	
		if ( vecProperty == *(propertyFull.getProperty()) ){
		
			cout<<"The property has the correct propertyvector vecProperty. "<<endl;
		}else{
			cerr<<"Error: The property has a not the correct propertyvector vecProperty. "<<endl;
			cerr<<"The propertyvector has "<< propertyFull.getProperty()->getNumberOfElements() <<" elements. "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The property has a no propertyvector (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cProperty
	if ( propertyFull.hasUnderAllObjects() ){
	
		cout<<"The propertyelement has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The propertyelement is missing a underobject."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a cProperty with a 3 D domain and a 2 D Propertyvector"<<endl;
	
	cout<<"cRoot root2D3;"<<flush<<endl;
	cRoot root2D3;
	cout<<"root2D3.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainD3 );"<<endl;
	root2D3.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainD3 );
	
	cout<<"cVectorProperty vecPropertyE2( cTypeProperty::COLOR_RGB, 2, NULL );"<<endl;
	cVectorProperty vecPropertyE2( cTypeProperty::COLOR_RGB, 2, NULL );
	cout<<"vecPropertyE2.setValue( 1, 11.0 );"<<endl;
	vecPropertyE2.setValue( 1, 11.0 );
	cout<<"vecPropertyE2.setValue( 2, 2.0 );"<<endl;
	vecPropertyE2.setValue( 2, 2.0 );

	cout<<"cVectorProperty vecPropertyE3( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyE3( cTypeProperty::COLOR_RGB );
	cout<<"vecPropertyE3.setValue( 1, 1.0 );"<<endl;
	vecPropertyE3.setValue( 1, 1.0 );
	cout<<"vecPropertyE3.setValue( 2, 2.0 );"<<endl;
	vecPropertyE3.setValue( 2, 2.0 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property2( vecPropertyE2, &point1, &root2D3 );"<<endl;
	cProperty property2( vecPropertyE2, &point1, &root2D3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property2Pre( vecProperty, &root2D3, &root2D3, &propertyEmpty );"<<endl;
	cProperty property2Pre( vecProperty, &root2D3, &root2D3, &propertyEmpty );
	
	cout<<"cProperty property2( vecPropertyE2, &root2D3, &property2Pre, &point1 );"<<endl;
	cProperty property2( vecPropertyE2, &root2D3, &property2Pre, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	//check the getType() methode from cProperty
	if ( property2.getType() == 'y' ){
	
		cout<<"The type of the property -element is correctly 'y' . "<<endl;
	}else{
		cerr<<"Error: The type of the property -element is "<<
			property2.getType()<<" but should be 'y' ."<<endl;
		iReturn++;
	}

	//check the isValidFibElement() methode from cProperty
	if ( property2.isValidFibElement() ){
	
		cout<<"The property -element is correctly a correct property -element. "<<endl;
	}else{
		cerr<<"Error: The property -element is not a correct property -element, but should be ."<<endl;
		iReturn++;
	}

	//check the isMovable() methode from cProperty
	if ( property2.isMovable() ){
	
		cout<<"The property -element is correctly movebel. "<<endl;
	}else{
		cerr<<"Error: The property -element is not movebel."<<endl;
		iReturn++;
	}

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNumberOfElement() methode from cProperty
	if ( property2.getNumberOfElement() == 2 ){
	
		cout<<"The number of the fib -element for the property -element is correctly 2. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the property -element is "<<
			property2.getNumberOfElement() <<", but should be 2."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNumberOfElement() methode from cProperty
	if ( property2.getNumberOfElement() == 3 ){
	
		cout<<"The number of the fib -element for the property -element is correctly 3. "<<endl;
	}else{
		cerr<<"Error: The number of the fib -element for the property -element is "<<
			property2.getNumberOfElement() <<", but should be 3."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getNextFibElement() methode from cProperty
	if ( property2.getNextFibElement() == &point1 ){
	
		cout<<"The next/ main fib -element for the property -element is correctly propertyEmpty. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -element for the property -element is not propertyEmpty."<<endl;
		iReturn++;
	}
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cProperty
	if ( property2.getFibElement( -1 ) == &root2D3 ){
	
		cout<<"The previous fib -element for the property -element is correctly root2D3. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the property -element is not root2D3."<<endl;
		iReturn++;
	}
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getFibElement() methode from cProperty
	if ( property2.getFibElement( -1 ) == &property2Pre ){
	
		cout<<"The previous fib -element for the property -element is correctly property2Pre. "<<endl;
	}else{
		cerr<<"Error: The previous fib -element for the property -element is not property2Pre."<<endl;
		iReturn++;
	}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	//check the getSuperiorFibElement() methode from cProperty
	if ( property2.getSuperiorFibElement() == &root2D3 ){
	
		cout<<"The superior fib -element for the property -element is correctly root2D3. "<<endl;
	}else{
		cerr<<"Error: The superior fib -element for the property -element is "<<
			property2.getSuperiorFibElement() << " and not root2D3."<<endl;
		iReturn++;
	}
	//check the getProperty() methode from cProperty
	if ( property2.getProperty() != NULL ){
	
		if ( vecPropertyE3 == *(property2.getProperty()) ){
		
			cout<<"The property has the correct propertyvector vecPropertyE3. "<<endl;
		}else{
			cerr<<"Error: The property has a not the correct propertyvector vecPropertyE3. "<<endl;
			cerr<<"The propertyvector has "<< property2.getProperty()->getNumberOfElements() <<" elements. "<<endl;
			//check the elements of the positionsvektor
			for ( unsignedIntFib uiActualElement = 1;
					uiActualElement <= property2.getProperty()->getNumberOfElements();
					uiActualElement++ ){
				
				if ( ! property2.getProperty()->isVariable( uiActualElement ) ){
				
					cout<<"The "<<uiActualElement<<"'th element of the "<<
						"propertyvector is correctly not an variable. "<<endl;
				}else{
					cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
						"propertyvector is an variable. "<<endl;
					iReturn++;
				}
				if ( property2.getProperty()->getValue( uiActualElement ) ==
						vecPropertyE3.getValue( uiActualElement ) ){
				
					cout<<"The "<<uiActualElement<<"'th element of the "<<
						"propertyvector is correctly "<<
						vecPropertyE3.getValue( uiActualElement ) <<" . "<<endl;
				}else{
					cerr<<"Error: The "<<uiActualElement<<"'th element of the "<<
						"propertyvector is "<<property2.getProperty()->getValue( uiActualElement )<<
						" and not "<<
						vecPropertyE3.getValue( uiActualElement ) <<" . "<<endl;
					iReturn++;
				}
			}
			iReturn++;
		}
	}else{
		cerr<<"Error: The property has a no propertyvector (NULL is given back). "<<endl;
		iReturn++;
	}
	//check the hasUnderAllObjects() methode from cProperty
	if ( property2.hasUnderAllObjects() ){
	
		cout<<"The propertyelement has correctly all needed underobjects. "<<endl;
	}else{
		cerr<<"Error: The propertyelement is missing a underobject."<<endl;
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
 * This method tests the constructor of the cProperty class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cProperty with 3 dimensional propertyvector"<<endl;

	cout<<"cVectorProperty vecPropertyE2( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyE2( cTypeProperty::COLOR_RGB );
	cout<<"vecPropertyE2.setValue( 1, 4 );"<<endl;
	vecPropertyE2.setValue( 1, 4 );
	cout<<"vecPropertyE2.setValue( 2, 7 );"<<endl;
	vecPropertyE2.setValue( 2, 7 );
	cout<<"vecPropertyE2.setValue( 3, 3 );"<<endl;
	vecPropertyE2.setValue( 3, 3 );
	
	cout<<"cVectorPosition vecPositionE2;"<<endl;
	cVectorPosition vecPositionE2;

	cout<<"cPoint point1( &vecPositionE2 );"<<endl;
	cPoint point1( &vecPositionE2 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property1( vecPropertyE2, &point1 );"<<endl;
	cProperty property1( vecPropertyE2, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property1( vecPropertyE2, NULL, NULL, &point1 );"<<endl;
	cProperty property1( vecPropertyE2, NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	unsigned int uiTimeNeeded = 4 + 3;

	//check the getTimeNeed() methode from cProperty
	cout<<"property1.getTimeNeed()"<<endl;
	if ( property1.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property1.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cProperty
	cout<<"property1.getTimeNeed( 2 )"<<endl;
	if ( property1.getTimeNeed( 2 ) == 2 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 2 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property1.getTimeNeed( 2 ) <<", but should be "<< 2 <<" . "<<endl;
		iReturn++;
	}
	
	unsigned int uiPointsToEvalue = 1;
	
	cout<<"list<cVectorProperty> liVecProperties;"<<endl;
	list<cVectorProperty> liVecProperties;
	
	list< pair< const cVectorPosition*, list<cVectorProperty> > > liPointsToEvalue;
	liPointsToEvalue.push_back( make_pair( &vecPositionE2, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyE2 );
	cEvaluePositionList evaluePositionList;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"property1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bool bObjectEvalued = property1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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
	liFibElementsToEvalue.push_back( make_pair( & point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyE2 );
	cEvalueFibElementList evalueFibElementList;
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;

	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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
	cout<<"property1.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = property1.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cProperty with a propertylist given"<<endl;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	
	cout<<"cVectorProperty vecPropertyColorRgb1( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyColorRgb1( cTypeProperty::COLOR_RGB );
	cout<<"vecPropertyColorRgb1.setValue( 1, 5 );"<<endl;
	vecPropertyColorRgb1.setValue( 1, 5 );
	cout<<"vecPropertyColorRgb1.setValue( 2, 3 );"<<endl;
	vecPropertyColorRgb1.setValue( 2, 3 );
	
	cout<<"liVecProperties.push_back( vecPropertyColorRgb1 );"<<endl;
	liVecProperties.push_back( vecPropertyColorRgb1 );

	cout<<"cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW( cTypeProperty::COLOR_SW );
	cout<<"vecPropertyColorSW.setValue( 1, 14 );"<<endl;
	vecPropertyColorSW.setValue( 1, 14 );
	
	cout<<"liVecProperties.push_back( vecPropertyColorSW );"<<endl;
	liVecProperties.push_back( vecPropertyColorSW );

	cout<<"cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );
	cout<<"vecPropertyLayer.setValue( 1, 2 );"<<endl;
	vecPropertyLayer.setValue( 1, 2 );

	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	
	liPointsToEvalue.clear();
	liPointsToEvalue.push_back( make_pair( & vecPositionE2, list<cVectorProperty>() ) );
#ifdef FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY
	liPointsToEvalue.back().second.push_back( vecPropertyColorRgb1 );
	liPointsToEvalue.back().second.push_back( vecPropertyColorSW );
#endif //FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY	
	liPointsToEvalue.back().second.push_back( vecPropertyLayer );
	liPointsToEvalue.back().second.push_back( vecPropertyE2 );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"property1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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
	cout<<"liVecProperties.push_back( vecPropertyColorRgb1 );"<<endl;
	liVecProperties.push_back( vecPropertyColorRgb1 );
	cout<<"liVecProperties.push_back( vecPropertyColorSW );"<<endl;
	liVecProperties.push_back( vecPropertyColorSW );
	cout<<"liVecProperties.push_back( vecPropertyLayer );"<<endl;
	liVecProperties.push_back( vecPropertyLayer );
	
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( & point1, list<cVectorProperty>() ) );
#ifdef FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorRgb1 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyColorSW );
#endif //FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY
	liFibElementsToEvalue.back().second.push_back( vecPropertyLayer );
	liFibElementsToEvalue.back().second.push_back( vecPropertyE2 );
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cProperty for non existing object point 1"<<endl;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();

	liPointsToEvalue.clear();
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"property1.evalueObject( evaluePositionList, 1,  liVecProperties );"<<endl;
	bObjectEvalued = property1.evalueObject( evaluePositionList, 1,  liVecProperties );

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
	cout<<"property1.evalueObject( evalueFibElementList, 1,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 1,  liVecProperties, liCFibElementTyps );

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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cProperty when returnvalue is false"<<endl;

	evaluePositionList.lNumberOfTrueEvalueCalls = 0;
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	cout<<"property1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( ! bObjectEvalued ){
	
		cout<<"The property was correctly evalued. with result false "<<endl;
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
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( ! bObjectEvalued ){
	
		cout<<"The property was correctly evalued. with result false "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cProperty with differnt elements to evalue"<<endl;

	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( & property1, liVecProperties ) );
	
	cout<<"liCFibElementTyps.push_back( 'y' );"<<endl;
	liCFibElementTyps.push_back( 'y' );
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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
	
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( & point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyE2 );
	
	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	cout<<"liCFibElementTyps.push_back( 'r' );"<<endl;
	liCFibElementTyps.push_back( 'r' );
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( & property1, liVecProperties ) );
	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	cout<<"liCFibElementTyps.push_back( 'r' );"<<endl;
	liCFibElementTyps.push_back( 'r' );
	cout<<"liCFibElementTyps.push_back( 'y' );"<<endl;
	liCFibElementTyps.push_back( 'y' );
	cout<<"liCFibElementTyps.push_back( 'm' );"<<endl;
	liCFibElementTyps.push_back( 'm' );
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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


#ifndef FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing overwriting of properties in one limb"<<endl;


	cout<<"cVectorProperty vecPropertyLayer2( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecPropertyLayer2( cTypeProperty::LAYER );
	cout<<"vecPropertyLayer2.setValue( 1, 1 );"<<endl;
	vecPropertyLayer2.setValue( 1, 1 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property2( vecPropertyLayer2, &property1 );"<<endl;
	cProperty property2( vecPropertyLayer2, &property1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property2( vecPropertyLayer2, NULL, NULL, &property1 );"<<endl;
	cProperty property2( vecPropertyLayer2, NULL, NULL, &property1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	uiTimeNeeded = 2 + 4 + 3;

	//check the getTimeNeed() methode from cProperty
	cout<<"property2.getTimeNeed()"<<endl;
	if ( property2.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property2.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cProperty
	cout<<"property2.getTimeNeed( 5 ) "<<endl;
	if ( property2.getTimeNeed( 5 ) == 5 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 5 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property2.getTimeNeed( 5 ) <<", but should be "<< 5 <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"cVectorProperty vecPropertyColorSw2( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSw2( cTypeProperty::COLOR_SW );
	cout<<"vecPropertyColorSw2.setValue( 1, 21 );"<<endl;
	vecPropertyColorSw2.setValue( 1, 21 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property3( vecPropertyColorSw2, &property2 );"<<endl;
	cProperty property3( vecPropertyColorSw2, &property2 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property3( vecPropertyColorSw2, NULL, NULL, &property2 );"<<endl;
	cProperty property3( vecPropertyColorSw2, NULL, NULL, &property2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	uiTimeNeeded = 2 + 2 + 4 + 3;

	//check the getTimeNeed() methode from cProperty
	cout<<"property3.getTimeNeed() "<<endl;
	if ( property3.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property3.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cProperty
	cout<<"property3.getTimeNeed( 6 )"<<endl;
	if ( property3.getTimeNeed( 6 ) == 6 ){
	
		cout<<"The time needed to evalue the object is correctly "<< 6 <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property3.getTimeNeed( 6 ) <<", but should be "<< 6 <<" . "<<endl;
		iReturn++;
	}
	//check the getTimeNeed() methode from cProperty
	cout<<"property3.getTimeNeed( 30 ) "<<endl;
	if ( property3.getTimeNeed( 30 ) == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			property3.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}

	liPointsToEvalue.clear();
	liPointsToEvalue.push_back( make_pair( & vecPositionE2, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyE2 );
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"property1.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property1.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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

	cout<<"liCFibElementTyps.clear();"<<endl;
	liCFibElementTyps.clear();
	
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( & point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyE2 );
	
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property1.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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

	
	//evaule vor property2
	
	liPointsToEvalue.clear();
	liPointsToEvalue.push_back( make_pair( & vecPositionE2, list<cVectorProperty>() ) );
	liPointsToEvalue.back().second.push_back( vecPropertyLayer2 );
	liPointsToEvalue.back().second.push_back( vecPropertyE2 );
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"property2.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property2.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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
	liFibElementsToEvalue.push_back( make_pair( & point1, list<cVectorProperty>() ) );
	liFibElementsToEvalue.back().second.push_back( vecPropertyLayer2 );
	liFibElementsToEvalue.back().second.push_back( vecPropertyE2 );
	
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"property2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property2.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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

	
	//evaule vor property3
	
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	cout<<"property3.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = property3.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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
	
	cout<<"property3.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = property3.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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
#endif //not FEATURE_EVALUE_ALL_PROPERTIES_IN_C_PROPERTY


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing evaluing cProperty with a property that isn't evalued"<<endl;

	cout<<"cVectorProperty vecPropertyChecksum( cTypeProperty::CHECKSUM );"<<endl;
	cVectorProperty vecPropertyChecksum( cTypeProperty::CHECKSUM );
	cout<<"vecPropertyChecksum.setValue( 1, 1 );"<<endl;
	vecPropertyChecksum.setValue( 1, 1 );
	cout<<"vecPropertyChecksum.setValue( 2, 2 );"<<endl;
	vecPropertyChecksum.setValue( 2, 2 );
	cout<<"vecPropertyChecksum.setValue( 3, 3 );"<<endl;
	vecPropertyChecksum.setValue( 3, 3 );
	
	cout<<"cVectorPosition vecPositionE3( 3 );"<<endl;
	cVectorPosition vecPositionE3( 3 );

	cout<<"cPoint pointE3( &vecPositionE3 );"<<endl;
	cPoint pointE3( &vecPositionE3 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyChecksum( vecPropertyChecksum, &pointE3 );"<<endl;
	cProperty propertyChecksum( vecPropertyChecksum, &pointE3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyChecksum( vecPropertyChecksum, NULL, NULL, &pointE3 );"<<endl;
	cProperty propertyChecksum( vecPropertyChecksum, NULL, NULL, &pointE3 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	uiTimeNeeded = 4 + 4;

	//check the getTimeNeed() methode from cProperty
	cout<<"propertyChecksum.getTimeNeed()"<<endl;
	if ( propertyChecksum.getTimeNeed() == uiTimeNeeded ){
	
		cout<<"The time needed to evalue the object is correctly "<< uiTimeNeeded <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the object is "<<
			propertyChecksum.getTimeNeed() <<", but should be "<< uiTimeNeeded <<" . "<<endl;
		iReturn++;
	}
	
	cout<<"liVecProperties.clear();"<<endl;
	liVecProperties.clear();
	liPointsToEvalue.clear();
	
	liPointsToEvalue.push_back( make_pair( & vecPositionE3, list<cVectorProperty>() ) );
	evaluePositionList.liEvaluedPositionData.clear();
	evaluePositionList.ulCountOfEvalueMethodCalled = 0;
	evaluePositionList.lNumberOfTrueEvalueCalls = 100;
	
	cout<<"propertyChecksum.evalueObject( evaluePositionList, 0,  liVecProperties );"<<endl;
	bObjectEvalued = propertyChecksum.evalueObject( evaluePositionList, 0,  liVecProperties );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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
	
	liFibElementsToEvalue.clear();
	liFibElementsToEvalue.push_back( make_pair( & pointE3, list<cVectorProperty>() ) );
	evalueFibElementList.liEvaluedElementData.clear();
	evalueFibElementList.ulCountOfEvalueMethodCalled = 0;
	evalueFibElementList.lNumberOfTrueEvalueCalls = 100;
	cout<<"propertyChecksum.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );"<<endl;
	bObjectEvalued = propertyChecksum.evalueObject( evalueFibElementList, 0,  liVecProperties, liCFibElementTyps );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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
	cout<<"propertyChecksum.evalueObjectSimple( evalueFibElementList );"<<endl;
	bObjectEvalued = propertyChecksum.evalueObjectSimple( evalueFibElementList );

	if ( bObjectEvalued ){
	
		cout<<"The property was correctly evalued. "<<endl;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing equal methods for propertyelements"<<endl;

	cout<<endl<<"Creating propertyobjects objects to compare: "<<endl<<endl;

	//property with colorSw Propertyvector
	cout<<"cVectorProperty vecPropertyColorSW1( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW1( cTypeProperty::COLOR_SW );
	cout<<"cProperty propertyColorSw1( vecPropertyColorSW1 );"<<endl;
	cProperty propertyColorSw1( vecPropertyColorSW1 );

	cout<<"cVectorProperty vecPropertyColorSW2( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW2( cTypeProperty::COLOR_SW );
	cout<<"cProperty propertyColorSw2( vecPropertyColorSW2 );"<<endl;
	cProperty propertyColorSw2( vecPropertyColorSW2 );

	cout<<"cVectorProperty vecPropertyColorSW3Ch( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW3Ch( cTypeProperty::COLOR_SW );
	cout<<"vecPropertyColorSW3Ch.setValue( 1, 4);"<<endl;
	vecPropertyColorSW3Ch.setValue( 1, 4);
	cout<<"cProperty propertyColorSw3Ch( vecPropertyColorSW3Ch );"<<endl;
	cProperty propertyColorSw3Ch( vecPropertyColorSW3Ch );

	//property with colorRgb Propertyvector
	cout<<"cVectorProperty vecPropertyColorRgb1( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyColorRgb1( cTypeProperty::COLOR_RGB );
	cout<<"cProperty propertyColorRgb1( vecPropertyColorRgb1 );"<<endl;
	cProperty propertyColorRgb1( vecPropertyColorRgb1 );
	
	
	cout<<"cVectorProperty vecPropertyColorRgb1Ch( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyColorRgb1Ch( cTypeProperty::COLOR_RGB );
	cout<<"vecPropertyColorRgb1Ch.setValue( 1, 4);"<<endl;
	vecPropertyColorRgb1Ch.setValue( 1, 4);
	cout<<"cProperty propertyColorRgb1Ch( vecPropertyColorRgb1Ch );"<<endl;
	cProperty propertyColorRgb1Ch( vecPropertyColorRgb1Ch );

	cout<<"cVectorProperty vecPropertyColorRgb2Ch( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyColorRgb2Ch( cTypeProperty::COLOR_RGB );
	cout<<"vecPropertyColorRgb2Ch.setValue( 2, 4);"<<endl;
	vecPropertyColorRgb2Ch.setValue( 2, 4);
	cout<<"cProperty propertyColorRgb2Ch( vecPropertyColorRgb2Ch );"<<endl;
	cProperty propertyColorRgb2Ch( vecPropertyColorRgb2Ch );


	//property with a layer Propertyvector
	cout<<"cVectorProperty vecPropertyLayer1( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecPropertyLayer1( cTypeProperty::LAYER );
	cout<<"cProperty propertyLayer1( vecPropertyLayer1 );"<<endl;
	cProperty propertyLayer1( vecPropertyLayer1 );
	
	
	cout<<"cVectorProperty vecPropertyLayer2Ch( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecPropertyLayer2Ch( cTypeProperty::LAYER );
	cout<<"vecPropertyLayer2Ch.setValue( 1, 4);"<<endl;
	vecPropertyLayer2Ch.setValue( 1, 4);
	cout<<"cProperty propertyLayer2Ch( vecPropertyLayer2Ch );"<<endl;
	cProperty propertyLayer2Ch( vecPropertyLayer2Ch );

	
	//property with supperior element
	cout<<"cRoot rootEmpty1;"<<endl;
	cRoot rootEmpty1;
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertySup( vecPropertyColorSW1, NULL, &rootEmpty1 );"<<endl;
	cProperty propertySup( vecPropertyColorSW1, NULL, &rootEmpty1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertySup( vecPropertyColorSW1, &rootEmpty1 );"<<endl;
	cProperty propertySup( vecPropertyColorSW1, &rootEmpty1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//property in fib -element structur
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyNextPrev( vecPropertyColorSW1, &poinNext );"<<endl;
	cProperty propertyNextPrev( vecPropertyColorSW1, &poinNext );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinPrev;"<<endl;
	cPoint poinPrev;
	cout<<"cProperty propertyNextPrev( vecPropertyColorSW1, NULL, &poinPrev, &poinNext );"<<endl;
	cProperty propertyNextPrev( vecPropertyColorSW1, NULL, &poinPrev, &poinNext );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	cout<<"cPoint poinNext2;"<<endl;
	cPoint poinNext2;
	cout<<"cRoot root1;"<<flush<<endl;
	cRoot root1;
	
	cout<<"cTypeProperty testTypePropertyColorSw( cTypeProperty::COLOR_SW );"<<endl;
	cTypeProperty testTypePropertyColorSw( cTypeProperty::COLOR_SW );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1( 1 );
	cout<<"vecDomainsE1[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomainE1( vecDomainsE1 );"<<endl;
	cDomainVector vectorDomainE1( vecDomainsE1 );
	delete vecDomainsE1[ 0 ];

	cout<<"root1.getDomains()->addDomain( testTypePropertyColorSw, &vectorDomainE1 );"<<endl;
	root1.getDomains()->addDomain( testTypePropertyColorSw, &vectorDomainE1 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyFull( vecPropertyColorSW1, &poinNext2, &root1 );"<<endl;
	cProperty propertyFull( vecPropertyColorSW1, &poinNext2, &root1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinPrev2;"<<endl;
	cPoint poinPrev2;
	cout<<"cProperty propertyFull( vecPropertyColorSW1, &root1, &poinPrev2, &poinNext2 );"<<endl;
	cProperty propertyFull( vecPropertyColorSW1, &root1, &poinPrev2, &poinNext2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	//properties with a contained pointelement
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cProperty propertyColorSwO( vecPropertyColorSW1, &point1 );"<<endl;
	cProperty propertyColorSwO( vecPropertyColorSW1, &point1 );

	cout<<"cPoint point2;"<<endl;
	cPoint point2;
	cout<<"cProperty propertyColorRgbO( vecPropertyColorRgb1, &point2 );"<<endl;
	cProperty propertyColorRgbO( vecPropertyColorRgb1, &point2 );

	//a limb with more then one propertyelement and pointelement
	cout<<"cPoint point3;"<<endl;
	cPoint point3;
	cout<<"cProperty property1ColorSwO1( vecPropertyColorSW1, &point3 );"<<endl;
	cProperty property1ColorSwO1( vecPropertyColorSW1, &point3 );
	cout<<"cProperty property1ColorSwO2LayerO1( vecPropertyLayer1, &property1ColorSwO1 );"<<endl;
	cProperty property1ColorSwO2LayerO1( vecPropertyLayer1, &property1ColorSwO1 );

	cout<<"cPoint point4;"<<endl;
	cPoint point4;
	cout<<"cProperty property2ColorSwO1( vecPropertyColorSW1, &point4 );"<<endl;
	cProperty property2ColorSwO1( vecPropertyColorSW1, &point4 );
	cout<<"cProperty property2ColorSwO1LayerO1( vecPropertyLayer1, &property2ColorSwO1 );"<<endl;
	cProperty property2ColorSwO1LayerO1( vecPropertyLayer1, &property2ColorSwO1 );

	cout<<"cPoint point5;"<<endl;
	cPoint point5;
	cout<<"cProperty property3LayerO1( vecPropertyLayer1, &point5 );"<<endl;
	cProperty property3LayerO1( vecPropertyLayer1, &point5 );
	cout<<"cProperty property3LayerO2ColorSwO1( vecPropertyColorSW1, &property3LayerO1 );"<<endl;
	cProperty property3LayerO2ColorSwO1( vecPropertyColorSW1, &property3LayerO1 );
	
	cout<<"cPoint point6;"<<endl;
	cPoint point6;
	cout<<"cProperty property3ColorSwO1( vecPropertyColorSW3Ch, &point6 );"<<endl;
	cProperty property3ColorSwO1( vecPropertyColorSW3Ch, &point6 );
	cout<<"cProperty property3ColorSwO1LayerO1( vecPropertyLayer1, &property3ColorSwO1 );"<<endl;
	cProperty property3ColorSwO1LayerO1( vecPropertyLayer1, &property3ColorSwO1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	//properties with a contained pointelement
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cProperty propertyColorSwO( vecPropertyColorSW1, NULL, NULL, &point1 );"<<endl;
	cProperty propertyColorSwO( vecPropertyColorSW1, NULL, NULL, &point1 );

	cout<<"cPoint point2;"<<endl;
	cPoint point2;
	cout<<"cProperty propertyColorRgbO( vecPropertyColorRgb1, NULL, NULL, &point2 );"<<endl;
	cProperty propertyColorRgbO( vecPropertyColorRgb1, NULL, NULL, &point2 );

	//a limb with more then one propertyelement and pointelement
	cout<<"cPoint point3;"<<endl;
	cPoint point3;
	cout<<"cProperty property1ColorSwO1( vecPropertyColorSW1, NULL, NULL, &point3 );"<<endl;
	cProperty property1ColorSwO1( vecPropertyColorSW1, NULL, NULL, &point3 );
	cout<<"cProperty property1ColorSwO2LayerO1( vecPropertyLayer1, NULL, NULL, &property1ColorSwO1 );"<<endl;
	cProperty property1ColorSwO2LayerO1( vecPropertyLayer1, NULL, NULL, &property1ColorSwO1 );

	cout<<"cPoint point4;"<<endl;
	cPoint point4;
	cout<<"cProperty property2ColorSwO1( vecPropertyColorSW1, NULL, NULL, &point4 );"<<endl;
	cProperty property2ColorSwO1( vecPropertyColorSW1, NULL, NULL, &point4 );
	cout<<"cProperty property2ColorSwO1LayerO1( vecPropertyLayer1, NULL, NULL, &property2ColorSwO1 );"<<endl;
	cProperty property2ColorSwO1LayerO1( vecPropertyLayer1, NULL, NULL, &property2ColorSwO1 );

	cout<<"cPoint point5;"<<endl;
	cPoint point5;
	cout<<"cProperty property3LayerO1( vecPropertyLayer1, NULL, NULL, &point5 );"<<endl;
	cProperty property3LayerO1( vecPropertyLayer1, NULL, NULL, &point5 );
	cout<<"cProperty property3LayerO2ColorSwO1( vecPropertyColorSW1, NULL, NULL, &property3LayerO1 );"<<endl;
	cProperty property3LayerO2ColorSwO1( vecPropertyColorSW1, NULL, NULL, &property3LayerO1 );
	
	cout<<"cPoint point6;"<<endl;
	cPoint point6;
	cout<<"cProperty property3ColorSwO1( vecPropertyColorSW3Ch, NULL, NULL, &point6 );"<<endl;
	cProperty property3ColorSwO1( vecPropertyColorSW3Ch, NULL, NULL, &point6 );
	cout<<"cProperty property3ColorSwO1LayerO1( vecPropertyLayer1, NULL, NULL, &property3ColorSwO1 );"<<endl;
	cProperty property3ColorSwO1LayerO1( vecPropertyLayer1, NULL, NULL, &property3ColorSwO1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR




	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with propertyColorSw1
	cFibElement *actualObject = &propertyColorSw1;
	string szActualObjectName = "propertyColorSw1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1" );


	//compare with propertyColorSw2
	actualObject = & propertyColorSw2;
	szActualObjectName = "propertyColorSw2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1" );

	//compare with propertyColorSw3Ch
	actualObject = & propertyColorSw3Ch;
	szActualObjectName = "propertyColorSw3Ch";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1" );

	//compare with propertyColorRgb1
	actualObject = & propertyColorRgb1;
	szActualObjectName = "propertyColorRgb1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1" );

	//compare with propertyColorRgb1Ch
	actualObject = & propertyColorRgb1Ch;
	szActualObjectName = "propertyColorRgb1Ch";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1" );

	//compare with propertyColorRgb2Ch
	actualObject = & propertyColorRgb2Ch;
	szActualObjectName = "propertyColorRgb2Ch";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1" );

	//compare with propertyLayer1
	actualObject = & propertyLayer1;
	szActualObjectName = "propertyLayer1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1", true );

	//compare with propertyLayer2Ch
	actualObject = & propertyLayer2Ch;
	szActualObjectName = "propertyLayer2Ch";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1" );

	//compare with propertySup
	actualObject = & propertySup;
	szActualObjectName = "propertySup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1" );

	//compare with propertyNextPrev
	actualObject = & propertyNextPrev;
	szActualObjectName = "propertyNextPrev";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1" );

	//compare with propertyFull
	actualObject = & propertyFull;
	szActualObjectName = "propertyFull";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1" );

	//compare with propertyColorSwO
	actualObject = & propertyColorSwO;
	szActualObjectName = "propertyColorSwO";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup", true );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1" );

	//compare with propertyColorRgbO
	actualObject = & propertyColorRgbO;
	szActualObjectName = "propertyColorRgbO";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1" );

	//compare with property1ColorSwO2LayerO1
	actualObject = & property1ColorSwO2LayerO1;
	szActualObjectName = "property1ColorSwO2LayerO1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1", true );

	//compare with property2ColorSwO1LayerO1
	actualObject = & property2ColorSwO1LayerO1;
	szActualObjectName = "property2ColorSwO1LayerO1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1", true );

	//compare with property3LayerO2ColorSwO1
	actualObject = & property3LayerO2ColorSwO1;
	szActualObjectName = "property3LayerO2ColorSwO1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1" );

	//compare with property3LayerO2ColorSwO1
	actualObject = & property3ColorSwO1LayerO1;
	szActualObjectName = "property3ColorSwO1LayerO1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw1, "propertyColorSw1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw2, "propertyColorSw2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSw3Ch, "propertyColorSw3Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1, "propertyColorRgb1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb1Ch, "propertyColorRgb1Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgb2Ch, "propertyColorRgb2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer1, "propertyLayer1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyLayer2Ch, "propertyLayer2Ch" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertySup, "propertySup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyNextPrev, "propertyNextPrev" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyFull, "propertyFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorSwO, "propertyColorSwO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, propertyColorRgbO, "propertyColorRgbO" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property2ColorSwO1LayerO1, "property2ColorSwO1LayerO1", true );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, property3LayerO2ColorSwO1, "property3LayerO2ColorSwO1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, property3ColorSwO1LayerO1, "property3ColorSwO1LayerO1" );

	return iReturn;
}



/**
 * This method tests the equal() method of two given fib -objects which are
 * equal.
 * It also compares the superior, next and previous fib -element propertyers.
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
	
	//check the getNextFibElement() methode from cProperty
	if ( const_cast<cFibElement*>(&fibObject1)->getNextFibElement() ==
			const_cast<cFibElement*>(&fibObject2)->getNextFibElement() ){
	
		cout<<"The next/ main fib -elementpointer for the property -element are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The next/ main fib -elementpointer for the property -element are not equal."<<endl;
		iReturn++;
	}

	//check the getFibElement() methode from cProperty
	if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) ==
			const_cast<cFibElement*>(&fibObject2)->getFibElement( -1 ) ){
	
		cout<<"The previous fib -elementpointer for the property -element are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the property -element are not equal."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cProperty
	if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() ==
			const_cast<cFibElement*>(&fibObject2)->getSuperiorFibElement() ){
	
		cout<<"The superior fib -elementpointer for the property -element are correctly equal. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the property -element are not equal."<<endl;
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
 * This method tests the copy methods and copyconstructor of the cProperty class.
 *
 * methods tested:
 * 	- cProperty( const cProperty &propertyElement );
 * 	- cFibElement *clone( ) const;
 * 	- cProperty *copy( const unsignedIntFib iObjectProperty=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementProperty=0 ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a empty cProperty"<<endl;

	cout<<"cVectorProperty vecPropertyColorSW1( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW1( cTypeProperty::COLOR_SW );
	cout<<"cProperty propertyEmpty( vecPropertyColorSW1 );"<<endl;
	cProperty propertyEmpty( vecPropertyColorSW1 );

	cout<<"cProperty propertyEmptyCopyConstruct( propertyEmpty );"<<endl;
	cProperty propertyEmptyCopyConstruct( propertyEmpty );

	iReturn += testCompareTwoEqualObjectsStructur( propertyEmptyCopyConstruct, "propertyEmptyCopyConstruct", propertyEmpty, "propertyEmpty" );

	cout<<"cFibElement * pPropertyEmptyClone = propertyEmpty.clone();"<<endl;
	cFibElement * pPropertyEmptyClone = propertyEmpty.clone();

	iReturn += testCompareTwoEqualObjectsStructur( *pPropertyEmptyClone, "pPropertyEmptyClone", propertyEmpty, "propertyEmpty" );
	delete pPropertyEmptyClone;

	cout<<"cFibElement * pPropertyEmptyCopy = propertyEmpty.copy();"<<endl;
	cFibElement * pPropertyEmptyCopy = propertyEmpty.copy();

	iReturn += testCompareTwoEqualObjectsStructur( *pPropertyEmptyCopy, "pPropertyEmptyCopy", propertyEmpty, "propertyEmpty" );
	delete pPropertyEmptyCopy;

	cout<<"cFibElement * pPropertyEmptyCopyElement = propertyEmpty.copyElement();"<<endl;
	cFibElement * pPropertyEmptyCopyElement = propertyEmpty.copyElement();

	iReturn += testCompareTwoEqualObjectsStructur( *pPropertyEmptyCopyElement, "pPropertyEmptyCopyElement", propertyEmpty, "propertyEmpty" );
	delete pPropertyEmptyCopyElement;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying for a other object or elementpoint"<<endl;

	cout<<"cFibElement * pPropertyEmptyNoCopy = propertyEmpty.copy( 1 );"<<endl;
	cFibElement * pPropertyEmptyNoCopy = propertyEmpty.copy( 1 );

	if ( pPropertyEmptyNoCopy == NULL ){
	
		cout<<"The cProperty was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cProperty was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pPropertyEmptyNoCopy;
	}

	cout<<"cFibElement * pPropertyEmptyNoCopyElement = propertyEmpty.copyElement( 'y', 2 );"<<endl;
	cFibElement * pPropertyEmptyNoCopyElement = propertyEmpty.copyElement( 'y', 2 );

	if ( pPropertyEmptyNoCopyElement == NULL ){
	
		cout<<"The cProperty -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cProperty -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pPropertyEmptyNoCopyElement;
	}

	cout<<"pPropertyEmptyNoCopyElement = propertyEmpty.copyElement( 'u', 2 );"<<endl;
	pPropertyEmptyNoCopyElement = propertyEmpty.copyElement( 'u', 2 );

	if ( pPropertyEmptyNoCopyElement == NULL ){
	
		cout<<"The cProperty -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cProperty -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pPropertyEmptyNoCopyElement;
	}

	cout<<"pPropertyEmptyNoCopyElement = propertyEmpty.copyElement( 'r', 1 );"<<endl;
	pPropertyEmptyNoCopyElement = propertyEmpty.copyElement( 'r', 1 );

	if ( pPropertyEmptyNoCopyElement == NULL ){
	
		cout<<"The cProperty -element was not copied, NULL was given back. "<<endl;
	}else{
		cerr<<"Error: The cProperty -element was copied, not NULL was given back.  "<<endl;
		iReturn++;
		delete pPropertyEmptyNoCopyElement;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cProperty with all members set"<<endl;

	//property in fib -element structur
	cout<<"cPoint poinNext;"<<endl;
	cPoint poinNext;

	cout<<"cRoot rootD3;"<<flush<<endl;
	cRoot rootD3;
	
	cout<<"cTypeProperty testTypePropertyColorRgb( cTypeProperty::COLOR_RGB );"<<endl;
	cTypeProperty testTypePropertyColorRgb( cTypeProperty::COLOR_RGB );
	
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

	cout<<"rootD3.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainD3 );"<<endl;
	rootD3.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainD3 );

	cout<<"cVectorProperty vecPropertyColorRgb1( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyColorRgb1( cTypeProperty::COLOR_RGB );
	cout<<"vecPropertyColorRgb1.setValue( 1, 1 );"<<endl;
	vecPropertyColorRgb1.setValue( 1, 1 );
	cout<<"vecPropertyColorRgb1.setValue( 2, 2 );"<<endl;
	vecPropertyColorRgb1.setValue( 2, 2 );
	cout<<"vecPropertyColorRgb1.setValue( 3, 3 );"<<endl;
	vecPropertyColorRgb1.setValue( 3, 3 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property2E2( vecPropertyColorRgb1, &poinNext, &rootD3 );"<<endl;
	cProperty property2E2( vecPropertyColorRgb1, &poinNext, &rootD3 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cPoint poinPrev;"<<endl;
	cPoint poinPrev;
	cout<<"cProperty property2E2( vecPropertyColorRgb1, &rootD3, &poinPrev, &poinNext );"<<endl;
	cProperty property2E2( vecPropertyColorRgb1, &rootD3, &poinPrev, &poinNext );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"cProperty property2E2CopyConstruct( property2E2 );"<<endl;
	cProperty property2E2CopyConstruct( property2E2 );

	if ( property2E2CopyConstruct.equalElement( property2E2 ) ){

		cout<<"The property2E2CopyConstruct fib -element is equal to property2E2. "<<endl;
	}else{
		cerr<<"Error: The property2E2CopyConstruct fib -element is not equal to property2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( property2E2CopyConstruct );

	cout<<"cFibElement * pProperty2E2Copy = property2E2.copy();"<<endl;
	cFibElement * pProperty2E2Copy = property2E2.copy();
	iReturn += testCompareTwoEqualObjects( *pProperty2E2Copy, "pProperty2E2Copy", property2E2, "property2E2" );
	//check the getFibElement() methode from cProperty
	if ( NULL == pProperty2E2Copy->getFibElement( -1 ) ){
	
		cout<<"The previous fib -elementpointer for the property -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the property -element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cProperty
	if ( NULL == pProperty2E2Copy->getSuperiorFibElement() ){
	
		cout<<"The superior fib -elementpointer for the property -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the property -element is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( pProperty2E2Copy );

	cout<<"cFibElement * pProperty2E2CopyElement = property2E2.copyElement( 'u', 1 );"<<endl;
	cFibElement * pProperty2E2CopyElement = property2E2.copyElement( 'u', 1 );

	if ( pProperty2E2CopyElement->equalElement( property2E2 ) ){
	
		cout<<"The pProperty2E2CopyElement fib -element is equal to property2E2. "<<endl;
	}else{
		cerr<<"Error: The pProperty2E2CopyElement fib -element is not equal to property2E2."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pProperty2E2CopyElement );
	delete pProperty2E2CopyElement;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a limb with more then one propertyelement and pointelement"<<endl;

	//a limb with more then one propertyelement and pointelement
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );"<<endl;
	cVectorProperty vecPropertyLayer( cTypeProperty::LAYER );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property1ColorSwO1( vecPropertyColorSW1, &point1 );"<<endl;
	cProperty property1ColorSwO1( vecPropertyColorSW1, &point1 );
	cout<<"cProperty property1ColorSwO2LayerO1( vecPropertyLayer, &property1ColorSwO1 );"<<endl;
	cProperty property1ColorSwO2LayerO1( vecPropertyLayer, &property1ColorSwO1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty property1ColorSwO1( vecPropertyColorSW1, NULL, NULL, &point1 );"<<endl;
	cProperty property1ColorSwO1( vecPropertyColorSW1, NULL, NULL, &point1 );
	cout<<"cProperty property1ColorSwO2LayerO1( vecPropertyLayer, NULL, NULL, &property1ColorSwO1 );"<<endl;
	cProperty property1ColorSwO2LayerO1( vecPropertyLayer, NULL, NULL, &property1ColorSwO1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR


	cout<<endl<<"cProperty property1ColorSwO2LayerO1CopyConstruct( property1ColorSwO2LayerO1 );"<<endl;
	cProperty property1ColorSwO2LayerO1CopyConstruct( property1ColorSwO2LayerO1 );

	if ( property1ColorSwO2LayerO1CopyConstruct.equalElement( property1ColorSwO2LayerO1 ) ){
	
		cout<<"The property1ColorSwO2LayerO1CopyConstruct fib -element is equal to property1ColorSwO2LayerO1. "<<endl;
	}else{
		cerr<<"Error: The property1ColorSwO2LayerO1CopyConstruct fib -element is not equal to property1ColorSwO2LayerO1."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( property1ColorSwO2LayerO1CopyConstruct );

	cout<<"cFibElement * pProperty1ColorSwO2LayerO1CopyConstructCopy = property1ColorSwO2LayerO1CopyConstruct.copy();"<<endl;
	cFibElement * property1ColorSwO2LayerO1Copy =
		property1ColorSwO2LayerO1.copy();

	iReturn += testCompareTwoEqualObjects(
		*property1ColorSwO2LayerO1Copy, "property1ColorSwO2LayerO1Copy",
		property1ColorSwO2LayerO1, "property1ColorSwO2LayerO1" );
	//check the getFibElement() methode from cProperty
	if ( NULL == property1ColorSwO2LayerO1Copy->getFibElement( -1 ) ){
	
		cout<<"The previous fib -elementpointer for the property -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The previous fib -elementpointer for the property -element is not NULL."<<endl;
		iReturn++;
	}
	//check the getSuperiorFibElement() methode from cProperty
	if ( property1ColorSwO2LayerO1Copy->getSuperiorFibElement() == NULL ){
	
		cout<<"The superior fib -elementpointer for the property -element is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The superior fib -elementpointer for the property -element is not NULL."<<endl;
		iReturn++;
	}
	cFibElement::deleteObject( property1ColorSwO2LayerO1Copy );

	cout<<"cFibElement * pProperty1ColorSwO2LayerO1CopyElement = property1ColorSwO2LayerO1.copyElement();"<<endl;
	cFibElement * pProperty1ColorSwO2LayerO1CopyElement = property1ColorSwO2LayerO1.copyElement();

	if ( pProperty1ColorSwO2LayerO1CopyElement->equalElement( property1ColorSwO2LayerO1 ) ){
	
		cout<<"The pProperty1ColorSwO2LayerO1CopyElement fib -element is equal to property1ColorSwO2LayerO1. "<<endl;
	}else{
		cerr<<"Error: The pProperty1ColorSwO2LayerO1CopyElement fib -element is not equal to property1ColorSwO2LayerO1."<<endl;
		iReturn++;
	}
	iReturn += testNotConnectedFibElement( *pProperty1ColorSwO2LayerO1CopyElement );
	delete pProperty1ColorSwO2LayerO1CopyElement;


	return iReturn;
}




/**
 * This method tests a in the xml -format stored cFibVector.
 *
 * @param szFilename the name of the file wher the cFibVector is stored
 * @param szPropertyName the name/type of property
 * @param uiVectorElements the number of elements in the vector
 * @param vecElementType a vector with the typs of the vectorelements
 * 	(w=value; v=variable, u=undefined)
 * @param vecValues the values of the vectorelements
 * @return the number of errors occured in the test
 */
int testXmlProperty( const string szFilename, const string szPropertyName,
		bool bHasVector, unsigned int uiVectorElements, vector<char> vecElementType,
		vector<double> vecValues ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cProperty:"<<endl;
	
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
		
		const string szPropertyElementName = "property";
		if ( szElementName == szPropertyElementName ){
			cout<<"The root element is correctly named \""<< szPropertyElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szPropertyElementName <<"\"."<<endl;
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
			cout<<"The property contains correctly no vector. "<<endl;
		
		}else{
			cerr<<"Error: The property contains vector, but it shouldn't."<<endl;
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
		}else if ( szPropertyName == szVectorXmlType ) {
			cout<<"The type of the vector is correctly \""<< szPropertyName <<"\". "<<endl;
		}else{
			cerr<<"Error: The type of the vector is \""<< szVectorXmlType
				<<"\", but should be \""<< szPropertyName <<"\"."<<endl;
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
 * This method tests the storeXml() method of the cProperty class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an property for colorSw"<<endl;

	cout<<"cVectorProperty vecPropertyColorSW1( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW1( cTypeProperty::COLOR_SW );
	cout<<"cProperty propertyColorSw1( vecPropertyColorSW1 );"<<endl;
	cProperty propertyColorSw1( vecPropertyColorSW1 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlPropertyFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "propertyColorSw1.xml" );
	ofstream * pFileVectorPostion = new ofstream( szXmlPropertyFileName );
	
	bool bStoreSuccesfull = propertyColorSw1.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cProperty was stored successfull to the file \""<< szXmlPropertyFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cProperty to the file \""<< szXmlPropertyFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	vector<char> vecElementTypePosition( 5, 'w' );
	vector<double> vecValuesPosition( 5, 0.0 );
	
	iReturn += testXmlProperty( szXmlPropertyFileName, "property.colorSW", true,
		1, vecElementTypePosition, vecValuesPosition );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an property with a propertyvector for colorRgb"<<endl;

	//property with 3 D Propertyvector
	cout<<"cVectorProperty vecPropertyColorRgb( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyColorRgb( cTypeProperty::COLOR_RGB );
	cout<<"vecPropertyColorRgb.setValue( 1, 4);"<<endl;
	vecPropertyColorRgb.setValue( 1, 4);
	vecElementTypePosition[0] = 'w';
	vecValuesPosition[0] = 4;
	cout<<"vecPropertyColorRgb.setValue( 2, 3);"<<endl;
	vecPropertyColorRgb.setValue( 2, 3);
	vecElementTypePosition[1] = 'w';
	vecValuesPosition[1] = 3;
	cout<<"vecPropertyColorRgb.setValue( 3, 2);"<<endl;
	vecPropertyColorRgb.setValue( 3, 2);
	vecElementTypePosition[2] = 'w';
	vecValuesPosition[2] = 2;
	cout<<"cProperty propertyColorRgb( vecPropertyColorRgb );"<<endl;
	cProperty propertyColorRgb( vecPropertyColorRgb );
	
	szFileNameBuffer[0] = 0;
	szXmlPropertyFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "propertyColorRgb.xml" );
	pFileVectorPostion = new ofstream( szXmlPropertyFileName );
	
	bStoreSuccesfull = propertyColorRgb.storeXml( *pFileVectorPostion );
	delete pFileVectorPostion;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cProperty was stored successfull to the file \""<< szXmlPropertyFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cProperty to the file \""<< szXmlPropertyFileName <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlProperty( szXmlPropertyFileName, "property.colorRGB", true,
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

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an colorSw property"<<endl;

	cout<<"cPoint point1;"<<flush<<endl;
	cPoint point1;

	cout<<"cRoot rootColorSw;"<<flush<<endl;
	cRoot rootColorSw;
	
	cout<<"cTypeProperty testTypePropertyColorSw( cTypeProperty::COLOR_SW );"<<endl;
	cTypeProperty testTypePropertyColorSw( cTypeProperty::COLOR_SW );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1( 1 );
	cout<<"vecDomainsE1[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomainE1( vecDomainsE1 );"<<endl;
	cDomainVector vectorDomainE1( vecDomainsE1 );
	delete vecDomainsE1[ 0 ];

	cout<<"rootColorSw.getDomains()->addDomain( testTypePropertyColorSw, &vectorDomainE1 );"<<endl;
	rootColorSw.getDomains()->addDomain( testTypePropertyColorSw, &vectorDomainE1 );


	cout<<"cVectorProperty vecPropertyColorSW1( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW1( cTypeProperty::COLOR_SW );
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyColorSw1( vecPropertyColorSW1, &point1, &rootColorSw );"<<endl;
	cProperty propertyColorSw1( vecPropertyColorSW1, &point1, &rootColorSw );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyColorSw1( vecPropertyColorSW1, &rootColorSw, &rootColorSw, &point1 );"<<endl;
	cProperty propertyColorSw1( vecPropertyColorSW1, &rootColorSw, &rootColorSw, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//test get compressed size
	unsigned int uiCompressedSize = 4 + 2 + 5;
	if ( (unsigned int)(propertyColorSw1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			propertyColorSw1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "propertyColorSw1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bool bStoreSuccesfull = propertyColorSw1.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cPropertyColorSw1[] = { (char)0x83, (char)0x04  };
	iReturn += compareBytsWithFile( szFileNameBuffer, cPropertyColorSw1, 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an property with is the secound property of two possibles"<<endl;


	cout<<"cTypeProperty testTypePropertyColorRgb( cTypeProperty::COLOR_RGB );"<<endl;
	cTypeProperty testTypePropertyColorRgb( cTypeProperty::COLOR_RGB );
	
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

	cout<<"cRoot rootColorSwRgb;"<<flush<<endl;
	cRoot rootColorSwRgb;
	cout<<"rootColorSwRgb.getDomains()->addDomain( testTypePropertyColorSw, &vectorDomainE1 );"<<endl;
	rootColorSwRgb.getDomains()->addDomain( testTypePropertyColorSw, &vectorDomainE1 );
	cout<<"rootColorSwRgb.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainD3 );"<<endl;
	rootColorSwRgb.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainD3 );

	cout<<"cVectorProperty vecPropertyColorRgb1( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyColorRgb1( cTypeProperty::COLOR_RGB );
	cout<<"vecPropertyColorRgb1.setValue( 2, 2);"<<endl;
	vecPropertyColorRgb1.setValue( 2, 2);
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyColorRgb( vecPropertyColorRgb1, &point1, &rootColorSwRgb );"<<endl;
	cProperty propertyColorRgb( vecPropertyColorRgb1, &point1, &rootColorSwRgb );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyColorRgb( vecPropertyColorRgb1, &rootColorSwRgb, &rootColorSwRgb, &point1 );"<<endl;
	cProperty propertyColorRgb( vecPropertyColorRgb1, &rootColorSwRgb, &rootColorSwRgb, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//test get compressed size
	uiCompressedSize = 4 + 1 + 9 + 5;
	if ( (unsigned int)(propertyColorRgb.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			propertyColorRgb.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "propertyColorRgb.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = propertyColorRgb.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	const char cPropertyColorRgb[] = { (char)0x13, (char)0x82, (char)0x04 }; //Bits: 0001 0011 ; 1000 0010 ; 0000 0010
	iReturn += compareBytsWithFile( szFileNameBuffer, cPropertyColorRgb, 3 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an property with a propertyvector with changed values"<<endl;

	cout<<"vecPropertyColorSW1.setValue( 1, 1 );"<<endl;
	vecPropertyColorSW1.setValue( 1, 1 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootColorSwRgb1;"<<flush<<endl;
	cRoot rootColorSwRgb1;
	cout<<"rootColorSwRgb1.getDomains()->addDomain( testTypePropertyColorSw, &vectorDomainE1 );"<<endl;
	rootColorSwRgb1.getDomains()->addDomain( testTypePropertyColorSw, &vectorDomainE1 );
	cout<<"rootColorSwRgb1.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainD3 );"<<endl;
	rootColorSwRgb1.getDomains()->addDomain( testTypePropertyColorRgb, &vectorDomainD3 );

	cout<<"cProperty propertyColorSw2( vecPropertyColorSW1, &point1, &rootColorSwRgb1 );"<<endl;
	cProperty propertyColorSw2( vecPropertyColorSW1, &point1, &rootColorSwRgb1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyColorSw2( vecPropertyColorSW1, &rootColorSwRgb, &rootColorSwRgb, &point1 );"<<endl;
	cProperty propertyColorSw2( vecPropertyColorSW1, &rootColorSwRgb, &rootColorSwRgb, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//test get compressed size
	uiCompressedSize = 4 + 1 + 2 + 5;
	if ( (unsigned int)(propertyColorSw2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			propertyColorSw2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "propertyColorSw2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	bStoreSuccesfull = propertyColorSw2.store( *pFile );
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	//test stored data
	const char cPropertyColorSw2[] = { (char)0x43, (char)0x09  };//Bits: 0100 0011 ; 0000 1001
	iReturn += compareBytsWithFile( szFileNameBuffer, cPropertyColorSw2, 2 );
	
	return iReturn;
}



/**
 * This method positions methods of the class.
 *
 * methods tested:
 * 	- cVectorProperty * getProperty();
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testProperty( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getProperty() method"<<endl;

	cout<<"cVectorProperty vecPropertyColorRgb( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyColorRgb( cTypeProperty::COLOR_RGB );
	cout<<"vecPropertyColorRgb.setValue( 1, 1);"<<endl;
	vecPropertyColorRgb.setValue( 1, 1);
	cout<<"vecPropertyColorRgb.setValue( 2, 2);"<<endl;
	vecPropertyColorRgb.setValue( 2, 2);
	cout<<"vecPropertyColorRgb.setValue( 3, 3);"<<endl;
	vecPropertyColorRgb.setValue( 3, 3);

	cout<<"cVectorProperty vecPropertyColorRgbCopy( vecPropertyColorRgb );"<<endl;
	cVectorProperty vecPropertyColorRgbCopy( vecPropertyColorRgb );

	cout<<"cProperty property1( vecPropertyColorRgb );"<<endl;
	cProperty property1( vecPropertyColorRgb );

	//test getProperty()
	cout<<"property1.getProperty()"<<endl;
	if ( property1.getProperty() != NULL ){
	
		if ( *property1.getProperty() == vecPropertyColorRgb ){
		
			cout<<"The propertyvector is equal to vecPropertyColorRgb. "<<endl;
		}else{
			cerr<<"Error: The propertyvector is not equal to vecPropertyColorRgb."<<endl;
			iReturn++;
		}
		if ( property1.getProperty() != &vecPropertyColorRgb ){
		
			cout<<"The propertyvectorpointer is not equal to vecPropertyColorRgb. "<<endl;
		}else{
			cerr<<"Error: The propertyvectorpointer is equal to vecPropertyColorRgb."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error:The propertyvectorpointer is NULL ."<<endl;
		iReturn++;
	}

	cout<<"property1.getProperty()->setValue( 1, 7 );"<<endl;
	property1.getProperty()->setValue( 1, 7 );
	cout<<"vecPropertyColorRgbCopy.setValue( 1, 7 );"<<endl;
	vecPropertyColorRgbCopy.setValue( 1, 7 );

	//test getProperty()
	cout<<"property1.getProperty()"<<endl;
	if ( property1.getProperty() != NULL ){
	
		if ( ! (*property1.getProperty() == vecPropertyColorRgb) ){
		
			cout<<"The propertyvector is not anymore equal to vecPropertyColorRgb. "<<endl;
		}else{
			cerr<<"Error: The propertyvector is equal to vecPropertyColorRgb."<<endl;
			iReturn++;
		}
		if ( *property1.getProperty() == vecPropertyColorRgbCopy ){
		
			cout<<"The propertyvector has the correct values. "<<endl;
		}else{
			cerr<<"Error: The propertyvector hasn't the correct values."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error:The propertyvectorpointer is NULL ."<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getProperty() methods on a property with a accessible domain"<<endl;

	cout<<"cRoot rootColorSw;"<<flush<<endl;
	cRoot rootColorSw;
	
	cout<<"cTypeProperty testTypePropertyColorSw( cTypeProperty::COLOR_SW );"<<endl;
	cTypeProperty testTypePropertyColorSw( cTypeProperty::COLOR_SW );
	
	//create vector domain with two elements
	cout<<"vector<cDomainSingle*> vecDomainsE1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomainsE1( 1 );
	cout<<"vecDomainsE1[ 0 ] = new cDomainNaturalNumberBit( 1 );"<<endl;
	vecDomainsE1[ 0 ] = new cDomainNaturalNumberBit( 1 );
	cout<<"cDomainVector vectorDomainE1( vecDomainsE1 );"<<endl;
	cDomainVector vectorDomainE1( vecDomainsE1 );
	delete vecDomainsE1[ 0 ];

	cout<<"rootColorSw.getDomains()->addDomain( testTypePropertyColorSw, &vectorDomainE1 );"<<endl;
	rootColorSw.getDomains()->addDomain( testTypePropertyColorSw, &vectorDomainE1 );


	cout<<"cVectorProperty vecPropertyColorSW1( cTypeProperty::COLOR_SW );"<<endl;
	cVectorProperty vecPropertyColorSW1( cTypeProperty::COLOR_SW );
	cout<<"vecPropertyColorSW1.setValue( 1, 2 );"<<endl;
	vecPropertyColorSW1.setValue( 1, 2 );
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyColorSw1( vecPropertyColorSW1, NULL, &rootColorSw );"<<endl;
	cProperty propertyColorSw1( vecPropertyColorSW1, NULL, &rootColorSw );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyColorSw1( vecPropertyColorSW1, &rootColorSw, &rootColorSw, NULL );"<<endl;
	cProperty propertyColorSw1( vecPropertyColorSW1, &rootColorSw, &rootColorSw, NULL );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	
	cVectorProperty vecPropertyColorSW2( cTypeProperty::COLOR_SW );
	vecPropertyColorSW2.setValue( 1, 1 );

	//test getProperty()
	cout<<"propertyColorSw1.getProperty()"<<endl;
	if ( propertyColorSw1.getProperty() != NULL ){
	
		if ( ! (*propertyColorSw1.getProperty() == vecPropertyColorSW1) ){
		
			cout<<"The propertyvector is not anymore equal to vecPropertyColorSW1. "<<endl;
		}else{
			cerr<<"Error: The propertyvector is equal to vecPropertyColorSW1."<<endl;
			iReturn++;
		}
		if ( *propertyColorSw1.getProperty() == vecPropertyColorSW2 ){
		
			cout<<"The propertyvector has the correct values. "<<endl;
		}else{
			cerr<<"Error: The propertyvector hasn't the correct values."<<endl;
			iReturn++;
		}
		if ( propertyColorSw1.getProperty() != &vecPropertyColorSW1 ){
		
			cout<<"The propertyvectorpointer is not equal to propertyColorSw1. "<<endl;
		}else{
			cerr<<"Error: The propertyvectorpointer is equal to propertyColorSw1."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error:The propertyvectorpointer is NULL ."<<endl;
		iReturn++;
	}


	return iReturn;
}




/**
 * This method tests the variable methods of the cProperty class.
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
	
	cout<<"cVectorProperty vecPropertyColorRgb( cTypeProperty::COLOR_RGB );"<<endl;
	cVectorProperty vecPropertyColorRgb( cTypeProperty::COLOR_RGB );
	cout<<"vecPropertyColorRgb.setValue( 1, 4);"<<endl;
	vecPropertyColorRgb.setValue( 1, 4);
	cout<<"vecPropertyColorRgb.setValue( 2, 7);"<<endl;
	vecPropertyColorRgb.setValue( 2, 7);
	cout<<"vecPropertyColorRgb.setValue( 3, 4);"<<endl;
	vecPropertyColorRgb.setValue( 3, 4);

	cout<<"cProperty propertyE3( vecPropertyColorRgb );"<<endl;
	cProperty propertyE3( vecPropertyColorRgb );

	//check the isUsedVariable() methode from cProperty
	cout<<"propertyE3.isUsedVariable( pVariable1 )"<<endl;
	if ( ! propertyE3.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the property -element. "<<endl;
		iReturn++;
	}
	set<cFibVariable*> setCorrectUsedVariables;
	
	//check getUsedVariables()
	cout<<"setUsedVariables = propertyE3.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = propertyE3.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"propertyE3.getProperty()->setVariable( 3, pVariable1 );"<<endl;
	propertyE3.getProperty()->setVariable( 3, pVariable1 );
	setCorrectUsedVariables.insert( pVariable1 );

	//check the isUsedVariable() methode from cProperty
	cout<<"propertyE3.isUsedVariable( pVariable1 )"<<endl;
	if ( propertyE3.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the property -element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = propertyE3.getUsedVariables(); "<<endl;
	setUsedVariables = propertyE3.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"propertyE3.getProperty()->setVariable( 1, pVariable2 );"<<endl;
	propertyE3.getProperty()->setVariable( 1, pVariable2 );
	setCorrectUsedVariables.insert( pVariable2 );

	//check the isUsedVariable() methode from cProperty
	cout<<"propertyE3.isUsedVariable( pVariable2 )"<<endl;
	if ( propertyE3.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the property -element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = propertyE3.getUsedVariables(); "<<endl;
	setUsedVariables = propertyE3.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"propertyE3.getProperty()->setVariable( 2, pVariable4 );"<<endl;
	propertyE3.getProperty()->setVariable( 2, pVariable4 );
	setCorrectUsedVariables.insert( pVariable4 );

	//check the isUsedVariable() methode from cProperty
	cout<<"propertyE3.isUsedVariable( pVariable4 )"<<endl;
	if ( propertyE3.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable4 is correctly used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is not used in the property -element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = propertyE3.getUsedVariables(); "<<endl;
	setUsedVariables = propertyE3.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"propertyE3.getProperty()->setVariable( 2, pVariable1 );"<<endl;
	propertyE3.getProperty()->setVariable( 2, pVariable1 );
	setCorrectUsedVariables.erase( pVariable4 );
	//check the isUsedVariable() methode from cProperty
	cout<<"propertyE3.isUsedVariable( pVariable1 )"<<endl;
	if ( propertyE3.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the property -element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = propertyE3.getUsedVariables(); "<<endl;
	setUsedVariables = propertyE3.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"propertyE3.replaceVariable( pVariable2, pVariable3 );"<<endl;
	bool bVariableReplaced = propertyE3.replaceVariable( pVariable2, pVariable3 );
	setCorrectUsedVariables.erase( pVariable2 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cProperty
	cout<<"propertyE3.isUsedVariable( pVariable2 )"<<endl;
	if ( ! propertyE3.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the property -element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cProperty
	cout<<"propertyE3.isUsedVariable( pVariable3 )"<<endl;
	if ( propertyE3.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the property -element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = propertyE3.getUsedVariables(); "<<endl;
	setUsedVariables = propertyE3.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	cout<<"Try replacing non existing variable pVariable2:"<<endl;
	cout<<"propertyE3.replaceVariable( pVariable2, pVariable4 );"<<endl;
	bVariableReplaced = propertyE3.replaceVariable( pVariable2, pVariable4 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = propertyE3.getUsedVariables(); "<<endl;
	setUsedVariables = propertyE3.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cProperty
	cout<<"propertyE3.isUsedVariable( pVariable2 )"<<endl;
	if ( ! propertyE3.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the property -element. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cProperty
	cout<<"propertyE3.isUsedVariable( pVariable4 )"<<endl;
	if ( ! propertyE3.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable4 is correctly not used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is used in the property -element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cProperty
	cout<<"propertyE3.isUsedVariable( pVariable3 )"<<endl;
	if ( propertyE3.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the property -element. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing variable methods on a property with a containing point"<<endl;

	cout<<"cVectorPosition vecPositionE3( 3 );"<<endl;
	cVectorPosition vecPositionE3( 3 );

	cout<<"cPoint point1( &vecPositionE3 );"<<endl;
	cPoint point1( &vecPositionE3 );

#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyRgbPoint( vecPropertyColorRgb, &point1 );"<<endl;
	cProperty propertyRgbPoint( vecPropertyColorRgb, &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cProperty propertyRgbPoint( vecPropertyColorRgb, NULL, NULL, &point1 );"<<endl;
	cProperty propertyRgbPoint( vecPropertyColorRgb, NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	//check the isUsedVariable() methode from cProperty
	cout<<"propertyRgbPoint.isUsedVariable( pVariable1 )"<<endl;
	if ( ! propertyRgbPoint.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the property -element. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.clear();
	
	//check getUsedVariables()
	cout<<"setUsedVariables = propertyRgbPoint.getUsedVariables(); "<<endl;
	setUsedVariables = propertyRgbPoint.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<"point1.getPosition()->setVariable( 3, pVariable1 );"<<endl;
	point1.getPosition()->setVariable( 3, pVariable1 );

	//check the isUsedVariable() methode from cProperty
	cout<<"propertyRgbPoint.isUsedVariable( pVariable1 )"<<endl;
	if ( ! propertyRgbPoint.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the property -element. "<<endl;
		iReturn++;
	}
	cout<<"point1.isUsedVariable( pVariable1 )"<<endl;
	if ( point1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the property -element. "<<endl;
		iReturn++;
	}
	cout<<"propertyRgbPoint.isUsedVariable( pVariable1, ED_BELOW_EQUAL )"<<endl;
	if ( propertyRgbPoint.isUsedVariable( pVariable1, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable1 is correctly used ED_BELOW_EQUAL the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used ED_BELOW_EQUAL the property -element. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = propertyRgbPoint.getUsedVariables(); "<<endl;
	setUsedVariables = propertyRgbPoint.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.insert( pVariable1 );
	//check getUsedVariables()
	cout<<"setUsedVariables = propertyRgbPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = propertyRgbPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back for ED_BELOW_EQUAL. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong for ED_BELOW_EQUAL. "<<endl;
		iReturn++;
	}


	cout<<"point1.getPosition()->setVariable( 1, pVariable2 );"<<endl;
	point1.getPosition()->setVariable( 1, pVariable2 );
	
	//check the isUsedVariable() methode from cProperty
	cout<<"propertyRgbPoint.isUsedVariable( pVariable2 )"<<endl;
	if ( ! propertyRgbPoint.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the property -element. "<<endl;
		iReturn++;
	}
	cout<<"point1.isUsedVariable( pVariable2 )"<<endl;
	if ( point1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the property -element. "<<endl;
		iReturn++;
	}
	cout<<"propertyRgbPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( propertyRgbPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly used ED_BELOW_EQUAL the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used ED_BELOW_EQUAL the property -element. "<<endl;
		iReturn++;
	}
	
	//check getUsedVariables()
	cout<<"setUsedVariables = propertyRgbPoint.getUsedVariables(); "<<endl;
	setUsedVariables = propertyRgbPoint.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	setCorrectUsedVariables.insert( pVariable2 );
	//check getUsedVariables()
	cout<<"setUsedVariables = propertyRgbPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = propertyRgbPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back for ED_BELOW_EQUAL. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong for ED_BELOW_EQUAL. "<<endl;
		iReturn++;
	}
	
	cout<<"propertyRgbPoint.replaceVariable( pVariable2, pVariable3 );"<<endl;
	bVariableReplaced = propertyRgbPoint.replaceVariable( pVariable2, pVariable3 );
	setCorrectUsedVariables.erase( pVariable2 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cProperty
	cout<<"propertyRgbPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL )"<<endl;
	if ( ! propertyRgbPoint.isUsedVariable( pVariable2, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable2 is correctly not used ED_BELOW_EQUAL the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used ED_BELOW_EQUAL the property -element. "<<endl;
		iReturn++;
	}

	//check the isUsedVariable() methode from cProperty
	cout<<"propertyRgbPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL )"<<endl;
	if ( propertyRgbPoint.isUsedVariable( pVariable3, ED_BELOW_EQUAL ) ){
	
		cout<<"The variable pVariable3 is correctly used ED_BELOW_EQUAL the property -element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used ED_BELOW_EQUAL the property -element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = propertyRgbPoint.getUsedVariables( ED_BELOW_EQUAL ); "<<endl;
	setUsedVariables = propertyRgbPoint.getUsedVariables( ED_BELOW_EQUAL );
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods isDefinedVariable( ED_POSITION ) and getDefinedVariables( ED_POSITION )"<<endl;

	//check the isDefinedVariable() methode from cList
	cout<<"propertyRgbPoint.isDefinedVariable( pVariable1, ED_POSITION )"<<endl;
	if ( ! propertyRgbPoint.isDefinedVariable( pVariable1, ED_POSITION ) ){
	
		cout<<"The variable pVariable1 is correctly not defined in the propertyelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is defined in the propertyelement. "<<endl;
		iReturn++;
	}

	//check getDefinedVariables()
	cout<<"liDefinedVariables = propertyRgbPoint.getDefinedVariables( ED_POSITION ); "<<endl;
	list<cFibVariable*> liDefinedVariables = propertyRgbPoint.getDefinedVariables( ED_POSITION );
	if ( liDefinedVariables.empty() ){
	
		cout<<"Ther are correctly no variables defines. "<<endl;
	}else{
		cerr<<"Error: Ther are variables defines. "<<endl;
		iReturn++;
	}
	
	return iReturn;
}








