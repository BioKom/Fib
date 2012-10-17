/**
 * @file tTypeDimension
 * file name: tTypeDimension.cpp
 * @author Betti Oesterholz
 * @date 04.06.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cTypeDimension.
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
 * This file contains the test for the class cTypeDimension,
 * which represents the type for dimension means positionsvector elements.
 *
 *
 *
 *  What's tested of class cTypeDimension:
 * 	- cTypeDimension( unsignedIntFib iNumberOfDimensions=2  )
 * 	- cTypeDimension( vector<unsignedIntFib> dimensionMapping  )
 * 	- cTypeDimension( const cTypeDimension &typeDimension )
 * 	- unsignedIntFib getType() const
 * 	- bool isCompatible( const cDomain &domain ) const
 * 	- cDomain *getStandardDomain( ) const
 * 	- bool equal( const cTypeElement &typeElement ) const
 * 	- bool operator==( const cTypeElement &typeElement ) const
 * 	- cTypeElement *clone() const
 * 	- unsignedIntFib getNumberOfDimensions() const
 * 	- unsignedIntFib getDimensionMapping( unsignedIntFib iDimensionNumber ) const
 * 	- bool setDimensionMapping( unsignedIntFib iDimensionNumber, unsignedIntFib iMapping )
 * 	- string getDimensionMappingName( unsignedIntFib iMapping ) const
 * 	- vector<string> getUnit()
 * 	- bool equalElementType( const cTypeElement & typeElement ) const
 * 	- bool storeXml( ostream & ostream, const cDomain * domain = NULL ) const
 * 	- unsignedLongFib getCompressedSize() const
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const
 *
 *
 */
/*
History:
04.06.2009  Oesterholz  created
10.11.2009  Oesterholz  store*(), getCompressedSize() and equalElementType() tested
13.05.2010  Oesterholz  the ordering of bits for the compressed storing corrected
04.04.2011  Oesterholz  storing to binary stream
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/


#include "version.h"

#include "cTypeDimension.h"
#include "cTypeProperty.h"
#include "cTypeInVar.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <iomanip>

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif


using namespace fib;
using namespace std;


int testCostructor( unsigned long &ulTestphase );//+getNumberOfDimension()
int testIsCompatibleGetStandardDomainD2( unsigned long &ulTestphase );
int testIsCompatibleGetStandardDomainD5( unsigned long &ulTestphase );
int testSetDimensionMapping( unsigned long &ulTestphase );
int test5DimensionObejct( unsigned long &ulTestphase );
int testGetDimensionMappingName( unsigned long &ulTestphase );
int testClone( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testGetUnit( unsigned long &ulTestphase );
int testEqualElementType( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );


int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cTypeDimension methods"<<endl;
	cout<<      "======================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testIsCompatibleGetStandardDomainD2( ulTestphase );
	iReturn += testIsCompatibleGetStandardDomainD5( ulTestphase );
	iReturn += testSetDimensionMapping( ulTestphase );
	iReturn += test5DimensionObejct( ulTestphase );
	iReturn += testGetDimensionMappingName( ulTestphase );
	iReturn += testClone( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testGetUnit( ulTestphase );
	iReturn += testEqualElementType( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );

	if ( iReturn==0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * This method tests the constructors and the getNumberOfDimension()
 * and getType() method of the cTypeDimension class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cTypeDimension"<<endl;

	cout<<"cTypeDimension typeDimension=cTypeDimension( );"<<endl;
	cTypeDimension typeDimension=cTypeDimension( );

	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension.getType()==(unsignedIntFib)(1) ){
	
		cout<<"The type of dimensions is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of dimensions is "<<
			typeDimension.getType()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension.getNumberOfDimensions()==(unsignedIntFib)(2) ){
	
		cout<<"The number of dimensions is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of dimensions is "<<
			typeDimension.getNumberOfDimensions()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	for ( unsignedIntFib actualDimension=0;
			actualDimension<=typeDimension.getNumberOfDimensions();
			actualDimension++ ){
			
		//check the default dimension mappings
		//dimension number 0 is not defined and the mapping should be 0
		if ( typeDimension.getDimensionMapping( actualDimension )==actualDimension ){
		
			cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
				actualDimension<<" . "<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
				typeDimension.getDimensionMapping( actualDimension )<<" but should be "<<
				actualDimension<<" ."<<endl;
			iReturn++;
		}
	}

	//check a dimension mapping for a not defined dimension
	if ( typeDimension.getDimensionMapping( 
			typeDimension.getNumberOfDimensions()+1 )==0 ){
	
		cout<<"The mapping for the undefined "<<
			(typeDimension.getNumberOfDimensions()+1)<<
			" dimension is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The mapping for the undefined "<<
			(typeDimension.getNumberOfDimensions()+1)<<
			" dimension is "<<
			typeDimension.getDimensionMapping( 
				typeDimension.getNumberOfDimensions()+1 )<<
			" but should be 0 ."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cTypeDimension with 5 dimensions"<<endl;

	cout<<"cTypeDimension typeDimension5=cTypeDimension( 5 );"<<endl;
	cTypeDimension typeDimension5=cTypeDimension( 5 );

	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension.getType()==(unsignedIntFib)(1) ){
	
		cout<<"The type of dimensions is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of dimensions is "<<
			typeDimension.getType()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension5.getNumberOfDimensions()==(unsignedIntFib)(5) ){
	
		cout<<"The number of dimensions is correctly 5 . "<<endl;
	}else{
		cerr<<"Error: The number of dimensions is "<<
			typeDimension5.getNumberOfDimensions()<<" but should be 5 ."<<endl;
		iReturn++;
	}

	for ( unsignedIntFib actualDimension=0;
			actualDimension<=typeDimension5.getNumberOfDimensions();
			actualDimension++ ){
			
		//check the default dimension mappings
		//dimension number 0 is not defined and the mapping should be 0
		if ( typeDimension5.getDimensionMapping( actualDimension )==actualDimension ){
		
			cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
				actualDimension<<" . "<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
				typeDimension5.getDimensionMapping( actualDimension )<<" but should be "<<
				actualDimension<<" ."<<endl;
			iReturn++;
		}
	}

	//check a dimension mapping for a not defined dimension
	if ( typeDimension5.getDimensionMapping( 
			typeDimension5.getNumberOfDimensions()+1 )==0 ){
	
		cout<<"The mapping for the undefined "<<
			(typeDimension5.getNumberOfDimensions()+1)<<
			" dimension is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The mapping for the undefined "<<
			(typeDimension5.getNumberOfDimensions()+1)<<
			" dimension is "<<
			typeDimension5.getDimensionMapping( 
				typeDimension5.getNumberOfDimensions()+1 )<<
			" but should be 0 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cTypeDimension with given mappings"<<endl;

	cout<<"vector<unsignedIntFib> dimensionMapping;"<<endl;
	vector<unsignedIntFib> dimensionMapping;
	cout<<"dimensionMapping.push_back( 3 );"<<endl;
	dimensionMapping.push_back( 3 );
	cout<<"dimensionMapping.push_back( 1 );"<<endl;
	dimensionMapping.push_back( 1 );
	cout<<"dimensionMapping.push_back( 4 );"<<endl;
	dimensionMapping.push_back( 4 );
	cout<<"dimensionMapping.push_back( 7 );"<<endl;
	dimensionMapping.push_back( 7 );

	cout<<"cTypeDimension typeDimensionMap1=cTypeDimension( dimensionMapping );"<<endl;
	cTypeDimension typeDimensionMap1=cTypeDimension( dimensionMapping );

	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension.getType()==(unsignedIntFib)(1) ){
	
		cout<<"The type of dimensions is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of dimensions is "<<
			typeDimension.getType()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimensionMap1.getNumberOfDimensions()==(unsignedIntFib)(4) ){
	
		cout<<"The number of dimensions is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of dimensions is "<<
			typeDimensionMap1.getNumberOfDimensions()<<" but should be 4 ."<<endl;
		iReturn++;
	}

	for ( unsignedIntFib actualDimension=1;
			actualDimension<=typeDimensionMap1.getNumberOfDimensions();
			actualDimension++ ){
			
		//dimension number 0 is not defined and the mapping should be 0
		if ( typeDimensionMap1.getDimensionMapping( actualDimension )==
				dimensionMapping[ actualDimension-1 ] ){
		
			cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
				dimensionMapping[ actualDimension-1 ]<<" . "<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
				typeDimensionMap1.getDimensionMapping( actualDimension )<<" but should be "<<
				dimensionMapping[ actualDimension-1 ]<<" ."<<endl;
			iReturn++;
		}
	}

	//check a dimension mapping for a not defined dimension
	if ( typeDimensionMap1.getDimensionMapping( 
			typeDimensionMap1.getNumberOfDimensions()+1 )==0 ){
	
		cout<<"The mapping for the undefined "<<
			(typeDimensionMap1.getNumberOfDimensions()+1)<<
			" dimension is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The mapping for the undefined "<<
			(typeDimensionMap1.getNumberOfDimensions()+1)<<
			" dimension is "<<
			typeDimensionMap1.getDimensionMapping( 
				typeDimensionMap1.getNumberOfDimensions()+1 )<<
			" but should be 0 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cTypeDimension with given mappings with duplicates"<<endl;

	cout<<"vector<unsignedIntFib> dimensionMappingDup;"<<endl;
	vector<unsignedIntFib> dimensionMappingDup;
	cout<<"dimensionMapping.push_back( 2 );"<<endl;
	dimensionMappingDup.push_back( 2 );
	cout<<"dimensionMapping.push_back( 3 );"<<endl;
	dimensionMappingDup.push_back( 3 );
	cout<<"dimensionMapping.push_back( 2 );"<<endl;
	dimensionMappingDup.push_back( 2 );
	cout<<"dimensionMapping.push_back( 1 );"<<endl;
	dimensionMappingDup.push_back( 1 );
	cout<<"dimensionMapping.push_back( 2 );"<<endl;
	dimensionMappingDup.push_back( 2 );

	cout<<"cTypeDimension typeDimensionMapDup=cTypeDimension( dimensionMappingDup );"<<endl;
	cTypeDimension typeDimensionMapDup=cTypeDimension( dimensionMappingDup );

	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension.getType()==(unsignedIntFib)(1) ){
	
		cout<<"The type of dimensions is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of dimensions is "<<
			typeDimension.getType()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimensionMapDup.getNumberOfDimensions()==(unsignedIntFib)(5) ){
	
		cout<<"The number of dimensions is correctly 5 . "<<endl;
	}else{
		cerr<<"Error: The number of dimensions is "<<
			typeDimensionMapDup.getNumberOfDimensions()<<" but should be 5 ."<<endl;
		iReturn++;
	}

	for ( unsignedIntFib actualDimension=1;
			actualDimension<=typeDimensionMapDup.getNumberOfDimensions();
			actualDimension++ ){
		
		if ( (actualDimension!=3) && (actualDimension!=5) ){
			//non duplicates
			//check the default dimension mappings
			if ( typeDimensionMapDup.getDimensionMapping( actualDimension )==
					dimensionMappingDup[ actualDimension-1 ] ){
			
				cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
					dimensionMappingDup[ actualDimension-1 ]<<" . "<<endl;
			}else{
				cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
					typeDimensionMapDup.getDimensionMapping( actualDimension )<<" but should be "<<
					dimensionMappingDup[ actualDimension-1 ]<<" ."<<endl;
				iReturn++;
			}
		}else{//duplicates; should be canged to 0

			if ( typeDimensionMapDup.getDimensionMapping( actualDimension )==0 ){
			
				cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
					0<<" . "<<endl;
			}else{
				cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
					typeDimensionMapDup.getDimensionMapping( actualDimension )<<" but should be "<<
					0<<" ."<<endl;
				iReturn++;
			}
		}
	}

	//check a dimension mapping for a not defined dimension
	if ( typeDimensionMapDup.getDimensionMapping( 
			typeDimensionMapDup.getNumberOfDimensions()+1 )==0 ){
	
		cout<<"The mapping for the undefined "<<
			(typeDimensionMapDup.getNumberOfDimensions()+1)<<
			" dimension is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The mapping for the undefined "<<
			(typeDimensionMapDup.getNumberOfDimensions()+1)<<
			" dimension is "<<
			typeDimensionMapDup.getDimensionMapping( 
				typeDimensionMapDup.getNumberOfDimensions()+1 )<<
			" but should be 0 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copy constructer of the cTypeDimension with 5 dimensions"<<endl;

	cout<<"cTypeDimension typeDimension5Copy=cTypeDimension( typeDimension5 );"<<endl;
	cTypeDimension typeDimension5Copy=cTypeDimension( typeDimension5 );

	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension.getType()==(unsignedIntFib)(1) ){
	
		cout<<"The type of dimensions is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of dimensions is "<<
			typeDimension.getType()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension5Copy.getNumberOfDimensions()==(unsignedIntFib)(5) ){
	
		cout<<"The number of dimensions is correctly 5 . "<<endl;
	}else{
		cerr<<"Error: The number of dimensions is "<<
			typeDimension5Copy.getNumberOfDimensions()<<" but should be 5 ."<<endl;
		iReturn++;
	}

	for ( unsignedIntFib actualDimension=0;
			actualDimension<=typeDimension5Copy.getNumberOfDimensions();
			actualDimension++ ){
			
		//check the default dimension mappings
		//dimension number 0 is not defined and the mapping should be 0
		if ( typeDimension5Copy.getDimensionMapping( actualDimension )==actualDimension ){
		
			cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
				actualDimension<<" . "<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
				typeDimension5Copy.getDimensionMapping( actualDimension )<<" but should be "<<
				actualDimension<<" ."<<endl;
			iReturn++;
		}
	}

	//check a dimension mapping for a not defined dimension
	if ( typeDimension5Copy.getDimensionMapping( 
			typeDimension5Copy.getNumberOfDimensions()+1 )==0 ){
	
		cout<<"The mapping for the undefined "<<
			(typeDimension5Copy.getNumberOfDimensions()+1)<<
			" dimension is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The mapping for the undefined "<<
			(typeDimension5Copy.getNumberOfDimensions()+1)<<
			" dimension is "<<
			typeDimension5Copy.getDimensionMapping( 
				typeDimension5Copy.getNumberOfDimensions()+1 )<<
			" but should be 0 ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copy constructing of the cTypeDimension with given mappings"<<endl;

	cout<<"cTypeDimension typeDimensionMap1Copy=cTypeDimension( typeDimensionMap1 );"<<endl;
	cTypeDimension typeDimensionMap1Copy=cTypeDimension( typeDimensionMap1 );

	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension.getType()==(unsignedIntFib)(1) ){
	
		cout<<"The type of dimensions is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of dimensions is "<<
			typeDimension.getType()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimensionMap1Copy.getNumberOfDimensions()==(unsignedIntFib)(4) ){
	
		cout<<"The number of dimensions is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of dimensions is "<<
			typeDimensionMap1Copy.getNumberOfDimensions()<<" but should be 4 ."<<endl;
		iReturn++;
	}

	for ( unsignedIntFib actualDimension=1;
			actualDimension<=typeDimensionMap1Copy.getNumberOfDimensions();
			actualDimension++ ){
			
		//dimension number 0 is not defined and the mapping should be 0
		if ( typeDimensionMap1Copy.getDimensionMapping( actualDimension )==
				dimensionMapping[ actualDimension-1 ] ){
		
			cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
				dimensionMapping[ actualDimension-1 ]<<" . "<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
				typeDimensionMap1Copy.getDimensionMapping( actualDimension )<<" but should be "<<
				dimensionMapping[ actualDimension-1 ]<<" ."<<endl;
			iReturn++;
		}
	}

	//check a dimension mapping for a not defined dimension
	if ( typeDimensionMap1Copy.getDimensionMapping( 
			typeDimensionMap1Copy.getNumberOfDimensions()+1 )==0 ){
	
		cout<<"The mapping for the undefined "<<
			(typeDimensionMap1Copy.getNumberOfDimensions()+1)<<
			" dimension is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The mapping for the undefined "<<
			(typeDimensionMap1Copy.getNumberOfDimensions()+1)<<
			" dimension is "<<
			typeDimensionMap1Copy.getDimensionMapping( 
				typeDimensionMap1Copy.getNumberOfDimensions()+1 )<<
			" but should be 0 ."<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests the isCompatible() and getStandardDomain() method of
 * the cTypeDimension class with 2 Dimensions.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testIsCompatibleGetStandardDomainD2( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the global standard domain for the cTypeDimension"<<endl;
	
	cout<<"cTypeDimension typeDimension=cTypeDimension( );"<<endl;
	cTypeDimension typeDimension=cTypeDimension( );

	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension.getType()==(unsignedIntFib)(1) ){
	
		cout<<"The type of dimensions is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of dimensions is "<<
			typeDimension.getType()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension.getNumberOfDimensions()==(unsignedIntFib)(2) ){
	
		cout<<"The number of dimensions is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The number of dimensions is "<<
			typeDimension.getNumberOfDimensions()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt=new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeDimension.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to a integer domain."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain=new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! typeDimension.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1=new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( ! typeDimension.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ]=new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ]=new cDomainNaturalNumberBit( 16 );
	vectorDomain=new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( typeDimension.isCompatible( *vectorDomain ) ){
	
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
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 8 );
	vectorDomain=new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeDimension.isCompatible( *vectorDomain ) ){
	
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
	cDomain *standardDomain = typeDimension.getStandardDomain();
	
	if ( standardDomain == NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType() == "DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector = (cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements = 2;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
			
			for ( unsignedIntFib actualElement = 1; actualElement <= uiStandardDomainVectorElements;
					actualElement++ ){
			
				//test domain of first vector element
				cDomain *domainElement = standardDomainVector->getElementDomain( actualElement );
				if ( domainElement == NULL ){
				
					cerr<<"Error: The "<<actualElement<<"'th element of the"<<
						" standarddomain is not given back, but the Nullpointer NULL."<<endl;
					iReturn++;
					
				} else if ( domainElement->getType() == "DomainNaturalNumberBit" ){
				
					cout<<"The "<<actualElement<<"'th element of the standarddomain is correctly an cDomainNaturalNumberBit domain. "<<endl;
					
					cDomainIntegerBasis *domainNaturalNumberBit = (cDomainIntegerBasis*)domainElement;
					
					const doubleFib lowerBound = 0;
					const doubleFib upperBound = 65535;
					
					if ( (domainNaturalNumberBit->getMinimum() == lowerBound) &&
							(domainNaturalNumberBit->getMaximum() == upperBound) ){
					
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
					cerr<<"Error: The "<<actualElement<<" element of the standarddomain is not of type cDomainNaturalNumberBit."<<endl;
					iReturn++;
				}
			}//for
		
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

	return iReturn;
}




/**
 * This method tests the isCompatible() and getStandardDomain() method of
 * the cTypeDimension class with 5 Dimensions.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testIsCompatibleGetStandardDomainD5( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the domain for a cTypeDimension with 5 dimensions"<<endl;
	
	cout<<"cTypeDimension typeDimension=cTypeDimension( 5 );"<<endl;
	cTypeDimension typeDimension=cTypeDimension( 5 );

	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension.getType()==(unsignedIntFib)(1) ){
	
		cout<<"The type of dimensions is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The type of dimensions is "<<
			typeDimension.getType()<<" but should be 1 ."<<endl;
		iReturn++;
	}
	
	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension.getNumberOfDimensions()==(unsignedIntFib)(5) ){
	
		cout<<"The number of dimensions is correctly 5 . "<<endl;
	}else{
		cerr<<"Error: The number of dimensions is "<<
			typeDimension.getNumberOfDimensions()<<" but should be 5 ."<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt=new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeDimension.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to a integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to a integer domain."<<endl;
		iReturn++;
	}
	delete domainInt;

	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain=new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! typeDimension.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 0 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 0 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with one elements
	vector<cDomainSingle*> vecDomains1( 1 );
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 16 );
	cDomainVector *vectorDomain1=new cDomainVector( vecDomains1 );
	
	//check the isCompatible() methode for vectordomain with 1 elements
	if ( ! typeDimension.isCompatible( *vectorDomain1 ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 1 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 1 elements."<<endl;
		iReturn++;
	}
	delete vecDomains1[ 0 ];
	delete vectorDomain1;

	//check compatible for vector domain with two elements
	vector<cDomainSingle*> vecDomains2( 2 );
	vecDomains2[ 0 ]=new cDomainNaturalNumberBit( 8 );
	vecDomains2[ 1 ]=new cDomainNaturalNumberBit( 16 );
	vectorDomain=new cDomainVector( vecDomains2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! typeDimension.isCompatible( *vectorDomain ) ){
	
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
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 24 );
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 8 );
	vectorDomain=new cDomainVector( vecDomains3 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeDimension.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;


	//check compatible for vector domain with tree elements
	vector<cDomainSingle*> vecDomains5( 5 );
	vecDomains5[ 0 ]=new cDomainNaturalNumberBit( 24 );
	vecDomains5[ 1 ]=new cDomainNaturalNumberBit( 16, 0.002 );
	vecDomains5[ 2 ]=new cDomainNaturalNumberBit( 8 );
	vecDomains5[ 3 ]=new cDomainNaturalNumberBit( 24 );
	vecDomains5[ 4 ]=new cDomainNaturalNumberBit( 32, 0.5 );
	vectorDomain=new cDomainVector( vecDomains5 );
	delete vecDomains5[ 0 ];
	delete vecDomains5[ 1 ];
	delete vecDomains5[ 2 ];
	delete vecDomains5[ 3 ];
	delete vecDomains5[ 4 ];

	//check the isCompatible() methode for vectordomain with 3 elements
	if ( typeDimension.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with 5 elements. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with 5 elements."<<endl;
		iReturn++;
	}
	delete vectorDomain;


	//test the getStandardDomain() method of the property
	cDomain *standardDomain=typeDimension.getStandardDomain();
	
	if ( standardDomain==NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *standardDomainVector=(cDomainVector*)standardDomain;

		unsignedIntFib uiStandardDomainVectorElements=5;
		
		if ( standardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standarddomainvector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
			
			for ( unsignedIntFib actualElement=1; actualElement<=uiStandardDomainVectorElements;
					actualElement++ ){
			
				//test domain of first vector element
				cDomain *domainElement=standardDomainVector->getElementDomain( actualElement );
				if ( domainElement==NULL ){
				
					cerr<<"Error: The "<<actualElement<<"'th element of the"<<
						" standarddomain is not given back, but the Nullpointer NULL."<<endl;
					iReturn++;
					
				} else if ( domainElement->getType()=="DomainNaturalNumberBit" ){
				
					cout<<"The "<<actualElement<<"'th element of the standarddomain is correctly an cDomainIntegerBasis domain. "<<endl;
					
					cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)domainElement;
					
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
					cerr<<"Error: The "<<actualElement<<
						" element of the standarddomain is not of type cDomainIntegerBasis."<<endl;
					iReturn++;
				}
			}//for
		
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

	return iReturn;
}


/**
 * This method tests the setDimensionMapping() method of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testSetDimensionMapping( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing method setDimensionMapping()"<<endl;

	cout<<"cTypeDimension typeDimension=cTypeDimension( 3 );"<<endl;
	cTypeDimension typeDimension=cTypeDimension( 3 );

	//check the setDimensionMapping() methode from cTypeDimension
	cout<<"typeDimension.setDimensionMapping( 1, 4 )"<<endl;
	if ( typeDimension.setDimensionMapping( 1, 4 ) ){
	
		cout<<"The mapping for the first dimension could be changed."<<endl;
	}else{
		cerr<<"Error: The mapping for the first dimension couldn't be changed."<<endl;
		iReturn++;
	}

	//check a dimension mapping for the changed dimension
	if ( typeDimension.getDimensionMapping( 1 )==4 ){
	
		cout<<"The mapping for the first dimension is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The mapping for the first dimension is "<<
			typeDimension.getDimensionMapping( 1 )<<
			" but should be 4 ."<<endl;
		iReturn++;
	}

	//check icf rest dimensionmapping whern't changed
	for ( unsignedIntFib actualDimension=2;
			actualDimension<=typeDimension.getNumberOfDimensions();
			actualDimension++ ){
			
		//check the default dimension mappings
		//dimension number 0 is not defined and the mapping should be 0
		if ( typeDimension.getDimensionMapping( actualDimension )==actualDimension ){
		
			cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
				actualDimension<<" . "<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
				typeDimension.getDimensionMapping( actualDimension )<<" but should be "<<
				actualDimension<<" ."<<endl;
			iReturn++;
		}
	}


	//check the setDimensionMapping() methode from cTypeDimension
	cout<<"typeDimension.setDimensionMapping( 1, 5 )"<<endl;
	if ( typeDimension.setDimensionMapping( 1, 5 ) ){
	
		cout<<"The mapping for the first dimension could be changed."<<endl;
	}else{
		cerr<<"Error: The mapping for the first dimension couldn't be changed."<<endl;
		iReturn++;
	}

	//check a dimension mapping for the changed dimension
	if ( typeDimension.getDimensionMapping( 1 )==5 ){
	
		cout<<"The mapping for the first dimension is correctly 5 . "<<endl;
	}else{
		cerr<<"Error: The mapping for the first dimension is "<<
			typeDimension.getDimensionMapping( 1 )<<
			" but should be 5 ."<<endl;
		iReturn++;
	}

	//check if rest dimensionmapping whern't changed
	for ( unsignedIntFib actualDimension=2;
			actualDimension<=typeDimension.getNumberOfDimensions();
			actualDimension++ ){
			
		//check the default dimension mappings
		//dimension number 0 is not defined and the mapping should be 0
		if ( typeDimension.getDimensionMapping( actualDimension )==actualDimension ){
		
			cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
				actualDimension<<" . "<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
				typeDimension.getDimensionMapping( actualDimension )<<" but should be "<<
				actualDimension<<" ."<<endl;
			iReturn++;
		}
	}

	//check the setDimensionMapping() methode from cTypeDimension
	cout<<"typeDimension.setDimensionMapping( 1, 2 )"<<endl;
	if ( !typeDimension.setDimensionMapping( 1, 2 ) ){
	
		cout<<"The mapping for the first dimension couldn't be changed to"<<
			" mapping 2 (becaus dimension 2 has allready this mapping)."<<endl;
	}else{
		cerr<<"Error: The mapping for the first dimension could be changed to"<<
			" mapping 2, but dimension 2 has allready this mapping."<<endl;
		iReturn++;
	}

	//check a dimension mapping for the changed dimension
	if ( typeDimension.getDimensionMapping( 1 )==5 ){
	
		cout<<"The mapping for the undefined first dimension is correctly 5 . "<<endl;
	}else{
		cerr<<"Error: The mapping for the undefined first dimension is "<<
			typeDimension.getDimensionMapping( 1 )<<
			" but should be 5 ."<<endl;
		iReturn++;
	}

	//check icf rest dimensionmapping whern't changed
	for ( unsignedIntFib actualDimension=2;
			actualDimension<=typeDimension.getNumberOfDimensions();
			actualDimension++ ){
			
		//check the default dimension mappings
		//dimension number 0 is not defined and the mapping should be 0
		if ( typeDimension.getDimensionMapping( actualDimension )==actualDimension ){
		
			cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
				actualDimension<<" . "<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
				typeDimension.getDimensionMapping( actualDimension )<<" but should be "<<
				actualDimension<<" ."<<endl;
			iReturn++;
		}
	}
	
	
	//check the setDimensionMapping() methode from cTypeDimension
	cout<<"typeDimension.setDimensionMapping( 1, 0 )"<<endl;
	if ( typeDimension.setDimensionMapping( 1, 0 ) ){
	
		cout<<"The mapping for the first dimension could be changed."<<endl;
	}else{
		cerr<<"Error: The mapping for the first dimension couldn't be changed."<<endl;
		iReturn++;
	}

	//check a dimension mapping for the changed dimension
	if ( typeDimension.getDimensionMapping( 1 )==0 ){
	
		cout<<"The mapping for the first dimension is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The mapping for the first dimension is "<<
			typeDimension.getDimensionMapping( 1 )<<
			" but should be 0 ."<<endl;
		iReturn++;
	}

	//check the setDimensionMapping() methode from cTypeDimension
	cout<<"typeDimension.setDimensionMapping( 3, 0 )"<<endl;
	if ( typeDimension.setDimensionMapping( 3, 0 ) ){
	
		cout<<"The mapping for the first dimension could be changed."<<endl;
	}else{
		cerr<<"Error: The mapping for the first dimension couldn't be changed."<<endl;
		iReturn++;
	}

	//check a dimension mapping for the changed dimension
	if ( typeDimension.getDimensionMapping( 3 )==0 ){
	
		cout<<"The mapping for the third dimension is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The mapping for the third dimension is "<<
			typeDimension.getDimensionMapping( 3 )<<
			" but should be 0 ."<<endl;
		iReturn++;
	}

	//check the setDimensionMapping() methode from cTypeDimension
	cout<<"typeDimension.setDimensionMapping( 3, 1 )"<<endl;
	if ( typeDimension.setDimensionMapping( 3, 1 ) ){
	
		cout<<"The mapping for the first dimension could be changed."<<endl;
	}else{
		cerr<<"Error: The mapping for the first dimension couldn't be changed."<<endl;
		iReturn++;
	}

	//check a dimension mapping for the changed dimension
	if ( typeDimension.getDimensionMapping( 3 )==1 ){
	
		cout<<"The mapping for the third dimension is correctly 1 . "<<endl;
	}else{
		cerr<<"Error: The mapping for the third dimension is "<<
			typeDimension.getDimensionMapping( 3 )<<
			" but should be 1 ."<<endl;
		iReturn++;
	}


	return iReturn;
}


/**
 * This method tests the constructor abd the setDimensionMapping()
 * method of the class on an cTypeDimension with 5 dimensions.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int test5DimensionObejct( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cTypeDimension object with 5 dimensions"<<endl;


	cout<<"cTypeDimension typeDimension=cTypeDimension( 5 );"<<endl;
	cTypeDimension typeDimension=cTypeDimension( 5 );

	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension.getNumberOfDimensions()==(unsignedIntFib)(5) ){
	
		cout<<"The number of dimensions is correctly 5 . "<<endl;
	}else{
		cerr<<"Error: The number of dimensions is "<<
			typeDimension.getNumberOfDimensions()<<" but should be 5 ."<<endl;
		iReturn++;
	}

	for ( unsignedIntFib actualDimension=0;
			actualDimension<=typeDimension.getNumberOfDimensions();
			actualDimension++ ){
			
		//check the default dimension mappings
		//dimension number 0 is not defined and the mapping should be 0
		if ( typeDimension.getDimensionMapping( actualDimension )==actualDimension ){
		
			cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
				actualDimension<<" . "<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
				typeDimension.getDimensionMapping( actualDimension )<<" but should be "<<
				actualDimension<<" ."<<endl;
			iReturn++;
		}
	}

	//check a dimension mapping for a not defined dimension
	if ( typeDimension.getDimensionMapping( 
			typeDimension.getNumberOfDimensions()+1 )==0 ){
	
		cout<<"The mapping for the undefined "<<
			(typeDimension.getNumberOfDimensions()+1)<<
			" dimension is correctly 0 . "<<endl;
	}else{
		cerr<<"Error: The mapping for the undefined "<<
			(typeDimension.getNumberOfDimensions()+1)<<
			" dimension is "<<
			typeDimension.getDimensionMapping( 
				typeDimension.getNumberOfDimensions()+1 )<<
			" but should be 0 ."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing method setDimensionMapping() on 5 dimension object"<<endl;

	//check the setDimensionMapping() methode from cTypeDimension
	if ( typeDimension.setDimensionMapping( 3, 7 ) ){
	
		cout<<"The mapping for the first dimension could be changed."<<endl;
	}else{
		cerr<<"Error: The mapping for the first dimension couldn't be changed."<<endl;
		iReturn++;
	}

	//check a dimension mapping for the changed dimension
	if ( typeDimension.getDimensionMapping( 3 )==7 ){
	
		cout<<"The mapping for the undefined first dimension is correctly 7 . "<<endl;
	}else{
		cerr<<"Error: The mapping for the undefined first dimension is "<<
			typeDimension.getDimensionMapping( 3 )<<
			" but should be 7 ."<<endl;
		iReturn++;
	}

	//check icf rest dimensionmapping whern't changed
	for ( unsignedIntFib actualDimension=0;
			actualDimension<=typeDimension.getNumberOfDimensions();
			actualDimension++ ){
		
		if ( actualDimension==3 ){
			continue;// skip trid dimension
		}
		//check the default dimension mappings
		//dimension number 0 is not defined and the mapping should be 0
		if ( typeDimension.getDimensionMapping( actualDimension )==actualDimension ){
		
			cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
				actualDimension<<" . "<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
				typeDimension.getDimensionMapping( actualDimension )<<" but should be "<<
				actualDimension<<" ."<<endl;
			iReturn++;
		}
	}

	if ( !typeDimension.setDimensionMapping( 1, 2 ) ){
	
		cout<<"The mapping for the first dimension couldn't be changed to"<<
			" mapping 2 (becaus dimension 2 has allready this mapping)."<<endl;
	}else{
		cerr<<"Error: The mapping for the first dimension could be changed to"<<
			" mapping 2, but dimension 2 has allready this mapping."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the getDimensionMappingName() method of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testGetDimensionMappingName( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getDimensionMappingName() method for existing mappin gconstants"<<endl;

	cout<<"cTypeDimension typeDimension=cTypeDimension( );"<<endl;
	cTypeDimension typeDimension=cTypeDimension( );


	//check the getDimensionMappingName() methode for a constant
	if ( typeDimension.getDimensionMappingName( cTypeDimension::DIRECTION_NONE )=="none" ){
	
		cout<<"The mapping for the constant DIRECTION_NONE is correctly \"none\". "<<endl;
	}else{
		cerr<<"Error: The mapping for the constant DIRECTION_NONE is "<<
			typeDimension.getDimensionMappingName( cTypeDimension::DIRECTION_NONE )<<
			" but should be \"none\"."<<endl;
		iReturn++;
	}

	//check the getDimensionMappingName() methode for a number
	if ( typeDimension.getDimensionMappingName( 0 )=="none" ){
	
		cout<<"The mapping for the number 0 is correctly \"none\". "<<endl;
	}else{
		cerr<<"Error: The mapping for the number 0 is "<<
			typeDimension.getDimensionMappingName( 0 )<<
			" but should be \"none\"."<<endl;
		iReturn++;
	}

	//check the getDimensionMappingName() methode for a constant
	if ( typeDimension.getDimensionMappingName( cTypeDimension::DIRECTION_HORIZONTAL )=="horizontal" ){
	
		cout<<"The mapping for the constant DIRECTION_HORIZONTAL is correctly \"horizontal\". "<<endl;
	}else{
		cerr<<"Error: The mapping for the constant DIRECTION_HORIZONTAL is "<<
			typeDimension.getDimensionMappingName( cTypeDimension::DIRECTION_HORIZONTAL )<<
			" but should be \"horizontal\"."<<endl;
		iReturn++;
	}

	//check the getDimensionMappingName() methode for a number
	if ( typeDimension.getDimensionMappingName( 1 )=="horizontal" ){
	
		cout<<"The mapping for the number 1 is correctly \"horizontal\". "<<endl;
	}else{
		cerr<<"Error: The mapping for the number 1 is "<<
			typeDimension.getDimensionMappingName( 1 )<<
			" but should be \"horizontal\"."<<endl;
		iReturn++;
	}

	//check the getDimensionMappingName() methode for a constant
	if ( typeDimension.getDimensionMappingName( cTypeDimension::DIRECTION_VERTICAL )=="vertical" ){
	
		cout<<"The mapping for the constant DIRECTION_VERTICAL is correctly \"vertical\". "<<endl;
	}else{
		cerr<<"Error: The mapping for the constant DIRECTION_VERTICAL is "<<
			typeDimension.getDimensionMappingName( cTypeDimension::DIRECTION_VERTICAL )<<
			" but should be \"vertical\"."<<endl;
		iReturn++;
	}

	//check the getDimensionMappingName() methode for a number
	if ( typeDimension.getDimensionMappingName( 2 )=="vertical" ){
	
		cout<<"The mapping for the number 2 is correctly \"vertical\". "<<endl;
	}else{
		cerr<<"Error: The mapping for the number 2 is "<<
			typeDimension.getDimensionMappingName( 2 )<<
			" but should be \"vertical\"."<<endl;
		iReturn++;
	}

	//check the getDimensionMappingName() methode for a constant
	if ( typeDimension.getDimensionMappingName( cTypeDimension::DIRECTION_DEPTH )=="depth" ){
	
		cout<<"The mapping for the constant DIRECTION_DEPTH is correctly \"depth\". "<<endl;
	}else{
		cerr<<"Error: The mapping for the constant DIRECTION_DEPTH is "<<
			typeDimension.getDimensionMappingName( cTypeDimension::DIRECTION_DEPTH )<<
			" but should be \"depth\"."<<endl;
		iReturn++;
	}

	//check the getDimensionMappingName() methode for a number
	if ( typeDimension.getDimensionMappingName( 3 )=="depth" ){
	
		cout<<"The mapping for the number 3 is correctly \"depth\". "<<endl;
	}else{
		cerr<<"Error: The mapping for the number 3 is "<<
			typeDimension.getDimensionMappingName( 3 )<<
			" but should be \"depth\"."<<endl;
		iReturn++;
	}

	//check the getDimensionMappingName() methode for a constant
	if ( typeDimension.getDimensionMappingName( cTypeDimension::DIRECTION_TIME )=="time" ){
	
		cout<<"The mapping for the constant DIRECTION_TIME is correctly \"time\". "<<endl;
	}else{
		cerr<<"Error: The mapping for the constant DIRECTION_TIME is "<<
			typeDimension.getDimensionMappingName( cTypeDimension::DIRECTION_TIME )<<
			" but should be \"time\"."<<endl;
		iReturn++;
	}

	//check the getDimensionMappingName() methode for a number
	if ( typeDimension.getDimensionMappingName( 4 )=="time" ){
	
		cout<<"The mapping for the number 4 is correctly \"time\". "<<endl;
	}else{
		cerr<<"Error: The mapping for the number 4 is "<<
			typeDimension.getDimensionMappingName( 4 )<<
			" but should be \"time\"."<<endl;
		iReturn++;
	}


	/*check the getDimensionMappingName() methode for a number otside of 
	mapping with name*/
	if ( typeDimension.getDimensionMappingName( 5 )=="5" ){
	
		cout<<"The mapping for the number 5 is correctly \"5\". "<<endl;
	}else{
		cerr<<"Error: The mapping for the number 5 is "<<
			typeDimension.getDimensionMappingName( 5 )<<
			" but should be \"\"."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the clone() method of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testClone( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the clone() method"<<endl;

	cout<<"cTypeDimension typeDimension=cTypeDimension( 4 );"<<endl;
	cTypeDimension typeDimension=cTypeDimension( 4 );

	cout<<"cTypeDimension *typeDimensionClone1=typeDimension.clone();"<<endl;
	cTypeDimension *typeDimensionClone1=typeDimension.clone();


	cout<<endl<<"checking the clone:"<<endl;
	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimensionClone1->getNumberOfDimensions()==(unsignedIntFib)(4) ){
	
		cout<<"The number of dimensions is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of dimensions is "<<
			typeDimensionClone1->getNumberOfDimensions()<<" but should be 4 ."<<endl;
		iReturn++;
	}

	for ( unsignedIntFib actualDimension=0;
			actualDimension<=typeDimensionClone1->getNumberOfDimensions();
			actualDimension++ ){
			
		//check the default dimension mappings
		//dimension number 0 is not defined and the mapping should be 0
		if ( typeDimensionClone1->getDimensionMapping( actualDimension )==actualDimension ){
		
			cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
				actualDimension<<" . "<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
				typeDimensionClone1->getDimensionMapping( actualDimension )<<" but should be "<<
				actualDimension<<" ."<<endl;
			iReturn++;
		}
	}
	delete typeDimensionClone1;


	cout<<endl<<"checking the original:"<<endl;
	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension.getNumberOfDimensions()==(unsignedIntFib)(4) ){
	
		cout<<"The number of dimensions is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of dimensions is "<<
			typeDimension.getNumberOfDimensions()<<" but should be 4 ."<<endl;
		iReturn++;
	}

	for ( unsignedIntFib actualDimension=0;
			actualDimension<=typeDimension.getNumberOfDimensions();
			actualDimension++ ){
			
		//check the default dimension mappings
		//dimension number 0 is not defined and the mapping should be 0
		if ( typeDimension.getDimensionMapping( actualDimension )==actualDimension ){
		
			cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
				actualDimension<<" . "<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
				typeDimension.getDimensionMapping( actualDimension )<<" but should be "<<
				actualDimension<<" ."<<endl;
			iReturn++;
		}
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the clone() method on an object, which is not the original constructed object"<<endl;

	//first change to 0, so the dimensionmappings can be changed later
	for ( unsignedIntFib actualDimension=1;
			actualDimension<=typeDimension.getNumberOfDimensions();
			actualDimension++ ){
			
		//check the setDimensionMapping() methode from cTypeDimension
		if ( typeDimension.setDimensionMapping( actualDimension, 0 ) ){
		
			cout<<"The mapping for the "<<actualDimension<<
				" dimension could be changed to 0."<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<
				" dimension couldn't be changed to 0."<<endl;
			iReturn++;
		}
	}

	for ( unsignedIntFib actualDimension=1;
			actualDimension<=typeDimension.getNumberOfDimensions();
			actualDimension++ ){
			
		//check the setDimensionMapping() methode from cTypeDimension
		if ( typeDimension.setDimensionMapping( actualDimension, 5-actualDimension ) ){
		
			cout<<"The mapping for the "<<actualDimension<<
				" dimension could be changed to."<<5-actualDimension<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<
				" dimension couldn't be changed to."<<5-actualDimension<<endl;
			iReturn++;
		}
	}

	cout<<"typeDimensionClone1=typeDimension.clone();"<<endl;
	typeDimensionClone1=typeDimension.clone();

	cout<<endl<<"checking the clone:"<<endl;
	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimensionClone1->getNumberOfDimensions()==(unsignedIntFib)(4) ){
	
		cout<<"The number of dimensions is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of dimensions is "<<
			typeDimensionClone1->getNumberOfDimensions()<<" but should be 4 ."<<endl;
		iReturn++;
	}

	for ( unsignedIntFib actualDimension=1;
			actualDimension<=typeDimensionClone1->getNumberOfDimensions();
			actualDimension++ ){
			
		//check the default dimension mappings
		//dimension number 0 is not defined and the mapping should be 0
		if ( typeDimensionClone1->getDimensionMapping( actualDimension )==(5-actualDimension) ){
		
			cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
				(5-actualDimension)<<" . "<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
				typeDimensionClone1->getDimensionMapping( actualDimension )<<" but should be "<<
				(5-actualDimension)<<" ."<<endl;
			iReturn++;
		}
	}
	delete typeDimensionClone1;

	cout<<endl<<"checking the original:"<<endl;
	//check the getNumberOfDimensions() methode from cTypeDimension
	if ( typeDimension.getNumberOfDimensions()==(unsignedIntFib)(4) ){
	
		cout<<"The number of dimensions is correctly 4 . "<<endl;
	}else{
		cerr<<"Error: The number of dimensions is "<<
			typeDimension.getNumberOfDimensions()<<" but should be 4 ."<<endl;
		iReturn++;
	}

	for ( unsignedIntFib actualDimension=1;
			actualDimension<=typeDimension.getNumberOfDimensions();
			actualDimension++ ){
			
		//check the default dimension mappings
		//dimension number 0 is not defined and the mapping should be 0
		if ( typeDimension.getDimensionMapping( actualDimension )==(5-actualDimension) ){
		
			cout<<"The mapping for the "<<actualDimension<<" dimension is correctly "<<
				(5-actualDimension)<<" . "<<endl;
		}else{
			cerr<<"Error: The mapping for the "<<actualDimension<<" dimension is "<<
				typeDimension.getDimensionMapping( actualDimension )<<" but should be "<<
				(5-actualDimension)<<" ."<<endl;
			iReturn++;
		}
	}

	return iReturn;
}


/**
 * This method tests the equal() method and the operator== of two given
 * cTypeElement objects which are equal.
 *
 * @param typeElement1 the first type to compare
 * @param szNameType1 the name of the first type to compare
 * @param typeElement2 the secound type to compare to
 * @param szNameType2 the name of the secound type to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualTyps( const cTypeElement &typeElement1, const string &szNameType1,
	const cTypeElement &typeElement2, const string &szNameType2 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	if ( typeElement1.equal( typeElement2 ) ){
	
		cout<<"The "<<szNameType1<<" is equal to "<<szNameType2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameType1<<" is not equal to "<<
			szNameType2<<"."<<endl;
		iReturn++;
	}
	if ( typeElement1==typeElement2 ){
	
		cout<<"The "<<szNameType1<<" is equal (operator==) to "<<
			szNameType2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameType1<<" is not equal (operator==) to "<<
			szNameType2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}

/**
 * This method tests the equal() method and the operator== of two given
 * cTypeElement objects which are not equal.
 *
 * @param typeElement1 the first type to compare
 * @param szNameType1 the name of the first type to compare
 * @param typeElement2 the secound type to compare to
 * @param szNameType2 the name of the secound type to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualTyps( const cTypeElement &typeElement1, const string &szNameType1,
	const cTypeElement &typeElement2, const string &szNameType2 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	if ( ! typeElement1.equal( typeElement2 ) ){
	
		cout<<"The "<<szNameType1<<" is not equal to "<<szNameType2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameType1<<" is equal to "<<
			szNameType2<<"."<<endl;
		iReturn++;
	}
	if ( ! (typeElement1==typeElement2) ){
	
		cout<<"The "<<szNameType1<<" is not equal (operator==) to "<<
			szNameType2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameType1<<" is equal (operator==) to "<<
			szNameType2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the equal() method and the operator== of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testEqual( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equal method and the operator== "<<endl;

	//create cTypeDimensions to compare
	cout<<"cTypeDimension typeDimension1D2=cTypeDimension( );"<<endl;
	cTypeDimension typeDimension1D2=cTypeDimension( );
	cout<<"cTypeDimension typeDimension2D2=cTypeDimension( );"<<endl;
	cTypeDimension typeDimension2D2=cTypeDimension( );
	cout<<"cTypeDimension typeDimension1D3=cTypeDimension( 3 );"<<endl;
	cTypeDimension typeDimension1D3=cTypeDimension( 3 );
	cout<<"cTypeDimension typeDimension2D3=cTypeDimension( 3 );"<<endl;
	cTypeDimension typeDimension2D3=cTypeDimension( 3 );
	cout<<"cTypeDimension typeDimension1D5=cTypeDimension( 5 );"<<endl;
	cTypeDimension typeDimension1D5=cTypeDimension( 5 );
	cout<<"cTypeDimension typeDimension2D5=cTypeDimension( 5 );"<<endl;
	cTypeDimension typeDimension2D5=cTypeDimension( 5 );
	cout<<"cTypeDimension typeDimension1D5mod=cTypeDimension( 5 );"<<endl;
	cTypeDimension typeDimension1D5mod=cTypeDimension( 5 );
	cout<<"typeDimension1D5mod.setDimensionMapping( 2, 7 );"<<endl;
	typeDimension1D5mod.setDimensionMapping( 2, 7 );
	cout<<"typeDimension1D5mod.setDimensionMapping( 4, 2 );"<<endl;
	typeDimension1D5mod.setDimensionMapping( 4, 2 );
	cout<<"cTypeDimension typeDimension2D5mod=cTypeDimension( 5 );"<<endl;
	cTypeDimension typeDimension2D5mod=cTypeDimension( 5 );
	cout<<"typeDimension2D5mod.setDimensionMapping( 2, 7 );"<<endl;
	typeDimension2D5mod.setDimensionMapping( 2, 7 );
	cout<<"typeDimension2D5mod.setDimensionMapping( 4, 2 );"<<endl;
	typeDimension2D5mod.setDimensionMapping( 4, 2 );

	cout<<"cTypeProperty typeProperty( 1 );"<<endl;
	cTypeProperty typeProperty( 1 );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with typeDimension1D2
	cTypeElement * actualType = &typeDimension1D2;
	string szActualTypeName="typeDimension1D2";
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension1D2, "typeDimension1D2" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension2D2, "typeDimension2D2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D3, "typeDimension1D3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D3, "typeDimension2D3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D5, "typeDimension1D5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D5, "typeDimension2D5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D5mod, "typeDimension1D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D5mod, "typeDimension2D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeDimension2D2
	actualType=&typeDimension2D2;
	szActualTypeName="typeDimension2D2";
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension1D2, "typeDimension1D2" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension2D2, "typeDimension2D2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D3, "typeDimension1D3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D3, "typeDimension2D3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D5, "typeDimension1D5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D5, "typeDimension2D5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D5mod, "typeDimension1D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D5mod, "typeDimension2D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeDimension1D3
	actualType=&typeDimension1D3;
	szActualTypeName="typeDimension1D3";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D2, "typeDimension1D2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D2, "typeDimension2D2" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension1D3, "typeDimension1D3" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension2D3, "typeDimension2D3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D5, "typeDimension1D5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D5, "typeDimension2D5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D5mod, "typeDimension1D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D5mod, "typeDimension2D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeDimension2D3
	actualType=&typeDimension2D3;
	szActualTypeName="typeDimension2D3";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D2, "typeDimension1D2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D2, "typeDimension2D2" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension1D3, "typeDimension1D3" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension2D3, "typeDimension2D3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D5, "typeDimension1D5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D5, "typeDimension2D5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D5mod, "typeDimension1D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D5mod, "typeDimension2D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeDimension1D5
	actualType=&typeDimension1D5;
	szActualTypeName="typeDimension1D5";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D2, "typeDimension1D2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D2, "typeDimension2D2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D3, "typeDimension1D3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D3, "typeDimension2D3" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension1D5, "typeDimension1D5" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension2D5, "typeDimension2D5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D5mod, "typeDimension1D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D5mod, "typeDimension2D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeDimension2D5
	actualType=&typeDimension2D5;
	szActualTypeName="typeDimension2D5";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D2, "typeDimension1D2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D2, "typeDimension2D2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D3, "typeDimension1D3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D3, "typeDimension2D3" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension1D5, "typeDimension1D5" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension2D5, "typeDimension2D5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D5mod, "typeDimension1D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D5mod, "typeDimension2D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeDimension1D5mod
	actualType=&typeDimension1D5mod;
	szActualTypeName="typeDimension1D5mod";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D2, "typeDimension1D2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D2, "typeDimension2D2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D3, "typeDimension1D3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D3, "typeDimension2D3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D5, "typeDimension1D5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D5, "typeDimension2D5" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension1D5mod, "typeDimension1D5mod" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension2D5mod, "typeDimension2D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeDimension2D5mod
	actualType=&typeDimension2D5mod;
	szActualTypeName="typeDimension2D5mod";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D2, "typeDimension1D2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D2, "typeDimension2D2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D3, "typeDimension1D3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D3, "typeDimension2D3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D5, "typeDimension1D5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D5, "typeDimension2D5" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension1D5mod, "typeDimension1D5mod" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeDimension2D5mod, "typeDimension2D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeProperty
	actualType=&typeProperty;
	szActualTypeName="typeProperty";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D2, "typeDimension1D2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D2, "typeDimension2D2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D3, "typeDimension1D3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D3, "typeDimension2D3" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D5, "typeDimension1D5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D5, "typeDimension2D5" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension1D5mod, "typeDimension1D5mod" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeDimension2D5mod, "typeDimension2D5mod" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	return iReturn;
}



/**
 * This method tests the getUnit() method of the class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testGetUnit( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getUnit() method"<<endl;
	
	cout<<"cTypeDimension typeDimension=cTypeDimension( 5 );"<<endl;
	cTypeDimension typeDimension=cTypeDimension( 5 );

	vector<string> vecDimensionUnits=typeDimension.getUnit();

	if ( vecDimensionUnits.size()==5  ){
	
		cout<<"Ther are the correctly number of 5 units. "<<endl;

		//test getUnit()
		if ( vecDimensionUnits[0]=="m"  ){
		
			cout<<"The the unit of the dimension of the first element is correctly \"m\". "<<endl;
		}else{
			cerr<<"Error: The unit of the dimension of the first element is not \"m\" but \""<<
				vecDimensionUnits[0]<<"\" ."<<endl;
			iReturn++;
		}
	
		if ( vecDimensionUnits[1]=="m"  ){
		
			cout<<"The the unit of the dimension of the 2. element is correctly \"m\". "<<endl;
		}else{
			cerr<<"Error: The unit of the dimension of the 2. element is not \"m\" but \""<<
				vecDimensionUnits[1]<<"\" ."<<endl;
			iReturn++;
		}
		
		if ( vecDimensionUnits[2]=="m"  ){
		
			cout<<"The the unit of the dimension of the 3. element is correctly \"m\". "<<endl;
		}else{
			cerr<<"Error: The unit of the dimension of the 3. element is not \"m\" but \""<<
				vecDimensionUnits[2]<<"\" ."<<endl;
			iReturn++;
		}
		
		if ( vecDimensionUnits[3]=="s"  ){
		
			cout<<"The the unit of the dimension of the 4. element is correctly \"s\". "<<endl;
		}else{
			cerr<<"Error: The unit of the dimension of the 4. element is not \"s\" but \""<<
				vecDimensionUnits[3]<<"\" ."<<endl;
			iReturn++;
		}
		
		if ( vecDimensionUnits[4]==""  ){
		
			cout<<"The the unit of the dimension of the 5. element is correctly empty. "<<endl;
		}else{
			cerr<<"Error: The unit of the dimension of the 5. element is not empty but \""<<
				vecDimensionUnits[4]<<"\" ."<<endl;
			iReturn++;
		}

	}else{
		cerr<<"Error: Ther are "<<vecDimensionUnits.size()<<
			" units for the positionsvector and not 5 ."<<endl;
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

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equalElementType method "<<endl;

	//create cTypeDimensions to compare
	cout<<"cTypeDimension typeDimension1D2=cTypeDimension( );"<<endl;
	cTypeDimension typeDimension1D2  =cTypeDimension( );
	
	cout<<"cTypeDimension typeDimension1D3=cTypeDimension( 3 );"<<endl;
	cTypeDimension typeDimension1D3 = cTypeDimension( 3 );
	
	cout<<"cTypeDimension typeDimension1D5mod=cTypeDimension( 5 );"<<endl;
	cTypeDimension typeDimension1D5mod = cTypeDimension( 5 );
	cout<<"typeDimension1D5mod.setDimensionMapping( 2, 7 );"<<endl;
	typeDimension1D5mod.setDimensionMapping( 2, 7 );
	cout<<"typeDimension1D5mod.setDimensionMapping( 4, 2 );"<<endl;
	typeDimension1D5mod.setDimensionMapping( 4, 2 );

	cout<<"cTypeProperty typeProperty( 1 );"<<endl;
	cTypeProperty typeProperty( 1 );

	cout<<"cTypeInVar typeInVar( 1 );"<<endl;
	cTypeInVar typeInVar( 1 );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	if ( typeDimension1D2.equalElementType( typeDimension1D3 ) ){
	
		cout<<"The typeDimension1D2 is of the same type as typeDimension1D3. "<<endl;
	}else{
		cerr<<"Error: The typeDimension1D2 is not of the same type as typeDimension1D3."<<endl;
		iReturn++;
	}

	if ( typeDimension1D2.equalElementType( typeDimension1D5mod ) ){
	
		cout<<"The typeDimension1D2 is of the same type as typeDimension1D5mod. "<<endl;
	}else{
		cerr<<"Error: The typeDimension1D2 is not of the same type as typeDimension1D5mod."<<endl;
		iReturn++;
	}
	if ( ! typeDimension1D2.equalElementType( typeProperty ) ){
	
		cout<<"The typeDimension1D2 is not of the same type as typeProperty. "<<endl;
	}else{
		cerr<<"Error: The typeDimension1D2 is of the same type as typeProperty."<<endl;
		iReturn++;
	}

	if ( ! typeDimension1D2.equalElementType( typeInVar ) ){
	
		cout<<"The typeDimension1D2 is not of the same type as typeInVar. "<<endl;
	}else{
		cerr<<"Error: The typeDimension1D2 is of the same type as typeInVar."<<endl;
		iReturn++;
	}


	if ( typeDimension1D5mod.equalElementType( typeDimension1D3 ) ){
	
		cout<<"The typeDimension1D5mod is of the same type as typeDimension1D3. "<<endl;
	}else{
		cerr<<"Error: The typeDimension1D5mod is not of the same type as typeDimension1D3."<<endl;
		iReturn++;
	}

	if ( typeDimension1D5mod.equalElementType( typeDimension1D5mod ) ){
	
		cout<<"The typeDimension1D5mod is of the same type as typeDimension1D5mod. "<<endl;
	}else{
		cerr<<"Error: The typeDimension1D5mod is not of the same type as typeDimension1D5mod."<<endl;
		iReturn++;
	}
	if ( ! typeDimension1D5mod.equalElementType( typeProperty ) ){
	
		cout<<"The typeDimension1D5mod is not of the same type as typeProperty. "<<endl;
	}else{
		cerr<<"Error: The typeDimension1D5mod is of the same type as typeProperty."<<endl;
		iReturn++;
	}
	
	if ( ! typeDimension1D5mod.equalElementType( typeInVar ) ){
	
		cout<<"The typeDimension1D5mod is not of the same type as typeInVar. "<<endl;
	}else{
		cerr<<"Error: The typeDimension1D5mod is of the same type as typeInVar."<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests a in the xml -format stored cDomainVector with
 * cDomainNaturalNumberBit domains.
 *
 * @param szFilename the name of the file wher the cDomainNaturalNumberBit is stored
 * @param uiNumberOfElements the number of elements in the vector domain;
 * 	every element is an cDomainNaturalNumberBit
 * @param vecDimensionMapping the dimensionmapping for the dimension type 
 * @param bHasDomain true if the type was saved with his domain
 * @param vecUiBits a vector with the bits the cDomainNaturalNumberBit
 * 	domains have
 * @param vecScalingfactor a vector with the scalingfactors for the
 * 	cDomainNaturalNumberBit domains have
 * @return the number of errors occured in the test
 */
int testXmlType( const string szFilename, const unsigned int uiNumberOfElements,
		const vector<unsignedIntFib> vecDimensionMapping, bool bHasDomain,
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

		if ( szElementName == "dim" ){
			cout<<"The root element is correctly named \"dim\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"dim\"."<<endl;
			iReturn++;
		}
		
		int iNumberOfElementsLoaded = 0;
		const char * pcAttributElements = pXmlElement->Attribute( "count",
			&iNumberOfElementsLoaded );
		
		if ( pcAttributElements == NULL ){
			cerr<<"Error: The type has no attribute \"count\"."<<endl;
			iReturn++;
		}else if ( iNumberOfElementsLoaded == (int)uiNumberOfElements ) {
			cout<<"The number of elements of the type are correctly \""<<
				uiNumberOfElements <<"\". "<<endl;
		}else{
			cerr<<"Error: The number of elements of the loaded type are \""<<
				iNumberOfElementsLoaded <<"\", but should be \""<<
				uiNumberOfElements <<"\"."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}

	//read the dimensionmappings
	xmlRootHandle = xmlHandle.FirstChildElement();

	pXmlElement = xmlRootHandle.FirstChild( "dimension" ).Element();
	unsigned int uiActualDimension = 0;
	cTypeDimension typeDimension;
	//for every subdomain
	for( uiActualDimension = 0; pXmlElement;
			pXmlElement = pXmlElement->NextSiblingElement( "dimension" ), uiActualDimension++ ){

		// should always have a valid root but handle gracefully if it does
		string szElementName = pXmlElement->Value();

		if ( szElementName == "dimension" ){
			cout<<"The  element is correctly named \"dimension\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the element is \""<< szElementName <<"\" and not \"dimension\"."<<endl;
			iReturn++;
		}
		
		int iNumberLoaded = 0;
		const char * pcAttributNumber = pXmlElement->Attribute( "number", &iNumberLoaded );
		
		if ( pcAttributNumber == NULL ){
			cerr<<"Error: The dimension has no attribute number."<<endl;
			iReturn++;
		}else if ( ( 1 <= iNumberLoaded ) && ( iNumberLoaded <= (int)uiNumberOfElements ) ) {
			cout<<"The number of the dimension is \""<< iNumberLoaded <<"\". "<<endl;
		}else{
			cerr<<"Error: The number of the dimension is \""<< iNumberLoaded <<
				"\" this didn't lay in the range from 1 till "<<
				uiNumberOfElements <<" ."<<endl;
			iReturn++;
		}

		const char * pcAttributeDirection =
			pXmlElement->Attribute( "direction" );
		
		if ( pcAttributeDirection == NULL ){
			//no direction
			cerr<<"No direction attribut. "<<endl;
			iReturn++;
		}else{
			cout<<"The direction is: "<< pcAttributeDirection <<endl;
			if ( strlen( pcAttributeDirection ) == 0 ){
				cerr<<"Error: The direction string has the length 0 ."<<endl;
				iReturn++;
			}
			if ( ( 1 <= iNumberLoaded ) && ( iNumberLoaded <= (int)uiNumberOfElements ) ) {
				
				if ( typeDimension.getDimensionMappingName(
						vecDimensionMapping[ iNumberLoaded - 1 ] ) == pcAttributeDirection ) {
				
					cout<<"The direction is correct. "<<endl;
				}else{
					cerr<<"Error: The direction of the loaded dimension is \""<< pcAttributeDirection
						<<"\", but should be \""<< typeDimension.getDimensionMappingName(
							vecDimensionMapping[ iNumberLoaded - 1 ] ) <<"\"."<<endl;
					iReturn++;
				}
			}
		}
	}
	
	if ( uiActualDimension == uiNumberOfElements ){
		cout<<"The number of dimensions is correct. "<<endl;
	
	}else{
		cerr<<"Error: The number of dimensions is "<< uiActualDimension <<
			", but should be "<< uiNumberOfElements <<"."<<endl;
		iReturn++;
	}

	
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

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple type dimension with 0 dimensions"<<endl;
	
	cout<<"vector<unsignedIntFib> dimensionMappingD0( 0 );"<<endl;
	vector<unsignedIntFib> dimensionMappingD0;
	vector<unsigned int> vecDomainE0Bits( 0 );
	vector<double> vecDomainE0Scalingfactor( 0 );

	cout<<"cTypeDimension typeDimensionMapD0( dimensionMappingD0 );"<<endl;
	cTypeDimension typeDimensionMapD0( dimensionMappingD0 );

	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeDimensionMapD0.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeDimensionMapD0.storeXml( *fileXml );"<<endl;
	bool bStoreSuccesfull = typeDimensionMapD0.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, 0, dimensionMappingD0, false,
		vecDomainE0Bits, vecDomainE0Scalingfactor );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple type dimension with 1 dimension"<<endl;
	
	cout<<"vector<unsignedIntFib> dimensionMappingD1( 1 );"<<endl;
	vector<unsignedIntFib> dimensionMappingD1( 1 );
	cout<<"dimensionMappingD1[0] = 1;"<<endl;
	dimensionMappingD1[0] = 1;

	//create vector domain with one elements
	cout<<"vector<cDomainSingle*> vecDomains1( 1 );"<<endl;
	vector<cDomainSingle*> vecDomains1( 1 );
	cout<<"vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4 );"<<endl;
	vecDomains1[ 0 ]=new cDomainNaturalNumberBit( 4 );
	cout<<"cDomainVector domainVectorE1( vecDomains1 );"<<endl;
	cDomainVector domainVectorE1( vecDomains1 );
	delete vecDomains1[ 0 ];
	
	vector<unsigned int> vecDomainE1Bits(1);
	vecDomainE1Bits[ 0 ] = 4;
	vector<double> vecDomainE1Scalingfactor(1);
	vecDomainE1Scalingfactor[ 0 ] = 1.0;

	cout<<"cTypeDimension typeDimensionMapD1( dimensionMappingD1 );"<<endl;
	cTypeDimension typeDimensionMapD1( dimensionMappingD1 );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeDimensionMapD1.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeDimensionMapD1.storeXml( *fileXml );"<<endl;
	bStoreSuccesfull = typeDimensionMapD1.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, 1, dimensionMappingD1, false, vecDomainE1Bits, vecDomainE1Scalingfactor );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple type dimension with 1 dimension and an domain"<<endl;
	
	cout<<"dimensionMappingD1[0] = 3;"<<endl;
	dimensionMappingD1[0] = 3;

	cout<<"cTypeDimension typeDimensionMapD1Dom( dimensionMappingD1 );"<<endl;
	cTypeDimension typeDimensionMapD1Dom( dimensionMappingD1 );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeDimensionMapD1Dom.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeDimensionMapD1Dom.storeXml( *fileXml, &domainVectorE1 );"<<endl;
	bStoreSuccesfull = typeDimensionMapD1Dom.storeXml( *fileXml, &domainVectorE1 );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, 1, dimensionMappingD1, true, vecDomainE1Bits, vecDomainE1Scalingfactor );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple type dimension with 1 dimension in direction 2005 and an domain"<<endl;
	
	cout<<"dimensionMappingD1[0] = 2005;"<<endl;
	dimensionMappingD1[0] = 2005;

	cout<<"cTypeDimension typeDimensionMapD1Dom1( dimensionMappingD1 );"<<endl;
	cTypeDimension typeDimensionMapD1Dom1( dimensionMappingD1 );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeDimensionMapD1Dom1.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeDimensionMapD1Dom1.storeXml( *fileXml, &domainVectorE1 );"<<endl;
	bStoreSuccesfull = typeDimensionMapD1Dom1.storeXml( *fileXml, &domainVectorE1 );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, 1, dimensionMappingD1, true, vecDomainE1Bits, vecDomainE1Scalingfactor );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple type dimension with 3 dimension"<<endl;
	
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
	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1, 1.0 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 1, 1.0 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2, 0.125 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 2, 0.125 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3, 3.0 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 3, 3.0 );
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

	cout<<"cTypeDimension typeDimensionMapD3( dimensionMappingD3 );"<<endl;
	cTypeDimension typeDimensionMapD3( dimensionMappingD3 );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeDimensionMapD3.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeDimensionMapD3.storeXml( *fileXml, &domainVectorE3 );"<<endl;
	bStoreSuccesfull = typeDimensionMapD3.storeXml( *fileXml, &domainVectorE3 );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, 3, dimensionMappingD3, false, vecDomainE3Bits, vecDomainE3Scalingfactor );
	
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple type dimension"<<endl;
	
	//create vector domain with one elements
	cout<<"vector<unsignedIntFib> dimensionMappingD0( 0 );"<<endl;
	vector<unsignedIntFib> dimensionMappingD0;
	vector<unsigned int> vecDomainE0Bits( 0 );
	vector<double> vecDomainE0Scalingfactor( 0 );

	cout<<"cTypeDimension typeDimensionMapD0( dimensionMappingD0 );"<<endl;
	cTypeDimension typeDimensionMapD0( dimensionMappingD0 );

	//test get compressed size
	unsigned int uiCompressedSize = 8 + 16 + 16;
	if ( (unsigned int)(typeDimensionMapD0.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeDimensionMapD0.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeDimensionMapD0.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = typeDimensionMapD0.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeDimensionMapD0[] = { (char)0x0E,
		(char)0x02, (char)0x00, //length of parameterlist in byte
		(char)0x00, (char)0x00, //number of dimensione
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeDimensionMapD0, 6 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple type dimension with 1 dimension"<<endl;
	
	cout<<"vector<unsignedIntFib> dimensionMappingD1( 1 );"<<endl;
	vector<unsignedIntFib> dimensionMappingD1( 1 );
	cout<<"dimensionMappingD1[0] = 1;"<<endl;
	dimensionMappingD1[0] = 1;

	cout<<"cTypeDimension typeDimensionMapD1( dimensionMappingD1 );"<<endl;
	cTypeDimension typeDimensionMapD1( dimensionMappingD1 );

	//test get compressed size
	uiCompressedSize = 8 + 16 + 16 + 8;
	if ( (unsigned int)(typeDimensionMapD1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeDimensionMapD1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeDimensionMapD1.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeDimensionMapD1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeDimensionMapD1[] = { (char)0x0E,
		(char)0x03, (char)0x00, //length of parameterlist in byte
		(char)0x01, (char)0x00, //number of dimensione
		(char)0x01, // dimension
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeDimensionMapD1, 7 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple type dimension with 1 dimension in direction 500"<<endl;
	
	cout<<"vector<unsignedIntFib> dimensionMappingD1D500( 1 );"<<endl;
	vector<unsignedIntFib> dimensionMappingD1D500( 1 );
	cout<<"dimensionMappingD1D500[0] = 500;"<<endl;
	dimensionMappingD1D500[0] = 500;

	cout<<"cTypeDimension typeDimensionMapD1D500( dimensionMappingD1D500 );"<<endl;
	cTypeDimension typeDimensionMapD1D500( dimensionMappingD1D500 );

	//test get compressed size
	uiCompressedSize = 8 + 16 + 16 + 16;
	if ( (unsigned int)(typeDimensionMapD1D500.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeDimensionMapD1D500.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeDimensionMapD1D500.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeDimensionMapD1D500.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeDimensionMapD1D500[] = { (char)0x0E,
		(char)0x04, (char)0x00, //length of parameterlist in byte
		(char)0x01, (char)0x00, //number of dimensione
		(char)0xF4, (char)0x01, // dimension
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeDimensionMapD1D500, 8 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple type dimension with 3 dimensions"<<endl;
	
	cout<<"vector<unsignedIntFib> dimensionMappingD3( 3 );"<<endl;
	vector<unsignedIntFib> dimensionMappingD3( 3 );
	cout<<"dimensionMappingD3[0] = 4;"<<endl;
	dimensionMappingD3[0] = 4;
	cout<<"dimensionMappingD3[1] = 2;"<<endl;
	dimensionMappingD3[1] = 2;
	cout<<"dimensionMappingD3[2] = 46;"<<endl;
	dimensionMappingD3[2] = 46;

	cout<<"cTypeDimension typeDimensionMapD3( dimensionMappingD3 );"<<endl;
	cTypeDimension typeDimensionMapD3( dimensionMappingD3 );

	//test get compressed size
	uiCompressedSize = 8 + 16 + 16 + 3 * 8;
	if ( (unsigned int)(typeDimensionMapD3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeDimensionMapD3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeDimensionMapD3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeDimensionMapD3.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeDimensionMapD3[] = { (char)0x0E,
		(char)0x05, (char)0x00, //length of parameterlist in byte
		(char)0x03, (char)0x00, //number of dimensione
		(char)0x04,  (char)0x02,  (char)0x2E, // dimensions
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeDimensionMapD3, 9 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple type dimension with 3 dimensions a 3 Byte"<<endl;
	
	cout<<"vector<unsignedIntFib> dimensionMappingD3B( 3 );"<<endl;
	vector<unsignedIntFib> dimensionMappingD3B( 3 );
	cout<<"dimensionMappingD3B[0] = 4;"<<endl;
	dimensionMappingD3B[0] = 4;
	cout<<"dimensionMappingD3B[1] = 591832;"<<endl;
	dimensionMappingD3B[1] = 591832;
	cout<<"dimensionMappingD3B[2] = 2;"<<endl;
	dimensionMappingD3B[2] = 2;

	cout<<"cTypeDimension typeDimensionMapD3B( dimensionMappingD3B );"<<endl;
	cTypeDimension typeDimensionMapD3B( dimensionMappingD3B );

	//test get compressed size
	uiCompressedSize = 8 + 16 + 16 + 64;
	if ( (unsigned int)(typeDimensionMapD3B.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeDimensionMapD3B.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeDimensionMapD3B.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeDimensionMapD3B.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeDimensionMapD3B[] = { (char)0x0E,
		(char)0x0A, (char)0x00, //length of parameterlist in byte
		(char)0x03, (char)0x00, //number of dimensione
		(char)0x04, (char)0x00, (char)0x00, (char)0xfb, (char)0x20, (char)0x09, (char)0x00, (char)0x00, // dimensions
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeDimensionMapD3B, 14 );



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple type dimension with 3 dimensions and a 3 restbitsbits"<<endl;
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeDimensionMapD3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x07;
	cNumberOfRestBit = 3 ;
	bStoreSuccesfull = typeDimensionMapD3.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( (unsigned char)cRestBit == (char)0x01 ) && ( cNumberOfRestBit == 3 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x01 and number of restbit should be 3. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeDimensionMapD3R3[] = { (char)0x77, (char)0x28,
		(char)0x00, (char)0x18,
		(char)0x00, (char)0x20,
		(char)0x10, (char)0x70,
		(char)0x01 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeDimensionMapD3R3, 9 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple type dimension with 3 dimensions with maximum 4 Bits each"<<endl;
	
	cout<<"vector<unsignedIntFib> dimensionMappingD3B4( 3 );"<<endl;
	vector<unsignedIntFib> dimensionMappingD3B4( 3 );
	cout<<"dimensionMappingD3B4[0] = 1;"<<endl;
	dimensionMappingD3B4[0] = 1;
	cout<<"dimensionMappingD3B4[1] = 2;"<<endl;
	dimensionMappingD3B4[1] = 2;
	cout<<"dimensionMappingD3B4[2] = 9;"<<endl;
	dimensionMappingD3B4[2] = 9;

	cout<<"cTypeDimension typeDimensionMapD3B4( dimensionMappingD3B4 );"<<endl;
	cTypeDimension typeDimensionMapD3B4( dimensionMappingD3B4 );

	//test get compressed size
	uiCompressedSize = 8 + 16 + 16 + 16;
	if ( (unsigned int)(typeDimensionMapD3B4.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeDimensionMapD3B4.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeDimensionMapD3B4.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = typeDimensionMapD3B4.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeDimensionMapD3B4[] = { (char)0x0E,
		(char)0x04, (char)0x00, //length of parameterlist in byte
		(char)0x03, (char)0x00, //number of dimensione
		(char)0x41, (char)0x24, // dimensions
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeDimensionMapD3B4, 8 );
	
	return iReturn;
}






































