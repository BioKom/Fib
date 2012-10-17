/**
 * @file tFunctionOneValue
 * file name: tFunctionOneValue.cpp
 * @author Betti Oesterholz
 * @date 08.05.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for the children class of cFunctionOneValue.
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
 * This file contains the test for the children class of cFunctionOneValue, which
 * represents a value Fib -underfunction.
 *
 *
 * What's tested of class cFunctionOneValue:
 * 	- cFunctionOneValue( const cUnderFunction * const pUnderfunction, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cFunctionOneValue( const cFunctionOneValue & underfunction, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- cFunctionOneValue( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	-cFunctionOneValue( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- ~cFunctionOneValue();
 * 	- cUnderFunction * getUnderFunction();
 * 	- void setUnderFunction( const cUnderFunction & underFunction, bool bDeleteOld=true );
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
 * tested one values underfunctions:
 * 	- cFunctionAbs
 * 	- cFunctionSin
 * 	- cFunctionLog
 * 	- cFunctionRound
 * 	- cFunctionArcsin
 *
 */
/*
History:
08.05.2010  Oesterholz  created
04.04.2011  Oesterholz  storing to binary stream
23.06.2011  Oesterholz  cFunctionRound added
*/

#include "version.h"

#include "cFunctionAbs.h"
#include "cFunctionSin.h"
#include "cFunctionLog.h"
#include "cFunctionRound.h"
#include "cFunctionArcsin.h"


#include "cFunctionOneValue.h"
#include "cFunctionValue.h"
#include "cFunctionVariable.h"
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


template <class tUnderFunctionOneValue> int testCostructor(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function );
template <class tUnderFunctionOneValue> int testUnderfunctions(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function );
template <class tUnderFunctionOneValue> int testEqual(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function );
template <class tUnderFunctionOneValue> int testCopy(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function );
template <class tUnderFunctionOneValue> int testStoreXml(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function );
template <class tUnderFunctionOneValue> int testStore(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function );
template <class tUnderFunctionOneValue> int testVariable(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function );
template <class tUnderFunctionOneValue> int testDefiningFibElement(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function );
template <class tUnderFunctionOneValue> int testValue(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function );



/** the type of the actual underfunction which is tested */
unsigned int uiActualUnderfunctionType = 0;


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"Running Test for methods of the childclasses of cFunctionOneValue"<<endl;
	cout<<      "================================================================="<<endl;
	cout<<      "================================================================="<<endl;
	
	for ( unsigned int iType = 1; iType <= 5; iType++ ){
		
		cFunctionValue underfunction( 1.0 );
		
		switch ( iType ){
			case 1:{
				cout<<endl<<"Running Test for methods of the class of cFunctionAbs"<<endl;
				cout<<      "====================================================="<<endl;
				uiActualUnderfunctionType = 1;
				cFunctionAbs function( &underfunction );
				
				iReturn += testCostructor( ulTestphase, function );
				iReturn += testEqual( ulTestphase, function );
				iReturn += testUnderfunctions( ulTestphase, function );
				iReturn += testCopy( ulTestphase, function );
				iReturn += testStoreXml( ulTestphase, function );
				iReturn += testStore( ulTestphase, function );
				iReturn += testVariable( ulTestphase, function );
				iReturn += testDefiningFibElement( ulTestphase, function );
				iReturn += testValue( ulTestphase, function );

			}break;
			case 2:{
				cout<<endl<<"Running Test for methods of the class of cFunctionSin"<<endl;
				cout<<      "====================================================="<<endl;
				uiActualUnderfunctionType = 2;
				cFunctionSin function( &underfunction );
				
				iReturn += testCostructor( ulTestphase, function );
				iReturn += testEqual( ulTestphase, function );
				iReturn += testUnderfunctions( ulTestphase, function );
				iReturn += testCopy( ulTestphase, function );
				iReturn += testStoreXml( ulTestphase, function );
				iReturn += testStore( ulTestphase, function );
				iReturn += testVariable( ulTestphase, function );
				iReturn += testDefiningFibElement( ulTestphase, function );
				iReturn += testValue( ulTestphase, function );

			}break;
			case 3:{
				cout<<endl<<"Running Test for methods of the class of cFunctionLog"<<endl;
				cout<<      "====================================================="<<endl;
				uiActualUnderfunctionType = 3;
				cFunctionLog function( &underfunction );
				
				iReturn += testCostructor( ulTestphase, function );
				iReturn += testEqual( ulTestphase, function );
				iReturn += testUnderfunctions( ulTestphase, function );
				iReturn += testCopy( ulTestphase, function );
				iReturn += testStoreXml( ulTestphase, function );
				iReturn += testStore( ulTestphase, function );
				iReturn += testVariable( ulTestphase, function );
				iReturn += testDefiningFibElement( ulTestphase, function );
				iReturn += testValue( ulTestphase, function );

			}break;
			case 4:{
				cout<<endl<<"Running Test for methods of the class of cFunctionArcsin"<<endl;
				cout<<      "========================================================"<<endl;
				uiActualUnderfunctionType = 4;
				cFunctionArcsin function( &underfunction );
				
				iReturn += testCostructor( ulTestphase, function );
				iReturn += testEqual( ulTestphase, function );
				iReturn += testUnderfunctions( ulTestphase, function );
				iReturn += testCopy( ulTestphase, function );
				iReturn += testStoreXml( ulTestphase, function );
				iReturn += testStore( ulTestphase, function );
				iReturn += testVariable( ulTestphase, function );
				iReturn += testDefiningFibElement( ulTestphase, function );
				iReturn += testValue( ulTestphase, function );

			}break;
			case 5:{
				cout<<endl<<"Running Test for methods of the class of cFunctionRound"<<endl;
				cout<<      "======================================================="<<endl;
				uiActualUnderfunctionType = 5;
				cFunctionRound function( &underfunction );
				
				iReturn += testCostructor( ulTestphase, function );
				iReturn += testEqual( ulTestphase, function );
				iReturn += testUnderfunctions( ulTestphase, function );
				iReturn += testCopy( ulTestphase, function );
				iReturn += testStoreXml( ulTestphase, function );
				iReturn += testStore( ulTestphase, function );
				iReturn += testVariable( ulTestphase, function );
				iReturn += testDefiningFibElement( ulTestphase, function );
				iReturn += testValue( ulTestphase, function );

			}break;

			default://no underfunction type skip it
				continue;
		}
	}

	if ( iReturn == 0 ){
	
		cout<<endl<<endl<<"Test successfull: no errors occoured"<<endl;
	}else{
		cerr<<endl<<endl<<"Test failed: "<<iReturn<<" errors occoured"<<endl;
	}

	return iReturn;
}


/**
 * @return the actual underfunction type number
 * 	@see cUnderFunction::getType()
 * 	@see uiActualUnderfunctionType
 */
unsignedIntFib getActualFunctionType(){

	switch ( uiActualUnderfunctionType ){
	
		case 1: return cUnderFunction::FUNCTION_ABS;//cFunctionAbs
		case 2: return cUnderFunction::FUNCTION_SIN;//cFunctionSin
		case 3: return cUnderFunction::FUNCTION_LOG;//cFunctionLog
		case 4: return cUnderFunction::FUNCTION_ARCSIN;//cFunctionArcsin
		case 5: return cUnderFunction::FUNCTION_ROUND;//cFunctionRound
	}
	return 0;
}


/**
 * @return the actual underfunction type number
 * 	@see cUnderFunction::getUnderFunctionName()
 * 	@see uiActualUnderfunctionType
 */
string getActualFunctionName(){

	switch ( uiActualUnderfunctionType ){
	
		case 1: return "abs";//cFunctionAbs
		case 2: return "sin";//cFunctionSin
		case 3: return "log";//cFunctionLog
		case 4: return "arcsin";//cFunctionArcsin
		case 5: return "round";//cFunctionRound
	}
	return "";
}


/**
 * This function evalues the value for the actual underfunction type if
 * the value is given.
 *
 * @param dValue the value (value of the underfunction) for
 * 	the function to evalue
 * @return the value for the actual underfunction
 */
doubleFib getActualFunctionValue( doubleFib dValue ){

	switch ( uiActualUnderfunctionType ){
	
		case 1: return abs( dValue );//cFunctionAbs
		case 2: return sin( dValue );//cFunctionSin
		case 3:{;//cFunctionLog
			if ( dValue <= 0.0 ){
				return 0.0;
			}//else
			return log( dValue );
		}break;
		case 4:{
			if ( (dValue < -1) || (1 < dValue) ){
				//arsin is not defined outside [-1,1]
				return 0;
			}
			return asin( dValue );//cFunctionArcsin
		}break;
		case 5: return round( dValue );//cFunctionRound
	}
	return 0.0;
}

/**
 * This function returns the compressed underfunction initiation for the
 * actual underfunction type.
 * The initiation is returned without the leading 0x02, for initiation
 * of 1'ary underfunctions.
 *
 * @return the compressed underfunction initiation for the actual
 * 	underfunction type
 */
unsigned char getActualFunctionCInitiation(){

	switch ( uiActualUnderfunctionType ){
	
		case 1: return 0x00;//cFunctionAbs
		case 2: return 0x01;//cFunctionSin
		case 3: return 0x02;//cFunctionLog
		case 4: return 0x06;//cFunctionArcsin
		case 5: return 0x0A;//cFunctionRound
	}
	return 0x00;
}


/**
 * This function returns bits for the compressed underfunction initiation
 * for the actual underfunction type.
 * This also includes the 2 bits for the initiation for the leading 0x02,
 * for initiation of 1'ary underfunctions.
 *
 * @return the bits for the compressed underfunction initiation
 */
unsigned int getActualFunctionCInitiationBits(){
	
	if ( uiActualUnderfunctionType <= 2 ){
		return 4;
	}//else
	return 6;
}


/**
 * This function adds the compressed underfunction initiation for the
 * actual underfunction type.
 * This also includes the initiation for the leading 0x02, for initiation
 * of 1'ary underfunctions.
 * The buffer should contain 2 Byts more than for the data plus the null
 * shift from uiNullShift .
 * (min pcBuffer byts size = uiNumberOfByts + 2 + int((uiNullShift + 7) / 8) )
 *
 * @param pcBuffer a pointer to the character buffer wher the initiation
 * 	should be added
 * @param uiNumberOfDataByts the number of byts in the buffer which
 * @param uiNullShift the number of 0 bits to add befor the initiation
 * @return a pointer to the char puffer wher the initiation is added
 */
unsigned char * addCInitiationForActualFunction( unsigned char * pcBuffer,
		unsigned int uiNumberOfDataByts, unsigned int uiNullShift = 0 ){
	
	/*shift the buffer bits to make space for the initiation and the
	uiNullShift; it will be filled at the front with 0 bits*/
	unsigned int uiBitsToShift = getActualFunctionCInitiationBits() + uiNullShift;
	if ( uiNumberOfDataByts != 0 ){
		for ( long lActualByte = uiNumberOfDataByts - 1;
				lActualByte >= 0; lActualByte-- ){
			
			if ( uiBitsToShift % 8 != 0 ){
				pcBuffer[ lActualByte + uiBitsToShift / 8 + 1 ] =
					pcBuffer[ lActualByte ] >> (7 - (uiBitsToShift - 1) % 8);
			}
			
			pcBuffer[ lActualByte + uiBitsToShift / 8 ] =
				pcBuffer[ lActualByte ] << (uiBitsToShift % 8);
		}
	}
	//fill the leading uiBitsToShift bits with 0
	for ( unsigned int uiActualByte = 0; uiActualByte < (uiBitsToShift / 8);
			uiActualByte++ ){
		
		pcBuffer[ uiActualByte ] = 0x00;
	}
	unsigned char ucMask = 0xFF << uiBitsToShift % 8;
	pcBuffer[ (uiBitsToShift / 8) ] = pcBuffer[ (uiBitsToShift / 8) ] & ucMask;
	
	//add the initiation shifted with uiNullShift
	//add the one value underfunction initiator
	pcBuffer[ (uiNullShift / 8) ] = pcBuffer[ (uiNullShift / 8) ] | (0x02 << (uiNullShift % 8) );
	if ( (uiNullShift % 8) == 7 ){
		pcBuffer[ (uiNullShift / 8) + 1 ] = pcBuffer[ (uiNullShift / 8) + 1 ] | 0x01;
	}
	
	//add the underfunction type initiator
	unsigned char ucUnderfunctionType = getActualFunctionCInitiation();
	const unsigned int uiShiftTillUfType = uiNullShift + 2;
	pcBuffer[ (uiShiftTillUfType / 8) ] = pcBuffer[ (uiShiftTillUfType / 8) ] | (ucUnderfunctionType << (uiShiftTillUfType % 8) );
	if ( (uiShiftTillUfType % 8) != 0 ){
		pcBuffer[ (uiShiftTillUfType / 8) + 1 ] = pcBuffer[ (uiShiftTillUfType / 8) + 1 ] | (ucUnderfunctionType >> (8 - (uiShiftTillUfType % 8)) );
	}
	
	return pcBuffer;
}



/**
 * This method tests the constructor of the cFunctionOneValue class.
 *
 * methods tested:
 * 	- cFunctionOneValue( const cUnderFunction * const pUnderfunction, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- ~cFunctionOneValue();
 * 	- cUnderFunction * getUnderFunction();
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
 * @param tUnderFunctionOneValue the type of the tested cFunctionOneValue
 * 	is of the type of this object
 * @return the number of erros occured in the test
 */
template <class tUnderFunctionOneValue> int testCostructor(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
	
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootEmpty( &point1 );"<<endl;
	cRoot rootEmpty( &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootEmpty( NULL, NULL, &point1 );"<<endl;
	cRoot rootEmpty( NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"rootEmpty.setNumberOfInputVariables( 10 );"<<endl;
	rootEmpty.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 =  rootEmpty.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 =  rootEmpty.getInputVariable( 1 );
	cout<<"pVariable1->setValue( 1.1 );"<<endl;
	pVariable1->setValue( 1.1 );
	cout<<"pVariable2 =  rootEmpty.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 =  rootEmpty.getInputVariable( 2 );
	cout<<"pVariable2->setValue( 2.2 );"<<endl;
	pVariable2->setValue( 2.2 );
	cout<<"pVariableX =  rootEmpty.getInputVariable( 10 );"<<endl;
	cFibVariable * pVariableX =  rootEmpty.getInputVariable( 10 );
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing empty cFunctionOneValue underfunction"<<endl;

	cout<<"cFunctionValue underFunctionValue1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue1( 1.0 );
	
	cout<<"tUnderFunctionOneValue underFunctionOneValue1( &underFunctionValue1 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue1( &underFunctionValue1 );
	
	cUnderFunction * pUnderfunction = &underFunctionValue1;
	double dValue = getActualFunctionValue( pUnderfunction->getValue() );
	cFibElement * pDefiningFibElement = NULL;
	cUnderFunction * pSuperiorUnderFunction = NULL;
	cTypeUnderFunction typeUnderFunction;
	cDomain * pUnderFunctionDomain = NULL;
	cDomain * pValueDomain = NULL;
	cDomain * pStandardDomain = typeUnderFunction.getStandardDomain();
	cTypeVariable typeVariable;
	cDomain * pVariableDomain = typeVariable.getStandardDomain();
	unsigned long ulTimeNeed = 1 + pUnderfunction->getTimeNeed();
	unsigned long ulCompressedSize = getActualFunctionCInitiationBits() + pUnderfunction->getCompressedSize();
 
	//check the getValue() methode from cFunctionOneValue
	if ( underFunctionOneValue1.getValue() == dValue  ){
	
		cout<<"The underfunction value is correctly "<<
			underFunctionOneValue1.getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			underFunctionOneValue1.getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the underfunctions
	//check getUnderFunction()
	if ( underFunctionOneValue1.getUnderFunction() != NULL  ){
	
		if ( underFunctionOneValue1.getUnderFunction() != pUnderfunction  ){
		
			cout<<"The underfunction dosn't points to the object set as the underfunction . "<<endl;
		}else{
			cerr<<"Error: The underfunction points to the object set as the underfunction."<<endl;
			iReturn++;
		}
		if ( *(underFunctionOneValue1.getUnderFunction()) == *pUnderfunction  ){
		
			cout<<"The underfunction is equal to the underfunction set as the underfunction . "<<endl;
		}else{
			cerr<<"Error: The underfunction isn't equal to the underfunction set as the underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionOneValue
	if ( underFunctionOneValue1.getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			underFunctionOneValue1.getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			underFunctionOneValue1.getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionOneValue
	if ( underFunctionOneValue1.getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			underFunctionOneValue1.getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			underFunctionOneValue1.getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionOneValue
	if ( ! underFunctionOneValue1.isValid() ){
	
		cout<<"The underfunction is correctly not valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionOneValue
	if ( underFunctionOneValue1.getType() == getActualFunctionType() ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			underFunctionOneValue1.getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionOneValue
	if ( underFunctionOneValue1.getUnderFunctionName() == getActualFunctionName() ){
	
		cout<<"The underfunction name is correctly "<<
			underFunctionOneValue1.getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			underFunctionOneValue1.getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionOneValue
	if ( underFunctionOneValue1.getNumberOfUnderFunctions() == 1 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			underFunctionOneValue1.getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			underFunctionOneValue1.getNumberOfUnderFunctions() <<" , but should be 1 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionOneValue
	cTypeElement * pTypeOfUnderFunction = underFunctionOneValue1.getElementType();
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
	//check the getDomain() methode from cFunctionOneValue
	cDomain * pRetUnderFunctionDomain = underFunctionOneValue1.getDomain();
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
	//check the getValueDomain() methode from cFunctionOneValue
	cDomain * pRetValueDomain = underFunctionOneValue1.getValueDomain();
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
	//check the getStandardDomain() methode from cFunctionOneValue
	cDomain * pRetStandardDomain = underFunctionOneValue1.getStandardDomain();
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
	//check the getVariableDomain() methode from cFunctionOneValue
	cDomain * pRetVariableDomain = underFunctionOneValue1.getVariableDomain();
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
	//check the getTimeNeed() methode from cFunctionOneValue
	if ( underFunctionOneValue1.getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			underFunctionOneValue1.getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionOneValue
	if ( underFunctionOneValue1.getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			underFunctionOneValue1.getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	if ( ! underFunctionOneValue1.isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionOneValue
	set<cFibVariable*> setUsedVariables = underFunctionOneValue1.getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"Ther are correctly no used variables are given back from the underfunction. "<<endl;
	}else{
		cerr<<"Error: Ther are used variables are given back from the underfunction. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an full cFunctionOneValue underfunction, testing the included underFunctionOneValue1"<<endl;

	cout<<"tUnderFunctionOneValue underFunctionOneValue2( &underFunctionOneValue1, NULL, &rootEmpty );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue2( &underFunctionOneValue1, NULL, &rootEmpty );
	
	cFunctionOneValue * pFunctionToTest = (cFunctionOneValue*)
		underFunctionOneValue2.getUnderFunction();
	
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
	
	pUnderfunction = &underFunctionValue1;
	dValue = getActualFunctionValue( pUnderfunction->getValue() );
	pDefiningFibElement = &rootEmpty;
	pSuperiorUnderFunction = &underFunctionOneValue2;
	pUnderFunctionDomain = &domainNaturalNumberBit5;
	pValueDomain = &domainNaturalNumberBit7;
	delete pVariableDomain;
	pVariableDomain = domainNaturalNumberBit3.clone();
	ulTimeNeed = 1 + pUnderfunction->getTimeNeed();
	ulCompressedSize = getActualFunctionCInitiationBits() + 9;
 
	//check the getValue() methode from cFunctionOneValue
	if ( pFunctionToTest->getValue() == dValue  ){
	
		cout<<"The underfunction value is correctly "<<
			pFunctionToTest->getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			pFunctionToTest->getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the underfunctions
	//check getUnderFunction()
	if ( pFunctionToTest->getUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getUnderFunction() != pUnderfunction  ){
		
			cout<<"The underfunction dosn't points to the object set as the underfunction . "<<endl;
		}else{
			cerr<<"Error: The underfunction points to the object set as the underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getUnderFunction()) == *pUnderfunction  ){
		
			cout<<"The underfunction is equal to the underfunction set as the underfunction . "<<endl;
		}else{
			cerr<<"Error: The underfunction isn't equal to the underfunction set as the underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionOneValue
	if ( pFunctionToTest->getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			pFunctionToTest->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			pFunctionToTest->getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionOneValue
	if ( pFunctionToTest->getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			pFunctionToTest->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			pFunctionToTest->getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionOneValue
	if ( pFunctionToTest->isValid() ){
	
		cout<<"The underfunction is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is not valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionOneValue
	if ( pFunctionToTest->getType() == getActualFunctionType() ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			pFunctionToTest->getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionOneValue
	if ( pFunctionToTest->getUnderFunctionName() == getActualFunctionName() ){
	
		cout<<"The underfunction name is correctly "<<
			pFunctionToTest->getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			pFunctionToTest->getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionOneValue
	if ( pFunctionToTest->getNumberOfUnderFunctions() == 1 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" , but should be 1 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionOneValue
	pTypeOfUnderFunction = pFunctionToTest->getElementType();
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
	//check the getDomain() methode from cFunctionOneValue
	pRetUnderFunctionDomain = pFunctionToTest->getDomain();
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
	//check the getValueDomain() methode from cFunctionOneValue
	pRetValueDomain = pFunctionToTest->getValueDomain();
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
	//check the getStandardDomain() methode from cFunctionOneValue
	pRetStandardDomain = pFunctionToTest->getStandardDomain();
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
	//check the getVariableDomain() methode from cFunctionOneValue
	pRetVariableDomain = pFunctionToTest->getVariableDomain();
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
	//check the getTimeNeed() methode from cFunctionOneValue
	if ( pFunctionToTest->getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			pFunctionToTest->getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionOneValue
	if ( pFunctionToTest->getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			pFunctionToTest->getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	if ( ! pFunctionToTest->isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionOneValue
	setUsedVariables = pFunctionToTest->getUsedVariables();
	if ( setUsedVariables.empty() ){
	
		cout<<"Ther are correctly no used variables are given back from the underfunction. "<<endl;
	}else{
		cerr<<"Error: Ther are used variables are given back from the underfunction. "<<endl;
		iReturn++;
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the highest underFunctionOneValue2"<<endl;

	pFunctionToTest = (cFunctionOneValue*) &underFunctionOneValue2;
	
	pUnderfunction =  &underFunctionOneValue1;
	dValue = getActualFunctionValue( pUnderfunction->getValue() );
	pDefiningFibElement = &rootEmpty;
	pSuperiorUnderFunction = NULL;
	pUnderFunctionDomain = &domainNaturalNumberBit5;
	pValueDomain = &domainNaturalNumberBit7;
	delete pVariableDomain;
	pVariableDomain = domainNaturalNumberBit3.clone();
	ulTimeNeed = 1 + pUnderfunction->getTimeNeed();
	ulCompressedSize = 2 * getActualFunctionCInitiationBits() + 9;
	
	set<cFibVariable*> setUsedVariablesCorrect;
	
	//check the getValue() methode from cFunctionOneValue
	if ( pFunctionToTest->getValue() == dValue  ){
	
		cout<<"The underfunction value is correctly "<<
			pFunctionToTest->getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			pFunctionToTest->getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the underfunctions
	//check getUnderFunction()
	if ( pFunctionToTest->getUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getUnderFunction() != pUnderfunction  ){
		
			cout<<"The underfunction dosn't points to the object set as the underfunction . "<<endl;
		}else{
			cerr<<"Error: The underfunction points to the object set as the underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getUnderFunction()) == *pUnderfunction  ){
		
			cout<<"The underfunction is equal to the underfunction set as the underfunction . "<<endl;
		}else{
			cerr<<"Error: The underfunction isn't equal to the underfunction set as the underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionOneValue
	if ( pFunctionToTest->getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			pFunctionToTest->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			pFunctionToTest->getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionOneValue
	if ( pFunctionToTest->getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			pFunctionToTest->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			pFunctionToTest->getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionOneValue
	if ( pFunctionToTest->isValid() ){
	
		cout<<"The underfunction is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is not valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionOneValue
	if ( pFunctionToTest->getType() == getActualFunctionType() ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			pFunctionToTest->getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionOneValue
	if ( pFunctionToTest->getUnderFunctionName() == getActualFunctionName() ){
	
		cout<<"The underfunction name is correctly "<<
			pFunctionToTest->getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			pFunctionToTest->getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionOneValue
	if ( pFunctionToTest->getNumberOfUnderFunctions() == 1 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" , but should be 1 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionOneValue
	pTypeOfUnderFunction = pFunctionToTest->getElementType();
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
	//check the getDomain() methode from cFunctionOneValue
	pRetUnderFunctionDomain = pFunctionToTest->getDomain();
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
	//check the getValueDomain() methode from cFunctionOneValue
	pRetValueDomain = pFunctionToTest->getValueDomain();
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
	//check the getStandardDomain() methode from cFunctionOneValue
	pRetStandardDomain = pFunctionToTest->getStandardDomain();
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
	//check the getVariableDomain() methode from cFunctionOneValue
	pRetVariableDomain = pFunctionToTest->getVariableDomain();
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
	//check the getTimeNeed() methode from cFunctionOneValue
	if ( pFunctionToTest->getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			pFunctionToTest->getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionOneValue
	if ( pFunctionToTest->getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			pFunctionToTest->getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	if ( ! pFunctionToTest->isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionOneValue
	setUsedVariables = pFunctionToTest->getUsedVariables();
	if ( setUsedVariables == setUsedVariablesCorrect ){
	
		cout<<"The correct used variables are given back from the underfunction. "<<endl;
	}else{
		cerr<<"Error: The used variables are given back from the underfunction arn't correct. "<<endl;
		iReturn++;
	}


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing constructing an full cFunctionOneValue underfunction with depth 3, testing the included underFunctionOneValue1"<<endl;

	cout<<"tUnderFunctionOneValue underFunctionOneValue3( "<<
		"&underFunctionOneValue2, NULL, &point1 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue3( &underFunctionOneValue2, NULL, &point1 );
	
	pFunctionToTest = (cFunctionOneValue*)((cFunctionOneValue*)
		underFunctionOneValue3.getUnderFunction())->getUnderFunction();
	
	pUnderfunction = &underFunctionValue1;
	dValue = getActualFunctionValue( pUnderfunction->getValue() );
	pDefiningFibElement = &point1;
	pSuperiorUnderFunction = underFunctionOneValue3.getUnderFunction();
	pUnderFunctionDomain = &domainNaturalNumberBit5;
	pValueDomain = &domainNaturalNumberBit7;
	ulTimeNeed = 1 + pUnderfunction->getTimeNeed();
	
	ulCompressedSize = getActualFunctionCInitiationBits() + 9;
	
	setUsedVariablesCorrect.clear();
	
	//check the getValue() methode from cFunctionOneValue
	if ( pFunctionToTest->getValue() == dValue  ){
	
		cout<<"The underfunction value is correctly "<<
			pFunctionToTest->getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			pFunctionToTest->getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the underfunctions
	//check getUnderFunction()
	if ( pFunctionToTest->getUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getUnderFunction() != pUnderfunction  ){
		
			cout<<"The underfunction dosn't points to the object set as the underfunction . "<<endl;
		}else{
			cerr<<"Error: The underfunction points to the object set as the underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getUnderFunction()) == *pUnderfunction  ){
		
			cout<<"The underfunction is equal to the underfunction set as the underfunction . "<<endl;
		}else{
			cerr<<"Error: The underfunction isn't equal to the underfunction set as the underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionOneValue
	if ( pFunctionToTest->getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			pFunctionToTest->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			pFunctionToTest->getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionOneValue
	if ( pFunctionToTest->getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			pFunctionToTest->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			pFunctionToTest->getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionOneValue
	if ( pFunctionToTest->isValid() ){
	
		cout<<"The underfunction is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is not valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionOneValue
	if ( pFunctionToTest->getType() == getActualFunctionType() ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			pFunctionToTest->getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionOneValue
	if ( pFunctionToTest->getUnderFunctionName() == getActualFunctionName() ){
	
		cout<<"The underfunction name is correctly "<<
			pFunctionToTest->getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			pFunctionToTest->getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionOneValue
	if ( pFunctionToTest->getNumberOfUnderFunctions() == 1 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" , but should be 1 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionOneValue
	pTypeOfUnderFunction = pFunctionToTest->getElementType();
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
	//check the getDomain() methode from cFunctionOneValue
	pRetUnderFunctionDomain = pFunctionToTest->getDomain();
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
	//check the getValueDomain() methode from cFunctionOneValue
	pRetValueDomain = pFunctionToTest->getValueDomain();
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
	//check the getStandardDomain() methode from cFunctionOneValue
	pRetStandardDomain = pFunctionToTest->getStandardDomain();
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
	//check the getVariableDomain() methode from cFunctionOneValue
	pRetVariableDomain = pFunctionToTest->getVariableDomain();
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
	//check the getTimeNeed() methode from cFunctionOneValue
	if ( pFunctionToTest->getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			pFunctionToTest->getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionOneValue
	if ( pFunctionToTest->getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			pFunctionToTest->getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	if ( ! pFunctionToTest->isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionOneValue
	setUsedVariables = pFunctionToTest->getUsedVariables();
	if ( setUsedVariables == setUsedVariablesCorrect ){
	
		cout<<"The correct used variables are given back from the underfunction. "<<endl;
	}else{
		cerr<<"Error: The used variables are given back from the underfunction arn't correct. "<<endl;
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the constructed full cFunctionOneValue underfunction with depth 3, testing the included underFunctionOneValue2"<<endl;
	
	pFunctionToTest = (cFunctionOneValue*)underFunctionOneValue3.getUnderFunction();
	
	pUnderfunction = &underFunctionOneValue1;
	dValue = getActualFunctionValue( pUnderfunction->getValue() );
	pDefiningFibElement = &point1;
	pSuperiorUnderFunction = &underFunctionOneValue3;
	pUnderFunctionDomain = &domainNaturalNumberBit5;
	pValueDomain = &domainNaturalNumberBit7;
	delete pVariableDomain;
	pVariableDomain = domainNaturalNumberBit3.clone();
	ulTimeNeed = 1 + pUnderfunction->getTimeNeed();
	
	ulCompressedSize = 2 * getActualFunctionCInitiationBits() + 9;
	
	//check the getValue() methode from cFunctionOneValue
	if ( pFunctionToTest->getValue() == dValue  ){
	
		cout<<"The underfunction value is correctly "<<
			pFunctionToTest->getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			pFunctionToTest->getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the underfunctions
	//check getUnderFunction()
	if ( pFunctionToTest->getUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getUnderFunction() != pUnderfunction  ){
		
			cout<<"The underfunction dosn't points to the object set as the underfunction . "<<endl;
		}else{
			cerr<<"Error: The underfunction points to the object set as the underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getUnderFunction()) == *pUnderfunction  ){
		
			cout<<"The underfunction is equal to the underfunction set as the underfunction . "<<endl;
		}else{
			cerr<<"Error: The underfunction isn't equal to the underfunction set as the underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionOneValue
	if ( pFunctionToTest->getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			pFunctionToTest->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			pFunctionToTest->getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionOneValue
	if ( pFunctionToTest->getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			pFunctionToTest->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			pFunctionToTest->getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionOneValue
	if ( pFunctionToTest->isValid() ){
	
		cout<<"The underfunction is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is not valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionOneValue
	if ( pFunctionToTest->getType() == getActualFunctionType() ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			pFunctionToTest->getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionOneValue
	if ( pFunctionToTest->getUnderFunctionName() == getActualFunctionName() ){
	
		cout<<"The underfunction name is correctly "<<
			pFunctionToTest->getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			pFunctionToTest->getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionOneValue
	if ( pFunctionToTest->getNumberOfUnderFunctions() == 1 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" , but should be 1 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionOneValue
	pTypeOfUnderFunction = pFunctionToTest->getElementType();
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
	//check the getDomain() methode from cFunctionOneValue
	pRetUnderFunctionDomain = pFunctionToTest->getDomain();
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
	//check the getValueDomain() methode from cFunctionOneValue
	pRetValueDomain = pFunctionToTest->getValueDomain();
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
	//check the getStandardDomain() methode from cFunctionOneValue
	pRetStandardDomain = pFunctionToTest->getStandardDomain();
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
	//check the getVariableDomain() methode from cFunctionOneValue
	pRetVariableDomain = pFunctionToTest->getVariableDomain();
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
	//check the getTimeNeed() methode from cFunctionOneValue
	if ( pFunctionToTest->getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			pFunctionToTest->getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionOneValue
	if ( pFunctionToTest->getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			pFunctionToTest->getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	if ( ! pFunctionToTest->isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionOneValue
	setUsedVariables = pFunctionToTest->getUsedVariables();
	if ( setUsedVariables == setUsedVariablesCorrect ){
	
		cout<<"The correct used variables are given back from the underfunction. "<<endl;
	}else{
		cerr<<"Error: The used variables are given back from the underfunction arn't correct. "<<endl;
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the constructed full cFunctionOneValue underfunction with depth 3, testing the included underFunctionOneValue3"<<endl;
	
	pFunctionToTest = (cFunctionOneValue*)&underFunctionOneValue3;
	
	pUnderfunction = &underFunctionOneValue2;
	dValue = getActualFunctionValue( pUnderfunction->getValue() );
	pDefiningFibElement = &point1;
	pSuperiorUnderFunction = NULL;
	pUnderFunctionDomain = &domainNaturalNumberBit5;
	pValueDomain = &domainNaturalNumberBit7;
	delete pVariableDomain;
	pVariableDomain = domainNaturalNumberBit3.clone();
	ulTimeNeed = 1 + pUnderfunction->getTimeNeed();
	
	ulCompressedSize = getActualFunctionCInitiationBits() + pUnderfunction->getCompressedSize();
	
	//check the getValue() methode from cFunctionOneValue
	if ( pFunctionToTest->getValue() == dValue  ){
	
		cout<<"The underfunction value is correctly "<<
			pFunctionToTest->getValue() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction value is "<<
			pFunctionToTest->getValue() <<" but should be "<< dValue <<" ."<<endl;
		iReturn++;
	}
	//check the underfunctions
	//check getUnderFunction()
	if ( pFunctionToTest->getUnderFunction() != NULL  ){
	
		if ( pFunctionToTest->getUnderFunction() != pUnderfunction  ){
		
			cout<<"The underfunction dosn't points to the object set as the underfunction . "<<endl;
		}else{
			cerr<<"Error: The underfunction points to the object set as the underfunction."<<endl;
			iReturn++;
		}
		if ( *(pFunctionToTest->getUnderFunction()) == *pUnderfunction  ){
		
			cout<<"The underfunction is equal to the underfunction set as the underfunction . "<<endl;
		}else{
			cerr<<"Error: The underfunction isn't equal to the underfunction set as the underfunction."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The underfunction is NULL ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionOneValue
	if ( pFunctionToTest->getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"The underfunction defining fib -element is correctly "<<
			pFunctionToTest->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction defining fib -element is "<<
			pFunctionToTest->getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionOneValue
	if ( pFunctionToTest->getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"The superior underfunction of the underfunction correctly "<<
			pFunctionToTest->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"Error: The superior underfunction of the underfunction is "<<
			pFunctionToTest->getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	
	//check the isValid() methode from cFunctionOneValue
	if ( pFunctionToTest->isValid() ){
	
		cout<<"The underfunction is correctly valid . "<<endl;
	}else{
		cerr<<"Error: The underfunction is not valid ."<<endl;
		iReturn++;
	}
	//check the getType() methode from cFunctionOneValue
	if ( pFunctionToTest->getType() == getActualFunctionType() ){
	
		cout<<"The underfunction type is correctly FUNCTION_VARIABLE. "<<endl;
	}else{
		cerr<<"Error: The type of the underfunction is not FUNCTION_VARIABLE ( "<<
			cUnderFunction::FUNCTION_VARIABLE <<" ), but "<<
			pFunctionToTest->getType() <<" ."<<endl;
		iReturn++;
	}
	//check the getUnderFunctionName() methode from cFunctionOneValue
	if ( pFunctionToTest->getUnderFunctionName() == getActualFunctionName() ){
	
		cout<<"The underfunction name is correctly "<<
			pFunctionToTest->getUnderFunctionName() <<" . "<<endl;
	}else{
		cerr<<"Error: The name of the underfunction is not \"variable\", but "<<
			pFunctionToTest->getUnderFunctionName() <<" ."<<endl;
		iReturn++;
	}
	//check the getNumberOfUnderFunctions() methode from cFunctionOneValue
	if ( pFunctionToTest->getNumberOfUnderFunctions() == 1 ){
	
		cout<<"The underfunction number of underfunctions is correctly "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" . "<<endl;
	}else{
		cerr<<"Error: The underfunction number of underfunctions is "<<
			pFunctionToTest->getNumberOfUnderFunctions() <<" , but should be 1 ."<<endl;
		iReturn++;
	}
	//check the getElementType() methode from cFunctionOneValue
	pTypeOfUnderFunction = pFunctionToTest->getElementType();
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
	//check the getDomain() methode from cFunctionOneValue
	pRetUnderFunctionDomain = pFunctionToTest->getDomain();
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
	//check the getValueDomain() methode from cFunctionOneValue
	pRetValueDomain = pFunctionToTest->getValueDomain();
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
	//check the getStandardDomain() methode from cFunctionOneValue
	pRetStandardDomain = pFunctionToTest->getStandardDomain();
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
	//check the getVariableDomain() methode from cFunctionOneValue
	pRetVariableDomain = pFunctionToTest->getVariableDomain();
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
	//check the getTimeNeed() methode from cFunctionOneValue
	if ( pFunctionToTest->getTimeNeed() == ulTimeNeed ){
	
		cout<<"The time needed to evalue the function is correctly "<< ulTimeNeed <<" . "<<endl;
	}else{
		cerr<<"Error: The time needed to evalue the function is "<<
			pFunctionToTest->getTimeNeed()<<" ,but should be "<< ulTimeNeed <<" . "<<endl;
		iReturn++;
	}
	//check the getCompressedSize() methode from cFunctionOneValue
	if ( pFunctionToTest->getCompressedSize() == ulCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
		ulCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			pFunctionToTest->getCompressedSize()<<" ,but should be "<<
			ulCompressedSize <<" . "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	if ( ! pFunctionToTest->isUsedVariable( pVariableX ) ){
	
		cout<<"The variable pVariableX isn't used in the underfunction. "<<endl;
	}else{
		cerr<<"Error: The variable pVariableX is used in the underfunction. "<<endl;
		iReturn++;
	}
	//check the getUsedVariables() methode from cFunctionOneValue
	setUsedVariables = pFunctionToTest->getUsedVariables();
	if ( setUsedVariables == setUsedVariablesCorrect ){
	
		cout<<"The correct used variables are given back from the underfunction. "<<endl;
	}else{
		cerr<<"Error: The used variables are given back from the underfunction arn't correct. "<<endl;
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
 * This method tests the falues of an underfunction of a function.
 *
 *
 * @param pUnderfunction a pointer to the underfunction to test
 * @param pUnderfunctionOriginal a pointer to the underfunction which
 * 	should be equal to the underfunction to test (but not the same object)
 * @param pSuperiorUnderFunction the defining superior function the
 * 	underfunction to test should have
 * @param pDefiningFibElement the defining fib -element the
 * 	underfunction to test should have
 * @return the number of erros occured in the test
 */
int checkUnderFunction( cUnderFunction * pUnderfunction,
	cUnderFunction * pUnderfunctionOriginal,
	cUnderFunction * pSuperiorUnderFunction, cFibElement * pDefiningFibElement ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	if ( pUnderfunction != pUnderfunctionOriginal ){
	
		cout<<"   The underfunction dosn't points to the object set as the underfunction . "<<endl;
	}else{
		cerr<<"   Error: The underfunction points to the object set as the underfunction."<<endl;
		iReturn++;
	}
	if ( pUnderfunction == NULL ){
		cerr<<"   Error: The underfunction to check is NULL."<<endl;
		iReturn++;
		return iReturn;
	}
	if ( pUnderfunction == NULL ){
		cerr<<"   Error: The underfunction to check against is NULL."<<endl;
		iReturn++;
		return iReturn;
	}
	
	if ( *pUnderfunction == *pUnderfunctionOriginal ){
	
		cout<<"   The underfunction is equal to the underfunction set as the underfunction . "<<endl;
	}else{
		cerr<<"   Error: The underfunction isn't equal to the underfunction set as the underfunction."<<endl;
		iReturn++;
	}
	//check the getSuperiorUnderFunction() methode from cFunctionOneValue
	if ( pUnderfunction->getSuperiorUnderFunction() == pSuperiorUnderFunction  ){
	
		cout<<"   The superior underfunction of the underfunction correctly "<<
			pUnderfunction->getSuperiorUnderFunction() <<" . "<<endl;
	}else{
		cerr<<"   Error: The superior underfunction of the underfunction is "<<
			pUnderfunction->getSuperiorUnderFunction() <<
			" but should be "<< pSuperiorUnderFunction <<" ."<<endl;
		iReturn++;
	}
	//check the getDefiningFibElement() methode from cFunctionOneValue
	if ( pUnderfunction->getDefiningFibElement() == pDefiningFibElement  ){
	
		cout<<"   The underfunction defining fib -element is correctly "<<
			pUnderfunction->getDefiningFibElement() <<" . "<<endl;
	}else{
		cerr<<"   Error: The underfunction defining fib -element is "<<
			pUnderfunction->getDefiningFibElement() <<
			" but should be "<< pDefiningFibElement <<" ."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This method tests the methods for the underfunctions of the
 * cFunctionOneValue class.
 *
 * methods tested:
 * 	- cUnderFunction * getUnderFunction();
 * 	- void setUnderFunction( const cUnderFunction & underFunction, bool bDeleteOld=true );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param tUnderFunctionOneValue the type of the tested cFunctionOneValue
 * 	is of the type of this object
 * @return the number of erros occured in the test
 */
template <class tUnderFunctionOneValue> int testUnderfunctions(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing method for setting the underfunction"<<endl;
	
	cout<<"cPoint point1;"<<endl;
	cPoint point1;
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootEmpty( &point1 );"<<endl;
	cRoot rootEmpty( &point1 );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cout<<"cRoot rootEmpty( NULL, NULL, &point1 );"<<endl;
	cRoot rootEmpty( NULL, NULL, &point1 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR

	cout<<"cPoint point2;"<<endl;
	cPoint point2;

	cout<<"cFunctionValue underFunctionValue1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue1( 1.0 );
	cout<<"cFunctionValue underFunctionValue2( 2.0 );"<<endl;
	cFunctionValue underFunctionValue2( 2.0 );
	cout<<"cFunctionValue underFunctionValue3( 3.0 );"<<endl;
	cFunctionValue underFunctionValue3( 3.0 );
	cout<<"cFunctionValue underFunctionValue4( 4.0 );"<<endl;
	cFunctionValue underFunctionValue4( 4.0 );
	
	cout<<"tUnderFunctionOneValue underFunctionOneValue1( &underFunctionValue1, NULL, &point1 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue1( &underFunctionValue1, NULL, &point1 );

	cout<<"tUnderFunctionOneValue underFunctionOneValue2( &underFunctionValue3, NULL, &point2 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue2( &underFunctionValue3, NULL, &point2 );


	cout<<"checking: underFunctionOneValue1.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionOneValue1.getUnderFunction(),
		&underFunctionValue1, &underFunctionOneValue1, &point1 );
	
	cout<<"checking: underFunctionOneValue2.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionOneValue2.getUnderFunction(),
		&underFunctionValue3, &underFunctionOneValue2, &point2 );


	cout<<endl<<"underFunctionOneValue1.setUnderFunction( underFunctionOneValue2 );"<<endl;
	underFunctionOneValue1.setUnderFunction( underFunctionOneValue2 );

	cout<<"checking: underFunctionOneValue1.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionOneValue1.getUnderFunction(),
		&underFunctionOneValue2, &underFunctionOneValue1, &point1 );
	
	if ( underFunctionOneValue1.getUnderFunction() ){
		cout<<"checking: underFunctionOneValue1.getUnderFunction()->getUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionOneValue*)(
			underFunctionOneValue1.getUnderFunction()))->getUnderFunction(),
			&underFunctionValue3, underFunctionOneValue1.getUnderFunction(), &point1 );
	}

	cout<<"checking: underFunctionOneValue1.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionOneValue1.getUnderFunction(),
		&underFunctionOneValue2, &underFunctionOneValue1, &point1 );
	
	if ( underFunctionOneValue1.getUnderFunction() ){
		cout<<"checking: underFunctionOneValue1.getUnderFunction()->getUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionOneValue*)(
			underFunctionOneValue1.getUnderFunction()))->getUnderFunction(),
			&underFunctionValue3, underFunctionOneValue1.getUnderFunction(), &point1 );
	}

	cout<<endl<<"tUnderFunctionOneValue underFunctionOneValue2_Copy( &underFunctionValue3, NULL, NULL );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue2_Copy( &underFunctionValue3, NULL, NULL );
	
	cout<<"checking: underFunctionOneValue2.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionOneValue2.getUnderFunction(),
		&underFunctionValue3, &underFunctionOneValue2, &point2 );
	
	cout<<endl<<"tUnderFunctionOneValue underFunctionOneValue3( &underFunctionValue1 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue3( &underFunctionValue1 );
	cout<<"underFunctionOneValue2.setUnderFunction( underFunctionOneValue3 );"<<endl;
	underFunctionOneValue2.setUnderFunction( underFunctionOneValue3 );
	
	cout<<"checking: underFunctionOneValue2.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionOneValue2.getUnderFunction(),
		&underFunctionOneValue3, &underFunctionOneValue2, &point2 );
	if ( underFunctionOneValue2.getUnderFunction() ){
		cout<<"checking: underFunctionOneValue2.getUnderFunction()->getUnderFunction()"<<endl;
		iReturn += checkUnderFunction( ((cFunctionOneValue*)(
			underFunctionOneValue2.getUnderFunction()))->getUnderFunction(),
			&underFunctionValue1, underFunctionOneValue2.getUnderFunction(), &point2 );
	}

	return iReturn;
}



/**
 * This method tests the equal() method of one given fib -objects which are
 * equal.
 *
 * @param underFunction1 the fib -object to compare
 * @param szNameObject1 the name of the fib -object to compare
 * @param underFunction2 the secound fib -object to compare to
 * @param szNameObject2 the name of the secound fib -object to compare
 * @return the number of errors occured in the test
 */
int testCompareOneEqualObjects( const cUnderFunction &underFunction1, const string &szNameObject1,
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
	if ( iReturn != 0 ){
		cerr<<"function "<<szNameObject1<<" :";
		underFunction1.storeXml( cerr );
		cerr<<endl;
		cerr<<"function "<<szNameObject2<<" :";
		underFunction2.storeXml( cerr );
		cerr<<endl;
	}
	return iReturn;
}


/**
 * This method tests the equal() method of one given fib -objects which are
 * not equal.
 *
 * @param underFunction1 the fib -object to compare
 * @param szNameObject1 the name of the fib -object to compare
 * @param underFunction2 the secound fib -object to compare to
 * @param szNameObject2 the name of the secound fib -object to compare
 * @return the number of errors occured in the test
 */
int testCompareOneNotEqualObjects( const cUnderFunction &underFunction1, const string &szNameObject1,
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
 * This method tests equal method of the cFunctionOneValue classes.
 *
 * methods tested:
 * 	- bool equal( const cFibElement & fibObject ) const
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param tUnderFunctionOneValue the type of the tested cFunctionOneValue
 * 	is of the type of this object
 * @return the number of erros occured in the test
 */
template <class tUnderFunctionOneValue> int testEqual(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function ){

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
	cout<<"pVariable1->setValue( 1.0 );"<<endl;
	pVariable1->setValue( 1.0 );
	cout<<"pVariable2 =  rootEmpty.getInputVariable( 2 );"<<endl;
	cFibVariable * pVariable2 =  rootEmpty.getInputVariable( 2 );
	cout<<"pVariable2->setValue( 2.0 );"<<endl;
	pVariable2->setValue( 2.0 );
	cout<<"pVariable3 =  rootEmpty.getInputVariable( 3 );"<<endl;
	cFibVariable * pVariable3 =  rootEmpty.getInputVariable( 3 );
	cout<<"pVariable3->setValue( 1.0 );"<<endl;
	pVariable3->setValue( 1.0 );

	//function with a empty functionvector
	cout<<"cFunctionValue underFunctionValue1_V1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue1_V1( 1.0 );
	cout<<"cFunctionValue underFunctionValue2_V1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue2_V1( 1.0 );
	cout<<"cFunctionValue underFunctionValue1_V2( 2.0 );"<<endl;
	cFunctionValue underFunctionValue1_V2( 2.0 );
	cout<<"cFunctionValue underFunctionValue1_V1p01( 1.01 );"<<endl;
	cFunctionValue underFunctionValue1_V1p01( 1.01 );
	
	cout<<"tUnderFunctionOneValue underFunctionOneValue1V1( &underFunctionValue1_V1 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue1V1( &underFunctionValue1_V1 );
	
	cout<<"tUnderFunctionOneValue underFunctionOneValue2V1( &underFunctionValue2_V1 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue2V1( &underFunctionValue2_V1 );

	cout<<"tUnderFunctionOneValue underFunctionOneValue1V2( &underFunctionValue1_V2 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue1V2( &underFunctionValue1_V2 );

	cout<<"tUnderFunctionOneValue underFunctionOneValue1V1p01( &underFunctionValue1_V1p01 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue1V1p01( &underFunctionValue1_V1p01 );


	//functions with variables
	cout<<"cFunctionVariable underFunctionVariable1_V1( pVariable1 );"<<endl;
	cFunctionVariable underFunctionVariable1_V1( pVariable1 );
	cout<<"cFunctionVariable underFunctionVariable1_V2( pVariable2 );"<<endl;
	cFunctionVariable underFunctionVariable1_V2( pVariable2 );
	cout<<"cFunctionVariable underFunctionVariable2_V2( pVariable2 );"<<endl;
	cFunctionVariable underFunctionVariable2_V2( pVariable2 );
	cout<<"cFunctionVariable underFunctionVariable1_V3( pVariable3 );"<<endl;
	cFunctionVariable underFunctionVariable1_V3( pVariable3 );

	cout<<"tUnderFunctionOneValue underFunctionOneValue1_X1( &underFunctionVariable1_V1 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue1_X1( &underFunctionVariable1_V1 );

	cout<<"tUnderFunctionOneValue underFunctionOneValue2_X1( &underFunctionVariable1_V1 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue2_X1( &underFunctionVariable1_V1 );

	cout<<"tUnderFunctionOneValue underFunctionOneValue1_X2( &underFunctionVariable2_V2 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue1_X2( &underFunctionVariable2_V2 );

	cout<<"tUnderFunctionOneValue underFunctionOneValue1_X3( &underFunctionVariable1_V3 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue1_X3( &underFunctionVariable1_V3 );


	//function with defining fib -element
	cout<<"cRoot rootSimple1;"<<endl;
	cRoot rootSimple1;
	cout<<"tUnderFunctionOneValue underFunctionOneValueDE1_V1( &underFunctionValue1_V1, NULL, &rootSimple1 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValueDE1_V1( &underFunctionValue1_V1, NULL, &rootSimple1 );
	
	//function with superior underfunction
	cout<<"cFunctionValue underFunctionSup( 3.33 );"<<endl;
	cFunctionValue underFunctionSup( 3.333 );
	cout<<"tUnderFunctionOneValue underFunctionOneValueSup1_V1( &underFunctionValue1_V1, & underFunctionSup );"<<endl;
	tUnderFunctionOneValue underFunctionOneValueSup1_V1( &underFunctionValue1_V1, & underFunctionSup );

	//underfunction with domains set
	cout<<"root1 rootSimple1;"<<endl;
	cRoot root1;
	
	cout<<"cTypeUnderFunction testTypeUnderFunction;"<<endl;
	cTypeUnderFunction testTypeUnderFunction;
	cout<<"cDomainNaturalNumberBit domainNat8( 8 );"<<endl;
	cDomainNaturalNumberBit domainNat8( 8 );

	cout<<"root1.getDomains()->addDomain( testTypeUnderFunction, &domainNat8 );"<<endl;
	root1.getDomains()->addDomain( testTypeUnderFunction, &domainNat8 );

	cout<<"tUnderFunctionOneValue underFunctionOneValueDom1_V1( &underFunctionValue1_V1, NULL, &root1 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValueDom1_V1( &underFunctionValue1_V1, NULL, &root1 );
	
	//function with defining fib -element and superior underfunction
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cFunctionValue underFunctionSup2( 5.0 );"<<endl;
	cFunctionValue underFunctionSup2( 5.0 );
	
	cout<<"tUnderFunctionOneValue underFunctionOneValueSupDE1_V1( &underFunctionValue1_V1, & underFunctionSup2, &rootSimple2 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValueSupDE1_V1( &underFunctionValue1_V1, & underFunctionSup2, &rootSimple2 );



	cout<<endl<<"Beginning comparisson: "<<endl<<endl;

	//compare with underFunctionOneValue1V1
	cUnderFunction * actualObject = &underFunctionOneValue1V1;
	string szActualObjectName = "underFunctionOneValue1V1";
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1, "underFunctionOneValue1V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2V1, "underFunctionOneValue2V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V2, "underFunctionOneValue1V2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1p01, "underFunctionOneValue1V1p01" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X1, "underFunctionOneValue1_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2_X1, "underFunctionOneValue2_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X2, "underFunctionOneValue1_X2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X3, "underFunctionOneValue1_X3" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDE1_V1, "underFunctionOneValueDE1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSup1_V1, "underFunctionOneValueSup1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDom1_V1, "underFunctionOneValueDom1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSupDE1_V1, "underFunctionOneValueSupDE1_V1" );

	//compare with underFunctionOneValue2V1
	actualObject = &underFunctionOneValue2V1;
	szActualObjectName = "underFunctionOneValue2V1";
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1, "underFunctionOneValue1V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2V1, "underFunctionOneValue2V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V2, "underFunctionOneValue1V2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1p01, "underFunctionOneValue1V1p01" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X1, "underFunctionOneValue1_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2_X1, "underFunctionOneValue2_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X2, "underFunctionOneValue1_X2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X3, "underFunctionOneValue1_X3" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDE1_V1, "underFunctionOneValueDE1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSup1_V1, "underFunctionOneValueSup1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDom1_V1, "underFunctionOneValueDom1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSupDE1_V1, "underFunctionOneValueSupDE1_V1" );

	//compare with underFunctionOneValue2V1
	actualObject = &underFunctionOneValue1V2;
	szActualObjectName = "underFunctionOneValue1V2";
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1, "underFunctionOneValue1V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2V1, "underFunctionOneValue2V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V2, "underFunctionOneValue1V2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1p01, "underFunctionOneValue1V1p01" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X1, "underFunctionOneValue1_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2_X1, "underFunctionOneValue2_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X2, "underFunctionOneValue1_X2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X3, "underFunctionOneValue1_X3" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDE1_V1, "underFunctionOneValueDE1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSup1_V1, "underFunctionOneValueSup1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDom1_V1, "underFunctionOneValueDom1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSupDE1_V1, "underFunctionOneValueSupDE1_V1" );

	//compare with underFunctionOneValue1V1p01
	actualObject = &underFunctionOneValue1V1p01;
	szActualObjectName = "underFunctionOneValue1V1p01";
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1, "underFunctionOneValue1V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2V1, "underFunctionOneValue2V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V2, "underFunctionOneValue1V2" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1p01, "underFunctionOneValue1V1p01" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X1, "underFunctionOneValue1_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2_X1, "underFunctionOneValue2_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X2, "underFunctionOneValue1_X2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X3, "underFunctionOneValue1_X3" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDE1_V1, "underFunctionOneValueDE1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSup1_V1, "underFunctionOneValueSup1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDom1_V1, "underFunctionOneValueDom1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSupDE1_V1, "underFunctionOneValueSupDE1_V1" );

	//compare with underFunctionOneValue1_X1
	actualObject = &underFunctionOneValue1_X1;
	szActualObjectName = "underFunctionOneValue1_X1";
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1, "underFunctionOneValue1V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2V1, "underFunctionOneValue2V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V2, "underFunctionOneValue1V2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1p01, "underFunctionOneValue1V1p01" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X1, "underFunctionOneValue1_X1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2_X1, "underFunctionOneValue2_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X2, "underFunctionOneValue1_X2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X3, "underFunctionOneValue1_X3" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDE1_V1, "underFunctionOneValueDE1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSup1_V1, "underFunctionOneValueSup1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDom1_V1, "underFunctionOneValueDom1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSupDE1_V1, "underFunctionOneValueSupDE1_V1" );

	//compare with underFunctionOneValue2_X1
	actualObject = &underFunctionOneValue2_X1;
	szActualObjectName = "underFunctionOneValue2_X1";
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1, "underFunctionOneValue1V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2V1, "underFunctionOneValue2V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V2, "underFunctionOneValue1V2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1p01, "underFunctionOneValue1V1p01" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X1, "underFunctionOneValue1_X1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2_X1, "underFunctionOneValue2_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X2, "underFunctionOneValue1_X2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X3, "underFunctionOneValue1_X3" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDE1_V1, "underFunctionOneValueDE1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSup1_V1, "underFunctionOneValueSup1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDom1_V1, "underFunctionOneValueDom1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSupDE1_V1, "underFunctionOneValueSupDE1_V1" );

	//compare with underFunctionOneValue1_X2
	actualObject = &underFunctionOneValue1_X2;
	szActualObjectName = "underFunctionOneValue1_X2";
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1, "underFunctionOneValue1V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2V1, "underFunctionOneValue2V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V2, "underFunctionOneValue1V2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1p01, "underFunctionOneValue1V1p01" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X1, "underFunctionOneValue1_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2_X1, "underFunctionOneValue2_X1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X2, "underFunctionOneValue1_X2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X3, "underFunctionOneValue1_X3" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDE1_V1, "underFunctionOneValueDE1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSup1_V1, "underFunctionOneValueSup1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDom1_V1, "underFunctionOneValueDom1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSupDE1_V1, "underFunctionOneValueSupDE1_V1" );

	//compare with underFunctionOneValue1_X3
	actualObject = &underFunctionOneValue1_X3;
	szActualObjectName = "underFunctionOneValue1_X3";
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1, "underFunctionOneValue1V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2V1, "underFunctionOneValue2V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V2, "underFunctionOneValue1V2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1p01, "underFunctionOneValue1V1p01" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X1, "underFunctionOneValue1_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2_X1, "underFunctionOneValue2_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X2, "underFunctionOneValue1_X2" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X3, "underFunctionOneValue1_X3" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDE1_V1, "underFunctionOneValueDE1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSup1_V1, "underFunctionOneValueSup1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDom1_V1, "underFunctionOneValueDom1_V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSupDE1_V1, "underFunctionOneValueSupDE1_V1" );

	//compare with underFunctionOneValueDE1_V1
	actualObject = &underFunctionOneValueDE1_V1;
	szActualObjectName = "underFunctionOneValueDE1_V1";
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1, "underFunctionOneValue1V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2V1, "underFunctionOneValue2V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V2, "underFunctionOneValue1V2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1p01, "underFunctionOneValue1V1p01" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X1, "underFunctionOneValue1_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2_X1, "underFunctionOneValue2_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X2, "underFunctionOneValue1_X2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X3, "underFunctionOneValue1_X3" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDE1_V1, "underFunctionOneValueDE1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSup1_V1, "underFunctionOneValueSup1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDom1_V1, "underFunctionOneValueDom1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSupDE1_V1, "underFunctionOneValueSupDE1_V1" );

	//compare with underFunctionOneValueSup1_V1
	actualObject = &underFunctionOneValueSup1_V1;
	szActualObjectName = "underFunctionOneValueSup1_V1";
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1, "underFunctionOneValue1V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2V1, "underFunctionOneValue2V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V2, "underFunctionOneValue1V2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1p01, "underFunctionOneValue1V1p01" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X1, "underFunctionOneValue1_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2_X1, "underFunctionOneValue2_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X2, "underFunctionOneValue1_X2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X3, "underFunctionOneValue1_X3" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDE1_V1, "underFunctionOneValueDE1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSup1_V1, "underFunctionOneValueSup1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDom1_V1, "underFunctionOneValueDom1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSupDE1_V1, "underFunctionOneValueSupDE1_V1" );

	//compare with underFunctionOneValueDom1_V1
	actualObject = &underFunctionOneValueDom1_V1;
	szActualObjectName = "underFunctionOneValueDom1_V1";
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1, "underFunctionOneValue1V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2V1, "underFunctionOneValue2V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V2, "underFunctionOneValue1V2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1p01, "underFunctionOneValue1V1p01" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X1, "underFunctionOneValue1_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2_X1, "underFunctionOneValue2_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X2, "underFunctionOneValue1_X2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X3, "underFunctionOneValue1_X3" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDE1_V1, "underFunctionOneValueDE1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSup1_V1, "underFunctionOneValueSup1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDom1_V1, "underFunctionOneValueDom1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSupDE1_V1, "underFunctionOneValueSupDE1_V1" );

	//compare with underFunctionOneValueSupDE1_V1
	actualObject = &underFunctionOneValueSupDE1_V1;
	szActualObjectName = "underFunctionOneValueSupDE1_V1";
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1, "underFunctionOneValue1V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2V1, "underFunctionOneValue2V1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V2, "underFunctionOneValue1V2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1V1p01, "underFunctionOneValue1V1p01" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X1, "underFunctionOneValue1_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue2_X1, "underFunctionOneValue2_X1" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X2, "underFunctionOneValue1_X2" );
	iReturn += testCompareOneNotEqualObjects( *actualObject, szActualObjectName, underFunctionOneValue1_X3, "underFunctionOneValue1_X3" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDE1_V1, "underFunctionOneValueDE1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSup1_V1, "underFunctionOneValueSup1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueDom1_V1, "underFunctionOneValueDom1_V1" );
	iReturn += testCompareOneEqualObjects( *actualObject, szActualObjectName, underFunctionOneValueSupDE1_V1, "underFunctionOneValueSupDE1_V1" );


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
 * This method tests the copy methods and copyconstructor of the cFunctionOneValue class.
 *
 * methods tested:
 * 	- cFunctionOneValue( const cFunctionOneValue & underfunction, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 * 	- cUnderFunction * clone( cUnderFunction * pInSuperiorUnderFunction = NULL, cFibElement *pInDefiningFibElement = NULL) const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param tUnderFunctionOneValue the type of the tested cFunctionOneValue
 * 	is of the type of this object
 * @return the number of erros occured in the test
 */
template <class tUnderFunctionOneValue> int testCopy(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a simple cFunctionOneValue"<<endl;
	
	cout<<"cFunctionValue underFunctionValue1_V1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue1_V1( 1.0 );
	
	cout<<"tUnderFunctionOneValue ufOneValue1V1( &underFunctionValue1_V1 );"<<endl;
	tUnderFunctionOneValue ufOneValue1V1( &underFunctionValue1_V1 );

	cout<<"tUnderFunctionOneValue ufOneValue1V1CopyConstruct( ufOneValue1V1 );"<<endl;
	tUnderFunctionOneValue ufOneValue1V1CopyConstruct( ufOneValue1V1 );

	iReturn += testCompareOneEqualObjects( ufOneValue1V1CopyConstruct, "ufOneValue1V1CopyConstruct", ufOneValue1V1, "ufOneValue1V1" );
	iReturn += testNotConnectedUnderFunction( ufOneValue1V1CopyConstruct );
	cout<<"checking: ufOneValue1V1CopyConstruct.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( ufOneValue1V1CopyConstruct.getUnderFunction(),
		ufOneValue1V1.getUnderFunction(), &ufOneValue1V1CopyConstruct, NULL );

	cout<<endl<<"cFunctionOneValue * pUfOneValue1V1_V2Clone = ufOneValue1V1CopyConstruct.clone();"<<endl;
	cFunctionOneValue * pUfOneValue1V1_V2Clone = ufOneValue1V1CopyConstruct.clone();

	iReturn += testCompareOneEqualObjects( *pUfOneValue1V1_V2Clone, "pUfOneValue1V1_V2Clone", ufOneValue1V1, "ufOneValue1V1" );
	iReturn += testNotConnectedUnderFunction( *pUfOneValue1V1_V2Clone );
	cout<<"checking: pUfOneValue1V1_V2Clone->getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( pUfOneValue1V1_V2Clone->getUnderFunction(),
		ufOneValue1V1.getUnderFunction(), pUfOneValue1V1_V2Clone, NULL );
	delete pUfOneValue1V1_V2Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionOneValue with variable underfunctions"<<endl;

	cout<<"cRoot rootEmpty;"<<endl;
	cRoot rootEmpty;
	cout<<"rootEmpty.setNumberOfInputVariables( 10 );"<<endl;
	rootEmpty.setNumberOfInputVariables( 10 );
	cout<<"pVariable1 =  rootEmpty.getInputVariable( 1 );"<<endl;
	cFibVariable * pVariable1 =  rootEmpty.getInputVariable( 1 );
	
	cout<<"cFunctionVariable underFunctionVariable1_V1( pVariable1 );"<<endl;
	cFunctionVariable underFunctionVariable1_V1( pVariable1 );
	
	cout<<"tUnderFunctionOneValue ufOneVariable1V1( &underFunctionVariable1_V1 );"<<endl;
	tUnderFunctionOneValue ufOneVariable1V1( &underFunctionVariable1_V1 );

	cout<<"tUnderFunctionOneValue ufOneVariable1V1CopyConstruct( ufOneVariable1V1 );"<<endl;
	tUnderFunctionOneValue ufOneVariable1V1CopyConstruct( ufOneVariable1V1 );

	iReturn += testCompareOneEqualObjects( ufOneVariable1V1CopyConstruct, "ufOneVariable1V1CopyConstruct", ufOneVariable1V1, "ufOneVariable1V1" );
	iReturn += testNotConnectedUnderFunction( ufOneVariable1V1CopyConstruct );
	cout<<"checking: ufOneVariable1V1CopyConstruct.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( ufOneVariable1V1CopyConstruct.getUnderFunction(),
		ufOneVariable1V1.getUnderFunction(), &ufOneVariable1V1CopyConstruct, NULL );

	cout<<endl<<"cFunctionOneValue * pUfOneVariable1V1_V2Clone = ufOneVariable1V1CopyConstruct.clone();"<<endl;
	cFunctionOneValue * pUfOneVariable1V1_V2Clone = ufOneVariable1V1CopyConstruct.clone();

	iReturn += testCompareOneEqualObjects( *pUfOneVariable1V1_V2Clone, "pUfOneVariable1V1_V2Clone", ufOneVariable1V1, "ufOneVariable1V1" );
	iReturn += testNotConnectedUnderFunction( *pUfOneVariable1V1_V2Clone );
	cout<<"checking: pUfOneVariable1V1_V2Clone->getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( pUfOneVariable1V1_V2Clone->getUnderFunction(),
		ufOneVariable1V1.getUnderFunction(), pUfOneVariable1V1_V2Clone, NULL );
	delete pUfOneVariable1V1_V2Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionOneValue with a superior underfunction and defining fib -element"<<endl;

	//function with defining fib -element and superior underfunction
	cout<<"cRoot rootSimple;"<<endl;
	cRoot rootSimple;
	cout<<"cFunctionValue underFunctionSup( 325.142 );"<<endl;
	cFunctionValue underFunctionSup( 325.142 );

	cout<<"tUnderFunctionOneValue ufOneDefUf1V1( &underFunctionValue1_V1, &underFunctionSup, &rootSimple );"<<endl;
	tUnderFunctionOneValue ufOneDefUf1V1( &underFunctionValue1_V1, &underFunctionSup, &rootSimple );

	cout<<"tUnderFunctionOneValue ufOneDefUf1V1CopyConstruct( ufOneDefUf1V1 );"<<endl;
	tUnderFunctionOneValue ufOneDefUf1V1CopyConstruct( ufOneDefUf1V1 );

	iReturn += testCompareOneEqualObjects( ufOneDefUf1V1CopyConstruct, "ufOneDefUf1V1CopyConstruct", ufOneDefUf1V1, "ufOneDefUf1V1" );
	cout<<"checking: ufOneDefUf1V1CopyConstruct"<<endl;
	iReturn += checkUnderFunction( &ufOneDefUf1V1CopyConstruct,
		&ufOneValue1V1, NULL, &rootSimple );
	cout<<"checking: ufOneDefUf1V1CopyConstruct.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( ufOneDefUf1V1CopyConstruct.getUnderFunction(),
		ufOneDefUf1V1.getUnderFunction(), &ufOneDefUf1V1CopyConstruct, &rootSimple );

	cout<<endl<<"cFunctionOneValue * pUfOneDefUf1V1_V2Clone = ufOneDefUf1V1CopyConstruct.clone();"<<endl;
	cFunctionOneValue * pUfOneDefUf1V1_V2Clone = ufOneDefUf1V1CopyConstruct.clone();

	iReturn += testCompareOneEqualObjects( *pUfOneDefUf1V1_V2Clone, "pUfOneDefUf1V1_V2Clone", ufOneDefUf1V1, "ufOneDefUf1V1" );
	cout<<"checking: pUfOneDefUf1V1_V2Clone"<<endl;
	iReturn += checkUnderFunction( pUfOneDefUf1V1_V2Clone,
		&ufOneValue1V1, NULL, &rootSimple );
	cout<<"checking: pUfOneDefUf1V1_V2Clone->getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( pUfOneDefUf1V1_V2Clone->getUnderFunction(),
		ufOneDefUf1V1.getUnderFunction(), pUfOneDefUf1V1_V2Clone, &rootSimple );
	delete pUfOneDefUf1V1_V2Clone;


	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing copying a cFunctionOneValue with a superior underfunction and defining fib -element which will be changed"<<endl;

	//function with defining fib -element and superior underfunction
	cout<<"cRoot rootSimple2;"<<endl;
	cRoot rootSimple2;
	cout<<"cFunctionValue underFunctionSup2( 42.0 );"<<endl;
	cFunctionValue underFunctionSup2( 42.0 );

	cout<<"tUnderFunctionOneValue ufOneDefUf2V1( &underFunctionValue1_V1, &underFunctionSup, &rootSimple );"<<endl;
	tUnderFunctionOneValue ufOneDefUf2V1( &underFunctionValue1_V1, &underFunctionSup, &rootSimple );

	cout<<"tUnderFunctionOneValue ufOneDefUf2V1CopyConstruct( ufOneDefUf2V1, &underFunctionSup2, &rootSimple2 );"<<endl;
	tUnderFunctionOneValue ufOneDefUf2V1CopyConstruct( ufOneDefUf2V1, &underFunctionSup2, &rootSimple2 );

	iReturn += testCompareOneEqualObjects( ufOneDefUf2V1CopyConstruct, "ufOneDefUf2V1CopyConstruct", ufOneDefUf2V1, "ufOneDefUf2V1" );
	cout<<"checking: ufOneDefUf2V1CopyConstruct"<<endl;
	iReturn += checkUnderFunction( &ufOneDefUf2V1CopyConstruct,
		&ufOneValue1V1, &underFunctionSup2, &rootSimple2 );
	cout<<"checking: ufOneDefUf2V1CopyConstruct.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( ufOneDefUf2V1CopyConstruct.getUnderFunction(),
		ufOneDefUf2V1.getUnderFunction(), &ufOneDefUf2V1CopyConstruct, &rootSimple2 );

	cout<<endl<<"cFunctionOneValue * pUfOneDefUf2V1_V2Clone = ufOneDefUf2V1CopyConstruct.clone( &underFunctionSup2, &rootSimple2);"<<endl;
	cFunctionOneValue * pUfOneDefUf2V1_V2Clone = ufOneDefUf2V1CopyConstruct.clone( &underFunctionSup2, &rootSimple2);

	iReturn += testCompareOneEqualObjects( *pUfOneDefUf2V1_V2Clone, "pUfOneDefUf2V1_V2Clone", ufOneDefUf2V1, "ufOneDefUf2V1" );
	cout<<"checking: pUfOneDefUf2V1_V2Clone"<<endl;
	iReturn += checkUnderFunction( pUfOneDefUf2V1_V2Clone,
		&ufOneValue1V1, &underFunctionSup2, &rootSimple2 );
	cout<<"checking: pUfOneDefUf2V1_V2Clone->getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( pUfOneDefUf2V1_V2Clone->getUnderFunction(),
		ufOneDefUf2V1.getUnderFunction(), pUfOneDefUf2V1_V2Clone, &rootSimple2 );
	delete pUfOneDefUf2V1_V2Clone;


	return iReturn;
}



/**
 * This method tests a in the xml -format stored cFunctionOneValue.
 * The underfunctions of the cFunctionOneValue should be one value underfunction
 * ( cFunctionValue ).
 *
 * @param szFilename the name of the file wher the cFunctionOneValue is stored
 * @param dValue the value of the underfunction
 * @return the number of errors occured in the test
 */
int testXmlFunctionOneValue( const string szFilename, double dValue ){
	
	unsigned int iReturn = 0;
	
	cout<<endl<<"Checking stored cFunctionOneValue:"<<endl;
	
	TiXmlDocument xmlDocFunctionOneValue( szFilename );
	bool loadOkay = xmlDocFunctionOneValue.LoadFile();
	if ( loadOkay ){
		cout<<"The data of the vector was loaded successfull from the file \""<< szFilename <<"\". "<<endl;
	}else{
		cerr<<"Error: Failed to load file \""<< szFilename <<"\""<<endl;
		iReturn++;
	}

	TiXmlHandle xmlHandle( &xmlDocFunctionOneValue );
	TiXmlElement * pXmlElement;
	TiXmlHandle xmlHandleRoot(0);

	pXmlElement = xmlHandle.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if ( pXmlElement ) {
		string szElementName = pXmlElement->Value();
		
		const string szFunctionOneValueElementName = getActualFunctionName();
		if ( szElementName == szFunctionOneValueElementName ){
			cout<<"The function is correctly named \""<< szFunctionOneValueElementName <<"\". "<<endl;
		
		}else{
			cerr<<"Error: The name of the function is "<< szElementName <<" and not \""<< szFunctionOneValueElementName <<"\"."<<endl;
			iReturn++;
		}

	}else{// pXmlElement == NULL ->no root handle
		cerr<<"Error: No root handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	//check the underfunctions
	xmlHandleRoot = TiXmlHandle( pXmlElement );
	pXmlElement = xmlHandleRoot.FirstChild().Element();
	
	//check the underfunctions
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
		cerr<<"Error: No underfunction handle in \""<< szFilename <<"\"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	return iReturn;
}


/**
 * This method tests the storeXml() method of the cFunctionOneValue class.
 * Just storing properties with no underobjects is tested.
 *
 * methods tested:
 * 	- bool storeXml( ostream &stream ) const;
 * 	-  cFunctionOneValue( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cUnderFunction * restoreXml( const TiXmlElement * pXmlElement, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param tUnderFunctionOneValue the type of the tested cFunctionOneValue
 * 	is of the type of this object
 * @return the number of errors occured in the test
 */
template <class tUnderFunctionOneValue> int testStoreXml(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function ){

	unsigned int iReturn = 0;

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an underfunction with valuefunctions with 1.0 and 2.0"<<endl;
		
	cout<<"list<cFibVariable*> liDefinedVariables;"<<endl;
	list<cFibVariable*> liDefinedVariables;
	list<cFibVariable*> liDefinedVariablesOrg;

	cout<<"cFunctionValue underFunctionValue1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue1( 1.0 );

	cout<<"tUnderFunctionOneValue underFunctionOneValue1V1( &underFunctionValue1 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue1V1( &underFunctionValue1 );
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	char * szXmlFunctionOneValueFileName = strcat( strcat( strcat( szFileNameBuffer,
		(char*)DIR_OUTPUT ), getActualFunctionName().c_str() ), "1V1.xml" );
	ofstream * pFileUnderFunction = new ofstream( szXmlFunctionOneValueFileName );
	
	bool bStoreSuccesfull = underFunctionOneValue1V1.storeXml( *pFileUnderFunction );
	delete pFileUnderFunction;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFunctionOneValue was stored successfull to the file \""<< szXmlFunctionOneValueFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFunctionOneValue to the file \""<< szXmlFunctionOneValueFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlFunctionOneValue( szXmlFunctionOneValueFileName, underFunctionValue1.getValue() );
	
	TiXmlDocument xmlDocFunctionOneValue( szFileNameBuffer );
	bool loadOkay = xmlDocFunctionOneValue.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		cout<<"TiXmlHandle xmlHandle( &xmlDocFunctionOneValue ); "<<endl;
		TiXmlHandle xmlHandle( &xmlDocFunctionOneValue );
		cout<<"tUnderFunctionOneValue underFunctionOneValue1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		tUnderFunctionOneValue underFunctionOneValue1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionOneValue1Loaded.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionOneValue1Loaded.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareOneEqualObjects( underFunctionOneValue1Loaded, "underFunctionOneValue1Loaded", underFunctionOneValue1V1, "underFunctionOneValue1V1" );
		iReturn += testNotConnectedUnderFunction( underFunctionOneValue1Loaded );
		cout<<"checking: underFunctionOneValue1Loaded.getUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionOneValue1Loaded.getUnderFunction(),
			&underFunctionValue1, &underFunctionOneValue1Loaded, NULL );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocFunctionOneValue ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocFunctionOneValue );
		cout<<"cFunctionOneValue underFunctionOneValue1Loaded( xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cUnderFunction * pUnderFunctionOneValue1Loaded = cUnderFunction::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionOneValue1Loaded ){
			if ( pUnderFunctionOneValue1Loaded->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionOneValue1Loaded->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareOneEqualObjects( * pUnderFunctionOneValue1Loaded, "pUnderFunctionOneValue1Loaded", underFunctionOneValue1V1, "underFunctionOneValue1V1" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionOneValue1Loaded );
			cout<<"checking: pUnderFunctionOneValue1Loaded->getUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionOneValue*)pUnderFunctionOneValue1Loaded)->getUnderFunction(),
				&underFunctionValue1, pUnderFunctionOneValue1Loaded, NULL );
			delete pUnderFunctionOneValue1Loaded;
		}else{
			cerr<<"Error: No underfunction loaded ."<<endl;
			iReturn++;
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
		cout<<"TiXmlHandle xmlHandle3( &xmlDocFunctionOneValue ); "<<endl;
		TiXmlHandle xmlHandle3( &xmlDocFunctionOneValue );
		cout<<"tUnderFunctionOneValue underFunctionOneValue1LoadedFull( xmlHandle3.FirstChildElement().Element(), "<<
			"outStatus, liDefinedVariables, &underFunctionSup, &rootSimple ); "<<endl;
		tUnderFunctionOneValue underFunctionOneValue1LoadedFull( xmlHandle3.FirstChildElement().Element(),
			outStatus, liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionOneValue1LoadedFull.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionOneValue1LoadedFull.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareOneEqualObjects( underFunctionOneValue1LoadedFull,
			"underFunctionOneValue1LoadedFull", underFunctionOneValue1V1, "underFunctionOneValue1V1" );
		//check the getDefiningFibElement() methode from cFunctionOneValue
		if ( underFunctionOneValue1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionOneValue1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionOneValue1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionOneValue
		if ( underFunctionOneValue1LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionOneValue1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionOneValue1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		cout<<"checking: underFunctionOneValue1LoadedFull.getUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionOneValue1LoadedFull.getUnderFunction(),
			&underFunctionValue1, &underFunctionOneValue1LoadedFull, &rootSimple );

		
		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle4( &xmlDocFunctionOneValue ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocFunctionOneValue );
		cout<<"cFunctionOneValue pUnderFunctionOneValue1LoadedFull = cUnderFunction::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionOneValue1LoadedFull = cUnderFunction::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionOneValue1LoadedFull ){
			if ( pUnderFunctionOneValue1LoadedFull->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionOneValue1LoadedFull->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareOneEqualObjects( * pUnderFunctionOneValue1LoadedFull, "pUnderFunctionOneValue1LoadedFull", underFunctionOneValue1V1, "underFunctionOneValue1V1" );
			//check the getDefiningFibElement() methode from cFunctionOneValue
			if ( pUnderFunctionOneValue1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionOneValue1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionOneValue1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionOneValue
			if ( pUnderFunctionOneValue1LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionOneValue1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionOneValue1LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			cout<<"checking: pUnderFunctionOneValue1LoadedFull->getUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionOneValue*)pUnderFunctionOneValue1LoadedFull)->getUnderFunction(),
				&underFunctionValue1, pUnderFunctionOneValue1LoadedFull, &rootSimple );
			
			delete pUnderFunctionOneValue1LoadedFull;
		}else{
			cerr<<"Error: No underfunction loaded ."<<endl;
			iReturn++;
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
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the storeXml() method on an underfunction with valuefunctions with given superior underfunction and defining fib -element"<<endl;

	cout<<"cFunctionValue underFunctionValue3( -3.0 );"<<endl;
	cFunctionValue underFunctionValue3( -3.0 );
	
	cout<<"cRoot rootSimple;"<<endl;
	cRoot rootSimple;
	cout<<"cFunctionValue underFunctionSup1( 5.0 );"<<endl;
	cFunctionValue underFunctionSup1( 5.0 );

	cout<<"tUnderFunctionOneValue underFunctionOneValue2( &underFunctionValue3, &underFunctionSup1, &rootSimple );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue2( &underFunctionValue3, &underFunctionSup1, &rootSimple );
	
	szFileNameBuffer[0] = 0;
	szXmlFunctionOneValueFileName = strcat( strcat( strcat( szFileNameBuffer, (char*)DIR_OUTPUT ),
		getActualFunctionName().c_str() ), "2.xml" );
	pFileUnderFunction = new ofstream( szXmlFunctionOneValueFileName );
	
	bStoreSuccesfull = underFunctionOneValue2.storeXml( *pFileUnderFunction );
	delete pFileUnderFunction;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data of the cFunctionOneValue was stored successfull to the file \""<< szXmlFunctionOneValueFileName <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data of the cFunctionOneValue to the file \""<< szXmlFunctionOneValueFileName <<"\" failed."<<endl;
		iReturn++;
	}
	iReturn += testXmlFunctionOneValue( szXmlFunctionOneValueFileName, underFunctionValue3.getValue() );
	
	TiXmlDocument xmlDocFunctionOneValue2( szFileNameBuffer );
	loadOkay = xmlDocFunctionOneValue2.LoadFile();
	if ( loadOkay ){
		
		intFib outStatus = 0;
		cout<<"TiXmlHandle xmlHandle( &xmlDocFunctionOneValue2 ); "<<endl;
		TiXmlHandle xmlHandle( &xmlDocFunctionOneValue2 );
		cout<<"tUnderFunctionOneValue underFunctionOneValue1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		tUnderFunctionOneValue underFunctionOneValue1Loaded( xmlHandle.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionOneValue1Loaded.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionOneValue1Loaded.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareOneEqualObjects( underFunctionOneValue1Loaded, "underFunctionOneValue1Loaded", underFunctionOneValue2, "underFunctionOneValue2" );
		iReturn += testNotConnectedUnderFunction( underFunctionOneValue1Loaded );
		cout<<"checking: underFunctionOneValue1Loaded.getUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionOneValue1Loaded.getUnderFunction(),
			&underFunctionValue3, &underFunctionOneValue1Loaded, NULL );

		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle2( &xmlDocFunctionOneValue2 ); "<<endl;
		TiXmlHandle xmlHandle2( &xmlDocFunctionOneValue2 );
		cout<<"cFunctionOneValue underFunctionOneValue1Loaded( xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables ); "<<endl;
		cUnderFunction * pUnderFunctionOneValue1Loaded = cUnderFunction::restoreXml(
			xmlHandle2.FirstChildElement().Element(), outStatus, liDefinedVariables );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionOneValue1Loaded ){
			if ( pUnderFunctionOneValue1Loaded->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionOneValue1Loaded->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			if ( pUnderFunctionOneValue1Loaded->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionOneValue1Loaded->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareOneEqualObjects( * pUnderFunctionOneValue1Loaded, "pUnderFunctionOneValue1Loaded", underFunctionOneValue2, "underFunctionOneValue2" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionOneValue1Loaded );
			cout<<"checking: pUnderFunctionOneValue1Loaded->getUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionOneValue*)pUnderFunctionOneValue1Loaded)->getUnderFunction(),
				&underFunctionValue3, pUnderFunctionOneValue1Loaded, NULL );
			delete pUnderFunctionOneValue1Loaded;
		}else{
			cerr<<"Error: No underfunction loaded ."<<endl;
			iReturn++;
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
		cout<<"TiXmlHandle xmlHandle3( &xmlDocFunctionOneValue2 ); "<<endl;
		TiXmlHandle xmlHandle3( &xmlDocFunctionOneValue2 );
		cout<<"tUnderFunctionOneValue underFunctionOneValue1LoadedFull( xmlHandle3.FirstChildElement().Element(), "<<
			"outStatus, liDefinedVariables, &underFunctionSup, &rootSimple ); "<<endl;
		tUnderFunctionOneValue underFunctionOneValue1LoadedFull( xmlHandle3.FirstChildElement().Element(),
			outStatus, liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionOneValue1LoadedFull.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionOneValue1LoadedFull.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareOneEqualObjects( underFunctionOneValue1LoadedFull,
			"underFunctionOneValue1LoadedFull", underFunctionOneValue2, "underFunctionOneValue2" );
		//check the getDefiningFibElement() methode from cFunctionOneValue
		if ( underFunctionOneValue1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionOneValue1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionOneValue1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionOneValue
		if ( underFunctionOneValue1LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionOneValue1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionOneValue1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		cout<<"checking: underFunctionOneValue1LoadedFull.getUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionOneValue1LoadedFull.getUnderFunction(),
			&underFunctionValue3, &underFunctionOneValue1LoadedFull, &rootSimple );

		
		outStatus = 0;
		cout<<"TiXmlHandle xmlHandle4( &xmlDocFunctionOneValue2 ); "<<endl;
		TiXmlHandle xmlHandle4( &xmlDocFunctionOneValue2 );
		cout<<"cFunctionOneValue pUnderFunctionOneValue1LoadedFull = cUnderFunction::restoreXml( "<<
			"xmlHandle4.FirstChildElement().Element(), outStatus, liDefinedVariables, "<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionOneValue1LoadedFull = cUnderFunction::restoreXml(
			xmlHandle4.FirstChildElement().Element(), outStatus,
			liDefinedVariables, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionOneValue1LoadedFull ){
			if ( pUnderFunctionOneValue1LoadedFull->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionOneValue1LoadedFull->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareOneEqualObjects( * pUnderFunctionOneValue1LoadedFull, "pUnderFunctionOneValue1LoadedFull", underFunctionOneValue2, "underFunctionOneValue2" );
			//check the getDefiningFibElement() methode from cFunctionOneValue
			if ( pUnderFunctionOneValue1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionOneValue1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionOneValue1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionOneValue
			if ( pUnderFunctionOneValue1LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionOneValue1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionOneValue1LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			cout<<"checking: pUnderFunctionOneValue1LoadedFull->getUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionOneValue*)pUnderFunctionOneValue1LoadedFull)->getUnderFunction(),
				&underFunctionValue3, pUnderFunctionOneValue1LoadedFull, &rootSimple );
			
			delete pUnderFunctionOneValue1LoadedFull;
		}else{
			cerr<<"Error: No underfunction loaded ."<<endl;
			iReturn++;
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
 * 	-cFunctionOneValue( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInDomainValue, const cDomainSingle * pInDomainVariable, cUnderFunction * pInSuperiorFunction = NULL, cFibElement * pInDefiningFibElement = NULL );
 * 	- cUnderFunction * restore( cReadBits & iBitStream, intFib & outStatus, list<cFibVariable*> & liDefinedVariables, const cDomainSingle * pInValueDomain, const cDomainSingle * pInDomainVariable, cUnderFunction * pInSuperiorFunction = NULL, cFibElement *pInDefiningFibElement = NULL );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param tUnderFunctionOneValue the type of the tested cFunctionOneValue
 * 	is of the type of this object
 * @return the number of errors occured in the test
 */
template <class tUnderFunctionOneValue> int testStore(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the store() method an simple underfunction"<<endl;

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
	
	cout<<"cFunctionValue underFunctionValue1( 1.0 );"<<endl;
	cFunctionValue underFunctionValue1( 1.0 );

	cout<<"tUnderFunctionOneValue underFunctionOneValue1( &underFunctionValue1, NULL, &root );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue1( &underFunctionValue1, NULL, &root );

	//test get compressed size
	unsigned int uiCompressedSize = getActualFunctionCInitiationBits() + (2 + 16);
	if ( (unsigned int)(underFunctionOneValue1.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			underFunctionOneValue1.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}
	
	char szFileNameBuffer[128];
	szFileNameBuffer[0] = 0;
	strcat( strcat( strcat( szFileNameBuffer, (char*)DIR_OUTPUT ),
		getActualFunctionName().c_str() ), "1.fib" );
	ofstream * pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	char cRestBit = 0x00;
	unsigned char cRestBitPosition = 0;
	cout<<"underFunctionOneValue1.store( *pFile, cRestBits, cRestBitPosition );"<<endl;
	bool bStoreSuccesfull = underFunctionOneValue1.store( *pFile, cRestBit, cRestBitPosition );
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
	short sNumberOfRestBitCorrect = uiCompressedSize % 8;
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
	unsigned char cFunctionOneValue1[] = { 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	addCInitiationForActualFunction( cFunctionOneValue1, 3 );
	iReturn += compareBytsWithFile( szFileNameBuffer, (char*)cFunctionOneValue1, uiCompressedSize / 8 + 1 );

	char cFunctionName = 0x00;
	ifstream * fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
	if ( (fileInXml != NULL) && ( fileInXml->good() ) ){
		
		cReadBits iBitStream( * fileInXml );
		iBitStream.readBits( &cFunctionName, getActualFunctionCInitiationBits() );
		intFib outStatus = 0;
		cout<<"tUnderFunctionOneValue underFunctionOneValue1Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		tUnderFunctionOneValue underFunctionOneValue1Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionOneValue1Loaded.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionOneValue1Loaded.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareOneEqualObjects( underFunctionOneValue1Loaded, "underFunctionOneValue1Loaded", underFunctionOneValue1, "underFunctionOneValue1" );
		iReturn += testNotConnectedUnderFunction( underFunctionOneValue1Loaded );
		cout<<"checking: underFunctionOneValue1Loaded.getUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionOneValue1Loaded.getUnderFunction(),
			&underFunctionValue1, &underFunctionOneValue1Loaded, NULL );

		delete fileInXml;
		ifstream * fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream2( * fileInXml );
		outStatus = 0;
		cout<<"cFunctionOneValue pUnderFunctionOneValue1Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctionOneValue1Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionOneValue1Loaded ){
			if ( pUnderFunctionOneValue1Loaded->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionOneValue1Loaded->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareOneEqualObjects( * pUnderFunctionOneValue1Loaded, "pUnderFunctionOneValue1Loaded", underFunctionOneValue1, "underFunctionOneValue1" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionOneValue1Loaded );
			cout<<"checking: pUnderFunctionOneValue1Loaded->getUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionOneValue*)pUnderFunctionOneValue1Loaded)->getUnderFunction(),
				&underFunctionValue1, pUnderFunctionOneValue1Loaded, NULL );
			delete pUnderFunctionOneValue1Loaded;
		}else{
			cerr<<"Error: No underfunction loaded ."<<endl;
			iReturn++;
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
		fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream3( * fileInXml );
		iBitStream3.readBits( &cFunctionName, getActualFunctionCInitiationBits() );
		outStatus = 0;
		cout<<"tUnderFunctionOneValue underFunctionOneValue1LoadedFull( iBitStream3, "<<
			"outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &underFunctionSup, &rootSimple ); "<<endl;
		tUnderFunctionOneValue underFunctionOneValue1LoadedFull( iBitStream3,
			outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionOneValue1LoadedFull.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionOneValue1LoadedFull.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareOneEqualObjects( underFunctionOneValue1LoadedFull,
			"underFunctionOneValue1LoadedFull", underFunctionOneValue1, "underFunctionOneValue1" );
		//check the getDefiningFibElement() methode from cFunctionOneValue
		if ( underFunctionOneValue1LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionOneValue1LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionOneValue1LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionOneValue
		if ( underFunctionOneValue1LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionOneValue1LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionOneValue1LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		cout<<"checking: underFunctionOneValue1LoadedFull.getUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionOneValue1LoadedFull.getUnderFunction(),
			&underFunctionValue1, &underFunctionOneValue1LoadedFull, &rootSimple );
		
		delete fileInXml;
		fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream4( * fileInXml );
		outStatus = 0;
		cout<<"cFunctionOneValue pUnderFunctionOneValue1LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionOneValue1LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionOneValue1LoadedFull ){
			if ( pUnderFunctionOneValue1LoadedFull->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionOneValue1LoadedFull->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareOneEqualObjects( * pUnderFunctionOneValue1LoadedFull, "pUnderFunctionOneValue1LoadedFull", underFunctionOneValue1, "underFunctionOneValue1" );
			//check the getDefiningFibElement() methode from cFunctionOneValue
			if ( pUnderFunctionOneValue1LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionOneValue1LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionOneValue1LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionOneValue
			if ( pUnderFunctionOneValue1LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionOneValue1LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionOneValue1LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			cout<<"checking: pUnderFunctionOneValue1LoadedFull->getUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionOneValue*)pUnderFunctionOneValue1LoadedFull)->getUnderFunction(),
				&underFunctionValue1, pUnderFunctionOneValue1LoadedFull, &rootSimple );
			
			delete pUnderFunctionOneValue1LoadedFull;
		}else{
			cerr<<"Error: No underfunction loaded ."<<endl;
			iReturn++;
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

	delete pValueDomain;
	pValueDomain = new cDomainNaturalNumberBit( 6 );
	delete pVariableDomain;
	pVariableDomain = new cDomainNaturalNumberBit( 4 );
	
	cout<<"cTypeUnderFunction testTypeUnderFunction;"<<endl;
	cTypeUnderFunction testTypeUnderFunction;
	
	cout<<"cDomainNaturalNumberBit naturalNumberDomainB6( 6 );"<<endl;
	cDomainNaturalNumberBit naturalNumberDomainB6( 6 );

	cout<<"root.getDomains()->addDomain( testTypeUnderFunction, &naturalNumberDomainB6 );"<<endl;
	root.getDomains()->addDomain( testTypeUnderFunction, &naturalNumberDomainB6 );
	
	cout<<"cTypeVariable testTypeVariable;"<<endl;
	cTypeVariable testTypeVariable;
	
	cout<<"cDomainNaturalNumberBit domainsNatB4( 4 );"<<endl;
	cDomainNaturalNumberBit domainsNatB4( 4 );
	
	cout<<"root.getDomains()->addDomain( testTypeVariable, &domainsNatB4 );"<<endl;
	root.getDomains()->addDomain( testTypeVariable, &domainsNatB4 );
	
	cout<<"cFunctionValue underFunctionValue3( 3.0 );"<<endl;
	cFunctionValue underFunctionValue3( 3.0 );

	cout<<"tUnderFunctionOneValue underFunctionOneValue2( &underFunctionValue3, NULL, &root );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue2( &underFunctionValue3, NULL, &root );
	
	//test get compressed size
	uiCompressedSize = getActualFunctionCInitiationBits() + (2 + 6);
	if ( (unsigned int)(underFunctionOneValue2.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			underFunctionOneValue2.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( strcat( szFileNameBuffer, (char*)DIR_OUTPUT ),
		getActualFunctionName().c_str() ), "2.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0x00;
	cRestBitPosition = 0;
	cout<<"underFunctionOneValue2.store( *pFile, cRestBit, cRestBitPosition ); "<<endl;
	bStoreSuccesfull = underFunctionOneValue2.store( *pFile, cRestBit, cRestBitPosition );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	unsigned char szUnderFunctionOneValue2[] = { 0x0C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00 };
	addCInitiationForActualFunction( szUnderFunctionOneValue2, 2 );
	iReturn += compareBytsWithFile( szFileNameBuffer, (char*)szUnderFunctionOneValue2, uiCompressedSize / 8 + 1 );
	
	ucRestBit = cRestBit;
	ucRestBitCorrect = szUnderFunctionOneValue2[ (uiCompressedSize) / 8 ];
	sNumberOfRestBitCorrect = uiCompressedSize % 8;
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

	fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
	if ( (fileInXml != NULL) && ( fileInXml->good() ) ){
		
		cReadBits iBitStream( * fileInXml );
		iBitStream.readBits( &cFunctionName, getActualFunctionCInitiationBits() );
		intFib outStatus = 0;
		cout<<"tUnderFunctionOneValue underFunctionOneValue2Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		tUnderFunctionOneValue underFunctionOneValue2Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionOneValue2Loaded.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionOneValue2Loaded.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareOneEqualObjects( underFunctionOneValue2Loaded, "underFunctionOneValue2Loaded", underFunctionOneValue2, "underFunctionOneValue2" );
		iReturn += testNotConnectedUnderFunction( underFunctionOneValue2Loaded );
		cout<<"checking: underFunctionOneValue2Loaded.getUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionOneValue2Loaded.getUnderFunction(),
			&underFunctionValue3, &underFunctionOneValue2Loaded, NULL );

		delete fileInXml;
		ifstream * fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream2( * fileInXml );
		outStatus = 0;
		cout<<"cFunctionOneValue pUnderFunctionOneValue2Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctionOneValue2Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionOneValue2Loaded ){
			if ( pUnderFunctionOneValue2Loaded->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionOneValue2Loaded->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareOneEqualObjects( * pUnderFunctionOneValue2Loaded, "pUnderFunctionOneValue2Loaded", underFunctionOneValue2, "underFunctionOneValue2" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionOneValue2Loaded );
			cout<<"checking: pUnderFunctionOneValue2Loaded->getUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionOneValue*)pUnderFunctionOneValue2Loaded)->getUnderFunction(),
				&underFunctionValue3, pUnderFunctionOneValue2Loaded, NULL );
			delete pUnderFunctionOneValue2Loaded;
		}else{
			cerr<<"Error: No underfunction loaded ."<<endl;
			iReturn++;
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
		fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream3( * fileInXml );
		iBitStream3.readBits( &cFunctionName, getActualFunctionCInitiationBits() );
		outStatus = 0;
		cout<<"tUnderFunctionOneValue underFunctionOneValue2LoadedFull( iBitStream3, "<<
			"outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &underFunctionSup, &rootSimple ); "<<endl;
		tUnderFunctionOneValue underFunctionOneValue2LoadedFull( iBitStream3,
			outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionOneValue2LoadedFull.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionOneValue2LoadedFull.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareOneEqualObjects( underFunctionOneValue2LoadedFull,
			"underFunctionOneValue2LoadedFull", underFunctionOneValue2, "underFunctionOneValue2" );
		//check the getDefiningFibElement() methode from cFunctionOneValue
		if ( underFunctionOneValue2LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionOneValue2LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionOneValue2LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionOneValue
		if ( underFunctionOneValue2LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionOneValue2LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionOneValue2LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		cout<<"checking: underFunctionOneValue2LoadedFull.getUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionOneValue2LoadedFull.getUnderFunction(),
			&underFunctionValue3, &underFunctionOneValue2LoadedFull, &rootSimple );
		
		delete fileInXml;
		fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream4( * fileInXml );
		outStatus = 0;
		cout<<"cFunctionOneValue pUnderFunctionOneValue2LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionOneValue2LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionOneValue2LoadedFull ){
			if ( pUnderFunctionOneValue2LoadedFull->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionOneValue2LoadedFull->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareOneEqualObjects( * pUnderFunctionOneValue2LoadedFull, "pUnderFunctionOneValue2LoadedFull", underFunctionOneValue2, "underFunctionOneValue2" );
			//check the getDefiningFibElement() methode from cFunctionOneValue
			if ( pUnderFunctionOneValue2LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionOneValue2LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionOneValue2LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionOneValue
			if ( pUnderFunctionOneValue2LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionOneValue2LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionOneValue2LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			cout<<"checking: pUnderFunctionOneValue2LoadedFull->getUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionOneValue*)pUnderFunctionOneValue2LoadedFull)->getUnderFunction(),
				&underFunctionValue3, pUnderFunctionOneValue2LoadedFull, &rootSimple );
			
			delete pUnderFunctionOneValue2LoadedFull;
		}else{
			cerr<<"Error: No underfunction loaded ."<<endl;
			iReturn++;
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

	cout<<"tUnderFunctionOneValue underFunctionOneValue3( &underFunctionValue3, NULL, &root );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue3( &underFunctionValue3, NULL, &root );
	
	//test get compressed size
	uiCompressedSize = getActualFunctionCInitiationBits() + (2 + 6);
	if ( (unsigned int)(underFunctionOneValue3.getCompressedSize()) == uiCompressedSize ){
	
		cout<<"The compressed size of the function is correctly "<<
			uiCompressedSize <<" . "<<endl;
	}else{
		cerr<<"Error: The compressed size of the function is "<<
			underFunctionOneValue3.getCompressedSize() << ", but should be "<<
			uiCompressedSize <<" . "<<endl;
		iReturn++;
	}

	szFileNameBuffer[0] = 0;
	strcat( strcat( strcat( szFileNameBuffer, (char*)DIR_OUTPUT ),
		getActualFunctionName().c_str() ), "3.fib" );
	pFile = new ofstream( szFileNameBuffer, ios_base::out | ios_base::binary );
	
	cRestBit = 0x01;
	cRestBitPosition = 3;
	unsigned char cRestBitPositionOrginal = cRestBitPosition;
	cout<<"underFunctionOneValue3.store( *pFile, cRestBit, cRestBitPosition ); "<<endl;
	bStoreSuccesfull = underFunctionOneValue3.store( *pFile, cRestBit, cRestBitPosition );
	(*pFile) << cRestBit;
	delete pFile;
	
	if ( bStoreSuccesfull ){
	
		cout<<"The data was stored successfull to the file \""<< szFileNameBuffer <<"\". "<<endl;
	}else{
		cerr<<"Error: Storing the data to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
		iReturn++;
	}
	//test stored data
	unsigned char szUnderFunctionOneValue3[] = { 0x0C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00 };
	addCInitiationForActualFunction( szUnderFunctionOneValue3, 2, cRestBitPositionOrginal );
	szUnderFunctionOneValue3[ 0 ] = szUnderFunctionOneValue3[ 0 ] | 0x01;
	iReturn += compareBytsWithFile( szFileNameBuffer, (char*)szUnderFunctionOneValue3, (uiCompressedSize + cRestBitPositionOrginal) / 8 + 1 );
	
	ucRestBit = cRestBit;
	ucRestBitCorrect = szUnderFunctionOneValue3[ (uiCompressedSize + cRestBitPositionOrginal ) / 8 ];
	sNumberOfRestBitCorrect = (uiCompressedSize + cRestBitPositionOrginal) % 8;
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

	fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
	if ( (fileInXml != NULL) && ( fileInXml->good() ) ){
		
		cReadBits iBitStream( * fileInXml );
		long cBuffer;
		iBitStream.readBits( cBuffer, ((unsigned int)(cRestBitPositionOrginal + getActualFunctionCInitiationBits())) );
		intFib outStatus = 0;
		cout<<"tUnderFunctionOneValue underFunctionOneValue3Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		tUnderFunctionOneValue underFunctionOneValue3Loaded( iBitStream, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionOneValue3Loaded.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionOneValue3Loaded.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		int iErrorsEqual = testCompareOneEqualObjects( underFunctionOneValue3Loaded, "underFunctionOneValue3Loaded", underFunctionOneValue3, "underFunctionOneValue3" );
		iReturn += testNotConnectedUnderFunction( underFunctionOneValue3Loaded );
		if ( iErrorsEqual != 0 ){
			cerr<<"Error: Loaded underfunction not equal (value="<<
				underFunctionOneValue3Loaded.getValue() <<")."<<endl;
		}
		iReturn += iErrorsEqual;
		cout<<"checking: underFunctionOneValue3Loaded.getUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionOneValue3Loaded.getUnderFunction(),
			&underFunctionValue3, &underFunctionOneValue3Loaded, NULL );

		delete fileInXml;
		ifstream * fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream2( * fileInXml );
		iBitStream2.readBits( cBuffer, ((unsigned int)(cRestBitPositionOrginal)) );
		outStatus = 0;
		cout<<"cFunctionOneValue pUnderFunctionOneValue3Loaded = cUnderFunction::restore( "<<
			"iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain ); "<<endl;
		cUnderFunction * pUnderFunctionOneValue3Loaded = cUnderFunction::restore(
			iBitStream2, outStatus, liDefinedVariables, pValueDomain, pVariableDomain );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionOneValue3Loaded ){
			if ( pUnderFunctionOneValue3Loaded->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionOneValue3Loaded->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iErrorsEqual = testCompareOneEqualObjects( * pUnderFunctionOneValue3Loaded, "pUnderFunctionOneValue3Loaded", underFunctionOneValue3, "underFunctionOneValue3" );
			iReturn += testNotConnectedUnderFunction( * pUnderFunctionOneValue3Loaded );
			if ( iErrorsEqual != 0 ){
				cerr<<"Error: Loaded underfunction not equal (value="<<
					underFunctionOneValue3Loaded.getValue() <<")."<<endl;
			}
			iReturn += iErrorsEqual;
			cout<<"checking: pUnderFunctionOneValue3Loaded->getUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionOneValue*)pUnderFunctionOneValue3Loaded)->getUnderFunction(),
				&underFunctionValue3, pUnderFunctionOneValue3Loaded, NULL );
			delete pUnderFunctionOneValue3Loaded;
		}else{
			cerr<<"Error: No underfunction loaded ."<<endl;
			iReturn++;
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
		fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream3( * fileInXml );
		iBitStream3.readBits( cBuffer, ((unsigned int)(cRestBitPositionOrginal + getActualFunctionCInitiationBits())) );
		outStatus = 0;
		cout<<"tUnderFunctionOneValue underFunctionOneValue3LoadedFull( iBitStream3, "<<
			"outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &underFunctionSup, &rootSimple ); "<<endl;
		tUnderFunctionOneValue underFunctionOneValue3LoadedFull( iBitStream3,
			outStatus, liDefinedVariables, pValueDomain, pVariableDomain, &underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( underFunctionOneValue3LoadedFull.getType() == getActualFunctionType() ){
		
			cout<<"The loaded underfunction has the correct type. "<<endl;
		}else{
			cerr<<"Error: The loaded underfunction has the type "<<
				underFunctionOneValue3LoadedFull.getType() <<" , but should have the type "<<
				getActualFunctionType() <<" ."<<endl;
			iReturn++;
		}
		iReturn += testCompareOneEqualObjects( underFunctionOneValue3LoadedFull,
			"underFunctionOneValue3LoadedFull", underFunctionOneValue3, "underFunctionOneValue3" );
		//check the getDefiningFibElement() methode from cFunctionOneValue
		if ( underFunctionOneValue3LoadedFull.getDefiningFibElement() == &rootSimple  ){
		
			cout<<"The underfunction defining fib -element is correctly "<<
				underFunctionOneValue3LoadedFull.getDefiningFibElement() <<" . "<<endl;
		}else{
			cerr<<"Error: The underfunction defining fib -element is "<<
				underFunctionOneValue3LoadedFull.getDefiningFibElement() <<
				" but should be rootSimple="<< &rootSimple <<" ."<<endl;
			iReturn++;
		}
		//check the getSuperiorUnderFunction() methode from cFunctionOneValue
		if ( underFunctionOneValue3LoadedFull.getSuperiorUnderFunction() == &underFunctionSup  ){
		
			cout<<"The superior underfunction of the underfunction correctly "<<
				underFunctionOneValue3LoadedFull.getSuperiorUnderFunction() <<" . "<<endl;
		}else{
			cerr<<"Error: The superior underfunction of the underfunction is "<<
				underFunctionOneValue3LoadedFull.getSuperiorUnderFunction() <<
				" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
			iReturn++;
		}
		cout<<"checking: underFunctionOneValue3LoadedFull.getUnderFunction()"<<endl;
		iReturn += checkUnderFunction( underFunctionOneValue3LoadedFull.getUnderFunction(),
			&underFunctionValue3, &underFunctionOneValue3LoadedFull, &rootSimple );
		
		delete fileInXml;
		fileInXml = new ifstream( szFileNameBuffer, ios_base::in | ios_base::binary );
		cReadBits iBitStream4( * fileInXml );
		iBitStream4.readBits( cBuffer, ((unsigned int)(cRestBitPositionOrginal)) );
		outStatus = 0;
		cout<<"cFunctionOneValue pUnderFunctionOneValue3LoadedFull = cUnderFunction::restore( "<<
			"iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,"<<
			"&underFunctionSup, &rootSimple ); "<<endl;
		cUnderFunction * pUnderFunctionOneValue3LoadedFull = cUnderFunction::restore(
			iBitStream4, outStatus, liDefinedVariables, pValueDomain, pVariableDomain,
			&underFunctionSup, &rootSimple );
		
		if ( outStatus == 0 ){
		
			cout<<"The data was loaded successfull. "<<endl;
		}else{
			cerr<<"Error: While loading the data (outStatus="<< outStatus <<")."<<endl;
			iReturn++;
		}
		if ( pUnderFunctionOneValue3LoadedFull ){
			if ( pUnderFunctionOneValue3LoadedFull->getType() == getActualFunctionType() ){
			
				cout<<"The loaded underfunction has the correct type. "<<endl;
			}else{
				cerr<<"Error: The loaded underfunction has the type "<<
					pUnderFunctionOneValue3LoadedFull->getType() <<" , but should have the type "<<
					getActualFunctionType() <<" ."<<endl;
				iReturn++;
			}
			iReturn += testCompareOneEqualObjects( * pUnderFunctionOneValue3LoadedFull, "pUnderFunctionOneValue3LoadedFull", underFunctionOneValue3, "underFunctionOneValue3" );
			//check the getDefiningFibElement() methode from cFunctionOneValue
			if ( pUnderFunctionOneValue3LoadedFull->getDefiningFibElement() == &rootSimple  ){
			
				cout<<"The underfunction defining fib -element is correctly "<<
					pUnderFunctionOneValue3LoadedFull->getDefiningFibElement() <<" . "<<endl;
			}else{
				cerr<<"Error: The underfunction defining fib -element is "<<
					pUnderFunctionOneValue3LoadedFull->getDefiningFibElement() <<
					" but should be rootSimple="<< &rootSimple <<" ."<<endl;
				iReturn++;
			}
			//check the getSuperiorUnderFunction() methode from cFunctionOneValue
			if ( pUnderFunctionOneValue3LoadedFull->getSuperiorUnderFunction() == &underFunctionSup  ){
			
				cout<<"The superior underfunction of the underfunction correctly "<<
					pUnderFunctionOneValue3LoadedFull->getSuperiorUnderFunction() <<" . "<<endl;
			}else{
				cerr<<"Error: The superior underfunction of the underfunction is "<<
					pUnderFunctionOneValue3LoadedFull->getSuperiorUnderFunction() <<
					" but should be underFunctionSup="<< &underFunctionSup <<" ."<<endl;
				iReturn++;
			}
			cout<<"checking: pUnderFunctionOneValue3LoadedFull->getUnderFunction()"<<endl;
			iReturn += checkUnderFunction( ((cFunctionOneValue*)pUnderFunctionOneValue3LoadedFull)->getUnderFunction(),
				&underFunctionValue3, pUnderFunctionOneValue3LoadedFull, &rootSimple );
			delete pUnderFunctionOneValue3LoadedFull;
		}else{
			cerr<<"Error: No underfunction loaded ."<<endl;
			iReturn++;
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
 * This method tests the variable methods of the cFunctionOneValue class.
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
 * @param tUnderFunctionOneValue the type of the tested cFunctionOneValue
 * 	is of the type of this object
 * @return the number of erros occured in the test
 */
template <class tUnderFunctionOneValue> int testVariable(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function ){

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
	cout<<"cFunctionVariable underFunctionVariable2( pVariable2 );"<<endl;
	cFunctionVariable underFunctionVariable2( pVariable2 );

	cout<<"tUnderFunctionOneValue underFunctionOneValue1( &underFunctionVariable1 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue1( &underFunctionVariable1 );
	set<cFibVariable*> setCorrectUsedVariables;
	setCorrectUsedVariables.insert( pVariable1 );
	
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable1 )"<<endl;
	if ( underFunctionOneValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable2 )"<<endl;
	if ( ! underFunctionOneValue1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( ! underFunctionOneValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionOneValue1.getUsedVariables(); "<<endl;
	set<cFibVariable*> setUsedVariables = underFunctionOneValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}
	

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the getValue() method"<<endl;

	//check the getValue() methode from cFunctionOneValue
	cout<<"pVariable1->setValue( 2.0 );"<<endl;
	pVariable1->setValue( 2.0 );
	cout<<"pVariable2->setValue( 5.0 );"<<endl;
	pVariable2->setValue( 5.0 );
	double dValue = getActualFunctionValue( underFunctionVariable1.getValue() );
	cout<<"underFunctionOneValue1.getValue()"<<endl;
	if ( underFunctionOneValue1.getValue() == dValue ){
	
		cout<<"The the value "<< underFunctionOneValue1.getValue() <<
			" was correctly returned by the underfunction. "<<endl;
	}else{
		cerr<<"Error: The the value "<< underFunctionOneValue1.getValue() <<
			" was returned by the underfunction, but it should be "<< dValue <<" . "<<endl;
		iReturn++;
	}

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the replaceVariable() method"<<endl;
	
	cout<<"underFunctionOneValue1.replaceVariable( pVariable1, pVariable3 );"<<endl;
	bool bVariableReplaced = underFunctionOneValue1.replaceVariable( pVariable1, pVariable3 );
	setCorrectUsedVariables.erase( pVariable1 );
	setCorrectUsedVariables.insert( pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionOneValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! underFunctionOneValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable2 )"<<endl;
	if ( ! underFunctionOneValue1.isUsedVariable( pVariable2 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionOneValue1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionOneValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"underFunctionOneValue1.replaceVariable( pVariable1, pVariable4 );"<<endl;
	bVariableReplaced = underFunctionOneValue1.replaceVariable( pVariable1, pVariable4 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionOneValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! underFunctionOneValue1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionOneValue1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionOneValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"underFunctionOneValue1.replaceVariable( pVariable3, pVariable3 );"<<endl;
	bVariableReplaced = underFunctionOneValue1.replaceVariable( pVariable3, pVariable3 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionOneValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! underFunctionOneValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! underFunctionOneValue1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionOneValue1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionOneValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"underFunctionOneValue1.replaceVariable( NULL, pVariable1 );"<<endl;
	bVariableReplaced = underFunctionOneValue1.replaceVariable( NULL, pVariable1 );
	if ( ! bVariableReplaced ){
	
		cout<<"The variable was correctly not replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionOneValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! underFunctionOneValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! underFunctionOneValue1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionOneValue1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionOneValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	cout<<endl<<"underFunctionOneValue1.replaceVariable( pVariable3, NULL );"<<endl;
	bVariableReplaced = underFunctionOneValue1.replaceVariable( pVariable3, NULL );
	if ( ! bVariableReplaced ){
	
		cout<<"The variable was correctly not replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( underFunctionOneValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! underFunctionOneValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable4 )"<<endl;
	if ( ! underFunctionOneValue1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable2 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable2 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionOneValue1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionOneValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}


	cout<<endl<<"underFunctionOneValue1.replaceVariable( pVariable3, pVariable4 );"<<endl;
	bVariableReplaced = underFunctionOneValue1.replaceVariable( pVariable3, pVariable4 );
	setCorrectUsedVariables.erase( pVariable3 );
	setCorrectUsedVariables.insert( pVariable4 );
	if ( bVariableReplaced ){
	
		cout<<"The variable was correctly replaced. "<<endl;
	}else{
		cerr<<"Error: The variable was not replaced. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable4 )"<<endl;
	if ( underFunctionOneValue1.isUsedVariable( pVariable4 ) ){
	
		cout<<"The variable pVariable4 is correctly used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable4 is not used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable3 )"<<endl;
	if ( ! underFunctionOneValue1.isUsedVariable( pVariable3 ) ){
	
		cout<<"The variable pVariable3 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable3 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check the isUsedVariable() methode from cFunctionOneValue
	cout<<"underFunctionOneValue1.isUsedVariable( pVariable1 )"<<endl;
	if ( ! underFunctionOneValue1.isUsedVariable( pVariable1 ) ){
	
		cout<<"The variable pVariable1 is correctly not used in the functionelement. "<<endl;
	}else{
		cerr<<"Error: The variable pVariable1 is used in the functionelement. "<<endl;
		iReturn++;
	}
	//check getUsedVariables()
	cout<<"setUsedVariables = underFunctionOneValue1.getUsedVariables(); "<<endl;
	setUsedVariables = underFunctionOneValue1.getUsedVariables();
	if ( setUsedVariables == setCorrectUsedVariables ){
	
		cout<<"The correct used variables wher given back. "<<endl;
	}else{
		cerr<<"Error: The used variables given back are wrong. "<<endl;
		iReturn++;
	}

	return iReturn;
}


/**
 * This method tests the defining fib -element methods of the cFunctionOneValue class.
 *
 * methods tested:
 * 	- void setDefiningFibElement( cFibElement *fibElement=NULL, bool bCheckDomains=true );
 * 	- cFibElement * getDefiningFibElement() const;
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param tUnderFunctionOneValue the type of the tested cFunctionOneValue
 * 	is of the type of this object
 * @return the number of erros occured in the test
 */
template <class tUnderFunctionOneValue> int testDefiningFibElement(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the defining fib -element"<<endl;
	
	cout<<"cFunctionValue underFunctionValue1( 8.0 );"<<endl;
	cFunctionValue underFunctionValue1( 8.0 );

	cout<<"tUnderFunctionOneValue underFunctionOneValue1( &underFunctionValue1 );"<<endl;
	tUnderFunctionOneValue underFunctionOneValue1( &underFunctionValue1 );
	
	cout<<"tUnderFunctionOneValue ufValueCorrect1( &underFunctionValue1 );"<<endl;
	tUnderFunctionOneValue ufValueCorrect1( &underFunctionValue1 );

	cFibElement * pDefiningFibElement = NULL;
	//check the getDefiningFibElement() methode from cFunctionOneValue
	cout<<"checking: underFunctionOneValue1"<<endl;
	iReturn += checkUnderFunction( &underFunctionOneValue1,
		&ufValueCorrect1, NULL, pDefiningFibElement );
	cout<<"checking: underFunctionOneValue1.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionOneValue1.getUnderFunction(),
		&underFunctionValue1, &underFunctionOneValue1, pDefiningFibElement );

	cPoint point1;
	cout<<"underFunctionOneValue1.setDefiningFibElement( &point1 );"<<endl;
	underFunctionOneValue1.setDefiningFibElement( &point1 );
	pDefiningFibElement = &point1;
	cout<<"checking: underFunctionOneValue1"<<endl;
	iReturn += checkUnderFunction( &underFunctionOneValue1,
		&ufValueCorrect1, NULL, pDefiningFibElement );
	cout<<"checking: underFunctionOneValue1.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionOneValue1.getUnderFunction(),
		&underFunctionValue1, &underFunctionOneValue1, pDefiningFibElement );
	
	cout<<"underFunctionOneValue1.setDefiningFibElement( &point1 );"<<endl;
	underFunctionOneValue1.setDefiningFibElement( &point1 );
	pDefiningFibElement = &point1;
	cout<<"checking: underFunctionOneValue1"<<endl;
	iReturn += checkUnderFunction( &underFunctionOneValue1,
		&ufValueCorrect1, NULL, pDefiningFibElement );
	cout<<"checking: underFunctionOneValue1.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionOneValue1.getUnderFunction(),
		&underFunctionValue1, &underFunctionOneValue1, pDefiningFibElement );

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the methods for the defining fib -element with domains set"<<endl;
	
	cout<<"cRoot root;"<<endl;
	cRoot root;
	
	cout<<"cTypeUnderFunction testTypeUnderFunction;"<<endl;
	cTypeUnderFunction testTypeUnderFunction;
	
	//create vector domain with one elements
	cout<<"cDomainNaturalNumberBit domainsNatB3( 3 );"<<endl;
	cDomainNaturalNumberBit domainsNatB3( 3 );

	cout<<"root.getDomains()->addDomain( testTypeUnderFunction, &domainsNatB3 );"<<endl;
	root.getDomains()->addDomain( testTypeUnderFunction, &domainsNatB3 );
	
	cout<<"cTypeVariable testTypeVariable;"<<endl;
	cTypeVariable testTypeVariable;
	
	cout<<"cDomainNaturalNumberBit naturalNumberDomainB4( 4 );"<<endl;
	cDomainNaturalNumberBit naturalNumberDomainB4( 4 );
	
	cout<<"root.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB4 );"<<endl;
	root.getDomains()->addDomain( testTypeVariable, &naturalNumberDomainB4 );

	cout<<"underFunctionOneValue1.setDefiningFibElement( &root, false );"<<endl;
	underFunctionOneValue1.setDefiningFibElement( &root, false );
	pDefiningFibElement = &root;
	cout<<"checking: underFunctionOneValue1"<<endl;
	iReturn += checkUnderFunction( &underFunctionOneValue1,
		&ufValueCorrect1, NULL, pDefiningFibElement );
	cout<<"checking: underFunctionOneValue1.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionOneValue1.getUnderFunction(),
		&underFunctionValue1, &underFunctionOneValue1, pDefiningFibElement );


	cout<<"cFunctionValue underFunctionValue7( 7.0 );"<<endl;
	cFunctionValue underFunctionValue7( 7.0 );
	cout<<"cFunctionValue underFunctionValue0( 0.0 );"<<endl;
	cFunctionValue underFunctionValue0( 0.0 );

	cout<<"tUnderFunctionOneValue ufValueCorrect2( &underFunctionValue7 );"<<endl;
	tUnderFunctionOneValue ufValueCorrect2( &underFunctionValue7 );

	cout<<"underFunctionOneValue1.setDefiningFibElement( &root, true );"<<endl;
	underFunctionOneValue1.setDefiningFibElement( &root, true );
	pDefiningFibElement = &root;
	cout<<"checking: underFunctionOneValue1"<<endl;
	iReturn += checkUnderFunction( &underFunctionOneValue1,
		&ufValueCorrect2, NULL, pDefiningFibElement );
	cout<<"checking: underFunctionOneValue1.getUnderFunction()"<<endl;
	iReturn += checkUnderFunction( underFunctionOneValue1.getUnderFunction(),
		&underFunctionValue7, &underFunctionOneValue1, pDefiningFibElement );

	
	return iReturn;
}



/**
 * @param dValue the value to check
 * @return true if the value is true, else false
 */
inline bool own_isnan( double dValue ){
    return dValue != dValue;
}


/**
 * This method tests the getValue() method of the cFunctionOneValue class.
 *
 * methods tested:
 * 	- void getValue();
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param tUnderFunctionOneValue the type of the tested cFunctionOneValue
 * 	is of the type of this object
 * @return the number of erros occured in the test
 */
template <class tUnderFunctionOneValue> int testValue(
	unsigned long &ulTestphase, const tUnderFunctionOneValue &function ){
	
	int iReturn = 0;//returnvalue of the test; the number of occured Errors

	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the method getValue() method on some fixed values"<<endl;
	
	//test getValue() an standardvalues
	list< doubleFib > liStandardValues;
	liStandardValues.push_back( 0.0 );
	liStandardValues.push_back( 1.0 );
	liStandardValues.push_back( 1000.0 );
	liStandardValues.push_back( 0.0001 );
	liStandardValues.push_back( -1.0 );
	liStandardValues.push_back( -1000.0 );
	liStandardValues.push_back( -0.0001 );
	
	for ( list< doubleFib >::iterator itrUf = liStandardValues.begin();
			itrUf != liStandardValues.end(); itrUf++ ){
		
		cFunctionValue ufunction1( *itrUf );
		doubleFib dResult = getActualFunctionValue( *itrUf );
		
		tUnderFunctionOneValue ufOneValue( &ufunction1 );
		
		if ( own_isnan( dResult ) ){
			if ( own_isnan( ufOneValue.getValue() ) ){
				cout<<"The result from "<< (*itrUf) << " is correctly "<<
					ufOneValue.getValue() <<" . "<<endl;
			}else{
				cerr<<"Error: The result from "<< (*itrUf) <<" is "<<
					ufOneValue.getValue() <<" , but should be "<< dResult <<" . "<<endl;
				iReturn++;
			}
			continue;
		}
		
		if ( dResult == ufOneValue.getValue() ){
		
			cout<<"The result from "<< (*itrUf) << " is correctly "<<
				ufOneValue.getValue() <<" . "<<endl;
		}else{
			cerr<<"Error: The result from "<< (*itrUf) <<" is "<<
				ufOneValue.getValue() <<" , but should be "<< dResult <<" . "<<endl;
			iReturn++;
		}
	}
	
	ulTestphase++;
	cout<<endl<<"TESTPASE "<<ulTestphase<<" : Testing the method getValue() method on some random values"<<endl;
	//test getValue() on random values
	
	for ( unsigned int iteration = 0; iteration <= 1000; iteration++ ){
		
		doubleFib dValue = (double)(rand() % 2000000 - 1000000) / 1000.0;
		cFunctionValue ufunction1( dValue );
		doubleFib dResult = getActualFunctionValue( dValue );
		
		tUnderFunctionOneValue ufOneValue( &ufunction1 );
		
		if ( own_isnan( dResult ) ){
			if ( own_isnan( ufOneValue.getValue() ) ){
				cout<<"The result from "<< dValue << " is correctly "<<
					ufOneValue.getValue() <<" . "<<endl;
			}else{
				cerr<<"Error: The result from "<< dValue <<" is "<<
					ufOneValue.getValue() <<" , but should be "<< dResult <<" . "<<endl;
				iReturn++;
			}
			continue;
		}
		
		if ( dResult == ufOneValue.getValue() ){
		
			cout<<"The result from "<< dValue << " is correctly "<<
				ufOneValue.getValue() <<" . "<<endl;
		}else{
			cerr<<"Error: The result from "<< dValue << " is "<<
				ufOneValue.getValue() <<" , but should be "<< dResult <<" . "<<endl;
			iReturn++;
		}
	}
	
	return iReturn;
}










