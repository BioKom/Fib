/**
 * @file tFunctionVariable
 * file name: tFunctionVariable.cpp
 * @author Betti Oesterholz
 * @date 30.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the class cFunctionVariable.
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
 * This file contains the test for the class cFunctionVariable, which
 * represents a value Fib -underfunction.
 *
 *
 * What's tested of class cFunctionVariable:
 * 	- cFunctionVariable( cFibVariable * pInVariable, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cFunctionVariable( const cFunctionVariable & underfunction, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- cFunctionVariable( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cFunctionVariable( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInVariableDomain, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- ~cFunctionVariable();
 * 	- bool isValid() const;
 * 	- bool isUsedVariable( const cFibVariable * variable ) const;
 * 	- set<cFibVariable*> getUsedVariables();
 * 	- bool replaceVariable( cFibVariable *variableOld, cFibVariable *variableNew );
 * 	- cFibVariable * getVariable();
 * 	- bool setVariable( cFibVariable * pInVariable );
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
30.04.2010  Oesterholz  created
04.04.2011  Oesterholz  storing to binary stream
*/

#include "version.h"

#include "cFunctionVariable.h"
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
	
	cout<<endl<<"Running Test for cFunctionVariable methods"<<endl;
	cout<<      "=========================================="<<endl;

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
 * This method tests the constructor of the cFunctionVariable class.
 *
 * methods tested:
 * 	- cFunctionVariable( cFibVariable * pInVariable, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- ~cFunctionVariable();
 * 	- bool isValid() const;
 * 	- cFibVariable * getVariable();
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
	cout<<"pVariable2 =  rootEmpty.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 =  rootEmpty.getInputVariable( 2 );
	cout<<"pVariableX =  rootEmpty.getInputVariable( 10 );"<<endl;
	cFibVariable * pVariableX =  rootEmpty.getInputVariable( 10 );
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cFunctionVariable underfunction"<<endl;

	cout<<"cFunctionVariable underFunctionVariable1( pVariable1 );"<<endl;
	cFunctionVariable underFunctionVariable1( pVariable1 );
	cout<<"pVariable = pVariable1;"<<endl;
	cFibVariable * pVariable = pVariable1;
	cout<<"pVariable1->setValue( 1.0 );"<<endl;
	pVariable1->setValue( 1.0 );
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
	unsigned long ulCompressedSize = 2 + 8;
 
	//check the getValue() methode from cFunctionVariable
	if ( underFunctionVariable1.getValue() == dValue  ){
	
		cout<<"The underfunction value is correctly "<<
			underFunctionVariable1.getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			underFunctionVariable1.getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionVariable
	if ( underFunctionVariable1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionVariable1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionVariable1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionVariable
	if ( underFunctionVariable1.getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			underFunctionVariable1.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			underFunctionVariable1.getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionVariable
	if ( ! underFunctionVariable1.isValid() ){
	
		cout<<"The underfunction is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionVariable
	if ( underFunctionVariable1.getType() == cUnderFunction::FUNCTION_VARIABLE ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			underFunctionVariable1.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionVariable
	if ( underFunctionVariable1.getUnderFunctionName() == "variable" ){
	
		cout<<"The underfunction name is correctly "<<
			underFunctionVariable1.getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			underFunctionVariable1.getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionVariable
	if ( underFunctionVariable1.getNumberOfUnderFunctions() == 0 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			underFunctionVariable1.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			underFunctionVariable1.getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionVariable
	cTypeElement * pTypeOfUnderFunction = underFunctionVariable1.getElementType();
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
	//check the getDomain() methode from cFunctionVariable
	cDomain * pRetUnderFunctionDomain = underFunctionVariable1.getDomain();
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
	//check the getValueDomain() methode from cFunctionVariable
	cDomain * pRetValueDomain = underFunctionVariable1.getValueDomain();
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
	//check the getStandardDomain() methode from cFunctionVariable
	cDomain * pRetStandardDomain = underFunctionVariable1.getStandardDomain();
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
	//check the getVariableDomain() methode from cFunctionVariable
	cDomain * pRetVariableDomain = underFunctionVariable1.getVariableDomain();
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
	//check the getTimeNeed() methode from cFunctionVariable
	if ( underFunctionVariable1.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			underFunctionVariable1.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionVariable
	if ( underFunctionVariable1.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the function is "<<
			underFunctionVariable1.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the getVariable() methode from cFunctionVariable
	if ( underFunctionVariable1.getVariable() == pVariable ){
	
		cout<<"The variable pVariable is given back as the variable of the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable isn't given back as the variable of the underfunction. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	if ( underFunctionVariable1.isUsedVariable( pVariable ) ){
	
		cout<<"The variable pVariable is used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable isn't used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	if ( ! underFunctionVariable1.isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionVariable
	set<cFibVariable*> setUsedVariables = underFunctionVariable1.getUsedVariables();
	if ( ! setUsedVariables.empty() ){
	
		//check the isUsedVariable() methode from cFunctionVariable
		if ( setUsedVariables.find( pVariable ) != setUsedVariables.end() ){
		
			cout<<"The variable pVariable is used in the underfunction ( getUsedVariables() ). "<<endl;
		}else{
			cerr<<"Error: The variable pVariable isn't used in the underfunction ( getUsedVariables() ). "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: No used variables are given back from the underfunction. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an cFunctionVariable underfunction"<<endl;

	cout<<"cFunctionVariable underFunctionVariable2( pVariable2, &underFunctionVariable1, &rootEmpty  );"<<endl;
	cFunctionVariable underFunctionVariable2( pVariable2, &underFunctionVariable1, &rootEmpty );
	
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
	
	cout<<"pVariable = pVariable2;"<<endl;
	pVariable = pVariable2;
	dValue = -13.52;
	cout<<"pVariable2->setValue( "<<dValue<<" );"<<endl;
	pVariable2->setValue( dValue );
	pDefiningFibElement = &rootEmpty;
	pSuperiorUnderFunction = &underFunctionVariable1;
	
	pUnderFunctionDomain = &domainNaturalNumberBit5;
	pValueDomain = &domainNaturalNumberBit7;

	delete pVariableDomain;
	pVariableDomain = domainNaturalNumberBit3.clone();
	ulCompressedSize = 2 + 3;

	//check the getValue() methode from cFunctionVariable
	if ( underFunctionVariable2.getValue() == dValue  ){
	
		cout<<"The underfunction value is correctly "<<
			underFunctionVariable2.getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			underFunctionVariable2.getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionVariable
	if ( underFunctionVariable2.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionVariable2.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionVariable2.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionVariable
	if ( underFunctionVariable2.getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			underFunctionVariable2.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			underFunctionVariable2.getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionVariable
	if ( ! underFunctionVariable2.isValid() ){
	
		cout<<"The underfunction is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionVariable
	if ( underFunctionVariable2.getType() == cUnderFunction::FUNCTION_VARIABLE ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			underFunctionVariable2.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionVariable
	if ( underFunctionVariable2.getUnderFunctionName() == "variable" ){
	
		cout<<"The underfunction name is correctly "<<
			underFunctionVariable2.getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			underFunctionVariable2.getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionVariable
	if ( underFunctionVariable2.getNumberOfUnderFunctions() == 0 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			underFunctionVariable2.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			underFunctionVariable2.getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionVariable
	pTypeOfUnderFunction = underFunctionVariable2.getElementType();
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
	//check the getDomain() methode from cFunctionVariable
	pRetUnderFunctionDomain = underFunctionVariable2.getDomain();
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
	//check the getValueDomain() methode from cFunctionVariable
	pRetValueDomain = underFunctionVariable2.getValueDomain();
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
	//check the getStandardDomain() methode from cFunctionVariable
	pRetStandardDomain = underFunctionVariable2.getStandardDomain();
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
	//check the getVariableDomain() methode from cFunctionVariable
	pRetVariableDomain = underFunctionVariable2.getVariableDomain();
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
	//check the getTimeNeed() methode from cFunctionVariable
	if ( underFunctionVariable2.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			underFunctionVariable2.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionVariable
	if ( underFunctionVariable2.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the function is "<<
			underFunctionVariable2.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the getVariable() methode from cFunctionVariable
	if ( underFunctionVariable2.getVariable() == pVariable ){
	
		cout<<"The variable pVariable is given back as the variable of the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable isn't given back as the variable of the underfunction. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	if ( underFunctionVariable2.isUsedVariable( pVariable ) ){
	
		cout<<"The variable pVariable is used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable isn't used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	if ( ! underFunctionVariable2.isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionVariable
	setUsedVariables = underFunctionVariable2.getUsedVariables();
	if ( ! setUsedVariables.empty() ){
	
		//check the isUsedVariable() methode from cFunctionVariable
		if ( setUsedVariables.find( pVariable ) != setUsedVariables.end() ){
		
			cout<<"The variable pVariable is used in the underfunction ( getUsedVariables() ). "<<endl;
		}else{
			cerr<<"Error: The variable pVariable isn't used in the underfunction ( getUsedVariables() ). "<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: No used variables are given back from the underfunction. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an cFunctionVariable underfunction with given variablepointer NULL"<<endl;

	cout<<"cFunctionVariable underFunctionVariable3( NULL );"<<endl;
	cFunctionVariable underFunctionVariable3( NULL );
	
	cout<<"pVariable = NULL;"<<endl;
	pVariable = NULL;
	dValue = 0.0;
	pDefiningFibElement = &rootEmpty;
	pSuperiorUnderFunction = &underFunctionVariable1;
	
	pDefiningFibElement = NULL;
	pSuperiorUnderFunction = NULL;
	pUnderFunctionDomain = NULL;
	pValueDomain = NULL;
	delete pStandardDomain;
	pStandardDomain = typeUnderFunction.getStandardDomain();
	delete pVariableDomain;
	pVariableDomain = typeVariable.getStandardDomain();
	ulTimeNeed = 1;
	ulCompressedSize = 2 + 8;

	//check the getValue() methode from cFunctionVariable
	if ( underFunctionVariable3.getValue() == dValue  ){
	
		cout<<"The underfunction value is correctly "<<
			underFunctionVariable3.getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			underFunctionVariable3.getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionVariable
	if ( underFunctionVariable3.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionVariable3.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionVariable3.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionVariable
	if ( underFunctionVariable3.getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			underFunctionVariable3.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			underFunctionVariable3.getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionVariable
	if ( ! underFunctionVariable3.isValid() ){
	
		cout<<"The underfunction is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionVariable
	if ( underFunctionVariable3.getType() == cUnderFunction::FUNCTION_VARIABLE ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			underFunctionVariable3.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionVariable
	if ( underFunctionVariable3.getUnderFunctionName() == "variable" ){
	
		cout<<"The underfunction name is correctly "<<
			underFunctionVariable3.getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			underFunctionVariable3.getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionVariable
	if ( underFunctionVariable3.getNumberOfUnderFunctions() == 0 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			underFunctionVariable3.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			underFunctionVariable3.getNumberOfUnderFunctions() <<" , but should be 0 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionVariable
	pTypeOfUnderFunction = underFunctionVariable3.getElementType();
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
	//check the getDomain() methode from cFunctionVariable
	pRetUnderFunctionDomain = underFunctionVariable3.getDomain();
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
	//check the getValueDomain() methode from cFunctionVariable
	pRetValueDomain = underFunctionVariable3.getValueDomain();
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
	//check the getStandardDomain() methode from cFunctionVariable
	pRetStandardDomain = underFunctionVariable3.getStandardDomain();
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
	//check the getVariableDomain() methode from cFunctionVariable
	pRetVariableDomain = underFunctionVariable3.getVariableDomain();
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
	//check the getTimeNeed() methode from cFunctionVariable
	if ( underFunctionVariable3.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			underFunctionVariable3.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionVariable
	if ( underFunctionVariable3.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the function is "<<
			underFunctionVariable3.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the getVariable() methode from cFunctionVariable
	if ( underFunctionVariable3.getVariable() == pVariable ){
	
		cout<<"The variable pVariable is given back as the variable of the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable isn't given back as the variable of the underfunction. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	if ( ! underFunctionVariable3.isUsedVariable( pVariable ) ){
	
		cout<<"The variable pVariable isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	if ( ! underFunctionVariable3.isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionVariable
	setUsedVariables = underFunctionVariable3.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"Ther are correctly no used variables given back from the underfunction. "<<endl;

	}else{
		cerr<<"Error: Ther are used variables given back from the underfunction. "<<endl;
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
 * This method tests equal method of the cFunctionVariable class.
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
	
	cout<<"cRoot rootEmpty;"<<endl;
	cRoot rootEmpty;
	cout<<"rootEmpty.setNumberOfInputVariables( 10 );"<<endl;
	rootEmpty.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 =  rootEmpty.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 =  rootEmpty.getInputVariable( 1 );
	cout<<"pVariable2 =  rootEmpty.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 =  rootEmpty.getInputVariable( 2 );
	cout<<"pVariable3 =  rootEmpty.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 =  rootEmpty.getInputVariable( 3 );

	//function with a empty functionvector
	cout<<"cFunctionVariable underFunctionVariable1( pVariable1 );"<<endl;
	cFunctionVariable underFunctionVariable1( pVariable1 );

	cout<<"cFunctionVariable underFunctionVariable2( pVariable1 );"<<endl;
	cFunctionVariable underFunctionVariable2( pVariable1 );


	//function with one changed underfunction
	cout<<"cFunctionVariable underFunctionVariable3( pVariable2 );"<<endl;
	cFunctionVariable underFunctionVariable3( pVariable2 );

	cout<<"cFunctionVariable underFunctionVariableV3( pVariable3 );"<<endl;
	cFunctionVariable underFunctionVariableV3( pVariable3 );

	//function with defining fib -element
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	cout<<"cFunctionVariable functionDefFE( pVariable1, NULL, &rootSimple1 );"<<endl;
	cFunctionVariable functionDefFE( pVariable1, NULL, &rootSimple1 );

	//function with superior underfunction
	cout<<"cFunctionValue underFunctionSup( 3.33 );"<<endl;
	cFunctionValue underFunctionSup( 3.333 );
	cout<<"cFunctionVariable functionSup( pVariable1, & underFunctionSup );"<<endl;
	cFunctionVariable functionSup( pVariable1, & underFunctionSup );

	//underfunction with domains set
	cout<<"root1 rootSimple1;"<<endl;
	cRoot root1;
	
	cout<<"cTypeUnderFunction testTypeUnderFunction;"<<endl;
	cTypeUnderFunction testTypeUnderFunction;
	cout<<"cDomainNaturalNumberBit domainNat8( 8 );"<<endl;
	cDomainNaturalNumberBit domainNat8( 8 );

	cout<<"root1.getDomains()->addDomain( testTypeUnderFunction, &domainNat8 );"<<endl;
	root1.getDomains()->addDomain( testTypeUnderFunction, &domainNat8 );

	cout<<"cFunctionVariable functionDom( pVariable1, NULL, &root1 );"<<endl;
	cFunctionVariable functionDom( pVariable1, NULL, &root1 );

	//function with defining fib -element and superior underfunction
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cFunctionVariable underFunctionSup2( pVariable2 );"<<endl;
	cFunctionVariable underFunctionSup2( pVariable2 );
	cout<<"cFunctionVariable functionDefFeUf( pVariable1, & underFunctionSup2, &rootSimple2 );"<<endl;
	cFunctionVariable functionDefFeUf( pVariable1, & underFunctionSup2, &rootSimple2 );



	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with underFunctionVariable1
	cUnderFunction * actualObject = &underFunctionVariable1;
	string szActualObjectName = "underFunctionVariable1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionVariable1, "underFunctionVariable1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionVariable2, "underFunctionVariable2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariable3, "underFunctionVariable3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariableV3, "underFunctionVariableV3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with underFunctionVariable2
	actualObject = &underFunctionVariable2;
	szActualObjectName = "underFunctionVariable2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionVariable1, "underFunctionVariable1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionVariable2, "underFunctionVariable2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariable3, "underFunctionVariable3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariableV3, "underFunctionVariableV3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with underFunctionVariable3
	actualObject = &underFunctionVariable3;
	szActualObjectName = "underFunctionVariable3";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariable1, "underFunctionVariable1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariable2, "underFunctionVariable2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionVariable3, "underFunctionVariable3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariableV3, "underFunctionVariableV3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with underFunctionVariableV3
	actualObject = &underFunctionVariableV3;
	szActualObjectName = "underFunctionVariableV3";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariable1, "underFunctionVariable1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariable2, "underFunctionVariable2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariable3, "underFunctionVariable3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionVariableV3, "underFunctionVariableV3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with functionDefFE
	actualObject = &functionDefFE;
	szActualObjectName = "functionDefFE";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionVariable1, "underFunctionVariable1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionVariable2, "underFunctionVariable2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariable3, "underFunctionVariable3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariableV3, "underFunctionVariableV3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with functionSup
	actualObject = &functionSup;
	szActualObjectName = "functionSup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionVariable1, "underFunctionVariable1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionVariable2, "underFunctionVariable2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariable3, "underFunctionVariable3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariableV3, "underFunctionVariableV3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with functionDom
	actualObject = &functionDom;
	szActualObjectName = "functionDom";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionVariable1, "underFunctionVariable1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionVariable2, "underFunctionVariable2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariable3, "underFunctionVariable3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariableV3, "underFunctionVariableV3" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeUf, "functionDefFeUf" );

	//compare with functionDefFeUf
	actualObject = &functionDefFeUf;
	szActualObjectName = "functionDefFeUf";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionVariable1, "underFunctionVariable1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, underFunctionVariable2, "underFunctionVariable2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariable3, "underFunctionVariable3" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, underFunctionVariableV3, "underFunctionVariableV3" );
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
 * This method tests the copy methods and copyconstructor of the cFunctionVariable class.
 *
 * methods tested:
 * 	- cFunctionVariable( const cFunctionVariable & underfunction, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- cUnderFunction * clone( cUnderFunction * pInSuperiorUnderFunction = NULL, cFibElement *pInDefiningFibElement = NULL) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a simple cFunctionVariable"<<endl;
	
	cout<<"cRoot rootEmpty;"<<endl;
	cRoot rootEmpty;
	cout<<"rootEmpty.setNumberOfInputVariables( 10 );"<<endl;
	rootEmpty.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 =  rootEmpty.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 =  rootEmpty.getInputVariable( 1 );

	cout<<"cFunctionVariable underFunctionVariable1( pVariable1 );"<<endl;
	cFunctionVariable underFunctionVariable1( pVariable1 );

	cout<<"cFunctionVariable underFunctionVariable1CopyConstruct( underFunctionVariable1 );"<<endl;
	cFunctionVariable underFunctionVariable1CopyConstruct( underFunctionVariable1 );

	iReturn += testCompareTwoEqualObjects( underFunctionVariable1CopyConstruct, "underFunctionVariable1CopyConstruct", underFunctionVariable1, "underFunctionVariable1" );
	iReturn += testNotConnectedUnderFunction( underFunctionVariable1CopyConstruct );

	cout<<"cUnderFunction * pUnderFunctionVariable1Clone = underFunctionVariable1CopyConstruct.clone();"<<endl;
	cUnderFunction * pUnderFunctionVariable1Clone = underFunctionVariable1CopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pUnderFunctionVariable1Clone, "pUnderFunctionVariable1Clone", underFunctionVariable1, "underFunctionVariable1" );
	iReturn += testNotConnectedUnderFunction( *pUnderFunctionVariable1Clone );
	delete pUnderFunctionVariable1Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionVariable with variable pVariable2"<<endl;

	cout<<"pVariable2 =  rootEmpty.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 =  rootEmpty.getInputVariable( 2 );
	
	cout<<"cFunctionVariable underFunctionVariableV2( pVariable2 );"<<endl;
	cFunctionVariable underFunctionVariableV2( pVariable2 );

	cout<<"cFunctionVariable underFunctionVariableV2CopyConstruct( underFunctionVariableV2 );"<<endl;
	cFunctionVariable underFunctionVariableV2CopyConstruct( underFunctionVariableV2 );

	iReturn += testCompareTwoEqualObjects( underFunctionVariableV2CopyConstruct, "underFunctionVariableV2CopyConstruct", underFunctionVariableV2, "underFunctionVariableV2" );
	iReturn += testNotConnectedUnderFunction( underFunctionVariableV2CopyConstruct );

	cout<<"cUnderFunction * pUnderFunctionVariableV2Clone = underFunctionVariableV2CopyConstruct.clone();"<<endl;
	cUnderFunction * pUnderFunctionVariableV2Clone = underFunctionVariableV2CopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pUnderFunctionVariableV2Clone, "pUnderFunctionVariableV2Clone", underFunctionVariableV2, "underFunctionVariableV2" );
	iReturn += testNotConnectedUnderFunction( *pUnderFunctionVariableV2Clone );
	delete pUnderFunctionVariableV2Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionVariable with a superior underfunction and defining fib -element"<<endl;

	//function with defining fib -element and superior underfunction
	cout<<"cRoot rootSimple;"<<endl;
	cRoot rootSimple;
	cout<<"cFunctionValue underFunctionSup( 325.142 );"<<endl;
	cFunctionValue underFunctionSup( 325.142 );
	cout<<"cFunctionVariable functionDefFeUf( pVariable1, & underFunctionSup, &rootSimple );"<<endl;
	cFunctionVariable functionDefFeUf( pVariable1, & underFunctionSup, &rootSimple );

	cout<<"cFunctionVariable functionDefFeUfCopyConstruct( functionDefFeUf );"<<endl;
	cFunctionVariable functionDefFeUfCopyConstruct( functionDefFeUf );

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

	cout<<"cFunctionVariable functionDefFeUfCopy2Construct( functionDefFeUf, &underFunctionSup2, &rootSimple2 );"<<endl;
	cFunctionVariable functionDefFeUfCopy2Construct( functionDefFeUf, &underFunctionSup2, &rootSimple2 );

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
 * This method tests a in the xml -format stored cFunctionVariable.
 * The underfunction of the cFunctionVariable should be a value underfunction
 * ( cFunctionVariable ).
 *
 * @param szFilename the name of the file wher the cFunctionVariable is stored
 * @param dValue the value of the underfunction
 * @return the number of errors occured in the test
 */
int testXmlFunctionVariable( const string szFilename, double dValue ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cFunctionVariable:"<<endl;
	
	TiXmlDocument xmlDocFunctionVariable( szFilename );
	bool loadOkay = xmlDocFunctionVariable.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocFunctionVariable );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();
		
		const string szFunctionVariableElementName = "variable";
		if ( szElementName == szFunctionVariableElementName ){
			cout<<"The root element is correctly named \""<< szFunctionVariableElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szFunctionVariableElementName <<"\"."<<endl;
			iReturn++;
		}
		
		const char * pcValue = pXmlElement->GetText();
		cout<<"The value of the underfunction is: "<< pcValue <<endl;
		//converting value to double
		double dXmlValue;
		int iReadValues = sscanf ( pcValue, "%lf", & dXmlValue );
		if ( iReadValues != 0){
			if ( dXmlValue == dValue ){
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
 * This method tests the storeXml() method of the cFunctionVariable class.
 * Just storing properties with no underobjects is tested.
 *
 * methods tested:
 * 	- bool storeXml( ostream &stream ) const;
 * 	- cFunctionVariable( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cUnderFunction * restoreXml( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStoreXml( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an underfunction with value 1.0"<<endl;

	cout<<"cRoot rootEmpty;"<<endl;
	cRoot rootEmpty;
	cout<<"rootEmpty.setNumberOfInputVariables( 10 );"<<endl;
	rootEmpty.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 = rootEmpty.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootEmpty.getInputVariable( 1 );
	cout<<"pVariable2 = rootEmpty.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = rootEmpty.getInputVariable( 2 );
	cout<<"pVariable3 = rootEmpty.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = rootEmpty.getInputVariable( 3 );
	cout<<"pVariable4 = rootEmpty.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable4 = rootEmpty.getInputVariable( 4 );
	cout<<"pVariable1->setValue( 1.0 );"<<endl;
	pVariable1->setValue( 1.0 );
	cout<<"pVariable2->setValue( 2.0 );"<<endl;
	pVariable2->setValue( 2.0 );
	cout<<"pVariable3->setValue( 3.0 );"<<endl;
	pVariable3->setValue( 3.0 );
	cout<<"pVariable4->setValue( 4.0 );"<<endl;
	pVariable4->setValue( 4.0 );
	
	cout<<"list<cFibVariable*> liDefinedVariables;"<<endl;
	list<cFibVariable*> liDefinedVariables;
	cout<<"liDefinedVariables.push_back( pVariable3 );"<<endl;
	liDefinedVariables.push_back( pVariable3 );
	cout<<"liDefinedVariables.push_back( pVariable1 );"<<endl;
	liDefinedVariables.push_back( pVariable1 );
	cout<<"liDefinedVariables.push_back( pVariable4 );"<<endl;
	liDefinedVariables.push_back( pVariable4 );
	cout<<"liDefinedVariables.push_back( pVariable2 );"<<endl;
	liDefinedVariables.push_back( pVariable2 );
	
	list<cFibVariable*> liDefinedVariablesOrg = liDefinedVariables;
	
	cout<<"cFunctionVariable underFunctionVariable1( pVariable1 );"<<endl;
	cFunctionVariable underFunctionVariable1( pVariable1 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlFunctionVariableFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "underFunctionVariable1.xml" );
	ofstream * pFileUnderFunction = new ofstream( szXmlFunctionVariableFileName );
	
	bool bStoreSuccesfull = underFunctionVariable1.storeXml( *pFileUnderFunction );
	delete pFileUnderFunction;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFunctionVariable was stored successfull to the file \""<< szXmlFunctionVariableFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFunctionVariable to the file \""<< szXmlFunctionVariableFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlFunctionVariable( szXmlFunctionVariableFileName, underFunctionVariable1.getValue() );
	
	TiXmlDocument xmlDocFunctionVariable( szFileNameBuffer );
	bool loadOkay = xmlDocFunctionVariable.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		cout<<"TiXmlHandle xmlHandle( &xmlDocFunctionVariable ); "<<endl;
		TiXmlHandle xmlHandle( &xmlDocFunctionVariable );
		cout<<"cFunctionVariable underFunctionVariable1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cFunctionVariable underFunctionVariable1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionVariable1Loaded, "underFunctionVariable1Loaded", underFunctionVariable1, "underFunctionVariable1" );
		iReturn += testNotConnectedUnderFunction( underFunctionVariable1Loaded );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocFunctionVariable ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocFunctionVariable );
		cout<<"cFunctionVariable underFunctionVariable1Loaded( xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cUnderFunction * pUnderFunctionVariable1Loaded = cUnderFunction::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionVariable1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionVariable1Loaded, "pUnderFunctionVariable1Loaded", underFunctionVariable1, "underFunctionVariable1" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionVariable1Loaded );
			delete pUnderFunctionVariable1Loaded;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorFunction and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cFunctionValue underFunctionSup( 325.142 );"<<endl;
		cFunctionValue underFunctionSup( 325.142 );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle3( &xmlDocFunctionVariable ); "<<endl;
		TiXmlHandle xmlHandle3( &xmlDocFunctionVariable );
		cout<<"cFunctionVariable underFunctionVariable1LoadedFull( xmlHandle3.FirstChildElement().Element(), "<<
			"outStatus, liDefinedVariables, &underFunctionSup, &rootSimple ); "<<endl;
		cFunctionVariable underFunctionVariable1LoadedFull( xmlHandle3.FirstChildElement().Element(),
			outStatus, liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionVariable1LoadedFull,
			"underFunctionVariable1LoadedFull", underFunctionVariable1, "underFunctionVariable1" );
		//check the getDefiningFibElement() methode from cFunctionVariable
		if ( underFunctionVariable1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionVariable1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionVariable1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionVariable
		if ( underFunctionVariable1LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionVariable1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionVariable1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		
		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle4( &xmlDocFunctionVariable ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocFunctionVariable );
		cout<<"cFunctionVariable pUnderFunctionVariable1LoadedFull = cUnderFunction::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionVariable1LoadedFull = cUnderFunction::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionVariable1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionVariable1LoadedFull, "pUnderFunctionVariable1LoadedFull", underFunctionVariable1, "underFunctionVariable1" );
			//check the getDefiningFibElement() methode from cFunctionVariable
			if ( pUnderFunctionVariable1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionVariable1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionVariable1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionVariable
			if ( pUnderFunctionVariable1LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionVariable1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionVariable1LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctionVariable1LoadedFull;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
			iReturn++;
		}
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an underfunction with the variable pVariable2"<<endl;

	cout<<"cFunctionVariable underFunctionVariable2( pVariable2 );"<<endl;
	cFunctionVariable underFunctionVariable2( pVariable2 );
	
	szFileNameBuffer[0] = 0;
	szXmlFunctionVariableFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "underFunctionVariable2.xml" );
	pFileUnderFunction = new ofstream( szXmlFunctionVariableFileName );
	
	bStoreSuccesfull = underFunctionVariable2.storeXml( *pFileUnderFunction );
	delete pFileUnderFunction;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFunctionVariable was stored successfull to the file \""<< szXmlFunctionVariableFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFunctionVariable to the file \""<< szXmlFunctionVariableFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlFunctionVariable( szXmlFunctionVariableFileName, underFunctionVariable2.getValue() );
	
	TiXmlDocument xmlDocFunctionVariable2( szFileNameBuffer );
	loadOkay = xmlDocFunctionVariable2.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		cout<<"TiXmlHandle xmlHandle( &xmlDocFunctionVariable2 ); "<<endl;
		TiXmlHandle xmlHandle( &xmlDocFunctionVariable2 );
		cout<<"cFunctionVariable underFunctionVariable2Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cFunctionVariable underFunctionVariable2Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionVariable2Loaded, "underFunctionVariable2Loaded", underFunctionVariable2, "underFunctionVariable2" );
		iReturn += testNotConnectedUnderFunction( underFunctionVariable2Loaded );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocFunctionVariable2 ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocFunctionVariable2 );
		cout<<"pUnderFunctionVariable2Loaded = cUnderFunction::restoreXml( "<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cUnderFunction * pUnderFunctionVariable2Loaded = cUnderFunction::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionVariable2Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionVariable2Loaded, "pUnderFunctionVariable2Loaded", underFunctionVariable2, "underFunctionVariable2" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionVariable2Loaded );
			delete pUnderFunctionVariable2Loaded;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorFunction and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cFunctionValue underFunctionSup( 325.142 );"<<endl;
		cFunctionValue underFunctionSup( 325.142 );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle3( &xmlDocFunctionVariable2 ); "<<endl;
		TiXmlHandle xmlHandle3( &xmlDocFunctionVariable2 );
		cout<<"cFunctionVariable underFunctionVariable2LoadedFull( xmlHandle3.FirstChildElement().Element(), "<<
			"outStatus, liDefinedVariables, &underFunctionSup, &rootSimple ); "<<endl;
		cFunctionVariable underFunctionVariable2LoadedFull( xmlHandle3.FirstChildElement().Element(),
			outStatus, liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionVariable2LoadedFull,
			"underFunctionVariable2LoadedFull", underFunctionVariable2, "underFunctionVariable2" );
		//check the getDefiningFibElement() methode from cFunctionVariable
		if ( underFunctionVariable2LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionVariable2LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionVariable2LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionVariable
		if ( underFunctionVariable2LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionVariable2LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionVariable2LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		
		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle4( &xmlDocFunctionVariable2 ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocFunctionVariable2 );
		cout<<"cFunctionVariable pUnderFunctionVariable2LoadedFull = cUnderFunction::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionVariable2LoadedFull = cUnderFunction::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionVariable2LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionVariable2LoadedFull, "pUnderFunctionVariable2LoadedFull", underFunctionVariable2, "underFunctionVariable2" );
			//check the getDefiningFibElement() methode from cFunctionVariable
			if ( pUnderFunctionVariable2LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionVariable2LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionVariable2LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionVariable
			if ( pUnderFunctionVariable2LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionVariable2LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionVariable2LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctionVariable2LoadedFull;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
			iReturn++;
		}
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an underfunction with the variable pVariable3"<<endl;

	cout<<"cFunctionVariable underFunctionVariable3( pVariable3 );"<<endl;
	cFunctionVariable underFunctionVariable3( pVariable3 );
	
	szFileNameBuffer[0] = 0;
	szXmlFunctionVariableFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "underFunctionVariable3.xml" );
	pFileUnderFunction = new ofstream( szXmlFunctionVariableFileName );
	
	bStoreSuccesfull = underFunctionVariable3.storeXml( *pFileUnderFunction );
	delete pFileUnderFunction;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFunctionVariable was stored successfull to the file \""<< szXmlFunctionVariableFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFunctionVariable to the file \""<< szXmlFunctionVariableFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlFunctionVariable( szXmlFunctionVariableFileName, underFunctionVariable3.getValue() );
	
	TiXmlDocument xmlDocFunctionVariable3( szFileNameBuffer );
	loadOkay = xmlDocFunctionVariable3.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		cout<<"TiXmlHandle xmlHandle( &xmlDocFunctionVariable3 ); "<<endl;
		TiXmlHandle xmlHandle( &xmlDocFunctionVariable3 );
		cout<<"cFunctionVariable underFunctionVariable3Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cFunctionVariable underFunctionVariable3Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionVariable3Loaded, "underFunctionVariable3Loaded", underFunctionVariable3, "underFunctionVariable3" );
		iReturn += testNotConnectedUnderFunction( underFunctionVariable3Loaded );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocFunctionVariable3 ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocFunctionVariable3 );
		cout<<"pUnderFunctionVariable3Loaded = cUnderFunction::restoreXml( "<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cUnderFunction * pUnderFunctionVariable3Loaded = cUnderFunction::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionVariable3Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionVariable3Loaded, "pUnderFunctionVariable3Loaded", underFunctionVariable3, "underFunctionVariable3" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionVariable3Loaded );
			delete pUnderFunctionVariable3Loaded;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorFunction and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cFunctionValue underFunctionSup( 325.142 );"<<endl;
		cFunctionValue underFunctionSup( 325.142 );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle3( &xmlDocFunctionVariable3 ); "<<endl;
		TiXmlHandle xmlHandle3( &xmlDocFunctionVariable3 );
		cout<<"cFunctionVariable underFunctionVariable3LoadedFull( xmlHandle3.FirstChildElement().Element(), "<<
			"outStatus, liDefinedVariables, &underFunctionSup, &rootSimple ); "<<endl;
		cFunctionVariable underFunctionVariable3LoadedFull( xmlHandle3.FirstChildElement().Element(),
			outStatus, liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionVariable3LoadedFull,
			"underFunctionVariable3LoadedFull", underFunctionVariable3, "underFunctionVariable3" );
		//check the getDefiningFibElement() methode from cFunctionVariable
		if ( underFunctionVariable3LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionVariable3LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionVariable3LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionVariable
		if ( underFunctionVariable3LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionVariable3LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionVariable3LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		
		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle4( &xmlDocFunctionVariable3 ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocFunctionVariable3 );
		cout<<"cFunctionVariable pUnderFunctionVariable3LoadedFull = cUnderFunction::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionVariable3LoadedFull = cUnderFunction::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionVariable3LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionVariable3LoadedFull, "pUnderFunctionVariable3LoadedFull", underFunctionVariable3, "underFunctionVariable3" );
			//check the getDefiningFibElement() methode from cFunctionVariable
			if ( pUnderFunctionVariable3LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionVariable3LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionVariable3LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionVariable
			if ( pUnderFunctionVariable3LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionVariable3LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionVariable3LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctionVariable3LoadedFull;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
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
 * 	- cFunctionVariable( cReadBits & iBitStream, intFib & outStatus, const cDomainSingle * pInValueDomain, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cUnderFunction * restore( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInValueDomain, const cDomainSingle * pInDomainVariable, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStore( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method an an underfunction with value 1.0"<<endl;

	cout<<"cRoot root;"<<endl;
	cRoot root;
	cout<<"root.setNumberOfInputVariables( 10 );"<<endl;
	root.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 = root.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = root.getInputVariable( 1 );
	cout<<"pVariable2 = root.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = root.getInputVariable( 2 );
	cout<<"pVariable3 = root.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = root.getInputVariable( 3 );
	cout<<"pVariable4 = root.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable4 = root.getInputVariable( 4 );
	cout<<"pVariable1->setValue( 1.0 );"<<endl;
	pVariable1->setValue( 1.0 );
	cout<<"pVariable2->setValue( 2.0 );"<<endl;
	pVariable2->setValue( 2.0 );
	cout<<"pVariable3->setValue( 3.0 );"<<endl;
	pVariable3->setValue( 3.0 );
	cout<<"pVariable4->setValue( 4.0 );"<<endl;
	pVariable4->setValue( 4.0 );
	
	cout<<"list<cFibVariable*> liDefinedVariables;"<<endl;
	list<cFibVariable*> liDefinedVariables;
	cout<<"liDefinedVariables.push_back( pVariable3 );"<<endl;
	liDefinedVariables.push_back( pVariable3 );
	cout<<"liDefinedVariables.push_back( pVariable1 );"<<endl;
	liDefinedVariables.push_back( pVariable1 );
	cout<<"liDefinedVariables.push_back( pVariable4 );"<<endl;
	liDefinedVariables.push_back( pVariable4 );
	cout<<"liDefinedVariables.push_back( pVariable2 );"<<endl;
	liDefinedVariables.push_back( pVariable2 );
	
	list<cFibVariable*> liDefinedVariablesOrg = liDefinedVariables;
	
	cDomainSingle * pValueDomain = new cDomainNaturalNumberBit( 16 );
	cDomainSingle * pVariableDomain = new cDomainNaturalNumberBit( 8 );

	cout<<"cFunctionVariable underFunctionVariable1( pVariable1, NULL, &root );"<<endl;
	cFunctionVariable underFunctionVariable1( pVariable1, NULL, &root );

	//test get compressed size
	unsigned int uiCompressedSize = 2 + 8;
	if ( (unsigned int)(underFunctionVariable1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			underFunctionVariable1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "underFunctionVariable1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0x00;
	unsigned char cRestBitPosition = 0;
	cout<<"underFunctionVariable1.store( *pFile, cRestBits, cRestBitPosition );"<<endl;
	bool bStoreSuccesfull = underFunctionVariable1.store( *pFile, cRestBit, cRestBitPosition );
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
	const char cFunctionVariable1[] = { 0x05, 0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFunctionVariable1, 2 );

	char cFunctionName = 0x00;
	ifstream * fileInXml = new ifstream( szFileNameBuffer );
	if ( (fileInXml != NULL) && ( fileInXml->good() ) ){
		
		cReadBits iBitStream( * fileInXml );
		iBitStream.readBits( &cFunctionName, 2 );
		intFib outStatus = 0;
		cout<<"cFunctionVariable underFunctionVariable1Loaded( iBitStream, outStatus, liDefinedVariables, pVariableDomain ); "<<endl;
		cFunctionVariable underFunctionVariable1Loaded( iBitStream, outStatus, liDefinedVariables, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionVariable1Loaded, "underFunctionVariable1Loaded", underFunctionVariable1, "underFunctionVariable1" );
		iReturn += testNotConnectedUnderFunction( underFunctionVariable1Loaded );

		delete fileInXml;
		ifstream * fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream2( * fileInXml );
		outStatus = 0;
		cout<<"cFunctionVariable pUnderFunctionVariable1Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctionVariable1Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionVariable1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionVariable1Loaded, "pUnderFunctionVariable1Loaded", underFunctionVariable1, "underFunctionVariable1" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionVariable1Loaded );
			delete pUnderFunctionVariable1Loaded;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
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
		cout<<"cFunctionVariable underFunctionVariable1LoadedFull( iBitStream3, "<<
			"outStatus, liDefinedVariables, pVariableDomain, &underFunctionSup, &rootSimple ); "<<endl;
		cFunctionVariable underFunctionVariable1LoadedFull( iBitStream3,
			outStatus, liDefinedVariables, pVariableDomain, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionVariable1LoadedFull,
			"underFunctionVariable1LoadedFull", underFunctionVariable1, "underFunctionVariable1" );
		//check the getDefiningFibElement() methode from cFunctionVariable
		if ( underFunctionVariable1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionVariable1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionVariable1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionVariable
		if ( underFunctionVariable1LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionVariable1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionVariable1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		
		delete fileInXml;
		fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * fileInXml );
		outStatus = 0;
		cout<<"cFunctionVariable pUnderFunctionVariable1LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionVariable1LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionVariable1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionVariable1LoadedFull, "pUnderFunctionVariable1LoadedFull", underFunctionVariable1, "underFunctionVariable1" );
			//check the getDefiningFibElement() methode from cFunctionVariable
			if ( pUnderFunctionVariable1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionVariable1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionVariable1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionVariable
			if ( pUnderFunctionVariable1LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionVariable1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionVariable1LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctionVariable1LoadedFull;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
			iReturn++;
		}
		delete fileInXml;
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with given domains"<<endl;

	delete pVariableDomain;
	delete pValueDomain;
	pVariableDomain = new cDomainNaturalNumberBit( 6 );
	pValueDomain = new cDomainNaturalNumberBit( 4 );
	
	cout<<"cTypeUnderFunction testTypeUnderFunction;"<<endl;
	cTypeUnderFunction testTypeUnderFunction;
	
	cout<<"cDomainNaturalNumberBit naturalNumberDomainB4( 4 );"<<endl;
	cDomainNaturalNumberBit naturalNumberDomainB4( 4 );

	cout<<"root.getDomains()->addDomain( testTypeUnderFunction, &naturalNumberDomainB4 );"<<endl;
	root.getDomains()->addDomain( testTypeUnderFunction, &naturalNumberDomainB4 );
	
	cout<<"cTypeVariable testTypeVariable;"<<endl;
	cTypeVariable testTypeVariable;
	
	cout<<"cDomainNaturalNumberBit domainsNatB6( 6 );"<<endl;
	cDomainNaturalNumberBit domainsNatB6( 6 );
	
	cout<<"root.getDomains()->addDomain( testTypeVariable, &domainsNatB6 );"<<endl;
	root.getDomains()->addDomain( testTypeVariable, &domainsNatB6 );

	cout<<"cFunctionVariable underFunctionVariable2( pVariable2, NULL, &root );"<<endl;
	cFunctionVariable underFunctionVariable2( pVariable2, NULL, &root );
	
	//test get compressed size
	uiCompressedSize = 2 + 6;
	if ( (unsigned int)(underFunctionVariable2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			underFunctionVariable2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "underFunctionVariable2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0x00;
	cRestBitPosition = 0;
	cout<<"underFunctionVariable2.store( *pFile, cRestBit, cRestBitPosition ); "<<endl;
	bStoreSuccesfull = underFunctionVariable2.store( *pFile, cRestBit, cRestBitPosition );
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
	const char szUnderFunctionVariable2[] = { 0x09, 0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, szUnderFunctionVariable2, 2 );


	fileInXml = new ifstream( szFileNameBuffer );
	if ( (fileInXml != NULL) && ( fileInXml->good() ) ){
		
		cReadBits iBitStream( * fileInXml );
		iBitStream.readBits( &cFunctionName, 2 );
		intFib outStatus = 0;
		cout<<"cFunctionVariable underFunctionVariable2Loaded( iBitStream, outStatus, liDefinedVariables, pVariableDomain ); "<<endl;
		cFunctionVariable underFunctionVariable2Loaded( iBitStream, outStatus, liDefinedVariables, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionVariable2Loaded, "underFunctionVariable2Loaded", underFunctionVariable2, "underFunctionVariable2" );
		iReturn += testNotConnectedUnderFunction( underFunctionVariable2Loaded );

		delete fileInXml;
		ifstream * fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream2( * fileInXml );
		outStatus = 0;
		cout<<"cFunctionVariable pUnderFunctionVariable2Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctionVariable2Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionVariable2Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionVariable2Loaded, "pUnderFunctionVariable2Loaded", underFunctionVariable2, "underFunctionVariable2" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionVariable2Loaded );
			delete pUnderFunctionVariable2Loaded;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
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
		cout<<"cFunctionVariable underFunctionVariable2LoadedFull( iBitStream3, "<<
			"outStatus, liDefinedVariables, pVariableDomain, &underFunctionSup, &rootSimple ); "<<endl;
		cFunctionVariable underFunctionVariable2LoadedFull( iBitStream3,
			outStatus, liDefinedVariables, pVariableDomain, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionVariable2LoadedFull,
			"underFunctionVariable2LoadedFull", underFunctionVariable2, "underFunctionVariable2" );
		//check the getDefiningFibElement() methode from cFunctionVariable
		if ( underFunctionVariable2LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionVariable2LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionVariable2LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionVariable
		if ( underFunctionVariable2LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionVariable2LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionVariable2LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		
		delete fileInXml;
		fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * fileInXml );
		outStatus = 0;
		cout<<"cFunctionVariable pUnderFunctionVariable2LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionVariable2LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionVariable2LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionVariable2LoadedFull, "pUnderFunctionVariable2LoadedFull", underFunctionVariable2, "underFunctionVariable2" );
			//check the getDefiningFibElement() methode from cFunctionVariable
			if ( pUnderFunctionVariable2LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionVariable2LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionVariable2LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionVariable
			if ( pUnderFunctionVariable2LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionVariable2LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionVariable2LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctionVariable2LoadedFull;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
			iReturn++;
		}
		delete fileInXml;
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with given restbit"<<endl;

	cout<<"cFunctionVariable underFunctionVariable3( pVariable3, NULL, &root );"<<endl;
	cFunctionVariable underFunctionVariable3( pVariable3, NULL, &root );
	
	cout<<"pVariable3->setValue( 33.0 );"<<endl;
	pVariable3->setValue( 33.0 );
	
	//test get compressed size
	uiCompressedSize = 2 + 6;
	if ( (unsigned int)(underFunctionVariable3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			underFunctionVariable3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "underFunctionVariable3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0x01;
	cRestBitPosition = 2;
	cout<<"underFunctionVariable3.store( *pFile, cRestBit, cRestBitPosition ); "<<endl;
	bStoreSuccesfull = underFunctionVariable3.store( *pFile, cRestBit, cRestBitPosition );
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
	const char szUnderFunctionVariable3[] = { 0x15, 0x02 };
	iReturn += compareBytsWithFile( szFileNameBuffer, szUnderFunctionVariable3, 2 );


	fileInXml = new ifstream( szFileNameBuffer );
	if ( (fileInXml != NULL) && ( fileInXml->good() ) ){
		
		cReadBits iBitStream( * fileInXml );
		char cBuffer;
		iBitStream.readBits( &cBuffer, 2 + 2 );
		intFib outStatus = 0;
		cout<<"cFunctionVariable underFunctionVariable3Loaded( iBitStream, outStatus, liDefinedVariables, pVariableDomain ); "<<endl;
		cFunctionVariable underFunctionVariable3Loaded( iBitStream, outStatus, liDefinedVariables, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		int iErrorsEqual = testCompareTwoEqualObjects( underFunctionVariable3Loaded, "underFunctionVariable3Loaded", underFunctionVariable3, "underFunctionVariable3" );
		iReturn += testNotConnectedUnderFunction( underFunctionVariable3Loaded );
		if ( iErrorsEqual != 0 ){
			cerr<<"Error: Loaded underfunction not equal (value="<<
				underFunctionVariable3Loaded.getValue() <<")."<<endl;
		}
		iReturn += iErrorsEqual;

		delete fileInXml;
		ifstream * fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream2( * fileInXml );
		iBitStream2.readBits( &cBuffer, 2 );
		outStatus = 0;
		cout<<"cFunctionVariable pUnderFunctionVariable3Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctionVariable3Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionVariable3Loaded ){
			iErrorsEqual = testCompareTwoEqualObjects( * pUnderFunctionVariable3Loaded, "pUnderFunctionVariable3Loaded", underFunctionVariable3, "underFunctionVariable3" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionVariable3Loaded );
			if ( iErrorsEqual != 0 ){
				cerr<<"Error: Loaded underfunction not equal (value="<<
					underFunctionVariable3Loaded.getValue() <<")."<<endl;
			}
			iReturn += iErrorsEqual;
			delete pUnderFunctionVariable3Loaded;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
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
		cout<<"cFunctionVariable underFunctionVariable3LoadedFull( iBitStream3, "<<
			"outStatus, liDefinedVariables, pVariableDomain, &underFunctionSup, &rootSimple ); "<<endl;
		cFunctionVariable underFunctionVariable3LoadedFull( iBitStream3,
			outStatus, liDefinedVariables, pVariableDomain, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionVariable3LoadedFull,
			"underFunctionVariable3LoadedFull", underFunctionVariable3, "underFunctionVariable3" );
		//check the getDefiningFibElement() methode from cFunctionVariable
		if ( underFunctionVariable3LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionVariable3LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionVariable3LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionVariable
		if ( underFunctionVariable3LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionVariable3LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionVariable3LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		
		delete fileInXml;
		fileInXml = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * fileInXml );
		iBitStream4.readBits( &cBuffer, 2 );
		outStatus = 0;
		cout<<"cFunctionVariable pUnderFunctionVariable3LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionVariable3LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionVariable3LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctionVariable3LoadedFull, "pUnderFunctionVariable3LoadedFull", underFunctionVariable3, "underFunctionVariable3" );
			//check the getDefiningFibElement() methode from cFunctionVariable
			if ( pUnderFunctionVariable3LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionVariable3LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionVariable3LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionVariable
			if ( pUnderFunctionVariable3LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionVariable3LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionVariable3LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctionVariable3LoadedFull;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: The defined variables wher changed ."<<endl;
			iReturn++;
		}
		delete fileInXml;
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}


	delete pVariableDomain;
	delete pValueDomain;

	return iReturn;
}



/**
 * This method tests the variable methods of the cFunctionVariable class.
 *
 * methods tested:
 * 	- cFibVariable * getVariable();
 * 	- bool setVariable( cFibVariable * pInVariable );
 * 	- doubleFib getValue() const;
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
	cout<<"pVariable2 = rootSimple1.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = rootSimple1.getInputVariable( 2 );
	cout<<"pVariable3 = rootSimple1.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = rootSimple1.getInputVariable( 3 );
	cout<<"pVariable4 = rootSimple1.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable4 = rootSimple1.getInputVariable( 4 );
	
	cout<<"cFunctionVariable underFunctionVariable1( pVariable1 );"<<endl;
	cFunctionVariable underFunctionVariable1( pVariable1 );
	set<cFibVariable*> setCorrectUsedVariables;
	setCorrectUsedVariables.insert( pVariable1 );
	
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.getVariable()"<<endl;
	if ( underFunctionVariable1.getVariable() == pVariable1 ){
	
		cout<<"The variable pVariable1 is correctly given back as used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not given back as used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable1 )"<<endl;
	if ( underFunctionVariable1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable2 )"<<endl;
	if ( ! underFunctionVariable1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionVariable1.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = underFunctionVariable1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getValue() method"<<endl;

	//check the getValue() methode from cFunctionVariable
	cout<<"pVariable1->setValue( 1.0 );"<<endl;
	pVariable1->setValue( 1.0 );
	cout<<"underFunctionVariable1.getValue()"<<endl;
	if ( underFunctionVariable1.getValue() == 1.0 ){
	
		cout<<"The the value "<< underFunctionVariable1.getValue() <<
			" was correctly returned by the underfunction. "<<endl;
	}else{
		cerr<<"Error: The the value "<< underFunctionVariable1.getValue() <<
			" was returned by the underfunction, but it should be "<< 1.0 <<" . "<<endl;
		iReturn++;
	}
	//check the getValue() methode from cFunctionVariable
	cout<<"pVariable1->setValue( 381.521 );"<<endl;
	pVariable1->setValue( 381.521 );
	cout<<"underFunctionVariable1.getValue()"<<endl;
	if ( underFunctionVariable1.getValue() == 381.521 ){
	
		cout<<"The the value "<< underFunctionVariable1.getValue() <<
			" was correctly returned by the underfunction. "<<endl;
	}else{
		cerr<<"Error: The the value "<< underFunctionVariable1.getValue() <<
			" was returned by the underfunction, but it should be "<< 381.521 <<" . "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the setVariable() method"<<endl;

	//check the setVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.setVariable( pVariable2 );"<<endl;
	bool bVariableSet = underFunctionVariable1.setVariable( pVariable2 );
	setCorrectUsedVariables.clear();
	setCorrectUsedVariables.insert( pVariable2 );
	if ( bVariableSet ){
	
		cout<<"The variable pVariable2 could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 couldn't be set. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.getVariable()"<<endl;
	if ( underFunctionVariable1.getVariable() == pVariable2 ){
	
		cout<<"The variable pVariable2 is correctly given back as used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not given back as used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable2 )"<<endl;
	if ( underFunctionVariable1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! underFunctionVariable1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionVariable1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionVariable1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	
	//check the setVariable() methode from cFunctionVariable
	cout<<endl<<"underFunctionVariable1.setVariable( pVariable2 );"<<endl;
	bVariableSet = underFunctionVariable1.setVariable( pVariable2 );
	if ( bVariableSet ){
	
		cout<<"The variable pVariable2 could correctly be set. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 couldn't be set. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.getVariable()"<<endl;
	if ( underFunctionVariable1.getVariable() == pVariable2 ){
	
		cout<<"The variable pVariable2 is correctly given back as used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not given back as used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable2 )"<<endl;
	if ( underFunctionVariable1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! underFunctionVariable1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionVariable1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionVariable1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	
	//check the setVariable() methode from cFunctionVariable
	cout<<endl<<"underFunctionVariable1.setVariable( NULL );"<<endl;
	bVariableSet = underFunctionVariable1.setVariable( NULL );
	if ( ! bVariableSet ){
	
		cout<<"The pointer to NULL couldn't correctly be set as the variable. "<<endl;
	}else{
		cerr<<"Error: The pointer to NULL could be set as the variable. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.getVariable()"<<endl;
	if ( underFunctionVariable1.getVariable() == pVariable2 ){
	
		cout<<"The variable pVariable2 is correctly given back as used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not given back as used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable2 )"<<endl;
	if ( underFunctionVariable1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! underFunctionVariable1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionVariable1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionVariable1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the replaceVariable() method"<<endl;
	
	cout<<"underFunctionVariable1.replaceVariable( pVariable2, pVariable3 );"<<endl;
	bool bVariableReplaced = underFunctionVariable1.replaceVariable( pVariable2, pVariable3 );
	setCorrectUsedVariables.clear();
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.getVariable()"<<endl;
	if ( underFunctionVariable1.getVariable() == pVariable3 ){
	
		cout<<"The variable pVariable3 is correctly given back as used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not given back as used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionVariable1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable2 )"<<endl;
	if ( ! underFunctionVariable1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionVariable1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionVariable1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"underFunctionVariable1.replaceVariable( pVariable2, pVariable4 );"<<endl;
	bVariableReplaced = underFunctionVariable1.replaceVariable( pVariable2, pVariable4 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.getVariable()"<<endl;
	if ( underFunctionVariable1.getVariable() == pVariable3 ){
	
		cout<<"The variable pVariable3 is correctly given back as used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not given back as used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionVariable1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! underFunctionVariable1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionVariable1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionVariable1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"underFunctionVariable1.replaceVariable( pVariable3, pVariable3 );"<<endl;
	bVariableReplaced = underFunctionVariable1.replaceVariable( pVariable3, pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.getVariable()"<<endl;
	if ( underFunctionVariable1.getVariable() == pVariable3 ){
	
		cout<<"The variable pVariable3 is correctly given back as used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not given back as used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionVariable1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! underFunctionVariable1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionVariable1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionVariable1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"underFunctionVariable1.replaceVariable( NULL, pVariable1 );"<<endl;
	bVariableReplaced = underFunctionVariable1.replaceVariable( NULL, pVariable1 );
	if ( ! bVariableReplaced ){
	
		cout<<"The variable was correctly not replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.getVariable()"<<endl;
	if ( underFunctionVariable1.getVariable() == pVariable3 ){
	
		cout<<"The variable pVariable3 is correctly given back as used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not given back as used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionVariable1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! underFunctionVariable1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionVariable1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionVariable1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"underFunctionVariable1.replaceVariable( pVariable3, NULL );"<<endl;
	bVariableReplaced = underFunctionVariable1.replaceVariable( pVariable3, NULL );
	if ( ! bVariableReplaced ){
	
		cout<<"The variable was correctly not replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.getVariable()"<<endl;
	if ( underFunctionVariable1.getVariable() == pVariable3 ){
	
		cout<<"The variable pVariable3 is correctly given back as used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not given back as used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionVariable1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionVariable
	cout<<"underFunctionVariable1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! underFunctionVariable1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionVariable1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionVariable1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the variable methods of the cFunctionVariable class.
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
	
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	cout<<"rootSimple1.setNumberOfInputVariables( 10 );"<<endl;
	rootSimple1.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 = rootSimple1.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootSimple1.getInputVariable( 1 );
	
	cout<<"cFunctionVariable underFunctionVariable1( pVariable1 );"<<endl;
	cFunctionVariable underFunctionVariable1( pVariable1 );
	
	cFunctionVariable ufValueCorrect1( pVariable1 );
	
	cFibElement * pDefiningFibElement = NULL;
	//check the getDefiningFibElement() methode from cFunctionVariable
	if ( underFunctionVariable1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionVariable1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionVariable1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( underFunctionVariable1, "underFunctionVariable1", ufValueCorrect1, "correct underfunction" );
	
	cPoint point1;
	cout<<"underFunctionVariable1.setDefiningFibElement( &point1 );"<<endl;
	underFunctionVariable1.setDefiningFibElement( &point1 );
	pDefiningFibElement = &point1;
	//check the getDefiningFibElement() methode from cFunctionVariable
	if ( underFunctionVariable1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionVariable1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionVariable1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( underFunctionVariable1, "underFunctionVariable1", ufValueCorrect1, "correct underfunction" );
	
	cout<<"underFunctionVariable1.setDefiningFibElement( &point1 );"<<endl;
	underFunctionVariable1.setDefiningFibElement( &point1 );
	pDefiningFibElement = &point1;
	//check the getDefiningFibElement() methode from cFunctionVariable
	if ( underFunctionVariable1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionVariable1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionVariable1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( underFunctionVariable1, "underFunctionVariable1", ufValueCorrect1, "correct underfunction" );
	
	cout<<"cRoot root;"<<endl;
	cRoot root;
	
	cout<<"cTypeUnderFunction testTypeUnderFunction;"<<endl;
	cTypeUnderFunction testTypeUnderFunction;
	
	//create vector domain with two elements
	cout<<"cDomainNaturalNumberBit domainsNatB6( 6 );"<<endl;
	cDomainNaturalNumberBit domainsNatB6( 6 );

	cout<<"root.getDomains()->addDomain( testTypeUnderFunction, &domainsNatB6 );"<<endl;
	root.getDomains()->addDomain( testTypeUnderFunction, &domainsNatB6 );
	
	cout<<"cTypeVariable testTypeVariable;"<<endl;
	cTypeVariable testTypeVariable;
	
	cout<<"cDomainNaturalNumberBit naturalNumberDomainB4( 4 );"<<endl;
	cDomainNaturalNumberBit naturalNumberDomainB4( 4 );
	
	cout<<"root.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB4 );"<<endl;
	root.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB4 );

	cout<<"underFunctionVariable1.setDefiningFibElement( &root );"<<endl;
	underFunctionVariable1.setDefiningFibElement( &root );
	pDefiningFibElement = &root;
	//check the getDefiningFibElement() methode from cFunctionVariable
	if ( underFunctionVariable1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionVariable1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionVariable1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( underFunctionVariable1, "underFunctionVariable1", ufValueCorrect1, "correct underfunction" );

	
	return iReturn;
}










