/**
 * @file tDomainReference
 * file name: tDomainReference.cpp
 * @author Betti Oesterholz
 * @date 13.02.2012
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cDomainReference.
 *
 * Copyright (C) @c GPL3 2012 Betti Oesterholz
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
 * This file contains the test for the class cDomainReference,
 * which represents the a reference to an other domain.
 *
 *
 *  What's tested of class cDomainReference:
 * 	- cDomainReference( const cTypeElement & inOriginalType, const vector<unsignedIntFib> vecInElementDomains )
 * 	- cDomainReference( const cDomainReference & domain )
 * 	- bool isReference() const
 * 	- bool isScalar() const
 * 	- bool isVector() const
 * 	- string getType() const
 * 	- cDomain * clone() const
 * 	- bool equal( const cDomain &domain ) const
 * 	- bool operator==( const cDomain &domain ) const
 * 	- const cTypeElement * getTypeElement() const
 * 	- const vector<unsignedIntFib> & getElement() const
 * 	- bool storeXml( ostream & ostream ) const
 * 	- unsignedIntFib getCompressedSize() const
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const
 */
/*
History:
13.02.2012  Oesterholz  created
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/



#include "version.h"

#include "cRoot.h"
#include "cDomainReference.h"
#include "cDomainVector.h"
#include "cDomainNaturalNumberBit.h"
#include "cVectorPosition.h"
#include "cTypeDimension.h"
#include "cTypeProperty.h"
#include "cTypeInVar.h"
#include "cTypeFibSet.h"

#include "tinyxml.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <iomanip>
#include <vector>

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif

using namespace fib;
using namespace std;


int testConstructor( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testClone( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );

int main(int argc,char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cDomainReference methods"<<endl;
	cout<<      "========================================="<<endl;

	iReturn += testConstructor( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testClone( ulTestphase );
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
 * This method tests the constructor and the getType(),
 * getNumberOfElements(), getElementDomain() methods of the cDomainReference 
 * class.
 *
 * methods tested:
 * 	- cDomainReference( const cTypeElement & inOriginalType, const vector<unsignedIntFib> vecInElementDomains )
 * 	- cDomainReference( const cDomainReference & domain )
 * 	- bool isReference() const
 * 	- bool isScalar() const
 * 	- bool isVector() const
 * 	- const cTypeElement * getTypeElement() const
 * 	- const vector<unsignedIntFib> & getElement() const
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testConstructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a simple reference domain"<<endl;

	cout<<"cTypeInVar inVar1( 1 );"<<endl;
	cTypeInVar inVar1( 1 );
	cout<<"cDomainReference domainReference0( inVar1 );"<<endl;
	cDomainReference domainReference0( inVar1 );

	vector<unsignedIntFib> vecCorrectElementDomains;

	//test the getType() method
	if ( domainReference0.getType()=="DomainReference" ){
	
		cout<<"The type of domainReference0 is correctly \"DomainReference\". "<<endl;
	}else{
		cerr<<"Error: The type of domainReference0 is "<<domainReference0.getType() <<
			" and not \"DomainReference\""<<endl;
		iReturn++;
	}
	
	//test the getTypeElement() method
	if ( inVar1.equal( *(domainReference0.getTypeElement() ) ) ){
	
		cout<<"The domainReference0 has correctly a type equal to inVar1 as type. "<<endl;
	}else{
		cerr<<"Error: The domainReference0 has not a type equal to inVar1 as type."<<endl;
		iReturn++;
	}
	//test the getTypeElement() method
	if ( vecCorrectElementDomains == domainReference0.getElement() ){
	
		cout<<"The domainReference0 has the correct element domain numbers. "<<endl;
	}else{
		cerr<<"Error: The domainReference0 has the wrong element domain numbers."<<endl;
		vector<unsignedIntFib> vecWrongElementDomains = domainReference0.getElement();
		cerr<<"   It has:          ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecWrongElementDomains.begin();
				itrNumber != vecWrongElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		cerr<<"   But should have: ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecCorrectElementDomains.begin();
				itrNumber != vecCorrectElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		iReturn++;
	}

	//test the isReference() method
	if ( domainReference0.isReference() ){
	
		cout<<"The domainReference0 is correctly a reference domain. "<<endl;
	}else{
		cerr<<"Error: The domainReference0 is not a reference domain ."<<endl;
		iReturn++;
	}
	//test the isScalar() method
	if ( ! domainReference0.isScalar() ){
	
		cout<<"The domainReference0 is correctly not a scalar domain. "<<endl;
	}else{
		cerr<<"Error: The domainReference0 is a scalar domain ."<<endl;
		iReturn++;
	}
	//test the isVector() method
	if ( ! domainReference0.isVector() ){
	
		cout<<"The domainReference0 is correctly not a vector domain. "<<endl;
	}else{
		cerr<<"Error: The domainReference0 is a vector domain ."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copy constructing a simple reference domain (domainReference0)"<<endl;

	cout<<"cDomainReference domainReference0Copy( domainReference0 );"<<endl;
	cDomainReference domainReference0Copy( domainReference0 );

	//test the getType() method
	if ( domainReference0Copy.getType()=="DomainReference" ){
	
		cout<<"The type of domainReference0Copy is correctly \"DomainReference\". "<<endl;
	}else{
		cerr<<"Error: The type of domainReference0Copy is "<<domainReference0Copy.getType() <<
			" and not \"DomainReference\""<<endl;
		iReturn++;
	}
	
	//test the getTypeElement() method
	if ( inVar1.equal( *(domainReference0Copy.getTypeElement() ) ) ){
	
		cout<<"The domainReference0Copy has correctly a type equal to inVar1 as type. "<<endl;
	}else{
		cerr<<"Error: The domainReference0Copy has not a type equal to inVar1 as type."<<endl;
		iReturn++;
	}
	//test the getTypeElement() method
	if ( vecCorrectElementDomains == domainReference0Copy.getElement() ){
	
		cout<<"The domainReference0Copy has the correct element domain numbers. "<<endl;
	}else{
		cerr<<"Error: The domainReference0Copy has the wrong element domain numbers."<<endl;
		vector<unsignedIntFib> vecWrongElementDomains = domainReference0Copy.getElement();
		cerr<<"   It has:          ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecWrongElementDomains.begin();
				itrNumber != vecWrongElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		cerr<<"   But should have: ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecCorrectElementDomains.begin();
				itrNumber != vecCorrectElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		iReturn++;
	}

	//test the isReference() method
	if ( domainReference0Copy.isReference() ){
	
		cout<<"The domainReference0Copy is correctly a reference domain. "<<endl;
	}else{
		cerr<<"Error: The domainReference0Copy is not a reference domain ."<<endl;
		iReturn++;
	}
	//test the isScalar() method
	if ( ! domainReference0Copy.isScalar() ){
	
		cout<<"The domainReference0Copy is correctly not a scalar domain. "<<endl;
	}else{
		cerr<<"Error: The domainReference0Copy is a scalar domain ."<<endl;
		iReturn++;
	}
	//test the isVector() method
	if ( ! domainReference0Copy.isVector() ){
	
		cout<<"The domainReference0Copy is correctly not a vector domain. "<<endl;
	}else{
		cerr<<"Error: The domainReference0Copy is a vector domain ."<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a reference domain with a choosen subdomain element"<<endl;

	cout<<"cTypeProperty typePropertyRGB( cTypeProperty::COLOR_RGB );"<<endl;
	cTypeProperty typePropertyRGB( cTypeProperty::COLOR_RGB );

	cout<<"vector<unsignedIntFib> vecElementDomains;"<<endl;
	vector<unsignedIntFib> vecElementDomains;
	cout<<"vecElementDomains.push_back( 2 );"<<endl;
	vecElementDomains.push_back( 2 );
	vecCorrectElementDomains = vecElementDomains;
	
	cout<<"cDomainReference domainReferenceED1( typePropertyRGB, vecElementDomains );"<<endl;
	cDomainReference domainReferenceED1( typePropertyRGB, vecElementDomains );

	//test the getType() method
	if ( domainReferenceED1.getType()=="DomainReference" ){
	
		cout<<"The type of domainReferenceED1 is correctly \"DomainReference\". "<<endl;
	}else{
		cerr<<"Error: The type of domainReferenceED1 is "<<domainReferenceED1.getType() <<
			" and not \"DomainReference\""<<endl;
		iReturn++;
	}
	
	//test the getTypeElement() method
	if ( typePropertyRGB.equal( *(domainReferenceED1.getTypeElement() ) ) ){
	
		cout<<"The domainReferenceED1 has correctly a type equal to typePropertyRGB as type. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED1 has not a type equal to typePropertyRGB as type."<<endl;
		iReturn++;
	}
	//test the getTypeElement() method
	if ( vecCorrectElementDomains == domainReferenceED1.getElement() ){
	
		cout<<"The domainReferenceED1 has the correct element domain numbers. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED1 has the wrong element domain numbers."<<endl;
		vector<unsignedIntFib> vecWrongElementDomains = domainReferenceED1.getElement();
		cerr<<"   It has:          ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecWrongElementDomains.begin();
				itrNumber != vecWrongElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		cerr<<"   But should have: ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecCorrectElementDomains.begin();
				itrNumber != vecCorrectElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		iReturn++;
	}

	//test the isReference() method
	if ( domainReferenceED1.isReference() ){
	
		cout<<"The domainReferenceED1 is correctly a reference domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED1 is not a reference domain ."<<endl;
		iReturn++;
	}
	//test the isScalar() method
	if ( ! domainReferenceED1.isScalar() ){
	
		cout<<"The domainReferenceED1 is correctly not a scalar domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED1 is a scalar domain ."<<endl;
		iReturn++;
	}
	//test the isVector() method
	if ( ! domainReferenceED1.isVector() ){
	
		cout<<"The domainReferenceED1 is correctly not a vector domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED1 is a vector domain ."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copy constructing reference domain (domainReferenceED1)"<<endl;

	cout<<"cDomainReference domainReferenceED1Copy( domainReferenceED1 );"<<endl;
	cDomainReference domainReferenceED1Copy( domainReferenceED1 );

	//test the getType() method
	if ( domainReferenceED1Copy.getType()=="DomainReference" ){
	
		cout<<"The type of domainReferenceED1Copy is correctly \"DomainReference\". "<<endl;
	}else{
		cerr<<"Error: The type of domainReferenceED1Copy is "<<domainReferenceED1Copy.getType() <<
			" and not \"DomainReference\""<<endl;
		iReturn++;
	}
	
	//test the getTypeElement() method
	if ( typePropertyRGB.equal( *(domainReferenceED1Copy.getTypeElement() ) ) ){
	
		cout<<"The domainReferenceED1Copy has correctly a type equal to typePropertyRGB as type. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED1Copy has not a type equal to typePropertyRGB as type."<<endl;
		iReturn++;
	}
	//test the getTypeElement() method
	if ( vecCorrectElementDomains == domainReferenceED1Copy.getElement() ){
	
		cout<<"The domainReferenceED1Copy has the correct element domain numbers. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED1Copy has the wrong element domain numbers."<<endl;
		vector<unsignedIntFib> vecWrongElementDomains = domainReferenceED1Copy.getElement();
		cerr<<"   It has:          ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecWrongElementDomains.begin();
				itrNumber != vecWrongElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		cerr<<"   But should have: ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecCorrectElementDomains.begin();
				itrNumber != vecCorrectElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		iReturn++;
	}

	//test the isReference() method
	if ( domainReferenceED1Copy.isReference() ){
	
		cout<<"The domainReferenceED1Copy is correctly a reference domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED1Copy is not a reference domain ."<<endl;
		iReturn++;
	}
	//test the isScalar() method
	if ( ! domainReferenceED1Copy.isScalar() ){
	
		cout<<"The domainReferenceED1Copy is correctly not a scalar domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED1Copy is a scalar domain ."<<endl;
		iReturn++;
	}
	//test the isVector() method
	if ( ! domainReferenceED1Copy.isVector() ){
	
		cout<<"The domainReferenceED1Copy is correctly not a vector domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED1Copy is a vector domain ."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a reference domain with some choosen subdomain elements"<<endl;

	cout<<"cTypeFibSet typeFibSet;"<<endl;
	cTypeFibSet typeFibSet;

	cout<<"vecElementDomains.clear();"<<endl;
	vecElementDomains.clear();
	cout<<"vecElementDomains.push_back( 3 );"<<endl;
	vecElementDomains.push_back( 3 );
	cout<<"vecElementDomains.push_back( 1 );"<<endl;
	vecElementDomains.push_back( 1 );
	vecCorrectElementDomains = vecElementDomains;
	
	cout<<"cDomainReference domainReferenceED2( typeFibSet, vecElementDomains );"<<endl;
	cDomainReference domainReferenceED2( typeFibSet, vecElementDomains );

	//test the getType() method
	if ( domainReferenceED2.getType()=="DomainReference" ){
	
		cout<<"The type of domainReferenceED2 is correctly \"DomainReference\". "<<endl;
	}else{
		cerr<<"Error: The type of domainReferenceED2 is "<<domainReferenceED2.getType() <<
			" and not \"DomainReference\""<<endl;
		iReturn++;
	}
	
	//test the getTypeElement() method
	if ( typeFibSet.equal( *(domainReferenceED2.getTypeElement() ) ) ){
	
		cout<<"The domainReferenceED2 has correctly a type equal to typeFibSet as type. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED2 has not a type equal to typeFibSet as type."<<endl;
		iReturn++;
	}
	//test the getTypeElement() method
	if ( vecCorrectElementDomains == domainReferenceED2.getElement() ){
	
		cout<<"The domainReferenceED2 has the correct element domain numbers. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED2 has the wrong element domain numbers."<<endl;
		vector<unsignedIntFib> vecWrongElementDomains = domainReferenceED2.getElement();
		cerr<<"   It has:          ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecWrongElementDomains.begin();
				itrNumber != vecWrongElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		cerr<<"   But should have: ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecCorrectElementDomains.begin();
				itrNumber != vecCorrectElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		iReturn++;
	}

	//test the isReference() method
	if ( domainReferenceED2.isReference() ){
	
		cout<<"The domainReferenceED2 is correctly a reference domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED2 is not a reference domain ."<<endl;
		iReturn++;
	}
	//test the isScalar() method
	if ( ! domainReferenceED2.isScalar() ){
	
		cout<<"The domainReferenceED2 is correctly not a scalar domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED2 is a scalar domain ."<<endl;
		iReturn++;
	}
	//test the isVector() method
	if ( ! domainReferenceED2.isVector() ){
	
		cout<<"The domainReferenceED2 is correctly not a vector domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED2 is a vector domain ."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copy constructing reference domain (domainReferenceED2)"<<endl;

	cout<<"cDomainReference domainReferenceED2Copy( domainReferenceED2 );"<<endl;
	cDomainReference domainReferenceED2Copy( domainReferenceED2 );

	//test the getType() method
	if ( domainReferenceED2Copy.getType()=="DomainReference" ){
	
		cout<<"The type of domainReferenceED2Copy is correctly \"DomainReference\". "<<endl;
	}else{
		cerr<<"Error: The type of domainReferenceED2Copy is "<<domainReferenceED2Copy.getType() <<
			" and not \"DomainReference\""<<endl;
		iReturn++;
	}
	
	//test the getTypeElement() method
	if ( typeFibSet.equal( *(domainReferenceED2Copy.getTypeElement() ) ) ){
	
		cout<<"The domainReferenceED2Copy has correctly a type equal to typeFibSet as type. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED2Copy has not a type equal to typeFibSet as type."<<endl;
		iReturn++;
	}
	//test the getTypeElement() method
	if ( vecCorrectElementDomains == domainReferenceED2Copy.getElement() ){
	
		cout<<"The domainReferenceED2Copy has the correct element domain numbers. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED2Copy has the wrong element domain numbers."<<endl;
		vector<unsignedIntFib> vecWrongElementDomains = domainReferenceED2Copy.getElement();
		cerr<<"   It has:          ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecWrongElementDomains.begin();
				itrNumber != vecWrongElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		cerr<<"   But should have: ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecCorrectElementDomains.begin();
				itrNumber != vecCorrectElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		iReturn++;
	}

	//test the isReference() method
	if ( domainReferenceED2Copy.isReference() ){
	
		cout<<"The domainReferenceED2Copy is correctly a reference domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED2Copy is not a reference domain ."<<endl;
		iReturn++;
	}
	//test the isScalar() method
	if ( ! domainReferenceED2Copy.isScalar() ){
	
		cout<<"The domainReferenceED2Copy is correctly not a scalar domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED2Copy is a scalar domain ."<<endl;
		iReturn++;
	}
	//test the isVector() method
	if ( ! domainReferenceED2Copy.isVector() ){
	
		cout<<"The domainReferenceED2Copy is correctly not a vector domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceED2Copy is a vector domain ."<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing a reference domain with no type set (=NULL)"<<endl;

	cout<<"cDomainReference domainReferenceNULL( *NULL, vecElementDomains );"<<endl;
	cDomainReference domainReferenceNULL( *((cTypeElement*)NULL), vecElementDomains );

	//test the getType() method
	if ( domainReferenceNULL.getType()=="DomainReference" ){
	
		cout<<"The type of domainReferenceNULL is correctly \"DomainReference\". "<<endl;
	}else{
		cerr<<"Error: The type of domainReferenceNULL is "<<domainReferenceNULL.getType() <<
			" and not \"DomainReference\""<<endl;
		iReturn++;
	}
	
	//test the getTypeElement() method
	if ( domainReferenceNULL.getTypeElement() == NULL ){
	
		cout<<"The domainReferenceNULL has correctly no type (=NULL). "<<endl;
	}else{
		cerr<<"Error: The domainReferenceNULL has a type (=NULL)."<<endl;
		iReturn++;
	}
	//test the getTypeElement() method
	if ( vecCorrectElementDomains == domainReferenceNULL.getElement() ){
	
		cout<<"The domainReferenceNULL has the correct element domain numbers. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceNULL has the wrong element domain numbers."<<endl;
		vector<unsignedIntFib> vecWrongElementDomains = domainReferenceNULL.getElement();
		cerr<<"   It has:          ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecWrongElementDomains.begin();
				itrNumber != vecWrongElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		cerr<<"   But should have: ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecCorrectElementDomains.begin();
				itrNumber != vecCorrectElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		iReturn++;
	}

	//test the isReference() method
	if ( domainReferenceNULL.isReference() ){
	
		cout<<"The domainReferenceNULL is correctly a reference domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceNULL is not a reference domain ."<<endl;
		iReturn++;
	}
	//test the isScalar() method
	if ( ! domainReferenceNULL.isScalar() ){
	
		cout<<"The domainReferenceNULL is correctly not a scalar domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceNULL is a scalar domain ."<<endl;
		iReturn++;
	}
	//test the isVector() method
	if ( ! domainReferenceNULL.isVector() ){
	
		cout<<"The domainReferenceNULL is correctly not a vector domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceNULL is a vector domain ."<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copy constructing reference domain (domainReferenceNULL)"<<endl;

	cout<<"cDomainReference domainReferenceNULLCopy( domainReferenceNULL );"<<endl;
	cDomainReference domainReferenceNULLCopy( domainReferenceNULL );

	//test the getType() method
	if ( domainReferenceNULLCopy.getType()=="DomainReference" ){
	
		cout<<"The type of domainReferenceNULLCopy is correctly \"DomainReference\". "<<endl;
	}else{
		cerr<<"Error: The type of domainReferenceNULLCopy is "<<domainReferenceNULLCopy.getType() <<
			" and not \"DomainReference\""<<endl;
		iReturn++;
	}
	
	//test the getTypeElement() method
	if ( domainReferenceNULLCopy.getTypeElement() == NULL ){
	
		cout<<"The domainReferenceNULLCopy has correctly no type (=NULL). "<<endl;
	}else{
		cerr<<"Error: The domainReferenceNULLCopy has a type (=NULL)."<<endl;
		iReturn++;
	}
	//test the getTypeElement() method
	if ( vecCorrectElementDomains == domainReferenceNULLCopy.getElement() ){
	
		cout<<"The domainReferenceNULLCopy has the correct element domain numbers. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceNULLCopy has the wrong element domain numbers."<<endl;
		vector<unsignedIntFib> vecWrongElementDomains = domainReferenceNULLCopy.getElement();
		cerr<<"   It has:          ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecWrongElementDomains.begin();
				itrNumber != vecWrongElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		cerr<<"   But should have: ";
		for ( vector<unsignedIntFib>::iterator
				itrNumber = vecCorrectElementDomains.begin();
				itrNumber != vecCorrectElementDomains.end(); itrNumber++ ){
			cerr<<(*itrNumber)<<"; ";
		}
		cerr<<endl;
		iReturn++;
	}

	//test the isReference() method
	if ( domainReferenceNULLCopy.isReference() ){
	
		cout<<"The domainReferenceNULLCopy is correctly a reference domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceNULLCopy is not a reference domain ."<<endl;
		iReturn++;
	}
	//test the isScalar() method
	if ( ! domainReferenceNULLCopy.isScalar() ){
	
		cout<<"The domainReferenceNULLCopy is correctly not a scalar domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceNULLCopy is a scalar domain ."<<endl;
		iReturn++;
	}
	//test the isVector() method
	if ( ! domainReferenceNULLCopy.isVector() ){
	
		cout<<"The domainReferenceNULLCopy is correctly not a vector domain. "<<endl;
	}else{
		cerr<<"Error: The domainReferenceNULLCopy is a vector domain ."<<endl;
		iReturn++;
	}	
	
	return iReturn;
}



/**
 * This method tests the equal() method and the operator== of two given
 * cDomain objects which are equal.
 *
 * @param domain1 the first domain to compare
 * @param szNameDomain1 the name of the first domain to compare
 * @param domain2 the secound domain to compare to
 * @param szNameDomain2 the name of the secound domain to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualDomains( const cDomain &domain1, const string &szNameDomain1,
	const cDomain &domain2, const string &szNameDomain2 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	if ( domain1.equal( domain2 ) ){
	
		cout<<"The "<<szNameDomain1<<" is equal to "<<szNameDomain2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is not equal to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	if ( domain1==domain2 ){
	
		cout<<"The "<<szNameDomain1<<" is equal (operator==) to "<<
			szNameDomain2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is not equal (operator==) to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the equal() method and the operator== of two given
 * cDomain objects which are not equal.
 *
 * @param domain1 the first domain to compare
 * @param szNameDomain1 the name of the first domain to compare
 * @param domain2 the secound domain to compare to
 * @param szNameDomain2 the name of the secound domain to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualDomains( const cDomain &domain1, const string &szNameDomain1,
	const cDomain &domain2, const string &szNameDomain2 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	if ( ! domain1.equal( domain2 ) ){
	
		cout<<"The "<<szNameDomain1<<" is not equal to "<<szNameDomain2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is equal to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	if ( ! (domain1==domain2) ){
	
		cout<<"The "<<szNameDomain1<<" is not equal (operator==) to "<<
			szNameDomain2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameDomain1<<" is equal (operator==) to "<<
			szNameDomain2<<"."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the equal and operator== methods of the cDomainReference
 * class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testEqual( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the equal method and the operator== "<<endl;

	cout<<"cDomainReference domainReferenceNULL( *NULL );"<<endl;
	cDomainReference domainReferenceNULL( *((cTypeElement*)NULL) );

	cout<<"cTypeInVar typeInVar0( 0 );"<<endl;
	cTypeInVar typeInVar0( 0 );
	cout<<"cDomainReference domainReferenceInVar0( typeInVar0 );"<<endl;
	cDomainReference domainReferenceInVar0( typeInVar0 );

	cout<<"cTypeInVar typeInVar1( 1 );"<<endl;
	cTypeInVar typeInVar1( 1 );
	cout<<"cDomainReference domainReferenceInVar1( typeInVar1 );"<<endl;
	cDomainReference domainReferenceInVar1( typeInVar1 );

	cout<<"cTypeProperty typeProperty( cTypeProperty::COLOR_RGB );"<<endl;
	cTypeProperty typeProperty( cTypeProperty::COLOR_RGB );
	cout<<"cDomainReference domainReferenceRgb( typeProperty );"<<endl;
	cDomainReference domainReferenceRgb( typeProperty );

	cout<<"vector<unsignedIntFib> vecElementDomains;"<<endl;
	vector<unsignedIntFib> vecElementDomains;
	cout<<"vecElementDomains.push_back( 3 );"<<endl;
	vecElementDomains.push_back( 3 );
	cout<<"cDomainReference domainReferenceRgbVec3( typeProperty, vecElementDomains );"<<endl;
	cDomainReference domainReferenceRgbVec3( typeProperty, vecElementDomains );

	cout<<"cTypeFibSet typeFibSet( 1 );"<<endl;
	cTypeFibSet typeFibSet( 1 );
	cout<<"cDomainReference domainReferenceFibSet1Vec3( typeFibSet, vecElementDomains );"<<endl;
	cDomainReference domainReferenceFibSet1Vec3( typeFibSet, vecElementDomains );

	cout<<"vecElementDomains.push_back( 1 );"<<endl;
	vecElementDomains.push_back( 1 );
	cout<<"cDomainReference domainReferenceFibSet1Vec3u1( typeFibSet, vecElementDomains );"<<endl;
	cDomainReference domainReferenceFibSet1Vec3u1( typeFibSet, vecElementDomains );

	cout<<"vecElementDomains.push_back( 1 );"<<endl;
	vecElementDomains.push_back( 1 );
	cout<<"cDomainReference domainReferenceFibSet1Vec3u1u1( typeFibSet, vecElementDomains );"<<endl;
	cDomainReference domainReferenceFibSet1Vec3u1u1( typeFibSet, vecElementDomains );

	
	cout<<"cDomainReference domainReferenceNULLVec3u1u1( *NULL, vecElementDomains );"<<endl;
	cDomainReference domainReferenceNULLVec3u1u1( *((cTypeElement*)NULL), vecElementDomains );
	
	
	//check with other domains
	cout<<"vector<cDomainSingle*> vecDomains3( 3 );"<<endl;
	vector<cDomainSingle*> vecDomains3( 3 );
	cout<<"vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains3[ 0 ]=new cDomainNaturalNumberBit( 8 );
	cout<<"vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains3[ 1 ]=new cDomainNaturalNumberBit( 16 );
	cout<<"vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 6 );"<<endl;
	vecDomains3[ 2 ]=new cDomainNaturalNumberBit( 6 );
	cout<<"cDomainVector domainReferenceNorm3E3( vecDomains3 );"<<endl;
	cDomainVector domainReferenceNorm3E3( vecDomains3 );
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];

	cout<<"cDomainNaturalNumberBit domainInteger2Bit5( 5 );"<<endl;
	cDomainNaturalNumberBit domainInteger2Bit5( 5 );

	//compare with domainReferenceNULL
	cDomain *actualDomain=&domainReferenceNULL;
	string szActualDomainName="domainReferenceNULL";
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULL, "domainReferenceNULL" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar0, "domainReferenceInVar0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar1, "domainReferenceInVar1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgb, "domainReferenceRgb" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgbVec3, "domainReferenceRgbVec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3, "domainReferenceFibSet1Vec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1, "domainReferenceFibSet1Vec3u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1u1, "domainReferenceFibSet1Vec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULLVec3u1u1, "domainReferenceNULLVec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNorm3E3, "domainReferenceNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with domainReferenceInVar0
	actualDomain=&domainReferenceInVar0;
	szActualDomainName="domainReferenceInVar0";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULL, "domainReferenceNULL" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar0, "domainReferenceInVar0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar1, "domainReferenceInVar1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgb, "domainReferenceRgb" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgbVec3, "domainReferenceRgbVec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3, "domainReferenceFibSet1Vec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1, "domainReferenceFibSet1Vec3u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1u1, "domainReferenceFibSet1Vec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULLVec3u1u1, "domainReferenceNULLVec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNorm3E3, "domainReferenceNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with domainReferenceInVar1
	actualDomain=&domainReferenceInVar1;
	szActualDomainName="domainReferenceInVar1";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULL, "domainReferenceNULL" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar0, "domainReferenceInVar0" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar1, "domainReferenceInVar1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgb, "domainReferenceRgb" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgbVec3, "domainReferenceRgbVec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3, "domainReferenceFibSet1Vec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1, "domainReferenceFibSet1Vec3u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1u1, "domainReferenceFibSet1Vec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULLVec3u1u1, "domainReferenceNULLVec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNorm3E3, "domainReferenceNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with domainReferenceRgb
	actualDomain=&domainReferenceRgb;
	szActualDomainName="domainReferenceRgb";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULL, "domainReferenceNULL" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar0, "domainReferenceInVar0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar1, "domainReferenceInVar1" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgb, "domainReferenceRgb" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgbVec3, "domainReferenceRgbVec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3, "domainReferenceFibSet1Vec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1, "domainReferenceFibSet1Vec3u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1u1, "domainReferenceFibSet1Vec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULLVec3u1u1, "domainReferenceNULLVec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNorm3E3, "domainReferenceNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with domainReferenceRgbVec3
	actualDomain=&domainReferenceRgbVec3;
	szActualDomainName="domainReferenceRgbVec3";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULL, "domainReferenceNULL" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar0, "domainReferenceInVar0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar1, "domainReferenceInVar1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgb, "domainReferenceRgb" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgbVec3, "domainReferenceRgbVec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3, "domainReferenceFibSet1Vec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1, "domainReferenceFibSet1Vec3u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1u1, "domainReferenceFibSet1Vec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULLVec3u1u1, "domainReferenceNULLVec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNorm3E3, "domainReferenceNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with domainReferenceFibSet1Vec3
	actualDomain=&domainReferenceFibSet1Vec3;
	szActualDomainName="domainReferenceFibSet1Vec3";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULL, "domainReferenceNULL" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar0, "domainReferenceInVar0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar1, "domainReferenceInVar1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgb, "domainReferenceRgb" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgbVec3, "domainReferenceRgbVec3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3, "domainReferenceFibSet1Vec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1, "domainReferenceFibSet1Vec3u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1u1, "domainReferenceFibSet1Vec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULLVec3u1u1, "domainReferenceNULLVec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNorm3E3, "domainReferenceNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with domainReferenceFibSet1Vec3u1
	actualDomain=&domainReferenceFibSet1Vec3u1;
	szActualDomainName="domainReferenceFibSet1Vec3u1";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULL, "domainReferenceNULL" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar0, "domainReferenceInVar0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar1, "domainReferenceInVar1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgb, "domainReferenceRgb" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgbVec3, "domainReferenceRgbVec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3, "domainReferenceFibSet1Vec3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1, "domainReferenceFibSet1Vec3u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1u1, "domainReferenceFibSet1Vec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULLVec3u1u1, "domainReferenceNULLVec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNorm3E3, "domainReferenceNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with domainReferenceFibSet1Vec3u1u1
	actualDomain=&domainReferenceFibSet1Vec3u1u1;
	szActualDomainName="domainReferenceFibSet1Vec3u1u1";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULL, "domainReferenceNULL" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar0, "domainReferenceInVar0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar1, "domainReferenceInVar1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgb, "domainReferenceRgb" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgbVec3, "domainReferenceRgbVec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3, "domainReferenceFibSet1Vec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1, "domainReferenceFibSet1Vec3u1" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1u1, "domainReferenceFibSet1Vec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULLVec3u1u1, "domainReferenceNULLVec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNorm3E3, "domainReferenceNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with domainReferenceNULLVec3u1u1
	actualDomain=&domainReferenceNULLVec3u1u1;
	szActualDomainName="domainReferenceNULLVec3u1u1";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULL, "domainReferenceNULL" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar0, "domainReferenceInVar0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar1, "domainReferenceInVar1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgb, "domainReferenceRgb" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgbVec3, "domainReferenceRgbVec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3, "domainReferenceFibSet1Vec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1, "domainReferenceFibSet1Vec3u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1u1, "domainReferenceFibSet1Vec3u1u1" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULLVec3u1u1, "domainReferenceNULLVec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNorm3E3, "domainReferenceNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with domainReferenceNorm3E3
	actualDomain=&domainReferenceNorm3E3;
	szActualDomainName="domainReferenceNorm3E3";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULL, "domainReferenceNULL" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar0, "domainReferenceInVar0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar1, "domainReferenceInVar1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgb, "domainReferenceRgb" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgbVec3, "domainReferenceRgbVec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3, "domainReferenceFibSet1Vec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1, "domainReferenceFibSet1Vec3u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1u1, "domainReferenceFibSet1Vec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULLVec3u1u1, "domainReferenceNULLVec3u1u1" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainReferenceNorm3E3, "domainReferenceNorm3E3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	//compare with domainInteger2Bit5
	actualDomain=&domainInteger2Bit5;
	szActualDomainName="domainInteger2Bit5";
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULL, "domainReferenceNULL" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar0, "domainReferenceInVar0" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceInVar1, "domainReferenceInVar1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgb, "domainReferenceRgb" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceRgbVec3, "domainReferenceRgbVec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3, "domainReferenceFibSet1Vec3" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1, "domainReferenceFibSet1Vec3u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceFibSet1Vec3u1u1, "domainReferenceFibSet1Vec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNULLVec3u1u1, "domainReferenceNULLVec3u1u1" );
	iReturn+=testCompareTwoNotEqualDomains( *actualDomain, szActualDomainName, domainReferenceNorm3E3, "domainReferenceNorm3E3" );
	iReturn+=testCompareTwoEqualDomains( *actualDomain, szActualDomainName, domainInteger2Bit5, "domainInteger2Bit5" );

	return iReturn;
}


/**
 * This method tests the clone() method of the cDomainReference 
 * class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testClone( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cloning a reference domain to no type (=NULL)"<<endl;

	cout<<"cDomainReference domainReferenceNULL( *NULL );"<<endl;
	cDomainReference domainReferenceNULL( *((cTypeElement*)NULL) );

	cout<<"cDomainReference * pDomainReferenceNULLclone = domainReferenceNULL.clone();"<<endl;
	cDomainReference * pDomainReferenceNULLclone = domainReferenceNULL.clone();

	iReturn+=testCompareTwoEqualDomains( domainReferenceNULL, "domainReferenceNULL", *pDomainReferenceNULLclone, "pDomainReferenceNULLclone" );

	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cloning a reference domain with type invar"<<endl;

	cout<<"cTypeInVar typeInVar1( 1 );"<<endl;
	cTypeInVar typeInVar1( 1 );
	
	cout<<"cDomainReference domainReferenceInVar( typeInVar1 );"<<endl;
	cDomainReference domainReferenceInVar( typeInVar1 );


	cout<<"cDomainReference * pDomainReferenceInVarclone = domainReferenceInVar.clone();"<<endl;
	cDomainReference * pDomainReferenceInVarclone = domainReferenceInVar.clone();

	iReturn+=testCompareTwoEqualDomains( domainReferenceInVar, "domainReferenceInVar", *pDomainReferenceInVarclone, "pDomainReferenceInVarclone" );

	iReturn+=testCompareTwoNotEqualDomains( domainReferenceNULL, "domainReferenceNULL", *pDomainReferenceInVarclone, "pDomainReferenceInVarclone" );
	iReturn+=testCompareTwoNotEqualDomains( *pDomainReferenceNULLclone, "pDomainReferenceNULLclone", *pDomainReferenceInVarclone, "pDomainReferenceInVarclone" );
	delete pDomainReferenceNULLclone;
	delete pDomainReferenceInVarclone;
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing cloning a reference domain with given domain elements"<<endl;

	cout<<"cTypeProperty typeFibSet( 1 );"<<endl;
	cTypeProperty typeFibSet( 1 );

	cout<<"vector<unsignedIntFib> vecElementDomains;"<<endl;
	vector<unsignedIntFib> vecElementDomains;
	cout<<"vecElementDomains.push_back( 3 );"<<endl;
	vecElementDomains.push_back( 3 );
	cout<<"vecElementDomains.push_back( 2 );"<<endl;
	vecElementDomains.push_back( 2 );

	cout<<"cDomainReference domainReferenceEle2( typeFibSet, vecElementDomains );"<<endl;
	cDomainReference domainReferenceEle2( typeFibSet, vecElementDomains );

	cout<<"cDomainReference * pDomainReferenceEle2clone = domainReferenceEle2.clone();"<<endl;
	cDomainReference * pDomainReferenceEle2clone = domainReferenceEle2.clone();

	iReturn+=testCompareTwoEqualDomains( domainReferenceEle2, "domainReferenceEle2", *pDomainReferenceEle2clone, "pDomainReferenceEle2clone" );
	
	delete pDomainReferenceEle2clone;
	
	return iReturn;
}


/**
 * This method tests a in the xml -format stored cDomainReference with
 * cDomainNaturalNumberBit domains.
 *
 * @param szFilename the name of the file wher the cDomainNaturalNumberBit is stored
 * @param uiNumberInVar the number of the cTypeInVar to load, to which the
 * 	stored reference domain refers to
 * @param szElementDomain the string for the domain element atribute
 * @return the number of errors occured in the test
 */
int testXmlVectorDomain( const string szFilename,
		const unsigned int uiNumberInVar,
		const string szElementDomain = "" ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored domain:"<<endl;
	
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
	TiXmlHandle xmlRootHandle( 0 );

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();

		if ( szElementName == "domainReference" ){
			cout<<"The root element is correctly named \"domainReference\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"domainReference\"."<<endl;
			iReturn++;
		}
		
		const char * pcAttributDomainElement = pXmlElement->Attribute( "subdomain" );
		
		if ( pcAttributDomainElement == NULL ){
			if ( szElementDomain.empty() ){
				cout<<"The domain has correctly no attribute \"subdomain\"."<<endl;
			}else{
				cerr<<"Error: The domain has no attribute \"subdomain\"."<<endl;
				iReturn++;
			}
		}else if ( szElementDomain.compare( pcAttributDomainElement ) == 0 ) {
			cout<<"The number for subdomains of the domain are correctly \""<<
				szElementDomain <<"\". "<<endl;
		}else{
			cerr<<"Error: The umber for subdomains of the loaded domain are \""<<
				pcAttributDomainElement <<"\", but should be \""<<
				szElementDomain <<"\"."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	xmlRootHandle = xmlHandle.FirstChildElement();

	pXmlElement = xmlRootHandle.FirstChild().Element();
	
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();

		if ( szElementName == "inVar" ){
			cout<<"The root element is correctly named \"inVar\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"inVar\"."<<endl;
			iReturn++;
		}
		
		int uiInVarNumber = 0;
		const char * pcAttributNumber = pXmlElement->Attribute( "number",
			&uiInVarNumber );
		
		if ( pcAttributNumber == NULL ){
			cerr<<"Error: The type has no attribute \"number\"."<<endl;
			iReturn++;
		}else if ( (int)uiNumberInVar == uiInVarNumber ) {
			cout<<"The number of the input variable is correctly \""<<
				uiNumberInVar <<"\". "<<endl;
		}else{
			cerr<<"Error: The number of the input variable is \""<<
				uiInVarNumber <<"\", but should be \""<<
				uiNumberInVar <<"\"."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple vectordomain for input variable 1"<<endl;
	
	cout<<"cTypeInVar typeInVar1( 1 );"<<endl;
	cTypeInVar typeInVar1( 1 );
	cout<<"cDomainReference domainReferenceInVar1( typeInVar1 );"<<endl;
	cDomainReference domainReferenceInVar1( typeInVar1 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainReferenceInVar1.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	bool bStoreSuccesfull = domainReferenceInVar1.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlVectorDomain( szFileNameBuffer, 1, "" );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple vectordomain with one choosen subdomain"<<endl;
	
	//create reference domain with one elements
	cout<<"cTypeInVar typeInVar7( 7 );"<<endl;
	cTypeInVar typeInVar7( 7 );
	cout<<"vector<unsignedIntFib> vecElementDomains;"<<endl;
	vector<unsignedIntFib> vecElementDomains;
	cout<<"vecElementDomains.push_back( 3 );"<<endl;
	vecElementDomains.push_back( 3 );
	
	cout<<"cDomainReference domainReferenceSubdom3( typeInVar7, vecElementDomains );"<<endl;
	cDomainReference domainReferenceSubdom3( typeInVar7, vecElementDomains );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainReferenceSubdom3.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = domainReferenceSubdom3.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlVectorDomain( szFileNameBuffer, 7, "3" );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple vectordomain with two choosen subdomains"<<endl;
	
	//create reference domain with one elements
	cout<<"cTypeInVar typeInVar15( 15 );"<<endl;
	cTypeInVar typeInVar15( 15 );
	cout<<"vecElementDomains.push_back( 2 );"<<endl;
	vecElementDomains.push_back( 2 );
	
	cout<<"cDomainReference domainReferenceSubDom3p2( typeInVar15, vecElementDomains );"<<endl;
	cDomainReference domainReferenceSubDom3p2( typeInVar15, vecElementDomains );

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainReferenceSubDom3p2.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	bStoreSuccesfull = domainReferenceSubDom3p2.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlVectorDomain( szFileNameBuffer, 15, "3.2" );


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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple vector with a input variable type element"<<endl;
	
	//create reference domain with one elements
	cout<<"cTypeInVar typeInVar1( 1 );"<<endl;
	cTypeInVar typeInVar1( 1 );
	cout<<"cDomainReference domainReferenceInVar1( typeInVar1 );"<<endl;
	cDomainReference domainReferenceInVar1( typeInVar1 );

	//test get compressed size
	//domain reference + cTypeInVar + first start bit
	unsigned int uiCompressedSize = 8 + 16 + 1;
	if ( domainReferenceInVar1.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<<uiCompressedSize<<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domainReferenceInVar1.getCompressedSize() << ", but should be "<<
			uiCompressedSize<<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainReferenceInVar1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = domainReferenceInVar1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	char cCorrectNumberOfRestBit = 1;
	unsigned char cCorrectRestBit = (char)0x00;
	if ( ( cRestBit == cCorrectRestBit ) && ( cNumberOfRestBit == cCorrectNumberOfRestBit ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be \"(char)0x"<< hex <<cCorrectRestBit<<
			"\" and number of restbit should be "<< dec << cCorrectNumberOfRestBit<<". "<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomainReferenceInVar1[] = { (char)0xF0, //cDomainReference
		(char)0x2A, (char)0x01,//cTypeInVar( 1 )
		(char)0x00 }; //startbit + restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainReferenceInVar1, 4 );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple vector with one subdomain number"<<endl;
	
	//create reference domain with one elements
	cout<<"cTypeInVar typeInVar7( 7 );"<<endl;
	cTypeInVar typeInVar7( 7 );
	cout<<"vector<unsignedIntFib> vecElementDomains;"<<endl;
	vector<unsignedIntFib> vecElementDomains;
	cout<<"vecElementDomains.push_back( 3 );"<<endl;
	vecElementDomains.push_back( 3 );
	cout<<"cDomainReference domainReferenceSubdom3( typeInVar7, vecElementDomains );"<<endl;
	cDomainReference domainReferenceSubdom3( typeInVar7, vecElementDomains );

	//test get compressed size
	//domain reference + cTypeInVar + first start bit + bits per element number + (starter bits + subdomain numbers)
	uiCompressedSize = 8 + 16 + 1 + 8 + 1 * ( 1 + 2 );
	if ( domainReferenceSubdom3.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<<uiCompressedSize<<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domainReferenceSubdom3.getCompressedSize() << ", but should be "<<
			uiCompressedSize<<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainReferenceSubdom3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = domainReferenceSubdom3.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	cCorrectNumberOfRestBit = 4;
	cCorrectRestBit = (char)0x06;
	if ( ( cRestBit == cCorrectRestBit ) && ( cNumberOfRestBit == cCorrectNumberOfRestBit ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be \"(char)0x"<< hex <<cCorrectRestBit<<
			"\" and number of restbit should be "<< dec << cCorrectNumberOfRestBit<<". "<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomainReferenceSubdom3[] = { (char)0xF0, //cDomainReference
		(char)0x2A, (char)0x07,//cTypeInVar( 7 )
		// 1  0000 0010  11  0 -> 0000 0101  0110
		(char)0x05, //first starter bit + bits per element number
		(char)0x06 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainReferenceSubdom3, 5 );
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing compressed storing a simple vector with two subdomain numbers"<<endl;
	
	//create reference domain with one elements
	cout<<"cTypeInVar typeInVar11( 11 );"<<endl;
	cTypeInVar typeInVar11( 11 );
	cout<<"vecElementDomains.push_back( 258 );"<<endl;
	vecElementDomains.push_back( 258 );
	cout<<"cDomainReference domainReferenceSubdom3p258( typeInVar11, vecElementDomains );"<<endl;
	cDomainReference domainReferenceSubdom3p258( typeInVar11, vecElementDomains );

	//test get compressed size
	//domain reference + cTypeInVar + first start bit + bits per element number + (starter bits + subdomain numbers)
	uiCompressedSize = 8 + 16 + 1 + 8 + 2 * ( 1 + 9 );
	if ( domainReferenceSubdom3p258.getCompressedSize() == uiCompressedSize ){
	
		cout<<"The compressed size of the domain is correctly "<<uiCompressedSize<<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the domain is "<<
			domainReferenceSubdom3p258.getCompressedSize() << ", but should be "<<
			uiCompressedSize<<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "domainReferenceSubdom3p258.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0;
	cNumberOfRestBit = 0 ;
	bStoreSuccesfull = domainReferenceSubdom3p258.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	cCorrectNumberOfRestBit = 5;
	cCorrectRestBit = (char)0x08;
	if ( ( cRestBit == cCorrectRestBit ) && ( cNumberOfRestBit == cCorrectNumberOfRestBit ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be \"(char)0x"<< hex <<cCorrectRestBit<<
			"\" and number of restbit should be "<< dec << cCorrectNumberOfRestBit<<". "<<endl;
		iReturn++;
	}

	//test stored data
	const char cDomainReferenceSubdom3p258[] = { (char)0xF0, //cDomainReference
		(char)0x2A, (char)0x0B,//cTypeInVar( 11 )
		// 1  0000 1001  0 0000 0011  1  1 0000 0010  0  -> 0001 0011  0000 0110  0001 0100  0 1000
		(char)0x13, //first starter bit + bits per element number
		(char)0x06, (char)0x14, (char)0x08 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cDomainReferenceSubdom3p258, 7 );
	
	
	return iReturn;
}




