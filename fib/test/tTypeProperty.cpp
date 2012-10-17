/**
 * @file tTypeProperty
 * file name: tTypeProperty.cpp
 * @author Betti Oesterholz
 * @date 24.07.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cTypeProperty.
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
 * This file contains the test for the class cTypeProperty,
 * which represents the type for propertyvectors.
 *
 *
 *
 *  What's tested of class tTypeProperty:
 * 	- TypeProperty( unsignedIntFib uiPropertyType, unsignedIntFib uiNumberOfDimensions=2 )
 * 	- cTypeProperty( const cTypeProperty &typeProperty )
 * 	-(TODO) cTypeProperty( const cTypeProperty &typeProperty, const cDomain & domain )
 * 	- unsignedIntFib getType() const
 * 	- bool isCompatible( const cDomain &domain ) const
 * 	- cDomain *getStandardDomain( ) const
 * 	- bool equal( const cTypeElement &typeElement ) const
 * 	- bool operator==( const cTypeElement &typeElement ) const
 * 	- cTypeElement *clone() const
 * 	- unsignedIntFib getNumberOfProperty() const
 * 	- vector<string> getUnit() const
 * 	- string getNameOfProperty() const 
 * 	- bool equalElementType( const cTypeElement & typeElement ) const
 * 	- bool storeXml( ostream & ostream, const cDomain * domain = NULL ) const
 * 	- unsignedLongFib getCompressedSize() const
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const
 * 	- list<cTypeProperty> getOverwritenTyps() const
 * 	- bool isEvalued() const
 *
 */
/*
History:
04.06.2009  Oesterholz  created
11.11.2009  Oesterholz  getNameOfProperty, store*(), getCompressedSize()
	and equalElementType() tested
15.12.2009  Oesterholz  getOverwritenTyps() and isEvalued() tested
13.05.2010  Oesterholz  the ordering of bits for the compressed storing corrected
04.04.2011  Oesterholz  storing to binary stream
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

//TODO check isCompatible() for more domains + comparrisson
/*TODO check diffenrent standart Typs:

	-SOUND_AMPLITUDE = 305;

*/

#include "version.h"

#include "cTypeProperty.h"
#include "cTypeDimension.h"
#include "cTypeInVar.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <iomanip>
#include <algorithm>


#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif

using namespace fib;
using namespace std;


int testConstructor( unsigned long &ulTestphase );
int testCloneAndEqual( unsigned long &ulTestphase );

int testPropertyNon( unsigned long &ulTestphase );
int testPropertyColorRGB( unsigned long &ulTestphase );
int testPropertyColorSW( unsigned long &ulTestphase );
int testPropertyLayer( unsigned long &ulTestphase );
int testPropertyTransparency( unsigned long &ulTestphase );
int testPropertySound( unsigned long &ulTestphase );
int testPropertySoundPolarizedStandard2D( unsigned long &ulTestphase );
int testPropertySoundPolarizedStandard3D( unsigned long &ulTestphase );
int testPropertySoundBarrier( unsigned long &ulTestphase );
int testPropertySoundReflected( unsigned long &ulTestphase );
int testPropertySoundDamping( unsigned long &ulTestphase );
int testPropertyKelvin( unsigned long &ulTestphase );
int testPropertyElectromagnetic2D( unsigned long &ulTestphase );
int testPropertyElectromagnetic4D( unsigned long &ulTestphase );

int testPropertyChecksum( unsigned long &ulTestphase );

int testEqualElementType( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );



int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cTypeProperty methods"<<endl;
	cout<<      "======================================"<<endl;

	iReturn += testConstructor( ulTestphase );
	iReturn += testCloneAndEqual( ulTestphase );

	//test the property typs
	iReturn += testPropertyNon( ulTestphase );
	iReturn += testPropertyColorRGB( ulTestphase );
	iReturn += testPropertyColorSW( ulTestphase );
	iReturn += testPropertyLayer( ulTestphase );
	iReturn += testPropertyTransparency( ulTestphase );
	iReturn += testPropertySound( ulTestphase );
	iReturn += testPropertySoundPolarizedStandard2D( ulTestphase );
	iReturn += testPropertySoundPolarizedStandard3D( ulTestphase );
	iReturn += testPropertySoundBarrier( ulTestphase );
	iReturn += testPropertySoundReflected( ulTestphase );
	iReturn += testPropertySoundDamping( ulTestphase );
	iReturn += testPropertyKelvin( ulTestphase );
	iReturn += testPropertyElectromagnetic2D( ulTestphase );
	iReturn += testPropertyElectromagnetic4D( ulTestphase );
	iReturn += testPropertyChecksum( ulTestphase );
	
	iReturn += testEqualElementType( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the constructor of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testConstructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a simple property of type 1"<<endl;
	
	cTypeProperty testTypeProperty1( 1 );
	
	//check the getType() methode
	if ( testTypeProperty1.getType()==6 ){
	
		cout<<"The correct type 6 for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not 6 for \"cTypeProperty\"; it is : "<<
			testTypeProperty1.getType()<<endl;
		iReturn++;
	}

	vector<cDomainSingle*> vecDomains( 3 );
	vecDomains[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains[ 1 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains[ 2 ] = new cDomainNaturalNumberBit( 8 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( testTypeProperty1.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains[ 0 ];
	delete vecDomains[ 1 ];
	delete vecDomains[ 2 ];
	delete vectorDomain;
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty1.getNumberOfProperty()==1 ){
	
		cout<<"The correct number 1 for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The number given is not 1 for \"cTypeProperty\"; it is : "<<
			testTypeProperty1.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty1.getNameOfProperty() == "colorRGB" ){
	
		cout<<"The correct name \"colorRGB\" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \"colorRGB\" for \"cTypeProperty\"; it is : "<<
			testTypeProperty1.getNameOfProperty()<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a simple property of type transparency"<<endl;
	
	cTypeProperty testTypePropertyTransparency( cTypeProperty::TRANSPARENCY );
	
	//check the getType() methode
	if ( testTypePropertyTransparency.getType()==6 ){
	
		cout<<"The correct type 6 for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not 6 for \"cTypeProperty\"; it is : "<<
			testTypePropertyTransparency.getType()<<endl;
		iReturn++;
	}
	
	//check the getNumberOfProperty() methode
	if ( testTypePropertyTransparency.getNumberOfProperty()==cTypeProperty::TRANSPARENCY ){
	
		cout<<"The correct typenumber TRANSPARENCY for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not TRANSPARENCY for \"cTypeProperty\"; it is : "<<
			testTypePropertyTransparency.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypePropertyTransparency.getNameOfProperty() == "transparency" ){
	
		cout<<"The correct name \"transparency\" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \"transparency\" for \"cTypeProperty\"; it is : "<<
			testTypePropertyTransparency.getNameOfProperty()<<endl;
		iReturn++;
	}

	vector<cDomainSingle*> vecDomains1Nat( 1 );
	vecDomains1Nat[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1Nat );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( testTypePropertyTransparency.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1Nat[ 0 ];
	delete vectorDomain;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying the property of type 1"<<endl;
	
	cTypeProperty testTypePropertyCopy1( testTypeProperty1 );
	
	//check the getType() methode
	if ( testTypePropertyCopy1.getType()==6 ){
	
		cout<<"The correct type 6 for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not 6 for \"cTypeProperty\"; it is : "<<
			testTypePropertyCopy1.getType()<<endl;
		iReturn++;
	}
	
	//check the getType() methode
	if ( testTypePropertyCopy1.getNumberOfProperty()==1 ){
	
		cout<<"The correct number 1 for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The number given is not 1 for \"cTypeProperty\"; it is : "<<
			testTypePropertyCopy1.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypePropertyCopy1.getNameOfProperty() == "colorRGB" ){
	
		cout<<"The correct name \"colorRGB\" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \"colorRGB\" for \"cTypeProperty\"; it is : "<<
			testTypePropertyCopy1.getNameOfProperty()<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying the property of type transparency"<<endl;
	
	cTypeProperty testTypePropertyCopyTransparency( testTypePropertyTransparency );

	//check the getType() methode
	if ( testTypePropertyCopyTransparency.getType()==6 ){
	
		cout<<"The correct type 6 for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not 6 for \"cTypeProperty\"; it is : "<<
			testTypePropertyCopyTransparency.getType()<<endl;
		iReturn++;
	}
	
	//check the getNumberOfProperty() methode
	if ( testTypePropertyCopyTransparency.getNumberOfProperty()==cTypeProperty::TRANSPARENCY ){
	
		cout<<"The correct typenumber TRANSPARENCY for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not TRANSPARENCY for \"cTypeProperty\"; it is : "<<
			testTypePropertyCopyTransparency.getNumberOfProperty()<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a simple property of type 2003"<<endl;
	
	cTypeProperty testTypeProperty2003( 2003 );
	
	//check the getType() methode
	if ( testTypeProperty2003.getType()==6 ){
	
		cout<<"The correct type 6 for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The type given is not 6 for \"cTypeProperty\"; it is : "<<
			testTypeProperty2003.getType()<<endl;
		iReturn++;
	}

	vecDomains[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains[ 1 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains );
	delete vecDomains[ 0 ];
	delete vecDomains[ 1 ];
	delete vecDomains[ 2 ];
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( testTypeProperty2003.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;
	
	vector<cDomainSingle*> vecDomainsD1( 1 );
	vecDomainsD1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	cDomainVector vectorDomainD1( vecDomainsD1 );
	delete vecDomainsD1[ 0 ];
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( testTypeProperty2003.isCompatible( vectorDomainD1 ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 1 element. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 1 element."<<endl;
		iReturn++;
	}
	
	cDomainNaturalNumberBit domainNaturalNumberB3( 3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty2003.isCompatible( domainNaturalNumberB3 ) ){
	
		cout<<"The type is correctly not compatible to the cDomainNaturalNumberBit with 3 bit. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the cDomainNaturalNumberBit with 3 bit."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty2003.getNumberOfProperty()==2003 ){
	
		cout<<"The correct number 2003 for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The number given is not 2003 for \"cTypeProperty\"; it is : "<<
			testTypeProperty2003.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty2003.getNameOfProperty() == "2003" ){
	
		cout<<"The correct name \"2003\" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \"2003\" for \"cTypeProperty\"; it is : "<<
			testTypeProperty2003.getNameOfProperty()<<endl;
		iReturn++;
	}


	return iReturn;
}


/**
 * This method tests the equal method and operator and the clone method of
 * the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCloneAndEqual( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cloning a simple property of type COLOR_RGB"<<endl;
	
	cout<<"cTypeProperty testTypeProperty1( cTypeProperty::COLOR_RGB )"<<endl;
	cTypeProperty testTypeProperty1( cTypeProperty::COLOR_RGB );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty1.getNumberOfProperty()==cTypeProperty::COLOR_RGB ){
	
		cout<<"The correct typenumber COLOR_RGB="<<cTypeProperty::COLOR_RGB<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not COLOR_RGB="<<cTypeProperty::COLOR_RGB<<
			" for \"cTypeProperty\"; it is : "<<
			testTypeProperty1.getNumberOfProperty()<<endl;
		iReturn++;
	}

	cout<<"cTypeProperty *testTypePropertyClone1=testTypeProperty1.clone()"<<endl;
	cTypeProperty *testTypePropertyClone1=testTypeProperty1.clone();
	
	//check the getNumberOfProperty() methode
	if ( testTypePropertyClone1->getNumberOfProperty()==cTypeProperty::COLOR_RGB ){
	
		cout<<"The correct typenumber COLOR_RGB="<<cTypeProperty::COLOR_RGB<<
			" for \"cTypeProperty\" clone is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not COLOR_RGB="<<cTypeProperty::COLOR_RGB<<
			" for \"cTypeProperty\" clone; it is : "<<
			testTypePropertyClone1->getNumberOfProperty()<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cloning a simple property of type transparency"<<endl;
	
	cout<<"cTypeProperty testTypePropertyTransparency( cTypeProperty::TRANSPARENCY )"<<endl;
	cTypeProperty testTypePropertyTransparency( cTypeProperty::TRANSPARENCY );
	
	//check the getNumberOfProperty() methode
	if ( testTypePropertyTransparency.getNumberOfProperty()==cTypeProperty::TRANSPARENCY ){
	
		cout<<"The correct typenumber TRANSPARENCY="<<cTypeProperty::TRANSPARENCY<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not TRANSPARENCY="<<cTypeProperty::TRANSPARENCY<<
			" for \"cTypeProperty\"; it is : "<<
			testTypePropertyTransparency.getNumberOfProperty()<<endl;
		iReturn++;
	}

	cout<<"cTypeProperty *testTypePropertyCloneTransparency=testTypePropertyTransparency.clone()"<<endl;
	cTypeProperty *testTypePropertyCloneTransparency=testTypePropertyTransparency.clone();
	
	//check the getNumberOfProperty() methode
	if ( testTypePropertyCloneTransparency->getNumberOfProperty()==cTypeProperty::TRANSPARENCY ){
	
		cout<<"The correct typenumber TRANSPARENCY="<<cTypeProperty::TRANSPARENCY<<
			" for \"cTypeProperty\" clone is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not TRANSPARENCY="<<cTypeProperty::TRANSPARENCY<<
			" for \"cTypeProperty\" clone; it is : "<<
			testTypePropertyCloneTransparency->getNumberOfProperty()<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cloning a simple property of type transparency for 5 dimensions"<<endl;
	
	cout<<"cTypeProperty testTypePropertyTransparencyD5( cTypeProperty::TRANSPARENCY, 5 )"<<endl;
	cTypeProperty testTypePropertyTransparencyD5( cTypeProperty::TRANSPARENCY, 5 );
	
	//check the getNumberOfProperty() methode
	if ( testTypePropertyTransparencyD5.getNumberOfProperty()==cTypeProperty::TRANSPARENCY ){
	
		cout<<"The correct typenumber TRANSPARENCY="<<cTypeProperty::TRANSPARENCY<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not TRANSPARENCY="<<cTypeProperty::TRANSPARENCY<<
			" for \"cTypeProperty\"; it is : "<<
			testTypePropertyTransparencyD5.getNumberOfProperty()<<endl;
		iReturn++;
	}

	cout<<"cTypeProperty *testTypePropertyCloneTransparencyD5=testTypePropertyTransparencyD5.clone()"<<endl;
	cTypeProperty *testTypePropertyCloneTransparencyD5=testTypePropertyTransparencyD5.clone();
	
	//check the getNumberOfProperty() methode
	if ( testTypePropertyCloneTransparencyD5->getNumberOfProperty()==cTypeProperty::TRANSPARENCY ){
	
		cout<<"The correct typenumber TRANSPARENCY="<<cTypeProperty::TRANSPARENCY<<
			" for \"cTypeProperty\" clone is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not TRANSPARENCY="<<cTypeProperty::TRANSPARENCY<<
			" for \"cTypeProperty\" clone; it is : "<<
			testTypePropertyCloneTransparencyD5->getNumberOfProperty()<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing eqal method"<<endl;

	if ( testTypeProperty1.equal( *testTypePropertyClone1 ) ){
	
		cout<<"The testTypeProperty1 and testTypePropertyClone1 are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypeProperty1 and testTypePropertyClone1 are not equal."<<endl;
		iReturn++;
	}

	if ( testTypePropertyClone1->equal( testTypeProperty1 ) ){
	
		cout<<"The testTypePropertyClone1 and testTypeProperty1 are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyClone1 and testTypeProperty1 are not equal."<<endl;
		iReturn++;
	}

	if ( testTypePropertyTransparency.equal( *testTypePropertyCloneTransparency ) ){
	
		cout<<"The testTypePropertyTransparency and testTypePropertyCloneTransparency are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyTransparency and testTypePropertyCloneTransparency are not equal."<<endl;
		iReturn++;
	}

	if ( testTypePropertyCloneTransparency->equal( testTypePropertyTransparency ) ){
	
		cout<<"The testTypePropertyCloneTransparency and testTypePropertyTransparency are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyCloneTransparency and testTypePropertyTransparency are not equal."<<endl;
		iReturn++;
	}

	if ( testTypePropertyTransparencyD5.equal( *testTypePropertyCloneTransparencyD5 ) ){
	
		cout<<"The testTypePropertyTransparencyD5 and testTypePropertyCloneTransparencyD5 are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyTransparencyD5 and testTypePropertyCloneTransparencyD5 are not equal."<<endl;
		iReturn++;
	}

	if ( testTypePropertyCloneTransparencyD5->equal( testTypePropertyTransparencyD5 ) ){
	
		cout<<"The testTypePropertyCloneTransparencyD5 and testTypePropertyTransparencyD5 are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyCloneTransparencyD5 and testTypePropertyTransparencyD5 are not equal."<<endl;
		iReturn++;
	}


	if ( testTypePropertyTransparency.equal( *testTypePropertyCloneTransparencyD5 ) ){
	
		cout<<"The testTypePropertyTransparency and testTypePropertyCloneTransparencyD5 are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyTransparency and testTypePropertyCloneTransparencyD5 are not equal."<<endl;
		iReturn++;
	}

	if ( testTypePropertyTransparency.equal( testTypePropertyTransparencyD5 ) ){
	
		cout<<"The testTypePropertyTransparency and testTypePropertyTransparencyD5 are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyTransparency and testTypePropertyTransparencyD5 are not equal."<<endl;
		iReturn++;
	}


	if ( ! testTypePropertyTransparencyD5.equal( testTypeProperty1 ) ){
	
		cout<<"The testTypePropertyTransparencyD5 and testTypeProperty1 are correctly not equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyTransparencyD5 and testTypeProperty1 are equal."<<endl;
		iReturn++;
	}

	if ( ! testTypePropertyCloneTransparencyD5->equal( testTypeProperty1 ) ){
	
		cout<<"The testTypePropertyCloneTransparencyD5 and testTypeProperty1 are correctly not equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyCloneTransparencyD5 and testTypeProperty1 are equal."<<endl;
		iReturn++;
	}


	if ( ! testTypePropertyTransparency.equal( testTypeProperty1 ) ){
	
		cout<<"The testTypePropertyTransparency and testTypeProperty1 are correctly not equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyTransparency and testTypeProperty1 are equal."<<endl;
		iReturn++;
	}

	if ( ! testTypePropertyTransparency.equal( testTypeProperty1 ) ){
	
		cout<<"The testTypePropertyTransparency and testTypeProperty1 are correctly not equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyTransparency and testTypeProperty1 are equal."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing == operator method"<<endl;

	if ( testTypeProperty1 == (*testTypePropertyClone1) ){
	
		cout<<"The testTypeProperty1 and testTypePropertyClone1 are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypeProperty1 and testTypePropertyClone1 are not equal."<<endl;
		iReturn++;
	}

	if ( (*testTypePropertyClone1) == testTypeProperty1 ){
	
		cout<<"The testTypePropertyClone1 and testTypeProperty1 are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyClone1 and testTypeProperty1 are not equal."<<endl;
		iReturn++;
	}

	if ( testTypePropertyTransparency == (*testTypePropertyCloneTransparency ) ){
	
		cout<<"The testTypePropertyTransparency and testTypePropertyCloneTransparency are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyTransparency and testTypePropertyCloneTransparency are not equal."<<endl;
		iReturn++;
	}

	if ( (*testTypePropertyCloneTransparency) == testTypePropertyTransparency ){
	
		cout<<"The testTypePropertyCloneTransparency and testTypePropertyTransparency are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyCloneTransparency and testTypePropertyTransparency are not equal."<<endl;
		iReturn++;
	}

	if ( testTypePropertyTransparencyD5 == (*testTypePropertyCloneTransparencyD5) ){
	
		cout<<"The testTypePropertyTransparencyD5 and testTypePropertyCloneTransparencyD5 are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyTransparencyD5 and testTypePropertyCloneTransparencyD5 are not equal."<<endl;
		iReturn++;
	}

	if ( (*testTypePropertyCloneTransparencyD5) == testTypePropertyTransparencyD5 ){
	
		cout<<"The testTypePropertyCloneTransparencyD5 and testTypePropertyTransparencyD5 are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyCloneTransparencyD5 and testTypePropertyTransparencyD5 are not equal."<<endl;
		iReturn++;
	}


	if ( testTypePropertyTransparency == (*testTypePropertyCloneTransparencyD5) ){
	
		cout<<"The testTypePropertyTransparency and testTypePropertyCloneTransparencyD5 are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyTransparency and testTypePropertyCloneTransparencyD5 are not equal."<<endl;
		iReturn++;
	}

	if ( testTypePropertyTransparency == testTypePropertyTransparencyD5 ){
	
		cout<<"The testTypePropertyTransparency and testTypePropertyTransparencyD5 are correctly equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyTransparency and testTypePropertyTransparencyD5 are not equal."<<endl;
		iReturn++;
	}


	if ( ! ( testTypePropertyTransparencyD5 == testTypeProperty1 ) ){
	
		cout<<"The testTypePropertyTransparencyD5 and testTypeProperty1 are correctly not equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyTransparencyD5 and testTypeProperty1 are equal."<<endl;
		iReturn++;
	}

	if ( ! ( (*testTypePropertyCloneTransparencyD5) == testTypeProperty1 ) ){
	
		cout<<"The testTypePropertyCloneTransparencyD5 and testTypeProperty1 are correctly not equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyCloneTransparencyD5 and testTypeProperty1 are equal."<<endl;
		iReturn++;
	}


	if ( ! ( testTypePropertyTransparency == testTypeProperty1 ) ){
	
		cout<<"The testTypePropertyTransparency and testTypeProperty1 are correctly not equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyTransparency and testTypeProperty1 are equal."<<endl;
		iReturn++;
	}

	if ( ! ( testTypePropertyTransparency == testTypeProperty1 ) ){
	
		cout<<"The testTypePropertyTransparency and testTypeProperty1 are correctly not equal."<<endl;
	}else{
		cerr<<"Error: The testTypePropertyTransparency and testTypeProperty1 are equal."<<endl;
		iReturn++;
	}
	delete testTypePropertyClone1;
	delete testTypePropertyCloneTransparencyD5;
	delete testTypePropertyCloneTransparency;


	return iReturn;
}



/**
 * This method tests the property 0 for non of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertyNon( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type 0"<<endl;
	
	unsignedIntFib uiPropertyNumber = 0;
	string szPropertyName = "keine";
	
	cout<<"cTypeProperty testTypeProperty( "<< uiPropertyNumber <<" );"<<endl;
	cTypeProperty testTypeProperty( uiPropertyNumber );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == "none" ){
	
		cout<<"The correct name \"none\" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \"none\" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	
	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	}else if ( standardDomain->getType() == "DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector = (cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements = 1;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				if ( (domainNaturalNumberBit->getMinimum()==0) &&
						(domainNaturalNumberBit->getMaximum()==65535) ){
				
					cout<<"The domain goes correctly from 0 to 65535. "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from 0 to 65535, but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size() == 1 ){

		if ( vecUnits[0]=="" ){
		
			cout<<"The unit of the first vector domain is correctly empty. "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be empty."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The the number of vectorelements is not 1 but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;
	}
	
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	if ( liOverwirttenTyps.empty() ){

		cout<<"The property of this type correctly dosn't overwrite any other properties."<<endl;
	}else{
		cerr<<"Error: The property of this type overwrites "<< liOverwirttenTyps.size()<<" other properties."<<endl;
		iReturn++;
	}
	//test isEvalued()
	if ( ! testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly not evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	
	cout<<endl<<"Testing a property of type cTypeProperty() copyconstructor with a given domain"<<endl;
	
	cDomainNaturalNumberBit domainInt2( 8 );
	cout<<"cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );"<<endl;
	cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );
	
	if ( typePropertyDomainInt == testTypeProperty ){
	
		cout<<"The typePropertyDomainInt and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainInt and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1 );
	cout<<"cTypeProperty typePropertyDomain1( testTypeProperty, vectorDomainD1 );"<<endl;
	cTypeProperty typePropertyDomain1( testTypeProperty, *vectorDomain );
	delete vecDomains1[ 0 ];
	delete vectorDomain;

	if ( typePropertyDomain1 == testTypeProperty ){
	
		cout<<"The typePropertyDomain1 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomain1 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 4 );
	vectorDomain = new cDomainVector( vecDomains4 );
	cout<<"cTypeProperty typePropertyDomainD4( testTypeProperty, vecDomainsD4 );"<<endl;
	cTypeProperty typePropertyDomainD4( testTypeProperty, *vectorDomain );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	delete vectorDomain;
	
	if ( typePropertyDomainD4 == testTypeProperty ){
	
		cout<<"The typePropertyDomainD4 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainD4 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This function compares the to given propertytypelists.
 * It ignores the orter of the elements in the lists.
 *
 * @param liEvaluedPropertyTypes the first list with the propertytypes,
 * 	which are to be compared; this propertylist sould be evalued
 * @param liToGiveBackPropertyTypes the secound list with the propertytypes,
 * 	which are to be compared; this propertylist sould be the correct properties
 */
int comparePropertyTypeLists( const list<cTypeProperty> & liEvaluedPropertyTypes,
		const list<cTypeProperty> & liToGiveBackPropertyTypes ){
	
	int iReturn = 0;
	
	if ( liEvaluedPropertyTypes.size() == liToGiveBackPropertyTypes.size() ){
	
		cout<<"Ther are correctly "<< liEvaluedPropertyTypes.size() <<
			" propertytypes given back. "<<endl;
		
		bool bPropertiesCorrect = true;
		unsigned int uiPropertyPosition = 1;
		for ( list<cTypeProperty>::const_iterator itrPropertyType =
				liToGiveBackPropertyTypes.begin();
				itrPropertyType != liToGiveBackPropertyTypes.end();
				itrPropertyType++, uiPropertyPosition++ ){
			
			list<cTypeProperty>::const_iterator itrFoundType =
				find( liEvaluedPropertyTypes.begin(), liEvaluedPropertyTypes.end(), *itrPropertyType );
			
			if ( itrFoundType == liEvaluedPropertyTypes.end() ){
				cerr<<"Error: The "<< uiPropertyPosition <<
					"'th property couldn't be found in the evalued propertytypelist.  "<<endl;
				iReturn++;
				bPropertiesCorrect = false;
			}
		}
		uiPropertyPosition = 1;
		for ( list<cTypeProperty>::const_iterator itrPropertyType =
				liEvaluedPropertyTypes.begin();
				itrPropertyType != liEvaluedPropertyTypes.end();
				itrPropertyType++, uiPropertyPosition++ ){
			
			list<cTypeProperty>::const_iterator itrFoundType =
				find ( liToGiveBackPropertyTypes.begin(), liToGiveBackPropertyTypes.end(),
				*itrPropertyType );
			
			if ( itrFoundType == liToGiveBackPropertyTypes.end() ){
				cerr<<"Error: The "<< uiPropertyPosition <<
					"'th property couldn't be found in the to evalue propertytypelist.  "<<endl;
				iReturn++;
				bPropertiesCorrect = false;
			}
		}
		if ( bPropertiesCorrect ){
			cout<<"All evalued propertytypes are correct. "<<endl;
		}
		
	}else{
		cerr<<"Error: Ther wher "<< liEvaluedPropertyTypes.size() <<
			" properties evalued, but it should be "<<
			liToGiveBackPropertyTypes.size() <<".  "<<endl;
		iReturn++;
	}
	return iReturn;
}


/**
 * This method tests the property colorRGB=1 of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertyColorRGB( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type COLOR_RGB"<<endl;
	
	unsignedIntFib uiPropertyNumber = cTypeProperty::COLOR_RGB;
	string szPropertyName = "colorRGB";
	
	cTypeProperty testTypeProperty( uiPropertyNumber );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == szPropertyName ){
	
		cout<<"The correct name \""<<szPropertyName<<"\" for the property is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \""<<szPropertyName<<"\" for the property; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	
	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements=3;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=255;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
			
			//test domain of secound vector element
			cDomain *domainElement2=standardDomainVector->getElementDomain( 2 );
			if ( domainElement2==NULL ){
			
				cerr<<"Error: The secound element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement2->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The secound element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement2;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=255;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The secound element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
			
			//test domain of third vector element
			cDomain *domainElement3=standardDomainVector->getElementDomain( 3 );
			if ( domainElement3==NULL ){
			
				cerr<<"Error: The third element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement3->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The third element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement3;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=255;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The third element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
			
		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("R","G","B")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size()==3 ){

		if ( vecUnits[0]=="red" ){
		
			cout<<"The unit of the first vector domain is correctly \"red\". "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be \"red\"."<<endl;
			iReturn++;
		}
		
		if ( vecUnits[1]=="green" ){
		
			cout<<"The unit of the secound vector domain is correctly \"green\". "<<endl;
		}else{
			cerr<<"Error: The unit of the secound vector domain is \""<<vecUnits[0]
				<<"\", but should be \"green\"."<<endl;
			iReturn++;
		}
		
		if ( vecUnits[2]=="blue" ){
		
			cout<<"The unit of the third vector domain is correctly \"blue\". "<<endl;
		}else{
			cerr<<"Error: The unit of the third vector domain is \""<<vecUnits[0]
				<<"\", but should be \"blue\"."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The the number of vectorelements is not 3 but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;

	}
	
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	list<cTypeProperty> liToGiveBackPropertyTypes;
	liToGiveBackPropertyTypes.push_back( cTypeProperty( cTypeProperty::COLOR_RGB ) );
	liToGiveBackPropertyTypes.push_back( cTypeProperty( cTypeProperty::COLOR_SW ) );
	iReturn += comparePropertyTypeLists( liOverwirttenTyps, liToGiveBackPropertyTypes );
	
	//test isEvalued()
	if ( testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is not evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"Testing a property of type cTypeProperty() copyconstructor with a given domain"<<endl;
	
	cDomainNaturalNumberBit domainInt2( 8 );
	cout<<"cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );"<<endl;
	cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );
	
	if ( typePropertyDomainInt == testTypeProperty ){
	
		cout<<"The typePropertyDomainInt and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainInt and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1 );
	cout<<"cTypeProperty typePropertyDomain1( testTypeProperty, vectorDomainD1 );"<<endl;
	cTypeProperty typePropertyDomain1( testTypeProperty, *vectorDomain );
	delete vecDomains1[ 0 ];
	delete vectorDomain;

	if ( typePropertyDomain1 == testTypeProperty ){
	
		cout<<"The typePropertyDomain1 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomain1 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 4 );
	vectorDomain = new cDomainVector( vecDomains4 );
	cout<<"cTypeProperty typePropertyDomainD4( testTypeProperty, vecDomainsD4 );"<<endl;
	cTypeProperty typePropertyDomainD4( testTypeProperty, *vectorDomain );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	delete vectorDomain;
	
	if ( typePropertyDomainD4 == testTypeProperty ){
	
		cout<<"The typePropertyDomainD4 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainD4 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the property colorSW=2 of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertyColorSW( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type COLOR_SW=2"<<endl;
	
	unsignedIntFib uiPropertyNumber = cTypeProperty::COLOR_SW;
	string szPropertyName = "colorSW";
	
	cTypeProperty testTypeProperty( uiPropertyNumber );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == szPropertyName ){
	
		cout<<"The correct name \""<<szPropertyName<<"\" for the property is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \""<<szPropertyName<<"\" for the property; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	
	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements=1;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=255;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
			
			
		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("R","G","B")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size()==1 ){

		if ( vecUnits[0]=="white" ){
		
			cout<<"The unit of the first vector domain is correctly \"white\". "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be \"white\"."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The the number of vectorelements is not 1 but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;

	}
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	list<cTypeProperty> liToGiveBackPropertyTypes;
	liToGiveBackPropertyTypes.push_back( cTypeProperty( cTypeProperty::COLOR_RGB ) );
	liToGiveBackPropertyTypes.push_back( cTypeProperty( cTypeProperty::COLOR_SW ) );
	iReturn += comparePropertyTypeLists( liOverwirttenTyps, liToGiveBackPropertyTypes );
	
	//test isEvalued()
	if ( testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is not evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"Testing a property of type cTypeProperty() copyconstructor with a given domain"<<endl;
	
	cDomainNaturalNumberBit domainInt2( 8 );
	cout<<"cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );"<<endl;
	cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );
	
	if ( typePropertyDomainInt == testTypeProperty ){
	
		cout<<"The typePropertyDomainInt and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainInt and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1 );
	cout<<"cTypeProperty typePropertyDomain1( testTypeProperty, vectorDomainD1 );"<<endl;
	cTypeProperty typePropertyDomain1( testTypeProperty, *vectorDomain );
	delete vecDomains1[ 0 ];
	delete vectorDomain;

	if ( typePropertyDomain1 == testTypeProperty ){
	
		cout<<"The typePropertyDomain1 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomain1 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 4 );
	vectorDomain = new cDomainVector( vecDomains4 );
	cout<<"cTypeProperty typePropertyDomainD4( testTypeProperty, vecDomainsD4 );"<<endl;
	cTypeProperty typePropertyDomainD4( testTypeProperty, *vectorDomain );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	delete vectorDomain;
	
	if ( typePropertyDomainD4 == testTypeProperty ){
	
		cout<<"The typePropertyDomainD4 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainD4 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the property LAYER=100 of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertyLayer( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type LAYER=100"<<endl;
	
	unsignedIntFib uiPropertyNumber = cTypeProperty::LAYER;
	string szPropertyName = "layer";
	
	cTypeProperty testTypeProperty( uiPropertyNumber );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == szPropertyName ){
	
		cout<<"The correct name \""<<szPropertyName<<"\" for the property is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \""<<szPropertyName<<"\" for the property; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	
	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements=1;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=15;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
			
		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("R","G","B")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size()==1 ){

		if ( vecUnits[0]=="layer" ){
		
			cout<<"The unit of the first vector domain is correctly \"layer\". "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be \"layer\"."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The the number of vectorelements is not 1 but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;

	}
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	list<cTypeProperty> liToGiveBackPropertyTypes;
	liToGiveBackPropertyTypes.push_back( cTypeProperty( cTypeProperty::LAYER ) );
	iReturn += comparePropertyTypeLists( liOverwirttenTyps, liToGiveBackPropertyTypes );
	
	//test isEvalued()
	if ( testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is not evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	
	cout<<endl<<"Testing a property of type cTypeProperty() copyconstructor with a given domain"<<endl;
	
	cDomainNaturalNumberBit domainInt2( 8 );
	cout<<"cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );"<<endl;
	cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );
	
	if ( typePropertyDomainInt == testTypeProperty ){
	
		cout<<"The typePropertyDomainInt and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainInt and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1 );
	cout<<"cTypeProperty typePropertyDomain1( testTypeProperty, vectorDomainD1 );"<<endl;
	cTypeProperty typePropertyDomain1( testTypeProperty, *vectorDomain );
	delete vecDomains1[ 0 ];
	delete vectorDomain;

	if ( typePropertyDomain1 == testTypeProperty ){
	
		cout<<"The typePropertyDomain1 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomain1 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 4 );
	vectorDomain = new cDomainVector( vecDomains4 );
	cout<<"cTypeProperty typePropertyDomainD4( testTypeProperty, vecDomainsD4 );"<<endl;
	cTypeProperty typePropertyDomainD4( testTypeProperty, *vectorDomain );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	delete vectorDomain;
	
	if ( typePropertyDomainD4 == testTypeProperty ){
	
		cout<<"The typePropertyDomainD4 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainD4 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the property TRANSPARENCY=200 of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertyTransparency( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type TRANSPARENCY = 200"<<endl;
	
	unsignedIntFib uiPropertyNumber = cTypeProperty::TRANSPARENCY;
	string szPropertyName = "transparency";
	
	cTypeProperty testTypeProperty( uiPropertyNumber );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == szPropertyName ){
	
		cout<<"The correct name \""<<szPropertyName<<"\" for the property is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \""<<szPropertyName<<"\" for the property; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	
	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements=1;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=255;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
			
		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("R","G","B")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size()==1 ){

		if ( vecUnits[0]=="fraction" ){
		
			cout<<"The unit of the first vector domain is correctly \"fraction\". "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be \"fraction\"."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The the number of vectorelements is not 1 but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;

	}
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	list<cTypeProperty> liToGiveBackPropertyTypes;
	liToGiveBackPropertyTypes.push_back( cTypeProperty( cTypeProperty::TRANSPARENCY ) );
	iReturn += comparePropertyTypeLists( liOverwirttenTyps, liToGiveBackPropertyTypes );
	
	//test isEvalued()
	if ( testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is not evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	
	cout<<endl<<"Testing a property of type cTypeProperty() copyconstructor with a given domain"<<endl;
	
	cDomainNaturalNumberBit domainInt2( 8 );
	cout<<"cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );"<<endl;
	cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );
	
	if ( typePropertyDomainInt == testTypeProperty ){
	
		cout<<"The typePropertyDomainInt and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainInt and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1 );
	cout<<"cTypeProperty typePropertyDomain1( testTypeProperty, vectorDomainD1 );"<<endl;
	cTypeProperty typePropertyDomain1( testTypeProperty, *vectorDomain );
	delete vecDomains1[ 0 ];
	delete vectorDomain;

	if ( typePropertyDomain1 == testTypeProperty ){
	
		cout<<"The typePropertyDomain1 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomain1 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 4 );
	vectorDomain = new cDomainVector( vecDomains4 );
	cout<<"cTypeProperty typePropertyDomainD4( testTypeProperty, vecDomainsD4 );"<<endl;
	cTypeProperty typePropertyDomainD4( testTypeProperty, *vectorDomain );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	delete vectorDomain;
	
	if ( typePropertyDomainD4 == testTypeProperty ){
	
		cout<<"The typePropertyDomainD4 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainD4 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the property SOUND = 300 of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertySound( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type SOUND = 300"<<endl;
	
	unsignedIntFib uiPropertyNumber = cTypeProperty::SOUND;
	string szPropertyName = "sound";
	
	cTypeProperty testTypeProperty( uiPropertyNumber );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == szPropertyName ){
	
		cout<<"The correct name \""<<szPropertyName<<"\" for the property is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \""<<szPropertyName<<"\" for the property; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//check compatible for vector domain with four elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 13 );
	vectorDomain = new cDomainVector( vecDomains4 );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	
	//check the isCompatible() methode for vectordomain with 4 elements
	if ( testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 4 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	
	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements=4;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=65535.0;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of secound vector element
			cDomain *domainElement2=standardDomainVector->getElementDomain( 2 );
			if ( domainElement2==NULL ){
			
				cerr<<"Error: The scound element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement2->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The secound element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement2;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=4294967295.0;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The secound element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of third vector element
			cDomain *domainElement3=standardDomainVector->getElementDomain( 3 );
			if ( domainElement3==NULL ){
			
				cerr<<"Error: The third element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement3->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The third element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement3;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=0.9999847412109375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The third element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of fourth vector element
			cDomain *domainElement4=standardDomainVector->getElementDomain( 4 );
			if ( domainElement4==NULL ){
			
				cerr<<"Error: The fourth element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement4->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The fourth element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement4;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=16777215.99609375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The fourth element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("R","G","B")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size()==4 ){

		if ( vecUnits[0]=="1/s" ){
		
			cout<<"The unit of the first vector domain is correctly \"1/s\". "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be \"1/s\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[1]=="Pa" ){
		
			cout<<"The unit of the secound vector domain is correctly \"Pa\". "<<endl;
		}else{
			cerr<<"Error: The unit of the secound vector domain is \""<<vecUnits[0]
				<<"\", but should be \"Pa\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[2]=="radian" ){
		
			cout<<"The unit of the 3'th vector domain is correctly \"radian\". "<<endl;
		}else{
			cerr<<"Error: The unit of the 3'th vector domain is \""<<vecUnits[0]
				<<"\", but should be \"radian\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[3]=="s" ){
		
			cout<<"The unit of the 4'th vector domain is correctly \"s\". "<<endl;
		}else{
			cerr<<"Error: The unit of the 4'th vector domain is \""<<vecUnits[0]
				<<"\", but should be \"s\"."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The the number of vectorelements is not 1 but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;

	}
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	list<cTypeProperty> liToGiveBackPropertyTypes;
	iReturn += comparePropertyTypeLists( liOverwirttenTyps, liToGiveBackPropertyTypes );
	
	//test isEvalued()
	if ( testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is not evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	
	cout<<endl<<"Testing a property of type cTypeProperty() copyconstructor with a given domain"<<endl;
	
	cDomainNaturalNumberBit domainInt2( 8 );
	cout<<"cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );"<<endl;
	cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );
	
	if ( typePropertyDomainInt == testTypeProperty ){
	
		cout<<"The typePropertyDomainInt and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainInt and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1 );
	cout<<"cTypeProperty typePropertyDomain1( testTypeProperty, vectorDomainD1 );"<<endl;
	cTypeProperty typePropertyDomain1( testTypeProperty, *vectorDomain );
	delete vecDomains1[ 0 ];
	delete vectorDomain;

	if ( typePropertyDomain1 == testTypeProperty ){
	
		cout<<"The typePropertyDomain1 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomain1 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	//check compatible for vector domain with tree elements
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 4 );
	vectorDomain = new cDomainVector( vecDomains4 );
	cout<<"cTypeProperty typePropertyDomainD4( testTypeProperty, vecDomainsD4 );"<<endl;
	cTypeProperty typePropertyDomainD4( testTypeProperty, *vectorDomain );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	delete vectorDomain;
	
	if ( typePropertyDomainD4 == testTypeProperty ){
	
		cout<<"The typePropertyDomainD4 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainD4 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the property SOUND_POLARIZED = 301 of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertySoundPolarizedStandard2D( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type SOUND_POLARIZED = 301"<<endl;
	
	unsignedIntFib uiPropertyNumber = cTypeProperty::SOUND_POLARIZED;
	string szPropertyName = "soundPolarized";
	
	cTypeProperty testTypeProperty( uiPropertyNumber );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == szPropertyName ){
	
		cout<<"The correct name \""<<szPropertyName<<"\" for the property is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \""<<szPropertyName<<"\" for the property; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//check compatible for vector domain with four elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 13 );
	vectorDomain = new cDomainVector( vecDomains4 );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	
	//check the isCompatible() methode for vectordomain with 4 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is not correctly compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 4 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with 5 elements
	vector<cDomainSingle*> vecDomains5( 5 );
	vecDomains5[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains5[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains5[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains5[ 3 ] = new cDomainNaturalNumberBit( 13 );
	vecDomains5[ 4 ] = new cDomainNaturalNumberBit( 2, 0.5 );
	vectorDomain = new cDomainVector( vecDomains5 );
	delete vecDomains5[ 0 ];
	delete vecDomains5[ 1 ];
	delete vecDomains5[ 2 ];
	delete vecDomains5[ 3 ];
	delete vecDomains5[ 4 ];

	//check the isCompatible() methode for vectordomain with 5 elements
	if ( testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 5 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 5 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	const unsignedIntFib uiStandardDomainVectorElements=5;

	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=65535.0;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of secound vector element
			cDomain *domainElement2=standardDomainVector->getElementDomain( 2 );
			if ( domainElement2==NULL ){
			
				cerr<<"Error: The scound element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement2->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The secound element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement2;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=4294967295.0;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The secound element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of third vector element
			cDomain *domainElement3=standardDomainVector->getElementDomain( 3 );
			if ( domainElement3==NULL ){
			
				cerr<<"Error: The third element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement3->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The third element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement3;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=0.9999847412109375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The third element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of fourth vector element
			cDomain *domainElement4=standardDomainVector->getElementDomain( 4 );
			if ( domainElement4==NULL ){
			
				cerr<<"Error: The fourth element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement4->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The fourth element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement4;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=16777215.99609375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}

			}else{
				cerr<<"Error: The fourth element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of 5'th vector element
			cDomain *domainElement5=standardDomainVector->getElementDomain( 5 );
			if ( domainElement5==NULL ){
			
				cerr<<"Error: The 5'th element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement5->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The 5'th  element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement5;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=0.9999847412109375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}

			}else{
				cerr<<"Error: The 5'th element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("R","G","B")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size()==uiStandardDomainVectorElements ){

		if ( vecUnits[0]=="1/s" ){
		
			cout<<"The unit of the first vector domain is correctly \"1/s\". "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be \"1/s\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[1]=="Pa" ){
		
			cout<<"The unit of the secound vector domain is correctly \"Pa\". "<<endl;
		}else{
			cerr<<"Error: The unit of the secound vector domain is \""<<vecUnits[0]
				<<"\", but should be \"Pa\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[2]=="radian" ){
		
			cout<<"The unit of the third vector domain is correctly \"radian\". "<<endl;
		}else{
			cerr<<"Error: The unit of the third vector domain is \""<<vecUnits[0]
				<<"\", but should be \"radian\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[3]=="s" ){
		
			cout<<"The unit of the 4'th vector domain is correctly \"s\". "<<endl;
		}else{
			cerr<<"Error: The unit of the 4'th vector domain is \""<<vecUnits[0]
				<<"\", but should be \"s\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[4]=="radian" ){
		
			cout<<"The unit of the 5'th vector domain is correctly \"radian\". "<<endl;
		}else{
			cerr<<"Error: The unit of the 5'th vector domain is \""<<vecUnits[0]
				<<"\", but should be \"radian\"."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The the number of vectorelements is not "<<
			uiStandardDomainVectorElements<<" but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;

	}
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	list<cTypeProperty> liToGiveBackPropertyTypes;
	iReturn += comparePropertyTypeLists( liOverwirttenTyps, liToGiveBackPropertyTypes );
	
	//test isEvalued()
	if ( testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is not evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"Testing a property of type cTypeProperty() copyconstructor with a given domain"<<endl;
	
	cDomainNaturalNumberBit domainInt2( 8 );
	cout<<"cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );"<<endl;
	cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );
	
	if ( typePropertyDomainInt == testTypeProperty ){
	
		cout<<"The typePropertyDomainInt and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainInt and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	cTypeProperty typeSoundPolarized0D( cTypeProperty::SOUND_POLARIZED, 0 );
	
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1 );
	cout<<"cTypeProperty typePropertyDomain1( testTypeProperty, vectorDomainD1 );"<<endl;
	cTypeProperty typePropertyDomain1( testTypeProperty, *vectorDomain );
	delete vecDomains1[ 0 ];
	delete vectorDomain;

	if ( typePropertyDomain1 == typeSoundPolarized0D ){
	
		cout<<"The typePropertyDomain1 and typeSoundPolarized0D are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomain1 and typeSoundPolarized0D are not equal."<<endl;
		iReturn++;
	}
	
	//check compatible for vector domain with tree elements
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 4 );
	vectorDomain = new cDomainVector( vecDomains4 );
	cout<<"cTypeProperty typePropertyDomainD4( testTypeProperty, vecDomainsD4 );"<<endl;
	cTypeProperty typePropertyDomainD4( testTypeProperty, *vectorDomain );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	delete vectorDomain;
	
	cTypeProperty typeSoundPolarized1D( cTypeProperty::SOUND_POLARIZED, 1 );
	
	if ( typePropertyDomainD4 == typeSoundPolarized1D ){
	
		cout<<"The typePropertyDomainD4 and typeSoundPolarized1D are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainD4 and typeSoundPolarized1D are not equal."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This method tests the property SOUND_POLARIZED = 301 of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertySoundPolarizedStandard3D( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type SOUND_POLARIZED = 301 for 3 Dimensions"<<endl;
	
	unsignedIntFib uiPropertyNumber = cTypeProperty::SOUND_POLARIZED;
	string szPropertyName = "soundPolarized";
	
	cTypeProperty testTypeProperty( uiPropertyNumber, 3 );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == szPropertyName ){
	
		cout<<"The correct name \""<<szPropertyName<<"\" for the property is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \""<<szPropertyName<<"\" for the property; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//check compatible for vector domain with four elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 13 );
	vectorDomain = new cDomainVector( vecDomains4 );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	
	//check the isCompatible() methode for vectordomain with 4 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 4 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with 6 elements
	vector<cDomainSingle*> vecDomains6( 6 );
	vecDomains6[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains6[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains6[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains6[ 3 ] = new cDomainNaturalNumberBit( 13 );
	vecDomains6[ 4 ] = new cDomainNaturalNumberBit( 35 );
	vecDomains6[ 5 ] = new cDomainNaturalNumberBit( 2, 0.5 );
	vectorDomain = new cDomainVector( vecDomains6 );
	delete vecDomains6[ 0 ];
	delete vecDomains6[ 1 ];
	delete vecDomains6[ 2 ];
	delete vecDomains6[ 3 ];
	delete vecDomains6[ 4 ];
	delete vecDomains6[ 5 ];

	//check the isCompatible() methode for vectordomain with 6 elements
	if ( testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 6 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 6 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	const unsignedIntFib uiStandardDomainVectorElements=6;

	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=65535.0;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of secound vector element
			cDomain *domainElement2=standardDomainVector->getElementDomain( 2 );
			if ( domainElement2==NULL ){
			
				cerr<<"Error: The scound element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement2->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The secound element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement2;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=4294967295.0;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The secound element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of third vector element
			cDomain *domainElement3=standardDomainVector->getElementDomain( 3 );
			if ( domainElement3==NULL ){
			
				cerr<<"Error: The third element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement3->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The third element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement3;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=0.9999847412109375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The third element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of fourth vector element
			cDomain *domainElement4=standardDomainVector->getElementDomain( 4 );
			if ( domainElement4==NULL ){
			
				cerr<<"Error: The fourth element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement4->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The fourth element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement4;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=16777215.99609375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}

			}else{
				cerr<<"Error: The fourth element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of 5'th vector element
			cDomain *domainElement5=standardDomainVector->getElementDomain( 5 );
			if ( domainElement5==NULL ){
			
				cerr<<"Error: The 5'th element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement5->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The 5'th  element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement5;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=0.9999847412109375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}

			}else{
				cerr<<"Error: The 5'th element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of 6'th vector element
			cDomain *domainElement6=standardDomainVector->getElementDomain( 6 );
			if ( domainElement6==NULL ){
			
				cerr<<"Error: The 6'th element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement6->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The 6'th  element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement6;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=0.9999847412109375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}

			}else{
				cerr<<"Error: The 6'th element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}


		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("R","G","B")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size()==uiStandardDomainVectorElements ){

		if ( vecUnits[0]=="1/s" ){
		
			cout<<"The unit of the first vector domain is correctly \"1/s\". "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be \"1/s\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[1]=="Pa" ){
		
			cout<<"The unit of the secound vector domain is correctly \"Pa\". "<<endl;
		}else{
			cerr<<"Error: The unit of the secound vector domain is \""<<vecUnits[0]
				<<"\", but should be \"Pa\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[2]=="radian" ){
		
			cout<<"The unit of the third vector domain is correctly \"radian\". "<<endl;
		}else{
			cerr<<"Error: The unit of the third vector domain is \""<<vecUnits[0]
				<<"\", but should be \"radian\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[3]=="s" ){
		
			cout<<"The unit of the 4'th vector domain is correctly \"s\". "<<endl;
		}else{
			cerr<<"Error: The unit of the 4'th vector domain is \""<<vecUnits[0]
				<<"\", but should be \"s\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[4]=="radian" ){
		
			cout<<"The unit of the 5'th vector domain is correctly \"radian\". "<<endl;
		}else{
			cerr<<"Error: The unit of the 5'th vector domain is \""<<vecUnits[0]
				<<"\", but should be \"radian\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[5]=="radian" ){
		
			cout<<"The unit of the 6'th vector domain is correctly \"radian\". "<<endl;
		}else{
			cerr<<"Error: The unit of the 6'th vector domain is \""<<vecUnits[0]
				<<"\", but should be \"radian\"."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The the number of vectorelements is not "<<
			uiStandardDomainVectorElements<<" but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;

	}
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	list<cTypeProperty> liToGiveBackPropertyTypes;
	iReturn += comparePropertyTypeLists( liOverwirttenTyps, liToGiveBackPropertyTypes );
	
	//test isEvalued()
	if ( testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is not evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	return iReturn;
}



/**
 * This method tests the property SOUND_BARRIER = 310 of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertySoundBarrier( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type SOUND_BARRIER = 310"<<endl;
	
	unsignedIntFib uiPropertyNumber = cTypeProperty::SOUND_BARRIER;
	string szPropertyName = "soundBarrier";
	
	cTypeProperty testTypeProperty( uiPropertyNumber );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == szPropertyName ){
	
		cout<<"The correct name \""<<szPropertyName<<"\" for the property is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \""<<szPropertyName<<"\" for the property; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	
	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements=1;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=65535;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
			
		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("R","G","B")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size()==1 ){

		if ( vecUnits[0]=="m/s" ){
		
			cout<<"The unit of the first vector domain is correctly \"m/s\". "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be \"m/s\"."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The the number of vectorelements is not 1 but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;

	}
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	list<cTypeProperty> liToGiveBackPropertyTypes;
	liToGiveBackPropertyTypes.push_back( cTypeProperty( cTypeProperty::SOUND_BARRIER ) );
	iReturn += comparePropertyTypeLists( liOverwirttenTyps, liToGiveBackPropertyTypes );
	
	//test isEvalued()
	if ( testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is not evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	
	cout<<endl<<"Testing a property of type cTypeProperty() copyconstructor with a given domain"<<endl;
	
	cDomainNaturalNumberBit domainInt2( 8 );
	cout<<"cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );"<<endl;
	cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );
	
	if ( typePropertyDomainInt == testTypeProperty ){
	
		cout<<"The typePropertyDomainInt and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainInt and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1 );
	cout<<"cTypeProperty typePropertyDomain1( testTypeProperty, vectorDomainD1 );"<<endl;
	cTypeProperty typePropertyDomain1( testTypeProperty, *vectorDomain );
	delete vecDomains1[ 0 ];
	delete vectorDomain;

	if ( typePropertyDomain1 == testTypeProperty ){
	
		cout<<"The typePropertyDomain1 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomain1 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 4 );
	vectorDomain = new cDomainVector( vecDomains4 );
	cout<<"cTypeProperty typePropertyDomainD4( testTypeProperty, vecDomainsD4 );"<<endl;
	cTypeProperty typePropertyDomainD4( testTypeProperty, *vectorDomain );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	delete vectorDomain;
	
	if ( typePropertyDomainD4 == testTypeProperty ){
	
		cout<<"The typePropertyDomainD4 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainD4 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests the property SOUND_REFLECTED = 311 of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertySoundReflected( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type SOUND_REFLECTED = 311"<<endl;
	
	unsignedIntFib uiPropertyNumber = cTypeProperty::SOUND_REFLECTED;
	string szPropertyName = "soundReflected";
	
	cTypeProperty testTypeProperty( uiPropertyNumber );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == szPropertyName ){
	
		cout<<"The correct name \""<<szPropertyName<<"\" for the property is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \""<<szPropertyName<<"\" for the property; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	
	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements=1;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=0.9999847412109375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
			
		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("R","G","B")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size()==1 ){

		if ( vecUnits[0]=="fraction" ){
		
			cout<<"The unit of the first vector domain is correctly \"fraction\". "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be \"fraction\"."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The the number of vectorelements is not 1 but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;

	}
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	list<cTypeProperty> liToGiveBackPropertyTypes;
	liToGiveBackPropertyTypes.push_back( cTypeProperty( cTypeProperty::SOUND_REFLECTED ) );
	iReturn += comparePropertyTypeLists( liOverwirttenTyps, liToGiveBackPropertyTypes );
	
	//test isEvalued()
	if ( testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is not evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	
	cout<<endl<<"Testing a property of type cTypeProperty() copyconstructor with a given domain"<<endl;
	
	cDomainNaturalNumberBit domainInt2( 8 );
	cout<<"cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );"<<endl;
	cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );
	
	if ( typePropertyDomainInt == testTypeProperty ){
	
		cout<<"The typePropertyDomainInt and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainInt and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1 );
	cout<<"cTypeProperty typePropertyDomain1( testTypeProperty, vectorDomainD1 );"<<endl;
	cTypeProperty typePropertyDomain1( testTypeProperty, *vectorDomain );
	delete vecDomains1[ 0 ];
	delete vectorDomain;

	if ( typePropertyDomain1 == testTypeProperty ){
	
		cout<<"The typePropertyDomain1 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomain1 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 4 );
	vectorDomain = new cDomainVector( vecDomains4 );
	cout<<"cTypeProperty typePropertyDomainD4( testTypeProperty, vecDomainsD4 );"<<endl;
	cTypeProperty typePropertyDomainD4( testTypeProperty, *vectorDomain );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	delete vectorDomain;
	
	if ( typePropertyDomainD4 == testTypeProperty ){
	
		cout<<"The typePropertyDomainD4 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainD4 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the property SOUND_DAMPING = 312 of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertySoundDamping( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type SOUND_DAMPING = 312"<<endl;
	
	unsignedIntFib uiPropertyNumber = cTypeProperty::SOUND_DAMPING;
	string szPropertyName = "soundDamping";
	
	cTypeProperty testTypeProperty( uiPropertyNumber );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == szPropertyName ){
	
		cout<<"The correct name \""<<szPropertyName<<"\" for the property is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \""<<szPropertyName<<"\" for the property; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	
	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements=1;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=0.9999847412109375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
			
		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("R","G","B")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size()==1 ){

		if ( vecUnits[0]=="fraction" ){
		
			cout<<"The unit of the first vector domain is correctly \"fraction\". "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be \"fraction\"."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The the number of vectorelements is not 1 but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;

	}
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	list<cTypeProperty> liToGiveBackPropertyTypes;
	liToGiveBackPropertyTypes.push_back( cTypeProperty( cTypeProperty::SOUND_DAMPING ) );
	iReturn += comparePropertyTypeLists( liOverwirttenTyps, liToGiveBackPropertyTypes );
	
	//test isEvalued()
	if ( testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is not evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	
	cout<<endl<<"Testing a property of type cTypeProperty() copyconstructor with a given domain"<<endl;
	
	cDomainNaturalNumberBit domainInt2( 8 );
	cout<<"cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );"<<endl;
	cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );
	
	if ( typePropertyDomainInt == testTypeProperty ){
	
		cout<<"The typePropertyDomainInt and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainInt and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1 );
	cout<<"cTypeProperty typePropertyDomain1( testTypeProperty, vectorDomainD1 );"<<endl;
	cTypeProperty typePropertyDomain1( testTypeProperty, *vectorDomain );
	delete vecDomains1[ 0 ];
	delete vectorDomain;

	if ( typePropertyDomain1 == testTypeProperty ){
	
		cout<<"The typePropertyDomain1 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomain1 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 4 );
	vectorDomain = new cDomainVector( vecDomains4 );
	cout<<"cTypeProperty typePropertyDomainD4( testTypeProperty, vecDomainsD4 );"<<endl;
	cTypeProperty typePropertyDomainD4( testTypeProperty, *vectorDomain );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	delete vectorDomain;
	
	if ( typePropertyDomainD4 == testTypeProperty ){
	
		cout<<"The typePropertyDomainD4 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainD4 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests the property KELVIN = 400 of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertyKelvin( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type KELVIN = 400"<<endl;
	
	unsignedIntFib uiPropertyNumber = cTypeProperty::KELVIN;
	string szPropertyName = "kelvin";
	
	cTypeProperty testTypeProperty( uiPropertyNumber );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == szPropertyName ){
	
		cout<<"The correct name \""<<szPropertyName<<"\" for the property is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \""<<szPropertyName<<"\" for the property; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	
	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements=1;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=4095.9375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
			
		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("R","G","B")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size()==1 ){

		if ( vecUnits[0]=="K" ){
		
			cout<<"The unit of the first vector domain is correctly \"K\". "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be \"K\"."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The the number of vectorelements is not 1 but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;

	}
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	list<cTypeProperty> liToGiveBackPropertyTypes;
	liToGiveBackPropertyTypes.push_back( cTypeProperty( cTypeProperty::KELVIN ) );
	iReturn += comparePropertyTypeLists( liOverwirttenTyps, liToGiveBackPropertyTypes );
	
	//test isEvalued()
	if ( testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is not evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	
	cout<<endl<<"Testing a property of type cTypeProperty() copyconstructor with a given domain"<<endl;
	
	cDomainNaturalNumberBit domainInt2( 8 );
	cout<<"cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );"<<endl;
	cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );
	
	if ( typePropertyDomainInt == testTypeProperty ){
	
		cout<<"The typePropertyDomainInt and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainInt and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1 );
	cout<<"cTypeProperty typePropertyDomain1( testTypeProperty, vectorDomainD1 );"<<endl;
	cTypeProperty typePropertyDomain1( testTypeProperty, *vectorDomain );
	delete vecDomains1[ 0 ];
	delete vectorDomain;

	if ( typePropertyDomain1 == testTypeProperty ){
	
		cout<<"The typePropertyDomain1 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomain1 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 4 );
	vectorDomain = new cDomainVector( vecDomains4 );
	cout<<"cTypeProperty typePropertyDomainD4( testTypeProperty, vecDomainsD4 );"<<endl;
	cTypeProperty typePropertyDomainD4( testTypeProperty, *vectorDomain );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	delete vectorDomain;
	
	if ( typePropertyDomainD4 == testTypeProperty ){
	
		cout<<"The typePropertyDomainD4 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainD4 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests the property ELECTRO_MAGNETIC = 410 of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertyElectromagnetic2D( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type ELECTRO_MAGNETIC = 410"<<endl;
	
	unsignedIntFib uiPropertyNumber = cTypeProperty::ELECTRO_MAGNETIC;
	string szPropertyName = "electroMagnetic";
	
	cTypeProperty testTypeProperty( uiPropertyNumber );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == szPropertyName ){
	
		cout<<"The correct name \""<<szPropertyName<<"\" for the property is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \""<<szPropertyName<<"\" for the property; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//check compatible for vector domain with four elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 13 );
	vectorDomain = new cDomainVector( vecDomains4 );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	
	//check the isCompatible() methode for vectordomain with 4 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is not correctly compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 4 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with 5 elements
	vector<cDomainSingle*> vecDomains5( 5 );
	vecDomains5[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains5[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains5[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains5[ 3 ] = new cDomainNaturalNumberBit( 13 );
	vecDomains5[ 4 ] = new cDomainNaturalNumberBit( 2, 0.5 );
	vectorDomain = new cDomainVector( vecDomains5 );
	delete vecDomains5[ 0 ];
	delete vecDomains5[ 1 ];
	delete vecDomains5[ 2 ];
	delete vecDomains5[ 3 ];
	delete vecDomains5[ 4 ];

	//check the isCompatible() methode for vectordomain with 5 elements
	if ( testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 5 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 5 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	const unsignedIntFib uiStandardDomainVectorElements=5;

	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=18446744073709551615.0;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of secound vector element
			cDomain *domainElement2=standardDomainVector->getElementDomain( 2 );
			if ( domainElement2==NULL ){
			
				cerr<<"Error: The scound element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement2->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The secound element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement2;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=281474976710656.0;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The secound element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of third vector element
			cDomain *domainElement3=standardDomainVector->getElementDomain( 3 );
			if ( domainElement3==NULL ){
			
				cerr<<"Error: The third element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement3->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The third element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement3;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=0.9999847412109375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The third element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of fourth vector element
			cDomain *domainElement4=standardDomainVector->getElementDomain( 4 );
			if ( domainElement4==NULL ){
			
				cerr<<"Error: The fourth element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement4->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The fourth element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement4;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=16777215.99609375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}

			}else{
				cerr<<"Error: The fourth element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of 5'th vector element
			cDomain *domainElement5=standardDomainVector->getElementDomain( 5 );
			if ( domainElement5==NULL ){
			
				cerr<<"Error: The 5'th element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement5->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The 5'th  element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement5;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=0.9999847412109375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}

			}else{
				cerr<<"Error: The 5'th element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("R","G","B")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size()==uiStandardDomainVectorElements ){

		if ( vecUnits[0]=="1/s" ){
		
			cout<<"The unit of the first vector domain is correctly \"1/s\". "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be \"1/s\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[1]=="cd" ){
		
			cout<<"The unit of the secound vector domain is correctly \"cd\". "<<endl;
		}else{
			cerr<<"Error: The unit of the secound vector domain is \""<<vecUnits[0]
				<<"\", but should be \"cd\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[2]=="radian" ){
		
			cout<<"The unit of the third vector domain is correctly \"radian\". "<<endl;
		}else{
			cerr<<"Error: The unit of the third vector domain is \""<<vecUnits[0]
				<<"\", but should be \"radian\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[3]=="s" ){
		
			cout<<"The unit of the 4'th vector domain is correctly \"s\". "<<endl;
		}else{
			cerr<<"Error: The unit of the 4'th vector domain is \""<<vecUnits[0]
				<<"\", but should be \"s\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[4]=="radian" ){
		
			cout<<"The unit of the 5'th vector domain is correctly \"radian\". "<<endl;
		}else{
			cerr<<"Error: The unit of the 5'th vector domain is \""<<vecUnits[0]
				<<"\", but should be \"radian\"."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The the number of vectorelements is not "<<
			uiStandardDomainVectorElements<<" but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;

	}
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	list<cTypeProperty> liToGiveBackPropertyTypes;
	iReturn += comparePropertyTypeLists( liOverwirttenTyps, liToGiveBackPropertyTypes );
	
	//test isEvalued()
	if ( testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is not evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	
	cout<<endl<<"Testing a property of type cTypeProperty() copyconstructor with a given domain"<<endl;
	
	cDomainNaturalNumberBit domainInt2( 8 );
	cout<<"cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );"<<endl;
	cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );
	
	if ( typePropertyDomainInt == testTypeProperty ){
	
		cout<<"The typePropertyDomainInt and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainInt and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	cTypeProperty typeElectroMagnetic0D( cTypeProperty::ELECTRO_MAGNETIC, 0 );
	
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1 );
	cout<<"cTypeProperty typePropertyDomain1( testTypeProperty, vectorDomainD1 );"<<endl;
	cTypeProperty typePropertyDomain1( testTypeProperty, *vectorDomain );
	delete vecDomains1[ 0 ];
	delete vectorDomain;

	if ( typePropertyDomain1 == typeElectroMagnetic0D ){
	
		cout<<"The typePropertyDomain1 and typeElectroMagnetic0D are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomain1 and typeElectroMagnetic0D are not equal."<<endl;
		iReturn++;
	}
	
	//check compatible for vector domain with tree elements
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 4 );
	vectorDomain = new cDomainVector( vecDomains4 );
	cout<<"cTypeProperty typeElectroMagnetic4D( testTypeProperty, vecDomainsD4 );"<<endl;
	cTypeProperty typePropertyDomainD4( testTypeProperty, *vectorDomain );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	delete vectorDomain;
	
	cTypeProperty typeElectroMagnetic1D( cTypeProperty::ELECTRO_MAGNETIC, 1 );
	
	if ( typePropertyDomainD4 == typeElectroMagnetic1D ){
	
		cout<<"The typePropertyDomainD4 and typeElectroMagnetic1D are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainD4 and typeElectroMagnetic1D are not equal."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the property ELECTRO_MAGNETIC = 410 of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertyElectromagnetic4D( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type ELECTRO_MAGNETIC = 410 for 4 Dimenstions"<<endl;
	
	unsignedIntFib uiPropertyNumber = cTypeProperty::ELECTRO_MAGNETIC;
	string szPropertyName = "electroMagnetic";
	
	cTypeProperty testTypeProperty( uiPropertyNumber, 4 );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == szPropertyName ){
	
		cout<<"The correct name \""<<szPropertyName<<"\" for the property is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \""<<szPropertyName<<"\" for the property; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//check compatible for vector domain with four elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 13 );
	vectorDomain = new cDomainVector( vecDomains4 );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	
	//check the isCompatible() methode for vectordomain with 4 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is not correctly compatible to the vector domain with 4 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 4 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with 7 elements
	vector<cDomainSingle*> vecDomains7( 7 );
	vecDomains7[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains7[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains7[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains7[ 3 ] = new cDomainNaturalNumberBit( 13 );
	vecDomains7[ 4 ] = new cDomainNaturalNumberBit( 2, 0.5 );
	vecDomains7[ 5 ] = new cDomainNaturalNumberBit( 4, 0.5 );
	vecDomains7[ 6 ] = new cDomainNaturalNumberBit( 15, 1.0/15.0 );
	vectorDomain = new cDomainVector( vecDomains7 );
	delete vecDomains7[ 0 ];
	delete vecDomains7[ 1 ];
	delete vecDomains7[ 2 ];
	delete vecDomains7[ 3 ];
	delete vecDomains7[ 4 ];
	delete vecDomains7[ 5 ];
	delete vecDomains7[ 6 ];

	//check the isCompatible() methode for vectordomain with 7 elements
	if ( testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 7 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 7 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	const unsignedIntFib uiStandardDomainVectorElements=7;

	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=18446744073709551615.0;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of secound vector element
			cDomain *domainElement2=standardDomainVector->getElementDomain( 2 );
			if ( domainElement2==NULL ){
			
				cerr<<"Error: The scound element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement2->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The secound element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement2;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=281474976710656.0;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The secound element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of third vector element
			cDomain *domainElement3=standardDomainVector->getElementDomain( 3 );
			if ( domainElement3==NULL ){
			
				cerr<<"Error: The third element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement3->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The third element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement3;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=0.9999847412109375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The third element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of fourth vector element
			cDomain *domainElement4=standardDomainVector->getElementDomain( 4 );
			if ( domainElement4==NULL ){
			
				cerr<<"Error: The fourth element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement4->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The fourth element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement4;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=16777215.99609375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}

			}else{
				cerr<<"Error: The fourth element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of 5'th vector element
			cDomain *domainElement5=standardDomainVector->getElementDomain( 5 );
			if ( domainElement5==NULL ){
			
				cerr<<"Error: The 5'th element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement5->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The 5'th  element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement5;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=0.9999847412109375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}

			}else{
				cerr<<"Error: The 5'th element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of 6'th vector element
			cDomain *domainElement6=standardDomainVector->getElementDomain( 6 );
			if ( domainElement6==NULL ){
			
				cerr<<"Error: The 6'th element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement6->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The 6'th  element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement6;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=0.9999847412109375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}

			}else{
				cerr<<"Error: The 6'th element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

			//test domain of 7'th vector element
			cDomain *domainElement7=standardDomainVector->getElementDomain( 7 );
			if ( domainElement7==NULL ){
			
				cerr<<"Error: The 7'th element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement7->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The 7'th  element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement7;
				
				const doubleFib lowerBound=0.0;
				const doubleFib upperBound=0.9999847412109375;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}

			}else{
				cerr<<"Error: The 7'th element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}

		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("R","G","B")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size()==uiStandardDomainVectorElements ){

		if ( vecUnits[0]=="1/s" ){
		
			cout<<"The unit of the first vector domain is correctly \"1/s\". "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be \"1/s\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[1]=="cd" ){
		
			cout<<"The unit of the secound vector domain is correctly \"cd\". "<<endl;
		}else{
			cerr<<"Error: The unit of the secound vector domain is \""<<vecUnits[0]
				<<"\", but should be \"cd\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[2]=="radian" ){
		
			cout<<"The unit of the third vector domain is correctly \"radian\". "<<endl;
		}else{
			cerr<<"Error: The unit of the third vector domain is \""<<vecUnits[0]
				<<"\", but should be \"radian\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[3]=="s" ){
		
			cout<<"The unit of the 4'th vector domain is correctly \"s\". "<<endl;
		}else{
			cerr<<"Error: The unit of the 4'th vector domain is \""<<vecUnits[0]
				<<"\", but should be \"s\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[4]=="radian" ){
		
			cout<<"The unit of the 5'th vector domain is correctly \"radian\". "<<endl;
		}else{
			cerr<<"Error: The unit of the 5'th vector domain is \""<<vecUnits[0]
				<<"\", but should be \"radian\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[5]=="radian" ){
		
			cout<<"The unit of the 6'th vector domain is correctly \"radian\". "<<endl;
		}else{
			cerr<<"Error: The unit of the 6'th vector domain is \""<<vecUnits[0]
				<<"\", but should be \"radian\"."<<endl;
			iReturn++;
		}
		if ( vecUnits[6]=="radian" ){
		
			cout<<"The unit of the 7'th vector domain is correctly \"radian\". "<<endl;
		}else{
			cerr<<"Error: The unit of the 7'th vector domain is \""<<vecUnits[0]
				<<"\", but should be \"radian\"."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: The the number of vectorelements is not "<<
			uiStandardDomainVectorElements<<" but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;

	}
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	list<cTypeProperty> liToGiveBackPropertyTypes;
	iReturn += comparePropertyTypeLists( liOverwirttenTyps, liToGiveBackPropertyTypes );
	
	//test isEvalued()
	if ( testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is not evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	return iReturn;
}




/**
 * This method tests the property checksum=600 of the cTypeProperty class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testPropertyChecksum( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing a property of type CHECKSUM"<<endl;
	
	unsignedIntFib uiPropertyNumber = cTypeProperty::CHECKSUM;
	string szPropertyName = "checksum";
	
	cTypeProperty testTypeProperty( uiPropertyNumber );
	
	//check the getNumberOfProperty() methode
	if ( testTypeProperty.getNumberOfProperty() == uiPropertyNumber ){
	
		cout<<"The correct typenumber "<<szPropertyName<<"="<<uiPropertyNumber<<
			" for \"cTypeProperty\" is given. "<<endl;
	}else{
		cerr<<"Error: The typenumber given is not "<<szPropertyName<<"="<<
			uiPropertyNumber<<" for \"cTypeProperty\"; it is : "<<
			testTypeProperty.getNumberOfProperty()<<endl;
		iReturn++;
	}
	//check the getNameOfProperty() methode
	if ( testTypeProperty.getNameOfProperty() == szPropertyName ){
	
		cout<<"The correct name \""<<szPropertyName<<"\" for the property is given. "<<endl;
	}else{
		cerr<<"Error: The given name is not \""<<szPropertyName<<"\" for the property; it is : "<<
			testTypeProperty.getNameOfProperty()<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for integerdomain
	if ( ! testTypeProperty.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is correctly compatible to a integer domain.."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1 = new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vectorDomain = new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 2 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 2 elements."<<endl;
		iReturn++;
	}
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	delete vectorDomain;

	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains3( 3 );
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( testTypeProperty.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//TODO the checksum domain is not compatible to integer and real domains


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=testTypeProperty.getStandardDomain();
	
	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements=3;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain *domainElement1=standardDomainVector->getElementDomain( 1 );
			if ( domainElement1==NULL ){
			
				cerr<<"Error: The first element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement1->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement1;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=15;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
			
			//test domain of secound vector element
			cDomain *domainElement2=standardDomainVector->getElementDomain( 2 );
			if ( domainElement2==NULL ){
			
				cerr<<"Error: The secound element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement2->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The secound element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement2;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=255;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The secound element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
			
			//test domain of third vector element
			cDomain *domainElement3=standardDomainVector->getElementDomain( 3 );
			if ( domainElement3==NULL ){
			
				cerr<<"Error: The third element of the standarddomain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			} else if ( domainElement3->getType()=="DomainNaturalNumberBit" ){
			
				cout<<"The third element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
				
				cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement3;
				
				const doubleFib lowerBound=0;
				const doubleFib upperBound=255;
				
				if ( (domainNaturalNumberBit->getMinimum()==lowerBound) &&
						(domainNaturalNumberBit->getMaximum()==upperBound) ){
				
					cout<<"The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<lowerBound<<
						" to "<<upperBound<<", but it goes from "<<
						domainNaturalNumberBit->getMinimum()<<" to "<< 
						domainNaturalNumberBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The third element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
				iReturn++;
			}
			
		}else{
			cerr<<"Error: The standarddomain has "<<
				standardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete standardDomain;
	}

	//test the getUnit() method of the property, it should be ("R","G","B")
	vector<string> vecUnits = testTypeProperty.getUnit();
	
	if ( vecUnits.size()==3 ){

		if ( vecUnits[0]=="type" ){
		
			cout<<"The unit of the first vector domain is correctly \"type\". "<<endl;
		}else{
			cerr<<"Error: The unit of the first vector domain is \""<<vecUnits[0]
				<<"\", but should be \"type\"."<<endl;
			iReturn++;
		}
		
		if ( vecUnits[1]=="bits" ){
		
			cout<<"The unit of the secound vector domain is correctly \"bits\". "<<endl;
		}else{
			cerr<<"Error: The unit of the secound vector domain is \""<<vecUnits[0]
				<<"\", but should be \"bits\"."<<endl;
			iReturn++;
		}
		
		if ( vecUnits[2]=="bits" ){
		
			cout<<"The unit of the third vector domain is correctly \"bits\". "<<endl;
		}else{
			cerr<<"Error: The unit of the third vector domain is \""<<vecUnits[0]
				<<"\", but should be \"bits\"."<<endl;
			iReturn++;
		}
		
	}else{
		cerr<<"Error: The the number of vectorelements is not 3 but "<<
			vecUnits.size()<<" ."<<endl;
		iReturn++;

	}
	//test getOverwritenTyps()
	const list<cTypeProperty> liOverwirttenTyps = testTypeProperty.getOverwritenTyps();
	list<cTypeProperty> liToGiveBackPropertyTypes;
	liToGiveBackPropertyTypes.push_back( cTypeProperty( cTypeProperty::CHECKSUM ) );
	iReturn += comparePropertyTypeLists( liOverwirttenTyps, liToGiveBackPropertyTypes );
	
	//test isEvalued()
	if ( ! testTypeProperty.isEvalued() ){

		cout<<"The property of this type is correctly not evalued when a fib -object is evalued."<<endl;
	}else{
		cerr<<"Error: The property of this type is evalued when a fib -object is evalued."<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"Testing a property of type cTypeProperty() copyconstructor with a given domain"<<endl;
	
	cDomainNaturalNumberBit domainInt2( 8 );
	cout<<"cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );"<<endl;
	cTypeProperty typePropertyDomainInt( testTypeProperty, domainInt2 );
	
	if ( typePropertyDomainInt == testTypeProperty ){
	
		cout<<"The typePropertyDomainInt and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainInt and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 8 );
	vectorDomain = new cDomainVector( vecDomains1 );
	cout<<"cTypeProperty typePropertyDomain1( testTypeProperty, vectorDomainD1 );"<<endl;
	cTypeProperty typePropertyDomain1( testTypeProperty, *vectorDomain );
	delete vecDomains1[ 0 ];
	delete vectorDomain;

	if ( typePropertyDomain1 == testTypeProperty ){
	
		cout<<"The typePropertyDomain1 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomain1 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}
	
	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains4( 4 );
	vecDomains4[ 0 ] = new cDomainNaturalNumberBit( 24 );
	vecDomains4[ 1 ] = new cDomainNaturalNumberBit( 16 );
	vecDomains4[ 2 ] = new cDomainNaturalNumberBit( 8 );
	vecDomains4[ 3 ] = new cDomainNaturalNumberBit( 4 );
	vectorDomain = new cDomainVector( vecDomains4 );
	cout<<"cTypeProperty typePropertyDomainD4( testTypeProperty, vecDomainsD4 );"<<endl;
	cTypeProperty typePropertyDomainD4( testTypeProperty, *vectorDomain );
	delete vecDomains4[ 0 ];
	delete vecDomains4[ 1 ];
	delete vecDomains4[ 2 ];
	delete vecDomains4[ 3 ];
	delete vectorDomain;
	
	if ( typePropertyDomainD4 == testTypeProperty ){
	
		cout<<"The typePropertyDomainD4 and testTypeProperty are correctly equal."<<endl;
	}else{
		cerr<<"Error: The typePropertyDomainD4 and testTypeProperty are not equal."<<endl;
		iReturn++;
	}

	return iReturn;
}




/**
 * This method tests the equalElementType() method of the class.
 *
 * methods tested:
 * 	- bool equalElementType( const cTypeElement & typeElement ) const
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testEqualElementType( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equalElementType method "<<endl;

	//create typs to compare
	cout<<"cTypeProperty typeProperty1( 1 );"<<endl;
	cTypeProperty typeProperty1( 1 );
	
	cout<<"cTypeProperty typeProperty2( 2 );"<<endl;
	cTypeProperty typeProperty2( 2 );
	
	cout<<"cTypeProperty typeProperty3( 3 );"<<endl;
	cTypeProperty typeProperty3( 3 );

	
	cout<<"cTypeDimension typeDimension1D3( 3 );"<<endl;
	cTypeDimension typeDimension1D3( 3 );

	cout<<"cTypeInVar typeInVar( 1 );"<<endl;
	cTypeInVar typeInVar( 1 );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	if ( typeProperty1.equalElementType( typeProperty1 ) ){
	
		cout<<"The typeProperty1 is of the same type as typeProperty1. "<<endl;
	}else{
		cerr<<"Error: The typeProperty1 is not of the same type as typeProperty1."<<endl;
		iReturn++;
	}
	if ( ! typeProperty1.equalElementType( typeProperty2 ) ){
	
		cout<<"The typeProperty1 is not of the same type as typeProperty2. "<<endl;
	}else{
		cerr<<"Error: The typeProperty1 is of the same type as typeProperty2."<<endl;
		iReturn++;
	}
	if ( ! typeProperty1.equalElementType( typeProperty3 ) ){
	
		cout<<"The typeProperty1 is not of the same type as typeProperty3. "<<endl;
	}else{
		cerr<<"Error: The typeProperty1 is of the same type as typeProperty3."<<endl;
		iReturn++;
	}
	if ( ! typeProperty1.equalElementType( typeInVar ) ){
	
		cout<<"The typeProperty1 is not of the same type as typeInVar. "<<endl;
	}else{
		cerr<<"Error: The typeProperty1 is of the same type as typeInVar."<<endl;
		iReturn++;
	}
	if ( ! typeProperty1.equalElementType( typeDimension1D3 ) ){
	
		cout<<"The typeProperty1 is not of the same type as typeDimension1D3. "<<endl;
	}else{
		cerr<<"Error: The typeProperty1 is of the same type as typeDimension1D3."<<endl;
		iReturn++;
	}
	

	if ( typeProperty3.equalElementType( typeProperty3 ) ){
	
		cout<<"The typeProperty3 is of the same type as typeProperty3. "<<endl;
	}else{
		cerr<<"Error: The typeProperty3 is not of the same type as typeProperty3."<<endl;
		iReturn++;
	}
	if ( ! typeProperty3.equalElementType( typeProperty2 ) ){
	
		cout<<"The typeProperty3 is not of the same type as typeProperty2. "<<endl;
	}else{
		cerr<<"Error: The typeProperty3 is of the same type as typeProperty2."<<endl;
		iReturn++;
	}
	if ( ! typeProperty3.equalElementType( typeProperty1 ) ){
	
		cout<<"The typeProperty3 is not of the same type as typeProperty1. "<<endl;
	}else{
		cerr<<"Error: The typeProperty3 is of the same type as typeProperty1."<<endl;
		iReturn++;
	}
	if ( ! typeProperty3.equalElementType( typeDimension1D3 ) ){
	
		cout<<"The typeProperty3 is not of the same type as typeDimension1D3. "<<endl;
	}else{
		cerr<<"Error: The typeProperty3 is of the same type as typeDimension1D3."<<endl;
		iReturn++;
	}
	if ( ! typeProperty3.equalElementType( typeInVar ) ){
	
		cout<<"The typeProperty3 is not of the same type as typeInVar. "<<endl;
	}else{
		cerr<<"Error: The typeProperty3 is of the same type as typeInVar."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests a in the xml -format stored cDomainVector with
 * cDomainNaturalNumberBit domains.
 *
 * @param szFilename the name of the file wher the cDomainNaturalNumberBit is stored
 * @param uiPropertyType the type of the property
 * @param bHasDomain true if the type was saved with his domain
 * @param uiNumberOfElements the number of elements in the vector domain;
 * 	every element is an cDomainNaturalNumberBit
 * @param vecUiBits a vector with the bits the cDomainNaturalNumberBit
 * 	domains have
 * @param vecScalingfactor a vector with the scalingfactors for the
 * 	cDomainNaturalNumberBit domains have
 * @return the number of errors occured in the test
 */
int testXmlType( const string szFilename, const unsigned int uiPropertyType,
		bool bHasDomain, const unsigned int uiNumberOfElements,
		const vector<unsigned int> vecUiBits,
		const vector<double> vecScalingfactor ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored type:"<<endl;
	
	TiXmlDocument xmlDocVectorPosition( szFilename );
	bool loadOkay = xmlDocVectorPosition.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the type was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocVectorPosition );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlRootHandle( 0 );

	pXmlElement = xmlHandle.FirstChildElement().Element();
	
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();

		if ( szElementName == "property" ){
			cout<<"The root element is correctly named \"property\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"property\"."<<endl;
			iReturn++;
		}
		
		const char * pcAttributElements = pXmlElement->Attribute( "name" );
		
		cTypeProperty typeProperty( uiPropertyType );
		
		if ( pcAttributElements == NULL ){
			cerr<<"Error: The type has no attribute \"name\"."<<endl;
			iReturn++;
		}else if ( typeProperty.getNameOfProperty( ) == pcAttributElements ) {
			cout<<"The propertyname of the type is correctly \""<<
				typeProperty.getNameOfProperty() <<"\". "<<endl;
		}else{
			cerr<<"Error: The propertyname of the loaded type is \""<<
				pcAttributElements <<"\", but should be \""<<
				typeProperty.getNameOfProperty() <<"\"."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}

	//read the dimensionmappings
	xmlRootHandle = xmlHandle.FirstChildElement();

	
	if ( bHasDomain ){
	//check the domain of the type
		pXmlElement = xmlRootHandle.FirstChild( "vector" ).Element();
		
		if ( pXmlElement ) {
			string szElementName = pXmlElement->Value();
	
			if ( szElementName == "vector" ){
				cout<<"The root element is correctly named \"vector\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"vector\"."<<endl;
				iReturn++;
			}
			
			int iNumberOfElementsLoaded = 0;
			const char * pcAttributElements = pXmlElement->Attribute( "elements",
				&iNumberOfElementsLoaded );
			
			if ( pcAttributElements == NULL ){
				cerr<<"Error: The domain has no attribute \"elements\"."<<endl;
				iReturn++;
			}else if ( iNumberOfElementsLoaded == (int)uiNumberOfElements ) {
				cout<<"The number of elements of the domain are correctly \""<<
					uiNumberOfElements <<"\". "<<endl;
			}else{
				cerr<<"Error: The number of elements of the loaded domain are \""<<
					iNumberOfElementsLoaded <<"\", but should be \""<<
					uiNumberOfElements <<"\"."<<endl;
				iReturn++;
			}
	
		}else{// pXmlElement == NULL ->no root handle
			cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
			return iReturn;
		}
		
		TiXmlHandle xmlDomainHandle( 0 );
		xmlDomainHandle = xmlRootHandle.FirstChildElement( "vector" );
	
		pXmlElement = xmlDomainHandle.FirstChild().Element();
		unsigned int uiActualDimension = 0;
		//for every subdomain
		for( uiActualDimension = 0; pXmlElement; 
				pXmlElement = pXmlElement->NextSiblingElement(), uiActualDimension++ ){
	
			unsigned int uiBits = vecUiBits[ uiActualDimension ];
			double dScalingfactor = vecScalingfactor[ uiActualDimension ];
		
			// should always have a valid root but handle gracefully if it does
			string szElementName = pXmlElement->Value();
	
			if ( szElementName == "naturalNumberB" ){
				cout<<"The  element is correctly named \"naturalNumberB\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the element is \""<< szElementName <<"\" and not \"naturalNumberB\"."<<endl;
				iReturn++;
			}
			
			int iBitsLoaded = 0;
			const char * pcAttributBits = pXmlElement->Attribute( "bit", &iBitsLoaded );
			
			if ( pcAttributBits == NULL ){
				cerr<<"Error: The domain has no attribute bits."<<endl;
				iReturn++;
			}else if ( iBitsLoaded == (int)uiBits ) {
				cout<<"The number of bits of the domain are correctly \""<< uiBits <<"\". "<<endl;
			}else{
				cerr<<"Error: The number of bits of the loaded domain are \""<< iBitsLoaded
					<<"\", but should be \""<< uiBits <<"\"."<<endl;
				iReturn++;
			}
	
			const char * pcAttributeScalingfactor =
				pXmlElement->Attribute( "scalingfactor" );
			
			longFib lfMantissa;
			longFib lfExponent;
			decomposeDoubleFib( dScalingfactor, & lfMantissa, & lfExponent );
			
			long lMantissa = lfMantissa;
			long lExponent = lfExponent;
	
			char szScalingfactorBuffer[128];
			szScalingfactorBuffer[0] = 0;
			sprintf ( szScalingfactorBuffer, "%li * 2^(%li)", lMantissa, lExponent );
			
			string szScalingfactor( szScalingfactorBuffer );
			
			if ( ( dScalingfactor == 1.0 ) && ( pcAttributeScalingfactor == NULL ) ){
				//no scalingfactor needed
				cout<<"No scalingfactor attribut. This is correct because the scalingfactor is 1.0 . "<<endl;
			}else{
				if ( pcAttributeScalingfactor == NULL ){
					cerr<<"Error: The domain has no attribute scalingfactor."<<endl;
					iReturn++;
				}else if ( szScalingfactor == pcAttributeScalingfactor ) {
					cout<<"The scalingfactor of the domain is correctly \""<< pcAttributeScalingfactor <<"\". "<<endl;
				}else{
					cerr<<"Error: The scalingfactor of the loaded domain is \""<< pcAttributeScalingfactor
						<<"\", but should be \""<< dScalingfactor <<"\" (=\""<< szScalingfactor <<"\")."<<endl;
					iReturn++;
				}
			}
		}
		
		if ( uiActualDimension == uiNumberOfElements ){
			cout<<"The number of subdomains is correct. "<<endl;
		
		}else{
			cerr<<"Error: The number of subdomains is "<< uiActualDimension <<
				", but should be "<< uiNumberOfElements <<"."<<endl;
			iReturn++;
		}
	}

	return iReturn;
}


/**
 * This method storeXml() method of the class.
 *
 * methods tested:
 * 	- bool storeXml( ostringstream & ostream ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStoreXml( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple type property of type 1"<<endl;

	unsigned int uiPropertyType = 1;
	cout<<"cTypeProperty typeProperty1( "<< uiPropertyType <<" );"<<endl;
	cTypeProperty typeProperty1( uiPropertyType );

	vector<unsigned int> vecDomainE0Bits( 0 );
	vector<double> vecDomainE0Scalingfactor( 0 );

	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeProperty1.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeProperty1.storeXml( *fileXml );"<<endl;
	bool bStoreSuccesfull = typeProperty1.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, uiPropertyType, false, 0,
		vecDomainE0Bits, vecDomainE0Scalingfactor );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple propertytype of type 2 and an domain"<<endl;
	
	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomains1( 1 );
	cout<<"vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomains1[ 0 ] = new cDomainNaturalNumberBit( 4 );
	cout<<"cDomainVector domainVectorE1( vecDomains1 );"<<endl;
	cDomainVector domainVectorE1( vecDomains1 );
	delete vecDomains1[ 0 ];
	
	vector<unsigned int> vecDomainE1Bits(1);
	vecDomainE1Bits[ 0 ] = 4;
	vector<double> vecDomainE1Scalingfactor(1);
	vecDomainE1Scalingfactor[ 0 ] = 1.0;

	uiPropertyType = 2;
	cout<<"cTypeProperty typeProperty2( "<< uiPropertyType <<" );"<<endl;
	cTypeProperty typeProperty2( uiPropertyType );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeProperty2.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeProperty2.storeXml( *fileXml, &domainVectorE1 );"<<endl;
	bStoreSuccesfull = typeProperty2.storeXml( *fileXml, &domainVectorE1 );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, uiPropertyType, true, 1,
		vecDomainE1Bits, vecDomainE1Scalingfactor );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple propertytype of type 2003 and an domain"<<endl;

	uiPropertyType = 2003;
	cout<<"cTypeProperty typeProperty2003( "<< uiPropertyType <<" );"<<endl;
	cTypeProperty typeProperty2003( uiPropertyType );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeProperty2003.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeProperty2003.storeXml( *fileXml, &domainVectorE1 );"<<endl;
	bStoreSuccesfull = typeProperty2003.storeXml( *fileXml, &domainVectorE1 );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, uiPropertyType, true, 1,
		vecDomainE1Bits, vecDomainE1Scalingfactor );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple propertytype of type 1 and an domain"<<endl;
	
	//create vector domain with tree elements
	cout<<"vector<unsignedIntFib> dimensionMappingD3( 3 );"<<endl;
	vector<unsignedIntFib> dimensionMappingD3( 3 );
	cout<<"dimensionMappingD3[0] = 4;"<<endl;
	dimensionMappingD3[0] = 4;
	cout<<"dimensionMappingD3[1] = 2;"<<endl;
	dimensionMappingD3[1] = 2;
	cout<<"dimensionMappingD3[2] = 46;"<<endl;
	dimensionMappingD3[2] = 46;

	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 1, 1.0 );"<<endl;
	vecDomains3[ 0 ] = new cDomainNaturalNumberBit( 1, 1.0 );
	cout<<"vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 2, 0.125 );"<<endl;
	vecDomains3[ 1 ] = new cDomainNaturalNumberBit( 2, 0.125 );
	cout<<"vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 3, 3.0 );"<<endl;
	vecDomains3[ 2 ] = new cDomainNaturalNumberBit( 3, 3.0 );
	cout<<"cDomainVector domainVectorE3( vecDomains1 );"<<endl;
	cDomainVector domainVectorE3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	vector<unsigned int> vecDomainE3Bits( 3 );
	vecDomainE3Bits[ 0 ] = 1;
	vecDomainE3Bits[ 1 ] = 2;
	vecDomainE3Bits[ 2 ] = 3;
	vector<double> vecDomainE3Scalingfactor( 3 );
	vecDomainE3Scalingfactor[ 0 ] = 1.0;
	vecDomainE3Scalingfactor[ 1 ] = 0.125;
	vecDomainE3Scalingfactor[ 2 ] = 3.0;

	uiPropertyType = 1;
	cout<<"cTypeProperty typeProperty1Dom( "<< uiPropertyType <<" );"<<endl;
	cTypeProperty typeProperty1Dom( uiPropertyType );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeProperty1Dom.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeProperty1Dom.storeXml( *fileXml, &domainVectorE3 );"<<endl;
	bStoreSuccesfull = typeProperty1Dom.storeXml( *fileXml, &domainVectorE3 );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, uiPropertyType, true, 3,
		vecDomainE3Bits, vecDomainE3Scalingfactor );


	return iReturn;
}


/**
 * This method store() method of the class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a type property of type 1"<<endl;

	unsigned int uiPropertyType = 1;
	cout<<"cTypeProperty typeProperty1( "<< uiPropertyType <<" );"<<endl;
	cTypeProperty typeProperty1( uiPropertyType );

	//test get compressed size
	unsigned int uiCompressedSize = 8 + 8;
	if ( (unsigned int)(typeProperty1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeProperty1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeProperty1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = typeProperty1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	unsigned char ucRestBit = cRestBit;
	if ( ( ucRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeProperty1[] = { (char)0x22,
		(char)0x01,   //type of the property
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeProperty1, 3 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a type property of type 2003"<<endl;

	uiPropertyType = 2003;
	cout<<"cTypeProperty typeProperty2003( "<< uiPropertyType <<" );"<<endl;
	cTypeProperty typeProperty2003( uiPropertyType );

	//test get compressed size
	uiCompressedSize = 8 + 64;
	if ( (unsigned int)(typeProperty2003.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeProperty2003.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeProperty2003.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeProperty2003.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	if ( ( ucRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeProperty2003[] = { (char)0x24,
		(char)0xD3, (char)0x07, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,   //type of the property
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeProperty2003, 10 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a type property of type 7 and 2 restbits"<<endl;

	uiPropertyType = 7;
	cout<<"cTypeProperty typeProperty7( "<< uiPropertyType <<" );"<<endl;
	cTypeProperty typeProperty7( uiPropertyType );

	//test get compressed size
	uiCompressedSize = 8 + 8;
	if ( (unsigned int)(typeProperty7.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeProperty7.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeProperty7.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x01;
	cNumberOfRestBit = 2;
	bStoreSuccesfull = typeProperty7.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	if ( ( ucRestBit == (unsigned char)(char)0x00 ) && ( cNumberOfRestBit == 2 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x00 and number of restbit should be 2. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeProperty7[] = { (char)0x89,
		(char)0x1C,   //type of the property
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeProperty7, 3 );


	return iReturn;
}















