/**
 * @file tTypeArea
 * file name: tTypeArea.cpp
 * @author Betti Oesterholz
 * @date 13.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cTypeArea.
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
 * This file contains the test for the class cTypeArea,
 * which represents the type for area.
 *
 *
 *
 *  What's tested of class cTypeArea:
 * 	- cTypeArea()
 * 	- unsignedIntFib getType() const
 * 	- bool isCompatible( const cDomain &domain ) const
 * 	- cDomain *getStandardDomain( ) const
 * 	- bool equal( const cTypeElement &typeElement ) const
 * 	- bool operator==( const cTypeElement &typeElement ) const
 * 	- cTypeElement *clone() const
 * 	- bool equalElementType( const cTypeElement & typeElement ) const
 * 	- bool storeXml( ostream & ostream, const cDomain * domain = NULL ) const
 * 	- unsignedLongFib getCompressedSize() const
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const
 *
 */
/*
History:
13.02.2010  Oesterholz  created
13.05.2010  Oesterholz  the ordering of bits for the compressed storing corrected
04.04.2011  Oesterholz  storing to binary stream
25.08.2011  Oesterholz  underarea to subarea
02.01.2012  Oesterholz  subarea to area
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cTypeArea.h"
#include "cTypeProperty.h"
#include "cTypeInVar.h"
#include "cTypeDimension.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainRational.h"
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
int testIsCompatibleGetStandardDomain( unsigned long &ulTestphase );
int testClone( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testEqualElementType( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );

int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cTypeArea methods"<<endl;
	cout<<      "=================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testIsCompatibleGetStandardDomain( ulTestphase );
	iReturn += testClone( ulTestphase );
	iReturn += testEqual( ulTestphase );
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
 * This method tests the constructors and the getNumberOfDimension()
 * and getType() method of the cTypeArea class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cTypeArea"<<endl;

	cout<<"cTypeArea typeArea;"<<endl;
	cTypeArea typeArea;

	//check the getNumberOfInputArea() methode from cTypeArea
	if ( typeArea.getType() == (unsignedIntFib)(2) ){
	
		cout<<"The type of area is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The type of area is "<<
			typeArea.getType()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	return iReturn;
}



/**
 * This method tests the isCompatible() and getStandardDomain() method of
 * the cTypeArea class.
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testIsCompatibleGetStandardDomain( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the global standard domain for the cTypeArea"<<endl;
	
	cout<<"cTypeArea typeArea;"<<endl;
	cTypeArea typeArea;

	//check the getNumberOfInputArea() methode from cTypeArea
	if ( typeArea.getType() == (unsignedIntFib)(2) ){
	
		cout<<"The type of area is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The type of area is "<<
			typeArea.getType()<<" but should be 2 ."<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt = new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( ! typeArea.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly not compatible to an integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to a integer domain."<<endl;
		iReturn++;
	}
	delete domainInt;

	//TODO test more single domains
	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain = new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! typeArea.isCompatible( *vectorDomain ) ){
	
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
	if ( ! typeArea.isCompatible( *vectorDomain1 ) ){
	
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
	if ( ! typeArea.isCompatible( *vectorDomain ) ){
	
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
	if ( ! typeArea.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with 3 elements. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with 3 elements."<<endl;
		iReturn++;
	}
	delete vecDomains3[ 0 ];
	delete vecDomains3[ 1 ];
	delete vecDomains3[ 2 ];
	delete vectorDomain;
	
	//check compatible for vector domain with two elements, with a second a vector with two integers
	cout<<"vector<cDomain*> vecDomains2E2( 2 ); "<<endl;
	vector<cDomain*> vecDomains2E2( 2 );
	cout<<"vecDomains2E2[ 0 ]=new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains2E2[ 0 ]=new cDomainNaturalNumberBit( 8 );
	//check compatible for vector domain with two elements
	cout<<"vecDomains2[ 0 ]=new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains2[ 0 ]=new cDomainNaturalNumberBit( 8 );
	cout<<"vecDomains2[ 1 ]=new cDomainNaturalNumberBit( 16 );"<<endl;
	vecDomains2[ 1 ]=new cDomainNaturalNumberBit( 16 );
	cout<<"cDomainVector vecDomainE2Na8Na16( vecDomains2 );"<<endl;
	cDomainVector vecDomainE2Na8Na16( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	cout<<"vecDomains2E2[ 1 ]=&vecDomainE2Na8Na16;"<<endl;
	vecDomains2E2[ 1 ]=&vecDomainE2Na8Na16;
	cout<<"vectorDomain=new cDomainVector( vecDomains2E2 );"<<endl;
	vectorDomain=new cDomainVector( vecDomains2E2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( typeArea.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly compatible to the vector domain with two elements, with a second a vector with two integers. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to the vector domain with two elements, with a second a vector with two integers."<<endl;
		iReturn++;
	}
	delete vectorDomain;

	//check compatible for vector domain with two elements, with a second a vector with two numbers
	cout<<"vecDomains2[ 0 ]=new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains2[ 0 ]=new cDomainNaturalNumberBit( 8 );
	cout<<"vecDomains2[ 1 ]=new cDomainRational( cDomainNaturalNumberBit( 3 ), cDomainNaturalNumberBit( 2 ) );"<<endl;
	vecDomains2[ 1 ]=new cDomainRational( cDomainNaturalNumberBit( 3 ), cDomainNaturalNumberBit( 2 ) );
	cout<<"cDomainVector vecDomainE2Na8RatNat3Nat2( vecDomains2 );"<<endl;
	cDomainVector vecDomainE2Na8RatNat3Nat2( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	cout<<"vecDomains2E2[ 1 ]=&vecDomainE2Na8RatNat3Nat2;"<<endl;
	vecDomains2E2[ 1 ]=&vecDomainE2Na8RatNat3Nat2;
	cout<<"vectorDomain=new cDomainVector( vecDomains2E2 );"<<endl;
	vectorDomain=new cDomainVector( vecDomains2E2 );
	
	//check the isCompatible() methode for vectordomain with 2 elements
	if ( ! typeArea.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with two elements, with a second a vector with two numberss. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with two elements, with a second a vector with two numbers."<<endl;
		iReturn++;
	}
	delete vectorDomain;
	
	cout<<"vecDomains2[ 0 ]=new cDomainRational( cDomainNaturalNumberBit( 3 ), cDomainNaturalNumberBit( 2 ) );"<<endl;
	vecDomains2[ 0 ]=new cDomainRational( cDomainNaturalNumberBit( 3 ), cDomainNaturalNumberBit( 2 ) );
	cout<<"vecDomains2[ 1 ]=new cDomainNaturalNumberBit( 8 );"<<endl;
	vecDomains2[ 1 ]=new cDomainNaturalNumberBit( 8 );
	cout<<"cDomainVector vecDomainE2RatNat3Nat2Na8( vecDomains2 );"<<endl;
	cDomainVector vecDomainE2RatNat3Nat2Na8( vecDomains2 );
	delete vecDomains2[ 0 ];
	delete vecDomains2[ 1 ];
	cout<<"vecDomains2E2[ 1 ]=&vecDomainE2RatNat3Nat2Na8;"<<endl;
	vecDomains2E2[ 1 ]=&vecDomainE2RatNat3Nat2Na8;
	cout<<"vectorDomain=new cDomainVector( vecDomains2E2 );"<<endl;
	vectorDomain=new cDomainVector( vecDomains2E2 );
	
	//check compatible for vector domain with two elements, with a second a vector with two numbers
	if ( ! typeArea.isCompatible( *vectorDomain ) ){
	
		cout<<"The type is correctly not compatible to the vector domain with two elements, with a second a vector with two numbers. "<<endl;
	}else{
		cerr<<"Error: The type is compatible to the vector domain with two elements, with a second a vector with two numbers."<<endl;
		iReturn++;
	}
	delete vecDomains2E2[ 0 ];
	delete vectorDomain;

	
	
	//test the getStandardDomain() method of the property
	cDomain *pStandardDomain = typeArea.getStandardDomain();
	
	if ( pStandardDomain == NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( pStandardDomain->getType() == "DomainVector" ){
	
		cout<<"The standarddomain is correctly an cDomainVector domain. "<<endl;
		
		
		//check the isCompatible() methode for vectordomain with 3 elements
		if ( typeArea.isCompatible( *pStandardDomain ) ){
		
			cout<<"The type is correctly compatible to the standard domain. "<<endl;
		}else{
			cerr<<"Error: The type is compatible to the standard domain."<<endl;
			iReturn++;
		}
		
		cout<<"The standard domain is correctly an cDomainVector domain. "<<endl;
		
		cDomainVector *pStandardDomainVector = (cDomainVector*)pStandardDomain;

		unsignedIntFib uiStandardDomainVectorElements = 2;
		
		if ( pStandardDomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
		
			cout<<"The standard domain vector has correctly "<<
				uiStandardDomainVectorElements<<" element. "<<endl;
				
			//test domain of first vector element
			cDomain * pDomainElement1 = pStandardDomainVector->getElementDomain( 1 );
			if ( pDomainElement1 == NULL ){
			
				cerr<<"Error: The first element of the standard domain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			}else if ( pDomainElement1->getType() == "DomainNaturalNumberBit" ){
			
				cout<<"The first element of the standard domain is correctly an "<<
					pDomainElement1->getType()<<" domain. "<<endl;
				
				cDomainIntegerBasis * pDomainIntegerBit = (cDomainIntegerBasis*)pDomainElement1;
				
				const longFib ulMinimum = 0;
				const longFib ulMaximum = 255L;
				if ( (pDomainIntegerBit->getMinimum() == ulMinimum ) &&
						(pDomainIntegerBit->getMaximum() == ulMaximum ) ){
				
					cout<<"The domain goes correctly from "<<ulMinimum<<
						" to "<<ulMaximum<<". "<<endl;
				}else{
					cerr<<"Error: The domain goes correctly from "<<ulMinimum<<
						" to "<<ulMaximum<<", but it goes from "<<
						pDomainIntegerBit->getMinimum()<<" to "<<
						pDomainIntegerBit->getMaximum()<<"."<<endl;
					iReturn++;
				}
		
			}else{
				cerr<<"Error: The first element of the standard domain is not of type DomainNaturalNumberBit."<<endl;
				iReturn++;
			}
			
			//test domain of the remaining vector element
			cDomain * pDomainElement2 = pStandardDomainVector->getElementDomain( 2 );
			if ( pDomainElement2 == NULL ){
			
				cerr<<"Error: The  "<<2<<"'th element of the "<<
					"standard domain is not given back, but the Nullpointer NULL."<<endl;
				iReturn++;
				
			}else if ( pDomainElement2->getType() == "DomainVector" ){
			
				cout<<"The "<<2<<"'th element of the "<<
					"standard domain is correctly an "<<pDomainElement2->getType()<<" domain. "<<endl;
				
				cDomainVector * pStandard2SubdomainVector =
					(cDomainVector*)pDomainElement2;
				
				unsignedIntFib uiStandardDomainVectorElements = 2;
				
				if ( pStandard2SubdomainVector->getNumberOfElements() == uiStandardDomainVectorElements ){
				
					cout<<"The standarddomainvector has correctly "<<
						uiStandardDomainVectorElements<<" element. "<<endl;
					
					for ( unsignedIntFib actualElement = 1; actualElement <= uiStandardDomainVectorElements;
							actualElement++ ){
					
						//test domain of first vector element
						cDomain *domainElement = pStandard2SubdomainVector->getElementDomain( actualElement );
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
					cerr<<"Error: The standard domain second subdomain has "<<
						pStandard2SubdomainVector->getNumberOfElements()<<" elements and not "<<
						uiStandardDomainVectorElements<<" elements how it should."<<endl;
					iReturn++;
				}
				
			}else{
				cerr<<"Error: The standarddomain second subdomain has the type "<<
					pDomainElement2->getType()<<" and not the type cDomainVector."<<endl;
				iReturn++;
			}
		
		}else{
			cerr<<"Error: The standarddomain has "<<
				pStandardDomainVector->getNumberOfElements()<<" elements and not "<<
				uiStandardDomainVectorElements<<" elements how it should."<<endl;
			iReturn++;
		}
		
		delete pStandardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			pStandardDomain->getType()<<" and not the type cDomainVector."<<endl;
		iReturn++;
		delete pStandardDomain;
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

	cout<<"cTypeArea typeArea;"<<endl;
	cTypeArea typeArea;

	cout<<"cTypeArea * typeAreaClone1 = typeArea.clone();"<<endl;
	cTypeArea * typeAreaClone1 = typeArea.clone();


	cout<<endl<<"checking the clone:"<<endl;
	//check the getNumberOfInputArea() methode from cTypeArea
	if ( typeAreaClone1->getType() == (unsignedIntFib)(2) ){
	
		cout<<"The type of area is correctly 2 . "<<endl;
	}else{
		cerr<<"Error: The type of area is "<<
			typeAreaClone1->getType()<<" but should be 2 ."<<endl;
		iReturn++;
	}
	delete typeAreaClone1;

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

	//create cTypeAreas to compare
	cout<<"cTypeArea typeArea1;"<<endl;
	cTypeArea typeArea1;
	cout<<"cTypeArea typeArea2;"<<endl;
	cTypeArea typeArea2;

	cout<<"cTypeInVar typeInVar1N1( 1 );"<<endl;
	cTypeInVar typeInVar1N1( 1 );

	cout<<"cTypeProperty typeProperty( 1 );"<<endl;
	cTypeProperty typeProperty( 1 );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with typeArea1
	cTypeElement *actualType=&typeArea1;
	string szActualTypeName="typeArea1";
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeArea1, "typeArea1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeArea2, "typeArea2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeArea2
	actualType=&typeArea2;
	szActualTypeName="typeArea2";
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeArea1, "typeArea1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeArea2, "typeArea2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeInVar1N1
	actualType=&typeInVar1N1;
	szActualTypeName="typeInVar1N1";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeArea1, "typeArea1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeArea2, "typeArea2" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeProperty
	actualType=&typeProperty;
	szActualTypeName="typeProperty";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeArea1, "typeArea1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeArea2, "typeArea2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeInVar1N1, "typeInVar1N1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

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
	cout<<"cTypeArea typeArea1;"<<endl;
	cTypeArea typeArea1;
	
	cout<<"cTypeArea typeArea2;"<<endl;
	cTypeArea typeArea2;

	cout<<"cTypeInVar typeInVar1( 1 );"<<endl;
	cTypeInVar typeInVar1( 1 );

	cout<<"cTypeProperty typeProperty( 1 );"<<endl;
	cTypeProperty typeProperty( 1 );

	cout<<"cTypeDimension typeDimension1D3( 3 );"<<endl;
	cTypeDimension typeDimension1D3( 3 );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	if ( typeArea1.equalElementType( typeArea1 ) ){
	
		cout<<"The typeArea1 is of the same type as typeArea1. "<<endl;
	}else{
		cerr<<"Error: The typeArea1 is not of the same type as typeArea1."<<endl;
		iReturn++;
	}
	if ( typeArea1.equalElementType( typeArea2 ) ){
	
		cout<<"The typeArea1 is of the same type as typeArea2. "<<endl;
	}else{
		cerr<<"Error: The typeArea1 is not of the same type as typeArea2."<<endl;
		iReturn++;
	}
	if ( ! typeArea1.equalElementType( typeInVar1 ) ){
	
		cout<<"The typeArea1 is not of the same type as typeInVar1. "<<endl;
	}else{
		cerr<<"Error: The typeArea1 is of the same type as typeInVar1."<<endl;
		iReturn++;
	}

	if ( ! typeArea1.equalElementType( typeProperty ) ){
	
		cout<<"The typeArea1 is not of the same type as typeProperty. "<<endl;
	}else{
		cerr<<"Error: The typeArea1 is of the same type as typeProperty."<<endl;
		iReturn++;
	}

	if ( ! typeArea1.equalElementType( typeDimension1D3 ) ){
	
		cout<<"The typeArea1 is not of the same type as typeDimension1D3. "<<endl;
	}else{
		cerr<<"Error: The typeArea1 is of the same type as typeDimension1D3."<<endl;
		iReturn++;
	}


	return iReturn;
}



/**
 * This method tests a in the xml -format stored cDomainVector with
 * cDomainNaturalNumberBit domains.
 *
 * @param szFilename the name of the file wher the cDomainNaturalNumberBit is stored
 * @param uiBits a vector with the bits the cDomainNaturalNumberBit
 * 	domains have
 * @param scalingfactor a vector with the scalingfactors for the
 * 	cDomainNaturalNumberBit domains have
 * @return the number of errors occured in the test
 */
int testXmlType( const string szFilename,
		bool bHasDomain, unsigned int uiBits, double dScalingfactor ){
	
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

		if ( szElementName == "area" ){
			cout<<"The root element is correctly named \"area\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"area\"."<<endl;
			iReturn++;
		}
		
	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}

	if ( bHasDomain ){
		//read the subdomain
	
		xmlRootHandle = xmlHandle.FirstChildElement();
	
		pXmlElement = xmlRootHandle.FirstChildElement().Element();
	
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple area type"<<endl;

	cout<<"cTypeArea typeArea1;"<<endl;
	cTypeArea typeArea1;

	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeArea1.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeArea1.storeXml( *fileXml );"<<endl;
	bool bStoreSuccesfull = typeArea1.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, false,
		0, 0.0 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a 5'th area type with a domain"<<endl;

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB4( 4 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB4( 4 );
	unsigned int uiBits = 4;
	double dScalingfactor = 1.0;

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeArea1Dom.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeArea1.storeXml( *fileXml, &domainNaturalNumberB4 );"<<endl;
	bStoreSuccesfull = typeArea1.storeXml( *fileXml, &domainNaturalNumberB4 );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, true,
		uiBits, dScalingfactor );


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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple area type for the 1'th area"<<endl;
	
	cout<<"cTypeArea typeArea1;"<<endl;
	cTypeArea typeArea1;

	//test get compressed size
	unsigned int uiCompressedSize = 8;
	if ( (unsigned int)(typeArea1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeArea1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeArea1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = typeArea1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == (char)0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeArea1[] = { (char)0x18,
		(char)0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeArea1, 2 );



	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a area type with 5 restbitsbits"<<endl;

	//test get compressed size
	uiCompressedSize = 8;
	if ( (unsigned int)(typeArea1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeArea1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeArea1R5.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x07;
	cNumberOfRestBit = 5 ;
	bStoreSuccesfull = typeArea1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	unsigned char ucRestBit = cRestBit;
	if ( ( ucRestBit == (unsigned char)((char)0x03) ) && ( cNumberOfRestBit == 5 ) ){
		cout<<"The restbit is \"(char)0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"(char)0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be (char)0x03 and number of restbit should be 5. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeArea5[] = { (char)0x07, (char)0x03 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeArea5, 2 );


	return iReturn;
}




