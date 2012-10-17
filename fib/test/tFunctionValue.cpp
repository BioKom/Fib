/**
 * @file tFunctionValue
 * file name: tFunctionValue.cpp
 * @author Betti Oesterholz
 * @date 28.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cFunctionValue.
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
 * This file contains the test for the class cFunctionValue, which
 * represents a value Fib -underfunction.
 *
 *
 * What's tested of class cFunctionValue:
 * 	- cFunctionValue( double dInValue, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cFunctionValue( const cFunctionValue & underfunction, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- cFunctionValue( const TiXmlElement * pXmlElement, intFib & outStatus, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cFunctionValue( cReadBits & iBitStream, intFib & outStatus, const cDomainSingle * pInValueDomain, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- ~cFunctionValue();
 * 	- bool isValid() const;
 * 	- bool isUsedVariable( const cFibVariable * variable ) const;
 * 	- set<cFibVariable*> getUsedVariables();
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- doubleFib getValue() const;
 * 	- unsignedIntFib getNumberOfUnderFunctions() const;
 * 	- cTypeElement * getElementType() const;
 * 	- cDomainSingle * getDomain() const;
 * 	- cDomainSingle * getValueDomain() const;
 * 	- cDomainSingle * getStandardDomain() const;
 * 	- cDomainSingle * getVariableDomain() const;
 * 	- cFibElement * getDefiningFibElement() const;
 * 	- cUnderFunction * getSuperiorUnderFunction() const;
 * 	- void setDefiningFibElement( cFibElement *fibElement=NULL, bool bCheckDomains=true );
 * 	- unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- cUnderFunction * restoreXml( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- bool storeXml( ostream &stream ) const;
 * 	- cUnderFunction * restore( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInValueDomain, const cDomainSingle * pInDomainVariable, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 * 	- unsignedIntFib getType() const;
 * 	- string getUnderFunctionName() const;
 * 	- bool equal( const cUnderFunction &underfunction ) const;
 * 	- bool operator==( const cUnderFunction &underfunction ) const;
 * 	- bool operator!=( const cUnderFunction &underfunction ) const;
 * 	- cUnderFunction * clone( cUnderFunction * pInSuperiorUnderFunction = NULL, cFibElement *pInDefiningFibElement = NULL) const;
 *
 */
/*
History:
28.04.2010  Oesterholz  created
04.04.2011  Oesterholz  storing to binary stream
30.04.2011  Oesterholz  scanf long for 64 bit and windows
*/

#include "version.h"

#include "cFunctionValue.h"
#include "cPoint.h"
#include "cRoot.h"
#include "cProperty.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cTypeVariable.h"
#include "cTypeUnderFunction.h"
#include "cTypeInVar.h"
#include "cVectorProperty.h"
#include "cEvaluePositionList.h"
#include "cEvalueFibElementList.h"
#include "cReadBits.h"

#include "tinyxml.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <ctime>

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif



using namespace fib;
using namespace std;


int testCostructor( unsigned long &ulTestphase );
int testEqual( unsigned long &ulTestphase );
int testCopy( unsigned long &ulTestphase );
int testStoreXml( unsigned long &ulTestphase );
int testStore( unsigned long &ulTestphase );
int testVariable( unsigned long &ulTestphase );
int testDefiningFibElement( unsigned long &ulTestphase );


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for cFunctionValue methods"<<endl;
	cout<<      "======================================="<<endl;

	iReturn += testCostructor( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testVariable( ulTestphase );
	iReturn += testDefiningFibElement( ulTestphase );


	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}



/**
 * This method tests the constructor of the cFunctionValue class.
 *
 * methods tested:
 * 	- cFunctionValue( double dInValue, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- ~cFunctionValue();
 * 	- bool isValid() const;
 * 	- bool isUsedVariable( const cFibVariable * variable ) const;
 * 	- set<cFibVariable*> getUsedVariables();
 * 	- doubleFib getValue() const;
 * 	- unsignedIntFib getNumberOfUnderFunctions() const;
 * 	- cTypeElement * getElementType() const;
 * 	- cDomainSingle * getDomain() const;
 * 	- cDomainSingle * getValueDomain() const;
 * 	- cDomainSingle * getStandardDomain() const;
 * 	- cDomainSingle * getVariableDomain() const;
 * 	- cFibElement * getDefiningFibElement() const;
 * 	- cUnderFunction * getSuperiorUnderFunction() const;
 * 	- unsignedLongFib getTimeNeed( unsignedLongFib lMaxTime=0 ) const;
 * 	- unsignedLongFib getCompressedSize() const;
 * 	- unsignedIntFib getType() const;
 * 	- string getUnderFunctionName() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCostructor( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<"cRoot rootEmpty;"<<endl;
	cRoot rootEmpty;
	cout<<"rootEmpty.setNumberOfInputVariables( 10 );"<<endl;
	rootEmpty.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 =  rootEmpty.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 =  rootEmpty.getInputVariable( 1 );
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cFunctionValue underfunction"<<endl;

	cout<<"cFunctionValue underFunctionValue1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue1( 1.0 );
	double dValue = 1.0;
	cFibElement * pDefiningFibElement = NULL;
	cUnderFunction * pSuperiorUnderFunction = NULL;
	cTypeUnderFunction typeUnderFunction;
	cDomain * pUnderFunctionDomain = NULL;
	cDomain * pValueDomain = NULL;
	cDomain * pStandardDomain = typeUnderFunction.getStandardDomain();
	cTypeVariable typeVariable;
	cDomain * pVariableDomain = typeVariable.getStandardDomain();
	unsigned long ulTimeNeed = 1;
	unsigned long ulCompressedSize = 2 + 16;
 
	//check the getValue() methode from cFunctionValue
	if ( underFunctionValue1.getValue() == dValue  ){
	
		cout<<"The underfunction value is correctly "<<
			underFunctionValue1.getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			underFunctionValue1.getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionValue
	if ( underFunctionValue1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionValue1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionValue1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionValue
	if ( underFunctionValue1.getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			underFunctionValue1.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			underFunctionValue1.getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionValue
	if ( ! underFunctionValue1.isValid() ){
	
		cout<<"The underfunction is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionValue
	if ( underFunctionValue1.getType() == 0 ){
	
		cout<<"The underfunction type is correctly FUNCTION_VALUE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VALUE ( 0 ), but "<<
			underFunctionValue1.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionValue
	if ( underFunctionValue1.getUnderFunctionName() == "value" ){
	
		cout<<"The underfunction name is correctly "<<
			underFunctionValue1.getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"value\", but "<<
			underFunctionValue1.getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionValue
	if ( underFunctionValue1.getNumberOfUnderFunctions() == 0 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			underFunctionValue1.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			underFunctionValue1.getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionValue
	cTypeElement * pTypeOfUnderFunction = underFunctionValue1.getElementType();
	if ( pTypeOfUnderFunction != NULL ){
		if ( * pTypeOfUnderFunction == typeUnderFunction ){
		
			cout<<"The given back element type for the underfunction is correct. "<<endl;
		}else{
			cerr<<"Error: The given back element type for the underfunction is not correct."<<endl;
			iReturn++;
		}
		delete pTypeOfUnderFunction;
	}else{
		cerr<<"Error: The given back element type for the underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cFunctionValue
	cDomain * pRetUnderFunctionDomain = underFunctionValue1.getDomain();
	if ( pUnderFunctionDomain != NULL ){
		if ( pRetUnderFunctionDomain != NULL ){
			if ( * pRetUnderFunctionDomain == * pUnderFunctionDomain ){
			
				cout<<"The given back domain for the underfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back domain for the underfunction is not correct."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The given back domain for the underfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		if ( pRetUnderFunctionDomain == NULL ){
		
			cout<<"The given back domain for the underfunction is correctly NULL . "<<endl;
		}else{
			cerr<<"Error: The given back domain for the underfunction is not NULL ."<<endl;
			iReturn++;
		}
	}
	//check the getValueDomain() methode from cFunctionValue
	cDomain * pRetValueDomain = underFunctionValue1.getValueDomain();
	if ( pValueDomain != NULL ){
		if ( pRetValueDomain != NULL ){
			if ( * pRetValueDomain == * pValueDomain ){
			
				cout<<"The given back valuedomain for the underfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back valuedomain for the underfunction is not correct."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The given back valuedomain for the underfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		if ( pRetValueDomain == NULL ){
		
			cout<<"The given back valuedomain for the underfunction is correctly NULL . "<<endl;
		}else{
			cerr<<"Error: The given back valuedomain for the underfunction is not NULL ."<<endl;
			iReturn++;
		}
	}
	//check the getStandardDomain() methode from cFunctionValue
	cDomain * pRetStandardDomain = underFunctionValue1.getStandardDomain();
	if ( pStandardDomain != NULL ){
		if ( pRetStandardDomain != NULL ){
			if ( * pRetStandardDomain == * pStandardDomain ){
			
				cout<<"The given back the standarddomain for the underfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back the standarddomain domain for the underfunction is not correct."<<endl;
				iReturn++;
			}
			delete pRetStandardDomain;
		}else{
			cerr<<"Error: The given back the standarddomain domain for the underfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The given back the standarddomain domain for the underfunction is not NULL ."<<endl;
	}
	//check the getVariableDomain() methode from cFunctionValue
	cDomain * pRetVariableDomain = underFunctionValue1.getVariableDomain();
	if ( pVariableDomain != NULL ){
		if ( pRetVariableDomain != NULL ){
			if ( * pRetVariableDomain == * pVariableDomain ){
			
				cout<<"The given back variabledomain for the underfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back variabledomain for the underfunction is not correct."<<endl;
				iReturn++;
			}
			delete pRetVariableDomain;
		}else{
			cerr<<"Error: The given back variabledomain for the underfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		if ( pRetVariableDomain == NULL ){
		
			cout<<"The given back variabledomain for the underfunction is correctly NULL . "<<endl;
		}else{
			cerr<<"Error: The given back variabledomain for the underfunction is not NULL ."<<endl;
			iReturn++;
			delete pRetVariableDomain;
		}
	}
	//check the getTimeNeed() methode from cFunctionValue
	if ( underFunctionValue1.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			underFunctionValue1.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionValue
	if ( underFunctionValue1.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the function is "<<
			underFunctionValue1.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionValue
	if ( ! underFunctionValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionValue
	set<cFibVariable*> setUsedVariables = underFunctionValue1.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"No used variables are given back from the underfunction. "<<endl;
	}else{
		cerr<<"Error: Used variables are given back from the underfunction. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an cFunctionValue underfunction"<<endl;

	cout<<"cFunctionValue underFunctionValue2( -13.52, &underFunctionValue1, &rootEmpty  );"<<endl;
	cFunctionValue underFunctionValue2( -13.52, &underFunctionValue1, &rootEmpty );
	
	cout<<"cDomainNaturalNumberBit domainNaturalNumberBit3( 3 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberBit3( 3 );
	cout<<"cDomainNaturalNumberBit domainNaturalNumberBit5( 5 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberBit5( 5 );
	cout<<"cDomainNaturalNumberBit domainNaturalNumberBit7( 7 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberBit7( 7 );
	
	cout<<"rootEmpty.getDomains()->addDomain( typeVariable, domainNaturalNumberBit3 );"<<endl;
	rootEmpty.getDomains()->addDomain( typeVariable, domainNaturalNumberBit3 );
	cout<<"rootEmpty.getDomains()->addDomain( typeUnderFunction, domainNaturalNumberBit5 );"<<endl;
	rootEmpty.getDomains()->addDomain( typeUnderFunction, domainNaturalNumberBit5 );
	cout<<"rootEmpty.getValueDomains()->addDomain( typeUnderFunction, domainNaturalNumberBit7 );"<<endl;
	rootEmpty.getValueDomains()->addDomain( typeUnderFunction, domainNaturalNumberBit7 );
	
	dValue = -13.52;
	pDefiningFibElement = &rootEmpty;
	pSuperiorUnderFunction = &underFunctionValue1;
	
	pUnderFunctionDomain = &domainNaturalNumberBit5;
	pValueDomain = &domainNaturalNumberBit7;

	delete pVariableDomain;
	pVariableDomain = domainNaturalNumberBit3.clone();
	ulCompressedSize = 2 + 7;

	//check the getValue() methode from cFunctionValue
	if ( underFunctionValue2.getValue() == dValue  ){
	
		cout<<"The underfunction value is correctly "<<
			underFunctionValue2.getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			underFunctionValue2.getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionValue
	if ( underFunctionValue2.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionValue2.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionValue2.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionValue
	if ( underFunctionValue2.getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			underFunctionValue2.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			underFunctionValue2.getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionValue
	if ( ! underFunctionValue2.isValid() ){
	
		cout<<"The underfunction is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionValue
	if ( underFunctionValue2.getType() == 0 ){
	
		cout<<"The underfunction type is correctly FUNCTION_VALUE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VALUE ( 0 ), but "<<
			underFunctionValue2.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionValue
	if ( underFunctionValue2.getUnderFunctionName() == "value" ){
	
		cout<<"The underfunction name is correctly "<<
			underFunctionValue2.getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"value\", but "<<
			underFunctionValue2.getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionValue
	if ( underFunctionValue2.getNumberOfUnderFunctions() == 0 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			underFunctionValue2.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			underFunctionValue2.getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionValue
	pTypeOfUnderFunction = underFunctionValue2.getElementType();
	if ( pTypeOfUnderFunction != NULL ){
		if ( * pTypeOfUnderFunction == typeUnderFunction ){
		
			cout<<"The given back element type for the underfunction is correct. "<<endl;
		}else{
			cerr<<"Error: The given back element type for the underfunction is not correct."<<endl;
			iReturn++;
		}
		delete pTypeOfUnderFunction;
	}else{
		cerr<<"Error: The given back element type for the underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cFunctionValue
	pRetUnderFunctionDomain = underFunctionValue2.getDomain();
	if ( pUnderFunctionDomain != NULL ){
		if ( pRetUnderFunctionDomain != NULL ){
			if ( * pRetUnderFunctionDomain == * pUnderFunctionDomain ){
			
				cout<<"The given back domain for the underfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back domain for the underfunction is not correct."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The given back domain for the underfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		if ( pRetUnderFunctionDomain == NULL ){
		
			cout<<"The given back domain for the underfunction is correctly NULL . "<<endl;
		}else{
			cerr<<"Error: The given back domain for the underfunction is not NULL ."<<endl;
			iReturn++;
		}
	}
	//check the getValueDomain() methode from cFunctionValue
	pRetValueDomain = underFunctionValue2.getValueDomain();
	if ( pValueDomain != NULL ){
		if ( pRetValueDomain != NULL ){
			if ( * pRetValueDomain == * pValueDomain ){
			
				cout<<"The given back valuedomain for the underfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back valuedomain for the underfunction is not correct."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The given back valuedomain for the underfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		if ( pRetValueDomain == NULL ){
		
			cout<<"The given back valuedomain for the underfunction is correctly NULL . "<<endl;
		}else{
			cerr<<"Error: The given back valuedomain for the underfunction is not NULL ."<<endl;
			iReturn++;
		}
	}
	//check the getStandardDomain() methode from cFunctionValue
	pRetStandardDomain = underFunctionValue2.getStandardDomain();
	if ( pStandardDomain != NULL ){
		if ( pRetStandardDomain != NULL ){
			if ( * pRetStandardDomain == * pStandardDomain ){
			
				cout<<"The given back the standarddomain for the underfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back the standarddomain domain for the underfunction is not correct."<<endl;
				iReturn++;
			}
			delete pRetStandardDomain;
		}else{
			cerr<<"Error: The given back the standarddomain domain for the underfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The given back the standarddomain domain for the underfunction is not NULL ."<<endl;
	}
	//check the getVariableDomain() methode from cFunctionValue
	pRetVariableDomain = underFunctionValue2.getVariableDomain();
	if ( pVariableDomain != NULL ){
		if ( pRetVariableDomain != NULL ){
			if ( * pRetVariableDomain == * pVariableDomain ){
			
				cout<<"The given back variabledomain for the underfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back variabledomain for the underfunction is not correct."<<endl;
				iReturn++;
			}
			delete pRetVariableDomain;
		}else{
			cerr<<"Error: The given back variabledomain for the underfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		if ( pRetVariableDomain == NULL ){
		
			cout<<"The given back variabledomain for the underfunction is correctly NULL . "<<endl;
		}else{
			cerr<<"Error: The given back variabledomain for the underfunction is not NULL ."<<endl;
			iReturn++;
			delete pRetVariableDomain;
		}
	}
	//check the getTimeNeed() methode from cFunctionValue
	if ( underFunctionValue2.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			underFunctionValue2.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionValue
	if ( underFunctionValue2.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the function is "<<
			underFunctionValue2.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionValue
	if ( ! underFunctionValue2.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionValue
	setUsedVariables = underFunctionValue2.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"No used variables are given back from the underfunction. "<<endl;
	}else{
		cerr<<"Error: Used variables are given back from the underfunction. "<<endl;
		iReturn++;
	}

	
	if ( pStandardDomain ){
		delete pStandardDomain;
	}
	if ( pVariableDomain ){
		delete pVariableDomain;
	}

	return iReturn;
}


/**
 * This method tests the equal() method of two given fib -objects which are
 * equal.
 *
 * @param underFunction1 the first fib -object to compare
 * @param szNameObject1 the name of the first fib -object to compare
 * @param underFunction2 the secound fib -object to compare to
 * @param szNameObject2 the name of the secound fib -object to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualObjects( const cUnderFunction &underFunction1, const string &szNameObject1,
	const cUnderFunction &underFunction2, const string &szNameObject2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( underFunction1.equal( underFunction2 ) ){
	
		cout<<"The "<<szNameObject1<<" is equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is not equal to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}
	//check operator== for cUnderFunction
	if ( underFunction1 == underFunction2 ){
	
		cout<<"The "<<szNameObject1<<" is equal (operator==) to "<<
			szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is not equal (operator==) to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}
	//check operator!= for cUnderFunction
	if ( ! (underFunction1 != underFunction2) ){
	
		cout<<"The "<<szNameObject1<<" is not not equal (operator!=) to "<<
			szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is not equal (operator!=) to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the equal() method of two given fib -objects which are
 * not equal.
 *
 * @param underFunction1 the first fib -object to compare
 * @param szNameObject1 the name of the first fib -object to compare
 * @param underFunction2 the secound fib -object to compare to
 * @param szNameObject2 the name of the secound fib -object to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualObjects( const cUnderFunction &underFunction1, const string &szNameObject1,
	const cUnderFunction &underFunction2, const string &szNameObject2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! underFunction1.equal( underFunction2 ) ){
	
		cout<<"The "<<szNameObject1<<" is not equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is equal to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}
	//check operator== for cUnderFunction
	if ( ! (underFunction1 == underFunction2) ){
	
		cout<<"The "<<szNameObject1<<" is not equal (operator==) to "<<
			szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is equal (operator==) to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}

	//check operator!= for cUnderFunction
	if ( underFunction1 != underFunction2 ){
	
		cout<<"The "<<szNameObject1<<" is not equal (operator!=) to "<<
			szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is equal (operator!=) to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests equal method of the cFunctionValue class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing equal methods for functionelements"<<endl;

	cout<<endl<<"Creating functionobjects objects to compare: "<<endl<<endl;

	//function with a empty functionvector
	cout<<"cFunctionValue underFunctionValue1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue1( 1.0 );

	cout<<"cFunctionValue underFunctionValue2( 1.0 );"<<endl;
	cFunctionValue underFunctionValue2( 1.0 );


	//function with one changed underfunction
	cout<<"cFunctionValue underFunctionValue3( 3.0 );"<<endl;
	cFunctionValue underFunctionValue3( 3.0 );

	cout<<"cFunctionValue underFunctionValue3p3( 3.3 );"<<endl;
	cFunctionValue underFunctionValue3p3( 3.3 );

	cout<<"cFunctionValue underFunctionValuem1( -1.0 );"<<endl;
	cFunctionValue underFunctionValuem1( -1.0 );

	//function with defining fib -element
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	cout<<"cFunctionValue functionDefFE( 1.0, NULL, &rootSimple1 );"<<endl;
	cFunctionValue functionDefFE( 1.0, NULL, &rootSimple1 );

	//function with superior underfunction
	cout<<"cFunctionValue underFunctionSup( 3.33 );"<<endl;
	cFunctionValue underFunctionSup( 3.333 );
	cout<<"cFunctionValue functionSup( 1.0, & underFunctionSup );"<<endl;
	cFunctionValue functionSup( 1.0, & underFunctionSup );

	//underfunction with domains set
	cout<<"root1 rootSimple1;"<<endl;
	cRoot root1;
	
	cout<<"cTypeUnderFunction testTypeFunctionValue;"<<endl;
	cTypeUnderFunction testTypeFunctionValue;
	cout<<"cDomainNaturalNumberBit domainNat8( 8 );"<<endl;
	cDomainNaturalNumberBit domainNat8( 8 );

	cout<<"root1.getDomains()->addDomain( testTypeFunctionValue, &domainNat8 );"<<endl;
	root1.getDomains()->addDomain( testTypeFunctionValue, &domainNat8 );

	cout<<"cFunctionValue functionDom( 1.0, NULL, &root1 );"<<endl;
	cFunctionValue functionDom( 1.0, NULL, &root1 );

	//function with defining fib -element and superior underfunction
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cFunctionValue underFunctionSup2( 325.142 );"<<endl;
	cFunctionValue underFunctionSup2( 325.142 );
	cout<<"cFunctionValue functionDefFeUf( 1.0, & underFunctionSup2, &rootSimple2 );"<<endl;
	cFunctionValue functionDefFeUf( 1.0, & underFunctionSup2, &rootSimple2 );



	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with underFunctionValue1
	cUnderFunction * actualObject = &underFunctionValue1;
	string szActualObjectName = "underFunctionValue1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValue1, "underFunctionValue1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValue2, "underFunctionValue2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3, "underFunctionValue3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3p3, "underFunctionValue3p3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValuem1, "underFunctionValuem1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with underFunctionValue2
	actualObject = &underFunctionValue2;
	szActualObjectName = "underFunctionValue2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValue1, "underFunctionValue1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValue2, "underFunctionValue2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3, "underFunctionValue3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3p3, "underFunctionValue3p3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValuem1, "underFunctionValuem1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with underFunctionValue3
	actualObject = &underFunctionValue3;
	szActualObjectName = "underFunctionValue3";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue1, "underFunctionValue1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue2, "underFunctionValue2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValue3, "underFunctionValue3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3p3, "underFunctionValue3p3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValuem1, "underFunctionValuem1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with underFunctionValue3p3
	actualObject = &underFunctionValue3p3;
	szActualObjectName = "underFunctionValue3p3";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue1, "underFunctionValue1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue2, "underFunctionValue2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3, "underFunctionValue3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValue3p3, "underFunctionValue3p3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValuem1, "underFunctionValuem1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with underFunctionValuem1
	actualObject = &underFunctionValuem1;
	szActualObjectName = "underFunctionValuem1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue1, "underFunctionValue1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue2, "underFunctionValue2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3, "underFunctionValue3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3p3, "underFunctionValue3p3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValuem1, "underFunctionValuem1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with functionDefFE
	actualObject = &functionDefFE;
	szActualObjectName = "functionDefFE";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValue1, "underFunctionValue1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValue2, "underFunctionValue2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3, "underFunctionValue3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3p3, "underFunctionValue3p3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValuem1, "underFunctionValuem1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with functionSup
	actualObject = &functionSup;
	szActualObjectName = "functionSup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValue1, "underFunctionValue1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValue2, "underFunctionValue2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3, "underFunctionValue3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3p3, "underFunctionValue3p3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValuem1, "underFunctionValuem1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with functionDom
	actualObject = &functionDom;
	szActualObjectName = "functionDom";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValue1, "underFunctionValue1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValue2, "underFunctionValue2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3, "underFunctionValue3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3p3, "underFunctionValue3p3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValuem1, "underFunctionValuem1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with functionDefFeUf
	actualObject = &functionDefFeUf;
	szActualObjectName = "functionDefFeUf";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValue1, "underFunctionValue1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionValue2, "underFunctionValue2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3, "underFunctionValue3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValue3p3, "underFunctionValue3p3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionValuem1, "underFunctionValuem1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );


	return iReturn;
}


/**
 * This method tests if the given underfunction is not conected to other
 * underfunctions or fib -elements.
 *
 * @param underfunctionObject1 the underfunction to check
 * @return the number of errors occured in the test
 */
int testNotConnectedUnderFunction( const cUnderFunction & underfunctionObject1 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	//check the getNextFibElement() methode
	if ( underfunctionObject1.getSuperiorUnderFunction() == NULL ){
	
		cout<<"The superior underfunctionpointer for the functionelement is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The superior underfunctionpointer for the functionelement is not NULL, but "<<
			underfunctionObject1.getSuperiorUnderFunction() <<" ."<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode
	if ( underfunctionObject1.getDefiningFibElement() == NULL ){
	
		cout<<"The defining fib -elementpointer for the function is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The defining fib -elementpointer for the function is not NULL."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the copy methods and copyconstructor of the cFunctionValue class.
 *
 * methods tested:
 * 	- cFunctionValue( const cFunctionValue & underfunction, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- cUnderFunction * clone( cUnderFunction * pInSuperiorUnderFunction = NULL, cFibElement *pInDefiningFibElement = NULL) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a simple cFunctionValue"<<endl;

	cout<<"cFunctionValue underFunctionValue1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue1( 1.0 );

	cout<<"cFunctionValue underFunctionValue1CopyConstruct( underFunctionValue1 );"<<endl;
	cFunctionValue underFunctionValue1CopyConstruct( underFunctionValue1 );

	iReturn += testCompareTwoEqualObjects( underFunctionValue1CopyConstruct, "underFunctionValue1CopyConstruct", underFunctionValue1, "underFunctionValue1" );
	iReturn += testNotConnectedUnderFunction( underFunctionValue1CopyConstruct );

	cout<<"cUnderFunction * pUnderFunctionValue1Clone = underFunctionValue1CopyConstruct.clone();"<<endl;
	cUnderFunction * pUnderFunctionValue1Clone = underFunctionValue1CopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pUnderFunctionValue1Clone, "pUnderFunctionValue1Clone", underFunctionValue1, "underFunctionValue1" );
	iReturn += testNotConnectedUnderFunction( *pUnderFunctionValue1Clone );
	delete pUnderFunctionValue1Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionValue with value -3.3"<<endl;

	cout<<"cFunctionValue underFunctionValuem3p3( -3.3 );"<<endl;
	cFunctionValue underFunctionValuem3p3( -3.3 );

	cout<<"cFunctionValue underFunctionValuem3p3CopyConstruct( underFunctionValuem3p3 );"<<endl;
	cFunctionValue underFunctionValuem3p3CopyConstruct( underFunctionValuem3p3 );

	iReturn += testCompareTwoEqualObjects( underFunctionValuem3p3CopyConstruct, "underFunctionValuem3p3CopyConstruct", underFunctionValuem3p3, "underFunctionValuem3p3" );
	iReturn += testNotConnectedUnderFunction( underFunctionValuem3p3CopyConstruct );

	cout<<"cUnderFunction * pUnderFunctionValuem3p3Clone = underFunctionValuem3p3CopyConstruct.clone();"<<endl;
	cUnderFunction * pUnderFunctionValuem3p3Clone = underFunctionValuem3p3CopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pUnderFunctionValuem3p3Clone, "pUnderFunctionValuem3p3Clone", underFunctionValuem3p3, "underFunctionValuem3p3" );
	iReturn += testNotConnectedUnderFunction( *pUnderFunctionValuem3p3Clone );
	delete pUnderFunctionValuem3p3Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionValue with a superior underfunction and defining fib -element"<<endl;

	//function with defining fib -element and superior underfunction
	cout<<"cRoot rootSimple;"<<endl;
	cRoot rootSimple;
	cout<<"cFunctionValue underFunctionSup( 325.142 );"<<endl;
	cFunctionValue underFunctionSup( 325.142 );
	cout<<"cFunctionValue functionDefFeUf( 111.33, & underFunctionSup, &rootSimple );"<<endl;
	cFunctionValue functionDefFeUf( 111.33, & underFunctionSup, &rootSimple );

	cout<<"cFunctionValue functionDefFeUfCopyConstruct( functionDefFeUf );"<<endl;
	cFunctionValue functionDefFeUfCopyConstruct( functionDefFeUf );

	iReturn += testCompareTwoEqualObjects( functionDefFeUfCopyConstruct, "functionDefFeUfCopyConstruct", functionDefFeUf, "functionDefFeUf" );
	//check the getDefiningFibElement() methode from cFunctionValue
	if ( functionDefFeUfCopyConstruct.getDefiningFibElement() == &rootSimple  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			functionDefFeUfCopyConstruct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			functionDefFeUfCopyConstruct.getDefiningFibElement() <<" but should be rootSimple ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionValue
	if ( functionDefFeUfCopyConstruct.getSuperiorUnderFunction() == NULL  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			functionDefFeUfCopyConstruct.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			functionDefFeUfCopyConstruct.getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	
	cout<<"cUnderFunction * pFunctionDefFeUfClone = functionDefFeUfCopyConstruct.clone();"<<endl;
	cUnderFunction * pFunctionDefFeUfClone = functionDefFeUfCopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pFunctionDefFeUfClone, "pFunctionDefFeUfClone", functionDefFeUf, "functionDefFeUf" );
	//check the getDefiningFibElement() methode from cFunctionValue
	if ( pFunctionDefFeUfClone->getDefiningFibElement() == &rootSimple  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			pFunctionDefFeUfClone->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			pFunctionDefFeUfClone->getDefiningFibElement() <<" but should be rootSimple ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionValue
	if ( pFunctionDefFeUfClone->getSuperiorUnderFunction() == NULL  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			pFunctionDefFeUfClone->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			pFunctionDefFeUfClone->getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	delete pFunctionDefFeUfClone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionTwoValue with a superior underfunction and defining fib -element which will be changed"<<endl;

	//function with defining fib -element and superior underfunction
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cFunctionValue underFunctionSup2( 42.0 );"<<endl;
	cFunctionValue underFunctionSup2( 42.0 );

	cout<<"cFunctionValue functionDefFeUfCopy2Construct( functionDefFeUf, &underFunctionSup2, &rootSimple2 );"<<endl;
	cFunctionValue functionDefFeUfCopy2Construct( functionDefFeUf, &underFunctionSup2, &rootSimple2 );

	iReturn += testCompareTwoEqualObjects( functionDefFeUfCopy2Construct, "functionDefFeUfCopy2Construct", functionDefFeUf, "functionDefFeUf" );
	//check the getDefiningFibElement() methode from cFunctionValue
	if ( functionDefFeUfCopy2Construct.getDefiningFibElement() == &rootSimple2  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			functionDefFeUfCopy2Construct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			functionDefFeUfCopy2Construct.getDefiningFibElement() <<" but should be rootSimple2 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionValue
	if ( functionDefFeUfCopy2Construct.getSuperiorUnderFunction() == &underFunctionSup2  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			functionDefFeUfCopy2Construct.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			functionDefFeUfCopy2Construct.getSuperiorUnderFunction() <<
			" but should be underFunctionSup2 ."<<endl;
		iReturn++;
	}
	
	cout<<"pFunctionDefFeUfClone = functionDefFeUfCopyConstruct.clone( &underFunctionSup2, &rootSimple2 );"<<endl;
	pFunctionDefFeUfClone = functionDefFeUfCopyConstruct.clone( &underFunctionSup2, &rootSimple2 );

	iReturn += testCompareTwoEqualObjects( *pFunctionDefFeUfClone, "pFunctionDefFeUfClone", functionDefFeUf, "functionDefFeUf" );
	//check the getDefiningFibElement() methode from cFunctionValue
	if ( pFunctionDefFeUfClone->getDefiningFibElement() == &rootSimple2  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			pFunctionDefFeUfClone->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			pFunctionDefFeUfClone->getDefiningFibElement() <<" but should be rootSimple2 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionValue
	if ( pFunctionDefFeUfClone->getSuperiorUnderFunction() == &underFunctionSup2  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			pFunctionDefFeUfClone->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			pFunctionDefFeUfClone->getSuperiorUnderFunction() <<
			" but should be underFunctionSup2 ."<<endl;
		iReturn++;
	}
	delete pFunctionDefFeUfClone;



	return iReturn;
}



/**
 * This method tests a in the xml -format stored cFunctionValue.
 * The underfunction of the cFunctionValue should be a value underfunction
 * ( cFunctionValue ).
 *
 * @param szFilename the name of the file wher the cFunctionValue is stored
 * @param dValue the value of the underfunction
 * @return the number of errors occured in the test
 */
int testXmlFunctionValue( const string szFilename, double dValue ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cFunctionValue:"<<endl;
	
	TiXmlDocument xmlDocFunctionValue( szFilename );
	bool loadOkay = xmlDocFunctionValue.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocFunctionValue );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();
		
		const string szFunctionValueElementName = "value";
		if ( szElementName == szFunctionValueElementName ){
			cout<<"The root element is correctly named \""<< szFunctionValueElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szFunctionValueElementName <<"\"."<<endl;
			iReturn++;
		}
		
		const char * pcValue = pXmlElement->GetText();
		cout<<"The value of the underfunction is: "<< pcValue <<endl;
		//converting value to double
		double dValue1 = 0.0;
		int iReadValues = sscanf ( pcValue, "%lf", & dValue1 );
		
		long long lMantissa = 0;
		long long lExponent = 0;
#ifdef WINDOWS
		sscanf( pcValue, "%I64d * 2^(%I64d", & lMantissa, & lExponent );
#else //WINDOWS
		sscanf( pcValue, "%lld * 2^(%lld", & lMantissa, & lExponent );
#endif //WINDOWS
		
		//mantissa and exponent readed
		double dValue2 = ((doubleFib)lMantissa) * pow( 2.0, (doubleFib)lExponent );

		if ( iReadValues != 0){
			if ( (dValue1 == dValue) ||
					(dValue2 == dValue) ){
				cout<<"The value of the element is correct."<<endl;
			}else{
				cerr<<"Error: The value of the element should be : "<<
					dValue <<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The element text is not a number."<<endl;
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
 * This method tests the storeXml() method of the cFunctionValue class.
 * Just storing properties with no underobjects is tested.
 *
 * methods tested:
 * 	- bool storeXml( ostream &stream ) const;
 * 	- cFunctionValue( const TiXmlElement * pXmlElement, intFib & outStatus, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cUnderFunction * restoreXml( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStoreXml( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an underfunction with value 1.0"<<endl;

	cout<<"cFunctionValue underFunctionValue1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue1( 1.0 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlFunctionValueFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "underFunctionValue1.xml" );
	ofstream * pFileUnderFunction = new ofstream( szXmlFunctionValueFileName );
	
	bool bStoreSuccesfull = underFunctionValue1.storeXml( *pFileUnderFunction );
	delete pFileUnderFunction;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFunctionValue was stored successfull to the file \""<< szXmlFunctionValueFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFunctionValue to the file \""<< szXmlFunctionValueFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlFunctionValue( szXmlFunctionValueFileName, underFunctionValue1.getValue() );
	
	TiXmlDocument xmlDocFunctionValue( szFileNameBuffer );
	bool loadOkay = xmlDocFunctionValue.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		cout<<"TiXmlHandle xmlHandle( &xmlDocFunctionValue ); "<<endl;
		TiXmlHandle xmlHandle( &xmlDocFunctionValue );
		cout<<"cFunctionValue underFunctionValue1Loaded( xmlHandle.FirstChildElement().Element(), outStatus ); "<<endl;
		cFunctionValue underFunctionValue1Loaded( xmlHandle.FirstChildElement().Element(), outStatus );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionValue1Loaded, "underFunctionValue1Loaded", underFunctionValue1, "underFunctionValue1" );
		iReturn += testNotConnectedUnderFunction( underFunctionValue1Loaded );

		outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocFunctionValue ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocFunctionValue );
		cout<<"cFunctionValue underFunctionValue1Loaded( xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cUnderFunction * pUnderFunctionValue1Loaded = cUnderFunction::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionValue1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionValue1Loaded, "pUnderFunctionValue1Loaded", underFunctionValue1, "underFunctionValue1" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionValue1Loaded );
			delete pUnderFunctionValue1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorFunction and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cFunctionValue underFunctionSup( 325.142 );"<<endl;
		cFunctionValue underFunctionSup( 325.142 );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle3( &xmlDocFunctionValue ); "<<endl;
		TiXmlHandle xmlHandle3( &xmlDocFunctionValue );
		cout<<"cFunctionValue underFunctionValue1LoadedFull( xmlHandle3.FirstChildElement().Element(), "<<
			"outStatus, &underFunctionSup, &rootSimple ); "<<endl;
		cFunctionValue underFunctionValue1LoadedFull( xmlHandle3.FirstChildElement().Element(),
			outStatus, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionValue1LoadedFull,
			"underFunctionValue1LoadedFull", underFunctionValue1, "underFunctionValue1" );
		//check the getDefiningFibElement() methode from cFunctionValue
		if ( underFunctionValue1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionValue1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionValue1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionValue
		if ( underFunctionValue1LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionValue1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionValue1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		
		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDocFunctionValue ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocFunctionValue );
		cout<<"cFunctionValue pUnderFunctionValue1LoadedFull = cUnderFunction::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionValue1LoadedFull = cUnderFunction::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionValue1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionValue1LoadedFull, "pUnderFunctionValue1LoadedFull", underFunctionValue1, "underFunctionValue1" );
			//check the getDefiningFibElement() methode from cFunctionValue
			if ( pUnderFunctionValue1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionValue1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionValue1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionValue
			if ( pUnderFunctionValue1LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionValue1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionValue1LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctionValue1LoadedFull;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an underfunction with value -321.591"<<endl;

	cout<<"cFunctionValue underFunctionValue2( -321.591 );"<<endl;
	cFunctionValue underFunctionValue2( -321.591 );
	
	szFileNameBuffer[0] = 0;
	szXmlFunctionValueFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "underFunctionValue2.xml" );
	pFileUnderFunction = new ofstream( szXmlFunctionValueFileName );
	
	bStoreSuccesfull = underFunctionValue2.storeXml( *pFileUnderFunction );
	delete pFileUnderFunction;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFunctionValue was stored successfull to the file \""<< szXmlFunctionValueFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFunctionValue to the file \""<< szXmlFunctionValueFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlFunctionValue( szXmlFunctionValueFileName, underFunctionValue2.getValue() );
	
	TiXmlDocument xmlDocFunctionValue2( szFileNameBuffer );
	loadOkay = xmlDocFunctionValue2.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		cout<<"TiXmlHandle xmlHandle( &xmlDocFunctionValue2 ); "<<endl;
		TiXmlHandle xmlHandle( &xmlDocFunctionValue2 );
		cout<<"cFunctionValue underFunctionValue2Loaded( xmlHandle.FirstChildElement().Element(), outStatus ); "<<endl;
		cFunctionValue underFunctionValue2Loaded( xmlHandle.FirstChildElement().Element(), outStatus );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionValue2Loaded, "underFunctionValue2Loaded", underFunctionValue2, "underFunctionValue2" );
		iReturn += testNotConnectedUnderFunction( underFunctionValue2Loaded );

		outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocFunctionValue2 ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocFunctionValue2 );
		cout<<"pUnderFunctionValue2Loaded = cUnderFunction::restoreXml( "<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cUnderFunction * pUnderFunctionValue2Loaded = cUnderFunction::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionValue2Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionValue2Loaded, "pUnderFunctionValue2Loaded", underFunctionValue2, "underFunctionValue2" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionValue2Loaded );
			delete pUnderFunctionValue2Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorFunction and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cFunctionValue underFunctionSup( 325.142 );"<<endl;
		cFunctionValue underFunctionSup( 325.142 );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle3( &xmlDocFunctionValue2 ); "<<endl;
		TiXmlHandle xmlHandle3( &xmlDocFunctionValue2 );
		cout<<"cFunctionValue underFunctionValue2LoadedFull( xmlHandle3.FirstChildElement().Element(), "<<
			"outStatus, &underFunctionSup, &rootSimple ); "<<endl;
		cFunctionValue underFunctionValue2LoadedFull( xmlHandle3.FirstChildElement().Element(),
			outStatus, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionValue2LoadedFull,
			"underFunctionValue2LoadedFull", underFunctionValue2, "underFunctionValue2" );
		//check the getDefiningFibElement() methode from cFunctionValue
		if ( underFunctionValue2LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionValue2LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionValue2LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionValue
		if ( underFunctionValue2LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionValue2LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionValue2LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		
		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDocFunctionValue2 ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocFunctionValue2 );
		cout<<"cFunctionValue pUnderFunctionValue2LoadedFull = cUnderFunction::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionValue2LoadedFull = cUnderFunction::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionValue2LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionValue2LoadedFull, "pUnderFunctionValue2LoadedFull", underFunctionValue2, "underFunctionValue2" );
			//check the getDefiningFibElement() methode from cFunctionValue
			if ( pUnderFunctionValue2LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionValue2LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionValue2LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionValue
			if ( pUnderFunctionValue2LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionValue2LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionValue2LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctionValue2LoadedFull;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method store methods of the class.
 *
 * methods tested:
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 * 	- cFunctionValue( cReadBits & iBitStream, intFib & outStatus, const cDomainSingle * pInValueDomain, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cUnderFunction * restore( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInValueDomain, const cDomainSingle * pInDomainVariable, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStore( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method an an underfunction with value 1.0"<<endl;

	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	
	cDomainSingle * pValueDomain = new cDomainNaturalNumberBit( 16 );
	cDomainSingle * pVariableDomain = new cDomainNaturalNumberBit( 3 );

	cout<<"cFunctionValue underFunctionValue1( 1.0, NULL, &root );"<<endl;
	cFunctionValue underFunctionValue1( 1.0, NULL, &root );

	//test get compressed size
	unsigned int uiCompressedSize = 2 + 16;
	if ( (unsigned int)(underFunctionValue1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			underFunctionValue1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "underFunctionValue1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0x00;
	unsigned char cRestBitPosition = 0;
	cout<<"underFunctionValue1.store( *pFile, cRestBits, cRestBitPosition );"<<endl;
	bool bStoreSuccesfull = underFunctionValue1.store( *pFile, cRestBit, cRestBitPosition );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	unsigned char ucRestBit = cRestBit;
	unsigned char ucRestBitCorrect = 0x00;
	short sNumberOfRestBitCorrect = 2;
	if ( ( ucRestBit == ucRestBitCorrect ) && ( cRestBitPosition == sNumberOfRestBitCorrect ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cRestBitPosition <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cRestBitPosition <<
			", but the restbit should be "<< (unsigned short)ucRestBitCorrect <<
			" and number of restbit should be "<< sNumberOfRestBitCorrect <<" . "<<endl;
		iReturn++;
	}
	//test stored data
	const char cFunctionValue1[] = { 0x04, 0x00, 0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFunctionValue1, 3 );


	char cFunctionName = 0x00;
	ifstream * fileInXml = new ifstream( szFileNameBuffer );
	if ( (fileInXml != NULL) && ( fileInXml->good() ) ){
		
		cReadBits iBitStream( * fileInXml );
		iBitStream.readBits( &cFunctionName, 2 );
		intFib outStatus = 0;
		cout<<"cFunctionValue underFunctionValue1Loaded( iBitStream, outStatus, pValueDomain ); "<<endl;
		cFunctionValue underFunctionValue1Loaded( iBitStream, outStatus, pValueDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionValue1Loaded, "underFunctionValue1Loaded", underFunctionValue1, "underFunctionValue1" );
		iReturn += testNotConnectedUnderFunction( underFunctionValue1Loaded );

		delete fileInXml;
		ifstream * fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream2( * fileInXml );
		outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"cFunctionValue pUnderFunctionValue1Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctionValue1Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pValueDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionValue1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionValue1Loaded, "pUnderFunctionValue1Loaded", underFunctionValue1, "underFunctionValue1" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionValue1Loaded );
			delete pUnderFunctionValue1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorFunction and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cFunctionValue underFunctionSup( 325.142 );"<<endl;
		cFunctionValue underFunctionSup( 325.142 );
		
		delete fileInXml;
		fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream3( * fileInXml );
		iBitStream3.readBits( &cFunctionName, 2 );
		outStatus = 0;
		cout<<"cFunctionValue underFunctionValue1LoadedFull( iBitStream3, "<<
			"outStatus, pValueDomain, &underFunctionSup, &rootSimple ); "<<endl;
		cFunctionValue underFunctionValue1LoadedFull( iBitStream3,
			outStatus, pValueDomain, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionValue1LoadedFull,
			"underFunctionValue1LoadedFull", underFunctionValue1, "underFunctionValue1" );
		//check the getDefiningFibElement() methode from cFunctionValue
		if ( underFunctionValue1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionValue1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionValue1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionValue
		if ( underFunctionValue1LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionValue1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionValue1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		
		delete fileInXml;
		fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * fileInXml );
		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"cFunctionValue pUnderFunctionValue1LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionValue1LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionValue1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionValue1LoadedFull, "pUnderFunctionValue1LoadedFull", underFunctionValue1, "underFunctionValue1" );
			//check the getDefiningFibElement() methode from cFunctionValue
			if ( pUnderFunctionValue1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionValue1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionValue1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionValue
			if ( pUnderFunctionValue1LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionValue1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionValue1LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctionValue1LoadedFull;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		delete fileInXml;
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with given domains"<<endl;

	delete pValueDomain;
	delete pVariableDomain;
	pValueDomain = new cDomainNaturalNumberBit( 6 );
	pVariableDomain = new cDomainNaturalNumberBit( 4 );
	
	cout<<"cTypeUnderFunction testTypeFunctionValue;"<<endl;
	cTypeUnderFunction testTypeFunctionValue;
	
	//create vector domain with two elements
	cout<<"cDomainNaturalNumberBit domainsNatB6( 6 );"<<endl;
	cDomainNaturalNumberBit domainsNatB6( 6 );

	cout<<"root.getDomains()->addDomain( testTypeFunctionValue, &domainsNatB6 );"<<endl;
	root.getDomains()->addDomain( testTypeFunctionValue, &domainsNatB6 );
	
	cout<<"cTypeVariable testTypeVariable;"<<endl;
	cTypeVariable testTypeVariable;
	
	cout<<"cDomainNaturalNumberBit naturalNumberDomainB4( 4 );"<<endl;
	cDomainNaturalNumberBit naturalNumberDomainB4( 4 );
	
	cout<<"root.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB4 );"<<endl;
	root.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB4 );

	cout<<"cFunctionValue underFunctionValue2( 2.0, NULL, &root );"<<endl;
	cFunctionValue underFunctionValue2( 2.0, NULL, &root );
	
	//test get compressed size
	uiCompressedSize = 2 + 6;
	if ( (unsigned int)(underFunctionValue2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			underFunctionValue2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "underFunctionValue2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0x00;
	cRestBitPosition = 0;
	cout<<"underFunctionValue2.store( *pFile, cRestBit, cRestBitPosition ); "<<endl;
	bStoreSuccesfull = underFunctionValue2.store( *pFile, cRestBit, cRestBitPosition );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = 0x00;
	sNumberOfRestBitCorrect = 0;
	if ( ( ucRestBit == ucRestBitCorrect ) && ( cRestBitPosition == sNumberOfRestBitCorrect ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cRestBitPosition <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cRestBitPosition <<
			", but the restbit should be "<< (unsigned short)ucRestBitCorrect <<
			" and number of restbit should be "<< sNumberOfRestBitCorrect <<" . "<<endl;
		iReturn++;
	}
	//test stored data
	const char szUnderFunctionValue2[] = { 0x08, 0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, szUnderFunctionValue2, 2 );


	fileInXml = new ifstream( szFileNameBuffer );
	if ( (fileInXml != NULL) && ( fileInXml->good() ) ){
		
		cReadBits iBitStream( * fileInXml );
		iBitStream.readBits( &cFunctionName, 2 );
		intFib outStatus = 0;
		cout<<"cFunctionValue underFunctionValue2Loaded( iBitStream, outStatus, pValueDomain ); "<<endl;
		cFunctionValue underFunctionValue2Loaded( iBitStream, outStatus, pValueDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionValue2Loaded, "underFunctionValue2Loaded", underFunctionValue2, "underFunctionValue2" );
		iReturn += testNotConnectedUnderFunction( underFunctionValue2Loaded );

		delete fileInXml;
		ifstream * fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream2( * fileInXml );
		outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"cFunctionValue pUnderFunctionValue2Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctionValue2Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pValueDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionValue2Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionValue2Loaded, "pUnderFunctionValue2Loaded", underFunctionValue2, "underFunctionValue2" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionValue2Loaded );
			delete pUnderFunctionValue2Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorFunction and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cFunctionValue underFunctionSup( 325.142 );"<<endl;
		cFunctionValue underFunctionSup( 325.142 );
		
		delete fileInXml;
		fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream3( * fileInXml );
		iBitStream3.readBits( &cFunctionName, 2 );
		outStatus = 0;
		cout<<"cFunctionValue underFunctionValue2LoadedFull( iBitStream3, "<<
			"outStatus, pValueDomain, &underFunctionSup, &rootSimple ); "<<endl;
		cFunctionValue underFunctionValue2LoadedFull( iBitStream3,
			outStatus, pValueDomain, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionValue2LoadedFull,
			"underFunctionValue2LoadedFull", underFunctionValue2, "underFunctionValue2" );
		//check the getDefiningFibElement() methode from cFunctionValue
		if ( underFunctionValue2LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionValue2LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionValue2LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionValue
		if ( underFunctionValue2LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionValue2LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionValue2LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		
		delete fileInXml;
		fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * fileInXml );
		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"cFunctionValue pUnderFunctionValue2LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionValue2LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionValue2LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionValue2LoadedFull, "pUnderFunctionValue2LoadedFull", underFunctionValue2, "underFunctionValue2" );
			//check the getDefiningFibElement() methode from cFunctionValue
			if ( pUnderFunctionValue2LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionValue2LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionValue2LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionValue
			if ( pUnderFunctionValue2LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionValue2LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionValue2LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctionValue2LoadedFull;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		delete fileInXml;
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}



	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with given restbit"<<endl;

	cout<<"cFunctionValue underFunctionValue3( 33.0, NULL, &root );"<<endl;
	cFunctionValue underFunctionValue3( 33.0, NULL, &root );
	
	//test get compressed size
	uiCompressedSize = 2 + 6;
	if ( (unsigned int)(underFunctionValue3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			underFunctionValue3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "underFunctionValue3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0x01;
	cRestBitPosition = 2;
	cout<<"underFunctionValue3.store( *pFile, cRestBit, cRestBitPosition ); "<<endl;
	bStoreSuccesfull = underFunctionValue3.store( *pFile, cRestBit, cRestBitPosition );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = 0x02;
	sNumberOfRestBitCorrect = 2;
	if ( ( ucRestBit == ucRestBitCorrect ) && ( cRestBitPosition == sNumberOfRestBitCorrect ) ){
		cout<<"The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cRestBitPosition <<". "<<endl;
	}else{
		cerr<<"Error: The restbit is \""<< hex << (unsigned short)ucRestBit <<"\" the number of restbit is "<<
			dec << (unsigned short)cRestBitPosition <<
			", but the restbit should be "<< (unsigned short)ucRestBitCorrect <<
			" and number of restbit should be "<< sNumberOfRestBitCorrect <<" . "<<endl;
		iReturn++;
	}
	//test stored data
	const char szUnderFunctionValue3[] = { 0x11, 0x02 };
	iReturn += compareBytsWithFile( szFileNameBuffer, szUnderFunctionValue3, 2 );


	fileInXml = new ifstream( szFileNameBuffer );
	if ( (fileInXml != NULL) && ( fileInXml->good() ) ){
		
		cReadBits iBitStream( * fileInXml );
		char cBuffer;
		iBitStream.readBits( &cBuffer, 2 + 2 );
		intFib outStatus = 0;
		cout<<"cFunctionValue underFunctionValue3Loaded( iBitStream, outStatus, pValueDomain ); "<<endl;
		cFunctionValue underFunctionValue3Loaded( iBitStream, outStatus, pValueDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		int iErrorsEqual = testCompareTwoEqualObjects( underFunctionValue3Loaded, "underFunctionValue3Loaded", underFunctionValue3, "underFunctionValue3" );
		iReturn += testNotConnectedUnderFunction( underFunctionValue3Loaded );
		if ( iErrorsEqual != 0 ){
			cerr<<"Error: Loaded underfunction not equal (value="<<
				underFunctionValue3Loaded.getValue() <<")."<<endl;
		}
		iReturn += iErrorsEqual;

		delete fileInXml;
		ifstream * fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream2( * fileInXml );
		iBitStream2.readBits( &cBuffer, 2 );
		outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"cFunctionValue pUnderFunctionValue3Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctionValue3Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pValueDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionValue3Loaded ){
			iErrorsEqual = testCompareTwoEqualObjects( * pUnderFunctionValue3Loaded, "pUnderFunctionValue3Loaded", underFunctionValue3, "underFunctionValue3" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionValue3Loaded );
			if ( iErrorsEqual != 0 ){
				cerr<<"Error: Loaded underfunction not equal (value="<<
					underFunctionValue3Loaded.getValue() <<")."<<endl;
			}
			iReturn += iErrorsEqual;
			delete pUnderFunctionValue3Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorFunction and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cFunctionValue underFunctionSup( 325.142 );"<<endl;
		cFunctionValue underFunctionSup( 325.142 );
		
		delete fileInXml;
		fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream3( * fileInXml );
		iBitStream3.readBits( &cBuffer, 2 + 2 );
		outStatus = 0;
		cout<<"cFunctionValue underFunctionValue3LoadedFull( iBitStream3, "<<
			"outStatus, pValueDomain, &underFunctionSup, &rootSimple ); "<<endl;
		cFunctionValue underFunctionValue3LoadedFull( iBitStream3,
			outStatus, pValueDomain, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionValue3LoadedFull,
			"underFunctionValue3LoadedFull", underFunctionValue3, "underFunctionValue3" );
		//check the getDefiningFibElement() methode from cFunctionValue
		if ( underFunctionValue3LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionValue3LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionValue3LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionValue
		if ( underFunctionValue3LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionValue3LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionValue3LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		
		delete fileInXml;
		fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * fileInXml );
		iBitStream4.readBits( &cBuffer, 2 );
		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"cFunctionValue pUnderFunctionValue3LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionValue3LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionValue3LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionValue3LoadedFull, "pUnderFunctionValue3LoadedFull", underFunctionValue3, "underFunctionValue3" );
			//check the getDefiningFibElement() methode from cFunctionValue
			if ( pUnderFunctionValue3LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionValue3LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionValue3LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionValue
			if ( pUnderFunctionValue3LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionValue3LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionValue3LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctionValue3LoadedFull;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		delete fileInXml;
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}


	delete pValueDomain;
	delete pVariableDomain;

	return iReturn;
}



/**
 * This method tests the variable methods of the cFunctionValue class.
 *
 * methods tested:
 * 	- bool isUsedVariable( const cFibVariable * variable ) const;
 * 	- set<cFibVariable*> getUsedVariables();
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testVariable( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the variable methods"<<endl;

	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	cout<<"rootSimple1.setNumberOfInputVariables( 10 );"<<endl;
	rootSimple1.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 = rootSimple1.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootSimple1.getInputVariable( 1 );
	
	cout<<"cFunctionValue underFunctionValue1( 1 );"<<endl;
	cFunctionValue underFunctionValue1( 1 );
	
	cout<<"cFunctionValue underFunctionValue2( 2.2 );"<<endl;
	cFunctionValue underFunctionValue2( 2.2 );

	//check the isUsedVariable() methode from cFunctionValue
	cout<<"underFunctionValue1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! underFunctionValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionValue1.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = underFunctionValue1.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correctly no used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The ther are used variables given back. "<<endl;
		iReturn++;
	}
	cout<<"underFunctionValue1.replaceVariable( pVariable1, pVariable1 );"<<endl;
	bool bVariableReplaced = underFunctionValue1.replaceVariable( pVariable1, pVariable1 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	
	//check the isUsedVariable() methode from cFunctionValue
	cout<<"underFunctionValue2.isUsedVariable( pVariable1 )"<<endl;
	if ( ! underFunctionValue2.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionValue2.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionValue2.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correctly no used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The ther are used variables given back. "<<endl;
		iReturn++;
	}
	cout<<"underFunctionValue2.replaceVariable( pVariable1, pVariable1 );"<<endl;
	bVariableReplaced = underFunctionValue2.replaceVariable( pVariable1, pVariable1 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the variable methods of the cFunctionValue class.
 *
 * methods tested:
 * 	- void setDefiningFibElement( cFibElement *fibElement=NULL, bool bCheckDomains=true );
 * 	- cFibElement * getDefiningFibElement() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testDefiningFibElement( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the defining fib -element"<<endl;
	
	cout<<"cFunctionValue underFunctionValue1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue1( 1.0 );
	
	cFunctionValue ufValueCorrect1( 1.0 );
	
	cFibElement * pDefiningFibElement = NULL;
	//check the getDefiningFibElement() methode from cFunctionValue
	if ( underFunctionValue1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionValue1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionValue1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( underFunctionValue1, "underFunctionValue1", ufValueCorrect1, "correct underfunction" );
	
	cPoint point1;
	cout<<"underFunctionValue1.setDefiningFibElement( &point1 );"<<endl;
	underFunctionValue1.setDefiningFibElement( &point1 );
	pDefiningFibElement = &point1;
	//check the getDefiningFibElement() methode from cFunctionValue
	if ( underFunctionValue1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionValue1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionValue1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( underFunctionValue1, "underFunctionValue1", ufValueCorrect1, "correct underfunction" );
	
	cout<<"underFunctionValue1.setDefiningFibElement( &point1 );"<<endl;
	underFunctionValue1.setDefiningFibElement( &point1 );
	pDefiningFibElement = &point1;
	//check the getDefiningFibElement() methode from cFunctionValue
	if ( underFunctionValue1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionValue1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionValue1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( underFunctionValue1, "underFunctionValue1", ufValueCorrect1, "correct underfunction" );
	
	cout<<"cRoot root;"<<endl;
	cRoot root;
	
	cout<<"cTypeUnderFunction testTypeFunctionValue;"<<endl;
	cTypeUnderFunction testTypeFunctionValue;
	
	//create vector domain with two elements
	cout<<"cDomainNaturalNumberBit domainsNatB6( 6 );"<<endl;
	cDomainNaturalNumberBit domainsNatB6( 6 );

	cout<<"root.getDomains()->addDomain( testTypeFunctionValue, &domainsNatB6 );"<<endl;
	root.getDomains()->addDomain( testTypeFunctionValue, &domainsNatB6 );
	
	cout<<"cTypeVariable testTypeVariable;"<<endl;
	cTypeVariable testTypeVariable;
	
	cout<<"cDomainNaturalNumberBit naturalNumberDomainB4( 4 );"<<endl;
	cDomainNaturalNumberBit naturalNumberDomainB4( 4 );
	
	cout<<"root.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB4 );"<<endl;
	root.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB4 );

	cout<<"underFunctionValue1.setDefiningFibElement( &root );"<<endl;
	underFunctionValue1.setDefiningFibElement( &root );
	pDefiningFibElement = &root;
	//check the getDefiningFibElement() methode from cFunctionValue
	if ( underFunctionValue1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionValue1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionValue1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( underFunctionValue1, "underFunctionValue1", ufValueCorrect1, "correct underfunction" );


	cout<<"cFunctionValue underFunctionValue2( 65.0 );"<<endl;
	cFunctionValue underFunctionValue2( 65.0 );

	cFunctionValue ufValueCorrect65( 65.0 );
	cFunctionValue ufValueCorrect63( 63.0 );
	
	cout<<"underFunctionValue2.setDefiningFibElement( &point1 );"<<endl;
	underFunctionValue2.setDefiningFibElement( &point1 );
	pDefiningFibElement = &point1;
	//check the getDefiningFibElement() methode from cFunctionValue
	if ( underFunctionValue2.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionValue2.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionValue2.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( underFunctionValue2, "underFunctionValue2", ufValueCorrect65, "the correct underfunction" );

	cout<<"underFunctionValue2.setDefiningFibElement( &root, false );"<<endl;
	underFunctionValue2.setDefiningFibElement( &root, false );
	pDefiningFibElement = &root;
	//check the getDefiningFibElement() methode from cFunctionValue
	if ( underFunctionValue2.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionValue2.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionValue2.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( underFunctionValue2, "underFunctionValue2", ufValueCorrect65, "the correct underfunction" );

	cout<<"underFunctionValue2.setDefiningFibElement( &root );"<<endl;
	underFunctionValue2.setDefiningFibElement( &root );
	pDefiningFibElement = &root;
	//check the getDefiningFibElement() methode from cFunctionValue
	if ( underFunctionValue2.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionValue2.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionValue2.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( underFunctionValue2, "underFunctionValue2", ufValueCorrect63, "the correct underfunction" );

	
	return iReturn;
}










