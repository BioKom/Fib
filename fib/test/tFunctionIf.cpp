/**
 * @file tFunctionIf
 * file name: tFunctionIf.cpp
 * @author Betti Oesterholz
 * @date 09.06.2011
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for some special subfunctions.
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
 * This test is for some special subfunctions, which can't be tested with
 * the standard tFunction*Value test.
 *
 *
 * What's tested of class cUnderFunction:
 * 	- cUnderFunction( ..., cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cUnderFunction( const cUnderFunction & underfunction, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- cUnderFunction( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cUnderFunction( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- ~cUnderFunction();
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
 * functions tested for classes:
 * 	- cFunctionIf:
 * 		- cFunctionIf( const cUnderFunction & function, const cUnderFunction & firstUnderfunction, const cUnderFunction & secondUnderfunction, cUnderFunction * pInSuperiorFunction = NULL, FibElement * pInDefiningFibElement = NULL );
 * 		- cFunctionIf( const cCondition * pInCondition, const cUnderFunction * pInFirstUnderfunction, const cUnderFunction * pInSecondUnderfunction, cUnderFunction * pInSuperiorFunction, cFibElement * pInDefiningFibElement )
 * 		- cUnderFunction * getCondition();
 * 		- const cUnderFunction * getCondition() const;
 * 		- bool setCondition( const cUnderFunction & inCondition, bool bDeleteOld=true );
 * 		- bool setCondition( cUnderFunction * pInCondition, bool bDeleteOld=true );
 * 		- cUnderFunction * getFirstUnderFunction();
 * 		- void setFirstUnderFunction( const cUnderFunction & underFunction, bool bDeleteOld=true );
 * 		- cUnderFunction * getSecondUnderFunction();
 * 		- void setSecondUnderFunction( const cUnderFunction & underFunction, bool bDeleteOld=true );
 *
 * call: tFunctionIf [MAX_RAND_TEST_SIZE]
 *
 * parameters:
 * 	MAX_RAND_TEST_SIZE
 * 		A number for the random test sizes.
 * 		Standardvalue is 256.
 *
 */
/*
History:
09.06.2011  Oesterholz  created
09.10.2012  Oesterholz  Warning removed: "(char)" for char arrays added
09.03.2013  Oesterholz  Bugfix: isEqual() corrected
*/

#include "version.h"

#include "cUnderFunction.h"
#include "cFunctionIf.h"
#include "cConditionTrue.h"
#include "cConditionFalse.h"
#include "cConditionNot.h"
#include "cConditionGreater.h"
#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cFunctionAbs.h"
#include "cPoint.h"
#include "cRoot.h"
#include "cProperty.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cDomainRational.h"
#include "cTypeVariable.h"
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
int testSubElements( unsigned long &ulTestphase );
int testVariable( unsigned long &ulTestphase );
int testDefiningFibElement( unsigned long &ulTestphase );


//the size of the random tests
unsigned long MAX_RAND_TEST_SIZE = 256;


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	if ( argc >= 2 ){
		//one parameter given; read parameter iterations
		MAX_RAND_TEST_SIZE = atol( argv[1] );
		if ( MAX_RAND_TEST_SIZE < 1 ){
			MAX_RAND_TEST_SIZE = 1;
		}
	}
	
	cout<<endl<<"Running Test for cFunctionIf methods"<<endl;
	cout<<      "===================================="<<endl;
	
	iReturn += testCostructor( ulTestphase );
	iReturn += testEqual( ulTestphase );
	iReturn += testCopy( ulTestphase );
	iReturn += testStoreXml( ulTestphase );
	iReturn += testStore( ulTestphase );
	iReturn += testSubElements( ulTestphase );
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
 * @param dValue the value to check
 * @return true if the value is not a number, else false
 */
inline bool own_isnan( doubleFib dValue ){
    return dValue != dValue;
}


/**
 * @param dValue the value to check
 * @return true if the value is infinity, else false
 */
inline bool own_isinf( doubleFib dValue ){
    return ( ( dValue == INFINITY ) || ( dValue == -INFINITY ) );
}


/**
 * This function compares two values with a given savety boundery.
 *
 * @param dValue1 the first value to compare
 * @param dValue2 the second value to compare
 * @return true if the values are very simular
 */
bool isEqual( doubleFib dValue1, doubleFib dValue2 ){

	if ( own_isnan( dValue1 ) || own_isnan( dValue2 ) ){
		if ( own_isnan( dValue1 ) && own_isnan( dValue2 ) ){
			return true;
		}
		return false;
	}
	if ( own_isinf( dValue1 ) || own_isinf( dValue2 ) ){
		if ( own_isinf( dValue1 ) && own_isinf( dValue2 ) ){
			return true;
		}
		return false;
	}
	
	const doubleFib dSaveBoundery1 = abs( dValue1 / 1000000.0 );
	const doubleFib dSaveBoundery2 = abs( dValue2 / 1000000.0 );
	const doubleFib dSaveBoundery  = min( dSaveBoundery1, dSaveBoundery2 );
	
	if ( ( dValue1 - dSaveBoundery <= dValue2 ) &&
			( dValue2 <= dValue1 + dSaveBoundery ) ){
		return true;
	}
	return false;
}



/**
 * This function returns the value of the given subfunction by evaluating
 * its subelements.
 *
 * @return the value of the given subfunction
 */
double getCorrectValue( cFunctionIf * pUnderFunctionIf ){
	
	if ( pUnderFunctionIf == NULL ){
		return 0.0;
	}
	if ( ( pUnderFunctionIf->getCondition() != NULL ) &&
			( pUnderFunctionIf->getCondition()->getValue() ) ){
		//evalue first under function
		if ( pUnderFunctionIf->getFirstUnderFunction() ){
			return pUnderFunctionIf->getFirstUnderFunction()->getValue();
		}//else
		return 0.0;
	}//else evalue second under function
	if ( pUnderFunctionIf->getSecondUnderFunction() ){
		return pUnderFunctionIf->getSecondUnderFunction()->getValue();
	}//else
	return 0.0;
}



/**
 * This function returns the name of the type of the tested subfunction.
 *
 * @return "if"
 */
string getUnderFunctionName(){
	
	return "if";
}


/**
 * This function returns the number of the type of the tested subfunction.
 *
 * @return CONDITION_OR
 */
unsignedIntFib getFunctionType(){
	
	return cUnderFunction::FUNCTION_IF;
}


/**
 * This function returns the number of type bits of the tested subfunction.
 *
 * @return 10
 */
unsigned int getNumberOfTypeBits(){
	
	return 10;
}



/**
 * This function tests the constructor of the cFunctionIf class.
 *
 * methods tested:
 * 		- cFunctionIf( const cCondition & function, const cUnderFunction & firstUnderfunction, const cUnderFunction & secondUnderfunction, cUnderFunction * pInSuperiorFunction = NULL, FibElement * pInDefiningFibElement = NULL );
 * 		- cFunctionIf( const cCondition * pInCondition, const cUnderFunction * pInFirstUnderfunction, const cUnderFunction * pInSecondUnderfunction, cUnderFunction * pInSuperiorFunction, cFibElement * pInDefiningFibElement )
 * 	- ~cUnderFunction();
 * 	- bool isValid() const;
 * 	- bool isUsedVariable( const cFibVariable * variable ) const;
 * 	- set<cFibVariable*> getUsedVariables();
 * 	- bool getValue() const;
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
	cout<<"pVariable1 = rootEmpty.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = rootEmpty.getInputVariable( 1 );
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cFunctionIf function"<<endl;

	cout<<"cFunctionIf functionIfNull( NULL, NULL, NULL );"<<endl;
	cFunctionIf functionIfNull( NULL, NULL, NULL );
	
	cFibElement * pDefiningFibElement = NULL;
	cUnderFunction * pSuperiorUnderFunction = NULL;
	cCondition * pCondition = NULL;
	cUnderFunction * pFirstSubFunction = NULL;
	cUnderFunction * pSecondSubFunction = NULL;
	cTypeUnderFunction typeUnderFunction;
	cDomain * pUnderFunctionDomain = NULL;
	cDomain * pValueDomain = NULL;
	cDomain * pStandardDomain = typeUnderFunction.getStandardDomain();
	cTypeVariable typeVariable;
	cDomain * pVariableDomain = typeVariable.getStandardDomain();
	unsigned long ulTimeNeed = 1;
	unsigned long ulCompressedSize = getNumberOfTypeBits();

	//check the getValue() methode from cFunctionIf
	if ( isEqual( functionIfNull.getValue(),
			getCorrectValue( &functionIfNull ) ) ){
	
		cout<<"The function value is correctly "<<
			functionIfNull.getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The function value is "<<
			functionIfNull.getValue() <<" but should be "<<
			getCorrectValue( &functionIfNull )<<"."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionIf
	if ( functionIfNull.getDefiningFibElement() == pDefiningFibElement ){
	
		cout<<"The function defining Fib-element is correctly "<<
			functionIfNull.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The function defining Fib-element is "<<
			functionIfNull.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionIf
	if ( functionIfNull.getSuperiorUnderFunction() == pSuperiorUnderFunction ){
	
		cout<<"The superior function of the function correctly "<<
			functionIfNull.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior function of the function is "<<
			functionIfNull.getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstUnderFunction() methode from cFunctionIf
	if ( functionIfNull.getFirstUnderFunction() == pFirstSubFunction ){
	
		cout<<"The first subfunction of the function correctly "<<
			functionIfNull.getFirstUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The first subfunction of the function is "<<
			functionIfNull.getFirstUnderFunction() <<
			" but should be "<< pFirstSubFunction <<" ."<<endl;
		iReturn++;
	}
	//check the getSecondUnderFunction() methode from cFunctionIf
	if ( functionIfNull.getSecondUnderFunction() == pSecondSubFunction ){
	
		cout<<"The second subfunction of the function correctly "<<
			functionIfNull.getSecondUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The second subfunction of the function is "<<
			functionIfNull.getSecondUnderFunction() <<
			" but should be "<< pSecondSubFunction <<" ."<<endl;
		iReturn++;
	}
	//check the getCondition() methode from cFunctionIf
	if ( functionIfNull.getCondition() == pCondition ){
	
		cout<<"The condition of the function correctly "<<
			functionIfNull.getCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition of the function is "<<
			functionIfNull.getCondition() <<
			" but should be "<< pCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cFunctionIf
	if ( ! functionIfNull.isValid() ){
	
		cout<<"The function is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The function is valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionIf
	if ( functionIfNull.getType() == getFunctionType() ){
	
		cout<<"The function type is correctly "<<
			getFunctionType()<<". "<<endl;
	}else{
		cerr<<"Error: The type of the function is not "<<
			getFunctionType()<<", but "<<
			functionIfNull.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionIf
	if ( functionIfNull.getUnderFunctionName() == getUnderFunctionName() ){
	
		cout<<"The function name is correctly \""<<
			functionIfNull.getUnderFunctionName() <<"\" . "<<endl;
	}else{
		cerr<<"Error: The name of the function is not \""<<
			getUnderFunctionName()<<"\", but \""<<
			functionIfNull.getUnderFunctionName() <<"\" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from cFunctionIf
	if ( functionIfNull.getNumberOfUnderFunctions() == 2 ){
	
		cout<<"The function number of subfunctions is correctly "<<
			functionIfNull.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The function number of subfunctions is "<<
			functionIfNull.getNumberOfUnderFunctions() <<" , but should be 2 ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cFunctionIf
	cTypeElement * pTypeOfUnderFunction = functionIfNull.getElementType();
	if ( pTypeOfUnderFunction != NULL ){
		if ( * pTypeOfUnderFunction == typeUnderFunction ){
		
			cout<<"The given back element type for the subfunction is correct. "<<endl;
		}else{
			cerr<<"Error: The given back element type for the subfunction is not correct."<<endl;
			iReturn++;
		}
		delete pTypeOfUnderFunction;
	}else{
		cerr<<"Error: The given back element type for the subfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cFunctionIf
	cDomain * pRetUnderFunctionDomain = functionIfNull.getDomain();
	if ( pUnderFunctionDomain != NULL ){
		if ( pRetUnderFunctionDomain != NULL ){
			if ( * pRetUnderFunctionDomain == * pUnderFunctionDomain ){
			
				cout<<"The given back domain for the subfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back domain for the subfunction is not correct."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The given back domain for the subfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		if ( pRetUnderFunctionDomain == NULL ){
		
			cout<<"The given back domain for the subfunction is correctly NULL . "<<endl;
		}else{
			cerr<<"Error: The given back domain for the subfunction is not NULL ."<<endl;
			iReturn++;
		}
	}
	//check the getValueDomain() methode from cFunctionIf
	cDomain * pRetValueDomain = functionIfNull.getValueDomain();
	if ( pValueDomain != NULL ){
		if ( pRetValueDomain != NULL ){
			if ( * pRetValueDomain == * pValueDomain ){
			
				cout<<"The given back valuedomain for the subfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back valuedomain for the subfunction is not correct."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The given back valuedomain for the subfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		if ( pRetValueDomain == NULL ){
		
			cout<<"The given back valuedomain for the subfunction is correctly NULL . "<<endl;
		}else{
			cerr<<"Error: The given back valuedomain for the subfunction is not NULL ."<<endl;
			iReturn++;
		}
	}
	//check the getStandardDomain() methode from cFunctionIf
	cDomain * pRetStandardDomain = functionIfNull.getStandardDomain();
	if ( pStandardDomain != NULL ){
		if ( pRetStandardDomain != NULL ){
			if ( * pRetStandardDomain == * pStandardDomain ){
			
				cout<<"The given back the standarddomain for the subfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back the standarddomain domain for the subfunction is not correct."<<endl;
				iReturn++;
			}
			delete pRetStandardDomain;
		}else{
			cerr<<"Error: The given back the standarddomain domain for the subfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The given back the standarddomain domain for the subfunction is not NULL ."<<endl;
	}
	//check the getVariableDomain() methode from cFunctionIf
	cDomain * pRetVariableDomain = functionIfNull.getVariableDomain();
	if ( pVariableDomain != NULL ){
		if ( pRetVariableDomain != NULL ){
			if ( * pRetVariableDomain == * pVariableDomain ){
			
				cout<<"The given back variabledomain for the subfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back variabledomain for the subfunction is not correct."<<endl;
				iReturn++;
			}
			delete pRetVariableDomain;
		}else{
			cerr<<"Error: The given back variabledomain for the subfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		if ( pRetVariableDomain == NULL ){
		
			cout<<"The given back variabledomain for the subfunction is correctly NULL . "<<endl;
		}else{
			cerr<<"Error: The given back variabledomain for the subfunction is not NULL ."<<endl;
			iReturn++;
			delete pRetVariableDomain;
		}
	}
	
	//check the getTimeNeed() methode from cFunctionIf
	if ( functionIfNull.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			functionIfNull.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionIf
	if ( functionIfNull.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the function is "<<
			functionIfNull.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	//check the getCompressedSize() methode from cFunctionIf
	if ( ! functionIfNull.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 isn't used in the function. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the function. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionIf
	set<cFibVariable*> setUsedVariables = functionIfNull.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"No used variables are given back from the function. "<<endl;
	}else{
		cerr<<"Error: Used variables are given back from the function. "<<endl;
		iReturn++;
	}


	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an cFunctionIf function with all values set"<<endl;

	cout<<"cConditionFalse subConditionFalse;"<<endl;
	cConditionFalse subConditionFalse;
	
	cout<<"cFunctionValue funValue1( 1 );"<<endl;
	cFunctionValue funValue1( 1 );
	
	cout<<"cFunctionValue funValue2( 2 );"<<endl;
	cFunctionValue funValue2( 2 );
	
	cout<<"cFunctionIf functionIfFull( subConditionFalse, funValue1, funValue2, &functionIfNull, &rootEmpty );"<<endl;
	cFunctionIf functionIfFull( subConditionFalse, funValue1, funValue2, &functionIfNull, &rootEmpty );
	
	
	pDefiningFibElement = &rootEmpty;
	pSuperiorUnderFunction = &functionIfNull;
	pCondition = &subConditionFalse;
	pFirstSubFunction = &funValue1;
	pSecondSubFunction = &funValue2;
	ulTimeNeed = 4;
	ulCompressedSize = getNumberOfTypeBits() + 4 + 2 * (2 + 16);

	//check the getValue() methode from cFunctionIf
	if ( isEqual( functionIfFull.getValue(),
			getCorrectValue( &functionIfFull ) ) ){
	
		cout<<"The function value is correctly "<<
			functionIfFull.getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The function value is "<<
			functionIfFull.getValue() <<" but should be "<<
			getCorrectValue( &functionIfFull )<<"."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionIf
	if ( functionIfFull.getDefiningFibElement() == pDefiningFibElement ){
	
		cout<<"The function defining Fib-element is correctly "<<
			functionIfFull.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The function defining Fib-element is "<<
			functionIfFull.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionIf
	if ( functionIfFull.getSuperiorUnderFunction() == pSuperiorUnderFunction ){
	
		cout<<"The superior function of the function correctly "<<
			functionIfFull.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior function of the function is "<<
			functionIfFull.getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	//check the getFirstUnderFunction() methode from cFunctionIf
	if ( pFirstSubFunction->equal( *(functionIfFull.getFirstUnderFunction()) ) ){
	
		cout<<"The first subfunction of the function correctly equal to "<<
			functionIfFull.getFirstUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The first subfunction of the function "<<
			functionIfFull.getFirstUnderFunction() <<
			" not equal to "<< pFirstSubFunction <<" ."<<endl;
		iReturn++;
	}
	//check the getSecondUnderFunction() methode from cFunctionIf
	if ( pSecondSubFunction->equal( *(functionIfFull.getSecondUnderFunction()) ) ){
	
		cout<<"The second subfunction of the function correctly equal to "<<
			functionIfFull.getSecondUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The second subfunction of the function "<<
			functionIfFull.getSecondUnderFunction() <<
			" not equal to "<< pSecondSubFunction <<" ."<<endl;
		iReturn++;
	}

	//check the getCondition() methode from cFunctionIf
	if ( pCondition->equal( *(functionIfFull.getCondition()) ) ){
	
		cout<<"The condition of the function correctly equal to "<<
			functionIfFull.getCondition() <<" . "<<endl;
	}else{
		cerr<<"Error: The condition of the function "<<
			functionIfFull.getCondition() <<
			" is not equal to "<< pCondition <<" ."<<endl;
		iReturn++;
	}
	//check the isValid() methode from cFunctionIf
	if ( ! functionIfFull.isValid() ){
	
		cout<<"The function is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The function is valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionIf
	if ( functionIfFull.getType() == getFunctionType() ){
	
		cout<<"The function type is correctly "<<
			getFunctionType()<<". "<<endl;
	}else{
		cerr<<"Error: The type of the function is not "<<
			getFunctionType()<<", but "<<
			functionIfFull.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionIf
	if ( functionIfFull.getUnderFunctionName() == getUnderFunctionName() ){
	
		cout<<"The function name is correctly \""<<
			functionIfFull.getUnderFunctionName() <<"\" . "<<endl;
	}else{
		cerr<<"Error: The name of the function is not \""<<
			getUnderFunctionName()<<"\", but \""<<
			functionIfFull.getUnderFunctionName() <<"\" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfConditions() methode from cFunctionIf
	if ( functionIfFull.getNumberOfUnderFunctions() == 2 ){
	
		cout<<"The function number of subfunctions is correctly "<<
			functionIfFull.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The function number of subfunctions is "<<
			functionIfFull.getNumberOfUnderFunctions() <<" , but should be 2 ."<<endl;
		iReturn++;
	}
	
	//check the getElementType() methode from cFunctionIf
	pTypeOfUnderFunction = functionIfFull.getElementType();
	if ( pTypeOfUnderFunction != NULL ){
		if ( * pTypeOfUnderFunction == typeUnderFunction ){
		
			cout<<"The given back element type for the subfunction is correct. "<<endl;
		}else{
			cerr<<"Error: The given back element type for the subfunction is not correct."<<endl;
			iReturn++;
		}
		delete pTypeOfUnderFunction;
	}else{
		cerr<<"Error: The given back element type for the subfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDomain() methode from cFunctionIf
	pRetUnderFunctionDomain = functionIfFull.getDomain();
	if ( pUnderFunctionDomain != NULL ){
		if ( pRetUnderFunctionDomain != NULL ){
			if ( * pRetUnderFunctionDomain == * pUnderFunctionDomain ){
			
				cout<<"The given back domain for the subfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back domain for the subfunction is not correct."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The given back domain for the subfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		if ( pRetUnderFunctionDomain == NULL ){
		
			cout<<"The given back domain for the subfunction is correctly NULL . "<<endl;
		}else{
			cerr<<"Error: The given back domain for the subfunction is not NULL ."<<endl;
			iReturn++;
		}
	}
	//check the getValueDomain() methode from cFunctionIf
	pRetValueDomain = functionIfFull.getValueDomain();
	if ( pValueDomain != NULL ){
		if ( pRetValueDomain != NULL ){
			if ( * pRetValueDomain == * pValueDomain ){
			
				cout<<"The given back valuedomain for the subfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back valuedomain for the subfunction is not correct."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The given back valuedomain for the subfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		if ( pRetValueDomain == NULL ){
		
			cout<<"The given back valuedomain for the subfunction is correctly NULL . "<<endl;
		}else{
			cerr<<"Error: The given back valuedomain for the subfunction is not NULL ."<<endl;
			iReturn++;
		}
	}
	//check the getStandardDomain() methode from cFunctionIf
	pRetStandardDomain = functionIfFull.getStandardDomain();
	if ( pStandardDomain != NULL ){
		if ( pRetStandardDomain != NULL ){
			if ( * pRetStandardDomain == * pStandardDomain ){
			
				cout<<"The given back the standarddomain for the subfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back the standarddomain domain for the subfunction is not correct."<<endl;
				iReturn++;
			}
			delete pRetStandardDomain;
		}else{
			cerr<<"Error: The given back the standarddomain domain for the subfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The given back the standarddomain domain for the subfunction is not NULL ."<<endl;
	}
	//check the getVariableDomain() methode from cFunctionIf
	pRetVariableDomain = functionIfFull.getVariableDomain();
	if ( pVariableDomain != NULL ){
		if ( pRetVariableDomain != NULL ){
			if ( * pRetVariableDomain == * pVariableDomain ){
			
				cout<<"The given back variabledomain for the subfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back variabledomain for the subfunction is not correct."<<endl;
				iReturn++;
			}
			delete pRetVariableDomain;
		}else{
			cerr<<"Error: The given back variabledomain for the subfunction is NULL ."<<endl;
			iReturn++;
		}
	}else{
		if ( pRetVariableDomain == NULL ){
		
			cout<<"The given back variabledomain for the subfunction is correctly NULL . "<<endl;
		}else{
			cerr<<"Error: The given back variabledomain for the subfunction is not NULL ."<<endl;
			iReturn++;
			delete pRetVariableDomain;
		}
	}
	
	//check the getTimeNeed() methode from cFunctionIf
	if ( functionIfFull.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			functionIfFull.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionIf
	if ( functionIfFull.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The tcompressed size of the function is "<<
			functionIfFull.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	//check the getCompressedSize() methode from cFunctionIf
	if ( ! functionIfFull.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 isn't used in the function. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the function. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionIf
	setUsedVariables = functionIfFull.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"No used variables are given back from the function. "<<endl;
	}else{
		cerr<<"Error: Used variables are given back from the function. "<<endl;
		iReturn++;
	}




	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an random cFunctionIf function"<<endl;

	bool bIsValid = true;
	bool bIsPointer = true;
	cFunctionIf * pFunctionIfRand = NULL;
	
	set<cFibVariable*> setCorrectUsedVariables;
	
	cout<<"cConditionTrue subConditionTrue;"<<endl;
	cConditionTrue subConditionTrue;
	
	cout<<"cFunctionValue funValue3( 3 );"<<endl;
	cFunctionValue funValue3( 3 );
	cout<<"cFunctionValue funValue3p3( 3.3 );"<<endl;
	cFunctionValue funValue3p3( 3.3 );
	cout<<"cFunctionValue funValueVm1( -1 );"<<endl;
	cFunctionValue funValueVm1( -1 );
	

	cout<<"pVariable2 =  rootEmpty.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 =  rootEmpty.getInputVariable( 2 );
	cout<<"pVariable3 =  rootEmpty.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 =  rootEmpty.getInputVariable( 3 );
	cout<<"pVariable4 =  rootEmpty.getInputVariable( 4 );"<<endl;
	cFibVariable * pVariable4 =  rootEmpty.getInputVariable( 4 );
	cout<<"pVariable5 =  rootEmpty.getInputVariable( 5 );"<<endl;
	cFibVariable * pVariable5 =  rootEmpty.getInputVariable( 5 );
	
	cout<<"cFunctionVariable funVariable2( pVariable2 );"<<endl;
	cFunctionVariable funVariable2( pVariable2 );
	cout<<"cFunctionVariable funVariable3( pVariable3 );"<<endl;
	cFunctionVariable funVariable3( pVariable3 );
	cout<<"cFunctionVariable funVariable4( pVariable4 );"<<endl;
	cFunctionVariable funVariable4( pVariable4 );
	cout<<"cFunctionVariable funVariable5( pVariable5 );"<<endl;
	cFunctionVariable funVariable5( pVariable5 );
	
	cout<<"cDomainNaturalNumberBit domainNaturalNumberBit3( 3 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberBit3( 3 );
	cout<<"cDomainNaturalNumberBit domainNaturalNumberBit5( 5 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberBit5( 5 );
	cout<<"cDomainNaturalNumberBit domainNaturalNumberBit7( 7 );"<<endl;
	cDomainNaturalNumberBit domainNaturalNumberBit7( 7 );
	
	cout<<"cRoot rootFull;"<<endl;
	cRoot rootFull;
	cout<<"rootFull.getDomains()->addDomain( typeVariable, domainNaturalNumberBit3 );"<<endl;
	rootFull.getDomains()->addDomain( typeVariable, domainNaturalNumberBit3 );
	cout<<"rootFull.getDomains()->addDomain( typeUnderFunction, domainNaturalNumberBit5 );"<<endl;
	rootFull.getDomains()->addDomain( typeUnderFunction, domainNaturalNumberBit5 );
	cout<<"rootFull.getValueDomains()->addDomain( typeUnderFunction, domainNaturalNumberBit7 );"<<endl;
	rootFull.getValueDomains()->addDomain( typeUnderFunction, domainNaturalNumberBit7 );
	
	
	for ( unsigned int uiTestCase = 1; uiTestCase <= MAX_RAND_TEST_SIZE; uiTestCase++ ){
		
		setCorrectUsedVariables.clear();
		
		if ( rand() % 2 ){
			/*use constructor with references
				cFunctionIf( const cCondition & function, const cUnderFunction & firstUnderfunction, const cUnderFunction & secondUnderfunction, cUnderFunction * pInSuperiorFunction = NULL, FibElement * pInDefiningFibElement = NULL );*/
			cout<<endl<<"Generating new random function if with reference constructor:"<<endl;
			
			bIsValid = true;
			bIsPointer = false;
			
			//choose defining fib-element
			switch ( rand() % 3 ){
				case 0:
					cout<<"pDefiningFibElement = NULL"<<endl;
					pDefiningFibElement = NULL;
					pUnderFunctionDomain = NULL;
					pValueDomain = NULL;
					if ( pVariableDomain ){
						delete pVariableDomain;
					}
					pVariableDomain = typeVariable.getStandardDomain();
					ulCompressedSize = getNumberOfTypeBits() + 4 + 2 * (2 + 16);
				break;
				case 1:
					cout<<"pDefiningFibElement = &rootEmpty"<<endl;
					pDefiningFibElement = &rootEmpty;
					pUnderFunctionDomain = NULL;
					pValueDomain = NULL;
					if ( pVariableDomain ){
						delete pVariableDomain;
					}
					pVariableDomain = typeVariable.getStandardDomain();
					ulCompressedSize = getNumberOfTypeBits() + 4 + 2 * (2 + 16);
				break;
				case 2:
					cout<<"pDefiningFibElement = &rootFull"<<endl;
					pDefiningFibElement = &rootFull;
					pUnderFunctionDomain = &domainNaturalNumberBit5;
					pValueDomain = &domainNaturalNumberBit7;
					if ( pVariableDomain ){
						delete pVariableDomain;
					}
					pVariableDomain = domainNaturalNumberBit3.clone();
					ulCompressedSize = getNumberOfTypeBits() + 4 + 2 * (2 + 7);
				break;
			};//end switch choose defining fib-element
			//choose superior subfunction
			switch ( rand() % 3 ){
				case 0:
					cout<<"pSuperiorUnderFunction = NULL"<<endl;
					pSuperiorUnderFunction = NULL;
				break;
				case 1:
					cout<<"pSuperiorUnderFunction = &functionIfNull"<<endl;
					pSuperiorUnderFunction = &functionIfNull;
				break;
				case 2:
					cout<<"pSuperiorUnderFunction = &functionIfFull"<<endl;
					pSuperiorUnderFunction = &functionIfFull;
				break;
			};//end switch choose superior subfunction
			//choose condition
			switch ( rand() % 2 ){
				case 0:
					cout<<"pCondition = &subConditionTrue"<<endl;
					pCondition = &subConditionTrue;
				break;
				case 1:
					cout<<"pCondition = &subConditionFalse"<<endl;
					pCondition = &subConditionFalse;
				break;
			};//end switch choose condition
			unsigned char uiNumberOfVariableSubFunctions = 0;
			//choose first subfunction
			switch ( rand() % 9 ){
				case 0:
					cout<<"pFirstSubFunction = &funValue1"<<endl;
					pFirstSubFunction = &funValue1;
				break;
				case 1:
					cout<<"pFirstSubFunction = &funValue2"<<endl;
					pFirstSubFunction = &funValue2;
				break;
				case 2:
					cout<<"pFirstSubFunction = &funValue3"<<endl;
					pFirstSubFunction = &funValue3;
				break;
				case 3:
					cout<<"pFirstSubFunction = &funValue3p3"<<endl;
					pFirstSubFunction = &funValue3p3;
				break;
				case 4:
					cout<<"pFirstSubFunction = &funValueVm1"<<endl;
					pFirstSubFunction = &funValueVm1;
				break;
				case 5:
					cout<<"pFirstSubFunction = &funVariable2"<<endl;
					pFirstSubFunction = &funVariable2;
					setCorrectUsedVariables.insert( pVariable2 );
					uiNumberOfVariableSubFunctions++;
				break;
				case 6:
					cout<<"pFirstSubFunction = &funVariable3"<<endl;
					pFirstSubFunction = &funVariable3;
					setCorrectUsedVariables.insert( pVariable3 );
					uiNumberOfVariableSubFunctions++;
				break;
				case 7:
					cout<<"pFirstSubFunction = &funVariable4"<<endl;
					pFirstSubFunction = &funVariable4;
					setCorrectUsedVariables.insert( pVariable4 );
					uiNumberOfVariableSubFunctions++;
				break;
				case 8:
					cout<<"pFirstSubFunction = &funVariable5"<<endl;
					pFirstSubFunction = &funVariable5;
					setCorrectUsedVariables.insert( pVariable5 );
					uiNumberOfVariableSubFunctions++;
				break;
			};//end switch choose condition
			//choose second subfunction
			switch ( rand() % 9 ){
				case 0:
					cout<<"pSecondSubFunction = &funValue1"<<endl;
					pSecondSubFunction = &funValue1;
				break;
				case 1:
					cout<<"pSecondSubFunction = &funValue2"<<endl;
					pSecondSubFunction = &funValue2;
				break;
				case 2:
					cout<<"pSecondSubFunction = &funValue3"<<endl;
					pSecondSubFunction = &funValue3;
				break;
				case 3:
					cout<<"pSecondSubFunction = &funValue3p3"<<endl;
					pSecondSubFunction = &funValue3p3;
				break;
				case 4:
					cout<<"pSecondSubFunction = &funValueVm1"<<endl;
					pSecondSubFunction = &funValueVm1;
				break;
				case 5:
					cout<<"pSecondSubFunction = &funVariable2"<<endl;
					pSecondSubFunction = &funVariable2;
					setCorrectUsedVariables.insert( pVariable2 );
					uiNumberOfVariableSubFunctions++;
				break;
				case 6:
					cout<<"pSecondSubFunction = &funVariable3"<<endl;
					pSecondSubFunction = &funVariable3;
					setCorrectUsedVariables.insert( pVariable3 );
					uiNumberOfVariableSubFunctions++;
				break;
				case 7:
					cout<<"pSecondSubFunction = &funVariable4"<<endl;
					pSecondSubFunction = &funVariable4;
					setCorrectUsedVariables.insert( pVariable4 );
					uiNumberOfVariableSubFunctions++;
				break;
				case 8:
					cout<<"pSecondSubFunction = &funVariable5"<<endl;
					pSecondSubFunction = &funVariable5;
					setCorrectUsedVariables.insert( pVariable5 );
					uiNumberOfVariableSubFunctions++;
				break;
			};//end switch choose condition
			ulTimeNeed = 4;
			
			if ( uiNumberOfVariableSubFunctions != 0 ){
				//correct compressed size
				if ( pDefiningFibElement == &rootFull ){
					ulCompressedSize -= uiNumberOfVariableSubFunctions * 4;
				}else{
					ulCompressedSize -= uiNumberOfVariableSubFunctions * 8;
				}
			}
			
			cout<<"pConditionTest = new pFunctionIfRand( *pCondition, "<<
				"*pFirstSubFunction, *pSecondSubFunction, pSuperiorUnderFunction, pDefiningFibElement );"<<endl;
			pFunctionIfRand = new cFunctionIf( *pCondition, *pFirstSubFunction,
				*pSecondSubFunction, pSuperiorUnderFunction, pDefiningFibElement );
			
		}else{//use constructor with pointers
			/*use constructor with references
			- cFunctionIf( const cCondition * pInCondition, const cUnderFunction * pInFirstUnderfunction, const cUnderFunction * pInSecondUnderfunction, cUnderFunction * pInSuperiorFunction, cFibElement * pInDefiningFibElement )*/
			cout<<endl<<"Generating new random function if with pointer constructor:"<<endl;
			
			bIsValid = true;
			bIsPointer = true;
			
			//choose defining fib-element
			switch ( rand() % 3 ){
				case 0:
					cout<<"pDefiningFibElement = NULL"<<endl;
					pDefiningFibElement = NULL;
					pUnderFunctionDomain = NULL;
					pValueDomain = NULL;
					if ( pVariableDomain ){
						delete pVariableDomain;
					}
					pVariableDomain = typeVariable.getStandardDomain();
					ulCompressedSize = getNumberOfTypeBits() + 4 + 2 * (2 + 16);
				break;
				case 1:
					cout<<"pDefiningFibElement = &rootEmpty"<<endl;
					pDefiningFibElement = &rootEmpty;
					pUnderFunctionDomain = NULL;
					pValueDomain = NULL;
					if ( pVariableDomain ){
						delete pVariableDomain;
					}
					pVariableDomain = typeVariable.getStandardDomain();
					ulCompressedSize = getNumberOfTypeBits() + 4 + 2 * (2 + 16);
				break;
				case 2:
					cout<<"pDefiningFibElement = &rootFull"<<endl;
					pDefiningFibElement = &rootFull;
					pUnderFunctionDomain = &domainNaturalNumberBit5;
					pValueDomain = &domainNaturalNumberBit7;
					if ( pVariableDomain ){
						delete pVariableDomain;
					}
					pVariableDomain = domainNaturalNumberBit3.clone();
					ulCompressedSize = getNumberOfTypeBits() + 4 + 2 * (2 + 7);
				break;
			};//end switch choose defining fib-element
			//choose superior subfunction
			switch ( rand() % 3 ){
				case 0:
					cout<<"pSuperiorUnderFunction = NULL"<<endl;
					pSuperiorUnderFunction = NULL;
				break;
				case 1:
					cout<<"pSuperiorUnderFunction = &functionIfNull"<<endl;
					pSuperiorUnderFunction = &functionIfNull;
				break;
				case 2:
					cout<<"pSuperiorUnderFunction = &functionIfFull"<<endl;
					pSuperiorUnderFunction = &functionIfFull;
				break;
			};//end switch choose superior subfunction
			//choose condition
			switch ( rand() % 3 ){
				case 0:
					cout<<"pCondition = NULL"<<endl;
					pCondition = NULL;
					ulCompressedSize -= 4;
				break;
				case 1:
					cout<<"pCondition = new cConditionTrue()"<<endl;
					pCondition = new cConditionTrue();
				break;
				case 2:
					cout<<"pCondition = new cConditionFalse()"<<endl;
					pCondition = new cConditionFalse();
				break;
			};//end switch choose condition
			unsigned char uiNumberOfNullSubFunctions = 0;
			unsigned char uiNumberOfVariableSubFunctions = 0;
			//choose first subfunction
			switch ( rand() % 10 ){
				case 0:
					cout<<"pFirstSubFunction = NULL"<<endl;
					pFirstSubFunction = NULL;
					uiNumberOfNullSubFunctions++;
				break;
				case 1:
					cout<<"pFirstSubFunction = new cFunctionValue( 1 )"<<endl;
					pFirstSubFunction = new cFunctionValue( 1 );
				break;
				case 2:
					cout<<"pFirstSubFunction = new cFunctionValue( 2 )"<<endl;
					pFirstSubFunction = new cFunctionValue( 2 );
				break;
				case 3:
					cout<<"pFirstSubFunction = new cFunctionValue( 3 )"<<endl;
					pFirstSubFunction = new cFunctionValue( 3 );
				break;
				case 4:
					cout<<"pFirstSubFunction = new cFunctionValue( 3.3 )"<<endl;
					pFirstSubFunction = new cFunctionValue( 3.3 );
				break;
				case 5:
					cout<<"pFirstSubFunction = new cFunctionValue( -1 )"<<endl;
					pFirstSubFunction = new cFunctionValue( -1 );
				break;
				case 6:
					cout<<"pFirstSubFunction = new cFunctionVariable( pVariable2 )"<<endl;
					pFirstSubFunction = new cFunctionVariable( pVariable2 );
					setCorrectUsedVariables.insert( pVariable2 );
					uiNumberOfVariableSubFunctions++;
				break;
				case 7:
					cout<<"pFirstSubFunction = new cFunctionVariable( pVariable3 )"<<endl;
					pFirstSubFunction = new cFunctionVariable( pVariable3 );
					setCorrectUsedVariables.insert( pVariable3 );
					uiNumberOfVariableSubFunctions++;
				break;
				case 8:
					cout<<"pFirstSubFunction = new cFunctionVariable( pVariable4 )"<<endl;
					pFirstSubFunction = new cFunctionVariable( pVariable4 );
					setCorrectUsedVariables.insert( pVariable4 );
					uiNumberOfVariableSubFunctions++;
				break;
				case 9:
					cout<<"pFirstSubFunction = new cFunctionVariable( pVariable5 )"<<endl;
					pFirstSubFunction = new cFunctionVariable( pVariable5 );
					setCorrectUsedVariables.insert( pVariable5 );
					uiNumberOfVariableSubFunctions++;
				break;
			};//end switch choose condition
			//choose second subfunction
			switch ( rand() % 10 ){
				case 0:
					cout<<"pSecondSubFunction = NULL"<<endl;
					pSecondSubFunction = NULL;
					uiNumberOfNullSubFunctions++;
				break;
				case 1:
					cout<<"pSecondSubFunction = new cFunctionValue( 1 )"<<endl;
					pSecondSubFunction = new cFunctionValue( 1 );
				break;
				case 2:
					cout<<"pSecondSubFunction = new cFunctionValue( 2 )"<<endl;
					pSecondSubFunction = new cFunctionValue( 2 );
				break;
				case 3:
					cout<<"pSecondSubFunction = new cFunctionValue( 3 )"<<endl;
					pSecondSubFunction = new cFunctionValue( 3 );
				break;
				case 4:
					cout<<"pSecondSubFunction = new cFunctionValue( 3.3 )"<<endl;
					pSecondSubFunction = new cFunctionValue( 3.3 );
				break;
				case 5:
					cout<<"pSecondSubFunction = new cFunctionValue( -1 )"<<endl;
					pSecondSubFunction = new cFunctionValue( -1 );
				break;
				case 6:
					cout<<"pSecondSubFunction = new cFunctionVariable( pVariable2 )"<<endl;
					pSecondSubFunction = new cFunctionVariable( pVariable2 );
					setCorrectUsedVariables.insert( pVariable2 );
					uiNumberOfVariableSubFunctions++;
				break;
				case 7:
					cout<<"pSecondSubFunction = new cFunctionVariable( pVariable3 )"<<endl;
					pSecondSubFunction = new cFunctionVariable( pVariable3 );
					setCorrectUsedVariables.insert( pVariable3 );
					uiNumberOfVariableSubFunctions++;
				break;
				case 8:
					cout<<"pSecondSubFunction = new cFunctionVariable( pVariable4 )"<<endl;
					pSecondSubFunction = new cFunctionVariable( pVariable4 );
					setCorrectUsedVariables.insert( pVariable4 );
					uiNumberOfVariableSubFunctions++;
				break;
				case 9:
					cout<<"pSecondSubFunction = new cFunctionVariable( pVariable5 )"<<endl;
					pSecondSubFunction = new cFunctionVariable( pVariable5 );
					setCorrectUsedVariables.insert( pVariable5 );
					uiNumberOfVariableSubFunctions++;
				break;
			};//end switch choose condition
			ulTimeNeed = 4 - uiNumberOfNullSubFunctions;
			if ( pCondition == NULL ){
				ulTimeNeed--;
			}
			
			if ( uiNumberOfVariableSubFunctions != 0 ){
				//correct compressed size
				if ( pDefiningFibElement == &rootFull ){
					ulCompressedSize -= uiNumberOfVariableSubFunctions * 4;
				}else{
					ulCompressedSize -= uiNumberOfVariableSubFunctions * 8;
				}
			}
			if ( uiNumberOfNullSubFunctions != 0 ){
				//correct compressed size
				if ( pDefiningFibElement == &rootFull ){
					//7 bit value domain
					ulCompressedSize -= uiNumberOfNullSubFunctions * (7 + 2);
				}else{//16 bit value domain
					ulCompressedSize -= uiNumberOfNullSubFunctions * (16 + 2);
				}
			}
			
			cout<<"pConditionTest = new pFunctionIfRand( pCondition, "<<
				"pFirstSubFunction, pSecondSubFunction, pSuperiorUnderFunction, pDefiningFibElement );"<<endl;
			pFunctionIfRand = new cFunctionIf( pCondition, pFirstSubFunction,
				pSecondSubFunction, pSuperiorUnderFunction, pDefiningFibElement );
			
		}
	
		//corect bIsValid for subelements
		if ( pFunctionIfRand->getCondition() ){
			bIsValid &= pFunctionIfRand->getCondition()->isValid();
		}else{//no condition -> not valid
			bIsValid = false;
		}
		if ( pFunctionIfRand->getFirstUnderFunction() ){
			bIsValid &= pFunctionIfRand->getFirstUnderFunction()->isValid();
		}else{//no first subfunction -> not valid
			bIsValid = false;
		}
		if ( pFunctionIfRand->getSecondUnderFunction() ){
			bIsValid &= pFunctionIfRand->getSecondUnderFunction()->isValid();
		}else{//no second subfunction -> not valid
			bIsValid = false;
		}
	
		//check the getValue() methode from cFunctionIf
		if ( isEqual( pFunctionIfRand->getValue(),
				getCorrectValue( pFunctionIfRand ) ) ){
		
			cout<<"The function value is correctly "<<
				pFunctionIfRand->getValue() <<" . "<<endl;
		}else{
			cerr<<"Error: The function value is "<<
				pFunctionIfRand->getValue() <<" but should be "<<
				getCorrectValue( pFunctionIfRand )<<"."<<endl;
			iReturn++;
		}
		//check the getDefiningFibElement() methode from cFunctionIf
		if ( pFunctionIfRand->getDefiningFibElement() == pDefiningFibElement ){
		
			cout<<"The function defining Fib-element is correctly "<<
				pFunctionIfRand->getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The function defining Fib-element is "<<
				pFunctionIfRand->getDefiningFibElement() <<
				" but should be "<< pDefiningFibElement <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionIf
		if ( pFunctionIfRand->getSuperiorUnderFunction() == pSuperiorUnderFunction ){
		
			cout<<"The superior function of the function correctly "<<
				pFunctionIfRand->getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior function of the function is "<<
				pFunctionIfRand->getSuperiorUnderFunction() <<
				" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
			iReturn++;
		}
		
		//check the getCondition() methode from cFunctionIf
		if ( bIsPointer ){
			if ( pCondition == pFunctionIfRand->getCondition() ){
			
				cout<<"The condition of the function correctly "<<
					pFunctionIfRand->getCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition of the function is "<<
					pFunctionIfRand->getCondition() <<
					", but should be "<< pCondition <<" ."<<endl;
				iReturn++;
			}
		
		}else{
			if ( pCondition->equal( *(pFunctionIfRand->getCondition()) ) ){
			
				cout<<"The condition of the function is correctly equal to "<<
					pFunctionIfRand->getCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition of the function "<<
					pFunctionIfRand->getCondition() <<
					" is not equal to "<< pCondition <<" ."<<endl;
				iReturn++;
			}
		}
		
		//check the getFirstUnderFunction() methode from cFunctionIf
		if ( bIsPointer ){
			if ( pFirstSubFunction == pFunctionIfRand->getFirstUnderFunction() ){
			
				cout<<"The first subfunction of the function is correctly "<<
					pFunctionIfRand->getFirstUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The first subfunction of the function is "<<
					pFunctionIfRand->getFirstUnderFunction() <<
					", but should be "<< pFirstSubFunction <<" ."<<endl;
				iReturn++;
			}
		}else{
			if ( pFirstSubFunction->equal( *(pFunctionIfRand->getFirstUnderFunction()) ) ){
			
				cout<<"The first subfunction of the function is correctly equal to "<<
					pFunctionIfRand->getFirstUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The first subfunction of the function is "<<
					pFunctionIfRand->getFirstUnderFunction() <<
					" not equal to "<< pFirstSubFunction <<" ."<<endl;
				iReturn++;
			}
		}
		//check the getSecondUnderFunction() methode from cFunctionIf
		if ( bIsPointer ){
			if ( pSecondSubFunction == pFunctionIfRand->getSecondUnderFunction() ){
			
				cout<<"The second subfunction of the function is correctly "<<
					pFunctionIfRand->getSecondUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The second subfunction of the function is "<<
					pFunctionIfRand->getSecondUnderFunction() <<
					", but should be "<< pSecondSubFunction <<" ."<<endl;
				iReturn++;
			}
		}else{
			if ( pSecondSubFunction->equal( *(pFunctionIfRand->getSecondUnderFunction()) ) ){
			
				cout<<"The second subfunction of the function is correctly equal to "<<
					pFunctionIfRand->getSecondUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The second subfunction of the function is "<<
					pFunctionIfRand->getSecondUnderFunction() <<
					" not equal to "<< pSecondSubFunction <<" ."<<endl;
				iReturn++;
			}
		}
		
		//check the isValid() methode from cFunctionIf
		if ( pFunctionIfRand->isValid() == bIsValid ){
		
			cout<<"The function is correctly "<<(bIsValid?"":"not ")<<"valid . "<<endl;
		}else{
			cerr<<"Error: The function is "<<(bIsValid?"not ":"")<<"valid, but should be ."<<endl;
			iReturn++;
		}
		//check the getType() methode from cFunctionIf
		if ( pFunctionIfRand->getType() == getFunctionType() ){
		
			cout<<"The function type is correctly "<<
				getFunctionType()<<". "<<endl;
		}else{
			cerr<<"Error: The type of the function is not "<<
				getFunctionType()<<", but "<<
				pFunctionIfRand->getType() <<" ."<<endl;
			iReturn++;
		}
		//check the getUnderFunctionName() methode from cFunctionIf
		if ( pFunctionIfRand->getUnderFunctionName() == getUnderFunctionName() ){
		
			cout<<"The function name is correctly \""<<
				pFunctionIfRand->getUnderFunctionName() <<"\" . "<<endl;
		}else{
			cerr<<"Error: The name of the function is not \""<<
				getUnderFunctionName()<<"\", but \""<<
				pFunctionIfRand->getUnderFunctionName() <<"\" ."<<endl;
			iReturn++;
		}
		//check the getNumberOfConditions() methode from cFunctionIf
		if ( pFunctionIfRand->getNumberOfUnderFunctions() == 2 ){
		
			cout<<"The function number of subfunctions is correctly "<<
				pFunctionIfRand->getNumberOfUnderFunctions() <<" . "<<endl;
		}else{
			cerr<<"Error: The function number of subfunctions is "<<
				pFunctionIfRand->getNumberOfUnderFunctions() <<" , but should be 2 ."<<endl;
			iReturn++;
		}
		
		//check the getElementType() methode from cFunctionIf
		pTypeOfUnderFunction = pFunctionIfRand->getElementType();
		if ( pTypeOfUnderFunction != NULL ){
			if ( * pTypeOfUnderFunction == typeUnderFunction ){
			
				cout<<"The given back element type for the subfunction is correct. "<<endl;
			}else{
				cerr<<"Error: The given back element type for the subfunction is not correct."<<endl;
				iReturn++;
			}
			delete pTypeOfUnderFunction;
		}else{
			cerr<<"Error: The given back element type for the subfunction is NULL ."<<endl;
			iReturn++;
		}
		//check the getDomain() methode from cFunctionIf
		pRetUnderFunctionDomain = pFunctionIfRand->getDomain();
		if ( pUnderFunctionDomain != NULL ){
			if ( pRetUnderFunctionDomain != NULL ){
				if ( * pRetUnderFunctionDomain == * pUnderFunctionDomain ){
				
					cout<<"The given back domain for the subfunction is correct. "<<endl;
				}else{
					cerr<<"Error: The given back domain for the subfunction is not correct."<<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: The given back domain for the subfunction is NULL ."<<endl;
				iReturn++;
			}
		}else{
			if ( pRetUnderFunctionDomain == NULL ){
			
				cout<<"The given back domain for the subfunction is correctly NULL . "<<endl;
			}else{
				cerr<<"Error: The given back domain for the subfunction is not NULL ."<<endl;
				iReturn++;
			}
		}
		//check the getValueDomain() methode from cFunctionIf
		pRetValueDomain = pFunctionIfRand->getValueDomain();
		if ( pValueDomain != NULL ){
			if ( pRetValueDomain != NULL ){
				if ( * pRetValueDomain == * pValueDomain ){
				
					cout<<"The given back valuedomain for the subfunction is correct. "<<endl;
				}else{
					cerr<<"Error: The given back valuedomain for the subfunction is not correct."<<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: The given back valuedomain for the subfunction is NULL ."<<endl;
				iReturn++;
			}
		}else{
			if ( pRetValueDomain == NULL ){
			
				cout<<"The given back valuedomain for the subfunction is correctly NULL . "<<endl;
			}else{
				cerr<<"Error: The given back valuedomain for the subfunction is not NULL ."<<endl;
				iReturn++;
			}
		}
		//check the getStandardDomain() methode from cFunctionIf
		pRetStandardDomain = pFunctionIfRand->getStandardDomain();
		if ( pStandardDomain != NULL ){
			if ( pRetStandardDomain != NULL ){
				if ( * pRetStandardDomain == * pStandardDomain ){
				
					cout<<"The given back the standarddomain for the subfunction is correct. "<<endl;
				}else{
					cerr<<"Error: The given back the standarddomain domain for the subfunction is not correct."<<endl;
					iReturn++;
				}
				delete pRetStandardDomain;
			}else{
				cerr<<"Error: The given back the standarddomain domain for the subfunction is NULL ."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The given back the standarddomain domain for the subfunction is not NULL ."<<endl;
		}
		//check the getVariableDomain() methode from cFunctionIf
		pRetVariableDomain = pFunctionIfRand->getVariableDomain();
		if ( pVariableDomain != NULL ){
			if ( pRetVariableDomain != NULL ){
				if ( * pRetVariableDomain == * pVariableDomain ){
				
					cout<<"The given back variabledomain for the subfunction is correct. "<<endl;
				}else{
					cerr<<"Error: The given back variabledomain for the subfunction is not correct."<<endl;
					iReturn++;
				}
				delete pRetVariableDomain;
			}else{
				cerr<<"Error: The given back variabledomain for the subfunction is NULL ."<<endl;
				iReturn++;
			}
		}else{
			if ( pRetVariableDomain == NULL ){
			
				cout<<"The given back variabledomain for the subfunction is correctly NULL . "<<endl;
			}else{
				cerr<<"Error: The given back variabledomain for the subfunction is not NULL ."<<endl;
				iReturn++;
				delete pRetVariableDomain;
			}
		}
		
		//check the getTimeNeed() methode from cFunctionIf
		if ( pFunctionIfRand->getTimeNeed() == ulTimeNeed ){
		
			cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
		}else{
			cerr<<"Error: The time needed to evalue the function is "<<
				pFunctionIfRand->getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
			iReturn++;
		}
		//check the getCompressedSize() methode from cFunctionIf
		if ( pFunctionIfRand->getCompressedSize() == ulCompressedSize ){
		
			cout<<"The compressed size of the function is correctly "<<
			ulCompressedSize <<" . "<<endl;
		}else{
			cerr<<"Error: The compressed size of the function is "<<
				pFunctionIfRand->getCompressedSize()<<" ,but should be "<<
				ulCompressedSize <<" . "<<endl;
			iReturn++;
		}
		
		//check the getCompressedSize() methode from cFunctionIf
		if ( ! pFunctionIfRand->isUsedVariable( pVariable1 ) ){
		
			cout<<"The variable pVariable1 isn't used in the function. "<<endl;
		}else{
			cerr<<"Error: The variable pVariable1 is used in the function. "<<endl;
			iReturn++;
		}
		//check the getUsedVariables() methode from cFunctionIf
		setUsedVariables = pFunctionIfRand->getUsedVariables();
		if ( setUsedVariables == setCorrectUsedVariables ){
		
			cout<<"No used variables are given back from the function. "<<endl;
		}else{
			cerr<<"Error: Used variables are given back from the function. "<<endl;
			iReturn++;
		}

		
		if ( pFunctionIfRand ){
			delete pFunctionIfRand;
			pFunctionIfRand = NULL;
		}
	}//for random test

	if ( pStandardDomain ){
		delete pStandardDomain;
	}
	if ( pVariableDomain ){
		delete pVariableDomain;
	}

	return iReturn;
}



/**
 * This function tests the comparison methods of two given functions, which are
 * equal.
 *
 * @param function1 the first Fib-object to compare
 * @param szNameObject1 the name of the first Fib-object to compare
 * @param function2 the secound Fib-object to compare to
 * @param szNameObject2 the name of the secound Fib-object to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoEqualObjects( const cUnderFunction &function1, const string &szNameObject1,
	const cUnderFunction &function2, const string &szNameObject2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( function1.equal( function2 ) ){
	
		cout<<"The "<<szNameObject1<<" is equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is not equal to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}
	//check operator== for cUnderFunction
	if ( function1 == function2 ){
	
		cout<<"The "<<szNameObject1<<" is equal (operator==) to "<<
			szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is not equal (operator==) to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}
	//check operator!= for cUnderFunction
	if ( ! (function1 != function2) ){
	
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
 * This function tests the comparison methods of two given functions, which are
 * not equal.
 *
 * @param function1 the first Fib-object to compare
 * @param szNameObject1 the name of the first Fib-object to compare
 * @param function2 the secound Fib-object to compare to
 * @param szNameObject2 the name of the secound Fib-object to compare
 * @return the number of errors occured in the test
 */
int testCompareTwoNotEqualObjects( const cUnderFunction &function1, const string &szNameObject1,
	const cUnderFunction &function2, const string &szNameObject2 ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( ! function1.equal( function2 ) ){
	
		cout<<"The "<<szNameObject1<<" is not equal to "<<szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is equal to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}
	//check operator== for cUnderFunction
	if ( ! (function1 == function2) ){
	
		cout<<"The "<<szNameObject1<<" is not equal (operator==) to "<<
			szNameObject2<<". "<<endl;
	}else{
		cerr<<"Error: The "<<szNameObject1<<" is equal (operator==) to "<<
			szNameObject2<<"."<<endl;
		iReturn++;
	}

	//check operator!= for cUnderFunction
	if ( function1 != function2 ){
	
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
 * This function tests equal method of the cFunctionIf class.
 *
 * methods tested:
 * 	- bool equal( const cFibElement & fibObject ) const
 * 	- bool operator==( const cUnderFunction &function ) const;
 * 	- bool operator!=( const cUnderFunction &function ) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testEqual( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing comparison methods for function"<<endl;

	cout<<endl<<"Creating functions objects to compare: "<<endl<<endl;

	//simple function
	cout<<"cFunctionIf functionIfNull1( NULL, NULL, NULL );"<<endl;
	cFunctionIf functionIfNull1( NULL, NULL, NULL );

	cout<<"cFunctionIf functionIfNull2( NULL, NULL, NULL );"<<endl;
	cFunctionIf functionIfNull2( NULL, NULL, NULL );


	//with subcondition
	cout<<"cFunctionIf functionIfTrueNULL( new cConditionTrue(), NULL, NULL );"<<endl;
	cFunctionIf functionIfTrueNULL( new cConditionTrue(), NULL, NULL );

	cout<<"cFunctionIf functionIfFalseNULL( new cConditionFalse(), NULL, NULL );"<<endl;
	cFunctionIf functionIfFalseNULL( new cConditionFalse(), NULL, NULL );

	//with subfunctions
	cout<<"cFunctionIf functionIfNULLV1NULL( NULL, new cFunctionValue( 1 ), NULL );"<<endl;
	cFunctionIf functionIfNULLV1NULL( NULL, new cFunctionValue( 1 ), NULL );

	cout<<"cFunctionIf functionIfNULLV1p1NULL( NULL, new cFunctionValue( 1.1 ), NULL );"<<endl;
	cFunctionIf functionIfNULLV1p1NULL( NULL, new cFunctionValue( 1.1 ), NULL );

	cout<<"cFunctionIf functionIfNULLNULLV1( NULL, NULL, new cFunctionValue( 1 ) );"<<endl;
	cFunctionIf functionIfNULLNULLV1( NULL, NULL, new cFunctionValue( 1 ) );

	cout<<"cFunctionIf functionIfNULLNULLVm1( NULL, NULL, new cFunctionValue( -1 ) );"<<endl;
	cFunctionIf functionIfNULLNULLVm1( NULL, NULL, new cFunctionValue( -1 ) );

	cout<<"cFunctionIf functionIfNULLV1V1( NULL, new cFunctionValue( 1 ), new cFunctionValue( 1 ) );"<<endl;
	cFunctionIf functionIfNULLV1V1( NULL, new cFunctionValue( 1 ), new cFunctionValue( 1 ) );

	cout<<"cFunctionIf functionIfNULLV1V2( NULL, new cFunctionValue( 1 ), new cFunctionValue( 2 ) );"<<endl;
	cFunctionIf functionIfNULLV1V2( NULL, new cFunctionValue( 1 ), new cFunctionValue( 2 ) );

	cout<<"cFunctionIf functionIfNULLVm1V1( NULL, new cFunctionValue( -1 ), new cFunctionValue( 1 ) );"<<endl;
	cFunctionIf functionIfNULLVm1V1( NULL, new cFunctionValue( -1 ), new cFunctionValue( 1 ) );


	//with all subelements
	cout<<"cFunctionIf functionIfTrueV1NULL( new cConditionTrue(), new cFunctionValue( 1 ), NULL );"<<endl;
	cFunctionIf functionIfTrueV1NULL( new cConditionTrue(), new cFunctionValue( 1 ), NULL );

	cout<<"cFunctionIf functionIfTrueV1p1NULL( new cConditionTrue(), new cFunctionValue( 1.1 ), NULL );"<<endl;
	cFunctionIf functionIfTrueV1p1NULL( new cConditionTrue(), new cFunctionValue( 1.1 ), NULL );

	cout<<"cFunctionIf functionIfTrueNULLV1( new cConditionTrue(), NULL, new cFunctionValue( 1 ) );"<<endl;
	cFunctionIf functionIfTrueNULLV1( new cConditionTrue(), NULL, new cFunctionValue( 1 ) );

	cout<<"cFunctionIf functionIfTrueNULLVm1( new cConditionTrue(), NULL, new cFunctionValue( -1 ) );"<<endl;
	cFunctionIf functionIfTrueNULLVm1( new cConditionTrue(), NULL, new cFunctionValue( -1 ) );

	cout<<"cFunctionIf functionIfTrueV1V1( new cConditionTrue(), new cFunctionValue( 1 ), new cFunctionValue( 1 ) );"<<endl;
	cFunctionIf functionIfTrueV1V1( new cConditionTrue(), new cFunctionValue( 1 ), new cFunctionValue( 1 ) );

	cout<<"cFunctionIf functionIfTrueV1V2( new cConditionTrue(), new cFunctionValue( 1 ), new cFunctionValue( 2 ) );"<<endl;
	cFunctionIf functionIfTrueV1V2( new cConditionTrue(), new cFunctionValue( 1 ), new cFunctionValue( 2 ) );

	cout<<"cFunctionIf functionIfTrueVm1V1( new cConditionTrue(), new cFunctionValue( -1 ), new cFunctionValue( 1 ) );"<<endl;
	cFunctionIf functionIfTrueVm1V1( new cConditionTrue(), new cFunctionValue( -1 ), new cFunctionValue( 1 ) );


	cout<<"cFunctionIf functionIfFalseV1NULL( new cConditionFalse(), new cFunctionValue( 1 ), NULL );"<<endl;
	cFunctionIf functionIfFalseV1NULL( new cConditionFalse(), new cFunctionValue( 1 ), NULL );

	cout<<"cFunctionIf functionIfFalseV1p1NULL( new cConditionFalse(), new cFunctionValue( 1.1 ), NULL );"<<endl;
	cFunctionIf functionIfFalseV1p1NULL( new cConditionFalse(), new cFunctionValue( 1.1 ), NULL );

	cout<<"cFunctionIf functionIfFalseNULLV1( new cConditionFalse(), NULL, new cFunctionValue( 1 ) );"<<endl;
	cFunctionIf functionIfFalseNULLV1( new cConditionFalse(), NULL, new cFunctionValue( 1 ) );

	cout<<"cFunctionIf functionIfFalseNULLVm1( new cConditionFalse(), NULL, new cFunctionValue( -1 ) );"<<endl;
	cFunctionIf functionIfFalseNULLVm1( new cConditionFalse(), NULL, new cFunctionValue( -1 ) );

	cout<<"cFunctionIf functionIfFalseV1V1( new cConditionFalse(), new cFunctionValue( 1 ), new cFunctionValue( 1 ) );"<<endl;
	cFunctionIf functionIfFalseV1V1( new cConditionFalse(), new cFunctionValue( 1 ), new cFunctionValue( 1 ) );

	cout<<"cFunctionIf functionIfFalseV1V2( new cConditionFalse(), new cFunctionValue( 1 ), new cFunctionValue( 2 ) );"<<endl;
	cFunctionIf functionIfFalseV1V2( new cConditionFalse(), new cFunctionValue( 1 ), new cFunctionValue( 2 ) );

	cout<<"cFunctionIf functionIfFalseVm1V1( new cConditionFalse(), new cFunctionValue( -1 ), new cFunctionValue( 1 ) );"<<endl;
	cFunctionIf functionIfFalseVm1V1( new cConditionFalse(), new cFunctionValue( -1 ), new cFunctionValue( 1 ) );


	
	//function with defining Fib-element
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	cout<<"cFunctionIf functionDefFE( NULL, NULL, NULL, NULL, &rootSimple1 );"<<endl;
	cFunctionIf functionDefFE( NULL, NULL, NULL, NULL, &rootSimple1 );

	//function with superior function
	cout<<"cFunctionAbs functionAbsSup( NULL );"<<endl;
	cFunctionAbs functionAbsSup( NULL );
	cout<<"cFunctionIf functionSup( NULL, NULL, NULL, & functionAbsSup );"<<endl;
	cFunctionIf functionSup( NULL, NULL, NULL, & functionAbsSup );

	//function with domains set
	cout<<"root1 rootSimple1;"<<endl;
	cRoot root1;
	
	cout<<"cTypeVariable testTypeVariable;"<<endl;
	cTypeVariable testTypeVariable;
	cout<<"cDomainNaturalNumberBit domainNat8( 8 );"<<endl;
	cDomainNaturalNumberBit domainNat8( 8 );

	cout<<"root1.getDomains()->addDomain( testTypeVariable, &domainNat8 );"<<endl;
	root1.getDomains()->addDomain( testTypeVariable, &domainNat8 );

	cout<<"cFunctionIf functionDom( NULL, NULL, NULL, NULL, &root1 );"<<endl;
	cFunctionIf functionDom( NULL, NULL, NULL, NULL, &root1 );

	//function with defining Fib-element and superior function
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cFunctionAbs functionAbsSup2( NULL );"<<endl;
	cFunctionAbs functionAbsSup2( NULL );
	cout<<"cFunctionIf functionDefFeSc( NULL, NULL, NULL, & functionAbsSup2, &rootSimple2 );"<<endl;
	cFunctionIf functionDefFeSc( NULL, NULL, NULL, & functionAbsSup2, &rootSimple2 );

	//function with all elements set
	cout<<"cRoot rootSimple3;"<<endl;
	cRoot rootSimple3;
	cout<<"cFunctionAbs functionAbsSup3( NULL );"<<endl;
	cFunctionAbs functionAbsSup3( NULL );
	cout<<"cFunctionIf functionFull( new cConditionTrue(), new cFunctionValue( 1 ), new cFunctionValue( 1 ), & functionAbsSup3, &rootSimple3 );"<<endl;
	cFunctionIf functionFull( new cConditionTrue(), new cFunctionValue( 1 ), new cFunctionValue( 1 ), & functionAbsSup3, &rootSimple3 );


	//functions of other typs
	cout<<"cFunctionValue functionValueV1( 1 );"<<endl;
	cFunctionValue functionValueV1( 1 );
	
	cout<<"cFunctionValue subFunValueVm1( -1 );"<<endl;
	cFunctionValue subFunValueVm1( -1 );
	cout<<"cFunctionAbs functionAbs( &subFunValueVm1 );"<<endl;
	cFunctionAbs functionAbs( &subFunValueVm1 );


	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with functionIfNull1
	cUnderFunction * actualObject = &functionIfNull1;
	string szActualObjectName = "functionIfNull1";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfNull2
	actualObject = &functionIfNull2;
	szActualObjectName = "functionIfNull2";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfTrueNULL
	actualObject = &functionIfTrueNULL;
	szActualObjectName = "functionIfTrueNULL";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfFalseNULL
	actualObject = &functionIfFalseNULL;
	szActualObjectName = "functionIfFalseNULL";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfNULLV1NULL
	actualObject = &functionIfNULLV1NULL;
	szActualObjectName = "functionIfNULLV1NULL";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfNULLV1p1NULL
	actualObject = &functionIfNULLV1p1NULL;
	szActualObjectName = "functionIfNULLV1p1NULL";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfNULLNULLV1
	actualObject = &functionIfNULLNULLV1;
	szActualObjectName = "functionIfNULLNULLV1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfNULLNULLVm1
	actualObject = &functionIfNULLNULLVm1;
	szActualObjectName = "functionIfNULLNULLVm1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfNULLV1V1
	actualObject = &functionIfNULLV1V1;
	szActualObjectName = "functionIfNULLV1V1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfNULLV1V2
	actualObject = &functionIfNULLV1V2;
	szActualObjectName = "functionIfNULLV1V2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfNULLVm1V1
	actualObject = &functionIfNULLVm1V1;
	szActualObjectName = "functionIfNULLVm1V1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfTrueV1NULL
	actualObject = &functionIfTrueV1NULL;
	szActualObjectName = "functionIfTrueV1NULL";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfTrueV1p1NULL
	actualObject = &functionIfTrueV1p1NULL;
	szActualObjectName = "functionIfTrueV1p1NULL";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfTrueNULLV1
	actualObject = &functionIfTrueNULLV1;
	szActualObjectName = "functionIfTrueNULLV1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfTrueNULLVm1
	actualObject = &functionIfTrueNULLVm1;
	szActualObjectName = "functionIfTrueNULLVm1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfTrueV1V1
	actualObject = &functionIfTrueV1V1;
	szActualObjectName = "functionIfTrueV1V1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfTrueVm1V1
	actualObject = &functionIfTrueVm1V1;
	szActualObjectName = "functionIfTrueVm1V1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfFalseV1NULL
	actualObject = &functionIfFalseV1NULL;
	szActualObjectName = "functionIfFalseV1NULL";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfFalseV1p1NULL
	actualObject = &functionIfFalseV1p1NULL;
	szActualObjectName = "functionIfFalseV1p1NULL";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfFalseNULLV1
	actualObject = &functionIfFalseNULLV1;
	szActualObjectName = "functionIfFalseNULLV1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfFalseNULLVm1
	actualObject = &functionIfFalseNULLVm1;
	szActualObjectName = "functionIfFalseNULLVm1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfFalseV1V1
	actualObject = &functionIfFalseV1V1;
	szActualObjectName = "functionIfFalseV1V1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfFalseV1V2
	actualObject = &functionIfFalseV1V2;
	szActualObjectName = "functionIfFalseV1V2";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionIfFalseVm1V1
	actualObject = &functionIfFalseVm1V1;
	szActualObjectName = "functionIfFalseVm1V1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionDefFE
	actualObject = &functionDefFE;
	szActualObjectName = "functionDefFE";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionSup
	actualObject = &functionSup;
	szActualObjectName = "functionSup";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionDom
	actualObject = &functionDom;
	szActualObjectName = "functionDom";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionDefFeSc
	actualObject = &functionDefFeSc;
	szActualObjectName = "functionDefFeSc";
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionFull
	actualObject = &functionFull;
	szActualObjectName = "functionFull";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionValueV1
	actualObject = &functionValueV1;
	szActualObjectName = "functionValueV1";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );

	//compare with functionAbs
	actualObject = &functionAbs;
	szActualObjectName = "functionAbs";
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull1, "functionIfNull1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNull2, "functionIfNull2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULL, "functionIfTrueNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULL, "functionIfFalseNULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1NULL, "functionIfNULLV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1p1NULL, "functionIfNULLV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLV1, "functionIfNULLNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLNULLVm1, "functionIfNULLNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V1, "functionIfNULLV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLV1V2, "functionIfNULLV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfNULLVm1V1, "functionIfNULLVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1NULL, "functionIfTrueV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1p1NULL, "functionIfTrueV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLV1, "functionIfTrueNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueNULLVm1, "functionIfTrueNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueV1V1, "functionIfTrueV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfTrueVm1V1, "functionIfTrueVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1NULL, "functionIfFalseV1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1p1NULL, "functionIfFalseV1p1NULL" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLV1, "functionIfFalseNULLV1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseNULLVm1, "functionIfFalseNULLVm1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V1, "functionIfFalseV1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseV1V2, "functionIfFalseV1V2" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionIfFalseVm1V1, "functionIfFalseVm1V1" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFE, "functionDefFE" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionSup, "functionSup" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDom, "functionDom" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionDefFeSc, "functionDefFeSc" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionFull, "functionFull" );
	iReturn += testCompareTwoNotEqualObjects( *actualObject, szActualObjectName, functionValueV1, "functionValueV1" );
	iReturn += testCompareTwoEqualObjects( *actualObject, szActualObjectName, functionAbs, "functionAbs" );


	return iReturn;
}



/**
 * This function tests if the given function is not conected to superior
 * functions or Fib-elements.
 *
 * @param functionObject1 the function to check
 * @return the number of errors occured in the test
 */
int testNotConnectedUnderFunction( const cUnderFunction & functionObject1 ){
	
	int iReturn=0;//returnvalue of the test; the number of occured Errors
	
	//check the getNextFibElement() methode
	if ( functionObject1.getSuperiorUnderFunction() == NULL ){
	
		cout<<"The superior function pointer for the function element is correctly NULL . "<<endl;
	}else{
		cerr<<"Error: The superior function pointer for the function element is not NULL, but "<<
			functionObject1.getSuperiorUnderFunction() <<" ."<<endl;
		iReturn++;
	}
	
	//check the getDefiningFibElement() methode
	if ( functionObject1.getDefiningFibElement() == NULL ){
	
		cout<<"The defining Fib-element pointer for the function is correctly NULL. "<<endl;
	}else{
		cerr<<"Error: The defining Fib-element pointer for the function is not NULL."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the falues of an subfunction of a function.
 *
 *
 * @param pUnderfunction a pointer to the subfunction to test
 * @param pUnderfunctionOriginal a pointer to the subfunction which
 * 	should be equal to the subfunction to test (but not the same object)
 * @param pSuperiorUnderFunction the defining superior function the
 * 	subfunction to test should have
 * @param pDefiningFibElement the defining fib -element the
 * 	subfunction to test should have
 * @return the number of erros occured in the test
 */
int checkUnderFunction( cUnderFunction * pUnderfunction,
	cUnderFunction * pUnderfunctionOriginal,
	cUnderFunction * pSuperiorUnderFunction, cFibElement * pDefiningFibElement ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( pUnderfunction != pUnderfunctionOriginal ){
	
		cout<<"   The subfunction dosn't points to the object set as the subfunction . "<<endl;
	}else{
		cerr<<"   Error: The subfunction points to the object set as the subfunction."<<endl;
		iReturn++;
	}
	if ( pUnderfunction == NULL ){
		cerr<<"   Error: The subfunction to check is NULL."<<endl;
		iReturn++;
		return iReturn;
	}
	if ( pUnderfunction == NULL ){
		cerr<<"   Error: The subfunction to check against is NULL."<<endl;
		iReturn++;
		return iReturn;
	}
	
	if ( *pUnderfunction == *pUnderfunctionOriginal ){
	
		cout<<"   The subfunction is equal to the subfunction set as the subfunction . "<<endl;
	}else{
		cerr<<"   Error: The subfunction isn't equal to the subfunction set as the subfunction."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
	if ( pUnderfunction->getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"   The superior subfunction of the subfunction correctly "<<
			pUnderfunction->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"   Error: The superior subfunction of the subfunction is "<<
			pUnderfunction->getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionTwoValue
	if ( pUnderfunction->getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"   The subfunction defining fib -element is correctly "<<
			pUnderfunction->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"   Error: The subfunction defining fib -element is "<<
			pUnderfunction->getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This function tests the copy methods and copyconstructor of the cFunctionIf class.
 *
 * methods tested:
 * 	- cUnderFunction( const cUnderFunction & function, cUnderFunction * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- cUnderFunction * clone( cUnderFunction * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testCopy( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a simple cFunctionIf"<<endl;

	cout<<"cFunctionIf functionIf1( NULL, NULL, NULL );"<<endl;
	cFunctionIf functionIf1( NULL, NULL, NULL );

	cout<<"cFunctionIf functionIf1CopyConstruct( functionIf1 );"<<endl;
	cFunctionIf functionIf1CopyConstruct( functionIf1 );

	iReturn += testCompareTwoEqualObjects( functionIf1CopyConstruct, "functionIf1CopyConstruct", functionIf1, "functionIf1" );
	iReturn += testNotConnectedUnderFunction( functionIf1CopyConstruct );

	cout<<"cUnderFunction * pUnderFunctions1Clone = functionIf1CopyConstruct.clone();"<<endl;
	cUnderFunction * pUnderFunctions1Clone = functionIf1CopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pUnderFunctions1Clone, "pUnderFunctions1Clone", functionIf1, "functionIf1" );
	iReturn += testNotConnectedUnderFunction( *pUnderFunctions1Clone );
	delete pUnderFunctions1Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionIf with a subfunction, superior function and defining Fib-element"<<endl;
	
	//function with defining Fib-element and superior function
	cout<<"cRoot rootSimple;"<<endl;
	cRoot rootSimple;
	cout<<"cFunctionIf functionSup( NULL, NULL, NULL );"<<endl;
	cFunctionIf functionSup( NULL, NULL, NULL );
	cout<<"cConditionFalse subConditionFalse;"<<endl;
	cConditionFalse subConditionFalse;
	cout<<"cFunctionValue subFunValue1( 1 );"<<endl;
	cFunctionValue subFunValue1( 1 );
	cout<<"cFunctionValue subFunValue2( 2 );"<<endl;
	cFunctionValue subFunValue2( 2 );
	cout<<"cFunctionIf functionDefFeSc( subConditionFalse, subFunValue1, subFunValue2, & functionSup, &rootSimple );"<<endl;
	cFunctionIf functionDefFeSc( subConditionFalse, subFunValue1, subFunValue2, & functionSup, &rootSimple );

	cout<<"cFunctionIf functionDefFeScCopyConstruct( functionDefFeSc );"<<endl;
	cFunctionIf functionDefFeScCopyConstruct( functionDefFeSc );

	iReturn += testCompareTwoEqualObjects( functionDefFeScCopyConstruct, "functionDefFeScCopyConstruct", functionDefFeSc, "functionDefFeSc" );
	//check the getDefiningFibElement() methode from cFunctionIf
	if ( functionDefFeScCopyConstruct.getDefiningFibElement() == &rootSimple ){
	
		cout<<"The function defining Fib-element is correctly "<<
			functionDefFeScCopyConstruct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The function defining Fib-element is "<<
			functionDefFeScCopyConstruct.getDefiningFibElement() <<" but should be rootSimple ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionIf
	if ( functionDefFeScCopyConstruct.getSuperiorUnderFunction() == NULL ){
	
		cout<<"The superior function of the function correctly "<<
			functionDefFeScCopyConstruct.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior function of the function is "<<
			functionDefFeScCopyConstruct.getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	
	cout<<"cUnderFunction * pConditionDefFeUfClone = functionDefFeScCopyConstruct.clone();"<<endl;
	cUnderFunction * pConditionDefFeUfClone = functionDefFeScCopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pConditionDefFeUfClone, "pConditionDefFeUfClone", functionDefFeSc, "functionDefFeSc" );
	//check the getDefiningFibElement() methode from cFunctionIf
	if ( pConditionDefFeUfClone->getDefiningFibElement() == &rootSimple ){
	
		cout<<"The function defining Fib-element is correctly "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The function defining Fib-element is "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" but should be rootSimple ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionIf
	if ( pConditionDefFeUfClone->getSuperiorUnderFunction() == NULL ){
	
		cout<<"The superior function of the function correctly "<<
			pConditionDefFeUfClone->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior function of the function is "<<
			pConditionDefFeUfClone->getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	delete pConditionDefFeUfClone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionIf with a superior function and defining Fib-element which will be changed"<<endl;

	//function with defining Fib-element and superior function
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cFunctionIf functionSup2( NULL, NULL, NULL );"<<endl;
	cFunctionIf functionSup2( NULL, NULL, NULL );

	cout<<"cFunctionIf functionDefFeScCopy2Construct( functionDefFeSc, &functionSup2, &rootSimple2 );"<<endl;
	cFunctionIf functionDefFeScCopy2Construct( functionDefFeSc, &functionSup2, &rootSimple2 );

	iReturn += testCompareTwoEqualObjects( functionDefFeScCopy2Construct, "functionDefFeScCopy2Construct", functionDefFeSc, "functionDefFeSc" );
	//check the getDefiningFibElement() methode from cFunctionIf
	if ( functionDefFeScCopy2Construct.getDefiningFibElement() == &rootSimple2 ){
	
		cout<<"The function defining Fib-element is correctly "<<
			functionDefFeScCopy2Construct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The function defining Fib-element is "<<
			functionDefFeScCopy2Construct.getDefiningFibElement() <<" but should be rootSimple2 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionIf
	if ( functionDefFeScCopy2Construct.getSuperiorUnderFunction() == &functionSup2 ){
	
		cout<<"The superior function of the function correctly "<<
			functionDefFeScCopy2Construct.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior function of the function is "<<
			functionDefFeScCopy2Construct.getSuperiorUnderFunction() <<
			" but should be functionSup2 ."<<endl;
		iReturn++;
	}
	
	cout<<"pConditionDefFeUfClone = functionDefFeScCopyConstruct.clone( &functionSup2, &rootSimple2 );"<<endl;
	pConditionDefFeUfClone = functionDefFeScCopyConstruct.clone( &functionSup2, &rootSimple2 );

	iReturn += testCompareTwoEqualObjects( *pConditionDefFeUfClone, "pConditionDefFeUfClone", functionDefFeSc, "functionDefFeSc" );
	//check the getDefiningFibElement() methode from cFunctionIf
	if ( pConditionDefFeUfClone->getDefiningFibElement() == &rootSimple2 ){
	
		cout<<"The function defining Fib-element is correctly "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The function defining Fib-element is "<<
			pConditionDefFeUfClone->getDefiningFibElement() <<" but should be rootSimple2 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionIf
	if ( pConditionDefFeUfClone->getSuperiorUnderFunction() == &functionSup2 ){
	
		cout<<"The superior function of the function correctly "<<
			pConditionDefFeUfClone->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior function of the function is "<<
			pConditionDefFeUfClone->getSuperiorUnderFunction() <<
			" but should be functionSup2 ."<<endl;
		iReturn++;
	}
	delete pConditionDefFeUfClone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionIf with different subelements"<<endl;
	
	//function with defining Fib-element and superior function
	cout<<"cRoot rootSimpleTrueFalse;"<<endl;
	cRoot rootSimpleTrueFalse;
	cout<<"cFunctionIf functionSup2( NULL, NULL, NULL );"<<endl;
	cFunctionIf functionSu2p( NULL, NULL, NULL );
	cout<<"cConditionTrue subConditionTrue;"<<endl;
	cConditionTrue subConditionTrue;
	cout<<"cFunctionIf functionTrueFalse( subConditionTrue, subFunValue2, subFunValue1, & functionSup2, &rootSimpleTrueFalse );"<<endl;
	cFunctionIf functionTrueFalse( subConditionTrue, subFunValue2, subFunValue1, & functionSup2, &rootSimpleTrueFalse );

	cout<<"cFunctionIf functionTrueFalseCopyConstruct( functionTrueFalse );"<<endl;
	cFunctionIf functionTrueFalseCopyConstruct( functionTrueFalse );

	iReturn += testCompareTwoEqualObjects( functionTrueFalseCopyConstruct, "functionTrueFalseCopyConstruct", functionTrueFalse, "functionTrueFalse" );
	//check the getDefiningFibElement() methode from cFunctionIf
	if ( functionTrueFalseCopyConstruct.getDefiningFibElement() == &rootSimpleTrueFalse ){
	
		cout<<"The function defining Fib-element is correctly "<<
			functionTrueFalseCopyConstruct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The function defining Fib-element is "<<
			functionTrueFalseCopyConstruct.getDefiningFibElement() <<" but should be rootSimpleTrueFalse ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionIf
	if ( functionTrueFalseCopyConstruct.getSuperiorUnderFunction() == NULL ){
	
		cout<<"The superior function of the function correctly "<<
			functionTrueFalseCopyConstruct.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior function of the function is "<<
			functionTrueFalseCopyConstruct.getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	
	cout<<"cUnderFunction * pConditionTrueFalse = functionTrueFalseCopyConstruct.clone();"<<endl;
	cUnderFunction * pConditionTrueFalse = functionTrueFalseCopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pConditionTrueFalse, "pConditionTrueFalse", functionTrueFalse, "functionTrueFalse" );
	//check the getDefiningFibElement() methode from cFunctionIf
	if ( pConditionTrueFalse->getDefiningFibElement() == &rootSimpleTrueFalse ){
	
		cout<<"The function defining Fib-element is correctly "<<
			pConditionTrueFalse->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The function defining Fib-element is "<<
			pConditionTrueFalse->getDefiningFibElement() <<" but should be rootSimpleTrueFalse ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionIf
	if ( pConditionTrueFalse->getSuperiorUnderFunction() == NULL ){
	
		cout<<"The superior function of the function correctly "<<
			pConditionTrueFalse->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior function of the function is "<<
			pConditionTrueFalse->getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	delete pConditionTrueFalse;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionIf with a NULL subcondition and subfunctions"<<endl;
	
	//function with defining Fib-element and superior function
	cout<<"cRoot rootSimple3;"<<endl;
	cRoot rootSimple3;
	cout<<"cFunctionAbs functionSup3( NULL );"<<endl;
	cFunctionAbs functionSup3( NULL );
	cout<<"cFunctionIf functionNullFalse( NULL, new cFunctionValue( 3.3 ), new cFunctionValue( -7 ), & functionSup3, &rootSimple3 );"<<endl;
	cFunctionIf functionNullFalse( NULL, new cFunctionValue( 3.3 ), new cFunctionValue( -7 ), & functionSup3, &rootSimple3 );

	cout<<"cFunctionIf functionNullFalseCopyConstruct( functionNullFalse );"<<endl;
	cFunctionIf functionNullFalseCopyConstruct( functionNullFalse );

	iReturn += testCompareTwoEqualObjects( functionNullFalseCopyConstruct, "functionNullFalseCopyConstruct", functionNullFalse, "functionNullFalse" );
	//check the getDefiningFibElement() methode from cFunctionIf
	if ( functionNullFalseCopyConstruct.getDefiningFibElement() == &rootSimple3 ){
	
		cout<<"The function defining Fib-element is correctly "<<
			functionNullFalseCopyConstruct.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The function defining Fib-element is "<<
			functionNullFalseCopyConstruct.getDefiningFibElement() <<" but should be rootSimple3 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionIf
	if ( functionNullFalseCopyConstruct.getSuperiorUnderFunction() == NULL ){
	
		cout<<"The superior function of the function correctly "<<
			functionNullFalseCopyConstruct.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior function of the function is "<<
			functionNullFalseCopyConstruct.getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	
	cout<<"cUnderFunction * pConditionNullFalse = functionNullFalseCopyConstruct.clone();"<<endl;
	cUnderFunction * pConditionNullFalse = functionNullFalseCopyConstruct.clone();

	iReturn += testCompareTwoEqualObjects( *pConditionNullFalse, "pConditionNullFalse", functionNullFalse, "functionNullFalse" );
	//check the getDefiningFibElement() methode from cFunctionIf
	if ( pConditionNullFalse->getDefiningFibElement() == &rootSimple3 ){
	
		cout<<"The function defining Fib-element is correctly "<<
			pConditionNullFalse->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The function defining Fib-element is "<<
			pConditionNullFalse->getDefiningFibElement() <<" but should be rootSimple3 ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionIf
	if ( pConditionNullFalse->getSuperiorUnderFunction() == NULL ){
	
		cout<<"The superior function of the function correctly "<<
			pConditionNullFalse->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior function of the function is "<<
			pConditionNullFalse->getSuperiorUnderFunction() <<
			" but should be NULL ."<<endl;
		iReturn++;
	}
	delete pConditionNullFalse;


	return iReturn;
}



/**
 * This function tests a in the xml -format stored cFunctionIf.
 * The function of the cFunctionIf should be a value function
 * ( cFunctionIf ).
 *
 * @param szFilename the name of the file wher the cFunctionIf is stored
 * @param ucSubCondition1 if the first subfunction is a NULL pointer (=0), a
 * 	cConditionTrue (=1) or cConditionFalse (=2)
 * @param ucSubFun1Value the value of the first value subfunction
 * @param ucSubFun1Value the value of the second value subfunction
 * @return the number of errors occured in the test
 */
int testXmlFunctionValue( const string szFilename, unsigned char ucSubCondition1=0,
			double dSubFun1Value=0, double dSubFun2Value=0 ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cFunctionIf:"<<endl;
	
	TiXmlDocument xmlDocFunctionIf( szFilename );
	bool loadOkay = xmlDocFunctionIf.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocFunctionIf );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();
		
		const string szUnderFunctionsElementName = getUnderFunctionName();
		if ( szElementName == szUnderFunctionsElementName ){
			cout<<"The root element is correctly named \""<< szUnderFunctionsElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szUnderFunctionsElementName <<"\"."<<endl;
			iReturn++;
		}
		
	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}

	//check the subfunctions
	xmlHandleRoot = TiXmlHandle( pXmlElement );
	pXmlElement = xmlHandleRoot.FirstChild().Element();
	
	//check the subfunctions
	if ( pXmlElement ) {
		
		string szElementName = pXmlElement->Value();
		const string szSubfunctionElementName = ((ucSubCondition1==1)?"true":"false");
		if ( szElementName == szSubfunctionElementName ){
			cout<<"The subfunction is correctly named \""<< szSubfunctionElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the subfunction is "<< szElementName <<" and not \""<< szSubfunctionElementName <<"\"."<<endl;
			iReturn++;
		}
		
		
		pXmlElement = pXmlElement->NextSiblingElement();
		//check the first subfunction
		const string szFunctionValueElementName = "value";
		if ( pXmlElement ) {
			string szElementName = pXmlElement->Value();
			
			if ( szElementName == szFunctionValueElementName ){
				cout<<"The root element is correctly named \""<< szFunctionValueElementName <<"\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szFunctionValueElementName <<"\"."<<endl;
				iReturn++;
			}
			
			const char * pcValue = pXmlElement->GetText();
			cout<<"The value of the subfunction is: "<< pcValue <<endl;
			//converting value to double
			double dXmlValue;
			int iReadValues = sscanf( pcValue, "%lf", & dXmlValue );
			if ( iReadValues != 0){
				if ( dXmlValue == dSubFun1Value ){
					cout<<"The value of the first subfunction is correct."<<endl;
				}else{
					cerr<<"Error: The value of the first subfunction should be : "<<
						dSubFun1Value<<", but is "<<dXmlValue<<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: The element text is not a number."<<endl;
				iReturn++;
			}
	
		}else{// pXmlElement == NULL ->no root handle
			cerr<<"Error: No first subfunction handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
			return iReturn;
		}
	
		//check the second subfunction
		pXmlElement = pXmlElement->NextSiblingElement();
		if ( pXmlElement ){
			string szElementName = pXmlElement->Value();
			
			if ( szElementName == szFunctionValueElementName ){
				cout<<"The root element is correctly named \""<< szFunctionValueElementName <<"\". "<<endl;
			
			}else{
				cerr<<"Error: The name of the root element is "<< szElementName <<" and not \""<< szFunctionValueElementName <<"\"."<<endl;
				iReturn++;
			}
			
			const char * pcValue = pXmlElement->GetText();
			cout<<"The value of the subfunction is: "<< pcValue <<endl;
			//converting value to double
			double dXmlValue;
			int iReadValues = sscanf( pcValue, "%lf", & dXmlValue );
			if ( iReadValues != 0){
				if ( dXmlValue == dSubFun2Value ){
					cout<<"The value of the second subfunction is correct."<<endl;
				}else{
					cerr<<"Error: The value of the second subfunction should be : "<<
						dSubFun2Value<<", but is "<<dXmlValue<<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: The element text is not a number."<<endl;
				iReturn++;
			}
	
		}else{// pXmlElement == NULL ->no root handle
			cerr<<"Error: No first subfunction handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
			return iReturn;
		}
	}else{// pXmlElement == NULL ->no root handle
		if ( ucSubCondition1 == 0 ){
			cout<<"Ther is correctly no first subfunction. "<<endl;
		}else{
			cerr<<"Error: No subfunction handle in \""<< szFilename <<"\"."<<endl;
			iReturn++;
		}
	}


	return iReturn;
}



/**
 * This function tests the storeXml() method of the cFunctionIf class.
 * Just storing properties with no underobjects is tested.
 *
 * methods tested:
 * 	- cFunctionIf( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- bool storeXml( ostream &stream ) const;
 * 	- cUnderFunction * restoreXml( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cUnderFunction * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStoreXml( unsigned long &ulTestphase ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an "<<
		getUnderFunctionName()<<" function"<<endl;

	cout<<"cFunctionIf functionIf1( NULL, NULL, NULL );"<<endl;
	cFunctionIf functionIf1( NULL, NULL, NULL );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlUnderFunctionsFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "functionIfNull.xml" );
	ofstream * pFileCondition = new ofstream( szXmlUnderFunctionsFileName );
	
	bool bStoreSuccesfull = functionIf1.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( ! bStoreSuccesfull ){
	
		cout<<"The data of the cFunctionIf was correctly stored not successfull to the file \""<< szXmlUnderFunctionsFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFunctionIf to the file \""<< szXmlUnderFunctionsFileName <<"\" was successfull."<<endl;
		iReturn++;
	}
	iReturn += testXmlFunctionValue( szXmlUnderFunctionsFileName );
	
	TiXmlDocument xmlDocFunctionIf( szFileNameBuffer );
	bool loadOkay = xmlDocFunctionIf.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle( &xmlDocFunctionIf ); "<<endl;
		TiXmlHandle xmlHandle( &xmlDocFunctionIf );
		cout<<"cFunctionIf functionIf1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cFunctionIf functionIf1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus != 0 ){
		
			cout<<"The data was correctly not loaded successfull(outStatus="<< outStatus <<"). "<<endl;
		}else{
			cerr<<"Error: The data was correctly loaded, but shouldn't be. (subfunctions are NULL)"<<endl;
			iReturn++;
		}
		
		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocFunctionIf ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocFunctionIf );
		cout<<"cFunctionIf functionIf1Loaded = cUnderFunction::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cUnderFunction * pUnderFunctions1Loaded = cUnderFunction::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus != 0 ){
		
			cout<<"The data was loaded not successfull (outStatus="<< outStatus <<"). "<<endl;
		}else{
			cerr<<"Error: Data was loaded not successfull."<<endl;
			iReturn++;
		}
		if ( pUnderFunctions1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctions1Loaded, "pUnderFunctions1Loaded", functionIf1, "functionIf1" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctions1Loaded );
			delete pUnderFunctions1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorFunction and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cFunctionAbs functionSup( NULL );"<<endl;
		cFunctionAbs functionSup( NULL );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle3( &xmlDocFunctionIf ); "<<endl;
		TiXmlHandle xmlHandle3( &xmlDocFunctionIf );
		cout<<"cFunctionIf functionIf1LoadedFull( xmlHandle3.FirstChildElement().Element(), "<<
			"outStatus, liDefinedVariables, &functionSup, &rootSimple ); "<<endl;
		cFunctionIf functionIf1LoadedFull( xmlHandle3.FirstChildElement().Element(),
			outStatus, liDefinedVariables, &functionSup, &rootSimple );
		
		if ( outStatus != 0 ){
		
			cout<<"The data was correctly not loaded successfull(outStatus="<< outStatus <<"). "<<endl;
		}else{
			cerr<<"Error: The data was correctly loaded, but shouldn't be. (subfunctions are NULL)"<<endl;
			iReturn++;
		}
		
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cFunctionAbs functionSup2( NULL );"<<endl;
		cFunctionAbs functionSup2( NULL );

		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDocFunctionIf ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocFunctionIf );
		cout<<"cFunctionIf pUnderFunctions1LoadedFull = cUnderFunction::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&functionSup2, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctions1LoadedFull = cUnderFunction::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &functionSup2, &rootSimple );
		
		if ( outStatus != 0 ){
		
			cout<<"The data was loaded not successfull (outStatus="<< outStatus <<"). "<<endl;
		}else{
			cerr<<"Error: Data was loaded not successfull."<<endl;
			iReturn++;
		}
		if ( pUnderFunctions1LoadedFull ){
			if ( (pUnderFunctions1LoadedFull->getType()) == (getFunctionType()) ){
				cout<<"Correctly an "<<getUnderFunctionName()<<" function restored."<<endl;
				//check the first subfunction
				if ( ((cFunctionIf*)pUnderFunctions1LoadedFull)->getFirstUnderFunction() == NULL ){
				
					cout<<"The subfunction of the first function correctly NULL . "<<endl;
				}else{
					cerr<<"Error: The subfunction of the first function is NULL "<<
						" but should be NULL ."<<endl;
					iReturn++;
				}
				//check the second subfunction
				if ( ((cFunctionIf*)pUnderFunctions1LoadedFull)->getSecondUnderFunction() == NULL ){
				
					cout<<"The subfunction of the second function correctly NULL . "<<endl;
				}else{
					cerr<<"Error: The subfunction of the second function is NULL "<<
						" but should be NULL ."<<endl;
					iReturn++;
				}
			}else{
				cerr<<"Error: Not an "<<getUnderFunctionName()<<" function restored."<<endl;
				iReturn++;
			}
			//check the getDefiningFibElement() methode from cFunctionIf
			if ( pUnderFunctions1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The function defining Fib-element is correctly "<<
					pUnderFunctions1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The function defining Fib-element is "<<
					pUnderFunctions1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionIf
			if ( pUnderFunctions1LoadedFull->getSuperiorUnderFunction() == &functionSup2 ){
			
				cout<<"The superior function of the function correctly "<<
					pUnderFunctions1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior function of the function is "<<
					pUnderFunctions1LoadedFull->getSuperiorUnderFunction() <<
					" but should be functionSup2="<< &functionSup2 <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctions1LoadedFull;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an "<<
		getUnderFunctionName()<<" function with an true and a false subfunction"<<endl;
	
	cout<<"cConditionTrue subConditionTrue;"<<endl;
	cConditionTrue subConditionTrue;
	cout<<"cFunctionValue subfunValue1( 1 );"<<endl;
	cFunctionValue subfunValue1( 1 );
	cout<<"cFunctionValue subfunValue2( 2 );"<<endl;
	cFunctionValue subfunValue2( 2 );
	cout<<"cFunctionIf functionIfTrueV1V2( subConditionTrue, subfunValue1, subfunValue2 );"<<endl;
	cFunctionIf functionIfTrueV1V2( subConditionTrue, subfunValue1, subfunValue2 );
	
	szFileNameBuffer[0] = 0;
	szXmlUnderFunctionsFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "functionIfTrueV1V2.xml" );
	pFileCondition = new ofstream( szXmlUnderFunctionsFileName );
	
	bStoreSuccesfull = functionIfTrueV1V2.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFunctionIf was stored successfull to the file \""<< szXmlUnderFunctionsFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFunctionIf to the file \""<< szXmlUnderFunctionsFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlFunctionValue( szXmlUnderFunctionsFileName, 1, 1, 2 );
	
	TiXmlDocument xmlDocFunctionIfTrue( szFileNameBuffer );
	loadOkay = xmlDocFunctionIfTrue.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle( &xmlDocFunctionIfTrue ); "<<endl;
		TiXmlHandle xmlHandle( &xmlDocFunctionIfTrue );
		cout<<"cFunctionIf functionIf1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cFunctionIf functionIf1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( functionIf1Loaded.getType() == getFunctionType() ){
		
			cout<<"The loaded subfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded subfunction has the type "<<
				functionIf1Loaded.getType() <<" , but should have the type "<<
				getFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( functionIf1Loaded, "functionIf1Loaded", functionIfTrueV1V2, "functionIfTrueV1V2" );
		iReturn += testNotConnectedUnderFunction( functionIf1Loaded );
		
		
		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocFunctionIfTrue ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocFunctionIfTrue );

		cout<<"cFunctionIf pUnderFunctions1Loaded = cUnderFunction::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );dVariables ); "<<endl;
		cUnderFunction * pUnderFunctions1Loaded = cUnderFunction::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctions1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctions1Loaded, "pUnderFunctions1Loaded", functionIfTrueV1V2, "functionIfTrueV1V2" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctions1Loaded );
			delete pUnderFunctions1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		
		//with given pInSuperiorFunction and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cFunctionAbs functionSup( NULL );"<<endl;
		cFunctionAbs functionSup( NULL );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle3( &xmlDocFunctionIfTrue ); "<<endl;
		TiXmlHandle xmlHandle3( &xmlDocFunctionIfTrue );
		cout<<"cFunctionIf functionIf1LoadedFull( xmlHandle3.FirstChildElement().Element(), "<<
			"outStatus, liDefinedVariables, &functionSup, &rootSimple ); "<<endl;
		cFunctionIf functionIf1LoadedFull( xmlHandle3.FirstChildElement().Element(),
			outStatus, liDefinedVariables, &functionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( functionIf1LoadedFull.getType() == getFunctionType() ){
		
			cout<<"The loaded subfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded subfunction has the type "<<
				functionIf1LoadedFull.getType() <<" , but should have the type "<<
				getFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( functionIf1LoadedFull,
			"functionIf1LoadedFull", functionIfTrueV1V2, "functionIfTrueV1V2" );
		//check the getDefiningFibElement() methode from cFunctionTwoValue
		if ( functionIf1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The subfunction defining fib -element is correctly "<<
				functionIf1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The subfunction defining fib -element is "<<
				functionIf1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
		if ( functionIf1LoadedFull.getSuperiorUnderFunction() == &functionSup  ){
		
			cout<<"The superior subfunction of the subfunction correctly "<<
				functionIf1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior subfunction of the subfunction is "<<
				functionIf1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &functionSup <<" ."<<endl;
			iReturn++;
		}
		
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cFunctionAbs functionSup2( NULL );"<<endl;
		cFunctionAbs functionSup2( NULL );

		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDocFunctionIfTrue ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocFunctionIfTrue );
		cout<<"cFunctionIf pUnderFunctions1LoadedFull = cUnderFunction::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&functionSup2, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctions1LoadedFull = cUnderFunction::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &functionSup2, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctions1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctions1LoadedFull, "pUnderFunctions1LoadedFull", functionIfTrueV1V2, "functionIfTrueV1V2" );
			//check the getDefiningFibElement() methode from cFunctionIf
			if ( pUnderFunctions1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The function defining Fib-element is correctly "<<
					pUnderFunctions1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The function defining Fib-element is "<<
					pUnderFunctions1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionIf
			if ( pUnderFunctions1LoadedFull->getSuperiorUnderFunction() == &functionSup2 ){
			
				cout<<"The superior function of the function correctly "<<
					pUnderFunctions1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior function of the function is "<<
					pUnderFunctions1LoadedFull->getSuperiorUnderFunction() <<
					" but should be functionSup2="<< &functionSup2 <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctions1LoadedFull;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an "<<
		getUnderFunctionName()<<" function with an false and an true subfunction"<<endl;
	
	cout<<"cFunctionIf functionIfFalseVm1V4( ew cConditionFalse(), new cFunctionValue( -1 ), new cFunctionValue( 4 ) );"<<endl;
	cFunctionIf functionIfFalseVm1V4( new cConditionFalse(), new cFunctionValue( -1 ), new cFunctionValue( 4 ) );
	
	szFileNameBuffer[0] = 0;
	szXmlUnderFunctionsFileName = strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "functionIfFalseVm1V4.xml" );
	pFileCondition = new ofstream( szXmlUnderFunctionsFileName );
	
	bStoreSuccesfull = functionIfFalseVm1V4.storeXml( *pFileCondition );
	delete pFileCondition;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFunctionIf was stored successfull to the file \""<< szXmlUnderFunctionsFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFunctionIf to the file \""<< szXmlUnderFunctionsFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlFunctionValue( szXmlUnderFunctionsFileName, 2, -1, 4 );
	
	TiXmlDocument xmlDocFunctionIfFalse( szFileNameBuffer );
	loadOkay = xmlDocFunctionIfFalse.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		cout<<"TiXmlHandle xmlHandle( &xmlDocFunctionIfFalse ); "<<endl;
		TiXmlHandle xmlHandle( &xmlDocFunctionIfFalse );
		cout<<"cFunctionIf functionIf1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cFunctionIf functionIf1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( functionIf1Loaded.getType() == getFunctionType() ){
		
			cout<<"The loaded subfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded subfunction has the type "<<
				functionIf1Loaded.getType() <<" , but should have the type "<<
				getFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( functionIf1Loaded, "functionIf1Loaded", functionIfFalseVm1V4, "functionIfFalseVm1V4" );
		iReturn += testNotConnectedUnderFunction( functionIf1Loaded );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocFunctionIfFalse ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocFunctionIfFalse );
		cout<<"cFunctionIf * pUnderFunctions1Loaded = cUnderFunction::restoreXml("<<
			"xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cUnderFunction * pUnderFunctions1Loaded = cUnderFunction::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctions1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctions1Loaded, "pUnderFunctions1Loaded", functionIfFalseVm1V4, "functionIfFalseVm1V4" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctions1Loaded );
			delete pUnderFunctions1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorFunction and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cFunctionAbs functionSup( NULL );"<<endl;
		cFunctionAbs functionSup( NULL );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle3( &xmlDocFunctionIfFalse ); "<<endl;
		TiXmlHandle xmlHandle3( &xmlDocFunctionIfFalse );
		cout<<"cFunctionIf functionIf1LoadedFull( xmlHandle3.FirstChildElement().Element(), "<<
			"outStatus, liDefinedVariables, &functionSup, &rootSimple ); "<<endl;
		cFunctionIf functionIf1LoadedFull( xmlHandle3.FirstChildElement().Element(),
			outStatus, liDefinedVariables, &functionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( functionIf1LoadedFull.getType() == getFunctionType() ){
		
			cout<<"The loaded subfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded subfunction has the type "<<
				functionIf1LoadedFull.getType() <<" , but should have the type "<<
				getFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( functionIf1LoadedFull,
			"functionIf1LoadedFull", functionIfFalseVm1V4, "functionIfFalseVm1V4" );
		//check the getDefiningFibElement() methode from cFunctionTwoValue
		if ( functionIf1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The subfunction defining fib -element is correctly "<<
				functionIf1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The subfunction defining fib -element is "<<
				functionIf1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
		if ( functionIf1LoadedFull.getSuperiorUnderFunction() == &functionSup  ){
		
			cout<<"The superior subfunction of the subfunction correctly "<<
				functionIf1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior subfunction of the subfunction is "<<
				functionIf1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &functionSup <<" ."<<endl;
			iReturn++;
		}
		
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cFunctionAbs functionSup2( NULL );"<<endl;
		cFunctionAbs functionSup2( NULL );

		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"TiXmlHandle xmlHandle4( &xmlDocFunctionIfFalse ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocFunctionIfFalse );
		cout<<"cFunctionIf pUnderFunctions1LoadedFull = cUnderFunction::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&functionSup2, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctions1LoadedFull = cUnderFunction::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &functionSup2, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctions1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctions1LoadedFull, "pUnderFunctions1LoadedFull", functionIfFalseVm1V4, "functionIfFalseVm1V4" );
			//check the getDefiningFibElement() methode from cFunctionIf
			if ( pUnderFunctions1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The function defining Fib-element is correctly "<<
					pUnderFunctions1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The function defining Fib-element is "<<
					pUnderFunctions1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionIf
			if ( pUnderFunctions1LoadedFull->getSuperiorUnderFunction() == &functionSup2 ){
			
				cout<<"The superior function of the function correctly "<<
					pUnderFunctions1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior function of the function is "<<
					pUnderFunctions1LoadedFull->getSuperiorUnderFunction() <<
					" but should be functionSup2="<< &functionSup2 <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctions1LoadedFull;
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
 * 	- cFunctionIf( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- bool store( ostream & stream, char & cRestBits, unsigned char & uiRestBitPosition ) const;
 * 	- cUnderFunction * restore( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInValueDomain, const cDomainSingle * pInDomainVariable, cUnderFunction * pInSuperiorCondition = NULL, cFibElement *pInDefiningFibElement = NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of errors occured in the test
 */
int testStore( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method on an true condition and value 1 and 2 subfunction"<<endl;

	cout<<"cRoot root;"<<flush<<endl;
	cRoot root;
	
	cout<<"cConditionTrue subConditionTrue;"<<endl;
	cConditionTrue subConditionTrue;
	cout<<"cFunctionValue subFunValue1( 1 );"<<endl;
	cFunctionValue subFunValue1( 1 );
	cout<<"cFunctionValue subFunValue2( 2 );"<<endl;
	cFunctionValue subFunValue2( 2 );
	
	cout<<"cFunctionIf functionIf1( subConditionTrue, subFunValue1, subFunValue2, NULL, &root );"<<endl;
	cFunctionIf functionIf1( subConditionTrue, subFunValue1, subFunValue2, NULL, &root );

	//test get compressed size
	unsigned int uiCompressedSize = 10 + 4 + 2 * ( 2 + 16 );
	if ( (unsigned int)(functionIf1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			functionIf1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "functionIfTrue.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = (char)0x00;
	unsigned char cRestBitPosition = 0;
	cout<<"functionIf1.store( *pFile, cRestBits, cRestBitPosition );"<<endl;
	bool bStoreSuccesfull = functionIf1.store( *pFile, cRestBit, cRestBitPosition );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	unsigned char ucRestBit = cRestBit;
	unsigned char ucRestBitCorrect = (char)0x00;
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
	/*Bits: 0000000000000010 00  0000000000000001 00  1111  0000 0 111 11 =
		= 00 0000 0000 0000 1000 0000 0000 0000 0001  0011 1100  0001 1111
	*/
	const char tUnderFunction1[] = { (char)0x1F, (char)0x3C, (char)0x01, (char)0x00, (char)0x08, (char)0x00, (char)0x00 };
	iReturn += compareBytsWithFile( szFileNameBuffer, tUnderFunction1, 7 );


	cDomainSingle * pValueDomain = new cDomainNaturalNumberBit( 16 );
	cDomainSingle * pVariableDomain = new cDomainNaturalNumberBit( 3 );
	
	char szFunctionName[ 3 ];
	
	ifstream * pFileIn = new ifstream( szFileNameBuffer );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		
		cReadBits iBitStream( * pFileIn );
		iBitStream.readBits( szFunctionName, getNumberOfTypeBits() );
		cout<<"cFunctionIf underFunctionIf1Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cFunctionIf underFunctionIf1Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionIf1Loaded.getType() == getFunctionType() ){
		
			cout<<"The loaded subfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded subfunction has the type "<<
				underFunctionIf1Loaded.getType() <<" , but should have the type "<<
				getFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionIf1Loaded, "underFunctionIf1Loaded", functionIf1, "functionIf1" );
		iReturn += testNotConnectedUnderFunction( underFunctionIf1Loaded );
		cout<<"checking: underFunctionIf1Loaded.getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionIf1Loaded.getFirstUnderFunction(),
			&subFunValue1, &underFunctionIf1Loaded, NULL );
		cout<<"checking: underFunctionIf1Loaded.getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionIf1Loaded.getSecondUnderFunction(),
			&subFunValue2, &underFunctionIf1Loaded, NULL );

		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream2( * pFileIn );
		cout<<"cFunctionIf pUnderFunctions1Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctions1Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctions1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctions1Loaded, "pUnderFunctions1Loaded", functionIf1, "functionIf1" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctions1Loaded );
			delete pUnderFunctions1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorFunction and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cFunctionAbs underFunctionSup( NULL );"<<endl;
		cFunctionAbs underFunctionSup( NULL );
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );
		
		cReadBits iBitStream3( * pFileIn );
		iBitStream3.readBits( szFunctionName, getNumberOfTypeBits() );
		outStatus = 0;
		cout<<"cFunctionIf functionIf1LoadedFull( iBitStream3, "<<
			"outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &underFunctionSup, &rootSimple ); "<<endl;
		cFunctionIf functionIf1LoadedFull( iBitStream3,
			outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( functionIf1LoadedFull.getType() == getFunctionType() ){
		
			cout<<"The loaded subfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded subfunction has the type "<<
				functionIf1LoadedFull.getType() <<" , but should have the type "<<
				getFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( functionIf1LoadedFull,
			"functionIf1LoadedFull", functionIf1, "functionIf1" );
		//check the getDefiningFibElement() methode from cFunctionTwoValue
		if ( functionIf1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The subfunction defining fib -element is correctly "<<
				functionIf1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The subfunction defining fib -element is "<<
				functionIf1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
		if ( functionIf1LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior subfunction of the subfunction correctly "<<
				functionIf1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior subfunction of the subfunction is "<<
				functionIf1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		cout<<"checking: functionIf1LoadedFull.getFirstUnderFunction()"<<endl;
		iReturn += checkUnderFunction( functionIf1LoadedFull.getFirstUnderFunction(),
			&subFunValue1, &functionIf1LoadedFull, &rootSimple );
		cout<<"checking: functionIf1LoadedFull.getSecondUnderFunction()"<<endl;
		iReturn += checkUnderFunction( functionIf1LoadedFull.getSecondUnderFunction(),
			&subFunValue2, &functionIf1LoadedFull, &rootSimple );
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );
		
		cReadBits iBitStream4( * pFileIn );
		outStatus = 0;
		cout<<"cFunctionAbs underFunctionSup2( NULL );"<<endl;
		cFunctionAbs underFunctionSup2( NULL );
		liDefinedVariables.clear();
		cout<<"cFunctionIf pUnderFunctions1LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&underFunctionSup2, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctions1LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&underFunctionSup2, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctions1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctions1LoadedFull, "pUnderFunctions1LoadedFull", functionIf1, "functionIf1" );
			//check the getDefiningFibElement() methode from cFunctionIf
			if ( pUnderFunctions1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The function defining Fib-element is correctly "<<
					pUnderFunctions1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The function defining Fib-element is "<<
					pUnderFunctions1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionIf
			if ( pUnderFunctions1LoadedFull->getSuperiorUnderFunction() == &underFunctionSup2 ){
			
				cout<<"The superior function of the function correctly "<<
					pUnderFunctions1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior function of the function is "<<
					pUnderFunctions1LoadedFull->getSuperiorUnderFunction() <<
					" but should be functionSup="<< &underFunctionSup2 <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctions1LoadedFull;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		delete pFileIn;
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with given domains "<<endl;

	delete pValueDomain;
	pValueDomain = new cDomainNaturalNumberBit( 8 );
	delete pVariableDomain;
	pVariableDomain = new cDomainNaturalNumberBit( 4 );
	
	cout<<"cTypeUnderFunction testTypeUnderFunction;"<<endl;
	cTypeUnderFunction testTypeUnderFunction;
	
	cout<<"cDomainNaturalNumberBit naturalNumberDomainB8( 8 );"<<endl;
	cDomainNaturalNumberBit naturalNumberDomainB8( 8 );

	cout<<"root.getDomains()->addDomain( testTypeUnderFunction, &naturalNumberDomainB8 );"<<endl;
	root.getDomains()->addDomain( testTypeUnderFunction, &naturalNumberDomainB8 );
	
	cout<<"cTypeVariable testTypeVariable;"<<endl;
	cTypeVariable testTypeVariable;
	
	cout<<"cDomainNaturalNumberBit domainsNatB4( 4 );"<<endl;
	cDomainNaturalNumberBit domainsNatB4( 4 );
	
	cout<<"root.getDomains()->addDomain( testTypeVariable, &domainsNatB4 );"<<endl;
	root.getDomains()->addDomain( testTypeVariable, &domainsNatB4 );
	
	cout<<"cFunctionIf functionIfFalseV9V255( new cConditionFalse(), new cFunctionValue( 9 ), new cFunctionValue( 255 ), NULL, &root );"<<endl;
	cFunctionIf functionIfFalseV9V255( new cConditionFalse(), new cFunctionValue( 9 ), new cFunctionValue( 255 ), NULL, &root );

	//test get compressed size
	uiCompressedSize = 10 + 4 + 2 * ( 2 + 8 );
	if ( (unsigned int)(functionIfFalseV9V255.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			functionIfFalseV9V255.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "functionIfFalseV9V255.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x00;
	cRestBitPosition = 0;
	cout<<"functionIfFalseV9V255.store( *pFile, cRestBits, cRestBitPosition );"<<endl;
	bStoreSuccesfull = functionIfFalseV9V255.store( *pFile, cRestBit, cRestBitPosition );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = (char)0x03;
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
	/*Bits: 11111111 00  00001001 00  0000  0000 0 111 11 =
		= 11  1111 1100  0000 1001  0000 0000  0001 1111
	*/
	const char cFunctionIfFalseV9V255[] = { (char)0x1F, (char)0x00, (char)0x09, (char)0xFC, (char)0x03 };
	iReturn += compareBytsWithFile( szFileNameBuffer, cFunctionIfFalseV9V255, 5 );
	
	
	pFileIn = new ifstream( szFileNameBuffer );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		intFib outStatus = 0;
		list<cFibVariable*> liDefinedVariables;
		
		cReadBits iBitStream( * pFileIn );
		iBitStream.readBits( szFunctionName, getNumberOfTypeBits() );
		cout<<"cFunctionIf underFunctionIf1Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cFunctionIf underFunctionIf1Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionIf1Loaded.getType() == getFunctionType() ){
		
			cout<<"The loaded subfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded subfunction has the type "<<
				underFunctionIf1Loaded.getType() <<" , but should have the type "<<
				getFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionIf1Loaded, "underFunctionIf1Loaded", functionIfFalseV9V255, "functionIfFalseV9V255" );
		iReturn += testNotConnectedUnderFunction( underFunctionIf1Loaded );
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream2( * pFileIn );
		outStatus = 0;
		cout<<"cFunctionIf pUnderFunctions1Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctions1Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctions1Loaded ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctions1Loaded, "pUnderFunctions1Loaded", functionIfFalseV9V255, "functionIfFalseV9V255" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctions1Loaded );
			delete pUnderFunctions1Loaded;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorFunction and pInDefiningFibElement
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cFunctionAbs functionSup( NULL );"<<endl;
		cFunctionAbs functionSup( NULL );
		
		cReadBits iBitStream3( * pFileIn );
		iBitStream3.readBits( szFunctionName, getNumberOfTypeBits() );
		outStatus = 0;
		cout<<"cFunctionIf functionIf1LoadedFull( iBitStream3, "<<
			"outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &functionSup, &rootSimple ); "<<endl;
		cFunctionIf functionIf1LoadedFull( iBitStream3,
			outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &functionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( functionIf1LoadedFull.getType() == getFunctionType() ){
		
			cout<<"The loaded subfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded subfunction has the type "<<
				functionIf1LoadedFull.getType() <<" , but should have the type "<<
				getFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( functionIf1LoadedFull,
			"functionIf1LoadedFull", functionIfFalseV9V255, "functionIfFalseV9V255" );
		//check the getDefiningFibElement() methode from cFunctionTwoValue
		if ( functionIf1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The subfunction defining fib -element is correctly "<<
				functionIf1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The subfunction defining fib -element is "<<
				functionIf1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
		if ( functionIf1LoadedFull.getSuperiorUnderFunction() == &functionSup  ){
		
			cout<<"The superior subfunction of the subfunction correctly "<<
				functionIf1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior subfunction of the subfunction is "<<
				functionIf1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &functionSup <<" ."<<endl;
			iReturn++;
		}
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );

		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cFunctionAbs functionSup2( NULL );"<<endl;
		cFunctionAbs functionSup2( NULL );
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * pFileIn );
		outStatus = 0;
		liDefinedVariables.clear();
		cout<<"cFunctionIf pUnderFunctions1LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&functionSup2, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctions1LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&functionSup2, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctions1LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctions1LoadedFull, "pUnderFunctions1LoadedFull", functionIfFalseV9V255, "functionIfFalseV9V255" );
			//check the getDefiningFibElement() methode from cFunctionIf
			if ( pUnderFunctions1LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The function defining Fib-element is correctly "<<
					pUnderFunctions1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The function defining Fib-element is "<<
					pUnderFunctions1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionIf
			if ( pUnderFunctions1LoadedFull->getSuperiorUnderFunction() == &functionSup2 ){
			
				cout<<"The superior function of the function correctly "<<
					pUnderFunctions1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior function of the function is "<<
					pUnderFunctions1LoadedFull->getSuperiorUnderFunction() <<
					" but should be functionSup2="<< &functionSup2 <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctions1LoadedFull;
		}
		if ( ! liDefinedVariables.empty() ){
			cerr<<"Error: Defined variables wher created ."<<endl;
			iReturn++;
		}
		delete pFileIn;
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}


	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method with given restbit and variable subfunction"<<endl;

	cout<<"root.setNumberOfInputVariables( 10 );"<<endl;
	root.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 = root.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 = root.getInputVariable( 1 );
	cout<<"pVariable2 = root.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 = root.getInputVariable( 2 );
	cout<<"pVariable3 = root.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 = root.getInputVariable( 3 );
	cout<<"pVariable1->setValue( 1.0 );"<<endl;
	pVariable1->setValue( 1.0 );
	cout<<"pVariable2->setValue( 2.0 );"<<endl;
	pVariable2->setValue( 2.0 );
	cout<<"pVariable3->setValue( 3.0 );"<<endl;
	pVariable3->setValue( 3.0 );
	
	cout<<"list<cFibVariable*> liDefinedVariables;"<<endl;
	list<cFibVariable*> liDefinedVariables;
	cout<<"liDefinedVariables.push_back( pVariable3 );"<<endl;
	liDefinedVariables.push_back( pVariable3 );
	cout<<"liDefinedVariables.push_back( pVariable1 );"<<endl;
	liDefinedVariables.push_back( pVariable1 );
	cout<<"liDefinedVariables.push_back( pVariable2 );"<<endl;
	liDefinedVariables.push_back( pVariable2 );
	
	list<cFibVariable*> liDefinedVariablesOrg = liDefinedVariables;


	cout<<"cFunctionIf functionIf2( new cConditionTrue(), new cFunctionVariable( pVariable3 ), new cFunctionVariable( pVariable2 ), NULL, &root );"<<endl;
	cFunctionIf functionIf2( new cConditionTrue(), new cFunctionVariable( pVariable3 ), new cFunctionVariable( pVariable2 ), NULL, &root );
	
	//test get compressed size
	uiCompressedSize = 10 + 4 + 2 * ( 2 + 4 );
	if ( (unsigned int)(functionIf2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the type is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the type is "<<
			functionIf2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), "functionIf2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = (char)0x01;
	cRestBitPosition = 2;
	cout<<"functionIf2.store( *pFile, cRestBit, cRestBitPosition ); "<<endl;
	bStoreSuccesfull = functionIf2.store( *pFile, cRestBit, cRestBitPosition );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	ucRestBit = cRestBit;
	ucRestBitCorrect = (char)0x02;
	sNumberOfRestBitCorrect = 4;
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
	/*Bits: 0010 01  0011 01  1111  0000 0 111 11  01 =
		= 0010  0100 1101  1111 0000  0111 1101
	*/
	const char szUnderFunctions2[] = { (char)0x7D, (char)0xF0, (char)0x4D, (char)0x02 };
	iReturn += compareBytsWithFile( szFileNameBuffer, szUnderFunctions2, 4 );
	

	pFileIn = new ifstream( szFileNameBuffer );
	if ( (pFileIn != NULL) && ( pFileIn->good() ) ){
		
		char cBuffer;
		intFib outStatus = 0;
		
		cReadBits iBitStream( * pFileIn );
		iBitStream.readBits( &cBuffer, 2 );
		iBitStream.readBits( szFunctionName, getNumberOfTypeBits() );
		cout<<"cFunctionIf underFunctionIf1Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cFunctionIf underFunctionIf1Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionIf1Loaded.getType() == getFunctionType() ){
		
			cout<<"The loaded subfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded subfunction has the type "<<
				underFunctionIf1Loaded.getType() <<" , but should have the type "<<
				getFunctionType() <<" ."<<endl;
			iReturn++;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: Defined variables wher changed ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( underFunctionIf1Loaded, "underFunctionIf1Loaded", functionIf2, "functionIf2" );
		iReturn += testNotConnectedUnderFunction( underFunctionIf1Loaded );
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream2( * pFileIn );
		iBitStream2.readBits( &cBuffer, 2 );
		liDefinedVariables = liDefinedVariablesOrg;
		outStatus = 0;
		cout<<"cFunctionIf pUnderFunctions3Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctions3Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctions3Loaded ){
			const int iErrorsEqual = testCompareTwoEqualObjects( 
				* pUnderFunctions3Loaded, "pUnderFunctions3Loaded", functionIf2, "functionIf2" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctions3Loaded );
			if ( iErrorsEqual != 0 ){
				cerr<<"Error: Loaded function not equal."<<endl;
			}
			iReturn += iErrorsEqual;
			delete pUnderFunctions3Loaded;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: Defined variables wher changed ."<<endl;
			iReturn++;
		}
		
		//with given pInSuperiorFunction and pInDefiningFibElement
		cout<<"cRoot rootSimple;"<<endl;
		cRoot rootSimple;
		cout<<"cFunctionAbs functionSup( NULL );"<<endl;
		cFunctionAbs functionSup( NULL );
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream3( * pFileIn );
		iBitStream3.readBits( &cBuffer, 2 );
		iBitStream3.readBits( szFunctionName, getNumberOfTypeBits() );
		liDefinedVariables = liDefinedVariablesOrg;
		outStatus = 0;
		cout<<"cFunctionIf functionIf1LoadedFull( iBitStream3, "<<
			"outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &functionSup, &rootSimple ); "<<endl;
		cFunctionIf functionIf1LoadedFull( iBitStream3,
			outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &functionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( functionIf1LoadedFull.getType() == getFunctionType() ){
		
			cout<<"The loaded subfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded subfunction has the type "<<
				functionIf1LoadedFull.getType() <<" , but should have the type "<<
				getFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareTwoEqualObjects( functionIf1LoadedFull,
			"functionIf1LoadedFull", functionIf2, "functionIf2" );
		//check the getDefiningFibElement() methode from cFunctionTwoValue
		if ( functionIf1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The subfunction defining fib -element is correctly "<<
				functionIf1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The subfunction defining fib -element is "<<
				functionIf1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionTwoValue
		if ( functionIf1LoadedFull.getSuperiorUnderFunction() == &functionSup  ){
		
			cout<<"The superior subfunction of the subfunction correctly "<<
				functionIf1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior subfunction of the subfunction is "<<
				functionIf1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &functionSup <<" ."<<endl;
			iReturn++;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: Defined variables wher changed ."<<endl;
			iReturn++;
		}
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );
		
		//with given pInSuperiorCondition and pInDefiningFibElement
		cout<<"cFunctionAbs functionSup2( NULL );"<<endl;
		cFunctionAbs functionSup2( NULL );
		
		delete pFileIn;
		pFileIn = new ifstream( szFileNameBuffer );
		cReadBits iBitStream4( * pFileIn );
		iBitStream4.readBits( &cBuffer, 2 );
		outStatus = 0;
		liDefinedVariables = liDefinedVariablesOrg;
		cout<<"cFunctionIf pUnderFunctions3LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&functionSup2, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctions3LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&functionSup2, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: Error while loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctions3LoadedFull ){
			iReturn += testCompareTwoEqualObjects( * pUnderFunctions3LoadedFull, "pUnderFunctions3LoadedFull", functionIf2, "functionIf2" );
			//check the getDefiningFibElement() methode from cFunctionIf
			if ( pUnderFunctions3LoadedFull->getDefiningFibElement() == &rootSimple ){
			
				cout<<"The function defining Fib-element is correctly "<<
					pUnderFunctions3LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The function defining Fib-element is "<<
					pUnderFunctions3LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionIf
			if ( pUnderFunctions3LoadedFull->getSuperiorUnderFunction() == &functionSup2 ){
			
				cout<<"The superior function of the function correctly "<<
					pUnderFunctions3LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior function of the function is "<<
					pUnderFunctions3LoadedFull->getSuperiorUnderFunction() <<
					" but should be functionSup2="<< &functionSup2 <<" ."<<endl;
				iReturn++;
			}
			delete pUnderFunctions3LoadedFull;
		}
		if ( liDefinedVariables != liDefinedVariablesOrg ){
			cerr<<"Error: Defined variables wher changed ."<<endl;
			iReturn++;
		}
		delete pFileIn;
	
	}else{
		cerr<<"Error: Failed to load file \""<< szFileNameBuffer <<"\""<<endl;
		iReturn++;
	}


	delete pValueDomain;
	delete pVariableDomain;

	return iReturn;
}



/**
 * This function tests the subcelement methods of the cFunctionIf class.
 *
 * methods tested:
 * 		- cUnderFunction * getCondition();
 * 		- const cUnderFunction * getCondition() const;
 * 		- bool setCondition( const cUnderFunction & inCondition, bool bDeleteOld=true );
 * 		- bool setCondition( cUnderFunction * pInCondition, bool bDeleteOld=true );
 * 		- cUnderFunction * getFirstUnderFunction();
 * 		- void setFirstUnderFunction( const cUnderFunction & underFunction, bool bDeleteOld=true );
 * 		- cUnderFunction * getSecondUnderFunction();
 * 		- void setSecondUnderFunction( const cUnderFunction & underFunction, bool bDeleteOld=true );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @return the number of erros occured in the test
 */
int testSubElements( unsigned long &ulTestphase ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the condition and subfunction methods"<<endl;
	
	cout<<"cPoint point;"<<endl;
	cPoint point;
	cout<<"cRoot root( &point );"<<endl;
	cRoot root( &point );
	
	cout<<"cTypeUnderFunction testTypeUnderFunction;"<<endl;
	cTypeUnderFunction testTypeUnderFunction;
	cout<<"cDomainRational domFunValues( cDomainNaturalNumberBit( 16 ), "<<
		"cDomainNaturalNumberBit( 16 ) );"<<endl;
	cDomainRational domFunValues( cDomainNaturalNumberBit( 16 ),
		cDomainNaturalNumberBit( 16 ) );
	cout<<"root.getDomains()->addDomain( testTypeUnderFunction, &domFunValues );"<<endl;
	root.getDomains()->addDomain( testTypeUnderFunction, &domFunValues );
	
	cout<<"root.setNumberOfInputVariables( 10 );"<<endl;
	root.setNumberOfInputVariables( 10 );
	vector< cFibVariable * > vecVariables;
	for ( unsigned int uiNumberVariable = 1; uiNumberVariable <= 10; uiNumberVariable++ ){
		vecVariables.push_back( root.getInputVariable( uiNumberVariable ) );
		
		if ( rand() % 4 ){
			vecVariables.back()->setValue( domFunValues.round(
				((double)(rand() % (1024 ) - 512)) / 16.0 ) );
		}else{
			vecVariables.back()->setValue( ((double)(rand() % (1024 ) - 512)) / 16.0 );
		}
	}
	
	cout<<"cConditionTrue conditionTrue;"<<endl;
	cConditionTrue conditionTrue;
	cout<<"cConditionFalse conditionFalse;"<<endl;
	cConditionFalse conditionFalse;
	
	cout<<"cConditionNot conditionNot( new cConditionTrue() );"<<endl;
	cConditionNot conditionNot( new cConditionTrue() );
	
	double dCorrectValue = 0.0;
	
	cCondition * pCondition = NULL;
	bool bConditionValue = false;
	bool bConditionIsPointer = true;
	cCondition * pOldCondition = NULL;
	
	cUnderFunction * pFirstSubFunction = NULL;
	double dFirstSubFunctionValue = 0;
	cUnderFunction * pSecondSubFunction = NULL;
	double dSecondSubFunctionValue = 0;
	cout<<"pUnderFunction = new cFunctionIf( "<<pCondition<<","<<
		pFirstSubFunction<<", "<<pSecondSubFunction<<", NULL, &point );"<<endl;
	cFunctionIf * pUnderFunction = new cFunctionIf( NULL, NULL, NULL, NULL, &point );
	bool bIsValid = false;
	
	for ( unsigned int uiIteration = 1; uiIteration <= MAX_RAND_TEST_SIZE; uiIteration++ ){
		
		cout<<endl;
		if ( (rand() % 16) == 0 ){
			//create new function
			if ( pUnderFunction ){
				delete pUnderFunction;
				pUnderFunction = NULL;
				
				pCondition = NULL;
				bConditionValue = false;
				bConditionIsPointer = true;
				
				if ( pFirstSubFunction ){
					delete pFirstSubFunction;
				}
				pFirstSubFunction = NULL;
				if ( pSecondSubFunction ){
					delete pSecondSubFunction;
				}
				pSecondSubFunction = NULL;
				dFirstSubFunctionValue = 0;
				dSecondSubFunctionValue = 0;
			}
			if ( rand() % 4 ){
				if ( rand() % 2 ){
					cout<<"pCondition = new cConditionTrue();"<<endl;
					pCondition = new cConditionTrue();
					bConditionValue = true;
				}else{
					cout<<"pCondition = new cConditionFalse();"<<endl;
					pCondition = new cConditionFalse();
					bConditionValue = false;
				}
			}
			if ( rand() % 4 ){
				if ( rand() % 2 ){
					//set value subfunction
					dFirstSubFunctionValue = ((double)(rand() % (1024 ) - 512)) / 16.0;
					if ( rand() % 4 ){
						dFirstSubFunctionValue = domFunValues.round( dFirstSubFunctionValue );
					}
					cout<<"pFirstSubFunction = new cFunctionValue( "<<dFirstSubFunctionValue<<" );"<<endl;
					pFirstSubFunction = new cFunctionValue( dFirstSubFunctionValue );
				}else{
					//set variable subfunction
					cFibVariable * pChoosenVariable = vecVariables[ rand() % 10 ];
					dFirstSubFunctionValue = pChoosenVariable->getValue();
					cout<<"pFirstSubFunction = new cFunctionVariable( "<<pChoosenVariable<<
						"="<<dFirstSubFunctionValue<<" );"<<endl;
					pFirstSubFunction = new cFunctionVariable( pChoosenVariable );
				}
			}
			if ( rand() % 4 ){
				if ( rand() % 2 ){
					//set value subfunction
					dSecondSubFunctionValue = ((double)(rand() % (1024 ) - 512)) / 16.0;
					if ( rand() % 4 ){
						dSecondSubFunctionValue = domFunValues.round( dSecondSubFunctionValue );
					}
					cout<<"pSecondSubFunction = new cFunctionValue( "<<dSecondSubFunctionValue<<" );"<<endl;
					pSecondSubFunction = new cFunctionValue( dSecondSubFunctionValue );
				}else{
					//set variable subfunction
					cFibVariable * pChoosenVariable = vecVariables[ rand() % 10 ];
					dSecondSubFunctionValue = pChoosenVariable->getValue();
					cout<<"pSecondSubFunction = new cFunctionVariable( "<<pChoosenVariable<<
						"="<<dSecondSubFunctionValue<<" );"<<endl;
					pSecondSubFunction = new cFunctionVariable( pChoosenVariable );
				}
			}
			cout<<"pUnderFunction = new cFunctionIf( pCondition="<<pCondition<<","<<
				"pFirstSubFunction="<<pFirstSubFunction<<", pSecondSubFunction="<<pSecondSubFunction<<", NULL, &point );"<<endl;
			pUnderFunction = new cFunctionIf( pCondition, pFirstSubFunction, pSecondSubFunction, NULL, &point );
			
			if ( pFirstSubFunction ){
				pFirstSubFunction = pFirstSubFunction->clone();
			}
			if ( pSecondSubFunction ){
				pSecondSubFunction = pSecondSubFunction->clone();
			}
		}else{
			switch ( rand() % 3 ){
				case 0://set condition
				switch ( rand() % 10 ){
					case 0:{
						//set condition
						pCondition = new cConditionTrue();
						cout<<"pCondition = new conditionTrue();"<<endl;
						bConditionValue = true;
						bConditionIsPointer = true;
						cout<<"pUnderFunction->setCondition( "<<pCondition<<" );"<<endl;
						const bool bConditionSet = pUnderFunction->setCondition( pCondition );
						//check returnvalue
						if(  bConditionSet ){
							cout<<"The condition was correctly set. "<<endl;
						}else{
							cerr<<"Error: The condition couldn't be set."<<endl;
							iReturn++;
						}
					}break;
					case 1:{
						//set condition
						pCondition = &conditionTrue;
						bConditionValue = true;
						bConditionIsPointer = false;
						cout<<"pUnderFunction->setCondition( conditionTrue );"<<endl;
						const bool bConditionSet = pUnderFunction->setCondition( conditionTrue );
						//check returnvalue
						if(  bConditionSet ){
							cout<<"The condition was correctly set. "<<endl;
						}else{
							cerr<<"Error: The condition couldn't be set."<<endl;
							iReturn++;
						}
					}break;
					case 2:{
						//set condition
						pCondition = new cConditionFalse();
						cout<<"pCondition = new conditionFalse();"<<endl;
						bConditionValue = false;
						bConditionIsPointer = true;
						cout<<"pUnderFunction->setCondition( "<<pCondition<<" );"<<endl;
						const bool bConditionSet = pUnderFunction->setCondition( pCondition );
						//check returnvalue
						if(  bConditionSet ){
							cout<<"The condition was correctly set. "<<endl;
						}else{
							cerr<<"Error: The condition couldn't be set."<<endl;
							iReturn++;
						}
					}break;
					case 3:{
						//set condition
						pCondition = &conditionFalse;
						bConditionValue = false;
						bConditionIsPointer = false;
						cout<<"pUnderFunction->setCondition( conditionFalse );"<<endl;
						const bool bConditionSet = pUnderFunction->setCondition( conditionFalse );
						//check returnvalue
						if(  bConditionSet ){
							cout<<"The condition was correctly set. "<<endl;
						}else{
							cerr<<"Error: The condition couldn't be set."<<endl;
							iReturn++;
						}
					}break;
					case 4:{
						//set condition
						cout<<"pUnderFunction->setCondition( NULL );"<<endl;
						const bool bConditionSet = pUnderFunction->setCondition( NULL );
						//check returnvalue
						if(  ! bConditionSet ){
							cout<<"The condition could correctly not be set. "<<endl;
						}else{
							cerr<<"Error: The condition NULL could be set."<<endl;
							iReturn++;
						}
					}break;
					
					//delete old = false
					case 5:{
						//set condition
						pCondition = new cConditionTrue();
						cout<<"pCondition = new conditionTrue();"<<endl;
						bConditionValue = true;
						bConditionIsPointer = true;
						pOldCondition = pUnderFunction->getCondition();
						cout<<"pUnderFunction->setCondition( "<<pCondition<<", false );"<<endl;
						const bool bConditionSet = pUnderFunction->setCondition( pCondition, false );
						//check returnvalue
						if(  bConditionSet ){
							cout<<"The condition was correctly set. "<<endl;
						}else{
							cerr<<"Error: The condition couldn't be set."<<endl;
							iReturn++;
						}
					}break;
					case 6:{
						//set condition
						pCondition = new cConditionFalse();
						cout<<"pCondition = new conditionFalse();"<<endl;
						bConditionValue = false;
						bConditionIsPointer = true;
						pOldCondition = pUnderFunction->getCondition();
						cout<<"pUnderFunction->setCondition( "<<pCondition<<", false );"<<endl;
						const bool bConditionSet = pUnderFunction->setCondition( pCondition, false );
						//check returnvalue
						if(  bConditionSet ){
							cout<<"The condition was correctly set. "<<endl;
						}else{
							cerr<<"Error: The condition couldn't be set."<<endl;
							iReturn++;
						}
					}break;
					case 7:{
						//set condition
						cout<<"pUnderFunction->setCondition( NULL, false );"<<endl;
						const bool bConditionSet = pUnderFunction->setCondition( NULL, false );
						//check returnvalue
						if(  ! bConditionSet ){
							cout<<"The condition could correctly not be set. "<<endl;
						}else{
							cerr<<"Error: The condition NULL could be set."<<endl;
							iReturn++;
						}
					}break;
					//create subsubconditions
					case 8:{
						//set second subcondition
						pCondition = new cConditionNot( new cConditionTrue() );
						bConditionValue = pCondition->getValue();
						cout<<"pCondition = new cUnderFunctionNot( cConditionTrue( "<<
							pCondition->getValue()<<" ) );"<<endl;
						bConditionIsPointer = true;
						cout<<"pUnderFunction->setCondition( "<<pCondition<<" );"<<endl;
						const bool bConditionSet = pUnderFunction->setCondition( pCondition );
						//check returnvalue
						if(  bConditionSet ){
							cout<<"The condition was correctly set. "<<endl;
						}else{
							cerr<<"Error: The condition couldn't be set."<<endl;
							iReturn++;
						}
					}break;
					case 9:{
						//set second condition
						pCondition = &conditionNot;
						bConditionValue = conditionNot.getValue();
						bConditionIsPointer = false;
						cout<<"pUnderFunction->setCondition( conditionNot );"<<endl;
						const bool bConditionSet = pUnderFunction->setCondition( conditionNot );
						//check returnvalue
						if(  bConditionSet ){
							cout<<"The condition was correctly set. "<<endl;
						}else{
							cerr<<"Error: The condition couldn't be set."<<endl;
							iReturn++;
						}
					}break;
				}//end switch set condition
				if ( pOldCondition ){
					delete pOldCondition;
					pOldCondition = NULL;
				}
				break;//end case set condition
				
				case 1:{//set first subfunction
					if ( pFirstSubFunction ){
						delete pFirstSubFunction;
					}
					pFirstSubFunction = NULL;
					switch ( rand() % 3 ){
						case 0:{
							//set value subfunction
							dFirstSubFunctionValue = ((double)(rand() % (1024 ) - 512)) / 16.0;
							if ( rand() % 4 ){
								dFirstSubFunctionValue = domFunValues.round( dFirstSubFunctionValue );
							}
							cout<<"pFirstSubFunction = new cFunctionValue( "<<dFirstSubFunctionValue<<" );"<<endl;
							pFirstSubFunction = new cFunctionValue( dFirstSubFunctionValue );
						}break;
						case 1:{
							//set variable subfunction
							cFibVariable * pChoosenVariable = vecVariables[ rand() % 10 ];
							dFirstSubFunctionValue = pChoosenVariable->getValue();
							cout<<"pFirstSubFunction = new cFunctionVariable( "<<pChoosenVariable<<
								"="<<dFirstSubFunctionValue<<" );"<<endl;
							pFirstSubFunction = new cFunctionVariable( pChoosenVariable );
						}break;
						case 2:{
							//set value subfunction
							dFirstSubFunctionValue = ((double)(rand() % (1024 ) - 512)) / 16.0;
							if ( rand() % 4 ){
								dFirstSubFunctionValue = domFunValues.round( dFirstSubFunctionValue );
							}
							cFunctionValue * pFunValueTmp = new cFunctionValue( dFirstSubFunctionValue );
							cout<<"pFirstSubFunction = new cFunctionAbs( new cFunctionValue( "<<dFirstSubFunctionValue<<" ) );"<<endl;
							pFirstSubFunction = new cFunctionAbs( pFunValueTmp );
							
							delete pFunValueTmp;
							
							if ( dFirstSubFunctionValue < 0 ){
								dFirstSubFunctionValue *= -1;
							}
						}break;
					
					};//end switch choose subfunction
					cout<<"pUnderFunction->setFirstUnderFunction( *pFirstSubFunction );"<<endl;
					pUnderFunction->setFirstUnderFunction( *pFirstSubFunction );
				}break;//end switch set condition
				
				case 2:{//set second subfunction
					if ( pSecondSubFunction ){
						delete pSecondSubFunction;
					}
					pSecondSubFunction = NULL;
					switch ( rand() % 3 ){
						case 0:{
							//set value subfunction
							dSecondSubFunctionValue = ((double)(rand() % (1024 ) - 512)) / 16.0;
							if ( rand() % 4 ){
								dSecondSubFunctionValue = domFunValues.round( dSecondSubFunctionValue );
							}
							cout<<"pSecondSubFunction = new cFunctionValue( "<<dSecondSubFunctionValue<<" );"<<endl;
							pSecondSubFunction = new cFunctionValue( dSecondSubFunctionValue );
						}break;
						case 1:{
							//set variable subfunction
							cFibVariable * pChoosenVariable = vecVariables[ rand() % 10 ];
							dSecondSubFunctionValue = pChoosenVariable->getValue();
							cout<<"pSecondSubFunction = new cFunctionVariable( "<<pChoosenVariable<<
								"="<<dSecondSubFunctionValue<<" );"<<endl;
							pSecondSubFunction = new cFunctionVariable( pChoosenVariable );
						}break;
						case 2:{
							//set value subfunction
							dSecondSubFunctionValue = ((double)(rand() % (1024 ) - 512)) / 16.0;
							if ( rand() % 4 ){
								dSecondSubFunctionValue = domFunValues.round( dSecondSubFunctionValue );
							}
							cFunctionValue * pFunValueTmp = new cFunctionValue( dSecondSubFunctionValue );
							cout<<"pSecondSubFunction = new cFunctionAbs( new cFunctionValue( "<<dSecondSubFunctionValue<<" ) );"<<endl;
							pSecondSubFunction = new cFunctionAbs( pFunValueTmp );
							
							delete pFunValueTmp;
							
							if ( dSecondSubFunctionValue < 0 ){
								dSecondSubFunctionValue *= -1;
							}
						}break;
					
					};//end switch choose subfunction
					cout<<"pUnderFunction->setSecondUnderFunction( *pSecondSubFunction );"<<endl;
					pUnderFunction->setSecondUnderFunction( *pSecondSubFunction );
				}break;//end switch set condition

			};//end switch choose element to change
		}
		if ( ( pCondition != NULL ) && bConditionValue  ){
			//evalue first under function
			dCorrectValue = dFirstSubFunctionValue;
		}else{// evalue second under function
			dCorrectValue = dSecondSubFunctionValue;
		}
		
		if ( ( pCondition != NULL ) && ( pFirstSubFunction != NULL ) &&
				( pSecondSubFunction != NULL ) ){
			if ( ( ! pUnderFunction->getCondition()->isValid() ) ||
					( ! pUnderFunction->getFirstUnderFunction()->isValid() ) ||
					( ! pUnderFunction->getSecondUnderFunction()->isValid() ) ){
				//subfunction not valid -> function not valid
				bIsValid = false;
			}else{
				bIsValid = true;
			}
		}else{
			bIsValid = false;
		}

		
		//check the getValue() methode from cFunctionIf
		if ( pUnderFunction->getValue() == dCorrectValue ){
		
			cout<<"The function value is correctly "<<dCorrectValue <<" . "<<endl;
		}else{
			cerr<<"Error: The function value is "<<
				pUnderFunction->getValue() <<" but should be "<<
				dCorrectValue <<" ( condition="<<
				(bConditionValue?"true":"false")<<", first subfun="<<
				dFirstSubFunctionValue<<", second subfun="<<
				dSecondSubFunctionValue<<" )."<<endl;
			iReturn++;
		}
		if ( bConditionIsPointer ){
			//check the getCondition() methode from cFunctionIf
			if ( pUnderFunction->getCondition() == pCondition ){
			
				cout<<"The condition of the function correctly "<<
					pUnderFunction->getCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition of the function is "<<
					pUnderFunction->getCondition() <<
					" but should be "<< pCondition <<" ."<<endl;
				iReturn++;
			}
			const cFunctionIf * pUnderFunctionConst = pUnderFunction;
			if ( pUnderFunctionConst->getCondition() == pCondition ){
			
				cout<<"The condition of the const function correctly "<<
					pUnderFunctionConst->getCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition of the const function is "<<
					pUnderFunctionConst->getCondition() <<
					" but should be "<< pCondition <<" ."<<endl;
				iReturn++;
			}
		}else{
			//check the getCondition() methode from cFunctionIf
			if ( *(pUnderFunction->getCondition()) == *pCondition ){
			
				cout<<"The condition of the function correctly equal to "<<
					pUnderFunction->getCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition of the function is "<<
					pUnderFunction->getCondition() <<
					" but should be equal to "<< pCondition <<" ."<<endl;
				iReturn++;
			}
			const cFunctionIf * pUnderFunctionConst = pUnderFunction;
			if ( *(pUnderFunctionConst->getCondition()) == *pCondition ){
			
				cout<<"The condition of the const function correctly equal to "<<
					pUnderFunctionConst->getCondition() <<" . "<<endl;
			}else{
				cerr<<"Error: The condition of the const function is "<<
					pUnderFunctionConst->getCondition() <<
					" but should be equal to "<< pCondition <<" ."<<endl;
				iReturn++;
			}
		}
		//check the getFirstUnderFunction() methode from cFunctionIf
		if ( pUnderFunction->getFirstUnderFunction() ){
			if ( *(pUnderFunction->getFirstUnderFunction()) == *pFirstSubFunction ){
			
				cout<<"The second subfunction of the function correctly equal to "<<
					pUnderFunction->getFirstUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The second subfunction of the function is "<<
					pUnderFunction->getFirstUnderFunction() <<
					" but should be equal to "<< pFirstSubFunction <<" ."<<endl;
				iReturn++;
			}
		}else{//pUnderFunction->getFirstUnderFunction() == NULL
			if ( pFirstSubFunction == NULL ){
			
				cout<<"The second subfunction of the function correctly NULL . "<<endl;
			}else{
				cerr<<"Error: The second subfunction of the function is not NULL"<<
					" but should NULL ."<<endl;
				iReturn++;
			}
		}
		//check the getFirstUnderFunction() methode from cFunctionIf
		if ( pUnderFunction->getSecondUnderFunction() ){
			if ( *(pUnderFunction->getSecondUnderFunction()) == *pSecondSubFunction ){
			
				cout<<"The second subfunction of the function correctly equal to "<<
					pUnderFunction->getSecondUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The second subfunction of the function is "<<
					pUnderFunction->getSecondUnderFunction() <<
					" but should be equal to "<< pSecondSubFunction <<" ."<<endl;
				iReturn++;
			}
		}else{//pUnderFunction->getSecondUnderFunction() == NULL
			if ( pSecondSubFunction == NULL ){
			
				cout<<"The second subfunction of the function correctly NULL . "<<endl;
			}else{
				cerr<<"Error: The second subfunction of the function is not NULL"<<
					" but should NULL ."<<endl;
				iReturn++;
			}
		}
		//check the isValid() methode from cFunctionIf
		if ( pUnderFunction->isValid() == bIsValid ){
		
			cout<<"The function is correctly "<<(bIsValid?"":"not ")<<"valid . "<<endl;
		}else{
			cerr<<"Error: The function is "<<(bIsValid?"not ":"")<<"valid, but shouldn't be ."<<endl;
			iReturn++;
		}
		//check defining Fib-Element of sub and subsubfunction
		if ( pUnderFunction->getCondition() != NULL ){
			if ( pUnderFunction->getCondition()->getDefiningFibElement() == &point ){
			
				cout<<"The definig fib-element of the condition is root."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the condition is not root."<<endl;
				iReturn++;
			}
			if ( pUnderFunction->getCondition()->getNumberOfConditions() == 1 ){
				
				cConditionNot * pSubCondition = ((cConditionNot*)(pUnderFunction->getCondition()));
				
				if ( pSubCondition->getSubCondition()->getDefiningFibElement() == &point ){
				
					cout<<"The definig fib-element of the subsubcondition is root."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the subsubcondition is not root."<<endl;
					iReturn++;
				}
			}
		}
		if ( pUnderFunction->getFirstUnderFunction() != NULL ){
			if ( pUnderFunction->getFirstUnderFunction()->getDefiningFibElement() == &point ){
			
				cout<<"The definig fib-element of the first subfunction is root."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the first subfunction is not root."<<endl;
				iReturn++;
			}
			if ( pUnderFunction->getFirstUnderFunction()->getNumberOfUnderFunctions() == 1 ){
				
				cFunctionAbs * pSubFunction = ((cFunctionAbs*)(pUnderFunction->getFirstUnderFunction()));
				
				if ( pSubFunction->getUnderFunction()->getDefiningFibElement() == &point ){
				
					cout<<"The definig fib-element of the first subsubfunction is root."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the first subsubfunction is not root."<<endl;
					iReturn++;
				}
			}
		}
		if ( pUnderFunction->getSecondUnderFunction() != NULL ){
			if ( pUnderFunction->getSecondUnderFunction()->getDefiningFibElement() == &point ){
			
				cout<<"The definig fib-element of the second subfunction is root."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the second subfunction is not root."<<endl;
				iReturn++;
			}
			if ( pUnderFunction->getSecondUnderFunction()->getNumberOfUnderFunctions() == 1 ){
				
				cFunctionAbs * pSubFunction = ((cFunctionAbs*)(pUnderFunction->getSecondUnderFunction()));
				
				if ( pSubFunction->getUnderFunction()->getDefiningFibElement() == &point ){
				
					cout<<"The definig fib-element of the second subsubfunction is root."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the second subsubfunction is not root."<<endl;
					iReturn++;
				}
			}
		}
		
	}
	if ( pUnderFunction ){
		delete pUnderFunction;
		pUnderFunction = NULL;
		if ( pFirstSubFunction ){
			delete pFirstSubFunction;
		}
		if ( pSecondSubFunction ){
			delete pSecondSubFunction;
		}
	}
	
	return iReturn;
}



/**
 * This function tests the variable methods of the cFunctionIf class.
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
	cout<<"pVariableSimple1 = rootSimple1.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariableSimple1 = rootSimple1.getInputVariable( 1 );
	
	cout<<"cFunctionIf functionIf1( NULL, NULL, NULL );"<<endl;
	cFunctionIf functionIf1( NULL, NULL, NULL );
	
	cout<<"cConditionFalse functionFalse;"<<endl;
	cConditionFalse functionFalse;
	cout<<"cFunctionValue funValue1( 1 );"<<endl;
	cFunctionValue funValue1( 1 );
	cout<<"cFunctionValue funValue2( 2 );"<<endl;
	cFunctionValue funValue2( 2 );
	cout<<"cFunctionIf functionIf2( functionFalse, funValue1, funValue2 );"<<endl;
	cFunctionIf functionIf2( functionFalse, funValue1, funValue2 );

	//check the isUsedVariable() methode from cFunctionIf
	cout<<"functionIf1.isUsedVariable( pVariableSimple1 )"<<endl;
	if ( ! functionIf1.isUsedVariable( pVariableSimple1 ) ){
	
		cout<<"The variable pVariableSimple1 is correctly not used in the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableSimple1 is used in the function element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = functionIf1.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = functionIf1.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correctly no used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The ther are used variables given back. "<<endl;
		iReturn++;
	}
	cout<<"functionIf1.replaceVariable( pVariableSimple1, pVariableSimple1 );"<<endl;
	bool bVariableReplaced = functionIf1.replaceVariable( pVariableSimple1, pVariableSimple1 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	
	//check the isUsedVariable() methode from cFunctionIf
	cout<<"functionIf2.isUsedVariable( pVariableSimple1 )"<<endl;
	if ( ! functionIf2.isUsedVariable( pVariableSimple1 ) ){
	
		cout<<"The variable pVariableSimple1 is correctly not used in the function element. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableSimple1 is used in the function element. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = functionIf2.getUsedVariables(); "<<endl;
	setUsedVariables = functionIf2.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"The correctly no used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The ther are used variables given back. "<<endl;
		iReturn++;
	}
	cout<<"functionIf2.replaceVariable( pVariableSimple1, pVariableSimple1 );"<<endl;
	bVariableReplaced = functionIf2.replaceVariable( pVariableSimple1, pVariableSimple1 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	
	
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the variable methods on random objects"<<endl;

	cout<<"cPoint point;"<<endl;
	cPoint point;
	cout<<"cRoot root( &point );"<<endl;
	cRoot root( &point );
	
	cout<<"cTypeUnderFunction testTypeUnderFunction;"<<endl;
	cTypeUnderFunction testTypeUnderFunction;
	cout<<"cDomainRational domFunValues( cDomainNaturalNumberBit( 16 ), "<<
		"cDomainNaturalNumberBit( 16 ) );"<<endl;
	cDomainRational domFunValues( cDomainNaturalNumberBit( 16 ),
		cDomainNaturalNumberBit( 16 ) );
	cout<<"root.getDomains()->addDomain( testTypeUnderFunction, &domFunValues );"<<endl;
	root.getDomains()->addDomain( testTypeUnderFunction, &domFunValues );
	
	
	vector< cFibVariable * > vecVariables;
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
	cout<<"pVariable5 = root.getInputVariable( 5 );"<<endl;
	cFibVariable * pVariable5 = root.getInputVariable( 5 );
	cout<<"pVariable6 = root.getInputVariable( 6 );"<<endl;
	cFibVariable * pVariable6 = root.getInputVariable( 6 );
	cout<<"pVariable7 = root.getInputVariable( 7 );"<<endl;
	cFibVariable * pVariable7 = root.getInputVariable( 7 );
	cout<<"pVariable8 = root.getInputVariable( 8 );"<<endl;
	cFibVariable * pVariable8 = root.getInputVariable( 8 );
	cout<<"pVariable9 = root.getInputVariable( 9 );"<<endl;
	cFibVariable * pVariable9 = root.getInputVariable( 9 );
	cout<<"pVariable10 = root.getInputVariable( 10 );"<<endl;
	cFibVariable * pVariable10 = root.getInputVariable( 10 );
	
	cout<<"pVariable1(="<<pVariable1<<")->setValue( 1.0 );"<<endl;
	pVariable1->setValue( 1.0 );
	vecVariables.push_back( pVariable1 );
	cout<<"pVariable2(="<<pVariable2<<")->setValue( 2.0 );"<<endl;
	pVariable2->setValue( 2.0 );
	vecVariables.push_back( pVariable2 );
	cout<<"pVariable3(="<<pVariable3<<")->setValue( 3.0 );"<<endl;
	pVariable3->setValue( 3.0 );
	vecVariables.push_back( pVariable3 );
	cout<<"pVariable4(="<<pVariable4<<")->setValue( 4.0 );"<<endl;
	pVariable4->setValue( 4.0 );
	vecVariables.push_back( pVariable4 );
	cout<<"pVariable5(="<<pVariable5<<")->setValue( 5.5 );"<<endl;
	pVariable5->setValue( 5.5 );
	vecVariables.push_back( pVariable5 );
	cout<<"pVariable6(="<<pVariable6<<")->setValue( 4.0 );"<<endl;
	pVariable6->setValue( 4.0 );
	vecVariables.push_back( pVariable6 );
	cout<<"pVariable7(="<<pVariable7<<")->setValue( -1.0 );"<<endl;
	pVariable7->setValue( -1.0 );
	vecVariables.push_back( pVariable7 );
	cout<<"pVariable8(="<<pVariable8<<")->setValue( 2.5 );"<<endl;
	pVariable8->setValue( 2.5 );
	vecVariables.push_back( pVariable8 );
	cout<<"pVariable9(="<<pVariable9<<")->setValue( 2.51 );"<<endl;
	pVariable9->setValue( 2.51 );
	vecVariables.push_back( pVariable9 );
	cout<<"pVariable10(="<<pVariable10<<")->setValue( 2.49 );"<<endl;
	pVariable10->setValue( 2.49 );
	vecVariables.push_back( pVariable10 );
	
	cCondition * pCondition = NULL;
	bool bConditionValue = false;
	cFibVariable * pVariableCondition = NULL;
	
	cUnderFunction * pFirstSubFunction = NULL;
	double dFirstSubFunctionValue = 0.0;
	cFibVariable * pVariableFirstSubFunction = NULL;
	
	cUnderFunction * pSecondSubFunction = NULL;
	double dSecondSubFunctionValue = 0.0;
	cFibVariable * pVariableSecondSubFunction = NULL;
	
	cout<<"pUnderFunction = new cFunctionIf( NULL, NULL, NULL, NULL, &point  );"<<endl;
	cFunctionIf * pUnderFunction = new cFunctionIf( NULL, NULL, NULL, NULL, &point );
	bool bIsValid = false;
	
	set< cFibVariable* > setCorrectUsedVariables;
	
	for ( unsigned int uiIteration = 1; uiIteration <= MAX_RAND_TEST_SIZE; uiIteration++ ){
		
		cout<<endl;
		if ( (rand() % 16) == 0 ){
			//create new function
			if ( pUnderFunction ){
				delete pUnderFunction;
				pUnderFunction = NULL;
				
				if ( pCondition ){
					delete pCondition;
					pCondition = NULL;
				}
				bConditionValue = false;
				pVariableCondition = NULL;
				
				if ( pFirstSubFunction ){
					delete pFirstSubFunction;
					pFirstSubFunction = NULL;
				}
				dFirstSubFunctionValue = 0.0;
				pVariableFirstSubFunction = NULL;
				
				if ( pSecondSubFunction ){
					delete pSecondSubFunction;
					pSecondSubFunction = NULL;
				}
				dSecondSubFunctionValue = 0.0;
				pVariableSecondSubFunction = NULL;
			}
			if ( rand() % 4 ){
				if ( rand() % 4 == 0 ){
					pCondition = new cConditionGreater(
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ),
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ) );
					bConditionValue = pCondition->getValue();
					cout<<"pCondition = new cConditionGreater( "<<
						" cFunctionValue , cFunctionValue );"<<endl;
					pVariableCondition = NULL;
				}else{
					const size_t uiChoosenVariable = rand() % vecVariables.size();
					pCondition = new cConditionGreater(
						new cFunctionValue( domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 ) ),
						new cFunctionVariable( vecVariables[ uiChoosenVariable ] ) );
					bConditionValue = pCondition->getValue();
					cout<<"pCondition = new cConditionGreater( "<<
						"cFunctionValue, cFunctionVariable( pVariable"<<uiChoosenVariable<<"="<<
						vecVariables[ uiChoosenVariable ]<<") );"<<endl;
					pVariableCondition = vecVariables[ uiChoosenVariable ];
				}
			}
			if ( rand() % 4 ){
				if ( rand() % 2 ){
					//set value subfunction
					dFirstSubFunctionValue = domFunValues.round(
						((double)(rand() % (1024 ) - 512)) / 16.0 );
					cout<<"pFirstSubFunction = new cFunctionValue( "<<dFirstSubFunctionValue<<" );"<<endl;
					pFirstSubFunction = new cFunctionValue( dFirstSubFunctionValue );
				}else{
					//set variable subfunction
					pVariableFirstSubFunction = vecVariables[ rand() % 10 ];
					dFirstSubFunctionValue = pVariableFirstSubFunction->getValue();
					cout<<"pFirstSubFunction = new cFunctionVariable( "<<pVariableFirstSubFunction<<
						"="<<dFirstSubFunctionValue<<" );"<<endl;
					pFirstSubFunction = new cFunctionVariable( pVariableFirstSubFunction );
				}
			}
			if ( rand() % 4 ){
				if ( rand() % 2 ){
					//set value subfunction
					dSecondSubFunctionValue = domFunValues.round(
						((double)(rand() % (1024 ) - 512)) / 16.0 );
					cout<<"pSecondSubFunction = new cFunctionValue( "<<dSecondSubFunctionValue<<" );"<<endl;
					pSecondSubFunction = new cFunctionValue( dSecondSubFunctionValue );
				}else{
					//set variable subfunction
					pVariableSecondSubFunction = vecVariables[ rand() % 10 ];
					dSecondSubFunctionValue = pVariableSecondSubFunction->getValue();
					cout<<"pSecondSubFunction = new cFunctionVariable( "<<pVariableSecondSubFunction<<
						"="<<dSecondSubFunctionValue<<" );"<<endl;
					pSecondSubFunction = new cFunctionVariable( pVariableSecondSubFunction );
				}
			}
			cout<<"pUnderFunction = new cFunctionIf( pCondition="<<pCondition<<","
				"pFirstSubFunction="<<pFirstSubFunction<<", "<<
				"pSecondSubFunction="<<pSecondSubFunction<<", NULL, &point  );"<<endl;
			pUnderFunction = new cFunctionIf( pCondition, pFirstSubFunction, pSecondSubFunction, NULL, &point );
			
			if ( pCondition ){
				pCondition = pCondition->clone();
			}
			if ( pFirstSubFunction ){
				pFirstSubFunction = pFirstSubFunction->clone();
			}
			if ( pSecondSubFunction ){
				pSecondSubFunction = pSecondSubFunction->clone();
			}
		}else if ( rand() % 2 ){//change subelement
			
			if ( rand() % 4 ){
				switch ( rand() % 3 ){
					case 0:{//change condition
						const size_t uiChoosenVariable = rand() % vecVariables.size();
						if ( pCondition ){
							delete pCondition;
							pCondition = NULL;
						}
						pCondition =  new cConditionGreater(
							new cFunctionVariable( vecVariables[ uiChoosenVariable ] ),
							new cFunctionValue( domFunValues.round(
								((double)(rand() % (256 * 256))) / 256.0 ) ) );
						bConditionValue = pCondition->getValue();
						cout<<"pCondition = new cConditionGreater( "<<
							"cFunctionVariable( pVariable"<<uiChoosenVariable+1<<"="<<
							vecVariables[ uiChoosenVariable ]<<"), cFunctionValue );"<<endl;
						cout<<"pUnderFunction->setCondition( *pCondition );"<<endl;
						pUnderFunction->setCondition( *pCondition );
						pVariableCondition = vecVariables[ uiChoosenVariable ];
					}break;
					case 1:{//set first subfunction to variable
						const size_t uiChoosenVariable = rand() % vecVariables.size();
						if ( pFirstSubFunction ){
							delete pFirstSubFunction;
							pFirstSubFunction = NULL;
						}
						pFirstSubFunction = new cFunctionVariable( vecVariables[ uiChoosenVariable ] );
						dFirstSubFunctionValue = vecVariables[ uiChoosenVariable ]->getValue();
						cout<<"pFirstSubFunction = new cFunctionVariable( pVariable"<<uiChoosenVariable+1<<"="<<
							vecVariables[ uiChoosenVariable ]<<");"<<endl;
						cout<<"pUnderFunction->setFirstUnderFunction( *pFirstSubFunction );"<<endl;
						pUnderFunction->setFirstUnderFunction( *pFirstSubFunction );
						pVariableFirstSubFunction = vecVariables[ uiChoosenVariable ];
					}break;
					case 2:{//set second subfunction to variable
						const size_t uiChoosenVariable = rand() % vecVariables.size();
						if ( pSecondSubFunction ){
							delete pSecondSubFunction;
							pSecondSubFunction = NULL;
						}
						pSecondSubFunction = new cFunctionVariable( vecVariables[ uiChoosenVariable ] );
						dSecondSubFunctionValue = vecVariables[ uiChoosenVariable ]->getValue();
						cout<<"pSecondSubFunction = new cFunctionVariable( pVariable"<<uiChoosenVariable+1<<"="<<
							vecVariables[ uiChoosenVariable ]<<");"<<endl;
						cout<<"pUnderFunction->setSecondUnderFunction( *pSecondSubFunction );"<<endl;
						pUnderFunction->setSecondUnderFunction( *pSecondSubFunction );
						pVariableSecondSubFunction = vecVariables[ uiChoosenVariable ];
					}break;
				}//end switch change subelement
			}else{//change to value
				switch ( rand() % 3 ){
					case 0:{//change condition
						if ( pCondition ){
							delete pCondition;
							pCondition = NULL;
						}
						pCondition = new cConditionGreater(
							new cFunctionValue( domFunValues.round(
								((double)(rand() % (256 * 256))) / 256.0 ) ),
							new cFunctionValue( domFunValues.round(
								((double)(rand() % (256 * 256))) / 256.0 ) ) );
						cout<<"pCondition = new cConditionGreater( "<<
							" cFunctionValue , cFunctionValue );"<<endl;
						bConditionValue = pCondition->getValue();
						cout<<"pUnderFunction->setCondition( *pCondition );"<<endl;
						pUnderFunction->setCondition( *pCondition );
						pVariableCondition = NULL;
					}break;
					case 1:{//set first subfunction to value
						if ( pFirstSubFunction ){
							delete pFirstSubFunction;
							pFirstSubFunction = NULL;
						}
						dFirstSubFunctionValue = domFunValues.round(
								((double)(rand() % (256 * 256))) / 256.0 );
						pFirstSubFunction = new cFunctionValue( dFirstSubFunctionValue );
						cout<<"pFirstSubFunction = new cFunctionValue( "<<dFirstSubFunctionValue<<" );"<<endl;
						cout<<"pUnderFunction->setFirstUnderFunction( *pFirstSubFunction );"<<endl;
						pUnderFunction->setFirstUnderFunction( *pFirstSubFunction );
						pVariableFirstSubFunction = NULL;
					}break;
					case 2:{//set second subfunction to variable
						//set second subfunction to value
						if ( pSecondSubFunction ){
							delete pSecondSubFunction;
							pSecondSubFunction = NULL;
						}
						dSecondSubFunctionValue = domFunValues.round(
							((double)(rand() % (256 * 256))) / 256.0 );
						pSecondSubFunction = new cFunctionValue( dSecondSubFunctionValue );
						cout<<"pSecondSubFunction = new cFunctionValue( "<<dSecondSubFunctionValue<<" );"<<endl;
						cout<<"pUnderFunction->setSecondUnderFunction( *pSecondSubFunction );"<<endl;
						pUnderFunction->setSecondUnderFunction( *pSecondSubFunction );
						pVariableSecondSubFunction = NULL;
					}break;
				}//end switch change subelement
			}
		}else{
			if ( rand() % 2 ){
				if ( rand() % 4 ){
					//replace used variable
					if ( setCorrectUsedVariables.empty() ){
						//no variable to replace -> skip
						continue;
					}
					cout<<endl<<"replace used variable: "<<endl;
					
					//choose variable to replace
					size_t uiVariableToReplace = rand() % setCorrectUsedVariables.size();
					set< cFibVariable* >::const_iterator itrToReplaceVariable =
						setCorrectUsedVariables.begin();
					for ( ; ( itrToReplaceVariable != setCorrectUsedVariables.end() ) &&
							( uiVariableToReplace != 0 );
							itrToReplaceVariable++, uiVariableToReplace-- ){
						//nothing to do
					}
					const size_t uiVariableToReplaceWith = rand() % vecVariables.size();
					
					cout<<"pUnderFunction->replaceVariable( "<<(*itrToReplaceVariable)<<
						", "<< vecVariables[ uiVariableToReplaceWith ]<<" );"<<endl;
					const bool bVariableReplaced = pUnderFunction->replaceVariable(
						(*itrToReplaceVariable), vecVariables[ uiVariableToReplaceWith ] );
					if ( bVariableReplaced ){
					
						cout<<"The variable was correctly replaced. "<<endl;
					}else{
						cerr<<"Error: The variable was not replaced. "<<endl;
						iReturn++;
					}
					//update values
					if ( pVariableCondition == (*itrToReplaceVariable) ){
						pCondition->replaceVariable( (*itrToReplaceVariable),
							vecVariables[ uiVariableToReplaceWith ] );
						bConditionValue = pCondition->getValue();
						pVariableCondition = vecVariables[ uiVariableToReplaceWith ];
					}
					if ( pVariableFirstSubFunction == (*itrToReplaceVariable) ){
						pFirstSubFunction->replaceVariable( (*itrToReplaceVariable),
							vecVariables[ uiVariableToReplaceWith ] );
						dFirstSubFunctionValue = pFirstSubFunction->getValue();
						pVariableFirstSubFunction = vecVariables[ uiVariableToReplaceWith ];
					}
					if ( pVariableSecondSubFunction == (*itrToReplaceVariable) ){
						pSecondSubFunction->replaceVariable( (*itrToReplaceVariable),
							vecVariables[ uiVariableToReplaceWith ] );
						dSecondSubFunctionValue = pSecondSubFunction->getValue();
						pVariableSecondSubFunction = vecVariables[ uiVariableToReplaceWith ];
					}
					
				}else if ( rand() % 2 ){
					//replace not used variable
					if ( setCorrectUsedVariables.empty() ){
						//no variable to replace -> skip
						continue;
					}
					//choose variable to replace
					size_t uiVariableToReplace = rand() % vecVariables.size();
					if ( setCorrectUsedVariables.find( vecVariables[ uiVariableToReplace ] )
							!= setCorrectUsedVariables.end() ){
						//variable used skip
						continue;
					}
					cout<<endl<<"replace not used variable: "<<endl;
					const size_t uiVariableToReplaceWith = rand() % vecVariables.size();
					
					cout<<"pUnderFunction->replaceVariable( "<<
						vecVariables[ uiVariableToReplace ]<<", "<<
						vecVariables[ uiVariableToReplaceWith ]<<" );"<<endl;
					const bool bVariableReplaced = pUnderFunction->replaceVariable(
						vecVariables[ uiVariableToReplace ], vecVariables[ uiVariableToReplaceWith ] );
					if ( bVariableReplaced ){
					
						cout<<"The variable was correctly replaced. "<<endl;
					}else{
						cerr<<"Error: The variable was not replaced. "<<endl;
						iReturn++;
					}
				
				}else{//replace on NULL variable
					
					if ( rand() % 2 ){
						//replace an NULL variable
						cout<<endl<<"replace an NULL variable: "<<endl;
						//choose variable to replace
						const size_t uiVariableToReplaceWith = rand() % vecVariables.size();
						
						cout<<"pUnderFunction->replaceVariable( NULL,"<<
							vecVariables[ uiVariableToReplaceWith ]<<" );"<<endl;
						const bool bVariableReplaced = pUnderFunction->replaceVariable(
							NULL, vecVariables[ uiVariableToReplaceWith ] );
						if ( ! bVariableReplaced ){
						
							cout<<"The variable was correctly not replaced. "<<endl;
						}else{
							cerr<<"Error: The variable was replaced. "<<endl;
							iReturn++;
						}
							
					}else{
						//replace with an NULL variable
						cout<<endl<<"replace with an NULL variable: "<<endl;
						//choose variable to replace
						const size_t uiVariableToReplace = rand() % vecVariables.size();
						
						cout<<"pUnderFunction->replaceVariable( "<<
							vecVariables[ uiVariableToReplace ]<<", NULL );"<<endl;
						const bool bVariableReplaced = pUnderFunction->replaceVariable(
							vecVariables[ uiVariableToReplace ], NULL );
						if ( ! bVariableReplaced ){
						
							cout<<"The variable was correctly not replaced. "<<endl;
						}else{
							cerr<<"Error: The variable was replaced. "<<endl;
							iReturn++;
						}
					}//end if replace NULL
				}//end if replave
			}else{
				if ( setCorrectUsedVariables.empty() ){
					//no variables to change -> skip
					continue;
				}
				//change used variable value
				cout<<endl<<"change used variable value: "<<endl;
				
				//choose variable to replace
				size_t uiVariableToReplace = rand() % setCorrectUsedVariables.size();
				set< cFibVariable* >::const_iterator itrToReplaceChange =
					setCorrectUsedVariables.begin();
				for ( ; ( itrToReplaceChange != setCorrectUsedVariables.end() ) &&
						( uiVariableToReplace != 0 );
						itrToReplaceChange++, uiVariableToReplace-- ){
					//nothing to do
				}
				(*itrToReplaceChange)->setValue( ((double)(rand() % (256 * 256))) / 256.0 );
				//update values
				if ( pVariableCondition == (*itrToReplaceChange) ){
					bConditionValue = pCondition->getValue();
				}
				if ( pVariableFirstSubFunction == (*itrToReplaceChange) ){
					dFirstSubFunctionValue = pFirstSubFunction->getValue();
				}
				if ( pVariableSecondSubFunction == (*itrToReplaceChange) ){
					dSecondSubFunctionValue = pSecondSubFunction->getValue();
				}
			}
		}
		setCorrectUsedVariables.clear();
		if ( pVariableCondition ){
			setCorrectUsedVariables.insert( pVariableCondition );
		}
		if ( pVariableFirstSubFunction ){
			setCorrectUsedVariables.insert( pVariableFirstSubFunction );
		}
		if ( pVariableSecondSubFunction ){
			setCorrectUsedVariables.insert( pVariableSecondSubFunction );
		}
		
		if ( ( pCondition != NULL ) &&
				( pFirstSubFunction != NULL ) && ( pSecondSubFunction != NULL ) ){
			bIsValid = true;
		}else{
			bIsValid = false;
		}
		
		//check the isUsedVariable() methode from cFunctionIf
		for ( vector< cFibVariable * >::const_iterator itrVariable = vecVariables.begin();
				itrVariable != vecVariables.end(); itrVariable++ ){
			
			const bool bShouldBeUsedVariable = setCorrectUsedVariables.find(
					*itrVariable ) != setCorrectUsedVariables.end();
			
			cout<<"pUnderFunction->isUsedVariable( "<<(*itrVariable)<<" )"<<endl;
			if ( pUnderFunction->isUsedVariable( *itrVariable ) == bShouldBeUsedVariable ){
			
				cout<<"The variable "<<(*itrVariable)<<" is correctly "<<
					(bShouldBeUsedVariable?"":"not ")<<"used in the function element. "<<endl;
			}else{
				cerr<<"Error: The variable "<<(*itrVariable)<<" is "<<
					(bShouldBeUsedVariable?"not ":"")<<"used in the function element. "<<endl;
				iReturn++;
			}
		}
		//check getUsedVariables()
		cout<<"setUsedVariables = pUnderFunction->getUsedVariables(); "<<endl;
		set<cFibVariable*> setUsedVariables = pUnderFunction->getUsedVariables();
		if ( setUsedVariables == setCorrectUsedVariables ){
		
			cout<<"The correct used variables wher given back. "<<endl;
		}else{
			cerr<<"Error: Not correct used variables wher given back. "<<endl;
			setCorrectUsedVariables = setUsedVariables;
			iReturn++;
		}
		
		//check the getValue() methode from cFunctionIf
		double dCorrectValue = 0.0;
		if ( ( pCondition != NULL ) && bConditionValue  ){
			//evalue first under function
			dCorrectValue = dFirstSubFunctionValue;
		}else{// evalue second under function
			dCorrectValue = dSecondSubFunctionValue;
		}
		if ( pUnderFunction->getValue() == dCorrectValue ){
	
			cout<<"The function value is correctly "<<
				pUnderFunction->getValue() <<" . "<<endl;
		}else{
			cerr<<"Error: The function value is "<<
				pUnderFunction->getValue() <<" but should be "<<
				dCorrectValue <<" ( condition="<<
				(bConditionValue?"true":"false")<<", first subfun="<<
				dFirstSubFunctionValue<<", second subfun="<<
				dSecondSubFunctionValue<<" )."<<endl;
			iReturn++;
		}
		
		//check the isValid() methode from cFunctionIf
		if ( pUnderFunction->isValid() == bIsValid ){
		
			cout<<"The function is correctly "<<(bIsValid?"":"not ")<<"valid . "<<endl;
		}else{
			cerr<<"Error: The function is "<<(bIsValid?"not ":"")<<"valid ."<<endl;
			iReturn++;
			
			bIsValid = pUnderFunction->isValid();
		}
	}
	if ( pUnderFunction ){
		delete pUnderFunction;
		pUnderFunction = NULL;
		if ( pCondition ){
			delete pCondition;
			pCondition = NULL;
		}
		if ( pFirstSubFunction ){
			delete pFirstSubFunction;
			pFirstSubFunction = NULL;
		}
		if ( pSecondSubFunction ){
			delete pSecondSubFunction;
			pSecondSubFunction = NULL;
		}
	}
	
	
	return iReturn;
}



/**
 * This function tests the variable methods of the cFunctionIf class.
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the defining Fib-element"<<endl;
	
	cout<<"cFunctionIf functionIf1( NULL, NULL, NULL );"<<endl;
	cFunctionIf functionIf1( NULL, NULL, NULL );
	
	cFunctionIf functionIfCorrect( NULL, NULL, NULL );
	
	cFibElement * pDefiningFibElement = NULL;
	//check the getDefiningFibElement() methode from cFunctionIf
	if ( functionIf1.getDefiningFibElement() == pDefiningFibElement ){
	
		cout<<"The function defining Fib-element is correctly "<<
			functionIf1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The function defining Fib-element is "<<
			functionIf1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( functionIf1, "functionIf1", functionIfCorrect, "correct function" );
	
	cPoint pointDef1;
	cout<<"functionIf1.setDefiningFibElement( &pointDef1 );"<<endl;
	functionIf1.setDefiningFibElement( &pointDef1 );
	pDefiningFibElement = &pointDef1;
	//check the getDefiningFibElement() methode from cFunctionIf
	if ( functionIf1.getDefiningFibElement() == pDefiningFibElement ){
	
		cout<<"The function defining Fib-element is correctly "<<
			functionIf1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The function defining Fib-element is "<<
			functionIf1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( functionIf1, "functionIf1", functionIfCorrect, "correct function" );
	
	cout<<"functionIf1.setDefiningFibElement( &pointDef1 );"<<endl;
	functionIf1.setDefiningFibElement( &pointDef1 );
	pDefiningFibElement = &pointDef1;
	//check the getDefiningFibElement() methode from cFunctionIf
	if ( functionIf1.getDefiningFibElement() == pDefiningFibElement ){
	
		cout<<"The function defining Fib-element is correctly "<<
			functionIf1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The function defining Fib-element is "<<
			functionIf1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	iReturn += testCompareTwoEqualObjects( functionIf1, "functionIf1", functionIfCorrect, "correct function" );
	
	
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the defining Fib-element on random functions"<<endl;
	
	cout<<"cPoint point;"<<endl;
	cPoint point;
	cout<<"cRoot root( &point );"<<endl;
	cRoot root( &point );
	
	cout<<"cTypeUnderFunction testTypeUnderFunction;"<<endl;
	cTypeUnderFunction testTypeUnderFunction;
	cout<<"cDomainRational domFunValues( cDomainNaturalNumberBit( 16 ), "<<
		"cDomainNaturalNumberBit( 16 ) );"<<endl;
	cDomainRational domFunValues( cDomainNaturalNumberBit( 16 ),
		cDomainNaturalNumberBit( 16 ) );
	cout<<"root.getDomains()->addDomain( testTypeUnderFunction, &domFunValues );"<<endl;
	root.getDomains()->addDomain( testTypeUnderFunction, &domFunValues );
	
	cout<<"cFunctionValue funSubValue1( 1 );"<<endl;
	cFunctionValue funSubValue1( 1 );
	cout<<"cConditionGreater conditionGreater( funSubValue1, funSubValue1 );"<<endl;
	cConditionGreater conditionGreater( funSubValue1, funSubValue1 );
	
	cout<<"cFunctionValue funSubValue2( 2 );"<<endl;
	cFunctionValue funSubValue2( 2 );
	cout<<"cFunctionAbs functionAbs( &funSubValue2 );"<<endl;
	cFunctionAbs functionAbs( &funSubValue2 );
	
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	cout<<"cRoot root1( &point1 );"<<endl;
	cRoot root1( &point1 );
	cout<<"cDomainNaturalNumberBit domIntegerBit8( 8 );"<<endl;
	cDomainNaturalNumberBit domIntegerBit8( 8 );
	cout<<"root1.getDomains()->addDomain( testTypeUnderFunction, &domIntegerBit8 );"<<endl;
	root1.getDomains()->addDomain( testTypeUnderFunction, &domIntegerBit8 );
	
	
	cout<<"cPoint point2;"<<endl;
	cPoint point2;
	
	cCondition * pCondition = NULL;
	bool bConditionValue = false;
	
	cUnderFunction * pFirstSubFunction = NULL;
	double dFirstSubFunctionValue = false;
	
	cUnderFunction * pSecondSubFunction = NULL;
	double dSecondSubFunctionValue = false;
	
	pDefiningFibElement = &point;
	cout<<"pUnderFunction = new cFunctionIf( NULL, NULL, NULL, NULL, &point="<<
		pDefiningFibElement<<" );"<<endl;
	cFunctionIf * pUnderFunction = new cFunctionIf( NULL, NULL, NULL, NULL, pDefiningFibElement );
	bool bIsValid = false;
	
	for ( unsigned int uiIteration = 1; uiIteration <= MAX_RAND_TEST_SIZE; uiIteration++ ){
		
		cout<<endl;
		if ( (rand() % 16) == 0 ){
			//create new function
			if ( pUnderFunction ){
				delete pUnderFunction;
				pUnderFunction = NULL;
				
				pCondition = NULL;
				bConditionValue = false;
				
				if ( pFirstSubFunction && ( pFirstSubFunction != &functionAbs ) ){
					delete pFirstSubFunction;
				}
				pFirstSubFunction = NULL;
				dFirstSubFunctionValue = 0;
				
				if ( pSecondSubFunction && ( pSecondSubFunction != &functionAbs ) ){
					delete pSecondSubFunction;
				}
				pSecondSubFunction = NULL;
				dSecondSubFunctionValue = 0;
			}
			if ( rand() % 4 ){
				pCondition = new cConditionGreater(
					new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) ),
					new cFunctionValue( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) ) );
				bConditionValue = pCondition->getValue();
				cout<<"pCondition = new cConditionGreater( "<<
					" cFunctionValue , cFunctionValue );"<<endl;
			}
			if ( rand() % 4 ){
				//set value subfunction
				dFirstSubFunctionValue = domFunValues.round(
					((double)(rand() % (1024 ) - 512)) / 16.0 );
				cout<<"pFirstSubFunction = new cFunctionValue( "<<dFirstSubFunctionValue<<" );"<<endl;
				pFirstSubFunction = new cFunctionValue( dFirstSubFunctionValue );
			}
			if ( rand() % 4 ){
				//set value subfunction
				dSecondSubFunctionValue = domFunValues.round(
					((double)(rand() % (1024 ) - 512)) / 16.0 );
				cout<<"pSecondSubFunction = new cFunctionValue( "<<dSecondSubFunctionValue<<" );"<<endl;
				pSecondSubFunction = new cFunctionValue( dSecondSubFunctionValue );
			}
			
			switch ( rand() % 4 ){
				//choose defining fib-element
				case 0:
					pDefiningFibElement = &point;
				break;
				case 1:
					pDefiningFibElement = &point1;
				break;
				case 2:
					pDefiningFibElement = &point2;
				break;
				case 3:
					pDefiningFibElement = NULL;
				break;
			};//end switch choose defining fib-element
			cout<<"pUnderFunction = new cFunctionIf( pCondition="<<pCondition<<
				", pFirstSubFunction="<<pFirstSubFunction<<
				", pSecondSubFunction="<<pSecondSubFunction<<", NULL, "<<
				pDefiningFibElement<<"  );"<<endl;
			pUnderFunction = new cFunctionIf( pCondition, pFirstSubFunction, pSecondSubFunction, NULL, pDefiningFibElement );
			
			if ( pFirstSubFunction ){
				pFirstSubFunction = pFirstSubFunction->clone();
			}
			if ( pSecondSubFunction ){
				pSecondSubFunction = pSecondSubFunction->clone();
			}
		}else{
			switch ( rand() % 7 ){
				//create subsubfunctions
				case 0:{
					//set first subfunction
					cFunctionValue funSubValue1( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					cFunctionValue funSubValue2( domFunValues.round(
						((double)(rand() % (256 * 256))) / 256.0 ) );
					pCondition = new cConditionGreater ( funSubValue1, funSubValue2 );
					bConditionValue = pCondition->getValue();
					cout<<"pCondition = new cConditionGreater( cFunctionValue( "<<
						funSubValue1.getValue()<<" ), cFunctionValue( "<<
						funSubValue2.getValue()<<" ) );"<<endl;
					cout<<"pUnderFunction->setCondition( "<<pCondition<<" );"<<endl;
					pUnderFunction->setCondition( pCondition );
				}break;
				case 1:{
					//set second subfunction
					if ( pFirstSubFunction && ( pFirstSubFunction != &functionAbs ) ){
						delete pFirstSubFunction;
					}
					dFirstSubFunctionValue = domFunValues.round(
						((double)(rand() % (1024 ) - 512)) / 16.0 );
					cFunctionValue * pFunValueTmp = new cFunctionValue( dFirstSubFunctionValue );
					cout<<"pFirstSubFunction = new cFunctionAbs( new cFunctionValue( "<<dFirstSubFunctionValue<<" ) );"<<endl;
					pFirstSubFunction = new cFunctionAbs( pFunValueTmp );
					
					delete pFunValueTmp;
					
					if ( dFirstSubFunctionValue < 0 ){
						dFirstSubFunctionValue *= -1;
					}
					cout<<"pUnderFunction->setFirstUnderFunction( *"<<pFirstSubFunction<<" );"<<endl;
					pUnderFunction->setFirstUnderFunction( *pFirstSubFunction );
				}break;
				case 2:{
					//set second subfunction
					if ( pSecondSubFunction && ( pSecondSubFunction != &functionAbs ) ){
						delete pSecondSubFunction;
					}
					dSecondSubFunctionValue = domFunValues.round(
						((double)(rand() % (1024 ) - 512)) / 16.0 );
					cFunctionValue * pFunValueTmp = new cFunctionValue( dSecondSubFunctionValue );
					cout<<"pSecondSubFunction = new cFunctionAbs( new cFunctionValue( "<<dSecondSubFunctionValue<<" ) );"<<endl;
					pSecondSubFunction = new cFunctionAbs( pFunValueTmp );
					
					delete pFunValueTmp;
					
					if ( dSecondSubFunctionValue < 0 ){
						dSecondSubFunctionValue *= -1;
					}
					cout<<"pUnderFunction->setSecondUnderFunction( *"<<pSecondSubFunction<<" );"<<endl;
					pUnderFunction->setSecondUnderFunction( *pSecondSubFunction );
				}break;
				case 3:{
					//set first subfunction
					pCondition = &conditionGreater;
					bConditionValue = conditionGreater.getValue();
					cout<<"pUnderFunction->setCondition( conditionGreater );"<<endl;
					pUnderFunction->setCondition( conditionGreater );
				}break;
				case 4:{
					//set first subfunction
					if ( pFirstSubFunction && ( pFirstSubFunction != &functionAbs ) ){
						delete pFirstSubFunction;
					}
					pFirstSubFunction = &functionAbs;
					dFirstSubFunctionValue = functionAbs.getValue();
					cout<<"pUnderFunction->setFirstUnderFunction( functionAbs );"<<endl;
					pUnderFunction->setFirstUnderFunction( functionAbs );
				}break;
				case 5:{
					//set second subfunction
					if ( pSecondSubFunction && ( pSecondSubFunction != &functionAbs ) ){
						delete pSecondSubFunction;
					}
					pSecondSubFunction = &functionAbs;
					dSecondSubFunctionValue = functionAbs.getValue();
					cout<<"pUnderFunction->setSecondUnderFunction( functionAbs );"<<endl;
					pUnderFunction->setSecondUnderFunction( functionAbs );
				}break;
				case 6:{
					//set defining fib element
					switch ( rand() % 4 ){
						//choose defining fib-element
						case 0:
							pDefiningFibElement = &point;
						break;
						case 1:
							pDefiningFibElement = &point1;
						break;
						case 2:
							pDefiningFibElement = &point2;
						break;
						case 3:
							pDefiningFibElement = NULL;
						break;
					};//end switch choose defining fib-element
					const bool bCheckValues = rand() % 2;
					cout<<"pUnderFunction->setDefiningFibElement( "<<pDefiningFibElement<<", "<<
						(bCheckValues?"true":"false")<<" );"<<endl;
					pUnderFunction->setDefiningFibElement( pDefiningFibElement, bCheckValues );
					if ( bCheckValues ){
						if ( pDefiningFibElement == &point1 ){
							//round to correct values
							dFirstSubFunctionValue  = domIntegerBit8.round( dFirstSubFunctionValue );
							dSecondSubFunctionValue = domIntegerBit8.round( dSecondSubFunctionValue );
						}
					}
				}break;
			}
		}
		if ( ( pCondition != NULL ) &&
				( pFirstSubFunction != NULL ) && ( pSecondSubFunction != NULL ) ){
			bIsValid = pUnderFunction->getCondition()->isValid() &&
				pUnderFunction->getFirstUnderFunction()->isValid() &&
				pUnderFunction->getSecondUnderFunction()->isValid();
		}else{
			bIsValid = false;
		}
		
		//check the getValue() methode from cFunctionIf
		double dCorrectValue = 0.0;
		if ( ( pCondition != NULL ) && bConditionValue  ){
			//evalue first under function
			dCorrectValue = dFirstSubFunctionValue;
		}else{// evalue second under function
			dCorrectValue = dSecondSubFunctionValue;
		}
		//check the getValue() methode from cFunctionIf
		if ( pUnderFunction->getValue() == dCorrectValue ){
	
			cout<<"The function value is correctly "<<
				pUnderFunction->getValue() <<" . "<<endl;
		}else{
			cerr<<"Error: The function value is "<<
				pUnderFunction->getValue() <<" but should be "<<
				dCorrectValue <<" ( condition="<<
				(bConditionValue?"true":"false")<<", first subfun="<<
				dFirstSubFunctionValue<<", second subfun="<<
				dSecondSubFunctionValue<<" )."<<endl;
			iReturn++;
		}
		//check the isValid() methode from cFunctionIf
		if ( pUnderFunction->isValid() == bIsValid ){
		
			cout<<"The function is correctly "<<(bIsValid?"":"not ")<<"valid . "<<endl;
		}else{
			cerr<<"Error: The function is "<<(bIsValid?"not ":"")<<"valid ."<<endl;
			iReturn++;
		}
		//check defining Fib-Element of sub and subsubfunction
		if ( pUnderFunction->getCondition() != NULL ){
			if ( pUnderFunction->getCondition()->getDefiningFibElement() == pDefiningFibElement ){
			
				cout<<"The definig fib-element of the condition is root."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the condition is not root."<<endl;
				iReturn++;
			}
			if ( pUnderFunction->getCondition()->getNumberOfConditions() == 2 ){
				
				cConditionGreater * pSubCondition = ((cConditionGreater*)(pUnderFunction->getCondition()));
				
				if ( pSubCondition->getFirstSubFunction()->getDefiningFibElement() == pDefiningFibElement ){
				
					cout<<"The definig fib-element of the conditions first subfunction is root."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the conditions first subfunction is not root."<<endl;
					iReturn++;
				}
				if ( pSubCondition->getSecondSubFunction()->getDefiningFibElement() == pDefiningFibElement ){
				
					cout<<"The definig fib-element of the conditions second subfunction is root."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the conditions second subfunction is not root."<<endl;
					iReturn++;
				}
			}
		}
		if ( pUnderFunction->getFirstUnderFunction() != NULL ){
			if ( pUnderFunction->getFirstUnderFunction()->getDefiningFibElement() == pDefiningFibElement ){
			
				cout<<"The definig fib-element of the first subfunction is root."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the first subfunction is not root."<<endl;
				iReturn++;
			}
			if ( pUnderFunction->getFirstUnderFunction()->getNumberOfUnderFunctions() == 1 ){
				
				cFunctionAbs * pSubFunction = ((cFunctionAbs*)(pUnderFunction->getFirstUnderFunction()));
				
				if ( pSubFunction->getUnderFunction()->getDefiningFibElement() == pDefiningFibElement ){
				
					cout<<"The definig fib-element of the first subsubfunction is root."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the first subsubfunction is not root."<<endl;
					iReturn++;
				}
			}
		}
		if ( pUnderFunction->getSecondUnderFunction() != NULL ){
			if ( pUnderFunction->getSecondUnderFunction()->getDefiningFibElement() == pDefiningFibElement ){
			
				cout<<"The definig fib-element of the second subfunction is root."<<endl;
			}else{
				cerr<<"Error: The definig fib-element of the second subfunction is not root."<<endl;
				iReturn++;
			}
			if ( pUnderFunction->getSecondUnderFunction()->getNumberOfUnderFunctions() == 1 ){
				
				cFunctionAbs * pSubFunction = ((cFunctionAbs*)(pUnderFunction->getSecondUnderFunction()));
				
				if ( pSubFunction->getUnderFunction()->getDefiningFibElement() == pDefiningFibElement ){
				
					cout<<"The definig fib-element of the second subsubfunction is root."<<endl;
				}else{
					cerr<<"Error: The definig fib-element of the second subsubfunction is not root."<<endl;
					iReturn++;
				}
			}
		}
	}
	if ( pUnderFunction ){
		delete pUnderFunction;
		pUnderFunction = NULL;
		if ( pFirstSubFunction && ( pFirstSubFunction != &functionAbs ) ){
			delete pFirstSubFunction;
			pFirstSubFunction = NULL;
		}
		if ( pSecondSubFunction && ( pSecondSubFunction != &functionAbs ) ){
			delete pSecondSubFunction;
			pSecondSubFunction = NULL;
		}
	}
	


	return iReturn;
}











