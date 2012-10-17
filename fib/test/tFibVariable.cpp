/**
 * @file tFibVariable
 * file name: tFibVariable.cpp
 * @author Betti Oesterholz
 * @date 13.07.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cFibVariable.
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
 * This file contains the test for the class cFibVariable, which
 * represents a variable for an Fib -element.
 *
 *
 * What's tested of class cDomains:
 * 	- cFibVariable( const cFibVariable & variable );
 * 	- cFibVariable( cFibElement *definingFibElement );
 * 	- void registerUsingElement( iVariableUser * usingElement );
 * 	- void unregisterUsingElement( iVariableUser * usingElement );
 * 	- doubleFib getValue() const;
 * 	- longFib getIntegerValue() const;
 * 	- void setValue( const doubleFib dValue );
 * 	- void setIntegerValue( const longFib lValue );
 * 	- cFibElement *getDefiningElement( ) const;
 * 	- unsignedIntFib getNumberOfUsingElements( ) const;
 * 	- set<cFibElement*> getUsingElements() const;
 * 	- bool isSet() const;
 * 	- bool isIntegerValue() const;
 * 	- cFibVariable & operator=( const cFibVariable &variable );
 * 	- bool equal( const cFibVariable &variable ) const;
 * 	- bool operator==( const cFibVariable &variable ) const;
 *
 */
/*
History:
13.07.2009  Oesterholz  created
15.11.2009  Oesterholz  testing of: copyconstructor, operator=(),
	the equalmethodes and isIntegerValue()
20.02.2009  Oesterholz  testRegisterVector()
*/

#include "version.h"

#include "cFibVariable.h"
#include "cVectorProperty.h"
#include "cVectorPosition.h"
#include "cRoot.h"
#include "cPoint.h"

#include <iostream>
#include <algorithm>


using namespace fib;
using namespace std;

int testCostructor( unsigned long &ulTestphase );
int testValueMethods( unsigned long &ulTestphase );
int testUsingElements( unsigned long &ulTestphase );
int testCopyConstructor( unsigned long &ulTestphase );
int testAssignment( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testRegisterVector( unsigned long &ulTestphase );

int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cFibVariable methods"<<endl;
	cout<<      "====================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testValueMethods( ulTestphase );
	iReturn += testUsingElements( ulTestphase );
	iReturn += testCopyConstructor( ulTestphase );
	iReturn += testAssignment( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testRegisterVector( ulTestphase );

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the constructor and getDefiningElement( ) method of
 * the cFibVariable class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cFibVariable"<<endl;

	//TODO adapt root -constructor use other Fib -elements
	cRoot * definingRoot= new cRoot();

	cout<<"cFibVariable fibVariable1( definingRoot );"<<endl;
	cFibVariable fibVariable1( (cFibElement*)definingRoot );

	//check the getValue() methode from cFibVariable
	if ( fibVariable1.getValue()==(doubleFib)(0.0) ){
	
		cout<<"The value of the new variable object is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The value of the new variable object "<<
			fibVariable1.getValue()<<" but should be 0.0 ."<<endl;
		iReturn++;
	}

	//check the getIntegerValue() methode from cFibVariable
	if ( fibVariable1.getIntegerValue()==(longFib)(0) ){
	
		cout<<"The integer value of the new variable object is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The integer value of the new variable object "<<
			fibVariable1.getIntegerValue()<<" but should be 0 ."<<endl;
		iReturn++;
	}

	//check the getDefiningElement() methode from cFibVariable
	//TODO eleminate cast
	if ( fibVariable1.getDefiningElement()==(cFibElement*)definingRoot ){
	
		cout<<"The defining Fib -element of the new variable object is the"<<
			" correct root element . "<<endl;
	}else{
		cerr<<"Error: The defining Fib -element of the new variable object is "<<
			fibVariable1.getDefiningElement()<<" but should be "<<
				definingRoot<<" ."<<endl;
		iReturn++;
	}

	//check the getNumberOfUsingElements() methode from cFibVariable
	if ( fibVariable1.getNumberOfUsingElements()==(unsignedIntFib)(0) ){
	
		cout<<"The number of using Fib -elements of the new variable object"<<
				" is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of using Fib -elements of the new variable object is "<<
			fibVariable1.getNumberOfUsingElements()<<" but should be 0 ."<<endl;
		iReturn++;
	}

	//check the getUsingElements() methode from cFibVariable
	set<cFibElement*> usingElements=fibVariable1.getUsingElements();

	if ( usingElements.size()==(unsignedIntFib)(0) ){
	
		cout<<"The number of returned using Fib -elements of the new variable"<<
				" object is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of returned using Fib -elements of the new variable object is "<<
			usingElements.size()<<" but should be 0 ."<<endl;
		iReturn++;
	}

	//check the isSet() methode from cFibVariable
	if ( ! fibVariable1.isSet() ){
	
		cout<<"The variable is correctly not set to an value."<<endl;
	}else{
		cerr<<"Error: The variable is looks like it is set to an value, but it shouldn't."<<endl;
		iReturn++;
	}
	delete definingRoot;

	return iReturn;
}


/**
 * This method tests the methods for getting and setting the value of the
 * variable which is represented by the cFibVariable class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testValueMethods( unsigned long &ulTestphase ){


	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cFibVariable for value changes"<<endl;

	//TODO adapt root -constructor use other Fib -elements
	cRoot * definingRoot= new cRoot();

	cout<<"cFibVariable fibVariable1=cFibVariable( masterRoot );"<<endl;
	cFibVariable fibVariable1=cFibVariable( (cFibElement*)definingRoot );

	//check the getValue() methode from cFibVariable
	if ( fibVariable1.getValue()==(doubleFib)(0.0) ){
	
		cout<<"The value of the new variable object is correctly 0.0 . "<<endl;
	}else{
		cerr<<"Error: The value of the new variable object "<<
			fibVariable1.getValue()<<" but should be 0.0 ."<<endl;
		iReturn++;
	}

	//check the getIntegerValue() methode from cFibVariable
	if ( fibVariable1.getIntegerValue()==(longFib)(0) ){
	
		cout<<"The integer value of the new variable object is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The integer value of the new variable object "<<
			fibVariable1.getIntegerValue()<<" but should be 0 ."<<endl;
		iReturn++;
	}
	
	//check the isSet() methode from cFibVariable
	if ( ! fibVariable1.isSet() ){
	
		cout<<"The variable is correctly not set to an value."<<endl;
	}else{
		cerr<<"Error: The variable is looks like it is set to an value, but it shouldn't."<<endl;
		iReturn++;
	}
	//check the isIntegerValue() methode from cFibVariable
	if ( ! fibVariable1.isIntegerValue() ){
	
		cout<<"The variable is correctly not set to an integervalue."<<endl;
	}else{
		cerr<<"Error: The variable is looks like it is set to an integervalue, but it shouldn't."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : changing the value of the variable"<<endl;

	cout<<"fibVariable1.setValue( 1.1 );"<<endl;
	fibVariable1.setValue( 1.1 );

	//check the getValue() methode from cFibVariable
	if ( fibVariable1.getValue()==(doubleFib)(1.1) ){
	
		cout<<"The value of the variable object is correctly 1.1 . "<<endl;
	}else{
		cerr<<"Error: The value of the variable object "<<
			fibVariable1.getValue()<<" but should be 1.1 ."<<endl;
		iReturn++;
	}

	//check the getIntegerValue() methode from cFibVariable
	if ( fibVariable1.getIntegerValue()==(longFib)(1) ){
	
		cout<<"The integer value of the variable object is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The integer value of the variable object "<<
			fibVariable1.getIntegerValue()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the isSet() methode from cFibVariable
	if ( fibVariable1.isSet() ){
	
		cout<<"The variable is correctly set to an value."<<endl;
	}else{
		cerr<<"Error: The variable is looks like it isn't set to an value, but it should."<<endl;
		iReturn++;
	}
	//check the isIntegerValue() methode from cFibVariable
	if ( ! fibVariable1.isIntegerValue() ){
	
		cout<<"The variable is correctly not set to an integervalue."<<endl;
	}else{
		cerr<<"Error: The variable is looks like it is set to an integervalue, but it shouldn't."<<endl;
		iReturn++;
	}


	cout<<"fibVariable1.setValue( 1.49 );"<<endl;
	fibVariable1.setValue( 1.49 );

	//check the getValue() methode from cFibVariable
	if ( fibVariable1.getValue()==(doubleFib)(1.49) ){
	
		cout<<"The value of the variable object is correctly 1.49 . "<<endl;
	}else{
		cerr<<"Error: The value of the variable object "<<
			fibVariable1.getValue()<<" but should be 1.49 ."<<endl;
		iReturn++;
	}

	//check the getIntegerValue() methode from cFibVariable
	if ( fibVariable1.getIntegerValue()==(longFib)(1) ){
	
		cout<<"The integer value of the variable object is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The integer value of the variable object "<<
			fibVariable1.getIntegerValue()<<" but should be 1 ."<<endl;
		iReturn++;
	}

	//check the isSet() methode from cFibVariable
	if ( fibVariable1.isSet() ){
	
		cout<<"The variable is correctly set to an value."<<endl;
	}else{
		cerr<<"Error: The variable is looks like it isn't set to an value, but it should."<<endl;
		iReturn++;
	}
	//check the isIntegerValue() methode from cFibVariable
	if ( ! fibVariable1.isIntegerValue() ){
	
		cout<<"The variable is correctly not set to an integervalue."<<endl;
	}else{
		cerr<<"Error: The variable is looks like it is set to an integervalue, but it shouldn't."<<endl;
		iReturn++;
	}

	cout<<"fibVariable1.setValue( 1.501 );"<<endl;
	fibVariable1.setValue( 1.501 );

	//check the getValue() methode from cFibVariable
	if ( fibVariable1.getValue()==(doubleFib)(1.501) ){
	
		cout<<"The value of the variable object is correctly 1.501 . "<<endl;
	}else{
		cerr<<"Error: The value of the variable object "<<
			fibVariable1.getValue()<<" but should be 1.501 ."<<endl;
		iReturn++;
	}

	//check the getIntegerValue() methode from cFibVariable
	if ( fibVariable1.getIntegerValue()==(longFib)(2) ){
	
		cout<<"The integer value of the variable object is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The integer value of the variable object "<<
			fibVariable1.getIntegerValue()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	cout<<"fibVariable1.setValue( -1501.2547 );"<<endl;
	fibVariable1.setValue( -1501.2547 );

	//check the getValue() methode from cFibVariable
	if ( fibVariable1.getValue()==(doubleFib)(-1501.2547) ){
	
		cout<<"The value of the variable object is correctly -1501.2547 . "<<endl;
	}else{
		cerr<<"Error: The value of the variable object "<<
			fibVariable1.getValue()<<" but should be -1501.2547 ."<<endl;
		iReturn++;
	}

	//check the getIntegerValue() methode from cFibVariable
	if ( fibVariable1.getIntegerValue()==(longFib)(-1501) ){
	
		cout<<"The integer value of the variable object is correctly -1501 . "<<endl;
	}else{
		cerr<<"Error: The integer value of the variable object "<<
			fibVariable1.getIntegerValue()<<" but should be -1501 ."<<endl;
		iReturn++;
	}

	cout<<"fibVariable1.setValue( 952458712.7586421 );"<<endl;
	fibVariable1.setValue( 952458712.7586421 );

	//check the getValue() methode from cFibVariable
	if ( fibVariable1.getValue()==(doubleFib)(952458712.7586421) ){
	
		cout<<"The value of the variable object is correctly 952458712.7586421 . "<<endl;
	}else{
		cerr<<"Error: The value of the variable object "<<
			fibVariable1.getValue()<<" but should be 952458712.7586421 ."<<endl;
		iReturn++;
	}

	//check the getIntegerValue() methode from cFibVariable
	if ( fibVariable1.getIntegerValue()==(longFib)(952458713) ){
	
		cout<<"The integer value of the variable object is correctly 952458713 . "<<endl;
	}else{
		cerr<<"Error: The integer value of the variable object "<<
			fibVariable1.getIntegerValue()<<" but should be 952458713 ."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : changing the integer value of the variable"<<endl;

	cout<<"fibVariable1.setIntegerValue( 1 );"<<endl;
	fibVariable1.setIntegerValue( 1 );

	//check the getIntegerValue() methode from cFibVariable
	if ( fibVariable1.getIntegerValue()==(longFib)(1) ){
	
		cout<<"The integer value of the variable object is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The integer value of the variable object "<<
			fibVariable1.getIntegerValue()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	//check the isIntegerValue() methode from cFibVariable
	if ( fibVariable1.isIntegerValue() ){
	
		cout<<"The variable is correctly set to an integervalue."<<endl;
	}else{
		cerr<<"Error: The variable is looks like it isn't set to an integervalue, but it shouldn't."<<endl;
		iReturn++;
	}

	cout<<"fibVariable1.setIntegerValue( -1501 );"<<endl;
	fibVariable1.setIntegerValue( -1501 );

	//check the getIntegerValue() methode from cFibVariable
	if ( fibVariable1.getIntegerValue()==(longFib)(-1501) ){
	
		cout<<"The integer value of the variable object is correctly -1501 . "<<endl;
	}else{
		cerr<<"Error: The integer value of the variable object "<<
			fibVariable1.getIntegerValue()<<" but should be -1501 ."<<endl;
		iReturn++;
	}
	//check the isIntegerValue() methode from cFibVariable
	if ( fibVariable1.isIntegerValue() ){
	
		cout<<"The variable is correctly set to an integervalue."<<endl;
	}else{
		cerr<<"Error: The variable is looks like it isn't set to an integervalue, but it shouldn't."<<endl;
		iReturn++;
	}

	cout<<"fibVariable1.setIntegerValue( 950024581 );"<<endl;
	fibVariable1.setIntegerValue( 950024581 );

	//check the getIntegerValue() methode from cFibVariable
	if ( fibVariable1.getIntegerValue()==(longFib)(950024581) ){
	
		cout<<"The integer value of the variable object is correctly 950024581 . "<<endl;
	}else{
		cerr<<"Error: The integer value of the variable object "<<
			fibVariable1.getIntegerValue()<<" but should be 950024581 ."<<endl;
		iReturn++;
	}


	cout<<"fibVariable1.setValue( 1.49 );"<<endl;
	fibVariable1.setValue( 1.49 );

	//check the getValue() methode from cFibVariable
	if ( fibVariable1.getValue()==(doubleFib)(1.49) ){
	
		cout<<"The value of the variable object is correctly 1.49 . "<<endl;
	}else{
		cerr<<"Error: The value of the variable object "<<
			fibVariable1.getValue()<<" but should be 1.49 ."<<endl;
		iReturn++;
	}

	//check the getIntegerValue() methode from cFibVariable
	if ( fibVariable1.getIntegerValue()==(longFib)(1) ){
	
		cout<<"The integer value of the variable object is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The integer value of the variable object "<<
			fibVariable1.getIntegerValue()<<" but should be 1 ."<<endl;
		iReturn++;
	}

	//check the isSet() methode from cFibVariable
	if ( fibVariable1.isSet() ){
	
		cout<<"The variable is correctly set to an value."<<endl;
	}else{
		cerr<<"Error: The variable is looks like it isn't set to an value, but it should."<<endl;
		iReturn++;
	}
	//check the isIntegerValue() methode from cFibVariable
	if ( ! fibVariable1.isIntegerValue() ){
	
		cout<<"The variable is correctly not set to an integervalue."<<endl;
	}else{
		cerr<<"Error: The variable is looks like it is set to an integervalue, but it shouldn't."<<endl;
		iReturn++;
	}
	delete definingRoot;

	return iReturn;
}


/**
 * This method tests the methods for changing the using Fib -Elements of
 * the cFibVariable class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testUsingElements( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cFibVariable for testing using element methods"<<endl;

	//TODO adapt root -constructor use other Fib -elements
	cRoot * definingRoot= new cRoot();

	cout<<"cFibVariable fibVariable1=cFibVariable( masterRoot );"<<endl;
	cFibVariable fibVariable1=cFibVariable( (cFibElement*)definingRoot );

	//TODO adapt: use other Fib -elements
	cFibElement * usingFibElement1 = new cPoint();
	cVectorProperty usingElement1( 1 , usingFibElement1 );
	cFibElement * usingFibElement2 = new cPoint();
	cVectorProperty usingElement2( 2, usingFibElement2 );
	cFibElement * usingFibElement3 = new cPoint();
	cVectorProperty usingElement3( 3, usingFibElement3 );


	//check the getNumberOfUsingElements() methode from cFibVariable
	if ( fibVariable1.getNumberOfUsingElements() == (unsignedIntFib)(0) ){
	
		cout<<"The number of using Fib -elements of the new variable object"<<
				" is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of using Fib -elements of the new variable object is "<<
			fibVariable1.getNumberOfUsingElements()<<" but should be 0 ."<<endl;
		iReturn++;
	}

	//check the getUsingElements() methode from cFibVariable
	set<cFibElement*> usingElements = fibVariable1.getUsingElements();

	if ( usingElements.size() == (unsignedIntFib)(0) ){
	
		cout<<"The number of returned using Fib -elements of the new variable"<<
				" object is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of returned using Fib -elements of the new variable object is "<<
			usingElements.size()<<" but should be 0 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : register a new using element"<<endl;

	cout<<"fibVariable1.registerUsingElement( usingElement1 );"<<endl;
	fibVariable1.registerUsingElement( &usingElement1 );

	//check the getNumberOfUsingElements() methode from cFibVariable
	if ( fibVariable1.getNumberOfUsingElements()==(unsignedIntFib)(1) ){
	
		cout<<"The number of using Fib -elements of the variable object"<<
				" is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of using Fib -elements of the variable object is "<<
			fibVariable1.getNumberOfUsingElements()<<" but should be 1 ."<<endl;
		iReturn++;
	}

	//check the getUsingElements() methode from cFibVariable
	usingElements=fibVariable1.getUsingElements();

	if ( usingElements.size()==(unsignedIntFib)(1) ){
	
		cout<<"The number of returned using Fib -elements of the variable"<<
				" object is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of returned using Fib -elements of the variable object is "<<
			usingElements.size()<<" but should be 1 ."<<endl;
		iReturn++;
	}


	//check if the correct entry was found
	set< cFibElement* >::iterator entryFound;
	
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement1 );
	
	if ( entryFound != usingElements.end() ){
	
		cout<<"The usingFibElement1 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement1 could not be found."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : register a secound using element"<<endl;

	cout<<"fibVariable1.registerUsingElement( &usingElement2 );"<<endl;
	fibVariable1.registerUsingElement( &usingElement2 );

	//check the getNumberOfUsingElements() methode from cFibVariable
	if ( fibVariable1.getNumberOfUsingElements()==(unsignedIntFib)(2) ){
	
		cout<<"The number of using Fib -elements of the variable object"<<
				" is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of using Fib -elements of the variable object is "<<
			fibVariable1.getNumberOfUsingElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getUsingElements() methode from cFibVariable
	usingElements=fibVariable1.getUsingElements();

	if ( usingElements.size()==(unsignedIntFib)(2) ){
	
		cout<<"The number of returned using Fib -elements of the variable"<<
				" object is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of returned using Fib -elements of the variable object is "<<
			usingElements.size()<<" but should be 2 ."<<endl;
		iReturn++;
	}


	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement1 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement1 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement1 could not be found."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement2 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement2 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement2 could not be found."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : register the first element again using element"<<endl;

	cout<<"fibVariable1.registerUsingElement( &usingElement1 );"<<endl;
	fibVariable1.registerUsingElement( &usingElement1 );

	//check the getNumberOfUsingElements() methode from cFibVariable
	if ( fibVariable1.getNumberOfUsingElements()==(unsignedIntFib)(2) ){
	
		cout<<"The number of using Fib -elements of the variable object"<<
				" is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of using Fib -elements of the variable object is "<<
			fibVariable1.getNumberOfUsingElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getUsingElements() methode from cFibVariable
	usingElements=fibVariable1.getUsingElements();

	if ( usingElements.size()==(unsignedIntFib)(2) ){
	
		cout<<"The number of returned using Fib -elements of the variable"<<
				" object is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of returned using Fib -elements of the variable object is "<<
			usingElements.size()<<" but should be 2 ."<<endl;
		iReturn++;
	}


	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement1 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement1 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement1 could not be found."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement2 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement2 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement2 could not be found."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : register a third using element"<<endl;

	cout<<"fibVariable1.registerUsingElement( &usingElement3 );"<<endl;
	fibVariable1.registerUsingElement( &usingElement3 );

	//check the getNumberOfUsingElements() methode from cFibVariable
	if ( fibVariable1.getNumberOfUsingElements()==(unsignedIntFib)(3) ){
	
		cout<<"The number of using Fib -elements of the variable object"<<
				" is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of using Fib -elements of the variable object is "<<
			fibVariable1.getNumberOfUsingElements()<<" but should be 3 ."<<endl;
		iReturn++;
	}

	//check the getUsingElements() methode from cFibVariable
	usingElements=fibVariable1.getUsingElements();

	if ( usingElements.size()==(unsignedIntFib)(3) ){
	
		cout<<"The number of returned using Fib -elements of the variable"<<
				" object is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The number of returned using Fib -elements of the variable object is "<<
			usingElements.size()<<" but should be 3 ."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement1 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement1 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement1 could not be found."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement2 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement2 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement2 could not be found."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement3 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement3 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement3 could not be found."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : unregister the secound using element"<<endl;

	cout<<"fibVariable1.unregisterUsingElement( &usingElement2 );"<<endl;
	fibVariable1.unregisterUsingElement( &usingElement2 );

	//check the getNumberOfUsingElements() methode from cFibVariable
	if ( fibVariable1.getNumberOfUsingElements()==(unsignedIntFib)(2) ){
	
		cout<<"The number of using Fib -elements of the variable object"<<
				" is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of using Fib -elements of the variable object is "<<
			fibVariable1.getNumberOfUsingElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getUsingElements() methode from cFibVariable
	usingElements=fibVariable1.getUsingElements();

	if ( usingElements.size()==(unsignedIntFib)(2) ){
	
		cout<<"The number of returned using Fib -elements of the variable"<<
				" object is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of returned using Fib -elements of the variable object is "<<
			usingElements.size()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement1 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement1 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement1 could not be found."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement3 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement3 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement3 could not be found."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : unregister the secound using element again"<<endl;

	cout<<"fibVariable1.unregisterUsingElement( &usingElement2 );"<<endl;
	fibVariable1.unregisterUsingElement( &usingElement2 );

	//check the getNumberOfUsingElements() methode from cFibVariable
	if ( fibVariable1.getNumberOfUsingElements()==(unsignedIntFib)(2) ){
	
		cout<<"The number of using Fib -elements of the variable object"<<
				" is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of using Fib -elements of the variable object is "<<
			fibVariable1.getNumberOfUsingElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getUsingElements() methode from cFibVariable
	usingElements=fibVariable1.getUsingElements();

	if ( usingElements.size()==(unsignedIntFib)(2) ){
	
		cout<<"The number of returned using Fib -elements of the variable"<<
				" object is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of returned using Fib -elements of the variable object is "<<
			usingElements.size()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement1 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement1 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement1 could not be found."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement3 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement3 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement3 could not be found."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : unregister the first using element again"<<endl;

	cout<<"fibVariable1.unregisterUsingElement( &usingElement1 );"<<endl;
	fibVariable1.unregisterUsingElement( &usingElement1 );

	//check the getNumberOfUsingElements() methode from cFibVariable
	if ( fibVariable1.getNumberOfUsingElements()==(unsignedIntFib)(1) ){
	
		cout<<"The number of using Fib -elements of the variable object"<<
				" is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of using Fib -elements of the variable object is "<<
			fibVariable1.getNumberOfUsingElements()<<" but should be 1 ."<<endl;
		iReturn++;
	}

	//check the getUsingElements() methode from cFibVariable
	usingElements=fibVariable1.getUsingElements();

	if ( usingElements.size()==(unsignedIntFib)(1) ){
	
		cout<<"The number of returned using Fib -elements of the variable"<<
				" object is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of returned using Fib -elements of the variable object is "<<
			usingElements.size()<<" but should be 1 ."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement3 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement3 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement3 could not be found."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : register the first using element"<<endl;

	cout<<"fibVariable1.registerUsingElement( &usingElement1 );"<<endl;
	fibVariable1.registerUsingElement( &usingElement1 );

	//check the getNumberOfUsingElements() methode from cFibVariable
	if ( fibVariable1.getNumberOfUsingElements()==(unsignedIntFib)(2) ){
	
		cout<<"The number of using Fib -elements of the variable object"<<
				" is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of using Fib -elements of the variable object is "<<
			fibVariable1.getNumberOfUsingElements()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check the getUsingElements() methode from cFibVariable
	usingElements=fibVariable1.getUsingElements();

	if ( usingElements.size()==(unsignedIntFib)(2) ){
	
		cout<<"The number of returned using Fib -elements of the variable"<<
				" object is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of returned using Fib -elements of the variable object is "<<
			usingElements.size()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement1 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement1 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement1 could not be found."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement3 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement3 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement3 could not be found."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : unregister the first using element"<<endl;

	cout<<"fibVariable1.unregisterUsingElement( &usingElement1 );"<<endl;
	fibVariable1.unregisterUsingElement( &usingElement1 );

	//check the getNumberOfUsingElements() methode from cFibVariable
	if ( fibVariable1.getNumberOfUsingElements()==(unsignedIntFib)(1) ){
	
		cout<<"The number of using Fib -elements of the variable object"<<
				" is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of using Fib -elements of the variable object is "<<
			fibVariable1.getNumberOfUsingElements()<<" but should be 1 ."<<endl;
		iReturn++;
	}

	//check the getUsingElements() methode from cFibVariable
	usingElements=fibVariable1.getUsingElements();

	if ( usingElements.size()==(unsignedIntFib)(1) ){
	
		cout<<"The number of returned using Fib -elements of the variable"<<
				" object is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The number of returned using Fib -elements of the variable object is "<<
			usingElements.size()<<" but should be 1 ."<<endl;
		iReturn++;
	}

	//check if the correct entry was found
	entryFound=find( usingElements.begin(), usingElements.end(),
		usingFibElement3 );
	
	if ( entryFound!=usingElements.end() ){
	
		cout<<"The usingFibElement3 was correctly found."<<endl;
	}else{
		cerr<<"Error: The usingFibElement3 could not be found."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : unregister the third and last using element again"<<endl;

	cout<<"fibVariable1.unregisterUsingElement( &usingElement3 );"<<endl;
	fibVariable1.unregisterUsingElement( &usingElement3 );

	//check the getNumberOfUsingElements() methode from cFibVariable
	if ( fibVariable1.getNumberOfUsingElements()==(unsignedIntFib)(0) ){
	
		cout<<"The number of using Fib -elements of the variable object"<<
				" is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of using Fib -elements of the variable object is "<<
			fibVariable1.getNumberOfUsingElements()<<" but should be 0 ."<<endl;
		iReturn++;
	}

	//check the getUsingElements() methode from cFibVariable
	usingElements=fibVariable1.getUsingElements();

	if ( usingElements.size()==(unsignedIntFib)(0) ){
	
		cout<<"The number of returned using Fib -elements of the variable"<<
				" object is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The number of returned using Fib -elements of the variable object is "<<
			usingElements.size()<<" but should be 0 ."<<endl;
		iReturn++;
	}
	delete definingRoot;
	delete usingFibElement1;
	delete usingFibElement2;
	delete usingFibElement3;


	return iReturn;
}


/**
 * This method compares to cFibVariable's if ther are equal.
 *
 * @param variable1 the first variable to compare
 * @param szNameVariable1 the name of the first variable to compare
 * @param variable2 the secound variable to compare to
 * @param szNameVariable2 the name of the secound variable to compare
 * @return the number of elements of the variables which are not equal
 */
int compareVariables( const cFibVariable & variable1, const string & szNameVariable1,
	const cFibVariable & variable2, const string & szNameVariable2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<"Comparing variable "<< szNameVariable1 <<" with variable "<<
		szNameVariable2 <<" : "<<endl;
	
	//compare the values
	if ( variable1.getValue() != variable2.getValue() ){
		cerr<<"Error: The value of the variable "<< szNameVariable1 <<
			"  is "<< variable1.getValue() <<" but of variable "<<
			szNameVariable2 <<" it is "<< variable2.getValue() <<" ."<<endl;
		iReturn++;
	}
	//compare the variables are set
	if ( variable1.isSet() != variable2.isSet() ){
		cerr<<"Error: The the variable "<< szNameVariable1 <<
			"  is "<< ((variable1.isSet())?"set":"not set") <<" but variable "<<
			szNameVariable2 <<" is "<< ((variable2.isSet())?"set":"not set")
			<<" ."<<endl;
		iReturn++;
	}
	//compare the variables are integer values
	if ( variable1.isIntegerValue() != variable2.isIntegerValue() ){
		cerr<<"Error: The the variable "<< szNameVariable1 <<
			"  is "<< ((variable1.isIntegerValue())?"an integer value":"not an integer value")
			<<" but variable "<< szNameVariable2 <<" is "<<
			((variable1.isIntegerValue())?"an integer value":"not an integer value")
			<<" ."<<endl;
		iReturn++;
	}
	//compare the definingelements
	if ( variable1.getDefiningElement() != variable2.getDefiningElement() ){
		cerr<<"Error: The definingelement of the variable "<< szNameVariable1 <<
			"  is "<< variable1.getDefiningElement() <<" but of variable "<<
			szNameVariable2 <<" it is "<< variable2.getDefiningElement() <<" ."<<endl;
		iReturn++;
	}
/*TODO weg;
	//compare the number of using elements
	if ( variable1.getNumberOfUsingElements() == variable2.getNumberOfUsingElements() ){
		//compare the using elements
		set<cFibElement*> setUsingElements1 = variable1.getUsingElements();
		set<cFibElement*> setUsingElements2 = variable2.getUsingElements();
		
		if ( setUsingElements1 != setUsingElements2 ){
			
			cerr<<"Error: The using elements of the variables are not equal."<<endl;
			iReturn++;
		}
	
	}else{
		cerr<<"Error: The number of using elements of the variable "<< szNameVariable1 <<
			"  is "<< variable1.getNumberOfUsingElements() <<" but of variable "<<
			szNameVariable2 <<" it is "<< variable2.getNumberOfUsingElements() <<" ."<<endl;
		iReturn++;
	}
*/
	if ( iReturn == 0 ){
	
		cout<<"The variable "<< szNameVariable1 <<" is equal with variable "<<
			szNameVariable2 <<" . "<<endl;
	}else{
		cerr<<"Error: The variable "<< szNameVariable1 <<" is not equal with variable "<<
			szNameVariable2 <<" . "<<endl;
	}
	
	return iReturn;
}


/**
 * This method tests the copyconstructor of the cFibVariable class.
 *
 * methods tested:
 * 	- cFibVariable( const cFibVariable & variable );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopyConstructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a new variable"<<endl;

	//TODO adapt root -constructor use other Fib -elements
	cRoot * definingRoot= new cRoot();

	cout<<"cFibVariable fibVariable1( masterRoot );"<<endl;
	cFibVariable fibVariable1( (cFibElement*)definingRoot );
	
	cout<<"cFibVariable fibVariable1Copy( fibVariable1 );"<<endl;
	cFibVariable fibVariable1Copy( fibVariable1 );

	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable1Copy, "fibVariable1Copy" );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a variable with using elements"<<endl;

	//TODO adapt: use other Fib -elements
	cVectorProperty usingElement1( 1 );
	cVectorProperty usingElement2( 2 );
	cVectorProperty usingElement3( 3 );

	cout<<"fibVariable1.registerUsingElement( usingElement1 );"<<endl;
	fibVariable1.registerUsingElement( &usingElement1 );
	
	cout<<"cFibVariable fibVariable1Copy2( fibVariable1 );"<<endl;
	cFibVariable fibVariable1Copy2( fibVariable1 );

	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable1Copy2, "fibVariable1Copy2" );
	
	if ( fibVariable1Copy2.getNumberOfUsingElements() != 0 ){
		cerr<<"Error: The value of the variable fibVariable1Copy2 " <<
			"  has some using elements."<<endl;
		iReturn++;
	}

	cout<<"fibVariable1.registerUsingElement( &usingElement2 );"<<endl;
	fibVariable1.registerUsingElement( &usingElement2 );
	cout<<"fibVariable1.registerUsingElement( &usingElement3 );"<<endl;
	fibVariable1.registerUsingElement( &usingElement3 );
	
	cout<<"cFibVariable fibVariable1Copy3( fibVariable1 );"<<endl;
	cFibVariable fibVariable1Copy3( fibVariable1 );

	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable1Copy3, "fibVariable1Copy3" );
	if ( fibVariable1Copy3.getNumberOfUsingElements() != 0 ){
		cerr<<"Error: The value of the variable fibVariable1Copy3 " <<
			"  has some using elements."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a variable with a value set"<<endl;

	cout<<"fibVariable1.setValue( 1.1 );"<<endl;
	fibVariable1.setValue( 1.1 );

	cout<<"cFibVariable fibVariable1CopyV1( fibVariable1 );"<<endl;
	cFibVariable fibVariable1CopyV1( fibVariable1 );

	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable1CopyV1, "fibVariable1CopyV1" );

	cout<<"fibVariable1.setValue( -32.6544 );"<<endl;
	fibVariable1.setValue( -32.6544 );

	cout<<"cFibVariable fibVariable1CopyV2( fibVariable1 );"<<endl;
	cFibVariable fibVariable1CopyV2( fibVariable1 );

	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable1CopyV2, "fibVariable1CopyV2" );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a variable with a integer value set"<<endl;

	cout<<"fibVariable1.setIntegerValue( 24 );"<<endl;
	fibVariable1.setIntegerValue( 24 );

	cout<<"cFibVariable fibVariable1CopyIv1( fibVariable1 );"<<endl;
	cFibVariable fibVariable1CopyIv1( fibVariable1 );

	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable1CopyIv1, "fibVariable1CopyIv1" );

	cout<<"fibVariable1.setIntegerValue( -1245 );"<<endl;
	fibVariable1.setIntegerValue( -1245 );

	cout<<"cFibVariable fibVariable1CopyIv2( fibVariable1 );"<<endl;
	cFibVariable fibVariable1CopyIv2( fibVariable1 );

	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable1CopyIv2, "fibVariable1CopyIv2" );
	
	delete definingRoot;
	
	return iReturn;
}



/**
 * This method tests the operator = of the cFibVariable class.
 *
 * methods tested:
 * 	- cFibVariable & operator=( const cFibVariable &variable );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testAssignment( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing assignment of a new variable"<<endl;

	//TODO adapt root -constructor use other Fib -elements
	cRoot * definingRoot= new cRoot();
	cRoot * definingRoot2= new cRoot();

	cout<<"cFibVariable fibVariable1( masterRoot );"<<endl;
	cFibVariable fibVariable1( (cFibElement*)definingRoot );
	
	cout<<"cFibVariable fibVariable1Copy( definingRoot2 );"<<endl;
	cFibVariable fibVariable1Copy( definingRoot2 );
	
	cout<<"fibVariable1Copy = fibVariable1;"<<endl;
	fibVariable1Copy = fibVariable1;
	
	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable1Copy, "fibVariable1Copy" );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing assignment of a variable with using elements"<<endl;

	//TODO adapt: use other Fib -elements
	cVectorProperty usingElement1( 1 );
	cVectorProperty usingElement2( 2 );
	cVectorProperty usingElement3( 3 );

	cout<<"fibVariable1.registerUsingElement( &usingElement1 );"<<endl;
	fibVariable1.registerUsingElement( &usingElement1 );
	
	cout<<"cFibVariable fibVariable1Copy2( definingRoot2 );"<<endl;
	cFibVariable fibVariable1Copy2( definingRoot2 );
	
	cout<<"fibVariable1Copy2 = fibVariable1;"<<endl;
	fibVariable1Copy2 = fibVariable1;

	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable1Copy2, "fibVariable1Copy2" );

	cout<<"fibVariable1.registerUsingElement( &usingElement2 );"<<endl;
	fibVariable1.registerUsingElement( &usingElement2 );
	cout<<"fibVariable1.registerUsingElement( &usingElement3 );"<<endl;
	fibVariable1.registerUsingElement( &usingElement3 );
	
	cout<<"cFibVariable fibVariable1Copy3( definingRoot2 );"<<endl;
	cFibVariable fibVariable1Copy3( definingRoot2 );
	
	cout<<"fibVariable1Copy3 = fibVariable1;"<<endl;
	fibVariable1Copy3 = fibVariable1;

	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable1Copy3, "fibVariable1Copy3" );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing assignment of a variable with a value set"<<endl;

	cout<<"fibVariable1.setValue( 1.1 );"<<endl;
	fibVariable1.setValue( 1.1 );

	cout<<"cFibVariable fibVariable1CopyV1( definingRoot2 );"<<endl;
	cFibVariable fibVariable1CopyV1( definingRoot2 );
	
	cout<<"fibVariable1CopyV1 = fibVariable1;"<<endl;
	fibVariable1CopyV1 = fibVariable1;

	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable1CopyV1, "fibVariable1CopyV1" );

	cout<<"fibVariable1.setValue( -32.6544 );"<<endl;
	fibVariable1.setValue( -32.6544 );

	cout<<"cFibVariable fibVariable1CopyV2( definingRoot2 );"<<endl;
	cFibVariable fibVariable1CopyV2( definingRoot2 );
	
	cout<<"fibVariable1CopyV2 = fibVariable1;"<<endl;
	fibVariable1CopyV2 = fibVariable1;

	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable1CopyV2, "fibVariable1CopyV2" );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing assignment of a variable with a integer value set"<<endl;

	cout<<"fibVariable1.setIntegerValue( 24 );"<<endl;
	fibVariable1.setIntegerValue( 24 );

	cout<<"cFibVariable fibVariable1CopyIv1( definingRoot2 );"<<endl;
	cFibVariable fibVariable1CopyIv1( definingRoot2 );
	
	cout<<"fibVariable1CopyIv1 = fibVariable1;"<<endl;
	fibVariable1CopyIv1 = fibVariable1;

	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable1CopyIv1, "fibVariable1CopyIv1" );

	cout<<"fibVariable1.setIntegerValue( -1245 );"<<endl;
	fibVariable1.setIntegerValue( -1245 );

	cout<<"cFibVariable fibVariable1CopyIv2( definingRoot2 );"<<endl;
	cFibVariable fibVariable1CopyIv2( definingRoot2 );
	
	cout<<"fibVariable1CopyIv2 = fibVariable1;"<<endl;
	fibVariable1CopyIv2 = fibVariable1;

	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable1CopyIv2, "fibVariable1CopyIv2" );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing assignment of a variable to an variable wich is not new"<<endl;


	cout<<"fibVariable1.unregisterUsingElement( &usingElement2 );"<<endl;
	fibVariable1.unregisterUsingElement( &usingElement2 );

	cout<<"cFibVariable fibVariable2( definingRoot2 );"<<endl;
	cFibVariable fibVariable2( definingRoot2 );

	cout<<"fibVariable2.registerUsingElement( &usingElement2 );"<<endl;
	fibVariable2.registerUsingElement( &usingElement2 );
	cout<<"fibVariable2.registerUsingElement( &usingElement1 );"<<endl;
	fibVariable2.registerUsingElement( &usingElement1 );
	cout<<"fibVariable2.registerUsingElement( &usingElement3 );"<<endl;
	fibVariable2.registerUsingElement( &usingElement3 );
	
	cout<<"fibVariable2.setValue( -32.6544 );"<<endl;
	fibVariable2.setValue( -32.6544 );
	
	cout<<"fibVariable2 = fibVariable1;"<<endl;
	fibVariable2 = fibVariable1;
	
	iReturn += compareVariables( fibVariable1, "fibVariable1",
		fibVariable2, "fibVariable2" );
	
	delete definingRoot;
	delete definingRoot2;
	
	return iReturn;
}



/**
 * This method tests the equal() method and the operator== of two given
 * cFibVariable objects which are equal.
 *
 * @param variable1 the first variable to compare
 * @param szNameVariabler1 the name of the first variable to compare
 * @param variable2 the secound variable to compare to
 * @param szNameVariabler2 the name of the secound variable to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualVariables( const cFibVariable & variable1, const string & szNameVariabler1,
	const cFibVariable & variable2, const string & szNameVariabler2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( variable1.equal( variable2 ) ){
	
		cout<<"The "<<szNameVariabler1<<" is equal to "<<szNameVariabler2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVariabler1<<" is not equal to "<<
			szNameVariabler2<<"."<<endl;
		iReturn++;
	}
	if ( variable1 == variable2 ){
	
		cout<<"The "<<szNameVariabler1<<" is equal (operator==) to "<<
			szNameVariabler2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVariabler1<<" is not equal (operator==) to "<<
			szNameVariabler2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}

/**
 * This method tests the equal() method and the operator== of two given
 * cFibVariable objects which are not equal.
 *
 * @param variable1 the first variable to compare
 * @param szNameVariabler1 the name of the first variable to compare
 * @param variable2 the secound variable to compare to
 * @param szNameVariabler2 the name of the secound variable to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualVariables( const cFibVariable & variable1, const string & szNameVariabler1,
	const cFibVariable & variable2, const string & szNameVariabler2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! variable1.equal( variable2 ) ){
	
		cout<<"The "<<szNameVariabler1<<" is not equal to "<<szNameVariabler2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVariabler1<<" is equal to "<<
			szNameVariabler2<<"."<<endl;
		iReturn++;
	}
	if ( ! (variable1 == variable2) ){
	
		cout<<"The "<<szNameVariabler1<<" is not equal (operator==) to "<<
			szNameVariabler2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameVariabler1<<" is equal (operator==) to "<<
			szNameVariabler2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the equal() method and the operator== of the class.
 *
 * methods tested:
 * 	- bool equal( const cFibVariable &variable ) const;
 * 	- bool operator==( const cFibVariable &variable ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testEqual( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equal method and the operator== "<<endl;

	cout<<endl<<"creating variables to compare:"<<endl<<endl;
	
	cout<<"cRoot root1;"<<endl;
	cRoot root1;
	
	//creat defined variables to set them later in the vector
	cout<<"root1.setNumberOfInputVariables( 4 )"<<endl;
	root1.setNumberOfInputVariables( 4 );

	cout<<"cRoot root2;"<<flush<<endl;
	cRoot root2;
	
	cout<<"root2.setNumberOfInputVariables( 3 )"<<endl;
	root2.setNumberOfInputVariables( 3 );

	//TODO adapt: use other Fib -elements
	cVectorProperty usingElement1( 1 );
	cVectorProperty usingElement2( 2 );
	
	cout<<"cFibVariable fibVariableNull1( NULL );"<<endl;
	cFibVariable fibVariableNull1( NULL );
	
	cout<<"cFibVariable fibVariableNull2( NULL );"<<endl;
	cFibVariable fibVariableNull2( NULL );

	cout<<"pVariable1Root1 = root1.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1Root1 = root1.getInputVariable( 1 );
	cout<<"pVariable2Root1 = root1.getInputVariable( 2 );"<<endl;
	
	cFibVariable * pVariable2Root1 = root1.getInputVariable( 2 );
	cout<<"pVariable2Root1.registerUsingElement( &usingElement1 );"<<endl;
	pVariable2Root1->registerUsingElement( &usingElement1 );
	cout<<"pVariable2Root1->registerUsingElement( &usingElement2 );"<<endl;
	pVariable2Root1->registerUsingElement( &usingElement2 );

	cout<<"pVariable3Root1 = root1.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3Root1 = root1.getInputVariable( 3 );
	cout<<"pVariable3Root1->setValue( 1.1 );"<<endl;
	pVariable3Root1->setValue( 1.1 );
	
	cout<<"pVariable4Root1 = root1.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable4Root1 = root1.getInputVariable( 4 );
	cout<<"pVariable4Root1->registerUsingElement( &usingElement1 );"<<endl;
	pVariable4Root1->registerUsingElement( &usingElement1 );
	cout<<"pVariable4Root1->registerUsingElement( &usingElement2 );"<<endl;
	pVariable4Root1->registerUsingElement( &usingElement2 );
	cout<<"pVariable4Root1->setIntegerValue( 1.1 );"<<endl;
	pVariable4Root1->setIntegerValue( 1.1 );

	cout<<"pVariable1Root2 = root2.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1Root2 = root2.getInputVariable( 1 );
	
	cout<<"pVariable2Root2 = root2.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2Root2 = root2.getInputVariable( 2 );
	cout<<"pVariable2Root2->setIntegerValue( 1.1 );"<<endl;
	pVariable2Root2->setIntegerValue( 1.1 );

	cout<<"pVariable3Root2 = root2.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3Root2 = root2.getInputVariable( 3 );
	cout<<"pVariable3Root2->registerUsingElement( &usingElement1 );"<<endl;
	pVariable3Root2->registerUsingElement( &usingElement1 );
	cout<<"pVariable3Root2->registerUsingElement( &usingElement2 );"<<endl;
	pVariable3Root2->registerUsingElement( &usingElement2 );
	cout<<"pVariable3Root2->setValue( 1.1 );"<<endl;
	pVariable3Root2->setValue( 1.1 );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;
	
	cFibVariable * actualVariable = &fibVariableNull1;
	string szActualVariableName = "fibVariableNull1";
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, fibVariableNull1, "fibVariableNull1" );
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, fibVariableNull2, "fibVariableNull2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root1, "pVariable1Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root1, "pVariable2Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root1, "pVariable3Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable4Root1, "pVariable4Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root2, "pVariable1Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root2, "pVariable2Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root2, "pVariable3Root2" );

	actualVariable = &fibVariableNull2;
	szActualVariableName = "fibVariableNull2";
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, fibVariableNull1, "fibVariableNull1" );
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, fibVariableNull2, "fibVariableNull2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root1, "pVariable1Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root1, "pVariable2Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root1, "pVariable3Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable4Root1, "pVariable4Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root2, "pVariable1Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root2, "pVariable2Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root2, "pVariable3Root2" );

	actualVariable = pVariable1Root2;
	szActualVariableName = "pVariable1Root2";
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, fibVariableNull1, "fibVariableNull1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, fibVariableNull2, "fibVariableNull2" );
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root1, "pVariable1Root1" );
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root2, "pVariable1Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root1, "pVariable2Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root2, "pVariable2Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root2, "pVariable3Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root1, "pVariable3Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable4Root1, "pVariable4Root1" );

	actualVariable = pVariable2Root1;
	szActualVariableName = "pVariable2Root1";
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, fibVariableNull1, "fibVariableNull1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, fibVariableNull2, "fibVariableNull2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root1, "pVariable1Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root2, "pVariable1Root2" );
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root1, "pVariable2Root1" );
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root2, "pVariable2Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root2, "pVariable3Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root1, "pVariable3Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable4Root1, "pVariable4Root1" );

	actualVariable = pVariable2Root2;
	szActualVariableName = "pVariable2Root2";
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, fibVariableNull1, "fibVariableNull1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, fibVariableNull2, "fibVariableNull2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root1, "pVariable1Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root2, "pVariable1Root2" );
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root1, "pVariable2Root1" );
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root2, "pVariable2Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root2, "pVariable3Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root1, "pVariable3Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable4Root1, "pVariable4Root1" );

	actualVariable = pVariable3Root1;
	szActualVariableName = "pVariable3Root1";
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, fibVariableNull1, "fibVariableNull1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, fibVariableNull2, "fibVariableNull2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root1, "pVariable1Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root2, "pVariable1Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root1, "pVariable2Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root2, "pVariable2Root2" );
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root1, "pVariable3Root1" );
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root2, "pVariable3Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable4Root1, "pVariable4Root1" );

	actualVariable = pVariable3Root2;
	szActualVariableName = "pVariable3Root2";
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, fibVariableNull1, "fibVariableNull1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, fibVariableNull2, "fibVariableNull2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root1, "pVariable1Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root2, "pVariable1Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root1, "pVariable2Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root2, "pVariable2Root2" );
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root1, "pVariable3Root1" );
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root2, "pVariable3Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable4Root1, "pVariable4Root1" );

	actualVariable = pVariable4Root1;
	szActualVariableName = "pVariable4Root1";
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, fibVariableNull1, "fibVariableNull1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, fibVariableNull2, "fibVariableNull2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root1, "pVariable1Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable1Root2, "pVariable1Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root1, "pVariable2Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable2Root2, "pVariable2Root2" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root1, "pVariable3Root1" );
	iReturn += testCompareTwoNotEqualVariables( *actualVariable, szActualVariableName, *pVariable3Root2, "pVariable3Root2" );
	iReturn += testCompareTwoEqualVariables( *actualVariable, szActualVariableName, *pVariable4Root1, "pVariable4Root1" );

	
	return iReturn;
}





/**
 * This method tests if a variable and vector registerhandling of the
 * vector as a using element works correct.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testRegisterVector( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing registerhandling of the vector as a using element"<<endl;
	
	cVectorPosition * pVectorPosition;
	
	cFibVariable * pVariable;
	
	cout<<"pVectorPosition = new cVectorPosition( 3 ); "<<endl;
	pVectorPosition = new cVectorPosition( 3 );
	
	cout<<"pVariable = new cFibVariable( NULL ); "<<endl;
	pVariable = new cFibVariable( NULL );
	
	
	if ( pVariable->setUsingElements.empty() ){
	
		cout<<"The variable is correctly not used."<<endl;
	}else{
		cerr<<"Error: The variable is used "<<
			pVariable->setUsingElements.size() <<" times."<<endl;
		iReturn++;
	}

	cout<<"pVectorPosition->setVariable( 1, pVariable ); "<<endl;
	pVectorPosition->setVariable( 1, pVariable );

	if ( pVariable->setUsingElements.size() ){
	
		cout<<"The variable is correctly used by one element."<<endl;
	}else{
		cerr<<"Error: The variable is used by "<<
			pVariable->setUsingElements.size() <<" elements."<<endl;
		iReturn++;
	}
	if ( pVariable->setUsingElements.find( pVectorPosition ) !=
			pVariable->setUsingElements.end() ){
	
		cout<<"The variable is correctly used by pVectorPosition."<<endl;
	}else{
		cerr<<"Error: The variable is used."<<endl;
		iReturn++;
	}
	cout<<"delete pVectorPosition; "<<endl;
	delete pVectorPosition;

	if ( pVariable->setUsingElements.empty() ){
	
		cout<<"The variable is correctly not used."<<endl;
	}else{
		cerr<<"Error: The variable is used "<<
			pVariable->setUsingElements.size() <<" times."<<endl;
		iReturn++;
	}
	
	cout<<"pVectorPosition = new cVectorPosition( 3 ); "<<endl;
	pVectorPosition = new cVectorPosition( 3 );

	cout<<"pVectorPosition->setVariable( 1, pVariable ); "<<endl;
	pVectorPosition->setVariable( 1, pVariable );

	if ( pVariable->setUsingElements.size() == 1 ){
	
		cout<<"The variable is correctly used by one element."<<endl;
	}else{
		cerr<<"Error: The variable is used by "<<
			pVariable->setUsingElements.size() <<" elements."<<endl;
		iReturn++;
	}
	if ( pVariable->setUsingElements.find( pVectorPosition ) !=
			pVariable->setUsingElements.end() ){
	
		cout<<"The variable is correctly used by pVectorPosition."<<endl;
	}else{
		cerr<<"Error: The variable is used."<<endl;
		iReturn++;
	}
	cout<<"delete pVariable; "<<endl;
	delete pVariable;
	
	set<cFibVariable*> setUsedVariables = pVectorPosition->getUsedVariables();
	if ( setUsedVariables.size() == 0 ){
	
		cout<<"The variable is correctly not used by the vector."<<endl;
	}else{
		cerr<<"Error: The vector uses "<< setUsedVariables.size() <<" variables."<<endl;
		iReturn++;
	}

	cout<<"pVariable = new cFibVariable( NULL ); "<<endl;
	pVariable = new cFibVariable( NULL );

	cout<<"pVectorPosition->setVariable( 1, pVariable ); "<<endl;
	pVectorPosition->setVariable( 1, pVariable );
	
	cout<<"pair< cVectorPosition, int > paTestPair = make_pair( *pVectorPosition, 0 ); "<<endl;
	pair< cVectorPosition, int > paTestPair = make_pair( *pVectorPosition, 0 );

	if ( pVariable->setUsingElements.size() == 2 ){
	
		cout<<"The variable is correctly used by one element."<<endl;
	}else{
		cerr<<"Error: The variable is used by "<<
			pVariable->setUsingElements.size() <<" elements."<<endl;
		iReturn++;
	}

	cout<<"delete pVariable; "<<endl;
	delete pVariable;

	cout<<"delete pVectorPosition; "<<endl;
	delete pVectorPosition;


	return iReturn;
}
















