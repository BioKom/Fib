/**
 * @file tTypeUnderFunction
 * file name: tTypeUnderFunction.cpp
 * @author Betti Oesterholz
 * @date 22.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cTypeUnderFunction.
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
 * This file contains the test for the class cTypeUnderFunction,
 * which represents the type for underfunction.
 *
 *
 *
 *  What's tested of class cTypeUnderFunction:
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
22.04.2010  Oesterholz  created
13.05.2010  Oesterholz  the ordering of bits for the compressed storing corrected
04.04.2011  Oesterholz  storing to binary stream
21.07.2011  Oesterholz  for the Xml-format "underfunction" to "subfunction"
17.09.2012  Oesterholz  Warning removed: "(char)" for char arrays added
*/

#include "version.h"

#include "cTypeUnderFunction.h"
#include "cTypeProperty.h"
#include "cTypeDimension.h"
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
int testIsCompatibleGetStandardDomain( unsigned long &ulTestphase );
int testClone( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testEqualElementType( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );

int main(int argc,char* argv[]){

	unsigned long ulTestphase=0;//actual phase of the test 
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Running Test for cTypeUnderFunction methods"<<endl;
	cout<<      "==================================="<<endl;

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
 * This method tests the constructors and the getType() method of the
 * cTypeUnderFunction class.
 *
 * methods tested:
 * 	- unsignedIntFib getType() const
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing simple cTypeUnderFunction"<<endl;

	cout<<"cTypeUnderFunction typeUnderFunction;"<<endl;
	cTypeUnderFunction typeUnderFunction;

	//check the getType() methode from cTypeUnderFunction
	if ( typeUnderFunction.getType() == (unsignedIntFib)(3) ){
	
		cout<<"The type of underfunction is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The type of underfunction is "<<
			typeUnderFunction.getType()<<" but should be 3 ."<<endl;
		iReturn++;
	}


	return iReturn;
}


/**
 * This method tests the isCompatible() and getStandardDomain() method of
 * the cTypeUnderFunction class.
 *
 * methods tested:
 * 	- bool isCompatible( const cDomain &domain ) const
 * 	- cDomain *getStandardDomain( ) const
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testIsCompatibleGetStandardDomain( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the global standard domain for the cTypeUnderFunction"<<endl;
	
	cout<<"cTypeUnderFunction typeUnderFunction;"<<endl;
	cTypeUnderFunction typeUnderFunction;

	//check the getType() methode from cTypeUnderFunction
	if ( typeUnderFunction.getType() == (unsignedIntFib)(3) ){
	
		cout<<"The type of underfunction is correctly 3 . "<<endl;
	}else{
		cerr<<"Error: The type of underfunction is "<<
			typeUnderFunction.getType()<<" but should be 3 ."<<endl;
		iReturn++;
	}

	//check compatible for integer domain
	cDomainSingle* domainInt=new cDomainNaturalNumberBit( 12 );
	
	//check the isCompatible() methode for vectordomain with 3 elements
	if ( typeUnderFunction.isCompatible( *domainInt ) ){
	
		cout<<"The type is correctly compatible to an integer domain. "<<endl;
	}else{
		cerr<<"Error: The type is not compatible to a integer domain."<<endl;
		iReturn++;
	}
	delete domainInt;

	//TODO test more single domains
	
	//check compatible for vector domain with zero elements
	vector<cDomainSingle*> vecDomains0( 0 );
	cDomainVector *vectorDomain=new cDomainVector( vecDomains0 );
	
	//check the isCompatible() methode for vectordomain with 0 elements
	if ( ! typeUnderFunction.isCompatible( *vectorDomain ) ){
	
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
	if ( ! typeUnderFunction.isCompatible( *vectorDomain1 ) ){
	
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
	if ( ! typeUnderFunction.isCompatible( *vectorDomain ) ){
	
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
	if ( ! typeUnderFunction.isCompatible( *vectorDomain ) ){
	
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
	cDomain *standardDomain = typeUnderFunction.getStandardDomain();
	
	if ( standardDomain == NULL ){
	
		cerr<<"Error: The standarddomain is not given back, but the Nullpointer NULL."<<endl;
		iReturn++;
		
	} else if ( standardDomain->getType()=="DomainNaturalNumberBit" ){
	
		cDomainIntegerBasis *domainNaturalNumberBit=(cDomainIntegerBasis*)standardDomain;
		
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
		
		delete standardDomain;
	}else{
		cerr<<"Error: The standarddomain has the type "<<
			standardDomain->getType()<<" and not the type cDomainNaturalNumberBit."<<endl;
		iReturn++;
		delete standardDomain;
	}

	return iReturn;
}


/**
 * This method tests the clone() method of the class.
 *
 *
 * methods tested:
 * 	- cTypeElement *clone() const
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testClone( unsigned long &ulTestphase ){

	int iReturn=0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the clone() method"<<endl;

	cout<<"cTypeUnderFunction typeUnderFunction;"<<endl;
	cTypeUnderFunction typeUnderFunction;

	cout<<"cTypeUnderFunction *pTypeUnderFunctionClone1 = typeUnderFunction.clone();"<<endl;
	cTypeUnderFunction *pTypeUnderFunctionClone1 = typeUnderFunction.clone();


	cout<<endl<<"checking the clone:"<<endl;
	//check the getNumberOfInputVariable() methode from cTypeUnderFunction
	if ( pTypeUnderFunctionClone1 != NULL ){
	
		//check the getType() methode from cTypeUnderFunction
		if ( typeUnderFunction.getType() == (unsignedIntFib)(3) ){
		
			cout<<"The type of underfunction is correctly 3 . "<<endl;
		}else{
			cerr<<"Error: The type of underfunction is "<<
				typeUnderFunction.getType()<<" but should be 3 ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The underfunction type couldnt be cloned ."<<endl;
		iReturn++;
	}

	delete pTypeUnderFunctionClone1;

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
	if ( typeElement1 == typeElement2 ){
	
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
	if ( ! (typeElement1 == typeElement2) ){
	
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

	//create cTypeUnderFunctions to compare
	cout<<"cTypeUnderFunction typeUnderFunction1;"<<endl;
	cTypeUnderFunction typeUnderFunction1;
	cout<<"cTypeUnderFunction typeUnderFunction2;"<<endl;
	cTypeUnderFunction typeUnderFunction2;

	cout<<"cTypeProperty typeProperty( 1 );"<<endl;
	cTypeProperty typeProperty( 1 );

	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with typeUnderFunction1
	cTypeElement *actualType=&typeUnderFunction1;
	string szActualTypeName="typeUnderFunction1";
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeUnderFunction1, "typeUnderFunction1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeUnderFunction2, "typeUnderFunction2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeUnderFunction2
	actualType=&typeUnderFunction2;
	szActualTypeName="typeUnderFunction2";
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeUnderFunction1, "typeUnderFunction1" );
	iReturn += testCompareTwoEqualTyps( *actualType, szActualTypeName, typeUnderFunction2, "typeUnderFunction2" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeProperty, "typeProperty" );

	//compare with typeProperty
	actualType=&typeProperty;
	szActualTypeName="typeProperty";
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeUnderFunction1, "typeUnderFunction1" );
	iReturn += testCompareTwoNotEqualTyps( *actualType, szActualTypeName, typeUnderFunction2, "typeUnderFunction2" );
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
	cout<<"cTypeUnderFunction typeUnderFunction1;"<<endl;
	cTypeUnderFunction typeUnderFunction1;
	
	cout<<"cTypeUnderFunction typeUnderFunction2;"<<endl;
	cTypeUnderFunction typeUnderFunction2;

	cout<<"cTypeProperty typeProperty( 1 );"<<endl;
	cTypeProperty typeProperty( 1 );

	cout<<"cTypeDimension typeDimension1D3( 3 );"<<endl;
	cTypeDimension typeDimension1D3( 3 );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	if ( typeUnderFunction1.equalElementType( typeUnderFunction1 ) ){
	
		cout<<"The typeUnderFunction1 is of the same type as typeUnderFunction1. "<<endl;
	}else{
		cerr<<"Error: The typeUnderFunction1 is not of the same type as typeUnderFunction1."<<endl;
		iReturn++;
	}
	if ( typeUnderFunction1.equalElementType( typeUnderFunction2 ) ){
	
		cout<<"The typeUnderFunction1 is of the same type as typeUnderFunction2. "<<endl;
	}else{
		cerr<<"Error: The typeUnderFunction1 is not of the same type as typeUnderFunction2."<<endl;
		iReturn++;
	}
	
	if ( ! typeUnderFunction1.equalElementType( typeProperty ) ){
	
		cout<<"The typeUnderFunction1 is not of the same type as typeProperty. "<<endl;
	}else{
		cerr<<"Error: The typeUnderFunction1 is of the same type as typeProperty."<<endl;
		iReturn++;
	}

	if ( ! typeUnderFunction1.equalElementType( typeDimension1D3 ) ){
	
		cout<<"The typeUnderFunction1 is not of the same type as typeDimension1D3. "<<endl;
	}else{
		cerr<<"Error: The typeUnderFunction1 is of the same type as typeDimension1D3."<<endl;
		iReturn++;
	}


	if ( typeUnderFunction2.equalElementType( typeUnderFunction1 ) ){
	
		cout<<"The typeUnderFunction2 is of the same type as typeUnderFunction1. "<<endl;
	}else{
		cerr<<"Error: The typeUnderFunction2 is not of the same type as typeUnderFunction1."<<endl;
		iReturn++;
	}
	if ( typeUnderFunction2.equalElementType( typeUnderFunction2 ) ){
	
		cout<<"The typeUnderFunction2 is of the same type as typeUnderFunction2. "<<endl;
	}else{
		cerr<<"Error: The typeUnderFunction2 is not of the same type as typeUnderFunction2."<<endl;
		iReturn++;
	}
	
	if ( ! typeUnderFunction2.equalElementType( typeProperty ) ){
	
		cout<<"The typeUnderFunction2 is not of the same type as typeProperty. "<<endl;
	}else{
		cerr<<"Error: The typeUnderFunction2 is of the same type as typeProperty."<<endl;
		iReturn++;
	}

	if ( ! typeUnderFunction2.equalElementType( typeDimension1D3 ) ){
	
		cout<<"The typeUnderFunction2 is not of the same type as typeDimension1D3. "<<endl;
	}else{
		cerr<<"Error: The typeUnderFunction2 is of the same type as typeDimension1D3."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests a in the xml -format stored cDomainVector with
 * cDomainNaturalNumberBit domains.
 *
 * @param szFilename the name of the file wher the cDomainNaturalNumberBit is stored
 * @param bHasDomain if true the domain is stored to the type
 * @param uiBits a vector with the bits the cDomainNaturalNumberBit
 * 	domains have
 * @param dScalingfactor a vector with the scalingfactors for the
 * 	cDomainNaturalNumberBit domains have
 * @return the number of errors occured in the test
 */
int testXmlType( const string szFilename,
		bool bHasDomain, unsigned int uiBits, double dScalingfactor ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored type:"<<endl;
	
	TiXmlDocument xmlDocType( szFilename );
	bool loadOkay = xmlDocType.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the type was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocType );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlRootHandle( 0 );

	pXmlElement = xmlHandle.FirstChildElement().Element();
	
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();

		if ( szElementName == "subfunction" ){
			cout<<"The root element is correctly named \"subfunction\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \"subfunction\"."<<endl;
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
		
		if ( ( dScalingfactor == 1.0 ) && ( pcAttributeScalingfactor == NULL ) ){
			//no scalingfactor needed
			cout<<"No scalingfactor attribut. This is correct because the scalingfactor is 1.0 . "<<endl;
		}else{
			if ( pcAttributeScalingfactor == NULL ){
				cerr<<"Error: The domain has no attribute scalingfactor."<<endl;
				iReturn++;
			}else{
				long long lMantissa = 0;
				long long lExponent = 0;
				// construct an istream containing a number
				stringstream sinScalingfactor( pcAttributeScalingfactor );

				// read the number -- the crucial bit
				char c = 0;
				sinScalingfactor >> lMantissa;
				while ( (c != '(') && sinScalingfactor ){
					sinScalingfactor >> c;
				}
				sinScalingfactor >> lExponent;

				if ( ( lfMantissa == lMantissa ) &&  ( lfExponent == lExponent ) ) {
					 cout<<"The scalingfactor of the domain is correctly \""<< pcAttributeScalingfactor <<"\". "<<endl;
				}else{
					 cerr<<"Error: The scalingfactor of the loaded domain is \""<< pcAttributeScalingfactor<<
						"\" (=\""<<lMantissa <<" * 2^("<< lExponent <<")\") "<<
						", but should be \""<< dScalingfactor <<"\" (=\""<<
						lfMantissa <<" * 2^("<< lfExponent <<")\")."<<endl;
					iReturn++;
				}
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple underfunction type"<<endl;

	cout<<"cTypeUnderFunction typeUnderFunction1;"<<endl;
	cTypeUnderFunction typeUnderFunction1;

	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeUnderFunction1.xml" );
	ofstream * fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeUnderFunction1.storeXml( *fileXml );"<<endl;
	bool bStoreSuccesfull = typeUnderFunction1.storeXml( *fileXml );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, false, 0, 0.0 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a underfunction type with a domain"<<endl;

	cout<<"cTypeUnderFunction typeUnderFunction2;"<<endl;
	cTypeUnderFunction typeUnderFunction2;

	cout<<"cDomainNaturalNumberBit domainNaturalNumberB4( 4 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberB4( 4 );
	unsigned int uiBits = 4;
	double dScalingfactor = 1.0;

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeUnderFunction2.xml" );
	fileXml = new ofstream( szFileNameBuffer );
	
	cout<<"typeUnderFunction2.storeXml( *fileXml, &domainNaturalNumberB4 );"<<endl;
	bStoreSuccesfull = typeUnderFunction2.storeXml( *fileXml, &domainNaturalNumberB4 );
	delete fileXml;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	iReturn += testXmlType( szFileNameBuffer, true, uiBits, dScalingfactor );


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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a simple underfunction type"<<endl;
	
	cout<<"cTypeUnderFunction typeUnderFunction1;"<<endl;
	cTypeUnderFunction typeUnderFunction1;

	//test get compressed size
	unsigned int uiCompressedSize = 8;
	if ( (unsigned int)(typeUnderFunction1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeUnderFunction1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeUnderFunction1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0;
	unsigned char cNumberOfRestBit = 0 ;
	bool bStoreSuccesfull = typeUnderFunction1.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	
	if ( ( cRestBit == 0x00 ) && ( cNumberOfRestBit == 0 ) ){
		cout<<"The restbit is \"0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0 and number of restbit should be 0. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeUnderFunction1[] = { 0x10,
		0x00 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeUnderFunction1, 2 );


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing storing a underfunction type with 5 restbitsbits"<<endl;
	
	cout<<"cTypeUnderFunction typeUnderFunction2;"<<endl;
	cTypeUnderFunction typeUnderFunction2;

	//test get compressed size
	uiCompressedSize = 8;
	if ( (unsigned int)(typeUnderFunction2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			typeUnderFunction2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "typeUnderFunction2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0x08;
	cNumberOfRestBit = 5;
	bStoreSuccesfull = typeUnderFunction2.store( *pFile, cRestBit, cNumberOfRestBit );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	unsigned char ucRestBit = cRestBit;
	if ( ( ucRestBit == (unsigned char)(0x02) ) && ( cNumberOfRestBit == 5 ) ){
		cout<<"The restbit is \"0x"<< hex << (unsigned short)cRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \"0x"<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cNumberOfRestBit <<
			", but the restbit should be 0x02 and number of restbit should be 5. "<<endl;
		iReturn++;
	}

	//test stored data
	const char cTypeUnderFunction2[] = { 0x08,
		0x02 }; //restbit
	iReturn += compareBytsWithFile( szFileNameBuffer, cTypeUnderFunction2, 2 );


	return iReturn;
}


